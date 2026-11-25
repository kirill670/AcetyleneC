#########################################################
# Create_Symbian_List.PL
#
# Copyright (c) 2001 Symbian Ltd.  All rights reserved.
#########################################################

Main();

sub Main
{
my $PkgDef_Location=@ARGV[0];

	if($PkgDef_Location eq ""){ Help(); }

	if(-e $PkgDef_Location && -d $PkgDef_Location){
		print "\nReading restricted PKGDEF files at \U$PkgDef_Location...\n";

		Process_Location($PkgDef_Location);
	}
	else{
		print "\nERROR: \U$Location "."is a invalid location.\n";
	}
}

sub Sort_Locations
{ 
my $Location=$_[0];

	$Location=~ s/\//\\/g;

	if((length($Location)-1)!=rindex("$Location", "\\")){
		$Location="$Location"."\\";
	}
	return $Location;
}

sub Process_Location
{
my $Location=$_[0];
my $Input_File="Symbian_List.txt";
local $Input_Flag=0;

	unlink("$Input_File");

	open(NEW, ">$Input_File") || die "\nERROR: Unable to create $Input_File file\n";
	opendir(TOCHECK,"$Location") || die "\nError: Can not opendir $Location\n";

	$Location=Sort_Locations($Location);

	foreach $Name (readdir(TOCHECK)){
		if (!-d $Name && ($Name=~ /^com\.symbian\.(.*)restricted(.*)\.pkgdef$/i || $Name=~ /^com\.symbian\.(.*)confidential(.*)\.pkgdef$/i)){
			print "\nReading \U$Name...\n";
			Process_File($Location, $Name);			
		}
	}

	close(TOCHECK);
	close(NEW);

	print "\n\U$Input_File created.\n";

	if($Input_Flag==0){
		print "\n\UWARNING: $Input_File is empty.\n";
	}
}

sub Process_File
{
my $Location=$_[0];
my $Name=$_[1];
my $PkgDef_Flag=0;
my $Line;
	
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
			print NEW $Line;
			$Input_Flag=1;
		}		
	}

	close(FILE);
}

sub Edit_Line
{
my $Line=$_[0];
my @Split_Line;

	@Split_Line=split(/\"/,$Line);

	if($Split_Line[3]=~ /\[/ && $Split_Line[3]=~ /\](.*)/){
		$Split_Line[3]=$1;	
	}

	return "$Split_Line[3]\n";
}

sub Help
{
	print "\nUSAGE:\t\tCREATE_SYMBIAN_LIST <LOCATION>\n";
	print "\nDESCRIPTION:\tReads restricted and confidential named .PKGDEF files at <LOCATION> so ";
	print "\n\t\tthat an input file SYMBIAN_LIST.TXT is created from their contents.\n";

	print "\nWHERE:\n\n";

	print " <LOCATION>:-\tIs a location where restricted and confidential .PKGDEF files are "; 
	print "\n\t\tto be read.\n\n";
	print " SYMBIAN_LIST.TXT:- Is the default input file created for the SOURCE_CHECK tool.\n";

	exit();
}