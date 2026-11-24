# EXTMAKE.PL
#
# Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
#

# Will Create forwarding makefiles for makefiles.
# The forwarding makefiles allow the makefiles which actually do some work to be switched on or off.
# The behaviour depends on various variables such as the platform ARM4T (and sub platforms ARMI/ARM4/THUMB) etc.
# See design documentation for furthur info.


# all variables called *Path* are set up to end with a backslash
# all variables called *Path or *File are stored as absolute (file)paths within makmake
# all variables called UpPath* are stored as relative paths within makmake


use FindBin;		# for FindBin::Bin
use Getopt::Long;

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
use E32env;
use E32Plat;
use E32Variant;
use Genutl;
use Modload;
use Pathutl;
use Trgtype;
use Output;


# THE MAIN PROGRAM SECTION
##########################

{
	Load_SetModulePath($PerlLibPath);
	Plat_Init($PerlLibPath);
}


{

	my %Options;
	

	# -d pathname to makefile 
	# -f file name of makefile
	# -c This is the line used to do the forwarding to the extension makefile. 
	# -allowable arm4+armi+thumb => dictates what forwarding makefiles can be generated. Dependent on PRJ_PLATFORMS flags.
	# -arm => that module should be built for ARMI. (-arm normaly indicates BUILD_AS_ARM in the bld.inf file.)
	# -arm4t => Creating an ARM4T build platform. Which platform we are creating the forwarding makefile is what remains on the 
	#		command line should be ARMI/THUMB/ARM4.
	# -ithumb => override the BUILD_AS_ARM options ensure that everything that can be will be build as THUMB when built. 
	#		Note Kernal code will not build when an attempt to build is made.
	#		This is rather like removing every BUILD_AS_ARM and BUILD_ALWAYS_AS_ARM from the build files. 
	# -iarm => override the base options ensure that everything that can be will be build as ARMI when built. 
	#		This rather like putting BUILD_AS_ARM for the MMP file in the BLD.inf files.

	unless (GetOptions(\%Options, 'd=s' , 'f=s' , 'c=s', 'allowable=s' , 'arm' , 'arm4t' , 'ithumb' , 'iarm' )) {
		exit 1;
	}



	# Should have filename platform 
	# Note never called except via abld.
	
	if (@ARGV!=1)
	{	# indicate an error.
		exit 1;
	}

	my $ForwardingPath = uc($Options{d} );
	my $ForwardindFilename = uc( $Options{f} ) ;
	my $Command = $Options{c};
	
	my $Platform = uc($ARGV[0]) ;

	my $Ret = 0;
	if ( !$Options{arm4t} )
	{	# Not an arm4t build so must be something like thumb wins etc so just build makefile for specified platform that calls the extension makefile.		
		$Ret = GenerateMakefile( $ForwardingPath, $ForwardindFilename , $Command ,  $Platform , 1 , $Options{v}  );
	}
	else
	{
		my $Call = &IsExtensionMakefileCallable( \%Options , $Platform , $ForwardingPath, $ForwardindFilename );
		$Ret = GenerateMakefile( $ForwardingPath, $ForwardindFilename , $Command , $Platform , $Call , $Options{v} );
	}
		
	exit !($Ret);
}



#
# Note we always use a gnumakefile as the forwarding makefile.
#

# Create the forwading makefile.
# If the build is not allowed then we will create a blank makefile. Code will be cenerated that will 
# not pass on a request to build to the working makefiles.
# If the build is allowed then lines will be generated that allow the working makefiles to be called. 

sub GenerateMakefile
{
	my ( $ForwardingPath , $ForwardindFilename , $Command ,  $Platform , $GenerateMakefile , $Display )=@_;
	my $Ret=1;
		
	if ( $GenerateMakefile==0 ) { # Create a makefile which actually does no work. These represent builds that we do not want making. 
		GenerateNULLMakefile( );
	}
	else { # Create a makefile which will actually call the extension makefile. 
		GenerateForwardingMakefile( $Command );
	}
	
	$Ret = SaveMakefile( $ForwardingPath."\\".$ForwardindFilename , $Display);
	
	return $Ret;
}



sub GenerateNULLMakefile
{
	
	&Output("all:\n");
	&Output("	\n");
		# Just matches any call to the make file with nothing.

	&Output("%::\n");
	&Output("	\n");
		# Just matches any call to the makefile with any (or more) rules.
	
}

sub GenerateForwardingMakefile
{
	my ($Command)=@_;

	&Output("unexport MAKEFLAGS");
	&Output("\n");

	&Output("\n");
	&Output("all:\n");
	&Output("\t$Command\n"); 

	&Output("\n");
	
	&Output("%::\n");
	&Output("\t$Command\n"); 
}


sub IsARM4TBuild {
	my ( $refOptions )= @_;
	my $ret = $refOptions->{arm4t};
	return $ret;
}

