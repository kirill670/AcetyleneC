# CL_WIN.PM
#
# Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
#


package Cl_win;

# declare variables global for module
my @Win32LibList=();
my $BaseAddressFlag;
my $Win32Resrc;



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
use Pathutl;

sub PMHelp_Mmp {
	&Winutl_Help_Mmp;
}

sub PMCheckPlatformL {
	if ((&main::Plat eq 'TOOLS') and (&main::BasicTrgType ne 'EXE')) {
		die "Can't specify anything but EXE targettypes for this platform\n";
	}
}

sub PMPlatProcessMmp (@) {

	&Winutl_DoMmp(\@_, $ENV{INCLUDE});
	$BaseAddressFlag=&Winutl_BaseAddress;
	$BaseAddressFlag=~s/^(.+$)$/ \/base:\"$1\"/o;
	@Win32LibList=&Winutl_Win32LibList;
	$Win32Resrc=&Winutl_Win32Resrc;
}

sub PMStartBldList($) {
	my ($makecmd) = @_;
	die "Cannot generate $makecmd makefiles\n" if ($makecmd ne "nmake");
	my $AifStructRef=&main::AifStructRef;
	my $BaseTrg=&main::BaseTrg;
	my $BitMapStructRef=&main::BitMapStructRef;
	my @BldList=&main::BldList;
	my @ChopSysIncPaths=&main::Path_Chop(&main::SysIncPaths);
	my @ChopUserIncPaths=&main::Path_Chop(&main::UserIncPaths);
	my $ExportLibrary=&main::ExportLibrary;
	my $NoExportLibrary=&main::NoExportLibrary;
	my $DefFile=&main::DefFile;
	my $BasicTrgType=&main::BasicTrgType;
	my $LibPath=&main::LibPath;
	my @MacroList=&main::MacroList();
	my $VariantFile=&main::VariantFile();
	my $Plat=&main::Plat;
	my $ResourceStructRef=&main::ResourceStructRef;
	my $Trg=&main::Trg;
	my $TrgType=&main::TrgType;
	my $defaultWarningLevel="/W4";
	my $CompilerOption=&main::CompilerOption("MSVC");
	my $LinkAs=&main::LinkAs;

	&Generic_Header(0,$makecmd);	# define standard things using absolute paths

	my $TrgDir="";
	if (&Generic_Definition("TRGDIR") ne "") {
		$TrgDir="\$(TRGDIR)\\";
	}
	if (&main::Plat eq "WINC") {	# target path ignored under WINC
		$TrgDir="";
	}

	&main::Output(
		"INCDIR  ="
	);
	if($VariantFile){
		my $VariantFileFileName  = Path_Split('FILE',$VariantFile);
	    &main::Output(
			  " /FI \"$VariantFileFileName\"",
			  );
	}

	foreach (@ChopUserIncPaths,@ChopSysIncPaths) {
		&main::Output(
			" /I \"$_\""
		);
	}

	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"CLFLAGS =",
			" /nologo",			# suppress "sign-on" banner message
			" /Zp4",			# packs structures on 4 byte boundaries
			" /GF"				# Pools strings and places them in read-only memory 
		);	

