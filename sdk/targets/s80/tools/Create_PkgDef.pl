#########################################################
# Create_PkgDef.PL
#
# Copyright (c) 2001 Symbian Ltd.  All rights reserved.
#########################################################

use Cwd;

### Global Variables ###

$Original_Directory=cwd();
$Path_String;

Main();

sub Main
{
my $Input_File=@ARGV[0];
my $PkgDef_Name=@ARGV[1];

	if($Input_File eq "" || $PkgDef_Name eq ""){ 
		Help(); 
	}
	else{
		if($PkgDef_Name=~ /^(.*)\.pkgdef$/i){}
		else{
			$PkgDef_Name="$PkgDef_Name.pkgdef";
		}
		if(-e $Input_File && !-d $Input_File){
			Read_Input_File($Input_File,$PkgDef_Name);
		}
		else{
			print "\nERROR: \U$Input_File"." is an invalid input.\n";
		}
	}
}

sub Read_Input_File
{
my $Input_File=$_[0];
my $PkgDef_Name=$_[1];
my $Command="";
my $Meta_Data="";
my $Line;
my $Type;
my @Available_Types=("META DATA","DESTINATION","DIRECTORY LOCATIONS");
my $Counter=0;

	$Path_String="";

	open (THISFILE,"$Input_File") || die "\nError: Can not open $Info_File\n";

	print "\nReading \U$Input_File...\n";

	while(<THISFILE>){
		$Line=$_;

		if($Line=~ /^\[(.*)\]:(\s+)$/){
			$Type=$1;
			
			if($Available_Types[$Counter] ne $Type){
				print "\nERROR: Format of \U$Input_File"." is incorrect\n";
				exit();
			}
			$Counter++;
		}
		elsif($Type=~ /^META DATA$/){
			$Meta_Data="$Meta_Data"."$Line";
		}
		elsif($Type=~ /^DESTINATION$/){
			if($Command ne "" && $Line=~ /\w/ && $Line=~ /->/){
				print "\nERROR: DESTINATION cannot be defined more that once\n";
			}
			elsif($Line=~ /\w/ && $Line=~ /->/){
				$Line=Format_Line($Line);
				$Command=$Line;
			}
		}
		elsif($Type=~ /^DIRECTORY LOCATIONS$/){
			if($Command ne "" && $Line=~ /\w/){
				$Line=Format_Line($Line);
				List_Directory($Line,$Command);
			}
			elsif($Command eq ""){
				print "\nERROR: <DESTINATION> must be defined before <DIRECTORY LOCATIONS> in \U$Input_File\n";
				exit();
			}
		}
	}
	close (THISFILE);

	$Meta_Data=~ s/^(\s+)//;

	if($Counter==3){
		Create_PkgDef($Meta_Data, $PkgDef_Name);
	}
	else{
		print "\nERROR: META DATA, DESTINATION and DIRECTORY LOCATIONS no found in \U$Input_File\n";
		exit();
	}
}

