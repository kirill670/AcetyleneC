
// Copyright (c) Symbian Software Ltd 1999-2004.  All rights reserved.

/**
@file bt_sock.h
@publishedAll
@released
*/
//
// BT socket interface types
//

#ifndef BT_SOCK_H
#define BT_SOCK_H

#include <es_sock.h>
#include <bttypes.h>
#include <d32comm.h>	// for RS232 signal names for RFCOMM
#include <hcierrors.h>
#include <btsecmanclient.h>
#include <hcibase.h>
#include <bt_subscribe.h>




_LIT(KRFCOMMDesC,"RFCOMM");	/*!< Descriptor name for RFCOMM */

_LIT(KL2CAPDesC,"L2CAP"); 	/*!< Descriptor name for L2CAP */


//
// BT Protocol Family
//

const TUint KBTAddrFamily = 0x101; 		/*!< BT Address Family */

const TUint KBTLinkManager = 0x0099; 	/*!< Protocol Number for Link Manager */
const TUint KL2CAP = 0x0100;			/*!< Protocol Number for L2CAP */
const TUint KRFCOMM = 0x0003;			/*!< Protocol Number for RFCOMM */
const TUint KSDP = 0x0001;				/*!< Protocol Number for SDP */
const TUint	KAVCTP = 0x0017;			/*!< Protocol Number for AVCTP */
const TInt KTCIL2CAP = 0xF100;			/*!< Protocol Number for TCI L2CAP */

const TInt KBTMajor = 0;				/*!< BT version number for major version */
const TInt KBTMinor = 1;				/*!< BT version number for minor version */
const TInt KBTBuild = 1;				/*!< BT version number for build version */

// Socket Options
const TUint	KSolBtBlog  =0x1000;		/*!< Logging socket option */
const TUint KSolBtHCI   =0x1010;		/*!< HCI socket option */
const TUint KSolBtLM    =0x1011;		/*!< Link Manager socket option */
const TUint KSolBtL2CAP =0x1012;		/*!< L2CAP socket option */
const TUint KSolBtRFCOMM=0x1013;		/*!< RFCOMM socket option */
const TUint KSolBtAVCTP	=0x1014;		/*!< AVCTP socket option */
const TUint KSolBtACL	=0x1015;		/*!< ACL socket option */
const TUint KSolBtLMProxy = 0x2011;		/*!< Link Manager Proxy socket option */
const TUint KSolBtSCO 	  = 0x2012;		/*!< SCO Link scoket option */

/**
Internal socket option for access to the security store register
@internalTechnology
*/
const TUint KBTSecStoreRegisterService = 0x0001;

/**
Internal socket option for access to the security store
@internalTechnology
*/
static const TUint KSockBluetoothTypeSecStore = 0x4000;

const static TUint8 KSCOListenQueSize = 1; /*!< Length of SCO listening queue */

/** 
Defines the physical (max) size of our packets 
@deprecated 
*/
const static TUint16 KL2MaxReceiveMTU  = 672; 	

/** 
Defines the physical (max) size of our packets 
@deprecated
*/
const static TUint16 KL2MaxTransmitMTU = 672;

const static TUint16 KL2MinMTU = 48; 			/*!< BT Spec defined min. supported MTU size */
const static TInt    KL2HeaderLength = 4;     	/*!< Length of L2CAP message header */
const static TUint16 KL2MaxPacketSize = (KL2MaxReceiveMTU>KL2MaxTransmitMTU?KL2MaxReceiveMTU:KL2MaxTransmitMTU) + KL2HeaderLength; /*!< Max L2CAP packet size */

// All PSM values must be ODD, that is, the least significant bit of the least significant
// octet must be ’1’. Also, all PSM values must be assigned such that the
// least significant bit of the most significant octet equals ’0’.
const static TUint16 KMaxPSM = 0xFEFF;	/*!< Max L2CAP PSM value */

/**
 * This is the minimum user PSM. Smaller PSM values are possible but are reserved for use by the 
 * Bluetooth stack only.
 */
const static TUint16 KMinUserPSM = 0x1001;

/**
 * This constant has been deprecated since its name is misleading becasue it doesn't represent the 
 * absolute minimum PSM but the minimum user PSM instead. 
 * Use KMinUserPSM instead of this constant.
 * @deprecated
 */
const static TUint16 KMinPSM = 0x1001;

class TBTAccessRequirements
/** The access requirements set up by a bluetooth service.

An incoming connection must satisfy these criteria before the connection may proceed.
Not spectacularly useful for applications; mainly used by other Bluetooth libraries
@publishedAll
@released
*/
	{
public:
	IMPORT_C TBTAccessRequirements();
	IMPORT_C void SetAuthentication(TBool aPreference);
	IMPORT_C void SetAuthorisation(TBool aPreference);
	IMPORT_C void SetEncryption(TBool aPreference);
	IMPORT_C void SetDenied(TBool aPreference);
	IMPORT_C TBool AuthenticationRequired() const;
	IMPORT_C TBool AuthorisationRequired() const;
	IMPORT_C TBool EncryptionRequired() const;
	IMPORT_C TBool Denied() const;
	IMPORT_C TBool operator==(const TBTAccessRequirements& aRequirements) const;
private:
	TUint8 iRequirements;
private:
	enum TBTServiceSecuritySettings
		{
		EAuthenticate = 0x01,
		EAuthorise = 0x02,
		EEncrypt = 0x04,
		EDenied = 0x08
		};
	};

class TBTServiceSecurity
/** The security settings of a bluetooth service.

Contains information regarding the service UID and the access requirements.
@publishedAll
@released
*/
	{
public:
	IMPORT_C TBTServiceSecurity(const TBTServiceSecurity& aService);
	IMPORT_C TBTServiceSecurity();
	IMPORT_C void SetUid(TUid aUid);
	IMPORT_C void SetAuthentication(TBool aPreference);
	IMPORT_C void SetAuthorisation(TBool aPreference);
	IMPORT_C void SetEncryption(TBool aPreference);
	IMPORT_C void SetDenied(TBool aPreference);
	IMPORT_C TBool AuthorisationRequired() const;
	IMPORT_C TBool EncryptionRequired() const;
	IMPORT_C TBool AuthenticationRequired() const;
	IMPORT_C TBool Denied() const;
	IMPORT_C TUid Uid() const;
private:
	TUid iUid;	///<The UID of the service.  Will be used by the UI to work out the name of the service when prompting the user.
	TBTAccessRequirements iSecurityRequirements;	///<Whether the service requires authentication, authorisation, or encryption.
	};

typedef TPckgBuf<TBTServiceSecurity> TBTServiceSecurityPckg;	/*!< Package definition for securty settings */

class TBTSockAddr : public TSockAddr
/** Bluetooth socket address

Stores bluetooth device address, and security - these are common to all Bluetooth addresses
@publishedAll
@released
*/
	{
struct SBTAddrSecurity
	{		
	TBTDevAddr iAddress;
	TBTServiceSecurity iSecurity;
	};
public:
	IMPORT_C TBTSockAddr();
	IMPORT_C TBTSockAddr(const TSockAddr& aAddr);
	IMPORT_C TBTDevAddr BTAddr() const;
	IMPORT_C void SetBTAddr(const TBTDevAddr& aRemote);
	IMPORT_C void SetSecurity(const TBTServiceSecurity& aSecurity);
	inline TBTServiceSecurity BTSecurity() const;
	inline static TBTSockAddr& Cast(const TSockAddr& aAddr);
protected:
	inline TAny* EndBTSockAddrPtr() const;
private:
	inline SBTAddrSecurity& BTAddrSecStruct() const;
	inline TPtr8 AddressPtr() const;
	};


const static TInt KErrBtEskError = -6999;	/*!< BT ESK error code */


// Options available for all Bluetooth protocols

/** BT options. */
enum TBTOptions
	{
	/** Override device security */
	KBTSecurityDeviceOverride = 0x999,
	};

typedef TPckgBuf<TBTServiceSecurityPerDevice> TBTServiceSecurityPerDeviceBuf;	/*!< Package definition for securty settings */


// Link manager error codes.
const static TInt KLinkManagerErrBase = -6450;								/*!< Link manager base error value */
const static TInt KErrInsufficientBasebandResources = KLinkManagerErrBase;	/*!< Insufficient baseband resources error value */
const static TInt KErrProxyWriteNotAvailable = KLinkManagerErrBase-1;		/*!< Proxy write not available error value */
const static TInt KErrReflexiveBluetoothLink = KLinkManagerErrBase-2;		/*!< Reflexive BT link error value */

//
// L2CAP
//

