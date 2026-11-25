# cl_generic.pm
#
# Copyright (c) 2001 Symbian Ltd.  All rights reserved.
#


# this package contains generic routines to handle bits of makefiles which are
# common to all of the platforms. Currently it deals with AIF, MBM amd RSC files.

package cl_generic;

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	Generic_Define
	Generic_Definition
	Generic_MakeWorkDir
	Generic_MakeWorkFile
	Generic_Quote
	Generic_Header
	Generic_Releaseables
	Generic_BitMapBld
	Generic_ResrcBld
	Generic_AifBld
	Generic_End
	Generic_CopyAction
	Generic_WhatCleanTargets
);

use File::Basename;
use lockit_info;

my $SavedBldPath;
my $MakefileType=0;	# 0=NMAKE, 1=MAKE

sub Generic_Header ($$) {
	my ($UseRltPaths, $makefileType) = @_;
	
	$MakefileType=($makefileType eq "nmake")? 0:1;

	my $LibSubDir="UDEB";
#regression hack
	if (&main::PlatOS eq 'EPOC32') {
		$LibSubDir="UREL";
	}
#regression hack end

	my $BldPath=&main::BldPath;
	my $RelPath=&main::RelPath;
	my $LibPath=&main::LibPath;
	my $LinkPath=&main::LinkPath;
	my $StatLinkPath=&main::StatLinkPath;
	my $ASSPLinkPath=&main::ASSPLinkPath;

	$SavedBldPath=&main::Path_Chop($BldPath);

	if ($UseRltPaths) {
		$BldPath     =&main::Path_RltToWork($BldPath);
		$RelPath     =&main::Path_RltToWork($RelPath);
		$LibPath     =&main::Path_RltToWork($LibPath);
		$LinkPath    =&main::Path_RltToWork($LinkPath);
		$StatLinkPath=&main::Path_RltToWork($StatLinkPath);
		$ASSPLinkPath=&main::Path_RltToWork($ASSPLinkPath);
	}

	$BldPath=&main::Path_Chop($BldPath);
	$RelPath=&main::Path_Chop($RelPath);
	$LibPath=&main::Path_Chop($LibPath);
	$LinkPath=&main::Path_Chop($LinkPath);
	$StatLinkPath=&main::Path_Chop($StatLinkPath);
	$ASSPLinkPath=&main::Path_Chop($ASSPLinkPath);

	my $EPOCDataPath=&main::Path_Chop(&main::EPOCDataPath);
	my $EPOCIncPath=&main::Path_Chop(&main::EPOCIncPath);
	my $DataPath=&main::Path_Chop(&main::DataPath);
	my $TrgPath=&main::Path_Chop(&main::TrgPath);

	my $erasedefn = "\@erase";
	$erasedefn = "\@erase 2>>nul" if ($ENV{OS} eq "Windows_NT");

	&main::Output(
		"\n",
		'# CWD ',             &main::Path_WorkPath, "\n",
		'# MMPFile ',         &main::MmpFile,       "\n",
		'# Target ',          &main::Trg,           "\n",
		'# TargetType ',      &main::TrgType,       "\n",
		'# BasicTargetType ', &main::BasicTrgType,  "\n",
		'# MakefileType ', ($MakefileType==1)? "GNU":"NMAKE", "\n",
		"\n",
		"ERASE = $erasedefn\n",
		"\n",
		"# EPOC DEFINITIONS\n",
		"\n",
	);
	Generic_Define("EPOCBLD",  $BldPath);
	Generic_Define("EPOCTRG",  $RelPath);
	Generic_Define("EPOCLIB",  $LibPath);
	Generic_Define("EPOCLINK", $LinkPath);
	Generic_Define("EPOCSTATLINK", $StatLinkPath);
	Generic_Define("EPOCASSPLINK", $ASSPLinkPath);

	Generic_Define("EPOCDATA", $EPOCDataPath);
	Generic_Define("EPOCINC",  $EPOCIncPath);
	Generic_Define("TRGDIR",   $TrgPath);
	Generic_Define("DATADIR",  $DataPath);
	
	my @BldList=&main::BldList;
	foreach (@BldList) {
		&main::Output(
			"\n"
		);
		Generic_Define("EPOCBLD$_", "\$(EPOCBLD)\\$_");
		Generic_Define("EPOCTRG$_", "\$(EPOCTRG)\\$_");
		Generic_Define("EPOCLIB$_", "\$(EPOCLIB)\\$LibSubDir");
		Generic_Define("EPOCLINK$_", "\$(EPOCLINK)\\$LibSubDir");
		Generic_Define("EPOCSTATLINK$_", "\$(EPOCSTATLINK)\\$_");
		Generic_Define("EPOCASSPLINK$_", "\$(EPOCASSPLINK)\\$LibSubDir");
	}

	&main::Output(
		"\n",
		"# EPOC PSEUDOTARGETS\n",
		"\n"
	);

	foreach (@BldList) {
		&main::Output(
			"$_ : MAKEWORK$_ RESOURCE$_\n\n"
		);
	}

	&main::Output(	# ALL comes after DEB: because first target in makefile is the default
		"ALL :"
	);
	foreach (@BldList) {
		&main::Output(
			" $_"
		);
	}

	&main::Output(
		"\n",
		"\n",
		"CLEAN CLEANALL : CLEANBUILD CLEANRELEASE CLEANLIBRARY\n",
		"\n"
	);
	my $pseudoTarget;
	foreach $pseudoTarget ("WHAT", "RESOURCE", "CLEANBUILD", "CLEANRELEASE", 
				"MAKEWORK", "LISTING")
		{
		&main::Output(
			"\n",
			"\n",
			"$pseudoTarget $pseudoTarget","ALL :"
		);
		foreach (@BldList) {
			&main::Output(
				" $pseudoTarget$_"
			);
			}
		}
	&main::Output(
		"\n",
		"\n",
		"MAKEWORK : MAKEWORKLIBRARY\n",
		"\n"
	);

	foreach (@BldList) {
		&main::Output(
			"RESOURCE$_ "
		);
	}
	&main::Output(
		": GENERIC_RESOURCE\n",
		"\n"
	);

}

