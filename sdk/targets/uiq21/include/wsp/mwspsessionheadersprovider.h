// MWspSessionHeadersProvider.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.

/** 
	@file MWspSessionHeadersProvider.h
	@public
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __MWSPSESSIONHEADERSPROVIDER_H__
#define __MWSPSESSIONHEADERSPROVIDER_H__

// System includes
#include <e32base.h>

/**
	@public
	@class MWspSessionHeadersProvider
	@since			7.0
	The MWspSessionHeadersProvider API provides an interface for accessing and 
	setting the Client and Server session headers, respectively. The Client 
	session headers can be accessed to send to the Server in the S-Connect.req
	primitive. Any header information that is returned from the Server in the 
	S-Connect.cnf can be passed to the Client.
 */

class MWspSessionHeadersProvider
	{
public:	// Methods

/**
	@fn				ClientHeaders() const =0
	Intended Usage	:	Provides the Client session headers as an encoded buffer.
	@since			7.0
	@return			A const reference to a buffer containing the encoded headers.
 */	  
	virtual const TDesC8& ClientHeaders() const =0;

/**
	@fn				SetServerHeadersL(const TDesC8& aBuffer) =0;
	Intended Usage	:	Sets the Server session headers. Any headers returned 
						from the Server are passed to the Client in their encoded
						form.
	@since			7.0
	@leave			Leave code KErrNoMemory if the headers cannot be set.
	@param			aBuffer	A const reference to a buffer containing the encoded
							session headers from the Server.
	@post			The Server session headers have been passed to the Client.
 */	  
	virtual void SetServerHeadersL(const TDesC8& aBuffer) =0;
	};

#endif //	__MWSPSESSIONHEADERSPROVIDER_H__
