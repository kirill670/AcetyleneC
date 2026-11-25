/*
* =============================================================================
*  Name        : eikcmbox.h
*  Part of     : CKon
*  Interface   : CEikComboBox
*  Description : Classes relating to the Combobox widget
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


#ifndef EIKCMBOX_H
#define EIKCMBOX_H

//** INCLUDES *
#include <eikbctrl.h>
#include <eikcmobs.h>
#include <eiktxlbx.h>
#include <eiklbi.h>
#include "EikUbgcb.h"

//** FORWARD DECLARATIONS *
class CEikEdwin;
class TResourceReader;
class CCknComboListBox;

/**
* The <code>CEikComboBoxBC</code> class provides a Combobox control. A 
* Combobox enables an item from a list to be selected or a new item to be 
* entered by a user. The available items can be viewed in a pop-out listbox.
* <code>CEikComboBoxBC</code> ensures binary compatibility with S80 resources. 
* This class should not be used. Instead use <code>CEikComboBox</code>.
* 
* @lib eikctl.lib
*/
class CEikComboBoxBC : public CEikBorderedControl, public MCoeControlObserver, public MEikUpdatingBgContainerBase
    {
    public:

        /**
        * The <code>TArrayOwnershipType</code> enumeration specifies types for 
        * the ownership of the array.
        */
        enum TArrayOwnershipType
            {
            /** Combobox owns the array */
            EArrayInternalOwner=0x00,
            /** the array is owned externally */
            EArrayExternalOwner=0x01
            };

    public:

        /**
        * The object constructor.
        */
        IMPORT_C CEikComboBoxBC();

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikComboBoxBC();

        /**
        * The second phase object constructor. Completes construction of a 
        * Combobox.
        *
        * @param aParent The parent of the Combobox 
        * @param aWidthInChars The width of the Combobox, in characters
        * @param aTextLimit The maximum length for the Combobox's editable text
        * @param aMaxArraySize The maximum size of the array of Combobox items
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(const CCoeControl& aParent,TInt aWidthInChars,TInt aTextLimit,TInt aMaxArraySize);

        /**
        * Gets a pointer to the array of Combobox items.
        * 
        * @return the array of Combobox items
        * @remarks
        * @see
        */
        IMPORT_C MDesCArray* Array() const;

        /**
        * Sets the array of Combobox items from a specified resource.
        * Also sets the array's ownership type, that is, whether or not the 
        * Combobox handles the deletion of the array.
        *
        * @param aResourceId The ID of the <code>ARRAY</code> resource to use
        * @param aOwner The array's ownership type. A value of 
        *               <code>EArrayExternalOwner</code> specifies that the 
        *               Combobox does not delete the array; 
        *               <code>EArrayInternalOwner</code> specifies that the 
        *               Combobox takes ownership of the array and deletes it 
        *               in the destructor
        * @remarks
        * @see TArrayOwnershipType
        */
        IMPORT_C void SetArrayL(TInt aResourceId,TArrayOwnershipType aOwner=EArrayInternalOwner);

        /**
        * Sets the Combobox item array. This method also sets the array's 
        * ownership type, that is, whether or not the Combobox handles the 
        * array's deletion.
        * 
        * @param aArray The array
        * @param aOwner The array's ownership type. A value of 
        *               <code>EArrayExternalOwner</code> specifies that the 
        *               Combobox does not delete the array; 
        *               <code>EArrayInternalOwner</code> specifies that the 
        *               Combobox takes ownership of the array and deletes it 
        *               in the destructor
        * @remarks
        * @see TArrayOwnershipType
        */
        IMPORT_C void SetArray(MDesCArray* aArray,TArrayOwnershipType aOwner=EArrayInternalOwner);

        /**
        * Gets the text currently held in the editor that is used to edit 
        * Combobox items, and copies it into the provided buffer.
        * It is the caller's responsibility to provide a large enough buffer.
        *
        * @param aDes On return, the text currently held in the editor
        * @remarks <code>Edwin()->TextLength()</code> can be called to determine 
        *          the size of buffer to allocate. If the buffer size is not 
        *          large enough, the method panics
        * @see
        */
        IMPORT_C void GetText(TDes& aDes) const;

        /**
        * Sets the text to be edited with the Combobox editor.
        *
        * @param aDes The text to be edited with the Combobox editor
        * @remarks The Combobox editor can be accessed with the 
        *          <code>Edwin()</code> method
        * @see
        */
        IMPORT_C void SetTextL(const TDesC* aDes);

        /**
        * Inserts the text held in the editor into the Combobox item array.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void InsertTextIntoArrayL();

        /**
        * Gets a pointer to the editor used to edit Combobox items.
        *
        * @return the editor used to edit Combobox items
        * @remarks
        * @see CEikEdwin in eikedwin.h
        */
        IMPORT_C CEikEdwin* Edwin()const;

        /**
        * Gets the maximum size of the Combobox item array. This is set during 
        * construction.
        *
        * @return the maximum size of the Combobox item array
        * @remarks
        * @see
        */
        IMPORT_C TInt MaxArraySize() const;

        /**
        * Sets the maximum number of user-defined items that a user can insert 
        * into the list. A value of zero value allows a user to edit all list 
        * items, including predefined ones.
        *
        * @param aMaxItems The maximum number of user-defined items that can 
        *                  be inserted in the list
        * @remarks
        * @see
        */
        IMPORT_C void SetMaxEditableUserItems(TInt aMaxItems);

        /**
        * Determines whether a message is displayed if there are no items in 
        * the pop-out listbox.
        *
        * @param aValue <code>ETrue</code> if a message should be displayed; 
        *               <code>EFalse</code> otherwise
        * @remarks By default a message is not displayed
        * @see
        */
        IMPORT_C void SetInfoPrintNothingInHistoryList(TBool aValue);

        /**
        * Returns the number of user-defined items that are currently 
        * inserted into the Combobox list.
        *
        * @return the number of user-defined items inserted into the Combobox 
        *         pop-out listbox
        * @remarks
        * @see
        */
        IMPORT_C TInt InsertedItems() const;

        /**
        * Sets the .mbg resource index for the button bitmap.
        *
        * @param aValue The .mbg resource index for the button bitmap
        * @remarks This should be either <code>EMbmSkinwidgetsComboboxup</code>,
        *          <code>EMbmSkinwidgetsComboboxdown</code> or
        *          <code>EMbmSkinwidgetsComboboxupdisabled</code>.
        *          Used internally by <code>CEikComboBox</code>
        * @see TMbmSkinwidgets in skinwidgets.mbg
        */
        IMPORT_C void SetButtonBitmapIndex(TInt aValue);

        /**
        * Closes the pop-out listbox.
        *
        * @remarks
        * @see
        */
        IMPORT_C void DestroyPopout();

    public: //** from CCoeControl *

        /**
        * Handles key events offered to the control by the control environment. 
        * A tab key press causes the pop-out listbox to be displayed.
        *
        * @param aKeyEvent The key code and modifiers
        * @param aType The type of key event: either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Constructs a Combobox from a resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>COMBOBOX</code>
        * @see CCoeControl
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Gets the minimum size for the Combobox.
        * 
        * @return the minimum size of the Combobox
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TSize MinimumSize();

        // Not available before Release 005u
        /**
        * Responds to changes of focus. This method is called when a control 
        * gains or loses focus as a result of a call to <code>SetFocus()</code>. 
        * A typical use of this method is to change the appearance of the 
        * control to indicate whether or not it has focus. 
        *
        * @param aDrawNow Contains the value that was passed to it by 
        *        <code>SetFocus()</code> 
        * @remarks 
        * @see CCoeControl
        */
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);

        // Not available before Release 005u
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

        /**
        * Prepares the Combobox for gaining focus. Implementations can take 
        * any action required, such as updating control information. By 
        * default, the implementation is empty. 
        *
        * @remarks This method is empty. Implement if inherited
        * @see CCoeControl
        */
        IMPORT_C void PrepareForFocusGainL();

        /**
        * Draws a border relative to the currently selected skin border. 
        *
        * @param aRect The outer edges of the border 
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void Draw(const TRect& aRect) const;

    protected: //** from MCoeControlObserver *

        /**
        * Handles an event from an observed control.
        * This function is called when a control for which this control is the observer calls
        * <code>CCoeControl::ReportEventL()</code>. It should be implemented by the observer control,
        * and should handle all events sent by controls it observes.
        * @param aControl The control that sent the event.
        * @param aEvent The event type.
        * @return void
        */
        IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);

    protected: //** from CCoeControl *

        /**
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SetContainerWindowL(const CCoeControl& aParent);

        /**
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TInt CountComponentControls() const;

        /**
        * @see <code>CCoeControl</code>
        */
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

        /**
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SizeChanged();

    protected: //** from MEikUpdatingBgContainerBase *

        /**
        * Displays the popout
        * @return void
        */
        IMPORT_C void HandleChangeButtonL();

        /**
        * Determins if popout is displayed
        * @return The state of the popout
        * <BR><B>Type of return value:</B> <code>TBool</code>
        * <BR><B>Range of return value:</B> <code>ETrue</code> if popout displayed and <code>EFalse</code> if popout is not on display.
        */
        IMPORT_C TBool PopupDisplayed();

    private: //** from CCoeControl *
        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2();

    private:
        void ConstructTabButtonL();
        void GetBitmapsL();
        void HandleInteractionConfirmedL();
        void CreatePopoutL();
        void DoCreatePopoutL();
        void SizeChangedL();
        void PassOnEventL(CCoeControl* aControl,MCoeControlObserver::TCoeEvent aEvent);

    protected:
        //
        CEikEdwin* iEdwin;

    protected:
        //
        CEikTextListBox* iPopout;
        //** Number of items a user has added into item array *
        TInt iInsertedItems; //** To be made private *
        //
        TInt iButtonBitmapIndex; //** To be made private *

    private:
        //
        TInt iMaxArraySize;
        //
        MDesCArray* iArray; 
        //
        TInt iComboFlags;
        //
        TInt iMaxEditableUserItems; 
    };

