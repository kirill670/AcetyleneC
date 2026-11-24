#!perl -w
#
# T e s t O u t
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#
use strict;
package Symbian::SDK::Validate::Logger::TestOut;

use FileHandle;
use File::Basename;
use File::Path;
use Symbian::SDK::Validate::Logger::OpType;
use Symbian::SDK::Validate::Logger::TestOutDefaults;

#
# A class to record log information (and possibly display it to STDOUT too).
# Types of output are set up, either by you or you can use the defaults. These
# types, are for example, 'Pass:' or 'WARNING:'. When a report
# is made to using the 'write_typedoutput' instance method, the score
# of the specific type specified is incremented.
#
# Types have severities, and the whole object has a failurethreshold.
# If any report of a type with a severity greater than or equal to the
# failurethreshold happens then the status (see IsStatusGood) will be 0.
#
# Uses the 'Optype' class, which records the name, severity and score
# for a given logtype.
# Defaults for the output types and their severities can be found in
# 'TestOutDefaults'.
#

sub new
{
    my $arg = shift;
    my $class = ref($arg) || $arg;
    my $outputfile = shift;
    my $verbose = shift;
    my $types = shift;
    my $failurethreshold = shift;

    my $self = {
                    outputfile => undef,  #
                    filehandle => undef,
                    verbose => $verbose,  #

                    failurethreshold => undef,

                    # This gets set if something bad happens like a report
                    # on a non-existent type, so when the destructor runs
                    # or when the 'IsStatusGood' method is run they know
                    # there has been a problem and report failure.
                    overallfailure => 0,

                    # Hash of OpType objects. The keys are the
                    # type (e.g CTSDK_PASS (==0), the contents include the
                    # score (i.e how many reports of this type there have
                    # been), severity, etc.
                    types => {},

                    # An array of snapshots which can be used to restore the
                    # output to a known previous state, i.e to backtrack in
                    # test execution.
                    snapshots => undef,
               };

    bless $self, $class;

    # If the user has supplied a different failurethreshold (which determines
    # what level of report is deemed to be a failure) then use it.
    $self->FailureThreshold(CTSDK_FAILURE_THRESHOLD)
        unless(defined($self->FailureThreshold($failurethreshold)));

    # Set the output file.. If this isn't set, just give up in disgust.
    return undef unless($self->OutputFile($outputfile));

    # Set up the types to be those supplied, or the defaults if none supplied.
    if( ref($types) )
    {
        $self->Types($types);
    }else
    {
        # From TestOutDefaults.pm
        $self->Types(DefaultTypes());
    }

    return $self;
}

# Set and open the outputfile. Note that it is entirely possible to
# change the output file of the object after it has been in use for a while -
# quite how useful this might be is questionable though. Whatever calls this
# really ought to check the return value because if the file failed to open
# the output won't be logged. Obviously.
sub OutputFile
{
    my $self = shift;
    return undef unless(ref($self));
    my $file = shift;

    if( defined($file) )
    {
        # Lets have some proper forward slashes..
        $file =~ s/\\/\//g;

        $self->{filehandle}->close if( defined($self->{filehandle}) );
        $self->{outputfile} = $file ;
        my $dn = File::Basename::dirname($file);
        if($dn)
        {
            File::Path::mkpath($dn) unless(-d $dn);
        }
        $self->{filehandle} = new FileHandle "> $file";
        if( ref($self->{filehandle}) )
        {
            $self->{filehandle}->autoflush(1);
        }
        else
        {
            undef($self->{outputfile});
            print STDERR "FAIL: Could not open output file '$file'\n";
        }
    }
    return $self->{outputfile};
}

# Get or set the types member. See TestOutDefaults for an example
# of input that can be passed in. Note that this is additive - if types already
# exist and you pass in some new ones, the old ones remain.
sub Types
{
    my $self = shift;
    return undef unless(ref($self));
    my $hshrf = shift;
    if( ref($hshrf) )
    {
        for my $type (keys %$hshrf)  # type will be e.g CTSDK_OK, i.e 0.
        {
            my $severity = $hshrf->{$type}->{"Severity"};  # e.g 35
            my $msgtype = $hshrf->{$type}->{"MsgType"};    # e.g "WARNING:"
            my $verbose = $hshrf->{$type}->{"verbose"};    # 1 or 0
            my $optype = $self->{types}->{$type};          # See if got it.
            if( ref($optype) )
            {
                $optype->Severity($severity);
                $optype->Verbose($verbose);
            }
            else
            {
                $optype = Symbian::SDK::Validate::Logger::OpType->new( $msgtype, $severity, $verbose );
            }
            $self->{types}->{$type} = $optype;
        }
    }
    return $self->{types};
}

