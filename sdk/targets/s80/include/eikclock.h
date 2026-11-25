/*
* ==============================================================================
*  Name        : eikclock.h
*  Part of     : CKON
*  Interface   : Clock API
*  Description : Widget for standard clock control, and clock control that can 
*  Description : be generated from resources.
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

#ifndef EIKCLOCK_H
#define EIKCLOCK_H

// INCLUDES
#include <eikbctrl.h>
#include <gulbordr.h>

// FORWARD DECLARATIONS
class RAnimDll;
class RClock;
class RDigitalClock;
class RAnalogClock;
class CEikLocaleConformantClock;

//
struct STimeDeviceShadow;
//
struct SEikLocaleAndFontData
	{
		const TLocale* iLocale;
		const CFont* iFont;
		TInt iWidthOfSpace;
		TInt iWidthOfWidestCharacter;
		TInt iWidthOfWidestDigit;
		TInt iWidthOfWidestAmPmName;
		TInt iWidthOfWidestAbbreviatedDayName;
		TInt iWidthOfWidestDayName;
		TInt iWidthOfWidestAbbreviatedMonthName;
		TInt iWidthOfWidestMonthName;
		TInt iWidthOfWidestDateSuffix;
	};

//

/**
* Mixin observer class for the clock container.
*
* The class which contains the CEikLocaleConformantClock clock should implement this 
* mixin class so that the clock can access drawing information, e.g. visibility and position.
*
* @since Series90 1.0
*/
class MEikClockContainer
	{
	public:

		/**
		* Check whether or not a particular clock is visible.
		* @param aClock The clock whose visibility is to be checked.
		* @return ETrue if this clock is visible. EFalse otherwise.
		* <BR><B>Type of return value:</B> TBool
		*/
		virtual TBool ClockIsVisible(const CEikLocaleConformantClock& aClock) const=0;

		/**
		* Get the position and size of a particular clock.
		* @param aPosition On return, this should contain the position of the clock widget.
		* @param aSize On return, this should contain the size of the clock widget.
		* @param aClock The clock whose position and size are required.
		* @param aMinimumSize The minimum possible size for the clock.
		* <BR><B>Type of return value:</B> void
		*/
		virtual void GetClockPositionAndSize(TPoint& aPosition, TSize& aSize, const CEikLocaleConformantClock& aClock, const TSize& aMinimumSize)=0;
	};

//

