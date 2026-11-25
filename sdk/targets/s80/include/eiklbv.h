/*
* ==============================================================================
*  Name        : eiklbv.h
*  Part of     : CKON
*  Interface   : Listbox API
*  Description : Listbox view.
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

#ifndef EIKLBV_H
#define EIKLBV_H


// INCLUDES
#include <e32base.h>
#include <gdi.h>

// FORWARD DECLARATIONS
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


// CLASS DECLARATIONS

/**
 * The <code>MListVisibilityObserver</code> class tests the visibility of a
 * Listbox view. A Listbox view displays the list items that are currently
 * visible in a Listbox.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class MListVisibilityObserver
    {
    public:
    // New methods

       /**
        * Determines the visibility of the Listbox.
        *
        * @return <code>ETrue</code> if the Listbox view is visible;
        *         <code>EFalse</code> if the Listbox view is not visible
        * @remarks
        * @see
        */
        virtual TBool IsVisible() const = 0;
    };

/**
 * The <code>CListBoxView</code> class provides the Listbox view.
 * A Listbox view displays the list items that are currently visible in
 * a Listbox. Listbox views draw each of the items for display using
 * methods defined in their associated Listbox drawer. Together with its
 * list item drawer, a <code>CListBoxView</code> encapsulates the
 * onscreen appearance of data in a Listbox. Listbox views also
 * encapsulate item selection, the current item, and the fundamentals of
 * how the selection and the current item are updated according to user
 * input. Input events themselves are handled by
 * <code>CEikListBox</code>, which calls member methods of
 * <code>CListBoxView</code> appropriately. This class is sufficient for
 * plain Listbox views and may be derived from, to provide more
 * complex list views. Uikon supplies and uses the classes
 * <code>CHierarchicalListBoxView</code> and
 * <code>CSnakingListBoxView</code>, which provide two kinds of
 * list views.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CListBoxView : public CBase
    {
    public:  // Declarations
    /**
     * The <code>TCursorMovement</code> enumeration provides the cursor
     * movement flags that describe the cursor movements recognized by
     * <code>MoveCursorL()</code>.
     */
    enum TCursorMovement
        {
        /** next item */
        ECursorNextItem,
        /** previous item */
        ECursorPreviousItem,
        /** next column */
        ECursorNextColumn,
        /** previous column */
        ECursorPreviousColumn,
        /** previous page */
        ECursorPreviousPage,
        /** next page */
        ECursorNextPage,
        /** to the first item */
        ECursorFirstItem,
        /** to the last item */
        ECursorLastItem
        };
    /**
     * The <code>TFlags</code> enumeration provides Listbox view flags. These
     * flags may be combined with a logical OR to get a combination of effects.
     */
    enum TFlags
        {
        /** a selection anchor exists */
        EAnchorExists               = 0x0001,
        /** the view is emphasized */
        EEmphasized                 = 0x0002,
        /** the view is dimmed */
        EDimmed                     = 0x0004,
        /** the Listbox view has a cursor for incremental matching */
        EHasMatcherCursor           = 0x0008,
        /** redraw is disabled */
        EDisableRedraw              = 0x0010,
        /** if set, draws a highlight over a selected list item. This is used in the <code>CTextListItemDrawer::DoDrawItemText()</code> method */
        EPaintedSelection           = 0x0020,
        /** if set, the text may be truncated to fit within the bounds of the view rectangle */
        EDataWidthClippedToViewRect = 0x0040
        };

    /**
     * The <code>TSelectionMode</code> enumeration provides modes for modifying
     * a selection. Changing the current item of a Listbox view may also affect
     * which items are selected. The selection mode of such an action describes
     * how (or if) the selection is altered by the action. Each of the methods
     * of <code>CListBoxView</code> that affect the current item is passed an
     * appropriate selection mode by the calling the input handler method of
     * <code>CEikListBox</code>. The mode is varied according to the keyboard
     * modifiers held down by the user or whether a pointer action was a tap
     * or a sweep. The behavior of Listbox views may vary with the
     * target platform due to the wide range of possible input devices. The
     * following descriptions assume a device with a pointer and a keyboard.
     */
    enum TSelectionMode
        {
        /** the selection is not changed by actions while this is in effect, for example, holding CTRL while moving the cursor up or down  */
        ENoSelection,
        /** only a single item in the list can be selected by an action. For example, when selecting individual items with the pointer or moving using the cursor keys without any modifiers */
        ESingleSelection,
        /** a single continuous run of items can be added to the selection array by an action, for example, when keyboard-selecting with the shift key held down, or when sweeping a selection with the pointer  */
        EContiguousSelection,
        /** any single item in the list may be added to the selection by an action, for example, when selecting or drag-selecting with the pointer when the CTRL key is held down */
        EDisjointSelection,
        /** a single item has become deselected by an action, for example, keyboard selecting with the pointer held down */
        EDeSelect,
        /** a group of items has become deselected by an action, for example, when drag-unselecting with the pointer when the CTRL key is held down */
        EContiguousDeselection,
        };

    typedef CArrayFix<TInt> CSelectionIndexArray;

    protected:  // Declarations
    enum TInitialFlags
        {
        /** If set, allow variable height items */
        EAllowVariableHeightItems   =0x00000001,
        /** If set, allow partially visible items at top and bottom of Listbox */
        EAllowPartiallyVisibleItems =0x00000002
        // only two flags are currently accommodated as these enum values must only use the bottom 2 bits which are the "spare" bits of a pointer - to extend this in the future, switch to a scheme similar to RCoeExtensionStorage in CONE which uses a union
        };

    private:  // Declarations
    enum TSelectionModificationOperation
        {
        /** An item has been appended to the selection array */
        EAppendItem,
        /** An item has been deleted from the selection array */
        EDeleteItem
        };
    friend class CListBoxViewExtra;

    protected:  // Methods

    // New Methods

/**
 * Protected constructor allowing derived classes to pass TInitialFlags.
 * @since App-Framework_6.2
 * @public
 */
        IMPORT_C CListBoxView(TUint aInitialFlags); // one or more of TInitialFlags

