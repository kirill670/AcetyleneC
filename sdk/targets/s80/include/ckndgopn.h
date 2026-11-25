/**
* ==============================================================================
*  Name        : ckndgopn.h
*  Part of     : CKON
*  Interface   : Object Dialog API
*  Description : Dialogs to open a file and insert an existing file, plus dialog observers for open file dialog and select object dialog.
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

#ifndef CKNDGOPN_H
#define CKNDGOPN_H


// INCLUDES
#include "Ckndgfob.h"
#include <EikDclbm.h>
#include <ApgCli.h>
#include <CknObjectType.h>


// CLASS DECLARATIONS

/**
 * The <code>MCknOpenFileDialogObserver</code> class can be queried to decide 
 * whether to show a file in an Open File dialog.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class MCknOpenFileDialogObserver
    {

    public:

    // New methods
        
       /**
        * Method called by the Open File dialog to find out whether to show a 
        * file in the dialog's list.
        *
        * @param aParse File to check
        * @param aType UID of file
        * @param aDataType Data type (MIME type) of file
        * @return <code>ETrue</code> if the file is to be shown in the dialog, 
        *         <code>EFalse</code> if it is not
        * @remarks
        * @see
        */
        virtual TBool ShowFileInFileListL(const TParsePtrC& aParse,const TUidType& aType,const TDataType& aDataType)=0;

    };

/**
 * The <code>MCknSelectObjectDialogObserver</code> class can be queried to 
 * decide whether to allow an object in an Select Object dialog.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class MCknSelectObjectDialogObserver : public MCknDialogObserver
    {

    public:

    // New methods

       /**
        * Implementing this method gives the caller of a Select Object dialog 
        * the opportunity to perform any further checks on the suitability of 
        * the selected file, and to generate an appropriate infoprint.
        *
        * @param aPath The selected file to be checked
        * @return <code>ETrue</code> if the file is suitable, to close the 
        *         dialog and continue. <code>EFalse</code> if the file is not 
        *         suitable, to keep the dialog open
        * @remarks
        * @see
        */
        IMPORT_C virtual TBool IsOkToExitL(const TDesC& aPath);
        
    private: //Methods

        IMPORT_C virtual void MCknSelectObjectDialogObserver_Reserved_1();
        IMPORT_C virtual void MCknSelectObjectDialogObserver_Reserved_2();

    };

