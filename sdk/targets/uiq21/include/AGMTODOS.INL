// AGMTODOS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// ---------------------------- TAgnTodoDefaults ----------------------------
/**
 * Sets whether new to-do entries should be dated by default.
 *
 * @param     "TBool aIsDated"
 *            <code>ETrue</code> if new to-do entries should be
 *            dated by default, <code>EFalse</code> if not.
 */
inline void TAgnTodoDefaults::SetIsDated(TBool aIsDated)
	{ iIsDated = aIsDated; }

/**
 * Sets the default number of days warning for to-do entries.
 *
 * @param     "TTimeIntervalDays aDaysWarning"
 *            The new default number of days warning.
 */
inline void TAgnTodoDefaults::SetDaysWarning(TTimeIntervalDays aDaysWarning)
	{ 
	iDaysWarning=aDaysWarning; 
	}

/**
 * Sets the default display mode for the due date.
 *
 * @param     "CAgnTodo::TDisplayDueDateAs aDisplayAs"
 *            The new default display mode for the due date.
 */
inline void TAgnTodoDefaults::SetDisplayDueDateAs(CAgnTodo::TDisplayDueDateAs aDisplayAs)
	{ iDisplayDueDateAs = aDisplayAs; }

/**
 * Sets the default alarm settings for to-do entries.
 *
 * @param     "const TAgnAlarmDefaults& aAlarmDefaults"
 *            The new default alarm settings.
 */
inline void TAgnTodoDefaults::SetAlarmDefaults(const TAgnAlarmDefaults& aAlarmDefaults)
	{ iAlarmDefaults = aAlarmDefaults; }

/**
 * Sets the default entry symbol for to-do entries.
 *
 * The entry symbol is the character which is displayed in year views to
 * represent an entry.
 *
 * @param     "TChar aEntrySymbol"
 *            The new default entry symbol.
 */
inline void TAgnTodoDefaults::SetEntrySymbol(TChar aEntrySymbol)
	{ iEntrySymbol = aEntrySymbol; }

/**
 * Tests whether to-do entries are dated by default.
 *
 * This value is initialised to <code>EFalse</code>.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if to-do entries are dated by
 *            default, otherwise <code>EFalse</code>.
 */
inline TBool TAgnTodoDefaults::IsDated() const
	{ return(iIsDated); }

/**
 * Gets the default number of days warning for a to-do entry.
 *
 * This value is initialised to zero.
 *
 * @returns   "TTimeIntervalDays"
 *            The default number of days warning for a to-do entry.
 */
inline TTimeIntervalDays TAgnTodoDefaults::DaysWarning() const
	{ return(iDaysWarning); }

/**
 * Gets the default display mode for the due date.
 *
 * This value is initialised to <code>CAgnTodo::EAutomatic</code>.
 *
 * @returns   "CAgnTodo::TDisplayDueDateAs"
 *            The default display mode for the due date.
 */
inline CAgnTodo::TDisplayDueDateAs TAgnTodoDefaults::DisplayDueDateAs() const
	{ return(iDisplayDueDateAs); }

/**
 * Gets the default alarm settings.
 *
 * These settings are initialised to: no alarm, zero days warning, alarm
 * time = 525, sound name = Chimes.
 *
 * @returns   "TAgnAlarmDefaults&"
 *            The default alarm settings.
 */
inline const TAgnAlarmDefaults& TAgnTodoDefaults::AlarmDefaults() const
	{ return(iAlarmDefaults); }

/**
 * Gets the default entry symbol for to-do entries.
 *
 * This value is initialised to 'T'. The entry symbol is the character
 * which is displayed in year views to represent an entry.
 *
 * @returns   "TChar"
 *            The default entry symbol for to-do entries.
 */
inline TChar TAgnTodoDefaults::EntrySymbol() const
	{ return(iEntrySymbol); }

/**
 * Sets the default replication status for to-do entries.
 *
 * Replication status is used to define access rights to agenda
 * information; public, private or confidential.
 *
 * @param     "TAgnReplicationData::TStatus aStatus"
 *            The new default replication status for to-do entries.
 */
inline void TAgnTodoDefaults::SetReplicationStatus(TAgnReplicationData::TStatus aStatus)
	{ 
	__ASSERT_DEBUG(aStatus == TAgnReplicationData::EOpen || aStatus == TAgnReplicationData::EPrivate ||
					aStatus == TAgnReplicationData::ERestricted,Panic(_L("Invalid emun value")));
	iReplicationStatus = aStatus; 
	}

/**
 * Gets the default replication status for to-do entries.
 *
 * This value is initialised to <code>TAgnReplicationData::EOpen</code>.
 * Replication status is used to define access rights to agenda
 * information; public, private or confidential.
 *
 * @returns   "TAgnReplicationData::TStatus"
 *            The default replication status for to-do entries.
 */
