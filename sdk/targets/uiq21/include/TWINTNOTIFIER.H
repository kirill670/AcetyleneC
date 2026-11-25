// TWINTNOTIFIER.H
//
// Copyright (c) 1995-2000 Symbian Ltd.  All rights reserved.
//
// Text Window Server text notifiers.
//

#ifndef __TWINTNOTIFIER_H__
#define __TWINTNOTIFIER_H__

#include <f32file.h>


//  Notifier Plugin architecture copied from UIKON

_LIT(KNotifierPlugInExt,"*.*");
_LIT(KNotifierPlugInSearchPath,"\\system\\tnotifiers\\");
const TUid KUidNotifierPlugIn={0x10005522}; 

_LIT8(KNotifierPaused,"Eik_Notifier_Paused");
_LIT8(KNotifierResumed,"Eik_Notifier_Resumed");

enum TNotExtStatus
	{
	ENotExtRequestCompleted	=0,
	ENotExtRequestQueued	=1,
	};

/**
 * Interface to allow notifiers to manage their own startup/shutdown.  This class is likely to be of most
 * interest to notifiers that observe engines using publically available APIs rather than those that are run
 * via RNotifier.
 */
class MNotifierManager
	{
public:
	virtual void StartNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse)=0;
	virtual void CancelNotifier(TUid aNotifierUid)=0;
	virtual void UpdateNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse)=0;
	};

/**
 * Plug-in format for server side notifiers.  Any number of MNotifierBase objects can be included in a single
 * dll.  All notifiers will be loaded during device startup and won't be destroyed until the notifier server
 * closes down.
 */
class MNotifierBase
	{
public:
	enum TNotifierPriority
		{
		ENotifierPriorityAbsolute=500,
		ENotifierPriorityVHigh=400,	
		ENotifierPriorityHigh=300,	
		ENotifierPriorityLow=200,	
		ENotifierPriorityVLow=100,	
		ENotifierPriorityLowest=0	
		};
public:
	class TNotifierInfo
		{
	public:
		TUid iUid;
		TUid iChannel;
		TInt iPriority;
		};
public:
	/**
	 * Called when all resources allocated by notifiers should be freed.
	 */
	virtual void Release()=0;
	/**
	 * Called when a notifier is first loaded to allow any initial construction that is required.
	 */
	virtual TNotifierInfo RegisterL()=0;
	/**
	 * Return the priority a notifier takes and the channels it acts on.  The return value may be varied 
	 * at run-time.
	 */
	virtual TNotifierInfo Info() const=0;
	/**
	 * Start the notifier with data aBuffer and return an initial response.
	 */
	virtual TPtrC8 StartL(const TDesC8& aBuffer)=0;
	/**
	 * Start the notifier with data aBuffer.  aMessage should be completed when the notifier is deactivated.
	 * May be called multiple times if more than one client starts the notifier.  The notifier is immediately
	 * responsible for completing aMessage.
	 */
	virtual void StartL(const TDesC8& aBuffer, const TAny* aReturnVal, RMessage aMessage)=0;
	/**
	 * The notifier has been deactivated so resources can be freed and outstanding messages completed.
	 */
	virtual void Cancel()=0;
	/**
	 * Update a currently active notifier with data aBuffer.
	 */
	virtual TPtrC8 UpdateL(const TDesC8& aBuffer)=0;
public:
	void SetManager(MNotifierManager* aManager);
protected:
	MNotifierManager* iManager;
private:
	TInt iNotBSpare;
	};

// Remaining classes are internal to the text window server

class CNotifierManager;

class CNotifierServer : public CServer
	{
public:
	static CNotifierServer* NewL();
	~CNotifierServer();
public: // from CServer
	CSharableSession* NewSessionL(const TVersion &aVersion) const;
public:
	CNotifierServer(TInt aPriority);
	inline CNotifierManager* Manager() const;
public:
	void SetIsExiting();
	TBool IsExiting() const;
private:
	void ConstructL();
private:
	CNotifierManager* iManager;
	TBool iExiting;
	};

class CNotifierSession : public CSession
	{
public:
	CNotifierSession(RThread aClient,const CNotifierServer& aServer);
	~CNotifierSession();
public: // from CSession
	void ServiceL(const RMessage &aMessage);
private:
	enum TNotifierPanic
		{ENotifierPanicBadDescriptor=0,};
private:
	void DisplayAlertL(const RMessage& aMessage);
	void DisplayInfoMsgL(const RMessage& aMessage);
	void DoStartNotifierL(const RMessage& aMessage);
	void DoUpdateNotifierL(const RMessage& aMessage);
	TInt StartNotifierAndGetResponseL(const RMessage& aMessage,TBool& aCleanupComplete);
	void PanicClient(const RMessage& aMessage,TNotifierPanic aCode);
	static TInt InfoPrintThread(TAny* aMessage);
public:
	static RSemaphore NotifierSemaphore;
private:
	const CNotifierServer* iServer;
	TInt iClientId;
	};

