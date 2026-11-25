// CLOCK.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// public clock header
//
// $Workfile:   CLOCK.H  $
// $Revision:   1.6  $
// $Author:   marcos  $
// $Date:   27 Apr 1999 11:12:32  $

#if !defined(__CLOCK_H__)
#define __CLOCK_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

//
// miscellaneous typedefs
//

typedef TBuf8<1024> TConstructorBuf8; // implementation class

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

/**
 *
 * Horizontal alignment options for text in a digital clock's display.
  */
enum TDigitalDisplayHorizontalTextAlignment
	{
	/** Left align text.
	 */
	EDigitalDisplayHorizontalTextAlignmentLeft,
	/** Centre align text.
	 */
	EDigitalDisplayHorizontalTextAlignmentCenter,
	/** Right align text.
	 */
	EDigitalDisplayHorizontalTextAlignmentRight
	};

//

/**
 *
 * Vertical alignment options for text in a digital clock's display.
  */
enum TDigitalDisplayVerticalTextAlignment
	{
	/** Top alignm text.
	 */
	EDigitalDisplayVerticalTextAlignmentTop,
	/** Centre align text, including the character descent.
	 */
	EDigitalDisplayVerticalTextAlignmentCenterInclDescent,
	/** Centre align text, excluding the character descent.
	 */
	EDigitalDisplayVerticalTextAlignmentCenterExclDescent,
	/** Bottom align text, including the character descent.
	 */
	EDigitalDisplayVerticalTextAlignmentBottomInclDescent,
	/** Bottom align text, excluding the character descent.
	 */
	EDigitalDisplayVerticalTextAlignmentBottomExclDescent
	};

//

/**
 *
 * Special characters that can be used in a digital clock display.
  */
enum TDigitalDisplayLayoutChar
	{
	/** A flashing block to delimit different sections of the display.
	 */
	EDigitalDisplayLayoutCharFlashingBlockDelimiter=1
	};

//


/**
 *
 * Different types of hand for an analogue clock.
 */
enum TAnalogDisplayHandType
	{
	/** A hand that performs one revolution every 12 hours.
 	 */	
	EAnalogDisplayHandOneRevPer12Hours,
	/** A hand that performs one revolution every hour.
	 */
	EAnalogDisplayHandOneRevPerHour,
	/** A hand that performs one revolution every minute.
	 */
	EAnalogDisplayHandOneRevPerMinute
	};

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
	IMPORT_C TAnalogDisplayHand(TAnalogDisplayHandType aType);
	IMPORT_C void AddLine(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																const TPoint& aStartPoint, const TPoint& aEndPoint);
	IMPORT_C void AddPolyLine(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																CGraphicsContext::TBrushStyle aBrushStyle, TRgb aBrushColor,
																TBool aClosed, const CArrayFix<TPoint>* aPointList); // aPointList is not destroyed
	IMPORT_C void AddCircle(CGraphicsContext::TPenStyle aPenStyle, TRgb aPenColor, const TSize& aPenSize,
																CGraphicsContext::TBrushStyle aBrushStyle, TRgb aBrushColor,
																const TPoint& aCircleCenter, TInt aRadius);	
	/**
	 *
	 * Gets the number of features added to the hand.
	 *
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
	RAnimWithUtils(RAnimDll& aAnimDll, const RWindowBase& aWindow);
	void AppendToConstructorBufL(const TDesC8& aData);
	void SendConstructorBufIfCompleteL(TInt aAnimatedObjectType);
	void SendConstructorBufL(TInt aAnimatedObjectType);
	TBool ConstructorBufExists() const;
	TBool ConstructorBufAlreadySent() const;
	TConstructorBuf8& ConstructorBuf() const;
	void SetNumAdditionsStillExpected(TInt aNumAdditionsStillExpected);
public:
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
 *
 * Sets display parameters for clocks.
 *
 *
 *
 * @since 5.0
 * @lib "clock.lib"
 */
class RTimeDevice : public RAnimWithUtils
	{
protected:
	RTimeDevice(RAnimDll& aAnimDll, const RWindowBase& aWindow);
	void AppendDisplayTypeL(TDisplayType aType);
	void AppendDigitalDisplayConstructorArgsL(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow,
																TRgb aBackgroundColor, TInt aNumTextSections);
	void AppendAnalogDisplayConstructorArgsL(const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins, const STimeDeviceShadow& aShadow,
																TInt aFaceHandle, TInt aFaceMaskHandle, TInt aNumHands, const SAnalogDisplayAmPm* aAmPm);
public:
	IMPORT_C void SetVisible(TBool aVisible); // can only be called after full construction - by default clocks are invisible
	IMPORT_C void SetPositionAndSize(const TPoint& aPosition, const TSize& aSize); // can only be called after full construction
	IMPORT_C void SetPosition(const TPoint& aPosition); // can only be called after full construction
	IMPORT_C void SetSize(const TSize& aSize); // can only be called after full construction
	IMPORT_C void UpdateDisplay(); // can only be called after full construction
	IMPORT_C void Draw(); // can only be called after full construction
	};

