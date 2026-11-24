# CL_GCCXML.PM
#
# Copyright (c) 2004 Symbian Ltd.  All rights reserved.
#

package Cl_gccxml;

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	PMHelp_Mmp
	PMPlatProcessMmp
	PMStartBldList
	PMBld
	PMStartSrcList
	PMStartSrc
	PMSrcDepend
	PMSrcBldDepend
	PMEndSrcBld
	PMEndSrc
	PMEndSrcList
);

use cl_generic;
use File::Path;

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

my $epocroot = $ENV{EPOCROOT};
$epocroot=~ s-\\$--;            # chop trailing \\
my $Makecmd;
my $DefFile = &main::DefFile;
sub PMStartBldList($) {
	($Makecmd) = @_;
	my $BasicTrgType=&main::BasicTrgType;
	my @BldList=&main::BldList;
	my @ChopRTWSysIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::SysIncPaths));
	my @ChopRTWUserIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::UserIncPaths));
	my $RelPath="$epocroot\\EPOC32\\RELEASE";
	my $RPath = &main::Path_RltToWork($RelPath);
	my @MacroList=&main::MacroList();
	my $VariantFile=&main::VariantFile();
	my $Trg=&main::Trg;

	&Generic_Header(1,$Makecmd);	# define standard things using relative paths

	&main::Output(
		"GXPTRGUDEB = $RPath\\GCCXML\\UDEB\n",
		"GXPTRGUREL = $RPath\\GCCXML\\UREL\n\n",
		"DEFFILE = $DefFile\n\n"	
	);

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
	if($VariantFile){
	    #gcc needs a relative path
	    $VariantFile = &main::Path_RltToWork($VariantFile);
	    &main::Output("\\\n  -include \"$VariantFile\"");
	}
    
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
		"GCCFLAGS=\\\n",
		"\t\t -nostdinc -Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas -UWIN32 -fshort-wchar -quiet -w \n",  # -fsyntax-only
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
			"GCC$_ = gccxml_cc1plus.exe"
		);
		if (/REL$/o) {
			&main::Output(
				' -fomit-frame-pointer '
			);
		}
		elsif (/DEB$/o) {
			&main::Output(
				' -g'
			);
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
			" -D__GCCXML__"
		);

		&main::Output(
			" \$(GCCDEFS)\n"
		);
	}
	&main::Output(
		"\n",
		"\n"
	);

	&main::Output(
			"LIBRARY:\n",
			"\t\@echo Nothing to do\n"
	);

	&main::Output(
		"RESOURCEUREL:\n",
		"\t\@echo Nothing to do\n"
	);

	&main::Output(
		"RESOURCEUDEB:\n",
		"\t\@echo Nothing to do\n\n\n"
	);	

	foreach (@BldList) {
		&main::Output(
			"$_ :"
		);

		if ($BasicTrgType !~ /IMPLIB/io) {
			my $TrgBase = &main::Path_Split('base',$Trg);           
			&main::Output (
			" \\\n\t",
			&Generic_Quote("\$(GXPTRG$_)\\$TrgBase.gxp")
			);
		}

		&main::Output(
			"\n",
			"\n"
		);
	}

}

