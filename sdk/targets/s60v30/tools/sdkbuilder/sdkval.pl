#!perl -w
#
# S d k V a l
#
# Copyright (c) 2001-2005 Symbian Software Ltd. All rights reserved.
#
# A simple wrapper to create and run an SDK Validator test handler object
# passing in values such as the manifest file location, where results should
# be stored and so forth.
#
use strict;
use FindBin;
use lib $FindBin::Bin."\\perl\\lib\\";
use Getopt::Long;
use Pod::Usage;

use POSIX qw(strftime);
use File::Path;
use File::Basename;
use Symbian::SDK::Validate::Utility::TestHandler;

#
# Get the options.
#
my($vb, $tdf, $outputdir, $manifest, $dummyrun, $tdfhome, $help);
my $gorc = GetOptions(
             'DummyRun=s' => \$dummyrun,
                     'h+' => \$help, 
            'OutputDir=s' => \$outputdir,
             'manifest=s' => \$manifest,
                  'tdf=s' => \$tdf,
              'tdfhome=s' => \$tdfhome,
                     'v+' => \$vb,
                     );

# If we failed to get options or help was wanted, just run Usage which will
# exit.
pod2usage(1) unless($gorc);
pod2usage(1) if($help);

# Default verbose flag to zero if they weren't set.
$vb = 0       unless(defined($vb));

# Use backslashes in the manifest location, forward in the output directory.
$manifest =~ s/\//\\/g if(defined($manifest));
$outputdir =~ s/\\/\//g if(defined($outputdir));

# Just don't bother unless prerequisites are present.
pod2usage("Test definition file (tdf) not specified.")    unless($tdf);
pod2usage("SDK Manifest File not specified.\n")           unless($manifest);
pod2usage("Manifest file '$manifest' does not exist.\n")  unless(-f $manifest);
pod2usage("Output directory (OutputDir) not specified.\n") unless($outputdir);

# Create a unique output directory for this test.
my $ts = POSIX::strftime "%Y-%m-%d-%H-%M-%S", localtime;
my $opdir = "$outputdir/$ts";
mkpath($opdir) or die "Couldn't create output directory '$opdir'\n";

# Create out test handler object.
my $test = Symbian::SDK::Validate::Utility::TestHandler->new($tdf, $tdfhome, $opdir, $vb);
die "Failed to create TestHandler object. See the log in $opdir\\$tdf.\n" unless($test);

# Get the settings from the 'runner' object. 
my $runner = $test->Funcobj;
die "No runner object associated with TestHandler." unless($runner);
my $rset = $runner->Settings;
die "No settings associated with runner object." unless($rset);
# Pass this setting object to our 'ManifestSettings' subroutine which will
# create various settings from items defined in the manifest file. These
# will be used later by the runner object to find, for example, where
# 'EPOCROOT' is within the SDK under test.
die "Failed to read manifest file settings." 
                                 unless(ManifestSettings($manifest, $rset ) );
# Add a setting so tests know where output should be placed.
$rset->GetSet("TestOutputDirectory", $opdir);

# Check the status of the test. Only this one test will have been loaded,
# if this is a batch of tests the other tests won't get parsed until we
# at least do a dummy run.
my $testout = $test->TestOut;
unless($testout->IsStatusGood)
{
    print STDERR "Errors found parsing test '$tdf'. Continue?";
    my $ip = <STDIN>;
    exit 1 unless( $ip =~ m/^y/i );
}

# Run the test passing in the dummy run flag.
$test->ExecuteTest($dummyrun);

# Did it fail? If so list the tests that failed. Note that this includes not
# only tests that failed but any batches that triggered them.
my $ok = $testout->IsStatusGood();
unless($ok)
{
    my $fo = $test->Funcobj if(ref($test));
    my $se = $fo->Settings if(ref($fo));
    my $fs = $se->GetSet("failurestack") if(ref($se));
    $fs = [] unless(ref($fs));
    for my $fail (@$fs)
    {
        $testout->Report("Failure detected in test '$fail'");
    }
    print STDERR "\nOverall Failure. Check results in " . $testout->OutputFile . "\n" unless($testout->Verbose);
    exit 1;
}

# Exit. Zero status for ok.
print "\nOverall Pass. Check results in " . $testout->OutputFile . "\n"
        unless($testout->Verbose);
exit 0;

