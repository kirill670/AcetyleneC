# BLDMAKE.PL
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
#


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

sub ExportDirs ($);

use lib $PerlLibPath;
use E32env;
use E32Plat;
use Modload;
use Output;
use Pathutl;
use E32Variant;

my %Options;
my %KeepGoing;
my @DefaultPlats=('WINS', 'ARMI', 'ARM4', 'THUMB', 'WINSCW', 'ARM4T', 'GCCXML' );
# 'ARM4T' is not a default platform and is removed later. 

my $variantMacroHRHFile = Variant_GetMacroHRHFile();

# THE MAIN PROGRAM SECTION
##########################

{
	Load_SetModulePath($PerlLibPath);
	Plat_Init($PerlLibPath);

#	process the commmand-line
	unless (GetOptions(\%Options, 'v', "k|keepgoing", "notest")) {
		exit 1;
	}
	unless (@ARGV>=1) {
		&Usage();
	}
	my $Command=uc shift @ARGV;
	unless ($Command=~/^(BLDFILES|CLEAN|INF|PLAT)$/o) {
		&Usage();
	}
	my $CLPlat=uc shift @ARGV;

	unless ($CLPlat) {
		$CLPlat='ALL';
	}

	if ($Command eq 'INF') {
		&ShowBldInfSyntax();
		exit;
	}

	if ($Command eq 'PLAT') {
		my @PlatList = ($CLPlat);
		my $PlatName;
		if ($CLPlat eq "ALL") {
			@PlatList = &Plat_List();
			print(
				"Supported Platforms:\n",
				"  @PlatList\n\n"
			);
		}
		print(
			"Macros defined for BLD.INF preprocessing of MMPFILE sections:\n"
		);
		foreach $PlatName (@PlatList) {
			my %Plat;
			eval { &Plat_GetL($PlatName, \%Plat); };
			die $@ if $@;
			print(
				"\nPlatform $PlatName:\n",
				"  @{$Plat{MmpMacros}}\n"
			);
		}
		exit;
	}


#	check that the BLD.INF file exists
#	maybe BLDMAKE should allow a path to be specified leading to the BLD.INF file
	my $BldInfPath=&Path_WorkPath;
	unless (-e "${BldInfPath}BLD.INF") {
		&FatalError("Can't find \"${BldInfPath}BLD.INF\"");
	}

	if (!-d $E32env::Data{EPOCPath}){
		&FatalError("Directory \"$E32env::Data{EPOCPath}\" does not exist");
	}

#	decide the output directory
	my $OutDir=&Path_Chop($E32env::Data{BldPath}).$BldInfPath;

#	Work out the path for the IBY files
	my $RomDir=&Path_Chop($E32env::Data{RomPath}).$BldInfPath;

#	Work out the name for the BLD.INF module
	my @Dirs=&Path_Dirs($BldInfPath);
	my $Module='';
	foreach (@Dirs) {
		$Module.="$_.";
	}
	chop $Module;


	if ($Command eq 'CLEAN') {
		unlink "${BldInfPath}ABLD.BAT";
		$OutDir=~m-(.*)\\-o;
		if (-d $1) { # remove backslash for test because some old versions of perl can't cope
			opendir DIR, $1;
			my @Files=grep s/^([^\.].*)$/$OutDir$1/, readdir DIR;
			closedir DIR;
			unlink @Files;
		}
		exit;
	}

#	parse BLD.INF - to get the platforms and the export files
	eval { &Load_ModuleL('PREPFILE'); };
	&FatalError($@) if $@;

	my @RealPlats=();
	my @Exports=();
	my @TestExports=();
	if ($Options{v}) {
		print "Reading \"${BldInfPath}BLD.INF\" for platforms and exports\n";
	}
	&ParseBldInf(\@RealPlats, \@Exports, \@TestExports, $BldInfPath, 
		$E32env::Data{EPOCIncPath}, $E32env::Data{EPOCPath}, $E32env::Data{EPOCDataPath});
	
#	get any IDE platforms required into a new platforms list, and
#	Create a hash to contain the 'real' names of the platforms, i.e. WINS rather than VC6
	my @Plats=@RealPlats;
	my %Real;
	foreach (@RealPlats) { # hack to get VC6 batch files
		$Real{$_}=$_;
		my $AssocIDE;
		next unless $AssocIDE=&Plat_AssocIDE($_);
		push @Plats, $AssocIDE;
		$Real{$AssocIDE}=$Real{$_};
	}
	if ($Options{v}) {
		print "Platforms: \"@Plats\"\n";
	}

#	check that the platform specified on the command-line is acceptable
#	and sort out a list of platforms to process
	my @DoRealPlats=@RealPlats;
	my @DoPlats=@Plats;
	unless ($CLPlat eq 'ALL') {
		unless (grep /^$CLPlat$/, @Plats) {
			&FatalError("Platform $CLPlat not supported by \"${BldInfPath}BLD.INF\"\n");
		}
		@DoPlats=($CLPlat);
		@DoRealPlats=$Real{$CLPlat};
	}
	undef $CLPlat;
			
#	sort out the export directories we might need to make
	my @ExportDirs=&ExportDirs(\@Exports);
	my @TestExportDirs=&ExportDirs(\@TestExports);

#	parse the BLD.INF file again for each platform supported by the project
#	storing the information in a big data structure
	my %AllPlatData;
	my %AllPlatTestData;
	my $Plat;
	foreach $Plat (@RealPlats) {
		if ($Options{v}) {
			print "Reading \"${BldInfPath}BLD.INF\" for $Plat\n";
		}
		my (@PlatData, @PlatTestData);
		&ParseBldInfPlat(\@PlatData, \@PlatTestData, $Plat, $BldInfPath);
		$AllPlatData{$Plat}=\@PlatData;
		$AllPlatTestData{$Plat}=\@PlatTestData;
	}
	undef $Plat;

	if ($Command eq 'BLDFILES') {

#		create the perl file, PLATFORM.PM, listing the platforms
		if ($Options{v}) {
			print "Creating \"${OutDir}PLATFORM.PM\"\n";
		}
		&CreatePlatformPm($OutDir, \@Plats, \@RealPlats, \%Real, \%AllPlatData, \%AllPlatTestData);

#		create the .BAT files required to call ABLD.PL
		if ($Options{v}) {
			print "Creating \"${BldInfPath}ABLD.BAT\"\n";
		}
		&CreatePerlBat($BldInfPath);

#		create the makefile for exporting files
		if ($Options{v}) {
			print "Creating \"${OutDir}EXPORT.MAKE\"\n";
		}
		&CreateExportMak("${OutDir}EXPORT.MAKE", \@Exports, \@ExportDirs);

#		create the makefile for exporting test files
		if ($Options{v}) {
			print "Creating \"${OutDir}EXPORTTEST.MAKE\"\n";
		}
		&CreateExportMak("${OutDir}EXPORTTEST.MAKE", \@TestExports, \@TestExportDirs);

#		create the platform meta-makefiles
		foreach my $copyofPlat (@DoPlats) {  # Do not use $_ here !!
			if ($Options{v}) {
				print "Creating \"$OutDir$_.MAKE\"\n";
			}
			my $realplat = $Real{$copyofPlat};
 			&CreatePlatMak($OutDir, $E32env::Data{BldPath}, $AllPlatData{$realplat}, $copyofPlat, $realplat, $RomDir, $Module, $BldInfPath, \@Exports, $OutDir, '' , \@DoPlats);
		}
		foreach (@DoPlats) {
			if ($Options{v}) {
				print "Creating \"$OutDir${_}TEST.MAKE\"\n";
			}
			&CreatePlatMak($OutDir, $E32env::Data{BldPath}, $AllPlatTestData{$Real{$_}}, $_, $Real{$_}, $RomDir, $Module, $BldInfPath, \@TestExports, $OutDir, 'TEST' , \@DoPlats);
		}

#		create the platform test batch files
		foreach (@DoRealPlats) {
			if ($Options{v}) {
				print "Creating test batch files in \"$OutDir\" for $_\n";
			}
			&CreatePlatBatches($OutDir, $AllPlatTestData{$_}, $_);
		}

#		report any near-fatal errors
		if (scalar keys %KeepGoing) {
		    print STDERR
			    "\n${BldInfPath}BLD.INF WARNING(S):\n",
			    sort keys %KeepGoing
			    ;
		}

		exit;
	}
}


