// EIKNFYSV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKNFYSV_H__)
#define __EIKNFYSV_H__

#include <e32base.h>
#include <w32std.h>
#include <eiknotapi.h>
#include <eiksvfty.h>

//
// class CEikServNotifyServer
//

class CEikSrvNotifierManager;
class CEikServNotifyAlert;
class CEikInfoMsgWin;
class MEikSrvNotifierBase;
class CChannelMonitor;
class CActivityMonitor;
class CEikNotifierQueue;
class CQueueItem;
class CEikServNotifySession;

class TNotifierMessageInfo
	{
public:
	TNotifierMessageInfo(const RMessagePtr& aMessagePtr, const TAny* aMessageParam, CEikServNotifySession* aEikServNotifySession, TAny* aButtonValClientPtr);
private:
	TNotifierMessageInfo();
public:
	RMessagePtr iMessagePtr;
	const TAny* iMessageParam;
	CEikServNotifySession* iEikServNotifySession;
	TAny* iButtonValClientPtr;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CEikServNotifyServer : public CServer
	{
public:
	IMPORT_C ~CEikServNotifyServer();
	static CEikServNotifyServer* NewL(MEikServNotifyAlert* aAlert);
	void StartL();

public: // from CServer
	virtual CSharableSession* NewSessionL(const TVersion &aVersion) const;
public:
	IMPORT_C void DisplayNotifier(const TDesC& aTitle, const TDesC& aLabel, const TDesC& aBut1, const TDesC& aBut2, MEikNotifyAlertCompletionObserver* aObserver);
	IMPORT_C void DisplayInfoPrint(const TDesC& aDes);
	IMPORT_C CEikServNotifyServer(TInt aPriority);
	inline CEikSrvNotifierManager* Manager() const;
	inline RArray<TNotifierMessageInfo>& AsyncMessageQueue() { return iAsyncMessageQueue; }
public:
	void SetIsExiting();
	TBool IsExiting() const;
private:
	void ConstructL();
private:
	MEikServNotifyAlert* iAlert;
	class MEikSrvNotifierBase;
	CEikInfoMsgWin* iInfoMsg;
	RWindowGroup iInfoMsgGroupWin;
	CEikSrvNotifierManager* iManager;
	TBool iExiting;
	RArray<TNotifierMessageInfo> iAsyncMessageQueue;
	};

//
// class CEikServNotifySession
//

class CEikServNotifySession : public CSession, public MEikNotifyAlertCompletionObserver
	{
public:
	CEikServNotifySession(RThread aClient,const CEikServNotifyServer& aServer);
	~CEikServNotifySession();
public: // from CSession
	void HandleAlertCompletion(const TInt aButtonVal);
public: // from CSession
	virtual void ServiceL(const RMessage &aMessage);
private:
	void DisplayAlert(const RMessage& aMessage);
	void PrepareDisplayAlertL(const TAny* aMessageParam, TAny*& aButtonValClientPtr);
	void DisplayNextPendingAlert();
	void DisplayInfoMsg(const RMessage& aMessage);
	void DoStartNotifierL(const RMessage& aMessage);
	void DoUpdateNotifierL(const RMessage& aMessage);
	TInt StartNotifierAndGetResponseL(const RMessage& aMessage,TBool& aCleanupComplete);
	void DoStartNotifierAndGetResponse(const RMessage& aMessage);
private:
	const CEikServNotifyServer* iServer;
	TInt iClientId;
private:
	class CEikSrvPendingAlert : public CActive
		{
	public:
		CEikSrvPendingAlert();
		~CEikSrvPendingAlert();

	public:
		void RequestAndComplete(CEikServNotifySession* aEikServNotifySession);
	private: // from CActive
		void RunL();
		void DoCancel();

	private:
		CEikServNotifySession* iEikServNotifySession;
		};
private:
	CEikSrvPendingAlert* iEikSrvPendingAlert;
public: friend class CEikSrvPendingAlert;
	};


//
// class CEikSrvNotifierWrapper
//

class CEikSrvNotifierWrapper : public CBase
	{
public:
	CEikSrvNotifierWrapper(MEikSrvNotifierBase* aNotifier);
	~CEikSrvNotifierWrapper();
public:
	MEikSrvNotifierBase* iNotifier;
	TUid iPlugInDllUid;
	TBool iIsReadyForRemoval;
	};

//
// class CEikSrvNotifierRemoverTimer
//

class CEikSrvNotifierRemoverTimer : public CTimer
	{
public:
	static CEikSrvNotifierRemoverTimer* NewL(CArrayFix<RLibrary>* aLibraries, TUid aPlugInUid, RPointerArray<CEikSrvNotifierRemoverTimer>* aParentArray);
	~CEikSrvNotifierRemoverTimer();
private:
	CEikSrvNotifierRemoverTimer(CArrayFix<RLibrary>* aLibraries, TUid aPlugInUid, RPointerArray<CEikSrvNotifierRemoverTimer>* aParentArray);
	void ConstructL();
private:
	// from CActive
	void RunL();
public:
	TUid iPlugInUid;
private:
	CArrayFix<RLibrary>* iLibraries;
	RPointerArray<CEikSrvNotifierRemoverTimer>* iParentArray;
	};

//
// class CEikSrvNotifierRemover
//

class CEikSrvNotifierRemover : public CActive
	{
public:
	static CEikSrvNotifierRemover* NewL();
	void Start(CEikSrvNotifierManager* aManager, CArrayPtr<CEikSrvNotifierWrapper>* aObservedList, CArrayFix<RLibrary>* aLibraries);
	~CEikSrvNotifierRemover();
private:
	CEikSrvNotifierRemover();
private:
	// from CActive
	void RunL();
	void DoCancel();
public:
	CEikSrvNotifierManager* iManager;
	CArrayPtr<CEikSrvNotifierWrapper>* iObservedList;
	CArrayFix<RLibrary>* iLibraries;
	};

class CEikSrvNotifierManager: public CBase, public MEikSrvNotifierManager
	{
public:
	static CEikSrvNotifierManager* NewL();
	~CEikSrvNotifierManager();
	void RegisterL(RFs& aFs);
	TInt NotifierStartL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse,TInt aClientId);
	TInt NotifierUpdateL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse,TInt aClientId);
	TInt NotifierCancel(TUid aNotifierUid);
	TInt NotifierStartAndGetResponseL(TUid aNotifierUid,const TDesC8& aBuffer,const TAny* aResponse,
										const RMessage& aMessage,TInt aClientId,TBool& aCleanupComplete);
	void HandleClientExit(TInt aClientId);
	TInt NotifierStartAndGetResponseL(TUid aNotifierUid,TUid aChannelUid,const TDesC8& aBuffer,const TAny* aResponse,
										const RMessage& aMessage,TInt aClientId,TBool& aCleanupComplete);
	void HandleScreenDeviceChangedL();
	void RegisterSingleNotifierFromTransientPlugInL(TUid aPlugInUid, TUid aNotifierUid);
	void UnloadPlugIn(TUid aPlugInUid, TBool aImmediateUnload);
