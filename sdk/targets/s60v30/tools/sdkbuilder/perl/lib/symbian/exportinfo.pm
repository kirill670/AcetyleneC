# ExportInfo.pm
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::ExportInfo;
use strict;

use Archive::Zip qw(:ERROR_CODES);
use Carp;
use File::Basename;
use Symbian::DistributionPolicy::Reader;
use Symbian::E32Variant;

sub new {
    my $class = shift;
    my $flist = shift; # Symbian::File::List object
    my $thing = shift; # string or arrayref - see Run() for usage
    my $self = bless {
        exports => {},
        flist   => $flist,
        infs    => [],
        policy  => Symbian::DistributionPolicy::Reader->new(),
    }, $class;
    $self->Run($thing);
    return $self;
}

# init object. either internalise list of infs provided or search specified
# directory using find_infs method. then process infs using cpp_infs method.
#
sub Run {
    my $self = shift;
    my $thing = shift;
    # check for lazy object instantiation - users may call Run() themselves
    return unless defined $thing;
    if (ref $thing) {
        # it's a list of paths to the bld.inf file(s)
        $self->{infs} = [ map $self->normalise_path($_), @$thing ];
    } else {
        # it's a directory to search for bld.inf files
        $self->find_infs($thing);
    }
    $self->cpp_infs();
}

# public. return the export paths relative to %EPOCROOT%.
#
sub GetExports {
    my $self = shift;
    my $exports = [ keys %{$self->{exports}} ];
    return wantarray ? @$exports : $exports;
}

# public. return the ipr category of a specified export.
#
sub GetIPR {
    my $self = shift;
    my $export = shift;
    $export = $self->normalise_path($export);
    $export =~ s/^[A-Z]://i; # Remove drive letter
    return $self->{exports}{$export}{policy}->Category();
}

# public. return the bld.inf that mentioned the specified export.
#
sub GetInf {
    my $self = shift;
    my $export = shift;
    $export = $self->normalise_path($export);
    $export =~ s/^[A-Z]://i; # Remove drive letter
    return ${$self->{exports}{$export}{inf}};
}

# public. return the source path of a specified export.
#
sub GetSourcePath {
    my $self = shift;
    my $export = shift;
    $export = $self->normalise_path($export);
    $export =~ s/^[A-Z]://i; # Remove drive letter
    my $id = $self->{exports}{$export}{src};
    return $self->{flist}->LookupFile($id);
}

# public. return boolean to show whether the source is export restricted.
#
sub IsExportRestricted {
    my $self = shift;
    my $export = shift;
    $export = $self->normalise_path($export);
    $export =~ s/^[A-Z]://i; # Remove drive letter
    return $self->{exports}{$export}{policy}->ExportRestricted();
}

# public. return boolean to show whether the source path is referenced.
#
sub SourceExists {
    my $self = shift;
    my $path = shift;
    # resolve path to ID
    my $id = $self->{flist}->GetFileID($path);
    return unless defined $id;
    # iterate through exports
    for my $export (keys %{$self->{exports}}) {
        # return true to indicate found
        return 1 if $self->{exports}{$export}{src} == $id;
    }
    return; # not found
}

# private. search a directory and its subdirectories for bld.inf files.
#
sub find_infs {
    my $self = shift;
    my $searchdir = shift;
    # make search pattern
    my $pattern = qr/^bld\.inf$/i;
    my @infs = $self->{flist}->FindFiles($pattern);
    # iterate through comparing subdirs
    for my $id (@infs) {
        # skip if it's not under $searchdir
        next if !$self->{flist}->FileUnderPath($id, $searchdir);
        # add to list
        push @{$self->{infs}}, $self->{flist}->LookupFile($id);
    }
}

