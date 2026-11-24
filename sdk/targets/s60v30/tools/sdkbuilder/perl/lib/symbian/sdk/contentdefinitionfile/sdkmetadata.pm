#!perl
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# SdkMetaData - Module to create/update SdkMetaData object that correspond to a metadata xml element
#

package Symbian::SDK::ContentDefinitionFile::SdkMetaData;

use strict;
use Symbian::Logger::Singleton;

# New() : create a SdkMetaData object that correspond to a metadata xml element
# SdkMetaData is a conatainer for SdkCustomPage, SdkExecute, SdkStartMenu, and SdkWriteIni
# other elements may be added in the future.
#
# Parameters:
#   - none
# Returns:
#   - an empty SdkStartMenu object reference
sub New
{
    my $pkg = shift;
    my $self = {};
    $self->{logger} = Symbian::Logger::Singleton->new();
    bless $self, $pkg;
    $self->{customPage} = {};
    $self->{execute} = [];
    $self->{startMenu} = [];
    $self->{writeIni} = [];
    $self->{writeReg} = [];
    return $self;
}

sub Validate($)
{
    my $self = shift;
    my $rootpath = shift;

    foreach my $custompage (values %{$self->GetCustomPages()})
    {
        $custompage->Validate($rootpath);
    }
    foreach my $execute (@{$self->GetExecutes()})
    {
        $execute->Validate($rootpath);
    }
    foreach my $startmenu (@{$self->GetStartMenus()})
    {
        $startmenu->Validate($rootpath);
    }
    foreach my $writeini (@{$self->GetWriteInis()})
    {
        $writeini->Validate($rootpath);
    }
    foreach my $writereg (@{$self->GetWriteRegs()})
    {
        $writereg->Validate($rootpath);
    }
}

# addCustumPage() : add a SdkCustomPage object to the existing list.
#
# Parameters:
#   - SdkCustomPage object reference
# Returns:
#   - status : 1 success - 0 fail
sub AddCustomPage
{
    my $self = shift;
    my $custom = shift;
    if (exists $self->{customPage}->{$custom->CustomPageOrder()})
    {
        $self->{logger}->Error("Can not add custompage ".$custom->CustomPageName(). " : oder " . $custom->CustomPageOrder() . " already allocated.");
        return 0;
    }
    $self->{customPage}->{$custom->CustomPageOrder()} = $custom;
    return 1;
}

# removeCustomPage() : remove a SdkCustomPage from the existing list.
#
# Parameters:
#   - a customPage name
# Returns:
#   - status: 1 success - 0 fail
sub RemoveCustomPage
{
    my $self = shift;
    my $name = shift;
    my $custom = $self->GetCustomPageByName($name);
    if (!defined $custom)
    {
        $self->{logger}->Error("Can not delete Custom page: $name does not exist.");
        return 0;
    }
    delete $self->{customPage}->{$custom->CustomPageOrder()};
    return 1;
}

# getCustomPageByName() : get a SdkCustomPage object from the existing list by name
#
# Parameters:
#   - customPage name
# Returns:
#   - a SdkCustomPage reference
sub GetCustomPageByName
{
    my $self = shift;
    my $name = shift;
    if (exists $self->{customPage})
    {
        foreach my $ckey (keys %{$self->GetCustomPages()})
        {
            if ($self->{customPage}->{$ckey}->CustomPageName() eq $name)
            {
                return $self->{customPage}->{$ckey};
            }
        }
    }
    return undef;
}

# getCustomPageByOrder() : get a SdkCustomPage object from the existing list by order
#
# Parameters:
#   - customPage order
# Returns:
#   - a SdkCustomPage object refrence
sub GetCustomPageByOrder
{
    my $self =shift;
    my $order = shift;
    if (exists $self->{customPage}->{$order})
    {
        return $self->{customPage}->{$order};
    }
    return undef;
}

# getCustomPages() : get the existing list of SdkCustomPage objects
#
# Parameters:
#   - none
# Returns:
#   - Hash of SdkCustomPage keyed on their order
sub GetCustomPages
{
    my $self = shift;
    return $self->{customPage};
}

# addExecute() : add a SdkExecute object to the existing list
#
# Parameters:
#   - a SdkExecute object reference
# Returns:
#   - none
sub AddExecute
{
    my $self = shift;
    my $execute = shift;
    push @{$self->{execute}}, $execute;
}

# getExecutes() : get the existing list of SdkExecute objects
#
# Parameters:
#   - none
# Returns:
#   - array of SdkExecute objects
sub GetExecutes
{
    my $self = shift;
    return exists $self->{execute}
      ? $self->{execute}
      : [];
}

# addStartMenu() : add a SdkStartMenu object to the existing list
#
# Parameters:
#   - SdkStartMenu object reference
# Returns:
#   - none
sub AddStartMenu
{
    my $self = shift;
    my $startmenu = shift;
    push @{$self->{startMenu}}, $startmenu;
}

# getStartMenus() : get the existing list of SdkStartMenu objects
#
# Parameters:
#   - none
# Returns:
#   - array of SdkStartMenu objects
sub GetStartMenus
{
    my $self = shift;
    return $self->{startMenu};
}

# addWriteIni() : add a SdkWriteIni object to the existing list
#
# Parameters:
#   - a SdkStartIni object reference
# Returns:
#   - none
sub AddWriteIni
{
    my $self = shift;
    my $writeini = shift;
    push @{$self->{writeIni}}, $writeini;
}

# getWriteInis() : get the existing list of SdkWriteIni objects
#
# Parameters:
#   - none
# Returns:
#   - array of SdkWriteIni objects
sub GetWriteInis
{
    my $self = shift;
    return $self->{writeIni};
}

# addWriteReg() : add a SdkWriteReg Object to the existing list
#
# Parameters:
#   - a SdkWriteReg object reference
# Returns:
#   - none
sub AddWriteReg
{
    my $self = shift;
    my $writereg = shift;
    push @{$self->{writeReg}}, $writereg;
}

# getWriteRegs() : get the existing list of SdkWriteReg objects
#
# Parameters:
#   - none
# Returns:
#   - array of SdkWriteReg objects
sub GetWriteRegs
{
    my $self = shift;
    return $self->{writeReg};
}

1;

__END__
sub New creates a new SdkMetaData object
sub AddCustomPage
sub RemoveCusrtomPage
sub GetCustomPageByName
sub GetCustomPageByOrder
sub GetCustomPages
sub AddStartMenu
sub GetStartMenus
sub AddWriteIni
sub GetWriteInis
sub AddWriteReg
sub GetWriteRegs
