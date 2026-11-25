#########################################################
# Source_Verification.PL
#
# Copyright (c) 2001 Symbian Ltd.  All rights reserved.
#########################################################

use FindBin;
use lib $FindBin::Bin."/perllib","$FindBin::Bin";

Main();

sub Main
{
my $Location=@ARGV[0];
my $Input_Text=@ARGV[1];
my $Default_input=$FindBin::Bin."\\Symbian_List.TXT";
my $Log_File="Source_Check.LOG";
local $Result_Flag=0;

	$Default_input=~ s/\//\\/g;

	if($Location eq ""){ Help(); }

	if($Input_Text eq ""){ 
		$Input_Text="$Default_input"; 
	}

	if(-e $Location && -d $Location){
		print "\nUsing \U$Input_Text "."to check .SDKPKG files located at \U$Location...\n";

		if(!-e $Input_Text){ 
			print "\nERROR: The input file \U$Input_Text"." is not present.\n";
			exit();
		}

		unlink("$Log_File");

		open(LOGTEXT, ">$Log_File");

		print LOGTEXT "--SOURCE_CHECK LOG--\n\n";
		
		Process_Location($Location,$Input_Text);

		close(LOGTEXT);

		if($Result_Flag==0){
			print "\nAll packages at \U$Location"." have \Upassed.\n";
		}
		else{
			print "\nWARNING: Package(s) at \U$Location"." contain file(s) that should not be present!\n";
		}
	}
	else{
		print "\nERROR: \U$Location "."is a invalid location.\n";
	}
}

sub Sort_Locations
{ 
my $Location=$_[0];

	if((length($Location)-1)!=rindex("$Location", "\\") && (length($Location)-1)!=rindex("$Location", "/")){
		$Location="$Location"."\\";
	}
	return $Location;
}

sub Process_Location
{
my $Location=$_[0];
my $Input_Text=$_[1];
my $Temp_File="Temp_File.TXT";
my $Failed_Flag;
my $SDKPKG_Contents;
my @File_List=();
my $Space=70;

	print LOGTEXT "SDKPKG FILE"." " x($Space-11) ."RESULT\n\n";
	print LOGTEXT "=" x11 ." " x($Space-11) ."=" x6 ."\n\n";
	
	@File_List=Read_Input_File($Input_Text); 

	opendir(TOCHECK,"$Location") || die "\nError: Can not opendir $Location\n";

	$Location=Sort_Locations($Location);

	foreach $Name (readdir(TOCHECK)){

		if (!-d $Name &&  $Name=~ /^(.*)\.sdkpkg$/i){
			print "\nChecking \U$Name...\n";

			$Failed_Flag=0;
			
			unlink("$Temp_File");

			system("unzip -l $Location$Name >$Temp_File");
			
			$SDKPKG_Contents=Read_Package($Temp_File);
			
			foreach $Item (@File_List){

				if(index($SDKPKG_Contents, $Item)!=-1){
					if($Failed_Flag==1){
						print LOGTEXT " " x5 ."\""." " x($Space-6) ."FAILED - as \U$Item found.\n";
					}
					else{
						print LOGTEXT "\U$Name "." " x ($Space-length($Name)-1); 
						print LOGTEXT "FAILED - as \U$Item found.\n";
						$Failed_Flag=1;
					}
					$Result_Flag=1;
				}
			}

			if($Failed_Flag==0){
				print LOGTEXT "\U$Name "." " x ($Space-length($Name)-1) ."PASSED\n";
			}
		}
	}

	close(TOCHECK);

	unlink("$Temp_File");
}

sub Read_Package
{
my $Temp_File=$_[0];
my $Temp_String="";
my $Temp_File_Flag=0;
my $SDKPKG_Contents;

	open(TEMPFILE,$Temp_File) || die "\nError: $Temp_File not created. Unzip.exe not available.\n";

	while(<TEMPFILE>){

		if($Temp_File_Flag==0 && $_=~ /----/){
			$Temp_File_Flag=1;
		}
		elsif($Temp_File_Flag==1 && $_=~ /----/){
			$Temp_File_Flag=2;
		}
		elsif($Temp_File_Flag==1){
			$Temp_String=substr($_,rindex($_," ")+1,length($_));
			$Temp_String=~ s/\\/\//g;

			$SDKPKG_Contents="$SDKPKG_Contents".lc($Temp_String);
		}
	}

	close(TEMPFILE);

	return $SDKPKG_Contents;
}

sub Read_Input_File
{
my $Input_Text=$_[0];
my $Line;
my @File_List=();

	print "\nReading $Input_Text...\n";

	open(THISFILE,$Input_Text);

	while(<THISFILE>){		
		$Line=$_;
		$Line=~ s/\\/\//g;
		$Line=~ s/\n//g;

		if($Line=~ /\w/){ 
			push(@File_List,lc($Line)); 
		}
	}

	close(THISFILE);

	return @File_List;
}

sub Help
{
	print "\nUSAGE:\t\tSOURCE_CHECK <LOCATION> [INPUT_FILE]\n";
	
	print "\nDESCRIPTION:\tChecks all .SDKPKG files at <LOCATION> so that any files present as \n\t\tstated in [INPUT_FILE] are reported in a log file called Source_Log.txt.";

	print "\n\n\t\t(N.B. Archive files, like .zip or .jar, are not checked as they are \n\t\tpersumed to not contain files that are not to be redistributed.)";

	print "\nWHERE:\n\n";

	print " <LOCATION>:- \tIs a location where .SDKPKG files are to be checked.\n";

	print " [INPUT_FILE]:-\tIs an optional parameter to state an input file. By default \n\t\tthe file Symbian_List.TXT is used.\n";

	exit();
}
