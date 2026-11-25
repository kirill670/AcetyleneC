# IDE_CW.PM
#
# Copyright (c) 2001-2003 Symbian Ltd.  All rights reserved.
#


# Makmake-module for creating XML files which can be imported as CodeWarrior IDE projects

package Ide_cw;

# declare variables global for module
my $BaseAddress="";
my @CppCall;
my %IdeBlds=();
my %PrjHdrs=();
my @Win32LibList=();
my $Win32Resrc;
my $CopyForStaticLinkage;

my $PrefFilePath="";
my @KnownRoots=();

require Exporter;
@ISA=qw(Exporter);

@EXPORT=qw(
	PMHelp_Mmp

	PMCheckPlatformL

	PMPlatProcessMmp

	PMStartBldList
		PMBld
			PMResrcBld
	PMEndSrcList
);


sub PMHelp_Mmp {
# provide the help text for START <windows platforms> END blocks

	print
		"BASEADDRESS    [base address for dll loading]\n",
		"WIN32_LIBRARY  [win32 libraries]\n",
		"WIN32_RESOURCE  [win32 resource]\n",
		"COPY_FOR_STATIC_LINKAGE   // copy dll from emulated Z drive\n",
	;
}

use FindBin;
use lib $FindBin::Bin."\\perllib";

#use the DOM xml module
use XML::DOM;

my $xmlParser;
my $xmlDoc;

my $xmlLinkOrder;	# for accumulating the link order
my $xmlFileList;	# for accumulating the file list
my $xmlSourceGroup;	# for accumulating the source 
my $xmlLibGroup;	# for accumulating the library

my $MmpFile;
my $CW_version;
my $CW_libpath;

sub PMCheckPlatformL {

	# check version of CodeWarrior for Symbian OS
	
	my $template;
	if (defined($ENV{MWCSym2Includes})) {
		$CW_version = 2;
		$CW_libpath = 'Symbian_Support';
		$template = "CW_project_template_v2.xml";
		# print "Detected CodeWarrior for Symbian OS, OEM version 2\n";
	}
	if (!defined($CW_version) && defined($ENV{MWSym2Libraries})) {
		$CW_version = 2;
		$CW_libpath = 'Other_Metrowerks_Tools\Symbian Libs';
		$template = "CW_project_template_v2.xml";
		# print "Detected CodeWarrior for Symbian OS, Pro version 2.0\n";
	}
	if (!defined($CW_version) && defined($ENV{CWFolder})) {
		$CW_version = 1;
		$template = "CW_project_template.xml";
		# print "Assuming CodeWarrior for Symbian OS, Pro version 1.0\n";
	}
	if (!defined($CW_version)) {
		die "ERROR: Unable to identify a valid CodeWarrior for Symbian OS installation\n";
	}

	$xmlParser = new XML::DOM::Parser; 
	$xmlDoc = $xmlParser->parsefile ($FindBin::Bin."\\$template");
}

sub PMPlatProcessMmp (@) {
	my @PlatTxt=@_;

# process the START <windows platforms> END blocks

	my $BaseTrg=&main::BaseTrg;
	my $BasicTrgType=&main::BasicTrgType;
	my $MakeFilePath=&main::MakeFilePath;
	$MmpFile=&main::MmpFile;

	# set up START WINS ... END block module variables
	my @MmpWarn=();
	my $Line;
	LINE: foreach $Line (@PlatTxt) {
		my $LineInfo=shift @$Line;
		$_=shift @$Line;
		if (/^BASEADDRESS$/o) {
			if (@$Line) {
				$BaseAddress=shift @$Line;
				$BaseAddress=~s/X/x/o;
				next LINE;
			}
			push @MmpWarn, "$LineInfo : No base address specified for keyword BASEADDRESS\n";
			next LINE;
		}
		if (/^WIN32_LIBRARY$/o) {
			if (push @Win32LibList, @$Line) {
				next LINE;
			}
			push @MmpWarn, "$LineInfo : No libraries specified for keyword WIN32_LIBRARY\n";
			next LINE;
		}
		if (/^WIN32_RESOURCE$/o) {
			if (@$Line) {
				$Win32Resrc=shift @$Line;
				$Win32Resrc=&main::Path_MakeAbs($MmpFile, $Win32Resrc);
				next LINE;
			}
			push @MmpWarn, "$LineInfo : No resource specified for keyword WIN32_RESOURCE\n";
			next LINE;
		}
		if (/^COPY_FOR_STATIC_LINKAGE$/o) {
			if ($BasicTrgType!~/^DLL$/o) {
				push @MmpWarn, "$LineInfo : COPY_FOR_STATIC_LINKAGE only applies to DLLs\n";
				next LINE;
			}
			if (&main::TrgPath eq "") {
				push @MmpWarn, "$LineInfo : COPY_FOR_STATIC_LINKAGE requires TARGETPATH\n";
				next LINE;
			}
			$CopyForStaticLinkage=1;
			next LINE;
		}
		push @MmpWarn, "$LineInfo : Unrecognised Keyword \"$_\"\n";
	}

	undef $Line;
	if (@MmpWarn) {
		warn
			"\nMMPFILE \"",$MmpFile,"\"\n",
			"START .. END BLOCK WARNINGS(S)\n",
			@MmpWarn,
			"\n"
		;
	}
	undef @MmpWarn;

	# create the prefs file
	# if Win32 Libraries required - set the Windows standard macros
	if (@Win32LibList  || $Win32Resrc ) {
		&main::AddPlatMacros('WIN32','_WINDOWS');
	}

	# Set up the list of known roots

	my $epocroot=&main::Path_Drive . &main::EPOCPath;

	my $mmproot = &main::Path_Drive . &main::Path_Split('Path',$MmpFile);
	my $mmprootname = "MMPDir";
	my $mmpisglobal = 0;

	if (defined $ENV{CW_ROOT_NAME})
		{
		# generate KnownRoots suitable for the IDE MMP importer
		# This has a global source tree for EPOCROOT, and puts the
		# project next to the MMP file

		addKnownRoot($ENV{CW_ROOT_NAME}, 1, $epocroot, "EPOC32\\");
		$mmprootname = "Project";
		$mmpisglobal = 1;
		}
	else
		{
		# generate KnownRoots suitable for command-line generated XML files
		# We will add a user source tree for MMPDir and EPOCROOT, but can't use
		# EPOCROOT for the OutputDirectory

		addKnownRoot("EPOCROOT", 0, $epocroot, "EPOC32\\");
		}
	addKnownRoot($mmprootname, $mmpisglobal, $mmproot, "");

	# Allow for MMP files in component subdirectories by matching multiple levels
	# up to get {MMPDir}..\whatever paths. Stop one level down from the root,
	# since "everything on this drive" seems a bit extreme
	#
	my $tmppath = $mmproot;
	my $dotdots = '';
	while ($tmppath =~ /^(.:.+\\)[^\\]+\\$/i)
		{
		$tmppath = $1;
		$dotdots .= "..\\";
		addKnownRoot($mmprootname, $mmpisglobal, $tmppath, $dotdots);
		}
}

