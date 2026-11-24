// Copyright (c) 2003, Symbian Software Ltd.  All rights reserved
		
/*
Publish and Subscribe keys and categories.
Allows clients to observe various events published by the Bluetooth subsystem,
and for clients to influence some parameters in the Bluetooth subsystem
*/


#ifndef BT_SUBSCRIBE_H
#define BT_SUBSCRIBE_H

#include <e32property.h>


// P&S Categories

/**
KPropertyUidBluetoothCategory
This is the category that is used for observing events FROM the Bluetooth subsystem.
It can be viewed as the "out" channel
@publishedAll
@released
*/
const TUid KPropertyUidBluetoothCategory = {0x101FD916};

/**
KPropertyUidBluetoothControlCategory
This is the category that is used to allow clients to influence the Bluetooth subsystem
It can be viewed as the "in" channel.

This replaces some of the Ioctls present prior to v8.0 of SymbianOS
@publishedAll
@released
*/
const TUid KPropertyUidBluetoothControlCategory = {0x101FD917};

// P&S Keys

/**
KPropertyKeyBluetoothLocalDeviceAddress
The key to observe the device address of the local Bluetooth hardware
The P&S value will contain a descriptor of the device address
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothLocalDeviceAddress = 0;

/**
KPropertyKeyBluetoothLocalDeviceAddress
The key to observe the the number of Bluetooth physical links attached to the local device
The P&S value will contain the number of physical links
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothPHYCount = 1;

/**
KPropertyKeyBluetoothConnecting
The key to observe whether the local device is paging another device (i.e. is connecting a physical link)
The P&S value will contain a boolean: ETrue if connecting, otherwise EFalse
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothConnecting = 2;

/**
KPropertyKeyBluetoothScanning
The key to observe or control what scans the Bluetooth hardware is currently performing
The P&S value contains an integer with the scan value as published in the Bluetooth Core Specification
@see Bluetooth Core Specification
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothScanning = 3;

/**
KPropertyKeyBluetoothLimitedDiscoverable
The key to observe or control whether the local device is in Limited Discoverable mode
The P&S value will contain a boolean: ETrue if in limited discoverable mode, otherwise EFalse
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothLimitedDiscoverable = 4;

/**
KPropertyKeyBluetoothDeviceClass
The key to observe or set the class of device of the local device
The P&S value will contain an integer of the local device class.
@see Bluetooth Core Specification
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothDeviceClass = 5;

/**
KPropertyKeyBluetoothAFHHostChannelClassification
The key to send an AFH Host Channel Classification to the local Bluetooth hardware
The P&S value will contain a descriptor containing the AFH Host Channel Classification 
bit set. A bit which is set to zero instructs the local Bluetooth hardware 
not to hop to the frequency represented by that bit in a connection in which 
it is master and which is using AFH. Also, if the local Bluetooth hardware is slave in a 
connection, which is using AFH, an AFH Host Channel Classification may be used to advise
the remote master what frequencies to avoid.
NB. THIS IS SUPPORTED ONLY IN VERSION 8.1 AND THEREAFTER.

@see TBTAFHHostChannelClassification
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothAFHHostChannelClassification = 6;

/**
KPropertyKeyBluetoothAFHChannelAssessmentMode
The key to send the Bluetooth AFH Channel Assessment Mode to the local Bluetooth hardware.
If AFH Channel Assessment Mode is on, then the local hardware will keep checking what 
channels are busy and so should be avoided in a connection using AFH.
The P&S value will contain a boolean: ETrue if AFH Channel Assessment Mode is required 
(the default if supported by the hardware), EFalse if not.
Using this key is CURRENTLY NOT SUPPORTED. The default setting of AFH Channel Assessment Mode 
(on if supported by the hardware) is considered satisfactory.
@publishedPartner
@prototype
*/
const TUint KPropertyKeyBluetoothAFHChannelAssessmentMode = 7; //CURRENTLY NOT SUPPORTED 

/**
KPropertyKeyBluetoothDeviceName
The key to observe or set the name of device of the local device
The P&S value will be of type EText and contain the local device name in Unicode.
At all times the name must have a length <= KHCILocalDeviceNameMaxLength (defined in hcibase.h).
@see Bluetooth Core Specification
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothDeviceName = 8;

/**
KPropertyKeyBluetoothCorruptRegistryReset
This key is intended to be used by the UI to be informed when a corrupt 
Bluetooth registry has been detected so that the UI can inform the user
that all of the pairings they have made have been lost.

The P&S value will either be 0 or give the tick count, as given by 
User::TickCount(), at the time which the corrupt Bluetooth Registry has 
been restored or replaced. If the key is 0 this means that the Bluetooth 
registry has not been found to be corrupt since the device was turned on.
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothCorruptRegistryReset = 9;

/**
KPropertyKeyBluetoothRegistryTableChange
The key to observe changes in the Bluetooth Registry
The P&S value will contain an integer describing which of the tables in the Bluetooth Registry changed
see further in this header file
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothRegistryTableChange = 0x1000;

// Some keys have values that are "wellknown" - these are enumerated here
// RegistryTableChanges

/**
KRegistryChangeRemoteTable
@see KPropertyKeyBluetoothRegistryTableChange
The value in the KPropertyKeyBluetoothRegistryTableChange key if the Remote device table changed
@publishedAll
@released
*/
const TUint KRegistryChangeRemoteTable = 0;

/**
KRegistryChangeLocalTable
@see KPropertyKeyBluetoothRegistryTableChange
The value in the KPropertyKeyBluetoothRegistryTableChange key if the Local device table changed
@publishedAll
@released
*/
const TUint KRegistryChangeLocalTable = 1;

/**
KRegistryChangeCSYTable
@see KPropertyKeyBluetoothRegistryTableChange
The value in the KPropertyKeyBluetoothRegistryTableChange key if the CSY-settings table changed
@publishedAll
@released
*/
const TUint KRegistryChangeCSYTable = 2;

#endif //BT_SUBSCRIBE_H
