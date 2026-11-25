// AGMENTRY.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


//------------------------------ CAgnEntry -------------------------------------------
inline const CStreamStore& CAgnEntry::OriginatingStore() const
	{ return (*iOriginatingStore); }

inline void CAgnEntry::SetId(TAgnEntryId aId)
/** Sets the entry ID. 

@param aId The ID to assign to the entry. */
	{ iInstanceId.SetId(aId); }

inline TAgnEntryId CAgnEntry::EntryId() const
/** Gets the entry's ID. 

@return Uniquely identifies an entry. Note that for an instance, you also need to 
consider the instance date. */
	{ return (iInstanceId.Id()); }

inline TAgnInstanceId CAgnEntry::InstanceId() const
/** Gets the instance ID.

@return The instance ID (the entry ID plus the instance date). */
	{ return (iInstanceId); }

inline void CAgnEntry::SetInstanceDate(TAgnDate aDate)
/** Sets the instance date.

@param aDate The instance date. */
	{ iInstanceId.SetDate(aDate); }

inline TAgnDate CAgnEntry::InstanceDate() const
/** Gets the instance date. 

The instance's entry ID (TAgnEntryId) together with the instance date 
(TAgnDate) make up the instance ID (TAgnInstanceId). These two 
components of the instance ID can be retrieved individually or together.

By default, the instance date for all entries is NULL (AgnDateTime::NullDate()).

@return The instance date. */
	{ return (iInstanceId.Date()); }

inline void CAgnEntry::SetIdAndInstanceDate(TAgnEntryId aId,TAgnDate aDate)
/** Sets the entry ID and the instance date. 

Together these make up the instance ID.

@param aId Uniquely identifies an entry.
@param aDate The instance date. */
	{ iInstanceId.SetIdAndDate(aId,aDate); }

inline void CAgnEntry::SetIdAndInstanceDate(const TAgnInstanceId& aInstanceId)
/** Sets the instance ID. 

@param aInstanceId The instance ID, which is the entry ID and the instance 
date. */
	{ iInstanceId=aInstanceId; }

inline void CAgnEntry::SetInstanceId(const TAgnInstanceId& aInstanceId)
/** Sets the instance ID. 

@param aInstanceId Const reference to the instance ID, which is the entry 
ID and the instance date. */
	{ iInstanceId=aInstanceId; }

inline void CAgnEntry::SetUniqueId(TAgnUniqueId aUId)
/** Sets the entry's unique ID.

@param aUId The entry's unique ID. */
	{ iUniqueId=aUId; }

inline TAgnUniqueId CAgnEntry::UniqueId() const
/** Gets the entry's unique ID. 

The unique ID is assigned when the entry is created, and is preserved during updates. 
Because of this, it can be used to identify the entry during synchronisation.

@return The entry's unique ID. */
	{ return iUniqueId; }


inline const TAgnReplicationData& CAgnEntry::ReplicationData() const
/** Gets the entry's replication data, as set by SetReplicationData(). 

@return A const reference to the entry's replication data. */
	{ return (iReplicationData); }

inline TAgnReplicationData& CAgnEntry::ReplicationData()
/** Gets the entry's replication data, as set by SetReplicationData(). 

@return A non-const reference to the entry's replication data. */
	{ return (iReplicationData); }

inline void CAgnEntry::SetReplicationData(const TAgnReplicationData& aReplicationData)
/** Sets the entry's replication data.

@param aReplicationData A reference to the entry's replication data. */
	{ iReplicationData = aReplicationData; }

inline void CAgnEntry::SetRichTextStreamId(TStreamId aId)
/** For a rich text object which is stored out of line, this function sets the 
ID for the embedded stream store in which the object has been stored.

@param aId The ID for the stream store in which the entry's rich text object 
has been stored. */
	{ iRichTextStreamId = aId; }

inline TStreamId CAgnEntry::RichTextStreamId() const
/** Gets the ID of the embedded stream store in which the entry's rich 
text has been stored.

@return The ID for the stream store in which the entry's rich text has been 
stored. */
	{ return (iRichTextStreamId); }