################ END OF MAIN PROGRAM SECTION #################
#------------------------------------------------------------#
##############################################################


# SUBROUTINE SECTION
####################

sub Usage () {

	eval { &Load_ModuleL('E32TPVER'); };
	&FatalError($@) if $@;

	print
		"\n",
		"BLDMAKE - Project building Utility (Build ",&E32tpver,")\n",
		"\n",
		"BLDMAKE {options} [<command>] [<platform>]\n",
		"\n",
		"<command>: (case insensitive)\n",
		" BLDFILES - create build batch files\n",
		" CLEAN    - remove all files bldmake creates\n",
		" INF      - display basic BLD.INF syntax\n",
		" PLAT     - display platform macros\n",
		"\n",
		"<platform>: (case insensitive)\n",
		"  if not specified, defaults to \"ALL\"\n",
		"\n",
		"Options: (case insensitive)\n",
		" -v   ->  verbose mode\n",
		" -k   ->  keep going even if files are missing\n"
	;
	exit 1;
}

sub ShowBldInfSyntax () {

	print <<ENDHERE1;

BLD.INF - Syntax

/* Use C++ comments if required */
// (Curly braces denote optional arguments)

PRJ_PLATFORMS
{DEFAULT} {-<platform> ...} {<list of platforms>}
// list platforms your project supports here if not default
ENDHERE1

	print "// default = ".join(" ",@DefaultPlats)."\n";

	print <<ENDHERE;

PRJ_EXPORTS
[<source path>\<source file>]	{<destination>}
// list each file exported from source on a separate line
// {<destination>} defaults to \\EPOC32\\Include\\<source file>

PRJ_TESTEXPORTS
[<source path>\<source file>]	{<destination>}
// list each file exported from source on a separate line
// {<destination>} defaults to BLD.INF dir

PRJ_MMPFILES
[<mmp path>\<mmp file>] {<qualifiers>}
{MAKEFILE|NMAKEFILE} [<path>\<makefile>] {<qualifiers>}
// <qualifiers> are tidy, ignore, build_as_arm

#if defined(<platform>)
// .MMP statements restricted to <platform>
#endif

PRJ_TESTMMPFILES
[<mmp path>\<mmp file>] {<qualifiers>}
{MAKEFILE|NMAKEFILE} [<path>\<makefile>] {<qualifiers>}
// <qualifiers> are {tidy} {ignore} {manual} {support} {build_as_arm}

#if defined(<platform>)
// .MMP statements restricted to <platform>
#endif

ENDHERE

}

sub WarnOrDie ($$) {
	my ($dieref, $message) = @_;
	if ($Options{k}) {
		$KeepGoing{$message} = 1;
	} else {
		push @{$dieref}, $message;
	}
}

sub ParseBldInf ($$$$$) {
	my ($PlatsRef, $ExportsRef, $TestExportsRef, $BldInfPath, $EPOCIncPath, $EPOCPath, $EPOCDataPath)=@_;

	my @Prj2D;
	eval { &Prepfile_ProcessL(\@Prj2D, "${BldInfPath}BLD.INF",$variantMacroHRHFile); };
	&FatalError($@) if $@;
	
	my @SupportedPlats=&Plat_List();


	my @Plats;
	my %RemovePlats;

	my $DefaultPlatsUsed=0;
	my %PlatformCheck;

	my %ExportCheck;
	my $Section=0;
	my @PrjFileDie;
	my $Line;
	my $CurFile="${BldInfPath}BLD.INF";
	LINE: foreach $Line (@Prj2D) {
		my $LineNum=shift @$Line;
		$_=shift @$Line;
		if ($LineNum eq '#') {
			$CurFile=$_;
			next LINE;
		}
		if (/^PRJ_(\w*)$/io) {
			$Section=uc $1;
			if ($Section=~/^(PLATFORMS|EXPORTS|TESTEXPORTS|MMPFILES|TESTMMPFILES)$/o) {
				if (@$Line) {
					push @PrjFileDie, "$CurFile($LineNum) : Can't specify anything on the same line as a section header\n";
				}
				next LINE;
			}
			push @PrjFileDie, "$CurFile($LineNum) : Unknown section header - $_\n";
			$Section=0;
			next LINE;
		}
		if ($Section eq 'PLATFORMS') {
#			platforms are gathered up into a big list that contains no duplicates.  "DEFAULT" is
#			expanded to the list of default platforms.  Platforms specified with a "-" prefix
#			are scheduled for removal from the list.  After processing platforms specified
#			with the "-" prefix are removed from the list.

			unshift @$Line, $_;
			my $Candidate;
			CANDLOOP: foreach $Candidate (@$Line) {
				$Candidate=uc $Candidate;
#				expand DEFAULT
				if ($Candidate eq 'DEFAULT') {
					$DefaultPlatsUsed=1;
					my $Default;
					foreach $Default (@DefaultPlats) {
						unless ($PlatformCheck{$Default}) {
							push @Plats, $Default;
							$PlatformCheck{$Default}="$CurFile: $LineNum";
						}
					}
					next CANDLOOP;
				}
#				check for removals
				if ($Candidate=~/^-(.*)$/o) {
					$Candidate=$1;
#					check default is specified
					unless ($DefaultPlatsUsed) {
						push @PrjFileDie, "$CurFile($LineNum) : \"DEFAULT\" must be specified before platform to be removed\n";
						next CANDLOOP;
					}
					$RemovePlats{$Candidate}=1;
					next CANDLOOP;
				}
#				If arm4, armi or thumb platform is specified in bld.inf file then component is built for gccxml as well 
				if ($Candidate =~ /^arm4/i or $Candidate =~ /^armi/i or $Candidate =~ /^thumb/i){
					push @Plats,'GCCXML'
				};
# 				If tools platform is specified in bld.inf file then component is built for cwtools as well 
				if ($Candidate =~ /^tools/i)
						{
						push @Plats, 'CWTOOLS';
						}
#				check platform is supported
				unless (grep /^$Candidate$/, @SupportedPlats) {
					WarnOrDie(\@PrjFileDie, "$CurFile($LineNum) : Unsupported platform $Candidate specified\n");
					next CANDLOOP;
				}
#				check platform is not an IDE
				if ($Candidate=~/^VC/o) {
					push @PrjFileDie, "$CurFile($LineNum) : No need to specify platform $Candidate here\n";
					next CANDLOOP;
				}
#				add the platform
				unless ($PlatformCheck{$Candidate}) {
					push @Plats, $Candidate;
					$PlatformCheck{$Candidate}="$CurFile: $LineNum";
				}

				if ( ($Candidate eq "ARMI") || ($Candidate eq "THUMB") || ($Candidate eq "ARM4") )
				{	# To aid the developers any of the above may be built under ARM4T if it is specified in abld.
					unless ($PlatformCheck{"ARM4T"}) {
						push @Plats, "ARM4T";
						$PlatformCheck{"ARM4T"}="$CurFile: $LineNum";
					}
				}
			}
			next LINE;
		}
		
		# Skip PRJ_TESTEXPORT section if -notest flag		
		next LINE if ($Options{notest} && ($Section=~/^(TESTEXPORTS)$/o));
		
		if ($Section=~/^(EXPORTS|TESTEXPORTS)$/o) {

#			make path absolute - assume relative to group directory
			my $Type = 'file';
			if (/^\:(\w+)/) {
				# Export an archive
				$Type = lc $1;
				unless ($Type eq 'zip') {
					push @PrjFileDie, "$CurFile($LineNum) : Unknown archive type - $Type\n";
					next LINE;
				}
				$_ = shift @$Line;
			}
			my $Source=&Path_MakeAbs($CurFile, $_);
			my $Releasable='';
			my $emReleasable='';
			if (@$Line) {
#				get the destination file if it's specified
				$Releasable=shift @$Line;
				$emReleasable=ucfirst $Releasable;
 				if ($emReleasable=~/^([A-Z]):(\\.*)$/)  {
 				  	$emReleasable=~s/://;
 					$Releasable=$EPOCDataPath.$emReleasable;
 				}
			}
			if (@$Line) {
				push @PrjFileDie, "$CurFile($LineNum) : Too many arguments in exports section line\n";
				next LINE;
			}
			unless ($Type eq 'zip' or &Path_Split('File', $Releasable)) {
#				use the source filename if no filename is specified in the destination
#				no filename for archives
				$Releasable.=&Path_Split('File', $Source);
			}
			my $defpath;
			if ($Type eq 'zip') {
#				archives relative to EPOCROOT
				$defpath = $ENV{EPOCROOT};
			}
			elsif ($Section eq 'EXPORTS') {
#				assume the destination is relative to $EPOCIncPath
				$defpath = $EPOCIncPath;
			}
			else {
				$defpath = $CurFile;
			}
			$Releasable=&Path_MakeEAbs($EPOCPath, $defpath, $Releasable);
#			sanity checks!
			if ($Type eq 'file' && $ExportCheck{uc $Releasable}) {
				push @PrjFileDie, "$CurFile($LineNum) : Duplicate export $Releasable (from line $ExportCheck{uc $Releasable})\n";
				next LINE;
			}
			$ExportCheck{uc $Releasable}="$CurFile: $LineNum";
			if (! -e $Source) {
				WarnOrDie(\@PrjFileDie, "$CurFile($LineNum) : Exported source file $Source not found\n");
			}
			else {
				if ($Section eq 'EXPORTS') {
					push @$ExportsRef, {
						'Source'=>$Source,
						'Releasable'=>$Releasable,
						'emReleasable'=>$emReleasable,
						'Type'=>$Type
					};
				}
				else {
					push @$TestExportsRef, {
						'Source'=>$Source,
						'Releasable'=>$Releasable,
						'emReleasable'=>$emReleasable,
						'Type'=>$Type
					};
				}
			}
			next LINE;
		}
	}
	if (@PrjFileDie) {
		print STDERR
			"\n${BldInfPath}BLD.INF FATAL ERROR(S):\n",
			@PrjFileDie
		;
		exit 1;
	}

#	set the list of platforms to the default if there aren't any platforms specified,
#	else add platforms to the global list unless they're scheduled for removal,
	unless (@Plats) {
		@$PlatsRef=@DefaultPlats;
	}
	else {

		if ( ($Plats[0] eq "ARM4T") && (scalar(@Plats)==1) )
		{	# Only ARM4T platform by itself. So we intend to build ARM4T as if a proper platform.
			push @Plats, ( "ARMI" , "THUMB" , "ARM4" );
		}

		my $Plat;
		foreach $Plat (@Plats) {
			unless ($RemovePlats{$Plat}) {
				push @$PlatsRef, $Plat;
			}
		}
	}
}

