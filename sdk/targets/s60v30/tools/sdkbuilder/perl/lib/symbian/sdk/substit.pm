#!perl -w
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
# Substit - Module to automatically create subst'd drives
#
use strict;

#
# A simple class to create subst'd drives. This is useful when we may have
# the potential of exceeding Window's 256 character path length limit.
#

package Symbian::SDK::Substit;

# Create a new 'substit' object..
sub new
{
    my $arg = shift;
    my $class = ref($arg) || $arg;
    my $home = shift;
    return undef unless($home);
    my $wanted = shift;

    my $self = { homepath => $home,
                 drivelet => undef };
    
    bless $self, $class;
    return undef unless($self->dosubst($wanted));
    return $self;
}

# Run the 'subst' command to create the subst'd drive. If the 'wanted'
# parameter is set this will attempt to get that drive letter (in which
# case it will try only once). If no drive letter is provided this will
# run through the alphabet trying to create a subst until success or 'Z'.
sub dosubst
{
    my $self = shift;
    return undef unless(ref($self));
    return undef unless(-d $self->{homepath});
    my $wanted = uc(shift);
    my $drive = $wanted;
    $drive = 'B' unless($drive);

    # If drivelet is already defined delete the subst..
    if($self->{drivelet})
    {
        system("subst " . $self->{drivelet} . ": /d > nul 2>&1" );
        undef($self->{drivelet});
    }
    
    my $success;
    while(ord($drive) <= ord('Z'))
    {
        $success = 1;
        system("subst $drive: " . $self->{homepath} . "> nul 2>&1" ) or last;
        $success = 0;
        last if($wanted);       # Only one attempt if drive letter specified.
        $drive = chr(ord($drive) + 1);
    }
    $self->{drivelet} = $drive if($success);
    return $self->{drivelet};
}

sub SubstPath
{
    my $self = shift;
    return undef unless(ref($self));
    return undef unless($self->{drivelet});
    return( $self->{drivelet} . ":\\" );
}

sub HomePath
{
    my $self = shift;
    return undef unless(ref($self));
    return $self->{homepath};
}

sub DESTROY
{
    my $self = shift;
    return unless(ref($self));
    if($self->{drivelet})
    {
        system("subst " . $self->{drivelet} . ": /d > nul 2>&1" );
    }
    return;
}

1;


__END__

sub new 
creates new new 'Substit' object. Expects (mandatory) the path to subst and (optionally) the wanted drive letter.

=============

getters/setters

sub SubstPath
sub HomePath
