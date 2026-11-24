# Copyright (c) 2005 Symbian Software Ltd. All Rights Reserved

=pod
=head1 NAME

Symbian::SDK::FilterTool - backend for SDKCreator/FilterTool

=head1 SYNOPSIS

 use Symbian::SDK::FilterTool;

 # $config is a Symbian::Config::Basic object
 my $filtertool = new Symbian::SDK::FilterTool($config);

 $filtertool->Run();

=head1 DESCRIPTION

This is the main backend of the FilterTool. It integrates the L<FilterFiles|FilterTool\FilterFiles> and L<WriteSDK|FilterTool\WriteSDK> stages.

=head1 METHODS

=cut
package Symbian::SDK::FilterTool;

use Symbian::SDK::FilterTool::ConfigValidator;
use Symbian::SDK::FilterTool::FilterFiles;
use Symbian::SDK::FilterTool::WriteSDK;
use Symbian::SDK::Substit;
use Symbian::SDK::Utils;

use Symbian::Config::Basic;

use File::Path;
use File::Spec;

=head2 new(Symbian::Config::Basic $config)

B<Returns>: Symbian::SDK::FilterTool - The newly created object

B<Parameters>:
  $config - The configuration object to be passed to each of the stages

Creates the object, validates the config, and initialises the environment

=cut
sub new($$)
	{
	my $class = shift;

	my $self = bless {}, $class;

	$self->init(@_);

	return $self;
	}

# private init(Symbian::Config::Basic $config)
#
# Returns: None
# Parameters: $config - The configuration object to store and use
#
# Initialiser for the constructor. Validates the config and initialises the env
sub init
    {
    my $self = shift;
    my $config = shift;

    # validate config immediately
    my $validator = Symbian::SDK::FilterTool::ConfigValidator->new();

    if (!$validator->ValidateConfig($config)) {
        die "ERROR: Configuration invalid: ", $validator->Error(), "\n";
    }

    # store validated config internally
    $self->{config} = $config;

    # now the config is valid, we can set up our working environment
    $self->prepare_environment();

    # finally, initialise helper objects
	$self->{"Filterer"} = new Symbian::SDK::FilterTool::FilterFiles();
	$self->{"Writer"} = new Symbian::SDK::FilterTool::WriteSDK();
    }

# private prepare_environment()
#
# Returns: None
# Parameters: None
#
# Ensures filter tool run is successful by checking everything is OK with the
# environment (setting extra environment variables as necessary).
sub prepare_environment
    {
    my $self = shift;

    # check input area exists
    my $root = $self->{config}->Get('input area');

    # ensure EPOCROOT is set correctly
    my $epocroot = $self->{config}->Get('epoc root');

    if (defined $epocroot) {

        $epocroot = File::Spec->catdir($root, $epocroot);

        # if there's a drive letter, make sure we're running on the same drive
        if ($epocroot =~ s/^([a-z]:)//i) { # N.B. this removes the drive letter
            chdir("$1\\") or die "ERROR: Couldn't chdir to $1\\\n";
        }

        # make sure there's a \ on the end of EPOCROOT
        $epocroot =~ s/(\\)?$/\\/;

        # now overwrite the environment variable with the config EPOCROOT
        $ENV{EPOCROOT} = $epocroot;
    }

    # set the CPATH environment variable for cpp.exe
    my $inc = $self->{config}->Get('cpp include');

    # may be a list or only one - convert to definite list
    my @paths = ref($inc) ? @$inc : ($inc);

    @paths = map(File::Spec->catdir($root, $_), @paths);

    $ENV{CPATH} = join(';', @paths);

	# Work out what our destination location should be. Attempt to subst
    # this to shorten the path because adding the work area, kit name,
    # kit id and paths within the SDK could easily blow the Windows 256
    # character path length limit. If the subst fails, we use the
    # concatenated path as it.
    my $destination = File::Spec->catdir(
		$self->{config}->GetSafe('work area'),
		$self->{config}->GetSafe('sdk name'),
		$self->{config}->GetSafe('sdk id'));

    if (!-d $destination) {
        mkpath($destination) or die "ERROR: Couldn't create path $destination: $!\n";
    }

	# create the subst in the filter tool object because it gets deleted when
	# the object is destroyed and we don't want that to be before we are done
    $self->{subst} = Symbian::SDK::Substit->new($destination);
    $destination = $self->{subst}->SubstPath if( ref($self->{subst}) );

	# set this so anyone can use it later
	$self->{config}->Set('sdk output root', $destination);

	# check cpp.exe is on the path
	Symbian::SDK::Utils::Which('cpp.exe') or die "ERROR: cpp.exe not found on %PATH%\n";
    }

=head2 Run()

B<Returns>: None

B<Parameters>: None

Main runner. Calls the L<FilterFiles|FilterTool\FilterFiles> and L<WriteSDK|FilterTool\WriteSDK> stages.

=cut
sub Run()
	{
	my $self = shift;

	my $files = $self->{"Filterer"}->Run($self->{"config"});
	$self->{"Writer"}->Run($self->{"config"}, $files);
	}

1;
