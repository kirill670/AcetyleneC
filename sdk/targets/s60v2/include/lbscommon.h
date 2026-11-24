/*
* ==============================================================================
*  Name        : LbsCommon.h
*  Part of     : Mobile Location Framework/Core
*  Interface   : --
*  Description :
*   ?description_line
*  Version     :
*
*  Copyright (c) 2004 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
*
* ==============================================================================
*/
// LbsCommon.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __LBSCOMMON_H__
#define __LBSCOMMON_H__

#include <e32std.h>
#include <e32math.h>
#include <LbsRequestor.h>
#include <LbsClassTypes.h>
#include <LbsErrors.h>

// A compile time assert macro. The aExpr parameter must evaluate to an
// integer value at compile time.
// eg. sizeof(TTime) == KSizeOfTInt64
// If aExpr is false, the compiler generates an error.
// If aExpr is true, the compilation continues, and use of this macro will not
// result in any extra object code.
#define POSITION_COMPILE_TIME_ASSERT(aExpr)   typedef char assert_type[aExpr ? 1 : -1]

const TInt KPositionMaxModuleName = 20;

const TUint KPositionMaxSizeQualityItem = sizeof(TInt64);

const TUint KPositionMaxSectionFields = 10;

typedef TUid  TPositionModuleId;
const TPositionModuleId KPositionNullModuleId = {KNullUidValue};


/**
 * The base class for classes used to store position information
 */
class TPositionClassTypeBase
	{
public:
    /**
     * @return The type of the TPositionClassTypeBase-derived class
     */
	IMPORT_C TUint32 PositionClassType() const;

    /**
     * @return The size of the TPositionClassTypeBase-derived class
     */
	IMPORT_C TUint PositionClassSize() const;

protected:
	TPositionClassTypeBase();

protected:
	/** The type of the derived class */
	TUint32 iPosClassType;
	/** The size of the derived class */
	TUint iPosClassSize;
	};

class TPositionQualityItem
	{
public:
	enum TResult
		{
		EIsBetter,
		EIsEqual,
		EIsWorse
		};

	enum TValuePreference
		{
		EPreferSmallerValues,
		EPreferGreaterValues
		};

	enum TDataType
		{
		EUndefined,
		ETInt8,
		ETInt16,
		ETInt32,
		ETInt64,
		ETUint8,
		ETUint16,
		ETUint32,
		ETReal32,
		ETReal64,
		ETTime,
		ETTimeIntervalMicroSeconds
		};

	TPositionQualityItem();

	TInt Compare(const TPositionQualityItem& aItem, TResult& aComparison) const;

	void Set(TDataType aDataType, TValuePreference aValuePreference,
			 const TAny* aData, TUint aSizeOfData);

	TInt Get(TDataType aDataType, TAny* aData, TUint aSizeOfData) const;

	TBool IsDefined() const;

private:
	TDataType iDataType;
	TValuePreference iScaleDirection;
	TUint8 iData[KPositionMaxSizeQualityItem];
	};

/**
 * The base class for classes used to store position quality information
 */
class TPositionQualityBase : public TPositionClassTypeBase
	{
public:

    /**
     * Compares a specified element of another TPositionQualityBase object to this
     * TPositionQualityBase.
     *
     * @param aPositionQuality The position quality to compare against this position quality.
     * @param aElementToCompare The element number that we want to compare.
     * @param aComparison Set by this function to whether or not the TPositionQualityBase provided
     * is better or worse than this TPositionQualityBase.
     * @return KErrNone if comparison was successful.
     * @return KErrArgument if there is a mismatch of the datatypes of the value preference.
     */
	IMPORT_C TInt Compare(const TPositionQualityBase& aPositionQuality,
						  TInt aElementToCompare,
						  TPositionQualityItem::TResult& aComparison) const;

    /**
     * @return Whether or not an element has a state of EUndefined.
     */
	IMPORT_C TBool IsDefined(TInt aElementId) const;

    /**
     * @return The High Water Mark.
     */
	IMPORT_C TInt HighWaterMark() const;
protected:
	IMPORT_C TPositionQualityBase();

	IMPORT_C void ResetElement(TInt aElementId);

	template <class T>
		inline void SetElement(TInt aElementId, TPositionQualityItem::TDataType aDataType,
							   TPositionQualityItem::TValuePreference aValuePreference, T aData)
		{DoSetElement(aElementId, aDataType, aValuePreference, &aData, sizeof(T));}
	
	template <class T>
		inline TInt GetElement(TInt aElementId, TPositionQualityItem::TDataType aDataType,
							    T& aData) const
		{return DoGetElement(aElementId, aDataType, &aData, sizeof(T));}

private:
	IMPORT_C void DoSetElement(TInt aElementId, TPositionQualityItem::TDataType aDataType,
							   TPositionQualityItem::TValuePreference aValuePreference,
							   const TAny* aData, TUint aSizeOfData);

	IMPORT_C TInt DoGetElement(TInt aElementId, TPositionQualityItem::TDataType aDataType,
								TAny* aData, TUint aSizeOfData) const;
private:
	TFixedArray<TPositionQualityItem, KPositionMaxSectionFields> iPositionQualityData;
	TInt iHighwaterMark;
	};

