//
// SMLCHANGEFINDER.H
//

#if !defined(__SMLCHANGEFINDER_H__)
#define __SMLCHANGEFINDER_H__

#include <smlids.h>


/**

The TSmlSnapshotItem class represents the date/time when an item in a database was last changed (where
a change also includes its creation and deletion)

*/
class TSmlSnapshotItem : public TSmlDbItemUid
	{
public:
	IMPORT_C TSmlSnapshotItem();
	IMPORT_C TSmlSnapshotItem(const TTime& aLastChangedDate, const TDesC& aUid);
	IMPORT_C TSmlSnapshotItem(const TTime& aLastChangedDate, TUint aUid);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void SetLastChangedDate(const TTime& aLastChangedDate);
	IMPORT_C const TTime& LastChangedDate() const;
protected:
	TTime	iLastChangedDate;
	};


class CSmlDataStore;

/**

The CSmlChangeFinder  class may be used to determine which items in a database are new, have been changed
or have been deleted since a particular data/time.

*/
class CSmlChangeFinder : public CBase
	{
public:
	IMPORT_C static CSmlChangeFinder* NewL(CSmlDataStore& aDataStore);
	IMPORT_C CSmlChangeFinder(CSmlDataStore& aDataStore);
	IMPORT_C  ~CSmlChangeFinder();

	IMPORT_C void FindNewItemsL(CArrayFix<TSmlDbItemUid>& aNewUids, const TTime& aFrom);
	IMPORT_C void FindChangedItemsL(CArrayFix<TSmlDbItemUid>& aChangedUids, const TTime& aFrom);
	IMPORT_C void FindDeletedItemsL(CArrayFix<TSmlDbItemUid>& aDeletedUids, const TTime& aFrom);
	IMPORT_C void SetNewSnapshotL(CArrayFixSeg<TSmlSnapshotItem>& aNewSnapshot);
	IMPORT_C void ItemAddedL(const TSmlSnapshotItem& aItem);
	IMPORT_C void ItemDeletedL(const TSmlSnapshotItem& aItem);
	IMPORT_C void ItemUpdatedL(const TSmlSnapshotItem& aItem);
	IMPORT_C void CloseL();
	IMPORT_C void ResetL();
private:
	void ConstructL();	
	void CreateOrRestoreSnapshotL();

private:
	TKeyArrayFix					iSnapshotKey;
	CSmlDataStore&					iDataStore;
	CArrayFixSeg<TSmlSnapshotItem>*	iOldSnapshot;
	CArrayFixSeg<TSmlSnapshotItem>*	iNewSnapshot;
	TTime							iCreationTime;
	};


#endif