/**
 * The <code>CCknOpenFileDialog</code> class implements the Select Object
 * dialog, WID-Dia003.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknOpenFileDialog : public CCknFileListDialogBase, public MDirContentsListBoxFilter
    {

    private:  // Declarations

        enum
            {
            EUserFlags=0xff,
            EImportFileDialog=0x100,
            ESourceFileDialog=0x200,
            EFilterFiles=0x400,
            ESelectObjectDialog=0x800,
            ESelectEmbeddableObjectDialog=0x1000,
            // 0x2000 is reserved for the base clase (CCknFileListDialogBase)

            // Series90 1.1
            // Dialogs
            EMoveToFolderDialog = 0x4000,
            ESelectFolderDialog = 0x8000,
            // Dialog flags
            EShowFoldersOnly = 0x10000,
            EDisallowNewFolder = 0x20000
            // 0x40000 is reserved for the base class (CCknFileListDialogBase)
            };

    public:


       /**
        * Select Object dialog. Title is supplied by the user as a descriptor.
        *
        * @param aPath The path to display initially; if zero length or an 
        *              invalid path, then the default folder is used. Also 
        *              used to return the selected file
        * @param aTitle Dialog title
        * @param aFilterUid UID to filter the list presented to the user; if 
        *                   <code>KNullUid</code>, no filtering is performed
        * @param aFlags Flags from <code>CCknFileListDialogBase</code>
        * @param aNoFiles Message to use if no objects are found; if 
        *                 <code>KNullDesC</code>, a default is used
        * @param aPrecheckExitObserver Class to query when user tries to 
        *                              select an object, to check it's OK
        * @return <code>ETrue</code> if the the user selected the dialog, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks
        * @see
        */
        inline static TBool RunSelectObjectDlgLD(TDes& aPath,
                                                 const TDesC& aTitle,
                                                 TUid aFilterUid=KNullUid,
                                                 TUint aFlags=CCknFileListDialogBase::EShowAllDrives, 
                                                 const TDesC& aNoFiles=KNullDesC,
                                                 MCknSelectObjectDialogObserver* aPrecheckExitObserver=NULL);

       /**
        * Select Object dialog. Title is supplied by the user as a resource ID.
        *
        * @param aPath The path to display initially; if zero length or an 
        *              invalid path, then the default folder is used. Also 
        *              used to return the selected file
        * @param aTitle Dialog title resource
        * @param aFilterUid UID to filter the list presented to the user; if 
        *                   <code>KNullUid</code>, no filtering is performed
        * @param aFlags Flags from <code>CCknFileListDialogBase</code>
        * @param aNoFilesRid Message resource to use if no objects are found; 
        *                    if 0, a default is used
        * @param aPrecheckExitObserver Class to query when the user tries to 
        *                              select an object, to check it's OK
        * @return <code>ETrue</code> if the user selected OK, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks
        * @see
        */
        inline static TBool RunSelectObjectDlgLD(TDes& aPath,
                                                 TInt aTitle,
                                                 TUid aFilterUid=KNullUid,
                                                 TUint aFlags=CCknFileListDialogBase::EShowAllDrives, 
                                                 TInt aNoFilesRid=0,
                                                 MCknSelectObjectDialogObserver* aPrecheckExitObserver=NULL);

       /**
        * Select Object dialog. Title and other text resources are derived 
        * from the specified object type.
        *
        * @param aPath The path to display initially; if zero length or an 
        *              invalid path, then the default folder is used. Also 
        *              used to return the selected file
        * @param aObjectType Type of object to select; filtering is set to 
        *                    show only files that match this type
        * @param aFlags Flags from <code>CCknFileListDialogBase</code>
        * @param aPrecheckExitObserver Class to query when the user tries to 
        *                              select an object, to check it's OK
        * @return <code>ETrue</code> if the user selected OK, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks
        * @see
        */
        inline static TBool RunSelectObjectDlgLD(TDes& aPath,
                                                 TCknObjectType aObjectType,
                                                 TUint aFlags=CCknFileListDialogBase::EShowAllDrives,
                                                 MCknSelectObjectDialogObserver* aPrecheckExitObserver=NULL);

       /**
        * Select Embeddable Object dialog. Title is supplied by the user as a 
        * descriptor. Works in the same way as Select Object dialog, but shows 
        * only embeddable files.
        *
        * @param aPath The path to display initially; if zero length or an 
        *              invalid path, then the default folder is used. Also 
        *              used to return the selected file
        * @param aTitle Dialog title
        * @param aFilterUid UID to filter the list presented to the user; if 
        *                   <code>KNullUid</code>, no filtering is performed
        * @param aFlags Flags from <code>CCknFileListDialogBase</code>
        * @param aNoFiles Message to use if no objects are found; if 
        *                 <code>KNullDesC</code>, a default is used
        * @param aPrecheckExitObserver Class to query when the user tries to 
        *                              select an object, to check it's OK
        * @return <code>ETrue</code> if the user selected OK,
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks
        * @see
        */
        inline static TBool RunSelectEmbeddableObjectDlgLD(TDes& aPath,
                                                           const TDesC& aTitle,
                                                           TUid aFilterUid=KNullUid,
                                                           TUint aFlags=CCknFileListDialogBase::EShowAllDrives, 
                                                           const TDesC& aNoFiles=KNullDesC,
                                                           MCknSelectObjectDialogObserver* aPrecheckExitObserver=NULL);

       /**
        * Select Embeddable Object dialog. Title is supplied by the user as a 
        * resource ID. Works in the same way as Select Object dialog but shows 
        * only embeddable files.
        *
        * @param aPath The path to display initially; if zero length or an 
        *              invalid path, then the default folder is used. Also 
        *              used to return the selected file
        * @param aTitle Dialog title resource
        * @param aFilterUid UID to filter the list presented to the user; if 
        *                   <code>KNullUid</code>, no filtering is performed
        * @param aFlags Flags from <code>CCknFileListDialogBase</code>
        * @param aNoFilesRid Message resource to use if no objects are found; 
        *                    if 0, a default is used
        * @param aPrecheckExitObserver Class to query when the user tries to 
        *                              select an object, to check it's OK
        * @return <code>ETrue</code> if the user selected OK,
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks
        * @see
        */
        inline static TBool RunSelectEmbeddableObjectDlgLD(TDes& aPath,
                                                           const TInt aTitle,
                                                           TUid aFilterUid=KNullUid,
                                                           TUint aFlags=CCknFileListDialogBase::EShowAllDrives, 
                                                           TInt aNoFilesRid=0,
                                                           MCknSelectObjectDialogObserver* aPrecheckExitObserver=NULL);

       /**
        * Browse dialog. Title is supplied by the user as a descriptor.
        *
        * @param aPath The path to display initially; if zero length or an 
        *              invalid path, then the default folder is used. Also 
        *              used to return the selected file
        * @param aTitle Dialog title
        * @param aFilterUid UID to filter the list presented to the user; if 
        *                   <code>KNullUid</code>, no filtering is performed 
        * @param aFlags Flags from <code>CCknFileListDialogBase</code>
        * @param aNoFiles Message to use if no objects are found; if 
        *                 <code>KNullDesC</code>, a default is used
        * @param aPrecheckExitObserver Class to query when the user tries to 
        *                              select an object, to check it's OK
        * @return <code>ETrue</code> if the user selected OK, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks Internal, this method is used by the Browse dialog
        * @see  <code>CCknBrowseDialog</code> (CknBrowseDialog.h)
        */
        inline static TBool RunBrowseDlgLD(TDes& aPath,
                                           const TDesC& aTitle,
                                           TUid aFilterUid = KNullUid,
                                           TUint aFlags = CCknFileListDialogBase::EShowAllDrives,
                                           const TDesC& aNoFiles = KNullDesC,
                                           MCknDialogObserver* aPrecheckExitObserver = NULL);

       /**
        * Change location dialog. Title is supplied by the user as a 
        * descriptor.
        *
        * @param aPath The path to display initially; if zero length or an 
        *              invalid path, then the default folder is used. Also 
        *              used to return the selected file
        * @param aTitle Dialog title
        * @param aFlags Flags from <code>CCknFileListDialogBase</code>
        * @param aPrecheckExitObserver Class to query when the user tries to 
        *                              select an object, to check it's OK
        * @return <code>ETrue</code> if the user selected OK, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks Internal, this method is used by the Change Location dialog
        * @see <code>CCknChangeLocationDialog</code> (CknChangeLocationDialog.h)
        */
        inline static TBool RunChangeLocationDlgLD(TDes& aPath,
                                                   const TDesC& aTitle,
                                                   TUint aFlags = CCknFileListDialogBase::EShowAllDrives,
                                                   MCknDialogObserver* aPrecheckExitObserver = NULL);

       /**
        * Move To dialog. Title is supplied by the user as a descriptor.
        *
        * @param aPath The path to display initially; if zero length or an 
        *              invalid path, then the default folder is used. Also 
        *              used to return the selected file
        * @param aTitle Dialog title
        * @param aFlags Flags from <code>CCknFileListDialogBase</code>
        * @param aPrecheckExitObserver Class to query when the user tries to 
        *                              select an object, to check it's OK
        * @return <code>ETrue</code> if the user selected OK, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks Internal, this method is used by the Move To dialog
        * @see <code>CCknMoveToDialog</code> (CknMoveToDialog.h)
        */
        inline static TBool RunMoveToDlgLD(TDes& aPath,
                                           const TDesC& aTitle,
                                           TUint aFlags = CCknFileListDialogBase::EShowAllDrives,
                                           MCknDialogObserver* aPrecheckExitObserver = NULL);

       /**
        * Select Folder dialog. Title is supplied by the user as a descriptor. 
        *
        * @param aPath The path to display initially; if zero length or an 
        *              invalid path, then the default folder is used. Also 
        *              used to return the selected file
        * @param aTitle Dialog title
        * @param aFlags Flags from <code>CCknFileListDialogBase</code>
        * @param aPrecheckExitObserver Class to query when the user tries to 
        *                              select an object, to check it's OK
        * @return <code>ETrue</code> if the user selected OK, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks Internal, this method is used by the Select Folder dialog
        * @see <code>CCknSelectFolderDialog</code> (CknSelectFolderDialog.h)
        */
        inline static TBool RunSelectFolderDlgLD(TDes& aPath,
                                                 const TDesC& aTitle,
                                                 TUint aFlags = CCknFileListDialogBase::EShowAllDrives,
                                                 MCknDialogObserver* aPrecheckExitObserver = NULL);

       /**
        * Select File dialog. Title is supplied by the user as a descriptor.
        *
        * @param aPath The path to display initially; if zero length or an 
        *              invalid path, then the default folder is used. Also 
        *              used to return the selected file
        * @param aTitle Dialog title
        * @param aFilterUid UID to filter the list presented to the user; if 
        *                   <code>KNullUid</code>, no filtering is performed
        * @param aFlags Flags from <code>CCknFileListDialogBase</code>
        * @param aNoFiles Message to use if no objects are found; if 
        *                 <code>KNullDesC</code>, a default is used
        * @param aPrecheckExitObserver Class to query when the user tries to 
        *                              select an object, to check it's OK
        * @return <code>ETrue</code> if the user selected OK, 
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks Internal, this function is used by the Select File dialog
        * @see  <code>CCknSelectFileDialog</code> (CknSelectFileDialog.h)
        */
        inline static TBool RunSelectFileDlgLD(TDes& aPath,
                                               const TDesC& aTitle,
                                               TUid aFilterUid = KNullUid,
                                               TUint aFlags = CCknFileListDialogBase::EShowAllDrives,
                                               const TDesC& aNoFiles = KNullDesC,
                                               MCknDialogObserver* aPrecheckExitObserver = NULL);
        /** @internal */
        static TBool RunTargetFolderMoveDlgLD(TDes& aPath,
                                              const TDesC& aTitle,
                                              TUint aFlags = CCknFileListDialogBase::EShowAllDrives,
                                              MCknDialogObserver* aPrecheckExitObserver = NULL);
        /** @internal */
        static TBool RunTargetFolderSelectDlgLD(TDes& aPath,
                                                const TDesC& aTitle,
                                                TUint aFlags = CCknFileListDialogBase::EShowAllDrives,
                                                MCknDialogObserver* aPrecheckExitObserver = NULL);

    // Methods from base classes

       /**
        * From CCoeControl. Returns help information about the dialog.
        *
        * @param aContext Filled in with help details
        * @internal
        */
        void GetHelpContext(TCoeHelpContext& aContext) const;

    private: //Methods

        CCknOpenFileDialog(MCknOpenFileDialogObserver* aObserver,TDes& aPath,HBufC* aShowAppFilesText,TUint aFlags,TUid aAppUid,const TDesC* aExt);
        CCknOpenFileDialog(MCknDialogObserver* aObserver,TDes& aPath,TUint aFlags,TUid aAppUid);
        ~CCknOpenFileDialog();
        TInt GetTitleResource(TCknObjectType aObjectType);
        TInt GetNoFilesResource(TCknObjectType aObjectType);
        void UpdateEmbeddableAppListL();
        void CheckDefaultPath();
        IMPORT_C static TBool RunLD(MCknOpenFileDialogObserver* aObserver,TDes& aPath,TInt aTitleRid,const TDesC& aShowAppFilesText,TUint aFlags,TUid aAppUid,const TDesC* aExt);
        IMPORT_C static TBool RunLD(MCknOpenFileDialogObserver* aObserver,TDes& aPath,TInt aTitleRid,TInt aShowAppFilesRid,TUint aFlags,TUid aAppUid,const TDesC* aExt);
        IMPORT_C static TBool RunLD(MCknOpenFileDialogObserver* aObserver,TDes& aPath,const TDesC& aTitle,TInt aShowAppFilesRid,TUint aFlags,TUid aAppUid,const TDesC* aExt);
        IMPORT_C static TBool RunLD(MCknOpenFileDialogObserver* aObserver,TDes& aPath,const TDesC& aTitle,const TDesC& aShowAppFilesText,TUint aFlags,TUid aAppUid,const TDesC* aExt);
        IMPORT_C static TBool RunLD(MCknOpenFileDialogObserver* aObserver,TDes& aPath,TUint aFlags);
        IMPORT_C static TBool RunLD(TDes& aPath,TInt aTitleRid,TUint aFlags,TUid aAppUid,TInt aNoFilesRid,MCknSelectObjectDialogObserver* aPrecheckExitObserver);
        IMPORT_C static TBool RunLD(TDes& aPath,const TDesC& aTitle,TUint aFlags,TUid aAppUid,const TDesC& aNoFiles,MCknSelectObjectDialogObserver* aPrecheckExitObserver);
        IMPORT_C static TBool RunLD(TDes& aPath,TCknObjectType aObjectType,TUint aFlags,MCknSelectObjectDialogObserver* aPrecheckExitObserver);
        // from MDirContentsListBoxFilter
        TBool RemoveFileFromDirContentsListL(const TDesC& aPath,const TEntry& aEntry);
        // from CCknUpdatingFileDialogBase
        void UpdateThirdButtonTextL();
        void UpdateTitleL();
        TBool OkToExitL(TInt aButtonId);
        void PostLayoutDynInitL();
        void PreLayoutDynInitL();
        void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);
        void HandleControlStateChangeL(TInt aControl);
        void DisplayNoCardsLabelL();
        void RemoveNoCardsLabel();
        // from CCknUpdatingFileDialogBase
        void DoUpdateTimerCallBackL();
        // from CEikDialog
        virtual void HandleInteractionRefused(TInt aControlId);

        // Series90 1.1
        static TBool NewDialogsRunLD(TDes& aPath,TInt aTitleRid,TUint aFlags,TUid aAppUid,TInt aNoFilesRid,MCknDialogObserver* aPrecheckExitObserver);
        static TBool NewDialogsRunLD(TDes& aPath,const TDesC& aTitle,TUint aFlags,TUid aAppUid,const TDesC& aNoFiles,MCknDialogObserver* aPrecheckExitObserver);
        static TBool NewDialogsRunLD(TDes& aPath,TCknObjectType aObjectType,TUint aFlags,MCknDialogObserver* aPrecheckExitObserver);

        void NewDialogsPostLayoutDynInitL();
        void NewDialogsPreLayoutDynInitL();
        void NewDialogsHandleInteractionRefused(TInt aControlId);
        void NewDialogsHandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);
        TBool NewDialogsOkToExitL(TInt aButtonId);
        void NewDialogsHandleControlStateChangeL(TInt aControl);
        void NewDialogsDoUpdateTimerCallBackL();
        void NewDialogsDisplayNoCardsLabelL();
        void NewDialogsRemoveNoCardsLabel();

        static void ConvertTargetFlagsToOpenFlags(TUint& aFlags);

        TPath DefaultPath() const;
        TPath MMCDefaultPath() const;
        TPath CurrentPath() const;

        void SetInitialCurrentLine();
        void ActivateCurrentPageL();
        void PageChangedL(TInt aPageId);

        void SetButtonsDimmedStateWhenPageChanged();
        void SetButtonsDimmedStateWhenListBoxVisible();
        void SetButtonsDimmedStateWhenListBoxNotVisible();
        void SetOkButtonDimmedState();
        void SetUpButtonDimmedState();

        void CreateNewFolderL();

        void DisplayTopOfDriveMsgL();

        TBool MMCIsPresent() const;

        // from CCoeControl
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

    private:     // Data

        MCknOpenFileDialogObserver* iObserver;
        MCknDialogObserver* iPrecheckExitObserver;
        HBufC* iShowAppFilesText;
        HBufC* iShowAllFilesText;
        TBool iShowingAllFiles;
        RApaLsSession iApaSession;
        const TDesC* iExtension;
        TFileName iTempFileName;
        CArrayFixFlat<TDataTypeWithPriority>* iDataTypes;
        CArrayFix<TUid>* iEmbeddableAppList;
        HBufC* iNoFilesText;
        TCknObjectType iObjectType;

        // Series90 1.1
        CEikDirContentsListBox* iMMCDirContentsListBox;
        CEikDirContentsListBox* iCurrentListBox;

        TPath iCurrentDefaultPath;

    public:
        /** @deprecated */
        inline static TBool RunDlgLD(TDes& aPath,const TDesC& aShowAppFilesText,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid,const TDesC* aExt=NULL);
        /** @deprecated */
        inline static TBool RunDlgLD(TDes& aPath,TInt aShowAppFilesRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid,const TDesC* aExt=NULL);
        /** @deprecated */
        inline static TBool RunDlgLD(TDes& aPath,TUid aFilterUid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,const TDesC* aExt=NULL);
        /** @deprecated */
        inline static TBool RunDlgLD(TDes& aPath,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        /** @deprecated */
        inline static TBool RunDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,const TDesC& aShowAppFilesText,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        /** @deprecated */
        inline static TBool RunDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,TInt aShowAppFilesRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        /** @deprecated */
        inline static TBool RunImportDlgLD(TDes& aPath,const TDesC& aShowAppFilesText,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid,const TDesC* aExt=NULL);
        /** @deprecated */
        inline static TBool RunImportDlgLD(TDes& aPath,TInt aShowAppFilesRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid,const TDesC* aExt=NULL);
        /** @deprecated */
        inline static TBool RunImportDlgLD(TDes& aPath,TUid aFilterUid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,const TDesC* aExt=NULL);
        /** @deprecated */
        inline static TBool RunImportDlgLD(TDes& aPath,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        /** @deprecated */
        inline static TBool RunImportDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,const TDesC& aShowAppFilesText,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        /** @deprecated */
        inline static TBool RunImportDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,TInt aShowAppFilesRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        /** @deprecated */
        inline static TBool RunSourceDlgLD(TDes& aPath,const TDesC& aTitle,const TDesC& aShowAppFilesText,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid,const TDesC* aExt=NULL);
        /** @deprecated */
        inline static TBool RunSourceDlgLD(TDes& aPath,const TDesC& aTitle,TInt aShowAppFilesRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid,const TDesC* aExt=NULL);
        /** @deprecated */
        inline static TBool RunSourceDlgLD(TDes& aPath,TUid aFilterUid,const TDesC& aTitle,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,const TDesC* aExt=NULL);
        /** @deprecated */
        inline static TBool RunSourceDlgLD(TDes& aPath,const TDesC& aTitle,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        /** @deprecated */
        inline static TBool RunSourceDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,const TDesC& aTitle,const TDesC& aShowAppFilesText,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        /** @deprecated */
        inline static TBool RunSourceDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,const TDesC& aTitle,TInt aShowAppFilesRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        /** @deprecated */
        inline static TBool RunSourceDlgLD(TDes& aPath,TInt aTitleRid,const TDesC& aShowAppFilesText,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid,const TDesC* aExt=NULL);
        /** @deprecated */
        inline static TBool RunSourceDlgLD(TDes& aPath,TInt aTitleRid,TInt aShowAppFilesRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid,const TDesC* aExt=NULL);
        /** @deprecated */
        inline static TBool RunSourceDlgLD(TDes& aPath,TUid aFilterUid,TInt aTitleRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,const TDesC* aExt=NULL);
        /** @deprecated */
        inline static TBool RunSourceDlgLD(TDes& aPath,TInt aTitleRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        /** @deprecated */
        inline static TBool RunSourceDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,TInt aTitleRid,const TDesC& aShowAppFilesText,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
        /** @deprecated */
        inline static TBool RunSourceDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,TInt aTitleRid,TInt aShowAppFilesRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);
    };

//
// open file dialog
//
inline TBool CCknOpenFileDialog::RunDlgLD(TDes& aPath,const TDesC& aShowAppFilesText,TUint aFlags,TUid aAppUid,const TDesC* aExt)
    {
    return RunLD(NULL,aPath,NULL,aShowAppFilesText,aFlags|EUseOldDialogs,aAppUid,aExt);
    }

inline TBool CCknOpenFileDialog::RunDlgLD(TDes& aPath,TInt aShowAppFilesRid,TUint aFlags,TUid aAppUid,const TDesC* aExt)
    {
    return RunLD(NULL,aPath,NULL,aShowAppFilesRid,aFlags|EUseOldDialogs,aAppUid,aExt);
    }

inline TBool CCknOpenFileDialog::RunDlgLD(TDes& aPath,TUid aFilterUid,TUint aFlags,const TDesC* aExt)
    {
    return RunLD(NULL,aPath,NULL,NULL,(aFlags&EUserFlags)|EUseOldDialogs|EFilterFiles,aFilterUid,aExt);
    }

inline TBool CCknOpenFileDialog::RunDlgLD(TDes& aPath,TUint aFlags)
    {
    return RunLD(NULL,aPath,aFlags|EUseOldDialogs);
    }

inline TBool CCknOpenFileDialog::RunDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,const TDesC& aShowAppFilesText,TUint aFlags)
    {
    return RunLD(aObserver,aPath,NULL,aShowAppFilesText,aFlags|EUseOldDialogs,KNullUid,NULL);
    }

inline TBool CCknOpenFileDialog::RunDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,TInt aShowAppFilesRid,TUint aFlags)
    {
    return RunLD(aObserver,aPath,NULL,aShowAppFilesRid,aFlags|EUseOldDialogs,KNullUid,NULL);
    }
