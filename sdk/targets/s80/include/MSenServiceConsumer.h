/*
 * =========================================================================
 *  Name     : MSenServiceConsumer.h
 *  Part of  : MSenServiceConnection
 *  Created  : 2004-06-08 by Nokia
 *  Descr.   :
 *
 *  Version : 
 *   $Source: /projects/serene/sen/ServiceConnection/inc/MSenServiceConsumer.h,v $
 *   $Date: 2004/07/31 05:29:22 $
 *   $Revision: 1.1 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef M_SEN_SERVICE_CONSUMER_H
#define M_SEN_SERVICE_CONSUMER_H

// CLASS DECLARATION

#include <e32std.h>

/**
 * An interface class for SenServiceConnection callbacks 
 * from remote service
 *
 */

class MSenServiceConsumer
    {
public:
	enum TError
		{
		EInitError = 1,
		ESubmitError
		};

public:

    /**
     * Receive response to a request submitted. 
     *
     * @param aMessage incoming message. The ownerships
	 * is transfered with the message ,)
     */    
    virtual void HandleMessageL(const TDesC8& aMessage) = 0;

    /**
     * Error occured. Error codes are of type TError:
     * EInitError       Initialization failed.
     * ESubmitError     Submitting a message failed.
     *
     * @param aError error code.
     */ 
    virtual void HandleErrorL(const TDesC8& aMessage) = 0;


	/**
	 * This method is called when the status of the connection
	 * to the service changes.
	 * @param aStatus is connection state indicator, which 
	 * could be specified by the actual service invocation framework 
	 * implementation. The following status codes are possible for 
	 * any installed framework:
	 *
	 * STATUS_NEW (0)
	 * STATUS_VALID (1) ( == "initialized", ready to be used)
	 * In addition many frameworks for web services may notify about
	 * STATUS_EXPIRED (2)
	 */
	virtual void SetStatus(const TInt aStatus) = 0;

    };

#endif // M_SEN_SERVICE_CONSUMER_H
            
// End of File
