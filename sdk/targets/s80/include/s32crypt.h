// S32CRYPT.H
//
// Copyright (c) 1998-2003 Symbian Ltd.  All rights reserved.
//
#if !defined(__S32CRYPT_H__)
#define __S32CRYPT_H__
#if !defined(__S32BUF_H__)
#include <s32buf.h>
#endif
#if !defined(__S32STOR_H__)
#include <s32stor.h>
#endif

#ifdef SYMBIAN_CRYPTO
class CPBEncryptor;
class CPBDecryptor;
class CPBEncryptionBase;
class CPBEncryptSet;
#endif

const TInt KEncryptionFilterBufSize=160;

/**
 * @publishedAll 
 * @released
 * Base class used in the derivation of TEncryptFilter and TDecryptFilter. 

It has no user accessible functions.

@see TEncryptFilter
@see TDecryptFilter  
*/
class TSecureFilter : public TStreamFilter
	{
protected:
	TSecureFilter();
	void Set(MStreamBuf* aHost,TInt aMode=EWrite);
protected:
	IMPORT_C TInt Capacity(TInt aMaxLength);
	IMPORT_C TInt FilterL(TAny* aPtr,TInt aMaxLength,const TUint8*& aFrom,const TUint8* anEnd);
	IMPORT_C void DoSynchL();
	TInt EmitL(const TDesC8& aDes);
private:
	virtual TInt CryptL(TDes8& aTarget,const TDesC8& aSource) =0;
	virtual void CompleteL(TDes8& aTarget,const TDesC8& aSource) =0;
private:
	TBuf8<KEncryptionFilterBufSize> iIn;
	TPtrC8 iOut;
	TUint8 iBuf[KEncryptionFilterBufSize];
	};

/**
 * @publishedAll 
 * @released
 * An encrypting filter.

An object of this type is used by REncryptStream to encrypt stream data as 
it is written to a target stream.

Encryption itself is performed by an encryption handling object, an instance 
of a class implementing the CSecurityEncryptBase interface.

@see REncryptStream
@see CSecurityEncryptBase
@see CSecurityBase  
*/
class TEncryptFilter : public TSecureFilter
	{
public:
	IMPORT_C TEncryptFilter();
//	Original function, now deprecated
	IMPORT_C void Set(MStreamBuf* aHost,CSecurityEncryptBase* aKey,TInt aMode=EWrite);
#ifdef SYMBIAN_CRYPTO
//	New function, recommended
	IMPORT_C void SetL(MStreamBuf* aHost,CPBEncryptor* aKey,TInt aMode=EWrite);
#endif
protected:
	IMPORT_C void DoRelease();
private:
	IMPORT_C TInt CryptL(TDes8& aTarget,const TDesC8& aSource);
	IMPORT_C void CompleteL(TDes8& aTarget,const TDesC8& aSource);
private:
	CSecurityEncryptBase* iKey;
	};

/**
 * @publishedAll 
 * @released
 * A decrypting filter.

An object of this type is used by RDecryptStream to decrypt stream data as 
it is read from a source stream.

Decryption itself is performed by a decryption handling object, an instance 
of a class implementing the CSecurityDecryptBase interface.

@see RDecryptStream
@see CSecureStore
@see CSecurityDecryptBase  
*/
class TDecryptFilter : public TSecureFilter
	{
public:
	IMPORT_C TDecryptFilter();
//	Original function, now deprecated
	IMPORT_C void Set(MStreamBuf* aHost,CSecurityDecryptBase* aKey,TInt aMode=ERead);
#ifdef SYMBIAN_CRYPTO
//	New function, recommended	
	IMPORT_C void SetL(MStreamBuf* aHost,CPBDecryptor* aKey,TInt aMode=ERead);
#endif
protected:
	IMPORT_C void DoRelease();
private:
	IMPORT_C TInt CryptL(TDes8& aTarget,const TDesC8& aSource);
	IMPORT_C void CompleteL(TDes8& aTarget,const TDesC8& aSource);
private:
	CSecurityDecryptBase* iKey;
	};

