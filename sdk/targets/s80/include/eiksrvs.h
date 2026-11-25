/*
* ==============================================================================
*  Name        : eiksrvs.h
*  Part of     : CKON
*  Interface   : Application Server API
*  Description : Miscellaneous consts.
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef EIKSRVS_H
#define EIKSRVS_H

// INCLUDES
#include <eikappui.h>
#include <eikenv.h>
#include <eiksrv.pan>
#include <apgtask.h>
#include <eiksrv.h>

// FORWARD DECLARATIONS
class CDictionaryFileStore;

// CONSTANTS
/**
@publishedPartner
@released
*/
_LIT(EIKAPPUI_SERVER_NAME,"EikAppUiServer");

/**
@publishedPartner
@released
*/
_LIT(EIKAPPUI_SERVER_THREAD_NAME,"EikAppUiServerThread");

/**
@publishedPartner
@released
*/
_LIT(EIKAPPUI_SERVER_SEMAPHORE,"EikAppUiServerStartSemaphore");

/**
@internalComponent
*/
const TInt KEikSrvDefaultHeapSize=0x10000;

/**
@internalComponent
*/
const TInt KEikSrvDefaultMaxHeapSize=0x100000;


/**
@internalComponent
*/
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
	EEikAppUiUpdateStatusPaneLayout
	};


/**
function to panic the server

@internalComponent
*/
GLREF_C void PanicServer(TEikAppUiServPanic aPanic);


#endif	// EIKSRVS_H

// End of File
