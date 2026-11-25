//
// Resolver.h
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

/** 
	@file Resolver.h
	Comments : This file contains the definition of the CResolver
		class.
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef __RESOLVER_H__
#define __RESOLVER_H__

#include <e32base.h>
#include <f32file.h>

#include <Ecom/ECom.h>
#include <Ecom/PublicRegistry.h>

class TEComResolverParams;

/**
	@public
	@class CResolver
	@since 7.0
	@dependencies CBase, TEComResolverParams, CImplementationInformation, MPublicRegistry
	Abstract base class which is used to identify the correct interface implementation
	based on criteria supplied by the client.
	This base class can be used to write a client specific resolver, however this is not 
	required as a default implementation is provided within ECom.
 */
//##ModelId=3B16386703B2
class CResolver : public CBase
{
public:
/**
	@fn				IdentifyImplementationL(TUid aInterfaceUid, 
											const TEComResolverParams& aAdditionalParameters) const = 0
	Intended Usage	:	Request that the resolver identify the most appropriate interface 
						implementation.
	Error Condition	:	Depends on implementation.
	@since			7.0
	@param			aInterfaceUid The interface for which an implementation is requested
	@param			aAdditionalParameters The parameters which must match for an 
					implementation to be suitable
	@return			The unique Id of the implementation which satisfies the specified parameters.
	@pre 			This object is fully constructed.
 */
	//##ModelId=3B1638680008
	virtual TUid IdentifyImplementationL(TUid aInterfaceUid, 
										 const TEComResolverParams& aAdditionalParameters) const = 0;

/**
	@fn				ListAllL(TUid aInterfaceUid, 
							 const TEComResolverParams& aAdditionalParameters) const = 0
	Intended Usage	:	List all the implementations which satisfy the specified 
						interface definition and the resolve parameters supplied.
	Error Condition	:	Depends on implementation.
	@since			7.0
	@param			aInterfaceUid The interface for which implementations are requested
	@param			aAdditionalParameters The parameters which must match for an 
					implementation to be suitable
	@return			Pointer to an array of suitable implementations. Ownership of this 
					array is passed to the calling function.
	@pre 			Object is fully constructed and initialized
	@post			Registry contents are not modified but registry keys may be updated
 */
	//##ModelId=3B16386703DC
	virtual RImplInfoArray* ListAllL(TUid aInterfaceUid, 
									 const TEComResolverParams& aAdditionalParameters) const = 0;

/**
	@fn				ListAllL(TUid aInterfaceUid) const
	Intended Usage	:	List all the implementations which satisfy the specified interface.
	Error Condition	:	@see CRegistryData::ListImplementationsL
	@since			7.0
	@param			aInterfaceUid The interface for which implementations are requested
	@return			Array of suitable implementations
	@pre 			Object is fully constructed and initialized
	@post			Registry contents are not modified but registry keys may be updated
 */
	//##ModelId=3B16386703DF
	inline RImplInfoArray& ListAllL(TUid aInterfaceUid) const;

protected:
/**
	@internal
	@fn				CResolver(MPublicRegistry& aRegistry)
	Intended Usage	: Standardized default c'tor
	Error Condition	: None
	@since			7.0
	@post			CResolver is fully constructed
 */
	//##ModelId=3B16386703D1
	explicit inline CResolver(MPublicRegistry& aRegistry);

// Attributes
/** A reference to the instantiated registry information */
	//##ModelId=3B16386703BF
	const MPublicRegistry& iRegistry;
};

CResolver::CResolver(MPublicRegistry& aRegistry) :
CBase(),
iRegistry(aRegistry)
	{
	// Do nothing
	}

RImplInfoArray& CResolver::ListAllL(TUid aInterfaceUid) const
	{
	return iRegistry.ListImplementationsL(aInterfaceUid);
	}

#endif /* __RESOLVER_H__ */

