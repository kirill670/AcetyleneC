#!perl -w
#
# C o m m a n d E l e m e n t
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#
use strict;
package Symbian::SDK::Validate::Parser::CommandElement;

#
# A class to record information about a single line within a test definition
# file. The line could be a comment, a blank line, a command, anything.
# No handling is done with the settings, they're just stored, though there
# is the option to search and replace the args and commandline members
# and interpolate any environment variables on the same memebers.
#

sub new
{
    my $arg = shift;
    my $class = ref($arg) || $arg;
    my $text = shift;
    my $type = shift;
    my $lineno = shift;

    my $self = {
                    text => undef,        # Original line of text.
                    commandline => undef, # Same, with comments stripped.
                    type => undef,        # Some kind of type name, e.g comment
                    level => undef,       # Inside how many '{'s are we?
                    lineno => undef,      # Line number.
                    args => undef,        # Arguments.
               };

    bless $self, $class;

    $self->Text($text);
    $self->Type($type);
    $self->Lineno($lineno);

    return $self;
}

sub Text
{
    my $self = shift;
    return undef unless ref($self);
    my $text = shift;
    $self->{text} = $text if( defined($text) );
    return $self->{text};
}

sub CommandLine
{
    my $self = shift;
    return undef unless ref($self);
    my $text = shift;
    $self->{commandline} = $text if( defined($text) );
    return $self->{commandline};
}

sub Args
{
    my $self = shift;
    return undef unless ref($self);
    my $text = shift;
    $self->{args} = $text if( defined($text) );
    return $self->{args};
}

sub Type
{
    my $self = shift;
    return undef unless ref($self);
    my $type = shift;
    $self->{type} = $type if( defined($type) );
    return $self->{type};
}

sub Level
{
    my $self = shift;
    return undef unless ref($self);
    my $level = shift;
    $self->{level} = $level if( defined($level) );
	$self->{level} = 0 unless( $self->{level} );
    return $self->{level};
}

sub Lineno
{
    my $self = shift;
    return undef unless ref($self);
    my $lineno = shift;
    $self->{lineno} = $lineno if( defined($lineno) );
    return $self->{lineno};
}

# Check through the command replacing any references to environment
# variables with the value of the variable. Don't call this unless the
# command object has been set up.
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

# Check through the command replacing any references to settings
# with the value of the setting. Usually called with the 'Runner' object's
# settings object to get, for example, the location of an SDK.
sub InterpolateSettings
{
    my $self = shift;
    return undef unless(ref($self));
	my $settings = shift;

	while( defined($self->{commandline}) and $self->{commandline} =~ m/!!(.*?)!!/ )
	{
		my $settingname = $1;
		my $setval = $settings->GetSet($settingname);
		$setval = "" unless(defined($setval));
		$self->{commandline} =~ s/!!.*?!!/$setval/ ;
	}
	while( defined($self->{args}) and  $self->{args} =~ m/!!(.*?)!!/ )
	{
		my $settingname = $1;
		my $setval = $settings->GetSet($settingname);
		$self->{args} =~ s/!!.*?!!/$setval/ ;
	}
}

# Check through the command replacing occurences of the first arg with the
# second.
sub SearchAndReplace
{
    my $self = shift;
    return undef unless ref($self);
    my($search, $replace) = @_;
    return undef unless( defined($search) );
    $replace = "" unless( defined($replace) );

    $self->{commandline} =~ s!$search!$replace!gi 
	                                       if(defined($self->{commandline}));
#    $self->{text} =~ s/$search/$replace/gi; # Do we want to do the orig text?
    $self->{args} =~ s!$search!$replace!gi if(defined($self->{args}));

    return $self->{lineno};
}

1;
