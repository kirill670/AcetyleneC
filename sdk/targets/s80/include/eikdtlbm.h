/*
* =============================================================================
*  Name        : eikdtlbm.h
*  Part of     : CKON
*  Interface   : Tree Listbox API
*  Description : Directory tree listbox data class
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
* =============================================================================
*/

#ifndef EIKDTLBM_H
#define EIKDTLBM_H

// INCLUDES
#include <f32file.h>
#include <eikhlbm.h>

// FORWARD DECLARATIONS
class CDirectoryTreeListBoxModelExt;

// CLASS DECLARATIONS

/**
* Listbox model class for the CEikDirectoryTreeListBox, for listboxes that 
* display a hierarchical directory structure.
*
*  @lib eikfile.lib
*  @since Series90 1.0
*/
class CDirectoryTreeListBoxModel : public CHierarchicalListBoxModel
    {
    public:
    // user flags
    enum TContent
        {
        /** show system folders */
        EShowSystem =0x01,
        /** show hidden folders */
        EShowHidden =0x02,
        /** hide the ROM drive */
        EHideRom    =0x04,
        /** hide the hierarchy's root item */
        EHideRoot   =0x08,
		/** there is a list of drives that must not be shown defined in the resource file, if
		 this flag is set these drives are shown anyway **/
		EShowDrivesInExclusionList =0x10
        };
    // Constructors and destructor
        /**
        * The default object constructor.
        *
        * @param aFsSession The file session to be used by this listbox model 
        *                   when accessing files
        * @param aFlags The flags to be set in this listbox model
        * @return
        * @remarks
        * @see
        */
        IMPORT_C CDirectoryTreeListBoxModel(RFs& aFsSession,TInt aFlags);

        /**
        * The object destructor.
        *
        * @return
        * @remarks
        * @see 
        */
        IMPORT_C ~CDirectoryTreeListBoxModel();

    // New methods
        
        /**
        * Creates a hierarchical file list model for a specified drive number.
        *
        * @param aDrive The number of the drive whose files are to be stored 
        *               in the listbox model
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void CreateListForSpecifiedDriveL(TDriveNumber* aDrive);

        /**
        * Creates a hierarchical file list model for a specified path.
        *
        * @param aPath The full path of the directory to be stored in the 
		*              listbox model
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void CreateListForSpecifiedPathL(const TDesC& aPath);

        /**
        * Expands a specified node in the hierarchical model.
        *
        * @param aNodeToBeExpanded The <code>TInt</code> index of the node to
		*                          be expanded
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void ExpandItemL(TInt aNodeToBeExpanded);

        /**
        * Gets the full path and file name of a list item in the listbox model.
        *
        * @param aIndex The index of the requested list item
        * @return the full path and file name of the list item
        * @remarks
        * @see
        */
        IMPORT_C TFileName FullPath(TInt aIndex) const;

        /**
        * Gets the root directory of the file hierarchy.
        *
        * @return the full path of the root directory
        * @remarks
        * @see
        */
        IMPORT_C TPath Root();

        /**
        * Updates the file hierarchy by checking all the files and directories
        * in the model, adding any new ones, and removing any deleted ones. 
        * 
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void UpdateL();

        /**
        * Sets the flags for this listbox model.
        *
        * @param aContentFlags The flags to be set
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void SetContent(TInt aContentFlags);

        /**
        * Clears flags for this listbox model.
        *
        * @param aContentFlags The flags to be cleared
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void ResetContent(TInt aContentFlags);

        /**
        * Reports whether the tree root is shown as an item in the list, or 
		* not.
        *
        * @return <code>ETrue</code> if the root is hidden; <code>EFalse</code>
		*         if displayed
        * @remarks
        * @see
        */
        IMPORT_C TBool IsRootHidden();

        /**
        * Returns the number of directories in the top level item.
        *
        * @return the number of sub-directories
        * @remarks
        * @see
        */
        IMPORT_C TInt LevelsInRootItemL();

    private: //Methods
        IMPORT_C TAny* Reserved_1();
        void AddDirListItemsLD(const TDesC& aPath,CDir* aDirList,TInt aParentIndex,TInt aItemIndex);
        void CheckIfItemHasChildrenUsingSpecifiedPathL(const TDesC& aPath,CHierListItem* aItem);
        void CheckIfItemHasChildrenL(const TDesC& aPath,CHierListItem* aItem);
        void CreateDriveListL();
        TInt PathExists(const TDesC& aPath) const;
        TBool MemoryCardInList() const;
        void AddMemoryCardIfItExistsL();
        void CheckCreateExtensionL();
        TInt Flags();
        void SetFlags(TInt aFlags);
        void SetRoot(const TDesC& aRootPath);
        TBool CheckFSName(const TInt aIndex);

    private:     // Data
        RFs& iFsSession;
        CDirectoryTreeListBoxModelExt* iExt;
    };

#endif      // EIKDTLBM_H   
            
// End of File
