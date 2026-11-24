#!perl
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# SdkCustomPage - Module to create/update SdkCustomPage that correspond to a customPage xm element
#

package Symbian::SDK::ContentDefinitionFile::SdkCustomPage;
use File::Spec::Functions;
use strict;
use Symbian::Logger::Singleton;
use FindBin;

# New() : create a new SdkCustomPage
#
# Parameters:
#   - order : the index of the custom page
#   - header : header text to be displayed on the custom page
#   - subHeader : the sub header text to be displayed on the custom page
#   - scriptFile : the associated script to be run for this custom page
#   - iniFile : the nsis ini file that defines the fields of custom page
#   - name : custom page name
#   - creatorFunction name
#   - leaveFunction name
#   - functionsFile name
# Returns:
#   - the newly created SdkCustomPage object reference.
sub New
{
    my $pkg = shift;
    my $self = {};
    my ($order,$name,$header,$subHeader,$iniFile,$scriptFile,$creatorFunction,$leaveFunction,$functionsFile) = @_;
    $self->{logger} = Symbian::Logger::Singleton->new();
    bless $self, $pkg;
    $self->{order} = $order if $order;
    $self->{header} = $header if $header;
    $self->{subHeader} = $subHeader if $subHeader;
    $self->{scriptFile} = $scriptFile if $scriptFile;
    $self->{iniFile} = $iniFile if $iniFile;
    $self->{name} = $name if $name;
    $self->{creatorFunction} = $creatorFunction if $creatorFunction;
    $self->{leaveFunction} = $leaveFunction if $leaveFunction;
    $self->{functionsFile} = $functionsFile if $functionsFile;
    return $self;
}

sub Validate
{
    my $self = shift;
    my $rootpath = shift;
    my $logger = $self->{logger};
    my $bin = $FindBin::Bin;

    my $ini = $self->CustomPageIniFile();
    $logger->Die("CustomPage : " . $self->{name} . " Ini file not defined.") if !$ini;
    $ini =~ s/\$\{SDKTOOLS_PATH\}/$bin/;
    $ini = Symbian::SDK::Utils::GetFullPath($rootpath,$ini);
    $logger->Die("CustomPage : " . $self->{name} . " Ini file $ini does not exists.") if !-f $ini;
    $self->CustomPageIniFile($ini);

    my $script = $self->CustomPageScriptFile();
    if ($script)
    {
        $script =~ s/\$\{SDKTOOLS_PATH\}/$bin/;
        $script = Symbian::SDK::Utils::GetFullPath($rootpath,$script);
        $logger->Die("CustomPage : " . $self->{name} . " Script file $script does not exists.") if !-f $script;
    }
    $self->CustomPageScriptFile($script);
    my $funcfile = $self->CustomPageFunctionsFile();
    if ($funcfile)
    {
        $funcfile =~ s/\$\{SDKTOOLS_PATH\}/$bin/;
        $funcfile = Symbian::SDK::Utils::GetFullPath($rootpath,$funcfile);

        $logger->Die("CustomPage : " . $self->{name} . " Functions file $funcfile does not exists.") if !-f $funcfile;
    }
    $self->CustomPageFunctionsFile($funcfile);
}

# CustomPageOrder() : get/set the custom page order/index
#
# Parameters:
#   - order
# Returns:
#   - order
sub CustomPageOrder
{
    my $self = shift;
    my $newval = shift;
    $self->{order} = $newval if defined $newval;
    return $self->{order};
}

# CustomPageHeader() : set/get the custom page header
#
# Parameters:
#   - header
# Returns:
#   - header
sub CustomPageHeader
{
    my $self = shift;
    my $newval = shift;
    $self->{header} = $newval if defined $newval;
    return $self->{header};
}

# CustomPageSubHeader() : get/set the custom page subheader
#
# Parameters:
#   - subheader
# Returns:
#   - subheader
sub CustomPageSubHeader
{
    my $self = shift;
    my $newval = shift;
    $self->{subHeader} = $newval if defined $newval;
    return $self->{subHeader};
}

# CustomPageScriptFile() : get/set the script file name
#
# Parameters:
#   - script file name
# Returns:
#   - script file name
sub CustomPageScriptFile
{
    my $self = shift;
    my $newval = shift;
    $self->{scriptFile} = lc(canonpath($newval)) if defined $newval;
    return $self->{scriptFile};
}

# CustomPageIniFile() : get/set the ini file name
#
# Parameters:
#   - ini file name
# Returns:
#   - ini file name
sub CustomPageIniFile
{
    my $self = shift;
    my $newval = shift;
    $self->{iniFile} = lc(canonpath($newval)) if defined $newval;
    return $self->{iniFile};
}

# CustomPageName() : get/set custom page name
#
# Parameters:
#   - name
# Returns:
#   - name
sub CustomPageName
{
    my $self = shift;
    my $newval = shift;
    $self->{name} = $newval if defined $newval;
    return $self->{name};
}

# CustomPageCreatorFunction() : get/set the script file name
#
# Parameters:
#   - Function name
# Returns:
#   - Function name
sub CustomPageCreatorFunction
{
    my $self = shift;
    my $newval = shift;
    $self->{creatorFunction} = $newval if defined $newval;
    return $self->{creatorFunction};
}

# CustomPageLeaveFunction() : get/set the script file name
#
# Parameters:
#   - script file name
# Returns:
#   - script file name
sub CustomPageLeaveFunction
{
    my $self = shift;
    my $newval = shift;
    $self->{leaveFunction} = $newval if defined $newval;
    return $self->{leaveFunction};
}

# CustomPageFunctionsFile() : get/set the CP functions file name
#
# Parameters:
#   - functions file name
# Returns:
#   - functions file name
sub CustomPageFunctionsFile
{
    my $self = shift;
    my $newval = shift;
    $self->{functionsFile} = lc(canonpath($newval)) if defined $newval;
    return $self->{functionsFile};
}

1;

__END__
sub New creates a new object
sub CustomPageOrder
sub CustomPageHeader
sub CustomPageSubHeader
sub CustomPageScriptFile
sub CustomPageIniFile
sub CustomPageName