sub findTarget($$$) {
	my ($name,$platbld,$abibld) = @_;

	my @targets = $xmlDoc->getElementsByTagName("TARGET",1); 
	foreach my $target (@targets)
		{
		my $element = $target->getElementsByTagName("NAME",0)->item(0);
		$element = $element->getFirstChild;
		if ($element->getData() =~ /$abibld$/) 
			{
			my $newtarget=$target->cloneNode(1);
			$target->getParentNode()->appendChild($newtarget);
			$element = $newtarget->getElementsByTagName("NAME",0)->item(0);
			$element = $element->getFirstChild;
			$element->setData("$platbld");
			# remember name as an attribute: this is removed before
			# writing out the project.
			$newtarget->setAttribute("NAME", "$platbld");	
			return $newtarget;
			}
		}
	return undef;
}

sub newList($$$) {
	my ($target, $tag, $replace) = @_;

	my $newlist = new XML::DOM::Element($xmlDoc,$tag);
	if ($replace==1)
		{
		my $elements = $target->getElementsByTagName($tag,0);
		my $element = $elements->item(0);
		$target->replaceChild($newlist, $element);
		}
	else
		{
		$target->appendChild($newlist);
		}
	return $newlist;
}

sub changeValue($$) {
	my ($setting, $replacement) = @_;
	my $value = $setting->getElementsByTagName("VALUE",0)->item(0);
	if (defined $value)
		{
		if ($value->hasChildNodes)
			{
			$value->getFirstChild->setData($replacement);
			}
		else
			{
			$value->addText($replacement);
			}
		}
}

sub textSetting($$$$) {
	my ($element,$name,$value,$insertionpoint)=@_;

	my $setting = new XML::DOM::Element($xmlDoc,"SETTING");
	&textElement($setting, "NAME", $name);
	&textElement($setting, "VALUE", $value);
	$element->insertBefore($setting, $insertionpoint);
	$element->addText("\n");
}

sub addKnownRoot($$$$) {
	my ($rootname, $global, $rootpath, $pathprefix) = @_;
	$rootpath=&main::Path_Chop($rootpath);
	push @KnownRoots, [$rootname, $global, quotemeta($rootpath), $pathprefix];
}

sub addRootedPath($$$) {
	my ($setting,$needglobal,$path) = @_;
	my $root = "Absolute";

	if ($path =~ /^\\/)
		{
		$path = &main::Path_Drive . $path;	# ensure it has a drive letter
		}
	foreach (@KnownRoots)
		{
		my ($rootname, $global, $rootpath, $pathprefix) = @{$_};
		next if ($needglobal && !$global);
		if ($path =~ /^$rootpath\\/i)
			{
			$path =~ s/^$rootpath\\/$pathprefix/i;
			$root = $rootname;
			last;
			}
		}
	$path=&main::Path_Chop($path);
	if ($root eq "Absolute" && $path =~ /^(.:)$/)
		{
		# M:\ or M:\sub\dir
		$path .= "\\";
		}

	&textSetting($setting, "Path", $path);
	&textSetting($setting, "PathFormat", "Windows");
	&textSetting($setting, "PathRoot", $root);
}