//
// Import File dialog
//
inline TBool CCknOpenFileDialog::RunImportDlgLD(TDes& aPath,const TDesC& aShowAppFilesText,TUint aFlags,TUid aAppUid,const TDesC* aExt)
    {
    return RunLD(NULL,aPath,NULL,aShowAppFilesText,(aFlags&EUserFlags)|EUseOldDialogs|EImportFileDialog,aAppUid,aExt);
    }

inline TBool CCknOpenFileDialog::RunImportDlgLD(TDes& aPath,TInt aShowAppFilesRid,TUint aFlags,TUid aAppUid,const TDesC* aExt)
    {
    return RunLD(NULL,aPath,NULL,aShowAppFilesRid,(aFlags&EUserFlags)|EUseOldDialogs|EImportFileDialog,aAppUid,aExt);
    }

inline TBool CCknOpenFileDialog::RunImportDlgLD(TDes& aPath,TUid aFilterUid,TUint aFlags,const TDesC* aExt)
    {
    return RunLD(NULL,aPath,NULL,NULL,(aFlags&EUserFlags)|EUseOldDialogs|EImportFileDialog|EFilterFiles,aFilterUid,aExt);
    }

inline TBool CCknOpenFileDialog::RunImportDlgLD(TDes& aPath,TUint aFlags)
    {
    return RunLD(NULL,aPath,(aFlags&EUserFlags)|EUseOldDialogs|EImportFileDialog);
    }

