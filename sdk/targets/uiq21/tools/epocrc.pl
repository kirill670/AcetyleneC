# epocrc.pl
#
# Copyright (c) 2000 Symbian Ltd.  All rights reserved.
#

# Wrapper to support the EPOC Resource Compiler

use Cwd;		# for cwd
use FindBin;		# for FindBin::Bin
use File::Copy;		# for copy()

my $curdrive="x";	    	# will be initialised when first needed
my $PerlBinPath;	# fully qualified pathname of the directory containing this script

# establish the path to the Perl binaries
BEGIN {
	require 5.005_03;		# check user has a version of perl that will cope
	$PerlBinPath = $FindBin::Bin;	# X:/epoc32/tools
	$PerlBinPath =~ s/\//\\/g;	# X:\epoc32\tools
}
use lib $PerlBinPath;
use lockit_info;

sub print_usage
	{
#........1.........2.........3.........4.........5.........6.........7.....
	print <<USAGE_EOF;

Usage:
  epocrc [options] srcfile [-ooutputfile] [-hheaderfile] [-l "TargetPath:CWDir"]  

Compile an EPOC resource file, optionally generating a compiled resource 
file and an associated header file.

The available options are

   -Dxxx, -Ixxx      -- C++ preprocessor arguments
   -u                -- compile for use with Unicode EPOC
   -ttmpdir          -- specify a directory for temporary files
   -nocpp            -- do not call C++ preprocessor
   -l                -- if specified, capture all source to \\epoc32\\localisation\\... 

The resource file is first passed through the C++ preprocessor, using any 
specified preprocessor arguments, and then compiled with RCOMP.EXE to 
generate a compiled resource and the associated header file. 

All intermediate files are generated into a temporary directory.

USAGE_EOF
	}

#-------------------------------------------------------
# Process commandline arguments
#
# Can't use the Getopt package because it doesn't like the -D and -I style options
#
my $sourcefile="";
my $opt_o="";
my $opt_h="";	
my $opt_l="";
my $tmpdir="";
my $unicode=0;
my $opt_v=0;
my $opt_cpp = 1;

my $cpp_spec= "cpp -undef -C ";	    # preserve comments

my $errors = 0;
while (@ARGV)
	{
	my $arg = shift @ARGV;
	if ($arg =~ /^-D(.*)$/)
		{
		if ($1 eq "")
		    {
		    $arg = shift @ARGV;
		    $cpp_spec .= "-D \"$arg\" ";
		    }
		else
		    {
		    $cpp_spec .= "$arg ";
		    }
		next;
		}
	if ($arg =~ /^-I-$/)
		{
		$cpp_spec .= "-I- ";
		next;
		}
	if ($arg =~ /^-I(.*)$/)
		{
		$cpp_spec .= "-I ";
		if ($1 eq "")
		    {
		    $arg = shift @ARGV;
		    }
		else
		    {
		    $arg = $1;
		    }
		$cpp_spec .= quoted_path($arg)." ";
		next;
		}
	if ($arg =~ /^-v$/)
		{
		$opt_v =1;
		next;
		}
	if ($arg =~ /^-nocpp$/)
		{
		$opt_cpp =0;
		next;
		}
	if ($arg =~ /^-u$/)
		{
		$unicode =1;
		next;
		}
	if ($arg =~ /^-o(.*)$/)
		{
		$opt_o =$1;
		next;
		}
	if ($arg =~ /^-h(.*)$/)
		{
		$opt_h =$1;
		next;
		}
	if ($arg =~ /^-t(.*)\\?$/)
		{
		$tmpdir ="$1\\";
		next;
		}
	if ($arg =~ /^-l(.*)$/)
		{
		$opt_l =$1;
		next;
		}

	if ($arg =~ /^-/)
		{
		print "Unknown arg: $arg\n";
		$errors++;
		next;
		}
	$sourcefile=$arg;
	}

if ($errors || $sourcefile eq "")
	{
	print_usage();
	exit 1;
	}

use File::Basename;
my $rss_base = basename($sourcefile);
my ($rssfile) = split(/\./, $rss_base);	    # remove extension
my $rpp_name = $tmpdir. $rssfile . ".rpp";
my $outputfile=$opt_o;	
my $headerfile=$opt_h;

if ($opt_v)
	{
	print "* Source file:   $sourcefile\n";
	print "* Resource file: $outputfile\n" if ($outputfile ne "");
	print "* Header file:   $headerfile\n" if ($headerfile ne "");
	}

