# CL_ARM.PM
#
# Copyright (c) 1997-2005 Symbian Software Ltd.  All rights reserved.
#


package Cl_arm;

my $ToolPrefix='';
my %PlatOpt=(
	'Dlltool'=>'',
	'Entry'=>'-e',
	'Ld'=>'',
	'Elftran'=>'',
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

# specify floating point model here
my $floatingpointmodel = "softvfp";

if (&main::ARMFPU && (&main::ARMFPU =~ /^VFPV2$/i)) {
	$floatingpointmodel = "vfpv2";
}

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
use Armutl;
use cl_generic;
use E32env;
use Genutl;

sub PMHelp_Mmp {
    &Armutl_Help_Mmp;
}

my $RVCTMajorVersion = Armutl_RVCTMajorVersion();
my $RVCTMinorVersion = Armutl_RVCTMinorVersion();
my $RVCTVersion = "${RVCTMajorVersion}_${RVCTMinorVersion}";

my $oP = '--';
$oP = '-' if ($RVCTMajorVersion == 2 && $RVCTMinorVersion < 2);

#Check the existence of elf2e32.exe in the system path
my $IsExistELF2E32EXE = 0;
    open ELF2E32PIPE, "elf2e32 2>&1 |";
    while (<ELF2E32PIPE>) {
	if($_=~/^Symbian Post Linker\, Elf2E32/) {
	    $IsExistELF2E32EXE = 1;
	    last;
	}
	next;
    }
    close ELF2E32PIPE;

my $ArmIncDir;
my @ArmLibList;
my $ArmRT = 0;
my %AsmFiles = ();
my %AsmDirs = ();



sub PMPlatProcessMmp (@) {
        &Armutl_DoMmp(@_);
	$ArmIncDir = &Armutl_ArmIncDir;
	&main::SetStdIncPaths($ArmIncDir);
	@ArmLibList = &Armutl_ArmLibList;
	$ArmRT = &Armutl_ArmRT;
	my @AsmFileList = &Armutl_AsmFileList;
	foreach (@AsmFileList) { $AsmFiles{ucfirst lc $_} = 1; }
}

sub SysTrg () {
	return 1 if &main::SystemTrg;
	my $ExportLibrary=&main::ExportLibrary;
	return 1 if ($ExportLibrary =~ /EKERN/i);
	my $Trg=&main::Trg;
	return 1 if ($Trg =~ /KSRT/i);
	return 0;
}

# Move to RVCT/RVDS2.1 
# my $RVCT20 = Armutl_ArmVersion() =~ /^2\.0$/;
my $RVCT20 = 0; 

# suppress these warnings & errors
#Warning: #66-D: enumeration value is out of "int" range 
# "EUSER\CBASE\Ub_act.cpp", line 20: Warning:  #161-D: unrecognized #pragma
# 611: overloaded virtual function "entity" is only partially overridden in <entitykind> "entity"
# "EUSER\CBASE\Ub_act.cpp", line 256: Warning:  #654-D: declaration modifiers are incompatible with previous declaration
# 997: <entity-kind> "entity" is hidden by "entity" -- virtual function override intended?
# "EPOC32\include\s32stor.h", line 354: Error:  #1152-D: polymorphic base classes need to be exported as well
# "INCLUDE\e32base.h", line 31: Warning:  #1300-D: ~CBufBase inherits implicit virtual
#"COMPSUPP\\RVCT2_1\\Dfpaeabi.cpp", line 87: Warning: A1488W: PROC/FUNC at line 9 without matching ENDP/ENDFUNC
#"COMPSUPP\\RVCT2_1\\Dfpaeabi.cpp", line 85: Warning: A1464W: ENDP/ENDFUNC without corresponding PROC/FUNC
#Warning: L6318W: _integrator_cm1136_ekern.in(.text) contains branch to a non-code symbol FindMostSignificantOne(unsigned long).

my $diag_suppressions = '--diag_suppress 66,161,611,654,997,1152,1300,1464,1488,6318,6331';

# downgrade from errors to warnings
my $diag_warnings = '';

# upgrade from warnings to errors
# Warning:  #1267-D: Implicit physical register R0 should be defined as a variable
my $diag_errors = '--diag_error 1267';
  
my $commonOptions = $RVCT20 ?
  "$diag_suppressions $diag_warnings $diag_errors" :
  "$diag_suppressions $diag_warnings $diag_errors";  

my $mmpReplaceOptions = &main::ReplaceOptions("ARMCC");
my @mmpOption = split(/\s+/,$mmpReplaceOptions); 
my $CompilerOption = &main::CompilerOption("ARMCC");
my $contingentOptions;
my $thumbOptions = $RVCT20 ? '-thumb' : '--thumb  --fpu '.$floatingpointmodel.' --exceptions --exceptions_unwind';
my $armOptions = $RVCT20 ? '-arm' : '--arm  --fpu '.$floatingpointmodel.' --exceptions --exceptions_unwind';
my $kernelOptions = $RVCT20 ? '-arm' : '--arm --no_exceptions --no_exceptions_unwind';
my $invariantOptions = $RVCT20 ? 
  '-cpu 5T --enum_is_int -Ono_known_library --export_vtbl -apcs /inter' :
  '--cpu 5T --enum_is_int -Ono_known_library --fpmode ieee_no_fenv --export_all_vtbl --no_vfe --apcs /inter';
$invariantOptions .= ' --dllimport_runtime' unless ($RVCTMajorVersion == 2 && $RVCTMinorVersion < 2);  

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
  return "--feedback $file ";
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

sub ComputeCompilerOpts() {
	my %plat = &main::PlatRec();
	Set_Compiler_Options() if ($plat{'CUSTOMIZES'});
	my $ABI=&main::ABI;
	if (SysTrg()) {
	        $contingentOptions = $kernelOptions;
        } elsif (main::BuildAsARM() or ($ABI eq 'ARMV4')) {
	        $contingentOptions = $armOptions;
        } else {
	        $contingentOptions = $thumbOptions.' -D__MARM_THUMB__';	
	}
	# hack support for ARMV4
	my $invopts = "$invariantOptions";
	if ($ABI eq 'ARMV4') {
		$invopts =~ s/5T/4/;
		$invopts =~ s/inter/nointer/;
	} else {
		$contingentOptions .= ' -D__MARM_INTERWORK__';
	}
	return $commonOptions.' '.$contingentOptions.' '.&main::CompilerOption("ARMCC").' '.$invopts;
}

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
	
	my $VariantFile=&main::VariantFile();

	my $Plat=&main::Plat;
	my $Trg=&main::Trg;
	if ($RVCTMajorVersion == 2 && $RVCTMinorVersion < 2) {
		if ($BasicTrgType=~/^LIB$/o) {
			# Temporary Workaround for RVCT2.1 static libs problem with RVCT2.2 builds
			# Rename all the static libs produced with RVCT2.1 as {libname}2_1.lib
		        if ($Trg=~/^\s*(\S+)(\.lib)$/io) {
			        if ($1!~/$RVCTVersion/i) {
				        $Trg=$1.$RVCTVersion.".lib";
				}
			}
			if ($BaseTrg!~/$RVCTVersion/i) {
			        $BaseTrg .= $RVCTVersion;
			}
		}
	}

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
	unless ($ABI eq 'ARMV5' or $ABI eq 'ARMV4') {
		&main::FatalError("Platform module - ABI \"$ABI\" unrecognised");
	}
	my $ComputeCompilerOpts=ComputeCompilerOpts();
	my $replace_count = $#mmpOption;
	while( $replace_count >= 0 ) {
		my $opt = shift(@mmpOption);
		my $rep = shift(@mmpOption);
		if( !($ComputeCompilerOpts =~ s/$opt\s+\S+\s+/\ $opt $rep /g) ){
			$ComputeCompilerOpts .= " ".$opt." ".$rep." ";
		}
		$replace_count -= 2;
	}
	$PlatOpt{Arm} = $ComputeCompilerOpts;

	my $InterWorking = ($ABI eq 'ARMV4') ? "" : "--inter";

	$Archive=$ToolPrefix.'armar';
	$Link=$ToolPrefix."armlink ${oP}diag_suppress 6331,6780 ";
	$Objcopy=$ToolPrefix.'objcopy';

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

	&main::Output(
		"INCDIR  ="
	);
	PrintList("\" -J \$_\"", @ChopRTWUserIncPaths);
	PrintList("\" -J \$_\"", @ChopRTWSysIncPaths);
	if ($ArmIncDir) {
		&main::Output(
		    " -J \"$ArmIncDir\" ",
		);	
	}
	&main::Output(
		"\n",
		"\n"
	);
	&main::Output(
		"ARMCCFLAGS=$PlatOpt{Arm} -c\\\n",
		"\n"
	);

	&main::Output(
		"ARMCCDEFS = "
	);
	PrintList("\" -D\$_\"", @MacroList);
	
	if($VariantFile){
	    &main::Output(" -D__PRODUCT_INCLUDE__=\\\"${VariantFile}\\\"");
	}

	&main::Output(
		" \$(USERDEFS)\n",
		"\n"
	);





	foreach (@BldList) {
		&main::Output(
			"ARMCC$_ = armcc"
		);
		if (/DEB$/o) {
			&main::Output(
				      ' -g -O0'
			);
		}
		else {
			&main::Output(
				      ' -O2'
			);
		}		
		&main::Output(
			' $(ARMCCFLAGS)'
		);
		my @ml = &main::MacroList($_);
		PrintList("\" -D\$_\"", @ml);
		&main::Output(
			" \$(ARMCCDEFS)\n"
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
					" ", &Generic_Quote("\$(EPOCLIB)\\LIB\\$PrimaryExportLibrary.lib"),
				);
				# if elf2e32.exe(postlinker) exists, then generate .dso along with .lib
				if ($IsExistELF2E32EXE) {
					&main::Output(
						" ", &Generic_Quote("\$(EPOCLIB)\\LIB\\$PrimaryExportLibrary.dso"), "\n"
					);
				}
				else {
					&main::Output("\n");
				}
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
				"\t\@echo Not attempting to create \"\$(EPOCLIB)\\LIB\\$PrimaryExportLibrary.lib\"\n",
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
			&Generic_Quote("\$(EPOCLIB)\\LIB\\$ExportLibrary.lib"), " : ",
			&Generic_Quote($DefFile), "\n",
				"\tperl -S prepdef.pl ", &Generic_Quote($DefFile), " \"\$(EPOCBLD)\\$ExportLibrary.prep.def\"\n",
				"\tdef2dll.bat --path=\$(EPOCLIB)\\LIB \\\n\t\t--bldpath=\$(EPOCBLD) \\\n\t\t--import=$ExportLibrary \\\n",
			"\t\t--deffile=\"\$(EPOCBLD)\\$ExportLibrary.prep.def\" \\\n\t\t--linkAs=$LinkAs \\\n\t\t$InterWorking\n",
			"\n",
		 );
		if ($ExtraExportLibrary) {
			&main::Output(
				"\n",
				&Generic_Quote("\$(EPOCLIB)\\LIB\\$ExtraExportLibrary.lib"), " : ",
				&Generic_Quote("\$(EPOCLIB)\\LIB\\$ExportLibrary.lib"), "\n",
				"\tcopy \$< \$@\n"
			);
		}
		#if elf2e32.exe(postlinker) exists, then generate .dso(which will be used by ABIV2 platforms)
		if ($IsExistELF2E32EXE) {
			&main::Output(
				"\n",
				&Generic_Quote("\$(EPOCLIB)\\LIB\\$ExportLibrary.dso"), " : ",
				&Generic_Quote($DefFile), "\n",
					"\telf2e32 --definput=\"\$(EPOCBLD)\\$ExportLibrary.prep.def\" --dso=",
					&Generic_Quote("\$(EPOCLIB)\\LIB\\$ExportLibrary.dso"),
					" --linkas=$LinkAs\n"
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
			"\t-\$(ERASE) \"\$(EPOCLIB)\\LIB\\$ExportLibrary.lib\"\n"
		);
		if ($ExtraExportLibrary) {
			&main::Output(
				"\t-\$(ERASE) \"\$(EPOCLIB)\\LIB\\$ExtraExportLibrary.lib\"\n"
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
    if ($RVCTMajorVersion == 2 && $RVCTMinorVersion < 2) {
	    # Temporary Workaround for RVCT2.1 static libs problem with RVCT2.2 builds
	    # Rename all the static libs used with RVCT2.1 as {libname}2_1.lib
	    if ($FirstLib=~/^\s*(\S+)(\.lib)$/io) {
		    if ($1!~/$RVCTVersion/i) {
			    $FirstLib=$1."${RVCTVersion}.lib";
		    }
	    }
    }
    my $BasicTrgType=&main::BasicTrgType;
    my @LibList;
    my @RTLibList = $RVCT20 ?
      ('udfp.lib', 'udrt.lib', 'udrt.lib(VtblExports.o)'):
      ('dfpaeabi.lib', "dfprvct${RVCTVersion}.lib", 'drtaeabi.lib', 'drtaeabi.lib(VtblExports.o)');
    if ($RVCTMajorVersion == 2 && $RVCTMinorVersion >= 2) {
	# The scppnwdl.lib should come before drtrvct2_2.lib
	push @RTLibList, "scppnwdl.lib";
	push @RTLibList, "drtrvct${RVCTVersion}.lib";
    }
    else
    {
	push @RTLibList, "dfprvct${RVCTVersion}-thunk.lib";
	push @RTLibList, "drtrvct${RVCTVersion}.lib";
    }
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
    if ($RVCTMajorVersion == 2 && $RVCTMinorVersion < 2) {
	    # Temporary Workaround for RVCT2.1 static libs problem with RVCT2.2 builds
	    # Rename all the static libs used with RVCT2.1 as {libname}2_1.lib
	    for (my $i =0; $i < scalar(@StatLibList); $i++) {
		    if ($StatLibList[$i]=~/^\s*(\S+)(\.lib)$/io) {
			    if ($1!~/$RVCTVersion/i) {
				    $StatLibList[$i]=$1."${RVCTVersion}.lib";
			    }
		    }
	    }
    }	     
    my $StatLinkPath=&main::StatLinkPath;
    my $Trg=&main::Trg;
    if ($RVCTMajorVersion == 2 && $RVCTMinorVersion < 2) {
	    if ($BasicTrgType=~/^LIB$/o) {
		    # Temporary Workaround for RVCT2.1 static libs problem with RVCT2.2 builds
		    # Rename all the static libs produced with RVCT2.1 as {libname}2_1.lib
		    if ($Trg=~/^\s*(\S+)(\.lib)$/io) {
			    if ($1!~/$RVCTVersion/i) {
				    $Trg=$1.$RVCTVersion.".lib";
			    }
		    }
		    if ($BaseTrg!~/$RVCTVersion/i) {
			    $BaseTrg .= $RVCTVersion;
		    }
	    }
    }

    my $TrgType=&main::TrgType;
    my @UidList=&main::UidList;
	my $InterWorking = ($ABI eq 'ARMV4') ? "" : "--inter";
	my %Version = &main::Version();
	my $ExtraExportLibrary;
	unless ($Version{explicit}) {
		$ExtraExportLibrary = $ExportLibrary;
		$ExtraExportLibrary =~ s/\{(\d|a|b|c|d|e|f){8}\}//i;
	}	
	my $objectsViaFile;

    if ($Bld =~ /DEB/) {
	@LibList = &main::DebugLibList;
	$Link.="${oP}debug ";
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
		push @releaseables, "$LibPath$ExportLibrary.lib";
		push @releaseables, "$LibPath$ExtraExportLibrary.lib" if ($ExtraExportLibrary);
		#if elf2e32.exe(postlinker) exists in the $PATH, then include .dsos also into releasables list
		if ($IsExistELF2E32EXE) {
			push @releaseables, "$LibPath$ExportLibrary.dso";
			push @releaseables, "$LibPath$ExtraExportLibrary.dso" if ($ExtraExportLibrary);
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
		if ($RVCTMajorVersion == 2 && $RVCTMinorVersion < 2) {
			# Temporary Workaround for RVCT2.1 static libs problem with RVCT2.2 builds
			&main::Output(
				" \\\n\t",
				&Generic_Quote("\$(EPOCSTATLINK$Bld)\\EDLLSTUB$RVCTVersion.lib")
			);
		}
		else {
			&main::Output(
				" \\\n\t",
				&Generic_Quote("\$(EPOCSTATLINK$Bld)\\EDLLSTUB.lib")
			);
		}
	}
	    
        PrintList("\' \\\n\t\'\.\&Generic_Quote\(\"\\\$\(EPOCSTATLINK$Bld\)\\\\\$_\"\)", @StatLibList);
        PrintList("\' \\\n\t\'\.\&Generic_Quote\(\"\\\$\(EPOCLIB\)\\\\LIB\\\\\$_\"\)", @LibList);
        
        my $StaticRTLib = $RVCT20 ? "usrt20" : "usrt${RVCTVersion}" ;
        # use ksrt for system code and usrt for user ARM code
        $StaticRTLib = "ksrt${RVCTVersion}" if ($SystemTrg);
        &main::Output(
	        " \\\n\t",
		&Generic_Quote("\$(EPOCSTATLINK$Bld)\\$StaticRTLib\.lib")
		) unless ($Trg =~ /(U|K)SRT/i || ($BasicTrgType=~/^LIB$/o));

	unless ($ArmRT || ($BasicTrgType=~/^LIB$/o)) {
	    my $TargLib = "$ExportLibrary.lib";
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
        PrintList("\' \\\n\t\'\.\&Generic_Quote\(\"\$_\"\)", @ArmLibList);
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"VTBLEXPORTS$Bld="
	);
        my $vtobj = quotemeta("(VtblExports.o)");
        PrintList("\' \\\n\t\'\.\&Generic_Quote\(\"\\\$\(EPOCLIB\)\\\\LIB\\\\\$_$vtobj\"\)", @LibList);
	&main::Output(
		"\n",
		"\n"
	);

	my $objectFiles;

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


	# Create "via" file containing all object files in order to reduce
	# command line lengths in pertinent calls
	$objectsViaFile = &main::MakeFilePath.$BaseTrg."_".$Bld."_objects.via";	
	&main::CreateExtraFile($objectsViaFile, $objectFiles);
	

        if ($BasicTrgType=~/^LIB$/o) {
	        &main::Output(
		      &Generic_Quote("\$(EPOCTRG$Bld)\\$Trg"),
		      " : \$(OBJECTS$Bld)"
		);
        } else {
	        &main::Output(
		      &Generic_Quote("\$(EPOCTRG$Bld)\\$Trg"), " : ",
		      &Generic_Quote("\$(EPOCBLD$Bld)\\$BaseTrg.in")
	        );
        }

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
		" \$(LIBS$Bld)"
	);

#	generate an export object from the ordered .DEF file
        if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEXP$/o || $TrgType=~/^EXEDLL$/o) {
#       	make the .exp file a dependency for targets that have exports		
		&main::Output(" ", &Generic_Quote("\$(EPOCBLD$Bld)\\$ExportLibrary.exp"), "\n");
		if (&main::ExportUnfrozen) {
		    &main::Output(
			"\tdef2dll.bat --path=\$(EPOCBLD$Bld) \\\n\t\t--bldpath=\$(EPOCBLD) \\\n\t\t--export=$ExportLibrary \\\n\t\t--import=$ExportLibrary\\\n",
			"\t\t--deffile=\$(EPOCBLD)\\$ExportLibrary.def \\\n\t\t--linkAs=$LinkAs \\\n\t\t$InterWorking\n"
		    );
		    &main::Output(
		        "\n",
		        "\tcopy \$(EPOCBLD$Bld)\\$ExportLibrary.lib ",
		        "\$(EPOCLIB)\\LIB\\$ExportLibrary.lib",
		        "\n"
		    );
		    if ($ExtraExportLibrary) {
			&main::Output(
			    "\n",
			    "\tcopy \$(EPOCLIB)\\LIB\\$ExportLibrary.lib ",
			    "\$(EPOCLIB)\\LIB\\$ExtraExportLibrary.lib",
			    "\n"
			);
		    }			    
		    #if elf2e32.exe(postlinker) exists, then generate .dso(which will be used by ABIV2 platforms)
		    if ($IsExistELF2E32EXE) {
			    &main::Output(
				    "\n",
				    "\telf2e32 --definput=\"\$(EPOCBLD)\\$ExportLibrary.def\" --dso=",
				    "\$(EPOCLIB)\\LIB\\$ExportLibrary.dso --linkas=$LinkAs\n"
			    );
			    if ($ExtraExportLibrary) {
				    &main::Output(
					    "\n",
					    "\tcopy \$(EPOCLIB)\\LIB\\$ExportLibrary.dso ",
					    "\$(EPOCLIB)\\LIB\\$ExtraExportLibrary.dso",
					    "\n"
				    );
			    }		
		    }		
	        }
	} else {
	    &main::Output("\n");
	}

#       get rid of any -symbols produced .map file
        if ($BasicTrgType=~/^(DLL|EXE)/o) {
	        &main::Output(
			"\t-\$(ERASE) \"\$(EPOCTRG$Bld)\\$Trg.map\" \n"
		);	
	}

		my $AbsentSubst = '';
        if ($BasicTrgType=~/^(DLL|EXE)/o) {
	        my $datalinkbase = "0x400000";
	        $datalinkbase = &main::DataLinkAddress if (&main::DataLinkAddress);

#               make sure the linker feedback file is writable if it exists.
		my $lfbfile = LinkerFeedBackFile();
		&main::Output(
			"\t\@if exist $lfbfile attrib -r $lfbfile\n"
			) if $useLinkerFeedBack;

		my $lfboption = LinkerFeedBackOption();

	        &main::Output(
		        "\t$Link ${oP}shl ${oP}reloc ${oP}split ${oP}rw-base $datalinkbase  \\\n\t\t$lfboption${oP}noscanlib $PlatOpt{Ld}\\\n"
			);
			my $EntrySymbol;
			if ($BasicTrgType=~/^DLL$/o) {
				$EntrySymbol = '_E32Dll';
			}
			elsif ($BasicTrgType=~/^EXE$/o) {
				$EntrySymbol = '_E32Startup';
			}
			if ($EntrySymbol) {
				$AbsentSubst = " -absent $EntrySymbol";
			}
	        if ($BasicTrgType=~/^DLL$/o) {
	            # get the right object file for the entry point
	            my $ObjFile = "UC_DLL_.o";
	            if ($FirstLib =~ /EDEV/i) {
		            $ObjFile = "D_ENTRY_.o";
	            }
	            if ($FirstLib =~ /EKLL/i) {
		            $ObjFile = "L_ENTRY_.o";
	            }
	            if ($FirstLib =~ /EEXT/i) {
		            $ObjFile = "X_ENTRY_.o";
	            }
	            if ($FirstLib =~ /EVAR/i) {
		            $ObjFile = "V_ENTRY_.o";
	            }
	            &main::Output(
				    "\t\t${oP}entry _E32Dll \$(EPOCSTATLINK$Bld)\\$FirstLib($ObjFile) \\\n",
				    "\t\t\$(EPOCBLD$Bld)\\$ExportLibrary.exp \\\n"
				);
	        } elsif ($BasicTrgType=~/^EXE$/o || $TrgType=~/^EXEXP$/o) {
			    # get the right object file for the entry point
			    my $ObjFile = "UC_EXE_.o" ;
			    if ($FirstLib =~ /KC_EXE/i) {
					$ObjFile = "K_ENTRY_.o";
			    }
				# If building user-side under RVCT2.0.x, use 2.0.1 static library	
				if ($RVCT20) { 
					if ($ObjFile =~/UC_EXE_.o/i) { 
						$FirstLib = "EEXE20.LIB"; 
					} 
				} 
			    
			    &main::Output( "\t\t${oP}entry _E32Startup \$(EPOCSTATLINK$Bld)\\$FirstLib($ObjFile) \\\n" );
			    if ($TrgType=~/^EXEXP$/o || $TrgType=~/^EXEDLL$/o) {
					&main::Output( "\t\t\$(EPOCBLD$Bld)\\$ExportLibrary.exp \\\n" );
			    }
			}
	        &main::Output(
		        "\t\t-o \"\$(EPOCBLD$Bld)\\$Trg\" \\\n",
		        "\t\t${oP}symbols ${oP}list \"\$(EPOCTRG$Bld)\\$Trg.map\" \\\n",
				"\t\t\$(EPOCBLD$Bld)\\$BaseTrg.in \\\n"
			);
	        &main::Output(
		        "\t\t\$(LIBS$Bld) \\\n",
				"\t\t\$(VTBLEXPORTS$Bld) \$(USERLDFLAGS) \n"
			);

	        if ($Bld=~/^UDEB$/o) {
	               &main::Output(
			       "\tcopy \"\$(EPOCBLD$Bld)\\$Trg\" \"\$(EPOCTRG$Bld)\\$BaseTrg.sym\"\n"
		       );
	        }
		
		if (&main::CompressTarget) {
			&main::Output(
				"\telftran $PlatOpt{Elftran} -version ", &Genutl_VersionToUserString(%Version), " -sid ", &main::SecureId(), " ", " -nocompress "
			);
		}
		else {
			&main::Output(
				"\telftran $PlatOpt{Elftran} -version ", &Genutl_VersionToUserString(%Version), " -sid ", &main::SecureId(), " "
			);
		}

		# hack - exexps are allowed data, but they look like dlls to elftran....
		if (&main::AllowDllData || $TrgType=~/^EXEXP$/o || $TrgType=~/^EXEDLL$/o) {
			&main::Output(
				' -allow'
			);
		}
		if (not &main::CallDllEntryPoints ) {
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
		&main::Output(
			"\\\n\t\t"
		);

		my $i=1;
		foreach (@UidList) {
			&main::Output(
				" -uid$i $_"
			);
			$i++;
		}
		if(&main::VendorId) {
			&main::Output(
				' -vid ',&main::VendorId
			);
		}
		&main::Output(
			"\\\n\t\t"
		);
		&main::Output(
			' -fpu ',$floatingpointmodel
		);
		&main::Output(
			' -capability ',&main::Capability
		);
		&main::Output(
			"\\\n\t\t"
		);
		&main::Output(
			" \"\$(EPOCBLD$Bld)\\$Trg\""
		);
		&main::Output(
			"\\\n\t\t"
		);
		&main::Output(
			" \"\$\@\" \n"
		);
		&main::Output(
			"\n"
		);

         }
         elsif ($BasicTrgType=~/^LIB$/o) {
	        &main::Output(
		        "\tarmar ${oP}create \$(EPOCSTATLINK$Bld)\\$Trg ${oP}via $objectsViaFile\n"
		);
         }

         &main::Output(
		 "\n"
	 );

    # TARGET *.IN
    #------------
	 
    &main::Output(
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseTrg.in"), ": \$(OBJECTS$Bld)\n",
		# Fix the "via" file for use with build 416 of ARMLINK - a defect currently exists where two adjacent words in a
		# build 416 ARMLINK via file lead to a buffer overload.  fixviafile.pl pops a benign '-diag_error' argument between
		# words that exceed this limit.  This workaround can be removed when ARMLINK is fixed.
		"\tperl -S fixviafile.pl \"$objectsViaFile\"\n",
 	    "\t$Link ${oP}partial \\\n",
	    "\t\t-o \$\@ \\\n",
	    "\t\t${oP}via $objectsViaFile\n\n",
    );
    

#   reorder the .DEF file taking frozen exports into account if there are any
    if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEXP$/o || $TrgType=~/^EXEDLL$/o) {

	    # TARGET *.EXP
	    #------------
	    &main::Output(
		    &Generic_Quote("\$(EPOCBLD$Bld)\\$ExportLibrary.exp"), ": \$(EPOCBLD$Bld)\\$BaseTrg.in"
	    );

# if project is frozen, makedef (and hence the .exp file) are dependent upon it
		unless (&main::ExportUnfrozen) {
			if (-e $DefFile) { # effectively "if project frozen ..."
			    &main::Output(" $DefFile");
			}
		}

	    &main::Output(
		"\n\tperl -S elf2inf.pl -o \$(EPOCBLD$Bld)\\$ExportLibrary.inf \\\n", 
		"\t\t\$\<",
		"\n\tperl -S makedef.pl $AbsentSubst -Inf \$(EPOCBLD$Bld)\\$ExportLibrary.inf \\\n"
	    );
    	if (!$DefFile || $NoExportLibrary) {    			
    		&main::Output( "\t\t-ignore_unfrozen_noncallable \\\n" );
    	}
	if (SysTrg()) {
    		&main::Output( "\t\t-SystemTargetType \\\n" );
    	}
    		
	    if (-e $DefFile) {	# effectively "if project frozen ..."
	            &main::Output(
			"\t\t-Frzfile \"$DefFile\" \\\n"
		    );
	    }
	    # freeze ordinals, a maximum of 2, for polymorphic dlls
	    my $Ordinal;
	    my $Num=1;
	    foreach $Ordinal (&main::Exports) {
	            &main::Output( "\t\t-$Num $Ordinal \\\n" );
		    $Num++;
	    }
	    
	    my $theDefFile = "\$(EPOCBLD)\\$ExportLibrary.def";
	    $theDefFile = $DefFile if (-e $DefFile && !&main::ExportUnfrozen);
	    &main::Output(
		"\t\t\"\$(EPOCBLD)\\$ExportLibrary.def\"\n",
		"\tcopy \$(EPOCBLD)\\$ExportLibrary.def \$(EPOCBLD$Bld)\\$ExportLibrary.def\n",
		"\tdef2dll.bat $AbsentSubst \\\n\t\t--path=\$(EPOCBLD$Bld) \\\n\t\t--bldpath=\$(EPOCBLD) \\\n\t\t--export=$ExportLibrary \\\n",
		"\t\t--deffile=$theDefFile \\\n\t\t--linkAs=$LinkAs \\\n\t\t$InterWorking\n"
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
		&main::Output(
			&Generic_Quote("\$(EPOCBLD$_)\\$BaseSrc.pre"), " ",
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

	&main::Output(
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.pre"), " ",
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseObj.cpp"), " ",
	) if $cia;
	&main::Output(
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.lis"), " ",
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseObj.o"), " :",
	);
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
    my $IncPath = &main::EPOCIncPath;
    
    return quoted_path(&Generic_Quote("$IncPath"."RVCT${RVCTVersion}\\RVCT${RVCTVersion}.H"));
}


my $preinclude =   "--preinclude \$(EPOCINC)\\RVCT${RVCTVersion}\\RVCT${RVCTVersion}.h";

sub SelectLangOptions {
	my ($Ext) = @_;
	if ($Ext=~/^.cpp$/) {
		return "--cpp $preinclude ";
	}
	if ($Ext=~/^.cia$/) {
		return "--cpp ";
	}
	if ($Ext=~/^.c$/) {
		if($CompilerOption =~/^--cpp$/) { 
			return "--cpp $preinclude ";
		}
		else {
			return "--c90 $preinclude ";
		}
	}
	return '';
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

	my $RTWSrcPath=&main::Path_Chop(&main::Path_RltToWork($SrcPath));
	my $lfboption = LinkerFeedBackOption();

	if ($AsmFilep || $Ext =~ /cia/i) {
		&main::Output(
# compile the translated, preprocessed source
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.o"), " : ",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.cpp"), "\n",
			"\t\@echo $Src\n",
			"\t\$(ARMCC$Bld) $lfboption$LangOptions -J $RTWSrcPath \$(INCDIR) -o \$\@ \$(EPOCBLD$Bld)\\$BaseSrc\_.cpp\n",
			"\n",
# rule to translate the preprocessed source
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.cpp"), " : ",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.pre"), "\n",
			"\ttranasm.bat -n -s -o=\$\@ \$(EPOCBLD$Bld)\\$BaseSrc.pre\n",
			"\n",
# rule to preprocess the source
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.pre"), " : ",
			&Generic_Quote("$SrcPath$Src"), "\n",
			"\t\$(ARMCC$Bld) -E $preinclude $LangOptions -J $RTWSrcPath \$(INCDIR) $RTWSrcPath\\$Src -o \$\@ \n",
# generate an assembly listing target too
			"LISTING$Bld$BaseSrc\_ : ", &Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.lis"), "\n",
			"\t", &Generic_CopyAction("$SrcPath$BaseSrc\_.$ABI.lst"),
			"\n",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.lis"), " : ",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.cpp"), "\n",
			"\t\$(ARMCC$Bld) $LangOptions -S -J $RTWSrcPath \$(INCDIR) -o \$\@ \$(EPOCBLD$Bld)\\$BaseSrc\_.cpp\n",
			"\n"
			);
	} else {

		&main::Output(
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.o"), " : ",
			&Generic_Quote("$SrcPath$Src"), "\n",
			"\t\@echo $Src\n",
			"\t\$(ARMCC$Bld) $lfboption$LangOptions -J $RTWSrcPath \$(INCDIR) -o \$\@ $RTWSrcPath\\$Src\n",
			"\n",
# generate an assembly listing target too
			"LISTING$Bld$BaseSrc : ", &Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.lis"), "\n",
			"\t", &Generic_CopyAction("$SrcPath$BaseSrc.$ABI.lst"),
			"\n",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.lis"), " : ",
			&Generic_Quote("$SrcPath$Src"), "\n",
			"\t\$(ARMCC$Bld) $LangOptions -S -J $RTWSrcPath \$(INCDIR) -o \$\@ $RTWSrcPath\\$Src \n",
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
				     "\t\$(ARMCC$Bld) -J $RTWSrcPath \$(INCDIR) $lfboption\\\n",
				     "\t\t$LangOptions -o \$\@ --multifile \$(SOURCES$MFVarN)"
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
			"\t\$(ARMCC$Bld) -E $preinclude $LangOptions -J $RTWSrcPath \$(INCDIR) $RTWSrcPath\\$Src -o \$\@ \n",
# generate an assembly listing target too
			"LISTING$Bld$BaseSrc\_ : ", &Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.lis"), "\n",
			"\t", &Generic_CopyAction("$SrcPath$BaseSrc\_.$ABI.lst"),
			"\n",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.lis"), " : ",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc\_.cpp"), "\n",
			"\t\$(ARMCC$Bld) $LangOptions -S -J $RTWSrcPath \$(INCDIR) -o \$\@ \$(EPOCBLD$Bld)\\$BaseSrc\_.cpp\n",
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
				     "\t\$(ARMCC$Bld) -J $RTWSrcPath \$(INCDIR) $lfboption\\\n",
				     "\t\t$LangOptions -o \$\@ --multifile \$(SOURCES$MFVarN)"
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
			"\t\$(ARMCC$Bld) $LangOptions -S -J $RTWSrcPath \$(INCDIR) -o \$\@ $RTWSrcPath\\$Src \n",
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

1;







