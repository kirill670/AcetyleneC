#!perl -w
#
# T e s t H a n d l e r
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

use strict;
package Symbian::SDK::Validate::Utility::TestHandler;

use Symbian::SDK::Validate::Logger::TestOut;
use Symbian::SDK::Validate::Logger::TestOutDefaults;
use Cwd;
use File::Basename;

use FindBin;
use lib $FindBin::Bin;

#
# A test handler class. The constructor 'new' takes a test definition
# file, and optionally two bits of syntax ('setparser' and 'runner')
# which, within the test definition file will be the keywords which
# define what object types should be instantiated to parse the remainder
# of the file, and to handle the commands within that file.
#
sub new
{
    my $arg = shift;
    my $class = ref($arg) ? ref($arg) : $arg;
    my $tdf = shift;
    my $tdfhome = shift;
    my $opd = shift;       # Output directory for reports.
    my $verbose = shift;
    my $setparser = shift;
    my $runner = shift;

    my $self = {
                 tdf        => undef,     # The test definition file.
                 tdfhome    => $tdfhome,  # Where tdfs live.
                 tdfcontent => undef,
                 parsername => undef,
                 setparser => "#!parser", # Default syntax for setting parser.
                 funcset => undef,        # A function set to execute the cmds.
                 runner => "#!runner",
                 funcobj    => undef,
                 parseobj   => undef,
                 testout => undef,
                 opd => $opd,
                 verbose => $verbose,
                 origpath => $ENV{PATH},
               };
    bless $self, $class;

    # Check if the user wants different syntax to set the parser and funcset
    # classes.
    $self->{setparser} = $setparser if(defined($setparser));
    $self->{runner} = $runner if(defined($runner));

    # Set the tdfhome member to something.. Is this a good idea? The
    # batch runner needs to know where tests call home, perhaps we
    # should insist on this being passed correctly.
	unless( $self->{tdfhome} and -d $self->{tdfhome} )
	{
        print STDERR "$class: FAIL: tdfhome must be an existing directory.\n";
        return undef;
	}

    # Make a 'logger' object to record output (aka 'testout')
    my $opfile = "$opd/$tdf";

    # For the moment use the default types from TestOutDefaults.
    $self->{testout} = Symbian::SDK::Validate::Logger::TestOut->new($opfile, $self->{verbose});
    unless(ref($self->{testout}))
    {
        print STDERR "$class: FAIL: Could not create TestOut object.\n";
        return undef;
    }

    # The test definition file must be set. If not just give up.
    if( $tdf )
    {
        # An error report has already been given if tdf is bad.
        return undef unless( defined($self->Tdf($tdf)) );
    }
    else
    {
        # We have no test definition file. Forget it.
        $self->{testout}->write_typedoutput(CTSDK_FAIL, "Test definition file not defined. I give up.");
        return undef;
    }

    # Find out the name of the parser and function set.
    return undef unless(defined($self->FindParser));
    return undef unless(defined($self->Funcset));

    # Create the object with all of the code to execute the
    # commands expected in the test definition file.
    return undef unless(defined($self->Funcobj));
                     
    # Parse the input file.
    return undef unless(defined($self->Parseobj));

    return $self;
}

