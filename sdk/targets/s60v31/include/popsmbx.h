// PopsMbx.h
//
// Copyright (c) 1998-2004 Symbian Ltd.  All rights reserved. 
// 

#ifndef __POPSMBX_H__
#define __POPSMBX_H__

#include <badesca.h>
#include <e32base.h>
#include <f32fsys.h>
#include <pop3set.h>
#include <mentact.h>
#include <imsk.h>
#include <msvstd.h>
#include <imcvutil.h>

const TInt KMsgPop3RefreshMailboxPriority = 1;
const TUid KMsgFileRemoteIdIndex ={0x100002F9};

const TInt KImMailMaxIdLength = 200;
const TInt KPop3RefreshUidlEquate=1;

class CImPop3Session;
class CImPop3Operation;
class CImPop3Stat;
class CImPop3List;
class CImPop3UidlMap;
class CImPop3Uidl;
class CImPop3Top;
class CImPop3Capa;
class CImPop3Dele;
class CImPop3Retr;
class TImPop3Parameters;
class CImRecvConvert;
class CImHeader;
class CRichText;
class CRfc822Token;
class CParaFormatLayer;
class CCharFormatLayer;
class CMsvServerEntry;
class RMsvWriteStream;
class CMsvStore;

/**
@internalComponent
@released
*/
class CImPop3RefreshOperation : public CMsgActive
	{
private:
	enum TState {
		EPopRefreshSyncCollection,
		EPopRefreshStat,
		EPopRefreshList,
		EPopRefreshUidl,
		EPopRefreshSyncUidl,
		EPopRefreshGetHeader,
		EPopRefreshDeleteDeadMessages,
		EPopRefreshComplete,
		EPopRefreshDeleteExcessMessages,
		EPopRefreshCapa
		};

	class TMsgUidlStore
		{
	public:
		enum {EInvalid=-1,EPresent=-2};
	public:
		HBufC8*						iPopId;
		TMsvId						iMsvId;
		TUint						iRemoteSize;
	//
		TInt						iSelectionPos;	// transient member
	public:
		void ExternalizeL(RWriteStream& aStream) const;
		};
public:
	static CImPop3RefreshOperation *NewL(CMsvServerEntry&, CImPop3Session&, RFs& );
	~CImPop3RefreshOperation();
	void Start(TRequestStatus& aStatus, CArrayFixFlat<TMsvId>* aMsvIdArray);
	void Start(TRequestStatus& aStatus);  

	TPop3Progress Progress();

	void SetMessagesToKeepL(const CMsvEntrySelection* aMessagesToKeep);
	TUint RemoteMessageSizeL(TMsvId aId);

private:
	CImPop3RefreshOperation(CMsvServerEntry&, CImPop3Session&, RFs& );
	void ConstructL();

	void ChangeStateL(TState aState);			// the state machine engine
	TInt SelectNextState();

	void DoRunL();
	void DoComplete(TInt&);
	void DoCancel();
	
	void AllocateArraysL();
	void GetNoMessagesL();
	void GetMsgSizesL();
	void GetMsgUidlsL();
	void GetCapabilitiesL();

	void DeleteUidl(TInt anIndex);

	void RetrieveHeadersL();

	void GetHeaderByIndexL(TInt);
	void GetMessageByIndexL(TInt);

	void CreateNewHeaderEntryL(TMsvEntry& aNewEntry);
	void GetRemoteMessagesL();
	void QueueRemoteUpdate();	// will be asynch
	void SyncCollectionL();
	void CompleteSyncCollection();
	void SyncUidlL();

	TBool CompareIdAndSizeL();
	TBool GetMessagesIfAny();

	void OpenUidlFileL();
	void CreateUidlFileL();

	void RefreshFinishedL();

	TBool CanDeleteEntry(const TMsvEmailEntry& aEntry) const;

private:
	TState				iState;
	TUint				iNoMessages;
	TUint				iMboxSize;
	TInt32*				iIdTab;
	TUint*				iSize;
	CArrayFixFlat<TMsvId>* iNewMsg;
	TPtrC8				iImMsgId;

	TInt				iRemoteArrayCtr;
	CImPop3UidlMap*		iPop3Uidls;
	CArrayFix<TMsgUidlStore>*	iUidlArray;
	TKeyArrayFix		iUidlKey;

	CMsvServerEntry&	iRemoteServerEntry;
	CMsvServerEntry*	iLocalEntry;
	CMsvEntrySelection*	iMsvSelection;

	CImPop3Session&		iPopSession;
	CImPop3Stat*		iPopStat;
	CImPop3List*		iPopList;
	CImPop3Uidl*		iPopUidl;
	CImPop3Top*			iPopTop;
	CImPop3Retr*		iPopRetr;
	CImPop3Capa*		iPopCapa;

	CImRecvConvert*		iRecvConverter;
	RArray <TInt> iUniqueUidlPosArray;
	RArray <TInt> iTemporaryUidlPosArray;
	TInt 				iPreviousIndex;

	TInt				iMsgCtr;
	RFs&				iFs;

	TMsvId				iRemoteId;

	TPop3Progress		iProgress;
	TMsvEntry			iEntry;

	// flags for existence of UIDL / TOP command
	TBool				iUidlExists;
	TBool				iTopExists;
	TBool				iFirstCallToTop;
	TBool				iEmptyHeaders;
	// array of unwanted entries
	CMsvEntrySelection*	iUnwantedEntries;

	TInt iCheckDiskSpaceCounter;
	TInt iCurrentDrive;

	TInt iLastHeaderToGet;
	TInt iRemoteArraySize;

	CMsvEntrySelection*	iMessagesToKeep;
	
	TBool				iPipeliningSupported;
	};

