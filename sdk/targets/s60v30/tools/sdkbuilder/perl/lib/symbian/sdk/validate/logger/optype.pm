#!perl -w
#
# O p T y p e
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#
use strict;
package Symbian::SDK::Validate::Logger::OpType;

#
# A very simple class that stores the name, severity and score of a certain
# output type as used by 'TestOut'. When a type such as 'FAIL:' is
# required, we must record how many times this kind of output (score) been
# reported within a single 'TestOut' object. It is also useful to record the
# severity of this kind of log (0 - not severe, e.g 'Pass:', bigger numbers
# more severe).
#
sub new
{
    my $arg = shift;
    my $class = ref($arg) || $arg;
    my $name = shift;
    my $severity = shift;
    my $verbose = shift;

    my $self = {
                    name  => $name,
                    severity => $severity,
                    verbose => $verbose,
                    score => 0,
               };

    bless $self, $class;
    return $self;
}

# Set/Get the name of the output type.
sub Name
{
    my $self = shift;
    return undef unless(ref($self));
    my $name = shift;

    if( defined($name) )
    {
        $self->{name} = $name ;
    }
    return $self->{name};
}

# Set/Get the severity of the output type.
sub Severity
{
    my $self = shift;
    return undef unless(ref($self));
    my $severity = shift;

    if( defined($severity) )
    {
        $self->{severity} = $severity ;
    }
    return $self->{severity};
}

# Set/Get the verbose flag.
sub Verbose
{
    my $self = shift;
    return undef unless(ref($self));
    my $verbose = shift;

    if( defined($verbose) )
    {
        $self->{verbose} = $verbose ;
    }
    return $self->{verbose};
}

# Get the score of the output type.
sub Score
{
    my $self = shift;
    return undef unless(ref($self));

    return $self->{score};
}

# Set the score for an output type. Not used normally hence not combined with
# 'Score' above. Required to be able to reset logs to a previous state.
sub SetScore
{
	my $self = shift;
	return undef unless(ref($self));
	my $newscore = shift;
	$self->{score} = $newscore if(defined($newscore));
	return $self->{score};
}

# Add to the score of the output type. You could use negative numbers, there
# is nothing to prevent you but I think that's probably a bad idea.
sub AddToScore
{
    my $self = shift;
    return undef unless(ref($self));
    my $add = shift;
    $add = 0 unless( defined($add) );
    $self->{score} += $add;
    return $self->Score;
}

1;
