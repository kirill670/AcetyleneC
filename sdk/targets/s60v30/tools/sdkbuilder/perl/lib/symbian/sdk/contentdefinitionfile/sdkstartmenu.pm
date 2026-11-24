#!perl
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# SdkStartMenu - Module to create/update SdkStartMenu object that correspond to a startMenu xml element
#

package Symbian::SDK::ContentDefinitionFile::SdkStartMenu;

use strict;
use Symbian::Logger::Singleton;

# New() : create a SdkStartMenu object that correspond to a startMenu xml element
#
# Parameters:
#   - link source
#   - link destination
# Returns:
#   the newly created SdkStartMenu object reference
sub New
{
    my $pkg = shift;
    my $self = {};
    $self->{logger} = Symbian::Logger::Singleton->new();
    bless $self, $pkg;
    $self->{sourceLink} = shift;
    $self->{destinationLink} = shift;
    $self->{parameters} = shift;
    $self->{iconFile} = shift;
    $self->{iconIndex} = shift;
    $self->{startOptions} = shift;
    $self->{keyboardShortcut} = shift;
    $self->{description} = shift;
    return $self;
}
sub Validate
{
    my $self = shift;
    my $rootpath = shift;

}

# StartMenuSourceLink() : set/get the link source
#
# Parameters:
#   - link source
# Returns:
#   - link source
sub StartMenuSourceLink
{
    my $self = shift;
    my $newval = shift;
    $self->{sourceLink} = $newval if defined $newval;
    return $self->{sourceLink};
}

# StartMenuDestinationLink() : set/get the link destination
#
# Parameters:
#   - link destination
# Returns:
#   - link destination
sub StartMenuDestinationLink
{
    my $self = shift;
    my $newval = shift;
    $self->{destinationLink} = $newval if defined $newval;
    return $self->{destinationLink};
}

# StartMenuParameters() : set/get parameters
#
# Parameters:
#   - parameters string
# Returns:
#   - parameters string
sub StartMenuParameters
{
    my $self = shift;
    my $newval = shift;
    $self->{parameters} = $newval if defined $newval;
    return $self->{parameters} || "";
}

# StartMenuIconFile() : set/get the icon file
#
# Parameters:
#   - icon file
# Returns:
#   - ison file
sub StartMenuIconFile
{
    my $self = shift;
    my $newval = shift;
    $self->{iconFile} = $newval if defined $newval;
    return $self->{iconFile} || "";
}

# StartMenuIconIndex() : set/get the icon index
#
# Parameters:
#   - icon index number
# Returns:
#   - icon index number
sub StartMenuIconIndex
{
    my $self = shift;
    my $newval = shift;
    $self->{iconIndex} = $newval if defined $newval;
    return defined $self->{iconIndex}?  $self->{iconIndex} : 0;
}

# StartMenuStartOptions() : set/get the start options
#
# Parameters:
#   - start options (string)
# Returns:
#   - start options (string)
sub StartMenuStartOptions
{
    my $self = shift;
    my $newval = shift;
    $self->{startOptions} = $newval if defined $newval;
    return $self->{startOptions} || "";
}

# StartMenuKeyboardShortcut() : set/get keyboard shortcut
#
# Parameters:
#   - keyboard shortcut (string)
# Returns:
#   - keyboard shortcut (string)
sub StartMenuKeyboardShortcut
{
    my $self = shift;
    my $newval = shift;
    $self->{keyboardShortcut} = $newval if defined $newval;
    return $self->{keyboardShortcut} || "";
}

# StartMenuDescription() : set/get description
#
# Parameters:
#   - description
# Returns:
#   - description
sub StartMenuDescription
{
    my $self = shift;
    my $newval = shift;
    $self->{description} = $newval if defined $newval;
    return $self->{description} || "";
}

1;

__END__
sub New creates a new object
sub StartMenuSourceLink
sub StartMenuDestinationLink
