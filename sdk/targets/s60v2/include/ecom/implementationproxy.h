//
// ImplementationProxy.h
// Copyright (c) Symbian Software Ltd 1997-2004. All rights reserved.
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

#include <e32std.h>

/**
 	@public
	@typedef TFuncPtr

	Pre-defined function pointer type used in TImplementationProxy

	@dependencies None
 */
typedef TAny* (*TFuncPtr)();

/**
	@internalAll
	@typedef TProxyNewLPtr
	
	Typedef used to cover the difference between EABI and older handling
	of the instantiation method pointer.
*/
#if  defined(__EABI__) || defined(__GCCXML__)
typedef TFuncPtr TProxyNewLPtr;
#else
typedef TAny* TProxyNewLPtr;
#endif

/**
 	@internalAll
	@struct TImplementationProxy

	The structure that defines the pairing required by the ECOM framework
	to correctly identify the instantiation method pointer to provide
	to a client's resolution request.
	Dependencies TUid, TAny

	@since 7.0
 */
typedef struct
	{
	/** The unique UID for an Interface Implementation */
	TUid	iImplementationUid;
	/** 
		The pointer to the instantiation method for the 
		Interface Implementation identified by the UID.
	 */
	TProxyNewLPtr iNewLFuncPtr;
	} TImplementationProxy;

/**
	@internalAll
	@see TImplementationProxy
	
	Macro to initialise an element of a static array of TImplementationProxy objects.
	This macro deals with casting the function pointer to the type used in the structure.
*/
#define IMPLEMENTATION_PROXY_ENTRY(aUid, aFuncPtr)	{{aUid},(TProxyNewLPtr)(aFuncPtr)}

#endif	// __IMPLEMENTATIONPROXY_H__
