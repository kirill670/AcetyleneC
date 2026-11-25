// AGMDATE.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//



// ---------------------------- TAgnDateTime -----------------------------------
inline TAgnDateTime::TAgnDateTime()
	{ iDate=AgnDateTime::NullDate(); }

inline TAgnDateTime::TAgnDateTime(TAgnDate aDate,TAgnTime aTime)
	: iDate(aDate),iTime(aTime)
	{}
	
inline TAgnDateTime::TAgnDateTime(TAgnDate aDate)
	: iDate(aDate),iTime(AgnDateTime::NullTime())
	{}

inline TAgnDate TAgnDateTime::Date() const
	{ return (iDate); }

inline TAgnTime TAgnDateTime::Time() const
	{ return (iTime); }

inline void TAgnDateTime::SetDate(TAgnDate aDate)
	{ iDate=aDate; }

inline void TAgnDateTime::SetTime(TAgnTime aTime)
	{ iTime=aTime; }

inline TAgnDateTime::operator TTime() const
	{ return (AgnDateTime::AgnDateTimeToTTime(*this)); }

inline TAgnDateTime::operator TAgnDate() const 
	{ return (iDate); };


// ---------------------------- AgnDateTime ------------------------------------
//inline TTimeIntervalMinutes AgnDateTime::DefaultDisplayTime() 
//	{ return (NullTime()); }

/**
 * Gets the minimum date value allowed for <code>TAgnDate</code>s.
 *
 * This date marks the start of the agenda model's valid date range.
 *
 * @returns   "TAgnDate"
 *            The agenda model's minimum date value.
 */
inline TAgnDate AgnDateTime::MinDate()
	{ return (0); }  	

/**
 * Gets the maximum date value allowed for <code>TAgnDate</code>s.
 *
 * This date marks the end of the agenda model's valid date range.
 *
 * @returns   "TAgnDate"
 *            The agenda model's maximum date value.
 */
inline TAgnDate AgnDateTime::MaxDate()
	{ 
	return 44194;	
//	return ((TAgnDate)(((TTimeIntervalDays)MaxDateAsTTime().DaysFrom(MinDateAsTTime())).Int()));
	}

/**
 * Gets a NULL date.
 *
 * This is used in the agenda model to indicate a date value which has
 * not been set or which does not apply.
 *
 * @returns   "TAgnDate"
 *            A NULL date.
 */
inline TAgnDate AgnDateTime::NullDate()
	{ return (0xFFFF); }	 // largest figure that can be stored in a TUint16

/**
 * Gets a NULL time.
 *
 * This is used in the agenda model to indicate a time value which has
 * not been set or which does not apply.
 *
 * @returns   "TAgnTime"
 *            A NULL time.
 */
inline TAgnTime AgnDateTime::NullTime()
	{ return (0xFFFF); }

/**
 * Gets the maximum time value for an agenda entry as a number of minutes
 * from midnight.
 *
 * @returns   "TUint"
 *            Maximum time for an agenda entry (= 1439 minutes).
 */
inline TUint AgnDateTime::MaxTime()
	{ return 1439; }
//	{ return ((23 * 60) + 59); }

/**
 * Gets the minimum date allowed for agenda entries as a time interval in
 * days from 0 AD nominal Gregorian.
 *
 * @returns   "TTimeIntervalDays"
 *            The number of days between 0 AD nominal Gregorian and
 *            the agenda model's minimum date.
 */
inline TTimeIntervalDays AgnDateTime::MinDateAsTTimeIntervalDaysFrom0AD()
	{ return 723192;}
//	{ return MinDateAsTTime().DaysFrom(TTime(0));}

/**
 * Gets the maximum date allowed for agenda entries as a time interval in
 * days from 0 AD nominal Gregorian.
 *
 * @returns   "TTimeIntervalDays"
 *            The number of days between 0 AD nominal Gregorian and
 *            the agenda model's maximum date.
 */
inline TTimeIntervalDays AgnDateTime::MaxDateAsTTimeIntervalDaysFrom0AD()
	{ return 767386; }
//	{ return MaxDateAsTTime().DaysFrom(TTime(0)); }
