// SaCls.h
//
// Copyright (c) 1997-2005 Symbian Software Ltd. All rights reserved.
//

#ifndef __SACLS_H__
#define __SACLS_H__

#include <e32std.h>

/**
System agent 2 - maintained entries
@publishedAll
@released
*/
const TInt KUidProfileValue		=0x100052D2;
const TUid KUidProfile			={KUidProfileValue};

/**
@capability WriteDeviceData capability is required for changing KUidPhonePwr property value.
@publishedAll
@released
*/
const TInt KUidPhonePwrValue=0x100052C5;
const TUid KUidPhonePwr={KUidPhonePwrValue};

/**
@publishedAll
@released
*/
enum TSAPhoneStatus
	{
	ESAPhoneOff,
	ESAPhoneOn
	};

/**
@capability WriteDeviceData capability is required for changing KUidSIMStatus property value.
@publishedAll
@released
*/
const TInt KUidSIMStatusValue	=0x100052C6;
const TUid KUidSIMStatus		={KUidSIMStatusValue};

/**
@publishedAll
@released
*/
enum TSASIMStatus
	{
	ESASimOk,
	ESASimNotPresent,
	ESASimRejected
	};

/**
@capability WriteDeviceData capability is required for changing KUidNetworkStatus property value.
@publishedAll
@released
*/
const TInt KUidNetworkStatusValue=0x100052C7;
const TUid KUidNetworkStatus	={KUidNetworkStatusValue};

/**
@publishedAll
@released
*/
enum TSANetworkStatus
	{
	ESANetworkAvailable,
	ESANetworkUnAvailable
	};

/**
@capability WriteDeviceData capability is required for changing KUidNetworkStrength property value.
@publishedAll
@released
*/
const TInt KUidNetworkStrengthValue  =0x100052C8;
const TUid KUidNetworkStrength  ={KUidNetworkStrengthValue};

/**
@publishedAll
@released
*/
enum TSANetworkStrength
	{
	ESANetworkStrengthNone,
	ESANetworkStrengthLow,
	ESANetworkStrengthMedium,
	ESANetworkStrengthHigh,
	ESANetworkStrengthUnknown
	};

/**
@capability WriteDeviceData capability is required for changing KUidChargerStatus property value.
@publishedAll
@released
*/
const TInt KUidChargerStatusValue	=0x100052C9;
const TUid KUidChargerStatus	={KUidChargerStatusValue};

/**
@publishedAll
@released
*/
enum TSAChargerStatus
	{
	ESAChargerConnected,
	ESAChargerDisconnected,
	ESAChargerNotCharging
	};

/**
@capability WriteDeviceData capability is required for changing KUidBatteryStrength property value.
@publishedAll
@released
*/
const TInt KUidBatteryStrengthValue  =0x100052CA;
const TUid KUidBatteryStrength  ={KUidBatteryStrengthValue};

/**
@publishedAll
@released
*/
enum TSABatteryStrength
	{
	ESABatteryAlmostEmpty,
	ESABatteryLow,
	ESABatteryFull
	};

/**
@capability WriteDeviceData capability is required for changing KUidCurrentCall property value.
@publishedAll
@released
*/
const TInt KUidCurrentCallValue	=0x100052CB;
const TUid KUidCurrentCall		={KUidCurrentCallValue};

/**
@publishedAll
@released
*/
enum TSACurrentCall
	{
	ESACallNone,
	ESACallVoice,
	ESACallFax,
	ESACallData,
	ESACallAlerting,
	ESACallRinging,
	ESACallAlternating,
	ESACallDialling,
	ESACallAnswering,
	ESACallDisconnecting
	};

/**
@publishedAll
@released
*/
const TInt KUidDataPortValue	=0x100052CC;
const TUid KUidDataPort			={KUidDataPortValue};

/**
@publishedAll
@released
*/
enum TSAPort
	{
	ESADataPortIdle,
	ESADataPortBusy	
	};

/**
@publishedAll
@released
*/
const TInt KUidInboxStatusValue	=0x100052CD;
const TUid KUidInboxStatus		={KUidInboxStatusValue};

/**
@publishedAll
@released
*/
enum TSAInboxStatus
	{
	ESAInboxEmpty,
	ESADocumentsInInbox
	};

/**
@publishedAll
@released
*/
const TInt KUidOutboxStatusValue=0x100052CE;
const TUid KUidOutboxStatus		={KUidOutboxStatusValue};

