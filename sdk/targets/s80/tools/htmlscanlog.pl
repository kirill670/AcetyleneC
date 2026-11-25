# Copyright (c) 2003 Symbian Ltd. All rights reserved

# summarise an automated build log
use strict;
use Getopt::Long;
use HTML::Entities;
use Date::Calc qw(:all);
use Carp;
use FindBin;		# for FindBin::Bin

# Add the directory contain this perl script into the path to find modules
use lib $FindBin::Bin;
use Scanlog;

# Variables
my $line;
my $PhaseStartTime;
my %Phases;
my %Components;
my %Commands;
my $component;
my $command;
my $phase;
my $match_phase='';
my %errors;
my %warnings;
my %CmdErrors;
my %CmdWarnings;
my %missing;
my %not_built;
my $starttime;
my $duration;
my $warningcount;
my $errorcount;
my ($iStatus, $iName);

# Hires Timer Variables
my %HiResComponents;
my %HiResCommands;
my $HiResStartTime;
my $HiResErrorFlag; #True if one of the Clients has not reported HiRes timing info

my $Dsec;

# Main section

my ($iOutput, $iTitle, $iVerbose, $iDiff, $iWhat, @iLogs) =&ProcessCommandLine();

# Open Output file
  open (HTML, "> $iOutput") or die "Couldn't open $iOutput for writing: $!\n";

# Open Diff file if specified
if ($iDiff ne '')
{
  open (DIFF, "> $iDiff") or die "Couldn't open $iDiff for writing: $!\n";
}

# Print HTML Header
&PrintHTMLHeader($iTitle);


# Parse each log File
foreach my $iLog (@iLogs)
{
  # Open the Log file for reading
  open (LOG, "< $iLog") or die "Couldn't open $iLog for reading: $!\n";

  # Chop $iLog just to the filename
  $iLog =~ s/^.*\\//;

  # Process the logs
  &ProcessLog($iLog);
  close LOG;
}

&PrintResults($iTitle);

# Print HTML Footer
&PrintHTMLFooter();

# DiffLog
#
# Inputs
#
# Outputs
#
# Description
# This function Outputs lines to the diff log
sub DiffLog()
{
    # Write the line to diff file if specified and not a line with Build Time dependent infomation
    if ($iDiff ne '')
    {
       # Check the line for Build Time dependent infomation
       unless (($line =~ /^=== .+ started/) || ($line =~ /^=== .+ finished/) || ($line =~ /^---/) || ($line =~ /^\+\+/))
       {
          print DIFF $line;
       }
    }
}


