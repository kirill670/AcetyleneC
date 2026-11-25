// EIKSBFRM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
	
#if !defined(__EIKSBFRM_H__)
#define __EIKSBFRM_H__

#include <lafpublc.h>
#include <eikscrlb.h>


/**
 *
 * Enables you to set the frame layout for a scroll bar.
 * @since 1.2
 * @lib "eikcoctl.lib"
 */
class TEikScrollBarFrameLayout
	{
public:
	/**
	 * Determines whether the client rectangle, or the inclusive rectangle,
	 * remains constant.
	 */
	enum TTilingMode
		{
		EClientRectConstant,		/** The client rectangle rectangle remains constant. */
		EInclusiveRectConstant		/** The inclusive rectangle remains constant. */
		};
public:
	// c'tor
	IMPORT_C TEikScrollBarFrameLayout();

	// set all margins to the same value
	IMPORT_C void SetInclusiveMargin(TInt aMargin);
	IMPORT_C void SetClientMargin(TInt aMargin);
public:
	TMargins iInclusiveMargin;
	TMargins iClientMargin;
	TSize iClientAreaGranularity;
	TTilingMode iTilingMode;
	};


// 
// CEikScrollBarFrame
//

class CEikCornerWindow;

/**
 *
 * The scroll bar frame is a control assemblage manager that relates a
 * control, or control body, to two scroll bars and a corner window.
 *
 * A corner window is that part of the screen that is common to both the
 * horizontal, and the vertical elements of a scroll bar.This class helps
 * with access to, and set up of, scroll bars and also with the layout of
 * the scrolled control or control body. A scroll bar frame is not a
 * control, but it does implement the standard control composite pattern
 * to manage the assemblage.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikScrollBarFrame : public CBase
	{
public:	// enums
	/**
	 * Defines the scroll bars visibility.
	 */
	enum TScrollBarVisibility
		{
		EOff,		/** Scroll bar not visible. */
		EOn,		/** Scroll bar visible. */
		EAuto		/** Scroll bar visible if required. */
		};

	/**
	 * Defines where the scroll bar is located.
	 */
	enum TScrollBarSide
		{
		/** Scroll bar located at the bottom, or to the right of the scroll bar
		frame.	 */
		EBottomOrRight				=SLafScrollBarFrame::EBottomOrRight,

		/** Scroll bar located at the top, or to the left of the scroll bar frame.
		 */
		ETopOrLeft					=SLafScrollBarFrame::ETopOrLeft		
		};

	/**
	 * Determines how the scroll bar frame manages scroll bars.
	 */
	enum TScrollBarManagement
		{
		/** The scroll bar frame creates, destroys and recreates, scroll bars
		according to the visibility mode. The scroll bar frame also acts as an
		intermediary with its owning control so that the scroll bars can be
		treated as component controls.	 */
		EComponent					=SLafScrollBarFrame::EComponent,

		/** The scroll bar frame creates, destroys and recreates, scroll bars
		according to the visibility mode. In this case, the scroll bars are
		not treated as component controls. Instead, the scroll bars are
		geometry managed in windows floating above the control window and
		their position is determined in relation to the frames position on the
		screen.	 */
		EFloating					=SLafScrollBarFrame::EFloating,

		/** The scroll bar frame uses the central application scroll bar as held
		in the environment. This scroll bar is neither owned by the frame nor
		treated as a component control of the frames owner.	 */
		EApplicationScrollBar		=SLafScrollBarFrame::EApplicationScrollBar
		};

public:	// deprecated
	/**
	 * Defines the type of scroll bar.
	 * @deprecated
	 */
	enum TScrollBarType
		{
		ENormalScrollBar			=0x0000,	/** Scroll bar complete with shaft. */
		EArrowHead					=0x1000		/** Floating arrow head scroll bar, without shaft. */
		};

private:
	class TScrollBarAttributes
		{
	public:
		TScrollBarAttributes();
	public:
		TInt iControlType;
		TInt iBreadth;
		TScrollBarSide iSide;
		TScrollBarManagement iManagement;
		};

