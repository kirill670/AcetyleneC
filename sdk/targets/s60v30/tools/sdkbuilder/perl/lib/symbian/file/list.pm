# Symbian/File/List.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::File::List;
use strict;

use Carp;
use File::Basename;
use File::Find;
use File::Spec;

sub new {
    my $class = shift;
    my $path = shift;
    my $self = {
        dirs     => {},
        dir_rev  => [],
        files    => {},
        file_rev => [],
    };
    bless $self, $class;
    $self->Populate($path) if defined $path;
    return $self;
}

# public.

sub AddDirectory {
    my $self = shift;
    my $path = shift;
    # clean-up path
    $path = $self->normalise_path($path);
    # add to internal list if not already present
    if (!defined $self->{dirs}{$path}) {
        push @{$self->{dir_rev}}, $path;
        $self->{dirs}{lc($path)} = $#{$self->{dir_rev}};
    }
    return $self->{dirs}{lc($path)};
}

sub AddFile {
    my $self = shift;
    my $path = shift;
    # clean-up path
    $path = $self->normalise_path($path);
    # get directory id
    my $dir = dirname($path);
    my $id = $self->GetDirectoryID($dir);
    $id = $self->AddDirectory($dir) if !defined $id;
    # modify path to include directory id rather than full path
    $path = "$id/".basename($path);
    # add to internal list if not already present
    if (!defined $self->{files}{$path}) {
        push @{$self->{file_rev}}, $path;
        $self->{files}{lc($path)} = $#{$self->{file_rev}};
    }
    return $self->{files}{lc($path)};
}

sub FileUnderPath {
    my $self = shift;
    my $id = shift;
    my $path = shift;
    $path = $self->normalise_path($path);
    my $file = $self->LookupFile($id);
    return $file =~ /^\Q$path\E/i; # win32 case insensitive match
}

sub FindFiles {
    my $self = shift;
    my $pattern = shift;
    my $matches = [];
    # iterate through files
    for my $path (@{$self->{file_rev}}) {
        # remove directory id before comparison
        (my $file = $path) =~ s!^\d+/!!;
        # match file or skip
        next if $file !~ $pattern;
        # add to result list
        push @$matches, $self->{files}{lc($path)};
    }
    return wantarray ? @$matches : $matches;
}

sub GetDirectoryID {
    my $self = shift;
    my $path = shift;
    # clean-up path
    $path = $self->normalise_path($path);
    # lookup clean path
    return $self->{dirs}{lc($path)};
}

sub GetFileID {
    my $self = shift;
    my $path = shift;
    # clean-up path
    $path = $self->normalise_path($path);
    # get directory id
    my $dir = dirname($path);
    my $id = $self->GetDirectoryID($dir);
    # modify path to include directory id rather than full path
    $path = "$id/".basename($path);
    return $self->{files}{lc($path)};
}

sub ListDirectoryIDs {
    my $self = shift;
    my $ids = [ values %{$self->{dirs}} ];
    return wantarray ? @$ids : $ids;
}

sub ListFileIDs {
    my $self = shift;
    my $ids = [ values %{$self->{files}} ];
    return wantarray ? @$ids : $ids;
}

sub LookupDirectory {
    my $self = shift;
    my $id = shift;
    return if !defined $id;
    return if $id !~ /^(\d+)/;
    return $self->{dir_rev}[$1];
}

sub LookupFile {
    my $self = shift;
    my $id = shift;
    return if !defined $id;
    my $file = $self->{file_rev}[$id];
    return if !defined $file;
    my $dir = $self->LookupDirectory($file);
    return if !defined $dir;
    $file =~ s/^\d+/$dir/;
    return $file;
}

sub Populate {
    my $self = shift;
    my $path = shift;
    croak "ERROR: Path does not exist: '$path'\n" if !-d $path;
    find(sub { $self->AddFile($File::Find::name) }, $path);
}

# private.

sub normalise_path {
    my $self = shift;
    my $path = File::Spec->canonpath(shift);
    # replace foo\bar\..\baz with foo\baz
    1 while $path =~ s![^\\]+\\\.\.(\\|$)!!;
    return $path;
}

# The pattern passed through to FindFiles should normally be case insentive since you normally don't care about file case in win32

1;