# ProcessLog
#
# Inputs
# $iLog - Logfile name
#
# Outputs
#
# Description
# This function processes the commandline
sub ProcessLog()
{
  my ($iLog) = @_;

  while ($line=<LOG>)
	{
    &DiffLog;


    # ===-------------------------------------------------
    # === Stage=1
    # ===-------------------------------------------------
    # === Stage=1 started Wed Apr 30 23:09:38 2003

    if ($line =~ /^===------/)
    {
      $line=<LOG>;
          &DiffLog;
      $line=<LOG>;
          &DiffLog;
      $line = <LOG>;
          &DiffLog;
      $line =~ /^=== (.+) started (.*)/;
      $phase = $1;
      $PhaseStartTime =$2;
      $match_phase=$phase;
      $match_phase=~s-\\-\\\\-go;
      next;
    }

    # === bldfiles finished Sat Jul 24 01:38:56 1999.
    if ($line =~ /^=== $match_phase finished (.*)/)
    {
      # Calculate the difference in Date/Time and Total up for Phase
      $Phases{$phase} += &DiffDateTime($PhaseStartTime, $1) ;
      next;
    }


    # === resource == gdtran 036

    if ($line =~ /=== $match_phase == (.*)$/)
    {
      $component = $1;
      next;
    }

    # Find Command
    # -- bldmake bldfiles -keepgoing
    if ($line =~ /^-- (.*)/)
    {
      $command = $1;
      next;
    }

    # Find the Command's Start time
    # ++ Started at Sat May 03 21:09:07 2003
    if ($line =~ /^\+\+ Started at (.*)/)
    {
      $starttime = $1;
      next;
    }

    # Find the Command's End time
    # ++ Started at Sat May 03 21:09:07 2003
    if ($line =~ /^\+\+ Finished at (.*)/)
    {
      # Calculate the difference in Date/Time and Total up for Command
      $Dsec = &DiffDateTime($starttime, $1);
      $Commands{$command} += $Dsec;
      # Calculate the difference in Date/Time and Total up for Component
      $Components{$component} += $Dsec;
      next;
    }

    # Act on a HiRes Timer unavailable statement in the log
    # +++ HiRes Time Unavailable
    if (($line =~ /^\+\+\+ HiRes Time Unavailable/) && !$HiResErrorFlag)
    {
      $HiResErrorFlag = 1;
          print "Warning one of the clients is not sending HiRes timer Data\n";
          print "No HiRes timings will be available\n";
          print "Reverting to LowRes timing Data\n";
      # Clear out Current HiRes Data
      undef %HiResCommands;
      undef %HiResComponents;
      next;
    }


    # Find the Command's HiRes Start time
    # +++ HiRes Start 1051993130.602050
    if (($line =~ /^\+\+\+ HiRes Start (\S+)/) && !$HiResErrorFlag)
    {
      $HiResStartTime = $1;
      next;
    }

    # Find the Command's HiRes End time
    # +++ HiRes End 1051993193.829650
    if (($line =~ /^\+\+\+ HiRes End (\S+)/) && !$HiResErrorFlag)
    {
      # Calculate the difference in Date/Time and Total up for Command
      $HiResCommands{$command} += ($1 - $HiResStartTime);
      # Calculate the difference in Date/Time and Total up for Component
      $HiResComponents{$component} += ($1 - $HiResStartTime);
      next;
    }


    # Errors
    ($iStatus) =&Scanlog::CheckForErrors($line);
    if ($iStatus)
    {
      do_error($iLog);
      next;
    }

    # Warnings
    ($iStatus) =&Scanlog::CheckForWarnings($line);
    if ($iStatus)
    {
      do_warning($iLog);
      next;
    }

    # Things Not Built
    ($iStatus, $iName) =&Scanlog::CheckForNotBuilt($line);
    if ($iStatus)
    {
      $errorcount += 1;
      $not_built{$iName} = "genbuild";
      next;
    }

    # Things missing
    ($iStatus, $iName) =&Scanlog::CheckForMissing($line);
    if ($iStatus)
    {
      do_error($iLog);
      $missing{$iName} += 1;
      next;
    }

	}
}


