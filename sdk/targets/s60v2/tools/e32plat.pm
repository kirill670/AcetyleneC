# E32PLAT.PM
#
# Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
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
);


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

my %CompatibleABIs=(
	ARMI=>['ARM4', 'THUMB'],
	ARM4=>['ARMI'],
	THUMB=>['ARMI']
);

my @EpocMacros=('__SYMBIAN32__');

my %Plat=(
	ARM4=>{
		ABI=>'ARM4',
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
	},
	ARM4T=>{
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
	VC6WINC=>{
		ABI=>'WINS',
		ASSPABI=>'',
		Compiler=>'VC32',
		CPU=>'WINS',
		Ext=>'.DSP',
		OS=>'WINS',
		MakeMod=>'Ide_vc6',
		MakeCmd=>'nmake',
		Real=>'WINC',
		UsrHdrsOnly=>1
	},
	WINC=>{
		ABI=>'WINS',
		ASSPABI=>'',
		Compiler=>'VC32',
		CPU=>'WINS',
		MakeMod=>'Cl_win',
		MakeCmd=>'nmake',
		OS=>'WINS',
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
	GCCXML=>{
		ABI=>'ARM4',
		ASSP=>'MARM',
		ASSPABI=>'',
		Generic=>1,
		MakeMod=>'cl_gccxml',
	},

	# ASSP platforms should be described using .ASSP files
	# Do not add additional ASSP platforms to this file.
);

sub Plat_Init ($) { # takes path to ASSP modules
	my ($Path)=@_;

	my %PlatHashKeys=(
		ABI=>1,
		ASSPABI=>1,
		SINGLE=>1,
	);

#	get a list of modules
	opendir DIR, $Path;
	my @ASSPs=grep s/^([^\.].*)\.ASSP$/$1/, map { uc $_ } readdir DIR;
	closedir DIR;

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
		%{$Plat{$ASSP}}=%Data;
		if ($MatchingSingle ne "") {
			%{$Plat{$MatchingSingle}}=%SingleData;
		}		    
	}
}

sub Plat_GetL ($$$) { # takes Platform name, ref to plat hash, ref to bldmacrohash
	my ($Candidate,$PlatHash_ref,$BldMacrosHash_ref)=@_;
	$Candidate=uc $Candidate;

# is platform in our list?
	unless (defined $Plat{$Candidate}) {
		die "ERROR: Platform \"$Candidate\" not supported\n";
	}

# check the data
	my %PlatHash=%{$Plat{$Candidate}};

# set the defaults
	$PlatHash{Name}=$Candidate;
	$PlatHash{Real}=$PlatHash{Name} unless $PlatHash{Real};
	$PlatHash{Ext}=".$PlatHash{Real}" unless $PlatHash{Ext};
	$PlatHash{ASSP}=$PlatHash{Real} unless $PlatHash{ASSP};

	$PlatHash{Compiler}='GCC32' unless $PlatHash{Compiler};
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
	
#	get compatible ABIs
	@{$PlatHash{CompatibleABIs}}=();
	if ($CompatibleABIs{$PlatHash{ABI}}) {
		@{$PlatHash{CompatibleABIs}}=@{$CompatibleABIs{$PlatHash{ABI}}};
	}


# .MMP macros - keeping the order is useful
	@{$PlatHash{MmpMacros}}=$PlatHash{Compiler};
	push @{$PlatHash{MmpMacros}}, $PlatHash{OS};
	push @{$PlatHash{MmpMacros}}, $PlatHash{CPU} unless $PlatHash{CPU} eq $PlatHash{OS};
	push @{$PlatHash{MmpMacros}}, $PlatHash{ASSP} unless $PlatHash{ASSP}=~/^($PlatHash{CPU}|$PlatHash{OS})$/;
	if ($PlatHash{Single}) {
		push @{$PlatHash{MmpMacros}}, 'SINGLE';
	}

#	add GCCXML to the mmp macro list, so we can filter out stuff in bld.inf files and mmps.
#	note that this mean that __GCCXML__ is automacally routed to makefile, so we can take out explicit call. 
	if( $PlatHash{Name} eq "GCCXML") {
		push @{$PlatHash{MmpMacros}}, 'GCCXML';
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
			"CompatibleABIs   @{$PlatHash{CompatibleABIs}}\n",
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

sub Plat_AssocIDE ($) {
#	return the IDE associated with a "Real" platform if there is one
	my ($Candidate)=@_;

	unless (defined $Plat{$Candidate}) {
		die "ERROR: Platform \"$Candidate\" not supported\n";
	}

	my $Key;
	foreach $Key (keys %Plat) {
		if (${Plat{$Key}}{Real}) {
			if (${Plat{$Key}}{Real} eq $Candidate) {
				return $Key;
			}
		}
	}
	return '';
}

1;
