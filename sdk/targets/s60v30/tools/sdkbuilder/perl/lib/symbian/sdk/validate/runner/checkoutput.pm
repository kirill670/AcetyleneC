#!perl -w
#
# C h e c k O u t p u t
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#
use strict;

package Symbian::SDK::Validate::Runner::CheckOutput;

use Symbian::SDK::Validate::Parser::CommandElement;
use Symbian::SDK::Validate::Utility::Settings;
use Symbian::SDK::Validate::Logger::TestOut;
use Symbian::SDK::Validate::Logger::TestOutDefaults;
use IO::Pipe;

sub new
{
    my $arg = shift;
    my $class = ref($arg) || $arg;
    my $commandtorun = shift;
    my $testout = shift;
    return undef unless($testout);
    my $providedstream = shift;

    # Expected output is a Settings object that contains at most three
    # arrays of (un)expected output.
    my $expectedoutput = shift;

    my $self = { command => $commandtorun,
                 testout => $testout,
                 iopipe => $providedstream,
                 expectedoutput => $expectedoutput,
                 state => 1, };

    bless $self, $class;

    # If we haven't been provided with an alternate stream, run the
    # command provided, creating a pipe (setting up iopipe).
    unless($self->{iopipe})
    {
        return undef unless($self->Runit);
    }

    # Check the output. Output is recorded interspersed with reports from
    # the output checking.
    return undef unless($self->CheckOutput);

    # This object does not persist. This return value is 0 if any report
    # of failure was made, 1 otherwise.
    return $self->{state};
}

sub DESTROY
{
    my $self = shift;
    return undef unless(ref($self));

    # Close the pipe. Probably unnecessary, but lets be tidy..
    $self->{iopipe}->close() if(defined($self->{iopipe}));

    # Make sure any child process has finished.
    wait;

    # The return status will be in $?, but we can't do anything with that.
}

# Run the command and attach it to the pipe. Don't check anything.
# Only necessary if we weren't provided with a stream.
sub Runit
{
    my $self = shift;
    return undef unless(ref($self));
    return undef unless(defined($self->{command}));

    my $pipe = new IO::Pipe;
    return undef unless($pipe);
    $self->{iopipe} = $pipe;

    # Combine STDOUT and STDERR.
    my $command = $self->{command} . " 2>&1";

    # Tell the user what we're doing..
    $self->{testout}->write_typedoutput( CTSDK_INFO, "Running command '" . 
            $self->{command} . "'" );

    # Run the command.
    $pipe->reader($command);

    return 1;
}

