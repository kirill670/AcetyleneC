// EIKNFYSV.H
//
// Copyright (c) Symbian Software Ltd 1997-2005.  All rights reserved.
//

/** @file 
@internalComponent */

#ifndef __EIKNFYSV_H__
#define __EIKNFYSV_H__

#include <e32base.h>
#include <w32std.h>
#include <eiknotapi.h>
#include <uikon/eiksvfty.h>

#include <ecom/ecom.h>

//
// class CEikServNotifyServer
//

class CEikSrvNotifierManager;
class CEikServNotifyAlert;
class MEikSrvNotifierBase2;
class CChannelMonitor;
class CActivityMonitor;
class CEikNotifierQueue;
class CQueueItem;
class CEikServNotifySession;
class TNotifierSecureInfo;

class MEikInfoMsgWin;

class TNotifierMessageInfo
/**
@internalComponent 
*/
	{
public:
	TNotifierMessageInfo(const RMessage2& aMessage, CEikServNotifySession& aEikServNotifySession);
private:
	TNotifierMessageInfo();
public:
	RMessage2 iMessage;
	CEikServNotifySession& iEikServNotifySession;
	};

class CEikServNotifyServer : public CPolicyServer
/** 
@internalComponent 
*/
	{
public:
	IMPORT_C ~CEikServNotifyServer();
	IMPORT_C static CEikServNotifyServer* NewL(MEikServNotifyAlert* aAlert);
	IMPORT_C void StartL();
	
public: // from CServer2
	virtual CSession2* NewSessionL(const TVersion &aVersion,const RMessage2& aMessage) const;
public:
	IMPORT_C void DisplayNotifier(const TDesC& aTitle, const TDesC& aLabel, const TDesC& aBut1, const TDesC& aBut2, MEikNotifyAlertCompletionObserver* aObserver);
	IMPORT_C void DisplayInfoPrint(const TDesC& aDes);
	IMPORT_C CEikServNotifyServer(TInt aPriority);
	inline CEikSrvNotifierManager* Manager() const;
	inline RArray<TNotifierMessageInfo>& AsyncMessageQueue() { return iAsyncMessageQueue; }
	inline RArray<TNotifierSecureInfo>& AsyncSecureInfoQueue() { return iAsyncSecureInfoQueue; }
public:
	void SetIsExiting();
	TBool IsExiting() const;
private:
	void ConstructL();
	TCustomResult CustomSecurityCheckL(const RMessage2& aMsg, TInt& aAction, TSecurityInfo& aMissing);
private:
	MEikServNotifyAlert* iAlert;
	MEikInfoMsgWin* iInfoMsg;
	RWindowGroup iInfoMsgGroupWin;
	CEikSrvNotifierManager* iManager;
	TBool iExiting;
	RArray<TNotifierMessageInfo> iAsyncMessageQueue;
	RArray<TNotifierSecureInfo> iAsyncSecureInfoQueue;
	};

//
// class CEikServNotifySession
//
class CEikServNotifySession : public CSession2, public MEikNotifyAlertCompletionObserver
/**
@internalComponent
*/
	{
public:
	static CEikServNotifySession* NewL();
	~CEikServNotifySession();
public: // from CSession
	void HandleAlertCompletion(const TInt aButtonVal);
public: // from CSession2
	virtual void ServiceL(const RMessage2 &aMessage);
private:
	CEikServNotifySession();
	void ConstructL();
	void DisplayAlert(const RMessage2& aMessage);
	void PrepareDisplayAlert();
	void DisplayNextPendingAlert();
	void DisplayInfoMsg(const RMessage2& aMessage);
	void StartNotifierL(const RMessage2& aMessage);
	void UpdateNotifierL(const RMessage2& aMessage);
	void StartNotifierAndGetResponseL(const RMessage2& aMessage,TBool& aCleanupComplete);
	inline CEikServNotifyServer& Server() const {return *STATIC_CAST(CEikServNotifyServer*,CONST_CAST(CServer2*,CSession2::Server()));}
	static HBufC8* GetRemoteInputBufferLC(const RMessage2& aMessage,TInt aSlot);
	void UpdateNotifierAndGetResponseL(const RMessage2& aMessage);
	TInt NotifierCancel(const RMessage2 &aMessage);
private:
	const CEikServNotifyServer* iServer;
	TInt iClientId;
	TInt iLengthOfFirstLineOfMessage;
	TInt iLengthOfSecondLineOfMessage;
	TInt iLengthOfFirstButtonOfMessage;
	TInt iLengthOfSecondButtonOfMessage;
	TInt iLengthOfCombinedBuffer;
	HBufC* iBuffer;
private:
	class CEikSrvPendingAlert : public CActive
		{
	public:
		CEikSrvPendingAlert(CEikServNotifySession& aEikServNotifySession);
		~CEikSrvPendingAlert();
	public:
		void TriggerNext();
	private: // from CActive
		void RunL();
		void DoCancel();

	private:
		CEikServNotifySession& iEikServNotifySession;
		};
private:
	CEikSrvPendingAlert* iEikSrvPendingAlert;
public: friend class CEikSrvPendingAlert;
	};


