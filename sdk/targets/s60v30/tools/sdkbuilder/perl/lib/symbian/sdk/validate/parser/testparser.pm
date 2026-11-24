#!perl -w
#
# T e s t P a r s e r
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#
use strict;
package Symbian::SDK::Validate::Parser::TestParser;

use Symbian::SDK::Validate::Parser::CommandElement;
use Symbian::SDK::Validate::Logger::TestOutDefaults;
use Symbian::SDK::Validate::Utility::Settings;

#
# A base class to define the basics for parsers. To use this define a derived
# class which overrides the 'ProcessInputText' method. That's where the
# intelligence that knows about syntax lives.
#

sub new
{
    my $arg = shift;
    my $class = ref($arg) ? ref($arg) : $arg;

    # The remaining text - a reference to an array of lines.
    my $text = shift;

    # What line number are we at?
    my $lineno = shift;

    # List of recognized commands. (ref to array)
    my $commandlist = shift;

    # An object that can report or store errors etc.
    my $report = shift;

    my $self = {
                   elements => [],     # An array of CommandElement objects
                                       # each representing a single line.
                 baselineno => $lineno,# Line we start on. 
                 homelineno => undef,, # Where the actual commandline is.
                nextcommand => undef,  # Reference to next TestParser object.
                commandlist => $commandlist, # List of valid commands.
                    command => undef,  # What to run, no args.
                       args => undef,  # args.

                     report => $report,# An object that can report output.
                     extras => undef,  # An object holding additional info
                                       # following the command.
                   settings => undef,  # Somewhere to store information
                                       # about commands following parsing.
               };

    bless $self, $class;

    # Check we have the minimum required information.
    return undef unless ref($text);
    return undef unless ref($commandlist);

    # Copy the text input, because 'ProcessInputText' eats it.
    my @iptext = @$text;
    return undef unless($self->ProcessInputText(\@iptext));

    # Ok, that should have broken the input into chunks, but it won't have
    # bothered with blocks of extra options following steps to execute.
    return undef unless($self->ParseBlock);

    return $self;
}

#
# Override this function.
# Run through the input constructing a single parser object from the
# first command seen in the input until a single command is complete.
# Then create a new parser object with the remainder of the input and
# place a reference to it in $self->{nextcommand}, thus creating a linked
# list of commands.
#
# Returns non-zero on success, 0 otherwise. The constructor will give up in
# disgust if we do not return a non-zero value.
#
sub ProcessInputText
{
    my $self = shift;

    $self->Fail("TestParser: Attempt to use the 'ProcessInputText' in the 'TestParser' base class. This method must be overridden.\n");
    return 0;
}

# Override this method. This processes the input further after ProcessInputText
# has run, determining if any block of text beneath a command is ok, placing
# the information in the Settings object.
# e.g
# rundos echo fred
# {
#     CheckOutput
#     {
#         Pass
#         {
#             fred
#         }
#         Fail
#         {
#             sid
#         }
#     }
# }
#
# .. of course the exact syntax will depend on your ProcessInputText method in
# your derived class.

sub ParseBlock
{
    my $self = shift;

    # This isn't a failure. If this method is not overridden then no additional
    # information will be retrieved from the parsed input until the test is
    # run.
    # $self->Fail("TestParser: Attempt to use the 'ParseBlock' in the 'TestParser' base class. This method must be overridden.\n");
    return 1;
}

# Return the command that needs running sans arguments.
sub Command
{
    my $self = shift;
    return undef unless(ref($self) );
    return $self->{command};
}

# Return a reference to the list of elements making up this command.
sub Elements
{
    my $self = shift;
    return undef unless(ref($self) );
    return $self->{elements};
}

# Return an array of elements from one linenumber to another. Note we
# burrow into the other Parser objects that we are linked to - remember
# we are a linked list of commands, each Parser object only holds the
# information representing one command.
sub Content
{
    my $self = shift;
    return undef unless(ref($self));
    my($line1, $line2) = @_;
    $line1 = 1 unless($line1);
    $line2 = -1 unless($line2);
    my @stack;
    my $obj = $self;
    while( $obj )
    {
        my $elements = $obj->Elements;
        for my $el (@$elements)
        {
            my $lineno = $el->Lineno;
            if(($lineno >= $line1) and (($line2 == -1) or $lineno <= $line2))
            {
                push @stack, $el;
            }
        }
        $obj = $obj->{nextcommand};
    }
    return @stack;
}

