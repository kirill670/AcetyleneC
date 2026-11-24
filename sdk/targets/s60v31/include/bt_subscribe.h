// Copyright (c) 2003, Symbian Software Ltd.  All rights reserved
		
/*
Publish and Subscribe keys and categories.
Allows clients to observe various events published by the Bluetooth subsystem,
and for clients to influence some parameters in the Bluetooth subsystem
*/


#ifndef BT_SUBSCRIBE_H
#define BT_SUBSCRIBE_H

#include <e32property.h>

/**
@publishedAll
@released
*/
const TInt KUidBluetoothPubSubKeyBase = 0x10203637;	//	Range of 32 values registered

// P&S Categories
 
/**
KPropertyUidBluetoothCategory
This is a deprecated constant, maintained for source compatibility with non-secured 
Symbian OS platforms.

@publishedAll
@deprecated
*/
const TUid KPropertyUidBluetoothCategory = {KUidSystemCategoryValue};

/**
KPropertyUidBluetoothControlCategory
This is a deprecated constant, maintained for source compatibility with non-secured 
Symbian OS platforms.

@publishedAll
@deprecated
*/
const TUid KPropertyUidBluetoothControlCategory = {KUidSystemCategoryValue};

// P&S Keys

//-------------

/**
KPropertyKeyBluetoothGetLocalDeviceAddress
The key to observe the device address of the local Bluetooth hardware
The P&S value will contain a descriptor of the device address
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothGetLocalDeviceAddress = (KUidBluetoothPubSubKeyBase + 0);

/**
KPropertyKeyBluetoothLocalDeviceAddress
This is a deprecated constant, maintained for source compatibility with non-secured 
Symbian OS platforms.
@publishedAll
@deprecated
*/
const TUint KPropertyKeyBluetoothLocalDeviceAddress = KPropertyKeyBluetoothGetLocalDeviceAddress;

//-------------

/**
KPropertyKeyBluetoothGetPHYCount
The key to observe the the number of Bluetooth physical links attached to the local device
The P&S value will contain the number of physical links
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothGetPHYCount = (KUidBluetoothPubSubKeyBase + 1);

/**
KPropertyKeyBluetoothPHYCount
This is a deprecated constant, maintained for source compatibility with non-secured 
Symbian OS platforms.
@publishedAll
@deprecated
*/
const TUint KPropertyKeyBluetoothPHYCount = KPropertyKeyBluetoothGetPHYCount;

//-------------

/**
KPropertyKeyBluetoothGetConnectingStatus
The key to observe whether the local device is paging another device (i.e. is connecting a physical link)
The P&S value will contain a boolean: ETrue if connecting, otherwise EFalse
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothGetConnectingStatus = (KUidBluetoothPubSubKeyBase + 2);

/**
KPropertyKeyBluetoothConnecting
This is a deprecated constant, maintained for source compatibility with non-secured 
Symbian OS platforms.
@publishedAll
@deprecated
*/
const TUint KPropertyKeyBluetoothConnecting = KPropertyKeyBluetoothGetConnectingStatus;

//-------------