/**
 * The standard position quality class.
 */
class TPositionQuality : public TPositionQualityBase
	{
public:
	enum TCostIndicator
		{
		ECostUnknown,
		ECostZero,
		ECostPossible,
		ECostCharge
		};

	enum TPowerConsumption
		{
		EPowerUnknown,
		EPowerZero,
		EPowerLow,
		EPowerMedium,
		EPowerHigh
		};

public:
    /**
     * Default constructor for TPositionQuality
     * Note that the horizontal accuracy and vertical accuracy are initially NaNs.
     */
	IMPORT_C TPositionQuality();

    /**
     * @return The time required to obtain an initial location fix
     */
	IMPORT_C TTimeIntervalMicroSeconds TimeToFirstFix() const;

    /**
     * @return The time required to obtain subsequent location fixes
     */
	IMPORT_C TTimeIntervalMicroSeconds TimeToNextFix()  const;  

    /**
     * @return The horizontal accuracy
     */
	IMPORT_C TReal32 HorizontalAccuracy() const;

    /**
     * @return The vertical accuracy
     */
	IMPORT_C TReal32 VerticalAccuracy()   const;

    /**
     * @return The cost indicator
     */
	IMPORT_C TCostIndicator CostIndicator() const;

    /**
     * @return The power consumption
     */
	IMPORT_C TPowerConsumption PowerConsumption() const;

    /**
     * @param aTimeToFirstFix The time required to obtain an initial location fix to set
     * Panics with "LocationClient EPositionBadTime" if aTimeToFirstFix
     * is negative.
     */
	IMPORT_C void SetTimeToFirstFix(TTimeIntervalMicroSeconds aTimeToFirstFix);

    /**
     * @param aTimeToNextFix The time required to obtain subsequent location fixes to set
     * Panics with "LocationClient EPositionBadTime" if aTimeToNextFix
     * is negative.
     */
	IMPORT_C void SetTimeToNextFix(TTimeIntervalMicroSeconds aTimeToNextFix);

    /**
     * @param aHorizontalAccuracy The horizontal accuracy to set
     * Panics with "LocationClient EPositionBadAccuracy" if aHorizontalAccuracy
     * is negative.
     */
	IMPORT_C void SetHorizontalAccuracy(TReal32 aHorizontalAccuracy);

    /**
     * @param aVerticalAccuracy The vertical accuracy to set
     * Panics with "LocationClient EPositionBadAccuracy" if aVerticalAccuracy
     * is negative.
     */
	IMPORT_C void SetVerticalAccuracy(TReal32 aVerticalAccuracy);

    /**
     * @param aCost The cost indicator to set
     */
	IMPORT_C void SetCostIndicator(TCostIndicator aCost);

    /**
     * @param aPower The power consumption to set
     */
	IMPORT_C void SetPowerConsumption(TPowerConsumption aPower);

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};


/**
 * The base class for classes storing information on position modules
 */
class TPositionModuleInfoBase : public TPositionClassTypeBase
	{
protected:
	IMPORT_C TPositionModuleInfoBase();
	};

/**
 * The standard class for storing information on position modules
 */