sub ExportDirs ($) {
	my ($ExportsRef)=@_;

	my %ExportDirHash;
	foreach (@$ExportsRef) {
		my $dir = ($$_{Type} eq 'zip') ? $$_{Releasable} : &Path_Split('Path',$$_{Releasable});
		$ExportDirHash{uc $dir}=$dir if ($dir);
	}
	my @ExportDirs;
	foreach (keys %ExportDirHash) {
		push @ExportDirs, &Path_Chop($ExportDirHash{$_});
	}
	@ExportDirs;
}


sub ParseBldInfPlat ($$$$) {
	my ($DataRef, $TestDataRef, $Plat, $BldInfPath)=@_;

#	get the platform .MMP macros
	my %Plat;
	eval { &Plat_GetL($Plat,\%Plat); };
	&FatalError($@) if $@;

#	get the raw data from the BLD.INF file
	my @Prj2D;
	eval { &Prepfile_ProcessL(\@Prj2D, "${BldInfPath}BLD.INF", $variantMacroHRHFile, @{$Plat{MmpMacros}}); };
	&FatalError($@) if $@;
	
#	process the raw data
	my %Check;
	my $Section=0;
	my @PrjFileDie;
	my $Line;
	my $CurFile="${BldInfPath}BLD.INF";
	LINE: foreach $Line (@Prj2D) {

		my %Data;
		my %Temp;

		my $LineNum=shift @$Line;
		if ($LineNum eq '#') {
			$CurFile=shift @$Line;
			next LINE;
		}
		
#		upper-case all the data here
		foreach (@$Line) {
			$_=uc $_;
		}

		$_=shift @$Line;

#		check for section headers - don't test for the right ones here
#		because we do that in the first parse function

		if (/^PRJ_(\w*)$/o) {
			$Section=$1;
			next LINE;
		}

#		Skip section if PRJ_TESTMMPFILES and -notest option
		next LINE if ($Options{notest} && ($Section=~/^(TESTMMPFILES)$/o)); 

#		check for the sections we're interested in and get the .MMP file details
		if ($Section=~/^(MMPFILES|TESTMMPFILES)$/o) {

			$Data{Ext}='.MMP';

#			check for MAKEFILE statements for custom building
			if (/^MAKEFILE$/o) {
				$Data{Makefile}=2;  # hack - treat MAKEFILE=>NMAKEFILE   =1;
				$_=shift @$Line;
				$Data{Ext}=&Path_Split('Ext', $_);


			}
			if (/^NMAKEFILE$/o) {
				$Data{Makefile}=2;
				$_=shift @$Line;
				$Data{Ext}=&Path_Split('Ext', $_);

			}
			if (/^GNUMAKEFILE$/o) {
				$Data{Makefile}=1;
				$_=shift @$Line;
				$Data{Ext}=&Path_Split('Ext', $_);

			}
			
#			path considered relative to the current file
			$Data{Path}=&Path_Split('Path', &Path_MakeAbs($CurFile, $_));

#			this function doesn't care whether the .MMPs are listed with their extensions or not
			$Data{Base}=&Path_Split('Base', $_);
			my $MmpFile= $Data{Path}.$Data{Base};

#			check the file isn't already specified
  			if ($Check{$MmpFile}) {
  				push @PrjFileDie, "$CurFile($LineNum) : duplicate $Data{Base} (from line $Check{$MmpFile})\n";
   				next;
   			}
  			$Check{$MmpFile}="$CurFile: $LineNum";

#			check the file exists
			unless (-e "$Data{Path}$Data{Base}$Data{Ext}") {
				WarnOrDie(\@PrjFileDie, "$CurFile($LineNum) : $Data{Path}$Data{Base}$Data{Ext} does not exist\n");
				next LINE;
			}

#			process the file's attributes
			if ($Section eq 'MMPFILES') {
				foreach (@$Line) {
					if (/^TIDY$/o) {
						$Data{Tidy}=1;
						next;
					}
					if (/^IGNORE$/o) {
						next LINE;
					}
					if (/^BUILD_AS_ARM$/o) {
					  $Data{BuildAsARM}="-arm";
					  next;
					}

					push @PrjFileDie, "$CurFile($LineNum) : Don't understand .MMP file argument \"$_\"\n";
				}
			}

#			process the test .MMP file's attributes
			elsif ($Section eq 'TESTMMPFILES') {
				foreach (@$Line) {
					if (/^TIDY$/o) {
						$Data{Tidy}=1;
						next;
					}
					if (/^IGNORE$/o) {
						next LINE;
					}
					if (/^BUILD_AS_ARM$/o) {
 					  $Data{BuildAsARM}="-arm";
					  next;
					}
					if (/^MANUAL$/o) {
						$Data{Manual}=1;
						next;
					}
					if (/^SUPPORT$/o) {
						$Data{Support}=1;
						next;
					}
					push @PrjFileDie, "$CurFile($LineNum) : Don't understand test .MMP file argument \"$_\"\n";
				}
			}


#			store the data
			if ($Section eq 'MMPFILES') {
				push @$DataRef, \%Data;
				next LINE;
			}
			if ($Section eq 'TESTMMPFILES') {
				push @$TestDataRef, \%Data;
				next LINE;
			}
		}
	}
#	line loop end

#	exit if there are errors
	if (@PrjFileDie) {
		print STDERR
			"\n\"${BldInfPath}BLD.INF\" FATAL ERROR(S):\n",
			@PrjFileDie
		;
		exit 1;
	}
}


