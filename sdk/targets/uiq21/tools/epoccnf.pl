# epoccnf.pl
#
# Copyright (c) 2001 Symbian Ltd.  All rights reserved.
#
# Wrapper to support the EPOC extended makefile Compiler

use Cwd;		# for cwd
use FindBin;		# for FindBin::Bin
use File::Copy;		# for copy()

my $uppath="x";	    	# will be initialised when first needed
my $PerlBinPath;	# fully qualified pathname of the directory containing this script

my $epocroot = $ENV{EPOCROOT};
die "ERROR: Must set the EPOCROOT environment variable\n" if (!defined($epocroot));
$epocroot =~ s-/-\\-go;	# for those working with UNIX shells
die "ERROR: EPOCROOT must not include a drive letter\n" if ($epocroot =~ /^.:/);
die "ERROR: EPOCROOT must be an absolute path without a drive letter\n" if ($epocroot !~ /^\\/);
die "ERROR: EPOCROOT must not be a UNC path\n" if ($epocroot =~ /^\\\\/);
die "ERROR: EPOCROOT must end with a backslash\n" if ($epocroot !~ /\\$/);
die "ERROR: EPOCROOT must specify an existing directory\n" if (!-d $epocroot);

$epocroot=~ s-\\$--;		# chop trailing \\

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
  epoccnf [options] srcfile [-o outputfile]

Compile an EPOC resource file, optionally generating a compiled resource
file and an associated header file.

The available options are

   -t[Temporary directory]		  -- temporary directory
   -l[Target directory:Working directory] -- if specified, captures all source to \\epoc32\\localisation\\...
   -c[path including filename]		  -- path of compiled cnf file
   -v 					  -- verbose

The resource file is first passed through the C++ preprocessor, using any
specified preprocessor arguments, and then compiled with RCOMP.EXE to
generate a compiled resource, it is then compiled with CNFTOOL.EXE to produce
a .cnf file.

All intermediate files are generated into a temporary directory.

USAGE_EOF
	}

#-------------------------------------------------------
# Process commandline arguments
#
# Can't use the Getopt package because it doesn't like the -D and -I style options
#
my $sourcefile="";
my $opt_l="";
my $tmpdir="";
my $opt_v=0;

my $cpp_spec= "cpp -undef -C ";	    # preserve comments

my $errors = 0;
while (@ARGV)
	{
	my $arg = shift @ARGV;
	if ($arg =~ /^-v$/)
		{
		$opt_v =1;
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
	if ($arg =~ /^-c(.*)$/)
		{
		$opt_c =$1;
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
my $rpp_name = $tmpdir . $rssfile . ".rpp";
my $rsc_name = $tmpdir . $rssfile . ".rsc";

if ($opt_v)
	{
	print "* Source file\t\t: $sourcefile\n";
	print "* Temp. .RSC file\t: $rsc_name\n";
	print "* Temp. .RPP file\t: $rpp_name\n";
	print "* .CNF location\t\t: $opt_c\n";
	print "* localisation dets.\t: $opt_l\n";
	print "* Temp. directory\t: $tmpdir\n";
	}

#-------------------------------------------------------
# Run the preprocessor
#
## Creates the .rpp file

$cpp_spec .= "-I $PerlBinPath\\..\\include ";	# path to support shared tools
$cpp_spec .= "-D_UNICODE ";
$cpp_spec .= "<\"$sourcefile\"";

open RPP, ">$rpp_name" or die "* Can't write to $rpp_name";
open CPP, "$cpp_spec |" or die "* Can't execute cpp";
my $line;

while ($line=<CPP>)
	{
	print RPP $line;
	}
close RPP;
close CPP;

my $cpp_status = $?;
die "* cpp failed\n" if ($cpp_status != 0);

#-------------------------------------------------------
# Copy .rpp and .rss file to epoc32\localisation
#

if ($opt_l ne "")
	{
	&Lockit_SrcFile($rssfile, $rpp_name, $opt_l, "CNF", "");
	}

#-------------------------------------------------------
# Run the resource compiler
#

my $rcomp_spec = "rcomp ";
$rcomp_spec .= "-u -o\"$rsc_name\" -s\"$rpp_name\" -i\"$sourcefile\"";

if ($opt_v)
	{
	print "\n* generating rsc file\n" if ($opt_v);
	print "*** $rcomp_spec\n" if ($opt_v);
	}
system($rcomp_spec);
if ($? != 0)
	{
	print "* RCOMP failed - deleting output files\n";
	unlink $rpp_name;
	exit 1;
	}
print "* deleting $rpp_name\n" if ($opt_v);
unlink $rpp_name;

#-------------------------------------------------------
# Run the cnftool compiler

my $cnftool_spec = "";
$cnftool_spec = "$epocroot\\epoc32\\release\\winc\\udeb\\cnftool.exe";
$cnftool_spec .= " $rsc_name $opt_c";

print "\n* generating cnf file\n" if ($opt_v);
print "*** $cnftool_spec\n\n" if ($opt_v);

system($cnftool_spec);
if ($? != 0)
	{
	print "*** CNFTOOL failed - deleting output files\n";
	unlink $rsc_name;
	exit 1;
	}
print "* deleting $rsc_name\n" if ($opt_v);
unlink $rsc_name;
exit 0;


#-------------------------------------------------------
# Subroutine: convert possibly absolute path into relative path
#

sub quoted_relative_path
    {
    my ($arg) = @_;
    return "\"$arg\"" if ($arg !~ /^\\/);	# not an absolute path
    if ($uppath eq "x")
	{
	$uppath=cwd;
	$uppath=~s-/-\\-go;		    # separator from Perl 5.005_02+ is forward slash
	$uppath=~s-^(.*[^\\])$-$1\\-o;	    # ensure path ends with a backslash
	$uppath=~s-\\([^\\]+)-\\..-og;	    # convert directories into ..
	$uppath=~s-^.:\\--o;		    # remove drive letter and leading backslash
	}
    $arg=~s-^\\--o;	# remove leading backslash from original path
    return "\"$uppath$arg\"";
    }
