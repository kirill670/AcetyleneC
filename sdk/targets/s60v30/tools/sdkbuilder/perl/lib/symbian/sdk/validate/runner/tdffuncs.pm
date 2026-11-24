#!perl -w
#
# T D F F u n c s
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#

#
# TDF runner function set.
#
# The methods provided in this class allow execution of 'test' type tdf
# files. These basically consist of a list of operations to perform
# to validate the target SDK.
#
use strict;
package Symbian::SDK::Validate::Runner::TDFFuncs;

# This class is derived from CommandImplementation..
use base ("Symbian::SDK::Validate::Runner::CommandImplementation");

use Symbian::SDK::Validate::Logger::TestOut;         # For reports..
use Symbian::SDK::Validate::Logger::TestOutDefaults; # ditto..
use Symbian::SDK::Validate::Runner::CheckOutput;     # For checking output
use Symbian::SDK::Validate::Runner::ManualDialog;    # For user interaction.
                                                      # against what is expected.
use POSIX qw(strftime);            # For the Printtime method.
use Cwd;

#
# This class contains all of the intelligence to deal with specific 'TDF'
# commands.
#

#
# Setup the hash of command we know how to deal with.
#
# This hash contains keys which are commands we know about, the value is
# a reference to a subroutine that knows what to do about it.
#
sub SetupCommandsHash
{
    my $self = shift;
    return undef unless(ref($self));

    my %commandshash = (
                          abortunless    => \&abortunless,
                          assert         => \&assert,
                          cd             => \&cd,
                          critical       => \&critical,
                          direxists      => \&direxists,
                          echo           => \&echo,
                          fileexists     => \&fileexists,
                          hold           => \&hold,
                          manualstep     => \&manualstep,
                          printtime      => \&printtime,
                          runcmd         => \&runcmd,
                          runperl        => \&runperl,
                          setenv         => \&setenv,
                          unknown        => \&unknown  );

    $self->{commandshash} = \%commandshash;
}

sub ExecuteTest
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;
    return undef unless(ref($po));

    my $startId = $self->TestOut->CreateSnapshot();

    my $lastrc = "some value not returned";
    for( my $torun=$po ; defined($torun) ; $torun = $torun->{nextcommand} )
    {
        # Normally rc is just undef, 0 or 1. But 'manualstep's can ask us
        # to restart. We do this at the beginning of the loop or we end
        # up restarting at the second test.
        if($lastrc eq "RESTART")
        {
            $torun = $po;
            $self->TestOut->RestoreSnapshot($startId);
            $lastrc = "some value not returned";
        }

        # Execute it, passing the parsed information from the test definition
        # file.
        $lastrc = $self->Gateway($torun);

    }
    # This is a bit nasty, we have to undefine the snapshots in the logger
    # object before we finish executing the test or a circular reference
    # remains and the logger doesn't DESTROY cleanly.
    undef($self->TestOut->{snapshots});
}

