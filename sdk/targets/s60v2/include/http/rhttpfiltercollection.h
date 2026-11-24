// RHTTPFilterCollection.h
//
// Copyright (C) 2001 Symbian Ltd.

/** 
	@file RHTTPFilterCollection.h
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef	__RHTTPFILTERCOLLECTION_H__
#define	__RHTTPFILTERCOLLECTION_H__ 

// System includes
#include <e32std.h>
#include <http/thttpevent.h>
#include <stringpool.h>

// Forward declarations
class CHTTPSession;
class RHTTPSession;
class MHTTPFilter;
class THTTPFilterIterator;


//##ModelId=3C4C187C02B3
class RHTTPFilterCollection
/** 
A Handle on the filter collection in a session. It provides
facilities for adding and deleting filters and for querying what
filters are installed. 
@publishedAll
@released
@see RHTTPSession::FilterCollection 
@see MHTTPFilter::TPositions
*/
	{
 public:
	//##ModelId=3C4C187C02F9
	inline RHTTPFilterCollection();
	/** Adds a filter to the session's filter queue.  

		Note: This function only adds filters; it doesn't replace or
		otherwise affect any pre-existing filters.

		@pre The session is open and no transactions have been created yet.
		@param aFilter The filter to add
		@param aEvent The event that triggers this filter (or all)
		@param aHeader The header whose presence triggers this filter
		(or KNullDesC for any) 
		@param aStatusCode The status code that triggers this filter
		(or -1 for all) 
		@param aPosition The position of the filter in the
		queue. Standard values are documented in the documentation for
		the supplied filters, and are based on the standard defines in
		MHTTPFilter::TPositions
		@param aName  the name of the Filter to add
		@exception KErrNoMemory There was not enough memory. 
		@see See MHTTPFilter::TPositions */
	//##ModelId=3C4C187C02E5
	IMPORT_C void AddFilterL(MHTTPFilter& aFilter, THTTPEvent aEvent,
							 RStringF aHeader, TInt aStatusCode, 
 							 TInt aPosition, RStringF aName);


	/** Adds a filter to the session's filter queue.
		Intended Usage: This variant takes no status code or header. It is intended for filters
		that are only interested in events. For example session events.
		@pre The session is open and no transactions have been created yet
		@param aFilter The filter to add
		@param aEvent The event that triggers this filter (or all)
		@param aPosition The position of the filter in the
		queue. Standard values are documented in the documentation for
		the supplied filters, and are based on the standard defines in
		MHTTPFilter::TPositions
		@param aName  the name of the Filter to add
		@exception KErrNoMemory There was not enough memory. 
		@see See MHTTPFilter::TPositions */
	//##ModelId=3C4C187C02F1
	IMPORT_C void AddFilterL(MHTTPFilter& aFilter, THTTPEvent aEvent, 
 							 TInt aPosition, RStringF aName);

	/** Returns ETrue if filters can currently be added or removed.
		Filters can only be added/removed if there are no transactions
		in existence on the session.
	*/
	//##ModelId=3C4C187C02DF
	IMPORT_C TBool CanChangeFilters() const;

	/// Removes all filter registrations of the specified name.
	//##ModelId=3C4C187C02DD
	IMPORT_C void RemoveFilter(RStringF aFilter);
	/** Returns an iterator to look at all filter registrations of a
		particular name. By default it will find all filters.
		@param aName The name of the filter to find. (All filters will
		be found if the default parameter is used) 
	*/
	//##ModelId=3C4C187C02DB
	IMPORT_C THTTPFilterIterator Query(RStringF aName = RStringF());

	//##ModelId=3C4C187C02D1
	inline RHTTPSession Session() const;

 private:
	friend class CHTTPSession;
	friend class RHTTPSession;

	//##ModelId=3C4C187C02C9
	CHTTPSession* iImplementation;
	};


inline RHTTPFilterCollection::RHTTPFilterCollection()
		: iImplementation(NULL)
	{
	}

#endif //	__RHTTPFILTERCOLLECTION_H__
