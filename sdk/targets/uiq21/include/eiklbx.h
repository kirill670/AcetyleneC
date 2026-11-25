// EIKLBX.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKLBX_H__)
#define __EIKLBX_H__

#include <gdi.h>
#include <eikbctrl.h>
#include <eiklbo.h>
#include <eiksbfrm.h>
#include <eiklbm.h>
#include <eiklbv.h>
#include <gulbordr.h>
#include <eiklbed.h>
#include <gulutil.h>
#include <lafpublc.h>
#include <eiklbvo.h>

enum TKeyCode;
class RIncrMatcherBase;
class CListItemDrawer;
class CEikScrollBarFrame;
class CEikButtonBase;
class CMatchBuffer;
class CListBoxExt;

/**
 *
 * Base class for an on-screen list box control from which one or more
 * items can be selected.
 *
 * <code>CEikListBox</code> implements the basics of a list box it has a
 * scroll bar frame, an item drawer, and a model, and reports events to a
 * list box observer.List boxes display a number of items within a
 * scrolling frame; the items in a list box which are visible at one time
 * are represented by a list box view. Writing derived classes:This class
 * may be derived from to provide specialisations of the basic list box
 * behaviour. It is usual when subclassing <code>CEikListBox</code> to
 * also provide specialisations of <code>CListItemDrawer</code> and
 * <code>CListBoxView</code> for representing the data of such a list box
 * effectively.
 *
 * @since 6.0
 * @lib " eikcoctl.lib "
 */