inline TBool CCknOpenFileDialog::RunImportDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,const TDesC& aShowAppFilesText,TUint aFlags)
    {
    return RunLD(aObserver,aPath,NULL,aShowAppFilesText,(aFlags&EUserFlags)|EUseOldDialogs|EImportFileDialog,KNullUid,NULL);
    }

inline TBool CCknOpenFileDialog::RunImportDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,TInt aShowAppFilesRid,TUint aFlags)
    {
    return RunLD(aObserver,aPath,NULL,aShowAppFilesRid,(aFlags&EUserFlags)|EUseOldDialogs|EImportFileDialog,KNullUid,NULL);
    }
//
// Source File dialog
//
inline TBool CCknOpenFileDialog::RunSourceDlgLD(TDes& aPath,const TDesC& aTitle,const TDesC& aShowAppFilesText,TUint aFlags,TUid aAppUid,const TDesC* aExt)
    {   
    return RunLD(NULL,aPath,aTitle,aShowAppFilesText,(aFlags&EUserFlags)|EUseOldDialogs|ESourceFileDialog,aAppUid,aExt);
    }

inline TBool CCknOpenFileDialog::RunSourceDlgLD(TDes& aPath,const TDesC& aTitle,TInt aShowAppFilesRid,TUint aFlags,TUid aAppUid,const TDesC* aExt)
    {   
    return RunLD(NULL,aPath,aTitle,aShowAppFilesRid,(aFlags&EUserFlags)|EUseOldDialogs|ESourceFileDialog,aAppUid,aExt);
    }

