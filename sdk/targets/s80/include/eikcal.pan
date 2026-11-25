// EIKCAL.PAN
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCALPAN__)
#define __EIKCALPAN__

enum TEikCalendarPanic
	{
	EEikPanicCalendarDivideTestCodeFailed,
	EEikPanicCalendarBadNumMonths,
	EEikPanicCalendarNoTextSeparatingYearRange,
	EEikPanicCalendarCannotDisplayAllMonths,
	EEikPanicCalendarBadMinimumAndMaximum,
	EEikPanicCalendarBadStartMonth1,
	EEikPanicCalendarBadStartMonth2,
	EEikPanicCalendarBadSize,
	EEikPanicCalendarBadComponentControlIndex,
	EEikPanicCalendarNoControlContext,
	EEikPanicCalendarBadRowOrColumn,
	EEikPanicCalendarBadRule1,
	EEikPanicCalendarBadRule2,
	EEikPanicCalendarCannotAlterCursor1,
	EEikPanicCalendarCannotAlterCursor2,
	EEikPanicCalendarCannotAlterCursor3,
	EEikPanicCalendarNotFocused,
	EEikPanicCalendarShouldHaveCompletedDrawingDayMatrix,
	EEikPanicCalendarBadRangeOfColumns,
	EEikPanicCalendarBadDivisor,
	EEikPanicCalendarDialogBadResourceId,
	EEikPanicCalendarDialogBadButtonId
	};

GLREF_C void Panic(TEikCalendarPanic aPanic);

#endif

