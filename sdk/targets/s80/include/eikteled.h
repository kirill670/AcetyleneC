/*
* ==============================================================================
*  Name        : eikteled.h
*  Part of     : CKON
*  Interface   : Telephone Number API
*  Description : Telephone number editor control
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

#ifndef EIKTELED_H
#define EIKTELED_H


// INCLUDES
#include <eikedwin.h>
#include <t32wld.h>
#include <eikon.hrh>

// CONSTANTS
/** 
 * represents the total number of parts that make up the whole 
 * number, that is, country, area, and number 
 */
const TInt KTelephoneNumberEditorPartTotal=3;
/** the maximum number of characters in each part prompt */
const TInt KTelephoneNumberEditorPromptMaxChars=20;

// FORWARD DECLARATIONS
class CEikTelephoneNumberEditorExtra;


// CLASS DECLARATIONS

/**
*  Editor that accepts phone numbers to be inputed.
*
*  This control is maintained for backward compatibility. Use the CEikTelephoneNumberEditor
*  class instead.
*  @internal
*  @lib eikctl.lib
*/
class CEikTelephoneNumberEditorBC : public CEikEdwin
    {
    public:  // Declarations
    enum TTelephoneEditorModeBC
        {
        ECoerceFormat=EEikTelephoneNumberEditorModeCoerceFormat,
        EFreeFormat=EEikTelephoneNumberEditorModeFreeFormat
        };

    public:
    // Constructors and destructor
        /**
        * C++ default constructor.
        */
        IMPORT_C CEikTelephoneNumberEditorBC();


        /**
        * Destructor.
        */
        IMPORT_C ~CEikTelephoneNumberEditorBC();


    // New methods
        
        /**
        * Second-phase constructor
        * @param aMode The editor mode.
        * @param aFlags The editor flags.
        * @param aPromptArray The pointer to the prompt array.
        * @param aWidth Editor's width.
        */
        IMPORT_C void ConstructL(TTelephoneEditorModeBC aMode, TInt aFlags, TPtrC* aPromptArray, TInt aWidth);

        /**
        * Second-phase constructor
        * @param aMode The editor mode.
        * @param aFlags The editor flags.
        * @param aPromptArray The pointer to the prompt array.
        * @param aWidth Editor's width.
        * @param aMaxChars Pointer to the max chars.
        */
        IMPORT_C void ConstructL(TTelephoneEditorModeBC aMode, TInt aFlags, TPtrC* aPromptArray, TInt aWidth, const TInt* aMaxChars);

        /**
        * CEikEdwin
        * Handles cut, copy and paste commands.
        * @param aClipboardFunc Clipboard operation.
        */
        IMPORT_C void ClipboardL(TClipboardFunc aClipboardFunc);

        /**
        * Sets the editor mode.
        * @param aMode The editor mode (ECoerceFormat, EFreeFormat).
        */
        IMPORT_C void SetModeL(TTelephoneEditorModeBC aMode);

        /**
        * Sets the number. Takes string as paramete.
        * Parse the provided number, filling in any blanks and removing
        * obsolete bits, and set the control.
        * @param aNumber The number to be set.
        */
        IMPORT_C void SetNumberL(const TDesC& aNumber);

        /**
        * Sets the number. Takes country, area and number strings as a parameter.
        * @param aCountry Country code.
        * @param aArea Area code.
        * @param aNumber Tele number.
        */
        IMPORT_C void SetNumberL(const TDesC& aCountry, const TDesC& aArea, const TDesC& aNumber);

        /**
        * Gets the number from the editor. Removes the any blank strings.
        * @param aNumber On return, gets phone number in the editor.
        */
        IMPORT_C void GetNumber(TDes& aNumber) const;

        /**
        * Gets the number from the editor. Removes the any blank strings.
        * @param aCountry Country code to be copied.
        * @param aArea Area code to be copied.
        * @param aNumber Number to be copied.
        */
        IMPORT_C void GetNumber(TDes& aCountry, TDes& aArea, TDes& aNumber);

        /**
        * Clear the contents of number editor.
        */
        IMPORT_C void BlankNumberL();

        /**
        * Set the maximum characters for this editor.
        * @param aMaxChars Pointer to TInt which content is the max char. 
        */
        IMPORT_C void SetMaxChars(const TInt* aMaxChars);

        /**
        * From CCoeControl
        * Handles the key event.
        * @param aKeyEvent The key event.
        * @param aType Event type.
        * @return Suitable event code.
        * <BR><B>Type of return value:</B> TKeyResponse
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Second-phase constructor from resource.
        * @param aReader Resource reader.
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * From CCoeControl
        * Handles pointer events.
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * From CCoeControl
        * Response to focus changed.
        */
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);

        /**
        * Gets the list of logical colours used to draw the control. 
        * The list includes an explanation of how each colour is used.
        * By default, this function has an empty implementation. 
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

        /**
        * From CCoeControl 
        * Handles a change to the control's resources.
        * @param aType A message UID value.
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u

        /**
        * Returns telephone number editor input capabilities
        * @return Telephone number editor input capabilities
        * <BR><B>Type of return value:</B> TCoeInputCapabilities
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;

    private:  // Declarations
        enum TPositionInPart
            {
            EStart=0,
            EMiddle=1,
            EEnd=2
            };
        enum TPart
            {
            ECountry=0,
            EArea=1,
            ENumber=2
            };
        enum TNumParseState
            {
            EStateSpace=0,
            EStatePart=1,
            EStateCountry=2
            };

    private: //Methods

        TBool IsLegalFreeFormatChar(TChar ch);

        /**
        * Handles key event in free format mode (TTelephoneEditorModeBC::EFreeFormat)
        */
        TKeyResponse FreeFormatOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        TPtrC NumberOrBlank(TPart aPart, const TDesC& aNumber);
        TPart CheckPart(TPositionInPart& aPos, TInt& aBeg, TInt& aEnd, TInt& aLen) const;
        void SelectPartL(TPart aPart, TPositionInPart aPos);
        void SetCursorVisibilityL(TBool aEmphasis);
        void InsertTextL(TInt aPos, const TDesC& aText);
        void InsertCharL(TInt aPos, TChar aChar);
        void DeleteCharL(TInt aPos, TInt aCode);
        void ChangePartLenL(TPart aPart, TInt aDelta, TInt aOff);
        void ParseToParts(const TDesC& aNumber, TDes& aCountry, TDes& aArea, TDes& aLocal) const;
        void GetText(TDes& aDes) const; // overloaded version of edwin get text
        TBool SpecialCharacter(TChar ch);
        void ClipboardFreeFormatL(TClipboardFunc aClipboardFunc);
        void ClipboardCoerceFormatL(TClipboardFunc aClipboardFunc);
        TBool CoerceDeleteBackspaceL(TInt aCode, TPositionInPart aPos, TInt aLen, TInt aPart);
        void CoerceLeftArrowL(TPositionInPart aPos, TInt aLen, TInt aPart);
        void CoerceRightArrowL(TPositionInPart aPos, TInt aLen, TInt aPart);
        TBool CoerceInsertL(TPositionInPart aPos, TInt aLen, TInt aPart);
        TBool CoerceSpaceDashL(TInt aCode, TInt aPart);
        void InfoPrintMaxChars() const;
    
    protected:
        void doConstructFromResourceL(TResourceReader& aReader, TBool aReadMaxChars);
    
    private:
        friend class CEikTelephoneNumberEditorFepSupport;

    private:     // Data
        TTelephoneEditorModeBC iMode;
        TUint32 iFlags;
        TInt iNumlen[KTelephoneNumberEditorPartTotal];
        TInt iBlnkResLen[KTelephoneNumberEditorPartTotal];
        TInt iNumPos[KTelephoneNumberEditorPartTotal];
        TBuf<KTelephoneNumberEditorPromptMaxChars> iPrompts[KTelephoneNumberEditorPartTotal];
        RWorldServer iWorldServer;
        CEikTelephoneNumberEditorExtra *iExtra;
    };

