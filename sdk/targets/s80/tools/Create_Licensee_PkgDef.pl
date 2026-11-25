#########################################################
# Create_Licensee_PkgDef.PL
#
# Copyright (c) 2001 Symbian Ltd.  All rights reserved.
#########################################################

use File::Copy;

Main();

sub Main
{
my $Location=@ARGV[0];

	if($Location eq ""){ Help(); }
	
	if(-e $Location && -d $Location){
		print "\nProcessing .PKGDEF file(s) at \U$Location...\n";

		Process_PKGDEF($Location);		
	}
	else{
		print "\nERROR: \U$Location "."is an invalid [LOCATION].\n";
		Help();
	}
}

sub Process_PKGDEF
{
my $Location=$_[0];
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
local $Logfile=0;
my $Line;

	if(substr($Location, length($Location)-1, 1)=~ /[^\\|\/]/ ){
		$Location="$Location"."\\";
	}

	open(TEMP, ">$PkgDef_TempFile") || die "\nERROR: Unable to create $PkgDef_TempFile file\n";
	open(FILE, "$Location$Name") || die "\nERROR: Unable to open file at $Location$Name\n";

	while(<FILE>){
		$Line=$_;
	
		if($Line=~ /<manifest>\n/i && $PkgDef_Flag==0){
			$PkgDef_Flag=1;
		}
		elsif($Line=~ /<\/manifest>\n/i && $PkgDef_Flag==1){
			$PkgDef_Flag=0;
		}
		elsif($PkgDef_Flag==1){
			$Line=Edit_Line($Line);
		}
		print TEMP $Line;
	}

	close(FILE);
	close(TEMP);

	if($Logfile!=0){
		unlink("$Location$Name") || die "\nERROR: Unable to delete $Location$Name.\n";
		rename("$PkgDef_TempFile", "$Name") || die "\nERROR: Unable to rename $PkgDef_TempFile.\n";
		move("$Name", "$Location$Name") || die "\nERROR: Unable to move $Name.\n"
	}

	return $Logfile;
}

sub Edit_Line
{
my $Line=$_[0];
my $Item;
my @Split_Line;
my $Left_Bracket;
my $Right_Bracket;

	@Split_Line=split(/\"/,$Line);

	$Left_Bracket=index($Split_Line[3],"[");
	$Right_Bracket=index($Split_Line[3],"]");

	if($Left_Bracket!=-1 && $Right_Bracket!=-1){
		$Item=substr($Split_Line[3], ($Left_Bracket+1), $Right_Bracket-($Left_Bracket+1));

		$Split_Line[1]=$Split_Line[3];
		$Split_Line[1]=~ s/\[$Item\]/\[SET-$Item\]/;

		$Logfile=1;
	}

	return "$Split_Line[0]\"$Split_Line[1]\"$Split_Line[2]\"$Split_Line[3]\"$Split_Line[4]";
}

sub Help
{
	print "\nUSAGE:\t\tCREATE_LICENSEE_PKGDEF <LOCATION>\n";
	print "\nDESCRIPTION:\tChanges all .PKGDEF files at the stated <LOCATION> so that licensees \n\t\tare able to use them.";
	print "\nWHERE:\n\n";

	print " <LOCATION>:-\tIs a location where the .PKGDEF, to be changed, can be found.\n";
	
	exit();	
}