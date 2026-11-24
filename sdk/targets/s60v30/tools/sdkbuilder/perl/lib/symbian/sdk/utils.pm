#!perl

package Symbian::SDK::Utils;
use strict;
use File::Basename;
use File::Spec::Functions;
use File::Path;
use Cwd;
use Cwd 'abs_path';
use Symbian::Logger::Singleton;

my $logger = Symbian::Logger::Singleton->new();

sub ValidateRoot($$$)
{
    my $rootid = shift;
    my $rootval = shift;
    my $root = shift;
    $logger->Die("Error: $rootid $rootval must not include a drive letter") if ($rootval =~ /^.:/);
    $logger->Die("Error: $rootid $rootval must not be a UNC path") if ($rootval =~ /^\\\\/);
    my $realpath = catdir($root,$rootval);
    if(!-d $realpath)
    {
        $logger->Die("Error: $rootid $realpath must specify an existing directory");
    }
}

sub GetFullPath($$)
{
    my $root = shift;
    my $path = shift || return canonpath($root);
    $path =~ s/^[\\\/]//;
    $path = canonpath($path);
    return file_name_is_absolute($path)
      ? $path
      : catfile($root,$path);
}

# hasWildCards() : internal - checks of the provided string contains wildcards - currently * ?
#
# Parameters:
#   - string
# Returns:
#   - 1 string contains wc - 0 if not
sub HasWildCards
{
    my $source = shift;
    my $return = 0;
    $return = 1 if $source =~ /[\*\?]/;
    return $return;
} # end of sub hasWildCards

sub Which {
    my $filename = shift;
    foreach (split /;/, $ENV{'PATH'}) {
        if( -f catfile($_,$filename) ) {
            return catfile($_,$filename);
        }
    }
    return undef;
}

1;