/**
Changes the modes for CImPop3RefreshOperation depending on 
operation failures,

CImPop3RefreshMailBox was the original name of CImPop3RefreshOperation
This version is written to trap a Leave while downloading equal UIDLs
and re-run CImPop3RefreshOperation skiping UIDL downloading. (BFSW1-2016)

The public section is left to be exactly the same as the original 
CImPop3RefreshOperation structure.

@internalComponent
@released
*/
class CImPop3RefreshMailBox : public CMsgActive
{
private :
		enum TState {
			EPop3RefreshBoxDefault,	
			EPop3RefreshBoxTop,
			EPop3RefreshBoxPurgeInput
			};		
public:
	static CImPop3RefreshMailBox* NewL(CMsvServerEntry&, CImPop3Session&, RFs&);
	~CImPop3RefreshMailBox();
	void Start(TRequestStatus& aStatus, CArrayFixFlat<TMsvId>* aMsgIdArray);

	TPop3Progress Progress();

	void SetMessagesToKeepL(const CMsvEntrySelection* aMessagesToKeep);

	TUint RemoteMessageSizeL(TMsvId aId);
	
private :
	TState	 					iState;
	CImPop3RefreshOperation*	iRefreshOperation;
	CImTextServerSession*		iTextServer;
	CImPop3Session&				iPopSession;
	TImMailBuffer				iTextServerResponse;
	
	TBufC8<3>					iFullStopTerminator;
	CArrayFixFlat <TMsvId>*		iMsvIdArray;
private:
	CImPop3RefreshMailBox(CImPop3Session& aPopSession );

	void ConstructL(CMsvServerEntry&, RFs& );

	void DoRunL();
	void DoCancel();
	void ChangeStateL(TState aState);
};

/**
Defines copy/move from remote mailbox to remote collection

@internalComponent
@released
*/
enum
	{ EPopCpMvRetrieving, EPopCpMvDeleting, EPopCpMvLogging };


class CImPop3Delete;
class CMsvServerEntry;
class CMsvServer;
class CImPop3TransferMessage;