inline TAgnReplicationData::TStatus TAgnTodoDefaults::ReplicationStatus() const
	{ return (iReplicationStatus); }

/**
 * Tests whether the default to-do entry settings include an entry
 * symbol.
 *
 * This value is initialised to <code>EFalse</code>.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the default to-do entry settings
 *            include an entry symbol, otherwise
 *            <code>EFalse</code>.
 */
inline TBool TAgnTodoDefaults::HasEntrySymbol() const
	{ return (iHasEntrySymbol); }

/**
 * Sets whether new to-do entries should have an entry symbol by default.
 *
 * @param     "TBool aSetting"
 *            <code>ETrue</code> if new to-do entries should have an
 *            entry symbol by default. <code>EFalse</code> if not.
 */
inline void TAgnTodoDefaults::SetHasEntrySymbol(TBool aSetting)
	{ iHasEntrySymbol = aSetting; }

/**
 * Sets the background colour.
 *
 * This is the default background colour assigned to entry symbols for
 * to-do entries.
 *
 * @since     5.2
 * @param     "const TRgb& aColor"
 *            The default background colour for entry symbols.
 */
inline void TAgnTodoDefaults::SetBackgroundColor(const TRgb& aColor)
	{ iBackgroundColor = aColor; }

/**
 * Gets the background colour.
 *
 * This is the default background colour assigned to entry symbols for
 * to-do entries. This value is initialised to <code>KRgbBlack</code>.
 *
 * @since     5.2
 * @returns   "TRgb"
 *            The background colour for entry symbols.
 */
inline TRgb TAgnTodoDefaults::BackgroundColor() const
	{ return (iBackgroundColor); }

// ----------------------------------- TAgnTodoDisplaySettings ------------------------------
inline TAgnTodoDisplaySettings::TAgnTodoDisplaySettings()
	: iSettings(0) 
	{}

inline TBool TAgnTodoDisplaySettings::DisplayEntries() const
	{ return (iSettings & EDisplayInOtherViewsMask); }

inline TBool TAgnTodoDisplaySettings::DisplayCrossedOutEntries() const
	{ return (iSettings & EDisplayCrossedOutMask); } 

inline TTimeIntervalMinutes TAgnTodoDisplaySettings::DefaultDisplayTime() const
	{ return (iSettings & ETimeMask); }

inline void TAgnTodoDisplaySettings::ClearAllSettings()
	{ iSettings = 0; }

inline TBool TAgnTodoDisplaySettings::operator==(const TAgnTodoDisplaySettings& aOther) const
	{ return (iSettings == aOther.iSettings); }



// --------------------------------- CAgnTodoListList ---------------------------
/**
 * Inserts a list ID into the list of IDs.
 *
 * @param     "TInt aPosition"
 *            The index of the insertion point.
 * @param     "const TListItem* aItem"
 *            A pointer to the ID to be inserted.
 */
inline void CAgnTodoListList::InsertL(TInt aPosition,const TListItem* aItem)
	{ iTodoLists->InsertL(aPosition,*aItem); }

/**
 * Appends a list ID to the end of the list of IDs.
 *
 * @param     "const TListItem* aItem"
 *            A pointer to the ID.
 */
inline void CAgnTodoListList::AppendL(const TListItem* aItem)
	{ iTodoLists->AppendL(*aItem); }

/**
 * Returns the count of to-do lists.
 *
 * @returns   "TInt"
 *            The number of to-do lists.
 */
inline TInt CAgnTodoListList::Count() const
	{ return (iTodoLists->Count()); }

/**
 * Deletes a list ID from the list of IDs.
 *
 * @param     "TAgnTodoListId aTodoListId"
 *            The ID of the list to be deleted.
 */
inline void CAgnTodoListList::Delete(TInt aPosition)
	{
	__ASSERT_DEBUG(aPosition >=0 && aPosition < Count(),Panic(_L("TodoListListIndexOutOfRange")));
	iTodoLists->Delete(aPosition);
	}



// ------------------------ CAgnDeletedTodoListList ---------------------------------------
inline TInt CAgnDeletedTodoListList::Count() const
	{ return (iTodoListIds->Count()); }

inline void CAgnDeletedTodoListList::AppendL(const TAgnTodoListId* aItem)
	{ iTodoListIds->AppendL(*aItem); }

inline void CAgnDeletedTodoListList::Delete(TInt aPosition)
	{
	__ASSERT_DEBUG(aPosition >=0 && aPosition < Count(),Panic(_L("DeletedTodoListListIndexOutOfRange")));
	iTodoListIds->Delete(aPosition);
	}

