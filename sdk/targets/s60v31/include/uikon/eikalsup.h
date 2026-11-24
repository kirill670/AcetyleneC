// EIKALSUP.H
//
// Copyright (c) Symbian Software Ltd 1997-2005. All rights reserved.
//
/**
@file
@internalComponent
*/
#ifndef __EIKALSUP_H__
#define __EIKALSUP_H__

// System includes
#include <e32base.h>
#include <eiksvfty.h>
#include <asaltdefs.h>
#include <eikalsrv.h>

// Constants
/** @internalComponent */
const TInt KAlarmSnoozeIncrement=5;  //default snooze increment in minutes


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
	/** The priority of the periodic timer that is used to count down the snooze period. */
	enum TPriority 
		{ 
		/** The timer's priority. This value is between EPriorityStandard and 
		EPriorityUserInput. */
		ESnoozeCountDownPriority=0x00000001
		};

public:  //exported API
	inline TInt PauseSoundMinutes() const;
	inline TTime QuietPeriodEndTime() const;
	IMPORT_C void CmdAcknowledgeAlarm();
	IMPORT_C void CmdPauseAlarmSoundL(TInt aNumMinutes=KAlarmSnoozeIncrement);
	inline void CmdPauseAlarmSound(TInt aNumMinutes=KAlarmSnoozeIncrement);
	IMPORT_C void CmdSilenceAlarmSound();
	IMPORT_C TBool CmdTaskAwayFromAlarmL();
	IMPORT_C TBool CmdTaskAwayFromAlarmL(TInt aMinutesToSnooze);
	inline TBool CmdTaskAwayFromAlarm();

	IMPORT_C TDesC8& AlarmData() const;
	IMPORT_C void CmdAcknowledgeAllAlarms();
	
public:  //internal for UIKON
	~CEikAlmControlSupervisor();
	void CancelTimeCountDown();
	void SynchronizeCountDownTimer();
	void ServiceL(const RMessage2& aMessage);

	static CEikAlmControlSupervisor* NewL(MEikServAlarmFactory* aAlarmControl, CEikServAlarmAlertSession* aSession);
	TBool IsVisible()  ;
	TAlarmId AlarmId() ;

protected:
	IMPORT_C virtual void CEikAlmControlSupervisor_Reserved1();
	IMPORT_C virtual void CEikAlmControlSupervisor_Reserved2();

private:
	void StartTimeCountDown();
	static TInt CallbackSnoozeDecrement(TAny *aAlarmAlert);
	void DecrementSnoozeMinutes();
	void SetAlertState(TInt aAlarmServerStateFlags);
	void StartPlayAlarmL(const RMessage2& aMessage);
	void StopPlayAlarm();

	CEikAlmControlSupervisor();
	void ConstructL(MEikServAlarmFactory* aAlarmControl, CEikServAlarmAlertSession* aSession);
	TTime ReturnTimeToSnoozeL(TInt aMinutesToSnooze);	
	void UpdateAlarmInfoL(const RMessage2& aMessage);
	void SetVisibility(TBool aVisible);

private:
	CPeriodic* iMinuteCountDown;
	TInt iPauseSoundMinutes;
	TTime iPauseSoundDueTime;
	
	HBufC8*	iAlarmData;
	TBool iVisible;
	CEikServAlarmAlertSession* iSession;
	TAlarmId iAlarmId;

	MEikServAlarm* iAlarmAlert;
	TInt iCEikAlmControlSupervisor_Reserved1;
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

	return(iSession->QuietPeriodEndTime());
	
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
