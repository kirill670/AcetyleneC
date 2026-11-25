//
// ARITHMETICALCAL.H
//
// Copyright (c) 2000 Symbian Ltd. All rights reserved
//
#ifndef __ARITHMETICALCAL_H__
#define __ARITHMETICALCAL_H__

// System includes
#include <e32std.h>

// User includes
#include "calconvcalendar.h"


class TArithmeticalCalendar : public TCalendar  
	{
public:
	TArithmeticalCalendar();

protected:
	TInt DayMonthInYear(const TInt) const;
	TInt DaysMonthsElapsed(const TInt) const;
	virtual TBool IsLeapYear(const TInt) const;
	};


#endif