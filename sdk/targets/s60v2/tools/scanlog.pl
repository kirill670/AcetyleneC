# Copyright (c) 2003 Symbian Ltd. All rights reserved

# summarise an automated build log
#
# documentation available in generic\tools\e32toolp\docs\scanlog.txt
# please update the documentation when modifying this file
# RegEx's in Scanlog Module

use strict;
use FindBin;		# for FindBin::Bin

# Add the directory contain this perl script into the path to find modules
use lib $FindBin::Bin;

use Scanlog;

my $line;
my $phase;
my $match_phase='';
my $command='???';
my $skipping=0;
my $starttime;
my $duration;
my $errorcount=0;
my $component='???';
my %errors;
my %missing;
my %not_built;
my $totalduration = 0;
my $totalerrors = 0;
my $warningcount=0;
my %warnings;
my $totalwarnings = 0;
my $remarkscount=0;
my %remarks;
my $totalremarks = 0;
my ($iStatus, $iName);

my $verbose = 0;
my $argc = scalar(@ARGV);
if ($argc>0 and $ARGV[0]=~/^\s*\-v\s*$/)
	{
	$verbose = 1;
	shift @ARGV;
	}
elsif ($argc>0 and $ARGV[0]=~/^\s*\-V\s*$/)
	{
	$verbose = 2;
	shift @ARGV;
	}

sub do_remarks()
	{
	$remarkscount += 1;
	if (!defined $remarks{$component})
		{
		$remarks{$component} = ();
		}
	push @{$remarks{$component}}, $line;
	}
sub do_warning()
	{
	$warningcount += 1;
	if (!defined $warnings{$component})
		{
		$warnings{$component} = ();
		}
	push @{$warnings{$component}}, $line;
	}
	
sub do_error()
	{
	$errorcount += 1;
	if (!defined $errors{$component})
		{
		$errors{$component} = ();
		}
	push @{$errors{$component}}, $line;
	}

sub print_command_summary($;$)
	{
	my ($command, $duration) = @_;
	
	return if ($command eq '???' && $errorcount==0 && $warningcount==0 && $remarkscount==0 );
	
	my $elapsed = '??:??:??';
	if (defined($duration))
		{
		$totalduration += $duration;
		my ($sec,$min,$hour) = gmtime($duration);
		$elapsed = sprintf("%02d:%02d:%02d", $hour, $min, $sec);
		}

	printf "%-20s\t%s\t%6d\t%6d\t%6d\n", $command, $elapsed, $errorcount, $warningcount, $remarkscount;
	$totalerrors += $errorcount;
	$totalwarnings += $warningcount;
	$totalremarks += $remarkscount;
	$errorcount = 0;
	$warningcount = 0;
	$remarkscount = 0;
	}
	
printf "%-20s\t%-8s\t%-7s\t%-8s   %s\n", 'Command', 'Time', 'Errors', 'Warnings','Remarks';

while ($line=<>)
	{

	# ===-------------------------------------------------
	# === baseline_bldfiles   
	# ===-------------------------------------------------
	# === bldfiles started Sat Jul 24 01:38:03 1999.

	if ($line =~ /^===------/)
		{
		print_command_summary($command);
		$line = <>;
		$line =~ /=== (.*)$/;
		$command = $1;
		<>;
		$line = <>;
		$line =~ /^=== (.+) started ... ... .. (..):(..):(..)/;
		$phase = $1;
		$starttime = ($2*60 + $3)*60 + $4;
		$match_phase=$phase;
		$match_phase=~s-\\-\\\\-go;
		if (!$verbose)
			{
			$skipping = ($command =~ /(armv)/i)? 1:0;
			}
		next;
		}

	# === bldfiles finished Sat Jul 24 01:38:56 1999.
	if ($line =~ /^=== $match_phase finished ... ... .. (..):(..):(..)/)
		{
		$duration = ($1*60 + $2)*60 + $3 - $starttime;
		if ($duration < 0)
			{
			$duration += 24*60*60;
			}
		
		if ($skipping)
			{
			print STDERR "Skipped $command\n";
			}
		else
			{
			print_command_summary($command,$duration);
			}
		$skipping = 0;
		$command = '???';
		$component = '???';
		next;
		}

	next if ($skipping);
	
	# === resource == gdtran 036

	if ($line =~ /=== $match_phase == (\S+)/)
		{
		$component = $1;
		next;
		}

	# Remarks
  ($iStatus) =&Scanlog::CheckForRemarks($line);
	if ($iStatus)
	{
		do_remarks();
		next;
	}
	# Errors
  ($iStatus) =&Scanlog::CheckForErrors($line);
	if ($iStatus)
	{
		do_error();
		next;
	}

	# Warnings
  ($iStatus) =&Scanlog::CheckForWarnings($line);
	if ($iStatus)
	{
		do_warning();
		next;
	}

	# Things Not Built
  ($iStatus, $iName) =&Scanlog::CheckForNotBuilt($line);
	if ($iStatus)
	{
		do_error();
		$not_built{$iName} = "$component";
		next;
	}

	# Things missing
  ($iStatus, $iName) =&Scanlog::CheckForMissing($line);
	if ($iStatus)
	{
		do_error();
		$missing{$iName} += 1;
		next;
	}

}

print_command_summary($command);
print "\n";
my ($sec,$min,$hour, $mday) = gmtime($totalduration);
$hour+=($mday-1)*24;	# to allow for builds taking longer than 24 hours!

printf "%-20s\t%02d:%02d:%02d\t%6d\t%6d\t%6d\n\n", "Total", $hour, $min, $sec, $totalerrors, $totalwarnings, $totalremarks;

if (scalar %errors)
	{
	print "Fatal Errors by Component\n";
	$errorcount = 0;
	foreach $component (sort keys %errors)
		{
		printf "%-16s\t%6d\n", $component, scalar(@{$errors{$component}});
		$errorcount += scalar(@{$errors{$component}});
		}
	if ($verbose>0)
		{
		print "\nError details";
		foreach $component (sort keys %errors)
			{
			print "\n----------------------------\n$component\n";
			foreach $line (@{$errors{$component}})
				{
				print $line;
				}
			}
		}
	}

if (scalar %missing)
	{
	print "\nDon't know how to make...\n";
	foreach my $file (sort keys %missing)
		{
		printf "%d\t%s\n", $missing{$file}, $file;
		}
	}

if (scalar %not_built)
	{
	print "\nThings not built...\n";
	foreach my $file (sort keys %not_built)
		{
		print "MISSING: $file ($not_built{$file})\n";
		}
	print "\n\n";
	}

if (scalar %warnings)
	{
	print "\nWarnings by Component\n";
	$warningcount = 0;
	foreach $component (sort keys %warnings)
		{
		printf "%-16s\t%6d\n", $component, scalar @{$warnings{$component}};
		}
	if ($verbose>1)
		{
		print "\nWarning details";
		foreach $component (sort keys %warnings)
			{
			print "\n----------------------------\n$component\n";
			foreach $line (@{$warnings{$component}})
				{
				print $line;
				}
			}
		}
	}
if (scalar %remarks)
	{
	print "\nRemarks by Component\n";
	$remarkscount = 0;
	foreach $component (sort keys %remarks)
		{
		printf "%-16s\t%6d\n", $component, scalar @{$remarks{$component}};
		}
	if ($verbose>1)
		{
		print "\nRemarks details";
		foreach $component (sort keys %remarks)
			{
			print "\n----------------------------\n$component\n";
			foreach $line (@{$remarks{$component}})
				{
				print $line;
				}
			}
		}
	}