# Quote name if necessary, according to the type of Makefile

sub Generic_Quote ($) {
	my ($name)=@_;
	if ($MakefileType==1) {
		# GNU make wants backslash before each space
		$name =~ s/ /\\ /go;
	} else {
		# NMAKE prefers quotes around all filenames
		$name = "\"$name\"";
	}
	return $name;
}

# Generic file copying action, which uses built-in variables quoted appropriately
#
# GNU make variables may contain spaces, but perl.exe will be executed directly
# and so doesn't need any quotes.

sub Generic_CopyAction($) {
	my ($target) = @_;
	my $source = '$?';
	$target = '$@' if (!defined $target);
	return "perl -S ecopyfile.pl $source $target\n";
}

# Record necessary directories, for eventual emkdir.pl rules
# Also need to record related defines, to eliminate duplicates

my %DirDefines;
sub expandDefines ($) {
	my ($value)=@_;
	while ($value =~ /^(.*)\$\((\w+)\)(.*)$/) {
		$value="$1$DirDefines{$2}$3";
	}
	return $value;
}
sub Generic_Define ($$;$) {
	my ($name, $value, $trailer)=@_;
	$trailer="" if (! defined $trailer);
	&main::Output(
		"$name = $value$trailer\n"
	);
	$DirDefines{$name}=expandDefines($value);
}
sub Generic_Definition ($) {
	return $DirDefines{$_[0]};
}

my %MkDirs;
sub Generic_MkDir ($) {
	my $dir=&main::Path_Chop(&expandDefines($_[0]));
	$MkDirs{$dir}=1;
	return $dir;
}

# Accumulate MAKEWORK targets and lists of directories,
# automatically filling in the rest of the details.
#
my %MakeWork;
sub Generic_MakeWorkDir($$) {
	my ($work, $dir) = @_;
	my $workhash;
	if (defined $MakeWork{$work}) {
		$workhash=$MakeWork{$work};
	} else {
		my %newhash;
		$workhash=\%newhash;
		$MakeWork{$work}=$workhash;
	}
	$$workhash{&Generic_MkDir($dir)}=1;
}

sub Generic_MakeWorkFile($$) {
	my ($work, $file) = @_;
	my $dir=&main::Path_Split('Path',&expandDefines($file));
	&Generic_MakeWorkDir($work,$dir);
}

