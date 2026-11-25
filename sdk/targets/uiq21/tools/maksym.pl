# maksym.pl
#
# Copyright (c) 1996-1999 Symbian Ltd.  All rights reserved.
#

#
# Produces symbolic information given a ROM image
#

require 5.003_07;
no strict 'vars';
use English;
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
use Modload;
Load_SetModulePath($PerlLibPath);

# Globals
my $maksym = "";
my $rombuild;
my $debug = 0;

&args;
&main;

exit 0;


#
# main
#
sub main
  {
	my $file;
	my $mapfile;
	my $mapfile2;
	my $text;

	open (ROM, "<$rombuild")
	  or die "ERROR: Can't open rombuild log file \"$rombuild\"\n";
	if ($maksym ne "")
	    {
	    open (SYM, ">$maksym")
	      or die "ERROR: Can't open output file \"$maksym\"\n";
	    print "Creating $maksym...\n"
	    }

	while (<ROM>)
	  {
		# Start of ROM
		if (/^Creating Rom image (\S*)/)
		  {
		  if ($maksym eq "")
		      {
		      # For backwards compatibility, replace trailing .img with .symbol
		      # if no trailing .img, just append .symbol anyway
		      $maksym = $1;
		      $maksym =~ s/(\.img)?$/.symbol/i;
		      close SYM;
		      open (SYM, ">$maksym")
			or die "ERROR: Can't open output file \"$maksym\"\n";
		      print "\nCreating $maksym...\n"
		      }
		  next;
		  }
		# end of ROM
		if (/^Writing Rom image/)
		  {
		  close SYM;
		  $maksym = "";
		  next;
		  }
		# Data file
		if (/^Reading resource (.*) to rom linear address (.*)/)
		  {
			$file = $1;
			my $data = hex($2);
			$file =~ /([^\\]+)$/;
			printf SYM "\nFrom    $file\n\n%08x    0000    $1\n", $data;
		  }
		# Executable file
		elsif (/^Processing file (.*)/)
		  {
			$file = $1;
			$text = 0;
			my $codesize = 0;

			# Work out final addresses of sections
			while (defined($_=<ROM>) && !/^$/)
			  {
				if (/^Code start addr:\s+(\w+)/)
				  {
					$text = hex($1);
				  }
				if (/^Code size:\s+(\w+)/)
				  {
					$codesize = hex($1);	# text + rdata
				  }
			  }

			# Sanity check - text section can't be zero
			die "ERROR: Can't find rombuild info for \"$file\"\n"
			  if (!$text);

			print SYM "\nFrom    $file\n\n";

			# Look in map file for symbols in .text and relocate them
			$mapfile2 = $file.".map";			
			$mapfile = $file;
			$mapfile =~ s/\.\w+$/\.map/;			
			if (!(open (MAP, "$mapfile2") || open (MAP, "$mapfile")))
			  {
				print "$file\nWarning: Can't open \"$mapfile2\" or \"$mapfile\"\n";
				$file =~ /([^\\]+)$/;
				printf SYM "%08x    0000    $1\n", $text;
			  }
			else
			  {
				my $imgtext;
				my $textlen;
				my %syms;
				my $stubhex=1;

				# Find text section
				while (defined($_=<MAP>) && !(/^\.text\s+/))
				  {};

				/^\.text\s+(\w+)\s+(\w+)/
				  or die "ERROR: Can't get .text section info for \"$file\"\n";
				$imgtext=hex($1);
				$textlen=hex($2);
				$syms{$imgtext+$codesize} = ' ';	# impossible symbol as end marker

				print "$file\n";

				# Slurp symbols 'til the end of the text section
				while (defined($_=<MAP>))
				  {
				  	# blank line marks the end of the text section
				  	last if (/^$/);
				  	  
					# .text <addr> <len>  <library(member)>
					# .text$something
					#       <addr> <len>  <library(member)>
					#       <addr> <len>  LONG 0x0
					if (/^\s(\.text)?\s+(0x\w+)\s+(0x\w+)\s+(.*)$/io)
					  {
					    my $address = hex($2);
					    my $length = hex($3);
					    my $libraryfile = $4;
					    next if ($libraryfile =~ /^LONG 0x/);
					    $syms{$address+$length} = ' ';	# impossible symbol as end marker
					    
						# EUSER.LIB(ds01423.o)
						# EUSER.LIB(C:/TEMP/d1000s_01423.o)					    
					    if ($libraryfile =~ /.*lib\(.*d\d*s_?\d{5}.o\)$/io)
					      {
						    $stubhex=$address;
						  }
						next;
					  }
					
					#  <addr>  <symbol name possibly including spaces>
					if (/^\s+(\w+)\s\s+([a-zA-Z_].+)/o)
					  {
					    my $addr = hex($1);
					    my $symbol = $2;
						$symbol = "stub $symbol" if ($addr == $stubhex);
						$syms{$addr} = $symbol;
						next;
					  }
				  }				

				# Write symbols in address order
				@addrs = sort keys %syms;
				for ($i = 0; $i < @addrs - 1; $i++)
				  {
				    my $symbol = $syms{$addrs[$i]};
				    next if ($symbol eq ' ');
					printf SYM "%08x    %04x    %s\n",
					  $addrs[$i]-$imgtext+$text, $addrs[$i+1]-$addrs[$i], $symbol;
				  }
				# last address assumed to be imgtext+lentext

				close MAP;
			  }
		  }
	  }
	close SYM;
	close ROM;
  }

#
# args - get command line args
#
sub args
  {
	my $arg;
	my @args;
	my $flag;

	&help if (!@ARGV);
		
	while (@ARGV)
	  {
		$arg = shift @ARGV;

		if ($arg=~/^[\-\/](\S*)$/)
		  {
			$flag=$1;
			
			if ($flag=~/^[\?h]$/i)
			  {
				&help;
			  }
			elsif ($flag=~/^d$/i)
			  {
				$debug = 1;
			  }
			else
			  {
				print "\nERROR: Unknown flag \"-$flag\"\n";
				&usage;
				exit 1;
			  }
		  }
		else
		  {
			push @args,$arg;
		  }
	  }

	if (@args)
	  {
		$rombuild = shift @args;
		if (@args)
		  {
			$maksym = shift @args;
			if (@args)
			  {
				print "\nERROR: Incorrect argument(s) \"@args\"\n";
				&usage;
				exit 1;
			  }
		  }
	  }
  }

sub help ()
  {
	my $build;

	&Load_ModuleL('E32TPVER');
	print "\nmaksym - Produce symbolic information given a ROM image (Build ",
	  &E32tpver, ")\n";
	&usage;
	exit 0;
  }

sub usage ()
  {
	print <<EOF

Usage:
  maksym <logfile> [<outfile>]

Where:
  <logfile>   Log file from rombuild tool.
  <outfile>   Output file. Defaults to imagename.symbol.
EOF
  ;
	exit 0;
  }
