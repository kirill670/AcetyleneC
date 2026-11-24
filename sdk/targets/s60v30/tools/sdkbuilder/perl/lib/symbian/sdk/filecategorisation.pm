# FileCategorisation.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::SDK::FileCategorisation;
use strict;

use Carp;
use File::Spec;

sub new {
    my $class = shift;
    my $list = shift; # Symbian::File::List object
    my $opts = shift; # Symbian::Config::Basic object
    # init object
    my $self = {
        api           => [],
        documentation => [],
        list          => $list,
        non_os        => [],
        options       => $opts,
        other         => [],
        source        => [],
        uisource      => [],
        user_groups   => {},
    };
    bless $self, $class;
    $self->init();
    return $self;
}

sub init {
    my $self = shift;
    # store roots now to speed up access during categorisation
    $self->{epocroot} = File::Spec->canonpath($self->{options}->Get('epoc root'));
    $self->{epocroot} =~ s/^\\?/\\/; # ensure leading slash
    $self->{epocroot} =~ s/\\$//; # Remove any trailing slash
    $self->{srcroot} = File::Spec->canonpath($self->{options}->Get('source root'));
    $self->{srcroot} =~ s/^\\?/\\/; # ensure leading slash
    $self->{srcroot} =~ s/\\$//; # Remove any trailing slash
    $self->{uisrcroot} = File::Spec->canonpath($self->{options}->Get('UI source path'));
    $self->{uisrcroot} =~ s/^\\?/\\/; # ensure leading slash
    $self->{uisrcroot} =~ s/\\$//; # Remove any trailing slash
}

sub GroupsNames {
	my $self = shift;
	my @groups = ('api','documentation','non_os','other','source', 'uisource');
	return \@groups;
}

# public.

sub CategoriseFiles {
    my $self = shift;
    my $root = File::Spec->canonpath(shift);
    # store the root - we want to ignore it during categorisation
    $self->{root} = $root;
    my $files = $self->{list}->ListFileIDs();
    # iterate through list
    for my $id (@$files) {
        # resolve path through File::List lookup
        my $path = $self->{list}->LookupFile($id);
        # categorise to a group
        my $group = $self->categorise_path($path);
        # add the file id to the group
        push @{$self->{$group}}, $id;
    }
}

sub RecategoriseFiles {
    my $self = shift;
    my $ids = shift; # List of file ids to check for
    my $categorise_from = shift; # Category to look for files in
    my $categorise_to = shift; # User category to mark categorised files as

    my @new_from;
    my @new_to;
    @new_to = @{$self->{user_groups}->{$categorise_to}} if exists $self->{user_groups}->{$categorise_to};

    if (($categorise_from eq "user_groups") || (!exists ($self->{$categorise_from}))) {
        croak "ERROR: Source group name '$categorise_from' is an invalid group name\n";
    }

    foreach my $from_id (@{$self->{$categorise_from}}) {
        if (scalar(grep($_==$from_id, @$ids)) > 0) {
             push @new_to, $from_id;
        } else {
             push @new_from, $from_id;
        }
    }

    $self->{user_groups}->{$categorise_to} = \@new_to;
    $self->{$categorise_from} = \@new_from;
}

sub GetUserGroup {
    my $self = shift;
    my $group_name = shift;

    my $files = $self->{user_groups}->{$group_name};
    return wantarray ? @$files : $files;
}
    
sub ApiGroupName {
	my $self = shift;
	return 'api';  
}

sub ApiFiles {
    my $self = shift;
    my $files = [ @{$self->{api}} ];
    return wantarray ? @$files : $files;
}

sub BuildFiles {
    my $self = shift;
    my $files = [
        @{$self->{api}},
        @{$self->{non_os}},
        @{$self->{other}},
    ];
    return wantarray ? @$files : $files;
}

sub DocumentationGroupName {
	my $self = shift;
	return 'documentation';  
}

sub DocumentationFiles {
    my $self = shift;
    my $files = [ @{$self->{documentation}} ];
    return wantarray ? @$files : $files;
}

sub NonOsGroupName {
	my $self = shift;
	return 'non_os';  
}

sub NonOsFiles {
    my $self = shift;
    my $files = [ @{$self->{non_os}} ];
    return wantarray ? @$files : $files;
}

sub OtherGroupName {
	my $self = shift;
	return 'other';  
}

