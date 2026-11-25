// AGMREPLI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#ifndef __AGMREPLI_H__
#define __AGMREPLI_H__

#include "agmdate.h"

class TAgnReplicationData
/** Stores the synchronisation data associated with each agenda entry and to-do 
list. 

This data is used when a Symbian OS agenda file is synchronised with 
a PC or other scheduler. The synchronisation data consists of:

- a last changed date/time

- a status (controls access rights to the entry / to-do list)

- a synchronisation count (prevents synchronised entries or to-do lists from 
being fully deleted until they are no longer needed for synchronisation)

- a flag which indicates whether or not the entry / to-do list has been marked 
as deleted but cannot be fully deleted until its synchronisation count is zero 

@publishedAll
@released
*/
	{
public:
	/** Status */
	enum TStatus 
		{
		/** No restriction on access. */
		EOpen, 
		/** Data is private (no access). */
		EPrivate, 
		/** Data is confidential (restricted access). */
		ERestricted
		};

	IMPORT_C TAgnReplicationData();
	inline TStatus Status() const;
	inline TBool HasBeenDeleted() const;
	IMPORT_C TTime LastChangedDate() const;
	inline void SetStatus(TStatus aStatus);
	inline void SetHasBeenDeleted(TBool aHasBeenDeleted);
	IMPORT_C void SetLastChangedDate();
	IMPORT_C void SetLastChangedDate(const TTime& aTime);
	inline void IncCount();
	inline void DecCount();
	inline void SetCount(TUint aCount);
	inline TUint Count() const;
	IMPORT_C void Reset();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
protected:
	TStatus			iStatus;
	TBool			iHasBeenDeleted;
	TUint			iCount;
	TAgnDateTime	iLastChangedDate;
	};

#include "agmrepli.inl"

#endif
