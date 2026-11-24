# IDE_CW.PM
#
# Copyright (c) 2001-2004 Symbian Software Ltd.  All rights reserved.
#


# Makmake-module for creating XML files which can be imported as CodeWarrior IDE projects

package Ide_cw;

my $CW_minimum_supported_version = 2.0;


# declare variables global for module
my $BaseAddress="";
my %IdeBlds=();
my %PrjHdrs=();
my @Win32LibList=();
my $Win32Resrc;
my $Win32StdHeaders;
my $CopyForStaticLinkage;

my $ExtraFilesPath="";
my @KnownRoots=();

my @addedFiles=();
my $addHeaders = 1;
my $addDocuments = 1;

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

use Pathutl;
use Win32API::Registry qw( :ALL );
use Preprocessor;

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

my $projectTemplate;

my $xmlParser;
my $xmlProjectDoc;
my $xmlLinkDescriptorDoc;
my $xmlLinkDescriptorCommandParent;

my $xmlLinkOrder;		# for accumulating the link order
my $xmlFileList;		# for accumulating the file list
my $xmlSourceGroup;		# for accumulating the source
my $xmlHeadersGroup;	# for accumulating local header files
my $xmlRootGroup;		# for accumulating files to be added outside of project groups (CW >= 2.8 only)
my $xmlLinkGroup;		# for accumulating the link descriptor files (CW >= 2.8 only)
my $xmlLibGroup;		# for accumulating the libraries
my $xmlResourcesGroup;	# for accumulating the .resources files
my $xmlDocumentsGroup;	# for accumulating supported files specified with DOCUMENT in the .mmp file

my $MmpFile;
my $VariantFile;
my $CW_major_version;
my $CW_minor_version;
my $CW_libpath;


sub RoundUp1k($) {
	# Accept C hexadecimal number (0xNNN).  Convert argument to Kb
	# rounded up to the next 1kb boundary.
	use integer;
	return (hex($_[0]) + 1023) / 1024;
}

use Genutl;
use cl_generic;

my $ToolPrefix='';
my $HelperLib='';
my %PlatOpt=(
	'Dlltool'=>'',
	'Entry'=>'-e',
	'Gcc'=>'',
	'Ld'=>'',
	'Petran'=>'',
	'Optimize'=>'-O'
);
my $Dlltool;
my $Archive;
my $Link;
my $Objcopy;

my %CompatibleABIs=(
	ARMI=>['ARM4', 'THUMB'],
	ARM4=>['ARMI'],
	THUMB=>['ARMI']
);
my @CompatibleABIs;

my $Makecmd;
my %ABILibPath=();

sub PMUnderlyingABI($) {
	my ($ABI) = @_;
	if ($ABI eq 'ARM4T') {
		if (&main::BuildAsARM) {
			return 'ARMI';
		}
		elsif (SystemTarget()) {
			return 'ARM4';
		}
		else {
			return 'THUMB';
		}
	}
	return $ABI;
}

sub GetMajorVersion ($)
	{
	my ($versionString) = @_;
	
	if ($versionString =~ /^\d\.\d\.\d$/)
		{
		$versionString =~ s/\.\d$//;
		}
	
	return $versionString;
	}
	
	sub GetMinorVersion ($)
	{
	my ($versionString) = @_;
	
	if ($versionString =~ /^\d\.\d\.\d$/)
		{
		$versionString =~ s/^\d\.\d\.//;
		}
	else
		{
		$versionString = 0;
		}
	
	return $versionString;
	}

sub PMCheckPlatformL {

	# check version of CodeWarrior for Symbian OS

	my @compatibleCWInstallations;

	$CW_major_version = 0;
	$CW_minor_version = 0;

	my $minimumMajorVersion = GetMajorVersion ($CW_minimum_supported_version);
	my $minimumMinorVersion = GetMinorVersion ($CW_minimum_supported_version);

	if (defined $ENV{CW_SYMBIAN_VERSION})
		{
		# CW_SYMBIAN_VERSION is set - either MAKMAKE is being executed by an IDE's .mmp Importer,
		# or the user is specifying a specific CW version to target from the command line.
		# Either way, we've been given a single version to target, so we attempt to do just that.

		$CW_major_version = GetMajorVersion ($ENV{CW_SYMBIAN_VERSION});
		$CW_minor_version = GetMinorVersion ($ENV{CW_SYMBIAN_VERSION});
		
		push @compatibleCWInstallations, $ENV{CW_SYMBIAN_VERSION};
		}
	else
		{
		# CW_SYMBIAN_VERSION isn't set - either MAKMAKE is being executed by a pre-OEM3.0 IDE .mmp
		# Importer or from the command line.  Either way, we delve into the registry and attempt to
		# target the latest CW for Symbian OS installed, recording all CW for Symbian OS installations
		# too.

		my $regKeyHandle;
		my $topLevelKey = HKEY_LOCAL_MACHINE;
		my $productVersionKey = 'SOFTWARE\\Metrowerks\\CodeWarrior\\Product Versions';

		if (!RegOpenKeyEx($topLevelKey, $productVersionKey, 0, KEY_READ, $regKeyHandle))
			{		    		
			die "Can't read \"HKEY_LOCAL_MACHINE\\$productVersionKey\" : ", regLastError(), "\n";
		    }

		my $subKeyIndex = 0;
		my $subKeySize = 0;
		my $subKeyName;

		my @installedCWForSymbianKeys;

		while (RegEnumKeyEx($regKeyHandle, $subKeyIndex, $subKeyName, $subKeySize, [], [], [], []))
			{
			push (@installedCWForSymbianKeys, $productVersionKey."\\".$subKeyName) unless ($subKeyName !~ /Symbian/);
			$subKeyIndex++;
			}

		RegCloseKey($regKeyHandle) || print STDERR "WARNING: Could not close registry key.";

		my $versionType;
		my $versionValue;

		foreach my $installedCWForSymbianKey (@installedCWForSymbianKeys)
			{
			if (!RegOpenKeyEx($topLevelKey, $installedCWForSymbianKey, 0, KEY_READ, $regKeyHandle))
				{		    		
				die "Can't read \"HKEY_LOCAL_MACHINE\\$installedCWForSymbianKey\" : ", regLastError(), "\n";
			    }

			if (!RegQueryValueEx($regKeyHandle, "VERSION", [], $versionType, $versionValue, []))
				{
				die "Can't read \"HKEY_LOCAL_MACHINE\\$installedCWForSymbianKey\\VERSION\" : ", regLastError(), "\n";
				}

			my $temp_major_version = GetMajorVersion ($versionValue);
			my $temp_minor_version = GetMinorVersion ($versionValue);

			if (($temp_major_version > $CW_major_version) ||
				(($temp_minor_version > $CW_minor_version) &&
				   ($temp_major_version >= $CW_major_version)))
				{
				$CW_major_version = $temp_major_version;
				$CW_minor_version = $temp_minor_version;
				}
			
			if (($temp_major_version > $minimumMajorVersion) ||
				(($temp_minor_version > $minimumMinorVersion) &&
				   ($temp_major_version >= $minimumMajorVersion)))
				{
				push @compatibleCWInstallations, $versionValue;
				}

			RegCloseKey($regKeyHandle);
			}
		}

	# We've determined a CW version to target, now we validate if we actually support this

	if (!$CW_major_version ||
		($CW_major_version < $minimumMajorVersion) ||
		(($CW_major_version >= $minimumMajorVersion) && ($CW_minor_version < $minimumMinorVersion)))
		{
		if (defined $ENV{CW_SYMBIAN_VERSION})
			{
			die "Error: CW_SYMBIAN_VERSION is set to $ENV{CW_SYMBIAN_VERSION}.\n       The minimum version supported by these tools is $CW_minimum_supported_version.\n";
			}
		else
			{
			die "ERROR: Unable to identify a compatible CodeWarrior for Symbian OS installation.\n";
			}
		}

	if (@compatibleCWInstallations > 1)
		{
		my $targetVersion = $CW_major_version;
		$targetVersion .= ".$CW_minor_version" if $CW_minor_version;
			
		print ("Info: More than one compatible CodeWarrior for Symbian OS installation has been detected.\n");
		print ("      The generated project will target $targetVersion - to override this, set the CW_SYMBIAN_VERSION\n");
		print ("      environment variable to the version number you wish to target and re-run this command.\n");
		print ("      Supported version numbers detected : @compatibleCWInstallations.\n");
		}


	# CW version has been validated, tailor generated projects on this basis

	$CW_libpath = 'Symbian_Support\Win32-x86 Support\Libraries\Win32 SDK';
	$projectTemplate = "CW_project_template_v3.xml";

	if ($CW_major_version < 2.8)
		{
		$projectTemplate = "CW_project_template_v2.xml";
		$CW_libpath = 'Other_Metrowerks_Tools\Symbian Libs\Pro2';
		}

	$xmlParser = new XML::DOM::Parser; 
	$xmlProjectDoc = $xmlParser->parsefile ($FindBin::Bin."\\$projectTemplate");
}

