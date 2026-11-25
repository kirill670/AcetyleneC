// AGMDATE.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//



// ---------------------------- TAgnDateTime -----------------------------------
inline TAgnDateTime::TAgnDateTime()
/** Constructs a TAgnDateTime object setting the date and time to NULL. */
	{ iDate=AgnDateTime::NullDate(); }

inline TAgnDateTime::TAgnDateTime(TAgnDate aDate,TAgnTime aTime)
/** Constructs a TAgnDateTime object setting the date and time to the values specified. */
	: iDate(aDate),iTime(aTime)
	{}
	
inline TAgnDateTime::TAgnDateTime(TAgnDate aDate)
/** Constructs a TAgnDateTime object setting the date, but leaving the time set to NULL. */
	: iDate(aDate),iTime(AgnDateTime::NullTime())
	{}

inline TAgnDate TAgnDateTime::Date() const
/** Gets the date.

@return The date. */
	{ return (iDate); }

inline TAgnTime TAgnDateTime::Time() const
/** Gets the time.

@return The time. */
	{ return (iTime); }

inline void TAgnDateTime::SetDate(TAgnDate aDate)
/** Sets the date.

@param aDate The new date. */
	{ iDate=aDate; }

inline void TAgnDateTime::SetTime(TAgnTime aTime)
/** Sets the time.

@param aTime The new time. */
	{ iTime=aTime; }

inline TAgnDateTime::operator TTime() const
/** Converts the stored date and time into a TTime object. */
	{ return (AgnDateTime::AgnDateTimeToTTime(*this)); }

inline TAgnDateTime::operator TAgnDate() const 
/** Gets the stored date value. */
	{ return (iDate); };


// ---------------------------- AgnDateTime ------------------------------------
//inline TTimeIntervalMinutes AgnDateTime::DefaultDisplayTime() 
//	{ return (NullTime()); }

inline TAgnDate AgnDateTime::MinDate()
/** Gets the minimum date value allowed for a TAgnDate.

This date marks the start of the agenda model's valid date range.

@return The agenda model's minimum date value. */
	{ return (0); }  	

inline TAgnDate AgnDateTime::MaxDate()
/** Gets the maximum date value allowed for a TAgnDate.

This date marks the end of the agenda model's valid date range.

@return The agenda model's maximum date value. */
	{ 
	return 44194;	
//	return ((TAgnDate)(((TTimeIntervalDays)MaxDateAsTTime().DaysFrom(MinDateAsTTime())).Int()));
	}

inline TAgnDate AgnDateTime::NullDate()
/** Gets a NULL date. 

This is used in the agenda model to indicate a date value 
which has not been set or which does not apply.

@return A NULL date. */
	{ return (0xFFFF); }	 // largest figure that can be stored in a TUint16

inline TAgnTime AgnDateTime::NullTime()
/** Gets a NULL time. 

This is used in the agenda model to indicate a time value 
which has not been set or which does not apply.

@return A NULL time. */
	{ return (0xFFFF); }

inline TUint AgnDateTime::MaxTime()
/** Gets the maximum time value for an agenda entry as a number of minutes from 
midnight.

@return The maximum time for an agenda entry (= 1439 minutes). */
	{ return 1439; }
//	{ return ((23 * 60) + 59); }

inline TTimeIntervalDays AgnDateTime::MinDateAsTTimeIntervalDaysFrom0AD()
/** Gets the minimum date allowed for agenda entries as a time interval in days 
from 0 AD nominal Gregorian.

@return The number of days between 0 AD nominal Gregorian and the agenda model's 
minimum date. */
	{ return 723192;}
//	{ return MinDateAsTTime().DaysFrom(TTime(0));}

inline TTimeIntervalDays AgnDateTime::MaxDateAsTTimeIntervalDaysFrom0AD()
/** Gets the maximum date allowed for agenda entries as a time interval in days 
from 0 AD nominal Gregorian.

@return The number of days between 0 AD nominal Gregorian and the agenda model's 
maximum date. */
	{ return 767386; }
//	{ return MaxDateAsTTime().DaysFrom(TTime(0)); }
