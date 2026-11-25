# Copyright (c) 2003 Symbian Ltd. All rights reserved

package BuildServer;

use strict;

use FindBin;		# for FindBin::Bin
use lib "$FindBin::Bin/lib/FreezeThaw"; # For FreezeThaw

# Other necessary modules. For "use Scanlog;" see dynamic code below.
use Carp;
use Msg;
use ParseXML;
use FreezeThaw qw(freeze thaw);
use IO::File;
use File::Basename;
use File::Copy;


# Globals
my (%Commands);
my (%SetEnv);
my ($gIDCount) = 1;
my ($gStageCount) = 1;
my (%gEnvOrder);
my ($gClientReadyCount);
my (%gClientStatus);
my (%gClientHandles);
my ($gLogFileH);
my ($gLogStart) = 0;
my ($gRealTimeError) = 0;       # 0 = FALSE (No error) # Windows error code = TRUE
my ($gScanlogAvailable) = 0;

# Check if Scanlog.pm is available.
# In the Perforce order of things, Scanlog.pm is in directory ".\Scanlog" relative to BuildServer.pl
# However, at build time, BuildServer.pl is in "\EPOC32\Tools\Build" while Scanlog.pm is in "\EPOC32\Tools"
# i.e. in the parent directory relative to BuildServer.pl
# If Scanlog cannot be found in either place, we continue, but the Scanlog functionality will be skipped.
if (eval {require Scanlog::Scanlog;})
  {
  $gScanlogAvailable = 1;
  }
elsif (eval {use lib $FindBin::Bin.'/..'; require Scanlog;})
###elsif (eval {require '../Scanlog.pm';})
  {
  $gScanlogAvailable = 1;
  }
else
  {
  print "Cannot load Scanlog Module\n";
  }

# GetServerVersion
#
# Inputs
#
# Outputs
# Server Version Number
#
# Description
# This function returns the server version number
sub GetServerVersion
{
  return "1.0";
}