public: // from MEikSrvNotifierManager
	void StartNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);
	void CancelNotifier(TUid aNotifierUid);
	void UpdateNotifierL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8& aResponse);
private:
	void DoAddPlugInL(const TDesC& aPath,const TDesC& aFileName,const TUidType& aUidType);
	void TryAddNotifiersFromNotifierArrayL(CArrayPtr<CEikSrvNotifierWrapper>* aNotifierArray, TInt& aRollBackChannels);
	CEikSrvNotifierManager();
	void ConstructL();
	void StartFromQueueL(CQueueItem* aItem);
	TBool NotfierHandlesScreenMode(MEikSrvNotifierBase* aNotifier);
	CArrayPtr<CEikSrvNotifierWrapper>* TryLoadPlugInL(TUid aPlugInUid);
	void DoTryLoadNotifierL(TUid aNotifierUid, TUid aPlugInUid, CArrayPtr<CEikSrvNotifierWrapper>* aNotifierArray, TInt& aRollBackObservedList, TInt& aRollBackChannels);
	void TryLoadNotifierL(TUid aNotifierUid, TUid aPlugInUid, CArrayPtr<CEikSrvNotifierWrapper>* aNotifierArray);
	TBool TryLoadPlugInFromSpecifiedDriveL(RFs& aFs,TUid aPlugInUid,TInt aDriveIndex,CArrayPtr<CEikSrvNotifierWrapper>*& aNotifierArray);
	CArrayPtr<CEikSrvNotifierWrapper>* LoadPlugInAndPopulateNotifierArrayL(const TDesC& aPath,const TDesC& aFileName,const TUidType& aUidType);
	TInt QueueNotifierForPossibleRemoval(TUid aNotifierUid);
	CArrayPtr<CEikSrvNotifierWrapper>* CreateNotifierArrayFromPlugInArrayL(CArrayPtr<MEikSrvNotifierBase>* aPlugInArray);
	void UpdateHighestPriorityNotifiersOnThisChannelOfTheirPausingOrResuming(TUid aChannelUid, TUid aHighestPriorityNotifierOnThisChannelUid, const TDesC8& aBuffer);
	void TryFindAndRegisterNotifierFromPlugInDllL(TUid aNotifierUid);
	void LookForNotifierInObservedListL(TUid aNotifierUid, TUid aChannelUid, RArray<TInt>& aNotifierPositions);
private:
	CArrayPtr<CEikSrvNotifierWrapper>* iObservedList;
	CArrayFix<RLibrary>* iLibraries;
	CChannelMonitor* iChannelMonitor;
	CActivityMonitor* iActivityMonitor;
	CEikNotifierQueue* iQueue;
	CEikSrvNotifierRemover* iNotifierRemover;
	RPointerArray<CEikSrvNotifierRemoverTimer> iPlugInUnloadTimerArray;
	};

