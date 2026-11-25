// ASSHDDEFS.H
//
// Copyright (c) 1999-2001 Symbian Ltd. All rights reserved.
//
#ifndef __ASSHDDEFS_H__
#define __ASSHDDEFS_H__

// System includes
#include <e32std.h>

// User includes
#include "asshdbitflags.h"

// Constants
const TInt KMaxAlarmMessageLength				= 0x80;
const TInt KMaxAlarmSoundNameLength				= KMaxFileName;

// Type definitions
typedef TInt TAlarmId;
typedef TUid TAlarmCategory;
//
typedef TBitFlags8 TAlarmCharacteristicsFlags;
//
typedef TBuf<KMaxAlarmMessageLength> TAlarmMessage;
typedef TBuf<KMaxAlarmSoundNameLength> TAlarmSoundName;
//
const TAlarmId KNullAlarmId						= 0;
//
const TInt KDefaultSoundPlayOffsetInSeconds		= 0;
const TInt KDefaultSoundPlayDurationInSeconds	= 30;

// Constants
const TAlarmCategory KASCliCategoryClock		= { 0x101F5030 };

/**
 * Alarms can be either enabled or disabled
 */
enum TAlarmStatus
	{
	/**
	 * The alarm is currently enabled
	 */
	EAlarmStatusEnabled = 0,

	/**
	 * The alarm is currently disabled, and therefore
	 * will not expire.
	 */
	EAlarmStatusDisabled,
	};

/**
 * This represents one of the status or modes that
 * any given alarm may be in. Alarms can occupy only one
 * state.
 */
enum TAlarmState
	{
	/**
	 * The alarm isn't currently known by the alarm server
	 */
	EAlarmStateInPreparation = -1,

	/**
	 * The alarm is waiting for its expiry time to be reached
	 */
	EAlarmStateQueued = 0,

	/**
	 * The alarm is current snoozed, and will expire again
	 * when the snooze period is up.
	 */
	EAlarmStateSnoozed,

	/**
	 * The alarm is waiting to notify. This state is used when
	 * an alarm that was previously notifying is pre-empted by
	 * another due alarm. This alarm is moved to "waiting" and
	 * the new alarm replaces it by moving to "notifying").
	 * Can also happen where there is more than 2 alarms to
	 * be notified, i.e. the 2nd and 3rd alarms will be in
	 * the waiting state, whilst the "most due" (i.e the alarm
	 * which is the newest) will be in the notifying state.
	 */
	EAlarmStateWaitingToNotify,

	/**
	 * The alarm is currently notifying
	 */
	EAlarmStateNotifying,

	/**
	 * The alarm has already notified and has been 
	 * dismissed. Effectively any alarm which remains
	 * in this state is dead.
	 */
	EAlarmStateNotified
	};

enum TAlarmDayOrTimed
	{
	EASShdAlarmTypeTimed = 0,

	EASShdAlarmTypeDay
	};

/**
 * Controls the global Alarm Server-wide sound state.
 */
enum TAlarmGlobalSoundState
	{
	/**
	 * When an alarm expires, the Alarm Server will request
	 * that the alarm sound is played.
	 */
	EAlarmGlobalSoundStateOn = 0,

	/**
	 * When an alarm expires, no sound will play.
	 */
	EAlarmGlobalSoundStateOff
	};

/**
 * Controls the repeat definition for this alarm
 *
 * NOTE:
 * Alarm settings are all validated by the Alarm
 * Server, and KErrArguement will be returned
 * to the Alarm Server client for any alarm with
 * invalid settings.
 */
enum TAlarmRepeatDefinition
	{
	/**
	 * The alarm expires only once, and is then deleted
	 * from the alarm server. By default, all alarms behave
	 * this way. Standard repeat-once alarms are date
	 * relative, i.e they occur on a fixed date and point
	 * in time.
	 *
	 * If the system-time changes so that the new date and
	 * time is one (or more) days after the original expiry
	 * time, then the alarm is silently deleted.
	 *
	 * If the system time is changed so that the new time
	 * is before the original expiry time, the alarm is
	 * not changed.
	 *
	 * If the system time changes so that the new date
	 * and time is less than one day after the original
	 * expiry time, then the alarm will expire immediately.
	 */
	EAlarmRepeatDefintionRepeatOnce						= 0,

	/**
	 * When initially scheduling the alarm, the date 
	 * specified for the alarm is ignored by the Alarm
	 * Server.
	 *
	 * The date is always the next appropriate day 
	 * (given the specified time).
	 *
	 * E.g. 1] if the time is 15:00 and the alarm time
	 * specified is 14:00, then the next appropriate
	 * date & time is "Tomorrow" at 14:00.
	 *
	 * E.g. 2] if the time is 15:00 and the specified
	 * time for the alarm is 16:00 then the alarm will
	 * expire "Today" at 16:00.
	 *
	 * If the system date/time changes so that the new time
	 * is more than 1 day after the calculated expiry time,
	 * then the alarm changes its type from "Repeat in the
	 * next 24 Hours" to "Repeat Once." Subsequent changes
	 * in system time will result in the behaviour described
	 * by the EAlarmRepeatDefintionRepeatOnce characteristic.
	 */
	EAlarmRepeatDefintionRepeatNext24Hours,

	/**
	 * The alarm repeats every single day at the same time.
	 *
	 * System date/time changes result in the same behaviour
	 * as "Repeat once" except an alarm is never deleted,
	 * just rescheduled for the next available time. Changes
	 * to the date/time which result in the time being moved
	 * in the past (relative to the old time) will not result
	 * in any phantom alarm expiries.
	 */
	EAlarmRepeatDefintionRepeatDaily,

	/**
	 * The alarm repeats every single work day at the same
	 * time.
	 *
	 * System date/time changes result in the same behaviour
	 * as "Repeat once" except an alarm is never deleted,
	 * just rescheduled for the next available time. Changes
	 * to the date/time which result in the time being moved
	 * in the past (relative to the old time) will not result
	 * in any phantom alarm expiries.
	 */
	EAlarmRepeatDefintionRepeatWorkday,

	/**
	 * The alarm repeats every single week, on the same
	 * day at the same time.
	 *
	 * System date/time changes result in the same behaviour
	 * as "Repeat once" except an alarm is never deleted,
	 * just rescheduled for the next available time. Changes
	 * to the date/time which result in the time being moved
	 * in the past (relative to the old time) will not result
	 * in any phantom alarm expiries.
	 */
	EAlarmRepeatDefintionRepeatWeekly
	};

