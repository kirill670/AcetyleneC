// EIKSCRLB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
		
#ifndef __EIKSCRLB_H__
#define __EIKSCRLB_H__

#include <eikbctrl.h>
#include <eiksbobs.h>
#include <eikscbut.h>
#include <lafpublc.h>

const TInt KEikScrollEventFromVBar=0;
const TInt KEikScrollEventFromHBar=0x01;
const TInt KEikScrollEventBarMask=0x01;

const TInt KButtonPositionMask=KLafScrollBarButtonPositionMask; // sets all bits in EButtonsXxx range
const TInt KDisplayComponentsMask=0x1f; // sets all bits in determining which components exist

/**
 *
 * Sets all inclusive margins.
 *
 * @param     "TInt aMargin"
 *            The value to use for all inclusive margins.
 */
class TEikScrollBarModel
	{
public:
	inline TEikScrollBarModel();
	IMPORT_C TEikScrollBarModel(TInt aScrollSpan,TInt aThumbSpan=0,TInt aThumbPosition=0);
	// operators
	IMPORT_C TBool operator==(const TEikScrollBarModel aModel) const;
	inline TBool operator!=(const TEikScrollBarModel aModel) const; 
public:
	IMPORT_C TBool ScrollBarUseful() const;
	IMPORT_C TInt MaxThumbPos() const;
	IMPORT_C void CheckBounds();
public:
	TInt iScrollSpan;
	TInt iThumbSpan;
	TInt iThumbPosition;            
	};


/**
 * Constructor.
 *
 * Creates, allocates and initialises a new
 * <code>TEikScrollBarModel</code>.
 */
inline TEikScrollBarModel::TEikScrollBarModel()
	{}

/**
 * Tests two models for inequality.
 *
 * The two models are the current model and the model specified by
 * <code>aModel</code>.
 *
 * @param     "const TEikScrollBarModel aModel"
 *            The model against which the current model is tested.
 * @returns   "TBool"
 *            <code>ETrue</code> if the two models are not equal.
 */
inline TBool TEikScrollBarModel::operator!=(const TEikScrollBarModel aModel) const { return !(*this==aModel); }

//
// CEikScrollBar
//

class CEikScrollButton;
class CEikScrollThumb;
  
/**
 *
 * A scroll bar.
 *
 * Scroll bars are used when all the content of another control cannot be
 * seen at the same time. They may be oriented horizontally or
 * vertically, and may be displayed in several ways.Scroll bars represent
 * integers, and have a maximum, a minimum, and a current position
 * encapsulated within their model. The on-screen image of a scroll bar
 * is calculated and displayed by the <code>CEikScrollBar</code> object,
 * and user changes to the scroll bar (and hence its model) are reported
 * to an interested class through the <code>MEikScrollBarObserver</code>
 * interface.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikScrollBar : public CEikBorderedControl, public MCoeControlObserver
	{
public:
	/**
	 * Scroll bar orientation.
	 */
	enum TOrientation
		{
		EVertical = SLafScrollBar::EVertical,		/** Scroll bar is oriented vertically. */
		EHorizontal = SLafScrollBar::EHorizontal	/** Scroll bar is oriented horizontally. */
		};

	/**
	 * Scroll bar initialisation flags.
	 *
	 * The default is for the scroll bar to have both a shaft and a thumb.
	 */
	enum TEikScrollBarFlags
		{
		EEikScrollBarDefaultBehaviour   =SLafScrollBar::EEikScrollBarDefaultBehaviour,
		EEikScrollBarNoNudgeButtons		=SLafScrollBar::EEikScrollBarNoNudgeButtons,	/** Does not display nudge buttons. */
		EEikScrollBarHasPageButtons		=SLafScrollBar::EEikScrollBarHasPageButtons,	/** Has buttons which move it a page at a time. */
		EEikScrollBarHasHomeEndButtons	=SLafScrollBar::EEikScrollBarHasHomeEndButtons,	/** Has buttons which move it its entire extent. */
		EEikScrollBarNoShaftOrThumb		=SLafScrollBar::EEikScrollBarNoShaftOrThumb,	/** Central area is empty. */
		EEikScrollBarShaftButNoThumb	=SLafScrollBar::EEikScrollBarShaftButNoThumb,	/** Central area has no scroll thumb. */
		EButtonsAtStartOfShaft			=SLafScrollBar::EButtonsAtStartOfShaft,			/** Buttons are placed at the start of the bar. */
		EButtonsAtEndOfShaft			=SLafScrollBar::EButtonsAtEndOfShaft,			/** Buttons are placed at the end of the bar. */

		/** Buttons are placed at either end of the bar
		(<code>EButtonsAtStartOfShaft | EButtonsAtEndOfShaft</code>). */
		EButtonsEitherSideOfShaft		=SLafScrollBar::EButtonsEitherSideOfShaft,

		/** Buttons do not automatically dim when scroll bar is at its maximum
		extent. */
		ENoAutoDimming					=SLafScrollBar::ENoAutoDimming		
		};

