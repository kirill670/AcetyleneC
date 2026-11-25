/**
* ==============================================================================
*  Name        : ckndgtrg.h
*  Part of     : CKON
*  Interface   : Object Dialog API
*  Description : Dialog to select a folder.
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

#ifndef CKNDGTRG_H
#define CKNDGTRG_H


// INCLUDES
#include "Ckndgfob.h"
#include <EikLbed.h>
#include <EikLbo.h>
#include <EikEnv.h>
#include <EikHlbi.h>
#include <EikDtlbx.h>

// FORWARD DECLARATIONS
class CEikDirectoryTreeListBox;
class CCknTargetFolderDialog;

// CLASS DECLARATIONS

/**
 * The <code>TTargetFolderItemObserver</code> class is a helper class for the 
 * <code>CCknTargetFolderDialog</code> folder dialog. It is used to react to 
 * collapse and expand events to update the CBA.
 * 
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class TTargetFolderItemObserver : public MHierarchicalListItemObserver
    {
private:    // from MHierarchicalListItemObserver
    void ItemUpdated(TInt aItemIndex, TEvent aEvent);

public:
    /** The dialog used to update the CBA*/
    CCknTargetFolderDialog* iDialog;
    };

/**
 * The <code>MCknTargetFolderDialogObserver</code> class can perform extra 
 * error checking on the selected path before the dialog closes.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class MCknTargetFolderDialogObserver : public MCknDialogObserver
    {

    public:

    // New methods

       /**
        * Implementing this method gives the caller of a Target Folder dialog 
        * the opportunity to perform any further checks on the suitability of 
        * the selected folder, and to generate an appropriate infoprint.
        *
        * @param aPath The selected folder to be checked
        * @return <code>ETrue</code> if the folder is suitable, to close the 
        *         dialog and continue; <code>EFalse</code> if the folder is 
        *         not suitable, to keep the dialog open
        * @remarks
        * @see
        */
        IMPORT_C virtual TBool IsOkToExitL(const TDesC& aPath)=0;
        
    private: //Methods

        IMPORT_C virtual void MCknTargetFolderDialogObserver_Reserved_1();
        IMPORT_C virtual void MCknTargetFolderDialogObserver_Reserved_2();

    };

