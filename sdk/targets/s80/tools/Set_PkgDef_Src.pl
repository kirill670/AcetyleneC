#########################################################
# Set_PkgDef_Src.PL
#
# Copyright (c) 2001 Symbian Ltd.  All rights reserved.
#########################################################

use File::Copy;

## Global Variables ##

$Location=@ARGV[0];
$ChangeFrom=@ARGV[1];
$ChangeTo=@ARGV[2];

## Start ##

if($ChangeTo ne ""){ 

	$ChangeTo=Format_String($ChangeTo); 

	print "\n|$ChangeTo|\n";
}

Main();

sub Main
{
	if($Location eq ""){ Help(); }

	elsif($ChangeFrom eq ""){
		print "\nChecking .PKGDEF file(s) at $Location...\n";

		Search_PKGDEF();
	}
	elsif(-d $Location && -e $Location && $ChangeFrom=~ /^\[.*\]$/){
		print "\nProcessing .PKGDEF file(s) at $Location...\n";

		Process_PKGDEF();
	}
	elsif(!-d $Location && !-e $Location){
		print "\nERROR: \U$Location "."is an invalid [LOCATION].\n";
		Help();
	}
	else{
		print "\nERROR: \"$ChangeFrom\" is an invalid [KEYWORD].\n";
		Help();
	}
}

sub Search_PKGDEF
{
my $List_Length;
my @Note_List=();
local @List=();

	opendir(DIR, $Location) || die "\nERROR: Unable to open $Location\n";

	foreach $Name (readdir(DIR)){
		if(!-d $Name && $Name=~ /^com.symbian.supportkit.(.*).PKGDEF$/i){
			push(@Note_List, $Name);
		}
		elsif(!-d $Name && $Name=~ /^(.*).PKGDEF$/i){
			Search_PKGDEF_File($Name,$Location);
		}
	}

	closedir(DIR);

	$List_Length=@List;

	if($List_Length==0){
		print "\nAll missing source paths have been entered.\n";
	}	
	else{
		print "\nBelow lists all missing source paths that require entering:\n\n";
	
		foreach $Name (@List){
			print "$Name\n";
		}
	}

	if(@Note_List>0){
		print "\nNOTE: The following files need to be edited manually:\n";

		foreach $Name (@Note_List){
			print "\U\n$Name\n";
		}
	}
}

sub Search_PKGDEF_File
{
my $Name=$_[0];
my $Location=$_[1];
my $Line;
my $Item;
my $Item_Flag=0;

	if(substr($Location, length($Location)-1, 1)=~ /[^\\|\/]/ ){
		$Location="$Location"."\\";
	}

	open(FILE, "$Location$Name") || die "ERROR: Unable to open file at $Location$Name";

	while(<FILE>){
		$Line=$_;

		if($Line=~ /<item src=\"\[SET-(.*)/i){
			
			$Item=substr($1,0, index($1,"]"));
			$Item="[SET-$Item]";

			foreach $Name (@List){
				if($Name eq $Item){ $Item_Flag=1; }
			}

			if($Item_Flag==0){ push(@List,$Item); }
		}
	}

	close(FILE);
}

sub Process_PKGDEF
{
my $Counter=0;
my @Note_List=();

	opendir(DIR, $Location) || die "\nERROR: Unable to open $Location\n";

	foreach $Name (readdir(DIR)){

		if(!-d $Name && $Name=~ /^com.symbian.supportkit.(.*).PKGDEF$/i){
			push(@Note_List, $Name);
		}
		elsif(!-d $Name && $Name=~ /^(.*).PKGDEF$/i){

			if(Edit_PKGDEF_File($Name,$Location)==1){
				print "\n\U$Name"." edited...\n";
				$Counter++;
			}
		}
	}
	closedir(DIR);

	print "\n-- PROCESS COMPLETE --\n";

	if($Counter==0 || $Counter>1){
		print "\n-- $Counter files processed --\n";
	}
	else{
		print "\n-- $Counter file processed --\n";
	}

	if(@Note_List>0){
		print "\nNOTE: The following files need to be edited manually:\n";

		foreach $Name (@Note_List){
			print "\U\n$Name\n";
		}
	}
}

sub Edit_PKGDEF_File
{
my $Name=$_[0];
my $Location=$_[1];
my $PkgDef_TempFile="PKGDEF_TEMP.TXT";
my $PkgDef_Flag=0;
my $ChangeFrom_Length=length($ChangeFrom);
my $LogFlag=0;
my $Line;

	if(substr($Location, length($Location)-1, 1)=~ /[^\\|\/]/ ){
		$Location="$Location"."\\";
	}

	open(TEMP, ">$PkgDef_TempFile") || die "\nERROR: Unable to create $PkgDef_TempFile file\n";
	open(FILE, "$Location$Name") || die "ERROR: Unable to open file at $Location$Name";

	while(<FILE>){
		$Line=$_;
	
		if($Line=~ /<manifest>\n/i && $PkgDef_Flag==0){
			$PkgDef_Flag=1;
		}
		elsif($Line=~ /<\/manifest>\n/i && $PkgDef_Flag==1){
			$PkgDef_Flag=0;
		}
		elsif($PkgDef_Flag==1){
			if(index($Line,$ChangeFrom)!=-1){
				substr($Line,index($Line,$ChangeFrom),$ChangeFrom_Length)=$ChangeTo;
				$LogFlag=1;
			}
		}
		print TEMP $Line;
	}

	close(FILE);
	close(TEMP);

	if($LogFlag==1){
		unlink("$Location$Name") || die "\nERROR: Unable to delete $Location$Name.\n";
		rename("$PkgDef_TempFile", "$Name") || die "\nERROR: Unable to rename $PkgDef_TempFile.\n";
		move("$Name", "$Location$Name") || die "\nERROR: Unable to move $Name.\n"
	}
	else{
		unlink("$PkgDef_TempFile") || die "\nERROR: Unable to delete $Location$Name.\n";
	}

	return $LogFlag;
}

sub Format_String
{
my $String=$_[0];

	$String=~ s/\//\\/g;

	if($String=~ /^\w:\\/ || $String=~ /^\\/){}

	else{
		$String="\\"."$String";
	}

	return $String;
}

sub Help
{
	print "\nUSAGE(1):\t SET_PKGDEF_SRC <LOCATION>\n";
	print "\nUSAGE(2):\t SET_PKGDEF_SRC <LOCATION> <KEYWORD> <REPLACEMENT>\n";

	print "\nDESCRIPTION(1):\t Displays all missing source paths for the .PKGDEF files at the \n\t\t stated <LOCATION>.\n";
	print "\nDESCRIPTION(2):\t Changes all .PKGDEF files at the stated <LOCATION> so that all files \n\t\t with source string <KEYWORD> are replaced with string <REPLACEMENT>.";
	print "\nWHERE:\n\n";

	print " <LOCATION>:-\t Is a location where .PKGDEF file(s) can be found.\n";
	print " <KEYWORD>:-\t Is the keyword source string that is to be replaced (*).\n";
	print " <REPLACEMENT>:- Is the replacement string that is to be added.\n";

	print "\n(*) NOTE: The source string entered here is CASE SENSITSIVE and must be between square \n\t  brackets [] e.g. [SET-sdkroot].\n";
	
	exit();	
}