inline TBool CCknOpenFileDialog::RunSourceDlgLD(TDes& aPath,TUid aFilterUid,const TDesC& aTitle,TUint aFlags,const TDesC* aExt)
    {
    return RunLD(NULL,aPath,aTitle,NULL,(aFlags&EUserFlags)|EUseOldDialogs|ESourceFileDialog|EFilterFiles,aFilterUid,aExt);
    }

inline TBool CCknOpenFileDialog::RunSourceDlgLD(TDes& aPath,const TDesC& aTitle,TUint aFlags)
    {   
    return RunLD(NULL,aPath,aTitle,NULL,(aFlags&EUserFlags)|EUseOldDialogs|ESourceFileDialog,KNullUid,NULL);
    }

inline TBool CCknOpenFileDialog::RunSourceDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,const TDesC& aTitle,const TDesC& aShowAppFilesText,TUint aFlags)
    {
    return RunLD(aObserver,aPath,aTitle,aShowAppFilesText,(aFlags&EUserFlags)|EUseOldDialogs|ESourceFileDialog,KNullUid,NULL);
    }

inline TBool CCknOpenFileDialog::RunSourceDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,const TDesC& aTitle,TInt aShowAppFilesRid,TUint aFlags)
    {
    return RunLD(aObserver,aPath,aTitle,aShowAppFilesRid,(aFlags&EUserFlags)|EUseOldDialogs|ESourceFileDialog,KNullUid,NULL);
    }