# tools hack in line below
	if (&main::Plat eq 'TOOLS') {
#--- not yet ---
#		$defaultWarningLevel="/W3";		# to avoid /W4 warnings in Standard Template Library
#		&main::Output(
#			" /GX",				# Enables synchronous C++ exception handling
#			" /GR"				# Enables run-time type information (RTTI)
#		);
#--- not yet ---
	}
	else {
		unless (@Win32LibList) {
			&main::Output(
				" /X"			# ignore standard include directories
			);
		}
	}
	if ($CompilerOption !~ /\/W\d/) {
		# Supply default warning level unless /Wn already specified via OPTION MSVC
		&main::Output(
			" $defaultWarningLevel"
		);
	}
	&main::Output(
		" $CompilerOption",		# user-supplied compiler options
		"\n",
		"\n"
	);

	&main::Output(
		"CLDEFS  ="
	);
	foreach(@MacroList) {
		&main::Output(
			" /D \"$_\""
		);
	}
	&main::Output(
		" \$(USERDEFS)\n",
		"\n"
	);

	foreach (@BldList) {
		&main::Output(
			"CL$_ = cl.exe"
		);
		if ($BasicTrgType=~/^EXE$/o) {
			&main::Output(
				' /ML'			# Creates a single-threaded executable file, using LIBC.LIB
			);
		}
		elsif ($BasicTrgType=~/^(DLL|LIB)$/o) {
			&main::Output(
				' /MD'			# Creates a multithreaded DLL, using MSVCRT.LIB
			);
		}
		if (/DEB$/o) {
			&main::Output(
				'd'				# i.e. /MLd or /MDd, debug executable using debug version of LIB
			);
		}
		if (/DEB$/o) {
			&main::Output(
				' /Zi',			# Generates complete debugging information
				' /Od'			# Disables optimization
			);
#			euser hack to apply inlining on the _NAKED functions
			if ($BaseTrg=~/^EUSER$/o) {
				&main::Output(
					' /Ob1'		# Specific control of expension of inline functions
				);
			}
		}
		elsif (/REL$/o) {
#			euser hack to prevent minimum size optimisation from disrupting the maths functions
			unless ($BaseTrg=~/^EUSER$/o) {
				&main::Output(
					' /O1',		# Creates small code
					' /Op'		# Improves floating-point consistency
				);
			}
			else {
				&main::Output(
					' /Od',		# Disables optimization
					' /Ob1'		# Specific control of expension of inline functions
				);
			}
		}
		&main::Output(
			' $(CLFLAGS)'
		);
		if (/DEB$/o) {
			&main::Output(
				" /FR\"\$(EPOCBLD$_)/\" /Fd\"\$(EPOCTRG$_)\\$TrgDir$BaseTrg.pdb\""
			);
		}
		foreach (&main::MacroList($_)) {
			&main::Output(
				" /D $_"
			);
		}
		&main::Output(
			" \$(CLDEFS) \$(INCDIR)\n"
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
		
		if ($BasicTrgType !~ /^IMPLIB$/io) {
			&main::Output (
				" \\\n",
				"\t\"\$(EPOCTRG$_)\\$TrgDir$Trg\""
			);
			unless (/REL$/o) {
				&main::Output(
					" \\\n",
					"\t\"\$(EPOCTRG$_)\\$BaseTrg.bsc\""
				);
			}
			if (&Winutl_CopyForStaticLinkage) {
				&main::Output(
					" \\\n",
					"\t\"\$(EPOCTRG$_)\\$Trg\""
				);
			}
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
				"\t\"$file\""
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
				"\t\"$file\""
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
	elsif ($DefFile and !$NoExportLibrary) {
		unless (&main::ExportUnfrozen) {
			if (-e $DefFile) { # effectively "if project frozen ..."
				&main::Output(
					" \"\$(EPOCLIB)\\UDEB\\$ExportLibrary.lib\"\n"
				);
			}
			else {
				&main::Output(
					"\n",
					"\t\@echo WARNING: Not attempting to create \"\$(EPOCLIB)\\UDEB\\$ExportLibrary.lib\".\n",
					"\t\@echo When exports are frozen in \"$DefFile\", regenerate Makefile.\n"
				);
			}
		}
		else {
			&main::Output(
				"\n",
				"\t\@echo Not attempting to create \"\$(EPOCLIB)\\UDEB\\$ExportLibrary.lib\"\n",
				"\t\@echo from frozen .DEF file, since EXPORTUNFROZEN specified.\n"
			);
		}
		my $LibLinkAs = ($BasicTrgType=~/^IMPLIB$/io) ? $LinkAs : $Trg;
		&main::Output(
			"\n",
			"\n",
			"# REAL TARGET - LIBRARY\n",
			"\n",
			"\"\$(EPOCLIB)\\UDEB\\$ExportLibrary.lib\" : \"$DefFile\"\n",
			"\tlib.exe /nologo /machine:i386 /nodefaultlib /name:\"$LibLinkAs\" /def:\"$DefFile\" /out:\"\$(EPOCLIB)\\UDEB\\$ExportLibrary.lib\"\n",
			"\tdel \"\$(EPOCLIB)\\UDEB\\$ExportLibrary.exp\"\n"
		);
	}
	&main::Output(
		"\n",
		"\n",
		"FREEZE :\n"
	);
	if ($DefFile and $BasicTrgType !~ /^IMPLIB$/io) {
		&main::Output(
#			call perl on the script here so nmake will die if there are errors - this doesn't happen if calling perl in a batch file
			"\tperl -S efreeze.pl \"$DefFile\" \"\$(EPOCBLD)\\$ExportLibrary.def\" \n"
		);
	}
	&main::Output(
		"\n",
		"CLEANLIBRARY :\n"
	);
	if ($DefFile and !$NoExportLibrary) {
		&main::Output(
			"\t-\$(ERASE) \"\$(EPOCLIB)\\UDEB\\$ExportLibrary.lib\"\n"
		);
	}
	&Generic_MakeWorkDir('MAKEWORKLIBRARY',"${LibPath}UDEB");

	&Generic_Releaseables;
}

sub PMBld {

	my $AifStructRef=&main::AifStructRef;
	my @BaseSrcList=&main::BaseSrcList;
	my $BaseTrg=&main::BaseTrg;
	my $BitMapStructRef=&main::BitMapStructRef;
	my $Bld=&main::Bld;
	my $ExportLibrary=&main::ExportLibrary;
	my $NoExportLibrary=&main::NoExportLibrary;
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

	my $WarningLevel='/WARN:3';
	if (&main::Plat() eq 'TOOLS') {
		$WarningLevel='/WARN:1';    # avoid LNK4005 warnings about unused libraries
	}

	if ($Bld =~ /DEB/) {
		@LibList=&main::DebugLibList;
	} else {
		@LibList=&main::LibList;
	}

	my $BLDTRGPATH = "\$(EPOCTRG$Bld)\\";
	my $BLDDATAPATH = "\$(EPOCTRG$Bld)\\";
	if (&main::Plat ne "WINC") {	# target paths ignored under WINC
		if (&Generic_Definition("TRGDIR") ne "") {
			$BLDTRGPATH .= "\$(TRGDIR)\\";	    # handles TARGETPATH
		}
		$BLDDATAPATH .= "\$(DATADIR)\\";
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
		if ($BasicTrgType !~ /^IMPLIB$/io) {
			push @releaseables, "$BLDTRGPATH$Trg";
			if (&Winutl_CopyForStaticLinkage) {
				push @releaseables, "\$(EPOCTRG$Bld)\\$Trg";
			}
			my $BitMapRef;
			foreach $BitMapRef (@$BitMapStructRef) {
				push @releaseables, "\$(EPOCTRG$Bld)\\$$BitMapRef{TrgPath}$$BitMapRef{Trg}";
			}
			my $ResourceRef;
			foreach $ResourceRef (@$ResourceStructRef) {
				push @releaseables, "\$(EPOCTRG$Bld)\\$$ResourceRef{Trg}";
			}
			my $AifRef;
			foreach $AifRef (@$AifStructRef) {
				push @releaseables, "$BLDTRGPATH$$AifRef{Trg}";
			}
			if ($Bld=~/DEB$/o) {
				push @releaseables,"$BLDTRGPATH$BaseTrg.PDB";
			}
		}
		if (-e $DefFile and !$NoExportLibrary) { # effectively "if project frozen ..."
			push @releaseables, "\$(EPOCLIB$Bld)\\$ExportLibrary.lib";
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
		"CLEANBUILD$Bld : CLEANILK$Bld\n",
		"\t\@perl -S ermdir.pl \"\$(EPOCBLD$Bld)\"\n",
		"\n",
		"CLEANRELEASE$Bld : CLEANGENERIC CLEANILK$Bld\n",
		"\n",
		"CLEANILK$Bld :\n",
		"\t-\$(ERASE) \"$BLDTRGPATH$BaseTrg.ILK\"\n",
		"\n"
	);
	&Generic_WhatCleanTargets($Bld, "WHAT$Bld", "CLEANRELEASE$Bld", @releaseables);

	&Generic_MakeWorkDir("MAKEWORK$Bld", &main::BldPath);
	&Generic_MakeWorkDir("MAKEWORK$Bld", $BLDTRGPATH);

	return if ($BasicTrgType =~ /^IMPLIB$/io);

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

	if ($Bld=~/DEB$/o) {
		&main::Output(
			"BSC32_SBRS="
		);
		foreach (@BaseSrcList) {
			&main::Output(
				" \\\n",
				"\t\"\$(EPOCBLD$Bld)\\$_.sbr\""
			);
		}
		&main::Output(
			"\n",
			"\n",
		"\"\$(EPOCTRG$Bld)\\$BaseTrg.bsc\" : \$(BSC32_SBRS)\n",
		"\tbscmake.exe \@<<\n",
		"\t/nologo /o\$\@ \$(BSC32_SBRS)\n",
		"<<\n",
		"\n",
		"\n"
		);
	}

	&main::Output(
		"LIBS="
	);
	foreach (@StatLibList) {
		&main::Output(
			" \\\n\t\"\$(EPOCSTATLINK$Bld)\\$_\""
		);
	}
	foreach (@LibList) {
		&main::Output(
			" \\\n\t\"\$(EPOCLINK$Bld)\\$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"LINK_OBJS="
	);
	foreach (@BaseSrcList) {
		&main::Output(
			" \\\n",
			"\t\"\$(EPOCBLD$Bld)\\$_.obj\""
		);
	}
	if ($Win32Resrc) {
		&main::Output(
			" \\\n",
			"\t\"\$(EPOCBLD$Bld)\\",&main::Path_Split('Base',$Win32Resrc),".res\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	if ($BasicTrgType=~/^DLL$/o) {
		&main::OutFormat(
			"STAGE1_LINK_FLAGS="
		);
		&main::OutFormat(
			"\"\$(EPOCSTATLINK$Bld)\\$FirstLib\""
		);
		foreach (@Win32LibList) {
			&main::OutFormat(
				' ',lc $_
			);
		}
		&main::OutFormat(
			" \$(LIBS) /nologo$BaseAddressFlag /entry:\"_E32Dll\" /subsystem:windows /dll"
		);
		if ($Bld=~/DEB$/o) {
			&main::OutFormat(
				' /debug'
			);
		}
		&main::OutFormat(
			" /incremental:no /machine:IX86 /nodefaultlib /include:\"",'?_E32Dll@@YGHPAXI0@Z',"\" /out:\"\$(EPOCBLD$Bld)\\$Trg\" $WarningLevel /implib:\"\$(EPOCBLD$Bld)\\$ExportLibrary.lib\""
		);
		&main::Output(
			"\n",
			"\n"
		);
	}

	&main::OutFormat(
		'LINK_FLAGS='
	);
	if ($BasicTrgType=~/^(EXE|DLL)$/o) {
# tools hack
		unless (&main::Plat eq 'TOOLS') {
			&main::OutFormat(
				" \"\$(EPOCSTATLINK$Bld)\\$FirstLib\""
			);
		}
# tools hack end
	}
	foreach (@Win32LibList) {
		&main::OutFormat(
			' ',lc $_
		);
	}
	&main::OutFormat(
		' $(LIBS) /nologo'
	);
	if ($BasicTrgType=~/^DLL$/o) {
		&main::OutFormat(
			"$BaseAddressFlag /entry:\"_E32Dll\""
		);
	}
	elsif ($BasicTrgType=~/^EXE$/o) {
# tools hack
		unless (&main::Plat eq 'TOOLS') {
			&main::OutFormat(
				" /entry:\"_E32Startup\""
			);
		}
# tools hack end
	}
	if (&main::Plat=~/^(WINC|TOOLS)$/o && $BasicTrgType=~/^EXE$/o) {
		&main::OutFormat(
			' /subsystem:console'
		);
	}
	else {
		&main::OutFormat(
			' /subsystem:windows'
		);
	}
	if ($BasicTrgType=~/^DLL$/o) {
		&main::OutFormat(
			" /dll \"\$(EPOCBLD$Bld)\\$ExportLibrary.exp\""
		);
	}
	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
		if ($Bld=~/DEB$/o) {
			&main::OutFormat(
				' /debug'
			);
		}
		elsif ($Bld=~/REL$/o) {
			&main::OutFormat(
				' /incremental:no'
			);
		}
	}
	&main::OutFormat(
		' /machine:IX86'
	);
# tools hack
	unless (&main::Plat eq 'TOOLS') {
		&main::OutFormat(
			' /nodefaultlib'
		);
		if ($BasicTrgType=~/^DLL$/o) {	# force link to edll.lib
			&main::OutFormat(
				" /include:\"",'?_E32Dll@@YGHPAXI0@Z',"\""
			);
		}
		elsif ($BasicTrgType=~/^EXE$/o) {	# force link to eexe.lib
			&main::OutFormat(
				" /include:\"",'?_E32Startup@@YGXXZ',"\""
			);
		}
	}
# tools hack end
	&main::OutFormat(
		" /out:\"$BLDTRGPATH$Trg\""
	);
	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
		&main::OutFormat(
			" $WarningLevel",
			" /implib:\"$BLDTRGPATH$ExportLibrary.lib\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"\"$BLDTRGPATH$Trg\" : \$(LINK_OBJS)"
	);
	if (-e $DefFile) { # effectively "if project frozen ..."
		&main::Output(
			" \"$DefFile\""
		);
	}
	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
# tools hack
		unless (&main::Plat eq 'TOOLS') {
			&main::Output(
				" \"\$(EPOCSTATLINK$Bld)\\$FirstLib\""
			);
		}
	}
# tools hack end
	&main::Output(
		" \$(LIBS)\n"
	);


#	Link by name first time round for dlls
	if ($BasicTrgType=~/^DLL$/o) {
		&main::Output(
			"\tlink.exe \@<<\n",
			"\t\t\$(STAGE1_LINK_FLAGS) \$(LINK_OBJS)\n",
			"<<\n",
			"\tdel \"\$(EPOCBLD$Bld)\\$Trg\"\n",
			"\tdel \"\$(EPOCBLD$Bld)\\$ExportLibrary.exp\"\n"
		);

#		Generate an export info file
		&main::Output(
			"\tdumpbin /exports /out:\"\$(EPOCBLD$Bld)\\$ExportLibrary.inf\" \"\$(EPOCBLD$Bld)\\$ExportLibrary.lib\"\n",
			"\tdel \"\$(EPOCBLD$Bld)\\$ExportLibrary.lib\"\n"
		);

#		call makedef to reorder the export information
		&main::Output(
#			call perl on the script here so nmake will die if there are errors - this doesn't happen if calling perl in a batch file
			"\tperl -S makedef.pl -Inffile \"\$(EPOCBLD$Bld)\\$ExportLibrary.inf\""
		);
		if (-e $DefFile) { # effectively "if project frozen ..."
			&main::Output(
				" -Frzfile \"$DefFile\""
			);
		}
		else { # freeze ordinals, a maximum of 2, for polymorphic dlls
			my $Ordinal;
			my $Num=1;
			foreach $Ordinal (&main::Exports) {
#				replace "$" with "$$" so that NMAKE doesn't think there's a macro in the function name
				$Ordinal=~s-\$-\$\$-go;
				&main::Output(
					" -$Num $Ordinal"
				);
				$Num++;
			}
		}
		&main::Output(
			" \"\$(EPOCBLD)\\$ExportLibrary.def\" \n",
			"\tdel \"\$(EPOCBLD$Bld)\\$ExportLibrary.inf\"\n"
		);

		# create the export object from the .DEF file
		&main::Output(
			"\tlib.exe  /nologo /machine:i386 /nodefaultlib /name:\"$Trg\" /def:\"\$(EPOCBLD)\\$ExportLibrary.def\" /out:\"\$(EPOCBLD$Bld)\\$ExportLibrary.lib\"\n"
		);
		if (&main::ExportUnfrozen) {
			&main::Output(
			"\tcopy \"\$(EPOCBLD$Bld)\\$ExportLibrary.lib\" \"\$(EPOCLIB)\\UDEB\\$ExportLibrary.lib\"\n"
			);
		}
		&main::Output(
			"\tdel \"\$(EPOCBLD$Bld)\\$ExportLibrary.lib\"\n"
		);
	}

	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
		&main::Output(
			"\tlink.exe \@<<\n"
		);
	}
	elsif ($BasicTrgType=~/^LIB$/o) {
		&main::Output(
			"\tlib.exe \@<<\n"
		);
	}
	&main::Output(
		"\t\t\$(LINK_FLAGS) \$(LINK_OBJS)\n",
		"<<\n"
	);

	if ($BasicTrgType=~/^DLL$/o) {
		&main::Output(
			"\tdel \"\$(EPOCBLD$Bld)\\$ExportLibrary.exp\"\n"
		);
	}

# tools hack
	if (&main::Plat eq 'TOOLS') {
		&main::Output(
			"\tcopy \"$BLDTRGPATH$Trg\" \"",&main::EPOCToolsPath,"$Trg\"\n"
		);
	}
# tools hack end
	if (&Winutl_CopyForStaticLinkage) {
		&Generic_MakeWorkDir("MAKEWORK$Bld", "\$(EPOCTRG$Bld)");
		&main::Output(
			"\n",
			"\"\$(EPOCTRG$Bld)\\$Trg\" : \"$BLDTRGPATH$Trg\"\n",
			"\tcopy \$\? \$\@\n"
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
	if (&main::Plat eq "WINC") {	# target path ignored under WINC
		$TrgDir="";
	}

	my @BldList=&main::BldList;
	my $Bld;
	foreach $Bld (@BldList) {
		my $file="\$(EPOCTRG$Bld)$TrgDir\\$$AifRef{Trg}";
		&main::Output(
			"\"$file\" : \"$$AifRef{GenericTrg}\"\n",
			"\tperl -S ecopyfile.pl \$? \$\@\n",
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

	&main::Output(
		"DEPEND="
	);
	foreach (@DepList) {
		&main::Output(
		" \\\n\t\"$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
	foreach (@BldList) {
		&main::Output(
			"DEPEND$_=\$(DEPEND)\n",
			"\n"
		);
	}
	&main::Output(
		"\n"
	);
}

sub PMSrcBldDepend {
	my $Bld=&main::Bld;
	my @DepList=&main::DepList;

	&main::Output(
		"DEPEND$Bld="
	);
	foreach (@DepList) {
		&main::Output(
			" \\\n\t\"$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
}

sub PMEndSrcBld {
	my $BaseSrc=&main::BaseSrc;
	my $Bld=&main::Bld;
	my $Plat=&main::Plat;
	my $Src=ucfirst lc &main::Src;
	my $SrcPath=&main::SrcPath;

	&main::Output(
		"\"\$(EPOCBLD$Bld)\\$BaseSrc.obj\" \"\$(EPOCBLD$Bld)\\$BaseSrc.sbr\" : \"$SrcPath$Src\" \$(DEPEND$Bld)\n",
		"\t\$(CL$Bld) /Fo\"\$(EPOCBLD$Bld)/\" /c \"$SrcPath$Src\"\n",
		"\n",
#		assembler listing target 
		"LISTING$Bld$BaseSrc : \"\$(EPOCBLD$Bld)\\$BaseSrc.lis\"\n",
		"\tcopy \$? \"$SrcPath$BaseSrc.lst.$Plat\"\n",
		"\n",
		"\"\$(EPOCBLD$Bld)\\$BaseSrc.lis\": \"$SrcPath$Src\" \$(DEPEND$Bld)\n",
		"\t\$(CL$Bld) /Fa\"\$\@\" /Fo\"\$(EPOCBLD$Bld)/\" /c \"$SrcPath$Src\"\n",
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
				" \\\n\t\"$_\""
			);
		}
		&main::Output(
			"\n",
			"\n"
		);
	
		my $Bld;
		foreach $Bld (@BldList) {
			&main::Output(
				"\"\$(EPOCBLD$Bld)\\",&main::Path_Split('Base',$Win32Resrc),".res\" : \"$Win32Resrc\" \$(DEPEND)\n",
				"\trc /l 0x809 /fo\$\@ /i \"",&main::Path_Chop(&main::Path_Split('Path',$Win32Resrc)),"\" \"$Win32Resrc\"\n",
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
