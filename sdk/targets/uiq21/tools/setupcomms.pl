#
# Launcher for the Symbian Emulator, including
# functionality to read the $ENV{EPOCROOT}epoc32\data\BuildInfo.txt
# file to find out information regarding the current Emulator.
#
# Copyright (c) 1999-2001 UIQ Technology.  All rights reserved.
#
# Depends on the current working directory providing
# the drive of the currently used SDK.
#

use Cwd;
use Getopt::Long;
Getopt::Long::Configure ("bundling_override", "pass_through"); 

GetOptions ('winscw|cw' => \$winscw,
		'wins' => \$wins,
		'deb|udeb' => \$deb,
		'rel|urel' => \$rel,
		#'240' => sub {$option='-MstandardQ--'},
		#'console|con' => sub {$option='-Mconsole--'},
		'verbose|v' => \$verbose,
		'version|ver' => \$version,
		'help|h|?' => \$help,
		'test' => \$test);

$option='-Mconsole--'; #T_editdb must be run in console mode.
foreach $a (@ARGV){$option="$option $a";}


if($winscw&&$wins||$udeb&&$urel) {
	print "Error: More than one emulator specified.\n";
	exit 1;
	}

$help && &printHelp;
$version && &printVersion;

$epocroot = &getEpocroot;
$drive = &getDrive;

!$wins && !$rel && push @try_this, $drive . $epocroot . "epoc32\\release\\winscw\\udeb\\T_editdb.exe";       		
!$wins && !$deb && push @try_this, $drive . $epocroot . "epoc32\\release\\winscw\\urel\\T_editdb.exe";
!$winscw && !$rel && push @try_this, $drive . $epocroot . "epoc32\\release\\wins\\udeb\\T_editdb.exe";
!$winscw && !$deb && push @try_this, $drive . $epocroot . "epoc32\\release\\wins\\urel\\T_editdb.exe";
	
foreach $path (@try_this)
{
	if (-e ($path))
	{
		$verbose && print "Starting $path $option\n";
		if (!$test) {
			exec("\"" . $path . " " . $option . " " . @ARGV . "\"") || (die "Failed to execute the emulator \"$path\": $!");
		}
		
		exit 0
	}	
}
# This will never execute if emulator launch is sucsessfull.
die "ERROR: File \"pepoc.exe\" not found.\n\n" .
	"The EPOCROOT environment variable does not identify\n" .
	"a valid Symbian emulator installation on this drive.\n" . 
	"EPOCROOT must be an absolute path to an existing\n" .
	"directory - it should have no drive qualifier and\n" .
	"must end with a backslash.\n";


sub printHelp
{
    print "Symbian Platform Emulator Launcher\n";
    print "Syntax :\tepoc [-rel] [-wins|-winscw] [-version] [-help] [-verbose|v]\n";
    print "(no options)\tLaunch active winscw debug emulator\n";
    print "-rel\t\tLaunch active release emulator\n";
    print "-wins\t\tLaunch active wins emulator\n";
    print "-winscw\t\tLaunch active winscw emulator\n";
    print "-version\tDisplay active emulator details\n";
    print "-help\tOutput this help message\n";
    print "-verbose\tOutput full path to launched emulator\n";
    exit 0;
}


sub printVersion
{
    my $epocroot = &getEpocroot;
    my $drive = &getDrive;

    my $binfo = $drive . $epocroot . "epoc32" . "\\" 
	        . "data" . "\\" . "BuildInfo.txt";

    -e $binfo || die "ERROR: File \"" . $binfo . "\" does not exist.\n";
    open(IFILE, $binfo) ||
	die "ERROR: Failed to open file \"" . $binfo . "\": $!";

    my $DeviceFamily = "";
    my $DeviceFamilyRev = "";
    my $ManufacturerSoftwareRev = "";
    my $ManufacturerSoftwareBuild = "";

    while(<IFILE>) {
	if(/DeviceFamily\s+(.*\S)\s*$/i) {
	    $DeviceFamily = $1;
	}
	if(/DeviceFamilyRev\s+(.*\S)\s*$/i) {
	    $DeviceFamilyRev = $1;
	}
	if(/ManufacturerSoftwareRev\s+(.*\S)\s*$/i) {
	    $ManufacturerSoftwareRev = $1;
	}
	if(/ManufacturerSoftwareBuild\s+(.*\S)\s*$/i) {
	    $ManufacturerSoftwareBuild = $1;
	}
    }

    close(IFILE);

    #
    # Verify that we got everything we should have.
    #
    $DeviceFamily ne "" ||
	die "ERROR: Device family not specified in file \"" . $binfo .
	    "\".\n";
    $DeviceFamilyRev ne "" ||
	die "ERROR: Device family revision not specified in file \"" . $binfo .
	    "\".\n";
    $ManufacturerSoftwareBuild ne "" ||
	die "ERROR: Manufacturer software build not specified in file \"" .
	    $binfo . "\".\n";

    $Revision = (($ManufacturerSoftwareRev eq "")?($DeviceFamilyRev):
		 ($ManufacturerSoftwareRev));

    $DeviceFamily = getDFRDName($DeviceFamily);

    #
    # Make the standard revision representation prettier,
    # but leave other representations untouched.
    #
    if($Revision =~ /^0x([0-9])([0-9][0-9])$/) {
	$Revision = $1 . "." . $2;
    }
   
    print $DeviceFamily . " " .
	"version " . $Revision . " " .
	    "build " . $ManufacturerSoftwareBuild . "\n";
exit 0;
}

#
# Determines, validates, and returns EPOCROOT.
#
sub getEpocroot
{
    my $epocroot = $ENV{EPOCROOT};
    die "ERROR: Must set the EPOCROOT environment variable.\n"
	if (!defined($epocroot));
    $epocroot =~ s-/-\\-go;	# for those working with UNIX shells
    die "ERROR: EPOCROOT must be an absolute path, " .
	"not containing a drive letter.\n" if ($epocroot !~ /^\\/);
    die "ERROR: EPOCROOT must not be a UNC path.\n" if ($epocroot =~ /^\\\\/);
    die "ERROR: EPOCROOT must end with a backslash.\n" if ($epocroot !~ /\\$/);
    die "ERROR: EPOCROOT must specify an existing directory.\n" 
	if (!-d $epocroot);
    return $epocroot;
}

#
# Determines and returns the current drive, if any.
#
sub getDrive
{
    my $wd = cwd;
    my $drive;
    if($wd =~ /^([a-zA-Z]:)/) {
	$drive = $1;
    } else {
	# Perhaps we're on a machine that has no drives.
	$drive = "";
    }
    return $drive;
}

#
# The DFRD may be represented by a numeric value, as defined by HAL.
# Changes known numeric values to the name of the DFRD,
# and leaves all other values untouched.
#
sub getDFRDName
{
    my $dfrd = shift;
    return "Crystal" if $dfrd eq "0";
    return "Pearl" if $dfrd eq "1";
    return "Quartz" if $dfrd eq "2";
    return $dfrd; # as fallback
}
