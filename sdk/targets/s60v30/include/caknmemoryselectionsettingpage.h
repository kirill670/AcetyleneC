/*
* ==============================================================================
*  Name        : CAknMemorySelectionSettingPage.h
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

#ifndef CAKNMEMORYSELECTIONSETTINGPAGE_H
#define CAKNMEMORYSELECTIONSETTINGPAGE_H

// INCLUDES
#include <CAknMemorySelectionDialog.h>

// FORWARD DECLARATIONS
class MAknMemorySelectionObserver;

//  CLASS DEFINITION
/**
*  A class that launches a popup setting page for memory selection.
*
*  @lib CommonDialogs.dll
*  @since 1.2
*/
NONSHARABLE_CLASS(CAknMemorySelectionSettingPage) : public CAknMemorySelectionDialog
	{
	public:		// Constructors and destructors

		/**
		* Static constructor. Loads default settings.
		* @return Returns a pointer to an instance of itself.
		*/
		IMPORT_C static CAknMemorySelectionSettingPage* NewL();

		/**
		* Static constructor.
		* @param aResourceId A resource id (MEMORYSELECTIONDIALOG).
		* @return Returns a pointer to an instance of itself.
		*/
		IMPORT_C static CAknMemorySelectionSettingPage* NewL( TInt aResourceId );

		IMPORT_C ~CAknMemorySelectionSettingPage();

	public:		// New functions

		/** 
		* Executes the memory selection setting page. Virtual to allow derivation.
		* @param aSelectedMemory A reference to a memory (TMemory).
		*        If one of the memories is selected, the selected memory is
		*        stored to the parameter.
		* @return Returns true if user has selected an item and false
		*         if user hits cancel.
		*/
		IMPORT_C TReturnKey ExecuteL( TMemory& aSelectedMemory );

		/** 
		* Executes the memory selection setting page. Virtual to allow derivation.
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
		IMPORT_C TReturnKey ExecuteL(
			TMemory& aSelectedMemory, TDes* aRootPath, TDes* aDefaultFolder );
		
		// Static methods for launching memory selection dialog
		// Parameters & return value are descibed in method RunLD

		IMPORT_C static TBool RunDlgLD( TMemory& aSelectedMemory,
			MAknMemorySelectionObserver* aObserver = NULL );

		IMPORT_C static TBool RunDlgLD( TMemory& aSelectedMemory,
			const TDesC& aTitle,
			MAknMemorySelectionObserver* aObserver = NULL );

		IMPORT_C static TBool RunDlgLD( TMemory& aSelectedMemory,
			TInt aResourceId,
			TDes* aRootPath = NULL, TDes* aDefaultFolder = NULL,
			MAknMemorySelectionObserver* aObserver = NULL );


	private:	// Constructors and destructors

		CAknMemorySelectionSettingPage();

	private:	// New functions

		/**
		* A static method for launching a memory selection setting page.
		* Creates, constructs, runs and deletes a memory selection dialog with
		* different parameters.
		* @param aResourceId An id of a resource.
		* @param aSelectedMemory A reference to a memory described in ExecuteL.
		* @param aTitle A title for memory selection dialog.
		* @param aRootPath A pointer to a descriptor where the root path
		*        of the selected memory is stored.
		* @param aDefaultFolder A pointer to a descriptor where the default folder
		*        of the selected memory is stored.
		* @param aObserver An observer which is asked if the selected item
		*        can be selected. Implemented in application.
		*/
		static TBool RunL(
			TInt aResourceId,
			TMemory& aSelectedMemory,
			const TDesC& aTitle,
			TDes* aRootPath,
			TDes* aDefaultFolder,
			MAknMemorySelectionObserver* aObserver );
	};

#endif // CAKNMEMORYSELECTIONSETTINGPAGE_H

// End of File
