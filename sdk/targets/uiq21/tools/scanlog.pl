# summarise an automated build log

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
	
	return if ($command eq '???' && $errorcount==0 && $warningcount==0);
	
	my $elapsed = '??:??:??';
	if (defined($duration))
		{
		$totalduration += $duration;
		my ($sec,$min,$hour) = gmtime($duration);
		$elapsed = sprintf("%02d:%02d:%02d", $hour, $min, $sec);
		}

	printf "%-39s\t%s\t%6d\t%6d\n", $command, $elapsed, $errorcount, $warningcount;
	$totalerrors += $errorcount;
	$totalwarnings += $warningcount;
	$errorcount = 0;
	$warningcount = 0;
	}
	
printf "%-39s\t%-8s\t%-7s\t%-8s\n", 'Command', 'Time', 'Errors', 'Warnings';
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

	# MISSING COMPONENT alp2csh: can't find tools\sdk_eng\alp2csh\group\bld.inf

	if ($line =~ /^MISSING COMPONENT (.*):.* find (.*)$/)
		{
		$errorcount += 1;
		$not_built{$2} = "genbuild";
		next;
		}


	# BLDMAKE ERROR: Can't find "\INTERNET\GROUP\BLD.INF"
	# ABLD ERROR: Project Bldmake directory "\EPOC32\BUILD\APP-FRAMEWORK\UIKLAF\GROUP\" does not exist

	if ($line =~ /(ABLD|BLDMAKE) ERROR:/)
		{
		do_error();
		next;
		}

	# "\WAPENG\GROUP\BLD.INF" FATAL ERROR(S):

	if ($line =~ /FATAL ERROR\(S\):/)
		{
		do_error();
		next;
		}

	# NMAKE : fatal error U1073: don't know how to make '"\EPOC32\INCLUDE\COMMS.MBG"'

	if ($line =~ /fatal error U1073: .* make '(.*)'/)
		{
		do_error();
		$missing{$1} += 1;
		next;
		}

	# NMAKE : fatal error U1077: 'C:\apps\DevStudio\VC\BIN\NMAKE.EXE' : return code '0x2'

	if ($line =~ /fatal error U1077/)
		{
		do_error();
		next;
		}

	# NMAKE : warning U4010: 'FINALCOPYFXCM' : build failed; /K specified, continuing ...

	if ($line =~ /warning U4010/)
		{
		do_error();
		next;
		}

	# make: *** [SAVESPACECONVTOOL] Error 2

	if ($line =~ /make(\[\d+\])?: \*\*\* /)
		{
		do_error();
		next;
		}

	# make: Target `SAVESPACE' not remade because of errors.

	if ($line =~ /make(\[\d+\])?: .* not remade /)
		{
		do_error();
		next;
		}

	# RCOMP Warning: Unmatched enum name used as simple initialiser

	if ($line =~ /Warning: Unmatched/i)
		{
		do_warning();
		next;
		}


	# BLDMAKE WARNING: read-only ABLD.BAT will be overwritten

	if ($line =~ /^BLDMAKE WARNING:/)
		{
		do_warning();
		next;
		}


	# \FORM\GROUP\BLD.INF WARNING(S):
	# \FORM\GROUP\BLD.INF(28) : Exported source file \form\group\tagma.rtf not found

	if ($line =~ /WARNING\(S\)/)
		{
		do_warning();
		next;
		}

	# WARNING: Can't find following headers in User or System Include Paths
	# WARNING: Frozen .DEF file \CSTUBSHELL\BMARM\STUBRUNU.DEF not found - project not frozen
	# WARNING: Not attempting to create any import libraries.
	# WARNING: rls_string STRING_r_ssl_error_ssl_AlertNoRenegotiation; either has incorrect syntax or no value

	if ($line =~ /^WARNING: /)
		{
		do_warning();
		next;
		}

	# \BIOMSG\BITSINC\BioTestUtils.inl(4) : warning C4100: 'iOperation' : unreferenced formal parameter

	if ($line =~ /\(\d+\) : warning C/)
		{
		do_warning();
		next;
		}

	# LINK : warning LNK4005: no objects used from library \EPOC32\RELEASE\WINS\UDEB\ESTOR.LIB

	if ($line =~ /LINK : warning/)
		{
		do_warning();
		next;
		}

	# ..\\..\\BAFL\\SRC\\Bacline.cpp:68: warning: value computed is not used

	if ($line =~ /:\d+: warning:/)
		{
		do_warning();
		next;
		}

	# "..\UCRT\Ecrt0.cpp", line 12: Warning:  #335-D: linkage specification is not allowed
	# "s16c.o(.directive)", line 70: Warning: L6331W: s16c.o(.directive)(line 70, col 14) No eligible global symbol matches pattern _fsqrt.

	if ($line =~ /"(.*)", line (\d+): (Warning: +(.\d+.*?):.*)$/)
		{
		do_warning();
		next;
		}

	# "..\UCRT\Ecrt0.cpp", line 24: Error:  #390: function "main" may not be called or have its address taken
	# "EUSER\\epoc\\arm\\Uc_i64.cia", line 16: Error: A1356W: Instruction not supported on targeted CPU

	if ($line =~ /"(.*)", line (\d+): (Error: +(.\d+.*?):.*)$/)
		{
		do_error();
		next;
		}

	# Fatal error: Internal fault: 0x5c6e (200322) in _ZN17CContactLocalView20HandleDatabaseEventLE23TContactDbObserverEvent

	if ($line =~ /error: ((Internal fault):.*)$/)
		{
		do_error();
		next;
		}
	# MAKEDEF WARNING: 1 export(s) not yet Frozen:

	if ($line =~ /^MAKEDEF WARNING:/)
		{
		do_warning();
		next;
		}

	# Comment from PETRAN which is actually a warning rather than an error
	# ERROR: bad relocation:  [00004f60] = 00000f68

	if ($line =~ /ERROR: bad relocation:/)
		{
		do_warning();
		next;
		}

	# 1 warning

	if ($line =~ /^(\d+) warning/)
		{
		do_warning();
		next;
		}

	# MISSING: \EPOC32\RELEASE\WINS\UDEB\OPLR.DLL

	if ($line =~ /^MISSING: (\S+)/)
		{
		$not_built{$1} = $component;
		next;
		}

	# mwld.exe: No symbols were exported

	if ($line =~ /mwld.exe:/)
		{
		do_warning();
		next;
		}
	
	}

print_command_summary($command);
print "\n";
my ($sec,$min,$hour, $mday) = gmtime($totalduration);
$hour+=($mday-1)*24;	# to allow for builds taking longer than 24 hours!

printf "%-39s\t%02d:%02d:%02d\t%6d\t%6d\n\n", "Total", $hour, $min, $sec, $totalerrors, $totalwarnings;

if ($totalerrors > 0)
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

if ($totalwarnings > 0)
	{
	print "Warnings by Component\t  Total\n";
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