public:
	IMPORT_C ~CEikScrollBar();
	IMPORT_C CEikScrollBar();
public: // from CCoeControl
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	IMPORT_C virtual void ActivateL();
	IMPORT_C virtual void SetDimmed(TBool aDimmed);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);                 // not available before Release 005u
public:
	// second phase construction
	IMPORT_C virtual void ConstructL(MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
				TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);

	// set state functions
	IMPORT_C void SetLengthL(TInt aLength);
	IMPORT_C void SetModelL(const TEikScrollBarModel* aModel);
	IMPORT_C void SetLengthAndModelL(TInt aLength,const TEikScrollBarModel* aModel);
	IMPORT_C void SetModelThumbPosition(TInt aThumbPos);
	IMPORT_C static TInt DefaultScrollBarBreadth();
	inline void SetScrollBarObserver(MEikScrollBarObserver* aScrollBarObserver);    // not available before Release 005u

	// information retreival functions
	inline const TEikScrollBarModel* Model() const;
	IMPORT_C TInt ThumbPosition() const;
	IMPORT_C TInt ScrollBarBreadth() const;
	IMPORT_C static TInt MinVisibleLength(const TInt aScrollBarFlags);

	// Button dimming functions
	IMPORT_C void SetDecreaseButtonsDimmed(TBool aDimmed);
	IMPORT_C void SetIncreaseButtonsDimmed(TBool aDimmed);
	IMPORT_C void SetAllButtonsDimmed(TBool aDimmed);

protected:      // from CCoeControl
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from MCoeControlObserver
	IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);
private: // virtual - reserved from CCoeControl
	IMPORT_C virtual void Reserved_2();

protected:
	friend class CEikScrollBarFrame;
	/**
	 * Flags to determine whether there are visible components and whether to
	 * dim the increase, or decrease, buttons.
	 */
	enum TPrivateScrollBarFlags
		{
		ENoComponentsToDisplay          =0x10000,	/** There are no visible components in the scroll bar. */
		EIncreaseButtonsDimmed          =0x20000,	/** Dim the increase buttons. */
		EDecreaseButtonsDimmed          =0x40000	/** Dim the decrease buttons. */
		};
	/**
	 * Determines where on a scroll bar a pointer down event occurred.
	 */
	enum TPointerDownOn
		{
		ENone,					/** No pointer down event occurred on the scroll bar. */
		EHomeButton,			/** A pointer down event occurred on the home button. */
		EDecreasePageButton,	/** A pointer down event occurred on the decrease page button. */
		EDecreaseNudgeButton,	/** A pointer down event occurred on the decrease nudge button. */
		EDecreaseShaft,			/** A pointer down event occurred on the decrease shaft button. */
		EThumb,					/** A pointer down event occurred on the scroll bar thumb. */
		EIncreaseShaft,			/** A pointer down event occurred on the increase shaft button. */
		EIncreaseNudgeButton,	/** A pointer down event occurred on the increase nudge button. */
		EIncreasePageButton,	/** A pointer down event occurred on the increase page button. */
		EEndButton				/** A pointer down event occurred on the end button. */
		};

	/**
	 * Determines whether to redraw the scroll bar shaft.
	 */
	enum TShaftRedrawRequired
		{
		ENoRedrawRequired,		/** Do not redraw the scroll bar shaft. */
		ERedrawShaft			/** Redraw the scroll bar shaft. */
		};

	/**
	 * Determines which buttons are displayed.
	 */
	enum TWhichButtons
		{
		EIncreaseOnly,			/** Display the increase buttons only. */
		EDecreaseOnly,			/** Display the decrease buttons only. */
		EAll					/** Display all buttons. */
		};

	struct SEikScrollBarButtons
		{
		CEikScrollButton* iHome;
		CEikScrollButton* iDecreasePage;
		CEikScrollButton* iDecreaseNudge;
		CEikScrollButton* iIncreaseNudge;
		CEikScrollButton* iIncreasePage;
		CEikScrollButton* iEnd;
		};

public:
	void SetControlContextForAllComponents(MCoeControlContext* aContext);
protected:
	void HandleButtonEventL(const TPointerEvent& aPointerEvent, CEikScrollButton* aButton);
