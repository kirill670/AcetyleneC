// WTLSCERT.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//


#ifndef __WTLSCERT_H__
#define __WTLSCERT_H__

#include <e32base.h>
#include <e32std.h>
#include <s32std.h>
#include <signed.h>
#include <unifiedcertstore.h>
#include <wtlsnames.h>

/*
forward declare classes from cryptalg.h
so we don't have to include the header publicly
*/

class CRSAPublicKey;
class CDSAPublicKey;
class CDSASignature;
class CDSAParameters;

const TInt KWTLSCertMaxDataElements = 6;

class CWTLSRSASignatureResult : public CRSASignatureResult
	{
public:
	IMPORT_C static CWTLSRSASignatureResult* NewL(const CAlgorithmIdentifier& aDigestAlgorithm, const TDesC8& aDigest);
	IMPORT_C static CWTLSRSASignatureResult* NewLC(const CAlgorithmIdentifier& aDigestAlgorithm, const TDesC8& aDigest);
	IMPORT_C virtual TBool VerifyL(const TDesC8& aResult);
private:
	void ConstructL(const CAlgorithmIdentifier& aDigestAlgorithm, const TDesC8& aDigest);
	};

class TWTLSKeyFactory : public TKeyFactory
	{
public:
	virtual CRSAPublicKey* RSAPublicKeyL(const TDesC8& aEncoding) const;
	virtual CRSASignatureResult* RSASignatureResultL(const CAlgorithmIdentifier& aDigestAlgorithm, TDesC8& aDigest) const;
	virtual CDSAPublicKey* DSAPublicKeyL(const CDSAParameters& aParams, const TDesC8& aEncoding) const;
	virtual CDSASignature* DSASignatureL(const TDesC8& aEncoding) const;
	virtual CDSAParameters* DSAParametersL(const TDesC8& aEncoding) const;
	};

//validity period
class CWTLSValidityPeriod : public CValidityPeriod
	{
public:
	IMPORT_C static CWTLSValidityPeriod* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSValidityPeriod* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSValidityPeriod* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CWTLSValidityPeriod* NewLC(const TDesC8& aBinaryData, TInt& aPos);
private:
	CWTLSValidityPeriod();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	};

//algorithm id
class CWTLSAlgorithmIdentifier : public CAlgorithmIdentifier
	{
public:
	IMPORT_C static CWTLSAlgorithmIdentifier* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSAlgorithmIdentifier* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSAlgorithmIdentifier* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CWTLSAlgorithmIdentifier* NewLC(const TDesC8& aBinaryData, TInt& aPos);
private:
	CWTLSAlgorithmIdentifier();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	};

//signing algorithm id
class CWTLSSigningAlgorithmIdentifier : public CSigningAlgorithmIdentifier
	{
public:
	IMPORT_C static CWTLSSigningAlgorithmIdentifier* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSSigningAlgorithmIdentifier* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSSigningAlgorithmIdentifier* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CWTLSSigningAlgorithmIdentifier* NewLC(const TDesC8& aBinaryData, TInt& aPos);
private:
	CWTLSSigningAlgorithmIdentifier();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	};

//wtls subject public key info
class CWTLSSubjectPublicKeyInfo : public CSubjectPublicKeyInfo
	{
public:
	IMPORT_C static CWTLSSubjectPublicKeyInfo* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSSubjectPublicKeyInfo* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSSubjectPublicKeyInfo* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CWTLSSubjectPublicKeyInfo* NewLC(const TDesC8& aBinaryData, TInt& aPos);
private:
	CWTLSSubjectPublicKeyInfo();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	};

_LIT(KWTLSTCAType, " T");
_LIT(KWTLSTCAValue, "ca");

//wtls certificate
class CWTLSCertificate : public CCertificate
	{
public:
	enum	//enum values for encoded data element positions in tbsCert data structure
		{	//these values are to be used as params to DataElementEncoding() function
		EVersionNumber = 0,
		EAlgorithmId = 1,
		EIssuerName = 2,
		EValidityPeriod = 3,
		ESubjectName = 4,
		ESubjectPublicKeyInfo = 5,
		};
	IMPORT_C static CWTLSCertificate* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CWTLSCertificate* NewLC(const TDesC8& aBinaryData);

	IMPORT_C static CWTLSCertificate* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CWTLSCertificate* NewLC(const TDesC8& aBinaryData, TInt& aPos);

	IMPORT_C static CWTLSCertificate* NewL(RReadStream& aStream);
	IMPORT_C static CWTLSCertificate* NewLC(RReadStream& aStream);

//	IMPORT_C static CWTLSCertificate* NewL(CCertStore& aStore, const CCertStoreEntry& aEntry);
//	IMPORT_C static CWTLSCertificate* NewLC(CCertStore& aStore, const CCertStoreEntry& aEntry);

	IMPORT_C static CWTLSCertificate* NewL(const CWTLSCertificate& aCert);
	IMPORT_C static CWTLSCertificate* NewLC(const CWTLSCertificate& aCert);

	IMPORT_C ~CWTLSCertificate();
	IMPORT_C TBool IsEqualL(const CWTLSCertificate& aCert) const;
	//extra accessors
	IMPORT_C TInt Version() const;
	IMPORT_C const CWTLSName& IssuerName() const;
	IMPORT_C const CWTLSName& SubjectName() const;
	IMPORT_C virtual TBool IsSelfSignedL() const;
	IMPORT_C virtual HBufC* SubjectL() const;
	IMPORT_C virtual HBufC* IssuerL() const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C const TPtrC8 SignedDataL() const;
	//return the encoding for a data element at the index specified
	IMPORT_C virtual const TPtrC8* DataElementEncoding(const TUint aIndex) const;
	//returns whether a non selfsigned certificate can be used to sign others
	IMPORT_C TBool IsTCAL() const;
private:
	CWTLSCertificate();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	void ConstructL(const CWTLSCertificate& aCertificate);
	void ConstructCertL(const TDesC8& aBinaryData, TInt& aPos);
	void InitEncodedDataElementsL();
	//private data
	TInt iVersion;
	CWTLSName* iIssuerName;
	CWTLSName* iSubjectName;
	TFixedArray<TPtrC8*, KWTLSCertMaxDataElements>* iDataElements;
	};

#endif---