/**
KPropertyKeyBluetoothGetScanningStatus
The key to observe what scans the Bluetooth hardware is currently performing
The P&S value contains an integer with the scan value as published in the Bluetooth Core Specification

The use of this key is equivalent in a secure Symbian OS platform to the use of the key
KPropertyKeyBluetoothScanning with the category KPropertyUidBluetoothCategory in a non-secure
Symbian OS platform.

@see Bluetooth Core Specification
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothGetScanningStatus = (KUidBluetoothPubSubKeyBase + 3);

/**
KPropertyKeyBluetoothSetScanningStatus
The key to control what scans the Bluetooth hardware is currently performing
The P&S value contains an integer with the scan value as published in the Bluetooth Core Specification

The use of this key is equivalent in a secure Symbian OS platform to the use of the key
KPropertyKeyBluetoothScanning with the category KPropertyUidBluetoothControlCategory in a non-secure
Symbian OS platform.

@see Bluetooth Core Specification
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothSetScanningStatus = (KUidBluetoothPubSubKeyBase + 4);

//-------------

/**
KPropertyKeyBluetoothGetLimitedDiscoverableStatus
The key to observe whether the local device is in Limited Discoverable mode
The P&S value will contain a boolean: ETrue if in limited discoverable mode, otherwise EFalse

The use of this key is equivalent in a secure Symbian OS platform to the use of the key
KPropertyKeyBluetoothLimitedDiscoverable with the category KPropertyUidBluetoothCategory in a non-secure
Symbian OS platform.

@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothGetLimitedDiscoverableStatus = (KUidBluetoothPubSubKeyBase + 5);

/**
KPropertyKeyBluetoothSetLimitedDiscoverableStatus
The key to control whether the local device is in Limited Discoverable mode
The P&S value will contain a boolean: ETrue if in limited discoverable mode, otherwise EFalse

The use of this key is equivalent in a secure Symbian OS platform to the use of the key
KPropertyKeyBluetoothLimitedDiscoverable with the category KPropertyUidBluetoothControlCategory in a non-secure
Symbian OS platform.

@publishedAll
@released
*/

const TUint KPropertyKeyBluetoothSetLimitedDiscoverableStatus = (KUidBluetoothPubSubKeyBase + 6);


//-------------

/**
KPropertyKeyBluetoothGetDeviceClass
The key to observe the class of device of the local device
The P&S value will contain an integer of the local device class.

The use of this key is equivalent in a secure Symbian OS platform to the use of the key
KPropertyKeyBluetoothDeviceClass with the category KPropertyUidBluetoothCategory in a non-secure
Symbian OS platform.

@see Bluetooth Core Specification
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothGetDeviceClass = (KUidBluetoothPubSubKeyBase + 7);

/**
KPropertyKeyBluetoothSetDeviceClass
The key to set the class of device of the local device
The P&S value will contain an integer of the local device class.

The use of this key is equivalent in a secure Symbian OS platform to the use of the key
KPropertyKeyBluetoothDeviceClass with the category KPropertyUidBluetoothControlCategory in a non-secure
Symbian OS platform.

@see Bluetooth Core Specification
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothSetDeviceClass = (KUidBluetoothPubSubKeyBase + 8);

//-------------

/**
KPropertyKeyBluetoothSetAFHHostChannelClassification
The key to send an AFH Host Channel Classification to the local Bluetooth hardware
The P&S value will contain a descriptor containing the AFH Host Channel Classification 
bit set. A bit which is set to zero instructs the local Bluetooth hardware 
not to hop to the frequency represented by that bit in a connection in which 
it is master and which is using AFH. Also, if the local Bluetooth hardware is slave in a 
connection, which is using AFH, an AFH Host Channel Classification may be used to advise
the remote master what frequencies to avoid.

NB. THIS IS SUPPORTED ONLY IN VERSION 9.0 AND THEREAFTER. The same functionality can be
accessed in 8.1 also through the use of the KPropertyKeyBluetoothAFHHostChannelClassification
key in conjunction with category KPropertyUidBluetoothControlCategory.

@see TBTAFHHostChannelClassification
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothSetAFHHostChannelClassification = (KUidBluetoothPubSubKeyBase + 9);

/**
KPropertyKeyBluetoothAFHHostChannelClassification
This is a deprecated constant, maintained for source compatibility with non-secured 
Symbian OS platforms.

@publishedAll
@deprecated
*/
const TUint KPropertyKeyBluetoothAFHHostChannelClassification = KPropertyKeyBluetoothSetAFHHostChannelClassification;

//-------------

/**
KPropertyKeyBluetoothSetAFHChannelAssessmentMode
The key to send the Bluetooth AFH Channel Assessment Mode to the local Bluetooth hardware.
If AFH Channel Assessment Mode is on, then the local hardware will keep checking what 
channels are busy and so should be avoided in a connection using AFH.
The P&S value will contain a boolean: ETrue if AFH Channel Assessment Mode is required 
(the default if supported by the hardware), EFalse if not.
Using this key is CURRENTLY NOT SUPPORTED. The default setting of AFH Channel Assessment Mode 
(on if supported by the hardware) is considered satisfactory.
@publishedPartner
@released
*/
const TUint KPropertyKeyBluetoothSetAFHChannelAssessmentMode = (KUidBluetoothPubSubKeyBase + 10); //CURRENTLY NOT SUPPORTED 