# private. tidy up a dirty path - remove double directory separators, make
# all separators backslashes in case there's a mix. substitute-out single,
# and resolve double dot directories in path. convert to lower case.
#
sub normalise_path {
    my $self = shift;
    my $path = shift;
    # replace (double?) (back?)slash with \
    $path =~ s![\\/]+!\\!g;
    # replace foo\.\bar with foo\bar
    $path =~ s!\\\.\\!\\!g;
    # replace \foo\bar\..\baz with \foo\baz
    1 while $path =~ s![^\\]+\\\.\.\\!!;
    # convert to lower case - win32 doesn't care
    return lc($path);
}

# private. resolve potentially empty destination path into a full path for
# query by the user. add on the filename (from source) if only a directory
# is specified. handle special emulator drives and epoc32 shortcut +, then
# prepend \epoc32\include to relative paths. lastly call normalise().
#
sub resolve_dest {
    my $self = shift;
    my $src = shift;
    my $dest = shift;
    # make all path separators backslashes
    $dest =~ s![\\/]+!\\!g;
    # append filename if dest is empty or a directory
    $dest =~ s!^(.*\\)?$!$1.basename($src)!e;
    # do special substitution on drive leters
    $dest =~ s!^([a-z]):\\!\\epoc32\\data\\$1\\!i;
    # do special substitution on +/ (or +\)
    $dest =~ s!^\+[\\/]!\\epoc32\\!;
    # prepend \epoc32\include to a relative path
    $dest =~ s|^(?!\\)|\\epoc32\\include\\|;
    # prepend EPOCROOT
    $dest = $ENV{EPOCROOT}."\\$dest";
    # finally, normalise path to remove possible ..s
    return $self->normalise_path($dest);
}

# private. add an export to the internal store of the object resolving its
# destination and determining its policy automatically.
#
sub add_export {
    my $self = shift;
    my $src = shift;
    my $dest = shift;
    my $index = shift;
    # determine export destination path
    $dest = $self->resolve_dest($src, $dest);
    # get source file id from file list
    my $srcid = $self->{flist}->GetFileID($src);
    # compile export indexed by destination
    $self->{exports}{$dest} = {
        inf    => \$self->{infs}[$index],
        policy => $self->{policy}->ReadPolicyFile($src),
        src    => $srcid,
    };
}

# private. read an archive and add its (file) members as exports.
#
sub process_archive {
    my $self = shift;
    my $src = shift;
    my $dest = shift;
    my $index = shift;
    # destination defaults to root
    $dest = '\\' if (!defined $dest or !length $dest);
    # open archive
    my $zip = Archive::Zip->new();
    my $status = $zip->read($src);
    croak "ERROR: Couldn't read archive '$src' ($status)\n" if $status != AZ_OK;
    # read file member names (ignore dirs)
    for my $member (grep !$_->isDirectory(), $zip->members()) {
        # prepend destination (any double \\ will be cleaned up later)
        my $file = $dest.'\\'.$member->fileName();
        $self->add_export($src, $file, $index);
    }
}

