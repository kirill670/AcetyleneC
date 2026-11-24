#!perl
#
# ECL.pm
#
# Copyright (c) 2004 Symbian Software Ltd. All rights reserved.
#
use FindBin;
use lib $FindBin::Bin;

package ECL;

use strict;
use SymBin;
use CapToolsUtils;

#-------------------------------------------------------------------------------------------------
# Subroutine:   new
# Purpose:      Constructor
# Input:        An 'expected capability list' file name
# Output:       A reference to itself
#-------------------------------------------------------------------------------------------------
sub new 
{
    my $lPackage = shift;
    my $self = {};              # Create reference to object
    bless $self,  $lPackage;    # Associate a reference with class name
    $self->{iECLFile}        = $_[0];
    @{$self->{iBinaries}} = ();
    return $self;
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Process
# Purpose:      Processes the ECL and extracts binaries and their capabilities 
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub Process
{
    my $self = shift;
    
    open (ECL_FH, $self->{iECLFile}) or die "Warning: Couldn't open \"$self->{iECLFile}\": $!\n";
    
    my $beginFlag;
    my $lineCount = 0;
    while (my $line = <ECL_FH>)
    {
        ++$lineCount;
        chomp $line;
        
        # Ignore everything before the [MATCHES] tag:
        if ($line =~ /^\s*\[MATCHES\]\s*$/)
        {
            $beginFlag = 1;
        }
        next unless defined $beginFlag;
        
        # end tags:
        last if $line =~ /^\s*$/;               # a blank line signals the end of the section
        if ($line =~ /^\s*\[(\w+\])\s*$/)       # a [ also signals the end of the section, search for [MATCHES] tag again
        {
            $beginFlag = 0 if $1 ne "MATCHES";
            next;
        }
        
        # read in individual lines listing binaries and their expected capabilities:
        if ($line =~ /^(\w+\.\w+)\s+(.*)$/)
        {
            my $cap = $2;
            
            # If no capability is defined - raise an error
            if ($cap eq "")
            {
                warn " ERROR(".CapToolsUtils::KCapToolsInvalidECL.") - InvalidECL: Incorrect Expected Capability List format (Line $lineCount).\n";
                exit CapToolsUtils::KCapToolsInvalidECL;
            }
            
            # Create a binary and add to the list
            my $bin = new SymBin($1);
            
            #$cap =~ s/\s//g;    # remove spaces (e.g., in case of a 64 bit number)
            
            # check whether the capability is a valid hexadecimal number:
            if (!CapToolsUtils::IsHex($cap))
            {
                warn " ERROR(".CapToolsUtils::KCapToolsInvalidECL.") - InvalidECL: Incorrect Expected Capability List format (Line $lineCount).\n";
                exit CapToolsUtils::KCapToolsInvalidECL;
            }
            
            $bin->Capabilities(new SymCapSet($cap));
            push @{$self->{iBinaries}}, $bin;
        }
    }
    close(ECL_FH);
    
    # Create a hash of binaries by names to speed up lookups:
    %{$self->{iBinaryHashTable}} = ();
    foreach my $bin (@{$self->{iBinaries}})
    {
        $self->{iBinaryHashTable}->{lc $bin->Name()} = $bin;
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   DEBUG_Print
# Purpose:      Prints binaries and their capabilities 
# Input:        None
# Output:       None
#-------------------------------------------------------------------------------------------------
sub DEBUG_Print
{
    my $self = shift;
    my $count = 1;
    foreach my $bin (@{$self->{iBinaries}})
    {
        printf "$count.\t%s\n\tPlatform:\t%s\n\tBuild:\t\t%s\n\tCaps:\t\t%s\n",$bin->Name(),$bin->Platform(),$bin->Build(),$bin->Capabilities()->HextString;
        ++$count;
    }
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   Binaries
# Purpose:      Accesses the list of binaries in the ECL
# Input:        None
# Output:       A reference to an array of SymBin object
#-------------------------------------------------------------------------------------------------
sub Binaries
{
    my $self = shift;
    return $self->{iBinaries};
}

#-------------------------------------------------------------------------------------------------
# Subroutine:   GetBinaryByName
# Purpose:      Given a name of the binary, gets a SymBin object 
# Input:        A string
# Output:       A SymBin object
#-------------------------------------------------------------------------------------------------
sub GetBinaryByName
{
    my $self = shift;
    return $self->{iBinaryHashTable}->{lc $_[0]} if $self->{iBinaryHashTable}->{lc $_[0]};
    return 0;
}

1;
