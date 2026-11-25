///////////////////////////////////////////////////////////////////////////
// T32ALM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
// Written by BLB, June 1995
///////////////////////////////////////////////////////////////////////////

/** @file
@publishedAll
@deprecated */

#ifndef __T32ALM_H__
#define __T32ALM_H__


#ifndef __E32BASE_H__
#include <e32base.h>
#endif

const TInt KAlarmServerMajorVN=1;
const TInt KAlarmServerMinorVN=1;
const TInt KAlarmServerBuildVN=80;
//
/** Defines a null alarm identifier. */
const TInt KNullAlarmID=-1;
/** The maximum number of clock alarms.

This interface is deprecated, and is made available to provide binary compatibility 
with Symbian OS v6.1. Developers are strongly advised not to use this API 
in new applications. */
const TInt KMaxClockAlarms=8;
const TInt KMaxAlarmMessage=0x80;
const TInt KMaxAlarmSoundName=0x20;
/** The maximum number of review alarms.

This interface is deprecated, and is made available to provide binary compatibility 
with Symbian OS v6.1. Developers are strongly advised not to use this API 
in new applications. */
const TInt KMaxAcknowledgeReviewAlarms=8;
/** Defines the length in seconds of an alarm sound offset. */
const TInt KDefaultSoundPlayOffsetInSeconds=0;
/** Defines the length in seconds of an alarm sound duration. */
const TInt KDefaultSoundPlayDurationInSeconds=30;
//
typedef CArrayFixFlat<TInt> CAlarmIdArray;
/** Stores the text message associated with an alarm. */
typedef TBuf<KMaxAlarmMessage> TAlarmMessage;
/** Stores the name of the sound file which is played when a particular alarm 
activates. */
typedef TBuf<KMaxAlarmSoundName> TAlarmSoundName;
typedef TInt TAlarmId;
//
/** Defines the different types of alarms.

This interface is deprecated, and is made available to provide binary compatibility 
with Symbian OS v6.1. Developers are strongly advised not to use this API 
in new applications. 
*/
enum TAlarmType 
	{
	/** The day alarm is untimed. */
	EAlarmTypeDay,
	/** The alarm is a clock alarm. */
	EAlarmTypeClock,
	/** The alarm is timed. */
	EAlarmTypeTimed,
	/** The alarm is orphaned. */
	EAlarmTypeOrphan,
	/** The alarm is snoozed. */
	EAlarmTypeSnoozed // Must be last type
	};
/** Defines how often a clock alarm is repeated, whether it is deleted after being 
acknowledged, and the way that the alarm is modified when the system time 
is changed.

This interface is deprecated, and is made available to provide binary compatibility 
with Symbian OS v6.1. Developers are strongly advised not to use this API 
in new applications. 
*/
enum TAlarmClockRepeat 
	{
	/** The alarm activates at a specified date and time. It is then deleted. */
	EAlarmClockOnce,
	/** The alarm activates at a specified time within the next 24 hours. It is then 
	deleted. */
	EAlarmClockNext24hours,
	/** The alarm activates at a specified time every day. The alarm is not deleted. */
	EAlarmClockDaily,
	/** The alarm activates at a specified time on the same day every week. The 
	alarm is not deleted. */
	EAlarmClockWeekly,
	/** The alarm activates every work day at the specified time. The alarm is 
	not deleted. */
	EAlarmClockWorkday // Must be last type
	};
/** Indicates whether alarms are pending, disabled, or non-existent. They may be 
returned by the RAlarmServer::AlarmState() function, and set using RAlarmServer::AlarmEnable().

This interface is deprecated, and is made available to provide binary compatibility 
with Symbian OS v6.1. Developers are strongly advised not to use this API 
in new applications. 
*/
enum TAlarmSetState
	{
	/** If the alarm is neither pending nor disabled then it is not set. 
	
	This implies that the alarm with the specified ID does not exist. */
	EAlarmNotSet,
	/** The alarm is pending, i.e. it exists and is enabled. */
	EAlarmSet,
	/** The alarm is disabled. */
	EAlarmDisabled
	};
/** Shows the current sound status of all alarms. 

The flags are returned by the RAlarmServer::AlarmSoundState() function. 
*/
enum TAlarmSoundState
	{
	/** Alarm sounds are on. Active alarms that are not snoozed or silenced have sound. */
	EAlarmSoundOn,
	/** Alarm sounds are off. Active alarms do not have sound. */
	EAlarmSoundOff,
	/** Alarm sounds are off until a certain time has expired, and then turn on. */
	EAlarmQuietPeriod,
	};