# rcvd_msg_from_client
#
# Inputs
# $iConn (Instance of the Msg Module)
# $msg (the recieved message from the client)
# $err (any error message from the Msg Module)
#
# Outputs
#
# Description
# This function processes the incoming message from the Build Client and acts upon them
sub rcvd_msg_from_client {
    my ($iConn, $msg, $err) = @_;
    
    # if the message is empty or a "Bad file descriptor" error happens
    # This usually means the the Build Server has closed the socket connection.
    # The client is returned to trying to connect to a build server
    if (($msg eq "") || ($err eq "Bad file descriptor"))
    {
      print "A client has probably Disconnected\n";
      croak "Cannot recover from Error:$err";
    }
    
    # Thaw the message, this decodes the text string sent from the client back into perl variables
    my ($iCommand, $iClientName, $iID, $iStage, $iComp, $iCwd, $iCommandline, $args) = thaw ($msg);
    
    # Process the commands
    if ( $iCommand eq "Ready")
    {
      # Check the Client Version
      if ($iID ne &GetServerVersion)
      {
        die "Client version $iID does not match Server version ".&GetServerVersion.", cannot continue";
      }
      # Handle the initial "Ready" Command from the client
      # Check that the Client name is unique
      if (defined $gClientHandles{$iClientName})
      {
        # The Client name is not unique, a client by this name has already connected
        print "Warning - Multiple Clients using the same name\n";
        print "Adding random number to client name to try and make it unique.";
        print "This will affect the preference order of the Clients\n";
        # Generate a ramdom number to ad to the client name.
        my ($iRNum) = int(rand 10000000);
        $iClientName .= $iRNum;
        print "Changing ClientName to $iClientName\n";
        # Send the new Client name to the client
        $msg = freeze("ChangeClientName", $iClientName);
        $iConn->send_now($msg);
      }
      
      # Add the connection object to the store of connections
      $gClientHandles{$iClientName} = $iConn;
      
      # Send the first Environment Variable
      $gEnvOrder{$iClientName} = 1;    
      $iConn->send_now($BuildServer::SetEnv{$gEnvOrder{$iClientName}});
      # Increment the order number of this client so that it sends the next enviroment varible to be set when a "SetEnv Ready" command is recieved
      $gEnvOrder{$iClientName}++;
      # Start the log headers on first connection
      if ( $BuildServer::gLogStart == 0)
      {
        # The start of the log file only needs to be printed once
        $BuildServer::gLogStart = 1;
        print $BuildServer::gLogFileH "===-------------------------------------------------\n";
        print $BuildServer::gLogFileH "=== Stage=$gStageCount\n";
        print $BuildServer::gLogFileH "===-------------------------------------------------\n";
        print $BuildServer::gLogFileH "=== Stage=$gStageCount started ".localtime()."\n";
        # Flush the handle to try and make sure the logfile is up to date
        $BuildServer::gLogFileH->flush;
      }
    }

    # Handle the "SetEnv Ready" command
    if ( $iCommand eq "SetEnv Ready")
    {
      # If there is another environment variable to set, send the command to the client to set it
      if (defined $BuildServer::SetEnv{$gEnvOrder{$iClientName}})
      {
        $iConn->send_now($BuildServer::SetEnv{$gEnvOrder{$iClientName}});
        $gEnvOrder{$iClientName}++;
      } else {
        # All the actions that all the client need to do have been done
        # Add this client to the list of client ready to process commands
        AddReady($iClientName,$iConn);
      }
    }
    
    # Handle the "Results" command
    if ( $iCommand eq "Results")
    {
        # If Scanlog has been found, check returned text for real time error string.
        # If a client reports a real time error, set global flag. We can't just die here and 
        # now; instead we must wait for other "busy" clients to finish their current tasks.
        if($gScanlogAvailable and Scanlog::CheckForRealTimeErrors($args)) {$gRealTimeError = 240}; # Windoww Error 240: The session was canceled.
        # Print the correct headers for an individual command to the log
        print $BuildServer::gLogFileH "=== Stage=$gStageCount == $iComp\n";
        print $BuildServer::gLogFileH "-- $iCommandline\n";
        print $BuildServer::gLogFileH "--- $iClientName Executed ID $iID\n";
        # Print the output of the command into the log
        print $BuildServer::gLogFileH "$args";
        # Flush the handle to try and make sure the logfile is up to date
        $BuildServer::gLogFileH->flush;
        # Add this client to the list of client ready to process commands
        AddReady($iClientName,$iConn);
    }
}

# login_proc
#
# Inputs
#
# Outputs
#
# Description
# This function can be used to process a login procedure
# No login procdure is implemented
sub login_proc {
    # Unconditionally accept
    \&rcvd_msg_from_client;
}

# Start
#
# Inputs
# $iDataSource (XML Command file)
# $iPort (Port number to listen on for Build Clients)
# $iLogFile (Logfile to write output from Build Clients to)
#
# Outputs
#
# Description
# This function starts the server

sub Start
{
  my ($iDataSource, $iPort, $iLogFile, $iEnvSource) = @_;

  my ($iHost) = '';

  # Open the log file for writing, it will not overwrite logs
  $BuildServer::gLogFileH = IO::File->new("> $iLogFile")
    or croak "Couldn't open $iLogFile for writing: $!\n";  

  # If $iEnvSource is defined the Environment needs to be process from this file
  if (defined $iEnvSource)
  {
    # Parse the XML data
    &ParseXML::ParseXMLData($iEnvSource);
    # The $gEnvStart needs to be set to the number of Environment Variable Parsed from this file
    &ParseXML::SetEnvStart(scalar(keys %BuildServer::SetEnv));
  } else {
    # Set $gEnvStart to flag to process next XML normally
    &ParseXML::SetEnvStart(0);
  }

  # Parse the XML data
  &ParseXML::ParseXMLData($iDataSource);

  # Create the TCP/IP listen socket
  Msg->new_server($iHost, $iPort, \&login_proc);
  print "BuildServer created. Waiting for BuildClients\n";
  # Enter event loop to process incoming connections and messages
  Msg->event_loop();
}


