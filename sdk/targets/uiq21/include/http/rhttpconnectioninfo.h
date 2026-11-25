// RHTTPConnectionInfo.h
//
// Copyright (C) 2001 Symbian Ltd.

/** 
	@file RHTTPConnectionInfo.h
	@public
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef	__RHTTPCONNECTIONINFO_H__
#define	__RHTTPCONNECTIONINFO_H__ 

// System includes
#include <e32std.h>
#include <stringpool.h>
#include <http/rhttppropertyset.h>

/**
	@public
	@class			RHTTPConnectionInfo
	@since			7.0
	The RHTTPConnectionInfo is used for setting/getting 
	values used for setting up a connection over a protocol.  All methods are inherited
	directly from RHTTPPropertySet.

	To lookup/change any of the following properties, use 
	RHTTPPropertySet::Property(...) and RHTTPPropertySet::SetPropertyL(...) 

	To remove properties, use RHTTPPropertySet::RemoveProperty(...) for a named property,
	or RHTTPPropertySet::RemoveAllProperties() for all.

	The following values are currently defined. Note that new values
	could be added by individual filters. In general, properties
	should be defined before the first transction is created; filters
	are not obliged to check with the connection info if the values
	have changed after this point.

	HTTP::EProxyUsage (default HTTP::EDoNotUseProxy) (HTTP::EDoNotUseProxy | HTTP::EUseProxy)

	HTTP::EProxyAddress (default empty)

	HTTP::EMaxNumTransportHandlers (default 4)

	HTTP::EMaxNumTransPerTranspHndlr (default 5)

	HTTP::EHTTPVersion	(default HTTP::EHttp11) (HTTP::EHttp11 | HTTP::EHttp10)

	HTTP::EProtocol (default, and currently only defined value is HTTP::EHTTP)
 */

//##ModelId=3C4C187A01CA
class RHTTPConnectionInfo : public RHTTPPropertySet
	{
	};

#endif // __RHTTPCONNECTIONINFO_H__
