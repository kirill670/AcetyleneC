// AGMRPTD.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if defined(_DEBUG)
#include <agmutil.h> // Panic called in debug builds
#endif


// ------------------------------ TAgnRpt -------------------------------------------
/**
 * Returns the start date as an agenda date.
 *
 * @returns   "TAgnDate"
 *            The start date.
 */
inline TAgnDate TAgnRpt::StartDateAsAgnDate() const
	{ return (iStartDate); }

/**
 * Returns the end date as an agenda date.
 *
 * @returns   "TAgnDate"
 *            The end date.
 */
inline TAgnDate TAgnRpt::EndDateAsAgnDate() const
	{ return (iEndDate); }

/**
 * Sets the start date for this repeat.
 *
 * @param     "TAgnDate aStartdate"
 *            The start date.
 */
inline void TAgnRpt::SetStartDate(TAgnDate aStartDate)
	{ iStartDate=aStartDate; }

/**
 * Sets the end date for this repeat.
 *
 * @param     "TAgnDate aEndDate"
 *            <code>The end date.</code>
 */
inline void TAgnRpt::SetEndDate(TAgnDate aEndDate)
	{ iEndDate=aEndDate; }

/**
 * Returns the repeat interval.
 *
 * @returns   "TInt"
 *            The interval.
 */
inline TInt TAgnRpt::Interval() const
	{ return (iInterval); }

/**
 * Returns whether the display next only flag is set.
 *
 * @returns   "TBool"
 *            True if display is next only, otherwise False.
 */
inline TBool TAgnRpt::DisplayNextOnly() const
	{ return (iDisplayNextOnly); }

/**
 * Returns whether the repeat forever flag is set.
 *
 * @returns   "TBool"
 *            True if repeat forever is set, otherwise False.
 */
inline TBool TAgnRpt::RepeatForever() const
	{ return (iRepeatForever); }

/**
 * Sets the flag which is used to indicate whether views should display
 * the next repeat instance only.
 *
 * @param     "TBool aDisplayNextOnly"
 *            True = display next only, False = do not display next
 *            only.
 */
inline void TAgnRpt::SetDisplayNextOnly(TBool aDisplayNextOnly)
	{ iDisplayNextOnly=(TUint8)!!aDisplayNextOnly; }

/**
 * Sets the repeat interval.
 *
 * This is a number of days for a daily repeat, a number of weeks for a
 * weekly repeat , etc.
 *
 * @param     "TUint aInterval"
 *            The interval.
 */
inline void TAgnRpt::SetInterval(TUint aInterval)
	{ iInterval=(TUint16)aInterval; }




// ---------------------------- TAgnDailyRpt--------------------------------------
//inline TAgnDailyRpt::TAgnDailyRpt(const TAgnRpt& aRpt)
//	: TAgnRpt(aRpt)
//	{}



// ------------------------------ TAgnWeeklyRpt -------------------------------------
//inline TAgnWeeklyRpt::TAgnWeeklyRpt(const TAgnRpt& aRpt)
//	: TAgnRpt(aRpt)
//	{}

/**
 * Clears all the weekly repeat days.
 */
inline void TAgnWeeklyRpt::ClearDays()
	{ iWeeklyRptDays=0; }



// ------------------------------ TAgnMonthlyRpt -------------------------
inline TAgnMonthlyRpt::TAgnMonthlyRpt(const TAgnRpt& aRpt)
	: TAgnRpt(aRpt)
	{}


// ----------------------- TAgnMonthlyByDaysRpt --------------------------------
//inline TAgnMonthlyByDaysRpt::TAgnMonthlyByDaysRpt(const TAgnRpt& aRpt)
//	: TAgnMonthlyRpt(aRpt)
//	{}



// ------------------------------- TAgnMonthlyByDatesRpt ----------------------------
//inline TAgnMonthlyByDatesRpt::TAgnMonthlyByDatesRpt(const TAgnRpt& aRpt)
//	: TAgnMonthlyRpt(aRpt)
//	{}

/**
 * Clears all the monthly repeat dates.
 */
inline void TAgnMonthlyByDatesRpt::ClearAllDates()
	{ iMonthlyRptDates=0; }


// --------------------------- CAgnRptDef -----------------------------------
inline CAgnRptDef::CAgnRptDef()
	{
	}

/**
 * Returns the repeat definitions type, as set by
 * <code>SetDaily()</code>, <code>SetWeekly()</code> etc.
 *
 * @returns   "TType"
 *            The repeat definitions type.
 */
inline CAgnRptDef::TType CAgnRptDef::Type() const
	{ return (iType); }

/**
 * Returns a pointer to the repeat details.
 *
 * @returns   "TAgnRpt*"
 *            Pointer to the repeat details.
 */
inline const TAgnRpt* CAgnRptDef::RptDef() const 
	{ return (iRpt); }

/**
 * Returns a pointer to the repeat definitions exception list.
 *
 * @returns   "CAgnExceptionList*"
 *            Pointer to the exception list.
 */
inline const CAgnExceptionList* CAgnRptDef::Exceptions() const
	{ return (iExceptions); }
