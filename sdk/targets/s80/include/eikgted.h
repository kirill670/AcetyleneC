/*
* ==============================================================================
*  Name        : eikgted.h
*  Part of     : CKON
*  Interface   : Global Text Editor API
*  Description : Text editor control with global formatting.
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

#ifndef EIKGTED_H
#define EIKGTED_H


// INCLUDES
#include <eikedwin.h>
#include <badesca.h>
#include <eikon.hrh>
#include <eikfardi.h>


// FORWARD DECLARATIONS
class CGlobalText;
class CControlEnv;
class CEikDialogToolBar;
class CPrintSetup;
class CTextPageRegionPrinter;
class CEikDialogToolBar;


// CLASS DECLARATIONS

/**
*  The <code>CEikGlobalTextEditor</code> class implements a Global Text Editor. 
*  The Global Text Editor is an editor control that supports globally formatted 
*  text. This means that all of the text has the same character and paragraph 
*  format, unlike the rich text editor control, which allows individual 
*  for each character.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikGlobalTextEditor : public CEikEdwin, public MEikFindAndReplaceDlgObserver
    {
    public:  // Declarations

    /**
    * The enumeration <code>TFontStyleFlags</code> specifies standard font 
    * styles.
    */
    enum TFontStyleFlags
        {
        /** no font styles applied */
        EStandard   =0x00,
        /** bold font style */
        EBold       =0x01,
        /** italic font style */
        EItalic     =0x02,
        /** underlined font style */
        EUnderline  =0x04
        };

    public:
        // Constructors and destructor
        /**
        * The default object constructor.
        */
        IMPORT_C CEikGlobalTextEditor();
        
        /**
        * The object destructor.
        */
        IMPORT_C ~CEikGlobalTextEditor();
        
        /**
        * The object constructor. This method constructs the control with a 
        * border around it.
        *
        * @param aBorder The border for the editor
        * @remarks 
        * @see tgulborder.h
        */
        IMPORT_C CEikGlobalTextEditor(const TGulBorder& aBorder);

        /**
        * Completes construction of a Global Text Editor.
        *
        * @param aParent The parent control. Can be <code>NULL</code>
        * @param aNumberOfLines The maximum number of lines that can be 
        *                       displayed by the editor
        * @param aTextLimit The maximum number of characters that can be 
        *                   entered in the editor
        * @param aEdwinFlags Bitmask of flags that control the attributes of 
        *                    the editor, for instance, whether the editor is 
        *                    read-only. Set to 0 if not required. See 
        *                    <code>CEikEdwin</code> for more details
        * @param aFontControlFalgs The font control flags (see gulftflg.hrh), 
        *                          for example, <code>EGulFontControlUnderline</code>
        * @param aFontNameFlags The font types (see gulftflg.hrh), 
        *                       for example, <code>EGulNoMonospaceFonts</code> 
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aNumberOfLines,TInt aTextLimit,TInt aEdwinFlags,TInt aFontControlFalgs,TInt aFontNameFlags);

        /**
        * Sets the Global Text Editor's button group.  
        * This implementation is empty.
        *
        * @param aButtonGroup The button group to use
        * @remarks
        * @see
        */
        IMPORT_C void SetButtonGroup(CEikDialogToolBar* aButtonGroup);

        /**
        * Sets the bitmap used for the line cursor.
        *
        * @param aBitmap The bitmap used for the line cursor
        * @remarks
        * @see
        */
        IMPORT_C void SetLineCursorBitmapL(CFbsBitmap* aBitmap);

        /**
        * Runs a dialog enabling a user to set the font.
        *
        * @param aFontFlags Flags determining the type of fonts to be displayed,
        *                   for example, <code>EGulNoMonospaceOrSymbolFonts</code>
        * @param aGraphicsDevice The graphics device, <code>iCoeEnv->ScreenDevice</code>
        * @param aFontControlFlags Flags determining what styles are to be made 
        *                          available, for example, 
        *                          <code>EGulFontControlBold</code>
        * @return <code>ETrue</code> if changes are made successfully; 
        *         <code>EFalse</code> otherwise
        * @remarks 
        * @see gulftflg.hrh for font flags, for example,
        *      <code>EGulFontControlUnderline</code>
        */
        IMPORT_C TBool RunFontDialogL(TInt aFontFlags=EGulNoSymbolFonts,CGraphicsDevice* aGraphicsDevice=NULL,TInt aFontControlFlags=EGulFontControlAll);

        /**
        * Runs a dialog enabling a user to set tabs.
        * Applies the new settings to the control upon closure.
        *
        * @param aPageWidth The page width
        * @remarks
        * @see
        */
        IMPORT_C void RunTabsDialogL(TInt aPageWidth);

        /**
        * Runs the Indents dialog. Applies the new settings to the control
        * upon closure.
        *
        * @param aPageWidth The page width
        * @remarks
        * @see
        */
        IMPORT_C void RunIndentsDialogL(TInt aPageWidth);

        /**
        * Sets the graphics device.
        * This is used when determining the available fonts and their sizes.
        *
        * @param aGraphicsDevice The graphics device (<code>iCoeEnv->ScreenDevice</code>)
        * @remarks
        * @see gdi.h
        */
        IMPORT_C void SetGraphicsDevice(CGraphicsDevice* aGraphicsDevice);

        /**
        * Runs the Find dialog, which enables the user to specify text 
        * to search for.  The results are displayed automatically to the user.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void RunFindDialogL();
       
        /**
        * Runs the Find Again dialog.
        * The results are displayed automatically to the user.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void RunFindAgainDialogL();
        
        /**
        * Runs the Replace dialog, which enables the user to specify text 
        * to search for and the text to replace it with.
        * The results are handled automatically.
        *
        * @remarks
        * @see
        */
        IMPORT_C void RunReplaceDialogL();
        
        /**
        * Sets up the find model, the find list, and the replace list ready 
        * for find or replace operations.
        * This is necessary if the application needs to search for
        * code itself, as opposed to the user-driven <code>RunFindDialog()</code>
        * methods, for example. <code>DoFindL()</code> can then be called 
        * without arguments.
        *
        * @param aModel The find model to use
        * @param aFindList The find list
        * @param aReplaceList The replace list
        * @remarks If any of the parameters are empty, they are created
        * @see
        */
        IMPORT_C void InitFindL(SEdwinFindModel*& aModel,CDesCArray*& aFindList,CDesCArray*& aReplaceList);

        /**
        * Searches for text using the currently defined model
        * The behavior is undefined if a model has not been set up.
        *
        * @return <code>ETrue</code> if the text is found; <code>EFalse</code> 
        *         otherwise
        * @remarks
        * @see <code>InitFindL()</code>
        */
        IMPORT_C TBool DoFindL();

        /**
        * Searches for text using the specified model.
        *
        * @param aModel The find model to use
        * @return <code>ETrue</code> if the text is found; <code>EFalse</code> 
        *         otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool DoFindL(SEdwinFindModel& aModel);

        /**
        * Runs a dialog that enables the user to set text alignment, spacing,
        * or border.
        *
        * @param aCommand The user-entered command
        * @remarks
        * @see
        */
        IMPORT_C void RunParaDialogsL(TInt aCommand);  
        
        /**
        * Runs a paginate dialog.
        *
        * @param aPrintSetup Print setup information
        * @param aCharsPerPage The number of characters per page
        * @return <code>ETrue</code> if cancel is pressed; 
        *         <code>EFalse</code> otherwise.  It can be useful
        *         to know if pagination has occurred
        * @remarks
        * @see
        */
        IMPORT_C TBool RunPaginateDialogL(CPrintSetup* aPrintSetup,CArrayFix<TInt>* aCharsPerPage);

        /**
        * Gets a pointer to the global text object, which contains the
        * formatting for the Global Text Editor text.
        * The <code>CGlobalText</code> object contains one instance of a 
        * paragraph format and a character format class. Each presents
        * the formatting applied to the total document contents.
        *
        * @return The global text object
        * @remarks
        * @see txtglobl.h
        */
        IMPORT_C CGlobalText* GlobalText() const;

        /**
        * Applies paragraph formatting through code, as opposed to user
        * intervention as with <code>RunParaDialogsL()</code>.
        *
        * @param aParaFormat Contains the new paragraph formatting values to 
        *                    apply
        * @param aParaMask Bitmask specifying the paragraph format attributes 
        *                  to change
        * @remarks All text in the editor is formatted, regardless of selection
        * @see txtfrmat.h
        */
        IMPORT_C void ApplyParaFormatL(CParaFormat* aParaFormat,TParaFormatMask& aParaMask);

        /**
        * Applies character formatting.
        *
        * @param aCharFormat Contains the new character formatting values to 
        *                    apply
        * @param aCharMask Bitmask specifying the character format attributes 
        *                  to change. Use a <code>TTextFormatAttribute</code> 
        *                  setting
        * @remarks All text in the editor is formatted, regardless of selection
        * @see txtfrmat.h
        */
        IMPORT_C void ApplyCharFormatL(TCharFormat& aCharFormat,TCharFormatMask& aCharMask);
        
        /**
        * Toggles bold, italics, or underlining in all of the editor text.
        *
        * @param aFontFlag The format attribute to toggle (<code>TFontStyleFlags</code>)
        * @remarks
        * @see
        */
        IMPORT_C void BoldItalicUnderlineEventL(TInt aFontFlag);
     
        /**
        * Updates the buttons in the button group (toolbar) so they reflect the 
        * formatting of the text in the control.
        * This implementation is empty.
        *
        * @remarks
        * @see
        */
        // Methods from base classes
        IMPORT_C void UpdateButtonGroup();

        /**
        * Constructs a Global Text Editor from a resource file. The control factory 
        * ID is <code>EEikCtGlobalTextEditor</code>.
        * 
        * @param aReader A resource reader
        * @remarks The resource type is <code>GTXTED</code>
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType The type of key event, either: <code>EEventKey</code>, 
        *              <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Activates this control. Sets the Global Text Editor as ready for 
        * drawing.
        * 
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ActivateL();

        /**
        * This method is used by the <code>CEikFindAndReplaceDialog</code> to 
        * call back with find instructions from a user dialog. 
        * The find text and criteria are 
        * contained in <code>aModel</code>. 
        *
        * @param aModel The find model to use
        * @param aResetStart Where to start the find operation from. If 
        *                    <code>aResetStart</code> is <code>ETrue</code>, 
        *                    a fresh find operation will start from the 
        *                    beginning of the document, or, if the 
        *                    <code>EFindStartAtCursor</code> flag is set in 
        *                    <code>aModel</code> (see <code>TFindFlags</code> 
        *                    in eikedwin.h), the current position. 
        *                    If <code>aResetStart</code> is <code>EFalse</code>, 
        *                    a find next operation will continue from the 
        *                    current cursor position
        * @return <code>ETrue</code> if the text was found;
        *         <code>EFalse</code> otherwise
        * @remarks 
        * @see <code>MEikFindAndReplaceDlgObserver</code>
        */
        IMPORT_C TBool CallBackFindL(SEdwinFindModel& aModel, TBool aResetStart);

        /**
        * This method is used by the <code>CEikFindAndReplaceDialog</code> to 
        * call back with replace instructions from a user dialog. 
        * The find text and criteria are contained in <code>aModel</code>. 
        *
        * @param aModel The find model to use
        * @param aResetStart Where to start the find/replace operation from. If 
        *                    <code>aResetStart</code> is <code>ETrue</code>, 
        *                    a fresh find/replace operation will start from the 
        *                    beginning of the document, or, if the 
        *                    <code>EFindStartAtCursor</code> flag is set in 
        *                    <code>aModel</code> (see <code>TFindFlags</code> 
        *                    in eikedwin.h), the current position. 
        *                    If <code>aResetStart</code> is <code>EFalse</code>, 
        *                    a find next operation will continue from the 
        *                    current cursor position
        * @return <code>ETrue</code> if the text was found; <code>EFalse</code> 
        *         otherwise
        * @remarks
        * @see <code>MEikFindAndReplaceDlgObserver</code>
        */
        IMPORT_C TBool CallBackReplaceL(SEdwinFindModel& aModel, TBool aResetStart);

        /**
        * Gets the width of the line cursor, in pixels.
        *
        * @return the width of the line cursor, in pixels
        * @remarks
        * @see <code>CEikEdwin</code>
        */
        IMPORT_C TInt LineCursorWidth() const;

        /**
        * Creates the Global Text Editor custom draw. This method has an empty 
        * implementation apart from returning <code>NULL</code>.
        * 
        * @return <code>NULL</code> at present
        * @remarks
        * @see <code>CEikEdwin</code> for more details
        */
        IMPORT_C CLafEdwinCustomDrawBase* CreateCustomDrawL();

    protected:  // Methods

    // New Methods
        
        /**
        * Displays info that the replace operation has been done.
        * @param aReplaceText Text to be displayed
        */
        IMPORT_C void DisplayReplaceOperationDone(TDes& aReplaceText);
        /**
        * Displayes info that the text has been found.
        * @param aFindText Text to be displayed
        */
        IMPORT_C void DisplayFindTextFound(TDes& aFindText);
        /**
        * Basic construction.
        */
        IMPORT_C void BaseConstructL();
    private: // from CoeControl
        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2();
    private: // from CEikEdwin
        IMPORT_C void Reserved_3();
    private:
        void CheckDocumentNotEmptyL();
        void CreateFindModelL();
        void GetTextForFindL();
        protected:     // Data
            /** Characters format. */
        CCharFormatLayer* iCharFormatLayer;
            /** Paragraphs format. */
        CParaFormatLayer* iParaFormatLayer;
        private:     // Data
        CDesCArray* iFindList; 
        CDesCArray* iReplaceList;
        SEdwinFindModel* iFindModel;
        CEikDialogToolBar* iButGroup;
        TInt iLineCursorWidth;
        CFbsBitmap* iLineCursor;
        TInt iFontControlFlags;
        TInt iFontNameFlags;
        CGraphicsDevice* iGraphicsDevice;
    };


#endif      // EIKGTED_H   
            
// End of File
