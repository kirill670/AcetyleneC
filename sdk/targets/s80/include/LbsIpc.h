/*
* ==============================================================================
*  Name        : LbsIpc.h
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
// LbsIpc.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __LBSIPC_H__
#define __LBSIPC_H__

const TInt8 KPosMajorVersionNumber = 1;
const TInt8 KPosMinorVersionNumber = 0;
const TInt16 KPosBuildVersionNumber = 0;

const TInt KDefaultMessageSlots = 16;

// The name of the server held in the kernel
_LIT(KPositionServerName, "PosServer");

// Used to offset the cancel IPC values
#define EPositioningCancelOffset      500

#define IPC_LOCATION_START  1000

// 1000 to 1099 reserved for RPositionServer requests
// 1500 to 1599 reserved for RPositionServer cancel requests
#define EPositionServerIpcOffset      (IPC_LOCATION_START)

// 1100 to 1199 reserved for RPositioner requests
// 1600 to 1699 reserved for RPositioner cancel requests
#define EPositionerIpcOffset          (IPC_LOCATION_START + 100)

// 1200 to 1499 reserved for 3rd party extensions to the LBS API.
// 1700 to 1999 reserved for 3rd party cancel requests.
// All extensions implemented by 3rd parties should be implemented in this range.
#define EPositionerCustomIpcOffset		(IPC_LOCATION_START + 200)



enum TPositionIpcId
	{
	//
	// Request IDs

	EPositionServerConnect             = EPositionServerIpcOffset,
	EPositionServerGetDefaultModuleId,
	EPositionServerGetNumModules,
	EPositionServerGetModuleInfoByIndex,
	EPositionServerGetModuleInfoById,
	EPositionServerGetModuleStatus,
	EPositionServerNotifyModuleStatusEvent,

	EPositionerOpenServer              = EPositionerIpcOffset,
	EPositionerOpen,
	EPositionerOpenModuleId,
	EPositionerOpenCriteria,
	EPositionerClose,
	EPositionerSetSingleRequestor,
	EPositionerSetMultipleRequestors,
	EPositionerSetUpdateOptions,
	EPositionerGetUpdateOptions,
	EPositionerGetLastKnownPosition,
	EPositionerNotifyPositionUpdate,

	EPositionCustomCodesBegin = EPositionerCustomIpcOffset,
	//
	// Cancel IDs
	EPositionCancelIpcsBegin = IPC_LOCATION_START + EPositioningCancelOffset,

	EPositionServerNotifyModuleStatusEventCancel =
		EPositionServerNotifyModuleStatusEvent + EPositioningCancelOffset,

	EPositionerGetLastKnownPositionCancel =
		EPositionerGetLastKnownPosition + EPositioningCancelOffset,
	EPositionerNotifyPositionUpdateCancel =
		EPositionerNotifyPositionUpdate + EPositioningCancelOffset,


	EPositionCustomCancelCodesBegin =
		EPositionCustomCodesBegin + EPositioningCancelOffset
	};

class TPositionServerStart
/**
 * Provides server startup parameters.
 *
 * @internalComponent
 */
	{
public:
	TPositionServerStart(TRequestStatus& aStatus);
	TPositionServerStart();

	TPtrC AsCommand() const;
	TInt GetCommand();
	void SignalL();

private:
	/** The thread ID of the thread trying to start the server */
	TThreadId iId;
	/** The status used to denote the success / failure of server startup */
	TRequestStatus* iStatus;
	};


#endif // __LBSIPC_H__
