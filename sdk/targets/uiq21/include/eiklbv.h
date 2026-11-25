// EIKLBV.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//


#if !defined(__EIKLBV_H__)
#define __EIKLBV_H__

#include <e32base.h>
#include <gdi.h>

class CEikListBox;
class CListBoxViewExtra;
class CListItemDrawer;
class MListBoxModel;
class CWindowGc;
class RWindowGroup;
class CWsScreenDevice;
class CWindowGc;
class RWindow;
class TEikScrollBarModel;
class MEikListBoxViewObserver;

/**
 *
 * Tests the visibility of a list box view.
 *
 * A list box view displays the list items which are currently visible in
 * a list box.
 *
 * @since 6.0
 * @lib ""
 */
class MListVisibilityObserver 
	{
public:
	/**
	 * Tests list box view visibility.
	 *
	 * @returns   " TBool"
	 *            <code>ETrue</code> if the list box view is visible.
	 *            <code>EFalse</code> if the list box view is not
	 *            visible.
	 */
	virtual TBool IsVisible() const = 0;
	};

/**
 *
 * List box view.
 *
 * A list box view displays the list items which are currently visible in
 * a list box. List box views draw each of the items for display using
 * methods defined in their associated list box drawer. Together with its
 * list item drawer, a <code>CListBoxView</code> encapsulates the
 * on-screen appearance of data in a list box.List box views also
 * encapsulate item selection, the current item, and the fundamentals of
 * how the selection and the current item are updated according to user
 * input. Input events themselves are handled by
 * <code>CEikListBox</code>, which calls member functions of
 * <code>CListBoxView</code> appropriately.This class is sufficient for
 * plain list box views, and may be derived from in order to provide more
 * complex list views. Uikon supplies and uses the classes
 * <code>CHierarchicalListBoxView</code> and
 * <code>CSnakingListBoxView</code>, which provide two kinds of indented
 * list views.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CListBoxView : public CBase
	{
public:
	/**
	 * Cursor movement flags.
	 *
	 * These describe the cursor movements recognised by
	 * <code>MoveCursorL()</code>.
	 */
	enum TCursorMovement 
		{
		ECursorNextItem,  			/** Next item. */
		ECursorPreviousItem,		/** Previous item. */
		ECursorNextColumn,			/** Next column. */
		ECursorPreviousColumn,		/** Previous. column. */
		ECursorPreviousPage,		/** Previous page. */
		ECursorNextPage,			/** Next page. */
		ECursorFirstItem,			/** To the first item. */
		ECursorLastItem				/** To the last item. */
		};  

	/**
	 * List box view flags. These flags may be combined with a logical OR to
	 * get a combination of effects.
	 */
	enum TFlags
		{
		EAnchorExists				= 0x0001,		/** A selection anchor exists. */
		EEmphasized					= 0x0002,		/** The view is emphasised. */
		EDimmed						= 0x0004,		/** The view is dimmed. */
		EHasMatcherCursor			= 0x0008,		/** List box view has a cursor for incremental matching. */
		EDisableRedraw				= 0x0010,		/** Redraw is disabled. */
		EPaintedSelection			= 0x0020,
		EDataWidthClippedToViewRect = 0x0040
		};

	/**
	 * Modes for modifying the selection.
	 *
	 * Changing the current item of a list box view may also affect which
	 * items are selected. The selection mode of such an action describes how
	 * (or if) the selection is altered by the action.Each function of
	 * <code>CListBoxView</code> which affects the current item is passed an
	 * appropriate selection mode by the calling input handler method of
	 * <code>CEikListBox</code>. The mode is varied according to the keyboard
	 * modifiers held down by the user, or whether a pointer action was a tap
	 * or a sweep.Note that the behaviour of list box views may vary with the
	 * target platform due to the wide range of possible input devices. The
	 * following description assumes a device with a pointer and a keyboard.
	 */
	enum TSelectionMode
		{
		/** The selection is not changed by actions while this is in effect,
		holding CTRL while pressing cursor up or down for example. */
		ENoSelection,

		/** Only a single item in the list is allowed to be selected by an action;
		when selecting individual items with the pointer, or moving using the
		cursor keys without any modifiers for example. */
		ESingleSelection,

		/** A single continuous run of items can be added to the selection array
		by an action, when keyboard-selecting with the shift key held down, or
		when sweeping a selection with the pointer for example.	 */
		EContiguousSelection,

		/** Any single item in the list may be added to the selection by an
		action, when selecting or drag-selecting with the pointer when the
		CTRL key is held down for example. */
		EDisjointSelection,
		EDeSelect
		};

	/**
	 * The items which are selected within a list box list.
	 */
	typedef CArrayFix<TInt> CSelectionIndexArray;