#
# G a t e w a y
#
# Before a command is executed we go through this method.
# This allows us to not actually execute the step if for example a failure
# has already occured in a 'critical' block.
# We return undef, 0, 1 or whatever the particular implementation method
# called returned.
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
    my $settings = $self->Settings;  # Settings object.

    # Put a line in the output..
    if($cmd)
    {
        my $c2 = "-- Running command '$cmd";
        $c2 .= " " . $po->{args} if($po->{args});
        $c2 .= "' ";
        $c2 .= '-'x(75-length($c2)) if(length($c2) < 75); 
        $self->TestOut->Report($c2);
    }
    else
    {
        $self->TestOut->Report('-'x75);
    }

    # Show the command, comments and everything. Return if 'cmd' is not
    # set. This can happen at the end of a tdf where there is no command
    # to execute, just a bunch of comments.
    $self->DisplayCommand($po);
    return undef unless($cmd);

    # Check the DummyRun flag..
    if( $self->DummyRun )
    {
        $self->TestOut->write_typedoutput(CTSDK_DUMMYRUN, "Dummy run flag set. Step skipped.");
        return 1;
    }

    # Get the current settings within this test for skipremainder and
    # critical.
    my $skipremainder = $settings->GetSet("skipremainder");
    my $critical = $settings->GetSet("critical");

    # Set default for skipremainder and critical
    unless(defined($skipremainder))
    {
        $skipremainder = "off";
        $settings->GetSet("skipremainder", "off");
    }
    unless(defined($critical))
    {
        $critical = "off";
        $settings->GetSet("critical", "off");
    }

    #
    # Run the code unless we're in a critical block and a failure has
    # been seen.
    #
    unless($skipremainder eq "on" )
    {
        # Find the method to run and run it..
        my $coderef = $self->{commandshash}->{$cmd};
        my $rc;
        if( ref($coderef) )
        {
            $rc = $self->$coderef($po);
        }
        else
        {
            $rc = $self->Unknown($po);
        }

        # Record running of this step.
        $self->{testout}->write_typedoutput(CTSDK_RUN, 1);

        # Did it fail within a critical block?
        if( (!$rc) and ($critical eq "on") )
        {
            $settings->GetSet("skipremainder", "on");
            $self->{testout}->write_typedoutput(CTSDK_INFO, "Failure within critical block. Remaining steps will be skipped." );
        }
        return $rc;
    }
    # The remainder of the input is being skipped.
    my $command = $po->{command};
    $self->{testout}->write_typedoutput(CTSDK_NOT_RUN, $command . "\n")
            if( $command );

    return 1;
}

#
#
# A b o r t U n l e s s
#
# Same as 'assert', but when interpreted will force all following steps
# to be skipped if the assertion fails.
#
sub abortunless
{
    my $self = shift;
    return undef unless(ref($self));
    
    my $rc = $self->assert(@_);
    unless($rc)
    {
        my $settings = $self->Settings;
        $self->TestOut->write_typedoutput( CTSDK_INFO, "Failure in 'abortunless'. All remaining steps will be skipped.");
        $settings->GetSet("skipremainder", "on" );
    }
    return $rc;
}

#
# A s s e r t
# 
# Check the specified condition is true.
#
sub assert
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parseoject.
    return undef unless(ref($po));

    # First, work out what line number the command appeared at.
    my $lineno = $po->{homelineno};

    # Get the line specified in the test definition file.
    my $test = $po->{args};

    # Try it.
    my $rc = eval $test;
    $rc = 0 if( !defined($rc) or ($rc==0) ); # Force numeric 0 on failure.
    
    #
    # So did it work?
    # Report.
    #
    if( $@ )
    {
        $self->{testout}->write_typedoutput(CTSDK_FAIL, "Assertion '$test' gave Perl error '$@' at $lineno.\n");
    }

    # Ok, no Perl errors, but the assertion my have failed.
    if($rc)
    {
        $self->{testout}->write_typedoutput(CTSDK_PASS,  "Assertion '$test' at line $lineno.\n");
    }else
    {
        $self->{testout}->write_typedoutput(CTSDK_FAIL, "Assertion '$test' gave return code '$rc' at line $lineno.\n");
    }

    return($rc);
}

#
# Change directory. Note that some commands require the current directory
# to be !!homedir!!, so use 'cd !!homedir!!' when you aren't poking about within
# the SDK..
#
sub cd
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parseoject.
    return undef unless(ref($po));
    my $args = $po->{args};

    chdir($args) or $self->{testout}->write_typedoutput(CTSDK_FAIL, "Failed to cd to directory '$args'.");
    return 1;
}

#
# Set/Unset the critical flag.
#
sub critical
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parseoject.
    return undef unless(ref($po));
    my $settings = $self->Settings;

    # First, work out what line number the command appeared at.
    my $lineno = $po->{homelineno};
    my $args = $po->{args};

    if($args and $args =~ m/^\s*on\s*$/i )
    {
        $settings->GetSet("critical", "on" );
        return 1;
    }
    if($args and $args =~ m/^\s*off\s*$/i )
    {
        $settings->GetSet("critical", "off" );
        return 1;
    }
    
    $self->{testout}->write_typedoutput(CTSDK_FAIL, "Unknown value '$args' passed to 'critical' command.");
    return 0;
}

