// timezone.h
//
// Copyright (c) Symbian Software Ltd 1997-2006. All rights reserved.
//

#ifndef __TIMEZONE_H__
#define __TIMEZONE_H__

#include <e32base.h>
#include <s32std.h>
#include <tzdefines.h>
#include <tzupdate.h>

class CTzChangeNotifier;
class CTzActualisedRules;
class CTzRules;
class CTzOlsenRules;
class CTzRuleHolder;

//-------------------------------------------------------------------------
/**
Encapsulates a time zone identifier.

The identifier may be either a name or a number.
@publishedAll
@released
@since 9.1
*/
// @lib "timezoneclient.lib"
class CTzId : public CBase
	{
public:

	/** 
	@internalComponent 
	*/	
	IMPORT_C ~CTzId();
	
	/** 
	@internalComponent 
	*/
	IMPORT_C CTzId* CloneL() const;
	
	/** 
	@internalComponent 
	*/
	IMPORT_C static CTzId* NewL(TUint aNumericId);
	
	/** 
	@internalComponent 
	*/
	IMPORT_C static CTzId* NewL(const TDesC8& aNameIdentity);
	
	/** 
	@internalComponent 
	*/
	IMPORT_C static CTzId* NewL(RReadStream& aStream);
	
	/** 
	@internalComponent 
	*/
	IMPORT_C void SetId(TUint aNumericId);
	
	/** 
	@internalComponent 
	*/
	IMPORT_C void SetIdL(const TDesC8& aNameIdentity);
	
	/** 
	@internalComponent 
	*/
	IMPORT_C void InternalizeL(RReadStream& aStream);
	
	/** 
	@internalComponent 
	*/
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

	/** 
	@internalComponent 
	*/
	IMPORT_C const TDesC8& TimeZoneNameID() const;
	
	/** 
	@internalComponent 
	*/
	IMPORT_C TUint TimeZoneNumericID() const;
	
	/** 
	@internalComponent 
	*/
	IMPORT_C TBool operator==(const CTzId& aTZId) const;

	inline TBool operator!=(const CTzId& aTZId) const;

public:
	static CTzId* NewL(TUint aReferenceId, const TDesC8& aZoneIdentity);
	void SetIdL(TUint aNumRefId, const TDesC8& aZoneIdentity);

private:
	void ConstructL(const TDesC8& aZoneIdentity);
	CTzId();
	CTzId(TUint aNumericId);

private:
	HBufC8* iZoneId;
	TUint32 iReferenceId;
	};