class CEikListBox : public CEikBorderedControl, public MEikScrollBarObserver
	{
public:
	friend class CListBoxExt;
protected:
	enum TProtectedFlags
		{
		EShowPartiallyVisibleItems	= 0x80000000,
		ESmoothVerticalScrolling	= 0x40000000
		};
public:
	/**
	 * Construction flags.
	 *
	 * The <code>aFlags</code> argument of
	 * <code>CEikListBox::ConstructL()</code> is formed from an ORed
	 * combination of the following flag values:
	 */
	enum TFlags
		{
		EMultipleSelection			= SLafListBox::EMultipleSelection,		/** User can select more than one item from this list box. */
		ENoExtendedSelection		= SLafListBox::ENoExtendedSelection,	/** If set, extended selection using SHIFT is not possible. */
		EIncrementalMatching		= SLafListBox::EIncrementalMatching,	/** List box matches users keystrokes incrementally. */
		EPopout						= SLafListBox::EPopout,					/** List box is a pop-out list box. Pop-out list boxes handle certain keystrokes and events differently. */
		ELeftDownInViewRect			= SLafListBox::ELeftDownInViewRect,		/** If set, indicates the pointer being pressed inside the view rectangle of the list box. */
		EItemDoubleClicked			= SLafListBox::EItemDoubleClicked,		/** If set, indicates the <code>CEikListBox</code> item was double clicked. */

		/** If set, the <code>CEikListBox</code> does not take ownership of the
		supplied list box model, and will not delete it upon its destruction.
		 */
		EKeepModel					= SLafListBox::EKeepModel,

		/** If set, the scroll bar is drawn outside the window describing the
		extent of the scroll box.
		 */
		EScrollBarSizeExcluded		= SLafListBox::EScrollBarSizeExcluded,
		EStateChanged				= SLafListBox::EStateChanged,			/** If set, indicates the <code>CEikListBox</code> has changed. */
		ECreateOwnWindow			= SLafListBox::ECreateOwnWindow,		/** The list box should create its own window. */
        ENoFirstLetterMatching      = SLafListBox::ENoFirstLetterMatching,	/** List box does not permit any key press matching. */
		EPaintedSelection			= SLafListBox::EPaintedSelection,		/** Different selection draw mode. */
		EHiddenHighlight			= SLafListBox::EHiddenHighlight			/** When set, the highlight is hidden until the next pointer event, or consumed key event. */
		};
	/**
	 * Miscellaneous constants.
	 */
	enum
		{
		KEikMaxMatchingBufferLength = 22	/** Maximum length of incremental match buffer (=22). */
		};
protected:
	enum TReasonForFocusLost
		{ EFocusLostToExternalControl, EFocusLostToInternalEditor };
public:
	// construction/initialization
	IMPORT_C ~CEikListBox();
	IMPORT_C CEikListBox();
	IMPORT_C void ConstructL(MListBoxModel* aListBoxModel,CListItemDrawer* aListItemDrawer,const CCoeControl* aParent,TInt aFlags = 0);
	IMPORT_C void ConstructL(MListBoxModel* aListBoxModel,CListItemDrawer* aListItemDrawer,const CCoeControl* aParent, TGulBorder aBorder, TInt aFlags = 0);

	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aContainer);
	IMPORT_C virtual TSize MinimumSize();
	IMPORT_C virtual void SetDimmed(TBool aDimmed);

	// from MEikScrollBarObserver
	IMPORT_C virtual void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType);

	// model/view access functions 
	IMPORT_C MListBoxModel* Model() const;
	IMPORT_C CListBoxView* View() const;

	// functions for accessing top/current/bottom item index
	IMPORT_C TInt TopItemIndex() const;	 
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex) const;
	IMPORT_C TInt BottomItemIndex() const;
	IMPORT_C TInt CurrentItemIndex() const;	  
	IMPORT_C void SetCurrentItemIndex(TInt aItemIndex) const;
	IMPORT_C void SetCurrentItemIndexAndDraw(TInt aItemIndex) const;
	IMPORT_C void HideHighlight(TBool aHide, TDrawNow aDraw);
	IMPORT_C TBool HighlightIsHidden() const;

	// functions for dealing with the selection state
	IMPORT_C const CListBoxView::CSelectionIndexArray* SelectionIndexes() const;
	IMPORT_C void SetSelectionIndexesL(CListBoxView::CSelectionIndexArray* aArrayOfSelectionIndexes);
	IMPORT_C void ClearSelection();	

	// functions for updating a listbox's internal state after its model has been updated
	IMPORT_C void HandleItemAdditionL();
	IMPORT_C void HandleItemRemovalL();
	IMPORT_C void Reset();

	// functions for accessing the item height
	IMPORT_C virtual void SetItemHeightL(TInt aHeight);
	IMPORT_C void SetItemHeightL(TInt aItemIndex, TInt aItemHeight);
	IMPORT_C void SetToDefaultItemHeight(TInt aItemIndex);
	IMPORT_C TInt ItemHeight() const;
	IMPORT_C TInt ItemHeight(TInt aItemIndex) const;

	// functions for scrollbars
	IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL(TBool aPreAlloc=EFalse);
	IMPORT_C CEikScrollBarFrame* const ScrollBarFrame();
	IMPORT_C void UpdateScrollBarsL();

	// construction support functions
	IMPORT_C void CalculatePopoutRect(TInt aTargetItemIndex, TInt aTargetYPos, TRect& aListBoxRect, TInt aMinHeightInNumOfItems = 1);
	IMPORT_C TSize CalcSizeInPixels(TInt aWidthAsNumOfChars, TInt aHeightAsNumOfItems) const;
	IMPORT_C TInt CalcWidthBasedOnNumOfChars(TInt aNumOfChars) const;
	IMPORT_C TInt CalcHeightBasedOnNumOfItems(TInt aNumOfItems) const;
	IMPORT_C TInt CalcWidthBasedOnRequiredItemWidth(TInt aTextWidthInPixels) const;

	// drawing/scrolling functions
	IMPORT_C void DrawItem(TInt aItemIndex) const;
	IMPORT_C void ScrollToMakeItemVisible(TInt aItemIndex) const;
	IMPORT_C void ScrollToMakeItemVisibleL(TInt aItemIndex) const;

	// observer support
	IMPORT_C void SetListBoxObserver(MEikListBoxObserver* aObserver);

	IMPORT_C TInt VerticalInterItemGap() const;

	// popouts only
	IMPORT_C void SetLaunchingButton(CEikButtonBase* aButton);

    // Editing support
    IMPORT_C void SetItemEditor(MEikListBoxEditor* aEditor);
    IMPORT_C void ResetItemEditor();
    IMPORT_C MEikListBoxEditor* ItemEditor();
    IMPORT_C virtual void EditItemL(TInt aMaxLength);
    IMPORT_C void StopEditingL(TBool aUpdateModel);

	// miscellaneous
	inline TInt Flags() const {return iListBoxFlags;}

public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C TCoeInputCapabilities InputCapabilities() const; // not available before Release 006
	IMPORT_C void ReportExternalEventL(MCoeControlObserver::TCoeEvent aEvent);
     
	class TDestroyInfo
		{
		public:
		TDestroyInfo(const TBool& aDestroyed, TBool** aLbxDestroyed) : iDestroyed(aDestroyed), iLbxDestroyed(aLbxDestroyed) { }
		const TBool& iDestroyed;
		TBool** iLbxDestroyed;
		};