sub FatalError (@) {

	print STDERR "BLDMAKE ERROR: @_\n";
	exit 1;
}

sub CreatePlatformPm ($$$$$$) {
	my ($BatchPath, $PlatsRef, $RealPlatsRef, $RealHRef, $AllPlatDataHRef, $AllPlatTestDataHRef)=@_;
# 	exclude GCCXML and CWTOOLS  from list of RealPlats
	my @RealPlats;
	foreach my $Plat (@$RealPlatsRef){
	unless (($Plat =~ /^gccxml/i)  or  ($Plat =~ /^cwtools/i)) {
			push @RealPlats, $Plat;
		}
	}

	&Output(
		"# Bldmake-generated perl file - PLATFORM.PM\n",
		"\n",
		"# use a perl integrity checker\n",
		"use strict;\n",
		"\n",
		"package Platform;\n",
		"\n",
		"use vars qw(\@Plats \@RealPlats %Programs %TestPrograms);\n",
		"\n",
		"\@Plats=qw(@$PlatsRef);\n",
		"\n",
		"\@RealPlats=qw(@RealPlats);\n",
		"\n",
		"%Programs=(\n"
	);
	my %All; # all programs for all platforms
	my $TmpStr;
	my $Plat;
	foreach $Plat (@$PlatsRef) {
		$TmpStr="	$Plat=>[";
		if (@{${$AllPlatDataHRef}{$$RealHRef{$Plat}}}) {
			my $ProgRef;
			foreach $ProgRef (@{${$AllPlatDataHRef}{$$RealHRef{$Plat}}}) {
				$TmpStr.="'$$ProgRef{Base}',";
				$All{$$ProgRef{Base}}=1;
			}
			chop $TmpStr;
		}
		&Output(
			"$TmpStr],\n"
		);
	}
	$TmpStr="	ALL=>[";
	if (keys %All) {
		my $Prog;
		foreach $Prog (keys %All) {
			$TmpStr.="'$Prog',";
		}
		chop $TmpStr;
	}
	&Output(
		"$TmpStr]\n",
		");\n",
		"\n",
		"%TestPrograms=(\n"
	);
	%All=();
	foreach $Plat (@$PlatsRef) {
		$TmpStr="	$Plat=>[";
		if (@{${$AllPlatTestDataHRef}{$$RealHRef{$Plat}}}) {
			my $ProgRef;
			foreach $ProgRef (@{${$AllPlatTestDataHRef}{$$RealHRef{$Plat}}}) {
				$TmpStr.="'$$ProgRef{Base}',";
				$All{$$ProgRef{Base}}=1;
			}
			chop $TmpStr;
		}
		&Output(
			"$TmpStr],\n"
		);
	}
	$TmpStr="	ALL=>[";
	if (keys %All) {
		my $Prog;
		foreach $Prog (keys %All) {
			$TmpStr.="'$Prog',";
		}
		chop $TmpStr;
	}
	&Output(
		"$TmpStr]\n",
		");\n",
		"\n",
		"1;\n"
	);

#	write the PLATFORM.PM file
	&WriteOutFileL($BatchPath."PLATFORM.PM");
}

sub CreatePerlBat ($) {
	my ($BldInfPath)=@_;

#	create ABLD.BAT, which will call ABLD.PL
#   NB. must quote $BldInfPath because it may contain spaces, but we know it definitely
#       ends with \ so we need to generate "\foo\bar\\" to avoid quoting the close double quote
	&Output(
		"\@ECHO OFF\n",
		"\n", 
		"REM Bldmake-generated batch file - ABLD.BAT\n",
		"REM ** DO NOT EDIT **", 
		"\n",
		"\n",
		"perl -S ABLD.PL \"${BldInfPath}\\\" %1 %2 %3 %4 %5 %6 %7 %8 %9\n",
		"if errorlevel==1 goto CheckPerl\n",
		"goto End\n",
		"\n",
		":CheckPerl\n",
		"perl -v >NUL\n",
		"if errorlevel==1 echo Is Perl, version 5.003_07 or later, installed?\n",
		"goto End\n",
		"\n",
		":End\n"
	);

#	check that the .BAT file does not already exist and is read-only
	if ((-e "${BldInfPath}ABLD.BAT")  && !(-w "${BldInfPath}ABLD.BAT")) {
		warn "BLDMAKE WARNING: read-only ABLD.BAT will be overwritten\n";
		chmod 0222, "${BldInfPath}ABLD.BAT";
	}

#	create the .BAT file in the group directory
	&WriteOutFileL($BldInfPath."ABLD.BAT",1);

}

sub GetArchiveExportList($) {
	my ($ExportRef) = @_;
	my $Type = $ExportRef->{Type};
	my $Src = $ExportRef->{Source};
	my $Dest = $ExportRef->{Releasable};
	$Dest = '' if (!defined($Dest));
	my @list = ();
	if ($Type eq 'zip') {
		unless (open PIPE, "unzip -l $Src | ") {
			warn "Can't unzip $Src\n";
		}
		while (<PIPE>) {
			if (/^\s*\d+\s+\S+\s+\S+\s+(.*?)\s*$/) {
#				ignore empty lines and anything that finishes with / 
 				unless(($1=~/\/\s*$/) || ($1=~/^$/)) {
 					if (!$Dest){
 						push @list, "$ENV{EPOCROOT}$1";
 					}
 					else{
 						push @list, "$Dest\\$1";
 					}
				}
			}
		}
		close PIPE;
	}
	return @list;
}

