/*
* ==============================================================================
*  Name        : ckncalendarnavigation.h
*  Part of     : CKON
*  Interface   : ?Interface_category, ?Interface_name
*  Description : MCknCalendarNavigationObserver class is an interface class
*				 that observes navigation events.
*				 CCknCalendarNavigation class is used to display the text of a month 
*				 or year with increment/decrement navigation arrows.
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


#ifndef CKNCALENDARNAVIGATION_H
#define CKNCALENDARNAVIGATION_H

// INCLUDES
#include <cknbctrl.h>
#include <gulcolor.h>

// FORWARD DECLARATIONS
class CCknCalendarNavigation;
class CCknSkinBase;

/**
*  MCknCalendarNavigationObserver class is an interface class 
*  that observes navigation events.
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/

class MCknCalendarNavigationObserver
	{
	public:
	enum TNavigationButtonEvent
		{
		ETapNone = 0,
		ETapLeft,
		ETapRight
		};
	public:

		/**
		* Handles calendar navigation control event.
		* 
		* @param aControl Calendar navigation control.
		* @param aEvent The button event.
		* <BR><B>Type of return value:</B> void
		*/
		virtual void HandleCalendarNavigationControlEventL(CCknCalendarNavigation* aControl, TNavigationButtonEvent aEvent)=0;
	};

/**
*  This class is used to display the text of a month or year with 
*  increment/decrement navigation arrows.
*  If the navigation arrows are pressed, the control reports the navigation event to its observer.
*  The observer is responsible for setting/updating the text in the control when navigation events occur.
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/
class CCknCalendarNavigation : public CCknBorderedControl
	{
	public:
		~CCknCalendarNavigation();
		static CCknCalendarNavigation* NewL(const CCoeControl& aContainer, const TDesC& aText);
		void SetTextL(const TDesC& aText);
		//const TDesC* Text( );
		void SetObserver(MCknCalendarNavigationObserver* aObserver);
		void SetTextWidthInPixels(TInt aWidth);
		void SetFont(const CFont* aFont);
		void SetTextColor(TLogicalColor aColor);
		void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	// From CCoeControl
		TSize MinimumSize();
protected: 
		CCknCalendarNavigation();
		// From CCoeControl
		void Draw(const TRect& aRect) const;
	private:
		void ConstructL(const CCoeControl& aContainer, const TDesC& aText);
		const CFont* Font() const;
	private:
		HBufC* iText;					// text
		const CFont* iFont;			// font used to display text
		TLogicalColor iTextColor;		// color of displayed text
		TInt iTextWidthInPixels;        // a static width allocated for text between the left and right navigation arrows
		MCknCalendarNavigationObserver* iObserver; // notify navigation button events
		TUint iRepeatDelay;
		TBool iLeftArrowPressed;
		TBool iRightArrowPressed;
		TUint iInternalFlags;
	};


#endif	// CKNCALENDARNAVIGATION_H

// End of File
