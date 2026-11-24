//	MsvScheduleSettings.h
//
//	Copyright (c) Symbian Software Ltd 1999-2004.  All rights reserved. 
//

#ifndef __MSVSCHEDULESETTINGS_H__
#define __MSVSCHEDULESETTINGS_H__

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__
 
#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__


#include <msvrcpt.h>
#include <schinfo.h>
#include <msvsenderroraction.h>


#ifndef __HIDE_MESSAGING_API_V1__
const TUid KUidMsvFileScheduleSettings	= {0x100056BB}; //Used by CMsvScheduleSettings
#endif

#ifndef __HIDE_MESSAGING_API_V1__
#ifdef __CONDITIONS_SCHEDULES_VALID__
const TInt16 KMsvScheduleSettingsVersion	= 2;
#else
const TInt16 KMsvScheduleSettingsVersion	= 1;
#endif
#endif // __HIDE_MESSAGING_API_V1__

#ifndef __HIDE_MESSAGING_API_V1__
#if defined(__WINS__) && !defined(EKA2)
_LIT(KMsvDefaultSendExe, "z:\\system\\programs\\schsendexe.dll");
#else
_LIT(KMsvDefaultSendExe, "z:\\system\\programs\\schsendexe.exe");
#endif
#endif // __HIDE_MESSAGING_API_V1__

/**
Stores the MTM-specific (general) settings for scheduling messages on the
Task Scheduler. 

These settings include the latency (minimum amount of time between now and when
the message is scheduled for), the intervals (short, long or variable) to wait 
for before attempting to re-send the message and the timout value for messages
pending conditions to be met.

The other MTM scheduling releated settings are stored in CMsvOffPeakTimes 
and CMsvSendErrorActions. 

@publishedAll
@released
*/

class CMsvScheduleSettings : public CBase
	{
public:

	IMPORT_C static CMsvScheduleSettings* NewL();
#ifdef __MESSAGING_API_V2__		
	IMPORT_C static CMsvScheduleSettings* NewLC();	
#endif	// __MESSAGING_API_V2__
	IMPORT_C ~CMsvScheduleSettings();

#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C void StoreL(CMsvStore& aStore) const;
	IMPORT_C void RestoreL(CMsvStore& aStore);
#endif	// __HIDE_MESSAGING_API_V1__

	IMPORT_C void Reset();

#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C void SetSendExe(const TDesC& aSendExe);
	IMPORT_C const TDesC& SendExe() const;
#endif	// __HIDE_MESSAGING_API_V1__

	IMPORT_C void SetPriority(const TInt aPriority);
	IMPORT_C TInt Priority() const;

	IMPORT_C void SetValidityPeriod(const TTimeIntervalMinutes& aValidityPeriod);
	IMPORT_C const TTimeIntervalMinutes& ValidityPeriod() const;

	IMPORT_C void SetIntervalType(const TIntervalType aIntervalType);
	IMPORT_C TIntervalType IntervalType() const;

	IMPORT_C void SetLongInterval(const TTimeIntervalSeconds& aInterval);
	IMPORT_C const TTimeIntervalSeconds& LongInterval() const;
	
	IMPORT_C void SetShortInterval(const TTimeIntervalSeconds& aInterval);
	IMPORT_C const TTimeIntervalSeconds& ShortInterval() const;

	IMPORT_C const CArrayFixFlat<TTimeIntervalSeconds>& VariableIntervals() const;
	IMPORT_C void SetVariableIntervalsL(const CArrayFixFlat<TTimeIntervalSeconds>& aIntervals);

	IMPORT_C const TTimeIntervalMicroSeconds32& Latency() const;
	IMPORT_C void SetLatency(const TTimeIntervalMicroSeconds32& aLatency);
	
#ifdef __CONDITIONS_SCHEDULES_VALID__
	IMPORT_C void SetPendingConditionsTimeout(const TTimeIntervalMinutes& aTimeout);
	IMPORT_C const TTimeIntervalMinutes& PendingConditionsTimeout() const;
#endif

	/** Default scheduler settings values. */
	enum
		{
		/** Default priority. */
		EDefaultPriority		= 27,
		/** Default validity period: 10080 Minutes in 1 week. */
		EDefaultValidityPeriod	= 10080,
		/** Default interval type: EYearly */	
		EDefaultIntervalType	= 3,
		/** Default short retry interval. */		
		EDefaultShortInterval	= 5,
		/** Default long retry interval. */
		EDefaultLongInterval	= 120,
		/** Default latency. */
		EDefaultLatency			= 1500000,
		/** Default timeout. Zero minutes - no timeout. */
		EDefaultPendingConditionsTimeout	= 0
		};

private:
	CMsvScheduleSettings();

	void ConstructL();

#ifndef __HIDE_MESSAGING_API_V1__		
	void ExternalizeL (RWriteStream& aWriteStream) const;
    void InternalizeL (RReadStream& aReadStream);
#endif	// __HIDE_MESSAGING_API_V1__

#ifndef __REMOVE_MESSAGING_API_V1__		
	TInt16					iVersion;
	TFileName				iSendExe;		//EXE that will be called by the Task Scheduler
#endif	// __REMOVE_MESSAGING_API_V1__
	TInt					iPriority;		//Priority of the schedules on the task scheduler
	TTimeIntervalMinutes	iValidityPeriod;//Validity period of message on the task scheduler
	TIntervalType			iIntervalType;	//See TIntervalType declaration and Task Scheduler user documentation
	TTimeIntervalMicroSeconds32 iLatency;		//Minimum amount of time between now and when the message is scheduled for. Cannot be negative.
#ifdef __CONDITIONS_SCHEDULES_VALID__
	TTimeIntervalMinutes	iPendingConditionsTimeout;
#endif	// __CONDITIONS_SCHEDULES_VALID__

	TTimeIntervalSeconds iLongInterval;
	TTimeIntervalSeconds iShortInterval;
	CArrayFixFlat<TTimeIntervalSeconds>* iVariableIntervals;
	};

#endif	// __MSVSCHEDULESETTINGS_H__