/**
 * Protected function for explicitly allowing variable-height items in "this"
 * list-box.
 * @since App-Framework_6.2
 * @public
 */
        IMPORT_C void AllowVariableHeightItems();

/**
 * Protected function for explicitly allowing showing partially visible items
 * in "this" list-box.
 * @since App-Framework_6.2
 * @public
 */
        IMPORT_C void AllowPartiallyVisibleItems();

    public:
    // Constructors and destructor

        /**
         * The object destructor.
         * The destructor destroys this Listbox view, its item drawer, its
         * graphics context, and its selection list.
        */
        IMPORT_C ~CListBoxView();

        /**
         * The default object constructor.
         * This method allocates an area of memory for a <code>CListBoxView</code>,
         * and begins its initialization.
        */
        IMPORT_C CListBoxView();


    // New methods

        /**
         * Completes construction of the Listbox view object.
         * This method completes the initialization of a default-constructed
         * Listbox view. The item drawer's graphics context is created on
         * <code>aScreen</code> and the list item drawer's graphics context is
         * set to this.
         *
         * @param aListBoxModel The Listbox model to use
         * @param aItemDrawer A default-constructed item drawer
         * @param aScreen The screen on which to display. Gives access to the
         *                list of screen modes
         * @param aGroupWin This Listbox view's window group
         * @param aWsWindow The window for this view
         * @param aDisplayArea The viewing rectangle that this Listbox view is
         *                     to use
         * @param aItemHeight The height of a single list item
         * @remarks
         * @see CListItemDrawer::SetGc()
         * @see CWsScreenDevice in w32std.h
         * @see RWindowGroup in w32std.h
         * @see RWindow in w32std.h
         * @see MListBoxModel in eiklbm.h
         * @see CListItemDrawer in eiklbi.h
         */
        IMPORT_C virtual void ConstructL(MListBoxModel* aListBoxModel, CListItemDrawer* aItemDrawer, CWsScreenDevice* aScreen, RWindowGroup* aGroupWin, RWindow* aWsWindow, const TRect& aDisplayArea, TInt aItemHeight);

        /**
         * Gets the Listbox's view rectangle.
         * Initially, this is the display area that is passed in via the 
         * <code>ConstructL()</code> method.
         *
         * @return this Listbox view's viewing rectangle
         * @remarks
         * @see
         */
        IMPORT_C TRect ViewRect() const;

        /**
         * Sets the area within the list window in which the view can draw
         * itself. Overwrites the view rectangle passed into <code>ConstructL</code>.
         *
         * @param aRect The new viewing rectangle
         * @remarks
         * @see CListBoxView::Draw()
         */
        IMPORT_C void SetViewRect(const TRect& aRect);

        /**
         * Returns the number of pixels between the top of the
         * <code>ViewRect</code> and the top of the top item.
         *
         * @since App-Framework_6.2
         * @internal
         */
        IMPORT_C TInt NumberOfPixelsAboveTopItem() const;

        /**
         * Returns the number of pixels difference between the tops of any two 
         * items in a list.
         *
         * @param aItemIndex1 The index of the first item to be compared
         * @param aItemIndex2 The index of the second item to be compared
         * @return the difference between <code>aItemIndex1</code>
         *         and <code>aItemIndex2</code>, in pixels. If the first item
         *         is lower, the result returned is negative
         * @remarks Neither <code>aItemIndex1</code> nor <code>aItemIndex2</code>
         *          need to be currently visible
         * @see
         */
        IMPORT_C TInt PixelOffsetBetweenItemTops(TInt aItemIndex1, TInt aItemIndex2) const;

        /**
         * Gets the currently selected item's index.
         *
         * @return the index number of the currently selected item
         * @remarks
         * @see
         */
        IMPORT_C TInt CurrentItemIndex() const;

        /**
         * Sets the item at the specified index to be the currently selected item.
         * The method panics if the specified item index is not valid.
         *
         * @param aItemIndex The position of the item to set as the currently
         *                   selected item
         * @remarks
         * @see
         */
        IMPORT_C void SetCurrentItemIndex(TInt aItemIndex);

        /**
         * Gets the index of the item at the top of the view.
         *
         * @return the item currently displayed at the top of this Listbox view
         * @remarks
         * @see
         */
        IMPORT_C TInt TopItemIndex() const;

        /**
         * Sets the item that will appear at the top of the Listbox view, by index.
         * This method also invokes <code>CalcBottomItemIndex()</code>.
         *
         * @param aItemIndex The index of the item to start the Listbox view at
         * @remarks
         * @see
         */
        IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex);

        /**
         * Gets the index of the item at the bottom of the Listbox view.
         *
         * @return the index of the item at the bottom of the Listbox view
         * @remarks
         * @see
         */
        IMPORT_C TInt BottomItemIndex() const;

        /**
         * Recalculates the index of the bottom item in the list from the top
         * item index and the size of the display.
         * This method is called by the owning Listbox control when either the
         * size of the Listbox or the number of items in its model
         * changes, that is, when items are added or removed from the Listbox.
         *
         * @remarks
         * @see
         */
        IMPORT_C virtual void CalcBottomItemIndex();

        /**
         * Sets the item height for every entry in the Listbox.
         *
         * @param aItemHeight The new item height
         * @remarks
         * @see
         */
        IMPORT_C virtual void SetItemHeight(TInt aItemHeight);

        /**
         * Sets the matcher cursor's color.
         *
         * @param aColor The color in which to display the incremental match
         *               cursor
         * @remarks
         * @see
         */
        IMPORT_C void SetMatcherCursorColor(TRgb aColor);

        /**
         * Sets the matcher cursor's position within an item.
         *
         * @param aPosWithinCurrentItem The character position for the match
         *                              cursor within the current item's string
         * @remarks
         * @see
         */
        IMPORT_C void SetMatcherCursorPos(TInt aPosWithinCurrentItem);

        /**
         * Gets the matcher cursor's position.
         *
         * @return the character position of the matcher cursor within the
         *            current item's string
         * @remarks
         * @see
         */
        IMPORT_C TInt MatcherCursorPos() const;

        /**
         * If the matcher cursor flag has been set with 
         * <code>SetMatchCursor(ETrue)</code>, draws the matcher cursor in its 
         * current screen position.
         *
         * @remarks
         * @see
         */
        IMPORT_C void DrawMatcherCursor();

        /**
         * Hides the matcher cursor.
         *
         * @remarks
         * @see
         */
        IMPORT_C void HideMatcherCursor();

        /**
         * Sets or resets the matcher cursor flag <code>EHasMatcherCursor</code>
         * to specify whether the matcher cursor is drawn.
         * The matcher cursor is the cursor that highlights matched text via
         * incremental matching.
         *
         * @param aMatcherCursor If <code>ETrue</code>, this view will draw
         *                       matcher cursors. If <code>EFalse</code> will not
         *                       draw matcher cursors
         * @remarks
         * @see <code>CListBoxView::EHasMatcherCursor</code>
         */
        IMPORT_C void SetMatcherCursor(TBool aMatcherCursor);

        /**
         * Sets whether or not items are drawn emphasized.
         * This method sets or resets the emphasized flag <code>EEmphasized</code>.
         *
         * @param aEmphasized If <code>ETrue</code>, this view will draw items
         *                    emphasized; if <code>EFalse</code> the items will
         *                    be drawn without emphasis
         * @remarks 'Emphasized', in terms of a Listbox item, refers to whether 
         *          the currently selected item is drawn with focus or not
         * @see CListBoxView::EEmphasized
         */
        IMPORT_C void SetEmphasized(TBool aEmphasized);

        /**
         * Sets whether or not items are drawn dimmed.
         * This method sets or resets the dim flag.
         *
         * @param aDimmed If <code>ETrue</code>, this view will draw items
         *                dimmed; if <code>EFalse</code> items are not drawn
         *                dimmed
         * @remarks
         * @see
         */
        IMPORT_C void SetDimmed(TBool aDimmed);

        /**
         * Disables or enables redraws.
         * If this flag is set to <code>ETrue</code>, all member methods that
         * draw items return immediately without drawing anything.
         * Methods that update the internal state of the Listbox will still
         * work, but nothing is drawn or updated on the screen.
         * This method is most commonly used to disable redraws for a short
         * period while changes are made to the Listbox, and then enabling
         * redraws. This stops wasted use of multiple screen updates.
         *
         * @param aDisableRedraw If <code>ETrue</code>, disables redraw;
         *                        <code>EFalse</code> otherwise
         * @remarks
         * @see
         */
        IMPORT_C void SetDisableRedraw(TBool aDisableRedraw);

        /**
         * Tests whether redraw is disabled.
         *
         * @return <code>ETrue</code> if redraw is disabled; <code>EFalse</code>
         *         otherwise
         * @remarks
         * @see
         */
        IMPORT_C TBool RedrawDisabled() const;

        /**
         * Sets the painted selection flag.
         * If set, draws a highlight over selected Listbox items.
         *
         * @param aPaintedSelection If <code>ETrue</code>, the painted selection
         *                          flag is set on; if <code>EFalse</code>, the
         *                          selection flag is set off; if
         *                          <code>NULL</code>, the painted selection
         *                          flag is cleared
         * @remarks This method is called from <code>CEikListBox::CreateViewL()</code>,
         *          when the Listbox is constructed
         * @see CListBoxView::EPaintedSelection
         */
        IMPORT_C void SetPaintedSelection( TBool aPaintedSelection );

        /**
         * Gets a pointer to the items that are currently selected.
         * The entries in the array hold the indices of the items
         * in the Listbox that are currently selected.
         *
         * @return a pointer to an array describing the items in the list
         *         that are currently selected. The object pointed to is
         *         owned by the <code>CListBoxView</code>
         * @remarks
         * @see
         */
        IMPORT_C const CSelectionIndexArray* SelectionIndexes() const;

        /**
         * Gets a copy of the array of currently selected items.
         * The copy of the array returned is not owned by the Listbox,
         * and the developer is responsible for its cleanup.
         * If there is no memory available for
         * creating the copy of the selection array, this method leaves.
         * If there is no selection array to copy, an empty array is returned.
         *
         * @param aSelectionArray An instantiated
         *                        <code>CSelectionIndexArray</code>. On
         *                        return, contains a copy of
         *                        <code>SelectionIndexes()</code>
         * @remarks
         * @see CListBoxView::CSelectionIndexArray
         */
        IMPORT_C void GetSelectionIndexesL(CSelectionIndexArray* aSelectionArray) const;

        /**
         * Sets the currently selected items of this view from a selection
         * index array.
         *
         * @param aSelectionIndexes The items to select
         * @remarks
         * @see
         */
        IMPORT_C void SetSelectionIndexesL(const CSelectionIndexArray* aSelectionIndexes);

        /**
         * Resets the selection state so that there is nothing selected.
         *
         * @remarks
         * @see
         */
        IMPORT_C void ClearSelection();

        /**
         * Updates item selection.
         *
         * @param aSelectionMode The selection mode
         * @remarks
         * @see CListBoxView::TSelectionMode
         */
        IMPORT_C virtual void UpdateSelectionL(TSelectionMode aSelectionMode);  // select/highlight items without moving the cursor

        /**
         * Toggles the selection of an item.
         *
         * @param aItemIndex The item to toggle
         * @remarks
         * @see
         */
        IMPORT_C void ToggleItemL(TInt aItemIndex);

        /**
         * Selects the item identified by <code>aItemIndex</code>. The newly 
         * selected item is added to the array of selected items.
         * If memory could not be allocated for an extra
         * item in the array of selected items, this method leaves.
         *
         * @param aItemIndex The item to select
         * @internal
         * @deprecated
         */
        IMPORT_C void SelectItemL(TInt aItemIndex);

        /**
         * Selects the item identified by <code>aItemIndex</code>. The newly 
         * selected item is added to the array of selected items. If memory 
         * could not be allocated for an extra item in the array of selected 
         * items, this method leaves with <code>KErrNoMemory</code>.
         *
         * @param aItemIndex The item to select
         * @param aReportSelectionChanged If <code>ETrue</code> and the
         *                                selection has changed, this 
         *                                triggers a notification of 
         *                                <code>EEventSelectionChanged</code>
         *                                to the view's observer
         * @since 6.2
         * @remarks 
         * @see MEikListBoxObserver::EEventSelectionChanged in eiklbo.h
         * @see HandleListBoxEventL() in eiklbo.h
         */
        IMPORT_C void SelectItemL(TInt aItemIndex, TBool aReportSelectionChanged);

        /**
         *
         * Deselects an item by index.
         *
         * @param aItemIndex Item to deselect
         * @internal
         * @deprecated
         */
        IMPORT_C void DeselectItem(TInt aItemIndex);

        /**
         * Deselects an item by index.
         *
         * @param aItemIndex The item to deselect
         * @param aReportSelectionChanged If <code>ETrue</code> and the
         *                                selection has changed, this 
         *                                triggers a notification to the view's
         *                                observer
         * @since 6.2
         * @remarks
         * @see
         */
        IMPORT_C void DeselectItem(TInt aItemIndex, TBool aReportSelectionChanged);

        /**
         * Sets the anchor to the specified item.
         *
         * @param aItemIndex The index of the item at which the anchor is set
         * @remarks
         * @see
         */
        IMPORT_C void SetAnchor(TInt aItemIndex);

        /**
         * Sets the anchor index and active end index to <code>NULL</code>,
         * and clears the <code>EAnchorExists</code> flag.
         *
         * @remarks
         * @see
         */
        IMPORT_C void ClearSelectionAnchorAndActiveIndex();

        /**
         * Scrolls vertically to make a particular item visible.
         *
         * @param aItemIndex The item to make visible
         * @return <code>ETrue</code> if any scrolling was performed;
         *         <code>EFalse</code> if no scrolling was necessary
         * @remarks
         * @see
         */
        IMPORT_C virtual TBool ScrollToMakeItemVisible(TInt aItemIndex);

        /**
         * Scrolls vertically to the specified item.
         * Scrolls the contents of this list view so that the specified item
         * is the top item and redraws the view.
         *
         * @param aNewTopItemIndex The item to scroll to
         * @remarks
         * @see
         */
        IMPORT_C virtual void VScrollTo(TInt aNewTopItemIndex);

        /**
         * Scrolls vertically to the specified item.
         * Scrolls the contents of this list view so that the specified item
         * is the top item and redraws the view.
         *
         * @param aNewTopItemIndex The item to scroll to
         * @param aMinRedrawRect The minimum area that needs to be redrawn
         *                       for this scroll event
         * @remarks
         * @see
         */
        IMPORT_C virtual void VScrollTo(TInt aNewTopItemIndex, TRect& aMinRedrawRect);

        /**
         * Scrolls horizontally by the specified number of pixels.
         *
         * @param aHScrollAmount The distance to scroll by, in pixels. A
         *                       negative value scrolls to the left, a
         *                       positive value scrolls to the right
         * @remarks
         * @see
         */
        IMPORT_C virtual void HScroll(TInt aHScrollAmount);

        /**
         * Gets the offset of the visible portion of the data from the left
         * margin, in pixels.
         *
         * @return The horizontal scroll offset, in pixels
         * @remarks
         * @see
         */
        IMPORT_C TInt HScrollOffset() const;

        /**
         * Sets the horizontal scroll offset, in pixels.
         *
         * @param aHorizontalOffset The new value for the horizontal scroll
         *                          offset, in pixels
         * @remarks
         * @see
         */
        IMPORT_C void SetHScrollOffset(TInt aHorizontalOffset);

        /**
         * Gets the width of the widest item in the list, in pixels.
         *
         * @return the data width, in pixels
         * @remarks
         * @see
         */
        IMPORT_C TInt DataWidth() const;

        /**
         * Recalculates the data width of this Listbox view from the item width
         * of its list item drawer.
         * This method is called directly by <code>CEikListBox</code> when the
         * Listbox's size changes or when data is added.
         *
         * @remarks
         * @see
         */
        IMPORT_C virtual void CalcDataWidth();

        /**
         * Gets the visible width of the specified rectangle, in pixels.
         *
         * @param aRect The rectangle to get the visible width for
         * @return the visible width of <code>aRect</code>, in pixels
         * @remarks This method returns the <code>Rect.Width()</code> of 
         *          the specified rectangle
         * @see
         */
        IMPORT_C virtual TInt VisibleWidth(const TRect& aRect) const;

        /**
         * Calculates which item to scroll to in order to make a
         * particular item visible. For example, calling
         * <code>VScrollTo(CalcNewTopItemIndexSoItemIsVisible(idx))</code>
         * makes the item with an index of <code>idx</code> visible.
         *
         * @param aItemIndex The index of the new top item
         * @return the item to scroll to
         * @remarks
         * @see
         */
        IMPORT_C virtual TInt CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const;

        /**
         * Draws every visible item within the specified rectangle.
         * As implemented in <code>CListBoxView</code>, this method's argument
         * is ignored and the internal viewing rectangle, as set with the
         * method <code>SetViewRect()</code>, is used.
         *
         * @param aClipRect The rectangle to draw into (this is ignored)
         * @remarks
         * @see CListBoxView::SetViewRect()
         */
        IMPORT_C virtual void Draw(const TRect* aClipRect = NULL) const;

        /**
         * Draws the specified item via <code>CListBoxDrawer::DrawItem()</code>
         * if it is visible.
         *
         * @param aItemIndex The index number of the item to draw
         * @remarks
         * @see
         */
        IMPORT_C virtual void DrawItem(TInt aItemIndex) const;

        /**
         * Determines whether an item is selected.
         *
         * @param aItemIndex The index of the item to test
         * @return <code>ETrue</code> if the item is selected;
         *         <code>EFalse</code> otherwise
         * @remarks
         * @see
         */
        IMPORT_C TBool ItemIsSelected(TInt aItemIndex) const;

        /**
         * Determines whether an item is visible.
         *
         * @param aItemIndex The index of the item to test
         * @return <code>ETrue</code> if the item is visible or partially visible;
         *         <code>EFalse</code> otherwise
         * @remarks
         * @see
         */
        IMPORT_C TBool ItemIsVisible(TInt aItemIndex) const; // returns "true" if the item is fully or partially visible

        /**
         * Returns whether an item is fully visible or not.
         *
         * @param aItemIndex The index of the item to test
         * @since App-Framework_6.2
         * @public
         * @return <code>ETrue</code> if the item is fully visible;
         *         <code>EFalse</code> if the item is partially or not visible
         * @remarks
         * @see
         */
        IMPORT_C TBool ItemIsFullyVisible(TInt aItemIndex) const;

        /**
         * Returns whether an item is partially visible or not. 
         *
         * @param aItemIndex The index of the item to test
         * @return <code>EFalse</code> if the item at <code>aItemIndex</code>
         *         is fully visible; <code>ETrue</code> otherwise
         * @since App-Framework_6.2
         * @public
         * @remarks
         * @see
         */
        IMPORT_C TBool ItemIsPartiallyVisible(TInt aItemIndex) const;

        /**
         * Gets the onscreen position of an item.
         *
         * @param aItemIndex The index of an item
         * @return the position of the item
         * @remarks
         * @see
         */
        IMPORT_C virtual TPoint ItemPos(TInt aItemIndex) const;

        /**
         * Gets the onscreen size of an item.
         * As implemented in <code>CListBoxView</code>, all items report the
         * same size. The size returned may be larger than the width of the
         * Listbox view, but will not be smaller.
         *
         * @param aItemIndex The index of an item
         * @return the size of the item
         * @remarks
         * @see
         */
        IMPORT_C virtual TSize ItemSize(TInt aItemIndex=0) const;

        /**
         * Sets the color in which to display item text.
         *
         * @param aColor The color in which to display item text
         * @remarks
         * @see
         */
        IMPORT_C void SetTextColor(TRgb aColor);

        /**
         * Sets the item background color.
         *
         * @param aColor The background color
         * @remarks
         * @see
         */
        IMPORT_C void SetBackColor(TRgb aColor);

        /**
         * Gets the color in which the item text is to be displayed.
         *
         * @return the current text color
         * @remarks
         * @see
         */
        IMPORT_C TRgb TextColor() const;

        /**
         * Gets the background color used to display items.
         *
         * @return the current background color
         * @remarks
         * @see
         */
        IMPORT_C TRgb BackColor() const;

        /**
         * Calculates a new index position for the current item cursor
         * after it is moved in the specified direction.
         *
         * @param aCursorMovement The cursor movement to apply
         * @return the newly calculated cursor index position
         * @remarks
         * @see CListBoxView::TCursorMovement
         */
        IMPORT_C TInt GetNewCursorPos(TCursorMovement aCursorMovement);

        /**
         * Responds to cursor movement commands sent by the Listbox control,
         * updating the selection appropriately if a selection mode has been set
         * for the action.
         *
         * @param aCursorMovement A cursor movement action
         * @param aSelectionMode The selection mode in use for that action
         * @remarks
         * @see
         */
        IMPORT_C virtual void MoveCursorL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode);

        /**
         * Moves to the specified item, sets it as the current item, and scrolls
         * the display to make the item visible.
         * Depending on the selection mode used, this method may add items to the
         * selection array, that is, <code>EContiguousSelection</code>.
         *
         * @param aTargetItemIndex The index of the item to move to
         * @param aSelectionMode The selection mode
         * @remarks
         * @see
         */
        IMPORT_C virtual void VerticalMoveToItemL(TInt aTargetItemIndex, TSelectionMode aSelectionMode);

        /**
         * Converts a pixel position into an item index.
         * This method returns <code>ETrue</code> and sets
         * <code>aItemIndex</code> to the index of the item whose bounding box
         * contains <code>aPosition</code>.
         * Returns <code>EFalse</code> if no such item exists.
         *
         * @param aPosition A position relative to the origin of the Listbox
         *                  control
         * @param aItemIndex Is set to the item at that position
         * @return whether there was an item at <code>aPosition</code>
         * @remarks
         * @see
         */
        IMPORT_C virtual TBool XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const;   // returns false if no item                                                            //Keyword to test this

        /**
         * Calculates whether a pixel position is in the tick mark column.
         * If the tick mark column contains <code>aPosition</code>, the method
         * returns <code>ETrue</code>; if not, it returns <code>EFalse</code>.
         *
         * @param aPosition A position relative to the origin of the Listbox's
         *                  view
         * @return whether or not <code>aPosition</code> is in the tick mark column
         * @remarks
         * @see
         */
        IMPORT_C TBool XYPosInMarkColumn(TPoint aPosition);

        /**
         * Gets the largest number of items that could fit inside the specified
         * rectangle.
         * This virtual method is used internally for layout of the view.
         *
         * @param aRect A rectangle
         * @return the largest number of items that could fit in the
         *            rectangle
         * @remarks
         * @see
         */
        IMPORT_C virtual TInt NumberOfItemsThatFitInRect(const TRect& aRect) const;

        /**
         * Sets the visibility observer.
         * The <code>MListVisibilityObserver</code> class tests the visibility
         * of a Listbox view.
         *
         * @param aObserver The new visibility observer for this control
         * @remarks
         * @see MListVisibilityObserver in eiklbv.h
         */
        void SetVisibilityObserver(MListVisibilityObserver* aObserver);

        /**
         * Tests if this view is visible.
         *
         * @return <code>ETrue</code> if this view is visible; <code>EFalse</code>
         *         if this view is not visible, or does not exist
         * @remarks
         * @see
         */
        IMPORT_C TBool IsVisible() const;

        /**
         * Gets the object used by this Listbox view to draw its items.
         *
         * @return the pointer to the Listbox viewer
         * @remarks
         * @see
         */
        inline CListItemDrawer* ItemDrawer() const;

        /**
         * Returns whether variable-height items have been explicitly allowed
         * on this Listbox.
         *
         * @since App-Framework_6.2
         * @public
         * @return <code>ETrue</code> if variable-height items have been 
         *         explicitly allowed; <code>EFalse</code> otherwise
         * @remarks
         * @see CListBoxView::EAllowVariableHeightItems
         */
        IMPORT_C TBool SupportsVariableHeightItems() const;

        /**
         * Returns whether showing partially visible items have been explicitly
         * allowed on this Listbox.
         *
         * @since App-Framework_6.2
         * @public
         * @return <code>ETrue</code> if partially visible items have been 
         *         explicitly allowed; <code>EFalse</code> otherwise
         * @remarks
         * @see CListBoxView::EAllowPartiallyVisibleItems
         */
        IMPORT_C TBool SupportsPartiallyVisibleItems() const;

        /**
         * Sets the flag <code>EDataWidthClippedToViewRect</code> that allows 
         * the view to handle the fact that its text may be truncated to fit 
         * within the bounds of the view rectangle. If text is truncated, 
         * an ellipsis is appended to the end of the text to signify this.
         *
         * @param aIsClipped If <code>ETrue</code>, text may be truncated; if
         *                   <code>EFalse</code>, the text is not truncated
         * @since App-Framework_6.2
         * @public
         * @remarks
         * @see CListBoxView::EDataWidthClippedToViewRect
         */
        IMPORT_C void SetDataWidthClippedToViewRect(TBool aIsClipped);

        /**
         * Returns a boolean value informing the client whether or not the
         * text has been truncated to fit within the bounds of the list's view
         * rectangle, so that special handling can be done, for example,
         * adding an ellipsis.
         *
         * @return <code>ETrue</code> if the clipped to view flag is set;
         *         <code>EFalse</code> if the clipped to view flag is not set
         * @since App-Framework_6.2
         * @public
         * @remarks
         * @see
         */
        IMPORT_C TBool DataWidthClippedToViewRect() const;

        /**
         * Sets the text string to display in an empty list. If this is not
         * set, no text is displayed when the list is empty.
         *
         * @param aEmptyText The string to display
         * @since Series90 1.0
         * @public
         * @remarks
         * @see
         */
        IMPORT_C void SetEmptyListTextL(const TDesC& aEmptyText);

