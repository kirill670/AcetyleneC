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
	{
public:
	virtual void AlarmServerTerminated() = 0;
	};


/**
 * Represents the interface between the agenda model and the alarm
 * server.
 *
 * A session with the alarm server is created in the <code>NewL()</code>
 * function. The agenda model's next due alarm is retrieved and set as
 * the session alarm (using <code>FindAndQueueNextAlarmL()</code>). This
 * is added to the alarm server's pending alarm queue and is handled by
 * the alarm server when its due time is reached. At ER5.1, a new
 * function <code>FindAndQueueNextFewAlarmsL()</code> was added. This
 * allows the queuing of several alarms with the alarm server.If the
 * session with the alarm server is disconnected, the session alarm is
 * cancelled. If you want the alarm to run after the session has been
 * disconnected, the alarm must be orphaned.Optionally, a callback may be
 * passed to the object on construction. This callback defines a single
 * function <code>AlarmServerTerminated()</code>. This function is called
 * if notification is requested (using
 * <code>RequestServerTerminationNotification()</code>) when the session
 * is disconnected from the alarm server.After disconnection occurs, an
 * attempt may be made to reconnect to the server using
 * <code>Connect()</code>. Once a connection has been re-established you
 * should call <code>RestartL()</code> to re-queue the agenda model's
 * next outstanding alarm with the alarm server.
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class CAgnAlarm : public CBase
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
	inline RASCliSession& AlarmServer() { return (iAlarmServer); }// for test code
private:
	void ConstructL(CAgnEntryModel* aModel,MAgnAlarmServerTerminationCallBack* aCallBack);
	CAgnAlarmActive*					iAlarm;
	CAgnAlarmServerTerminationActive*	iNotifier;
	RASCliSession						iAlarmServer;
	};


struct TAgnAlarmEntry
	{
	TAgnDateTime	iDueDateTime;
	TTime			iAlarmTime;
	TAlarmMessage	iMessage;
	TAlarmSoundName iSound;
	TAgnInstanceId	iInstanceId;
	};

class CAgnAlarmActive : public CActive
 	{
public:	
	static CAgnAlarmActive* NewL(CAgnEntryModel* aModel,RASCliSession& aAlarmServer);
	virtual ~CAgnAlarmActive();
	virtual void RunL();
	void FindAndQueueNextAlarmL();
	void FindAndQueueNextFewAlarmsL(const TInt aMaxNumberOfAlarms,const TInt aMaxNumberOfDays);
	void RequestNotification();
	inline void SetModel(CAgnEntryModel* aModel) { iModel = aModel; };
	void SetDefaultTitleL(const TDesC& aDefaultTitle);
	TPtrC DefaultTitle() const;
	void OrphanAlarm();
	void QueueNextAlarmL(CArrayFixFlat<TAgnSortInstance>*aAlarmedIds);
private:
	CAgnAlarmActive(TInt aPriority,RASCliSession& aAlarmServer);
	void UpdateAlarmListL(CArrayFixFlat<TAgnSortInstance>* aAlarmedIds,
							CArrayFixFlat<TAgnSortInstance>* aDayInfoList,
							TAgnDate aCurrentDate, const TAgnDateTime& aNow,TAgnDateTime& aNextAlarm);
	virtual void DoCancel();
private:
	enum {EPriority=100,EGranularity=2};
	RASCliSession&					iAlarmServer;
	CArrayFixFlat<TAgnAlarmEntry>*	iAlarmList;	
	TInt							iAlarmListIndex; //index of the currently queued alarm 	
	CAgnEntryModel*					iModel; // pointer to owning CAgnEntryModel class
	HBufC*							iDefaultTitle;
	TASShdAlarm						iAlarm;
	};


class CAgnAlarmServerTerminationActive : public CActive
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
private:
	enum {EPriority = 100};
	TAlarmId			iAlarmId;
	RASCliSession&		iAlarmServer;
	MAgnAlarmServerTerminationCallBack*	iCallBack;
	TRequestStatus*		iUserRequestStatus;
	CAgnAlarm*			iOwningObject;
	};

#endif