# PrintResults
#
# Inputs
# $iTitle (Title for Log file)
#
# Outputs
#
# Description
# This function prints all the data as HTML
sub PrintResults
{
  my ($iTitle) = @_;

  # Print Heading of Log File
  print HTML qq{<h1>$iTitle</h1>\n};
  print HTML qq{<h2>Overall</h2>\n};

  # Calculate the Total number of errors
  	$errorcount = 0;
	foreach $component (sort keys %errors)
		{
		$errorcount += scalar(@{$errors{$component}});
		}
  # Calculate the total number of warnings
	$warningcount = 0;
	foreach $component (sort keys %warnings)
		{
		$warningcount += scalar(@{$warnings{$component}});
		}
  # Calculate the Total Duration from Phase Data
	$duration = 0;
	foreach $phase (sort keys %Phases)
		{
		  $duration += $Phases{$phase};
		}
  # Start the Table
  &StartHTMLTable();

  # Print the Totals
  &HTMLTableRow("Total", $duration, $errorcount, $warningcount);

  # End the Table
  print HTML qq{</table>\n};



  # By Component
  print HTML qq{<h2>By Component</h2>\n};

  # Start the Table
  &StartHTMLTable("Component");

  # Print the by Component Data
  # If there is a complete set of HiRes data then use that instead of the LowRes data
  if ((defined %HiResComponents) && !$HiResErrorFlag)
  {
    foreach $component (sort keys %HiResComponents)
	{
      # Calculate the number errors and warnings
      my $totalerrors;
      my $totalwarnings;
      if (!defined $errors{$component})
      {
        # No errors were recorded, set total to zero
        $totalerrors = 0;
      } else {
        $totalerrors = scalar(@{$errors{$component}});
      }
      if (!defined $warnings{$component})
      {
        # No Warnings were recorded, set total to zero
        $totalwarnings = 0;
      } else {
        $totalwarnings = scalar(@{$warnings{$component}});
      }

      # Print the Table Row
	  &HTMLTableRow($component, $HiResComponents{$component}, $totalerrors, $totalwarnings);
	}
  } else {
    foreach $component (sort keys %Components)
	{
      # Calculate the number errors and warnings
      my $totalerrors;
      my $totalwarnings;
      if (!defined $errors{$component})
      {
        # No errors were recorded, set total to zero
        $totalerrors = 0;
      } else {
        $totalerrors = scalar(@{$errors{$component}});
      }
      if (!defined $warnings{$component})
      {
        # No Warnings were recorded, set total to zero
        $totalwarnings = 0;
      } else {
        $totalwarnings = scalar(@{$warnings{$component}});
      }

      # Print the Table Row
	  &HTMLTableRow($component, $Components{$component}, $totalerrors, $totalwarnings);
	}
  }

  # End the Table
  print HTML qq{</table>\n};

  # By Command
  print HTML qq{<h2>By Command</h2>\n};

  # Start the Table
  &StartHTMLTable("Command");

  # Print the by Command Data
  # If there is a complete set of HiRes data then use that instead of the LowRes data
  if ((defined %HiResCommands) && !$HiResErrorFlag)
  {
    foreach $command (sort keys %HiResCommands)
	{
      # Calculate the number errors and warnings
      my $totalerrors;
      my $totalwarnings;
      if (!defined $CmdErrors{$command})
      {
        # No errors were recorded, set total to zero
        $totalerrors = 0;
      } else {
        $totalerrors = scalar(@{$CmdErrors{$command}});
      }
      if (!defined $CmdWarnings{$command})
      {
        # No Warnings were recorded, set total to zero
        $totalwarnings = 0;
      } else {
        $totalwarnings = scalar(@{$CmdWarnings{$command}});
      }

      # Print the Table Row
	  &HTMLTableRow($command, $HiResCommands{$command}, $totalerrors, $totalwarnings);
	}
  } else {
    foreach $command (sort keys %Commands)
    {
      # Calculate the number errors and warnings
      my $totalerrors;
      my $totalwarnings;
      if (!defined $CmdErrors{$command})
      {
        # No errors were recorded, set total to zero
        $totalerrors = 0;
      } else {
        $totalerrors = scalar(@{$CmdErrors{$command}});
      }
      if (!defined $CmdWarnings{$command})
      {
        # No Warnings were recorded, set total to zero
        $totalwarnings = 0;
      } else {
        $totalwarnings = scalar(@{$CmdWarnings{$command}});
      }

      # Print the Table Row
      &HTMLTableRow($command, $Commands{$command}, $totalerrors, $totalwarnings);
    }
  }

  # End the Table
  print HTML qq{</table>\n};

  # Print Things Missing
  if (scalar %missing)
	{
	print HTML qq{<h2>Things Missing</h2>\n};
	print HTML "Don't know how to make...\n";
	foreach my $file (sort keys %missing)
		{
		printf HTML "%d\t%s</BR>\n", $missing{$file}, $file;
		}
	}
  print HTML qq{</BR>\n};

  # Print Things Not Built
  if (scalar %not_built)
	{
	print HTML qq{<h2>Things Not Built</h2>\n};
	foreach my $file (sort keys %not_built)
		{
		print HTML "MISSING: $file ($not_built{$file})</BR>\n";
		}
	}


  # Print the Actual Errors by Component
  if ($iVerbose > 0)
  {
    # Only Print the header if there are some errors
    if (scalar(keys %errors))
    {
      print HTML qq{<h2>Error Details by Component</h2>\n};
	  foreach $component (sort keys %errors)
		{
			my ($HTML) = $component;
			encode_entities($HTML);
			print HTML qq{<h3>$HTML</h3>\n};
			foreach $line (@{$errors{$component}})
				{
				encode_entities($line);
				print HTML $line.qq{</BR>};
				}
			print HTML qq{</BR>\n};
		}
    }
  }

  # Print the Actual Warning by Component
  if ($iVerbose > 1)
  {
    # Only Print the header if there are some warnings
    if (scalar(keys %warnings))
    {
      print HTML qq{<h2>Warning Details by Component</h2>\n};
      foreach $component (sort keys %warnings)
        {
          my ($HTML) = $component;
          encode_entities($HTML);
          print HTML qq{<h3>$HTML</h3>\n};
          foreach $line (@{$warnings{$component}})
            {
            encode_entities($line);
            print HTML $line.qq{</BR>};
            }
          print HTML qq{</BR>\n};
        }
    }
  }

  # Print the Actual Errors by Command
  if ($iVerbose > 0)
  {
    # Only Print the header if there are some errors
    if (scalar(keys %CmdErrors))
    {
      print HTML qq{<h2>Error Details by Command</h2>\n};
	  foreach $command (sort keys %CmdErrors)
		{
			my ($HTML) = $command;
			encode_entities($HTML);
			print HTML qq{<h3>$HTML</h3>\n};
			foreach $line (@{$CmdErrors{$command}})
				{
				encode_entities($line);
				print HTML $line.qq{</BR>};
				}
			print HTML qq{</BR>\n};
		}
    }
  }

  # Print the Actual Warning by Command
  if ($iVerbose > 1)
  {
    # Only Print the header if there are some warnings
    if (scalar(keys %CmdWarnings))
    {
      print HTML qq{<h2>Warning Details by Command</h2>\n};
	  foreach $command (sort keys %CmdWarnings)
		{
			my ($HTML) = $command;
			encode_entities($HTML);
			print HTML qq{<h3>$HTML</h3>\n};
			foreach $line (@{$CmdWarnings{$command}})
				{
				encode_entities($line);
				print HTML $line.qq{</BR>};
				}
			print HTML qq{</BR>\n};
		}
    }
  }

}


