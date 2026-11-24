#!perl
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# SdkExecute - Module to create/update SdkExecute object that correspond to a execute xml element
#

package Symbian::SDK::ContentDefinitionFile::SdkExecute;
use strict;
use Symbian::Logger::Singleton;

# New() : create a new SdkExecute object
#
# Parameters:
#   - type : pre/post
#   - application : name of the application to execute
#   - parameters : the list of parameters to be fed to the application
# Returns:
#   - the newly created SdkExecute object reference
sub New
{
    my $pkg = shift;
    my $self = {};
    $self->{logger} = Symbian::Logger::Singleton->new();
    bless $self, $pkg;
    $self->{type} = shift;
    $self->{application} = shift;
    $self->{parameters} = shift;
    return $self;
}

sub validate
{
    my $self = shift;
    my $rootpath = shift;

}

# ExecuteType() : get/set type
#
# Parameters:
#   - type
# Returns:
#   - type
sub ExecuteType
{
    my $self = shift;
    my $newval = shift;
    $self->{type} = lc($newval) if defined $newval;
    return $self->{type};
}

# ExecuteApplication() : get/set application
#
# Parameters:
#   - application name
# Returns:
#   - application name
sub ExecuteApplication
{
    my $self = shift;
    my $newval = shift;
    $self->{application} = $newval if defined $newval;
    return $self->{application};
}

# ExecuteParameters() : get/set parameters
#
# Parameters:
#   - parameters as a string
# Returns:
#   - parameters as a string
sub ExecuteParameters
{
    my $self = shift;
    my $newval = shift;
    $self->{parameters} = $newval if defined $newval;
    return $self->{parameters};
}

1;

__END__
sub New create a new SdkExecute object
sub ExecuteType
sub ExecuteApplication
sub ExecuteParameters
