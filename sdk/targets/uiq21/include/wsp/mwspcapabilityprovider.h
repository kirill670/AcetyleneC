// MWspCapabilityProvider.h
//
// Copyright (C) 2001 Symbian Ltd

/** 
	@file MWspCapabilityProvider.h
	@public
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __MWSPCAPABILITYPROVIDER_H__
#define __MWSPCAPABILITYPROVIDER_H__

// System includes
#include <e32base.h>

// Forward declarations
class MWspCapabilityViewer;
class MWspCapabilitySetter;

/**
	@public
	@class MWspCapabilityProvider
	@since			7.0
	The MWspCapabilityProvider API supplies the capabilities proposed by the 
	Client using the MWspCapabilityViewer API. The negotiated capabilities from
	the Server can be given to the Client using the MWspCapabilitySetter API.
 */

class MWspCapabilityProvider
	{
public:	// Methods

/**
	@fn				ClientCapabilities() const =0
	Intended Usage	:	Provides the proposed Client capabilities. 
	@since			7.0
	@return			A reference to a MWspCapabilityViewer object that contains
					the Client's proposed capabilities.
 */
	virtual const MWspCapabilityViewer& ClientCapabilities() const =0;

/**
	@fn				ServerCapabilities() const =0
	Intended Usage	:	Provides the call-back interface for the negotiated 
						capabilities from the Server.
	@since			7.0
	@return			A reference to a MWspCapabilitySetter object through which
					the negotiated capabilities from the Server are passed to 
					the Client.
 */
	virtual MWspCapabilitySetter& ServerCapabilities() const =0;
	};

#endif	// __MWSPCAPABILITYPROVIDER_H__