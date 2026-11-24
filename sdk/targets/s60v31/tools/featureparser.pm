# featureparser.pm
#
# Copyright (c) 1997-2005 Symbian Software Ltd.  All rights reserved.
#

# This package contains routines to read the information from the Feature List XML file.
package featureparser;

require Exporter;
@ISA=qw(Exporter);
@EXPORT=qw(
	parseFeatureuidFile
	getFeatureInfo
	getFeatureUID
	ValidateUIDValue
	getDefaultIncludeInfo
	getDefaultExcludeInfo
	getDefaultIncludeCount
	getDefaultExcludeCount
	getDefaultTotalCount
	getRangeEntry
	getDefaultRanges
	getFeatures
);

use strict;

# Include the GenericParser to use API to read from XML file.
use GenericParser;

# filename, path and Root Element
my $file; 
my $root;

# Global hashmap for the list of feature uids provided in the feature list. For a given uid, the corresponding
# information of the features is stored.
my %featureHashMap = ();

# Global hashmap for the default ranges of feature ids that are either included or excluded on the device as default.
# Describes attributes for a block of features. The attributes for the range indicate the minimum uid in the range,
# the maximum uid in the range. Whether the features in this range are included or excluded from the ROM and if they
# are installable.
my @rangeList;

# Global hashmap for the list of feature names and the corresponding uid. This map is used to retrieve the feature uid
# when the uid value is provided.
my %featureNameUidMap =();

my $defaultIncludeRangeCount=0;
my $defaultExcludeRangeCount=0;

# Parse the featureuid XML file and generate the maps and counts
sub parseFeatureuidFile
{
	my $file = shift; # Get the featureuid XML filename
	my $returnBool = 0;

#	Parse the file and Get root Element
	$root = &GenericParser::getRootElement($file);

	if($root)
	{
		if(&createFeatureMap())
		{				
			if(&createRangeMap())
			{
				$returnBool = 1;
			}
		}
	}
	return $returnBool;							
}

#Returns the Hashmap containing the Featureuid as key and their Feature details in another hashmap as value pairs
sub createFeatureMap
{
# Get all <feature> Elements to @featureList
	my @featureList =  &GenericParser::getNodeFromTree($root, "features", "feature");

	foreach my $node (@featureList)
	{		
		# Define local variables to hold attribute names and values for each $node
		my $uid_value = &GenericParser::getAttrValue($node, "uid");

		if(ValidateUIDValue($uid_value))
		{
			$uid_value = ConvertHexToDecimal($uid_value);
		}
		else
		{
			return 0;
		}

		my $name_value = &GenericParser::getAttrValue($node, "name");
		#my $support_value = &GenericParser::getAttrValue($node, "support");
		my $install_value = &GenericParser::getAttrValue($node, "installable");
		if ($install_value eq undef) {
			$install_value = "false";
		}

		# Store all key=values to global %featureHashMap & %featureNameUidMap
		$featureNameUidMap{$name_value} = $uid_value;
		$featureHashMap{$uid_value}{"name"} = $name_value;
		#$featureHashMap{$uid_value}{"support"} = $support_value;
		$featureHashMap{$uid_value}{"installable"} = $install_value;
	}
	return 1;
}

#Returns the Hashmap containing the default feature range details(min,max,support,installable)
sub createRangeMap
{
# Can contain one or more <range> Elements
	my @rangesList =  &GenericParser::getNodeFromTree($root, "default", "range");
	my $defaultRangeCount = 0;						# Holds the count of ranges
	
	foreach my $node (@rangesList) 
	{
		my $min_value = &GenericParser::getAttrValue($node, "min");
		if(ValidateUIDValue($min_value))
		{
			$min_value = ConvertHexToDecimal($min_value);
		}
		else # The uid value is incorrect
		{
			return 0; 
		}

		my $max_value = &GenericParser::getAttrValue($node, "max");
		if(ValidateUIDValue($max_value))
		{
			$max_value = ConvertHexToDecimal($max_value);
		}
		else # The uid value is incorrect
		{
			return 0;
		}

# Check if the minimum uid is less than the maximum uid
		if($min_value > $max_value)
		{
			print "\n Error: In the Default Include feature ranges, the minimum uid, $min_value is greater than the maximum uid, $max_value\n";
			return 0;
		}

		my $support_value = &GenericParser::getAttrValue($node, "support");
		my $install_value = &GenericParser::getAttrValue($node, "installable");

		my %featlist = ();

		$featlist{"min"} = $min_value;
		$featlist{"max"} = $max_value;
		$featlist{"support"} = $support_value;
		$featlist{"installable"} = $install_value;

		if($support_value eq "include")
		{
			$defaultIncludeRangeCount++;
		}
		elsif ($support_value eq "exclude")
		{
			$defaultExcludeRangeCount++;
		}
		else
		{
			print "\n Warning: Attribute to specify whether the features in this range are included or excluded from the ROM is not set \n";
		}
		push @rangeList, \%featlist;
	}
	return 1;
}

