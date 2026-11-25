/*
* ==============================================================================
*  Name        : eiklbx.h
*  Part of     : CKON
*  Interface   : Listbox API
*  Description : Listbox control
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

#ifndef EIKLBX_H
#define EIKLBX_H


// INCLUDES
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
#include <eikubgcb.h>

// DATA TYPES

/** key code for special keys, defined in <code>TKeyCode</code> in e32keys.h */
enum TKeyCode;

/** one second: the time after which the incremental match buffer is reset */
const TInt KMatchTimeout = 1000000; 

// FORWARD DECLARATIONS
class RIncrMatcherBase;
class CListItemDrawer;
class CEikScrollBarFrame;
class CEikButtonBase;
class CMatchBuffer;
class CListBoxExt;
class CPopoutScroller;
class MCknMarginsObserver;
class CCoeBrushAndPenContext;

// CLASS DECLARATIONS

class CEikTextListBox;
class CEikChoiceListPopoutListBox;

/**
 * An internal class used on Series80 to put a "change" button in the CBA
 * when Yes/No is used to reflect the user's selection in text listboxes.
 * This should be in text list box source files but the only extension available
 * is in CEikListBox, can't change CEikTextListBox for BC reasons.
 */
class CCbaButtonHandler : public CBase, public MEikUpdatingBgContainerBase, public MCoeControlObserver
	{	
	friend class CEikTextListBox;

public:
	static CCbaButtonHandler* NewL();
	~CCbaButtonHandler();

private:
	CCbaButtonHandler();
	void ConstructL();

private: // from MEikUpdatingBgContainerBase
	virtual void HandleChangeButtonL();
	virtual TBool PopupDisplayed();

private:
	void SetTextListBox(CEikTextListBox* aTextListBox);
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
	
private:
	CEikChoiceListPopoutListBox* iPopoutListBox;
	TInt iCurrentItem;
	CDesCArray* iArray;
	CEikTextListBox* iTextListBox;
	};

