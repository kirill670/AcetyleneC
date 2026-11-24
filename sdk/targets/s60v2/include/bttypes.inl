// BTTypes.inl
//
// Copyright (c) 1999-2000 Symbian Ltd.  All rights reserved.
//

//
// BT protocol wide types
//

/**
Comparison operator.
@param aAddr The device address to compare to this object.
@return ETrue if the addresses are equal, EFalse if not.
*/
inline TBool TBTDevAddr::operator==(const TBTDevAddr& aAddr) const
	{
	return Mem::Compare(&iAddr[0],KBTDevAddrSize,&aAddr.iAddr[0],KBTDevAddrSize) == 0;
	}

/**
Inequality operator.
@param aAddr The device address to compare to this object.
@return EFalse if the addresses are equal, ETrue if not.
*/
inline TBool TBTDevAddr::operator!=(const TBTDevAddr& aAddr) const
	{
	return !(*this==aAddr);
	}

/**
Access a single element of the address.
@param aIndex The index of the element to access.
@return The element.  The reference remains valid as long as this object is in scope.
*/
inline const TUint8 &TBTDevAddr::operator[](TInt aIndex) const
	{
	return iAddr[aIndex];
	}

/**
Access a single element of the address.
@param aIndex The index of the element to access.
@return The element.  The reference remains valid as long as this object is in scope.
*/
inline TUint8 &TBTDevAddr::operator[](TInt aIndex)
	{
	return iAddr[aIndex];
	}

/**
Reset the data contained within the object.
*/
inline void TBTDevAddr::Reset()
	{
	iAddr.Reset();
	}

/**
Access value as a bigendian descriptor.
@return A non-const descriptor.
*/
inline TPtr8 TBTDevAddr::Des()
	{
	return TPtr8(&iAddr[0], KBTDevAddrSize, KBTDevAddrSize);
	}

/**
Access value as a bigendian descriptor.
@return A const descriptor.
*/
inline const TPtrC8 TBTDevAddr::Des() const
	{
	return TPtrC8(&iAddr[0], KBTDevAddrSize);
	}


/** 
Extract the Bluetooth device address into a human-readable format, in aDest.

Output is in hexadecimal bigendian format, with no padding characters.

Note: aDest must be large enough to hold the entire output, or else a
a panic will occur.

@param aDest Descriptor where result is placed.
**/
inline void TBTDevAddr::GetReadable(TDes& aDest) const
	{
	GetReadable(aDest, KNullDesC, KNullDesC, KNullDesC);
	}

/**
Comparison operator.
@param aUUID Object to compare to this.
@return ETrue is aUUID is the same as this, EFalse if not.
*/
inline TBool TUUID::operator==(const TUUID& aUUID) const
	{
	return Mem::Compare(iUUID.Begin(), KSdpUUIDMaxLength, aUUID.iUUID.Begin(), KSdpUUIDMaxLength)==0;
	}

/**
Inequality operator.
@param aUUID Object to compare to this.
@return EFalse is aUUID is the same as this, ETrue if not.
*/
inline TBool TUUID::operator!=(const TUUID& aUUID) const
	{
	return !(*this==aUUID);
	}

/**
Access a single element of the UUID.
@param aIndex The index of the element to access.
@return The element.  The reference remains valid as long as this object is in scope.
*/
inline const TUint8 &TUUID::operator[](TInt aIndex) const
	{
	return iUUID[aIndex];
	}

/**
Access a single element of the UUID.
@param aIndex The index of the element to access.
@return The element.  The reference remains valid as long as this object is in scope.
*/
inline TUint8 &TUUID::operator[](TInt aIndex)
	{
	return iUUID[aIndex];
	}
