/**
* ==============================================================================
*  Name        : ckncopyobjectdialog.h
*  Part of     : CKON
*  Interface   : Object Dialog API
*  Description : Dialogs for copying objects
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

#ifndef CKNCOPYOBJECTDIALOG_H
#define CKNCOPYOBJECTDIALOG_H


// INCLUDES
#include <eikdialg.h>
#include <CknObjectType.h>


// CLASS DECLARATIONS

/**
 * The <code>CCknCopyObjectDialog</code> class implements the "save <object>" 
 * dialog WID-Dia004. This dialog determines the user's choice of path and 
 * filename when saving a file. It ensures a unique filename, no illegal 
 * characters and correct path length. The dialog will take an application's 
 * 'suggested' path and filename, or will generate defaults if either of these 
 * are not present. The dialog will not save the file or perform any 
 * conversions.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknCopyObjectDialog : public CEikDialog
    {
    public:  // Declarations
    /** 
     * The enumeration <code>TCopyObjectDialogFlags</code> defines various 
     * flags in order to decide which folder and file extension options are 
     * available to the user when the dialog is created.
     */
    enum TCopyObjectDialogFlags
        {
        /** do not have the Change Folder dialog */
        ECopyObjectNoChangeLocation     =0x0001, 
        /** do not allow the creation of new folders */
        ECopyObjectNoNewFolder          =0x0002,
        /** show the file extension */
        ECopyObjectShowFileExtension    =0x0004  
        };

    public:

    // New methods
        
       /**
        * Runs the Save Object dialog with a custom title and object type 
        * independent infoprints. If the chosen filename already exists, the 
        * dialog will determine an object type specific infoprint from the 
        * file that shares the path and name, if this is possible. If a 
        * dialog-generated path or filename is used, these are also 
        * object type independent.
        *
        * @param aInitialDestination The suggested path/filename for the file 
        *                            to be saved; can be full 
        *                            drive+path+filename, drive only, 
        *                            drive+path or filename only. If the 
        *                            drive/drive+path is missing, the dialog 
        *                            provides a default path; if the filename 
        *                            is missing, the dialog provides a default 
        *                            filename. This includes an incrementing 
        *                            numerical postfix to ensure the filename 
        *                            is unique. The dialog ignores a filename 
        *                            if it includes any wildcard characters 
        * @param aDestination Reference to a <code>TFullName</code> used to 
        *                     return the full path/filename for saving the 
        *                     file. Undefined if the user does not confirm the 
        *                     dialog
        *                     
        * @param aTitleRid The ID of a resource used to set the dialog title
        * @param aFlags <code>TCopyObjectDialogFlags</code>
        * @param aNameEditorLabelRid The ID of a resource used as the name 
        *                            editor label text; if 0, the default text 
        *                            is used
        * @return <code>ETrue</code> if the user taps OK,
        *         <code>EFalse</code> if the user taps Cancel
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(const TFullName& aInitialDestination, TFullName& aDestination, TInt aTitleRid, TUint aFlags=0, TInt aNameEditorLabelRid=0);

       /**
        * Runs the Save Object dialog with a custom title and object type 
        * independent infoprints. If the chosen filename already exists, the 
        * dialog will determine an object type specific infoprint from the 
        * file that shares the path and name, if possible. If a 
        * dialog-generated path or filename is used, it  will also be 
        * object-type independent.
        *
        * @param aInitialDestination The suggested path/filename for the file 
        *                            to be saved; can be full 
        *                            drive+path+filename, drive only, 
        *                            drive+path or filename only. If the 
        *                            drive/drive+path is missing, the dialog 
        *                            provides a default path; if the filename 
        *                            is missing, the dialog provides a default 
        *                            filename. This includes an incrementing 
        *                            numerical postfix to ensure the filename 
        *                            is unique. The dialog ignores a filename 
        *                            if it includes any wildcard characters 
        * @param aDestination Reference to a <code>TFullName</code> used to 
        *                     return the full path/filename for saving the 
        *                     file. Undefined if the user does not confirm the 
        *                     dialog
        * @param aTitle Reference to a string used as the dialog title
        * @param aFlags <code>TCopyObjectDialogFlags</code>
        * @param aNameEditorCaption Reference to a string used as the name 
        *                           editor label text; if
        *                           <code>aNameEditorCaption=KNullDesC</code>, 
        *                           the default label text is used
        * @return <code>ETrue</code> if the user taps OK, 
        *         <code>EFalse</code> if the user taps Cancel
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(const TFullName& aInitialDestination, TFullName& aDestination, const TDesC& aTitle, TUint aFlags=0, const TDesC& aNameEditorCaption=KNullDesC);

       /**
        * Runs the Save Object dialog, taking an object type which is used to
        * determine the dialog title, infoprint text and any default filename
        * generated. For details see the <code>RunDlgLD</code> method above.
        *
        * @param aInitialDestination The suggested path/filename for the file 
        *                            to be saved; can be full 
        *                            drive+path+filename, drive only, 
        *                            drive+path or filename only. If the 
        *                            drive/drive+path is missing, the dialog 
        *                            provides a default path; if the filename 
        *                            is missing, the dialog provides a default 
        *                            filename. This includes an incrementing 
        *                            numerical postfix to ensure the filename 
        *                            is unique. The dialog ignores a filename 
        *                            if it includes any wildcard characters 
        * @param aDestination Reference to a <code>TFullName</code> used to 
        *                     return the full path/filename for saving the 
        *                     file. Undefined if the user does not confirm the 
        *                     dialog
        * @param aObjectType Indicates the object type
        * @param aFlags <code>TCopyObjectDialogFlags</code>
        * @return <code>ETrue</code> if the user taps OK, 
        *         <code>EFalse</code> if the user taps Cancel
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(const TFullName& aInitialDestination, TFullName& aDestination, TCknObjectType aObjectType, TUint aFlags=0);

       /**
        * Runs the Save Object dialog, using the path for the source file to 
        * determine the object type.
        *
        * @param aSource Used to determine the file type; this must be a full 
        *                path and filename
        * @param aInitialDestination The suggested path/filename for the file 
        *                            to be saved; can be full 
        *                            drive+path+filename, drive only, 
        *                            drive+path or filename only. If the 
        *                            drive/drive+path is missing, the dialog 
        *                            provides a default path; if the filename 
        *                            is missing, the dialog provides a default 
        *                            filename. This includes an incrementing 
        *                            numerical postfix to ensure the filename 
        *                            is unique. The dialog ignores a filename 
        *                            if it includes any wildcard characters 
        * @param aDestination Reference to a <code>TFullName</code> used to 
        *                     return the full path/filename for saving the 
        *                     file. Undefined if the user does not confirm the 
        *                     dialog
        * @param aFlags <code>TCopyObjectDialogFlags</code>
        * @return <code>ETrue</code> if the user taps OK, 
        *         <code>EFalse</code> if the user taps Cancel
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(const TFullName& aSource, const TFullName& aInitialDestination, TFullName& aDestination, TUint aFlags=0);    
       /**
        * Runs the Save Object dialog, reading the title and editor label from 
        * a resource.
        *
        * @param aInitialDestination The suggested path/filename for the file 
        *                            to be saved; can be full 
        *                            drive+path+filename, drive only, 
        *                            drive+path or filename only. If the 
        *                            drive/drive+path is missing, the dialog 
        *                            provides a default path; if the filename 
        *                            is missing, the dialog provides a default 
        *                            filename. This includes an incrementing 
        *                            numerical postfix to ensure the filename 
        *                            is unique. The dialog ignores a filename 
        *                            if it includes any wildcard characters 
        * @param aDestination Reference to a <code>TFullName</code> used to 
        *                     return the full path/filename for saving the 
        *                     file. Undefined if the user does not confirm the 
        *                     dialog
        * @param aTitleRid The ID of a resource used to set the dialog title
        * @param aFlags <code>TCopyObjectDialogFlags</code>
        * @param aNameEditorLabelRid The ID of a resource used as the name 
        *                            editor label text; if 0, the default text 
        *                            is used
        * @param aDialog A self pointer to the newly created dialog. This 
        *                method allocates memory for the dialog and sets 
        *                <code>aDialog</code> to point to the new dialog
        * @return <code>ETrue</code> if the user taps OK, 
        *         <code>EFalse</code> if the user taps Cancel
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(const TFullName& aInitialDestination, TFullName& aDestination, TInt aTitleRid, TUint aFlags, TInt aNameEditorLabelRid, CCknCopyObjectDialog*& aDialog);
       /**
        * Runs the Save Object dialog using a custom title and editor label.
        *
        * @param aInitialDestination The suggested path/filename for the file 
        *                            to be saved; can be full 
        *                            drive+path+filename, drive only, 
        *                            drive+path or filename only. If the 
        *                            drive/drive+path is missing, the dialog 
        *                            provides a default path; if the filename 
        *                            is missing, the dialog provides a default 
        *                            filename. This includes an incrementing 
        *                            numerical postfix to ensure the filename 
        *                            is unique. The dialog ignores a filename 
        *                            if it includes any wildcard characters 
        * @param aDestination Reference to a <code>TFullName</code> used to 
        *                     return the full path/filename for saving the 
        *                     file. Undefined if the user does not confirm the 
        *                     dialog
        * @param aTitle Reference to a string used as the dialog title
        * @param aNameEditorCaption Reference to a string used as the name 
        *                           editor label text; if 
        *                           <code>aNameEditorCaption=KNullDesC</code>, 
        *                           the default label text is used
        * @param aDialog A self pointer to the newly created dialog. This 
        *                method allocates memory for the dialog and sets 
        *                <code>aDialog</code> to point to the new dialog
        * @return <code>ETrue</code> if the user taps OK, 
        *         <code>EFalse</code> if the user taps Cancel
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(const TFullName& aInitialDestination, TFullName& aDestination, const TDesC& aTitle, TUint aFlags, const TDesC& aNameEditorCaption, CCknCopyObjectDialog*& aDialog);
       /**
        * Runs the Save Object dialog, taking an object type which is used to 
        * determine the dialog title, infoprint text and any default filename 
        * generated. 
        *
        * @param aInitialDestination The suggested path/filename for the file 
        *                            to be saved; can be full 
        *                            drive+path+filename, drive only, 
        *                            drive+path or filename only. If the 
        *                            drive/drive+path is missing, the dialog 
        *                            provides a default path; if the filename 
        *                            is missing, the dialog provides a default 
        *                            filename. This includes an incrementing 
        *                            numerical postfix to ensure the filename 
        *                            is unique. The dialog ignores a filename 
        *                            if it includes any wildcard characters 
        * @param aDestination Reference to a <code>TFullName</code> used to 
        *                     return the full path/filename for saving the 
        *                     file. Undefined if the user does not confirm the 
        *                     dialog
        * @param aObjectType Indicates the object type
        * @param aFlags <code>TCopyObjectDialogFlags</code>
        * @param aDialog A self pointer to the newly created dialog. This 
        *                method allocates memory for the dialog and sets 
        *                <code>aDialog</code> to point to the new dialog
        * @return <code>ETrue</code> if the user taps OK, 
        *         <code>EFalse</code> if the user taps Cancel
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(const TFullName& aInitialDestination, TFullName& aDestination, TCknObjectType aObjectType, TUint aFlags, CCknCopyObjectDialog*& aDialog);
       /**
        * Runs the save object dialog using the path for the source file to
        * determine the object type.
        *
        * @param aSource Used to determine the file type; this must be a full
        *                path and filename
        * @param aInitialDestination The suggested path/filename for the file 
        *                            to be saved; can be full 
        *                            drive+path+filename, drive only, 
        *                            drive+path or filename only. If the 
        *                            drive/drive+path is missing, the dialog 
        *                            provides a default path; if the filename 
        *                            is missing, the dialog provides a default 
        *                            filename. This includes an incrementing 
        *                            numerical postfix to ensure the filename 
        *                            is unique. The dialog ignores a filename 
        *                            if it includes any wildcard characters 
        * @param aDestination Reference to a <code>TFullName</code> used to 
        *                     return the full path/filename for saving the 
        *                     file. Undefined if the user does not confirm the 
        *                     dialog
        * @param aFlags <code>TCopyObjectDialogFlags</code>
        * @param aDialog A self pointer to the newly created dialog. This 
        *                method allocates memory for the dialog and sets 
        *                <code>aDialog</code> to point to the new dialog
        * @return <code>ETrue</code> if the user taps OK, 
        *         <code>EFalse</code> if the user taps Cancel
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(const TFullName& aSource, const TFullName& aInitialDestination, TFullName& aDestination, TUint aFlags, CCknCopyObjectDialog*& aDialog);  

    private: //Methods

        CCknCopyObjectDialog(const TFullName& aFileName, TFullName& aSaveToFullFileName, TUint aFlags, TCknObjectType aObjectType);
        ~CCknCopyObjectDialog();
        /**
        * Method that returns a resource id for the dialog title. Only used if the application passed
        * in a value for TCopyObjectDialogType aObjectType in the RunDlgLD method. The resource is 
        * object-type dependant. 
        *
        * @return The id of the dialog title resource.
        */
        TInt GetTitleResource();
        /**
        * Method that returns a resource for the "object exists" infoprint. 
        *
        * @param aCopyObjectType The object type referred to by the resource
        * @return The id of the "object exists" infoprint resource.
        */
        TInt GetObjectExistsNoteResource(TCknObjectType aCopyObjectType);
        /**
        * Method that returns a resource for the filename stub used to generate a unique filename if
        * the application has not included a filename in the aFileName argument of the run method. 
        * The resource is object type dependant if the application passed in a value for 
        * TCopyObjectDialogType aObjectType in the RunDlgLD method. Otherwise it is a default, 
        * object type independent resource
        *
        * @return TInt The id of the filename stub resource.
        */
        TInt GetDefaultFileNameStubResource();
        /**
        * Method that generates a unique filename using a file name stub. Used to seed the name
        * field if the application does not pass in a filename in the aFileName argument of the run 
        * method, or the user OK's the dialog with no text in the name field.
        */
        void SetDefaultNewFileNameL();
        /**
        * Function that returns the next candidate file name including an 
        * incremental number used to achieve uniqueness.
        *
        * @param    "TInt aNumber"
        *           The incremented number to be used in the candidate file name 
        *
        * @param    "TDes& aNewFile"
        *            The candidate file name (including the full path)
        */
        void GetNextNewFileNameL(TInt aNumber, TDes& aNewFile);
        /**
        * Method that determines a default path for the file's parent folder, used when the application 
        * has not included a Drive or Drive+path in the aFileName argument of the run method.
        * Or if the Path passed is on the default folder drive, but does not have the default folder
        * as a parent.
        */
        void CheckDefaultPath();
        /**
        * Method that checks for uniqueness of file name, illegal characters and path length.
        * It gives appropriate infoprints if the filename is not valid.
        *
        * @param aInfoprintResourceId An id for a resource to use as text in an infoprint.           
        *
        * @return ETrue if the new file name is valid, else EFalse
        */
        TBool IsNewFileNameValidL(TInt& aInfoprintResourceId);
        /**
        * Method that checks that the parent directory exists.
        *          
        * @return ETrue if the new parent folder exists, else EFalse
        */
        TBool LocationExistsL();
        /**
        * Method that sets iTitle to the value passed in aTitle
        */
        void SetTitleText(HBufC* aTitle);
        /**
        * Method that sets iNameEditorLabel to the value passed in aNameEditorLabel
        */
        void SetNameEditorLabelText(HBufC* aNameEditorLabel);

        void PreLayoutDynInitL();
        TBool OkToExitL(TInt aButtonId);
        void HandleControlStateChangeL(TInt aControlId);

    private:     // Data

        /**
        * Full path of the currently selected parent folder
        */
        TPath iParentFolderPath;
        /**
        * Full path/name to save the file to, to be returned.
        */
        TFullName& iSaveToFullFileName;
        /**
        * Proposed name for the saved file
        */
        TFileName iFileName;
        /**
        * Extension for the saved file
        */
        HBufC* iExtension;
        /**
        * Used to determine whether or not the parent folder can be changed
        * or new folders created
        */
        TUint iFlags;
        /**
        * Used to determine whether or not the application has provided a value for the 
        * file name or the user has entered a value for the file name.
        */
        TBool iUserOrAppEnteredName;
        /**
        * The text used for the dialog title
        */
        HBufC* iTitle;
        /**
        * The text used for the name edior label
        */
        HBufC* iNameEditorLabel;
        /**
        * The type of object to be saved
        */
        TCknObjectType iCopyObjectType;

        /**
        * allows the caller to delete the dialog
        */
        CCknCopyObjectDialog** iSelfPointer;
    };


#endif      // CKNCOPYOBJECTDIALOG_H   

// End of File
