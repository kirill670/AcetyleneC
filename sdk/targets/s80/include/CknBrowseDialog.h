/*
* ==============================================================================
*  Name        : CknBrowseDialog.h
*  Part of     : CKON / CKNDLG
*  Interface   : Dialogs, Browse
*  Description : Browse dialog to select a file/folder
*  Version     : 1.0
*
*  Copyright (c) 2002 Nokia Corporation.
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

#ifndef CCKNBROWSEDIALOG_H
#define CCKNBROWSEDIALOG_H

// INCLUDES
#include <e32def.h>
#include <e32std.h>

// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class MCknDialogObserver;

// CLASS DECLARATION

/**
*  Browse dialog.
*  WID-Dia278
*
*  @lib CKNDLG
*  @since Series90 1.1
*/
class CCknBrowseDialog
    {
    public:  // Constructors and destructor

    public:  // New functions
        
        /**
        * Runs Browse dialog.
        * @since Series90 1.1
        * @param aPath The initial path. If invalid then default path used. Also used to return the selection.
        * @param aFilterUid The Uid to filter the list. If KNullUid then no filtering performed.
        * @param aTitle The dialog title. If KNullDesC then default title used.
        * @param aNoFiles The text to show if no files found. If KNullDesC then default text used.
        * @param aPrecheckExitObserver The observer class used to check that selection is ok.  If NULL then no checking of the selection.
        * @return ETrue if the dialog is okayed. EFalse if the dialog is cancelled.
        */
	IMPORT_C static TBool RunDlgLD(TDes& aPath,
                                       TUid aFilterUid = KNullUid,
                                       const TDesC& aTitle = KNullDesC,
                                       const TDesC& aNoFiles = KNullDesC,
                                       MCknDialogObserver* aPrecheckExitObserver = NULL);

    public: // Functions from base classes

    protected:  // New functions
        
    protected:  // Functions from base classes
        
    private:

        /**
        * C++ default constructor.
        */
	CCknBrowseDialog();

        /**
        * Destructor.
        */
	~CCknBrowseDialog();

        // Prohibit copy constructor if not deriving from CBase.
        CCknBrowseDialog(const CCknBrowseDialog& aCopy);

        // Prohibit assigment operator if not deriving from CBase.
        CCknBrowseDialog& operator=(const CCknBrowseDialog& aAssign);
 
    public:     // Data
    
    protected:  // Data

    private:    // Data

    public:     // Friend classes

    protected:  // Friend classes

    private:    // Friend classes

    };

#endif      // CCKNBROWSEDIALOG_H
            
// End of File
