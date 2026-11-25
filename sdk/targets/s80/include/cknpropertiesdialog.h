/*
* ==============================================================================
*  Name        : cknpropertiesdialog.h
*  Part of     : CKON
*  Interface   : Properties Dialog API
*  Description : The TPropertiesDialogArgumentList class implements a class to contain the arguments
*                passed to CCknPropertiesDialog.
*                The CCknPropertiesDialog class implements the Properties dialog.
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


#ifndef CKNPROPERTIESDIALOG_H
#define CKNPROPERTIESDIALOG_H

// INCLUDES
#include <eikdialg.h>
#include <CknColumnedText.h>
#include <CknObjectType.h>
#include "CknFolderPropertiesReporter.h"

/**
*  The <code>TPropertiesDialogArgumentList</code> class implements a class to 
*  contain the arguments passed to <code>CCknPropertiesDialog</code>. This aims 
*  to proof the API against future changes for <code>CCknPropertiesDialog</code>.
*
*  @lib ckndlg.lib
*  @since Series90 1.0
*/

class TPropertiesDialogArgumentList
    {
    public: 

   /**
    * The object constructor.
    *
    * @param aReadOnlyState Initializes the Read-only checkbox state 
    *                       in a Properties Dialog. Holds the final state 
    *                       of the checkbox when the method returns. This value 
    *                       is independent of whether the user taps 
    *                       OK or Cancel
    * @param aReadOnlyDimmed Sets the Read-only checkbox to dimmed or 
    *                        not dimmed
    * @param aNameValue The Name field value text 
    * @param aTypeValue The Type field value text 
    * @param aDateAndTimeValue The Date field and Time field value text 
    * @param aSizeValueInB The Size field value text 
    * @param aExtraFieldArray Additional prompt/value pairs for the Properties 
    *                         Dialog. 
    *                         <code>CCknColumnItems</code> can contain empty 
    *                         text values to provide row spacing within columns.
    *                         Defaults to <code>NULL</code>
    * @remarks
    * @see
    */
    IMPORT_C TPropertiesDialogArgumentList(CEikButtonBase::TState& aReadOnlyState, 
                                            TBool aReadOnlyDimmed, 
                                            const TDesC& aNameValue, 
                                            const TDesC& aTypeValue, 
                                            const TTime& aDateAndTimeValue, 
                                            TInt aSizeValueInB, 
                                            const RPointerArray<CCknColumnItem>* aExtraFieldArray=NULL);
    public:
    ///Passes the initial state of the Read-only checkbox to a CCknPropertiesDialog 
    ///and holds the final state of this checkbox after CCknPropertiesDialog::RunDlgLD
        /** @internal */
        CEikButtonBase::TState& iReadOnlyCheckBoxState; 

    ///Passes an initial setting for dimmedness of Read-only checkbox to a CCknPropertiesDialog
        /** @internal */
        TBool iReadOnlyCheckBoxDimmed; 
    
    ///Passes a name value text to a CCknPropertiesDialog
        /** @internal */
        const TDesC& iNameValue; 

    ///Passes a type value text to a CCknPropertiesDialog
        /** @internal */
        const TDesC& iTypeValue; 

    ///Passes a date and time value to a CCknPropertiesDialog used for both date value 
    ///and time value text
        /** @internal */
        const TTime& iDateAndTimeValue; 

    ///Passes a size value to a CCknPropertiesDialog used for size value text
        /** @internal */
        TInt iSizeValueInB;  

    ///Passes an array of extra Prompt/Value pairs to be displayed in a CCknPropertiesDialog
        /** @internal */
        const RPointerArray<CCknColumnItem>* iExtraFieldArray;
    };


