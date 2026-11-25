// AGMENTRY.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


//------------------------------ CAgnEntry -------------------------------------------
inline const CStreamStore& CAgnEntry::OriginatingStore() const
	{ return (*iOriginatingStore); }

/**
 * Sets the entry ID.
 *
 * @param     "TAgnEntryId aId"
 *            The ID to assign to the entry.
 */
inline void CAgnEntry::SetId(TAgnEntryId aId)
	{ iInstanceId.SetId(aId); }

/**
 * Retrieves the entrys ID.
 *
 * @returns   "TAgnEntryId"
 *            Uniquely identifies an entry, but for an instance, you
 *            also need to consider the instance date.
 */
inline TAgnEntryId CAgnEntry::EntryId() const
	{ return (iInstanceId.Id()); }

/**
 * Retrieves the instance ID.
 *
 * @returns   "TAgnInstanceId"
 *            The instance ID (the entry ID plus the instance date).
 */
inline TAgnInstanceId CAgnEntry::InstanceId() const
	{ return (iInstanceId); }

/**
 * Sets the instance date.
 *
 * @param     "TAgnDate aDate"
 *            The instance date.
 */
inline void CAgnEntry::SetInstanceDate(TAgnDate aDate)
	{ iInstanceId.SetDate(aDate); }

/**
 * Retrieves the instance date.
 *
 * The instances entry ID (<code>TAgnEntryId</code>) together with the
 * instance date (<code>TAgnDate</code>) make up the instance ID
 * (<code>TAgnInstanceId</code>). These two components of the instance ID
 * can be retrieved individually or together.By default, the instance
 * date for all entries is NULL (<code>AgnDateTime::NullDate()</code>).
 *
 * @returns   "TAgnDate"
 *            The instance date.
 */
inline TAgnDate CAgnEntry::InstanceDate() const
	{ return (iInstanceId.Date()); }

/**
 * Sets the entry ID and the instance date.
 *
 * Together these two details make up the instance ID.
 *
 * @param     "TAgnEntryId aId"
 *            Uniquely identifies an entry.
 * @param     "TAgnDate aDate"
 *            The instance date.
 */
inline void CAgnEntry::SetIdAndInstanceDate(TAgnEntryId aId,TAgnDate aDate)
	{ iInstanceId.SetIdAndDate(aId,aDate); }

inline void CAgnEntry::SetIdAndInstanceDate(const TAgnInstanceId& aInstanceId)
	{ iInstanceId=aInstanceId; }

/**
 * Sets the instance ID.
 *
 * @param     "const TAgnInstanceId& aInstanceId"
 *            Const reference to the instance ID, which is the entry
 *            ID plus the instance date.
 */
inline void CAgnEntry::SetInstanceId(const TAgnInstanceId& aInstanceId)
	{ iInstanceId=aInstanceId; }

/**
 * Sets the entrys unique ID.
 *
 * @param     "TAgnUniqueId aUId"
 *            The entrys unique ID.
 */
inline void CAgnEntry::SetUniqueId(TAgnUniqueId aUId)
	{ iUniqueId=aUId; }

/**
 * Retrieves the entrys replication data as set
 * by<code>SetReplicationData()</code>.
 *
 * Two versions of the function are supplied. The compiler chooses the
 * appropriate version based on the use made of the returned pointer. If
 * the returned pointer is used in an expression where that pointer can
 * be modified, then the non-const version is chosen.
 *
 * @returns   "const TAgnReplicationData&"
 *            A const reference to the entrys replication data.
 * @returns   "TAgnReplicationData&"
 *            A non-const reference to the entrys replication data.
 */
inline const TAgnReplicationData& CAgnEntry::ReplicationData() const
	{ return (iReplicationData); }

inline TAgnReplicationData& CAgnEntry::ReplicationData()
	{ return (iReplicationData); }

/**
 * Sets the entrys replication data.
 *
 * @param     "const TAgnReplicationData& aReplicationData"
 *            A reference to the entrys replication data.
 */
inline void CAgnEntry::SetReplicationData(const TAgnReplicationData& aReplicationData)
	{ iReplicationData = aReplicationData; }

/**
 * For a rich text object which is stored out of line, this function sets
 * the ID for the embedded stream store in which the object has been
 * stored.
 *
 * @param     "TStreamId aId"
 *            The ID for the stream store in which the entrys rich
 *            text object has been stored.
 */
inline void CAgnEntry::SetRichTextStreamId(TStreamId aId)
	{ iRichTextStreamId = aId; }

/**
 * Retrieves the ID for the embedded stream store in which the entrys
 * rich text has been stored.
 *
 * @returns   "TStreamId"
 *            The ID for the stream store in which the entrys rich
 *            text has been stored.
 */
inline TStreamId CAgnEntry::RichTextStreamId() const
	{ return (iRichTextStreamId); }



//------------------------------ CAgnAppt -------------------------------------------

