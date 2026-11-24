@rem = '--*-Perl-*--
@echo off
if "%OS%" == "Windows_NT" goto WinNT
perl -x -S "%0" %1 %2 %3 %4 %5 %6 %7 %8 %9
goto endofperl
:WinNT
perl -x -S "%0" %*
if NOT "%COMSPEC%" == "%SystemRoot%\system32\cmd.exe" goto endofperl
if %errorlevel% == 9009 echo You do not have Perl in your PATH.
goto endofperl
@rem ';
#!perl
#line 14


use File::Spec;
use Getopt::Long;
use File::Copy;
use File::Path;

my $toolVersion = "1.0";


# 1. Check arguments, output help etc.

my $analyse = 0;
my $list = 0;
my $update = 0;
my $warnings = 0;
my $debugUpdate = 0;
GetOptions ('analyse|a' => \$analyse, 'list|l' => \$list, 'update|u' => \$update, 'warnings|w' => \$warnings, 'debugupdate|du' => \$debugUpdate);

if (@ARGV == 0)
	{
	print (STDERR "\nFIXSOURCE.BAT - Version $toolVersion\n");

	print STDERR << 'END_OF_HELP';

Usage: fixsource.bat -analyse|-list|-update|-warnings buildlog_1.log [buildlog_n.log] 

Parses the output from the specified build logs to locate warnings produced via "abld -checksource".
Provides the option to update source automatically to comply with Symbian's Filename Policy.

-analyse | -a	List and describe all warnings that cannot be addressed by this tool.
-list    | -l	List all source files that can be updated by this tool using "-update".
-update  | -u	Update source files, as output by "-list", to comply with Symbian's Filename Policy.
-warnings| -w	Output all unique "-checksource"  warnings present in the specified logs, regardless
		of whether they can be fixed by this tool.

NOTES:
*	The tool assumes that the original build source layout is replicated on the drive
	where it is being executed.
*	With the exception of the "-warnings" output, any warnings for files under the known release and
	build locations of \epoc32\include and \epoc32\build are discarded by default.

END_OF_HELP

	}



# 2. Parse the logs storing all GNU format warnings and errors


my %FilenamePolicyWarnings; 	# Hash Key (filename)
								#	Hash Key (line number)
								#		Hash Key (text to change)
								#            Value (original warning)
my %AllFilenamePolicyWarnings;
my %OtherWarningsAndErrors;


foreach my $BUILD_LOG (@ARGV)
	{
	open BUILD_LOG, "< $BUILD_LOG" or die "\nCannot read \"$BUILD_LOG\"!\n\n";

	my $line;
	
	while ($line = <BUILD_LOG>)
		{
		if ($line =~ /^\S+:\d+: Incorrect/)
			{
			$AllFilenamePolicyWarnings{$line} = 1;
				
			my $file = $line;
			my $lineNumber = $line;
			my $plainText = $line;
			my $originalWarning = $line;

			$file =~ s/:\d+: Incorrect.*$//;
			$lineNumber =~ s/: .+$//;
			$lineNumber =~ s/^.+://;
			$plainText =~ s/\'\.$//;
			$plainText =~ s/^\S+:\d+: Incorrect.*\'//;
			chomp ($file, $lineNumber, $plainText);
			my $quotemetaText = quotemeta ($plainText);

			my $lineNumberHashRef;

			if ($FilenamePolicyWarnings{$file})
				{
				$lineNumberHashRef = $FilenamePolicyWarnings{$file};
				}
			else
				{
				my %newHash;
				$lineNumberHashRef = \%newHash;
				$FilenamePolicyWarnings{$file} = $lineNumberHashRef;
				}

			my $textToChangeHashRef;

			if ($$lineNumberHashRef{$lineNumber})
				{
				$textToChangeHashRef = $$lineNumberHashRef{$lineNumber};
				}
			else
				{
				my %newHash;
				$textToChangeHashRef = \%newHash;
				$$lineNumberHashRef{$lineNumber} = $textToChangeHashRef;
				}

			$$textToChangeHashRef{$quotemetaText} = $originalWarning;

			next
			}

		if ($line =~ /^\S+:\d+:/)
			{
			$OtherWarningsAndErrors{$line} = 1;
			next;
			}
		}

	close BUILD_LOG;
	}


# 3. Compile lists of files and warnings that we can/can't do anything about

my %missingFiles;
my %mismatchedWarnings;

