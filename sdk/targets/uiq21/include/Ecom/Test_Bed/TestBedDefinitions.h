// TestBedDefinitions.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file TestBedDefinitions.h
	Comments : This file contains common definitions used in the TestBed (error codes etc)
 */ 

#ifndef __TESTBEDDEFINITIONS_H__
#define __TESTBEDDEFINITIONS_H__

#include <e32base.h>	// For TInt definition

const TInt KErrTestBedInvalidTransition		= -0x6100;	//-24832

const TInt KTestBedRepeatTest				= -0x6101;	//-24833
const TInt KTestBedTestLeft					= -0x6102;	//-24834
const TInt KTestBedTestCancel				= -0x6103;	//-24835
const TInt KTestBedLeakTestLoopDetected		= -0x6104;	//-24836
const TInt KTestBedFailedPreConditions		= -0x6105;	//-24837
const TInt KTestBedFailedPostConditions		= -0x6106;	//-24838
const TInt KTestBedAsynchronousTransition	= -0x6107;	//-24839
const TInt KTestBedInvalidStatus			= -0x6108;	//-24840
const TInt KTestBedFailedInvariant			= -0x6109;	//-24841

#endif