sub PMPlatProcessMmp (@) {
	my @PlatTxt=@_;
	
# process the START <windows platforms> END blocks

	my $BaseTrg=&main::BaseTrg;
	my $BasicTrgType=&main::BasicTrgType;
	my $MakeFilePath=&main::MakeFilePath;
	$MmpFile=&main::MmpFile;
	$VariantFile=&main::VariantFile();

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
	
	my $TrgType=&main::TrgType;

	# Set up the list of known roots

	my $epocroot=&main::Path_Drive . &main::EPOCPath;
	$epocroot =~ s/EPOC32\\$//i;

	my $mmproot = &main::Path_Drive . &main::Path_Split('Path',$MmpFile);
	my $mmprootname = "MMPDir";
	my $mmpisglobal = 0;

	if (defined $ENV{CW_ROOT_NAME})
		{
		# generate KnownRoots suitable for the IDE MMP importer
		# This has a global source tree for EPOCROOT, and puts the
		# project next to the MMP file

		addKnownRoot($ENV{CW_ROOT_NAME}, 1, $epocroot, "");
		$mmprootname = "Project";
		$mmpisglobal = 1;
		}
	else
		{
		# generate KnownRoots suitable for command-line generated XML files
		# We will add a user source tree for MMPDir and EPOCROOT, but can't use
		# EPOCROOT for the OutputDirectory

		addKnownRoot("EPOCROOT", 0, $epocroot, "");
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

	my @targets = $xmlProjectDoc->getElementsByTagName("TARGET",1); 
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

	my $newlist = new XML::DOM::Element($xmlProjectDoc,$tag);
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

	my $setting = new XML::DOM::Element($xmlProjectDoc,"SETTING");
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

	my $sourcepath = new XML::DOM::Element($xmlProjectDoc,"SETTING");
	$sourcepath->addText("\n");
	&textSetting($sourcepath, "Name", "EPOCROOT");
	&textSetting($sourcepath, "Kind", "AbsolutePath");

	my $pathdata = new XML::DOM::Element($xmlProjectDoc,"SETTING");
	&textElement($pathdata, "NAME", "Path"); 
	$pathdata->addText("\n");

	my $epocroot=&main::EPOCPath;
	$epocroot =~ s/\\EPOC32\\$/\\/i;

	&addRootedPath($pathdata, 1, $epocroot);

	$sourcepath->appendChild($pathdata);
	$node->appendChild($sourcepath);

	my $mmproot = &main::Path_Split('Path',$MmpFile);
	my $sourcepath2 = new XML::DOM::Element($xmlProjectDoc,"SETTING");
	$sourcepath2->addText("\n");
	&textSetting($sourcepath2, "Name", "MMPDir");
	&textSetting($sourcepath2, "Kind", "AbsolutePath");

	my $pathdata2 = new XML::DOM::Element($xmlProjectDoc,"SETTING");
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

	my %ordereddirs;
	my @ordereddirlist=();
	foreach my $dir (&main::UserIncPaths)
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

	if ($CW_major_version >= 2.8)
		{
		my $MmpFilePath = &main::Path_Split('Path',$MmpFile);
		$dirs{$MmpFilePath}=1;
		}

	$dirs{$ExtraFilesPath}=1;
		

	foreach my $srcdir (sort keys %dirs)
		{
		if (!defined($ordereddirs{uc $srcdir}))
			{
			push @ordereddirlist, $srcdir;
			}
		}
		
	foreach my $srcdir (@ordereddirlist)
		{
		my $accesspath = new XML::DOM::Element($xmlProjectDoc,"SETTING");
		$accesspath->addText("\n");
		my $pathdata = new XML::DOM::Element($xmlProjectDoc,"SETTING");
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

	my $ASSPLinkPath;
	$ASSPLinkPath = &main::ASSPLinkPath if (&main::ASSPLibList);

	my %ordereddirs;
	my @ordereddirlist=();
	foreach my $dir (&main::SysIncPaths, &main::StatLinkPath, $ASSPLinkPath, &main::LinkPath)
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

	my %dirs;

	if ($VariantFile)
		{
		my $VariantFilePath = &main::Path_Split('Path',$VariantFile);
		$dirs{$VariantFilePath}=1;
		}
		

	foreach my $srcdir (sort keys %dirs)
		{
		if (!defined($ordereddirs{uc $srcdir}))
			{
			push @ordereddirlist, $srcdir;
			}
		}
		
	foreach my $srcdir (@ordereddirlist)
		{
		my $accesspath = new XML::DOM::Element($xmlProjectDoc,"SETTING");
		$accesspath->addText("\n");
		my $pathdata = new XML::DOM::Element($xmlProjectDoc,"SETTING");
		&textElement($pathdata, "NAME", "SearchPath"); 
		$pathdata->addText("\n");
		&addRootedPath($pathdata, 0, $srcdir);

		$accesspath->appendChild($pathdata);
		&textSetting($accesspath, "Recursive", "false");
		&textSetting($accesspath, "FrameworkPath", "false");
		&textSetting($accesspath, "HostFlags", "All");
		$node->appendChild($accesspath);
		}

	my $accesspath = new XML::DOM::Element($xmlProjectDoc,"SETTING");
	$accesspath->addText("\n");
	my $pathdata = new XML::DOM::Element($xmlProjectDoc,"SETTING");
	&textElement($pathdata, "NAME", "SearchPath"); 
	$pathdata->addText("\n");
	&textSetting($pathdata, "Path", $CW_libpath);
	&textSetting($pathdata, "PathFormat", "Windows");
	&textSetting($pathdata, "PathRoot", "CodeWarrior");

	$accesspath->appendChild($pathdata);
	&textSetting($accesspath, "Recursive", "false");
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
		
		my $download = new XML::DOM::Element($xmlProjectDoc,"SETTING");
		$download->addText("\n");
		my $pathdata = new XML::DOM::Element($xmlProjectDoc,"SETTING");
		&textElement($pathdata, "NAME", "HostFilePath"); 
		$pathdata->addText("\n");
		&addRootedPath($pathdata, 0, "$epocdata$srcfile");

		$download->appendChild($pathdata);
		&textSetting($download, "TargetFilePath", $targetpath);
		$node->appendChild($download);
		}
	}

sub kitRelativePath ($) {
	my ($kitRootBasedPath) = @_;
		
	my $kitRoot = &main::EPOCPath;
	$kitRoot =~ s/EPOC32\\$//i;
	$kitRoot = quotemeta (&main::Path_Chop($kitRoot));

	$kitRootBasedPath =~ s/^$kitRoot//i;

	$kitRootBasedPath;
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
	$epocroot =~ s/EPOC32\\$//i;
	my $UIDFile;

	$ExtraFilesPath = &main::MakeFilePath;

	if ($Bld =~ /DEB/) {
		@LibList=&main::DebugLibList;
	} else {
		@LibList=&main::LibList;
	}
	
	if ( !&main::CanBuild( ) )
	{	# Unable to build given platforms.
		return ;
	}

	my $xmlTarget = findTarget($BaseName, "$Plat $Bld", "$ABI $Bld");
	return if (!defined($xmlTarget));
	my $targetname = $xmlTarget->getAttribute("NAME");

	my $UnderlyingABI=PMUnderlyingABI($ABI);
	my @ChopRTWSysIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::SysIncPaths));
	my @ChopRTWUserIncPaths=&main::Path_Chop(&main::Path_RltToWork(&main::UserIncPaths));
	my $EPOCPath=&main::EPOCPath;
	my $LinkAs=&main::LinkAs;
	my $LibPath=&main::LibPath;
	my @UidList=&main::UidList;	
	my $WarningLevelGCC=&main::CompilerOption("GCC");
	my $ExportLibrary=$BaseTrg;
	my $NoExportLibrary=&main::NoExportLibrary;

	my $ChopBldPath=&main::Path_Chop(&main::BldPath);
	my $EPOCIncPath=&main::EPOCIncPath;
	my $ChopRelPath=&main::Path_Chop(&main::RelPath);
	my $RelPath=&main::RelPath;
	my $StatLinkPath=&main::StatLinkPath;

	my @compatibleDOCUMENTExtensions = ("cfg", "h", "hrh", "iby", "inf", "ini", "loc", "mmpi", "policy", "ra", "rh", "rls", "rss", "script", "txt");
	my @DocList = &main::DocList;
	@addedFiles=();

