#!perl

package Symbian::SDK::makeNsis;

use strict;
use File::Basename;
use File::Spec::Functions;
use File::Path;
use Cwd;
use Symbian::SDK::SdkDef;
use Symbian::SDK::Utils;
use FindBin;
use Symbian::Logger::Singleton;

my $secNum = 1;
my $showlist;
my %sdksources;
my $outputdir;
my $createcomps;
my $delcomps;
my $filelist;
my $paramfile;
my $sdk;
my $no_installer_log;
my $custom_nsis;
my $productarea;
my $nsis_param;
my $manifest;
my $no_devices;

my $logger = Symbian::Logger::Singleton->new();

sub Run($$$$$$$)
{
    my $self = shift;
    my $command = Symbian::SDK::Utils::Which("makensis.exe");
    my $nsisversion;
    if ($command)
    {
        $nsisversion = `\"$command\" /VERSION`;
    }
    if (!$command || ($nsisversion && $nsisversion ne "v2.03"))
    {
        $logger->Die("You must have nsis v2.03 installed and added to you PATH.");
    }

    # Read the manifest file. get a full SdkDef object
    $productarea = shift;
    $manifest = shift || $logger->Die("Manifest file not defined\n");
    $outputdir = shift || $logger->Die("Output directory not defined\n");
    $nsis_param = shift;
    $no_installer_log = shift;
    $custom_nsis = shift;
    $no_devices = shift;
    $sdk = Symbian::SDK::SdkDef->New($manifest,$productarea);
    $createcomps = catfile($outputdir,"CreateComponents.nsh");
    $delcomps = catfile($outputdir,"DeleteComponents.nsh");
    $filelist = catfile($outputdir,"FilesList.txt");
    $paramfile = catfile($outputdir, "sdk_param.nsh");

    $logger->PhaseStart("Generating Nsis Code");

    #generate the installer
    GenerateNsis();
    $logger->PhaseEnd();

    $logger->PhaseStart("Compiling Nsis Code");

    CompileNsis($command, $nsis_param);
    $logger->PhaseEnd();
}

sub CompileNsis($$)
{
    my $command = shift;
    my $tmpPath = $FindBin::Bin;
    $tmpPath =~ s/\//\\/g;
    my $param = shift;
    my $args; # = qq($param) if $param;

    #make sure outputdir does not have a trailing \ (nsis issue)
    $outputdir =~ s/[\\\/]$//;
    $args = qq( "/O$outputdir\\NsisCompiler.log" "/X!addincludedir \'$outputdir\'");
    $args = $args . qq( "$param" ) if $param;
    $args = $args . qq( "$tmpPath\\Nsis\\sdkMain.nsi");
    $logger->Print("Calling Compiler: $command $args\n") if $logger->Debug();
    open(NSIS, "| \"$command\" $args") or $logger->Die("Couldn't execute $command $args - $!");
    close(NSIS);
}

#================================================================
sub GenerateNsis
{

    #generate installer parameters which will be included the main nsis script
    open (FILE, ">$paramfile") || $logger->Die("Can't open $paramfile for writing");
    GenerateNsisParam();
    close FILE;

#generate nsis sections and functions header files, included by the main nsis script
    open (SECFILE, ">$createcomps") or $logger->Die("Can't open $createcomps for writing");
    open (COMPDEL, ">$delcomps") or $logger->Die("Can't open $delcomps for writing");
    open (LISTFILE, ">$filelist") or $logger->Die("Can't open $filelist for writing");
    GenerateNsisComponents();
    GenerateNsisEnd();
    close SECFILE;
    close COMPDEL;
    close LISTFILE;
}

#================================================================