public:	// specific
	IMPORT_C CEikScrollBarFrame(CCoeControl* aParentWindow, MEikScrollBarObserver* aObserver, TBool aPreAlloc=EFalse);
	IMPORT_C ~CEikScrollBarFrame();

	// drawing
	IMPORT_C void DrawScrollBarsNow() const;

	// scrollbar visibility functions
	IMPORT_C void SetScrollBarVisibilityL(TScrollBarVisibility aHVisibility, TScrollBarVisibility aVVisibility);
	inline TScrollBarVisibility HScrollBarVisibility() const;
	inline TScrollBarVisibility VScrollBarVisibility() const;

	// scrollbar dimming
	IMPORT_C void SetScrollBarsDimmed(TBool aHDimmed, TBool aVDimmed) const;

	// Tile  - the main function
	IMPORT_C TBool TileL(TEikScrollBarModel* aHModel, TEikScrollBarModel* aVModel,
			  TRect& aClientRect, TRect& aInclusiveRect, const TEikScrollBarFrameLayout& aLayout);

	// move scrollbar thumbs functions
	IMPORT_C void MoveThumbsBy(TInt aDeltaX, TInt aDeltaY) const;
	IMPORT_C void MoveThumbTo(CEikScrollBar::TOrientation aOrientation, TInt aThumbPos) const;

 	IMPORT_C TInt ScrollBarBreadth(CEikScrollBar::TOrientation aOrientation) const;

	// scroll bar frame behavior functions
	IMPORT_C void SetAdjustsModel(CEikScrollBar::TOrientation aOrientation, TBool aAdjusts);
	IMPORT_C TBool AdjustsModel(CEikScrollBar::TOrientation aOrientation) const;

	// scrollbar flags functions
	inline void SetFlagsForHScrollBar(TInt aMask);
	inline void SetFlagsForVScrollBar(TInt aMask);
	inline void ClearFlagsForHScrollBar(TInt aMask);
	inline void ClearFlagsForVScrollBar(TInt aMask);
	inline TInt FlagsForHScrollBar() const;
	inline TInt FlagsForVScrollBar() const;

	// does a scrollbar exist? function
	IMPORT_C TBool ScrollBarExists(CEikScrollBar::TOrientation aOrientation) const;

	// component control functions
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C CEikScrollBar* GetScrollBarHandle(CEikScrollBar::TOrientation aOrientation) const;

	// application scroll bar utilities
	IMPORT_C static CEikScrollBar* ApplicationScrollBar(CEikScrollBar::TOrientation aOrientation);
	IMPORT_C static void AddApplicationScrollBarL(CEikScrollBar::TOrientation aOrientation, CEikScrollBar& aScrollBar);
	IMPORT_C static void RemoveApplicationScrollBar(CEikScrollBar::TOrientation aOrientation, CEikScrollBar& aScrollBar);

	// scroll bar attributes functions
	IMPORT_C void SetScrollBarManagement(CEikScrollBar::TOrientation aOrientation, TScrollBarManagement aManagement);
	IMPORT_C TScrollBarManagement ScrollBarManagement(CEikScrollBar::TOrientation aOrientation) const;
	IMPORT_C void SetScrollBarControlType(CEikScrollBar::TOrientation aOrientation, TInt aControlType);
	IMPORT_C TInt ScrollBarControlType(CEikScrollBar::TOrientation aOrientation) const;
	IMPORT_C void SetScrollBarSide(CEikScrollBar::TOrientation aOrientation, TScrollBarSide aSide);
	IMPORT_C TScrollBarSide ScrollBarSide(CEikScrollBar::TOrientation aOrientation) const;
	IMPORT_C void SetScrollBarBreadth(CEikScrollBar::TOrientation aOrientation, TInt aBreadth);
	IMPORT_C void SetObserver(MEikScrollBarObserver* aObserver);
public:	// Do not use
	IMPORT_C void SetAdjustsHorizontalModel(TBool aAdjusts); 
	IMPORT_C void SetAdjustsVerticalModel(TBool aAdjusts);
	IMPORT_C TBool AdjustsHorizontalModel() const;
	IMPORT_C TBool AdjustsVerticalModel() const;
	IMPORT_C void MoveHorizThumbTo(TInt aHorizThumbPos) const;
	IMPORT_C void MoveVertThumbTo(TInt aVertThumbPos) const;
	IMPORT_C void SetTypeOfHScrollBar(TScrollBarType aType);
	IMPORT_C void SetTypeOfVScrollBar(TScrollBarType aType);
	IMPORT_C void SetSideOfHScrollBar(TScrollBarSide aSide);
	IMPORT_C void SetSideOfVScrollBar(TScrollBarSide aSide);
	IMPORT_C TScrollBarType TypeOfHScrollBar() const;
	IMPORT_C TScrollBarType TypeOfVScrollBar() const;
	IMPORT_C TBool RightSideForHScrollBar() const;
	IMPORT_C TBool RightSideForVScrollBar() const;
	IMPORT_C TBool IsArrowHeadScrollBar(TInt aFlag) const;