#
# d i r e x i s t s
#
# Verify that the specified directory exists.
#
sub direxists
{
    my $self = shift;
    return undef unless(ref($self));

    return( $self->myexists(@_, "d") );
}

#
# E c h o
# 
# Just display the command line and attached list.
#
sub echo
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parseoject.
    return undef unless(ref($po));

    # First, work out what arguments we have.
    my $args = $po->{args};
    my $lineno = $po->{homelineno};
    my $command = $po->{command};

    # Echo the arguments if there are any.
    $self->{testout}->Report( "- $args" );

    # Is there anything else to echo in a list?
    my $cmdsettings = $po->Settings;
    my $more = $cmdsettings->GetSet("listitem");
    for my $element (@$more)
    {
        my $item = $element->CommandLine;  # Comments already stripped.
        $self->{testout}->Report( "- $item" );
    }
    # Could anything have gone horribly wrong?
    return 1;
}

#
# f i l e e x i s t s
#
# Verify that the specified directory exists.
#
sub fileexists
{
    my $self = shift;
    return undef unless(ref($self));

    return( $self->myexists(@_, "f") );
}

#
# h o l d
# 
# Stop until the user hits a key. Useful for debugging new test files.
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
# P r i n t t i m e
# 
# Just display the current time. 
#
sub printtime
{
    my $self = shift;
    return undef unless(ref($self));
    my $ts = POSIX::strftime "%c", localtime;
    $self->{testout}->write_typedoutput( CTSDK_INFO, "Time is now: $ts\n" );
    return 1;
}

# Run a step within a test manually. We prompt the test engineer and receive
# feedback.
sub manualsteptext
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parseoject.
    return undef unless(ref($po));
    my $cmdsettings = $po->Settings;
    return 0 unless(ref($cmdsettings));

    my $prompt = $cmdsettings->GetSet("listitem_prompt");
    my $question = $cmdsettings->GetSet("listitem_question");
    my $actions = $cmdsettings->GetSet("manual_action");

    # Display the instructions on how to do something.
    for my $el (@$prompt)
    {
        $self->TestOut->Report($el->CommandLine);
    }
    # Build a temporary hash out of the information in 'actions'.
    my %tmphsh;
    for my $el (@$actions)
    {
        my $cl = $el->CommandLine;
        next unless($cl =~ m/^\s*(warn|info|pass|fail)\s+(\S+)\s+(.*$)/i);
        my $pf = lc($1); # pass or fail.
        my $msgtype = CTSDK_PASS if($pf eq "pass" );
           $msgtype = CTSDK_FAIL if($pf eq "fail" );
           $msgtype = CTSDK_INFO if($pf eq "info" );
           $msgtype = CTSDK_WARNING if($pf eq "warn" );
        my $bn = $2;     # 'Button name' if we had a gui.
        my $msg = $3;     # Message to display.
        $tmphsh{$bn} = { msgtype => $msgtype,
                         message => $msg };
    }

    # Ask a question about it.
    for my $el (@$question)
    {
        $self->TestOut->Report($el->CommandLine);
    }

    $self->TestOut->Report("Please enter one of the following: " . join(", ", keys %tmphsh) . "." );
    # Get the response from the user which should correspond to one of the
    # 'bn' items above (i.e a button if we had a gui).
    while(my $resp = <STDIN>)
    {
        chomp $resp;
        unless(exists($tmphsh{$resp}))
        {
            $self->TestOut->write_typedoutput( CTSDK_INFO, "'$resp' is not one of the options. Enter one of the following: ", join(", ", keys %tmphsh) . "." );
            next;
        }
        # write_typedoutput returns 1 if the report is not a failure, 0
        # otherwise
        return $self->TestOut->write_typedoutput( $tmphsh{$resp}->{msgtype}, "($resp) " . $tmphsh{$resp}->{message} );
    }
}

