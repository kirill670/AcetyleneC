// d32usbc.h
//
// Copyright (c) Symbian Software Ltd 1995-2004.  All rights reserved.
//

/** @file
	@publishedAll
	@released
*/

#ifndef __D32USBC_H__
#define __D32USBC_H__

#include <e32ver.h>
#include <usb.h>


// USB driver error codes

/** USB driver specific error codes start from here */
const TInt KErrUsbDriverBase = -6701;

/**
	Attempt at data transfer, or something interface related,
	when neither an Interface has been set up nor Device Control is owned by
	the channel
*/
const TInt KErrUsbInterfaceNotReady = KErrUsbDriverBase - 1;

/**
	Attempt at data transfer on an endpoint that does not belong to the active interface
*/
const TInt KErrUsbEpNotInInterface = KErrUsbDriverBase - 2;

/**
	Attempt at data transfer in a direction not supported by the endpoint
*/
const TInt KErrUsbEpBadDirection = KErrUsbDriverBase - 3;

/**
	The data transfer size specified exceeds that of the source or
	destination buffer descriptor
*/
const TInt KErrUsbTransferSize = KErrUsbDriverBase - 4;

/**
	This has multiple uses:
	1) User request completed because device is no longer in configured state
	2) Something endpoint related, stall, unstall, status enquiry etc,
	   that requires the device to be configured
*/
const TInt KErrUsbDeviceNotConfigured = KErrUsbDriverBase - 5;

/**
	Requested endpoint properties inconsistent during Interface setup
*/
const TInt KErrUsbBadEndpoint = KErrUsbDriverBase - 6;

/**
	User data request completed because channel is closing (channel destructor called)
*/
const TInt KErrUsbDeviceClosing = KErrUsbDriverBase - 7;

/**
	User data request completed because current endpoint set is being
	replaced since alternate setting is changing
*/
const TInt KErrUsbInterfaceChange = KErrUsbDriverBase - 8;

/**
	User data request completed because cable has been detached (or equivalent)
*/
const TInt KErrUsbCableDetached = KErrUsbDriverBase - 9;

/**
	User data request completed because cable has been detached (or equivalent)
*/
const TInt KErrUsbDeviceBusReset = KErrUsbDriverBase - 10;

/**
	This means that read data is still available when a write request is made.
	Relates to bidirectional eps only (ep0).
	A bidirectional ep must consume all of its read data before attempting to write.
*/
const TInt KErrUsbEpNotReady = KErrUsbDriverBase - 11;


enum TUsbcDeviceState
	{ // These states are described but not given values in the standard
	  // p176 Fig 9-1
	EUsbcDeviceStateUndefined,
	EUsbcDeviceStateAttached,
	EUsbcDeviceStatePowered,
	EUsbcDeviceStateDefault,
	EUsbcDeviceStateAddress,
	EUsbcDeviceStateConfigured,
	EUsbcDeviceStateSuspended,
	EUsbcNoState = 0xff										// used as a place holder
	};


enum TTransferType
	{
	ETransferTypeReadData,
	ETransferTypeReadPacket,
	ETransferTypeWrite,
	ETransferTypeNone,
	ETransferTypeReadUntilShort,
	ETransferTypeReadOneOrMore
	};


enum TEndpointNumber
	{
	EEndpoint0 = 0,
	EEndpoint1 = 1,
	EEndpoint2 = 2,
	EEndpoint3 = 3,
	EEndpoint4 = 4,
	EEndpoint5 = 5
	};


enum TEndpointState
	{
	EEndpointStateNotStalled,
	EEndpointStateStalled,
	EEndpointStateUnknown
	};