/**
 * The <code>CCknTargetFolderDialog</code> class implements the Select Folder 
 * dialog. Allows a folder to be selected, with optional "New Folder" button.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknTargetFolderDialog : public CCknUpdatingFileDialogBase, public MEikListBoxObserver, 
                                public MListBoxEditorObserver
    {

    private:  // Declarations

        enum TTargetDialogType
            {
            ESelectDialog,
            ECopyDialog,
            EMoveDialog,
            EUserDialog,
            };

    public: // Methods

    // New methods
        
       /**
        * Runs the dialog to select a folder. Title is fixed.
        *
        * @param aPath Initial folder path in dialog. Also filled in with 
        *              user's selection if they OK the dialog
        * @param aFlags Flags to control the operation of the dialog
        * @return <code>ETrue</code> if the user OKs a selection, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks
        * @see
        */
        inline static TBool RunSelectFolderDlgLD(TDes& aPath,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);

       /**
        * Runs the dialog to select a folder. Title is fixed.
        *
        * @param aPath Initial folder path in dialog. Also filled in with 
        *              user's selection if they OK the dialog
        * @param aFlags Flags to control the operation of the dialog
        * @return <code>ETrue</code> if the user OKs a selection, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks
        * @see
        */
        inline static TBool RunCopyDlgLD(TDes& aPath,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);

       /**
        * Runs the dialog to select a folder. Title is fixed.
        *
        * @param aPath Initial folder path in dialog. Also filled in with 
        *              user's selection if they OK the dialog
        * @param aFlags Flags to control the operation of the dialog
        * @return <code>ETrue</code> if the user OKs a selection, 
         *         <code>EFalse</code> if the dialog is canceled 
        * @remarks
        * @see
        */
        inline static TBool RunMoveDlgLD(TDes& aPath,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);

       /**
        * Runs the dialog to select a folder with extra error checking. Title
        * is fixed.
        *
        * @param aPrecheckExitObserver Observer that will perform extra error 
        *                              checking on the selected folder before 
        *                              the dialog closes
        * @param aPath Initial folder path in dialog. Also filled in with
        *              user's selection if they OK the dialog 
        * @param aFlags Flags to control the operation of the dialog
        * @return <code>ETrue</code> if the user OKs a selection, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks
        * @see
        */
        inline static TBool RunMoveDlgLD(MCknTargetFolderDialogObserver* aPrecheckExitObserver,TDes& aPath,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        

       /**
        * Runs the dialog to select a folder.
        *
        * @param aPath Initial folder path in dialog. Also filled in with 
        *              user's selection if they OK the dialog
        * @param aTitle Dialog title
        * @param aFlags Flags to control the operation of the dialog
        * @return <code>ETrue</code> if the user OKs a selection, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(TDes& aPath,const TDesC& aTitle,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);

       /**
        * Runs the dialog to select a folder.
        *
        * @param aPath Initial folder path in dialog. Also filled in with 
        *              user's selection if they OK the dialog
        * @param aTitleRid Dialog title resource
        * @param aFlags Flags to control the operation of the dialog
        * @return <code>ETrue</code> if the user OKs a selection, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(TDes& aPath,TInt aTitleRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        
    // Methods from base classes
        /** @internal */
        void GetHelpContext(TCoeHelpContext& aContext) const;

    private: //Methods

        ~CCknTargetFolderDialog();
        IMPORT_C static TBool RunLD(TDes& aPath,TTargetDialogType aDialogType,TUint aFlags,TInt aTitleRid=0);
        IMPORT_C static TBool RunLD(MCknTargetFolderDialogObserver* aPrecheckExitObserver,TDes& aPath,TTargetDialogType aDialogType,TUint aFlags,TInt aTitleRid=0);
        IMPORT_C static TBool RunLD(TDes& aPath,const TDesC& aTitle,TUint aFlags);
        static TBool RunLD(TDes& aPath,TTargetDialogType aDialogType,TUint aFlags,const TDesC& aTitle,MCknDialogObserver* aPrecheckExitObserver=NULL);
        CCknTargetFolderDialog(TDes& aPath,TInt aTitleRid,TUint aFlags,MCknDialogObserver* aPrecheckExitObserver=NULL);
        void SetTitleTextL(const TDesC& aTitle);
        void CreateNewFolderL();
        void InitialiseCurrentListBoxL();
        void SetCurrentListBoxToPageL(TInt aPageId);
        void UpdateCurrentListBoxL();
        void ActivateCurrentPageL();
        void DisplayNoCardsLabelL(TBool aDrawNow=ETrue);
        void RemoveNoCardsLabel();
        static TInt GetResourceForVisibleTabsL(TUint aFlags, TTargetDialogType aDialogType);
        // from CEikDialog/CEikForm/CCoeControl
        TBool OkToExitL(TInt aButtonId);
        void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);
        void HandleControlStateChangeL(TInt aControlId);
        void PreLayoutDynInitL();
        void PostLayoutDynInitL();
        void SetInitialCurrentLine();
        // from CCknUpdatingFileDialogBase
        void DoUpdateTimerCallBackL();
        void HandleCorruptOrMissingDiskL();
        // from MListBoxEditorObserver
        TKeyResponse HandleListBoxEditorEventL(MEikListBoxEditor* aListBoxEditor, const TKeyEvent& aKeyEvent);
        void SetButtonDimmedStatesL();
        // from CEikDialog
        void PageChangedL(TInt aPageId);
        
    public:
        // Set Expand/Contract CBA, public because it is used by TTargetFolderItemObserver
        /** @internal */
        void SetExpandedCbaL();

    private:     // Data

        TDes& iPath;
        TInt iTitleRid;
        TInt iButtonsRid;
        TUint iFlags;
        CDirectoryTreeListBoxModel* iDirTreeModel;
        CEikDirectoryTreeListBox* iDirTreeListBox;
        HBufC* iTitleText;
        HBufC* iCollapseText;
        HBufC* iExpandText;
        CPeriodic* iProgressDelayTimer;
        TTargetFolderItemObserver iItemObserver;
        MCknDialogObserver* iPrecheckExitObserver;
    };

inline TBool CCknTargetFolderDialog::RunSelectFolderDlgLD(TDes& aPath,TUint aFlags)
    {
    return RunLD(aPath,ESelectDialog,aFlags);
    }

inline TBool CCknTargetFolderDialog::RunCopyDlgLD(TDes& aPath,TUint aFlags)
    {
    return RunLD(aPath,ECopyDialog,aFlags);
    }

inline TBool CCknTargetFolderDialog::RunMoveDlgLD(TDes& aPath,TUint aFlags)
    {
    return RunLD(aPath,EMoveDialog,aFlags);
    }

inline TBool CCknTargetFolderDialog::RunMoveDlgLD(MCknTargetFolderDialogObserver* aPrecheckExitObserver,TDes& aPath,TUint aFlags)
    {
    return RunLD(aPrecheckExitObserver,aPath,EMoveDialog,aFlags);
    }

inline TBool CCknTargetFolderDialog::RunDlgLD(TDes& aPath,const TDesC& aTitle,TUint aFlags)
    {
    return RunLD(aPath,aTitle,aFlags);
    }

inline TBool CCknTargetFolderDialog::RunDlgLD(TDes& aPath,TInt aTitleRid,TUint aFlags)
    {
    return RunLD(aPath,EUserDialog,aFlags,aTitleRid);
    }

#endif      // CKNDGTRG_H   
            
// End of File