class CQueueItem;
class CChannelMonitor;
class CActivityMonitor;
class CNotifierQueue;

class CNotifierManager : public CBase, public MNotifierManager
	{
public:
	static CNotifierManager* NewL();
	~CNotifierManager();
	void RegisterL(RFs& aFs);
	TInt NotifierStartL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse,TInt aClientId);
	TInt NotifierUpdateL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse,TInt aClientId);
	TInt NotifierCancel(TUid aNotifierUid);
	TInt NotifierStartAndGetResponseL(TUid aNotifierUid,const TDesC8& aBuffer,const TAny* aResponse,
										const RMessage& aMessage,TInt aClientId,TBool& aCleanupComplete);
	void HandleClientExit(TInt aClientId);
	TInt NotifierStartAndGetResponseL(TUid aNotifierUid,TUid aChannelUid,const TDesC8& aBuffer,const TAny* aResponse,
										const RMessage& aMessage,TInt aClientId,TBool& aCleanupComplete);
public: // from MNotifierManager
	void StartNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);
	void CancelNotifier(TUid aNotifierUid);
	void UpdateNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);
private:
	void DoAddPlugInL(const TDesC& aPath,const TDesC& aFileName,const TUidType& aUidType);
	CNotifierManager();
	void ConstructL();
	void StartFromQueueL(CQueueItem* aItem);
private:
	CArrayPtr<MNotifierBase>* iObservedList;
	CArrayFix<RLibrary>* iLibraries;
	CChannelMonitor* iChannelMonitor;
	CActivityMonitor* iActivityMonitor;
	CNotifierQueue* iQueue;
	};

class TChannelActivity
	{
public:
	inline TChannelActivity(TUid aChannel,TInt aHighestPriorityRunning);
public:
	TUid iChannel;
	TInt iHighestPriorityRunning;
	};
	
class CChannelMonitor : public CBase
	{
public:
	static CChannelMonitor* NewL();
	inline void AddNewChannelL(TUid aChannel);
	TBool AlreadyHasChannel(TUid aChannel) const;
	TInt ActivityLevel(TUid aChannel) const;
	void UpdateChannel(TUid aChannel,TInt aLevel);
private:
	CChannelMonitor();
private:
	CArrayFixFlat<TChannelActivity> iMonitor;
	};

class CNotifierActivity : public CBase
	{
public:
	static CNotifierActivity* NewLC(const MNotifierBase::TNotifierInfo& aInfo,TInt aClientId);
	~CNotifierActivity();
	TInt Find(TInt aClientId) const;
private:
	CNotifierActivity(const MNotifierBase::TNotifierInfo& aInfo);
	void ConstructL(TInt aClientId);
public:
	const MNotifierBase::TNotifierInfo iInfo;
	CArrayFixFlat<TInt> iClientArray;
	};

class CActivityMonitor : public CBase
	{
public:
	static CActivityMonitor* NewL();
	~CActivityMonitor();
	void AddL(const MNotifierBase::TNotifierInfo& aInfo,TInt aClientId);
	void Remove(TUid aNotifierUid,TInt aClientId);
	void RemoveNotifier(TUid aNotifierUid,TUid aChannel);
	void RemoveClient(TInt aClientId);
	TBool IsNotifierActive(TUid aNotifierUid,TUid aChannel) const;
	TBool IsChannelActive(TUid aChannel,TUid& aNotifier,MNotifierBase::TNotifierPriority& aHighestPriority) const;
	TBool IsClientPresent(TUid aNotifierUid,TUid aChannel,TInt aClientId) const;
	TBool NotifierForClient(TUid& aNotifier,TInt aClientId) const;
private:
	CActivityMonitor();
	TInt Find(TUid aNotifierUid) const;
	TInt Find(TUid aNotifierUid,TUid aChannel) const;
private:
	CArrayPtrFlat<CNotifierActivity> iMonitor;
	};

class CQueueItem : public CBase
	{
public:
	static CQueueItem* NewL(const MNotifierBase::TNotifierInfo& aInfo,const TDesC8& aBuffer,const TAny* aPtr,
										const RMessage& aMessage,TInt aClientId); //Asynchronous
	static CQueueItem* NewL(const MNotifierBase::TNotifierInfo& aInfo,const TDesC8& aBuffer,
										TDes8& aResponse,TInt aClientId); //synchronous
	~CQueueItem();
private:
	CQueueItem(const MNotifierBase::TNotifierInfo& aInfo);
	void ConstructL(const TDesC8& aBuffer,TDes8& aResponse,TInt aClientId);
	void ConstructL(const TDesC8& aBuffer,const RMessage& aMessage,TInt aClientId,const TAny* aPtr);
public:
	const MNotifierBase::TNotifierInfo iInfo;
	HBufC8* iBuffer;
	HBufC8* iResponse;
	TBool iAsynchronous;
	RMessage iMessage;
	TInt iClientId;
	const TAny* iPtr;
	};

