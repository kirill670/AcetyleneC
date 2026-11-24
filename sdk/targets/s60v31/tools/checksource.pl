# CHECKSOURCE.PL
#
# Copyright (c) 2005 Symbian Software Ltd.  All rights reserved.
#

# Front-end to routines checking that source matches Symbian's filename policy

use FindBin;
use Cwd;
use Getopt::Long;
use lib $FindBin::Bin;
use CheckSource;
use Pathutl;

my $preprocessCall = "cpp.exe -w -undef -nostdinc -+ -dI";


my $preprocess = 0;
my $parsefile = 0;

GetOptions ('preprocess|pp' => \$preprocess, 'parsefile|pf' => \$parsefile);

my %warnings;


if (!@ARGV)
	{
	print ("\nchecksource.pl - [-preprocess|-parsefile] args\n");
	}
elsif ($preprocess)
	{
	my $PREPROCESSPIPE;
	open PREPROCESSPIPE,"$preprocessCall @ARGV |" or die "ERROR: Can't invoke preprocessor for \"-checksource\".\n";

	my $lineNumber = 0;
	my $currentFile = "";
	my $warning = "";

	while (<PREPROCESSPIPE>)
		{
		if (/^\s*$/o)
			{
			$lineNumber++;
			next;
			}	
		elsif (/^# (\d+) "(.*)"( \d+)?/o)
			{
			$lineNumber = scalar $1;
			$currentFile=$2;
			$currentFile=~s-\\\\-\\-go;
			$currentFile=~s-\\\/-\\-go;
			$currentFile=~s-\/\\-\\-go;
			$currentFile=~s-\/\/-\\-go;
			$currentFile=~s/\//\\/g;
			next;
			}
		elsif (/^\s*#include\s*[\"|\<]{1}/)
			{
			chomp ($_);
			CheckSource_CaseAndDelimiter($currentFile, $_, $lineNumber, %warnings, 1);
			}

		$lineNumber++
		}

	close PREPROCESSPIPE;
	}
elsif ($parsefile)
	{
	my $SOURCE_FILE = $ARGV[0];		
	open SOURCE_FILE, "< $SOURCE_FILE" or die "ERROR: Can't open $SOURCE_FILE for \"-checksource\".\n";

	my $lineNumber = 0;
	
	while (<SOURCE_FILE>)
		{
		$lineNumber++;

		if (/(^\s*#include\s*[\"|\<]{1}\S+[\"|\>]{1})/)
			{
			CheckSource_CaseAndDelimiter($SOURCE_FILE, $1, $lineNumber, %warnings, 1);
			}		
		}

	close SOURCE_FILE;
	}


print "$_\n" foreach (sort keys %warnings);
