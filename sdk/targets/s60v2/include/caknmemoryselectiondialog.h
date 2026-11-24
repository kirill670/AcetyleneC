/*
* ==============================================================================
*  Name        : CAknMemorySelectionDialog.h
*  Part of     : Common File Dialogs / CommonDialogs.dll
*  Interface   : ?Interface_category, ?Interface_name
*  Description : ?Description
*  Version     : ?Version
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

#ifndef CAKNMEMORYSELECTIONDIALOG_H
#define CAKNMEMORYSELECTIONDIALOG_H

// INCLUDES
#include <CAknCommonDialogsBase.h>
#include <badesca.h> // CDesCArray

// FORWARD DECLARATIONS
class CAknMemorySelectionModel;
class CAknMemorySelectionEventHandler;
class MAknMemorySelectionObserver;

//  CLASS DEFINITION
/**
*  A class that launches a pop-up dialog for memory selection.
*
*  @lib CommonDialogs.dll
*  @since 1.2
*/
NONSHARABLE_CLASS(CAknMemorySelectionDialog) : public CAknCommonDialogsBase
	{
	public:		// Enumerations

		/**
		* Enumerations for items in list.
		* e.g. EMemoryCard2 could be added in the future if necessary.
		*/
		enum TMemory
			{
			EPhoneMemory = 0,
			EMemoryCard,
			EMemoryCount // must remain last one
			};

	public:		// Constructors and destructors

		/**
		* Static constructor.
		* @param aDialogType Defines the type of the dialog in order to read
		*        correct default settings for title and softkeys from resource.
		* @param aShowUnavailableDrives Defines whether unavailable or corrupted
		*        drives are shown in memory selection list or not.
		* @return Returns a pointer to an instance of itself.
		*/
		IMPORT_C static CAknMemorySelectionDialog* NewL(
			TCommonDialogType aDialogType,
			TBool aShowUnavailableDrives );

		/**
		* Static constructor.
		* @param aDialogType Defines the type of the dialog in order to read
		*        correct default settings for title and softkeys from resource.
		* @param aResourceId A resource id (MEMORYSELECTIONDIALOG).
		* @param aShowUnavailableDrives Defines whether unavailable or corrupted
		*        drives are shown in memory selection list or not.
		* @return Returns a pointer to an instance of itself.
		*/
		IMPORT_C static CAknMemorySelectionDialog* NewL(
			TCommonDialogType aDialogType,
			TInt aResourceId,
			TBool aShowUnavailableDrives );


		IMPORT_C virtual ~CAknMemorySelectionDialog();

	public:		// New functions

		/**
		* Sets an observer which is asked if the selected item can be selected.
		* @param aObserver A pointer to an observer.
		*/
		IMPORT_C void SetObserver( MAknMemorySelectionObserver* aObserver );

		/**
		* Sets title for the dialog.
		* @param aText Title text.
		*/
		IMPORT_C void SetTitleL( const TDesC& aText );

		/**
		* Sets the text used for left softkey.
		* @param aText The text used for left softkey.
		*/
		IMPORT_C void SetLeftSoftkeyL( const TDesC& aText );

		/**
		* Sets the text used for right softkey.
		* @param aText The text used for right softkey.
		*/
		IMPORT_C void SetRightSoftkeyL( const TDesC& aText );

		/**
		* Gets an item from memory selection dialog at specified index.
		* @param aIndex Index to the item in the memory selection list.
		* @param aItem A reference to a descriptor where the item is stored.
		*/
		IMPORT_C void GetItem( TInt aIndex, TDes& aItem );

		/**
		* Gets the location paths of a memory.
		* @param aSelectedMemory The memory that was selected.
		* @param aRootPath A pointer to a descriptor where the root path
		*        of the selected memory is stored. Must have KMaxFileName space.
		*        Set to NULL to ignore.
		* @param aDefaultFolder A pointer to a descriptor where the default folder
		*        of the selected memory is stored. Must have KMaxFileName space.
		*        Set to NULL to ignore.
		*/
		IMPORT_C void GetMemories( TMemory aSelectedMemory,
			TDes* aRootPath, TDes* aDefaultFolder );

		/**
		* Executes the memory selection dialog. Virtual to allow derivation.
		* @param aSelectedMemory A reference to a memory (TMemory).
		*        If one of the memories is selected, the selected memory is
		*        stored to the parameter.
		* @return Returns true if user has selected an item and false
		*         if user hits cancel.
		*/
		IMPORT_C virtual TReturnKey ExecuteL( TMemory& aSelectedMemory );

		/**
		 * Executes the memory selection dialog. Virtual to allow derivation.
		 * @param aSelectedMemory A reference to a memory (TMemory).
		 *        If one of the memories is selected, the selected memory is
		 *        stored to the parameter.
		 * @param aRootPath A pointer to a descriptor where the root path
		 *        of the selected memory is stored.
		 * @param aDefaultFolder A pointer to a descriptor where the default folder
		 *        of the selected memory is stored.
		 * @return Returns true if user has selected an item and false
		 *         if user hits cancel.
		 */
		IMPORT_C virtual TReturnKey ExecuteL( TMemory& aSelectedMemory,
			TDes* aRootPath, TDes* aDefaultFolder );

		/**
		* A static method that launches a memory selection dialog.
		* @see RunL()
		*/
		IMPORT_C static TBool RunDlgLD( TMemory& aSelectedMemory,
			MAknMemorySelectionObserver* aObserver = NULL );

		/**
		* A static method that launches a memory selection dialog.
		* @see RunL()
		*/
		IMPORT_C static TBool RunDlgLD( TMemory& aSelectedMemory,
			const TDesC& aTitle,
			MAknMemorySelectionObserver* aObserver = NULL );

		/**
		* A static method that launches a memory selection dialog.
		* @see RunL()
		*/
		IMPORT_C static TBool RunDlgLD( TMemory& aSelectedMemory,
			TInt aResourceId,
			TDes* aRootPath = NULL, TDes* aDefaultFolder = NULL,
			MAknMemorySelectionObserver* aObserver = NULL );

		/**
		* Returns the number of items in list box array.
		* Not exported, for CFD internal use only.
		* @return Returns the number of items in list box array.
		*/
		TInt NumberOfItems() const;

	protected:	// Constructors and destructors

		CAknMemorySelectionDialog( TCommonDialogType aDialogType );

		/**
		* Constructs class from resource
		* @param aResourceId ID of the resource. Can be zero.
		* @param aShowUnavailableDrives Defines whether unavailable or corrupted
		*        drives are shown in memory selection list or not.
		*/
		virtual void ConstructFromResourceL(
			TInt aResourceId,
			TBool aShowUnavailableDrives );

	private:	//  New functions

		/**
		* A static method for launching a memory selection dialog.
		* Creates, constructs, runs and deletes a memory selection dialog with
		* different parameters.
		* @param aResourceId An id of a resource.
		* @param aSelectedMemory A reference to a memory described in ExecuteL.
		* @param aRootPath A pointer to a descriptor where the root path
		*        of the selected memory is stored.
		* @param aDefaultFolder A pointer to a descriptor where the default folder
		*        of the selected memory is stored.
		* @param aTitle A title for memory selection dialog.
		* @param aObserver An observer which is asked if the selected item
		*        can be selected. Implemented in application..
		*/
		static TBool RunL(
			TInt aResourceId,
			TMemory& aSelectedMemory,
			TDes* aRootPath,
			TDes* aDefaultFolder,
			const TDesC& aTitle,
			MAknMemorySelectionObserver* aObserver );

		/**
		* Sets id to a default CFD resource depending on dialog type.
		*/
		void SetResourceId( TInt& aResourceId, TCommonDialogType aDialogType ) const;

		/**
		* Reads settings from resource.
		*/
		void ReadFromResourceL( TInt aResourceId );

	protected:	// Data

		// Own: Dialog type
		TCommonDialogType iDialogType;

		// Own: Model
		CAknMemorySelectionModel* iModel;
		
		// Own: Event handler
		CAknMemorySelectionEventHandler* iEventHandler;

		// Ref: Observer
		MAknMemorySelectionObserver* iObserver;

		// Own: Title
		HBufC* iTitle;
		
		// Own: Left softkey text
		HBufC* iLeftSoftkey;

		// Own: Right softkey text
		HBufC* iRightSoftkey;

		// Own: Root path array
		CDesCArrayFlat iRootPathArray;

		// Own: Default folder array
		CDesCArrayFlat iDefaultFolderArray;
	};

#endif // CAKNMEMORYSELECTIONDIALOG_H

// End of File
