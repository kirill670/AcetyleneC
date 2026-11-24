#!perl -w
#
# T D F P a r s e r 
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#
use strict;
package Symbian::SDK::Validate::Parser::TDFParser;
use Symbian::SDK::Validate::Parser::TDFParseBlock;

use base ("Symbian::SDK::Validate::Parser::TestParser");

#
# A class to read the SDK test definition files.
# Format is
#
# # Comment
# knowncommand <options>   # Comment
#
# Alternatively, a block maybe defined with braces WHICH MUST MATCH PROPERLY.
#
# knowncommand <options> {  # Comment
#     CommandBitsAndPieces
#     {                     # Comment
#         Stuff
#         {                 # Comment
#         }
#         More Stuff
#         {
#         }
#     }
# }
#
#
# Open braces may be end of line (as above, yuk!), or on their own.
# Open and close braces created their own 'CommandElement' object so
# a single line could end up creating multiple 'CommandElement' objects.
#
# Returns a TDFParser object which is the first command in your test
# definition file that need to be executed, which contains within itself
# a pointer to the next (i.e we return a linked list).
#
# Each command could consist of more that one line. Every line is stored
# within one or another command as a 'CommandElement', whether the line is
# an actual command, a comment or part of a command (known as a 'commandpart').
#

#
# Run through the input constructing a single TDFParser object from the
# first command seen in the input (which will include comments etc, i.e
# probably multiple lines) until the command is complete. For multi-line
# commands this is when all of the braces have matched. Then create a new
# TDFParser object with the remainder of the input and place a reference
# to it in $self->{nextcommand}, thus creating a linked list of commands.
#
# Returns non-zero on success, 0 otherwise. The constructor will give up in
# disgust if we do not return a non-zero value.
#
sub ProcessInputText
{
    my $self = shift;
    my $intext = shift;  # Reference to an array of input text.
    return 0 unless( ref($self) and ref($intext) );

    my $lineno = $self->{baselineno};
    unless($lineno >= 1)
    {
        $lineno = 1;
        $self->{baselineno} = 1;
    }

    # Store any leading comments before..
    my @commentstack = $self->StackComments($lineno, @$intext);
    # .. the next significant line.
    my $nsl = $self->NextSignificantLine(@$intext);
    $lineno += scalar(@commentstack);
    unless($nsl)
    {
        push @{$self->{elements}}, @commentstack; # No significant line
        return 1;                                 # remains.
    }

    # It's not a comment, so is it a command? Check through our list of
    # valid commands. A command must start in the first column and
    # must be followed by an end of line or space character.
    my $cmd_element = Symbian::SDK::Validate::Parser::CommandElement->new;
    my $gotcommand;
    my $cmdi;
    for my $cmd (@{$self->{commandlist}})
    {
        if( $nsl =~ m/^$cmd($|\s)/i )
        {
            $gotcommand = $nsl;
            $cmdi = $cmd;
            last;
        }
    }

    # Look for the case where someone has stuck a brace on the
    # end of a command.
    # Non comment-or-brace, open brace, non-comment, comment.
    my $commandtail;
    if( $nsl =~ m/^([^\{\}#]*)(\{)([^#]*)((#.*$)|$)/ )
    {
        my($lhs, $brace, $rhs, $comment) = ($1, $2, $3, $4);
        $gotcommand = $lhs;

        # Record the remainder of the command with braces.
        $commandtail = $brace . $rhs . $comment;
    }

    unless( $cmdi )  # Didn't we find our command?
    {
        # We no longer drop out on this failure, we just mark it as a 
        # bad command.
        $cmd_element->Text($nsl);
        $cmd_element->CommandLine($self->RemoveComments($nsl));
        $self->{command} = $self->RemoveComments($nsl); # With args.
        $cmd_element->Type("unknown");
        $self->Fail("TDFParser: Illegal line '$nsl' (line $lineno).\n");
#        return 0;
    }
	else
	{
        # Set up the element information for this line.
        $cmd_element->Text($gotcommand);
        $cmd_element->CommandLine($self->RemoveComments($gotcommand));
        $self->{command} = $self->RemoveComments($gotcommand); # With args.
        $cmd_element->Type("command");
#        $self->{command} = $cmdi;      # No args.
	}
    $cmd_element->Lineno($lineno);
    $self->{homelineno} = $lineno++;

    # Record what to execute. It is possible that cmdi and the command member
	# may be uninitialized (if this is an unrecognized command) hence the
	# multiple ands. This prevents perl warnings.
    $self->{args} = "";
    if( $self->{command} and $cmdi and $self->{command} =~ m/^$cmdi\s+(.*)/i )
    {
		$self->{command} = $cmdi;
        $self->{args} = $1;
    }

    # Store the leading comments and command in the elements member.
    # Remove the corresponding lines from the incoming array.
    push @{$self->{elements}}, @commentstack;
    push @{$self->{elements}}, $cmd_element;
    @$intext = splice( @$intext, scalar(@commentstack) + 1);

    # Is there a open brace potentially followed by other bits?
    if( $commandtail )
    {
        unshift @{$intext}, $commandtail;  # Braces to deal with.
        $lineno--;
    }

    # If we haven't found an open brace on the end of our command, see if
    # the next significant line has one. If this is the last significant
	# line then nsl will come back undefined, hence the check in the unless
	# to prevent perl warnings.
    $nsl = $self->NextSignificantLine(@$intext);
    unless( $nsl and $nsl =~ m/^\s*\{/ )
    {
        # No open brace. It must be another command.
        undef($self->{nextcommand});
        if( scalar(@$intext) ) # If any lines remain.
        {
            $self->{nextcommand} = Symbian::SDK::Validate::Parser::TDFParser->new($intext, $lineno, $self->{commandlist}, $self->{report});
            return (ref($self->{nextcommand}));
        }
        return 1;
    }

    # Either we've already hit an open brace on the end of our command (which
    # will now have been stuck back on the pile) or else the next line
    # definitely starts with an open brace. Keep reading until enough close
    # braces have been seen. Most of this messing about deals with the
    # possibility of more than one brace on a line interspersed with
    # command parts.
    my $openbrace = 0;
    while( scalar(@$intext) )
    {
        my @commentstack = $self->StackComments($lineno, @$intext);
        push @{$self->{elements}}, @commentstack;
        $lineno += scalar(@commentstack);
        @$intext = splice( @$intext, scalar(@commentstack));
        my $nsl = $self->NextSignificantLine(@$intext);
        my $pad;
        while( $nsl )
        {
            # Look for something followed by an open or close brace followed
            # by non-comments followed by comments followed by end of line.
            # The 'pad' stuff tries to add the right number of spaces to
            # a given command to maintain its indent on output.
            $nsl =~ m/^([^\{\}#]*)(\{|\})?([^#]*)((#.*$)|$)/ ;
            my($lhs, $brace, $rhs, $comment) = ($1, $2, $3, $4);

            if($lhs !~ m/^\s*$/)
            {
                 my $cmd_element = Symbian::SDK::Validate::Parser::CommandElement->new;
				 # The comment bit is a bit naughty, we could end up with
				 # the same comment repeated..
                 $cmd_element->Text($pad . $lhs . "  $comment");
                 $cmd_element->CommandLine($self->RemoveComments($lhs));
                 $cmd_element->Type("commandpart");
                 $cmd_element->Level($openbrace);
                 $cmd_element->Lineno($lineno);
                 push @{$self->{elements}}, $cmd_element;
            }
            $pad .= ( " " x length($lhs)); # Don't worry about tabs right now.
            if($brace)
            {
                 my $cmd_element = Symbian::SDK::Validate::Parser::CommandElement->new;
                 $cmd_element->Text($pad . $brace . "  $comment");
                 $cmd_element->CommandLine($brace);
                 $cmd_element->Type($brace);
                 $cmd_element->Lineno($lineno);
                 # Note the level of a brace is the level before it changes it.
                 $cmd_element->Level($openbrace);
                 push @{$self->{elements}}, $cmd_element;
                 $pad .= " ";
            }
			# Keep track of the brace level.
            $openbrace++ if($brace and $brace eq "\{");
            $openbrace-- if($brace and $brace eq "\}");
            $nsl = $rhs;
            last if($openbrace == 0);
        }
        @$intext = splice( @$intext, 1 );
        if( $nsl )  # Text remains after we closed all the '}'s
        {
             $self->Warning("TDFParser: Text '$nsl' following '}' on line " .  $lineno . ". Too many '}'s?\n");
             unshift @{$intext}, $nsl;  # Store any remaining text.
        }
        else   # No text remains. Go onto the next line.
        {
            $lineno++;
        }
        last unless($openbrace);
    }

    # Did we run out of input before the braces were resolved?
    if($openbrace)
    {
        $self->Fail("TDFParser: Insufficient close braces before EOF.\n");
        # Should
        return 1;
    }

    # We've detected the last matching close brace, so we're done with this
    # command. There might be more input though..
    undef($self->{nextcommand});
    if( scalar(@$intext) ) # If any lines remain.
    {
        $self->{nextcommand} = Symbian::SDK::Validate::Parser::TDFParser->new($intext, $lineno, $self->{commandlist}, $self->{report});
        return(ref($self->{nextcommand}));
    }
    # No file contents remain. That's ok.
    return 1;

}

# The remaining code is about parsing block of extra options beneath the main
# command.

# Should be in a derived class?

# This function parses a block following a command. For example...
#
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
# The information held in the braces is assembled into a 'TDFParseBlock'
# object, which we check for correctness.
#
# Remember, we are working on ONE command, but with a block of stuff
# following it.
#
sub ParseBlock
{
    my $self = shift;
    return undef unless(ref($self));

    # Look for a 'level 1' command part that isn't a comment or a brace.
    # Level 1 means within one layer of braces.
    # Make a copy of the array of elements for this command.
    my @elcopy = @{$self->Elements};

    # Break the array of elements into blocks. If none exist, that's fine,
    # we give up returning an ok status.
    my $block = Symbian::SDK::Validate::Parser::TDFParseBlock->new(\@elcopy);
       return 1 unless( ref($block->{subblocks}) );
    $self->{extras} = $block->{subblocks};

    # Our command can have at most one block. Get it if it's there.
    # If you were to check $block->{element}->Text at this point, it
    # would contain something like 'rundos echo hello' - it is a base
    # level command. We need to drill one level down.
    my @arr1 = @{$self->{extras}};

    # Go through the 'first level' subcommands..
    for my $subcmd (@arr1)
    {
        my $element = $subcmd->{element};
		next unless($element->Type() eq "commandpart");
		next unless(defined($element->CommandLine));
        $element->CommandLine =~ m/(\S*)/;
        my $name = $1;
        #
        # Does it match anything we've heard of? If not discard the whole
        # block, it is likely a spelling error or something.
        # It should be something like 'CheckOutput'.
        #
        my $coderef = $self->SubcmdToCoderef($name);
        unless($coderef)
        {
            my $firstline = $subcmd->{firstline};
            my $lastline = $subcmd->{lastline};

            # Get the full content between the relevant lines. We can't
            # get this from $subcmd because that has braces and comments
            # stripped.
            my @content = $self->Content($firstline, $lastline);
            my @discardedlines;
            for(@content) { push @discardedlines, $_->Text; };
            $self->Fail("Unknown subcommand '$name'. The following lines between line $firstline and $lastline have been discarded.", @discardedlines );
            next;
        }
        #
        # Call the function that knows what to expect in sub-blocks of this
        # internal command.
        # 
        $self->$coderef($subcmd);
    }
    return 1;
}


#
# This method is just a hash with a bunch of methods defined which
# know what to do about certain subcommands. The 'ParseBlock' method
# above uses this to decide where to send the TDFParseBlock object
# ($self->{extras}) to verify it isn't rubbish.
#
sub SubcmdToCoderef
{
    my $self = shift;
    return undef unless(ref($self));
    my $subcmd = lc(shift);

    my $subcommands = { "checkoutput" => \&CheckOutput,
                        "definelist" => \&DefineList,

                        "prompt" =>   \&DefineList,
                        "question" => \&DefineList,
                        "response" => \&Response,

                      };

    return $subcommands->{$subcmd};
}

#
# Check the syntax of a 'CheckOutput' sub-block within the current command.
# Perhaps we should check if this is within an appropriate command to be
# checking for output?
# Records information in the Settings object that the runner object can find
# later.
#
sub CheckOutput
{
    my $self = shift;
    return undef unless(ref($self));
    my $sc = shift;
    return undef unless(ref($sc));
    my $firstline = $sc->{firstline};
    my $lastline = $sc->{lastline};

    # This has already been checked. It is CheckOutput.
    my $command = $sc->{element}->CommandLine;

    # For checking of output we must have at least one sub-block.
    my $blocks = $sc->{subblocks};
    unless( ref($blocks) and scalar(@$blocks) )
    {
        my $lineno = $sc->{element}->Lineno;
        $self->Fail("No block following subcommand '$command' (Line $lineno)");
        return;
    }
    my $pfo=0;
    for my $block (@$blocks)
    {
        my $el = $block->{element}; # Object holding info about this line.
        my $cl = $el->CommandLine;  # e.g 'Pass'
		next unless(defined($cl));
        my $lineno = $block->{firstline};

        unless( $cl =~ m/(^pass$|^fail$|^ordered$)/i )
        {
            $self->Fail("Illegal block '$cl' in CheckOutput block (line $lineno)");
        }
        else
        {
            my $type = lc($1);
            my $type2 = "checkoutput_" . lc($1);
            $pfo++; # Suppress the 'no pass/fail/ordered' error.
            my $settings = $self->Settings;
            my $pfoblock = $block->{subblocks};
            unless(ref($pfoblock))
            {
                $self->Fail("No sub-block in $type block. (line " . $block->{firstline} . ")");
                next;
            }
            

            # Get the 'checkoutput_pass' (or whatever) stack from our settings
            # object.
            my $stack = $settings->GetSet($type2);
            $stack = [] unless(defined($stack));

            # Get the (un)expected lines from the pass fail or ordered block.
            # We store the whole element because we're likely to want to
            # know things like it's line number and so on.
            for my $exp (@$pfoblock)
            {
                my $el = $exp->{element};
                push @$stack, $el;
            }

            $settings->GetSet($type2, $stack);

        }
    }
    $self->Fail("No 'Pass', 'FAIL', or 'Ordered' blocks in CheckOutput block (between lines $firstline and $lastline)") unless($pfo);
    return 1;
}

#
# Check the syntax of a 'DefineList' sub-block within the current command.
# Perhaps we should check if this is within an appropriate command to be
# defining a list.
# Records information in the Settings object that the runner object can find
# later.
#
sub DefineList
{
    my $self = shift;
    return undef unless(ref($self));
    my $sc = shift;
    return undef unless(ref($sc));
    my $firstline = $sc->{firstline};
    my $lastline = $sc->{lastline};

    # This has already been checked. It is 'DefineList' or 'Prompt',
	# 'Question', etc. Note we change the 'listitem' settings key if
	# we aren't 'DefineList'.
    my $command = $sc->{element}->CommandLine;
	my $listname = "listitem";
	unless($command =~ m/^\s*(definelist).*$/i )
	{
		$command =~ m/^\s*(\S*)/;
	    $listname .= "_" . lc($1) if($1);
	}

    # For checking of output we must have at least one sub-block.
    my $blocks = $sc->{subblocks};
    unless( ref($blocks) and scalar(@$blocks) )
    {
        $self->Fail("No lines detected following subcommand '$command'.");
        return;
    }

    my $settings = $self->Settings;
    # Get the 'listitem' stack from our settings object.
    my $stack = $settings->GetSet($listname);
    $stack = [] unless(defined($stack));
    for my $block (@$blocks)
    {
        my $el = $block->{element}; # Object holding info about this line.
        push @$stack, $el;
    }
    $settings->GetSet($listname, $stack);
    return 1;
}

#
# Check the syntax of a 'Response' sub-block within the current command,
# which is theoretically 'ManualStep', though we don't enforce that.
# Records information in the Settings object that the runner object can find
# later.
#
sub Response
{
    my $self = shift;
    return undef unless(ref($self));
    my $sc = shift;
	return undef unless(ref($sc));
    my $command = $sc->{element}->CommandLine;

    # For checking of output we must have at least one sub-block.
    my $blocks = $sc->{subblocks};
    unless( ref($blocks) and scalar(@$blocks) )
    {
        $self->Fail("No lines detected following subcommand '$command'.");
        return;
    }

    # Get the 'manual_action' item from our settings object.
    my $settings = $self->Settings;
    my $stack = $settings->GetSet("manual_action");
    $stack = [] unless(defined($stack));
    for my $block (@$blocks)
    {
        my $el = $block->{element}; # Object holding info about this line.
		my $cl = $el->CommandLine;
        my $lineno = $sc->{element}->Lineno;
		unless( $cl =~ m/^(warn|info|pass|fail)\s/i )
		{
            $self->Fail("Unrecognized action name '$cl' in ManualStep/Response sub-block. (Line $lineno)");
			next;
		}
        push @$stack, $el;
    }
    $settings->GetSet("manual_action", $stack);
    return 1;
}
1;
