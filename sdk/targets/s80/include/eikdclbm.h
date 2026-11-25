/*
* ==============================================================================
*  Name        : eikdclbm.h
*  Part of     : CKON
*  Interface   : Contents Listbox API
*  Description : Directory contents list box data model.
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

#ifndef EIKDCLBM_H
#define EIKDCLBM_H

// INCLUDES
#include <eiklbm.h>
#include <f32file.h>
#include <bamdesca.h>

// CLASS DECLARATIONS

/*
 * Allows users of the CDirContentsListBoxModel class to filter out files from the file list.
 * If an observer it present, the RemoveFileFromDirContentsListL function is called for every
 * file in the list box, and the function can return ETrue to remove that file. It can be used
 * for example to remove all files that aren't a particular application file.
 *
 * @since Series90 1.0
 */
class MDirContentsListBoxFilter
    {
	public:
	// New methods
        
		/**
		* Called to get information about whether particular files should be removed from the list box.
		* @param aPath The file name of the file in questions.
		* @param aEntry Data structure giving file information.
		* @return ETrue if the file should be removed from the list box. EFalse if it shouldn't
		* <BR><B>Type of return value:</B> TBool
		*/
		virtual TBool RemoveFileFromDirContentsListL(const TDesC& aPath,const TEntry& aEntry)=0;
    };

/**
 *
 * File Directory list box model interface.
 *
 * File Directory list box models provide the file data of the items which are drawn by
 * an associated <code>CDirContentsListItemDrawer</code>. This interface is
 * implemented by <code>CDirContentsListBoxModel</code>.
 *
 * @since Series90 1.0
 * @lib eikfile.lib
 */
