# CL_BPABI.PM
#
# Copyright (c) 1997-2005 Symbian Software Ltd.  All rights reserved.
#

# This package contains routines to handle Base Platform ABI (BPABI) Platforms.
package Cl_bpabi;

my $commonOptions;
my $thumbOptions;
my $armOptions;
my $kernelOptions; 
my $invariantOptions;
my $ArmIncDir;
my @ArmLibList;

my %configVariables;

# the following custom dlls are required to be built
my @CustomDlls=(
'dfprvct2_2.dll' ,
'dfprvct2_2_vfpv2.dll' ,
'dfpaeabi.dll' ,
'dfpaeabi_vfpv2.dll' ,
'drtaeabi.dll' ,
'drtrvct2_2.dll',
'drtrvct2_2_vfpv2.dll',
'scppnwdl.dll' 
);

# takes an 'expression'  to evaluate with $_ bound to each of the 
# remaining args
sub PrintList
{
    my $expr = shift @_;
    foreach (@_) {
	my $str = eval($expr);
	&main::Output($str);
    }
}

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
		PMStartSrc
		PMAifBld
		PMSrcDepend
			PMSrcBldDepend
			PMEndSrcBld
		PMEndSrc
	PMEndSrcList
	PMPrefixFile
);

use Cwd;

# Armutl package does various ancillary things for armedg modules
use Armutl;
use BPABIutl;

# This is the RVCT Version information required by Armutl package
my $RVCTMajorVersion;
my $RVCTMinorVersion;
my $RVCTVersion;

# cl_generic package contains generic routines to handle bits of makefiles which are
# common to all of the platforms. Currently it deals with AIF, MBM amd RSC files.
use cl_generic;

# E32env package contains information for makmake and associated e32tools perl programs
# within the Epoc32 Environment
use E32env;

# Genutl package contains utility subroutines for MAKMAKE and associated scripts
use Genutl;

# Modload package is the runtime module-loading routine for loading e32tools modules into
# 'main' module
use Modload;

sub PMHelp_Mmp {
	my $Plat=&main::Plat;

# Help Text for ARM Platform, lists out the MMP keywords used incase of ARM Compiler
	if($Plat eq "ARMV5_ABIV2")
	{
		return &Armutl_Help_Mmp;
	}
	else
	{
		return "";
	}
}

my $ToolChainIncDir;
my @ToolChainLibList;
my $ArmRT = 0;
my %AsmFiles = ();
my %AsmDirs = ();


sub PMPlatProcessMmp (@) {
	&InitToolChain(@_);    
	$ToolChainIncDir = &GetToolChainIncDir;
	&main::SetStdIncPaths($ToolChainIncDir);
	@ToolChainLibList = &GetLibList;
	$TargetRT = &IsTargetRT;
	my @AsmFileList = &GetToolChainAsmFileList;
	foreach (@AsmFileList) { $AsmFiles{ucfirst lc $_} = 1; }
}

my $preinclude;

my $Makecmd;

sub PMStartBldList($) {
	($Makecmd) = @_;
	my $ABI=&main::ABI;
	my $BaseTrg=&main::BaseTrg;
	my $BasicTrgType=&main::BasicTrgType;
	my @BldList=&main::BldList;
	my @ChopRTWSysIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::SysIncPaths));
	my @ChopRTWUserIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::UserIncPaths));
	my $DefFile=&main::DefFile;
	my $EPOCPath=&main::EPOCPath;
	my $LinkAs=&main::LinkAs;
	my $LibPath=&main::LibPath.'LIB\\';
	my @MacroList=&main::MacroList();
	push @MacroList, "__SUPPORT_CPP_EXCEPTIONS__";
	
	my $myStatLinkPath;
	$myStatLinkPath = "$E32env::Data{LinkPath}";
	$myStatLinkPath .= "ARMV5";
	&main::SetStatLinkPath($myStatLinkPath);

	my $VariantFile=&ChangeSlash(&main::VariantFile);

	my $Plat=&main::Plat;
	my $Trg=&main::Trg;
	my $TrgType=&main::TrgType;
	my @UidList=&main::UidList;	
    my $SystemTrg = &main::SystemTrg;
    my $ExportLibrary=&main::ExportLibrary;
    my $NoExportLibrary=&main::NoExportLibrary;
    # N.B. should get better way to detect kernel probably!!
    $SystemTrg = 1 if ($ExportLibrary =~ /EKERN/i);
	
    # N.B. should get better way to detect this
    $SystemTrg = 1 if ($Trg =~ /KSRT/i);

	my %Version = &main::Version();
	my $ExtraExportLibrary;
	my $PrimaryExportLibrary = $ExportLibrary;
	unless ($Version{explicit}) {
		$ExtraExportLibrary = $ExportLibrary;
		$ExtraExportLibrary =~ s/\{(\d|a|b|c|d|e|f){8}\}//i;
		$PrimaryExportLibrary = $ExtraExportLibrary;
	}

#	set up LinkAs
	$UidList[2]=~/^0x(.*)$/o;
	if ($1 ne '00000000') { # have to make sure than series of noughts in brackets doesn't appear in name for null uids
		$LinkAs=join '', &main::Path_Split('Base',$LinkAs),"[$1]",&main::Path_Split('Ext',$LinkAs);
	}

