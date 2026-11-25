//
// hash.h
//
// 2000 (c) Symbian Ltd

// This header contains the definition of the message digest classes

#ifndef __HASH_H__
#define __HASH_H__

#include <e32base.h>

class CMessageDigest:public CBase
	{
	public:
		IMPORT_C virtual CMessageDigest* ReplicateL(void)=0;		// makes a reinitialised copy of this message digest object
		IMPORT_C virtual TPtrC8 Hash(const TDesC8& aMessage)=0;
		IMPORT_C virtual CMessageDigest* CopyL(void)=0;
		IMPORT_C virtual TInt BlockSize(void)=0;
		IMPORT_C virtual TInt HashSize(void)=0;
		IMPORT_C virtual void Reset(void)=0;
		IMPORT_C ~CMessageDigest(void);
	protected:
		IMPORT_C CMessageDigest(void);
		IMPORT_C CMessageDigest(const CMessageDigest& aMD);
	};

const TInt MD2_BLOCK=16;
const TInt MD2_HASH=16;

class CMD2:public CMessageDigest

	{
	public:
		IMPORT_C static CMD2* NewL(void);
		IMPORT_C CMessageDigest* ReplicateL(void);
		IMPORT_C TPtrC8 Hash(const TDesC8& aMessage);
		IMPORT_C ~CMD2(void);
		IMPORT_C CMessageDigest* CopyL(void);
		IMPORT_C TInt BlockSize(void);
		IMPORT_C TInt HashSize(void);
		IMPORT_C void Reset(void);
	private:
		CMD2(void);
		CMD2(const CMD2& aMD2);
		TBuf8<MD2_HASH> iHash;
		TInt iNum;
		TUint8 iData[MD2_BLOCK];
		TUint iChecksum[MD2_BLOCK];
		TUint iState[MD2_BLOCK];
		void Update(const TUint8* aData,TUint aLength);
		void Final(void);
		void Block(const TUint8* aData);
	};

const TUint MD5_LBLOCK=16;
const TUint MD5_HASH=16;

class CMD5:public CMessageDigest
	{
	public:
		IMPORT_C static CMD5* NewL(void);
		IMPORT_C CMessageDigest* ReplicateL(void);
		IMPORT_C TPtrC8 Hash(const TDesC8& aMessage);
		IMPORT_C ~CMD5(void);
		IMPORT_C CMessageDigest* CopyL(void);
		IMPORT_C TInt BlockSize(void);
		IMPORT_C TInt HashSize(void);
		IMPORT_C void Reset(void);
	private:
		CMD5(void);
		CMD5(const CMD5& aMD5);
		TBuf8<MD5_HASH> iHash;
		TUint iA;
		TUint iB;
		TUint iC;
		TUint iD;
		TUint iNl;
		TUint iNh;
		TUint iData[MD5_LBLOCK];
		TInt iNum;
		void Update(const TUint8* aData,TUint aLength);
		void Final(void);
		void Block(TUint* aData,TInt aNum);
	};

const TUint SHA_LBLOCK=16;
const TUint SHA_HASH=20;

class CSHA:public CMessageDigest
	{
	public:
		IMPORT_C static CSHA* NewL(void);
		IMPORT_C CMessageDigest* ReplicateL(void);
		IMPORT_C TPtrC8 Hash(const TDesC8& aMessage);
		IMPORT_C ~CSHA(void);
		IMPORT_C CMessageDigest* CopyL(void);
		IMPORT_C TInt BlockSize(void);
		IMPORT_C TInt HashSize(void);
		IMPORT_C void Reset(void);
	private:
		TBuf8<20> iHash;
		TUint iH0;
		TUint iH1;
		TUint iH2;
		TUint iH3;
		TUint iH4;
		TUint iNl;
		TUint iNh;
		TUint iData[SHA_LBLOCK];
		TInt iNum;
		void Update(const TUint8* aData,TUint aLength);
		void Final(void);
		void Block(TUint* aData,TInt aNum);
		CSHA(void);
		CSHA(const CSHA& aSHA);
		void ConstructL(void);
		TUint8* iTempData;
	};

class CSHA1:public CMessageDigest
	{
	public:
		IMPORT_C static CSHA1* NewL(void);
		IMPORT_C CMessageDigest* ReplicateL(void);
		IMPORT_C TPtrC8 Hash(const TDesC8& aMessage);
		IMPORT_C ~CSHA1(void);
		IMPORT_C CMessageDigest* CopyL(void);
		IMPORT_C TInt BlockSize(void);
		IMPORT_C TInt HashSize(void);
		IMPORT_C void Reset(void);
	private:
		CSHA1(void);
		CSHA1(const CSHA1& aSHA1);
		TBuf8<20> iHash;
		TUint iH0;
		TUint iH1;
		TUint iH2;
		TUint iH3;
		TUint iH4;
		TUint iNl;
		TUint iNh;
		TUint iData[SHA_LBLOCK];
		TInt iNum;
		void Update(const TUint8* aData,TUint aLength);
		void Final(void);
		void Block(TUint* aData,TInt aNum);
		void ConstructL(void);
		TUint8* iTempData;
	};

class CHMAC:public CMessageDigest

	{
	public:
		IMPORT_C static CHMAC* NewL(const TDesC8& aKey,CMessageDigest* aDigest);
		// This object will assume ownership of the CMessageDigest object given above
		
		IMPORT_C CMessageDigest* ReplicateL(void);
		IMPORT_C TPtrC8 Hash(const TDesC8& aMessage);
		IMPORT_C ~CHMAC(void);
		IMPORT_C CMessageDigest* CopyL(void);
		IMPORT_C TInt BlockSize(void);
		IMPORT_C TInt HashSize(void);
		IMPORT_C void Reset(void);
	private:
		TBuf8<20> iHash;
		HBufC8* iKey;
		CMessageDigest* iInnerDigest;
		CMessageDigest* iOuterDigest;
		TBuf8<64> iInnerPad;
		TBuf8<64> iOuterPad;
		CHMAC(void);
		void ConstructL(const TDesC8& aKey, CMessageDigest* aMessageDigest);
		void ConstructL(const CHMAC& aHMAC);
		void InitL(CMessageDigest* aMessageDigest);
	};

#endif // __HASH_H__
