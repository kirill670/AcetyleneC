# MAKEDEF.PL
#
# Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
#


# all variables called *Path* are set up to end with a backslash
# all variables called *Path or *File are stored as absolute (file)paths
# all variables called UpPath* are stored as relative paths


use FindBin;		# for FindBin::Bin
use Getopt::Long;

my $PerlBinPath;	# fully qualified pathname of the directory containing this script

# establish the path to the Perl binaries
BEGIN {
	require 5.005_03;				# check user has a version of perl that will cope
	$PerlBinPath = $FindBin::Bin;	# X:/epoc32/tools
	$PerlBinPath =~ s/\//\\/g;		# X:\epoc32\tools
}
use lib $PerlBinPath;

use Defutl;
use E32tpver;
use Pathutl;
use File::Copy;

# THE MAIN PROGRAM SECTION
##########################

{

	my %Options;
	my $INFILE;
	my $FRZFILE;
	my $OUTFILE;
	my @ObjFiles;

	# process the command-line
	unless (GetOptions(\%Options, '1=s', '2=s', 'deffile=s', 'frzfile=s', 'inffile=s', 'overwrite')) {
		exit 1;
	}
	unless (@ARGV==1) {
		&Usage;
	}

#	check the flags

	if (($Options{deffile} and $Options{inffile}) or (not ($Options{deffile} or $Options{inffile}))) {
		die "MAKEDEF ERROR: Must specify either -Deffile [file] or -Inf [file]\n";
	}
	if ($Options{frzfile} and $Options{1}) {
		die "MAKEDEF ERROR: Specify either -Frzfile [file] or -1 [name] {-2 [name]}\n";
	}
	if ($Options{2} && !$Options{1}) {
		die "MAKEDEF ERROR: Can't specify second export name and not first export name\n";
	}

#	process the flags
	if ($Options{deffile}) {
		$INFILE=$Options{deffile};
		unless (-e $INFILE) {
			die "MAKEDEF ERROR: $INFILE: Deffile not found\n";
		}
	}
	else {
		$INFILE=$Options{inffile};
		unless (-e $INFILE) {
			die "MAKEDEF ERROR: $INFILE: Inffile not found\n";
		}
	}
	if ($Options{frzfile}) {
		$FRZFILE=$Options{frzfile};
#		check the frozen .DEF file exists
		unless (-e $FRZFILE) {
			die "MAKEDEF ERROR: $FRZFILE: Frzfile not found\n";
		}
	}
	$OUTFILE=pop @ARGV;


#	Read the Frozen .DEF file if specified
	my @FrzDataStruct;
	if ($FRZFILE) {
		eval { &Def_ReadFileL(\@FrzDataStruct, $FRZFILE); };
		die $@ if $@;
	}
	elsif ($Options{1}) {
#		create an export structure for the names passed on the command line
		push @FrzDataStruct, {
			Name=>$Options{1},
			Ordinal=>1
		};
		if ($Options{2}) {
			push @FrzDataStruct, {
				Name=>$Options{2},
				Ordinal=>2
			};
		}
	}

#	Read the Input .DEF file
	my @InDataStruct;
	if ($Options{deffile}) {
		eval { &Def_ReadFileL(\@InDataStruct, $INFILE); };
	}
	else {
		eval { &ReadInfFileL(\@InDataStruct, $INFILE); };
	}
	die $@ if $@;

#	Compare the frozen .DEF data with the input .DEF or export info file data
	my (@NewDataStruct, @MissingDataStruct, @MatchedDataStruct);
	eval { &CompareFrzInL (\@NewDataStruct, \@MissingDataStruct, \@MatchedDataStruct, \@FrzDataStruct, \@InDataStruct); };
	die $@ if $@;

#	Create the output .DEF file
	eval { &CreateDefFileL(\@NewDataStruct, \@MatchedDataStruct, $OUTFILE); };
	die $@ if $@;

#	report missing frozen export errors
	if (@MissingDataStruct) {
		my @Errors;
		my $Num=@MissingDataStruct;
		my $Ref;
		if ($FRZFILE) {
			push @Errors, "MAKEDEF ERROR: $Num Frozen Export(s) missing from object files:\n";
			foreach $Ref (@MissingDataStruct) {
				push @Errors, "  $FRZFILE($$Ref{LineNum}) : $$Ref{Name} \@$$Ref{Ordinal}\n";
			}
		}
		else {
			push @Errors, "MAKEDEF ERROR: command-line: $Num Frozen Export(s) missing from object files:\n";
			foreach $Ref (@MissingDataStruct) {
				push @Errors, "  $$Ref{Name} \@$$Ref{Ordinal}\n";
			}
		}
		die "\n", @Errors;
	}
	elsif ($Options{overwrite} && -w $FRZFILE) #sag
		{
		warn "Copying $OUTFILE to $FRZFILE\n";
		rename $FRZFILE, "$FRZFILE.bak";
		copy($OUTFILE, $FRZFILE);
		}

	exit;
}

