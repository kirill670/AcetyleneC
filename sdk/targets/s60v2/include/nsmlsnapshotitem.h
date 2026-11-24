/*
* ==============================================================================
*  Name        : nsmlsnapshotitem.h
*  Part of     : Nokia SyncML / DS Utils (Changefinder)
*  Interface   : TNSmlSnapshotItem
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

#ifndef __NSMLSNAPSHOTITEM_H__
#define __NSMLSNAPSHOTITEM_H__

// ------------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------------
#include <e32base.h>
#include <nsmlids.h>

// ------------------------------------------------------------------------------------------------
// TNSmlSnapshotItem
// ------------------------------------------------------------------------------------------------
struct TNSmlSnapshotItem : public TNSmlDbItemUid
	{
public:
	/**
    * C++ constructor
    */
	IMPORT_C TNSmlSnapshotItem();

	/**
    * C++ constructor
    * @param aItemUid Preset UID.
    */
	IMPORT_C TNSmlSnapshotItem( const TNSmlDbItemUid& aItemUid );
	
	/**
    * C++ constructor
    * @param aLastChangedDate Preset last modification date.
    * @param aId Preset UID as descriptor.
    */
	IMPORT_C TNSmlSnapshotItem( const TTime& aLastChangedDate, const TDesC8& aId );
	
	/**
    * C++ constructor
    * @param aLastChangedDate Preset last modification date.
    * @param aId Preset UID as 64-bit integer.
    */
	IMPORT_C TNSmlSnapshotItem( const TTime& aLastChangedDate, TInt64 aId );

	/**
    * Stream externalizer method.
    * @param aStream Stream this snapshot item will be externalized into.
    */
	IMPORT_C void ExternalizeL( RWriteStream& aStream ) const;

	/**
    * Stream interlizer method.
    * @param aStream Stream this snapshot item will be internalized from.
    */
	IMPORT_C void InternalizeL( RReadStream& aStream );

	/**
    * Getter for last modification date value.
    * @return const TTime& Last modification date.
    */
	IMPORT_C const TTime& LastChangedDate() const;

	/**
    * Setter for last modification date value.
    * @param aLastChangedDate Last modification date.
    */
	IMPORT_C void SetLastChangedDate( const TTime& aLastChangedDate );

	/**
    * Compare method for comparing two snapshot items. Returns < 0 if this item is smaller
	* than aItem, returns 0 if both items are equal and > 0 if aItem is greater than
	* this snapshot item.
    * @param aItem Item which this item is compared to.
	* @return TInt Comparison result.
    */
	IMPORT_C virtual TInt Compare( const TNSmlSnapshotItem& aItem );

public:
	TTime iLastChangedDate;
	};

#endif // __NSMLSNAPSHOTITEM_H__