#	set up LinkAs
	$UidList[2]=~/^0x(.*)$/o;
	if ($1 ne '00000000') { # have to make sure than series of noughts in brackets doesn't appear in name for null uids
		$LinkAs=join '', &main::Path_Split('Base',$LinkAs),"[$1]",&main::Path_Split('Ext',$LinkAs);
	}

#	set up dlltool flag hash
	my %ABIDlltool=(
		ARMI=>'-m arm_interwork',
		ARM4=>'-m arm',
		THUMB=>'-m thumb'
	);

#	work out the flags for various platforms
	if ($ABI eq 'ARMI') {
		$PlatOpt{Gcc}='-march=armv4t -mthumb-interwork';
		$PlatOpt{Dlltool}=$ABIDlltool{ARMI};
	}
	elsif ($ABI eq 'ARM4') {
		$PlatOpt{Gcc}='-march=armv4';
#		allow thumb for ARM4 ABI where necessary
		unless (&main::PlatABI eq 'ARM4') {
			$PlatOpt{Gcc}.='t';
		}
		$PlatOpt{Dlltool}=$ABIDlltool{ARM4};
	}
	elsif ($ABI eq 'THUMB') {
		$PlatOpt{Entry}='--thumb-entry';
		$PlatOpt{Gcc}='-mthumb-interwork';
		$PlatOpt{Dlltool}=$ABIDlltool{THUMB};
#		$HelperLib='up_thumb.lib';
	}
	elsif ($Plat ne 'WINSCW') {
		&main::FatalError("Platform module - ABI \"$ABI\" unrecognised");
	}

	if ($Plat ne 'WINSCW') {
		@CompatibleABIs=@{$CompatibleABIs{$UnderlyingABI}};
	}

#	set up CompatibleABI lib path hash
	foreach (@CompatibleABIs) {
		$ABILibPath{$_}=&main::Path_Strip("$LibPath..\\..\\$_\\");
	}

	$Dlltool=$ToolPrefix.'dlltool.exe';
	$Archive=$ToolPrefix.'ar.exe';
	$Link=$ToolPrefix.'ld.exe';
	$Objcopy=$ToolPrefix.'objcopy.exe';

	my $WarningLevelCW=&main::CompilerOption("CW");

	$xmlFileList = newList($xmlTarget,"FILELIST",1);
	$xmlFileList->addText("\n");

	$xmlLinkOrder = newList($xmlTarget,"LINKORDER",1);
	$xmlLinkOrder->addText("\n");

	# Create temporary sublists, which will be
	# removed during finaliseProject

	$xmlSourceGroup = newList($xmlTarget,"SOURCEGROUP",0);
	$xmlSourceGroup->setAttribute("TARGET", $targetname);
	$xmlSourceGroup->addText("\n");

