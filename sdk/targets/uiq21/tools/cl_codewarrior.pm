# CL_CODEWARRIOR.PM
#
# Copyright (c) 2001-2003 Symbian Ltd.  All rights reserved.
#


package Cl_codewarrior;

# declare variables global for module
my @Win32LibList=();
my $BaseAddressFlag;
my $Win32Resrc;

my $MWCC;
my $MWLD;
my $MWIncludePath;
my $MWIncludeVar;

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	PMHelp_Mmp

	PMCheckPlatformL

	PMPlatProcessMmp
	
	PMStartBldList
		PMBld
	PMStartSrcList
		PMBitMapBld
		PMResrcBld
		PMAifBld
		PMStartSrc
		PMSrcDepend
			PMSrcBldDepend
			PMEndSrcBld
		PMEndSrc
	PMEndSrcList
);

use Winutl;
use cl_generic;

sub PMHelp_Mmp {
	&Winutl_Help_Mmp;
}

sub PMCheckPlatformL {

	# check version of CodeWarrior for Symbian OS
	
	if (defined($ENV{MWCSym2Includes})) {
		$MWCC = "mwccsym2.exe";
		$MWLD = "mwldsym2.exe";
		# print "Detected CodeWarrior for Symbian OS, OEM version 2\n";
	}
	if (!defined($MWCC) && defined($ENV{MWSym2Libraries})) {
		$MWCC = "mwccsym2.exe";
		$MWLD = "mwldsym2.exe";
		# print "Detected CodeWarrior for Symbian OS, Pro version 2.0\n";
	}
	if (!defined($MWCC) && defined($ENV{CWFolder})) {
		$MWCC = "mwcc.exe";
		$MWLD = "mwld.exe";
		# print "Assuming CodeWarrior for Symbian OS, Pro version 1.0\n";
	}
	if (!defined($MWCC)) {
		die "ERROR: Unable to identify a valid CodeWarrior for Symbian OS installation\n";
	}
	
	# determine default include path
	
	$MWIncludeVar = 'MWCIncludes';	# default, even if it doesn't exist
	$MWIncludePath = '';			# default is empty
	
	foreach my $var ('MWCSym2Includes','MWCWinx86Includes','MWCIncludes') {
		if (defined($ENV{$var})) {
			$MWIncludePath = $ENV{$var};
			$MWIncludeVar = $var;
			last;
		}
	}
}

sub PMPlatProcessMmp (@) {

	&Winutl_DoMmp(\@_,$MWIncludePath);
	$BaseAddressFlag=&Winutl_BaseAddress;
	if ($BaseAddressFlag ne "") {
		$BaseAddressFlag=" -imagebase \"$BaseAddressFlag\"";
	}
	@Win32LibList=&Winutl_Win32LibList;
	$Win32Resrc=&Winutl_Win32Resrc;
}

