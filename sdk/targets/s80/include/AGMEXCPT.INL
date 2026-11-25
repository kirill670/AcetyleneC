// AGMEXCPT.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//



// -------------------------- TAgnException ------------------------------
inline TAgnDate TAgnException::Date() const
/** Gets the exception date.

@return The exception date. */
	{ return (iDate); }

//inline TAgnEntryId TAgnException::Id() const
//	{ return (iEntryId); }

inline void TAgnException::SetDate(TAgnDate aDate)
/** Sets the exception date, specified as an agenda date value.

@param aDate The exception date. */
	{ iDate=aDate; }

//inline void TAgnException::SetId(TAgnEntryId aId)
//	{ iEntryId=aId; }



// -------------------------- CAgnExceptionList -------------------------------------------


inline TInt CAgnExceptionList::InsertL(const TAgnException& aException)
	{	return (InsertIsqL(aException,iDateKey)); }

inline TInt CAgnExceptionList::Find(const TAgnException& aException,TInt& aPos)
	{ return (FindIsq(aException,iDateKey,aPos)); }

