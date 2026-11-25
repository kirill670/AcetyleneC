/////////////////////////////////////////////////////////////////////////////
//
//	MsvScheduledEntry.INL
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

inline const TMsvId CMsvScheduledEntry::Id() const
/** Gets the entry's ID.

@return The entry's ID */
	{
	return iEntry.Id();
	}

inline const TBool CMsvScheduledEntry::OffPeak() const
/** Gets the entry's OffPeak() flag.

@return The entry's OffPeak() flag */
	{
	return iEntry.OffPeak();
	}

inline const TUid CMsvScheduledEntry::Mtm() const
/** Gets the entry's iMtm data member.

@return The entry's iMtm data member */
	{
	return iEntry.iMtm;
	}

inline const TTime& CMsvScheduledEntry::ScheduleDate() const
/** Gets the entry's iDate member.

@return Entry's iDate member */
	{
	return iEntry.iDate;
	}

inline void CMsvScheduledEntry::SetScheduleDate(const TTime& aDate)
/** Sets the entry's iDate member.

@param aDate Entry's iDate member */
	{
	iEntry.iDate = aDate;
	}

inline const TBool CMsvScheduledEntry::Scheduled() const
/** Gets the entry's Scheduled() flag.

@return The entry's Scheduled() flag */
	{
	return iEntry.Scheduled();
	}

inline void CMsvScheduledEntry::SetScheduled(const TBool aScheduled)
/** Sets the entry's Scheduled() flag.

@param aScheduled The entry's Scheduled() flag */
	{
	iEntry.SetScheduled(aScheduled);
	}

inline const TInt CMsvScheduledEntry::Error() const
/** Gets the entry's iError data member.

@return The entry's iError data member */
	{
	return iEntry.iError;
	}

inline const TInt CMsvScheduledEntry::SendingState() const
/** Gets the entry's SendingState() flag.

@return The entry's SendingState() flag */
	{
	return iEntry.SendingState();
	}

inline void CMsvScheduledEntry::SetSendingState(TInt aState)
/** Sets the entry's SendingState() flag.

@param aState The entry's SendingState() flag */
	{
	iEntry.SetSendingState(aState);
	}

inline void CMsvScheduledEntry::SetFailed(const TBool aFail)
/** Sets the entry's Failed() flag.

@param aFail The entry's Failed() flag */
	{
	iEntry.SetFailed(aFail);
	}

inline const TBool CMsvScheduledEntry::Failed() const
/** Gets the entry's Failed() flag.

@return The entry's Failed() flag */
	{
	return iEntry.Failed();
	}