const static TInt KL2CAPErrBase = -6300;								/*!< Base error value for L2CAP error codes */
const static TInt KErrBadAddress = KL2CAPErrBase;						/*!< L2CAP Bad address error code */
const static TInt KErrSAPUnexpectedEvent = KL2CAPErrBase - 1;			/*!< L2CAP unexpected SAP event error code */
const static TInt KErrBadPacketReceived = KL2CAPErrBase - 2;			/*!< L2CAP bad packet received error code */
const static TInt KErrL2CAPBadResponse = KL2CAPErrBase - 3;				/*!< L2CAP bad response error code */
const static TInt KErrHCIConnectFailed = KL2CAPErrBase - 4;				/*!< L2CAP HCI connection failed error code */
const static TInt KErrHCILinkDisconnection = KL2CAPErrBase - 5;			/*!< L2CAP HCI link disconnection error code */
const static TInt KErrSAPNotConnected = KL2CAPErrBase - 6;				/*!< L2CAP SAP not connected error code */
const static TInt KErrConfigBadParams = KL2CAPErrBase - 7;				/*!< L2CAP bad configuration parameters error code */
const static TInt KErrConfigRejected = KL2CAPErrBase - 8;				/*!< L2CAP configuration rejected error code */
const static TInt KErrConfigUnknownOptions = KL2CAPErrBase - 9;			/*!< L2CAP unknown configuration options error code */
const static TInt KErrL2PeerDisconnected = KL2CAPErrBase - 10;			/*!< L2CAP peer disconnected error code */
const static TInt KErrL2CAPAccessRequestDenied = KL2CAPErrBase - 11;	/*!< L2CAP access request denied error code */
const static TInt KErrL2CAPRequestTimeout = KL2CAPErrBase - 12;			/*!< L2CAP request timeout error code */
const static TInt KErrL2PeerRejectedCommand = KL2CAPErrBase - 13;		/*!< L2CAP peer rejected command error code */
const static TInt KErrHostResNameTooLong = KL2CAPErrBase - 14;			/*!< L2CAP host resolver name too long error code */
const static TInt KErrL2CAPNoMorePSMs = KL2CAPErrBase - 15;				/*!< L2CAP no more PSMs error code */
const static TInt KErrL2CAPMaxTransmitExceeded = KL2CAPErrBase - 16;	/*!< L2CAP in reliable mode: the maximum L2Cap retransmissions have been made and channel will disconnect error code*/
const static TInt KErrL2CAPDataControllerDetached = KL2CAPErrBase - 17;	/*!< L2CAP problems (e.g. no memory) whilst sending data error code*/
const static TInt KErrL2CAPConfigPending = KL2CAPErrBase - 18;			/*!< L2CAP configuration is in progress error code 
																			 @internalComponent*/
const static TInt KErrL2CAPConfigAlreadyInProgress = KL2CAPErrBase - 19;/*!< L2CAP attempt to alter config whilst configuration is in progress error code*/
const static TInt KErrL2CAPNoFreeCID = KL2CAPErrBase - 21;				/*!< L2CAP no more channel IDs available error code*/

const static TInt KErrHostResNoMoreResults = KErrEof;  					/*!< Host resolver has no more results error code */

/** L2CAP host resolver has no more results error code
@deprecated
*/
const static TInt KErrL2HostResNoMoreResults = KErrEof;


/** Inquiry number of responses option.
@deprecated
*/
const static TUint KInquiryNumResponsesOpt=1;
/** Inquiry time option.
@deprecated
*/
const static TUint KInquiryTimeOpt=2;

const static TUint KHostResInquiry = 1;			/*!< Host resolver inquiry option */ 
const static TUint KHostResName = 2;			/*!< Host resolver name option */ 
const static TUint KHostResIgnoreCache = 16; 	/*!< A way of ignoring the cache */ 
const static TUint KHostResCache = 32; 			/*!< A way to get CoD from cache */

// L2CAP Ioctls
const static TInt KL2CAPEchoRequestIoctl	= 0;		/*!< Echo Request Ioctl name */
const static TInt KL2CAPIncomingMTUIoctl	= 1;		/*!< Change incoming MTU Ioctl name */
const static TInt KL2CAPOutgoingMTUIoctl    = 2;		/*!< Change outgoing MTU Ioctl name */
const static TInt KL2CAPUpdateChannelConfigIoctl	= 3;/*!< Change conguration parameters Ioctl name */


// Link Manager Ioctls

/** Link manager Ioctl codes.*/
enum TBTLMIoctls
	{
	/** Disconnect ACL Ioctl code
	@deprecated
	*/
	KLMDisconnectACLIoctl,
	/** Set Packet type Ioctl code
	@deprecated
	*/
	KLMSetPacketTypeIoctl,
	/** Wait for SCO notification Ioctl code
	@internalComponent
	*/
	KLMWaitForSCONotificationIoctl,
	/** One-shot baseband notification Ioctl code
	@internalComponent
	*/	
	KLMBasebandEventOneShotNotificationIoctl,
	/** Baseband event notification Ioctl code
	@internalComponent
	*/	
	KLMBasebandEventNotificationIoctl,
	};


/** Paging policy for baseband.*/
enum TBasebandPageTimePolicy
    {
	EPagingDontCare,	/*!< Don't care setting */
    EPagingNormal,		/*!< Normal setting */
    EPagingBestEffort,	/*!< Best effort setting */
    EPagingQuick,		/*!< Quick paging setting */
    };

struct TBasebandPolicyParams
/** Baseband policy parameters.*/
	{
	TBasebandPageTimePolicy		iPageTimePolicy;	/*!< Page time policy */
	};

struct TSetBasebandPolicy
/** Set baseband policy.

@deprecated
@see RBTBaseband, TPhysicalLinkQuickConnectionToken
*/
	{
	TBTDevAddr				iDevAddr;	/*!< Device Address */
	TBasebandPolicyParams	iPolicy;	/*!< Policy parameters */
	};

/** Package for SetBasebandPolicy structure
@deprecated
*/
typedef TPckgBuf<TSetBasebandPolicy> TSetBasebandPolicyBuf;	

struct TPhysicalLinkQuickConnectionToken
/** Specifies details for faster connection.*/
	{
	TBTNamelessDevice		iDevice;	/*!< Nameless device */
	TBasebandPolicyParams	iPolicy;	/*!< New policy */
	};
	
typedef TPckgBuf<TPhysicalLinkQuickConnectionToken> TPhysicalLinkQuickConnectionTokenBuf;	/*!< Package for TPhysicalLinkQuickConnectionToken structure */

#define KBasebandSlotTime 0.000625	/*!< Baseband timeslot duration (0.000625 seconds) */
static const TUint KDefaultBasebandConnectionTimeout = 10;  /*!< Default baseband connection timeout (10 seconds) */


struct TLMDisconnectACLIoctl
/**
Structure to specify the remote ACL connection to disconnect.
The reason passed in iReason will be sent to the remote device.

Use with KLMDisconnectACLIoctl.
@deprecated
*/
	{
	TBTDevAddr	iDevAddr;	/*!< Device address */
	TUint8		iReason;	/*!< Reason code */
	};

typedef TPckgBuf<TLMDisconnectACLIoctl> TLMDisconnectACLBuf;	/*!< Package for TLMDisconnectACLIoctl structure */

// private tokens for use by RBTBaseband facade and stack
_LIT8(KDisconnectOnePhysicalLink, "1");		/*!< Specifes one physical link should be disconnected */
_LIT8(KDisconnectAllPhysicalLinks, "A");	/*!< Specifes all physical links should be disconnected */


