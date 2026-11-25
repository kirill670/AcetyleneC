// BACKUP_STD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__BACKUP_STD_H__)
#define __BACKUP_STD_H__

#include <e32std.h>

/**
@internalComponent
*/
_LIT(__BACKUP_SERVER_NAME_V2,"BackupServer");

/**
@internalComponent
*/
enum TBaBakOpCode
	{
	EBakOpCodeEventReady=20, // EBakOpCodeStartNotifications,
	EBakOpCodeGetEvent,
	EBakOpCodeCloseAllFiles,
	EBakOpCodeRestartAll,
	EBakOpCodeCloseFile,
	EBakOpCodeRestartFile,
	EBakOpCodeNotifyLockChange,
	EBakOpCodeNotifyLockChangeCancel,
	EBakOpCodeCloseServer,
	EBakOpCodeNotifyBackupOperation,
	EBakOpCodeCancelOutstandingBackupOperationEvent,
	EBakOpCodeGetBackupOperationState,
	EBakOpCodeBackupOperationEventReady,
	EBakOpCodeGetBackupOperationEvent,
	EBakOpCodeSetBackupOperationObserverIsPresent,
	EBakOpCodeStopNotifications
	};

#endif
