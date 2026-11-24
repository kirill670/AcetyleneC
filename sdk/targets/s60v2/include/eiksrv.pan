// EIKSRV.PAN
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKSRV_PAN__)
#define __EIKSRV_PAN__

/**
@publishedPartner
@released
*/
#define __EIKON_SERVER _L("Eikon server")

/**
@internalComponent
*/
enum TEikServPanic
	{
	EEikServPanicNotifyServiceNotSupported,
	EEikServPanicNotifyBadDescriptor,
	EEikServPanicAlarmAlertServiceNotSupported,
	EEikServPanicNoTaskListDialog,
	EEikServPanicTaskNull,
	EEsPanicAlarmAlert,
	EEikServPanicAlarmAlertServerAlreadyConnected,
	EEikServEnvPanicNullAppUi,
	EEikServPanicNoSuchLabelInAlarm,
	EEikServPanicDriveIndexOutOfRange,
	EEikServPanicNotiferArrayNotNull,
	EEikServPanicChannelIndexOutOfRange,
	EEikServPanicNullObservedList,
	EEikServPanicQueueIndexOutOfRange,
	EEikServPanicNotifyAlertQueueEmpty,
	EEikSrvClientPanicInconsistentMessageParameters,
	};

/**
@internalComponent
*/
GLREF_C void Panic(TEikServPanic aPanic);
#endif