/** Link manager options.
@internalComponent
*/
enum TBTLMOptions
	{
	ELMOutboundACLSize,						/*!< Outbound ACL size option */
	ELMInboundACLSize,						/*!< Inbound ACL size option */
	KLMGetACLHandle,						/*!< Get ACL Handle option */
	KLMGetACLLinkCount,						/*!< Get ACL link count option */
	KLMGetACLLinkArray,						/*!< Get ACL link array option */
	KLMSetBasebandConnectionPolicy,			/*!< Set baseband connection policy option */
	KLMGetBasebandHandle,					/*!< Get baseband handle option */
	EBBSubscribePhysicalLink,				/*!< Subscribe physical link option */
	EBBBeginRaw,							/*!< Enable raw broadcast option */
	EBBRequestRoleMaster,					/*!< Request switch to master option */
	EBBRequestRoleSlave,					/*!< Request switch to slave option */
	EBBCancelModeRequest,					/*!< Cancel mode request option */
	EBBRequestSniff,						/*!< Request sniff mode option */
	EBBRequestPark,							/*!< Request park mode option */
	EBBRequestPreventRoleChange,			/*!< Request to prevent a role (master / slave) switch option */
	EBBRequestAllowRoleChange,				/*!< Request to allow a role (master / slave) switchoption */
	EBBRequestChangeSupportedPacketTypes,	/*!< Request to cange the current supported packet types option */
	EBBEnumeratePhysicalLinks,				/*!< Enumerate physical links option */
	EBBGetPhysicalLinkState,				/*!< Get the physical link state option */
	//Allow combination of options below...
	EBBRequestPreventSniff = 0x100,			/*!< Request to prevent entering sniff mode option */
	EBBRequestPreventHold = 0x200,			/*!< Request to prevent entering hold mode option */
	EBBRequestPreventPark = 0x400,			/*!< Request to prevent entering park mode option */
	EBBRequestPreventAllLowPowerModes = 
		(EBBRequestPreventSniff | 
		 EBBRequestPreventHold | 
		 EBBRequestPreventPark),			/*!< Request to prevent entering all modes option */
	EBBRequestAllowSniff = 0x800,			/*!< Request to allow entering sniff mode option */
	EBBRequestAllowHold = 0x1000,			/*!< Request to allow entering hold mode option */
	EBBRequestAllowPark = 0x2000,			/*!< Request to allow entering park mode option */
	EBBRequestAllowAllLowPowerModes = 
		(EBBRequestAllowSniff | 
		 EBBRequestAllowHold | 
		 EBBRequestAllowPark),				/*!< Request to allow entering-all-modes option. */

	};

/** SCO SAP options.
@internalComponent
*/
enum TBTSCOOptions
	{
	ESCOSetUserHVPacketTypes					/*!< Set user required HV packet types >*/
	};

// HCI stuff (used via L2CAP - that's why it's here)

// HCI Ioctls
/** Add SCO connnection Ioctl
@deprecated
*/
static const TUint KLMAddSCOConnIoctl			=0;
/** Remove SCO connection Ioctl
@deprecated
*/
static const TUint KHCIRemoveSCOConnIoctl		=1;
/** Change packet types allowed Ioctl
@deprecated
*/
static const TUint KHCIChangePacketTypeIoctl	=2;
/** Request authorisation Ioctl 
@deprecated
*/
static const TUint KHCIAuthRequestIoctl			=3;
/** Request encryption Ioctl
@deprecated
*/
static const TUint KHCIEncryptIoctl				=4;
/** Change link key Ioctl
@deprecated
*/
static const TUint KHCIChangeLinkKeyIoctl		=5;
/** Master link key Ioctl
@deprecated
*/
static const TUint KHCIMasterLinkKeyIoctl		=6;
/** Enable hold mode Ioctl
@deprecated
*/
static const TUint KHCIHoldModeIoctl			=7;
/** Enable sniff mode Ioctl
@deprecated
*/
static const TUint KHCISniffModeIoctl			=8;
/** Exit sniff mode Ioctl
@deprecated
*/
static const TUint KHCIExitSniffModeIoctl		=9;
/** Enable park mode Ioctl
@deprecated
*/
static const TUint KHCIParkModeIoctl			=10;
/** Exit park mode Ioctl
@deprecated
*/
static const TUint KHCIExitParkModeIoctl		=11;

/** Read page timeout Ioctl
@deprecated
*/
static const TUint KHCIReadPageTimeoutIoctl		=12;
/** Write page timeout Ioctl
@deprecated
*/
static const TUint KHCIWritePageTimeoutIoctl	=13;
/** Read scan enable Ioctl
@deprecated
@see bt_subscribe.h
*/
static const TUint KHCIReadScanEnableIoctl		=14;
/** Write scan enable Ioctl
@deprecated
@see bt_subscribe.h
*/
static const TUint KHCIWriteScanEnableIoctl		=15;
/** Read device class Ioctl
@deprecated
@see bt_subscribe.h
*/
static const TUint KHCIReadDeviceClassIoctl		=16;
/** Write device class Ioctl
@deprecated
@see bt_subscribe.h
*/
static const TUint KHCIWriteDeviceClassIoctl	=17;
/** Read voice settings Ioctl
@deprecated
*/
static const TUint KHCIReadVoiceSettingIoctl	=18;
/** Write voice settings Ioctl
@deprecated
*/
static const TUint KHCIWriteVoiceSettingIoctl	=19;
/** Read hold mode activity Ioctl
@deprecated
*/
static const TUint KHCIReadHoldModeActivityIoctl=20;
/** Write hold mode activity Ioctl
@deprecated
*/
static const TUint KHCIWriteHoldModeActivityIoctl=21;
/** Local version Ioctl
@deprecated
*/
static const TUint KHCILocalVersionIoctl		=22;
/** Local features Ioctl
@deprecated
*/
static const TUint KHCILocalFeaturesIoctl		=23;
/** Country code Ioctl
@deprecated
*/
static const TUint KHCICountryCodeIoctl			=24;
/** Local address Ioctl
@deprecated
@see bt_subscribe.h
*/
static const TUint KHCILocalAddressIoctl		=25;
/** Write discoverability Ioctl
@deprecated
@see bt_subscribe.h
*/
static const TUint KHCIWriteDiscoverabilityIoctl=26;
/** Read discoverability Ioctl
@deprecated
@see bt_subscribe.h
*/
static const TUint KHCIReadDiscoverabilityIoctl	=27;
/** Read authentification enabled Ioctl
@deprecated
*/
static const TUint KHCIReadAuthenticationEnableIoctl=33;
/** Write authentification enabled Ioctl
@deprecated
*/
static const TUint KHCIWriteAuthenticationEnableIoctl=34;


// Structs for ioctl parameters

/**
Enumerations for the four possible scan enable modes.
Use Inquiry scan for discoverability and Page scan for
connectability.

Use with KHCIReadScanEnableIoctl and KHCIWriteScanEnableIoctl.
@deprecated
@see bt_subscribe.h
*/
enum THCIScanEnableIoctl 
    {
     EHCINoScansEnabled=0x00,          /*!< No scans enabled. */
     EHCIInquiryScanOnly,              /*!< Inquiry scan only. */
     EHCIPageScanOnly,                 /*!< Page scan only. */
     EHCIInquiryAndPageScan            /*!< Both inquiry and page scan enabled. */
    };

typedef TPckgBuf<THCIScanEnableIoctl> THCIScanEnableBuf;	/*!< Package for THCIScanEnableIoctl structure */

struct TLMAddSCOConnectionIoctl
/**
Structure for specifying SCO type to add to a connected socket.
The connection handle for the SCO link is returned in iConnH when
the Ioctl completes.

Use with KHCIAddSCOConnIoctl.
@deprecated
*/
	{
	TUint16        iPktType;	/*!< Packet type */
	};

typedef TPckgBuf<TLMAddSCOConnectionIoctl> TLMAddSCOConnectionBuf;	/*!< Package for TLMAddSCOConnectionIoctl structure */

struct THCISetEncryptionIoctl
/**
Request to change the encryption state of a connection.
iEncrypt specifies whether to turn encryption on or off.

Use with KHCIEncryptIoctl.
@deprecated
*/
	{
	TBool             iEncrypt;		/*!< Encryption enabled / disabled */
	};
typedef TPckgBuf<THCISetEncryptionIoctl> THCISetEncryptionBuf;	/*!< Package for THCISetEncryptionIoctl structure */

struct THCIDeviceClassIoctl
/**
Structure to specify the class of device when getting or setting
the local device class.

Use with KHCIReadDeviceClassIoctl and KHCIWriteDeviceClassIoctl.
@deprecated
@see bt_subscribe.h
*/
	{
	TUint16    iMajorServiceClass;		/*!< Major Service class */
	TUint8     iMajorDeviceClass;		/*!< Major Device class */
	TUint8     iMinorDeviceClass;		/*!< Minor Device class */
	};
typedef TPckgBuf<THCIDeviceClassIoctl> THCIDeviceClassBuf;	/*!< Package for THCIDeviceClassIoctl structure */
	
struct THCILocalVersionIoctl
/**
Structure describing the local Bluetooth hardware version.

Use with KHCILocalVersionIoctl.
@deprecated
*/
	{
	TUint8   iHCIVersion;			/*!< HCI version */
	TUint16  iHCIRevision;			/*!< HCI Revision */
	TUint8   iLMPVersion;			/*!< LMP version */
	TUint16  iLMPSubversion;		/*!< LMP subversion */
	TUint16  iManufacturerName;		/*!< Manufacturer name */
	};
typedef TPckgBuf<THCILocalVersionIoctl> THCILocalVersionBuf;	/*!< Package for THCILocalVersionIoctl structure */

