/*
* ==============================================================================
*  Name        : clock.h
*  Part of     : CLOCK
*  Interface   : Clock API
*  Description : Classes for drawing analog/digital Clock and Message windows.
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


#ifndef CLOCK_H
#define CLOCK_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <w32std.h>

//
// miscellaneous enums
//

enum TDisplayType // implementation class
	{
	EDisplayDigital,
	EDisplayAnalog
	};

//

enum TAnalogDisplayHandFeatureType // implementation class
	{
	EAnalogDisplayHandFeatureLine,
	EAnalogDisplayHandFeaturePolyLine,
	EAnalogDisplayHandFeatureCircle
	};

//

enum TDigitalDisplayHorizontalTextAlignment
	{
	EDigitalDisplayHorizontalTextAlignmentLeft,
	EDigitalDisplayHorizontalTextAlignmentCenter,
	EDigitalDisplayHorizontalTextAlignmentRight
	};

//

enum TDigitalDisplayVerticalTextAlignment
	{
	EDigitalDisplayVerticalTextAlignmentTop,
	EDigitalDisplayVerticalTextAlignmentCenterInclDescent,
	EDigitalDisplayVerticalTextAlignmentCenterExclDescent,
	EDigitalDisplayVerticalTextAlignmentBottomInclDescent,
	EDigitalDisplayVerticalTextAlignmentBottomExclDescent
	};

//

enum TDigitalDisplayLayoutChar
	{
	EDigitalDisplayLayoutCharFlashingBlockDelimiter=1
	};

//

enum TAnalogDisplayHandType
	{
	EAnalogDisplayHandOneRevPer12Hours,
	EAnalogDisplayHandOneRevPerHour,
	EAnalogDisplayHandOneRevPerMinute
	};

// DATA TYPES
typedef TBuf8<1024> TConstructorBuf8; // implementation class

//
// miscellaneous structs
//

struct STimeDeviceShadow
	{
		TBool iIsOn;
		TRgb iColor;
		TPoint iOffset;
	};

//

struct SAnalogDisplayAmPm
	{
		TPoint iPositionRelativeToFace;
		TSize iSize;
		STimeDeviceShadow iShadow;
		TRgb iBackgroundColor;
		TInt iFontHandle;
		TRgb iTextColor;
	};

//
// display-addition classes
//
/**
*
* This class is used in the derivation of
* <code>TAnalogDisplayHand</code> and
* <code>TDigitalDisplayTextSection</code>.
*
* It has no user accessible functions.
*
* @since 5.0
* @lib "clock.lib"
*/
class TDisplayAddition
	{
	public:
		const TDesC8& Buf() const;
	protected:
		TConstructorBuf8 iBuf;
	};

//

/**
*
* A text section for a digital clock (<code>RDigitalClock</code>).
* @since 5.0
* @lib "clock.lib"
*/
class TDigitalDisplayTextSection : public TDisplayAddition
	{
	public:
	/**
 *
 * Constructs a text section for a digital clock.
 *
 * @param     "TInt aFontHandle"
 *            A handle to the font to use. This can be obtained with
 *            <code>CFbsFont::Handle()</code>. This font cannot be
 *            destroyed until the <code>RDigitalClock</code> has
 *            been completely constructed, including all necessary
 *            calls to
 *            <code>RDigitalClock::AddTextSectionL()</code>.
 * @param     "TRgb aTextColor"
 *            Text colour
 * @param     "TDigitalDisplayHorizontalTextAlignment aHorizontalAlignment"
 *            Horizontal alignment
 * @param     "TDigitalDisplayVerticalTextAlignment aVerticalAlignment"
 *            Vertical alignment
 * @param     "TInt aHorizontalMargin"
 *            Horizontal margin
 * @param     "TInt aVerticalMargin"
 *            Vertical margin
 * @param     "const TDesC& aFormat"
 *            A formatting string for the time. The allowed
 *            characters for this are as for
 *            <code>TTime::FormatL()</code>, plus those in
 *            <code>TDigitalDisplayLayoutChar</code>.
 */
		IMPORT_C TDigitalDisplayTextSection(TInt aFontHandle, TRgb aTextColor, TDigitalDisplayHorizontalTextAlignment aHorizontalAlignment,
																TDigitalDisplayVerticalTextAlignment aVerticalAlignment,
																TInt aHorizontalMargin, TInt aVerticalMargin, const TDesC& aFormat);
																// N.B. the font passed in to aFontHandle cannot be destroyed until the
																// RDigitalClock has been completely constructed, including all necessary
																// calls to RDigitalClock::AddTextSectionL()
	};