# StartHTMLTable
#
# Inputs
# $iC1Title (Column 1 Title)
#
# Outputs
#
# Description
# This function prints the start of the HTML Table
sub StartHTMLTable
{
  my ($iC1Title) = @_;

  if ($iC1Title eq '')
  {
    $iC1Title = "&nbsp;";
  } else {
    encode_entities($iC1Title);
  }

  # Start the Table
  print HTML qq{<table border="1" cellpadding="0" cellspacing="0" width="100%">\n};

  # Print the Header Row
  print HTML qq{<tr>\n};
  print HTML qq{\t<th width="55%">$iC1Title</th>\n};
  print HTML qq{\t<th width="15%">Time</th>\n};
  print HTML qq{\t<th width="15%">Errors</th>\n};
  print HTML qq{\t<th width="15%">Warnings</th>\n};
  print HTML qq{</tr>\n};
}

# HTMLTableRow
#
# Inputs
# $iC1Data(Column 1 Data)
# $iC2Data(Column 2 Data) (Time in seconds)
# $iC3Data(Column 3 Data) (Number of errors)
# $iC4Data(Column 4 Data) (Number of warnings)
#
# Outputs
#
# Description
# This function prints the start of the HTML Table
sub HTMLTableRow
{
  my ($iC1Data, $iC2Data, $iC3Data, $iC4Data) = @_;

  #print "$iC2Data\n";

  # Convert the seconds in hh:mm:ss format
  my ($ih) = int($iC2Data/3600);
  my ($im) = int(($iC2Data-($ih*3600))/60);
  my ($is) = $iC2Data-($ih*3600)-($im*60);
  # Print the correct format if the data is HiRes (has a decimal point in the string)
  if ($is =~ /\d+\.\d+/)
  {
    $iC2Data = sprintf "%d:%02d:%06.3f", $ih, $im, $is;
  } else {
    $iC2Data = sprintf "%d:%02d:%02d", $ih, $im, $is;
  }

  # HTML encode the text
  encode_entities($iC1Data);
  encode_entities($iC2Data);
  encode_entities($iC3Data);
  encode_entities($iC4Data);

  # Print the Row
  print HTML qq{<tr>\n};
  print HTML qq{\t<td width="55%">$iC1Data</td>\n};
  print HTML qq{\t<td width="15%" align="center">$iC2Data</td>\n};
  # Highlight the errors with red cell background
  if ($iC3Data > 0)
  {
    print HTML qq{\t<td width="15%" align="center" BGCOLOR="#ff0000">$iC3Data</td>\n};
  } else {
    print HTML qq{\t<td width="15%" align="center">$iC3Data</td>\n};
  }
  # Highlight the warnings with yellow cell background
  if ($iC4Data > 0)
  {
    print HTML qq{\t<td width="15%" align="center" BGCOLOR="#ffff00">$iC4Data</td>\n};
  } else {
    print HTML qq{\t<td width="15%" align="center">$iC4Data</td>\n};
  }
  print HTML qq{</tr>\n};
}

# ProcessCommandLine
#
# Inputs
#
# Outputs
# $iOutput (Output filename)
# $iVerbose (Verbose Level)
# $iLogs (Log files to process)
#
# Description
# This function processes the commandline

