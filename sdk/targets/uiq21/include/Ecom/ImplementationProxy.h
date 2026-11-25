//
// ImplementationProxy.h
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

/** 
	@file ImplementationProxy.h
	Comments : This file contains the definition for the
				TImplementationProxy structure.
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __IMPLEMENTATIONPROXY_H__
#define __IMPLEMENTATIONPROXY_H__

/**
 	@public
	@struct TImplementationProxy

	The stucture that defines the pairing required by the ECOM framework
	to correctly identify the instantiation method pointer to provide
	to a client's resolution request.

	@since 7.0
	@dependencies TUid, TAny
 */
typedef struct
	{
	/** The unique UID for an Interface Implementation */
	TUid	iImplementationUid;
	/** 
		The pointer to the instantiation method for the 
		Interface Implementation identified by the UID.
	 */
	const TAny*	iNewLFuncPtr;
	} TImplementationProxy;

#endif	// __IMPLEMENTATIONPROXY_H__