# File.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::SDK::ContentDefinitionFile::File;
use base qw(Symbian::XML::Simple::Object);
use strict;

sub new {
    my $class = shift;
    my $src = shift;
    my $dest = shift;
    my $self = {
          source     => $src,
          exclude    => [],
        '-recursive' => 0,
    };
    bless $self, $class;
    $self->SetDestination($dest);
    return $self;
}

# public.

sub AddExclude {
    my $self = shift;
    my $path = shift;
    push @{$self->{exclude}}, { path => $path };
}

sub SetDestination {
    my $self = shift;
    my $dest = shift;
    if (!defined $dest or !length $dest) {
        delete $self->{destination};
        return;
    }
    $self->{destination} = $dest;
}

sub SetRecursive {
    my $self = shift;
    my $flag = shift;
    $self->set_bool_attr('recursive', $flag);
}

# private.

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

Symbian::SDK::ContentDefinitionFile::File - SDK content definition file <file/>.

=head1 SYNOPSIS

# see L<Symbian::SDK::ContentDefinitionFile>

=head1 DESCRIPTION

This class implements methods for SDK content definition file <file/> elements.

=head1 METHODS

=head2 new($source[, $destination])

Creates the Symbian::SDK::CDF::File object. This can be done via the
Symbian::SDK::CDF::Group AddFile method, too. Specify the source path of the
file at creation (optionally also the destination too).

=head2 SetDestination($path)

Sets the destination path of the file to whatever is in $path. If this is empty
or undefined the destination attribute will not be shown in the XML output.

=head2 SetRecursive($bool)

Sets the @recursive attribute to 'true' or 'false' in accordance with the
boolean value of $bool. If this is the default value it will not be shown in
the XML output.

=head1 SEE ALSO

L<Symbian::SDK::ContentDefinitionFile>

L<Symbian::SDK::ContentDefinitionFile::File>

=head1 COPYRIGHT

Copyright (c) 2005 Symbian Software Ltd. All rights reserved.

=cut