/**
 * The <code>CEikListBox</code> class is the base class for an onscreen 
 * Listbox control from which one or more items can be selected.
 * <code>CEikListBox</code> implements the basics of a Listbox. It has a
 * scrollbar frame, an item drawer, and a model, and reports events to a
 * Listbox observer. Listboxes display a number of items within a
 * scrolling frame. The items in a Listbox that are visible at one time
 * are represented by a Listbox view. This class may be used by derived 
 * classes to extend the basic Listbox behavior.
 * When deriving from <code>CEikListBox</code> it is usual also to
 * extend <code>CListItemDrawer</code> and <code>CListBoxView</code>
 * in order to provide a representation of the data specific to the extended 
 * Listbox.
 * The Listbox class comes with methods for editing Listbox items while
 * the Listbox is active, via a text editor. The two main methods for editing
 * are <code>EditItemL()</code> and <code>StopEditingL()</code>, which start and
 * stop editing respectively. Both of these methods report an event to a 
 * Listbox observer when editing starts and stops.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CEikListBox : public CEikBorderedControl, public MEikScrollBarObserver
    {
    public:  // Declarations
    friend class CListBoxExt;
    /** 
     * The <code>TFlags</code> contains flags describing the properties of the 
     * Listbox. 
     */
    enum TFlags
        {
        /** the user can select more than one item from this Listbox */
        EMultipleSelection          = SLafListBox::EMultipleSelection,
        /** if set, extended selection using the SHIFT key is not possible */
        ENoExtendedSelection        = SLafListBox::ENoExtendedSelection, 
        /** 
         * the Listbox matches user's keystrokes incrementally. This feature 
         * allows the user to select an item by pressing keys in an order that 
         * corresponds with the text in the item 
         */
        EIncrementalMatching        = SLafListBox::EIncrementalMatching,
        /** 
         * the Listbox is a pop-out Listbox that floats over the dialog or 
         * application area. Pop-out Listboxes handle certain keystrokes and 
         * events differently 
         */
        EPopout                     = SLafListBox::EPopout,
        /** 
         * if set, indicates the pointer being pressed inside the view 
         * rectangle of the Listbox 
         */
        ELeftDownInViewRect         = SLafListBox::ELeftDownInViewRect,
        /** 
         * if set, indicates that the <code>CEikListBox</code> item was 
         * double tapped 
         */
        EItemDoubleClicked          = SLafListBox::EItemDoubleClicked,
        /** 
         * enables the automatic switching in and out mark mode for multiple 
         * selection
         */
        EEnableAutoMarkMode             = 0x8000,
        /** 
         * if set, the <code>CEikListBox</code> does not take ownership of the
         * supplied Listbox model, and does not delete it on its destruction 
         */
        EKeepModel                  = SLafListBox::EKeepModel,
        /** 
         * if set, the scrollbar is drawn outside the window describing the 
         * extent of the scroll box 
         */
        EScrollBarSizeExcluded      = SLafListBox::EScrollBarSizeExcluded,
        /** if set, indicates that the <code>CEikListBox</code> has changed */
        EStateChanged               = SLafListBox::EStateChanged,
        /** the Listbox should create its own window */
        ECreateOwnWindow            = SLafListBox::ECreateOwnWindow,
        /** the Listbox does not permit any key press matching */
        ENoFirstLetterMatching      = SLafListBox::ENoFirstLetterMatching,
        /** this mode enables the user to select multiple contiguous items */
        EPaintedSelection           = SLafListBox::EPaintedSelection,
        /** 
         * when set, the highlight is hidden until the next pointer event, or 
         * consumed key event 
         */
        EHiddenHighlight            = SLafListBox::EHiddenHighlight,
        /** 
         * in this mode, a Listbox shows the selected item only when the Listbox 
         * is focused. When not focused, in this mode, a Listbox displays the 
         * selected item using a passive focus rectangle (a rectangle that is 
         * not filled) 
         * @since Series 90 1.0
         */
        EDrawOnlyActiveSelection    = 0x2000,
        /** 
         * indicates whether the incremental match buffer is reset after a 
         * period of time
         * @since Series 90 1.0
         */
        EIncrementalMatchingTimeout = 0x4000,
		/**
		 * when set, infoprints concerning mark mode and items selected will
		 * not be displayed.
		 * @since Series 90 1.0
		 */
		ENoVerboseOnMarkMode = 0x10000,
		/**
		 * when set, the listbox will not override the usage of CBA buttons
		 * Applies to textlist box only
		 * @since Series 90 1.1 
		 */
		ENoCBAButtonOverride = 0x20000
        };
    /** This anonymous enumeration provides constants for use by Listbox. */
    enum
        {
        /** the maximum length of the incremental match buffer */
        KEikMaxMatchingBufferLength=22,
        /** the maximum length of the incremental match buffer */
        EEikMaxMatchingBufferLength=22
        };  

    protected:  // Declarations
    enum TProtectedFlags
        {
        EShowPartiallyVisibleItems  = 0x80000000,
        ESmoothVerticalScrolling    = 0x40000000
        };
    enum TReasonForFocusLost
        { EFocusLostToExternalControl, EFocusLostToInternalEditor };


    public:
    // Constructors and destructor
        /**
        * The object destructor.
        */
        IMPORT_C ~CEikListBox();
        
        /**
        * The default object constructor.
        */
        IMPORT_C CEikListBox();

    // New methods
        /**
         * Completes construction of a Listbox object, initializing
         * its heap-stored members with the information provided by the
         * arguments. 
         *
         * @param aListBoxModel The Listbox model representing the data to be
         *                      displayed. Must not be <code>NULL</code>
         * @param aListItemDrawer A drawer for the list items. 
         *        Must not be <code>NULL</code>
         * @param aParent The parent control. May be <code>NULL</code>
         * @param aFlags An OR'ed combination of <code>TFlags</code>
         * @remarks If <code>aParent</code> is <code>NULL</code>, the Listbox 
         *          is created as a window-owning control. This is 
         *          discouraged as it taxes run-time resources
         * @see TFlags
         */
        IMPORT_C void ConstructL(MListBoxModel* aListBoxModel,CListItemDrawer* aListItemDrawer,const CCoeControl* aParent,TInt aFlags = 0);

        /**
         * Completes construction of a Listbox object with a border, initializing
         * its heap-stored members with the information provided by the
         * arguments. The protected form is overridden non-virtually by the
         * second-phase constructors of each derived class and should be invoked 
         * by them using <code>CEikListBox::ConstructL()</code>.
         *
         * @param aListBoxModel The Listbox model representing the data to be
         *                      displayed. Must not be <code>NULL</code>
         * @param aListItemDrawer A drawer for the list items. 
         *        Must not be <code>NULL</code>
         * @param aParent The parent control. May be <code>NULL</code>
         * @param aBorder A specified border style defined by enumeration 
         *        <code>TBorder</code> in gulbordr.h
         * @param aFlags An OR'ed combination of <code>TFlags</code> 
         * @remarks If <code>aParent</code> is <code>NULL</code>, the Listbox 
         *          is created as a window-owning control. This is 
         *          discouraged as it taxes run-time resources
         * @see TFlags
         */
        IMPORT_C void ConstructL(MListBoxModel* aListBoxModel,CListItemDrawer* aListItemDrawer,const CCoeControl* aParent, TGulBorder aBorder, TInt aFlags = 0);

        /**
        * Handles key events offered to the control by the control environment.
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this control. 
        *         <code>EKeyWasConsumed</code> if the control takes action on the 
        *         key event; <code>EKeyWasNotConsumed</code> otherwise
        * @remarks
        * @see <code>CCoeControl</code>
         */
        IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
         * Handles pointer events offered to the control by the control 
         * environment when the current FEP is pointer-based.
         * This method gets called whenever a pointer event occurs in the control, 
         * that is, when the pointer is within the control's extent, or when 
         * the control has grabbed the pointer.
         *
         * @param aPointerEvent The pointer event
         * @remarks
         * @see CCoeControl in coecntrl.h
         */
        IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
         * Sets the container for this Listbox.
         * This method enables drag events and pointer grab, that is, all 
         * pointer events after a pen-down event are sent to this window.
         * If the <code>ECreateOwnWindow</code> or <code>EPopout</code>
         * flags are set, a window is first created for this control and this 
         * control becomes a window-owning control. Otherwise, the control is a 
         * component of the <code>aContainer</code> container control.
         * Enabling pointer grab means that any pen-down event in this window 
         * causes a pointer grab. This is terminated by the next corresponding 
         * pen-up event. All pointer events up to and including the next pen-up 
         * event are then sent to this window. Pointer grab is typically used 
         * for drag-and-drop or other situations when the events should be 
         * delivered to the same window even though the pen may be dragged
         * outside that window. Pop-out Listboxes have backup set on them, 
         * which means that whenever the window is activated or made
         * visible, the window server makes a backup of the screen 
         * contents that are overlaid by this window. Thus, the backed-up 
         * window can be restored rather than be redrawn and so is less of a 
         * drain on resources. 
         *
         * @param aContainer A compound control to set as this Listbox's 
         *                   container
         * @remarks 
         * @see
         */
        IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aContainer);

        /**
         * Gets the smallest area in which this Listbox can be 
         * displayed in its entirety.
         *
         * @return the smallest area in which this Listbox can be
         *         displayed in its entirety
         * @remarks The minimum size is dictated by the cell size and any 
         *          margins and borders that are set. For <code>CEikListBox</code>
         *          the minimum cell size is zero. Any inheriting control must 
         *          take into account the data that is stored, for example, 
         *          <code>CEikTextListBox</code> needs to work out how
         *          much space is required to draw the text in each cell using
         *          the current font
         * @see
         */
        IMPORT_C virtual TSize MinimumSize();

        /**
         * Sets the Listbox dim state.
         *
         * @param aDimmed <code>ETrue</code> to dim the Listbox; 
         *                <code>EFalse</code> to undim
         * @remarks
         * @see
         */
        IMPORT_C virtual void SetDimmed(TBool aDimmed);

        /**
         * Handles scrollbar events.
         * This method is called by this Listbox's scrollbars.
         *
         * @param aScrollBar The scrollbar on which the event occurred
         * @param aEventType The type of event
         * @remarks The scroll event type is one of the <code>TEikScrollEvent</code>
         *          values
         * @see TEikScrollEvent in eiksbobs.h
         */
        IMPORT_C virtual void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType);

        /**
         * The callback method from the <code>CPopoutScroller</code> class.
         * This method is called when a pointer event happens to the pop-out 
         * scroller and a scroll event is generated.
         * The pop-out scroller provides vertical arrowhead controls for
         * scrolling in pop-out Listboxes. Tapping on these generates either
         * a scroll-up or scroll-down event.
         *
         * @param aEventType The type of scroll event
         * @remarks The scroll event type is one of the <code>TEikScrollEvent</code>
         *          values
         * @see TEikScrollEvent in eiksbobs.h
         */
        void HandlePopoutScrollEventL(TEikScrollEvent aEventType);

        /**
         * Gets a pointer to the Listbox model.
         *
         * @return the Listbox model used by this Listbox
         * @remarks
         * @see
         */
        IMPORT_C MListBoxModel* Model() const;

        /**
         * Gets a pointer to the Listbox view.
         *
         * @return the Listbox view used by this Listbox
         * @remarks
         * @see
         */
        IMPORT_C CListBoxView* View() const;

        /**
         * Gets the index number of the item at the top of the view.
         *
         * @return the index of the item at the top of the view
         * @remarks The index of the top item may not necessarily be zero 
         *          since it refers to the index of the item currently  
         *          displayed at the top of the list. For example if the list 
         *          is scrolled part of the way down, the top index may be 3
         * @see
         */
        IMPORT_C TInt TopItemIndex() const;  

        /**
         * Sets which item is displayed at the top of the view.
         * The view updates the Listbox and the scrollbar to reflect the
         * change.
         *
         * @param aItemIndex The index of the item to display at the top
         * @remarks 
         * @see
         */
        IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex) const;

        /**
         * Gets the index number of the item at the bottom of the view.
         *
         * @return the index number of the item displayed at the bottom of
         *         the view
         * @remarks
         * @see        
         */
        IMPORT_C TInt BottomItemIndex() const;

        /**
         * Gets the index number of the currently selected item in the view.
         *
         * @return the index number of the currently selected item
         * @remarks If there is no selected item, the method returns -1
         * @see
         */
        IMPORT_C TInt CurrentItemIndex() const;   

        /**
         * Sets the current item, but does not redraw the list.
         * If the item was not previously visible, it is set to the top item in 
         * the view.
         *
         * @param aItemIndex The index of the item to make current
         * @remarks
         * @see
         */
        IMPORT_C void SetCurrentItemIndex(TInt aItemIndex) const;

        /**
         * Sets the currently selected item to <code>aItemIndex</code> and 
         * redraws the list. The Listbox view is scrolled so that the new 
         * current item is visible. If the item was not previously visible, it 
         * is set to the top item in the view.
         *
         * @param aItemIndex The index of the item to make current
         * @remarks
         * @see
         */
        IMPORT_C void SetCurrentItemIndexAndDraw(TInt aItemIndex) const;

        /**
         * Temporarily hides the selected item's highlight (by turning the 
         * emphasis off). Hiding the highlight clears any current selection.
         * The highlight is hidden until any pointer event, or consumed key 
         * event occurs. On a key event, the highlight is reinstated at the 
         * top of the current page. That is, there is no automatic scrolling.
         *
         * @param aHide <code>ETrue</code> to hide the highlight - any selection 
         *              will be cleared if a painted selection is used;
         *              <code>EFalse</code> to unhide the highlight - will have 
         *              no visible effect if a painted selection is used
         * @param aDraw If <code>EDrawNow</code>, a redraw is performed
         *              immediately
         * @since App-Framework_7.0
         * @public
         * @remarks
         * @see
         */
        IMPORT_C void HideHighlight(TBool aHide, TDrawNow aDraw);

        /**
         * Determines whether the highlight is currently hidden or not.
         *
         * @return <code>ETrue</code> if the highlight is hidden; otherwise 
         *         <code>EFalse</code>
         * @since App-Framework_7.0
         * @public
         * @remarks
         * @see
         */
        IMPORT_C TBool HighlightIsHidden() const;

        /**
         * Gets the items that are currently selected.
         * The entries in the array hold the indices of the items
         * in the Listbox that are currently selected.
         *
         * @return the items that are currently selected
         * @remarks
         * @see
         */
        IMPORT_C const CListBoxView::CSelectionIndexArray* SelectionIndexes() const;

        /**
         * Sets a new list of items as selected.
         * The entries in the array hold the indices of the items
         * in the Listbox that will become the new selection.
         *
         * @param aArrayOfSelectionIndexes The new list of selected items
         * @remarks
         * @see
         */
        IMPORT_C void SetSelectionIndexesL(CListBoxView::CSelectionIndexArray* aArrayOfSelectionIndexes);

        /**
         * Clears the current selection.
         * This method resets the selection indexes so that there are no 
         * selected items. This only has an effect if multiple item selection
         * is enabled.
         *
         * @remarks
         * @see
         */
        IMPORT_C void ClearSelection(); 

        /**
         * This method should be called after one or more new items have been 
         * added to the Listbox model. Unlike <code>HandleItemRemoval()</code>,
         * below, this method redraws the Listbox, ensuring that any currently 
         * selected item is visible.
         * 
         * @remarks
         * @see
         */
        IMPORT_C void HandleItemAdditionL();

        /**
         * Handles the removal of an item from the model. This method should be 
         * called after one or more items have been 
         * removed from the model. It is then up to the application to make 
         * sure that the current item index is set to an appropriate value and 
         * to redraw the Listbox.
         * 
         * @remarks
         * @see
         */
        IMPORT_C void HandleItemRemovalL();

        /**
         * Resets the indices and clears the current selection, the top item, and the 
         * horizontal scroll offset of this Listbox. Sets the current item index
         * to zero. This method does not redraw the Listbox.
         *
         * @remarks
         * @see
         */
        IMPORT_C void Reset();

        /**
         * Sets the required height of the Listbox according to the 
         * number of items to be displayed.
         *
         * @param aNumOfItems The number of Listbox entry items to be displayed
         * @remarks
         * @see
         */
        IMPORT_C void SetRequiredHeightInNumOfItems(TInt aNumOfItems);

        /**
         * Sets the item height.
         *
         * @param aHeight The new height for all items, in pixels
         * @remarks All items will be the same height
         * @see
         */
        IMPORT_C virtual void SetItemHeightL(TInt aHeight);

        /**
         * Sets the height of the item at <code>aItemIndex</code>. This 
         * Listbox must have been explicitly set to allow items of variable 
         * height via the method <code>CListBoxView.AllowVariableHeightItems()</code>.
         *
         * @since App-Framework_6.2
         * @public
         * @remarks
         * @see <code>CListBoxView</code> for setting variable height items
         */
        IMPORT_C void SetItemHeightL(TInt aItemIndex, TInt aItemHeight);

        /**
         * Sets the height of the item at <code>aItemIndex</code> to the 
         * Listbox's default item height. The default height is the height
         * of standard Listbox items. This method only affects Listbox items
         * that have had a variable height set.
         *
         * @since App-Framework_6.2
         * @public
         * @remarks
         * @see
         */
        IMPORT_C void SetToDefaultItemHeight(TInt aItemIndex);

        /**
         * Gets the item height in pixels.
         *
         * @return the height of each item in the list, in pixels 
         * @remarks
         * @see
         */
        IMPORT_C TInt ItemHeight() const;

        /**
         * Returns the height of a specified item.
         *
         * @param aItemIndex The index of the item whose height has been 
         *                   requested
         * @return the height of the item
         * @since App-Framework_6.2
         * @remarks
         * @see
         */
        IMPORT_C TInt ItemHeight(TInt aItemIndex) const;

        /**
         * Creates a scrollbar frame.
         *
         * @param aPreAlloc <code>EFalse</code> to not pre-allocate scrollbars;
         *                  <code>ETrue</code> to pre-allocate scrollbars
         * @return the newly created scrollbar frame
         * @remarks <code>aPreAlloc</code> determines whether to allocate
         *          scrollbars immediately. This is useful if the control 
         *          being scrolled can change size while the scrollbar is 
         *          displayed
         * @see
         */
        IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL(TBool aPreAlloc=EFalse);

        /**
         * Gets a pointer to the scrollbar frame.
         *
         * @return the pointer to the scrollbar frame
         * @remarks
         * @see
         */
        IMPORT_C CEikScrollBarFrame* const ScrollBarFrame();

        /**
         * Updates the size, span, and thumb position of this Listbox's 
         * scrollbars.
         *
         * @remarks Called after any size changes to the Listbox or any keyboard
         *          activity
         * @see
         */
        IMPORT_C void UpdateScrollBarsL();

        /**
         * Gets the size of the rectangle required to display a pop-out Listbox.
         *
         * @param aTargetItemIndex 
         * @param aTargetItemIndex The item from which the pop-out Listbox 
         *                         originates
         * @param aTargetYPos The vertical position of the item from which the 
         *                    pop-out Listbox originates
         * @param aListBoxRect The Listbox rectangle
         * @param aMinHeightInNumOfItems The minimum number of items for the 
         *                               pop-out Listbox
         * @remarks Examples of pop-out Listboxes include those from the
         *          <code>CEikChoicelist</code> and <code>CEikComboBox</code> 
         *          controls
         * @see
         */
        IMPORT_C void CalculatePopoutRect(TInt aTargetItemIndex, TInt aTargetYPos, TRect& aListBoxRect, TInt aMinHeightInNumOfItems = 1);

        /**
         * Gets the size of the Listbox, in pixels, based on the height of the
         * Listbox, in items.
         *
         * @param aWidthAsNumOfChars The width of the Listbox, in characters
         * @param aHeightAsNumOfItems The height of the Listbox, in characters
         * @return a two dimensional size as a width and a height value, in 
         *         pixels
         * @remarks
         * @see
         */
        IMPORT_C TSize CalcSizeInPixels(TInt aWidthAsNumOfChars, TInt aHeightAsNumOfItems) const;

        /**
         * Gets the width of the Listbox, in pixels, based on the width of the
         * Listbox, in characters.
         *
         * @param aNumOfChars The width of the Listbox, in characters
         * @return the width of the Listbox, in pixels
         * @remarks
         * @see
         */
        IMPORT_C TInt CalcWidthBasedOnNumOfChars(TInt aNumOfChars) const;

        /**
         * Gets the height of the Listbox based on the number of Listbox items.
         * The height returned includes the Listbox margins, border and, if
         * present, the scrollbar frame.
         *
         * @param aNumOfItems The number of Listbox items
         * @return the height of the Listbox, in pixels
         * @remarks
         * @see
         */
        IMPORT_C TInt CalcHeightBasedOnNumOfItems(TInt aNumOfItems) const;

        /**
         * Gets the width of the Listbox, in pixels, based on the width of the
         * Listbox text, in pixels.
         *
         * @param aTextWidthInPixels The width of the Listbox text, in pixels
         * @return the required width of the whole Listbox, in pixels
         * @remarks
         * @see
         */
        IMPORT_C TInt CalcWidthBasedOnRequiredItemWidth(TInt aTextWidthInPixels) const;

        /**
         * Draws a Listbox item. First, the list scrolls to make the item 
         * visible, if it is not already. This method panics if there is no 
         * Listbox view currently set.
         *
         * @param aItemIndex The index of the item to reveal
         * @remarks If there is no Listbox view, the panic raised is 
         *          <code>EEikPanicListBoxNoView</code>
         * @see
         */
        IMPORT_C void DrawItem(TInt aItemIndex) const;

        /**
         * Makes an item visible in the list, scrolling it if necessary.
         *
         * @param aItemIndex The index of the item to reveal
         * @remarks
         * @see
         */
        IMPORT_C void ScrollToMakeItemVisible(TInt aItemIndex) const;

        /**
         * This method is a leaving variant of 
         * <code>CEikListBox::ScrollToMakeItemVisible</code> since scrolling 
         * can now result in an error.
         *
         * @param aItemIndex The index of the item to reveal
         * @since App-Framework_6.2
         * @remarks
         * @see
         */
        IMPORT_C void ScrollToMakeItemVisibleL(TInt aItemIndex) const;

        /**
         * Sets the Listbox observer. This observer receives future Listbox 
         * events from this Listbox.
         *
         * @param aObserver The Listbox observer to report Listbox events to
         * @remarks
         * @see MEikListBoxObserver in eiklbo.h
         */
        IMPORT_C void SetListBoxObserver(MEikListBoxObserver* aObserver);

        /**
         * Sets the Listbox margin observer. This observer receives an event 
         * when the margins change.
         *
         * @param aObserver The Listbox margin observer to report to, when the
         *                  Listbox's margins change
         * @remarks
         * @see MCknMarginsObserver in cknmarginsobserver.h
         */
        IMPORT_C void SetMarginsObserver(MCknMarginsObserver* aObserver);

        /**
         * Gets the size of the vertical gap between items.
         * This space is used by the view to allow a box to be drawn around 
         * each item.
         *
         * @return the size of the vertical gap, in pixels
         * @remarks
         * @see
         */
        IMPORT_C TInt VerticalInterItemGap() const;

        /**
         * Provides a callback mechanism to the button that just launched a
         * pop-out menu. When the Listbox is destroyed, it notifies
         * the launching button's <code>HandlePointerEventL()</code> with a 
         * <code>EButton1Up</code> event. 
         *
         * @param aButton The button that just launched a pop-out menu
         * @remarks
         * @see CEikButtonBase in eikbutb.h
         */
        IMPORT_C void SetLaunchingButton(CEikButtonBase* aButton);

        /**
         * Sets the item editor. Ownership of the item editor is transferred to
         * this class.
         *
         * @param aEditor The item editor
         * @remarks
         * @see MEikListBoxEditor in eiklbed.h
         */
        IMPORT_C void SetItemEditor(MEikListBoxEditor* aEditor);

        /**
         * Deletes and <code>NULL</code>s the item editor.
         * 
         * @remarks
         * @see
         */
        IMPORT_C void ResetItemEditor();

        /**
         * Gets a pointer to the item editor. Calling this method does not 
         * imply transfer of ownership.
         * The item editor is an interface to a text editor that can be used
         * to edit items inside a Listbox.
         *
         * @return a pointer to the item editor
         * @remarks
         * @see MEikListBoxEditor in eiklbed.h
         */
        IMPORT_C MEikListBoxEditor* ItemEditor();

        /**
         * Creates an item editor and starts editing the current Listbox item.
         * The editor can edit the current item up to a maximum length of
         * <code>aMaxLength</code> characters. By default, this method
         * also reports an <code>EEventEditingStarted</code> event to any 
         * Listbox observer. The method only creates a new editor if one
         * does not already exist.
         *
         * @param aMaxLength The maximum length of characters to edit
         * @remarks The developer of the Listbox class defines the calling of
         *          this method. Examples include a Listbox item being double 
         *          tapped
         * @see MEikListBoxObserver::EEventEditingStarted in eiklbo.h
         */
        IMPORT_C virtual void EditItemL(TInt aMaxLength);

        /**
         * Stops editing and deletes the item editor.
         * This method reports an <code>EEventEditingStopped</code> event to 
         * any Listbox observer and updates the Listbox model if
         * <code>aUpdateModel</code> is <code>ETrue</code>.
         *
         * @param aUpdateModel If <code>ETrue</code>, the Listbox model is 
         *                     updated; <code>EFalse</code> otherwise
         * @remarks This method is called on scroll events, pointer events that
         *          occur outside the item editor, and keyboard events that 
         *          are not used by the item editor, such as Enter and Escape
         * @see MEikListBoxObserver::EEventEditingStopped in eiklbo.h
         */
        IMPORT_C void StopEditingL(TBool aUpdateModel);

        /**
         * The <code>TDestroyInfo</code> class provides a singly linked list of cleanup 
         * information.
         */
    class TDestroyInfo
        {
    public:
        /**
         * The object constructor
         */
        TDestroyInfo() : iDestroyed(EFalse), iPtrDestroyed(NULL), iNext(NULL) { }
        /** indicates whether the object has been destroyed or not */
        TBool iDestroyed;
        /** a pointer to the reference of the destroyed <code>TDestroyInfo</code> */
        TDestroyInfo** iPtrDestroyed;
        /** a pointer to the next <code>TDestroyInfo</code> in the linked list */
        TDestroyInfo *iNext;
        };

       /**
        * Sets or clears the <code>ENoExtendedSelection</code> flag.
        * If set, performing extended selection using the SHIFT key is not 
        * possible.
        *
        * @param aNoExtendedSelection <code>ETrue</code> to set the flag; 
        *                             <code>EFalse</code> to clear it
        * @remarks
        * @see
        */
        IMPORT_C void SetNoExtendedSelection(TBool aNoExtendedSelection);

       /**
        * Pushes the specified <code>TDestroyInfo</code> onto the cleanup 
        * stack and adds it to the end of the list of <code>TDestroyInfo</code> 
        * objects.
        *
        * @remarks
        * @see TDestroyInfo in eiklbx.h
        */
        IMPORT_C void ReportDestroyedLC(TDestroyInfo &aDestroyedInfo);

       /**
        * Returns the Listbox's currently set flags.
        * These flags are enumerated in <code>CEikListBox::TFlags</code>.
        *
        * @return the flags
        * @remarks
        * @see CEikListBox::TFlags
        */
        inline TInt Flags() const {return iListBoxFlags;}

       /**
        * Handles a selection command, for example, to mark all items as 
        * selected.
        *
        * @param aCmd The command
        * @remarks The commands used are <code>EEikCmdMark</code>, 
        *          <code>EEikCmdUnmark</code>, <code>EEikCmdMarkAll</code>, 
        *          and <code>EEikCmdUnmarkAll</code>.
        *          <code>EEikCmdMark</code> and <code>EEikCmdUnmark</code>
        *          relate to the currently selected item
        * @see
        */
        IMPORT_C void CmdSelectL(TInt aCmd);

       /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

       /**
        * Handles a change to the Listbox's resources that are shared across 
        * the environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see CCoeControl
        * @since Release 005u
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);    

       /**
        * Returns the input capabilities of the Listbox as set through the 
        * Listbox flags.
        *
        * @return the input capabilities of the Listbox
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const; // not available before Release 006

       /**
        * Reports an event to the observer of this Listbox.
        *
        * @param aEvent The event type
        * @remarks The observer of the Listbox is set via the method 
        *          <code>CCoeControl::SetObserver()</code>
        * @see
        */
        IMPORT_C void ReportExternalEventL(MCoeControlObserver::TCoeEvent aEvent);

       /**
        * Activates this control.
        * 
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void ActivateL();

       /**
        * Returns the current setting for mark mode. Mark mode is used to select 
        * multiple items in a list.
        * 
        * @return <code>ETrue</code> if mark mode is currently active; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool MarkModeActive() const;

       /**
        * Sets mark mode active or inactive. Mark mode is used to select 
        * multiple items in a list.
        * 
        * @param aActive <code>ETrue</code> if mark mode is to be enabled;
        *        <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetMarkModeActive(TBool aActive);

        /**
        * Sets the text to display in a Listbox when there are no items in it.
        *
        * @param aEmptyText The text string to display
        * @remarks
        * @see
        */
        IMPORT_C void SetEmptyListTextL(const TDesC& aEmptyText);