private:
	// construction/destruction
	IMPORT_C virtual void CreateButtonL(CEikScrollButton*& aButton,CEikScrollButton::TType aType);

	// pointer event functions
	void HandleShaftEventL(const TPointerEvent& aPointerEvent, TPointerDownOn aLastPointerDownOn);

	// drawing functions
	void DrawButtons(TWhichButtons aWhich) const;
	IMPORT_C virtual void DrawButtonsNow(TWhichButtons aWhich) const;
	void DrawShaft(CWindowGc& aGc) const;
	void DrawShaftNow() const;
	void DrawThumbInShaft(CWindowGc& aGc) const;
	void DrawThumbInShaftNow() const;
	void RedrawShaft(const TRect& aRect) const;

	// set state functions
	void MoveResizeThumbL(TShaftRedrawRequired aShaftRedrawRequired=ENoRedrawRequired);
	void NewThumbAtPixelL();
	void MoveThumbToPixel(TInt aPos);
	void UpdateThumbL();
	void UpdateButtonsL();
	void DoSetModel(const TEikScrollBarModel* aModel);

	// calculation
	TInt CalcThumbPixelPos() const;
	TInt CalcThumbModelPos() const;
	TInt MinReqLengthToDisplay() const;
	IMPORT_C virtual void CalcDisplayFlags();
	void AddShaftIfPossible(TInt aExcessSpace);
	void CheckModelBounds();

	// misc
	void GetShaftRect(TRect& aRect) const; 
	void CheckAutoButtonDimming(TDrawNow aDrawNow=EDrawNow);
	TPointerDownOn ResolveButtonPress(TInt aPos);
	TPointerDownOn GeneralizeButtonType(CEikScrollButton::TType aType) const;
	void ReportScrollEventL(TEikScrollEvent aEvent);
protected:
	void CreateRequiredComponentsL();
	void DestroyButton(CEikScrollButton*& aButton);
	void SetButtonAdjacency(CEikScrollButton* aButton);
	TInt NumberOfButtonPairs(TBool aUseDisplayFlags=EFalse) const;
	IMPORT_C virtual void DoSetLengthL(TInt aLength);
	IMPORT_C virtual void SetButtonPositionL(CEikScrollButton* aButton);
	IMPORT_C virtual void SetLayoutL();
public:
	TDblQueLink iSBLink;
protected:
	SEikScrollBarButtons iButtons;
	TOrientation iOrientation;
	TInt iScrollBarFlags;
	TInt iScrollBarDisplayFlags;
	TInt iLength;
	TInt iDecreaseButtonsStart;
	TInt iIncreaseButtonsStart;
	MEikScrollBarObserver* iScrollBarObserver;
	TInt iDecreaseButtonsEnd;
	TInt iIncreaseButtonsEnd;
	TPointerDownOn iPointerDownOn;
private:
	CEikScrollThumb* iThumb;
	TEikScrollBarModel iModel;
	// following quantities all in pixels
	TInt iThumbLength;
	TInt iThumbPos;
	TInt iShaftStart;
	TInt iShaftEnd;
	TInt iPointerOffsetFromThumb;
	TInt iDummy;
	};

/**
 *
 * An arrow head scroll bar.
 *
 * This consists of two small nudge button arrows, it has no shaft and so
 * takes up very little space.Scroll bars are used when all the content
 * of another control cannot be seen at the same time. They may be
 * oriented horizontally or vertically, and may be displayed in several
 * ways.Scroll bars represent integers, and have a maximum, a minimum,
 * and a current position encapsulated within their model. The on-screen
 * image of a scroll bar is calculated and displayed by the
 * <code>CEikArrowHeadScrollBar</code> object, and user changes to the
 * scroll bar (and hence its model) are reported to an interested class
 * through the <code>MEikScrollBarObserver</code> interface.
 *
 * @since 1.2
 * @lib "eikcoctl.lib"
 *
 * @internal
 * Internal to Symbian
 */
class CEikArrowHeadScrollBar : public CEikScrollBar
	{
public:
	IMPORT_C CEikArrowHeadScrollBar();
	IMPORT_C ~CEikArrowHeadScrollBar();
public: // from CEikScrollBar
	IMPORT_C void ConstructL(MEikScrollBarObserver* aScrollBarObserver,const CCoeControl* aParent,
				TOrientation aOrientation,TInt aLength,TInt aScrollBarFlags=EEikScrollBarDefaultBehaviour);
public: // from CCoeControl
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C void Draw(const TRect& aRect) const;
protected: // from CEikScrollBar
	void SetLayoutL();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CEikScrollBar
	void CreateButtonL(CEikScrollButton*& aButton,CEikScrollButton::TType aType);
	void DoSetLengthL(TInt aLength);
	void SetButtonPositionL(CEikScrollButton* aButton);
	void DrawButtonsNow(TWhichButtons aWhich) const;
	void CalcDisplayFlags();
private: // from CCoeControl
	void PositionChanged();
private:
	CCoeControl* iParentControl;
	};


/**
 * Sets the scroll bar observer.
 *
 * @param     "MEikScrollBarObserver* aScrollBarObserver"
 *            The scroll bar observer.
 */
inline void CEikScrollBar::SetScrollBarObserver(MEikScrollBarObserver* aScrollBarObserver)
	{ iScrollBarObserver=aScrollBarObserver; }

/**
 * Gets the scroll bar model used by this scroll bar.
 *
 * @returns   "TEikScrollBarModel*"
 *            The scroll bar model.
 */
inline const TEikScrollBarModel* CEikScrollBar::Model() const
	{ return &iModel; }


#endif