sub GenerateNsisParam
{
    my $tmpPath;
    $logger->Print("Generating $paramfile\n") if $logger->Debug();

    # generates a nsis header file to define parameters
    print FILE "!define PRODUCT_NAME \"" . $sdk->SDKName() . "\"\n";
    print FILE "!define PRODUCT_VERSION \"" . $sdk->SDKId() . "\"\n";
    print FILE "!define PRODUCT_PUBLISHER \"" . $sdk->SDKPublisherName() . "\"\n";
    print FILE "!define PRODUCT_WEB_SITE \"" . $sdk->SDKPublisherWebSite() . "\"\n" if $sdk->SDKPublisherWebSite();
    $tmpPath = Symbian::SDK::Utils::GetFullPath($sdk->SDKRootPath(),$sdk->SDKLicenseName());
    print FILE "!define LICENSEDATA \"" . $tmpPath . "\"\n" if -f $tmpPath;
    $tmpPath = Symbian::SDK::Utils::GetFullPath($sdk->SDKRootPath(),$sdk->SDKReadmeName());
    print FILE "!define READMEDATA \"" . $tmpPath . "\"\n" if -f $tmpPath;
    print FILE "!define PRODUCT_PATH \"" . canonpath($sdk->SDKRootPath(),$sdk->SDKRootPath()) . "\"\n";
    print FILE "!define PARAM_FILE \"$paramfile\"\n";
    print FILE "!define CREATECOMP_FILE \"$createcomps\"\n";
    print FILE "!define DELETECOMP_FILE \"$delcomps\"\n";
    $tmpPath = Symbian::SDK::Utils::GetFullPath($sdk->SDKRootPath(),$sdk->SDKManifest());
    print FILE "!define MANIFEST_FILE \"" . $tmpPath . "\"\n";
    my $manifestdest=canonpath(catfile($sdk->SDKEpocRoot(), "epoc32\\relinfo"));
    $manifestdest =~ s/^[\\\/]//;
    print FILE "!define MANIFEST_DESTINATION \"$manifestdest\"\n";
    print FILE "!define MANIFEST_FILENAME \"" . basename($tmpPath) ."\"\n";
    $tmpPath = $FindBin::Bin;
    $tmpPath =~ s/\//\\/g;
    print FILE "!define SDKTOOLS_PATH \"" . $tmpPath . "\"\n";
    if($no_installer_log)
    {
        print FILE "!define NO_INSTALLER_LOG\n";
    }
    if($no_devices)
    {
        print FILE "!define NO_DEVICES_UPDATE\n";
    }
    if($custom_nsis)
    {
        $custom_nsis =~ s/\$\{SDKTOOLS_PATH\}/$tmpPath/;
        $custom_nsis = Symbian::SDK::Utils::GetFullPath($sdk->SDKRootPath(),$custom_nsis);
        $logger->Die("Installer customisation file $custom_nsis does not exist") if ! -f $custom_nsis;
        print FILE "!define CUSTOM_INSTALLER \"$custom_nsis\"\n";
    }
}

#================================================================