class TPositionModuleInfo : public TPositionModuleInfoBase
	{
public:

	typedef TUint32 TTechnologyType;
	/**
	 * Technology types
	 */
	enum _TTechnologyType
		{
		ETechnologyUnknown	= 0,
		ETechnologyTerminal	= 0x01,
		ETechnologyNetwork	= 0x02,
		ETechnologyAssisted	= 0x04
		};

	typedef TUint32 TDeviceLocation;
	/**
	 * Device locations
	 */
	enum _TDeviceLocation
		{
		EDeviceUnknown	= 0,
		EDeviceInternal	= 0x01,
		EDeviceExternal	= 0x02
		};

	typedef TUint32 TCapabilities;
	/**
	 * Position module capabilities
	 */
	enum _TCapabilities
		{
		ECapabilityNone	       = 0,
		ECapabilityHorizontal  = 0x0001,
		ECapabilityVertical    = 0x0002,
		ECapabilitySpeed       = 0x0004,
		ECapabilityDirection   = 0x0008,
		ECapabilitySatellite   = 0x0010,
		ECapabilityCompass     = 0x0020,
		ECapabilityNmea        = 0x0040,
		ECapabilityAddress     = 0x0080,
		ECapabilityBuilding    = 0x0100,
		ECapabilityMedia       = 0x0200
		};

public:
    /**
     * Default constructor for TPositionModuleInfo
     */
	IMPORT_C TPositionModuleInfo();

    /**
     * @return The module ID
     */
	IMPORT_C TPositionModuleId ModuleId() const;

    /**
     * @return Whether or not this module is available
     */
	IMPORT_C TBool IsAvailable() const;

    /**
     * @param aModuleName The descriptor where the module's name will be placed
     */
	IMPORT_C void GetModuleName(TDes& aModuleName) const;

    /**
     * @param aPosQuality The quality of the position
     */
	IMPORT_C void GetPositionQuality(TPositionQuality& aPosQuality) const;

    /**
     * @return The technology type
     */
	IMPORT_C TTechnologyType TechnologyType() const;

    /**
     * @return The location of the positioning device associated with this module
     */
	IMPORT_C TDeviceLocation DeviceLocation() const;

    /**
     * @return The capabilities of this module
     */
	IMPORT_C TCapabilities Capabilities() const ;

    /**
     * @return The classes supported
     */
	IMPORT_C TUint32 ClassesSupported(TPositionClassFamily aClassType) const;

    /**
     * @return The version of the module
     */
	IMPORT_C TVersion Version() const;

    /**
     * @param aModuleId The module ID to set
     */
	IMPORT_C void SetModuleId(TPositionModuleId aModuleId);

    /**
     * @param aIsAvailable Whether or not the module is available for use
     */
	IMPORT_C void SetIsAvailable(TBool aIsAvailable);

    /**
     * @param aModuleName The module name to set
     */
	IMPORT_C void SetModuleName(const TDesC& aModuleName);

    /**
     * @param aPosQuality The position quality to set
     */
	IMPORT_C void SetPositionQuality(const TPositionQuality& aPosQuality);

    /**
     * @param aTechnologyType The technology type to set
     */
	IMPORT_C void SetTechnologyType(TTechnologyType aTechnologyType);

    /**
     * @param aDeviceLocation The positioning device location to set
     */
	IMPORT_C void SetDeviceLocation(TDeviceLocation aDeviceLocation);

    /**
     * @param aCapabilities Bitfield of the capabilities of this module to set
     */
	IMPORT_C void SetCapabilities(TCapabilities aDeviceCapabilities);

    /**
     * @param aClassType The class type
     * @param aSupportedClasses The supported classes
     */
	IMPORT_C void SetClassesSupported(TPositionClassFamily aClassType,
									  TUint32 aSupportedClasses);

    /**
     * @param aVersion The version to set
     */
	IMPORT_C void SetVersion(TVersion aVersion);

protected:
	/** The module ID */
	TPositionModuleId	iModuleId;
	/** Whether or not the module is available */
	TBool iIsAvailable;
	/** The module name */
	TBuf<KPositionMaxModuleName> iModuleName;
	/** The position quality */
	TPositionQuality    iPosQuality;
	/** The technology type */
	TTechnologyType     iTechnologyType;
	/** The location of the device associated with this module */
	TDeviceLocation     iDeviceLocation;
	/** The capabilities of this module */
	TCapabilities		iCapabilities;
	/** The array of supported classes for the different class types */
	TFixedArray<TUint32, EPositionLastFamily> iSupportedClassTypes;
	/** The version of this module */
	TVersion            iVersion;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};


/**
 * The base class for classes storing a position module's status
 */
class TPositionModuleStatusBase : public TPositionClassTypeBase
	{
protected:
	IMPORT_C TPositionModuleStatusBase();
	};

