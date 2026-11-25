// HCIBase.H
// This is the API that the bluetooth stack expects from the HCI layer.
// It comprises an event notification interface and a command sending interface.
// Implementations of the HCI must derive from CHCIBase.

// Copyright (c) 1999-2002 Symbian Ltd.  All rights reserved.

#ifndef BT_HCIBASE_H_
#define BT_HCIBASE_H_

#include <bttypes.h>
#include <hcierrors.h>
#include <hcitypes.h>
#include <e32base.h>

class CHCICommandFrame;
class CHCIACLDataFrame;

/**********************************************/
/* Protocol constants                         */
/**********************************************/

// HCI Command opcodes are built up as follows:
//
//      lower 10 bit OCF | upper 6 bit OGF
//
// The OGF distinguishes the command subgroup and the OCF 
// determines the command within the subgroup.  Here
// individual opcodes are constructed by shifting the OGF 
// up by 10 and or'ing with the command OCF.

// ************* HCI Command Opcodes ***********************
// SUBGROUP 0x01 - LINK CONTROL
const THCIOpcode KLinkControlOGF                   =0x0001<<10;
const THCIOpcode KInquiryOpcode                    =0x0001|KLinkControlOGF;
const THCIOpcode KInquiryCancelOpcode              =0x0002|KLinkControlOGF;
const THCIOpcode KPeriodicInquiryModeOpcode        =0x0003|KLinkControlOGF;
const THCIOpcode KExitPeriodicInquiryModeOpcode    =0x0004|KLinkControlOGF;
const THCIOpcode KCreateACLConnectionOpcode        =0x0005|KLinkControlOGF;
const THCIOpcode KDisconnectOpcode                 =0x0006|KLinkControlOGF;
const THCIOpcode KAddSCOConnectionOpcode           =0x0007|KLinkControlOGF;
const THCIOpcode KAcceptConnectionRequestOpcode    =0x0009|KLinkControlOGF;
const THCIOpcode KRejectConnectionRequestOpcode    =0x000a|KLinkControlOGF;
const THCIOpcode KLinkKeyRequestReplyOpcode        =0x000b|KLinkControlOGF;
const THCIOpcode KLinkKeyRequestReplyNegativeOpcode=0x000c|KLinkControlOGF;
const THCIOpcode KPINCodeRequestReplyOpcode        =0x000d|KLinkControlOGF;
const THCIOpcode KPINCodeRequestReplyNegativeOpcode=0x000e|KLinkControlOGF;
const THCIOpcode KChangeConnectionPacketTypeOpcode =0x000f|KLinkControlOGF;
const THCIOpcode KAuthenticationRequestedOpcode    =0x0011|KLinkControlOGF;
const THCIOpcode KSetConnectionEncryptionOpcode    =0x0013|KLinkControlOGF;
const THCIOpcode KChangeLinkKeyOpcode              =0x0015|KLinkControlOGF;
const THCIOpcode KChangeMasterLinkKeyOpcode        =0x0017|KLinkControlOGF;
const THCIOpcode KRemoteNameRequestOpcode          =0x0019|KLinkControlOGF;
const THCIOpcode KReadRemoteSupportedFeaturesOpcode=0x001b|KLinkControlOGF;
const THCIOpcode KReadRemoteVersionInfoOpcode      =0x001d|KLinkControlOGF;
const THCIOpcode KReadClockOffsetOpcode            =0x001f|KLinkControlOGF;
// SUBGROUP 0x02 - LINK POLICY
const THCIOpcode KLinkPolicyOGF				=0x0002<<10;
const THCIOpcode KHoldModeOpcode				=0x0001|KLinkPolicyOGF;
const THCIOpcode KSniffModeOpcode				=0x0003|KLinkPolicyOGF;
const THCIOpcode KExitSniffModeOpcode			=0x0004|KLinkPolicyOGF;
const THCIOpcode KParkModeOpcode				=0x0005|KLinkPolicyOGF;
const THCIOpcode KExitParkModeOpcode			=0x0006|KLinkPolicyOGF;
const THCIOpcode KQOSSetupOpcode				=0x0007|KLinkPolicyOGF;
const THCIOpcode KRoleDiscoveryOpcode			=0x0009|KLinkPolicyOGF;
const THCIOpcode KSwitchRoleOpcode				=0x000b|KLinkPolicyOGF;
const THCIOpcode KReadLinkPolicySettingsOpcode	=0x000c|KLinkPolicyOGF;
const THCIOpcode KWriteLinkPolicySettingsOpcode=0x000d|KLinkPolicyOGF;


