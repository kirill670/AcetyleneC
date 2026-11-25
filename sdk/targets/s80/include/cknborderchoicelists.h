/*
* ==============================================================================
*  Name        : cknborderchoicelists.h
*  Part of     : CKON
*  Interface   : Choice List API
*  Description : Choice lists for selecting line styles and borders.
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

#ifndef CKNBORDERCHOICELISTS_H
#define CKNBORDERCHOICELISTS_H


// INCLUDES
#include <eikchlst.h>

// FORWARD DECLARATIONS
class CCknBorderPlaceChoiceList;
class CCknLineStyleChoiceList;
class CCknSkinBase;

// CLASS DECLARATIONS

/**
 * The <code>CCknLineStylePopoutListBox</code> class creates a pop-out listbox 
 * that is used within <code>CCknLineStyleChoiceList</code>.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknLineStylePopoutListBox : public CEikBorderedControl, public MEikCommandObserver
    {
    public:
    // Constructors and destructor

        /**
        * The object constructor.
        *
        * @param aParent The parent control
        * @remarks
        * @see
        */
        IMPORT_C CCknLineStylePopoutListBox(CCknLineStyleChoiceList* aParent);
        
        /**
        * The object destructor.
        */
        IMPORT_C ~CCknLineStylePopoutListBox();
        
        /**
        * Completes construction of a pop-out linestyle listbox object.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL();
        
        /**
        * Gets the selected style.
        * 
        * @return the style being set
        * @remarks
        * @see <code>TBorderLineStyle<\code> in <code>eikparad.h<\code>
		*      for valid values returned by the method
        */

        IMPORT_C TInt SelectedStyle() const;
        /**
        * Sets the selected style.
        * 
        * @param aStyle The style to be set 
        * @remarks
        * @see <code>TBorderLineStyle<\code> in <code>eikparad.h<\code>
		*      for valid values of <code>aStyle<\code>
        */
        IMPORT_C void SetSelectedStyle(const TInt aStyle);

    // Methods from base classes

        /**
        * Sets the size and position of the contents of the control after a 
        * resize.
        * 
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SizeChanged();
        
        /**
        * Gets the minimum size for the pop-out listbox.
        * 
        * @return the minimum size of the pop-out listbox
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize();
        
        /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, one of <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        
        /**
        * Handles pointer events.
        *
        * @param aPointerEvent The pointer event
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * Draws the control.
        *
        * @param aRect Not currently used 
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void Draw(const TRect& aRect) const;
        
        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u
        
        /**
        * Returns the input capabilities of the object. Typically, called by 
        * the FEP-aware text-editors. By default, the pop-out listbox is 
        * capable of handling navigation keys, including arrow keys, 
        * page-up, page-down, home, end, and tab keys, etc.
        *
        * @return the input capabilities
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;
        
        /**
        * Activates this control. Sets it as ready for drawing.
        * 
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ActivateL();
    protected:  // Methods
    // New Methods
        
        /**
        * This function does nothing because CCknLineStylePopoutListBox does not use the CBA.
        */
        IMPORT_C void CreateButtonGroupContainerL();
    // Methods from base classes

        /**
        * From MEikCommandObserver Command processor ie. OK, Cancel
        * @param aCommandId Command to be processed
        */
        IMPORT_C void ProcessCommandL(TInt aCommandId);
    private: //Methods
        void DrawLineStyles() const;
        void DrawHighlightToStyle(TInt aGrayLevel, TBool aHighLighted) const;
        void DrawHighlightToStyleNow(TInt aGrayLevel, TBool aHighLighted) const;
    private:     // Data
        TInt iSelectedStyle;
        TInt iOriginalSelectedStyle;
        TPoint iTopLeft;
        CCknLineStyleChoiceList* iParent;
        CCknSkinBase& iSkin;
        /// extension class for BC
        TAny* iReserved;
    };

