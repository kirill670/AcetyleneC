// EIKCAL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef EIKCAL_H__
#define EIKCAL_H__

#include <eikbctrl.h>
#include <eikscbut.h>
#include <eikcmbut.h>
#include <eikchlst.h>

#include <eikctl.rsg>

/**
 * @short The observer mixin class for a Calendar, required to get information from the Calendar.
 * @see CEikCalendar
 * @since Er5U
 */
class MEikCalendarObserver
	{
public:
	virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const=0;
	virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate)=0;
	};

/**
 * @short Any real implmentation of the CEikCalendar must inherit from this base class.
 * @see CEikCalendar
 * @since v6.1
 */
class CEikCalendarBase : public CEikBorderedControl
	{
public:
	virtual void SetCalendarObserver(MEikCalendarObserver* aObserver) =0;
	virtual void ExecuteLD() =0;

	virtual void CEikCalendarBase_Reserved1() =0;
	virtual void CEikCalendarBase_Reserved2() =0;
private:
	TInt iSpare;
	};

/**
 * The CEikCalendar is just a wrapper class for a real calendar. This class will
 * start a Gregorian Calendar (default, implemented in CQikCalendar) but might also 
 * start a Lunar Calendar on a chinese device. If only a Gregorian Calendar is wanted,
 * the CQikCalendar should get used. This control is only derived from a CCoeControl
 * to be able to construct it by Type.
 * @short A standard control that displays a calendar.
 * @see CQikCalendar 
 * @since Er5U
 */
class CEikCalendar : public CEikBorderedControl
	{
public:
	IMPORT_C CEikCalendar();
	IMPORT_C ~CEikCalendar();
	IMPORT_C void SetCalendarObserver(MEikCalendarObserver* aObserver);
	IMPORT_C void ExecuteLD(TInt aDepricatedArgument=R_EIK_ONE_MONTH_CALENDAR);

	IMPORT_C void CreateCalendarByTypeL();
	IMPORT_C TBool CreateCalendarByTypeL(TInt aCalendarControlId);
	IMPORT_C CEikCalendarBase* GetCalendar() const;
	IMPORT_C static void SetCalendarTypeInFileL(TInt aCalendarControlId);
	IMPORT_C static TInt GetCalendarTypeFromFileL();

private:
	TInt GetCalendarTypeFromFileOrResourceL();
	void CorrectCalendarTypeInFileL();
	void SetCalendarTypeInFileIsOkL();

private:
	CEikCalendarBase*		iCalendar;
	MEikCalendarObserver*	iObserver;

	TInt iSpares[3];
	};

#endif
