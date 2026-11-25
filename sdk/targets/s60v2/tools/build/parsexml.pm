# Copyright (c) 2003 Symbian Ltd. All rights reserved

package ParseXML;

use strict;
use Carp;
use XML::Parser;

# Variables
my ($gEnvStart) = -1;
my ($gDataSource);

# ParseXMLData
#
# Inputs
# $iDataSource (XML Command file)
#
# Outputs
#
# Description
# This function Parses the XML file into a Hash for access by the main command loop
sub ParseXMLData
{
  my ($iDataSource) = @_;

  eval { $ParseXML::gDataSource = File::Spec->rel2abs($iDataSource); };

  my ($iParser);
  # Create a new XML Parser
  $iParser = new XML::Parser(Style=>'Subs', Pkg=>'SubHandlers', ErrorContext => 2);
  # Supply the XML Parser the data source
  $iParser->parsefile($iDataSource);
}

# SetEnvStart
#
# Inputs
# $iNum (Number to set the variable)
#
# Outputs
#
# Description
# This function Sets the EnvStart Number
sub SetEnvStart
{
  my ($iNum) = @_;
  $gEnvStart = $iNum;
}

# GetEnvStart
#
# Inputs
#
# Outputs
# $gEnvStart
#
# Description
# This function return the EnvStart Number
sub GetEnvStart
{
  return $gEnvStart;
}

package SubHandlers;
use FreezeThaw qw(freeze thaw);

# Execute
#
# Inputs
#
# Outputs
#
# Description
# This function handles the Execute tag in the XML
sub Execute
{
  my $iExpat = shift; my $iElement = shift;

  # Do nothing if only the SetEnv Tags are to be processed
  return 0 if (&ParseXML::GetEnvStart == -1);

  my (%iAttr);

  # Read the attributes
  while (@_) {
    my $iAtt = shift;
    my $iVal = shift;
    $iAttr{$iAtt} = $iVal;
  }

  my $iID  = $iAttr{'ID'};
  my $iStage = $iAttr{'Stage'};
  my $iComp = $iAttr{'Component'};
  my $iCwd = $iAttr{'Cwd'};
  my $iCommandLine = $iAttr{'CommandLine'};

  # Replace the magic words with values in the commandline
  if ($ParseXML::gDataSource) {
    $iCommandLine =~ s/%%%this_file%%%/$ParseXML::gDataSource/g;
  } else {
    $iCommandLine =~ s/%%%this_file%%%/this_file/g;
  }

  # Replace the server side environment variables with values in the commandline
  $iCommandLine =~ s/%%(\w+)%%/$ENV{$1}/g;

  # Freeze the data ready to be sent to the client
  $BuildServer::Commands{$iID}{$iStage} = freeze($iElement, $iID, $iStage, $iComp, $iCwd, $iCommandLine);
}

# Product
#
# Inputs
#
# Outputs
#
# Description
# This function handles the Product tag in the XML
sub Product
{
  my $iExpat = shift; my $iElement = shift;

  # Do nothing if only the SetEnv Tags are to be processed
  return 0 if (&ParseXML::GetEnvStart == -1);

  my (%iAttr);

  # Read the attributes
  while (@_) {
    my $iAtt = shift;
    my $iVal = shift;
    $iAttr{$iAtt} = $iVal;
  }

  my $iName  = $iAttr{'Name'};

  print "$iElement = $iName\n";
}

# SetEnv
#
# Inputs
#
# Outputs
#
# Description
# This function handles the SetEnv tag in the XML
sub SetEnv
{
  my $iExpat = shift; my $iElement = shift;

  my (%iAttr);

  # Read the attributes
  while (@_) {
    my $iAtt = shift;
    my $iVal = shift;
    $iAttr{$iAtt} = $iVal;
  }

  # If Process a sencond file $gSetEnv will be non zero
  my $iOrder;
  if (&ParseXML::GetEnvStart >= 0)
  {
    $iOrder  = &ParseXML::GetEnvStart + $iAttr{'Order'};
  } else {
    $iOrder  = $iAttr{'Order'};
  }

  my $iName  = $iAttr{'Name'};
  my $iValue = $iAttr{'Value'};

  # Freeze the data ready to be sent to the client
  $BuildServer::SetEnv{$iOrder} = freeze("SetEnv", $iName, $iValue);
}
1;