//
class TAlarmInfo
/** Stores alarm information. 

The information can be about outstanding alarms retrieved from the alarm 
server or new alarms which the client wishes to post. 

This interface is deprecated, and is made available to provide binary compatibility 
with Symbian OS v6.1. Developers are strongly advised not to use this API 
in new applications. 
*/
	{
public:
	/** The alarm ID, used to reference a particular alarm */
	TInt iAlarmId;
	/** The alarm due time. */
	TTime iDueTime;
	/** The alarm time. */
	TTime iAlarmTime;
	/** The type of alarm. */
	TAlarmType iType;
	/** The alarm message. */
	TAlarmMessage iMessage;
	/** The name of the sound file to play when the alarm activates. */
	TAlarmSoundName iSound;
	/** This field is only relevant to clock alarms. It defines the repetition rate. 
	E.g. is the alarm to occur once, daily etc. */
	TAlarmClockRepeat iRepeat;
	};
//
class TAlmSoundPlay
/** An alarm interval.

This consists of a duration and an offset.

An array of alarm intervals is stored and managed by the alarm server. It 
can be set and retrieved using RAlarmServer::SetAlarmPlayIntervals() and RAlarmServer::GetAlarmPlayIntervalsL().

This interface is deprecated, and is made available to provide binary compatibility 
with Symbian OS v6.1. Developers are strongly advised not to use this API 
in new applications. 
*/
	{
public:
	inline TAlmSoundPlay();
	inline TAlmSoundPlay(TTimeIntervalMinutes aOffset, TTimeIntervalSeconds aDuration);
public:
	/** The offset. 
	
	This is the number of minutes between the alarm being activated and the alarm 
	sound beginning to play. */
	TTimeIntervalMinutes iOffset;		// from the time an alarm is first displayed
	/** The duration. 
	
	This is is the number of seconds the alarm sound plays. */
	TTimeIntervalSeconds iDuration;
	};
