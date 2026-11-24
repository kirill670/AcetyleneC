#!\bin\perl -w
# Copyright (c) 2003-2005 Symbian Software Ltd. All Rights Reserved.
#
# Symbian::Config::Basic

package Symbian::Config::Basic;

use strict;
use IO::File;
use Symbian::Logger::Singleton;

# Symbian::Config::Basic new(scalar aFilename)
# Object constructor
sub new($)
	{
	my $proto = shift;
	my ($aDefault, $aFilename) = @_;

	my $class = ref($proto) || $proto;

	my $self = { RELTOOLS_REQUIRED => ""};
	bless($self, $class);

	$self->{iDefault} = $aDefault;
	
	# Load in options
	if (!$self->Reload($aFilename))
		{
		die "Option file could not be loaded.\n";
		}
	
	return $self;
	}

# boolean Set(scalar aOptionName, scalar aValue)
sub Set($$)
	{
	my $self = shift;
	my ($aOptionName, $aValue) = @_;

	my $logger = new Symbian::Logger::Singleton();

	if (!defined($aOptionName))
		{
		$logger->Warning("Cannot set undefined option");
		
		return 0;
		}
		
	if (!defined($aValue))
		{
		$logger->Warning("Cannot set option '$aOptionName' to undefined value.");
		return 0;
		}
	
	if ((ref($aValue) ne "") && (ref($aValue) ne "ARRAY"))
		{
		$logger->Warning("Value of '$aOptionName' must be either a string or list.");
		return 0;
		}

	$self->{iOptions}->{lc($aOptionName)} = [$aOptionName, $aValue];
	return 1;
	}

# scalar Get(scalar aOptionName)
sub Get($)
	{
	my $self = shift;
	my ($aOptionName) = @_;

	if (defined($self->{iOptions}->{lc($aOptionName)}))
		{
		return ($self->{iOptions}->{lc($aOptionName)})->[1];
		}
	else
		{
		return undef;
		}
	}

# scalar GetSafe(scalar aOptionName)
# dies if option is unset
sub GetSafe($)
	{
	my $self = shift;
	my ($aOptionName) = @_;

	my $logger = new Symbian::Logger::Singleton();
	my $value = $self->Get($aOptionName);
	
	return $value if(defined($value));
	$logger->Die("Could not find '$aOptionName' item in configuration");
	}

# list GetNames()
#
# Returns list of directive names currently defined
sub GetNames()
	{
	my $self = shift;

	return keys(%{$self->{iOptions}});
	}

# boolean Reload(scalar aFilename)
sub Reload($)
	{
	my $self = shift;
	my ($aFilename) = @_;

	my $okay = 1;
	
	my $logger = new Symbian::Logger::Singleton();

	$self->{iOptions}={}; # Blank existing options

	if (defined ($self->{iDefault}) && (!$self->loadOver($self->{iDefault})))
		{
		$logger->Die("Couldn't load default config settings from ".$self->{iDefault});
		$okay = 0; # Most loggers won't get us this far
		}
	elsif (defined $aFilename)
		{
		$okay = $self->loadOver($aFilename);
		}
	
	return $okay;
	}