public: // for test code only - DO NOT USE!
	IMPORT_C void SetShowPartiallyVisibleItemsL(TBool aShowPartiallyVisibleItems);
	IMPORT_C TBool ShowPartiallyVisibleItems() const;
	IMPORT_C void SetSmoothVerticalScrollingL(TBool aSmoothVerticalScrolling);
	IMPORT_C TBool SmoothVerticalScrolling() const;
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
protected:

	IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C virtual void SizeChanged();
	IMPORT_C virtual void HandleViewRectSizeChangeL();
	IMPORT_C virtual TInt CountComponentControls() const;
	IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;

	// functions that implement first letter and incremental matching
	IMPORT_C void CreateMatchBufferL();  // utility function called from RestoreL() of subclasses such as CEikStandardListBox
	IMPORT_C void ClearMatchBuffer() const;
	IMPORT_C void MatchTypedCharL(TUint aCode);
	IMPORT_C void UndoLastChar();

	// functions needed for supporting scrollbars
	IMPORT_C void UpdateScrollBarThumbs() const;
	IMPORT_C virtual TInt HorizScrollGranularityInPixels() const;
	IMPORT_C virtual TInt HorizontalNudgeValue() const;
	IMPORT_C virtual void AdjustTopItemIndex() const;

	// navigation support functions
	IMPORT_C void SimulateArrowKeyEventL(TKeyCode aKeyCode);
	IMPORT_C virtual void HandleLeftArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);
	IMPORT_C virtual void HandleRightArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);

	// construction support functions
	IMPORT_C void RestoreCommonListBoxPropertiesL(TResourceReader& aReader); // utility function called from RestoreL() of subclasses such as CEikStandardListBox
	IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aFlags = 0);
	IMPORT_C virtual void CreateViewL();
	IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
	IMPORT_C void SetViewRectFromClientRect();
	IMPORT_C void SetViewRectFromClientRect(const TRect& aClientRect);
	IMPORT_C virtual void RestoreClientRectFromViewRect(TRect& aClientRect) const;
	IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const;

	// accessor for Laf members
	IMPORT_C TMargins8 ListBoxMargins() const;

	// various accessors for private data members
	IMPORT_C TInt HorizontalMargin() const;
	IMPORT_C TInt VerticalMargin() const;
	IMPORT_C void SetHorizontalMargin(TInt aMargin);
	IMPORT_C void SetVerticalMargin(TInt aMargin);
	IMPORT_C RIncrMatcherBase* MatchBuffer() const;
	IMPORT_C TInt ViewRectHeightAdjustment() const;
	IMPORT_C TRgb BackColor() const;

	// misc functions
	IMPORT_C virtual void ReportListBoxEventL(MEikListBoxObserver::TListBoxEvent aEvent);
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	IMPORT_C void ClearMargins() const;
	IMPORT_C virtual void UpdateCurrentItem(TInt aItemIndex) const;
	IMPORT_C virtual void HandleDragEventL(TPoint aPointerPos);
	IMPORT_C TBool ItemExists(TInt aItemIndex) const;
	IMPORT_C void DrawMatcherCursor() const;

	IMPORT_C static TInt InterItemGap();

	IMPORT_C void UpdateViewColors();
	IMPORT_C void UpdateItemDrawerColors();

protected:	// functions which deal with extension

	IMPORT_C void SetReasonForFocusLostL(TReasonForFocusLost aReasonForFocusLost);
	IMPORT_C TReasonForFocusLost ReasonForFocusLostL();
	TBool IsMatchBuffer() const;
	void CheckCreateExtensionL();
	TBool CheckCreateExtension();
	void CheckCreateBufferL();
	CMatchBuffer* Buffer() const;
	TKeyResponse PreProcessKeyEventL(TKeyEvent& aKeyEvent,TEventCode aType);
	TKeyResponse DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	IMPORT_C virtual void Reserved_3(); // listbox use only
	void HorizontalScroll(TInt aScrollAmountInPixels);
	void CreateScrollBarFrameLayout(TEikScrollBarFrameLayout& aLayout) const;
	void TryStartNewSelection(TInt aKeyCode);
	void DrawItemInView(TInt aItemIndex) const;
	void ClearMargins(CWindowGc& aGc) const;
	void UpdateScrollBarColors(CEikScrollBar* aScrollBar);
	void UpdateScrollBarsColors();
	void VerticalScrollToNewTopItemIndexL(TInt aNewTopItemIndex) const;
	void VerticalScrollToNewBottomItemIndexL(TInt aNewBottomItemIndex) const;
	void VerticalScrollToNewTopOrBottomItemIndexL(TInt aNewTopItemIndex, TInt aNewBottomItemIndex, TInt aOverridingScrollBarThumbPosition) const;
	void VerticalScrollToNewScrollBarThumbPositionL(TInt aNewScrollBarThumbPosition) const;
	void VerticalScrollL(TInt aNewNumberOfPixelsAboveTopItem, TInt aNewTopItemIndex, const TEikScrollBarModel& aScrollBarModel) const;
	void PrepareToCallMoveCursorLC();
	static void DropListBoxAndNumberOfVerticalPixels(TAny* aThis);
	void AdjustRectForScrollBar(TRect& aRect, CEikScrollBar::TOrientation aScrollBarOrientation, TInt TPoint::* aDimensionToAdjust) const;
	TRect ClientRect(TBool aAdjustForScrollBars=ETrue) const;
	TBool PreReportListBoxEventL(MEikListBoxObserver::TListBoxEvent aEvent);
	inline TInt TopItemIndexCalculatedFromScrollBarThumbPosition(TInt aScrollBarThumbPosition) const {TInt notUsed1; TInt notUsed2; return iView->TopItemIndexCalculatedFromScrollBarThumbPosition(notUsed1, notUsed2, aScrollBarThumbPosition);}
