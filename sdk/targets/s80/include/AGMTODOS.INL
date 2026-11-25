// AGMTODOS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// ---------------------------- TAgnTodoDefaults ----------------------------
inline void TAgnTodoDefaults::SetIsDated(TBool aIsDated)
/** Sets whether new to-do entries should be dated by default.

@param aIsDated ETrue if new to-do entries should be dated by default, EFalse 
if not. */
	{ iIsDated = aIsDated; }

inline void TAgnTodoDefaults::SetDaysWarning(TTimeIntervalDays aDaysWarning)
/** Sets the default number of days warning for to-do entries.

@param aDaysWarning The new default number of days warning. */
	{ 
	iDaysWarning=aDaysWarning; 
	}

inline void TAgnTodoDefaults::SetDisplayDueDateAs(CAgnTodo::TDisplayDueDateAs aDisplayAs)
/** Sets the default display mode for the due date.

@param aDisplayAs The new default display mode for the due date. */
	{ iDisplayDueDateAs = aDisplayAs; }

inline void TAgnTodoDefaults::SetAlarmDefaults(const TAgnAlarmDefaults& aAlarmDefaults)
/** Sets the default alarm settings for to-do entries.

@param aAlarmDefaults The new default alarm settings. */
	{ iAlarmDefaults = aAlarmDefaults; }

inline void TAgnTodoDefaults::SetEntrySymbol(TChar aEntrySymbol)
/** Sets the default entry symbol for to-do entries. 

The entry symbol is the character which is used to represent an entry in some views, 
for instance the year view.

@param aEntrySymbol The new default entry symbol. */
	{ iEntrySymbol = aEntrySymbol; }

inline TBool TAgnTodoDefaults::IsDated() const
/** Tests whether to-do entries are dated by default. 

This value is initialised to EFalse on construction.

@return ETrue if to-do entries are dated by default, otherwise EFalse. */
	{ return(iIsDated); }

inline TTimeIntervalDays TAgnTodoDefaults::DaysWarning() const
/** Gets the default number of days warning for a to-do entry. 

This value is initialised to zero on construction.

@return The default number of days warning for a to-do entry. */
	{ return(iDaysWarning); }

inline CAgnTodo::TDisplayDueDateAs TAgnTodoDefaults::DisplayDueDateAs() const
/** Gets the default display mode for the due date. 

This value is initialised to CAgnTodo::EAutomatic on construction.

@return The default display mode for the due date. */
	{ return(iDisplayDueDateAs); }

inline const TAgnAlarmDefaults& TAgnTodoDefaults::AlarmDefaults() const
/** Gets the default alarm settings. 

These settings are initialised on construction to: no alarm, 
zero days warning, alarm time = 525, sound name = Chimes.

@return The default alarm settings. */
	{ return(iAlarmDefaults); }

inline TChar TAgnTodoDefaults::EntrySymbol() const
/** Gets the default entry symbol for to-do entries. 

This value is initialised on construction to 'T'. The entry symbol is the 
character which is used to represent an entry in some views, for instance 
the year view.

@return The default entry symbol for to-do entries. */
	{ return(iEntrySymbol); }

inline void TAgnTodoDefaults::SetReplicationStatus(TAgnReplicationData::TStatus aStatus)
/** Sets the default replication status for to-do entries. 

Replication status is used to define access rights to agenda information: public, 
private or confidential.

@param aStatus The new default replication status for to-do entries. */
	{ 
	__ASSERT_DEBUG(aStatus == TAgnReplicationData::EOpen || aStatus == TAgnReplicationData::EPrivate ||
					aStatus == TAgnReplicationData::ERestricted,Panic(_L("Invalid emun value")));
	iReplicationStatus = aStatus; 
	}

inline TAgnReplicationData::TStatus TAgnTodoDefaults::ReplicationStatus() const
/** Gets the default replication status for to-do entries. 

This value is initialised on construction to TAgnReplicationData::EOpen. 
Replication status is used to define access rights to agenda information; 
public, private or confidential.

@return The default replication status for to-do entries. */
	{ return (iReplicationStatus); }

inline TBool TAgnTodoDefaults::HasEntrySymbol() const
/** Tests whether the default to-do entry settings include an entry symbol. 

This value is initialised on construction to EFalse.

@return ETrue if the default to-do entry settings include an entry symbol, 
otherwise EFalse. */
	{ return (iHasEntrySymbol); }

inline void TAgnTodoDefaults::SetHasEntrySymbol(TBool aSetting)
/** Sets whether new to-do entries should have an entry symbol by default.

@param aSetting ETrue if new to-do entries should have an entry symbol by 
default. EFalse if not. */
	{ iHasEntrySymbol = aSetting; }

inline void TAgnTodoDefaults::SetBackgroundColor(const TRgb& aColor)
/** Sets the background colour. 

This is the default background colour assigned to entry symbols for to-do entries.

@param aColor The default background colour for entry symbols. */
	{ iBackgroundColor = aColor; }

inline TRgb TAgnTodoDefaults::BackgroundColor() const
/** Gets the background colour. 

This is the default background colour assigned to entry symbols for 
to-do entries. This value is initialised on construction to KRgbBlack. 

@return The background colour for entry symbols. */
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
inline void CAgnTodoListList::InsertL(TInt aPosition,const TListItem* aItem)
/** Inserts a to-do list ID into the list of IDs.

@param aPosition The index of the insertion point.
@param aItem A pointer to the ID to be inserted. */
	{ iTodoLists->InsertL(aPosition,*aItem); }

inline void CAgnTodoListList::AppendL(const TListItem* aItem)
/** Appends a to-do list ID to the list of IDs.

@param aItem A pointer to the ID. */
	{ iTodoLists->AppendL(*aItem); }

