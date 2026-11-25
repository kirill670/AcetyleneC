/*
* ==============================================================================
*  Name        : eikhlbx.h
*  Part of     : CKON
*  Interface   : Hierarchical Listbox API
*  Description : Hierarchical Listbox.
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

#ifndef EIKHLBX_H
#define EIKHLBX_H

// INCLUDES
#include <eiklbx.h>
#include <eiklbed.h>

// FORWARD DECLARATIONS
class CHierarchicalListBoxModel;
class CHierarchicalListBoxView;
class CHierarchicalListItemDrawer;

// CLASS DECLARATIONS

/**
*  The <code>CEikHierarchicalListBox</code> class provides a Hierarchical 
*  Listbox. Hierarchical Listboxes present hierarchical data in a scrollable 
*  listbox. Individual parent items can be collapsed or expanded to reduce or 
*  increase the amount of visible data. The class has an item drawer, a model, 
*  and a view, and it responds to user input appropriately.  All classes must
*  be sub-classed before use.
*
*  @lib eikctl.lib 
*  @since Series90 1.0
*/
class CEikHierarchicalListBox : public CEikListBox
    {
    public:
    // Constructors and destructor
        /**
        * The default object constructor.
        */
        IMPORT_C CEikHierarchicalListBox();


        /**
        * The object destructor.
        */
        IMPORT_C ~CEikHierarchicalListBox();


    // New methods
        
        /**
        * Gets the model owned by this Hierarchical Listbox.
        *
        * @return a pointer to the model used by this Hierarchical Listbox
        * @remarks
        * @see
        */
        IMPORT_C CHierarchicalListBoxModel* HlModel() const;

        /**
        * Gets the view owned by this Hierarchical Listbox.
        *
        * @return a pointer to the view owned by this Hierarchical Listbox
        * @remarks
        * @see
        */
        IMPORT_C CHierarchicalListBoxView* HlView() const;

        /**
        * Gets the item drawer owned by this Hierarchical Listbox.
        *
        * @return a pointer to the item drawer owned by this Hierarchical 
        *         Listbox
        * @remarks
        * @see
        */
        IMPORT_C CHierarchicalListItemDrawer* HlDrawer() const;
    // Methods from base classes
    public: // from CCoeControl
        /**
        * Handles key events offered to the Hierarchical Listbox by the control 
        * environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Handles pointer events.
        *
        * @param aPointerEvent The pointer event to handle
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void HandleResourceChange(TInt aType);
public: // from CEikListBox
        /**
        * This method creates an item editor, if one does not already exist, 
        * and starts editing the current item up to a maximum length of 
        * <code>aMaxLength</code> characters.
        *
        * @param aMaxLength The maximum number of characters that can be 
        *                   edited
        * @remarks
        * @see CEikListBox
        */
        IMPORT_C void EditItemL(TInt aMaxLength);
public: // new function
        /**
        * Expands or collapses the current item. 
        *
        * @remarks Redraws the display to reflect the new state of the item. 
        *          The effect is the same as calling either 
        *          <code>HlModel()->ExpandItemL()</code> or
        *          <code>HlModel()->CollapseItem()</code>
        * @see CEikHierarchicalListBoxModel
        */
        IMPORT_C void ToggleCurrentItemStateL();

private: // from CEikListBox

        /**
        * From <code>CEikListBox</code>. Creates the Hierarchical Listbox view.
        * The function is called by <code>ConstructL()</code> to create an instance of the appropriate 
        * Hierarchical Listbox view class for this Hierarchical Listbox. The returned 
        * instance is owned by this object, and does not have to have its second-phase 
        * constructor run. This function is called by <code>CreateViewL()</code>
        * @return Pointer to a newly constructed Hierarchical Listbox view for this object
        */
        IMPORT_C CListBoxView* MakeViewClassInstanceL();
private: // from CCoeControl
        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2();
private: // from CEikListBox
        IMPORT_C void Reserved_3(); // listbox use only
private:
        void HandleItemSelectionL();
        void HandleArrowKeysL(TChar aCh);
        void HandlePlusMinusKeysL(TChar aCh);
        void ActionItemL();

    private:     // Data
        TBool* iHlbxDestroyed;
        TInt iPressedIndex;

    };

/**
* The <code>CEikHierarchicalListBoxEditor</code> class provides the 
* Hierarchical Listbox editor. This is derived from 
* <code>CEikListBoxTextEditor</code>. This Hierarchical Listbox editor 
* contains editor functionality specific to the Hierarchical Listbox.
*
* @lib eikcotl.lib 
* @since
*/
class CEikHierarchicalListBoxEditor : public CEikListBoxTextEditor
    {
public:
        /**
        * The object destructor.
        */
        IMPORT_C ~CEikHierarchicalListBoxEditor();
public: 
        /**
        * The object constructor.
        *
        * @param aModel The mixin interface that provides information needed 
        *               to display the required data in a Hierarchical Listbox
        * @remarks <code>MListBoxModel</code> is defined in eiklbm.h
        * @see
        */
        IMPORT_C CEikHierarchicalListBoxEditor( MListBoxModel* aModel );

    // New methods

        // Methods from base classes
        /**
        * Gets a pointer to the current editable item text.
        *
        * @return a pointer to the editable item text
        * @remarks
        * @see CEikListBoxTextEditor
        */
        IMPORT_C TPtrC ItemText();

        /**
        * Updates the Hierarchical Listbox model with the new item contents. 
        * If no editor window is currently open, this method has no effect.
        *
        * @return <code>ETrue</code> if successful; <code>EFalse</code> if 
        *         editing is not currently on
        * @remarks
        * @see CEikListBoxTextEditor
        */
        IMPORT_C TBool UpdateModelL();
    };


#endif      // EIKHLBX_H   
            
// End of File