public: // but not exported
        /** @internal */
        void DrawItem(CWindowGc& aGc, TInt aItemIndex);
        /** @internal */
        void Draw(CWindowGc& aGc, const TRect* aClipRect=NULL);
        /** @internal */
        TInt NumberOfItemsThatFitGivenTopItemIndex(TInt& aNumberOfSpareVerticalPixels, TBool& aFillsVerticalPixelSpan, TInt aNumberOfVerticalPixels, TInt aTopItemIndex) const;
        /** @internal */
        TInt NumberOfItemsThatFitGivenBottomItemIndex(TInt& aNumberOfSpareVerticalPixels, TBool& aFillsVerticalPixelSpan, TInt aNumberOfVerticalPixels, TInt aBottomItemIndex) const;
        /** @internal */
        TInt CalculatedScrollBarThumbPosition(TInt aNumberOfPixelsAboveTopItem, TInt aTopItemIndex) const;
        /** @internal */
        TInt TopItemIndexCalculatedFromScrollBarThumbPosition(TInt& aNumberOfPixelsAboveTopItem, TInt& aScrollBarScrollSpan, TInt& aScrollBarThumbPosition) const;
        /** @internal */
        void SetItemHeightL(TInt aItemIndex, TInt aItemHeight);
        /** @internal */
        void SetToDefaultItemHeight(TInt aItemIndex);
        /** @internal */
        TInt ItemHeight(TInt aItemIndex) const;
        /** @internal */
        void CreateExtensionL();
        /** @internal */
        void HoldNewNumberOfPixelsAboveTopItem(TInt aNewNumberOfPixelsAboveTopItem);
        /** @internal */
        void HoldNewTopItemIndex(TInt aNewTopItemIndex);
        /** @internal */
        void HoldNewViewRect(const TRect& aNewViewRect);
        /** @internal */
        void HoldNumberOfVerticalPixels(TInt aNumberOfVerticalPixels);
        /** @internal */
        void HoldListBox(CEikListBox* aListBox);
        /** @internal */
        TBool HoldingNewNumberOfPixelsAboveTopItem() const;
        /** @internal */
        TBool HoldingNewTopItemIndex() const;
        /** @internal */
        TBool HoldingNewViewRect() const;
        /** @internal */
        TBool HoldingNumberOfVerticalPixels() const;
        /** @internal */
        TBool HoldingListBox() const;
        /** @internal */
        TInt NewNumberOfPixelsAboveTopItem() const;
        /** @internal */
        TInt NewTopItemIndex() const;
        /** @internal */
        TRect NewViewRect() const;
        /** @internal */
        TInt NumberOfVerticalPixels() const;
        /** @internal */
        CEikListBox* ListBox() const;
        /** @internal */
        void DropNewNumberOfPixelsAboveTopItem();
        /** @internal */
        void DropNewTopItemIndex();
        /** @internal */
        void DropNewViewRect();
        /** @internal */
        void DropNumberOfVerticalPixels();
        /** @internal */
        void DropListBox();
        /** @internal */
        TBool DragSelect() const;
        /** @internal */
        void SetListBoxViewObserverL(MEikListBoxViewObserver* aObserver);
        /** @internal */
        void VScrollTo(CWindowGc& aGc, TInt aNewTopItemIndex);
        /** @internal */
        void CommonConstructorCode(TUint aInitialFlags); // one or more of TInitialFlags
        /** @internal */
        CListBoxViewExtra* Extra() const;
        /** @internal */
        void ModifySelectionArrayL(CSelectionIndexArray& aSelectionIndexes,TSelectionModificationOperation aOperation,TInt aModificationArgument, TBool aReportSelectionChanged);
        /** @internal */
        TBool AnchorStartItemSelected() const;