/** 
The client interface to the time zone server. 

This class performs two basic functions:
1. Converts between UTC time and local time.
2. Sets the current local time zone.

Exceptional cases occur when a user requests conversion 
for a non-existent local time or a double local time. 

Non-existent local times occur when the local time 
changes from winter to summer for DST.

For example, 01:59 local time is non-existent on the day of a change to BST
in Europe/London since the time changes directly from 12:59:59 to 2:00.

A double local time occurs when the local time changes from
summer to winter. 

For example, if the time changes at 02:00 AM BST to 01:00 AM GMT
then local times between 01:00 and 01:59 occur twice.

The conversion applies the DST offset regardless of whether the local time value 
exists or is double.

This decision makes the conversion process asymmetrical around
the discontinuity in the local time when there is a DST change.

An example conversion from a double local time to UTC and 
from UTC to a double local time is:

	01:59 AM BST => 00:59 AM UTC
	01:59 AM UTC => 01:59 AM GMT

@publishedAll
@released
@since 9.1
*/
// @lib "timezoneclient.lib"
class RTz : public RSessionBase
	{
public:
	/**
	These enumerators are to describe different modes of the automatic 
	DST event handling.

	These are used both as arguments for the API SetAutoUpdateBehaviorL, 
	and as notifications for the publish and subscribe.
	*/
	enum TTzAutoDSTUpdateModes
		{
		/** No auto update notification when a DST event occurs. */
		ETZAutoDSTUpdateOff = 0,

		/** Automatic time update will occur and the client app will be notified. */
		ETZAutoDSTUpdateOn,

		/** Client app needs to confirm that the time should be updated whenever a DST event occurs. */
		ETZAutoDSTNotificationOnly,
		};

	/**
	@internalComponent
	*/
	enum TTzChanges
		{
		ETZDatabaseChanged = 1,
		ETZSystemTimeZoneChanged,
		ETZDSTRuleChanged,
		ETZAutomaticTimeUpdate
		};

	/**
	@internalComponent
	*/
	enum TPanic
		{
		EPanicServerNotFound = 1,
		EPanicServerDead,
		EPanicTimeZoneNameIdNotSet,
		EPanicRulesIndexOutofRange,
		EPanicTimeNotCoveredByRules,
		EPanicBadTimeZoneRules,
		EPanicUnsupportedTimeReference,
		EPanicUnsupportedTimeZoneNoId,
		EPanicNotificationRequestPending,
		};
	
	/** 
	@internalComponent 
	*/
	IMPORT_C static void Panic(TPanic aPanic);
	
	/** 
	@internalTechnology 
	*/
	IMPORT_C CTzId* GetTimeZoneIdL() const;
	
	/** 
	@internalTechnology 
	*/
	IMPORT_C void SetTimeZoneL(CTzId& aZone) const;

	/** 
	@internalComponent
	*/
	IMPORT_C void Close();
	
	/** 
	@internalComponent
	*/
	IMPORT_C TInt Connect();

	/** 
	@internalComponent
	*/
	IMPORT_C ~RTz();
	
	/** 
	@internalComponent
	*/
	IMPORT_C RTz();
	
	/** 
	@internalComponent
	*/
	IMPORT_C TInt ConvertToLocalTime(TTime& aTime) const;
	
	/** 
	@internalComponent
	*/
	IMPORT_C TInt ConvertToLocalTime(TTime& aTime, const CTzId& aZone) const;

	/** 
	@internalComponent
	*/
	IMPORT_C TInt ConvertToUniversalTime(TTime& aTime) const;
	
	/** 
	@internalComponent
	*/
	IMPORT_C TInt ConvertToUniversalTime(TTime& aTime, const CTzId& aZone) const;
	
	/** 
	@internalComponent
	*/	
	IMPORT_C void GetOffsetsForTimeZoneIdsL(const RArray<TInt>& aTzNumericIds, RArray<TInt>& aOffsets) const; 
	
	/** 
	@internalComponent
	*/
	IMPORT_C TInt AutoUpdateSettingL();
	
	/** 
	@internalComponent 
	*/
    IMPORT_C void SetAutoUpdateBehaviorL(TTzAutoDSTUpdateModes aUpdateEnabled);
    
    // Methods for setting the system time.
    /** 
    @internalComponent
    */
    IMPORT_C TInt SetHomeTime(const TTime& aLocalTime) const;

	/** 
	@internalComponent
	*/
    IMPORT_C TBool IsDaylightSavingOnL(CTzId& aZone) const;

	// Get Olsen Encoded Rules for Current Local Time Zone
	/** 
	@internalComponent
	*/
    IMPORT_C CTzOlsenRules* GetTimeZoneOlsenRulesL(const TTime& aStartTime, const TTime& aEndTime, 
    												TTzTimeReference aTimeRef) const;
    
 	// Get Encoded Rules for Current Local Time Zone
 	/** 
	@internalComponent
	*/
	IMPORT_C CTzRules* GetTimeZoneRulesL(const TTime& aStartTime, const TTime& aEndTime, TTzTimeReference aTimeRef) const;
	
	/** 
	@internalComponent
	*/
	IMPORT_C CTzRules* GetTimeZoneRulesL(const CTzId& aZone, const TTime& aStartTime, const TTime& aEndTime, TTzTimeReference aTimeRef) const;
	
	CTzActualisedRules* GetActualisedTimeZoneRulesL(const TTime& aTime, TTzTimeReference aTimerRef) const;
	CTzActualisedRules* GetActualisedTimeZoneRulesL(const CTzId& aZone, const TTime& aTime, TTzTimeReference aTimerRef) const;
	void RegisterTzChangeNotifier(TRequestStatus& aStatus) const;
	TInt CancelRequestForNotice() const;
	TVersion Version() const;
	
	/** 
	@internalComponent
	*/
	IMPORT_C void NotifyHomeTimeZoneChangedL(const NTzUpdate::TTimeZoneChange& aChange) const;
	
	/** 
	@internalComponent
	*/
	IMPORT_C void SetUnknownZoneTimeL(const TTime& aUTCTime, const TInt aUTCOffset);


    TBool StartCachingL();
    TUint16 CurrentCachedTzId();

private:
	static TInt StartServer();
	TInt DoConnect();
	void doConvertL(const CTzId& aZone, TTime& aTime,
					TTzTimeReference aTimerRef) const;
	void doConvertL(TTime& aTime, 
					TTzTimeReference aTimerRef) const;
private:
	CTzRuleHolder* iRulesHolder;
	};

/**
Encapsulates a TTime and a TTzTimeReference.
Use, for example, for iCalendar's DTSTART.

@internalComponent
*/
class TTimeWithReference
	{
public:
	static inline TTimeWithReference Max();
	inline TTimeWithReference();
	inline TTimeWithReference(TTime aTime, TTzTimeReference aTimeReference=ETzUtcTimeReference);
	inline TTimeWithReference(TDateTime aTime, TTzTimeReference aTimeReference=ETzUtcTimeReference);
	inline bool operator==(const TTimeWithReference& aTime) const;
	inline bool operator!=(const TTimeWithReference& aTime) const;

	TTime iTime;
	TTzTimeReference iTimeReference;
	};

/** Inequality operator.

@param aTZId The time zone ID to compare with this one.
@return True if the two IDs are different. False if they are the same.
*/
inline TBool CTzId::operator!=(const CTzId& aTZId) const
	{
	return (!operator==(aTZId));
	}

//////////////////////////////////
// TTimeWithReference
//////////////////////////////////
inline TTimeWithReference TTimeWithReference::Max()
	{
	return TTimeWithReference(
		TDateTime(9999,EDecember,30,23,59,59,0), 
		ETzUtcTimeReference);
	}

inline TTimeWithReference::TTimeWithReference() 
		: iTime(0), iTimeReference(ETzUtcTimeReference)
	{
	}
inline TTimeWithReference::TTimeWithReference(TTime aTime, TTzTimeReference aTimeReference)
		: iTime(aTime), iTimeReference(aTimeReference)
	{
	}
inline TTimeWithReference::TTimeWithReference(TDateTime aTime, TTzTimeReference aTimeReference)
		: iTime(aTime), iTimeReference(aTimeReference)
	{
	}
inline bool TTimeWithReference::operator==(const TTimeWithReference& aTime) const
	{
	return(aTime.iTime == iTime && aTime.iTimeReference == iTimeReference);
	}
inline bool TTimeWithReference::operator!=(const TTimeWithReference& aTime) const
	{
	return(!(*this == aTime));
	}
#endif
