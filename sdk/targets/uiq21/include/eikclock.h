// EIKCLOCK.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCLOCK_H__)
#define __EIKCLOCK_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__GULBORDR_H__)
#include <gulbordr.h>
#endif

//

class RAnimDll;
class RClock;
class RDigitalClock;
class RAnalogClock;
class CEikLocaleConformantClock;
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

class MEikClockContainer
	{
public:
	virtual TBool ClockIsVisible(const CEikLocaleConformantClock& aClock) const=0;
	virtual void GetClockPositionAndSize(TPoint& aPosition, TSize& aSize, const CEikLocaleConformantClock& aClock, const TSize& aMinimumSize)=0;
	};

//

class CEikLocaleConformantClock : public CActive
	{
protected:
	IMPORT_C CEikLocaleConformantClock(MEikClockContainer& aContainer, RAnimDll& aAnimDll, const RWindowBase& aWindow, TInt aType, TBool aTypeNeverChanges);
public:
	IMPORT_C void ConstructL(); // call this to construct a clock showing the home time (automatically updating as the OS's locale data changes)
	IMPORT_C void ConstructL(TTimeIntervalSeconds aUniversalTimeOffset, TDaylightSavingZone aDaylightSavingZone); // call this to construct a clock whose universal-time-offset and daylight-saving-zone are independent of the OS's locale data
	IMPORT_C virtual ~CEikLocaleConformantClock();
	IMPORT_C void ChangeFormatL(TClockFormat aFormat); // can only be called if the clock-type is *not* EEikLocaleConformantClockTypeChangesFormatAccordingToLocale
	IMPORT_C TClockFormat Format() const;
	IMPORT_C void ChangeUniversalTimeOffsetAndDaylightSavingZone(TTimeIntervalSeconds aUniversalTimeOffset, TDaylightSavingZone aDaylightSavingZone); // can only be called if it was constructed with the 2-parameter ConstructL
	IMPORT_C void GetUniversalTimeOffsetAndDaylightSavingZone(TTimeIntervalSeconds& aUniversalTimeOffset, TDaylightSavingZone& aDaylightSavingZone) const;
	IMPORT_C TTimeIntervalSeconds CompleteUniversalTimeOffset() const;
	IMPORT_C void SetVisible(TBool aVisible);
	IMPORT_C void SetPositionAndSize(const TPoint& aPosition, const TSize& aSize);
	IMPORT_C void SetPosition(const TPoint& aPosition);
	IMPORT_C void SetSize(const TSize& aSize);
	IMPORT_C void Draw(CWindowGc& aGc) const; // uses aGc's current brush settings
	IMPORT_C void RedrawAll(CWindowGc& aGc) const; // called when clock is displayed on backed up window (OPL)
	IMPORT_C TSize MinimumSize() const;
	IMPORT_C TRect Rect() const;
	IMPORT_C TBool HasBorder() const;
	IMPORT_C TBool IgnoresLocaleClockFormat() const;
	IMPORT_C TBool TypeNeverChanges() const;
	IMPORT_C static TInt PotentialWidthOfTextBlock(const TDesC& aTextBlock, const SEikLocaleAndFontData& aLocaleAndFontData);
	IMPORT_C void SetBackgroundColor(TRgb aBackgroundColor, TRgb aShadowColor);
protected:
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
	TBool iDrawBackground;
	TGulBorder iBorder;
	};

//

class CEikResourceConstructedClock : public CEikLocaleConformantClock
	{
public:
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
private:
	CCoeEnv& iCoeEnv;
	TInt iDigitalResourceId;
	TInt iAnalogResourceId;
	};

//

class CEikClock : public CEikBorderedControl, public MEikClockContainer
	{
public:
	IMPORT_C CEikClock();
	IMPORT_C void SetClock(CEikLocaleConformantClock* aClock); // takes ownership of aClock - to be called by container only if not constructed from resource
	IMPORT_C virtual ~CEikClock();
	// from CCoeControl
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C virtual void MakeVisible(TBool aVisible);
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader); // just calls CreateLocaleDependentL
	IMPORT_C virtual void ActivateL();
	IMPORT_C virtual TSize MinimumSize();
	IMPORT_C virtual TBool HasBorder() const;
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C virtual void HandleResourceChange(TInt aType);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	// framework
	IMPORT_C virtual void SizeChanged();
	IMPORT_C virtual void PositionChanged();
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	IMPORT_C virtual void Reserved_2();
	IMPORT_C virtual TBool ClockIsVisible(const CEikLocaleConformantClock& aClock) const;
	IMPORT_C virtual void GetClockPositionAndSize(TPoint& aPosition, TSize& aSize, const CEikLocaleConformantClock& aClock, const TSize& aMinimumSize);
	// other functions
	IMPORT_C virtual void ConstructClockL(CEikLocaleConformantClock& aClock); // override this if you want to call the CEikLocaleConformantClock::ConstructL with parameters
private:
	CEikLocaleConformantClock* iClock;
	};



#endif