class TChannelActivity
	{
public:
	inline TChannelActivity(TUid aChannel,TInt aHighestPriorityRunning);
public:
	TUid iChannel;
	TInt iHighestPriorityRunning;
	};
	
class CChannelMonitor: public CBase
	{
public:
	static CChannelMonitor* NewL();
	inline void AddNewChannelL(TUid aChannel);
	void DeleteChannel(TInt aIndex);
	TInt NumberOfChannels() const;
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
	static CNotifierActivity* NewLC(const MEikSrvNotifierBase::TNotifierInfo& aInfo,TInt aClientId);
	~CNotifierActivity();
	TInt Find(TInt aClientId) const;
private:
	CNotifierActivity(const MEikSrvNotifierBase::TNotifierInfo& aInfo);
	void ConstructL(TInt aClientId);
public:
	const MEikSrvNotifierBase::TNotifierInfo iInfo;
	CArrayFixFlat<TInt> iClientArray;
	};

class CActivityMonitor : public CBase
	{
public:
	static CActivityMonitor* NewL();
	~CActivityMonitor();
	void AddL(const MEikSrvNotifierBase::TNotifierInfo& aInfo,TInt aClientId);
	void Remove(TUid aNotifierUid,TInt aClientId);
	void RemoveNotifier(TUid aNotifierUid,TUid aChannel);
	void RemoveClient(TInt aClientId);
	TBool IsNotifierActive(TUid aNotifierUid,TUid aChannel) const;
	TBool IsChannelActive(TUid aChannel,TUid& aNotifier,MEikSrvNotifierBase::TNotifierPriority& aHighestPriority) const;
	TBool IsClientPresent(TUid aNotifierUid,TUid aChannel,TInt aClientId) const;
	TBool NotifierForClient(TUid& aNotifier,TInt aClientId) const;
private:
	CActivityMonitor();
	TInt Find(TUid aNotifierUid) const;
	TInt Find(TUid aNotifierUid,TUid aChannel) const;
private:
	CArrayPtrFlat<CNotifierActivity> iMonitor;
	};

class CQueueItem: public CBase
	{
public:
	static CQueueItem* NewL(const MEikSrvNotifierBase::TNotifierInfo& aInfo,const TDesC8& aBuffer,
										const TAny* aPtr,const RMessage& aMessage,TInt aClientId); //Asynchronous
	static CQueueItem* NewL(const MEikSrvNotifierBase::TNotifierInfo& aInfo,const TDesC8& aBuffer,
										TDes8& aResponse,TInt aClientId); //synchronous
	~CQueueItem();
private:
	CQueueItem(const MEikSrvNotifierBase::TNotifierInfo& aInfo);
	void ConstructL(const TDesC8& aBuffer,TDes8& aResponse,TInt aClientId);
	void ConstructL(const TDesC8& aBuffer,const RMessage& aMessage,TInt aClientId,const TAny* aPtr);
public:
	const MEikSrvNotifierBase::TNotifierInfo iInfo;
	HBufC8* iBuffer;
	HBufC8* iResponse;
	TBool iAsynchronous;
	RMessage iMessage;
	TInt iClientId;
	const TAny* iPtr;
	};
	
class CEikNotifierQueue: public CBase
	{
public:
	static CEikNotifierQueue* NewL();
	inline void QueueItemL(CQueueItem* aItem);
	CQueueItem* FetchItem(TUid aChannel);
	TBool IsAlreadyQueued(TUid aNotifier,TUid aChannel) const;
	void RemoveClient(TInt aClientId);
	TInt GetHighestQueuePriority(TUid aChannel);
	inline TInt Count() const;
	const CQueueItem& At(TInt aIndex) const;
	void RemoveNotifier(TUid aNotifierUid);
private:
	inline CEikNotifierQueue();
private:
	CArrayPtrFlat<CQueueItem> iQueue;
	};


inline TChannelActivity::TChannelActivity(TUid aChannel, TInt aHighestPriorityRunning)
	:iChannel(aChannel),iHighestPriorityRunning(aHighestPriorityRunning)
	{}

inline void CChannelMonitor::AddNewChannelL(TUid aChannel)
	{iMonitor.AppendL(TChannelActivity(aChannel,0));}

inline CEikSrvNotifierManager* CEikServNotifyServer::Manager() const
	{return iManager;}

inline void CEikNotifierQueue::QueueItemL(CQueueItem* aItem)
	{iQueue.AppendL(aItem);}
inline TInt CEikNotifierQueue::Count() const
	{return iQueue.Count();}
inline CEikNotifierQueue::CEikNotifierQueue()
	:iQueue(3)
	{}

#endif
