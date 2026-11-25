// AGMLISTS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// --------------------------- CAgnList<InstanceItem> --------------------------
template<class InstanceItem>
inline void CAgnList<InstanceItem>::Reset()
/** Removes all items from the list. */
	{ iInstances->Reset(); }

template<class InstanceItem>
inline TInt CAgnList<InstanceItem>::Count() const
/** Gets the number of list items.

@return The number of list items. */
	{ return (iInstances->Count()); }

template<class InstanceItem>
inline void CAgnList<InstanceItem>::Delete(TInt aIndex)
/** Removes an item from the list.

@param aIndex The index of the item to be deleted. A panic occurs if the index 
is out of range. */
	{ 
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < iInstances->Count(),Panic(_L("Invalid index")));
	iInstances->Delete(aIndex); 
	}

template<class InstanceItem>
inline void CAgnList<InstanceItem>::AppendL(const InstanceItem& aElement)
/** Appends an item to the list.

@param aElement The list item to be appended. */
	{ iInstances->AppendL(aElement); }

template<class InstanceItem>
inline void CAgnList<InstanceItem>::InsertL(TInt aIndex,const InstanceItem& aElement)
/** Inserts an item into the list.

@param aIndex The index in the list at which the item should be inserted.
@param aElement The item to be inserted. */
	{ 
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < iInstances->Count(),Panic(_L("Invalid index")));
	iInstances->InsertL(aIndex,aElement);
	}

template<class InstanceItem>
inline TInt CAgnList<InstanceItem>::Find(const InstanceItem& aItem,TKeyArrayFix& aKey,TInt& aPos) const
/** Finds the index of the first item which matches the item specified. 

The search is sequential, starting with the first object in the array.

@param aItem Reference to the object which is used for comparison.
@param aKey Reference to a key object defining the properties of the key to 
use in the search.
@param aPos If the element is found, this is set to the position of 
the element in the array. The position is relative to zero. If the element 
is not found and the array is not empty, then this is set to the number of 
elements in the array. If the element is not found and the array is empty, 
then this is set to zero.
@return Zero, if the element with the specified key is found, otherwise non-zero. */
	{ return (iInstances->Find(aItem,aKey,aPos)); }


template<class InstanceItem>
inline void CAgnList<InstanceItem>::ConstructL(TInt aGranularity)	
	{ iInstances=new(ELeave)CArrayFixFlat<InstanceItem>(aGranularity); }

template<class InstanceItem>
inline const InstanceItem& CAgnList<InstanceItem>::operator[](TInt aIndex) const
/** Gets an item from the list.

@param aIndex The index of the required item in the list.
@return A reference to the item at position aIndex. */
	{ 
	__ASSERT_DEBUG(aIndex < Count(),Panic(_L("Instance List Index Out Of Range")));
	return ((*iInstances)[aIndex]);
	}


template<class InstanceItem>
CAgnList<InstanceItem>::~CAgnList()
//
// Destructor
//
	{
	
	delete iInstances;
	}

// --------------------------- CAgnDayList<InstanceItem> -----------------------
template<class InstanceItem>
inline CAgnDayList<InstanceItem>::CAgnDayList(const TTime& aDay)
	: iDay(aDay)
	{
	}

template<class InstanceItem>
inline void CAgnDayList<InstanceItem>::SetDay(const TTime& aDay)
/** Sets the day for this list.

@param aDay The day. */
	{ iDay=aDay; }

template<class InstanceItem>
inline TTime CAgnDayList<InstanceItem>::Day() const
/** Gets the day for this list.

@return The day as a TTime. */
	{ return(iDay); }


template<class InstanceItem>
inline CAgnDayList<InstanceItem>* CAgnDayList<InstanceItem>::NewL(const TTime& aDay)
/** Allocates and constructs a CAgnDayList. 

Initialises the day to the value specified.

@param aDay The day, as a TTime.
@return Pointer to the new list object. */
	{

	CAgnDayList* Self=new(ELeave)CAgnDayList(aDay);
	CleanupStack::PushL(Self);
	Self->ConstructL(EGranularity);
	CleanupStack::Pop();
	return (Self);
	}

// ------------------------------- CAgnDayDateTimeInstanceList --------------------
inline CAgnDayDateTimeInstanceList::CAgnDayDateTimeInstanceList(const TTime& aDay)
	:CAgnDayList<TAgnInstanceDateTimeId>(aDay)
	{
	}

// -------------------------- CAgnMonthInstanceList ------------------------------------
inline CAgnMonthInstanceList::CAgnMonthInstanceList(TTimeIntervalYears aYear,TMonth aMonth)
	: iYear(aYear),iMonth(aMonth)
	{
	}

inline void CAgnMonthInstanceList::SetYear(TTimeIntervalYears aYear)
/** Sets the year.

@param aYear The year. */
	{ iYear=aYear; }

