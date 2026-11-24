# CHECKSOURCE.PM
#
# Copyright (c) 2005 Symbian Software Ltd.  All rights reserved.
#

# Routines involved in checking that source matches Symbian's filename policy


package CheckSource;

require Exporter;
@ISA=qw(Exporter);

@EXPORT=qw(
	CheckSource_CaseAndDelimiter
	CheckSource_Includes
	CheckSource_ExportedFileIncludes
);

use Cwd;
use Pathutl;

my $warningTitle = "Incorrect ";
my $warningPrefix = "\@echo ";

my $checksourceCall = "\@perl -S checksource.pl";

sub CheckSource_CaseAndDelimiter($$$\%;$)
	{
	my ($sourceFile, $text, $lineNumber, $warningHash, $noEcho) = @_;
	my ($case, $delimiter) = 0;

	$case = 1 if ($text =~ /[A-Z]/);
	$delimiter = 1 if ($text =~/\\/);

	return "." if (!$case && !$delimiter);

	$sourceFile =~ s/\//\\/g;
	$sourceFile =~ s/^[a-zA-Z]{1}://;
	$sourceFile = &Path_Strip ($sourceFile);

	my $warning;
	$warning .= $warningPrefix unless $noEcho;
	$warning .= $sourceFile.":".$lineNumber.": ".$warningTitle;

	if ($case)
		{
		$warning.="Case";
		}

	if ($delimiter)
		{
		$warning.=" and " if ($case);
		$warning.="Path Delimiter"
		}

	$warning.=" \'".$text."\'.";

	# Escape any '&' chars - DOS echo doesn't like these
	$warning =~ s/\&/\^\&/g;

#	print ("$warning\n");

	$$warningHash{$warning} = 1;
	}

sub CheckSource_Includes ($\%$\@;\@;\@)
	{
	# References are used for array arguments only so
	# that they can be distinguished within the subroutine
	my ($sourceFile, $commandHash, $preInclude, $macros, $userIncludesRef, $systemIncludesRef) = @_;
	my (@userIncludes, @systemIncludes);

	@userIncludes = @$userIncludesRef if ($userIncludesRef);
	@systemIncludes = @$systemIncludesRef if ($systemIncludesRef);

	my $call = "$checksourceCall --preprocess -- ";

	if (($sourceFile !~ /\.inf$/i) && ($sourceFile !~ /\.mmp/i))
		{
		push @$macros, "__SUPPORT_CPP_EXCEPTIONS__";
		}

	my $platformPreInclude = "";

	foreach my $macro (@$macros)
		{
		$call .= "-D$macro ";

		if ($macro =~ /__ARMCC_2_2__/)
			{
			$platformPreInclude = $ENV{EPOCROOT}."epoc32\\include\\rvct2_2\\rvct2_2.h";

			if (($sourceFile =~ /BASE\\E32\\compsupp\\/i) && $ENV{RVCT22INC})
				{					
				# Need some way to deal with ARMINC from the front-end...
				my $rvctIncDir = $ENV{RVCT22INC};
				push @systemIncludes, $rvctIncDir;
				}
			}
		elsif ($macro =~ /__GCCE__/)
			{
			$platformPreInclude = $ENV{EPOCROOT}."epoc32\\include\\GCCE\\GCCE.h";

			my $GCCEinstall = Cl_bpabi::GCCInstallPath();
			push @systemIncludes, "\"\\\"$GCCEinstall\\..\\lib\\gcc\\arm-none-symbianelf\\3.4.3\\include\\\"\"";
			}
# Unsupported, at least for now...
#
#		elsif ($macro =~/__WINSCW__/)
#			{
#			my $CWInstall = $ENV{MWCSYM2INCLUDES};
#			$CWInstall =~ s/^\+//;
#			$CWInstall =~ s/\;$//;
#			push @systemIncludes, "\"\\\"$CWInstall\\Win32-x86 Support\\Headers\\Win32 SDK\\\"\"";
#			push @systemIncludes, "\"\\\"$CWInstall\\MSL\\MSL_CPP\\MSL_Common\\include\\\"\"";
#			push @systemIncludes, "\"\\\"$CWInstall\\MSL\\MSL_C\\MSL_Common\\include\\\"\"";
#			}
		}

	if ($preInclude ne "")
		{
		$call .= "-include ".getDrive().$preInclude." ";
		}		

	if ($platformPreInclude ne "")
		{
		$call .= "-include ".getDrive().$platformPreInclude." ";
		}	

	foreach my $include (@userIncludes, @systemIncludes)
		{
		$include =~ s/\\$//;
		$include = getDrive().$include if (($include !~ /^[a-zA-Z]:/) && ($include !~ /^\"/));
		$call .= "-I $include ";
		}

	$sourceFile =~ s/\//\\/g;
	$sourceFile = &Path_Strip ($sourceFile);
	$sourceFile = getDrive().$sourceFile;

	$call .= $sourceFile;

#	print ("CPP : $call\n");

	$$commandHash{$call} = 1;

	return $call;
	}


sub CheckSource_ExportedFileIncludes ($$\%)
	{
	my ($sourceFile, $destinationFile, $commandHash) = @_;

	# Exclude exported files as appropriate
	if ($destinationFile)
		{
		my $epoc32Include = quotemeta ($ENV{EPOCROOT})."epoc32\\\\include";
		return if ($destinationFile !~ /^$epoc32Include/i);
		return if ($destinationFile =~ /\.def$/i);
		}

	$$commandHash{"$checksourceCall --parsefile -- $sourceFile"} = 1;
	}


sub getDrive
	{
    if(cwd =~ /^([a-zA-Z]:)/)
    	{
		return $1;
    	}

	return "";
	}

1;
