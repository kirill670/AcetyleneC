// AGMREPLI.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline TAgnReplicationData::TStatus TAgnReplicationData::Status() const
	{ return (iStatus); }

/**
 * Tests whether the has been deleted flag is set.
 *
 * @returns   "TBool"
 *            True = the flag is set, otherwise False.
 */
inline TBool TAgnReplicationData::HasBeenDeleted() const
	{ return (iHasBeenDeleted); }

/**
 * Sets the status for an agenda entry or to-do list.
 *
 * @param     "TStatus aStatus"
 *            The status.
 */
inline void TAgnReplicationData::SetStatus(TStatus aStatus)
	{ 
	__ASSERT_DEBUG(aStatus == EOpen || aStatus == EPrivate || aStatus == ERestricted,
			Panic(_L("Invalud TStatus enum")));
	iStatus = aStatus; 
	}

/**
 * Sets the has been deleted flag to the specified value.
 *
 * @param     "TBool aHasBeenDeleted"
 *            True to set the flag, False to clear the flag.
 */
inline void TAgnReplicationData::SetHasBeenDeleted(TBool aHasBeenDeleted)
	{ iHasBeenDeleted = aHasBeenDeleted; }

/**
 * Increments the synchronisation count.
 */
inline void TAgnReplicationData::IncCount()
	{ ++iCount; }

/**
 * Decrements the synchronisation count.
 */
inline void TAgnReplicationData::DecCount()
	{ 
	__ASSERT_DEBUG(iCount,Panic(_L("Decrementing past 0")));
	--iCount;
	}

/**
 * Sets the synchronisation count.
 *
 * @param     "TUint aCount"
 *            The count to be set.
 */
inline void TAgnReplicationData::SetCount(TUint aCount)
	{ iCount = aCount; }

/**
 * Gets the synchronisation count.
 *
 * @returns   "TUint"
 *            The count.
 */
inline TUint TAgnReplicationData::Count() const
	{ return (iCount); }
