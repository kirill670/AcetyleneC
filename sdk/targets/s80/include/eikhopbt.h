/*
* ==============================================================================
*  Name        : eikhopbt.h
*  Part of     : CKON
*  Interface   : Option Button API
*  Description : CEikLabeledOptionButton class creates a labelled option button.
*                CEikHorOptionButtonList class creates horizontal radio buttons.
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


#ifndef EIKHOPBT_H
#define EIKHOPBT_H

// INCLUDES
#include <coecntrl.h>
#include <eikbutb.h>

// FORWARD DECLARATIONS
class CEikOptionButton;
class CEikLabel;

/**
 * The <code>CEikLabeledOptionButton</code> class creates a labeled Option 
 * Button.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class CEikLabeledOptionButton : public CEikButtonBase 
    {
    public:

        /**
        * The default object constructor.
        */
        IMPORT_C CEikLabeledOptionButton();

        /**
        * The object constructor.
        *
        * @param aId The Option Button's ID
        * @param aTextOnRight <code>ETrue</code> to place the Option Button's 
        *                     label on the right; <code>EFalse</code> to place 
        *                     it on the left
        * @remarks
        * @see
        */
        IMPORT_C CEikLabeledOptionButton(TInt aId,TBool aTextOnRight);

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikLabeledOptionButton();

        /**
        * Completes construction of the Option Button object.
        *
        * @param aContainer The button's container window
        * @param aCoordinator The button's coordinator
        * @param aText The text for the button's label
        * @remarks
        * @see <code>CCoeControl</code> (coecntl.h), 
        *      <code>TEikButtonCoordinator</code> (eikbutb.h)
        */
        IMPORT_C void ConstructL(const CCoeControl& aContainer,TEikButtonCoordinator& aCoordinator,const TDesC& aText);

        /**
        * Gets the button's ID.
        *
        * @return the button's ID
        * @remarks
        * @see
        */
        IMPORT_C const TInt Id();
    public: // from CCoeControl

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see <code>CCoeControl</code> (coecntl.h)
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

        /**
        * Handles a change to the control's resources that are shared across 
		* the environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @return
        * @remarks
        * @see <code>CCoeControl</code> (coecntl.h)
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u
    private: // framework
        IMPORT_C void SizeChanged();
        IMPORT_C TSize MinimumSize();
        IMPORT_C TInt CountComponentControls() const;
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
        IMPORT_C void StateChanged();
    private:
        TInt iId;
        CEikOptionButton* iButton;
        CEikLabel* iLabel;
        TBool iTextOnRight;
    };
             
/**
 * The <code>CEikHorOptionButtonList</code> creates a set of Option Buttons 
 * (or radio buttons) that are displayed horizontally. Only one button can be 
 * selected at any one time. This class is not intended for developer 
 * derivation.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class CEikHorOptionButtonList : public CCoeControl ,public MCoeControlObserver
    {
    public:

        /**
        * The object constructor.
        *
        * @param aInterButtonSpacing The spacing between Option Buttons
        * @param aTextOnRight <code>ETrue</code> to display the button's text 
        *                     to the right of each button; <code>EFalse</code> 
        *                     to display it to the left
        * @remarks
        * @see 
        */
        IMPORT_C CEikHorOptionButtonList(TInt aInterButtonSpacing,TBool aTextOnRight);

        /**
        * The default object constructor.
        */
        IMPORT_C CEikHorOptionButtonList();

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikHorOptionButtonList();

        /**
        * Completes construction of an Option Button object.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(); 

        /**
        * Constructs an Option Button from a resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>HOROPBUT</code> (eikon.hrh)
        * @see <code>CCoeControl</code> (coecntl.h),
        *      <code>TResourceReader</code> (barsread.h)
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader &aReader);
    public: 

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see <code>CCoeControl</code> (coecntl.h)
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

        /**
        * Handles a change to the control's resources that are shared across 
		* the environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @return
        * @remarks
        * @see <code>CCoeControl</code> (coecntl.h)
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u
    public:

        /**
        * Handles a control event.
        *
        * @param aControl The button receiving the event
        * @param aEvent The event can be: <code>EEventRequestExit</code>, 
        *               <code>EEventRequestCancel</code>, 
        *               <code>EEventRequestFocus</code>, 
		*               <code>EEventPrepareFocusTransition</code>, 
        *               <code>EEventStateChanged</code> or 
		*               <code>EEventInteractionRefused</code>
        * @remarks
        * @see <code>MCoeControlObserver</code> (coecobs.h)
        * @see <code>CCoeControl</code> (coecntl.h)   
        */
        IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
    public:// framework

        /**
        * Gets the number of Option Buttons in the button list.
        *
        * @return the number of Option Buttons
        * @remarks
        * @see
        */
        IMPORT_C TInt CountComponentControls() const;

        /**
        * Gets a specified Option Button from the button list.
        *
        * @param aIndex The index of the Option Button to return
        * @return the button at the specified index
        * @remarks
        * @see
        */
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;

        /**
        * Gets the minimum size of the control.
        *
        * @return the control's minimum size
        * @remarks
        * @see
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see <code>CCoeControl</code> (coecntl.h)
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Handles a change in the control's size.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void SizeChanged();

        /**
        * Returns the input capabilities of the Option Button. Typically, 
        * called by the FEP-aware [what]. By default, the Option Button is 
        * capable of handling [what]. 
        *
        * @return the input capabilities
        * @remarks
        * @see <code>CCoeControl</code> (coecntl.h)
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;
    public: // new functions

        /**
        * Adds an Option Button to a horizontal Option Button list.
        *
        * @param aId The Option Button's ID
        * @param aDes The Option Button's text label
        * @remarks
        * @see
        */
        IMPORT_C void AddOptionButtonL( TInt aId,const TDesC& aDes);

        /**
        * Sets the specified Option Button as selected.
        *
        * @param aId The ID of the button to set as selected
        * @remarks
        * @see
        */
        IMPORT_C void SetButtonById(TInt aId);

        /**
        * Gets the selected Option Button's ID.
        *
        * @return the ID of the currently selected Option Button
        * @remarks
        * @see
        */
        IMPORT_C TInt LabeledButtonId();
    private: // from CCoeControl
        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2(); 
    private:
        TEikButtonCoordinator iCoordinator;
        TBool iTextOnRight;
        TInt iInterButtonSpacing;
        TInt iButtonId;
        CArrayFix<CEikLabeledOptionButton*> *iOptionButtonArray;
    };


#endif  // EIKHOPBT_H

// End of File
