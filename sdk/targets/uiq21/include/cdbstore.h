// CDBSTORE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __CDBSTORE_H__
#define __CDBSTORE_H__

#include <s32mem.h>
#include <cdbover.h>

/** Extends `CCommDbOverrideSettings` to provide functions that store and
	retrieve override sets to and from both streams and buffers.
*/
class CStoreableOverrideSettings : public CCommDbOverrideSettings
	{
public:
	IMPORT_C static CStoreableOverrideSettings* NewL(TParamList aParamList);
	IMPORT_C ~CStoreableOverrideSettings();

	/** Initialise the override set from a stream. */
	IMPORT_C void InternalizeL(RReadStream& aStream);
	/** nitialise the override set from a buffer */
	IMPORT_C void RestoreL(HBufC8* aBuf);
	/** Copy the override set to a stream. */
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	/** Copy the override set to a buffer. */
	IMPORT_C CBufFlat* StoreLC();
	/** Access the buffer store
		@internal "This is pointless - none of the above functions use this
					store. If a client needs a store it should create its own"
		@deprecated 7.0 "There is no need for this store"
	*/
	inline CBufStore* GetStore() const;

protected:
	/** @private */
	CStoreableOverrideSettings(TParamList aParamList);
	virtual void ConstructL();
private:
	/** @deprecated 7.0 "There is no need for this store" */
	CBufStore* iStore;
	};

#include <cdbstore.inl>

#endif