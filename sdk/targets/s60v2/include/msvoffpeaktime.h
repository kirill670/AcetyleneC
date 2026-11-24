//	MsvOffPeakTime.h
//
//	Copyright (c) Symbian Software Ltd 1999-2004.  All rights reserved. 
//

#ifndef __MSVOFFPEAKTIME_H__
#define __MSVOFFPEAKTIME_H__

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__
 
#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__


/////////////////////////////////////////////////////////////////////////////
//
//	Constants
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __HIDE_MESSAGING_API_V1__
const TUid		KUidMsvFileOffPeak			= {0x100056BC};	//Used by CMsvOffPeakTimes

const TInt16	KMsvOffPeakTimeVersion		= 1;
const TInt16	KMsvOffPeakTimesVersion		= 1;
#endif	// __HIDE_MESSAGING_API_V1__

/////////////////////////////////////////////////////////////////////////////
//
//	TMsvOffPeakTime Declaration
//
/////////////////////////////////////////////////////////////////////////////

/**
Defines an off-peak period for message sending.

An off-peak period is specified as a start time and a duration. 

@publishedAll
@released
*/

class TMsvOffPeakTime
	{
public:
	IMPORT_C TMsvOffPeakTime();
	IMPORT_C TMsvOffPeakTime(const TDay aDay, const TInt aHour, const TInt aMinute, const TTimeIntervalMinutes aValidityPeriod);

#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C void ExternalizeL (RWriteStream &aWriteStream) const;
    IMPORT_C void InternalizeL (RReadStream &aReadStream);
#endif	// __HIDE_MESSAGING_API_V1__

	IMPORT_C void Reset();

	IMPORT_C TDay Day() const;
	IMPORT_C void SetDay(const TDay aDay);

	IMPORT_C TInt Hour() const;
	IMPORT_C void SetHour(const TInt aHour);

	IMPORT_C TInt Minute() const;
	IMPORT_C void SetMinute(const TInt aMinute);

	IMPORT_C const TTimeIntervalMinutes ValidityPeriod() const;
	IMPORT_C void SetValidityPeriod(const TTimeIntervalMinutes aValidityPeriod);

	IMPORT_C const TTime NextTimeInclusive(const TTime& aFromTime) const;

private:
#ifndef __REMOVE_MESSAGING_API_V1__
	TInt16 iVersion;
#endif	//__REMOVE_MESSAGING_API_V1__
	TDay iDay;
	TInt8 iHour;							//Start hour
	TInt8 iMinute;							//Start minute
	TTimeIntervalMinutes iValidityPeriod;	//Validity period. Must be less than 24 hours
	};

/////////////////////////////////////////////////////////////////////////////
//
//	CMsvOffPeakTimes Declaration
//
/////////////////////////////////////////////////////////////////////////////

/**
Array of off-peak time data.

This represents all the off-peak time periods in each week. 

@publishedAll
@released
*/

class CMsvOffPeakTimes : public CArrayFixFlat<TMsvOffPeakTime>
	{
public:
	IMPORT_C CMsvOffPeakTimes();

#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C void StoreL(CMsvStore& aStore) const;
	IMPORT_C void RestoreL(CMsvStore& aStore);
#endif	// __HIDE_MESSAGING_API_V1__

	IMPORT_C TInt GetNextOffPeakTime(const TTime& aFromTime, TMsvOffPeakTime& aNext, TTime& aNextTime) const;

protected:

#ifndef __HIDE_MESSAGING_API_V1__		
	void ExternalizeL (RWriteStream &aWriteStream) const;
    void InternalizeL (RReadStream &aReadStream);
#endif	// __HIDE_MESSAGING_API_V1__

private:
#ifndef __REMOVE_MESSAGING_API_V1__
	TInt16 iVersion;
#endif	// __REMOVE_MESSAGING_API_V1__
	};

#endif	// __MSVOFFPEAKTIME_H__
