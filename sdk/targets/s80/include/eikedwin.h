/*
* ==============================================================================
*  Name        : eikedwin.h
*  Part of     : CKON
*  Interface   : Edwin API
*  Description : Basic text editor control.
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

#ifndef EIKEDWIN_H
#define EIKEDWIN_H


// INCLUDES
#include <s32std.h>
#include <gdi.h>
#include <txtetext.h>
#include <medobsrv.h>
#include <gulutil.h>
#include <fepbase.h>
#include <frmvis.h>
#include <frmtview.h>
#include <uikon.hrh>
#include <eikbctrl.h>
#include <eikedwob.h>
#include <eiksbfrm.h>


// DATA TYPES

/** 
 * the UID of the corresponding class. This UID is used in a 
 * <code>CCoeEnv::Static()</code> call to a pointer to an object of type 
 * <code>CEikEdwinClipboardObserverTls</code>
 */
const TUid KUidEdwinClipboardObserverTls={0x1000AD19};

/** 
 * The <code>TReplaceOption</code> enumeration defines values that control the 
 * replace functionality.
 */
enum TReplaceOption
    {
    /** do not replace */
    ENoReplace,
    /** replace once */
    EReplaceOnce,
    /** replace all */
    EReplaceAll,
    /** skip the replace */
    EReplaceSkip
    };

/** 
 * The struct <code>SEdwinFindModel</code> defines a state structure used by 
 * the find and replace functionality.  The structure is used for 
 * communication between the Edwin and the Find/Replace dialog.
 */
struct SEdwinFindModel
    {
    /** 
     * the state of the find and replace operation (see 
     * <code>CEikEdwin::TFindFlags</code>)
     */
    TInt iFlags;
    /** the text to search for */
    TBuf<EEikEdwinFindStringMaxLen> iText;
    /** the text to replace the search text */
    TBuf<EEikEdwinFindStringMaxLen> iReplaceText;
    /** the current replace operation */
    TReplaceOption iReplaceOption;
    };


// FORWARD DECLARATIONS
class CGlobalText;
class CParaFormatLayer;
class CCharFormatLayer;
class MLayDoc;
class CEikEdwinExtra;
class CLafEdwinCustomDrawBase;
class CLafEdwinCustomWrapBase;
class CEikonEnv;
class CBufStore;

// CLASS DECLARATIONS

/**
* The <code>CEikEdwinDefaultClipboard</code> class provides the default
* implementation of the clipboard functionality defined in
* <code>MEikEdwinClipboardObserver</code>. The methods must be accessed via
* the mixin interface <code>MEikEdwinClipboardObserver</code>,
* as these are not exported.
*
* @lib eikcoctl.lib
* @since Series90 1.0
*/
class CEikEdwinDefaultClipboard : public CBase, public MEikEdwinClipboardObserver
    {
    public:
        /**
        * Starts the two-phase object construction.
        * 
        * @param aEikEnv The <code>CEikonEnv</code> environment for the Edwin 
        *                clipboard. This is used to display infoprint error 
        *                messages
        * @return a pointer to the clipboard class
        * @remarks
        * @see
        */
        IMPORT_C static CEikEdwinDefaultClipboard* NewL(CEikonEnv& aEikEnv);
        void HandleNothingSelected(TClipboardFunc aClipboardFunc);
        void HandleCopiedToClipboard();
        void Release();
    private: 
        CEikEdwinDefaultClipboard(CEikonEnv& aEikEnv);
        void MEikEdwinClipboardObserver_Reserved_1();
    private:    
        CEikonEnv& iEikEnv;

    };

/**
 * The <code>CEikEdwinClipboardObserverTls</code> class implements global 
 * static storage and access to the object, thereby providing the default 
 * implementation of clipboard feedback.
 *
 * @lib eikcoctl.lib
 * @since Series90 1.0
 */
class CEikEdwinClipboardObserverTls : public CCoeStatic
    {
    public:
    // Constructors and destructor

        /**
        * The object destructor.
        */
        ~CEikEdwinClipboardObserverTls();


    // New methods
        
        /**
        * A static method that sets <code>aClipboardObserver</code> to be the 
        * current clipboard observer. The first time this method is called,
        * <code>Tls</code> gets created. If a clipboard is already assigned,
        * it is released and re-assigned to <code>aClipboardObserver</code>.
        *
        * @param aClipboardObserver The clipboard observer
        * @remarks
        * @see
        */
        IMPORT_C static void SetL(MEikEdwinClipboardObserver* aClipboardObserver);
        /** @internal */
        static MEikEdwinClipboardObserver* Current();

    private: //Methods

        /**
        * The default object constructor.
        */
        inline CEikEdwinClipboardObserverTls();

        /**
        * Gets the pointer to "this".
        */
        inline static CEikEdwinClipboardObserverTls* Self();

    private:     // Data
        MEikEdwinClipboardObserver* iClipboardObserver;

    };

inline CEikEdwinClipboardObserverTls::CEikEdwinClipboardObserverTls()
    : CCoeStatic(KUidEdwinClipboardObserverTls)
    {}

inline CEikEdwinClipboardObserverTls* CEikEdwinClipboardObserverTls::Self()
    {
    return (static_cast<CEikEdwinClipboardObserverTls*>(CCoeEnv::Static(KUidEdwinClipboardObserverTls)));
    }