sub changePathSetting($$$) {
	my ($setting,$global,$value) = @_;

	my @oldstuff = $setting->getElementsByTagName("SETTING",0);
	foreach my $old (@oldstuff)
		{
		&removeNode($old);
		}

	&addRootedPath($setting,$global,$value);
}

sub addSourceTrees($) {
	my ($node) = @_;

	my $element = $node->getElementsByTagName("VALUE",0)->item(0);
	&removeNode($element) if (defined $element);

	if (defined $ENV{CW_ROOT_NAME})
		{
		return;	# paths were converted to be relative to global source trees
		}

	my $sourcepath = new XML::DOM::Element($xmlDoc,"SETTING");
	$sourcepath->addText("\n");
	&textSetting($sourcepath, "Name", "EPOCROOT");
	&textSetting($sourcepath, "Kind", "AbsolutePath");

	my $pathdata = new XML::DOM::Element($xmlDoc,"SETTING");
	&textElement($pathdata, "NAME", "Path"); 
	$pathdata->addText("\n");

	my $epocroot=&main::EPOCPath;
	$epocroot =~ s/\\EPOC32\\$/\\/i;

	&addRootedPath($pathdata, 1, $epocroot);

	$sourcepath->appendChild($pathdata);
	$node->appendChild($sourcepath);

	my $mmproot = &main::Path_Split('Path',$MmpFile);
	my $sourcepath2 = new XML::DOM::Element($xmlDoc,"SETTING");
	$sourcepath2->addText("\n");
	&textSetting($sourcepath2, "Name", "MMPDir");
	&textSetting($sourcepath2, "Kind", "AbsolutePath");

	my $pathdata2 = new XML::DOM::Element($xmlDoc,"SETTING");
	&textElement($pathdata2, "NAME", "Path"); 
	$pathdata2->addText("\n");
	&addRootedPath($pathdata2, 1, $mmproot);

	$sourcepath2->appendChild($pathdata2);
	$node->appendChild($sourcepath2);

}

sub addUserSearchPaths($) {
	my ($node) = @_;

	my @elements = $node->getElementsByTagName("SETTING",0);
	foreach (@elements)
		{
		&removeNode($_);
		}

	# Sort out the access paths for include files and libraries: note that
	# they must be in the right order, with include files first, followed
	# by static libraries and finally the DLL import libraries.

	my $ASSPLinkPath;
	$ASSPLinkPath = &main::ASSPLinkPath if (&main::ASSPLibList);

	my %ordereddirs;
	my @ordereddirlist=();
	foreach my $dir (&main::UserIncPaths, &main::SysIncPaths, &main::StatLinkPath, $ASSPLinkPath, &main::LinkPath)
		{
		next if (!defined $dir);
		$dir = &main::Path_Chop($dir)."\\";
		my $key = uc $dir;
		if (! defined($ordereddirs{$key}))
			{
			$ordereddirs{$key}=1;
			push @ordereddirlist, $dir;
			}
		}

	# now add the directories used to find source files
	
	my %dirs;
	my %srcHash = %{&main::SrcHash};
	foreach my $key (keys %srcHash)
		{
		foreach my $file (@{$srcHash{$key}})
			{
			my $path = &main::Path_Split('Path',"$key$file");
			$dirs{$path}=1;
			}
		}
	my $DefFile = &main::DefFile;
	if ($DefFile)
		{
		$DefFile = &main::Path_Split('Path',$DefFile);
		$dirs{$DefFile}=1;
		}
	$dirs{$PrefFilePath}=1;

	# Now emit all of the access paths, putting the source related ones
	# after the include and library ones and avoiding duplicates.

	foreach my $srcdir (sort keys %dirs)
		{
		if (!defined($ordereddirs{uc $srcdir}))
			{
			push @ordereddirlist, $srcdir;
			}
		}
		
	foreach my $srcdir (@ordereddirlist)
		{
		my $accesspath = new XML::DOM::Element($xmlDoc,"SETTING");
		$accesspath->addText("\n");
		my $pathdata = new XML::DOM::Element($xmlDoc,"SETTING");
		&textElement($pathdata, "NAME", "SearchPath"); 
		$pathdata->addText("\n");
		&addRootedPath($pathdata, 0, $srcdir);

		$accesspath->appendChild($pathdata);
		&textSetting($accesspath, "Recursive", "false");
		&textSetting($accesspath, "FrameworkPath", "false");
		&textSetting($accesspath, "HostFlags", "All");
		$node->appendChild($accesspath);
		}
}

sub addSystemSearchPaths($) {
	my ($node) = @_;

	my @elements = $node->getElementsByTagName("SETTING",0);
	foreach (@elements)
		{
		&removeNode($_);
		}

	my $accesspath = new XML::DOM::Element($xmlDoc,"SETTING");
	$accesspath->addText("\n");
	my $pathdata = new XML::DOM::Element($xmlDoc,"SETTING");
	&textElement($pathdata, "NAME", "SearchPath"); 
	$pathdata->addText("\n");
	&textSetting($pathdata, "Path", $CW_libpath);
	&textSetting($pathdata, "PathFormat", "Windows");
	&textSetting($pathdata, "PathRoot", "CodeWarrior");

	$accesspath->appendChild($pathdata);
	&textSetting($accesspath, "Recursive", "true");
	&textSetting($accesspath, "FrameworkPath", "false");
	&textSetting($accesspath, "HostFlags", "All");
	$node->appendChild($accesspath);
}

