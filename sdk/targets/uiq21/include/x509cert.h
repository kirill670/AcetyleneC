// X509CERT.H
//
// Copyright (c) 1998-2000 Symbian Ltd.  All rights reserved.
//

#if !defined (__X509CERT_H__)
#define __X509CERT_H__

#include <e32base.h>
#include <e32std.h>
#include <s32std.h>
#include <signed.h>
#include <x500dn.h>

_LIT(KMD2WithRSA,"1.2.840.113549.1.1.2");
_LIT(KMD5WithRSA,"1.2.840.113549.1.1.4");
_LIT(KSHA1WithRSA,"1.2.840.113549.1.1.5");
_LIT(KDSAWithSHA1,"1.2.840.10040.4.3");

_LIT(KRSA,"1.2.840.113549.1.1.1");
_LIT(KDH,"1.2.840.10046.2.1");
_LIT(KDSA,"1.2.840.10040.4.1");
_LIT(KMD5,"1.2.840.113549.2.5");
_LIT(KMD2,"1.2.840.113549.2.2");
_LIT(KSHA1,"1.3.14.3.2.26");

const TInt KX509MaxDataElements = 10;

/*
forward declare classes from cryptalg.h
so we don't have to include the header publicly
*/
class CRSAPublicKey;
class CDSAPublicKey;
class CDSASignature;
class CDSAParameters;

class CPKCS1SignatureResult : public CRSASignatureResult
	{
public:
	IMPORT_C static CPKCS1SignatureResult* NewL(const CAlgorithmIdentifier& aDigestAlgorithm, const TDesC8& aDigest);
	IMPORT_C static CPKCS1SignatureResult* NewLC(const CAlgorithmIdentifier& aDigestAlgorithm, const TDesC8& aDigest);
	IMPORT_C virtual TBool VerifyL(const TDesC8& aResult);
private:
	void ConstructL(const CAlgorithmIdentifier& aDigestAlgorithm, const TDesC8& aDigest);
	TBool DoVerifyL(const TDesC8& aResult);
	};

class TX509KeyFactory : public TKeyFactory
	{
public:
	IMPORT_C CRSAPublicKey* RSAPublicKeyL(const TDesC8& aEncoding) const;
	IMPORT_C CRSASignatureResult* RSASignatureResultL(const CAlgorithmIdentifier& aDigestAlgorithm, TDesC8& aDigest) const;
	IMPORT_C CDSAPublicKey* DSAPublicKeyL(const CDSAParameters& aParams, const TDesC8& aEncoding) const;
	IMPORT_C CDSASignature* DSASignatureL(const TDesC8& aEncoding) const;
	IMPORT_C CDSAParameters* DSAParametersL(const TDesC8& aEncoding) const;
	};

//validity period
class CX509ValidityPeriod : public CValidityPeriod
	{
public:
	IMPORT_C static CX509ValidityPeriod* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509ValidityPeriod* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509ValidityPeriod* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509ValidityPeriod* NewLC(const TDesC8& aBinaryData, TInt& aPos);
private:
	CX509ValidityPeriod();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	};

//algorithm id
class CX509AlgorithmIdentifier : public CAlgorithmIdentifier
	{
public:
	IMPORT_C static CX509AlgorithmIdentifier* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509AlgorithmIdentifier* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509AlgorithmIdentifier* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509AlgorithmIdentifier* NewLC(const TDesC8& aBinaryData, TInt& aPos);
private:
	CX509AlgorithmIdentifier();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	};

//signing algorithm id
class CX509SigningAlgorithmIdentifier : public CSigningAlgorithmIdentifier
	{
public:
	IMPORT_C static CX509SigningAlgorithmIdentifier* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509SigningAlgorithmIdentifier* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509SigningAlgorithmIdentifier* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509SigningAlgorithmIdentifier* NewLC(const TDesC8& aBinaryData, TInt& aPos);
private:
	CX509SigningAlgorithmIdentifier();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	};