# SendCommand
#
# Inputs
# $iConn
#
# Outputs
# Command sent via TCP connection
#
# Description
# This function Send a comand to the client
sub SendCommand
{
  my ($iConn) = @_;

  # Sends the next command to the client
  my $msg = $BuildServer::Commands{$gIDCount}{$gStageCount};
  $iConn->send_now($msg);
}

# AddReady
#
# Inputs
# $iClientName (Client name)
# $iConn (Connection Object)
#
# Outputs
#
# Description
# This function adds the client define by the connect ($iConn) to the list of ready clients
# It also sends new commands to clients if apropriate
sub AddReady
{
  my ($iClientName,$iConn) = @_;
  
  my (@iClientsWaiting, $iClientFN);
  
  # Set the client status to the "Waiting" State
  $gClientStatus{$iClientName} = "Waiting";

  # Count the number of waiting clients
  foreach $iClientFN (keys %gClientStatus)
  {
    if ($gClientStatus{$iClientFN} eq "Waiting")
    {
      # Add the all "Waiting" clients to a list of waiting Clients
      push @iClientsWaiting, $iClientFN;
    }
  }

  # If the number of waiting is equal to the total number of clients then this stage has finished
  if ((scalar @iClientsWaiting) == $iConn->TotalConnections)
  {
    # Check that a command is available (and that no real time error has been detected)
    if ((!defined $BuildServer::Commands{$gIDCount}{$gStageCount}) or $gRealTimeError)
    {
      # Increase the stage number
      print "Stage End $gStageCount\n";
      # Output to the log that the Stage has finished
      print $BuildServer::gLogFileH "=== Stage=$gStageCount finished ".localtime()."\n";
      # Flush the handle to try and make sure the logfile is up to date
      $BuildServer::gLogFileH->flush;
      # Increment the Stage number
      $gStageCount++;
      # Check whether a real time error has been reported. If so, terminate!
      if ($gRealTimeError)
      {
        # Real Time Error detected, so exit
        print "Real time error!!!\n";
        print $BuildServer::gLogFileH "Real time error! BuildServer terminating.\n";
        # Close the log file
        close ($BuildServer::gLogFileH);
        exit $gRealTimeError;
      }
      # Check that a command is available in the new stage
      if (!defined $BuildServer::Commands{$gIDCount}{$gStageCount})
      {
        # No more stages so exit
        print "No more stages\n";
        # Close the log file
        close ($BuildServer::gLogFileH);
        exit 0;
      }
        # Start the next Stage
        print $BuildServer::gLogFileH "===-------------------------------------------------\n";
        print $BuildServer::gLogFileH "=== Stage=$gStageCount\n";
        print $BuildServer::gLogFileH "===-------------------------------------------------\n";
        print $BuildServer::gLogFileH "=== Stage=$gStageCount started ".localtime()."\n";
        # Flush the handle to try and make sure the logfile is up to date
        $BuildServer::gLogFileH->flush;
    }
  }
  
  # While we have clients waiting and steps in a stage, send the clients commands (unless real time error)
  if ($gRealTimeError) { return; }
  # Sort the waiting client alphabetically
  @iClientsWaiting = sort(@iClientsWaiting);
  # Extract the first client name
  $iClientFN = shift @iClientsWaiting;
  # Loop through the client list
  while ((defined $iClientFN) && (defined $BuildServer::Commands{$gIDCount}{$gStageCount}))
  {
    print "Step $gIDCount\n";
    # Set client as "Busy"
    $gClientStatus{$iClientFN} = "Busy";    
    # Send the command
    print "Sending to $iClientFN\n";
    SendCommand($gClientHandles{$iClientFN});
    # Increment to IDCount
    $gIDCount++;
    # Extract the next client name
    $iClientFN = shift @iClientsWaiting;
  }
}
1;