protected:
	TInt iListBoxFlags;
	CListBoxView* iView;
	CListItemDrawer* iItemDrawer;
	MListBoxModel* iModel;
	TInt iItemHeight; 	
	CEikScrollBarFrame* iSBFrame;
	TInt iRequiredHeightInNumOfItems;
	CEikButtonBase* iLaunchingButton; // only used by popouts
	MEikListBoxObserver* iListBoxObserver;
private:
	TRgb iBackColor;
	TMargins8 iMargins;
	CListBoxExt* iListBoxExt;
	TInt iViewRectHeightAdjustment;
	MEikListBoxEditor* iItemEditor;
	TBool* iLbxDestroyed;
	};

/**
 * This class is only for use within EIKCOCTL.DLL.
 * @since App-Framework_6.2
 * @private
 */
class CListBoxExt : public CBase, public MListVisibilityObserver, public MEikListBoxViewObserver
	{
public:
	static CListBoxExt* New(CEikListBox& aListBox); // does not leave, returns NULL if failed
	
	~CListBoxExt();
	CListBoxExt(CEikListBox& aListBox);

	// new functions
	void CreateMatchBufferL();
	void CheckCreateBufferL();
	CMatchBuffer* Buffer() const;
	TBool IsMatchBuffer() const;
	void SetReasonForFocusLost(CEikListBox::TReasonForFocusLost aReasonForFocusLost);
	CEikListBox::TReasonForFocusLost ReasonForFocusLost() const;
	inline void SetEditorComponentControl(CCoeControl* aEditorComponentControl) {iEditorComponentControl=aEditorComponentControl;}
	inline CCoeControl* EditorComponentControl() const {return iEditorComponentControl;}
public:
	// from MListVisibilityObserver
	TBool IsVisible() const;
	void SetUpdateScrollBarsColors(TBool aUpdate);
	TBool UpdateScrollBarsColors() const;
	// from MEikListBoxViewObserver
	void HandleListBoxViewEventL(CListBoxView* aListBoxView, TListBoxViewEvent aEventType);
private:
	enum { EUpdateScrollBarsColors =0x1 };
private:
	CMatchBuffer* iBuffer;
	CEikListBox& iListBox;
	CEikListBox::TReasonForFocusLost iReasonForFocusLost;
	TInt iFlags;
	CCoeControl* iEditorComponentControl;
	};

/**
 *
 * Snaking list box.
 *
 * This is a list box that scrolls horizontally, displaying its items in
 * as many vertical columns as needed. Columns are arranged across the
 * control from left to right; within columns, items are arranged from
 * top to bottom. The flow of items or text snakes across the face of the
 * control.This is a flexible control class that makes good use of short,
 * wide display areas; subclasses of <code>CEikSnakingListBox</code> are
 * used in the EPOC shell for the file list and for the control panel. A
 * standard user subclass, <code>CEikSnakingTextListBox</code>, also
 * exists.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikSnakingListBox : public CEikListBox  
	{
public:
	IMPORT_C CEikSnakingListBox();
	IMPORT_C ~CEikSnakingListBox();
	IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex) const;
   	IMPORT_C TInt ColumnWidth() const;
	IMPORT_C void SetColumnWidth(TInt aColumnWidth);
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);	// not available before Release 6.2
protected:
	IMPORT_C virtual void HandleViewRectSizeChangeL();
	IMPORT_C virtual void HandleLeftArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);
	IMPORT_C virtual void HandleRightArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);
	IMPORT_C virtual TInt HorizontalNudgeValue() const;
	IMPORT_C virtual TInt HorizScrollGranularityInPixels() const;
	IMPORT_C virtual void AdjustTopItemIndex() const;
	IMPORT_C virtual void HandleDragEventL(TPoint aPointerPos);
	IMPORT_C virtual void RestoreClientRectFromViewRect(TRect& aClientRect) const;
	IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const;
	IMPORT_C void MoveToNextOrPreviousItemL(TPoint aPoint);
protected: //from CCoeControl
	IMPORT_C virtual void SizeChanged();
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
protected:
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikListBox
	IMPORT_C void Reserved_3(); // listbox use only
	};

#endif
