// BAKSRV.H
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//

// generic backup server

#if !defined(__BAKSRV_H__)
#define __BAKSRV_H__

#include <e32std.h>
#include <e32base.h>
#include <babackup.h>
#include <badesca.h>
#include "plpbakms.h"

/**
@internalTechnology
*/
const TInt KBakServMajorVN		=KBakMajorVN;
const TInt KBakServMinorVN		=KBakMinorVN;
const TInt KBakServBuildVN		=KBakBuildVN;
const TInt KBakServMessageSlots	=4;		// no async messages to backup server

/**
@internalTechnology
*/
enum TBaBackupServPanic
	{
	EReqAlreadyOutstanding	=0,
	EReqDoesNotExist		=1,
	EBadFileName			=2,
	ELocksAlreadyReleased	=3,
	EBufferOverflow			=4,
	ENoEventToFetch			=5,
	EHandleNotClosed		=6,
	};

/**
@internalTechnology
*/
enum TCompletionType
	{
	ECompleteSync	=0x00,
	ECompleteAsync	=0x01,
	};

class CBaServBackupSession;

/**
@internalTechnology
*/
class CBaServBackupScheduler : public CActiveScheduler
	{
public:
	inline static CBaServBackupScheduler* Current();
	IMPORT_C void SetErrorHandler(CBaServBackupSession* aErrorHandler);
public: // from CActiveScheduler
	IMPORT_C virtual void Error(TInt aError) const;
private:
	CBaServBackupSession* iErrorHandler;
	};

/**
@internalTechnology
*/
class CBaServBackupMessageQueue : public CBase
	{
public:
	static CBaServBackupMessageQueue* NewL();
	~CBaServBackupMessageQueue();
	void AddItemL(const TDesC& aFileName,MBackupObserver::TFileLockFlags aFlag);
	void AddItem(const TDesC& aFileName);
	TBool IsEmpty() const;
	void GetHead(TDes& aFileName,MBackupObserver::TFileLockFlags& aFlag) const;
	void RemoveHead();
	void RemoveItem(const TDesC& aFileName);
private:
	TInt HeadIndex() const;
private:
	enum TOperation
		{
		ENoOp		=-1,
		ETakeLock	=0,
		};
	class TQueueItem
		{
	public:
		inline TQueueItem(HBufC* aFileName,TInt aOperation);
	public:
		HBufC* iFileName;
		TInt iOperation;
		};
private:
	RArray<TQueueItem> iQueue;
	};
	 
class CBaBackupServer;

/**
@internalTechnology
*/
class CBaServBackupSession : public CSession2

	{
public:
	class TClosedFile
		{
	public:
		inline TBool operator==(const TClosedFile& aClosedFile) const;
	public:
		TFileName iDocName;
		TUid iUid;
		};
	enum TLockType
		{ENull,ERelease,ETake,EPendingReleaseReadOnly,EPendingReleaseNoAccess,EPendingTake};
	class TFileLock
		{
	public:
		RMessagePtr2 iMessagePtr;
		TLockType iRequest;
		HBufC* iFileName;
		};
public:
	IMPORT_C ~CBaServBackupSession();
	inline CBaBackupServer* BackupServer() const;
public:
	IMPORT_C virtual void HandleError(TInt aError);
protected: // from CSession
	IMPORT_C virtual void ServiceL(const RMessage2& aMessage);
	IMPORT_C virtual void CreateL();
protected:
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual TCompletionType CloseAllFilesL(const RMessage2& aMessage);
	IMPORT_C virtual void RestartAll();
protected:
	IMPORT_C CBaServBackupSession();
	inline CArrayFix<TClosedFile>* ClosedFiles() const;
	inline void SetClosedFiles(CArrayFix<TClosedFile>* aClosedFiles);
	inline TInt UniqueClientId() const;
public:
	static CBaServBackupSession* NewL();
	void SignalReleaseAllFileLocksL(MBackupObserver::TFileLockFlags aFlag);
	void SignalRetakeAllFileLocks();
	void SignalReleaseFileLockL(MBackupObserver::TFileLockFlags aFlag,const TDesC& aFileName);
	void SignalRetakeFileLocks(const TDesC& aFileName);
	void SignalBackupOperation(const TBackupOperationAttributes& aBackupOperationAttributes);
private:
	static void CleanupCloseAllFiles(TAny* aPtr);
	void HandleEventReady(RMessagePtr2 aPtr);
	void GetEvent(const RMessage2& aMessage);
	void RestartFile(const RMessage2& aMessage);
	void NotifyLockChangeL(const RMessage2& aMessage);
	void NotifyLockChangeCancel(const RMessage2& aMessage);
	void GetFileName(const RMessage2& aMessage,TDes& aFileName);
	void GetOwnerInfoL(const RMessage2 &aMessage);
	void BackupOperationEventReady(RMessagePtr2 aPtr);
	void GetBackupOperationEvent(const RMessage2& aMessage);
	void GetBackupOperationState(const RMessage2& aMessage);
	void DoRestartAll();
	void NotifyBackupOperationL(const RMessage2& aMessage);
	void DoServiceL(const RMessage2& aMessage, TCompletionType& aCompleteType);
	void CloseFileL(const RMessage2& aMessage);
	void StopNotifications();
private:
	TUint32 iUniqueClientId;
	CBaServBackupMessageQueue* iMessageQueue;
	RMessagePtr2 iNotificationPullMsg;
	CArrayFix<TClosedFile>* iClosedFiles;
	CDesCArray* iFileLockObservers;
	CDesCArray* iReleasedFiles;
	RMessagePtr2 iBackupOperationMessagePtr;
	TBackupOperationAttributes iBackupOperationAttributes;
	TBool iBackupOperationObserverPresent;
	};