#	CW2.8-> has additional groups to contain link descriptor files,
#	files on the root of a project (currently just the .mmp file),
#	local header files and files added with the DOCUMENT .mmp keyword
	if ($CW_major_version >= 2.8)
		{
		$xmlRootGroup = newList($xmlTarget,"ROOTGROUP",0);
		$xmlRootGroup->setAttribute("TARGET", $targetname);
		$xmlRootGroup->addText("\n");
			
		$xmlLinkGroup = newList($xmlTarget,"LINKGROUP",0);
		$xmlLinkGroup->setAttribute("TARGET", $targetname);
		$xmlLinkGroup->addText("\n");

		$xmlHeadersGroup = newList($xmlTarget,"HEADERSGROUP",0);
		$xmlHeadersGroup->setAttribute("TARGET", $targetname);
		$xmlHeadersGroup->addText("\n");

		$xmlDocumentsGroup = newList($xmlTarget,"DOCUMENTSGROUP",0);
		$xmlDocumentsGroup->setAttribute("TARGET", $targetname);
		$xmlDocumentsGroup->addText("\n");
		}

	$xmlLibGroup = newList($xmlTarget,"LIBGROUP",0);
	$xmlLibGroup->setAttribute("TARGET", $targetname);
	$xmlLibGroup->setAttribute("PLAT", $Plat);
	$xmlLibGroup->addText("\n");

	$xmlResourcesGroup = newList($xmlTarget,"RESOURCESGROUP",0);
	$xmlResourcesGroup->setAttribute("TARGET", $targetname);
	$xmlResourcesGroup->addText("\n");

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

	# Add the .mmp file for CW 2.8->
	if ($CW_major_version >= 2.8)
		{
		addFile(&main::Path_Split('File',$MmpFile), "Text", "", "", "Root");
		}

	# Create the pref file for CW < 2.8
	if ($CW_major_version < 2.8)
		{
		my $preffile = &main::Path_Split('Base',$MmpFile).".pref";
	
		my @UidList=&main::UidList;
		my $PrefsText=join(
				"\n",
				"TARGET      $Trg",
				"TARGETTYPE  $TrgType",
				"UID         $UidList[1] $UidList[2]"
#				"CAPABILITY  ".&main::Capability
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

		&main::CreateExtraFile("${ExtraFilesPath}$preffile", "$PrefsText\n");
		
		addFile($preffile, "Text", $debug, "");
		}


	# Create the uid.cpp file for CW 2.8->		
	if ($CW_major_version >= 2.8 && $Plat eq "WINSCW" && $BasicTrgType=~/^(EXE|DLL)$/oi)
		{
		# create the UID source file
		my $UidText=join(
			"\n",
			'// Makmake-generated uid source file',
			'#include <E32STD.H>',
			'#pragma data_seg(".E32_UID")',
			'__WINS_UID('
		);
		foreach (@UidList) {
			$UidText.="$_,";
		}
		chop $UidText;
		$UidText.=")\n";
		$UidText.="#pragma data_seg()\n";

		$UIDFile = uc ($BaseTrg).'_UID_.cpp';
		&main::CreateExtraFile("${ExtraFilesPath}$UIDFile", $UidText);
		}


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

#  		addFile($rssfile, "Text", "", "", "Resources");
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

#			addFile($rssfile, "Text", "", "", "Resources");
			}
		$resourcefiles{$fullsource} .= "    <language id = \"$$ResourceRef{Lang}\"/>\n";
		push @ResourceDownloadList, $resourcetargets{$fullsource}.".R".$$ResourceRef{Lang};
	}

	foreach (sort keys %resourcefiles) {
		$ResourcesText .= $resourcefiles{$_} . "  </rsc>\n";
	}

	# --- If required, generate .resources file per platform
	
	if ($ResourcesText ne "")
		{
		my $resourcesfile = "$BaseTrg$Plat.resources";
		&main::CreateExtraFile("${ExtraFilesPath}$resourcesfile", "<resources>\n$ResourcesText</resources>\n");
		addFile($resourcesfile, "Text", "", "", "Resources");
		}
		
	# Build the rest of the file list

	if ($BasicTrgType!~/^LIB$/o)
		{
		addFile($FirstLib, "Library", $debug, "$Bld\\");	# static library, build-specific
		}

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

	# If required, add the uid.cpp file so that it appears after all other source files in the link order
	if (defined $UIDFile)
		{
		addFile($UIDFile, "Text", "", "");
		}

	foreach $file (@RuntimeLibs, @StatLibList)
		{
		next if ( $file eq $FirstLib );		#skip if file equals FirstLib.
		addFile($file, "Library", $debug, "$Bld\\");	# static library, build specific
		}
	foreach $file (@ASSPLibList, @LibList)
		{
		next if ( $file eq $FirstLib );		#skip if file equals FirstLib.
		addFile($file, "Library", $debug, "");
		}
	if ($Plat eq "WINSCW")
		{
		my $defaults = $ENV{'MWSym2LibraryFiles'};
		# look out for paths?
		foreach $file (@Win32LibList)
			{
			# skip default libs and FirstLib.
			next if ( ($defaults =~ /;$file/) || ($file eq $FirstLib) );	
			addFile($file, "Library", $debug, "");
			}
		}

	
	# Update the project settings

	$changedsettings{"UserSourceTrees"} = "{}";
	$changedsettings{"UserSearchPaths"} = "{}";
	$changedsettings{"SystemSearchPaths"} = "{}";
	$changedsettings{"Targetname"} = $targetname;

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
		
	if ($Plat eq "WINSCW")
		{
		if ($TrgType eq "EXE")
			{	
			# IDE would do the right thing, but we might as well make sure...
			$changedsettings{"MWRuntimeSettings_HostApplication"} = "{0}$outputdir$Trg";
			}
		else
			{
			$changedsettings{"MWRuntimeSettings_HostApplication"} = "{0}${RelPath}epoc.exe";
			}
		}

	if ($CW_major_version < 2.8)
		{
		$changedsettings{"Gnu Tools Path"} = "{0}${epocroot}epoc32\\gcc\\bin";
		$changedsettings{"Epoc32 Tools Path"} = "{0}${epocroot}epoc32\\tools";
		$changedsettings{"SymbianImportLibraryPath"} = "{0}".&main::Path_Chop(&main::LibPath);
		}
	else
		{
		if (defined $ENV{CW_ROOT_NAME})
			{
			$changedsettings{"SymbianEpocToolsPath"} = "{0}${epocroot}";
			}
		}

	if ($Plat ne "WINSCW")
		{
		my $downloadpath = &main::TrgPath;
		$downloadpath =~ s/^Z\\/C:\\/i;
		$changedsettings{"DownloadPath"} = $downloadpath;
		$changedsettings{"FileList"} = "{}";
		}

	my @MacroList;

	if ($CW_major_version < 2.8)
		{
		@MacroList = &main::Mmp_Macros();
		}
	else
		{
		@MacroList = &main::MacroList();			
		}

	push @MacroList, "__${Plat}__" if ($Plat ne $ABI);

	if ($CW_major_version < 2.8)
		{
		my $extracommands="";
		if ($Plat eq "WINSCW")
			{
			foreach (@MacroList)
				{
				$extracommands .= "-d $_ ";
				}				
			if (@Win32LibList || $Win32Resrc )
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

		if ($VariantFile)
			{
			$changedsettings{"CompilerPrefix"} = &main::Path_Split('File',$VariantFile);
			}
		}
	else
		{
		# Symbian Compiler Panel
			
		my $compiler="";
		my $compilerargs="";
		my $macros="";

		foreach (@MacroList)
			{
			$_ =~ s/\s+$//;
			$_ =~ s/^\s+//;
			$macros .= "$_,";
			}

# CW2.8-> WINSCW compilation stage

		if ($Plat eq "WINSCW")
			{
			$compiler = "WINSCW";
			$compilerargs .= "-wchar_t off -align 4 -warnings on -w nohidevirtual, nounusedexpr -msgstyle gcc -enum int -str pool ";

			if ($Bld =~ /DEB/)
				{
				$compilerargs .= "-O0 ";

				# euser hack to apply inlining on the _NAKED functions
				# NOTE: persisting with this for consistency - inlining behaviour for CW is incorrect
				if ($BaseTrg !~ /^EUSER$/oi)
					{
					$compilerargs .= "-inline off ";
					}
				}
			else
				{
				$compilerargs .= "-O4,s ";
				}
				
			if (@Win32LibList || $Win32Resrc ) 
				{
				$macros .= "WIN32,_WINDOWS,";
				# Callisto bug workaround
				# NOTE: persisting with this for consistency
				$compilerargs .= "-stdinc ";
				}
			else
				{
				$compilerargs .= "-nostdinc ";
				}
				
			$compilerargs .= &main::CompilerOption("CW");			
			}
		else
			{

# CW2.8-> GCC compilation stage

			$compiler = "ARM";
				
			if ($Bld =~ /REL$/)
				{
				$compilerargs .= "-s -fomit-frame-pointer -O "
				}
			else
				{
				unless (&main::SrcDbg)
					{
					$compilerargs .= "-O ";
					}
				}
			
			if ($ABI eq "ARMI")
				{
				$compilerargs .= "-march=armv4t -mthumb-interwork";
				}
			elsif ($ABI eq "ARM4")
				{
				$compilerargs .= "-march=armv4";

				unless (&main::PlatABI eq "ARM4")
					{
					$compilerargs .= "t";
					}
				}
			elsif ($ABI eq "THUMB")
				{
				$compiler = "THUMB";
				$compilerargs .= "-mthumb-interwork";
				}

			$compilerargs .= " -pipe -nostdinc -Wall -Wno-ctor-dtor-privacy -Wno-unknown-pragmas ";

			$compilerargs .= &main::CompilerOption("GCC");
			}

		$macros =~ s/,$//;
		$compilerargs =~ s/ $//;

		$changedsettings{"Compiler"} = $compiler;
		$changedsettings{"Macros"} = $macros;
		$changedsettings{"Arguments"} = $compilerargs;
		
		if ($VariantFile)
			{
			$changedsettings{"PrefixFile"} = &main::Path_Split('File',$VariantFile);
			}

		# Symbian Linker Panel
		$changedsettings{"LinkOutputFile"} = $Trg;
			
		if (!$NoExportLibrary)
			{
			$changedsettings{"SymbianImportLibrary"} = $ExportLibrary.".lib";
			}

		# Template defaults for canDebug/canRun are both "true"
		if ($Bld =~ /REL/)
			{
			$changedsettings{"canDebug"} = "false";
			}

		if ($Plat eq "WINSCW")
			{
			if ($TrgType ne "APP" && $TrgType ne "EXE" && $TrgType ne "EXEDLL" && $TrgType ne "EPOCEXE")
				{
				$changedsettings{"canDebug"} = "false";
				$changedsettings{"canRun"} = "false";
				}
			}
		else
			{
			$changedsettings{"canRun"} = "false";

			if ($TrgType eq "LIB" || $TrgType eq "KLIB")
				{
				$changedsettings{"canDebug"} = "false";
				}
			}
		}


	if ($CW_major_version >= 2.8)
		{
		$xmlLinkDescriptorDoc = $xmlParser->parsefile ($FindBin::Bin."\\CW_link_descriptor_template.cwlink");
		$xmlLinkDescriptorCommandParent = $xmlLinkDescriptorDoc->getElementsByTagName("array",1)->item(0);
		
		my $linkDescriptorFile = "$BaseTrg$Plat$Bld.cwlink";

		my $copyCommand = 'perl.exe -S ecopyfile.pl ';
		my $deleteCommand = 'cmd.exe /C del ';

		my $exportUnfrozenWarningMessage = 'Created "${var:KIT_EPOCROOT}'.kitRelativePath($LibPath).'${var:IMPORT_LIBRARY}" '.
											'from "${target.data}\\${output.file.root}.def" as EXPORTUNFROZEN specified.';

		my $linkCommand = "";		

# CW2.8-> WINSCW library generation and link stage

		if ($Plat eq "WINSCW")
			{
			# Generate library
			if ($DefFile and !$NoExportLibrary)
				{
				unless (&main::ExportUnfrozen)
					{
						my $LibLinkAs = ($BasicTrgType=~/^IMPLIB$/io) ? $LinkAs : $Trg;

						$linkCommand = 'mwldsym2.exe "${var:DEF_FILE}" -importlib -o "'.
										'${var:KIT_EPOCROOT}'.kitRelativePath($LibPath).'${var:IMPORT_LIBRARY}" -addcommand "out:'.$LibLinkAs.'" -warnings off';
						addLinkDescriptorCommand ($linkCommand);
					}
				}

			if ((2.8 == $CW_major_version) && (0 == $CW_minor_version))
				{
				# For OEM2.8, create a file containing all objects required in the link.  This is used in all
				# calls to mwldsym2 in order to avoid exceeding the Windows command line
				# length in projects containing a large amount of source files
				$linkCommand ='cmd.exe /C echo ${var:LINK_OBJS}>"${target.data}\${output.file.root}.lst"';
				addLinkDescriptorCommand ($linkCommand);
				}
			
			my $stage1linkflags = "";
			my $linkflags = "";
			my $commonLinkFlags = '-msgstyle gcc -stdlib';

			if ($BasicTrgType=~/^(EXE|DLL)$/o) {
						$commonLinkFlags .= ' ${var:FIRST_LIB} '
				}

			foreach my $lib (@Win32LibList)
				{
				my $win32lib = $lib;
				$win32lib = "-l$win32lib" unless ($win32lib =~ /\\/);
				$commonLinkFlags .= " ". lc $win32lib;
				}

			if ($BasicTrgType =~ /^DLL$/o)
				{
				if ($BaseAddress ne "")
					{
					$commonLinkFlags .= " -imagebase $BaseAddress";
					}
				
				$commonLinkFlags .= ' -m "?_E32Dll@@YGHPAXI0@Z" -shared';
				}
			elsif ($BasicTrgType =~ /^EXE$/o)
				{
				$commonLinkFlags .= ' -m "?_E32Startup@@YGXXZ"';
				}

			$commonLinkFlags .= ' -subsystem windows';

			if (&main::HeapSize)
				{
				my %HeapSize = &main::HeapSize;
				$commonLinkFlags .= ' -heapreserve='.RoundUp1k($HeapSize{Max}).' -heapcommit='.RoundUp1k($HeapSize{Min}); 
				}

			if ($BasicTrgType =~ /^(DLL|EXE)$/o)
				{
				if ($Bld =~ /DEB$/o)
					{
					$commonLinkFlags .= ' -g';
					}
				}
				
			my $EntrySymbol='';
			if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEXP$/o)
				{
				$stage1linkflags = $commonLinkFlags.' ${var:LIBS}'.
					' -o "${target.data}\\${output.file.name}"'. 
					' -export dllexport '.
					' -nocompactimportlib'. 
					' -implib "${target.data}\\${output.file.root}.lib"'.
					' -addcommand "out:${output.file.name}"'.
					' -warnings off';
				}

			$linkflags = $commonLinkFlags.' ${var:LIBS}'.
				' -o "${output}\\${output.file.name}"';
				
			if ($Bld=~/REL$/o && $BasicTrgType!~/^LIB$/o)
				{
				# Generate map file for release build executables
				$linkflags .= ' -map "${output}\\${output.file.name}.map"';
				}
			
			if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEXP$/o)
				{
				$linkflags .= ' -f "${target.data}\\${output.file.root}.def"';
				
				if (&main::ExportUnfrozen)
					{
					$linkflags .= ' -implib "${var:KIT_EPOCROOT}'.kitRelativePath($LibPath).'${var:IMPORT_LIBRARY}"'.
						' -addcommand "out:${output.file.name}" -warnings off';
					}
				else
					{
					$linkflags .= ' -noimplib';
					}
				}
			else
				{
				$linkflags .= ' -noimplib';
				}
	
			if ($BasicTrgType=~/^DLL$/o)
				{
				if ((2.8 == $CW_major_version) && (0 == $CW_minor_version))
					{
					$linkCommand = 'mwldsym2.exe '.$stage1linkflags.' ${var:COMMON_LINK_FLAGS} @"${target.data}\${output.file.root}.lst"';
					}
				else
					{
					# For OEM2.8.1 onwards, make use of ${var:LINK_OBJS_NO_PATH} in order to reduce link
					# command line lengths
					$linkCommand = 'mwldsym2.exe '.$stage1linkflags.' ${var:COMMON_LINK_FLAGS} -l "${target.data}\\ObjectCode" -search ${var:LINK_OBJS_NO_PATH}';					
					}

				addLinkDescriptorCommand ($linkCommand, undef, undef, undef, $FirstLib);

				$linkCommand = $deleteCommand.'"${target.data}\\${output.file.name}"';
				addLinkDescriptorCommand ($linkCommand);

				my $show_options = 'names,unmangled,verbose';
				$linkCommand = 'mwldsym2.exe -S -show only,'.$show_options.' -o "${target.data}\\${output.file.root}.inf" "${target.data}\\${output.file.root}.lib"';
				addLinkDescriptorCommand ($linkCommand);

				$linkCommand = 'perl.exe -w -S makedef.pl -Inffile "${target.data}\\${output.file.root}.inf"';
				if (-e $DefFile)
					{
					$linkCommand .= ' -Frzfile "'.$DefFile.'"';
					}
					
				my $Export;
				my $Ordinal=1;
				foreach $Export (&main::Exports)
					{
					$linkCommand .= " -$Ordinal $Export";
					$Ordinal++;
					}					

				$linkCommand .= ' "${target.data}\\${output.file.root}.def"';					
				addLinkDescriptorCommand ($linkCommand);
				
				$linkCommand = $deleteCommand.'"${target.data}\\${output.file.root}.inf"';
				addLinkDescriptorCommand ($linkCommand);
				
				$linkCommand = $deleteCommand.'"${target.data}\\${output.file.root}.lib"';
				addLinkDescriptorCommand ($linkCommand);
				}

			$linkCommand = "mwldsym2.exe ";

			if ($BasicTrgType =~/^LIB$/o)
				{
				$linkCommand .= '-library ';
				}
				
			if ((2.8 == $CW_major_version) && (0 == $CW_minor_version))
				{
				$linkCommand .= $linkflags.' ${var:COMMON_LINK_FLAGS} @"${target.data}\${output.file.root}.lst"';
				}
			else
				{
				# For OEM2.8.1 onwards, make use of ${var:LINK_OBJS_NO_PATH} in order to reduce link
				# command line lengths
				$linkCommand .= $linkflags.' ${var:COMMON_LINK_FLAGS} -l "${target.data}\\ObjectCode" -search ${var:LINK_OBJS_NO_PATH}';					
				}

			my $warningMessage;
			
			if (&main::ExportUnfrozen)
				{
				$warningMessage = $exportUnfrozenWarningMessage;
				}
			
			if ($BasicTrgType =~/^LIB$/o)
				{				
				addLinkDescriptorCommand ($linkCommand, undef, undef, undef, undef, $warningMessage);
				}
			else
				{
				addLinkDescriptorCommand ($linkCommand, undef, undef, undef, $FirstLib, $warningMessage);
				}

			if ($CopyForStaticLinkage)
				{
				$linkCommand = $copyCommand.
								'"${output}\\${output.file.name}" '.
								'"${var:KIT_EPOCROOT}'.kitRelativePath($RelPath).'${output.file.name}"';
				addLinkDescriptorCommand ($linkCommand, "false", "false");
				}
			}