sub addDownloadFileList($) {
	my ($node, @DownloadList) = @_;
	
	my @elements = $node->getElementsByTagName("SETTING",0);
	foreach (@elements)
		{
		&removeNode($_);
		}

	my $epocdata = &main::EPOCPath . "data\\";
	foreach my $srcfile (@DownloadList)
		{
		my $targetpath = $srcfile;
		$targetpath =~ s/^Z\\/C:\\/i;
		
		my $download = new XML::DOM::Element($xmlDoc,"SETTING");
		$download->addText("\n");
		my $pathdata = new XML::DOM::Element($xmlDoc,"SETTING");
		&textElement($pathdata, "NAME", "HostFilePath"); 
		$pathdata->addText("\n");
		&addRootedPath($pathdata, 0, "$epocdata$srcfile");

		$download->appendChild($pathdata);
		&textSetting($download, "TargetFilePath", $targetpath);
		$node->appendChild($download);
		}
	}
	
sub PMBld() {

	my %changedsettings;

	my $ABI=&main::ABI;
	my $Bld=&main::Bld;
	my $BaseName=&main::BaseMak;
	my @SrcList=&main::SrcList;
	my $BaseTrg=&main::BaseTrg;
	my @BldList=&main::BldList;
	my $DefFile=&main::DefFile;
	my $FirstLib=&main::FirstLib;
	my $BasicTrgType=&main::BasicTrgType;
	my @LibList;
	my @StatLibList=&main::StatLibList;
	my @ASSPLibList = &main::ASSPLibList;
	my $Trg=&main::Trg;
	my $TrgPath=&main::TrgPath;
	my $TrgType=&main::TrgType;
	my $Plat=&main::Plat;
	my $epocroot=&main::Path_Drive . &main::EPOCPath;

	if ($Bld =~ /DEB/) {
		@LibList=&main::DebugLibList;
	} else {
		@LibList=&main::LibList;
	}

	my $xmlTarget = findTarget($BaseName, "$Plat $Bld", "$ABI $Bld");
	return if (!defined($xmlTarget));
	my $targetname = $xmlTarget->getAttribute("NAME");

	$xmlFileList = newList($xmlTarget,"FILELIST",1);
	$xmlFileList->addText("\n");

	$xmlLinkOrder = newList($xmlTarget,"LINKORDER",1);
	$xmlLinkOrder->addText("\n");

	# Create two temporary sublists, which will be
	# removed during finaliseProject

	$xmlSourceGroup = newList($xmlTarget,"SOURCEGROUP",0);
	$xmlSourceGroup->setAttribute("TARGET", $targetname);
	$xmlSourceGroup->addText("\n");

	$xmlLibGroup = newList($xmlTarget,"LIBGROUP",0);
	$xmlLibGroup->setAttribute("TARGET", $targetname);
	$xmlLibGroup->setAttribute("PLAT", $Plat);
	$xmlLibGroup->addText("\n");

	my $debug="";
	$debug="Debug" if ($Bld =~ /DEB$/);

	my @RuntimeLibs = ();	# add platform-specific runtime libraries here
	if (&main::PlatCompiler eq "GCC32")
		{
		if ($BasicTrgType=~/^DLL$/o) 
			{ # Add the DLL stub library
			push @RuntimeLibs, "EDLLSTUB.LIB";
			}
		if ($BasicTrgType=~/^(DLL|EXE)/o) 
			{ # Add the GCC helper fns
			push @RuntimeLibs, "EGCC.LIB";
			}
		}

	# Create the prefs file

	my $preffile = &main::Path_Split('Base',$MmpFile).".pref";
	
	if ($PrefFilePath eq "")
		{
		my @UidList=&main::UidList;
		my $PrefsText=join(
				"\n",
				"TARGET      $Trg",
				"TARGETTYPE  $TrgType",
				"UID         $UidList[1] $UidList[2]"
			);
		$PrefsText .= "\nBASEADDRESS $BaseAddress" if ($BaseAddress ne "");
		$PrefsText .= "\nEXPORTUNFROZEN" if (&main::ExportUnfrozen);
		$PrefsText .= "\nEPOCALLOWDLLDATA" if (&main::AllowDllData);
		$PrefsText .= "\nEPOCCALLDLLENTRYPOINTS" if (&main::CallDllEntryPoints);
		$PrefsText .= "\nEPOCDATALINKADDRESS ".&main::DataLinkAddress if (&main::DataLinkAddress);
		$PrefsText .= "\nEPOCFIXEDPROCESS" if (&main::FixedProcess);
		if (&main::HeapSize) 
			{
			my %HeapSize=&main::HeapSize;
			$PrefsText .= "\nEPOCHEAPSIZE $HeapSize{Min} $HeapSize{Max}";
			}
		$PrefsText .= "\nEPOCPROCESSPRIORITY ".&main::ProcessPriority if (&main::ProcessPriority);
		$PrefsText .= "\nEPOCSTACKSIZE ".&main::StackSize if (&main::StackSize);
		$PrefsText .= "\nLINKAS ".&main::LinkAs if (&main::LinkAs ne $Trg);

		$PrefFilePath = &main::MakeFilePath;
		&main::CreateExtraFile("${PrefFilePath}$preffile", "$PrefsText\n");
		}
		
	addFile($preffile, "Text", $debug, "");

	if (-e $DefFile)
		{
		addFile(&main::Path_Split('File',$DefFile), "Text", "", &main::DefFileType."\\");
		}

	# Add resources: rsc files, mbm files and aif files

	my $mmpdir = &main::Path_Split('Path',$MmpFile);
	$changedsettings{"SymbianResourcesMMPFileLocation"} = "{0}$mmpdir";
	my $ResourcesText="";
	my @ResourceDownloadList=();
	
	# --- MBM files
	
	my $BitMapStructRef = &main::BitMapStructRef();
	my $BitMapRef;
	
	foreach my $BitMapRef (@$BitMapStructRef) {
		my $trgfile = $$BitMapRef{Trg};
# hack - only use colour resource files
		next if ($trgfile =~ /\.MBW$/i);	# ignore greyscale MBM files
		$trgfile =~ s/\.MCL$/.MBM/;			# convert MCL to MBM for immediate use
# hack - end
		my $entry = "  <mbm targetfile = \"$trgfile\"";
		$entry .= " targetpath = \"".&main::Path_Chop($$BitMapRef{TrgPath})."\"";
		push @ResourceDownloadList, $$BitMapRef{TrgPath}.$trgfile;
		if (defined $$BitMapRef{Hdr})
			{
			$entry .= " header = \"true\"";
			}
		else
			{
			$entry .= " header = \"false\"";
			}
		$entry .= ">\n";
		foreach my $SrcRef (@{$$BitMapRef{Source}}) {
			$entry .= "    <bmp bpp = \"$$SrcRef{ClDepth}\"";
			my $bmpfile = &main::Path_Split('File',$$SrcRef{Src});
			my $bmppath = &main::Path_Split('Path',$$SrcRef{Src});
			my $sourcepath = &main::Path_Chop(&main::Path_MakeRltToBase($mmpdir,$bmppath));
			$entry .= " sourcepath = \"$sourcepath\"";
			$entry .= " sourcefile = \"$bmpfile\"/>\n";
		}
		$ResourcesText .= $entry . "  </mbm>\n";
	}
	
	# --- AIF files

	my $AifStructRef = &main::AifStructRef();
	my $AifRef;

	foreach $AifRef (@$AifStructRef) {
# regression hack - workaround lack of AIF directory
		my $trgpath=&main::TrgPath;
		my $trgfile=&main::Path_Split('File',$$AifRef{Trg});
		my $path=&main::Path_Split('Path',"$trgpath$$AifRef{Trg}");
		$path=&main::Path_Chop($path);  
# regression hack - end
# hack - only use colour resource files
		next if ($trgfile =~ /\.ABW$/i);	# ignore greyscale AIF files
		$trgfile =~ s/\.ACL$/.AIF/;			# convert ACL to AIF for immediate use
# hack - end
		my $rssfile = &main::Path_Split('File',$$AifRef{Source});
		my $rsspath = &main::Path_Split('Path',$$AifRef{Source});
		my $sourcepath=&main::Path_Chop(&main::Path_MakeRltToBase($mmpdir,$rsspath));
		my $entry = "  <aif sourcefile = \"$rssfile\"";
		$entry .= " sourcepath = \"$sourcepath\"";
		$entry .= " targetfile = \"$trgfile\" targetpath = \"$path\">\n";
		push @ResourceDownloadList, "$path\\$trgfile";
		foreach my $BitmapRef (@{$$AifRef{BitMaps}}) {
			$entry .= "    <bmp bpp = \"$$BitmapRef{ClDepth}\"";
			my $bmpfile = &main::Path_Split('File',$$BitmapRef{Src});
			my $bmppath = &main::Path_Split('Path',$$BitmapRef{Src});
			$sourcepath = &main::Path_Chop(&main::Path_MakeRltToBase($mmpdir,$bmppath));
			$entry .= " sourcepath = \"$sourcepath\"";
			$entry .= " sourcefile = \"$bmpfile\"/>\n";
		}
		$ResourcesText .= $entry . "  </aif>\n";
	}
	
	# --- RSC files, which must come after .MBM files since they may use the .MBG header files
	
	my $ResourceStructRef=&main::ResourceStructRef;
	my %resourcefiles;
	my %resourcetargets;
	
	foreach my $ResourceRef (@$ResourceStructRef) {
		my $fullsource=$$ResourceRef{Source};
		if (!defined $resourcefiles{$fullsource})
			{
			my $rssfile=&main::Path_Split('File', $fullsource);
			my $rsspath=&main::Path_Split('Path', $fullsource);
			my $entry = "  <rsc sourcefile = \"$rssfile\"";
			$entry .= " targetpath = \"".&main::Path_Chop($$ResourceRef{TrgPath})."\"";
			if (defined $$ResourceRef{Hdr})
				{
				$entry .= " header = \"true\"";
				}
				else
				{
				$entry .= " header = \"false\"";
				}
			my $sourcepath=&main::Path_Chop(&main::Path_MakeRltToBase($mmpdir,$rsspath));
			$entry .= " sourcepath = \"$sourcepath\">\n";
			# ignore the UidList for now..
			$resourcefiles{$fullsource} = $entry;
			$resourcetargets{$fullsource} = $$ResourceRef{TrgPath}.&main::Path_Split('Base', $rssfile);
			}
		$resourcefiles{$fullsource} .= "    <language id = \"$$ResourceRef{Lang}\"/>\n";
		push @ResourceDownloadList, $resourcetargets{$fullsource}.".R".$$ResourceRef{Lang};
	}

	foreach (sort keys %resourcefiles) {
		$ResourcesText .= $resourcefiles{$_} . "  </rsc>\n";
	}

	# --- generate overall .resources file, if any
	
	if ($ResourcesText ne "")
		{
		my $resourcesfile = "$BaseTrg.resources";
		&main::CreateExtraFile("${PrefFilePath}$resourcesfile", "<resources>\n$ResourcesText</resources>\n");
		addFile($resourcesfile, "Text", "", "");
		}
		
	# Build the rest of the file list

	addFile($FirstLib, "Library", $debug, "$Bld\\");	# static library, build-specific
	my $file;
	foreach $file (@SrcList)
		{
		# ensure the case of the extension is what GCC expects
		$file =~ s/\.CPP$/.cpp/i;
		$file =~ s/\.C$/.c/i;
		$file =~ s/\.s$/.S/i;
		my $srcfile=&main::Path_Split('File',$file);
		addFile($srcfile, "Text", $debug, "");
		}
	foreach $file (@RuntimeLibs, @StatLibList)
		{
		addFile($file, "Library", $debug, "$Bld\\");	# static library, build specific
		}
	foreach $file (@ASSPLibList, @LibList)
		{
		addFile($file, "Library", $debug, "");
		}
	if ($Plat eq "WINSCW")
		{
		my $defaults = $ENV{'MWSym2LibraryFiles'};
		# look out for paths?
		foreach $file (@Win32LibList)
			{
			next if ($defaults =~ /;$file/);	# skip default libs
			addFile($file, "Library", $debug, "");
			}
		}

	# Update the project settings

	$changedsettings{"UserSourceTrees"} = "{}";
	$changedsettings{"UserSearchPaths"} = "{}";
	$changedsettings{"Targetname"} = $targetname;

	if ($CW_version > 1)
		{
		$changedsettings{"SystemSearchPaths"} = "{}";
		}
		
	my $RelPath = &main::RelPath;
	my $outputdir = $RelPath;
	if ($Plat eq "WINSCW")
		{
		$outputdir .= &main::TrgPath;
		}
	$changedsettings{"OutputDirectory"} = "{1}".&main::Path_Chop($outputdir);
	$changedsettings{"SymbianInstallationContentSearchLocation"} = "{0}".&main::Path_Chop($RelPath);

	$changedsettings{"SymbianResourcesHeaderFileOutputLocation"} = "{0}".&main::Path_Chop(&main::EPOCIncPath());
	if ($Plat eq "WINSCW")
		{
		$changedsettings{"SymbianResourcesBinaryOutputLocation"} = "{0}".&main::Path_Chop($RelPath);
		}
	else
		{
		$changedsettings{"SymbianResourcesBinaryOutputLocation"} = "{0}".&main::Path_Chop(&main::EPOCDataPath());
		}
		
	if ($TrgType eq "EXE")
		{	
		$changedsettings{"StopAtTempBPOnLaunch"} = "true";
		}
	if ($Plat eq "WINSCW")
		{
		if ($TrgType eq "EXE")
			{	
			# IDE would do the right thing, but we might as well make sure...
			$changedsettings{"MWRuntimeSettings_HostApplication"} = "{0}$outputdir$Trg";
			$changedsettings{"StopAtTempBPOnLaunch"} = "true";
			}
		else
			{
			$changedsettings{"MWRuntimeSettings_HostApplication"} = "{0}${RelPath}epoc.exe";
			}
		}

	$changedsettings{"Gnu Tools Path"} = "{0}${epocroot}gcc\\bin";
	$changedsettings{"Epoc32 Tools Path"} = "{0}${epocroot}tools";
	$changedsettings{"SymbianImportLibraryPath"} = "{0}".&main::Path_Chop(&main::LibPath);

	if ($Plat ne "WINSCW")
		{
		if ($CW_version == 1)
			{
			$changedsettings{"DebuggerAppPath"} = "{0}${epocroot}gcc\\bin\\gdb.exe";
			}
		my $downloadpath = &main::TrgPath;
		$downloadpath =~ s/^Z\\/C:\\/i;
		$changedsettings{"DownloadPath"} = $downloadpath;
		$changedsettings{"FileList"} = "{}";
		}

	my @MacroList=&main::Mmp_Macros();
	push @MacroList, "__${Plat}__" if ($Plat ne $ABI);
	my $extracommands="";
	if ($Plat eq "WINSCW")
		{
		foreach (@MacroList)
			{
			$extracommands .= "-d $_ ";
			}
		if (@Win32LibList  || $Win32Resrc ) 
			{
			$extracommands .= "-d WIN32 -d _WINDOWS ";
			# Callisto bug workaround
			$extracommands .= "-stdinc ";	# to remove the previous -nostdinc
			}
		$extracommands .= &main::CompilerOption("CW");
		}
	else
		{
		foreach (@MacroList)
			{
			$extracommands .= "-D$_ ";
			}
		$extracommands .= &main::CompilerOption("GCC");
		if (&main::SrcDbg && $Bld =~ /DEB$/)
			{
			$extracommands .= " -O0";		# SRCDBG turns off all optimisation
			}
		}
	$changedsettings{"CompilerCmdLine"} = $extracommands;
	
	# Apply the changed settings

	my $settinglist = $xmlTarget->getElementsByTagName("SETTINGLIST",0)->item(0);
	my @settingnodes = $settinglist->getElementsByTagName("SETTING",0);
	foreach my $setting (@settingnodes)
		{
		my $element = $setting->getElementsByTagName("NAME",0)->item(0);
		my $settingname = $element->getFirstChild->getData();
		my $replacement = $changedsettings{$settingname};
		if (defined $replacement) 
			{
			if ($replacement eq "{}")
				{
				if ($settingname eq "UserSearchPaths")
					{
					&addUserSearchPaths($setting);
					}
				if ($settingname eq "SystemSearchPaths")
					{
					&addSystemSearchPaths($setting);
					}
				elsif ($settingname eq "UserSourceTrees")
					{
					&addSourceTrees($setting);
					}
				elsif ($settingname eq "FileList")
					{
					&addDownloadFileList($setting, @ResourceDownloadList);
					}
				}
			elsif ($replacement =~ /^{(.+)}(.+)$/)
				{
				&changePathSetting($setting,$1,$2);
				}
			else
				{
				&changeValue($setting,$replacement);
				}
			}
		}
}

