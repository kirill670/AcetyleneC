// impcmtm.h
//
// Copyright (c) 1998-2004 Symbian Software Ltd.  All rights reserved. 
//

// Client MTM for the IMAP4 protocol


#if !defined (__IMPCMTM_H__)
#define __IMPCMTM_H__

#if !defined (__MTCLBASE_H_)
#include <mtclbase.h>
#endif

#if !defined (__MIUTHDR_H_)
#include "miuthdr.h"
#endif

#if !defined (__MIUTPARS_H__)
#include "miutpars.h"		//TImMessageField
#endif

#if !defined (__IMAPSET_H__)
#include "IMAPSET.H"
#endif

#if !defined (__IMAPCMDS_H__)
#include "IMAPCMDS.H"
#endif

#if !defined(__OFFOP_H__)
#include "offop.h"
#endif

#if !defined(__MIUTMSG_H__)
#include "miutmsg.h"
#endif

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__

#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__

// Forward declarations.
class CImap4ClientSessionObserver;
class CImImap4GetMail;
class CImEmailAutoSend;

/////////////////////////////////////////////////////////////////////////////
// Imap4 Client MTM  
class CImap4ClientMtm : public CBaseMtm, public MImUndoOffLineOperation

/** IMAP4 client MTM interface.
Most of the functions in this class are implementations of the virtual functions 
defined by the base class CBaseMtm. 
@publishedAll
@released
*/

	{
public:
   	IMPORT_C static CImap4ClientMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aSession);
	
	~CImap4ClientMtm();
	void HandleEntryEvent(TMsvEntryEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	void StoreL(); // uses a CMsvStore from the Session
	void RestoreL();
	CMsvOperation* ReplyL(TMsvId aDestination, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);
	CMsvOperation* ForwardL(TMsvId aDestination, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);
	TUint ValidateMessage(TUint aPartList);
	TMsvPartList Find(const TDesC& aTextToFind, TMsvPartList aPartList);
	void SaveMessageL(); 
	void LoadMessageL();
	IMPORT_C void StoreSettingsL();	// uses a CMsvStore from the session
	IMPORT_C void RestoreSettingsL();

	// --- RTTI functions ---
	TInt QueryCapability(TUid aCapability, TInt& aResponse);
	void InvokeSyncFunctionL(TInt aFunctionId, const CMsvEntrySelection& aSelection, TDes8& aParameter);
	CMsvOperation* InvokeAsyncFunctionL(TInt aFunctionId, const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus);
	// Addressees have no meaning in the text mtm.
	void AddAddresseeL(const TDesC& aRealAddress);
	void AddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias);
	void RemoveAddressee(TInt aIndex);

	// Attachment functions to support the SendAs API
#ifndef __HIDE_MESSAGING_API_V1__	
	IMPORT_C void CreateAttachmentL(TMsvId& aAttachmentId, TFileName& aDirectory);
	IMPORT_C void DeleteAttachmentL(TMsvId aMessageId, TMsvId aAttachmentId);
#endif	// __HIDE_MESSAGING_API_V1__

#ifdef __MESSAGING_API_V2__
	IMPORT_C virtual void AddAttachmentL(const TDesC& aFilePath, const TDesC8& aMimeType, TRequestStatus& aStatus);
	IMPORT_C virtual void AddAttachmentL(RFile& aFile, const TDesC8& aMimeType, TRequestStatus& aStatus);
	IMPORT_C virtual void AddLinkedAttachmentL(const TDesC& aFilePath, const TDesC8& aMimeType, TRequestStatus& aStatus);
	IMPORT_C virtual void AddEntryAsAttachmentL(TMsvId aAttachmentId, TRequestStatus& aStatus);
	IMPORT_C virtual void CreateAttachmentL(const TDesC& aFileName, RFile& aAttachmentFile, const TDesC8& aMimeType, TRequestStatus& aStatus);
#endif // __MESSAGING_API_V2__
	IMPORT_C void CreateMessageL(TMsvId aServiceId);
	
#ifdef __MESSAGING_API_V2__
	IMPORT_C virtual TMsvId DefaultServiceL() const;
	IMPORT_C virtual void RemoveDefaultServiceL();
	IMPORT_C virtual void ChangeDefaultServiceL(const TMsvId& aService);
#endif	

public: // Returning a list of all the offline operations for a service entry.
    IMPORT_C CImOperationQueueList* QueueListL(CMsvEntry& aServiceEntry);
public:  // Wrapper to settings
    IMPORT_C const CImImap4Settings& Imap4Settings() const;
    IMPORT_C void SetImap4SettingsL(const CImImap4Settings& aSettings);
