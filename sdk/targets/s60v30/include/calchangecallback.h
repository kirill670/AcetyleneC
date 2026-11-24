// calchangecallback.h
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//
#ifndef __CALCHANGECALLBACK_H__
#define __CALCHANGECALLBACK_H__

#include "calcommon.h"

class TCalChangeEntry;

class MCalChangeCallBack
/** A call back class for observing changes in the model view. 

A client will not be notified of a change if it is the source of 
the change.

@publishedAll
@released
*/
	{
public:
	/** Instance view change type
	@publishedAll
	@released
	*/
	enum TChangeType
		{
		EChangeAdd,
		EChangeDelete,
		EChangeModify,
		EChangeUndefined,
		EChangeOverflowError
		};

	/** Instance view entry type
	@publishedAll
	@released
	*/
	enum TChangeEntryType
		{
		EChangeEntryTodo,
		EChangeEntryEvent,
		EChangeEntryAll
		};	

	virtual void CalChangeNotification(TChangeEntryType aChangeEntryType) = 0;
	};

/** A call back class for observing changes in the model view.

The call back returns an array containing information about at least 
one change to the database. The information includes the type of change 
and the identity of the item being changed.

A client will not be notified of a change if it is the source of 
the change. 

@publishedAll
@prototype
*/
class MCalChangeCallBack2
	{
public:
	/** Instance view change type
	@publishedAll
	@prototype
	*/
	enum TChangeType
		{
		EChangeAdd,
		EChangeDelete,
		EChangeModify,
		EChangeUndefined
		};

	/** Instance view entry type
	@publishedAll
	@prototype
	*/
	enum TChangeEntryType
		{
		EChangeEntryTodo,
		EChangeEntryEvent,
		EChangeEntryAll
		};	
		
	virtual void CalChangeNotification(RArray<TCalChangeEntry>& aChangeItems) = 0;
	};

/** Struct for storing change notification data.
This contains the calendar local ID, the type of change and the entry type.

The iChangeType will only be set to EChangeEntryTodo or EChangeEntryEvent
values. EChangeEntryAll is provided for callback registration only.

If iChangeType is EChangeUndefined or EChangeOverflowError, iEntryId and 
iEntryType are undefined and should not be used by clients.

@publishedAll
@prototype
*/
struct TCalChangeEntry
	{
	TCalLocalUid iEntryId;
	MCalChangeCallBack2::TChangeType iChangeType;
	MCalChangeCallBack2::TChangeEntryType iEntryType;
	};

/** Class to encapsulate call back registration parameters.

The type of entries, the date range and whether undated todos are included
can be specified.

@publishedAll
@prototype
*/
class CCalChangeNotificationFilter
	{
public:
	IMPORT_C static CCalChangeNotificationFilter* NewL(MCalChangeCallBack2::TChangeEntryType aChangeEntryType, TBool aIncludeUndatedTodos, const CalCommon::TCalTimeRange& aTimeRange);
	IMPORT_C ~CCalChangeNotificationFilter();
	
	MCalChangeCallBack2::TChangeEntryType ChangeEntryType() const;
	TCalTime StartTime() const;
	TCalTime EndTime() const;
	TBool IncludeUndatedTodos() const;

private:
	CCalChangeNotificationFilter(MCalChangeCallBack2::TChangeEntryType aChangeEntryType, TBool aIncludeUndatedTodos, const CalCommon::TCalTimeRange& aTimeRange);

	MCalChangeCallBack2::TChangeEntryType iChangeEntryType;
	CalCommon::TCalTimeRange iTimeRange;
	TBool iIncludeUndatedTodos;
	};
	
#endif // __CALCHANGECALLBACK_H__