inline TAgnTodoListId CAgnDeletedTodoListList::TodoListId(TInt aIndex) const	
	{
	__ASSERT_DEBUG(aIndex >=0 && aIndex < Count(),Panic(_L("DeletedTodoListListIndexOutOfRange")));
	return (((*iTodoListIds)[aIndex]));
	}



// --------------------------- CAgnTodoList ------------------------------
/**
 * Gets the name of the to-do list, as set by <code>SetName()</code>.
 *
 * @returns   "TPtrC"
 *            The name of the to-do list.
 */
inline TPtrC CAgnTodoList::Name() const
	{ return (iName); };

/**
 * Gets the sort order of the to-do entries in the to-do list as it is
 * displayed in the to-do view.
 *
 * Also updates the last changed date/time. The sort order is set by
 * <code>SetSortOrder()</code>.
 *
 * @returns   "TSortOrder"
 *            How the to-do entries are to be sorted in the to-do
 *            view: <code>EManual</code>, <code>EByDate</code> or
 *            <code>EByPriority</code>.
 */
inline CAgnTodoList::TSortOrder CAgnTodoList::SortOrder() const
	{ return (iSortOrder); }

/**
 * Tests whether crossed out to-do entries should be displayed in the
 * to-do view as set by <code>SetDisplayCrossedOutEntries()</code>.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if crossed out to-do entries should
 *            be displayed in the to-do view, <code>EFalse</code> if
 *            not.
 */
inline TBool CAgnTodoList::DisplayCrossedOutEntries() const
	{ return (iDisplayCrossedOutEntries); }

/**
 * Tests whether crossed out to-do entries should be displayed in views
 * other than the to-do view as set by
 * <code>SetDisplayCrossedOutEntriesInOtherViews()</code>.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if crossed out to-do entries should
 *            be displayed in views other than the to-do view,
 *            <code>EFalse</code> if not.
 */
inline TBool CAgnTodoList::DisplayCrossedOutEntriesInOtherViews() const
	{ return (iHowTodosAreDisplayedInViewsOtherThanTheTodoView.DisplayCrossedOutEntries()); }

/**
 * Returns the default display time for to-do entries which belong to
 * this to-do list in views other than the to-do view.
 *
 * This value is a number of minutes since midnight and is set by
 * <code>SetDefaultDisplayTimeInOtherViews()</code>.
 *
 * @returns   "TTimeIntervalMinutes"
 *            The default display time setting, in number of minutes
 *            since midnight, for to-do entries in views other than
 *            the to-do view.
 */
inline TTimeIntervalMinutes CAgnTodoList::DefaultDisplayTimeInOtherViews() const
	{ return (iHowTodosAreDisplayedInViewsOtherThanTheTodoView.DefaultDisplayTime()); }

/**
 * Returns whether to-do entries should be displayed in views other than
 * the to-do view.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if to-do entries should be
 *            displayed in views other than the to-do view,
 *            <code>EFalse</code> if not.
 */
inline TBool CAgnTodoList::DisplayEntriesInOtherViews() const
	{ return (iHowTodosAreDisplayedInViewsOtherThanTheTodoView.DisplayEntries()); }

/**
 * Gets the number of to-do entries in the list.
 *
 * @returns   "TInt"
 *            The number of to-do entries in the list.
 */
inline TInt CAgnTodoList::Count() const
	{ return (iTodos->Count()); }

/**
 * Gets the to-do list ID.
 *
 * @returns   "TAgnTodoListId"
 *            The to-do list ID.
 */
inline  TAgnTodoListId CAgnTodoList::Id() const
	{ return (iId);}

void CAgnTodoList::InsertL(TInt aPosition,TAgnEntryId aItem)
	{ iTodos->InsertL(aPosition,aItem); }

inline void CAgnTodoList::AppendL(TAgnEntryId aItem)
	{ iTodos->AppendL(aItem); }

inline void CAgnTodoList::Delete(TInt aPos)
	{ 
	__ASSERT_DEBUG(aPos >=0 && aPos < Count(),Panic(_L("Todo list item out of range")));
	iTodos->Delete(aPos);
	}
	
inline const TAgnEntryId& CAgnTodoList::At(TInt aIndex) 
	{
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < Count(),Panic(_L("TodoListIndexOutOfRange")));
	return ((*iTodos)[aIndex]);
	}

inline TAgnEntryId& CAgnTodoList::operator[](TInt aIndex) const
	{
	__ASSERT_DEBUG(aIndex >= 0 && aIndex < Count(),Panic(_L("TodoListIndexOutOfRange")));
	return ((*iTodos)[aIndex]);
	}

inline void CAgnTodoList::Reset()
	{ iTodos->Reset(); }

inline void CAgnTodoList::SetId(TAgnTodoListId aId)
	{ iId=aId; }

