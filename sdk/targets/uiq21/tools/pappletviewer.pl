#
# Pappletviewer Launcher
#
# Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
#

use Cwd;

$numArgs = $#ARGV + 1;
if($numArgs == 0) 
	{
    	&launchPAppletViewer("winscw");
    	exit(0);
	}

if($numArgs > 1) 
	{
    	&printHelp;
    	die "ERROR: Too many arguments.\n";
	}

if(lc($ARGV[0]) eq "-winscw") 
	{
    	&launchPAppletViewer("winscw");
    	exit(0);
	}


if(lc($ARGV[0]) eq "-wins") 
	{
    	&launchPAppletViewer("wins");
    	exit(0);
	}

if(lc($ARGV[0]) eq "-help") 
	{
    	&printHelp;
    	exit(0);
	}

# Error, unknown argument.
&printHelp;
die "ERROR: Unknown argument " . "\"" . $ARGV[0] . "\".\n";


sub launchPAppletViewer
	{
	my $type = shift;
	$epocroot = &getEpocroot;
	$drive = &getDrive;
	$pappletviewer = $drive . $epocroot . "epoc32" . "\\" . "release\\" .$type. "\\urel\\pappletviewer.exe";

	-e $pappletviewer || die 	"ERROR: File \"$pappletviewer\" not found.\n\n" .
	    			"The EPOCROOT environment variable does not identify\n" .
	    			"a valid pappletviewer.exe installation on this drive.\n" . 
					"EPOCROOT must be an absolute path to an existing\n" .
		    		"directory - it should have no drive qualifier and\n" .
					"must end with a backslash.\n";

	# Append any command line arguments
	for ($i = 0; $i < $numArgs; $i++)
		{
		$pappletviewer .= " \"" . $ARGV[$i] ."\"";
		}
	

	# Run pappletviewer
	system ($pappletviewer);
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

    if($wd =~ /^([a-zA-Z]:)/)
    	{
		$drive = $1;
    	}
    else
    	{
		# Perhaps we're on a machine that has no drives.
		$drive = "";
    	}
    return $drive;
	}


sub printHelp
{
    print "PAppletViewer Launcher\n";
    print "Syntax :\tpappletviewer [-winscw|wins] [-help]\n";
    print "(no options)\tLaunch active winscw pappletviewer executable\n";
    print "-winscw\t\tLaunch active winscw pappletviewer executable\n";
    print "-winscw\t\tLaunch active wins pappletviewer executable\n";
    print "-help\t\tOutput this help message\n";
}
