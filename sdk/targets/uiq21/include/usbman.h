/** @file usbman/Inc/UsbMan.h
 *
 * RUsb Client side header
 * Implements the Symbian OS USB Management API RUsb
 *
 * Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
 */

#ifndef __USBMAN_H__
#define __USBMAN_H__

#include <e32base.h>
#include <e32std.h>
#include <e32svr.h>

/**
 * Enumeration of all the USB service state
 */
enum TUsbServiceState
	{
	EUsbServiceIdle        = 0x01,
	EUsbServiceStarting    = 0x02,
	EUsbServiceStarted     = 0x04,
	EUsbServiceStopping    = 0x08,
	};

/**
 * Enumeration of all of the states of the USB device
 * The states reported are dependent on the hardware.
 * *** If this changes update KUsbDeviceStates below
 */
enum TUsbDeviceState
	{
	EUsbDeviceStateUndefined  = 0x00,
	EUsbDeviceStateDefault    = 0x01,
	EUsbDeviceStateAttached   = 0x02,
	EUsbDeviceStatePowered    = 0x04,
	EUsbDeviceStateConfigured = 0x08,
	EUsbDeviceStateAddress    = 0x10,
	EUsbDeviceStateSuspended  = 0x20
	};

/**
 * Number of different USB Device States
 */
const TInt	KUsbDeviceStates = 7;

/**
 * The UsbMan class
 *
 * Implements the thread handling and launch of the Symbian OS server
 */
class UsbMan
	{
public:
	class TSignal
		{
		friend class UsbMan;
	public:
		inline TSignal() {}
		inline TInt Set(const TDesC& aCommand);
		inline TSignal(TRequestStatus& aStatus);
		inline TPtrC Command() const;
	private:
		TRequestStatus* iStatus;
		TThreadId iId;
		};
public:
	static TInt Start();
	IMPORT_C static TInt Run(TSignal& aSignal);
private:
	static TInt Init();
	};


/**
 * The RUsb class
 *
 * Implements the Symbian OS USB Management API RUsb
 */
class RUsb : public RSessionBase
	{
public:

	/**
	 * Constructor
	 *
	 * @public
	 * @since 7.0
	 */
	IMPORT_C RUsb();

	/**
	 * Destructor
	 *
	 * @public
	 * @since 7.0
	 */
	IMPORT_C ~RUsb();

	/**
	 * Extract the version of the server providing the RUsb API
	 *
	 * @public
	 * @since 7.0
	 *
	 * @return	Version of the server
	 */
	IMPORT_C TVersion Version() const;

	/**
	 * Connect the Handle to the Server
	 * Must be called before all other methods except Version()
	 *
	 * @public
	 * @since 7.0
	 *
	 * @return	KErrNone if successful, otherwise the error that occurred
	 */
	IMPORT_C TInt Connect();

	/**
	 * Start the device's USB service. Should not be called if the USB services
	 * have already been started
	 * Note: Asynchonous Version, outcome returned when the status is completed
	 * 
	 * @public
	 * @since 7.0
	 * @param	aStatus		Status to complete once the start operation has completed
	 */
	IMPORT_C void Start(TRequestStatus& aStatus);

	/**
	 * The RUsb::StartCancel method
	 *
	 * Cancels the pending start operation of the device's USB service.
	 *
	 * @public
	 * @since 7.0
	 */
	IMPORT_C void StartCancel();

	/**
	 * Stop the device's USB service. Should not be called if the USB services
	 * have not been started
	 * 
	 * @public
	 * @since 7.0
	 */
	IMPORT_C void Stop();

	/**
	 * Get the current state of the device's USB service
	 *
	 * @public
	 * @since 7.0
	 * @param	aState	Set by the method to the current state of the USB service
	 *
	 * @return	KErrNone if successful, otherwise the error that occurred
	 */
	IMPORT_C TInt GetCurrentState(TUsbServiceState& aState);

	/**
	 * Request to be notified of a change in state of the USB device
	 * Note: Asynchonous Version, outcome returned when the status is completed
	 * @public
	 * @since 7.0
	 * @param	aStateMask	State mask of the states the client is interested in	
	 * @param	aState		State variable to be written to upon completion of the request
	 * @param	aStatus		Status to complete when required state change occurs
	 */
	IMPORT_C void StateNotification(TUint aStateMask, TUsbDeviceState& aState, TRequestStatus& aStatus);

	/**
	 * Cancel the  outstanding State notification status
	 *
	 * @public
	 * @since 7.0
	 */
	IMPORT_C void StateNotificationCancel();

protected:
	/**
	 * Perform the connect to the server
	 *
	 * @public
	 * @since 7.0
	 *
	 * @return	KErrNone if successful, otherwise the error that occurred
	 */
	TInt DoConnect();

private:
	TPckg<TUint32> iStatePkg;
	};

#include "usbman.inl"

#endif
