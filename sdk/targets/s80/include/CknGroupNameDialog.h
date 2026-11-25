/*
* ==============================================================================
*  Name        : ckngroupnamedialog.h
*  Part of     : CKON
*  Interface   : 
*  Description : Dialog for editing group names.
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


#ifndef CKNGROUPNAMEDIALOG_H
#define CKNGROUPNAMEDIALOG_H
#include "MEikDialogCancelInterface.h"
// INCLUDES
#include <eikdialg.h>

// CONSTANTS
const TInt KMaxGroupNameLength=256;

/**
*  Shows a dialog for editing group names.
*
*  Takes in a text array for existing group names and checks that the new name
*  does not clash with any of them.
*
*  @lib ckndlg.lib
*  @since Series90 1.0
*/
class CCknGroupNameDialog : public CEikDialog, public MEikDialogCancelInterface
	{
	public:
		/**
		 * Runs the group name dialog in either "New Group" or "Rename Group" mode. 
		 * The dialog will return the name for a new group or the new name for an existing group.
		 * This name will be checked for uniqueness among the array of existing group names passed 
		 * into the dialog. If run in "Rename" mode, the dialog will accept a change of case on the 
		 * original group name.
		 *             
		 * @param aGroupName Reference to a descriptor used to return the new name of the group
		 *			   If aGroupName contains text, the dialog is run as Rename Group Dialog,
		 *             If aGroupName is empty, the dialog is run as New Group Dialog
		 *       
		 * @param aExistingNames An array of the existing group names used to ensure that the new name
		 *             is unique
		 *
		 * @return ETrue if the user presses OK, EFalse if the user presses Cancel
		 *			   If ETrue, aGroupName contains the new group name, if EFalse, the contents 
		 *             of aGroupName are undefined
		 */
		IMPORT_C static TBool RunDlgLD(TDes& aGroupName, 
									   MDesCArray* aExistingNames);
		/**
		 * Runs the group name dialog in either "New Group" or "Rename Group" mode. 
		 * The dialog will return the name for a new group or the new name for an existing group.
		 * This name will be checked for uniqueness among the array of existing group names passed 
		 * into the dialog. If run in "Rename" mode, the dialog will accept a change of case on the 
		 * original group name.
		 *             
		 * @param aGroupName Reference to a descriptor used to return the new name of the group
		 *			   If aGroupName contains text, the dialog is run as Rename Group Dialog,
		 *             If aGroupName is empty, the dialog is run as New Group Dialog
		 *       
		 * @param aExistingNames An array of the existing group names used to ensure that the new name
		 *             is unique
		 *
		 * @param aDefaultGroupName If this is a new group then this argument specifies the
		 *             default name for the group. If this is an empty string then the default
		 *             is chosen by the dialog i.e. it behaves like 
		 *             TBool RunDlgLD(TDes& aGroupName, MDesCArray* aExistingNames);
		 *
		 * @return ETrue if the user presses OK, EFalse if the user presses Cancel
		 *			   If ETrue, aGroupName contains the new group name, if EFalse, the contents 
		 *             of aGroupName are undefined
		 */
		IMPORT_C static TBool RunDlgLD(TDes& aGroupName,MDesCArray* aExistingNames,
			const TDesC& aDefaultGroupName);


		/**
		* From CCoeControl Get the help context for displaying help.
		* @param aContext pass in to get the UID and context
		*/
		IMPORT_C void GetHelpContext(TCoeHelpContext& aContext) const;
		
		/**
		 * Runs the group name dialog in either "New Group" or "Rename Group" mode. 
		 * The dialog will return the name for a new group or the new name for an existing group.
		 * This name will be checked for uniqueness among the array of existing group names passed 
		 * into the dialog. If run in "Rename" mode, the dialog will accept a change of case on the 
		 * original group name.
		 *             
		 * @param aGroupName Reference to a descriptor used to return the new name of the group
		 *			   If aGroupName contains text, the dialog is run as Rename Group Dialog,
		 *             If aGroupName is empty, the dialog is run as New Group Dialog
		 *       
		 * @param aExistingNames An array of the existing group names used to ensure that the new name
		 *             is unique
		 *
		 * @param aDefaultGroupName If this is a new group then this argument specifies the
		 *             default name for the group. If this is an empty string then the default
		 *             is chosen by the dialog i.e. it behaves like 
		 *             TBool RunDlgLD(TDes& aGroupName, MDesCArray* aExistingNames);
		 *
		 * @param aNewGroupDialogCancelInterface This interface provides a mechanism where the NewGroupDialog
		 *			   can be dismissed by another class by calling CCknGroupNameDialog::CancelDialog() by
		 *			   passing in an MEikDialogCancelInterface instance
		 *
		 *
		 * @return ETrue if the user presses OK, EFalse if the user presses Cancel
		 *			   If ETrue, aGroupName contains the new group name, if EFalse, the contents 
		 *             of aGroupName are undefined
		 *
		 *
		 */
		IMPORT_C static TBool RunDlgLD(MEikDialogCancelInterface*& aNewGroupDialogCancelInterface, TDes& aGroupName,
		MDesCArray* aExistingNames,	const TDesC& aDefaultGroupName);
		
		/*
		*	Implementation of the MEikDialogCancelInterface, this function allows the 
		*	cancelling of this dialog from a class that passes in a MEikDialogCancelInterface instance
		*   @see MEikDialogCancelInterface
		*/
		void CancelDialog();
	 
	private: 
	    CCknGroupNameDialog(TDes& aGroupName, 
					    MDesCArray* aExistingNames, const TDesC& aDefaultGroupName);

		void ReseedNewGroupNameL();
		void GetNextNewGroupNameL(TInt aNumber, TDes& aNewGroupName);
		TBool IsNewGroupNameValidL(TInt& aInfoprintResourceId);
		TBool GroupNameExists(TDesC& aProposedName);
		void PreLayoutDynInitL();
		TBool OkToExitL(TInt aButtonId);

	private:
		MDesCArray* iArrayExistingNames;
		TDes& iNewName;
		TBuf<KMaxGroupNameLength> iDefaultName;
	};


#endif	// CKNGROUPNAMEDIALOG_H

// End of File
