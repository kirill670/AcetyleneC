// PKIXCERTCHAIN.H
//
// Copyright (c) 1998-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __PKIXCERTCHAIN_H__
#define __PKIXCERTCHAIN_H__

#include <e32std.h>
#include <x509certchain.h>
#include <pkixvalidationresult.h>

//implements key validation according to RFC 2459 (PKIX cert/CRL profile), section 6
class CPKIXValidationState;
class CPKIXChainBuilder;
class CPKIXCertChainAO;

/**
 * This class implements a PKIX certificate chain.
 * The chain itself is iChain which is a member of CX509CertChain, the base class of this
 * class.
 */
class CPKIXCertChain : public CX509CertChain
	{
	friend class CPKIXCertChainAO;

public:
		//constructors
	/**
	 * Constructs a certificate chain using the binary data in aEncodedCerts
	 * @param aFs A file server session. It must already be open.
	 * @param aEncodedCerts The certificates encoded as binary data. It is a series
	 * of concatenated certificates. The individual certificates can be retrieved
	 * since each one contains its own length.
	 * @param aClient The uid of the client.
	 */
	IMPORT_C static CPKIXCertChain* NewL(RFs& aFs, const TPtrC8& aEncodedCerts, 
		const TUid aClient);
	IMPORT_C static CPKIXCertChain* NewLC(RFs& aFs, const TPtrC8& aEncodedCerts, 
		const TUid aClient);
	IMPORT_C static CPKIXCertChain* NewL(RFs& aFs, const TPtrC8& aEncodedCerts, 
		const RPointerArray<CX509Certificate>& aRootCerts);
	IMPORT_C static CPKIXCertChain* NewLC(RFs& aFs, const TPtrC8& aEncodedCerts, 
		const RPointerArray<CX509Certificate>& aRootCerts);
		
		//destructor
	IMPORT_C ~CPKIXCertChain();
		//validation

	/**
	 * This function validates the chain.
	 * @param aValidationResult On completion, this contains the result of the validation.
	 * @param aValidationTime The time.
	 * @param aStatus 
	 */
	IMPORT_C void ValidateL(CPKIXValidationResult& aValidationResult, 
		const TTime& aValidationTime, TRequestStatus& aStatus);
	
	/**
	 * This function validates the chain.
	 * @param aValidationResult On completion, this contains the result of the validation.
	 * @param aValidationTime The time.
	 * @param aInitialPolicies The policies we want to be present in the certificate chain.
	 * @param aStatus 
	 */
	IMPORT_C void ValidateL(CPKIXValidationResult& aValidationResult, 
		const TTime& aValidationTime, const CArrayPtr<HBufC>& aInitialPolicies, 
		TRequestStatus& aStatus);

	IMPORT_C void CancelValidate();

	IMPORT_C void AddCertL(const TPtrC8& aEncodedCerts);
	IMPORT_C TBool ChainHasRoot() const;

private:
	CPKIXCertChain();
	/**
	 * Second-phase constructor.
	 * The second phase constructor TODO : description
	 * @param aEncodedCerts TODO : what is it
	 * @param aClient TODO : what is it
	 */
	void ConstructL(RFs& aFs, const TPtrC8& aEncodedCerts, TUid aClient);
	void ConstructL(RFs& aFs, const TPtrC8& aEncodedCerts,
		const RPointerArray<CX509Certificate>& aRootCerts);
	void DoConstructL(const TPtrC8& aEncodedCerts);

	/**
	 * This function adds certificates to the chain but only the ones that are not
	 * self-signed.
	 * @param aEncodedCerts The encoded certificates.
	 */
	void AddIntermediateCertsL(const TPtrC8& aEncodedCerts);

	void RemoveLastCerts(TInt aNumberOfCertsToRemove);
	
private:
	/**
	 * TODO
	 */
	RPointerArray<CX509Certificate> iIntermediateCerts;

	/**
	 * This is ETrue if the chain has a root and EFalse if it hasn't.
	 * The value is only significant after a successfull call to
	 * ValidateL.
	 */
	TBool iChainHasRoot;

	/**
	 * TODO : is this true ?
	 * Used when the user doesn't specify any initial policies
	 */
	CArrayPtrFlat<HBufC>* iPolicies;

	/**
	 * Most of the fucntionality of the class is asynchronous and is in fact
	 * delegated to iActiveObject which will deal with all the asynchronous
	 * functions.
	 */
	CPKIXCertChainAO* iActiveObject;
	};

#endif