private:
	// enums
	enum TMarginsAdjustmentMode
		{
		EGrow,
		EShrink
		};
private:
	void CalcTheoreticalScrollBarVisibility(const TEikScrollBarModel* aHModel, const TEikScrollBarModel* aVModel);
	void CheckPhysicalScrollBarVisibility(TEikScrollBarModel* aHModel, TEikScrollBarModel* aVModel, const TRect& aOutputRect, const TEikScrollBarFrameLayout& aLayout);
	void AdjustRect(TRect& aOutputRect, TEikScrollBarFrameLayout::TTilingMode aTilingMode) const;
	void CreateOrRemoveRequiredScrollBarsL();
	void RemoveScrollBar(CEikScrollBar*& aScrollBar);
	void TileScrollBarsWithClientL(const TRect& aClientRect, const TEikScrollBarModel* aHModel, const TEikScrollBarModel* aVModel);
	TBool AdjustScrollBarModel(CEikScrollBar::TOrientation aOrientation, TEikScrollBarModel* aModel, TInt aNewPixelThumbSpan, const TEikScrollBarFrameLayout& aLayout) const;
	void AdjustRectByMargins(TMarginsAdjustmentMode aMode, TRect& aRect, const TMargins& aMargins) const;
	CEikScrollBar* CreateSBarLC(CEikScrollBar::TOrientation aOrientation,TInt aFlags) const;
	CEikScrollBar* CreateHSBarLC() const;
	CEikScrollBar* CreateVSBarLC() const;
	CEikCornerWindow* CreateCornerWindowLC() const;
	static void CheckVisible(CCoeControl* aComponent);
private:
	TScrollBarVisibility iHVisibility;
	TScrollBarVisibility iVVisibility;
	MEikScrollBarObserver* iObserver;
	CCoeControl* iParentWindow;
	CEikCornerWindow* iCornerWindow;
	CEikScrollBar* iHSbar;
	CEikScrollBar* iVSbar;
	TInt iScrollBarFrameFlags;
	TInt iHScrollBarFlags;
	TInt iVScrollBarFlags;
	TScrollBarAttributes iHAttributes;
	TScrollBarAttributes iVAttributes;
	};

//
// Inlines
//

/**
 * Determines the horizontal scroll bars visibility.
 *
 * @returns   "TScrollBarVisibility"
 *            Visibility for horizontal scroll bar.
 */
inline CEikScrollBarFrame::TScrollBarVisibility CEikScrollBarFrame::HScrollBarVisibility() const
	{ return iHVisibility; }

/**
 * Determines the vertical scroll bars visibility.
 *
 * @returns   "TScrollBarVisibility"
 *            Visibility for vertical scroll bar.
 */
inline CEikScrollBarFrame::TScrollBarVisibility CEikScrollBarFrame::VScrollBarVisibility() const
	{ return iVVisibility; }

/**
 * Specifies flags for the horizontal scroll bar.
 *
 * @param     "TInt aMask"
 *            Flags for the horizontal scroll bar.
 */
inline void CEikScrollBarFrame::SetFlagsForHScrollBar(TInt aMask)
	{ iHScrollBarFlags|=aMask; }

/**
 * Specifies flags for the vertical scroll bar.
 *
 * @param     "TInt aMask"
 *            Flags for the vertical scroll bar.
 */
inline void CEikScrollBarFrame::SetFlagsForVScrollBar(TInt aMask)
	{ iVScrollBarFlags|=aMask; }

/**
 * Clears horizontal scroll bar flags.
 *
 * @param     "TInt aMask"
 *            Horizontal scroll bar flags.
 */
inline void CEikScrollBarFrame::ClearFlagsForHScrollBar(TInt aMask)
	{ iHScrollBarFlags&=(~aMask); }

/**
 * Clears vertical scroll bar flags.
 *
 * @param     "TInt aMask"
 *            Vertical scroll bar flags.
 */
inline void CEikScrollBarFrame::ClearFlagsForVScrollBar(TInt aMask)
	{ iVScrollBarFlags&=(~aMask); }

/**
 * Gets the flags that are specified for the horizontal scroll bar.
 *
 * @returns   "TInt"
 *            Horizontal scroll bar flags.
 */
inline TInt CEikScrollBarFrame::FlagsForHScrollBar() const
	{ return iHScrollBarFlags; }

/**
 * Gets the flags that are specified for the vertical scroll bar.
 *
 * @returns   "TInt"
 *            Vertical scroll bar flags.
 */
inline TInt CEikScrollBarFrame::FlagsForVScrollBar() const
	{ return iVScrollBarFlags; }

#endif
