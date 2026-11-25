// EIKCHLST.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCHLST_H__)
#define __EIKCHLST_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#if !defined(__EIKTXLBX_H__)
#include <eiktxlbx.h>
#endif

#if !defined(__GULALIGN_H__)
#include <gulalign.h>
#endif

//
// class CEikChoiceListBase
//

class CEikCommandButton;
class TResourceReader;
class RIncrMatcherBase;

class CEikChoiceListBase : public CEikBorderedControl, public MCoeControlObserver
	{
public:
	enum { KEikMaxMatchingBufLength=24 };
	enum TFlags
		{
		EArrayOwnedExternally	=0x01,
		EIncrementalMatching	=0x02,
		ENoPopout				=0x04
		};
public: // new functions
	IMPORT_C ~CEikChoiceListBase();
	IMPORT_C TInt CurrentItem() const;
	IMPORT_C void SetCurrentItem(TInt aItem);
	IMPORT_C void SetIncrementalMatching(TBool aAllowIncrementalMatching);
	IMPORT_C void SetArrayExternalOwnership(TBool aArrayOwnedExternally);
	inline MDesCArray* Array() const;
	IMPORT_C void SetArrayL(TInt aResourceId);
	IMPORT_C void SetArrayL(MDesCArray* aArray);
	IMPORT_C CDesCArray* DesCArray() const;
	IMPORT_C void AllowPopout(TBool aAllow);
	IMPORT_C void SetFont(const CFont* aFont);
	IMPORT_C static TInt TextEdgeMargin();
protected: // framework
	IMPORT_C void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aEventCode);
	IMPORT_C void SizeChanged();
	IMPORT_C void ActivateL();
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C void SetAdjacent(TInt aAdjacent);
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
protected: // new functions
	IMPORT_C CEikChoiceListBase();
	IMPORT_C TInt CursorPos() const;
	IMPORT_C void ResetMatchBuf();
	IMPORT_C TInt CalculateTextWidth() const;
	virtual void CreatePopoutL()=0;
	virtual void DestroyPopout()=0;
	IMPORT_C virtual TInt PopoutCurrentItem() const;
	virtual void DrawContent() const=0;
	IMPORT_C void DrawContentNow() const;
	IMPORT_C virtual void HandleInteractionConfirmedL();
	IMPORT_C virtual void CurrentItemChangedL();
	IMPORT_C void DestroyArray();
	IMPORT_C virtual void MatchTypedChar(TUint aCode);
	IMPORT_C void UndoLastChar();
	IMPORT_C void DisplayCursor();
	IMPORT_C void ContentHasChangedL();
	IMPORT_C const CFont* Font() const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	IMPORT_C virtual void Reserved_3();
protected:
	MDesCArray* iArray;
	RIncrMatcherBase* iMatchBuf;
	TInt iChoiceListFlags;
	TInt iCurrentItem;
	TInt iMaxDisplayChar;
	TInt iAscent;
private:
	TInt iCursorPos;
	const CFont* iChlstFont;
	TInt iSpare;
	};


inline MDesCArray* CEikChoiceListBase::Array() const
	{return iArray;};

class CEikListBox;
class CEikTextListBox;

class CEikChoiceList : public CEikChoiceListBase
	{
public:
	enum TTextAlignment
		{
		ELeft=CGraphicsContext::ELeft,
		ECenter=CGraphicsContext::ECenter,
		ERight=CGraphicsContext::ERight
		};

	IMPORT_C void SetTextAlignment(TTextAlignment aTextAlignment);
	IMPORT_C void SetArrowVisible(TBool aArrowVisible);

	IMPORT_C ~CEikChoiceList();
	IMPORT_C CEikChoiceList();
	IMPORT_C void ConstructL(CCoeControl* aParent, TInt aFlags, TInt aMaxDisplayChar);
	IMPORT_C CEikTextListBox* PopoutTextListBox() const;
public: // from CCoeControl
	IMPORT_C virtual TSize MinimumSize();
	IMPORT_C virtual void MakeVisible(TBool aVisible);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C virtual void HandleResourceChange(TInt aType);
protected:
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C virtual void CreatePopoutL();
	IMPORT_C virtual void DestroyPopout();
	IMPORT_C virtual TInt PopoutCurrentItem() const;
	IMPORT_C virtual void DrawContent() const;
	IMPORT_C virtual void DoDrawContent(const TDesC& aDes) const;
	IMPORT_C virtual void DoCreatePopoutL();
	IMPORT_C virtual void CreateListBoxL();
	IMPORT_C virtual void InitializeListBoxL();
	IMPORT_C virtual void SetListBoxExtentL();
	IMPORT_C virtual void ActivateListBoxL();
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikChoiceListBase
	IMPORT_C void Reserved_3();
protected:
	CEikListBox* iPopoutListBox;

private:
	TTextAlignment iTextAlignment;
	TBool iArrowVisible;
	};

class CEikChoiceListPopoutListBox : public CEikTextListBox
	{
public:
	IMPORT_C CEikChoiceListPopoutListBox();
	IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aFlags,const CFont* aFont);
	};

#endif