protected:
	enum TInitialFlags
		{
		EAllowVariableHeightItems	=0x00000001,
		EAllowPartiallyVisibleItems	=0x00000002
		// only two flags are currently accommodated as these enum values must only use the bottom 2 bits which are the "spare" bits of a pointer - to extend this in the future, switch to a scheme similar to RCoeExtensionStorage in CONE which uses a union
		};
	IMPORT_C CListBoxView(TUint aInitialFlags); // one or more of TInitialFlags
	IMPORT_C void AllowVariableHeightItems();
	IMPORT_C void AllowPartiallyVisibleItems();
public:
	IMPORT_C ~CListBoxView();
	IMPORT_C CListBoxView();

	// constructors
	IMPORT_C virtual void ConstructL(MListBoxModel* aListBoxModel, CListItemDrawer* aItemDrawer, CWsScreenDevice* aScreen, RWindowGroup* aGroupWin, RWindow* aWsWindow, const TRect& aDisplayArea, TInt aItemHeight);

	// functions for accessing the view rect (the area of the host window in which the items are drawn)
	IMPORT_C TRect ViewRect() const;
	IMPORT_C void SetViewRect(const TRect& aRect);  // the area within the list window in which the view can draw itself
	IMPORT_C TInt NumberOfPixelsAboveTopItem() const;
	IMPORT_C TInt PixelOffsetBetweenItemTops(TInt aItemIndex1, TInt aItemIndex2) const;

	// misc. access functions for the main attributes 
	IMPORT_C TInt CurrentItemIndex() const;	
	IMPORT_C void SetCurrentItemIndex(TInt aItemIndex); 
	IMPORT_C TInt TopItemIndex() const;		
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex);
	IMPORT_C TInt BottomItemIndex() const;
	IMPORT_C virtual void CalcBottomItemIndex();
	IMPORT_C virtual void SetItemHeight(TInt aItemHeight);

	// functions that support incremental matching 
	IMPORT_C void SetMatcherCursorColor(TRgb aColor);
	IMPORT_C void SetMatcherCursorPos(TInt aPosWithinCurrentItem);
	IMPORT_C TInt MatcherCursorPos() const;
	IMPORT_C void DrawMatcherCursor();
	IMPORT_C void HideMatcherCursor();

	// functions for getting/setting flags
	IMPORT_C void SetMatcherCursor(TBool aMatcherCursor);
	IMPORT_C void SetEmphasized(TBool aEmphasized);
	IMPORT_C void SetDimmed(TBool aDimmed);
	IMPORT_C void SetDisableRedraw(TBool aDisableRedraw);
	IMPORT_C TBool RedrawDisabled() const;
	IMPORT_C void SetPaintedSelection( TBool aPaintedSelection );

	// functions that support selection
	IMPORT_C const CSelectionIndexArray* SelectionIndexes() const;
	IMPORT_C void GetSelectionIndexesL(CSelectionIndexArray* aSelectionArray) const;
	IMPORT_C void SetSelectionIndexesL(const CSelectionIndexArray* aSelectionIndexes);
	IMPORT_C void ClearSelection();	 // resets the selection state so that there is nothing selected  		
	IMPORT_C virtual void UpdateSelectionL(TSelectionMode aSelectionMode);  // select/highlight items without moving the cursor
	IMPORT_C void ToggleItemL(TInt aItemIndex);
	IMPORT_C void SelectItemL(TInt aItemIndex);
	IMPORT_C void SelectItemL(TInt aItemIndex, TBool aReportSelectionChanged);
	IMPORT_C void DeselectItem(TInt aItemIndex);
	IMPORT_C void DeselectItem(TInt aItemIndex, TBool aReportSelectionChanged);
	IMPORT_C void SetAnchor(TInt aItemIndex);
	IMPORT_C void ClearSelectionAnchorAndActiveIndex();

	// functions that support scrolling
	IMPORT_C virtual TBool ScrollToMakeItemVisible(TInt aItemIndex);
	IMPORT_C virtual void VScrollTo(TInt aNewTopItemIndex);
	IMPORT_C virtual void VScrollTo(TInt aNewTopItemIndex, TRect& aMinRedrawRect);
	IMPORT_C virtual void HScroll(TInt aHScrollAmount);
	IMPORT_C TInt HScrollOffset() const;
	IMPORT_C void SetHScrollOffset(TInt aHorizontalOffset);
	IMPORT_C TInt DataWidth() const;
	IMPORT_C virtual void CalcDataWidth();
	IMPORT_C virtual TInt VisibleWidth(const TRect& aRect) const;
	IMPORT_C virtual TInt CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const;

	// functions that support drawing
	IMPORT_C virtual void Draw(const TRect* aClipRect = NULL) const;
	IMPORT_C virtual void DrawItem(TInt aItemIndex) const;

	// functions for accessing an item's position/size, selection status, and visibility status
	IMPORT_C TBool ItemIsSelected(TInt aItemIndex) const; 
	IMPORT_C TBool ItemIsVisible(TInt aItemIndex) const; // returns "true" if the item is fully or partially visible
	IMPORT_C TBool ItemIsFullyVisible(TInt aItemIndex) const;
	IMPORT_C TBool ItemIsPartiallyVisible(TInt aItemIndex) const;
	IMPORT_C virtual TPoint ItemPos(TInt aItemIndex) const;
	IMPORT_C virtual TSize ItemSize(TInt aItemIndex=0) const;

	IMPORT_C void SetTextColor(TRgb aColor);
	IMPORT_C void SetBackColor(TRgb aColor);
	IMPORT_C TRgb TextColor() const;
	IMPORT_C TRgb BackColor() const;

	IMPORT_C virtual void MoveCursorL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode);
	IMPORT_C virtual void VerticalMoveToItemL(TInt aTargetItemIndex, TSelectionMode aSelectionMode);
	IMPORT_C virtual TBool XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const;   // returns false if no item 															//Keyword to test this
	IMPORT_C virtual TInt NumberOfItemsThatFitInRect(const TRect& aRect) const;

	void SetVisibilityObserver(MListVisibilityObserver* aObserver);
	IMPORT_C TBool IsVisible() const;
	
	inline CListItemDrawer* ItemDrawer() const;

	IMPORT_C TBool SupportsVariableHeightItems() const;
	IMPORT_C TBool SupportsPartiallyVisibleItems() const;

	// functions for limiting the width of items (using item truncation)
	IMPORT_C void SetDataWidthClippedToViewRect(TBool aIsClipped);
	IMPORT_C TBool DataWidthClippedToViewRect() const;
