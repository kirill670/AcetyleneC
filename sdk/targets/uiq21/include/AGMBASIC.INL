// AGMBASIC.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// --------------------- TAgnAlarmPreTime -----------------------------------
inline TBool TAgnAlarmPreTime::operator==(const TAgnAlarmPreTime& aOther) const
	{ return (iAlarmPreTime == aOther.iAlarmPreTime); }

inline TBool TAgnAlarmPreTime::operator!=(const TAgnAlarmPreTime& aOther) const
	{ return (iAlarmPreTime != aOther.iAlarmPreTime); }



// ---------------------------- CAgnBasicEntry ----------------------------

/** 
 * Default constructor
 * Sets the status of the entry to "needs action" by default
 */
inline CAgnBasicEntry::CAgnBasicEntry()
	{
	iAttributes = EIsNeedsAction;
	}

/**
 * Tests whether the entry is crossed out.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the entry is crossed out,
 *            <code>EFalse</code> if not.
 */
inline TBool CAgnBasicEntry::IsCrossedOut() const
	{ return (iAttributes & EIsCrossedOut); }

/**
 * Is the entry repeating?.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if entry is repeating,
 *            <code>EFalse</code> if not.
 */
inline TBool CAgnBasicEntry::IsRepeating() const  	
	{ return (iAttributes & EIsRepeating); }

/**
 * Returns whether or not the entry has repeat exceptions, as set by
 * <code>SetHasExceptions()</code>.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if entry has any repeat exceptions,
 *            <code>EFalse</code> if not.
 */
inline TBool CAgnBasicEntry::HasExceptions() const
	{ return (iAttributes & EHasExceptions); }

/**
 * Tests whether the entry's rich text object is stored inline or out of
 * line.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the entry is stored inline,
 *            <code>EFalse</code> if not.
 */
inline TBool CAgnBasicEntry::IsStoredInline() const
	{ return (iAttributes & EIsStoredInline); }

/**
 * Returns whether the entry is displayed in the application's year view.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if entry is displayed in the year
 *            view, <code>EFalse</code> if not.
 */
inline TBool CAgnBasicEntry::DisplayInYearView() const
	{ return (iAttributes & EDisplayInYearView); }

/**
 * Tests whether the entry has an entry symbol.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if entry has an entry symbol,
 *            <code>EFalse</code> if not.
 */
inline TBool CAgnBasicEntry::HasEntrySymbol() const
	{ return (iAttributes & EHasEntrySymbol); } 

/**
 * Tests whether the entry is a day note.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the entry is a day note,
 *            <code>EFalse</code> if not.
 */
inline TBool CAgnBasicEntry::IsADayNote() const
	{ return (iAttributes & EIsADayNote); }

/**
 * Does the entry use the default display time?.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the entry uses the default
 *            display time, <code>EFalse</code> if not.
 */
inline TBool CAgnBasicEntry::HasDefaultDisplayTime() const
	{ return (iAttributes & EHasDefaultDisplayTime); }

//inline TBool CAgnBasicEntry::HasBeenDeleted() const 
//	{ return (iAttributes & EHasBeenDeleted); }

//inline TBool CAgnBasicEntry::IsRestricted() const
//	{ return (iAttributes & EIsRestricted); }

//inline TBool CAgnBasicEntry::IsPrivate() const
//	{ return (iAttributes & EIsPrivate); }

/**
 * Tests whether the entry is tentative (not yet confirmed).
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if entry is tentative,
 *            <code>EFalse</code> if not.
 */
inline TBool CAgnBasicEntry::IsTentative() const 
	{ return (iAttributes & EIsTentative); }

/**
 * Tests whether the entry is a sketch.
 *
 * An entry can be a sketch if the only thing contained in the entry's
 * rich text is a picture character providing a link to the embedded
 * sketch.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if entry is a sketch,
 *            <code>EFalse</code> if not.
 */
inline TBool CAgnBasicEntry::IsSketch() const
	{ return (iAttributes & EIsSketch); }

/**
 * This function indicates whether the entry has extended attributes
 * (added in EPOC Release 5 and later).
 *
 * It should not be called by third parties.
 *
 */
