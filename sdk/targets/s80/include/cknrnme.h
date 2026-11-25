/*
* ==============================================================================
*  Name        : cknrnme.h
*  Part of     : CKON
*  Interface   : Object Dialog API
*  Description : Dialogs for renaming objects and folders.
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


#ifndef CKNRNME_H
#define CKNRNME_H


// INCLUDES
#include <eikdialg.h>
#include <CknObjectType.h>

// CLASS DECLARATIONS

/**
* The <code>CCknRenameObjectDialog</code> class implements the Rename Dialog.
* It allows a filename and its extension to be renamed. The title of 
* the Rename Dialog varies according to the type of object to be 
* renamed. The type of object can either be explicitly specified using a 
* resource ID or a descriptor, or the dialog determines the type of 
* the object to be renamed from the path specified.
* 
* @lib ckndlg.lib
* @since Series90 1.0
*/

class CCknRenameObjectDialog : public CEikDialog
    {
    public:  // Declarations
    /** 
     * The enumeration <code>TRenameObjectUserFlags</code> specifies whether 
     * the extension is displayed along with the filename. The new filename 
     * returned will contain the new extension specified by the user. */
    enum TRenameObjectUserFlags
        {
        /** shows the extension along with the filename */
        EShowExtensions=0x0001
        };
    private:  // Declarations
    public:
    // Constructors and destructor
    // New methods
        /**
        * Displays the Rename Dialog specifying the type of object to be 
        * renamed.
        * 
        * @param aObjectType The type of object to be renamed. The title of the
        *                    Rename Dialog varies according to the object type 
        * @param aPath A string specifying the file to be renamed. 
        *              Should include the drive, complete absolute 
        *              path, filename, and any extension
        * @param aNewName Returns the new filename specified by the user. Does 
        *                 not contain the complete path, but just the new 
        *                 filename and extension. The extension is the same as 
        *                 the original if <code>aFlags</code> is set to a 
        *                 default value of <code>0</code>; otherwise the
        *                 new extension specified by the user is returned
        * @param aFlags Specifies that the file extension has to be shown
        *               in the Rename Dialog along with the filename. The 
        *               default is <code>0</code>, which specifies that no 
        *               extension is shown. If set to 
        *               <code>EShowExtensions</code>, the extension is  
        *               displayed and can be changed by the user
        * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> 
        *         if the user taps Cancel
        * @remarks The string specifying the file to be renamed(aPath) must not contain 
		*		   any of these characters <>"/|\:?*. Having any of these characters in 
		*		   the string might cause a panic.
        * @see <code>TCknObjectType</code> in cknobjecttype.h
        */
        IMPORT_C static TBool RunDlgLD(TCknObjectType aObjectType, const TDesC& aPath, TDes& aNewName, TUint aFlags=0);

        /**
        * Displays the Rename Dialog. The dialog determines the type of the 
        * object to be renamed from the path specified and displays the title
        * of the Rename Dialog accordingly.
        *
        * @param aPath A string specifying the file to be renamed. 
        *              Should include the drive, complete absolute 
        *              path, filename, and any extension
        * @param aNewName Returns the new filename specified by the user. Does 
        *                 not contain the complete path, but just the new 
        *                 filename and extension. The extension is the same as 
        *                 the original if <code>aFlags</code> is set to a 
        *                 default value of <code>0</code>; otherwise the
        *                 new extension specified by the user is returned
        * @param aFlags Specifies that the file extension has to be shown
        *               in the Rename Dialog along with the filename. The 
        *               default is <code>0</code>, which specifies that no 
        *               extension is shown. If set to 
        *               <code>EShowExtensions</code>, the extension is  
        *               displayed and can be changed by the user
        * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> 
        *         if the user taps Cancel
        * @remarks The string specifying the file to be renamed(aPath) must not contain 
		*		   any of these characters <>"/|\:?*. Having any of these characters in 
		*		   the string might cause a panic.
        * @see <code>TRenameObjectUserFlags</code>
        */
        IMPORT_C static TBool RunDlgLD(const TDesC& aPath, TDes& aNewName, TUint aFlags=0);

        /**
        * Displays the Rename Dialog with a custom title.
        *
        * @param aTitleRid The ID of the resource used for the title of the 
        *                  Rename Dialog
        * @param aPath A string specifying the file to be renamed. 
        *              Should include the drive, complete absolute 
        *              path, filename, and any extension
        * @param aNewName Returns the new filename specified by the user. Does 
        *                 not contain the complete path, but just the new 
        *                 filename and extension. The extension is the same as 
        *                 the original if <code>aFlags</code> is set to a 
        *                 default value of <code>0</code>; otherwise the
        *                 new extension specified by the user is returned
        * @param aFlags Specifies that the file extension has to be shown
        *               in the Rename Dialog along with the filename. The 
        *               default is <code>0</code>, which specifies that no 
        *               extension is shown. If set to 
        *               <code>EShowExtensions</code>, the extension is  
        *               displayed and can be changed by the user
        * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> 
        *         if the user taps Cancel
        * @remarks The string specifying the file to be renamed(aPath) must not contain 
		*		   any of these characters <>"/|\:?*. Having any of these characters in 
		*		   the string might cause a panic.
        * @see <code>TRenameObjectUserFlags</code>
        */
     
        IMPORT_C static TBool RunDlgLD(TInt aTitleRid, const TDesC& aPath, TDes& aNewName, TUint aFlags=0);

        /**
        * Displays the Rename Dialog with a custom title.
        *
        * @param aTitle     A string specifying the title of the 
        *                   Rename Dialog 
        * @param aPath A string specifying the file to be renamed. 
        *              Should include the drive, complete absolute 
        *              path, filename, and any extension
        * @param aNewName Returns the new filename specified by the user. Does 
        *                 not contain the complete path, but just the new 
        *                 filename and extension. The extension is the same as 
        *                 the original if <code>aFlags</code> is set to a 
        *                 default value of <code>0</code>; otherwise the
        *                 new extension specified by the user is returned
        * @param aFlags Specifies that the file extension has to be shown
        *               in the Rename Dialog along with the filename. The 
        *               default is <code>0</code>, which specifies that no 
        *               extension is shown. If set to 
        *               <code>EShowExtensions</code>, the extension is  
        *               displayed and can be changed by the user
        * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> 
        *         if the user taps Cancel
        * @remarks The string specifying the file to be renamed(aPath) must not contain 
		*		   any of these characters <>"/|\:?*. Having any of these characters in 
		*		   the string might cause a panic.
        * @see <code>TRenameObjectUserFlags</code>
        */

        IMPORT_C static TBool RunDlgLD(const TDesC& aTitle, const TDesC& aPath, TDes& aNewName, TUint aFlags=0);

        /**
        * From CCoeControl Not used.
        * @param aContext Not used
        * @internal
        */
        void GetHelpContext(TCoeHelpContext& aContext) const;

        
    protected:  // Methods

    // New Methods
        
    private: //Methods
        CCknRenameObjectDialog(TCknObjectType aType, const TDesC& aPath, TDes& aNewName, TUint aFlags);
        CCknRenameObjectDialog(TDesC& aTitle, TDesC& aPath, TDes& aNewName);

        /**
        * Destructor.
        */

        ~CCknRenameObjectDialog();
        void PreLayoutDynInitL();
        TBool OkToExitL(TInt aButtonId);
        TBool IsNewNameValidL(TInt& aInfoprintResourceId);
        TInt GetTitleResource();
        void SetTitleText(HBufC* aTitle);
        
        private:     // Data
        /// The type of the Object to be renamed using the Rename Dialog.
        TCknObjectType iObjectType;

        /// Text string for dialog title.
        HBufC* iTitle;

        /// Complete path of the file to be renamed along with the extension.
        const TDesC& iPath;

        /// The new name of the file specified by the user.
        TDes& iNewName;

        /// Whether the file extension has to be shown in the Rename Dialog.
        TUint iFlags;

        HBufC* iOriginalName;
    };


