// AGMXITER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMXITER_H__
#define __AGMXITER_H__

#include <e32base.h>
#include "agmfilts.h"
#include "agmiter.h"
#include "AGMXSORT.H"

// ---------------------------- Local classes ----------------------------------

class TAgnApptNonRpt1dayIterator;
class TAgnApptNonRptNdayIterator;
class TAgnApptNonRptIterator;
class TAgnEventIterator;
class TAgnRptIterator;
class TAgnApptRptIterator;
class TAgnTodoNonRptIterator;
class TAgnTodoRptIterator;
class TAgnEntryInfoFilter;
class TAgnEntryDateIterator;

// ------------------------------Referenced classes-----------------------------
class CAgnSortEntry;
class CAgnApptInfo;
class CAgnTodoInfo;
class CAgnEventInfo;
class CAgnAnnivInfo;
class CAgnSortEntryTable;
class TAgnFilter;


// ----------------------------TAgnEntryInfoFilter------------------------------
// Used to filter Entrys
//
class TAgnEntryInfoFilter : public TFilter<CAgnSortEntry*>
/**
@publishedAll
@released
*/
	{
public:
	IMPORT_C TAgnEntryInfoFilter();
	IMPORT_C TAgnEntryInfoFilter(const TAgnFilter* aFilter);
	IMPORT_C virtual ~TAgnEntryInfoFilter();
	IMPORT_C virtual TBool Compare(CAgnSortEntry* const & aElement) const;
	inline void SetFilter(const TAgnFilter* aFilter);
	const TAgnFilter* EntryFilter() const { return iFilter; }
private:
	const TAgnFilter* iFilter;
	};

inline void TAgnEntryInfoFilter::SetFilter(const TAgnFilter* aFilter)
	{ iFilter = aFilter; }

// ----------------------------TAgnApptNonRpt1dayIterator-----------------------
// Iterator - Non repeating appointments NOT spanning more than one day 
//
class TAgnApptNonRpt1dayIterator : public TAgnIterator
/**
@internalComponent
@released
*/
	{
public:	
	TAgnApptNonRpt1dayIterator(CAgnSortEntryTable* aEntryInfoTable,TAgnEntryInfoFilter* aFilter = NULL);
private:
	};

// ----------------------------TAgnApptNonRptNdayIterator-----------------------
// Iterator - Non repeating appointments spanning more than one day 
//
class TAgnApptNonRptNdayIterator : public TAgnIterator
/**
@internalComponent
@released
*/
	{
public:	
	TAgnApptNonRptNdayIterator(CAgnSortEntryTable* aEntryInfoTable,TAgnEntryInfoFilter* aFilter = NULL);
	};


// ----------------------------TAgnApptNonRptIterator---------------------------
// Compound non repeating Appt Iterator 
//
class TAgnApptNonRptIterator : public TAgnCompoundIteratorBase
/**
@internalComponent
@released
*/
	{
public:
	TAgnApptNonRptIterator(CAgnSortEntryTable* aEntryInfoTable,TAgnEntryInfoFilter* aFilter = NULL);
	virtual ~TAgnApptNonRptIterator();
private:
	TAgnIteratorBase* iArray[2];		
	TAgnApptNonRptNdayIterator iManyDayIter;
	TAgnApptNonRpt1dayIterator iDayIter;
	};

// ----------------------------TAgnEventIterator--------------------------------
// Iterator - Events
//
class TAgnEventIterator : public TAgnIterator
/**
@internalComponent
@released
*/
	{
public:	
	TAgnEventIterator(CAgnSortEntryTable* aEntryInfoTable,TAgnEntryInfoFilter* aFilter = NULL);
	};


// ----------------------------TAgnAnnivRptIterator-----------------------------
// Iterator - Repeating anniv
//
class TAgnAnnivRptIterator : public TAgnIterator
/**
@internalComponent
@released
*/
	{
public:	
	TAgnAnnivRptIterator(CAgnSortEntryTable* aEntryInfoTable,TAgnEntryInfoFilter* aFilter = NULL);
	};

