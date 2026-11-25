// ASSHDALARM.H
//
// Copyright (c) 1999-2001 Symbian Ltd. All rights reserved.
//
#ifndef __ASSHDALARM_H__
#define __ASSHDALARM_H__

// System includes
#include <e32base.h>
#include <s32strm.h>

// User includes
#include "asshddefs.h"


///////////////////////////////////////////////////////////////////////////////////////
// ----> TASShdAlarm (header)
///////////////////////////////////////////////////////////////////////////////////////
/**
 * This class represents an client-side alarm object. It contains all of the
 * necessary information in order to create an alarm in the Alarm Server.
 */
class TASShdAlarm
	{
///////////////////////////////////////////////////////////////////////////////////////
public:										// CONSTRUCT
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C TASShdAlarm();

///////////////////////////////////////////////////////////////////////////////////////
public:										// INTERNALIZE / EXTERNALIZE
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C void							InternalizeL(RReadStream& aStream);

	IMPORT_C void							ExternalizeL(RWriteStream& aStream) const;

///////////////////////////////////////////////////////////////////////////////////////
public:										// READ-ONLY ACCESS
///////////////////////////////////////////////////////////////////////////////////////

	/**
	 * Return the alarm status, e.g. enabled/disabled
	 */
	inline TAlarmStatus						Status() const				{ return iStatus; }

	/**
	 * Return the alarm state, e.g. queued, notifying, etc
	 */
	inline TAlarmState						State() const				{ return iState; }

	/**
	 * Return the alarm type, e.g. day, timed
	 */
	inline TAlarmDayOrTimed					DayOrTimed() const				{ return iDayOrTimed; }

	/**
	 * Does this alarm have any associated data?
	 */
	inline TBool							HasAssociatedData() const;

	/**
	 * Does this alarm still have an active owning session?
	 */
	inline TBool							HasOwningSession() const;

	/**
	 * Is this alarm orphaned, that is, did it used to have an owning session
	 * but no longer does?
	 */
	inline TBool							HasBecomeOrphaned() const;

///////////////////////////////////////////////////////////////////////////////////////
public:										// READ-ONLY & MODIFIABLE
///////////////////////////////////////////////////////////////////////////////////////

	IMPORT_C void							Reset();

	/**
	 * Return a writable version of this alarm's id
	 */
	inline TAlarmId&						Id()						{ return iAlarmId; }

	/**
	 * Return this alarm's id
	 */
	inline TAlarmId							Id() const					{ return iAlarmId; }

	/**
	 * Return a writable version of the next due time this alarm is scheduled
	 * to expire.
	 */
	inline TTime&							NextDueTime()				{ return iNextDueTime; }

	/**
	 * Return the next due time that this alarm is scheduled to expire.
	 */
	inline const TTime&						NextDueTime() const			{ return iNextDueTime; }

	/**
	 * Return a writable version of this alarm's original expiry time.
	 */
	inline TTime&							OriginalExpiryTime()		{ return iOriginalExpiryTime; }

	/**
	 * Return this alarm's original expiry time. The original expiry time
	 * is usually the same as the next due time, except if the alarm has been
	 * snoozed. In this instance, the original expiry time was the time
	 * when the alarm first expired, and the next due time is that when it
	 * is due to re-awaken after the snooze.
	 */
	inline const TTime&						OriginalExpiryTime() const	{ return iOriginalExpiryTime; }

	/**
	 * Return a writable version of this alarm's category
	 */
	inline TAlarmCategory&					Category()					{ return iCategory; }

	/**
	 * Return this alarm's category. The alarm's category is a unique identifier which
	 * may (optionally) be used by clients to tag each alarm with a specific code. This allows
	 * clients to identify all alarms that fall within a category, e.g. all alarms associated
	 * with a particular application or application engine.
	 */
	inline TAlarmCategory					Category() const			{ return iCategory; }

	/**
	 * Return a writable version of this alarm's characteristics.
	 */
	inline TAlarmCharacteristicsFlags&		Characteristics()			{ return iCharacteristics; }

	/**
	 * Return this alarm's characteristics
	 */
	inline TAlarmCharacteristicsFlags		Characteristics() const		{ return iCharacteristics; }

	/**
	 * Return a writable version of this alarm's repeat definition
	 */
	inline TAlarmRepeatDefinition&			RepeatDefinition()			{ return iRepeatDefinition; }

	/**
	 * Return the repeat definition for this alarm. The repeat definition controls the alarm's
	 * behaviour after it has expired. For example, via the repeat definition, it is possible to
	 * automatically re-queue the alarm to expire again in exactly 24 hours time ("repeat daily").
	 */
	inline TAlarmRepeatDefinition			RepeatDefinition() const	{ return iRepeatDefinition; }

	/**
	 * Return a writable version of this alarm's message
	 */
	inline TAlarmMessage&					Message()					{ return iMessage; }

	/**
	 * Return this alarm's message. It is usually displayed in the Alarm UI when
	 * the alarm expires.
	 */
	inline const TAlarmMessage&				Message() const				{ return iMessage; }

	/**
	 * Return a writable version of this alarm's sound name
	 */
	inline TAlarmSoundName&					SoundName()					{ return iSoundName; }

	/**
	 * Return this alarm's sound name.
	 */
	inline const TAlarmSoundName&			SoundName() const			{ return iSoundName; }

///////////////////////////////////////////////////////////////////////////////////////
public:										// CLIENT DATA ACCESS
///////////////////////////////////////////////////////////////////////////////////////

	/**
	 * Return a writable version of this alarm's client flags
	 */
	inline TBitFlags16&						ClientFlags()				{ return iClientFlags; }

	/**
	 * Return this alarm's client flags. The client flags are a series of bit flags which may
	 * be used for any client-specific data. The Alarm Server does not use this data member
	 * for any purpose.
	 */
	inline TBitFlags16						ClientFlags() const			{ return iClientFlags; }

	/**
	 * Return the client data (slot 1) for this alarm
	 */
	inline TInt								ClientData1() const			{ return iClientData1; }

	/**
	 * Return the client data (slot 1) for this alarm
	 */
	inline TInt&							ClientData1()				{ return iClientData1; }

	/**
	 * Return the client data (slot 2) for this alarm
	 */
	inline TInt								ClientData2() const			{ return iClientData2; }

	/**
	 * Return the client data (slot 2) for this alarm
	 */
	inline TInt&							ClientData2()				{ return iClientData2; }

///////////////////////////////////////////////////////////////////////////////////////
protected:									// INTERNAL FLAGS
///////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @internal
	 */
	enum TASShdAlarmFlags
		{

		/**
		 * @internal
		 */
		EASShdAlarmFlagsHasAssociatedData	= 0,

		/**
		 * @internal
		 */
		EASShdAlarmFlagsHasOwningSession	= 1,

		/**
		 * @internal
		 */
		EASShdAlarmFlagsHasBecomeOrphaned	= 2
		};

///////////////////////////////////////////////////////////////////////////////////////
protected:									// MEMBER DATA
///////////////////////////////////////////////////////////////////////////////////////

	/**
	 * Various flags - used internally by the alarm object
	 */
	TBitFlags8								iFlags;

	/**
	 * This represents the desired behaviour for a given alarm.
	 * The Alarm Server uses this information to control the
	 * behaviour of the alarm.
	 *
	 * @see TAlarmCharacteristics
	 */
	TAlarmCharacteristicsFlags				iCharacteristics;

	/**
	 * The unique identifier assoicated with each alarm maintained
	 * by the alarm world server.
	 */
	TAlarmId								iAlarmId;

	/**
	 * The status of this alarm (e.g. enabled, disabled)
	 */
	TAlarmStatus							iStatus;

	/**
	 * The state of this alarm (e.g. queued, notifying, notified, snoozed etc)
	 */
	TAlarmState								iState;

	/**
	 * The type of this alarm (e.g. day, timed)
	 */
	TAlarmDayOrTimed						iDayOrTimed;

	/**
	 * Controls how the alarm repeats after it has expired. Note that
	 * session alarms are not allowed to repeat (they must be "once
	 * only").
	 */
	TAlarmRepeatDefinition					iRepeatDefinition;

	/**
	 * This UID is supplied by the client and is used to indicate
	 * the category that this alarm is part of. The Alarm Server
	 * is category-agnostic, that is, this information is for
	 * the client's use only
	 */
	TAlarmCategory							iCategory;

	/**
	 * The date and time at which this alarm is next due. For alarms
	 * that haven't been snoozed, then this is the original due time.
	 *
	 * For alarms that have been snoozed, this is the time at which
	 * the alarm will reawaken.
	 */
	TTime									iNextDueTime;

	/**
	 * This attribute is only used in the instance whereby an alarm
	 * is snoozed. It represents the time at which the alarm first 
	 * expired.
	 */
	TTime									iOriginalExpiryTime;

	/**
	 * The message associated with this alarm, typically used
	 * in an application UI to inform the user as to the reason
	 * for the alarm.
	 */
	TAlarmMessage							iMessage;

	/**
	 * A descriptor which holds the name of the sound file which
	 * should be played when the alarm expires.
	 */
	TAlarmSoundName							iSoundName;

///////////////////////////////////////////////////////////////////////////////////////
protected:									// CLIENT SPECIFIC DATA
///////////////////////////////////////////////////////////////////////////////////////

	/**
	 * Flags for use by any particular client. These will
	 * only be relevant to a client who can interpret them.
	 */
	TBitFlags16								iClientFlags;

	/**
	 * For arbitrary client data 1
	 */
	TInt									iClientData1;

	/**
	 * For arbitrary client data 2
	 */
	TInt									iClientData2;

///////////////////////////////////////////////////////////////////////////////////////
private:									// BC PROOFING
///////////////////////////////////////////////////////////////////////////////////////
	TAny*									iTASShdAlarm_1;
	TAny*									iTASShdAlarm_2;
	TAny*									iTASShdAlarm_3;
	};


///////////////////////////////////////////////////////////////////////////////////////
// ----> TASShdAlarm (inline)
///////////////////////////////////////////////////////////////////////////////////////

inline TBool TASShdAlarm::HasAssociatedData() const
	{
	return iFlags.IsSet(EASShdAlarmFlagsHasAssociatedData);
	}

inline TBool TASShdAlarm::HasOwningSession() const
	{
	return iFlags.IsSet(EASShdAlarmFlagsHasOwningSession);
	}

inline TBool TASShdAlarm::HasBecomeOrphaned() const
	{
	return iFlags.IsSet(EASShdAlarmFlagsHasBecomeOrphaned);
	}


#endif