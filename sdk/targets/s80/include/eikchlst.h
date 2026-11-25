/*
* ==============================================================================
*  Name        : eikchlst.h
*  Part of     : CKON
*  Interface   : Choicelist API
*  Description : Choicelist control
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

#ifndef EIKCHLST_H
#define EIKCHLST_H


// INCLUDES
#include <eikbctrl.h>
#include <badesca.h>
#include <eiktxlbx.h>
#include <eikcmobs.h>
#include "EikUbgcb.h"

// FORWARD DECLARATIONS
class TResourceReader;
class RIncrMatcherBase;
class CEikChoiceListBaseExt;
class CEikListBox;
class CEikTextListBox;


// CLASS DECLARATIONS

/**
* The <code>CEikChoiceListBase</code> class is the base class for all 
* Choicelists.
*  
* @lib eikctl.lib
* @since Series90 1.0
*/
class CEikChoiceListBase : public CEikBorderedControl, public MCoeControlObserver
    {
    friend class CCknChoiceListCheckBox;

    public:  // Declarations

        /** This enumeration contains constants for the Choicelist base. */
        enum
            {
            /** use <code>EEikMaxMatchingBufLength</code> below */
            KEikMaxMatchingBufLength=24,
            /** the maximum matching buffer length */
            EEikMaxMatchingBufLength=24,
            /** the value of an <code>iCurrentItem</code> item in the Choicelist when it is not valid */
            ECknChoiceListNonListItem=-1
            };

        /** 
         * The <code>TFlags</code> enumeration contains flags describing the 
         * properties of the Choicelist. 
         */
        enum TFlags
            {
            /** indicates that the Choicelist text array is not owned by this object and so is not deleted by the destructor */
            EArrayOwnedExternally       =0x01, 
            /** indicates that the user's keystrokes are matched incrementally */
            EIncrementalMatching        =0x02,
            /** indicates that no pop-out listbox is permitted from the Choicelist */
            ENoPopout                   =0x04,
            /** indicates whether the incremental match buffer is reset after a period of time */
            EIncrementalMatchingTimeout =0x08,
            /** indicates that the control wants to be notified of all state changes, even if they are the same as the last one */
            EEventStateChangedAlways    =0x10,
			/** indicates that we want the little icon to open the popout. This is for Series80 only,
			in Series90 the icon is always shown */
			EPopoutIcon				=0x20
            };

		enum TZoomLevel
			{
			EZoomLevel1 = 0,
			EZoomLevel2 = 1,
			EZoomLevel3 = 2
            };

        /** 
         * The <code>TChoiceListPointerState</code> enumeration contains 
         * states for the pointer when interacting with the Choicelist. 
         * It is used to allow the user to tap the Choicelist and then drag 
         * the pen off it and thus to cancel the intention to open the pop-out 
         * listbox. 
         */
        enum TChoiceListPointerState 
            {
            /** the pointer is in an "up" state, that is, it is not depressed */
            EChoiceListPointerStateUp,
            
            /** the pointer is in an "in" state, that is, it is down */
            EChoiceListPointerStateIn,
            
            /** the pointer is outside the Choicelist area */
            EChoiceListPointerStateOut
            };

    public:

    // Constructors and destructor

        /**
        * The object destructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C ~CEikChoiceListBase();

    // New methods

        /**
        * Gets the current item's index.
        * 
        * @return either the <code>TInt</code> index of the current item in the
        *         list or, if the current item is a non-list item, 
        *         <code>ECknChoiceListNonListItem</code> 
        * @remarks
        * @see
        */
        IMPORT_C TInt CurrentItem() const;

        /**
        * Sets the current item by index.
        * 
        * @param aItem The index of the current item
        * @remarks
        * @see
        */
        IMPORT_C void SetCurrentItem(TInt aItem);

        /**
        * Sets the Choicelist matching behavior. If set to <code>ETrue</code>,
        * the keyboard input will be used to incrementally match the Choice 
        * List item.
        * 
        * @param aAllowIncrementalMatching <code>ETrue</code> to allow incremental matching; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetIncrementalMatching(TBool aAllowIncrementalMatching);

        /**
        * Sets whether the array of values in the Choicelist are owned by the
        * control or externally. If owned by the control, the control deals 
        * with array cleanup.
        * 
        * @param aArrayOwnedExternally <code>ETrue</code> if the array is 
        *        owned by another control; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetArrayExternalOwnership(TBool aArrayOwnedExternally);

        /**
        * Returns the array of list items.
        * 
        * @return the array of list items
        * @remarks
        * @see
        */
        MDesCArray* Array() const;

        /**
        * Sets the Choicelist to use an array of list items specified in a 
        * resource file.
        * 
        * @param aResourceId The resource ID of the array
        * @remarks
        * @see
        */
        IMPORT_C void SetArrayL(TInt aResourceId);

        /**
        * Sets the Choicelist to use the given array of items.
        * 
        * @param aArray The array of items to use
        * @remarks
        * @see
        */
        IMPORT_C void SetArrayL(MDesCArray* aArray);

        /**
        * Returns the array of list items as a <code>CDesCArray*</code>.
        * 
        * @return the array of list items
        * @remarks
        * @see
        */
        IMPORT_C CDesCArray* DesCArray() const;

        /**
        * Sets whether the Choicelist pop-out listbox appears on activation.
        * 
        * @param aAllow <code>ETrue</code> if a pop-out listbox is allowed; 
        *               <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void AllowPopout(TBool aAllow);

        /**
        * Sets the font used by the Choicelist.
        * 
        * @param aFont The font to use
        * @remarks
        * @see
        */
        IMPORT_C void SetFont(const CFont* aFont);

		/**
		* Sets the zoom level
		* @param aZoomLevel The zoom level to use.
		*/
		IMPORT_C void SetZoomLevel(TZoomLevel aZoomLevel);

        /**
        * Returns the margin for the text. Currently, this can only be 
        * <code>0</code>.
        * 
        * @return the margin, in pixels
        * @remarks
        * @see
        */
        IMPORT_C static TInt TextEdgeMargin();

        /**
        * @internal
        */
        void HandleMatchTimeout();

    protected:  // Methods

    // Methods from base classes

        /**
        * From CCoeControl.
        * @param aControl unused.
        * @param aEventType The event type
        */
        IMPORT_C void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType);

        /**
        * From CCoeControl.
        * @param aPointerEvent The pointer event
        */
        IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * From CCoeControl.
        * @param aKeyEvent The key event
        * @param aEventCode The event code
        * @return A response.
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aEventCode);

        /**
        * From CCoeControl.
        */
        IMPORT_C void SizeChanged();

        /**
        * From CCoeControl.
        */
        IMPORT_C void ActivateL();

        /**
        * From CCoeControl.
        * @param aDrawNow Redraw immediately if true.
        */
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);

        /**
        * From CCoeControl
        * @param aAdjacent Typically a value defined in TCoeAdjacent
        */
        IMPORT_C void SetAdjacent(TInt aAdjacent);

        /**
        * From CCoeControl.
        * @param aRect The rect in which to draw
        */
        IMPORT_C virtual void Draw(const TRect& aRect) const;

        /**
        * From CCoeControl.
        * @return The control's input capabilities.
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;

    // Constructors and destructor

        /**
        * Default C++ constructor
        */
        IMPORT_C CEikChoiceListBase();

    // New Methods

        /**
        * Returns the position of the cursor in the match buffer.
        * @return The cursor position
        */
        IMPORT_C TInt CursorPos() const;

        /**
        * Reset the match buffer.
        */
        IMPORT_C void ResetMatchBuf();

        /**
        * Returns the width of the maximum list item.
        * @return The width of the maximum list item.
        */
        IMPORT_C TInt CalculateTextWidth() const;

        /**
        * Creates the Choicelist pop-out. This must be implemented by deriving classes.
        */
        virtual void CreatePopoutL()=0;

        /**
        * Destroys the Choicelist pop-out. This must be implemented by deriving classes.
        */
        virtual void DestroyPopout()=0;

        /**
        * Returns the currently selected item in the pop-out
        * @return The index if the currently selected item.
        */
        IMPORT_C virtual TInt PopoutCurrentItem() const;

        /**
        * Implemented by derived classes. This function should draw the content of the Choicelist.
        */
        virtual void DrawContent() const=0;

        /**
        * This function uses DrawContent to draw the content of the Choicelist immediately.
        */
        IMPORT_C void DrawContentNow() const;

        /**
        * For internal use.
        */
        IMPORT_C virtual void HandleInteractionConfirmedL();

        /**
        * Called when the current item has changed. May be overridden by derived classes.
        */
        IMPORT_C virtual void CurrentItemChangedL();

        /**
        * Destroys the array of list items
        */
        IMPORT_C void DestroyArray();

        /**
        * For internal use. Adds aCode to match buffer and looks for matching list item.
        * @param aCode The key code to add to the match buffer.
        */
        IMPORT_C virtual void MatchTypedChar(TUint aCode);

        /**
        * Remove char last added to match buffer.
        */
        IMPORT_C void UndoLastChar();

        /**
        * Displays the cursor for the match buffer.
        */
        IMPORT_C void DisplayCursor();

        /**
        * Called when the content of the Choicelist has changed.
        */
        IMPORT_C void ContentHasChangedL();

        /**
        * Returns the font used by the Choicelist
        * @return The font used.
        */
        IMPORT_C const CFont* Font() const;

        /**
        * Returns the button bitmap index.
        * @return The button bitmap index.
        */
        IMPORT_C TInt ButtonBitmapIndex() const;

        /**
        * Sets the button bitmap index.
        * @param aValue The button bitmap index
        */
        IMPORT_C void SetButtonBitmapIndex(TInt aValue);

    private: //Methods

    // Methods from base classes

        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2();

    protected:  // Methods

        /**
        * For internal use only.
        * @return ETrue if extension exists.
        */
        TBool CheckCreateExtension();

        /**
        * For internal use only.
        * @return The extension
        */
        CEikChoiceListBaseExt& BaseExt();

        /**
        * For internal use.
        * @param aState The new pointer state
        */
        void SetPointerState(TChoiceListPointerState aState);

		/**
		* For internal use.
		* @return The index of the bitmap for the button icon depending on
		* the zoom level.
		*/
		TInt GetButtonIndex() const;
		void DrawRaisedBorder(CWindowGc& aGc, TRect& aRect) const;
		TRect InnerRect() const;
		TMargins Margins() const;
		TSize ArrowSize() const;
		void RemoveCursor();
		
    private: //Methods

    // Methods from base classes

        IMPORT_C virtual void Reserved_3();

    protected:     // Data
        /** the array of list items. */
        MDesCArray* iArray;
        /** The incremental match buffer. */
        RIncrMatcherBase* iMatchBuf;
        /** The flags for the widget. */
        TInt iChoiceListFlags;
        /** The currently selected item. */
        TInt iCurrentItem;
        /** The maximum number of chars to display. */
        TInt iMaxDisplayChar;
        /** The text ascent. */
        TInt iAscent;

    private:     // Data

        TInt iCursorPos;
        const CFont* iChlstFont;
        CEikChoiceListBaseExt* iBaseExt;
    };

