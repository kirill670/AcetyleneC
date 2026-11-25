# bsp.pl (c) Symbian 2001

use ExtUtils::Command;
use Win32;

if (@ARGV < 3)
{
  print ("Not enough arguments\n\n");
  Usage ();
}

# Collect command line arguments

use Getopt::Std;
if (!getopts("zvdmf:be")) { Usage (); };

# Validate command line argumets
if ($opt_m and $opt_d) 	 { Usage (); };
if (!$opt_m and !$opt_d) { Usage (); };
if ($opt_b and $opt_e)	 { Usage (); };

# Check development and reference directories are sane

$dev_dir = Win32::GetFullPathName(@ARGV[1]);
$ref_dir = Win32::GetFullPathName(@ARGV[0]);
if (!($ref_dir cmp "" && $dev_dir cmp "")) { 
	die ("Development and Reference directories needed\n"); 
}

if (!($dev_dir cmp $ref_dir)) { die ("Duplicate directories: $dev_dir\n"); }
if (!-d $dev_dir) { die ("$dev_dir is not a directory\n"); }
if (!-d $ref_dir) { die ("$ref_dir is not a directory\n"); }

$dev_dir = uc $dev_dir;
$ref_dir = uc $ref_dir;

if ($opt_e) {
	$opt_b = 1;
	$dev_dir = "$dev_dir\\BIN\\TECHVIEW\\EPOC32";
	$ref_dir = "$ref_dir\\BIN\\TECHVIEW\\EPOC32";
}

$metawritten = 0; # Has anything been written to the meta datafile?
$Output = ($opt_f ? $opt_f : "bsp.met");  
$SDKid = "";
$SDKpath = "";
$IPRFile = "DISTRIBUTION.POLICY";

# Globals for CompLists()

@List1; 
@List2; 
$Path1 = $ref_dir;
$Path2 = $dev_dir;

# Start the directory comparision with the current values of $Path1 and $Path2

FlagDifferences (1);

if ($metawritten) { 
	print OUTPUT ("</manifest>\n</packagedef>\n");
	close(OUTPUT);
}

# Any files missing in the dev tree found?

foreach $name (@MissingFiles) {
	print("$name missing\n");
}

exit;

#####################################################
# GetCategory                                       #
#####################################################
sub GetCategory
{
	my $Buffer1;
	my $Buffer2; 
	my $RetVal1;
	my $RetVal2;
	open (CATFILE, "@_[0]") or return -2;

	$RetVal1 = read (CATFILE, $Buffer1, 9);

 	$RetVal2 = read (CATFILE, $Buffer2, 1);
	close (CATFILE);

	if (($RetVal1 != 9) || ($RetVal2 != 1) || ($Buffer1 cmp "Category ")) {
		print ("@_[0] bad content\n");
		return -1;
	} 
	return $Buffer2;

}


#####################################################
# Function GetIPRMsg                                #
#####################################################
sub GetIPRMsg
{
	if ($opt_z) { return""; }
	my ($refpath, $devpath) = @_;

	my $refcat = GetCategory("$refpath\\$IPRFile");
	my $devcat = GetCategory("$devpath\\$IPRFile");

	if ($refcat < 0) {
		return "";
	}
	if (!grep(/$refcat/, A,B,C,D,E,F,G)) {
		print("$refpath\\$IPRFile bad category: $refcat\n");
		return "";
	}
	if ($devcat == -2) {
		print("$devpath\\$IPRFile missing\n");
		return "";
	}
	if ($devcat == -1) {
		return "";
	}
	if (!grep(/$devcat/, A,B,C,D,E,F,G)) {
		print("$devpath\\$IPRFile bad category: $devcat\n");
		return "";
	}
	my $comp = $devcat cmp $refcat;

	if ($comp < 0) {
		print("$devpath\\$IPRFile IPR promotion $refcat -> $devcat\n");
		return "(IPR promotion $refcat -> $devcat)";
	}
	if ($comp > 0) {
		print("$devpath\\$IPRFile IPR demotion $refcat -> $devcat\n");
		return "(IPR demotion $refcat -> $devcat)";
	}
	return "";
}
		

