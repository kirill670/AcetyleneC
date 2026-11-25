/**
* ==============================================================================
*  Name        : ckndgsve.h
*  Part of     : CKON
*  Interface   : Object Dialog API
*  Description : Dialogs for new file and save as
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

#ifndef CKNDGSVE_H
#define CKNDGSVE_H


// INCLUDES
#include "Ckndgfob.h"
#include <EikLbed.h>
#include <ConCnf.h>
#include <ConList.h>

// FORWARD DECLARATIONS

class MCknConversionUi;
class CCknConversionUi;


// CLASS DECLARATIONS

/**
 * The <code>CCknSaveAsFileDialogBase</code> class implements the file dialogs 
 * that can create a new file. Examples are the 'Save As' and 'New File' 
 * dialogs. Base class handles the in-place filename editor, and any file list 
 * updates/browsing.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 * @internal
 */
class CCknSaveAsFileDialogBase : public CCknFileListDialogBase, public MListBoxEditorObserver
    {

    protected:  // Methods

    // New Methods
        
        CCknSaveAsFileDialogBase(TDes& aFileName,TUint aFlags,TUid aNewFileUid);

        TBool OverwriteFileIfAlreadyExistsL();

        void StartEditorL();

    // Methods from base classes

        // from CCoeControl
        void ActivateL();

        // from CEikDialog
        virtual TBool OkToExitL(TInt aButtonId);
        virtual void HandleControlStateChangeL(TInt aControl);
        virtual void PostLayoutDynInitL();

        // from MListBoxEditorObserver
        TKeyResponse HandleListBoxEditorEventL(MEikListBoxEditor* aListBoxEditor, const TKeyEvent& aKeyEvent);

    protected:     // Data

        TFileName iNewDocName;

    };