inline CEikChoiceListBaseExt& CEikChoiceListBase::BaseExt()
    {
    return *iBaseExt;
    }

inline MDesCArray* CEikChoiceListBase::Array() const
    {
    return iArray;
    }

/**
 * The <code>CEikChoiceList</code> class provides a basic Choicelist.
 * The Choicelist control displays a single item from a list of items
 * and allows users to scroll through the items by using the up and down 
 * navigation keys. Users can also select the desired item from the pop-out 
 * listbox launched from this control. During initialization, flags can be set 
 * to allow item selection through the incremental matching 
 * of entered text. A flag can also be set to disable the pop-out listbox.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class CEikChoiceList : public CEikChoiceListBase, public MEikUpdatingBgContainerBase
    {
    public:

    // Constructors and destructor

        /**
        * The object destructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C ~CEikChoiceList();

        /**
        * The default object constructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C CEikChoiceList();

    // New methods

        /**
        * Completes construction of a Choicelist object.
        * 
        * @param aParent The parent control
        * @param aFlags Flags for this Choicelist control
        * @param aMaxDisplayChar The maximum number of characters to display
        * @return
        * @remarks The <code>aFlags</code> parameter is as the 
        *          <code>TFlags</code> enum. That is: 
        *          <code>EArrayOwnedExternally</code>, 
        *          <code>EIncrementalMatching</code>, 
        *          <code>ENoPopout</code>, 
        *          <code>EIncrementalMatchingTimeout</code>, and 
        *          <code>EEventStateChangedAlways</code>. The width of the 
        *          Choicelist is the width of the longest option up to the 
        *          maximum width specified for the <code>aMaxDisplayChar</code> 
        *          parameter. If <code>aMaxDisplayChar</code> is set to 
        *          <code>0</code>, the maximum width of the Choicelist is the 
        *          length of the longest option, or the length to the edge of 
        *          the screen, whichever is the shorter
        * @see
        */
        IMPORT_C void ConstructL(CCoeControl* aParent, TInt aFlags, TInt aMaxDisplayChar);

        /**
        * Returns the pop-out listbox.
        * 
        * @return the pop-out listbox
        * @remarks 
        * @see
        */
        IMPORT_C CEikTextListBox* PopoutTextListBox() const;

        /**
        * Sets the currently selected item to the item equal to 
        * <code>aItem</code>.
        * 
        * @param aItem The item to be considered current
        * @remarks The <code>aItem</code> parameter enables the Choicelist in
        *          its closed state to display text that is not one of the 
        *          options in the Choicelist listbox. This is useful, for 
        *          example, to set the visible item to be blank
        * @see
        */
        IMPORT_C void SetCurrentItemL(const TDesC& aItem);

        /**
        * Returns the current list item.
        * 
        * @return a pointer to the current list item
        * @remarks
        * @see
        */
        IMPORT_C TPtrC GetCurrentItem();

        /**
        * Removes the pop-out listbox.
        * 
        * @remarks
        * @see
        */
        IMPORT_C virtual void DestroyPopout();

    // Methods from base classes

