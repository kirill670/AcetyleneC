/*
* ==============================================================================
*  Name        : cknctbar.h
*  Part of     : CKON
*  Interface   : Calendar Pop-out API
*  Description : MEikCalendarObserver class observes the calendar.
*				 CEikCalendarBC class is created for binary compatibility purposes.
*				 CEikCalendar class creates a calendar (in a month view) 
*					and handles calendar events.	
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


#ifndef EIKCAL_H
#define EIKCAL_H

// INCLUDES
#include <eikbctrl.h>
#include <eikscbut.h>
#include <eikcmbut.h>
#include <eikcmobs.h>

// FORWARD DECLARATIONS
class CEikButtonGroupContainer;
class CCknCallHeaderButton;

// CLASS DECLARATIONS
/**
*  MEikCalendarObserver class observes the calendar.
*  It gets and sets the appropriate dates for and from the calendar.
*
*  @since Series90 1.0
*/
class MEikCalendarObserver
	{
	public:
		/**
		* Gets minimum, maximum and initial date for the calendar.
		* @param aMinimumDate Minimum date.
		* @param aMaximumDate Maximum date.
		* @param aInitialDate Initial date.
		* <BR><B>Type of return value:</B> void
		*/
		virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(TTime& aMinimumDate, TTime& aMaximumDate, TTime& aInitialDate) const=0;
		/**
		* Sets the date from the calendar and draws it.
		* @param aDate Date to be set to.
		* <BR><B>Type of return value:</B> void
		*/
		virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate)=0;
	};