//
// class CEikSrvNotifierWrapper
//


class CEikSrvNotifierWrapper : public CBase
/**
@internalComponent 
*/
	{
public:
	CEikSrvNotifierWrapper(MEikSrvNotifierBase2* aNotifier);
	~CEikSrvNotifierWrapper();
	void RegisterNotifierL();
public:
	MEikSrvNotifierBase2* iNotifier;
	MEikSrvNotifierBase2::TNotifierInfo iInfo;
	TUid iDestructorKey;
	TUid iPlugInDllUid;
	TBool iIsReadyForRemoval;
	};

//
// class CEikSrvNotifierRemover
//

class CEikSrvNotifierRemover : public CActive
/**
@internalComponent 
*/
	{
public:
	static CEikSrvNotifierRemover* NewL();
	void Start(CEikSrvNotifierManager* aManager, CArrayPtr<CEikSrvNotifierWrapper>* aObservedList);
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
	};

class MNotifierStarter;
class MNotifierUpdater;
class CDiscoverNewImplementation;
class CPluginTrack;
class CEikSrvNotifierManager: public CBase, public MEikSrvNotifierManager
/**
@internalComponent
*/
	{
public:
	static CEikSrvNotifierManager* NewL();
	~CEikSrvNotifierManager();
	void NotifierStartL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8* aResponse,TInt aClientId);
	TInt NotifierUpdateL(TUid aNotifierUid,const TDesC8& aBuffer,TDes8* aResponse,TInt aClientId);
	TInt NotifierCancel(TUid aNotifierUid);
	void NotifierStartAndGetResponseL(TUid aNotifierUid,const TDesC8& aBuffer,TInt aReplySlot,
										const RMessage2& aMessage,TInt aClientId,TBool& aCleanupComplete);
	void HandleClientExit(TInt aClientId);
	void NotifierStartAndGetResponseL(TUid aNotifierUid,TUid aChannelUid,const TDesC8& aBuffer,TInt aReplySlot,
										const RMessage2& aMessage,TInt aClientId,TBool& aCleanupComplete);
	void HandleScreenDeviceChangedL();
	void RegisterSingleNotifierFromTransientPlugInL(TUid aPlugInUid, TUid aNotifierUid);
	void NotifierUpdateAndGetResponseL(TUid aNotifierUid,const TDesC8& aBuffer,TInt aReplySlot,
										const RMessage2& aMessage,TInt aClientId);
////////////////////////////////////////////////////////////////////////////////////////////////////////
	void RegisterL();
	void CheckForEcomPluginInstallUninstall();
////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	TBool NotifierHandlesScreenMode(MEikSrvNotifierBase2* aNotifier);
	CArrayPtr<CEikSrvNotifierWrapper>* TryLoadPlugInL(TUid aPlugInUid);
	TBool TryLoadPlugInFromSpecifiedDriveL(RFs& aFs,TUid aPlugInUid,TInt aDriveIndex,CArrayPtr<CEikSrvNotifierWrapper>*& aNotifierArray);
	CArrayPtr<CEikSrvNotifierWrapper>* LoadPlugInAndPopulateNotifierArrayL(const TDesC& aPath,const TDesC& aFileName,const TUidType& aUidType);
	TInt QueueNotifierForPossibleRemoval(TUid aNotifierUid);
	CArrayPtr<CEikSrvNotifierWrapper>* CreateNotifierArrayFromPlugInArrayL(CArrayPtr<MEikSrvNotifierBase2>* aPlugInArray, const TUidType& aUidType);
	void UpdateHighestPriorityNotifiersOnThisChannelOfTheirPausingOrResuming(TUid aChannelUid, TUid aHighestPriorityNotifierOnThisChannelUid, const TDesC8& aBuffer);
	void TryFindAndRegisterNotifierFromPlugInDllL(TUid aNotifierUid);
	void LookForNotifierInObservedListL(TUid aNotifierUid, TUid aChannelUid, RArray<TInt>& aNotifierPositions);
	void DoNotifierStartL(MNotifierStarter& aNotifierStarter,TBool& aCleanupComplete,TUid aNotifierUid,TUid aChannelUid,const TDesC8& aBuffer,TDes8* aResponse,TInt aClientId);
	TInt DoNotifierUpdateL(MNotifierUpdater& aNotifierStarter,TUid aNotifierUid,const TDesC8& aBuffer,TDes8* aResponse,TInt aClientId);
	
