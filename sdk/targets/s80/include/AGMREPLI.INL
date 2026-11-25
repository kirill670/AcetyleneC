// AGMREPLI.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline TAgnReplicationData::TStatus TAgnReplicationData::Status() const
/** Gets the replication status for the agenda entry/to-do list.

@return The status. */
	{ return (iStatus); }

inline TBool TAgnReplicationData::HasBeenDeleted() const
/** Tests whether the 'has been deleted' flag is set.

@return True = the flag is set, otherwise False. */
	{ return (iHasBeenDeleted); }

inline void TAgnReplicationData::SetStatus(TStatus aStatus)
/** Sets the replication status for an agenda entry or to-do list.

@param aStatus The status. */
	{ 
	__ASSERT_DEBUG(aStatus == EOpen || aStatus == EPrivate || aStatus == ERestricted,
			Panic(_L("Invalud TStatus enum")));
	iStatus = aStatus; 
	}

inline void TAgnReplicationData::SetHasBeenDeleted(TBool aHasBeenDeleted)
/** Sets the 'has been deleted' flag to the specified value.

@param aHasBeenDeleted True to set the flag, False to clear the flag. */
	{ iHasBeenDeleted = aHasBeenDeleted; }

inline void TAgnReplicationData::IncCount()
/** Increments the synchronisation count. */
	{ ++iCount; }

inline void TAgnReplicationData::DecCount()
/** Decrements the synchronisation count. */
	{ 
	__ASSERT_DEBUG(iCount,Panic(_L("Decrementing past 0")));
	--iCount;
	}

inline void TAgnReplicationData::SetCount(TUint aCount)
/** Sets the synchronisation count.

@param aCount The new count. */
	{ iCount = aCount; }

inline TUint TAgnReplicationData::Count() const
/** Gets the synchronisation count.

@return The count. */
	{ return (iCount); }