// SUBGROUP 0x03 - HOST CONTROLLER AND BASEBAND
const THCIOpcode KHCBasebandOGF                        =0x0003<<10;
const THCIOpcode KSetEventMaskOpcode                   =0x0001|KHCBasebandOGF;
const THCIOpcode KResetOpcode                          =0x0003|KHCBasebandOGF;
const THCIOpcode KSetEventFilterOpcode                 =0x0005|KHCBasebandOGF;
const THCIOpcode KFlushOpcode                          =0x0008|KHCBasebandOGF;
const THCIOpcode KReadPINTypeOpcode                    =0x0009|KHCBasebandOGF;
const THCIOpcode KWritePINTypeOpcode                   =0x000a|KHCBasebandOGF;
const THCIOpcode KCreateNewUnitKeyOpcode               =0x000b|KHCBasebandOGF;
const THCIOpcode KReadStoredLinkKeyOpcode              =0x000d|KHCBasebandOGF;
const THCIOpcode KWriteStoredLinkKeyOpcode             =0x0011|KHCBasebandOGF;
const THCIOpcode KDeleteStoredLinkKeyOpcode            =0x0012|KHCBasebandOGF;
const THCIOpcode KChangeLocalNameOpcode                =0x0013|KHCBasebandOGF;
const THCIOpcode KReadLocalNameOpcode                  =0x0014|KHCBasebandOGF;
const THCIOpcode KReadConnectionAcceptTimeoutOpcode    =0x0015|KHCBasebandOGF;
const THCIOpcode KWriteConnectionAcceptTimeoutOpcode   =0x0016|KHCBasebandOGF;
const THCIOpcode KReadPageTimeoutOpcode                =0x0017|KHCBasebandOGF;
const THCIOpcode KWritePageTimeoutOpcode               =0x0018|KHCBasebandOGF;
const THCIOpcode KReadScanEnableOpcode                 =0x0019|KHCBasebandOGF;
const THCIOpcode KWriteScanEnableOpcode                =0x001a|KHCBasebandOGF;
const THCIOpcode KReadPageScanActivityOpcode           =0x001b|KHCBasebandOGF;
const THCIOpcode KWritePageScanActivityOpcode          =0x001c|KHCBasebandOGF;
const THCIOpcode KReadInquiryScanActivityOpcode        =0x001d|KHCBasebandOGF;
const THCIOpcode KWriteInquiryScanActivityOpcode       =0x001e|KHCBasebandOGF;
const THCIOpcode KReadAuthenticationEnableOpcode       =0x001f|KHCBasebandOGF;
const THCIOpcode KWriteAuthenticationEnableOpcode      =0x0020|KHCBasebandOGF;
const THCIOpcode KReadEncryptionModeOpcode             =0x0021|KHCBasebandOGF;
const THCIOpcode KWriteEncryptionModeOpcode            =0x0022|KHCBasebandOGF;
const THCIOpcode KReadClassOfDeviceOpcode              =0x0023|KHCBasebandOGF;
const THCIOpcode KWriteClassOfDeviceOpcode             =0x0024|KHCBasebandOGF;
const THCIOpcode KReadVoiceSettingOpcode               =0x0025|KHCBasebandOGF;
const THCIOpcode KWriteVoiceSettingOpcode              =0x0026|KHCBasebandOGF;
const THCIOpcode KReadAutomaticFlushTimeoutOpcode		=0x0027|KHCBasebandOGF;
const THCIOpcode KWriteAutomaticFlushTimeoutOpcode		=0x0028|KHCBasebandOGF;
const THCIOpcode KReadNumBroadcastRetransmissionsOpcode	=0x0029|KHCBasebandOGF;
const THCIOpcode KWriteNumBroadcastRetransmissionsOpcode	=0x002A|KHCBasebandOGF;
const THCIOpcode KReadHoldModeActivityOpcode				=0x002B|KHCBasebandOGF;
const THCIOpcode KWriteHoldModeActivityOpcode				=0x002C|KHCBasebandOGF;
const THCIOpcode KReadTransmitPowerLevelOpcode				=0x002D|KHCBasebandOGF;
const THCIOpcode KReadSCOFlowControlEnableOpcode			=0x002E|KHCBasebandOGF;
const THCIOpcode KWriteSCOFlowControlEnableOpcode			=0x002F|KHCBasebandOGF;
const THCIOpcode KSetHostControllerToHostFlowOpcode		=0x0031|KHCBasebandOGF;
const THCIOpcode KHostBufferSizeOpcode						=0x0033|KHCBasebandOGF;
const THCIOpcode KHostNumberOfCompletedPacketsOpcode		=0x0035|KHCBasebandOGF; 
const THCIOpcode KReadLinkSupervisionTimeoutOpcode			=0x0036|KHCBasebandOGF; 
const THCIOpcode KWriteLinkSupervisionTimeoutOpcode		=0x0037|KHCBasebandOGF; 
const THCIOpcode KReadNumberOfSupportedIACOpcode			=0x0038|KHCBasebandOGF;
const THCIOpcode KReadCurrentIACLAPOpcode					=0x0039|KHCBasebandOGF;
const THCIOpcode KWriteCurrentIACLAPOpcode					=0x003A|KHCBasebandOGF;
const THCIOpcode KReadPageScanPeriodOpcode					=0x003B|KHCBasebandOGF;
const THCIOpcode KWritePageScanPeriodOpcode				=0x003C|KHCBasebandOGF;
const THCIOpcode KReadPageScanOpcode						=0x003D|KHCBasebandOGF;
const THCIOpcode KWritePageScanOpcode						=0x003E|KHCBasebandOGF;