# CW2.8-> GCC library generation and link stage

		else
			{
			# Generate library

			if ($DefFile and !$NoExportLibrary)
				{
				unless (&main::ExportUnfrozen)
					{
					$linkCommand = "$Dlltool $PlatOpt{Dlltool}".' --output-lib "${var:KIT_EPOCROOT}'.kitRelativePath($LibPath).'${var:IMPORT_LIBRARY}" --def '.
							'"${var:DEF_FILE}" --dllname "'.$LinkAs.'"';
					addLinkDescriptorCommand ($linkCommand);

					foreach (@CompatibleABIs)
						{
						$linkCommand = "$Dlltool $ABIDlltool{$_}".' --output-lib "${var:KIT_EPOCROOT}'.kitRelativePath($ABILibPath{$_}).'UREL\\${var:IMPORT_LIBRARY}" --def '.
								'"${var:DEF_FILE}" --dllname "'.$LinkAs.'"';
						addLinkDescriptorCommand ($linkCommand);
						}
					}
				}


			# TARGET *.IN
			#------------
			$linkCommand = $deleteCommand.'"${target.data}\\${output.file.root}.in"';
			addLinkDescriptorCommand ($linkCommand, "false", "false", undef, undef, undef, undef, (0,1));
					
			$linkCommand = 'ar.exe cr "${target.data}\\${output.file.root}.in" ${var:LINK_OBJS}';
			addLinkDescriptorCommand ($linkCommand);
			

			# Perform Link

		#	Establish the entry point symbol
			my $EntrySymbol;
			if ($BasicTrgType=~/^DLL$/o) {
				$EntrySymbol = '_E32Dll';
			}
			elsif ($BasicTrgType=~/^EXE$/o) {
				$EntrySymbol = '_E32Startup';
			}

			if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEDLL$/o) {

		#		generate a .DEF file from the objects and static libraries
				$linkCommand = "$Dlltool $PlatOpt{Dlltool} --output-def ".'"${target.data}\\${output.file.root}.inf" "${target.data}\\${output.file.root}.in"';

				foreach (@StatLibList) {
					$linkCommand .= ' "${var:KIT_EPOCROOT}'.kitRelativePath($StatLinkPath).$_.'"';
				}

				addLinkDescriptorCommand ($linkCommand);

		#		reorder the .DEF file taking frozen exports into account if there are any
		#			call perl on the script here so nmake will die if there are errors - this doesn't happen if calling perl in a batch file
				$linkCommand = 'perl.exe -S makedef.pl -Deffile "${target.data}\\${output.file.root}.inf"';
				if (-e $DefFile) { # effectively "if project frozen ..."
					$linkCommand .= " -Frzfile \"".'${var:DEF_FILE}'."\"";
				}
				# freeze ordinals, a maximum of 2, for polymorphic dlls
				my $Ordinal;
				my $Num=1;
				foreach $Ordinal (&main::Exports) {
					$linkCommand .= " -$Num $Ordinal";
					$Num++;
				}
				$linkCommand .= ' "${target.data}\\${output.file.root}.def"';
				addLinkDescriptorCommand ($linkCommand);

		#		delete the unordered definition file
				$linkCommand = $deleteCommand.'"${target.data}\\${output.file.root}.inf"';
				addLinkDescriptorCommand ($linkCommand, "false", "false");

		#		generate an export object from the ordered .DEF file
				$linkCommand = "$Dlltool $PlatOpt{Dlltool} --def".' "${target.data}\\${output.file.root}.def"'.
					' --output-exp "${target.data}\\${output.file.root}.exp"'.
					" --dllname \"$LinkAs\"";

				my $warningMessage;
					
				if (&main::ExportUnfrozen) {
					$warningMessage = $exportUnfrozenWarningMessage;
					$linkCommand .= ' --output-lib "${var:KIT_EPOCROOT}'.kitRelativePath($LibPath).'${var:IMPORT_LIBRARY}"';
				}
				
				addLinkDescriptorCommand ($linkCommand, undef, undef, undef, undef, $warningMessage);
			}

		#	call ld to do base relocations (and dll exports)
			if ($BasicTrgType=~/^(DLL|EXE)/o) {
				$linkCommand = "$Link $PlatOpt{Ld} -s";	
				if ($BasicTrgType=~/^DLL$/o) {
					$linkCommand .= " $PlatOpt{Entry} _E32Dll -u _E32Dll ".'"${target.data}\\${output.file.root}.exp" --dll ';
				}
				elsif ($BasicTrgType=~/^EXE$/o) {
					$linkCommand .= " $PlatOpt{Entry} _E32Startup -u _E32Startup \ ";
				}
		#		--whole-archive is required here apparently because of a bug in the gcc toolchain
		#		the flag can probably be removed with a later version of gcc

				$linkCommand .= '--base-file "${target.data}\\${output.file.root}.bas" -o "${target.data}\\${output.file.name}" '.
					'${var:FIRST_LIB} --whole-archive "${target.data}\\${output.file.root}.in" '.
					"--no-whole-archive";
				$linkCommand .= ' ${var:COMMON_LINK_FLAGS} ${var:LIBS}';
				addLinkDescriptorCommand ($linkCommand, undef, undef, undef, $FirstLib);

		#		delete temporary files
				if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEXP$/o || $TrgType=~/^EXEDLL$/o) {
					$linkCommand = $deleteCommand.'"${target.data}\\${output.file.root}.exp"';
					addLinkDescriptorCommand ($linkCommand, "false", "false", undef, undef, undef, undef, (0,1));
				}
				$linkCommand = $deleteCommand.'"${target.data}\\${output.file.name}"';
				addLinkDescriptorCommand ($linkCommand, "false", "false");

		#		call dlltool to do base relocations (and dll exports)
				$linkCommand = "$Dlltool $PlatOpt{Dlltool} ";
				if ($BasicTrgType=~/^DLL$/o || $TrgType=~/^EXEXP$/o || $TrgType=~/^EXEDLL$/o) {
					$linkCommand .= '--def "${target.data}\\${output.file.root}.def" '.
						"--dllname \"$LinkAs\" ";
				}
				$linkCommand .= '--base-file "${target.data}\\${output.file.root}.bas" '.
					'--output-exp "${target.data}\\${output.file.root}.exp" ';
				addLinkDescriptorCommand ($linkCommand);

		#		delete temporary files
				$linkCommand = $deleteCommand.'"${target.data}\\${output.file.root}.bas"';
				addLinkDescriptorCommand ($linkCommand, "false", "false");

		#		call ld to link the target
				$linkCommand = "$Link $PlatOpt{Ld}";
				if ($Bld=~/^U?REL$/o) {
					$linkCommand .= " -s";
				}
				if ($BasicTrgType=~/^DLL$/o) {
					$linkCommand .= " $PlatOpt{Entry} $EntrySymbol -u $EntrySymbol --dll ";
				}
				elsif ($BasicTrgType=~/^EXE$/o) {
					$linkCommand .= " $PlatOpt{Entry} $EntrySymbol -u $EntrySymbol ";
				}
		#		--whole-archive is required here apparently because of a bug in the gcc toolchain
		#		the flag can probably be removed with a later version of gcc
				$linkCommand .= '"${target.data}\\${output.file.root}.exp" '.
					'-Map "${output}\\${output.file.name}.map" -o "${target.data}\\${output.file.name}" '.
					'${var:FIRST_LIB} --whole-archive "${target.data}\\${output.file.root}.in" '.
					"--no-whole-archive";
				$linkCommand .= ' ${var:LIBS}';
				addLinkDescriptorCommand ($linkCommand, undef, undef, undef, $FirstLib);

		#		delete temporary files
				$linkCommand = $deleteCommand.'"${target.data}\\${output.file.root}.exp"';
				addLinkDescriptorCommand ($linkCommand, "false", "false");

				if ($Bld=~/DEB$/o) {
					$linkCommand = $Objcopy.' -X "${target.data}\\${output.file.name}" "${output}\\${output.file.root}.sym"';
					addLinkDescriptorCommand ($linkCommand);
				}

				$linkCommand = "petran.exe $PlatOpt{Petran} ".' "${target.data}\\${output.file.name}" "${output}\\${output.file.name}" ';
				if (&main::CompressTarget) {
					$linkCommand .= ' -compress';
				}
				if (&main::AllowDllData) {
					$linkCommand .= ' -allow';
				}
				if (not &main::CallDllEntryPoints) {
					$linkCommand .= ' -nocall';
				}
				if (&main::DataLinkAddress) {
					$linkCommand .= ' -datalinkaddress '.&main::DataLinkAddress;
				}
				if (&main::FixedProcess) {
					$linkCommand .= ' -fixed';
				}
				if (&main::HeapSize) {
					my %HeapSize=&main::HeapSize;
					$linkCommand .= ' -heap '.$HeapSize{Min}.' '.$HeapSize{Max};
				}
				if (&main::ProcessPriority) {
					$linkCommand .= ' -priority '.&main::ProcessPriority;
				}
				if (&main::StackSize) {
					$linkCommand .= ' -stack '.&main::StackSize;
				}
				my $i=1;
				foreach (@UidList) {
					$linkCommand .= " -uid$i $_";
					$i++;
				}
				addLinkDescriptorCommand ($linkCommand, "false");
				
				$linkCommand = $deleteCommand.'"${target.data}\\${output.file.name}"';
				addLinkDescriptorCommand ($linkCommand, "false", "false");
			}
			elsif ($BasicTrgType=~/^LIB$/o) {
				$linkCommand = $copyCommand.'"${target.data}\\${output.file.root}.in" "${var:KIT_EPOCROOT}'.kitRelativePath($StatLinkPath).'${output.file.name}"';
				addLinkDescriptorCommand ($linkCommand,"false", "false");
			}
		}

	if (($CW_major_version >= 2.8) && $addHeaders)
		{
		# Ideally we would do this for all targets, both UREL and UDEB.  This would,
		# however, be very slow - so we just do it for the first target we come to.

		my $cpp = &PreprocessorToUseExe();
		my $cppCommandLine = "$cpp.EXE -M -MG -nostdinc ";
		my $preInclude = "";

		if($VariantFile)
			{	    
		    $preInclude = $VariantFile;
			}

		$cppCommandLine .= '-include '.Path_RltToWork($preInclude).' ' if $preInclude;

		foreach (&main::UserIncPaths, &main::SysIncPaths)
			{
			$cppCommandLine .= '-I '.&Path_Chop(&Path_RltToWork($_)).' ';
			}

		foreach (@MacroList)
			{			
			$cppCommandLine .= '-D'.$_.' ';
			}

		my %srcHash = %{&main::SrcHash};
		my @srcArray;
		
		foreach my $key (keys %srcHash)
			{
			foreach my $file (@{$srcHash{$key}})
				{
				push @srcArray, $key.$file;
				}
			}		

		my %localIncludes;

		foreach my $srcFile (@srcArray)
	   		{
			$file = Path_RltToWork($srcFile);

			# ensure the case of the extension is what GCC expects
			$file =~ s/\.CPP$/.cpp/i;
			$file =~ s/\.C$/.c/i;
			$file =~ s/\.s$/.S/i;

#			print ($cppCommandLine.$file."\n");
			open CPPPIPE,$cppCommandLine.$file." |" or die "ERROR: Can't invoke CPP.EXE\n";

			while (<CPPPIPE>)
				{
				#convert any Unix slashes found in CPP output to DOS slashes
				s/\//\\/g;	
				while (/\.(\.\\|\\){1}\S+\.(hrh|h){1}/gi)
					{
					my $file = $&;
					my $filePath = &main::Path_Split('Path',$file);
						
					# Ignore files that are clearly not local to the project
					next if ($filePath =~ /\\epoc32\\/i);

					# Ignore files that are #included with intermediate directories -
					# we can't guarantee these will be on an Access Path.
					next if ($filePath =~ /\w+\\\.\./);

					# Finally confirm that the file we have is definitely on an Access Path
					my $presentOnAccessPath = 0;
					foreach my $accessPath (&main::UserIncPaths, &main::SysIncPaths)
						{
						my $accessPathCompare = $accessPath;
						$accessPathCompare =~ s/\\/_/g;

						my $filePathCompare = $filePath;
						$filePathCompare =~ s/(\.\\|\.\.\\)//g;
						$filePathCompare =~ s/\\/_/g;

						$presentOnAccessPath = 1 if ($accessPathCompare =~ /$filePathCompare$/i);
						}
					next if (!$presentOnAccessPath);

					# Maintain availability of original case of filename using a lc keyed hash
					my $localInclude = &main::Path_Split('Base',$file).&main::Path_Split('Ext',$file);					
					$localIncludes{lc ($localInclude)} = $localInclude unless (!-e $file);
					}
				}
			}

		foreach my $localInclude (keys %localIncludes)
			{
			addFile($localIncludes{$localInclude}, "Text", 0, "", "Headers");
			}

		$addHeaders = 0;
		}


	# Add DOCUMENT specified files that we know we can add - we only add these for one target,
	# as they should be identical through-out

	if (($CW_major_version >= 2.8) && $addDocuments)
		{
		foreach my $document (@DocList)
			{
			# Only add files as Documents if they haven't already been added to
			# the target (it's not possible to have duplicate entries) and if they
			# have an extension we know about.

			next if (grep (/$document/i, @addedFiles));

			my $extension = $document;
			$extension =~ s/^.*\.//;

			next if (!grep (/$extension/i, @compatibleDOCUMENTExtensions));
			
			addFile($document, "Text", "", "", "Documents");
			}

		$addDocuments = 0;
		}


		$xmlLinkDescriptorCommandParent->addText("\n\t\t\t");
		&main::CreateExtraFile("${ExtraFilesPath}$linkDescriptorFile", $xmlLinkDescriptorDoc->toString);
		addFile($linkDescriptorFile, "Text", "", "", "Link");
        }
	
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
				elsif ($settingname eq "SystemSearchPaths")
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


