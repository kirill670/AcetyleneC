/*
* ==============================================================================
*  Name        : HWRMPowerStateSDKPSKeys.h
*  Part of     : HW Resources and Enhancements / HWResourceManager
*  Interface   : Public
*  Description : SDK Publish&Subscribe definitions of the
*                HW Resource Manager for the Power State API.
*  Version     : %version:4 %
*
*  Copyright © 2002-2005 Nokia Corporation.
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

#ifndef HWRMPOWERSTATESDKPSKEYS_H
#define HWRMPOWERSTATESDKPSKEYS_H

// INCLUDES
#include <e32std.h>

// =============================================================================
// HW Resource Power State PubSub SDK API
// =============================================================================
const TUid KPSUidHWRMPowerState = { 0x10205041 }; 


/**
* Battery level of device.
* Interpreted as enum EPSHWRMBatteryLevel and can be related to the number 
* of battery bars displayed.
* This property is updated only when battery level changes.
*
* @see EPSHWRMBatteryLevel
*/
const TUint32 KHWRMBatteryLevel = 0x00000001;
enum EPSHWRMBatteryLevel
    {
    EBatteryLevelUnknown        = -1,   ///< Uninitialized or some other error
    EBatteryLevelLevel0         = 0,    ///< Lowest battery level
    EBatteryLevelLevel1         = 1,
    EBatteryLevelLevel2         = 2,
    EBatteryLevelLevel3         = 3,
    EBatteryLevelLevel4         = 4,
    EBatteryLevelLevel5         = 5,
    EBatteryLevelLevel6         = 6,
    EBatteryLevelLevel7         = 7     ///< Highest battery level
    };

/**
* Battery status of device.
* Interpreted as enum EPSHWRMBatteryStatus.
* This property may be updated to same status as previously, to indicate
* the note in question needs to be shown again.
*
* EBatteryStatusLow update comes approximately ten times before 
* battery is completely empty and it comes at approximately
* 10 minute intervals. If phone is in-call mode, update comes at 
* approximately 1 minute intervals.
*
* EBatteryStatusEmpty comes slightly before phone must power down 
* automatically because of insufficient battery power.  
*
* @see EPSHWRMBatteryStatus
*/
const TUint32 KHWRMBatteryStatus = 0x00000002;
enum EPSHWRMBatteryStatus
    {
    EBatteryStatusUnknown        = -1, ///< Uninitialized or some other error
    EBatteryStatusOk             = 0,  ///< This can also be used during charging
    EBatteryStatusLow            = 1,  ///< Show note to user "Battery low"
    EBatteryStatusEmpty          = 2   ///< Show "recharge battery" note to user
    };

/**
* Charging status of device.
* Interpreted as enum EPSHWRMChargingStatus.
* This property is updated only when charging status changes.
*
* @see EPSHWRMChargingStatus
*/
const TUint32 KHWRMChargingStatus = 0x00000003;
enum EPSHWRMChargingStatus
    {
    EChargingStatusError              = -1,
    EChargingStatusNotConnected       = 0,  ///< Charger not connected/uninitialized
    EChargingStatusCharging           = 1,  ///< Device is charging
    EChargingStatusNotCharging        = 2,  ///< Charger is connected, device not charging
    EChargingStatusAlmostComplete     = 3,  ///< Charging almost completed
    EChargingStatusChargingComplete   = 4,  ///< Charging completed
    EChargingStatusChargingContinued  = 5   ///< Charging continued after brief interruption
    };


// HWRMPOWERSTATESDKPSKEYS_H
#endif

// End of File