/** L2CAP Get / Set Options. */
enum TBTL2CAPOptions
	{
	KL2CAPGetOutboundMTU,			/*!< Get / Set the current outbound MTU size */ 
	KL2CAPGetDebug1,				/*!< Debug Command */
	KL2CAPInboundMTU,				/*!< Get / Set the current inbound MTU size */
	KL2CAPRTXTimer,					/*!< Change the extended L2CAP command retransmission timeout */
	KL2CAPERTXTimer,				/*!< Change the L2CAP command retransmission timeout */
	KL2CAPGetMaxOutboundMTU,		/*!< Get the max outbound MTU supported by the stack */
	KL2CAPGetMaxInboundMTU,			/*!< Get the max inbound MTU supported by the stack */
	KL2CAPUpdateChannelConfig,		/*!< Get and Set the current configuration parameters */
#ifdef _DEBUG
	KL2CAPTestConfigure,	
	KL2CAPDebugFlush,
	KL2CAPVersion1_2,
	KL2CAPHeapAlloc,
	KL2CAPDataPlaneConfig,
#endif
	};

typedef TUint16 TL2CAPPort;			/*!< Definition of a L2CAP port number type */

const static TL2CAPPort KL2CAPPassiveAutoBind = KMaxTUint16;  /*!< PSM out of the valid range used for passive auto bind operation */

class TL2CAPSockAddr : public TBTSockAddr
/** L2CAP Socket Address.

Use this class to specify a local or remote L2CAP connection end-point,
that is Device Address and PSM/CID.
When unconnected, the Port() specifies the PSM, once connected it refers to
the CID.
@see TBTSockAddr
@publishedAll
@released
*/
	{
public:
	IMPORT_C TL2CAPSockAddr();
	IMPORT_C TL2CAPSockAddr(const TSockAddr &aDevAddr);
	inline static TL2CAPSockAddr& Cast(const TSockAddr &aDevAddr);

	inline TL2CAPPort Port() const;
	inline void SetPort(const TL2CAPPort aHomePort);
	};

class TInquirySockAddr : public TSockAddr
/** Socket address class used for inquiries.

Used to specify the inquiry request, and then filled with information
about remote devices discovered through the inquiry process.

Use the BTAddr() method to extract the device address to connect to.
@publishedAll
@released
*/
	{
struct SInquiryAddr
	{
	TBTDevAddr iAddress;
	TUint8 iFormatTypeField;
	TUint16 iMajorServiceClass;
	TUint8 iMajorDeviceClass;
	TUint8 iMinorDeviceClass;
	TUint  iIAC;
	TUint8 iFlags;
    };
public:
	IMPORT_C TInquirySockAddr();
	IMPORT_C TInquirySockAddr(const TSockAddr &aDevAddr);
	IMPORT_C TBTDevAddr BTAddr() const;
	IMPORT_C void SetBTAddr(const TBTDevAddr& aRemote);

	inline static TInquirySockAddr& Cast(const TSockAddr &aDevAddr);
	inline TUint16 MajorServiceClass() const;
	inline void SetMajorServiceClass(TUint16 aClass);
	inline TUint8 MajorClassOfDevice() const;
	inline void SetMajorClassOfDevice(TUint8 aMajorClassOfDevice);
	inline TUint8 MinorClassOfDevice() const;
	inline void SetMinorClassOfDevice(TUint8 aMinorClassOfDevice);
	inline TUint IAC() const;
	inline void SetIAC(const TUint aIAC);
	inline TUint8 Action() const;
	inline void SetAction(TUint8 aFlags);
private:
	inline SInquiryAddr& InquiryAddrStruct() const;
	inline TPtr8 AddressPtr() const;
	};


enum TACLPort
/** ACL port types.
@internalComponent
*/
	{
	EACLPortRaw		= 0x00,		/*!< Raw port type */
	EACLPortL2CAP	= 0x01,		/*!< L2CAP port type */
	EACLPortUnset	= 0xFF,		/*!< Unspecified ACL port type */
	};


// SAP types for baseband
/** ACL socket type
@internalTechnology
*/
static const TUint KSockBluetoothTypeACL = KMaxTUint;
/** SCO socket type
@internalTechnology
*/
static const TUint KSockBluetoothTypeSCO = KMaxTUint-1;
/** Raw broadcast socket type
@internalTechnology
*/
static const TUint KSockBluetoothTypeRawBroadcast = KMaxTUint-2;

class TACLSockAddr : public TBTSockAddr
/** ACL Socket Address.

Use this class to specify a local or remote baseband connection end-point,
This is tied to the flags field in ACL data packets
@internalComponent
*/
	{
public:
	IMPORT_C TACLSockAddr();
	IMPORT_C TACLSockAddr(const TSockAddr &aDevAddr);
	inline static TACLSockAddr& Cast(const TSockAddr &aDevAddr);
	//
	inline TACLPort Port() const;
	inline void SetPort(TACLPort aPort);
	};


//
// RFCOMM
//

const static TInt KRFErrorBase = -6350;										/*!< RFCOMM base error code. */
const static TInt KErrRfcommSAPUnexpectedEvent = KRFErrorBase;				/*!< RFCOMM unexpected event error code. */
const static TInt KErrRfcommAlreadyBound = KRFErrorBase-1;					/*!< RFCOMM SAP already bound error code. */
const static TInt KErrRfcommBadAddress = KRFErrorBase-2;					/*!< RFCOMM bad address error code. */
const static TInt KErrRfcommMTUSize = KRFErrorBase-3;						/*!< RFCOMM MTU size exceeded error code. */
const static TInt KErrRfcommFrameResponseTimeout = KRFErrorBase-4;			/*!< RFCOMM frame response timeout error code. */
const static TInt KErrRfcommMuxRemoteDisconnect = KRFErrorBase-5;			/*!< RFCOMM remote end disconnected error code. */
const static TInt KErrRfcommNotBound = KRFErrorBase-6;						/*!< RFCOMM SAP not bound error code. */
const static TInt KErrRfcommParameterNegotiationFailure = KRFErrorBase-7;	/*!< RFCOMM parameter negotiation failure error code. */
const static TInt KErrRfcommNotListening = KRFErrorBase-8;					/*!< RFCOMM not listening error code. */
const static TInt KErrRfcommNoMoreServerChannels = KRFErrorBase-9;			/*!< RFCOMM no more server channels available error code. */

//RFCOMMIoctls

const static TInt KRFCOMMModemStatusCmdIoctl =0;		/*!< RFCOMM status command Ioctl */
const static TInt KRFCOMMRemoteLineStatusCmdIoctl = 1;	/*!< RFCOMM remote line status command Ioctl */
const static TInt KRFCOMMRemotePortNegCmdIoctl = 2;		/*!< RFCOMM remote port negotiation command Ioctl */
const static TInt KRFCOMMRemotePortNegRequestIoctl = 3;	/*!< RFCOMM remote port negotiation request Ioctl */

// RFCOMM Options

const static TInt KRFCOMMLocalPortParameter = 0;	/*!< RFCOMM local port parameter option (Get + Set) */
/** RFCOMM Get Available server channel option (Get only)
@deprecated
*/
const static TInt KRFCOMMGetAvailableServerChannel = 1;

const static TInt KRFCOMMMaximumSupportedMTU = 2; 	/*!< RFCOMM maximum supported option (Get + Set) */
const static TInt KRFCOMMGetDebug1 = 3;   			/*!< RFCOMM debug option (Get only) */
const static TInt KRFCOMMGetRemoteModemStatus = 4; 	/*!< RFCOMM remote modem status option (Get + Set) */

const static TInt KRFCOMMGetTransmitCredit = 5;		/*!< RFCOMM get transmit credits option */
const static TInt KRFCOMMGetReceiveCredit = 6;		/*!< RFCOMM get receive credits option */
const static TInt KRFCOMMGetReUsedCount = 7;		/*!< RFCOMM get number of remote used credits option */
const static TInt KRFCOMMFlowTypeCBFC = 8; 			/*!< RFCOMM Credit based flow control option (Get + Set) */
const static TInt KRFCOMMErrOnMSC = 9;				/*!< RFCOMM set the value of MSC signals that will cause a disconnect error to be generated */
const static TUint KRFCOMMLocalModemStatus = 10;   	/*!< RFCOMM local modem status option (Get + Set) */

// Masks for interpreting signalling commands
const static TUint8 KModemSignalFC  = 0x01;			/*!< RFCOMM FC signalling command mask */
const static TUint8 KModemSignalRTC = 0x02;			/*!< RFCOMM RTC signalling command mask */
const static TUint8 KModemSignalRTR = 0x04;			/*!< RFCOMM RTR signalling command mask */
const static TUint8 KModemSignalIC  = 0x20;			/*!< RFCOMM IC signalling command mask */
const static TUint8 KModemSignalDV  = 0x40;			/*!< RFCOMM DV signalling command mask */