private:
        IMPORT_C virtual TAny* Reserved_1();

protected:
/**
 * Gets this views flags.
 *
 * @returns   "TInt"
 *            An OR-ed combination of <code>TFlags</code>.
 */
        inline TInt Flags() const;

/**
 * Sets this views flags according to a bitmask.
 *
 * @param     "TInt aMask"
 *            An OR-ed combination of <code>TFlags</code>.
 */
        inline void SetFlags(TInt aMask);

/**
 * Clears this views flags according to a bitmask.
 *
 * @param     "TInt aMask"
 *            An OR-ed combination of <code>TFlags</code>.
 */
        inline void ClearFlags(TInt aMask);

/**
 *
 * Selects all items in the list between the two specified indices,
 * inclusively. Reports a selection changed event once for the range.
 *
 * @param     "TInt aItemIndex1"
 *            One end of the range to select.
 * @param     "TInt aItemIndex2"
 *            The other end of the range to select.
 */
        IMPORT_C void SelectRangeL(TInt aItemIndex1, TInt aItemIndex2);
        void SelectRangeL(TInt aItemIndex1, TInt aItemIndex2, TSelectionModificationOperation aOperation);

private:
		TRect CalculateMatcherCursorRect() const;

    protected:     // Data
        TInt iFlags;
        CListItemDrawer* iItemDrawer;
        MListBoxModel* iModel;
        TInt iDataWidth;            // width (in pixels) of the longest item in the model
        TInt iTopItemIndex;
        TInt iBottomItemIndex;
        TInt iHScrollOffset;        // pixel offset (from the left margin) of the visible portion of the data
        TInt iCurrentItemIndex;
        TInt iItemHeight;
        RWindow* iWin;
        RWindowGroup* iGroupWin;
        CWindowGc* iGc;
        TRect iViewRect;

    private:     // Data
        TInt iMatcherCursorPos;
        TRgb iMatcherCursorColor;
        TRgb iBackColor;
        TRgb iTextColor;
        TInt iAnchorIndex;
        TInt iActiveEndIndex;
        CListBoxViewExtra* iExtra;
        MListVisibilityObserver* iVisibilityObserver;

    };

