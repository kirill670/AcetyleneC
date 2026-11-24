#!perl -w
#
# T D F B a t c h F u n c s
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

#
# Batch runner function set.
#
# The methods provided in this class allow execution of 'batch' type tdf
# files. These basically consist of a list of other tests to run (using
# the 'tdf' command), plus a method 'prerun' to check whether this batch
# should be run.
#
use strict;
package Symbian::SDK::Validate::Runner::TDFBatchFuncs;
use FileHandle;
use File::Basename;

# This class is derived from CommandImplementation..
use base ("Symbian::SDK::Validate::Runner::CommandImplementation");

use Symbian::SDK::Validate::Logger::TestOut;           # For reports..
use Symbian::SDK::Validate::Logger::TestOutDefaults;   # ditto..
use Symbian::SDK::Validate::Utility::TestHandler;      # Needed to run tests.
use Symbian::SDK::Validate::Runner::CheckOutput;      # Needed to checkoutput

#
# This class contains all of the intelligence to deal with specific batch
# commands.
#

#
# Setup the hash of commands we know how to deal with.
#
# This hash contains keys which are commands we know about, the value is
# a reference to a subroutine that knows what to do about it.
#
sub SetupCommandsHash
{
    my $self = shift;
    return undef unless(ref($self));

    my %commandshash = (
                     failonskip => \&failonskip,
                           hold => \&hold,
                         prerun => \&prerun,
                        setting => \&setting,
                         setenv => \&setenv,
                            tdf => \&tdf,
                       );

    $self->{commandshash} = \%commandshash;
}

#
# G a t e w a y
#
# When a command is executed, we come into this module through this method.
#
sub Gateway
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parse object.
    $po->InterpolateEnvironmentVariables;
    $po->InterpolateSettings($self->Settings);
    return undef unless(ref($po));
    my $cmd = lc($po->Command);
    return undef unless($cmd);

    # Put a line in the output...
    $self->TestOut->Report('-'x75);

    # Display all of the lines that make up this command, i.e comments,
    # brace blocks etc.
    $self->DisplayCommand($po);

    # Display what we are actually running. If an environment variable
    # was in the command or argument it will have been interpolated so
    # what gets run could be very different from what is in the test
    # definition file.
    my $running = "\tRunning '$cmd";
    $running .= $po->{args} ? " " . $po->{args} . "'" : "'";
    $self->TestOut->Report($running);

    # Find the method to run and run it..
    my $coderef = $self->{commandshash}->{$cmd};
    my $rc;
    if( ref($coderef) )
    {
        $rc = $self->$coderef($po)
    }
    else
    {
        $rc = $self->Unknown($po)
    }

    # Report any failure.
    $self->TestOut->write_typedoutput(CTSDK_FAIL, "Failure in command '$cmd'")
        unless($rc);

    # Record running of this step.
    $self->{testout}->write_typedoutput(CTSDK_RUN, 1);

    return 0;
}

#
# f a i l o n s k i p
#
# Useful for developing batches to verify that execution is definitely
# happening rather than failing to run due to a dodgy 'prerun' script. Not
# much use for a live test.
#
sub failonskip
{
    my $self = shift;
    return undef unless(ref($self));
    my $dr = $self->DummyRun;
    if($dr and ($dr eq "skip" or $dr eq "skipall"))
    {
        $self->TestOut->write_typedoutput( CTSDK_FAIL, "Skip flag is on!");
        return 1;
    }
    $self->TestOut->write_typedoutput( CTSDK_INFO, "Skip not on.");
    return 1;
}

#
# h o l d
# 
# Stop until the user hits a key. Useful for debugging new test files.
# Force the verbose flag on the logger object to be on so even if output
# is suppressed we get the prompt..
#
sub hold
{
    my $self = shift;
    return undef unless(ref($self));
    my $verbose = $self->TestOut->Verbose();
    $self->TestOut->Verbose("verbose") unless($verbose);
    $self->TestOut->write_typedoutput( CTSDK_INFO, "Method 'hold' called. Hit carriage-return when ready.");
    <STDIN>;
    $self->TestOut->Verbose($verbose);

    return 1;
}