$opt_o = "-o\"$outputfile\"" if ($outputfile ne "");
$opt_h = "-h\"$headerfile\"" if ($headerfile ne "");


#-------------------------------------------------------
# Run the preprocessor
#

if($opt_cpp) 
	{
	$cpp_spec .= "-D_UNICODE " if ($unicode);
	
	$cpp_spec .= quoted_path($sourcefile) ." -o ". quoted_path($rpp_name);

	print "* $cpp_spec\n" if ($opt_v);
	system($cpp_spec);

	my $cpp_status = $?;
	die "* cpp failed\n" if ($cpp_status != 0);
	}


#-------------------------------------------------------
# Copy rpp files to epoc32\localisation
#

if ($opt_l ne "")
	{
	&Lockit_SrcFile($rssfile, $rpp_name, $opt_l, "RSC", "");
}

#-------------------------------------------------------
# Merge rls strings to rpp
#

my $line;
my $StringId;
my $key;
my $value;
my $StringToSubstitute;
my %ResourceString;

print "* merging text strings to $rpp_name\n" if ($opt_v);

open NEWRPP, ">$rpp_name.new" or die "* Can't write to $rpp_name.new";
open RPP, "$rpp_name" or die "* Can't open $rpp_name";

while ($line = <RPP>) 	{
	while (($StringId, $StringToSubstitute)=each %ResourceString)
	{
		$line=~s/\b$StringId\b/$StringToSubstitute/g if ($line !~ /^rls_string/);
	}

	# find quoted "" strings
	if($line =~ /^rls_string\s+(\S+)\s+(.*$)/)
	{
		my $text = $2;
		$key = $1;
		$line=~s/(.*)/\/\/$1/;
		my $substr_count = 0;
		if(!exists $ResourceString{$key})
		{
		SUBSTR:	while (1)
		{
			# find quoted "" strings e.g. "hello"
			if($text =~ /^(\s*\"(.*?\\.)*.*?\")/)		
			{
				$value = $1;
				$text = $';
				++$substr_count;
			}

			# find quoted '' strings. e.g. 'world'
			elsif($text =~ /^(\s*\'(.*?\\.)*.*?\')/)			
			{
				$value = $1;
				$text = $';
				++$substr_count;
			}

			# find hex strings e.g. <0x34><0x45><0x65>
			elsif($text =~ /^(\s*(<.*?>)+)/)		
			{
				$value = $1;
				$text = $';
				++$substr_count;
			}

			# find c comment e.g. /*hello world*/ (may exist between strings)
			elsif($text =~ /^(\s*\/\*.*?\*\/)/)		
			{
				$text = $';
				next SUBSTR; # ignore embedded comment
			}

			# find c++ comment e.g. //hello world (may exist after strings)
			elsif($text =~ /^(\s*\/\/.*$)/)		
			{
				$text = $';
				next SUBSTR; # ignore trailing comment
			}

			# exit search
			else
			{
				if ($substr_count == 0)
				{
					warn("WARNING: rls_string $key either has incorrect syntax or no value\n");
				}
				last SUBSTR;
			}
		$ResourceString{$key} .= $value;
		}
	  	}
	}
	print NEWRPP $line;
}

	
close RPP;
close NEWRPP;
copy ("$rpp_name.new", "$rpp_name");
unlink ("$rpp_name.new");

#-------------------------------------------------------
# Run the resource compiler
#

my $rcomp_spec = "rcomp ";
$rcomp_spec .= "-u " if ($unicode);
$rcomp_spec .= "$opt_o $opt_h -s\"$rpp_name\" -i\"$sourcefile\"";

print "* $rcomp_spec\n" if ($opt_v);
system($rcomp_spec);
if ($? != 0)
	{
	print "* RCOMP failed - deleting output files\n";
	unlink $outputfile if ($outputfile ne "");
	unlink $headerfile if ($headerfile ne "");
	exit 1;
	}
print "* deleting $rpp_name\n" if ($opt_v);
unlink $rpp_name;
exit 0;


#-------------------------------------------------------
# Subroutine: convert path into something acceptable to CPP.EXE
#

sub quoted_path
    {
    my ($arg) = @_;
    return "\"$arg\"" if ($arg !~ /^\\[^\\]/);	# not an absolute path
    if ($curdrive eq "x")
		{
		$curdrive="";
		$curdrive=$1 if (cwd =~ /^(.:)/);	
		}
    return "\"$curdrive$arg\"";
    }