sub CreateExportMak ($$$) {
	my ($Makefile, $ExportsRef, $ExpDirsRef)=@_;

#	create EXPORT.MAKE

	my $erasedefn = "\@erase";
	$erasedefn = "\@erase 2>>nul" if ($ENV{OS} eq "Windows_NT");
	&Output(
		"ERASE = $erasedefn\n",
		"\n",
		"\n",
		"EXPORT : EXPORTDIRS"
	);
	my $ref;
	if (@$ExportsRef) {
		foreach $ref (@$ExportsRef) {
			if ($$ref{Type} eq 'zip') {
				my @list = &GetArchiveExportList($ref);
				foreach (@list) {
					my $dst=&Path_Quote($_);
					&Output(
						" \\\n",
						"\t$dst"
					);
				}
			} else {
				my $name=&Path_Quote($$ref{Releasable});
				&Output(
					" \\\n",
					"\t$name"
				);
			}
		}
	}
	else {
		&Output(
			" \n",
			"\t\@echo Nothing to do\n"
		);
	}
	&Output(
		"\n",
		"\n",
		"\n",
		"EXPORTDIRS :"
	);
	my $dir;
	foreach $dir (@$ExpDirsRef) {
		$dir=&Path_Quote($dir);
		&Output(
			" $dir"
		);
	}
	&Output(
		"\n",
		"\n"
	);
	foreach $dir (@$ExpDirsRef) {
		$dir=&Path_Quote($dir);
		&Output(
			"$dir :\n",
			    "\t\@perl -S emkdir.pl \"\$\@\"\n",
			"\n"
		);
	}
	&Output(
		"\n",
		"\n"
	);
	foreach $ref (@$ExportsRef) {
		if ($$ref{Type} eq 'zip') {
			my $src = &Path_Quote($$ref{Source});
			my $destdir = &Path_Quote($$ref{Releasable});
			$destdir=$ENV{EPOCROOT} if (!defined($destdir) or ($destdir eq ''));
			my @list = &GetArchiveExportList($ref);
  			foreach (@list) {
   				my $dst=&Path_Quote($_);
   				&Output(
  					"$dst : $src\n",
   				);
   			}
			&Output(
			"\tunzip -u  -o $src -d \"$destdir\"\n",
			);
		} else {
			my $dst=&Path_Quote($$ref{Releasable});
			my $src=&Path_Quote($$ref{Source});
			&Output(
				"$dst : $src\n",
					"\tcopy \"\$?\" \"\$\@\"\n",
				"\n"
			);
		}
	}
	&Output(
		"\n",
		"\n"
	);
	if (@$ExportsRef) {
		&Output(
			"CLEANEXPORT :\n"
		);
		foreach $ref (@$ExportsRef) {
			if ($$ref{Type} eq 'zip') {
				my @list = &GetArchiveExportList($ref);
				foreach (@list) {
					my $dst=&Path_Quote($_);
					$dst =~ s/\//\\/go;
					&Output(
						"\t-\$(ERASE) \"$dst\"\n"
					);
				}
			} else {
				my $dst = $$ref{Releasable};
				$dst =~ s/\//\\/go;
				&Output(
					"\t-\$(ERASE) \"$dst\"\n"
				);
			}
		}
		&Output(
			"\n",
			"WHAT :\n"
		);
		foreach $ref (@$ExportsRef) {
			if ($$ref{Type} eq 'zip') {
				my @list = &GetArchiveExportList($ref);
				foreach (@list) {
					my $dst=&Path_Quote($_);
					$dst =~ s/\//\\/go;
					&Output(
						"\t\@echo \"$dst\"\n"
					);
				}
			} else {
				my $dst = $$ref{Releasable};
				$dst =~ s/\//\\/go;
				&Output(
					"\t\@echo \"$dst\"\n"
				);
			}
		}
	}
	else {
		&Output(
			"CLEANEXPORT :\n",
			"\t\@echo Nothing to do\n",
			"WHAT :\n",
			"\t\@rem do nothing\n"
		);
	}
	
#	write EXPORT.MAKE
	&WriteOutFileL($Makefile);
}

sub CreatePlatExports ($$) {
	my ($RealPlat,$Exports)=@_;
	my $Ref;
	&Output(
 	"\n# Rules which handle the case when \$(CFG) is not defined\n\n" ,
 	"EXPORT:		\tEXPORTUREL EXPORTUDEB\n", 
 	"EXPORTCLEAN:	\tEXPORTCLEANUREL EXPORTCLEANUDEB\n",
 	"EXPORTWHAT:	\tEXPORTWHATUREL EXPORTWHATUDEB\n",
  
 	"\n# definitions \n",
 	"DATAx = $ENV{EPOCROOT}epoc32\\data\n",
 	"EMULx = $ENV{EPOCROOT}epoc32\\$RealPlat\n",
 	"URELx = $ENV{EPOCROOT}epoc32\\release\\$RealPlat\\urel\n",
 	"UDEBx = $ENV{EPOCROOT}epoc32\\release\\$RealPlat\\udeb\n",
 	"\n"
	);
	
	&Output( 
	"# Exports to emulated drive A: to Y \n\n",
	"EXPORTGENERIC : EXPORTDIRSGENERIC",
	);
	 
	my @dirs;
	my @expgen;
	my %dirsg;
	foreach $Ref (@$Exports) {
	 	if ($$Ref{emReleasable}=~/^([A-Y])(\\.*)$/){
		   my $exp="\\$$Ref{emReleasable}";
	 	   if ($$Ref{Type} eq 'zip') {	
			 my @list = &GetArchiveExportList($Ref);	
			  foreach (@list) {
				my $dst=&Path_Quote($_);
				if ($dst=~/([^\\]*)$/o){
					$dst=$1;
				}
				my $zipdest=$dst;
				$zipdest =~ s/\//\\/g;
			    push  @expgen, "$exp\\$zipdest";
			    my $zippath= &Path_Chop(&Path_Split('Path', $zipdest));
				if(!$zippath){
					$dirsg{$exp}=$exp;
				}
				else{
					 $dirsg{"$exp\\$zippath"}="$exp\\$zippath";
				}
				&Output(" \\\n","\t\$(EMULx)$exp\\$zipdest");
			 }      
		 }
		 else { 
		     my $dir =  &Path_Chop(&Path_Split('Path', $exp));  
			 push @expgen,  $exp;	
			 $dirsg{$dir}=$dir;
			 &Output(" \\\n", "\t\$(EMULx)$exp "); 
		 }
	   }
	}
	&Output("\n\nEXPORTDIRSGENERIC : ");
	foreach (keys %dirsg){
			 push @dirs, "\$(EMULx)$dirsg{$_}";
			 &Output(" \\\n", "\t\$(EMULx)$_"); 
	} 
	&Output("\n\n");
	foreach (@expgen){	 
			&Output( 
			"\$(EMULx)$_ : \t\$(DATAx)$_ \n",
			"\tcopy \"\$?\" \"\$@\" \n"
			);
	}	
	&Output("\nEXPORTCLEANGENERIC :\n");		
	foreach (@expgen){	 
			&Output("\t-@\$(ERASE) \$(EMULx)$_ \n");
	} 			
	&Output("\nEXPORTWHATGENERIC :\n");			
	foreach (@expgen){	   
			&Output("\t\@echo \$(EMULx)$_ \n");
	}
		
	&Output( 
	 		"\n\n# Exports to emulated drive Z: - UREL version \n\n",
	 		"EXPORTUREL : EXPORTDIRSUREL",
	 	   );
	
	my @expurel; 
	my %dirsurel;
	foreach $Ref (@$Exports) {
		if ($$Ref{emReleasable}=~/^(Z)(\\.*)$/){
			my $exp="\\$$Ref{emReleasable}";
	 	    if ($$Ref{Type} eq 'zip') {
			  my @list = &GetArchiveExportList($Ref);
			  foreach (@list) {
				my $dst=&Path_Quote($_);
				if ($dst=~/([^\\]*)$/o){
					$dst=$1;
				}
				my $zipdest=$dst;
				$zipdest=~ s/\//\\/g;
				push  @expurel, "$exp\\$zipdest"; 
				my $zippath= &Path_Chop(&Path_Split('Path', $zipdest)); 
				if(!$zippath){
				   $dirsurel{$exp}=$exp;
				}
				else{
					$dirsurel{"$exp\\$zippath"}="$exp\\$zippath";
				}
				&Output(" \\\n","\t\$(URELx)$exp\\$zipdest");
			}  
		}
		else {
			  my $dir =  &Path_Chop(&Path_Split('Path', $exp));  
			  push @expurel,  $exp; 
			  $dirsurel{$dir}=$dir;
			  &Output(" \\\n", "\t\$(URELx)$exp "); 
		}
	  }
	} 
	&Output("\n\nEXPORTDIRSUREL : ");
	foreach (keys %dirsurel){
			push @dirs, "\$(URELx)$dirsurel{$_}";
   			&Output(" \\\n", "\t\$(URELx)$_ "); 
	}
	&Output("\n\n");	
	foreach (@expurel){
			 &Output( 
					"\$(URELx)$_ : \t\$(DATAx)$_ \n",
					"\tcopy \"\$?\" \"\$@\" \n"
			 );
	}		
	&Output("\nEXPORTCLEANUREL :\n"); 		
	foreach (@expurel){	
			 &Output("\t-@\$(ERASE) \$(URELx)$_ \n"); 
	}  
	&Output("\nEXPORTWHATUREL :\n");	
	foreach (@expurel){	
			 &Output( "\t\@echo \$(URELx)$_ \n"); 	
	}
	   
	&Output( 
	 		"\n\n# Exports to emulated drive Z: - UDEB version \n\n",
	 		"EXPORTUDEB : EXPORTDIRSUDEB",
	);  
	 	   
	my %dirsudeb=%dirsurel;          
	my @expudeb=@expurel;
	foreach (@expudeb){
	         &Output(" \\\n", "\t\$(UDEBx)$_ ");		  
	}
	&Output("\n\nEXPORTDIRSUDEB : ");
	foreach(keys %dirsudeb){
	  		push @dirs, "\$(UDEBx)$dirsudeb{$_}";
	  		&Output(" \\\n", "\t\$(UDEBx)$_ "); 
	  	
	}
	&Output("\n\n");
	foreach (@expudeb){
	 		 &Output( 
					"\$(UDEBx)$_ : \t\$(DATAx)$_ \n",
					"\tcopy \"\$?\" \"\$@\" \n"
			 );
	}			
	&Output("\nEXPORTCLEANUDEB :\n");
	foreach (@expudeb){	
			 &Output("\t-@\$(ERASE) \$(UDEBx)$_ \n"); 
	}  
	&Output("\nEXPORTWHATUDEB :\n");	
	foreach (@expudeb){	
			 &Output("\t\@echo \$(UDEBx)$_ \n"); 	
	}
	
    &Output("\n# Directories \n\n");  
	&Output(join (" \\\n", @dirs)." :")       
	&Output("\n\t\@perl -S emkdir.pl \$@\n\n");			
		   		
}

