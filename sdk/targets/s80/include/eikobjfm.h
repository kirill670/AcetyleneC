/*
* ==============================================================================
*  Name        : eikobjfm.h
*  Part of     : CKON
*  Interface   : Format Object Dialog API
*  Description : Format Object Dialog
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


#ifndef EIKOBJFM_H
#define EIKOBJFM_H

// INCLUDES
#include <eikdialg.h>
#include <gdi.h>
#include <apadbase.h>
#include <apgdoor.h>
#include <eikembal.h>

// FORWARD DECLARATIONS
class CEikRichTextEditor;

/**
 * The <code>CEikFormatObjectDialog</code> class specifies the format object 
 * dialog. This class launches a dialog allowing the formatting of an object 
 * embedded in a document to be altered, for example, to allow the user to 
 * specify whether it should be iconic or use a glass door.
 *
 * @lib eikcdlg.lib
 * @since Series90 1.0
 */
class CEikFormatObjectDialog : public CEikDialog
    {
    public: 
        /**
        * The static method to launch the dialog.
        *
        * @param aDoor An embedded document that can be displayed in a user 
        *              interface as an icon or a glass door
        * @param aDoc Used to determine the document's capability
        * @param aDefaultIconSize The default icon size
        * @return <code>ETrue</code> if the dialog closes successfully; 
        *         <code>EFalse</code> if a failure occurred
        * @remarks
        * @see <code>CApaDoor</code> class in apgdoor.h and 
        *      <code>CApaDocument</code> class in apparc.h
        */
    IMPORT_C static TBool RunDlgLD( CApaDoor&       aDoor,
                                    CApaDocument&   aDoc,
                                    const TSize&    aDefaultIconSize);
    private: 
        CEikFormatObjectDialog(CApaDoor& aDoor,CApaDocument& aDoc,const TSize& aDefaultIconSizeInTwips);
    // from CEikDialog
        void PreLayoutDynInitL();
        void HandleControlStateChangeL(TInt aControlId);
        void PrepareForFocusTransitionL();
        TBool OkToExitL(TInt aButtonId);
    private:
        void SetScaleCropControlsL();
        void ResetScaleCropControlsL();
        void UpdateObjectFormat(CApaDoor::TFormat aFormat);
        void SetGlassDoorInfo(const CPicture& aGlassDoor);
    private:
        CApaDoor& iDoor;
        CApaDocument& iDocument;
        CApaDoorBase::TFormat iDoorFormat;
        TInt iGlassDoorScaleFactorWidth;
        TInt iGlassDoorScaleFactorHeight;
        TMargins iGlassDoorCropInTwips;
        TPictureCapability iGlassDoorCapability;
        TSize iOriginalGlassDoorSizeInTwips;
        TSize iIconSizeInTwips;
        TInt iChangedFlag;
    private:
    enum TScaleChangedType
        {
        EPictureScaleWidthChanged       =0x01,
        EPictureScaleHeightChanged      =0x02,
        EPictureDisplayWidthChanged     =0x04,
        EPictureDisplayHeightChanged    =0x08,
        EPictureCropLeftRightChanged    =0x10,
        EPictureCropTopBottomChanged    =0x20
        };

    };


/**
 * The <code>CEikObjectInfoDialog</code> class specifies the object 
 * information dialog. This class brings up a dialog that displays information 
 * about an object embedded in a document.
 *
 * @lib eikcdlg.lib
 * @since Series90 1.0
 */
class CEikObjectInfoDialog : public CEikDialog
    {
    public: 

        /**
        * A static method to launch the dialog.
        *
        * @param aCaption The caption text 
        * @return <code>ETrue</code> if the dialog closes successfully; 
        *         <code>EFalse</code> if a failure occurred
        * @remarks
        * @see
        */
        IMPORT_C static TBool RunDlgLD(const TDesC& aCaption);
    private: 
        CEikObjectInfoDialog(const TDesC& aCaption);
    // from CEikDialog
        void PreLayoutDynInitL();
    private:
        const TDesC& iCaption;
    };


/**
 * The <code>CEikInsertObjectDialog</code> class specifies the insert object 
 * dialog. This class launches a dialog that allows the user to select an 
 * embeddable object to insert into a document.
 *
 * @lib eikcdlg.lib
 * @since Series90 1.0
 */
class CEikInsertObjectDialog : public CEikDialog
    {
    public: 

        /**
        * The static method to launch the dialog.
        *
        * @param aList The list of embeddable types
        * @param aChoice On return, gets the index of the selected object from 
        *                the dialog
        * @return <code>ETrue</code> if the user selects OK to embed an 
        *         object; <code>EFalse</code> otherwise
        * @remarks
        * @see <code>CEikEmbeddableAppList</code> class in eikembal.h
        */
        IMPORT_C static TBool RunDlgLD(CEikEmbeddableAppList* aList,TInt& aChoice);
    private: 
        CEikInsertObjectDialog();
    };


#endif  // EIKOBJFM_H

// End of File
