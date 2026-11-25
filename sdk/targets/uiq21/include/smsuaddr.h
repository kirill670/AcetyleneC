// SMSUADDR.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

/**
 * @file smsuaddr.h Defines types for SMS adressing and the class TSmsAddr
 */

#if !defined(SMSUADDR_H__)
#define SMSUADDR_H__

#include <es_sock.h>
#include <etelmm.h>

const TUint KSMSAddrFamily = 0x010;
const TUint KSMSDatagramProtocol = 0x02;
const TInt KSMSNumberSockets = 0x100;
const TUint KSMSDatagramServiceInfo = KSIConnectionLess | KSIMessageBased ;

_LIT(KSmsDatagram,"SMS Datagram");


const TUint KSolSmsProv = 0x100; ///< Ioctl level for provider

const TUint KIoctlDeleteSmsMessage        = 0x0300; ///< Ioctl command for deleting SMS messages
const TUint KIoctlEnumerateSmsMessages    = 0x0301; ///< Ioctl command for enumerating SMS messages
const TUint KIoctlReadMessageSucceeded    = 0x0304; ///< Ioctl command to indicate messages was received OK
const TUint KIoctlReadMessageFailed       = 0x0305; ///< Ioctl command to indicate messages was not received OK
const TUint KIoctlSendSmsMessage          = 0x0306; ///< Ioctl command for sending SMS messages
const TUint KIoctlWriteSmsMessage         = 0x0307; ///< Ioctl command for writing SMS messages to SIM
const TUint KIoctlReadSmsParams           = 0x0308; ///< Ioctl command for enumerating SMS parameter sets
const TUint KIoctlCompleteReadSmsParams   = 0x0309; ///< Ioctl command for completing SMSP list read request
const TUint KIoctlWriteSmsParams          = 0x0310; ///< Ioctl command ofr writing SMS parameter sets

const TUint KIoctlSelectModemPresent    = 0x400; ///< KIOctlSelect completion status if modem present
const TUint KIoctlSelectModemNotPresent = 0x401; ///< KIOctlSelect completion status if modem not present

//ahe TODO
//typedef TBuf<KGsmMaxTelNumberSize> TSmsServiceCenterAddress;
typedef TBuf<14> TSmsServiceCenterAddress;
typedef TPckgBuf<TSmsServiceCenterAddress> TSmsServiceCenterAddressBuf;


/**
 * used to selecting the SMS address family for a socket
 *
 * @note Maintainers, please do *not* change the order of these enums!
 */
enum TSmsAddrFamily
	{
	ESmsAddrUnbound                = 0, ///< not bound yet
	ESmsAddrSendOnly               = 1, ///< only for sending, no reception
	ESmsAddrMessageIndication      = 2, ///< matches on IEI 0x01 and DCS 0x1100xxxx, 0x1101xxxx and 0x1110xxxx, 
	ESmsAddrMatchIEI               = 3, ///< for matching Information Element Identifiers (IEI)
	ESmsAddrMatchText              = 4, ///< for matching any text patterns
	ESmsAddrRecvAny                = 5, ///< receive all, only one client can use this
	ESmsAddrStatusReport           = 6, ///< for receiving Status Reports
	ESmsAddrLocalOperation         = 7, ///< For local SIM operations
	ESmsAddrApplication8BitPort    = 8, ///< For sock port identification
	ESmsAddrApplication16BitPort   = 9  ///< For sock port identification
	};


/**
 * used to selecting the SMS address for a socket
 */
class TSmsAddr : public TSockAddr
	{
public:
	enum { EMaxTextMatchLength = 24 };
public:
	IMPORT_C TSmsAddr();
	IMPORT_C TSmsAddrFamily SmsAddrFamily() const;
	IMPORT_C void SetSmsAddrFamily(TSmsAddrFamily aFamily);
	IMPORT_C TInt IdentifierMatch() const;
	IMPORT_C void SetIdentifierMatch(TInt aIdentifier);
	IMPORT_C TPtrC8 TextMatch() const;
	IMPORT_C void SetTextMatch(const TDesC8& aText);
	IMPORT_C TBool operator==(const TSmsAddr& aAddr) const;
	};


#endif // SMSUADDR_H__