enum TRPNParameterMask
/** Remote port negotiation parameter masks
*/
	{
	EPMBitRate		= 0x0001,		/*!< Remote port negotiation parameter masks for bit rate */
	EPMDataBits		= 0x0002,		/*!< Remote port negotiation parameter masks for data bits */
	EPMStopBit		= 0x0004,		/*!< Remote port negotiation parameter masks for stop bit */
	EPMParity		= 0x0008,		/*!< Remote port negotiation parameter masks for parity */
	EPMParityType	= 0x0010,		/*!< Remote port negotiation parameter masks for parity type */
	EPMXOnChar		= 0x0020,		/*!< Remote port negotiation parameter masks for on character */
	EPMXOffChar		= 0x0040,		/*!< Remote port negotiation parameter masks for off character */
	// RESERVED		= 0x0080		
	EPMXOnOffInput	= 0x0100,		/*!< Remote port negotiation parameter masks for XOn/Off input */
	EPMXOnOffOutput	= 0x0200,		/*!< Remote port negotiation parameter masks for XOn/Off output */
	EPMRTRInput		= 0x0400,		/*!< Remote port negotiation parameter masks for read to receive input */
	EPMRTROutput	= 0x0800,		/*!< Remote port negotiation parameter masks for read to receive output */
	EPMRTCInput		= 0x1000,		/*!< Remote port negotiation parameter masks for RTC input */
	EPMRTCOutput	= 0x2000		/*!< Remote port negotiation parameter masks for RTC output */
	// RESERVED		= 0x4000
	// RESERVED		= 0x8000
	};

enum TRPNFlowCtrlMask
/** Remote port negotiation flow control masks
*/
	{
	EFCXOnOffInput	=0x01,	/*!< Remote port negotiation flow control masks for XOn/Off input */
	EFCXOnOffOutput =0x02,	/*!< Remote port negotiation flow control masks for XOn/Off output */
	EFCRTRInput		=0x04,	/*!< Remote port negotiation flow control masks for ready to receive input */
	EFCRTROutput	=0x08,	/*!< Remote port negotiation flow control masks for ready to receive output */
	EFCRTCInput		=0x10,	/*!< Remote port negotiation flow control masks for RTC input */
	EFCRTCOutput	=0x20	/*!< Remote port negotiation flow control masks for RTC output */
	};

enum TRPNValidityMask
/** Remote port negotiation validity masks
*/
	{
	EVMBitRate	= 0x01,	/*!< Remote port negotiation validity masks for bit rate */
	EVMDataBits	= 0x02,	/*!< Remote port negotiation validity masks for data bits */
	EVMStopBit	= 0x04,	/*!< Remote port negotiation validity masks for stop bit */
	EVMParity	= 0x08,	/*!< Remote port negotiation validity masks for parity */
	EVMFlowCtrl	= 0x10,	/*!< Remote port negotiation validity masks for flow control */
	EVMXOnChar	= 0x20,	/*!< Remote port negotiation validity masks for XOn charater */
	EVMXOffChar	= 0x40	/*!< Remote port negotiation validity masks for XOff charater */
	};

// structs for RFCOMM Ioctls

class TRfcommRPNTransaction;

class TRfcommRemotePortParams
/** RF COMM remote port parameters. 

@publishedAll
@released
*/
	{
public:
	inline TRfcommRemotePortParams();
	inline TUint8	IsValid() const;
	inline TBool	GetBitRate(TBps& aBitRate) const;
	inline TInt		SetBitRate(TBps  aBitRate);
	inline TBool	GetDataBits(TDataBits& aDataBits) const;
	inline TInt     SetDataBits(TDataBits  aDataBits);
	inline TBool	GetStopBit(TStopBits& aStopBit) const;
	inline TInt		SetStopBit(TStopBits  aStopBit);
	inline TBool	GetParity(TParity& aParity) const;
	inline TInt		SetParity(TParity  aParity);
	inline TBool    GetFlowCtrl(TUint8& aFlowCtrl) const;
	inline TInt     SetFlowCtrl(TUint8  aFlowCtrl);
	inline TBool    GetXOnChar(TUint8& aXOnChar) const;
	inline TInt     SetXOnChar(TUint8  aXOnChar);
	inline TBool    GetXOffChar(TUint8& aXOffChar) const;
	inline TInt     SetXOffChar(TUint8  aXOffChar);
	IMPORT_C void	UpdateFlowCtrlBit(TUint8 aFlowCtrl, TRPNFlowCtrlMask aFCMask);
	IMPORT_C void	UpdateWholeFlowCtrl(TUint16 aParamMask, TUint8 aFlowCtrl);
	IMPORT_C void	UpdateFromRPNTransaction(const TRfcommRPNTransaction& 
											aRPNTransaction);	
private:	
	TBps iBitRate;
	TDataBits iDataBits;
	TStopBits iStopBit; //It's really only one bit - ignore what the type implies...
	TParity iParity;
	TUint8 iFlowCtrl;
	TUint8 iXOnChar;
	TUint8 iXOffChar;
	TUint8 iValidMask;
	};

// structs for RFCOMM Ioctls

class TRfcommRPNTransaction
/** RF COMM IO control structs.

@publishedAll
@released
*/
	{
public: // Functions
	inline TRfcommRPNTransaction();
public: // Variables
	TRfcommRemotePortParams iPortParams;	/*!< Remote port parameters */
	TUint16 iParamMask;						/*!< Parameter mask */
	};

// RFCOMM addresses

typedef TUint8 TRfcommChannel;	/*!< RFCOMM channel type definition */

const static TRfcommChannel KMinRfcommServerChannel = 1;	/*!< Minimum RFCOMM server channel value */
const static TRfcommChannel KMaxRfcommServerChannel = 30;	/*!< Maximum RFCOMM server channel value */

const static TRfcommChannel KRfcommPassiveAutoBind = KMaxTUint8;	/*!< Channel value out of the valid range used for passive auto bind. */

class TRfcommSockAddr : public TBTSockAddr
/** Defines the format of an Rfcomm address.

This class uses the TSockAddr data area to hold the address so that
it can be passed through the ESOCK boundary.
Assumes that the remote RFCOMM instance is always bound to PSM 3 on
L2CAP, so there is no way of specifying another remote PSM.

@see TBTSockAddr
@publishedAll   
@released
*/
	{
public:
	IMPORT_C TRfcommSockAddr();
	IMPORT_C TRfcommSockAddr(const TSockAddr &aDevAddr);
	inline static TRfcommSockAddr& Cast(const TSockAddr& aDevAddr);
	};

//
// AVCTP
//

const static TInt KAVCTPErrBase = -6400;								/*!< AVCTP base error code */
const static TInt KErrAvctpBadAddress = KAVCTPErrBase;					/*!< AVCTP bad address error code */
const static TInt KErrAvctpSAPUnexpectedEvent = KAVCTPErrBase - 1;		/*!< AVCTP unexpected SAP event error code */
const static TInt KErrAvctpBadPacketReceived = KAVCTPErrBase - 2;		/*!< AVCTP bad packet received error code */
const static TInt KErrAvctpBadResponse = KAVCTPErrBase - 3;				/*!< AVCTP bad response error code */
const static TInt KErrAvctpConnectFailed = KAVCTPErrBase - 4;			/*!< AVCTP connect failed error code */
const static TInt KErrAvctpLinkDisconnection = KAVCTPErrBase - 5;		/*!< AVCTP link disconnection error code */
const static TInt KErrAvctpSAPNotConnected = KAVCTPErrBase - 6;			/*!< AVCTP SAP not connected error code */
const static TInt KErrAvctpPeerDisconnected = KAVCTPErrBase - 10;		/*!< AVCTP peer disconnection error code */
const static TInt KErrAvctpAccessRequestDenied = KAVCTPErrBase - 11;	/*!< AVCTP access request denied error code */
const static TInt KErrAvctpRequestTimeout = KAVCTPErrBase - 12;			/*!< AVCTP request timeout error code */
const static TInt KErrAvctpPeerRejectedCommand = KAVCTPErrBase - 13;	/*!< AVCTP peer rejected command error code */

//
// AVCTP ioctls
//

/** Gets AVCTP packet info
@internalTechnology
*/
const static TUint KAvctpGetPacketInfoIoctl		= 0x0000;

typedef TUint16 TAvctpPID;	/*!< Type definition of PID used for AVCTP */

