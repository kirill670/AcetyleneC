/*
* ==============================================================================
*  Name        : ckncancl.h
*  Part of     : CKON
*  Interface   : Misc Dialog API
*  Description : CCknCancelDialog class implements the Cancel Note dialog.
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


#ifndef CKNCANCL_H
#define CKNCANCL_H

// INCLUDES
#include <eikdialg.h>
#include <cknmcanc.h>

// FORWARD DECLARATIONS
class TResourceReader;
class CGulIcon;
class CEikProgressInfo;
class CCknAnimationControl;

// CONSTANTS
/** animation ID (indicates default animation) */
const TInt KUseDefaultAnimation = 0;

/**
 * The <code>CCknCancelDialog</code> class implements the Cancel Note.
 * The Cancel Note has two constructors; one with an animation and one with a 
 * progress bar. Each has a title and a text message.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknCancelDialog : public CEikDialog, public MCknCancelDialog
    {
    public:
        /**
        * Constructs a Cancel Note.
        *
        * @param aSelfPtr A pointer to a pointer that allows the Cancel Note 
        *                 to be launched and deleted
        * @param aMsgRid The message resource ID
        * @param aButtonTextRid The button text resource ID
        * @param aCancellableOperation An object which implements <code>CancelOperation()</code>
        * @param aAnimationId The resource ID of an animation. If no ID is given, 
        *                     a default animation is constructed. The animation 
        *                     IDs are defined in skin.rsg
        * @return The newly created Cancel Note
        * @remarks 
        * @see 
        */
        IMPORT_C static CCknCancelDialog* NewL(CCknCancelDialog** aSelfPtr,
                                           TInt aMsgRid,
                                           TInt aButtonTextRid,
                                           MCknCancellableOperation* aCancellableOperation,
                                           TInt aAnimationId=KUseDefaultAnimation);

        /**
        * Constructs a Cancel Note.
        *
        * @param aSelfPtr A pointer to a pointer that allows the Cancel Note 
        *                 to be launched and deleted
        * @param aMsg The message text
        * @param aButtonText The button text
        * @param aCancellableOperation An object that implements <code>CancelOperation()</code>
        * @param aAnimationId The resource ID of an animation. If no ID is given,
        *                     a default animation is constructed. The animation 
        *                     IDs are defined in skin.rsg 
        * @return The newly created Cancel Note 
        * @remarks
        * @see
        */
        IMPORT_C static CCknCancelDialog* NewL(CCknCancelDialog** aSelfPtr,
                                           const TDesC& aMsg,
                                           const TDesC& aButtonText,
                                           MCknCancellableOperation* aCancellableOperation,
                                           TInt aAnimationId=KUseDefaultAnimation);

        /**
        * Constructs a Cancel Note.
        *
        * @param aSelfPtr A pointer to a pointer that allows the Cancel Note 
        *                 to be launched
        * @param aMsgRid The message resource ID
        * @param aButtonTextRid The button text resource ID
        * @param aCancellableOperation An object that implements <code>CancelOperation()</code>
        * @param aProgressBar A progress bar
        * @return The newly created Cancel Note
        * @remarks
        * @see <code>CEikProgressInfo</code> in eikprogi.h
        */
        IMPORT_C static CCknCancelDialog* NewL(CCknCancelDialog** aSelfPtr,
                                           TInt aMsgRid,
                                           TInt aButtonTextRid,
                                           MCknCancellableOperation* aCancellableOperation,
                                           CEikProgressInfo& aProgressBar);


        /**
        * Constructs a Cancel Note.
        *
        * @param aSelfPtr A pointer to a pointer that allows the Cancel Note 
        *                 to be deleted
        * @param aMsg The message text
        * @param aButtonText The button text
        * @param aCancellableOperation An object that implements <code>CancelOperation()</code>
        * @param aProgressBar A progress bar
        * @return The newly created Cancel Note
        * @remarks
        * @see <code>CEikProgressInfo</code> in eikprogi.h
        */
        IMPORT_C static CCknCancelDialog* NewL(CCknCancelDialog** aSelfPtr,
                                           const TDesC& aMsg,
                                           const TDesC& aButtonText,
                                           MCknCancellableOperation* aCancellableOperation,
                                           CEikProgressInfo& aProgressBar);

        /**
        * Launches a Cancel Note after it is constructed. This method runs the 
        * dialog in <code>UpdatingMessage</code> mode, which allows the 
        * message text to be updated while the Cancel Note is open. It sets 
        * the number of lines available for a message and the width of the 
        * message in pixels.
        *
        * @param aMessageHeightInLines The number of lines that any 
        *                              message passed to the Cancel Note can 
        *                              have. The maximum number of lines is 
        *                              truncated to five
        * @param aMessageWidthInPixels The maximum width of any single line 
        *                              of text in the message, in pixels 
        * @return <code>EFalse</code>
        * @remarks Always returns <code>EFalse</code>
        * @see
        */
        IMPORT_C TBool RunDlgLD(TInt aMessageHeightInLines, TInt aMessageWidthInPixels);

        /**
        * Allows the application to change the message text while the dialog  
        * is open. It only updates the text if the dialog is run in
        * <code>UpdatingMessage</code> mode. The number of lines in the 
        * message should not be greater than the argument 
        * <code>aMessageHeightInLines</code> passed when the dialog is run. 
        * Text is only displayed to the width passed as 
        * <code>aMessageWidthInPixels</code> when the dialog is run.
        *
        * @param aMsg The new message text
        * @remarks <code>RunDlgLD(iMessageHeight,iMessageWidth)</code> should 
        *          be called before using this
        * @see
        */
        IMPORT_C void UpdateMessageTextL(const TDesC& aMsg);


        /**
        * Launches a Cancel Note after it is constructed. This method does 
        * not run in <code>UpdatingMessage</code> mode.
        *
        * @return <code>EFalse</code>
        * @remarks Always returns <code>EFalse</code>
        * @see
        */
        IMPORT_C TBool RunDlgLD();

        /**
        * The object destructor.
        */
        IMPORT_C ~CCknCancelDialog();

        /**
        * The destructor for class <code>CCknCancelDialog</code>.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void Release();

        /**
        * Returns a Cancel Note object as <code>CCoeControl</code>.
        *
        * @return the Cancel Note object
        * @remarks
        * @see <code>CCoeControl</code> in coecntrl.h
        */
        IMPORT_C CCoeControl* AsControl();
    protected:
        /**
        * C++ constructor.
        * @param aSelfPtr Pointer to a pointer that allows the note to be deleted.
        * @param aCancellableOperation Pointer to an operation that can be cancelled.
        * @param aTitle Reference to a descriptor to be used as title text in the note.
        * @param aMsg Reference to a descriptor to be used as message text in the note.
        *    This text string should never be of zero length.
        * @param aButtonText Reference to the descriptor to be used as button text.
        * @param aAnimationId Resource id of an animation. The note will internally construct
        * an animation by the id and set it to itself. If no id will be given a default animation
        * will be constructed.
        */
    CCknCancelDialog(CCknCancelDialog** aSelfPtr,
                     MCknCancellableOperation* aCancellableOperation,
                     const TDesC& aTitle,
                     const TDesC& aMsg,
                     const TDesC& aButtonText,
                     TInt aAnimationId);

        /**
        * C++ constructor.
        * @param aSelfPtr Pointer to a pointer that allows the note to be deleted.
        * @param aCancellableOperation Pointer to an operation that can be cancelled.
        * @param aTitle Reference to a descriptor to be used as title text in the note.
        * @param aMsg Reference to a descriptor to be used as message text in the note.
        *    This text string should never be of zero length.
        * @param aButtonText Reference to the descriptor to be used as button text.
        * @param aProgressBar Reference to a progress bar.
        */
    CCknCancelDialog(CCknCancelDialog** aSelfPtr,
                     MCknCancellableOperation* aCancellableOperation,
                     const TDesC& aTitle,
                     const TDesC& aMsg,
                     const TDesC& aButtonText,
                     CEikProgressInfo& aProgressBar);
    private:
    CCknAnimationControl* CreateAnimationFromResourceAndStartL(TInt aResourceId,
                                                               CCoeControl& aContainer);
    protected:
        void AllocResourcesL(TInt aMsgRid, TInt aButtonTextRid);
        TInt DialogResourceId() const;
    private:
        void PreLayoutDynInitL();
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        TBool OkToExitL(TInt aButtonId);
    private:
    enum TGraphicsControlOwnership
        {
        EControlOwnershipExternal=0x01
        };
    private:
        CCknCancelDialog** iSelfPtr; // Allows dialog to be destroyed by user
        MCknCancellableOperation* iCancellableOperation;
        CCoeControl* iGraphicsControl;
        TInt iAnimationId;
        TInt iDialogResource;
        TUint32 iFlags;
        TBool iUpdatingMessageMode;
        TInt iNumberOfLinesInMessage;
        TInt iMessageWidthInPixels;
    protected:
        const TDesC* iTitle;
        const TDesC* iMessage;
        const TDesC* iButtonText;
        HBufC* iButtonTextBuf;
        HBufC* iMessageBuf;
    public:
    // deprecated - kept for BC
    /** @deprecated */
    IMPORT_C static CCknCancelDialog* NewL(CCknCancelDialog** aSelfPtr,
                                           MCknCancellableOperation* aCancellableOperation,
                                           const TDesC& aTitle,
                                           const TDesC& aMsg,
                                           TInt aAnimationId=KUseDefaultAnimation);

    // deprecated - kept for BC
    /** @deprecated */
    IMPORT_C static CCknCancelDialog* NewL(CCknCancelDialog** aSelfPtr,
                                           MCknCancellableOperation* aCancellableOperation,
                                           const TDesC& aTitle,
                                           const TDesC& aMsg,
                                           CEikProgressInfo& aProgressBar);
    };


#endif  // CKNCANCL_H

// End of File