// SUBGROUP 0x04 - INFORMATIONAL
const THCIOpcode KInfoOGF                          =0x0004<<10;
const THCIOpcode KReadLocalVersionInfoOpcode       =0x0001|KInfoOGF;
const THCIOpcode KReadLocalSupportedFeaturesOpcode =0x0003|KInfoOGF;
const THCIOpcode KReadBufferSizeOpcode             =0x0005|KInfoOGF;
const THCIOpcode KReadCountryCodeOpcode            =0x0007|KInfoOGF;
const THCIOpcode KReadBdaddrOpcode                 =0x0009|KInfoOGF;

// SUBGROUP 0x05 - STATUS
const THCIOpcode KStatusOGF                        =0x0005<<10;
const THCIOpcode KReadFailedContactCounterOpcode   =0x0001|KStatusOGF;
const THCIOpcode KResetFailedContactCounterOpcode  =0x0002|KStatusOGF;
const THCIOpcode KGetLinkQualityOpcode             =0x0003|KStatusOGF;
const THCIOpcode KReadRSSIOpcode                   =0x0005|KStatusOGF;

// SUBGROUP 0x06 - TESTING
const THCIOpcode KTestingOGF                       =0x0006<<10;
const THCIOpcode KReadLoopbackModeOpcode           =0x0001|KTestingOGF;
const THCIOpcode KWriteLoopbackModeOpcode          =0x0002|KTestingOGF;
const THCIOpcode KEnableDeviceUnderTestModeOpcode  =0x0003|KTestingOGF;

// SUBGROUP 0xFF - Vendor Specific Commands
const THCIOpcode KVendorDebugOGF					=0x003f<<10;
const THCIOpcode KSomeVendorSpecificCommand        =0x0001|KVendorDebugOGF;
const THCIOpcode KOGFMask					        =0xFC00; //top six bits of opcode

// ACL Data Packet Flags
const TUint8 KPacketDataFlagMask=0xf0;  // operates on hi connH byte
// Packet Boundary Flags
const TUint8 KContinuingFragment=0x10;
const TUint8 KFirstHLFragment=0x20;
// PacketBroadcast Flags
const TUint8 KPointToPointOnly=0x00;
const TUint8 KActiveBroadcast=0x40;
const TUint8 KPiconetBroadcast=0x80;

