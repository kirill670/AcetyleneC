// AGMSITER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMSITER_H__
#define __AGMSITER_H__

#include "agclient.h"


/**
 * Agenda model entry iterator used for synchronisation.
 *
 * To use this class, the agenda model must be in client mode. If the
 * model is not in client mode, use the <code>TAgnEntryIter</code> class
 * instead.The following code sets up a <code>CAgnSyncIter</code> and
 * uses it to iterate through all entries:
 *
 * @since 5.0
 * @lib "agnmodel.lib"
 */
class CAgnSyncIter : public CBase
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
	void SetLastChangedCounter(TInt aCounter);
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
	{
	return iAvailable;
	}

/**
 * Gets the entry ID of the entry at the current iterator position, if an
 * entry is available.
 *
 * @returns   "TAgnEntryId"
 *            The entry ID of the entry at the current iterator
 *            position.
 */
inline TAgnEntryId CAgnSyncIter::EntryId()
	{
	return iEntryId;
	}

/**
 * Gets the unique ID of the entry at the current iterator position, if
 * an entry is available.
 *
 * @returns   "TAgnUniqueId"
 *            The unique ID of the entry at the current iterator
 *            position.
 */
inline TAgnUniqueId CAgnSyncIter::UniqueId()
	{
	return iUniqueId;
	}

/**
 * Tests whether the entry at the current iterator position, if one is
 * available, has been marked as deleted.
 *
 * This indicates that the entry has been deleted by the user, but it
 * cannot be fully deleted by the model, because it has been synchronised
 * and has a positive synchronisation count. It should not be displayed
 * in views.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the entry has been marked as
 *            deleted, otherwise <code>EFalse</code>.
 */
inline TBool CAgnSyncIter::HasBeenDeleted()
	{
	return iDeleted;
	}

/**
 * Gets the type of the entry at the current iterator position, if one is
 * available.
 *
 * @returns   "CAgnEntry::TType"
 *            The type of the entry at the current iterator
 *            position.
 */
inline CAgnEntry::TType CAgnSyncIter::Type()
	{
	return iType;
	}

/**
 * Gets the agenda date/time that the entry at the current iterator
 * position, if one is avaliable, was last changed.
 *
 * @returns   "TAgnDateTime"
 *            The entry's last changed date/time.
 */
inline TAgnDateTime CAgnSyncIter::LastChangedDate()
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
