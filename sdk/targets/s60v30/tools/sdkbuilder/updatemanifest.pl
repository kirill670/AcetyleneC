#!/usr/bin/perl
use strict;
use File::Basename;
use File::Spec::Functions;

my($file) = shift;
die "Error: $file does not exist" if ( ! defined $file || ! -e $file );
my $rootpath = canonpath(shift);
my $output = dirname($file). "\\tmp" . basename($file);

my $file_dir = lc(canonpath(dirname($file)));
$file_dir =~ s/\Q$rootpath\E//i;
$file_dir =~ s/\//\\/g;
my $root;
foreach my $chunk (split /\\/,$file_dir)
{
    $root .= "..\\" if $chunk;
}

$root = ".\\" if !$root;

open (FILE, "<", $file) || die "Can't open $file for reading";
open (FILE1, ">", $output) || die "Can't create tmp file $output for writing";

my $list = {};
while ($_ = <FILE>)
{
    if ($_ =~ /^\s*<\s*group\s*>/)
    {
        s/^\s*<\s*group\s*>\s*(.+)\s*[\\<]/$1/;
        $list->{$1} = undef;
    }
}
close FILE;
open (FILE, "<", $file);

while ( $_ = <FILE>)
{
    if ($_ !~ /^\s*<\s*group\s*>/ && $_ !~ /^\s*<\s*contentDefinition.*>/)
    {
        $_ =~ s/^(\s*<\s*paths\s+root\s*=\s*").*("\s*>\s*)$/$1$root$2/; # hard code root to "."
        print FILE1 $_;
        if ($_ =~ /<installed>/)
        {

            # write the list of installed components
            foreach my $arg (@ARGV)
            {
                if(exists $list->{$arg})
                {
                    print FILE1 " <group>". $arg . "<\/group>\n";
                }
            }
        }
    }
}

close FILE;
close FILE1;

#rename $file, $file."_saved";
rename $output, $file;

__END__
