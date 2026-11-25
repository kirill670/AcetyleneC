// Mda\Common\Base.inl
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

// Inline functions for package classes defined in MdaBase.h

inline TPtr8& TMdaRawPackage::Package()
	{ 
	((TMdaRawPackage*)this)->iThis.Set((TUint8*)this,iThis.Length(),iThis.MaxLength()); 
	return iThis; 
	}

inline const TPtr8& TMdaRawPackage::Package() const
	{ 
	((TMdaRawPackage*)this)->iThis.Set((TUint8*)this,iThis.Length(),iThis.MaxLength()); 
	return iThis; 
	}

inline void TMdaRawPackage::SetSize(TInt aDerivedSize)
	{ 
	iThis.Set((TUint8*)this,aDerivedSize,aDerivedSize);
	}

inline void TMdaOpenPackage::SetHandleAddress(TPckgBuf<TInt>* aHandle)
	{
	iHandle = aHandle;
	}

inline TPckgBuf<TInt>* TMdaOpenPackage::GetHandleAddress() const
	{
	return iHandle;
	}

inline TUid TMdaPackage::Type() const
	{ 
	return iType; 
	}

inline TUid TMdaPackage::Uid() const
	{ 
	return iUid;
	}

inline TBool TMdaPackage::operator==(const TMdaPackage& aPackage)
	{
	return ((aPackage.Type()==Type())&&(aPackage.Uid()==Uid()));
	}

inline void TMdaPackage::SetUid(TUid aUid)
	{
	iUid = aUid;
	}

inline TInt TMdaReturnPackage::ReturnSize() const
	{ 
	return iRetSize;
	}

inline void TMdaReturnPackage::SetReturnSize(TInt aReturnSize)
	{
	iRetSize = aReturnSize;
	}

inline TMdaRawPackage::TMdaRawPackage(TInt aDerivedSize)
#pragma warning( disable : 4355 )	// 'this' : used in base member initializer list
: iThis((TUint8*)this,aDerivedSize,aDerivedSize) 
#pragma warning( default : 4355 )
	{ 
	}

inline TMdaPackage::TMdaPackage(TUid aType, TUid aUid, TInt aDerivedSize)
: TMdaRawPackage(aDerivedSize),iType(aType),iUid(aUid)
	{ 
	}

inline TMdaOpenPackage::TMdaOpenPackage(TInt aDerivedSize) :
TMdaRawPackage(aDerivedSize)
	{
	}

inline TMdaReturnPackage::TMdaReturnPackage(TUid aType, TUid aUid, TInt aDerivedSize)
: TMdaPackage(aType,aUid,aDerivedSize)
	{ // Zero the package
	iRetSize = 0;
	}	

