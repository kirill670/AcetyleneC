# E32PLAT.PM
#
# Copyright (c) 1997-2005 Symbian Ltd.  All rights reserved.
#


# Module providing platform details for platforms supported
# by Symbian OS
#
# all data is uppercase

package E32Plat;

require Exporter;
@ISA=qw(Exporter);

@EXPORT=qw(
	Plat_SetVerbose
	Plat_Init
	Plat_GetL
	Plat_List
	Plat_AssocIDE
	Plat_Customizations
	Plat_Customizes
);

use Winutl;
use Armutl;
use BPABIutl;

my %Mode=(
	Verbose=>0
);
my $ModulePath;

sub Plat_SetVerbose () {
	$Mode{Verbose}=1;
}

my %BldLists=(
	EPOC32=>['UREL','UDEB'],
	WINS=>['UDEB','UREL'],
	TOOLS=>['DEB','REL']
);

my %BldMacros=(
	DEB=>['_DEBUG'],
	REL=>['NDEBUG'],
	UDEB=>['_DEBUG','_UNICODE'],
	UREL=>['NDEBUG','_UNICODE']
);
#Added SERIES60 macros
my @EpocMacros=('__SYMBIAN32__','__SERIES60_30__','__SERIES60_3X__');

my @BPABIPlats = &BPABIutl_Plat_List;

my %Plat=(
	ARM4=>{
		ABI=>'ARM4',
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
	},
	ARM4T=>{
		ABI=>'ARM4T',
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
	},
	ARMI=>{
		ASSP=>'MARM',
		Generic=>1,
		ASSPABI=>'',
	},
	SARM4=>{
		ABI=>'ARM4',
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
		Single=>1,
	},
	SARMI=>{
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
		Single=>1,
	},
	STHUMB=>{
		ABI=>'THUMB',
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
		Single=>1,
	},
	THUMB=>{
		ABI=>'THUMB',
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
	},
	TOOLS=>{
		ABI=>'TOOLS',
		ASSPABI=>'',
		Compiler=>'VC32',
		CPU=>'TOOLS',
		OS=>'TOOLS',
		MakeMod=>'Cl_win',
		MakeCmd=>'nmake',
	},
	CWTOOLS=>{
 		ABI=>'TOOLS',
 		ASSPABI=>'',
 		Compiler=>'CW32',
 		CPU=>'TOOLS',
 		OS=>'TOOLS',
 		MakeMod=>'Cl_tools',
 		MakeCmd=>'make',
 	},
	VC6TOOLS=>{
		ABI=>'TOOLS',
		ASSPABI=>'',
		Compiler=>'VC32',
		CPU=>'TOOLS',
		Ext=>'.DSP',
		MakeMod=>'Ide_vc6',
		MakeCmd=>'nmake',
		OS=>'TOOLS',
		Real=>'TOOLS',
		UsrHdrsOnly=>1,
	},
	WINS=>{
		ABI=>'WINS',
		ASSPABI=>'',
		Compiler=>'VC32',
		CPU=>'WINS',
		MakeMod=>'Cl_win',
		MakeCmd=>'nmake',
		OS=>'WINS',
	},
	VC6=>{
		ABI=>'WINS',
		ASSPABI=>'',
		Compiler=>'VC32',
		CPU=>'WINS',
		Ext=>'.DSP',
		MakeMod=>'Ide_vc6',
		MakeCmd=>'nmake',
		OS=>'WINS',
		Real=>'WINS',
		UsrHdrsOnly=>1,
	},
	WINSCW=>{
		ABI=>'WINSCW',
		ASSPABI=>'',
		Compiler=>'CW32',
		CPU=>'WINS',
		MakeMod=>'Cl_codewarrior',
		OS=>'WINS',
		DefFile=>'WINS',	# use the MSVC def files
	},
	CW_IDE=>{
		ABI=>'WINSCW',
		ASSPABI=>'',
		Compiler=>'CW32',
		CPU=>'WINS',
		Ext=>'.xml',
		MakeMod=>'Ide_cw',
		MakeCmd=>'make',
		OS=>'WINS',
		Real=>'WINSCW',
		DefFile=>'WINS',	# use the MSVC def files
		UsrHdrsOnly=>1,
		SupportsMultiplePlatforms=>1,	# supports more than one real platform
	},
	X86=>{
		ABI=>'X86',
		ASSPABI=>'',
		Compiler=>'VC32',
		CPU=>'X86',
		MakeMod=>'Cl_x86',
		MakeCmd=>'nmake',
		OS=>'EPOC32',
		DefFile=>'X86',
		Generic=>1,
	},
	ARMV4=>{
		ABI=>'ARMV4',
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
		MakeMod=>'Cl_arm',
		Compiler=>'ARMCC',
		DefFile=>'EABI',
		EABI=>1,
	},
	ARMV5=>{
		ABI=>'ARMV5',
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
		MakeMod=>'Cl_arm',
		Compiler=>'ARMCC',
		DefFile=>'EABI',
		EABI=>1,
	},
	ABIV2=>{
		ABI=>'ARMV5',
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
		MakeMod=>'Cl_bpabi',
		DefFile=>'EABI',
		EABI=>1,
	},
	GCCXML=>{
		ABI=>'ARM4',
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
		MakeMod=>'cl_gccxml',
	},
	VS6=>{
		ABI=>'WINSCW',
		ASSPABI=>'',
		Compiler=>'CW32',
		CPU=>'WINS',
		MakeMod=>'Cl_vscw',
		OS=>'WINS',
		Real=>'WINSCW',
		DefFile=>'WINS',	# use the MSVC def files
		Ext=>'.mak'		
	},
	VS2003=>{
		ABI=>'WINSCW',
		ASSPABI=>'',
		Compiler=>'CW32',
		CPU=>'WINS',
		MakeMod=>'Cl_vscw',
		OS=>'WINS',
		Real=>'WINSCW',
		DefFile=>'WINS',	# use the MSVC def files
		Ext=>'.mak'
	},
	EDG=>{
		ABI=>'ARMV5',
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
		MakeMod=>'cl_edg',
	},

	# ASSP platforms should be described using .ASSP files
	# Do not add additional ASSP platforms to this file.
);

