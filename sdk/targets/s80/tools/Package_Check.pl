#########################################################
# Package_Check.PL
#
# Copyright (c) 2001 Symbian Ltd.  All rights reserved.
#########################################################

use Cwd;
use File::Copy;
use File::Path;
use FindBin;
use lib $FindBin::Bin."/perllib","$FindBin::Bin";

### Global Variables ###

$Original_Directory=Sort_Locations(cwd());
$Log_Text="===PACKAGE CHECK LOG FILE===\n\n";

$Original_Directory=~ s/\//\\/g;

Main();

sub Main
{
my $Check_Location=@ARGV[0];
my $Symbian_Location=@ARGV[1];

	if($Symbian_Location eq "" || $Check_Location eq ""){
		Help(); 
	}
	elsif(!-e $FindBin::Bin."\\evalid.bat" && !-e $FindBin::Bin."\\evalid.pl"){
		print "\nERROR: Unable to locate the EVALID tool.\n";
		exit();
	}

	if(-e $Check_Location && -d $Check_Location && -e $Symbian_Location  && -d $Symbian_Location){
		print "\nFiles at \U$Check_Location"." are to be checked by the files at \U$Symbian_Location...\n";

		$Check_Location=Sort_Locations($Check_Location);
		$Symbian_Location=Sort_Locations($Symbian_Location);

		$Log_Text="$Log_Text"."Result of checked packages at \U$Check_Location:-\n";

		Clean_Drive($Check_Location);

		Check_Packages($Check_Location,$Symbian_Location);

		Create_Log_File("$Check_Location");
	}
	elsif(-e $Check_Location && -d $Check_Location){
		print "\nERROR: Location \U$Symbian_Location "."does not exist.\n";
	}
	elsif(-e $Symbian_Location && -d $Symbian_Location){
		print "\nERROR: Location \U$Check_Location "."does not exist.\n";
	}
	else{
		print "\nERROR: Neither \U$Check_Location "."nor \U$Symbian_Location "."locations exist.\n";
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

sub Help
{
	print "\nUSAGE:\t\tPACKAGE_CHECK <TO_CHECK_LOCATION> <SYMBIAN_LOCATION>\n";
	
	print "\nDESCRIPTION:\tChecks the named Symbian package files at <TO_CHECK_LOCATION> with the \n\t\tSymbian package files at <SYMBIAN_LOCATION>.";

	print "\n\n\t\t(N.B. This tool requires the EVALID tool.)";

	print "\nWHERE:\n\n";

	print " <TO_CHECK_LOCATION>:- \tIs a location where named Symbian package files are to be checked.\n";

	print " <SYMBIAN_LOCATION>:-\tIs a location where original Symbian package files can be found.\n";
	
	exit();	
}

sub Check_Packages
{
my $Check_Location=$_[0];
my $Symbian_Location=$_[1];
my $Evalid_Temp=$FindBin::Bin."\\evalid.txt";
my $Count;
local $Result_Flag;
local $Result_String;

	opendir(TOCHECK,"$Check_Location") || die "\nError: Can not opendir $Check_Location\n";

	foreach $Name (readdir(TOCHECK)){	

		if(!-d $Name && $Name=~ /^com\.symbian\./i && $Name=~ /^(.*)\.sdkpkg$/i){
			
			$Log_Text="$Log_Text"."\n[PACKAGE FILE]: \U$Name\n\n";

			print "\nProcessing \U$Name...\n";

			$Result_Flag=0;				
			$Result_String="";

			if(-e "$Symbian_Location$Name"){

				print "\nUnzipping \U$Check_Location$Name"." to \U\\Check_Temp\\...\n";

				system("unzip -s -o -q $Check_Location$Name -d \\Check_Temp\\");

				print "\nUnzipping \U$Symbian_Location$Name"." to \U\\Symbian_Temp\\...\n";
				
				system("unzip -s -o -q $Symbian_Location$Name -d \\Symbian_Temp\\");

				print "\nComparing files...\n";

				if(!-e "\\Check_Temp\\" || !-e "\\Symbian_Temp\\"){
					print "\nERROR: Problem unzipping \U$Name...\n";
					exit();
				}

				system($FindBin::Bin."\\evalid.bat -l $Evalid_Temp \\Symbian_Temp \\Check_Temp");

				$Log_Text="$Log_Text"."[PACKAGE LOG]:\n\n". Read_Results($Evalid_Temp);
				$Log_Text="$Log_Text"."\nChecking for additional files at \\Check_Temp\\\n\n";

				chdir("\\Check_Temp\\") || die "\nERROR: Unable to change to \\Check_Temp\\ directory.\n";

				Compare_Files("Check_Temp");

				if($Result_String eq ""){ $Log_Text="$Log_Text"."No additional files found\n"; }
				else{
					$Result_Flag=1;
					$_=$Result_String;
					$Count =tr/\n//;					

					if($Count==1){ 
						$Log_Text="$Log_Text"."$Count additional file found\n\n";
					}
					else{
						$Log_Text="$Log_Text"."$Count additional files found\n\n";
					}
					$Log_Text="$Log_Text"."$Result_String";
				}

				print "\nCheck on \U$Name"." complete.\n";

				chdir("$Original_Directory");

				rmtree("\\Check_Temp\\");
				rmtree("\\Symbian_Temp\\");
			}
			else{
				print "\nWARNING: Unable to compare \U$Check_Location$Name"." \nwith \U$Symbian_Location$Name...\n";
				$Log_Text="$Log_Text"."[PACKAGE LOG]:\n\n"."Unable to compare \U$Check_Location$Name"." with \U$Symbian_Location$Name.\n\n";
				$Log_Text="$Log_Text"."\U$Symbian_Location$Name"." not found.\n";

				$Result_Flag=1;
			}

			if($Result_Flag==0){ $Log_Text="$Log_Text"."\n[PACKAGE RESULT]: >>PASSED<<\n"; }
			
			else{ $Log_Text="$Log_Text"."\n[PACKAGE RESULT]: >>FAILED<<\n"; }

			$Log_Text="$Log_Text"."\n"."=" x75 ."\n";
		}
	}	
	close(TOCHECK);
}

sub Compare_Files
{
my $Temp_Check=$_[0];
my $This_Path;
my $Back="..";

	opendir(HERE,'.');
	
	foreach $File (readdir(HERE)){

		if($File eq "." || $File eq ".."){}
		elsif(-d $File){
			chdir($File);
			Compare_Files($Temp_Check);
			chdir($Back);
		}
		else{
			$Compare_Path=cwd();
			$Compare_Path=~ s/$Temp_Check/Symbian_Temp/;
			$Compare_Path=~ s/\//\\/g;

			if ($Compare_Path=~ /:\\(.*)/){
				$Compare_Path="\\$1";
			}

			if(-f "$Compare_Path\\$File" && -e "$Compare_Path\\$File"){}
			else{
				$Result_String="$Result_String"."EXTRA: Additional file $Compare_Path/$File found\n";
			}
		}
	}
	close(HERE);
}

sub Read_Results
{
my $Evalid_Temp=$_[0];
my $Evalid_Sting="";
my $Evalid_Flag=0;

	open(RESULT,"$Evalid_Temp") || print "\nERROR: Can not open the file $Evalid_Temp\n";

	while(<RESULT>){
		if($_ =~ /^Failed(.*)$/i || $_ =~ /^MISSING: (.*)$/i){
			$Result_Flag=1;
		}
		
		if($Evalid_Flag==1){
			$Evalid_Sting="$Evalid_Sting"."$_";
		}
		elsif($_ =~ /Results of evalid/i && $Evalid_Flag==0){
			$Evalid_Sting="$Evalid_Sting"."$_";
			$Evalid_Flag=1;
		}
	}

	close(RESULT);

	if($Evalid_Flag==0 && $Evalid_Sting eq ""){

		open(RESULT,"$Evalid_Temp");

		while(<RESULT>){
			$Evalid_Sting="$Evalid_Sting"."$_";
		}

		close(RESULT);
	}

	unlink("$Evalid_Temp");

	return($Evalid_Sting);
}

sub Create_Log_File
{
my $Location=$_[0];
my $Log_File="Package_Check.LOG";

	unlink("$Log_File");

	open(LOGTEXT, ">$Log_File");

	print LOGTEXT "$Log_Text";

	close(LOGTEXT);

	print "\n$Log_File created\n";

	if($Log_Text =~ /\[PACKAGE RESULT\]: >>FAILED<</i){
		print "\nOne or more Symbian named package files at \U$Location"." have been \Umodified:"." see $Log_File.\n";
	}
	else{
		print "\nAll Symbian named packages at \U$Location"." have \Upassed.\n";
	}
}

sub Clean_Drive
{
my $Check_Location=$_[0];

	rmtree("\\Check_Temp\\");
	rmtree("\\Symbian_Temp\\");

	unlink("\\evalid.txt");
}