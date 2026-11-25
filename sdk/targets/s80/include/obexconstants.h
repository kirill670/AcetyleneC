//
// obexconstants.h
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifdef __OBEX_USER_DEFINED_HEADERS__

#ifndef __OBEXCONSTANTS_H
#define __OBEXCONSTANTS_H

#include <e32std.h>
#include <es_sock.h>
#include <ir_sock.h>
#include <bt_sock.h>


//common to request & resp digests
const TInt KChallResponseSize = 58;
const TInt KMinChallResponseSize = 18; //Nonce(16) + tag(1) + size(1)
const TInt KObexNonceSize = 16;
const TUint8 KObexRequireUID = 0x01;
//request or chall
const TUint KObexChallNonceTag = 0;
const TUint8 KObexChallOptionsTag = 0x01;
const TUint8 KObexChallRealmTag = 0x02;
const TInt KObexChallOptionSize = 1; //this can't be changed from one without making
const TUint KObexChallHeaderSize = 23; //assuming no Realm data
//response
const TUint KObexRespTag = 0;
const TInt KObexRespSize = 16;
const TUint8 KObexRespUserIDTag = 0x01;
const TUint8 KObexRespNonceTag = 0x02;

const TUint8 KObexHeaderTypeMask = 0xc0;
const TUint8 KObexHeaderTypeOffset = 6;

#ifdef _UNICODE
const TInt KUidOBEXTransportModule = 0x10003d56;
#else
const TInt KUidOBEXTransportModule = 0x1000169c;
#endif

const TUint8 KObexConnectionIDLength = 4;

const TInt KUsbIntStringDescLength = 30;

const TUint8 KFourByteTimeHeaderAddress = 0xc4;

// Header mask definitions.
// Old style accessor for which headers are present or
// should be sent by an object.  Now deprecated, use the
// header iterator instead.
const TUint16 KObexHdrName				= 0x0001;
const TUint16 KObexHdrType				= 0x0002;
const TUint16 KObexHdrLength			= 0x0004;
const TUint16 KObexHdrTime				= 0x0008;
const TUint16 KObexHdrDescription		= 0x0010;
const TUint16 KObexHdrTarget			= 0x0020;
const TUint16 KObexHdrConnectionID		= 0x0040;
const TUint16 KObexHdrBody				= 0x0080;
const TUint16 KObexHdrEndOfBody			= 0x0100;
const TUint16 KObexHdrHttp				= 0x0200;
const TUint16 KObexHdrAppParam			= 0x0400;
const TUint16 KObexHdrUserDefined		= 0x0800;
const TUint16 KObexHdrCount				= 0x1000;
const TUint16 KObexHdrCreatorID			= 0x2000;
const TUint16 KObexHdrWanUUID			= 0x4000;
const TUint16 KObexHdrObjectClass		= 0x8000;

const TUint8  KObexUserDefinedHdrAddrMin	 = 0x30; //start of user defined header address range
const TUint8  KObexUserDefinedHdrAddrMax	 = 0x3F; //end of user defined header address range

const TUint8 KObexVersion           	= 0x10;		///< Version 1.0 (still correct for Obex spec v 1.2)

const TUint8 KObexObjectFieldSize   	= 127;
const TUint8 KObexObjectDescriptionSize = 255;

//Extended Errors for IrObex
const TInt KErrIrObexRespBase			= - 5500; //must not use as not in our allocated range

const TInt KErrIrObexClientNoDevicesFound = -5501;
const TInt KErrIrObexClientPeerDoesNotHaveObex = -5502;
const TInt KErrIrObexClientPutPeerAborted	= -5503;
const TInt KErrIrObexServerPutPeerAborted = -5507;
const TInt KErrIrObexConnectChallRejected = -5512;

// Other Obex errors defined in the system:
// KErrIrObexClientPutPeerCannotHandleObject -5504
// KErrIrObexServerPutFileWriteError		-5509
// KErrIrObexClientFirstPutFailed			-5510
// KErrIrObexClientSubsequentPutFailed		-5511
//
// There are other error codes defined at the end of this file,
// which are a direct mapping of specific Obex error codes and
// are returned by the client.