class CShutdownServer;

/**
@internalTechnology
*/
class CBaBackupServerExt : public CBase  
	{
public:
	TUint32 iCachedBusyClientId;
	TUint32 iUniqueBusyClientId;
	};

//
// CBaBackupServer
//


/**
@internalTechnology
*/
class CBaBackupServer : public CServer2

	{
public:
	IMPORT_C static CBaBackupServer* NewL();
	IMPORT_C ~CBaBackupServer();
	IMPORT_C void SetBusy(TUint32 aUniqueClientId);
	IMPORT_C TBool IsClientBusy(TUint32 aUniqueClientId) const;
	IMPORT_C void SignalBackupOperation(const TBackupOperationAttributes& aBackupOperationAttributes);
public:
	inline TBool IsBackupOperationRunning() const;
	inline void SetBackupOperationRunning(TBool aBackupOperationRunning);
public:
	IMPORT_C virtual void CloseAllFilesL(MBackupObserver::TFileLockFlags aFlag);
	IMPORT_C virtual void RestartAll();
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual void CompleteClosingFiles(CArrayFix<CBaServBackupSession::TClosedFile>* aClosedFiles);
	IMPORT_C virtual TBool IsOtherClientBusy(TUint32 aUniqueClientId) const;
public:
	void CloseFileL(MBackupObserver::TFileLockFlags aFlag,const TDesC& aFileName);
	void RestartFile(const TDesC& aFileName);
	void AddSession();
	void DropSession();
public: // from CServer
	IMPORT_C TInt RunError(TInt aError);
protected:
	IMPORT_C CBaBackupServer(TInt aPriority);
protected: // from CServer
	IMPORT_C CSession2* NewSessionL(const TVersion &aVersion, const RMessage2& aMessage) const;
private:
	CBaBackupServerExt* iExtension;
	TBool iBackupOperationRunning;
	TInt iSessionCount;
	CShutdownServer* iShutdown;
	};

inline CBaServBackupScheduler* CBaServBackupScheduler::Current()
	{ // static
	return static_cast<CBaServBackupScheduler*>(CActiveScheduler::Current());
	}

inline CBaBackupServer* CBaServBackupSession::BackupServer() const
	{
	return static_cast<CBaBackupServer*>(const_cast<CServer2*>(CSession2::Server()));
	}

inline CArrayFix<CBaServBackupSession::TClosedFile>* CBaServBackupSession::ClosedFiles() const
	{
	return iClosedFiles;
	}

inline void CBaServBackupSession::SetClosedFiles(CArrayFix<TClosedFile>* aClosedFiles)
	{
	if(!iClosedFiles)
		{
		iClosedFiles=aClosedFiles;
		}
	}

inline TInt CBaServBackupSession::UniqueClientId() const
	{
	return iUniqueClientId;
	}

inline TBool CBaServBackupSession::TClosedFile::operator==(const TClosedFile& aClosedFile) const
	{
	return iDocName==aClosedFile.iDocName && iUid==aClosedFile.iUid;
	}

inline TBool CBaBackupServer::IsBackupOperationRunning() const
	{
	return iBackupOperationRunning;
	}

inline void CBaBackupServer::SetBackupOperationRunning(TBool aBackupOperationRunning)
	{
	iBackupOperationRunning = aBackupOperationRunning;
	}

#endif
