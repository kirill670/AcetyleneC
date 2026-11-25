/*
* ==============================================================================
*  Name        : eikfpne.h
*  Part of     : CKON
*  Interface   : Floating Point Editor API
*  Description : Editor for floating point numbers
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

#ifndef EIKFPNE_H
#define EIKFPNE_H


//  INCLUDES
#include <eikedwin.h>

// CLASS DECLARATION

/**
* The <code>CEikFloatingPointEditor</code> class creates a Floating Point Editor. 
* The editor can accept floating point values. The minimum and maximum values 
* for the editor can be specified.
*
* @lib eikctl.lib
* @since Series90 1.0
*/
class CEikFloatingPointEditor : public CEikEdwin
    {
    public:  // Methods

    // Constructors and destructor

        /**
        * The default object constructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C CEikFloatingPointEditor();

    // New methods

        /**
        * Completes construction of a Floating Point Editor object.
        *
        * @param aMin The minimum value
        * @param aMax The maximum value
        * @param aTextLimit Text length limit
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(const TReal& aMin,const TReal& aMax,TInt aTextLimit);

        /**
        * Gets the value currently in the editor.
        *
        * @return The current value
        * @remarks
        * @see
        */
        IMPORT_C TReal Value() const;

        /**
        * Sets the value for the editor. Clears the editor if a null pointer is
        * given as a parameter.
        *
        * @param aValue The new value
        * @remarks
        * @see
        */
        IMPORT_C void SetValueL(const TReal* aValue);

        /**
        * Sets the minimum and maximum values permissible in the editor.
        *
        * @param aMin The minimum value
        * @param aMax The maximum value
        * @remarks
        * @see
        */
        IMPORT_C void SetMinMax(TReal aMin,TReal aMax);

        /**
        * Gets the minimum and maximum values in the relevant parameters.
        *
        * @param aMin On return, contains the minimum value
        * @param aMax On return, contains the maximum value
        * @remarks
        * @see
        */
        IMPORT_C void GetMinMax(TReal& aMin,TReal& aMax) const;

    // Methods from base classes

        /**
        * Constructs a Floating Point Editor from a resource.
        *
        * @param aReader A resource reader
        * @remarks The resource type is <code>FLPTED</code> 
        * @see CCoeControl
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Prepares the editor for loss of focus. 
        * The method checks that the number is valid and between the minimum 
        * and maximum values. If the minimum and maximum values are exceeded 
        * or if the number is not correct, it leaves and displays an infoprint. 
        * 
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void PrepareForFocusLossL();

        /**
        * Handles key events offered to the control by the control environment.
        * If the validate key is pressed, the method reformats the contents of 
        * the Floating Point Editor by calling <code>PrepareForFocusLossL</code>. 
        * Otherwise, it offers the key pressed to Edwin.
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
        * Returns the input capabilities of the Floating Point Editor. 
        * Typically, called by the FEP-aware text editor. By default, the 
        * Floating Point Editor is capable of handling all text input. 
        *
        * @return the input capabilities
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;

    private:    // Data

        /** The current value */
        TReal iValue;

        /** The minimum allowable value */
        TReal iMin;

        /** The maximum allowable value */
        TReal iMax;

    };