#
# c h e c k o u t p u t
#
# Go through the output of whatever is running checking it against any
# defined 'pass's, 'fail's or 'ordered's. The word 'ordered' is nearly
# the same as 'pass', but the array of expected output seen in the ordered
# array must appear in order. Obvious really, :)
#
sub CheckOutput
{
    my $self = shift;
    return undef unless(ref($self));
    return undef unless(ref($self->{iopipe}));
    return undef unless(ref($self->{testout}));

    # Get the (un)expected output into three arrays.
    my @fail_expout = ();
    my @pass_expout = ();
    my @ordr_expout = ();

    # If any (un)expected output is defined, set up the relevant arrays.
    # Note the arrays are copies of the originals because as we see the
    # output the will steadily get deleted.
    if( ref($self->{expectedoutput}) )
    {
        my $pa = $self->{expectedoutput}->GetSet("checkoutput_pass");
        @pass_expout = @$pa if(ref($pa));
        my $fa = $self->{expectedoutput}->GetSet("checkoutput_fail");
        @fail_expout = @$fa if(ref($fa));
        my $or = $self->{expectedoutput}->GetSet("checkoutput_ordered");
        @ordr_expout = @$or if(ref($or));
        $self->{testout}->write_typedoutput( CTSDK_INFO, "- Checking output...." );
    }

    # Read the output of the command.
    my $PIPE = $self->{iopipe};

    while(my $opline = <$PIPE>)
    {
        chomp($opline);
        chomp($opline);
        $self->{testout}->Report("- " . $opline);

        # Look for lines that should not be present, i.e we don't want them.
        # The array contains 'CommandElement's, we have to get the text out.
        # Also fetch the line number so reports can be easily correlated to
        # the original test definition file.
        for my $fail (@fail_expout)
        {
            next unless(defined($fail));
            my $text = $fail->CommandLine;  # Comments, leading space removed.
            my $multimatch=0;
            if($text =~ m/^\*\s*/)   # Look for '*   pattern' for multimatch.
            {
                $text =~ s/^\*\s*//;
                $multimatch = 1;
            }
            my $lineno = $fail->Lineno;
            if( $opline =~ m/($text)/ )
            {
                my $match = $1;
                $opline =~ s/(\Q$match\E)//; # Lose the matched text from input.
                undef($fail) unless($multimatch); # Matched this case, Lose it..
                $self->{state} &= $self->{testout}->write_typedoutput( CTSDK_FAIL, "Detected specifically excluded output '$match' (line $lineno)." );
            }

        }
        # Look for lines that should be present in a specific order.
        for my $ordp (@ordr_expout)
        {
            next unless(defined($ordp));
            my $text = $ordp->CommandLine; # Comments, leading space removed.
            my $lineno = $ordp->Lineno;
            if( $opline =~ m/($text)/ )
            {
                my $match = $1;
                $opline =~ s/(\Q$match\E)//; # Lose the matched text from input.
                undef($ordp);           # Matched this case, get rid of it..
                $self->{testout}->write_typedoutput( CTSDK_PASS, "Got expected ordered output '$match' (line $lineno)." );
            }
            else { last; } # We didn't see this expected output, don't check
                           # the rest, they don't get checked until this one
                           # is done.

        }
        # Look for lines that should be present in any order.
        for my $pass (@pass_expout)
        {
            next unless(defined($pass));
            my $text = $pass->CommandLine; # Comments, leading space removed.
            my $lineno = $pass->Lineno;
            my $multimatch=0;
            if($text =~ m/^\*\s*/)   # Look for '*   pattern' for multimatch.
            {
                $text =~ s/^\*\s*//;
                $multimatch = 1;
            }
            if( $opline =~ m/($text)/ )
            {
                my $match = $1;
                $opline =~ s/(\Q$match\E)//; # Lose the matched text from input.
                undef($pass) unless($multimatch);  # Lose this case..
                $self->{testout}->write_typedoutput( CTSDK_PASS, "Got expected output '$match' (line $lineno)." );

                # A bit naughty this. We add a new member to the CommandElement
                # 'pass' called 'matched' pointing out we have found this
                # case. This is necessary to suppress a failure that would
                # happen otherwise where the code below seeing a still defined
                # 'pass' case would assume unmatched required output.
                $pass->{matched} = 1 if(defined($pass));
            }
        }
    }

    # 
    # Generate a failure for any expected output that was not seen.
    #
    for my $missedpass (@ordr_expout)
    {
        next unless(defined($missedpass));
        my $text = $missedpass->CommandLine; # Comments, leading space removed.
        my $lineno = $missedpass->Lineno;
        $self->{state} &= $self->{testout}->write_typedoutput( CTSDK_FAIL, "Failed to get expected ordered output '$text' (line $lineno)." );
    }
    for my $missedpass (@pass_expout)
    {
        next unless(defined($missedpass));
        if($missedpass->{matched})
        {
            undef($missedpass->{matched}); # Get rid of this.
            next;
        }
        my $text = $missedpass->CommandLine; # Comments, leading space removed.
        my $lineno = $missedpass->Lineno;
        $self->{state} &= $self->{testout}->write_typedoutput( CTSDK_FAIL, "Failed to get expected output '$text' (line $lineno)." );
    }

    return 1;
}

1;