sub CreatePlatMak ($$$$$$$$$) {
	my ($BatchPath, $E32MakePath, $DataRef, $Plat, $RealPlat, $RomDir, $Module, $BldInfPath, $Exports, $OutDir, $Test , $DoPlats_ref)=@_;

	unless ($Test) {
		$Test='';
	}
	else {
		$Test='TEST';
	}


 	if ($RealPlat =~ /^ARM4T$/) {
		&CreateARM4TPlat( $BatchPath, $DataRef, $Plat, $Module, $OutDir, $Test , $DoPlats_ref );
		return ;		
	}


 	my $Ref;
 	my $eDrive=0;
 	if ($RealPlat =~ /^WINS/) {
 	    foreach $Ref (@$Exports) {
 			if ($$Ref{emReleasable}=~/^([A-Z])(\\.*)$/) {
 				$eDrive=1;
 				last;
 			}
 		}
 	} 
 
	my $OutRomFile="$RomDir$RealPlat$Test.IBY";
	my $GCCDir="gcc\\bin";
	
	my $erasedefn = "\@erase";
	$erasedefn = "\@erase 2>>nul" if ($ENV{OS} eq "Windows_NT");

	if ($ENV{'PATH'} !~ m/[a-zA-z]{1}:{1}.[^;]*epoc32\\gcc\\bin/i) {
		&Output(
			"# set Path for custom builds using GCC - must set Path and PATH\n",
			'Path:=',&main::Path_Drive,$E32env::Data{EPOCPath},$GCCDir,";\$(Path)\n",
			"PATH:=\$(Path)\n"
			);
	}
	
	&Output(		
		"\n",
		"# prevent MAKEFLAGS variable from upsetting calls to NMAKE\n",
		"unexport MAKEFLAGS\n",
		"\n",
		"ERASE = $erasedefn\n",
		"\n",
		"\n"
		);
 
 	if ($eDrive) {
 		# Generate exports into emulated drives
 		&CreatePlatExports($RealPlat,$Exports);
 	}

	my $Command;
	foreach $Command (qw(CLEAN CLEANMAKEFILE CLEANALL FINAL FREEZE LIBRARY MAKEFILE RESOURCE SAVESPACE TARGET LISTING WHATMAKEFILE)) {
		&Output(
			"$Command :"
		);
		 
		if ($eDrive and $Command eq 'CLEAN'){	
			&Output(" EXPORTCLEANGENERIC EXPORTCLEAN\$(CFG) ");	    	
			foreach $Ref (@$DataRef) {
					&Output(" $Command$$Ref{Base}");
			}
		}	    	 
		elsif ($eDrive and $Command eq 'RESOURCE'){
			&Output(" EXPORTGENERIC EXPORT\$(CFG) ");
			foreach $Ref (@$DataRef) {
					&Output(" $Command$$Ref{Base}");
			}

			foreach $Ref (@$DataRef) {
				&Output("\n\nRESOURCE$$Ref{Base} : EXPORTGENERIC EXPORT\$(CFG)");
			}
		}
		else {
			if(@$DataRef){
				foreach $Ref (@$DataRef) {
				&Output(" $Command$$Ref{Base}");
 			    }
			} 		
			else {
				&Output("\n","\t\@echo Nothing to do\n");
			}
		}  
		&Output("\n","\n");
	}

	&Output(
		"WHAT :"
	);
 	if($eDrive){
 	  &Output(" EXPORTWHATGENERIC EXPORTWHAT\$(CFG) ");
 	}
	my $whatcount=0;
	foreach $Ref (@$DataRef) {
		unless ($$Ref{Tidy}) {
			$whatcount++;
			&Output(
				" WHAT$$Ref{Base}"
			);
		}
	}
	if ($whatcount==0 and !$eDrive) {
		&Output(
			"\n",
			"\t\@rem do nothing\n" 
		);
	}
	&Output(
		"\n",
		"\n",
		"TIDY :"
	);
	my $Tidy='';
	foreach $Ref (@$DataRef) {
		if ($$Ref{Tidy}) {
			$Tidy.=" TIDY$$Ref{Base}";
		}
	}
	if ($Tidy) {
		&Output(
			"$Tidy\n"
		);
	}
	else {
		&Output(
			"\n",
			"\t\@echo Nothing to do\n"
		);
	}
	&Output(
		"\n",
		"\n"
	);
#	hack for non-EPOC platforms
	if ($RealPlat=~/^(WINS|WINSCW|WINC|TOOLS)$/o) {
		&Output(
			"ROMFILE :\n"
		);
	}
	else {
		&Output(
			'ROMFILE : STARTROMFILE'
		);
		foreach $Ref (@$DataRef) {
			&Output(
				" ROMFILE$$Ref{Base}"
			);
		}
		&Output(
			"\n",
			"\n",
			"STARTROMFILE :\n",
			    "\t\@perl -S emkdir.pl \"", &Path_Chop($RomDir), "\"\n",
			    "\t\@echo // $OutRomFile > $OutRomFile\n",
			    "\t\@echo // >> $OutRomFile\n"
		);
		if ($Test) {
			my ($Auto, $Manual);
			foreach $Ref (@$DataRef) {
				++$Auto unless ($$Ref{Manual} or $$Ref{Support});
				++$Manual if ($$Ref{Manual});
			}
			if ($Auto) {
				my $IbyTextFrom="data=$BatchPath$Plat.AUTO.BAT";
				my $IbyTextTo="Test\\$Module.$Plat.AUTO.BAT";
				my $Spaces= 60>length($IbyTextFrom) ? 60-length($IbyTextFrom) : 1; 
				&Output("\t\@echo ", $IbyTextFrom, ' 'x$Spaces, $IbyTextTo, ">> $OutRomFile\n");
			}
			if ($Manual) {
				my $IbyTextFrom="data=$BatchPath$Plat.MANUAL.BAT";
				my $IbyTextTo="Test\\$Module.$Plat.MANUAL.BAT";
				my $Spaces= 60>length($IbyTextFrom) ? 60-length($IbyTextFrom) : 1; 
				&Output("\t\@echo ", $IbyTextFrom, ' 'x$Spaces, $IbyTextTo, ">> $OutRomFile\n");
			}
		}
	}
	&Output(
		"\n",
		"\n"
	);
	my $CallNmake='nmake -nologo -x - $(VERBOSE) $(KEEPGOING)';
	my $CallGNUmake='$(MAKE) $(VERBOSE) $(KEEPGOING)';

	my %PlatHash;
	&Plat_GetL($RealPlat, \%PlatHash);
	my $CallMake=$CallNmake;
	if ($PlatHash{MakeCmd} eq "make") {
		$CallMake="$CallGNUmake -r";
	}
	&Plat_GetL($Plat, \%PlatHash);

	foreach $Ref (@$DataRef) {

#		standard commands
		unless ($$Ref{Makefile}) {
			my $MakefilePath=join('', &Path_Chop($E32MakePath), $$Ref{Path}, $$Ref{Base}, "\\", $RealPlat, "\\");
			my $RealMakefile="-f \"$MakefilePath$$Ref{Base}.$RealPlat\"";
			my $MakefileBase="$MakefilePath$$Ref{Base}";		
			&Output(
				"MAKEFILE$$Ref{Base}_FILES= \\\n",
					"\t\"$MakefileBase$PlatHash{Ext}\"",
			);
#			hacks for WINS/WINSCW/WINC and VC6
			if ($Plat =~ /^VC6/) {
				&Output(
					" \\\n\t\"$MakefileBase.DSW\"",
					" \\\n\t\"$MakefileBase.SUP.MAKE\""
				);
			}
			if ($Plat eq 'CW_IDE') {
				&Output(
					" \\\n\t\"$MakefileBase.pref\""		# BUG: actually uses $BaseTrg, not mmp file name
				);
			}

			my $callMakmake;
			my $build_as_arm_arg="\$(ARM4T)";
				# Controls if we are attempting to build an ARM4T build. 
				#-ARM4T => that we are otherwise NULL and build will be normal default behaviour. 
			

			if ( $$Ref{BuildAsARM} ) {	
			    # Pass down the fact that a request to build arm has been made from the bld.inf
				$build_as_arm_arg .= " ".$$Ref{BuildAsARM};
			}

			$callMakmake = "\tperl -S makmake.pl \$(NO_DEPENDENCIES) -D $$Ref{Path}$$Ref{Base} \$(ABLD_FLAGS) $build_as_arm_arg $Plat\n";

			&Output(
				"\n",
				"\n",
				"MAKEFILE$$Ref{Base} :\n",
				    "$callMakmake",
				"\n",
				"CLEANMAKEFILE$$Ref{Base} :\n",
				    "\t-\$(ERASE) \$(MAKEFILE$$Ref{Base}_FILES)\n",
				"\n",
				"WHATMAKEFILE$$Ref{Base} :\n",
				    "\t\@echo \$(MAKEFILE$$Ref{Base}_FILES)\n",
				"\n",
				"TARGET$$Ref{Base} :\n",
				    "\t$CallMake $RealMakefile \$(CFG)\n",
				"\n",
				"SAVESPACE$$Ref{Base} :\n",
				    "\t$CallMake $RealMakefile \$(CFG) CLEANBUILD\$(CFG)\n",
				"\n",
				"LISTING$$Ref{Base} :\n",
				    "\t$CallMake $RealMakefile MAKEWORK\$(CFG) LISTING\$(CFG)\$(SOURCE)\n",
				"\n",
				"FINAL$$Ref{Base} :\n",
				    "\t\@rem do nothing\n",
				"\n",
			);
			foreach $Command (qw(CLEANALL)) {
				&Output(
					"CLEANALL$$Ref{Base} :\n",
					"\tperl -S ermdir.pl $MakefilePath\n",
					"\n",
				);
			}
			foreach $Command (qw(CLEAN RESOURCE)) {
				&Output(
					"$Command$$Ref{Base} :\n",
					    "\t$CallMake $RealMakefile $Command\$(CFG)\n",
					"\n"
				);
			}
			foreach $Command (qw(FREEZE LIBRARY)) {
				&Output(
					"$Command$$Ref{Base} :\n",
					    "\t$CallMake $RealMakefile $Command\n",
					"\n"
				);
			}
			unless ($$Ref{Tidy}) {
				&Output(
					"WHAT$$Ref{Base} :\n",
					    "\t\@$CallMake -s $RealMakefile WHAT\$(CFG)\n",
					"\n"
				);
			}
			else {
				&Output(
					"TIDY$$Ref{Base} :\n",
					    "\t$CallMake $RealMakefile CLEANRELEASE CLEANLIBRARY\n",
					"\n"
				);
			}
			&Output(
				"ROMFILE$$Ref{Base} :\n",
				    "\t\@$CallMake $RealMakefile ROMFILE >> $OutRomFile\n",
				"\n",
				"\n"
			);
		}


		else {

#		calls to custom makefiles
#		We now have an intermidate forwarding makefile which will either do nothing or will forward all the parameters 
#		and varibles to the extension makefile which will do the work.
#		
#		Note we will always go through the intermidiate forwarding makefiles for all supported platforms.
#		Note in the case of ARM4T psudo platform not all of the sub platforms thumb/armi/arm4 will be supported.
#			Those platforms which are not suppported will have NULL forwarding makefiles which will do nothing. 
#		See documentation "SGL.PR0099.023_vX.X_Mostly_Thumb_EKA1_Design_Specification.doc" for furthur information. 


			my $ChopRefPath=&Path_Chop($$Ref{Path});
			my $ChopBldInfPath=&Path_Chop($BldInfPath);
			my $MakefileCall;
			my $Call;

			if ($$Ref{Makefile}==2) {
				$MakefileCall="cd $ChopRefPath;$CallNmake";
				$Call = $CallNmake;
			} else {
				$MakefileCall="$CallGNUmake -C $ChopRefPath";
				$Call = $CallGNUmake." -s";
			}

			$MakefileCall.=" -f \"$$Ref{Base}$$Ref{Ext}\" TO_ROOT=";
			$MakefileCall.=&Path_Chop(&Path_UpToRoot($$Ref{Path}));

			my $Ext = $$Ref{Ext};
			$Ext=~s/\./_/;	# Just get rid of the . in the extension. 

			my $ForwardingMakefilePath =&Path_Chop($E32env::Data{BldPath})."$$Ref{Path}$$Ref{Base}$Ext\\$RealPlat";
			my $ForwardingMakefileName = "$$Ref{Base}$$Ref{Ext}";
			my $ForwardingMakefilePathName = $ForwardingMakefilePath."\\".$ForwardingMakefileName;
			my $MakefileCallBase = $MakefileCall." PLATFORM=$Plat "." \$\$\@";
				# Pass in  platform so child gets variable, and overrides eviroment. 

			$MakefileCallBase =~ s/\"/\\\"/g;
				# ensure that the quotes get passed through. 

			my $ForwardingMakefileCall = "make "." -s"." -f ".$ForwardingMakefilePathName;

			# deal with -arm option if any. 
			my $ARM_PARAM="";
			if ( $$Ref{BuildAsARM} )
			{
				$ARM_PARAM=$$Ref{BuildAsARM}." ";
			}

			# extmake.pl generates the forwarding makefiles for the extension makefiles.
			&Output(
# should change to MAKEFILE
				"MAKEFILE$$Ref{Base} :\n",
					"\tperl -S extmake.pl ${ARM_PARAM}\$(ABLD_FLAGS) \$(ARM4T) $RealPlat", 
					" -d $ForwardingMakefilePath", 
					" -f $ForwardingMakefileName", 
					" -c \"$MakefileCallBase\"",
					"\n",
				    "\t\@$ForwardingMakefileCall ",
					"PLATFORM=$Plat MAKMAKE\n",
				"\n");

			# Rather than call the extension makefiles directly call the forwarding makefiles.
			# In ARM4T
			# The forwarding makefiles may then pass the various variables on the actual makefiles if the platform is valid.
			# If the platform is not something that needs to be built the extension makefile will not be called and no work will be done. 

			&Output(
# should call in custom makefiles maybe
				"CLEANMAKEFILE$$Ref{Base} :\n",
				"#	\@$ForwardingMakefileCall PLATFORM=$Plat CLEANMAKEFILE\n",
				"\n",
				"WHATMAKEFILE$$Ref{Base} :\n",
				"#	\@$ForwardingMakefileCall -s PLATFORM=$Plat WHATMAKEFILE\n",
				"\n"
			);
			&Output(
# should change to TARGET
				"TARGET$$Ref{Base} :\n",
				    "\t\@$ForwardingMakefileCall PLATFORM=$RealPlat CFG=\$(CFG) BLD\n",
				"\n",
			);
			&Output(
# should ignore this target and just call the TARGET target instead?
				"SAVESPACE$$Ref{Base} :\n",
				    "\t\@$ForwardingMakefileCall PLATFORM=$RealPlat CFG=\$(CFG) SAVESPACE\n",
				"\n",
				"LISTING$$Ref{Base} :\n",
				"\n",
				"\n",
			);
			&Output(
# should change to LIBRARY
				"LIBRARY$$Ref{Base} :\n",
				    "\t\@$ForwardingMakefileCall PLATFORM=$RealPlat LIB\n",
				"\n",
				"FREEZE$$Ref{Base} :\n",
				    "\t\@$ForwardingMakefileCall PLATFORM=$RealPlat FREEZE\n",
				"\n",
			);
			foreach $Command (qw(CLEANALL)) {
				&Output(
					"$Command$$Ref{Base} :\n",
					"\t$MakefileCall PLATFORM=$RealPlat CFG=\$(CFG) CLEAN\n",
					"\n"
				);
			}
			foreach $Command (qw(CLEAN RESOURCE FINAL)) {
				&Output(
					"$Command$$Ref{Base} :\n",
					    "\t\@$ForwardingMakefileCall PLATFORM=$RealPlat CFG=\$(CFG) $Command\n",
					"\n"
				);
			}
			unless ($$Ref{Tidy}) {
# should change to WHAT
				&Output(
					"WHAT$$Ref{Base} :\n",
					    "\t\@$ForwardingMakefileCall -s PLATFORM=$RealPlat CFG=\$(CFG) RELEASABLES\n",
					"\n"
				);
			}
			else {
				&Output(
					"TIDY$$Ref{Base} :\n",
					    "\t\@$ForwardingMakefileCall PLATFORM=$RealPlat TIDY\n",
# should change to CLEANLIBRARY
					    "\t\@$ForwardingMakefileCall CLEANLIB\n",
					"\n"
				);
			}
			&Output(
				"ROMFILE$$Ref{Base} :\n",
				    "\t\@$ForwardingMakefileCall PLATFORM=$RealPlat ROMFILE >> $OutRomFile\n",
				"\n",
				"\n"
			);
		}

	}
	
	&WriteOutFileL("$BatchPath$Plat$Test.MAKE");
}