/**
 * The <code>CCknSaveAsFileDialog</code> class implements the Save As file 
 * dialog. Adds <code>ChangeFormat</code> functionality to the 
 * <code>CCknSaveAsFileDialogBase</code> class.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknSaveAsFileDialog : public CCknSaveAsFileDialogBase
    {

    private:  // Declarations

        enum
            {
            EUserFlags=0xff,
            EExportFileDialog=0x100,
            };

    public:

    // New methods

        //
        // The UID of the file being saved can be passed in or determined by 
        // the dialog
        //

        // with change format functionality
       /**
        * Launches the Save As dialog.
        *
        * @param aFileName The default file name to save the file as 
        * @param aDataType The file type - see <code>TDataType</code>
        * @param aConversionUi The file converter if the file format changes. 
        *                      <code>NULL</code> by default
        * @param aFlags Any combination of flags as defined in 
        *               <code>CCknFileListDialogBase</code>. 
        *               <code>EShowAllDrives</code> by default
        * @param aAppUid The application UID to associate with this file. If 
        *                this is <code>NULL</code>, the current application's 
        *                UID is used. <code>NULL</code> by default 
        * @return <code>ETrue</code> if the dialog runs and is closed 
        *         successfully; <code>EFalse</code> if it is canceled or it 
        *         fails
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(TDes& aFileName,TDataType& aDataType,MCknConversionUi* aConversionUi=NULL,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid);

       /**
        * Launches the Save As dialog.
        *
        * @param aFileName The default file name to save the file as
        * @param aTitleRid The resource ID of the dialog title
        * @param aDataType The file type - see <code>TDataType</code>
        * @param aConversionUi The file converter if the file format changes. 
        *                      <code>NULL</code> by default
        * @param aFlags Any combination of flags as defined in 
        *               <code>CCknFileListDialogBase</code>. 
        *               <code>EShowAllDrives</code> by default
        * @param aAppUid The application UID to associate with this file. If 
        *                this is <code>NULL</code>, the current application's 
        *                UID is used. <code>NULL</code> by default
        * @return <code>ETrue</code> if the dialog runs and is closed 
        *         successfully; <code>EFalse</code> if it is canceled or it 
        *         fails
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(TDes& aFileName,TInt aTitleRid,TDataType& aDataType,MCknConversionUi* aConversionUi=NULL,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid);

       /**
        * Launches the Save As dialog.
        *
        * @param aFileName The default file name to save the file as
        * @param aTitle The test of the dialog title
        * @param aDataType The file type - see <code>TDataType</code>
        * @param aConversionUi The file converter if the file format changes. 
        *                      <code>NULL</code> by default
        * @param aFlags Any combination of flags as defined in 
        *               <code>CCknFileListDialogBase</code>. 
        *               <code>EShowAllDrives</code> by default
        * @param aAppUid The application UID to associate with this file. If 
        *                this is <code>NULL</code>, the current application's 
        *                UID is used. <code>NULL</code> by default
        * @return <code>ETrue</code> if the dialog runs and is closed 
        *         successfully; <code>EFalse</code> if it is canceled or it 
        *         fails
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(TDes& aFileName,const TDesC& aTitle,TDataType& aDataType,MCknConversionUi* aConversionUi=NULL,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid);

       /**
        * Launches the Save As dialog. This dialog does not have the change 
        * format functionality.
        *
        * @param aFileName The default file name to save the file as
        * @param aFlags Any combination of flags as defined in 
        *               <code>CCknFileListDialogBase</code>. 
        *               <code>EShowAllDrives</code> by default
        * @param aAppUid The application UID to associate with this file. If 
        *                this is <code>NULL</code>, the current application's 
        *                UID is used. <code>NULL</code> by default
        * @return <code>ETrue</code> if the dialog runs and is closed 
        *         successfully; <code>EFalse</code> if it is canceled or it 
        *         fails
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(TDes& aFileName,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid);

       /**
        * Launches the Save As dialog. This dialog does not have the change 
        * format functionality.
        *
        * @param aFileName The default file name to save the file as 
        * @param aTitleRid The resource ID of the dialog title
        * @param aFlags Any combination of flags as defined in 
        *               <code>CCknFileListDialogBase</code>. 
        *               <code>EShowAllDrives</code> by default
        * @param aAppUid The application UID to associate with this file. If 
        *                this is <code>NULL</code>, the current application's 
        *                UID is used. <code>NULL</code> by default
        * @return <code>ETrue</code> if the dialog runs and is closed 
        *         successfully; <code>EFalse</code> if it is canceled or it 
        *         fails
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(TDes& aFileName,TInt aTitleRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid);

       /**
        * Launches the Save As dialog. This dialog does not have the change 
        * format functionality.
        *
        * @param aFileName The default file name to save the file as
        * @param aTitle The test of the dialog title
        * @param aFlags Any combination of flags as defined in 
        *               <code>CCknFileListDialogBase</code>.
        *               <code>EShowAllDrives</code> by default
        * @param aAppUid The application UID to associate with this file. If 
        *                this is <code>NULL</code>, the current application's 
        *                UID is used. <code>NULL</code> by default
        * @return <code>ETrue</code> if the dialog runs and is closed 
        *         successfully; <code>EFalse</code> if it is canceled or it 
        *         fails
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(TDes& aFileName,const TDesC& aTitle,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid);

       /**
        * Launches the export dialog.
        *
        * @param aFileName The default file name to export the file as
        * @param aDataType The file type - see <code>TDataType</code>
        * @param aConversionUi The file converter if the file format changes. 
        *                      <code>NULL</code> by default
        * @param aFlags Any combination of flags as defined in 
        *               <code>CCknFileListDialogBase</code>. 
        *               <code>EShowAllDrives</code> by default
        * @param aAppUid The application UID to associate with this file. If 
        *                this is <code>NULL</code>, the current application's 
        *                UID is used. <code>NULL</code> by default
        * @return <code>ETrue</code> if the dialog runs and is closed 
        *         successfully; <code>EFalse</code> if it is canceled or it 
        *         fails
        * @remarks
        * @see
        */
        inline static TBool RunExportDlgLD(TDes& aFileName,TDataType& aDataType,MCknConversionUi* aConversionUi=NULL,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid);

       /**
        * Launches the export dialog. This dialog does not have the change 
        * format functionality.
        *
        * @param aFileName The default file name to export the file as
        * @param aFlags Any combination of flags as defined in 
        *               <code>CCknFileListDialogBase</code>.
        *               <code>EShowAllDrives</code> by default 
        * @param aAppUid The application UID to associate with this file. If 
        *                this is <code>NULL</code>, the current application's 
        *                UID is used. <code>NULL</code> by default
        * @return <code>ETrue</code> if the dialog runs and is closed 
        *         successfully; <code>EFalse</code> if it is canceled or it 
        *         fails
        * @remarks
        * @see
        */
        inline static TBool RunExportDlgLD(TDes& aFileName,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid);

    // Methods from base classes
        /** @internal */
        void GetHelpContext(TCoeHelpContext& aContext) const;

    private: //Methods

        ~CCknSaveAsFileDialog();
        IMPORT_C static TBool RunLD(TDes& aFileName,TInt aTitleRid,TDataType* aDataType,MCknConversionUi* aConversionUi,TUint aFlags,TUid aAppUid);
        IMPORT_C static TBool RunLD(TDes& aFileName,const TDesC& aTitle,TDataType* aDataType,MCknConversionUi* aConversionUi,TUint aFlags,TUid aAppUid);
        CCknSaveAsFileDialog(TDes& aFileName,TDataType* aDataType,MCknConversionUi* aConversionUi,TUint aFlags,TUid aAppUid);
        void UpdateConverterListL();
        void SelectChangeFormatL();
        void SaveFileL();
        // from CCknFileListDialogBase
        void UpdateThirdButtonTextL();
        void UpdateTitleL();
        void FileServerHasChangedL();
        // from  CCknFileListDialogBase
        TBool OkToExitL(TInt aButtonId);
        void PreLayoutDynInitL();

    private:     // Data

        TDataType* iDataType;
        MCknConversionUi* iConversionUi;
        CCnaConverterList* iConverterList;
        CArrayFix<SConverterInfo>* iConverterInfoArray;
        CCknConversionUi* iDlgConversionUi;
        TInt iSaveAsFormatIndex;
        TDataType iDataTypeCopy;

    };