//Obex panics
enum TObexPanicCode
	{
	ENullPointer				= 0,
	EInvalidUnicodeHeaderRead	= 1,
	EInvalidUnicodeOddByte      = 2,
	EStringOverflow             = 3,
	EHILargerThanTotal          = 4,
	EPacketOverrun              = 5,
	ESocketNotOpen              = 6,
	ENotImplementedPanicCode	= 7,
	EInvalidHeaderSize			= 8,
	EInvalidPacketSize			= 9,
	EEmptyBuffer				= 10,
	EHurricaneCaller			= 11,
	EUnknownUsbState			= 12,
	EUnknownTransport			= 13,
	EHeaderAsBadType			= 14,
	ERefCountNonZero			= 15,
	EInvalidBufferStrategy		= 16,
	EPanicRemovedExport			= 17,
	};

 
// Flags used by Connect
// ...None in OBEX 1.0

// Flags used by SetPath
const TUint8 KObexSetPathParent	= 0x01;


// Constants used to define which transport Obex will run over.  Used in
// TObexProtocolInfo's iTransport member.

///< Protocol string when running over IrDA
_LIT(KObexIrTTPProtocol, "IrTinyTP");

///< Protocol string when running over Bluetooth
_LIT(KObexRfcommProtocol, "RFCOMM");

///< Protocol string when running over USB
_LIT(KObexUsbProtocol, "USB");


class TObexProtocolInfo
	/** 
	 * TObexProtocolInfo is derived for each underlying transport protocol OBEX 
	 * runs over. 
	 *
	 * At this time, IrTinyTP and Rfcomm are supported. Use @c TObexIrProtocolInfo 
	 * whenever running over TinyTP, and @c TObexBluetoothProtocolInfo when 
	 * running over Rfcomm.
	 *
	 * The @c iTransport member holds the unique name for the transport, for TinyTP
	 * this is @p "IrTinyTP", and for Rfcomm, it is @p "RFCOMM". 
	 */
	{
	public:
		TBuf<60> iTransport;
	};


class TObexIrProtocolInfo : public TObexProtocolInfo
	/** 
	 * @c iAddr holds IrDA address information about this 
	 * connection, as used in the IrDA sockets interface. Refer to the SDK for 
	 * more information about this. It’s main use is for setting the port that the
	 * local machine will listen on.
	 *	
	 * @c iClassName and iAttributeName set the IAS class and attribute values 
	 * that the OBEX session will register its listener port, or request remote 
	 * port with. To access the default OBEX server, these should be @p "OBEX" and 
	 * @p "IrDA:TinyTP:LsapSel" respectively. 
	 */
	{
	public:
		TIrdaSockAddr iAddr;
		TBuf8<KIASClassNameMax> iClassName;
		TBuf8<KIASAttributeNameMax> iAttributeName;
	};


class TObexBluetoothProtocolInfo : public TObexProtocolInfo
	{
	public:
		TRfcommSockAddr iAddr;
	};

class TObexUsbProtocolInfo : public TObexProtocolInfo
	{
	public:
		TBuf16<KUsbIntStringDescLength> iInterfaceStringDescriptor;
	};

struct TObexConnectionInfo;

class TObexConnectInfo
	/**
	 * TObexConnectInfo
	 * This structure contains information used during OBEX connection. iVersion
	 * holds the encoded OBEX version of the machine, use @c VersionMajor() and
	 * @c VersionMinor() to extract the parts of the version number (each having a
	 * value from 0 to 15). @c iFlags holds OBEX connection flags. @c iWho holds 
	 * the Who attribute from the connect packet, if any was specified, or 
	 * otherwise has a length of 0. 
	 * It is recommended that this class is only ever allocated on the heap as it is quite big.
	 */
	{
	public:
		IMPORT_C TObexConnectInfo();
		IMPORT_C TUint8 VersionMajor() const;
		IMPORT_C TUint8 VersionMinor() const;
	public:
		TUint8 iVersion; ///< Encoded OBEX version of the machine
		TUint8 iFlags; ///< iFlags holds OBEX connection flags
		TBuf8<KObexObjectDescriptionSize> iWho; ///< the Who attribute from the connect packet, if any was specified
		TBuf8<KObexObjectDescriptionSize> iTargetHeader; ///< the Target header from the connect packet, if any was specified
	};



