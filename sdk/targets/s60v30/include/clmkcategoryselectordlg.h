/*
* ==============================================================================
*  Name        : CLmkCategorySelectorDlg.h
*  Part of     : Landmarks UI / LmkCommonUI.dll
*  Interface   : Public
*  Description : This class provides functionality for selecting either one or
*                multiple categories.
*  Version     : 
*
*  Copyright (c) 2004 Nokia Corporation.
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


#ifndef CLMKCATEGORYSELECTORDLG_H
#define CLMKCATEGORYSELECTORDLG_H

//  INCLUDES
#include <e32base.h>                    // CBase
#include <e32std.h>			//RArray and RPointerArray
#include <EPos_Landmarks.h>             // Lm typedefs, constants etc.
#include <EPos_CPosLandmarkDatabase.h>
// FORWARD DECLARATIONS
//class CPosLandmarkDatabase;
class CLmkDlgSelectorImplBase;
class MObjectProvider;

// For multiple database support 
class TLmkItemIdDbCombiInfo;

// CLASS DECLARATION

/**
*  Landmark category selector dialog.
*  This class provides functionality for selecting either one or
*  multiple categories.
*
*/
class CLmkCategorySelectorDlg : public CBase
    {
    public:  // Constructors and destructor
        /**
        * Creates a selector for selecting one or more categories.
        * Categories in the given database are shown in the selector.
        * Construction leaves with KErrNotSupported if framework
        * functionality is not available.
        *
        * 
        * @param aShowEmptyCategories specifies whether categories without
        *        landmarks are shown or not
        * @return new instance of this class
        */       
        IMPORT_C static CLmkCategorySelectorDlg* NewL(TBool aShowEmptyCategories = EFalse );
        
        /**
        * Destructor. Can be also used to cancel this dialog.
        */
        IMPORT_C ~CLmkCategorySelectorDlg();

    public: // New functions
        /**
        * Object provider mechanism.
        * @param aParent parent object
        */
        IMPORT_C void SetMopParent( MObjectProvider* aParent );

        /**
        * Runs single category selection dialog.
        * This object is destroyed when this function returns or leaves.
        *
        * @param aSelected will contain user's selection
        * @return !=0 if accepted, 0 if canceled
        */          
        IMPORT_C TInt ExecuteLD( TLmkItemIdDbCombiInfo& aSelected );
        
        /**
        * Runs multiple category selection dialog.
        * This object is destroyed when this function returns or leaves.
        * Parameter aSelectedItems is used as both input and output parameter,
        * if a non-empty array is given then those items are marked selected
        * by default. Any pre-selected item which is not found is just ignored.
        *
        * @param aSelectedItems contains input/output selections
        * @return !=0 if accepted, 0 if canceled
        */      
        IMPORT_C TInt ExecuteLD( RArray<TLmkItemIdDbCombiInfo>& aSelectedItems );

    private:
        /**
        * C++ default constructor.
        * @return newly instantiated object
        */
        CLmkCategorySelectorDlg(); 	
        
        /**
        * By default Symbian 2nd phase constructor is private.        
        * @param aShowEmptyCategories        
        */
        void ConstructL( TBool aShowEmptyCategories );

    private:    // Data        
        // ETrue if executed in multiple item selector mode
        TBool iIsMultiSelector;

        ///Own: Search implementor object
        CLmkDlgSelectorImplBase* iSelector;

        //Own: Set to ETrue in destructor
        TBool* iDestroyedPtr;

        // Multiple database support 
        RPointerArray <CPosLandmarkDatabase> iDbs; 
        
    };

#endif      // CLMKCATEGORYSELECTORDLG_H   
            
// End of File