/**
 * Controls various behavioural characteristics of an alarm
 *
 * NOTE:
 * Alarm settings are all validated by the Alarm
 * Server, and KErrArguement will be returned
 * to the Alarm Server client for any alarm with
 * invalid settings.
 */
enum TAlarmCharacteristics
	{
	/**
	 * This alarm only exists whilst a session is maintained
	 * with the Alarm Server. By default, all alarms are
	 * persisted with the Alarm Server and remain so, even
	 * after the initiating session has disconnected. Session
	 * alarms are removed from the alarm queue when the
	 * originating session disconnects from the server
	 */
	EAlarmCharacteristicsSessionSpecific				= 0,

	/**
	 * By default, all alarms will result in a suitable
	 * screen being displayed (device specific). If it is
	 * desirable to ignore this behaviour, use the following
	 * flag.
	 */
	EAlarmCharacteristicsDoNotNotifyAlarmAlertServer	= 1,

	//
	EAlarmCharacteristicsLast
	};

/**
 * This enumeration defines one of many events which may occur
 * (and be reported) by the alarm server. These events are
 * channelled to the client using the RASCliSession::NotifyChange
 * method.
 */
enum TAlarmChangeEvent
	{
	/**
	 * An alarm has changed state
	 */
	EAlarmChangeEventState = 1,

	/**
	 * An alarm has changed status
	 */
	EAlarmChangeEventStatus = 2,

	/**
	 * An alarm has changed characteristics
	 */
	EAlarmChangeEventCharacteristics = 3,

	/**
	 * An alarm has been deleted from the queue of alarms
	 */
	EAlarmChangeEventAlarmDeletion = 4,

	/**
	 * An alarm has been added to the queue of alarms
	 */
	EAlarmChangeEventAlarmAddition = 5,

	/**
	 * The next alarm to be due has expired
	 */
	EAlarmChangeEventTimerExpired = 6,

	/**
	 * The sound for an alarm has just started playing
	 */
	EAlarmChangeEventSoundPlaying = 7,

	/**
	 * The sound for an alarm has just stopped playing
	 */
	EAlarmChangeEventSoundStopped = 8,

	/**
	 * The sound intervals associated with sound timing
	 * have changed
	 */
	EAlarmChangeEventPlayIntervalsChanged = 9,

	/**
	 * The global sound state (on/off) has changed
	 */
	EAlarmChangeEventGlobalSoundStateChanged = 10,

	/**
	 * The next alarm at the head of the alarm queue
	 * has changed
	 */
	EAlarmChangeEventHeadQueueItemChanged = 11,

	/**
	 * The system date/time has changed
	 */
	EAlarmChangeEventSystemDateTimeChanged = 12,

	/**
	 * The Alarm Alert Server has been instructed
	 * to show the "alarm expired" UI widget
	 */
	EAlarmChangeEventAlarmUIVisible = 13,

	/**
	 * The Alarm Alert Server has been instructed
	 * to hide the "alarm expired" UI widget
	 */
	EAlarmChangeEventAlarmUIInvisible = 14,

	/**
	 * Alarm sounds have been temporarily silenced/paused
	 * or re-enabled.
	 */
	EAlarmChangeEventSoundSilence = 15,

	/**
	 * The data associated with an alarm has changed
	 */
	EAlarmChangeEventAlarmData = 16,

	/**
	 * Last change event (anchor) - always at the end of
	 * the list.
	 */
	EAlarmChangeEventLast,
	
	/**
	 * An undefined alarm event has occurred
	 */
	EAlarmChangeEventUndefined = 0
	};

/**
 * Server initiated panics of the client session
 */
enum TAlarmServerInitiatedClientPanic
	{
	/**
	 * Panic occurs when the client requests a copy of any data attached
	 * to an alarm, and the client didn't supply a big enough buffer to
	 * copy the date to.
	 */
	EAlarmServerInitiatedClientPanicInsufficientRoomForAlarmData = 0,

	/**
	 * Typically occurs when a client method expects to write to a descriptor
	 * (sometimes asynchronously) and the client supplied descriptor is not
	 * valid.
	 */
	EAlarmServerInitiatedClientPanicBadDescriptor = 1,

	/**
	 * Occurs when a client already has an outstanding notification request
	 * but attempts to request another.
	 */
	EAlarmServerInitiatedClientPanicChangeNotificationAlreadyOutstanding = 2,

	/**
	 * Occurs when a client tries to perform an invalid operation
	 */
	EAlarmServerInitiatedClientPanicInvalidOperation = 3,

	/**
	 * Occurs when a request to add an alarm (with notification) contains
	 * a null Alarm Id (and in the case of alarms with notifications, the
	 * alarm id is pre-allocated by the client before requesting the 
	 * notification).
	 */
	EAlarmServerInitiatedClientPanicBadPreAllocatedAlarmId = 4

	};

#endif