sub ExtraPlat($) {

# Call PmBld again after reprocessing the MMP file and tweaking various main:: variables

	my ($Plat) = @_;

	&main::SetVarsFromMmp($Plat);
	if ($@) {
		print $@;
		print "-- $Plat ignored\n";
		return;	
	}

	foreach (&main::BldList) {
		&main::SetCurBld($_);
		&PMBld;
	}

}

sub disconnectNode($) {

# Remove a node from its parent, also removing the following text node (if any)
# The text node is assumed to contain whitespace for file formatting.
 
	my ($node)=@_;

	my $parent = $node->getParentNode;
	my $sibling = $node->getNextSibling;
	$parent->removeChild($node);
	if (defined $sibling && $sibling->getNodeType == TEXT_NODE)
		{
		$parent->removeChild($sibling);
		}
	return $node;
}

sub removeNode($) {

# disconnect the node and dispose of it

	my ($node) = @_;
	&disconnectNode($node);
	$node->dispose;		# setAttribute("disposed",1);
}

sub textElement($$$$) {
	my ($element,$name,$value,$insertionpoint)=@_;

	my $subElement = new XML::DOM::Element($xmlDoc,$name);
	$subElement->appendChild($xmlDoc->createTextNode($value));
	$element->insertBefore($subElement, $insertionpoint);
}

