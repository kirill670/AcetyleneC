// AGMIDS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// ----------------------------------- TAgnId ----------------------------------------------
/**
 * Tests whether this ID is less than another.
 *
 * @param     "TAgnId aId"
 *            The ID to compare with this one.
 * @returns   "TBool"
 *            True if this ID is less than <code>aId</code>. False
 *            if not.
 */
inline TBool TAgnId::operator<(TAgnId aId) const
	{ return (iId < aId.iId);}

/**
 * Tests whether this ID is greater than another.
 *
 * @param     "TAgnId aId"
 *            The ID to compare with this one.
 * @returns   "TBool"
 *            True if this ID is greater than <code>aId</code>.
 *            False if not.
 */
inline TBool TAgnId::operator>(TAgnId aId) const
	{ return (iId > aId.iId);}

/**
 * Gets the ID value.
 *
 * @returns   "TAgnId"
 *            The ID value.
 */
inline TAgnId TAgnId::Id() const
	{ return (iId); }

inline void TAgnId::SetId(TAgnId aId)
	{ iId=aId.iId; }

inline TAgnId::TAgnId(TUint aId)
	{ iId = aId; }

inline TStreamId TAgnId::StreamId() const
	{ return (iId & KMaskStreamIdValue); }

inline TUint TAgnId::Value() const
	{ return (iId); }



// ------------------------------- TAgnInstanceId -----------------------------------------
/**
 * Gets the date of the instance ID.
 *
 * @returns   "TAgnDate"
 *            The date of the instance ID.
 */
inline TAgnDate TAgnInstanceId::Date() const
	{ return (iDate); }

/**
 * Sets the date of the instance ID.
 *
 * @param     "TAgnDate aDate"
 *            The date of the instance ID.
 */
inline void TAgnInstanceId::SetDate(TAgnDate aDate)
	{ iDate=aDate; }

/**
 * Tests whether the instance ID is NULL.
 *
 * @returns   "TBool"
 *            True if the instance ID is NULL, false if not.
 */
inline TBool TAgnInstanceId::IsNullInstanceId() const
	{ return (iDate==AgnDateTime::NullDate()); }

/**
 * Sets both the ID and date.
 *
 * @param     "TAgnEntryId aId"
 *            The entry ID.
 * @param     "TAgnDate aDate"
 *            The date.
 */	
inline void TAgnInstanceId::SetIdAndDate(TAgnEntryId aId,TAgnDate aDate)
	{ iId=aId.Value(); iDate=aDate; }




// ------------------------------- TAgnInstanceDateTimeId ------------------------
/**
 * Sets the start date of the current ID.
 *
 * @param     "TAgnDate aDate"
 *            The start date.
 */
inline void TAgnInstanceDateTimeId::SetStartDate(TAgnDate aDate) 
	{ iStartDateTime.SetDate(aDate); }

/**
 * Sets the end date of the current ID.
 *
 * @param     "TAgnDate aDate"
 *            The end date.
 */
inline void TAgnInstanceDateTimeId::SetEndDate(TAgnDate aDate)
	{ iEndDateTime.SetDate(aDate); }

/**
 * Sets the start time of the current ID.
 *
 * @param     "TAgnTime aTime"
 *            The start time.
 */
inline void TAgnInstanceDateTimeId::SetStartTime(TAgnTime aTime)
	{ iStartDateTime.SetTime(aTime); }

/**
 * Sets the end time of the current ID.
 *
 * @param     "TAgnTime aTime"
 *            The end time.
 */
inline void TAgnInstanceDateTimeId::SetEndTime(TAgnTime aTime) 
	{ iEndDateTime.SetTime(aTime); }


// ----------------------------------- TAgnUniqueId -------------------------------------------
//inline TUint TAgnUniqueId::operator++()
//	{ return (++iUId); } 

//inline TUint TAgnUniqueId::operator--() 
//	{ return (--iUId); } 

/**
 * Compares two unique IDs for equivalence.
 *
 * @param     "TAgnUniqueId aUId"
 *            The unique ID to compare with this one.
 * @returns   "TBool"
 *            True if <code>aUId</code> is equal to this ID. False
 *            if they are different.
 */
inline TBool TAgnUniqueId::operator==(TAgnUniqueId aUId) const
	{ return (iUId==aUId.iUId); }

/**
 * Compares two unique IDs for inequality.
 *
 * @param     "TAgnUniqueId aUId"
 *            The unique ID to compare with this one.
 * @returns   "TBool"
 *            True if <code>aUId</code> is different from this ID.
 *            False if they are the same.
 */
inline TBool TAgnUniqueId::operator!=(TAgnUniqueId aUId) const
	{ return (iUId!=aUId.iUId); }

/**
 * Tests whether this unique ID value is less than another.
 *
 * @param     "TAgnUniqueId aUId"
 *            The unique ID to compare with this one.
 * @returns   "TBool"
 *            True if this unique ID value is less than
 *            <code>aUId</code>. False if not.
 */
inline TBool TAgnUniqueId::operator<(TAgnUniqueId aUId) const
	{ return (iUId < aUId.iUId);}

/**
 * Tests whether this unique ID value is greater than another.
 *
 * @param     "TAgnUniqueId aUId"
 *            The unique ID to compare with this one.
 * @returns   "TBool"
 *            True if this unique ID value is greater than
 *            <code>aUId</code>. False if not.
 */
inline TBool TAgnUniqueId::operator>(TAgnUniqueId aUId) const
	{ return (iUId > aUId.iUId);}

/**
 * Sets the unique ID value.
 *
 * @param     "TUint aUId"
 *            The new unique ID value.
 */
inline void TAgnUniqueId::SetId(TUint aUId)
	{ iUId=aUId; }

/**
 * Gets the unique ID value.
 *
 * @returns   "TUint"
 *            The unique ID value.
 */
inline TUint TAgnUniqueId::Id() const
	{ return (iUId); }

/**
 * Sets the unique ID value to zero.
 */
inline void TAgnUniqueId::SetNullId()
	{ iUId=0; }

/**
 * Returns whether the unique ID value has been set.
 *
 * @returns   "TBool"
 *            True if the ID value is zero. False if not.
 */
inline TBool TAgnUniqueId::IsNullId()
	{ return (iUId==0); }

// ----------------------------------- TAgnMapId ----------------------------------------------
template<class TypeId>
inline TypeId TAgnMapId<TypeId>::AgmId()	const
	{ return (iAgmId); }

template<class TypeId>
inline TAgnUniqueId TAgnMapId<TypeId>::UniqueId() const
	{ return (iUniqueId); }

template<class TypeId>
inline void TAgnMapId<TypeId>::SetAgmId(TypeId id)
	{ iAgmId=id; }

template<class TypeId>
inline void TAgnMapId<TypeId>::SetUniqueId(TAgnUniqueId uid)
	{ iUniqueId=uid; }