sub addLinkDescriptorCommand($$;$;$;$;$;$;$;) {		
	my ($linkCommand, $parseStdOut, $parseStdErr, $outputParser, $firstLibProcessing,
	    $linkWarning, $linkInformation, @successCodes) = @_;

	my $structIndent = "\n\t\t\t\t";
	my $settingIndent = "$structIndent\t";
	my $simpleIndent = "$settingIndent\t";
	my $successCodeArrayIndent = $simpleIndent;
	my $successCodeSimpleIndent = "$successCodeArrayIndent\t";

	my $structElement = new XML::DOM::Element($xmlLinkDescriptorDoc,"struct");
	$xmlLinkDescriptorCommandParent->addText("$structIndent");
	$xmlLinkDescriptorCommandParent->appendChild ($structElement);

	my $settingElementTemplate = new XML::DOM::Element($xmlLinkDescriptorDoc,"setting");
	$settingElementTemplate->setAttribute("uuid-alias", ".");
	my $simpleElementTemplate = new XML::DOM::Element($xmlLinkDescriptorDoc,"simple");

	my $settingElement;
	my $simpleElement;

	$settingElement = $settingElementTemplate->cloneNode(0);
	$simpleElement = $simpleElementTemplate->cloneNode(0);
	
	$settingElement->setAttribute ("entry", "linkCommand");
	$structElement->addText ($settingIndent);
	$structElement->appendChild ($settingElement);

	$simpleElement->addText ($linkCommand);

	$settingElement->addText ($simpleIndent);
	$settingElement->appendChild ($simpleElement);
	$settingElement->addText($settingIndent);
	
	if (defined $parseStdOut)
		{
		$settingElement = $settingElementTemplate->cloneNode(0);
		$simpleElement = $simpleElementTemplate->cloneNode(0);

		$settingElement->setAttribute("entry", "parseStdOut");
		$simpleElement->addText($parseStdOut);

		$structElement->addText ($settingIndent);
		$structElement->appendChild ($settingElement);

		$settingElement->addText ($simpleIndent);
		$settingElement->appendChild ($simpleElement);
		$settingElement->addText($settingIndent);
		}
	
	if (defined $parseStdErr)
		{
		$settingElement = $settingElementTemplate->cloneNode(0);
		$simpleElement = $simpleElementTemplate->cloneNode(0);

		$settingElement->setAttribute("entry", "parseStdErr");
		$simpleElement->addText($parseStdErr);

		$structElement->addText ($settingIndent);
		$structElement->appendChild ($settingElement);

		$settingElement->addText ($simpleIndent);
		$settingElement->appendChild ($simpleElement);
		$settingElement->addText($settingIndent);
		}

	if (defined $outputParser)
		{
		$settingElement = $settingElementTemplate->cloneNode(0);
		$simpleElement = $simpleElementTemplate->cloneNode(0);

		$settingElement->setAttribute("entry", "outputParser");
		$simpleElement->addText($outputParser);

		$structElement->addText ($settingIndent);
		$structElement->appendChild ($settingElement);

		$settingElement->addText ($simpleIndent);
		$settingElement->appendChild ($simpleElement);
		$settingElement->addText($settingIndent);
		}

	if (defined $firstLibProcessing)
		{
		$settingElement = $settingElementTemplate->cloneNode(0);
		$simpleElement = $simpleElementTemplate->cloneNode(0);

		$settingElement->setAttribute("entry", "firstLibProcessing");
		$simpleElement->addText($firstLibProcessing);

		$structElement->addText ($settingIndent);
		$structElement->appendChild ($settingElement);

		$settingElement->addText ($simpleIndent);
		$settingElement->appendChild ($simpleElement);
		$settingElement->addText($settingIndent);
		}

	if (defined $linkWarning)
		{
		$settingElement = $settingElementTemplate->cloneNode(0);
		$simpleElement = $simpleElementTemplate->cloneNode(0);

		$settingElement->setAttribute("entry", "linkWarning");
		$simpleElement->addText($linkWarning);

		$structElement->addText ($settingIndent);
		$structElement->appendChild ($settingElement);

		$settingElement->addText ($simpleIndent);
		$settingElement->appendChild ($simpleElement);
		$settingElement->addText($settingIndent);
		}

	if (defined $linkInformation)
		{
		$settingElement = $settingElementTemplate->cloneNode(0);
		$simpleElement = $simpleElementTemplate->cloneNode(0);

		$settingElement->setAttribute("entry", "linkInformation");
		$simpleElement->addText($linkInformation);

		$structElement->addText ($settingIndent);
		$structElement->appendChild ($settingElement);

		$settingElement->addText ($simpleIndent);
		$settingElement->appendChild ($simpleElement);
		$settingElement->addText($settingIndent);
		}

	if (@successCodes)
		{
		$settingElement = $settingElementTemplate->cloneNode(0);
		$settingElement->setAttribute("entry", "successCodes");

		my $arrayElement = new XML::DOM::Element($xmlLinkDescriptorDoc,"array");
		$arrayElement->setAttribute("inheritance", "none");
		
		foreach my $successCode (@successCodes)
			{
			$simpleElement = $simpleElementTemplate->cloneNode(0);
			$simpleElement->addText($successCode);
			$arrayElement->addText ($successCodeSimpleIndent);
			$arrayElement->appendChild ($simpleElement);
			}

		$arrayElement->addText ($successCodeArrayIndent);

		$settingElement->addText ($successCodeArrayIndent);
		$settingElement->appendChild ($arrayElement);
		$settingElement->addText($settingIndent);

		$structElement->addText ($settingIndent);
		$structElement->appendChild ($settingElement);
		}

	$structElement->addText($structIndent);
}
	

