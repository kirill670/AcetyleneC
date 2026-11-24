#!perl
#
#   filtertool.pl
#
#   Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#
use strict;
use warnings;

$|++;

use Getopt::Long;
use Pod::Usage;

use FindBin;
use lib $FindBin::Bin."\\perl\\lib\\";
use Symbian::Config::Basic;
use Symbian::Logger::Singleton;
use Symbian::SDK::FilterTool;

# command line option container
my $options = { config => '', dummy => 0 };

{
    # trap warnings from GetOptions
    local $SIG{__WARN__} = sub { $@ = shift };

    # parse options or die with usage information
    GetOptions($options, qw(config=s dummy help|?)) or pod2usage("ERROR: $@");
}

# respond to help requests
pod2usage(1) if $options->{help};

# ensure a configuration file path was provided
pod2usage("ERROR: Configuration file must be specified. -h for help.\n") if !length($options->{config});

# ensure configuration file specified exists
pod2usage("ERROR: No such file: $options->{config}.\n") if !-f $options->{config};

# create logger and config objects
my $logger = new Symbian::Logger::Singleton();
my $config = new Symbian::Config::Basic(undef, $options->{config});

# create the filter tool
my $tool = Symbian::SDK::FilterTool->new($config);

# set dummy on/off
$config->Set('dummy run', $options->{dummy});

# check we aren't running from inside the work area
my $tools= $FindBin::Bin;
my $value = $config->GetSafe("input area");
$tools =~ s/[\/\\]+/\//g; # Normalise slashes
$value =~ s/[\/\\]+/\//g;

if ($tools =~ /^\Q$value\E/i) {
    $logger->Error("Tools must not be run from inside the work area");
}

# run the tool
$tool->Run();

__END__

=head1 NAME

filtertool.pl - Filter a CBR environment to produce an SDK.

=head1 DESCRIPTION

The Filter Tool will remove files from a CBR environment (which it can
optionally install for you) in order to leave a directory tree suitable for
production of an SDK.

=head1 SYNOPSIS

perl filtertool.pl [ -h ] [ -d ] -c CONFIGFILE

=head1 OPTIONS

=over 8

=item B<--help|-h|-?>

Display this usage message.

=item B<-config|-c CONFIGFILE>

Run Filter Tool with this configuration file. Required.

=item B<-dummy|-d>

Run in dummy run mode. Does not create an SDK. Logs additional information while running.

=back

=cut
