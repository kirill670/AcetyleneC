//
// obextypes.h
//
// Copyright (c) 2003-2004 Symbian Software Ltd.  All rights reserved.
//

/**
@file
@internalTechnology
*/

#ifndef __OBEXTYPES_H
#define __OBEXTYPES_H

#include <e32std.h>
#include <e32des8.h>
#include <e32des16.h>
#include <utf.h> // Required for source compatability
#include "obexconstants.h"

/**
@publishedAll
@released
*/
typedef TUint16 TObexHeaderMask;

typedef TUint8 TObexOpcode;
typedef TBuf8<KObexConnectionIDLength> TConnId;
typedef TBuf8<16> TNonce;
typedef TBuf8<16> TRequestDigest;

class TObexProtocolInfo;
class TObexIrProtocolInfo;
class TObexBluetoothProtocolInfo;
class TObexUsbProtocolInfo;
class TObexUsbProtocolInfoV2;
class TObexProcotolPolicy;
struct TObexConnectionInfo;
class TObexConnectInfo;

class CObexPacket;
class CObexHeader;
class CObexUnderlyingHeader;
class MObexHeaderCheck;
class CObexHeaderSet;
class CObexBaseObject;
class CObexFileObject;
class CObexBufObject;
class CObexNullObject;
class MObexNotify;
class MObexAuthChallengeHandler;
class CObexTransport;
class CObexSocketConnector;
class TObexInternalHeader;
class CObexAuthenticator;
class CObex;
class CObexClient;
class MObexServerNotify;
class CObexServer;
class MObexServerNotify;


#endif	// __OBEXTYPES_H