# List the kinds of output types in ascending order of severity, so Pass:'s
# and other good things first, failures etc, later or last. The odd double loop
# below is necessary because the types are stored in a hash (no guaranteed
# access order), this sorts the severities, then goes through the severities
# in order, looking for types of that severity. There is no guaranteed output
# order for output types with the same severity.
sub ListTypes
{
    my $self = shift;
    return undef unless(ref($self));
    return undef unless(ref($self->{types}));

    my @sevarray;
    for my $type (keys %{$self->{types}})
    {
        push @sevarray, $self->Types->{$type}->Severity;
    }

    sub numerically { $a <=> $b }
    @sevarray = sort numerically @sevarray;
    my %done;
    my @retarray;
    for my $sev (@sevarray)
    {
        for my $type (keys %{$self->{types}})
        {
            next if( exists($done{$type}) );
            my $sev2 = $self->Types->{$type}->Severity;
            next unless( $sev2 == $sev );
            $done{$type} = 1;
            push @retarray, $type;
        }
    }
    return @retarray;
}

# Simple destructor, gives a summary of the output and closes the file.
sub DESTROY
{
    my $self = shift;
    $self->Report("-" x 75 . "\n");
    for my $type ($self->ListTypes)
    {
        my $name = $self->Types->{$type}->Name;
        my $score = $self->Types->{$type}->Score;
        my $severity = $self->Types->{$type}->Severity;
        my $not_ok = ($severity > $self->FailureThreshold);
        my $failure = ($not_ok and $score) ? "(overall failure)" : "";

        $self->Report("$score $name 's detected. $failure\n") if($score);
    }
    $self->Report("-" x 75 . "\n");
    my $finalreport = "Overall status: ";
    $finalreport .= ($self->IsStatusGood) ? "Pass\n" : "Failure\n";
    $self->Report($finalreport);
    $self->Report("-" x 75 . "\n");
    $self->{filehandle}->close if( defined($self->{filehandle}) );
    undef $self->{filehandle};
    return;
}

# Write output to the test output file and possibly to STDOUT too if verbose
# is on..
sub Report
{
    my $self = shift;
    return undef unless(ref($self));
    my $fh = $self->{filehandle};
    my $op = shift;

    # If there is no input at least give a carriage return.
    unless($op)
    {
        print $fh "\n";
        print STDOUT "\n" if( $self->{verbose});
        return;
    }

    while($op)
    {
        # Tack on a carriage return if there isn't already one there.
        $op .= "\n" unless( $op =~ m/\n$/ );
        print $fh $op;
        print STDOUT $op if( $self->{verbose});
        $op = shift;
    }
    return;
}

#
# Write output checking for expected type info (e.g 'FAIL:'), if this
# is seen, increment the score of the associated type.
# If we see a type that we don't recognize, report as a CTSDK_INTERNAL_FAIL
# with any arguments tacked on the end. This triggers an overall failure.
#
# For known types we trigger overall failure if the severity of the report
# is greater than the failure threshold.
#
sub write_typedoutput
{
    my $self = shift;
    return undef unless(ref($self));
    my $types = $self->Types;
    my $type = shift;

    # Set the overallfailure flag if we have an unrecognized type.
    unless(defined($self->Types->{$type}))
    {
        my $typeval = CTSDK_INTERNAL_FAIL;
        my $severity = $ctsdk_defaults{$typeval}->{"Severity"};
        $self->OverallFailure(1);

        unless( defined($self->Types->{$typeval}))
        {
            my $typename = $ctsdk_defaults{$typeval}->{"MsgType"};
            my $optype = OpType->new( $typename, $severity, "verbose" );
            $self->{types}->{$typeval} = $optype;
        }
        # Report the problem with the remaining arguments following.
        $self->write_typedoutput($typeval, "Unknown report type '$type' detected.\n", @_ );
        return 0;
    }

    # We do recognize $type. Get the name, something like 'FAIL:'
    my $typename = $self->Types->{$type}->Name; # Something like "FAIL:"

    # Increment the score on this type. Note that multiple lines within the
    # same call count as one.
    $self->Types->{$type}->AddToScore(1); 

    # The verbose member in the type object determines if this output
    # type should generate output. The 'CTSDK_RUN' default type merely
    # indicates that a particular line has been run - we need this to
    # keep score but don't need a report about it.
    my $verbose = $self->Types->{$type}->Verbose;
    
    # Go through the output writing it out, prepend it all with a tab to
    # make it more readable.
    my $tabit="\t";
    while( $verbose and my $op = shift )
    {
        $self->Report($tabit . $typename . " " . $op) if($verbose);

        # Change the tab for the second and subsequent lines to indicate the
        # output is in the same block, also lose the typename, its displayed
        # on the first line, there's no need to repeat it.
        $tabit = "\t - ";
        $typename = "";
    }
    # Remember to set the failure flag if this report is of greater
    # severity than the threshold.
    if( $self->Types->{$type}->Severity >= $self->FailureThreshold)
    {
        $self->OverallFailure(1);
        return 0;
    }
    return 1;
}

