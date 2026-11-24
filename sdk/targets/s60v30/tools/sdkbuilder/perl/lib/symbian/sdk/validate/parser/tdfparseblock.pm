#!perl -w
#
# T D F P a r s e B l o c k
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#
# A utility class used by TDFParser to take a TDFParser object (which
# represents a single command including any comments and other parts)
# and construct a tree structure representing any blocks within the
# command.
#
use strict;

package Symbian::SDK::Validate::Parser::TDFParseBlock;

sub new
{
	my $arg = shift;
	my $class = ref($arg) || $arg;
	my $elements = shift;

	return undef unless(ref($elements));

	my $self = { element => undef,
			     subblocks => undef,
				 level => undef,
				 firstline => undef,
				 lastline => undef,
			   };

	bless $self, $class;

	$self->ConstructBlock($elements);
	return $self;
}

# Create a block based on an array of elements.
sub ConstructBlock
{
    my $self = shift;
    return undef unless(ref($self));
    my $aref = shift;
    return undef unless(ref($aref));

    # What level are we, what command/comment/whatever?
	my $nextsubcmd = $self->NextSubcmd($aref);
	return undef unless(ref($nextsubcmd));
    $self->{level} = $nextsubcmd->Level;
	$self->{firstline} = $nextsubcmd->Lineno;
	$self->{lastline} = $self->{firstline};
	$self->{element} = $nextsubcmd;

	while( $nextsubcmd = $self->NextSubcmd($aref) )
	{
        unshift @$aref, $nextsubcmd;
    	if( $nextsubcmd->Level <= $self->{level} )
    	{
			# This could be wrong if someone has put more than one close
			# brace on a line.
			$self->{lastline} = $nextsubcmd->Lineno() - 1;
			# The next sub command is not a deeper level than the current one
			# so it isn't a subcommand of this subcommand.
    		return;
    	}
		# The next subcommand is deeper, so its part of the current command.
		# Put it in the blocks array.
    	my $pb = Symbian::SDK::Validate::Parser::TDFParseBlock->new( $aref );
		$self->{lastline} = $pb->{lastline};
    	push @{$self->{subblocks}}, $pb;
	}
}

# Search for the next subcommand in the input (which we discard as we go).
# Braces and comments are ignored.
sub NextSubcmd
{
	my $self = shift;
	my $aref = shift;
	return undef unless(ref($aref) and ref($self));
	
	while( my $element = shift @$aref )
	{
		next if( ($element->Type eq "\{") or ($element->Type eq "\}") or
                 ($element->Type eq "comment") );
		return $element;
	}
    return undef;
}

# Return an array of elements in this block and any of its sub-blocks.
sub Content
{
    my $self = shift;
	return undef unless(ref($self));

	my @stack;
	push @stack, $self->{element};
	return @stack unless(ref($self->{subblocks}));

	for my $pb (@{$self->{subblocks}})
	{
		push @stack, $pb->Content;
	}
	return @stack;
}

1;
