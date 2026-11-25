# CL_GCC.PM
#
# Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
#


package Cl_gcc;

my $GccPrefix='';
my $ToolPrefix='';
my $HelperLib='';
my %PlatOpt=(
	'Dlltool'=>'',
	'Entry'=>'-e',
	'Gcc'=>'',
	'Ld'=>'',
	'Petran'=>'',
	'Optimize'=>'-O'
);
my $Dlltool;
my $Archive;
my $Link;
my $Objcopy;

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	PMHelp_Mmp

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

use cl_generic;

sub PMHelp_Mmp {
	print "// No additional keywords for this platform\n";
}

sub PMPlatProcessMmp (@) {
	my $MMPFILE=&main::MmpFile;

	# set up START MARM ... END block module variables
	my @MmpWarn=();
	my $Line;
	LINE: foreach $Line (@_) {
		my $LineInfo=shift @$Line;
		$_=shift @$Line;
		push @MmpWarn, "$LineInfo : Unrecognised Keyword \"$_\"\n";
	}

	undef $Line;
	if (@MmpWarn) {
		warn
			"\nMMPFILE \"$MMPFILE\"\n",
			"START .. END BLOCK WARNINGS(S)\n",
			@MmpWarn,
			"\n"
		;
	}
	undef @MmpWarn;
}

my $Makecmd;
my %ABILibPath=();
sub PMStartBldList($) {
	($Makecmd) = @_;
	my $ABI=&main::ABI;
	my $BaseTrg=&main::BaseTrg;
	my $BasicTrgType=&main::BasicTrgType;
	my @BldList=&main::BldList;
	my @ChopRTWSysIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::SysIncPaths));
	my @ChopRTWUserIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::UserIncPaths));
	my @CompatibleABIs=&main::CompatibleABIs;
	my $DefFile=&main::DefFile;
	my $EPOCPath=&main::EPOCPath;
	my $LinkAs=&main::LinkAs;
	my $LibPath=&main::LibPath;
	my @MacroList=&main::MacroList();
	my $Plat=&main::Plat;
	my $Trg=&main::Trg;
	my $TrgType=&main::TrgType;
	my @UidList=&main::UidList;	
	my $WarningLevel=&main::CompilerOption("GCC");



#	set up LinkAs
	$UidList[2]=~/^0x(.*)$/o;
	if ($1 ne '00000000') { # have to make sure than series of noughts in brackets doesn't appear in name for null uids
		$LinkAs=join '', &main::Path_Split('Base',$LinkAs),"[$1]",&main::Path_Split('Ext',$LinkAs);
	}

#	set up CompatibleABI lib path hash
	foreach (@CompatibleABIs) {
		$ABILibPath{$_}=&main::Path_Strip("$LibPath..\\$_\\");
	}
	my %ABIRTWLibPath=();
	foreach (@CompatibleABIs) {
		$ABIRTWLibPath{$_}=&main::Path_RltToWork($ABILibPath{$_});
	}

#	set up dlltool flag hash
	my %ABIDlltool=(
		ARMI=>'-m arm_interwork',
		ARM4=>'-m arm',
		THUMB=>'-m thumb'
	);

#	work out the flags for various platforms
	if ($ABI eq 'ARMI') {
		$PlatOpt{Gcc}='-march=armv4t -mthumb-interwork';
		$PlatOpt{Dlltool}=$ABIDlltool{ARMI};
	}
	elsif ($ABI eq 'ARM4') {
		$PlatOpt{Gcc}='-march=armv4';
#		allow thumb for ARM4 ABI where necessary
		unless (&main::PlatABI eq 'ARM4') {
			$PlatOpt{Gcc}.='t';
		}
		$PlatOpt{Dlltool}=$ABIDlltool{ARM4};
	}
	elsif ($ABI eq 'THUMB') {
		$GccPrefix='thumb-epoc-pe-';
		$PlatOpt{Entry}='--thumb-entry';
		$PlatOpt{Gcc}='-mthumb-interwork';
		$PlatOpt{Dlltool}=$ABIDlltool{THUMB};
#		$HelperLib='up_thumb.lib';
	}
	else {
		&main::FatalError("Platform module - ABI \"$ABI\" unrecognised");
	}
	$Dlltool=$ToolPrefix.'dlltool';
	$Archive=$ToolPrefix.'ar';
	$Link=$ToolPrefix.'ld';
	$Objcopy=$ToolPrefix.'objcopy';

	&Generic_Header(1,$Makecmd);	# define standard things using relative paths

