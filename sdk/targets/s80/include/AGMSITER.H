// AGMSITER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMSITER_H__
#define __AGMSITER_H__

#include "agclient.h"


class CAgnSyncIter : public CBase
/** Agenda model entry iterator, used for synchronisation.

To use this class, the agenda model must be in client mode. If not, 
use the TAgnEntryIter class instead.

The following code sets up a CAgnSyncIter and uses it to iterate through all 
entries:

@code
CAgnSyncIter* iter = CAgnSyncIter::NewL(agnServer);
CleanupStack::PushL(iter); // Push onto cleanup stack
iter->First(); // go to the first entry
while (iter->Available())
	{
	CAgnEntry* entry = model->FetchEntryL(iter->UniqueId());
	// ... do something with the entry
	iter->Next(); // move to next entry
	}
CleanupStack::PopAndDestroy(); // iter
@endcode 
@publishedAll
@released */

	{
	friend class RAgendaServ;
public:
	IMPORT_C static CAgnSyncIter* NewL(RAgendaServ* aServ);
	IMPORT_C static CAgnSyncIter* NewL();

	// Navigation functions
	IMPORT_C void First();
	IMPORT_C void Next();

	// Query functions
	inline TBool Available();
	inline TAgnEntryId EntryId();
	inline TAgnUniqueId UniqueId();
	inline TBool HasBeenDeleted();
	inline CAgnEntry::TType Type();
	inline TAgnDateTime LastChangedDate();

	// Setter functions

	inline void SetAvailable(TBool aAvailable);
	inline void SetEntryId(TAgnEntryId aId);
	inline void SetUniqueId(TAgnUniqueId aId);
	inline void SetHasBeenDeleted(TBool aDeleted);
	inline void SetType(CAgnEntry::TType aType);
	inline void SetLastChangedDate(TAgnDateTime aDateTime);
	inline void SetPosition(TInt aPosition);
	CAgnSyncIter();

private:
	inline TInt Position();

private:
	RAgendaServ*	iServer;
	TBool			iAvailable;
	TInt			iPosition;
	TAgnEntryId		iEntryId;
	TAgnUniqueId	iUniqueId;
	TBool			iDeleted;
	CAgnEntry::TType iType;
	TAgnDateTime	iDate;
	TInt			iLastChangedCounter;
	};

// Inline functions

inline TBool CAgnSyncIter::Available()
/** Tests whether there is an entry at the current iterator position. 

First() or Next() should have been called before calling this function.

@return ETrue if an entry exists, EFalse if not. */
	{
	return iAvailable;
	}

inline TAgnEntryId CAgnSyncIter::EntryId()
/** Gets the entry ID of the entry at the current iterator position, if an entry 
is available.

@return The entry ID of the entry at the current iterator position. */
	{
	return iEntryId;
	}

inline TAgnUniqueId CAgnSyncIter::UniqueId()
/** Gets the unique ID of the entry at the current iterator position, if there is one.

@return The unique ID of the entry at the current iterator position. */
	{
	return iUniqueId;
	}

inline TBool CAgnSyncIter::HasBeenDeleted()
/** Tests whether the entry at the current iterator position, if one is available, 
has been marked as deleted.

This indicates that the entry has been deleted by the user, but it cannot 
be fully deleted by the model, because it has been synchronised and has a 
positive synchronisation count. It should not be displayed in views.

@return ETrue if the entry has been marked as deleted, otherwise EFalse. */
	{
	return iDeleted;
	}

inline CAgnEntry::TType CAgnSyncIter::Type()
/** Gets the type of the entry at the current iterator position, if there is one.

@return The type of the entry at the current iterator position. */
	{
	return iType;
	}

inline TAgnDateTime CAgnSyncIter::LastChangedDate()
/** Gets the agenda date/time that the entry at the current iterator position 
was last changed, if there is one.

@return The entry's last changed date/time. */
	{
	return iDate;
	}

inline TInt CAgnSyncIter::Position()
	{
	return iPosition;
	}


// Setters

inline void CAgnSyncIter::SetAvailable(TBool aAvailable)
	{
	iAvailable = aAvailable;
	}


inline void CAgnSyncIter::SetEntryId(TAgnEntryId aId)
	{
	iEntryId = aId;
	}

inline void CAgnSyncIter::SetUniqueId(TAgnUniqueId aId)
	{
	iUniqueId = aId;
	}

inline void CAgnSyncIter::SetHasBeenDeleted(TBool aDeleted)
	{
	iDeleted = aDeleted;
	}

inline void CAgnSyncIter::SetType(CAgnEntry::TType aType)
	{
	iType = aType;
	}

inline void CAgnSyncIter::SetLastChangedDate(TAgnDateTime aDateTime)
	{
	iDate = aDateTime;
	}

inline void CAgnSyncIter::SetPosition(TInt aPosition)
	{
	iPosition = aPosition;
	}



#endif
