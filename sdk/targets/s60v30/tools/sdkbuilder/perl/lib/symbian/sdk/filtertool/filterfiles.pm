#!\bin\perl -w
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.

=pod
=head1 NAME

Symbian::SDK::FilterTool::FilterFiles - implements rules for turning a release into an SDK

=head1 SYNOPSIS

 use Symbian::SDK::FilterTool::FilterFiles;

 my $filterer = Symbian::SDK::FilterTool::FilterFiles();

 # $config is a Symbian::Config::Basic object
 my $files = $filterer->Run($config)

=head1 DESCRIPTION

This is the class where the filter rules are implemented. It works on files in the directory specified by the 'Work area' setting in the configuration object.

This makes use of the various stat gathering libraries;
  L<Symbian::SDK::DoxyDocStats|..\DoxyDocStats>;
  L<Symbian::SDK::LibSource|..\LibSource>;
  L<Symbian::DistributionPolicy::Reader|..\..\DistributionPolicy::Reader>;
  L<Symbian::Exportinfo|..\..\ExportInfo>;
  L<Symbian::SourceInfo|..\..\SourceInfo>.

It also uses L<Symbian::SDK::FileCategorisation|FileCategorisation> to assign files into filter groups, in order to determine which set of rules to use for each file.

=head1 METHODS

=cut
package Symbian::SDK::FilterTool::FilterFiles;

use Symbian::SDK::FilterTool::FilterFileList;
use Symbian::SDK::FileCategorisation;
use Symbian::SDK::DoxyDocStats;
use Symbian::SDK::LibSource;
use Symbian::Config::Basic;
use Symbian::DistributionPolicy::Reader;
use Symbian::ExportInfo;
use Symbian::SourceInfo;
use Symbian::Logger::Singleton;
use File::Find;
use File::Spec;
use File::Basename;
use Symbian::SDK::FilterTool::UserFilterRules;
use Symbian::SystemDefinition::SysDefCollector;
use Symbian::SystemDefinition::SysDefParser;

=head2 new()

B<Returns>: Symbian::SDK::FilterTool::FilterFiles - the newly created object

B<Parameters>: None

Constructs the object.

=cut
sub new()
	{
	my $class = shift;

	my $self={};

	bless $self, $class;

	return $self;
	}

=head2 Run(Symbian::Config::Basic $options)

B<Returns>: Symbian::SDK::FilterTool::FilterFileList - The filtered list of files in the input area

B<Parameters>:
  $options - The configuration object containing options settings for filtering (including the input area to use)

Creates a L<FilterFileList> object listing all files in the input area, marking each file as being either included or excluded, according to the filtering rules.