/**
KPropertyKeyBluetoothAFHChannelAssessmentMode
This is a deprecated constant, maintained for source compatibility with non-secured 
Symbian OS platforms.

@publishedPartner
@deprecated
*/
const TUint KPropertyKeyBluetoothAFHChannelAssessmentMode = KPropertyKeyBluetoothSetAFHChannelAssessmentMode; //CURRENTLY NOT SUPPORTED 

//-------------

/**
KPropertyKeyBluetoothGetRegistryTableChange
The key to observe changes in the Bluetooth Registry
The P&S value will contain an integer describing which of the tables in the Bluetooth Registry changed
see further in this header file
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothGetRegistryTableChange = (KUidBluetoothPubSubKeyBase + 11);

/**
KPropertyKeyBluetoothRegistryTableChange
This is a deprecated constant, maintained for source compatibility with non-secured 
Symbian OS platforms.

@publishedAll
@deprecated
*/
const TUint KPropertyKeyBluetoothRegistryTableChange = KPropertyKeyBluetoothGetRegistryTableChange;

//-------------

// Some keys have values that are "wellknown" - these are enumerated here
// RegistryTableChanges

//-------------

/**
KRegistryChangeRemoteTable
@see KPropertyKeyBluetoothGetRegistryTableChange
The value in the KPropertyKeyBluetoothGetRegistryTableChange key if the Remote device table changed
@publishedAll
@released
*/
const TUint KRegistryChangeRemoteTable = (KUidBluetoothPubSubKeyBase + 12);

//-------------

/**
KRegistryChangeLocalTable
@see KPropertyKeyBluetoothGetRegistryTableChange
The value in the KPropertyKeyBluetoothGetRegistryTableChange key if the Local device table changed
@publishedAll
@released
*/
const TUint KRegistryChangeLocalTable = (KUidBluetoothPubSubKeyBase + 13);

//-------------

/**
KRegistryChangeCSYTable
@see KPropertyKeyBluetoothGetRegistryTableChange
The value in the KPropertyKeyBluetoothGetRegistryTableChange key if the CSY-settings table changed
@publishedAll
@released
*/
const TUint KRegistryChangeCSYTable = (KUidBluetoothPubSubKeyBase + 14);

//-------------

/**
KPropertyKeyBluetoothGetDeviceName
The key to observe the name of device of the local device
The P&S value will be of type EText and contain the local device name in Unicode.
At all times the name must have a length <= KHCILocalDeviceNameMaxLength (defined in hcibase.h).
@see Bluetooth Core Specification
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothGetDeviceName = (KUidBluetoothPubSubKeyBase + 15);

/**
KPropertyKeyBluetoothSetDeviceName
The key to set the name of device of the local device
The P&S value will be of type EText and contain the local device name in Unicode.
At all times the name must have a length <= KHCILocalDeviceNameMaxLength (defined in hcibase.h).
@see Bluetooth Core Specification
@publishedAll
@released
*/
const TUint KPropertyKeyBluetoothSetDeviceName = (KUidBluetoothPubSubKeyBase + 16);

//-------------

/**
KPropertyKeyBluetoothGetCorruptRegistryResetIndication
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
const TUint KPropertyKeyBluetoothGetCorruptRegistryResetIndication = (KUidBluetoothPubSubKeyBase + 17);

/**
KPropertyKeyBluetoothCorruptRegistryReset
This is a deprecated constant, maintained for source compatibility with non-secured 
Symbian OS platforms.

@publishedAll
@deprecated
*/
const TUint KPropertyKeyBluetoothCorruptRegistryReset = KPropertyKeyBluetoothGetCorruptRegistryResetIndication;
 


//BT_SUBSCRIBE_H
#endif
