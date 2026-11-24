# Symbian/E32Variant.pm
#
# Copyright (c) 2004-2005 Symbian Software Ltd. All rights reserved.
#

package Symbian::E32Variant;
use base qw(Exporter);
use strict;

our @EXPORT = qw(Variant_GetMacroList Variant_GetMacroHRHFile);
our @predef = qw(__BIG_ENDIAN__ __CW32__ _UNICODE _FS_EXTENSION);

use Carp;
use Cwd;

sub Variant_GetMacroHRHFile {
    my $file = $ENV{EPOCROOT}.'epoc32\tools\variant\variant.cfg';
    open(CONF, $file) or croak "ERROR: Can't open $file: $!\n";
    while (<CONF>) {
        # strip comments
        s/(?<!\\)#.*$//;
        # trim leading and trailing whitespace
        s/^\s+|\s+$//g;
        # find .hrh file line
        next if !/.hrh$/i;
        # return full path with EPOCROOT prepended
        close(CONF);
        return $ENV{EPOCROOT}.$_;
    }
    croak "ERROR: .hrh file location not found in $file\n";
}

sub Variant_GetMacroList {
    my $driveletter = substr(cwd(), 0, 1);
    my $file = $driveletter.':'.Variant_GetMacroHRHFile();
    # prepare cpp command
    my $cmd = "cpp -undef -dM $file";
    open(CPPOUT, "$cmd |") or croak "ERROR: Couldn't run '$cmd': $!\n";
    # read macros
    my $macros = [ @predef ];
    while (<CPPOUT>) {
        push(@$macros, $1) if /#define\s+(.*?)\s*$/;
    }
    carp "WARNING: No macros discovered.\n" if @$macros == @predef;
    return wantarray ? @$macros : $macros;
}

1;
