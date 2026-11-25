/*
* ==============================================================================
*  Name        : muiuserv.h
*  Part of     : Utilities
*  Interface   : Utilities API
*  Description : MTM server utilities
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


#ifndef MUIUSERV_H
#define MUIUSERV_H

// INCLUDES
#include <MSVIPC.H>


// FORWARD DECLARATIONS
class CMsvSession;

/**
*  Provides a number of static function for access messaging accounts and servers. 
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class MsvUiServiceUtilities
{
	public:

		/**
		* Gets the list of accounts
		* @since ?Series90_version
		* @param aSession The MsvSession to use
		* @param aAlwaysListHidden ETrue if hidden accounts are required, EFalse otherwise
		* @return The retrieved array of entries
		* <BR><B>Type of return value:</B> CMsvEntrySelection*
		*/
		IMPORT_C static CMsvEntrySelection* GetListOfAccountsL(CMsvSession& aSession, TBool aAlwaysListHidden=EFalse);

		/**
		* Gets the list of accounts with specified MTM
		* @since ?Series90_version
		* @param aSession The MsvSession to use
		* @param aMtm The MTM to use
		* @param aAlwaysListHidden ETrue if hidden accounts are required, EFalse otherwise
		* @return The retrieved array of entries
		* <BR><B>Type of return value:</B> CMsvEntrySelection*
		*/
		IMPORT_C static CMsvEntrySelection* GetListOfAccountsWithMTML(CMsvSession& aSession, TUid aMtm, TBool aAlwaysListHidden=EFalse);

		/**
		* Returns the ID of the default service for the specified MTM
		* @since ?Series90_version
		* @param aSession The MsvSession to use
		* @param aMtm The MTM to use
		* @param aFindFirstServiceIfNoDefault If ETrue, uses first service if no default, otherwise EFalse
		* @return The ID of the default service
		* <BR><B>Type of return value:</B> TMsvId
		*/
		IMPORT_C static TMsvId DefaultServiceForMTML(CMsvSession& aSession, TUid aMtm, TBool aFindFirstServiceIfNoDefault);

		/**
		* Sets the default service for the specified MTM
		* @since ?Series90_version
		* @param aSession The MsvSession to use
		* @param aMtm The MTM to use
		* @param aServiceId The Service ID to use as the default
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C static void SetDefaultServiceForMTML(CMsvSession& aSession, TUid aMtm, TMsvId aServiceId);
	private:
		static CMsvEntrySelection* DoGetListOfAccountsL(CMsvSession& aSession, TUid aMtm, TBool aAlwaysListHidden=EFalse);
};


#endif	// MUIUSERV_H

// End of File
