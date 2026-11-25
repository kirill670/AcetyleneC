/** @file usbman/Src/Usb_std.h
 *
 * Implements an Active Scheduler for the server to use
 *
 * Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
 */

#ifndef __USB_STD_H__
#define __USB_STD_H__

#include <CUsbServer.h>

/**
 * Debug Logging Macro
 */
#ifdef _USBDEBUG
#define LOG(a)		a
#else
#define LOG(a)
#endif


const TInt KUsbSrvMajorVersionNumber=1;
const TInt KUsbSrvMinorVersionNumber=0;
const TInt KUsbSrvBuildVersionNumber=0;

const TInt KShutdownPause=5000000;

_LIT(KUsbServerName,"USBMAN Server");
_LIT(KUsbDLLName,"USBMAN.DLL");
_LIT(KUsbThreadName,"USBMAN");
_LIT(USB_SEMAPHORE_NAME,"USBSEM");

enum TUsbOperations 
	{
	EUsbStart,
	EUsbStop,
	EUsbRegisterObserver,
	EUsbGetCurrentState,
	EUsbStartCancel,
	EUsbCancelObserver
	};

enum TUsbActionEnum
	{
	EUsbActionPending,		// Async Action
	EUsbActionCompleted,	// Sync Action
	EUsbActionFailed		// Sync Action
	};

class TUsbAction
	{
public:
	TUsbActionEnum iAction;
	TInt iError;
	};

/**
 * The CUsbScheduler class
 *
 * Implements an Active Scheduler for the server to use
 */
class CUsbScheduler : public CActiveScheduler
	{
public:
	static CUsbScheduler* NewL();
	~CUsbScheduler();

private:
	inline CUsbScheduler() {;};

	// from CActiveScheduler
	void Error(TInt aError) const;

private:
	CUsbServer* iServer;
	};

#endif // __USB_STD_H__

