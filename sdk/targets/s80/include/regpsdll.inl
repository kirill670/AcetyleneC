// regpsdll.inl
//
// Copyright (c) 1999 Symbian Software plc.  All rights reserved.
//

inline TUidType CRegisteredParserDll::UidType() const
/** Gets the parser UID.

@return Parser UID */
	{
	return iUidType;
	}

inline void CRegisteredParserDll::SetUidType(const TUidType& aUidType)
/** Sets the parser UID.

@param aUidType Parser UID */
	{
	iUidType= aUidType;
	}


inline TInt CRegisteredParserDll::DllRefCount() const
/** Gets the parser reference count.

@return Parser reference count */
	{
	return iDllRefCount;
	}
