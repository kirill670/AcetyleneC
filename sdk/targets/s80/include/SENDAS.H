// SENDAS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//


#if !defined (__SENDAS_H__)
#define __SENDAS_H__

#include <e32base.h>
#include <mtclreg.h>
#include <mtclbase.h>
#include <txtmrtsr.h>

//**********************************
// MSendAsObserver
//**********************************
//
// 
//

class MSendAsObserver
/** Allows CSendAs to call back a client with further information or requests. 

Any client of the Send As functionality needs to implement this class. 
@publishedAll
@released
*/
	{
public:
	/** Checks an MTM capability that returns a response (e.g. maximum message size).
	 
	After calling CSendAs::AddMtmCapabilityL(), the observer is called with the 
	response from the MTM. If the mixin function returns ETrue, then the MTM has 
	satisfied the required capability and will remain in the available MTM array.
	
	@param aCapabilty UID of capability to check 
	@param aResponse Capability information 
	@return ETrue: Capability supported; EFalse: Capability unsupported */
	virtual TBool CapabilityOK(TUid aCapabilty, TInt aResponse)=0;
	IMPORT_C virtual TInt RenderImage(TUid aPrinterUid, const TDesC& aFileName);
	IMPORT_C virtual TInt RenderImage(TUid aPrinterUid, const TDesC& aFileName, TRequestStatus& aRequestStatus);
	IMPORT_C virtual void CancelRendering();
	};

//**********************************
// CSendAsStoreResolver
//**********************************
//
//
//

class CSendAsStoreResolver : public CBase, public MRichTextStoreResolver
/**
@internalComponent
@released
*/
	{
public:
	CSendAsStoreResolver(CStreamStore* aStore);
	~CSendAsStoreResolver();
	//
private:
	const CStreamStore& StreamStoreL(TInt aPos)const;
	//
private:
	CStreamStore* iStore;
	};

//**********************************
// CSendAs
//**********************************
//
// 
//

class CSendAs : public CActive, public MMsvSessionObserver
/** Encapsulates the Send-As functionality provided by the Messaging Architecture.

It allows applications simply to package data into outgoing messages without 
directly using the MTM interfaces. 

The class is failure-safe in that if it gets deleted before the client application 
commits the message, the message is abandoned rather than saved in a potentially 
indeterminate state, which could later cause problems in the Message Server.

If the MTM requires the data to be rendered (i.e. printed), then, when saving 
the message, the CSendAs class calls back to the application using the mixin 
observer, and give the UID of the printer driver to use and the filename the 
printer should produce. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C static CSendAs* NewL(MSendAsObserver& aObserver);
	IMPORT_C ~CSendAs();
	//
	// MTM selection
	inline const CDesCArray& AvailableMtms() const;
	IMPORT_C void AddMtmCapabilityL(TUid aCapabilityId, TBool aResponseExpected=EFalse);
	IMPORT_C void ResetMtmCapabilitiesL();
	IMPORT_C void SetMtmL(TInt aMtmIndex);
	IMPORT_C void SetMtmL(TUid aMtmUid);
	//
	// Service selection
	inline const CDesCArray& AvailableServices() const;
	IMPORT_C void SetService(TInt aServiceIndex);
	//
	// Message creation / deletion
	IMPORT_C void CreateMessageL();
	IMPORT_C void CreateMessageL(TMsvId aId);
	IMPORT_C void SaveMessageL(TBool aMakeVisible=ETrue);
	IMPORT_C void SaveMessageL(TRequestStatus& aCompletionStatus, TBool aMakeVisible=ETrue);
	IMPORT_C void AbandonMessage();
	inline TMsvId MessageId();
	//
	// Message definition
	IMPORT_C const CDesCArray& RecipientList() const;
	IMPORT_C void AddRecipientL(const TDesC& aRealAddress);
	IMPORT_C void AddRecipientL(const TDesC& aRealAddress, const TDesC& aAlias);
	IMPORT_C void RemoveRecipient(TInt aIndex);
	IMPORT_C void SetSubjectL(const TDesC& aSubject);
	IMPORT_C void SetBodyL(const CRichText& aMessageBody);
	IMPORT_C TMsvPartList ValidateMessage();
	IMPORT_C TInt QueryMessageCapability(TUid aCapabilityId, TBool aResponseExpected=EFalse);
	IMPORT_C void SetBioTypeL(TUid aBioTypeUid);
	//
	// Attachment functions
	IMPORT_C void CreateAttachmentL(TMsvId& aAttachmentId, TFileName& aDirectory);
	IMPORT_C void DeleteAttachmentL(TMsvId aAttachmentId);
	IMPORT_C void SetAttachmentL(TMsvId aAttachmentId, const TDesC& aAttachmentName);

	IMPORT_C TInt CountServicesForMtmL(TUid aMtmId);
	IMPORT_C TInt CountServicesForAvailableMtmL(TInt aIndex);
	IMPORT_C TUid AvailableUid(TInt aIndex) const;
	
	//
	// Accessor to underlying messaging components
	inline CClientMtmRegistry& ClientRegistry();
	inline CBaseMtm& ClientMtm();
	//
	// from MMsvSessionObserver
	void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	//
	// from CActive
	void RunL();
	void DoCancel();
	//
protected:
	CSendAs(MSendAsObserver& aObserver);
	void ConstructL();
	//
private:
	void CreateMtmArrayL();
	void DoResetMtmCapabilitiesL();
	//
	void CreateServiceArrayL();
	void DoCreateServiceArrayL();
	TMsvId FindServiceIdL();
	TInt GetDefaultServiceL(TUid aMtm, TMsvId& aService);
	//
	void DoSaveMessageL();
	void SetupRenderingL(TUid& aUid, TFileName& aFileName);
	//
	TBool AttachmentCountL(TMsvId aEntryId);

	CBaseMtm* FindStoredMtm(TUid aMtmId);
	CBaseMtm* AddMtmToStoredListL(TUid aMtmId);

private:
	enum TSendAsState {	EDefault=1,
						EMtmChosen,
						EMessageCreated,
						EMessageSaved,
						EMessageAbandoned,
						EMessageBeingRendered};
private:
	MSendAsObserver& iObserver;
	CMsvSession* iSession;
	CClientMtmRegistry* iClientRegistry;
	CArrayPtrFlat<CBaseMtm>* iMainMtmArray;
	CArrayPtrFlat<CBaseMtm>* iAvailMtmArray;
	CDesCArrayFlat* iMainNameArray;
	CDesCArrayFlat* iAvailNameArray;
	CBaseMtm* iClientMtm;
	CMsvEntry* iEntry;
	CDesCArrayFlat* iServiceNameArray;
	TSendAsState iState;
	TInt iServiceIndex;
	TMsvId iMessageId;
	TRequestStatus* iCompletionStatus;
	TBool iMakeVisible;
	TBool iHasAttachment;
	TUid iBioTypeUid;
	CSendAsStoreResolver* iStoreResolver;
	TMsvEntry iTempEntry;
	CArrayFixFlat<TUid>* iMtmUidArray;
	CArrayFixFlat<TUid>* iAvailUidArray;
	};


#include "sendas.inl"

#endif