/**
@publishedAll
@released
*/
enum TSAOutboxStatus
	{
	ESAOutboxEmpty,
	ESADocumentsInOutbox
	};

/**
@publishedAll
@released
*/
const TInt KUidClockValue		=0x100052CF;
const TUid KUidClock			={KUidClockValue};

/**
@publishedAll
@released
*/
enum TSAClock
	{
	ESAAm,
	ESAPm
	};

/**
No longer used
@publishedAll
@released
*/
const TInt KUidAlarmValue		=0x100052D0;
const TUid KUidAlarm			={KUidAlarmValue};

/**
@publishedAll
@released
*/
enum TSAAlarm
	{
	ESAAlarmOff,
	ESAAlarmOn,
	};

/**
@publishedAll
@released
*/
const TInt KUidIrdaStatusValue	=0x100052D1;
const TUid KUidIrdaStatus		={KUidIrdaStatusValue};

/**
@publishedAll
@released
*/
enum TSAIrdaStatus
	{
	ESAIrLoaded,		//IRDA Irlap layer loaded
	ESAIrDiscoveredPeer,//Discovery begin
	ESAIrLostPeer,		//Discovery end
	ESAIrConnected,		//IRDA Irlap layer connected
	ESAIrBlocked,		//IRDA Irlap layer blocked
	ESAIrDisConnected,	//IRDA Irlap layer disconnected
	ESAIrUnloaded		//IRDA Irlap layer unloaded
	};
	
/**
This is a duplicate of Swi::KUidSoftwareInstallKey from swi/swispubsubdefs.h
This is the publish and subscribe property used by Secure Software Install to publish
its current state. The publish and subscribe key is defined by SysAgent2 server, but we
do not want to have a dependency to the security subsystem, so we redefine a constant 
with the same value here.
@internalTechnology
*/
const TInt KSAUidSoftwareInstallKeyValue = 0x102047B7;

/**
This is a duplicate of KUidJavaInstallKey from swi/swispubsubdefs.h
This is the Publish and Subscribe property used by Java install to publish its current 
state. The publish and subscribe key is defined by SysAgent2 server, but we
do not want to have a dependency to the security subsystem, so we redefine a constant 
with the same value here.
@internalTechnology
*/
const TInt KSAUidJavaInstallKeyValue = 0x1020806E;


/** This is the global definition used by Software Install server (SWIS)
This is the publish and subscribe property used by SWI to publish the most
recently installed or updated application. If the application has 
subsequently been uninstalled the value may refer to an application
that no longer exists. Has value KUidNull if no applications have been 
installed
 
@publishedPartner
@released
@capability ECapabilityTrustedUI capability is required to modify the value of this property
*/
const TUint KUidSwiLatestInstallation = 0x10272C8E;

/** This is the global definition of KUidJmiLatestInstallation used
by Java Midlet Installer
This is the publish and subscribe property used by JMI to publish the most
recently installed application. If the application has 
subsequently been uninstalled the value may refer to an application
that no longer exists. Has value KUidNull if no applications have been 
installed 

@publishedPartner
@released
@capability ECapabilityTrustedUI capability is required to modify the value of this property
*/
const TUint KUidJmiLatestInstallation = 0x10272D3D;


/** This is the global definitioin of KUidUnifiedCertstoreFlag. This publish
and subscribe property is used to notify users of changes in the unified certstore

@publishedPartner
@released
*/
const TUint KUidUnifiedCertstoreFlag = 0x10272C83;

/**
This is a duplicate of KUidBackupRestoreKey from the secure backup engine's sbdefs.h
This is the Publish and Subscribe property used by Secure Backup Engine to publish its current 
state. The publish and subscribe key is defined by SysAgent2 server.
@publishedAll
@released
*/
const TUint KUidBackupRestoreKey = 0x10202792;


/** 
The function starts SysAgt2 server.

SysAgt2 server does not ofer any functionality other than registering P&S properties
with UIDs {0x100052C5..0x100052F4} and updating the "battery status" property at regular
periods of time (30 seconds).

@return KErrNone The server was started successfully.
        KErrAlreadyExists An instance of the server already exists.
        KErrGeneral The server panicked at the startup.
        Some other system-wide error codes.

@publishedAll
@released
*/
IMPORT_C TInt StartSysAgt2();

#endif //__SACLS_H__
