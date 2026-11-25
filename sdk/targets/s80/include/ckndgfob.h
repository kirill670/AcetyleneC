/**
* ==============================================================================
*  Name        : ckndgfob.h
*  Part of     : CKON
*  Interface   : Object Dialog API
*  Description : Base classes for dialogs with file lists, and for file updating dialogs.
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


#ifndef CKNDGFOB_H
#define CKNDGFOB_H

// INCLUDES
#include <eikdialg.h>
#include <EikLbo.h>


// FORWARD DECLARATIONS
class CCknFileUpdateReporter;
class CEikDirContentsListBox;


// CLASS DECLARATIONS

/**
 * The <code>MCknDialogObserver</code> class implements an interface that 
 * can be queried to decide whether to allow an object in an open dialog.
 *
 * @lib ckndlg.lib
 * @since Series90 1.1
 */
class MCknDialogObserver
    {
    public:
       /**
        * Implemented by file dialogs to provide a check on the filename 
        * before closing the dialog.`
        *
        * @param aPath A reference to a descriptor containing the full path 
        *              to a file
        * @return <code>ETrue</code> if the path is OK
        *         <code>EFalse</code> if the path is not OK
        * @remarks
        * @see
        */
        IMPORT_C virtual TBool IsOkToExitL(const TDesC& aPath) = 0;
    };

/**
 * The <code>MCknFileUpdateObserver</code> class implements an interface for 
 * an observer of file dialogs.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class MCknFileUpdateObserver
    {
    public:

    // New methods

       /**
        * Implemented by file dialogs to allow observers to keep updating them.
        *
        * @remarks
        * @see
        */
        virtual void StartUpdateTimer()=0;

    };

/**
 * The <code>CCknUpdatingFileDialogBase</code> class is for any file dialog 
 * that requires file server change notifications. This handles delaying 
 * notifications if the dialog does not have focus, and any file server errors.
 *
 * @internal
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknUpdatingFileDialogBase : public CEikDialog, public MCknFileUpdateObserver
    {

    public:  // Declarations
        enum
            { // these flags are passed on to the Browse dialog
            EDisableBrowseButton=1,
            EShowSystemFolders=2,
            EShowSystemFilesAndFolders=2,
            EShowHiddenFolders=4,
            EShowHiddenFilesAndFolders=4,
            EShowAllDrives=8,
            EShowRomDrive=16,
            EDisableCancelButton=32,
            EShowBothFilesAndFolders=64,
            /** extends the directory list beyond the default path */
            EShowExtendedView=128,
            EDisallowNewFolder=256,
            /**
            * this flag sets the dialog to show informational text in 
            * directories that have no files
            */
            EShowNoFilesText=0x2000,    
            /** this flag is used to display old-style file dialogs */
            EUseOldDialogs=0x40000
            };

    private:  // Declarations

        enum
            {
            EUpdateOnFocus=1,
            };

    protected:  // Methods

    // Constructors and destructor

        CCknUpdatingFileDialogBase();
        virtual ~CCknUpdatingFileDialogBase();

    // Methods from base classes

        virtual void PostLayoutDynInitL();

    // New Methods

        /**
        * Callback class to be called when the file server has completed an 
        * update.
        */
        virtual void DoUpdateTimerCallBackL()=0;

    // Methods from base classes

        virtual void FocusChanged(TDrawNow aDrawNow);

        virtual void StartUpdateTimer();

    // New Methods

        virtual void UpdateTimerCallBackL();

        virtual TBool CanUpdate();

        virtual void HandleCorruptOrMissingDiskL();

        virtual void HandleErrorFromFileServerL(TInt aErrorCode);

        virtual void StartUpdateTimer(TInt aInterval);

    private: //Methods

        static TInt UpdateTimerCallBackL(TAny* aObj);

    private:     // Data

        CCknFileUpdateReporter* iUpdateReporter;
        CPeriodic* iUpdateTimer;
        TTime iLastUnhandledErrorTime;
        TUint iFileSelFlags;
        RFs iFsSession;

    };

/**
 * The <code>CCknFileListDialogBase</code> class is for any file dialog that 
 * requires a directory contents file list, that is the 'Save As', 'Open 
 * File' and 'New File' dialogs. Handles browsing and updating the directory 
 * contents list box upon file server changes.
 *
 * @internal
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknFileListDialogBase : public CCknUpdatingFileDialogBase, public MEikListBoxObserver
    {

    protected:  // Methods

    // Constructors and destructor

        CCknFileListDialogBase(TDes& aPath,TUint aFlags,TUid aFileUid);
        virtual ~CCknFileListDialogBase();

    // New Methods

        TUid ApplicationUid() const;
        void CreateBrowseDialogL(TBool aAllowNewFolder);
        void SetTitleTextL(TInt aRid);
        void SetDummyItemTextL(HBufC* aDummyItemText);
        inline void SetTitleText(HBufC* aTitle);
        inline void SetTitleTextL(const TDesC& aTitle);
        virtual void FileServerHasChangedL();
        TBool DriveAccessible(const TDesC& aPath);
       /**
        * Update the text displayed on the third button of the dialog.
        */
        virtual void UpdateThirdButtonTextL()=0;
        virtual void UpdateTitleL();
// MEikListBoxObserver
    // Methods from base classes

        virtual void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);
// from CEikDialog/CEikForm/CCoeControl
        virtual void HandleControlStateChangeL(TInt aControl);
        virtual void PostLayoutDynInitL();
        virtual void PreLayoutDynInitL();
// from CCknUpdatingFileDialogBase
        virtual TBool CanUpdate();
// from CEikDialog
        TBool OkToExitL(TInt aButtonId);

    private: //Methods

        void DoUpdateTimerCallBackL();

    protected:     // Data

        CEikDirContentsListBox* iDirContentsListBox;
        TDes& iPath;
        TUint iFlags;
        TUid iFileUid;
        HBufC* iTitleText;

    };

inline void CCknFileListDialogBase::SetTitleText(HBufC* aTitle)
    {
    delete iTitleText;
    iTitleText=aTitle;
    }

inline void CCknFileListDialogBase::SetTitleTextL(const TDesC& aTitle)
    {
    SetTitleText(aTitle.AllocL());
    }

#endif      // CKNDGFOB_H   
            
// End of File
