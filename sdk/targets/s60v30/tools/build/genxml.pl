# Copyright (c) 2003 Symbian Ltd. All rights reserved

# Script to Generate the XML command file from the xml files

use strict;
use FindBin;		# for FindBin::Bin
use Getopt::Long;
use File::Copy;

use lib $FindBin::Bin;
use lib "$FindBin::Bin/lib";

# Process the commandline
my ($iDataSource, $iDataOutput, $iLogFile, $iSourceDir, $iReallyClean, $iClean, $iXmlSource, $iConfName, $iMergedXml, $iValidate) = ProcessCommandLine();

if (scalar(@$iXmlSource))
{
	use GenXml;
	&GenXml::Start($iXmlSource, $iDataOutput, $iLogFile, $iSourceDir, $iConfName, $iMergedXml, $iValidate);
} else {
	use GenBuild;
	# Start the generation of the XML
  print "Warning old .txt file input is being used\n";
	&GenBuild::Start($iDataSource, $iDataOutput, $iLogFile, $iSourceDir, $iReallyClean, $iClean);
}


# ProcessCommandLine
#
# Inputs
#
# Outputs
# @iDataSource array of multiple (txt file(s) to process)
# @iXmlSource array of multiple (XML file(s) to process)
# $iDataOutput (XML file to generate)
# $iLogFile (Log file to put processing errors)
# $iSourceDir (Location of Source)
# $iMergedXml - Hidden option to save the output of the merging xml process for debug use
#
# Description
# This function processes the commandline

sub ProcessCommandLine {
  my ($iHelp, $iPort, @iDataSource, $iLogFile, $iSourceDir, $iReallyClean, $iClean, @iXmlSource, $iConfName, $iMergedXml, $iValidate);
  GetOptions('h' => \$iHelp, 'd=s@' =>\@iDataSource, 'o=s' => \$iDataOutput, 'l=s' => \$iLogFile, 's=s' => \$iSourceDir, 'r=s' => \$iReallyClean, 'c=s' => \$iClean , 'x=s@' =>\@iXmlSource, 'n=s' => \$iConfName, 'm=s' => \$iMergedXml, 'v' =>\$iValidate);

  if (($iHelp) || (!defined $iDataOutput) || (!defined $iLogFile) || (!defined $iSourceDir) || ((!@iDataSource) && (!@iXmlSource)))
  {
    Usage();
  }
  &backupFile($iDataOutput) if (-e $iDataOutput);
  &backupFile($iLogFile) if (-e $iLogFile);
  &backupFile($iMergedXml) if (-e $iMergedXml);
	
  die "$iSourceDir is not a directory" if (!-d $iSourceDir);

  &backupFile($iReallyClean) if (-e $iReallyClean);
  &backupFile($iClean) if (-e $iClean);

  foreach my $iFile (@iDataSource)
  {
    if (! -e $iFile)
    {
      die "Cannot open $iFile";
    }
  }

  foreach my $iFile (@iXmlSource)
  {
    if (! -e $iFile)
    {
      die "Cannot open $iFile";
    }
  }

  return(\@iDataSource, $iDataOutput, $iLogFile, $iSourceDir, $iReallyClean, $iClean, \@iXmlSource, $iConfName, $iMergedXml, $iValidate);
}

# backupFile
#
# Inputs
# $iFile - filename to backup
#
# Outputs
#
# Description
# This function renames a file with the .baknn extension
sub backupFile
{
	my ($iFile) = @_;
	
	my ($iBak) = $iFile.".bak";
	my ($i, $freefilename);
	# Loop until you find a free file name by increamenting the number on the end of the .bak extension
	while (!$freefilename)
	{
		if (-e $iBak.$i)
		{
			$i++;
		} else {
			$iBak .= $i;
			$freefilename = 1;
		}
	}
	print "WARNING: $iFile already exists, creating backup of original with new name of $iBak\n";
	move($iFile,$iBak) or die "Could not backup $iFile to $iBak because of: $!\n";
}

# Usage
#
# Output Usage Information.
#

sub Usage {
  print <<USAGE_EOF;

  Usage: Genxml.pl [options]

  options:

  -h  help
  -x  XML Data Source (XML file) [Multiple -x options allowed]
  -n  Configuration name to use
  -s  Source Directory
  -o  Output XML file
  -l  Logfile
  -v  Validate XML files only, Stop after merging and validating.
      Turns on extra INFO messages for Validation [optional]

  options for backward compatibility:

  -d  Data Source (txt file) [Multiple -d options allowed]
  -r  Filename for ReallyClean xml file [optional]
  -c  Filename for Clean xml file [optional]

  These options will be ignored if the -x options is used

  Description:
  This program generates an XML file that is used by the Build
  Client-Server System. It expands the summarised configuration
  information stored in the input files to a detailed command by command
  instruction set for the Build System to use. This enabled the
  specified configuration to be built by the build system.

USAGE_EOF
  exit 1;
}
