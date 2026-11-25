/*
* =============================================================================
*  Name        : eiktxlbx.h
*  Part of     : CKON
*  Interface   : List box API
*  Description : Text Listbox control and snaking Text Listbox control.
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
* =============================================================================
*/

#ifndef EIKTXLBX_H
#define EIKTXLBX_H


//** INCLUDES */
#include <coecntrl.h>
#include <eiklbx.h>
#include <eiklbm.h>

//** FORWARD DECLARATIONS */
class CTextListBoxModel;


//** CLASS DECLARATIONS */

/**
 * The <code>CEikTextListBox</code> class provides a Listbox for 
 * displaying text. Text Listboxes use the standard Listbox view, 
 * <code>CListBoxView</code>, and a customized item drawer and Listbox
 * model. When writing derived classes, this class can be either used as is, 
 * or derived from to provide further functionality. There are three classes
 * supplied in <code>Uikon</code> that are derived from this class: 
 * <code>CEikChoiceListPopoutListBox</code>, <code>CEikColumnListBox</code>, 
 * and <code>CEikFileSelectorListBox</code>.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CEikTextListBox : public CEikListBox
    {
public:
    //** Constructors and destructor */

    /**
     * The default object constructor.
     */
    IMPORT_C CEikTextListBox();

    /**
     * The object destructor.
     */
    IMPORT_C ~CEikTextListBox();


    //** New methods */

    /**
     * Constructs a Text Listbox from a resource file. 
     * 
     * @param aReader A resource reader
     * @remarks The resource type is <code>LISTBOX</code>
     * @see CCoeControl
     */
    IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

    /**
     * Completes construction of a Text Listbox object.
     *
     * @param aParent The parent control for this control
     * @param aFlags The flags for the Text Listbox
     * @remarks
     * @see
     */
    IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aFlags = 0);

    /**
     * Gets the Text Listbox model.
     *
     * @return the Listbox model used by this Text Listbox
     * @remarks
     * @see
     */
    IMPORT_C CTextListBoxModel* Model() const;

    //** Methods from base classes */

    /**
     * Gets the list of logical colors used for drawing the control. This 
     * method is no longer used. Skin functionality manages the colors for 
     * this control.
     * 
     * @param aColorUseList Not used
     * @remarks
     * @see CCoeControl
     */
    IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

    // not available before Release 005u
    /**
     * Handles a change to the control's resources that are shared across the 
     * environment.
     * 
     * @param aType A <code>TInt</code> message UID value for the resource 
     *              that has changed
     * @remarks
     * @see CCoeControl
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);       
	
	/**
	 *
	 * Handles focus changes.
	 *
	 * The function emphasises or de-emphasises the view as needed, and shows
	 * or hides the matcher cursor.
	 *
	 * @param     " TDrawNow aDrawNow "
	 *            If <code>EDrawNow</code>, a redraw is performed
	 *            immediately.
	 */
	IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);

protected: //** Methods */
    //** Methods from base classes */

    /**
     *@internal
     */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

    /**
     * Creates the item drawer.
     */
    IMPORT_C virtual void CreateItemDrawerL();

    /**
     * Creates the Text Listbox view.
     * 
     * @return Pointer to a newly constructed Text Listbox view for this object
     */
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();

private: //** Methods *

    /**
     * Reserved
     */
    IMPORT_C virtual void Reserved_3(); // listbox use only

public:
	void HandleChangeButtonL();
	void HandleControlEventL(CCoeControl* /*aControl*/,MCoeControlObserver::TCoeEvent aEventType);

private:
	void DestroyPopout();
	void CreatePopoutL();
	void DoCreatePopoutL();
	void CreateListBoxL();
	void InitializeListBoxL();
	void SetListBoxExtentL();
	TInt CalculateTextWidth();
	void ActivateListBoxL();

protected: //** Data */
    /** Number of characters to display in a cell*/
    TInt iRequiredCellCharWidth;
    };

/**
 * The <code>CTextListBoxView</code> class provides the Text Listbox view.
 * A Text Listbox view displays the list items that are currently visible in
 * a Text Listbox. Text Listbox views draw each of the items for display using
 * methods defined in their associated Text Listbox drawer. Together with its
 * list item drawer, a <code>CTextListBoxView</code> encapsulates the
 * onscreen appearance of data in a Text Listbox. Text Listbox views also
 * encapsulate item selection, the current item, and the fundamentals of
 * how the selection and the current item are updated according to user
 * input.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CTextListBoxView : public CListBoxView
    {
public:
    //** Constructors and destructor */

    /**
     * The default object constructor.
     */
    IMPORT_C CTextListBoxView();

    /**
     * The object destructor.
     */
    IMPORT_C ~CTextListBoxView();

    //** New methods */

    /**
     * Explicitly allows variable-height items in this Text Listbox.
     *
     * @remarks
     * @see
     */
    IMPORT_C void AllowVariableHeightItems();

    /**
     * Sets a flag to explicitly allow partially visible items to be displayed 
     * at the top and bottom of the Text Listbox.
     *
     * @remarks
     * @see CListBoxView::TInitialFlags
     */
    IMPORT_C void AllowPartiallyVisibleItems();

