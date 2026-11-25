// X509KEYS.H
//
// Copyright (c) 1998-2000 Symbian Ltd.  All rights reserved.
//

#if !defined (__X509KEYS_H__)
#define __X509KEYS_H__

#include <e32base.h>
#include <e32std.h>
#include <cryptalg.h>
#include <bigint.h>

//RSA public key
class CX509RSAPublicKey : public CRSAPublicKey
	{
public:
	IMPORT_C static CX509RSAPublicKey* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509RSAPublicKey* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509RSAPublicKey* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509RSAPublicKey* NewLC(const TDesC8& aBinaryData, TInt& aPos);
private:
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	};

//DSA public key, params, signature
class CX509DSAParameters : public CDSAParameters
	{
public:
	IMPORT_C static CX509DSAParameters* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509DSAParameters* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509DSAParameters* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509DSAParameters* NewLC(const TDesC8& aBinaryData, TInt& aPos);
private:
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	};

class CX509DSAPublicKey : public CDSAPublicKey
	{
public:
	IMPORT_C static CX509DSAPublicKey* NewL(const CDSAParameters& aParams, const TDesC8& aBinaryData);
	IMPORT_C static CX509DSAPublicKey* NewLC(const CDSAParameters& aParams, const TDesC8& aBinaryData);
	IMPORT_C static CX509DSAPublicKey* NewL(const CDSAParameters& aParams, const TDesC8& aBinaryData,TInt& aPos);
	IMPORT_C static CX509DSAPublicKey* NewLC(const CDSAParameters& aParams, const TDesC8& aBinaryData, TInt& aPos);
private:
	void ConstructL(const CDSAParameters& aParams, const TDesC8& aBinaryData, TInt& aPos);
	};
 
class CX509DSASignature : public CDSASignature
	{
public:
	IMPORT_C static CX509DSASignature* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509DSASignature* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509DSASignature* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509DSASignature* NewLC(const TDesC8& aBinaryData, TInt& aPos);
private:
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	};

//DH params
class CX509DHPublicKey : public CBase
	{
public:
	IMPORT_C static CX509DHPublicKey* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509DHPublicKey* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509DHPublicKey* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509DHPublicKey* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C const CInteger& Y() const;
	IMPORT_C ~CX509DHPublicKey();
private:
	CX509DHPublicKey();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	CInteger* iY;
	};

class CX509DHValidationParams : public CBase
	{
public:
	IMPORT_C static CX509DHValidationParams* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509DHValidationParams* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509DHValidationParams* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509DHValidationParams* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C const TPtrC8 Seed() const;
	IMPORT_C const CInteger& PGenCounter() const;
	~CX509DHValidationParams();
protected:
	CX509DHValidationParams();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	HBufC8* iSeed;
	CInteger* iPGenCounter;
	};

class CX509DHDomainParams : public CBase
	{
public:
	IMPORT_C static CX509DHDomainParams* NewL(const TDesC8& aBinaryData);
	IMPORT_C static CX509DHDomainParams* NewLC(const TDesC8& aBinaryData);
	IMPORT_C static CX509DHDomainParams* NewL(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C static CX509DHDomainParams* NewLC(const TDesC8& aBinaryData, TInt& aPos);
	IMPORT_C const CInteger& P() const;	
	IMPORT_C const CInteger& G() const;	
//the next 3 members are optional, in which case NULL is returned
//the returned objects remain the property of this object

//N.B. according to RFC 2459 the Q member is *not* optional, 
//however it is not essential for doing DH, and empirical studies
//suggest it doesn't get included much, so I'm relaxing the spec here
//to permit DomainParams objects which contain no Q.
	IMPORT_C const CInteger* Q() const;	
	IMPORT_C const CInteger* J() const;									
	IMPORT_C const CX509DHValidationParams* ValidationParams() const;
	
	~CX509DHDomainParams();
protected:
	CX509DHDomainParams();
	void ConstructL(const TDesC8& aBinaryData, TInt& aPos);
	CInteger* iP;
	CInteger* iG;
	CInteger* iQ;
	CInteger* iJ;
	CX509DHValidationParams* iValidationParams;
	};

#endif