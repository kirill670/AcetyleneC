# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# Symbian::SDK::FilterTool::WriteSDK - given a FilterFileList, creates an SDK

package Symbian::SDK::FilterTool::WriteSDK;
use strict;

use Symbian::Config::Basic;
use Symbian::SDK::ContentDefinitionFile;
use Symbian::SDK::FilterTool::FilterFileList;
use Symbian::SDK::SdkDef;
use File::Spec;
use File::Path;
use Symbian::SDK::Utils;
use File::Basename;
use Symbian::Logger::Singleton;

sub new
    {
    my $class = shift;

    my $self = { options => undef };

    bless $self, $class;

    return $self;
    }

sub Run
    {
    my $self = shift;
    my ($options, $files) = @_;

    $self->{options} = $options; # store options

    my $logger = new Symbian::Logger::Singleton;

    my $workArea = File::Spec->canonpath($options->GetSafe("Work area"));
    my $inputArea = File::Spec->canonpath($options->GetSafe("Input area"));
    my $dummy = $options->GetSafe("dummy run");

    my $kitname = $options->GetSafe("SDK name");
    my $kitid = $options->GetSafe("SDK id");

    $logger->Print("Dummy run follows:") if ($dummy);

    $logger->PhaseStart("Removing files");
    my @files = $files->GetIncludedFiles();

    # "work area\sdk name\sdk id" or the subst'd drive from filtertool.pm
    my $destination = $options->Get('sdk output root');

    my $tickfreq = 100; # Print a dot every n files
    my $ticker = $tickfreq;

    foreach my $file (@files)
        {
        $ticker -= 1;
        if (!$ticker)
            {
            $logger->Tick(); # Disable this if we're being verbose
            $ticker = $tickfreq;
            }

        # remove work area from file path
        (my $path = $file) =~ s/^\Q$inputArea\E//i;

        # prepend new destination
        $path = File::Spec->catdir($destination, $path);

        # ensure destination path exists
        my $dir = dirname($path);
        if ((!-d $dir) && (!$dummy))
		{
        	mkpath($dir) or $logger->Warning("Couldn't create path $dir: $!");
        	}

        # move file aside
	if (!$dummy)
		{
        	rename($file, $path) or $logger->Warning("Couldn't move $file to $path: $!");
		}

        $self->RmParent($file);
        }

    $logger->PhaseEnd();

    $logger->PhaseStart("Writing content definition");
    $self->WriteContentDefinitionFile() if (!$dummy);
    $logger->PhaseEnd();

    $logger->PhaseStart("Writing manifest file");
    $self->WriteManifest() if (!$dummy);
    $logger->PhaseEnd();
    }

sub WriteContentDefinitionFile
    {
    my $self = shift;
    my $options = $self->{options}; # save some typing

    # create content definition file obejct
    my $defn = Symbian::SDK::ContentDefinitionFile->new();

    # create groups (order is important here)
    my $groups = {
        src => $defn->AddGroup('Source Files'),
        doc => $defn->AddGroup('Documentation and Examples'),
        emu => $defn->AddGroup('Emulator Files'),
        bld => $defn->AddGroup('Build Environment'),
    };

    # set group defaults
    $groups->{$_}->SetDefault(1) for keys %$groups;

    # short-hand paths (no input area prefixed)
    my $epoc32 = File::Spec->catdir($options->Get('epoc root'), '\epoc32');
    my $source = $options->Get('source root');

    # remove multiple leading backslashes
    $epoc32 =~ s/^\\+/\\/;
    $source =~ s/^\\+/\\/;

    # set group files
    $groups->{src}->AddFile($source.'\*')->SetRecursive(1);
    $groups->{doc}->AddFile('\documentation\*')->SetRecursive(1);
    $groups->{emu}->AddFile($epoc32.'\data\*')->SetRecursive(1);
    $groups->{emu}->AddFile($epoc32.'\tools\epoc.bat');
    $groups->{emu}->AddFile($epoc32.'\tools\epoc.pl');
    $groups->{emu}->AddFile($epoc32.'\wins\*')->SetRecursive(1);
    $groups->{emu}->AddFile($epoc32.'\winscw\*')->SetRecursive(1);
    $groups->{bld}->AddFile('\*')->SetRecursive(1);

    # special file rules with exclusions
    my @nolibs;

    push @nolibs, $groups->{emu}->AddFile($epoc32.'\release\wins\*');
    push @nolibs, $groups->{emu}->AddFile($epoc32.'\release\winscw\*');

    for my $file (@nolibs) {
        $file->SetRecursive(1);
        $file->AddExclude('*.lib');
        $file->AddExclude('*.pdb');
    }

    # add hidden start menu shortcuts group
    my $menu = $defn->AddGroup('Start Menu Shortcuts');
    $menu->SetHidden(1);

    # determine link source directory prefix
    my $prefix = $options->GetSafe('SDK Name').'\\'.$options->GetSafe('SDK ID');

    $menu->AddMetadata('startMenu',
        sourceLink      => $prefix.'\Techview Emulator.lnk',
        destinationLink => $epoc32.'\release\winscw\urel\epoc.exe');

    $menu->AddMetadata('startMenu',
        sourceLink      => $prefix.'\Documentation.lnk',
        destinationLink => 'documentation\developerlibrary\doc_source\index.html');

    # work out the location for the content definition...
    my $file = File::Spec->catdir(
        $options->Get('sdk output root'),
        $epoc32.'\relinfo\contentdefinition.xml');

    # make sure the directory exists...
    my $cddir = File::Basename::dirname($file);
    mkpath($cddir) unless( -d $cddir );

    # write content definition file
    $defn->XML(outputfile => $file);

    # prevent recalculation of file path
    $options->Set('content definition file', $file);
    }