#
# Generate the forwarding makefiles for the ARM4T platform.
# Note what platforms are generated depends on the flags in PRJ_PLATFORMS
# Any platforms that do not exist will not be generated. 
#
sub CreateARM4TPlat( $$ ) 
{
	my ($BatchPath, $DataRef, $Plat, $Module, $OutDir, $Test, $DoPlats_ref)=@_;

	&Output( "all :\n" );


	my $ARM4 = grep(/^ARM4$/, @$DoPlats_ref);
	my $ARMI = grep(/^ARMI$/, @$DoPlats_ref);
	my $THUMB = grep(/^THUMB$/, @$DoPlats_ref );
		# Only want to generate forwarding makefiles for platforms that exist. 

	if ($ARM4) { &Output( "\t\@make --no-print-directory -C . -f \"${BatchPath}arm4${Test}.make\" \$\@\n" ); }
	if ($ARMI) { &Output( "\t\@make --no-print-directory -C . -f \"${BatchPath}armi${Test}.make\" \$\@\n" ); }
	if ($THUMB) { &Output( "\t\@make --no-print-directory -C . -f \"${BatchPath}thumb${Test}.make\" \$\@\n" ); }
	&Output( "# forward \"all\" commands if any.\n\n");


	&Output(
		"MAKEFILE : "
	);

 	my $Ref;
	if(@$DataRef){
		foreach $Ref (@$DataRef) {

		if ( !$$Ref{Makefile} )	{ # Do not call for makefiles.
			&Output(" MAKEFILE$$Ref{Base}");
			}
 		}
	} 		

	&Output( "\n" );

	if ($ARM4) { &Output( "\t\@make --no-print-directory -C . -f \"${BatchPath}arm4${Test}.make\" \$\@\n" ); }
	if ($ARMI) { &Output( "\t\@make --no-print-directory -C . -f \"${BatchPath}armi${Test}.make\" \$\@\n" ); }
	if ($THUMB) { &Output( "\t\@make --no-print-directory -C . -f \"${BatchPath}thumb${Test}.make\" \$\@\n" ); }

	&Output( "# now forward the making of the other build files. Maybe they get built Maybe they are null. \n" );
	&Output( "# Important {ARM4T} flag will be set to -ARM4T\n",
		"\n"
	);


	&Output( "%::\n" );
	if ($ARM4) { &Output( "\t\@make --no-print-directory -C . -f \"${BatchPath}arm4${Test}.make\" \$\@\n" ); }
	if ($ARMI) { &Output( "\t\@make --no-print-directory -C . -f \"${BatchPath}armi${Test}.make\" \$\@\n" ); }
	if ($THUMB) { &Output( "\t\@make --no-print-directory -C . -f \"${BatchPath}thumb${Test}.make\" \$\@\n" ); }
	&Output( "# forward all the commands\n" );


	my @List=();
	if ($ARM4) { push @List , "ARM4"; }
	if ($ARMI) { push @List , "ARMI"; }
	if ($THUMB) { push @List , "THUMB"; }

	my $Allowable = "";
	if ( scalar(@List) > 0)
	{
		$Allowable = " -allowable" . " " . join("+" , @List);
	}


	foreach $Ref (@$DataRef) {
		my $callMakmake;
		my $build_as_arm_arg=" -ARM4T";	
			# We are always trying to build an ARM4T makefile from here.
		
		if ( !$$Ref{Makefile} )	{ # Do not call for makefiles.
			if ( $$Ref{BuildAsARM} ) {	
				# Pass down the fact that a request to build arm has been made from the bld.inf
				$build_as_arm_arg .= " ".$$Ref{BuildAsARM};
			}

			$callMakmake = "\tperl -S makmake.pl \$(NO_DEPENDENCIES) -D $$Ref{Path}$$Ref{Base}$Allowable$build_as_arm_arg $Plat\n";

			&Output(
				"\n",
				"\n",
				"MAKEFILE$$Ref{Base} :\n",
					"$callMakmake",
				"\n"
			);
		}
	}


	&WriteOutFileL("$BatchPath$Plat$Test.MAKE");

	return ;		
}