/**
 * The normal class for storing a position module's status
 */
class TPositionModuleStatus : public TPositionModuleStatusBase
	{
public:
	typedef TInt TDeviceStatus;

	/**
	 * The device status
	 */
	enum _TDeviceStatus 
		{
		EDeviceUnknown,
		EDeviceError,
		EDeviceDisabled,
		EDeviceInactive,
		EDeviceInitialising,
		EDeviceStandBy,
		EDeviceReady,
		EDeviceActive
		};

	typedef TInt TDataQualityStatus;

	/**
	 * The data quality status
	 */
	enum _TDataQualityStatus
		{
		EDataQualityUnknown,
		EDataQualityLoss,
		EDataQualityPartial,
		EDataQualityNormal
		};

    /**
     * Default constructor for TPositionModuleStatus
     */
	IMPORT_C TPositionModuleStatus();

    /**
     * @return The module's device status
     */
	IMPORT_C TDeviceStatus DeviceStatus() const;

    /**
     * @return  The data quality status
     */
	IMPORT_C TDataQualityStatus DataQualityStatus() const;

    /**
     * @param aStatus The device status to set
     */
	IMPORT_C void SetDeviceStatus(TDeviceStatus aStatus);

    /**
     * @param The data quality status to set
     */
	IMPORT_C void SetDataQualityStatus(TDataQualityStatus aStatus);
	
protected:
	/** The device status */
	TDeviceStatus      iDeviceStatus;
	/** The data quality status */
	TDataQualityStatus iDataQualityStatus;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[8];
	};


/**
 * The base class for classes storing position module status events
 */
class TPositionModuleStatusEventBase : public TPositionClassTypeBase
	{
public:
	typedef TUint32 TSystemModuleEvent;

	/**
	 * Module events
	 */
	enum _TSystemModuleEvent
		{
		ESystemUnknown				= 0,
		ESystemError,
		ESystemModuleInstalled,
		ESystemModuleRemoved
		};
	
	typedef TUint32 TModuleEvent;

	/**
	 * Module events
	 */
	enum _TModuleEvent
		{
		EEventNone				= 0,
		EEventDeviceStatus      = 0x01,
		EEventDataQualityStatus = 0x02,
		EEventSystemModuleEvent = 0x04,
		EEventAll				= EEventDeviceStatus |
								  EEventDataQualityStatus |
								  EEventSystemModuleEvent
		};

protected:
	IMPORT_C TPositionModuleStatusEventBase();
	IMPORT_C TPositionModuleStatusEventBase(TModuleEvent aRequestedEventMask);

public:
    /**
     * @param aRequestedEventMask The requested events to set
     */
	IMPORT_C void SetRequestedEvents(TModuleEvent aRequestedEventMask);

    /**
     * @return The requested events
     */
	IMPORT_C TModuleEvent RequestedEvents() const;

    /**
     * @param aOccurredEventMask The occurred events to set
     */
	IMPORT_C void SetOccurredEvents(TModuleEvent aOccurredEventMask);

    /**
     * @return The events which have occurred
     */
	IMPORT_C TModuleEvent OccurredEvents() const;

    /**
     * @return The module ID
     */
	IMPORT_C TPositionModuleId ModuleId() const;

    /**
     * @param aModuleId The module ID to set
     */
	IMPORT_C void SetModuleId(TPositionModuleId aModuleId);

    /**
     * @param aSystemModuleEvent The system event to set.
     */
	IMPORT_C void SetSystemModuleEvent(TSystemModuleEvent aSystemModuleEvent);

    /**
     * @return The system event type.
     */
	IMPORT_C TSystemModuleEvent SystemModuleEvent() const;

protected:
	IMPORT_C virtual void DoReset(TInt aSizeOfClass);

private:
	friend class RPositionServer;
	void Reset();

protected:
	/** A bitmask of the requested events */
	TModuleEvent iRequestedEvents;
	/** A bitmask of the events which occurred */
	TModuleEvent iOccurredEvents;
	/** System level module status events*/
	TSystemModuleEvent iSystemModuleEvent;
	/** The module ID causing the event*/
	TPositionModuleId  iModuleId;
	};

/**
 * The normal class for storing position module status events
 */