inline TBool CAgnBasicEntry::HasExtended() const
	{ return (iAttributes & EHasExtended); }

/**
 *
 * Clears all entry attributes, for instance whether the entry is
 * tentative and whether it is crossed out.
 *
 */
inline void CAgnBasicEntry::ClearAllAttributes()
	{ iAttributes=0; }

/**
 * Returns the entry symbol.
 *
 * @returns   "TChar"
 *            The entry symbol.
 */
inline TChar CAgnBasicEntry::EntrySymbol() const
	{ return (iEntrySymbol); }
		
inline TAgnAlarmPreTime CAgnBasicEntry::AlarmPreTime() const
	{ return (iAlarmPreTime); }; 

/**
 * Returns a pointer to the entrys repeat details, including exceptions.
 *
 * Two versions of the function are supplied. The compiler chooses the
 * appropriate version based on the use made of the returned reference.
 * If the returned reference is used in an expression where that
 * reference can be modified, then the non-const version is chosen.
 *
 * @returns   "CAgnRptDef*"
 *            A non-const pointer to an object which contains the
 *            entry's repeat details including exceptions. NULL if
 *            the entry is not repeating.
 * @returns   "const CAgnRptDef*"
 *            A const pointer to an object which contains the
 *            entry's repeat details including exceptions. NULL if
 *            the entry is not repeating.
 */
inline CAgnRptDef* CAgnBasicEntry::RptDef() 
	{ return (iRptDef);}

inline const CAgnRptDef* CAgnBasicEntry::RptDef() const
	{ return (iRptDef); }

// ---------------------------------- TAgnBasicAppt -------------------------------------------
/**
 * Gets the appointment's start date/time.
 *
 * If the object is a day note, its display time is given by the time
 * portion of this value.
 *
 * @returns   "TAgnDateTime"
 *            The appointment's start date/time.
 */
inline TAgnDateTime TAgnBasicAppt::StartDateTime() const
	{ return (iStartDateTime); }

inline TAgnDateTime TAgnBasicAppt::EndDateTime() const
	{ return (iEndDateTime); }

// --------------------------------- TAgnBasicEvent ------------------------------------------
//inline TAgnBasicEvent::TAgnBasicEvent() /*: iDisplayTime((TAgnTime)AgnDateTime::DefaultDisplayTime().Int()) */
//	{}

/**
 * Gets the event's start date as an agenda date.
 *
 * @returns   "TAgnDate"
 *            The event's start date.
 */
inline TAgnDate TAgnBasicEvent::StartDate() const
	{ return (iStartDate); }

/**
 * Gets the event's end date as an agenda date.
 *
 * @returns   "TAgnDate"
 *            The event's end date.
 */
inline TAgnDate TAgnBasicEvent::EndDate() const
	{ return (iEndDate); }

/**
 * Gets the event's display time.
 *
 * The display time can be used to tell the user interface where to
 * display the event in a view that contains times of day. It is stored
 * as a number of minutes from midnight.
 *
 * @returns   "TAgnTime"
 *            The display time of the event.
 */
inline TAgnTime TAgnBasicEvent::DisplayTime() const
	{ return (iDisplayTime); }

inline void TAgnBasicEvent::SetDisplayTime(TAgnTime aDisplayTime)
	{  iDisplayTime=(TAgnTime)aDisplayTime; } 


// -------------------------------------- TAgnBasicTodo ------------------------------------------
//inline TAgnBasicTodo::TAgnBasicTodo() /*: iDisplayTime((TAgnTime)AgnDateTime::DefaultDisplayTime().Int()) */
//	{
//	SetHasDefaultDisplayTime(ETrue);
//	}

/**
 * Returns the due date (indicates the date by which the action should be
 * carried out).
 *
 * @returns   "TAgnDate"
 *            The due date.
 */
inline TAgnDate TAgnBasicTodo::DueDate() const
	{ return (iDueDate); }

/**
 * Sets the due date (this should be a null value for an undated to-do).
 *
 * @param     "TAgnDate aDueDate"
 *            The due date.
 */