//

/**
*
* A hand for an analogue clock (<code>RAnalogClock</code>).
*
* A hand is a vector drawing made from a number of features (lines,
* circles, polylines). These are specified with the hand assumed to be
* in the 12 o'clock position, with <code>TPoint(0,0)</code> being the
* center of the clock.
*
* @since 5.0
* @lib "clock.lib"
*/
class TAnalogDisplayHand : public TDisplayAddition
	{
	public:

		/**
		* C++ default constructor.
 *
 * Constructs a hand for an analogue clock.
 *
 * @param     "TAnalogDisplayHandType aType"
 *            Type of hand
 */
		IMPORT_C TAnalogDisplayHand(TAnalogDisplayHandType aType);
		
		/**
 *
 * Adds a line to the hand.
 *
 * @param     "CGraphicsContext::TPenStyle aPenStyle"
 *            The pen style
 * @param     "TRgb aPenColor"
 *            The pen colour
 * @param     "const TSize& aPenSize"
 *            The pen size
 * @param     "const TPoint& aStartPoint"
 *            The start point for the line
 * @param     "const TPoint& aEndPoint"
 *            The end point for the line
 */
		IMPORT_C void AddLine(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
	/**
 *
 * Adds a polyline to the hand.
 *
 * @param     "CGraphicsContext::TPenStyle aPenStyle"
 *            The pen style
 * @param     "TRgb aPenColor"
 *            The pen colour
 * @param     "const TSize& aPenSize"
 *            The pen size
 * @param     "CGraphicsContext::TBrushStyle aBrushStyle"
 *            The brush style
 * @param     "TRgb aBrushColor"
 *            The brush colour
 * @param     "TBool aClosed"
 *            True if the polyline forms a closed shape, else false
 * @param     "const CArrayFix<TPoint>* aPointList"
 *            An array of points for the polyline. The class does
 *            not delete <code>aPointList</code>.
 */															const TPoint& aStartPoint, const TPoint& aEndPoint);
	IMPORT_C void AddPolyLine(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																CGraphicsContext::TBrushStyle aBrushStyle, TRgb aBrushColor,
																TBool aClosed, const CArrayFix<TPoint>* aPointList); // aPointList is not destroyed
	
		/**
 *
 * Adds a circle to the hand.
 *
 * @param     "CGraphicsContext::TPenStyle aPenStyle"
 *            The pen style
 * @param     "TRgb aPenColor"
 *            The pen colour
 * @param     "const TSize& aPenSize"
 *            The pen size
 * @param     "CGraphicsContext::TBrushStyle aBrushStyle"
 *            The brush style
 * @param     "TRgb aBrushColor"
 *            The brush colour
 * @param     "const TPoint& aCircleCenter"
 *            The centre of the circle
 * @param     "TInt aRadius"
 *            The radius of the circle
 */
		IMPORT_C void AddCircle(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																CGraphicsContext::TBrushStyle aBrushStyle, TRgb aBrushColor,
																const TPoint& aCircleCenter, TInt aRadius);

		/**
		* Get the number of <code>TAnalogDisplayHandFeatureType</code>s used in the clock.
		* @return Number of features.
		* <BR><B>Type of return value:</B> TInt
		*/
		inline TInt NumFeatures() const {return *iNumFeaturesPtr;}
	private:
		void AppendType(TAnalogDisplayHandFeatureType aType);
	private:
		TInt* iNumFeaturesPtr;
	};

//
// utility class
//