inline TBool CCknOpenFileDialog::RunSourceDlgLD(TDes& aPath,TInt aTitleRid,const TDesC& aShowAppFilesText,TUint aFlags,TUid aAppUid,const TDesC* aExt)
    {
    return RunLD(NULL,aPath,aTitleRid,aShowAppFilesText,(aFlags&EUserFlags)|EUseOldDialogs|ESourceFileDialog,aAppUid,aExt);
    }

inline TBool CCknOpenFileDialog::RunSourceDlgLD(TDes& aPath,TInt aTitleRid,TInt aShowAppFilesRid,TUint aFlags,TUid aAppUid,const TDesC* aExt)
    {
    return RunLD(NULL,aPath,aTitleRid,aShowAppFilesRid,(aFlags&EUserFlags)|EUseOldDialogs|ESourceFileDialog,aAppUid,aExt);
    }

inline TBool CCknOpenFileDialog::RunSourceDlgLD(TDes& aPath,TUid aFilterUid,TInt aTitleRid,TUint aFlags,const TDesC* aExt)
    {
    return RunLD(NULL,aPath,aTitleRid,NULL,(aFlags&EUserFlags)|EUseOldDialogs|ESourceFileDialog|EFilterFiles,aFilterUid,aExt);
    }

inline TBool CCknOpenFileDialog::RunSourceDlgLD(TDes& aPath,TInt aTitleRid,TUint aFlags)
    {
    return RunLD(NULL,aPath,aTitleRid,NULL,(aFlags&EUserFlags)|EUseOldDialogs|ESourceFileDialog,KNullUid,NULL);
    }