//------------------------------ CAgnAppt -------------------------------------------

inline const TAgnBasicAppt& CAgnAppt::BasicAppt() const
/** Gets the appointment's basic details. 

These are the start date/time and end date/time. 

@return The appointment entry's basic details (start date/time and end date/time). */
	{ return (iBasicAppt); }


//------------------------------ CAgnEvent -------------------------------------------

inline const TAgnBasicEvent& CAgnEvent::BasicEvent() const
/** Gets the event-specific entry details. 

These details are the start date and end date and the display time.

@return The event-specific entry details. */
	{ return (iBasicEvent); }


//------------------------------ CAgnAnniv -------------------------------------------

inline TTimeIntervalYears CAgnAnniv::BaseYear() const
/** Gets the anniversary's base year, as set by SetBaseYear().

@return The anniversary's base year. */
	{ return (iBaseYear); }


inline CAgnAnniv::TDisplayAs CAgnAnniv::DisplayAs() const
/** Tests whether the anniversary should be displayed as the base year alone, 
the elapsed years alone, both the base year and elapsed years, or none of 
these.

@return Indicates how the anniversary should be displayed. */
	{ return (iDisplayAs); }


inline TBool CAgnAnniv::HasBaseYear() const
/** Gets the anniversary's 'has base year' property. 

This property indicates whether the anniversary has a base year.

@return ETrue if anniversary has a base year, EFalse if not. */
	{ return (iHasBaseYear); }

inline void CAgnAnniv::SetHasBaseYear(TBool aHasBaseYear)
/** Sets the anniversary's 'has base year' property. 

This function is invoked by SetBaseYear().

@param aHasBaseYear ETrue if anniversary has a base year, EFalse if not. */
	{ iHasBaseYear = aHasBaseYear; }


//------------------------------ CAgnTodo -------------------------------------------
inline TAgnTodoListId CAgnTodo::TodoListId() const
/** Gets the ID of the to-do list to which the entry belongs, as set by 
SetTodoListId().

@return Identifies the to-do list to which the entry belongs. */
	{ return (iBasicTodo.TodoListId()); }

inline CAgnTodo::TDisplayDueDateAs CAgnTodo::DisplayDueDateAs() const
/** Tests how the to-do entry's due date should be displayed. 

By default, the due date is displayed as EAutomatic.

@return Indicates how the due date should be displayed. */
	{ return (iDisplayDueDateAs); }

inline TUint CAgnTodo::Priority() const
/** Gets the priority of a to-do entry as set by SetPriority(). The default 
value is zero.

@return The priority of the to-do entry. */
	{ return (iBasicTodo.Priority()); }

inline TTimeIntervalDays CAgnTodo::Duration() const
/** Gets the to-do entry's duration, (the number of days between the start 
date and the due date). 

This function can be called on an entry if it is not repeating or on an 
individual instance if the entry is repeating. If the duration has not 
been set, this function returns zero.

@return The to-do entry's duration. */
	{ return (iBasicTodo.Duration()); }

inline const TAgnBasicTodo& CAgnTodo::BasicTodo() const
/** Gets the details specific to the to-do entry, e.g. the due and crossed 
out dates and the display time.

@return The to-do specific entry details. */
	{ return (iBasicTodo); }

inline TBool CAgnTodo::IsAlarmSetFromDueDate() const
/** Tests whether the alarm date is set relative to the entry's due date, 
as set by SetAlarmFromDueDate(). 

By default, the alarm is set relative to the due date.

@return ETrue if an alarm has been set from the to-do entry's due date, 
EFalse if not. */
	{ return (iBasicTodo.IsAlarmSetFromDueDate()); }

inline TBool CAgnTodo::IsAlarmSetFromStartDate() const
/** Tests whether the alarm date is set relative to the entry's start date 
as set by SetAlarmFromStartDate(). 

By default, the alarm is set relative to the due date.

@return ETrue if an alarm has been set from the to-do entry's start date, 
EFalse if not. */
	{ return (iBasicTodo.IsAlarmSetFromStartDate()); }