/**
 * This function is for test code only.
 * @since App-Framework_6.2
 * @private
 * @internal
 */
        IMPORT_C void SetShowPartiallyVisibleItemsL(TBool aShowPartiallyVisibleItems);

/**
 * This function is for test code only.
 * @since App-Framework_6.2
 * @private
 * @internal
 */
        IMPORT_C TBool ShowPartiallyVisibleItems() const;

/**
 * This function is for test code only.
 * @since App-Framework_6.2
 * @private
 * @internal
 */
        IMPORT_C void SetSmoothVerticalScrollingL(TBool aSmoothVerticalScrolling);

/**
 * This function is for test code only. 
 * @since App-Framework_6.2
 * @private
 * @internal
 */
        IMPORT_C TBool SmoothVerticalScrolling() const;

        
    protected:  // Methods

    // New Methods
        
        /**
        * This function does nothing.
        * @param aWriteStream Not used
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

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

/**
 *
 * Responds to the size being changed.
 *
 * This function over-rides the <code>CCoeControl::SizeChanged()</code>
 * function.
 *
 */
        IMPORT_C virtual void SizeChanged();

/**
 *
 * Handles a change in size of the viewing rectangle.
 *
 * This function is called by framework functions to update the content,
 * view, and scrollbars of this Listbox after the viewing rectangle has
 * changed size. This implementation ensures that the current item is
 * visible after a resize.
 *
 */
        IMPORT_C virtual void HandleViewRectSizeChangeL();