/**
* The <code>CEikComboBox</code> provides a Combobox that allows an item from 
* a list to be selected or a new item to be entered by a user. The available 
* items can be viewed in a pop-out listbox. 
* 
* @lib eikctl.lib
* @since SerieS90 1.0
*/
class CEikComboBox : public CEikComboBoxBC
    {
    public:

        /**
        * Completes construction of a Combobox from resource. Has an 
        * associated resource struct <code>COMBOBOX</code> and control 
        * factory identifier <code>EEikCtComboBox</code>.
        * 
        * @param aReader The resource reader
        * @see CEikComboBoxBC
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    };

/**
 * The <code>CCknComboListBox</code> class implements the listbox part of the 
 * <code>CEikComboBox</code>.
 * 
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class CCknComboListBox : public CEikTextListBox, public MEikCommandObserver
    {
    public:

        /**
        * The object destructor.
        */
        IMPORT_C ~CCknComboListBox();

        /**
        * The default object constructor.
        */
        IMPORT_C CCknComboListBox();

        /**
        * Completes construction of the pop-out listbox 
        * and sets <code>CComboListItemDrawer</code>.
        *
        * @param aParent The parent control
        * @param aFlags The pop-out listbox flags - see 
        *               <code>CEikListBox::TFlags</code>
        * @param aInsertedItems The number of user-defined items to be included 
        *                       in the pop-out listbox
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aFlags,TInt aInsertedItems);

    public: //** from CCoeControl *

        /**
        * Handles key events offered to the control by the control environment.
        *
        * @param aKeyEvent The key code and modifiers
        * @param aType The type of key event, either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this control. 
        *         <code>EKeyWasConsumed</code> if the control takes action on the 
        *         key event; <code>EKeyWasNotConsumed</code> otherwise
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

        /**
        * Activates and sets the control as ready to be drawn.
        * 
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void ActivateL();

    protected:

        /**
        * This function is used to create a CBA for the control.
        */
        IMPORT_C void CreateButtonGroupContainerL();

    protected: //** from MEikCommandObserver *

        /**
        * This function used to support button group command handling.
        * @param aCommandId The command to handle.
        */
        IMPORT_C void ProcessCommandL(TInt aCommandId);

    private:
        CEikButtonGroupContainer *iButtonGroupContainer;
    };

