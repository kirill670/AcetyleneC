// HCITypes.h
// Common protocol-local HCI types 
// Copyright (c) 1999-2002 Symbian Ltd.  All rights reserved.

#ifndef HCITYPES_H__
#define HCITYPES_H__

#include <bttypes.h>

enum TLinkType
	{
	ESCOLink=0x00,
	EACLLink=0x01
	};

enum TEncryptMode
	{
	EDisabled=0x00,
	EPointToPoint,
	EAll
	};

enum THCIDeleteAllKeysFlag 
	{
	EDeleteBdaddrLinkKey=0x00,
	EDeleteAllLinkKeys=0x01
	};
 
enum THCITimeoutType
    {
    EConnectionAcceptTimeout,
    EPageTimeout,
    };

enum THCIReadAllKeysFlag
    {
    EReadBdaddrLinkKey=0x00,
    EReadAllLinkKeys=0x01,
    };

enum THCIEncryptModeFlag
    {
    EEncryptionDisabled=0x00,
    EPointToPointEncryption=0x01,
    EPointToPointAndBroadcastEncryption=0x02,
    };

enum THCIScanEnable 
    {
     ENoScansEnabled=0x00,          // 0x00
     EInquiryScanOnly,              // 0x01
     EPageScanOnly,                 // 0x02
     EInquiryAndPageScan            // 0x03
    };

enum THCILinkPolicySettings
     {
     EEnableMSSwitch     = 0x0001,
     EEnableHoldMode     = 0x0002,
     EEnableSniffMode    = 0x0004,
     EEnableParkMode     = 0x0008
     };

class THCIEventMask
    {
public:
    TUint32 iLoBytes;
    TUint32 iHiBytes;
    };

enum THCIEventFilterType {EClearAllFilters,
     EInquiryResultFilter,EConnectionSetupFilter};

class TBTDevAddr;
class THCIEventCondition
    {
public:
    THCIEventFilterType iEventFilterType;
    TUint8 iConditionType;
    // unionise this
    TUint iCoD;
    TUint iCoDMask;
    TBTDevAddr iDevAddr;
    TUint8 iAutoAcceptFlag;
    };

class TInquiryLogEntry
    {
public:
    TUint8 iPageScanRepetitionMode;
    TUint8 iPageScanPeriodMode;
    TUint8 iPageScanMode;
    TUint8 iSpare;
    TUint16 iClockOffset;
    TBTDevAddr iBdaddr;
    TUint	iCoD;
    };

class TBTConnect
    {
public:
    THCIConnHandle iConnH;
    TBTDevAddr iBdaddr;
    TUint iCoD;
    TLinkType iLinkType;
    TEncryptMode iEncryptMode;
    };

class TBTDevHCIVersion
	{
public:
	TUint8 iHCIVersion;
	TUint16 iHCIRevision;
	};

class TBTDevLMPVersion
	{
public:
	TUint8	iLMPVersion;
	TUint16	iManufacturerID;
	TUint16	iLMPSubVersion;
	};

class TBTQOS
	{
public:
	TUint8	iFlags;
	TUint8	iServiceType;
	TUint	iTokenRate;
	TUint	iPeakBandwidth;
	TUint	iLatency;
	TUint	iDelayVariation;
	};

typedef TBTDevLMPVersion TBTDevRemoteHwVersion;
typedef TUint16 THCIOpcode;
typedef TUint16 TBasebandTime;

// Transport

typedef TUint16 THCITransportChannel;

static const THCITransportChannel KHCITransportNoChannels		= 0x0000;
static const THCITransportChannel KHCITransportCommandChannel	= 0x0001;
static const THCITransportChannel KHCITransportACLDataChannel	= 0x0002;
static const THCITransportChannel KHCITransportSCODataChannel	= 0x0004;
static const THCITransportChannel KHCITransportAllChannels		= static_cast<THCITransportChannel>
																( KHCITransportCommandChannel
																| KHCITransportACLDataChannel 
																| KHCITransportSCODataChannel);


#endif
