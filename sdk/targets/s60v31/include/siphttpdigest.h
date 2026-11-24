/*
* ==============================================================================
*  Name        : siphttpdigest.h
*  Part of     : SIP Client
*  Interface   : SDK API, SIP Client API
*  Description : 
*  Version     : 1.0
*
*  Copyright (c) 2004 Nokia Corporation.
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

#ifndef CSIPHTTPDIGEST_H
#define CSIPHTTPDIGEST_H

// INCLUDES 
#include <e32base.h>
#include "_sipcodecdefs.h"

// FORWARD DECLARATIONS
class CSIP;
class MSIPHttpDigestChallengeObserver;

// CLASS DECLARATION

/**
* @publishedAll
* @released
*
* Class for managing SIP HTTP Digest security settings.
* Class provides functions for setting/removing
* HTTP Digest security mechanism related parameters.
* If the user does not use the class for the providing credentials for the
* received challenges, an error will be returned to the original request in
* case it was challenged.
* 
* Note that the user will be asked to provide credentials one realm
* at the time.
*
*  @lib sipclient.lib
*/
class CSIPHttpDigest : public CBase
	{
	public: // Constructors and destructor
	
		/**
		* Two-phased constructor.
		* @param aSIP a handle to SIP server
		* @param aObserver an observer for the received challenges
		* @return New object, ownership is transferred.
		*/
		IMPORT_C static CSIPHttpDigest*
			NewL(CSIP& aSIP,
				 MSIPHttpDigestChallengeObserver& aObserver);
				 
		/**
		* Two-phased constructor.
		* @param aSIP a handle to SIP server
		* @param aObserver an observer for the received challenges
		* @return New object, ownership is transferred.
		*/
		IMPORT_C static CSIPHttpDigest*
			NewLC(CSIP& aSIP,
				  MSIPHttpDigestChallengeObserver& aObserver);
				  
		IMPORT_C ~CSIPHttpDigest();

	public: // New functions

        /**
		* Sets credentials for the realm of the outbound proxy.
		* Must be used in case the realm is the realm of the outbound proxy.
		* The user can set credentials only upon request from the
		* SIP implementation.
		* @pre aOutboundProxy, aRealm, aUsername and aPasswd must not be empty
		*	   descriptors.
		* @param aOutboundProxy an outbound proxy (FQDN or IP address)
		* @param aRealm servers's realm
		* @param aUsername user's name
		* @param aPasswd user's password for the given server's realm
		* @leave KErrNoMemory if out of memory
		* @leave KErrArgument if some of the parameters is an empty descriptor
		* @leave KErrSIPResourceNotAvailable if a required object has been
		*		 deleted
		*/
		IMPORT_C void SetCredentialsL(const TDesC8& aOutboundProxy,
			                          const TDesC8& aRealm,
			                          const TDesC8& aUsername,
			                          const TDesC8& aPasswd);
			            
       /**
		* Sets parameters for the realm. 
		* The user can set credentials only upon request from the
		* SIP implementation.
		* @pre aRealm, aUsername and aPasswd must not be empty descriptors.
		* @param aRealm servers's realm
		* @param aUsername user's name
		* @param aPasswd user's password for the given server's realm
		* @leave KErrNoMemory if out of memory
		* @leave KErrArgument if some of the parameters is an empty descriptor
		* @leave KErrSIPResourceNotAvailable if a required object has been
		*		 deleted
		*/
		IMPORT_C void SetCredentialsL(const TDesC8& aRealm,
			                          const TDesC8& aUsername,
			                          const TDesC8& aPasswd);

        /**
		* Removes all set credentials for the realm 
		* @pre aRealm must not be an empty descriptor
		* @param aRealm servers's realm
		* @return KErrNone if no error
		*		  KErrArgument if aRealm is an empty descriptor
		*		  KErrNoMemory if out of memory
		*		  KErrNotFound if the given realm was not found
        */
		IMPORT_C TInt RemoveCredentials(const TDesC8& aRealm);
		
        /**
		* Removes all set credentials by the user
		* @return KErrNone if succesful; KErrNoMemory if out of memory 
        */
		IMPORT_C TInt RemoveCredentials();
					                                                        
		/**
		* Sets the observer	to listen for the possible received
		* challenges.
		* @param aObserver an observer for the received challenges. 
		*/
		IMPORT_C void SetObserver(MSIPHttpDigestChallengeObserver& aObserver);
		
		/**
		* Ignores the challenge for the realm. As a result the error will be
		* generated to the original request in case 
		* @pre aRealm must not be an empty descriptor
		* @param aRealm a realm for which the challenge was ignored
		* @return KErrNone if no error
		*		  KErrNotFound if the given realm was not found
		*		  KErrArgument if aRealm is an empty descriptor
		*/
		IMPORT_C TInt IgnoreChallenge(const TDesC8& aRealm);

	public: // New functions, for internal use

		void CSIPDeleted();

		void SetCredentialParamsL(const TDesC8& aRealm,
				                  const TDesC8& aUsername,
				                  const TDesC8& aPasswd,
				                  const TDesC8& aOutboundProxy) const;

		TInt RemoveCredentialParams(const TDesC8& aRealm) const;

	private:

        CSIPHttpDigest(CSIP& aSIP);
		CSIPHttpDigest(const CSIPHttpDigest& aHttpDigest);
		CSIPHttpDigest& operator=(const CSIPHttpDigest& aHttpDigest);

		void ConstructL(MSIPHttpDigestChallengeObserver& aObserver);
          
    private: // Data

        CSIP* iSIP;
	};

#endif
