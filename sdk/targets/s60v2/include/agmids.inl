// AGMIDS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// ----------------------------------- TAgnId ----------------------------------------------
inline TBool TAgnId::operator<(TAgnId aId) const
/** Tests whether this ID is less than another.

@param aId The ID to compare with this one.
@return True if this ID is less than aId. False if not. */
	{ return (iId < aId.iId);}

inline TBool TAgnId::operator>(TAgnId aId) const
/** Tests whether this ID is greater than another.

@param aId The ID to compare with this one.
@return True if this ID is greater than aId. False if not. */
	{ return (iId > aId.iId);}

inline TAgnId TAgnId::Id() const
/** Gets the ID value.

@return The ID value. */
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
inline TAgnDate TAgnInstanceId::Date() const
/** Gets the date component of the instance ID.

@return The date component of the instance ID. */
	{ return (iDate); }

inline void TAgnInstanceId::SetDate(TAgnDate aDate)
/** Sets the date component of the instance ID.

@param aDate The new date. */
	{ iDate=aDate; }

inline TBool TAgnInstanceId::IsNullInstanceId() const
/** Tests whether the instance ID is NULL.

@return True if the instance ID is NULL, false if not. */
	{ return (iDate==AgnDateTime::NullDate()); }

inline void TAgnInstanceId::SetIdAndDate(TAgnEntryId aId,TAgnDate aDate)
/** Sets the instance ID's ID and date components.

@param aId The entry ID.
@param aDate The date. */
	{ iId=aId.Value(); iDate=aDate; }




// ------------------------------- TAgnInstanceDateTimeId ------------------------
inline void TAgnInstanceDateTimeId::SetStartDate(TAgnDate aDate) 
/** Sets the start date of the ID.

@param aDate The start date. */
	{ iStartDateTime.SetDate(aDate); }

inline void TAgnInstanceDateTimeId::SetEndDate(TAgnDate aDate)
/** Sets the end date of the ID.

@param aDate The end date. */
	{ iEndDateTime.SetDate(aDate); }

inline void TAgnInstanceDateTimeId::SetStartTime(TAgnTime aTime)
/** Sets the start time of the ID.

@param aTime The start time. */
	{ iStartDateTime.SetTime(aTime); }

inline void TAgnInstanceDateTimeId::SetEndTime(TAgnTime aTime) 
/** Sets the end time of the ID.

@param aTime The end time. */
	{ iEndDateTime.SetTime(aTime); }


// ----------------------------------- TAgnUniqueId -------------------------------------------
//inline TUint TAgnUniqueId::operator++()
//	{ return (++iUId); } 

//inline TUint TAgnUniqueId::operator--() 
//	{ return (--iUId); } 

inline TBool TAgnUniqueId::operator==(TAgnUniqueId aUId) const
/** Compares two unique IDs for equivalence.

@param aUId The unique ID to compare with this one.
@return True if aUId is equal to this ID. False if they are different. */
	{ return (iUId==aUId.iUId); }

inline TBool TAgnUniqueId::operator!=(TAgnUniqueId aUId) const
/** Compares two unique IDs for inequality.

@param aUId The unique ID to compare with this one.
@return True if aUId is different from this ID. False if they are the same. */
	{ return (iUId!=aUId.iUId); }

inline TBool TAgnUniqueId::operator<(TAgnUniqueId aUId) const
/** Tests whether this unique ID value is less than another.

@param aUId The unique ID to compare with this one.
@return True if this unique ID value is less than aUId. False if not. */
	{ return (iUId < aUId.iUId);}

inline TBool TAgnUniqueId::operator>(TAgnUniqueId aUId) const
/** Tests whether this unique ID value is greater than another.

@param aUId The unique ID to compare with this one.
@return True if this unique ID value is greater than aUId. False if not. */
	{ return (iUId > aUId.iUId);}

inline void TAgnUniqueId::SetId(TUint aUId)
/** Sets the unique ID value.

@param aUId The new unique ID value. */
	{ iUId=aUId; }

inline TUint TAgnUniqueId::Id() const
/** Gets the unique ID value.

@return The unique ID value. */
	{ return (iUId); }

inline void TAgnUniqueId::SetNullId()
/** Sets the unique ID value to zero. */
	{ iUId=0; }

inline TBool TAgnUniqueId::IsNullId()
/** Tests whether the unique ID value has been set.

@return True if the ID value is zero. False if not. */
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
