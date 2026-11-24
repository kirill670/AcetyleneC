# Simple.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::XML::Simple;
use base qw(XML::Simple);
use strict;

# public.

sub XMLout {
    my $self = shift;
    my $ref = shift;
    return $self->SUPER::XMLout($self->resolve($ref), @_);
}

# private.

sub resolve {
    my $self = shift;
    my $ref = shift;
    my $cache = shift || {};
    # determine reference type
    my $type = UNIVERSAL::isa($ref, 'Symbian::XML::Simple::Object')
        ? $ref->xml_object_type()
        : ref($ref);
    # if we have a list reference
    if ($type eq 'ARRAY' or $type eq 'HASH') {
        # do not re-resolve if we have already seen this ref
        (my $addr) = ($ref =~ /\((.*)\)$/);
        if (exists $cache->{$addr}) {
            return $cache->{$addr};
        }
        # de-re-ref array resolving contents
        if ($type eq 'ARRAY') {
            my $new = [];
            $cache->{$addr} = $new;
            push @$new, $self->resolve($_, $cache) for @$ref;
            return $new;
        }
        # de-re-ref hash resolving values
        if ($type eq 'HASH') {
            my $new = {};
            $cache->{$addr} = $new;
            $new->{$_} = $self->resolve($ref->{$_}, $cache) for keys %$ref;
            return $new;
        }
    }
    # otherwise return ref unmodified
    return $ref;
}

1;

=pod

=head1 NAME

Symbian::XML::Simple - Extends XML::Simple to write objects.

=head1 SYNOPSIS

 use Symbian::XML::Simple;

 my $sxs = Symbian::XML::Simple->new();

 print $sxs->XMLout($object);

=head1 DESCRIPTION

This module allows you to convert your Symbian::XML::Simple::Object-derived
objects to XML.

=head1 METHODS

=head2 XMLout($ref[, @options])

Proxies your object reference to XML::Simple::XMLout. See L<XML::Simple> for
the description of available options.

=head1 SEE ALSO

L<Symbian::XML::Simple::Object>

L<XML::Simple>

=head1 COPYRIGHT

Copyright (c) 2005 Symbian Software Ltd. All rights reserved.

=cut
