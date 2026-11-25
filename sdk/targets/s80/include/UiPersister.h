/*
* ==============================================================================
*  Name        : uipersister.h
*  Part of     : Utilities
*  Interface   : Utilities API
*  Description : Persistant information utilities
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


#ifndef UIPERSISTER_H
#define UIPERSISTER_H

// INCLUDES
#include <e32std.h>
#include <f32file.h>
#include <barsread.h>
#include <badesca.h>

// CONSTANTS
// UIDs for items in system.ini file
const TUid KUidLocaleInfo={0x1000966A};
const TUid KUidCurrencySymbolInfo={0x10009791};
const TUid KUidDisplayBrightness={0x10008F6E};
const TUid KUidDisplayContrast={0x10009959};

/**
*  A static class to manage persisting of various information on the Hildon platform
*  To persist (save and restore) the following information on the platform:
*  locale, currency symbol, brightness level, contrast level
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class UiPersister
	{
	public:

		/**
		* Writes out locale information to file
		* @since ?Series90_version
		* @param aFs The file system
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void ExternalizeLocaleToSystemL(RFs& aFs);

		/**
		* Loads locale information from file
		* @since ?Series90_version
		* @param aFs The file system
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void InternalizeLocaleFromSystemL(RFs& aFs);

		/**
		* Writes out currency information to file
		* @since ?Series90_version
		* @param aFs The file system
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void ExternalizeCurrencySymbolToSystemL(RFs& aFs);

		/**
		* Loads currency information from file
		* @since ?Series90_version
		* @param aFs The file system
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void InternalizeCurrencySymbolFromSystemL(RFs& aFs);

		/**
		* Writes out the brightness information to file
		* @since ?Series90_version
		* @param aFs The file system
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void ExternalizeBrightnessLevelToSystemL(RFs& aFs);

		/**
		* Reads the brightness information from file
		* @since ?Series90_version
		* @param aFs The file system
		* @return void
		* <BR><B>Type of return value:</B> void
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C static void InternalizeBrightnessLevelFromSystemL(RFs& aFs);

		/**
		* Writes out the contrast level to file
		* @since ?Series90_version
		* @param aFs The file system
		* @return void
		* <BR><B>Type of return value:</B> void
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C static void ExternalizeContrastLevelToSystemL(RFs& aFs);

		/**
		* Loads the contrast level from file
		* @since ?Series90_version
		* @param aFs The file system
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void InternalizeContrastLevelFromSystemL(RFs& aFs);
	};


#endif	// UIPERSISTER_H

// End of File
