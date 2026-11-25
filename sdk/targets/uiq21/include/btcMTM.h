// BTCMTM.CPP
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined (__BTCMTM_H__)
#define __BTCMTM_H__



#if !defined (__E32BASE_H__)
#include <e32base.h>		// CActive, TFileName)
#endif
#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif
#if !defined (__MSVAPI_H__)
#include <msvapi.h>
#endif
#include <mtclbase.h>

class CMsvEntry;
class CMtmDllRegistry;
class CRichText;
class TMsvEntry;
class CRegisteredMtmDll;
class CMsvSession;



//#include <BTObjUse.h>
#include <IrObUtil.h>

const TInt KBTMaxTextMessageSize = 0xFFFF;
const TInt32 KUidMsgTypeBT			 =	0x10009ED5;
//
// TBTMtmProgress
//
class TBTMtmProgress
	{
public:
	enum TSendState
		{
		EBTMtmUiNullOp,
		EInitialise,
		EConnect,
		EConnectAttemptComplete,
		ESendObject,
		ESendNextObject,
		ESendComplete,
		EDisconnected,
		EUserCancelledDialog,  // User has cancelled the send, the current operation is unimportant
		ESendError
		};
	TSendState iSendState;
	TInt iTotalEntryCount;
	TInt iEntriesDone;
	TInt iCurrentEntrySize; 
	TInt iCurrentBytesTrans;
	TInt iError;
	TInt iTotalReceipients;
	TInt iTotalFailed;
	TFileName iCurrentFile;
	TBuf<128> iCurrentRecipient;	
	TBuf<160> iFailedRecipients;
	};
	

///////  BT Client MTM  /////////////////////////////////////////////////////////////////////////////
class CBTClientMtm : public CBaseMtm
	{
public:
IMPORT_C static CBTClientMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	~CBTClientMtm();

	enum TSyncCmds
		{  // BT mtm SendAs commands for
		ESendasCmdStartExternalise,
		ESendasCmdExternaliseFileName,
		ESendasCmdCommitExternalise,
		};

	enum TAsyncCmds
		{
		EBTcCmdSend
		};

	struct STimeouts
		{
		TInt iConnectTimeout;
		TInt iPutTimeout;
		};

	void SaveMessageL();
	void LoadMessageL();

	void StoreBTMessageL();
	void SetSubjectL(const TDesC& aSubject);
	const TPtrC SubjectL() const;
	TInt32 GetAttachmentSizeL();

	CMsvOperation* ReplyL  (TMsvId aReplyEntryId, TMsvPartList aPartlist, TRequestStatus& aCompletionStatus);
	CMsvOperation* ForwardL(TMsvId aForwardEntryId, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);

	TUint ValidateMessage(TMsvPartList aPartList);
	TMsvPartList Find(const TDesC& aTextToFind, TMsvPartList aPartList);

	// addresssee list (used by objects with no MTM knowledge)
	void AddAddresseeL(const TDesC& aRealAddress);
	void AddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias);
	void RemoveAddressee(TInt aIndex);

	// --- Generic message functions (not already in TMsvEntry) ---
	CDesCArray& AddresseeList();

	// --- RTTI functions ---
	TInt QueryCapability(TUid aCapability, TInt& aResponse);
	void InvokeSyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter);
	CMsvOperation* InvokeAsyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus);

protected:
	CBTClientMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	void ConstructL();
	
	void ContextEntrySwitched(); // called after the context of this instance has been changed to another entry
private:
	CMsvOperationWait* iWait;
	CIrMtmFileNameExternaliser* iBTMtmFileNameExternaliser;

	HBufC* iSubject;

	};



#endif // __BTCMTM_H__