class TAvctpSockAddr : public TBTSockAddr
/** AVCTP Socket Address.

Use this class to specify a local or remote AVCTP connection end-point,
that is: the BT device address and PID.
@publishedPartner
@prototype
*/
	{
public:
	IMPORT_C TAvctpSockAddr();
	IMPORT_C TAvctpSockAddr(const TSockAddr &aDevAddr);
	inline static TAvctpSockAddr& Cast(const TSockAddr &aDevAddr);
	//
	inline TAvctpPID PID() const;
	inline void SetPID(const TAvctpPID aPID);
	};


#include <bt_sock.inl>




/*****BASEBAND CLIENT*********/

class CBTBasebandSocketProxy;
class CBTBasebandPropertySubscriber;

class MBasebandObserver;
/** Array of device addresses
@see Enumerate method
*/
typedef RArray<TBTDevAddr> RBTDevAddrArray;		

class RBTBaseband
/** API useful for Bluetooth as seen from a single physical link perspective
@publishedAll
@released
*/
	{
public:
	RBTBaseband();
	//API useful for Bluetooth as seen from a single physical link perspective
	TInt Open(RSocketServ& aSocketServ, RSocket& aSocket);
	TInt Open(RSocketServ& aSocketServ, TBTDevAddr& aDevAddr);
	void Close();
	TInt PhysicalLinkState(TUint32& aState);
	TInt BasebandState(TUint32& aState); 
	TInt PreventRoleSwitch();
	TInt AllowRoleSwitch();
	TInt RequestMasterRole();
	TInt RequestSlaveRole();
	TInt PreventLowPowerModes(TUint32 aLowPowerModes);
	TInt AllowLowPowerModes(TUint32 aLowPowerModes);
	TInt ActivateSniffRequester();
	TInt ActivateParkRequester();
	TInt CancelLowPowerModeRequester();
	TInt RequestChangeSupportedPacketTypes(TUint16 aPacketTypes);
	//THE TWO NOTIFY METHODS BELOW MUST NOT BE CALLED CONCURRENTLY
	//Method to be used if only the next event should be notified
	void ActivateNotifierForOneShot(TBTBasebandEvent& aEventNotification, 
		                            TRequestStatus& aStatus, 
									TUint32 aEventMask);
	//Method to be used if it is intended to call it again 
	//(or call CancelNextBasebandChangeEventNotifier) when it completes 
	// - this sets up a continuous monitoring of events on the server.
	//Each time ActivateNotifierForOneShot is called it will either return
	//the next event in the servers notification queue or if the
	//queue is empty it will await the next event. 
	void ActivateNotifierForRecall(TBTBasebandEvent& aEventNotification, 
		                           TRequestStatus& aStatus, 
								   TUint32 aEventMask);
	void CancelNextBasebandChangeEventNotifier();
	
	//API useful for Bluetooth as seen from a device perspective
	TInt Open(RSocketServ& aSocketServ);
	void Connect(const TBTDevAddr& aDevAddr, TRequestStatus& aStatus);
	void Connect(const TPhysicalLinkQuickConnectionToken& aToken, TRequestStatus& aStatus);
	TInt Broadcast(const TDesC8& aData); // testing broadcast writes
	TInt ReadRaw(TDes8& aData);
	TInt Enumerate(RBTDevAddrArray& aBTDevAddrArray, TUint aMaxNumber);
	void TerminatePhysicalLink(TInt aReason);
	void TerminatePhysicalLink(TInt aReason, TRequestStatus& aStatus);
	void TerminatePhysicalLink(TInt aReason, const TBTDevAddr& aDevAddr, TRequestStatus& aStatus);
	void ShutdownPhysicalLink(TRequestStatus& aStatus);
	void TerminateAllPhysicalLinks(TInt aReason);
	void TerminateAllPhysicalLinks(TInt aReason, TRequestStatus& aStatus);
	TInt SubSessionHandle();
	
private:
	TInt RequestRole(TBTLMOptions aRole);
	TInt RequestEncrypt(THCIEncryptModeFlag aEnable);
	void LocalComplete(TRequestStatus& aStatus, TInt aErr);
	void SetClientPending(TRequestStatus& aStatus);
	void DoConnect(TRequestStatus& aStatus);
	TInt Enumerate(TDes8& aData);
	TInt Construct();
		
private:
	RSocketServ*			iSocketServer;
	RSocket					iSocket;

	TRequestStatus*							iClientRequestStatus;
	TBTSockAddr								iSocketAddress;				
	TPhysicalLinkQuickConnectionTokenBuf	iConnectToken;
	TBuf8<1>								iConnectInData; // not used yet - needed tho!
	TBuf8<1>								iDummySCOShutdownDescriptor;
	};


class RBTPhysicalLinkAdapter
/** Class to enable modification of a physical link:

Modifications may be requested or prevented (blocked).
Whilst a modification is being prevented, any request to
perform that modification by this or any other
RBTPhysicalLinkAdapter client will be ignored.
If a low power mode is being used on the physical link, a
call to prevent that low power mode will, if possible, cause
the physical link to exit that low power mode. An
arbitration between all RBTPhysicalLinkAdapter clients will then occur
to decide whether the physical link should remain active or 
enter another low power mode. (If all low power modes are prevented
then that arbitration will result in the physical link remaining
active.)

Methods to prevent modifications begin 'Prevent...'

Methods to cancel the prevention of modification begin 'Allow...'

Requests for low power mode modifications, and notification of modifications
take the form of continuously repeated requests which can be switched on or 
switched off. 

Only one low power mode requester may active on a single RBTPhysicalLinkAdapter
client at a time. If several RBTPhysicalLinkAdapter clients have differing low
power mode requests active at a given moment then the priority will be:
	Hold
	Sniff
	Park

Methods to perform these requests start 'Activate...'

Methods to cancel these requests start 'Cancel...'
@publishedAll
@released
*/
	{
public:
	IMPORT_C RBTPhysicalLinkAdapter();
	IMPORT_C TInt Open(RSocketServ& aSocketServ, RSocket& aSocket);
	IMPORT_C TInt Open(RSocketServ& aSocketServ, TBTDevAddr& aDevAddr);
	IMPORT_C void Close();
	IMPORT_C TInt PhysicalLinkState(TUint32& aState);
	IMPORT_C TInt PreventRoleSwitch();
	IMPORT_C TInt AllowRoleSwitch();
	IMPORT_C TInt RequestMasterRole();
	IMPORT_C TInt RequestSlaveRole();
	IMPORT_C TInt PreventLowPowerModes(TUint32 aLowPowerModes);
	IMPORT_C TInt AllowLowPowerModes(TUint32 aLowPowerModes);
	IMPORT_C TInt ActivateSniffRequester();
	IMPORT_C TInt ActivateParkRequester();
	IMPORT_C TInt CancelLowPowerModeRequester();
	IMPORT_C TInt RequestChangeSupportedPacketTypes(TUint16 aPacketTypes);
	IMPORT_C void NotifyNextBasebandChangeEvent(TBTBasebandEvent& aEventNotification, 
		                                        TRequestStatus& aStatus, 
						     		            TUint32 aEventMask = ENotifyAnyPhysicalLinkState);

	IMPORT_C void CancelNextBasebandChangeEventNotifier();
	
private:
	RBTBaseband iBTBaseband;
	};



class MBluetoothSocketNotifier
/** This allows for notification of events relating to a CBluetoothSocket object.

Such notification consists of notification of logical link events (for example receipt 
of a user packet) and physical link state events (for example change of power mode).

Mixin class to be used with CBluetoothPhysicalLinks
@publishedAll
@released
*/
	{
public:
	/** Notification of a connection complete event.
	
	 If no error is reported, then the connection is ready for use.
	 @param aErr the returned error
	*/
	virtual void HandleConnectCompleteL(TInt aErr) = 0;

	/** Notification of an accept complete event.
	
	 If no error is reported, then we have accepted a connection request 
	 and that connection is ready for use.
	 @param aErr the returned error
	*/
	virtual void HandleAcceptCompleteL(TInt aErr) = 0;

	/** Notification of a shutdown complete event.
	
	 If no error is reported, then the connection has been closed.
	 @param aErr the returned error
	*/
	virtual void HandleShutdownCompleteL(TInt aErr) = 0;

	/** Notification of a send complete event.
	
	 If no error is reported, then an attempt to send data over Bluetooth has succeeded.
	 @param aErr the returned error
	*/
	virtual void HandleSendCompleteL(TInt aErr) = 0;

	/** Notification of a receive complete event.
	
	 If no error is reported, then then we have successfully received
	 a specified quantity of data.
	 @param aErr the returned error
	*/
	virtual void HandleReceiveCompleteL(TInt aErr) = 0;

	/** Notification of a ioctl complete event.
	
	 An HCI request that has an associated command complete has completed.
	 @param aErr the returned error
	*/
	virtual void HandleIoctlCompleteL(TInt aErr) = 0;

	/** Notification of a baseband event.
	
	 If no error is reported, then the connection is ready for use.
	 @param aErr the returned error
	 @param TBTBasebandEventNotification Bit(s) set in TBTBasebandEventNotification bitmap indicate what event has taken place.
	 @see TBTPhysicalLinkStateNotifier
	*/
	virtual void HandleActivateBasebandEventNotifierCompleteL(TInt aErr, TBTBasebandEventNotification& aEventNotification) = 0;
	};


