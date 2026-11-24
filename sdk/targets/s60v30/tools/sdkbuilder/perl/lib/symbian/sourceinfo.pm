# SourceInfo.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::SourceInfo;
use strict;

use Carp;
use Cwd;
use Symbian::E32Variant;
use File::Basename;

sub new {
    my $class = shift;
    my $self = { macros => '' };
    bless $self, $class;
    $self->init(@_);
    return $self;
}

sub init {
    my $self = shift;
    my $macros = shift;
    # get predefined macros from .hrh
    my @macros = Symbian::E32Variant::Variant_GetMacroList();
    # add on user macros
    push @macros, @$macros if ref($macros);
    # make -DFOO -DBAR string for cpp
    $self->{macros} = join(' ', map('-D'.$_, @macros));
}

# public.

sub GetIncludes {
    my $self = shift;
    my $file = shift;
    my @include = ();
    # change dir to $file dir
    my $old = cwd();
    my $dir = dirname($file);
    chdir($dir) or croak "ERROR: Couldn't chdir to '$dir': $!\n";
    # prepare and run cpp command
    my $cmd = "cpp -w -undef $self->{macros} -I. $file";
    open(CPPOUT, "$cmd |") or croak "ERROR: Couldn't run '$cmd': $!\n";
    # read cpp output
    while (<CPPOUT>) {
        push(@include, $1) if /^# 1 "(.*)" 1$/;
    }
    # close and chdir back
    close(CPPOUT);
    chdir($old) or croak "ERROR: Couldn't chdir back to '$old': $!\n";
    # tidy up paths
    s/\\+/\//g for @include;
    return wantarray ? @include : \@include;
}

1;

=pod

=head1 NAME

Symbian::SourceInfo - examine source files for useful information.

=head1 SYNOPSIS

 use Symbian::SourceInfo;

 my $info = Symbian::SourceInfo->new([\@macros]);

 my @includes = $info->GetIncludes('/path/to/some/source.h');

=head1 DESCRIPTION

Use this module to examine source files for specific information.

=head1 METHODS

=head2 new([\@macros])

Creates the Symbian::SourceInfo object with an optional list of macros.

=head2 GetIncludes($file)

Returns a list (or listref, depending on the calling context) of paths to
files #include-d by $file. Respects macros available to E32Variant.

=head1 SEE ALSO

L<E32Variant>

=head1 COPYRIGHT

Copyright (c) 2005 Symbian Software Ltd. All rights reserved.

=cut