/**
 *
 * Gets a count of the component controls of this Listbox control.
 *
 * This information is used for <code>DrawNow()</code>.
 *
 * @returns   " TInt "
 *            The number of component controls.
 */
        IMPORT_C virtual TInt CountComponentControls() const;

/**
 *
 * Gets a pointer to the specified component control.
 *
 * This is used for <code>DrawNow()</code>.
 *
 * @param     " TInt aIndex "
 *            Index of the component control to look up.
 * @returns   " CCoeControl* "
 *            The control at <code>aIndex</code>.
 */
        IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;

        /**
        * Utility function called from RestoreL() of subclasses such as CEikStandardListBox
        */
        IMPORT_C void CreateMatchBufferL();

        /**
        * Clears the match buffer.
        */
        IMPORT_C void ClearMatchBuffer() const;

/**
 *
 * Searches the match buffer for a match to a typed character.
 *
 * Displays the item corresponding to the typed character if a match is
 * found. No effect if no match is found.
 *
 * @param     " TUint aCode "
 *            The ID of the character to match.
 */
        IMPORT_C void MatchTypedCharL(TUint aCode);

/**
 *
 * Removes one character from the matcher buffer, then finds the first
 * item which matches the new buffer, if any.
 *
 * Redraws the Listbox to reflect the change. This should not be called
 * from within another <code>Draw()</code> function.
 *
 */
        IMPORT_C void UndoLastChar();