/**
*  Auto-updating clock widget.
*
*  This clock widget can display either an analogue or digital clock.
*
*  Link against EIKCTL.LIB
*  @since Series90 1.0
*/
class CEikLocaleConformantClock : public CActive
	{
	protected:

		/**
		* C++ default constructor.
		* @param aContainer The container object for the clock.
		* @param aAnimDll The animation DLL to pass into the RDigitalClock / RAnalogClock class.
		* @param aWindow The window on which the clock will be drawn.
		* @param aType The type of clock, which is a combination of these flags:
		*	EEikLocaleConformantClockTypeChangesFormatAccordingToLocale 0x00
		*	EEikLocaleConformantClockTypeDigital						0x01
		*	EEikLocaleConformantClockTypeAnalog							0x02
		*	EEikUsesDefaultSystemColors									0x04
		* @param aTypeNeverChanges Set to ETrue if the clock will never change between analog/digital.
		*/
		IMPORT_C CEikLocaleConformantClock(MEikClockContainer& aContainer, RAnimDll& aAnimDll, const RWindowBase& aWindow, TInt aType, TBool aTypeNeverChanges);
	public:

		/**
		* Second phase constructor.
		* Call this to construct a clock showing the home time (automatically updating as the OS's locale data changes).
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructL();

		/**
		* Second phase constructor.
		* Call this to construct a clock whose universal-time-offset and daylight-saving-zone are independent of the OS's locale data.
		* @param aUniversalTimeOffset The difference in seconds between this clock and universal time.
		* @param aDaylightSavingZone The daylight saving zone of this clock.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructL(TTimeIntervalSeconds aUniversalTimeOffset, TDaylightSavingZone aDaylightSavingZone);

		/**
		* Destructor.
		*/
		IMPORT_C virtual ~CEikLocaleConformantClock();

		/**
		* Switches between an analogue and digital clock display.
		* @param aFormat If this is set to EClockAnalog, an analogue clock will be displayed.
		* Pass in EClockDigital to display a digital clock.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ChangeFormatL(TClockFormat aFormat); // can only be called if the clock-type is *not* EEikLocaleConformantClockTypeChangesFormatAccordingToLocale

		/**
		* Gets the current format of the clock.
		* @return EClockAnalog if the clock is currently analogue, EClockDigital if the clock is digital.
		* <BR><B>Type of return value:</B> TClockFormat
		*/
		IMPORT_C TClockFormat Format() const;

		/**
		* This function can only be called if the widget was constructed with the 2-parameter ConstructL.
		* It updates the universal time offset and daylight saving zone of the clock.
		* @param aUniversalTimeOffset The new value for the difference between the clock time and universal time (in seconds).
		* @param aDaylightSavingZone The new daylight saving zone.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ChangeUniversalTimeOffsetAndDaylightSavingZone(TTimeIntervalSeconds aUniversalTimeOffset, TDaylightSavingZone aDaylightSavingZone);

		/**
		* This function can only be called if the widget was constructed with the 2-parameter ConstructL.
		* It gets the universal time offset and daylight saving zone of the clock.
		* @param aUniversalTimeOffset On return, gives the difference between the clock time and universal time (in seconds).
		* @param aDaylightSavingZone On return, gives the clock's daylight saving zone.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void GetUniversalTimeOffsetAndDaylightSavingZone(TTimeIntervalSeconds& aUniversalTimeOffset, TDaylightSavingZone& aDaylightSavingZone) const;

		/**
		* Get the difference between the clock and universal time, taking daylight saving into account.
		* @return The time difference in seconds
		* <BR><B>Type of return value:</B> TTimeIntervalSeconds
		*/
		IMPORT_C TTimeIntervalSeconds CompleteUniversalTimeOffset() const;

		/**
		* Sets the clock's visibility. 
		* @param aVisible Set to ETrue to make the clock visible, EFalse to hide it.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetVisible(TBool aVisible);

		/**
		* Sets the clock's position and size.
		* @param aPosition The new position for the clock.
		* @param aSize The new size for the clock.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetPositionAndSize(const TPoint& aPosition, const TSize& aSize);

		/**
		* Sets the clock's position.
		* @param aPosition The new position for the clock.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetPosition(const TPoint& aPosition);

		/**
		* Sets the clock's size.
		* @param aSize The new size for the clock.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetSize(const TSize& aSize);

		/**
		* Sets the clock's font.
		* @param aHandle The handle of the font to be used to draw the clock. This can be accessed
		* by calling CFbsFont::Handle().
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetFont(const TInt aHandle);

		/**
		* Sets the bitmap to be displayed in the background of the clock.
		* @param aHandle The handle of the bitmap to be used. This can be accessed
		* by calling CFbsBitmap::Handle().
		* @param aBitmapRect The rectangle on which the bitmap can be drawn
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetBackgroundBitmap(const TInt aHandle, const TRect aBitmapRect);

		/**
		* Sets the text section to allow the date/time to be toggled
		* @param aTextSection The index of the text section to toggle the date time
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetDateTimeToggle(const TInt aTextSection);

		/**
		* Sends the toggle date/time message to toggle between the time and date displays on the clock.
		* This allows the CBA clock to be changed when the user clicks on it.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ToggleDateTime();

		/**
		* Draws the clock's border only. This uses aGc's current brush settings.
		* @param aGc The graphic context to draw with.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void Draw(CWindowGc& aGc) const; 

		/**
		* Draws the complete clock. This uses aGc's current brush settings.
		* Called when clock is displayed on backed up window (OPL).
		* @param aGc The graphic context to draw with.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void RedrawAll(CWindowGc& aGc) const; 

		/**
		* @return The minimum size of the clock.
		* <BR><B>Type of return value:</B> TSize
		*/
		IMPORT_C TSize MinimumSize() const;

		/**
		* @return The position and size of the clock, as a TRect.
		* <BR><B>Type of return value:</B> TRect
		*/
		IMPORT_C TRect Rect() const;

		/**
		* @return ETrue if the clock has a border.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool HasBorder() const;

		/**
		* @return EFalse if the Clock type changes format according to the TLocale. ETrue if the TLocale format is ignored.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool IgnoresLocaleClockFormat() const;

		/**
		* @return ETrue if the clock cannot change between analogue/digital. EFalse if it can change.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool TypeNeverChanges() const;

		/**
		* Gets the maximum possible width of the text displayed in the clock.
		* @param aTextBlock Text symbols specifying the layout of the clock.
		* Each of these should be preceded by '%', then any or none of the following characters:
		*	'*': The day or month name is abbreviated
		*	'+': The am/pm text is located after the time.
		*	'-': The am/pm text is located before the time.
		*
		* The following characters can signify special cases:
		*   'D': day name in date
		*   'H': hour in 24 hour time format
		*	'I': hour in 12 hour time format
		*	'J': default time format for hour
		*	'M': month as a number
		*	'S': seconds
		*	'T': minutes
		*	'W': week number in year
		*	'B': am/pm text if local time format is 12 hour clock
		*	'A': am/pm text
		*	'C': microseconds
		*	'E': day name
		*	'N': month name
		*	'FX': day suffix
		*	'Y': year
		*	'Z': day no in year
		*
		* e.g. 10:35.03%C would check the size of the clock with microseconds.
		*      25/08/2003%D%N would check the size of the clock with the day and month as names.
		*
		* @param aLocaleAndFontData Data structure with pointers to the locale, font, and other clock display information.
		* See <code>SEikLocaleAndFontData</code>.
		* @return The maximum possible width.
		* <BR><B>Type of return value:</B> TInt	
		*/
		IMPORT_C static TInt PotentialWidthOfTextBlock(const TDesC& aTextBlock, const SEikLocaleAndFontData& aLocaleAndFontData);

	public:
		void HandleResourceChange();

	protected:

		/** 
		* Gets the width of the specified character in a particular font.
		* @param aFont The font to use.
		* @param aCharacter The character to get the width of.
		* @return The character width.
		* <BR><B>Type of return value:</B> TInt	
		*/
		IMPORT_C static TInt WidthOfCharacter(const CFont& aFont, TChar aCharacter);
	enum
		{
		EIgnoresLocaleClockFormat									=0x1,
		EIgnoresLocaleUniversalTimeOffsetAndHomeDaylightSavingZone	=0x2,
		ETypeNeverChanges											=0x4,
		EUsesDefaultSystemColors									=0x8
		};
		TUint32 iFlags;
	private:
	// framework
		IMPORT_C virtual void DoCancel();
		IMPORT_C virtual void RunL();
	// other functions
		void LogonChangeNotifier();
		TTimeIntervalSeconds CalculateCompleteUniversalTimeOffset() const;
		TBool CompleteUniversalTimeOffsetHasChanged();
		void SetFormatL(TClockFormat aFormat, TBool aCompleteSetUp=ETrue);
		virtual void ConstructDigitalClockL(RDigitalClock& aDigitalClock, TGulBorder& aBorder, TSize& aMinimumSize) const=0;
		virtual void ConstructAnalogClockL(RAnalogClock& aAnalogClock, TGulBorder& aBorder, TSize& aMinimumSize) const=0;
		static TInt ToggleBack(TAny* aObject);
	private:
	struct TExtraData
		{
		inline TExtraData() : iDrawBackground(EFalse), iPeriodic(NULL) {};
		TBool iDrawBackground;
		CPeriodic* iPeriodic;
		};
	private:
		RChangeNotifier iChangeNotifier;
		MEikClockContainer& iContainer;
		RAnimDll& iAnimDll;
		const RWindowBase& iWindow;
		TClockFormat iFormat;
		RClock* iClock;
		TTimeIntervalSeconds iUniversalTimeOffset;
		TDaylightSavingZone iDaylightSavingZone;
		TTimeIntervalSeconds iCompleteUniversalTimeOffset;
		TPoint iPosition;
		TSize iSize;
		TSize iMinimumSize;
		TExtraData *iExtra;
		TGulBorder iBorder;
	};

