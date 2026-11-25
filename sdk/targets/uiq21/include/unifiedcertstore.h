// UNIFIEDCERTSTORE.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __UNIFIEDCERTSTORE_H__
#define __UNIFIEDCERTSTORE_H__

#include <signed.h>
#include <e32std.h>
#include <ct.h>
#include <mctwritablecertstore.h>

// This class is forward declared to avoid to include its definition in this
// exported header file because it must only be used internally
class CUnifiedCertStoreWorkingVars;

/**
 * This class is used to provide a single point of access to all the certificate stores
 * on the device.
 */
class CUnifiedCertStore : public CActive, public MCertStore
	{
public:
	/** 
	 * Creates a new CUnifiedCertStore
	 * @param aFs A file server session. It must already be open.
	 * @param aOpenForWrite ETrue if the stores must be opened with write access
	 * (e.g. for adding certificates)
	 * and EFalse if the user only needs read-only access.
	 * @return A pointer to an instance of the CUnifiedCertStore class.
	 */
	IMPORT_C static CUnifiedCertStore* NewL(RFs& aFs, TBool aOpenForWrite);
	/** 
	 * Creates a new CUnifiedCertStore and pushes it on the cleanup stack.
	 * @param aFs A file server seesion. It must already be open.
	 * @param aOpenForWrite ETrue if the stores must be opened with write access
	 * (e.g. for adding certificates)
	 * and EFalse if the user only needs read-only access.
	 * @return A pointer to an instance of the CUnifiedCertStore class.
	 */
	IMPORT_C static CUnifiedCertStore* NewLC(RFs& aFs, TBool aOpenForWrite);
	/**
	 * The destructor destroyes all the resources owned by this object.
	 * In particular it releases all the interfaces acquired by the CUnifiedCertStore.
	 */
	IMPORT_C ~CUnifiedCertStore();
	/**
	 * This function initializes the manager. It must be called after the
	 * manager has been constructed and before any call to the manager methods.
	 */
	IMPORT_C void Initialize(TRequestStatus& aStatus);
	IMPORT_C void CancelInitialize();

public:	// identical to MCTCertStore
	IMPORT_C virtual void List(RMPointerArray<CCTCertInfo>& aCertInfos,
		const CCertAttributeFilter& aFilter, TRequestStatus& aStatus);
	IMPORT_C virtual void CancelList();
	IMPORT_C void GetCert(CCTCertInfo*& aCertInfo, const TCTTokenObjectHandle& aHandle, 
		TRequestStatus& aStatus);
	IMPORT_C void CancelGetCert();
	IMPORT_C virtual void Applications(const CCTCertInfo& aCertInfo, 
		RArray<TUid>& aApplications, TRequestStatus &aStatus);
	IMPORT_C virtual void CancelApplications();
	IMPORT_C virtual void IsApplicable(const CCTCertInfo& aCertInfo, TUid aApplication, 
		TBool& aIsApplicable, TRequestStatus& aStatus);
	IMPORT_C virtual void CancelIsApplicable();
	IMPORT_C void Trusted(const CCTCertInfo& aCertInfo, TBool& aTrusted, 
		TRequestStatus& aStatus);
	IMPORT_C virtual void CancelTrusted();
	IMPORT_C virtual void Retrieve(const CCTCertInfo& aCertInfo, TDes8& aEncodedCert,
		TRequestStatus& aStatus);
	IMPORT_C virtual void CancelRetrieve();

public:	// identical to MCTWritableCertStore but without Add functions
	IMPORT_C virtual void Remove(const CCTCertInfo& aCertInfo, TRequestStatus& aStatus);
	IMPORT_C virtual void CancelRemove();
	IMPORT_C virtual void SetApplicability(const CCTCertInfo& aCertInfo, 
		RArray<TUid>* aApplications, TRequestStatus& aStatus);
	IMPORT_C virtual void CancelSetApplicability();
	IMPORT_C virtual void SetTrust(const CCTCertInfo& aCertInfo, TBool aTrusted, 
		TRequestStatus& aStatus);
	IMPORT_C virtual void CancelSetTrust();

public:
	IMPORT_C TInt CertStoreCount() const;
	IMPORT_C MCTCertStore& CertStore(TInt aIndex);
	IMPORT_C TInt WritableCertStoreCount() const;
	IMPORT_C MCTWritableCertStore& WritableCertStore(TInt aIndex);
	IMPORT_C TInt ReadOnlyCertStoreCount() const;
	IMPORT_C MCTCertStore& ReadOnlyCertStore(TInt aIndex);


private:
	CUnifiedCertStore(RFs& aFs, TBool aOpenForWrite);
	void ConstructL();
	void DoCancel();
	void RunL();
	TInt RunError(TInt aError);

	void InitializeL(); // Helper for Initialize
	TBool BeginAsyncOp(TRequestStatus& aStatus);
	void DestroyTemporaryMembers();

private:
	enum TState
		{
		EIdle,

		EInitializeGetTokenList,
		EInitializeGetToken,
		EInitializeGetWritableInterface,
		EInitializeGetReadableInterface,
		EInitializeGetReadableInterfaceFinished,
		EInitializeFinished,

		EList,

		EApplications,
		EApplicationsFinished,

		EIsApplicable,
		EIsApplicableFinished,

		ETrusted,
		ETrustedFinished,

		ERetrieve,
		ERetrieveFinished,

		ERemove,
		ERemoveFinished,

		ESetApplicability,
		ESetApplicabilityFinished,

		ESetTrust,
		ESetTrustFinished
		};

private:
	/**
	 * A file server session, this is not logically a part of this class
	 * but is needed for the client store and the file certstore.
	 */
	RFs& iFs;

	TBool iOpenedForWrite;

	RPointerArray<MCTCertStore> iReadOnlyCertStores;
	RPointerArray<MCTWritableCertStore> iWritableCertStores;
	RPointerArray<MCTCertStore> iCertStores;

	TBool iCurrentlyDoingReadOnly;

	/**
	 * This a TokenType retrieved from the iTokenTypes array.
	 * We use this to get a list of Tokens and to open these Tokens.
	 */
	MCTTokenType* iTokenType;

	/**
	 * This is the list of Tokens for one of the Token Types of iTokenTypes.
	 */
	RCPointerArray<HBufC> iTokens;
	/**
	 * This is used as an index for the iTokens array when we try 
	 * to get an interface to each of the tokens.
	 */
	TInt iIndexTokens;

	/**
	 * A Token interface. We will use the interface to get a readable or writable
	 * certstore interface. The value is updated at EInitializeGetToken and used
	 * at EInitializeGetWritableInterface.
	 */
	MCTToken* iToken;

	/**
	 * We use this to (temporarily) store the interface we obtained from iToken.
	 * It will be inserted in iWritableCertStores or iCertStores.
	 * We also use it for TODO : put list of functions here
	 */
	MCTTokenInterface* iTokenInterface;

	TInt iIndex;	// TODO : we probably can reuse one of the indexes defined previously

	TBool* iTrusted;				// used to store arguments
	TBool iTrusted2;
	TDes8* iEncodedCert;			// used to store arguments
	TUid iApp;

	TState iState;

	TBool iIsInitialized;

	/**
	 * This member holds all the variables that are only used to store temporary results
	 * while performing a given operation. It must be initialized at the start of the
	 * operation and deleted at the end of it whether the opeartion completes successfully
	 * or not. When no operation is being performed it must be 0.
	 */
	CUnifiedCertStoreWorkingVars* iWorkingVars;

	TInt iCertStoreToCancelGetCert;
	};

#endif



