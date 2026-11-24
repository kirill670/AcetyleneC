#!perl -w
#
# C o m m a n d I m p l e m e n t a t i o n
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#
use strict;
package Symbian::SDK::Validate::Runner::CommandImplementation;

use Symbian::SDK::Validate::Utility::Settings;
use Symbian::SDK::Validate::Logger::TestOutDefaults;
use Cwd;

#
# This is a base class, not to be used directly. A sub-class will define
# all of the functions necessary to execute all of the commands defined in
# the 'commandshash' member hash. The key is the command name, the content
# a reference to a function that knows what to do about it.
#

sub new
{
    my $arg = shift;
    my $class = ref($arg) ? ref($arg) : $arg;

    # Assume we are provided with a test output object. Right now we
    # aren't using the facility to setup our own types (Pass, Fail etc) in
    # the output, there should be the possibility of doing that. The overriding
    # class will have to do it.
    my $testout = shift;
    my $testhandler = shift;

    my $self = {
                   commandshash => undef,   # Hash of commands & functions.
                   settings => undef,
                   dummyrun => undef,
                   testout => $testout,     # Test output object
                   testhandler => $testhandler, # Handler that owns this.
               };

    bless $self, $class;

    $self->SetupCommandsHash;                 # This MUST be overridden.
    $self->Settings->GetSet("homedir", getcwd());;
    return undef unless( ref($self->{commandshash}));

    return $self;
}

sub SetupCommandsHash
{
    my $self = shift;
    return undef unless(ref($self));
    print STDERR "Illegal call to CommandImplementation SetupCommandsHash().\n";
    print STDERR " This method should be overridden.\n";
}

#
# Execute all of the test. Note that you might want to override this if, for
# example, you have the possibility of skipping steps or perhaps going back
# a few steps or something. This implementation just goes through running the
# commands in sequence.
#
sub ExecuteTest
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;
    return undef unless(ref($po));

    while(defined($po))
    {
        # Execute it, passing the parsed information from the test definition
        # file.
        $self->Gateway($po);

        # Lose the executed command to free up memory.
        my $lo = $po;
        $po = $po->{nextcommand};
        undef($lo);
    }

    # Undef any snapshots to lose circular references in the logger object.
    undef($self->TestOut->{snapshots});
}

sub Settings
{
    my $self = shift;
    my $settings = shift;
    $self->{settings} = $settings if(defined($settings));
    $self->{settings} = Symbian::SDK::Validate::Utility::Settings->new() unless(ref($self->{settings}));
    return $self->{settings};
}

sub ListAvailableCommands
{
    my $self = shift;
    return undef unless(ref($self));
    return undef unless( defined($self->{commandshash}) );
    return keys %{$self->{commandshash}};
}

# Return a code reference to the method that is required to handle command.
sub GetCodeRef
{
    my $self = shift;
    return undef unless(ref($self));
    return undef unless( defined($self->{commandshash}) );
    my $commandname = lc(shift);
    return undef unless( defined($commandname) );
    return $self->{commandshash}->{$commandname};
}

sub Report
{
    my $self=shift;
    return undef unless ref($self);
    if( ref($self->{testout}) )
    {
        $self->{testout}->Report(@_);
        return;
    }
    for(@_)
    {
        print "CommandImplementation: $_";
    }
    return;
}

sub DESTROY
{
    my $self = shift;
    undef $self->{commandshash};
    undef $self->{testout};
    undef $self->{testhandler};
}

#
# G a t e w a y
# 
# This method is called from within the TestHandler class to execute a
# certain method for a command in a test definition.
# You probably ought to override this.
# 
sub Gateway
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parse object.
    $po->InterpolateEnvironmentVariables;
    $po->InterpolateSettings($self->Settings);
    return undef unless(ref($po));
    my $settings = shift;            # Settings object.
    my $cmd = lc($po->Command);

    my $coderef = $self->{commandshash}->{$cmd};
    $coderef = \&Unknown unless(ref($coderef));

    # Go and execute the operation, unless dummyrun is set. Note that depending
    # on your available commands you might have to change this, if for example
    # your tests start up other tests.
       $self->$coderef($po, $settings) 
        if(defined($coderef) and !($self->DummyRun));
    return 1;
}

# An object that can record and display output.
# Should it create its own? It really ought to be there already.
sub TestOut
{
    my $self = shift;
    return undef unless(ref($self));
    my $to = shift;
    $self->{testout} = $to if defined($to);
    if( !defined($self->{testout}) )
    {
        $self->{testout} = Symbian::SDK::Validate::Logger::TestOut->new("_op.txt", "verbose");
    }
    return $self->{testout};
}


# A flag that tells us to not really execute tests. This is useful if a test
# loads up other tests when executed which we might not know had problems
# until execution potentially hours after the test began.
# Note it can have any value - this can be useful if you want to execute
# e.g tests that load other tests and you want to check their syntax first.
sub DummyRun
{
    my $self = shift;
    return undef unless(ref($self));
    my $dm = shift;
    $self->{dummyrun} = $dm if(defined($dm));
    return $self->{dummyrun};
}

#
# Return the test handler object passed in when this object was created.
# Should be the handler that created this object. This is useful for tests
# which need to access information such as where test definitions live when
# running batches.
# This can be problematical in object destruction because we have a reference
# to the object that created this object. This is circular, so this
# class member should be undef'd when the file has completed execution.
#
sub ParentTestHandler
{
    my $self = shift;
    return undef unless(ref($self));
    return $self->{testhandler};
}

#
# Display the command (comments etc all included). If 'testout' is not
# defined write to stdout.
#
sub DisplayCommand
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                      # Parse object.
    return undef unless(ref($po));

    if(ref($self->TestOut))
    {
        for my $el (@{$po->Elements})
        {
            $self->TestOut->Report($el->Text);
        }
    }
    else
    {
        for my $el (@{$po->Elements})
        {
            print STDOUT $el->Text, "\n";
        }
    }
    return 1;
}

#
# U n k n o w n
# 
# This gets called when an unknown command was found in the input.
#
sub Unknown
{
    my $self = shift;
    return undef unless(ref($self));
    my $po = shift;                  # Parseoject.
    my $lineno = "(line " . $po->{homelineno} . ")";
    return undef unless(ref($po));
    $self->{testout}->write_typedoutput( CTSDK_FAIL, "Unknown command '" . $po->{command} . "' $lineno" );
    return 1;
}


1;
