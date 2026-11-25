//
// SMLDATASTORE.H
//

# if !defined(__SMLDATASTORE_H__)
#define __SMLDATASTORE_H__
#include <s32strm.h>
#include <f32file.h>
#include "smlids.h"


class CDictionaryStore;

/**

The CSmlDataStore class is used to store data in a storage space while hiding from the user of the class
where that store is located, its nature or its name. The user creates or opens one by passing in two CSmlIdentifier
objects. If the flag aCreate is ETrue the store is opened or created if it doesn't already exist. If the flag is EFalse,
the Call to NewL() will leave with KErrNotFound if the store does not already exist.
The two CSmlIdentifiers are used to uniquely identify a particular area of storage space. To add, update or extract
data from the storage space the object should be created in EUsingStoreMode. To delete an existing store it should be
opened in EDeletingStore mode - the store will be automatically deleted.
Data is accessed in the store by use of streams, a new stream can be created or an existing one opened for
updating by calling OpenWriteStreamL(). An existing stream can be opened for reading by calling OpenReadStreamL().
Changes to the store must be commited using CommitL()

*/
class CSmlDataStore : public CBase
	{
public:
	enum TMode
		{
		EUsingStore,
		EDeletingStore
		};

	IMPORT_C static CSmlDataStore* NewL(TUint aId1, TUint aId2,	TBool aCreate = EFalse, TMode = EUsingStore);
	IMPORT_C ~CSmlDataStore();
	IMPORT_C MStreamBuf* OpenReadStreamL(TUid aUid);
	IMPORT_C MStreamBuf* OpenWriteStreamL(TUid aUid);
	IMPORT_C TBool IsPresentL(TUid aUid) const;
	IMPORT_C void DeleteStreamL(TUid aUid);
	IMPORT_C void DeleteStoreL();
	IMPORT_C void CommitL();
	IMPORT_C void RevertL();

protected:
	void ConstructL(TUint aId1, TUint aId2, TBool aCreate, TMode aMode);
	CDictionaryStore*	iStore;
	RFs					iFs;
	TFileName			iFileName;
	TMode				iMode;
	};

#endif