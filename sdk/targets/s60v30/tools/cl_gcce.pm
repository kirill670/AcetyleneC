# CL_GCCE.PM
#
# Copyright (c) 1997-2005 Symbian Ltd.  All rights reserved.
#

package Cl_gcce;

my %PlatToolChainHashTbl=(
	'TOOLPREFIX'=>'arm-none-symbianelf-',
	'COMPILER_REL'=>'arm-none-symbianelf-g++ ',
	'COMPILER_DBG'=>'arm-none-symbianelf-g++ -g ',
	'ENTRY'=>'--entry ',
	'OPTIMIZE'=>'-O',
	'INC'=>'-I ',
	'MAP'=>'-Map ',
	'LINKER'=>'ld ',
	'ARCHIVER'=>' arm-none-symbianelf-ar ',
	'DLL'=>' -shared --default-symver ',
	'SONAME'=>'-soname ',
	'DEBUG'=>' ',
	'ARCHIVE_CR'=>'cr',
	'STATIC_LIB_OPTION'=>' ',
	'ASM' => 'arm-none-symbianelf-as ',
	'SUPPORTS_VFPV2' => 0
);

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	InitToolChain
	ComputeToolChainCompilerOpts
	ComputeToolChainLinkerOpts
	GetToolChainOption
	GetLibList
	GetRTLibList
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

sub GetToolChainOption($){

	my $key = $_[0];

	if (defined $PlatToolChainHashTbl{$key})
	{
		if(uc $key eq "MAP")
		{
			if(IsMapOptAvail() eq 0)
			{
				return '';
			}
		}
		return $PlatToolChainHashTbl{$key};
	}
	else
	{
		print "cl_gcce.pm : $key is not defined in tool options \n";
		return 0;
	}

}


sub ComputeToolChainCompilerOpts{

# 	my $CompilerOption = $PlatToolChainHashTbl{TOOLPREFIX} . $PlatToolChainHashTbl{COMPILER_REL};
#	my $CompilerOption .= '-march=armv5';

	my $CompilerOption = ' -march=armv5t -mthumb-interwork -mapcs';

	$CompilerOption .= " -msoft-float -fexceptions -pipe -nostdinc -Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas";

#	my $WarningLevel=&main::CompilerOption("GCC");
#	$CompilerOption .= $WarningLevel;
	my $COption=&main::CompilerOption("GCCE");
	if ($COption){
		$CompilerOption .= " $COption  ";
	} 
	return $CompilerOption;

}

sub ComputeToolChainLinkerOpts{

	my $Linker = $PlatToolChainHashTbl{TOOLPREFIX} . $PlatToolChainHashTbl{LINKER};
	$Linker .= GetLibPath("-print-file-name=libsupc++.a");
	$Linker .= GetLibPath("-print-libgcc-file-name");
	$Linker .= " --target1-abs";
	$Linker .= " --no-undefined -nostdlib";
	$Linker .= " -Ttext 0x8000 -Tdata  0x400000 ";
	return $Linker;

}

sub InitToolChain(@) {
}

sub Set_Compiler_Options() {
}

sub SysTrg () {
	return 1 if &main::SystemTrg;
	my $ExportLibrary=&main::ExportLibrary;
	return 1 if ($ExportLibrary =~ /EKERN/i);
	my $Trg=&main::Trg;
	return 1 if ($Trg =~ /KSRT/i);
	return 0;
}

sub GetRTLibList() {
	# The scppnwdl.dso should come before drtrvct2_2.dso
	my @RtLib = ('dfpaeabi.dso', "dfprvct2_2.dso", 'drtaeabi.dso', 'drtaeabi.dso'.&main::ArchiveObjectOption('VtblExports.o'), 'scppnwdl.dso', "drtrvct2_2.dso");
	return @RtLib;
}

sub GetLibList() {
	my @LibList = ('-lsupc++', '-lgcc');
	return @LibList;
}

sub GetLibPath($) {
	my $gnulibgccPath;
	open PIPE, "arm-none-symbianelf-g++ $_[0] 2>&1 | ";
	while(<PIPE>){
		$gnulibgccPath = $_;
		$gnulibgccPath =~ s/\//\\/g;
	}
	close PIPE;
	my $SearchlibgccDir = &main::Path_Chop(&main::Path_Split('Path', $gnulibgccPath));
	my $LibPath = (" -L\"$SearchlibgccDir\"");

	return $LibPath;
}

sub GetToolChainAsmFileList() {
}

sub IsTargetRT() {
}

sub GetToolChainHelp_Mmp {
}

sub GetToolChainIncDir {
	my $libgccPath;
	open PIPE, "arm-none-symbianelf-g++ -print-libgcc-file-name 2>&1 | ";
	while(<PIPE>){
		$libgccPath = $_;
		$libgccPath =~ s/\//\\/g;
	}
	close PIPE;
	my $IncPath = &main::Path_Chop(&main::Path_Split('Path', $libgccPath));
	return "$IncPath\\include";
}

sub GetToolChainPreInclude {
	my $IncPath = &main::Path_Chop(&main::EPOCIncPath);
	$IncPath =~ s/\\/\//g;
	return "-include $IncPath\/GCCE\/GCCE.h";
}

sub GetToolChainPrefixFile {
	my $IncPath = &main::Path_Chop(&main::EPOCIncPath);
	return "$IncPath\/GCCE\/GCCE.h";
}

sub SelectLangOptions {
	my ($Ext) = @_;
	$preinclude = &GetToolChainPreInclude;
	if ($Ext=~/^.cpp$/) {
		return " -x c++ $preinclude ";
	}
	if ($Ext=~/^.cia$/) {
		return " -x c++ -S -Wa,-adln ";
	}
	if ($Ext=~/^.c$/) {
		return " -x c $preinclude ";
	}
	return '';
}

sub ArchiveObjectOption {
# Alas! Couldn't find a way to say the object within the archive
# even if we knew which object contains some of the symbols(like,
# _E32Dll or _E32Startup). Till we find a way, we are ignoring the
# object file in case of GNU link command. E.g. while for RVCT linker
# we say edll.lib(uc_dll_.o), for GNU linker, we say only edll.lib

	return '';
}

sub EntryPointOption($) {
	my $EPOption = GetToolChainOption(ENTRY);
	$EPOption .= "@_";
#Start with an undefined reference to this symbol so that 
#linker ropes in the object defining this symbol definition.
	$EPOption .= " -u @_";
	return $EPOption;
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
1;
