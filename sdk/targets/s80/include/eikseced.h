/*
* ==============================================================================
*  Name        : Eikseced.h
*  Part of     : CKon
*  Interface   : Secret Editor API
*  Description : Classes relating to CKON password editor widget
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
#ifndef EIKSECED_H
#define EIKSECED_H

// INCLUDES
#include <eikdef.h>
#include <eikbctrl.h>

// DATA TYPES

/**
 * The <code>CEikSecretEditor</code> class implements a single line 
 * text editor which displays an asterisk for every character entered. 
 * The editor is suitable for editing confidential information such 
 * as a password. The editor can be pasted to, but no other clipboard 
 * functions are available. The editor has an associated resource 
 * struct <code>SECRETED</code> and control factory identifier 
 * <code>EEikCtSecretEd</code>.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class CEikSecretEditor : public CEikBorderedControl
    {
    public:
    /**
     * Container for enumerated values
     */
    enum
        {
        /** Maximum length (in chars) of the Secret Editor text */
        EMaxSecEdLength=32
        };
    public:
       /**
        * C++ default constructor.
        *
        * @return
        * @remarks
        * @see
        */
        IMPORT_C CEikSecretEditor();
       /**
        * Second-phase construction from a resource file. This function 
        * reads the number of characters which may be entered by the 
        * user into the editor from a <code>SECRETED</code> resource. 
        * This function or <code>SetMaxLength</code> should be called before 
        * drawing the editor and offering key events, otherwise the 
        * editor will not accept text input.
        *
        * @param aReader Resource file reader
        * @return
        * @remarks The resource type is <code>SECRETED</code>
        * @see <code>CCoeControl</code>
        * @see barsread.h for more info on <code>TResourceReader</code>
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
       /**
        * Gets the minimum size for the editor.
        * 
        * @return minimum size of the editor
        * @remarks For a compact layout, the value returned from this method 
        *          should be used to set the size of the component before 
        *          display.
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual TSize MinimumSize();
       /**
        * Handles key events offered to the control by the control 
        * environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return Indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
       /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see <code>CCoeControl</code>
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
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);
       /**
        * Returns the input capabilities of the editor. This Secret Editor 
        * is capable of handling secret text and navigation keys. 
        *
        * @return the input capabilities
        * @remarks
        * @see <code>CCoeControl</code>, <code>TCoeInputCapabilities</code>
        */
        IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
       /**
        * Gets the editor's text string.
        *
        * @param aText On return, the editor's text; this is what is stored 
        *              in memory, not what is displayed (ie. not asterisks)
        * @return
        * @remarks <code>aText</code> should be a descriptor long enough to 
        *          store the maximum length set in this control
        *          (<code>EMaxSecEdLength</code> for safety).
        * @see
        */
        IMPORT_C void GetText(TDes& aText) const;
       /**
        * Clears the editor's text string, removing any trace of it from 
        * memory. The editor's buffer is overwritten with zeros for 
        * security.
        *
        * @return
        * @remarks The control is redrawn as part of this call
        * @see
        */
        IMPORT_C void Reset();
       /**
        * Set the maximum length of the editor. This is the maximum number of
        * characters which may be entered into the editor by the user.
        *
        * @param aMaxLength The maximum number of characters which may be
        *                   entered
        * @return
        * @remarks Will panic if the maximum length set exceeds 
        *          <code>EMaxSecEdLength</code> characters
        * @see
        */
        IMPORT_C void SetMaxLength(TInt aMaxLength);
       /**
        * Sets the text in the editor.
        *
        * @param aText The text to be set
        * @return
        * @remarks Will panic if the text length set exceeds the max length
        * @see
        */
        IMPORT_C void SetText(const TDesC& aText);
    protected:  // inherited
        /**
        * Draws the cursor if the editor has focus, removes the cursor 
        * if the editor does not have focus.
        *
        * @param aDrawNow Not used
        * @return
        * @remarks
        * @see
        */
        IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);
    private: // virtual
        IMPORT_C virtual void Draw(const TRect& aRect) const;
    private: // from CCoeControl
        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2();
    private: // specific
        void DrawText() const;
        void DrawTextNow() const;
        void DisplayCursor();
    private:
        typedef TBuf<EMaxSecEdLength> TSecEdBuf;
    protected:
        TInt iSecPos;
    private:
        TInt iMaxLen;
        TInt iCharWidth;
        TInt iAscent;
    protected:
        TSecEdBuf iSecCharArr;
    enum TSecedHotKeys // order of hotkeys defined in resource file.  Not all applicable to plain text editors
        {
        EHotKeyPaste=2,
        EHotKeyInsertChar=5
        };
        TChar iChar;
    };

#endif  // EIKSECED_H

// End of File
