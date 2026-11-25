/*
* ==============================================================================
*  Name        : statuspaneutilities.h
*  Part of     : CKON
*  Interface   : Indicator API
*  Description : Utility class for status pane.
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
#ifndef STATUSPANEUTILITIES_H
#define STATUSPANEUTILITIES_H


// INCLUDES
#include <e32std.h>
#include <eikappui.h>

// CLASS DECLARATIONS

/**
*  StatusPaneUtilities class provides functions for setting the title area text, 
*  and fading of the title area.
*
*  Link against CKIND.LIB
*/
class CApaMaskedBitmap;
class StatusPaneUtilities 
	{
	public:  // Declarations
	enum TStatusPaneItem
		{
		EItemAppName	 = 0x0000,
		EItemAppSubname	 = 0x0001,
		EItemAppIcon	 = 0x0002,
		EItemExpressName = 0x0003
		};
	public:
	// New methods
		/**
		* Sets the title area text.
		* @param aItem Status pane item. See TStatusPaneItem enum
		* @param aName Name to be updated with
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void UpdateStatusPane(TStatusPaneItem aItem, const TDesC& aName=KNullDesC);
	
		/**
	    * Sets the title area window to allow fading
		* @param aFading Whether fading is on
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void SetTitleNonFading(TBool aFading);

		/**
		Sets the application icon bitmap. Takes ownership of the bitmap.
		*/
		IMPORT_C static void SetAppIconBitmap(CApaMaskedBitmap* aAppIconBitmap);
		
		IMPORT_C static void CreateExpressMenuL(CEikAppUi* aAppUi, TInt aResourceId);

	};

#endif      // STATUSPANEUTILITIES_H   
            
// End of File