#####################################################
# Function GetIDFromInstalled2                      #
#####################################################
sub GetIDFromInstalled2
{

	use XML::Parser::Expat;
	$parser = new XML::Parser::Expat;
 
	$parser->setHandlers('Start' => \&CatchElements,
			     'Char'  => \&CatchDummy);
	open(I2, "@_[0]") or Stop("Could not open @_[0]: $!");
	$parser->parse(*I2);
	close(I2);
	if (($SDKid cmp "") == 0) {
		Stop ("Cannot find $dev_dir in list of installed devkits");
	}
}

sub CatchDummy {}
 
#####################################################
# Function CatchSdkElements                         #
#####################################################
sub CatchElements
{
	my ($p, $el, %atts) = @_;
	if (($el cmp "sdk") == 0) {
		$SDKid = $atts{id};
	} 
	elsif (($el cmp "sdk-path") == 0) {
		$p->setHandlers('Char' => \&CatchSdkPath);
	}
 }

#####################################################
# Function CatchSdkPath                             #
#####################################################
sub CatchSdkPath
{
   	my ($p, $Path) = @_;
	
	$Path =~ s/\\\\/\\/g;
	if (((uc $Path) cmp (substr($dev_dir,0,length($Path)))) !=0 ) {
		$SDKid = "";
	}
	else {
		# Found a matching SDK path, so no need to look at the
		# rest of the installed2 file.
		$SDKpath = $Path;
		$parser->setHandlers('Start' => \&CatchDummy);
	}
	$p->setHandlers('Char' => \&CatchDummy);
     
}

#####################################################
# Function GetSdkID                                 #
#####################################################
sub GetSdkID
{

	use Win32API::Registry 0.13 qw( :ALL );

	my $ENVIRONMENT_KEY = "Software\\Symbian\\EPOC SDKs";
	my $VALUE = "CommonPath";

	my $type = 0;
	my $key = 0;
	my $data ='';

	RegOpenKeyEx( HKEY_LOCAL_MACHINE, $ENVIRONMENT_KEY, 0, KEY_READ, $key );
	if($key) {
		RegQueryValueEx( $key, $VALUE, [], $type, $data, [] );
		if ($key) { 
			RegCloseKey( $key ) 
		} else { 
			Stop("Can't read HKEY_LOCAL_MACHINE\\$ENVIRONMENT_KEY\\$VALUE");
		}
	} else {
     		Stop("Can't open HKEY_LOCAL_MACHINE\\$ENVIRONMENT_KEY $!");
	}

	GetIDFromInstalled2("$data\\installed2.xml");
}

#####################################################
# WriteMetaHeader                                   #
#####################################################
sub WriteMetaHeader
{
	GetSdkID(); # leaves ID in $SDKid
	open (OUTPUT, ">$Output") or Stop ("Can't open $Output): $!\n");

	# Write the header (part 1)
	print OUTPUT <<EOF;
<?xml version="1.0" encoding="UTF-8"?>
<packagedef version="1.0">
<package name="com.symbian.bsptemplate" 
	major-version="0" minor-version="0" build-number="0">
<supplier>template supplier</supplier>
<description>template description</description>
EOF
	print OUTPUT ("<sdk-version>$SDKid</sdk-version\>\n");
	# Write header (part 2)
	print OUTPUT <<EOF;
<category>BSP</category>
<dependencies>
<dependency name="com.symbian.devkit.hardware" major-version="0" minor-version="0" build-number="0"/>
</dependencies>
</package>
<manifest>
EOF
}
	
#####################################################
# Function AddFileToArchive                         #
#   Writes the content of a file into the archive.  #
#                                                   #
#   This function is called by CompLists,           #
#   CompContent, and AddDirToArchive with 2         #
#   parameters : the SubPath of                     #
#   the file and the file name.                     #
#####################################################
sub AddFileToArchive
{

#	Why was this here?
#	if (!$opt_m) { return };
	if (!$metawritten) {
		WriteMetaHeader();
		$metawritten = 1;
	}
		
	my $Path = "@_[0]\\@_[1]";
	if ($opt_v) {
		printf("New/Modified: $Path %s\n", 
		    FileIsToBeLeftOut(@_[1]) ? "excluded" : "included");
	}
	print OUTPUT ( "<item src=\"$Path\" dest=",
		       "\"\[sdkroot\]",
		       substr($Path, length($SDKpath)),
		       "\"/>\n"); 
  
}


