//
// PublicRegistry.h
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

/** 
@file PublicRegistry.h
Comments : The interface definition for the MPublicRegistry class

@warning This code contains Rose2000 generated ModelId comments
		 used in round trip engineering. Please do not remove.
 */ 

#ifndef __PUBLICREGISTRY_H__
#define __PUBLICREGISTRY_H__

#include <Ecom/ImplementationInformation.h>

/**
@internalAll
@class MPublicRegistry
Provides access to the public functions of CRegistryData.
Dependencies TUid, RImplInfoArray
@since 7.0
*/
//##ModelId=3B2A284A0332
class MPublicRegistry
	{
public:
	/**
	Intended Usage	: Provides a list of the implementations which satisfy the 
					interface uid specified.
	@exception		Depends on implementation.
	@since			7.0
	@return			None.
	@pre 			This object is fully constructed.
 	*/
	//##ModelId=3B2A284A038C
	virtual RImplInfoArray& ListImplementationsL(TUid aInterfaceUid) const = 0;
	};

#endif // __PUBLICREGISTRY_H__
