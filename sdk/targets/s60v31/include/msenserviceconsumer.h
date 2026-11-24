/*
* ==============================================================================
*  Name        : MSenServiceConsumer.h
*  Part of     : Web Services Connection
*  Interface   : 
*  Description : 
*  Version     : 
*
*  Copyright © 2002-2005 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/

#ifndef M_SEN_SERVICE_CONSUMER_H
#define M_SEN_SERVICE_CONSUMER_H

// CLASS DECLARATION

/**
* An interface class for SenServiceConnection callbacks
* from remote service
*/
class MSenServiceConsumer
    {
	public: 
		
		// New functions
		
    	/**
     	* Receive response to a request submitted.
        * @param aMessage incoming message. The ownerships
	 	* is transfered with the message ,)
     	*/
    	virtual void HandleMessageL(const TDesC8& aMessage) = 0;

    	/**
     	* Error occured. 
        * @param aError error code.
	    * Error codes are some of the following:
	 	* KErrSenNotInitialized				Connection hasn't been initialized.
     	* KErrConnectionInitializing        Connection is still initializing.
     	* KErrSubmitting					Submitting a message failed, 
	 	*									e.g. tried to send a NULL message.
	 	* KErrConnectionExpired				Connection has expired and needs to be
	 	*									renewed.
	 	* KErrSenSoapFault					A SOAP fault occurred, aMessage should 
	 	*									contain more detailed information.
	 	* KErrSenInternal					Internal error in Web Services 
	 	*									framework
	 	* KErrUnknown						An unexpected major error has occurred
	 	*									and cause is unknown.
	 	* Other possible error codes can be HTTP error codes or 
	 	* system-wide Symbian error codes.
     	*/
    	virtual void HandleErrorL(const TInt aErrorCode, 
								  const TDesC8& aMessage) = 0;

		/**
	 	* This method is called when the status of the connection
	 	* to the service changes.
	 	* @param aStatus is connection state indicator, which
	 	* could be specified by the actual service invocation framework
	 	* implementation. The following status codes are possible for
	 	* any installed framework:
	    * KSenConnectionStatusNew			   Connection is being initialized, but not yet ready.
	 	* KSenConnectionStatusReady			   Connection is ready to be used. For example, SubmitL()
	 	*                                      and SendL() methods (depending of framework) are in
	 	*                                      invocable state.
	 	* KSenConnectionStatusExpired          Connection is expired. Typically, a new connection
	 	*                                      needs next to be initialized in order to communicate
	 	*                                      with the underlying service behind this service
	 	*                                      connection.
 	 	*/
		virtual void SetStatus(const TInt aStatus) = 0;
    };

// M_SEN_SERVICE_CONSUMER_H
#endif

// End of File