//
class RAlarmServer : public RSessionBase
/** Defines the alarm server's client side API.

Clients can use this API to connect to the alarm server, add, count and delete 
alarms, retrieve alarm information, orphan session alarms, and set the alarm 
sound state.

This interface is deprecated, and is made available to provide binary compatibility 
with Symbian OS v6.1. Developers are strongly advised not to use this API 
in new applications. 
*/
	{
public:
	/** Specifies whether a session alarm is for a timed or an untimed event. 
	
	The alarm type is set using the RAlarmServer::SetSessionAlarm() function. */
	enum TSessionType 
		{ 
		/** The alarm is an untimed event. */
		ESessionTypeDay,
		/** The alarm is a timed event. */
		ESessionTypeTimed 
		};

	/** Defines the type of alarms to be put into an array. This enumeration is used 
	by the AlarmArrayPopulateL() function. */
	enum TArrayCategory 
		{ 
		/** The array is to contain pending alarms, including clock alarms, session alarms, 
		orphaned alarms and snoozed alarms. */
		EArrayNext,
		/** The array is to contain review alarms. */
		EArrayReview,
		/** The array is to contain orphaned alarms. This will also include all snoozed 
		alarms. */
		EArrayOrphan,
		/** The array is to contain snoozed alarms. */
		EArraySnooze 
		};

	/** Defines the category of alarms for which information is required. This enumeration 
	is used by the RAlarmServer::AlarmInfo() function. */
	enum TInfoCategory 
		{ 
		/** Get information for the alarm with the specified ID, irrespective of type. */
		EInfoById,
		/** Get information for one of the 8 clock alarms. */
		EInfoClock,
		/** Get information for the next alarm which is due, irrespective of type. */
		EInfoNext,
		/** Get information for a session alarm. */
		EInfoSession 
		};

	/** Defines the category of the alarms to be counted using the RAlarmServer::AlarmCount() 
	function. */
	enum TCountCategory 
		{ 
		/** Count the number of pending alarms. */
		ECountNext,
		/** Count the number of review alarms. */
		ECountReview,
		/** Count the number of orphaned alarms. */
		ECountOrphan,
		/** Count the number of snoozed alarms. */
		ECountSnooze,
		/** Count the number of unacknowledged alarms. */
		ECountUnacknowledged 
		};
public:
	IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;
	IMPORT_C void NotifyOnChangeCancel();
	IMPORT_C void NotifyOnChange(TRequestStatus& aStatus);
public:
	IMPORT_C void CancelSessionAlarm();
	IMPORT_C TInt OrphanSessionAlarm();
	IMPORT_C void SetClockAlarm(TInt aClockAlarmIndex,const TTime& aAlarmTime,const TAlarmMessage& aMessage,const TAlarmSoundName& aSound,TAlarmClockRepeat aRepeat);
	IMPORT_C void SetAgendaAlarm(const TTime& aAlarmTime,const TAlarmMessage& aMessage,const TAlarmSoundName& aSound,const TTime& aDueDateTime,TSessionType aType);
	IMPORT_C void SetSessionAlarm(TRequestStatus& aStatus,const TTime& aAlarmTime,const TAlarmMessage& aMessage,const TAlarmSoundName& aSound,const TTime& aDueDateTime,TSessionType aType);
	IMPORT_C TAlarmId SetAgendaAlarm(const TTime& aAlarmTime,const TAlarmMessage& aMessage,const TAlarmSoundName& aSound,const TTime& aDueDateTime,TSessionType aType, const TDesC8& aData);
	IMPORT_C TAlarmId SetSessionAlarm(TRequestStatus& aStatus,const TTime& aAlarmTime,const TAlarmMessage& aMessage,const TAlarmSoundName& aSound,const TTime& aDueDateTime,TSessionType aType, const TDesC8& aData);
	IMPORT_C TInt GetAlarmData(TAlarmId aAlarmId, TDes8& aSink) const;

	//
	IMPORT_C TInt AlarmDelete(TInt aAlarmId);
	IMPORT_C TInt DeleteAllOrphanAlarms();
	IMPORT_C TInt AlarmEnable(TBool aShouldEnable,TInt aAlarmId);
	//
	IMPORT_C TAlarmSetState AlarmState(TInt aAlarmId) const;
	IMPORT_C TInt AlarmCount(TCountCategory aCategory) const;
	IMPORT_C TInt AlarmType(TAlarmType& aType,TInt aAlarmId) const;
	IMPORT_C TInt AlarmOwner(TFullName& aName,TInt aAlarmId) const;
	IMPORT_C void AlarmArrayPopulateL(CAlarmIdArray& aArray,TArrayCategory aCategory,TInt aMaxNumber=64) const;
	IMPORT_C TInt AlarmInfo(TAlarmInfo& anAlarm,TInfoCategory aCategory,TInt aAlarmId=KNullAlarmID) const;
	//
	IMPORT_C void QuietPeriodCancel();
	IMPORT_C TTime QuietPeriodUntil() const;
	IMPORT_C TInt QuietPeriodSet(TTimeIntervalMinutes aQuietInterval);
	IMPORT_C void SetAlarmSoundOn(TBool aSetSoundOn);
	IMPORT_C TAlarmSoundState AlarmSoundState() const;
	//
	IMPORT_C TInt SetAlarmPlayIntervals(const CArrayFix<TAlmSoundPlay>& aIntervals);
	IMPORT_C TInt GetAlarmPlayIntervalsL(CArrayFix<TAlmSoundPlay>& aIntervals);

public:
	IMPORT_C void __DbgShutDownServer();
	IMPORT_C void __DbgFailAlloc(TInt aCount);
	IMPORT_C void __DbgPreventUserNotify(TBool aShouldStop);
	IMPORT_C TInt __DbgSnoozeAlarm(TInt aAlarmId,const TTime& aNewTime);

private:	// these are private leave capable functions; 
			// with the exception of the former, all of these are here because non-leave-capable functions
			// now need to call leave-capable functions within the new alarm server
	CBufBase* FetchTransferBufferLC(TInt aBufferSize) const;
	TInt ContainsClockAlarmL(TUid& aClockAlarmCategory, TInt aClockAlarmIndex, TInt& aId) const;
	TUid ClockAlarmCategory(TInt aClockAlarmIndex) const;
	TInt ClockAlarmIdFromIndexL(TInt aClockAlarmIndex, TInt& aAlarmId) const;
	TInt DeleteAllOrphanAlarmsL();
	TInt SetAlarmPlayIntervalsL(const CArrayFix<TAlmSoundPlay>& aIntervals);
	TInt CountOrphanAlarmsL() const;
	TAlarmId DoSetAgendaAlarm(const TTime& aAlarmTime, const TAlarmMessage& aMessage,
						const TAlarmSoundName& aSound, TSessionType aType, const TDesC8& aData);
	TAlarmId DoSetSessionAlarm(TRequestStatus& aStatus, const TTime& aAlarmTime,
										const TAlarmMessage& aMessage, 
										const TAlarmSoundName& aSound, 
										TSessionType aType, const TDesC8& aData);

private:
	TPckgBuf<TAlarmInfo> iPckgAlarmInfo;
	};





// 	class TAlmSoundPlay
inline TAlmSoundPlay::TAlmSoundPlay()
:	iOffset(KDefaultSoundPlayOffsetInSeconds), iDuration(KDefaultSoundPlayDurationInSeconds)
/** Trivial default C++ constructor.
	
Initialises the offset to zero and the duration to 30 seconds. */
	{}
inline TAlmSoundPlay::TAlmSoundPlay(TTimeIntervalMinutes aOffset, TTimeIntervalSeconds aDuration)
:	iOffset(aOffset), iDuration(aDuration)
/** C++ constructor with an offset and a duration.
	
@param aOffset The offset in minutes.
@param aDuration The duration in seconds. */
	{}


#endif