public: // inherited from MUndoOffLine
    virtual void UndoOffLineChangesL(const CImOffLineOperation& aDeleted, TMsvId aFolderId); 
protected:
	CImap4ClientMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aSession);
	void ConstructL();
	void ContextEntrySwitched(); // called after the context of this instance has been changed to another entry

private:
	TBool ValidateAddress(const TPtrC& anAddress);
	void SendOnNextConnectionL();
	TMsvPartList DoFindL(const TDesC& aTextToFind, TMsvPartList aPartList);
	void FilterAllOrNewMailsL(TInt aFunctionId,const CMsvEntrySelection& aSelection,TDes8& aParameter);
	void FilterMailSelectionL(const CMsvEntrySelection& aSelection,TDes8& aParameter);
	CMsvOperation* CopyMoveOrPopulateL(TInt aFunctionId,TDes8& aParameter,TRequestStatus& aCompletionStatus);
	void ConvertToPartialPopulate(TDes8& aParameter);
	// To check whether a partial fetch or full fetch of message has to be done.
	TBool IsPartialPopulate(TDes8& aParameter);
#if defined(__WINS__) && !defined(EKA2)
	TThreadFunction AutoSendExeL(RLibrary& aLib) const; //places aLib on the cleanup stack
#endif

private:
	CImImap4Settings iImImap4Settings;
	TImMessageField iTImMessageField;
	CImap4ClientSessionObserver* iImap4ClientSessionObserver;
	HBufC* iEmailAddressFormatString;	// defines format of email address used by "Send as" API eg _L("/"%S/" <%S>")
	CImHeader* iHeader;
	CMsvEntrySelection* iMsvEntrySelection;
	CImImap4GetMail*	iImIMAP4GetMail;
	CImEmailOperation*	iImEmailOperation;
	TPckgBuf<TImImap4GetPartialMailInfo>	iImap4GetPartialMailInfo;
	};

class CImImap4GetMail : public CMsvOperation
/** Encapsulates an operation to copy, move, and populate (i.e. download the full 
message body) IMAP4 emails from the remote inbox to any local folder.

Objects of this type are returned from CImap4ClientMtm::InvokeAsyncFunctionL() 
when a suitable get command is requested. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C CMsvOperation* GetMailL(TInt aFunctionId, CImap4ClientMtm& aImap4ClientMtm, const CMsvEntrySelection& aMsvEntrySelection, TDes8& aImap4GetMailInfo, TRequestStatus& aObserverRequestStatus);
	~CImImap4GetMail();
	void DoCancel();
	void RunL();
	const TDesC8& ProgressL();
	const TDesC8& FinalProgress();
private:
	CImImap4GetMail(CMsvSession& aMsvSession, CImap4ClientMtm& aImap4ClientMtm, TRequestStatus& aObserverRequestStatus);
	void ConstructL(TInt aFunctionId, const CMsvEntrySelection& aMsvEntrySelection, TDes8& aImap4GetMailInfo);
	void SelectNextStateL();					// selects next state to go to
	void ChangeStateL();					// initiates the next state operation
	void SelectAndChangeToNextStateL();
	void RequestComplete(TInt aError);
	void Complete();
	void ConnectToMailboxL();
	void CopyMoveNewMessagesL(TBool aCopy);
	void CopyMoveMessageSelectionL(TBool aCopy);
	void CopyMoveAllMessagesL(TBool aCopy);
	void PopulateNewMessagesL();
	void PopulateAllMessagesL();
	void PopulateMessageSelectionL();
	void DisconnectFromMailboxL();
	void ResetProgress();
	void StoreProgressL();
private:
	enum TImImap4GetMailState
		{
		EConnectToMailbox,
		ECopyNewMessages,
		EMoveNewMessages,
		EPopulateNewMessages,
		ECopyMessageSelection,
		EMoveMessageSelection,
		EPopulateMessageSelection,
		ECopyAllMessages,
		EMoveAllMessages,
		EPopulateAllMessages,
		EDisconnectFromMailbox,
		EFinished
		};
	
	CImap4ClientMtm&				iImap4ClientMtm;
	CMsvEntrySelection*				iMsvEntrySelection;
	CMsvOperation*					iMsvOperation;

	TImap4GenericProgress			iProgress;
	TImap4GenericProgress			iErrorProgress;
	TImImap4GetMailState			iState;
	TInt							iCommand;
	TPckgBuf<TImap4GenericProgress>	iProgressBuf;
	TPckgBuf<TImImap4GetPartialMailInfo>	iImap4GetPartialMailInfo;
	};

#endif // __IMPCMTM_H__
