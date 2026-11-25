/*
* ==============================================================================
*  Name        : uisemaphoreutils.h
*  Part of     : Utilities
*  Interface   : Utilities API
*  Description : Semaphore utilities
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


#ifndef UISEMAPHOREUTILS_H
#define UISEMAPHOREUTILS_H

// INCLUDES
#include <E32STD.H>

/**
*  A static utility class to allow simplified access to Semaphores,
*  Here a Semaphore can be either Set or Clear.
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class UiSemaphoreUtils
	{
	public:

		/**
		* Checks if semaphore is set
		* @since ?Series90_version
		* @return ETrue if specified semaphore is set, EFalse otherwise
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C static TBool IsSemaphoreSetL(const TDesC &aString);

		/**
		* Checks if semaphore is set. Non-leaving version of this function
		* @since ?Series90_version
		* @return KErrNone if successful, otherwise system-wide error code.
		* <BR><B>Type of return value:</B> TInt
		*/
		IMPORT_C static TInt IsSemaphoreSet(const TDesC &aString, 
											  TBool& aSemaphoreSet);

		/**
		* Sets a semaphore
		* @since ?Series90_version
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void SetSemaphoreL(const TDesC &aString);

		/**
		* Sets a semaphore. Non-leaving version of this function.
		* @since ?Series90_version
		* @return KErrNone if successful, otherwise system-wide error code.
		* <BR><B>Type of return value:</B> TInt
		*/
		IMPORT_C static TInt SetSemaphore(const TDesC &aString);

		/**
		* Clears a semaphore
		* @since ?Series90_version
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void ClearSemaphoreL(const TDesC &aString);

		/**
		* Clears a semaphore. Non-leaving version of this function.
		* @since ?Series90_version
		* @return KErrNone if successful, otherwise system-wide error code.
		* <BR><B>Type of return value:</B> TInt
		*/
		IMPORT_C static TInt ClearSemaphore(const TDesC &aString);
	};



#endif	// UISEMAPHOREUTILS_H

// End of File
