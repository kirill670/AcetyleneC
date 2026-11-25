// V32PL180.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __V32PL180_H__
#define __V32PL180_H__
#include <e32std.h>
#include <e32pccd.h>

//
// Abstract class definition for the variant-layer MMC functions
// Custom class provides a function which creates and returns an
// implementation of this.
//
// The owner must provide a MPL180VariantObserver to handle notifications
//

/**
 * Mixin defining the interface of a media change observer
 */
class MPL180MediaChangeObserver
	{
	public:
		/// Called to notify a media change
		virtual void MediaChange() = 0;
	};


/**
 * Mixin defining the interface of a power check observer
 */
class MPL180PowerCheckObserver
	{
	public:
		/// Notification that voltage is stable
		virtual void VoltageCheckResult( TBool aVoltageOk ) = 0;
	};


/**
 * Abstract definition of variant layer MMC API
 */
class DPL180VariantMmc : public CBase
	{
public:
	/// Initialization function
	virtual void InitL() = 0;

	/// Return name of interrupt to bind to
	virtual const TDesC8& Interrupt1Name() const = 0;
	virtual const TDesC8& Interrupt2Name() const = 0;

	/// Return number of card slots
	virtual TUint PhysicalCardSlots() = 0;

	/// Return supported voltages in OCD format
	virtual TUint32	SupportedVoltages() = 0;

	/// Return inactivity timeout (0 = use the default)
	virtual TUint InactivityPowerTimeoutSeconds() = 0;

	/// Convert requested frequency to PL18X divider setting
	virtual TUint GetDividerValue( TUint aFreqkHz ) = 0;

	/// Request for power up
	virtual void RequestPowerUp() = 0;

	/// Request PL180 voltage control index for request voltage
	/// (Requested voltage is in OCD format)
	virtual TUint ConvertVoltageToPL180( TUint32 aRequestVoltageOcd ) = 0;

	/// Notify power down
	virtual void NotifyPowerDown() = 0;

	/// Request notification of stable volage. Waits until the voltage is stable
	virtual void RequestVoltageOkNotification( MPL180PowerCheckObserver* aObserver ) = 0;

	/// Request a synchronous voltage check. This should be fast
	virtual TInt SynchronousVoltageCheck() = 0;

	/// Detect whether a card is present
	virtual TBool CardPresent() = 0;

	/// Request media change notification
	virtual void RequestMediaChangeNotify( MPL180MediaChangeObserver* aObserver ) = 0;

	/// Cancel media change notification
	virtual void CancelMediaChangeNotify() = 0;
	};



#endif