sub addFile($$$$) {    

	my ($src, $kind, $debug, $shared) = @_;

	my $linkElement = new XML::DOM::Element($xmlDoc,"FILEREF");

	&textElement($linkElement, "PATHTYPE",   "Name");
	&textElement($linkElement, "PATH",       $src);
	&textElement($linkElement, "PATHFORMAT", "Windows");

	my $fileElement = $linkElement->cloneNode(1);
	$fileElement->setTagName("FILE");
	&textElement($fileElement, "FILEKIND",   $kind);
	&textElement($fileElement, "FILEFLAGS",  "Debug") if ($debug);

	$xmlLinkOrder->appendChild($linkElement);
	$xmlFileList->appendChild($fileElement);

	$xmlLinkOrder->addText("\n");
	$xmlFileList->addText("\n");

	# Accumulate source group information

	my $groupfile = $linkElement->cloneNode(1);
	$groupfile->setAttribute("NAME", "$shared$src");			# convenience - remove this later!

	if ($kind eq "Library")
		{
		$xmlLibGroup->appendChild($groupfile);
		$xmlLibGroup->addText("\n");
		}
	else
		{
		$xmlSourceGroup->appendChild($groupfile);
		$xmlSourceGroup->addText("\n");
		}
}

sub addGroup($$) {
	my ($grouplist,$name)=@_;

	my $group = new XML::DOM::Element($xmlDoc,"GROUP");
	$grouplist->appendChild($group);
	$grouplist->addText("\n");

	&textElement($group, "NAME", $name);
	$group->addText("\n");
	return $group;
}

