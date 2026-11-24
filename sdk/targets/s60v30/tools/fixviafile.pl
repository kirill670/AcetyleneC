# FIXVIAFILE.PL
#
# Copyright (c) 2004 Symbian Software Ltd.  All rights reserved.
#

# Perl script to resolve issue with ARMLINK "via" files in RVCT 2.1 Build 416 tools
# Any two adjacent "words" in a via file that, when combined, exceed 340 characters,
# need to have a benign command line argument inserted between them.

use FindBin;		# for FindBin::Bin

my $PerlLibPath;    # fully qualified pathname of the directory containing our Perl modules

BEGIN {
# check user has a version of perl that will cope
	require 5.005_03;
# establish the path to the Perl libraries: currently the same directory as this script
	$PerlLibPath = $FindBin::Bin;	# X:/epoc32/tools
	$PerlLibPath =~ s/\//\\/g;	# X:\epoc32\tools
	$PerlLibPath .= "\\";
}

use lib $PerlLibPath;

use Armutl;

my $fixedViaFile;
my $previousWordLength = 0;

my $viaFile = $ARGV[0];
if (!$viaFile)
	{
	die "ERROR: No via file specified to fixup.\n";
	}

my $oP = '--';
$oP = '-' if (Armutl_RVCTMajorVersion() == 2 && Armutl_RVCTMinorVersion() < 2);

open (CURRENTVIAFILE, $viaFile) || die "ERROR: Unable to open via file : $viaFile.\n";
while (my $line = <CURRENTVIAFILE>)
	{		
	while ($line =~ /\S+\s+/g)
		{
		my $word = $&;
		my $wordLength = length ($word);

		if ($previousWordLength && ($previousWordLength + $wordLength) > 340)
			{
			$fixedViaFile .= "${oP}diag_suppress 6331 ";
			}

		$fixedViaFile .= $word;
		$previousWordLength = $wordLength;
		}
	}
close (CURRENTVIAFILE);

open (NEWVIAFILE, ">".$viaFile) || die "ERROR: Unable to create via file : $viaFile.\n"; 
print (NEWVIAFILE $fixedViaFile);
close (NEWVIAFILE);

