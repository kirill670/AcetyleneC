//
// CALENDAR.H
//
// Copyright (c) 2000 Symbian Ltd. All rights reserved
//
#ifndef __CALENDAR_H__
#define __CALENDAR_H__

// System includes
#include <e32std.h>
#include <e32def.h>

// Constants
const TInt KCalConvDayOffsetByOne = 1;
const TInt KCalConvMonthOffsetByOne = 1;
const TInt KCalConvYearOffsetByOne = 1;
const TReal KCalConvPointFive = 0.5;

class TCalendar
	{
public:
	TCalendar();
	TCalendar& operator=(const TCalendar& aTCal);
	TInt JulianDay();

protected:
	void Round(TInt& aRes, TReal& aNum) const;
	void Mod(TReal& aRes, const TReal& aAbscissa, const TReal& aDenominator) const;
	void Amod(TReal& aRes, const TReal& aAbscissa, const TReal& aDenominator) const;
	void Floor(TInt& aRes, const TReal& aNum) const;
	void Ceiling(TInt& aRes, const TReal& aNum) const;

protected:
	TReal iStartEpoch;
	TInt iDaysInNormYear;
	TReal iJulianDay;
	TInt iCycle;
	TInt iLeaps;
	TInt iOffset;
	TInt iStdYearMonth;
	};
#endif