protected: //** Methods */

    //** New Methods */

    /**
     * Default constructor.
     *
     * @param aInitialFlags One or more of CListBoxView::TInitialFlags
     */
    IMPORT_C CTextListBoxView(TUint aInitialFlags); 

    //** Methods from base classes */

    /**
     * From CListBoxView 
     */

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aListBoxModel The Text Listbox model to use. 
     * @param aItemDrawer A default-constructed item drawer. 
     * @param aScreen Screen on which to display. 
     * @param aGroupWin This Text Listbox view’s window group.
     * @param aWsWindow Window for this view.
     * @param aDisplayArea The viewing rectangle this Text Listbox view is to use.
     * @param aItemHeight Height of a single list item. 
    */
    IMPORT_C virtual void ConstructL(MListBoxModel* aListBoxModel, CListItemDrawer* aItemDrawer, CWsScreenDevice* aScreen, RWindowGroup* aGroupWin, RWindow* aWsWindow, const TRect& aDisplayArea, TInt aItemHeight);

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aItemIndex Index of the item to start the view at.
     */
    IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex);

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     */
    IMPORT_C virtual void CalcBottomItemIndex();

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aItemHeight New item height.
     */
    IMPORT_C virtual void SetItemHeight(TInt aItemHeight);

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aSelectionMode The selection mode.
     */
    IMPORT_C virtual void UpdateSelectionL(TSelectionMode aSelectionMode);

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aItemIndex The item to make visible.
     * @return ETrue if any scrolling was done, EFalse if no scrolling was necessary.
     */
    IMPORT_C virtual TBool ScrollToMakeItemVisible(TInt aItemIndex);

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aNewTopItemIndex The item to scroll to.
     */
    IMPORT_C virtual void VScrollTo(TInt aNewTopItemIndex);

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aNewTopItemIndex The distance by which to scroll. 
     * @param aMinRedrawRect On return, the minimum rectangle to redraw. 
     */
    IMPORT_C virtual void VScrollTo(TInt aNewTopItemIndex, TRect& aMinRedrawRect);

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aHScrollAmount The distance to scroll by in pixels. A negative value scrolls to the left, a positive value scrolls to the right.
     */
    IMPORT_C virtual void HScroll(TInt aHScrollAmount);

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     */
    IMPORT_C virtual void CalcDataWidth();

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aRect The rectangle to get the visible width for. 
     * @return   Visible width of aRect.
     */
    IMPORT_C virtual TInt VisibleWidth(const TRect& aRect) const;

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aItemIndex The index of the new top item.
     * @return   The item to scroll to.
     */
    IMPORT_C virtual TInt CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const;

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aClipRect The rectangle to draw into, this is ignored.
     */
    IMPORT_C virtual void Draw(const TRect* aClipRect = NULL) const;

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aItemIndex Index number of the item to draw.
     */
    IMPORT_C virtual void DrawItem(TInt aItemIndex) const;

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aItemIndex Index of an item.
     */
    IMPORT_C virtual TPoint ItemPos(TInt aItemIndex) const;

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aItemIndex Index of an item. 
     * @return Size of the item.
     */
    IMPORT_C virtual TSize ItemSize(TInt aItemIndex=0) const;

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aCursorMovement The cursor movement to apply. 
     * @param aSelectionMode The selection mode of the calling Text Listbox.
     */
    IMPORT_C virtual void MoveCursorL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode);

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aTargetItemIndex The index of the item to which to move.
     * @param aSelectionMode The selection mode.
     */
    IMPORT_C virtual void VerticalMoveToItemL(TInt aTargetItemIndex, TSelectionMode aSelectionMode);

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aPosition A position relative to the origin of the Text Listbox control.
     * @param aItemIndex Is set to the item at that position. 
     * @return Whether there was an item at aPosition.
     */
    IMPORT_C virtual TBool XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const;

    /**
     * The overriding implementation of CListBoxView's equivalent virtual function.
     *
     * @param aRect The rectangle.
     * @return The number of items that will fit into the given rectangle.
     */
    IMPORT_C virtual TInt NumberOfItemsThatFitInRect(const TRect& aRect) const;

private: //** Methods */
    IMPORT_C virtual TAny* Reserved_1();

private: //** Data */
    TAny* iSpareForFutureUse;
    };

/**
 * The <code>CEikSnakingTextListBox</code> class provides a horizontal snaking 
 * Text Listbox. This snaking Text Listbox is for displaying text. The snaking 
 * Text Listbox lays its items out using the <code>CEikSnakingListBox</code>
 * algorithms and uses a <code>CTextListItemDrawer</code> to draw its
 * items. This class is not intended for derivation.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CEikSnakingTextListBox : public CEikSnakingListBox
    {
public:
    //** Constructors and destructor */

    /**
     * The default object constructor.
     */
    IMPORT_C CEikSnakingTextListBox();

    /**
     * The object destructor.
     */
    IMPORT_C ~CEikSnakingTextListBox();

    //** New methods */

    /**
     * Completes construction of a <code>CEikSnakingTextListBox</code> object.
     *
     * @param aParent The parent control
     * @param aFlags The flags for the control
     * @remarks
     * @see CEikListBox::TFlags
     */
    IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aFlags = 0);

    /**
     * Gets a pointer to the model used by this Text Listbox.
     *
     * @return this Text Listbox's model
     * @remarks
     * @see 
     */
    IMPORT_C CTextListBoxModel* Model() const;

    // not available before Release 005u
    /**
     * Gets the list of logical colors used for drawing the control. This 
     * method is no longer used. Skin functionality manages the colors for 
     * this control.
     * 
     * @param aColorUseList Not used
     * @remarks
     * @see CCoeControl 
     */
    IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

    // not available before Release 005u
    /**
     * Handles a change to the control's resources that are shared across the 
     * environment.
     * 
     * @param aType A <code>TInt</code> message UID value for the resource 
     *              that has changed
     * @remarks
     * @see CCoeControl
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);
    };


#endif //** EIKTXLBX_H */

//** End of File */