class TPositionModuleStatusEvent : public TPositionModuleStatusEventBase
	{
public:
    /**
     * Default constructor for TPositionModuleStatusEvent
     */
	IMPORT_C TPositionModuleStatusEvent();

    /**
     * Constructor for TPositionModuleStatusEvent (with events)
     * @param aRequestedEventMask The requested events
     */
	IMPORT_C TPositionModuleStatusEvent(TModuleEvent aRequestedEventMask);

    /**
     * @param aModuleStatus The module status to set
     */
	IMPORT_C void SetModuleStatus(const TPositionModuleStatus& aModuleStatus);

    /**
     * @param aModuleStatus Where the module status will be written to
     */
	IMPORT_C void GetModuleStatus(TPositionModuleStatus& aModuleStatus) const;

protected:
	IMPORT_C virtual void DoReset(TInt aSizeOfClass);

protected:
	/** The module status */
	TPositionModuleStatus iModuleStatus;
	};


/**
 * The base class for classes storing position update options
 */
class TPositionUpdateOptionsBase : public TPositionClassTypeBase
	{
protected:
	IMPORT_C TPositionUpdateOptionsBase();
	IMPORT_C TPositionUpdateOptionsBase(TTimeIntervalMicroSeconds aInterval,
	                                    TTimeIntervalMicroSeconds aTimeOut = TTimeIntervalMicroSeconds(0),
	                                    TTimeIntervalMicroSeconds aMaxAge = TTimeIntervalMicroSeconds(0));

public:
    /**
     * @param aInterval The update interval to be set
     * @return KErrArgument if aInterval is negative, KErrNone otherwise.
     * Panics with "LocationClient EPositionBadTime" if aInterval is negative.
     */
	IMPORT_C void SetUpdateInterval(TTimeIntervalMicroSeconds aInterval);

    /**
     * @param aTimeOut The update timeout to be set
     * Panics with "LocationClient EPositionBadTime" if aTimeOut is negative.
     */
	IMPORT_C void SetUpdateTimeOut(TTimeIntervalMicroSeconds aTimeOut);

    /**
     * @param aMaxAge The maximum update age to be set
     * Panics with "LocationClient EPositionBadTime" if aMaxAge is negative.
     */
	IMPORT_C void SetMaxUpdateAge(TTimeIntervalMicroSeconds aMaxAge);

    /**
     * @return The update interval
     */
	IMPORT_C TTimeIntervalMicroSeconds UpdateInterval() const;

    /**
     * @return The update timeout
     */
	IMPORT_C TTimeIntervalMicroSeconds UpdateTimeOut() const;

    /**
     * @return The maximum update age
     */
	IMPORT_C TTimeIntervalMicroSeconds MaxUpdateAge() const;

protected:
	/** The update interval */
	TTimeIntervalMicroSeconds iUpdateInterval;
	/** The update timeout */
	TTimeIntervalMicroSeconds iUpdateTimeOut;
	/** The maximum update age */
	TTimeIntervalMicroSeconds iMaxUpdateAge;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[8];
	};

/**
 * The normal class for storing position update options
 */
class TPositionUpdateOptions : public TPositionUpdateOptionsBase
	{
public:

    /**
     * Default constructor for TPositionUpdateOptions
     */
	IMPORT_C TPositionUpdateOptions();

    /**
     * Constructor for TPositionUpdateOptions. All parameters except aInterval
     * have default values.
     *
     * @param aInterval The update interval to be set.
     * @param aTimeOut The update timeout to be set. Defaults to zero.
     * @param aMaxAge The maximum update age to be set. Defaults to zero.
     * @param aAcceptPartialUpdates Whether partial updates will be accepted.
     * Defaults to false.
     */
	IMPORT_C TPositionUpdateOptions(TTimeIntervalMicroSeconds aInterval,
	                                TTimeIntervalMicroSeconds aTimeOut = TTimeIntervalMicroSeconds(0),
	                                TTimeIntervalMicroSeconds aMaxAge = TTimeIntervalMicroSeconds(0),
	                                TBool aAcceptPartialUpdates = EFalse);

    /**
     * @param aAcceptPartialUpdates Whether partial updates will be accepted
     */
	IMPORT_C void SetAcceptPartialUpdates(TBool aAcceptPartialUpdates);

    /**
     * @return ETrue if partial updates are accepted, EFalse otherwise
     */
	IMPORT_C TBool AcceptPartialUpdates() const;

protected:
	/** Whether partial updates are accepted */
	TBool iAcceptPartialUpdates;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};


#endif //__LBSCOMMON_H__
