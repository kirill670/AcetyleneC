// AGMCOMON.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// --------------------------------------------------------------------
// -------------------------- TAgnLiteEntry ---------------------------
// --------------------------------------------------------------------
inline TAgnLiteEntry::TAgnLiteEntry(CAgnSortEntry* aSortEntry)
	: iEntry(aSortEntry)
	{}

/**
 * Gets the entry type.
 *
 * @returns   "CAgnEntry::TType"
 *            The type of agenda entry.
 */
inline CAgnEntry::TType TAgnLiteEntry::Type() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->Type());
	}

/**
 * Gets the entry ID.
 *
 * @returns   "TAgnEntryId"
 *            The entry ID.
 */
inline TAgnEntryId TAgnLiteEntry::Id() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->Id());
	}

/**
 * Gets the entry symbol.
 *
 * @returns   "TChar"
 *            The entry symbol.
 */
inline TChar TAgnLiteEntry::EntrySymbol() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	__ASSERT_DEBUG(HasEntrySymbol(),Panic(_L("Doesn't have an entry symbol")));
	return (iEntry->EntrySymbol());
	}


/**
 * Gets the display time.
 *
 * The display time is the time at which the entry is displayed in dated
 * views, as a number of minutes from midnight.
 *
 * @returns   "TTimeIntervalMinutes"
 *            The display time.
 */
inline TTimeIntervalMinutes TAgnLiteEntry::DisplayTime() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->DisplayTime());
	}

/**
 * Gets a pointer to the entrys repeat details, including exceptions.
 *
 * @returns   "CAgnRptDef*"
 *            The entry's repeat details.
 */
inline const CAgnRptDef* TAgnLiteEntry::RptDef() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	__ASSERT_DEBUG(IsRepeating(),Panic(_L("Isn't repeating")));
	return (iEntry->RptDef());
	}

/**
 * Returns the number of days warning for the entrys alarm.
 *
 * The number of days warning is a time interval in days and is the
 * number of days before an entrys start date, that the alarm is set to
 * sound. Returns zero if the entry is not alarmed.
 *
 * @returns   "TTimeIntervalDays"
 *            Number of days warning for the entrys alarm.
 */
inline TTimeIntervalDays TAgnLiteEntry::AlarmDaysWarning() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	__ASSERT_DEBUG(HasAlarm(),Panic(_L("Isn't alarmed")));
	return (iEntry->AlarmDaysWarning());
	}

/**
 * Returns the time of the alarm as a time interval in minutes from
 * midnight.
 *
 * @returns   "TTimeIntervalMinutes"
 *            Time interval in minutes from midnight.
 */
inline TTimeIntervalMinutes TAgnLiteEntry::AlarmTime() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	__ASSERT_DEBUG(HasAlarm(),Panic(_L("Isn't alarmed")));
	return (iEntry->AlarmTime());
	}

/**
 * Tests whether the entry is crossed out.
 *
 * @returns   "TBool"
 *            True if the entry is crossed out, otherwise false.
 */
inline TBool TAgnLiteEntry::IsCrossedOut() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsCrossedOut());
	}

/**
 * Tests whether the entry is repeating.
 *
 * @returns   "TBool"
 *            True if the entry is repeating, otherwise false.
 */
inline TBool TAgnLiteEntry::IsRepeating() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsRepeating());
	}

/**
 * Tests whether or not a repeating entry has any repeat exceptions.
 *
 * @returns   "TBool"
 *            True if the entry has any repeat exceptions, otherwise
 *            false.
 */
inline TBool TAgnLiteEntry::HasExceptions() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->HasExceptions());
	}

/**
 * Tests whether the entry has an alarm.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the entry has an alarm,
 *            <code>EFalse</code> if it does not have an alarm or if
 *            the entry is crossed out.
 */
inline TBool TAgnLiteEntry::HasAlarm() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->HasAlarm());
	}

/**
 * Tests whether the entry's rich text is stored inline (within the same
 * stream as the entry), or out of line (in an embedded store).
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the event is stored inline,
 *            otherwise, <code>EFalse</code>.
 */
inline TBool TAgnLiteEntry::IsStoredInline() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsStoredInline());
	}

//inline TBool TAgnLiteEntry::RichTextStoreIsOpen() const
//	{
//	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
//	return (iEntry->RichTextStoreIsOpen());
//	}

/**
 * Tests whether the entry should be displayed in the year view.
 *
 * @returns   "TBool"
 *            True if the entry should be displayed in the year
 *            view, false if not.
 */
inline TBool TAgnLiteEntry::DisplayInYearView() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->DisplayInYearView());
	}

/**
 * Tests whether the entry has an entry symbol.
 *
 * @returns   "TBool"
 *            True if the entry has an entry symbol, otherwise
 *            false.
 */
