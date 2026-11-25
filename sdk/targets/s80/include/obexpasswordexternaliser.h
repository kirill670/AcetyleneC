// $Workfile: obexpasswordexternaliser.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//


#include <e32std.h> 
#include <msvapi.h>     
class ObexPasswordExternaliser
/**
Utility class for accessing the password stored in the service entry. Only contains static member functions, so not a
C class.

@internalTechnology
@released
*/
	{
public:

	/**
	 * Static getter function to get the ObexPassword associated with the given entry. If the password stream doesn't exist,
	 * a zero-length HBufC is returned. Ownership of the returned descriptor is passed to the caller, and is pushed onto the
	 * cleanup stack.
	 *
	 * @param aEntry CMsvEntry whose owning service entry's password is to be set
	 * @return HBufC containing the password (zero length if not set). Ownership is passed to the caller, and left on the cleanup stack
	 * @exception KErrXXX system-wide error codes
	 */

	IMPORT_C static HBufC* GetPasswordLC(CMsvEntry& aEntry);
	
	/**
	* Static setter function to set the ObexPassword associated with the given entry. If the length of the password is
	* zero, then the password is cleared
	*
	* @param aEntry CMsvEntry whose owning service entry's password is to be set
	* @param aPassword the password to set
	* @exception KErrXXX system-wide error codes
	*/
	
	IMPORT_C static void SetPasswordL(CMsvEntry& aEntry, const TDesC& aPassword);
	
	/**
	 * Resets the password associated with the given entry. Does nothing if there is no password.
	 *
	 * @param aEntry CMsvEntry whose owning service entry's password is to be reset
	 * @exception KErrXXX system-wide error codes
	 */
	
	IMPORT_C static void ResetPasswordL(CMsvEntry& aEntry);

	/**
	 * Static getter function to get the ObexPassword associated with the given MTM UID. The zeroth service entry is assumed.
	 * If the password stream doesn't exist,a zero-length HBufC is returned. Ownership of the returned descriptor is passed
	 * to the caller, and is pushed onto the cleanup stack.
	 *
	 * @param aSessionObserver a session observer
	 * @param aMtmUid UID of the MTM whose password is to be set
	 * @return HBufC containing the password (zero length if not set). Ownership is passed to the caller, and left on the cleanup stack
	 * @exception KErrXXX system-wide error codes
	 */	
	
	IMPORT_C static HBufC* GetPasswordLC(CMsvSession& aSession, const TUid& aMtmUid);
	
	/**
	 * Static setter function to set the ObexPassword associated with the given entry. If the length of the password is
	 * zero, then the password is cleared
	 *
	 * @param aEntry aSessionObserver A session observer
	 * @param aMtmUid Uid of the MTM whose password is to be set
	 * @param aPassword the password to set
	 * @exception KErrXXX system-wide error codes
	 */
		
	IMPORT_C static void SetPasswordL(CMsvSession& aSession, const TUid& aMtmUid, const TDesC& aPassword);
	
	/**
	 * Resets the password associated with the given entry. Does nothing if there is no password.
	 *
	 * @param aEntry aSessionObserver A session observer
	 * @param aMtmUid Uid of the MTM whose password is to be set
	 * @exception KErrXXX system-wide error codes
	 */
	
	IMPORT_C static void ResetPasswordL(CMsvSession& aSession, const TUid& aMtmUid);

	/**
	 * Returns a CMsvEntry pointing to the zeroth service entry associated with aMtmUid. Ownership of the returned CMsvEntry
	 * is passed to the caller, and it is left on the cleanup stack.
	 *
	 * @param aSession a session
	 * @param aSessionObserver A session observer
	 * @param aMtmUid Uid of the MTM whose service entry is to be found
	 * @return A newly created CMsvEntry
	 */
	
	IMPORT_C static CMsvEntry* GetServiceEntryLC(CMsvSession& aSession, const TUid& aMtmUid);
	
	/**
	 * Static getter function to get the ObexPassword from the given service entry. If the password stream doesn't exist,
	 * a zero-length HBufC is returned. Ownership of the returned descriptor is passed to the caller, and is pushed onto the
	 * cleanup stack.
	 *
	 * @param aServiceEntry CMsvEntry set to the service entry containing the password
	 * @return HBufC containing the password (zero length if not set of cannot be read). Ownership is passed to the caller, and left on the cleanup stack
	 * @exception KErrXXX system-wide error codes
	 */
	
	IMPORT_C static HBufC* GetPasswordFromServiceEntryLC(CMsvEntry& aServiceEntry);

	/**
	 * Static setter function to set the ObexPassword associated with the given entry. If the length of the password is
	 * zero, then the password is cleared. Calling this function causes the entry to be changed, too, which allows the watcher
	 * to detect the change to the password.
	 *
	 * @param aServiceEntry The service entry to set the password into
	 * @param aPassword the password to set
	 * @exception KErrXXX system-wide error codes
	 */

	IMPORT_C static void SetPasswordFromServiceEntryL(CMsvEntry& aEntry, const TDesC& aPassword);
	};