# Setter/getter for the failurethreshold. Any optype with a severity greater
# than this will trigger an overall failure if a report of that type happens.
sub FailureThreshold
{
    my $self = shift;
    return undef unless(ref($self));
    my $ft = shift;
    $self->{failurethreshold} = $ft if( defined($ft) );
    return $self->{failurethreshold};
}

# Return the overall status for the test output thus far. If any type
# of report that has a severity greater than the failure threshold
# has a score greater than zero, we have seen a failure, so return 0.
# If no failing reports have happened return 1.
sub IsStatusGood
{
    my $self = shift;
    return undef unless(ref($self));

    # Something set this internal flag.
    return 0 if($self->OverallFailure);

    # The overallfailure flag would have already been set if a report blew
    # the failurethreshold, but if the severity on a certain type has been
    # changed then calling this would 'retro-check' earlier calls.
    my $rc = 1;
    for my $type ($self->ListTypes)
    {
        my $severity = $self->Types->{$type}->Severity;
        next unless( $severity >= $self->FailureThreshold );
        my $score = $self->Types->{$type}->Score;
        next unless($score);
        $self->OverallFailure(1);
        $rc = 0;
        last;
    }
    return $rc;
}

# Set/Get the overall failure flag.
# This does allow cancellation of a previous failure.
sub OverallFailure
{
    my $self = shift;
    my $of = shift;
    $self->{overallfailure} = $of;  # '|=' this to prevent cancellation.
    return $self->{overallfailure};
}

sub Verbose
{
    my $self = shift;
    my $vb = shift;
    $self->{verbose} = $vb if(defined($vb));
    return $self->{verbose};
}

# Create a 'snapshot' of the current state of the testoutput. This enables
# 'backtracking' when a user decides he's made a mistake and wants to try
# again. Returns an id that can be passed to 'RestoreSnapshot' to do the
# obvious.
sub CreateSnapshot
{
    my $self = shift;
    return undef unless(ref($self));
    my $id;
    my $snapshots;
    unless(ref($self->{snapshots}))
    {
        $self->{snapshots} = [];
    }
    $snapshots = $self->{snapshots};
    # Id is the index in the array where the snapshot will live.
    $id = $#{$snapshots} + 1;

    # First get the types we have. $self->{types} is a reference to a hash
    # each member of which is an 'OpType' object. Make a copy of each and
    # place it in hshref..
    my $hshref = {};
    for my $type (keys %{$self->{types}})
    {
        my $opt = $self->{types}->{$type};
        my $optname = $opt->Name;
        my $score = $opt->Score();
        my $severity = $opt->Severity();
        my $verbose = $opt->Verbose();
        my $optype = Symbian::SDK::Validate::Logger::OpType->new( $optname, $severity, $verbose );
        $hshref->{$type} = $optype;
    }
    my $filepos = $self->{filehandle}->tell();
    my $ovfail = $self->OverallFailure;
    my $failth = $self->FailureThreshold;

    my $snap = [ $filepos, $ovfail, $failth, $hshref ];
    push @$snapshots, $snap;
    
    return $id;
}

sub RestoreSnapshot
{
    my $self = shift;
    return undef unless(ref($self));
    my $id = shift;
    return undef unless(defined($id));
    my $snapshots = $self->{snapshots};

    # Find the snapshot. Give up immediately if it isn't there.
    return undef unless($$snapshots[$id]);
    my $snref = $$snapshots[$id];
    return undef unless(ref($snref));

    # Get the old values back..
    my($filepos, $ovfail, $failth, $hshref) = @$snref;

    # Set the old file position.. Note this TRASHES any old output that
    # happened after the point in the output we are restoring to.
    $self->{filehandle}->seek($filepos, 0);
    $self->{filehandle}->truncate($filepos);

    # Reset the overallfailure member. Don't use the OverallFailure method,
    # because this could change to prevent 'cancellation' of overall failure
    # states.
    $self->{overallfailure} = $ovfail;

    # Reset the failurethreshold member.
    $self->FailureThreshold($failth);

    # Now the nasty bit. Potentially additional types of report could have
    # been added since the snapshot was made, so we must delete the lot!
    # We do this just be redefined $self->{types}, the old ones will evaporate.
    $self->{types} = {};
    for my $type (keys %$hshref)
    {
        # The CreateSnapshot method set up copies of the OpType objects that
        # existed when the snapshot was made. Use them..
        $self->{types}->{$type} = $hshref->{$type};
    }

    # Remove any 'later' snapshots. We can't restore to these now because the
    # 'truncate' method above has trashed the output from the current point
    # onwards. A bit of syntax trouble here..
    my @arr = @$snapshots[0..$id];
    $self->{snapshots} = \@arr;

    # Return..
    return 1;
}

1;