/**
@internalComponent
@released
*/
class CImPop3CopyMove : public  CMsgActive
	{
public:
	static CImPop3CopyMove *NewL(const CMsvEntrySelection&, CMsvServerEntry&, CImPop3Session&, TBool, RFs&, TMsvId, CImLogMessage* aLogMessage, TBool aDisconnectedMode);
	static CImPop3CopyMove *NewL(const CMsvEntrySelection&, CMsvServerEntry&, CImPop3Session&, TBool, RFs&, CImLogMessage* aLogMessage, TBool aDisconnectedMode);
	~CImPop3CopyMove();

	void StartL(TRequestStatus& aStatus);
	TPop3Progress Progress();
	
private:
	CImPop3CopyMove( CMsvServerEntry&, CImPop3Session&, TBool, RFs&, TMsvId, CImLogMessage* aLogMessage, TBool aDisconnectedMode);
	CImPop3CopyMove( CMsvServerEntry&, CImPop3Session&, TBool, RFs&, CImLogMessage* aLogMessage, TBool aDisconnectedMode);
	void ConstructL( const CMsvEntrySelection& );

	void DoTransferL(TMsvEntry& aEntry );
	void DoRetrieveL();
	void RetrievalCompleteL();

	void DoRunL();
	void DoComplete(TInt& aCompleteStatus);
	void DoCancel();

	void RunLProcessingL();
	void LogFetchedMessageL();
	void LeaveIfLowDiskL(const CMsvEntrySelection& aMsgSelection);
private:

	CMsvEntrySelection*			iSource;
	CMsvServerEntry&			iDestination;
	
	CImPop3Session&				iPopSession;
	CImPop3Delete*				iDelete;
	CImPop3Retr*				iRetrieve;

	TBool						iCopy;
	RFs							iFs;
	TPop3Progress				iProgress;
	// CRecv things
	CImRecvConvert*				iRecvConverter;
	// message body stuff
	CRichText*					iBody;
	CParaFormatLayer*			iParaLayer;
	CCharFormatLayer*			iCharLayer;
	CImPop3TransferMessage*		iTransfer;

	TInt						iMsgCtr;
	TInt						iPopCopyMoveState;
	TBool						iRetrieveMessage;
	TBool						iProcessComplete;
	TMsvId						iServiceId;
	TMsvId						iDestId;
	TMsvEntry					iEntry;
	TBool						iPopulate;
	CImLogMessage*				iLogMessage;
	TInt						iSavedError;
	TBool						iDoingTransfer;
	TBool						iDisconnectedMode;
	TBool						iAlreadyComplete;
	TBool						iMessageMarkedForDelete;
	};

/**
@internalComponent
@released
*/

class CImPop3TopPopulate : public  CMsgActive
	{
public:
	static CImPop3TopPopulate *NewL(const CMsvEntrySelection&, CMsvServerEntry&, TInt aLimit, CImPop3Session&, RFs&, CImLogMessage* aLogMessage, TBool aDisconnectedMode, RArray<TUint>& aRemoteSizes);
	~CImPop3TopPopulate();

	void StartL(TRequestStatus& aStatus);
	TPop3Progress Progress();
	
private:

	CImPop3TopPopulate( CMsvServerEntry&, TInt aLimit, CImPop3Session&, RFs&, CImLogMessage* aLogMessage, TBool aDisconnectedMode, RArray<TUint>& aRemoteSizes);
	void ConstructL( const CMsvEntrySelection& );

	void DoTransferL(TMsvEntry& aEntry );
	void DoRetrieveL();
	void RetrievalCompleteL();

	void DoRunL();
	void DoComplete(TInt& aCompleteStatus);
	void DoCancel();

	void RunLProcessingL();
	void LogFetchedMessageL();



	enum 
		{
		EPopTopPopRetrieving, 
		EPopTopPopDeleting,
		EPopTopPopLogging
		};	
private:
	CMsvEntrySelection*			iSource;
	CMsvServerEntry&			iDestination;
	CImPop3Session&				iPopSession;
	CImPop3Top*					iTop;

	CRichText*					iBody;
	CParaFormatLayer*			iParaLayer;
	CCharFormatLayer*			iCharLayer;

	TBool						iCopy;
	RFs							iFs;
	TPop3Progress				iProgress;
	// CRecv things
	CImRecvConvert*				iRecvConverter;
	CImLogMessage*				iLogMessage;
	TBool						iDisconnectedMode;
	TMsvId						iServiceId;
	TInt						iPopTopPopState;
	TBool						iProcessComplete;
	TBool						iAlreadyComplete;
	TBool						iMessageMarkedForDelete;
	TBool						iRetrieveMessage;
	TInt						iMsgCtr;
	TMsvId						iDestId;
	TInt						iSavedError;
	TInt						iTopLimit;
	TInt						iCurrentMsgSize;
	RArray<TUint>				iRemoteSizes;
	};


/**
Pop3 delete from mailbox

@internalComponent
@released
*/
class CImPop3Delete : public  CMsgActive
	{
public:
	static CImPop3Delete *NewL(CMsvServerEntry&, const CMsvEntrySelection&, CImPop3Session&);
	~CImPop3Delete();

	void Start(TRequestStatus& aStatus);
	TPop3Progress Progress();
	
private:
	CImPop3Delete(CMsvServerEntry&, CImPop3Session&);
	void ConstructL(const CMsvEntrySelection&);

	void DoDelete();

	void DoRunL();
	void DoCancel();

private:
	CMsvEntrySelection*				iSource;
	CMsvServerEntry&				iRemoteEntry;
	CImPop3Session&					iPopSession;
	CImPop3Dele*					iPopDelete;

	TPop3Progress					iProgress;
	TInt							iMsgCtr;
	};

#endif