class CBTConnecter;
class CBTAccepter;
class CBTShutdowner;
class CBTReceiver;
class CBTSender;
class CBTIoctler;
class CBTBasebandChangeEventNotifier;

class CBluetoothSocket: public CBase
    /** This allows Bluetooth ACL socket-based services to be run.

    It allows all user-plane data flow to occur, plus control-plane Bluetooth 
    baseband modification capabilities.
    @publishedAll
    @released
    */
	{
public:
	IMPORT_C static CBluetoothSocket* NewL(MBluetoothSocketNotifier& aNotifier, 
										   RSocketServ& aServer,TUint aSockType,
										   TUint aProtocol);
	IMPORT_C static CBluetoothSocket* NewLC(MBluetoothSocketNotifier& aNotifier, 
										   RSocketServ& aServer,TUint aSockType,
										   TUint aProtocol);
	IMPORT_C static CBluetoothSocket* NewL(MBluetoothSocketNotifier& aNotifier, 
										   RSocketServ& aServer,TUint aSockType,
										   TUint aProtocol, 
										   RConnection& aConnection);
	IMPORT_C static CBluetoothSocket* NewLC(MBluetoothSocketNotifier& aNotifier, 
										   RSocketServ& aServer,
										   TUint aSockType,TUint aProtocol, 
										   RConnection& aConnection);
	IMPORT_C static CBluetoothSocket* NewL(MBluetoothSocketNotifier& aNotifier, 
										   RSocketServ& aServer,
										   const TDesC& aName);
	IMPORT_C static CBluetoothSocket* NewLC(MBluetoothSocketNotifier& aNotifier, 
										   RSocketServ& aServer,
										   const TDesC& aName);
	IMPORT_C static CBluetoothSocket* NewL(MBluetoothSocketNotifier& aNotifier, 
										   RSocketServ& aServer);
	IMPORT_C static CBluetoothSocket* NewLC(MBluetoothSocketNotifier& aNotifier, 
										   RSocketServ& aServer);
	IMPORT_C ~CBluetoothSocket();

	//Forwarding functions to RSocket
	IMPORT_C TInt Send(const TDesC8& aDesc,TUint someFlags);
	IMPORT_C TInt Send(const TDesC8& aDesc,TUint someFlags,TSockXfrLength& aLen);
	IMPORT_C void CancelSend();
	IMPORT_C TInt Recv(TDes8& aDesc,TUint flags);
	IMPORT_C TInt Recv(TDes8& aDesc,TUint flags,TSockXfrLength& aLen);
	IMPORT_C TInt RecvOneOrMore(TDes8& aDesc,TUint flags,TSockXfrLength& aLen);
	IMPORT_C void CancelRecv();
	IMPORT_C TInt Read(TDes8& aDesc);
	IMPORT_C void CancelRead();
	IMPORT_C TInt Write(const TDesC8& aDesc);
	IMPORT_C void CancelWrite();
	IMPORT_C TInt SendTo(const TDesC8& aDesc,TSockAddr& aDevAddr,TUint flags);
	IMPORT_C TInt SendTo(const TDesC8& aDesc,TSockAddr& aDevAddr,TUint flags,TSockXfrLength& aLen);
	IMPORT_C TInt RecvFrom(TDes8& aDesc,TSockAddr& aDevAddr,TUint flags);
	IMPORT_C TInt RecvFrom(TDes8& aDesc,TSockAddr& aDevAddr,TUint flags,TSockXfrLength& aLen);
	IMPORT_C TInt Connect(TBTSockAddr& aDevAddr);
	IMPORT_C TInt Connect(TBTSockAddr& aDevAddr,const TDesC8& aConnectDataOut,TDes8& aConnectDataIn);
	IMPORT_C void CancelConnect();
	IMPORT_C TInt Bind(TSockAddr& aDevAddr);
	IMPORT_C TInt SetLocalPort(TInt aPort);
	IMPORT_C TInt Accept(CBluetoothSocket& aBlankSocket);
	IMPORT_C TInt Accept(CBluetoothSocket& aBlankSocket,TDes8& aConnectData);
	IMPORT_C void CancelAccept();
	IMPORT_C TInt Listen(TUint qSize);
	IMPORT_C TInt Listen(TUint qSize,const TDesC8& aConnectData);
	IMPORT_C TInt SetOpt(TUint aOptionName,TUint aOptionLevel,const TDesC8& aOption=TPtrC8(NULL,0));
	IMPORT_C TInt SetOpt(TUint aOptionName,TUint aOptionLevel,TInt aOption);
	IMPORT_C TInt GetOpt(TUint aOptionName,TUint aOptionLevel,TDes8& aOption);
	IMPORT_C TInt GetOpt(TUint aOptionName,TUint aOptionLevel,TInt &aOption);
	IMPORT_C TInt Ioctl(TUint aCommand,TDes8* aDesc=NULL,TUint aLevel=KLevelUnspecified);
	IMPORT_C void CancelIoctl();
	IMPORT_C TInt GetDisconnectData(TDes8& aDesc);
	IMPORT_C void LocalName(TSockAddr& aDevAddr);
	IMPORT_C TUint LocalPort();
	IMPORT_C void RemoteName(TSockAddr& aDevAddr);
	IMPORT_C TInt Shutdown(RSocket::TShutdown aHow);
	IMPORT_C TInt Shutdown(RSocket::TShutdown aHow,const TDesC8& aDisconnectDataOut,TDes8& aDisconnectDataIn);
	IMPORT_C void CancelAll();
	IMPORT_C TInt Info(TProtocolDesc& aProtocol);
	IMPORT_C TInt Name(TName& aName);
	IMPORT_C TInt Transfer(RSocketServ& aServer, const TDesC& aName);

	
	//Forwarding functions to RBTBaseband
	IMPORT_C TInt PhysicalLinkState(TUint32& aState);
	IMPORT_C TInt PreventRoleSwitch();
	IMPORT_C TInt AllowRoleSwitch();
	IMPORT_C TInt RequestMasterRole();
	IMPORT_C TInt RequestSlaveRole();
	IMPORT_C TInt PreventLowPowerModes(TUint32 aLowPowerModes);
	IMPORT_C TInt AllowLowPowerModes(TUint32 aLowPowerModes);
	IMPORT_C TInt ActivateSniffRequester();
	IMPORT_C TInt ActivateParkRequester();
	IMPORT_C TInt CancelLowPowerModeRequester();
	IMPORT_C TInt RequestChangeSupportedPacketTypes(TUint16 aPacketTypes);
	IMPORT_C TInt ActivateBasebandEventNotifier(TUint32 aEventTypes);
	IMPORT_C void CancelBasebandEventNotifier();
		
	IMPORT_C void SetNotifier(MBluetoothSocketNotifier& aNewNotifier);

	//Callback functions called by active object RunLs.
	// NB These functions kill the active objects that call them (cf mating spiders) 
	MBluetoothSocketNotifier& Notifier();
	void HandleConnectCompleteL(TInt aErr);
	void HandleAcceptCompleteL(TInt aErr);
	void HandleShutdownCompleteL(TInt aErr);
	void HandleSendCompleteL(TInt aErr);
	void HandleReceiveCompleteL(TInt aErr);
	void HandleIoctlCompleteL(TInt aErr);
	void HandleActivateBasebandEventNotifierCompleteL(TInt aErr, TBTBasebandEventNotification aEventNotification);

public:
	RBTBaseband& BTBaseband();
	RSocket& Socket();
	RSocketServ& SocketServer();

private:
	CBluetoothSocket(MBluetoothSocketNotifier& aNotifier, RSocketServ& aServer);
	void ConstructL(TUint aSockType,TUint aProtocol);
	void ConstructL(TUint aSockType,TUint aProtocol, RConnection& aConnection);
	void ConstructL(const TDesC& aName);
	void ConstructL();

private:
	RSocket							iSocket;
	RSocketServ						iSockServer;
	RBTBaseband						iBTBaseband;
	TBTSockAddr						iSockAddr;

	MBluetoothSocketNotifier*		iNotifier;

	CBTConnecter* 					iBTConnecter;
	CBTAccepter*					iBTAccepter;
	CBTShutdowner*					iBTShutdowner;
	CBTReceiver*					iBTReceiver;	//for read, recv etc
	CBTSender*						iBTSender;		//for send, write etc
	CBTIoctler*						iBTIoctler;
	CBTBasebandChangeEventNotifier* iBTBasebandChangeEventNotifier;
	TUint32							iNotifierEventMask;
	TBool							iSending;
	TBool							iReceiving;
	};


