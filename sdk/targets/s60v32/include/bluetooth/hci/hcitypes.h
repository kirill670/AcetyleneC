// Copyright (c) Symbian Software Ltd 2006.  All rights reserved.

/**
@file
@publishedPartner
*/

#ifndef HCITYPES_H
#define HCITYPES_H

#include <bttypes.h>


enum TBTHardResetState 
/**
Controller 'reset' states
*/
	{
	//NB In chronologically reverse order
	EBTResetComplete = 0x00, /*!< The reset process is complete. */
	EBTResetStarted = 0x01 /*!< The reset process has started. */
	};

enum TBTPowerState 
/**
Controller 'power' states
*/
	{
	EBTOn = 0x00, /*!< Power on. */
	EBTOff = 0x01 /*!< Power off. */
	};

enum TLinkType
/**
Bluetooth link type (ACL / SCO)
*/
	{
	ESCOLink = 0x00, /*!< Synchronous Connection Oriented link */
	EACLLink = 0x01, /*!< Asynchronous ConnectionLess link */
	EeSCOLink = 0x02 /*!< eSCO link */
	};

enum TEncryptMode
/**
Bluetooth encryption mode
*/
	{
	EDisabled = 0x00, /*!< Encryption disabled */
	EPointToPoint = 0x01, /*!< Point to point encryption enabled */
	EAll = 0x02 /*!< Device wide encryption enabled */
	};

enum TAirMode
/**
Air mode of synchronous connection
*/
	{
	ECVSD = 0x00, /*!< CVSD */
	EuLawLog = 0x01, /*!< u-law log */
	EALawLog = 0x02, /*!< A-law log */
	ETransparentData = 0x03	/*!< Transparent data */
	};

enum THCIDeleteAllKeysFlag
/**
HCI delete all keys flag
*/
	{
	EDeleteBdaddrLinkKey = 0x00, /*!< Delete Bluetooth device address link key */
	EDeleteAllLinkKeys = 0x01 /*!< Delete all link keys */
	};
 
enum THCITimeoutType
/**
HCI timeout type
*/
    {
    EConnectionAcceptTimeout = 0x00, /*!< Connection accept timeout */
    EPageTimeout = 0x01, /*!< Page timeout */
    };

enum THCIReadAllKeysFlag
/**
HCI read all keys flag
*/
    {
    EReadBdaddrLinkKey = 0x00, /*!< Read Bluetooth device address link key */
    EReadAllLinkKeys = 0x01, /*!< Read all link keys */
    };

enum THCIEncryptModeFlag
/**
HCI encryption mode flag
*/
    {
    EEncryptionDisabled = 0x00, /*!< Encryption disabled */
    EPointToPointEncryption = 0x01, /*!< Point to point encryption enabled */
    EPointToPointAndBroadcastEncryption = 0x02, /*!< Point to point and broadcast encryption enabled */
    };

enum THCIScanEnable 
/**
HCI Scan enable mask
*/
    {
     ENoScansEnabled = 0x00, /*!< No HCI scans enabled */
     EInquiryScanOnly = 0x01, /*!< HCI inquiry scan enabled */
     EPageScanOnly = 0x02, /*!< HCI page scan enabled */
     EInquiryAndPageScan = 0x03 /*!< HCI inquiry and page scan enabled */
    };

NONSHARABLE_CLASS(THCIEventMask)
/**
HCI event mask
This can be used to specify the mask used to control which events the controller reports.
*/
    {
public:
    TUint32 iLoBytes; /*!< Least significant bytes (bytes 0 - 3) */
    TUint32 iHiBytes; /*!< Most significant bytes (bytes 4 - 7) */
    };

enum THCIEventFilterType
/**
HCI event filter type
*/ 
	{
	EClearAllFilters = 0x00, /*!< Clear all filters */
    EInquiryResultFilter = 0x01, /*!< Inquiry result filter */
    EConnectionSetupFilter = 0x02 /*!< Connection setup filter */
    };

NONSHARABLE_CLASS(THCIEventCondition)
/**
HCI event condition definition.
*/
    {
public:
    THCIEventFilterType iEventFilterType; /*!< Event filter type */
    TUint8 iConditionType; /*!< Condition type */
    TUint iCoD; /*!< Class of device */
    TUint iCoDMask; /*!< Class of device mask */
    TBTDevAddr iDevAddr; /*!< Bluetooth device address */
    TUint8 iAutoAcceptFlag; /*!< Auto accept flag */
    };

NONSHARABLE_CLASS(TInquiryLogEntry)
/**
Inquiry log entry.  Used to pass information from a BT inquiry operation.
*/
    {
public:
    TUint8 iPageScanRepetitionMode; /*!< Page scan repetition mode */
    TUint8 iPageScanPeriodMode; /*!< Page scan period mode */
    TUint8 iPageScanMode; /*!< Page scan mode */
/**
Not used: iSpare
@internalComponent
*/
    TUint8 iSpare;

    TUint16 iClockOffset; /*!< Clock offset */
    TBTDevAddr iBdaddr; /*!< Bluetooth device address */
    TUint iCoD; /*!< Class of device */
    };

NONSHARABLE_CLASS(TBTConnect)
/**
Definition of the parameters required to make a HCI connection.
*/
    {
public:
    THCIConnHandle iConnH; /*!< Handle to the HCI connection */
    TBTDevAddr iBdaddr; /*!< Bluetooth device address */
    TUint iCoD; /*!< Class of device */
    TLinkType iLinkType; /*!< Link type (ACL / SCO) */
/**
Encryption mode 
@see TEncryptMode
*/
    TEncryptMode iEncryptMode;
    };