public: // from CCoeControl

        /**
        * Gets the minimum size of the Choicelist control.
        * 
        * @return the minimum size of the control
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual TSize MinimumSize();

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        * @since ER5U
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

        /**
        * Handles a change to the control's resources that are shared across 
        * the environment.
        *
        * @since ER5U
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed 
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);

        /**
        * Prepares the Choicelist for gaining focus. Implementations can take
        * any action required, such as updating control information. By default,
        * the implementation is empty.
        * 
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void PrepareForFocusGainL();

        /**
        * Responds to the focus changing. This method is called whenever a 
        * control gains or loses focus as a result of a call to 
        * <code>SetFocus()</code>. 
        *
        * @param aDrawNow Contains the value that was passed to it by 
        *                 <code>SetFocus()</code>
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);

    protected:  // Methods

    // New Methods

        /**
        * Constructs the control from a resource
        * @param aReader The resource reader
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Creates the listbox pop-out.
        */
        IMPORT_C virtual void CreatePopoutL();

        /**
        * Returns the index of the current item.
        * @return The index of the current item.
        */
        IMPORT_C virtual TInt PopoutCurrentItem() const;

        /**
        * Gets things ready to draw the content of the listbox.
        */
        IMPORT_C virtual void DrawContent() const;

        /**
        * Draws the content of the listbox.
        * @param aDes the text of the current item.
        */
        IMPORT_C virtual void DoDrawContent(const TDesC& aDes) const;

        /**
        * Sets up and creates the listbox pop-out.
        */
        IMPORT_C virtual void DoCreatePopoutL();

        /**
        * Creates the listbox pop-out.
        */
        IMPORT_C virtual void CreateListBoxL();

        /**
        * Initialises the listbox pop-out.
        */
        IMPORT_C virtual void InitializeListBoxL();

        /**
        * Sets the extent of the listbox.
        */
        IMPORT_C virtual void SetListBoxExtentL();

        /**
        * Activates the listbox.
        */
        IMPORT_C virtual void ActivateListBoxL();

        /**
        * Called when the current item in the listbox is changed.
        */
        IMPORT_C virtual void CurrentItemChangedL();

    // Methods from base classes