/**
 *
 * Updates the position of this Listboxs scrollbars thumbs to reflect
 * the horizontal and vertical position of the list view within the list.
 *
 */
        IMPORT_C void UpdateScrollBarThumbs() const;

/**
 *
 * Gets the granularity for horizontal scrolls.
 *
 * The granularity is the minimum size of a horizontal move of the client
 * area.
 *
 * @returns   " TInt "
 *            Grain size for horizontal scrolling in pixels.
 */
        IMPORT_C virtual TInt HorizScrollGranularityInPixels() const;

/**
 *
 * Gets the number of grains to move horizontally when a nudge button is
 * tapped.
 *
 * For simple Listboxes, this value is a fraction of the width of the
 * client area.
 *
 * @returns   " TInt "
 *            Number of grains to move left or right on each nudge.
 */
        IMPORT_C virtual TInt HorizontalNudgeValue() const;

/**
 *
 * Called by various functions of this class to ensure that the top item
 * index is always a sane value.
 *
 * The implementation in <code>CEikListBox</code> tries to ensure the
 * minimum amount of white space at the bottom of the Listbox. Note that
 * this function does not affect the current item index.
 *
 */
        IMPORT_C virtual void AdjustTopItemIndex() const;

/**
 *
 * Simulates an arrow key event.
 *
 * If the Listbox flags include <code>EMultipleSelection</code>, this
 * has the effect of pressing SHIFT with the arrow key represented by
 * <code>aKeyCode</code>. Calls
 * <code>CEikListBox::OfferKeyEventL()</code> with <code>aKeyCode</code>
 * translated into a key event.
 *
 * @param     " TKeyCode aKeyCode "
 *            A key code.
 */
        IMPORT_C void SimulateArrowKeyEventL(TKeyCode aKeyCode);