sub OtherFiles {
    my $self = shift;
    my $files = [ @{$self->{other}} ];
    return wantarray ? @$files : $files;
}

sub SourceGroupName {
	my $self = shift;
	return 'source';  
}

sub SourceFiles {
    my $self = shift;
    my $files = [ @{$self->{source}} ];
    return wantarray ? @$files : $files;
}

sub UISourceGroupName {
    return 'uisource';
}

sub UISourceFiles {
    my $self = shift;
    my $files = [ @{$self->{uisource}} ];
    return wantarray ? @$files : $files;
}

# private.

sub categorise_path {
    my $self = shift;
    my $path = File::Spec->canonpath(shift);
    # validate and remove root - unnecessary for categorisation
    if ($path !~ s/^\Q$self->{root}\E//i) {
        croak "ERROR: Path '$path' root does not match '$self->{root}'\n";
    }
    # match path to one of the following rules
    if ($path =~ /^\Q$self->{uisrcroot}\E\\/i) { # ui source file
        return 'uisource';
    } elsif ($path =~ /^\Q$self->{srcroot}\E\\/i) { # source file
        return 'source';
    } elsif ($path =~ /^\\documentation\\/i) { # doc file
        return 'documentation';
    } elsif ($path =~ /^\Q$self->{epocroot}\E\\epoc32\\(?:tools|gcc\\bin)\\/i) {
        # non-os file
        return 'non_os'; # general
    } elsif ($path =~ /^\Q$self->{epocroot}\E\\epoc32\\include\\/i or
             $path =~ /\.(?:lib|pdb)$/i) { # api file
        return 'api';
    }
    return 'other'; # default
}

1;

=pod

=head1 NAME

Symbian::SDK::FileCategorisation - Finds and categorises files under a path.

=head1 SYNOPSIS

 use Symbian::ExportInfo;
 use Symbian::SDK::FileCategorisation;

 my $path = 'c:\path\to\epoc32\src';
 my $list = Symbian::File::List->new($path);
 my $conf = 'c:\path\to\config.ini';
 my $opts = Symbian::Config::Basic->new($conf);
 my $fcat = Symbian::SDK::FileCategorisation->new($list, $opts);

 $fcat->CategoriseFiles($path);

 # then get the categorised lists of files, e.g.

 my $docs = $fcat->DocumentationFiles();
 foreach (@$docs) {
     # ...
 }

 # see METHODS for full list of file lists available

=head1 DESCRIPTION

This module scans an environment and categorises the files found within. Methods
are provided to query the object and return lists of files for each category.

Categories are determined according to the following group filters:

=begin text

    +------------------+-----------------------------------------+
    | Group Name       | Filter Rule                             |
    +------------------+-----------------------------------------+
    | Source           | /src/* (or whatever the source root is) |
    | Documentation    | /documentation/*                        |
    | Non-OS Files     | /epoc32/tools/* and /epoc32/gcc/bin/*   |
    | API Files        | /epoc32/include/* and *.lib and *.pdb   |
    | Other            | everything else                         |
    +------------------+-----------------------------------------+

=end text

The above groups are processed in order and files captured by a previous rule
are not available for categorisation into further groups, e.g. /src/foo.lib is
categorised into Source (because it lives under /src/) and will not be "stolen"
by API Files (even though it has a .lib extension).

=head1 METHODS

=head2 new($list, $opts)

Creates the Symbian::SDK::FileCategorisation object. Expects a populated
Symbian::File::List object and a validated Symbian::Config::Basic object as
arguments.

=head2 CategoriseFiles($root_path)

Initiates the directory scan, searching for files recursively under $root_path.

=head2 ApiFiles()

Returns a list of file paths for: API files.

=head2 BuildFiles()

Returns a list of file paths for: API files, Non-OS files and Others.

=head2 DocumentationFiles()

Returns a list of file paths for: Documentation files.

=head2 NonOsFiles()

Returns a list of file paths for: Non-OS files.

=head2 OtherFiles()

Returns a list of file paths for: Other files.

=head2 SourceFiles()

Returns a list of file paths for: Source files.

=head1 SEE ALSO

L<Symbian::ExportInfo>

=head1 COPYRIGHT

Copyright (c) 2005 Symbian Software Ltd. All rights reserved.

=cut