sub ProcessCommandLine {
  my ($iHelp, @iLogs, $iOutput, $iTitle, $iVerbose, $iDiff, $iWhat);
  GetOptions('h' => \$iHelp, 'l=s' =>\@iLogs, 'o=s' => \$iOutput, 't=s' => \$iTitle, 'v+' => \$iVerbose, 'd=s' =>\$iDiff, 'w=s' =>\$iWhat);

  if (($iHelp) || (!defined @iLogs) || (!defined $iOutput))
  {
    Usage();
  } elsif (-e $iOutput) {
    die "$iOutput already exists";
  } elsif (-e $iDiff) {
    die "$iDiff already exists";
  } elsif (-e $iWhat) {
    die "$iWhat already exists";
  }
  foreach my $iLog (@iLogs)
  {
    die "$iLog does not exists" if (! -e $iLog);
  }

  # Set default title
  if ($iTitle eq '')
  {
    $iTitle = "Log File Summary";
  }

  return($iOutput, $iTitle, $iVerbose, $iDiff, $iWhat, @iLogs);
}

# Usage
#
# Output Usage Information.
#

sub Usage {
  print <<USAGE_EOF;

    Usage: Scanlog.pl [options]

    options:

    -h  help
    -l  Log file to scan [Multiple allowed]
    -o  Output file
    -v  Increments Verbose level [Maximum Level = 2]
    -t  Title to add to the Summary
    -d  Filename for Logfile with Time information removed [Optional]
USAGE_EOF
	exit 1;
}

# PrintHTMLHeader
#
# Inputs
# $iTitle (Title for Log file)
#
# Outputs
#
# Description
# This function print the HTML Header

sub PrintHTMLHeader {
  my ($iTitle) = @_;

   print HTML <<HTML_EOF;
<HTML>
<HEAD>
<TITLE>$iTitle</TITLE>
</HEAD>
<BODY BGCOLOR="FFFFFF">
<FONT FACE="Courier New">
HTML_EOF
}

# PrintHTMLFooter
#
# Inputs
#
# Outputs
#
# Description
# This function print the HTML Footer

sub PrintHTMLFooter {
   print HTML <<HTML_EOF;
</FONT>
</BODY>
</HTML>
HTML_EOF
}

#  DiffDateTime
#
# Inputs
# $StartDateTime (Start Date/Time String)
# $EndDateTime (End Date/Time String)
#
# Outputs
# $Duration (Difference in seconds bertween the two dates/Times)
#
# Description
# This function calculate the difference between to dates and times

sub DiffDateTime {
  my ($String1, $String2) = @_;

  my ($year1,$month1,$day1, $hour1,$min1,$sec1);
  my ($year2,$month2,$day2, $hour2,$min2,$sec2);
  my ($Dd,$Dh,$Dm,$Ds);

  # Split date and Time
  ($hour1,$min1,$sec1) = $String1 =~ /(\d+):(\d+):(\d+)/;
  ($year1,$month1,$day1) = Parse_Date($String1);
  ($hour2,$min2,$sec2) = $String2 =~ /(\d+):(\d+):(\d+)/;
  ($year2,$month2,$day2) = Parse_Date($String2);
  # Calculate the duration
  ($Dd,$Dh,$Dm,$Ds) = Delta_DHMS($year1,$month1,$day1, $hour1,$min1,$sec1, $year2,$month2,$day2, $hour2,$min2,$sec2);
  # Convert into seconds to aid additions
  return ((((($Dd*24)+$Dh)*60)+$Dm)*60)+$Ds;
}


sub do_warning()
{
	my ($iLog) =@_;
	# Store warning by Command
	if (!defined $CmdWarnings{$command})
		{
		$CmdWarnings{$command} = ();
		}
	push @{$CmdWarnings{$command}}, "$iLog:"."$.".">$line";

	# Store warning by Component
	if (!defined $warnings{$component})
		{
		$warnings{$component} = ();
		}
	push @{$warnings{$component}}, "$iLog:"."$.".">$line";
}

sub do_error()
{
  my ($iLog) =@_;
	# Store Errors by Command
	if (!defined $CmdErrors{$command})
		{
		$CmdErrors{$command} = ();
		}
	push @{$CmdErrors{$command}}, "$iLog:"."$.".">$line";

	# Store Errors by Component
	if (!defined $errors{$component})
		{
		$errors{$component} = ();
		}
	push @{$errors{$component}}, "$iLog:"."$.".">$line";
}