sub Create_PkgDef
{
my $Meta_Data=$_[0];
my $PkgDef_Name=$_[1];
my $PkgDef_Meta;
my $PkgDef_Paths;
my $PkgDef_Flag=0;
my $Diff_Flag=0;
my $Extra_Paths="";
my @Paths;

	if(-e $PkgDef_Name){
		print "\n\U$PkgDef_Name"." already exists, checking for additional input data...\n";

		open(PKGDEF,"$PkgDef_Name") || die "\nERROR: Unable to open $PkgDef_Name\n";

		while(<PKGDEF>){
			if($_ =~ /<manifest>/i){
				$PkgDef_Flag=1;						
			}
			elsif($_ =~ /<\/manifest>/i){
				$PkgDef_Flag=2;
			}
			elsif($PkgDef_Flag==0){
				$PkgDef_Meta="$PkgDef_Meta$_";	
			}
			elsif($PkgDef_Flag==1){
				$PkgDef_Paths="$PkgDef_Paths$_";
			}
		}

		close(PKGDEF);

		@Paths= split(/\n/,$Path_String);

		foreach $Name (@Paths){
			if(index("$PkgDef_Paths","$Name")==-1){
				$Diff_Flag=1;
				$Extra_Paths="$Extra_Paths$Name\n";
			}
		}
				
		if($Diff_Flag==1 || index("$PkgDef_Meta","$Meta_Data")==-1){
			
			if(index("$PkgDef_Meta","$Meta_Data")==-1){
				print "\nChanging Meta Data in \U$PkgDef_Name...\n";
			}
			if($Diff_Flag==1){
				print "\nAdding additional directory locations to \U$PkgDef_Name...\n";
			}

			open(PKGDEF,">$PkgDef_Name") || die "\nERROR: Unable to create $PkgDef_Name\n" ;

			print PKGDEF "$Meta_Data";
			print PKGDEF " " x3 ."<manifest>\n$Extra_Paths$PkgDef_Paths";
			print PKGDEF " " x3 ."</manifest>\n</packagedef>";

			close(PKGDEF);

			print "\n\U$PkgDef_Name updated.\n";
		}
		else{
			print "\nNo new data found...\n";

			print "\n\UNo change to $PkgDef_Name.\n";
		}
	}
	else{
		print "\nCreating \U$PkgDef_Name...\n";

		open(PKGDEF,">$PkgDef_Name") || die "\nERROR: Unable to create $PkgDef_Name\n" ;

		print PKGDEF "$Meta_Data";
		print PKGDEF " " x3 ."<manifest>\n$Path_String";
		print PKGDEF " " x3 ."</manifest>\n</packagedef>";

		close(PKGDEF);

		print "\n\U$PkgDef_Name created.\n";
	}
}

sub Format_Line
{
my $Line=$_[0];

	chomp($Line);
	$Line=~ s/\t//g;
	$Line=~ s/ //g;
	
	return $Line;
}

sub List_Directory
{
my $Location=$_[0];
my $Command=lc($_[1]);
my $Change_From;
my $Change_To;

	if(chdir($Location)){

		($Change_From,$Change_To)=split(/->/,$Command);
		Get_Paths($Change_From, $Change_To);

		chdir($Original_Directory);
	}
	else{ 
		print "\nERROR: Can not access directory \U$Location\n";
	}
}

sub Get_Paths
{
my $Change_From=$_[0];
my $Change_To=$_[1];
my $Path;
my $Dest_Path;
my $Back="..";

	opendir(HERE,'.');
	
	foreach $Name (readdir(HERE)){
		if($Name eq "." || $Name eq ".."){}
		elsif(-d $Name){
			chdir($Name);
			Get_Paths($Change_From, $Change_To);
			chdir($Back);
		}
		else{
			if(cwd()=~ /:(.*)/){
				$Path="$1\\$Name";
				$Path=lc($Path);
				$Path=~ s/\//\\/g;
				$Dest_Path="$Path";

				if(index("$Dest_Path","$Change_From")!=-1){
					$Dest_Path=substr("$Dest_Path", index("$Dest_Path","$Change_From")+length($Change_From), length($Dest_Path));
					$Dest_Path="$Change_To$Dest_Path";
				}
				if(index("$Path_String","\"$Path\"")==-1){
					$Path_String="$Path_String"." " x6 ."<item src=\"$Path\" dest=\"$Dest_Path\"/>\n";
				}
			}
		}
	}
	close(HERE);
}

sub Help
{
	print "\nUSAGE:\t\tCREATE_PKGDEF <INFO_FILE> <NAME>\n";
	print "\nDESCRIPTION:\tCreates a .PKGDEF file <NAME> using the information provided in the \n\t\tfile <INFO_FILE>.";
	print "\nWHERE:\n\n";

	print " <INFO_FILE>:-\tIs a file that is pre-written and will contain the information\n";
	print " \t\tMETA DATA, DESTINATION and DIRECTORY LOCATIONS.\n\n";

	print " <NAME>:- \tIs the name of the .PKGDEF file that is to be created.\n";
	
	exit();	
}