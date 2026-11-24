// ASALTDEFS.H
//
// Copyright (c) 1999-2005 Symbian Software Ltd. All rights reserved.
//
#ifndef __ASALTDEFS_H__
#define __ASALTDEFS_H__

// System includes
#include <e32std.h>
#include <Babitflags.h>

// Type definitions
typedef TBitFlags TASAltClientServerStateFlags;

// Constants
#ifdef SYMBIAN_FLEXIBLE_ALARM
const TInt KASAltVersionMajor = 3;
#else
const TInt KASAltVersionMajor = 2;
#endif

const TInt KASAltVersionMinor = 0;
const TInt KASAltVersionBuild = 0;
//
const TInt KAlmMessageSlots	= 5;

// Enumerations
/*
 The individual op codes which the Alert Server and Alarm Server
 handshake using
 */
enum TASAltOpCode
    {
	/**
	 Notify the alarm server (asynchronously) when the Alert Server
	 wishes to perform some action.
	 */
    EASAltOpCodeNotify = 0,

	/**
	 Cancel an earlier notification
	 */
    EASAltOpCodeNotifyCancel,

	/**
	 Change the visibility of the Alert Server UI furniture
	 */
	EASAltOpCodeVisible,

	/**
	 Update the Alert Server flags
	 */
    EASAltOpCodeSetState,

	/**
	 Inform the Alert Server of the currently notifying alarm
	 */
    EASAltOpCodeSetAlarm,

	/**
	 Inform the Alert Server that the currently alerting alarm
	 has been snoozed.
	 */
	EASAltOpCodeSetDeferTime,

	/**
	 Retrieve the time from the Alert Server when a quiet period 
	 should be terminated
	 */
	EASAltOpCodeGetUserTime,

	/**
	 Create an outstanding request with the Alert Server. Used
	 as a mechanism to obtain Alert Server thread death notifications.
	 */
	EASAltOpCodeLogon,

	/**
	 Ask the Alert Server to start playing the specified alarm sound
	 */
	EASAltOpCodeStartPlayingSound,

	/**
	 Ask the Alert Server to stop playing any sound
	 */
	EASAltOpCodeStopPlayingSound

#ifdef SYMBIAN_FLEXIBLE_ALARM		
	/**
	Ask the  Alert Server to change vissibility for all alarms
	*/
	, EASAltOpCodeVisibleAll,
	
	/**
	Ask the  Alert Server to update states for all alarms
	*/
	EASAltOpCodeSetStateAll,
	
	/**
	Ask the  Alert Server to stop playing all sounds.
	*/
	EASAltOpCodeStopPlayingSoundAll,
	
	/**
	Ask the  Alert Server to delete alarm with provided Id
	*/
	EASAltOpCodeDeleteAlarm,

	/**
	 Retrieve the time from the Alert Server when a quiet period 
	 should be terminated
	 */

	EASAltOpCodeGetEndQuietTime,

	/**
	Ask the Alarm Server to get number of simultaneously supported alarms
	*/
	EASAltOpCodeGetMaxAlarms,
	
	/**
	Ask the  Alert Server to delete all alarms
	*/
	EASAltOpCodeDeleteAlarmAll,
			
	EASAltOpCodeLast
	
#endif //SYMBIAN_FLEXIBLE_ALARM
	
    };

/**
 All communication from the Alert Server to the Alarm Server
 occurs via a single outstanding TRequesStatus which is handled
 by the Alarm Server (as an active object). This enumeration
 describes the type of action that the Alarm Server should take in
 response to a request from the Alert Server.
 */
enum TASAltAlertServerResponse
	{
	/**
	 The Alert Server wishes the Alarm Server to
	 silence all alarms.
	 */
	EASAltAlertServerResponseSilence = 0,

	/**
	 The Alert Server wishes the Alarm Server to
	 enter a global quiet period.
	 */
	EASAltAlertServerResponseQuietPeriod,

	/**
	 The Alert Server wishes the Alarm Server to
	 acknowledge (clear) the currently notifying alarm.
	 */
	EASAltAlertServerResponseClear,

	/**
	 The Alert Server wishes the Alarm Server to
	 acknowledge (clear) the currently notifying alarm
	 and all others that are awaiting notification.
	 */
	EASAltAlertServerResponseClearAll,

	/**
	 The Alert Server wishes the Alarm Server to
	  snooze the currently notifying alarm.
	 */
	EASAltAlertServerResponseSnooze,

	/**
	 The Alert Server wishes the Alarm Server to
	 temporarily pause all sound (i.e stop sending sound
	 play events to the Alert Server).
	 */
	EASAltAlertServerResponsePauseSound
	};

/**
 Flags for TASAltClientServerStateFlags
 */
enum TASAltStateFlags
	{
	/**
	 The Alert Server should not play any sound
	 */
	EASAltStateFlagsSilentRunning = 1,

	/**
	 The Alarm Server is currently within a quiet period
	 */
	EASAltStateFlagsInQuietPeriod = 2,

	/**
	 The Alarm Server currently has more than one alarm
	 ready to notify.
	 */
	EASAltStateFlagsMoreThanOneDueAlarm	= 3,

	/**
	 There wasn't sufficient memory within the Alarm
	 Server to allocate room for a snoozed alarm. I'm
	 note convinced we need this anymore
	 */
	EASAltStateFlagsNoMemoryForSnoozeAlarm = 4,

	/**
	 There isn't any sound filename for the current
	 alarm.
	 */
	EASAltStateFlagsAlarmHasNoSoundFileName	= 5,

	/**
	 This isn't used by the Alert Server.
	 */
	EASAltStateFlagsSoundIsPaused = 6

	};

// Literal constants
_LIT(KAlarmAlertServerName, "!AlarmAlertServer");


#endif