class CDirContentsListBoxModel : public CBase, public MListBoxModel
    {
	public:  // Declarations
	enum TSortOrder
		{
		EOrderByName	=0x00,
		EOrderBySize	=0x01,
		EOrderByDate	=0x02,
		EOrderByType	=0x04
		};
	enum TDisplayFlags
		{
		EShowFilesOnly	=0x08,
		EShowDirsOnly	=0x10,
		EShowSingleExt	=0x20,
		EShowRootItem	=0x40,
		EShowNoItemsText=0x400,  /**If set, the dummy item is used to display an informational text 
									at the end of the list, if the current parent folder has no files*/
		};
	enum TContent
		{
		EShowSystem	=0x80,
		EShowHidden	=0x100
		};

/**
 * Data structure for a file item - file attributes, size and time modified.
 * @since Series90 1.0
 * @lib eikfile.lib
 */
	class TFileInfo
		{
	public:
		IMPORT_C TFileInfo();
	public:
		TUint iAtt;
		TInt iSize;
		TTime iModified;
		};

	private:  // Declarations
	enum 
		{
		ESortMask		=0x007,
		EAllowUid		=0x100,
		ESortDescending	=0x200,
		ENoItemsDummyExists    =0x800 /**Used to indicate the existence of a dummy item showing 
										 that the current parent folder has no files*/
		};

	public:
	// Constructors and destructor

		/**
		* Static constructor.
		*/
		IMPORT_C static CDirContentsListBoxModel* NewL(RFs& aFsSession,TUint aFlags);

		/**
		* Destructor.
		*/
		IMPORT_C ~CDirContentsListBoxModel();


	// New methods
        
		/**
		* Reloads the file list for the current directory.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void UpdateL();

		/**
		* Clears all file data from the list box.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void Reset();

		/**
		* Sets the current directory from which to get files, then calls UpdateL() to reload the file list.
		* @param aPath The full path of the directory.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetCurrentPathL(const TDesC& aPath);

		/**
		* Gets the file name of a particular item.
		* @param aItemIndex The index of the requested item.
		* @return The file name of this item.
		* <BR><B>Type of return value:</B> TDesC&
		*/
		IMPORT_C TDesC& ItemName(TInt aItemIndex) const;

		/**
		* Gets the file information of a particular item
		* @param aItemIndex The index of the requested item.
		* @return The TFileInfo data structure for this item
		* <BR><B>Type of return value:</B> TFileInfo
		*/
		IMPORT_C TFileInfo ItemInfo(TInt aItemIndex) const;

		/**
		* Sets the current path to be the parent directory of the current one, then calls UpdateL() to reload the file list.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ChangeToParentDirL();

		/**
		* Sets the current path to be the folder on the specified line of the file list,
		* then calls UpdateL() to reload the file list.
		* @param aItemIndex The index of the folder item to change to.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ChangeToSubDirL(TInt aItemIndex);

		/**
		* Returns the full path and name of the specified item.
		* @param aItemIndex The index of the requested item.
		* @return The path and file name of this item.
		* <BR><B>Type of return value:</B> TFileName
		*/
		IMPORT_C TFileName ItemFullName(TInt aItemIndex) const;

		/**
		* Returns ETrue if this item is the parent directory of the current files in the list.
		* @param aItemIndex The index of the item. Note this function can only return ETrue if
		*     aItemIndex is 0, because the parent directory item is always displayed at the top.
		* @return ETrue if the item is the parent directory item.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool ItemIsParent(TInt aItemIndex) const;

		/**
		* Returns ETrue if this item is a sub-directory of the current directory.
		* @param aItemIndex The index of the item.
		* @return ETrue if the item is a sub-directory.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool ItemIsSubDir(TInt aItemIndex) const;

		/**
		* @param  aPath full path of the item
		* @return  -1 if the item does not exist or is empty. 
		            0 if the item does not have any valid child.
			        1 if the item has at least one valid child
		* <BR><B>Type of return value:</B> TInt
		*/
		TInt CheckIfItemHasChildrenUsingSpecifiedPathL(const TDesC& aPath);

		/**
		* @param  aItemIndex index of the item
		* @return  -1 if the item does not exist or is empty. 
		            0 if the item does not have any valid child.
			        1 if the item has at least one valid child
		* <BR><B>Type of return value:</B> TInt
		*/
		TInt CheckIfItemHasChildrenL(TInt aItemIndex);

		/**
		* Sets the file extension for the file list. This will filter the list to only show files with this extension.
		* It will also automatically add the extension to a file name when calling ItemFullName(). 
		* @param aExt The extension name, including the dot, e.g. ".txt"
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetExtensionL(const TDesC& aExt);

		/**
		* Gets the path of the currently displayed directory.
		* @return The full path.
		* <BR><B>Type of return value:</B> TDesC*
		*/
		inline TDesC* CurrentPath() const;

		/**
		* Gets the current file extension.
		* @return Pointer to the file extension of displayed files.
		* <BR><B>Type of return value:</B> TDesC*
		*/
		inline TDesC* Extension() const;

		/**
		* Sets the order in which files should be sorted in the list box.
		* @param aSortOrder The sort order - either by file name, size, date modified or type. 
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetSortOrder(CDirContentsListBoxModel::TSortOrder aSortOrder);

		/**
		* Gets the current sort order for the list box.
		* @return The sort order.
		* <BR><B>Type of return value:</B> CDirContentsListBoxModel::TSortOrder
		*/
		IMPORT_C CDirContentsListBoxModel::TSortOrder SortOrder() const;
	
		/**
		* Sets the display flags for this list box.
		* @param aDisplayFlags The flags to be set. Valid flags are:
		*  EShowFilesOnly    :  Shows only files, and no folders
		*  EShowDirsOnly     :  Shows only folders, and no files	
		*  EShowSingleExt	 :  Shows file extensions
		*  EShowRootItem	 :  Adds an item for the parent directory of the files
		*  EShowNoItemsText  :  Display text if no items are in the list
		*  
		* <BR><B>Type of return value:</B> void
		*/
		inline void SetDisplayFlags(CDirContentsListBoxModel::TDisplayFlags aDisplayFlags);

		/**
		* Clears display flags for this list box.
		* @param aDisplayFlags The flags to be cleared.
		* <BR><B>Type of return value:</B> void
		*/
		inline void ClearDisplayFlags(CDirContentsListBoxModel::TDisplayFlags aDisplayFlags);

		/**
		* Sets or clears the flag to allow uids to be added to the TFileInfo.
		* @param aAllow Set ETrue if the flag is to be set, EFalse if it is to be cleared.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetAllowUid(TBool aAllow);

		/**
		* Specifies whether the sort order should be in ascending or descending order.
		* @param aAscending Set ETrue if the files should be displayed in ascending order,
		*             EFalse to sort in descending order.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetSortAscending(TBool aAscending);

		/**
		* Gets the file information for the specified item.
		* @param aItemIndex The index of the requested item.
		* @return Data structure giving information for this file.
		* <BR><B>Type of return value:</B> TEntry*
		*/
		IMPORT_C TEntry* Item(TInt aItemIndex) const;

		/**
		* Gets the uid of the application associated with the file.
		* @param aItemIndex The index of the requested item.
		* @return Uid of the application.
		* <BR><B>Type of return value:</B> TUid
		*/
		IMPORT_C TUid ItemUid(TInt aItemIndex) const;

		/**
		* Checks if the file is DRM-closed.
		* @param aItemIndex The index of the requested item.
		* @retval ETrue if the file is closed.
		* @retval EFalse if the file is not closed.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool IsItemClosed(TInt aItemIndex) const;

		/**
		* Sets the flags for the list box.
		* @param aContentFlags The flags to be set.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetContent(TUint aContentFlags);

		/**
		* Returns ETrue if this item is a dummy item. A dummy item is displayed
		* when there are no files in the list.
		* @param aItemIndex The index of the item in question
		* @return ETrue if the item is a dummy item.
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C TBool ItemIsDummy(TInt aItemIndex) const;

		/**
		* Get the Uid of the dummy item.
		* @return The dummy item Uid.
		* <BR><B>Type of return value:</B> TUid
		*/
		IMPORT_C TUid DummyItemUid() const;

		/**
		* Sets the name and Uid for a dummy item.
		* @param aDummyItemName The dummy item's name.
		* @param aDummyItemUid The dummy item's Uid.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetDummyItemL(const TDesC& aDummyItemName,TUid aDummyItemUid);

		/**
		* Sets the name for a dummy item, and deletes the old one.
		* @param aNewName The dummy item's name. The class takes ownership of this descriptor.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void RenameDummyItem(HBufC* aNewName);

		/**
		* Gets the name for a dummy item.
		* @return Descriptor for the dummy item's name.
		* <BR><B>Type of return value:</B> TPtrC
		*/
		IMPORT_C TPtrC DummyItemName() const;

		/**
		* Set the file list filter, for filtering the displayed files. 
		* @param aFilterObserver The filtering class, which must implement the RemoveFileFromDirContentsListL() function.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void SetFileListFilterObserver(MDirContentsListBoxFilter* aFilterObserver);

		/**
		* Gets the file name of the specified item, without the file extension.
		* @param aBuf The buffer into which the filename is copied.
		* @param aItemIndex The index of the item whose filename is requested.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ItemNameNoExt(TDes &aBuf, TInt aItemIndex) const;

		/**
		* Gets the number of items in the list box.
		* @return The number of items.
		* <BR><B>Type of return value:</B> TInt
		*/
		IMPORT_C TInt NumberOfItems() const;

		/**
		* Gets the filename array of items in the list box.
		* @return Pointer to the filename array
		* <BR><B>Type of return value:</B> MDesCArray*
		*/
		inline const MDesCArray* MatchableTextArray() const;

    private: //Methods

		IMPORT_C TAny* Reserved_1();
		CDirContentsListBoxModel(RFs& aFsSession,TInt aFlags);
		void ConstructL();
		void CheckForErrorFromFileServerL(TInt aErrorCode);
		void ChangeCurrentPathL(const TDesC& aPath);
		void GetDriveNameL(TFileName& aName,const TParsePtrC& aParse);
        TBool IsItemClosedHelperL(const TInt aJ) const;

	private:     // Data
		MDesCArray* iItemTextArray;
		HBufC* iCurrentPath;
		HBufC* iExtension;
		HBufC* iParentName;
		RFs iFsSession;
		CDir* iDirList;
		CDir* iFileList;
		TUint iFlags;
		TUint iInternalFlags;	// used to be integrated into iFlags but there was a clash
		TParse iParse;
		HBufC* iDummyItemName;
		TUid iDummyItemUid;
		MDirContentsListBoxFilter* iFilterObserver;
		mutable RArray<TUid> iFileUids;
		mutable RArray<TBool> iFileIsClosedContentArray;
    };

