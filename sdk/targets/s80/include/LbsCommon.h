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


class TPositionClassTypeBase
/**
 * The base class for classes used to store position information
 *
 * @publishedAll
 */
	{
public:
	IMPORT_C TUint32 PositionClassType() const;
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

class TPositionQualityBase : public TPositionClassTypeBase
/**
 * The base class for classes used to store position quality information
 *
 * @publishedAll
 */
	{
public:
	IMPORT_C TInt Compare(const TPositionQualityBase& aPositionQuality,
						  TInt aElementToCompare,
						  TPositionQualityItem::TResult& aComparison) const;

	IMPORT_C TBool IsDefined(TInt aElementId) const;
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

class TPositionQuality : public TPositionQualityBase
/**
 * The standard position quality class.
 *
 * @publishedAll
 */
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
	IMPORT_C TPositionQuality();

	IMPORT_C TTimeIntervalMicroSeconds TimeToFirstFix() const;
	IMPORT_C TTimeIntervalMicroSeconds TimeToNextFix()  const;  

	IMPORT_C TReal32 HorizontalAccuracy() const;
	IMPORT_C TReal32 VerticalAccuracy()   const;

	IMPORT_C TCostIndicator CostIndicator() const;
	IMPORT_C TPowerConsumption PowerConsumption() const;

	IMPORT_C void SetTimeToFirstFix(TTimeIntervalMicroSeconds aTimeToFirstFix);
	IMPORT_C void SetTimeToNextFix(TTimeIntervalMicroSeconds aTimeToNextFix);

	IMPORT_C void SetHorizontalAccuracy(TReal32 aHorizontalAccuracy);
	IMPORT_C void SetVerticalAccuracy(TReal32 aVerticalAccuracy);

	IMPORT_C void SetCostIndicator(TCostIndicator aCost);
	IMPORT_C void SetPowerConsumption(TPowerConsumption aPower);

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};


class TPositionModuleInfoBase : public TPositionClassTypeBase
/**
 * The base class for classes storing information on position modules
 *
 * @publishedAll
 */
	{
protected:
	IMPORT_C TPositionModuleInfoBase();
	};

class TPositionModuleInfo : public TPositionModuleInfoBase
/**
 * The standard class for storing information on position modules
 *
 * @publishedAll
 */
	{
public:
	/**
	 * Technology types
	 */
	typedef TUint32 TTechnologyType;
	enum _TTechnologyType
		{
		ETechnologyUnknown	= 0,
		ETechnologyTerminal	= 0x01,
		ETechnologyNetwork	= 0x02,
		ETechnologyAssisted	= 0x04
		};

	/**
	 * Device locations
	 */
	typedef TUint32 TDeviceLocation;
	enum _TDeviceLocation
		{
		EDeviceUnknown	= 0,
		EDeviceInternal	= 0x01,
		EDeviceExternal	= 0x02
		};

	/**
	 * Position module capabilities
	 */
	typedef TUint32 TCapabilities;
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
	IMPORT_C TPositionModuleInfo();

	IMPORT_C TPositionModuleId ModuleId() const;
	IMPORT_C TBool IsAvailable() const;
	IMPORT_C void GetModuleName(TDes& aModuleName) const;
	IMPORT_C void GetPositionQuality(TPositionQuality& aPosQuality) const;
	IMPORT_C TTechnologyType TechnologyType() const;
	IMPORT_C TDeviceLocation DeviceLocation() const;
	IMPORT_C TCapabilities Capabilities() const ;
	IMPORT_C TUint32 ClassesSupported(TPositionClassFamily aClassType) const;
	IMPORT_C TVersion Version() const;

	IMPORT_C void SetModuleId(TPositionModuleId aModuleId);
	IMPORT_C void SetIsAvailable(TBool aIsAvailable);
	IMPORT_C void SetModuleName(const TDesC& aModuleName);
	IMPORT_C void SetPositionQuality(const TPositionQuality& aPosQuality);
	IMPORT_C void SetTechnologyType(TTechnologyType aTechnologyType);
	IMPORT_C void SetDeviceLocation(TDeviceLocation aDeviceLocation);
	IMPORT_C void SetCapabilities(TCapabilities aDeviceCapabilities);
	IMPORT_C void SetClassesSupported(TPositionClassFamily aClassType,
									  TUint32 aSupportedClasses);
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


class TPositionModuleStatusBase : public TPositionClassTypeBase
/**
 * The base class for classes storing a position module's status
 *
 * @publishedAll
 */
	{
protected:
	IMPORT_C TPositionModuleStatusBase();
	};

class TPositionModuleStatus : public TPositionModuleStatusBase
/**
 * The normal class for storing a position module's status
 *
 * @publishedAll
 */
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

	IMPORT_C TPositionModuleStatus();

	IMPORT_C TDeviceStatus DeviceStatus() const;
	IMPORT_C TDataQualityStatus DataQualityStatus() const;

	IMPORT_C void SetDeviceStatus(TDeviceStatus aStatus);
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


class TPositionModuleStatusEventBase : public TPositionClassTypeBase
/**
 * The base class for classes storing position module status events
 *
 * @publishedAll
 */
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
	IMPORT_C void SetRequestedEvents(TModuleEvent aRequestedEventMask);
	IMPORT_C TModuleEvent RequestedEvents() const;

	IMPORT_C void SetOccurredEvents(TModuleEvent aOccurredEventMask);
	IMPORT_C TModuleEvent OccurredEvents() const;

	IMPORT_C TPositionModuleId ModuleId() const;
	IMPORT_C void SetModuleId(TPositionModuleId aModuleId);

	IMPORT_C void SetSystemModuleEvent(TSystemModuleEvent aSystemModuleEvent);
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

class TPositionModuleStatusEvent : public TPositionModuleStatusEventBase
/**
 * The normal class for storing position module status events
 *
 * @publishedAll
 */
	{
public:
	IMPORT_C TPositionModuleStatusEvent();
	IMPORT_C TPositionModuleStatusEvent(TModuleEvent aRequestedEventMask);

	IMPORT_C void SetModuleStatus(const TPositionModuleStatus& aModuleStatus);
	IMPORT_C void GetModuleStatus(TPositionModuleStatus& aModuleStatus) const;

protected:
	IMPORT_C virtual void DoReset(TInt aSizeOfClass);

protected:
	/** The module status */
	TPositionModuleStatus iModuleStatus;
	};


class TPositionUpdateOptionsBase : public TPositionClassTypeBase
/**
 * The base class for classes storing position update options
 *
 * @publishedAll
 */
	{
protected:
	IMPORT_C TPositionUpdateOptionsBase();
	IMPORT_C TPositionUpdateOptionsBase(TTimeIntervalMicroSeconds aInterval,
	                                    TTimeIntervalMicroSeconds aTimeOut = TTimeIntervalMicroSeconds(0),
	                                    TTimeIntervalMicroSeconds aMaxAge = TTimeIntervalMicroSeconds(0));

public:
	IMPORT_C void SetUpdateInterval(TTimeIntervalMicroSeconds aInterval);
	IMPORT_C void SetUpdateTimeOut(TTimeIntervalMicroSeconds aTimeOut);
	IMPORT_C void SetMaxUpdateAge(TTimeIntervalMicroSeconds aMaxAge);

	IMPORT_C TTimeIntervalMicroSeconds UpdateInterval() const;
	IMPORT_C TTimeIntervalMicroSeconds UpdateTimeOut() const;
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

class TPositionUpdateOptions : public TPositionUpdateOptionsBase
/**
 * The normal class for storing position update options
 *
 * @publishedAll
 */
	{
public:
	IMPORT_C TPositionUpdateOptions();
	IMPORT_C TPositionUpdateOptions(TTimeIntervalMicroSeconds aInterval,
	                                TTimeIntervalMicroSeconds aTimeOut = TTimeIntervalMicroSeconds(0),
	                                TTimeIntervalMicroSeconds aMaxAge = TTimeIntervalMicroSeconds(0),
	                                TBool aAcceptPartialUpdates = EFalse);

	IMPORT_C void SetAcceptPartialUpdates(TBool aAcceptPartialUpdates);
	IMPORT_C TBool AcceptPartialUpdates() const;

protected:
	/** Whether partial updates are accepted */
	TBool iAcceptPartialUpdates;

private:
	/** Unused variable for future expansion. */
	TUint8 iReserved[16];
	};


#endif //__LBSCOMMON_H__
