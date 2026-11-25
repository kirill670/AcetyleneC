// V32MMCV.H
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __V32MMCV_H__
#define __V32MMCV_H__
#include <p32mmc.h>

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
class MCotullaMediaChangeObserver
	{
	public:
		/// Called to notify a media change
		virtual void MediaChange() = 0;
	};


/**
 * Mixin defining the interface of a power check observer
 */
class MCotullaPowerCheckObserver
	{
	public:
		/// Notification that voltage is stable
		virtual void VoltageCheckResult( TBool aVoltageOk ) = 0;
	};


/**
 * Abstract definition of variant layer MMC API
 */
class DMMCControllerIsaInterface : public CBase
	{
public:
	IMPORT_C TInt Create();
    virtual void PeriphBusMachineInfo(TDes8* anInfo)=0;
    
	/// Initialization function
	virtual void InitL() = 0;

	/// Return name of interrupt to bind to
	virtual const TDesC8& Interrupt1Name() const = 0;

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

	/// Request Cotulla voltage control index for request voltage
	/// (Requested voltage is in OCD format)
	virtual TUint ConvertVoltageToCotulla( TUint32 aRequestVoltageOcd ) = 0;

	/// Notify power down
	virtual void NotifyPowerDown() = 0;

	/// Request notification of stable volage. Waits until the voltage is stable
	virtual void RequestVoltageOkNotification( MCotullaPowerCheckObserver* aObserver ) = 0;

	/// Request a synchronous voltage check. This should be fast
	virtual TInt SynchronousVoltageCheck() = 0;

	/// Detect whether a card is present
	virtual TBool CardPresent() = 0;

	/// Request media change notification
	virtual void RequestMediaChangeNotify( MCotullaMediaChangeObserver* aObserver ) = 0;

	/// Cancel media change notification
	virtual void CancelMediaChangeNotify() = 0;
	
	virtual TPBusNum PeriphBusFromMediaDevice(TMediaDevice aDevice)=0;
	virtual TInt MediaChangeFromPeriphBus(TPBusNum aBus)=0;
	virtual TInt MediaChangeFromPrimaryPsu(TInt aPsuNum)=0;
	virtual TPtrC8 MediaChangeIntSource(TInt aMediaChange)=0;
	virtual void ClearMediaChangeInt(TInt aMediaChange)=0;
	virtual TMediaState MediaState(TInt aMediaChange)=0;
	};

#endif
