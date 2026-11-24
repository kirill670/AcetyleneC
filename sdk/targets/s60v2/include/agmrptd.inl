// AGMRPTD.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if defined(_DEBUG)
#include <agmutil.h> // Panic called in debug builds
#endif


// ------------------------------ TAgnRpt -------------------------------------------
inline TAgnDate TAgnRpt::StartDateAsAgnDate() const
/** Gets the repeat's start date as an agenda date.

@return The start date. */
	{ return (iStartDate); }

inline TAgnDate TAgnRpt::EndDateAsAgnDate() const
/** Gets the repeat's end date as an agenda date.

@return The end date. */
	{ return (iEndDate); }

inline void TAgnRpt::SetStartDate(TAgnDate aStartDate)
/** Sets the repeat's start date.
	
@param aStartDate The start date. */
	{ iStartDate=aStartDate; }

inline void TAgnRpt::SetEndDate(TAgnDate aEndDate)
/** Sets the repeat's end date.

@param aEndDate The end date. */
	{ iEndDate=aEndDate; }

inline TInt TAgnRpt::Interval() const
/** Gets the repeat interval.

@return The interval. */
	{ return (iInterval); }

inline TBool TAgnRpt::DisplayNextOnly() const
/** Tests whether the 'display next only' flag is set.

@return True if 'display next only' is set, otherwise False. */
	{ return (iDisplayNextOnly); }

inline TBool TAgnRpt::RepeatForever() const
/** Tests whether the 'repeat forever' flag is set.

@return True if repeat forever is set, otherwise False. */
	{ return (iRepeatForever); }

inline void TAgnRpt::SetDisplayNextOnly(TBool aDisplayNextOnly)
/** Sets a flag which indicates whether views should display the next 
repeat instance only.

@param aDisplayNextOnly True = display next only, False = do not display next 
only. */
	{ iDisplayNextOnly=(TUint8)!!aDisplayNextOnly; }

inline void TAgnRpt::SetInterval(TUint aInterval)
/** Sets the repeat interval. 

This is a number of days for a daily repeat, a number of weeks for a 
weekly repeat, etc. 

@param aInterval The interval. */
	{ iInterval=(TUint16)aInterval; }




// ---------------------------- TAgnDailyRpt--------------------------------------
//inline TAgnDailyRpt::TAgnDailyRpt(const TAgnRpt& aRpt)
//	: TAgnRpt(aRpt)
//	{}



// ------------------------------ TAgnWeeklyRpt -------------------------------------
//inline TAgnWeeklyRpt::TAgnWeeklyRpt(const TAgnRpt& aRpt)
//	: TAgnRpt(aRpt)
//	{}

inline void TAgnWeeklyRpt::ClearDays()
/** Clears all the weekly repeat days. */
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

inline void TAgnMonthlyByDatesRpt::ClearAllDates()
/** Clears all the monthly repeat dates. */
	{ iMonthlyRptDates=0; }


// --------------------------- CAgnRptDef -----------------------------------
inline CAgnRptDef::CAgnRptDef()
	{
	}

inline CAgnRptDef::TType CAgnRptDef::Type() const
/** Gets the repeat definition's type, as set by SetDaily(), SetWeekly() etc.

@return The repeat definition's type. */
	{ return (iType); }

inline const TAgnRpt* CAgnRptDef::RptDef() const 
/** Gets a pointer to the repeat details.

@return Pointer to the repeat details. */
	{ return (iRpt); }

inline const CAgnExceptionList* CAgnRptDef::Exceptions() const
/** Gets a pointer to the repeat definition's exception list.

@return Pointer to the exception list. */
	{ return (iExceptions); }
