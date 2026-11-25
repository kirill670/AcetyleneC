/*
* ==============================================================================
*  Name        : nsmlchangefinder.h
*  Part of     : Nokia SyncML / DS Utils (Changefinder)
*  Interface   : CNSmlChangeFinder
*  Description : Changefinder header
*  Version     : $Revision: 5 $ $Modtime: 18.06.03 14:09 $
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

#ifndef __NSMLCHANGEFINDER_H__
#define __NSMLCHANGEFINDER_H__

// ------------------------------------------------------------------------------------------------
// Includes
// ------------------------------------------------------------------------------------------------
#include <e32base.h>
#include <nsmlsnapshotitem.h>

// ------------------------------------------------------------------------------------------------
// Class forwards
// ------------------------------------------------------------------------------------------------
class MNSmlDataStore;

// ------------------------------------------------------------------------------------------------
// Constants
// ------------------------------------------------------------------------------------------------
const TInt KNSmlDefaultSnapshotStreamUID = 0x101F6DE4;

// ------------------------------------------------------------------------------------------------
// CNSmlChangeFinder
// ------------------------------------------------------------------------------------------------
class CNSmlChangeFinder : public CBase
	{
public:
	/**
    * Two-phase constructor for CNSmlChangeFinder class.
    * @param aDataStore Pointer to MNSmlDataStore interface. This parameter may be NULL.
    * @param aKey Key that is used in sorting snapshot.
    * @param aStreamUid Snapshot stream UID.
	* @return CNSmlChangeFinder* Pointer to newly created instance.
    */
	IMPORT_C static CNSmlChangeFinder* NewL( MNSmlDataStore* aDataStore, TKeyArrayFix aKey, TInt aStreamUid = KNSmlDefaultSnapshotStreamUID );

	/**
    * C++ destructor.
    */
	IMPORT_C ~CNSmlChangeFinder();

	/**
    * Closes and saves snapshot.
    */
	IMPORT_C void CloseL();

	/**
    * Resets (clears) snapshot.
    */
	IMPORT_C void ResetL();

	/**
    * Returns changed items.
	* @param aChangedUids On return contains changed items.
	* @param aFrom From which time on changes should be found.
    */
	IMPORT_C void FindChangedItemsL( CArrayFix<TNSmlDbItemUid>& aChangedUids, const TTime& aFrom );

	/**
    * Returns deleted items.
	* @param aChangedUids On return contains deleted items.
    */
	IMPORT_C void FindDeletedItemsL( CArrayFix<TNSmlDbItemUid>& aDeletedUids );

	/**
    * Returns new items.
	* @param aChangedUids On return contains new items.
	* @param aFrom From which time on additions should be found.
    */
	IMPORT_C void FindNewItemsL( CArrayFix<TNSmlDbItemUid>& aNewUids, const TTime& aFrom );

	/**
    * Update snapshot for added item.
	* @param aItem Item that needs update.
    */
	IMPORT_C void ItemAddedL( const TNSmlSnapshotItem& aItem );

	/**
    * Update snapshot for deleted item.
	* @param aItem Item that needs update.
    */
	IMPORT_C void ItemDeletedL( const TNSmlSnapshotItem& aItem );

	/**
    * Update snapshot for updated item.
	* @param aItem Item that needs update.
    */
	IMPORT_C void ItemUpdatedL( const TNSmlSnapshotItem& aItem );

	/**
    * Update snapshot for item that was deleted by the partner.
	* @param aItem Item that needs update.
    */
	IMPORT_C void PartnerDeletedL( const TNSmlSnapshotItem& aItem );

	/**
    * Update snapshot for item that was added by the partner.
	* @param aItem Item that needs update.
    */
	IMPORT_C void PartnerAddedL( const TNSmlSnapshotItem& aItem );

	/**
    * Update snapshot for item that was replaced by the partner.
	* @param aItem Item that needs update.
    */
	IMPORT_C void PartnerReplacedL( const TNSmlSnapshotItem& aItem );
		
	/**
    * Sets new (current) snapshot.
	* @param aNewSnapshot New snapshot.
    */
	IMPORT_C void SetNewSnapshotL( CArrayFixSeg<TNSmlSnapshotItem>& aNewSnapshot );

protected:
	CNSmlChangeFinder( MNSmlDataStore* aDataStore, TKeyArrayFix aKey, TInt aStreamUid );
	void ConstructL();

private:
	MNSmlDataStore* iDataStore;
	CArrayFixSeg<TNSmlSnapshotItem>* iCurrentSnapshot;
	CArrayFixSeg<TNSmlSnapshotItem>* iOldSnapshot;
	TKeyArrayFix iKey;
	TInt iStreamUid;
	};

#endif // __NSMLCHANGEFINDER_H__