#####################################################
# Function AddDirToArchive                          #
#   Writes the content of a dir into the archive.   #
#                                                   #
#   This function is called by CompLists and        #
#   CompContent with 2 parameters : the SubPath of  #
#   the dir and the dir name.		      	    #
#####################################################
sub AddDirToArchive
{

  my $DirTemp = "@_[0]\\@_[1]";
  opendir (DIRTEMP, $DirTemp) or Stop ("Can't open directory $DirTemp: $!");

  # Store the seek pointer so DIRTEMP can be scanned twice
  #
  my $HeadDirTemp = telldir (DIRTEMP);
  
  # Creating lists containing the files in the directory.
  #
  my @FilesListTemp = grep {-f "$DirTemp\\$_"} readdir(DIRTEMP);
  seekdir (DIRTEMP, $HeadDirTemp) or Stop ("Can't seekdir $DirTemp: $!");
  my @DirListTemp = grep {!(/^\./) && !(-f "$DirTemp\\$_")} readdir (DIRTEMP);
  closedir (DIRTEMP);

  # Make pathnames upper case for consistency
  #
  @FilesListTemp = sort (map (uc ($_), @FilesListTemp));
  @DirListTemp = sort (map (uc ($_), @DirListTemp));

  my $IndexTemp = 0;
  while (($FilesListTemp[$IndexTemp] cmp "") != 0) {
    if (!($FilesListTemp[$IndexTemp] cmp "DISTRIBUTION.POLICY")) {
		# CheckCategory("$DirTemp\\$FilesListTemp[$IndexTemp]");
    } 
    AddFileToArchive ($DirTemp, $FilesListTemp[$IndexTemp]);
    $IndexTemp ++;
  }
  
  $IndexTemp = 0;
  while (($DirListTemp[$IndexTemp] cmp "") != 0) {
    AddDirToArchive ($DirTemp, $DirListTemp[$IndexTemp]);
    $IndexTemp ++;
  }
}
  
#####################################################
# Function CompContent                              #
#   Compare the content of 2 files.                 #
#                                                   #
#   This function is called by CompLists with       #
#   3 parameters : the 2 concerned directories      #
#   and the file name.				    #
#####################################################
sub CompContent
{
	use File::Compare;

	my ($Directory1, $Directory2, $Filename, $IPRMsg) = @_;

	my $File1 = sprintf ("%s\\%s", $Directory1, $Filename);
	my $File2 = sprintf ("%s\\%s", $Directory2, $Filename);

	if (compare($File1, $File2) != 0 ) {
		print ("$File2 modified $IPRMsg\n");
    		AddFileToArchive ($Directory2, $Filename);
	}
}

#####################################################
# Function FileIsToBeLeftOut                        #
#   Checks if the parameter file is a file          #
#   corresponding to the -b option file extensions. #
#####################################################
sub FileIsToBeLeftOut
{
	if ($opt_b) { return 0; }

	my @ExtL = split (/[.]/, reverse (@_[0]));
	my $Ext = uc (reverse (@ExtL[0]));

	if (!($Ext cmp "OBJ") || 
	    !($Ext cmp "O") ||
	    !($Ext cmp "DLL") ||
	    !($Ext cmp "LIB") || 
	    !($Ext cmp "BIN") || 
	    !($Ext cmp "MAKEFILE") ||
	    !($Ext cmp "MAP") ||
	    !($Ext cmp "PDB")) { 
		return 1; 
	}
	return 0;
}