inline TInt CAgnTodoListList::Count() const
/** Gets the count of to-do lists in the list.

@return The number of to-do lists. */
	{ return (iTodoLists->Count()); }

inline void CAgnTodoListList::Delete(TInt aPosition)
/** Deletes a list ID from the list of IDs.

@param aPosition The index of the list ID to be deleted. */
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
inline TPtrC CAgnTodoList::Name() const
/** Gets the name of the to-do list, as set by SetName().

@return The name of the to-do list. */
	{ return (iName); };

inline CAgnTodoList::TSortOrder CAgnTodoList::SortOrder() const
/** Gets the sort order of the entries in the to-do list, as used 
in the to-do view. 

The sort order is set by SetSortOrder().

@return How the to-do entries are sorted in the to-do view: EManual, 
EByDate or EByPriority. */
	{ return (iSortOrder); }

inline TBool CAgnTodoList::DisplayCrossedOutEntries() const
/** Tests whether crossed out to-do entries should be displayed in the to-do view, 
as set by SetDisplayCrossedOutEntries().

@return ETrue if crossed out to-do entries should be displayed in the to-do 
view, EFalse if not. */
	{ return (iDisplayCrossedOutEntries); }

inline TBool CAgnTodoList::DisplayCrossedOutEntriesInOtherViews() const
/** Tests whether crossed out to-do entries should be displayed in views other 
than the to-do view, as set by SetDisplayCrossedOutEntriesInOtherViews().

@return ETrue if crossed out to-do entries should be displayed in views other 
than the to-do view, EFalse if not. */
	{ return (iHowTodosAreDisplayedInViewsOtherThanTheTodoView.DisplayCrossedOutEntries()); }

inline TTimeIntervalMinutes CAgnTodoList::DefaultDisplayTimeInOtherViews() const
/** Gets the default display time for to-do entries which belong to this to-do 
list, in views other than the to-do view. 

This is a number of minutes since midnight and is set using 
SetDefaultDisplayTimeInOtherViews().

@return The default display time setting, in number of minutes since midnight, 
for to-do entries in views other than the to-do view. */
	{ return (iHowTodosAreDisplayedInViewsOtherThanTheTodoView.DefaultDisplayTime()); }

inline TBool CAgnTodoList::DisplayEntriesInOtherViews() const
/** Tests whether to-do entries should be displayed in views other than the to-do 
view.

@return ETrue if to-do entries should be displayed in views other than the 
to-do view, EFalse if not. */
	{ return (iHowTodosAreDisplayedInViewsOtherThanTheTodoView.DisplayEntries()); }

inline TInt CAgnTodoList::Count() const
/** Gets the number of entries in the list.

@return The number of entries in the list. */
	{ return (iTodos->Count()); }

inline  TAgnTodoListId CAgnTodoList::Id() const
/** Gets the to-do list ID.

@return The to-do list ID. */
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

inline const TAgnTodoDefaults& CAgnTodoList::TodoDefaults() const
/** Gets the default settings given to a new to-do entry.

@return Reference to the default settings (including alarm defaults) given 
to a new to-do entry. */
	{ return (iTodoDefaults); }

inline const TAgnTodoDisplaySettings& CAgnTodoList::TodoDisplaySettings() const
/** Gets the settings that control how to-do entries are displayed in views 
other than the to-do view. 

@return Reference to the settings that show how to-do entries are displayed 
in views other than the to-do view. */
	{ return (iHowTodosAreDisplayedInViewsOtherThanTheTodoView); }

inline void CAgnTodoList::SetTodoDisplaySettings(const TAgnTodoDisplaySettings& aSettings)
/** Sets how to-do entries are displayed in views other than the to-do view. 

@param aSettings The settings that control how to-do entries are displayed in 
views other than the to-do view. */
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

inline void CAgnTodoListNames::Reset()
/** Deletes the list of names and frees the allocated memory. */
	{ iTodoNameList->Reset(); }

inline TInt CAgnTodoListNames::Count() const
/** Gets the number of names in the name list.

@return The number of names. */
	{ return (iTodoNameList->Count()); }

inline void CAgnTodoListNames::AppendL(const TListItem& aItem)
/** Appends a name to the end of the name list.

@param aItem The name to append. */
	{ iTodoNameList->AppendL(aItem); }

inline void CAgnTodoListNames::InsertL(TInt aPosition,const TListItem& aItem)
/** Inserts an item into the list of names at the indexed position.

@param aPosition The index for the item in the list.
@param aItem The item to insert. */
	{  iTodoNameList->InsertL(aPosition,aItem); }
	

inline const TDesC& CAgnTodoListNames::TListItem::Name() const
/** Gets the list item's name.

@return The name of the to-do list. */
	{ return (iName); }

inline void CAgnTodoListNames::TListItem::SetName(const TDesC& aName)
/** Sets the name of the list item.
	
@param aName The name. */
	{ iName=aName; }

inline TAgnTodoListId CAgnTodoListNames::TListItem::TodoListId() const
/** Gets the list item's ID.

@return The list item's ID. */
	{ return (iTodoListId); }

inline void CAgnTodoListNames::TListItem::SetTodoListId(TAgnTodoListId aTodoListId)
/** Sets the list item's ID.

@param aTodoListId The ID. */
	{ iTodoListId=aTodoListId; }

inline CAgnTodoList::TSortOrder CAgnTodoListNames::TListItem::SortOrder() const
/** Gets the list item's sort order.

@return The sort order. */
	{ return (iSortOrder); }

inline void CAgnTodoListNames::TListItem::SetSortOrder(CAgnTodoList::TSortOrder aSortOrder)
/** Sets the list item's sort order.

@param aSortOrder The sort order. */
	{ iSortOrder = aSortOrder; }








