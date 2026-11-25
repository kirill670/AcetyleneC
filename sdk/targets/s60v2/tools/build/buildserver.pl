# Copyright (c) 2003 Symbian Ltd. All rights reserved

# Script to send commands to 1 or more Build Clients to perform parallel builds

use strict;
use FindBin;		# for FindBin::Bin
use Getopt::Long;
use File::Copy;

# Add the directory contain this perl script into the path to find modules
use lib $FindBin::Bin;

use BuildServer;
use ParseXML;

# Turn on per command Buffering of STDOUT, so the log files are not so far behind what is actually happening
$| = 1;

# Process the commandline
my ($iDataSource, $iPort, $iLogFile, $iEnvSource) = ProcessCommandLine();

# Create socket to server
&BuildServer::Start($iDataSource, $iPort, $iLogFile, $iEnvSource);


# ProcessCommandLine
#
# Inputs
#
# Outputs
# $iPort (Port to listen on for Build Clients)
#
# Description
# This function processes the commandline

sub ProcessCommandLine {
  my ($iHelp, $iPort, $iDataSource, $iLogFile, $iEnvSource);
  GetOptions('h' => \$iHelp, 'd=s' =>\$iDataSource, 'p=i' => \$iPort, 'l=s' => \$iLogFile, 'e=s' =>\$iEnvSource);

  if (($iHelp) || (!defined $iPort) || (!defined $iDataSource) || (!defined $iLogFile))
  {
    Usage();
  } elsif (! -e $iDataSource) {
    die "Cannot open $iDataSource";
  }
	if ((defined $iEnvSource) && (! -e $iEnvSource))
	{
    die "Cannot open $iEnvSource";
  }
	
  &backupFile($iLogFile) if (-e $iLogFile);
  
	return($iDataSource,$iPort,$iLogFile, $iEnvSource);
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
	print "WARNING: $iFile already exists, creating backup of orignal with new name of $iBak\n";
	move($iFile,$iBak) or die "Could not backup $iFile to $iBak because of: $!\n";
}

# Usage
#
# Output Usage Information.
#

sub Usage {
  print <<USAGE_EOF;

  Usage: BuildServer.pl [options]

USAGE_EOF
print "  Version: ".&BuildServer::GetServerVersion()."\n";
print <<USAGE_EOF;

  options:

  -h  help
  -p  Port number to listen on for Build Clients
  -d  Data Source (XML command file)
  -l  Log file for output from commands run on the Build Client
  -e  Use Environment of this data source (XML command file)
      The Environment in the main data source takes precedence
USAGE_EOF
	exit 1;
}
