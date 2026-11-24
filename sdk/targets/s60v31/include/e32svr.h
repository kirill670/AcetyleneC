// e32\include\e32svr.h
//
// Copyright (c) 1995-2005 Symbian Software Ltd. All rights reserved.
//

#ifndef __E32SVR_H__
#define __E32SVR_H__
#include <e32hal.h>
#include <d32locd.h>
#include <e32notif.h>
#include <e32ldr.h>
#include <e32event.h>
#include <e32ktran.h>
#include <e32debug.h>
#include <e32lmsg.h>

/**
@internalComponent
@removed
*/
enum TBlockType {EBlocked,EUnBlocked,ERelease};

/**
@internalAll
*/
class UserSvr
	{
public:
	IMPORT_C static void CaptureEventHook();
	IMPORT_C static void ReleaseEventHook();
	IMPORT_C static void RequestEvent(TRawEventBuf &anEvent,TRequestStatus &aStatus);
	IMPORT_C static void RequestEventCancel();
	IMPORT_C static TInt AddEvent(const TRawEvent& anEvent);
	IMPORT_C static void ScreenInfo(TDes8& anInfo);
	IMPORT_C static TInt DllSetTls(TInt aHandle, TAny *aPtr);
	IMPORT_C static TInt DllSetTls(TInt aHandle, TInt aDllUid, TAny *aPtr);	/**< @internalComponent */
	IMPORT_C static TAny *DllTls(TInt aHandle);
	IMPORT_C static TAny *DllTls(TInt aHandle, TInt aDllUid);	/**< @internalComponent */
	IMPORT_C static void DllFreeTls(TInt aHandle);
	IMPORT_C static void DllFileName(TInt aHandle, TDes &aFileName);
	IMPORT_C static void FsRegisterThread();
	IMPORT_C static void WsRegisterThread();
    IMPORT_C static TBool TestBootSequence();
    IMPORT_C static void WsRegisterSwitchOnScreenHandling(TBool aState);
    IMPORT_C static void WsSwitchOnScreen();
    IMPORT_C static TInt ChangeLocale(const TDesC& aLocaleDllName);
	IMPORT_C static TInt ResetMachine(TMachineStartupType aType);
	IMPORT_C static void UnlockRamDrive();
	IMPORT_C static void LockRamDrive();
	IMPORT_C static TUint32 RomRootDirectoryAddress();
	IMPORT_C static TInt ExecuteInSupervisorMode(TSupervisorFunction aFunction, TAny* aParameter);
	IMPORT_C static TUint32 RomHeaderAddress();
	IMPORT_C static TUint32 DebugMask();                    // Return the kernel debug mask 0
	IMPORT_C static TUint32 DebugMask(TUint aIndex);        // Return the kernel debug mask
	IMPORT_C static TInt HalFunction(TInt aGroup, TInt aFunction, TAny* a1, TAny* a2);
	IMPORT_C static TInt HalFunction(TInt aGroup, TInt aFunction, TAny* a1, TAny* a2, TInt aDeviceNumber);
	IMPORT_C static TInt HalGet(TInt,TAny*);	// redundant - only here for BC
	IMPORT_C static TInt HalSet(TInt,TAny*);	// redundant - only here for BC
	IMPORT_C static TInt SetMemoryThresholds(TInt aLowThreshold, TInt aGoodThreshold);
	IMPORT_C static TBool IpcV1Available();
	IMPORT_C static TLinAddr ExceptionDescriptor(TLinAddr aCodeAddress); /**< @internalTechnology */
	IMPORT_C static TInt LocalePropertiesSetDefaults();	/**< @internalTechnology */
	};

#endif