/**
* The <code>CEikFixedPointEditor</code> class creates a Fixed Point Editor 
* that accepts values to a fixed decimal place. 
* The application can specify the minimum and maximum values.
*
* @lib eikctl.lib
* @since Series90 1.0
*/
class CEikFixedPointEditor : public CEikEdwin
    {
    public:  // Methods

    // Constructors and destructor

        /**
        * The default object constructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C CEikFixedPointEditor();

    // New methods
        /**
        * Completes construction of a Fixed Point Editor object.
        * 
        * @param aMin The minimum value 
        * @param aMax The maximum value
        * @remarks The <code>aMin</code> and <code>aMax</code> values are 
        *          calculated by taking the desired value and removing the 
        *          decimal point (multiplying by 10 to the power to the number 
        *          of decimal places). These values must not exceed the 
        *          minimum and maximum integer values
        * @see
        */
        IMPORT_C void ConstructL(TInt aMin,TInt aMax);

        /**
        * Gets the value currently in the editor.
        *
        * @return the current value
        * @remarks The value is an integer multiplied by 10 to the power,
        *          to the number of decimal places
        * @see
        */
        IMPORT_C TInt Value() const;

        /**
        * Sets the value for the Fixed Point Editor. This method clears the 
        * editor if a null pointer is given as parameter.
        *
        * @param aValue The new value
        * @remarks This must be the desired value times 10 to the power, to 
        *          the number of decimal places. It must not exceed the 
        *          minimum and maximum integer values
        * @see
        */
        IMPORT_C void SetValueL(const TInt* aValue);

        /**
        * Sets the minimum and maximum values for the Fixed Point Editor.
        *
        * @param aMin The minimum value
        * @param aMax The maximum value
        * @remarks
        * @see
        */
        IMPORT_C void SetMinMax(TInt aMin, TInt aMax);

        /**
        * Returns the minimum and maximum values in the relevant parameters.
        *
        * @param aMin On return, contains the minimum value
        * @param aMax On return, contains the maximum value
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void GetMinMax(TInt& aMin, TInt& aMax) const;

        /**
        * Sets the number of decimal places for the Fixed Point Editor.
        *
        * @param aDecimalPlaces The number of decimal places to use
        * @remarks
        * @see
        */
        IMPORT_C void SetDecimalPlaces(TInt aDecimalPlaces);

        /**
        * Returns the number of decimal places used.
        *
        * @return the number of decimal places
        * @remarks
        * @see
        */
        IMPORT_C TInt DecimalPlaces() const;

    // Methods from base classes

        /**
        * Constructs a Fixed Point Editor from a resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>FIXPTED</code> 
        * @see CCoeControl
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Prepares the editor for loss of focus. 
        * The method checks that the number is valid and between the minimum 
        * and maximum values. If the minimum and maximum values are exceeded 
        * or if the number is not correct, it leaves and displays an infoprint. 
        * 
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void PrepareForFocusLossL();

        /**
        * Handles key events offered to the control by the control environment. If 
        * the Enter key is pressed, it validates the contents of the Fixed 
        * Point Editor. Otherwise, it offers the key pressed to Edwin.
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
        * Returns the input capabilities of the Fixed Point Editor. Typically,
        * called by the FEP-aware text editor. By default, the editor is 
        * capable of handling all text input. 
        *
        * @return the input capabilities
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;

    private:  // Methods

        /**
        * Required number of characters for value to be valid.
        *
        * @return the required number of characters
        */
        TInt RequiredNumberOfCharacters() const;

    private:  // Data

        /** The current value */
        TInt iValue;

        /** The minimum allowable value */
        TInt iMin;

        /** The maximum allowable value */
        TInt iMax;

        /** The required number of decimal places */
        TInt iDecimalPlaces;
    };

