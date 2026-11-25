/*
* ==============================================================================
*  Name        : ckndgobj.h
*  Part of     : CKON
*  Interface   : Object Dialog API
*  Description : Dialogs for inserting files or fields
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

#ifndef CKNDGOBJ_H
#define CKNDGOBJ_H


// INCLUDES
#include <EikDialg.h>
#include <ApgCli.h>
#include <Gulicon.h>

// FORWARD DECLARATIONS
class CEikEmbeddableAppList;
class CHeaderFooter;
class CEikRichTextEditor;
class MFieldFileNameInfo;
class MFieldNumPagesInfo;


// CLASS DECLARATIONS

/**
* The <code>CCknInsertObjectDialog</code> class provides the Insert Object 
* dialog. This class keeps compatibility with the old eikon Insert Object 
* dialog.
*
* @lib ckndlg.lib
* @since Series90 1.0
*/
class CCknInsertObjectDialog : public CEikDialog, public MDesCArray
    {

    public:

    // New methods
        
        /**
        * Runs the Insert Object dialog with the 'Insert Existing' button 
        * enabled.
        * 
        * @param aList A list of embeddable types
        * @param aChoice Used to return the index of the chosen object from 
        *                the dialog
        * @param aPath The path to use if the user selects the 'Insert Existing'
        *              button and the Select Embeddable Object dialog is opened
        * @param aFlags Flags from <code>CCknFileListDialogBase</code> (used if 
        *               the user selects the 'Insert Existing' button and the 
        *               Select Embeddable Object dialog is opened
        * @return <code>ETrue</code> if the user accepts an object; 
        *         <code>EFalse</code> if the user cancels the dialog
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(CEikEmbeddableAppList* aList,TInt& aChoice,TDes& aPath,TUint aFlags=0);

        /**
        * Runs the Insert Object dialog with the 'Insert Existing' button 
        * disabled.
        *
        * @param aList A list of embeddable types
        * @param aChoice Used to return the index of the chosen object from 
        *                the dialog
        * @return <code>ETrue</code> if the user accepts an object; 
        *         <code>EFalse</code> if the user cancels the dialog
        * @remarks
        * @see
        */
        inline static TBool RunDlgLD(CEikEmbeddableAppList* aList,TInt& aChoice);

    private: //Methods

        IMPORT_C static TBool RunDlgLD(CEikEmbeddableAppList* aList,TInt& aChoice,TDes* aPath,TUint aFlags);
        CCknInsertObjectDialog(CEikEmbeddableAppList* aList,TInt& aChoice,TDes* aPath,TUint aFlags);
        ~CCknInsertObjectDialog();
        TBool OkToExitL(TInt aButtonId);
        void PreLayoutDynInitL();
        void HandleControlStateChangeL(TInt aControlId);
        TInt MdcaCount() const;
        TPtrC MdcaPoint(TInt aIndex) const;

    private:     // Data
        CEikEmbeddableAppList* iList;
        TInt& iChoice;
        TDes* iPath;
        TUint iFlags;
        HBufC* iTextBuffer;
        CArrayPtr<CGulIcon>* iIconArray;

    };

inline TBool CCknInsertObjectDialog::RunDlgLD(CEikEmbeddableAppList* aList,TInt& aChoice,TDes& aPath,TUint aFlags)
    {
    return RunDlgLD(aList,aChoice,&aPath,aFlags);
    }

inline TBool CCknInsertObjectDialog::RunDlgLD(CEikEmbeddableAppList* aList,TInt& aChoice)
    {
    return RunDlgLD(aList,aChoice,NULL,0);
    }

/**
* The <code>CCknInsertFieldDialog</code> class provides the Insert Field 
* dialog. This class inserts a field (current date, current time, page number, 
* number of pages, or document name) into an Edwin control. If the number of 
* pages and the document name fields are to be used, the dialog requires either 
* a <code>CHeaderFooter</code> or both a <code>MFieldFileNameInfo</code> and a
* <code>MFieldNumPagesInfo</code>.
*
* @lib ckndlg.lib
* @since Series90 1.0
*/
class CCknInsertFieldDialog : public CEikDialog, public MDesCArray
    {

    public:  // Declarations

        /**
        * The <code>CCknInsertFieldDialog::TFieldInfo</code> class provides a 
        * data structure for storing field information. This consists of an ID 
        * and text.
        */
        class TFieldInfo
            {
        public:
            /** @internal */
            TFieldInfo() { iFieldText=NULL; };
        public:
            /** @internal */
            TInt iFieldId;
            /** @internal */
            HBufC* iFieldText;
            };

    public:

    // New methods
        
        /**
        * Runs the Insert Field dialog.
        *
        * @param aEdwin The edwin having an object inserted
        * @param aHeaderFooter Information about the document in the edwin
        * @return <code>ETrue</code> if the user accepts an object; 
        *         <code>EFalse</code> if the user cancels the dialog
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(CEikRichTextEditor* aEdwin,const CHeaderFooter* aHeaderFooter=NULL);

        /**
        * Runs the Insert Field dialog.
        *
        * @param aEdwin The edwin having an object inserted
        * @param aFileNameFieldInfo Information about the filename
        * @param aNumPagesFieldInfo Information about the number of pages
        * @return <code>ETrue</code> if the user accepts an object; 
        *         <code>EFalse</code> if the user cancels the dialog
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(CEikRichTextEditor* aEdwin,MFieldFileNameInfo* aFileNameFieldInfo,MFieldNumPagesInfo* aNumPagesFieldInfo);

    // Methods from base classes

        /**
        * Returns help information
        * @internal
        * @param aContext Filled in with help information
        */
        void GetHelpContext(TCoeHelpContext& aContext) const;

    private: //Methods

        CCknInsertFieldDialog(CEikRichTextEditor* aEdwin,MFieldFileNameInfo* aFileNameFieldInfo,MFieldNumPagesInfo* aNumPagesFieldInfo);
        ~CCknInsertFieldDialog();
        TBool OkToExitL(TInt aButtonId);
        void PreLayoutDynInitL();
        TInt MdcaCount() const;
        TPtrC MdcaPoint(TInt aIndex) const;

    private:     // Data

        CEikRichTextEditor* iEdwin;
        MFieldFileNameInfo* iFileNameFieldInfo;
        MFieldNumPagesInfo* iNumPagesFieldInfo;
        CArrayFix<TFieldInfo>* iFieldInfoArray;

    };

#endif      // CKNDGOBJ_H   
            
// End of File