/**
 * The <code>CCknRenameFolderDialog</code> implements the Rename Folder Dialog.
 * This class only allows the folder name to be changed to a different folder 
 * name within the same parent folder.
 *
 * @lib ckndlg.lib
 * @since Series 90 1.0
 */
class CCknRenameFolderDialog : public CEikDialog
    {

    public:

    // New methods

        /**
        * Displays the Rename Folder Dialog.
        *
        * @param aPath A string specifying the path of the folder to 
        *              be renamed. Should include the drive. Should not include 
        *              any filename, but must include a terminating backslash
        * @param aNewPath Returns the new path of the renamed folder. Contains 
        *                 the full path including the drive and the terminating 
        *                 backslash
        * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> 
        *         if the user taps Cancel
        * @remarks The string specifying the path of the folder to be renamed(aPath) 
		*          must not contain any of these characters <>"/|\:?*. Having any of 
		*          these characters in the string might cause a panic.
        * @see
        */
    IMPORT_C static TBool RunDlgLD(TDesC& aPath, TDes& aNewPath);

    //from CCoeControl
        /**
        * Not used.
        * @internal
        */
    void GetHelpContext(TCoeHelpContext& /*aContext*/) const {};

    private: //Methods
        CCknRenameFolderDialog(TDesC& aPath, TDes& aNewPath);
        ~CCknRenameFolderDialog();
        void PreLayoutDynInitL();
        TBool OkToExitL(TInt aButtonId);
        TBool IsNewFolderValidL(TInt& aInfoprintResourceId);
        TBool IsMaxPathReachedL(TInt& aInfoprintResourceId);

    private:     // Data

        /** A string specifying the path of the folder to be renamed. */
        TDesC& iPath;
        /** Path of the renamed folders parent folder. */
        TPtrC iParentPath;
        /** New path of the renamed folder */
        TDes& iNewPath;
        /** Original folder name. */
        HBufC* iOriginalName;

    };


#endif      // CKNRNME_H   
            
// End of File