sub PMStartBldList($) {
	my ($makecmd) = @_;
	my $AifStructRef=&main::AifStructRef;
	my $BaseTrg=&main::BaseTrg;
	my $BitMapStructRef=&main::BitMapStructRef;
	my @BldList=&main::BldList;
	my @ChopSysIncPaths=&main::Path_Chop(&main::SysIncPaths);
	my @ChopUserIncPaths=&main::Path_Chop(&main::UserIncPaths);
	my $DefFile=&main::DefFile;
	my $BasicTrgType=&main::BasicTrgType;
	my $LibPath=&main::LibPath;
	my @MacroList=&main::MacroList();
	my $ResourceStructRef=&main::ResourceStructRef;
	my $Plat=&main::Plat;
	my $Trg=&main::Trg;
	my $TrgType=&main::TrgType;
	my $WarningLevel=&main::CompilerOption("CW");

	Generic_Header(0,$makecmd);	# define standard things using absolute paths

	my $TrgDir="";
	if (&Generic_Definition("TRGDIR") ne "") {
		$TrgDir="\$(TRGDIR)\\";
	}

# Hack - mwwinrc.exe uses MWWinx86Includes or MWCIncludes, but some installations
# fail to install either. Set MWCIncludes from the chosen variable as part
# of the Makefile.
	if (!defined($ENV{MWCIncludes}) && $MWIncludeVar ne 'MWCIncludes') {
		&main::Output(
			"\n",
			"MWCIncludes:=\$($MWIncludeVar)\n",
			"export MWCIncludes\n",
			"\n"
		);
	}
# hack ends

	&main::Output(
		"# EPOC DEFINITIONS\n",
		"\n",
		"INCDIR  = -cwd source -i-"
	);
	foreach (@ChopUserIncPaths,@ChopSysIncPaths) {
		&main::Output(
			" \\\n -i \"$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"CWFLAGS =",
		" -wchar_t off",	# do not treat wchar_t as a predefined type
		" -align 4",		# long alignment
		" -warnings on",	# selection of warnings
		" -w nohidevirtual",	# turn off "hides inherited virtual function" warning
		   ",nounusedexpr",	# turn off "expression has no side effect" warning
		" -msgstyle gcc",	# use GCC-style message format
		# " -strict on",		# strict ANSI/ISO C++ checking
		" -enum int",		# use int for enumeration types
		" -str pool",		# pool strings into a single data object
		" $WarningLevel"		
	
	);
# tools hack in line below
	if (@Win32LibList or &main::Plat eq 'TOOLS') {
		&main::Output(
			" -stdinc"		# insist because mwccsym2 has -nostdinc as the default(?)
		);
	}
	else {
		&main::Output(
			" -nostdinc"	# insist because mwcc has -stdinc as the default.
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"CWDEFS  = "
	);
	foreach(@MacroList) {
		&main::Output(
			" -d \"$_\""
		);
	}
	&main::Output(
		" \$(USERDEFS)\n",
		"\n"
	);

	foreach (@BldList) {
		&main::Output(
			"CW$_ = $MWCC"
		);
		if (/DEB$/o) {
			&main::Output(
				' -g -O0'   # debug information, no optimisation
			);
#			euser hack to apply inlining on the _NAKED functions
			if ($BaseTrg=~/^EUSER$/o) {
				&main::Output(
					' -inline on'
				);
			}
		}
		elsif (/REL$/o) {
			&main::Output(
				' -O4,s'	# highest level of optimisation, optimise for space
			);
		}
		&main::Output(
			' $(CWFLAGS)'
		);
		if (/DEB$/o) {
			&main::Output(
				" -browse"
			);
		}
		foreach (&main::MacroList($_)) {
			&main::Output(
				" -d $_"
			);
		}
		&main::Output(
			" \$(CWDEFS) \$(INCDIR)\n"
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
	
	foreach (@BldList) {
		&main::Output(
			"$_ :"
		);

		&main::Output (
			" \\\n",
			"\t", &Generic_Quote("\$(EPOCTRG$_)\\$TrgDir$Trg")
		);
		if (&Winutl_CopyForStaticLinkage) {
			&main::Output(
				" \\\n",
				"\t", &Generic_Quote("\$(EPOCTRG$_)\\$Trg")
			);
		}

#		lib has to come after the main target so that a .DEF file will be generated if the project is not frozen
		if ($DefFile and not &main::ExportUnfrozen) {
			&main::Output(
				" \\\n",
				"\tLIBRARY\n"
			);
		}
		&main::Output(
			"\n",
			"\n"
		);
	}

	foreach (@BldList) {
		my $makework="MAKEWORK$_";
		&main::Output(
			"\n",
			"RESOURCE$_ : $makework"
		);

		my $BitMapRef;
		foreach $BitMapRef (@$BitMapStructRef) {
			my $file="\$(EPOCTRG$_)\\$$BitMapRef{TrgPath}$$BitMapRef{Trg}";
			&Generic_MakeWorkFile($makework,$file);
			&main::Output(
				" \\\n",
				"\t", &Generic_Quote($file)
			);
		}
		undef $BitMapRef;

		my $ResourceRef;
		foreach $ResourceRef (@$ResourceStructRef) {
			my $file="\$(EPOCTRG$_)\\$$ResourceRef{Trg}";
			&Generic_MakeWorkFile($makework,$file);
			&main::Output(	# must come before main target because source for target will depend on the
			" \\\n",		# *.rsg file in $EPOCIncPath
			"\t", &Generic_Quote("$file")
			);
		}
		undef $ResourceRef;

		my $AifRef;
		foreach $AifRef (@$AifStructRef) {
			my $file="\$(EPOCTRG$_)\\$TrgDir$$AifRef{Trg}";
			&Generic_MakeWorkFile($makework,$file);
			&main::Output(
				" \\\n",
				"\t", &Generic_Quote($file)
			);
		}
		undef $AifRef;

		&main::Output(
			"\n"
		);
	}
	&main::Output(
		"\n",
		"\n",
	);

	&main::Output(
		"\n",
		"# REAL TARGET - LIBRARY\n",
		"\n",
		"LIBRARY : MAKEWORKLIBRARY"
	);
	if ($BasicTrgType=~/^LIB$/o) {
#		code to ensure that the static libraries for all builds are built at the library stage
		foreach (@BldList) {
			&main::Output(
				" $_"
			);
		}
	}
	elsif ($DefFile) {
		unless (&main::ExportUnfrozen) {
			if (-e $DefFile) { # effectively "if project frozen ..."
				&main::Output(
					" ", &Generic_Quote("\$(EPOCLIB)\\UDEB\\$BaseTrg.LIB"), "\n",
					"\n",
					&Generic_Quote("\$(EPOCLIB)\\UDEB\\$BaseTrg.LIB"), " : ",
					&Generic_Quote($DefFile), "\n",
					"\t$MWLD \$\? -importlib -o \$\@",
					" -addcommand \"out:$Trg\" -warnings off",
					"\n"
				);
			}
			else {
				&main::Output(
					"\n",
					"\t\@echo WARNING: Not attempting to create \"\$(EPOCLIB)\\UDEB\\$BaseTrg.LIB\".\n",
					"\t\@echo When exports are frozen in \"$DefFile\", regenerate Makefile.\n"
				);
			}
		}
		else {
			&main::Output(
				"\n",
				"\t\@echo Not attempting to create \"\$(EPOCLIB)\\UDEB\\$BaseTrg.LIB\"\n",
				"\t\@echo from frozen .DEF file, since EXPORTUNFROZEN specified.\n"
			);
		}
	}
	&main::Output(
		"\n",
		"\n",
		"FREEZE :\n"
	);
	if ($DefFile) {
		&main::Output(
#			call perl on the script here so nmake will die if there are errors - this doesn't happen if calling perl in a batch file
			"\tperl -S efreeze.pl \"$DefFile\" \"\$(EPOCBLD)\\$BaseTrg.def\" \n"
		);
	}
	&main::Output(
		"\n",
		"CLEANLIBRARY :\n"
	);
	if ($DefFile) {
		&main::Output(
			"\t-\$(ERASE) \"\$(EPOCLIB)\\UDEB\\$BaseTrg.LIB\"\n"
		);
	}
	&main::Output(
		"\n"
	);
	&Generic_MakeWorkDir('MAKEWORKLIBRARY',"${LibPath}UDEB");

	&Generic_Releaseables;
}

my $uidfile;
sub PMBld {

	my $AifStructRef=&main::AifStructRef;
	my @BaseSrcList=&main::BaseSrcList;
	my $BaseTrg=&main::BaseTrg;
	my $BitMapStructRef=&main::BitMapStructRef;
	my $Bld=&main::Bld;
	my $ChopBldPath=&main::Path_Chop(&main::BldPath);
	my $DefFile=&main::DefFile;
	my $EPOCIncPath=&main::EPOCIncPath;
	my $FirstLib=&main::FirstLib;
	my $BasicTrgType=&main::BasicTrgType;
	my @LibList;
	my $RelPath=&main::RelPath;
	my $ResourceStructRef=&main::ResourceStructRef;
	my @StatLibList=&main::StatLibList;
	my $Trg=&main::Trg;
	my $TrgPath=&main::TrgPath;
	my $TrgType=&main::TrgType;

	$uidfile = "$BaseTrg.UID";

	if ($Bld =~ /DEB/) {
		@LibList=&main::DebugLibList;
	} else {
		@LibList=&main::LibList;
	}

	my $BLDTRGPATH = "\$(EPOCTRG$Bld)\\";
	if ($TrgPath) {
		$BLDTRGPATH .= "\$(TRGDIR)\\";	    # handles TARGETPATH
	}

	# REAL TARGETS
	#-------------
	&main::Output(
		"# REAL TARGET - BUILD VARIANT $Bld\n",
		"\n"
	);

#	releasables
	my @releaseables;
	
#tools hack
	unless (&main::Plat() eq 'TOOLS') {
		push @releaseables, "$BLDTRGPATH$Trg";
		if ($Bld=~/REL$/o && $BasicTrgType!~/^LIB$/o) {
			push @releaseables,"$BLDTRGPATH$Trg.map";
		}
		if (&Winutl_CopyForStaticLinkage) {
			push @releaseables, "\$(EPOCTRG$Bld)\\$Trg";
		}
		my $BitMapRef;
		foreach $BitMapRef (@$BitMapStructRef) {
			push @releaseables, "\$(EPOCTRG$Bld)\\$$BitMapRef{TrgPath}$$BitMapRef{Trg}";
		}
		my $ResourceRef;
		foreach $ResourceRef (@$ResourceStructRef) {
			push @releaseables,"\$(EPOCTRG$Bld)\\$$ResourceRef{Trg}";
		}
		my $AifRef;
		foreach $AifRef (@$AifStructRef) {
			push @releaseables, "$BLDTRGPATH$$AifRef{Trg}";
		}
		if (-e $DefFile) { # effectively "if project frozen ..."
			push @releaseables, "\$(EPOCLIB$Bld)\\$BaseTrg.LIB";
		}
		if ($Bld=~/DEB$/o) {
			# debugging support files?
		}
	}
	else {
		my $toolspath=&main::EPOCToolsPath();
		push @releaseables, "$toolspath$Trg";
	}
#tools hack end

	&main::Output(
		"WHAT$Bld : WHATGENERIC\n",
		"\n",
		"CLEAN$Bld : CLEANBUILD$Bld CLEANRELEASE$Bld\n",
		"\n",
		"CLEANBUILD$Bld : \n",
		"\t\@perl -S ermdir.pl \"\$(EPOCBLD$Bld)\"\n",
		"\n",
		"CLEANRELEASE$Bld : CLEANGENERIC\n",
		"\n"
	);
	&Generic_WhatCleanTargets($Bld, "WHAT$Bld", "CLEANRELEASE$Bld", @releaseables);

	&Generic_MakeWorkDir("MAKEWORK$Bld", &main::BldPath);
	&Generic_MakeWorkDir("MAKEWORK$Bld", "$RelPath$TrgPath");

	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"LISTING$Bld : MAKEWORK$Bld"
	);
	foreach (@BaseSrcList) {
		&main::Output(
			" \\\n\tLISTING$Bld$_"
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"LIBS$Bld="
	);
	foreach (@StatLibList) {
		&main::Output(
			" \\\n\t", &Generic_Quote("\$(EPOCSTATLINK$Bld)\\$_")
		);
	}
	foreach (@LibList) {
		&main::Output(
			" \\\n\t", &Generic_Quote("\$(EPOCLINK$Bld)\\$_")
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"LINK_OBJS$Bld="
	);
	my $have_uidfile = 0;
	foreach (@BaseSrcList) {
		if ($_ eq $uidfile) {
			$have_uidfile = 1;
			next;
		}
		&main::Output(
			" \\\n",
			"\t", &Generic_Quote("\$(EPOCBLD$Bld)\\$_.o")
		);
	}
	if ($Win32Resrc) {
		my $resbase=&main::Path_Split('Base',$Win32Resrc);
		&main::Output(
			" \\\n",
			"\t", &Generic_Quote("\$(EPOCBLD$Bld)\\$resbase.res")
		);
	}
	if ($have_uidfile) {
		# ensure that the uid file is at the end of the list, as it's implicit in
		# CodeWarrior IDE projects.
		&main::Output(
			" \\\n",
			"\t", &Generic_Quote("\$(EPOCBLD$Bld)\\uid.o")
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::OutFormat(
		"COMMON_LINK_FLAGS$Bld=",
		' -msgstyle gcc',
		' -stdlib'		# FIXME: use default runtime library for compiler help functions
	);
	if ($MWLD eq "mwcc.exe") {
		&main::OutFormat(
			' -warnings on'	# on by default in mwccsym2.exe
		);
	}
	if ($BasicTrgType=~/^(EXE|DLL)$/o) {
# tools hack
		unless (&main::Plat eq 'TOOLS') {
			&main::OutFormat(
				" \"\$(EPOCSTATLINK$Bld)\\$FirstLib\""
			);
		}
# tools hack end
	}
	foreach my $lib (@Win32LibList) {
		 my $win32lib = $lib;    # take a copy, to avoid updating contents of Win32LibList!
		$win32lib = "-l$win32lib" unless ($win32lib =~ /\\/);
		&main::OutFormat(
			" ",lc $win32lib
		);
	}
	if ($BasicTrgType=~/^DLL$/o) {
		&main::OutFormat(
			"$BaseAddressFlag",
			' -m "?_E32Dll@@YGHPAXI0@Z"',
			' -shared'
		);
	}
	elsif ($BasicTrgType=~/^EXE$/o) {
# tools hack
		unless (&main::Plat eq 'TOOLS') {
			&main::OutFormat(
				' -m "?_E32Startup@@YGXXZ"'
			);
		}
# tools hack end
	}
	if (&main::Plat=~/^(WINC|TOOLS)$/o && $BasicTrgType=~/^EXE$/o) {
		&main::OutFormat(
			' -subsystem console'
		);
	}
	else {
		&main::OutFormat(
			' -subsystem windows'
		);
	}
	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
		if ($Bld=~/DEB$/o) {
			&main::OutFormat(
				' -g'
			);
		}
	}
	&main::Output(
		"\n",
		"\n"
	);

	if ($BasicTrgType=~/^DLL$/o) {
		&main::Output(
			"STAGE1_LINK_FLAGS$Bld= \$(COMMON_LINK_FLAGS$Bld) \$(LIBS$Bld) \\\n\t",
			" -o \"\$(EPOCBLD$Bld)\\$Trg\"", 
			' -export dllexport', 
			' -nocompactimportlib', 
			" -implib \"\$(EPOCBLD$Bld)\\$BaseTrg.lib\"",
			" -addcommand \"out:$Trg\" -warnings off",
			"\n",
		);
	}

	&main::Output(
		"LINK_FLAGS$Bld= \$(COMMON_LINK_FLAGS$Bld) \$(LIBS$Bld) \\\n\t",
		" -o \"$BLDTRGPATH$Trg\"" 
	);
	if ($Bld=~/REL$/o && $BasicTrgType!~/^LIB$/o) {
		# Generate map file for release build executables
		&main::Output(
			" -map \"$BLDTRGPATH$Trg.map\"", 
		);
	}
	if ($BasicTrgType=~/^DLL$/o) {
		&main::Output(
			" -f \"\$(EPOCBLD)\\$BaseTrg.def\"",	# use generated .DEF file
		);
		if (&main::ExportUnfrozen) {
			&main::Output(
				" -implib \"\$(EPOCLIB)\\UDEB\\$BaseTrg.LIB\"",
				" -addcommand \"out:$Trg\" -warnings off"
			);
		}
		else {
			&main::Output(
				' -noimplib'
			);
		}
	}
	else {
		&main::Output(
			' -export none -noimplib'	# ignore spurious exports
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		&Generic_Quote("$BLDTRGPATH$Trg"), " : \$(LINK_OBJS$Bld) "
	);
	if (-e $DefFile) { # effectively "if project frozen ..."
		&main::Output(
			&Generic_Quote($DefFile)
		);
	}
	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
# tools hack
		unless (&main::Plat eq 'TOOLS') {
			&main::Output(
				" ", &Generic_Quote("\$(EPOCSTATLINK$Bld)\\$FirstLib")
			);
		}
	}
# tools hack end
	&main::Output(
		" \$(LIBS$Bld)\n"
	);


#	Link by name first time round for dlls
	if ($BasicTrgType=~/^DLL$/o) {
		&main::Output(
			"\t$MWLD \$(STAGE1_LINK_FLAGS$Bld) \$(LINK_OBJS$Bld)\n",
			"\t\$(ERASE) \"\$(EPOCBLD$Bld)\\$Trg\"\n",
		);

#		Generate an export info file
		my $show_options = "names,verbose";
		$show_options = "names,unmangled,verbose" if ($MWLD eq "mwldsym2.exe");
		&main::Output(
			"\t$MWLD -S -show only,$show_options -o \"\$(EPOCBLD$Bld)\\$BaseTrg.inf\" \"\$(EPOCBLD$Bld)\\$BaseTrg.lib\"\n"
		);

#		call makedef to reorder the export information
		&main::Output(
#			call perl on the script here so nmake will die if there are errors - this doesn't happen if calling perl in a batch file
			"\tperl -S makedef.pl -Inffile \"\$(EPOCBLD$Bld)\\$BaseTrg.inf\""
		);
		if (-e $DefFile) { # effectively "if project frozen ..."
			&main::Output(
				" -Frzfile \"$DefFile\""
			);
		}
		else { # freeze exports for polymorphic dlls
			my $Export;
			my $Ordinal=1;
			foreach $Export (&main::Exports) {
#				replace "$" with "$$" so that NMAKE doesn't think there's a macro in the function name
				$Export=~s-\$-\$\$-go;
				&main::Output(
					" -$Ordinal $Export"
				);
				$Ordinal++;
			}
		}
		&main::Output(
			" \"\$(EPOCBLD)\\$BaseTrg.def\" \n",
			"\t\$(ERASE) \"\$(EPOCBLD$Bld)\\$BaseTrg.inf\"\n",
			"\t\$(ERASE) \"\$(EPOCBLD$Bld)\\$BaseTrg.lib\"\n"
		);
	}

#	Perform the final link step
	&main::Output(
		"\t$MWLD "
	);
	if ($BasicTrgType=~/^LIB$/o) {
		&main::Output(
			"-library "
		);
	}
	&main::Output(
		"\$(LINK_FLAGS$Bld) \$(LINK_OBJS$Bld)\n",
	);

# tools hack
	if (&main::Plat eq 'TOOLS') {
		&main::Output(
			"\tcopy \"BLDTRGPATH$Trg\" \"",&main::EPOCToolsPath,"$Trg\"\n"
		);
	}
# tools hack end
	if (&Winutl_CopyForStaticLinkage) {
		&Generic_MakeWorkDir("MAKEWORK$Bld", "\$(EPOCTRG$Bld)");
		&main::Output(
			"\n",
			&Generic_Quote("\$(EPOCTRG$Bld)\\$Trg"), " : ", 
			&Generic_Quote("$BLDTRGPATH$Trg"), "\n",
			"\t", &Generic_CopyAction(),
		);
	}

	&main::Output(
		"\n",
		"\n"
	);
}

sub PMStartSrcList {

	&main::Output(
		"# SOURCES\n",
		"\n"
	);
}

sub PMBitMapBld {

	&Generic_BitMapBld;

	# Need to copy generic resource into emulated Z drive

	my $BitMapRef=&main::BitMapRef;

	my $ChopTrgPath="";
	if ($$BitMapRef{TrgPath}) {
		$ChopTrgPath.="\\$$BitMapRef{TrgPath}";
		chop $ChopTrgPath;
	}

	my @BldList=&main::BldList;
	my $Bld;
	foreach $Bld (@BldList) {
		my $path="\$(EPOCTRG$Bld)$ChopTrgPath";
		&main::Output(
			&Generic_Quote("$path\\$$BitMapRef{Trg}"), " : ", 
			&Generic_Quote("$$BitMapRef{GenericTrg}"), "\n",
			"\t", &Generic_CopyAction(),
			"\n"
		);
	}
}

sub PMResrcBld {

	&Generic_ResrcBld;

	# Need to copy generic resource into emulated Z drive

	my $ResourceRef=&main::ResourceRef;
	my @BldList=&main::BldList;

	foreach my $Bld (@BldList) {
		&main::Output(
			&Generic_Quote("\$(EPOCTRG$Bld)\\$$ResourceRef{Trg}"), " : ", 
			&Generic_Quote("$$ResourceRef{GenericTrg}"), "\n",
			"\t", &Generic_CopyAction(),
			"\n"
		);
	}
}

sub PMAifBld {

	&Generic_AifBld;

	# Need to copy generic resource into emulated Z drive

	my $AifRef=&main::AifRef;
	my $TrgDir="";
	if (&Generic_Definition("TRGDIR") ne "") {
		$TrgDir="\\\$(TRGDIR)";
	}

	my @BldList=&main::BldList;
	my $Bld;
	foreach $Bld (@BldList) {
		my $path="\$(EPOCTRG$Bld)$TrgDir";
		&main::Output(
			&Generic_Quote("$path\\$$AifRef{Trg}"), " : ",
			&Generic_Quote("$$AifRef{GenericTrg}"), "\n",
			"\t", &Generic_CopyAction(),
			"\n"
		);
	}
}

sub PMStartSrc {
	my $Src=&main::Src;

	&main::Output(
		"# Source $Src\n",
		"\n"
	);
}

sub PMSrcDepend {
	my @BldList=&main::BldList;	
	my @DepList=&main::DepList;
	my $BaseSrc=&main::BaseSrc;
	$BaseSrc = "uid" if ($BaseSrc eq $uidfile);

	return if (@DepList == 0);

	foreach (@BldList) {
		&main::Output(
			&Generic_Quote("\$(EPOCBLD$_)\\$BaseSrc.o"), " \\\n",
		);
	}
	&main::Output(
		":"
	);
	foreach (@DepList) {
		&main::Output(
		" \\\n\t", &Generic_Quote($_)
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
}

sub PMSrcBldDepend {
	my $Bld=&main::Bld;
	my @DepList=&main::DepList;
	my $BaseSrc=&main::BaseSrc;
	$BaseSrc = "uid" if ($BaseSrc eq $uidfile);

	return if (@DepList == 0);

	&main::Output(
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.o"), " :",
	);
	foreach (@DepList) {
		&main::Output(
			" \\\n\t", &Generic_Quote($_)
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
}

sub PMEndSrcBld {
	my $BaseSrc=&main::BaseSrc;
	$BaseSrc = "uid" if ($BaseSrc eq $uidfile);
	my $Bld=&main::Bld;
	my $Plat=&main::Plat;
	my $Src=ucfirst lc &main::Src;
	my $SrcPath=&main::SrcPath;

	&main::Output(
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.o"), " : ",
		&Generic_Quote("$SrcPath$Src"), "\n",
		"\t\$(CW$Bld) -o \"\$\@\" -c \"$SrcPath$Src\"\n",
		"\n",
#		assembler listing target - uses implicit rule to do disassembly
		"LISTING$Bld$BaseSrc : ", &Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.lis"), "\n",
		"\t", &Generic_CopyAction("$SrcPath$BaseSrc.lst.$Plat"),
		"\n"
	);
}

sub PMEndSrc {

	&main::Output(
		"\n",
		"\n"
	);
}

sub PMEndSrcList {

	my $show_options = "source";
	$show_options = "source,unmangled,comments" if ($MWLD eq "mwldsym2.exe");
	
	&main::Output(
		"\n",
		"# Implicit rule for generating .lis files\n",
		"\n",
		".SUFFIXES : .lis .o\n",
		"\n",
		".o.lis:\n",
		"\t$MWLD -S -show $show_options \$< -o \$\@\n",
		"\n",
		"\n"
	);

	if ($Win32Resrc) {
		my @BldList=&main::BldList;
		my @DepList=&main::Deps_GenDependsL($Win32Resrc);

		&main::Output(
			"# Win32 Resource $Win32Resrc\n",
			"\n",
			"DEPEND="
		);
		foreach (@DepList) {
			&main::Output(
				" \\\n\t", &Generic_Quote($_)
			);
		}
		&main::Output(
			"\n",
			"\n"
		);
	
		my $Bld;
		my $resbase=&main::Path_Split('Base',$Win32Resrc);
		my $respath=&main::Path_Chop(&main::Path_Split('Path',$Win32Resrc));
		foreach $Bld (@BldList) {
			&main::Output(
				&Generic_Quote("\$(EPOCBLD$Bld)\\$resbase.res"), " : ",
				&Generic_Quote($Win32Resrc), " \$(DEPEND)\n",
				"\tmwwinrc -o \$\@ \"$Win32Resrc\"\n",
				"\n"
			);
		}
		&main::Output(
			"\n",
			"\n"
		);
	}

	# Deal with accumulated MAKEDIRS etc.

	&Generic_End;
}

1;