/**
* The <code>CEikTwipsEditor</code> class creates a Twips Editor. The Twips 
* Editor stores values corresponding to an 
* imperial or metric value entered by the user.
*
* @lib eikctl.lib
* @since Series90 1.0
*/
class CEikTwipsEditor : public CEikEdwin
    {
    public:  // Methods

    // Constructors and destructor

        /**
        * The default object constructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C CEikTwipsEditor();

    // New methods
        /**
        * Completes construction of a new Twips Editor. 
        * The method initializes its heap-stored members from the supplied 
        * arguments. This method leaves if any of the pointer members being 
        * constructed leave. 
        * 
        * @param aMin The minimum value
        * @param aMax The maximum value
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(TInt aMin,TInt aMax);

        /**
        * Gets the value currently in the Twips Editor.
        *
        * @return the current value
        * @remarks
        * @see
        */
        IMPORT_C TInt Value() const;

        /**
        * Sets the value for the Twips Editor. The method clears the Twips 
        * Editor if a null pointer is given as parameter.
        *
        * @param aValue The new value
        * @remarks
        * @see
        */
        IMPORT_C void SetValueL(const TInt* aValue);

        /**
        * Sets the minimum and maximum values for the Twips Editor.
        *
        * @param aMin The minimum allowable value
        * @param aMax The maximum allowable value
        * @remarks
        * @see
        */
        IMPORT_C void SetMinMax(TInt aMin, TInt aMax);

        /**
        * Returns the minimum and maximum values in the relevant parameters.
        *
        * @param aMin On return, contains the minimum value
        * @param aMax On return, contains the maximum value
        * @remarks
        * @see
        */
        IMPORT_C void GetMinMax(TInt& aMin, TInt& aMax) const;

        /**
        * Sets the units used.
        *
        * @param aUnitsFormat The unit format to use, metric or imperial. The 
        *        default is imperial 
        * @remarks 
        * @see
        */
        IMPORT_C void SetUnits(TUnitsFormat aUnitsFormat);

        /**
        * Reports the unit format used, metric or imperial.
        *
        * @return the unit format
        * @remarks
        * @see
        */
        IMPORT_C TUnitsFormat Units();

    // Methods from base classes

        /**
        * Constructs a Twips Editor from a resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>TWIPSED</code>
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Prepares the Twips Editor for loss of focus. The method checks that 
        * the number is valid and between the minimum and maximum values. If 
        * the minimum and maximum values are exceeded or if the number is not 
        * correct, it leaves and displays an infoprint. 
        * 
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual void PrepareForFocusLossL();

        /**
        * Handles key events offered to the control by the control environment.
        * If the validate key is pressed, then reformats the contents of the 
        * Twips Editor by calling <code>PrepareForFocusLossL()</code>. 
        * Otherwise, it offers the key pressed to Edwin.
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
        * Returns the input capabilities of the Twips Editor. Typically, called 
        * by the FEP-aware text editor. By default, the Twips Editor is capable 
        * of handling all text input. 
        *
        * @return the input capabilities
        * @remarks Changing the locale setting may well change the character
        *          used as the decimal separator
        * @see CCoeControl
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;

    private:  // Methods

        /**
        * Locate a key from a key event in the buffer.
        *
        * @param aKeyEvent the key event
        * @return the index of the character
        */
        TInt KeyEventCode(const TKeyEvent &aKeyEvent) const;

        /**
        * Handle clipboard capabilities
        *
        * @param aClipboardFunc The clipboard command
        */
        void ClipboardL(TClipboardFunc aClipboardFunc);

        /**
        * Required number of characters for value to be valid.
        *
        * @return the required number of characters
        */
        TInt RequiredNumberOfCharacters() const;

        /**
        * Returns true if the character is valid for this editor
        *
        * @param aCharacter the character to test
        * @return TRUE if the character is valid, FALSE otherwise.
        */
        bool ValidCharacterL(TChar aCharacter);

    private:  // Data

        /** The current value */
        TInt iValue;

        /** The minimum allowable value */
        TInt iMin;

        /** The maximum allowable value */
        TInt iMax;

        /** The units format used */
        TUnitsFormat iUnits;
    };



/**
* The <code>Twips</code> class is a utility class that converts twips to strings 
* and strings to twips. The class contains static methods for converting twips 
* values to strings with given string formats.
*
* @lib eikctl.lib
* @since Series90 1.0
*/
class Twips
    {
    public:

        /**
        * Converts a twips value to a string using locale information to 
        * determine the units.
        *
        * @param aTwips The <code>TInt</code> twips value
        * @param aDecimalPlaces The number of decimal places to display
        * @param aDes The resulting string
        * @remarks
        * @see
        */
        IMPORT_C static void TwipsToString(TInt aTwips, TInt aDecimalPlaces, TDes& aDes);

        /**
        * Converts a string to a twips value using locale information to 
        * determine the units.
        *
        * @param aDes The string
        * @param aTwips The twips value
        * @return <code>ETrue</code> if the string is valid; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C static TBool StringToTwips(const TDes& aDes, TInt& aTwips);

        /**
        * Convert a twips value to a string using units passed as a parameter.
        *
        * @param aTwips The <code>TInt</code> twips value
        * @param aUnitsFormat The format for the conversion
        * @param aDecimalPlaces The number of decimal places to display
        * @param aDes The resulting string
        * @remarks
        * @see
        */
        IMPORT_C static void TwipsToString(TInt aTwips, TUnitsFormat aUnitsFormat, TInt aDecimalPlaces, TDes& aDes);

        /**
        * Convert a string to a twips value using units passed as a parameter.
        *
        * @param aDes The string
        * @param aUnitsFormat The format for the conversion
        * @param aTwips The <code>TInt</code> twips value
        * @return <code>ETrue</code> if the string is valid; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C static TBool StringToTwips(const TDes& aDes, TUnitsFormat aUnitsFormat, TInt& aTwips);
    };

#endif      // EIKFPNE_H

// End of File

