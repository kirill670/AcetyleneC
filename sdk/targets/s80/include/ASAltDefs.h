// ASALTDEFS.H
//
// Copyright (c) 1999-2001 Symbian Ltd. All rights reserved.
//
#ifndef __ASALTDEFS_H__
#define __ASALTDEFS_H__

// System includes
#include <e32std.h>
#include <Babitflags.h>

// Type definitions
typedef TBitFlags TASAltClientServerStateFlags;

// Constants
const TInt KASAltVersionMajor = 2;
const TInt KASAltVersionMinor = 0;
const TInt KASAltVersionBuild = 0;
//
const TInt KAlmMessageSlots	= 5;

// Enumerations
/*
 * The individual op codes which the Alarm Alert Server and Alarm Server
 * handshake using
 */
enum TASAltOpCode
    {
	/*
	 * Notify the alarm server (asynchronously) when the Alarm Alert Server
	 * wishes to perform some action.
	 */
    EASAltOpCodeNotify = 0,

	/*
	 * Cancel an earlier notification
	 */
    EASAltOpCodeNotifyCancel,

	/*
	 * Change the visibility of the Alarm Alert Server UI furniture
	 */
	EASAltOpCodeVisible,

	/*
	 * Update the Alarm Alert Server flags
	 */
    EASAltOpCodeSetState,

	/*
	 * Inform the Alarm Alert Server of the currently notifying alarm
	 */
    EASAltOpCodeSetAlarm,

	/*
	 * Inform the Alarm Alert Server that the currently alerting alarm
	 * has been snoozed.
	 */
	EASAltOpCodeSetDeferTime,

	/*
	 * Retrieve the time from the Alarm Alert Server when a quiet period 
	 * should be terminated
	 */
	EASAltOpCodeGetUserTime,

	/*
	 * Create an outstanding request with the Alarm Alert Server. Used
	 * as a mechanism to obtain Alarm Alert Server thread death notifications.
	 */
	EASAltOpCodeLogon,

	/*
	 * Ask the Alarm Alert Server to start playing the specified alarm sound
	 */
	EASAltOpCodeStartPlayingSound,

	/*
	 * Ask the Alarm Alert Server to stop playing any sound
	 */
	EASAltOpCodeStopPlayingSound
    };

/*
 * All communication from the Alarm Alert Server to the Alarm Server
 * occurs via a single outstanding TRequesStatus which is handled
 * by the Alarm Server (as an active object). The following enumeration
 * describes the type of action that the Alarm Server should take in
 * response to a request from the Alarm Alert Server.
 */
enum TASAltAlertServerResponse
	{
	/*
	 * The Alarm Alert Server wishes the Alarm Server to
	 * silence all alarms.
	 */
	EASAltAlertServerResponseSilence = 0,

	/*
	 * The Alarm Alert Server wishes the Alarm Server to
	 * enter a global quiet period.
	 */
	EASAltAlertServerResponseQuietPeriod,

	/*
	 * The Alarm Alert Server wishes the Alarm Server to
	 * acknowledge (clear) the currently notifying alarm.
	 */
	EASAltAlertServerResponseClear,

	/*
	 * The Alarm Alert Server wishes the Alarm Server to
	 * acknowledge (clear) the currently notifying alarm
	 * and all others that are awaiting notification.
	 */
	EASAltAlertServerResponseClearAll,

	/*
	 * The Alarm Alert Server wishes the Alarm Server to
	 * snooze the currently notifying alarm.
	 */
	EASAltAlertServerResponseSnooze,

	/*
	 * The Alarm Alert Server wishes the Alarm Server to
	 * temporarily pause all sound (i.e stop sending sound
	 * play events to the Alarm Alert Server).
	 */
	EASAltAlertServerResponsePauseSound
	};

/*
 * Flags for TASAltClientServerStateFlags
 */
enum TASAltStateFlags
	{
	/*
	 * The Alarm Alert Server should not play any sound
	 */
	EASAltStateFlagsSilentRunning = 1,

	/*
	 * The Alarm Server is currently within a quiet period
	 */
	EASAltStateFlagsInQuietPeriod = 2,

	/*
	 * The Alarm Server currently has more than one alarm
	 * ready to notify.
	 */
	EASAltStateFlagsMoreThanOneDueAlarm	= 3,

	/*
	 * There wasn't sufficient memory within the Alarm
	 * Server to allocate room for a snoozed alarm. I'm
	 * note convinced we need this anymore
	 */
	EASAltStateFlagsNoMemoryForSnoozeAlarm = 4,

	/*
	 * There isn't any sound filename for the current
	 * alarm.
	 */
	EASAltStateFlagsAlarmHasNoSoundFileName	= 5,

	/*
	 * This isn't used by the Alarm Alert Server.
	 */
	EASAltStateFlagsSoundIsPaused = 6

	};

// Literal constants
_LIT(KAlarmAlertServerName, "AlarmAlertServer");


#endif
