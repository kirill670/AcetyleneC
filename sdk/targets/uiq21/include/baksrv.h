// BAKSRV.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// generic backup server

#if !defined(__BAKSRV_H__)
#define __BAKSRV_H__

#include <e32std.h>
#include <e32base.h>
#include <babackup.h>
#include <badesca.h>
#include "plpbakms.h"

const TInt KBakServMajorVN		=KBakMajorVN;
const TInt KBakServMinorVN		=KBakMinorVN;
const TInt KBakServBuildVN		=KBakBuildVN;
const TInt KBakServMessageSlots	=2;		// no async messages to backup server

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

enum TCompletionType
	{
	ECompleteSync	=0x00,
	ECompleteAsync	=0x01,
	};

class CBaServBackupSession;

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

class CBaServBackupSession : public CSession
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
		RMessagePtr iMessagePtr;
		TLockType iRequest;
		HBufC* iFileName;
		};
public:
	IMPORT_C ~CBaServBackupSession();
	inline CBaBackupServer* BackupServer() const;
public:
	IMPORT_C virtual void HandleError(TInt aError);
protected: // from CSession
	IMPORT_C virtual void ServiceL(const RMessage& aMessage);
	IMPORT_C virtual void CreateL(const CServer& aServer);
protected:
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual TCompletionType CloseAllFilesL(const RMessage& aMessage);
	IMPORT_C virtual void RestartAll();
protected:
	IMPORT_C CBaServBackupSession(RThread aClient);
	inline CArrayFix<TClosedFile>* ClosedFiles() const;
	inline void SetClosedFiles(CArrayFix<TClosedFile>* aClosedFiles);
	inline TInt UniqueClientId() const;
public:
	static CBaServBackupSession* NewL(RThread aClient);
	void SignalReleaseAllFileLocksL(MBackupObserver::TFileLockFlags aFlag);
	void SignalRetakeAllFileLocks();
	void SignalReleaseFileLockL(MBackupObserver::TFileLockFlags aFlag,const TDesC& aFileName);
	void SignalRetakeFileLocks(const TDesC& aFileName);
	void SignalBackupOperation(const TBackupOperationAttributes& aBackupOperationAttributes);
private:
	static void CleanupCloseAllFiles(TAny* aPtr);
	void HandleEventReady(RMessagePtr aPtr);
	void HandleCancelLockChangeNotifierRequest(const RMessage& aMessage);
	void GetEvent(const RMessage& aMessage);
	void RestartFile(const RMessage& aMessage);
	void NotifyLockChangeL(const RMessage& aMessage);
	void NotifyLockChangeCancel(const RMessage& aMessage);
	void GetFileName(const RMessage& aMessage,TDes& aFileName);
	void GetOwnerInfoL(const RMessage &aMessage);
	void BackupOperationEventReady(RMessagePtr aPtr);
	void GetBackupOperationEvent(const RMessage& aMessage);
	void GetBackupOperationState(const RMessage& aMessage);
	void DoRestartAll();
	void NotifyBackupOperationL(const RMessage& aMessage);
	void DoServiceL(const RMessage& aMessage, TCompletionType& aCompleteType);
	void CloseFileL(const RMessage& aMessage);
private:
	TUint32 iUniqueClientId;
	CBaServBackupMessageQueue* iMessageQueue;
	RMessagePtr iMessagePtr;
	CArrayFix<TClosedFile>* iClosedFiles;
	CDesCArray* iFileLockObservers;
	CDesCArray* iReleasedFiles;
	RMessagePtr iBackupOperationMessagePtr;
	TBackupOperationAttributes iBackupOperationAttributes;
	TBool iBackupOperationObserverPresent;
	};


class CShutdownServer;

//
// CBaBackupServer
//

class CBaBackupServer : public CServer
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
	IMPORT_C CSharableSession* NewSessionL(const TVersion &aVersion) const;
private:
	TUint32 iUniqueBusyClientId;
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
	return static_cast<CBaBackupServer*>(const_cast<CServer*>(CSharableSession::Server()));
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
