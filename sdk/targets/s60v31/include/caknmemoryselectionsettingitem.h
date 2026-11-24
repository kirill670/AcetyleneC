/*
* ==============================================================================
*  Name        : CAknMemorySelectionSettingItem.h
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

#ifndef CAKNMEMORYSELECTIONSETTINGITEM_H
#define CAKNMEMORYSELECTIONSETTINGITEM_H

//  INCLUDES
#include <AknSettingItemList.h>
#include <CAknMemorySelectionSettingPage.h>

// CLASS DECLARATION
/**
*  CAknMemorySelectionSettingItem is a setting item class that
*  launches a CAknMemorySelectionSettingPage.
*
*  @lib CommonDialogs.dll
*  @since 1.2
*/
class CAknMemorySelectionSettingItem : public CAknSettingItem
	{
	public:		// Constructors and destructor

		IMPORT_C CAknMemorySelectionSettingItem(
			TInt aIdentifier,
			CAknMemorySelectionSettingPage::TMemory& aSelectedMemory );
		IMPORT_C virtual ~CAknMemorySelectionSettingItem();
		IMPORT_C void CompleteConstructionL();

	public:		// Functions from base classes

		/**
		* From CAknSettingItem
		*/
		IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );

		/**
		* From CAknSettingItem
		*/
		IMPORT_C virtual void LoadL();

		/**
		* From CAknSettingItem
		*/
		IMPORT_C virtual void StoreL();

		/**
		* From CAknSettingItem
		*/
		IMPORT_C virtual const TDesC& SettingTextL();

	protected:	// Data

		// Ref: External data
		CAknMemorySelectionSettingPage::TMemory& iExternalData;

		// Own: Internal data
		CAknMemorySelectionSettingPage::TMemory iInternalData;

		// Own: Setting page
		CAknMemorySelectionSettingPage* iSettingPage;

		// Own: The length is enough for memory name.
		TBuf<64> iSettingText;

	};

// CAKNMEMORYSELECTIONSETTINGITEM_H
#endif

// End of File
