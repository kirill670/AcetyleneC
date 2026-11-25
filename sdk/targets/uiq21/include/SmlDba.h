//
// SMLDBA.H
//

#if !defined(__SMLDBA_H__)
#define __SMLDBA_H__

#include <smlids.h>

class CSmlDataStore;

/**

The CSmlDbAdapter is an abstract class defining the API all DB Adapters must implement

*/
class CSmlDbAdapter : public CBase
	{
public:
	static CSmlDbAdapter* NewL(const TUid& aImplementationUid, CSmlDataStore* aDataStore = NULL);
	virtual ~CSmlDbAdapter();
	virtual void OpenDbL(const TFileName& aDb, TRequestStatus& aStatus) = 0;
	virtual void CreateFileL(const TFileName& aFileName) = 0;
	virtual TBool DoesDbUidMatchL() const = 0;
	virtual void CancelOpenL() = 0;
	virtual void CloseL() = 0;
	virtual void AddItemL(TSmlDbItemUid& aUid, const TDesC8& aItem) = 0;
	virtual void FetchItemL(const TSmlDbItemUid& aUId, CBufBase& aBuffer) = 0;
	virtual void UpdateItemL(const TSmlDbItemUid& aUid, const TDesC8& aItem) = 0;
	virtual void DeleteItemL(const TSmlDbItemUid& aUId) = 0;
	virtual void FetchDeletedItemUidsL(CArrayFix<TSmlDbItemUid>& aItems, const TTime& aFrom = Time::NullTTime()) = 0;
	virtual void FetchNewItemUidsL(CArrayFix<TSmlDbItemUid>& aItems, const TTime& aFrom = Time::NullTTime()) = 0;
	virtual void FetchChangedItemUidsL(CArrayFix<TSmlDbItemUid>& aItems, const TTime& aFrom = Time::NullTTime()) = 0;
	virtual HBufC* DbCapabilitiesL() const = 0;
	virtual void ServerDbCapabilitiesL(const TDesC& aCapabilities) = 0;
	virtual void SetRxItemDataFormatL(const TDesC& aFormat, const TDesC& aVersion) = 0;
	virtual void SetTxItemDataFormatL(const TDesC& aFormat, const TDesC& aVersion) = 0;
	virtual TInt ItemEncoding() const = 0;
	virtual void SetMetaInformationL(const TDesC8& aData) = 0;
	virtual HBufC8* GetMetaInformationL() const = 0;
	virtual void ResetL() = 0;
	virtual TVersion Version() const = 0;
	virtual void ResetDatabaseL() = 0;
	virtual void BeginTransactionL() = 0;
	virtual void CommitTransactionL() = 0;
	virtual void RollbackL() = 0;
	virtual TBool SupportTransaction() const = 0;
	virtual TBool DoesDatabaseExistL(const TDesC& aDatabase) const = 0;
private:
	TUid	iDtorKey; 
	};

#include <smldba.inl>


#endif