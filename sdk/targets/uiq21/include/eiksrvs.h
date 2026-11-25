// EIKSRVS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSRVS_H__)
#define __EIKSRVS_H__

#if !defined(__EIKAPPUI_H__)
#include <eikappui.h>
#endif

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif

#if !defined(__EIKSRV_PAN__)
#include <eiksrv.pan>
#endif

#if !defined(__APGTASK_H__)
#include <apgtask.h>
#endif

#if !defined(__EIKSRV_H__)
#include <eiksrv.h>
#endif

class CDictionaryFileStore;
_LIT(EIKAPPUI_SERVER_NAME,"EikAppUiServer");
_LIT(EIKAPPUI_SERVER_THREAD_NAME,"EikAppUiServerThread");
_LIT(EIKAPPUI_SERVER_SEMAPHORE,"EikAppUiServerStartSemaphore");
const TInt KEikSrvDefaultHeapSize=0x10000;
const TInt KEikSrvDefaultMaxHeapSize=0x100000;

enum TEikUiOpCode
	{
	EEikAppUiNotifyAlarmServerOfTaskChange,
	EEikAppUiLaunchTaskList,
	EEikAppUiCycleTasks,
	EEikAppUiAddToStack,
	EEikAppUiRemoveFromStack,
	EEikAppUiExecuteD,
	EEikAppUiSetStatusPaneFlags,
	EEikAppUiSetStatusPaneLayout,
	EEikAppUiNotifer,
	EEikAppUiBlankScreen,
	EEikAppUiUnblankScreen,
	EEikAppUiResolveError,
	EEikAppUiExtension,
	};

// function to panic the server
GLREF_C void PanicServer(TEikAppUiServPanic aPanic);

#endif
