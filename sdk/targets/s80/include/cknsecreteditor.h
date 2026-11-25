/**
* ==============================================================================
*  Name        : CknSecretEditor.h
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
#ifndef CKNSECRETEDITOR_H
#define CKNSECRETEDITOR_H

// INCLUDES
#include <eikdef.h>
#include <cknbctrl.h>
#include <gulutil.h>

// DATA TYPES
// FORWARD DECLARATIONS
/**
 * The <code>CCknSecretEditorFepSupport</code> class implements FEP 
 * support for the <code>CCknSecretEditor</code> class.
 *
 * @internal
 */
class CCknSecretEditorFepSupport;

/** maximum possible length of a password */
const TInt KCknMaxPassword=0x100;
/** maximum advisable length for passwords */
const TInt KCknStandardPassword=0x014;
/** minimum length of a password */
const TInt KCknMinPassword=0x006;
/** maximum number of display characters in a Secret Editor control */
const TInt KCknStandardPasswordControlWidth=0x00c;
/** typedef for password buffer descriptor */
typedef TBuf<KCknMaxPassword> TCknPassword;

/**
 * The <code>CCknSecretEditor</code> class implements a Secret Editor that
 * allows editing of a text string and optional hiding of the entered 
 * characters. This is generally used when entering or setting passwords 
 * which should remain hidden.
 * This control supports a border and usage with a FEP. It can be 
 * constructed from resource or not.
 *
 * @lib cknctl.lib
 * @since Series 90 1.0
 */