#######################################################################
# SUBROUTINES
#######################################################################

sub Usage () {

	print(
		"\n",
		"MAKEDEF - .DEF file generator (Build ",&E32tpver,")\n",
		"\n",
		"MAKEDEF {options} [Output .DEF file]\n",
		"\n",
		"options:   (case-insensitive)\n",
		"  -Deffile [Input .DEF file]\n",
		"  -Inffile [Input export information file]\n",
		"  -Frzfile [Frozen .DEF file]\n",
		"  -1 [first export name] {-2 [second export name]}\n",
		"  -Overwrite\n",
		"\n",
		"Either specify -Deffile or -Inffile, and\n",
		"either -Frzfile or -1 {-2} if required.\n"
	);
	exit 1;
}

sub ReadInfFileL ($$$) {
	my ($DataStructRef, $FILE)=@_;

#	open export information file for reading
	open (FILE, "<$FILE") or die "could not open $FILE: $!";

#	read the export info. file, and create dummy frozen .DEF file text
	my $LineNum=0;
	my $Ordinal=0;
	my $Comment='';
	my $Name='';
	my $InfType=0;	# dumpbin output
	my %exports;	# MWLD workaround - record mangled names in case we don't see the demangled ones
	my $Line;
	while ($Line=<FILE>) {
		$LineNum++;
		if ($InfType == 0) {
			if ($Line =~ /\*\*\* ARCHIVE SYMBOL TABLE.* \*\*\*/o) {
				$InfType=1;	# mwld disassembly output
				next;
			}
			if ($Line =~ /^\s+(\?\S+)(\s+\((.*)\))?$/o) {
#                   ??0TAgnAlarmDefaults@@QAE@XZ (public: __thiscall TAgnAlarmDefaults::TAgnAlarmDefaults(void))
				$Name=$1;
				$Comment=$3;
			} 
			elsif ($Line =~ /^\s+_(\S+)(\s+\((.*)\))?$/o) {
# frozen ordinals like "UserNoLongerSupported01" seem to inherit a leading underscore in the dumpbin output
				$Name=$1;
				$Comment=$3;
			}
			else {
				next;
			}
		}
		else {
			if ($Line =~ /^\s*\d+\s+\(.+\)\s+__imp_((.)(\S+))$/o) {
					if ($2 eq "_") {
							$Name = $3;		# C symbol, so remove leading underscore
							$Comment = '';	# name isn't mangled anyway
					} else {
							$Name = $1;		# C++ mangled name
							$Comment = '';	# can't unmangle names...
					}
					$exports{$Name}=$LineNum;
					next;
			}
			if ($Line =~ /\*\*\* Unmangled Symbols \*\*\*/o) {
				<FILE>; 
				$Line = <FILE>; 
				$LineNum+=2;
				if ($Line !~ /^\s*\d+:\s+(\S+)$/o) {
				    print STDERR "MAKEDEF WARNING: unknown inf file format\n";
				    next;
				}
				$Name = $1;
# Workaround: if MWLD can't demangle the name, we will see only the __imp_ version.
				if ($Name =~ /^__imp_(\S+)$/o) {
					$Name = $1;
				}
				$Line = <FILE>; 
				$LineNum++;
				next if ($Line !~ /^\s+(.+)$/o);
				$Comment = $1;
			}
			elsif ($Line =~ /^0x\S{8}\s+__imp__(\S+)$/o) {
				$Name = $1;	# leading underscore already removed
				$Comment = '';	# a C symbol, and therefore not mangled
			}
			else {
				next;
			}
		}

		$Ordinal++;
		$Comment='' if (!defined $Comment);
		push @$DataStructRef, {
			Ordinal=>$Ordinal,
			Name=>$Name,
			Comment=>$Comment,
			LineNum=>$LineNum
		};
		$exports{$Name}=0;	# indicates processed name
	}
	foreach $Name (keys %exports) {
		$LineNum = $exports{$Name};
		if ($LineNum > 0) {
			$Ordinal++;
			push @$DataStructRef, {
				Ordinal=>$Ordinal,
				Name=>$Name,
				Comment=>'',
				LineNum=>$LineNum
			};
		}
	}
}