/**
 * The <code>CSnakingListBoxView</code> class provides the Listbox view for
 * Snaking Listboxes.
 * The view is responsible for drawing items and maintaining the
 * selection status.
 *
 * @since 6.0
 * @lib eikcoctl.lib
 */
class CSnakingListBoxView : public CListBoxView
    {

    public:
    // Constructors and destructor
        /**
        * The object destructor.
        */
        IMPORT_C ~CSnakingListBoxView();

        /**
        * The default object constructor.
        */
        IMPORT_C CSnakingListBoxView();

    // New methods

       /**
        * Gets the width of all columns in the view.
        *
        * @return the width of all columns in the view, in pixels
        */
        inline TInt ColumnWidth() const;

       /**
        * Sets the width of all columns in the view.
        *
        * @param aColumnWidth The required width of all columns in the view, in
        *            pixels
        */
        IMPORT_C void SetColumnWidth(TInt aColumnWidth);

       /**
        * Responds to cursor movement commands sent by the Listbox control. It
        * updates the selection appropriately if a selection mode has been set
        * for the action.
        *
        * @param aCursorMovement A cursor movement action
        * @param aSelectionMode The selection mode in use for that action
        */
        IMPORT_C virtual void MoveCursorL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode);

       /**
        * Sets which item appears at the top left corner of the view.
        * This method changes items displayed in the view appropriately.
        *
        * @param aItemIndex Index of the item to set at the top left
        */
        IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex);

       /**
        * Sets the item height, in pixels.
        *
        * @param aItemHeight The new height for this view's items, in pixels
        */
        IMPORT_C virtual void SetItemHeight(TInt aItemHeight);

       /**
        * Converts a pixel position into an item index.
        * This method returns <code>ETrue</code> and sets
        * <code>aItemIndex</code> to the index of the item whose bounding box
        * contains <code>aPosition</code>. It returns <code>EFalse</code> if no
        * such item exists.
        *
        * @param aPosition A position relative to the origin of the Listbox
        *            control
        * @param aItemIndex Is set to the item at that position
        * @return whether there was an item at <code>aPosition</code>
        */
        IMPORT_C virtual TBool XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const;

       /**
        * Gets the largest number of items that could fit inside the specified
        * rectangle.
        * This virtual method is used internally for layout of the view.
        *
        * @param aRect A rectangle
        * @return the largest number of items that could fit in the
        *            rectangle
        */
        IMPORT_C virtual TInt NumberOfItemsThatFitInRect(const TRect& aRect) const;

       /**
        * Scrolls horizontally by a number of columns.
        *
        * @param aHScrollAmount The number of columns to move. A positive
        *                       value scrolls to the right, a negative value scrolls
        *                       to the left
        */
        IMPORT_C virtual void HScroll(TInt aHScrollAmount);

       /**
        * Calculates the data width, in columns.
        * <code>iDataWidth</code> is calculated based on model and drawer
        * information.
        *
        */
        IMPORT_C virtual void CalcDataWidth();

       /**
        * Recalculates the bottom item's index.
        * This method is called by the Listbox control when either the size
        * of the Listbox or the number of items in its model changes. In
        * <code>CSnakingListBox</code>, this method calculates the index of the
        * item at bottom right.
        *
        */
        IMPORT_C virtual void CalcBottomItemIndex();

       /**
        * Draws the portion of the view inside the specified rectangle into
        * <code>iGc</code>.
        * This method is called by the control's own <code>Draw()</code>
        * method.
        *
        * @param aClipRect A clipping rectangle. <code>NULL</code> means
        *                  redraw the entire view
        */
        IMPORT_C virtual void Draw(const TRect* aClipRect = NULL) const;

       /**
        * Gets the visible width of the specified rectangle, in pixels.
        *
        * @param aRect The rectangle for which to get the visible width
        * @return the visible width of <code>aRect</code>, in pixels
        */
        IMPORT_C virtual TInt VisibleWidth(const TRect& aRect) const;

       /**
        * Makes the specified item visible by moving the view location and
        * redrawing the control.
        *
        * @param aItemIndex The index of the item to make visible
        * @return <code>ETrue</code> if the control was redrawn;
        *            <code>EFalse</code> if no redraw happened (i.e. the
        *            item was already visible, or redraw was disabled)
        */
        IMPORT_C virtual TBool ScrollToMakeItemVisible(TInt aItemIndex);

       /**
        * Gets the number of columns that this view would need to be scrolled
        * by to make the specified item visible.
        * This method returns <code>0</code> if no scrolling is
        * needed. <code>ScrollToMakeItemVisible()</code> uses this method.
        *
        * @param aItemIndex The item to make visible
        * @return the number of columns to scroll, or zero if no
        *            scrolling is needed
        */
        IMPORT_C virtual TInt CalculateHScrollOffsetSoItemIsVisible(TInt aItemIndex);

       /**
        * Calculates which item to scroll to in order to make a
        * particular item visible.
        * For example, calling
        * <code>VScrollTo(CalcNewTopItemIndexSoItemIsVisible(idx))</code>
        * would make the item whose index is <code>idx</code> visible.
        *
        * @param aItemIndex The index of the new top item
        * @return the item to scroll to
        */
        IMPORT_C virtual TInt CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const;

       /**
        * Gets the position of the top left corner of the specified item, in
        * pixels.
        *
        * @param  aItemIndex An item in the model
        * @return contains the position of the top left corner
        *         of the item, in pixels
        */
        IMPORT_C virtual TPoint ItemPos(TInt aItemIndex) const;

       /**
        * Gets the size of the specified item.
        *
        * @param aItemIndex The index of the item to retrieve the size from
        * @return the size of the item, in pixels
        */
        IMPORT_C virtual TSize ItemSize(TInt aItemIndex=0) const;

       /**
        * Converts an item index into the row/column pair describing that
        * item. This method returns references passed in via the parameters.
        *
        * @param aItemIndex The item index
        * @param aRowIndex Returns a referance to the row index
        * @param aColIndex Returns a referance to the column index
        */
        IMPORT_C void CalcRowAndColIndexesFromItemIndex(TInt aItemIndex, TInt& aRowIndex, TInt& aColIndex) const;

       /**
        * Converts a row/column pair into the item index for that item.
        *
        * @param aItemIndex Returns the item index
        * @param aRowIndex The row index of the item
        * @param aColIndex The column index of the item
        */
        IMPORT_C void CalcItemIndexFromRowAndColIndexes(TInt& aItemIndex, TInt aRowIndex, TInt aColIndex) const;

       /**
        * Gets the number of items that can fit in a column.
        *
        * @return the number of items that can fit in a column
        */
        IMPORT_C TInt NumberOfItemsPerColumn() const;

    protected:  // Methods

    // New Methods

