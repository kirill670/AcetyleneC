# CL_BPABI_RVCT.PM
#
# Copyright (c) 1997-2005 Symbian Software Ltd.  All rights reserved.
#

package Cl_bpabi_rvct;

use Armutl;

my $RVCTMajorVersion;
my $RVCTMinorVersion;
my $RVCTVersion;
my $commonOptions;
my $thumbOptions;
my $armOptions;
my $kernelOptions; 
my $invariantOptions;

# specify floating point model here
my $floatingpointmodel = "softvfp";

if (&main::ARMFPU && (&main::ARMFPU =~ /^VFPV2$/i)) {
	$floatingpointmodel = "vfpv2";
}

my %PlatToolChainHashTbl=(
	'TOOLPREFIX'=>'',
	'COMPILER_DBG'=>'armcc -g --dwarf3 -O0 ',
	'COMPILER_REL'=>'armcc -O2 ',
	'ENTRY'=>'--entry ',
	'INC'=>'-J ',
	'MAP'=>'--symbols --list ',
	'CPP'=>'--cpp ',
	'ARCHIVER'=>'armar ',
	'DLL'=>' --dll --symver_soname ',
	'SONAME'=>'--soname ',
	'DEBUG'=>'--debug',
	'ARCHIVE_CR'=>'--create',
	'STATIC_LIB_OPTION'=>' --dllimport_runtime',
	'ASM' => 'armasm ',
	'SUPPORTS_VFPV2' => 1
);

my $ArmIncDir;
my @ArmLibList;

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	InitToolChain
	ComputeToolChainCompilerOpts
	ComputeToolChainLinkerOpts
	GetToolChainOption
	GetRTLibList
	GetLibList
	IsTargetRT
	GetToolChainAsmFileList
	GetToolChainIncDir
	GetToolChainPreInclude
	GetToolChainPrefixFile
	GetToolChainHelp_Mmp
	SelectLangOptions
	ArchiveObjectOption
	EntryPointOption
);


my $invariantOptions = '--cpu 5T --enum_is_int -Ono_known_library --fpmode ieee_no_fenv --export_all_vtbl --no_vfe --apcs /inter';

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

sub InitToolChain(@) {
	$RVCTMajorVersion = Armutl_RVCTMajorVersion();
	$RVCTMinorVersion = Armutl_RVCTMinorVersion();
	$RVCTVersion = "${RVCTMajorVersion}_${RVCTMinorVersion}";

	&Armutl_DoMmp(@_);
}