//
// save as dialog
//
inline TBool CCknSaveAsFileDialog::RunDlgLD(TDes& aFileName,TDataType& aDataType,MCknConversionUi* aConversionUi,TUint aFlags,TUid aAppUid)
    {
    return RunLD(aFileName,NULL,&aDataType,aConversionUi,aFlags,aAppUid);
    }

inline TBool CCknSaveAsFileDialog::RunDlgLD(TDes& aFileName,TInt aTitleRid,TDataType& aDataType,MCknConversionUi* aConversionUi,TUint aFlags,TUid aAppUid)
    {
    return RunLD(aFileName,aTitleRid,&aDataType,aConversionUi,aFlags,aAppUid);
    }

inline TBool CCknSaveAsFileDialog::RunDlgLD(TDes& aFileName,const TDesC& aTitle,TDataType& aDataType,MCknConversionUi* aConversionUi,TUint aFlags,TUid aAppUid)
    {
    return RunLD(aFileName,aTitle,&aDataType,aConversionUi,aFlags,aAppUid);
    }

inline TBool CCknSaveAsFileDialog::RunDlgLD(TDes& aFileName,TUint aFlags,TUid aAppUid)
    {
    return RunLD(aFileName,NULL,NULL,NULL,aFlags,aAppUid);
    }

inline TBool CCknSaveAsFileDialog::RunDlgLD(TDes& aFileName,TInt aTitleRid,TUint aFlags,TUid aAppUid)
    {
    return RunLD(aFileName,aTitleRid,NULL,NULL,aFlags,aAppUid);
    }

inline TBool CCknSaveAsFileDialog::RunDlgLD(TDes& aFileName,const TDesC& aTitle,TUint aFlags,TUid aAppUid)
    {
    return RunLD(aFileName,aTitle,NULL,NULL,aFlags,aAppUid);
    }
//
// export dialog
//
inline TBool CCknSaveAsFileDialog::RunExportDlgLD(TDes& aFileName,TDataType& aDataType,MCknConversionUi* aConversionUi,TUint aFlags,TUid aAppUid)
    {
    return RunLD(aFileName,NULL,&aDataType,aConversionUi,(aFlags&EUserFlags)|EExportFileDialog,aAppUid);
    }