class CCknSecretEditor : public CCknBorderedControl
    {
    public:
    /**
     * The mode of display for any characters entered in the Secret Editor.
     */
    enum TMode
        {
        /**
         * entered characters are immediately masked with asterisks
         */
        EModeSecretChar,
        /**
         * entered characters are not masked with asterisks
         */
        EModeNoSecretChar,
        /**
         * each entered character is displayed for a short interval,
         * and then masked with an asterisk
         */
        EModeTimer
        };
    public:
       /**
        * Static construction method for instantiating an object of this 
        * class.
        *
        * @remarks
        * @see
        */
        IMPORT_C static CCknSecretEditor* NewL();
       /**
        * The object destructor.
        *
        * @remarks
        * @see
        */
        IMPORT_C ~CCknSecretEditor();
       /**
        * Sets the current mode of display for characters entered in the 
        * Secret Editor.
        *
        * @param aMode Mode of display
        * @remarks
        * @see <code>TMode</code> enumeration
        */
        IMPORT_C void SetMode(TMode aMode);
        /**
        * Second-phase construction from a resource file. This function 
        * reads from a <code>SECRETEDITOR</code> resource, which allows
        * resource definition of the maximum password length, maximum 
        * display length and font height.
        *
        * @param aReader Resource file reader
        * @remarks The resource type is <code>SECRETEDITOR</code>. 
        * @remarks It is possible to initialize the control without calling 
        *          this method, as default values are set in the control 
        *          in the first phase constructor
        * @see <code>CCoeControl</code>
        * @see barsread.h for more information on <code>TResourceReader</code>
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
       /**
        * Gets the minimum size for the editor.
        * 
        * @return minimum size of the editor
        * @remarks For a compact layout, the value returned from this method 
        *          should be used to set the size of the component before 
        *          display
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual TSize MinimumSize();
       /**
        * Handles key events offered to the control by the control 
        * environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType	The type of key event, one of: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code> 
		* @return indicates whether or not the key event was used by this 
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
		* @see <code>TCoeColorUse</code>
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
       /**
        * Handles a change to the control's resources that are shared across
        * the environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed 
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);
       /**
        * Returns the input capabilities of the editor. The input capabilities
        * of this editor are determined by the FEP installed.
        *
        * @return The input capabilities
        * @remarks
        * @see <code>CCoeControl</code>
		* @see <code>TCoeInputCapabilities</code> (defined in coeinput.h)
        */
        IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
       /**
        * Sets the editor's input capabilities.
        *
        * @param aInputCapabilities An OR'd set of input
        *                           capabilities as defined in
        *                           <code>TCoeInputCapabilities</code>
        * @remarks
        * @see <code>TCoeInputCapabilities</code> (defined in coeinput.h)
        */
        IMPORT_C void SetInputCapabilities(const TUint aInputCapabilities);
       /**
        * Handles pointer events. This function gets called whenever a pointer
        * event occurs in the control. This occurs when the pointer is within 
        * the control's extent, or when the control has grabbed the pointer.
        *
        * @param aPointerEvent The pointer event
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
       /**
        * Gets the editor's text string.
        *
        * @param aText The editor's text; this is what is stored in memory
        * @remarks <code>aText</code> should be a descriptor long enough to 
        *          store the maximum length set in this control
        *          (<code>KCknMaxPassword</code> characters for safety)
        * @see cknsecreteditor.h for the <code>KCknMaxPassword</code> constant
        */
        IMPORT_C void GetText(TDes& aText) const;
       /**
        * Gets the maximum number of characters allowed in a password.
        *
        * @return maximum number of characters allowed in a password
        * @remarks
        * @see
        */
        IMPORT_C TInt MaxPasswordLengthInCharacters() const;
       /**
        * Gets the maximum number of characters that the control will display
        * without scrolling.
        *
        * @return maximum number of characters that the control will 
        *         display without scrolling
        * @remarks
        * @see
        */
        IMPORT_C TInt MaxControlWidthInCharacters() const;
       /**
        * Clears the editor's text string, removing any trace of it from 
        * memory. The editor's buffer is overwritten with zeros for 
        * security.
        *
        * @remarks The control is redrawn as part of this call
        * @see
        */
        IMPORT_C void Reset();
       /**
        * Set the maximum length of the editor. This is the maximum number of
        * characters which may be entered by the user into the editor.
        *
        * @param aMaxLength Maximum number of characters which may be
        *                   entered
        * @remarks Will panic if the maximum length set exceeds 
        *          <code>KCknMaxPassword</code> characters
        * @see cknsecreteditor.h for the <code>KCknMaxPassword</code> constant
        */
        IMPORT_C void SetMaxPasswordLength(TInt aMaxLength);
       /**
        * Sets the maximum number of characters that the control can 
        * display without scrolling.
        *
        * @param aMaxWidth Maximum number of characters that the control
        *                  can display without scrolling
        * @remarks
        * @see
        */
        IMPORT_C void SetMaxControlWidth(TInt aMaxWidth);
       /**
        * Sets the text in the editor.
        *
        * @param aText The text to be set
        * @remarks Will panic if the text length set exceeds the max length
        * @see
        */
        IMPORT_C void SetText(const TDesC& aText);
       /**
        * Determines whether or not the FEP will receive notifications 
        * when the position of the cursor changes
        *
        * @param aEnable <code>ETrue</code> to disable notifications to 
        *                the FEP, <code>EFalse</code> otherwise
        * @remarks By default, the cursor change event is enabled
        * @see
        */
        IMPORT_C void DisableCursorChangeEvent(TBool aEnable);
       /**
        * Sets or removes a highlight for the editor contents.
        *
        * @param aHighlighted <code>ETrue</code> to highlight the contents
        * @param aDrawNow <code>ETrue</code> to force a redraw
        * @remarks
        * @see
        */
        IMPORT_C void SetHighlighted(TBool aHighlighted, TBool aDrawNow=EFalse);
       /**
        * Sets a font height for the Secret Editor. Causes the size of this 
        * control to change, and triggers a redraw of this control.
        *
        * @param aHeight Height of the font to use
        * @remarks Passing a font height of zero will reset the font to the
        *          default.
        * @remarks Though using this method forces a redraw of the control, 
        *          the developer should also ensure that the surrounding area 
		*          of this control is redrawn, especially in cases where the 
		*          font height is reduced using this method
        * @see
        */
        IMPORT_C void SetFontHeightInPixels(TInt aHeight);
    public:
    // FEP related functions
       /**
        * Sets the <code>Gc</code> to display inline text.
        *
        * @param aGc The Graphics Context to be changed
        * @internal
        */
        void SetGcToInlineEditingVideo(CWindowGc& aGc) const;
       /**
        * Simulates the Enter key being pressed.
        *
        * @internal
        */
        void SimulateEnterKeyEventL();
       /**
        * Resets the edit line.
        *
        * @internal
        */
        void ResetInlineEditing();
       /**
        * Returns the Cursor Position.
        *
        * @internal
        */
        TInt CursorPosition();
       /**
        * Gets content from the editor.
        *
        * @param aEditorContent - the retrieved content
        * @param aDocumentPosition - the position to start retrieving the content from
        * @param aLengthToRetrieve - the length of text to retrieve
        * @internal
        */
        void GetEditorContent(TDes& aEditorContent,TInt aDocumentPosition,TInt aLengthToRetrieve) const;
       /**
        * Gets screen coordinates.
        *
        * @param aLeftSideOfBaseLine - the point to the left side of the baseline
        * @param aHeight - the height
        * @param aAscent - the ascent
        * @param aDocumentPosition - the position in the document
        * @internal
        */
        void GetScreenCoordinates(TPoint& aLeftSideOfBaseLine,TInt& aHeight,TInt& aAscent,TInt aDocumentPosition) const;
       /**
        * Display an infoprint stating that the max number of chars has been reached.
        *
        * @internal
        */
        void InfoPrintMaxChars();
    protected:
        /**
        * C++ default constructor.
        *
        * @return
        * @remarks
        * @see
        */
        IMPORT_C CCknSecretEditor();
        /**
        * 2nd phase constructor.
        * 
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL();
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
        TInt BaseLine() const;
        void DrawBackground() const;
        IMPORT_C virtual void Draw(const TRect& aRect) const;
        IMPORT_C void PrepareForFocusGainL();
    private: // from CCoeControl
        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2();
    private:
        static TInt HideCharacterCallback(TAny* aSelf);
        void SetSecretMode();
    private: // specific
        void DrawText() const;
        void DrawTextNow() const;
        void DisplayCursor();
        void HideCursor();
        void HideCharacter();
        void ResetTimerArray();
        void StartNewCharacterHidingTimerL();
        TInt GetHiddenPosAccordingToMode() const;
        TInt DisplayedTextWidthInPixels() const;
        TInt SecretTextWidthInPixels(const CFont* aFont) const;
        TInt InlineTextWidthInPixels(const CFont* aFont) const;
        void SetGcToInverseVideo(CWindowGc& aGc) const;
        const CFont* Font() const;
    private:
        typedef TBuf<KCknMaxPassword> TSecEdBuf;
    protected:
        TInt iSecPos;
        TInt iHiddenPos;
        RPointerArray<CPeriodic> iTimerArray;
        TBool iHighlighted;
    private:
        TInt iMaxPasswordLength;
        TInt iMaxControlWidth;
        TInt iCharWidth;
    protected:
        TSecEdBuf iSecCharArr;
    enum TSecedHotKeys // order of hotkeys defined in resource file.  Not all applicable to plain text editors
        {
        EHotKeyPaste=2,
        EHotKeyInsertChar=5
        };
        TChar iChar;
        TMargins8 iMargins;
        TMode iMode;
    private:
        CCknSecretEditorFepSupport* iFepSupport;
        TBool iIsInlineEditing;
        TSecEdBuf iInlineCharArr;
        TInt iInlinePos;
        TBool iCursorChangeDisabled;
        TUint iInternalFlags;
        TInt iLeftDownXPos;
        TInt iFontHeightInPixels;
        CFont* iFont;
    friend class CCknSecretEditorFepSupport;
    };




#endif  // CKNSECRETEDITOR_H

// End of File