//

/**
*  A version of the clock widget which can be constructed from resources.
*
*  Link against EIKCTL.LIB.
*  @since Series90 1.0
*/
class CEikResourceConstructedClock : public CEikLocaleConformantClock
	{
	public:
		/**
		* C++ default constructor.
		* @param aContainer The container object for the clock.
		* @param aAnimDll The animation DLL to pass into the RDigitalClock / RAnalogClock class.
		* @param aWindow The window on which the clock will be drawn.
		* @param aType The type of clock, which is a combination of these flags:
		*	EEikLocaleConformantClockTypeChangesFormatAccordingToLocale 0x00
		*	EEikLocaleConformantClockTypeDigital						0x01
		*	EEikLocaleConformantClockTypeAnalog							0x02
		*	EEikUsesDefaultSystemColors									0x04
		* @param aTypeNeverChanges Set to ETrue if the clock will never change between analog/digital.
		* @param aCoeEnv The environment for the clock.
		* @param aDigitalResourceId The resource ID of the DIGITAL_CLOCK object.
		* @param aAnalogResourceId The resource ID of the ANALOG_CLOCK object. Either this or aDigitalResourceId must 
		* contain valid clock resources, depending on the initial clock type.
		*/
	IMPORT_C CEikResourceConstructedClock(MEikClockContainer& aContainer, RAnimDll& aAnimDll, const RWindowBase& aWindow, TInt aType,
											TBool aTypeNeverChanges, CCoeEnv& aCoeEnv, TInt aDigitalResourceId, TInt aAnalogResourceId);
	private:
	// framework
		virtual void ConstructDigitalClockL(RDigitalClock& aDigitalClock, TGulBorder& aBorder, TSize& aMinimumSize) const;
		virtual void ConstructAnalogClockL(RAnalogClock& aAnalogClock, TGulBorder& aBorder, TSize& aMinimumSize) const;
	// other functions
		static TPoint ReadPoint(TResourceReader& aResourceReader);
		static TRgb ReadColor(TResourceReader& aResourceReader);
		static STimeDeviceShadow ReadShadow(TResourceReader& aResourceReader);
		static void ReadPen(TResourceReader& aResourceReader, CGraphicsContext::TPenStyle& aStyle, TRgb& aColor, TSize& aSize);
		static void ReadBrush(TResourceReader& aResourceReader, CGraphicsContext::TBrushStyle& aStyle, TRgb& aColor);
	protected:
	void CommonConstructDigitalClockL(RDigitalClock& aDigitalClock, 
									  TGulBorder& aBorder, 
									  TSize& aMinimumSize,
									  TBool aIsCBAClock) const;
	protected:
		CCoeEnv& iCoeEnv;
		TInt iDigitalResourceId;
		TInt iAnalogResourceId;
	};