public: // but not exported
	void DrawItem(CWindowGc& aGc, TInt aItemIndex);
	void Draw(CWindowGc& aGc, const TRect* aClipRect=NULL);
	TInt NumberOfItemsThatFitGivenTopItemIndex(TInt& aNumberOfSpareVerticalPixels, TBool& aFillsVerticalPixelSpan, TInt aNumberOfVerticalPixels, TInt aTopItemIndex) const;
	TInt NumberOfItemsThatFitGivenBottomItemIndex(TInt& aNumberOfSpareVerticalPixels, TBool& aFillsVerticalPixelSpan, TInt aNumberOfVerticalPixels, TInt aBottomItemIndex) const;
	TInt CalculatedScrollBarThumbPosition(TInt aNumberOfPixelsAboveTopItem, TInt aTopItemIndex) const;
	TInt TopItemIndexCalculatedFromScrollBarThumbPosition(TInt& aNumberOfPixelsAboveTopItem, TInt& aScrollBarScrollSpan, TInt& aScrollBarThumbPosition) const;
	void SetItemHeightL(TInt aItemIndex, TInt aItemHeight);
	void SetToDefaultItemHeight(TInt aItemIndex);
	TInt ItemHeight(TInt aItemIndex) const;
	void CreateExtensionL();
	// CreateExtensionL must have been called before any of these functions can be called
	void HoldNewNumberOfPixelsAboveTopItem(TInt aNewNumberOfPixelsAboveTopItem);
	void HoldNewTopItemIndex(TInt aNewTopItemIndex);
	void HoldNewViewRect(const TRect& aNewViewRect);
	void HoldNumberOfVerticalPixels(TInt aNumberOfVerticalPixels);
	void HoldListBox(CEikListBox* aListBox);
	TBool HoldingNewNumberOfPixelsAboveTopItem() const;
	TBool HoldingNewTopItemIndex() const;
	TBool HoldingNewViewRect() const;
	TBool HoldingNumberOfVerticalPixels() const;
	TBool HoldingListBox() const;
	TInt NewNumberOfPixelsAboveTopItem() const;
	TInt NewTopItemIndex() const;
	TRect NewViewRect() const;
	TInt NumberOfVerticalPixels() const;
	CEikListBox* ListBox() const;
	void DropNewNumberOfPixelsAboveTopItem();
	void DropNewTopItemIndex();
	void DropNewViewRect();
	void DropNumberOfVerticalPixels();
	void DropListBox();
	// observer support
	void SetListBoxViewObserver(MEikListBoxViewObserver* aObserver);
	// scrolling support
	void VScrollTo(CWindowGc& aGc, TInt aNewTopItemIndex);
