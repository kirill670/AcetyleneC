//
// CALENDARCONVERTER.H
//
// Copyright (c) 2002 Symbian Ltd. All rights reserved
//

#ifndef __CALENDARCONVERTER_H__
#define __CALENDARCONVERTER_H__

// System includes
#include <e32std.h>
#include <e32base.h>

/**
	@since	6.1
	@public
	@class TChineseDate
	Dependencies : none
	Comments : Defines a single date in Chinese form (cycle, year, month, leapmonth and day)
	@lib	ccon.lib
*/
class TChineseDate  
	{
public:
	IMPORT_C TChineseDate();
	IMPORT_C TBool operator==(const TChineseDate& aDate) const;
public:
	TInt iCycle;
	TInt iYear;
	TInt iMonth;
	TBool iLeapMonth;
	TInt iDay;
	};

/**
	@since	6.1
	@public
	@class CChineseCalendarConverter
	Dependencies : none
	Comments : Converts between TDateTime and TChinese date formats in both directions
	@lib	ccon.lib
*/
class CChineseCalendarConverter : public CBase
	{
public:
	IMPORT_C static CChineseCalendarConverter* NewL();
/**
 * Fills a supplied TChineseDate using a supplied TDateTime
 *
 *
 * @since     6.1
 * @param     const TDateTime& aDateTime
 *            The TDateTime to use
 * @param     TChineseDate& aChineseDate
 *			  The TChineseDate to fill
 * @returns   void
 *            Leaves with KErrArgument if error
 */
	virtual void DateTimeToChineseL(const TDateTime& aDateTime, TChineseDate& aChineseDate)=0;

/**
 * Fills a supplied TDateTime using a supplied TChineseDate
 *
 *
 * @since     6.1
 * @param     const TChineseDate& aChineseDate
 *            The TChineseDate to use
 * @param     TDateTime& aDateTime
 *			  The TDateTime to fill
 * @returns   void
 *            Leaves with KErrArgument if error
 */
	virtual void ChineseToDateTimeL(const TChineseDate& aChineseDate, TDateTime& aDateTime)=0;

/**
 * Returns the range of dates the Chinese calendar converter can handle
 *
 * @since     6.1
 * @param     TDateTime& aLower
 *            The lower bound of the date range
 * @param     TDateTime& aUpper
 *			  The upper bound of the date range
 * @returns   void
 */
	virtual void DateRange(TDateTime& aLower, TDateTime& aUpper)=0;

/**
 * Returns the range of dates the Chinese calendar converter can handle
 *
 * @since     6.1
 * @param     TChineseDate& aLower
 *            The lower bound of the date range
 * @param     TChineseDate& aUpper
 *			  The upper bound of the date range
 * @returns   void
 */
	virtual void DateRange(TChineseDate& aLower, TChineseDate& aUpper)=0;
/**
 * Returns the result of the last calendar conversion as a Julian Date.
 *
 * @since     6.1
 * @returns   TRead - the Julian Date
 */
	virtual TReal JulianDate()=0;
	};
#endif
