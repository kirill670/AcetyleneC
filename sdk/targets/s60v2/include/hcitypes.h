// HCITypes.h
// Common protocol-local HCI types 
// 
// Copyright (c) 1999-2002 Symbian Ltd.  All rights reserved.

/**
@file hcitypes.h
@publishedPartner
@released
*/

#ifndef HCITYPES_H__
#define HCITYPES_H__

#include <bttypes.h>

enum TLinkType
/** Bluetooth link type (ACL / SCO)
*/
	{
	ESCOLink=0x00,	/*!< Synchronous Connection Oriented link */
	EACLLink=0x01	/*!< Asynchronous ConnectionLess link */
	};

enum TEncryptMode
/** Bluetooth encryption mode
*/
	{
	EDisabled=0x00,	/*!< Encryption disabled */
	EPointToPoint,	/*!< Point to point encryption enabled */
	EAll			/*!< Device wide encryption enabled */
	};

enum THCIDeleteAllKeysFlag
/** HCI delete all keys flag
*/
	{
	EDeleteBdaddrLinkKey=0x00,	/*!< Delete bluetooth device address link key */
	EDeleteAllLinkKeys=0x01		/*!< Delete all link keys */
	};
 
enum THCITimeoutType
/** HCI timeout type
*/
    {
    EConnectionAcceptTimeout,	/*!< Connection accept timeout */
    EPageTimeout,				/*!< Page timeout */
    };

enum THCIReadAllKeysFlag
/** HCI read all keys flag
*/
    {
    EReadBdaddrLinkKey=0x00,	/*!< Read bluetooth device address link key */
    EReadAllLinkKeys=0x01,		/*!< Read all link keys */
    };

enum THCIEncryptModeFlag
/** HCI encryption mode flag
*/
    {
    EEncryptionDisabled=0x00,					/*!< Encryption disabled */
    EPointToPointEncryption=0x01,				/*!< Point to point encryption enabled */
    EPointToPointAndBroadcastEncryption=0x02,	/*!< Point to point and broadcast encryption enabled */
    };

enum THCIScanEnable 
/** HCI Scan enable mask
*/
    {
     ENoScansEnabled=0x00,	/*!< No HCI scans enabled */
     EInquiryScanOnly,      /*!< HCI inquiry scan enabled */
     EPageScanOnly,         /*!< HCI page scan enabled */
     EInquiryAndPageScan    /*!< HCI inquiry and page scan enabled */
    };

class THCIEventMask
/** HCI event mask
This can be used to specify the mask used to control which events the controller reports.
*/
    {
public:
    TUint32 iLoBytes;	/*!< Least significant bytes (bytes 0 - 3) */
    TUint32 iHiBytes;	/*!< Most significant bytes (bytes 4 - 7) */
    };

enum THCIEventFilterType
/** HCI event filter type
*/ 
	{
	EClearAllFilters,		/*!< Clear all filters */
    EInquiryResultFilter,	/*!< Inquiry result filter */
    EConnectionSetupFilter	/*!< Connection setup filter */
    };

class TBTDevAddr;
class THCIEventCondition
/** HCI event condition definition.
*/
    {
public:
    THCIEventFilterType iEventFilterType;	/*!< Event filter type */
    TUint8 iConditionType;					/*!< Condition type */
    // unionise this
    TUint iCoD;								/*!< Class of device */
    TUint iCoDMask;							/*!< Class of device mask */
    TBTDevAddr iDevAddr;					/*!< Bluetooth device address */
    TUint8 iAutoAcceptFlag;					/*!< Auto accept flag */
    };

class TInquiryLogEntry
/** Inquiry log entry.  Used to pass information from a BT inquiry operation.
*/
    {
public:
    TUint8 iPageScanRepetitionMode;		/*!< Page scan repetition mode */
    TUint8 iPageScanPeriodMode;			/*!< Page scan period mode */
    TUint8 iPageScanMode;				/*!< Page scan mode */
/** Not used
@internalComponent
*/
    TUint8 iSpare;						
    TUint16 iClockOffset;				/*!< Clock offset */
    TBTDevAddr iBdaddr;					/*!< Bluetooth device address */
    TUint	iCoD;						/*!< Class of device */
    };

class TBTConnect
/** Definition of the parameters required to make a HCI connection.
*/
    {
public:
    THCIConnHandle iConnH;		/*!< Handle to the HCI connection */
    TBTDevAddr iBdaddr;			/*!< Bluetooth device address */
    TUint iCoD;					/*!< Class of device */
    TLinkType iLinkType;		/*!< Link type (ACL / SCO) */
/** Encryption mode 
@see TEncryptMode */
    TEncryptMode iEncryptMode;
    };

class TBTDevHCIVersion
/** BT HCI version definition.
*/
	{
public:
	TUint8 iHCIVersion;		/*!< HCI version */
	TUint16 iHCIRevision;	/*!< HCI Revision */
	};

class TBTDevLMPVersion
/** BT Link Manager Protocol (LMP) version definition.
*/
	{
public:
	TUint8	iLMPVersion;		/*!< LMP version */
	TUint16	iManufacturerID;	/*!< Manufacturer ID */
	TUint16	iLMPSubVersion;		/*!< LMP sub version */ 
	};

class TBTQOS
/** BT quality of service definition.
@see BT code specification.
*/
	{
public:
	TUint8	iFlags;				/*!< QoS flags */ 
	TUint8	iServiceType;		/*!< Service type */
	TUint	iTokenRate;			/*!< Token rate */
	TUint	iPeakBandwidth;		/*!< Peak bandwidth */
	TUint	iLatency;			/*!< Latency */
	TUint	iDelayVariation;	/*!< Delay variation */
	};

typedef TBTDevLMPVersion TBTDevRemoteHwVersion;	/*!< Definition of the TBTDevRemoteHwVersion type */
typedef TUint16 THCIOpcode;						/*!< Definition of the THCIOpcode type */
typedef TUint16 TBasebandTime;					/*!< Definition of the TBasebandTime type */

// Transport

typedef TUint16 THCITransportChannel;	/*!< Definition of the HCI transport channel type */

static const THCITransportChannel KHCITransportNoChannels		= 0x0000;	/*!< No HCI transport channels available for sending */
static const THCITransportChannel KHCITransportCommandChannel	= 0x0001;	/*!< Command HCI transport channel available for sending */
static const THCITransportChannel KHCITransportACLDataChannel	= 0x0002;	/*!< ACL data HCI transport channel available for sending */
static const THCITransportChannel KHCITransportSCODataChannel	= 0x0004;	/*!< SCO data HCI transport channel available for sending */
static const THCITransportChannel KHCITransportAllChannels		= static_cast<THCITransportChannel>
																( KHCITransportCommandChannel
																| KHCITransportACLDataChannel 
																| KHCITransportSCODataChannel);		/*!< All HCI transport channels available for sending */


#endif