#
# P r e r u n
#
# Check that the required groups have been installed before attempting
# to run tests relating to them.
#
sub prerun
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parseoject.
    return undef unless(ref($po));
    my $settings = $self->Settings;

    # First, work out what arguments we have.
    my $lineno = $po->{homelineno};
    my $args = $po->{args};

    # Get the location of this test.
    my $tloc = File::Basename::dirname($self->ParentTestHandler->Tdf);
    $tloc =~ s/\\/\//g;

    # Check if 'args' is unset. This should only happen if the test gave
    # no arguments to 'prerun', or (more likely) the argument was an
    # environment variable which was not set. Run the test anyway if so.
    unless($args)
    {
        $self->TestOut->write_typedoutput(CTSDK_FAIL, "No script to prerun. Batch disabled.");
        return 0;
    }
    if($args =~ m/\S+\.pl/)
    {
	$args =~ s/(\S+\.pl)/perl -I $tloc $tloc\/$1/;
    }else
    {
        $args = $tloc/$args;
    }

    # Run the command..  If it is a Perl script that attempts to 'use' its
    # own module (from the same directory), that will fail, but it will
    # just have to use FindBin won't it?
    open PR, $args . " 2>&1 |" or $self->TestOut->write_typedoutput(CTSDK_FAIL, "Could not run prerun command '$args'.");
    while(my $line = <PR>)
    {
        $self->TestOut->Report("- " . $line); # Display any output.
        # Look for the case where the command could not be found. Unfortunately
        # there doesn't seem to be a way to do this using return codes etc
        # that can't be duplicated with a script.
        if( $line =~ m/\'\Q$args\E\' is not recognized as an internal or external command,/ )
        {
            $self->TestOut->write_typedoutput(CTSDK_FAIL, "Could not find prerun script '\Q$args\E'.\n");
        }
    }
    close PR;

    # Get the return code. Should be zero.
    my $rc = ($? >> 8);
    if($rc)
    {
        $self->TestOut->write_typedoutput(CTSDK_INFO, "Prerun command failed. (rc '$rc'). Check output displayed before this message.", "Batch disabled.");
    }
    else
    {
        $self->TestOut->write_typedoutput(CTSDK_INFO, "Prerun command successful. Batch enabled.");
    }

    # If the return code is not zero, something didn't work. Set the dummy run
    # flag. It's a convenient way of preventing any other operations (other
    # than 'tdf's) running. A dummy run value of "skipall" would prevent tdf's
    # from running.
    if($rc)
    {
        $self->DummyRun("skip");
    }
    return 1;
}

#
# s e t t i n g
#
# Set an internal value (as accessed with !!these!!) based on others. This
# is useful to define, for example where example source lives based on
# other settings. One day the Manifest file could define where the example
# source is, but we can make our own setting based on others *in one place*,
# so if we get it wrong we can correct it easily.
#
sub setting
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;
    return undef unless(ref($po));
    my $dr = $self->DummyRun;
    return 1 if($dr and (($dr eq "skip") or ($dr eq "skipall")));
    my $settings = $self->Settings;

    # e.g 'setting mysetting = !!SomeOtherSetting!!/fredo.txt'
    my $args = $po->{args};
    if( $args =~ m/(.*?)=(.*$)/ )
    {
        my $lhs = $1;
        my $rhs = $2;
        $lhs =~ s/\s*//g;  # Lose white space from our setting name.
        $rhs =~ s/^\s*//;  # Lose leading white space from its value.
        $self->TestOut->write_typedoutput(CTSDK_INFO, "Setting internal value !!$lhs!! to '$rhs'");
        $settings->GetSet( $lhs, $rhs );
        return 1;
    }
    $self->TestOut->write_typedoutput(CTSDK_FAIL, "Bad syntax '$args' for 'setting'");
    return 1;
}

#
# Set an environment variable..
#
sub setenv
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parseoject.
    return undef unless(ref($po));

    # First, work out what arguments we have.
    my $args = $po->{args};
    unless(defined($args))
    {
        $self->TestOut->write_typedoutput(CTSDK_FAIL, "No arguments to 'setenv'.");
        return 0;
    }

    my $lineno = $po->{homelineno};
    my $command = $po->{command};

    # Determine the variable and the value to set it to.
    $args =~ m/^\s*(\S*)\s*=(.*)/  ;
    my $var = uc($1);
    my $val = $2;

    # If value has a value then go for it, otherwise clear the variable.
    if( $val )
    {
        $self->{testout}->write_typedoutput(CTSDK_INFO, "Setting environment variable '$var' to '$val'.\n");
        $ENV{$var} = $val;
    } else
    {
        $self->{testout}->write_typedoutput(CTSDK_INFO, "Unsetting environment variable '$var'.\n");
        delete ($ENV{$var});
    }
    return 1;
}

