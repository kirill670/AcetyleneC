// TCTTOKENOBJECTHANDLE.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __TCTTOKENOBJECTHANDLE_H__
#define __TCTTOKENOBJECTHANDLE_H__

#include <e32std.h>
#include <ct/tcttokenhandle.h>

/**@ingroup ct */
/**@{ */

/**
 * This class defines a handle to an object represented by a class which is
 * a subclass of the MCTTokenObject class. 
 *
 * The handle identifies the object, not the instance of the subclass of MCTTokenObject
 * used to manage that object.
 * It is guaranted to be unique within the context of a specific device
 * (i.e. mobile phone, ...) at a specific point in time. This limitation in time is
 * due to the fact that objects can be created and destroyed. We can't guarantee that a 
 * handle will still point to the same object after we add or remove one or more
 * objects from the store from where the object comes from.
 * It is guaranteed however that the addition of objects to the store will not affect
 * the validity of the handles that were obtained previously.
 *
 * For instance, if the object is a certificate 
 * in a certificate store, the subclass of MCTTokenObject will be CCTCertInfo and
 * the handle will identify the certificate in the certificate store, not the instance
 * of CCTCertInfo.
 *
 * The handle is especially useful for communication across process boundaries.
 * A process A can get a handle to an object, give that handle to process B.
 * B can then try to get the same object using the handle..
 */
class TCTTokenObjectHandle
	{
public:
	/**
	 * This creates an invalid handle. An invalid handle has an invalid
	 * iTokenHandle and an iObjectId equal to 0.
	 */
	IMPORT_C TCTTokenObjectHandle();
	/**
	 * This creates a handle.
	 * @param aTokenHandle. The handle that identifies the Token where the object is stored.
	 * @param aObjectId. The identifier of the object within the Token.
	 */
	IMPORT_C TCTTokenObjectHandle(TCTTokenHandle aTokenHandle, TInt aObjectId);

public:
	/**
	 * The handle that identifies the Token where the object is stored.
	 */
	TCTTokenHandle iTokenHandle;
	/**
	 * The identifier of the object within the Token. This is unique within the context
	 * of a particular Token and only at a specific point in time.
	 */
	TInt iObjectId;
	};
///@}
#endif
