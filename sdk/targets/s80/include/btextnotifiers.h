// BTExtNotifiers.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef BTEXTNOTIFIERS_H
#define BTEXTNOTIFIERS_H

#include <e32std.h>
#include <bttypes.h>
#include <btdevice.h>

/** Device selection plug-in: allows the user to select a device from a list of 
the devices present in the surrounding environment. */
const TUid KDeviceSelectionNotifierUid={0x100069D1};
const TUid KUidBTBasebandNotification={0x1000A5FB};
class TBTDeviceSelectionParams
/** Allows parameters to be sent to the device selection dialog via the RNotifier 
API.

Device information is used to form a list of possible devices from which the 
user can select the appropriate device.

Either the device class or the SDP UUID may be left blank. The device selection 
plug-in must perform a device search relating to the information passed in, 
although the search need not be constrained by this. */
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
	TBTDeviceClass iDeviceClass;
	TUUID iSdpUuid;
	TBool iValidDeviceClass;
	TBool iValidUuid;
	};

class TBTDeviceResponseParams
/** Information about the device selected by a user from a Device Selection dialog.

You can use the tester functions to test if the response contains the device 
address/name/class.

@see TBTDeviceSelectionParamsPckg */
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
	TBTDevAddr iBDAddr; 				///< The BT address of the remote device
	TBTDeviceName iDeviceName; 			///< The name given by the remote device
	TBTDeviceClass iDeviceClass;
	TBool iValidBDAddr;
	TBool iValidDeviceName;
	TBool iValidDeviceClass;
	};


class TBTBasebandNotificationParams
/** Enables the passing of baseband connection event information to an extended 
notifier. */
	{
public:
	
/** Baseband connection event types. */
	enum TBasebandEvent
		{
	/** Disconnection. */
		EBasebandDisconnect,
	/** Connection attempt. */
		EBasebandConnectAttempt,
	/** Failed connection attempt. */
		EBasebandConnectAttemptFailure,
	/** Successful connection attempt. */
		EBasebandConnectAttemptSuccess
		};

	//	Construction
	IMPORT_C TBTBasebandNotificationParams();
	IMPORT_C TBTBasebandNotificationParams(TBasebandEvent aEvent, TInt aNumConnections);
	
	IMPORT_C TBasebandEvent BasebandEvent() const;
	IMPORT_C TInt CurrentConnections() const;
	
	/** Sets the baseband event.
	
	@param aEvent The baseband event to set. */
	IMPORT_C void SetBasebandEvent(TBasebandEvent aEvent);
	IMPORT_C void SetCurrentConnections(TInt aCurrentConnections);

private:
	TBasebandEvent  iBasebandEvent;
	TInt			iCurrentConnections;
	};

/** Packages a TBTDeviceSelectionParams for transfer over an IPC boundary.

@see TBTDeviceSelectionParams */
typedef TPckgBuf<TBTDeviceSelectionParams> TBTDeviceSelectionParamsPckg;
/** Packages a TBTDeviceResponseParams for transfer over an IPC boundary. */
typedef TPckgBuf<TBTDeviceResponseParams> TBTDeviceResponseParamsPckg;
/** Packages a TBTBasebandNotificationParams for transfer over an IPC boundary. */
typedef TPckgBuf<TBTBasebandNotificationParams> TBTBasebandNotificationParamsPckg;

#endif