#####################################################
# Function CompLists                                #
#   Compare 2 lists, either 2 Files Lists or 2 Dir  #
#   Lists.                                          #
#                                                   #
#   This function is called by FlagDifferences with #
#   3 parameters : whether this is a File List or a #
#   Dir List comparison, and the 2 concerned        #
#   directories. The lists themselves are           #
#   stored in the globals @List1 and @List2.        #
#####################################################
sub CompLists
{
  # Parameter
  #
  my ($CompFiles, $Dir1_l_l, $Dir2_l_l) = @_;

  # Local Variables
  #
  my $Index1 = 0;
  my $Index2 = 0;
  my $Continue = (((@List1[$Index1] cmp "") != 0) || 
                  ((@List2[$Index2] cmp "") != 0));
  my $CmpRes;
  my $IPRMsg;

  # Local copies needed for recursion
  #
  my @List1_l = grep (!/^$IPRFile/, @List1); # REFERENCE   tree
  my @List2_l = grep (!/^$IPRFile/, @List2); # DEVELOPMENT tree

  if ($CompFiles) {
	$IPRMsg = GetIPRMsg($Dir1_l_l, $Dir2_l_l);
  }


  while ($Continue)
  {
    $CmpRes = @List1_l[$Index1] cmp @List2_l[$Index2];
    if (!$CmpRes) {
	if ($CompFiles) {
	  if (!FileIsToBeLeftOut (@List1_l[$Index1])) {
            CompContent ($Dir1_l_l, $Dir2_l_l, @List1_l[$Index1], $IPRMsg);
	  }
	} 
	else {
          $Path1 = sprintf ("%s\\%s", ($Dir1_l_l,@List1_l[$Index1]));
          $Path2 = sprintf ("%s\\%s", ($Dir2_l_l,@List2_l[$Index2]));
          FlagDifferences (0);
	}

      $Index1 ++;
      $Index2 ++;
    }
    elsif ($CmpRes < 0) { # there are items only in the REF tree only
	while ((@List1_l[$Index1] cmp "") && 
	       ((@List1_l[$Index1] cmp @List2_l[$Index2]) < 0))
	{
		push @MissingFiles, sprintf("$Dir1_l_l\\@List1_l[$Index1]%s", $CompFiles ? "" : "\\");
	    $Index1 ++;
	}
    }
    else { #i.e ($CmpRes > 0) there are items in the DEV tree only
	  while ((@List2_l[$Index2] cmp "") && 
		((@List1_l[$Index1] cmp @List2_l[$Index2]) > 0))
	  {
	    if ($CompFiles) {
		if (!FileIsToBeLeftOut (@List2_l[$Index2])) {

		  print("$Dir2_l_l\\@List2_l[$Index2] new\n");
		  if (!(@List2_l[$Index2] cmp "DISTRIBUTION.POLICY")) {
		    CheckCategory (sprintf ("%s\\%s", $Dir2_l_l, @List2_l[$Index2]));
		  }
		  AddFileToArchive ($Dir2_l_l, @List2_l[$Index2]);
		}
	    } else {
		print("$Dir2_l_l\\@List2_l[$Index2]\\ new\n");
		AddDirToArchive ($Dir2_l_l, @List2_l[$Index2]);
	    }
	    $Index2 ++;
	  }
    }

    # If reference tree list exhausted then deal with remaining items
    # in the development tree list here.
    #
    if ((@List1_l[$Index1] cmp "") == 0)
    {
      while ((@List2_l[$Index2] cmp "") != 0)
      {
	  if ($CompFiles) {
	    if (!FileIsToBeLeftOut (@List2_l[$Index2])) {
	      print("$Dir2_l_l\\@List2_l[$Index2] new\n");

	      if (!(@List2_l[$Index2] cmp "DISTRIBUTION.POLICY")) {
		  CheckCategory (sprintf ("%s\\%s", $Dir2_l_l, @List2_l[$Index2]));
	      }

	      AddFileToArchive ($Dir2_l_l, @List2_l[$Index2]);
	    }
	  } else {
	      print("$Dir2_l_l\\@List2_l[$Index2]\\ new\n");
 	      AddDirToArchive ($Dir2_l_l, @List2_l[$Index2]);
	  }
	
	  $Index2 ++;
      }
      $Continue = 0;
    }

    # If the development tree list is exhausted then report the remaining
    # reference tree itens as missing in the development tree

    if ((@List2_l[$Index2] cmp "") == 0) {
	while ((@List1_l[$Index1] cmp "") != 0) {
		push @MissingFiles, sprintf("$Dir1_l_l\\@List1_l[$Index1]%s", $CompFiles ? "" : "\\");

		$Index1 ++;
	}
	$Continue = 0;
    }
  }
}