//if these codes are extended due to a IRObex spec update ensure 
//that the TInt immediately below are updated 
//and the default in the method IrOBEXUtil::ObexResponse is also updated
enum TObexResponse  
	{ 
	ERespContinue			= 0x10,
	ERespSuccess			= 0x20,
	ERespCreated			= 0x21,
	ERespAccepted			= 0x22,
	ERespNonAuthInfo		= 0x23,
	ERespNoContent			= 0x24,
	ERespResetContent		= 0x25,
	ERespPartialContent		= 0x26,
	ERespMultipleChoices	= 0x30,
	ERespMovedPerm			= 0x31,
	ERespMovedTemp			= 0x32,
	ERespSeeOther			= 0x33,
	ERespNotModified		= 0x34,
	ERespUseProxy			= 0x35,
	ERespBadRequest			= 0x40,
	ERespUnauthorized		= 0x41,
	ERespPaymentRequired	= 0x42,
	ERespForbidden			= 0x43,
	ERespNotFound			= 0x44,
	ERespMethodNotAllowed	= 0x45,
	ERespNotAcceptable		= 0x46,
	ERespProxyAuthenReqd	= 0x47,
	ERespTimedOut			= 0x48,
	ERespConflict			= 0x49,
	ERespGone				= 0x4A,
	ERespLengthReqd			= 0x4B,
	ERespPreCondFailed		= 0x4C,
	ERespReqEntityTooLarge	= 0x4D,
	ERespReqURLTooLarge		= 0x4E,
	ERespUnsupMediaType		= 0x4F,
	ERespInternalError		= 0x50,
	ERespNotImplemented		= 0x51,
	ERespBadGateway			= 0x52,
	ERespServiceUnavail		= 0x53,
	ERespGatewayTimeout		= 0x54,
	ERespHTTPVerNotSupp		= 0x55,
	ERespDatabaseFull		= 0x60,
	ERespDatabaseLocked		= 0x61,
	ERespServiceUnavailable = 0xD3,
	};