=cut
sub Run($)
	{
	my $self = shift;
	my ($options) = @_;

	my $logger= new Symbian::Logger::Singleton();

	$logger->PhaseStart("Initialising variables");

	my $ruleslog;
	my $workArea = $options->GetSafe("Input area");
	my $sourcepath = $options->GetSafe("Source root") || "/src/";
	my $sourceArea = File::Spec->catdir($workArea,$sourcepath);
	my $doxydir = $options->GetSafe("Doxygen output area");
	my $configs = $options->GetSafe("Config names");
	my @configs;
	my @bldinfs;
	my $filteruicode = $options->Get("IPR filter UI code");
	my $uisourcepath;
	my @uibldinfs;

	my $ruleslogfile = $options->GetSafe("filter log");
	$ruleslog = new Symbian::Logger($ruleslogfile);

	$workArea =~ s!\\!/!g; # Normalise slashes
	if (!-d $workArea)
		{
		$logger->Die("ERROR: Work area product directory '$workArea' does not exist");
		}

	@configs = ($configs);
	@configs = @$configs if ref $configs; # May be a list

	@bldinfs = $self->getBldInfs($logger, $sourceArea, \@configs);
	@bldinfs = map (File::Spec->catfile($sourceArea,$_), @bldinfs); # Add root


	if ((defined $filteruicode) && ($filteruicode =~ /(true|yes)/i))
		{
		$filteruicode = 1; # TRUE
		$logger->Print("IPR filtering of UI source enabled");
		$uisourceroot = $options->GetSafe("UI source root");
		my $uiconfigs = $options->GetSafe("UI configs");

		my @uiconfigs = ($uiconfigs);
		@uiconfigs = @$uiconfigs if ref $uiconfigs; # May be a list

		@uibldinfs = $self->getBldInfs($logger, File::Spec->catdir($workArea, $uisourceroot), \@uiconfigs);
		@uibldinfs = map (File::Spec->catfile($workArea, $uisourceroot, $_), @uibldinfs); # Add ui source root
		}
	else
		{
		$filteruicode = 0; # FALSE
		$logger->Print("Not IPR filtering UI source");
		}

	$logger->PhaseStart("Scanning input area");
	my $files = new Symbian::SDK::FilterTool::FilterFileList();
	$files->ScanDir($workArea);

	$logger->PhaseStart("Filtering files");
	$ruleslog->PhaseStart("Filtering files");

	my $distpolreader = new Symbian::DistributionPolicy::Reader();

	my $filelistobj =  $files->GetFileList();
	my $filecats = new Symbian::SDK::FileCategorisation($filelistobj, $options);
	$filecats->CategoriseFiles($workArea);

	my $definedGroups = $filecats->GroupsNames();
	my $userFilter = Symbian::SDK::FilterTool::UserFilterRules->new();
	if (my $userRulesFile = $options->Get("User rules file"))
		{
		$userFilter->ReadUserRules($userRulesFile,$definedGroups);
		}

	# Identify UI files
	$logger->Component("Identifying UI binaries and exports");

	# Find release tools
	my $reltoolspath;

	foreach my $path (split(/;/, $ENV{PATH}))
		{
		$reltoolspath = $path if -f $path."\\envdb.pm";
		}

	push @INC, $reltoolspath if defined $reltoolspath;

	require IniData;
	require EnvDb;

	# Get the CBR environment
	my $envdb;
	eval { $envdb = EnvDb->Open() };

	if (!defined $envdb)
		{
		$logger->Die("ERROR: Couldn't read CBR environment: $!");
		}

	my $verinfo = $envdb->VersionInfo();
	my %components;

	if (!defined $verinfo)
		{
		$logger->Die("No valid CBR environment found; please check");
		}

	# Get UI components
	my $UIfilter = $options->Get("UI components");

	my @matched_components;

	if (defined $UIfilter)
		{
		my @UIfilter = ref($UIfilter) ? @$UIfilter : ($UIfilter);

		foreach my $match (@UIfilter)
			{
			# Convert match to regexp
			$match =~ s/([\\^\.\$\|\(\)\[\]\+\?\{\}])/\\$1/g; # Escape special characters
			$match =~ s/\*/\.\*/g; # Convert * to .*

			push @matched_components, grep(/^$match$/i, keys(%$verinfo));
			}
		}

	# Read the UI bins
	my @UIbins;

	$workArea =~ /^([a-z]:)/i;
	my $drive = $1;

	foreach my $component (@matched_components)
		{
		my @bins = @{$envdb->ListBinsStandard($component, $verinfo->{$component})};
		shift @bins; # Discard '[Files, Status]' header
		@bins = map($drive.$_->[0], @bins); # Take the first entry in each element listref, and prepend the drive

		push @UIbins, @bins;
		}

	# Categorise the UI bins
	my @UIbinIDs = map($filelistobj->GetFileID($_), @UIbins);	
	$filecats->RecategoriseFiles(\@UIbinIDs, "api", "UI_api");
	$filecats->RecategoriseFiles(\@UIbinIDs, "non_os", "UI_bin");
	$filecats->RecategoriseFiles(\@UIbinIDs, "other", "UI_bin");

	# Parse doc stats
	$logger->Component("Loading Doxygen output");

	my $docstats = new Symbian::SDK::DoxyDocStats();
	my $libsource = new Symbian::SDK::LibSource();

	my $statsparsed = 0; #FALSE
	my $parser = sub
		{
		$docstats->parse($File::Find::name) if -f $File::Find::name;
		$statsparsed = 1; #TRUE
		};

	my $bldinfparsed = 0; #FALSE
	foreach my $config (@configs)
		{
		my $stats = File::Spec->catdir($doxydir, "stats", $config);
		find($parser, $stats);

		if ($libsource->LoadTargetData(File::Spec->catdir($doxydir, "doxygen", $config)))
			{
			$bldinfparsed = 1; #TRUE
			}
		}

	if (!$statsparsed)
		{
		$logger->Die("ERROR: Didn't find any doxygen stats to parse");
		}
	elsif (!$bldinfparsed)
		{
		$logger->Die("ERROR: Didn't find any doxygen bld.inf xml files to parse");
		}

	# Parse bld.inf files for exports
	$logger->Component("Gathering export mappings");

	my $exportInfo = new Symbian::ExportInfo($filelistobj, \@bldinfs);

	my $uiexportInfo;
	if ($filteruicode)
		{
		$uiexportInfo = new Symbian::ExportInfo($filelistobj, \@uibldinfs);
		}

	my $extramacros = $options->Get("cpp macros");
	$extramacros = [$extramacros] if (defined($extramacros) && (!ref($extramacros)));
	my $includer = new Symbian::SourceInfo($extramacros);

	# Perform filtering
	$logger->Component("Filtering UI source");
	$ruleslog->Component("Filtering UI source");

	my $groupname = $filecats->UISourceGroupName();
	my $userGroupFilters = $userFilter->GetGroupFilters($groupname);

	foreach my $fileid ($filecats->UISourceFiles())
		{
		my $file = $filelistobj->LookupFile($fileid);

		if ($filteruicode)
			{
			my $policy = $distpolreader->ReadPolicyFile($file);

			if ($policy->ExportRestricted())
				{
				$ruleslog->Print("Excluded: $file\: File is export restricted");
				$files->ExcludeFile($file);
				}
	 		elsif ($policy->Category() =~ /^[ABCDE]$/i)
				{
				# Is neither cat F/G example, or documentation (cat X)
				$ruleslog->Print("Excluded: $file\: File is not IPR type F or G");
				$files->ExcludeFile($file);
				}
			elsif (!$files->IsExcluded($file))
				{
				if(!$self->UserFilterer($files,$file,$groupname,$ruleslog,$userGroupFilters))
					{
					$ruleslog->Print("Included: $file\: File is type F or G");
					$files->IncludeFile($file);
					}
				}
			}
		else
			{
			# Not filtering UI source
			$ruleslog->Print("Included: $file\: Not filtering UI source");
			$files->IncludeFile($file);
			}
		}

	# Perform filtering
	$logger->Component("Filtering UI API items");
	$ruleslog->Component("Filtering UI API items");

	foreach my $fileid ($filecats->GetUserGroup("UI_api"))
		{
		my $file = $filelistobj->LookupFile($fileid);

		if ($filteruicode)
			{
			if ($file =~ /epoc32[\/\\]include[\/\\]/i)
				{
				$file =~ s!/!\\!g;
				my $sourcefile = $uiexportInfo->GetSourcePath($file);
				if (!defined $sourcefile)
					{
					$ruleslog->Print("Included: $file\: UI Binary in epoc32\\include");
					# File has no IM or IPR
					$files->IncludeFile($file);
					}
				else
					{
					my $policy = $distpolreader->ReadPolicyFile($sourcefile);

					if ($policy->ExportRestricted())
						{
						$ruleslog->Print("Excluded: $file\: UI File is export restricted");
						$files->ExcludeFile($file);
						}
					elsif ($policy->Category() =~ /^[DEFG]$/i)
						{
						$ruleslog->Print("Included: $file\: UI File has IPR type D, E, F, G");
						$files->IncludeFile($file);
						}
					elsif ($policy->Category() =~ /^[ABC]$/i)
						{
						$ruleslog->Print("Excluded: $file\: UI File is IPR type A, B, C");
						$files->ExcludeFile($file);
						}
					else
						{
						$ruleslog->Print("Excluded: $file\: UI File is IPR type X");
						$files->ExcludeFile($file);
						}
					}
				}
			else
				{
				# Don't filtering non-header files
				$ruleslog->Print("Included: $file\: Non-header UI API file");
				$files->IncludeFile($file);
				}
			}
		else
			{
			# Not filtering bins+exports
			$ruleslog->Print("Included: $file\: Not filtering UI API files");
			$files->IncludeFile($file);
			}
		}
	
	# Perform filtering
	$logger->Component("Filtering UI binaries");
	$ruleslog->Component("Filtering UI binaries");

	foreach my $fileid ($filecats->GetUserGroup("UI_bin"))
		{
		my $file = $filelistobj->LookupFile($fileid);

		$ruleslog->Print("Included: $file\: UI binary");
		$files->IncludeFile($file);
		}

	# Perform filtering
	$logger->Component("Filtering API items");
	$ruleslog->Component("Filtering API items");

	$groupname = $filecats->ApiGroupName();
	$userGroupFilters = $userFilter->GetGroupFilters($groupname);

	my @APIfiles = map($filelistobj->LookupFile($_), $filecats->ApiFiles());	

	foreach my $file (@APIfiles)
		{
		if ($file =~ /epoc32[\/\\]include[\/\\]/i)
			{
			$file =~ s!/!\\!g;
			my $sourcefile = $exportInfo->GetSourcePath($file);
			if (!defined $sourcefile)
				{
				$ruleslog->Print("Included: $file\: UI Binary in epoc32\\include");
				# File has no IM or IPR
				$files->IncludeFile($file);
				}
			else
				{
				my $policy = $distpolreader->ReadPolicyFile($sourcefile);

				if ($policy->ExportRestricted())
					{
					$ruleslog->Print("Excluded: $file\: File is export restricted");
					$files->ExcludeFile($file);
					}
				elsif ($policy->Category() =~ /^[DEFG]$/i)
					{
					my @im = $docstats->GetFileAccess($sourcefile);
					if ((scalar(@im) == 0) || (scalar(grep(/publishedAll/, @im))>=1))
						{
						$ruleslog->Print("Included: $file\: File has publishedAll IM (or no IM)");
						$files->IncludeFile($file);
						$self->shipIncludedFiles($file, $includer, $files, \@APIfiles, $ruleslog);
						}
					else
						{
						$ruleslog->Print("Excluded: $file\: File only has IM of ".join(", ",@im)." (pending)");
						}
					}
				elsif ($policy->Category() =~ /^[ABC]$/i)
					{
					$ruleslog->Print("Excluded: $file\: File is IPR type A, B, C");
					$files->ExcludeFile($file);
					}
				else
					{
					$ruleslog->Print("Excluded: $file\: File is IPR type X (pending)");
					}
				}
			}
		elsif (($file =~ /\.lib$/i) || ($file =~ /\.pdb$/i))
			{
			if (lc(basename($file)) eq lc(basename($libsource->FindTarget($file))))
				{
				# File was a static library (or otherwise explicit target)
				$files->IncludeFile($file);
				$ruleslog->Print("Included: $file\: File is an explicit target");
				}
			else
				{
				my $sources = $libsource->GetLibSource($file);

				if (defined($sources))
					{
					# File was a link library or pdb
					my %ims;
					foreach my $sourcefile (@$sources)
						{
						my @im = $docstats->GetFileAccess($sourcefile);
						$ims{$_}="null" foreach (@im);
						}

					if (scalar(grep(/publishedAll/, keys(%ims)))>=1)
						{
						$files->IncludeFile($file);
						$ruleslog->Print("Included: $file\: File has publishedAll IM");
						}
					else
						{
						if (scalar(keys(%ims)) > 0)
							{
							$ruleslog->Print("Excluded: $file\: File only has im of ".join(", ",keys(%ims))." (pending)");
							}
						else
							{
							$ruleslog->Print("Excluded: $file\: File has no API items (pending)");
							}
						}
					}
				else
					{
					# File not originating from an identified target
					$files->IncludeFile($file);
					$ruleslog->Print("Included: $file\: Does not originate from an identified target");
					}
				}
			}
		else
			{
			$logger->Die("Internal error: Don't know how to filter API item '$file'");
			}
		}

	# Fix all non included files
	$ruleslog->Print("Excluded: Fixing all pending exclusions");
	foreach my $fileid ($filecats->ApiFiles)
		{
		my $file = $filelistobj->LookupFile($fileid);

		if (!($files->IsIncluded($file)))
			{
			$files->ExcludeFile($file);
			}
		else
			{
			if (!$files->IsExcluded($file))
				{
				$self->UserFilterer($files,$file,$groupname,$ruleslog,$userGroupFilters);
				}
			}
		}

	# Check for documented APIs in excluded files
	foreach my $fileid ($filecats->ApiFiles)
		{
		my $file = $filelistobj->LookupFile($fileid);

		if ($file =~ /epoc32[\/\\]include[\/\\]/i && !($files->IsIncluded($file)))
			{
			$file =~ s!/!\\!g;
			my $sourcefile = $exportInfo->GetSourcePath($file);
			if (defined $sourcefile)
				{
				my @im = $docstats->GetFileAccess($sourcefile);
				if (scalar(grep(/publishedAll/, @im))>=1)
					{
					$logger->Warning("Excluded file $file contains documented APIs.");
					}
				}
			}

		}

	# Perform filtering
	$logger->Component("Filtering source");
	$ruleslog->Component("Filtering source");
	$groupname = $filecats->SourceGroupName();
	$userGroupFilters = $userFilter->GetGroupFilters($groupname);
	foreach my $fileid ($filecats->SourceFiles())
		{
		my $file = $filelistobj->LookupFile($fileid);
		my $policy = $distpolreader->ReadPolicyFile($file);

		if ($policy->ExportRestricted())
			{
			$ruleslog->Print("Excluded: $file\: File is export restricted");
			$files->ExcludeFile($file);
			}
		elsif ($policy->Category() =~ /^[ABCDEX]$/i)
			{
			$ruleslog->Print("Excluded: $file\: File is not IPR Type F or G");
			$files->ExcludeFile($file);
			}
		elsif (!$files->IsExcluded($file))
			{
			if (!$self->UserFilterer($files,$file,$groupname,$ruleslog,$userGroupFilters))
				{
				$ruleslog->Print("Included: $file\: File is IPR Type F or G");
				$files->IncludeFile($file);
				}
			}
		}

	# Perform filtering
	$logger->Component("Filtering examples");
	$ruleslog->Component("Filtering examples");
	$groupname = $filecats->DocumentationGroupName();
	$userGroupFilters = $userFilter->GetGroupFilters($groupname);
	foreach my $fileid ($filecats->DocumentationFiles())
		{
		my $file = $filelistobj->LookupFile($fileid);
		my $policy = $distpolreader->ReadPolicyFile($file);

		if ($policy->ExportRestricted())
			{
			$ruleslog->Print("Excluded: $file\: File is export restricted");
			$files->ExcludeFile($file);
			}
	 	elsif ($policy->Category() =~ /^[ABCDE]$/i)
			{
			# Is neither cat F/G example, or documentation (cat X)
			$ruleslog->Print("Excluded: $file\: File is not IPR type F or G");
			$files->ExcludeFile($file);
			}
		elsif (!$files->IsExcluded($file))
			{
			if(!$self->UserFilterer($files,$file,$groupname,$ruleslog,$userGroupFilters))
				{
				$ruleslog->Print("Included: $file\: File is type F or G");
				$files->IncludeFile($file);
				}
			}
		}

	# Perform filtering
	$logger->Component("Filtering non-OS files");
	$ruleslog->Component("Filtering non-OS files");
	$groupname = $filecats->NonOsGroupName();
	$userGroupFilters = $userFilter->GetGroupFilters($groupname);
	foreach my $fileid ($filecats->NonOsFiles())
		{
		my $file = $filelistobj->LookupFile($fileid);

		my $sourcefile = $exportInfo->GetSourcePath($file);
		my $exportrestricted = 0;

		if (defined $sourcefile)
			{
			# Has been exported
			my $policy = $distpolreader->ReadPolicyFile($sourcefile);

			if ($policy->ExportRestricted())
				{
				$exportrestricted = 1;
				}
			}

		if ($exportrestricted)
			{
			$ruleslog->Print("Excluded: $file\: File is export restricted");
			$files->ExcludeFile($file);
			}
		elsif (!$files->IsExcluded($file))
			{
			if(!$self->UserFilterer($files,$file,$groupname,$ruleslog,$userGroupFilters))
				{
				$ruleslog->Print("Included: $file\: Non-OS file");
				$files->IncludeFile($file);
				}
			}
		}

	# Perform filtering
	$logger->Component("Filtering other binaries");
	$ruleslog->Component("Filtering other binaries");
	$groupname = $filecats->OtherGroupName();
	$userGroupFilters = $userFilter->GetGroupFilters($groupname);
	foreach my $fileid ($filecats->OtherFiles())
		{
		my $file = $filelistobj->LookupFile($fileid);

		my $sourcefile = $exportInfo->GetSourcePath($file);
		my $exportrestricted = 0;

		if (defined $sourcefile)
			{
			# Has been exported
			my $policy = $distpolreader->ReadPolicyFile($sourcefile);

			if ($policy->ExportRestricted())
				{
				$exportrestricted = 1;
				}
			}

		if ($exportrestricted)
			{
			$ruleslog->Print("Excluded: $file\: File is export restricted");
			$files->ExcludeFile($file);
			}
		elsif ($file =~ /epoc32[\/\\]release[\/\\].*STRONG_CRYPTOGRAPHY\./i)
			{
			$ruleslog->Print("Excluded: $file\: File is export restricted");
			$files->ExcludeFile($file);
			}
		elsif (!$files->IsExcluded($file))
			{
			if (!$self->UserFilterer($files,$file,$groupname,$ruleslog,$userGroupFilters))
				{
				$ruleslog->Print("Included: $file\: Non-filtered binary");
				$files->IncludeFile($file);
				}
			}
		}

	foreach my $file ($files->GetUnfilteredFiles())
		{
		$logger->Print("ERROR: Internal error: $file was unfiltered\n");
		}

	$logger->PhaseEnd();
	$ruleslog->PhaseEnd();

	return $files;
	}