/**
 * The <code>CEikTelephoneNumberEditor</code> class provides the Telephone 
 * Number Editor. This control is a text editor that enables the user to enter 
 * a telephone number. The control can be implemented in one of two modes; 
 * coerced and free format. Coerced format has three fields that are placed 
 * horizontally. The fields are for the country code, area code, and number. 
 * Free format enables the user to enter the telephone number with any 
 * arrangement of characters and spaces.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class CEikTelephoneNumberEditor : public CEikTelephoneNumberEditorBC
    {
    public:  // Declarations
    /** 
     * The enumeration <code>TTelephoneEditorMode</code> specifies the mode
     * in which the telephone number is formatted. */
    enum TTelephoneEditorMode
        {
        /** specifies coerce mode */
        ECoerceFormat=EEikTelephoneNumberEditorModeCoerceFormat,
        /** specifies free format */
        EFreeFormat=EEikTelephoneNumberEditorModeFreeFormat
        };
        
        /**
        * Constructs a Telephone Number Editor from a resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>TELNUMBER</code>
        * @see <code>CCoeControl</code> in coecntrl.h
		* @see <code>TResourceReader</code> in barsread.h
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Completes construction of a Telephone Number Editor object.
        *
        * @param aMode The editor's mode
        * @param aFlags The editor's flags:
		* <code> EEikTelephoneNumberEditorCountryReadOnly </code> makes the country prompt read only
		* <code> EEikTelephoneNumberEditorHideNumber </code> makes the number prompt read only
		* <code> EEikTelephoneNumberEditorCountryOnly </code> only allow edit access to the country prompt
        * @param aPromptArray A pointer to the prompt array
        * @param aWidth The editor's width in pixels
        * @remarks This method leaves if there is not enough memory to create 
        *          this object
        * @see
        */
        IMPORT_C void ConstructL(TTelephoneEditorMode aMode, TInt aFlags, TPtrC* aPromptArray, TInt aWidth);

        /**
        * Completes construction of a Telephone Number Editor object.
        *
        * @param aMode The editor's mode
        * @param aFlags The editor's flag
        * @param aPromptArray A pointer to the prompt array
        * @param aWidth The editor's width in pixels
        * @param aMaxChars The maximum chars for each part of the prompt. Pass in the address of
		* a <code>TInt</code> array size <code>KTelephoneNumberEditorPartTotal</code> the first 
		* position in the array contains the maximum chars for the Country, the second position 
		* contains the maximum chars for the Area and the third position contains the maximum 
		* chars for the Number
        * @remarks This method leaves if there is not enough memory to create 
        *          this object
        * @see
        */
        IMPORT_C void ConstructL(TTelephoneEditorMode aMode, TInt aFlags, TPtrC* aPromptArray, TInt aWidth, const TInt* aMaxChars);

        /**
        * Sets the mode of the Telephone Number Editor.
        *
        * @param aMode The mode to be set
        * @remarks 
        * @see
        */
        IMPORT_C void SetModeL(TTelephoneEditorMode aMode);
    };


#endif      // EIKTELED_H   
            
// End of File
