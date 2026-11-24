#!perl
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# SdkComponent - Module to create/update SdkWriteReg object that correspond to a writeReg xml element
#

package Symbian::SDK::ContentDefinitionFile::SdkWriteReg;

use strict;
use Symbian::Logger::Singleton;

# New() : Creates a new SdkWriteReg object that corresponds to a xml writeReg element
#
# Parameters:
#   - registry ROOT KEY : HKCR, HKLM, HKCU, HKU, HKCC, HKDD, HKPD
#   - subkey
#   - key name
#   - value
# Returns:
#   $self - the newly created SdkWriteReg object reference
sub New
{
    my $pkg = shift;
    my $self = {};
    $self->{logger} = Symbian::Logger::Singleton->new();
    bless $self, $pkg;
    $self->{rootKey} = shift;
    $self->{subKey} = shift;
    $self->{keyName} = shift;
    $self->{value} = shift;
    return $self;
}
sub Validate
{
    my $self = shift;
    my $rootpath = shift;

}

# WriteRegRootKey() : getter/setter registry rootkey
#
# Parameters:
#   root key
# Returns:
#   root key

sub WriteRegRootKey
{
    my $self = shift;
    my $newval = shift;
    $self->{rootKey} = $newval if defined $newval;
    return $self->{rootKey};
}

# WriteRegSubKey() : getter/setter registry subkey
#
# Parameters:
#   subkey
# Returns:
#   subkey

sub WriteRegSubKey
{
    my $self = shift;
    my $newval = shift;
    $self->{subKey} = $newval if defined $newval;
    return $self->{subKey};
}

# WriteRegkeyName() : getter/setter registry key name
#
# Parameters:
#   key name
# Returns:
#   key name

sub WriteRegKeyName
{
    my $self = shift;
    my $newval = shift;
    $self->{keyName} = $newval if defined $newval;
    return $self->{keyName};
}

# WriteRegValue() : registry key value
#
# Parameters:
#   key value
# Returns:
#   key value
sub WriteRegValue
{
    my $self = shift;
    my $newval = shift;
    $self->{value} = $newval if defined $newval;
    return $self->{value};
}

1;