NONSHARABLE_CLASS(TBTSyncConnectOpts)
/**
Parameters returned by HCI after a successful Synchronous connection.
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

NONSHARABLE_CLASS(TBTDevHCIVersion)
/**
BT HCI version definition.
*/
	{
public:
	TUint8 iHCIVersion; /*!< HCI version */
	TUint16 iHCIRevision; /*!< HCI Revision */
	};

NONSHARABLE_CLASS(TBTDevLMPVersion)
/**
BT Link Manager Protocol (LMP) version definition.
*/
	{
public:
	TUint8 iLMPVersion; /*!< LMP version */
	TUint16	iManufacturerID; /*!< Manufacturer ID */
	TUint16	iLMPSubVersion; /*!< LMP sub version */ 
	};

NONSHARABLE_CLASS(TBTQOS)
/**
BT quality of service definition.
@see BT code specification.
*/
	{
public:
	TUint8 iFlags; /*!< QoS flags */ 
	TUint8 iServiceType; /*!< Service type */
	TUint iTokenRate; /*!< Token rate */
	TUint iPeakBandwidth; /*!< Peak bandwidth */
	TUint iLatency; /*!< Latency */
	TUint iDelayVariation; /*!< Delay variation */
	};

/**
Connection handle class for use in the HCI API.

Although THCIConnHandle is a valid type to use for representing 
a connection handle, as there are commands that require an array
of the type to be provided, RArray instances are used as the
API. The type contents RArrays use must be at a minimum 4 bytes
in size.  This class provides a 4 byte encapsulation of a 2 byte
connection handle.

@see THCIConnHandle.
*/
NONSHARABLE_CLASS(THCIConnectionHandle)
	{
public:
	IMPORT_C THCIConnectionHandle();
	IMPORT_C THCIConnectionHandle(THCIConnHandle aConnHandle);
	IMPORT_C THCIConnectionHandle& operator=(THCIConnHandle aConnHandle);

	IMPORT_C THCIConnHandle ConnHandle() const;
	IMPORT_C operator THCIConnHandle() const;

private:
	THCIConnHandle iConnHandle;
	TUint16 iPad; // To pad the class out making it 4 bytes in total (for use in RArray).
	};

/**
Class for reporting the number of completed packets by either the
host or the controller over the HCI API.

Although a simple TUint16 would be sufficient, as there are commands
that require an array of the type to be provided as RArray instances
are used as the API. The type contents RArrays use must be at a 
minimum 4 bytes in size.  This class provides a 4 byte encapsulation
of a 2 byte value representing the {Host,HC}NumOfCompletedPackets.
*/
NONSHARABLE_CLASS(THCINumOfCompletedPackets)
	{
public:
	IMPORT_C THCINumOfCompletedPackets();
	IMPORT_C THCINumOfCompletedPackets(TUint16 aNumOfCompletedPackets);
	IMPORT_C THCINumOfCompletedPackets& operator=(TUint16 aNumOfCompletedPackets);

	IMPORT_C TUint16 NumOfCompletedPackets() const;
	IMPORT_C operator TUint16() const;

private:
	TUint16 iNumOfCompletedPackets;
	TUint16 iPad; // To pad the class out making it 4 bytes in total (for use in RArray).
	};

NONSHARABLE_CLASS(THCIClockOffset)
	{
public:
	IMPORT_C THCIClockOffset();
	IMPORT_C THCIClockOffset(TUint16 aClockOffset);
	IMPORT_C THCIClockOffset& operator=(TUint16 aClockOffset);

	IMPORT_C TUint16 ClockOffset() const;
	IMPORT_C operator TUint16() const;

private:
	TUint16 iClockOffset;
	TUint16 iPad; // To pad the class out making it 4 bytes in total (for use in RArray).
	};

NONSHARABLE_CLASS(THCIPageScanRepetitionMode)
	{
public:
	IMPORT_C THCIPageScanRepetitionMode();
	IMPORT_C THCIPageScanRepetitionMode(TUint8 aPageScanRepetitionMode);
	IMPORT_C THCIPageScanRepetitionMode& operator=(TUint8 aPageScanRepetitionMode);

	IMPORT_C TUint8 PageScanRepetitionMode() const;
	IMPORT_C operator TUint8() const;

private:
	TUint8 iPageScanRepetitionMode;
	TUint8 iPad1; // To pad the class out making it 4 bytes in total (for use in RArray).
	TUint16 iPad2;
	};

NONSHARABLE_CLASS(THCIReservedOctet)
	{
public:
	IMPORT_C THCIReservedOctet();
	IMPORT_C THCIReservedOctet(TUint8 aReservedOctet);
	IMPORT_C THCIReservedOctet& operator=(TUint8 aReservedOctet);

	IMPORT_C TUint8 ReservedOctet() const;
	IMPORT_C operator TUint8() const;

private:
	TUint8 iReservedOctet;
	TUint8 iPad1; // To pad the class out making it 4 bytes in total (for use in RArray).
	TUint16 iPad2;
	};
	
NONSHARABLE_CLASS(THCIRssi)
	{
public:
	IMPORT_C THCIRssi();
	IMPORT_C THCIRssi(TUint8 aRssi);
	IMPORT_C THCIRssi& operator=(TUint8 aRssi);

	IMPORT_C TUint8 Rssi() const;
	IMPORT_C operator TUint8() const;

private:
	TUint8 iRssi;
	TUint8 iPad1; // To pad the class out making it 4 bytes in total (for use in RArray).
	TUint16 iPad2;
	};

typedef TBTDevLMPVersion TBTDevRemoteHwVersion; /*!< Definition of the TBTDevRemoteHwVersion type */
typedef TUint16 THCIOpcode; /*!< Definition of the THCIOpcode type */
typedef TUint16 TBasebandTime; /*!< Definition of the TBasebandTime type */

// HCITYPES_H
#endif
