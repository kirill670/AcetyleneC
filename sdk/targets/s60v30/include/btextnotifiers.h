/**
BTExtNotifiers.h
Copyright (c) 2001 Symbian Ltd.  All rights reserved.
*/

#ifndef BTEXTNOTIFIERS_H
#define BTEXTNOTIFIERS_H

#include <e32std.h>
#include <bttypes.h>
#include <btdevice.h>


#define NOTIFIERS_SUPPORT_PASSKEY_MIN_LENGTH

/**
@file
@publishedAll
@released

UID to invoke the device selection dialog via the notifier framework.
**/
const TUid KDeviceSelectionNotifierUid={0x100069D1};

/**
@publishedPartner
@deprecated
@see "bt_subscribe.h"

UID to notify the UI that a bluetooth link is currently active.
Now deprecated by the publish/subscribe mechanism.
**/
const TUid KUidBTBasebandNotification={0x1000A5FB};

NONSHARABLE_CLASS(TBTDeviceSelectionParams)
/**
@publishedAll
@released

Class to allow parameters to be sent to the device selection dialog via the RNotifier API.
**/
	{
public:
	IMPORT_C TBTDeviceSelectionParams();
	IMPORT_C void SetUUID(const TUUID& aUUID);
	IMPORT_C void SetDeviceClass(TBTDeviceClass aClass);
	IMPORT_C const TUUID& UUID();
	IMPORT_C TBTDeviceClass DeviceClass();
	IMPORT_C TBool IsValidDeviceClass();
	IMPORT_C TBool IsValidUUID();
private:
	TBTDeviceClass iDeviceClass; /*!< The device class */
	TUUID iSdpUuid; /*!< The sdp uuid */
	TBool iValidDeviceClass; /*!< ETrue if iDeviceClass has been set, EFalse if not */
	TBool iValidUuid; /*!< ETrue if iSdpUuid has be set, EFalse if not */

	// This data padding has been added to help prevent future binary compatibility breaks	
	// Neither iPadding1 nor iPadding2 have been zero'd because they are currently not used
	TUint32     iPadding1; 
	TUint32     iPadding2; 	
	};

NONSHARABLE_CLASS(TBTDeviceResponseParams)
/**
@publishedAll
@released

Class to allow parameters to be received from the device selection dialog via the RNotifier API.
**/
	{
public:
	IMPORT_C TBTDeviceResponseParams();
	IMPORT_C void SetDeviceAddress(const TBTDevAddr& aBDAddr);	///< Set the address of the device
	IMPORT_C void SetDeviceName(const TDesC& aName);	///< Set the name of the device
	IMPORT_C void SetDeviceClass(TBTDeviceClass aClass);
	IMPORT_C const TBTDevAddr& BDAddr() const;				///< Returns the address of the device
	IMPORT_C const TDesC& DeviceName() const;		///< Returns the name of the device
	IMPORT_C TBTDeviceClass DeviceClass();
	IMPORT_C TBool IsValidBDAddr() const;			///< Has the address of the device been set?
	IMPORT_C TBool IsValidDeviceName() const;		///< Has the name of the device been set?
	IMPORT_C TBool IsValidDeviceClass();
private:
	TBTDevAddr iBDAddr; /*!< The BT address of the remote device */
	TBuf<KMaxBluetoothNameLen> iDeviceName; /*!< The name given by the remote device */
	TBTDeviceClass iDeviceClass; /*!< The device class */
	TBool iValidBDAddr; /*!< ETrue if iBDAddr has been set, EFalse if not */
	TBool iValidDeviceName; /*!< ETrue if iDeviceName has been set, EFalse if not */
	TBool iValidDeviceClass; /*!< ETrue if iDeviceClass has been set, EFalse if not */
	
	// This data padding has been added to help prevent future binary compatibility breaks	
	// Neither iPadding1 nor iPadding2 have been zero'd because they are currently not used	
	TUint32     iPadding1; 
	TUint32     iPadding2; 	
	};

/**
@publishedAll
@released

Typedef'ed pckgbuf to send paramaters to the device selection dialog via the notifier framework.
**/
typedef TPckgBuf<TBTDeviceSelectionParams> TBTDeviceSelectionParamsPckg;

/**
@publishedAll
@released

Typedef'ed pckgbuf to retrieve the response from the device selection dialog via the notifier framework.
**/
typedef TPckgBuf<TBTDeviceResponseParams> TBTDeviceResponseParamsPckg;

/**
@deprecated
Use TBTDeviceList::MaxNumberOfDevices() instead. Note however that 
you should call this function each time you wish to use this value
rather than storing a copy because the actual value is subject to 
change.
*/
const TUint KMaxPanDevicesForSimultaneousSelection = 8;

NONSHARABLE_CLASS(TBTDeviceList)
/**
A list of TBTDevAddrs
@note Used to pass a list of devices to which to connect.
@publishedPartner
@released
*/
	{
public:
	IMPORT_C TBTDeviceList();
	
	IMPORT_C TInt AddDevice(const TBTDevAddr& aDevAddr);
	IMPORT_C TInt GetDevice(TBTDevAddr& aDevAddr);
	IMPORT_C void Reset();
	
	IMPORT_C operator const TDesC8&();
	IMPORT_C operator TDes8&();
	
	IMPORT_C TUint MaxNumberOfDevices();
	
private:
	const static TUint KMaxDevicesForSimultaneousSelection = 8;

private:
	TInt iPosition;	// the position within the list for stateful reading
	TFixedArray<TBTDevAddr, KMaxDevicesForSimultaneousSelection> iDevices;
	TPckg<TFixedArray<TBTDevAddr, KMaxDevicesForSimultaneousSelection> > iPtr;
		
	const TBTDevAddr iKNullDevAddr;

	// This data padding has been added to help prevent future binary compatibility breaks	
	// Neither iPadding1 nor iPadding2 have been zero'd because they are currently not used
	TUint32     iPadding1; 
	TUint32     iPadding2; 	
	};

#endif // BTEXTNOTIFIERS_H
