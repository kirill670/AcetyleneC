/*
* ==============================================================================
*  Name        : eiklbbut.h
*  Part of     : CKON
*  Interface   : Labeled button API
*  Description : CEikLabeledButton implements a command button with a label.
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


#ifndef EIKLBBUT_H
#define EIKLBBUT_H

// INCLUDES
#include <coecntrl.h>
#include <coecobs.h>

// FORWARD DECLARATIONS
class CEikCommandButtonBase;
class CEikLabel;

/**
* The <code>CEikLabeledButton</code> class implements a command button with a 
* label. A Labeled Button displays text only, and has no picture associated 
* with it. A hotkey code can be assigned to the button, but this has no effect 
* in Series 90 as hotkeys are not supported
* 
* @lib eikcoctl.lib
* @since 6.0
*/
class CEikLabeledButton : public CCoeControl, private MCoeControlObserver
    {
    public:
        /**
         * The enumeration <code>TFlags</code> specifies the flags to control 
         * whether hotkeys are displayed on the button.
         */
        enum TFlags
            {
            /** hotkeys for commands are displayed */
            EShowHotKey     =0x01,  
            /** hotkeys for commands are not displayed */
            EPlainHotKey    =0x02   
            };

        /**
        * The default object constructor. This method starts construction. 
        * It sets the Labeled Button to inherit the visibility of its owner.
        * 
        * @remarks
        * @see
        */
        IMPORT_C CEikLabeledButton();

        /**
        * The object destructor. Removes the button and its label.
        */
        IMPORT_C ~CEikLabeledButton();

        /**
        * Completes construction of a Labeled Button object.
        * 
        * @param aButton The button for which construction is completed
        * @param aHotKeyCode The hotkey code for the button
        * @param aFlags Flags for the button that determine whether the hotkey
        *               code is displayed
        * @remarks Parameters aHotKeyCode and aFlags have no effect as hotkeys 
        *          are not supported in Series 90
        * @see
        */
        IMPORT_C void ConstructL(CEikCommandButtonBase* aButton,TInt aHotKeyCode,TInt aFlags);
        
        /**
        * Gets a pointer to the Labeled Button.
        * 
        * @return a pointer to the button
        * @remarks
        * @see
        */
        IMPORT_C CEikCommandButtonBase* Button() const;
        
        /**
        * Gets the button's label.
        * 
        * @return a pointer to the button's label
        * @remarks
        * @see
        */
        IMPORT_C CEikLabel* Label() const;
        
        /**
        * Gets the button's hotkey code.
        * 
        * @return the button's hotkey code
        * @remarks Hotkeys are not supported in Series 90
        * @see
        */
        IMPORT_C TInt HotKeyCode() const;
        
        /**
        * Determines whether the button displays hotkeys for commands 
        * 
        * @return <code>ETrue</code> if the button displays
        *         hotkeys for commands; <code>EFalse</code> 
        *         otherwise
        * @remarks Hotkeys are not supported in Series 90
        * @see
        */
        IMPORT_C TBool ShowsHotKey() const;

        /**
        * Determines whether the button is set so that hotkeys for commands 
        * are not displayed.
        * 
        * @return <code>ETrue</code> if the button is set so that
        *         hotkeys for commands are not displayed; <code>EFalse</code> 
        *         otherwise
        * @remarks Hotkeys are not supported in Series 90
        * @see
        */
        IMPORT_C TBool PlainHotKey() const;

        /**
        * Animates the button so that it appears to be pressed then released.
        * 
        * @remarks This method only affects the appearance of the button - 
        *          the command ID for the button is not generated.
        * @see
        */
        IMPORT_C void Animate();

        /**
        * Sets the button's hotkey code and the flags that determine whether 
        * the hotkey code is displayed.
        * 
        * @param aKeyCode The button's new hotkey code
        * @param aFlags The flags that determine whether the hotkey code is 
        *               displayed
        * @remarks This method has no effect as hotkeys 
        *          are not supported in Series 90
        * @see
        */
        IMPORT_C void UpdateHotKey(TInt aKeyCode,TFlags aFlags);
    public: 

        /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, either: <code>EEventKey</code>, 
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
        * Constructs a Labeled Button from a resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>LBBUT</code>
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
        
        /**
        * Gets the minimum size required to display the button. This includes 
        * the space required to display the button's margins and label.
        * 
        * @return the minimum size of the Labeled Button
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize();
        
        /**
        * Sets the button's containing window. This method copies the 
        * containing window and control context from <code>aContainer</code>.
        * 
        * @param aContainer The control from which the containing window and 
        *                   control context are copied
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);
        
        /**
        * Sets the button's dimmed state.
        * 
        * @param aDimmed <code>ETrue</code> to set the button as dimmed;
        *           <code>EFalse</code> to set the button as not dimmed
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SetDimmed(TBool aDimmed);
        
        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
        
        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void HandleResourceChange(TInt aType);

        /**
        * Returns the input capabilities of the Labeled Button. Typically, 
        * called by the FEP-aware text editor. By default, the Labeled Button
        * is capable of handling navigation keys such as arrow keys, page-up,
        * page-down, home, end and tab. 
        *
        * @return the input capabilities
        * @remarks
        * @see <code>CCoeControl</code>; <code>TCoeInputCapabilities</code> in
        *      <code>coeinput.h</code>
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;
    protected: 

        /**
        * Writes the internal state of the control and its components to 
        * <code>aWriteStream</code>.
        *
        * @param aWriteStream The write stream
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

    private:
        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt aIndex) const;
        void SizeChanged();
        void Reserved_2();
    private:
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
    private:
        void CreateLabelL();
        void UpdateHotKeyL();
    private:
        CEikCommandButtonBase* iButton;
        CEikLabel* iLabel;
        TInt iHotKeyCode;
        TInt iLButFlags;
    };


#endif  // EIKLBBUT_H

// End of File
