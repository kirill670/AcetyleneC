/*
* ==============================================================================
*  Name        : eikrted.h
*  Part of     : CKON
*  Interface   : Rich Text Editor API
*  Description : Widget that implements an editor of rich text documents.
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

#ifndef __EIKRTED_H__
#define __EIKRTED_H__

// INCLUDES
#include <eikgted.h>
#include <apparc.h>
#include <txtmrtsr.h>
#include <gdi.h>
#include <cknparserbanner.h>

// FORWARD DECLARATIONS
class CRichText;
class TResourceReader;
class TPictureHeader;
class CEikRubberBand;
class CBufStore;
class CStreamStore;
class CApaDoor;
class CRichTextParser;
class CEikParserManager;
class MParser;
class CCknParserBanner;


/**
 * @deprecated
 */
class MEikRichTextEditorParserObserver
    {
    public:
        virtual void HandleCursorOverParserL(const TDesC& aDoItText, MParser* aParser, TBool aOverParser)=0;
    };

/**
* The <code>CEikRichTextEditor</code> class implements a Rich Text Editor that 
* can handle different character and paragraph formatting throughout the text.
* Objects can also be inserted into the text, for example, images, spreadsheets,
* and Word documents. These objects can be opened for editing in their 
* associated application.
*
* @lib eikctl.lib
* @since Series90 1.0
*/
class CEikRichTextEditor : public CEikGlobalTextEditor, public MApaEmbeddedDocObserver, public MRichTextStoreResolver, public MPictureFactory
    {
    public:
    /** 
     * The enumeration <code>TObjectFormat</code> specifies the format of 
     * embedded documents. 
     */
    enum TObjectFormat
        {
        /** display the embedded document as an icon */
        EAlwaysIconic,
        /** display a live representation of the object's data, if possible */
        EGlassIfPossible
        };

    /** 
     * The anonymous enumeration provides control flags that are also defined 
     * in eikon.hrh.
     */
    enum 
        {
        /** always display embedded documents as icons */
        EShowAllPicturesAsIconic    =0x00100000,
        /** no parsing of the text will be done, so no Click To... controls are displayed */
        ENoTextParsers              =0x00200000
        };

    public:

        /**
        * The default object constructor.
        */
        IMPORT_C CEikRichTextEditor();

        /**
        * The object constructor.
        *
        * @param aBorder The border type for the Rich Text Editor
        * @remarks <code>TGulBorder</code> is defined in gulbordr.h
        * @see
        */
        IMPORT_C CEikRichTextEditor(const TGulBorder& aBorder);

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikRichTextEditor();

        /**
        * Completes construction of a Rich Text Editor object.
        *
        * @param aParent The control to get the container window from
        * @param aNumberOfLines The number of lines to be displayed in the 
        *                       Rich Text Editor. If this is greater than the
        *                       viewable area, the developer should add
        *                       scrollbars manually
        * @param aTextLimit The maximum number of characters that can be entered
        *                   in the Rich Text Editor
        * @param aEdwinFlags Flags (see <code>CEikEdwin</code>)
        * @param aFontControlFlags The Font control flags to be passed into the
        *                          Rich Text Editor's font dialog
        * @param aFontNameFlags The Font name flags to be passed into the 
        *                       Rich Text Editor's font dialog
        * @remarks <code>EGulFontControlAll</code> and <code>EGulNoSymbolFonts</code>
        *          are defined in gulftflg.hrh
        * @see CEikEdwin
        */
        IMPORT_C void ConstructL(const CCoeControl* aParent,TInt aNumberOfLines,TInt aTextLimit,TInt aEdwinFlags,TInt aFontControlFlags=EGulFontControlAll,TInt aFontNameFlags=EGulNoSymbolFonts);

        /**
        * Gets the formatted text.
        *
        * @return a pointer to the text of the Rich Text Editor
        * @remarks
        * @see
        */
        IMPORT_C CRichText* RichText() const;

        /**
        * Brings up a file selection dialog to find an object to be inserted,
        * then adds it to the rich text at the current cursor position. The
        * dialog only shows files associated with supported applications.
        * The supported applications are Word, Sheet, Images, and Sketch.
        *
        * @param aFormat <code>EAlwaysIconic</code> if an icon is 
        *                required to represent the object. 
        *                <code>EGlassIfPossible</code> to try and display 
        *                the object as a glass door. If this is not possible,
        *                the object is represented by an icon
        * @remarks
        * @see
        */
        IMPORT_C void InsertObjectL(TObjectFormat aFormat);

        /**
        * Brings up a file selection dialog to find an object to be inserted,
        * then adds it to the rich text at the current cursor position. The
        * dialog only shows files associated with supported applications.
        * The supported applications are Word, Sheet, Images, and Sketch.
        * This calls <code>InsertObjectL(EGlassIfPossible)</code>.
        *
        * @remarks
        * @see 
        */
        IMPORT_C void InsertObjectL();

        /**
        * Creates a new object using a specified application and adds it to the
        * rich text at the current cursor position. The method opens the 
        * object for editing in the specified application.
        *
        * @param aAppDllName The name of the application DLL to be embedded
        * @param aAppDllUid The UID of the application DLL to be embedded
        * @param aFormat <code>EAlwaysIconic</code> if an icon is 
        *                required to represent the object. 
        *                <code>EGlassIfPossible</code> to try and display 
        *                the object as a glass door. If this is not possible,
        *                the object is represented by an icon
        * @remarks
        * @see CApaProcess::AddNewDocumentL()
        */
        IMPORT_C void InsertObjectL(const TDesC& aAppDllName,TUid aAppDllUid,TObjectFormat aFormat);

        /**
        * Edits the object at the current cursor position. This opens the 
        * appropriate embedded application. The object must be selected for 
        * the cursor position to be set correctly. This method does nothing if 
        * no object is found at the current cursor position.
        *
        * @remarks To edit how the object looks when embedded, use
        *          <code>EditPictureFormatL()</code>
        * @see
        */
        IMPORT_C void ReEditObjectL();

        /**
        * Gets the cursor position of the currently selected object.
        *
        * @return the cursor position of the currently selected object. If no
        *         object is selected, return <code>KErrNotFound</code>
        * @remarks
        * @see
        */
        IMPORT_C TInt ObjectCursorPos() const;

        /**
        * Checks if there is a selected object, and if found, opens it up for 
        * editing in the associated application.
        *
        * @return <code>ETrue</code> if an object was selected; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool CheckForObjectL();

        /**
        * If possible, brings up a dialog to edit the format of the selected
        * embedded object. The format covers cropping, scaling, and whether to
        * display the object as an icon or a full representation. This method 
        * calls the <code>RunFormatObjectDlgLD()</code> method, and only returns
        * when the dialog is dismissed.
        *
        * @remarks To edit the content of the embedded object, use
        *          <code>ReEditObjectL()</code>
        * @see
        */
        IMPORT_C void EditPictureFormatL();

        /**
        * Updates the text, text view, and scrollbars when the format of a 
        * picture has been changed.
        *
        * @remarks This needs to be called when the underlying rich text
        *          is changed directly by an application. The Rich Text Editor
        *          API methods take care of calling this
        * @see
        */
        IMPORT_C void PictureFormatChangedL();

        /**
        * Gets the embedded application that corresponds to the object at the
        * specified document position.
        *
        * @param aDoor On return, a pointer to the embedded object wrapper
        * @param aDoc On return, points to the embedded object
        * @param aDocPos The cursor position, or index, of the embedded object
        *                in the rich text
        * @remarks <code>CApaDoor</code> is defined in apgdoor.h.
        *          <code>CApaDocument</code> is defined in apparc.h
        * @see
        */
        IMPORT_C void GetEmbeddedAppL(CApaDoor*& aDoor,CApaDocument*& aDoc,TInt aDocPos);

        /**
        * Sets all embedded objects in the text to be icons, temporarily.
        *
        * @remarks Calls <code>UpdatePictureFormatL(0, iText->DocumentLength())</code>
        *          where <code>iText</code> is the internal rich text object 
        *          pointer
        * @see
        */
        IMPORT_C void UpdatePictureFormatL();

        /**
        * Sets all embedded objects in the specified text region to be
        * icons, temporarily.
        *
        * @param aStartPos The start position to search for icons
        * @param aLength The length that defines the end position from which to
        *                search for icons
        * @remarks
        * @see
        */
        IMPORT_C void UpdatePictureFormatL(TInt aStartPos,TInt aLength);

        /**
        * Sets the default size of icons that represent embedded objects.
        * Future iconic embedded objects take this size.
        *
        * @param aSize The default size
        * @remarks This does not affect existing embedded objects
        * @see
        */
        IMPORT_C void SetDefaultIconicDoorSize(const TSize& aSize); 

        /**
        * Gets the default size of icons that represent embedded documents.
        *
        * @return the default size
        * @remarks
        * @see
        */
        IMPORT_C const TSize& DefaultIconicDoorSize() const;

        /**
        * Updates the size of all embedded object icons and reformats the 
        * rich text appropriately. This should be called after 
        * <code>SetDefaultIconicDoorSize()</code> to update existing icons.
        *
        * @remarks Calls <code>UpdatePictureSizeL(0, iText->DocumentLength())</code>
        *          where <code>iText</code> is the internal rich text object 
        *          pointer
        * @see
        */
        IMPORT_C void UpdatePictureSizeL();

        /**
        * Updates the size of all embedded object icons in the selected text,
        * and then reformats the rich text appropriately. This should be called
        * after <code>SetDefaultIconicDoorSize()</code> to update existing icons.
        *
        * @param aStartPos The start position, or index, to search for icons
        * @param aLength The length that defines the end position from which to
        *                search for icons
        * @remarks
        * @see
        */
        IMPORT_C void UpdatePictureSizeL(TInt aStartPos,TInt aLength);

        /**
        * @deprecated
        */
        IMPORT_C void SetParserObserver(MEikRichTextEditorParserObserver* aObserver); // no longer does anything

        /**
        * Clears the parser banner, which is the Click To... icon displayed
        * when the cursor is within a Dynamic Navigation Link.
        * This method enables the parser banner, if required, 
        * and sets its boundaries.
        *
        * @param aEnable Set to <code>ETrue</code> to enable the parser banner; 
        *                <code>EFalse</code> to disable it
        * @param aParserBannerBounds <code>EParserBannerBoundByScreen</code> if the 
        *                            banner is bound by the screen; or
        *                            <code>EParserBannerBoundByOwnerRect</code> if it is to
        *                            be bound by the 
        *                            <code>CEikRichTextEditor</code>
        * @remarks
        * @see
        */
        IMPORT_C void EnableParserBanner(TBool aEnable, CCknParserBanner::TParserBannerBounds aParserBannerBounds);
    public: // from CCoeControl

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
        * @see CCoeControl
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Handles a pointer event.
        *
        * @param aPointerEvent The pointer event
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * Constructs a Rich Text Editor from a resource file. 
        *
        * @param aReader A resource reader
        * @remarks The resource type is <code>RTXTED</code>
        * @see CCoeControl
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Activates the Rich Text Editor. 
        *
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void ActivateL();

        /**
        * Called when the Rich Text Editor's focus has changed.
        *
        * @param aDrawNow Whether or not to redraw the control immediately
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);
    public: // from CEikEdwin

        /**
        * Replaces the current text, and returns the old text through
        * <code>aOutText</code>
        *
        * @param aInText The text with which the current text is replaced
        * @param aOutText On return, the old text
        * @remarks <code>CGlobalText</code> is defined in txtglobl.h. 
        * @see 
        * @panic Panics with <code>EEikPanicNullPointer</code> if 
        *        <code>aInText</code> or <code>aOutText</code> are <code>NULL</code>
        */
        IMPORT_C void CopyDocumentContentL(CGlobalText& aInText,CGlobalText& aOutText);

        /**
        * Handles scrollbar events passed by this control's scrollbars.
        *
        * @param aScrollBar The scrollbar on which the event occurred
        * @param aEventType The type of event to which a response is required
        * @remarks <code>CEikScrollBar</code> is defined in eikscrlb.h
        * @see 
        */
        IMPORT_C void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType);
    protected:
    enum // internal flags
        {
        ECropFromLeft           =0x00010000,
        ECropFromRight          =0x00020000,
        ECropFromTop            =0x00040000,
        ECropFromBottom         =0x00080000,
        EReEditingObject        =0x00100000
        };

    private: // from CoeControl
        IMPORT_C void Draw(const TRect& aRect) const;
        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2();
    private: // from CEikEdwin
        IMPORT_C void HandleTextPastedL(TInt aStartPos,TInt& aLength);
        IMPORT_C void Reserved_3();
    private: // from MApaEmbeddedDocObserver
        IMPORT_C void NotifyExit(TExitMode aMode);
    private: // from MRichTextStoreResolver
        IMPORT_C const CStreamStore& StreamStoreL(TInt aPos) const;
    private: // from MPictureFactory
        IMPORT_C void NewPictureL(TPictureHeader& aHdr,const CStreamStore& aDeferredPictureStore) const;
    private: // from MEditObserver
        IMPORT_C void EditObserver(TInt aStartEdit,TInt aEditLength);
    private:
        void CommonConstructL();
        static TInt InsertEmbeddedDocL(TAny *aThis);
        static TInt DeleteEmbeddedDoc(TAny *aThis);
        static TInt UpdateEmbeddedDocL(TAny* aThis);
        static TInt TryDeleteEmbeddedDocL(TAny *aThis);
        void InsertPictureL(const TPictureHeader& aPictureHeader);
        void DoInsertPictureL(TBool& aFormatHasChanged,const TPictureHeader& aPictureHeader);
        void DoReEditObjectL(TInt aDocPos);
        void RoomForObjectL();
        void InsertObjectL(CApaDocument* aDoc,TObjectFormat aFormat,TBool aEditDoc);
        void SetTextObserver(CRichText& aText);
        inline void DoReportEdwinEventL(MEikEdwinObserver::TEdwinEvent aEventType);
    
        TInt CheckParserBannerCanBeShown(MParser* aParser, TBool& aResult);
        void ShowParserBannerL(MParser* aParser,TInt aTagStart,TInt aTagLength);
        TBool CheckLinkAndActivateL(const TInt aCursorPos, const TBool aKeyboard);
        void ClearParserBanner();
        void RepositionParserBannerL();
        void CalcBannerBoundingRect(TRect& aBoundingRect);
        void CalcBannerPosition(TPoint& aPos, TInt aTextHeight);
    protected:
        TSize iDefaultIconicDoorSize;
    private:
        CEikRubberBand* iRubberBand;
        TPictureHeader iEmbeddedDoc;
        CIdle* iEmbeddedDocUpdate;
        CBufStore* iBufStore;
        CEikParserManager* iParserManager;
        CCknParserBanner* iParserBanner;

    private:
    friend class CEikParserManager;
    };

inline void CEikRichTextEditor::DoReportEdwinEventL(MEikEdwinObserver::TEdwinEvent aEventType)
    {ReportEdwinEventL(aEventType);}


#endif  // EIKRTED_H

// End of File