private:
	enum TSelectionModificationOperation
		{
		EAppendItem,  	
		EDeleteItem
		};  
private:
	void CommonConstructorCode(TUint aInitialFlags); // one or more of TInitialFlags
	CListBoxViewExtra* Extra() const;
	void ModifySelectionArrayL(CSelectionIndexArray& aSelectionIndexes,TSelectionModificationOperation aOperation,TInt aModificationArgument, TBool aReportSelectionChanged);
	IMPORT_C virtual TAny* Reserved_1();
protected:
	// functions for accessing the flags
	inline TInt Flags() const;
	inline void SetFlags(TInt aMask);
	inline void ClearFlags(TInt aMask);

	// misc. functions
	IMPORT_C void SelectRangeL(TInt aItemIndex1, TInt aItemIndex2);
protected:
	TInt iFlags;   	
	CListItemDrawer* iItemDrawer;
	MListBoxModel* iModel;
	TInt iDataWidth;			// width (in pixels) of the longest item in the model
	TInt iTopItemIndex;
	TInt iBottomItemIndex;
	TInt iHScrollOffset;		// pixel offset (from the left margin) of the visible portion of the data 
	TInt iCurrentItemIndex;
	TInt iItemHeight;
	RWindow* iWin;
	RWindowGroup* iGroupWin;
	CWindowGc* iGc;
	TRect iViewRect;
private:
	TInt iMatcherCursorPos;
	TRgb iMatcherCursorColor; 
	TRgb iBackColor;
	TRgb iTextColor;
	TInt iAnchorIndex;  
	TInt iActiveEndIndex;
	CListBoxViewExtra* iExtra;
	MListVisibilityObserver* iVisibilityObserver;
private:
	friend class CListBoxViewExtra;
	};

