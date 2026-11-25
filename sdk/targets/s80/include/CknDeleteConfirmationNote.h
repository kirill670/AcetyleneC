/*
* ==============================================================================
*  Name        : ckndeleteconfirmationnote.h
*  Part of     : CKON
*  Interface   : Misc Dialog API
*  Description : Class for displaying a confirmation note to delete a file.
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


#ifndef CKNDELETECONFIRMATIONNOTE_H
#define CKNDELETECONFIRMATIONNOTE_H

// INCLUDES
#include <eikdialg.h>
#include <CknObjectType.h>

// FORWARD DECLARATIONS
class CGulIcon;

/**
*  Class for displaying a confirmation note to delete a file.
*  Special processing is required for the filename string to truncate it inside quotes.
*
*  @lib CKNDLG.LIB
*  @since Series90 1.0
*/
class CCknDeleteConfirmationNote : public CEikDialog
	{
public:
		/**
		* Runs the dialog with a custom message resource and custom buttons.
		* @param aMessageRid - The resource id of the dialog message string.
		* @param aObject - The name of the file or object to be deleted. Shown as text in the dialog.
		*				 Must not be empty.
		* @param aButtonsRid - The id of the button resource to be used by the dialog
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C static TBool RunDlgLD(TInt aMessageRid, const TDesC& aObject, TInt aButtonsRid);

		/**
		* Runs the dialog with a custom message string and custom buttons.
		* @param aMessage - The dialog message string.
		* @param aObject - The name of the file or object to be deleted. Shown as text in the dialog.  
		*				 Must not be empty.
		* @param aButtonsRid - The id of the button resource to be used by the dialog
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C static TBool RunDlgLD(const TDesC& aMessage, const TDesC& aObject, TInt aButtonsRid);

		/**
		* Runs the dialog to confirm deletion of a file or folder. The message and buttons
		* resources are determined from the type of the file passed in aFileName. If the 
		* file/folder does not exist the dialog uses the default resource.
		* @param aFilename - The full path and name of the file or folder to be deleted. 
		* <BR><B>Type of return value:</B> TBool
		*/
		IMPORT_C static TBool RunDlgLD(const TFullName& aFileName);

		/**
		* Destructor.
		*/
		virtual ~CCknDeleteConfirmationNote();
	protected:
	// from CEikDialog
		/**
		* Initialises the layout of the delete confirmation dialog.
		*/
		void PreLayoutDynInitL();
	private:
		CCknDeleteConfirmationNote();
		CCknDeleteConfirmationNote(TInt aMessageRid, const TDesC& aFilename);
		CCknDeleteConfirmationNote(const TDesC& aMessage, const TDesC& aFilename);
		TInt GetMessageRidForObjectType(TCknObjectType aObjectType) const;
		TInt GetButtonResourceForObjectType(TCknObjectType aObjectType) const;
	private:
		const TDesC* iFilename;		///< The filename passed in to display (not owned).
		const TDesC* iMessage;		///< The message passed in to display (not owned).
		TInt iMessageRid;			///< The resource id of the dialog message string.
		HBufC* iMessageBuf;			///< A buffer to load in message string from resources (owned).
		const CGulIcon* iIcon;		///< Icon to display in the dialog (owned).
		TInt iButtonsResource;		///< The id of the button resource used by the dialog
	};


#endif	// CKNDELETECONFIRMATIONNOTE_H

// End of File
