//
// obexirtransportinfo.h
//
// Copyright (c) 2005 Symbian Software Ltd.  All rights reserved.
//

#ifndef __OBEXIRTRANSPORTINFO_H__
#define __OBEXIRTRANSPORTINFO_H__

#include <ir_sock.h>
#include <obextransportinfo.h>

/**
Concrete transport info type for use when using Irda ttp  transport controller.
@see KObexIrTTPProtocol
@publishedAll
@released
*/
NONSHARABLE_CLASS(TObexIrTransportInfo) : public TObexTransportInfo

{
//From TObexIrProtocolInfo
public:
	/** IrDA address information for this connection, as used in the IrDA sockets interface.
	Refer to the SDK for more information about this.
	Its main use is for setting the port that the local machine will listen on. */
	TIrdaSockAddr iAddr;
	/** The IAS class value that the OBEX session will register its listener port,
	or request remote port with. */
	TBuf8<KIASClassNameMax> iClassName;
	/** The IAS attribute value that the OBEX session will register its listener port,
	or request remote port with. */
	TBuf8<KIASAttributeNameMax> iAttributeName;


};

/**
Concrete transport info type for use when using Irda ttp  transport controller, with discovery extensions.
@see KObexIrTTPProtocolV2
@publishedAll
@released
*/
NONSHARABLE_CLASS(TObexIrV2TransportInfo) : public TObexIrTransportInfo

{
//From TObexIrProtocolInfo
public:
	/** The number of discovery slots to use. */
	TUint8 iDiscoverySlots;
	/** The number of discovery attempts to make. */
	TUint8 iDiscoveryAttempts;
	
private:
	// This data padding has been added to help prevent future binary compatibility breaks	
	// None of these padding variables have been zero'd because they are currently not used
	TUint32     iPadding1; 
	TUint32     iPadding2; 		
	TUint32     iPadding3; 
	TUint32     iPadding4; 	
};
// __OBEXIRTRANSPORTINFO_H__
#endif
