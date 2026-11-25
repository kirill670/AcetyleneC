/*
* ==============================================================================
*  Name        : eikhkeyt.h
*  Part of     : ckon
*  Interface   : Hotkey API
*  Description : Hotkeys
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


#ifndef EIKHKEYT_H
#define EIKHKEYT_H

// INCLUDES
#include <e32base.h>
#include <e32keys.h>


struct SEikHotKey
	{
		TInt iCommandId;
		TInt iKeycode;
	};

/**
 *
 * An array for hotkey commands and their associated key codes and
 * modifiers.
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikHotKeyTable : public CArrayFixFlat<SEikHotKey>
	{
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikHotKeyTable();

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikHotKeyTable();

		/**
		* Gets the hotkey code and modifier for the specified command ID.
		* @param aCommandId The ID of the hotkey for which the key code and modifiers are obtained
		* @param aKeycode On return, the key code for the specified command ID
		* @param aModifiers On return, the modifier for the specified command ID. 
		* <BR><B>Type of return value:</B> TBool
		* <BR><B>Range of return value:</B> ETrue if the hotkey exists, EFalse otherwise
		*/
		IMPORT_C TBool HotKeyFromCommandId(TInt aCommandId,TInt& aKeycode,TInt& aModifiers) const;

		/**
		* Gets the command ID associated with the specified key code and modifier.
		* @param aKeycode The key code for which the command ID is obtained
		* @param aModifiers The key modifier for which the command ID is obtained
		* <BR><B>Type of return value:</B> TInt
		* <BR><B>Range of return value:</B> The command ID for the specified key code and modifier.
		*/
		IMPORT_C TInt CommandIdFromHotKey(TInt aKeycode,TInt aModifiers) const;

		/**
		* Adds the specified hotkey to the hotkey array
		* @param aCommandId The command associated with the hotkey
		* @param aKeycode The key code used to invoke the com
		* @param aModifiers Any modifiers used to invoke the command, shift or control for example
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void AddItemL(TInt aCommandId,TInt aKeycode,TInt aModifiers);

		/**
		* Removes the item specified by command ID from the array
		* @param aCommandId The ID of the item to remove
			* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void RemoveItem(TInt aCommandId);

		/**
		* Constructs an empty array from resource
		* @param aResourceId The ID if the resource reader to use to construct the array
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void ConstructFromResourceL(TInt aResourceId);

		/**
		* Resets the hotkey array.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void Reset();
	private:
		TInt iNumberPlain;
		TInt iNumberCtrl;
		TInt iNumberShiftCtrl;
		TInt iSpare;
	};


#endif	// EIKHKEYT_H

// End of File