sub addSubTarget($$) {
	my ($subtargetlist,$name)=@_;

	my $subtarget = new XML::DOM::Element($xmlDoc,"SUBTARGET");
	$subtargetlist->appendChild($subtarget);
	$subtargetlist->addText("\n");

	&textElement($subtarget, "TARGETNAME", $name);
}

sub addOrderedTarget($$) {
	my ($targetorder,$name)=@_;

	my $orderedtarget = new XML::DOM::Element($xmlDoc,"ORDEREDTARGET");
	$targetorder->appendChild($orderedtarget);
	$targetorder->addText("\n");

	&textElement($orderedtarget, "NAME", $name);
}

sub finaliseProject {

	# Run through the project, removing all unused targets
	# and build up the TARGETORDER list and the "Build All" target

	my $target;
	my $targetname;

	my $xmlSubTargetList = new XML::DOM::Element($xmlDoc,"SUBTARGETLIST");

	my $xmlTargetOrder = new XML::DOM::Element($xmlDoc,"TARGETORDER");
	$xmlTargetOrder->addText("\n");

	my @targets = $xmlDoc->getElementsByTagName("TARGET",1);
	foreach $target (@targets)
		{
		$targetname = $target->getAttribute("NAME");
		if ($targetname eq "")
			{
			&removeNode($target);
			}
		else
			{
			$target->removeAttribute("NAME");
			&addSubTarget($xmlSubTargetList, $targetname);
			&addOrderedTarget($xmlTargetOrder, $targetname);
			}
		}

	# Build the GROUPLIST
	
	my $xmlGroupList = new XML::DOM::Element($xmlDoc,"GROUPLIST");

	# Build the "Source" group

	my $xmlSourceGroup = &addGroup($xmlGroupList,"Source");
	my %sourcefiles;
	my @sourcegroups = $xmlDoc->getElementsByTagName("SOURCEGROUP",1);
	foreach my $group (@sourcegroups)
		{
		$targetname = $group->getAttribute("TARGET");
		my @files = $group->getElementsByTagName("FILEREF",0);
		foreach my $file (@files)
			{
			my $name = $file->getAttribute("NAME");
			if (!defined $sourcefiles{$name})
				{
				# first occurrence - add to list
				$sourcefiles{$name}=1;
				&textElement($file, "TARGETNAME", $targetname, $file->getFirstChild);
				$file->removeAttribute("NAME");
				&disconnectNode($file);
				$xmlSourceGroup->appendChild($file);
				$xmlSourceGroup->addText("\n");
				}
			}
		&removeNode($group);
		}

	# Build the "Lib" group and its subgroups

	my $xmlLibGroup = &addGroup($xmlGroupList, "Libraries");
	my %libplats;
	my @libgroups = $xmlDoc->getElementsByTagName("LIBGROUP",1);
	foreach my $group (@libgroups)
		{
		$targetname = $group->getAttribute("TARGET");
		my $plat = $group->getAttribute("PLAT");
		if (!defined $libplats{$plat})
			{
			$libplats{$plat} = &addGroup($xmlLibGroup, $plat);
			}
		my $platgroup = $libplats{$plat};
		my @files = $group->getElementsByTagName("FILEREF",0);
		foreach my $file (@files)
			{
			my $name = $file->getAttribute("NAME");
			if (!defined $sourcefiles{"$plat\\$name"})
				{
				# first occurrence - add to list
				$sourcefiles{"$plat\\$name"}=1;
				&textElement($file, "TARGETNAME", $targetname, $file->getFirstChild);
				$file->removeAttribute("NAME");
				&disconnectNode($file);
				$platgroup->appendChild($file);
				$platgroup->addText("\n");
				}
			}
		&removeNode($group);
		}

	# Replace the GROUPLIST & TARGETORDER in the template document

	my $node = $xmlDoc->getElementsByTagName("GROUPLIST",1)->item(0);
	$node->getParentNode->replaceChild($xmlGroupList, $node);

	$node = $xmlDoc->getElementsByTagName("TARGETORDER",1)->item(0);
	$node->getParentNode->replaceChild($xmlTargetOrder, $node);

	# Insert the "Build All" target

	my $xmlBuildAll = new XML::DOM::Element($xmlDoc,"TARGET");
	$xmlBuildAll->addText("\n");
	&textElement($xmlBuildAll, "NAME", "Build All");
	my $settinglist = new XML::DOM::Element($xmlDoc,"SETTINGLIST");
	&textSetting($settinglist, "Linker", "None");
	&textSetting($settinglist, "Targetname", "Build All");
	$xmlBuildAll->appendChild($settinglist);
	$xmlBuildAll->addText("\n");
	&textElement($xmlBuildAll, "FILELIST", "");
	$xmlBuildAll->addText("\n");
	&textElement($xmlBuildAll, "LINKORDER", "");
	$xmlBuildAll->addText("\n");
	$xmlBuildAll->appendChild($xmlSubTargetList);

	&addOrderedTarget($xmlTargetOrder, "Build All");

	$node = $xmlDoc->getElementsByTagName("TARGETLIST",1)->item(0);
	$node->appendChild($xmlBuildAll);

	# Output the result

	&main::Output(
		$xmlDoc->toString
	);

}

sub PMEndSrcList {

	my @PlatList=&main::PlatOverrideList();
	
	if (scalar @PlatList == 0)
		{
		@PlatList = ("WINSCW", "ARM4", "ARMI", "THUMB");
		}
		
	shift @PlatList;	# we've already done the first one in the list
	foreach (@PlatList)
		{
		ExtraPlat($_);
		}

	&finaliseProject();

}

1;
