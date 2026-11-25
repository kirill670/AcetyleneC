// AGMLISTS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// --------------------------- CAgnList<InstanceItem> --------------------------
template<class InstanceItem>

/** Removes all list items from the list.*/
inline void CAgnList<InstanceItem>::Reset()
	{ iInstances->Reset(); }

template<class InstanceItem>
/**
 * Returns the current number of list instances.
 *
 * @returns   "TInt"
 *            The current number of list instances.
 */
inline TInt CAgnList<InstanceItem>::Count() const
	{ return (iInstances->Count()); }

template<class InstanceItem>
/**
 * Removes a list item from the list.
 *
 * @param     "TInt aIndex"
 *            The index of the item to be deleted. A panic occurs if
 *            the index is out of range.
 */
inline void CAgnList<InstanceItem>::Delete(TInt aIndex)
	{ 
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < iInstances->Count(),Panic(_L("Invalid index")));
	iInstances->Delete(aIndex); 
	}

template<class InstanceItem>

/**
 * Appends a list item to the end of the existing list.
 *
 * @param     "const InstanceItem& aElement"
 *            The list item to be appended.
 */
inline void CAgnList<InstanceItem>::AppendL(const InstanceItem& aElement)
	{ iInstances->AppendL(aElement); }

template<class InstanceItem>
/**
 * Inserts a list item into the list.
 *
 * @param     "TInt aIndex"
 *            The position in the list at which the item should be
 *            inserted relative to zero.
 * @param     "const InstanceItem& aElement"
 *            The item to be inserted.
 */
inline void CAgnList<InstanceItem>::InsertL(TInt aIndex,const InstanceItem& aElement)
	{ 
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < iInstances->Count(),Panic(_L("Invalid index")));
	iInstances->InsertL(aIndex,aElement);
	}

template<class InstanceItem>
/**
 * Finds the index of the first item which matches the item specified in
 * <code>aKey</code>.
 *
 * The search is sequential, starting with the first object in the array.
 *
 * @param     "const InstanceItem& aItem"
 *            Reference to the object which is used for comparison.
 * @param     "TKeyArrayFix& aKey"
 *            Reference to a key object defining the properties of
 *            the key to use in the search.
 * @param     "TInt& aPos"
 *            If the element is found, the reference is set to the
 *            position of that element within the array. The
 *            position is relative to zero, (i.e. the first element
 *            in the array is at position 0). If the element is not
 *            found and the array is not empty, then the value of
 *            the reference is set to the number of elements in the
 *            array. If the element is not found and the array is
 *            empty, then the reference is set to zero.
 * @returns   "TInt"
 *            Zero, if the element with the specified key is found,
 *            otherwise non-zero.
 */
inline TInt CAgnList<InstanceItem>::Find(const InstanceItem& aItem,TKeyArrayFix& aKey,TInt& aPos) const
	{ return (iInstances->Find(aItem,aKey,aPos)); }


template<class InstanceItem>
inline void CAgnList<InstanceItem>::ConstructL(TInt aGranularity)	
	{ iInstances=new(ELeave)CArrayFixFlat<InstanceItem>(aGranularity); }

template<class InstanceItem>
inline const InstanceItem& CAgnList<InstanceItem>::operator[](TInt aIndex) const
//
// Index into the list
//
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
/**
 * Sets the day for this list to <code>aDay</code>.
 *
 * @param     "const TTime& aDay"
 *            The day.
 */
inline void CAgnDayList<InstanceItem>::SetDay(const TTime& aDay)
	{ iDay=aDay; }

template<class InstanceItem>
/**
 * Gets the day for this list.
 *
 * @returns   "TTime"
 *            The day as a <code>TTime</code>.
 */
inline TTime CAgnDayList<InstanceItem>::Day() const
	{ return(iDay); }


template<class InstanceItem>
/**
 * Allocates and constructs a <code>CAgnDayList</code> object.
 *
 * Initialises the day to the value specified.
 *
 * @param     "const TTime& aDay"
 *            The day, as a <code>TTime</code>.
 * @returns   "CAgnDayList*"
 *            Pointer to the new list object.
 */
inline CAgnDayList<InstanceItem>* CAgnDayList<InstanceItem>::NewL(const TTime& aDay)
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

/**
 * Sets the year.
 *
 * @param     "TTimeIntervalYears aYear"
 *            The year.
 */
inline void CAgnMonthInstanceList::SetYear(TTimeIntervalYears aYear)
	{ iYear=aYear; }

/**
 * Sets the month.
 *
 * @param     "TMonth aMonth"
 *            The month.
 */
inline void CAgnMonthInstanceList::SetMonth(TMonth aMonth)
	{ iMonth=aMonth; }

/**
 * Gets the year.
 *
 * @returns   "TTimeIntervalYears"
 *            The year.
 */
inline TTimeIntervalYears CAgnMonthInstanceList::Year() const
	{ return (iYear); }

/**
 * Gets the month.
 *
 * @returns   "TMonth"
 *            The month.
 */
inline TMonth CAgnMonthInstanceList::Month() const
	{ return (iMonth); }




// -------------------------- CAgnTodoInstanceList -----------------------------------
inline CAgnTodoInstanceList::CAgnTodoInstanceList(TAgnTodoListId aTodoListId)
	: iTodoListId(aTodoListId)
	{
	}

/**
 * Sets the to-do list ID.
 *
 * @param     "TAgnTodoListId aTodoListId"
 *            The to-do list ID.
 */
inline void CAgnTodoInstanceList::SetTodoListId(TAgnTodoListId aTodoListId)
	{ iTodoListId=aTodoListId; }