enum TUsbcBandwidthPriority
	{
	EUsbcBandwidthOUTDefault=0x00, /** Economical OUT buffering */
	EUsbcBandwidthOUTPlus1=0x01,   /** More memory than Default for OUT buffering */
	EUsbcBandwidthOUTPlus2=0x02,   /** More memory than Plus1 for OUT buffering */
	EUsbcBandwidthOUTMaximum=0x03, /** Maximum memory for OUT buffering */
//
	EUsbcBandwidthINDefault=0x00,  /** Economical IN buffering */
	EUsbcBandwidthINPlus1=0x10,	   /** More memory than Default for IN buffering */
	EUsbcBandwidthINPlus2=0x20,	   /** More memory than Plus1 for IN buffering */
	EUsbcBandwidthINMaximum=0x30   /** Maximum memory for IN buffering */
	};


enum TUsbcEndpointResource
	{
	EUsbcEndpointResourceDMA			  = 0,	/** Requests the use of DMA */
	EUsbcEndpointResourceDoubleBuffering  = 1,	/** Requests the use of double FIFO buffering */
	};

class TCapsDevUsbc
	  {
public:
	  TVersion version;
	  };


const TInt KUsbcMaxEndpoints = 30;							// w/o endpoint 0
const TInt KMaxEndpointsPerClient = 5;
const TInt KUsbAlternateSetting = 0x80000000;


class TUsbDeviceCapsV01
	{
public:
	TInt iTotalEndpoints;
	TBool iConnect;
	TBool iSelfPowered;
	TBool iRemoteWakeup;
	};


typedef TPckgBuf<TUsbDeviceCapsV01> TUsbDeviceCaps;

const TUint KUsbEpNotAvailable	  = 0x00000000;

// bitmap for TUsbcEndpointCaps.iSupportedSizes
const TUint KUsbEpSizeCont		  = 0x00000001;
const TUint KUsbEpSize8			  = 0x00000008;
const TUint KUsbEpSize16		  = 0x00000010;
const TUint KUsbEpSize32		  = 0x00000020;
const TUint KUsbEpSize64		  = 0x00000040;
const TUint KUsbEpSize128		  = 0x00000080;
const TUint KUsbEpSize256		  = 0x00000100;
const TUint KUsbEpSize512		  = 0x00000200;
const TUint KUsbEpSize1023		  = 0x00000400;

// bitmap for TUsbcEndpointCaps.iSupportedTypesAndDir
const TUint KUsbEpTypeControl	  = 0x00000001;
const TUint KUsbEpTypeIsochronous = 0x00000002;
const TUint KUsbEpTypeBulk		  = 0x00000004;
const TUint KUsbEpTypeInterrupt	  = 0x00000008;
const TUint KUsbEpDirIn			  = 0x80000000;
const TUint KUsbEpDirOut		  = 0x40000000;
const TUint KUsbEpDirBidirect	  = 0x20000000;

static inline TUint PacketSize2Mask(TInt aSize);
static inline TUint EpTypeMask2Value(TInt aType);


class TUsbcEndpointCaps
	{
public:
	TInt MaxPacketSize() const;
	TInt MinPacketSize() const;
public:
	TUint iSizes;											// Supported max packet sizes
	TUint iTypesAndDir;										// Supported endpoint types and directions
	};


class TUsbcEndpointData
	{
public:
	TUsbcEndpointCaps iCaps;								// see above
	TBool iInUse;											// whether this endpoint already claimed
	};


class TUsbcEndpointInfo
	{
public:
	TUsbcEndpointInfo(TUint aType=KUsbEpTypeBulk, TUint aDir=KUsbEpDirOut,
					  TInt aSize=0, TInt aInterval=0, TInt aExtra=0);
public:
	TUint iType;											// Endpoint type (mask: KUsbEpTypeControl, etc)
	TUint iDir;												// Direction (mask: KUsbEpDirIn, etc)
	TInt iSize;												// Maximum packet size (literal, no mask)
	TInt iInterval;						// Interval for polling interrupt endpoint, expressed in milliseconds.
	TInt iExtra;											// Number of extra bytes
	};


class TUsbcClassInfo
	{
public:
	TUsbcClassInfo(TInt aClass=0,TInt aSubClass=0,TInt aProtocol=0);
public:
	TInt iClassNum;											// The class type number.
	TInt iSubClassNum;										// The sub-class type number.
	TInt iProtocolNum;										// The protocol number.
	};