#
# t d f
#
# Run a test definition file within this batch.
#
sub tdf
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;
    return undef unless(ref($po));
    my $dr = $self->DummyRun;

    # dr should never be "skipall" unless passed in by the user, in which case
    # very little will run.
    if($dr and $dr eq "skipall")
    {
        $self->TestOut->write_typedoutput(CTSDK_DUMMYRUN, "'Skipall' flag set. Step skipped.");
        return 1;
    }

    # First, work out what arguments we have.
    my $lineno = $po->{homelineno};
    my $args = $po->{args};

    # See if there is a 'CheckOutput' block. If so, we will assume that
    # results will not be inherited, but checked. In this way we can have
    # a component test that correctly generates failures which is proper
    # (i.e PASSing) behaviour.
    my $settings = $po->Settings;
    my $expout = ( $settings->GetSet("checkoutput_pass") or
                      $settings->GetSet("checkoutput_fail") or
                      $settings->GetSet("checkoutput_ordered") );
    # Inherit results?
    my $ir = !$expout;

    # Now run the tdf, passing the inherit results flag. The runtdf method
    # returns the filename of the output generated by the tdf. We are calling
    # this in a separated method so by the time it gets back here it will have
    # all gone out of scope, destructors will have been called and so on, i.e
    # it will have finished, completely.
    my $fn = $self->runtdf($po, $ir);
    # We've already inherited the results unless there was a CheckOutput block.
    # There's no point in checking the output if we're doing a dummy run
    # because it will be very different from a real run.
    return 1 if($ir or $dr);

    # Ok, we have to check the output.
    my $fi = FileHandle->new($fn);

    # If DummyRun is set we don't get this far. 
    return (Symbian::SDK::Validate::Runner::CheckOutput->new( undef, $self->TestOut, $fi, $settings ));
}

#
# r u n t d f
#
# Run a test definition file within this batch.
#
sub runtdf
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;
    return undef unless(ref($po));
    my $ir = shift;

    # First, work out what arguments we have.
    my $lineno = $po->{homelineno};
    my $args = $po->{args};

    # Where does output go? Each tdf will get it's own output file.
    # The ParentTestHandler is an instance of the TestHandler class,
    # this is the one that spawned this object.
    my $opd = $self->ParentTestHandler->{opd};

    # Find out if we're doing a dummy run..
    my $dr = $self->DummyRun;

    # Find out how verbose we're being..
    my $verbose = $self->TestOut->Verbose();

    # Find out where our tests call home..
    my $th = $self->ParentTestHandler->{tdfhome};
    $th =~ s/\\/\//g if(defined($th));

    # Report what we're doing..
    $self->TestOut->Report( '='x10 . " TDF '$args' starting... " . '='x10 );

    # The provided argument should be a test definition file, e.g examples/ex1
    my $test = Symbian::SDK::Validate::Utility::TestHandler->new( $args, $th, $opd, $verbose );

    # If we failed to get the test object then we have a failure. Something
    # went wrong. The TestHandler object will have reported on that, but
    # only into its own TestOutput object. We want to report it too.
    unless(ref($test))
    {
        $self->TestOut->write_typedoutput( CTSDK_FAIL, "Failed to create Test Handler object (line $lineno)");
        return 0;
    }

    # Before we execute the test, pass on our settings. We must make a copy
    # because we don't want a low level test affecting the whole batch.
    # We must knock out the 'failurestack' though, because that propagates
    # UPWARD towards batches NOT downwards toward leaf tests.
    if(my $funcout = $test->Funcobj)
    {
        my $newsettings = $self->Settings->Copy();
        $newsettings->Unset("failurestack"); 
        $funcout->Settings($newsettings);
    }

    # If we're doing a dummy run make sure that this is also dummy run..
    # Run the test.
    $test->ExecuteTest($dr);

    # Add the score for all kinds of reports, Pass', Fails, Info's, everything
    # to our score IF the 'inherit results' flag is set.
    my $to = $test->TestOut;      # The testout object just created..
    if($ir)
    {
        for my $type ($to->ListTypes) # The types within that..
        {
            my $score = $to->Types->{$type}->Score; # The score for each.
            next unless($score);
            my $myoptype = $self->TestOut->Types->{$type};  # My output types.
            if( ref($myoptype) )
            {
                my $name = $myoptype->Name;
                $self->TestOut->write_typedoutput( $type, "$score $name\'s detected running $args\n");
                $myoptype->AddToScore($score-1);
            }
        }

        # This lot is to record where failures have happened. Knowing that a
        # batch has failed isn't very useful if the reason is one of its
        # subtests broke. This will naturally not get executed if we don't
        # want results inherited.
        # Note that 'failurestack' is explicitly prevented from being passed
        # to lower level tests so only 'TDFBatchFunc' tests should ever own
        # a 'failurestack' setting.
        my $ok = $to->IsStatusGood();
        unless($ok)
        {
            my $settings = $self->Settings;
            my $failstack = $settings->GetSet("failurestack");
            $failstack = [] unless(ref($failstack));
            my $tofo = $test->Funcobj;
            my $toset = $tofo->Settings if(ref($tofo));
            my $tofs = $toset->GetSet("failurestack") if(ref($toset));
            if(ref($tofs))
            {
                push @$failstack, @$tofs;
            }
            push @$failstack, $args;
            $settings->GetSet("failurestack", $failstack);
        }
    }

    # Report ..
    $self->TestOut->Report( '='x10 . " Batch $args complete.." . '='x10 );

    # Explicitly undef the testhandler member because that is a circular
    # reference and can prevent destruction.
    undef($test->Funcobj->{testhandler}) if($test and $test->Funcobj);

    # Return the file that results were stored in.
    return $to->OutputFile;
}

1;
