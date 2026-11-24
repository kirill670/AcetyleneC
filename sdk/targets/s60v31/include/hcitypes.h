// HCITypes.h
// Common protocol-local HCI types 
// 
// Copyright (c) 1999-2002 Symbian Ltd.  All rights reserved.

/**
@file
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
	EACLLink=0x01,	/*!< Asynchronous ConnectionLess link */
	EeSCOLink=0x02	/*!< eSCO link */
	};

enum TEncryptMode
/** Bluetooth encryption mode
*/
	{
	EDisabled=0x00,	/*!< Encryption disabled */
	EPointToPoint,	/*!< Point to point encryption enabled */
	EAll			/*!< Device wide encryption enabled */
	};

enum TAirMode
/** Air mode of synchronous connection
*/
	{
	ECVSD =			 0x00,	/*!< CVSD */
	EuLawLog =		 0x01,	/*!< u-law log */
	EALawLog =		 0x02,	/*!< A-law log */
	ETransparentData=0x03	/*!< Transparent data */
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
     EInquiryScanOnly=0x01,      /*!< HCI inquiry scan enabled */
     EPageScanOnly=0x02,         /*!< HCI page scan enabled */
     EInquiryAndPageScan=0x03    /*!< HCI inquiry and page scan enabled */
    };

NONSHARABLE_CLASS(THCIEventMask)
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
NONSHARABLE_CLASS(THCIEventCondition)
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

NONSHARABLE_CLASS(TInquiryLogEntry)
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

NONSHARABLE_CLASS(TBTConnect)
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

NONSHARABLE_CLASS(TBTSyncConnectOpts)
/** Parameters returned by HCI after a sucessful Synchronous conenction.
*/
	{
	public:
		inline TBTSyncConnectOpts(const TUint8 aTransmissionInterval, const TUint8 aRetransmissionWindow, 
	    	const TUint16 aRxPacketLength, const TUint16 aTxPacketLength, const TAirMode aAirMode)
			: iTransmissionInterval(aTransmissionInterval), iRetransmissionWindow(aRetransmissionWindow),
			  iRxPacketLength(aRxPacketLength), iTxPacketLength(aTxPacketLength),
			  iAirMode(aAirMode)
			{}
			
	public:
		TUint8 iTransmissionInterval;
	    TUint8 iRetransmissionWindow;
	    TUint16 iRxPacketLength;
	    TUint16 iTxPacketLength;
	    TAirMode iAirMode;
	};

const TUint8 KSCODefaultTransmissionInterval = 4;
const TUint8 KSCODefaultRetransmissionWindow = 0;
const TUint16 KSCODefaultRxPacketLength = 20;
const TUint16 KSCOTxDefaultPacketLength = 20;
const TAirMode KSCODefaultAirMode = ECVSD;

NONSHARABLE_CLASS(TBTDevHCIVersion)
/** BT HCI version definition.
*/
	{
public:
	TUint8 iHCIVersion;		/*!< HCI version */
	TUint16 iHCIRevision;	/*!< HCI Revision */
	};

NONSHARABLE_CLASS(TBTDevLMPVersion)
/** BT Link Manager Protocol (LMP) version definition.
*/
	{
public:
	TUint8	iLMPVersion;		/*!< LMP version */
	TUint16	iManufacturerID;	/*!< Manufacturer ID */
	TUint16	iLMPSubVersion;		/*!< LMP sub version */ 
	};

NONSHARABLE_CLASS(TBTQOS)
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