sub Generic_WhatCleanTargets($$$@) {
	my ($prefix, $whattarget, $cleantarget, @files)=@_;
	
	if ((scalar @files) == 0) {
		&main::Output(
			"\n",
			"\n$whattarget $cleantarget :\n",
			"\t\@rem none\n"
		);
	} else {
# emit list of releasables in batches to avoid overflowing the 2048 character 
# batch file line limit doing echo or erase...

		my $count=1;
		my $length=0;
		&main::Output(
			"\n",
			"${prefix}_RELEASEABLES$count="
		);

		my $File;
		foreach $File (sort @files) {
			my $name = &Generic_Quote($File);
			my $namelen = length($name)+3;	# for space, newline and tab
			if ($length+$namelen > 1700) {	# very conservative limit
				$count++;
				$length=0;
				&main::Output(
					"\n",
					"${prefix}_RELEASEABLES$count="
				);
			}
			&main::Output(
				" \\\n\t", $name
			);
			$length += $namelen;
		}
		&main::Output(
			"\n",
			"\n",
			"$whattarget:\n"
		);
		my $filecount=1;
		while ($filecount<=$count) {
			&main::Output(
				"\t\@echo \$(${prefix}_RELEASEABLES$filecount)\n"
			);
			$filecount++;
		}
		&main::Output(
			"\n",
			"$cleantarget:\n",
		);
		$filecount=1;
		while ($filecount<=$count) {
			&main::Output(
				"\t-\$(ERASE) \$(${prefix}_RELEASEABLES$filecount)\n"
			);
			$filecount++;
		}
	}

	&main::Output(
		"\n",
	);
}

# accumulated list of generic releasables
my %Files;	
sub Generic_End {

	&Generic_WhatCleanTargets("GENERIC","WHATGENERIC","CLEANGENERIC", keys %Files);
	
	&main::Output(
		"# Rules to create all necessary directories\n",
	);

	foreach (sort keys %MakeWork) {
		my $workhash = $MakeWork{$_};
		&main::Output(
			"\n$_ :",
		);
		foreach (sort keys %$workhash) {
			&main::Output(
				" \\\n",
				"\t", &Generic_Quote($_)
			);
		}
	}
	&main::Output(
		"\n",
		"\n"
	);

	my $dir;
	foreach $dir (sort keys %MkDirs) {
		&main::Output(
			&Generic_Quote($dir)," \\\n",
		);
	}
	&main::Output(
		":\n",
		"\tperl -S emkdir.pl \$\@\n",
		"\n"
	)
}

sub Generic_Releaseables {

	my $ResrcPath=&main::TrgPath;
	my $dir;
	my $EPOCIncPath=&main::EPOCIncPath;

	&Generic_MakeWorkDir('GENERIC_MAKEWORK',$SavedBldPath);	    # used for temp directory in epocrc.pl
			
	my $AifStructRef=&main::AifStructRef;
	my $AifRef;
	foreach $AifRef (@$AifStructRef) {
# regression hack - workaround lack of AIF directory
		$$AifRef{TrgFile}=&main::Path_Split('File',$$AifRef{Trg});  # record for later
		my $path=&main::Path_Split('Path',"$ResrcPath$$AifRef{Trg}");  
		my $file="\$(EPOCDATA)\\$ResrcPath$$AifRef{Trg}";
		if ($path eq "") {
			# no target path for the AIF file, so not a releasable
			$file="$SavedBldPath\\$$AifRef{Trg}";
		} else {
			$Files{$file}=1;
		}
		# $Files{$file}=1;
# regression hack - end
		$$AifRef{GenericTrg}=$file;	    # record for later
		&Generic_MakeWorkFile('GENERIC_MAKEWORK',$file);
	}

	my $BitMapStructRef=&main::BitMapStructRef;
	my $BitMapRef;
	foreach $BitMapRef (@$BitMapStructRef) {
		my $path=$$BitMapRef{TrgPath};
		my $file="\$(EPOCDATA)\\$path$$BitMapRef{Trg}";
		$$BitMapRef{GenericTrg}=$file;	    # record for later
		$Files{$file}=1;
		&Generic_MakeWorkFile('GENERIC_MAKEWORK',$file);
		if ($$BitMapRef{Hdr}) {
			my $mbg=&main::Path_Split('Base', $$BitMapRef{Trg});
			$mbg="\$(EPOCINC)\\$mbg.MBG";
			&Generic_MakeWorkDir('GENERIC_MAKEWORK',$EPOCIncPath);
			$Files{$mbg}=1;
		}
	}

	my $ResourceStructRef=&main::ResourceStructRef;
	my $ResourceRef;
	foreach $ResourceRef (@$ResourceStructRef) {
		my $file="\$(EPOCDATA)\\$$ResourceRef{Trg}";
		$$ResourceRef{GenericTrg}=$file;	# record for later
		$Files{$file}=1;
		&Generic_MakeWorkFile('GENERIC_MAKEWORK',$file);
		if ($$ResourceRef{Hdr}) {
			my $rsg="\$(EPOCINC)\\$$ResourceRef{BaseTrg}.RSG";
			&Generic_MakeWorkDir('GENERIC_MAKEWORK',$EPOCIncPath);
			$Files{$rsg}=1;
		}
	}

	&main::Output(
		"GENERIC_RESOURCE : GENERIC_MAKEWORK\n",
		"\n"
	);

}

