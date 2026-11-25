/**
* ==============================================================================
*  Name        : cknnewfolderdialog.h
*  Part of     : CKON
*  Interface   : Object Dialog API
*  Description : Dialog for creating a new folder
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


#ifndef CKNNEWFOLDERDIALOG_H
#define CKNNEWFOLDERDIALOG_H

// INCLUDES
#include <eikdialg.h>

// CLASS DECLARATIONS

/**
 * The <code>CCknNewFolderDialog</code> class implements a dialog for creating 
 * a new folder.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknNewFolderDialog : public CEikDialog
    {

    public:

    // New methods

       /**
        * Runs the new folder dialog.
        *
        * @param aStartingFolderPath The full path of the parent folder for 
        *                            the new folder to be created
        * @param aNewFolderPath Used to return the full path of the newly 
        *                       created folder if the user presses OK; if the 
        *                       user presses cancel, the value is undefined
        * @param aAllowChangeLocation Used to determine whether the dialog can 
        *                             change the location of the parent 
        *                             folder; if true, the location line of 
        *                             the dialog can be tapped to open a 
        *                             Change Folder dialog
        * @return <code>ETrue</code> if the user taps OK, 
        *         <code>EFalse</code> if the user taps Cancel
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(const TPath& aStartingFolderPath, 
                                        TPath& aNewFolderPath,
                                        TBool aAllowChangeLocation=ETrue);

       /**
        * Runs the new folder dialog.
        *
        * @param aTitleRid Resource ID of the title text to use in the dialog
        * @param aStartingFolderPath The full path of the parent folder for 
        *                            the new folder to be created
        * @param aNewFolderPath If the user taps OK, used to return the 
        *                       full path of the newly created folder; if the 
        *                       user taps Cancel, the value is undefined
        * @param aAllowChangeLocation Used to determine whether the dialog can 
        *                             change the location of the parent folder; 
        *                             if true, the location line of the dialog 
        *                             can be tapped to open a Change Folder 
        *                             dialog
        * @return <code>ETrue</code> if the user taps OK,
        *         <code>EFalse</code> if the user taps Cancel
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(TInt aTitleRid,
                                       const TPath& aStartingFolderPath, 
                                       TPath& aNewFolderPath,
                                       TBool aAllowChangeLocation=ETrue);

    private: //Methods

        /**
        * C++ constructor for the new folder dialog
        *
        * @param     "TInt aTitleRid"
        *             Resource ID of the text string to be used as the dialog title
        *
        * @param     "const TPath& aStartingFolderPath"
        *              The full path of the parent folder for the new folder to be created
        *
        * @param      "TPath& aNewFolderPath"
        *              Reference to a TPath used to return the full path of the newly created folder
        *              if the user presses OK.  If the user presses cancel the value is undefined
        *       
        * @param     "TBool aAllowChangeLocation"
        *              Used to determine whether the dialog can change the location of the parent
        *             folder. If true, the location line of the dialog can be tapped to open a
        *             Change folder dialog
        */
       CCknNewFolderDialog(TInt aTitleRid,
                           const TPath& aStartingFolderPath, 
                           TPath& aNewFolderPath, 
                           TBool aAllowChangeLocation);
        /**
        * Function to re-seed the New Folder name field with a unique folder 
        * name. Uses a localised name stub and appends a numeral contained 
        * within localisable prefix and postfix e.g. " (01)". If the user has 
        * already entered a value in the name field then this is unchanged.
        */
        void ResetNewFolderNameL();
        /**
        * Function that returns the next candidate folder name, including an 
        * incremental number used to achieve uniqueness.
        *
        * @param    "TInt aNumber"
        *           The incremented number to be used in the candidate 
        *           folder name 
        *
        * @param    "TDes& aNewFolder"
        *            The candidate folder name (including the full path)
        */
        void GetNextNewFolderNameL(TInt aNumber, TDes& aNewFolder);
        /**
        * Function that checks the new folder name is valid
        * i.e. within path length, unique, contains no illegal characters
        *
        * @param    "TInt& aInfoPrintResourceId"
        *           An id for a resource to use as text in an infoprint. 
        *
        * @returns  "TBool"
        *            ETrue if the new folder name is valid, else EFalse
        */
        TBool IsNewFolderValid(TInt& aInfoprintResourceId);
        void PreLayoutDynInitL();
        TBool OkToExitL(TInt aButtonId);
        void HandleControlStateChangeL(TInt aControlId);

    private:     // Data

        /** Full path of the currently selected parent folder */
        TPath iParentFolderPath;
        /** Full path of the new folder, to be returned */
        TPath& iNewFolderPath;
        /** Proposed name for the new folder */
        TFileName iNewFolderName;
        /** Used to determine if the location field is tappable open the Change Folder dialog */
        TBool iCanChangeLocation;
        /** Used to determine whether or not the user has entered value for the new folder name */
        TBool iUserEnteredName;
        /** The resource id for the dialog title */
        TInt iTitleRid;

    };

#endif      // CKNNEWFOLDERDIALOG_H   

// End of File
