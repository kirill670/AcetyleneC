/*
* ==============================================================================
*  Name        : MAknMemorySelectionObserver.h
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

#ifndef MAKNMEMORYSELECTIONOBSERVER_H
#define MAKNMEMORYSELECTIONOBSERVER_H

// INCLUDES
#include <CAknMemorySelectionDialog.h>

/**
*  Observer class that can be set to observe if selected memory
*  e.g. has enoung free space before letting dialog exit.
*
*  @lib CommonDialogs.dll
*  @since 1.2
*/
class MAknMemorySelectionObserver
	{
	public: // Constructors and destructor

		/**
		* A virtual destructor to ensure that correct destructor gets called.
		* Must have an empty implementation.
		*/
		virtual ~MAknMemorySelectionObserver() { };

	public:		// New functions

		/**
		* Get's called when user selects a memory.
		* @param aMemory Currently selected memory.
		* @return Returns ETrue if it is ok to exit from dialog.
		*/
		virtual TBool OkToExitL( CAknMemorySelectionDialog::TMemory aMemory ) = 0;
	};

#endif // MAKNMEMORYSELECTIONOBSERVER_H

// End of File