/**
 * The <code>CCknLineStyleChoiceList</code> class creates a choice list with 
 * a pop-out listbox.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknLineStyleChoiceList : public CEikChoiceListBase
    {
    public:
    // Constructors and destructor

        /**
        * The object destructor.
        */
        IMPORT_C ~CCknLineStyleChoiceList();
        /**
        * The default object constructor.
        */
        IMPORT_C CCknLineStyleChoiceList();
    // New methods
        
        /**
        * Completes construction of a <code>CCknLineStyleChoiceList</code>
        * object.
        *
        * @param aParent The parent control
        * @param aFlags The choice list flags
        * @param aMaxDisplayChar The maximum number of characters to be 
        *                        displayed
        * @remarks
        * @see <code>CEikChoiceListBase::TFlags<\code> enumeration for valid values of <code>aFlags<\code>.
        */
        IMPORT_C void ConstructL(CCoeControl* aParent, TInt aFlags, TInt aMaxDisplayChar);
        
        /**
        * Creates a pop-out listbox.
        *
        * @remarks
        * @see
        */
        IMPORT_C void CreatePopoutL();
        
        /**
        * Destroys a pop-out listbox.
        *
        * @remarks DestroyPopout() is safe to call whether a popout exists or not
        * @see
        */
        IMPORT_C void DestroyPopout();
        
        /**
        * Constructs a <code>CCknLineStyleChoiceList</code> from a resource 
        * file. To use this control, create a method 
        * <code>CreateCustomControlL()</code>.
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>CHOICELIST</code>
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
        
        /**
        * Gets the minimum size for the choice list.
        * 
        * @return the minimum size of the choice list
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize();
        
        /**
        * Gets the style of the current pop-out item.
        *
        * @return the style of the current pop-out item
        * @remarks PopoutCurrentItem() panics if no popout exists (with Kern Exec 3)
        * @see <code>TBorderLineStyle<\code> in <code>eikparad.h<\code>
		*      for valid return values
        */
        IMPORT_C TInt PopoutCurrentItem() const;

        /**
        * Returns the correct bitmap depending on whether the border is latched 
        * or not.
        *
        * @param aIndex Bitmap index (in a bitmap array) 
        * @return a pointer to the bitmap
        * @remarks 
        * @see
        */
        CFbsBitmap* Bitmap(TInt aIndex) const;
    protected:  // Methods

    // New Methods
        
        /**
        * Activates listbox.
        */
        void ActivateListBoxL();
        /**
        * Sets the listbox extent.
        */
        void SetListBoxExtentL();
        /**
        * Draw the selected style bitmap.
        */
        IMPORT_C void DrawContent() const;
    private: //Methods
        void CreateAndAppendBitmapL(const TDesC& aFileName,TInt aId);
    protected:     // Data
        /** Listbox that pops out. */
        CCknLineStylePopoutListBox* iPopoutListBox; 
        CArrayPtrFlat<CFbsBitmap> iBitmapArray;
        CCknSkinBase& iSkin;
    private:
        TAny* iReserved;
    };

/**
 * The <code>CCknBorderPlacePopoutListBox</code> class creates a pop-out 
 * listbox that is used within <code>CCknBorderPlaceChoiceList</code>.
 *
 * @lib cknctl.lib 
 * @since Series90 1.0
 */