/**
* The <code>CEikEdwin</code> class is the base class for controls that allow
* the entry, editing, and display of text and numbers. The properties of a
* particular Edwin object can be set using bitwise flags that are defined in
* member enumerations such as <code>TFlags</code>. Controls derived from Edwin
* support Front End Processors, if present on the target machine, and so are an
* effective way of getting text and numeric data input from the user. The text 
* currently being composed by the user is called the composition text.
*
*  @lib eikcoctl.lib
*  @since 6.0
*/
class CEikEdwin : public CEikBorderedControl, public MEikScrollBarObserver, public CTextView::MObserver, public MEditObserver
    {
public:  // Declarations
    /**
     * The <code>TFlags</code> may be combined with a bitwise OR to form the
     * <code>aEdwinFlags</code> argument to <code>ConstructL()</code>, or the 
     * flags field of an <code>EDWIN</code> resource structure run through 
     * a call of <code>ConstructFromResourceL()</code>. These flags are 
     * duplicated in uikon.hrh (see <code>EEikEdwinKeepDocument</code> etc.).
     */
    enum TFlags
        { 
        /** the Edwin does not destroy its content on destruction */
        EKeepDocument           =0x00000001,
        /**
        * the content buffer uses segmented storage
        * (see <code>CEditableText::ESegmentedStorage</code>). Segmented
        * storage places the data in more than one heap location. Each forms
        * a part of the buffer. When this flag is not used, the content buffer
        * is stored in one memory location (referred to as a flat buffer). 
        * Segmented memory tends to be more flexible in memory allocation, 
        * but is slower in operation than flat buffering
        */
        ESegmentedStorage       =0x00000002,
        /**
        * the size specified in the resource used to construct the object is
        * given in pixels, not characters
        */
        EWidthInPixels          =0x00000004,
        /**
        * no automatic selection takes place. Typically, the entire text is
        * selected as one operation whenever the Edwin is created, resized, or 
        * has its text set 
        */
        ENoAutoSelection        =0x00000008,
        /**
        * when the control is activated, the cursor is moved
        * to the end of the text
        */
        EJustAutoCurEnd         =0x00000010,
        /** do not wrap the text being edited */
        ENoWrap                 =0x00000020,
        /** use a line cursor instead of a block cursor */
        ELineCursor             =0x00000040,
        /** horizontal scrolling is disabled */
        ENoHorizScrolling       =0x00000080,            
        /**
        * if set, scrollbars for long documents appear inside the Edwin,
        * reducing the area available to the Edwin. If not set, scrollbars
        * appear outside the Edwin. This does not affect the <code>TSize</code>
        * values returned by method <code>MinimumSize()</code>
        */
        EInclusiveSizeFixed     =0x00000100,
        /**
        * sets the height of the Edwin in lines, according to text supplied
        * by the user
        */
        EUserSuppliedText       =0x00000200,
        /** the Edwin is a window-owning control */
        EOwnsWindow             =0x00000400,
        /** the Edwin does not respond to user input */
        EDisplayOnly            =0x00000800,
        /** if the Edwin loses focus, do not hide the selection */
        EAlwaysShowSelection    =0x00001000,
        /** the Edwin is read-only. Attempting to add text displays a message
        * to say it is read-only */
        EReadOnly               =0x00002000,
        /** no special attempt to delete embedded pictures cleanly will be
        * made. This flag does not apply to Edwins that do not edit rich text */
        EAllowPictures          =0x00004000,
        /** enable undo operations */
        EAllowUndo              =0x00008000,
        /** do not allow line or paragraph breaks in the text being edited */
        ENoLineOrParaBreaks     =0x00010000,
        /** allow only ASCII characters */
        EOnlyASCIIChars         =0x00020000,
        /** 
         * the Edwin control is resizable, for example, when contained 
         * in a parent control. Should the parent control be required 
         * to resize itself, the image of the Edwin control that is 
         * displayed can be resized to fit within the parent control. 
         * This does not affect the maximum width of the Edwin 
         * control 
         */
        EResizable              =0x00040000,
        /** 
         * the Edwin ignores the virtual cursor.
         * <b>Note</b>: Touch screen devices do not use the virtual cursor.
         */
        EIgnoreVirtualCursor    =0x00080000,
        /** no custom draw is done */
        ENoCustomDraw           =0x01000000,
        /** custom wrap is allowed */
        ECustomWrap             =0x02000000,
        /** no text parsers are used */
        ENoTextParsers          =0x04000000,
        /** the Edwin ignores tab key presses */
        EDontConsumeTab         =0x08000000, 
        /** on focus loss, the Edwin scrolls to the beginning of the text.
        * On focus gain, the cursor goes to the end of the text and scrolls to
        * show the cursor, if required */
        EAutoScrollOnFocusChange=0x10000000,
        /** prevents the Edwin sending the notification to FEP */
        ENoCursorChangeEvent    =0x20000000,
        /** borders are allowed */
        EAllowBorders           =0x40000000
        };
    /**
     * The <code>TClipboardFunc</code> enumeration specifies actions for the 
     * <code>ClipboardL()</code> method.  
     */
    enum TClipboardFunc
        {
        /** do nothing */
        ENoClipboard,
        /** cut selected content */
        ECut,
        /** copy selected content */
        ECopy,
        /** paste from clipboard */
        EPaste
        };
    /**
     * The <code>TFindFlags</code> enumeration specifies the text search 
     * flags. These may be combined with a bitwise OR, 
     * for example, see <code>FindL()</code>.
     */
    enum TFindFlags
        {
        /** search upwards */
        EFindDirectionUp        =0x001,
        /** search for whole words only */
        EFindWholeWord          =0x002,
        /** the search is case-sensitive */
        EFindCaseSensitive      =0x004,
        /** find again */
        EFindAgain              =0x008,
        /** do not display a busy message */
        ENoBusyMessage          =0x010,
        /** the file is read-only */
        EReadOnlyFile           =0x020,
        /** the search ignores any accent differences */
        EFindFoldAccents        =0x040,
        /** new searches start and end at the current cursor position */
        EFindStartAtCursor      =0x080,
        /** no scrolling is performed to reposition the found text */
        EFindNoScroll           =0x100,
        /** set in <code>CallBackFindL()</code> or <code>CallBackReplaceL()</code>
        * to reposition the find/replace dialog */
        EFindDialogTopRight     =0x200                      
        };
    /**
     * The <code>TSetContent</code> enumeration specifies a copy or replace 
     * operation. When content is supplied to an Edwin using 
     * <code>SetDocumentContentL()</code>, the Edwin can either copy the 
     * supplied content into its existing content or replace the existing
     * content with the supplied content.
     */
    enum TSetContent
        {
        /** replace the Edwin's existing content */
        EUseText,    
        /** copy the supplied content into the existing content */
        ECopyText         
        };
    /**
     * The <code>TOwnershipType</code> enumeration specifies whether 
     * the Edwin owns the control contents that it is being used to edit. If 
     * the Edwin owns the contents, the contents are destroyed on destruction.
     */
    enum TOwnershipType
        {
        /** the contents are owned by the Edwin */
        EOwnsText, 
        /** the contents are owned by another object */
        EDoesNotOwnText 
        };
    /**
     * The <code>TEdwinHotKeys</code> enumeration defines the order of hotkeys 
     * defined in an Edwin resource structure. Not all are applicable to plain 
     * text editors.
     */
    enum TEdwinHotKeys
        {
        /** cut */
        EHotKeyCut,
        /** copy */
        EHotKeyCopy,  
        /** paste */
        EHotKeyPaste,   
        /** undo */
        EHotKeyUndo, 
        /** find */
        EHotKeyFind,        
        /** insert a character */
        EHotKeyInsertChar,      
        /** bold */
        EHotKeyBold,  
        /** italic */
        EHotKeyItalic,         
        /** underline */
        EHotKeyUnderline,     
        /** font */
        EHotKeyFont,   
        /** insert an object */
        EHotKeyInsertObject,       
        /** edit an object */
        EHotKeyEditObject,      
        /** format an object */
        EHotKeyFormatObject                             
        };

    public:
    // Constructors and destructor
        /**
        * The object destructor.
        */
        IMPORT_C ~CEikEdwin();

        /**
        * The default object constructor.
        *
        * @remarks The Edwin control does not have FEP support if there is 
        *          insufficient memory available. The FEP allows alternative 
        *          input interfaces to the Edwin control, such as speech and 
        *          handwriting recognition. If the FEP is not created, the 
        *          Edwin control continues to function but without such input 
        *          interfaces
        * @see
        */
        IMPORT_C CEikEdwin();

        /**
        * Creates a new Edwin control, specifying the border to use.
        *
        * @param aBorder The Edwin border
        * @remarks The Edwin control does not have FEP support if there is 
        *          insuficient memory available. The FEP allows alternative 
        *          input interfaces to the Edwin control, such as speech and 
        *          handwriting recognition. If the FEP is not created, the 
        *          Edwin control continues to function but without such input 
        *          interfaces
        * @see
        */
        IMPORT_C CEikEdwin(const TGulBorder& aBorder);

        /**
        * Completes construction of a new Edwin object, initializing its
        * heap-stored members from the supplied arguments. This method leaves
        * if any of the pointer members that are being constructed leave.
        *
        * @param aEdwinFlags A bitwise ORed combination of flags from
        *                    <code>TFlags</code>
        * @param aWidthInChars Specifies the width of the Edwin in characters or
        *                      pixels (see the <code>EWidthInPixels</code> flag)
        * @param aTextLimit The maximum length for the editable text
        * @param aNumberOfLines The height for the Edwin, in lines
        * @remarks If the width is defined in characters, the unit of width is 
        *          defined by the widest character
        * @see
        */
        IMPORT_C void ConstructL(TInt aEdwinFlags=0,TInt aWidthInChars=0,TInt aTextLimit=0,TInt aNumberOfLines=0);

        /**
        * Sets the Edwin observer that is called back with control events 
        * associated with the Edwin.
        *
        * @param aEdwinObserver The new observer
        * @remarks Avoid using a <code>NULL</code> pointer
        * @see AddEdwinObserverL()
        * @see RemoveEdwinObserver()
        * @see ReportEdwinEventL()  
        */
        IMPORT_C void SetEdwinObserver(MEikEdwinObserver* aEdwinObserver);

        /**
        * Adds an observer of standard Edwin events to a list of observers,
        * creating the list if necessary. This method may be called many times 
        * and is independent of calls to <code>SetEdwinObserver</code>.
        *
        * @param aEdwinObserver The observer to add to the list of observers
        * @remarks Observers added to this list are called by 
        *          <code>ReportEdwinEventL()</code>. Avoid adding a 
        *          <code>NULL</code> pointer
        * @see SetEdwinObserver()
        * @see RemoveEdwinObserver()
        * @see ReportEdwinEventL()  
        */
        IMPORT_C void AddEdwinObserverL(MEikEdwinObserver* aEdwinObserver);

        /**
        * Removes the specified observer from the list of observers. If
        * <code>aEdwinObserver</code> is not an observer, this method
        * has no effect.
        *
        * @param aEdwinObserver The observer to remove from the list of observers
        * @remarks The <code>MEikEdwinObserver</code> class is a mixin interface 
        *          class for observing the contents and cursor position of
        *          an Edwin control
        * @see SetEdwinObserver()
        * @see AddEdwinObserverL() 
        */
        IMPORT_C void RemoveEdwinObserver(MEikEdwinObserver* aEdwinObserver);

        /**
        * Sets the containing window for the Edwin.
        * If the <code>EOwnsWindow</code> flag is set, the method creates a 
        * window, making the Edwin a window-owning control.
        *
        * @remarks The <code>EOwnsWindow</code> flag must be set
        * @see SetContainerWindowL(const CCoeControl&)  
        */
        IMPORT_C void SetContainerWindowL();

        /**
        * Sets the Edwin's editable content. Before calling this method, get
        * the <code>iText</code> pointer, because <code>iText</code> is
        * replaced by <code>aText</code>. Also, frees the memory by deleting
        * the previous <code>iText</code> contents.
        *
        * @param aText The new value for the content
        * @param aContent Specifies whether to use <code>aText</code> itself,
        *                 or to copy its content
        * @remarks <code>aText</code> must be a valid object. 
        *          The text can be referenced by calling <code>Text()</code> 
        *          to check whether the pointer returned is <code>NULL</code> 
        *          or contains a pointer.
        *          If <code>aText</code> is not a valid object, the method
        *          panics with <code>EEikPanicNullPointer</code>
        * @see
        */
        IMPORT_C void SetDocumentContentL(CGlobalText& aText,TSetContent aContent=CEikEdwin::ECopyText);

        /**
        * Handles key events offered to the control by the control environment.
        * 
        * @param aKeyEvent The key event offered. <code>TKeyEvent</code> 
        *                  contains four fields;
        *      <code>iCode</code>, <code>iScanCode</code>,
        *      <code>iModifiers</code>, and <code>iRepeats</code>.
        *      <code>iCode</code> represents keys found on a PC keyboard,
        *      such as F1 to F12. If the terminal does not have a keyboard, the 
        *      keys can be represented using a FEP. For more information on 
        *      <code>TKeyCode</code>, see <code>E32keys.h</code>. Variable 
        *      <code>iScanCode</code> is rarely used, 
        *      and represents the scan codes of keyboard positions of keys on
        *      the 81-key IBM keyboard. The variable <code>iModifiers</code> 
        *      allows the testing for modifier keys such as <code>Ctrl</code>.
        *      The variable <code>iRepeats</code> contains the number of 
        *      auto-repeats that have been missed since handling the last key 
        *      event
        * @param aType  The type of key event, either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this
        *         control. <code>EKeyWasConsumed</code> if the control takes
        *         action on the key event; <code>EKeyWasNotConsumed</code>
        *         otherwise
        * @remarks If used in a view, the developer is responsible for
        *          implementing this method. The framework calls this method
        * @see     <code>CCoeControl</code>
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Handles focus-change events. This method is called whenever there is a 
        * gain or loss of focus.  
        *
        * @param aDrawNow Whether to redraw the Edwin
        * @remarks <code>EAutoScrollOnFocusChange</code> should 
        *          not be set  
        * @see CCoeControl
        */
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);

        /**
        * Prepares the Edwin for loss of focus. 
        * 
        * @remarks The framework calls this method for any control that it
        *          is about to remove focus from. The method can therefore
        *          be used to save any relevant information prior to focus 
        *          loss
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void PrepareForFocusLossL();

        /**
        * Sets the Edwin as ready for drawing.
        * 
        * @remarks Calling this method is often unnecessary. Preconditions: 
        *          <code>iTextView</code> and <code>iText</code> must be 
        *          initialized. Call <code>ConstructL()</code> to initialize 
        *          <code>iText</code> and <code>CreateTextViewL()</code> to 
        *          create a text view. <code>iTextView</code> and
        *          <code>iText</code> are member variables of Edwin and are
        *          required to support certain Edwin functionality
        * @see CCoeControl
        */
        IMPORT_C void ActivateL();

        /**
        * Construct an Edwin control from a resource file. This method
        * initializes the heap-stored members from an <code>EDWIN</code>
        * resource and leaves if any of the pointer members being 
        * constructed leave.
        *
        * @param aReader A resource reader 
        * @remarks Resource is of type <code>EDWIN</code> 
        * @see CCoeControl
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Handles pointer events that occur in the control.
        *
        * @param aPointerEvent The pointer event to respond to
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * Gets the minimum size of this Edwin for automatic layout control
        * contexts such as dialogs.
        * 
        * @return the width and height of the Edwin. The <code>TSize</code> 
        *         contains the two <code>TInt</code> values: <code>iWidth</code>
        *         and <code>iHeight</code>
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Draws the Edwin control on request.
        *
        * @param aRect Optional. If supplied, the rectangle in which to draw 
        *              the Edwin
        * @remarks The <code>aRect</code> is not used in the Edwin 
        *          implementation of <code>Draw()</code>, but the method can 
        *          be overridden to use it
        * @see CCoeControl
        */
        IMPORT_C void Draw(const TRect& aRect) const;

        /**
        * Sets the dimmed/undimmed state of the Edwin control. Dimming prevents
        * the Edwin control from accepting user interaction.  
        *
        * @param aDimmed <code>ETrue</code> to dim the Edwin; <code>EFalse</code> 
        *                to undim the Edwin
        * @remarks <code>SetDimmed()</code> does not initiate a redraw of the 
        *          control. The application should call <code>DrawNow()</code> or 
        *          <code>DrawDeferred()</code> if a redraw is required after 
        *          calling <code>SetDimmed()</code>
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SetDimmed(TBool aDimmed);

        /**
        * Sets the containing window for the Edwin by copying it from the 
        * specified parent. This method also copies a control context from 
        * <code>aParent</code> if one has not been previously set.
        *
        * @param aParent The control to set as this Edwin's parent
        * @remarks
        * @see
        */
        IMPORT_C void SetContainerWindowL(const CCoeControl& aParent);

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        * @see TCoeColorUse
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

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
        * Returns the input capabilities of the Edwin. Typically, called by the 
        * FEP-aware text editor. By default, the Edwin is capable of handling all 
        * text input. 
        *
        * @return the input capabilities
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;

        /**
        * Sets the input capabilities of the Edwin (the types of text input 
        * that the Edwin allows).
        *
        * @param aInputCapabilities The input capabilities to be set
        * @remarks Not available before Release 006
        */
        IMPORT_C void SetInputCapabilitiesL(const TCoeInputCapabilities& aInputCapabilities);

        /**
        * In debug mode, writes the internal state of the control and its 
        * components to <code>aStream</code>. In release mode, there is no 
        * implementation unless the method is overridden.
        *
        * @param aWriteStream The reference to the write stream  
        * @remarks This method is designed to be overridden and the base called 
        *          by subclasses
        * @see
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

        /**
        * Handles scrollbar events passed by this Edwin's scrollbars.
        *
        * @param aScrollBar The scrollbar on which the event occurred
        * @param aEventType The type of event to which a response is required
        * @remarks
        * @see MEilScrollBarObserver
        */
        IMPORT_C void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType);

        /**
        * Responds to text height change. This method reports the event 
        * <code>EEventSizeChanging</code> to the Edwin observer of type 
        * <code>MEikEdwinObserver</code> when the text view height changes. 
        * This method checks that the new height is within the Edwin's minimum 
        * and maximum height limits and redraws the Edwin within those limits.
        *
        * @param aTextView The text view for which the height has changed
        * @remarks This method is defined by <code>MObserver</code> (an inner class 
        *          of <code>CTextView</code>). It is called after reformatting but 
        *          before redisplay, to allow the edit window to be resized
        * @see
        */
        IMPORT_C void OnReformatL(const CTextView* aTextView);

        /**
        * Gets the number of characters in the Edwin control.
        *
        * @return the number of characters in the Edwin
        * @remarks A text object must exist prior to this call  
        * @see
        */
        IMPORT_C TInt TextLength() const;

        /**
        * Gets the cursor's position in the Edwin control.
        *
        * @return the cursor's position in the Edwin
        * @remarks A <code>CTextView</code> object must exist before 
        *          calling this method
        * @see CreateTextViewL()
        */
        IMPORT_C TInt CursorPos() const;

        /**
        * Gets the number of characters within the selection (including 
        * non-printing characters).
        *
        * @return the number of characters within the selection
        * @remarks A <code>CTextView</code> object must exist before 
        *          calling this method. After a change has been made to the text 
        *          layout, a reformat and redraw should normally take place. 
        *          <code>CTextView</code> provides methods that are optimized 
        *          for reformat operations. For example, when a global formatting 
        *          parameter is changed, such as the wrap width, the layout of 
        *          the whole document must be recalculated. Method 
        *          <code>SelectionLength</code> provides the information that is
        *          required, such as the length of items selected, to the
        *          <code>CTextView</code> methods
        * @see CreateTextViewL()
        */
        IMPORT_C TInt SelectionLength() const;

        /**
        * Gets the number of objects selected in the Edwin.
        *
        * @return the number of selected objects
        * @remarks The objects are pictures of type 
        *          <code>CEditableText::EPictureCharacter</code>
        * @see
        */
        IMPORT_C TInt CountSelectedObjects() const;

        /**
        * Gets the cursor selection. If no text view is associated to this Edwin 
        * this returns <code>TCursorSelection(0,0)</code>.
        *
        * @return the cursor selection
        * @remarks The selection covers the text from the lower to the higher 
        *          position, not including the character after the higher position
        * @see
        */
        IMPORT_C TCursorSelection Selection() const;

        /**
        * Removes the selection and any composition text. The cursor position is 
        * unaffected. If there is no selected text, this method has no effect.
        *
        * @remarks
        * @see
        */
        IMPORT_C void ClearSelectionL();

        /**
        * Sets the text selection by highlighting the selected area and making the 
        * new cursor position visible. Any previous selection is cancelled. This 
        * method also updates the scrollbar thumbs, if present.
        *
        * @param aCursorPos The cursor's position. The terminating point of 
        *                   the selected text
        * @param aAnchorPos The anchor's position. The starting point of the 
        *                   selected text
        * @remarks The positions referred to are represented as indexes
        * @see
        */
        IMPORT_C void SetSelectionL(TInt aCursorPos,TInt aAnchorPos);

        /**
        * Sets the cursor's position within the Edwin control.
        * If the new position is not visible the text is scrolled so that the
        * line containing the cursor is visible. This method also updates the 
        * scrollbar thumbs, if present.
        *
        * @param aCursorPos The new cursor position
        * @param aSelect <code>ETrue</code> to extend the cursor selection to the 
        *        new position; <code>EFalse</code> otherwise
        * @remarks If <code>aSelect == ETrue</code>, text is selected from the 
        *          previous cursor position
        * @see
        */
        IMPORT_C void SetCursorPosL(TInt aCursorPos,TBool aSelect);

        /**
        * Selects the entire contents of the Edwin.
        *
        * @remarks Works like CTRL+A in Word
        * @see
        */
        IMPORT_C void SelectAllL();

        /**
        * Recalculates the screen width of an Edwin using <code>aWidthInChars</code>.
        * This method is called during construction. If the Edwin control only 
        * allows editing of numbers, the width of the zero character is used, 
        * otherwise <code>CFont::MaxNormalCharWidthInPixels</code> is used. If
        * the flag <code>EWidthInPixels</code> (defined in the 
        * <code>CEikEdwin</code> class) is set, the <code>aWidthInChars</code> 
        * argument is measured in pixels, not characters.
        *
        * @param aWidthInChars The width in either pixels or characters
        * @remarks <code>EWidthInPixels</code> is also defined in uikon.hrh as 
        *          <code>EEikEdwinWidthInPixels</code> 
        * @see
        */
        IMPORT_C void CalculateWidth(TInt aWidthInChars);

        /**
        * Copies the entire content of an Edwin control into a descriptor.
        * It is the caller's responsibility to provide a large enough buffer.
        *
        * @param aDes An initialized descriptor that, on return, contains a copy
        *             of the content of this Edwin
        * @remarks <code>TextLength()</code> can be called to determine the size 
        *          of buffer to allocate. If the buffer size is not large 
        *          enough, the method panics
        * @see
        */
        IMPORT_C void GetText(TDes& aDes) const;

        /**
        * Gets a new buffer that contains a copy of the content of the Edwin. This
        * method creates a new <code>HBuf</code>, independent of the Edwin control. 
        * A 16-bit build variant is generated for a Unicode build and an 8-bit 
        * build variant is generated for a non-Unicode build.
        * 
        * @return a new copy of the Edwin contents
        * @remarks It is the developer's responsibility to delete memory allocated 
        *          for the <code>HBuf</code> by this method
        * @see
        */
        IMPORT_C HBufC* GetTextInHBufL() const;

        /**
        * Sets the contents of this Edwin from the contents of a descriptor.
        *
        * @param aDes The descriptor from which to copy
        * @remarks
        * @see
        */
        IMPORT_C void SetTextL(const TDesC* aDes);

        /**
        * Handles the cut, copy, and paste commands.
        * This method also reports to the observer when the state of the Edwin
        * control is changed.
        *
        * @param aClipboardFunc The enumerated clipboard operation to be performed
        * @remarks The framework calls this method to handle standard clipboard 
        *          functionality. <code>ClipboardL()</code> implements a switch 
        *          that calls the appropriate method dependent on 
        *          <code>aClipboardFunc</code>. The operations are selected 
        *          by passing in enumeration values such as 
        *          <code>ECut</code>, <code>ECopy</code> and <code>EPaste</code>.
        *          The values are defined in <code>CEikEdwin::TClipboardFunc</code>
        * @see
        */
        IMPORT_C void ClipboardL(TClipboardFunc aClipboardFunc);

        /**
        * Inserts a field at the current cursor position.
        * If a selection was made, the field replaces that selection.
        *
        * @param aField The text field to insert
        * @param aFieldType The type of the text field
        * @remarks Some examples of field types are date and time, page number.
        *          and filename. Field type UIDs are defined in 
        *          flddef.h
        * @see
        */
        IMPORT_C void InsertFieldL(CTextField* aField,TUid aFieldType);

        /**
        * Updates all of the fields in the Edwin's contents.
        *
        * @remarks
        * @see
        */
        IMPORT_C void UpdateAllFieldsL();

        /**
        * Updates the field in an Edwin control that contains the cursor. The 
        * method does nothing if the cursor is not within a field. Updating 
        * involves calculating the new content for the field and replacing 
        * the field's existing content with the new content.
        *
        * @remarks
        * @see InsertFieldL()
        * @see UpdateAllFieldsL()
        */
        IMPORT_C void UpdateCurrentFieldL();

        /**
        * Counts and returns the number of words in the document.
        *
        * @return the number of words in the Edwin control
        * @remarks
        * @see
        */
        IMPORT_C TInt CountWords();

        /**
        * Inserts the contents of a text file into the text being edited at the
        * current cursor position.
        *
        * @param aFileName The file to open and read
        * @param aTextOrganisation How to handle line breaks. The default is 
        *                          <code>CPlainText::EOrganiseByLine</code>. See 
        *                          txtetext.h for an explanation of the available 
        *                          possibilities
        * @remarks When importing text from a text file, a single line feed or a 
        *          line feed followed by a carriage return is converted into a 
        *          space character. A line feed that is followed by another line 
        *          feed is converted to a 
        *          <code>CEditableText::EParagraphDelimiter</code> 
        * @see txtetext.h 
        */
        IMPORT_C void InsertFromTextFileL(const TFileName &aFileName,const CPlainText::TTextOrganisation aTextOrganisation=CPlainText::EOrganiseByLine);

        /**
        * A call back method used to update scrollbars in the background.
        *
        * @param aPtr A pointer to type <code>TAny</code> gets cast to 
        *             <code>CEikEdwin</code>
        * @return <code>EFalse</code> is always returned.
        * @remarks Scrollbars are updated asynchronously using this method. 
        *          Scrollbar calculations are time consuming, so the task of 
        *          updating them is performed in the background at a lower 
        *          priority
        * @see
        */
        IMPORT_C static TInt IdleL(TAny *aPtr);

        /**
        * Gets a pointer to the contents of the Edwin.
        *
        * @return the pointer to the contents of the Edwin
        * @remarks
        * @see
        */
        IMPORT_C CPlainText* Text() const;

        /**
        * Cancels any current transaction with the Edwin's FEP.
        * Any front-end input windows are removed, any highlighted text being 
        * edited in the Edwin is removed, and the Edwin is rolled back to the
        * state it was in before the FEP transaction started. This method is
        * called by <code>CEikEdwin</code> itself when the document content, the
        * cursor position, or the current selection changes. Canceling
        * outstanding FEP transactions before performing operations on the text
        * programmatically is particularly important when the FEP is 
        * inline-editing an Edwin.
        *
        * @remarks A FEP transaction begins when an event is first intercepted
        *          by the FEP and ends either when the processed text is 
        *          committed to the application underneath, or if it is 
        *          cancelled
        * @see
        */
        IMPORT_C void CancelFepTransaction();

        /**
        * Handles all modifications made by reformatting the entire contents of
        * the Edwin. This method calls <code>CEikEdwin::FormatText()</code> and 
        * redraws the Edwin's contents and scrollbars (if these are ready to be 
        * redrawn).
        *
        * @remarks
        * @see
        */
        IMPORT_C void HandleTextChangedL();

        /**
        * Gets the width used for laying out the text in the Edwin, in pixels.
        * This can be larger or smaller than the specified width of the Edwin
        * control. For example, see <code>SetWysiwygModeOn()</code>.
        *
        * @return the width of the text layout area, in pixels
        * @remarks The width of the Edwin control relates to the maximum 
        *          number of characters allowed
        * @see
        */
        IMPORT_C TInt LayoutWidth() const;
        
        /**
        * Formats and draws the contents of an Edwin, and updates the 
        * scrollbars, if necessary.
        *
        * @remarks
        * @see
        */
        IMPORT_C void NotifyNewDocumentL();
        
        /**
        * Reformats and redraws the contents of an Edwin, and updates the 
        * scrollbars, if necessary.
        *
        * @remarks A text view must exist before calling this method  
        * @see
        */      
        IMPORT_C void NotifyNewFormatL();
        
        /**
        * Gets <code>ETrue</code> if a substring is present in the text being 
        * edited before or after the cursor position. If <code>aFindText</code> is
        * <code>NULL</code>, the current word or selection is searched 
        * for again.
        *
        * @param aFindText The substring to search for
        * @param aFindFlags The <code>TFindFlags</code> find flags
        * @return <code>Etrue</code> if the substring <code>aFindText</code> was 
        *         found; <code>EFalse</code> otherwise
        * @remarks <code>TFindFlags</code> can be ORed together for text searches  
        * @see TFind
        */
        IMPORT_C TBool FindL(const TDesC* aFindText,TInt aFindFlags=0);

        /**
        * Gets the cursor position of the matching text in the Edwin control.
        * The  search starts from <code>aPos</code>. If <code>aFindText</code> is 
        * <code>NULL</code>, the current word or selection is searched for. 
        * If the substring cannot be found, this method returns 
        * <code>KErrNotFound</code>.
        *
        * @param aFindText The descriptor containing the substring to search for
        * @param aPos The cursor position to search from
        * @param aFindFlags The <code>TFindFlags</code> flags
        * @return <code>KErrNotFound</code> if the text was not found,
        *         otherwise the position of the matched substring
        * @remarks
        * @see TFind
        */
        IMPORT_C TInt FindTextL(const TDesC* aFindText,TInt aPos,TInt aFindFlags);

        /**
        * Replaces the highlighted text.
        *
        * @param aFindModel The pointer to the replacement text
        * @remarks
        * @see SEdwinFindModel
        */
        IMPORT_C void ReplaceL(SEdwinFindModel* aFindModel);

        /**
        * Replaces all occurrences of a string with a new text string. Both old 
        * and new text are held in <code>aFindModel</code>.
        *
        * @param aFindModel A pointer to the structure that describes the operation
        * @remarks
        * @see SEdwinFindModel 
        */
        IMPORT_C void ReplaceAllL(SEdwinFindModel* aFindModel);

        /**
        * Sets the Find string to the current word, or selection, and searches for 
        * it. The methods <code>FindL()</code> and <code>FindTextL()</code> call 
        * <code>GetFindText()</code> when they are not supplied with the text to 
        * search for.
        *
        * @param aFindText An empty descriptor
        * @remarks
        * @see
        */
        IMPORT_C void GetFindText(TDes* aFindText);

        /**
        * Updates the scrollbars asynchronously.
        * This method returns immediately after generating a call back to 
        * update the scrollbars, if there is not one waiting to be serviced 
        * already.
        *
        * @remarks
        * @see
        */          
        IMPORT_C void UpdateScrollBarsL();

        /**
        * Creates a scrollbar frame with no pre-allocation of memory
        * for scrollbars. The scrollbar frame is a control assemblage manager 
        * that relates a control, or control body, to two scrollbars and a corner 
        * window.
        *
        * @return a pointer to the newly created scrollbar frame
        * @remarks
        * @see
        */
        IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL();

        /**
        * Creates a pre-allocated scrollbar frame.
        *
        * @return the pre-allocated scrollbar frame
        * @remarks
        * @see
        */
        inline CEikScrollBarFrame* CreatePreAllocatedScrollBarFrameL();

        /**
        * Gets the scrollbar frame surrounding this Edwin.
        *
        * @return the pointer to this Edwin's scrollbar frame
        * @remarks This is an inline method that returns <code>iSBFrame</code> - the 
        *          pointer to the scrollbar frame. It is <code>NULL</code> 
        *          unless a frame has been created
        * @see
        */
        inline CEikScrollBarFrame* ScrollBarFrame();

        /**
        * Sets word-wrapping on or off in the Edwin control.
        *
        * @param aWrapIsOn <code>ETrue</code> enables word-wrapping; 
        *                  <code>EFalse</code> disables word-wrapping
        * @remarks Call after <code>ConstructL()</code>. Before 
        *          calling <code>SetWordWrapL()</code>, <code>iTextView</code> 
        *          must point to a <code>CTextView</code> object created by 
        *          calling <code>CreateTextViewL()</code>
        * @see
        */
        IMPORT_C void SetWordWrapL(TBool aWrapIsOn);

        /**
        * Gets the width of a line cursor, in pixels.
        *
        * @return the width of the line cursor, in pixels
        * @remarks
        * @see
        */
        IMPORT_C virtual TInt LineCursorWidth() const;

        /**
        * Sets the zoom factor of the Edwin control and reformats its contents 
        * accordingly.
        *
        * @param aZoomFactor The new value for the zoom factor
        * @remarks
        * @see
        */
        IMPORT_C void SetZoomFactorL(TZoomFactor* aZoomFactor);

        /**
        * Sets the Edwin's background color.
        *
        * @param aBackground The new value for the background color
        * @remarks
        * @see
        */
        IMPORT_C void SetBackgroundColorL(TRgb aBackground);

        /**
        * Sets the format mode to WYSIWYG.
        *
        * @param aLayoutWidth The formatting width, in twips
        * @param aDevice The mapping between twips and pixels on the target device
        * @remarks
        * @see TFormatMode
        */
        IMPORT_C void SetWysiwygModeOn(TInt aLayoutWidth,MGraphicsDeviceMap* aDevice);

        /**
        * Switches off the WYSIWYG mode. This method sets the new format mode to 
        * <code>EFScreenMode</code>.
        *
        * @remarks
        * @see TFormatMode
        */
        IMPORT_C void SetWysiwygModeOff();

        /**
        * Updates the text wrap width. This method is for use in WYSIWYG mode only.
        *
        * @param aLayoutWidth The new width to wrap text at, in twips
        * @remarks For use in WYSIWYG mode only
        * @see
        */
        IMPORT_C void UpdateLayoutWidth(TInt aLayoutWidth);

        /**
        * Sends the contents of the Edwin using infrared.
        *
        * @remarks
        * @see
        */
        IMPORT_C void SendDataOverIrL();

        /**
        * Receives the content of an Edwin using infrared.
        *
        * @remarks
        * @see
        */
        IMPORT_C void ReceiveDataOverIrL();

        /**
        * Sets the amount of text in the Edwin to format. This method is called by 
        * <code>NotifyNewDocumentL()</code>, <code>OfferKeyEventL()</code>, and 
        * other methods and sets an appropriate amount of the Edwin's contents 
        * for formatting. At least the portion of text currently displayed is 
        * marked as able to be formatted.
        *
        * @param aIsNewDoc If <code>ETrue</code>, the content is new and full 
        *                  re-formatting should be performed. This is the default 
        *                  argument. If <code>EFalse</code>, the content is not new
        * @remarks
        * @see
        */
        IMPORT_C void SetAmountToFormatL(TBool aIsNewDoc=EFalse);

        /**
        * Sets the <code>EPasteFromIrStore</code> flag.
        *
        * @param aPasteFromIrStore <code>ETrue</code> to set the 
        *        <code>EPasteFromIrStore</code> flag; <code>EFalse</code> to 
        *        remove the <code>EPasteFromIrStore</code> flag
        * @remarks
        * @see
        */
        IMPORT_C void SetPasteFromIrStore(TBool aPasteFromIrStore);

        /**
        * Copies the contents of a stream store to the current cursor position,
        * replacing any selected text.
        *
        * @param aStore The store from which to read
        * @param aDict The stream dictionary
        * @remarks
        * @see
        */
        IMPORT_C void PasteFromStoreL(CStreamStore& aStore, CStreamDictionary& aDict);

        /**
        * Copies the highlighted text into a stream store.
        *
        * @param aStore The store from which to read
        * @param aDict The stream dictionary
        * @remarks
        * @see
        */
        IMPORT_C void CopyToStoreL(CStreamStore& aStore, CStreamDictionary& aDict);

        /**
        * Sets the text view margin values.
        *
        * @param aMargins The new value for the view margins
        * @remarks
        * @see
        */
        IMPORT_C void SetBorderViewMargins(TMargins8 aMargins);

        /**
        * Forces the scrollbars to update immediately. This is a synchronous method.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void ForceScrollBarUpdateL();

        /**
        * Sets whether the Edwin owns a document.
        * An Edwin can be used as a standalone text editor control or as
        * an editor for text owned by another object. The document ownership
        * setting determines whether the Edwin or another object owns the document.
        *
        * @param aOwner An enumeration with the possible items: 
        *               <code>EOwnsText</code> if the Edwin owns the document; 
        *               <code>EDoesNotOwnText</code> otherwise
        * @remarks
        * @see TOwnershipType
        */
        IMPORT_C void SetDocumentOwnership(TOwnershipType aOwner);

        /**
        * Sets the maximum number of characters that can be inserted in the Edwin.
        *
        * @param aLimit The new maximum number of characters 
        * @remarks Attempting to enter more than <code>aLimit</code> results in 
        *          an info message
        * @see
        */
        IMPORT_C void SetTextLimit(TInt aLimit);

        /**
        * Displays the Character Map dialog, which allows the user to select a 
        * character. The selected character is inserted into the Edwin at the 
        * current cursor position.
        *
        * @remarks
        * @see
        */
        IMPORT_C void RunCharMapDialogL();

        /**
        * Gets the text view margins.
        *
        * @return the text view margins
        * @remarks
        * @see
        */
        IMPORT_C TMargins8 Margins() const;

        /**
        * Gets the upper limit for formatting.
        * This returns the value of <code>KFullFormattingUpperThreshold</code>, 
        * which determines the maximum number of characters that can be
        * formatted. If the maximum is exceeded, then only visible text is 
        * formatted. This method is used with <code>KPartialFormattingLowerThreshold</code> 
        * to control the extent of text formatting.
        *
        * @return the value of <code>KFullFormattingUpperThreshold</code>
        * @remarks
        * @see EIKEDWIN.CPP
        */
        IMPORT_C TInt UpperFullFormattingLength() const;

        /**
        * Gets the lower limit for formatting. This method returns the value of
        * <code>KPartialFormattingLowerThreshold</code>, which determines when 
        * a switch is made from just formatting visible text to formatting all
        * text. When the text length exceeds the
        * <code>KFullFormattingUpperThreshold</code> value, only visible text 
        * is formatted. If some characters are deleted so that the text length 
        * is less than <code>KFullFormattingUpperThreshold</code>, the entire 
        * text is not formatted. Instead, reformatting occurs only when the
        * number of characters is less than the value of
        * <code>KPartialFormattingLowerThreshold</code>.
        *
        * @return the value of <code>KPartialFormattingLowerThreshold</code>
        * @remarks
        * @see eikedwin.cpp
        */
        IMPORT_C TInt LowerPartialFormattingLength() const;

        /**
        * Sets the Edwin read-only flag so that text displayed by Edwin
        * cannot be edited by users. It uses the <code>TFlags</code> enumeration 
        * <code>EReadOnly</code>.  
        *
        * @param aReadOnly <code>ETrue</code> to set Edwin to display documents as 
        *                  read-only; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetReadOnly(TBool aReadOnly);

        /**
        * Determines whether the document being edited with Edwin is read-only. It 
        * uses the <code>TFlags</code> enumeration <code>EReadOnly</code>.

        * @return <code>ETrue</code> if the text is read-only; <code>EFalse</code>
        *         otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsReadOnly() const;

        /**
        * Determines whether the document being edited is read-only. It displays a 
        * message with <code>CEikonEnv::InfoMsg()</code> if the document is set as 
        * read-only. It uses the <code>TFlags</code> enumeration 
        * <code>EReadOnly</code>.
        *
        * @remarks
        * @see
        */
        IMPORT_C void CheckNotReadOnlyL();

        /**
        * Sets whether the Edwin accepts the insertion of images into rich text 
        * Edwin controls, by setting the <code>TFlags</code> enumeration 
        * <code>EAllowPictures</code> of rich text Edwin controls.  
        *
        * @param aAllow <code>ETrue</code> sets the document to accept pictures;
        *               <code>EFalse</code> sets the document to not accept 
        *               pictures
        * @remarks
        * @see
        */
        IMPORT_C void SetAllowPictures(TBool aAllow);

        /**
        * Removes unwanted pictures from a rich text Edwin. This method returns
        * immediately if the Edwin's <code>TFlags</code> enumeration 
        * <code>EAllowPictures</code> has been set. Otherwise, this method checks 
        * the Edwin's text between two bounds and removes pictures in that range.
        *
        * @param aStartPos Text position from which to start searching for 
        *                  unwanted pictures
        * @param aLength The length of text to search from <code>aStartPos</code> 
        * @remarks
        * @see
        */
        IMPORT_C void CheckRemovePictures(TInt aStartPos,TInt aLength);

        /**
        * Sets the minimum gap between text and the right-hand edge of
        * the Edwin when text is wrapped.
        * This value is used to calculate the layout area for text.
        *
        * @param aGap The size of the gutter, in pixels
        * @remarks
        * @see
        */
        IMPORT_C void SetRightWrapGutter(TInt aGap);

        /**
        * Undoes the most recent text operation if the Edwin's <code>TFlags</code> 
        * enumeration <code>EAllowUndo</code> is set to <code>ETrue</code> and 
        * when the undo store is not empty.
        *
        * @remarks
        * @see
        */
        IMPORT_C void UndoL();

        /**
        * Deletes the undo store.
        *
        * @remarks
        * @see
        */
        IMPORT_C void ClearUndo();

        /**
        * Sets whether the undo operation is permitted.
        *
        * @param aAllow <code>ETrue</code> to permit undo operations; 
        *               <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetAllowUndo(TBool aAllow);

        /**
        * Gets whether Edwin is set to support the undo command, that is, 
        * whether the value of the Edwin's <code>TFlags</code> enumeration 
        * <code>EAllowUndo</code> is <code>ETrue</code>.
        *
        * @return <code>ETrue</code> if edits can be undone; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see TFlags
        */
        IMPORT_C TBool SupportsUndo() const;

        /**
        * Determines whether an undo is possible. 
        * 
        * @return <code>ETrue</code> if the undo store is available; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see TFlags 
        */
        IMPORT_C TBool CanUndo() const;

        /**
        * Determines whether an operation that cannot be undone has ever been 
        * performed.
        * 
        * @return <code>ETrue</code> if the undo store has ever been created;
        *         <code>EFalse</code> otherwise
        * @remarks
        */
        IMPORT_C TBool NothingToUndoL();

        /**
        * Prevents any action carried out on the selected text from being undone.
        *
        * @param aCursorPos The current position of the cursor relative to the text
        * @remarks 
        * @see
        */
        IMPORT_C void SetNoUndoSelection(TInt aCursorPos);

        /**
        * Sets whether picture characters and/or punctuation should be treated
        * as word delimiters in addition to white space.
        *
        * @param aPicture <code>ETrue</code> if picture characters should be 
        *                 treated as delimiters for words; 
        *                 <code>EFalse</code> otherwise
        * @param aPunctuation <code>ETrue</code> if punctuation should be 
        *                 treated as delimiters for words;
        *                 <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetWordDelimiters(TBool aPicture,TBool aPunctuation);

        /**
        * Gets the start position and length of the word in which the
        * specified document position is located.
        *
        * @param aCurrentPos The cursor position within a word in the text
        * @param aStartPos The start position of the word
        * @param aLength The length of the word
        * @remarks
        * @see
        */
        IMPORT_C void GetWordInfo(TInt aCurrentPos,TInt& aStartPos,TInt& aLength) const;

        /**
        * Sets the new cursor position.
        * If the cursor is no longer visible, the document is scrolled to display
        * the line containing the new cursor position. Any scrollbars present are
        * updated as necessary.
        *
        * @param aMovement The type of cursor movement
        * @param aSelect If <code>ETrue</code>, the selection is extended. This 
        *                is like holding down the Shift key on a physical keyboard
        * @remarks <code>iTextView</code> must point to a 
        *          <code>CTextView</code>. The Edwin's associated text view is
        *          created by calling <code>CreateTextViewL()</code>
        * @see TMovementType
        */
        IMPORT_C void MoveCursorL(TCursorPosition::TMovementType aMovement,TBool aSelect);

        /**
        * Scrolls the content in the Edwin either horizontally or vertically 
        * without affecting the position of the cursor.
        *
        * @param aMovement The type of cursor movement
        * @remarks
        * @see
        */
        IMPORT_C void MoveDisplayL(TCursorPosition::TMovementType aMovement);

        /**
        * Removes all non-ASCII characters from the specified text.
        * This can be used, for example, to remove Unicode characters where they 
        * are not valid characters.
        *
        * @param aStartPos The start position in the text
        * @param aLength The number of characters, beginning with 
        *                <code>aStartPos</code> to check
        * @remarks
        * @see
        */
        IMPORT_C void CheckValidityOfChars(TInt aStartPos,TInt aLength);

        /**
        * Sets the <code>EOnlyASCIIChars</code> flag in the enumeration 
        * <code>TFlags</code> so that the Edwin can only contain ASCII characters. 
        *
        * @param aASCIIOnly If <code>ETrue</code>, the flag is set and the Edwin 
        *                   can only contain ASCII characters; 
        *                   if <code>EFalse</code>, the 
        *                   <code>EOnlyASCIIChars</code> flag is removed and 
        *                   the Edwin can also contain Unicode characters
        * @remarks
        * @see
        */
        IMPORT_C void SetOnlyASCIIChars(TBool aASCIIOnly);

        /**
        * Determines whether the <code>EOnlyASCIIChars</code> flag in the 
        * enumeration <code>TFlags</code> is set. If so, the Edwin can only 
        * contain ASCII characters.
        *
        * @return if <code>ETrue</code>, the flag is set and the Edwin can
        *         contain only ASCII character; if <code>EFalse</code>, the 
        *         <code>EOnlyASCIIChars</code> flag is removed and the Edwin 
        *         can also contain Unicode characters
        * @remarks
        * @see
        */
        IMPORT_C TBool OnlyASCIIChars() const;

        /**
        * Gets the average number of lines shown in the Edwin's view.
        *
        * @return the average number of lines
        * @remarks
        * @see
        */
        inline TInt AvgLinesInViewRect() const;

        /**
        * Gets the average number of characters on a line.
        *
        * @return the average number of characters on a line
        * @remarks
        * @see
        */
        inline TInt AvgCharsPerLine() const;

        /**
        * Sets the average number of lines displayed in an Edwin's view.
        *
        * @param aAvgLines The average number of lines to display
        * @remarks
        * @see
        */
        inline void SetAvgLinesInViewRect(TInt aAvgLines);

        /**
        * Sets the average number of characters per line.
        *
        * @param aAvgChars The average number of characters per line
        * @remarks
        * @see
        */
        inline void SetAvgCharsPerLine(TInt aAvgChars);

        /**
        * Sets the Edwin size observer.
        *
        * @param aEdwinSizeObserver The Edwin size observer. Does not imply 
        *                           transfer of ownership
        * @remarks
        * @see
        */
        IMPORT_C void SetEdwinSizeObserver(MEikEdwinSizeObserver* aEdwinSizeObserver);

        /**
        * Sets the observer to be used for clipboard feedback functions. 
        * Sets <code>aEdwinClipboardObserver</code> into <code>iEdwinExtra</code>. 
        * <code>aOwnedExternally</code> specifies whether
        * <code>aEdwinClipboardObserver</code> is owned internally by 
        * <code>CEikEdwinExtra</code> or by an external client.
        * This method leaves only when <code>iEdwinExtra</code> is <code>NULL</code>, 
        * in which case <code>aEdwinClipboardObserver</code> does not get
        * set into <code>iEdwinExtra</code>.
        *
        * @param aEdwinClipboardObserver The clipboard observer
        * @param aOwnedExternally <code>ETrue</code> if the clipboard observer is 
        *                         owned externally; <code>EFalse</code> if it is 
        *                         part of the <code>CEikEdwin</code>
        */
        IMPORT_C void SetEdwinClipboardObserverL(MEikEdwinClipboardObserver* aEdwinClipboardObserver, TBool aOwnedExternally);

        /**
        * Gets the minimum height of the Edwin.
        *
        * @return the minimum height of the Edwin control
        * @remarks
        * @see
        */
        IMPORT_C TInt MinimumHeight() const;

        /**
        * Gets the maximum height of the Edwin control.
        *
        * @return the maximum height of the Edwin
        * @remarks
        * @see
        */
        IMPORT_C TInt MaximumHeight() const;

        /**
        * Sets the minimum height of the Edwin control. This method also increases 
        * the maximum height of the Edwin if its value is less than 
        * <code>aHeight</code>.
        *
        * @param aHeight The minimum height of the Edwin
        * @remarks
        * @see
        */
        IMPORT_C void SetMinimumHeight(TInt aHeight);

        /**
        * Sets the maximum height of the Edwin control. This method also decreases
        * the minimum height of the Edwin if its value is greater than 
        * <code>aHeight</code>.
        *
        * @param aHeight The maximum height of the Edwin
        * @remarks
        * @see
        */
        IMPORT_C void SetMaximumHeight(TInt aHeight);

        /**
        * Calculates the height of the Edwin control. If <code>iNumberOfLines=0</code>,
        * this method returns the border height.
        *
        * @return the height of the Edwin
        * @remarks
        * @see
        */
        IMPORT_C TInt CalculateHeight();

        /**
        * @internal
        * @deprecated
        */
        IMPORT_C void SetDontConsumeTab(TBool aDontConsumeTab);

        /**
        * @internal
        * @deprecated
        */
        IMPORT_C TBool DontConsumeTab() const;

        /**
        * Sets the <code>EAutoScrollOnFocusChange</code> flag.
        *
        * @param aAutoScrollOnFocusChange If <code>ETrue</code>, the 
        *                                 <code>EAutoScrollOnFocusChange</code> 
        *                                 flag is set; if <code>EFalse</code> the 
        *                                 <code>EAutoScrollOnFocusChange</code> flag 
        *                                 is removed
        * @remarks
        * @see TFlags
        */
        IMPORT_C void SetAutoScrollOnFocusChange(TBool aAutoScrollOnFocusChange);

        /**
        * Determines whether the <code>EAutoScrollOnFocusChange</code> flag is set.
        *
        * @return <code>ETrue</code> if the <code>EAutoScrollOnFocusChange</code> 
        *         flag is set; <code>EFalse</code> otherwise
        * @remarks
        * @see TFlags
        */
        IMPORT_C TBool AutoScrollOnFocusChange() const;

        /**
        * Sets the <code>EAllowBorders</code> flag, which allows borders.
        *
        * @param aAllowBorders If <code>ETrue</code>, the <code>EAllowBorders</code>
        *                      flag is set; if <code>EFalse</code>, the 
        *                      flag is removed
        * @remarks 
        * @see TFlags
        */
        IMPORT_C void SetAllowBorders(TBool aAllowBorders);

        /**
        * Determines whether the <code>EAllowBorders</code> flag, which allows borders,
        * is set.
        *
        * @return <code>ETrue</code> if the <code>EAllowBorders</code> flag is 
        *         set; <code>EFalse</code> otherwise
        * @remarks
        * @see TFlags
        */
        IMPORT_C TBool AllowBorders() const;

        /**
        * Search operations can wrap over a document. This method resets the 
        * points in the document at which a search operation begins and ends
        * its search.
        *
        * @param aStartPos The position where a search begins
        * @param aRestart If <code>ETrue</code>, the next 'Find/Find next' 
        *                 operation begins a fresh search at <code>aStartPos</code>.
        *                 If <code>EFalse</code>, the next 'Find next' operation 
        *                 ends its search at <code>aStartPos</code>
        * @remarks 
        * @see
        */
        IMPORT_C void SetFindStartPos(TInt aStartPos, TBool aRestart=ETrue);

        /**
        * Find operations can wrap over a document. This method returns the point 
        * in the document at which a search operation will begin and end.
        *
        * @return the position in the document where a search operation begins
        *         or ends 
        * @remarks Due to the wrapping nature of the search functionality, the 
        *          search and end position are the same
        * @see
        */
        IMPORT_C TInt FindStartPos();

        /**
        * Inserts and deletes text. <code>aText</code> is inserted at 
        * position <code>aInsertPos</code>. The selection defined by
        * <code>aDelete</code> is deleted.
        *
        * @param aInsertPos The position at which text is inserted
        * @param aText The text to insert
        * @param aDelete The selected text to be replaced by <code>aText</code>
        * @remarks If no selection is defined, no text is deleted
        * @see
        */
        IMPORT_C void InsertDeleteCharsL(TInt aInsertPos,const TDesC& aText,const TCursorSelection& aDelete);

        /**
        * Sets the visibility of non-printing characters.
        *
        * @param aVisibility A <code>TNonPrintingCharVisibility</code> object
        * @remarks
        * @see
        */
        IMPORT_C void SetNonPrintingCharsVisibility(TNonPrintingCharVisibility aVisibility);

        /**
        * Gets the visibility of non-printing characters.
        *
        * @return the visibility of the non-printing characters
        * @remarks
        * @see
        */
        IMPORT_C TNonPrintingCharVisibility NonPrintingCharsVisibility() const;

        /**
        * Allocates memory for the Edwin text <code>CTextView</code>.
        * 
        * @remarks <code>iLayout</code> must point to a valid <code>CTextLayout</code>
        *          object constructed by <code>ConstructL()</code>
        * @see
        */
        IMPORT_C void CreateTextViewL();

        /**
        * @internal
        * @deprecated
        */
        IMPORT_C CTextView* TextView() const;

        /**
        * @internal
        * @deprecated
        */
        IMPORT_C CTextLayout* TextLayout() const;

        /**
        * @internal
        */
        IMPORT_C TBool SetUndoBufferL(const TCursorSelection& aSelection);

        /**
        * @internal
        */
        IMPORT_C void SetUndoableText(const TCursorSelection& aSelection);
    
    protected:  // Declarations
    /**
     * Specifies the end points of the editable area.
     */
    enum TEnd
        {
        EStart,         /** The start of the editable area. */
        EEnd            /** The end of the editable area. */
        };
    /**
     * Specifies the chunk size as either a word, or a paragraph.
     */
    enum TChunkSize
        {
        /** a word */
        EChunkWord,    
        /** a paragraph */
        EChunkPara      
        };
    enum TEikEdwinFlags
        { 
        // internal flags
		// NOTE: These bitfield values are shared with the flags in the private area below in iEdwinInternalFlags
        /** @internal */
        ERichText					=0x00000001,
        EDragDouble					=0x00000002,
        ELeftDownInViewRect			=0x00000004,
        ENumericCharacters			=0x00000008, // only used to calculate initial width
		EPasteOnlyNumericCharacters	=0x00001000
        };

    protected:  // Methods
        IMPORT_C void EditObserver(TInt aStartEdit,TInt aEditLength);

        /**
        * This will update the position of the view rect of iTextView
        */
        IMPORT_C void PositionChanged();

        /**
        * Draws the visible text and the cursor for DrawL, but 
        * does not draw the border.
        * The DrawL function is trapped to handle problems due to 
        * insufficient resources being available.
        * @param aRect Rectangle in which to draw.
        */
        IMPORT_C void TrappedDraw(const TRect& aRect) const;

        /**
        * Draws the visible text and the cursor.
        */
        IMPORT_C void DrawContents();

        /**
        * Completes the second-phase construction of a CEikEdwin object.
        * 
        * This protected function is called by ConstructL and 
        * ConstructFromResourceL after the Edwin size, flags and text limit
        * have been set. Derived classes should call either this function
        * or CEikEdwin's  ConstructL or construction before initializing their
        * own members.
        */
        IMPORT_C void BaseConstructL();

        /**
        * Formats all the text in the text view.
        * Called by several functions, such as <code>CEikEdwin::HandleTextChangedL</code>
        * and <code>CEikEdwin::SetTextL</code>.
        */
        IMPORT_C void FormatTextL();

        /**
        * This function asks the user to confirm this action if 
        * <code>aPromptConfirmation</code> is <code>ETrue</code>.
        * @param aChanged On return, ETrue if the text was changed.
        * @param aIsBackSpace ETrue if this is in response to backspace
        * being pressed. Determines whether character formatting is preserved or not.
        * @param aPromptConfirmation Optional. ETrue to ask the user to confirm this action.
        * @return The cursor position in the text after deletion.
        */
        IMPORT_C TInt DeleteHighlightL(TBool& aChanged,TBool aIsBackSpace=EFalse,TBool aPromptConfirmation=ETrue);

        /**
        * Confirms whether deletion of the user selection is required.
        * If the user selection is less than KBlockDeleteWarninSize and does not
        * contain a picture, this function returns ETrue. If the users selection is
        * greater than KBlockDeleteWarningSize or contains a picture, this function
        * asks the user to confirm deletion of their
        * selection and then returns the users response.
        * @return ETrue if deletion is required. EFalse if deletion is not required.
        */
        IMPORT_C TBool OkToDeleteSelectionL();

        /**
        * Deletes the cursors selection.
        * If no selection is made, this function deletes only one character. The
        * argument aIsBackSpace determines whether to preserve the character formatting or not.
        * @param aChanged On return, whether the text was changed.
        * @param aSelection The cursor selection describing the position to be delted.
        * @param aIsBackSpace ETrue if this in response to backspace being
        * pressed. Determines whether character formatting is preserved or not.
        * @param aAllowUndo ETrue if the user is permitted to undo this change.
        */
        IMPORT_C void DeleteL(TBool& aChanged,const TCursorSelection& aSelection,TBool aIsBackSpace=EFalse,TBool aAllowUndo=ETrue);

        /**
        * Handles errors that occur when handling a change in Edwin size.
        * Calls CEikonEnv::NotifyIdleErrorWhileRedrawing().
        */
        IMPORT_C void TrappedSizeChanged();

        /**
        * Handles a change in Edwins size.
        * This function accounts for text wrap settings and whether the Edwin is
        * ready to be redrawn and also calls functions to reformat text and to 
        * update the Edwins scrollbars.
        */
        IMPORT_C void HandleSizeChangedL();

        /**
        * Cancels the selection and any FEP composition text.
        * This function then repostions the cursor at the specified end of 
        * the currently selected text.
        * @param aEndOfSelectionToLeaveCursor The end of the current selection at which the
        * cursor is repositioned.
        */
        IMPORT_C void CancelSelectionL(TEnd aEndOfSelectionToLeaveCursor);

        /**
        * Moves the cursor to the beginning of the next word or paragraph
        * This function cancels any from end processing transaction currently 
        * in progress for Edwin.
        * @param aSelect If ETrue the chunk is selected, otherwise EFalse.
        * @param aChunkSize The chunk size, this can be either a word or a 
        * paragraph. See TChunkSize enum.
        * @param aEndScanningTowards Which direction to scan towards, the start 
        * or the end of the document.
        */
        IMPORT_C void MoveCursorToChunkStartL(TBool aSelect,TChunkSize aChunkSize,TEnd aEndScanningTowards);

        /**
        * Cancels the insertion of a character format.
        */
        IMPORT_C void CancelInsertCharFormat();

        /**
        * Copies the contents of the cursor selection onto the clipboard.
        */
        IMPORT_C void PlaceDataOnClipboardL();

        /**
        * Reports an Edwin event of the specified type.
        * The Edwin event is passed first to the Edwin observer and then
        * to the list of observers, even if the first Edwin observer is not set.
        * If the Edwin has a custom drawer, and the event is of type EEventFormatChanged,
        * the event is passed to the custom drawer. If the Edwin has an observer the 
        * event is passed to that observer. If no observer is set for the Edwin, this 
        * function passes the event to each observer in the observer list.
        * @param aEventType The type of event to report.
        */
        IMPORT_C void ReportEdwinEventL(MEikEdwinObserver::TEdwinEvent aEventType);

        /**
        * Sets margin widths and line cursor width.
        */
        IMPORT_C void SetLineCursorDetailsL();

        /**
        * Replaces the current Edwin text.
        * @param aInText Text with which the current text is replaced.
        * @param aOutText On return, the replaced text.
        */
        IMPORT_C virtual void CopyDocumentContentL(CGlobalText& aInText,CGlobalText& aOutText);

        /**
        * Displays an information message to indicate that the specified text
        * could not be found.
        * @param aFindText The text that could not be found.
        */
        IMPORT_C void DisplayFindTextNotFound(TDes& aFindText);

        /**
        * Displays an information message to indicate that the current find
        * or replace operation has completed a loop through the document.
        */
        IMPORT_C void DisplaySearchComplete();

        /**
        * Handles pasting of text.
        * @param aStartPos The start position of the pasted text.
        * @param aLength The length of the pasted text.
        */
        IMPORT_C virtual void HandleTextPastedL(TInt aStartPos,TInt& aLength);

        /**
        * Creates the Edwin custom draw.
        */
        IMPORT_C virtual CLafEdwinCustomDrawBase* CreateCustomDrawL();

        /**
        * @internal
        */
        IMPORT_C void CreateLayoutL(MLayDoc* aLayDoc);

        /**
        * @internal
        */
        IMPORT_C void CreateTextAndLayoutL(CParaFormatLayer* aParaFormatLayer,CCharFormatLayer* aCharFormatLayer);

		/**
		* Determines if a charcter is valid for a numerical editor
		* @param aCharacter The character to determine validity
		*/
		IMPORT_C static TBool IsValidNumericCharacter(TChar aCharacter);

        void CheckCreateExtensionL();
    private:  // Declarations
		// NOTE: These bitfield values are shared with the flags in the protected area above in iEdwinInternalFlags
       enum
            { // internal flags
            EWysiwygOn                      =0x00000010,
            EUnderOneScreenFormattedText    =0x00000020,
            EPictureDelimits                =0x00000040,
            EPunctuationDelimits            =0x00000080,
            EPasteFromIrStore               =0x00000100,
            ELockScrollBarState             =0x00000200,
            EOnReformatting                 =0x00000400,
            EFindSearchHasWrapped           =0x00000800
            };

    private: //Methods
        IMPORT_C void SizeChanged();
        IMPORT_C TInt CountComponentControls() const;
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
        IMPORT_C void Reserved_2();
        IMPORT_C virtual void Reserved_3();
        IMPORT_C virtual void NotifyInvalidOperationOnReadOnlyL();
        IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL(TBool aPreAlloc);
        void SetVirtualCursorStateL(TBool aIsFocused) const;
        void SetHeightForNumOfLinesL();
        void ApplyAutoSelectionL();
        void SetScrollBarsL();
        void SetVertScrollBarModelByCharactersL(TEikScrollBarModel& aVertModel) const;
        void RetrieveDataFromClipboardL();
		void CheckClipboardDataValidForPasteL();
		static TBool IsValidNumericText(CPlainText& aText);
		void SetCursorVisibilityL(TBool aEmphasis);
        TBool OwnsScrollBars() const;
        void CreateScrollBarFrameLayout(TEikScrollBarFrameLayout& aLayout) const;
        void UpdateHorizScrollBarThumb();
        void UpdateVertScrollBarThumbL();
        void DoSetUndoBufferL(const TCursorSelection& aSelection);
        void DoPasteFromStoreL(const CStreamStore& aStore,const CStreamDictionary& aDict);
        void DoReplaceAllL(SEdwinFindModel* aModel,TBool& aTextFound,TBool& aReplaced);
        void DeleteExtraParasL(TInt aStartPos,TInt aLength);
        TInt LocateChar(TChar aChar,TInt aStartPos,TInt aLength);
        TBool IsValidChar(TInt aChar) const;
        TInt CalcMinimumHeightFromNumOfLinesL() const;
        void CheckEdwinHeight(TInt& aHeight);
    TBool IsNewHeightWithinMinimumAndMaximum(TInt aNewHeight) const;
        void SetEdwinHeight(TInt aHeight);
        void DoCreateCustomDrawL();
        void DoCreateCustomWrapL();
        void HandleCapsLockMessage();
        TKeyResponse DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        TInt HeightForNumOfLinesL();
        void SetLayoutFormat(TBool aIsUpperThresholdFull=EFalse);
        void UpdateAvgCharsPerLine();
        void TrappedPositionChanged();
        void HandlePositionChangedL();
        void FocusChangedL(TDrawNow aDrawNow);
        void SetCursorPosL(TInt aDocPos, TBool aSelect, TBool aCancelFormat);
        void DoParseL();	//Only used in Series 80.

    protected:     // Data
        /** Flags for the CEikEdwin. See CEikEdwin::TFlags. */
        TUint32 iEdwinUserFlags;
        /** Flags used internally in CEikEdwin. */
        TUint32 iEdwinInternalFlags;
        /** Pointer to the editor's text. */
        CPlainText* iText;
        /** Pointer to the editor's text view. */
        CTextView* iTextView;
        /** Pointer to the editor's text layout. */
        CTextLayout* iLayout;
        /** The maximum number of characters that can be displayed. */
        TInt iTextLimit;
        /** The number of lines of the editor. */
        TInt iNumberOfLines;
        /** The current zoom level of the editor. */
        MGraphicsDeviceMap* iZoomFactor;
        /** The last position of the cursor. */
        TInt iLastPointerDocPos;
        /** The margins for the editor. */
        TMargins8 iMargins;

    private:
        class CUndoBuffer : public CBase
            {
        public:
            static CUndoBuffer* NewL();
            ~CUndoBuffer();
            CBufStore& Store() const;
            CStreamDictionary& Dictionary() const;
            TCursorSelection NewText() const;
            void SetNewText(const TCursorSelection& aSelection);
            TInt OldCursorPos() const;
            void SetOldCursorPos(TInt aPos);
            void SetNoSelection(TInt aCursorPos);
            TBool NoSelection() const;
            TInt NoSelectionCursorPos() const;
        private:
            void ConstructL();
        private:
            CBufStore* iStore;
            CStreamDictionary* iDictionary;
            TCursorSelection iNewText;
            TInt iOldCursorPos;
            TInt iNoSelectionCursorPos;
            };

    private:     // Data
        friend class CEikEdwinFepSupport; 
        CIdle* iSetScrollBar;
        CEikScrollBarFrame* iSBFrame;
        MEikEdwinObserver* iEdwinObserver;
        CArrayPtr<MEikEdwinObserver>* iObserverArray;
        CEikEdwinExtra* iEdwinExtra; // replaces CEikEdwinFepSupport* iEdwinFepSupport
        CUndoBuffer* iUndoStore;
        TInt iAvgLinesInViewRect;
        TInt iAvgCharsPerLine;
        TInt iRightWrapGutter;
        TInt iLayoutWidth;
        MEikEdwinSizeObserver* iEdwinSizeObserver;
        TInt iMinimumHeight;
        TInt iMaximumHeight;
        CLafEdwinCustomDrawBase* iCustomDrawer;
        TInt iLastPointerAnchorPos;
    };

inline CEikScrollBarFrame* CEikEdwin::CreatePreAllocatedScrollBarFrameL()
    { return CreateScrollBarFrameL(ETrue);}

inline CEikScrollBarFrame* CEikEdwin::ScrollBarFrame()
    { return ((CEikScrollBarFrame* const)iSBFrame); }

inline TInt CEikEdwin::AvgLinesInViewRect() const
    { return iAvgLinesInViewRect; }

inline TInt CEikEdwin::AvgCharsPerLine() const
    { return iAvgCharsPerLine;}

inline void CEikEdwin::SetAvgLinesInViewRect(TInt aAvgLines)
    { iAvgLinesInViewRect=aAvgLines; }

inline void CEikEdwin::SetAvgCharsPerLine(TInt aAvgChars)
    { iAvgCharsPerLine=aAvgChars; }


#endif      // EIKEDWIN_H   
            
// End of File