/**
 *
 * Handles left arrow keypresses.
 *
 * Moves the cursor into the correct column and clears any matcher buffer
 * that may have been built up.
 *
 * @param     "CListBoxView::TSelectionMode aSelectionMode"
 *            The current selection mode.
 */
        IMPORT_C virtual void HandleLeftArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);

/**
 *
 * Handles right arrow keypresses.
 *
 * Moves the cursor into the correct column and clears any matcher buffer
 * that may have been built up.
 *
 * @param     "CListBoxView::TSelectionMode aSelectionMode"
 *            The current selection mode.
 */
        IMPORT_C virtual void HandleRightArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);

/**
 *
 * Restores the Listbox properties shared by all subclasses from a
 * resource reader.
 *
 * This function is not called within <code>CEikListBox</code> itself,
 * but is used by subclasses which support construction from resources.
 *
 * @param     " TResourceReader& aReader "
 *            A resource reader.
 */
        IMPORT_C void RestoreCommonListBoxPropertiesL(TResourceReader& aReader); // utility function called from RestoreL() of subclasses such as CEikStandardListBox

/**
 *
 * Protected second-phase constructor.
 *
 * This protected form is overridden non-virtually by the second-phase
 * constructors of each subclass, and should be invoked by them using
 * <code>CEikListBox::ConstructL()</code>.
 *
 * @param     " const CCoeControl* aParent "
 *            The parent control. May be <code>NULL</code>.
 * @param     " TInt aFlags = 0 "
 *            An ORed combination of <code>TFlags</code> (below).
 */
        IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aFlags = 0);

/**
 *
 * Completes the Listbox views construction.
 *
 * This function is called by <code>ConstructL()</code> to complete
 * construction of the resource view, calling its
 * <code>ConstructL()</code> with appropriate arguments and assigning it
 * to <code>iView</code>. Also prepares the view for use.
 *
 */
        IMPORT_C virtual void CreateViewL();

/**
 *
 * Creates the Listbox view.
 *
 * The function is called by <code>ConstructL()</code> to create an
 * instance of the appropriate Listbox view class for this Listbox. The
 * returned instance is owned by this object, and does not have to have
 * its second-phase constructor run. This function is called by
 * <code>CreateViewL()</code>.
 *
 * @returns   " CListBoxView* "
 *            Pointer to a newly constructed Listbox view for this
 *            object.
 */
        IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();

/**
 *
 * Sets the view rectangle from the client rectangle making sure a whole
 * number of items is displayed. The rectangle is got by calling ClientRect().
 *
 */
        IMPORT_C void SetViewRectFromClientRect();

/**
 *
 * Sets the view rectangle from the client rectangle making sure a whole
 * number of items is displayed.
 *
 * @param     " const TRect& aClientRect "
 *            The client rectangle.
 */
        IMPORT_C void SetViewRectFromClientRect(const TRect& aClientRect);

/**
 *
 * Calculates the client area.
 *
 * This method is called by various functions of this class to
 * recalculate the extent of the client area from <code>iViewRect</code>.
 * This implementation takes into account any rounding of the viewing
 * rectangle made to fit a whole number of items.
 *
 * @param     " TRect& aClientRect "
 *            On return contains a size for the client area in
 *            pixels.
 */
        IMPORT_C virtual void RestoreClientRectFromViewRect(TRect& aClientRect) const;

/**
 *
 * Rounds down the height of the rectangle (if necessary) so that only a
 * whole number of items can be displayed inside the Listbox.
 *
 * @param     " TRect& aRect "
 *            The rectangle to be modified.
 * @returns   " TInt "
 *            The number of pixels reduced.
 */
        IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const;

/**
 *
 * Gets Listbox margins.
 * A method which returns a TMargins object for the Listbox.
 * The TMargins object has 4 values, one for each side of the Listbox.
 * Depending on use of the Laf, the DFRD can program 2, 3 or 4 margins ...
 * ... and although the application developer can see up to 4 different margins ...
 * ... they can still set 2 (ie. iHorizontalMargin and iVerticalMargin) if they wish
 * ... though this backwards compatability is marked as deprecated.
 *
 * @returns   " TMargins8 "
 *            The Listbox margins in pixels.
 */
        IMPORT_C TMargins8 ListBoxMargins() const;

/**
 *
 * @deprecated
 *
 * This function gets the horizontal margin. Use
 * <code>CEikListBox::ListBoxMargins()</code> instead, as this provides a
 * more accurate value due to the bit shifting involved.
 *
 * @returns   " TInt "
 *            The horizontal margin in pixels.
 */
        IMPORT_C TInt HorizontalMargin() const;

/**
 *
 * @deprecated
 *
 * This function gets the vertical margin. This function is deprecated,
 * use <code>CEikListBox::ListBoxMargins()</code> instead, this provides
 * a more accurate value due to the bit shifting involved.
 *
 * @returns   " TInt "
 *            The vertical margin in pixels.
 */
        IMPORT_C TInt VerticalMargin() const;

/**
 *
 * Sets the horizontal margin.
 *
 * @param     " TInt aMargin "
 *            The required horizontal margin.
 */
        IMPORT_C void SetHorizontalMargin(TInt aMargin);

/**
 *
 * Sets the vertical margin to <code>aMargin</code>.
 *
 * @param     " TInt aMargin "
 *            The required vertical margin.
 */
        IMPORT_C void SetVerticalMargin(TInt aMargin);

/**
 *
 * Gets a pointer to the match buffer.
 *
 * Returns <code>NULL</code> if the match buffer does not exist.
 *
 * @returns   " RIncrMatcherBase* "
 *            Pointer to the match buffer.
 */
        IMPORT_C RIncrMatcherBase* MatchBuffer() const;

/**
 *
 * Gets the view rectangle height adjustment.
 *
 * These are the adjustments that were made to the view rectangle when
 * the <code>SetViewRectFromClientRect()</code> function was called.
 *
 * @returns   " TInt "
 *            Height adjustment.
 */
        IMPORT_C TInt ViewRectHeightAdjustment() const;

/**
 *
 * Gets the background colour.
 *
 * @returns   " TRgb "
 *            The background colour.
 */
        IMPORT_C TRgb BackColor() const;

/**
 *
 * Reports a Listbox event to any observer of this Listbox.
 *
 * This function returns immediately if no observer is set.
 *
 * @param     " MEikListBoxObserver::TListBoxEvent aEvent "
 *            The event to report.
 */
        IMPORT_C virtual void ReportListBoxEventL(MEikListBoxObserver::TListBoxEvent aEvent);

/**
 *
 * Redraws the specified area of this Listbox into the specified
 * rectangle.
 *
 * @param     " const TRect& aRect "
 *            Rectangle to be redrawn, specified relative to the
 *            origin of this control.
 */
        IMPORT_C virtual void Draw(const TRect& aRect) const;

        /**
        * Clears the margins, provided redraw has not been disabled and the item drawer
        * has a graphics context.
        */
        IMPORT_C void ClearMargins() const;

/**
 *
 * Sets an item as the current item, even if it is not currently visible.
 *
 * Redraws the Listbox to reflect the change. This should not be called
 * from within another <code>Draw</code> function.
 *
 * @param     " TInt aItemIndex "
 *            The index of the Listbox item to update.
 */
        IMPORT_C virtual void UpdateCurrentItem(TInt aItemIndex) const;

