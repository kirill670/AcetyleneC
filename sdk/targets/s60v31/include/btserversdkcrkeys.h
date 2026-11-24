/*
* ============================================================================
*  Name     : BTServerSDKCRKeys.h
*  Part of  : BTServer
*
*  Description:
*     BT Server SDK CenRep key definitions
*  Version: %version: 1 %
*
*  Copyright (C) 2005 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef BTSERVER_SDK_CR_KEYS_H
#define BTSERVER_SDK_CR_KEYS_H

/**
* Bluetooth Power Mode UID
*/
const TUid KCRUidBluetoothPowerState = {0x10204DA9};

/**
* CenRep keys for storing BT power mode
*
* Bluetooth power state
*
* Possible integer values:
* 0 (EBTPowerOff) Bluetooth chip is unpowered / in sleep mode
* 1 (EBTPowerOn) Bluetooth chip is powered up and fully functional
*
* Default value: 0 (EBTPowerOff)
*/
const TUint32 KBTPowerState = 0x00000001;

// Enumeration for BT power mode values
enum TBTPowerStateValue
	{
	EBTPowerOff,
	EBTPowerOn
	};

// BTSERVER_SDK_CR_KEYS_H
#endif