// Common packet types
const TUint16 KDM1Packet=0x0008;
// ACL only packet types
const TUint16 KDH1Packet=0x0010;
const TUint16 KAUX1Packet=0x0200;
const TUint16 KDM3Packet=0x0400;
const TUint16 KDH3Packet=0x0800;
const TUint16 KDM5Packet=0x4000;
const TUint16 KDH5Packet=0x8000;
// SCO only packet types
const TUint16 KHV1Packet=0x0020;
const TUint16 KHV2Packet=0x0040;
const TUint16 KHV3Packet=0x0080;
const TUint16 KDVPacket=0x0100;

const TInt KHCILocalDeviceNameMaxLength=248;
const TInt KHCIRemoteDeviceNameMaxLength=KHCILocalDeviceNameMaxLength;

// Inquiry stuff - see page 562 of BT Standard 1.1
const TUint8  KHCIMaximumAmountOfInquiryTime=0x30;

// Event stuff
const TUint8  KHCIRemoteNameReqCompleteEventPacketLength=255;

// Power stuff
enum TPowerState {EBTOn, EBTOff};

class CHCIBase;
class MHCIEventObserver;
class CESockIniData;

/**
	Factory for creating CHCIBase derived class.
	To provide a new HCI implementation, re-implement this
	class in a DLL, which has a factory fucntion at oridnal 1
	which returns a TAny* to the instance of this factory.
	NewHCIL() will then be called on the factory to actually
	create the CHCIBase derived object.
**/	
class CHCIFactory : public CBase
    {
// Factory base for creating a concrete instance of a CHCI
public: 
	CHCIFactory();
    virtual TVersion Version() const;
    virtual CHCIBase* NewHCIL(MHCIEventObserver* aParent, CESockIniData* aIni=0);
	virtual CHCICommandFrame* NewHCICommandFrameL(THCIOpcode aOpcode);
	virtual CHCIACLDataFrame* NewHCIACLDataFrameL(TUint16 aSize);
	};


/**
	Abstract HCI Interface class.
	The Symbian Bluetooth stack uses this abstract class as the 
	polymorphic base through which it obtains host controller
	access. The actual implementation is dependent on the DLL
	loaded at run-time, as specified in the bt.esk file.
	The concrete class derived from this should be returned
	by the CHCIFactory class, located through ordinal 1 in the
	polymorphic DLL.
	@see 
	CHCI for detailed description of the functions.
	MHCIEventObserver for the callback interface for events received over HCI.
**/ 