/**
 *
 * Draws every item between the start and end indices inclusively.
 *
 * @param     " TInt aStartItemIndex "
 *            First item to draw.
 * @param     " TInt aEndItemIndex "
 *            Final item to draw.
 */
        IMPORT_C void DrawItemRange(TInt aStartItemIndex, TInt aEndItemIndex) const;

/**
 *
 * Draws every item in every column between the start and end columns
 * inclusively.
 *
 * @param     " TInt aStartColIndex "
 *            First column to draw.
 * @param     " TInt aEndColIndex "
 *            Last column to draw.
 */
        IMPORT_C void DrawColumnRange(TInt aStartColIndex, TInt aEndColIndex) const;

/**
 *
 * Move to previous column.
 *
 * Whether the selection is updated depends on
 * <code>aSelectionMode</code>.
 *
 * @param     " TSelectionMode aSelectionMode "
 *            Determines whether and how the selection is updated.
 */
        IMPORT_C void MoveToPreviousColumnL(TSelectionMode aSelectionMode);

/**
 *
 * Move to next column.
 *
 * Whether the selection is updated depends on
 * <code>aSelectionMode</code>.
 *
 * @param     " TSelectionMode aSelectionMode "
 *            Determines whether and how the selection is updated.
 */
        IMPORT_C void MoveToNextColumnL(TSelectionMode aSelectionMode);