class MBluetoothSynchronousLinkNotifier
/** SCO and eSCO link notification events.

This allows for notification of Connect, Disconnect, Send and
Receive events relating to SCO and eSCO links.

Mixin class to be used with CBluetoothPhysicalLinks
@publishedAll
@released
*/
	{
public:
	/** Notification that a synchronous link (SCO) has been set up
	
	 If no error is reported, then the synchronous link is ready for use.
	 @param aErr the returned error
	*/
	virtual void HandleSetupConnectionCompleteL(TInt aErr) = 0;

	/** Notification that a synchronous link (SCO) has disconnected
	
	 If no error is reported, then the synchronous link has been closed.
	 @param aErr the returned error
	*/
	virtual void HandleDisconnectionCompleteL(TInt aErr) = 0;

	/** Notification that a synchronous link (SCO) has been accepted
	
	 If no error is reported, then we have accepted a request for a synchronous link.
	 That synchronous link is ready for use.
	 @param aErr the returned error
	*/
	virtual void HandleAcceptConnectionCompleteL(TInt aErr) = 0;

	/** Notification of a send complete event
	
	 If no error is reported, then an attempt to send synchronous (SCO) data 
	 (e.g. voice) over Bluetooth has succeeded.
	 @param aErr the returned error
	*/
	virtual void HandleSendCompleteL(TInt aErr) = 0;

	/** Notification of a receive complete event
	
	 If no error is reported, then then we have successfully received
	 a specified quantity of synchronous (SCO) data.
	 @param aErr the returned error
	*/
	virtual void HandleReceiveCompleteL(TInt aErr) = 0;
	};

class CBTSynchronousLinkAttacher;
class CBTSynchronousLinkDetacher;
class CBTSynchronousLinkAccepter;
class CBTSynchronousLinkSender;
class CBTSynchronousLinkReceiver;
class CBTSynchronousLinkEventCatcher;


class CBluetoothSynchronousLink: public CBase
/** Provides Bluetooth SCO functionality.

This allows Bluetooth SCO (synchronous) link Connect, Disconnect, Send and Receive.
@publishedAll
@released
*/
	{
public:
	IMPORT_C static CBluetoothSynchronousLink* NewL(MBluetoothSynchronousLinkNotifier& aNotifier, 
											  RSocketServ& aServer);
	IMPORT_C static CBluetoothSynchronousLink* NewLC(MBluetoothSynchronousLinkNotifier& aNotifier,
											   RSocketServ& aServer);
	IMPORT_C ~CBluetoothSynchronousLink();

	IMPORT_C TInt SetupConnection(const TBTDevAddr& aDevAddr);
	IMPORT_C TInt SetupConnection(const TBTDevAddr& aDevAddr, const TUint16 aHVPacketTypes);
	IMPORT_C void CancelSetup();
	IMPORT_C TInt Disconnect();
	IMPORT_C TInt Send(const TDesC8& aData);
	IMPORT_C void CancelSend();
	IMPORT_C TInt Receive(TDes8& aData/*,TUint aFlags*/);
	IMPORT_C void CancelReceive();
	IMPORT_C TInt AcceptConnection();
	IMPORT_C void CancelAccept();
	
	IMPORT_C void RemoteName(TSockAddr& aAddr);

	MBluetoothSynchronousLinkNotifier& Notifier();
	RSocket& Socket();
	RSocket& ListeningSocket();
	RSocketServ& SocketServer();

	
	//Callback methods called by active object RunLs.
	//NB These methods kill the active objects that call them (cf mating spiders) 
	void HandleSetupConnectionCompleteL(TInt aErr);
	void HandleAcceptConnectionCompleteL(TInt aErr);
	void HandleDisconnectionCompleteL(TInt aErr);
	void HandleSendCompleteL(TInt aErr);
	void HandleReceiveCompleteL(TInt aErr);

private:
	CBluetoothSynchronousLink(MBluetoothSynchronousLinkNotifier& aNotifier, RSocketServ& aServer);
	void ConstructL();

private:
	CBTSynchronousLinkSender*			iBTSynchronousLinkSender;
	CBTSynchronousLinkReceiver*			iBTSynchronousLinkReceiver;
	CBTSynchronousLinkAccepter*			iBTSynchronousLinkAccepter;
	CBTSynchronousLinkAttacher* 		iBTSynchronousLinkAttacher;
	CBTSynchronousLinkDetacher* 		iBTSynchronousLinkDetacher;
	CBTSynchronousLinkEventCatcher*		iBTSynchronousLinkEventCatcher;
	MBluetoothSynchronousLinkNotifier&	iNotifier;
	RSocket								iSocket;
	RSocket 							iListeningSocket;
	RSocketServ 						iSockServer;
	TBTSockAddr 						iSockAddr;
	TBuf8<1> 							iDummySCOShutdownDescriptor;
	};


class MBluetoothPhysicalLinksNotifier
/** This allows for notifications of Physical link connections & disconnections

Mixin class to be used with CBluetoothPhysicalLinks
@publishedAll
@released
*/
	{
public:
	/** Notification of a requested connection coming up
	
	 If no error is reported, then that connection is ready for use.
	 @param aErr the returned error
	*/
	virtual void HandleCreateConnectionCompleteL(TInt aErr) = 0;

	/** Notification of a requested disconnection having taken place
	
	 If no error is reported, then that connection has been closed.
	 @param aErr the returned error
	*/
	virtual void HandleDisconnectCompleteL(TInt aErr) = 0;

	/** Notification that all existing connections have been torn down
	
	 If no error is reported, then there are no Bluetooth connections existing.
	 @param aErr the returned error
	*/
	virtual void HandleDisconnectAllCompleteL(TInt aErr) = 0;
	};


class CBTBasebandConnecter;
class CBTBasebandShutdowner;
class CBTDisconnector;

class CBluetoothPhysicalLinks: public CBase
/** This is used to enumerate members of piconet, and attach and remove members thereof

It may also be used for non-service dependent reads and writes.
@publishedAll
@released
*/
	{
public:
	IMPORT_C static CBluetoothPhysicalLinks* NewL(MBluetoothPhysicalLinksNotifier& aNotifier,
											      RSocketServ& aServer);
	IMPORT_C static CBluetoothPhysicalLinks* NewLC(MBluetoothPhysicalLinksNotifier& aNotifier,
											      RSocketServ& aServer);
	IMPORT_C ~CBluetoothPhysicalLinks();

	IMPORT_C TInt CreateConnection(const TBTDevAddr& aDevAddr);
	IMPORT_C void CancelCreateConnection();
	IMPORT_C TInt Disconnect(const TBTDevAddr& aDevAddr);
	IMPORT_C TInt DisconnectAll();
	
	IMPORT_C TInt Broadcast(const TDesC8& aData);
	IMPORT_C TInt ReadRaw(TDes8& aData);
	IMPORT_C TInt Enumerate(RBTDevAddrArray& aBTDevAddrArray, TUint aMaxNumber);

	
	//Callback methods called by active object RunLs.
	//NB These methods kill the active objects that call them
	void HandleCreateConnectionCompleteL(TInt aErr);
	void HandleDisconnectCompleteL(TInt aErr);
	void HandleDisconnectAllCompleteL(TInt aErr);

	RSocketServ& SockServer();
	RBTBaseband& BTBaseband();
	MBluetoothPhysicalLinksNotifier& Notifier();


private:
	CBluetoothPhysicalLinks(MBluetoothPhysicalLinksNotifier& aNotifier, 
							RSocketServ& aServer);
	void ConstructL();

private:
	CBTBasebandConnecter* iBTBasebandConnecter;
	CBTDisconnector* iBTDisconnector;
	MBluetoothPhysicalLinksNotifier& iNotifier;
	RSocketServ& iSockServer;
	RBTBaseband iBTBaseband;
	};




class RBluetoothPowerSwitch
/** This is intended for controlling whether the Bluetooth hardware is switched on or not.

@publishedPartner
@prototype
*/
	{
	public:

	IMPORT_C RBluetoothPowerSwitch();
	IMPORT_C void RequestSwitchOn();
	IMPORT_C void RequestSwitchOff();
	};

#endif