class CCknBorderPlacePopoutListBox : public CEikBorderedControl, public MEikCommandObserver
    {
    public:
    // Constructors and destructor

        /**
        * The object constructor.
        *
        * @param aParent The parent control
        * @param aCentreBorders Whether there are center borders
        * @remarks
        * @see
        */
        IMPORT_C CCknBorderPlacePopoutListBox(CCknBorderPlaceChoiceList* aParent, 
                                          TBool aCentreBorders);
        /**
        * The object destructor.
        */
        IMPORT_C ~CCknBorderPlacePopoutListBox();
    // New methods
        
        /**
        * Completes construction of a <code>CCknBorderPlacePopoutListBox</code>
        * object.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL();
        
        /**
        * Returns the selected place.
        *
        * @return The place being selected
        * @remarks
        * @see
        */
        IMPORT_C TInt SelectedPlace() const;
        
        /**
        * Sets the selected place.
        *
        * @param aStyle The selected place to be set
        * @remarks
        * @see
        */
        IMPORT_C void SetSelectedPlace(const TInt aStyle);
    // Methods from base classes

        /**
        * Sets the size and position of the contents of the control after a 
        * resize.
        * 
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SizeChanged();
        
        /**
        * Gets the minimum size for the control.
        * 
        * @return the minimum size of the control
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize();
        
        /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, one of <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        
        /**
        * Handles pointer events.
        *
        * @param aPointerEvent The pointer event
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
        
        /**
        * Draws the control.
        *
        * @param aRect Not currently used 
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void Draw(const TRect& aRect) const;
        
        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u
        
        /**
        * Returns the input capabilities of the control. Typically, called by 
        * the FEP-aware text-editors. By default, the control is capable of 
        * handling navigation keys, including arrow keys, page-up, page-down, 
        * home, end, and tab keys, etc.
        *
        * @return the input capabilities
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;
        
        /**
        * Activates this control. Sets the object as ready for drawing.
        * 
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ActivateL();
    protected:  // Methods
    // New Methods
        
        /**
        * This function does nothing because CCknBorderPlacePopoutListBox does not use the CBA.
        */
        IMPORT_C void CreateButtonGroupContainerL();
    protected: // from MEikCommandObserver
    // Methods from base classes

        /**
        * From MEikCommandObserver Command processor ie. OK, Cancel
        * @param aCommandId Command to be processed
        */
        IMPORT_C void ProcessCommandL(TInt aCommandId);
    private: //Methods
        void DrawLinePlaces() const;
        void DrawLinePlace(TInt aPlaceIndex, TPoint aPos) const;
        void DrawLinePlaceNow(TInt aPlaceIndex, TPoint aPos) const;
        void DrawHighlightToPlace(TInt aPlaceIndex, TBool aHighLighted) const;
        void DrawHighlightToPlaceNow(TInt aPlaceIndex, TBool aHighLighted) const;
        TRect CalcBorderRect(TInt aPlaceIndex) const;
    private:     // Data
        TBool iCentreBorders;
        TInt iBorderPlacePopoutTopRightIndex;
        TInt iBorderPlacePopoutColumns;
        TInt iSelectedPlace;
        TInt iOriginalSelectedPlace;
        TPoint iTopLeft;

        CCknBorderPlaceChoiceList* iParent;
        CCknSkinBase& iSkin;
        TAny* iReserved;
    };