#####################################################
# Function FlagDifferences                          #
#   Flag the differences between two directories    #
#   and recursively check every directory included. #
#                                                   #
#   The directories being compared are stored in    #
#   variables $Path1 and $Path2                     #
#####################################################
sub FlagDifferences
{
  # Local Variables : don't get changed when the recursive call returns
  #
  my @FilesList1_l;
  my @DirList1_l;
  my @FilesList2_l;
  my @DirList2_l;

  # Local Variable : is 1 if the function is called for the first time
  # is 0 otherwise. If have to do special treatment when the function is
  # called the first time
  #
  my $First_l = @_[0];
  
  # Opens Directories
  #
  opendir (DIR1, $Path1) or Stop ("Can't open directory $Path1: $!");
  opendir (DIR2, $Path2) or Stop ("Can't open directory $Path2: $!");
  
  # Store the seek pointer to the beginning of the list
  # so that we can scan it twice to create FilesList and DirList

  $HeadDir1 = telldir (DIR1);
  $HeadDir2 = telldir (DIR2);
  
  # Creating lists containing the files in the directory.
  #
  @FilesList1_l = grep {-f "$Path1\\$_"} readdir(DIR1);

  seekdir (DIR1, $HeadDir1) or Stop ("Can't seekdir $Path1: $!");
  @DirList1_l = grep {!(/^\./) && !(-f "$Path1\\$_")} readdir (DIR1);
  
  @FilesList2_l = grep {-f "$Path2\\$_"} readdir(DIR2);
  seekdir (DIR2, $HeadDir2) or Stop ("Can't seekdir $Path2: $!");
  @DirList2_l = grep {!(/^\./) && !(-f "$Path2\\$_")} readdir (DIR2);
  
  # Close directories
  #
  closedir (DIR1);
  closedir (DIR2);
  
  # Make sure the list are alphabetically ordered (and transformed in UPPER case)
  #
  @FilesList1_l = sort (map (uc ($_), @FilesList1_l));
  @DirList1_l = sort (map (uc ($_), @DirList1_l));
  @FilesList2_l = sort (map (uc ($_), @FilesList2_l));
  @DirList2_l = sort (map (uc ($_), @DirList2_l));
  
  # When called from main(), exit if either directory is empty.

  if ($First_l) {
	if (!($FilesList1_l[0] cmp "") && !($DirList1_l[0] cmp "")) {
		Stop ("Directory $Path1 is empty");
	}
	if (!($FilesList2_l[0] cmp "") && !($DirList2_l[0] cmp "")) {
		Stop ("Directory $Path2 is empty");
	}
  }
  
  
  # Store Dirs in local variables

  my $Dir1_l = $Path1;
  my $Dir2_l = $Path2;
  
  # Begin FILE comparison

  @List1 = @FilesList1_l;
  @List2 = @FilesList2_l;
  CompLists (1, $Dir1_l, $Dir2_l);

  # Begin DIR comparison
  
  @List1 = @DirList1_l;
  @List2 = @DirList2_l;
  CompLists (0, $Dir1_l, $Dir2_l);

}

#####################################################
# Function Stop                                     #
#   close output file (if open) and exit            #
#####################################################
sub Stop
{
	if ($metawritten) {
		close (OUTPUT);
      		system ("del \"$Output\"");
	}
	print ("@_[0]\n");
	exit;
}

#####################################################
# Function Usage                                    #
#####################################################

sub Usage
{
	print <<EOF;
bsp.pl (c) Symbian 2001
bsp -d | -m [-b] [-e] [-z] [-f metadata] ref_dir dev_dir

-d: report differences between ref_dir and dev_dir\
-m: generate metadata file
-f: specify metadata filename, defaults to bsp.met
-b: include binary (non source) files
-e: limit comparision to epoc32, implicitly sets -b
-z: turn off IPR warnings
ref_dir: pathname of reference devkit tree
dev_dir: pathname of bsp development tree
EOF
	exit;
}
