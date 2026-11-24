// X509CERTCHAIN.H
//
// Copyright (c) Symbian Software Ltd 1998-2004.  All rights reserved.
//
/**
 * @file 
 * X509 certificate chain and the validation status implementations
 *
 * @publishedAll
 */
 
#ifndef __X509CERTCHAIN_H__
#define __X509CERTCHAIN_H__

#include <e32std.h>
#include <x509cert.h>
#include <ct.h>

class TValidationStatus
/** The validation status.
* 
* Some errors cannot be blamed on any single certificate, in which case the 
* iCert value is meaningless. The same structure is used for errors and for 
* warnings. 
* 
* @publishedAll
* 
* */
	{
public:
	/** Creates a validation status object.	
	* 
	* @param aError	The error type that occurred when validating the certificate chain.
	* @param aCert	The index number identifying the certificate that gave rise to 
	* 				the error. */
	IMPORT_C TValidationStatus(const TValidationError aError, const TInt aCert);
	
	/** The reason for the error. */
	TValidationError iReason;
	
	/** The index number identifying the certificate that gave rise to the error. */
	TInt iCert;
	};

class CX509CertChain : public CBase
/** Abstract base class for X.509 certificate chain validation; 
* derive from this to suit your profile.
* 
* @publishedAll
* 
* */
	{
public:
	/** Gets the number of certificates in the chain.	
	* 
	* @return	The number of certificates in the chain. */
	IMPORT_C TInt Count() const;
	
	/** Gets the certificate identified by the specified index.
	* Note that Cert(Count()) corresponds to the root (if any)
	* whilst Cert(0) corresponds to the outmost certificate in the chain.
	*
	* @param aIndex	The ordinal number representing the position of the certificate 
	* 				within the chain.
	* @return		The X.509 certificate at the specified index. */
	IMPORT_C const CX509Certificate& Cert(TInt aIndex) const;
	
	/** Decodes the individual elements of the signed data to construct the certificates.
	* 
	* @param aBinaryData	The encoded binary representation.
	* @return				The certificate objects. */
	IMPORT_C CArrayPtrFlat<CX509Certificate>* CX509CertChain::DecodeCertsL(const TDesC8& aBinaryData);
	
	/** Destructor.
	* 
	* Frees all resources owned by the object, prior to its destruction. */
	IMPORT_C ~CX509CertChain();

	/** Tests whether the specified X.509 certificate chain is equal to this X.509 
	* certificate chain.
	* 
	* @param aOther	The X.509 certificate chain to be compared.
	* @return		ETrue, if the certificate chains are equal;EFalse, otherwise. */
	IMPORT_C TBool IsEqualL(const CX509CertChain& aOther) const;
protected:
	//certificate chain
	CArrayPtrFlat<CX509Certificate>* iChain;
private:
	static void CleanupCertArray(TAny* aArray);
	};

#endif


