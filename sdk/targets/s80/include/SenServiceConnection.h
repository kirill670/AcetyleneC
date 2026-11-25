/*
 * =========================================================================
 *  Name     : SenServiceConnection.h
 *  Part of  : SenServiceConnection
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version : 
 *   $Source: /projects/serene/sen/ServiceConnection/inc/SenServiceConnection.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.7 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef SEN_SERVICE_CONNECTION_H
#define SEN_SERVICE_CONNECTION_H

//  INCLUDES
#include <e32base.h> // for CActive
#include <badesca.h>
#include <MSenServiceConsumer.h>
#include <SenFragment.h>
#include <MSenServiceDescription.h>
#include <SenSoapEnvelope.h>

// FORWARD DECLARATIONS
class CSenServicePattern;


// CONSTANTS
static const TInt KErrSenNotInitialized				=	-22001;
static const TInt KErrSenServiceConnectionBusy		=	-22002;

static const TInt KErrConnectionInitializing		=	-22101;
static const TInt KErrConnectionExpired				=	-22102;

static const TInt KSenConnectionStatusNew			=	0;
static const TInt KSenConnectionStatusReady			=	1;
static const TInt KSenConnectionStatusExpired		=	2;

// CLASS DECLARATION

/**
 * The class for connecting with, and using services provided 
 * by the Serene Framework (which may have one or more service
 * frameworks installed as ECOM plugins, like the ID-WSF framework).
 * 
 */