////////////////////////////////////////////////////////////////////////////////////////////////////////
	void DoAddPlugInL(TUid aUid);
	CArrayPtr<CEikSrvNotifierWrapper>* LoadPlugInAndPopulateNotifierArrayL(TUid aUid);
	void UnloadEComPlugInImplementation(TInt aIndex);
	TBool IsImplementationRemoved(TUid aImplementationUid,RImplInfoPtrArray& aPlugInArray);
	TBool IsImplementationAdded(TUid aImplementationUid);
////////////////////////////////////////////////////////////////////////////////////////////////////////

private:
	CArrayPtr<CEikSrvNotifierWrapper>* iObservedList;
	CChannelMonitor* iChannelMonitor;
	CActivityMonitor* iActivityMonitor;
	CEikNotifierQueue* iQueue;
	CEikSrvNotifierRemover* iNotifierRemover;
	CDiscoverNewImplementation* iDiscoverNewImplementation;
	RPointerArray <CPluginTrack> iPluginUidList;
	};


class TChannelActivity
/**
@internalComponent
*/
	{
public:
	inline TChannelActivity(TUid aChannel,TInt aHighestPriorityRunning);
public:
	TUid iChannel;
	TInt iHighestPriorityRunning;
	};
	

class CChannelMonitor: public CBase
/**
@internalComponent 
*/
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
/**
@internalComponent 
*/
	{
public:
	static CNotifierActivity* NewLC(const MEikSrvNotifierBase2::TNotifierInfo& aInfo,TInt aClientId);
	~CNotifierActivity();
	TInt Find(TInt aClientId) const;
private:
	CNotifierActivity(const MEikSrvNotifierBase2::TNotifierInfo& aInfo);
	void ConstructL(TInt aClientId);
public:
	const MEikSrvNotifierBase2::TNotifierInfo iInfo;
	CArrayFixFlat<TInt> iClientArray;
	};


class CActivityMonitor : public CBase
/**
@internalComponent 
*/
	{
public:
	static CActivityMonitor* NewL();
	~CActivityMonitor();
	void AddL(const MEikSrvNotifierBase2::TNotifierInfo& aInfo,TInt aClientId);
	void Remove(TUid aNotifierUid,TInt aClientId);
	void RemoveNotifier(TUid aNotifierUid,TUid aChannel);
	void RemoveClient(TInt aClientId);
	TBool IsNotifierActive(TUid aNotifierUid,TUid aChannel) const;
	TBool IsChannelActive(TUid aChannel,TUid& aNotifier,MEikSrvNotifierBase2::TNotifierPriority& aHighestPriority) const;
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
	static CQueueItem* NewLC(const MEikSrvNotifierBase2::TNotifierInfo& aInfo,TInt aClientId,const TDesC8& aBuffer,const RMessage2& aMessage,TInt aReplySlot);
	virtual ~CQueueItem();
	inline const TDesC8& Buffer() const {return *iBuffer;}
private:
	CQueueItem(const MEikSrvNotifierBase2::TNotifierInfo& aInfo,TInt aClientId,const RMessage2& aMessage,TInt aReplySlot);
	void ConstructL(const TDesC8& aBuffer);
public:
	const MEikSrvNotifierBase2::TNotifierInfo iInfo;
	const TInt iClientId;
	const RMessage2 iMessage;
	TInt iReplySlot;
private:
	HBufC8* iBuffer;
	};
		

class CEikNotifierQueue: public CBase
/**
@internalComponent 
*/
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

class TNotifierSecureInfo
/**
@internalComponent 
*/
	{
public:
	TNotifierSecureInfo(const TUid aNotifierUid, const TSecureId aSecureId);
public:
	TUid iNotifierUid;
	TSecureId iSecureId;
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
