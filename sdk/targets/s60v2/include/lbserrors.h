/*
* ==============================================================================
*  Name        : LbsErrors.h
*  Part of     : Mobile Location Framework/Core
*  Interface   : --
*  Description :
*   ?description_line
*  Version     :
*
*  Copyright (c) 2004 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
*
* ==============================================================================
*/
// LbsErrors.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __LBSERRORS_H__
#define __LBSERRORS_H__

#include <e32def.h>

_LIT(KPosClientFault,"Lbs Client Fault");

/**
 * Position Client API panic codes
 */
enum TPositionClientPanic
	{
	/** HPGI datatype mismatch */
	EPositionGenericInfoMismatchDataType		= 0,
	/** CRequestor constructed with a null descriptor */
	EPositionRequestorConstructorGivenNullData	= 1,
	/** HPGI zero-byte buffer */
	EPositionGenericInfoZeroBufferSize			= 2,
	/** A unknown IPC request has been made on the server. */
	EPositionBadRequest							= 3,
	/** A bad descriptor has been given to the server by the client. */
	EPositionBadDescriptor						= 4,
	/** An attempt has been made to connect using an already open handle. */
	EPositionServerHandleNotClosed				= 5,
	/** An attempt has been made to communicate though a non connected handle. */
	EPositionServerBadHandle					= 6,
	/** A client has tried to use a RPositioner/RPositionServer handle that hasn't
	    been properly initialised. */
	EPositionNullPointerHolder					= 7,
	/** A client has asked for/set the supported classes in TPositionModuleInfo
	    with an invalid class type. */
	EPositionInvalidClassType					= 8,
	/** Too many items specified in a TPositionSelectionOrder. */
	EPositionSelectionOrderOverflow				= 9,
	/** The class' size doesn't match the expected value. */
	EPositionClassSizeMismatch					= 10,
	/** An unsupported object of size greater than KPositionMaxSizeQualityTrait has been
	passed to a TPositionQualityBase as a field. */
	EPositionQualityBadDataType					= 11,
	/** A negative TTimeIntervalMicroSeconds was passed to a method. */
	EPositionBadTime                            = 12,
	/** A negative value for accuracy was passed to a method. */
	EPositionBadAccuracy                        = 13,
	/** A client has attempted to instantiate a HPositionGenricInfo with 0 Max Fields. */
	EPositionGenericInfoZeroMaxFields			= 14,
	/** A client has called an asynchronous request while it is still outstanding
	on that RPositionServer / RPositioner. */
	EPositionDuplicateRequest                   = 15,
	/** A session or sub-session was closed with requests still outstanding. */
	EPositionRequestsNotCancelled               = 16,
	/** A NULL entry has been found in the requestor stack. */
	EPositionNullRequestor	                    = 17
	};


/*
 * Completion codes to give extended information about location fix.
 */
const TInt KPositionQualityLoss = 1;
const TInt KPositionPartialUpdate = 2;


/**
 * Lbs specific error codes.
 */
const TInt KPositionErrBase = -17350;

const TInt KErrPositionBufferOverflow = KPositionErrBase;		//-17350
const TInt KErrPositionIncalculable = KPositionErrBase - 1;		//-17351


#endif //__LBSERRORS_H__