sub CompareFrzInL ($$$$$) {
	my ($NewStructRef, $MissingStructRef, $MatchedStructRef, $FrzStructRef, $InStructRef)=@_;

#	compare the input export data with the frozen data

#	this function trashes the frozen .DEF data structure and the new .DEF data structure

#	nullify non-export statements in the structures
	foreach (@$FrzStructRef,@$InStructRef) {
		next if $$_{Name};
		undef $_;
	}

	my $LastOrdinal=0;

	my $FrzRef;
	my $InRef;
	FRZLOOP: foreach $FrzRef (@$FrzStructRef) {
		next unless $$FrzRef{Name};		# ignore lines in the .DEF file not containing an export
		if ($LastOrdinal<$$FrzRef{Ordinal}) {
			$LastOrdinal=$$FrzRef{Ordinal};
		}
		foreach $InRef (@$InStructRef) {
			next unless defined $InRef; # ignore nullified entries in the temporary array
#			does the function name match?
			if ($$InRef{Name} eq $$FrzRef{Name}) {
#				give the generated export the same number as the corresponding frozen one
				$$InRef{Ordinal}=$$FrzRef{Ordinal};
				push @$MatchedStructRef, $InRef;
				undef $InRef;
				next FRZLOOP;
			}
		}
#		these frozen exports haven't been found in the object files
		push @$MissingStructRef, $FrzRef;
#		put a comment in the generated .DEF file to that effect
		$$FrzRef{Missing}=1;
		push @$MatchedStructRef, $FrzRef;
	}

#	all the exports left in the new .DEF file aren't frozen - give them the right ordinals
	foreach $InRef (@$InStructRef) {
		next unless defined $InRef; # ignore nullified entries
		$LastOrdinal++;
		$$InRef{Ordinal}=$LastOrdinal;
		push @$NewStructRef, $InRef;
	}
}

sub CreateDefFileL ($$$) {
#	creates a new .DEF file
	my ($NewStructRef, $MatchedStructRef, $FILE)=@_;

	my @Text=("EXPORTS\n");
	my $LineNum=1;


	my $InRef;
	foreach $InRef (@$MatchedStructRef) {
		my $Comment='';
		if ($$InRef{Comment}) {
			$Comment=" ; $$InRef{Comment}";
		}
		if ($$InRef{Missing}) {
			push @Text, '; MISSING:';
		}
		my $r3unused = $$InRef{R3Unused} ? " R3UNUSED" : "";
		push @Text, "\t$$InRef{Name} \@ $$InRef{Ordinal} NONAME$r3unused$Comment\n";
		$LineNum++;
		next;
	}
	if (@$NewStructRef) {

#		warn about unfrozen exports and add them to the end of the generated .DEF file
		my $Num=@$NewStructRef;
		my @Warnings;
		push @Warnings, "MAKEDEF WARNING: $Num export(s) not yet Frozen:\n";

		push @Text, "; NEW:\n";
		$LineNum++;
		foreach $InRef (@$NewStructRef) {
			my $Comment='';
			if ($$InRef{Comment}) {
				$Comment=" ; $$InRef{Comment}";
			}
			my $r3unused = $$InRef{R3Unused} ? " R3UNUSED" : "";
			push @Text, "\t$$InRef{Name} \@ $$InRef{Ordinal} NONAME$r3unused$Comment\n";
			$LineNum++;
			push @Warnings, "  $FILE($LineNum) : $$InRef{Name} \@$$InRef{Ordinal}\n";
			next;
		}
		warn @Warnings;
	}

#	add a terminating newline
	push @Text, "\n";

#	write the new .DEF file
	eval { &Def_WriteFileL(\@Text, $FILE); };
	die $@ if $@;
}