inline TBool TAgnLiteEntry::HasEntrySymbol() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->HasEntrySymbol());
	}

/**
 * Tests whether the entry is a day note.
 *
 * @returns   "TBool"
 *            True if the event is a day note, otherwise false.
 */
inline TBool TAgnLiteEntry::IsADayNote() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsADayNote());
	}

/**
 *
 * Tests whether the entry is tentative (i.
 *
 * e. not yet confirmed).
 *
 * @returns   "TBool"
 *            True if the event is tentative, otherwise false.
 */
inline TBool TAgnLiteEntry::IsTentative() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsTentative());
	}

/**
 * Tests whether the entry uses the default display time.
 *
 * @returns   "TBool"
 *            True if the entry uses the default display time,
 *            otherwise, false.
 */
inline TBool TAgnLiteEntry::HasDefaultDisplayTime() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->HasDefaultDisplayTime());
	}

inline const CAgnSortEntry* TAgnLiteEntry::SortEntry() const
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry);
	}


// --------------------------------------------------------------------
// -------------------------- TAgnAlarmDefaults -----------------------
// --------------------------------------------------------------------
/**
 * Returns the state of the "has alarm" flag.
 *
 * @returns   "TBool"
 *            True if there is an alarm set, otherwise False.
 */
inline TBool TAgnAlarmDefaults::HasAlarm() const
	{ return(iHasAlarm); }

/**
 * Gets the number of days warning for the alarm, as set by
 * <code>SetAlarmDateTime()</code>.
 *
 * @returns   "TTimeIntervalDays"
 *            The number of days warning.
 */
inline TTimeIntervalDays TAgnAlarmDefaults::AlarmDaysWarning() const
	{ return(iDaysWarning); }

/**
 * Gets the time of the alarm, as a number of minutes from midnight.
 *
 * @returns   "TTimeIntervalMinutes"
 *            The alarm time.
 */
inline TTimeIntervalMinutes TAgnAlarmDefaults::AlarmTime() const
	{ return(iTimeOfDay); }

/**
 * Gets the alarm sound name.
 *
 * @returns   "TPtrC"
 *            The alarm sound name.
 */
inline TPtrC TAgnAlarmDefaults::AlarmSoundName() const
	{ return(iSoundName); }

/**
 * Sets or unsets the "has alarm" flag.
 *
 * @param     "TBool aHasAlarm"
 *            <code>ETrue</code> to set the flag,
 *            <code>EFalse</code> to clear it.
 */
inline void TAgnAlarmDefaults::SetHasAlarm(TBool aHasAlarm)
	{ iHasAlarm=aHasAlarm; }

/**
 * Sets the name of the alarm sound.
 *
 * @param     "const TDesC& aAlarmSoundName"
 *            The alarm sound name.
 */
inline void TAgnAlarmDefaults::SetAlarmSoundName(const TDesC& aAlarmSoundName)
	{ iSoundName=aAlarmSoundName; }



// --------------------------------------------------------------------
// -------------------------- AgnModel --------------------------------
// --------------------------------------------------------------------
inline TAgnId AgnModel::NullId() 
	{ return (KNullStreamId); }

inline TAgnTodoListId AgnModel::NullTodoListId() 
	{ return TAgnTodoListId(KNullStreamId); }

inline TTime AgnModel::MinValidDate()
	{ return (AgnDateTime::MinDateAsTTime()); }

inline TTime AgnModel::MaxValidDate()
	{ return (AgnDateTime::MaxDateAsTTime()); }

inline TBool AgnModel::IsValidDate(const TTime& aDate)
	{ return (aDate != Time::NullTTime() && aDate >= MinValidDate() && aDate <= MaxValidDate()); }

inline TBool AgnModel::IsValidDate(TAgnDate aDate)
	{ return (aDate != AgnDateTime::NullDate()  && aDate >= AgnDateTime::MinDate() && aDate <= AgnDateTime::MaxDate()); }

inline TBool AgnModel::IsValidTime(TAgnTime aTime)
	{ return (aTime == AgnDateTime::NullTime() || aTime <= 1439); }

inline TBool AgnModel::IsValidTime(TTimeIntervalMinutes aTime)
	{ return (/*aTime == AgnDateTime::DefaultDisplayTime() || (*/aTime.Int() >= 0 && aTime.Int() <= 1439)/*)*/; }

inline TBool AgnModel::IsValidAlarmWarning(TTimeIntervalDays aDays)
	{ return (aDays.Int() >= 0 && aDays.Int() <= 1000); } //!!! any old figure for the moment

inline TUint AgnModel::MaxTodoListNameLength()
	{ return (KAgnMaxTodoListNameLength); }

inline TUint AgnModel::MaxSearchStringLength()
	{ return (KAgnMaxSearchStringLength); }


