#!perl
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# SdkContent - Module to create SdkContent object that correspond to a/aggregate of content definition xml file(s)
#

package Symbian::SDK::SdkContent;
use strict;

use Symbian::SDK::ContentDefinitionFile::SdkComponent;
use Symbian::SDK::ContentDefinitionFile::SdkFile;
use Symbian::SDK::ContentDefinitionFile::SdkMetaData;
use Symbian::SDK::ContentDefinitionFile::SdkCustomPage;
use Symbian::SDK::ContentDefinitionFile::SdkWriteIni;
use Symbian::SDK::ContentDefinitionFile::SdkWriteReg;
use Symbian::SDK::ContentDefinitionFile::SdkStartMenu;
use Symbian::SDK::ContentDefinitionFile::SdkExecute;
use Symbian::Logger::Singleton;
use integer;
use XML::Simple;
use File::Basename;
use File::Spec::Functions;
use Cwd 'abs_path';

# New() : create a new SdkContent object
#
# Parameters:
#   - content definition xml file
#   - rootpath : location of the source files
#   - order : group order to start with if not defined in the xml group elements
# Returns:
#   - the newly created SdkContent object reference
sub New 
	{

	# convert components definitions xml file into SdkContent object
	my $pkg = shift;
	my $self = {};
	$self->{logger} = Symbian::Logger::Singleton->new();
	bless $self, $pkg;
	my $sdk_content_definition_file = shift;
	my $rootPath = shift;
	my $gorder = shift;
	$gorder = 0 if ! defined $gorder;
	if (defined $sdk_content_definition_file)
		{
		$self->{logger}->Print("Reading content definition file $sdk_content_definition_file\n") if $self->{logger}->Debug();

		# create SdkContent from xml
		$self->{logger}->Die("Content definition file $sdk_content_definition_file does not exist") if (! -e $sdk_content_definition_file);
		my $xs1 = XML::Simple->new();

		# read the xml file, switch off the [] -> {} feature and force the ones mentioned to []
		my $xml = eval{ $xs1->XMLin($sdk_content_definition_file, suppressempty => 1,
				keyattr => [],
				forcearray=>["group", "file", "execute", "startMenu", "writeIni", "writeReg", "customPage","exclude"])};
		if( $@ )
			{
			$@ =~ s/at (.:|)\/.*?$//s; # remove module line number
			$self->{logger}->Die("ERROR in '$sdk_content_definition_file':\n$@");
			}
		if (exists $xml->{group})
			{
			my $groups = $xml->{group};
			foreach my $group (@$groups)
				{
				my $cleangroup = Symbian::SDK::ContentDefinitionFile::SdkComponent->New(); # new empty component
				# fill the group attributes
				if (exists $group->{order})
					{
					$cleangroup->SdkComponentOrder($group->{order});
					}
				else
					{
					$cleangroup->SdkComponentOrder($gorder++);
					}

				if (exists $group->{name})
					{
					$cleangroup->SdkComponentName($group->{name});
					}

				if (exists $group->{description})
					{
					$cleangroup->SdkComponentDescription($group->{description});
					}

				if (exists $group->{hidden})
					{
					$cleangroup->SdkComponentHidden($group->{hidden});
					}
				if (exists $group->{required})
					{
					$cleangroup->SdkComponentRequired($group->{required});
					}
				if (exists $group->{default})
					{
					$cleangroup->SdkComponentDefault($group->{default});
					}

				if (exists $group->{root})
					{
					$cleangroup->RootPath(Symbian::SDK::Utils::GetFullPath($rootPath,$group->{root}));
					}
				elsif (exists $xml->{root})
					{
					$cleangroup->RootPath(Symbian::SDK::Utils::GetFullPath($rootPath,$xml->{root}));
					}
				elsif (defined $rootPath)
					{
					$cleangroup->RootPath($rootPath);
					}

				if (exists $group->{files})
					{
					my $files = exists $group->{files}->{file} ? $group->{files}->{file} : [] ;
					my $forder = 0; # file order
					foreach my $file (@$files)
						{
						$file->{logger} = $self->{logger};
						bless $file,"Symbian::SDK::ContentDefinitionFile::SdkFile";
						if (!exists $file->{order})
							{
							$file->SdkFileOrder($forder++);
							}
						$cleangroup->AddComponentFile($file);
						}
					}
				my $metadata = exists $group->{metadata} ? $group->{metadata} : {};
				my $cleanmeta = Symbian::SDK::ContentDefinitionFile::SdkMetaData->New();
				my $custompages = exists $metadata->{customPage} ? $metadata->{customPage} : [];
				my $corder = 0;
				foreach my $custom (@$custompages)
					{
					$custom->{logger} = $self->{logger};
					bless $custom,"Symbian::SDK::ContentDefinitionFile::SdkCustomPage";
					if (!exists $custom->{order})
						{
						$custom->CustomPageOrder($corder++);
						}
					$cleanmeta->AddCustomPage($custom);
					}

				my $executes = exists $metadata->{execute} ? $metadata->{execute} : [];
				foreach my $execute (@$executes)
					{
					$execute->{logger} = $self->{logger};
					bless $execute, "Symbian::SDK::ContentDefinitionFile::SdkExecute";
					$cleanmeta->AddExecute($execute);
					}

				my $writeinis = exists $metadata->{writeIni} ? $metadata->{writeIni} : [];
				foreach my $writeini (@$writeinis)
					{
					$writeini->{logger} = $self->{logger};
					bless $writeini,"Symbian::SDK::ContentDefinitionFile::SdkWriteIni";
					$cleanmeta->AddWriteIni($writeini);
					}

				my $writeregs = exists $metadata->{writeReg} ? $metadata->{writeReg} : [];
				foreach my $writereg (@$writeregs)
					{
					$writereg->{logger} = $self->{logger};
					bless $writereg,"Symbian::SDK::ContentDefinitionFile::SdkWriteReg";
					$cleanmeta->AddWriteReg($writereg);
					}

				my $startmenus = exists $metadata->{startMenu} ? $metadata->{startMenu} : [];
				foreach my $startmenu (@$startmenus)
					{
					$startmenu->{logger} = $self->{logger};
					bless $startmenu, "Symbian::SDK::ContentDefinitionFile::SdkStartMenu";
					$cleanmeta->AddStartMenu($startmenu);
					}
				$cleangroup->SdkComponentMetaData($cleanmeta);
				$self->AddSDKComponent($cleangroup);
				}
			}
		}
	return $self;
	}