# DumpToFile
sub DumpMMPToFile
{
	my $BldPath=&main::BldPath;
	my $Target = &main::Trg; 
	my $TargetBase = &main::Path_Split('Base', $Target);
	my $Gxpurel="$epocroot\\epoc32\\release\\gccxml\\urel";
	my $Gxpudeb="$epocroot\\epoc32\\release\\gccxml\\udeb";
	unless (-d $BldPath) {
		mkpath([$BldPath]);
	}
	unless (-d $Gxpurel) {
		mkpath([$Gxpurel]);
	}
	unless (-d $Gxpudeb) {
		mkpath([$Gxpudeb]);
	}
	$BldPath = (&main::Path_StepDirs($BldPath))[-2];
	my $FileName = $BldPath.$TargetBase.".mmp.xml";
	open FILE,"> $FileName" or die "Cannot open mmp info dump file $FileName: $!";
	print FILE "<?xml version=\"1.0\"?>\n<mmpInfo>\n"; 
	my $Path = &main::RelPath();
	my $MmpFile = &main::MmpFile();  
	my $TrgType = &main::TrgType(); 
	my $TrgPath = &main::TrgPath(); 
	print FILE "\t<mmp path=\"$MmpFile\"/>\n"; 
	print FILE "\t<target name=\"$Target\" type=\"$TrgType\" ";
    
	if(not $TrgPath eq '') 
	{
		print FILE "path=\"$TrgPath\""; 
	}
	print FILE "/>\n"; 
	my $WorkPath = &main::Path_WorkPath();
	print FILE "\t<cwd path=\"$WorkPath\"/>\n";
    
	my $ABI = &main::ABI; 
	print FILE "\t<abi type=\"$ABI\"/>\n"; 
	my $LinkAs = &main::LinkAs;
	print FILE "\t<linkAs name=\"$LinkAs\"/>\n"; 
     
	# Uids
	my @UidList=&main::UidList;
	my $count = 0;
	print FILE "\t<uids";
	foreach my $uid(@UidList)
	{
		print FILE " u$count=\"$uid\"" ;
		$count++; 
	}
	print FILE "/>\n";
        
	# DefFile
	print FILE "\t<defFile path=\"$DefFile\" type=\"GCC\"/>\n"; 
	print FILE "\t<defFile path=\"\" type=\"EABI\"/>\n"; 
        
	# Handle All types of libraries
	my $FirstLib = &main::FirstLib; 
	my @LibList = &main::LibList;
	my @ASSPLibList = &main::ASSPLibList;
	my @StatLibList = &main::StatLibList;;    
	print FILE "\t<libs>\n"; 
    
	#first
	print FILE "\t\t<lib name=\"$FirstLib\" type=\"First\"/>\n"; 
    
	#  normal
	foreach my $lib (@LibList)
	{
		print FILE "\t\t<lib name=\"$lib\"/>\n"; 
	}
	# ASSP Specific
	foreach my $lib (@ASSPLibList)
	{ 
		print FILE "\t\t<lib name=\"$lib\" type=\"ASSP\"/>\n";
	}
    
	# Static Libraries
	foreach my $lib (@StatLibList)
	{ 
		print FILE "\t\t<lib name=\"$lib\" type=\"Static\"/>\n";
	}
	print FILE "\t</libs>\n";
    
	close FILE;
}

