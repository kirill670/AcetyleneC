/**
@file COMMDB.INL

Comms Database and Table inline functions

Written by AEW, July 1998
Copyright (C) Symbian Ltd 2003
*/

#ifndef __COMMDB_INL__
#define	__COMMDB_INL__

#include <commdb.h>
#include <cdbpreftable.h>


inline RDbNamedDatabase* CCommsDatabaseBase::Database()
/**
Returns the interface for creating and opening a database identified by name and format.

@return A pointer to the interface for creating and opening a database identified by name and format.
*/
	{
	return &iDatabase;
	}

inline void CCommsDbTableView::GetTableName(TDes& aTableName) const
/** 
Gets the name of the table associated with this view and copies it into the 
descriptor supplied by the caller.

@param aTableName A reference to a descriptor passed by the caller. On return 
from this function it contains the name of the table. 
*/
	{
	aTableName=iTableName;
	}

inline TDbColNo CCommsDbConnectionPrefTableView::ColNum(const TDesC& aColumn) const
/**
Returns the column number of the Column aColumn in the table

@param aColumn A reference to a descriptor containing the name of a column in the current record. 
@return The ordinal number of the column else KDbNullColNo if no such column exists.
*/
	{
	return iTableExt->GetColSet()->ColNo(aColumn);
	}


#endif