sub Generic_BitMapBld {

	my $BitMapRef=&main::BitMapRef;
	my $quotedTrg=&Generic_Quote($$BitMapRef{GenericTrg});
	my $WorkPath = &main::Path_Chop(&main::Path_WorkPath); ## required for Lockit

	&main::Output(
		"# BitMap $$BitMapRef{Trg}\n",
		"\n",
		"GENERIC_RESOURCE : $quotedTrg\n",
		"\n",
		"$quotedTrg :"
	);

#	must lower-case header here since bmconv generates a header with case-sensitive enums accordingly
	my $BitMapHdr=join('', &main::EPOCIncPath, &main::Path_Split('Base', $$BitMapRef{Trg}), '.mbg');
	my $RTWBitMapHdr=&main::Path_RltToWork($BitMapHdr);
	my $TmpBitMapHdr=join('', &main::BldPath, &main::Path_Split('Base', $$BitMapRef{Trg}), '.mbg');
	my $RTWTmpBitMapHdr=&main::Path_RltToWork($TmpBitMapHdr);


	my $SrcRef;
	foreach $SrcRef (@{$$BitMapRef{Source}}) {
		%Files = &Lockit_Releasables($WorkPath, $$BitMapRef{Trg}, \%Files, basename($$SrcRef{Src}));
		&main::Output(
			" \\\n  ", &Generic_Quote($$SrcRef{Src})
		);
	}
	&main::Output(
		"\n",
		"\tperl -S epocmbm.pl -h\"$TmpBitMapHdr\"",
		"\t-o\"$$BitMapRef{GenericTrg}\"",
		"\t-l\"\\$$BitMapRef{TrgPath}:$WorkPath\"",
		"\\\n\t\t"
	);
	&main::Output(
		" -b\""
	);
	foreach $SrcRef (@{$$BitMapRef{Source}}) {
		&main::Output(
			"\\\n\t\t/$$SrcRef{ClDepth}$$SrcRef{Src}"
		);
	}


	&main::Output(
		"\" \\\n\t\t"
	);

	&main::Output(
		" -l\"\\$$BitMapRef{TrgPath}:$WorkPath\"\n"
	);

	if ($$BitMapRef{Hdr}) {
		&main::Output(
			"\tperl -S ecopyfile.pl \"$TmpBitMapHdr\" \"$BitMapHdr\"\n",
		);
	}
	&main::Output(
		"\n"
	);
}