sub ExtraPlat($) {

# Call PmBld again after reprocessing the MMP file and tweaking various main:: variables

	my ($Plat) = @_;

	&main::SetVarsFromMmp($Plat);
#	&main::InitLinkPaths();
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

	my $subElement = new XML::DOM::Element($xmlProjectDoc,$name);
	$subElement->appendChild($xmlProjectDoc->createTextNode($value));
	$element->insertBefore($subElement, $insertionpoint);
}

sub addFile($$$$;$) {    

	my ($src, $kind, $debug, $shared, $group) = @_;

	my $linkElement = new XML::DOM::Element($xmlProjectDoc,"FILEREF");

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

	push (@addedFiles, $src) unless ($kind eq "Documents");

	if ($kind eq "Library")
		{
		$xmlLibGroup->appendChild($groupfile);
		$xmlLibGroup->addText("\n");
		}
	elsif (defined $group)
		{
		if ($group eq "Link")
			{
			$xmlLinkGroup->appendChild($groupfile);
			$xmlLinkGroup->addText("\n");
			}
		elsif ($group eq "Resources")
			{
			$xmlResourcesGroup->appendChild($groupfile);
			$xmlResourcesGroup->addText("\n");
			}
		elsif ($group eq "Root")
			{
			$xmlRootGroup->appendChild($groupfile);
			$xmlRootGroup->addText("\n");
			}
		elsif ($group eq "Headers")
			{
			$xmlHeadersGroup->appendChild($groupfile);
			$xmlHeadersGroup->addText("\n");
			}
		elsif ($group eq "Documents")
			{
			$xmlDocumentsGroup->appendChild($groupfile);
			$xmlDocumentsGroup->addText("\n");
			}
		}
	else
		{
		$xmlSourceGroup->appendChild($groupfile);
		$xmlSourceGroup->addText("\n");
		}
}

