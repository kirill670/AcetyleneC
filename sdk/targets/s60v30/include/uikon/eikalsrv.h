// EIKALSRV.H
//
// Copyright (c) Symbian Software Ltd 1997 - 2005.  All rights reserved.
//
/**@file
*/


#if !defined(__EIKALSRV_H__)
#define __EIKALSRV_H__

#include <e32base.h>

#ifdef SYMBIAN_FLEXIBLE_ALARM
 #include <asaltdefs.h>
 #include <asshddefs.h>
#endif


class CEikServAppUi;
class MEikServAlarmFactory;
class MEikServAlarm;

class CEikServAlarmAlertSession;

/** 
@internalComponent
*/

class CEikServAlarmAlertServer : public CPolicyServer
	{
public:
	IMPORT_C static CEikServAlarmAlertServer* NewL(MEikServAlarmFactory* aAlarmControl);
	IMPORT_C void HandleSwitchOnEvent();
	IMPORT_C void TaskKeyPressedL();
	inline TBool AlarmAlertIsVisible() const;
	inline void SessionDied();
	virtual CSession2* NewSessionL(const TVersion& aVersion,const RMessage2& aMessage) const;
#ifdef SYMBIAN_FLEXIBLE_ALARM	
	IMPORT_C static CEikServAlarmAlertServer* NewL(MEikServAlarmFactory* aAlarmControl, TInt aMaxAlarms);
	IMPORT_C void SetQuietPeriodL(TTime aQuietPeriodEndTime);
	IMPORT_C void ClearAllAlarmsL();	
#endif //SYMBIAN_FLEXIBLE_ALARM

private:
#ifdef SYMBIAN_FLEXIBLE_ALARM	
	CEikServAlarmAlertServer(TInt aPriority, MEikServAlarmFactory* aAlarmControl,  TInt aMaxAlarms);
#else
	CEikServAlarmAlertServer(TInt aPriority);
#endif	//SYMBIAN_FLEXIBLE_ALARM
	

private:
	CEikServAlarmAlertSession* iSession; // iSession does not *own* what it points to
	MEikServAlarmFactory* iAlarmControl;
#ifdef SYMBIAN_FLEXIBLE_ALARM
	TInt iMaxAlarms;
#endif	
	};




class CEikAlmControlSupervisor;

#ifdef SYMBIAN_FLEXIBLE_ALARM

/** 
Helper class for CEikServAlarmAlertSession. Holds response data for queuing
@internalComponent
*/
class TAlarmResponse
	{
public:	
	TAlarmResponse (TASAltAlertServerResponse  aCode,  TAlarmId aId, TTime aTime);
	TASAltAlertServerResponse ResponseCode () const;
	TAlarmId AlarmId () const;
	TTime TimeToSnooze() const;

private:
	TASAltAlertServerResponse  iCode;
	TAlarmId iId;
	TTime iTime;
	};
	
// supposed to be maximum one response in a queue, because client should resubmit request 
// for response as soon	as it receive previous 
const TInt KAlertResponseQueueSize = 20;	
#endif // SYMBIAN_FLEXIBLE_ALARM

/**
Represents a session for a client thread on the server-side.
@internalComponent 
*/
class CEikServAlarmAlertSession : public CSession2

	{
public:
	~CEikServAlarmAlertSession();
	void TaskKeyPressedL();
	void HandleSwitchOnEvent();
	inline TBool AlarmAlertIsVisible() const;

#ifndef SYMBIAN_FLEXIBLE_ALARM	
	static CEikServAlarmAlertSession* NewL(MEikServAlarmFactory* aAlarmControl);
#else
	static CEikServAlarmAlertSession* NewL(MEikServAlarmFactory* aAlarmControl, TInt aMaxAlarms);
	void SetQuietPeriodL(TTime aQuietPeriodEndTime);
	inline TTime QuietPeriodEndTime() const; 
	void RespondEventL(TASAltAlertServerResponse aCode);
	void RespondEventL(TASAltAlertServerResponse aCode,TAlarmId aId, TTime aTimeToSnooze=0);
	void ClearAllAlarmsL();
#endif // SYMBIAN_FLEXIBLE_ALARM	

private:
	CEikServAlarmAlertServer* AlarmAlertServer() const;
	void ConstructL(MEikServAlarmFactory* aAlarmControl);
	virtual void ServiceL(const RMessage2 &aMessage);

#ifdef SYMBIAN_FLEXIBLE_ALARM	
	CEikServAlarmAlertSession(MEikServAlarmFactory* aAlarmControl, TInt aMaxAlarms);
	void QueueEventL (TASAltAlertServerResponse&  aCode,TAlarmId& aId, TTime& aTimeToSnooze);
	TInt FindAlarm (TAlarmId aAlarmId);
	void DeleteAlarmL(const RMessage2& aMessage);
	void UpdateVisibility();
#else
	inline CEikServAlarmAlertSession() {}
#endif // SYMBIAN_FLEXIBLE_ALARM

private:
#ifndef SYMBIAN_FLEXIBLE_ALARM
	CEikAlmControlSupervisor* iAlarmSupervisor;
#endif	
	TBool iVisible;

#ifdef SYMBIAN_FLEXIBLE_ALARM
	MEikServAlarmFactory* iAlarmControlFactory;
	TTime iQuietPeriodEndTime;
	TInt iMaxAlarms;
	RPointerArray<CEikAlmControlSupervisor> iAlarmSupervisors;
	RArray <TAlarmResponse> iResponseQueue;
	RMessage2 iMessage;
#endif // SYMBIAN_FLEXIBLE_ALARM
	};

inline TBool CEikServAlarmAlertServer::AlarmAlertIsVisible() const { return iSession->AlarmAlertIsVisible(); }

inline TBool CEikServAlarmAlertSession::AlarmAlertIsVisible() const { return iVisible; }

inline void CEikServAlarmAlertServer::SessionDied() { iSession=NULL; }

#ifdef SYMBIAN_FLEXIBLE_ALARM
inline TTime CEikServAlarmAlertSession::QuietPeriodEndTime() const { return iQuietPeriodEndTime; }
#endif // SYMBIAN_FLEXIBLE_ALARM

#endif //__EIKALSRV_H__
