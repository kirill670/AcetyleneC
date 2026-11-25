// EIKCAPC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCAPC_H__)
#define __EIKCAPC_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__FEPBASE_H__)
#include <fepbase.h>
#endif

#if !defined(__EIKLABEL_H__)
#include <eiklabel.h>
#endif

class CEikCaptionedControl : public CCoeControl, public MCoeCaptionRetrieverForFep
	{
public:
	enum TSpaceSharingFlags
		{
		EIfTooSmallCtlGetsWidthLast			=0x0,
		EIfTooSmallCtlGetsWidthFirst		=0x1,
		EIfTooSmallCtlGetsEqualShareOfWidth	=0x2,
		EIfTooBigCtlStaysMinHeight			=0x4,
		EIfTooBigCtlStaysMinWidth			=0x8,
		EIfTooBigCtlStaysMinSize			=0xc
		};
public:
	IMPORT_C CEikCaptionedControl();
	IMPORT_C ~CEikCaptionedControl();
public: // new functions
	IMPORT_C void SetUsesEars();
	IMPORT_C void SetSpaceSharingFlags(TInt aFlags);
	IMPORT_C void SetExtraAscent();
	IMPORT_C void SetCaptionL(const TDesC& aText);
	IMPORT_C void SetTrailerL(const TDesC& aText);
	IMPORT_C void SetCurrent(TBool aSelected);
	IMPORT_C void CheckDimmedDisplayState();
	IMPORT_C void ResetMinimumSizes();
	IMPORT_C TBool IsLatent() const;
	IMPORT_C void SetLatent(TBool aLatent);
	IMPORT_C TBool LatentGroupLineFollows() const;
	IMPORT_C void SetLatentGroupLineFollows(TBool aLglf);
	IMPORT_C TBool DividerAfter() const;
	IMPORT_C void SetDividerAfter(TBool aDividerAfter);
	IMPORT_C TBool TakesEnterKey() const;
	IMPORT_C void SetTakesEnterKey(TBool aTakesEnter);
	IMPORT_C TBool OfferHotKeys() const;
	IMPORT_C void SetOfferHotKeys(TBool aOffer);
public: // Quartz specific extension
	IMPORT_C TBool IsCaptionAboveControl() const;			
	IMPORT_C void SetCaptionAboveControl(TBool aAbove);
	IMPORT_C TBool IsDenselyPacked() const;
	IMPORT_C void SetDenselyPacked(TBool aDense);
	IMPORT_C TBool UsesFullWidth() const;
	IMPORT_C void SetUseFullWidth(TBool aFullWidth);
public: // from CCoeControl
	IMPORT_C TSize MinimumSize();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C virtual void HandleResourceChange(TInt aType);
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
	IMPORT_C void SetDimmed(TBool aDimmed);
private: // from CCoeControl
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void SizeChanged();
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
protected: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
	// from MCoeCaptionRetrieverForFep
	IMPORT_C virtual void GetCaptionForFep(TDes& aCaption) const;
	IMPORT_C virtual void MCoeCaptionRetrieverForFep_Reserved_1();
	IMPORT_C virtual void MCoeCaptionRetrieverForFep_Reserved_2();
private:
	enum TWhichEars
		{
		ENoEar=0x00,
		ELeftEar=0x01,
		ERightEar=0x02,
		EBothEars=0x03
		};

private: // new functions
	TInt WidthForEars(TInt aWidthRemaining) const;
	void DrawEarsNow(TWhichEars aEar) const;
	void DrawEars(TWhichEars aEar) const;
	void DrawSingleEar(TWhichEars aEar,TBool aPressed) const;
	TRect EarRect(TWhichEars aEar) const;
	void FireEarL(TWhichEars aEar,TInt aEarRepeat);
	TInt SquashComponentWidth(TInt& aTotalWidth,const TInt aComponentWidthHint);
	void StretchComponents();
	void SquashComponents();

public:
	CCoeControl* iControl;
	CEikLabel* iCaption;
	CEikLabel* iTrailer;
	TInt iId;
	TInt iControlType;
	TAny* iReturnValue;
private:
	TSize iMinSize;
	TInt iCapCFlags;
	TInt iCaptionWidth;
	TInt iFullWidth;
	TInt iControlWidth;	// Quartz 6.0
	friend class CEikCapCArray;
	};



#endif
