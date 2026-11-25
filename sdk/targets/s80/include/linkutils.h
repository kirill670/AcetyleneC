/*
* ==============================================================================
*  Name        : linkutils.h
*  Part of     : Link model
*  Interface   : Link model API
*  Description : Link model interface for adding links to menus and launching them
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


#ifndef     __LINKUTILS_H__
#define     __LINKUTILS_H__


//  INCLUDES

#include <e32std.h>

#include <eikhkeyt.h>

#include <f32file.h>

//  FORWARD DECLARATIONS

class   CEikMenuPane;
class   CLinkBase;


//  CLASS DEFINITIONS 

/**
*  Link utilities class
*  A lot of this is deprecated and remains for backward compatibility with 9210
*
*  @lib LinkModel.dll
*/
class   LinkUtils

    {
	public:     // New functions
		/**
		* Adds an 'Add to Favourites' menu item to given menu pane
		* @since ?Series90_version
		* @param aMenuPane Reference to the menu pane the menu item is to be added
		* @param aCommandId Id of the associated menu command
		* @return EFalse
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C static TBool       AddLinkMenuItemL(CEikMenuPane& aMenuPane, TInt aCommandId);
        
		/**
		* Adds a hotkey to the application, that offers add link functionality 
		* with the specified command Id.
		* @since ?Series90_version
		* @param aHotkeyTable reference to the hotkey table
		* @param aCommandId Id of the associated menu command
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void        AddLinkHotKeyL(CEikHotKeyTable& aHotkeyTable, TInt aCommandId);

		/**
		* Creates and adds an item to Favourites.
		* @since ?Series90_version
		* @param aLink reference to the link object to be added
		* @return void
		* <BR><B>Type of return value:</B> void
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C static void        CreateLinkDocumentL(CLinkBase& aLink);

		/**
		* Creates and adds an item to Favourites
		* @since ?Series90_version
		* @param aLink  reference to the link object to be added
		* @param aFsSession reference to a file server session
		* @return ?description
		* <BR><B>Type of return value:</B> void
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C static void        CreateLinkDocumentL(CLinkBase& aLink, RFs& aFsSession);

		/**
		* Checks whether a link is broken if this is possible.
		* @since ?Series90_version
		* @param aLinkName The link to validate
		* @return eTrue - Unable to perform this functionality so ETrue 
		*         is returned for backwards compatability
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C static TBool       ValidateLinkL(const TDesC& aLinkName);

		/**
		* Starts the given link 
		* @since ?Series90_version
		* @param aLinkName The link to start
		* @return The ThreadId of the linked application
		* <BR><B>Type of return value:</B> TThreadId
		*/
		IMPORT_C static TThreadId   StartLinkL(const TDesC& aLinkName);

		/**
		* Updates document links linked to an old file name to link new file name
		* @since ?Series90_version
		* @param aOldFileName n/a
		* @param aNewFileName n/a
		* @return Interface not supported other than returning a NULL thread ID
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void        UpdateLinkL(const TDesC& aOldFileName, const TDesC& aNewFileName);

    };


#endif      //  __LINKUTILS_H__

// End of File