//

/**
*  A version of the clock widget which can be constructed from resources,
* and which is drawn below the CBA buttons.
*
*  Link against EIKCTL.LIB.
*  @since Series90 1.0
*/
class CEikCBAResourceConstructedClock : public CEikResourceConstructedClock
	{
	public:
	CEikCBAResourceConstructedClock(MEikClockContainer& aContainer, 
									RAnimDll& aAnimDll, 
									const RWindowBase& aWindow, 
									TInt aType,
									CCoeEnv& aCoeEnv, 
									TInt aDigitalResourceId);
	private:
	// framework
	virtual void ConstructDigitalClockL(RDigitalClock& aDigitalClock, 
										TGulBorder& aBorder, 
										TSize& aMinimumSize) const;
	};

//

/**
*  A clock widget made from a CEikLocaleConformantClock.
*
*  Link against EIKCTL.LIB.
*  @since Series90 1.0
*/
class CEikClock : public CEikBorderedControl, public MEikClockContainer
	{
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikClock();

		/**
		* Takes ownership of aClock - to be called by container only if not constructed from resource.
		* @param aClock Pointer to a clock widget.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetClock(CEikLocaleConformantClock* aClock);

		/**
		* Destructor.
		*/
		IMPORT_C virtual ~CEikClock();
	// from CCoeControl

		/**
		* See CCoeControl.
		*/
		IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

		/**
		* See CCoeControl.
		*/
		IMPORT_C virtual void MakeVisible(TBool aVisible);

		/**
		* See CCoeControl.
		* Constructs a clock from resources. This takes a resource of type EEikCtClock with
		* struct CLOCK.
		*/
		IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader); // just calls CreateLocaleDependentL

		/**
		* See CCoeControl.
		*/
		IMPORT_C virtual void ActivateL();

		/**
		* See CCoeControl.
		*/
		IMPORT_C virtual TSize MinimumSize();

		/**
		* @return ETrue if the clock has a border.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C virtual TBool HasBorder() const;

		/**
		* See CCoeControl.
		*/
		IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

		/**
		* See CCoeControl.
		*/
		IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	private:
	// framework
		IMPORT_C virtual void SizeChanged();
		IMPORT_C virtual void PositionChanged();
		IMPORT_C virtual void Draw(const TRect& aRect) const;
		IMPORT_C void Dummy1();	// To replace reserved funcs that are actually inherited from...
		IMPORT_C void Dummy2();	// ... CCoeControl so shouldn't be re-declared in here
		IMPORT_C virtual TBool ClockIsVisible(const CEikLocaleConformantClock& aClock) const;
		IMPORT_C virtual void GetClockPositionAndSize(TPoint& aPosition, TSize& aSize, const CEikLocaleConformantClock& aClock, const TSize& aMinimumSize);
	// other functions
		IMPORT_C virtual void ConstructClockL(CEikLocaleConformantClock& aClock); // override this if you want to call the CEikLocaleConformantClock::ConstructL with parameters
	private:
		CEikLocaleConformantClock* iClock;
	};

/**
*  An internal font class used by the clock to read a font type from resources.
*
*  Link against EIKCTL.LIB.
*  @since Series90 1.0
*/
class CCleanupStackableNamedFont : public CBase
	{
	public:

		/**
		* Static constructor.
		*/
		static CCleanupStackableNamedFont* NewL(TResourceReader& aReader,CWsScreenDevice& aScreenDevice);

		/**
		* Static constructor.
		*/
		static CCleanupStackableNamedFont* NewLC(TResourceReader& aReader,CWsScreenDevice& aScreenDevice);

		/**
		* Destructor.
		*/
		virtual ~CCleanupStackableNamedFont();

		CFbsFont& Font() const;
		CFbsFont* TakeOwnershipOfFont();
	private:
		CCleanupStackableNamedFont(CWsScreenDevice& aScreenDevice);
	private:
		CWsScreenDevice& iScreenDevice;
		CFbsFont* iFont;
	};


#endif	// EIKCLOCK_H

// End of File