# addContentDefinitionFile() : add a content definition file to the existing list
#
# Parameters:
#   - content definition file name
# Returns:
#   - 1 success, 0 fail
sub AddContentDefinitionFile
	{
	my $self = shift;
	my $cdf = shift;
	if (! exists $self->{content_definition})
		{
		$self->{content_definition}->[0] = $cdf;
		}
	else
		{
		my $cdfidx = -1;
		while (defined $self->{content_definition}->[++$cdfidx])
			{
			return 0 if (lc($self->{content_definition}->[$cdfidx]) eq lc($cdf));
			}
		$self->{content_definition}->[$cdfidx] = $cdf;
		}
	return 1;
	}

# getContentDefinitionFiles() : get the existing list of content definition files
#
# Parameters:
#   - none
# Returns:
#   - array of the existing content definition files
sub GetContentDefinitionFiles
	{
	my $self=shift;
	return exists $self->{content_definition} ? $self->{content_definition} : undef;
	}

# validateContent() : validate the content of the current object
#
# Parameters:
#   - force : force re-validation
# Returns:
#   - none
sub ValidateContent
	{
	my $self = shift;
	my $force = shift;
	foreach my $gkey (keys (%{$self->{group}}))
		{
		if (! $self->{group}->{$gkey}->ValidateComponent($force))
			{
			$self->{logger}->Error($self->{group}->{$gkey}->SdkComponentName() . " : Component is not valid, therefore excluded\n\n");
			}
		}
	}

# RootPath() : set/get rootpath
#
# Parameters:
#   - rootpath
# Returns:
#   - rootpath
sub RootPath
	{
	my $self = shift;
	my $newval = shift;
	$self->{rootpath}->{path} = $newval if defined $newval;
	return $self->{rootpath}->{path};
	}

# getSDKComponents() : get a hash containing the list the existing SdkComponents keyed on their orders
#
# Parameters:
#   - none
# Returns:
#   - hash containing the list the existing SdkComponents keyed on their orders
sub GetSDKComponents
	{
	my $self = shift;
	return $self->{group};
	}

# getSDKComponentsList() : get the list of names of the existing SdkComponent objects
#
# Parameters:
#   - none
# Returns:
#   - array containing the list of components names
sub GetSDKComponentsList
	{
	my $self = shift;
	my @returnlist=();
	foreach my $gkey (keys (%{$self->{group}}))
		{
		push @returnlist, $self->{group}->$gkey->SdkComponentName();
		}
	return @returnlist;
	}

# getSDKComponent() : get a SdkComponent object (by name)
#
# Parameters:
#   - name
# Returns:
#   - a SdkComponent object reference
sub GetSDKComponent
	{
	my $self = shift;
	my $comp = shift;
	my $retcomp = undef;
	foreach my $gkey (keys (%{$self->{group}}))
		{
		if ($self->{group}->$gkey->SdkComponentName() =~ /$comp$/i)
			{
			$retcomp = $self->{group}->{$gkey};
			last;
			}
		}
	return $retcomp;
	}

# addSDKComponent() : add a SdkComponent object
#
# Parameters:
#   - SdkComponent object
# Returns:
#   - 1 success - 0 fail
sub AddSDKComponent
	{
	my $self = shift;
	my $comp = shift;
	my $gorder = $comp->SdkComponentOrder();
	if (exists $self->{group}->{$gorder})
		{
		$self->{logger}->Error("Can not add component " . $comp->SdkComponentName() . " Order = ".$gorder. " : Order already used by another component");
		return 0;
		}
	else
		{
		foreach my $gkey (keys (%{$self->{group}}))
			{
			my $name = $comp->SdkComponentName();
			if ($self->{group}->{$gkey}->SdkComponentName() =~ /$name$/i)
				{
				$self->{logger}->Error("Can not add component " . $comp->SdkComponentName() . " Order = ".$gorder. " : name already used by another component");
				return 0;
				}
			}

		}
	$self->{group}->{$gorder} = $comp;
	return 1;
	}

# removeSDKComponent() :  remove all SdkComponent objects (by name)
#
# Parameters:
#   - name
# Returns:
#   - 1 success - 0 fail
sub RemoveSDKComponentByName
	{
	my $self = shift;
	my $name = shift;
	my $success = 0;
	foreach my $gkey (keys (%{$self->{group}}))
		{
		if ($self->{group}->{$gkey}->SdkComponentName() =~ /$name$/i)
			{
			delete ($self->{group}->{$gkey});
			$success = 1;
			}
		}
	return $success
	}

1;

__END__

sub New
sub ValidateContent
sub AddContentDefinitionFile
sub GetContentDefinitionFiles
sub RootPath
sub GetSDKComponents
sub GetSDKComponentsList
sub GetSDKComponent
sub AddSDKComponent
sub RemoveSDKComponentByName