sub PMBld {
	my @BaseSrcList=&main::BaseSrcList;
	my $BaseTrg=&main::BaseTrg;
	my $Bld=&main::Bld;
	my $ChopBldPath=&main::Path_Chop(&main::BldPath);
	my @CompatibleABIs=&main::CompatibleABIs;
	my $EPOCIncPath=&main::EPOCIncPath;
	my $BasicTrgType=&main::BasicTrgType;
	my $ChopRelPath=&main::Path_Chop(&main::RelPath);
	my $RelPath=&main::RelPath;
	my $Trg=&main::Trg;
	my $TrgType=&main::TrgType;
	my @UidList=&main::UidList;

	DumpMMPToFile();

	# REAL TARGETS
	#-------------
	&main::Output(
		"# REAL TARGET - BUILD VARIANT $Bld\n",
		"\n"
	);

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
	my @releaseables;
	&Generic_WhatCleanTargets($Bld, "WHAT$Bld", "CLEANRELEASE$Bld", @releaseables);

	&Generic_MakeWorkDir("MAKEWORK$Bld",$ChopBldPath);
	&Generic_MakeWorkDir("MAKEWORK$Bld",$ChopRelPath);

	&main::Output(
		"\n",
		"\n"
	);
	
	# XML Stuff
	&main::Output(
				&Generic_Quote("\$(GXPTRG$Bld)\\$BaseTrg.gxp"), " : ",
				&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseTrg.gxp"),
				"\n\tcopy \$(EPOCBLD$Bld)\\$BaseTrg.gxp \$@"
	); 

	&main::Output(
		"\n",
		"\n"
	);

	# TARGET *.GXP
	#-------------
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
			my $BaseSrc = &main::Path_Split('Base', $_);
			my $Ext = &main::Path_Split('Ext', $_);
			&main::Output(
				" \\\n\t", &Generic_Quote("\$(EPOCBLD$Bld)\\$_.xml")
			);
			$counter1++;
		}
 		&main::Output(
			" \\\n\t\$(EPOCBLD)\\$BaseTrg.mmp.xml",
			"\n",
			"\n",
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseTrg.gxp"), " : ", @objvarlist,"\n",
			"\tif exist \"\$\@\" del \"\$\@\"\n"
 		);
		foreach (@objvarlist) {
			&main::Output(
					"\tzip -j \$\@$_\n"
			);
		}
		&main::Output(
			"\tif exist \$(DEFFILE) zip -j \$\@ \$(DEFFILE)\n",
			"\n\n"
		);
	} else {
		# shorter lists remain unchanged
		#
		&main::Output(
			"OBJECTS$Bld="
		);
		&main::Output("\$(EPOCBLD)\\$BaseTrg.mmp.xml");
	
		foreach (@BaseSrcList) {
			&main::Output(
				" \\\n\t", &Generic_Quote("\$(EPOCBLD$Bld)\\$_.xml")
			);
		}
		&main::Output(
			"\n",
			"\n"
		);

		&main::Output(
			&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseTrg.gxp"), " : \$(OBJECTS$Bld)\n",
			"\tif exist \"\$\@\" del \"\$\@\"\n",
			"\tzip -j \$\@ \$^ \$(DEFFILE) \n",
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
			&Generic_Quote("\$(EPOCBLD$_)\\$BaseSrc.xml"), " \\\n",
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
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.xml"), " :",
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

my %sources;

sub PMEndSrcBld {
	my $ABI=&main::ABI;
	my $BaseSrc=&main::BaseSrc;
	my $Bld=&main::Bld;
	my $Src=ucfirst lc &main::Src;
	my $SrcPath=&main::SrcPath;
	my $RTWSrcPath=&main::Path_Chop(&main::Path_RltToWork($SrcPath));

	$sources{$SrcPath}{$Src}{$Bld}=1;

	# Use GCC trick to get assembler source files preprocessed with CPP
	$Src =~ s/\.s$/.S/i;

	&main::Output(
		&Generic_Quote("\$(EPOCBLD$Bld)\\$BaseSrc.xml"), " : ",
		&Generic_Quote("$SrcPath$Src"), "\n",
		"\t\$(GCC$Bld) -I \"$RTWSrcPath\" \$(INCDIR) -fxml=\$\@ \"$RTWSrcPath\\$Src\"\n",
		"\n",
	);
}

sub PMEndSrc {
	&main::Output(
		"\n",
		"\n"
	);
}

sub PMEndSrcList {
my $BldPath=&main::BldPath;
        my $Target = &main::Trg; 
        my $TargetBase = &main::Path_Split('Base', $Target);
        my $FileName = $BldPath.$TargetBase.".mmp.xml";
		open FILE,">> $FileName" or die "Cannot open mmp info dump file $FileName: $!";
		my $path;
		foreach $path (keys %sources)
		{
			my %thing =  %{$sources{$path}}; # {"UREL"}; 
			my $file;
			foreach $file (keys %thing)
			{
				if( defined $thing{$file}{"UREL"})
				{
					if( defined  $thing{$file}{"UDEB"} )
					{
						print FILE "\t<sourceFile name=\"$file\" path=\"$path\"/>\n";
					}
					else
					{
						print FILE "\t<sourceFile name=\"$file\" path=\"$path\" type=\"UREL\"/>\n";
					}
				}
				else
				{
					if(defined $thing{$file}{"UDEB"})
					{
						print FILE "\t<sourceFile name=\"$file\" path=\"$path\" type=\"UDEB\"/>\n";
					}
					else
					{
						die "Should Never Get HERE!";
					}
				}
			}
		}
		print FILE "</mmpInfo>\n\n";
		close FILE; 

	# Deal with accumulated MAKEDIRS etc.
	&Generic_End;
}

1;
