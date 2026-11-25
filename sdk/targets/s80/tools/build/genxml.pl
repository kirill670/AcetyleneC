# Copyright (c) 2003 Symbian Ltd. All rights reserved

# Script to Generate the XML command file from the txt files like genbuild.pl

use strict;
use FindBin;		# for FindBin::Bin
use Getopt::Long;

use lib $FindBin::Bin;

use GenBuild;
use ParseXML;

# Process the commandline
my ($iDataSource, $iDataOutput, $iLogFile, $iSourceDir, $iReallyClean, $iClean) = ProcessCommandLine();

# Start the generation of the XML
&GenBuild::Start($iDataSource, $iDataOutput, $iLogFile, $iSourceDir, $iReallyClean, $iClean);


# ProcessCommandLine
#
# Inputs
#
# Outputs
# @iDataSource array of multiple (txt file(s) to process)
# $iDataOutput (XML file to generate)
# $iLogFile (Log file to put processing errors)
# $iSourceDir (Location of Source)
#
# Description
# This function processes the commandline

sub ProcessCommandLine {
  my ($iHelp, $iPort, @iDataSource, $iLogFile, $iSourceDir, $iReallyClean, $iClean);
  GetOptions('h' => \$iHelp, 'd=s@' =>\@iDataSource, 'o=s' => \$iDataOutput, 'l=s' => \$iLogFile, 's=s' => \$iSourceDir, 'r=s' => \$iReallyClean, 'c=s' => \$iClean);

  if (($iHelp) || (!defined @iDataSource) || (!defined $iDataOutput) || (!defined $iLogFile) || (!defined $iSourceDir))
  {
    Usage();
  } elsif (-e $iDataOutput) {
    die "$iDataOutput already exists";
  } elsif (-e $iLogFile) {
    die "$iLogFile already exists";
  } elsif (!-d $iSourceDir) {
    die "$iSourceDir is not a directory";
  }
  if (-e $iReallyClean) {
    print "WARNING: Not generating $iReallyClean as it already exists\n";
    undef $iReallyClean;
  }
  if (-e $iClean) {
    print "WARNING: Not generating $iClean as it already exists\n";
    undef $iClean;
  }

  foreach my $iFile (@iDataSource)
  {
    if (! -e $iFile)
    {
      die "Cannot open $iFile";
    }
  }

  return(\@iDataSource, $iDataOutput, $iLogFile, $iSourceDir, $iReallyClean, $iClean);
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
  -d  Data Source (txt file) [Multiple -d options allowed]
  -s  Source Directory
  -o  Output XML file
  -l  Logfile
  -r  Filename for ReallyClean xml file [optional]
  -c  Filename for Clean xml file [optional]
USAGE_EOF
	exit 1;
}