#	work out the flags for various platforms
#	unless ($ABI eq 'BPABI' ) {
#		&main::FatalError("Platform module - ABI \"$ABI\" unrecognised");
#	}


	# need to add config file for makmake invocation
	my $config_file = BPABIutl_Config_Path(&main::Plat);
	
	&main::Output("\n", "include $config_file\n", "\n");
	&Generic_Header(1,$Makecmd);	# define standard things using relative paths
		 
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

	if ($BasicTrgType=~/^(DLL|EXE)/o) 
	{

		# In case of GCCE releases, '--map' option was supported only from build 3.4.3 Q1C release
		# Hence this is a special case, where GCCE platform is checked to ensure that the --map option
		# is accepted in the correct relase. Even if the option is provided in the config file, it will be
		# ignored for versions before 3.4.3 Q1C 2005 release.
		if($Plat eq "GCCE")
		{
			if(IsMapOptAvail() eq 0)
			{
				&main::Output(
					"LINKER_SYMBOLS_MAP_OPTION=",
					"\n"
				);
			}
		# Incase of GCCE, the following paths should be provided to the linker

		my $gccinstallpath = &GCCInstallPath;
		$gccinstallpath .= "\\\.\.";
			&main::Output(
				"ifndef CC_INSTALL_PATH\n",
 				"\tCC_INSTALL_PATH=",$gccinstallpath,"\n",
				"\tSTATIC_LIBS = \$(STATIC_LIBS_PATH)\"\$(CC_INSTALL_PATH)\\arm-none-symbianelf\\lib\" \$(STATIC_LIBS_PATH)\"\$(CC_INSTALL_PATH)\\lib\\gcc\\arm-none-symbianelf\\3.4.3\"",
				"\nendif\n"
			);

		}

		# Check to be included in the Makefile, so that the map filename is provided as input only
		# when the MAP option is supplied
		&main::Output(
			"ifdef LINKER_SYMBOLS_MAP_OPTION\n",
			"\tUREL_MAP_FILE=\"\$(EPOCTRGUREL)\\$Trg.map\"\n",
			"\tUDEB_MAP_FILE=\"\$(EPOCTRGUDEB)\\$Trg.map\"\n",
			"else\n",
			"\tUREL_MAP_FILE=\n",
			"\tUDEB_MAP_FILE=\n",
			"endif\n\n"
		);

		#	In some compiler toolchains, the start address may be required to be provided using the appropriate option.
		# 	Incase if the option is provided by the toolchain, then pass we need to pass in the start address.
		&main::Output(
			"\nifdef CODE_SEGMENT_START\n",
			"\tCODE_SEGMENT_START += 0x8000 \n",
			"endif\n",
		);


		# In some compiler toolchain, the symboled archives may have to be listed
		&main::Output(
			"ifdef START_GROUP_SYMBOL\n",
			"\tEEXE_OBJECT=\$(START_GROUP_SYMBOL)UC_EXE_.o\$(END_GROUP_SYMBOL)\n",
			"\tEDLL_OBJECT=\$(START_GROUP_SYMBOL)UC_DLL_.o\$(END_GROUP_SYMBOL)\n",
			"\tDENTRY_OBJECT=\$(START_GROUP_SYMBOL)D_ENTRY_.o\$(END_GROUP_SYMBOL)\n",
			"\tLENTRY_OBJECT=\$(START_GROUP_SYMBOL)L_ENTRY_.o\$(END_GROUP_SYMBOL)\n",
			"\tXENTRY_OBJECT=\$(START_GROUP_SYMBOL)X_ENTRY_.o\$(END_GROUP_SYMBOL)\n",
			"\tVENTRY_OBJECT=\$(START_GROUP_SYMBOL)V_ENTRY_.o\$(END_GROUP_SYMBOL)\n",
			"\tKENTRY_OBJECT=\$(START_GROUP_SYMBOL)K_ENTRY_.o\$(END_GROUP_SYMBOL)\n",
			"endif\n\n"
		);
	}

	&main::Output(
		"INCDIR ="
	);

	PrintList("\"  \\\$(INCLUDE_OPTION) \$_\"", @ChopRTWUserIncPaths);
	PrintList("\" \\\$(INCLUDE_OPTION) \$_\"", @ChopRTWSysIncPaths);
	
	$ToolchainIncDir = &GetToolChainIncDir;

	if($ToolchainIncDir ne '')
	{
		&main::Output(
			" \$(INCLUDE_OPTION) ","\"$ToolchainIncDir\"");
	}

	&main::Output(
		"\n",
		"\n"
	);

	my %plat = &main::PlatRec();
	Set_Compiler_Options() if ($plat{'CUSTOMIZES'});

	my $kernelOption=0;
	my $buildAsArmOption=0;
	my $thumbOption=0;

	if (SysTrg())
	{
		$kernelOption=1;
	}
	elsif (main::BuildAsARM() or ($ABI eq 'ARMV4'))
	{
		$buildAsArmOption=1;
	}
	else
	{
		$thumbOption=1;
	}

	my $OtherOptionFlag=0;
	my $OtherOpts;
	my $mmpReplaceOptions;

	if($Plat eq "ARMV5_ABIV2")
	{
		$OtherOpts=&main::CompilerOption("ARMCC");
	}
	else
	{
		$OtherOpts=&main::CompilerOption($Plat);
	}

	if($OtherOpts)
	{
		$OtherOptionFlag=1;
	}

	if($kernelOption==1 || $buildAsArmOption==1)
	{
		$OtherOptionFlag=1;
		$OtherOpts .= " \$(ARM_INSTRUCTION_SET) ";
	}
	elsif($thumbOption==1)
	{
		$OtherOptionFlag=1;
		$OtherOpts .= " \$(THUMB_INSTRUCTION_SET) ";
	}

	if($thumbOption==1 || $buildAsArmOption==1)
	{
		$OtherOptionFlag=1;
		if (&main::ARMFPU && (&main::ARMFPU =~ /^VFPV2$/i)) 
		{
			$OtherOpts .=	" \$(VFP2MODE_OPTION) ";
		}
		else
		{
			$OtherOpts .=	" \$(SOFTVFPMODE_OPTION) ";
		}
	}

	if ($thumbOption==1)
	{
		$OtherOpts .= " \$(COMPILER_THUMB_DEFINES) ";
	}

	$OtherOpts .= " \$(COMPILER_INTERWORK_DEFINES) ";

	if($OtherOptionFlag eq 1)
	{
		&main::Output(
			"OTHEROPTIONS=$OtherOpts",
			"\n",
			"CCFLAGS += \$(OTHEROPTIONS)",
			"\n"
		);
	}

	&main::Output(
		"CCDEFS = \$(COMPILER_DEFINES) "
	);
	
	PrintList("\" -D\$_\"", @MacroList);

	&main::Output(
		" \$(PLATFORM_DEFINES) "
	);

	&main::Output(
		
	);

	if($kernelOption==1)
	{
		&main::Output(
			"-D__KERNEL_MODE__ "
		);
	}
	
	if($VariantFile){
	    &main::Output(" -D__PRODUCT_INCLUDE__=\\\"${VariantFile}\\\"");
	}

	&main::Output(
		" \$(USERDEFS)\n",
		"\n"
	);

	foreach (@BldList) {
		&main::Output(
			"CC$_ = ","\$(CC) "
		);
		if (/DEB$/o) {
			&main::Output(
				" \$(SYMBIAN_UDEB_CCFLAGS) "
			);
		}
		else {
			&main::Output(
				" \$(SYMBIAN_UREL_CCFLAGS) "
			);

		}

		&main::Output(
			"\$(RUNTIME_SYMBOL_VISIBILITY_OPTION) "
		);
		
		&main::Output(
			'$(CCFLAGS) '
		);

		my @ml = &main::MacroList($_);
		PrintList("\" -D\$_\"", @ml);

		&main::Output(
			" \$(CCDEFS)\n"
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

		if ($BasicTrgType !~ /IMPLIB/io) {
			&main::Output (
				" \\\n\t",
				&Generic_Quote("\$(EPOCTRG$_)\\$Trg")
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

	# Resource building is done entirely via cl_generic.pm
	PrintList("\"\nRESOURCE\$_ : MAKEWORK\$_\"", @BldList);
	&main::Output(
		"\n",
		"\n",
	);

	&main::Output(
		"LIBRARY : MAKEWORKLIBRARY"
	);
	if ($BasicTrgType=~/^LIB$/o) {
#		code to ensure that the static libraries for all builds are built at the library stage
	        PrintList("\" \$_\"", @BldList);
	}
	elsif ($DefFile and !$NoExportLibrary) {
		unless (&main::ExportUnfrozen) {
			if (-e $DefFile) { # effectively "if project frozen ..."
				&main::Output(
					" ", &Generic_Quote("\$(EPOCLIB)\\LIB\\$PrimaryExportLibrary.dso"), "\n"
				);
			}
			else {
				&main::Output(
					"\n",
					"\t\@echo WARNING: Not attempting to create any import libraries.\n",
					"\t\@echo When exports are frozen in \"$DefFile\", regenerate Makefile.\n"
				);
			}
		} else {
			&main::Output(
				"\n",
				"\t\@echo Not attempting to create \"\$(EPOCLIB)\\LIB\\$PrimaryExportLibrary.dso\"\n",
				"\t\@echo from frozen .DEF file, since EXPORTUNFROZEN specified.\n"
			);
		}

		my $theDefFile = $DefFile;
		$theDefFile = "\$(EPOCBLD)\\$BaseTrg.def" unless (-e $DefFile);
		&main::Output(
			"\n",
			"\n",
			"# REAL TARGET - LIBRARY\n",
			"\n",
			&Generic_Quote("\$(EPOCLIB)\\LIB\\$ExportLibrary.dso"), " : ",
			&Generic_Quote($DefFile), "\n",
				"\tcopy ", &Generic_Quote($DefFile), " \"\$(EPOCBLD)\\$ExportLibrary.prep.def\"\n",
				"\telf2e32 --definput=\"\$(EPOCBLD)\\$ExportLibrary.prep.def\" --dso=",
				&Generic_Quote("\$(EPOCLIB)\\LIB\\$ExportLibrary.dso"),
				" --linkas=$LinkAs\n",
			"\n"
		 );
		if ($ExtraExportLibrary) {
			&main::Output(
				"\n",
				&Generic_Quote("\$(EPOCLIB)\\LIB\\$ExtraExportLibrary.dso"), " : ",
				&Generic_Quote("\$(EPOCLIB)\\LIB\\$ExportLibrary.dso"), "\n",
				"\tcopy \$< \$@\n"
			);
		}
	}

	my $freezeDir = &main::Path_Split('Path', $DefFile);
	chop($freezeDir);

	# dummy rule for def files to cope with filename case differences
	unless (&main::ExportUnfrozen) {
		if (-e $DefFile) { # effectively "if project frozen ..."
			&main::Output(
				"\n",
				"\n",
				&Generic_Quote($DefFile), " : ", "\n",
				"\t\@rem Do nothing\n",
			);
		}
	}

	&main::Output(
		"\n",
		"\n",
		&Generic_Quote($freezeDir), " : ", "\n",
		"\tperl -S emkdir.pl \$\@\n",
	);

	&main::Output(
		"\n",
		"\n",
		"FREEZE : ",
		&Generic_Quote($freezeDir), "\n",
	);
	if ($DefFile and $BasicTrgType!~/^IMPLIB$/io) {
# 	    call perl on the script here so make will die if there are errors 
#           - this doesn't happen if calling perl in a batch file
	    &main::Output( "\tperl -S efreeze.pl \$(EFREEZE_ALLOW_REMOVE) \"$DefFile\" \"\$(EPOCBLD)\\$ExportLibrary.def\" \n" );
	}
	&main::Output(
		"\n",
		"CLEANLIBRARY :\n"
	);
	if ($DefFile and !$NoExportLibrary) {
		&main::Output(
			"\t-\$(ERASE) \"\$(EPOCLIB)\\LIB\\$ExportLibrary.dso\"\n"
		);
		if ($ExtraExportLibrary) {
			&main::Output(
				"\t-\$(ERASE) \"\$(EPOCLIB)\\LIB\\$ExtraExportLibrary.dso\"\n"
			);
		}
	}
	&main::Output(
		"\n",
		"\n"
	);
	&Generic_MakeWorkDir('MAKEWORKLIBRARY',"${LibPath}");

	&Generic_Releaseables;
}


sub PMBld {

    my $ABI=&main::ABI;
    my @ASSPLibList=&main::ASSPLibList;
    my @SrcList=&main::SrcList;
    my $BaseTrg=&main::BaseTrg;
    my $Bld=&main::Bld;
    my $ChopBldPath=&main::Path_Chop(&main::BldPath);
    my $DefFile=&main::DefFile;
    my $EPOCIncPath=&main::EPOCIncPath;
    my $FirstLib=&main::FirstLib;
    my $BasicTrgType=&main::BasicTrgType;
    my @LibList;
    my @RTLibList = &GetRTLibList();
    my $SystemTrg = &main::SystemTrg;
    my $LibPath= &main::LibPath;
    my $LinkAs=&main::LinkAs;
    my $ExportLibrary=&main::ExportLibrary;
    my $NoExportLibrary=&main::NoExportLibrary;
    # N.B. should get better way to detect kernel probably!!
    $SystemTrg = 1 if ($ExportLibrary =~ /EKERN/i);
    my $ChopRelPath=&main::Path_Chop(&main::RelPath);
    my $RelPath=&main::RelPath;
    my @StatLibList=&main::StatLibList;
    my $StatLinkPath=&main::StatLinkPath;
    my $Trg=&main::Trg;
    my $TrgType=&main::TrgType;
    my @UidList=&main::UidList;
	my %Version = &main::Version();
	my $ExtraExportLibrary;
	unless ($Version{explicit}) {
		$ExtraExportLibrary = $ExportLibrary;
		$ExtraExportLibrary =~ s/\{(\d|a|b|c|d|e|f){8}\}//i;
	}	
	my $objectFiles;

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
	
	push @releaseables, "$RelPath$Trg" if ($BasicTrgType!~/^IMPLIB$/io);
	if ($BasicTrgType=~/^(DLL|EXE)$/o) {
		push @releaseables, "$RelPath$Trg.map";
	}
	if (-e $DefFile and !$NoExportLibrary) { # effectively "if project frozen ..."
		push @releaseables, "$LibPath$ExportLibrary.dso";
		push @releaseables, "$LibPath$ExtraExportLibrary.dso" if ($ExtraExportLibrary);
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

	return if ($BasicTrgType=~/^IMPLIB$/io);

	&main::Output(
		"LISTING$Bld : MAKEWORK$Bld"
	);
	foreach (@SrcList) {
	    	my $BaseSrc = &main::Path_Split('Base', $_);
	    	my $Ext = &main::Path_Split('Ext', $_);
		if ($Ext =~ /cia/i) {
		    $BaseSrc = "$BaseSrc\_";
		}
		&main::Output(
			" \\\n\tLISTING$Bld$BaseSrc"
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
			&Generic_Quote("\$(EPOCSTATLINK$Bld)\\EDLLSTUB.lib")
		);
	}
        PrintList("\' \\\n\t\'\.\&Generic_Quote\(\"\\\$\(EPOCSTATLINK$Bld\)\\\\\$_\"\)", @StatLibList);
        my @ImportLibList = ImportLibraryList(@LibList);
		PrintList("\' \\\n\t\'\.\&Generic_Quote\(\"\\\$\(EPOCLIB\)\\\\LIB\\\\\$_\"\)", @ImportLibList);
        
        my $StaticRTLib = "usrt2_2" ;
        # use ksrt for system code and for user ARM code
        $StaticRTLib = "ksrt2_2" if ($SystemTrg);
        &main::Output(
	        " \\\n\t",
		&Generic_Quote("\$(EPOCSTATLINK$Bld)\\$StaticRTLib\.lib")
	) unless ($Trg =~ /(U|K)SRT/i || ($BasicTrgType=~/^LIB$/o));

	unless ($ArmRT || ($BasicTrgType=~/^LIB$/o)) {
	    my $TargLib = "$ExportLibrary.dso";
		$TargLib =~ s/\{(\d|a|b|c|d|e|f){8}\}//i;
	    unless ($SystemTrg) {
			foreach (@RTLibList) {
				&main::Output(
					" \\\n\t",
					&Generic_Quote("\$(EPOCLIB)\\LIB\\$_")
				) unless ($_ =~ /$TargLib/i);
			}
	    }
	}
        PrintList("\' \\\n\t\'\.\&Generic_Quote\(\"\$_\"\)", @ToolChainLibList);
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"VTBLEXPORTS$Bld="
	);
        my $vtobj = quotemeta("(VtblExports.o)");
#        PrintList("\' \\\n\t\'\.\&Generic_Quote\(\"\\\$\(EPOCLIB\)\\\\LIB\\\\\$_$vtobj\"\)", @LibList);
	&main::Output(
		"\n",
		"\n"
	);

        &main::Output(
	        "OBJECTS$Bld="
		);
        foreach (@SrcList) {
	    	my $BaseSrc = &main::Path_Split('Base', $_);
	    	my $Ext = &main::Path_Split('Ext', $_);
		if ($Ext =~ /cia/i) {
		    $BaseSrc = "$BaseSrc\_";
		}

	        &main::Output(
		        " \\\n\t",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.o")
		      );

		    $objectFiles .= &main::BldPath.$BaseSrc.".o\n";
	}
        &main::Output(
	        "\n",
		"\n"
	);

           &main::Output(
		     &Generic_Quote("\$(EPOCTRG$Bld)\\$Trg"),
		     " : \$(OBJECTS$Bld)"
		);

	if (-e $DefFile) { # effectively "if project frozen ..."
		&main::Output(
			" ", &Generic_Quote($DefFile)
		);
	}
#	if ($BasicTrgType=~/^(EXE|DLL)$/o) {
#		&main::Output(
#			" ", &Generic_Quote("\$(EPOCSTATLINK$Bld)\\$FirstLib")
#		);
#	}
#	&main::Output(
#		" \$(LIBS$Bld)"
#	);

	my $IsCustomDll = IsCustomDllUseCase($Trg);
	if($BasicTrgType=~/^DLL$/o && $IsCustomDll eq 1)
	{
		&main::Output( "\t\$(EPOCBLD$Bld)\\$ExportLibrary.exp " );
	}

    &main::Output("\n");
	

#       get rid of any -symbols produced .map file
        if ($BasicTrgType=~/^(DLL|EXE)/o) {
	        &main::Output(
			"\t-\$(ERASE) \"\$(EPOCTRG$Bld)\\$Trg.map\" \n"
		);	
		}

		my $AbsentSubst = '';
        if ($BasicTrgType=~/^(DLL|EXE)/o) {

			if ($Bld =~ /DEB/)
			{
				&main::Output(
					"\t\$(LD) ","\$(STATIC_LIBS) ","\$(SYMBIAN_UDEB_LINK_FLAGS) ", "\$(SHARED_OBJECT_OPTION) ",
					"\$(CODE_SEGMENT_START) ", "\$(DATA_SEGMENT_START) 0x400000 ", "\$(SYMVER_OPTION) ","\$(SO_NAME_OPTION) ","$LinkAs"
				);
			}
			else
			{
				&main::Output(
					"\t\$(LD) ","\$(STATIC_LIBS) ","\$(SYMBIAN_UREL_LINK_FLAGS) ","\$(SHARED_OBJECT_OPTION) ",
					"\$(CODE_SEGMENT_START) ", "\$(DATA_SEGMENT_START) 0x400000 ", "\$(SYMVER_OPTION) ","\$(SO_NAME_OPTION) ","$LinkAs"
				);
			}

			my $EntrySymbol;
			if ($BasicTrgType=~/^DLL$/o) {
				$EntrySymbol = '_E32Dll';
			}
			elsif ($BasicTrgType=~/^EXE$/o) {
				$EntrySymbol = '_E32Startup';
			}
			if ($EntrySymbol) {
				$AbsentSubst = " --absent $EntrySymbol";
			}

			if (($BasicTrgType=~/^DLL$/o) || ($BasicTrgType=~/^EXE$/o)) {
				&main::Output(
					" \$(LINKER_ENTRY_OPTION)",
					" $EntrySymbol "
					);
				my $undefined_option = getConfigVariable('UNDEFINED_SYMBOL_REF_OPTION');
				if ($undefined_option)
				{
					&main::Output(
						" \$(UNDEFINED_SYMBOL_REF_OPTION)",
						" $EntrySymbol "
					);
				}
			}

	        if ($BasicTrgType=~/^DLL$/o) {
	            # get the right object file for the entry point
	            my $ObjFile="\$(EDLL_OBJECT)";
	            if ($FirstLib =~ /EDEV/i) {
		            $ObjFile="\$(DENTRY_OBJECT)";
	            }
	            if ($FirstLib =~ /EKLL/i) {
		            $ObjFile="\$(LENTRY_OBJECT)";
	            }
	            if ($FirstLib =~ /EEXT/i) {
		            $ObjFile="\$(XENTRY_OBJECT)";
	            }
	            if ($FirstLib =~ /EVAR/i) {
		            $ObjFile="\$(VENTRY_OBJECT)";
	            }

	            &main::Output(
					" \$(EPOCSTATLINK$Bld)\\$FirstLib",
					"$ObjFile",
					" \\\n"
				);
	        } elsif ($BasicTrgType=~/^EXE$/o || $TrgType=~/^EXEXP$/o) {
			    # get the right object file for the entry point
				my $ObjFile="\$(EEXE_OBJECT)";
			    if ($FirstLib =~ /KC_EXE/i) {
					$ObjFile="\$(KENTRY_OBJECT)";
			    }
				
			    &main::Output(
				" \$(EPOCSTATLINK$Bld)\\$FirstLib",
				"$ObjFile",
				" \\\n"	
					);
			}

	        &main::Output(
		        "\t\t\$(OUTPUT_OPTION) \"\$(EPOCBLD$Bld)\\$Trg\" \\\n",
#				"\t\t\$(OBJECTS$Bld) \\\n"
			);
		
		&main::Output(
			"\t\t\$(LINKER_SYMBOLS_MAP_OPTION) ",
			"\$(","$Bld","_MAP_FILE) \\\n"
		);

	        &main::Output(
				"\t\t\$(OBJECTS$Bld) \\\n"
			);

			if($BasicTrgType=~/^DLL$/o && $IsCustomDll eq 1)
			{
				&main::Output( "\t\t\$(EPOCBLD$Bld)\\$ExportLibrary.exp \\\n" );
			}

	        &main::Output(
		        "\t\t\$(LIBS$Bld) \\\n",
				"\t\t\$(VTBLEXPORTS$Bld) \$(USERLDFLAGS) \n"
			);

	        if ($Bld=~/^U?DEB$/o) {
	               &main::Output(
			       "\tcopy \"\$(EPOCBLD$Bld)\\$Trg\" \"\$(EPOCTRG$Bld)\\$BaseTrg.sym\"\n"
		       );
	        }
		if (-e $DefFile) {
			&main::Output(
				"\tcopy ", &Generic_Quote($DefFile), " \"\$(EPOCBLD)\\$ExportLibrary.prep.def\"\n",
			);
		}
				
		&main::Output(
			"\telf2e32 --sid=", &main::SecureId(), " "
		);
		# hack - exexps are allowed data, but they look like dlls to elftran....
		if (&main::AllowDllData || $TrgType=~/^EXEXP$/o || $TrgType=~/^EXEDLL$/o) {
			&main::Output(
#				' --allow'
				' --dlldata'
			);
		}
#		if (not &main::CallDllEntryPoints ) {
#			&main::Output(
#				' --nocall'
#			);
#		}
		if (&main::DataLinkAddress) {
			&main::Output(
				' --datalinkaddress=',&main::DataLinkAddress
			);
		}
		if (&main::FixedProcess) {
			&main::Output(
				' --fixedaddress'
			);
		}
		if (&main::HeapSize) {
			my %HeapSize=&main::HeapSize;
			&main::Output(
				' --heap=',$HeapSize{Min},',',$HeapSize{Max}
			);
		}
		if (&main::ProcessPriority) {
			&main::Output(
				' --priority=',&main::ProcessPriority
			);
		}
		if (&main::StackSize) {
			&main::Output(
				' --stack=',&main::StackSize
			);
		}
		&main::Output(
			"\\\n\t\t"
		);

		my $i=1;
		foreach (@UidList) {
			&main::Output(
				" --uid$i=$_"
			);
			$i++;
		}
		if(&main::VendorId) {
			&main::Output(
				' --vid=',&main::VendorId
			);
		}
		&main::Output(
			"\\\n\t\t"
		);
		
		&main::Output(
			' --capability=',&main::Capability
		);

		my $vfpv2_support = getConfigVariable('VFP2MODE_OPTION');
		if ($vfpv2_support && &main::ARMFPU && (&main::ARMFPU =~ /^VFPV2$/i))
		{
			&main::Output(
				' --fpu=vfpv2'
			);
		}
		else
		{
			&main::Output(
				' --fpu=softvfp'
			);
		}

	if(($BasicTrgType=~/^DLL/ && $TrgType!~/^DLL/ ) || $TrgType=~/^EXEXP/){
 			&main::Output(
 				' --targettype=',$TrgType
 				);
 		}
 		else{
 			&main::Output(
 				' --targettype=',$BasicTrgType
 				);
 		}

#		&main::Output(
#			' --targettype=',$BasicTrgType
#			);
		&main::Output(
			' --output=',"\"\$\@\""
			);
		if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEXP$/o || $TrgType=~/^EXEDLL$/o) {
			if (-e $DefFile) {
				&main::Output(
					' --definput=',"\"\$(EPOCBLD)\\$ExportLibrary.prep.def\""
					);
			}
			&main::Output(
				' --dso=',
				&Generic_Quote("\$(EPOCBLD$Bld)\\$ExportLibrary.dso")
				);
			&main::Output(
				' --defoutput=',
				&Generic_Quote("\$(EPOCBLD$Bld)\\$ExportLibrary.def")
				);
				if(&main::ExportUnfrozen) {
					&main::Output( ' --unfrozen ');
				}
			}
		#the input elf file - as the last arg
		&main::Output(
			" --elfinput=","\"\$(EPOCBLD$Bld)\\$Trg\"",
			" --linkas=$LinkAs"
			);

		&main::Output(
#		" --uncompressed",
 		" --libpath=", "\"\$(EPOCLIB)\\LIB\""
 		);

		if($BasicTrgType=~/^DLL/ && $TrgType!~/^DLL/){
			my $Export;
			my $Ordinal=1;
			foreach $Export (&main::Exports) {
				if($Ordinal == 1) {
				&main::Output(" --sysdef=");
				}
				&main::Output(
					"$Export,$Ordinal; "
				);
				$Ordinal++;
			}
 		}
 
 		&main::Output(
 			"\n"
 		);
		
		}
         elsif ($BasicTrgType=~/^LIB$/o) {
	        &main::Output(
			"\t\$(ARCHIVER) ",
				" \$(ARCHIVER_CREATE_OPTION) ",
				" \$(EPOCSTATLINK$Bld)\\$Trg \$(OBJECTS$Bld)\n"
			);
         }

         &main::Output(
		 "\n"
	 );

	if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEXP$/o || $TrgType=~/^EXEDLL$/o) {
		&main::Output(
			"\tcopy ", " \"\$(EPOCBLD$Bld)\\$ExportLibrary.def\"", " \"\$(EPOCBLD)\\$ExportLibrary.def\"\n"
			);
	}

	if($BasicTrgType=~/^DLL$/o && $IsCustomDll eq 1)
	{
		&main::Output(
			&Generic_Quote("\$(EPOCBLD$Bld)\\$ExportLibrary.exp"), ": $DefFile\n");

	    my $theDefFile = "\$(EPOCBLD)\\$ExportLibrary.def";
	    $theDefFile = $DefFile if (-e $DefFile && !&main::ExportUnfrozen);
	    my $theAssembler = " \$(ASM) ";
	    &main::Output(
		"\telf2e32  \\\n\t\t--definput=$theDefFile \\\n\t\t--dump=a \\\n\t\t--output=\$(EPOCBLD)\\$ExportLibrary.s \n",
		"\t$theAssembler \\\n\t\t \$(OUTPUT_OPTION) \$(EPOCBLD$Bld)\\$ExportLibrary.exp  \$(EPOCBLD)\\$ExportLibrary.s\n\n"	    
	    );
		&main::Output(
			"\t-\$(ERASE) \"\$(EPOCBLD)\\$ExportLibrary.s\"\n\n"
		);
	}

    &main::Output( "\n" );
}

# Set to 1 if multifile compilation wanted
my $domultifile = 0;

sub DoMultiFile () {
        return $ENV{RVCTMultiFile} if (defined $ENV{RVCTMultiFile});
	return $domultifile;
}

my %CompilationGroups = ();

sub InitMultiFileCompilation() {
#	Do preparatory work for multifile compilation
	my $SourceStructRef=&main::SourceStructRef;

#	We sort the source files by path and extension. These form natural groups to compile together.
	my %PathToSourceMap = ();
	foreach my $SourceRef (@$SourceStructRef) {
		my $SrcFile = $$SourceRef{CurFile};
		my $Ext = &main::Path_Split('Ext', $SrcFile);
	        push @{$PathToSourceMap{$$SourceRef{SrcPath}}{$Ext}}, $SrcFile;
	}

#	Now we split each group into sets of 10. 
	foreach my $SrcPath (keys %PathToSourceMap) {
		foreach my $Ext (keys %{$PathToSourceMap{$SrcPath}}) {
			my @FileList;
			my @ObjectList;
			my @SourceList;
			my $NumToGo = 10;
			foreach my $File (@{$PathToSourceMap{$SrcPath}{$Ext}}) {
				my $base = &main::Path_Split('Base', $File);
				my $cia = ($Ext =~ /cia/i);
				$base .= "_" if $cia;
				push @FileList, $File;
				push @ObjectList, "$base.o";
#				this gives us our source files xxx				
				push @SourceList, $cia ? "$base.cpp" : "$SrcPath$base$Ext";
				$NumToGo--;
				unless ($NumToGo) {
#				       Use the last file as the key. This means e.g that all the dependency
#				       info will have been generated for the earlier files in the list
				       push @{$CompilationGroups{$FileList[$#FileList]}{Sources}}, @SourceList;
       				       push @{$CompilationGroups{$FileList[$#FileList]}{Objects}}, @ObjectList;
				       $NumToGo = 10;
				       undef @FileList;
				       undef @ObjectList;
				       undef @SourceList;
				}
			}
			push @{$CompilationGroups{$FileList[$#FileList]}{Sources}}, @SourceList;
			push @{$CompilationGroups{$FileList[$#FileList]}{Objects}}, @ObjectList;
		}
	}

#	debug print out	
	if (0) {
	foreach my $keyfile (keys %CompilationGroups) {
		print "$keyfile :\n";
		foreach my $class (keys %{$CompilationGroups{$keyfile}}) {
			print "\t$class:\n\t\t";
			print join " ", @{$CompilationGroups{$keyfile}{$class}}, "\n";
		}
	}
	}
			
}

sub PMStartSrcList {

	&main::Output(
		"# SOURCES\n",
		"\n"
	);

	InitMultiFileCompilation() if DoMultiFile();

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
	my @DepList=&main::DepList;
	return if (@DepList == 0);

	my @BldList=&main::BldList;	
	my $BaseSrc=&main::BaseSrc;
	my $ExtSrc=&main::ExtSrc;
	
	my $BaseObj=$BaseSrc;
	my $cia = 0;
	if ($ExtSrc =~ /cia/i ) {
		$cia = 1;
		$BaseObj .= '_';
	}

	foreach (@BldList) {
		my $tranasm = getConfigVariable('TRANASM');
		if ($tranasm)
		{
			&main::Output(
				&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.pre"), " ",
			) if $cia;
		}

		&main::Output(
			&Generic_Quote("\$(EPOCBLD$_)\\$BaseObj.cpp"), " ",
		) if $cia;
		&main::Output(
			&Generic_Quote("\$(EPOCBLD$_)\\$BaseSrc.lis"), " ",
			&Generic_Quote("\$(EPOCBLD$_)\\$BaseObj.o"), " \\\n",
		);
	}
	&main::Output(
		":"
	);

	my $prefix_file=getConfigVariable('PREFIXFILE');

	my @tempdeplist = &main::DepList;

	my $totalcount = $#tempdeplist;
	my $count = 0;
	while( $totalcount >= $count )
	{
		my $dependencyfile = shift(@tempdeplist);
		if($dependencyfile eq $prefix_file )
		{
			$DepList[$count]="\$(PREFIXFILE)";
		}
		$count += 1;
	}

        PrintList("\' \\\n\t\'\.\&Generic_Quote\(\$_\)", @DepList);
	&main::Output(
		"\n",
		"\n"
	);
}

sub PMSrcBldDepend {
	my @DepList=&main::DepList;
	return if (@DepList == 0);
	
	my $Bld=&main::Bld;
	my $BaseSrc=&main::BaseSrc;
	my $ExtSrc=&main::ExtSrc;
	
	my $BaseObj=$BaseSrc;
	my $cia = 0;
	if ($ExtSrc =~ /cia/i ) {
		$cia = 1;
		$BaseObj .= '_';
	}

	my $tranasm = getConfigVariable('TRANASM');
	if ($tranasm)
	{
		&main::Output(
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.pre"), " ",
		) if $cia;
	}

	&main::Output(
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseObj.cpp"), " ",
	) if $cia;

	&main::Output(
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.lis"), " ",
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseObj.o"), " :",
	);

	my $prefix_file=getConfigVariable('PREFIXFILE');

	my @tempdeplist = &main::DepList;

	my $totalcount = $#tempdeplist;
	my $count = 0;
	while( $totalcount >= $count )
	{
		my $dependencyfile = shift(@tempdeplist);
		if($dependencyfile eq $prefix_file )
		{
			$DepList[$count]="\$(PREFIXFILE)";
		}
		$count += 1;
	}

        PrintList("\' \\\n\t\'\.\&Generic_Quote\(\$_\)", @DepList);
	&main::Output(
		"\n",
		"\n"
	);
}

my $curdrive = "x";

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

sub PMPrefixFile 
{
# Prefix Header File passed to the preprocessor
    
	my $prefix_file=getConfigVariable('PREFIXFILE');	
	return quoted_path($prefix_file) if defined $prefix_file;
}

sub PMEndSrcBld {
#       Generate multifile compilation stuff if needed.
        if (DoMultiFile()) {
	       MultiFileEndSrcBld();
	       return;
	}

	my $ABI=&main::ABI;
	my $BaseSrc=&main::BaseSrc;
	my $Bld=&main::Bld;
	my $Src=ucfirst lc &main::Src;
	my $SrcPath=&main::SrcPath;
	my $Ext = &main::Path_Split('Ext', $Src);
	my $LangOptions = &SelectLangOptions($Ext);
	# support for auto 'translated' ASM 
	my $AsmFilep = $AsmFiles{$Src};

	$preinclude = &GetToolChainPreInclude();

	my $RTWSrcPath=&main::Path_Chop(&main::Path_RltToWork($SrcPath));
	my $lfboption = LinkerFeedBackOption();

	if ($AsmFilep || $Ext =~ /cia/i) {
		&main::Output(
# compile the translated, preprocessed source
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.o"), " : ",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.cpp"), "\n",
			"\t\@echo $Src\n",
			"\t\$(CC$Bld) $lfboption $LangOptions ", "\$(INCLUDE_OPTION)"," $RTWSrcPath \$(INCDIR) \$(OUTPUT_OPTION) \$\@ \$(EPOCBLD$Bld)\\$BaseSrc\_.cpp\n",
			"\n"
			);
# rule to translate the preprocessed source
			my $tranasm = getConfigVariables('TRANASM');
			if ($tranasm)
			{
		&main::Output(
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.cpp"), " : ",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.pre"), "\n",

				"\t\$(TRANASM) \$(TRANASM_FLAGS) \$(TRANASM_OUTPUT_OPTION)\$\@ \$(TRANASM_INPUT_OPTION)\$(EPOCBLD$Bld)\\$BaseSrc.pre\n",
#			"\ttranasm.bat -n -s -o=\$\@ \$(EPOCBLD$Bld)\\$BaseSrc.pre\n",
			"\n"
			);
# rule to preprocess the source
		&main::Output(
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.pre"), " : ",
			&Generic_Quote("$SrcPath$Src"), "\n",
			"\t\$(CC$Bld) -E $preinclude $LangOptions ","\$(INCLUDE_OPTION)"," $RTWSrcPath \$(INCDIR) $RTWSrcPath\\$Src \$(OUTPUT_OPTION) \$\@ \n",
# generate an assembly listing target too
			"LISTING$Bld$BaseSrc\_ : ", &Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.lis"), "\n",
			"\t", &Generic_CopyAction("$SrcPath$BaseSrc\_.$ABI.lst"),
			"\n",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.lis"), " : ",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.cpp"), "\n",
			"\t\$(CC$Bld) $LangOptions ", "\$(ASSEMBLER_LISTING_OPTION) ","\$(INCLUDE_OPTION)"," $RTWSrcPath \$(INCDIR) \$(OUTPUT_OPTION) \$\@ \$(EPOCBLD$Bld)\\$BaseSrc\_.cpp\n",
			"\n"
			);
			}
			else
			{
			&main::Output(
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.cpp"), " : ",
			&Generic_Quote("$SrcPath$Src"), "\n",
			"\t\$(CC$Bld) -E $preinclude $LangOptions ","\$(INCLUDE_OPTION)"," $RTWSrcPath \$(INCDIR) $RTWSrcPath\\$Src \$(OUTPUT_OPTION) \$\@ \n",
# generate an assembly listing target too
			"LISTING$Bld$BaseSrc\_ : ", &Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.lis"), "\n",
			"\t", &Generic_CopyAction("$SrcPath$BaseSrc\_.$ABI.lst"),
			"\n",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.lis"), " : ",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.cpp"), "\n",
			"\t\$(CC$Bld) $LangOptions ", "\$(ASSEMBLER_LISTING_OPTION) ","\$(INCLUDE_OPTION)"," $RTWSrcPath \$(INCDIR) \$(OUTPUT_OPTION) \$\@ \$(EPOCBLD$Bld)\\$BaseSrc\_.cpp\n",
			"\n"
			);
			}
	} else {

		&main::Output(
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.o"), " : ",
			&Generic_Quote("$SrcPath$Src"), "\n",
			"\t\@echo $Src\n",
			"\t\$(CC$Bld) $lfboption $LangOptions ", "\$(INCLUDE_OPTION)"," $RTWSrcPath \$(INCDIR) \$(OUTPUT_OPTION) \$\@ $RTWSrcPath\\$Src\n",
			"\n",
# generate an assembly listing target too
			"LISTING$Bld$BaseSrc : ", &Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.lis"), "\n",
			"\t", &Generic_CopyAction("$SrcPath$BaseSrc.$ABI.lst"),
			"\n",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.lis"), " : ",
			&Generic_Quote("$SrcPath$Src"), "\n",
			"\t\$(CC$Bld) $LangOptions ","\$(ASSEMBLER_LISTING_OPTION) ","\$(INCLUDE_OPTION)"," $RTWSrcPath \$(INCDIR) \$(OUTPUT_OPTION) \$\@ $RTWSrcPath\\$Src \n",
			"\n"
			);
	}
}

my $MFVarN = 0;
sub MultiFileEndSrcBld {
	my $ABI=&main::ABI;
	my $BaseSrc=&main::BaseSrc;
	my $Bld=&main::Bld;
        my $KeyFile = &main::Src;
	my $Src=ucfirst lc $KeyFile;
	my $SrcPath=&main::SrcPath;
	my $Ext = &main::Path_Split('Ext', $Src);
#	my $LangOptions = &main::SelectLangOptions($Ext);
	my $LangOptions = &SelectLangOptions($Ext);
	# support for auto 'translated' ASM 
	my $AsmFilep = $AsmFiles{$Src};

	my $RTWSrcPath=&main::Path_Chop(&main::Path_RltToWork($SrcPath));
	my $lfboption = LinkerFeedBackOption();

	if ($AsmFilep || $Ext =~ /cia/i) {
		if ($CompilationGroups{$KeyFile}) {
#		       print "$KeyFile :\n";
#		       print "\tSources : ", join " ", @{$CompilationGroups{$KeyFile}{Sources}}, "\n";
#      		       print "\tSources : ", join " ", @{$CompilationGroups{$KeyFile}{Objects}}, "\n";
# compile the translated, preprocessed source
		       &main::Output( "OBJECTS$MFVarN = ");
		       foreach my $obj (@{$CompilationGroups{$KeyFile}{Objects}}) {
			       &main::Output( &Generic_Quote("\\\n\t\$(EPOCBLD$Bld)\\$obj"), " "); 
		       }
       		       &main::Output( "\n\n");
		       &main::Output( "SOURCES$MFVarN = ");
		       foreach my $src (@{$CompilationGroups{$KeyFile}{Sources}}) {
			       &main::Output( &Generic_Quote("\\\n\t\$(EPOCBLD$Bld)\\$src", " "));
		       }
       		       &main::Output( "\n\n");
		       &main::Output( "\$(OBJECTS$MFVarN) : \$(SOURCES$MFVarN) \n");

		       &main::Output(
				     "\t\@echo Compiling \$(SOURCES$MFVarN)\n", 
				     "\t\$(CC$Bld) ","\$(INCLUDE_OPTION)"," $RTWSrcPath \$(INCDIR) $lfboption\\\n",
				     "\t\t$LangOptions \$(OUTPUT_OPTION) \$\@ --multifile \$(SOURCES$MFVarN)"
		      );
       		       &main::Output( "\n\n");
		       $MFVarN++;
		}
		&main::Output(
# rule to translate the preprocessed source
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.cpp"), " : ",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.pre"), "\n",
			"\ttranasm.bat -n -s -o=\$\@ \$(EPOCBLD$Bld)\\$BaseSrc.pre\n",
			"\n",
# rule to preprocess the source
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.pre"), " : ",
			&Generic_Quote("$SrcPath$Src"), "\n",
			"\t\$(CC$Bld) -E $preinclude $LangOptions ","\$(INCLUDE_OPTION)"," $RTWSrcPath \$(INCDIR) $RTWSrcPath\\$Src \$(OUTPUT_OPTION) \$\@ \n",
# generate an assembly listing target too
			"LISTING$Bld$BaseSrc\_ : ", &Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.lis"), "\n",
			"\t", &Generic_CopyAction("$SrcPath$BaseSrc\_.$ABI.lst"),
			"\n",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.lis"), " : ",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.cpp"), "\n",
			"\t\$(CC$Bld) $LangOptions ", "\$(ASSEMBLER_LISTING_OPTION) ","\$(INCLUDE_OPTION)"," $RTWSrcPath \$(INCDIR) \$(OUTPUT_OPTION) \$\@ \$(EPOCBLD$Bld)\\$BaseSrc\_.cpp\n",
			"\n"
			);
	} else {

		if ($CompilationGroups{$KeyFile}) {
#		       print "$KeyFile :\n";
#		       print "\tSources : ", join " ", @{$CompilationGroups{$KeyFile}{Sources}}, "\n";
#      		       print "\tSources : ", join " ", @{$CompilationGroups{$KeyFile}{Objects}}, "\n";
#                      compile the source
		       &main::Output( "OBJECTS$MFVarN = ");
		       foreach my $obj (@{$CompilationGroups{$KeyFile}{Objects}}) {
			       &main::Output( &Generic_Quote("\\\n\t\$(EPOCBLD$Bld)\\$obj"), " "); 
		       }
       		       &main::Output( "\n\n");
		       &main::Output( "SOURCES$MFVarN = ");
		       foreach my $src (@{$CompilationGroups{$KeyFile}{Sources}}) {
			       &main::Output( &Generic_Quote("\\\n\t$src"), " ");
		       }
       		       &main::Output( "\n\n");
		       &main::Output( "\$(OBJECTS$MFVarN) : \$(SOURCES$MFVarN) \n");

		       &main::Output(
				     "\t\@echo Compiling \$(SOURCES$MFVarN)\n", 
				     "\t\$(CC$Bld) ", "\$(INCLUDE_OPTION)"," $RTWSrcPath \$(INCDIR) $lfboption\\\n",
				     "\t\t$LangOptions \$(OUTPUT_OPTION) \$\@ --multifile \$(SOURCES$MFVarN)"
		      );
       		       &main::Output( "\n\n");
		       $MFVarN++;
		}
#		generate an assembly listing target too
		&main::Output(
			"LISTING$Bld$BaseSrc : ", &Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.lis"), "\n",
			"\t", &Generic_CopyAction("$SrcPath$BaseSrc.$ABI.lst"),
			"\n",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.lis"), " : ",
			&Generic_Quote("$SrcPath$Src"), "\n",
			"\t\$(CC$Bld) $LangOptions ","\$(ASSEMBLER_LISTING_OPTION) ","\$(INCLUDE_OPTION)"," $RTWSrcPath \$(INCDIR) \$(OUTPUT_OPTION) \$\@ $RTWSrcPath\\$Src \n",
			"\n"
			);
	}
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

sub ImportLibraryList {
	my $dso;
	my $base;
	my @ImportLibList;
	foreach $dso (@_) {
		$base = &main::Path_Split('Base', $dso);
		$dso = $base.".dso";
		push @ImportLibList, $dso;
	}
	return @ImportLibList;
}

sub ChangeSlash($) {
	my $abspath = $_[0];
	$abspath =~ s/\\/\//g ;
	return $abspath;
}


sub IsCustomDllUseCase($)	{
	my $OrigTrg = $_[0];

	foreach (@CustomDlls) { 
		if ($OrigTrg =~ /$_/i)	{
			return 1;
		}
	}
	return 0;	
}

sub GetToolChainPreInclude {
	my $preinclude_file = getConfigVariable('PREINCLUDE_OPTION');
	my $Plat=&main::Plat;
	if($Plat eq "GCCE")
	{
		$preinclude_file =~ s/\\/\//g;
	}
  	return "$preinclude_file";
}

sub SelectLangOptions {
	my ($Ext) = @_;
	$preinclude = &GetToolChainPreInclude;
	if ($Ext=~/^.cpp$/) {
		return " \$(CPP_LANG_OPTION) $preinclude ";
	}
	if ($Ext=~/^.cia$/) {
		return " \$(CIA_LANG_OPTION) ";
	}
	if ($Ext=~/^.c$/) {
		return " \$(C_LANG_OPTION) $preinclude ";
	}
	return '';
}

sub IsMapOptAvail() {
	open PIPE, "arm-none-symbianelf-g++ -v 2>&1 | ";
	while(<PIPE>){
		
		if($_ =~ /gcc version (.*) \(release\).*/i)
		{
			if($1 lt "3.4.3")
			{
				return 0;
			}
			elsif($_ =~ /gcc version (.*) \(release\) \(CodeSourcery ARM (.*) (\d*)\)/i)
			{
				if($1 eq "3.4.3" && uc $2 ne "Q1B" && $3 ge 2005)
				{
					return 1;
				}
				elsif($1 gt "3.4.3")
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}

		}
		
	}
	close PIPE;
}

sub GetRTLibList() {
	my @RtLib;
	my $list = getConfigVariable('RUNTIME_LIBS_LIST') ;
	if (length($list) >0)
	{
		@RtLib = split(/\s+/, $list);
	}
		return @RtLib;
}

sub InitToolChain(@) {

	my $Plat=&main::Plat;

	if($Plat eq "ARMV5_ABIV2")
	{
		$RVCTMajorVersion = Armutl_RVCTMajorVersion();
		$RVCTMinorVersion = Armutl_RVCTMinorVersion();
		$RVCTVersion = "${RVCTMajorVersion}_${RVCTMinorVersion}";
		&Armutl_DoMmp(@_);
	}
}

sub GCCInstallPath {
	my $gccInstallPath;

	open PIPE, "arm-none-symbianelf-g++ -print-libgcc-file-name 2>&1 | ";
	while(<PIPE>)
	{
		$gccInstallPath = $_;
		$gccInstallPath =~ s/\//\\/g;
	}
	close PIPE;

#	Extract the path till the occurence of bin directory.
	my @Installpath = split(/\\\.\./, $gccInstallPath);

	return @Installpath[0];
}

my %BSF_keywords = (
		    COMMON_OPTIONS => 1,
		    THUMB_OPTIONS => 1,
		    ARM_OPTIONS => 1,
		    KERNEL_OPTIONS => 1,
		    INVARIANT_OPTIONS => 1
		   );


sub Set_Compiler_Options() {
        my %plat = (main::PlatRec());
	foreach my $option (@{$plat{'CUSTOMIZATION_DATA'}}) {
	        warn "Unrecognized BSF syntax: $option.\n"
		        unless ($option =~ /\s*(\S+)\s+(.+)$/);
		my $key = uc $1;
		my $val = $2;
	        warn "Unrecognized BSF keyword: $key.\n"
		        unless ($BSF_keywords{$key});
		if ($key =~ /COMMON_OPTIONS/) {
		        $commonOptions = $val;
			next;
		}
		if ($key =~ /THUMB_OPTIONS/) {
		        $thumbOptions = $val;
			next;
		}
		if ($key =~ /ARM_OPTIONS/) {
		        $armOptions = $val;
			next;
		}
		if ($key =~ /KERNEL_OPTIONS/) {
		        $kernelOptions = $val;
			next;
		}
		if ($key =~ /INVARIANT_OPTIONS/) {
		        $invariantOptions = $val;
			next;
		}

	}		
}

sub SysTrg () {
	return 1 if &main::SystemTrg;
	my $ExportLibrary=&main::ExportLibrary;
	return 1 if ($ExportLibrary =~ /EKERN/i);
	my $Trg=&main::Trg;
	return 1 if ($Trg =~ /KSRT/i);
	return 0;
}

sub GetLibList() {
	my @LibList;
	@LibList=&Armutl_ArmLibList;
	if(@LibList==0)
	{
		@LibList = ('$(STATIC_LIBS_LIST)');
	}
	return @LibList;
}

sub GetToolChainAsmFileList() {
	my @FileList;
	@FileList=&Armutl_AsmFileList;
	if(@FileList)
	{
		return @FileList;
	}
	return;
}

sub IsTargetRT() {
	my $RTtarget=&Armutl_ArmRT;
	if($RTtarget)
	{
		return $RTtarget;
	}
	return;
}

sub GetToolChainIncDir {
	my $Plat=&main::Plat;
	if($Plat eq "ARMV5_ABIV2")
	{
		return &Armutl_ArmIncDir;
	}
	if($Plat eq "GCCE")
	{
		my $gcc_install_path=GCCInstallPath;
		return "$gcc_install_path\\..\\lib\\gcc\\arm-none-symbianelf\\3.4.3\\include";
	}
	else
	{
		my $ToolChainIncDir;
		my $compiler_inc_path = getConfigVariable('COMPILER_INCLUDE_PATH');
		if (length($compiler_inc_path) > 0)
		{ 
			$ToolChainIncDir = $compiler_inc_path;
		}
		return $ToolChainIncDir;
	}
}

my $useLinkerFeedBack = 0;

sub LinkerFeedBackFile() {
  return unless $useLinkerFeedBack;
  my $Trg = &main::Trg;
  return "$Trg.lfb";
}

sub LinkerFeedBackOption() {
	return "" unless $useLinkerFeedBack;
	my $BasicTrgType=&main::BasicTrgType;
	return "" unless ($BasicTrgType=~/^(DLL|EXE)/o);
	my $file = LinkerFeedBackFile();
	return "/$(FEEDBACK_FILE_OPTION) $file ";

}

sub getConfigVariable
{
    my ($variable) = @_;
    initialiseConfigVariables();
    return $configVariables{$variable};
}

sub initialiseConfigVariables()
{
    if (!keys(%configVariables))
    {
	my $plat = &main::Plat;
	%configVariables = BPABIutl_Get_Config_Variables($plat);

	if (!keys(%configVariables))
	{
	    # no variables were extracted from configuration file.
	    &main::FatalError("Cannot extract configuration variables for $plat");
	}
    }
}

1;