/**
*  Class for accessing the filename text array stored in the CDirContentsListBoxModel.
*
*  @since Series90 1.0
*  @lib eikfile.lib
*/
class CDirContentsTextArray : public CBase, public MDesCArray
    {
	public:
	// New methods
		/**
		* Constructor.
		* @param aModel Pointer to the list box model whose text will fill the array.
		*/
		CDirContentsTextArray(const CDirContentsListBoxModel* aModel);

		/**
		* Gets the size of the array.
		* @return The number of text items in the array.
		* <BR><B>Type of return value:</B> TInt
		*/
		TInt MdcaCount() const;

		/**
		* Gets an item from the array.
		* @param aIndex The item index to be got.
		* @return A descriptor for the item.
		* <BR><B>Type of return value:</B> TPtrC
		*/
		TPtrC MdcaPoint(TInt aIndex) const;

	private:     // Data
		const CDirContentsListBoxModel* iModel;
		TBuf<1> iParentIncMatchText;
    };

inline TDesC* CDirContentsListBoxModel::CurrentPath() const
	{ return iCurrentPath; }
inline TDesC* CDirContentsListBoxModel::Extension() const
	{ return iExtension; }
inline void CDirContentsListBoxModel::SetDisplayFlags(CDirContentsListBoxModel::TDisplayFlags aDisplayFlags)
	{ iFlags|=aDisplayFlags; }
inline void CDirContentsListBoxModel::ClearDisplayFlags(CDirContentsListBoxModel::TDisplayFlags aDisplayFlags)
	{ iFlags&=~aDisplayFlags; }
inline const MDesCArray* CDirContentsListBoxModel::MatchableTextArray() const
	{ return iItemTextArray; }

#endif      // EIKDCLBM_H   
            
// End of File