# Check through the command replacing any references to environment
# variables with the value of the variable. Don't call this unless the
# command object has been set up.
# CommandElement has an identical method. Do we need this here?
sub InterpolateEnvironmentVariables
{
    my $self = shift;
    return undef unless(ref($self));

    for my $var (keys %ENV)
    {
        $self->SearchAndReplace( "\%$var\%", $ENV{$var} );
    }
    # Now replace any attempted mappings of unset environment variables
    # with nothing.
    $self->SearchAndReplace( "\%.*?\%", "" );
}

# Check through the command replacing any references to settings (passed in)
# with the value of the setting. The Settings object passed in usually belongs
# to the 'runner' object.
sub InterpolateSettings
{
    my $self = shift;
    return undef unless(ref($self));
    my $settings = shift;
    return undef unless(ref($settings));

    # Go through all of the elements making up this command replacing any
    # setting reference (!!settingname!!) with its value.
    my $els = $self->Elements;
    for my $el (@$els)
    {
        $el->InterpolateSettings($settings);
    }

    # Also check the 'args' member.
    while(defined($self->{args}) and $self->{args} =~ m/!!(.*?)!!/ )
    {
        my $setname = $1;
        my $setting = $settings->GetSet($setname);
        $setting = "" unless(defined($setting));
        $self->{args} =~ s/!!.*?!!/$setting/ ;
    }

}

# Check through the command replacing occurences of the first arg with the
# second. Don't call this unless the command object has been set up.
# The element array contains 'CommandElement' objects that know how to do
# search and replace on themselves.
sub SearchAndReplace
{
    my $self = shift;
    return undef unless(ref($self));
    my($search, $replace) = @_;

    my @arr;
    while( my $el = shift @{$self->{elements}} )
    {
        if( $el->Type eq "comment" )
        {
            push @arr, $el;
        } else
        {
            $el->SearchAndReplace($search, $replace);
            push @arr, $el;
        }
    }
    $self->{elements} = \@arr;

    # Nearly there...
    $self->{args} =~ s!$search!$replace!gi if(defined($self->{args}));
}

#
# Generate some kind of output. If the $self->{report} member is defined
# - which should be a reference to an object that handles output - then
# call that with the output. If not just print it. Input is assumed to be
# a list.
#
sub Fail
{
    my $self = shift;
    return undef unless(ref($self));

    if( ref($self->{report}) )
    {
        $self->{report}->write_typedoutput(CTSDK_FAIL, @_);
    } else
    {
        for(@_) { print STDERR "ERROR: (no TestOut object): $_"; }
    }
}
sub Warning
{
    my $self = shift;
    return undef unless(ref($self));

    if( ref($self->{report}) )
    {
        $self->{report}->write_typedoutput(CTSDK_WARNING, @_);
    } else
    {
        for(@_) { print STDERR "WARNING: (no TestOut object): $_"; }
    }
}

# Return the next line in the passed array of lines from the test file
# which is significant - i.e is not blank or is only a comment.
sub NextSignificantLine
{
    my $self = shift;
    return undef unless(ref($self));
    my @linearray = @_;

    for my $line (@linearray)
    {
        chomp($line);
        my $cline = $self->RemoveComments($line);
        return $line unless( $cline =~ m/^$/ );
    }
    return undef;
}

# Utility function to strip comments (defined as anything following a '#',
# plus leading and trailing white-space) from the line that is passed in.
# You may need to override this if your comments are different. I suppose
# the '#' comment char could be defined in a class member.
sub RemoveComments
{
    my $self = shift;
    return undef unless(ref($self));
    my $line = shift;
    $line =~ s/#.*$//;
    $line =~ s/^\s*//;
    $line =~ s/\s*$//;
    return $line;
}

# Read the input file creating new CommandElements and stacking them
# up as long as they are comments. Return when something that looks like
# a non-comment is encountered or the input is exhausted. Return the
# stack. You may need to override this if your parser is different enough.
sub StackComments
{
    my $self = shift;
    return undef unless(ref($self));
    my $lineno = shift;
    my @linearray = @_;
    my @commentstack;

    for my $line (@linearray)
    {
        chomp $line;
        my $cline = $self->RemoveComments($line);
        last unless( $cline =~ m/^$/ );

        my $cmd_element = Symbian::SDK::Validate::Parser::CommandElement->new;
        $cmd_element->Text($line);
        $cmd_element->Type("comment");
        $cmd_element->Lineno($lineno++);
        push @commentstack, $cmd_element;
    }
    return @commentstack;
}

sub Settings
{
   my $self = shift;
   return undef unless(ref($self));
   $self->{settings} = Symbian::SDK::Validate::Utility::Settings->new() unless(ref($self->{settings}));
   return($self->{settings});
}

1;