class TUsbcInterfaceInfo
	{
public:
	TUsbcInterfaceInfo(TInt aClass=0,TInt aSubClass=0,TInt aProtocol=0,
					   TDesC16* aString=0,TUint aTotalEndpoints=0);
public:
	TUsbcClassInfo iClass;
	TDesC16* iString;										// String to Insert in Interface String Descriptor
	TUint iTotalEndpointsUsed;								// Total number of endpoints being requested (0-5)
	TUsbcEndpointInfo iEndpointData[KMaxEndpointsPerClient];
	};


class TEndpointTransferInfo
	{
public:
	TDesC8* iDes;
	TTransferType iTransferType;
	TInt iTransferSize;
	TBool iZlpReqd;
	};


class TEndpointDescriptorInfo
	{
public:
	TInt iSetting;											// alternate setting
	TInt iEndpoint;											// excludes ep0
	TAny* iArg;												// address of data
	};


class TCSDescriptorInfo
	{
public:
	TInt iSetting;											// alternate setting
	TInt iEndpoint;											// excludes ep0, not used for CS ifc desc
	TAny* iArg;												// address of data
	TInt iSize;												// size of data (descriptor block)
	};


class TUsbcStatusNotifyInfo
	{
public:
	TUint iStatusMask;
	TUsbcDeviceState* iDeviceStatus;
	};


typedef TPckgBuf<TUsbcInterfaceInfo> TUsbcInterfaceInfoBuf;

