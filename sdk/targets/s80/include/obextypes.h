//
// obextypes.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//
#ifdef __OBEX_USER_DEFINED_HEADERS__

#ifndef __OBEXTYPES_H
#define __OBEXTYPES_H

#include <e32std.h>
#include <e32des8.h>
#include <e32des16.h>
#include <utf.h> // Required for source compatability
#include "obexconstants.h"


typedef TUint16 TObexHeaderMask;
typedef TUint8 TObexOpcode;
typedef TBuf8<KObexConnectionIDLength> TConnId;
typedef TBuf8<16> TNonce;
typedef TBuf8<16> TRequestDigest;

class TObexProtocolInfo;
class TObexIrProtocolInfo;
class TObexBluetoothProtocolInfo;
class TObexUsbProtocolInfo;
struct TObexConnectionInfo;
class TObexConnectInfo;

class TObexPacket;
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

#endif // __OBEX_USER_DEFINED_HEADERS__