/**
 * Returns the appointment entry's basic details,
 * i.e. the start date/time and end date/time. Note that these details
 * should normally be set and retrieved using other functions in this
 * class.
 *
 * @returns   "TAgnBasicAppt&"
 *            The appointment entrys basic details (start date/time
 *            and end date/time).
 */
inline const TAgnBasicAppt& CAgnAppt::BasicAppt() const
	{ return (iBasicAppt); }


//------------------------------ CAgnEvent -------------------------------------------

/**
 * Returns the event-specific entry details, i.
 *
 * e. the start date and end date and the display time. Note that these
 * details should normally be set and retrieved using other functions in
 * this class.
 *
 * @returns   "TAgnBasicEvent&"
 *            The event-specific entry details.
 */
inline const TAgnBasicEvent& CAgnEvent::BasicEvent() const
	{ return (iBasicEvent); }


//------------------------------ CAgnAnniv -------------------------------------------

/**
 * Returns the anniversary entrys base year as set by
 * <code>SetBaseYear()</code>.
 *
 * @returns   "TTimeIntervalYears"
 *            The anniversary entrys base year.
 */
inline TTimeIntervalYears CAgnAnniv::BaseYear() const
	{ return (iBaseYear); }


/**
 * Retrieves whether the anniversary should be displayed as the base year
 * alone, the elapsed years alone, both the base year and elapsed years,
 * or none of these.
 *
 * @returns   "TDisplayAs"
 *            Indicates how the anniversary should be displayed.
 *            (See <code>TDisplayAs</code> enum)
 */
inline CAgnAnniv::TDisplayAs CAgnAnniv::DisplayAs() const
	{ return (iDisplayAs); }


/**
 * Retrieves the anniversary entrys has base year property.
 *
 * This property indicates whether the anniversary has a base year and
 * does not start at the default year 1980.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if anniversary has a base year,
 *            <code>EFalse</code> if not.
 */
inline TBool CAgnAnniv::HasBaseYear() const
	{ return (iHasBaseYear); }

inline void CAgnAnniv::SetHasBaseYear(TBool aHasBaseYear)
	{ iHasBaseYear = aHasBaseYear; }


//------------------------------ CAgnTodo -------------------------------------------
/**
 * Returns the ID of the to-do list to which the to-do entry belongs, as
 * set by <code>SetTodoListId()</code>.
 *
 * @returns   "TAgnTodoListId"
 *            Identifies the to-do list to which the entry belongs.
 */
inline TAgnTodoListId CAgnTodo::TodoListId() const
	{ return (iBasicTodo.TodoListId()); }

/**
 * Returns how the to-do entrys due date should be displayed, as set by
 * <code>SetDisplayDueDateAs()</code>.
 *
 * By default, the due date is displayed as <code>EAutomatic</code>.
 *
 * @returns   "TDisplayDueDateAs"
 *            Indicates how the due date should be displayed.
 */
inline CAgnTodo::TDisplayDueDateAs CAgnTodo::DisplayDueDateAs() const
	{ return (iDisplayDueDateAs); }

/**
 * Returns the priority of a to-do entry as set by
 * <code>SetPriority()</code>.
 *
 * The default value is zero.
 *
 * @returns   "TUint"
 *            The priority of the to-do entry.
 */
inline TUint CAgnTodo::Priority() const
	{ return (iBasicTodo.Priority()); }

/**
 * Returns the to-do entrys duration, i.
 *
 * e. the number of days between the start date and the due date. This
 * function can be called on an entry if it is not repeating or on an
 * individual instance if the entry is repeating. If the duration has not
 * been set, this function returns zero.
 *
 * @returns   "TTimeIntervalDays"
 *            The to-do entrys or instances duration.
 */
inline TTimeIntervalDays CAgnTodo::Duration() const
	{ return (iBasicTodo.Duration()); }

/**
 * Returns the entry details specific to the to-do entry, 
 * e.g. the due and crossed out dates and the display time. Note that these
 * details should normally be set and retrieved using other functions in
 * this class.
 *
 * @returns   "TAgnBasicTodo&"
 *            The to-do specific entry details.
 */
inline const TAgnBasicTodo& CAgnTodo::BasicTodo() const
	{ return (iBasicTodo); }

/**
 * Retrieves whether the alarm date is set relative to the entrys due
 * date as set by <code>SetAlarmFromDueDate()</code>.
 *
 * By default, the alarm is set relative to the due date.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if an alarm has been set from the
 *            to-do entrys due date, <code>EFalse</code> if not.
 */
inline TBool CAgnTodo::IsAlarmSetFromDueDate() const
	{ return (iBasicTodo.IsAlarmSetFromDueDate()); }

/**
 * Retrieves whether the alarm date is set relative to the entrys start
 * date as set by <code>SetAlarmFromStartDate()</code>.
 *
 * By default, the alarm is set relative to the due date.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if an alarm has been set from the
 *            to-do entrys start date, <code>EFalse</code> if not.
 */
inline TBool CAgnTodo::IsAlarmSetFromStartDate() const
	{ return (iBasicTodo.IsAlarmSetFromStartDate()); }