// ----------------------------TAgnRptIterator----------------------------------
// Iterator - Non repeating appointments 
//
class TAgnRptIterator : public TAgnIterator
/**
@internalComponent
@released
*/
	{
public:	
	TAgnRptIterator(CAgnSortEntryTable* aEntryInfoTable,TAgnEntryInfoFilter* aFilter = NULL);
	};

// ----------------------------TAgnApptRptIterator------------------------------
// Iterator - Repeating appointments 
//
class TAgnApptRptIterator : public TAgnIterator
/**
@internalComponent
@released
*/
	{
public:	
	TAgnApptRptIterator(CAgnSortEntryTable* aEntryInfoTable,TAgnEntryInfoFilter* aFilter = NULL);
	};

// ----------------------------TAgnEventRptIterator------------------------------
// Iterator - Repeating events
//

class TAgnEventRptIterator : public TAgnIterator
/**
@internalComponent
@released
*/
	{
public:	
	TAgnEventRptIterator(CAgnSortEntryTable* aEntryInfoTable,TAgnEntryInfoFilter* aFilter = NULL);
	};


// ----------------------------TAgnTodoNonRptIterator---------------------------
// Iterator - Non repeating todos
//
class TAgnTodoNonRptIterator : public TAgnIterator
/**
@publishedAll
@released
*/
	{
public:
	IMPORT_C TAgnTodoNonRptIterator(CAgnSortEntryTable* aEntryInfoTable,TAgnDate aToday, TAgnEntryInfoFilter* aFilter = NULL);
	IMPORT_C virtual TBool AtEnd();
	IMPORT_C virtual const TAgnDate& CurrentKey() const;
protected:
	virtual TBool MovedForward(TAgnDate aTargetValue);
	virtual TBool MovedBack(TAgnDate aTargetValue);
	virtual TBool MovedTo(TAgnDate aTargetValue);
	virtual TBool MovedToLessOrEqual(TAgnDate aTargetValue);
private:
	TBool IsKeyUndated(TAgnDate aKey) const;		
	TAgnDate UndatedKey() const;
	TBool GotoLastUndatedTodo();
	TBool HasUndatedTodos();
	void RestoreSavedCursor();
	TBool GotoFirstUndatedTodo();
	TInt iSavedCursor;
	TAgnDate iToday;
	};

// ----------------------------TAgnTodoRptIterator------------------------------
// Iterator - Repeating todos
//
class TAgnTodoRptIterator : public TAgnIterator
/**
@internalComponent
@released
*/
	{
public:	
	TAgnTodoRptIterator(CAgnSortEntryTable* aEntryInfoTable,TAgnDate aToday,TAgnEntryInfoFilter* aFilter = NULL);
private:
	TAgnDate iToday;
	};


// ----------------------------TAgnEntryDateIterator----------------------------
// Compound Entry Iterator 
//
class TAgnEntryDateIterator : public TAgnCompoundIteratorBase
/**
@publishedAll
@released
*/
	{
public:
	IMPORT_C TAgnEntryDateIterator(CAgnSortEntryTable* aEntryInfoTable,TAgnDate aToday, TAgnEntryInfoFilter* aFilter = NULL);
	IMPORT_C virtual ~TAgnEntryDateIterator();
private:
	TAgnIteratorBase* iArray[8];		
	TAgnApptNonRptNdayIterator iManyDayApptIter;
	TAgnApptNonRpt1dayIterator iDayApptIter;
	TAgnApptRptIterator iRptApptIter;
	TAgnTodoNonRptIterator iTodoIter;
	TAgnTodoRptIterator iTodoRptIter;
	TAgnEventIterator iEventIter;
	TAgnEventRptIterator iEventRptIter;
	TAgnAnnivRptIterator iAnnivRptIter;
	};


#endif

// -------------------------------- EOF ----------------------------------------
