# Group.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::SDK::ContentDefinitionFile::Group;
use base qw(Symbian::XML::Simple::Object);
use strict;

use Symbian::SDK::ContentDefinitionFile::File;

sub new {
    my $class = shift;
    my $name = shift;
    my $self = {
        name        => $name,
        order       => 0,
        '-default'  => 0,
        '-hidden'   => 0,
        '-required' => 0,
        files       => { file => [] },
        metadata    => {},
    };
    bless $self, $class;
    return $self;
}

# public.

sub AddFile {
    my $self = shift;
    my $file = shift;
    my $dest = shift;
    if (!UNIVERSAL::isa($file, 'Symbian::SDK::ContentDefinitionFile::File')) {
        $file = Symbian::SDK::ContentDefinitionFile::File->new($file, $dest);
    }
    push @{$self->{files}{file}}, $file;
    return $file;
}

sub AddMetadata {
    my $self = shift;
    my $element = shift;
    my %attr = @_;
    push @{$self->{metadata}{$element}}, \%attr;
}

sub SetDefault {
    my $self = shift;
    my $flag = shift;
    $self->set_bool_attr('default', $flag);
}

sub SetDescription {
    my $self = shift;
    my $desc = shift;
    if (!defined $desc or !length $desc) {
        delete $self->{description};
        return;
    }
    $self->{description} = $desc;
}

sub SetHidden {
    my $self = shift;
    my $flag = shift;
    $self->set_bool_attr('hidden', $flag);
}

sub SetOrder {
    my $self = shift;
    my $pos = shift;
    $self->{order} = int($pos);
}

sub SetRequired {
    my $self = shift;
    my $flag = shift;
    $self->set_bool_attr('required', $flag);
}

# private

sub set_bool_attr {
    my $self = shift;
    my $attr = shift;
    # double inversion reduces to boolean
    my $flag = !!shift;
    # remove rather than set to default
    if ($flag == $self->{"-$attr"}) {
        delete $self->{$attr};
        return;
    }
    # otherwise, set boolean string value
    $self->{$attr} = $flag ? 'true' : 'false';
}

1;

=pod

=head1 NAME

Symbian::SDK::ContentDefinitionFile::Group - SDK content definition file <group/>.

=head1 SYNOPSIS

# see L<Symbian::SDK::ContentDefinitionFile>

=head1 DESCRIPTION

This class implements methods for SDK content definition file <group/> elements.

=head1 METHODS

=head2 new($name)

Creates the Symbian::SDK::CDF::Group object. This can be done via the
Symbian::SDK::CDF AddGroup method, too. Specify the name of the group at
creation.

=head2 AddFile($file|$path[, $destination])

Accepts either a Symbian::SDK::CDF::File object or the source (optionally inc.
destination) of a file to create. Adds the file to the list of <files/> and
returns it.

=head2 AddMetadata($element[, %attr_value_pairs])

Adds a $element element to the group's <metadata/> section with the supplied
(arbitrary) attribute-value pairs.

=head2 SetDefault($bool)

Sets the @description attribute to 'true' or 'false' in accordance with the
boolean value of $bool. If this is the default value it will not be shown in
the XML output.

=head2 SetDescription($text)

Sets the description of the group to whatever is in $text. If this is empty or
undefined the description attribute will not be shown in the XML output.

=head2 SetHidden($bool)

Sets the @hidden attribute to 'true' or 'false' in accordance with the
boolean value of $bool. If this is the default value it will not be shown in
the XML output.

=head2 SetRequired($bool)

Sets the @required attribute to 'true' or 'false' in accordance with the
boolean value of $bool. If this is the default value it will not be shown in
the XML output.

=head1 SEE ALSO

L<Symbian::SDK::ContentDefinitionFile>

L<Symbian::SDK::ContentDefinitionFile::File>

=head1 COPYRIGHT

Copyright (c) 2005 Symbian Software Ltd. All rights reserved.

=cut
