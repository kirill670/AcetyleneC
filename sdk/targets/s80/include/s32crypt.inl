// S32CRYPT.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Class REncryptStream
inline REncryptStream::REncryptStream(const MExternalizer<TStreamRef>& anExter)
	: RWriteStream(anExter)
	{}

#ifdef SYMBIAN_CRYPTO

// Class TSecureKeyAdapter

//	Sets bottom bit to indicate PBE
inline void TSecureKeyAdapter::SetPBEKey()
	{
	TUint key = (TUint)iKey;
	key|=(0x1);
	iKey = (TAny*)key;
	}

//	Checks bottom bit for indication that the pointer is for a PBE object
inline TBool TSecureKeyAdapter::IsPBEKey() const
	{
	TUint key = (TUint)iKey;
	return (key & 0x1);
	}

//	Unsets bottom bit for PBE before returning pointer
inline const CPBEncryptSet* TSecureKeyAdapter::PBEKey() const
	{
	ASSERT(IsPBEKey());
	TUint key = (TUint)iKey;
	key&=~(0x1);
	return ((const CPBEncryptSet*)(key));
	}

inline const CSecurityBase* TSecureKeyAdapter::SecurityBaseKey() const
	{
	ASSERT(!IsPBEKey());
	return (static_cast<const CSecurityBase*>(iKey));
	}

inline const CBoundedSecurityBase* TSecureKeyAdapter::SecurityBoundedBaseKey() const
	{
	ASSERT(!IsPBEKey());	
	return (static_cast<const CBoundedSecurityBase*>(iKey));
	}

//	Determines and returns key type (old CSecurityBase- or new PBE- derived)
inline TSecureKeyAdapter::TSecureKeyType TSecureKeyAdapter::KeyType() const
	{
	if (IsPBEKey())
		return (EPBE);
	else
		return (EDeprecatedSecurityBase);
	}

#endif