/**
 * The <code>CComboListItemDrawer</code> class is the item drawer class 
 * specific to <code>CCknComboListBox</code>. This class is used by 
 * <code>CCknComboListBox</code> to emphasize user-defined list items.
 * The method currently separates user-defined items from predefined items
 * with a line.
 * 
 * @since Series90 1.0
 * @lib eikctl.lib
 */
class CComboListItemDrawer : public CTextListItemDrawer
    {
    public:

        /**
        * The object destructor.
        */
        IMPORT_C ~CComboListItemDrawer();

        /**
        * The default object constructor.
        *
        * @param aTextListBoxModel The data model to get the listbox items from
        * @param aFont The font to use to draw the listbox items
        * @param aInsertedItems Extra items that are not in the data model to 
        *                       add to the listbox
        * @remarks
        * @see CFont in gdi.h
        */
        IMPORT_C CComboListItemDrawer(
                                MTextListBoxModel* aTextListBoxModel, 
                                const CFont* aFont, 
                                TInt aInsertedItems);

        /**
        * This method is called by <code>CListItemDrawer::DrawItem()</code>
        * with appropriate arguments. Its purpose is to draw the actual item - 
        * everything other than the item mark - into the graphics context.
        * The graphics context is set in <code>CTextListItemDrawer</code>.
        *
        * @param aItemIndex The listbox item to draw
        * @param aActualItemRect Where the listbox item should be drawn
        * @param aItemIsCurrent <code>ETrue</code> if the listbox item is the 
        *                       current item
        * @param aViewIsEmphasized <code>ETrue</code> if the listbox item is 
        *                          emphasized
        * @param aViewIsDimmed <code>ETrue</code> if the listbox item is dimmed
        * @param aItemIsSelected <code>ETrue</code> if the listbox item is 
        *                        selected
        * @remarks
        * @see 
        */
        IMPORT_C virtual void DrawActualItem(
                                    TInt aItemIndex, 
                                    const TRect& aActualItemRect, 
                                    TBool aItemIsCurrent, 
                                    TBool aViewIsEmphasized, 
                                    TBool aViewIsDimmed,
                                    TBool aItemIsSelected) const;

    private:
        TInt iInsertedItems;
    };


#endif //** EIKCMBOX_H *

//** End of File *