inline TBool CCknOpenFileDialog::RunSourceDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,TInt aTitleRid,const TDesC& aShowAppFilesText,TUint aFlags)
    {
    return RunLD(aObserver,aPath,aTitleRid,aShowAppFilesText,(aFlags&EUserFlags)|EUseOldDialogs|ESourceFileDialog,KNullUid,NULL);
    }

inline TBool CCknOpenFileDialog::RunSourceDlgLD(TDes& aPath,MCknOpenFileDialogObserver* aObserver,TInt aTitleRid,TInt aShowAppFilesRid,TUint aFlags)
    {
    return RunLD(aObserver,aPath,aTitleRid,aShowAppFilesRid,(aFlags&EUserFlags)|EUseOldDialogs|ESourceFileDialog,KNullUid,NULL);
    }
//
// Select Object dialog
//
inline TBool CCknOpenFileDialog::RunSelectObjectDlgLD(TDes& aPath,const TDesC& aTitle,TUid aFilterUid,TUint aFlags,const TDesC& aNoFiles,MCknSelectObjectDialogObserver* aPrecheckExitObserver)
    {
    return RunLD(aPath,aTitle,(aFlags&(EUserFlags|EUseOldDialogs))|ESelectObjectDialog|EShowBothFilesAndFolders,aFilterUid,aNoFiles,aPrecheckExitObserver);
    }

inline TBool CCknOpenFileDialog::RunSelectObjectDlgLD(TDes& aPath,TInt aTitle,TUid aFilterUid,TUint aFlags,TInt aNoFilesRid,MCknSelectObjectDialogObserver* aPrecheckExitObserver)
    {
    return RunLD(aPath,aTitle,(aFlags&(EUserFlags|EUseOldDialogs))|ESelectObjectDialog|EShowBothFilesAndFolders,aFilterUid,aNoFilesRid,aPrecheckExitObserver);
    }

inline TBool CCknOpenFileDialog::RunSelectObjectDlgLD(TDes& aPath,TCknObjectType aObjectType,TUint aFlags,MCknSelectObjectDialogObserver* aPrecheckExitObserver)
    {
    return RunLD(aPath,aObjectType,(aFlags&(EUserFlags|EUseOldDialogs))|ESelectObjectDialog|EShowBothFilesAndFolders,aPrecheckExitObserver);
    }

