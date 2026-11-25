/*
* ==============================================================================
*  Name        : eikopbut.h
*  Part of     : CKON
*  Interface   : Option Button API
*  Description : CEikOptionButton class creates an option button control.
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


#ifndef EIKOPBUT_H
#define EIKOPBUT_H

// INCLUDES
#include <eikbutb.h>
#include <gulbordr.h>

// FORWARD DECLARATIONS
class CCknOptionButtonExtension;


/**
 * The <code>CEikOptionButton</code> class creates an Option Button control. 
 * An Option Button can be used to create a list of Option Buttons. The 
 * difference between this and radio buttons is that radio buttons are 
 * mutually exclusive. Option buttons should be used when one or more options 
 * can be selected from the list.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class CEikOptionButton : public CEikButtonBase
    {
    public:

        /**
        * The default object constructor.
        */
        IMPORT_C CEikOptionButton();

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikOptionButton();

        /**
        * Starts the two-phase object construction.
        * 
        * @remarks
        * @see
        */
        IMPORT_C static CEikOptionButton* NewL();

        /**
        * Constructs an Option Button from a resource file. The resource ID is 
        * <code>EEikCtOptionButton</code>. It does not need the resource 
        * structure.
        *
        * @param aReader A resource reader
        * @remarks
        * @see <code>TResourceReader</code> (barsread.h)
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    public: // framework

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
        * Gets the minimum size for the Option Button.
        * 
        * @return the minimum size of the Option Button
        * @remarks
        * @see <code>CCoeControl</code> (coecntl.h)
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Draws the Option Button control.
        *
        * @param aRect The rectangle to be redrawn. This parameter is ignored 
        *              in this implementation
        * @remarks
        * @see <code>TRect</code> (e32std.h)
        */
        IMPORT_C void Draw(const TRect& /*aRect*/) const;

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

        /**
        * Returns the input capabilities of the Option Button. Typically 
        * called by the FEP-aware [what]. By default, the Option Button is 
        * capable of handling [what]. 
        *
        * @return the input capabilities
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;
    protected:

        /**
        * Second phase constructor.
        * @return void
        */
        IMPORT_C void ConstructL();
    private:
        TAny* iDummy[5];      // Pad out to same size as old version for BC
    };




#endif  // EIKOPBUT_H

// End of File