# Run a step within a test manually. We prompt the test engineer and receive
# feedback.
sub manualstep
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parseoject.
    return undef unless(ref($po));
    my $cmdsettings = $po->Settings;
    return 0 unless(ref($cmdsettings));
    my $lineno = $po->{homelineno};

    my $ps = $cmdsettings->GetSet("listitem_prompt");
    my $qs = $cmdsettings->GetSet("listitem_question");
    my $as = $cmdsettings->GetSet("manual_action");

    # For the tk prompter, we need a reference to an array of instructions.
    my $prompt = [];
    for my $el (@$ps) { push @$prompt, $el->CommandLine; }

    # And a reference to an array of questions to ask.
    my $question = [];
    for my $el (@$qs) { push @$question, $el->CommandLine; }

    # And an array of arrays which define buttons (which are the response)
    # and what should be returned if a given button is pressed.
    my $actions = [];
    for my $el (@$as)
    {
        my $cl = $el->CommandLine;
        next unless($cl =~ m/^\s*(warn|info|pass|fail)\s+(\S+)\s+(.*$)/i);
        my $pf = lc($1); # pass or fail.
        my $state = CTSDK_PASS if($pf eq "pass" );
           $state = CTSDK_FAIL if($pf eq "fail" );
           $state = CTSDK_INFO if($pf eq "info" );
           $state = CTSDK_WARNING if($pf eq "warn" );

        my $bn = $2;     # 'Button name'..
        my $msg = $3;     # Message to display.

        # If the button called '$bn' is pressed, we'll get back the array ref.
        my $arr = [ $bn, [$state, $msg] ];
        push @$actions, $arr;
    }
    push @$actions, [ "Restart whole test", ["RESTART", undef ]];
    my $title = "Test: " . $self->ParentTestHandler->Tdf . "(line $lineno)";
    my $md = ManualDialog->new(  $title,
                                 $prompt,
                                 $question,
                                 $actions );

    # Display the dialog..
    my $rc = $md->Display;

    # The returned value is a reference to an array containing first the
    # value (e.g CTSDK_FAIL) and second the message to display.
    if( $rc and ($rc->[0] ne "RESTART"))
    {
        return $self->TestOut->write_typedoutput( $rc->[0], $rc->[1] );
    }
    return $rc->[0] if($rc and ($rc->[0] eq "RESTART"));

    $self->TestOut->write_typedoutput( CTSDK_FAIL, "No returned value from manual dialog.");
    return 0;
}

#
# r u n c m d
#
# Run a system command. For example, you could delete a file then later check
# for a compilation failure due to the missing file. Or you could invoke some
# perl.
#
sub runcmd
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parseoject.
    return undef unless(ref($po));
    # First, work out what arguments we have.
    my $args = $po->{args};

    # Check if there is a '-nowait' option. This is necessary for cases
    # where we want to run a command, are not interested in any output
    # it may generate and allows the possibility of e.g running the
    # emulator which will continue to run after this runcmd has completed.
    if( $args =~ m/^-nowait\s/ )
    {
        $args =~ s/^-nowait\s+//;
	system($args);
	return 1;
    }

    # Get the settings object for this command. These settings were
    # created by the Parser from any block following the actual command.
    # These DO NOT persist between commands, they ARE NOT related to
    # the '$self->Settings' which are those settings which live for the
    # duration of a test definition file.
    my $cmdsettings = $po->Settings;

    # We want to run a dos command. We may be interested in the output
    # of that command. So a 'CheckOutput' block may have been present
    # in the original test case. The CheckOutput class looks for settings
    # which might have been created by the parser. The undef parameter is
    # unset because we want CheckOutput to spawn the process for us, if
    # we had done it we would have to pass in a pipe or other descriptor.
    return (Symbian::SDK::Validate::Runner::CheckOutput->new( $args, $self->TestOut, undef, $cmdsettings ));
}