sub ComputeToolChainCompilerOpts() {

# suppress these warnings & errors
# "EUSER\CBASE\Ub_act.cpp", line 20: Warning:  #161-D: unrecognized #pragma
# 611: overloaded virtual function "entity" is only partially overridden in <entitykind> "entity"
# "EUSER\CBASE\Ub_act.cpp", line 256: Warning:  #654-D: declaration modifiers are incompatible with previous declaration
# 997: <entity-kind> "entity" is hidden by "entity" -- virtual function override intended?
# "EPOC32\include\s32stor.h", line 354: Error:  #1152-D: polymorphic base classes need to be exported as well
# "INCLUDE\e32base.h", line 31: Warning:  #1300-D: ~CBufBase inherits implicit virtual
#"COMPSUPP\\RVCT2_1\\Dfpaeabi.cpp", line 87: Warning: A1488W: PROC/FUNC at line 9 without matching ENDP/ENDFUNC
#"COMPSUPP\\RVCT2_1\\Dfpaeabi.cpp", line 85: Warning: A1464W: ENDP/ENDFUNC without corresponding PROC/FUNC
#Warning: L6318W: _integrator_cm1136_ekern.in(.text) contains branch to a non-code symbol FindMostSignificantOne(unsigned long).

my $diag_suppressions = '--diag_suppress 161,611,654,997,1152,1300,1464,1488,6318';

# downgrade from errors to warnings
my $diag_warnings = '';

# upgrade from warnings to errors
# Warning:  #1267-D: Implicit physical register R0 should be defined as a variable
my $diag_errors = '--diag_error 1267';

$commonOptions = $diag_suppressions;
$commonOptions .= " ".$diag_warnings;
$commonOptions .= " ".$diag_errors;


my $mmpReplaceOptions = &main::ReplaceOptions("ARMCC");
my @mmpOption = split(/\s+/,$mmpReplaceOptions); 
my $CompilerOption = &main::CompilerOption("ARMCC");
my $contingentOptions;
#commented due to problem of relocation
$thumbOptions = '--thumb  --fpu '.$floatingpointmodel.' --exceptions --exceptions_unwind';
#my $thumbOptions = '--thumb  --fpu '.$floatingpointmodel.' ';
$armOptions = '--arm  --fpu '.$floatingpointmodel.' --exceptions --exceptions_unwind';
$kernelOptions = '--arm --exceptions --exceptions_unwind';
#my $kernelOptions = '--arm --no_exceptions --no_exceptions_unwind';
$invariantOptions = '--cpu 5T --enum_is_int -Ono_known_library --fpmode ieee_no_fenv --export_all_vtbl --no_vfe --apcs /inter';
 

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

sub GetRTLibList() {
	#run-time library list
#	my $vtblObj = &main::ArchiveObjectOption('VtblExports.o');
#	my @RtLib = ('dfpaeabi.lib', "dfprvct${RVCTVersion}.lib", "dfprvct${RVCTVersion}-thunk.lib", 'drtaeabi.lib', "drtaeabi.lib$vtblObj", "drtrvct${RVCTVersion}.lib");
# Commented passing the object file in the lib as drtaeabi.lib is a dso file and not an archive lib...
	# The scppnwdl.dso should come before drtrvct2_2.dso
#	my @RtLib = ('dfpaeabi.dso', "dfprvct${RVCTVersion}.dso", 'drtaeabi.dso', 'scppnwdl.dso', "drtrvct${RVCTVersion}.dso");
	my @RtLib = ('drtaeabi.dso', 'dfpaeabi.dso', "dfprvct${RVCTVersion}.dso", 'scppnwdl.dso', "drtrvct${RVCTVersion}.dso");
	return @RtLib;
}

sub GetLibList() {
	return &Armutl_ArmLibList;
}

sub GetToolChainAsmFileList() {
	return &Armutl_AsmFileList;
}

sub IsTargetRT() {
	return &Armutl_ArmRT;
}

sub GetToolChainOption($) {
	my ($key) = @_;

	if( defined($PlatToolChainHashTbl{$key}) ){
		return 	$PlatToolChainHashTbl{$key};
	}
	else{
		print "Unrecognized option :$key:\n";
		return "";
	}
}

sub GetToolChainIncDir {
	return &Armutl_ArmIncDir;
}

sub GetToolChainPreInclude {
	return "--preinclude \$(EPOCINC)\\RVCT2_2\\RVCT2_2.h";
}

sub GetToolChainPrefixFile {
	my $IncPath = &main::Path_Chop(&main::EPOCIncPath);
	return ("$IncPath\\RVCT2_2\\RVCT2_2.h");
}

sub GetToolChainHelp_Mmp {
	&Armutl_Help_Mmp;
}

#Linker options are set here

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

sub ComputeToolChainLinkerOpts{
	my $Link='armlink --diag_suppress 6331 ';
	my $datalinkbase = "0x400000";
	$datalinkbase = &main::DataLinkAddress if (&main::DataLinkAddress);

#make sure the linker feedback file is writable if it exists.
#	my $lfbfile = '';#TBD LinkerFeedBackFile();
#	&main::Output(
#		"\t\@if exist $lfbfile attrib -r $lfbfile\n"
#		) if $useLinkerFeedBack;
#
#	my $lfboption = '';#TBD LinkerFeedBackOption();
#	    &main::Output(
##		        "\t$Link --shl --reloc --split --rw-base 0x400000 --info sizes --xref --map  $PlatOpt{Ld}"
#		    "\t$Link --shl --reloc --split --rw-base $datalinkbase  \\\n\t\t$lfboption--noscanlib $PlatOpt{Ld}\\\n"
#		);
#	$Link .= "--bpabi --shl --reloc --split --rw-base $datalinkbase  \\\n\t\t$lfboption--noscanlib $PlatOpt{Ld}";
#	$Link .= "--bpabi --shl --reloc --split --rw-base $datalinkbase  \\\n\t\t $PlatOpt{Ld}"; # Commented on Jan 27 to remove --shl option for solving "Warning: L6780W: STV_HIDDEN visibility removed from symbol 'User1::example()' through EXPORT".
# drop the --no_scanlib until ARM fix the defect
#	$Link .= "--bpabi --reloc --split --no_scanlib --rw-base $datalinkbase  \\\n ";
	$Link .= "--bpabi --reloc --split --rw-base $datalinkbase  \\\n ";
	return $Link;
}

sub SelectLangOptions {
	my ($Ext) = @_;
	$preinclude = &GetToolChainPreInclude;
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

sub ArchiveObjectOption($) {
	return "(@_)";
}

sub EntryPointOption($) {
	my $EPOption = GetToolChainOption(ENTRY);
	$EPOption .= "@_ ";
	return $EPOption;
}

1;