/**
 *
 * List box view for snaking list boxes.
 *
 * The view is responsible for drawing items and maintaining the
 * selection status.
 *
 * @since 6.0
 * @lib " eikcoctl.lib "
 */
class CSnakingListBoxView : public CListBoxView
	{
public:
	IMPORT_C ~CSnakingListBoxView();
	IMPORT_C CSnakingListBoxView();
	inline TInt ColumnWidth() const;
	IMPORT_C void SetColumnWidth(TInt aColumnWidth);
	IMPORT_C virtual void MoveCursorL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode);
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex);
	IMPORT_C virtual void SetItemHeight(TInt aItemHeight);
	IMPORT_C virtual TBool XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const;
	IMPORT_C virtual TInt NumberOfItemsThatFitInRect(const TRect& aRect) const;
	IMPORT_C virtual void HScroll(TInt aHScrollAmount);
	IMPORT_C virtual void CalcDataWidth();
	IMPORT_C virtual void CalcBottomItemIndex();
	IMPORT_C virtual void Draw(const TRect* aClipRect = NULL) const;
	IMPORT_C virtual TInt VisibleWidth(const TRect& aRect) const;
	IMPORT_C virtual TBool ScrollToMakeItemVisible(TInt aItemIndex);
	IMPORT_C virtual TInt CalculateHScrollOffsetSoItemIsVisible(TInt aItemIndex);
	IMPORT_C virtual TInt CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const;
	IMPORT_C virtual TPoint ItemPos(TInt aItemIndex) const;
	IMPORT_C virtual TSize ItemSize(TInt aItemIndex=0) const;
	IMPORT_C void CalcRowAndColIndexesFromItemIndex(TInt aItemIndex, TInt& aRowIndex, TInt& aColIndex) const;
	IMPORT_C void CalcItemIndexFromRowAndColIndexes(TInt& aItemIndex, TInt aRowIndex, TInt aColIndex) const;
	IMPORT_C TInt NumberOfItemsPerColumn() const;
protected:
	IMPORT_C void DrawItemRange(TInt aStartItemIndex, TInt aEndItemIndex) const;
	IMPORT_C void DrawColumnRange(TInt aStartColIndex, TInt aEndColIndex) const;
	IMPORT_C void MoveToPreviousColumnL(TSelectionMode aSelectionMode);
	IMPORT_C void MoveToNextColumnL(TSelectionMode aSelectionMode);
	IMPORT_C void ClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex) const;
	IMPORT_C void UpdateHScrollOffsetBasedOnTopItemIndex();
private:
	IMPORT_C virtual TAny* Reserved_1();
protected:
	TInt iColumnWidth;
	};

/**
 * Gets this views flags.
 *
 * @returns   "TInt"
 *            An OR-ed combination of <code>TFlags</code>.
 */
inline TInt CListBoxView::Flags() const
	{ return iFlags; }

/**
 * Sets this views flags according to a bitmask.
 *
 * @param     "TInt aMask"
 *            An OR-ed combination of <code>TFlags</code>.
 */
inline void CListBoxView::SetFlags(TInt aMask)
	{ iFlags|=aMask; }

/**
 * Clears this views flags according to a bitmask.
 *
 * @param     "TInt aMask"
 *            An OR-ed combination of <code>TFlags</code>.
 */
inline void CListBoxView::ClearFlags(TInt aMask)
	{ iFlags&=(~aMask); }

/**
 * Gets the object used by this list box view to draw its items.
 *
 * @returns   "CListItemDrawer*"
 *            Pointer to the list box viewer.
 */
inline CListItemDrawer* CListBoxView::ItemDrawer() const
	{ return iItemDrawer; }

/**
 * Gets the width of all columns in the view.
 *
 * @returns   " TInt "
 *            The width of all columns in the view, in pixels.
 */
inline TInt CSnakingListBoxView::ColumnWidth() const
	{ return iColumnWidth; }


#endif