/**
 *
 * Clears each items rectangle between the specified start and finish
 * items indexes.
 *
 * @param     " TInt aStartItemIndex "
 *            First item to clear.
 * @param     " TInt aEndItemIndex "
 *            Last item to clear.
 */
        IMPORT_C void ClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex) const;

/**
 *
 * Updates the horizontal scroll offset (<code>iHScrollOffset</code>)
 * based on the top items index.
 *
 * This function is called internally by
 * <code>CEikSnakingListBox</code>es when needed.
 *
 */

        IMPORT_C void UpdateHScrollOffsetBasedOnTopItemIndex();

    private: //Methods
        IMPORT_C virtual TAny* Reserved_1();

    protected:     // Data
        TInt iColumnWidth;
    };

//
// INLINE FUNCTIONS
//

inline TInt CListBoxView::Flags() const
    { return iFlags; }

inline void CListBoxView::SetFlags(TInt aMask)
    { iFlags|=aMask; }

inline void CListBoxView::ClearFlags(TInt aMask)
    { iFlags&=(~aMask); }

inline CListItemDrawer* CListBoxView::ItemDrawer() const
    { return iItemDrawer; }

inline TInt CSnakingListBoxView::ColumnWidth() const
    { return iColumnWidth; }

#endif      // EIKLBV_H

// End of File