sub Tdf  # Define the test definition file, or return what it is.
{
    my $self = shift;
    return undef unless ref($self);
    my $tdf = shift;
    return $self->{tdf} unless defined($tdf);

    undef($self->{tdf});
    undef($self->{funcset});    # We've changed file, this can't be valid..
    undef($self->{parsername}); # We've changed file, this can't be valid..
    undef($self->{parseobj});   # We've changed file, this can't be valid..
    undef($self->{funcobj});    # We've changed file, this can't be valid..
    undef($self->{tdfcontent}); # We've changed file, this can't be valid..

    # Lets have some proper forward slashes..
    $tdf =~ s/\\/\//g;

    # Is it a full path..? Batch runner is dependent on tdfhome being set
    # correctly, so this bit may be unnecessary (if we insist that a
    # valid tdfhome and relative 'tdf' location be specified).
    unless( ($tdf =~ m/^\//) or ($tdf =~ m/^[A-Z]:\//i) )
    {
        # Nope. So tack on the tdf home.
        $tdf  = $self->{tdfhome} . "/$tdf";
    }

    # Open the test definition file, and read it in one hit.
    unless(open TDF, $tdf) 
    {
        $self->Fail("Failed to open test definition file '$tdf'");
        return undef;
    }
    $self->{tdf} = $tdf;
    my @tdfcontent = <TDF>; close TDF;
    $self->{tdfcontent} = \@tdfcontent;

    # Before we return, put the directory where this test lives on the INC
    # array, so that perl scripts the test might want to call will be
    # easily available.
	my $pth = File::Basename::dirname($self->{tdf});
	$pth =~ s/\\/\//g;
    push @INC, $pth;
	$pth =~ s/\//\\/g;
	$ENV{PATH} = "$pth;" . $ENV{PATH};

    return $self->{tdf};
}

sub FindParser # Determine parser based on TDF if not already set. Return it.
{
    my $self = shift;
    return undef unless ref($self);
    return $self->{parsername} if( defined($self->{parsername}) );
    my $sp = $self->{setparser};
    for my $line (@{$self->{tdfcontent}})
    {
        if( $line =~ m/^\Q$sp\E\s+([^\s#]*)\s*$/ )
        {
            $self->{parsername} = $1;
            last;
        }
    }
    unless(defined($self->{parsername}))
    {
        $self->TestOut->write_typedoutput(CTSDK_FAIL, "Could not determine parser for '" . $self->Tdf . "'", "Use '" . $self->{setparser} . "' to define parser.");
        return undef;
    }
    # Check that the classname is fully qualified.
    unless( $self->{parsername} =~ m/^Symbian::SDK::Validate::Parser/ )
    {
        $self->{parsername} = "Symbian::SDK::Validate::Parser::" . $self->{parsername};
    }
    return $self->{parsername};
}

sub Funcset # Determine the funcset ('runner') based on TDF if not already set.
{
    my $self = shift;
    return undef unless ref($self);
    return $self->{funcset} if( defined($self->{funcset}) );
    my $sf = $self->{runner};
    for my $line (@{$self->{tdfcontent}})
    {
        if( $line =~ m/^\Q$sf\E\s+([^\s#]*)\s*$/ )
        {
            $self->{funcset} = $1;
            last;
        }
    }
    unless(defined($self->{funcset}))
    {
        $self->TestOut->write_typedoutput(CTSDK_FAIL, "Could not determine test runner for '" . $self->Tdf . "'", "Use '" . $self->{runner} . "' to define test runner class.");
        return undef;
    }
    # Check that the classname is fully qualified.
    unless( $self->{funcset} =~ m/^Symbian::SDK::Validate::Runner/ )
    {
        $self->{funcset} = "Symbian::SDK::Validate::Runner::" . $self->{funcset};
    }
    return $self->{funcset};
}

# Return the CommandImplementation object for this test handler, this
# contains a set of functions that implement the various commands.
sub Funcobj
{
    my $self = shift;
    return undef unless ref($self);

    # Already set up?
    return $self->{funcobj} if( ref($self->{funcobj}) );

    # No..
    # Try to create a new 'funcobj' object - this object contains all of the
    # code that knows what to do about commands. It will be an object
    # of a class derived from 'CommandImplementation'.
    #
    if( eval ("require $self->{funcset};") )
    {
        $self->{funcobj} = $self->{funcset}->new($self->{testout}, $self);
        unless(ref($self->{funcobj}))
        {
            $self->Fail("TestHandler: Failed to create CommandImplementation of class '" .  $self->Funcset . "'\n" );
        }
    }
    else
    {
        $self->Fail("TestHandler: Couldn't create command implementation object '" .  $self->Funcset . "'", "Error was '$@'\n" );
        undef($self->{funcobj});
    }
    return $self->{funcobj};
}

# Return the Parser object for this test handler, this contains a linked
# list of elements each representing one command.
sub Parseobj
{
    my $self = shift;
    return undef unless ref($self);

    # Already set up?
    return $self->{parseobj}
           if( defined($self->{parseobj}) and ref($self->{parseobj}) );

    # No..
    # Try to create a new 'parseobj' object - this object knows how to parse
    # the test definition file. We need to have the 'Funcobj' set up, because
    # that knows what commands are valid.
    if( eval ("require $self->{parsername};") )
    {
        if( my $funcobj = $self->Funcobj )
        {
            my @knowncommands = $funcobj->ListAvailableCommands;
            $self->TestOut->write_typedoutput(CTSDK_INFO, "Parsing '" . $self->Tdf . "'" );
            $self->{parseobj} = $self->FindParser->new($self->{tdfcontent},
                                      1, \@knowncommands, $self->TestOut );
          
# This report of parser creation failure is commented out because the parser
# itself reports any problems.
#
#        $self->Fail("TestHandler: Failed to create parser object of class '" .
#                   $self->FindParser . "'\n" ) unless ref($self->{parseobj});
        }
    }
    else
    {
        $self->Fail("TestHandler: Require failed for parser class '" .
                              $self->FindParser ."' error: '$@'\n" );
        undef($self->{parseobj});
    }
    return $self->{parseobj};
}

# Execute the test..
sub ExecuteTest
{
    my $self = shift;
    return undef unless ref($self);
    # The dummy value. This prevents tests actually running in the Funcobj
    # object, it just loads up all as necessary, looking for bad syntax etc.
    # This can have any numeric value, so that certain areas can be run
    # conditionally, e.g to check syntax of 'lower-level' tests loaded by
    # batches.
    my $dummy = shift;

    # Get the CommandImplementation derived function object (contains
    # all the intelligence to execute a command). Set up the dummy run flag.
    my $fo = $self->Funcobj;
    $fo->DummyRun($dummy) if(defined($dummy));

    # The Reporter object.
    my $to = $self->TestOut;

	# Get the first command in the chain.
	my $torun = $self->Parseobj;
	my $result = $fo->ExecuteTest($torun);

    return 1;
}

# Report an error through the testout object.
sub Fail
{
    my $self = shift;
    return undef unless(ref($self));
    
    if(ref($self->TestOut))
    {
        # The type of the report, a number.
        my $msgtype = CTSDK_FAIL;
        $self->TestOut->write_typedoutput($msgtype, @_);
        return;
    }
    print STDERR "FAIL: ", @_;
}

# The reporter object.
sub TestOut
{
     my $self = shift;
     return undef unless(ref($self));
     my $to = shift;
     $self->{testout} = $to if defined($to);
     return $self->{testout};
}
 
sub DESTROY
{
	my $self = shift;
	return undef unless(ref($self));
	$ENV{PATH} = $self->{origpath};
}


1;