void TAgnBasicTodo::SetDueDate(TAgnDate aDueDate)
	{ iDueDate=aDueDate; }

/**
 * Returns the crossed out date,
 * i.e. the date on which the action required by the to-do entry was
 * carried out.
 *
 * @returns   "TAgnDate"
 *            The crossed out date.
 */
inline TAgnDate TAgnBasicTodo::CrossedOutDate() const
	{ return (iCrossedOutDate); }

/**
 * Returns the display time (a number of minutes from midnight between
 * zero and 1439 inclusive).
 *
 * @returns   "TAgnTime"
 *            The display time.
 */
inline TAgnTime TAgnBasicTodo::DisplayTime() const
	{ return (iDisplayTime); }

/**
 * Sets the display time (the time at which the entry is displayed in
 * dated views a number of minutes from midnight; between zero and 1439
 * inclusive).
 *
 * @param     "TAgnTime aDisplayTime"
 *            The display time.
 */
inline void TAgnBasicTodo::SetDisplayTime(TAgnTime aDisplayTime)
	{ iDisplayTime=(TAgnTime)aDisplayTime; }

/**
 * Returns the ID of the to-do list to which the entry belongs.
 *
 * @returns   "TAgnTodoListId"
 *            Identifies the to-do list to which the entry belongs.
 */
inline TAgnTodoListId TAgnBasicTodo::TodoListId() const
	{ return (iTodoListId); }

/**
 * Sets the ID of the to-do list to which the entry belongs.
 *
 * @param     "TAgnTodoListId aTodoListId"
 *            The to-do list ID.
 */
inline void TAgnBasicTodo::SetTodoListId(TAgnTodoListId aTodoListId)
	{ iTodoListId=aTodoListId; }

/**
 * Returns the duration (the number of days between the start date and
 * the due date).
 *
 * @returns   "TAgnDurationDays"
 *            The duration in days.
 */
inline TAgnDurationDays TAgnBasicTodo::Duration() const
	{ return (iDuration); }

/**
 * Sets the duration (the number of days between the start date and the
 * due date).
 *
 * @param     "TAgnDurationDays aDuration"
 *            The duration.
 */
inline void TAgnBasicTodo::SetDuration(TAgnDurationDays aDuration)
	{ iDuration=aDuration; }

/**
 * Returns the priority of the current to-do entry, as set by
 * <code>SetPriority()</code>.
 *
 * The default is zero.
 *
 * @returns   "TUint"
 *            The priority value.
 */
inline TUint TAgnBasicTodo::Priority() const
	{ return (iPriority); }

/**
 * Sets the priority of the to-do entry.
 *
 * @param     "TUint aPriority"
 *            The priority.
 */
inline void TAgnBasicTodo::SetPriority(TUint aPriority)
	{ 
	__ASSERT_DEBUG(SafeToCast(sizeof(TUint8),aPriority),Panic(_L("Unsafe cast"))); 
	iPriority=(TUint8)aPriority; 
	}

/**
 * Sets the alarm date to be a number of days from the due date, rather
 * than from the start date.
 *
 */
inline void TAgnBasicTodo::SetAlarmFromDueDate()
	{ iAlarmFrom = EDueDate; }

/**
 * Sets the alarm date to be a number of days from the start date, rather
 * than from the due date.
 *
 */
inline void TAgnBasicTodo::SetAlarmFromStartDate()
	{ iAlarmFrom = EStartDate; }

/**
 * Tests whether the alarm is set from the due date, rather than the
 * start date.
 *
 * @returns   "TBool"
 *            True if the alarm is set from the due date, false if
 *            not.
 */
inline TBool TAgnBasicTodo::IsAlarmSetFromDueDate() const
	{ return (iAlarmFrom == EDueDate); }

/**
 * Tests whether the alarm is set from the start date, rather than the
 * due date.
 *
 * @returns   "TBool"
 *            True if the alarm is set from the start date, false if
 *            not.
 */
inline TBool TAgnBasicTodo::IsAlarmSetFromStartDate() const
	{ return (iAlarmFrom == EStartDate); }
