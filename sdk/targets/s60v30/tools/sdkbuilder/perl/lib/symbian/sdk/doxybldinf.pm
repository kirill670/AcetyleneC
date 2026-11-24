# DoxyBldInf.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::SDK::DoxyBldInf;
use strict;

use Carp;
use File::Basename;
use Symbian::ExportInfo;
use XML::Parser;

sub new {
    my $class = shift;
    my $self = bless {
        active  => 0,
        current => undef,
        exinf   => Symbian::ExportInfo->new(),
        file    => undef,
        parser  => undef,
        targets => {},
    }, $class;
    $self->init();
    return $self;
}

sub init {
    my $self = shift;
    $self->{parser} = XML::Parser->new();
    $self->{parser}->setHandlers(
        Start => sub { $self->start_element(@_) },
        End   => sub { $self->end_element(@_) });
}

sub GetTargetSource {
    my $self = shift;
    my $target = shift;
    my $ref = $self->{targets}{$target};
    return if !defined $ref;
    return [ @{$ref->{source}} ];
}

sub GetTargets {
    my $self = shift;
    return $self->{targets};
}

sub parse {
    my $self = shift;
    my $file = shift;
    $self->{file} = $file;
    return $self->{parser}->parsefile($file);
}

sub start_element {
    my $self = shift;
    my $parser = shift;
    my $element = shift;
    my %attrib = @_;

    # start caring when we see a TargetSources
    if ($element eq 'TargetSources') {
        $self->{active} = 1;
    }

    return if !$self->{active};

    # grab name of target and (possible) destination
    if ($element eq 'Target') {

        # append / if destination is a directory
        if (length($attrib{path}) and basename($attrib{path}) !~ /\./) {
            $attrib{path} .= '/';
        }

        # use Symbian::ExportInfo to determine target path
        my $target = $self->{exinf}->resolve_dest($attrib{name}, $attrib{path});

        # add this to the list of targets
        $self->{targets}{$target} = {
            file   => $self->{file},
            name   => $attrib{name},
            source => [],
        };

        # set current so we know where to put source paths
        $self->{current} = $self->{targets}{$target};
    }

    # add source Path to list of source for target
    if ($element eq 'Path') {
        push @{$self->{current}{source}}, $attrib{value};
    }
}

sub end_element {
    my $self = shift;
    my $parser = shift;
    my $element = shift;

    # stop caring when we see the end of TargetSources
    if ($element eq 'TargetSources') {
        $self->{active} = 0;
    }
}

1;
