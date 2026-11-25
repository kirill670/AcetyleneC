/*
 * =========================================================================
 *  Name     : SenServiceManager.h
 *  Part of  : SenServiceManager
 *  Created  : 2004/06/14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/ServiceManager/inc/SenServiceManager.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.4 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */


#ifndef SEN_SERVICE_MANAGER_H
#define SEN_SERVICE_MANAGER_H

//  INCLUDES
#include <e32base.h> // for CActive
#include <e32std.h>  // for RPointerArray
#include <badesca.h>
#include <MSenServiceConsumer.h>

#include <MSenServiceDescription.h>


// CONSTANTS
static const TInt KSenServiceManagerExpired			=    400;
static const TInt KErrServiceManagerClientNotInitialized	= -22001;
static const TInt KErrServiceManagerClientBusy				= -22002;


// FORWARD DECLARATION
class CSenXmlServiceDescription;
class CSenIdentityProvider;

typedef RPointerArray<CSenXmlServiceDescription> RServiceDescriptionArray;


class CSenServiceManager : public CActive
    {
public: // Constructors

	/**
     * Two-phased constructor. 
     */
    IMPORT_C static CSenServiceManager* NewL();
    IMPORT_C static CSenServiceManager* NewLC();

public: 

	/**
	* Search for services whose ServiceDescriptions 
	* have a matching contract URI.
	* 
	* Status codes: 
	* KErrNone						ok
	* KSenServiceConnectionExpired		connection expired (connection will be 
	*								automatically renewed in SenServiceManager)
	* Error codes:
	* KErrSenNotInitialized		connection has not been initialized
	* KErrSenServiceConnectionBusy		connection is already busy with another request
	* KErrNoMemory					out of dynamic memory
	*
	* Other error codes are system error codes
	*
	* @param	aUri a String which specifies the contract or endpoint of the required
	* 				ServiceDescriptions 
	* @param	aList an array with 0 or more ServiceDescriptions
	*  			The ownership of the array is passed to the caller so before 
	*			the array goes out of scope in the client, the caller must 
	*			call RPointerArray::ResetAndDestroy() on the array to free any entries.
	*
	* @return status/error code.
	*/
    virtual TInt ServiceDescriptionsL(TDesC8& aUri, RServiceDescriptionArray& aList) = 0;

	/**
	* Search for services with a matching ServiceDescription,
	* which can contain any combination of contract, endpoint and facets.
	* 
	* Status codes: 
	* KErrNone						ok
	* KSenServiceConnectionExpired		connection expired (connection will be 
	*								automatically renewed in SenServiceManager)
	* Error codes:
	* KErrSenNotInitialized		connection has not been initialized
	* KErrSenServiceConnectionBusy		connection is already busy with another request
	* KErrNoMemory					out of dynamic memory
	*
	* Other error codes are system error codes
	*
	* @param	aSD a ServiceDescription which specifies the contract and/or 
	*			endpoint and/or facets of the required ServiceDescriptions 
	* @param	aList an array with 0 or more ServiceDescriptions
	*  			The ownership of the array is passed to the caller so before 
	*			the array goes out of scope in the client, the caller must 
	*			call RPointerArray::ResetAndDestroy() on the array to free any entries.
	*
	* @return status/error code.
	*/
	virtual TInt ServiceDescriptionsL(MSenServiceDescription& aSD, RServiceDescriptionArray& aList) = 0;

	/**
	* Used by applications to inform the ServiceManager about a service,
	* for example about an Authentication Service, which typically cannot
	* be discovered through other means.
	*  
	* 
	* Status codes: 
	* KErrNone						ok
	* KSenServiceConnectionExpired		connection expired (connection will be 
	*								automatically renewed in SenServiceManager)
	* Error codes:
	* KErrSenNotInitialized		connection has not been initialized
	* KErrSenServiceConnectionBusy		connection is already busy with another request
	* KErrNoMemory					out of dynamic memory
	*
	* Other error codes are system error codes
	*
	* @param	aSD a ServiceDescription to be registered
	*
	* @return status/error code.
	*/
	virtual TInt RegisterServiceDescriptionL(MSenServiceDescription& aSD) = 0;
	
	/**
	* Used by application to to inform the ServiceManager about a service
	* which no longer is available. The ServiceManager will remove the 
	* service from its database as soon as it is no longer used. 
	* 
	* 
	* Status codes: 
	* KErrNone						ok
	* KSenServiceConnectionExpired		connection expired (connection will be 
	*								automatically renewed in SenServiceManager)
	* Error codes:
	* KErrSenNotInitialized		connection has not been initialized
	* KErrSenServiceConnectionBusy		connection is already busy with another request
	* KErrNoMemory					out of dynamic memory
	*
	* Other error codes are system error codes
	*
	* @param	aSD a ServiceDescription to be unregistered
	*
	* @return status/error code.
	*/
	virtual TInt UnregisterServiceDescriptionL(MSenServiceDescription& aSD) = 0;

	
	/**
	* Register an IdentityProvider for the current active Identity.
	* 
	* Status codes: 
	* KErrNone						ok
	* KSenServiceConnectionExpired		connection expired (connection will be 
	*								automatically renewed in SenServiceManager)
	* Error codes:
	* KErrSenNotInitialized		connection has not been initialized
	* KErrSenServiceConnectionBusy		connection is already busy with another request
	* KErrNoMemory					out of dynamic memory
	*
	* Other error codes are system error codes
	*
	* @param	aProvider an IdentityProvider to be registered
	*
	* @return status/error code.
	*/
	virtual TInt RegisterIdentityProviderL(CSenIdentityProvider& aProvider) = 0;
	
	/**
	* Unregister an IdentityProvider from the current active Identity.
	* 
	* Status codes: 
	* KErrNone						ok
	* KSenServiceConnectionExpired		connection expired (connection will be 
	*								automatically renewed in SenServiceManager)
	* Error codes:
	* KErrSenNotInitialized		connection has not been initialized
	* KErrSenServiceConnectionBusy		connection is already busy with another request
	* KErrNoMemory					out of dynamic memory
	*
	* Other error codes are system error codes
	*
	* @param	aProvider an IdentityProvider to be unregistered
	*
	* @return status/error code.
	*/
	virtual TInt UnregisterIdentityProviderL(CSenIdentityProvider& aProvider) = 0;
	

	/**
	* Associate a service to an IdentityProvider.
	* 
	* Status codes: 
	* KErrNone						ok
	* KSenServiceConnectionExpired		connection expired (connection will be 
	*								automatically renewed in SenServiceManager)
	* Error codes:
	* KErrSenNotInitialized		connection has not been initialized
	* KErrSenServiceConnectionBusy		connection is already busy with another request
	* KErrNoMemory					out of dynamic memory
	* 
	* @param aServiceID the contract or endpoint of a service
	* @param aProviderID the id of an IdentityProvider
	*
	* @return status/error code.
	*/
	virtual TInt AssociateServiceL(TDesC8& aServiceID, TDesC8& aProviderID) = 0;

	virtual TInt AssociateServiceL(const TDesC& aServiceID, const TDesC& aProviderID) = 0;
	
	/**
	* Dissociate a service from an IdentityProvider.
	* 
	* Status codes: 
	* KErrNone						ok
	* KSenServiceConnectionExpired		connection expired (connection will be 
	*								automatically renewed in SenServiceManager)
	* Error codes:
	* KErrSenNotInitialized		connection has not been initialized
	* KErrSenServiceConnectionBusy		connection is already busy with another request
	* KErrNoMemory					out of dynamic memory
	* 
	* @param aServiceID the contract or endpoint of a service
	* @param aProviderID the id of an IdentityProvider
	*
	* @return status/error code.
	*/
	virtual TInt DissociateServiceL(TDesC8& aServiceID, TDesC8& aProviderID) = 0;

	virtual TInt DissociateServiceL(const TDesC& aServiceID, const TDesC& aProviderID) = 0;

	/**
	 * Install a ServiceInvocationFramework. 
	 * 
	 * Status codes: 
	 * KErrNone						ok
	 * KSenServiceConnectionExpired		connection expired (connection will be 
	 *								automatically renewed in SenServiceManager)
	 * Error codes:
	 * KErrSenNotInitialized		connection has not been initialized
	 * KErrSenServiceConnectionBusy		connection is already busy with another request
	 * KErrNoMemory					out of dynamic memory
	 * 
	 * @param aFrameworkId is the "cue" of the ECOM plugin being installed 
	 * (existing in ECOM default dir)
	 *
	 * @return status/error code.
	 */
	virtual TInt InstallFrameworkL(TDesC8& aFrameworkId) = 0;

	
	CSenServiceManager();


    };

#endif //SEN_SERVICE_MANAGER_H
            
// End of File