sub KernalTarget() {
	my ( $ForwardingPath, $ForwardindFilename )= @_;
	my $ret=0;
	
	if ( ( uc($ForwardingPath) =~ /\\BEECH\\GENERIC\\BASE\\BOOTSTRAP\\/ ) && (uc($ForwardindFilename) eq "BOOTCPU.MKE") )
	{
		$ret=1;
	}

	return $ret;
}



#
# $Work==1 => the makefile will do some work.
#

sub IsExtensionMakefileCallable
{
	my ( $refOptions , $Platform , $ForwardingPath , $ForwardindFilename )= @_;
	my $ret=0;
	
	my $IsARM4TBuild=&IsARM4TBuild( $refOptions );

	{	
		# Okay we have the -ARM4t option set this indicates that it may be possible that we do not want to do this build.
		my $Kernal = &KernalTarget( $ForwardingPath , $ForwardindFilename  );
		my $arm=$refOptions->{arm}; # Comes from the command line via the bld.inf and the mmp file.

		if ( $refOptions->{ithumb} )
		{
			if ( ($Kernal) )
			{	# We can not generate a thumb build for kernel code. 
				print "Error : Unable to generate a THUMB platform from kernel code for ARM4T.\n";
				exit 1;
			}
			elsif ( ($Platform eq 'THUMB') )
			{	# Only allow thumb builds, with ithumb override. 
				$ret=1;
			}
			else
			{
				$ret=0;
			}
		}
		elsif (  $refOptions->{iarm} )
		{
			if ( ($Platform eq 'ARMI') )
			{	# Only allow armi builds, with iarm override. 
				$ret=1;
			}
			else
			{
				$ret=0;
			}
		}
		else
		{	# No override in progress. 
			if ( ($Platform eq 'ARM4') && ($Kernal) && ($arm) )
			{	# Can not build the interwoking for ARM4 even if forced to by the -arm option so build.
				$ret=0;
			}
			elsif ( ($Platform eq 'ARM4') && ($Kernal) && !($arm) )
			{ # Requesting that we build ARM4 in the kernal this is an allowable build.
				$ret=1;
			}		
			elsif ( ($Platform eq 'ARM4') && !($Kernal) && ($arm) )
			{ # Requesting that we build ARM4 in the user this is an not an allowable build.
				$ret=0;
			}		
			elsif ( ($Platform eq 'ARM4') && !($Kernal) && !($arm) )
			{ # Requesting that we build ARM4 in the user this is an not an allowable build.
				$ret=0;
			}		
			elsif ( ($Platform eq 'THUMB') && ($Kernal) && ($arm) )
			{ # Requesting that we build interwoking for THUMB in the kernal code. This is not an allowable build probally ebven a mistake. 
				$ret=0;
			}		
			elsif ( ($Platform eq 'THUMB') && ($Kernal) && !($arm) )
			{ # Requesting that we build THUMB in the user this is an not an allowable build. Probaly even a mistake.
				$ret=0;
			}		
			elsif ( ($Platform eq 'THUMB') && !($Kernal) && ($arm) )
			{ # Requesting that we build interwoking for THUMB in the user code. This is not an allowable build.
				$ret=0;
			}		
			elsif ( ($Platform eq 'THUMB') && !($Kernal) && !($arm) )
			{ # Requesting that we build THUMB in the user. This is an allowable build.
				$ret=1;
			}		
			elsif ( ($Platform eq 'ARMI') && ($Kernal) && ($arm)  )
			{ # Kernal code and requesting arm build.
				$ret=1;
			}		
			elsif ( ($Platform eq 'ARMI') && ($Kernal) && !($arm)  )
			{ # Kernal code and no request for -arm should build arm4.
				$ret=0;
			}		
			elsif ( ($Platform eq 'ARMI') && !($Kernal) && ($arm)  )
			{ # User code and requesting armi.
				$ret=1;
			}		
			elsif ( ($Platform eq 'ARMI') && !($Kernal) && !($arm)  )
			{ # 
				$ret=0;
			}		
			else
			{ # probably an error.
				$ret=0;
				print "Error : Invalid build specifications for ARM4T build. The build $Platform is not valid\n";
				exit 1;
			}
		}
	}
	
	return $ret;
}



sub SaveMakefile
{
	my ($MAKEFILE , $Display)=@_;
	my $Ret=1;
	
	# open the makefile and write all the text it requires to it if makmake has so far been successful
	#-------------------------------------------------------------------------------------------------
	eval { &Path_MakePathL($MAKEFILE); };
	die $@ if $@;
	
	if ($Display) {
		print "Creating: \"$MAKEFILE\"\n";
	}
	open MAKEFILE,">$MAKEFILE" or die "ERROR: Can't open or create file \"$MAKEFILE\"\n";
	print MAKEFILE &OutText or die "ERROR: Can't write output to file \"$MAKEFILE\"\n";
	close MAKEFILE or die "ERROR: Can't close file \"$MAKEFILE\"\n";
	if ($Display) {
		print "Successful MakeFile Creation\n";
	}
	
	return $Ret;
}
