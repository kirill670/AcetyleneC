# featurevariantmap.pm
#
# Copyright (c) 2007 Symbian Software Ltd.  All rights reserved.
#

use Digest::MD5;
use File::Basename;

package featurevariantmap;
our $verbose = 0;

# Usage:	featurevariantmap->Hash(\@sources, \%var)
#
# Generate a hash value from the source files for a target using the
# given feature variant data.
#
# \@sources	- list of source files (full path)
# \%var		- variant data (from featurevariantparser->GetVariant)
#
# returns the hash value, or "" if an error occurs.

sub Hash
{
	my $thisObj = shift;
	my $srcRef = shift;
	my $varRef = shift;

	return "" if (!$srcRef || !$varRef);
	return "" if (!$$varRef{'VALID'});

	# get the pre-processing options
	my $pre = $$varRef{'PREINCLUDE'};
	my $inc = $$varRef{'BUILD_INCLUDES'};
	my $mac = $$varRef{'MACROS'};

	my $options = "-undef -nostdinc -+";

	if ($pre)	# pre-include file
	{
		$options .= " -include \"$pre\"";
	}

	if ($inc)	# include directories
	{
		foreach (@$inc)
		{
			$options .= " -I \"$_\"";
		}
	}

	if ($mac)	# macro definitions
	{
		foreach (@$mac)
		{
			$options .= " -D$_";
		}
	}

	# pre-process the source files and digest the results
	my $digest = Digest::MD5->new;

	foreach my $src (@$srcRef)
	{
		my $options = "-I " . File::Basename::dirname($src) . " $options";

		print "cpp $options $src\n" if ($verbose);

		if (open(CPP, "cpp $options $src 2>&1 |"))
		{
			while (<CPP>)
			{
				print $_ if ($verbose && /No such file/);

				$digest->add($_) unless (/^#\s/ || /^\s*$/);
			}
			if (!close(CPP))
			{
				# this probably means that a rsg file was included
				# that hasn't been generated yet.
				print "Incomplete pre-process of $src\n" if ($verbose);
			}
		}
		else
		{
			print "ERROR: Could not pre-process $src\n";
			return "";
		}
	}

	return $digest->hexdigest;
}

# Usage:	featurevariantmap->Save("my.dll", "1234", "myvar", \@hints)
#
# Write a hash value for a target into the target.vmap file along
# with some optional hints data.
#
# "my.dll"	- the target (full path)
# "1234"	- the hash value (32 character hex number)
# "myvar"	- the feature variant name
# \@hints	- optional list of extra strings (eg. "FEATUREVARIANT")
#
# returns 0 if OK and non-zero if an error occurs.

sub Save
{
	my $thisObj = shift;
	my $binName = shift;
	my $keyValue = shift;
	my $varName = shift;
	my $hintRef = shift;

	# read the current data first if the .vmap file already exists
	my $vmapFile = "$binName.vmap";
	my @lines;
	if (open(VMAP, $vmapFile))
	{
		while (<VMAP>)
		{
			if (/^\w{32}\s+(\w+)\s*$/)
			{
				push(@lines, $_) unless (uc($1) eq uc($varName));
			}
		}
		close(VMAP);
	}

	# write the new data to the .vmap file
	if (!open(VMAP, ">$vmapFile"))
	{
		print "ERROR: Could not write VMAP to $vmapFile\n";
		return 1;
	}

	# put the hints at the beginning
	if ($hintRef)
	{
		foreach (@$hintRef)
		{
			print VMAP "$_\n";
		}
	}

	# then the "key var" pairs
	foreach (@lines)
	{
		print VMAP $_;
	}
	print VMAP "$keyValue $varName\n";

	close(VMAP);
	return 0;
}

# Usage:    featurevariantmap->Find("my.dll", "myvar")
#
# Look for a binary using its "final" name. We will use the feature
# variant map and the feature variant name to deduce the "variant"
# binary name and test for its existence.
#
# "my.dll"	- the final target (full path)
# "myvar"	- the feature variant name
#
# returns the file name if found, or "" otherwise.

sub Find
{
	my $thisObj = shift;
	my $binName = shift;
	my $varName = shift;

	# look for the vmap file
	my $vmapFile = "$binName.vmap";

	if (-e $vmapFile)
	{
		my $key = GetKeyFromVMAP($varName, $vmapFile);

		if ($key)
		{
			$binName =~ /^(.*)\.([^\.]*)$/;
			$binName = "$1.$key.$2";
		}
		else
		{
			print "ERROR: no key found for $varName in $vmapFile\n";
			return "";	# file not found
		}
	}

	# check that the actual binary exists
	if (-e $binName)
	{
		return $binName;
	}
	return "";	# file not found
}

# internal functions

sub GetKeyFromVMAP
{
	my $varName = shift;
	my $fileName = shift;

	if (!open(VMAP, $fileName))
	{
		print "ERROR: Could not read VMAP from $fileName\n";
		return "";
	}
	while (<VMAP>)
	{
		if (/(\w{32})\s+$varName\s*$/i)
		{
			close(VMAP);
			return $1;
		}
	}
	close(VMAP);
	return "";
}

1;