/**
 * Returns the to-do list ID.
 *
 * @returns   "TAgnTodoListId"
 *            The to-do list ID.
 */
inline TAgnTodoListId CAgnTodoInstanceList::TodoListId() const
	{ return (iTodoListId); }

/**
 * Returns the sort order.
 *
 * @returns   "CAgnTodoList::TSortOrder"
 *            The sort order.
 */
inline CAgnTodoList::TSortOrder CAgnTodoInstanceList::SortOrder() const
	{ return (iSortOrder); }

/**
 * Sets the sort order for the list.
 *
 * @param     "CAgnTodoList::TSortOrder aSortOrder"
 *            The sort order for the instance list.
 */
inline void CAgnTodoInstanceList::SetSortOrder(CAgnTodoList::TSortOrder aSortOrder)
	{ iSortOrder=aSortOrder; }


/**
 * Gets the instance ID at the specified index into the list.
 *
 * @param     "TInt aIndex"
 *            The index of the instance.
 * @returns   "TAgnInstanceId&"
 *            The ID of the instance.
 */
inline const TAgnInstanceId& CAgnTodoInstanceList::Id(TInt aIndex) const
	{
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < Count(),Panic(_L("Invalid index")));
	return ((*this)[aIndex]);
	}


// ----------------------------- CAgnSymbolList -----------------------------------
/**
 * Returns the day number for the indexed list item.
 *
 * @param     "TInt aIndex"
 *            The index.
 * @returns   "TUint"
 *            The day number for the indexed list item.
 */
inline TUint CAgnSymbolList::TListItem::DayNumber() const
	{ return (iDayNumber); }

/**
 * Returns the number of symbols for the indexed day.
 *
 * @param     "TInt aIndex"
 *            The index.
 * @returns   "TUint"
 *            The number of symbols for the indexed day.
 */
inline TUint 	CAgnSymbolList::TListItem::NumSymbols() const
	{ return (iNumSymbols); }

/**
 * Tests whether there are more than two symbols for the day indicated by
 * the indexed list item.
 *
 * Note that list items can only store a maximum of two entry symbols.
 *
 * @param     "TInt aIndex"
 *            The index.
 * @returns   "TBool"
 *            <code>ETrue</code> if there are more than two symbols
 *            for the day, <code>EFalse</code> if not.
 */
inline TBool 	CAgnSymbolList::TListItem::MoreSymbols() const
	{ return (iMoreSymbols); }

/**
 * Returns the first symbol for the indexed list item.
 *
 * @param     "TInt aIndex"
 *            The index.
 * @returns   "TChar"
 *            The first symbol for the indexed list item.
 */
inline TChar CAgnSymbolList::TListItem::FirstSymbol() const
	{ return (iFirstSymbol); }

/**
 * Returns the second symbol for the indexed list item.
 *
 * @param     "TInt aIndex"
 *            The index.
 * @returns   "TChar"
 *            The second symbol for the indexed list item.
 */
inline TChar CAgnSymbolList::TListItem::SecondSymbol() const
	{ return (iSecondSymbol); }

/**
 * Returns the first symbol for the indexed list item.
 *
 * @param     "TInt aIndex"
 *            The index.
 * @returns   "TChar"
 *            The first symbol for the indexed list item.
 */
inline TRgb CAgnSymbolList::TListItem::FirstSymbolColor() const
	{ return (iFirstSymbolColor); }

/**
 * Sets the number of entry symbols for the current list item.
 *
 * @param     "TUint aNumSymbols"
 *            The number of symbols.
 */
inline void CAgnSymbolList::TListItem::SetNumSymbols(TUint aNumSymbols)
	{ iNumSymbols=(TUint8)aNumSymbols; }

/**
 * Sets a flag to indicate whether there are more than two entry symbols
 * for the current list item.
 *
 * @param     "TBool aMoreSymbols"
 *            True if there are more than two symbols, otherwise
 *            False.
 */
inline void		CAgnSymbolList::TListItem::SetMoreSymbols(TBool aMoreSymbols)
	{ iMoreSymbols=aMoreSymbols; }

/**
 * Sets the character as the first entry symbol for the current list
 * item.
 *
 * @param     "TChar aSymbol"
 *            The symbol to set.
 */
inline void		CAgnSymbolList::TListItem::SetFirstSymbol(TChar aSymbol)
	{ iFirstSymbol=aSymbol; }

/**
 * Sets the character as the second entry symbol for the current list
 * item.
 *
 * @param     "TChar aSymbol"
 *            The symbol to set.
 */
inline void 	CAgnSymbolList::TListItem::SetSecondSymbol(TChar aSymbol)
	{ iSecondSymbol=aSymbol; }

/**
 * Sets the background colour for the first entry symbol for the current
 * list item.
 *
 * NoteOnly the first entry symbol can have a background colour.
 *
 * @since     5.2
 * @returns   "TRgb"
 *            The first symbol's background colour.
 */
inline void 	CAgnSymbolList::TListItem::SetFirstSymbolColor(const TRgb& aColor)
	{ iFirstSymbolColor=aColor; }

/**
 * Gets the year.
 *
 * @returns   "TTimeIntervalYears"
 *            The year.
 */
inline TTimeIntervalYears CAgnSymbolList::Year() const
	{ return (iYear); }

/**
 * Gets the month.
 *
 * @returns   "TMonth"
 *            The month.
 */
inline TMonth CAgnSymbolList::Month() const
	{ return (iMonth); }

/**
 * Returns the number of items in the list.
 *
 * @returns   "TInt"
 *            The number of items in the list.
 */
inline TInt CAgnSymbolList::Count() const
	{ return (iSymbols->Count()); }