//

/**
 *
 * Sets the time for clocks.
 *
 *
 *
 * @since 5.0
 * @lib "clock.lib"
 */
class RClock : public RTimeDevice
	{
protected:
	RClock(RAnimDll& aAnimDll, const RWindowBase& aWindow);
	void AppendClockConstructorArgsL(TTimeIntervalSeconds aUniversalTimeOffset);
public:
	IMPORT_C void SetUniversalTimeOffset(TTimeIntervalSeconds aUniversalTimeOffset); // can only be called after full construction
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
	IMPORT_C RDigitalClock(RAnimDll& aAnimDll, const RWindowBase& aWindow);
	IMPORT_C void ConstructL(TTimeIntervalSeconds aUniversalTimeOffset, const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins,
																const STimeDeviceShadow& aShadow, TRgb aBackgroundColor, TInt aNumTextSections);
	IMPORT_C void AddTextSectionL(const TDigitalDisplayTextSection& aTextSection);
	IMPORT_C void SetBackgroundColor(TRgb aBackgroundColor, TRgb aShadowColor); // can only be called after full construction
	IMPORT_C void SetTextColor(TRgb aTextColor);

	};

//

/**
 *
 * An analogue clock.
 * @since 5.0
 * @lib "clock.lib"
 */
class RAnalogClock : public RClock
	{
public:
	IMPORT_C RAnalogClock(RAnimDll& aAnimDll, const RWindowBase& aWindow);
	IMPORT_C void ConstructL(TTimeIntervalSeconds aUniversalTimeOffset, const TPoint& aPosition, const TSize& aSize, const TMargins& aMargins,
																const STimeDeviceShadow& aShadow, TInt aFaceHandle, TInt aFaceMaskHandle, TInt aNumHands, const SAnalogDisplayAmPm* aAmPm=NULL);
																// N.B. the bitmap(s) passed in to aFaceHandle and aFaceMaskHandle in these
																// ConstructL functions cannot be destroyed until the RAnalogClock has been
																// completely constructed, including all necessary calls to
																// RAnalogClock::AddHandL() - aFaceMaskHandle may be 0
	IMPORT_C void AddHandL(const TAnalogDisplayHand& aHand);
	IMPORT_C void SetBackgroundColor(TRgb aBackgroundColor, TRgb aShadowColor); // can only be called after full construction
	IMPORT_C void SetTextColor(TRgb aTextColor);
	IMPORT_C void SetPenColor(const TRgb aPenColor);
	IMPORT_C void SetBrushColor(const TRgb aBrushColor);
	};

//
// message-window class
//

class RMessageWindow : public RAnimWithUtils
	{
public:
	enum
		{
		EMaxTextLength=80
		};
public:
	IMPORT_C RMessageWindow(RAnimDll& aAnimDll, const RWindowBase& aWindow);
	IMPORT_C void ConstructL(TInt aBaselineOffset, TInt aFontHandle, TRgb aBackgroundColor, TRgb aTextColor);
	IMPORT_C void ConstructL(TInt aBaselineOffset, TInt aFontHandle, TRgb aBackgroundColor, TRgb aTextColor, TRgb aBorderColor);
	IMPORT_C void StartDisplay(TBool aFlash, TTimeIntervalMicroSeconds32 aInitialDelay, const TDesC& aText);
	IMPORT_C void StartDisplay(TBool aFlash, TTimeIntervalMicroSeconds32 aInitialDelay, TTimeIntervalMicroSeconds32 aDuration, const TDesC& aText);
	IMPORT_C void CancelDisplay();
	IMPORT_C void GetBorders(TMargins& aBorders);
	IMPORT_C void SetBackgroundColor(TRgb aBackgroundColor);
	IMPORT_C void SetTextColor(TRgb aTextColor);
	IMPORT_C void SetBorderColor(TRgb aBorderColor);
	IMPORT_C void SetPlinthColors(TRgb aTl,TRgb aBr);
	};

#endif