#
# r u n p e r l
#
# Run some perl. Runs 'perl -I<location> whatever.pl <further args>.
#
sub runperl
{
    my $self = shift;
    return undef unless(ref($self));

    # Get the usual..
    my $po = shift;
    return undef unless(ref($po));
    my $cmdsettings = $po->Settings;
    my $args = $po->{args};
    return undef unless($args);

    # Get the directory where the test we're running lives. Assume the perl
    # script is in there..
    my $loc = File::Basename::dirname($self->ParentTestHandler->Tdf);
    $args =~ m/\s*(\S*)(.*$)/;
    my $plscript = $1;
    my $perlscript = "$loc/$plscript";
    my $remainder = $2;
    unless( -f $perlscript )
    {
        $self->TestOut->write_typedoutput(CTSDK_FAIL, "Cannot find perl script '$perlscript'");
        return 0;
    }
    # Record where the current directory is.
    my $homedir = getcwd();

    # Change directory to where the script is.
    chdir($loc);

    # Set up the command to run.
    my $todo = "perl $plscript $remainder";

    # Run the perl script.
    my $rc = Symbian::SDK::Validate::Runner::CheckOutput->new( $todo, $self->TestOut, undef, $cmdsettings );

    # Return to the original directory.
    chdir $homedir;
    return $rc;
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
# m y e x i s t s
#
# Verify that the specified directory or file exists. This is common code
# used by 'fileexists' and 'direxists'.
#
sub myexists
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parseoject.
    return undef unless(ref($po));
    my $ford = shift;                # File or directory? Not Prefect.
    return undef unless(($ford eq "f") or ($ford eq "d"));
    my $donesomething=0;
    my $ok=1;

    # What we use to check for things. Perhaps it would have been neater to
    # pass these in.
    sub checkfile{ return( -f shift); };
    sub checkdir{ return( -d shift); };
    my($word, $checker);
    if( $ford eq "f" )
    {
        $checker = \&checkfile;
        $word = "File";
    } elsif( $ford eq "d" )
    {
        $checker = \&checkdir;
        $word = "Directory";
    }

    # First, work out what arguments we have.
    my $args = $po->{args};
    my $lineno = $po->{homelineno};

    # Perhaps the user put more than one file as an inline argument.
    my @files = split /,/, $args;
    $donesomething = @files;
    for my $file (@files)
    {
        $file =~ s/\\/\//g;
        $file =~ s/\/\//\//g;
        if( &$checker($file) )
        {
            $self->{testout}->write_typedoutput(CTSDK_PASS, "$word '$file' exists (line $lineno)." );
        } else
        {
            $self->{testout}->write_typedoutput(CTSDK_FAIL, "$word '$file' does not exist (line $lineno)." );
            $ok = 0;
        }
    }

    # Even more files/dirs could have been specified in a sub-block..
    my $cmdsettings = $po->Settings;
    my $morefiles = $cmdsettings->GetSet("listitem");
    unless($donesomething or ref($morefiles))
    {
        $self->{testout}->write_typedoutput(CTSDK_FAIL, "command does not check for any files or directories (line $lineno)." );
        return 0;
    }
    return($ok) unless(ref($morefiles));

    #
    # Now, the following aren't just files, they're CommandElements, we have
    # to pull the line number and text (minus comments) information out..
    #
    for my $element (@$morefiles)
    {
        my $lineno = $element->Lineno;
        my $file = $element->CommandLine;  # Comments already stripped.
        if( &$checker($file) )
        {
            $self->{testout}->write_typedoutput(CTSDK_PASS, "$word '$file' exists (line $lineno)." );
        } else
        {
            $self->{testout}->write_typedoutput(CTSDK_FAIL, "$word '$file' does not exist (line $lineno)." );
            $ok = 0;
        }
    }
    return $ok;
}

1;
