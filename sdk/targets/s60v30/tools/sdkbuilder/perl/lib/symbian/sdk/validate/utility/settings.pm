#!perl -w
#
# S e t t i n g s
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

use strict;
package Symbian::SDK::Validate::Utility::Settings;

#
# This class holds information which is required to persist for some time,
# either between parsing and execution, or during a test execution, or
# within a single test step.
#

sub new
{
    my $arg = shift;
    my $class = ref($arg) ? ref($arg) : $arg;

    my $self = {
                   settings => {},
               };

    bless $self, $class;
    return $self;
}

# Settings to store during execution of the test file. These persist between
# commands. Well generally, :)
# The value can be anything and is often a reference to an array (e.g
# for storing lists) etc.
sub GetSet
{
    my $self = shift;
    return undef unless(ref($self));
    my $name = shift;
    return undef unless(defined($name));
    my $value = shift;

    $self->{settings}->{$name} = $value if( defined($value) );
    return $self->{settings}->{$name};
}

# Remove a setting.
sub Unset
{
    my $self = shift;
    return undef unless(ref($self));
    my $name = shift;
    return undef unless(defined($name));

    delete($self->{settings}->{$name});
    return undef;
}


# Return a new copy of this settings object.
sub Copy
{
    my $self = shift;
    return undef unless(ref($self));
    my $newset = Symbian::SDK::Validate::Utility::Settings->new();
    return undef unless(ref($newset));
    for my $key (keys %{$self->{settings}})
    {
        $newset->GetSet( $key, $self->GetSet($key) );
    }
    return $newset;
}

1;