/**
 * The <code>CCknBorderPlaceChoiceList</code> class creates a choice list with a pop-out 
 * list box to choose bitmap borders. The currently selected border is displayed.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknBorderPlaceChoiceList : public CEikChoiceListBase
    {
    public:
    // Constructors and destructor
        /**
        * The object destructor.
        */
        IMPORT_C ~CCknBorderPlaceChoiceList();
        
        /**
        * The default object constructor.
        */
        IMPORT_C CCknBorderPlaceChoiceList();
        
        /**
        * Completes construction of the choice list object.
        *
        * @param aParent The parent control
        * @param aFlags The choice list's flags
        * @param aMaxDisplayChar The maximum number of characters to be 
        *                        displayed
        * @param aCentreBorders Whether there are center borders
        * @remarks
        * @see <code>CEikChoiceListBase::TFlags<\code> enumeration for valid values of <code>aFlags<\code>.
        */
        IMPORT_C void ConstructL(CCoeControl* aParent, TInt aFlags, TInt aMaxDisplayChar,
                             TBool aCentreBorders);
        /**
        * Creates a pop-out listbox.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void CreatePopoutL();
        
        /**
        * Destroys a pop-out listbox.
        *
        * @remarks DestroyPopout() is safe to call whether a popout exists or not
        * @see
        */
        IMPORT_C void DestroyPopout();
        
        /**
        * Constructs a choice list object from a resource file. To use this 
        * control, create a method <code>CreateCustomControlL()</code>.
        *
        * @param aReader A resource file reader
        * @remarks The resource type is <code>CHOICELIST</code>
        * @see
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
        
        /**
        * Gets the minimum size for the control.
        * 
        * @return the minimum size of the control
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize();
        
        /**
        * Gets the place of the current pop-out item.
        *
        * @return the place of the current pop-out item
        * @remarks PopoutCurrentItem() panics if no popout exists (with Kern Exec 3)
        * @see <code>TBorderLinePlace<\code> in <code>eikparad.h<\code>
		*      for valid return values 
        */
        IMPORT_C TInt PopoutCurrentItem() const;
        
        /**
        * Handles control events from the choice list.
        *
        * @param aControl The control
        * @param aEventType The event type
        * @remarks 
        * @see
        */
        IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
        
        /**
        * Sets the specified border to become latched/unlatched.
        *
        * @param aBorderPlace The border to set
        * @param aSetLatched <code>ETrue</code> to set the border to latched;
        *                    <code>EFalse</code> to unset the latching
        * @remarks
        * @see
        */
        IMPORT_C void SetBorderLatched(TInt aBorderPlace, TBool aSetLatched);
        
        /**
        * Checks if the specified border is latched.
        * 
        * @param aBorderPlace The border to check
        * @return <code>ETrue</code> if the border is latched; <code>EFalse</code>
        *         otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsBorderLatched(TInt aBorderPlace) const;
    
        /**
        * Checks if the latching feature is turned on.
        *
        * @return <code>ETrue</code> if latching is turned on; <code>EFalse</code>
        *         otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsLatchingOn() const;
        
        /**
        * Turns the latching feature in the choice list on or off.
        *
        * @param aOn On or off
        * @remarks
        * @see
        */
        IMPORT_C void SetLatchingOn(TBool aOn);

        /**
        * Returns the correct bitmap depending on whether the border is latched or not.
        * @param aIndex Index in an array
        * @return Pointer to the bitmap
        * <BR><B>Type of return value:</B> CFbsBitmap*
        * @internal
        */
        const CFbsBitmap* Bitmap(TInt aIndex) const;
        /**
        * Returns the correct mask bitmap depending on whether the border is latched or not.
        * @param aIndex Index in an array
        * @return Pointer to the mask bitmap
        * <BR><B>Type of return value:</B> CFbsBitmap*
        * @internal
        */
        const CFbsBitmap* Mask(TInt aIndex) const;
        /**
        * Updates the border in the choice list.
        * <BR><B>Type of return value:</B> void
        * @internal
        */
        void UpdateBorderPlace();
        /**
        * Returns the number of border places.
        * <BR><B>Type of return value:</B> TInt
        * @internal
        */
        TInt NumberOfBorderPlaces();
    protected:  // Methods
    // New Methods
        
        /**
        * Activates the listbox.
        */
        void ActivateListBoxL();
        /**
        * Sets listbox event.
        */
        void SetListBoxExtentL();
        /**
        * Draw the selected place.
        */
        IMPORT_C void DrawContent() const;
    private: //Methods
        void CreateAndAppendBitmapL(const TDesC& aFileName,TInt aId);
        TUint BorderFlag(TInt aBorderPlace) const;
        void SetFlags(TUint aFlags);
        void UnsetFlags(TUint aFlags);
        void CheckAllBordersLatched();
        TInt GetBitmapIndex(TInt aIndex) const;

    protected:     // Data
        /** (If) center borders. */
        TBool iCentreBorders;
        /** pop-out listbox. */
        CCknBorderPlacePopoutListBox* iPopoutListBox;
        /** (If) latching is on. */
        TBool iLatchingOn;
        /** Border bitmap flags. */
        TUint iFlags;
        RPointerArray<CFbsBitmap> iBitmapArray;
        /** Mask bitmap. */
        CFbsBitmap* iMaskBitmap;
        CCknSkinBase& iSkin;
        TBool iMbmDuplicated;
    private:        
        TAny* iReserved;
    };


#endif      // CKNBORDERCHOICELISTS_H               
// End of File
