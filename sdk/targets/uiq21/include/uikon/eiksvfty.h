// EIKSVFTY.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
// Standard factory definitions

#ifndef __EIKSVFTY_H__
#define __EIKSVFTY_H__

// System includes
#include <e32std.h>

// Classes referenced
class TASShdAlarm;
class CEikAlmControlSupervisor;

class MEikNotifyAlertCompletionObserver
	{
public:
	virtual void HandleAlertCompletion(const TInt aButtonVal)=0;
	};

class MEikServNotifyAlert
	{
public:
	virtual void Release()=0;
	virtual void DisplayNotifier(const TDesC& aTitle,const TDesC& aLabel,const TDesC& aBut1,const TDesC& aBut2, MEikNotifyAlertCompletionObserver* aObserver)=0;
	};

class MEikServAlarm
	{
public:
	virtual void Release()=0;
	virtual void ShowAlarm()=0;
	virtual void HideAlarm()=0;
	virtual TInt CurrentServerState() const=0;
	virtual void UpdateSoundPauseTimeInterval(TInt aMinutes)=0;
	virtual void UpdateForAlarmServerState(TInt aNewAlarmServerState)=0;
	virtual void UpdateAlarmInfo(const TASShdAlarm& aAlarm,const TFullName& aOwner)=0;
	virtual void StartPlayAlarmL(const TDesC& aAlarmName)=0;
	virtual void StopPlayAlarm()=0;
	};

class MEikServAlarmFactory
	{
	public:
		virtual MEikServAlarm* NewAlarmL(CEikAlmControlSupervisor& aSupervisor)=0;
	};

#endif