/**
 * Returns the default settings given to a new to-do entry.
 *
 * @returns   "TAgnTodoDefaults&"
 *            Reference to the default settings (including alarm
 *            defaults) given to a new to-do entry.
 */	
inline const TAgnTodoDefaults& CAgnTodoList::TodoDefaults() const
	{ return (iTodoDefaults); }

/**
 * Returns the settings that control how to-do entries are displayed in
 * views other than the to-do view.
 *
 * Note that all of these settings can also be retrieved using other
 * member functions of <code>CAgnTodoList</code>.
 *
 * @returns   "TAgnTodoDisplaySettings&"
 *            Reference to the settings that show how to-do entries
 *            are displayed in views other than the to-do view.
 */
inline const TAgnTodoDisplaySettings& CAgnTodoList::TodoDisplaySettings() const
	{ return (iHowTodosAreDisplayedInViewsOtherThanTheTodoView); }

/**
 * Sets the settings that control how to-do entries are displayed in
 * views other than the to-do view.
 *
 * Note that all of these settings can also be set using other member
 * functions of <code>CAgnTodoList</code>.
 *
 * @param     "const TAgnTodoDisplaySettings& aSettings"
 *            Const reference to the settings that show how to-do
 *            entries are displayed in views other than the to-do
 *            view.
 */
inline void CAgnTodoList::SetTodoDisplaySettings(const TAgnTodoDisplaySettings& aSettings)
	{ iHowTodosAreDisplayedInViewsOtherThanTheTodoView = aSettings; }

inline const TAgnReplicationData& CAgnTodoList::ReplicationData() const
	{ return (iReplicationData); }

inline TAgnReplicationData& CAgnTodoList::ReplicationData()
	{ return (iReplicationData); }

inline void CAgnTodoList::SetReplicationData(const TAgnReplicationData& aReplicationData)
	{ iReplicationData = aReplicationData; }

inline void CAgnTodoList::SetUniqueId(TAgnUniqueId aUId)
	{ iUniqueId = aUId; }

inline TAgnUniqueId CAgnTodoList::UniqueId() const
	{ return (iUniqueId); }



// ----------------------------- CAgnTodoListNames ------------------------------------------
inline CAgnTodoListNames::CAgnTodoListNames()
	{
	}

/** Deletes the list of names and frees the allocated memory.*/
inline void CAgnTodoListNames::Reset()
	{ iTodoNameList->Reset(); }

/**
 * Gets the number of names in the name list.
 *
 * @returns   "TInt"
 *            The number of names.
 */
inline TInt CAgnTodoListNames::Count() const
	{ return (iTodoNameList->Count()); }

/**
 * Appends a name to the end of the name list.
 *
 * @param     "const TListItem& aItem"
 *            The name to append.
 */
inline void CAgnTodoListNames::AppendL(const TListItem& aItem)
	{ iTodoNameList->AppendL(aItem); }

/**
 * Inserts an item into the list of names at the indexed position.
 *
 * @param     "TInt aPosition"
 *            The index for the item in the list.
 * @param     "const TListItem& aItem"
 *            The item to insert.
 */
inline void CAgnTodoListNames::InsertL(TInt aPosition,const TListItem& aItem)
	{  iTodoNameList->InsertL(aPosition,aItem); }
	

/**
 * Returns the to-do list name.
 *
 * @returns   "TDesC&"
 *            The name of the to-do list.
 */
inline const TDesC& CAgnTodoListNames::TListItem::Name() const
	{ return (iName); }

/**
 * Sets the name of the list item.
 *
 * @param     "const TDesC& aName"
 *            The name.
 */
inline void CAgnTodoListNames::TListItem::SetName(const TDesC& aName)
	{ iName=aName; }

/**
 * Gets the to-do list ID.
 *
 * @returns   "TAgnTodoListId"
 *            The list ID.
 */
inline TAgnTodoListId CAgnTodoListNames::TListItem::TodoListId() const
	{ return (iTodoListId); }

/**
 * Sets the to-do list ID.
 *
 * @param     "TAgnTodoListId aTodoListId"
 *            The ID.
 */
inline void CAgnTodoListNames::TListItem::SetTodoListId(TAgnTodoListId aTodoListId)
	{ iTodoListId=aTodoListId; }

/**
 * Gets the sort order of the list.
 *
 * @returns   "CAgnTodoList::TSortOrder"
 *            The sort order.
 */
inline CAgnTodoList::TSortOrder CAgnTodoListNames::TListItem::SortOrder() const
	{ return (iSortOrder); }

/**
 * Sets the sort order for the list.
 *
 * @param     "CAgnTodoList::TSortOrder aSortOrder"
 *            The sort order.
 */
inline void CAgnTodoListNames::TListItem::SetSortOrder(CAgnTodoList::TSortOrder aSortOrder)
	{ iSortOrder = aSortOrder; }