/**
 *
 * Handles drag events.
 *
 * This function is called by <code>HandlePointerEventL()</code> to
 * handle pointer drag events appropriately.
 *
 * @param     " TPoint aPointerPos "
 *            The position of the <code>TPointerEvent</code> for
 *            which this handler is invoked.
 */
        IMPORT_C virtual void HandleDragEventL(TPoint aPointerPos);

/**
 *
 * Tests whether an item exists.
 *
 * @param     " TInt aItemIndex "
 *            Index to test.
 * @returns   " TBool "
 *            <code>ETrue</code> if the specified item exists,
 *            <code>EFalse</code> otherwise.
 */
        IMPORT_C TBool ItemExists(TInt aItemIndex) const;

/**
 *
 * Draws the matcher cursor in the correct location for the current
 * match.
 *
 * If there is no match buffer, this function returns immediately;
 * otherwise the cursor is drawn on the current item using
 * <code>CListBoxView::DrawMatcherCursor()</code> after scrolling to make
 * the current item visible.A Listbox controls matcher cursor is an
 * on-screen cursor which is drawn to indicate to the user the location
 * of the current text. Whether the cursor is drawn is dependent on the
 * <code>CListBoxView::TFlags::EHasMatcherCursor</code> flag, which may
 * be set on the Listboxs view.
 *
 */
        IMPORT_C void DrawMatcherCursor() const;

/**
 *
 * Gets the vertical gap between elements in the Listbox.
 *
 * @returns   " TInt "
 *            The vertical gap between elements in the Listbox.
 */
        IMPORT_C static TInt InterItemGap();

/**
 *
 * Updates the view colours in line with the colours in effect for the
 * Uikon environment.
 *
 * Has no effect if there is no view.
 *
 */
        IMPORT_C void UpdateViewColors();

/**
 *
 * Updates the item drawer colours in line with the colours in effect for
 * the Uikon environment.
 *
 * Has no effect if there is no item drawer.
 *
 */
        IMPORT_C void UpdateItemDrawerColors();

/**
 *
 * Sets the reason for the Listboxs loss of focus.
 *
 * This is required so the Listbox can determine whether loss of focus
 * is due to an external control or an internal component.
 *
 * @returns   " TReasonForFocusLost aReasonForFocusLost "
 *            The reason for the loss of focus.
 */
        IMPORT_C void SetReasonForFocusLostL(TReasonForFocusLost aReasonForFocusLost);

/**
 *
 * Returns the reason for the focus being transferred from the Listbox.  Either it is lost to an internal
 * editor, or it is lost to another control which is external to it.  Called from FocusChanged()
 * in order to close an Listbox editor in response to external controls taking focus.  Obviously the list
 * box editor should not be closed if focus has been transferred to it.
 *
 * @returns   " TReasonForFocusLost "
 *            The reason for the loss of focus.
 */
        IMPORT_C TReasonForFocusLost ReasonForFocusLostL();

        TBool IsMatchBuffer() const;
        void CheckCreateExtensionL();
        TBool CheckCreateExtension();
        void CheckCreateBufferL();
        CMatchBuffer* Buffer() const;
        TKeyResponse PreProcessKeyEventL(TKeyEvent& aKeyEvent,TEventCode aType);
        TKeyResponse DoSeries90OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        TKeyResponse DoSeries80OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

	protected:
		CCbaButtonHandler* GetCBAButtonHandlerL();
		CCbaButtonHandler* GetCBAButtonHandler();

    private: //Methods
        IMPORT_C void Reserved_2();
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
        TBool AdjustVerticalMarginsForScrollArrows();
        void ChangeViewRect();
        void MoveCursorL(CListBoxView::TCursorMovement aCursorMovement, CListBoxView::TSelectionMode aSelectionMode);
        TBool Series90ModeActive() const;
        void SetMarkModeWithVerbose(TBool aActive, TBool aVerbose=ETrue);

    protected:     // Data
        TUint iListBoxFlags;
        CListBoxView* iView;
        CListItemDrawer* iItemDrawer;
        MListBoxModel* iModel;
        TInt iItemHeight;   
        CEikScrollBarFrame* iSBFrame;
        TInt iRequiredHeightInNumOfItems;
        CEikButtonBase* iLaunchingButton; // only used by popouts
        MEikListBoxObserver* iListBoxObserver;

    private:     // Data
        TRgb iBackColor;
        TMargins8 iMargins;
        CListBoxExt* iListBoxExt;
        TInt iViewRectHeightAdjustment;
        MEikListBoxEditor* iItemEditor;
        TDestroyInfo* iDestroyedInfo;
    };

/**
 * This class is only for use within EIKCOCTL.DLL.
 *
 * @internal
 * @since App-Framework_6.2
 * @private
 */
class CListBoxExt : public CBase, public MListVisibilityObserver, public MEikListBoxViewObserver
    {
    private:  // Declarations
    enum
        {
        EUpdateScrollBarsColors =0x1,
        EMarkModeActive=0x2,
        };

    public:
    // Constructors and destructor

        /**
        * Static constructor.
        */
        static CListBoxExt* New(CEikListBox& aListBox); // does not leave, returns NULL if failed

        /**
        * Destructor.
        */
        ~CListBoxExt();

        CListBoxExt(CEikListBox& aListBox);
        
    // New methods
        void CreateMatchBufferL();
        void CheckCreateBufferL();
		void CheckCreateCBAHandlerL();
        CMatchBuffer* Buffer() const;
        TBool IsMatchBuffer() const;
        void SetReasonForFocusLost(CEikListBox::TReasonForFocusLost aReasonForFocusLost);
        CEikListBox::TReasonForFocusLost ReasonForFocusLost() const;
		CCbaButtonHandler* GetCbaButtonHandlerL();
		CCbaButtonHandler* GetCbaButtonHandler();
    
        /**
        * Sets the editor for this Listbox
        * @param     aEditorComponentControl   Pointer to the new editor control.
        * <BR><B>Type of return value:</B> void
        */
        inline void SetEditorComponentControl(CCoeControl* aEditorComponentControl) {iEditorComponentControl=aEditorComponentControl;}

        /**
        * Gets the editor for this Listbox
        * @return Pointer to the editor control.
        * <BR><B>Type of return value:</B> CCoeControl*
        */
        inline CCoeControl* EditorComponentControl() const {return iEditorComponentControl;}

        void CreateMatchTimerL();
        void ResetMatchTimer();
        void CreateBrushAndPenContextL();
        CCoeBrushAndPenContext* BrushAndPenContext();

        /**
        * Gets the CPopoutScroller for this Listbox.
        * @return Pointer to the CPopoutScroller.
        * <BR><B>Type of return value:</B> CPopoutScroller*
        */
        inline CPopoutScroller* PopoutScroller() {return iPopoutScroller;}

        /**
        * Sets the CPopoutScroller for this Listbox.
        * @param     aScroller   Pointer to the new CPopoutScroller control.
        * <BR><B>Type of return value:</B> void
        */
        inline void SetPopoutScroller(CPopoutScroller *aScroller) {iPopoutScroller=aScroller;}

        // from MListVisibilityObserver
        TBool IsVisible() const;
        void SetUpdateScrollBarsColors(TBool aUpdate);
        TBool UpdateScrollBarsColors() const;
        void SetMarkModeActive(TBool aActive);
        TBool MarkModeActive() const;
        // from MEikListBoxViewObserver
        void HandleListBoxViewEventL(CListBoxView* aListBoxView, TListBoxViewEvent aEventType);

    private: //Methods
        static TInt TimerCallBackL(TAny* aSelf);
        void HandleMatchTimeout();

    public:     // Data
        MCknMarginsObserver* iMarginsObserver;

    private:     // Data
        CMatchBuffer* iBuffer;
        CEikListBox& iListBox;
    CEikListBox::TReasonForFocusLost iReasonForFocusLost;
        TInt iFlags;
        CCoeControl* iEditorComponentControl;
        CPeriodic* iTimer;          //< Timer for incremental matching with timeout.
        CCoeBrushAndPenContext* iBrushAndPenContext;
        CPopoutScroller* iPopoutScroller; 
		CCbaButtonHandler* iCBAButtonHandler;
    };

