//
// SMLIDS.H
//

#if !defined(__SMLIDS_H__)
#define __SMLIDS_H__
#include <s32strm.h>




/**

The TSmlDbItemUid class identifies an item in a database. The class is used by
the Client Engine and by the database adapter plugins.

*/
class TSmlDbItemUid
	{
public:
	inline TSmlDbItemUid() : iId (KNullDesC), iUint(0) {};
	inline TSmlDbItemUid(const TDesC& aId)  { SetId(aId); };
	inline TSmlDbItemUid(TUint aId) { SetId(aId); };
	inline operator const TDesC& () const { return iId; };
	inline TUint operator ()() const { return iUint; };
	inline TUint Id() const { return iUint; };
	inline void SetId(const TDesC& aId) { iId = aId; TLex(iId).Val(iUint); };
	inline void SetId(TUint aId) {iId.Num(aId); iUint = aId;};
	inline void InternalizeL(RReadStream& aStream) { iUint = aStream.ReadUint32L(); SetId(iUint); };
	inline void ExternalizeL(RWriteStream& aStream) const { aStream.WriteUint32L(iUint); };
	inline TBool IsNull() const { return iId==KNullDesC; };
	static inline TUint MaxUidSize() { return 32; };

	TBuf<32>	iId;
	TUint		iUint;
	};



/**

The CSmlIdentifier class represents a syncML system entity. Any item or object
can be represented by this class, as a string-Id pair. The class is used by
the Synchronisation Controller and a SyncML user-interface application.

*/
class CSmlIdentifier : public CBase
	{
public:
	IMPORT_C static CSmlIdentifier* NewL(const TDesC& aName, TUint aId = 0);
	IMPORT_C static CSmlIdentifier* NewL(const CSmlIdentifier& aId);
	IMPORT_C static CSmlIdentifier* NewL();
	IMPORT_C static CSmlIdentifier* NewL(RReadStream& aStream);
	IMPORT_C ~CSmlIdentifier();
	IMPORT_C operator const TDesC&() const;
	IMPORT_C operator TUint() const;
	IMPORT_C TBool operator ==(const CSmlIdentifier& aId) const;
	IMPORT_C void SetNameL(const TDesC& aName);
	IMPORT_C void SetId(TUint aId);
	IMPORT_C const TDesC& Name() const;
	IMPORT_C TUint Id() const;
	IMPORT_C void CopyL(const CSmlIdentifier& aIdentifier);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
protected:
	void ConstructL(const TDesC& aName, TUint aId);

	HBufC*		iName;
	TUint		iId;
	};

#endif