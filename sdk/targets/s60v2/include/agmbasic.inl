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

/*
 * Default constructor
 * Sets the status of the entry to "needs action" by default
 */
inline CAgnBasicEntry::CAgnBasicEntry()
	{
	iAttributes = EIsNeedsAction;
	}

inline TBool CAgnBasicEntry::IsCrossedOut() const
/** Tests whether the entry is crossed out.

@return ETrue if the entry is crossed out, EFalse if not. */
	{ return (iAttributes & EIsCrossedOut); }

inline TBool CAgnBasicEntry::IsRepeating() const  	
/** Tests whether the entry is repeating.

@return ETrue if entry is repeating, EFalse if not. */
	{ return (iAttributes & EIsRepeating); }

inline TBool CAgnBasicEntry::HasExceptions() const
/** Tests whether the entry has repeat exceptions, as set by SetHasExceptions().

@return ETrue if entry has any repeat exceptions, EFalse if not. */
	{ return (iAttributes & EHasExceptions); }

inline TBool CAgnBasicEntry::IsStoredInline() const
/** Tests whether the entry's rich text object is stored inline or out of line.

@return ETrue if the entry is stored inline, EFalse if not. */
	{ return (iAttributes & EIsStoredInline); }

inline TBool CAgnBasicEntry::DisplayInYearView() const
/** Returns whether the entry is displayed in the application's year view.

@return ETrue if entry is displayed in the year view, EFalse if not. */
	{ return (iAttributes & EDisplayInYearView); }

inline TBool CAgnBasicEntry::HasEntrySymbol() const
/** Tests whether the entry has a symbol.

@return ETrue if the entry has a symbol, EFalse if not. */
	{ return (iAttributes & EHasEntrySymbol); } 

inline TBool CAgnBasicEntry::IsADayNote() const
/** Tests whether the entry is a day note.

@return ETrue if the entry is a day note, EFalse if not. */
	{ return (iAttributes & EIsADayNote); }

inline TBool CAgnBasicEntry::HasDefaultDisplayTime() const
/** Does the entry use the default display time?

@return ETrue if the entry uses the default display time, EFalse if not. */
	{ return (iAttributes & EHasDefaultDisplayTime); }

//inline TBool CAgnBasicEntry::HasBeenDeleted() const 
//	{ return (iAttributes & EHasBeenDeleted); }

//inline TBool CAgnBasicEntry::IsRestricted() const
//	{ return (iAttributes & EIsRestricted); }

//inline TBool CAgnBasicEntry::IsPrivate() const
//	{ return (iAttributes & EIsPrivate); }

inline TBool CAgnBasicEntry::IsTentative() const 
/** Tests whether the entry is tentative (not yet confirmed).

@return ETrue if entry is tentative, EFalse if not. */
	{ return (iAttributes & EIsTentative); }

inline TBool CAgnBasicEntry::IsSketch() const
/** Tests whether the entry is a sketch. 

An entry can be a sketch if the only thing contained in the entry's 
rich text is a picture character providing a link to the embedded sketch.

@return ETrue if entry is a sketch, EFalse if not. */
	{ return (iAttributes & EIsSketch); }

inline TBool CAgnBasicEntry::HasExtended() const
/** Tests whether the entry has extended attributes.

It should not be called by third parties. */
	{ return (iAttributes & EHasExtended); }

inline void CAgnBasicEntry::ClearAllAttributes()
/** Clears all entry attributes. */
	{ iAttributes=0; }

inline TChar CAgnBasicEntry::EntrySymbol() const
/** Gets the entry symbol.

@return The entry symbol. */
	{ return (iEntrySymbol); }
		
inline TAgnAlarmPreTime CAgnBasicEntry::AlarmPreTime() const
	{ return (iAlarmPreTime); }; 

inline CAgnRptDef* CAgnBasicEntry::RptDef() 
/** Returns a pointer to the entry's repeat details, including exceptions. 

@return A non-const pointer to an object which contains the entry's repeat 
details including exceptions. NULL if the entry is not repeating. */
	{ return (iRptDef);}

inline const CAgnRptDef* CAgnBasicEntry::RptDef() const
/** Returns a pointer to the entry's repeat details, including exceptions. 

@return A const pointer to an object which contains the entry's repeat details 
including exceptions. NULL if the entry is not repeating. */
	{ return (iRptDef); }

// ---------------------------------- TAgnBasicAppt -------------------------------------------
inline TAgnDateTime TAgnBasicAppt::StartDateTime() const
/** Gets the appointment's start date/time. 

If the object is a day note, its display time is given by the time portion of 
this value.

@return The appointment's start date/time. */
	{ return (iStartDateTime); }

inline TAgnDateTime TAgnBasicAppt::EndDateTime() const
	{ return (iEndDateTime); }