/**
 * The <code>CEikSnakingListBox</code> class provides a Snaking Listbox.
 * This is a Listbox that scrolls horizontally, displaying its items in
 * as many vertical columns as are needed. Columns are arranged across the
 * Listbox from left to right. Within columns, items are arranged from
 * top to bottom. The flow of items, or text, snakes across the face of the
 * Listbox. This is a flexible control class that maximizes the use of short,
 * wide display areas. Subclasses of <code>CEikSnakingListBox</code> are
 * used in the Series 90 shell for the file list and for the control panel. A
 * standard user subclass, <code>CEikSnakingTextListBox</code>, also
 * exists.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CEikSnakingListBox : public CEikListBox
    {
    public:
    // Constructors and destructor
        /**
        * The default object constructor.
        */
        IMPORT_C CEikSnakingListBox();

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikSnakingListBox();


    // New methods
        
       /**
        * Creates the Listbox view.
        * This method is called by <code>ConstructL()</code> to create an
        * instance of the appropriate Listbox view class for this Listbox. The
        * returned instance is owned by this object and does not have to have
        * its second-phase constructor run. In the case of the Snaking Listbox, a
        * <code>CSnakingListBoxView</code> is returned.
        *
        * @return the view that is used by the Listbox being created
        * @remarks
        * @see
        */
        IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();

       /**
        * Sets the top item's index.
        *
        * @param aItemIndex The index of the item to set as the top item
        * @remarks
        * @see
        */
        IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex) const;

       /**
        * Gets the width of this Listbox's columns.
        *
        * @return the width of each column
        * @remarks All columns are the same width
        * @see
        */
        IMPORT_C TInt ColumnWidth() const;

       /**
        * Sets the width of all columns in the Listbox.
        *
        * @param aColumnWidth The new column width
        * @remarks
        * @see
        */
        IMPORT_C void SetColumnWidth(TInt aColumnWidth);

       /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this control. 
        *         <code>EKeyWasConsumed</code> if the control takes action on the 
        *         key event; <code>EKeyWasNotConsumed</code> otherwise
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);  // not available before Release 6.2


    protected:  // Methods

    // New Methods
        
        /**
        * Handles a change in the size of the viewing rectangle.
        */
        IMPORT_C virtual void HandleViewRectSizeChangeL();

/**
 *
 * Handles left arrow keypresses.
 *
 * Moves the cursor into the correct column and clears any matcher buffer
 * that may have been built up.
 *
 * @param     "CListBoxView::TSelectionMode aSelectionMode"
 *            The current selection mode.
 */
        IMPORT_C virtual void HandleLeftArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);

/**
 *
 * Handles right arrow keypresses.
 *
 * Moves the cursor into the correct column and clears any matcher buffer
 * that may have been built up.
 *
 * @param     "CListBoxView::TSelectionMode aSelectionMode"
 *            The current selection mode.
 */
        IMPORT_C virtual void HandleRightArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);

/**
 *
 * Gets the number of horizontal scroll grains to move left or right when
 * the nudge buttons are pressed.
 *
 * @returns   "TInt"
 *            Number of grains to move left or right by.
 */
        IMPORT_C virtual TInt HorizontalNudgeValue() const;

/**
 *
 * Gets the granularity of horizontal scroll actions.
 *
 * For snaking Listboxes, this is the same as the column width.
 *
 * @returns   "TInt"
 *            Movement grain size in pixels.
 */
        IMPORT_C virtual TInt HorizScrollGranularityInPixels() const;

/**
 *
 * Sets which item is displayed at the top of the view.
 *
 * Ensures that the rightmost column has at least one element in it in
 * Listboxes with a large number of items. If all the Listboxs items
 * can be displayed in the view, then this function does nothing.
 *
 */
        IMPORT_C virtual void AdjustTopItemIndex() const;

/**
 *
 * Handles a drag event.
 *
 * Updates the view and scrollbars when a drag event has occurred. If
 * you drag out of the current item any the match buffer is cleared.
 *
 * @param     "TPoint aPointerPos"
 *            Position of the drag event.
 */
        IMPORT_C virtual void HandleDragEventL(TPoint aPointerPos);

/**
 *
 * Calculates the client area.
 *
 * This method is called by various functions of this class to
 * recalculate the extent of the client area from <code>iViewRect</code>.
 * This implementation takes into account any rounding of the viewing
 * rectangle made to fit a whole number of items.
 *
 * @param     "TRect& aClientRect"
 *            On return contains a size for the client area in
 *            pixels.
 */
        IMPORT_C virtual void RestoreClientRectFromViewRect(TRect& aClientRect) const;

/**
 *
 * Shrinks the view rectangle to fit a whole number of items.
 *
 * @param     "TRect& aRect"
 *            Rectangle to adjust.
 * @returns   "TInt"
 *            Number of pixels removed vertically.
 */
        IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const;

/**
 *
 * Moves to the next or previous item in the direction of a pen tap.
 *
 * This function is used by <code>HandleDragEventL()</code> to highlight
 * the next or previous item in the direction of a point.
 *
 * @param     "TPoint aPoint"
 *            The current position of the cursor.
 */
        IMPORT_C void MoveToNextOrPreviousItemL(TPoint aPoint);

/**
 *
 * Responds to the size being changed.
 *
 * This function over-ridest the <code>CCoeControl::SizeChanged()</code>
 * function.
 *
 */
        IMPORT_C virtual void SizeChanged();

/**
 *
 * Gets the list of logical colours employed in the drawing of the
 * control, paired with an explanation of how they are used.
 *
 * Appends the list to <code>aColorUseList</code>.
 *
 * @param     "CArrayFix<TCoeColorUse>& aColorUseList"
 *            On return, a list of logical colours.
 */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

/**
 *
 * Handles a change in a resource.
 *
 * The types (<code>aType</code>) of Listbox resources handled are those
 * which are shared across the environment, for example, colours or
 * fonts.
 *
 * @param     "TInt aType"
 *            The type of resource that has changed.
 */
        IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u

        /**
        * This function does nothing.
        * @param aWriteStream Ignored.
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;


    private: //Methods
        // from CCoeControl
        IMPORT_C void Reserved_2();
        // from CEikListBox
        IMPORT_C void Reserved_3(); // listbox use only
    };


#endif      // EIKLBX_H   
            
// End of File