# Input Parameter : HexaDecimal Value
# Return Decimal value for the given Hexadecimal number.
sub ConvertHexToDecimal
{
	my $val = shift;
	if(grep /^0x/i, $val)
	{
		# Input is Hexadecimal value, convert to Decimal
		return hex($val);	 
	}
	else
	{
		# Decimal value
		return $val;
	}
}

# Validate if the given UID value is a valid number (either decimal or hexadecimal number)
sub ValidateUIDValue
{
	my $fuid = shift;
# check to ensure that uid value contains only valid digits (decimal/hexadecimal)
	if($fuid =~ /^\d+$|^0[x][\da-f]+/i)	
	{
		return 1;
	}
	else
	{
		print "Error: Invalid UID value, $fuid\n";
		return 0;
	}
}

# Input Parameter : Feature Name
# Return the feature uid for the given feature name.
sub getFeatureUID
{
	my $feature = shift;
	$feature = lc($feature);
	if(exists $featureNameUidMap{$feature}){
		return $featureNameUidMap{$feature};
	}else{
		return undef;
	}
}

# Get the details of feature with given featureuid and other parameters
# This function only consider the feature UID only and that UID should be in decimal
sub getFeatureInfo() 
{
	my $uid = shift;
	if(exists $featureHashMap{$uid})
	{
		return \%{$featureHashMap{$uid}};
	}
	return undef;
	
}

# Get the default include ranges of min and max values in 2dimensional array
sub getDefaultIncludeInfo()
{
	my @result;	
	my %tempHash=();

	foreach my $range (@rangeList)
	{
		if(lc($range->{"support"}) eq "include" )
		{
			my $min_value=$range->{"min"};
			my $max_value=$range->{"max"};
			$tempHash{$min_value} = $max_value;
		}				
	}

	my $index = 0;
	my @sortedHash = sort keys %tempHash;

	foreach my $key (@sortedHash)
	{
		push @{$result[$index]},$key;
		push @{$result[$index]},$tempHash{$key};	
		$index++;
	}	
	return @result;
}

# Get the default exclude ranges of min and max values in 2dimensional array
sub getDefaultExcludeInfo()
{
	my @result;
	my %tempHash=();

	foreach my $range (@rangeList)
	{
		if(lc($range->{"support"}) eq "exclude" )
		{
			my $min_value=$range->{"min"};
			my $max_value=$range->{"max"};
			$tempHash{$min_value} = $max_value;
		}				
	}

	my $index = 0;
	my @sortedHash = sort {$a <=> $b}(keys %tempHash);
	foreach my $key (@sortedHash){
		push @{$result[$index]},$key;
		push @{$result[$index]},$tempHash{$key};
		$index++;
	}
	return @result;
}

# Get the count of total number of ranges that are either included or excluded on the device as default
sub getDefaultTotalCount()
{
	return ($defaultIncludeRangeCount+$defaultExcludeRangeCount);
}

# Get the count of total number of ranges that are included on the device as default
sub getDefaultIncludeCount()
{
	return $defaultIncludeRangeCount;
}

# Get the count of total number of ranges that are excluded from the device as default
sub getDefaultExcludeCount()
{
	return $defaultExcludeRangeCount;
}

# For a given uid value, this function checks if the given uid is within the default=present range.
sub getRangeEntry
{
	my $aUid = shift;
	my $length = &getDefaultTotalCount;
	my $pos = 0;
	my $rangeRef;

	foreach my $range (@rangeList)
	{
		if ( (lc($range->{"support"}) eq "include") and ($range->{"min"} <= $aUid) and ($range->{"max"} >= $aUid) )
		{
			return $range;
		}
	}
	return undef;
}

# Get the default ranges
sub getDefaultRanges
{
	return \@rangeList;
}

# Get the list of features
sub getFeatures($$)
{
	my ($includeFeatureRef, $excludeFeatureRef) = @_;
	my %FeatureMap = ();
	my @FeatList;
	my $featRef;
	my $uid;

	foreach my $feat (@$excludeFeatureRef)
	{
		$uid = $feat->{uid};

		$featRef = $FeatureMap{$uid};

		if($featRef->{exclude} == 1)
		{
#			Already added to the final feature list
			next;
		}
		else
		{
			$FeatureMap{$uid} = $feat;
			push @FeatList, $feat;
		}
	}

	foreach my $feat (@$includeFeatureRef)
	{
		$uid = $feat->{uid};

		$featRef = $FeatureMap{$uid};

		if( $featRef->{exclude} == 1 )
		{
			print "Error:The feature Uid $uid was added into the exclude as well as include list\n";
			next;
		}
		elsif($featRef->{include} == 1)
		{
#			Already added to the final feature list
			next;
		}
		else
		{
			$FeatureMap{$uid} = $feat;
			push @FeatList, $feat;
		}
	}

	return \@FeatList;
}

1;