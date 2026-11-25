// EtherCardIoc.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
// Produced for Symbian by CLF Consulting Ltd.
//
// This header provides the IO Control and Event codes used by the LDD and PDD. 
//

#if !defined(__ETHERIOC_H__)
#define __ETHERIOC_H__

// IOControl options.
const TUint8 KIoControlNullCommand=0x00; //Test use only
const TUint8 KIoControlResetCard=0x01;
const TUint8 KIoControlPowerUpCard=0x02;
const TUint8 KIoControlPowerDownCard=0x03;
const TUint8 KIoControlGetStats=0x04;
const TUint8 KIoControlResetStats=0x05;
const TUint8 KIoControlGetStatus=0x06;
const TUint8 KIoControlSetParameters=0x07;
const TUint8 KIoControlSetMACAddress=0x08;

// GetEvent options.
const TUint8 KEventNull=0x00; //Test use only
const TUint8 KEventEmergencyPowerDown=0x01;
const TUint8 KEventNormalPowerDown=0x02;
const TUint8 KEventPCCardReady=0x04;
const TUint8 KEventMediaOpen=0x08;

// Card configuration - speed settings.
const TUint8 KEthSpeedUnknown=0x00;
const TUint8 KEthSpeedAuto=0x01;
const TUint8 KEthSpeed10BaseT=0x02;
const TUint8 KEthSpeed100BaseTX=0x03;
const TUint8 KEthSpeedDefault=KEthSpeedAuto;

// Card configuration - duplex settings.
const TUint8 KEthDuplexUnknown=0x00;
const TUint8 KEthDuplexAuto=0x01;
const TUint8 KEthDuplexFull=0x02;
const TUint8 KEthDuplexHalf=0x03;
const TUint8 KEthDuplexDefault=KEthDuplexAuto;

// Card configuration - rx mode settings.
const TUint8 KEthRxModeUnknown=0x00;
const TUint8 KEthRxModeStation=0x01;
const TUint8 KEthRxModeBroadcast=0x02;
const TUint8 KEthRxModeMulticast=0x03;
const TUint8 KEthRxModePromisuous=0x04;
const TUint8 KEthRxModeDefault=KEthRxModeMulticast;

// Card parameter - general no change indicator.
const TUint8 KEthNoChange=0x00;
const TUint8 KEthNoSetting=0x00;
const TUint8 KEthModeOn=0x01;
const TUint8 KEthModeOff=0x02;

// Default Ethernet Address
const TUint8 KDefEtherAddByte0=0x31; // MSB
const TUint8 KDefEtherAddByte1=0x32;
const TUint8 KDefEtherAddByte2=0x33;
const TUint8 KDefEtherAddByte3=0x34;
const TUint8 KDefEtherAddByte4=0x35;
const TUint8 KDefEtherAddByte5=0x36; // LSB

const TUint KEthernetAddressLength=6;

// Card configuration - status alternatives.
const TUint8 KEthCardReady=0x00;
const TUint8 KEthCardNotReady=0xFF;

// Card configuration - precise status alternatives.
const TUint8 KIoControlCardNotPresent=0x01;
const TUint8 KIoControlCardNotReady=0x02;
const TUint8 KIoControlCardBad=0x03;
const TUint8 KIoControlCardReady=0x04;

class TPddPcCardStatistics
//
// Ethernet card statistics class.
//
	{
public:
	inline TPddPcCardStatistics() { Init(); }
	inline void Init()
		{
		iTxErrReclaim = iTxErrStatusOverflow = iTxErrMaxCollisions = 0;
		iTxErrUnderrun = iTxErrJabber = 0;
		iRxErrOverflow = iRxErrLength = iRxErrFrame = 0;
		iRxErrCrc = iRxErrPacketDropped = 0;
		iBadSSD = iUpperBytesOK = iCarrierLost = 0;
		iSqeErrors = iMultiCollFrames = iSingleCollFrames = iLateCollisions = 0;
		iRxOverruns = iFramesXmittedOK = iFramesRcvdOK = iFramesDeferred = 0;
		iUpperFramesOK = iBytesRcvdOK = iBytesXmittedOK = 0;
		iBadSSD = iUpperBytesOK = 0;
		iNumRxPackets = iNumTxPackets = iNumRxBytes = iNumTxBytes = 0; 
		}
public:
	// Driver statistics
	TUint iTxErrReclaim;
	TUint iTxErrStatusOverflow;
	TUint iTxErrMaxCollisions;
	TUint iTxErrUnderrun;
	TUint iTxErrJabber;
	TUint iRxErrOverflow;
	TUint iRxErrLength;
	TUint iRxErrFrame;
	TUint iRxErrCrc;
	TUint iRxErrPacketDropped;

	// Adapter statistics
	TUint iCarrierLost;
	TUint iSqeErrors;
	TUint iMultiCollFrames;
	TUint iSingleCollFrames;
	TUint iLateCollisions;
	TUint iRxOverruns;
	TUint iFramesXmittedOK;
	TUint iFramesRcvdOK;
	TUint iFramesDeferred;
	TUint iUpperFramesOK;
	TUint iBytesRcvdOK;
	TUint iBytesXmittedOK;
	TUint iBadSSD;
	TUint iUpperBytesOK;

	// Derived adapter statistics
	TUint iNumRxPackets;
	TUint iNumTxPackets;
	TUint iNumRxBytes;
	TUint iNumTxBytes;
	};

class TEtherConfig
//
// Ethernet card configuration class.
//
	{
public:
	TUint8 iStatus;
	TUint8 iEthSpeed;
	TUint8 iEthDuplex;
	TUint8 iEthAddress[KEthernetAddressLength];
	};

class TEtherParams
	{
public:
	inline TEtherParams()
		:	iEthSpeed(KEthNoChange), iEthDuplex(KEthNoChange), iRxMode(KEthNoChange),
			iSwFullDuplexMode(KEthNoChange), iIntLoopbackMode(KEthNoChange),
			iIntAppendCRCMode(KEthNoChange), iPadFramesMode(KEthNoChange)
		{}
public:
	TUint8 iCommand;
	TUint8 iEthSpeed;
	TUint8 iEthDuplex;
	TUint8 iRxMode;
	TUint8 iSwFullDuplexMode;
	TUint8 iIntLoopbackMode;
	TUint8 iIntAppendCRCMode;
	TUint8 iPadFramesMode;
	};

#endif