inline TBool CCknSaveAsFileDialog::RunExportDlgLD(TDes& aFileName,TUint aFlags,TUid aAppUid)
    {
    return RunLD(aFileName,NULL,NULL,NULL,(aFlags&EUserFlags)|EExportFileDialog,aAppUid);
    }

/**
 * The <code>CCknNewFileDialog</code> class implements the New File dialog. 
 * Simple class derived from <code>CCknSaveAsFileDialogBase</code>, no extra 
 * functionality.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknNewFileDialog : public CCknSaveAsFileDialogBase
    {

    public:

    // New methods
        
       /**
        * Launches the New File dialog.
        *
        * @param aPath The default path in which to create the new file 
        * @param aFlags Any combination of flags as defined in 
        *               <code>CCknFileListDialogBase</code>. 
        *               <code>EShowAllDrives</code> by default
        * @param aAppUid The application UID to associate with this file. If 
        *                this is <code>NULL</code>, the current application's 
        *                UID is used. <code>NULL</code> by default
        * @return <code>ETrue</code> if the dialog runs and is closed 
        *         successfully; <code>EFalse</code> if it is canceled or it 
        *         fails
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(TDes& aPath,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid);

       /**
        * Launches the New File dialog.
        *
        * @param aPath The default path to create the new file in
        * @param aTitleRid The resource ID of the dialog title
        * @param aFlags Any combination of flags as defined in 
        *               <code>CCknFileListDialogBase</code>. 
        *               <code>EShowAllDrives</code> by default
        * @param aAppUid The application UID to associate with this file. If 
        *                this is <code>NULL</code>, the current application's 
        *                UID is used. <code>NULL</code> by default
        * @return <code>ETrue</code> if the dialog runs and is closed 
        *         successfully; <code>EFalse</code> if it is canceled or it 
        *         fails
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(TDes& aPath,TInt aTitleRid,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid);

       /**
        * Launches the New File dialog.
        *
        * @param aPath The default path to create the new file in
        * @param aTitle The text of the dialog title
        * @param aFlags Any combination of flags as defined in 
        *               <code>CCknFileListDialogBase</code>. 
        *               <code>EShowAllDrives</code> by default
        * @param aAppUid The application UID to associate with this file. If 
        *                this is <code>NULL</code>, the current application's 
        *                UID is used. <code>NULL</code> by default
        * @return <code>ETrue</code> if the dialog runs and is closed 
        *         successfully; <code>EFalse</code> if it is canceled or it 
        *         fails
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(TDes& aPath,const TDesC& aTitle,TUint aFlags=CCknFileListDialogBase::EShowAllDrives,TUid aAppUid=KNullUid);

    private: //Methods

        IMPORT_C static TBool RunLD(TDes& aPath,TInt aTitleRid,TUint aFlags,TUid aAppUid);
        IMPORT_C static TBool RunLD(TDes& aPath,const TDesC& aTitle,TUint aFlags,TUid aAppUid);
        CCknNewFileDialog(TDes& aPath,TUint aFlags,TUid aAppUid);
        // from CCknFileListDialogBase
        void UpdateThirdButtonTextL();

    };

inline TBool CCknNewFileDialog::RunDlgLD(TDes& aPath,TUint aFlags,TUid aAppUid)
    {
    return CCknNewFileDialog::RunLD(aPath,NULL,aFlags,aAppUid);
    }

inline TBool CCknNewFileDialog::RunDlgLD(TDes& aPath,TInt aTitleRid,TUint aFlags,TUid aAppUid)
    {
    return CCknNewFileDialog::RunLD(aPath,aTitleRid,aFlags,aAppUid);
    }

inline TBool CCknNewFileDialog::RunDlgLD(TDes& aPath,const TDesC& aTitle,TUint aFlags,TUid aAppUid)
    {
    return CCknNewFileDialog::RunLD(aPath,aTitle,aFlags,aAppUid);
    }

#endif      // CKNDGSVE_H   
            
// End of File