class CHCIBase : public CBase
	{
public:

	virtual TInt WriteCommand(const CHCICommandFrame& aFrame)=0;

	// HCI General exports
    virtual TInt SetOption(TUint aName,const TDesC8& aData)=0;
    virtual TInt GetOption(TUint aName,TDes8& aData)=0;
	
	// HCI Data Calls
    virtual void FormatACLData(CHCIACLDataFrame& aFrame, THCIConnHandle aConnH,TUint8 aFlags,const TDesC8& aData)=0;
	virtual TInt WriteACLData(const CHCIACLDataFrame& aFrame)=0;
    virtual TInt WriteSCOData(const TDesC8& aData)=0;

	// HCI Frame information commands
	virtual THCIConnHandle FrameConnectionHandle(CHCIACLDataFrame& aFrame)=0;
	virtual THCIOpcode FrameOpcode(CHCICommandFrame& aFrame)=0;
	
	// HCI Commands
    virtual void Inquiry(CHCICommandFrame& aFrame, const TUint aCode=KGIAC, const TUint8 aLength=10, const TUint8 aNumResponses=0)=0;
    virtual void InquiryCancel(CHCICommandFrame& aFrame)=0;
	virtual void PeriodicInquiryMode(CHCICommandFrame& aFrame, TUint16 aMax,TUint16 aMin, const TUint aCode=0,const TUint8 aLength=2,const TUint8 aNumResponses=0)=0;
    virtual void ExitPeriodicInquiryMode(CHCICommandFrame& aFrame)=0;
    virtual void CreateConnection(CHCICommandFrame& aFrame, const TBTDevAddr& aBdaddr,
					TUint16 aPacketType=KDM1Packet, TUint8 aPageScanRepetitionMode=0,
					TUint8 aPageScanMode=0, TUint16 aClockOffset=0, TUint8 aAllowRoleSwitch=1)=0;
    virtual void AddSCOConnection(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle,TUint16 aPacketType)=0;
    virtual void AcceptConnectionRequest(CHCICommandFrame& aFrame, const TBTDevAddr& aBdaddr,TUint8 aRole)=0;
    virtual void RejectConnectionRequest(CHCICommandFrame& aFrame, const TBTDevAddr& aBdaddr,THCIErrorCode aReason)=0;
    virtual void LinkKeyRequestReply(CHCICommandFrame& aFrame, const TBTDevAddr& aBdaddr,const TDesC8& aLinkKey)=0;
    virtual void LinkKeyRequestNegativeReply(CHCICommandFrame& aFrame, const TBTDevAddr& aBdaddr)=0;
    virtual void PINCodeRequestReply(CHCICommandFrame& aFrame, const TBTDevAddr& aBdaddr,const TDesC8& aPIN)=0; 
    virtual void PINCodeRequestNegativeReply(CHCICommandFrame& aFrame, const TBTDevAddr& aBdaddr)=0; 
	virtual void Disconnect(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle,THCIErrorCode aReason)=0;
    virtual void ChangeConnectionPacketType(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle,TUint16 aType)=0;
    virtual void AuthenticationRequest(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle)=0;
    virtual void SetEncryptionEnable(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle,TBool aEnable)=0;
    virtual void ChangeConnectionLinkKey(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle)=0;
    virtual void MasterLinkKey(CHCICommandFrame& aFrame, TBool aKeyFlag)=0;
    virtual void ReadRemoteSupportedFeatures(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle)=0;
    virtual void ReadRemoteVersionInfo(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle)=0;
    virtual void RemoteNameRequest(CHCICommandFrame& aFrame, const TBTDevAddr& aBdaddr, TUint8 aPageScanRepetitionMode=0,
					TUint8 aPageScanMode=0, TBasebandTime aClockOffset=0)=0;
    virtual void ReadClockOffset(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle)=0;
	
	// HCI Link Policy Commands 
    virtual void HoldMode(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle, TBasebandTime aHoldMaxInterval, 
		TBasebandTime aHoldMinInterval)=0;
    virtual void SniffMode(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle,TBasebandTime aSniffMaxInterval,TBasebandTime
		aSniffMinInterval, TBasebandTime aAttempSlots, TBasebandTime aTimeOutSlots)=0;
    virtual void ExitSniffMode(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle)=0;
    virtual void ParkMode(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle, TBasebandTime aBeaconMaxInterval, 
		TBasebandTime aBeaconMinInterval)=0;
    virtual void ExitParkMode(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle)=0;

    virtual void RoleDiscovery(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle)=0;

	virtual void WriteLinkPolicySettings(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle, TUint16 aLinkPolicySettings)=0;	
	// HCI Host Controller and Baseband Commands 
    virtual void SetEventMask(CHCICommandFrame& aFrame, const THCIEventMask& aMask)=0;
    virtual void Reset(CHCICommandFrame& aFrame)=0;
    virtual void SetEventFilter(CHCICommandFrame& aFrame, const THCIEventCondition& aData)=0;
    virtual void Flush(CHCICommandFrame& aFrame, THCIConnHandle aConnHandle)=0;
    virtual void CreateNewUnitKey(CHCICommandFrame& aFrame)=0;
    virtual void ReadStoredLinkKey(CHCICommandFrame& aFrame, const TBTDevAddr& aBdaddr,THCIReadAllKeysFlag aFlag)=0;
    virtual void WriteStoredLinkKey(CHCICommandFrame& aFrame, /*TUint8 aNumOfKeysToWrite,*/
		const TBTDevAddr& aBdaddr,const TDesC8& aLinkKey)=0;
    virtual void DeleteStoredLinkKey(CHCICommandFrame& aFrame, const TBTDevAddr& aBdaddr,THCIDeleteAllKeysFlag aFlag)=0;
    virtual void ChangeLocalName(CHCICommandFrame& aFrame, const TDesC8& aName)=0;
	virtual void ReadLocalName(CHCICommandFrame& aFrame)=0;
    virtual void ReadConnectionAcceptTimeout(CHCICommandFrame& aFrame)=0;

    virtual void WriteConnectionAcceptTimeout(CHCICommandFrame& aFrame, TBasebandTime aTimeout)=0;
    
	virtual void ReadPageTimeout(CHCICommandFrame& aFrame)=0;
    virtual void WritePageTimeout(CHCICommandFrame& aFrame, TBasebandTime aTimeout)=0;

    virtual void ReadScanEnable(CHCICommandFrame& aFrame)=0;
    virtual void WriteScanEnable(CHCICommandFrame& aFrame, THCIScanEnable aEnable=EInquiryAndPageScan)=0;
	
	virtual void ReadNumberOfSupportedIAC(CHCICommandFrame& aFrame)=0;
    virtual void WriteCurrentIACLAP(CHCICommandFrame& aFrame, TUint8 aNumCurrentIAC, TUint aIAC_LAP[])=0;
	virtual void ReadCurrentIACLAP(CHCICommandFrame& aFrame)=0;
    virtual void ReadAuthenticationEnable(CHCICommandFrame& aFrame)=0;
    virtual void WriteAuthenticationEnable(CHCICommandFrame& aFrame, TBool aAuthEnable)=0;
    virtual void ReadEncryptionMode(CHCICommandFrame& aFrame)=0;
    virtual void WriteEncryptionMode(CHCICommandFrame& aFrame, THCIEncryptModeFlag aFlag)=0;
    virtual void ReadClassOfDevice(CHCICommandFrame& aFrame)=0;
    virtual void WriteClassOfDevice(CHCICommandFrame& aFrame, TUint aCoD)=0;
	virtual void ReadVoiceSetting(CHCICommandFrame& aFrame)=0;
	virtual void WriteVoiceSetting(CHCICommandFrame& aFrame, TInt16 aVoiceChannelSetting)=0;
    
	// HCI Informational Parameters Commands
	virtual void ReadLocalVersionInformation(CHCICommandFrame& aFrame)=0;
	virtual void ReadLocalSupportedFeatures(CHCICommandFrame& aFrame)=0;
    virtual void ReadBufferSize(CHCICommandFrame& aFrame)=0;    
	virtual void ReadCountryCode(CHCICommandFrame& aFrame)=0;
    virtual void ReadBDADDR(CHCICommandFrame& aFrame)=0;
#ifdef ACL_QUERY_FUNCS
	virtual TUint16 ReadACLReportingInterval() = 0; // Some hardware only reports on the nth ACL data packet being sent
	                                                // this is an opportunity for the HCI to supply a minimum value of n
													// to the Link Manager
	virtual TUint16 ReadACLFramingOverhead() = 0; // Size of HCI framing overhead per frame
#endif
	
	// Host Controller to Host Data Flow Control
    virtual void SetHostControllerToHostFlowControl(CHCICommandFrame& aFrame, TBool aHC2HFlowFlag)=0;// may return KErrNoMemory

	virtual void HostNumberOfCompletedPackets(CHCICommandFrame& aFrame, TUint8 aNumHandles, THCIConnHandle aConnH[], TUint16 aCompletedPacketsNo[])=0;
	virtual void HostBufferSize(CHCICommandFrame& aFrame, TUint16 aACLDataLength,TUint8 aSCODataLength,
        TUint16 aTotalACLPackets, TUint16 aTotalSCOPackets)=0;

	virtual void WriteLinkSupervisionTimeout(CHCICommandFrame& aFrame, THCIConnHandle aConnH, TBasebandTime aTimeout)=0;
	virtual void WriteVendorRawFrameCommand(CHCICommandFrame& aFrame, const TDesC8& aData)=0;


	// HCI Status Parameters Commands
	// not here yet
	
	// HCI Testing Commands
	// not here yet 
	virtual TAny *LogIndex() const=0;
	};