inline void CAgnMonthInstanceList::SetMonth(TMonth aMonth)
/** Sets the month.

@param aMonth The month. */
	{ iMonth=aMonth; }

inline TTimeIntervalYears CAgnMonthInstanceList::Year() const
/** Gets the year.

@return The year. */
	{ return (iYear); }

inline TMonth CAgnMonthInstanceList::Month() const
/** Gets the month.

@return The month. */
	{ return (iMonth); }




// -------------------------- CAgnTodoInstanceList -----------------------------------
inline CAgnTodoInstanceList::CAgnTodoInstanceList(TAgnTodoListId aTodoListId)
	: iTodoListId(aTodoListId)
	{
	}

inline void CAgnTodoInstanceList::SetTodoListId(TAgnTodoListId aTodoListId)
/** Sets the to-do list ID.

@param aTodoListId The to-do list ID. */
	{ iTodoListId=aTodoListId; }

inline TAgnTodoListId CAgnTodoInstanceList::TodoListId() const
/** Gets the to-do list ID.

@return The to-do list ID. */
	{ return (iTodoListId); }

inline CAgnTodoList::TSortOrder CAgnTodoInstanceList::SortOrder() const
/** Gets the sort order.

@return The sort order. */
	{ return (iSortOrder); }

inline void CAgnTodoInstanceList::SetSortOrder(CAgnTodoList::TSortOrder aSortOrder)
/** Sets the sort order.

@param aSortOrder The sort order. */
	{ iSortOrder=aSortOrder; }


inline const TAgnInstanceId& CAgnTodoInstanceList::Id(TInt aIndex) const
/** Gets the instance ID at the specified index into the list.

@param aIndex The index of the instance.
@return The ID of the instance. */
	{
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < Count(),Panic(_L("Invalid index")));
	return ((*this)[aIndex]);
	}


// ----------------------------- CAgnSymbolList -----------------------------------
inline TUint CAgnSymbolList::TListItem::DayNumber() const
/** Gets the day number of the current list item.

@return The day number. */
	{ return (iDayNumber); }

inline TUint 	CAgnSymbolList::TListItem::NumSymbols() const
/** Gets the number of symbols for the current list item.

@return The number of symbols. */
	{ return (iNumSymbols); }

inline TBool 	CAgnSymbolList::TListItem::MoreSymbols() const
/** Tests whether there are more than two entry symbols for the day of the current 
list item (list items can store a maximum of two entry symbols, but there 
may be more than two entry symbols on that day).

@return True if there are more than two symbols, otherwise False. */
	{ return (iMoreSymbols); }

inline TChar CAgnSymbolList::TListItem::FirstSymbol() const
/** Gets the first entry symbol for the current list item.

@return The first symbol. */
	{ return (iFirstSymbol); }

inline TChar CAgnSymbolList::TListItem::SecondSymbol() const
/** Gets the second entry symbol for the current list item.

@return The second symbol. */
	{ return (iSecondSymbol); }

inline TRgb CAgnSymbolList::TListItem::FirstSymbolColor() const
/** Get the background colour for the first symbol in the current list item, as 
set by SetFirstSymbolColor().

@return The first entry symbol's background colour. */
	{ return (iFirstSymbolColor); }

inline void CAgnSymbolList::TListItem::SetNumSymbols(TUint aNumSymbols)
/** Sets the number of entry symbols for the current list item.

@param aNumSymbols The number of symbols. */
	{ iNumSymbols=(TUint8)aNumSymbols; }

inline void		CAgnSymbolList::TListItem::SetMoreSymbols(TBool aMoreSymbols)
/** Sets a flag to indicate whether there are more than two entry symbols for the 
current list item.

@param aMoreSymbols True if there are more than two symbols, otherwise false. */
	{ iMoreSymbols=aMoreSymbols; }

inline void		CAgnSymbolList::TListItem::SetFirstSymbol(TChar aSymbol)
/** Sets the specified character as the first entry symbol for the current list item.

@param aSymbol The symbol to set. */
	{ iFirstSymbol=aSymbol; }

inline void 	CAgnSymbolList::TListItem::SetSecondSymbol(TChar aSymbol)
/** Sets the specified character as the second entry symbol for the current list item.

@param aSymbol The symbol to set. */
	{ iSecondSymbol=aSymbol; }

inline void 	CAgnSymbolList::TListItem::SetFirstSymbolColor(const TRgb& aColor)
/** Sets the background colour for the first entry symbol for the current
list item.

Note: only the first entry symbol can have a background colour.

@return The first symbol's background colour. */
	{ iFirstSymbolColor=aColor; }

inline TTimeIntervalYears CAgnSymbolList::Year() const
/** Gets the year.

@return The year. */
	{ return (iYear); }

inline TMonth CAgnSymbolList::Month() const
/** Gets the month.

@return The month. */
	{ return (iMonth); }

inline TInt CAgnSymbolList::Count() const
/** Gets the number of items in the list.

@return The number of items in the list. */
	{ return (iSymbols->Count()); }