# private getBldInfs(Symbian::Logger $logger, String $sourceLocation, ListRef $configs)
#
# Returns: A list of all bld.infs, read from the system definition
# Parameters:
#   $logger - The logger object where any errors are recorded
#   $sourceLocation - The path to the source containing the system definition
#   $configs - The list of configs to read from the system definition
#
# Loads in the specified configs from the system definition and
sub getBldInfs($$$)
	{
	my $self=shift;
	my ($logger, $sourceLocation, $configs) = @_;
	my $sdf = $sourceLocation . "/common/generic/tools/build/System_Definition.xml";

	# Load system definition
	my @groupdirs;
	foreach my $config (@$configs)
		{
		my $sysdef = Symbian::SystemDefinition::SysDefCollector->new($config,STDOUT);
		my $parser = Symbian::SystemDefinition::SysDefParser->new(-client => $sysdef->parserClient());
		open $sysdeffile, $sdf or $logger->Die("ERROR: Couldn't locate System Definition in release source, '$sdf', '$!'");
		$parser->parse($sysdeffile);

		# Get list of bld.inf files
		push @groupdirs, map($_->[1], $sysdef->components());
		}

	return map(File::Spec->catdir($_,"bld.inf"), @groupdirs);
	}

# private shipIncludedFiles(String $file, Symbian::SourceInfo $includer, Symbian::SDK::FilterTool::FilterFileList $files, Symbian::Logger $logger)
#
# Returns: None
# Parameters:
#   $file - name of included file to check for #includes
#   $includer - An initialised SourceInfo object to list the #includes
#   $files - the FilterFileList to record the inclusions made
#   \@APIfiles - A listref to a list of the API files that could be included
#   $logger - the log file to record the decisions
#
# Recursively scans a file to include any files #included by the file
sub shipIncludedFiles($$$$$$)
	{
	my $self = shift;
	my ($file, $includer, $files, $APIfiles, $log) = @_;

	foreach my $include (@{$includer->GetIncludes($file)})
		{
		foreach my $fullinclude (grep(/[\/\\]\Q$include\E$/i, @$APIfiles))
			{
			if ($files->IncludeFile($fullinclude))
				{
				$log->Print("Included: $fullinclude\: File is included by $file");
				$self->shipIncludedFiles($fullinclude, $includer, $files, $APIfiles, $log);
				}
			}
		}
	}

# private UserFilterer(Symbian::SDK::FilterTool::FilterFileList $files, String $file, $options, String $group, Symbian::Logger $logger)
#
# Returns: Boolean : 1 if the file is filtered, 0 if not.
# Parameters:
#	 $files - the FilterFileList
#	 $file - name of the file to be filtered
#	 $group - group name
#	 $ruleslog - rules logger
#	 @filters - list of the user filters for that group
#
sub UserFilterer
	{
	my $self = shift;
	my ($files,$file,$group,$ruleslog,$filters) = @_;
	my $filtered = 0;
	foreach my $filter (@{$filters})
		{
		my $regexp = (keys %{$filter})[0];
		my $operation = $filter->{$regexp};
		if ($file =~ /$regexp/i)
			{
			if($operation eq 'include')
				{
				if($files->IncludeFile($file))
					{
					$ruleslog->Print("Included: $file : $group : Matched User Filter: $regexp");
					}
				}
			else
				{
				if($files->ExcludeFile($file))
					{
					$ruleslog->Print("Excluded: $file : $group : Matched User Filter: $regexp");
					}
				}
			$filtered =1;
			last;
			}
		}
	return $filtered;
	}

1;