/**
*
* Utility class to support clock animation.
* @since 5.0
* @lib "clock.lib"
*/
class RAnimWithUtils : public RAnim
	{
	protected:

		/**
		* C++ default constructor.
		*/
		RAnimWithUtils(RAnimDll& aAnimDll, const RWindowBase& aWindow);
		void AppendToConstructorBufL(const TDesC8& aData);
		void SendConstructorBufIfCompleteL(TInt aAnimatedObjectType);
		void SendConstructorBufL(TInt aAnimatedObjectType);
		TBool ConstructorBufExists() const;
		TBool ConstructorBufAlreadySent() const;
		TConstructorBuf8& ConstructorBuf() const;
		void SetNumAdditionsStillExpected(TInt aNumAdditionsStillExpected);
	public:

		/**
		* Closes the clock animation.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C virtual void Close();
	private:
		TConstructorBuf8* iConstructorBuf; // on the heap as it is only required for construction
		TBool iConstructorBufAlreadySent;
		const RWindowBase& iWindow;
		TInt iNumAdditionsStillExpected;
	};

//
// time-device abstract classes
//

/**
*  Sets display parameters for clocks.
*
* @since 5.0
* @lib "clock.lib"
*/
class RTimeDevice : public RAnimWithUtils
	{
	protected:

		RTimeDevice(RAnimDll& aAnimDll, const RWindowBase& aWindow);
		void AppendDisplayTypeL(TDisplayType aType);
	void AppendDigitalDisplayConstructorArgsL(const TPoint& aPosition, 
											  const TSize& aSize, 
											  const TMargins& aMargins, 
											  const STimeDeviceShadow& aShadow,
											  TRgb aBackgroundColor, 
											  TInt aNumTextSections);

	void AppendAnalogDisplayConstructorArgsL(const TPoint& aPosition,
											 const TSize& aSize,
											 const TMargins& aMargins,
											 const STimeDeviceShadow& aShadow,
											 TInt aFaceHandle,
											 TInt aFaceMaskHandle,
											 TInt aNumHands,
											 const SAnalogDisplayAmPm* aAmPm,
											 TPoint aOffsetHandCenter=TPoint());
	public:

		/**
 *
 * Makes the clock visible.
 *
 * By default, clocks are invisible.This function can only be called
 * after full construction of the clock.
 *
 * @param     "TBool aVisible"
 *            <code>ETrue</code> makes the clock visible,
 *            <code>EFalse</code> invisible
 */
		IMPORT_C void SetVisible(TBool aVisible); // can only be called after full construction - by default clocks are invisible

/**
 *
 * Sets the clock's on-screen position and size.
 *
 * This function can only be called after full construction of the clock.
 *
 * @param     "const TPoint& aPosition"
 *            Clock co-ordinates
 * @param     "const TSize& aSize"
 *            Clock size
 */
		IMPORT_C void SetPositionAndSize(const TPoint& aPosition, const TSize& aSize); // can only be called after full construction

/**
 *
 * Sets the clock's on-screen position.
 *
 * This function can only be called after full construction of the clock.
 *
 * @param     "const TPoint& aPosition"
 *            Clock co-ordinates
 */
		IMPORT_C void SetPosition(const TPoint& aPosition); // can only be called after full construction
/**
 *
 * Sets the clock's on-screen size.
 *
 * This function can only be called after full construction of the clock.
 *
 * @param     "const TSize& aSize"
 *            Clock size
 */
		IMPORT_C void SetSize(const TSize& aSize); // can only be called after full construction
/**
 *
 * Forces an update to the clock's display.
 *
 * This function can only be called after full construction of the clock.
 *
 */
		IMPORT_C void UpdateDisplay(); // can only be called after full construction

/**
 *
 * Draws the clock.
 *
 */
		IMPORT_C void Draw(); // can only be called after full construction

		/**
		* Sets the bitmap to be displayed in the background of the clock.
		* @param aHandle The handle of the bitmap to be used. This can be accessed
		* by calling CFbsBitmap::Handle().
		* @param aBitmapRect The rectangle on which the bitmap can be drawn
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetBackgroundBitmap(const TInt aHandle, const TRect aBitmapRect); // can only be called after full construction

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
		* Sets the clock's font.
		* @param aHandle The handle of the font to be used to draw the clock. This can be accessed
		* by calling CFbsFont::Handle().
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetFont(const TInt aHandle);
	};

//

/**
* Sets the time for clocks.
*
* @since 5.0
* @lib "clock.lib"
*/
class RClock : public RTimeDevice
	{
	protected:

		/**
		* C++ default constructor.
		*/
		RClock(RAnimDll& aAnimDll, const RWindowBase& aWindow);
		void AppendClockConstructorArgsL(TTimeIntervalSeconds aUniversalTimeOffset);
	public:

/**
 * Adjusts the clock's time.
 *
 * This function can only be called after full construction.
 *
 * @param     "TTimeIntervalSeconds aUniversalTimeOffset"
 *            The time to which to set the clock, expressed as an
 *            offset from universal time.
 */
		IMPORT_C void SetUniversalTimeOffset(TTimeIntervalSeconds aUniversalTimeOffset); 
	};

//
// time-device concrete classes
//

/**
*
* A digital clock.
*
* A digital clock is composed of one or more text sections, which define
* how the time information is displayed.
*
* @since 5.0
* @lib "clock.lib"
*/
class RDigitalClock : public RClock
	{
	public:

/**
 *
 * Creates a digital clock object.
 *
 * To complete construction, you must call <code>ConstructL()</code>.
 *
 * @param     "RAnimDll& aAnimDll"
 *            This <code>RAnimDll</code> must have been loaded with
 *            the server-side clock animation DLL, clocka.dll
 * @param     "const RWindowBase& aWindow"
 *            Window to which to add the clock
 */
		IMPORT_C RDigitalClock(RAnimDll& aAnimDll, const RWindowBase& aWindow);

/**
 *
 * Completes construction of a digital clock.
 *
 * @param     "TTimeIntervalSeconds aUniversalTimeOffset"
 *            Initial time for the clock, expressed as an offset
 *            from universal time
 * @param     "const TPoint& aPosition"
 *            Clock's on-screen position
 * @param     "const TSize& aSize"
 *            Clock's on-screen size
 * @param     "const TMargins& aMargins"
 *            Margin settings
 * @param     "const STimeDeviceShadow& aShadow"
 *            Shadow settings
 * @param     "TRgb aBackgroundColor"
 *            Background color
 * @param     "TInt aNumTextSections"
 *            Number of text sections
 */
		IMPORT_C void ConstructL(TTimeIntervalSeconds aUniversalTimeOffset, const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins,
																const STimeDeviceShadow& aShadow, TRgb aBackgroundColor, TInt aNumTextSections);

/**
 *
 * Adds a text section to the clock.
 *
 * This function can only be called after full construction of the clock.
 *
 * @param     "const TDigitalDisplayTextSection& aTextSection"
 *            Describes text section to add
 */
		IMPORT_C void AddTextSectionL(const TDigitalDisplayTextSection& aTextSection);


/**
 *
 * Sets background colour for the clock.
 *
 * This function can only be called after full construction of the clock.
 *
 * @param     "TRgb aBackgroundColor"
 *            Background colour
 * @param     "TRgb aShadowColor"
 *            Shadow colour
 */
		IMPORT_C void SetBackgroundColor(TRgb aBackgroundColor, TRgb aShadowColor); // can only be called after full construction

/**
 *
 * Sets the text colour.
 *
 * This function can only be called after full construction of the clock.
 *
 * @since     6.0
 * @param     "TRgb aTextColor"
 *            Text colour
 */
		IMPORT_C void SetTextColor(TRgb aTextColor);
	};

//

/**
* An analogue clock.
* @since 5.0
* @lib "clock.lib"
*/
class RAnalogClock : public RClock
	{
	public:

/**
 *
 * Creates an analogue clock object.
 *
 * To complete construction, you must call <code>ConstructL()</code>.
 *
 * @param     "RAnimDll& aAnimDll"
 *            This <code>RAnimDll</code> must have been loaded with
 *            the server-side clock animation DLL, clocka.dll
 * @param     "const RWindowBase& aWindow"
 *            Window to which to add the clock
 */
		IMPORT_C RAnalogClock(RAnimDll& aAnimDll, const RWindowBase& aWindow);

/**
 *
 * Completes construction of an analogue clock.
 *
 * The bitmaps specified in <code>aFaceHandle</code> and
 * <code>aFaceMaskHandle</code> cannot be destroyed until the clock has
 * been completely constructed, including all necessary calls to
 * <code>RAnalogClock::AddHandL()</code>.
 *
 * @param     "TTimeIntervalSeconds aUniversalTimeOffset"
 *            Initial time for the clock, expressed as an offset
 *            from universal time
 * @param     "const TPoint& aPosition"
 *            Clock's on-screen position
 * @param     "const TSize& aSize"
 *            Clock's on-screen size
 * @param     "const TMargins& aMargins"
 *            Margin settings
 * @param     "const STimeDeviceShadow& aShadow"
 *            Shadow settings
 * @param     "TInt aFaceHandle"
 *            Handle to a bitmap of the clock face. You can obtain a
 *            bitmap handle through
 *            <code>CFbsBitmap::Handle()</code>.
 * @param     "TInt aFaceMaskHandle"
 *            Handle to a bitmap mask for the clock face. This can
 *            be 0, if no mask is required.
 * @param     "TInt aNumHands"
 *            Number of hands on the clock. For each hand, you must
 *            call <code>AddHandL()</code>.
 * @param     "const SAnalogDisplayAmPm* aAmPm=NULL"
 *            Options for displaying AM/PM
 */
	IMPORT_C void ConstructL(TTimeIntervalSeconds aUniversalTimeOffset, 
							 const TPoint& aPosition, const TSize& aSize, 
							 const TMargins& aMargins, const STimeDeviceShadow& aShadow, 
							 TInt aFaceHandle, TInt aFaceMaskHandle, TInt aNumHands, 
							 const SAnalogDisplayAmPm* aAmPm=NULL);

/**
 *
 * Completes construction of an analogue clock.
 *
 * The bitmaps specified in <code>aFaceHandle</code> and
 * <code>aFaceMaskHandle</code> cannot be destroyed until the clock has
 * been completely constructed, including all necessary calls to
 * <code>RAnalogClock::AddHandL()</code>.
 *
 * @param     "TTimeIntervalSeconds aUniversalTimeOffset"
 *            Initial time for the clock, expressed as an offset
 *            from universal time
 * @param     "const TPoint& aPosition"
 *            Clock's on-screen position
 * @param     "const TSize& aSize"
 *            Clock's on-screen size
 * @param     "const TMargins& aMargins"
 *            Margin settings
 * @param     "const STimeDeviceShadow& aShadow"
 *            Shadow settings
 * @param     "TInt aFaceHandle"
 *            Handle to a bitmap of the clock face. You can obtain a
 *            bitmap handle through
 *            <code>CFbsBitmap::Handle()</code>.
 * @param     "TInt aFaceMaskHandle"
 *            Handle to a bitmap mask for the clock face. This can
 *            be 0, if no mask is required.
 * @param     "TInt aNumHands"
 *            Number of hands on the clock. For each hand, you must
 *            call <code>AddHandL()</code>.
 * @param     "TPoint aOffsetHandCenter"
 *            This offset the hands of the analog clock
 *			  from the centre by this amount.
 * @param     "const SAnalogDisplayAmPm* aAmPm=NULL"
 *            Options for displaying AM/PM
 */
	IMPORT_C void ConstructL(TTimeIntervalSeconds aUniversalTimeOffset, 
							 const TPoint& aPosition, const TSize& aSize, 
							 const TMargins& aMargins, const STimeDeviceShadow& aShadow, 
							 TInt aFaceHandle, TInt aFaceMaskHandle, TInt aNumHands, 
							 TPoint aOffsetHandCenter,
							 const SAnalogDisplayAmPm* aAmPm=NULL);

/**
 *
 * Adds a hand to the clock.
 *
 * This function can only be called after full construction of the clock.
 *
 * @param     "const TAnalogDisplayHand& aHand"
 *            Settings for the hand
 */
		IMPORT_C void AddHandL(const TAnalogDisplayHand& aHand);

/**
 *
 * Sets the background colour for the clock.
 *
 * This function can only be called after full construction of the clock.
 *
 * @since     6.0
 * @param     "TRgb aBackgroundColor"
 *            Background colour
 * @param     "TRgb aShadowColor"
 *            Shadow colour
 */
		IMPORT_C void SetBackgroundColor(TRgb aBackgroundColor, TRgb aShadowColor); // can only be called after full construction

/**
 *
 * Sets the text colour.
 *
 * This function can only be called after full construction of the clock.
 *
 * @since     6.0
 * @param     "TRgb aTextColor"
 *            Text colour
 */
		IMPORT_C void SetTextColor(TRgb aTextColor);

/**
 *
 * Sets the pen colour for the hands.
 *
 * This function can only be called after full construction of the clock.
 *
 * @since     6.0
 * @param     "const TRgb aPenColor"
 *            Pen colour
 */
		IMPORT_C void SetPenColor(const TRgb aPenColor);

/**
 *
 * Sets the brush colour for the hands.
 *
 * This function can only be called after full construction of the clock.
 *
 * @since     6.0
 * @param     "const TRgb aBrushColor"
 *            Brush colour
 */
		IMPORT_C void SetBrushColor(const TRgb aBrushColor);
	};

/**
*  A configurable window that appears for a brief time to display a message to the user and then disappears.
*
* This is the basic class that is used by such classes as CEikonEnv and CEikMsgWin to provide information and 
* message windows. Such higher-level classes would normally be used by client applications rather than RMessageWindow. 
* This class can be used though to implement specialist new classes. 
* 
* Note that this class is in the same library as the Clock API for implementation reasons only
*
*  @lib clock.lib
*  @since 5.0
*/
class RMessageWindow : public RAnimWithUtils
	{
	public:
	enum
		{
		EMaxTextLength=256
		};
	public:

		/**
		* C++ default constructor.
		* @param aAnimDll This RAnimDll must have been loaded with the server-side message window animation DLL, clocka.dll.
		* @param aWindow Window to which to add the message window
		*/
		IMPORT_C RMessageWindow(RAnimDll& aAnimDll, const RWindowBase& aWindow);

		/**
		* Second-phase construction.
		* @param aBaselineOffset Height of window in pixels above the font's baseline.
		* @param aFontHandle Handle to the font to use. This can be obtained with CFbsFont::Handle().
		* @param aBackgroundColor Window's background colour.
		* @param aTextColor Message text colour.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructL(TInt aBaselineOffset, TInt aFontHandle, TRgb aBackgroundColor, TRgb aTextColor);

		/**
		* Second-phase construction, with window border colour option.
		* @param aBaselineOffset Height of window in pixels above the font's baseline.
		* @param aFontHandle Handle to the font to use. This can be obtained with CFbsFont::Handle().
		* @param aBackgroundColor Window's background colour.
		* @param aTextColor Message text colour.
		* @param aBorderColor Window border colour.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructL(TInt aBaselineOffset, TInt aFontHandle, TRgb aBackgroundColor, TRgb aTextColor, TRgb aBorderColor);

		/**
		* Display message window for a specified time with initial delay.
		* @param aFlash Set this to true to make the message window flash.
		* @param aInitialDelay Duration for which to display the message window.
		* @param aText Text to put in the window.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void StartDisplay(TBool aFlash, TTimeIntervalMicroSeconds32 aInitialDelay, const TDesC& aText);

		/**
		* Display message window for a specified time.
		* @param aFlash Set this to true to make the message window flash.
		* @param aInitialDelay Initial delay before showing the window.
		* @param aDuration Duration for which to display the message window
		* @param aText Text to put in the window.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void StartDisplay(TBool aFlash, TTimeIntervalMicroSeconds32 aInitialDelay, TTimeIntervalMicroSeconds32 aDuration, const TDesC& aText);

		/**
		* Display message window for a specified time with initial delay.
		* @param aFlash Set this to true to make the message window flash.
		* @param aInitialDelay Duration for which to display the message window.
		* @param aBitmapCategory Bitmap Uid for the type of bitmap to display.
		* @param aBitmapId Index of the bitmap to display.
		* @param aText Text to put in the window.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void StartDisplay(TBool aFlash, TTimeIntervalMicroSeconds32 aInitialDelay, const TUid aBitmapCategory, TInt aBitmapId, const TDesC& aText);

		/**
		* Display message window for a specified time.
		* @param aFlash Set this to true to make the message window flash.
		* @param aInitialDelay Initial delay before showing the window.
		* @param aDuration Duration for which to display the message window
		* @param aBitmapCategory Bitmap Uid for the type of bitmap to display.
		* @param aBitmapId Index of the bitmap to display.
		* @param aText Text to put in the window.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void StartDisplay(TBool aFlash, TTimeIntervalMicroSeconds32 aInitialDelay, TTimeIntervalMicroSeconds32 aDuration, const TUid aBitmapCategory, TInt aBitmapId, const TDesC& aText);

		/**
		* Cancels the display of the window.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void CancelDisplay();

		/**
		* Gets the widths of the window's borders.
		* @param aBorders On return, widths of the window's borders.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void GetBorders(TMargins& aBorders);

		/**
		* Sets the background colour for the window.
		* @param aBackgroundColor Background colour.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetBackgroundColor(TRgb aBackgroundColor);

		/**
		* Sets the message text colour.
		* @param aTextColor Message text colour.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetTextColor(TRgb aTextColor);

		/**
		* Sets the window border colour.
		* @param aBorderColor Window border colour.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetBorderColor(TRgb aBorderColor);

		/**
		* Sets the plinth colours.
		* @param aTl Colour to use around the top and left borders.
		* @param aBr Colour to use around the bottom and right borders.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetPlinthColors(TRgb aTl,TRgb aBr);

		/**
		* Sets the font of the message text
		* @param	aHandle		The font handle
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetFont(TInt aFontHandle);
	};


#endif	// CLOCK_H

// End of File