# private boolean loadOver(scalar aFilename)
#
# Loads config settings without first wiping the existing settings.
sub loadOver($)
	{
	my $self = shift;
	my ($aFilename) = @_;
	my $okay = 1;
	
	my $logger = new Symbian::Logger::Singleton();

	if (!open(FILE, $aFilename))
		{
		print "WARNING: Option file '$aFilename' could not be opened.";
		$okay = 0;
		}
	else
		{
		foreach my $line (<FILE>)
			{
			chomp ($line);

			# Remove comments
			$line =~ s/#.*$//;

			# Split on colon
			my $parms = $line;
			$parms =~ s/([^\\]):/$1\x08/g; # Turn unescaped colons into 0x08 chars
			$parms =~ s/\\:/:/g; # Unescape escaped colons
			my @parms = split(/\x08/,$parms); # Split on 0x08

			if (scalar(@parms) != 0)
				{
				if (scalar(@parms) == 2)
					{
					my $key = $parms[0];
					$key =~ s/^\s+//; # Remove preceding spaces
					$key =~ s/([^\\])\s$/$1/g; # Remove unescaped trailing spaces
					$key =~ s/\\(\s)/$1/g; # Unescape space characters

					my $value = $parms[1];
					if ($value =~ /\s*\[.*\]\s*$/)
						{
						# Value is a [list]

						# Remove square brackets
						$value =~ s/^\s*\[//;
						$value =~ s/\]\s*$//;

						# Split on comma
						$value =~ s/([^\\]),/$1\x08/g; # Turn unescaped commas into 0x08 chars
						$value =~ s/\\,/,/g; # Unescape escaped commas
						$value =~ s/\\\[/\[/g; # Unescape open square brackets
						my @values = split(/\x08/,$value); # Split on 0x08

						map(s/^\s+//, @values); # Remove preceding spaces
						map(s/([^\\])\s$/$1/g, @values); # Remove unescaped trailing spaces
						map(s/\\(\s)/$1/g, @values); # Unescape space characters

						$value = [@values];
						}
					else
						{
						# Value is a scalar

						$value =~ s/^\s+//; # Remove preceding spaces
						$value =~ s/([^\\])\s$/$1/g; # Remove unescaped trailing spaces
						$value =~ s/\\(\s)/$1/g; # Unescape space characters
						$value =~ s/\\\[/\[/g; # Unescape open square brackets
						}

					if (defined($self->Get($key)))
						{
						$logger->Warning("In file '$aFilename', Option '$key' is repeated");
						$okay = 0;
						}

					if (!($self->Set($key, $value)))
						{
						$okay = 0;
						}
					}
				else
					{
					$logger->Warning("In file '$aFilename', ".scalar(@parms)." parameters found on a line.\nOnly two parameters, colon separated, are supported.\nLine: '$line'");
					$okay = 0;
					}
				}
			}
		close(FILE);
		}

	return ($okay);
	}

# boolean Save(scalar aFilename)
sub Save($)
	{
	my $self = shift;
	my ($aFilename) = @_;
	my $okay = 1;

	my $logger = new Symbian::Logger::Singleton();
	
	if (!open(FILE, ">$aFilename"))
		{
		$logger->Warning("Could not open option file '$aFilename' to save to.");
		$okay = 0;
		}
	else
		{
		foreach my $pair (values(%{$self->{iOptions}}))
			{
			my $key = $pair->[0];
			my $value = $pair->[1];
			
			if (!defined($value))
				{
				$self->{iLOFGILE}->Error("Cannot write undefined value for key '$key' when saving options.");
				$okay = 0;
				}
			else
				{

				if (ref($value))
					{
					if (ref($value) ne "ARRAY")
						{
						$logger->Error("Cannot write ".ref($value)." for key '$key' when saving options.");
						$okay = 0;
						}
					else
						{
						# It's a list: [value,value,value] and escape any commas or opening spaces
						my @values = @{$value};
						map(s/^(\s)/\\$1/,@values);
						map(s/,/\\,/g,@values);
						$value = "[".join(",",@values)."]";
						}
					}
				else
					{
					# It's a scalar string
					# Escape opening space
					$key =~ s/^(\s)/\\$1/;
					# Escape square brackets;
					}
					
				# Escape colons
				$key =~ s/:/\\:/g;
				$value =~ s/:/\\:/g;
				
				print FILE $key.":".$value."\n";
				}
			}
		close (FILE)
		}
	return $okay;
	}

###########################################
# Utility functions
###########################################

# boolean CheckRelTools()

sub CheckRelTools()
	{
	# Search for reldata API
	my $found = 0;
	foreach my $path (split(/;/,$ENV{PATH}))
		{
		if (-e $path."\\reldata\.pm")
			{
			$found = 1;
			last;
			}
		}
	
	return $found
	}

# void RequireRelTools() - Requires RelData and IniData. Dies if tools can't be located, or die when being required.

sub RequireRelTools()
	{
	my $self = shift;

	if ($self->{RELTOOLS_REQUIRED} ne "required")
		{
		# Locate reldata API
		my $found = 0;
		foreach my $path (split(/;/,$ENV{PATH}))
			{
			if (-e $path."\\reldata\.pm")
				{
				push @INC, $path;
				$found = 1;
				last;
				}
			}

		if (!$found)
			{
			die "Couldn't find release tools in path";
			}

		# Require core modules
		require RelData;
		require IniData;
		$self->{RELTOOLS_REQUIRED}="required";
		}
	}

1;
