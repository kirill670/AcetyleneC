/*
* ==============================================================================
*  Name        : cknphonenumbereditor.h
*  Part of     : CKON
*  Interface   : Telephone Number API
*  Description : Telephone number editor.
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

#ifndef CKNPHONENUMBEREDITOR_H
#define CKNPHONENUMBEREDITOR_H


// INCLUDES
#include <eikedwin.h>

// CLASS DECLARATIONS

/**
 * The <code>CCknPhoneNumberEditor</code> class provides the North American 
 * formatted Telephone Number Editor. This is a text editor derived from 
 * <code>CEikEdwin</code>, which is intended specifically for editing 
 * North American telephone numbers. This Telephone Number Editor has only one 
 * mode, unlike <code>CEikTelephoneNumberEditor</code>, which is not related 
 * to this class.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknPhoneNumberEditor : public CEikEdwin
    {
    public:
    // Constructors and destructor

        /**
        * Creates a new <code>CCknPhoneNumberEditor</code> object. 
        * 
        * @return A pointer to a newly created <code>CCknPhoneNumberEditor</code> object
        * @remarks This method leaves if there is not enough memory to create 
        *          this object
        * @see
        */
        IMPORT_C static CCknPhoneNumberEditor* NewL();

        /**
        * Creates a new <code>CCknPhoneNumberEditor</code> object.
        * 
        * @param aWidth The width in characters.
        * @param aFormatNumber A flag to set the formatting of the telephone 
        *                      number to North American format. This flag is 
        *                      set to <code>ETrue</code> by default. To stop 
        *                      the telephone number being formatted, set this 
        *                      flag to <code>EFalse</code>
        * @return A pointer to a newly created <code>CCknPhoneNumberEditor</code> object
        * @remarks This method leaves if there is not enough memory to create 
        *          this object
        * @see
        */
        IMPORT_C static CCknPhoneNumberEditor* NewL(TInt aWidth, bool aFormatNumber = true);

        /**
        * The object destructor.
        */
        IMPORT_C ~CCknPhoneNumberEditor();


    // New methods
        
        /**
        * Formats a supplied telephone number to the North American format.
        * It removes inappropriately placed spaces and inserts spaces where 
        * required. The first digit(s) are taken into account when performing 
        * the format, for example, "1234567890" becomes "1 234 567 890".
        *
        * @param aCursorPos The cursor position in the text
        * @param aPhoneNumber The text containing the telephone number
        * @remarks
        * @see
        */
        IMPORT_C static void FormatNATelephoneNumberString(TInt& aCursorPos, TPtrC& aPhoneNumber);

        /**
        * Constructs a North American formatted Telephone Number Editor from a 
        * resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>PHONENUMBER</code>
        * @see <code>CCoeControl</code> in coecntrl.h
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, one of: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code>,<code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see <code>CCoeControl</code> in coecntrl.h
        * @see <code>TEventCode</code> in w32std.h
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Returns the input capabilities of the North American formatted
        * Telephone Number Editor. Typically, called by the FEP-aware editor. 
        * By default, the Telephone Number Editor is capable of handling 
        * <code>TCoeInputCapabilities::EDialableCharacters</code>
        * and <code>TCoeInputCapabilities::ENavigation</code>
        *
        * @return the input capabilities
        * @remarks
        * @see <code>CCoeControl</code> in coecntrl.h
		* @see <code>TCoeInputCapabilities</code> in coecntrl.h
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;

    protected:  // Methods

        /**
        * Constructor.
        */
        IMPORT_C CCknPhoneNumberEditor();

        /**
        * Second-phase constructor.
        * @param aWidth Editor's width.
        * @param aFormatNumber If it's set true (default), it formats the phone number on key events.
        */
        IMPORT_C void ConstructL(TInt aWidth, bool aFormatNumber);

    private:
        TBool IsValidPhoneNumberCharacter(TChar aCharacter);
        TInt KeyEventCode(const TKeyEvent &aKeyEvent) const;
        void ClipboardL(TClipboardFunc aClipboardFunc);
        TBool IsSpecialCharacter(TChar aCharacter);
    private:     // Data
        bool iFormatNumber;
        HBufC* iSpecialCharacters;
        void* iReserved;
    };


#endif      // CKNPHONENUMBEREDITOR_H               
// End of File