class CNotifierQueue : public CBase
	{
public:
	static CNotifierQueue* NewL();
	inline void QueueItemL(CQueueItem* aItem);
	CQueueItem* FetchItem(TUid aChannel);
	TBool IsAlreadyQueued(TUid aNotifier,TUid aChannel) const;
	void RemoveClient(TInt aClientId);
	TInt GetHighestQueuePriority(TUid aChannel);
private:
	inline CNotifierQueue();
private:
	CArrayPtrFlat<CQueueItem> iQueue;
	};

inline TChannelActivity::TChannelActivity(TUid aChannel, TInt aHighestPriorityRunning)
	:iChannel(aChannel),iHighestPriorityRunning(aHighestPriorityRunning)
	{}

inline void CChannelMonitor::AddNewChannelL(TUid aChannel)
	{iMonitor.AppendL(TChannelActivity(aChannel,0));}

inline CNotifierManager* CNotifierServer::Manager() const
	{return iManager;}

inline void CNotifierQueue::QueueItemL(CQueueItem* aItem)
	{iQueue.AppendL(aItem);}
inline CNotifierQueue::CNotifierQueue()
	:iQueue(3)
	{}
/*
//
class CNotifierServer;
class CNotifierSession;
class CNotifierSession : public CSession
	{
public:
	CNotifierSession(RThread aClient,const CNotifierServer& aServer);
	virtual void ServiceL(const RMessage& aMessage);
private:
	static TInt InfoPrintThread(TAny* aMessage);
public:
	static RSemaphore NotifierSemaphore;
private:
	const CNotifierServer* iServer;

	};
class CChannelMonitor;
class CNotifierQueue;

class CNotifierManager: public CBase
	{
public:
	static CNotifierManager* NewL();
	void RegisterL(RFs& aFs);
	TInt StartNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);
	TInt UpdateNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);
	TInt CancelNotifierL(TUid aNotifierUid);
	TInt StartNotifierAndGetResponseL(TUid aNotifierUid,const TDesC8& aBuffer,const TAny* aResponse,RMessage aMessage);
private:
	TInt DoAddPlugInL(TFileName aFileName);
	CNotifierManager();
	void ConstructL();
private:
	CArrayPtr<MNotifierBase>* iObservedList;
	CChannelMonitor* iChannelMonitor;
	CNotifierQueue* iQueue;
	};

class TChannelActivity
	{
public:
	inline TChannelActivity(TUid aChannel, TInt aHighestPriorityRunning):iChannel(aChannel),iHighestPriorityRunning(aHighestPriorityRunning) {};
	TUid iChannel;
	TInt iHighestPriorityRunning;
	};
	
class CChannelMonitor: public CBase
	{
public:
	static CChannelMonitor* NewL();
	inline void AddNewChannelL(TUid aChannel);
	TBool AlreadyHasChannel(TUid aChannel)const;
	TInt ActivityLevel(TUid aChannel) const;
	void UpdateChannel(TUid aChannel,TInt aLevel);
private:
	CChannelMonitor();
	void ConstructL();
private:
	CArrayFixFlat<TChannelActivity> iMonitor;
	};

class CQueueItem: public CBase
	{
	public:
		static CQueueItem* NewL(TUid aUid,const TDesC8& aBuffer,const TAny* aPtr,RMessage aMsg); //Asynchronous
		static CQueueItem* NewL(TUid aUid,const TDesC8& aBuffer, TDes8& aResponse); //synchronous
		CQueueItem& CopyL(const CQueueItem& aItem);
		~CQueueItem();
	
	private:
		inline CQueueItem(){};
		void ConstructL(TUid aUid,const TDesC8& aBuffer,TDes8& aResponse);
		void ConstructL(TUid aUid,const TDesC8& aBuffer,RMessage aMsg,const TAny* aPtr);
	public:
		TUid iUid;
		HBufC8* iBuffer;
		HBufC8* iResponse;
		TBool iAsynchronous;
		RMessage iMessage;
		const TAny* iPtr;
	};
	

class CNotifierQueue: public CBase
	{
public:
	static CNotifierQueue* NewL();
	inline void QueueItemL(CQueueItem* aItem);
	CQueueItem* FetchItem();
private:
	inline CNotifierQueue():iQueue(3){};
	void ConstructL();
private:
	CArrayPtrFlat<CQueueItem> iQueue;
	};

class CNotifierServer : public CServer
	{
public:
	CNotifierServer(TInt aPriority);
	static CNotifierServer* NewL();
	virtual CSharableSession* NewSessionL(const TVersion& aVersion) const;
	inline CNotifierManager* Manager() const;
private:
	void ConstructL();
private:
	CNotifierManager* iManager;
	};

inline void CChannelMonitor::AddNewChannelL(TUid aChannel)
	{
	iMonitor.AppendL(TChannelActivity(aChannel,0));
	}

inline void CNotifierQueue::QueueItemL(CQueueItem* aItem)
	{
	iQueue.AppendL(aItem);
	}
inline CNotifierManager* CNotifierServer::Manager() const
	{
	return iManager;
	}
*/
#endif	// __TWINTNOTIFIER_H__
