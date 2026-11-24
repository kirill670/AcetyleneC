// AGMALARM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMALARM_H__
#define __AGMALARM_H__

// System includes
#include <e32base.h>
#include <asshdalarm.h>
#include <asclisession.h>

// User includes
#include "agmdate.h"
#include "agmxsort.h"

// Classes referenced
class CAgnModel;
class CAgnEntryModel;
class CAgnAlarmActive;
class CAgnAlarmServerTerminationActive;

// Constants
const TUid KUidAgendaModelAlarmCategory = { 0x101F4A70 };

class MAgnAlarmServerTerminationCallBack
/** The interface for an alarm server termination notifier.
If an object that implements this interface is supplied to 
CAgnAlarm::NewL(), its AlarmServerTerminated() function is 
called if the alarm server terminates.

@publishedAll
@released
*/
	{
public:
	/** Callback function that is called if the alarm server terminates. */
	virtual void AlarmServerTerminated() = 0;
	};

struct TAgnAlarmEntry
/**
@internalComponent
@released
*/
	{
	TAgnDateTime	iDueDateTime;
	TTime			iAlarmTime;
	TAlarmMessage	iMessage;
	TAlarmSoundName iSound;
	TAgnInstanceId	iInstanceId;
	TAlarmDayOrTimed	iSessionType;	// RASCliSession
	};

class CAgnAlarm : public CBase
/** The interface between the agenda model and the alarm server.

A session with the alarm server is created in the NewL() function. The agenda 
model's next due alarm is set as the session alarm using FindAndQueueNextAlarmL(). 
It is added to the alarm server's pending alarm queue and is handled by 
the alarm server when its due time is reached. 

If the session with the alarm server is disconnected, the session alarm is 
cancelled. If you want the alarm to run without reconnecting to the server, 
the alarm must be orphaned. Alternatively, you can reconnect to the server 
and re-queue the session alarm with the server using RestartL(). 

Optionally, a callback provider may be passed to the object on construction. This 
object defines a single function which is called if the alarm server terminates. 
For notification without a callback, call RequestServerTerminationNotification() instead.

@publishedAll
@released
*/
	{
public:
	IMPORT_C static CAgnAlarm* NewL(CAgnEntryModel* aModel,MAgnAlarmServerTerminationCallBack* aCallBack=NULL);
	IMPORT_C virtual ~CAgnAlarm();
	IMPORT_C void FindAndQueueNextAlarmL();
	IMPORT_C void FindAndQueueNextFewAlarmsL(const TInt aMaxNumberOfAlarms=10,const TInt aMaxNumberOfDays=31);
	IMPORT_C void SetModel(CAgnEntryModel* aModel);
	IMPORT_C void SetDefaultTitleL(const TDesC& aDefaultTitle);
	IMPORT_C TPtrC DefaultTitle() const;
	IMPORT_C TInt Connect();
	IMPORT_C void RestartL();
	IMPORT_C void RequestServerTerminationNotification(TRequestStatus& aStatus);
	IMPORT_C void CancelServerTerminationNotification();
	IMPORT_C void OrphanAlarm();
	void QueueNextAlarmL(CArrayFixFlat<TAgnSortInstance>*aAlarmedIds);
	void DeleteEntriesSnoozedAlarmL(const TAgnInstanceId& aEntryInstanceId);
	const TAgnAlarmEntry* AlarmEntry() const;
    void FindAndQueueNextFewAlarmsL(const TTime& startTime,const TTime& endTime,const TInt aMaxNumberOfAlarms=10);

private:
	void ConstructL(CAgnEntryModel* aModel,MAgnAlarmServerTerminationCallBack* aCallBack);
	CAgnAlarmActive*					iAlarm;
	CAgnAlarmServerTerminationActive*	iNotifier;
	RASCliSession						iAlarmServer;
	};

struct TAgnAlarmInfo
/**
Defines a system-wide unique agenda entry reference.

@publishedAll
@released
*/
	{
	TUid iAlarmCategory;
	TAgnInstanceId iAgnInstanceId;
	TFileName iFileName;
	};


typedef TPckgC<TAgnAlarmInfo> TPkgCAgnAlarmInfo;


class CAgnAlarmActive : public CActive
/**
@internalComponent
@released
*/
 	{
public:
	static CAgnAlarmActive* NewL(CAgnEntryModel* aModel,RASCliSession& aAlarmServer);
	virtual ~CAgnAlarmActive();
	virtual void RunL();
	void FindAndQueueNextAlarmL();
	void FindAndQueueNextFewAlarmsL(const TInt aMaxNumberOfAlarms,const TInt aMaxNumberOfDays);
	void FindAndQueueNextFewAlarmsL(const TTime& startTime,const TTime& endTime,const TInt aMaxNumberOfAlarms);

	void RequestNotification();
	inline void SetModel(CAgnEntryModel* aModel) { iModel = aModel; };
	void SetDefaultTitleL(const TDesC& aDefaultTitle);
	TPtrC DefaultTitle() const;
	void OrphanAlarm();
	void QueueNextAlarmL(CArrayFixFlat<TAgnSortInstance>*aAlarmedIds);
	const TAgnAlarmEntry* CurrentAlarmEntry() const; 
private:
	CAgnAlarmActive(TInt aPriority,RASCliSession& aAlarmServer);
	TAgnAlarmInfo GetAgnAlarmInfoL(const TAgnInstanceId aInstanceId);
	void GetAgnAlarmInfoL(const TAgnInstanceId& aInstanceId, TAgnAlarmInfo& aAlarmInfo);
	void UpdateAlarmListL(CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,
							CArrayFixFlat<TAgnSortInstance>* aDayInfoList,
							TAgnDate aCurrentDate, const TAgnDateTime& aNow,TAgnDateTime& aNextAlarm);
	void InitialiseAlarm(TASShdAlarm& aAlarm, const TAgnAlarmEntry& aEntryAlarm, TBool aIsSessionAlarm); 

	virtual void DoCancel();
private:
	enum {EPriority=100,EGranularity=2};
	RASCliSession&					iAlarmServer;
	CArrayFixFlat<TAgnAlarmEntry>*	iAlarmList;
	TInt							iAlarmListIndex; //index of the currently queued alarm
	CAgnEntryModel*                     iModel; // pointer to owning CAgnModel class
	HBufC*							iDefaultTitle;
	TASShdAlarm						iAlarm;
	};

class CAgnAlarmServerTerminationActive : public CActive
/**
@internalComponent
@released
*/
	{
public:
	static CAgnAlarmServerTerminationActive* NewL(RASCliSession& aAlarmServer,MAgnAlarmServerTerminationCallBack* aCallBack,CAgnAlarm* aOwningObject);
	virtual ~CAgnAlarmServerTerminationActive();
	virtual void RunL();
	void Start();
	void RequestServerTerminationNotification(TRequestStatus& aStatus);
	void CancelServerTerminationNotification();
private:
	CAgnAlarmServerTerminationActive(TInt aPriority,RASCliSession& aAlarmServer,CAgnAlarm* aOwningObject);	
	virtual void DoCancel();
	virtual TInt RunError(TInt aError);
private:
	enum {EPriority = 100};
	TAlarmId			iAlarmId;
	RASCliSession&		iAlarmServer;
	MAgnAlarmServerTerminationCallBack*	iCallBack;
	TRequestStatus*		iUserRequestStatus;
	CAgnAlarm*			iOwningObject;
	};

#endif
