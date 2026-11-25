// IrCMTM.CPP
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined (__IRCMTM_H__)
#define __IRCMTM_H__



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



//#include <IrObjUse.h>
#include <IrObUtil.h>

const TInt KIrMaxTextMessageSize = 0xFFFF;

//
// TIrMtmProgress
//
class TIrMtmProgress
	{
//#pragma message ("SW: Phil - using these instead of TIrMtmOperations defined in CIrSrvMtm.  You may want to change this.")
public:
	enum TSendState
		{
		EIrMtmUiNullOp,
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
	TFileName iFileName;
	};
	

///////  Smtp Client MTM  /////////////////////////////////////////////////////////////////////////////
class CIrClientMtm : public CBaseMtm
	{
public:
IMPORT_C static CIrClientMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	~CIrClientMtm();

	enum TSyncCmds
		{  // Ir mtm SendAs commands for
		ESendasCmdStartExternalise,
		ESendasCmdExternaliseFileName,
		ESendasCmdCommitExternalise,
		};

	enum TAsyncCmds
		{
		EIrcCmdSend
		};

	struct STimeouts
		{
		TInt iConnectTimeout;
		TInt iPutTimeout;
		};

	void SaveMessageL();
	void LoadMessageL();

	void StoreEmailMessageL();
	void GetBodyTextL(/*CImEmailMessage& aMessage,*/ TMsvId aMsvId);
//	void SetAddresseeListL();
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
	CIrClientMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);
	void ConstructL();
	
	void ContextEntrySwitched(); // called after the context of this instance has been changed to another entry
private:
	CMsvOperationWait* iWait;
	CIrMtmFileNameExternaliser* iIrMtmFileNameExternaliser;

	HBufC* iSubject;
	};



#endif // __IRCMTM_H__