if ($analyse || $list || $update || $debugUpdate)
	{	
	foreach my $SOURCE_FILE (sort keys %FilenamePolicyWarnings)
		{
		# Immediately discard anything in the known release locations
		if (($SOURCE_FILE =~ /\\epoc32\\include\\/i) || ($SOURCE_FILE =~ /\\epoc32\\build\\/i))
			{
			delete ($FilenamePolicyWarnings{$SOURCE_FILE});
			next;
			}
		
		if (!(open SOURCE_FILE, "< $SOURCE_FILE"))
			{				
			$missingFiles{$SOURCE_FILE} = 1;
			next;
			}

		my $lineNumbersHashRef = $FilenamePolicyWarnings{$SOURCE_FILE};
		my $lineNumber = 0;

		while (my $line = <SOURCE_FILE>)
			{
			$lineNumber++;

			next if (!($$lineNumbersHashRef{$lineNumber}));

			my $textToChangeHashRef = $$lineNumbersHashRef{$lineNumber};

			foreach my $text (keys %{$textToChangeHashRef})
				{
				chomp ($line);

				if ($line !~ /$text/)
					{
					# When comparing #includes warnings, we need to deal with the fact that CPP
					# may have removed whitespace from what's in the original source e.g.
					# CPP    : "#include <CommsDatTypesV1_1.h>"
					# Actual : "#	include   <CommsDatTypesV1_1.h>"
					# We check for this, and then re-instate what's actually in source as
					# the thing to be updated.
					
					if (($line =~ /\#\s+include\s+[\"|\<]{1}\S+[\"|\>]{1}/) ||
						($line =~ /\#include\s{2,}[\"|\<]{1}\S+[\"|\>]{1}/))
						{						
						my $actualSourceText = $&;

						my $whitespaceStrippedText = $actualSourceText;
						$whitespaceStrippedText =~ s/\#\s+include/\#include/;
						$whitespaceStrippedText =~ s/\#include\s{2,}/#include /;

						# Re-test, based on a CPP compliant version of the #include
						if ($whitespaceStrippedText =~ /$text/)
							{						
							my $originalWarning = $$textToChangeHashRef{$text};
							delete ($$textToChangeHashRef{$text});
							$$textToChangeHashRef{quotemeta($actualSourceText)} = $originalWarning;
							next;
							}
						}
					
					$mismatchedWarnings{$$textToChangeHashRef{$text}} = $line;
					delete ($$textToChangeHashRef{$text});
					}
				}

			delete ($$lineNumbersHashRef{$lineNumber}) if (!scalar (keys %{$textToChangeHashRef}));
			}

		delete ($FilenamePolicyWarnings{$SOURCE_FILE}) if (!scalar (keys %{$lineNumbersHashRef}));
		close SOURCE_FILE;
		}
	}


# 4. Provide -analyse output

if ($analyse)
	{
	print ("\nMissing Files\n".
		     "-------------\n\n");

	foreach my $missingFile (sort keys %missingFiles)
		{
		print ("$missingFile\n");
		}
	print ("NONE\n") if (!scalar (keys %missingFiles));

	print ("\nWarning\\Source Mismatches\n".
		     "--------------------------\n\n");
		
	foreach my $mismatchedWarning (sort keys %mismatchedWarnings)
		{
		print ("$mismatchedWarning");
		print ("\tACTUAL LINE : \'$mismatchedWarnings{$mismatchedWarning}\'\n\n");
		}
	print ("NONE\n") if (!scalar (keys %mismatchedWarnings));

	print ("\n");
	}


# 5. Provide -list output

if ($list)
	{
	foreach my $sourceFile (sort keys %FilenamePolicyWarnings)
		{
		print ("$sourceFile\n");
		}
	}	


# 6. Provide -warnings output

if ($warnings)
	{
	foreach my $warning (sort keys %AllFilenamePolicyWarnings)
		{
		print ($warning);
		}
	}


# 7. Perform -update function

if ($update || $debugUpdate)
	{
	foreach my $SOURCE_FILE (sort keys %FilenamePolicyWarnings)
		{
		if (!(open SOURCE_FILE, "< $SOURCE_FILE"))
			{				
			print ("ERROR: Could not open $SOURCE_FILE to read.\n");
			next;
			}

		print ("Updating: $SOURCE_FILE\n");

		my $lineNumbersHashRef = $FilenamePolicyWarnings{$SOURCE_FILE};
		my $lineNumber = 0;
		my @newSourceFile;

		while (my $line = <SOURCE_FILE>)
			{
			$lineNumber++;

			if ($$lineNumbersHashRef{$lineNumber})
				{
				my $textToChangeHashRef = $$lineNumbersHashRef{$lineNumber};

				# We need to order the updates on a per-line basis so that, for example,
				# a search and update for 'nkern\arm\' occurs after one for 'include\nkern\arm\nk_plat.h'
				# We can do this by length, making sure the longest updates are performed first
				my @orderedChanges = sort {length $b <=> length $a} (keys %{$textToChangeHashRef});

				foreach my $text (@orderedChanges)
					{
					my $revisedText = eval(qq(qq/$text/));
					$revisedText =~ s/\\\\/\//g;	# Convert "\\" to "/" first
					$revisedText =~ s/\\/\//g;
					$revisedText = lc $revisedText;
#	Not sure why the following *isn't* required
#					$revisedText = quotemeta($revisedText);
					$line =~ s/$text/$revisedText/;
					}
				}

			push @newSourceFile, $line;
			}

		close SOURCE_FILE;

		if ($debugUpdate)
			{
			# Don't touch the original source, but create two trees for easy comparison
				
			my $baseDir = $SOURCE_FILE;
			$baseDir =~ s/\\\w+\.\w+$//;
				
			mkpath ("\\compare\\orig".$baseDir);
			mkpath ("\\compare\\updated".$baseDir);
			copy ($SOURCE_FILE, "\\compare\\orig".$SOURCE_FILE);
			$SOURCE_FILE = "\\compare\\updated".$SOURCE_FILE;
			}

		if (!(open SOURCE_FILE, "> $SOURCE_FILE"))
			{				
			print ("ERROR: Could not open $SOURCE_FILE to write.\n");
			next;
			}

		foreach my $line (@newSourceFile)
			{
			print (SOURCE_FILE $line);
			}

		close SOURCE_FILE;
		}
	}

__END__

:endofperl