class RDevUsbcClient : public RBusLogicalChannel
	{

public:
	enum TVer
		{
		EMajorVersionNumber = 0,
		EMinorVersionNumber = 1,
		EBuildVersionNumber = KE32BuildVersionNumber,
		};

	enum TRequest
		{
		ERequestEp0 = 0x0,		  ERequestEp0Cancel = 1<<ERequestEp0,
		ERequestEp1 = EEndpoint1, ERequestEp1Cancel = 1<<ERequestEp1,
		ERequestEp2 = EEndpoint2, ERequestEp2Cancel = 1<<ERequestEp2,
		ERequestEp3 = EEndpoint3, ERequestEp3Cancel = 1<<ERequestEp3,
		ERequestEp4 = EEndpoint4, ERequestEp4Cancel = 1<<ERequestEp4,
		ERequestEp5 = EEndpoint5, ERequestEp5Cancel = 1<<ERequestEp5,
		};

	enum TControl
		{
		EControlEndpointZeroRequestError,					// 0
		EControlEndpointCaps,
		EControlDeviceCaps,
		EControlGetAlternateSetting,
		EControlDeviceStatus,
		EControlEndpointStatus,
		EControlSetInterface,
		EControlReleaseInterface,
		EControlQueryReceiveBuffer,
		EControlReqAlternateDeviceStatusNotify,
		//
		EControlReqReEnumerate,								// 10
		EControlReqAlternateDeviceStatusNotifyCancel,
		EControlReqReEnumerateCancel,
		EControlSendEp0StatusPacket,
		EControlHaltEndpoint,
		EControlClearHaltEndpoint,
		EControlNotifyEndpointStatus,
		EControlCancelNotifyEndpointStatus,
		EControlSetDeviceControl,
		EControlReleaseDeviceControl,
		//
		EControlEndpointZeroMaxPacketSizes,					// 20
		EControlSetEndpointZeroMaxPacketSize,
		EControlGetDeviceDescriptor,
		EControlSetDeviceDescriptor,
		EControlGetDeviceDescriptorSize,
		EControlGetConfigurationDescriptor,
		EControlSetConfigurationDescriptor,
		EControlGetConfigurationDescriptorSize,
		EControlGetInterfaceDescriptor,
		EControlSetInterfaceDescriptor,
		//
		EControlGetInterfaceDescriptorSize,					// 30
		EControlGetEndpointDescriptor,
		EControlSetEndpointDescriptor,
		EControlGetEndpointDescriptorSize,
		EControlGetCSInterfaceDescriptor,
		EControlSetCSInterfaceDescriptor,
		EControlGetCSInterfaceDescriptorSize,
		EControlGetCSEndpointDescriptor,
		EControlSetCSEndpointDescriptor,
		EControlGetCSEndpointDescriptorSize,
		//
		EControlSignalRemoteWakeup,							// 40
		EControlGetManufacturerStringDescriptor,
		EControlSetManufacturerStringDescriptor,
		EControlGetProductStringDescriptor,
		EControlSetProductStringDescriptor,
		EControlGetSerialNumberStringDescriptor,
		EControlSetSerialNumberStringDescriptor,
		EControlGetConfigurationStringDescriptor,
		EControlSetConfigurationStringDescriptor,
		EControlDeviceDisconnectFromHost,
		//
		EControlDeviceConnectToHost,						// 50
		EControlDevicePowerUpUdc,
		EControlDumpRegisters,
		EControlSetInterface1,
		EControlAllocateEndpointResource,
		EControlDeAllocateEndpointResource,
		EControlQueryEndpointResourceUse
		};

public:
	inline TInt Open(TInt aUnit);
	inline TVersion VersionRequired() const;
	// DoControl
	inline TInt EndpointZeroRequestError();
	inline TInt EndpointCaps(TDes8& aEpCapsBuf);
	inline TInt DeviceCaps(TDes8& aDevCapsBuf);
	inline TInt GetAlternateSetting(TInt& aInterfaceNumber);
	inline TInt DeviceStatus(TUsbcDeviceState& aDeviceStatus);
	inline TInt EndpointStatus(TEndpointNumber aEndpoint,TEndpointState& aEndpointStatus);
	inline TInt QueryReceiveBuffer(TEndpointNumber aEndpoint,TInt& aNumberOfBytes);
	inline TInt SendEp0StatusPacket();
	inline TInt HaltEndpoint(TEndpointNumber aEndpoint);
	inline TInt ClearHaltEndpoint(TEndpointNumber aEndpoint);
	inline TInt SetDeviceControl();
	inline TInt ReleaseDeviceControl();
	inline TUint EndpointZeroMaxPacketSizes();
	inline TInt SetEndpointZeroMaxPacketSize(TInt aMaxPacketSize);
	inline TInt GetDeviceDescriptor(TDes8& aDeviceDescriptor);
	inline TInt SetDeviceDescriptor(const TDesC8& aDeviceDescriptor);
	inline void GetDeviceDescriptorSize(TInt& aSize);
	inline TInt GetConfigurationDescriptor(TDes8& aConfigurationDescriptor);
	inline TInt SetConfigurationDescriptor(const TDesC8& aConfigurationDescriptor);
	inline void GetConfigurationDescriptorSize(TInt& aSize);
	inline TInt GetInterfaceDescriptor(TInt aSettingNumber, TDes8& aInterfaceDescriptor);
	inline TInt SetInterfaceDescriptor(TInt aSettingNumber, const TDesC8& aInterfaceDescriptor);
	inline TInt GetInterfaceDescriptorSize(TInt aSettingNumber, TInt& aSize);
	inline TInt GetEndpointDescriptor(TInt aSettingNumber, TInt aEndpointNumber, TDes8& aEndpointDescriptor);
	inline TInt SetEndpointDescriptor(TInt aSettingNumber, TInt aEndpointNumber,
									  const TDesC8& aEndpointDescriptor);
	inline TInt GetEndpointDescriptorSize(TInt aSettingNumber, TInt aEndpointNumber, TInt& aSize);
	inline TInt GetCSInterfaceDescriptorBlock(TInt aSettingNumber, TDes8& aInterfaceDescriptor);
	inline TInt SetCSInterfaceDescriptorBlock(TInt aSettingNumber, const TDesC8& aInterfaceDescriptor);
	inline TInt GetCSInterfaceDescriptorBlockSize(TInt aSettingNumber, TInt& aSize);
	inline TInt GetCSEndpointDescriptorBlock(TInt aSettingNumber, TInt aEndpointNumber,
											 TDes8& aEndpointDescriptor);
	inline TInt SetCSEndpointDescriptorBlock(TInt aSettingNumber, TInt aEndpointNumber,
											 const TDesC8& aEndpointDescriptor);
	inline TInt GetCSEndpointDescriptorBlockSize(TInt aSettingNumber, TInt aEndpointNumber, TInt& aSize);
	inline TInt SignalRemoteWakeup();
	inline TInt DeviceDisconnectFromHost();
	inline TInt DeviceConnectToHost();
	inline TInt PowerUpUdc();
	inline TInt AllocateEndpointResource(TInt aEndpoint, TUsbcEndpointResource aResource);
	inline TInt DeAllocateEndpointResource(TInt aEndpoint, TUsbcEndpointResource aResource);
	inline TBool QueryEndpointResourceUse(TInt aEndpoint, TUsbcEndpointResource aResource);

	// DoSvControl
	inline TInt SetInterface(TInt aInterfaceNumber, TUsbcInterfaceInfoBuf& aInterfaceData);
	inline TInt SetInterface(TInt aInterfaceNumber, TUsbcInterfaceInfoBuf& aInterfaceData,
							 TUint32 aBandwidthPriority);
	inline TInt ReleaseInterface(TInt aInterfaceNumber);

	inline TInt GetManufacturerStringDescriptor(TDes16& aString);
	inline TInt SetManufacturerStringDescriptor(const TDesC16& aString);

	inline TInt GetProductStringDescriptor(TDes16& aString);
	inline TInt SetProductStringDescriptor(const TDesC16& aString);

	inline TInt GetSerialNumberStringDescriptor(TDes16& aString);
	inline TInt SetSerialNumberStringDescriptor(const TDesC16& aString);

	inline TInt GetConfigurationStringDescriptor(TDes16& aString);
	inline TInt SetConfigurationStringDescriptor(const TDesC16& aString);

	// DoRequest
	inline void Read(TRequestStatus& aStatus, TEndpointNumber aEndpoint, TDes8& aDes);
	inline void Read(TRequestStatus& aStatus, TEndpointNumber aEndpoint, TDes8& aDes, TInt aLen);
	inline void ReadPacket(TRequestStatus& aStatus, TEndpointNumber aEndpoint,TDes8& aDes,TInt aMaxLen);
	inline void ReadCancel(TEndpointNumber aEndpoint);
	inline void ReadUntilShort(TRequestStatus& aStatus, TEndpointNumber aEndpoint, TDes8& aDes);
	inline void ReadUntilShort(TRequestStatus& aStatus, TEndpointNumber aEndpoint, TDes8& aDes, TInt aLen);
	inline void ReadOneOrMore(TRequestStatus& aStatus, TEndpointNumber aEndpoint, TDes8& aDes);
	inline void ReadOneOrMore(TRequestStatus& aStatus, TEndpointNumber aEndpoint, TDes8& aDes, TInt aLen);
	//
	inline void Write(TRequestStatus& aStatus, TEndpointNumber aEndpoint, const TDesC8& aDes, TInt aLen,
					  TBool aZlpRequired=EFalse);
	inline void WriteCancel(TEndpointNumber aEndpoint);
	//
	inline void EndpointTransferCancel(TUint aTransferMask);
	//
	inline void AlternateDeviceStatusNotify(TRequestStatus& aStatus, TUint& aValue);
	inline void ReEnumerate(TRequestStatus& aStatus);

	inline void AlternateDeviceStatusNotifyCancel();
	inline void ReEnumerateCancel();

	inline void EndpointStatusNotify(TRequestStatus& aStatus, TUint& aEndpointMask);
	inline void EndpointStatusNotifyCancel();
	//
	inline void DumpRegisters();
	};


#include <d32usbc.inl>

#endif // __D32USBC_H__