/**
*  CEikCalendarBC class is created for binary compatibility purposes.
*  Please use CEikCalendar.
*
*  This class should not be used by user clients. Use CEikCalendar.
*  @deprecated
*  Link against EIKCTL.LIB
*/
class CEikCalendarBC : public CEikBorderedControl, public MCoeControlObserver, public MEikCommandObserver
	{
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikCalendarBC();
		/**
		* Sets calendar observer.
		* @param aObserver Calendar observer.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetCalendarObserver(MEikCalendarObserver* aObserver);
		/**
		* Launches calendar (month view).
		* @param aResourceId Resource id.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ExecuteLD(TInt aResourceId);
	
		/**
		* Destructor.
		*/
		IMPORT_C virtual ~CEikCalendarBC();
		/**
		* Sets the range of dates displayable on this calendar control.
		* @param aMinimumDate New minimum date.
		* @param aMaximumDate New maximum date.
		* @param aMonthsWereReshuffled On return, indicates whether the currently selected date had to be moved
		* 			to be within the bounds set by this function.
		* @param aMonthsWereReshuffled Whether new dates are different from the old ones.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetMinimumAndMaximum(const TTime& aMinimumDate, const TTime& aMaximumDate, TBool* aMonthsWereReshuffled=NULL);
		/**
		* Gets minimum and maximum dates.
		* @param aMinimumDate Minimum date.
		* @param aMaximumDate Maximum date.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void GetMinimumAndMaximum(TTime& aMinimumDate, TTime& aMaximumDate) const;
		/**
		* Sets the currently selected date.
		* @param aDate New date.
		* @param aDoNotReshuffleMonthsUnlessNecessary If <code>ETrue</code>,
		*		calculates offset from start (old) month to current (new)one.
		* @param aMonthsWereReshuffled On return, indicates whether the currently selected date had to be moved
		* 			to be within the bounds set by this function.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetDateL(const TTime& aDate, TBool aDoNotReshuffleMonthsUnlessNecessary, TBool* aMonthsWereReshuffled=NULL);
		/**
		* Gets the current date.
		* @return Current date.
		* <BR><B>Type of return value:</B> TTime
		*/
		IMPORT_C TTime Date() const;
	public: 
		/**
		* From CCoeControl.
		* Offers a key event.
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
	// other functions
		void BaseConstructL();
		void ReadResourceL(TInt aResourceId);
		void ConstructMonthViewL(TInt aResourceId,const TTime& aInitialDate);
	//
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
		void DrawTitle(CWindowGc& aGc) const;
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
		void UpdateValuesFromSkinL();
		void SetCalendarSizeVariables();
	private: // from CCoeControl
		IMPORT_C virtual void Reserved_1();
		IMPORT_C void Reserved_2();
	private:
		TDay iStartOfWeek;
		TUint32 iWorkDays;
		TText iDayNameInitials[__Align(7)]; //NOT USED BC
		TInt iDayOfToday;
		TInt iMonthOfToday;
		TInt iYearOfToday;
		TUint32 iFlags;
		TInt iNumMonths;
		TInt iNumMonthsPerRowOfMonths; //NOT USED BC
		TInt iVerticalSpaceAboveYear;
		TInt iVerticalSpaceBetweenYearAndTopRowOfMonths;
		TInt iVerticalSpaceBetweenEachRowOfMonths; //NOT USED BC
		TInt iVerticalSpaceBeneathBottomRowOfMonths;
		TInt iHorizontalSpaceOnEachSideOfMonthMatrix;
		TInt iHeightOfDayNumber; // was TInt iHorizontalSpaceBetweenEachColumnOfMonths; //NOT USED BC
		TInt iHeightOfWeekNumber;// was TInt iVerticalSpaceBetweenMonthNameAndDayNameInitials; //NOT USED BC
		TInt iVerticalSpaceBetweenDayNameInitialsAndTopRowOfDays;
		TInt iVerticalSpaceBetweenEachRowOfDays;
		TInt iHorizontalSpaceBetweenEachColumnOfDays;
		TTime iMinimumDate;
		TTime iMaximumDate;
		TInt iCurrentDay;
		TInt iOffsetFromStartMonthToCurrentMonth;
		TMonth iStartMonth;
		TInt iStartYear;
		CDesCArray* iDayNameAbbreviations; // was HBufC* iTextSeparatingYearRange;
		HBufC* iWeekHeading;
	// generated from above and stored for convenience
		TInt iHeightOfWeekDayAbbreviations;
		TInt iWidthOfWeek;
		TSize iSizeOfSingleDayNumber; 
		TSize iSizeOfSingleMonth; 
		TSize iMinButtonSize;
		TSize iCalendarSize;
	//
		CWsBitmap* iBitmap;
	//
		CFbsBitmap* iBrushBitmap; //NOT USED BC
	// Mixin 
		MEikCalendarObserver* iCalendarObserver;
		TTime* iInitialDate;
/**
*  TEikCalendarExt class is a Calendar extension class.
*
*/
	class CEikCalendarExt : public CBase
		{
	public:
		void ConstructL();
		~CEikCalendarExt();

		CEikButtonGroupContainer *iButtonGroupContainer;
		TPoint iPreviousCursorPosition;
		TTime iCurrentTime;
		TTime iPreviousTime;
		CCknCallHeaderButton* iNavButtons[2]; //temp fudge to avoid name clash, awaiting new fixed eikcal from teleca
		const CFbsBitmap* iBackgroundBitmap;
		const CFbsBitmap* iTodayBitmap;
		const CFbsBitmap* iBackgroundBitmapMask;
		const CFbsBitmap* iTodayBitmapMask;
		TBool iValidDate;
		TInt iHeightOfYearText;
		TRgb iHighlightedTextColour;
		TRgb iTodayTextColour;
		TRgb iNormalTextColour;
		TPoint iNullPoint;
		};
		CEikCalendarExt* iCalExt;
	};

/**
*  CEikCalendar class creates a calendar (in a month view) 
*  and handles calendar events (gets and sets appropriate dates for and from the calendar).
*
*  Link against EIKCTL.LIB
*  @since Series90 1.0
*/
class CEikCalendar : public CEikCalendarBC, public MCoeControlContext
	{
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikCalendar();
	private: //from MCoeControlContext
		void PrepareContext(CWindowGc& aGc) const;
	};


#endif	// EIKCAL_H

// End of File
