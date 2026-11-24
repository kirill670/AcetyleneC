#!perl
# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved.
#
#  Symbian::SDK::FilterTool::UserRule - Module to create/update UserRule objects
#
package Symbian::SDK::FilterTool::UserRule;
use strict;
use Symbian::Logger::Singleton;

# new() : create a new Symbian::SDK::FilterTool::UserRule object
#
# Parameters:
#   operation - (String) 'include' or 'exclude'
#   location - (String) path e.g /epoc32/release/*/z/PLATTEST/
#   groups - (String) comma separated list of groups names e.g. 'other,non_os'
#   recursive - (String) 'true' or 'false'
#   extension - (String) file extension e.g '*.*'
# Returns:
#   Ref to the new Symbian::SDK::FilterTool::UserRule object
sub new
{
    my $pkg = shift;
    my $self = {
        operation => shift,
        location => shift,
        groups => shift,
        recursive => shift,
        extension => shift};
    $self->{logger} = Symbian::Logger::Singleton->new();
    bless $self, $pkg;
    return $self;
}

# Validate() : validates a Symbian::SDK::FilterTool::UserRule object
#
# Parameters:
#   groups - (List) list of all defined groups names
# Returns:
#   validation status : 1-valid, 0-invalid

sub Validate
{
    my $self = shift;
    my $groups = shift;
    my $message;
    $message .= "location = " . $self->{location} . " " if (defined $self->{location});
    $message .= "groups = " . $self->{groups} . " " if (defined $self->{groups});
    $message .= "recursive = " . $self->{recursive} . " " if (defined $self->{recursive});
    $message .= "extension = " . $self->{extension} . " " if (defined $self->{extension});
    $self->{valid} = 1;

    my $operation = lc($self->Operation());
    if (!$operation || ($operation ne 'exclude' && $operation ne 'include'))
    {
        $self->{logger}->Error("$message : Operation must be either 'include' or 'exclude' ");
        $self->{valid} = 0;
    }

    if (!defined $self->FilesExtension())
    {
        $self->{logger}->Error("$message : File extension not defined ");
        $self->{valid} = 0;
    }

    my @founds = ();
    foreach my $group (@{$self->Groups()})
    {
        foreach my $definedGroup (@{$groups})
        {
            if (lc($definedGroup) eq lc($group))
            {
                foreach my $found (@founds)
                {
                    if ($found eq $group)
                    {
                        $self->{logger}->Error("$message : Group $group is defined more than once");
                        $self->{valid} = 0;
                    }
                }
                push @founds, $group;
            }
        }
        if (scalar @founds < 1)
        {
            $self->{logger}->Error("$message : Group $group is not a valid group name");
            $self->{valid} = 0;
        }
    }
    return $self->{valid};
}

# Operation() : getter/setter
#
# Parameters:
#   $newval - optional (String) name of the operation 'include' or 'exclude'
# Returns:
#   operation - (String)
sub Operation
{
    my $self = shift;
    my $newval = shift;
    $self->{operation} = lc($newval) if defined $newval;
    return $self->{operation};
}

# FileExtension() : getter/setter
#
# Parameters:
#   $newval - optional (String) file extension
# Returns:
#   fileextension - (String)
sub FilesExtension
{
    my $self = shift;
    my $newval = shift;
    $self->{extension} = $newval if defined $newval;
    return $self->{extension};
}

# FileLocation() : getter/setter
#
# Parameters:
#   $newval - optional (String) filelocation path
# Returns:
#   filelocation - (String)
sub FilesLocation
{
    my $self = shift;
    my $newval = shift;
    $self->{location} = $newval if defined $newval;
    return $self->{location};
}

# Groups() : getter/setter
#
# Parameters:
#   $newval - optional (String) comma separated list of groups
# Returns:
#   Goups names - (list)
sub Groups
{
    my $self = shift;
    my $newval = shift;
    $self->{groups} = $newval if defined $newval;
    my @groups = defined $self->{groups} ? split(/,/,$self->{groups}) : ();
    return \@groups;
}

# Recursive() : getter/setter
#
# Parameters:
#   $newval - optional (String) Recursive 'true' or 'false'
# Returns:
#   operation - 1-recursive, 0-not recursive
sub Recursive
{
    my $self = shift;
    my $newval = shift;
    $self->{recursive} = lc($newval) if defined $newval;
    if (exists ($self->{recursive}) && $self->{recursive} =~ /true/i)
    {
        return 1;
    } else
    {
        return 0;
    }
}

1;