sub addGroup($$) {
	my ($grouplist,$name)=@_;

	my $group = new XML::DOM::Element($xmlProjectDoc,"GROUP");
	$grouplist->appendChild($group);
	$grouplist->addText("\n");

	&textElement($group, "NAME", $name);
	$group->addText("\n");
	return $group;
}

sub addSubTarget($$) {
	my ($subtargetlist,$name)=@_;

	my $subtarget = new XML::DOM::Element($xmlProjectDoc,"SUBTARGET");
	$subtargetlist->appendChild($subtarget);
	$subtargetlist->addText("\n");

	&textElement($subtarget, "TARGETNAME", $name);
}

sub addOrderedTarget($$) {
	my ($targetorder,$name)=@_;

	my $orderedtarget = new XML::DOM::Element($xmlProjectDoc,"ORDEREDTARGET");
	$targetorder->appendChild($orderedtarget);
	$targetorder->addText("\n");

	&textElement($orderedtarget, "NAME", $name);
}

sub finaliseProject {

	# Run through the project, removing all unused targets
	# and build up the TARGETORDER list and the "Build All" target

	my $target;
	my $targetname;

	my $xmlSubTargetList = new XML::DOM::Element($xmlProjectDoc,"SUBTARGETLIST");

	my $xmlTargetOrder = new XML::DOM::Element($xmlProjectDoc,"TARGETORDER");
	$xmlTargetOrder->addText("\n");

	my @targets = $xmlProjectDoc->getElementsByTagName("TARGET",1);
	my @emulatortargetnames;
	my @othertargetnames;

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

			if ($targetname =~ /^WINSCW/)
				{
				push (@emulatortargetnames, $targetname);
				}
			else
				{
				push (@othertargetnames, $targetname);
				}
			}
		}

	foreach $targetname ((sort @emulatortargetnames), (sort @othertargetnames))
		{
		&addSubTarget($xmlSubTargetList, $targetname);
		&addOrderedTarget($xmlTargetOrder, $targetname);
		}


	# Build the GROUPLIST
	
	my $xmlGroupList = new XML::DOM::Element($xmlProjectDoc,"GROUPLIST");

	# Build the "Root" group

	if ($CW_major_version >= 2.8)
		{
		my %rootfiles;
		my @rootgroups = $xmlProjectDoc->getElementsByTagName("ROOTGROUP",1);
		foreach my $group (@rootgroups)
			{
			$targetname = $group->getAttribute("TARGET");
			my @files = $group->getElementsByTagName("FILEREF",0);
			foreach my $file (@files)
				{
				my $name = $file->getAttribute("NAME");
				if (!defined $rootfiles{$name})
					{
					# first occurrence - add to list
					$rootfiles{$name}=1;
					&textElement($file, "TARGETNAME", $targetname, $file->getFirstChild);
					$file->removeAttribute("NAME");
					&disconnectNode($file);					
					$xmlGroupList->appendChild($file);
					$xmlGroupList->addText("\n");
					}
				}
			&removeNode($group);
			}
		}

	# Build the "Source" group

	my $xmlSourceGroup = &addGroup($xmlGroupList,"Source");
	my %sourcefiles;
	my @sourcegroups = $xmlProjectDoc->getElementsByTagName("SOURCEGROUP",1);
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


	# Build the "Headers" group
		
	if ($CW_major_version >= 2.8)
		{			
		my $xmlHeadersGroup;
		my %headerfiles;
		my @headersgroups = $xmlProjectDoc->getElementsByTagName("HEADERSGROUP",1);
		foreach my $group (@headersgroups)
			{
			$targetname = $group->getAttribute("TARGET");
			my @files = $group->getElementsByTagName("FILEREF",0);
			foreach my $file (@files)
				{
				# Only create the "Headers" group if there are some files to add to it
				if (!defined $xmlHeadersGroup)
					{
					$xmlHeadersGroup = &addGroup($xmlGroupList,"Headers");
					}
			
				my $name = $file->getAttribute("NAME");
				if (!defined $headerfiles{$name})
					{
					# first occurrence - add to list
					$headerfiles{$name}=1;
					&textElement($file, "TARGETNAME", $targetname, $file->getFirstChild);
					$file->removeAttribute("NAME");
					&disconnectNode($file);
					$xmlHeadersGroup->appendChild($file);
					$xmlHeadersGroup->addText("\n");
					}
				}
			&removeNode($group);
			}
		}


	# Build the "Resources" group
			
	my $xmlResourcesGroup;
	my %resourcesfiles;
	my @resourcesgroups = $xmlProjectDoc->getElementsByTagName("RESOURCESGROUP",1);
	foreach my $group (@resourcesgroups)
		{
		$targetname = $group->getAttribute("TARGET");
		my @files = $group->getElementsByTagName("FILEREF",0);
		foreach my $file (@files)
			{
			# Only create the "Resources" group if there's some .resources files
			# to add to it
			if (!defined $xmlResourcesGroup)
				{
				$xmlResourcesGroup = &addGroup($xmlGroupList,"Resources");
				}
				
			my $name = $file->getAttribute("NAME");
			if (!defined $resourcesfiles{$name})
				{
				# first occurrence - add to list
				$resourcesfiles{$name}=1;
				&textElement($file, "TARGETNAME", $targetname, $file->getFirstChild);
				$file->removeAttribute("NAME");
				&disconnectNode($file);
				$xmlResourcesGroup->appendChild($file);
				$xmlResourcesGroup->addText("\n");
				}
			}
		&removeNode($group);
		}


	# Build the "Link" group

	if ($CW_major_version >= 2.8)
		{			
		my $xmlLinkGroup = &addGroup($xmlGroupList,"Link");
		my %linkfiles;
		my @linkgroups = $xmlProjectDoc->getElementsByTagName("LINKGROUP",1);
		foreach my $group (@linkgroups)
			{
			$targetname = $group->getAttribute("TARGET");
			my @files = $group->getElementsByTagName("FILEREF",0);
			foreach my $file (@files)
				{
				my $name = $file->getAttribute("NAME");
				if (!defined $linkfiles{$name})
					{
					# first occurrence - add to list
					$linkfiles{$name}=1;
					&textElement($file, "TARGETNAME", $targetname, $file->getFirstChild);
					$file->removeAttribute("NAME");
					&disconnectNode($file);
					$xmlLinkGroup->appendChild($file);
					$xmlLinkGroup->addText("\n");
					}
				}
			&removeNode($group);
			}
		}


	# Build the "Documents" group

	if ($CW_major_version >= 2.8)
		{
		my $xmlDocumentsGroup;
		my %documentfiles;
		my @documentgroups = $xmlProjectDoc->getElementsByTagName("DOCUMENTSGROUP",1);
		foreach my $group (@documentgroups)
			{
			$targetname = $group->getAttribute("TARGET");
			my @files = $group->getElementsByTagName("FILEREF",0);
			foreach my $file (@files)
				{				
				# Only create the "Documents" group if there are some files to add to it
				if (!defined $xmlDocumentsGroup)
					{
					$xmlDocumentsGroup = &addGroup($xmlGroupList,"Documents");
					}

				my $name = $file->getAttribute("NAME");

			
				if (!defined $documentfiles{$name})
					{
					# first occurrence - add to list
					$documentfiles{$name}=1;
					&textElement($file, "TARGETNAME", $targetname, $file->getFirstChild);
					$file->removeAttribute("NAME");
					&disconnectNode($file);
					$xmlDocumentsGroup->appendChild($file);
					$xmlDocumentsGroup->addText("\n");
					}
				}
			&removeNode($group);
			}
		}


	# Build the "Lib" group and its subgroups

	my $xmlLibGroup = &addGroup($xmlGroupList, "Libraries");
	my %libplats;
	my @libgroups = $xmlProjectDoc->getElementsByTagName("LIBGROUP",1);
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

	my $node = $xmlProjectDoc->getElementsByTagName("GROUPLIST",1)->item(0);
	$node->getParentNode->replaceChild($xmlGroupList, $node);

	$node = $xmlProjectDoc->getElementsByTagName("TARGETORDER",1)->item(0);
	$node->getParentNode->replaceChild($xmlTargetOrder, $node);

	# Insert the "Build All" target

	my $xmlBuildAll = new XML::DOM::Element($xmlProjectDoc,"TARGET");
	$xmlBuildAll->addText("\n");
	&textElement($xmlBuildAll, "NAME", "Build All");
	my $settinglist = new XML::DOM::Element($xmlProjectDoc,"SETTINGLIST");
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

	$node = $xmlProjectDoc->getElementsByTagName("TARGETLIST",1)->item(0);
	$node->appendChild($xmlBuildAll);

	# Output the result

	&main::Output(
		$xmlProjectDoc->toString
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
