# ContentDefinitionFile.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::SDK::ContentDefinitionFile;
use base qw(Symbian::XML::Simple::Object);
use strict;

use Symbian::SDK::ContentDefinitionFile::Group;
use Symbian::XML::Simple;

sub new {
    my $class = shift;
    my $self = {
        group => [],
    };
    bless $self, $class;
    return $self;
}

# public.

sub AddGroup {
    my $self = shift;
    my $group = shift;
    if (!UNIVERSAL::isa($group, 'Symbian::SDK::ContentDefinitionFile::Group')) {
        $group = Symbian::SDK::ContentDefinitionFile::Group->new($group);
        $group->SetOrder(scalar @{$self->{group}}); # assign next order position
    }
    push @{$self->{group}}, $group;
    return $group;
}

sub XML {
    my $self = shift;
    my $dumper = Symbian::XML::Simple->new(
        keyattr  => [],
        rootname => 'groups',
        xmldecl  => '<?xml version="1.0"?>',
        @_
    );
    return $dumper->XMLout($self);
}

1;

=pod

=head1 NAME

Symbian::SDK::ContentDefinitionFile - SDK content definition file class.

=head1 SYNOPSIS

 use Symbian::SDK::ContentDefinitionFile;

 my $cdf = Symbian::SDK::ContentDefinitionFile->new();

 my $group = $cdf->AddGroup('foo');

 $group->AddFile('c:\foo.txt');

 print $cdf->XML();

=head1 DESCRIPTION

This class allows you to create a SDK Content Definition File by building up an
OO representation of the file with it's group and file components and then
converting that information to XML format.

=head1 METHODS

=head2 new()

Creates the Symbian::SDK::CDF object.

=head2 AddGroup($group|$name)

Accepts either a Symbian::SDK::CDF::Group object or the name of a group to
create. Adds the group to the list of <groups/> and returns it, i.e. for you to
add <file/>s to.

=head2 XML([@options])

Returns the XML for the file. Optionally can take XML::Simple options (e.g. to
write directly to a file).

=head1 SEE ALSO

L<Symbian::SDK::ContentDefinitionFile::Group>

L<Symbian::SDK::ContentDefinitionFile::File>

L<XML::Simple>

=head1 COPYRIGHT

Copyright (c) 2005 Symbian Software Ltd. All rights reserved.

=cut
