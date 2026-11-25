/*
* ==============================================================================
*  Name        : nsmlids.h
*  Part of     : Nokia SyncML / DS Utils (Changefinder)
*  Interface   : TNSmlDbItemUid, TNSmlModificationItem
*  Description : Changefinder header
*  Version     : $Revision: 4 $ $Modtime: 18.06.03 14:10 $
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef __NSMLIDS_H__
#define __NSMLIDS_H__

// ------------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------------
#include <e32base.h>

// ------------------------------------------------------------------------------------------------
// Constants
// ------------------------------------------------------------------------------------------------
const TUint32 KNSmlMaxUidSize = 32;

// ------------------------------------------------------------------------------------------------
// Class forwards
// ------------------------------------------------------------------------------------------------
class RWriteStream;
class RReadStream;

// ------------------------------------------------------------------------------------------------
// TNSmlDbItemUid
// ------------------------------------------------------------------------------------------------
struct TNSmlDbItemUid
	{
public:
	/**
    * C++ constructor.
    */
	IMPORT_C TNSmlDbItemUid();

	/**
    * C++ constructor.
    * @param aId UID value as descriptor.
    */
	IMPORT_C TNSmlDbItemUid( const TDesC8& aId );

	/**
    * C++ constructor.
    * @param aId UID value as 64-bit integer.
    */
	IMPORT_C TNSmlDbItemUid( TInt64 aId );

	/**
    * Stream externalizer method.
    * @param aStream Stream this item UID will be externalized into.
    */
	IMPORT_C void ExternalizeL( RWriteStream& aStream ) const;

	/**
    * Stream internalizer method.
    * @param aStream Stream this item UID will be externalized into.
    */
	IMPORT_C void InternalizeL( RReadStream& aStream );

	/**
    * Check whether this UID is NULL (not set) or not.
    * @return TBool ETrue if this value is not set, EFalse otherwise.
    */
	IMPORT_C TBool IsNull() const;

	/**
    * Get maximum size of UID (in bytes).
    * @return TUint Maximum size of UID in bytes.
    */
	inline TUint MaxUidSize();

	/**
    * Sets UID value.
    * @param aId New UID value as descriptor.
    */
	IMPORT_C void SetId( const TDesC8& aId );

	/**
    * Sets UID value.
    * @param aId New UID value as 64-bit integer.
    */
	IMPORT_C void SetId( TInt64 aId );

	/**
    * const TDesC8& operator. Returns UID value as constant 8-bit descriptor.
    * @return const TDesC8& UID as constant 8-bit descriptor.
    */
	IMPORT_C operator const TDesC8& () const;

	/**
    * TInt64 operator. Returns UID value as 64-bit integer.
    * @return TInt64 UID as constant 64-bit integer.
    */
	IMPORT_C TInt64 operator ()() const;

public:
	TBuf8<KNSmlMaxUidSize> iId;
	TInt64 iUint;
	};

// ------------------------------------------------------------------------------------------------
// inline methods
// ------------------------------------------------------------------------------------------------
inline TUint TNSmlDbItemUid::MaxUidSize()
	{
	return KNSmlMaxUidSize;
	}

// ------------------------------------------------------------------------------------------------
// struct TNSmlModificationItem 
// ------------------------------------------------------------------------------------------------
struct TNSmlModificationItem 
	{
public:
	enum TNSmlModificationType
		{
		EAdd,
		EReplace,
		EDelete
		};

	/**
    * C++ constructor.
    * @param aUid UID of the item this modification belongs to.
	* @param aModType Type of modification.
    */
	IMPORT_C TNSmlModificationItem( const TNSmlDbItemUid& aUid, TNSmlModificationType aModType );

	/**
    * Getter for UID.
    * @return const TNSmlDbItemUid& UID of the item this modification belongs to.
    */
	IMPORT_C const TNSmlDbItemUid& Uid() const;

	/**
    * Getter for modification type.
    * @return TNSmlModificationItem::TNSmlModificationType Type of modification.
    */
	IMPORT_C TNSmlModificationItem::TNSmlModificationType ModificationType();

private:
	TNSmlDbItemUid iId;
	TNSmlModificationType iType;
	};

#endif // __NSMLIDS_H__