//
// Select Embeddable Object dialog
//
inline TBool CCknOpenFileDialog::RunSelectEmbeddableObjectDlgLD(TDes& aPath,const TDesC& aTitle,TUid aFilterUid,TUint aFlags,const TDesC& aNoFiles,MCknSelectObjectDialogObserver* aPrecheckExitObserver)
    {
    return RunLD(aPath,aTitle,(aFlags&(EUserFlags|EUseOldDialogs))|ESelectEmbeddableObjectDialog|EShowBothFilesAndFolders,aFilterUid,aNoFiles,aPrecheckExitObserver);
    }

inline TBool CCknOpenFileDialog::RunSelectEmbeddableObjectDlgLD(TDes& aPath,TInt aTitle,TUid aFilterUid,TUint aFlags,TInt aNoFilesRid,MCknSelectObjectDialogObserver* aPrecheckExitObserver)
    {
    return RunLD(aPath,aTitle,(aFlags&(EUserFlags|EUseOldDialogs))|ESelectEmbeddableObjectDialog|EShowBothFilesAndFolders,aFilterUid,aNoFilesRid,aPrecheckExitObserver);
    }

//
// Browse dialog
//
inline TBool CCknOpenFileDialog::RunBrowseDlgLD(TDes& aPath, const TDesC& aTitle, TUid aFilterUid, TUint aFlags, const TDesC& aNoFiles, MCknDialogObserver* aPrecheckExitObserver)
    {
    return NewDialogsRunLD(aPath, aTitle, (aFlags&EUserFlags)|ESelectObjectDialog|EShowBothFilesAndFolders|EDisallowNewFolder, aFilterUid, aNoFiles, aPrecheckExitObserver);
    }

//
// Change Location dialog
//
inline TBool CCknOpenFileDialog::RunChangeLocationDlgLD(TDes& aPath, const TDesC& aTitle, TUint aFlags, MCknDialogObserver* aPrecheckExitObserver)
    {
    return NewDialogsRunLD(aPath, aTitle, (aFlags&EUserFlags)|ESelectFolderDialog|EShowFoldersOnly, KNullUid, KNullDesC, aPrecheckExitObserver);
    }

//
// Move To dialog
//
inline TBool CCknOpenFileDialog::RunMoveToDlgLD(TDes& aPath, const TDesC& aTitle, TUint aFlags, MCknDialogObserver* aPrecheckExitObserver)
    {
    return NewDialogsRunLD(aPath, aTitle, (aFlags&EUserFlags)|EMoveToFolderDialog|EShowFoldersOnly, KNullUid, KNullDesC, aPrecheckExitObserver);
    }

//
// Select Folder dialog
//
inline TBool CCknOpenFileDialog::RunSelectFolderDlgLD(TDes& aPath, const TDesC& aTitle, TUint aFlags, MCknDialogObserver* aPrecheckExitObserver)
    {
    return NewDialogsRunLD(aPath, aTitle, (aFlags&EUserFlags)|ESelectFolderDialog|EShowFoldersOnly|EDisallowNewFolder, KNullUid, KNullDesC, aPrecheckExitObserver);
    }

//
// Select File dialog
//
inline TBool CCknOpenFileDialog::RunSelectFileDlgLD(TDes& aPath, const TDesC& aTitle, TUid aFilterUid, TUint aFlags, const TDesC& aNoFiles, MCknDialogObserver* aPrecheckExitObserver)
    {
    return NewDialogsRunLD(aPath, aTitle, (aFlags&EUserFlags)|ESelectEmbeddableObjectDialog|EShowBothFilesAndFolders|EDisallowNewFolder, aFilterUid, aNoFiles, aPrecheckExitObserver);
    }

/**
 * The <code>CCknInsertExistingFileDialog</code> class implements a dialog to 
 * insert files. Shows embeddable files only.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknInsertExistingFileDialog : public CCknFileListDialogBase, public MDirContentsListBoxFilter
    {

public:

    // New methods

       /**
        * Insert the Embeddable File dialog.
        *
        * @param aPath  The path to display initially. If zero length or an 
        *               invalid path, then the default folder is used. Also 
        *               used to return the selected file
        * @param aFlags Flags from <code>CCknFileListDialogBase</code>
        * @return <code>ETrue</code> if the user selected OK,
        *         <code>EFalse</code> if the dialog is canceled 
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(TDes& aPath,TUint aFlags=CCknFileListDialogBase::EShowAllDrives);

    private: //Methods

        CCknInsertExistingFileDialog(TDes& aPath,TUint aFlags);
        ~CCknInsertExistingFileDialog();
        void UpdateEmbeddableAppListL();
        TBool RemoveFileFromDirContentsListL(const TDesC& aPath,const TEntry& aEntry);
        void UpdateThirdButtonTextL();
        TBool OkToExitL(TInt aButtonId);
        void PreLayoutDynInitL();

    private:     // Data

        RApaLsSession iApaSession;
        CArrayFix<TUid>* iEmbeddableAppList;

    };


#endif      // CKNDGOPN_H   

// End of File