sub GenerateNsisComponents
{

    # generate two files:
    # CreateComponents.nsh : nsis code to install and register components
    # DeleteComponents.nsh : nsis code to delete and un-register components
    $logger->Print("Generating $createcomps, $delcomps and $filelist\n") if $logger->Debug();
    my $sdkcomponents;
    my $secName;
    my $secRequired = 0;
    my $secDefault = 0;
    my $secHidden = 0;
    my $secHiddenPrefix;
    my $secDescription;
    my $outputPath = "";
    my $sourcePath = "";
    my $rootPath;
    my $tmpPath;

    # get the list of components
    $sdkcomponents = $sdk->SDKContentDefinition()->GetSDKComponents();

    print LISTFILE "List of resolved files\nFormat:\nComponent: name\n\ndestination\tsource\n------------\n\n";

    foreach my $gkey (sort {$a <=> $b} keys (%{$sdkcomponents}))
    {
        my $sdkcomponent = $sdkcomponents->{$gkey};
        my $componentname = $sdkcomponent->SdkComponentName();
        $logger->Print("Processing group $componentname\n") if $logger->Debug();
        if ( ! $sdkcomponent->ValidateComponent() )
        {

            # component no valid therfore ignore it.
            next;
        }
        my @gdirtodelete = ();
        print LISTFILE "COMPONENT: $componentname\n\n";
        $secNum++;
        $secName="";
        $secName=$componentname;
        $secRequired = 0;
        $secDefault = 0;
        $secHidden = 0;
        $secHiddenPrefix="";
        $secRequired = $sdkcomponent->SdkComponentRequired();
        $secDefault = $sdkcomponent->SdkComponentDefault();
        $secHidden = $sdkcomponent->SdkComponentHidden();
        $secHiddenPrefix = "-" if $secHidden;
        $secDescription = $sdkcomponent->SdkComponentDescription();
        $showlist->{$secNum} = {description => $secDescription,
            CompDef => $secDefault,
            CompReq => $secRequired,
            CompHid => $secHidden,
            Name => $secName};

        # code related to metadata custompage start
        my $metadata = $sdkcomponent->SdkComponentMetaData(); # holds a metadata object
        my $custompages =  defined $metadata ? $metadata->GetCustomPages() : {};
        my @customkeys = sort {$a <=> $b} keys %{$custompages};
        foreach my $ckey (@customkeys)
        {
            my $cname = $custompages->{$ckey}->CustomPageName();
            my $ini = $custompages->{$ckey}->CustomPageIniFile();

 #$ini = Symbian::SDK::Utils::GetFullPath($sdkcomponent->RootPath(), $ini);
 #$logger->Die("Custom Page $cname : inifile $ini does not exist") if ! -f $ini;
            print SECFILE "\tReserveFile \"" . $ini . "\"\n";
            print SECFILE "Page custom User_".$cname."_Pre User_".$cname."_Post\n";
        }

        # code related to metadata custompage -- end
        print SECFILE "Section \"$secHiddenPrefix$secName\" SEC$secNum\n";
        print SECFILE "SectionIn 1 "; # add all sections to Full Installation type
        if ($secRequired || $secHidden)
        {

            # if component Required make the section ReadOnly
            print SECFILE "RO";
        }
        print SECFILE "\n";
        print SECFILE "\tDetailPrint \"..................................\"\n";
        print SECFILE "\tDetailPrint \".\tInstalling $componentname\"\n";
        print SECFILE "\tDetailPrint \"..................................\"\n";
        print SECFILE "\tReadRegStr \$R0 \${PRODUCT_UNINST_ROOT_KEY} \"\${PRODUCT_DIR_REGKEY}\\$secName\" \"ComponentName\"\n";
        print SECFILE "\tstrCmp \$R0 \"$secName\" skipSEC$secNum 0\n";

        # code related to pre execute tasks -- start
        my $executes = defined $metadata ? $metadata->GetExecutes() : [];
        for my $execute (@$executes)
        {
            if (defined $execute->ExecuteType()
                && $execute->ExecuteType() =~ /pre/i)
            {
                $tmpPath = $execute->ExecuteApplication();
                $tmpPath =~ s/^[\\\/]//;
                print SECFILE "\tstrCpy \$R2 \"$tmpPath\"\n";
                if ( ! file_name_is_absolute($tmpPath))
                {

                    # check if application exists first
                    print SECFILE "\tIfFileExists \"\$INSTDIR\\" .$tmpPath . "\" 0 +2\n";
                    print SECFILE "\tstrCpy \$R2 \"\$INSTDIR\\" . $tmpPath . "\"\n";
                }
                my $param =   $execute->ExecuteParameters();
                $param = "" if !defined $param;
                print SECFILE "\tExecWait '\"\$R2\" \"" . $param . "\"' \n";
            }
        }

        # code related to pre execute tasks --end

        # start filing files
        print SECFILE "\t!insertmacro MUI_STARTMENU_WRITE_BEGIN Application\n";

        # start a delete function for this component
        print COMPDEL "Function deleteSEC$secNum\n";
        print COMPDEL "\n";
        print COMPDEL "\tDetailPrint \"..................................\"\n";
        print COMPDEL "\tDetailPrint \".\tDeleting $componentname\"\n";
        print COMPDEL "\tDetailPrint \"..................................\"\n";

        #==================================================================
        $rootPath = $sdkcomponent->RootPath();
        my %componentSources;
        $sdkcomponent->GetComponentSources(\%componentSources,\%sdksources);
        print SECFILE "\t!cd \"$rootPath\"\n";
        my $instdir;
        my @fkeys = sort {$a cmp $b} keys %componentSources;
        my $source;
        my $filename;
        my $dirname;
        my $startedaFILE;
        foreach my $key ( @fkeys )
        {
            $instdir = file_name_is_absolute($key) ? "" : "\$INSTDIR\\";
            if (! $componentSources{$key})
            {

                # no remapping or renaming : most probable case
                $source = $key;
            } else {
                $source = $componentSources{$key};
            }

            #$startedaFILE = 0;
            if ( -f catfile($rootPath,$source) )
            {
                $dirname = dirname($source);

                #it's a file or a link
                if ( $outputPath ne dirname($key))
                {
                    $outputPath = dirname($key);
                    print SECFILE "\n\tsetOutPath \"" . $instdir . $outputPath . "\\\"";
                    $startedaFILE = 0;
                }
                if (basename($key) ne basename($source))
                {

                    # rename case
                    print SECFILE "\n\tFILE /a /oname=\"" . basename($key) . "\" \"" . $source . "\"";
                    $sourcePath = $dirname;
                    $startedaFILE = 0;
                } else
                {

                    #print SECFILE "\tFILE /a \"" . $source . "\"\n";
                    $filename = basename($source);
                    if ( $startedaFILE && $sourcePath eq $dirname)
                    {
                        print SECFILE "\\\n\t\t\"". $filename . "\"";
                    } else {
                        $sourcePath = $dirname;
                        $startedaFILE = 1;
                        print SECFILE "\n\t!cd \"". catdir($rootPath,$sourcePath) . "\"";
                        print SECFILE "\n\tFILE /a \"". $filename ."\"";
                    }
                }
                print COMPDEL "\tdelete \"" . $instdir . $key . "\"\n";
                print LISTFILE "$key\t".$source."\n";
            } else
            {

                #it's a directory
                $sourcePath = $source;
                $startedaFILE = 0;
                print SECFILE "\n\tCreateDirectory \"" . $instdir . $key . "\"";

         #print LISTFILE "directory DESTINATION=$key\\\tSOURCE=".$source."\\\n";

                # preserve group directories to be deteled after deleting files
                push @gdirtodelete, $instdir.$key;
            }
        }
        print LISTFILE "\n\n";

        # a quick loop to delete folders if empty after deleting all files.
        foreach my $dir (sort {$b cmp $a} @gdirtodelete)
        {
            print COMPDEL "\tRMDir \"" . $dir . "\"\n";
        }
        print SECFILE "\n\t!insertmacro MUI_STARTMENU_WRITE_END\n";

        #code related to metadata custompage start
        foreach my $ckey (@customkeys)
        {
            $tmpPath = $custompages->{$ckey}->CustomPageScriptFile();
            print SECFILE "\t!include \"" . $tmpPath . "\"\n" if defined $tmpPath && -f $tmpPath;
        }

        # code related to metadata custompage -- end

        # code related to post execute tasks -- start
        foreach my $execute (@$executes)
        {

            # execute the application
            if ($execute->ExecuteType() !~ /pre/i)
            {
                $tmpPath = $execute->ExecuteApplication();
                $tmpPath =~ s/^[\\\/]//;
                print SECFILE "\tstrCpy \$R2 \"$tmpPath\"\n";
                if ( ! file_name_is_absolute($tmpPath))
                {

                    # check if application exists first
                    print SECFILE "\tIfFileExists \"\$INSTDIR\\" . "$tmpPath" . "\" 0 +2\n";
                    print SECFILE "\tstrCpy \$R2 \"\$INSTDIR\\" .$tmpPath. "\"\n";
                }
                print SECFILE "\tExecWait '\"\$R2\" \"" . $execute->ExecuteParameters() . "\"' \n";
            }
        }

        # code related to post execute tasks --end

        # code related to startmenu, writeini writereg --start
        #StartMenu
        my $items = defined $metadata ? $metadata->GetStartMenus() : [];
        foreach my $item (@$items)
        {
            $tmpPath = Symbian::SDK::Utils::GetFullPath(canonpath("\$SMPROGRAMS\\"),$item->StartMenuSourceLink());
            print COMPDEL "\tDelete \"$tmpPath\"\n";
            print SECFILE "\tCreateDirectory \"" . dirname($tmpPath) . "\"\n";
            my $command = "\tCreateShortCut ";
            $command .= "\"". $tmpPath . "\"";
            $tmpPath = $item->StartMenuDestinationLink();
            $tmpPath =~ s/^[\\\/]//;
            $tmpPath = (file_name_is_absolute($tmpPath) || $tmpPath =~ /:\/\// ) #url or absolute path
              ? " \"" . $tmpPath . "\""
              : " \"\$INSTDIR\\" . $tmpPath . "\"";

            $command .= " $tmpPath ";
            $command .= " \"" . $item->StartMenuParameters() . "\" ";
            $tmpPath = Symbian::SDK::Utils::GetFullPath($rootPath,$item->StartMenuIconFile());
            print SECFILE "\tReserveFile \"" . $tmpPath . "\"\n" if -f $tmpPath;
            $command .= " \"" . $tmpPath . "\" ";
            $command .= " \"" . $item->StartMenuIconIndex() . "\" ";
            $command .= " \"" . $item->StartMenuStartOptions() . "\" ";
            $command .= " \"" . $item->StartMenuKeyboardShortcut() . "\" ";
            $command .= " \"" . $item->StartMenuDescription() . "\" ";
            print SECFILE $command . "\n";
        }

        # writeini

        $items = defined $metadata ? $metadata->GetWriteInis() : [];
        foreach my $item (@$items)
        {
            my $inifile = canonpath($item->WriteIniIniFilename());

            #$inifile =~ s/^[\\\/]//;
            $tmpPath =  Symbian::SDK::Utils::GetFullPath($rootPath,$inifile);

            #file the ini file first
            print SECFILE "\tReserveFile \"" . $tmpPath . "\"\n" if -f $tmpPath;
            if (file_name_is_absolute($inifile))
            {
                print SECFILE "\tsetOutPath \"" . dirname($tmpPath) . "\"\n";
                print SECFILE "\tFILE /a \"". $tmpPath . "\"\n" if -f $tmpPath;
                $tmpPath = "\"" . $tmpPath . "\"";
            } else
            {
                print SECFILE "\tsetOutPath \"\$INSTDIR\\" . dirname($inifile) . "\"\n";
                print SECFILE "\tFILE /a \"". $tmpPath . "\"\n" if -f $tmpPath;
                $tmpPath = "\"\$INSTDIR\\".$inifile . "\"";
            }

            print SECFILE "\tWriteIniStr " .
              $tmpPath . " \"" .
              $item->WriteIniSectionName() . "\" \"" .
              $item->WriteIniEntryName() . "\" \"" .
              $item->WriteIniValue() . "\"\n";
            print COMPDEL "\tDeleteIniStr " .
              $tmpPath . " \"" .
              $item->WriteIniSectionName() . "\" \"" .
              $item->WriteIniEntryName() . "\"\n";
        }

        # writereg

        $items = defined $metadata ? $metadata->GetWriteRegs() : [];
        foreach my $item (@$items)
        {
            my $regkey =  $item->WriteRegRootKey() .
              " \"" . $item->WriteRegSubKey() . "\" " .
              "\"" . $item->WriteRegKeyName() . "\"";
            print SECFILE "\tWriteRegStr " . $regkey . " \"" . $item->WriteRegValue() . "\"\n";

            #when deleting the component, delete the key if empty
            print COMPDEL "\tDeleteRegValue " . $regkey . "\n";
        }

        # code related to startmenu, writeini writereg --end

        print SECFILE "\tskipSEC$secNum:\n";
        print SECFILE "SectionEnd\n\n\n";

        # close delete function
        print COMPDEL "FunctionEnd\n";

        # code related to metatadata custompage --start
        foreach my $ckey (@customkeys)
        {
            $tmpPath = $custompages->{$ckey}->CustomPageFunctionsFile();

#if ($tmpPath !~ /\$\{.*\}/)
#{
#  $tmpPath = Symbian::SDK::Utils::GetFullPath($sdkcomponent->RootPath(), $tmpPath);
#}
            print SECFILE "!include \"" . $tmpPath . "\"\n";
            print SECFILE "Function User_" . $custompages->{$ckey}->CustomPageName() . "_Pre\n";
            print SECFILE "\t!insertmacro SectionFlagIsSet " .
              "\${SEC$secNum}" . " \${SF_SELECTED} showpage noshow\n";
            print SECFILE "\tshowpage:\n";

#$tmpPath = Symbian::SDK::Utils::GetFullPath($sdkcomponent->RootPath(),canonpath($custompages->{$ckey}->CustomPageIniFile()));
            $tmpPath = $custompages->{$ckey}->CustomPageIniFile();
            print SECFILE "\t!insertmacro MUI_INSTALLOPTIONS_EXTRACT_AS \"$tmpPath\" \"". basename($tmpPath) . "\"\n";
            print SECFILE "\t!insertmacro MUI_HEADER_TEXT \"" .
              $custompages->{$ckey}->CustomPageHeader() ."\" \"" .
              $custompages->{$ckey}->CustomPageSubHeader() ."\"\n";
            if ($custompages->{$ckey}->CustomPageCreatorFunction() )
            {
                print SECFILE "\t!cd \"$rootPath\"\n";
                print SECFILE "\tcall ". $custompages->{$ckey}->CustomPageCreatorFunction() ."\n";
            }
            print SECFILE "\t!insertmacro MUI_INSTALLOPTIONS_DISPLAY \"" . basename($tmpPath) . "\"\n";
            print SECFILE "\tnoshow:\n";
            print SECFILE "FunctionEnd\n\n";

            print SECFILE "Function User_" . $custompages->{$ckey}->CustomPageName() . "_Post\n";
            if ($custompages->{$ckey}->CustomPageLeaveFunction() )
            {
                print SECFILE "\t!cd \"$rootPath\"\n";
                print SECFILE "\tcall ". $custompages->{$ckey}->CustomPageLeaveFunction() ."\n";
            }
            print SECFILE "FunctionEnd\n\n";
        }

        # code related to metadata custompage --end
    } # end of SdkComponent
    print SECFILE "!cd \"$outputdir\"\n";
} # end of sub generateNsisComponents

#================================================================

sub GenerateNsisEnd
{

    #+++++++++++++++++++++++++++++++
    # add Sections desciptions
    print SECFILE "\n\n;Sections Descriptions\n";
    print SECFILE "\t!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN\n";
    my $key = 0;
    foreach $key ( sort {$a <=> $b} keys %{$showlist})
    {
        if ( $showlist->{$key}->{description})
        {
            print SECFILE "\t!insertmacro MUI_DESCRIPTION_TEXT \$\{SEC". $key. "\} \"$showlist->{$key}->{description}\"\n";
        }else
        {
            print SECFILE "\t!insertmacro MUI_DESCRIPTION_TEXT \$\{SEC". $key. "\} \"No description available for this component\"\n";
        }
    }
    print SECFILE "\t!insertmacro MUI_FUNCTION_DESCRIPTION_END\n\n\n";

    #+++++++++++++++++++++++++++++++

    # register all installed componenents and uninstall the reamaining ones
    print SECFILE "Function updateCompReg\n";
    foreach $key ( sort keys %{$showlist} )
    {
        print SECFILE "\tSectionGetFlags \${SEC$key} \$SectionFlags\n";
        print SECFILE "\tIntOp \$SectionFlags \$SectionFlags & \${SF_SELECTED}\n";
        print SECFILE "\tIntCmp \$SectionFlags \${SF_SELECTED} 0 notSelectedSEC$key notSelectedSEC$key\n";
        print SECFILE "\tclearErrors\n";
        print SECFILE "\tWriteRegStr \${PRODUCT_UNINST_ROOT_KEY} \"\${PRODUCT_DIR_REGKEY}\\" .$showlist->{$key}->{Name}. "\" \"ComponentName\" \"". $showlist->{$key}->{Name}. "\"\n";
        print SECFILE "\tifErrors 0 processSEC$key\n";
        print SECFILE "\tgoto processSEC$key\n";
        print SECFILE "\tnotSelectedSEC$key:\n";
        print SECFILE "\tclearErrors\n";
        print SECFILE "\tdeleteRegKey \${PRODUCT_UNINST_ROOT_KEY} \"\${PRODUCT_DIR_REGKEY}\\".$showlist->{$key}->{Name}. "\"\n";
        print SECFILE "\tifErrors 0 delSEC$key\n";
        print SECFILE "\tgoto processSEC$key\n";
        print SECFILE "\tdelSEC$key:\n";
        print SECFILE "\tcall deleteSEC$key\n";
        print SECFILE "\tprocessSEC$key:\n";
    }
    print SECFILE "FunctionEnd\n";
    print SECFILE "\n\n";
    print SECFILE "Function setSelection\n";
    foreach $key ( sort keys %{$showlist} )
    {
        if ( $showlist->{$key}->{CompReq} == 0 && $showlist->{$key}->{CompHid} == 0 )
        {
            print SECFILE "\tSectionGetFlags \${SEC$key} \$SectionFlags\n";
            print SECFILE "\tintCmp \$selAll 1 setSelSEC$key 0\n";
            if ( $showlist->{$key}->{CompDef} == 1 )
            {
                print SECFILE "\tstrCmp \$newInstallation \"1\" setSelSEC$key 0 \n";
            } else
            {
                print SECFILE "\tstrCmp \$newInstallation \"1\" unselectSEC$key 0 \n";
            }
            print SECFILE "\tintCmp \$selAll 1 setSelSEC$key 0\n";
            print SECFILE "\tclearErrors\n";
            print SECFILE "\tReadRegStr \$sectName \${PRODUCT_UNINST_ROOT_KEY} \"\${PRODUCT_DIR_REGKEY}\\".$showlist->{$key}->{Name}."\" \"ComponentName\"\n";
            print SECFILE "\tifErrors 0 selSEC$key\n";
            print SECFILE "\tgoto unselectSEC$key\n";
            print SECFILE "\tselSEC$key:\n";
            print SECFILE "\tstrCmp \$SectName \"".$showlist->{$key}->{Name}."\" 0 nextSEC$key\n";
            print SECFILE "\tsetSelSEC$key:\n";
            print SECFILE "\t!insertmacro SelectSection \${SEC$key}\n";
            print SECFILE "\tgoto nextSEC$key\n";
            print SECFILE "\tunselectSEC$key:\n";
            print SECFILE "\t!insertmacro UnselectSection \${SEC$key}\n";
            print SECFILE "\tnextSEC$key:\n";
        }
    }
    print SECFILE "FunctionEnd\n";

    #+++++++++++++++++++++++++++++++

    #update devices.xml

    print SECFILE "Function addDevice\n";
    print SECFILE "\tReadRegStr \$R0 \${PRODUCT_UNINST_ROOT_KEY} \"Software\\Symbian\\EPOC SDKs\" \"CommonPath\"\n";
    print SECFILE "\tstrCmp \$R0 \"\" 0 +2\n";
    print SECFILE "\tstrCpy \$R0 \"-\"\n";
    print SECFILE "\tstrCpy \$R0 \"\$R0\\devices.xml\"\n";
    my $toolsroot = $sdk->SDKToolsRoot();
    $toolsroot =~ s/\\/\\\\/g;
    my $epocroot = $sdk->SDKEpocRoot();
    $epocroot =~ s/\\/\\\\/g;
    print SECFILE "\tExecWait 'perl \"\$INSTDIR\\updateDevices.pl\" -add -device=\"\$R0\" ".
      "-name=\"" . $sdk->SDKName() . "\" ".
      "-id=\"" . $sdk->SDKId() . "\" ".
      "-kitroot=\"\$INSTDIR\" ".
      "-epocroot=\"$epocroot\" ".
      "-toolsroot=\"$toolsroot\" '\n";
    print SECFILE "FunctionEnd\n\n";

    print SECFILE "Function un.removeDevice\n";
    print SECFILE "\tReadRegStr \$R0 \${PRODUCT_UNINST_ROOT_KEY} \"Software\\Symbian\\EPOC SDKs\" \"CommonPath\"\n";
    print SECFILE "\tstrCmp \$R0 \"\" 0 +2\n";
    print SECFILE "\tstrCpy \$R0 \"-\"\n";
    print SECFILE "\tstrCpy \$R0 \"\$R0\\devices.xml\"\n";
    print SECFILE "\tExecWait 'perl \"\$INSTDIR\\updateDevices.pl\" -remove -device=\"\$R0\" -name=\"".
      $sdk->SDKName() . "\" -id=\"" .
      $sdk->SDKId() . "\"'\n";
    print SECFILE "FunctionEnd\n\n";
}
1;