# private. run infs through cpp: a c pre-processor to expand the includes.
# derive a list of source and destination paths and store with associated
# policy data. if we see the magic :zip hand over to process_archive.
#
sub cpp_infs {
    my $self = shift;
    my $macros = join(' ', map('-D'.$_, Variant_GetMacroList()));
    my $index = 0;
    for my $inf (@{$self->{infs}}) {
        if (!-e $inf) {
            carp "WARNING: File does not exist: $inf\n";
            next;
        }
        my $dir = dirname($inf);
        # prepare command line to preprocess bld.inf
        my $cmd = "cpp -undef $macros $inf";
        open(CPPOUT, "$cmd |") or croak "ERROR: Couldn't run '$cmd': $!\n";
        my $ignore = 1;
        while (defined(my $line = <CPPOUT>)) {
            # look for includes and change base dir accordingly
            if ($line =~ /^# \d+ "(.*)"/) {
                $dir = dirname($1);
                next;
            }
            # look for a PRJ_foo line and toggle ignore flag
            if ($line =~ /^\s*PRJ_(\w+)/i) {
                $ignore = uc($1) ne 'EXPORTS';
                next;
            }
            next if $ignore or $line =~ /^\s*$/;
            # check for special :zip keyword by attempting to trim it off
            my $zipmagic = ($line =~ s/^\s*:zip\s*//i);
            # get source-destination paths (may be quoted)
            my($src, $dest) = grep defined, $line =~ /"(.*?)"|(\S+)/g;
            # make full path for src
            $src = $self->normalise_path("$dir\\$src");
            # apply magic to zipfiles where requested
            if ($zipmagic) {
                $self->process_archive($src, $dest, $index);
            } else {
                $self->add_export($src, $dest, $index);
            }
        }
        close(CPPOUT);
        ++$index;
    }
}

1;

=pod

=head1 NAME

Symbian::ExportInfo - Parses bld.inf files for exports and retrieves IPR info.

=head1 SYNOPSIS

 use Symbian::ExportInfo;
 use Symbian::File::List;

 # prepare a file list object for use by exportinfo
 my $flist = Symbian::File::List->new($ENV{EPOCROOT});

 # to search for and process bld.inf files
 my $exinf = Symbian::ExportInfo->new($flist, $ENV{EPOCROOT}.'/src');

 # OR, to process specific bld.inf file(s)
 my @infs = map $ENV{EPOCROOT}.$_, qw(
     /src/generic/component_a/group/bld.inf
     /src/generic/component_b/group/bld.inf
     /src/generic/component_c/group/bld.inf);
 my $exinf = Symbian::ExportInfo->new($flist, \@infs);

 # OR, to do the above in a lazy manner
 my $exinf = Symbian::ExportInfo->new($flist);
 print "Startup OK. Proceed with time consuming process [ENTER]?"; <STDIN>;
 $exinf->Run($path_or_listref_as_above);

 # to query the object
 for my $export ($exinf->GetExports()) {
     print "Export: $export\n";
     printf "From INF: %s\n", $exinf->GetInf($export);
     printf "Source: %s\n", $exinf->GetSourcePath($export);
     printf "IPR Category: %s\n", $exinf->GetIPR($export);
     printf "Export Restricted: %s\n",
        ($exinf->IsExportRestricted($export) ? 'YES' : 'NO');
 }

=head1 DESCRIPTION

This module will optionally locate, and parse bld.inf files to determine the
source and destination paths of mentioned exports and will also discover the
associated distribution policy information. Methods are provided (see below)
to query the object for this info.

=head1 METHODS

=head2 new($flist)

Creates the object but does not do any further processing until Run is called.
See the Run() method below. Expects a populated Symbian::File::List object.

=head2 new($flist, 'c:\path\to\epoc32\src')

Creates the object with a path to search for bld.inf files. Immediately goes
and locates those files and processes them. Expects a populated
Symbian::File::List object as the first argument.

=head2 new($flist, \@infs)

Creates the object with a list of full paths to bld.inf files. Immediately
processes the files. Expects a populated Symbian::File::List object as the first
argument.

=head2 Run($path_or_listref_as_above)

Takes the same arguments as the immediate-processing constructor and does the
processing not done at instantiation.

=head2 GetExports()

Return a list or listref depending on the calling context - i.e. if you are
expecting a large list then you may prefer to assign to a $variable and use
@$variable rather than using this method directly in a foreach loop. The list
contains the exports discovered in the parsed bld.inf files. These are the
destination paths of the export files relative to %EPOCROOT%.

N.B. Directory separators are \ and all exports begin with a \.

=head2 GetInf('\epoc32\include\some.dll')

Returns the path to the bld.inf that mentioned the specified export.

=head2 GetIPR('\epoc32\include\some.dll')

Returns the IPR category of the specified export.

=head2 GetSourcePath('\epoc32\include\some.dll')

Returns the path to the source of a specified export.

=head2 IsExportRestricted('\epoc32\include\some.dll')

Returns a boolean to show whether the source is export restricted.

=head2 SourceExists('c:\path\to\epoc32\src\component\example.h')

Returns a boolean to show whether the source path is referenced.

=head1 COPYRIGHT

Copyright (c) 2005 Symbian Software Ltd. All rights reserved.

=cut
