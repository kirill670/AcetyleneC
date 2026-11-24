// EIKALSUP.H
//
// Copyright (c) Symbian Software Ltd 1997-2004. All rights reserved.
//
#ifndef __EIKALSUP_H__
#define __EIKALSUP_H__

// System includes
#include <e32base.h>
#include <eiksvfty.h>
#include <asaltdefs.h>

// Constants
/** @internalComponent */
const TInt KAlarmSnoozeIncrement=5;


class CEikAlmControlSupervisor : public CBase
/** Provides an interface between the alarm server and applications that need to 
handle expiring alarms. 

When an alarm has expired, this class handles silencing, acknowledging and snoozing it, 
and users switching to another application (which causes the alarm to be snoozed for a 
default period).

@publishedPartner 
@released */
	{
public:
	enum TFlags
		{
		EHasMessageRequest		=0x00000002,
		EShouldCompleteMessage	=0x00000004,
		EHasMessageLogon		=0x00000008
		};
	/** The priority of the periodic timer that is used to count down the snooze period. */
	enum TPriority 
		{ 
		/** The timer's priority. This value is between EPriorityStandard and 
		EPriorityUserInput. */
		ESnoozeCountDownPriority=0x00000001
		};
public:
	IMPORT_C CEikAlmControlSupervisor();
    IMPORT_C void ConstructL(MEikServAlarmFactory* aAlarmControl);
	~CEikAlmControlSupervisor();
	void CancelTimeCountDown();
	void SynchronizeCountDownTimer();
	inline TInt PauseSoundMinutes() const;
	inline TTime QuietPeriodEndTime() const;
public:
	IMPORT_C void CmdAcknowledgeAlarm();
	IMPORT_C void CmdPauseAlarmSoundL(TInt aNumMinutes=KAlarmSnoozeIncrement);
	inline void CmdPauseAlarmSound(TInt aNumMinutes=KAlarmSnoozeIncrement);
	IMPORT_C void CmdSilenceAlarmSound();
	IMPORT_C TBool CmdTaskAwayFromAlarmL();
	inline TBool CmdTaskAwayFromAlarm();
public:
	void ServiceL(const RMessage2& aMessage);
private:
	void UpdateDisplay();
	void StartTimeCountDown();
	static TInt CallbackSnoozeDecrement(TAny *aAlarmAlert);
	void DecrementSnoozeMinutes();
	void UpdateAlarmInfo(const RMessage2& aMessage);
	void UpdateSoundDeferTimeL(const RMessage2& aMessage);
	void StartPlayAlarmL(const RMessage2& aMessage);
	void StopPlayAlarm();
	void ReturnTimeToSnoozeL(const RMessage2& aMessage);
	void SetAlertState(TInt aAlarmServerStateFlags);
private:
	CPeriodic* iMinuteCountDown;
	TInt iPauseSoundMinutes;
	TTime iPauseSoundDueTime;
	TTime iQuietPeriodEndTime;
	RMessage2 iMessage;
	MEikServAlarm* iAlarmAlert;
	};

inline TInt CEikAlmControlSupervisor::PauseSoundMinutes() const
/** Gets the number of minutes remaining in the alarm's snooze period, before 
the alarm is due to expire again.

@return The number of minutes remaining in the alarm's snooze period. */
	{
	return(iPauseSoundMinutes);
	}

inline TTime CEikAlmControlSupervisor::QuietPeriodEndTime() const
/** Gets the end time for the alarm server's quiet period. 

During a quiet period, any alarms that are due to expire are 
deferred until the quiet period is over. Not all UIs support 
this feature.

@return The end time for the quiet period (if any). */
	{
	return(iQuietPeriodEndTime);
	}

inline void CEikAlmControlSupervisor::CmdPauseAlarmSound(TInt aNumMinutes)
/** @deprecated

Deprecated in 7.0s. Use CEikAlmControlSupervisor::CmdPauseAlarmSoundL() instead 
because RMessage::WriteL() could leave. */
	{ CmdPauseAlarmSoundL(aNumMinutes); }

inline TBool CEikAlmControlSupervisor::CmdTaskAwayFromAlarm()
/** @deprecated

Deprecated in 7.0s. Use CEikAlmControlSupervisor::CmdTaskAwayFromAlarmL() instead 
because RMessage::WriteL() could leave. */
	{ return CmdTaskAwayFromAlarmL(); }

#endif
