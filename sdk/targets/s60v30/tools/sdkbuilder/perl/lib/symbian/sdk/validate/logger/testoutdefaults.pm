#!perl -w
#
# T e s t O u t D e f a u l t s
#
# Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
#
use strict;
package Symbian::SDK::Validate::Logger::TestOutDefaults;

#
# An extremely simple Perl module to set some constants used by the CTSDK
# test modules in one place.
#
use base ("Exporter");
our @EXPORT = qw( CTSDK_OK CTSDK_PASS CTSDK_INFO CTSDK_RUN CTSDK_DUMMYRUN CTSDK_ACCEPTED_FAILURE CTSDK_WARNING CTSDK_NOT_RUN CTSDK_FAIL CTSDK_ERROR CTSDK_CRITICAL_FAIL CTSDK_INTERNAL_FAIL CTSDK_FAILURE_THRESHOLD %ctsdk_defaults &DefaultTypes);

# These are the names by which we refer to report types. They have numeric
# values, but that shouldn't be necessary. In this case they are the same
# as the severities, but that need not be the case.
use constant CTSDK_OK                => 0;
use constant CTSDK_PASS              => 1;
use constant CTSDK_INFO              => 2;
use constant CTSDK_RUN               => 3;
use constant CTSDK_DUMMYRUN          => 4;
use constant CTSDK_ACCEPTED_FAILURE  => 30;
use constant CTSDK_WARNING           => 60;
use constant CTSDK_NOT_RUN           => 70;
use constant CTSDK_FAIL              => 80;
use constant CTSDK_ERROR             => 85;
use constant CTSDK_CRITICAL_FAIL     => 90;
use constant CTSDK_INTERNAL_FAIL     => 100;

# Default failure threshold. Defines what severity of report constitutes an
# overall failure.
use constant CTSDK_FAILURE_THRESHOLD => 50;

# A hash of hashes which define the displayed report name (e.g 'FAIL:'), the
# severity and verbosity of a report type. Verbosity just determines whether
# the report is displayed when it happens. Usually it is, but in the case
# of 'RUN:' we don't bother.
our %ctsdk_defaults = (
              CTSDK_OK , { "MsgType" => "Ok:",
					       "verbose" => 1,
                          "Severity" => 0 },

            CTSDK_PASS , { "MsgType" => "Pass:",
					       "verbose" => 1,
                          "Severity" => 1 },

            CTSDK_INFO , { "MsgType" => "Info:",
					       "verbose" => 1,
                          "Severity" => 2 }, 

             CTSDK_RUN , { "MsgType" => "Run:",
					       "verbose" => 0,
                          "Severity" => 3  },

        CTSDK_DUMMYRUN , { "MsgType" => "DummyRun:",
					       "verbose" => 1,
                          "Severity" => 4  },

CTSDK_ACCEPTED_FAILURE , { "MsgType" => "Accepted Failure:",
					       "verbose" => 1,
                          "Severity" => 30 },

         CTSDK_WARNING , { "MsgType" => "WARNING:",
					       "verbose" => 1,
                          "Severity" => 60 },

         CTSDK_NOT_RUN , { "MsgType" => "NOT RUN:",
					       "verbose" => 1,
                          "Severity" => 70 },

            CTSDK_FAIL , { "MsgType" => "FAIL:",
					       "verbose" => 1,
                          "Severity" => 80 },

           CTSDK_ERROR , { "MsgType" => "ERROR:",
					       "verbose" => 1,
                          "Severity" => 85 },

   CTSDK_CRITICAL_FAIL , { "MsgType" => "CRITICAL FAILURE:",
					       "verbose" => 1,
                          "Severity" => 90 },

   CTSDK_INTERNAL_FAIL , { "MsgType" => "CTSDK TESTOUT INTERNAL FAILURE:",
					       "verbose" => 1,
                          "Severity" => 100 },
               );

# Get a copy of the structure above.
sub DefaultTypes
{
	my %hsh = %ctsdk_defaults;
	return \%hsh;
}


1;