// --------------------------------- TAgnBasicEvent ------------------------------------------
//inline TAgnBasicEvent::TAgnBasicEvent() /*: iDisplayTime((TAgnTime)AgnDateTime::DefaultDisplayTime().Int()) */
//	{}

inline TAgnDate TAgnBasicEvent::StartDate() const
/** Gets the event's start date as an agenda date.

@return The event's start date. */
	{ return (iStartDate); }

inline TAgnDate TAgnBasicEvent::EndDate() const
/** Gets the event's end date as an agenda date.

@return The event's end date. */
	{ return (iEndDate); }

inline TAgnTime TAgnBasicEvent::DisplayTime() const
/** Gets the event's display time. The display time can be used to tell the user 
interface where to display the event in a view that contains times of day. 
It is stored as a number of minutes from midnight.

@return The display time of the event. */
	{ return (iDisplayTime); }

inline void TAgnBasicEvent::SetDisplayTime(TAgnTime aDisplayTime)
	{  iDisplayTime=(TAgnTime)aDisplayTime; } 


// -------------------------------------- TAgnBasicTodo ------------------------------------------
//inline TAgnBasicTodo::TAgnBasicTodo() /*: iDisplayTime((TAgnTime)AgnDateTime::DefaultDisplayTime().Int()) */
//	{
//	SetHasDefaultDisplayTime(ETrue);
//	}

inline TAgnDate TAgnBasicTodo::DueDate() const
/** Gets the due date. 

The due date indicates the date by which the action should be carried out.

@return The due date. */
	{ return (iDueDate); }

void TAgnBasicTodo::SetDueDate(TAgnDate aDueDate)
/** Sets the due date (this should be a null value for an undated to-do).

@param aDueDate The due date. */
	{ iDueDate=aDueDate; }

inline TAgnDate TAgnBasicTodo::CrossedOutDate() const
/** Gets the crossed out date, i.e. the date on which the action required by 
the to-do entry was carried out.

@return The crossed out date. */
	{ return (iCrossedOutDate); }

inline TAgnTime TAgnBasicTodo::DisplayTime() const
/** Gets the display time (a number of minutes from midnight: between zero 
and 1439 inclusive).

@return The display time. */
	{ return (iDisplayTime); }

inline void TAgnBasicTodo::SetDisplayTime(TAgnTime aDisplayTime)
/** Sets the display time. 

This is the time at which the entry is displayed in dated views and is 
a number of minutes from midnight: between zero and 1439 inclusive.

@param aDisplayTime The display time. */
	{ iDisplayTime=(TAgnTime)aDisplayTime; }

inline TAgnTodoListId TAgnBasicTodo::TodoListId() const
/** Gets the ID of the to-do list to which the entry belongs.

@return Identifies the to-do list to which the entry belongs. */
	{ return (iTodoListId); }

inline void TAgnBasicTodo::SetTodoListId(TAgnTodoListId aTodoListId)
/** Sets the ID of the to-do list to which the entry belongs.

@param aTodoListId The to-do list ID. */
	{ iTodoListId=aTodoListId; }

inline TAgnDurationDays TAgnBasicTodo::Duration() const
/** Gets the entry's duration (the number of days between the start date and the due 
date).

@return The duration in days. */
	{ return (iDuration); }

inline void TAgnBasicTodo::SetDuration(TAgnDurationDays aDuration)
/** Sets the entry's duration (the number of days between the start date and the due date).

@param aDuration The duration. */
	{ iDuration=aDuration; }

inline TUint TAgnBasicTodo::Priority() const
/** Gets the priority of the to-do entry, as set by SetPriority(). 

The default is zero.

@return The priority value. */
	{ return (iPriority); }

inline void TAgnBasicTodo::SetPriority(TUint aPriority)
/** Sets the priority of the to-do entry.

@param aPriority The priority. */
	{ 
	__ASSERT_DEBUG(SafeToCast(sizeof(TUint8),aPriority),Panic(_L("Unsafe cast"))); 
	iPriority=(TUint8)aPriority; 
	}

inline void TAgnBasicTodo::SetAlarmFromDueDate()
/** Sets the alarm date to be a number of days from the due date, rather than from 
the start date. */
	{ iAlarmFrom = EDueDate; }

inline void TAgnBasicTodo::SetAlarmFromStartDate()
/** Sets the alarm date to be a number of days from the start date, rather than 
from the due date. */
	{ iAlarmFrom = EStartDate; }

inline TBool TAgnBasicTodo::IsAlarmSetFromDueDate() const
/** Tests whether the alarm date is offset from the due date, rather than the start date.

@return True if the alarm date is offset from the due date, false if not. */
	{ return (iAlarmFrom == EDueDate); }

inline TBool TAgnBasicTodo::IsAlarmSetFromStartDate() const
/** Tests whether the alarm date is offset from the start date, rather than the due date.

@return True if the alarm date is offset from the start date, false if not. */
	{ return (iAlarmFrom == EStartDate); }