/**
 * @publishedAll 
 * @released
 * Supports the decrypting of a stream.

The stream to be decrypted is a stream represented by an existing RReadStream 
object. In effect, RDecryptStream forms a layer over the RReadStream object, 
either using its source stream buffer or taking complete ownership of the 
source stream buffer.

Decryption of streamed data is supported using the TDecryptFilter class derived 
from TStreamFilter. Decryption itself is performed by a decryption handling 
object, an instance of a class implementing the CSecurityDecryptBase interface, 
and which is constructed by a factory function supplied by the security model, 
an implementation of CSecurityBase.

@see TDecryptFilter
@see TStreamFilter
@see CSecurityDecryptBase
@see CSecurityBase  
*/
class RDecryptStream : public RReadStream
	{
public:
	/** Constructs an empty decrypting stream object.
	
	Call OpenL() or OpenLC() to use a source stream owned by an existing read 
	stream interface object, a RReadStream. 
	
	Call AttachL() or AttachLC() to use and take ownership of a source stream 
	owned by an existing read stream interface object. */
	RDecryptStream() {}
public:	//	Original functions, now deprecated
	IMPORT_C void OpenL(RReadStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
	IMPORT_C void OpenLC(RReadStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
	IMPORT_C void AttachL(RReadStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
	IMPORT_C void AttachLC(RReadStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
#ifdef SYMBIAN_CRYPTO
public:	//	New functions, using Password Based Encryption
	IMPORT_C void OpenL(RReadStream& aHost,const CPBEncryptionBase& aKey);
	IMPORT_C void OpenLC(RReadStream& aHost,const CPBEncryptionBase& aKey);
	IMPORT_C void AttachL(RReadStream& aHost,const CPBEncryptionBase& aKey);
	IMPORT_C void AttachLC(RReadStream& aHost,const CPBEncryptionBase& aKey);
#endif
private:
	TDecryptFilter iFilter;
	};

/**
 * @publishedAll 
 * @released
 * Supports the encryption of a stream.

The stream to be encrypted is a stream represented by an existing RWriteStream 
object. In effect, REncryptStream forms a layer over the RWriteStream object, 
either using its target stream buffer or taking complete ownership of the 
target stream buffer.

Encryption of streamed data is supported using the TEncryptFilter class derived 
from TStreamFilter. Encryption itself is performed by an encryption handling 
object, an instance of a class implementing the CSecurityEncryptBase interface, 
and which is constructed by a factory function supplied by the security model, 
an implementation of CSecurityBase.

@see TEncryptFilter
@see TStreamFilter
@see CSecurityEncryptBase
@see CSecurityBase  
*/
class REncryptStream : public RWriteStream
	{
public:
	/** Constructs an empty encrypting stream object.
	
	Call OpenL() or OpenLC() to use a target stream owned by an existing write 
	stream interface object, a RWriteStream. 
	
	Call AttachL() or AttachLC() to use and take ownership of a target stream 
	owned by an existing write stream interface object. */
	REncryptStream() {}
	inline REncryptStream(const MExternalizer<TStreamRef>& anExter);
public:	//	Original functions, now deprecated
	IMPORT_C void OpenL(RWriteStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
	IMPORT_C void OpenLC(RWriteStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
	IMPORT_C void AttachL(RWriteStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
	IMPORT_C void AttachLC(RWriteStream& aHost,const CSecurityBase& aKey,const TDesC8& aInit);
#ifdef SYMBIAN_CRYPTO
public:	//	New functions, using Password Based Encryption
	IMPORT_C void OpenL(RWriteStream& aHost,const CPBEncryptionBase& aKey);
	IMPORT_C void OpenLC(RWriteStream& aHost,const CPBEncryptionBase& aKey);
	IMPORT_C void AttachL(RWriteStream& aHost,const CPBEncryptionBase& aKey);
	IMPORT_C void AttachLC(RWriteStream& aHost,const CPBEncryptionBase& aKey);
#endif
private:
	TEncryptFilter iFilter;
	};
//

#ifdef SYMBIAN_CRYPTO
class TSecureKeyAdapter
/**
Internal API only. Adapter class for use by CSecureStore and RSecureStorePagePool.
@internalComponent
*/
{
public:
	enum TSecureKeyType {EDeprecatedSecurityBase, EPBE};
public:
	TSecureKeyAdapter(const CSecurityBase* aKey);
	TSecureKeyAdapter(const CBoundedSecurityBase* aKey);
	TSecureKeyAdapter(const CPBEncryptSet* aKey);
public:	//	Retrieve key type or key
	inline const CPBEncryptSet* PBEKey() const;
	inline const CSecurityBase* SecurityBaseKey() const;
	inline const CBoundedSecurityBase* SecurityBoundedBaseKey() const;
	inline TSecureKeyType KeyType() const;
private:
	inline void SetPBEKey();				//	Sets bottom bit to indicate PBE
	inline TBool IsPBEKey() const;			//	Checks bottom bit for PBE
private:
	const TAny* iKey;
};

class HEncryptFilter;

class CSecureStore : public CStreamStore
	{
public://	Original functions, now deprecated
	IMPORT_C static CSecureStore* NewL(CStreamStore& aHost,const CSecurityBase& aKey);
	IMPORT_C static CSecureStore* NewLC(CStreamStore& aHost,const CSecurityBase& aKey);
	IMPORT_C CSecureStore(CStreamStore& aHost,const CSecurityBase& aKey);
public://	New functions using PBE
	IMPORT_C static CSecureStore* NewL(CStreamStore& aHost,const CPBEncryptSet& aKey);
	IMPORT_C static CSecureStore* NewLC(CStreamStore& aHost,const CPBEncryptSet& aKey);
	CSecureStore(CStreamStore& aHost,const CPBEncryptSet& aKey);
protected:
	IMPORT_C MStreamBuf* DoReadL(TStreamId anId) const;
	IMPORT_C MStreamBuf* DoCreateL(TStreamId& anId);
	IMPORT_C TStreamId DoExtendL();
	IMPORT_C void DoDeleteL(TStreamId anId);
	IMPORT_C MStreamBuf* DoWriteL(TStreamId anId);
	IMPORT_C MStreamBuf* DoReplaceL(TStreamId anId);
	IMPORT_C void DoCommitL();
	IMPORT_C void DoRevertL();
private:
	inline CStreamStore& Host();
	inline const CStreamStore& Host() const;
	inline const CSecurityBase& SecurityBaseKey() const;
	inline const CPBEncryptSet& PBEKey() const;
	void setEncryptFilterL(HEncryptFilter& aFilter, RStoreWriteStream& aStream, TStreamId anId);	
private:
	CStreamStore* iHost;
	TSecureKeyAdapter iKey;
	};

#else

/**
 * @publishedAll 
 * @released
 * A stream store whose streams are encrypted.

The secure store is layered over another stream store which acts as the host 
for the encrypted streams. This stream store is not owned by the secure store, 
which means that it is possible to to use the secure store to store only a 
portion of the streams in encrypted form.

Access to the streams in this store is via the normal RStoreWriteStream and 
RStoreReadStream classes. Internally, TEncryptFilter and TDecryptFilter objects 
are attached to the streams from the host store in order to do the encryption 
and decryption.

@see RStoreWriteStream
@see RStoreReadStream
@see TEncryptFilter
@see TDecryptFilter  
*/
class CSecureStore : public CStreamStore
	{
public:
	IMPORT_C static CSecureStore* NewL(CStreamStore& aHost,const CSecurityBase& aKey);
	IMPORT_C static CSecureStore* NewLC(CStreamStore& aHost,const CSecurityBase& aKey);
//
	IMPORT_C CSecureStore(CStreamStore& aHost,const CSecurityBase& aKey);
protected:
	IMPORT_C MStreamBuf* DoReadL(TStreamId anId) const;
	IMPORT_C MStreamBuf* DoCreateL(TStreamId& anId);
private:
	inline CStreamStore& Host();
	inline const CStreamStore& Host() const;
	inline const CSecurityBase& Key() const;
private:
	CStreamStore* iHost;
	const CSecurityBase* iKey;
	};

#endif

//

/**
 * @publishedAll 
 * @released
 * Uses an encrypted store to implement the page pool interface MPagePool.

A secure store page pool uses a cache to store pages in-memory and to cache 
frequently accessed pages. You should provide a cache object (CPageCache) 
to the pool for this purpose.

@see CPageCache  
*/
class RSecureStorePagePool : public RStorePagePool
	{
public://	Original functions, now deprecated
	IMPORT_C RSecureStorePagePool(const CBoundedSecurityBase& aKey);
	IMPORT_C RSecureStorePagePool(CPageCache& aCache,const CBoundedSecurityBase& aKey);
#ifdef SYMBIAN_CRYPTO
public://	New functions using PBE
	IMPORT_C RSecureStorePagePool(const CPBEncryptSet& aKey);
	IMPORT_C RSecureStorePagePool(CPageCache& aCache, const CPBEncryptSet& aKey);
#endif
protected:
	IMPORT_C TPageRef ExtendL(const TAny* aPage,TPageReclamation aReclamation);
	IMPORT_C void WriteL(TPageRef aRef,const TAny* aPage,TPageChange aChange);
	IMPORT_C void ReadL(TPageRef aRef,TAny* aPage);
	IMPORT_C void DoDeleteL(TPageRef aRef);
private:
#ifdef SYMBIAN_CRYPTO	
	TSecureKeyAdapter iKey;
#else
	const CBoundedSecurityBase* iKey;
#endif
	};


#include <s32crypt.inl>
#endif