protected: // from MEikUpdatingBgContainerBase
        /**
        * Handles interaction with the 'change' CBA button, where one exists.
        */
        IMPORT_C void HandleChangeButtonL();

        /**
        * Is the popup up?
        * @return ETrue if the popup is displayed.
        */
        IMPORT_C TBool PopupDisplayed();

    private: //Methods

    // Methods from base classes

        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2();
        IMPORT_C void Reserved_3();

    protected:  // Methods

        /**
        * Draw the content of the Choicelist.
        * @param aDes The text of the current item
        */
        void DoDrawContentL(const TDesC& aDes) const;

    protected:     // Data

        CEikListBox* iPopoutListBox;

    };

/**
 * The pop-out listbox used by a Choicelist. The pop-out listbox is a type of
 * text listbox 
 * that pops out when the Choicelist is activated.
 * <code>CEikChoiceList</code> owns a <code>CEikListBox</code> class which is cast to
 * <code>CEikChoiceListPopoutListBox</code> and the functions from this class are used internally.
 * <code>CEikChoiceList</code> returns a pointer to a <code>CEikTextListBox</code> for the popout.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 * @internal
 */
class CEikChoiceListPopoutListBox : public CEikTextListBox, public MEikCommandObserver
    {

    public:

    // Constructors and destructor

        /**
        * The default object constructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C CEikChoiceListPopoutListBox();

        /**
        * The object destructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C ~CEikChoiceListPopoutListBox();

    // New methods

        /**
        * Completes construction of a Choicelist object.
        * 
        * @param aParent The parent control
        * @param aFlags The control flags
        * @param aFont The font to use
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aFlags,const CFont* aFont);

        /**
        * Handles key events offered to the control by the control environment.
        * 
        * @param aKeyEvent The key event
        * @param aType The type of key event, either: <code>EEventKey</code>, <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this control. <code>EKeyWasConsumed</code> if the control takes action on the key event; <code>EKeyWasNotConsumed</code> otherwise
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

public: // from CCoeControl
        /**
        * Activates the pop-out listbox.
        *
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ActivateL();

    protected:  // Methods

    // New Methods

        /**
        * Create a button group container. Internal use only.
        */
        IMPORT_C void CreateButtonGroupContainerL();

    // Methods from base classes

protected: // from MEikCommandObserver
        /**
        * From MEikCommandObserver
        * Process a command.
        * @param aCommandId The command Id to process
        */
        IMPORT_C void ProcessCommandL(TInt aCommandId);

    private:     // Data

        CEikButtonGroupContainer *iButtonGroupContainer;

    };

#endif      // EIKCHLST_H

// End of File
