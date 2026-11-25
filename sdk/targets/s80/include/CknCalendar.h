/*
* ==============================================================================
*  Name        : ckncalendar.h
*  Part of     : CKON
*  Interface   : 
*  Description : CCknCalendar constructs and initialises a new calendar control.
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef CKNCALENDAR_H
#define CKNCALENDAR_H

// INCLUDES
#include <cknbctrl.h>
#include <eikscbut.h>
#include <eikcmbut.h>
#include <eikcmobs.h>
#include <eikcal.h>
#include "CknCalendarNavigation.h"

const TInt KNumButtons=1;

// FORWARD DECLARATIONS
class CEikButtonGroupContainer;
class CCknDialogButton;
class CCknSkinBase;

/**
*  CCknCalendar constructs and initialises a new calendar control.
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/
class CCknCalendar : public CCknBorderedControl, public MCoeControlObserver, public MEikCommandObserver, public MCoeControlContext, public MCknCalendarNavigationObserver
	{
	public:

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CCknCalendar* NewL();

		/**
		* Registers a calendar observer.
		* 
		* @param aObserver The calendar observer, which is to observe this calendar.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetCalendarObserver(MEikCalendarObserver* aObserver);

		/**
		* Displays the calendar.
		* 
		* @param aResourceId The control resource to use when constructing the control.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ExecuteLD(TInt aResourceId);

		/**
		* Destructor.
		*/
		IMPORT_C virtual ~CCknCalendar();

		/**
		* Sets the range of dates displayable on this calendar control.
		* 
		* @param aMinimumDate New minimum date.
		* @param aMaximumDate New maximum date.
		* @param aMonthsWereReshuffled On return, indicates whether the currently selected date had
		* 			to be moved to be within the bounds set by this function
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetMinimumAndMaximum(const TTime& aMinimumDate, const TTime& aMaximumDate, TBool* aMonthsWereReshuffled=NULL);

		/**
		* Gets minimum and maximum dates.
		* 
		* @param aMinimumDate Minimum date.
		* @param aMaximumDate Maximum date.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void GetMinimumAndMaximum(TTime& aMinimumDate, TTime& aMaximumDate) const;

		/**
		* Sets the currently selected date.
		* 
		* @param aDate New current date for this calendar.
		* @param aDoNotReshuffleMonthsUnlessNecessary If <code>ETrue</code>,
		* 		calculates offset from start (old) month to current (new)one.
		* @param aMonthsWereReshuffled On return, indicates whether the currently selected date had to be moved
		* 			to be within the bounds set by this function.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetDateL(const TTime& aDate, TBool aDoNotReshuffleMonthsUnlessNecessary, TBool* aMonthsWereReshuffled=NULL);

		/**
		* Gets the current date.
		* 
		* @return Current date.
		* <BR><B>Type of return value:</B> TTime
		*/
		IMPORT_C TTime Date() const;
	public: 

		/**
		* From CCoeControl.
		* Handles key events.
		* @param aKeyEvent The key event.
		* @param aType The event type.
		* @return Indicates whether the key was consumed.
		* <BR><B>Type of return value:</B> TKeyResponse
		*/
		IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

		/**
		* From CCoeControl.
		* Returns the minimum size required by the control.
		* @return Minimum size.
		* <BR><B>Type of return value:</B> TSize
		*/
		IMPORT_C virtual TSize MinimumSize();

		/**
		* From CCoeControl.
		* Gets the list of logical colors employed in the drawing of the control,
		* paired with an explanation of how they are used. Appends the list to aColorUseList.
		* @param aColorUseList List of logical colours.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

		/**
		* From CCoeControl.
		* Handles a change to the control's resources which are shared across the environment.
		* @param aType The type of resource that has changed.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u

		/**
		* From MEikCommandObserver.
		* Processes a command.
		* @param aCommandId The command Id to process.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ProcessCommandL(TInt aCommandId); //from MEikCommandObserver
	private:
	enum TRule
		{
		ERuleAdjustRow,
		ERuleAdjustColumn
		};
	enum TDrawCursor
		{
		ECursorOff,
		ECursorOn
		};
	enum 
		{
		EFirstButton=0,
		ESecondButton=1
		};
	private:
	// framework
		IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
		IMPORT_C virtual void SizeChanged();
		IMPORT_C virtual TInt CountComponentControls() const;
		IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
		IMPORT_C virtual void Draw(const TRect& aRect) const;
		IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
		IMPORT_C TCoeInputCapabilities InputCapabilities() const;
	private:
	//from MCoeControlContext
		void PrepareContext(CWindowGc& aGc) const;
	//from MCknCalendarNavigationObserver
		void HandleCalendarNavigationControlEventL(CCknCalendarNavigation* aControl, TNavigationButtonEvent aEvent);
	private:
		CCknCalendar();
		void BaseConstructL();
		void ReadResourceL(TInt aResourceId);
		void ConstructMonthViewL(TInt aResourceId,const TTime& aInitialDate);
		void CheckDateIsWithinCalendarRangeL(const TTime& aDate);
		TTime Date(TInt aOffsetFromStartMonthToThisMonth, TInt aThisDay) const;
		TInt DayAtRowAndColumn(TInt aOffsetFromStartMonthToThisMonth, TInt aRow, TInt aColumn, TRule aRule) const;
		void IncrementStartMonth(TInt aIncrement);
		void MoveOneMonthToLeft(TInt& aOffsetFromOldStartMonthToNewCurrentMonth);
		void MoveOneMonthToRight(TInt& aOffsetFromOldStartMonthToNewCurrentMonth);
		void MoveOneMonthUp(TInt& aOffsetFromOldStartMonthToNewCurrentMonth);
		void MoveOneMonthDown(TInt& aOffsetFromOldStartMonthToNewCurrentMonth);
		void DrawCursor(CWindowGc& aGc,TDrawCursor aDrawCursor) const;
		void UpdateDisplayWithInfoMsgL(TBool aFullDraw, TInt aResourceId, const TTime& aTimeDate) const;
		TPoint CalendarPosition() const;
		void SetNavigatorTextL() const;
		void DrawMonth(CWindowGc& aGc) const;
		void DrawWeeks(CWindowGc& aGc) const;
		TInt WidthOfRangeOfColumnsOfDays(TInt aFirstColumn, TInt aLastColumn) const;
		void GetMonthData(TInt aOffsetFromStartMonthToThisMonth, TInt* aNumColumnsBlankAtStartOfTopRowOfDays, TInt* aNumDaysInThisMonth) const;
		void GetNearestDateFromPosition(const TPoint& aPosition, TInt& aOffsetFromStartMonthToThisMonth, TInt& aThisDay) const;

		static void Divide(TInt aDividend, TInt aDivisor, TInt* aResult, TInt* aRemainder);

		void DrawHighlights(CWindowGc& aGc) const;
		void CursorPosition(TPoint& aCursorPosition) const;
		TInt XPosOfWeekMatrix() const;
		TInt XPosOfMonthMatrix() const;
		TInt YPosOfMonthMatrix() const;
		void UpdateButtonTextL() const;
		void SetCalendarSizeVariables();
	private: // from CCoeControl
		IMPORT_C void Reserved_1();
		IMPORT_C void Reserved_2();
	private:
		TDay iStartOfWeek;
		TUint32 iWorkDays;
		CDesCArray* iDayNameAbbreviations;
		TInt iDayOfToday;
		TInt iMonthOfToday;
		TInt iYearOfToday;
		TUint32 iFlags;
		TInt iNumMonths;
		TInt iVerticalSpaceAboveYear;
		TInt iVerticalSpaceBetweenYearAndTopRowOfMonths;
		TInt iVerticalSpaceBeneathBottomRowOfMonths;
		TInt iHorizontalSpaceOnEachSideOfMonthMatrix;
		TInt iVerticalSpaceBetweenDayNameInitialsAndTopRowOfDays;
		TInt iVerticalSpaceBetweenEachRowOfDays;
		TInt iHorizontalSpaceBetweenEachColumnOfDays;
		TTime iMinimumDate;
		TTime iMaximumDate;
		TInt iCurrentDay;
		TInt iOffsetFromStartMonthToCurrentMonth;
		TMonth iStartMonth;
		TInt iStartYear;
		HBufC* iWeekHeading;
		CCknCalendarNavigation* iYearNavigator;
		CCknCalendarNavigation* iMonthNavigator;
		TInt iHeightOfWeekDayAbbreviations;
		TInt iHeightOfWeekNumber;
		TInt iHeightOfDayNumber;
		TInt iWidthOfWeek;
		TSize iSizeOfSingleDayNumber; 
		TSize iSizeOfSingleMonth; 
		TInt iHeightOfYearText;
		TSize iCalendarSize;
		CWsBitmap* iBitmap;
		MEikCalendarObserver* iCalendarObserver;
		TTime* iInitialDate;
		TPoint iPreviousCursorPosition;
		TTime iCurrentTime;
		TTime iPreviousTime;
		CCknDialogButton* iButtons[KNumButtons];
		TSize iMinButtonSize;
		TBool iValidDate;
		TAny* iReserved;
	};


#endif	// CKNCALENDAR_H

// End of File