#
# M a n i f e s t S e t t i n g s
#
# Create a number of settings within the runner objects' Settings object
# which correspond to various settings within the manifest file. These
# settings will then be available for tests to access later.
#
sub ManifestSettings
{
    use Symbian::SDK::SdkDef;
    my($manifest, $settings) = @_;
    return 0 unless(ref($settings));

    my $sdkdef = Symbian::SDK::SdkDef->New($manifest);

    # First get the values for things which may end up as environment
    # variable settings.. Those with an 'a' have full paths (drive letters
    # included), those without do not.
    my $epr = $sdkdef->SDKEnvRoot("epocroot", 0);
    $epr .= '\\' unless( $epr =~ m/\\$/ );
    $settings->GetSet( "EPOCROOT", $epr );
    $settings->GetSet( "EPOCROOT:", $sdkdef->SDKEnvRoot("epocroot", 1) );
    $settings->GetSet( "SRCROOT", $sdkdef->SDKEnvRoot("srcroot", 0) );
    $settings->GetSet( "SRCROOT:", $sdkdef->SDKEnvRoot("srcroot", 1) );
    $settings->GetSet( "TOOLSROOT", $sdkdef->SDKEnvRoot("toolsroot", 0) );
    $settings->GetSet( "TOOLSROOT:", $sdkdef->SDKEnvRoot("toolsroot", 1) );
    $settings->GetSet( "INCLUDEROOT", $sdkdef->SDKEnvRoot("includeroot", 0) );
    $settings->GetSet( "INCLUDEROOT:", $sdkdef->SDKEnvRoot("includeroot", 1) );
    $settings->GetSet( "EXAMPLESROOT", $sdkdef->SDKEnvRoot("examplesroot", 0) );
    $settings->GetSet( "EXAMPLESROOT:", $sdkdef->SDKEnvRoot("examplesroot", 1) );
    $settings->GetSet( "DOCUMENTATIONROOT", $sdkdef->SDKEnvRoot("documentationroot", 0) );
    $settings->GetSet( "DOCUMENTATIONROOT:", $sdkdef->SDKEnvRoot("documentationroot", 1) );

    # Get the rest, perhaps they will be useful sometime..
    $settings->GetSet( "SDKId", $sdkdef->SDKId() );
    $settings->GetSet( "SDKRootPath", $sdkdef->SDKRootPath() );
    $settings->GetSet( "SDKDescription", $sdkdef->SDKDescription() );
    $settings->GetSet( "SDKName", $sdkdef->SDKName() );
    $settings->GetSet( "SDKPublisherName", $sdkdef->SDKPublisherName() );
    $settings->GetSet( "SDKPublisherWebSite", $sdkdef->SDKPublisherWebSite() );
    $settings->GetSet( "SDKPublisherLogo", $sdkdef->SDKPublisherLogo() );
    $settings->GetSet( "SDKLicenseName", $sdkdef->SDKLicenseName() );
    $settings->GetSet( "SDKWebLocation", $sdkdef->SDKWebLocation() );
    return 1;
}

__END__

=head1 NAME

sdkval.pl - Validate a candidate SDK using tests.

=head1 DESCRIPTION

The SDK Validation Tool validates a candidate SDK by running various tests
against it. The tests are defined in 'tdf' (test definition) files, some of
these are 'batches' which can load other 'tdf' files thus you can set up a
tree of tests to check specific functionality.

=head1 SYNOPSIS

perl sdkval.pl [ -h ] [ -v ] -tdfhome=<test-home> -tdf=<test> -manifest=<manifest file> -outputdir=<output directory> [-dummyrun=SyntaxCheck]

head1 OPTIONS

=over 8

=item B<--help|-g>

Display this usage message.

=item B<-v>

Verbose mode. All output is displayed to the current command-prompt window as
well as log-files.

=item B<-dummyrun=SyntaxCheck>

Load and run all batches, but when running 'leaf' tests suppress all actions.
Useful to check if there are any syntax errors in a batch of tests.

=item B<-tdfhome=Test Home>

Define where the 'home' of the current batch of tests is. It is important
to get this right. References within batches in particular use paths relative
to this location to define leaf tests or other batches to run.


=item B<-tdf=Test>

Define what test to run. This can be any tdf file but is likely to be a batch
which will load further batches and leaf tests.


=item B<-outputdir=Output Directory>

Define where output should be stored. All output is created in this area
within a new directory whose name is generated from the current date and time.
Within this directory, output is stored in a similar layout to the tdf files
being run.

=back

=cut

