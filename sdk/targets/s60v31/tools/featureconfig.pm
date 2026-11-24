# featureconfig.pm
#
# Copyright (c) 1997-2006 Symbian Software Ltd.  All rights reserved.
#

# This package contains routines to create the feature registry file.
package featureconfig;

#Include Module package
use FileHandle;
use WRITER;
use featureparser;

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	createConfig
);

use strict;

#Global variables
my $file_handle;
my $feature_count = 0;

# Input Parameter 1 : Feature Registry Filename, 
# Input Parameter 2 : The complete List of features which are either to be included or excluded.
# The complete list of features are determined from the list of features provided in the IBY files using
# FEATURE and EXCLUDE_FEATURE keywords.

sub createConfig
{
# Feature Registry file output file name
	my $configfile = shift;
# List of features to be included or excluded
	my $featurelist= shift;
	my %mapFeatures=();	

	open (CONFIG_FH, ">$configfile");
	binmode(CONFIG_FH);
	$file_handle = *CONFIG_FH;

	if(!defined $file_handle){
		print "\nError in creating the $configfile, check for the accessability of File / Drive\n";
		return 0;
	}

	foreach my $fidMain (@$featurelist) 
	{
		my $fid = $fidMain->{uid};
		if(!defined $fidMain->{uid})
		{
			print "Error:Feature $fidMain->{name} not found in feature list XML \n";
			next;
		}

		my $featInfoRef = &getFeatureInfo($fid);
#		Check if the feature is within the default=present range
		my $rangeRef = &getRangeEntry($fid);

# Check if the feature is found in the default ranges. If not found, add it to the Config Feature Entries.
		if( defined $rangeRef)
		{
#			If a feature is already found in the default=present ranges, ignore it
#			Otherwise, add it to the Config Feature Entries.
			if ($fidMain->{include} == 1)
			{
				next;
			}
		}

#		Initialise the status bit
		$fidMain->{status} = 0;

#		If the feature is not in the default range, then check:
#		If the individual feature is to be included in Rom, If so, set the 0th bit.
#		If a feature is explicitly to be excluded from ROM, then nothing is to be done, 
#		since the 0th bit is already set to zero.
		if($fidMain->{include} == 1)
		{
			$fidMain->{status} |= 1;
		}

#		Check if the individual feature is installable, If so, set the 1st bit.
		if($featInfoRef->{installable} eq "true")
		{
			$fidMain->{status} |= 2;
		}
		
		$mapFeatures{$fid} = $fidMain->{status};
	}
	
	$feature_count = scalar (keys %mapFeatures);
	&writeHeader();
	foreach my $featureId (sort {$a <=> $b} (keys %mapFeatures))
	{
		write2File($featureId);
		write2File($mapFeatures{$featureId});
	}

	&writeDefault();
	close $file_handle;
	return 1;
}

# This function writes the bytes to the binary file. 
sub write2File
{
	my $bytes = shift;
	&WRITER::write32($file_handle, $bytes);
}

# Feature registry Header
sub writeHeader
{
	write2File(0x74616566);
	write2File(0);
	write2File($feature_count);
	write2File(&getDefaultIncludeCount());
}

# Write the default=present featureUID ranges (min,max) to the config file.
sub writeDefault
{
	my @defaultFeatures = &getDefaultIncludeInfo();
	for my $i ( 0 .. $#defaultFeatures )
	{
		my $minuid = $defaultFeatures[$i][0];
		my $maxuid = $defaultFeatures[$i][1];		
		write2File($minuid);
		write2File($maxuid);
	}
}

1;
