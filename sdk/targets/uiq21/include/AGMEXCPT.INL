// AGMEXCPT.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//



// -------------------------- TAgnException ------------------------------
/**
 * Gets the exception date.
 *
 * @returns   "TAgnDate"
 *            The exception date.
 */
inline TAgnDate TAgnException::Date() const
	{ return (iDate); }

//inline TAgnEntryId TAgnException::Id() const
//	{ return (iEntryId); }

/**
 * Sets the exception date, specified as an agenda date value.
 *
 * @param     "TAgnDate aDate"
 *            The exception date.
 */
inline void TAgnException::SetDate(TAgnDate aDate)
	{ iDate=aDate; }

//inline void TAgnException::SetId(TAgnEntryId aId)
//	{ iEntryId=aId; }



// -------------------------- CAgnExceptionList -------------------------------------------


inline TInt CAgnExceptionList::InsertL(const TAgnException& aException)
	{	return (InsertIsqL(aException,iDateKey)); }

inline TInt CAgnExceptionList::Find(const TAgnException& aException,TInt& aPos)
	{ return (FindIsq(aException,iDateKey,aPos)); }