sub Plat_Customizations($) {
        my ($plat) = @_;
	my @empty = ();
	return @{$Plat{$plat}{'CUSTOMIZATIONS'}} if $Plat{$plat}{'CUSTOMIZATIONS'};
	return @empty;
      }

sub Plat_Customizes($) {
	my ($plat) = @_;
	return $Plat{$plat}{'CUSTOMIZES'};
}

sub Init_BSFs($) {
	my ($Path)=@_;  
#	get a list of modules
	opendir DIR, $Path;
	my @BSFs=grep s/^([^\.].*)\.BSF$/$1/, map { uc $_ } readdir DIR;
	closedir DIR;

	my $BSF;
	foreach $BSF (@BSFs) {
		my $File=$Path.$BSF.'.bsf';
#		check whether the assp is already defined
		if (defined %{$Plat{$BSF}}) {
			warn(
				"$File : warning: Platform \"$BSF\" already defined\n",
				" ... skipping this spec\n"
			);
			delete $Plat{$BSF};
			next;
		}
#		open the module
		unless (open FILE, $File) {
			delete $Plat{$BSF};
			warn "warning: Can't open BSF specification \"$File\"\n";
			next;
		}
		my $line1 = <FILE>;
		$line1 = uc($line1);
		unless ($line1 =~ /^\#\<BSF\>\#/) {
			warn "warning: \"$File\" Invalid BSF specification - missing #<bsf>#\n";
			delete $Plat{$BSF};
			close FILE;
                  next;
            }
            my $custom;
            while ($custom = <FILE>) {
                	#skip blank lines and comments
			delete $Plat{$BSF};
                	last unless ($custom =~ /^$|^\#/);
            }
            $custom = uc $custom;
            unless ($custom =~ /^\s*CUSTOMIZES\s+(\S+)/) {
            	warn "warning: \"$File\" Invalid BSF specification - 'customizes' missing\n";
            	delete $Plat{$BSF};
            	close FILE;
			next;
            }
		my $root = $1;
		unless ($root =~ /^ARMV5/ || $root =~ /^ARMV5_ABIV2/) {
			warn "warning: \"$File\" Invalid BSF specification - customization restricted to ARMV5\n";
			close FILE;
			delete $Plat{$BSF};
			next;
		}

		my ( $key, $value);
		while (($key, $value) = each %{$Plat{$root}}) {
			$Plat{$BSF}{$key}=$value;
		}
		push @{$Plat{$root}{'CUSTOMIZATIONS'}}, $BSF;
		$Plat{$BSF}{'CUSTOMIZES'} = $root;
		while (<FILE>) {
			next if (/^$|^\#/);		        
			push @{$Plat{$BSF}{'CUSTOMIZATION_DATA'}}, $_;
		}
		close FILE;
	}
	1;
}

sub Plat_Init ($) { # takes path to ASSP modules
	my ($Path)=@_;

	my %PlatHashKeys=(
		ABI=>1,
		ASSPABI=>1,
		SINGLE=>1,
		Compiler=>1,
		CPU=>1,
		MakeMod=>1,
		MakeCmd=>1,
		OS=>1,
		DefFile=>1,
		ASSP=>1,
	);

	Init_BSFs($Path);

#	get a list of modules
	opendir DIR, $Path;
	my @_ASSPs=grep s/^([^\.].*)\.ASSP$/$1/, map { uc $_ } readdir DIR;
	closedir DIR;

	my @ASSPs;
	foreach (@_ASSPs) {
		if (!$ENV{USEARMCC} and /EDG$/i) {
#			warn(
#				"Note: ASSP \"$_\" disabled\n"
#			);

			next;
		}
		push @ASSPs, $_;
	}

#	open each module in turn, and add it to the array
	my $ASSP;
	foreach $ASSP (@ASSPs) {
		my $File=$Path.$ASSP.'.assp';
#		check whether the assp is already defined
		if (defined %{$Plat{$ASSP}}) {
			warn(
				"$File : warning: ASSP \"$ASSP\" already defined\n",
				" ... skipping this module\n"
			);

			next;
		}
#		open the module
		unless (open FILE, $File) {
			warn "warning: Can't open assp module \"$File\"\n";
			next;
		}
		my %Data=();
		my %SingleData=();
		my $MatchingSingle="";
		my @Errors=();
		while (<FILE>) {
#			strip comments
			s/^([^#]*)#.*$/$1/o;
#			skip blank lines
			if (/^\s*$/o) {
				next;
			}
#			get the key-value pair
			unless (/^\s*(\w+)\s+(\w+)\s*$/o) {
				push @Errors, "$File($.) : warning: syntax error - only key-value pairs allowed\n";
				next;
			}
			my ($Key, $Val)=($1, $2);
			if ($PlatHashKeys{$Key}!=1) {
				push @Errors, "$File($.) : warning: unrecognized keyword - $Key\n";
				next;
			}
			if ($Key eq "SINGLE") {
				$SingleData{Single} = 1;
				$SingleData{ASSP} = $ASSP;
				$MatchingSingle = uc $2;
			} else {
				$Data{$Key}=$Val;
				$SingleData{$Key}=$Val;
			}
		}
		close FILE;
		if (@Errors) {
			warn(
				@Errors,
				" ... skipping this module\n"
			);
			next;
		}
# hack -  Allow ASSPs to pick up all the options of the ABI they specify, 
# in particular the compiler they need.
	        $Data{'ASSP'} = $ASSP unless $Data{'ASSP'};
	        if ($Plat{$Data{'ABI'}}) {
		    foreach (keys %{$Plat{$Data{'ABI'}}}) {
			$Data{$_} = $Plat{$Data{'ABI'}}{$_} unless ($_ =~ /^GENERIC$/i) or $Data{$_};
		    }
		}

		%{$Plat{$ASSP}}=%Data;
		if ($MatchingSingle ne "") {
		    foreach (keys %Data) {
			$SingleData{$_} = $Data{$_} unless ($_ =~ /^GENERIC$/i) or $SingleData{$_};
		    }
		    %{$Plat{$MatchingSingle}}=%SingleData;
		}		    
	}
}

sub Plat_GetL ($$$) { # takes Platform name, ref to plat hash, ref to bldmacrohash
	my ($Candidate,$PlatHash_ref,$BldMacrosHash_ref)=@_;
	$Candidate=uc $Candidate;

# is platform in our list?
	unless (defined $Plat{$Candidate}) {

		# is platform BPABI compliant one?
		if (not(grep /^$Candidate$/i, @BPABIPlats))
		{
			die "ERROR: Platform \"$Candidate\" not supported\n";
		}
	}

	my $BPABIPlat;
	my %PlatHash=();

# check the data
	if (grep /^$Candidate$/i, @BPABIPlats) 
	{
		$BPABIPlat='ABIV2';
		%PlatHash=%{$Plat{$BPABIPlat}};
	}
	else
	{
		%PlatHash=%{$Plat{$Candidate}};
	}

# set the defaults
	$PlatHash{Name}=$Candidate;
	$PlatHash{Real}=$PlatHash{Name} unless $PlatHash{Real};
	$PlatHash{Ext}=".$PlatHash{Real}" unless $PlatHash{Ext};
	$PlatHash{ASSP}=$PlatHash{Real} unless $PlatHash{ASSP};

	if ($BPABIPlat) {
		if ($Candidate eq 'ARMV5_ABIV2') {  
			$PlatHash{Compiler}='ARMCC';
			$PlatHash{Toolchain}='rvct22';
		}
		else {
			$PlatHash{Compiler}=$Candidate;
			$PlatHash{Toolchain}=$Candidate;
		}
	}
	else {
		$PlatHash{Compiler}='GCC32' unless $PlatHash{Compiler};
	}
	$PlatHash{OS}='EPOC32' unless $PlatHash{OS};
	$PlatHash{MakeMod}='Cl_gcc' unless $PlatHash{MakeMod};
	$PlatHash{MakeCmd}='make' unless $PlatHash{MakeCmd};
	$PlatHash{CPU}='MARM' unless $PlatHash{CPU};
	$PlatHash{Single}=0 unless $PlatHash{Single};
	$PlatHash{UsrHdrsOnly}=0 unless $PlatHash{UsrHdrsOnly};
	$PlatHash{Generic}=0 unless $PlatHash{Generic}; # generic means "for a target device but no particular ASSP"
	$PlatHash{SupportsMultiplePlatforms}=0 unless $PlatHash{SupportsMultiplePlatforms};

	$PlatHash{ABI}='ARMI' unless $PlatHash{ABI};
	$PlatHash{ASSPABI}='ARM4' unless defined $PlatHash{ASSPABI};

	unless (defined $PlatHash{DefFile}) {
		if ($PlatHash{Compiler} eq 'VC32') {
		    $PlatHash{DefFile}='WINS';
		} else {
		    $PlatHash{DefFile}='MARM';
		}
	}
	
# .MMP macros - keeping the order is useful
	@{$PlatHash{MmpMacros}}=$PlatHash{Compiler};
	push @{$PlatHash{MmpMacros}}, $PlatHash{OS};
	push @{$PlatHash{MmpMacros}}, $PlatHash{CPU} unless $PlatHash{CPU} eq $PlatHash{OS};
	push @{$PlatHash{MmpMacros}}, $PlatHash{ASSP} unless $PlatHash{ASSP}=~/^($PlatHash{CPU}|$PlatHash{OS})$/;
	if ($PlatHash{Single}) {
		push @{$PlatHash{MmpMacros}}, 'SINGLE';
	}
	if ($PlatHash{EABI}) {
		push @{$PlatHash{MmpMacros}}, 'EABI';
	}
	if ($PlatHash{Compiler} eq 'VC32') {
		my $MSVCVer = &Winutl_MSVCVer;
		my $MSVCSubVer = &Winutl_MSVCSubVer;
		push @{$PlatHash{MmpMacros}}, 'MSVC'.$MSVCVer;
		push @{$PlatHash{MmpMacros}}, 'MSVC'.$MSVCVer.$MSVCSubVer;
		if ($MSVCVer > 6) {
			push @{$PlatHash{MmpMacros}}, 'MSVCDOTNET';
		}
	}
	if ($PlatHash{Compiler} eq 'ARMCC') {
		my $MajVer = &Armutl_RVCTMajorVersion;
		my $MinVer = &Armutl_RVCTMinorVersion;
		push @{$PlatHash{MmpMacros}}, 'ARMCC_'.$MajVer;
		push @{$PlatHash{MmpMacros}}, 'ARMCC_'.$MajVer.'_'.$MinVer;
	}

    # add GCCXML to the mmp macro list, so we can filter out stuff in bld.inf files and mmps.
    # note that this mean that __GCCXML__ is automacally routed to makefile, so we can take out explicit call. 
    if( $PlatHash{Name} eq "GCCXML") {
        push @{$PlatHash{MmpMacros}}, 'GCCXML';
    }
	
# add specific platform macros for platforms customising others.
	if (Plat_Customizes($PlatHash{Name})) {
		push @{$PlatHash{MmpMacros}}, $PlatHash{Name} unless grep /$PlatHash{Name}/, @{$PlatHash{MmpMacros}};
	}

# compilation macros
	@{$PlatHash{Macros}}=@EpocMacros;
	foreach (@{$PlatHash{MmpMacros}}) {
		push @{$PlatHash{Macros}}, '__'.$_.'__';
	}

#	extra special .MMP macros which aren't applied for compilation
	if ($PlatHash{Generic}) {
		push @{$PlatHash{MmpMacros}}, "GENERIC_$PlatHash{CPU}";
		if ($PlatHash{CPU} eq 'MARM') {
#			we can't define this for ASSP platforms because we won't be sure what
#			the ABI is until we've processed the .MMP file
			push @{$PlatHash{MmpMacros}}, "MARM_$PlatHash{ABI}";
		}
	}

# builds
	@{$PlatHash{Blds}}=@{$BldLists{$PlatHash{OS}}};

# output some information
	if ($Mode{Verbose}) {
		print
			"Platform         $PlatHash{Name}\n",
			"Real Name        $PlatHash{Real}\n",
			"Compiler         $PlatHash{Compiler}\n",
			"OS               $PlatHash{OS}\n",
			"CPU              $PlatHash{CPU}\n",
			"ASSP             $PlatHash{ASSP}\n",
			"ABI              $PlatHash{ABI}\n",
			"ASSPABI          $PlatHash{ASSPABI}\n",
			"Makefile Module  $PlatHash{MakeMod}\n",
			"Makefile Type    $PlatHash{MakeCmd}\n",
			"MMP Macros       @{$PlatHash{MmpMacros}}\n",
			"Macros           @{$PlatHash{Macros}}\n",
			"Blds             @{$PlatHash{Blds}}\n"
		;
	}

	%{$PlatHash_ref}=%PlatHash;
	%{$BldMacrosHash_ref}=%BldMacros;
}

sub Plat_List () {
#	return list of supported platforms

	sort keys %Plat;
}

sub Plat_AssocIDE ($$) {
#	return the IDE associated with a "Real" platform if there is one
	my ($Candidate, $AssocIDEs)=@_;

	unless (defined $Plat{$Candidate}) {
		die "ERROR: Platform \"$Candidate\" not supported\n";
	}

	my $Key;
	foreach $Key (keys %Plat) {
		if (${Plat{$Key}}{Real}) {
			if (${Plat{$Key}}{Real} eq $Candidate) {
				push @$AssocIDEs, $Key;
			}
		}
	}
}

1;
