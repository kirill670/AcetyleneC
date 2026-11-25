// SENDAS.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

inline const CDesCArray& CSendAs::AvailableMtms() const
/** Gets an array of MTMs that satisfy the current capability requirements. 

The array could change after every call to AddRequiredCapabilityL() and ResetCapabilitiesL(). 
The array never contains MTMs that do not have the capability to send messages.

@return The array of the human-readable names of the MTMs that satisfy the 
current required capabilities */
	{
	return *iAvailNameArray;
	}

inline CClientMtmRegistry& CSendAs::ClientRegistry()
/** Gets direct access to Messaging's client registry. 

@return Client registry object */
	{
	return *iClientRegistry;
	}

inline CBaseMtm& CSendAs::ClientMtm()
/** Gets direct access to the class providing protocol-specific messaging functionality 
(a client MTM). 

@return Client-side MTM object */
	{
	return *iClientMtm;
	}

inline const CDesCArray& CSendAs::AvailableServices() const
/** Gets a list of the available services. 

It panics if an MTM has not been set.

@return The list of the names of services that can be used by the chosen MTM 
type */
	{
	return *iServiceNameArray;
	}

inline TMsvId CSendAs::MessageId()
	{
	return iMessageId;
	}
