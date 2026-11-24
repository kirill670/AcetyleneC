// EIKALSRV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKALSRV_H__)
#define __EIKALSRV_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

//
// class CEikServAlarmAlertServer
//

class CEikServAppUi;
class MEikServAlarmFactory;
class MEikServAlarm;

class CEikServAlarmAlertSession;


class CEikServAlarmAlertServer : public CServer2
/** 
@internalComponent
*/
	{
public:
	static CEikServAlarmAlertServer* NewL(MEikServAlarmFactory* aAlarmControl);
public: // from CServer
	virtual CSession2* NewSessionL(const TVersion& aVersion,const RMessage2& aMessage) const;
public: // Internal to Symbian
	IMPORT_C void HandleSwitchOnEvent();
public:
	void TaskKeyPressedL();
	inline TBool AlarmAlertIsVisible() const;
	inline void SessionDied();
private:
	CEikServAlarmAlertServer(TInt aPriority);
private:
	CEikServAlarmAlertSession* iSession; // iSession does not *own* what it points to
	MEikServAlarmFactory* iAlarmControl;
	};

//
// class CEikServAlarmAlertSession
//

class CEikAlmControlSupervisor;


class CEikServAlarmAlertSession : public CSession2
/**
@internalComponent 
*/
	{
public:
	static CEikServAlarmAlertSession* NewL(MEikServAlarmFactory* aAlarmControl);
	~CEikServAlarmAlertSession();
	void TaskKeyPressedL();
	void HandleSwitchOnEvent();
	inline TBool AlarmAlertIsVisible() const;
private:
	inline CEikServAlarmAlertSession() {}
	void ConstructL(MEikServAlarmFactory* aAlarmControl);
	CEikServAlarmAlertServer* AlarmAlertServer() const;
	virtual void ServiceL(const RMessage2 &aMessage);
private:
	CEikAlmControlSupervisor* iAlarmSupervisor;
	TBool iVisible;
	};

inline TBool CEikServAlarmAlertServer::AlarmAlertIsVisible() const { return iSession->AlarmAlertIsVisible(); }
inline void CEikServAlarmAlertServer::SessionDied() { iSession=NULL; }
//
inline TBool CEikServAlarmAlertSession::AlarmAlertIsVisible() const { return iVisible; }

#endif
