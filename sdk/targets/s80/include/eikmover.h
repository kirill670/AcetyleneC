/*
* =============================================================================
*  Name        : eikmover.h
*  Part of     : CKON / EIKDLG
*  Interface   : Mover API
*  Description : A draggable bar that can be used as a title bar of a Dialog 
*                window.
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


#ifndef EIKMOVER_H
#define EIKMOVER_H

// INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class TResourceReader;
class CEikMoverExtension;


/**
* The <code>CEikMover</code> class implements a draggable bar that is used 
* as the title bar of a Dialog.
*
*  @lib eikdlg.lib
*  @since Series90 1.0
*/
class CEikMover : public CCoeControl
    {
    public: 

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikMover();

        /**
        * The default object constructor.
        */
        IMPORT_C CEikMover();

        /**
        * Sets the text for the moveable title bar.
        *
        * @param aText The title of the moveable title bar. Ownership is transferred
        * @remarks
        * @see
        */
        IMPORT_C void SetText(HBufC* aText);

        /**
        * Sets the text for the moveable title bar and allocates memory for it.
        *
        * @param aText The title of the moveable title bar
        * @remarks
        * @see
        */
        IMPORT_C void SetTextL(const TDesC& aText);

        /**
        * Sets whether the Dialog can be re-positioned by dragging the title bar.
        *
        * @param aActive <code>ETrue</code> to set the moveable title bar to be accessible
        *        to the user; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetActive(TBool aActive);

        /**
        * Indicates if the Dialog can be re-positioned by dragging the title bar.
        *
        * @return <code>ETrue</code> if the title bar is accessible to 
        *         the user; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool Active() const;

        /**
        * Sets the font for the moveable title bar
        *
        * @param aFont The font to use for the text of the moveable title bar. If 
        *        not specified the environment's normal font is set
        * @remarks
        * @see
        */
        IMPORT_C void SetFont(const CFont* aFont);

        /**
        * Sets whether the movable title bar has a Help button. The Help button
        * is the question mark icon in the top left-hand corner of the title 
        * bar. Tapping it brings up the Help viewer.
        *
        * @param aValue <code>ETrue</code> if the a Help button is present; 
        *               <code>EFalse</code> otherwise
        * @remarks Set the flag <code>EEikDialogFlagHelpButton</code> in the 
        *          Dialog's resource definition to display the Help button
        * @see
        */
        IMPORT_C void SetHasHelpButton(TBool aValue);

        /**
        * Sets whether the movable title bar's clipboard button responds to
        * taps or not. The clipboard button is the icon in the top left-hand
        * corner of the title bar. It displays a menu with options for cut, 
        * copy and paste when enabled by this method.
        *
        * @param aValue <code>ETrue</code> if a clipboard button is present;
        *               <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetHasClipboardButton(TBool aValue);

        /**
        * Determines whether the title bar has a clipboard button.
        *
        * @return <code>ETrue</code> if the title bar has a clipboard 
        *         button; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool HasClipboardButton() const;

        /**
        * Returns the index of the Help bitmap.
        * This is an index from <code>TMbmSkindialogbutton</code>, defined
        * in skindialogbutton.mbg.
        *
        * @return the index of the Help bitmap
        * @remarks
        * @see
        */
        IMPORT_C TInt HelpBitmapIndex();

        /**
        * Returns the index of the clipboard bitmap.
        * This is an index from <code>TMbmSkindialogbutton</code>, defined
        * in skindialogbutton.mbg.
        *
        * @return the index of the clipboard bitmap
        * @remarks
        * @see
        */
        IMPORT_C TInt ClipboardBitmapIndex();

        /**
        * Handles a clipboard command.
        *
        * @param aCommand The command to be handled
        * @remarks
        * @see
        */
        IMPORT_C void HandleClipboardCommand(TInt aCommand);

        /**
        * Sets the clipboard button to be dimmed.
        *
        * @param aDimmed <code>ETrue</code> if the clipboard button is to be 
        *                dimmed; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetClipboardButtonDimmed(TBool aDimmed);

        /**
        * Determines whether the clipboard button is dimmed.
        *
        * @return <code>ETrue</code> if the clipboard button is dimmed;
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsClipboardButtonDimmed() const;
    public: // from CCoeControl

        /**
        * Sets the text of the moveable title bar from resource.
        * 
        * @param aReader The resource reader
        * @remarks There is no associated resource struct. This method is
        *          called by <code>CEikDialog::ConstructFromResourceL()</code>
        * @see CCoeControl
        */
        IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Returns the minimum size of the title bar.
        *
        * @return the minimum size of the title bar
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual TSize MinimumSize(); 

        /**
        * Sets the container for the window.
        *
        * @param aContainer The container
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aContainer);

        // not available before Release 005u
        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

        /**
        * Handles a change to the moveable title bar's resources that are 
        * shared across the environment.
        *
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType); 
    public:

        /**
        * Completes construction of a moveable title bar object.
        *
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void ConstructL();
    public:
        /**
        * @deprecated kept for BC
        * @param aLeftMargin n/a
        */
        IMPORT_C void SetTitleLeftMargin(TInt aLeftMargin);
    public:
        /** @internal */
        void CloseMenu();
        /** @internal */
        void SetClipBoardMenuActioned(TBool aActioned);
    public:

    enum
        {
        /**
        * this character is used to split text into left and right parts
        * @internal
        */
        EEikMoverLeftRightDelimiter=9,
        };

    private: // from CCoeControl
        IMPORT_C virtual void Draw(const TRect& aRect) const;
        IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    protected:

        /**
        * Draws shadowed text on the movable title bar.
        * @param aGc The graphics context
        * @param aText The text to be drawn
        * @param aRect The area that the text is to be drawn in
        * @param aAlign The justification of the text - e.g. ELeft
        */
        void DrawShadowedText(CBitmapContext& aGc,const TDesC& aText,const TRect& aRect,CGraphicsContext::TTextAlign aAlign) const;

        /**
        * deprecated
        * @param aAppTitleAreaSize n/a
        */
        void CreateBrushBitmapL(const TSize aAppTitleAreaSize);

        /**
        * deprecated
        * @return n/a
        */
        CFbsBitmap* BrushBitmap();

        /**
        * Checks to see if the Help button has been pressed.
        * @param aPointerEvent The pointer event
        * @return <code>ETrue</code> if the pointer event was a Help button press,
        *         or <code>EFalse</code> otherwise
        */
        TBool CheckHelpButtonPressL(const TPointerEvent& aPointerEvent);

        /**
        * Checks to see if the Clipboard button has been pressed.
        * @param aPointerEvent The pointer event
        * @return <code>ETrue</code> if the pointer event was a Clipboard button
        *         press, or <code>EFalse</code> otherwise
        */
        TBool CheckClipboardButtonPressL(const TPointerEvent& aPointerEvent);
    //
    private:
        IMPORT_C void Dummy1(); // To fill gap in .DEF file from removing reserved function
        IMPORT_C void Dummy2(); // To fill gap in .DEF file from removing reserved function
    private:
        CEikMoverExtension* iExt;
        const CFont* iFont;
        TPoint iPointerDownPos;
        TInt iMoverFlags;
        CCoeControl* iParentControl;
        TInt iHelpBitmapIndex;
        TInt unused;
    };

#endif  // EIKMOVER_H

// End of File