class CSenServiceConnection : public CActive, public MSenFragment
    {
public: // Constructors

	/**
     * Two-phased constructor. URI of the service is provided.
     * Authentication is done using one of the identity providers 
     * introduced in the list if it is supplied.
	 *
	 * 
     *
     * @param aObserver		connection observer.
	 *
     * @param aContract		aContract of the service, a URI.
	 *
     */
    IMPORT_C static CSenServiceConnection* NewL(MSenServiceConsumer& aObserver,
                                                const TDesC8& aContract);


    IMPORT_C static CSenServiceConnection* NewLC(MSenServiceConsumer& aObserver,
                                                const TDesC8& aContract);

    /**
     * Two-phased constructor. URI of the service is provided.
     * Authentication is done using one of the identity providers 
     * introduced in the list if it is supplied. 
     *
     * @param				aObserver connection observer.
	 *
     * @param				aServiceDescription is the description used to
	 * obtain a service connection. Note that the service description may
	 * also be used to define Provider Policy features, which need to be met
	 * for accebtable connection to be initialized.
     *
     * One could set an Identity Provider Id list via Service Description:
	 * This will act as a list of accepted identity providers. If such
	 * list is not provided, the returned service connection is searched without
	 * recommendations. However, if IDP ID list is provided, then the the list's
	 * mode (aStrict is can be true or false) will define how the identity 
	 * provider list will be used.
	 *
	 * The aStrict param of the IDP ID list sets the connection search mode.
	 * If such list is provided, then a service connection can only be
	 * returned, if it matches with one of the given identity provider ID's
	 * (found from the list). If list is not strict (default), then the 
	 * list is only a recommendation, and also other identity provider 
	 * may be used.
	 *
	 *
	 * Please note, that for Basic Web Services, connection is typically wished
	 * from the point-of-view of a "consumer origated policy". In such cases,
	 * The other constructors accepting CSenServicePattern are recommended.
	 *
	 *
     */
    IMPORT_C static CSenServiceConnection* NewL(
						MSenServiceConsumer& aObserver, 
						MSenServiceDescription& aServiceDescription);

    IMPORT_C static CSenServiceConnection* NewLC(
						MSenServiceConsumer& aObserver, 
						MSenServiceDescription& aServiceDescription);

    /*
	 * The ServicePattern versions of static constructors. Please note,
	 * that these versions are mainly ment to be used in case of Basic
	 * Web Services, which may require custom "consumer policy" features
	 * to be set for the requested, current connection being initialized. 
	 *
	 * One of the usual cases is the one, where certain application 
	 * pre-determined Internet Access Point (IAP) must be used while
	 * opening new connection. Because CSenServicePattern implements
	 * required MSenConsumerPolicy inteface, users of these constructors
	 * may simply set the consumer-policy-versions of the provided 
	 * by the CSenServicePattern, like SetConsumerIapId(). Please note,
	 * however, that any ConsumerPolicy feature is treater from 
	 * "one-policy-per-client" -point-of-view, and not as a common policy.
	 *
	 * To set permanent information about known WSP, please use the 
	 * CSenXmlServiceDescription, which impelements MSenProviderPolicy 
	 * inteface.
	 *
	 * Please note, that for Basic Web Services, a "NONE" Framework ID
	 * is MANDATORY, in order for a service consumer to obtain a
	 * "frameworkless" connection directly to certain Basic Web Services
	 * Provider (Basic WSP).
	 * .
	 * 
	 */
    IMPORT_C static CSenServiceConnection* NewL(
						MSenServiceConsumer& aObserver, 
						CSenServicePattern& aServicePattern);

    IMPORT_C static CSenServiceConnection* NewLC(
						MSenServiceConsumer& aObserver, 
						CSenServicePattern& aServicePattern);
	

	CSenServiceConnection();

public: 

    /**
     * Send an ASYNCHRONOUS request message to a service. 
	 *
     * Observer will deliver the response message. 
	 *
     * Status codes: 
     * KErrNone						ok
	 *
     * Error codes:
     * KErrSenNotInitialized		connection has not been initialized
     * KErrSenServiceConnectionBusy		connection is already busy with another request
     * KErrNoMemory					out of dynamic memory
     * KSenServiceConnectionExpired		connection is expired and needs to be renewed
	 * KErrConnectionInitializing	connection is new and still initializing
	 *
     * Other error codes are system error codes
     *
     * @param aRequest outgoing request message.
     * @return status/error code.
     */    
    virtual TInt SendL(const TDesC8& aRequest) = 0;


    /**
     * Submit a message via SYNCHRONOUS call to a service. 
	 *
     * The response is the service specific part of the response.
	 * (for WebServices the contents of the SOAP Body).
	 *
     * Status codes: 
     * KErrNone						ok
	 *
     * Error codes:
     * KErrSenNotInitialized		connection has not been initialized
     * KErrSenServiceConnectionBusy		connection is already busy with another request
     * KErrNoMemory					out of dynamic memory
     * KSenServiceConnectionExpired		connection is expired and needs to be renewed
	 * KErrConnectionInitializing	connection is new and still initializing
	 *
     * Other error codes are system error codes
     *
     * @param aRequest outgoing request message.
	 *
	 * @param aResponse the resolved response message to be _stored_ here.

     * @return status/error code.
     */    
    virtual TInt SubmitL(const TDesC8& aRequest, HBufC8*& aResponse) = 0; // API bugfix, 2004-06-01


    /**
     * Validate that SenServiceConnection is ready to be used from the  
	 * Sen Framework point-of-view
	 *
     * Status codes: 
     * KErrNone               ok
	 *
	 *
     * Error codes:
     * KErrSenNotInitialized		connection has not been initialized
     * KErrSenServiceConnectionBusy		connection is already busy with another request
     * KErrNoMemory					out of dynamic memory
	 *
     * Other error codes are system error codes
     *
     * @param aReady indicates that the connection is ready to be used (not expired(?)). // TODO: check this

     * @return status/error code.
     */  	
    virtual TInt IsReady(TBool& aReady) = 0; 


    /**
     * Check if the underlying service has a certain characteristic. 
	 * For example, the application if application is interested in
	 * quering whether or not the service connection is free, it
	 * could call:
	 * _LIT8(KFacetOfFreeService, "urn:framework.com.free:cost");
	 * int err = HasFacet(KFacetOfFreeService, hasFacet);
	 *
	 *
     * Status codes: 
     * KErrNone               ok
	 *
	 *
     * Error codes:
     * KErrSenNotInitialized		connection has not been initialized
     * KErrSenServiceConnectionBusy		connection is already busy with another request
     * KErrNoMemory					out of dynamic memory
	 *
     * Other error codes are system error codes
     *
	 * @param aURI			checked input, a characteristic	
     * @param aHasFacet		will indicate that the underlying service has a 
							certain characteristic.

     * @return status/error code.
     */  	
    virtual TInt HasFacet(const TDesC8& aURI, TBool& aHasFacet) = 0; 


    /**
     * Set the flag that indicates that the application
	 * wishes to receive complete messages from the service.
	 *
     * Status codes: 
     * KErrNone               ok
	 *
	 *
     * Error codes:
     * KErrSenNotInitialized		connection has not been initialized
     * KErrSenServiceConnectionBusy		connection is already busy with another request
     * KErrNoMemory					out of dynamic memory
	 *
     * Other error codes are system error codes
     *
	 * @param aCompleteOnOff		If set to ETrue, the user of this ServiceConnection
	 *								will be given full service messages; 
	 *								If set to EFalse only the servicespecific content 
	 *								is forwarded to the application. 
     *
	 *								The default behaviour is as for complete = EFalse. 

     * @return status/error code.
     */  	
    virtual TInt CompleteServerMessagesOnOff(const TBool& aCompleteOnOff) = 0;



	/*
  	 * Send a SOAP message to the service. The SOAPEnvelope may contain propietory 
	 * headers. The system will augment the message with the appropiate headers
	 * specified in the service invocation framework, so a client application
	 * should add only non-standard headers; and IF it doesn't need to set such
	 * headers it is STRONGLY recommended to use send(TDesC8&), which is ment for this.
	 * 
	 * This is an ASYNCHRONOUS function, that returns immediately.
	 * If the service responds with another message the ServiceConnection
	 * will call the handleResponse method of the consumer.
	 * 
	 * @param	aMessage 
	 * SOAPEnvelope with the service specific message without any framework wrapping
	 *
	 * @param	aResponseTo
	 * This is a ref-to-ptr where string will be allocated. String includes 
	 * the complete response from the server, even if	the user of the 
	 * ServiceConnection has issued completeServerMessages(false).
	 * 
	 *
     * Status codes: 
     * KErrNone						ok
	 *
     * Error codes:
     * KErrSenNotInitialized		connection has not been initialized
     * KErrSenServiceConnectionBusy		connection is already busy with another request
     * KErrNoMemory					out of dynamic memory
     * KSenServiceConnectionExpired		connection is expired and needs to be renewed
	 * KErrConnectionInitializing	connection is new and still initializing
	 *
     * Other error codes are system error codes
     *
	 * @return status/error code
	 */
	virtual TInt SendL(CSenSoapEnvelope& aMessage) = 0;

	/*
	 * Submit a SOAP message to the service. This is a SYNCHRONOUS call
	 * so the method returns a new SOAP message that was received from the
	 * service.
	 * 
	 * @param	aMessage 
	 * SOAPEnvelope with the service specific message without any framework wrapping
	 *
	 * @param	aResponseTo
	 * This is a ref-to-ptr where string will be allocated. String includes 
	 * the complete response from the server, even if	the user of the 
	 * ServiceConnection has issued completeServerMessages(false).
	 *
     * Status codes: 
     * KErrNone						ok
	 *
     * Error codes:
     * KErrSenNotInitialized		connection has not been initialized
     * KErrSenServiceConnectionBusy		connection is already busy with another request
     * KErrNoMemory					out of dynamic memory
     * KSenServiceConnectionExpired		connection is expired and needs to be renewed
	 * KErrConnectionInitializing	connection is new and still initializing
	 *
     * Other error codes are system error codes
     *
	 * @return status/error code
	 */
	virtual TInt SubmitL(CSenSoapEnvelope& aMessage, HBufC8*& aResponseTo) = 0;

    /**
     * Gets the current Session info
	 *
     * Status codes: 
     * KErrNone               ok
	 *
	 *
     * Error codes:
     * KErrSenNotInitialized		connection has not been initialized
     * KErrSenServiceConnectionBusy		connection is already busy with another request
     * KErrNoMemory					out of dynamic memory
	 *
     * Other error codes are system error codes
     *
     * @param aServiceDescription Contains the servicedescription on return
     * @return status/error code.
     */  	
    virtual TInt ServiceDescriptionL(HBufC8*& aServiceDescription) = 0; 

    };

#endif //SEN_SERVICE_CONNECTION_H
            
// End of File
