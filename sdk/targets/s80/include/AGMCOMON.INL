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

inline CAgnEntry::TType TAgnLiteEntry::Type() const
/** Gets the entry type.

@return The type of agenda entry. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->Type());
	}

inline TAgnEntryId TAgnLiteEntry::Id() const
/** Gets the entry ID.

@return The entry ID. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->Id());
	}

inline TChar TAgnLiteEntry::EntrySymbol() const
/** Gets the entry symbol.

@return The entry symbol. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	__ASSERT_DEBUG(HasEntrySymbol(),Panic(_L("Doesn't have an entry symbol")));
	return (iEntry->EntrySymbol());
	}


inline TTimeIntervalMinutes TAgnLiteEntry::DisplayTime() const
/** Gets the display time. 

The display time is the time at which the entry is displayed 
in dated views, as a number of minutes from midnight.

@return The display time. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->DisplayTime());
	}

inline const CAgnRptDef* TAgnLiteEntry::RptDef() const
/** Gets a pointer to the entry's repeat details, including exceptions

@return The entry's repeat details. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	__ASSERT_DEBUG(IsRepeating(),Panic(_L("Isn't repeating")));
	return (iEntry->RptDef());
	}

inline TTimeIntervalDays TAgnLiteEntry::AlarmDaysWarning() const
/** Gets the number of days warning for the entry's alarm. 

The number of days warning is a time interval in days and is the number of 
days before an entry's start date, that the alarm is set to sound. Returns 
zero if the entry is not alarmed.

@return Number of days warning for the entry's alarm. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	__ASSERT_DEBUG(HasAlarm(),Panic(_L("Isn't alarmed")));
	return (iEntry->AlarmDaysWarning());
	}

inline TTimeIntervalMinutes TAgnLiteEntry::AlarmTime() const
/** Returns the time of the alarm as an interval in minutes from midnight.

@return Time interval in minutes from midnight. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	__ASSERT_DEBUG(HasAlarm(),Panic(_L("Isn't alarmed")));
	return (iEntry->AlarmTime());
	}

inline TBool TAgnLiteEntry::IsCrossedOut() const
/** Tests whether the entry is crossed out.

@return True if the entry is crossed out, otherwise false. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsCrossedOut());
	}

inline TBool TAgnLiteEntry::IsRepeating() const
/** Tests whether the entry is repeating.

@return True if the entry is repeating, otherwise false. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsRepeating());
	}

inline TBool TAgnLiteEntry::HasExceptions() const
/** Tests whether a repeating entry has any repeat exceptions.

@return True if the entry has any repeat exceptions, otherwise false. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->HasExceptions());
	}

inline TBool TAgnLiteEntry::HasAlarm() const
/** Tests whether the entry has an alarm.

@return ETrue if the entry has an alarm, EFalse if it does not have an alarm 
or if the entry is crossed out. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->HasAlarm());
	}

inline TBool TAgnLiteEntry::IsStoredInline() const
/** Tests whether the entry's rich text is stored inline (within the same stream 
as the entry), or out of line (in an embedded store).

@return ETrue if the event is stored inline, otherwise, EFalse. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsStoredInline());
	}

//inline TBool TAgnLiteEntry::RichTextStoreIsOpen() const
//	{
//	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
//	return (iEntry->RichTextStoreIsOpen());
//	}

inline TBool TAgnLiteEntry::DisplayInYearView() const
/** Tests whether the entry should be displayed in the year view.

@return True if the entry should be displayed in the year view, false if not. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->DisplayInYearView());
	}

inline TBool TAgnLiteEntry::HasEntrySymbol() const
/** Tests whether the entry has a symbol.

@return True if the entry has a symbol, otherwise false. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->HasEntrySymbol());
	}

inline TBool TAgnLiteEntry::IsADayNote() const
/** Tests whether the entry is a day note.

@return True if the event is a day note, otherwise false. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsADayNote());
	}

inline TBool TAgnLiteEntry::IsTentative() const
/** Tests whether the entry is tentative (not confirmed).

@return True if the event is tentative, otherwise false. */
	{
	__ASSERT_DEBUG(iEntry,Panic(_L("Null entry")));
	return (iEntry->IsTentative());
	}

inline TBool TAgnLiteEntry::HasDefaultDisplayTime() const
/** Tests whether the entry uses the default display time. 

@return True if the entry uses the default display time, otherwise, false. */
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
inline TBool TAgnAlarmDefaults::HasAlarm() const
/** Gets the state of the 'has alarm' flag.

@return True if there is an alarm set, otherwise false. */
	{ return(iHasAlarm); }

inline TTimeIntervalDays TAgnAlarmDefaults::AlarmDaysWarning() const
/** Gets the number of days warning for the alarm, as set by SetAlarmDateTime().

@return The number of days warning. */
	{ return(iDaysWarning); }

inline TTimeIntervalMinutes TAgnAlarmDefaults::AlarmTime() const
/** Gets the time of the alarm, as a number of minutes from midnight.

@return The alarm time. */
	{ return(iTimeOfDay); }

inline TPtrC TAgnAlarmDefaults::AlarmSoundName() const
/** Gets the alarm sound name.

@return The alarm sound name. */
	{ return(iSoundName); }

inline void TAgnAlarmDefaults::SetHasAlarm(TBool aHasAlarm)
/** Sets or unsets the 'has alarm' flag.

@param aHasAlarm ETrue to set the flag, EFalse to clear it. */
	{ iHasAlarm=aHasAlarm; }

inline void TAgnAlarmDefaults::SetAlarmSoundName(const TDesC& aAlarmSoundName)
/** Sets the name of the alarm sound.

@param aAlarmSoundName The alarm sound name. */
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