/**
*  The <code>CCknPropertiesDialog</code> class implements the Properties Dialog.
*
*  @lib ckndlg.lib
*  @since Series90 1.0
*/
class CCknPropertiesDialog : public CEikDialog, public MCknFolderPropertiesObserver
    {
    public: //Declarations

    /** 
    * The enumeration <code>TCknPropertiesDialogFlags</code> specifies that 
    * one or both of the Protected and Sending fields is not displayed in the 
    * Properties Dialog.
    */
    enum TCknPropertiesDialogFlags
        {
        /** the Protected field is not shown */
        ENoProtectionField  =0x01,
        /** the Sending field is not shown */
        ENoSendingField     =0x02
        };

    public:
      /**
       * Displays the File Properties Dialog.
       *
       * @param aDialogTitle The dialog title
       * @param aArgumentList See the definition of 
       *                      <code>TPropertiesDialogArgumentList</code>  
       *                      for details of individual fields
       * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> if 
       *         the user taps Cancel
       * @remarks
       * @see
       */
       IMPORT_C static TBool RunDlgLD(const TDesC& aDialogTitle, 
                                   const TPropertiesDialogArgumentList& aArgumentList);
      /**
       * Displays the File Properties Dialog.
       *
       * @param aDialogTitleRid The resource ID used to provide text for the 
       *                        Properties Dialog title
       * @param aArgumentList See the definition of 
       *                      <code>TPropertiesDialogArgumentList</code>  
       *                      for details of individual fields
       * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> if 
       *         the user taps Cancel
       * @remarks
       * @see
       */
       IMPORT_C static TBool RunDlgLD(TInt aDialogTitleRid, 
                                   const TPropertiesDialogArgumentList& aArgumentList);

      /**
       * Displays the File Properties Dialog.
       *
       * @param aObjectType Specifies the object type, for example, image or
       *                    application. Used to determine the dialog title
       * @param aArgumentList See the definition of 
       *                      <code>TPropertiesDialogArgumentList</code>  
       *                      for details of individual fields
       * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> if 
       *         the user taps Cancel
       * @remarks For the range of values in the <code>aObjectType</code>, see 
       *          the definition of <code>TCknObjectType</code> in 
       *          cknobjecttype.h
       * @see
       */
       IMPORT_C static TBool RunDlgLD(TCknObjectType aObjectType, 
                                   const TPropertiesDialogArgumentList& aArgumentList);

      /**
       * Displays the Properties Dialog for a file or folder, with the title 
       * passed in <code>aDialogTitle</code>. 
       *
       * @param aDialogTitle The dialog title
       * @param aFileName The full path of the file for which the properties are
       *                  displayed. The file must exist or the method raises a 
       *                  panic
       * @param aReadOnlyState Initializes the Read-only checkbox state 
       *                       in a Properties Dialog. Holds the final state 
       *                       of the checkbox when the method returns. This 
       *                       value is independent of whether the user taps 
       *                       OK or Cancel
       * @param aReadOnlyDimmed Sets the Read-only checkbox to dimmed or 
       *                        not dimmed
       * @param iExtraFieldArray Additional prompt/value pairs for the  
       *                         Properties Dialog. 
       *                         <code>CCknColumnItems</code> can contain empty 
       *                         text values to provide row spacing within 
       *                         columns.
       *                         Defaults to <code>NULL</code>
       * @param aFlags Specifies whether the Protected and Sending flags are 
       *               displayed in the dialog
       * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> if 
       *         the user taps Cancel. <b>Note</b>: If the return is 
       *         <code>ETrue</code>, the variable referenced by 
       *         <code>aReadOnlyState</code> in the argument list is the user's 
       *         choice of new settings for the checkbox. If the return is 
       *         <code>EFalse</code>, this variable contains the final state of 
       *         the checkbox, which the user has chosen to discard
       * @remarks
       * @see
       */
       IMPORT_C static TBool RunDlgLD(const TDesC& aDialogTitle,
                                   const TFullName& aFileName, 
                                   CEikButtonBase::TState& aReadOnlyState, 
                                   TBool aReadOnlyDimmed,
                                   const RPointerArray<CCknColumnItem>* iExtraFieldArray=NULL,
                                   TUint aFlags=0);

      /**
       * Displays the Properties Dialog for a file or folder, with the title 
       * passed as a resource ID in <code>aDialogTitleRid</code>.
       *
       * @param aDialogTitleRid The ID of the string resource used as the dialog 
       *                        title
       * @param aFileName The full path of the file for which the properties are
       *                  displayed. The file must exist or the method raises a 
       *                  panic
       * @param aReadOnlyState Initializes the Read-only checkbox state 
       *                       in a Properties Dialog. Holds the final state 
       *                       of the checkbox when the method returns. This 
       *                       value is independent of whether the user taps 
       *                       OK or Cancel
       * @param aReadOnlyDimmed Sets the Read-only checkbox to dimmed or 
       *                        not dimmed
       * @param aExtraFieldArray Additional prompt/value pairs for the  
       *                         Properties Dialog. 
       *                         <code>CCknColumnItems</code> can contain empty 
       *                         text values to provide row spacing within 
       *                         columns.
       *                         Defaults to <code>NULL</code>
       * @param aFlags Specifies whether the Protected and Sending flags are 
       *               displayed in the dialog
       * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> if 
       *         the user taps Cancel. <b>Note</b>: If the return is 
       *         <code>ETrue</code>, the variable referenced by 
       *         <code>aReadOnlyState</code> in the argument list is the user's 
       *         choice of new settings for the checkbox. If the return is 
       *         <code>EFalse</code>, this variable contains the final state of 
       *         the checkbox, which the user has chosen to discard
       * @remarks
       * @see
       */
       IMPORT_C static TBool RunDlgLD(TInt aDialogTitleRid,
                                   const TFullName& aFileName, 
                                   CEikButtonBase::TState& aReadOnlyState, 
                                   TBool aReadOnlyDimmed,
                                   const RPointerArray<CCknColumnItem>* aExtraFieldArray=NULL,
                                   TUint aFlags=0);

      /**
       * Displays the Properties Dialog for a file or folder. If 
       * <code>aFileName</code> refers to a file, the dialog title is 
       * determined from the type of the file. If <code>aFileName</code> refers 
       * to a folder, the dialog has the default folder Properties Dialog title.
       *
       * @param aFileName The full path of the file for which the properties are
       *                  displayed. The file must exist or the method raises a 
       *                  panic
       * @param aReadOnlyState Initializes the Read-only checkbox state 
       *                       in a Properties Dialog. Holds the final state 
       *                       of the checkbox when the method returns. This 
       *                       value is independent of whether the user taps 
       *                       OK or Cancel
       * @param aReadOnlyDimmed Sets the Read-only checkbox to dimmed or 
       *                        not dimmed
       * @param aExtraFieldArray Additional prompt/value pairs for the  
       *                         Properties Dialog. 
       *                         <code>CCknColumnItems</code> can contain empty 
       *                         text values to provide row spacing within 
       *                         columns.
       *                         Defaults to <code>NULL</code>
       * @param aFlags Specifies whether the Protected and Sending flags are 
       *               displayed in the dialog
       * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> if 
       *         the user taps Cancel. <b>Note</b>: If the return is 
       *         <code>ETrue</code>, the variable referenced by 
       *         <code>aReadOnlyState</code> in the argument list is the user's 
       *         choice of new settings for the checkbox. If the return is 
       *         <code>EFalse</code>, this variable contains the final state of 
       *         the checkbox, which the user has chosen to discard
       * @remarks
       * @see
       */
       IMPORT_C static TBool RunDlgLD(const TFullName& aFileName, 
                                   CEikButtonBase::TState& aReadOnlyState, 
                                   TBool aReadOnlyDimmed,
                                   const RPointerArray<CCknColumnItem>* aExtraFieldArray=NULL,
                                   TUint aFlags=0);

      /**
       * Displays the Properties Dialog without the Read-only checkbox for a file 
       * or folder. The dialog title is passed in <code>aDialogTitle</code>.
       *
       * @param aDialogTitle The dialog title
       * @param aFileName The full path of the file for which the properties 
       *                  are displayed. The file must exist or the method 
       *                  raises a panic
       * @param iExtraFieldArray Additional prompt/value pairs for the  
       *                         Properties Dialog. 
       *                         <code>CCknColumnItems</code> can contain empty 
       *                         text values to provide row spacing within 
       *                         columns.
       *                         Defaults to <code>NULL</code>
       * @param aFlags Specifies whether the Protected and Sending flags are 
       *               displayed in the dialog
       * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> if 
       *         the user taps Cancel. If <code>aFileName</code> refers to a 
       *         folder the return value is always <code>ETrue</code>
       * @remarks
       * @see
       */
       IMPORT_C static TBool RunDlgLD(const TDesC& aDialogTitle,
                                   const TFullName& aFileName, 
                                   const RPointerArray<CCknColumnItem>* iExtraFieldArray=NULL,
                                   TUint aFlags=0);

      /**
       * Displays the Properties Dialog without the Read-only checkbox for a file 
       * or folder. The dialog title is passed in <code>aDialogTitleRid</code>.
       *
       * @param aDialogTitleRid The string resource used as the dialog title
       * @param aFileName The full path of the file for which the properties 
       *                  are displayed. The file must exist or the method 
       *                  raises a panic
       * @param aExtraFieldArray Additional prompt/value pairs for the  
       *                         Properties Dialog. 
       *                         <code>CCknColumnItems</code> can contain empty 
       *                         text values to provide row spacing within 
       *                         columns.
       *                         Defaults to <code>NULL</code>
       * @param aFlags Specifies whether the Protected and Sending flags are 
       *               displayed in the dialog
       * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> if 
       *         the user taps Cancel. If <code>aFileName</code> refers to a 
       *         folder the return value is always <code>ETrue</code>
       * @remarks
       * @see
       */
       IMPORT_C static TBool RunDlgLD(TInt aDialogTitleRid,
                                   const TFullName& aFileName, 
                                   const RPointerArray<CCknColumnItem>* aExtraFieldArray=NULL,
                                   TUint aFlags=0);

      /**
       * Displays the Properties Dialog for a file or folder. If 
       * <code>aFileName</code> refers to a file, the dialog title is 
       * determined from the type of the file. If <code>aFileName</code> refers 
       * to a folder, the dialog has the default folder Properties Dialog title.
       *
       * @param aFileName The full path of the file for which the properties 
       *                  are displayed. The file must exist or the method 
       *                  raises a panic
       * @param aExtraFieldArray Additional prompt/value pairs for the  
       *                         Properties Dialog. 
       *                         <code>CCknColumnItems</code> can contain empty 
       *                         text values to provide row spacing within 
       *                         columns.
       *                         Defaults to <code>NULL</code>
       * @param aFlags Specifies whether the Protected and Sending flags are 
       *               displayed in the dialog
       * @return <code>ETrue</code> if the user taps OK; <code>EFalse</code> if 
       *         the user taps Cancel. If <code>aFileName</code> refers to a 
       *         folder the return value is always <code>ETrue</code>
       * @remarks
       * @see
       */
       IMPORT_C static TBool RunDlgLD(const TFullName& aFileName, 
                                   const RPointerArray<CCknColumnItem>* aExtraFieldArray=NULL,
                                   TUint aFlags=0);

// From MCknFolderPropertiesObserver

      /**
       * Updates the values shown for folder and file count and size
       * 
       * @param aFolderCount The latest folder count value
       * @param aFileCount The latest file count value
       * @param aSizeInBytes The latest size value value
       * @internal
       * @see <code>MCknFolderPropertiesObserver</code>
       */
       void UpdateValuesL(TInt aFolderCount, TInt aFileCount, TInt aSizeInBytes);

/**
 *
 * Handles completion of the directory scan
 * @internal
 */
    void HandleUpdateComplete();

    private: 
    CCknPropertiesDialog(CEikButtonBase::TState& aReadOnlyState, 
                         TBool aReadOnlyDimmed,
                         const RPointerArray<CCknColumnItem>* aExtraFieldArray,
                         TUint aFlags);
    ~CCknPropertiesDialog();

/**
 * private function to construct the dialog used by all the run methods that take the file name argument
 * 
 * @param aFileName The file or folder the dialog is to be run for
 * @param aHasCheckbox ETrue if the dialog is to have a read-only checkbox, else EFalse
 * @returns Resource Id for the appropriate dialog resource
 */
    TInt ConstructDialogL(const TFullName& aFileName, TBool aHasCheckbox);

/**
 * Sets up iDefaultItemArray with the default prompts for file properties and corresponding values from the 
 * arguments passed. Leaves if any append operation fails.
 *
 * @param aNameValue The name of the object who's properties are being displayed ('Name' default field)
 * @param aTypeValue The type of the object ('Type' default field)
 * @param aDateTimeValue Used to configure both the 'Date' and 'Time' default field value text 
 *            which are both formatted according to current locale settings
 * @param aSizeValueInkB Used to configure the Size default field value text which is converted to kB 
 *            if more than 1024 bytes. Units are added to the text displayed.
 */
    void InitialiseColumnedTextArrayForFileL(const TDesC& aNameValue, 
                                             const TDesC& aTypeValue, 
                                             const TTime& aDateTimeValue,  
                                             TInt aSizeValueInkB);

/**
 * Sets up iDefaultItemArray with the default prompts for folder properties and corresponding values from the 
 * arguments passed. Leaves if any append operation fails.
 *
 * @param aNameValue The name of the object who's properties are being displayed ('Name' default field)
 * @param aDateTimeValue Used to configure both the 'Date' and 'Time' default field value text 
 *            which are both formatted according to current locale settings
 */
    void InitialiseColumnedTextArrayForFolderL(const TDesC& aNameValue, 
                                               const TTime& aDateTimeValue);

/**
 * Appends a single Prompt/Value pair to the default array. Leaves if the append fails
 *
 * @param aPromptRid A resource Id used to provide text for the fields Prompt
 * @param aValue A reference to a string used to provide text for the fields Value
 * @param aColumn The column where the Prompt/Value pair will be displayed (Allowed range 0<=aColumn<2)
 *            Where aColumn >=2 the pair is not displayed in the dialog.
 */
    void AddColumnItemToDefaultItemArrayL(TInt aPromptRid, 
                                          const TDesC& aValue, 
                                          TInt aColumn);

/**
 * Appends a single Prompt/Value pair to the default array. Leaves if the append fails
 *
 * @param aPromptRid A resource Id used to provide text for the field's Prompt
 * @param aValueRid A resource Id used used to provide text for the field's Value
 * @param aColumn The column where the Prompt/Value pair will be displayed (Allowed range 0<=aColumn<2)
 *            Where aColumn >=2 the pair is not displayed in the dialog.
 */
    void AddColumnItemToDefaultItemArrayL(TInt aPromptRid, 
                                          TInt aValueRid, 
                                          TInt aColumn);

/**
 * Uses aFolders and aFiles to configure a text string giving the number of folders and files.
 *
 * @param aFolders Number of folders
 * @param aFiles Number of files
 *
 * @return Pointer to a string containing the contents in folders and files
 */
    HBufC* ContentsAsTextLC(TInt aFolders, TInt aFiles);

/**
 * Uses aSizeInB to configure a text string giving size and units, converting to kB if aSizeInB is greater 
 * than 1024 bytes. If converting to kB the value is rounded up to 2 significant figures
 *
 * @param aSizeInB Initial size value in bytes
 *
 * @return Pointer to a string containing the size in bytes/kB with appropriate units
 */
    HBufC* SizeAsTextLC(TInt aSizeInB);

/**
 * Uses aDateTimeValue to configure a text string giving the date in a format determined by the 
 * locale settings
 *
 * @param aDateTimeValue Value containing the required date 
 *
 * @return Pointer to a string containing the date from aDateTimeValue in locale determined format
 */
    HBufC* DateAsTextLC(const TTime& aDateTimeValue);

/**
 * Uses aDateTimeValue to configure a text string giving the time in a format determined by the 
 * locale settings
 *
 * @param aDateTimeValue Value containing the required time 
 *
 * @return Pointer to a string containing the time from aDateTimeValue in locale determined format
 */
    HBufC* TimeAsTextLC(const TTime& aDateTimeValue);

    void SetTitleText(HBufC* aTitle);

/**
 * Uses aObjectType to determine which dialog title string to return
 *
 * @param aObjectType Used as an index to a predefined resource, which is then returned by the method
 *
 * @return A string to be used as the dialog title
 */
    static HBufC* GetDialogTitleFromObjectTypeLC(TCknObjectType aObjectType);

/**
 * Uses the full path of a file or folder to determine which dialog title string to return
 *
 * @param aPath The full path of the file or folder
 *
 * @return A string to be used as the dialog title
 */
    static HBufC* DialogTitleLC(const TDesC& aPath);

    // From CEikDialog
    void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
    void HandleControlStateChangeL(TInt aControlId);
private:
    ///Text string for dialog title
    HBufC* iTitle;
    
    ///Current state of the 'Read only' check box
    CEikButtonBase::TState& iReadOnlyState; 

    ///Dimmedness of the 'Read only' check box
    TBool iReadOnlyIsDimmed;
    
    ///Array of column items for the default dialog fields (destroyed in destructor)
    RPointerArray<CCknColumnItem> iDefaultItemArray;    

    ///Array of column items for any custom dialog fields (not destroyed in destructor)
    const RPointerArray<CCknColumnItem>* iUserItemArray;

    ///Whether this is a folder-properties dialog or a file-properties dialog
    TBool iFolder;

    CCknFolderPropertiesReporter* iUpdateReporter;

    HBufC* iObjectName;

    TUint iFlags;
    };


#endif  // CKNPROPERTIESDIALOG_H