#	GCC needs a fully-qualified path
	if ($Makecmd eq "nmake") {
		&main::Output(
			"\n",
			"PATH=",&main::Path_Drive,$EPOCPath,"gcc\\bin;\$(PATH)\n",
			"\n"
		);
	}
	else {
		&main::Output(
			"\n",
			"# must set both PATH and Path to make it work correctly\n",
			"Path:=",&main::Path_Drive,$EPOCPath,"gcc\\bin;\$(Path)\n",
			"PATH:=\$(Path)\n",
			"\n"
		);
	}

	&main::Output(
		"INCDIR  ="
	);
	foreach (@ChopRTWUserIncPaths) {
		&main::Output(
			" -I \"$_\""
		);
	}
	foreach (@ChopRTWSysIncPaths) {
		&main::Output(
			" -I \"$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"GCCFLAGS=$PlatOpt{Gcc} \\\n",
		"\t\t-pipe -c -nostdinc -Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas $WarningLevel\n",
		"\n"
	);

	&main::Output(
		"GCCDEFS ="
	);
	foreach(@MacroList) {
		&main::Output(
			" -D$_"
		);
	}
	&main::Output(
		" \$(USERDEFS)\n",
		"\n"
	);

	foreach (@BldList) {
		&main::Output(
			"GCC$_ = ${GccPrefix}gcc"
		);
		if (/REL$/o) {
			&main::Output(
				      ' -s -fomit-frame-pointer ',
				      $PlatOpt{Optimize}
			);
		}
		elsif (/DEB$/o) {
			&main::Output(
				' -g'
			);
			unless (&main::SrcDbg) {
			    &main::Output(
			    	' ', $PlatOpt{Optimize}
			    );
			}
		}
		&main::Output(
			' $(GCCFLAGS)'
		);
		foreach (&main::MacroList($_)) {
			&main::Output(
				" -D$_"
			);
		}
		&main::Output(
			" \$(GCCDEFS)\n"
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
			" \\\n\t",
			&Generic_Quote("\$(EPOCTRG$_)\\$Trg")
		);

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

	# Resource building is done entirely via cl_generic.pm
	
	foreach (@BldList) {
		&main::Output(
			"\n",
			"RESOURCE$_ : MAKEWORK$_"
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
	elsif ($DefFile) {
		unless (&main::ExportUnfrozen) {
			if (-e $DefFile) { # effectively "if project frozen ..."
				&main::Output(
					" ", &Generic_Quote("\$(EPOCLIB)\\UREL\\$BaseTrg.LIB")
				);
				foreach (@CompatibleABIs) {
					&main::Output(
						" ", &Generic_Quote("$ABILibPath{$_}UREL\\$BaseTrg.LIB")
					);
					&Generic_MakeWorkDir('MAKEWORKLIBRARY',"$ABILibPath{$_}UREL");
				}
				&main::Output(
					"\n"
				);
			}
			else {
				&main::Output(
					"\n",
					"\t\@echo WARNING: Not attempting to create any import libraries.\n",
					"\t\@echo When exports are frozen in \"$DefFile\", regenerate Makefile.\n"
				);
			}
		}
		else {
			&main::Output(
				"\n",
				"\t\@echo Not attempting to create \"\$(EPOCLIB)\\UREL\\$BaseTrg.LIB\"\n",
				"\t\@echo from frozen .DEF file, since EXPORTUNFROZEN specified.\n"
			);
		}
		&main::Output(
			"\n",
			"\n",
			"# REAL TARGET - LIBRARY\n",
			"\n",
			&Generic_Quote("\$(EPOCLIB)\\UREL\\$BaseTrg.LIB"), " : ",
			&Generic_Quote($DefFile), "\n",
			"\t$Dlltool $PlatOpt{Dlltool} --output-lib \"\$(EPOCLIB)\\UREL\\$BaseTrg.LIB\" \\\n",
			"\t\t--def \"",&main::Path_RltToWork($DefFile),"\" \\\n",
			"\t\t--dllname \"$LinkAs\" \n"
		);
		foreach (@CompatibleABIs) {
			&main::Output(
				"\n",
				&Generic_Quote("$ABILibPath{$_}UREL\\$BaseTrg.LIB"), " : ",
				&Generic_Quote($DefFile), "\n",
				"\t$Dlltool $ABIDlltool{$_} --output-lib \"$ABIRTWLibPath{$_}UREL\\$BaseTrg.LIB\" \\\n",
				"\t\t--def \"",&main::Path_RltToWork($DefFile),"\" \\\n",
				"\t\t--dllname \"$LinkAs\" \n"
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
			"\t-\$(ERASE) \"\$(EPOCLIB)\\UREL\\$BaseTrg.LIB\"\n"
		);
		foreach (@CompatibleABIs) {
			&main::Output(
				"\t-\$(ERASE) \"$ABILibPath{$_}UREL\\$BaseTrg.LIB\"\n"
			);
		}
	}
	&main::Output(
		"\n",
		"\n"
	);
	&Generic_MakeWorkDir('MAKEWORKLIBRARY',"${LibPath}UREL");

	&Generic_Releaseables;
}


sub PMBld {

	my @ASSPLibList=&main::ASSPLibList;
	my @BaseSrcList=&main::BaseSrcList;
	my $BaseTrg=&main::BaseTrg;
	my $Bld=&main::Bld;
	my $ChopBldPath=&main::Path_Chop(&main::BldPath);
	my @CompatibleABIs=&main::CompatibleABIs;
	my $DefFile=&main::DefFile;
	my $EPOCIncPath=&main::EPOCIncPath;
	my $FirstLib=&main::FirstLib;
	my $BasicTrgType=&main::BasicTrgType;
	my @LibList;
	my $LibPath=&main::LibPath;
	my $LinkAs=&main::LinkAs;
	my $ChopRelPath=&main::Path_Chop(&main::RelPath);
	my $RelPath=&main::RelPath;
	my @StatLibList=&main::StatLibList;
	my $StatLinkPath=&main::StatLinkPath;
	my $Trg=&main::Trg;
	my $TrgType=&main::TrgType;
	my @UidList=&main::UidList;

	if ($Bld =~ /DEB/) {
		@LibList = &main::DebugLibList;
	} else {
		@LibList = &main::LibList;
	}

#	set up $LinkAs
	$UidList[2]=~/^0x(.*)$/o;
	if ($1 ne '00000000') {	# have to make sure than series of noughts in brackets doesn't appear in name for null uids
		$LinkAs=join '', &main::Path_Split('Base',$LinkAs),"[$1]",&main::Path_Split('Ext',$LinkAs);
	}


	# REAL TARGETS
	#-------------
	&main::Output(
		"# REAL TARGET - BUILD VARIANT $Bld\n",
		"\n"
	);

#	releasables
	my @releaseables;
	
	push @releaseables, "$RelPath$Trg";
	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
		push @releaseables, "$RelPath$Trg.MAP";
	}
	if (-e $DefFile) { # effectively "if project frozen ..."
		push @releaseables, "$LibPath$BaseTrg.LIB";
		foreach (@CompatibleABIs) {
			push @releaseables, "$ABILibPath{$_}UREL\\$BaseTrg.LIB";
		}
	}

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

	&Generic_MakeWorkDir("MAKEWORK$Bld",$ChopBldPath);
	&Generic_MakeWorkDir("MAKEWORK$Bld",$ChopRelPath);

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
	if ($BasicTrgType=~/^DLL$/o) { # Add the DLL stub library
		&main::Output(
			" \\\n\t",
			&Generic_Quote("\$(EPOCSTATLINK$Bld)\\EDLLSTUB.LIB")
		);
	}
	if ($BasicTrgType=~/^(DLL|EXE)/o) { # Add the GCC helper fns
		&main::Output(
			" \\\n\t",
			&Generic_Quote("\$(EPOCSTATLINK$Bld)\\EGCC.LIB")
		);
	}
	if ($HelperLib) {
		&main::Output(
			" \\\n\t",
			&Generic_Quote("\$(EPOCSTATLINK$Bld)\\$HelperLib")
		);
	}
	foreach (@StatLibList) {
		&main::Output(
			" \\\n\t",
			&Generic_Quote("\$(EPOCSTATLINK$Bld)\\$_")
		);
	}
	foreach (@ASSPLibList) {
		&main::Output(
			" \\\n\t",
			&Generic_Quote("\$(EPOCASSPLINK$Bld)\\$_")
		);
	}
	foreach (@LibList) {
		&main::Output(
			" \\\n\t",
			&Generic_Quote("\$(EPOCLINK$Bld)\\$_")
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		&Generic_Quote("\$(EPOCTRG$Bld)\\$Trg"), " : ",
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseTrg.in")
	);
	if (-e $DefFile) { # effectively "if project frozen ..."
		&main::Output(
			" ", &Generic_Quote($DefFile)
		);
	}
	if ($BasicTrgType=~/^(EXE|DLL)$/o) {
		&main::Output(
			" ", &Generic_Quote("\$(EPOCSTATLINK$Bld)\\$FirstLib")
		);
	}
	&main::Output(
		" \$(LIBS$Bld)\n"
	);

	if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEDLL$/o) {

#		generate a .DEF file from the objects and static libraries
		&main::Output(
			"\t$Dlltool $PlatOpt{Dlltool} --output-def \"\$(EPOCBLD$Bld)\\$BaseTrg.inf\" \"\$(EPOCBLD$Bld)\\$BaseTrg.in\""
		);
		foreach (@StatLibList) {
			&main::Output(
				" \"\$(EPOCSTATLINK$Bld)\\$_\""
			);
		}
		&main::Output(
			"\n"
		);

#		reorder the .DEF file taking frozen exports into account if there are any
		&main::Output(
#			call perl on the script here so nmake will die if there are errors - this doesn't happen if calling perl in a batch file
			"\tperl -S makedef.pl -Deffile \"\$(EPOCBLD$Bld)\\$BaseTrg.inf\""
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
				&main::Output(
					" -$Num $Ordinal"
				);
				$Num++;
			}
		}
		&main::Output(
			" \"\$(EPOCBLD)\\$BaseTrg.def\"\n"
		);

#		delete the unordered definition file
		&main::Output(
			"\t-\$(ERASE) \"\$(EPOCBLD$Bld)\\$BaseTrg.inf\"\n"
		);

#		generate an export object from the ordered .DEF file
		&main::Output(
			"\t$Dlltool $PlatOpt{Dlltool} --def \"\$(EPOCBLD)\\$BaseTrg.def\" \\\n",
			"\t\t--output-exp \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\" \\\n",
			"\t\t--dllname \"$LinkAs\""
		);
		if (&main::ExportUnfrozen) {
			&main::Output(
				"\\\n",
				"\t\t--output-lib \"\$(EPOCLIB)\\UREL\\$BaseTrg.LIB\""
			);
		}
		&main::Output(
			"\n"
		);
	}

#	call ld to do base relocations (and dll exports)
	if ($BasicTrgType=~/^(DLL|EXE)/o) {
		&main::Output(
			"\t$Link $PlatOpt{Ld} -s"
			);	
		if ($BasicTrgType=~/^DLL$/o) {
			&main::Output(
				" $PlatOpt{Entry} _E32Dll -u _E32Dll \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\" --dll \\\n"
			);
		}
		elsif ($BasicTrgType=~/^EXE$/o) {
			&main::Output(
				" $PlatOpt{Entry} _E32Startup -u _E32Startup \\\n"
			);
		}
#		--whole-archive is required here apparently because of a bug in the gcc toolchain
#		the flag can probably be removed with a later version of gcc
		&main::Output(
			"\t\t--base-file \"\$(EPOCBLD$Bld)\\$BaseTrg.bas\" -o \"\$(EPOCBLD$Bld)\\$Trg\" \\\n",
			"\t\t\"\$(EPOCSTATLINK$Bld)\\$FirstLib\" --whole-archive \"\$(EPOCBLD$Bld)\\$BaseTrg.in\" \\\n",
			"\t\t--no-whole-archive"
		);
		&main::Output(
			" \$(LIBS$Bld) \$(USERLDFLAGS)\n"
		);

#		delete temporary files
		if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEDLL$/o) {
			&main::Output(
				"\t-\$(ERASE) \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\"\n"
			);
		}
		&main::Output(
			"\t-\$(ERASE) \"\$(EPOCBLD$Bld)\\$Trg\"\n"
		);

#		call dlltool to do base relocations (and dll exports)
		&main::Output(
			"\t$Dlltool $PlatOpt{Dlltool} \\\n"
		);
		if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEDLL$/o) {
			&main::Output(
				"\t\t--def \"\$(EPOCBLD)\\$BaseTrg.def\" \\\n",
				"\t\t--dllname \"$LinkAs\" \\\n"
			);
		}
		&main::Output(
			"\t\t--base-file \"\$(EPOCBLD$Bld)\\$BaseTrg.bas\" \\\n",
			"\t\t--output-exp \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\" \n"
		);

#		delete temporary files
		&main::Output(
			"\t-\$(ERASE) \"\$(EPOCBLD$Bld)\\$BaseTrg.bas\"\n"
		);

#		call ld to link the target
		&main::Output(
			"\t$Link $PlatOpt{Ld}"
		);
		if ($Bld=~/^U?REL$/o) {
			&main::Output(
				" -s"
			);
		}
		if ($BasicTrgType=~/^DLL$/o) {
			&main::Output(
				" $PlatOpt{Entry} _E32Dll -u _E32Dll --dll \\\n"
			);
		}
		elsif ($BasicTrgType=~/^EXE$/o) {
			&main::Output(
				" $PlatOpt{Entry} _E32Startup -u _E32Startup \\\n"
			);
		}
#		--whole-archive is required here apparently because of a bug in the gcc toolchain
#		the flag can probably be removed with a later version of gcc
		&main::Output(
			"\t\t\"\$(EPOCBLD$Bld)\\$BaseTrg.exp\" \\\n",
			"\t\t-Map \"\$(EPOCTRG$Bld)\\$Trg.map\" -o \"\$(EPOCBLD$Bld)\\$Trg\" \\\n",
			"\t\t\"\$(EPOCSTATLINK$Bld)\\$FirstLib\" --whole-archive \"\$(EPOCBLD$Bld)\\$BaseTrg.in\" \\\n",
			"\t\t--no-whole-archive"
		);
		&main::Output(
			" \$(LIBS$Bld) \$(USERLDFLAGS)\n"
		);

#		delete temporary files
		&main::Output(
			"\t-\$(ERASE) \"\$(EPOCBLD$Bld)\\$BaseTrg.exp\"\n"
		);

		if ($Bld=~/DEB$/o) {
			&main::Output(
				"\t$Objcopy -X \"\$(EPOCBLD$Bld)\\$Trg\" \"\$(EPOCTRG$Bld)\\$BaseTrg.sym\"\n"
			);
		}

		&main::Output(
			"\tpetran $PlatOpt{Petran} \"\$(EPOCBLD$Bld)\\$Trg\" \"\$\@\" \\\n",
			"\t\t"
		);
		if (&main::AllowDllData) {
			&main::Output(
				' -allow'
			);
		}
		if (not &main::CallDllEntryPoints) {
			&main::Output(
				' -nocall'
			);
		}
		if (&main::DataLinkAddress) {
			&main::Output(
				' -datalinkaddress ',&main::DataLinkAddress
			);
		}
		if (&main::FixedProcess) {
			&main::Output(
				' -fixed'
			);
		}
		if (&main::HeapSize) {
			my %HeapSize=&main::HeapSize;
			&main::Output(
				' -heap ',$HeapSize{Min},' ',$HeapSize{Max}
			);
		}
		if (&main::ProcessPriority) {
			&main::Output(
				' -priority ',&main::ProcessPriority
			);
		}
		if (&main::StackSize) {
			&main::Output(
				' -stack ',&main::StackSize
			);
		}
		my $i=1;
		foreach (@UidList) {
			&main::Output(
				" -uid$i $_"
			);
			$i++;
		}
		&main::Output(
			"\n"
		);
		&main::Output(
			"\t-\$(ERASE) \"\$(EPOCBLD$Bld)\\$Trg\"\n"
		);
	}
	elsif ($BasicTrgType=~/^LIB$/o) {
		&main::Output(
			"\tcopy \"\$(EPOCBLD$Bld)\\$BaseTrg.in\" \"\$(EPOCSTATLINK$Bld)\\$Trg\"\n"
		);
	}

	&main::Output(
		"\n"
	);


	# TARGET *.IN
	#------------
	if (scalar @BaseSrcList >150) {
		# deal with very long lists by splitting them into 150 file pieces, which allows
		# about 200 bytes per filename if the underlying max size is 32K
		#
		my $counter1=150;	# i.e. trigger new variable immediately
		my $counter2=0;
		my @objvarlist=();
		foreach (@BaseSrcList) {
			if ($counter1==150) {
				$counter1=0;
				$counter2++;
				my $objvar = "OBJECTS$Bld$counter2";
				push @objvarlist, " \$($objvar)";
				&main::Output(
					"\n",
					"$objvar="
				);
			}
			&main::Output(
				" \\\n\t", &Generic_Quote("\$(EPOCBLD$Bld)\\$_.o")
			);
			$counter1++;
		}
		&main::Output(
			"\n",
			"\n",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseTrg.in"), " : ", @objvarlist,"\n",
			"\tif exist \"\$\@\" del \"\$\@\"\n"
		);
		foreach (@objvarlist) {
			# Add the files to the list in groups
			&main::Output(
				"\t$Archive cr \$\@$_\n"
			);
		}
		&main::Output(
			"\n\n"
		);
	} else {
		# shorter lists remain unchanged
		#
		&main::Output(
			"OBJECTS$Bld="
		);
		foreach (@BaseSrcList) {
			&main::Output(
				" \\\n\t", &Generic_Quote("\$(EPOCBLD$Bld)\\$_.o")
			);
		}
		&main::Output(
			"\n",
			"\n"
		);
		&main::Output(
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseTrg.in"), " : \$(OBJECTS$Bld)\n",
			"\tif exist \"\$\@\" del \"\$\@\"\n",
			"\t$Archive cr \$\@ \$^\n",
			"\n\n"
		);
	}
}