//x509 subject public key info
class CX509SubjectPublicKeyInfo : public CSubjectPublicKeyInfo
	{
public:
	IMPORT_C static CX509SubjectPublicKeyInfo* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509SubjectPublicKeyInfo* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509SubjectPublicKeyInfo* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509SubjectPublicKeyInfo* NewLC(const TDesC8& aBinaryData, TInt& aPos);
private:
	CX509SubjectPublicKeyInfo();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	};

//generic extension type
class CX509CertExtension : public CBase
	{
public:
	IMPORT_C static CX509CertExtension* NewL(const CX509CertExtension& aExtension);
	IMPORT_C static CX509CertExtension* NewLC(const CX509CertExtension& aExtension);
	IMPORT_C static CX509CertExtension* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509CertExtension* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509CertExtension* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509CertExtension* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C ~CX509CertExtension();
	IMPORT_C TBool Critical() const;
	IMPORT_C TPtrC Id() const;	//OID for the extension
	IMPORT_C TPtrC8 Data() const;	//the extension itself 
private:
	CX509CertExtension();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	void ConstructL(const CX509CertExtension& aExtension);
	HBufC* iId;
	TBool iCritical;
	HBufC8* iData;
	};

class CX509Certificate : public CCertificate
	{
public:
	enum	//enum values for encoded data element positions in tbsCert data structure
		{	//these values are to be used as params to DataElementEncoding() function
		EVersionNumber = 0,	//optional - may be NULL
		ESerialNumber = 1,
		EAlgorithmId = 2,
		EIssuerName = 3,
		EValidityPeriod = 4,
		ESubjectName = 5,
		ESubjectPublicKeyInfo = 6,
		EIssuerUID = 7,		//optional - may be NULL
		ESubjectUID = 8,	//optional - may be NULL
		EExtensionList = 9	//optional - may be NULL
		};
	IMPORT_C static CX509Certificate* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509Certificate* NewLC(const TDesC8& aBinaryData);

	IMPORT_C static CX509Certificate* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509Certificate* NewLC(const TDesC8& aBinaryData, TInt& aPos);

	IMPORT_C static CX509Certificate* NewL(RReadStream& aStream);
	IMPORT_C static CX509Certificate* NewLC(RReadStream& aStream);

	IMPORT_C static CX509Certificate* NewL(const CX509Certificate& aCert);
	IMPORT_C static CX509Certificate* NewLC(const CX509Certificate& aCert);

	IMPORT_C ~CX509Certificate();
	IMPORT_C TBool IsEqualL(const CX509Certificate& aCert) const;
	//extra accessors
	IMPORT_C const TPtrC8 SignedDataL() const;
	IMPORT_C TInt Version() const;
	IMPORT_C const CX500DistinguishedName& IssuerName() const;
	IMPORT_C const CX500DistinguishedName& SubjectName() const;
			//return all your generic extensions
	IMPORT_C const CArrayPtrFlat<CX509CertExtension>& Extensions() const;
		//return a particular extension: this is NOT OWNED by the client
		//returns NULL if the ext is not found
	IMPORT_C const CX509CertExtension* Extension(const TDesC& aExtensionName) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
		//return the encoding for a data element at the index specified
	IMPORT_C virtual const TPtrC8* DataElementEncoding(const TUint aIndex) const;

public:	// from CCertificate
	IMPORT_C HBufC* IssuerL() const;
	IMPORT_C HBufC* SubjectL() const;
	IMPORT_C TBool IsSelfSignedL() const;
	IMPORT_C TKeyIdentifier KeyIdentifierL() const;

private:
	CX509Certificate();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	void ConstructL(const CX509Certificate& aCertificate);
	void ConstructCertL();
	void InitDataElementsL(const CX509Certificate& aCertificate);
	HBufC8* DecodeUidL(const TDesC8& aBinaryData, TBool& aHasElementAlready);
	void DecodeExtsL(const TDesC8& aBinaryData, TBool& aHasElementAlready);
	//private data
	TInt iVersion;
	CX500DistinguishedName* iIssuerName;
	CX500DistinguishedName* iSubjectName;
	HBufC8* iIssuerUid;
	HBufC8* iSubjectUid;
	CArrayPtrFlat<CX509CertExtension>* iExtensions;
	TFixedArray<TPtrC8*, KX509MaxDataElements>* iDataElements;
	};

#endif
