// MMFSUBTHREADBASE.H
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MMFSUBTHREADBASE_H__
#define __MMFSUBTHREADBASE_H__

#include <e32base.h>
#include <e32std.h>
#include <mmf\common\mmfpaniccodes.h>
#include <mmf\common\MmfController.h>

/**
 * @publishedAll
 */
static const TInt KMMFSubThreadMaxCachedMessages = 4;
/**
 * @publishedAll
 */
static const TInt KMMFSubThreadMaxHeapSize = 0x100000;//1MB


/**
@publishedAll

All message id's to be decoded by any subthread server
*/
enum TMMFSubThreadMessageIds
	{
	EMMFSubThreadReceiveEvents,
	EMMFSubThreadCancelReceiveEvents,
	EMMFSubThreadShutdown,
	EMMFDataPathProxyLoadDataPathBy,
	EMMFDataPathProxyLoadDataPathByMediaId,
	EMMFDataPathProxyLoadDataPathByCodecUid,
	EMMFDataPathProxyLoadDataPathByMediaIdCodecUid,
	EMMFDataPathProxyAddDataSource,
	EMMFDataPathProxyAddDataSink,
	EMMFDataPathProxyPrime,
	EMMFDataPathProxyPlay,
	EMMFDataPathProxyPause,
	EMMFDataPathProxyStop,
	EMMFDataPathProxyGetPosition,
	EMMFDataPathProxySetPosition,
	EMMFDataPathProxySetPlayWindow,
	EMMFDataPathProxyClearPlayWindow,
	EMMFDataPathProxyState,
	EMMFAudioPolicyProxyGetAudioPolicy
	};



class RMMFSubThreadBase : public RMmfSessionBase
/**
@internalTechnology

Base class for clients to MMF sub threads.
Provides functionality to start the sub thread and transmit events from subthread to main thread.
*/
	{
public:
	RMMFSubThreadBase(TTimeIntervalMicroSeconds32 aShutdownTimeout) : iShutdownTimeout(aShutdownTimeout) {};
	/**
	Returns the id of the subthread, allowing a client to logon to the thread to receive notification of its death.
	*/
	TThreadId SubThreadId() {return iSubThread.Id();};
	/**
	Allows a client to receive events from the subthread.
	*/
	IMPORT_C void ReceiveEvents(TMMFEventPckg& aEventPckg, TRequestStatus& aStatus);
	IMPORT_C TInt CancelReceiveEvents();
	/**
	Signal to the subthread to exit.
	Note: This function will not return until the subthread has exited, or a timeout has occurred.
	*/
	IMPORT_C void Shutdown();
protected:
	/**
	Should be called by derived classes to start the subthread.
	*/
	TInt DoCreateSubThread(const TDesC& aName, TThreadFunction aFunction, TBool aUseNewHeap = EFalse);
	void Panic(TMMFSubThreadPanicCode aPanicCode);
protected:
	RThread iSubThread;
	TTimeIntervalMicroSeconds32 iShutdownTimeout;
	};


class CMMFSubThreadShutdown : public CTimer
/**
@internalTechnology

Used to Kill the subthread either immediately or after a timeout.
Used by the subthread on startup to prevent orphaning if no sessions are created to it.
*/
	{
	enum {EMMFSubThreadShutdownDelay=1000000};	// 1s
public:
	static CMMFSubThreadShutdown* NewL();
	CMMFSubThreadShutdown();
	void ConstructL();
	void Start();
	void ShutdownNow();
private:
	void RunL();
	};


class TMMFSubThreadStartParams
/**
@internalTechnology

Startup parameters passed into the threadfunction of the subthread.
Used to signal back to the main thread when the subthread is fully started.
*/
	{
public:
	TMMFSubThreadStartParams(TRequestStatus& aStatus) : iStatus(&aStatus), iThreadId(RThread().Id())
		{aStatus=KRequestPending;};
	void SignalL()
		{
		RThread starter;
		User::LeaveIfError(starter.Open(iThreadId));
		starter.RequestComplete(iStatus,KErrNone);
		starter.Close();
		};
public:
	TRequestStatus* iStatus;
	TThreadId iThreadId;
	};


class CMMFSubThreadServer : public CMmfIpcServer
/**
@internalTechnology

Subthread server base class.
Provides session counting and will kill the subthread immediately when the session count reaches zero.
Starts the shutdown timer on construction to prevent orphaning if no sessions are created.
*/
	{
public:
	virtual ~CMMFSubThreadServer();
	virtual void SessionCreated();
	virtual TInt RunError(TInt aError);
	virtual void ShutdownNow();
protected:
	virtual CMmfIpcSession* NewSessionL(const TVersion& aVersion) const = 0;
	CMMFSubThreadServer(TInt aPriority);
	void ConstructL();
private:
	CMMFSubThreadShutdown* iShutdownTimer;
	};


class CMMFSubThreadEventReceiver : public CBase
/**
@internalTechnology

Used to hold on to an RMessage so we can complete it asynchronously to send an event to the main thread.
*/
	{
public:
	static CMMFSubThreadEventReceiver* NewL(const RMmfIpcMessage& aMessage);
	~CMMFSubThreadEventReceiver();
	void SendEvent(const TMMFEvent& aEvent);
private:
	CMMFSubThreadEventReceiver(const RMmfIpcMessage& aMessage);
private:
	RMmfIpcMessage iMessage;
	TBool iNeedToCompleteMessage;
	};


class CMMFSubThreadSession : public CMmfIpcSession, public MAsyncEventHandler
/**
@internalTechnology

Subthread session base class.
Derived classes must implement the ServiceL() method.
*/
	{
public:
	virtual ~CMMFSubThreadSession();
	void CreateL(const CMmfIpcServer& aServer);
	virtual void ServiceL(const RMmfIpcMessage& aMessage) = 0;
	//from MAsyncEventHandler
	TInt SendEventToClient(const TMMFEvent& aEvent);
protected:
	CMMFSubThreadSession() {};
	TBool ReceiveEventsL(const RMmfIpcMessage& aMessage);
	TBool CancelReceiveEvents();
	TBool ShutDown();
protected:
	CMMFSubThreadServer* iServer;
private:
	CMMFSubThreadEventReceiver* iEventReceiver;
	RArray<TMMFEvent> iEvents;
	};



#endif