sub PMStartSrcList {

	&main::Output(
		"# SOURCES\n",
		"\n"
	);
}

sub PMBitMapBld {

	&Generic_BitMapBld;
	
}

sub PMResrcBld {

	&Generic_ResrcBld;

}

sub PMAifBld {

	&Generic_AifBld;

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

	return if (@DepList == 0);

	foreach (@BldList) {
		&main::Output(
			&Generic_Quote("\$(EPOCBLD$_)\\$BaseSrc.lis"), " ",
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

	return if (@DepList == 0);

	&main::Output(
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.lis"), " ",
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
	my $ABI=&main::ABI;
	my $BaseSrc=&main::BaseSrc;
	my $Bld=&main::Bld;
	my $Src=ucfirst lc &main::Src;
	my $SrcPath=&main::SrcPath;

	my $RTWSrcPath=&main::Path_Chop(&main::Path_RltToWork($SrcPath));

	# Use GCC trick to get assembler source files preprocessed with CPP
	$Src =~ s/\.s$/.S/i;

	&main::Output(
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.o"), " : ",
		&Generic_Quote("$SrcPath$Src"), "\n",
		"\t\$(GCC$Bld) -I \"$RTWSrcPath\" \$(INCDIR) -o \$\@ \"$RTWSrcPath\\$Src\"\n",
		"\n",
#		generate an assembly listing target too
		"LISTING$Bld$BaseSrc : ", &Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.lis"), "\n",
		"\t", &Generic_CopyAction("$SrcPath$BaseSrc.lst.$ABI"),
		"\n",
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.lis"), " : ",
		&Generic_Quote("$SrcPath$Src"), "\n",
		"\t\$(GCC$Bld) -Wa,-adln -I \"$RTWSrcPath\" \$(INCDIR) -o nul: \"$RTWSrcPath\\$Src\" > \$\@\n",
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

	# Deal with accumulated MAKEDIRS etc.

	&Generic_End;
}

1;