//some error codes to be used specifically by the client
//these shall, be mapped directly to OBEX defined error codes.
const TInt KErrIrObexRespSuccess		= KErrIrObexRespBase - ERespSuccess;			//-5532 returns 0x20 (0xA0)
const TInt KErrIrObexRespCreated		= KErrIrObexRespBase - ERespCreated;			//-5533 returns 0x21 (0xA1)
const TInt KErrIrObexRespAccepted		= KErrIrObexRespBase - ERespAccepted;			//-5534 returns 0x22 (0xA2)
const TInt KErrIrObexRespNonAuthInfo	= KErrIrObexRespBase - ERespNonAuthInfo;		//-5535 returns 0x23 (0xA3)
const TInt KErrIrObexRespNoContent		= KErrIrObexRespBase - ERespNoContent;			//-5536 returns 0x24 (0xA4)
const TInt KErrIrObexRespResetContent	= KErrIrObexRespBase - ERespResetContent;		//-5537 returns 0x25 (0xA5)
const TInt KErrIrObexRespPartialContent = KErrIrObexRespBase - ERespPartialContent;		//-5538 returns 0x26 (0xA6)
const TInt KErrIrObexRespMultipleChoices = KErrIrObexRespBase - ERespMultipleChoices;	//-5548 returns 0x30 (0xB0)
const TInt KErrIrObexRespMovedPerm		= KErrIrObexRespBase - ERespMovedPerm;			//-5549 returns 0x31 (0xB1)
const TInt KErrIrObexRespMovedTemp		= KErrIrObexRespBase - ERespMovedTemp;			//-5550 returns 0x32 (0xB2)
const TInt KErrIrObexRespSeeOther		= KErrIrObexRespBase - ERespSeeOther;			//-5551 returns 0x33 (0xB3)
const TInt KErrIrObexRespNotModified	= KErrIrObexRespBase - ERespNotModified;		//-5552 returns 0x34 (0xB4)
const TInt KErrIrObexRespUseProxy		= KErrIrObexRespBase - ERespUseProxy;			//-5553 returns 0x35 (0xB5)
const TInt KErrIrObexRespBadRequest		= KErrIrObexRespBase - ERespBadRequest;			//-5564 returns 0x40 (0xC0)
const TInt KErrIrObexRespUnauthorized	= KErrIrObexRespBase - ERespUnauthorized;		//-5565 returns 0x41 (0xC1)
const TInt KErrIrObexRespPaymentRequired = KErrIrObexRespBase - ERespPaymentRequired;	//-5566 returns 0x42 (0xC2)
const TInt KErrIrObexRespForbidden		= KErrIrObexRespBase - ERespForbidden;			//-5567 returns 0x43 (0xC3)
const TInt KErrIrObexRespNotFound		= KErrIrObexRespBase - ERespNotFound;			//-5568 returns 0x44 (0xC4)
const TInt KErrIrObexRespMethodNotAllowed = KErrIrObexRespBase - ERespMethodNotAllowed;	//-5569 returns 0x45 (0xC5)
const TInt KErrIrObexRespNotAcceptable	= KErrIrObexRespBase - ERespNotAcceptable;		//-5570 returns 0x46 (0xC6)
const TInt KErrIrObexRespProxyAuthenReqd = KErrIrObexRespBase - ERespProxyAuthenReqd;	//-5571 returns 0x47 (0xC7)
const TInt KErrIrObexRespTimedOut		= KErrIrObexRespBase - ERespTimedOut;			//-5572 returns 0x48 (0xC8)
const TInt KErrIrObexRespConflict		= KErrIrObexRespBase - ERespConflict;			//-5573 returns 0x49 (0xC9)
const TInt KErrIrObexRespGone			= KErrIrObexRespBase - ERespGone;				//-5574 returns 0x4A (0xCA)
const TInt KErrIrObexRespLengthReqd		= KErrIrObexRespBase - ERespLengthReqd;			//-5575 returns 0x4B (0xCB)
const TInt KErrIrObexRespPreCondFailed	= KErrIrObexRespBase - ERespPreCondFailed;		//-5576 returns 0x4C (0xCC)
const TInt KErrIrObexRespReqEntityTooLarge = KErrIrObexRespBase - ERespReqEntityTooLarge;//-5577 returns 0x4D (0xCD)
const TInt KErrIrObexRespReqURLTooLarge	= KErrIrObexRespBase - ERespReqURLTooLarge;		//-5578 returns 0x4E (0xCE)
const TInt KErrIrObexRespUnsupMediaType = KErrIrObexRespBase - ERespUnsupMediaType;		//-5579 returns 0x4F (0xCF)
const TInt KErrIrObexRespInternalError	= KErrIrObexRespBase - ERespInternalError;		//-5580 returns 0x50 (0xD0)
const TInt KErrIrObexRespNotImplemented = KErrIrObexRespBase - ERespNotImplemented;		//-5581 returns 0x51 (0xD1)
const TInt KErrIrObexRespBadGateway		= KErrIrObexRespBase - ERespBadGateway;			//-5582 returns 0x52 (0xD2)
const TInt KErrIrObexRespServiceUnavail = KErrIrObexRespBase - ERespServiceUnavail;		//-5583 returns 0x53 (0xD3)
const TInt KErrIrObexRespGatewayTimeout = KErrIrObexRespBase - ERespGatewayTimeout;		//-5584 returns 0x54 (0xD4)
const TInt KErrIrObexRespHTTPVerNotSupp = KErrIrObexRespBase - ERespHTTPVerNotSupp;		//-5585 returns 0x55 (0xD5)
const TInt KErrIrObexRespDatabaseFull	= KErrIrObexRespBase - ERespDatabaseFull;		//-5596 returns 0x60 (0xE0)
const TInt KErrIrObexRespDatabaseLocked = KErrIrObexRespBase - ERespDatabaseLocked;		//-5597 returns 0x61 (0xE1)


#endif	// __OBEXCONSTANTS_H

#endif // __OBEX_USER_DEFINED_HEADERS__
