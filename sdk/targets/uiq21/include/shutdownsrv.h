// SHUTDOWNSRV.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__SHUTDOWNSRV_H__)
#define __SHUTDOWNSRV_H__

#include <e32base.h>
#include <savenotf.h>


/**
 *
 * @internal
 */
class MShutdownEventObserver
	{
public:
	virtual void HandleShutdownEventL(MSaveObserver::TSaveType aAction,TBool aPowerOff)=0;
	virtual CArrayFix<TThreadId>* ClientArrayLC()=0;
	virtual TBool IsClientHung(TThreadId aId) const=0;
	virtual void GetShutdownState(TBool& aPowerOff, TBool& aAllSessionsHavePendingRequest) const=0;
	};

/**
 *
 * .
 *
 * @internal
 * @since     7.0
 */
class CServShutdownServer : public CServer, public MShutdownEventObserver
	{
public:
	IMPORT_C static CServShutdownServer* NewL();
	IMPORT_C ~CServShutdownServer();
	IMPORT_C void HandlePowerNotifRequest(const RThread& aClient);
	IMPORT_C void NotifySave(MSaveObserver::TSaveType aSaveType);
	IMPORT_C TBool IsPowerOff() const;
	IMPORT_C void CancelPowerOff();
public:
	IMPORT_C virtual void ConstructL();
public: // from MShutdownEventObserver
	IMPORT_C void HandleShutdownEventL(MSaveObserver::TSaveType aAction,TBool aPowerOff);
	IMPORT_C CArrayFix<TThreadId>* ClientArrayLC();
	IMPORT_C TBool IsClientHung(TThreadId aId) const;
	IMPORT_C void GetShutdownState(TBool& aPowerOff, TBool& aAllSessionsHavePendingRequest) const;
protected:
	IMPORT_C CServShutdownServer(TInt aPriority);
private:
	void SwitchOff();
	TBool AllSessionsHavePendingRequest() const;
private: // from CServer
	CSharableSession* NewSessionL(const TVersion& aVersion) const;
private:
	TBool iPowerOff;
	};

/**
 *
 * .
 *
 * @internal
 * @since     7.0
 */
class CServShutdownSession : public CSession
	{
public:
	IMPORT_C ~CServShutdownSession();
protected:
	IMPORT_C CServShutdownSession(RThread aClient);
public:
	static CServShutdownSession* NewL(RThread aClient);
	TBool HasPendingRequest() const;
	void NotifySave(MSaveObserver::TSaveType aSaveType);
protected: // from CSession
	IMPORT_C void ServiceL(const RMessage& aMessage);
private:
	void RequestNotifyPowerDown(const RMessage& aMessage);
	void RequestNotifyPowerDownCancel();
	void HandleSaveErrorL(const RMessage& aMessage);
	void DoServiceL(const RMessage& aMessage, TBool& aCompleteRequest);
private:
	RMessagePtr iPtr;
	TInt iCurrentEvent;
	TInt iOutstandingEvent;
	};

#endif
