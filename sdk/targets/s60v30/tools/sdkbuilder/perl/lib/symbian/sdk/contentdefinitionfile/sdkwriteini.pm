#!perl
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# SdkWriteIni - Module to create/update SdkWriteIni object that correspond to a writeIni xml element
#

package Symbian::SDK::ContentDefinitionFile::SdkWriteIni;

use strict;
use Symbian::Logger::Singleton;
use FindBin;

# New() : create a SdkWriteIni object that correspond to an entry in an .ini file
#
# Parameters:
#   - ini filename
#   - entry name
#   - value
#   - section name
# Returns:
#   the newly created SdkWriteIni object reference
sub New
{
    my $pkg = shift;
    my $self = {};
    $self->{logger} = Symbian::Logger::Singleton->new();
    bless $self, $pkg;
    $self->{iniFilename} = shift;
    $self->{sectionName} = shift;
    $self->{entryName} = shift;
    $self->{value} = shift;

    return $self;
}
sub Validate
{
    my $self = shift;
    my $rootpath = shift;

}

# WriteIniIniFilename() : get/set ini filename
#
# Parameters:
#   - ini file name
# Returns:
#   - ini file name
sub WriteIniIniFilename
{
    my $self = shift;
    my $newval = shift;
    $self->{iniFilename} = $newval if defined $newval;
    return $self->{iniFilename};
}

# WriteIniEntryName() : get/set an entry name
#
# Parameters:
#   - entry name
# Returns:
#   - entry name
sub WriteIniEntryName
{
    my $self = shift;
    my $newval = shift;
    $self->{entryName} = $newval if defined $newval;
    return $self->{entryName};
}

# WriteIniValue() : get/set ini value
#
# Parameters:
#   - ini value
# Returns:
#   - ini value
sub WriteIniValue
{
    my $self = shift;
    my $newval = shift;
    $self->{value} = $newval if defined $newval;
    return $self->{value};
}

# WriteIniSectionName() : get/set section name
#
# Parameters:
#   - section name
# Returns:
#   - section name
sub WriteIniSectionName
{
    my $self = shift;
    my $newval = shift;
    $self->{sectionName} = $newval if defined $newval;
    return $self->{sectionName};
}

1;

__END__
sub New
sub WriteIniIniFilename
sub WriteIniEntryName
sub WriteIniValue
sub WriteIniSectionName