sub WriteManifest
    {
    my $self = shift;
    my $options = $self->{options}; # save some typing

    # determine relative path to root of sdk from known manifest location
    my $epocroot = $options->Get('epoc root');
    my $root = File::Spec->catdir($epocroot, '\epoc32\relinfo');
    $root =~ s/^\\+//;          # remove leading backslashes
    $root =~ s/[^\\]+/../g;     # substitute all directories for ..

    # make content def path relative to root
    my $sdkroot = $options->Get('sdk output root');
    my $contentdef = $options->Get('content definition file');
    $contentdef =~ s/^\Q$sdkroot\E//;

    # create sdk definition file object
    my $sdkdef = Symbian::SDK::SdkDef->New();

    $sdkdef->SDKRootPath($root);
    $sdkdef->SDKName($options->GetSafe("SDK name"));
    $sdkdef->SDKId($options->GetSafe("SDK Id"));
    $sdkdef->SDKPublisherName($options->GetSafe("Publisher name"));
    $sdkdef->SDKDescription($options->Get("SDK description"));
    $sdkdef->SDKEpocRoot($epocroot);
    $sdkdef->SDKToolsRoot($options->Get("Tools root") || "\\" );
    $sdkdef->SDKSourceRoot($options->Get("Source root") || "\\src\\");
    $sdkdef->SDKExamplesRoot($options->Get("Examples root") || "\\src\\common\\developerlibrary\\examples\\");
    $sdkdef->SDKIncludeRoot($options->Get("Include root") || "\\epoc32\\include\\");
    $sdkdef->SDKDocumentationRoot($options->Get("Documentation root") || "\\src\\common\\developerlibrary\\doc_source\\");
    $sdkdef->SDKPublisherWebSite($options->Get("Publisher web site"));
    $sdkdef->SDKLicenseName($options->Get("SDK license"));
    $sdkdef->SDKReadmeName($options->Get("readme file"));
    $sdkdef->SetContentDefinitionFiles($contentdef);
    $sdkdef->AddSDKSection("Symbian OS", {
        build    => $options->Get("Build number"),
        cppflags => $options->Get("cpp flags")});


    # hardwired for the moment, the list of components should be drived from the contentdefinition object.
    my @installed = ("Source Files","Documentation and Examples","Emulator Files","Build Environment");
    $sdkdef->SDKInstalled( @installed );

    # write manifest
    my $manifest = File::Spec->catfile(
        $options->GetSafe('sdk output root'),
        $options->GetSafe('epoc root'),
        'epoc32\relinfo\manifest.xml');

    mkpath(dirname($manifest));
    $sdkdef->Write($manifest);
    }

sub RmParent
    {
    my $self = shift;
    my ($file) = @_;

    my $dir = dirname($file);
    $self->RmParent($dir) if rmdir($dir);
    }

1;