enum THCIErrorCode;



/**
	Event handler mixin that must be implemented by the client of HCI.
	A class that implements this interface must be passed into the
	CHCIBase derived class on construction, and will be used by the HCI
	class to notify the client of events received over the HCI interface.
**/
class MHCIEventObserver  // mixin that must be implemented by the HCI client
    {   
public:
	// Interfaces to allow HCI to notify LL
	virtual void SetCommandCredits(TUint16 aCredits)=0;
	virtual void HCIMaximumACLPacketSize(TUint16 aMTU)=0;
	virtual void CanSend(THCITransportChannel aChannel = KHCITransportAllChannels)=0;
	// Events as per spec
    virtual void InquiryCompleteEvent(THCIErrorCode aErr, TUint8 aNumResponses)=0;
    virtual void InquiryResultCompleteEvent(THCIErrorCode aErr,const TInquiryLogEntry& aEntry)=0;
    virtual void ConnectionCompleteEvent(THCIErrorCode aErr, const TBTConnect &aConn)=0;
    virtual void ConnectionRequestEvent(const TBTConnect &aConn)=0;
    virtual void DisconnectionCompleteEvent(THCIErrorCode aErr, THCIConnHandle aConnH, THCIErrorCode aReason)=0;
    virtual void AuthenticationCompleteEvent(THCIErrorCode aErr, THCIConnHandle aConnH)=0;
    virtual void RemoteNameReqCompleteEvent(THCIErrorCode aErr, const TBTDevAddr& aBdaddr, const TDesC8& aBuf)=0;
    virtual void EncryptionChangeEvent(THCIErrorCode aErr, THCIConnHandle aConnH,TBool aEnable)=0;
    virtual void ChangeLinkKeyCompleteEvent(THCIErrorCode aErr, THCIConnHandle aConnH)=0;
    virtual void MasterLinkKeyCompleteEvent(THCIErrorCode aErr, THCIConnHandle aConnH,TBool aKeyFlag)=0;
    virtual void ReadRemoteSupportedFeaturesCompleteEvent(THCIErrorCode aErr, THCIConnHandle aConnH, TUint32 aBitMaskList)=0;
	virtual void ReadRemoteVersionInfoCompleteEvent(THCIErrorCode aErr, THCIConnHandle aConnH, const TBTDevRemoteHwVersion& aVer)=0;
	virtual void QOSSetupCompleteEvent(THCIErrorCode aErr, THCIConnHandle aConnH, TBTQOS aQOS)=0;
    virtual void CommandCompleteEvent(THCIErrorCode aErr,THCIOpcode aOpcode)=0;
    virtual void CommandStatusEvent(THCIOpcode aOpcode)=0;
    virtual void HardwareErrorEvent(TUint8 aHwCode)=0;
	virtual void FlushOccurredEvent(THCIErrorCode aErr, THCIConnHandle aConnH)=0;
    virtual void RoleChangeEvent(THCIErrorCode aErr, TBTDevAddr aBdaddr,TBTBasebandRole aRole)=0;
    virtual void HCICompletedPackets(THCIConnHandle aConnH, TUint16 aNumPacketsCompleted)=0; //NumberCompletedPacketsEvent
    virtual void ModeChangeEvent(THCIErrorCode aErr, THCIConnHandle aConnH, TBTHostMode aMode, TUint16 aInterval)=0;
    virtual void ReturnLinkKeysEvent(THCIErrorCode aErr, TBTDevAddr aBdaddr,const TBTLinkKey& aLinkKey)=0;
    virtual void PINCodeRequestEvent(TBTDevAddr aBdaddr)=0;
    virtual void LinkKeyRequestEvent(TBTDevAddr aBdaddr)=0;
    virtual void LinkKeyNotificationEvent(TBTDevAddr aBdaddr,const TBTLinkKey& aLinkKey)=0;
	virtual void LoopbackCommandEvent()=0; //not supported yet
	virtual void DataBufferOverflowEvent(TUint8 aLinkType)=0;
	virtual void MaxSlotsChangeEvent(THCIConnHandle aConnH, TUint8 aMaxSlots)=0;
	virtual void ReadClockOffsetResultEvent(THCIErrorCode aErr, THCIConnHandle aConnH, TBasebandTime aClockOffset)=0;
	virtual void ConnectionPacketTypeChangedEvent(THCIErrorCode aErr,
					THCIConnHandle aConnH, TUint16 aPacketType)=0;
	virtual void QOSViolationEvent(THCIConnHandle aConnH)=0;
	virtual void PageScanModeChangeEvent(TBTDevAddr aBdaddr, TUint8 aPageScanMode)=0;
	virtual void PageScanRepetitionModeChangeEvent(TBTDevAddr aBdaddr, TUint8 aPageScanRepetitionMode)=0;

    // data events
	virtual void ACLDataReceivedEvent(THCIConnHandle aConnH,TUint8 aFlag,const TDesC8& aData)=0;

	// complete events

	virtual void ResetCompleteEvent(THCIErrorCode aStatus)=0;
	virtual void WriteLinkSupervisionTimeoutCompleteEvent(THCIErrorCode aStatus)=0;
	virtual void LinkKeyRequestReplyCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void LinkKeyRequestReplyNegativeCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void PINCodeRequestReplyCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void PINCodeRequestReplyNegativeCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void InquiryCancelCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void PeriodicInquiryModeCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void ExitPeriodicInquiryModeCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void ChangeConnectionPacketTypeCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void SetEventMaskCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void SetEventFilterCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void CreateNewUnitKeyCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void ChangeLocalNameCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void WriteAuthenticationEnableCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void WriteEncryptionModeCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void WritePageTimeoutCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void WriteConnectionAcceptTimeoutCompleteEvent(THCIErrorCode aStatus)=0;
    virtual void WriteClassOfDeviceCompleteEvent(THCIErrorCode aStatus)=0;
	virtual void WriteVoiceSettingCompleteEvent(THCIErrorCode aStatus)=0;
	virtual void WriteCurrentIACLAPCompleteEvent(THCIErrorCode aStatus)=0;
	virtual void SetHostControllerToHostFlowCompleteEvent(THCIErrorCode aStatus)=0;
	virtual void HostBufferSizeCompleteEvent(THCIErrorCode aStatus)=0;
	virtual void HostNumberOfCompletedPacketsCompleteEvent(THCIErrorCode aStatus)=0;
	virtual void WriteScanEnableCompleteEvent(THCIErrorCode aStatus)=0;

	// results of local commands

    virtual void ReadStoredLinkKeyResult(THCIErrorCode aErr,TUint16 aNumKeysRead,TUint16 aMaxNumKeys)=0;
    virtual void WriteStoredLinkKeyResult(THCIErrorCode aErr,TUint8 aNumKeysStored)=0;
    virtual void DeleteStoredLinkKeyResult(THCIErrorCode aErr,TUint8 aNumKeysDeleted)=0;
    virtual void ReadScanEnableResult(THCIErrorCode aErr,TUint8 aEnable)=0;
    virtual void ReadAuthenticationEnableResult(THCIErrorCode aErr,TUint8 aEnable)=0;
    virtual void ReadEncryptionEnableResult(THCIErrorCode aErr,THCIEncryptModeFlag aEnable)=0;
    virtual void ReadBdaddrResult(THCIErrorCode aErr,TBTDevAddr aBdaddr)=0;
    virtual void ReadClassOfDeviceResult(THCIErrorCode aErr,TUint aCoD)=0;
	virtual void ReadVoiceSettingResult(THCIErrorCode aErr,TUint16 aVoiceChannelSetting)=0;
	virtual void ReadLocalNameResult(THCIErrorCode aErr,const TDesC8& aLocalName)=0;
    virtual void ReadTimeoutResult(THCIErrorCode aErr,THCITimeoutType aType,TBasebandTime aTimeout)=0;
	virtual void ReadLocalVersionInfoResult(THCIErrorCode aErr, TBTDevHCIVersion aHCIVersion, TBTDevLMPVersion aLMPVersion)=0;
	virtual void ReadLocalSupportedFeaturesResult(THCIErrorCode aErr, TUint32 aBitMaskList)=0;
	virtual void ReadCountryCodeResult(THCIErrorCode aErr, TUint8 aCountryCode)=0;
	virtual void ReadNumberOfSupportedIACResult(THCIErrorCode aErr, TUint8 aNumIACs)=0;
	virtual void ReadDiscoverabilityResult(THCIErrorCode aErr, TUint8 aNumIACs, TUint aIAC[])=0;
    virtual void ReadBufferSizeResult(THCIErrorCode aErr,TUint16 aAclMaxLen,
			      TUint8 aScoMaxLen,TUint16 aNoACL,TUint16 aNoSCO)=0;
	virtual void ReadRoleDiscoveryResult(THCIErrorCode aStatus, TBTBasebandRole aRole)=0;
	virtual void WriteLinkPolicySettingsResult(THCIErrorCode aStatus, THCIConnHandle aConnH) = 0;
	virtual void VendorSpecificDebugEvent(TPtrC8 aEventFrame)=0;

	// Power off event
	virtual void HandlePowerStatusChange(TPowerState aState)=0;
    };

#endif
