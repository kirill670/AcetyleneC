// SENDAS.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

/**
Gets an array of MTMs that satisfy the current capability requirements. 

The array changes after every call to AddRequiredCapabilityL() and ResetCapabilitiesL(). 
The array never contains MTMs that do not have the capability to send messages.

@return The array of the human-readable names of the MTMs that satisfy the 
current required capabilities.
*/

inline const CDesCArray& CSendAs::AvailableMtms() const
	{
	return *iAvailNameArray;
	}


/**
Gets direct access to Messaging's client registry. 

@return Client registry object.
*/

inline CClientMtmRegistry& CSendAs::ClientRegistry()
	{
	return *iClientRegistry;
	}


/**
Gets direct access to the class providing protocol-specific messaging functionality 
(a client MTM). 

@return Client-side MTM object.
*/

inline CBaseMtm& CSendAs::ClientMtm()
	{
	return *iClientMtm;
	}


/**
Gets a list of the available services. 

The array is populated when the MTM is set.

@return The list of the names of services that can be used by the chosen MTM 
type.
*/

inline const CDesCArray& CSendAs::AvailableServices() const
	{
	return *iServiceNameArray;
	}


/**
Gets the ID of the message created by Send As.

@return The ID of the message.
*/

inline TMsvId CSendAs::MessageId()
	{
	return iMessageId;
	}
