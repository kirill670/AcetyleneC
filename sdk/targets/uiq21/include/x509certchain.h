// X509CERTCHAIN.H
//
// Copyright (c) 1998-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __X509CERTCHAIN_H__
#define __X509CERTCHAIN_H__

#include <e32std.h>
#include <x509cert.h>
#include <ct.h>

class TValidationStatus
	{
public:
	IMPORT_C TValidationStatus(const TValidationError aError, const TInt aCert);
	TValidationError iReason;
	TInt iCert;
	};

//abstract base class for x509 certificate chain validation; derive from this to suit your profile
class CX509CertChain : public CBase
	{
public:
	IMPORT_C TInt Count() const;
	IMPORT_C const CX509Certificate& Cert(TInt aIndex) const;
	IMPORT_C CArrayPtrFlat<CX509Certificate>* CX509CertChain::DecodeCertsL(const TDesC8& aBinaryData);
	IMPORT_C ~CX509CertChain();

	IMPORT_C TBool IsEqualL(const CX509CertChain& aOther) const;
protected:
	//certificate chain
	CArrayPtrFlat<CX509Certificate>* iChain;
private:
	static void CleanupCertArray(TAny* aArray);
	};

#endif


