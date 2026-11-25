// WTLSCERTCHAIN.H
//
// Copyright (c) 1998-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __WTLSCERTCHAIN_H__
#define __WTLSCERTCHAIN_H__

#include <e32std.h>
#include <unifiedcertstore.h>
#include <wtlscert.h>
#include <wtlsnames.h>

class TWTLSValidationStatus
	{
public:
	IMPORT_C TWTLSValidationStatus(const TValidationError aError, const TInt aCert);
	TValidationError iReason;
	TInt iCert;
	};

//this class encapsulates the results of the validation process
//it is returned to client code, which can examine it
//client code takes ownership of it.
class CWTLSValidationResult : public CBase
	{
public:
	IMPORT_C static CWTLSValidationResult* NewLC();
	IMPORT_C static CWTLSValidationResult* NewL();
	IMPORT_C ~CWTLSValidationResult();
	IMPORT_C const TWTLSValidationStatus Error() const;
	IMPORT_C const CArrayFixFlat<TWTLSValidationStatus>& Warnings() const;
	void Reset();
	void SetError(const TValidationError aError, const TInt aCert);
	void AppendWarningL(TWTLSValidationStatus aWarning);

private:
	CWTLSValidationResult();
	void ConstructL();
	TWTLSValidationStatus iError;
	CArrayFixFlat<TWTLSValidationStatus>* iWarnings;
	};

class CWTLSRootCerts;
class CWTLSCertChain : public CBase
	{
	friend class CWTLSCertChainAO;

public:
	IMPORT_C static CWTLSCertChain* NewL(RFs& aFs, const TPtrC8& aEncodedCerts, 
		const TUid aClient);
	IMPORT_C static CWTLSCertChain* NewLC(RFs& aFs, const TPtrC8& aEncodedCerts,
		const TUid aClient);
	IMPORT_C static CWTLSCertChain* NewL(RFs& aFs, const TPtrC8& aEncodedCerts,
		const CArrayPtr<CWTLSCertificate>& aRootCerts);
	IMPORT_C static CWTLSCertChain* NewLC(RFs& aFs, const TPtrC8& aEncodedCerts,
		const CArrayPtr<CWTLSCertificate>& aRootCerts);
	IMPORT_C ~CWTLSCertChain();
	IMPORT_C void ValidateL(CWTLSValidationResult& aValidationResult, 
		const TTime& aValidationTime, TRequestStatus& aStatus);
	IMPORT_C TInt Count() const;
	IMPORT_C const CWTLSCertificate& Cert(TInt aIndex) const;
	IMPORT_C TBool ChainHasRoot() const;
	IMPORT_C void AppendCertsL(const TPtrC8& aEncodedCerts);

private:
	CWTLSCertChain(RFs& aFs);
	void ConstructL(const TPtrC8& aEncodedCerts, const TUid aClient);
	void ConstructL(const TPtrC8& aEncodedCerts, const CArrayPtr<CWTLSCertificate>& aRootCerts);
	void DoConstructL(const TPtrC8& aEncodedCerts);
		
private:
	RFs& iFs;
	CWTLSCertChainAO* iActiveObject;
	CArrayPtrFlat<CWTLSCertificate>* iChain;
	TBool iChainHasRoot;
	};

#endif