sub CreatePlatBatches ($$$) {
	my ($OutDir, $DataRef, $Plat)=@_;

#	create the test batch files
#	this function won't work properly if the target basename is different from the .MMP basename
#	so perhaps it should call makmake on the .mmp file to check

	my $AutoText;
	my $ManualText;

	my $Ref;
	foreach $Ref (@$DataRef) {
		if ($$Ref{Manual}) {
			$ManualText.="$$Ref{Base}\n";
			next;
		}
		if ($$Ref{Support}) {
			next;
		}
		else {
			$AutoText.="$$Ref{Base}\n";
		}
	}

	if ($AutoText) {
		&Output($AutoText);
		&WriteOutFileL("$OutDir$Plat.AUTO.BAT");
	}

	if ($ManualText) {
		&Output($ManualText);
		&WriteOutFileL("$OutDir$Plat.MANUAL.BAT");
	}
}

sub WriteOutFileL ($$) { # takes batch file and boolean read-only flag
	my ($BATFILE, $ReadOnly)=@_;


	eval { &Path_MakePathL($BATFILE); };
	&FatalError($@) if $@;

	open BATFILE,">$BATFILE" or &FatalError("Can't open or create Batch File \"$BATFILE\"");
	print BATFILE &OutText or &FatalError("Can't write output to Batch File \"$BATFILE\"");
	close BATFILE or &FatalError("Can't close Batch File \"$BATFILE\"");
}