sub Generic_ResrcBld {

	my $ResourceRef=&main::ResourceRef;
	my $WorkPath = &main::Path_Chop(&main::Path_WorkPath); # required for Lockit

	&main::Output(
		"# Resource $$ResourceRef{Trg}\n",
		"\n"
	);
	my @DepList=&main::DepList;

	&main::Output(
		"DEPEND="
	);
	foreach (@DepList) {
		&main::Output(
			" \\\n",
			"\t", &Generic_Quote($_)
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	my $BaseResrc= $$ResourceRef{BaseTrg};
	my @ChopRTWSysIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::SysIncPaths));
	my @ChopRTWUserIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::UserIncPaths));
	my $SrcPath=&main::Path_Split('Path', $$ResourceRef{Source});
	my $RTWSrcPath=&main::Path_RltToWork($SrcPath);
	my $ChopRTWSrcPath=&main::Path_Chop($RTWSrcPath);

	my $ResrcHdr=join '', &main::EPOCIncPath(), $BaseResrc, '.RSG';
	my $RTWResrcHdr=&main::Path_RltToWork($ResrcHdr);
	

	my $EPOCDataDir = &main::Path_Chop($$ResourceRef{TrgPath});
	
	my $HeaderOption = "";
	my $HeaderCopyCmd = "";
	if ($$ResourceRef{Hdr}) {
		$HeaderOption = " -h\"$SavedBldPath\\$BaseResrc.rsg\"";
		$HeaderCopyCmd = "\tperl -S ecopyfile.pl \"$SavedBldPath\\$BaseResrc.rsg\" \"$ResrcHdr\"\n";
	}
	
	%Files = &Lockit_Releasables($WorkPath,$$ResourceRef{Source}, \%Files, "");

	my $quotedTrg=&Generic_Quote($$ResourceRef{GenericTrg});
	&main::Output(
		"GENERIC_RESOURCE : $quotedTrg\n",
		"\n",
		"$quotedTrg : ", &Generic_Quote($$ResourceRef{Source}), " \$(DEPEND)\n",
		"\tperl -S epocrc.pl -I \"$ChopRTWSrcPath\""
	);
	foreach (@ChopRTWUserIncPaths) {
		&main::Output(
			" -I \"$_\""
		);
	}
	&main::Output(
		" -I-"
	);
	foreach (@ChopRTWSysIncPaths) {
		&main::Output(
			" -I \"$_\""
		);
	}
	&main::Output(
		" -DLANGUAGE_$$ResourceRef{Lang} -u \"$$ResourceRef{Source}\" ",
		"-o\$\@ $HeaderOption -t\"$SavedBldPath\"  -l\"$EPOCDataDir:$WorkPath\"\n",
		$HeaderCopyCmd,
		"\n"
	);
}

sub Generic_AifBld {

	my $AifRef=&main::AifRef;
	my $ResrcPath=&main::TrgPath;

	&main::Output(
		"# Aif $$AifRef{Trg}\n",
		"\n"
	);
	my @DepList=&main::DepList;

	&main::Output(
		"DEPEND="
	);
	foreach (@DepList) {
		&main::Output(
			" \\\n",
			"\t", &Generic_Quote($_)
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	my @ChopRTWSysIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::SysIncPaths));
	my @ChopRTWUserIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::UserIncPaths));
	my $BaseResrc=&main::Path_Split('Base',$$AifRef{Source});

	my $WorkPath = &main::Path_Chop(&main::Path_WorkPath); # required for Lockit
	my $quotedTrg=&Generic_Quote($$AifRef{GenericTrg});
	&main::Output(
		"GENERIC_RESOURCE : $quotedTrg\n",
		"\n",
		"$quotedTrg : ", &Generic_Quote("$$AifRef{Source}"), " \$(DEPEND)"
	);

	%Files = &Lockit_Releasables($WorkPath, $$AifRef{TrgFile}, \%Files, "");

	my $bitmapArg = "";
	if ($$AifRef{BitMaps}) { # bitmaps aren't essential
		$bitmapArg = "\\\n\t\t-b\"";
		foreach my $BitMapRef (@{$$AifRef{BitMaps}}) {
			my $BitMap = &main::Path_Split('File', $$BitMapRef{Src});
			%Files = &Lockit_Releasables($WorkPath, $$AifRef{TrgFile}, \%Files, $BitMap);
			&main::Output(
				" ", &Generic_Quote("$$BitMapRef{Src}")
			);
			$bitmapArg .= "\\\n\t\t/$$BitMapRef{ClDepth}$$BitMapRef{Src}";
		}
		$bitmapArg .= "\" ";
	}
	&main::Output(
		"\n",
		"\tperl -S epocaif.pl -o\$\@ ",
		"\"$$AifRef{Source}\" ",
		"\\\n\t\t",
		"-t\"$SavedBldPath\" ",
		" -l\"\$(TRGDIR):$WorkPath\"",
		$bitmapArg,
		"\\\n\t\t"
	);
	foreach (@ChopRTWUserIncPaths) {
		&main::Output(
			" -I \"$_\""
		);
	}
	&main::Output(
		" -I-"
	);
	foreach (@ChopRTWSysIncPaths) {
		&main::Output(
			" -I \"$_\""
		);
	}
	&main::Output(
		"\n",
		"\n"
	);
}

1;

