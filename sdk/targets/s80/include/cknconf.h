/*
* ==============================================================================
*  Name        : cknconf.h
*  Part of     : CKON
*  Interface   : Confirmation Note API
*  Description : Confirmation Note
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

#ifndef CKNCONF_H
#define CKNCONF_H

//** INCLUDES */
#include <eikenv.h>
#include <eikdialg.h>
#include <gulicon.h>

//**  CLASS DECLARATIONS */

/**
 * The <code>CCknConfirmationDialog</code> class implements a Confirmation 
 * Note.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknConfirmationDialog : public CEikDialog, public MEikInfoDialog
    {
    public:
        //** Constructors and destructor */

        /**
         * Starts the two-phase object construction.
         *
         * @return a pointer to the newly constructed 
         *         <code>CCknConfirmationDialog</code> object
         */
        static CCknConfirmationDialog* NewL();

        /**
         * The object destructor.
         */
        ~CCknConfirmationDialog();

        //** New methods */

        /**
         * Invokes the Confirmation Note displaying the default icon.
         *
         * @param aMsgRid The resource ID containing the message text
         * @param aButtonsResource The resource ID for the Confirmation Note's 
         *                         button group
         * @return the ID of the button used to dismiss the Confirmation Note
         * @remarks
         * @see
         */
        IMPORT_C static TInt RunDlgWithDefaultIconLD(TInt aMsgRid, TInt aButtonsResource);

        /**
         * Invokes the Confirmation Note displaying the default icon. 
         * Added for Series 80 to allow clients to specify which of the 
         * commands shown in the CBA is the default one. <b>Note:</b>
         * Dialog button groups cannot have a default command.
         *
         * @param aMsgRid The resource ID containing the message text
         * @param aButtonsResource The resource ID for the Confirmation Note's
         *                         button group
         * @param aDefaultCommand The resource ID that is set as the
         *                        default command for the Confirmation Note
         * @return the ID of the button used to dismiss the Confirmation Note
         * @remarks
         * @see
         */
        IMPORT_C static TInt RunDlgWithDefaultIconLD(TInt aMsgRid, TInt aButtonsResource, TInt aDefaultCommand);

        /**
         * Invokes the Confirmation Note displaying the default icon.
         *
         * @param aMsg The descriptor containing the message text
         * @param aButtonsResource The resource ID for the Confirmation Note's 
         *                         button group         
         * @return the ID of the button used to dismiss the Confirmation Note
         * @remarks
         * @see
         */
        IMPORT_C static TInt RunDlgWithDefaultIconLD(const TDesC& aMsg, TInt aButtonsResource);

        /**
         * Invokes the Confirmation Note displaying a custom icon.
         *
         * @param aMsg The descriptor containing the message text
         * @param aButtonsResource The resource ID for the Confirmation Note's 
         *                         button group
         * @param aIcon The icon. No icon if <code>NULL</code>
         * @return the ID of the button used to dismiss the Confirmation Note
         * @remarks
         * @see
         */
        IMPORT_C static TInt RunDlgWithCustomIconLD(const TDesC& aMsg, TInt aButtonsResource, CGulIcon* aIcon=NULL);

        /**
         * Invokes the Confirmation Note displaying a custom icon.
         *
         * @param aMsgRid The resource ID containing the message text
         * @param aButtonsResource The resource ID for the Confirmation Note's 
         *                         button group
         * @param aIcon The icon. No icon if <code>NULL</code>
         * @return the ID of the button used to dismiss the Confirmation Note
         * @remarks
         * @see
         */
        IMPORT_C static TInt RunDlgWithCustomIconLD(TInt aMsgRid, TInt aButtonsResource, CGulIcon* aIcon=NULL);

        /**
         * Invokes the Confirmation Note displaying the default icon.
         *
         * @param aMsgRid The resource ID containing the message text
         * @param aButtonsResource The resource ID for the Confirmation Note's 
         *                         button group
         * @param aDialog The address of this Confirmation Note is passed to 
         *                the developer
         * @return the ID of the button used to dismiss the Confirmation Note
         * @remarks
         * @see
         */
        IMPORT_C static TInt RunDlgWithDefaultIconLD(TInt aMsgRid, TInt aButtonsResource, CCknConfirmationDialog*& aDialog);

        /**
         * Invokes the Confirmation Note displaying the default icon.
         * Added for Series 80 to allow clients to specify which of the 
         * commands shown in the CBA is the default one. <b>Note:</b>  
         * Dialog button groups cannot have a default command.
         *
         * @param aMsgRid The resource ID containing the message text
         * @param aButtonsResource The resource ID for the Confirmation Note's 
         *                         button group
         * @param aDialog The address of this Confirmation Note is passed to
         *                the developer
         * @param aDefaultCommand Button resource ID that will be set as the
         *                        default command for the Confirmation Note
         * @return the ID of the button used to dismiss the Confirmation Note
         * @remarks
         * @see
         */
        IMPORT_C static TInt RunDlgWithDefaultIconLD(TInt aMsgRid, TInt aButtonsResource, CCknConfirmationDialog*& aDialog, TInt aDefaultCommand);

        /**
         * Invokes the Confirmation Note displaying the default icon.
         *
         * @param aMsg The descriptor containing the message text
         * @param aButtonsResource The resource ID for the Confirmation Note's 
         *                         button group
         * @param aDialog The address of this Confirmation Note is passed to
         *                the developer
         * @return the ID of the button used to dismiss the Confirmation Note
         * @remarks
         * @see
         */
        IMPORT_C static TInt RunDlgWithDefaultIconLD(const TDesC& aMsg, TInt aButtonsResource, CCknConfirmationDialog*& aDialog);

        /**
         * Invokes the Confirmation Note displaying a custom icon.
         *
         * @param aMsg The descriptor containing the message text
         * @param aButtonsResource The resource ID for the Confirmation Note's 
         *                         button group
         * @param aIcon The icon. No icon if <code>NULL</code>
         * @param aDialog The address of this Confirmation Note is passed to
         *                the developer
         * @return the ID of the button used to dismiss the Confirmation Note
         */
        IMPORT_C static TInt RunDlgWithCustomIconLD(const TDesC& aMsg, TInt aButtonsResource, CGulIcon* aIcon, CCknConfirmationDialog*& aDialog);

        /**
         * Invokes the Confirmation Note displaying a custom icon.
         *
         * @param aMsgRid The resource ID containing the message text
         * @param aButtonsResource The resource ID for the Confirmation Note's 
         *                         button group
         * @param aIcon The icon. No icon if <code>NULL</code>
         * @param aDialog The address of this Confirmation Note is passed to the developer
         * @return the ID of the button used to dismiss the Confirmation Note
         */
        IMPORT_C static TInt RunDlgWithCustomIconLD(TInt aMsgRid, TInt aButtonsResource, CGulIcon* aIcon, CCknConfirmationDialog*& aDialog);

    private:    //** Methods */
        CCknConfirmationDialog();

        CCknConfirmationDialog(const TDesC& aTitle, const TDesC& aMsg, CGulIcon* aIcon, const TDesC* aOperationName);

        CCknConfirmationDialog(TInt aTitleRid,TInt aMsgRid, CGulIcon* aIcon, TInt aOperationNameRid);

        TBool RunDlgLD(TInt aResource, const TDesC& aTitle, const TDesC& aMsg);

        void PreLayoutDynInitL();

        TBool OkToExitL(TInt aButtonId);

    private:    //** Data */
        const TDesC* iTitle;
        const TDesC* iMessage;
        const TDesC* iOperationName;
        TInt iTitleRid;
        TInt iMessageRid;
        const CGulIcon* iIcon;
        TInt iOperationNameRid;
        HBufC* iTitleBuf;
        HBufC* iMessageBuf;
        HBufC* iOperationNameBuf;
        TInt iButtonsResource;
        CCknConfirmationDialog** iSelfPointer;

    public:
        /**
         * Kept for binary compatibility.
         * @deprecated
         */
        IMPORT_C static TBool RunDlgLD(const TDesC& aTitle, const TDesC& aMsg, CGulIcon* aIcon=NULL, const TDesC* aOperationName=NULL);
        
        /**
         * Kept for binary compatibility.
         * @deprecated
         */
        IMPORT_C static TInt RunDlgLD(const TDesC& aTitle, const TDesC& aMsg, TInt aButtonsResource, CGulIcon* aIcon=NULL);

        /**
         * Kept for binary compatibility.
         * @deprecated
         */
        IMPORT_C static TBool RunDlgLD(TInt aTitleRid, TInt aMsgRid, CGulIcon* aIcon=NULL, TInt aOperationNameRid=NULL);
    };


#endif // CKNCONF_H

// End of File