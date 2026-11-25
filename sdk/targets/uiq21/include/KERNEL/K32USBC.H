// k32usbc.h
// Kernel side header for USB device driver.
//
// Copyright (c) 1996-2002 Symbian Ltd. All rights reserved.
//

#if !defined(__K32USBC_H__)
#define __K32USBC_H__

#include <k32std.h>
#include <k32power.h>
#include <m32std.h>
#include <d32usbc.h>


// Define here whatever is appropriate (i.e. true):
//#define USB_SUPPORTS_CONTROLENDPOINTS
//#define USB_SUPPORTS_SET_DESCRIPTOR_REQUEST

const TInt KErrEndpointStall    = KErrLocked;
const TInt KErrPrematureEnd     = KErrDiskFull;

const TInt KUsbcMajorVersion    = 0;
const TInt KUsbcMinorVersion    = 1;
const TInt KUsbcBuildVersion    = KE32BuildVersionNumber;

const TInt KDmaBufSzControl     = 2048;
const TInt KDmaBufSzBulk        = 4096;
const TInt KDmaBufSzInterrupt   = 4096;
const TInt KDmaBufSzIsochronous = 4096;
const TInt KDmaBufSz_Ep0Rx      = 4096;
const TInt KDmaBufSz_Ep0Tx      = 4096;

const TInt KUsbcBufSzControl    = 64;						// max size that ep0 packets might ever have
const TInt KUsbcBufSz_Ep0Rx     = 1024;						// the ep0 rx collection buffer area
const TInt KUsbcBufSz_Ep0Tx     = 1024;						// the ep0 tx buffer area
const TInt KUsbDeviceStatusQueueDepth = 15;			// depth of the status fifo. enough for 2 complete configs
const TInt KUsbDeviceStatusNull = 0xffffffff;				// no status info

const TUint16 KUsbcUsbVersion   = 0x0110;					// the USB version we are compliant with (BCD: 1.1)

enum TUsbcEp0State
	{
	EEp0StateNone,		// 0
	EEp0StateIdle,		// 1
	EEp0StateSetup,		// 2
	EEp0StateDataIn,	// 3
	EEp0StateDataOut,	// 4
	EEp0StateStatusIn,	// 5
	EEp0StateStatusOut	// 6
	};

enum TUsbcStopMode {EUsbcStopNormal, EUsbcStopPwrDown, EUsbcStopEmergency};
enum TTransferDirection {EControllerNone, EControllerRead, EControllerWrite};

enum TUsbcDeviceEvent
	{
	EUsbEventSuspend,
	EUsbEventResume,
	EUsbEventReset,
	EUsbEventCableRemoved,
	EUsbEventCableInserted
	};

class TUsbcEndpointStatusCallBack
	{  // This is endpoint halt/clear halt status
public:
	TUsbcEndpointStatusCallBack(CBase* anOwner, const TCallBack& aCallBack);
	inline void SetState(TUint aState);
	inline TUint State() const;
	inline CBase* Owner() const {return iOwner;}
	inline void DoCallback() {Kern::Add(iCallBack);}
	inline void Cancel() {iCallBack.Cancel();}
public:
	TSglQueLink iSLink;
private:
	CBase* iOwner;
	TUint iState;
	TDfc iCallBack;
	};


static const TInt KUsbcDeviceRequests = 8;

class TUsbcStatusCallBack
	{  // This is device status
public:
	TUsbcStatusCallBack(CBase* anOwner, const TCallBack& aCallBack);
	inline void SetState(TUsbcDeviceState aState);
	inline TUsbcDeviceState State(TInt aIndex) const;
	inline void ResetState();
	inline CBase* Owner() const {return iOwner;}
	inline void DoCallback() {Kern::Add(iCallBack);}
	inline void Cancel() {iCallBack.Cancel();}

public:
	TSglQueLink iSLink;
private:
	CBase* iOwner;
	TUsbcDeviceState iState[KUsbcDeviceRequests];
	TDfc iCallBack;
	};

class TUsbcRequestCallBack
	{
public:
	TUsbcRequestCallBack(CBase* anOwner, TInt aEndpointNumber, const TCallBack& aCallBack);
	inline void SetCount(TInt aCount);
	inline void SetBufferInfo(TUint8* aBufferStart, TInt aLength);
	inline void SetTransferDirection(TTransferDirection aTransferDir) {iTransferDir=aTransferDir;}
	inline CBase* Owner() const {return iOwner;}
 	inline TInt DoCallback() {return iCallBack.CallBack();}
public:
	TSglQueLink iSLink;
public:
	CBase* iOwner;
	const TInt iEndpointNum;
	TCallBack iCallBack;
	TTransferDirection iTransferDir;
	TInt iLength;
	TUint8* iBufferStart;
	TBool iZlpReqd;
	TInt iCount;
	TInt iError;
	};

//
// Template LDD factory
//
class DUsbcLogDevice : public DLogicalDevice
      {
public:
      DUsbcLogDevice();
//override pure virtual
      virtual TInt Install();
      virtual void GetCaps(TDes8& aDes) const;
      virtual DLogicalChannel* CreateL();
      };
/**********************Dma Buffers*********************************/

class DUsbClientController;//forward declaration
class TPacket
	{
public:
	TPacket(TInt aStartPos=0,TInt aPacketSize=0, TInt aErrorCode=0);
	TInt iStartPos;
	TInt iPacketSize;
	TInt iErrorCode;
	};

class TUsbcEndpointInfo;
class TDmaBuf//Handicapped Circular Buffer
	{
public:
	TDmaBuf();
	TDmaBuf(TUsbcEndpointInfo* pEndpointInfo,DUsbClientController*  aController);
	~TDmaBuf();
	TInt Construct();
	void SetDriver(DUsbClientController* aDriver);
	TUint8* SetBufferBase(TUint8* aBase);
	TInt BufferSize() const;
	TUint8* BufferBase() const;
	void SetMaxPacketSize(TInt aSize);
	void Flush();
	TBool RxIsCancelled();
	TBool TxIsCancelled();
	// Rx variants
	void RxSetActive();
	void RxSetInActive();
	TBool RxIsActive();
	TBool IsReaderEmpty();
	void ReadXferComplete(TInt aNoBytesRecv,TInt aErrorCode);
	TInt RxCopyDataToClient(DThread* aThread,TAny* aDes, TInt aLength, TUint32& aDestOffset, TBool& aCompleteNow);
	TInt RxCopyDataUntilShortToClient(DThread* aThread,TAny* aDes, TInt aLength, TUint32& aDestOffset, TBool& aCompleteNow);
	TInt RxCopyPacketToClient(DThread* aThread,TAny* aDes, TInt aLength);
	TInt RxGetNextXfer(TPacket& aPacket);
	void RxCancelPacket();
	TBool RxIsEnoughSpace(TInt aSize);
	inline TInt RxBytesAvailable() const;
	TInt NoRxPackets() const;
	TBool ShortPacketExists() const;
	// Tx variants
	void TxSetActive();
	void TxSetInActive();
	TBool TxIsActive();
	TInt TxRemovePacket();
	TInt TxGetNextXfer(TUint8*& aBufferAddr, TInt& aTxLength);
	TInt TxStoreData(DThread* aThread, TAny* aTxPtr, TInt aTxLength, TUint32 aBufferOffset);
	TBool TxIsEnoughSpace(TInt aSize);
	TInt NoTxPackets();
private:
	// Rx only
	void AdvanceTail(TInt aSize);
	inline TInt AdvanceIndex(TInt aIndex) const;
	void RevertTail();
	void AdvanceHead();

private:
	DUsbClientController* iController;
	TInt iPacketArraySize;
	TInt iBufferDirect;
	TInt iNoRxPackets;
	TInt iNoTxPackets;
	TInt iExtractOffset;									// offset into current packet for data read
	TInt iInsertPt;
	TInt iInsertPtLast;
	TInt iRemovePt;
	TInt iHead;
	TInt iTail;
	TInt iTailLast;
	TInt iMaxPacketSize;
	TBool iRxOpCancelled;
	TBool iTxOpCancelled;
	TBool iRxActive;
	TBool iTxActive;
	TPacket* iPacketStore;
protected:
	TInt iRxBytesAvailable;
private:
	TUint8* iBufBasePtr;									// linear address of start of HwChunk
	TInt iBufSz;
	};

GLREF_D DUsbClientController* UsbClientController;

/******************** USB Client Controller ********************************/

class TUsbcDescriptorBase
	{
public:
	virtual ~TUsbcDescriptorBase();
	void SetByte(TUint aPosition, TUint8 aValue);
	void SetWord(TUint aPosition, TUint16 aValue);
	TUint8 Byte(TUint aPosition) const;
	TUint16 Word(TUint aPosition) const;
	virtual void GetDescriptorData(TDes8& aBuffer) const;
	virtual TInt GetDescriptorData(TUint8* aBuffer) const;
	virtual void GetDescriptorDataAppend(TDes8& aBuffer) const;
	virtual const TDes8& DescriptorData() const;
	virtual TDes8& DescriptorData();
	virtual TInt Size() const;
	TUint8 Type() const;
protected:
	TUsbcDescriptorBase();
	void SetBufferPointer(const TDesC8& aDes);
private:
#ifdef USB_SUPPORTS_SET_DESCRIPTOR_REQUEST
	TUint8 iIndex;											// only needed for SET_DESCRIPTOR
#endif
	TPtr8 iBufPtr;
	};


class TUsbcDeviceDescriptor : public TUsbcDescriptorBase
	{
public:
	~TUsbcDeviceDescriptor();
	static TUsbcDeviceDescriptor* NewL(TUint8 aDeviceClass, TUint8 aDeviceSubClass,
									   TUint8 aDeviceProtocol, TUint8 aMaxPacketSize0,
									   TUint16 aVendorId, TUint16 aProductId,
									   TUint16 aDeviceRelease, TUint8 aNumConfigurations);
private:
	TUsbcDeviceDescriptor();
	void ConstructL(TUint8 aDeviceClass, TUint8 aDeviceSubClass, TUint8 aDeviceProtocol,
					TUint8 aMaxPacketSize0, TUint16 aVendorId, TUint16 aProductId,
					TUint16 aDeviceRelease, TUint8 aNumConfigurations);
	TBuf8<KUsbDescSize_Device> iBuf;
	};


class TUsbcConfigDescriptor : public TUsbcDescriptorBase
	{
public:
	~TUsbcConfigDescriptor();
	static TUsbcConfigDescriptor* NewL(TUint8 aConfigurationValue, TBool aSelfPowered, TBool aRemoteWakeup,
									   TUint8 aMaxPower);	// give MaxPower in milliamps!
private:
	TUsbcConfigDescriptor();
	void ConstructL(TUint8 aConfigurationValue, TBool aSelfPowered, TBool aRemoteWakeup, TUint8 aMaxPower);
	TBuf8<KUsbDescSize_Config> iBuf;
	};


class TUsbcInterfaceDescriptor : public TUsbcDescriptorBase
	{
public:
	~TUsbcInterfaceDescriptor();
	static TUsbcInterfaceDescriptor* NewL(TUint8 aInterfaceNumber, TUint8 aAlternateSetting, TInt NumEndpoints,
										  const TUsbcClassInfo& aClassInfo);
private:
	TUsbcInterfaceDescriptor();
	void ConstructL(TUint8 aInterfaceNumber, TUint8 aAlternateSetting, TInt aNumEndpoints,
					const TUsbcClassInfo& aClassInfo);
	TBuf8<KUsbDescSize_Interface> iBuf;
	};


class TUsbcEndpointDescriptor : public TUsbcDescriptorBase
	{
public:
	~TUsbcEndpointDescriptor();
	static TUsbcEndpointDescriptor* NewL(TUint8 aEndpointAddress, const TUsbcEndpointInfo& aEpInfo);
	virtual void GetDescriptorData(TDes8& aBuffer) const;
	virtual TInt GetDescriptorData(TUint8* aBuffer) const;
	virtual void GetDescriptorDataAppend(TDes8& aBuffer) const;
	virtual TInt Size() const;
private:
	TUsbcEndpointDescriptor();
	void ConstructL(TUint8 aEndpointAddress, const TUsbcEndpointInfo& aEpInfo);
	TBuf8<KUsbDescSize_Endpoint> iBuf;
	HBufC8* iExtraBuf;
	};


class TUsbcClassSpecificDescriptor : public TUsbcDescriptorBase
	{
public:
	~TUsbcClassSpecificDescriptor();
	static TUsbcClassSpecificDescriptor* NewL(TUint8 aType, TInt aSize);
private:
	TUsbcClassSpecificDescriptor();
	void ConstructL(TUint8 aType, TInt aSize);
	HBufC8* iBuf;
	};


class TUsbcStringDescriptorBase
	{
public:
	virtual ~TUsbcStringDescriptorBase();
	TUint16 Word(TUint aPosition) const;
	void GetDescriptorData(TDes16& aBuffer) const;
	TInt GetDescriptorData(TUint8* aBuffer) const;
	const TDes16& StringData() const;
	TDes16& StringData();
	TInt Size() const;
protected:
	TUsbcStringDescriptorBase();
	TBuf8<2> iSBuf;
	TPtr16 iBufPtr;
private:
//	TUint8 iIndex;											// not needed in DescriptorPool: position == index
	};


class TUsbcStringDescriptor : public TUsbcStringDescriptorBase
	{
public:
	~TUsbcStringDescriptor();
	static TUsbcStringDescriptor* NewL(const TDesC16& aString);
private:
	TUsbcStringDescriptor();								// use static NewL
	void ConstructL(const TDesC16& aString);
	HBufC16* iBuf;
	};


// Currently we support only one language, and thus there's no need to provide
// a LangId string descriptor with more than one array element.
class TUsbcLangIdDescriptor : public TUsbcStringDescriptorBase
	{
public:
	~TUsbcLangIdDescriptor();
	static TUsbcLangIdDescriptor* NewL(TUint16 aLangId);
private:
	TUsbcLangIdDescriptor();								// use static NewL
	void ConstructL(TUint16 aLangId);
	TBuf16<1> iBuf;
	};


class TUsbcDescriptorPool
	{
public:
	TUsbcDescriptorPool();
	~TUsbcDescriptorPool();
	void Init(TUsbcDeviceDescriptor* aDeviceDesc, TUsbcConfigDescriptor* aConfigDesc,
			  TUsbcLangIdDescriptor* aLangId, TUsbcStringDescriptor* aManufacturer,
			  TUsbcStringDescriptor* aProduct, TUsbcStringDescriptor* aSerialNum,
			  TUsbcStringDescriptor* aConfig);
	// Descriptors
	TInt FindDescriptor(TUint8 aType, TUint8 aIndex, TUint16 aLangid, TInt& aSize, TUint8* aBuffer) const;
	void InsertDescriptor(TUsbcDescriptorBase* aDesc);
	void DeleteIfcDescriptor(TInt aNumber, TInt aSetting = 0);

	// The TC in many of the following functions stands for 'ThreadCopy' because that's what happens there.
	TInt GetDeviceDescriptorTC(DThread* aThread, TDes8& aBuffer) const;
	TInt SetDeviceDescriptorTC(DThread* aThread, const TDes8& aBuffer);
	TInt GetConfigurationDescriptorTC(DThread* aThread, TDes8& aBuffer) const;
	TInt SetConfigurationDescriptorTC(DThread* aThread, const TDes8& aBuffer);
	TInt GetInterfaceDescriptorTC(DThread* aThread, TDes8& aBuffer, TInt aInterface, TInt aSetting) const;
	TInt SetInterfaceDescriptor(const TDes8& aBuffer, TInt aInterface, TInt aSetting);
	TInt GetEndpointDescriptorTC(DThread* aThread, TDes8& aBuffer, TInt aInterface, TInt aSetting,
								 TUint8 aEndpointAddress) const;
	TInt SetEndpointDescriptorTC(DThread* aThread, const TDes8& aBuffer, TInt aInterface, TInt aSetting,
								 TUint8 aEndpointAddress);
	TInt GetEndpointDescriptorSize(TInt aInterface, TInt aSetting, TUint8 aEndpointAddress, TInt& aSize) const;
	TInt GetCSInterfaceDescriptorTC(DThread* aThread, TDes8& aBuffer, TInt aInterface, TInt aSetting) const;
	TInt SetCSInterfaceDescriptorTC(DThread* aThread, const TDes8& aBuffer, TInt aInterface, TInt aSetting,
									TInt aSize);
	TInt GetCSInterfaceDescriptorSize(TInt aInterface, TInt aSetting, TInt& aSize) const;
	TInt GetCSEndpointDescriptorTC(DThread* aThread, TDes8& aBuffer, TInt aInterface, TInt aSetting,
								   TUint8 aEndpointAddress) const;
	TInt SetCSEndpointDescriptorTC(DThread* aThread, const TDes8& aBuffer, TInt aInterface, TInt aSetting,
								   TUint8 aEndpointAddress, TInt aSize);
	TInt GetCSEndpointDescriptorSize(TInt aInterface, TInt aSetting, TUint8 aEndpointAddress, TInt& aSize) const;

	// String descriptors
	void SetIfcStringDescriptor(TUsbcStringDescriptor* aDesc, TInt aNumber, TInt aSetting = 0);
//	TUint StringDescriptorSize(TInt aIndex) const;
	TInt GetManufacturerStringDescriptorTC(DThread* aThread, TDes16& aString) const;
	TInt SetManufacturerStringDescriptorTC(DThread* aThread, const TDes16& aString);
	TInt GetProductStringDescriptorTC(DThread* aThread, TDes16& aString) const;
	TInt SetProductStringDescriptorTC(DThread* aThread, const TDes16& aString);
	TInt GetSerialNumberStringDescriptorTC(DThread* aThread, TDes16& aString) const;
	TInt SetSerialNumberStringDescriptorTC(DThread* aThread, const TDes16& aString);
	TInt GetConfigurationStringDescriptorTC(DThread* aThread, TDes16& aString) const;
	TInt SetConfigurationStringDescriptorTC(DThread* aThread, const TDes16& aString);
private:
	void InsertDevDesc(TUsbcDescriptorBase* aDesc);
	void InsertConfigDesc(TUsbcDescriptorBase* aDesc);
	void InsertIfcDesc(TUsbcDescriptorBase* aDesc);
	void InsertEpDesc(TUsbcDescriptorBase* aDesc);
	TInt FindIfcDescriptor(TInt aIfcNumber, TInt aIfcSetting) const;
	TInt FindEpDescriptor(TInt aIfcNumber, TInt aIfcSetting, TUint8 aEpAddress) const;
	void DeleteDescriptors(TInt aIndex, TInt aCount = 1);
	void DeleteString(TInt aIndex);
	void UpdateIfcNumbers(TInt aNumber);
	void UpdateIfcStringIndexes(TInt aStringIndex);
	void GetDeviceDescriptor(TDes8& aBuffer) const;
	TInt GetDeviceDescriptor(TUint8* aBuffer) const;
	void GetConfigDescriptor(TDes8& aBuffer) const;
	TInt GetConfigDescriptor(TUint8* aBuffer) const;
	void GetStringDescriptor(TInt aIndex, TDes16& aBuffer) const;
	TInt GetStringDescriptor(TInt aIndex, TUint8* aBuffer) const;
	TInt GetDeviceStringDescriptorTC(DThread* aThread, TDes16& aString, TInt aIndex) const;
	TInt SetDeviceStringDescriptorTC(DThread* aThread, const TDes16& aString, TInt aIndex);
	TInt ExchangeStringDescriptor(TInt aIndex, const TUsbcStringDescriptor* aDesc);
private:
	// Data members
	RPointerArray<TUsbcDescriptorBase> iDescriptors;
	RPointerArray<TUsbcStringDescriptorBase> iStrings;
	TInt iIfcIdx;
	};

//
// The following classes are mostly "structs with attitude"
//
class TUsbcLogicalEndpoint;
// This models a physical (real) endpoint on the UDC
class TUsbcPhysicalEndpoint
	{
public:
	TUsbcPhysicalEndpoint();
	~TUsbcPhysicalEndpoint();
	TBool EndpointSuitable(const TUsbcEndpointInfo* aEpInfo, TInt aIfcNumber) const;
	TInt TypeAvailable(TUint aType) const;
	TInt DirAvailable(TUint aDir) const;
public:
	TUsbcEndpointCaps iCaps;
	TUint8 iEndpointAddr;									// USB address: 0x00, 0x80, 0x01, 0x81, etc.
	const TUint8* iIfcNumber;								// ptr to ifc # this endpoint has been assigned to
	const TUsbcLogicalEndpoint* iLEndpoint;
	TBool iSettingReserve;									// only used when searching for available endpoints
	TBool iHalt;				// true if endpoint is halted (i.e. issues STALL handshakes), false otherwise
	};

class TUsbcInterface;
// This is a logical endpoint, as used by our device configuration model
class TUsbcLogicalEndpoint
	{
public:
	TUsbcLogicalEndpoint(TUint aEndpointNum, const TUsbcEndpointInfo& aInfo,
						 TUsbcInterface* aInterface, TUsbcPhysicalEndpoint* aPEndpoint);
	~TUsbcLogicalEndpoint();
public:
	const TInt iLEndpointNum;								// virtual endpoint number
	TUsbcEndpointInfo iInfo;
	const TUsbcInterface* iInterface;						// back pointer
	TUsbcPhysicalEndpoint* const iPEndpoint;
	};

class TUsbcInterfaceSet;
// This is one 'alternate setting' of an interface
class TUsbcInterface
	{
public:
	TUsbcInterface(TUsbcInterfaceSet* aIfcSet, TUint8 aSetting);
	~TUsbcInterface();
public:
	RPointerArray<TUsbcLogicalEndpoint> iEndpoints;
	TUsbcInterfaceSet* const iInterfaceSet;					// back pointer
	const TUint8 iSettingCode;								// bAlternateSetting (zero-based)
	};

// This is an interface (containing 1 or more alternate settings TUsbcInterface)
class TUsbcInterfaceSet
	{
public:
	TUsbcInterfaceSet(const CBase* aClientId, TUint8 aIfcNum);
	~TUsbcInterfaceSet();
	inline const TUsbcInterface* CurrentInterface() const;
	inline TUsbcInterface* CurrentInterface();
public:
	RPointerArray<TUsbcInterface> iInterfaces;
	const CBase* const iClientId;
	TUint8 iInterfaceNumber;								// bInterfaceNumber (zero-based)
	TUint8 iCurrentInterface;								// bAlternateSetting (zero-based)
	};

// This is one configuration of the USB device
class TUsbcConfiguration
	{
public:
	TUsbcConfiguration(TUint8 aConfigVal);
	~TUsbcConfiguration();
public:
	RPointerArray<TUsbcInterfaceSet> iInterfaceSets;
	const TUint8 iConfigValue;
	};

// a SETUP packet
class TUsbcSetup
	{
public:
	TUint8 iRequestType;									// bmRequestType
	TUint8 iRequest;										// bRequest
	TUint16 iValue;											// wValue
	TUint16 iIndex;											// wIndex
	TUint16 iLength;										// wLength
	};

class TUsbcEndpoint;
class TUsbcAlternateSettingList
	{
public:
	TUsbcAlternateSettingList();
	~TUsbcAlternateSettingList();
public:
	TUsbcAlternateSettingList* iNext;
	TInt iNumberOfEndpoints;
	TUint iSetting;
	TUsbcEndpoint* iEndpoint[KMaxEndpointsPerClient+1];
	};

class DUsbClientController : public CBase
	{
public:
	// Platform Independent Layer
	IMPORT_C TBool InitialiseBaseClassL(TUsbcDeviceDescriptor* aDeviceDesc,
										TUsbcConfigDescriptor* aConfigDesc,
										TUsbcLangIdDescriptor* aLangId,
										TUsbcStringDescriptor* aManufacturer,
										TUsbcStringDescriptor* aProduct,
										TUsbcStringDescriptor* aSerialNum,
										TUsbcStringDescriptor* aConfig);
	virtual ~DUsbClientController();
	IMPORT_C static DUsbClientController* UsbcControllerPointer();
	IMPORT_C void EndpointCaps(TDes8 &aCapsBuf) const;
	IMPORT_C void DeviceCaps(TDes8 &aCapsBuf) const;
	IMPORT_C TInt SetInterface(const CBase* aClientId, DThread* aThread, TInt aInterfaceNumber,
							   TUsbcClassInfo& aClass, const TDesC* aString, TInt aTotalEndpointsUsed,
							   const TUsbcEndpointInfo aEndpointData[]);
	IMPORT_C TInt ReleaseInterface(const CBase* aClientId, TInt aInterfaceNumber);
	IMPORT_C void ReEnumerate();
	IMPORT_C TInt PowerUpUdc();
	IMPORT_C TInt UsbConnect();
	IMPORT_C TInt UsbDisconnect();
	IMPORT_C TInt RegisterForStatusChange(TUsbcStatusCallBack& aCallBack);
	IMPORT_C TInt DeRegisterForStatusChange(const CBase* aClientId);
	IMPORT_C TInt RegisterForEndpointStatusChange(TUsbcEndpointStatusCallBack& aCallBack);
	IMPORT_C TInt DeRegisterForEndpointStatusChange(const CBase* aClientId);
	IMPORT_C TInt GetInterfaceNumber(const CBase* aClientId, TInt& aInterfaceNumber) const;
	IMPORT_C TInt DeRegisterClient(const CBase* aClientId);
	IMPORT_C TInt Ep0PacketSize() const;
	IMPORT_C TInt Ep0Stall(const CBase* aClientId);
	IMPORT_C void SendEp0StatusPacket(const CBase* aClientId);
	IMPORT_C TUsbcDeviceState GetDeviceStatus() const;
	IMPORT_C TEndpointState GetEndpointStatus(const CBase* aClientId, TInt aEndpointNum) const;
	IMPORT_C TInt SetupReadPacket(TUsbcRequestCallBack& aCallBack);
	IMPORT_C TInt SetupWriteBuffer(TUsbcRequestCallBack& aCallBack);
	IMPORT_C void CancelReadPacket(const CBase* aClientId, TInt aEndpointNum);
	IMPORT_C void CancelWritePacket(const CBase* aClientId, TInt aEndpointNum);
	IMPORT_C TInt HaltEndpoint(const CBase* aClientId, TInt aEndpointNum);
	IMPORT_C TInt ClearHaltEndpoint(const CBase* aClientId, TInt aEndpointNum);
	IMPORT_C TInt SetDeviceControl(const CBase* aClientId);
	IMPORT_C TInt ReleaseDeviceControl();
	IMPORT_C TUint EndpointZeroMaxPacketSizes() const;
	IMPORT_C TInt SetEndpointZeroMaxPacketSize(TInt aMaxPacketSize);
	IMPORT_C TInt GetDeviceDescriptor(DThread* aThread, TDes8& aDeviceDescriptor);
	IMPORT_C TInt SetDeviceDescriptor(DThread* aThread, const TDes8& aDeviceDescriptor);
	IMPORT_C void GetDeviceDescriptorSize(DThread* aThread, TDes8& aSize);
	IMPORT_C TInt GetConfigurationDescriptor(DThread* aThread, TDes8& aConfigurationDescriptor);
	IMPORT_C TInt SetConfigurationDescriptor(DThread* aThread, const TDes8& aConfigurationDescriptor);
	IMPORT_C void GetConfigurationDescriptorSize(DThread* aThread, TDes8& aSize);
	IMPORT_C TInt GetInterfaceDescriptor(DThread* aThread, const CBase* aClientId, TInt aSettingNumber,
										 TDes8& aInterfaceDescriptor);
	IMPORT_C TInt SetInterfaceDescriptor(DThread* aThread, const CBase* aClientId, TInt aSettingNumber,
										 const TDes8& aInterfaceDescriptor);
	IMPORT_C TInt GetInterfaceDescriptorSize(DThread* aThread, const CBase* aClientId, TInt aSettingNumber,
											 TDes8& aSize);
	IMPORT_C TInt GetEndpointDescriptor(DThread* aThread, const CBase* aClientId, TInt aSettingNumber,
										TInt aEndpointNumber, TDes8& aEndpointDescriptor);
	IMPORT_C TInt SetEndpointDescriptor(DThread* aThread, const CBase* aClientId, TInt aSettingNumber,
										TInt aEndpointNumber, const TDes8& aEndpointDescriptor);
	IMPORT_C TInt GetEndpointDescriptorSize(DThread* aThread, const CBase* aClientId, TInt aSettingNumber,
											TInt aEndpointNumber, TDes8& aSize);
	IMPORT_C TInt GetCSInterfaceDescriptorBlock(DThread* aThread, const CBase* aClientId, TInt aSettingNumber,
												TDes8& aInterfaceDescriptor);
	IMPORT_C TInt SetCSInterfaceDescriptorBlock(DThread* aThread, const CBase* aClientId, TInt aSettingNumber,
												const TDes8& aInterfaceDescriptor, TInt aSize);
	IMPORT_C TInt GetCSInterfaceDescriptorBlockSize(DThread* aThread, const CBase* aClientId,
													TInt aSettingNumber, TDes8& aSize);
	IMPORT_C TInt GetCSEndpointDescriptorBlock(DThread* aThread, const CBase* aClientId, TInt aSettingNumber,
											   TInt aEndpointNumber, TDes8& aEndpointDescriptor);
	IMPORT_C TInt SetCSEndpointDescriptorBlock(DThread* aThread, const CBase* aClientId, TInt aSettingNumber,
											   TInt aEndpointNumber, const TDes8& aEndpointDescriptor,
											   TInt aSize);
	IMPORT_C TInt GetCSEndpointDescriptorBlockSize(DThread* aThread, const CBase* aClientId, TInt aSettingNumber,
												   TInt aEndpointNumber, TDes8& aSize);
	IMPORT_C TInt GetManufacturerStringDescriptor(DThread* aThread, TDes16& aString);
	IMPORT_C TInt SetManufacturerStringDescriptor(DThread* aThread, const TDes16& aString);
	IMPORT_C TInt GetProductStringDescriptor(DThread* aThread, TDes16& aString);
	IMPORT_C TInt SetProductStringDescriptor(DThread* aThread, const TDes16& aString);
	IMPORT_C TInt GetSerialNumberStringDescriptor(DThread* aThread, TDes16& aString);
	IMPORT_C TInt SetSerialNumberStringDescriptor(DThread* aThread, const TDes16& aString);
	IMPORT_C TInt GetConfigurationStringDescriptor(DThread* aThread, TDes16& aString);
	IMPORT_C TInt SetConfigurationStringDescriptor(DThread* aThread, const TDes16& aString);

	IMPORT_C void Stop(TUsbcStopMode aStopMode);
	static DUsbClientController* UsbClientController;
	//
	IMPORT_C virtual TInt SignalRemoteWakeup()=0;
	IMPORT_C virtual void DumpRegisters()=0;


protected:
	// Functions and data members provided by Platform Independent Layer, called by Platform Specific Layer
	DUsbClientController();
	TInt DeviceEventNotification(TUsbcDeviceEvent anEvent);
	TInt EndpointRequestComplete(TInt aRealEndpoint, TInt aCount, TInt anErrorStatus);
	TInt MoveToAddressState();
	void SetCurrent(TInt aCurrent);
	TUsbcEp0State EnquireEp0NextState(const TUint8* aSetupBuf) const;
	TBool iEp0ReceivedNonStdRequest;						// info can be used by the PSL before sending ZLPs
	TBool iRmWakeupStatus_Enabled;							// rmw currently enabled? (set by either PIL or PSL)
private:
	// Platform Specific Layer
	virtual TInt SetDeviceAddress(TInt anAddress) =0;
	virtual TInt ConfigureEndpoint(TInt aRealEndpoint, const TUsbcEndpointInfo& aEndpointInfo) =0;
	virtual TInt DeConfigureEndpoint(TInt aRealEndpoint) =0;
	virtual TInt SetupEndpointRead(TInt aRealEndpoint, TUint8* aBuffer, TInt aLength) =0;
	virtual TInt SetupEndpointWrite(TInt aRealEndpoint, const TUint8* aBuffer, TInt aLength,
									TBool aZlpReqd = EFalse) =0;
	virtual TInt CancelEndpointRead(TInt aRealEndpoint) =0;
	virtual TInt CancelEndpointWrite(TInt aRealEndpoint) =0;
	virtual TInt SendEp0ZeroByteStatusPacket() =0;
	virtual TInt StallEndpoint(TInt aRealEndpoint) =0;
	virtual TInt ClearStallEndpoint(TInt aRealEndpoint) =0;
	virtual TBool EndpointStallStatus(TInt aRealEndpoint) const =0;
	virtual TInt EndpointErrorStatus(TInt aRealEndpoint) const =0;
	virtual TInt ResetDataToggle(TInt aRealEndpoint) =0;
	virtual TInt SynchFrameNumber(TInt aRealEndpoint) const =0;
	virtual TInt SetSynchFrameNumber(TInt aRealEndpoint, TInt aFrameNumber) =0;
	virtual TInt StartUdc() =0;
	virtual TInt StopUdc() =0;
	virtual TInt UdcConnect() =0;
	virtual TInt UdcDisconnect() =0;
	virtual TBool UsbConnectionStatus() const  =0;
	virtual TBool UsbPowerStatus() const =0;
	virtual TBool DeviceSelfPowered() const =0;				// _currently_ selfpowered, not capable of it!
	virtual const TUsbcEndpointCaps* DeviceEndpointCaps() const =0;
	virtual TInt DeviceTotalEndpoints() const =0;
	virtual TBool SoftConnectCaps() const =0;
	virtual TBool DeviceStateChangeCaps() const =0;
	virtual TInt Suspend() =0;
	virtual TInt Resume() =0;
	virtual TInt Reset() =0;
	virtual void Ep0ReadSetupPktProceed() =0;
	virtual void Ep0ReceiveProceed() =0;
private:
	// Private member functions used by controller itself
	TBool CheckEpAvailability(TInt aEndpointsUsed, const TUsbcEndpointInfo aEndpointData[], TInt aIfcNumber) const;
	TUsbcInterface* CreateInterface(const CBase* aClientId, TInt aIfc);
	TInt CreateEndpoints(TUsbcInterface* aIfc, TInt aEndpointsUsed, const TUsbcEndpointInfo aEndpointData[]);
	TInt SetupIfcDescriptor(TUsbcInterface* aIfc, TUsbcClassInfo& aClass, DThread* aThread, const TDesC* aString,
							const TUsbcEndpointInfo aEndpointData[]);
	TInt FindRealEndpoint(const TUsbcInterface* aIfc, TInt aEndpointNum) const;
	TInt FindRealEndpoint(const CBase* aClientId, TInt aEndpointNum) const;
	TInt FindRealEndpoint(TInt aIfcSet, TInt aSettingNumber, TInt aEndpointNum) const;
	TInt ClientId2InterfaceNumber(const CBase* aClientId) const;
	TUsbcInterfaceSet* ClientId2InterfacePointer(const CBase* aClientId);
	const CBase* InterfaceNumber2ClientId(TInt aIfcSet);
	const CBase* InterfaceNumber2ClientId(TInt aIfcSet) const;
	TUsbcInterfaceSet* InterfaceNumber2InterfacePointer(TInt aIfcSet);
	const TUsbcInterfaceSet* InterfaceNumber2InterfacePointer(TInt aIfcSet) const;
	inline const CBase* PEndpoint2ClientId(TInt aRealEndpoint) const;
	inline TInt PEndpoint2LEndpoint(TInt aRealEndpoint) const;
	void ActivateHardwareController();
	void DeActivateHardwareController();
	void DeleteInterfaceSet(TInt aIfcSet);
	void DeleteInterface(TInt aIfcSet, TInt aIfc);
	void CancelTransferRequests(TInt aRealEndpoint);
	void DeleteRequestCallback(const CBase* aClientId, TInt aEndpointNum, TTransferDirection aTransferDir);
	void DeleteRequestCallbacks(const CBase* aClientId);
	void StatusNotify(TUsbcDeviceState aState, const CBase* aClientId=NULL);
	void EpStatusNotify(TInt aRealEndpoint);
	void ProcessDataTransferDone(TUsbcRequestCallBack& aRcb, TInt aCount, TInt aErrorStatus);
	void NextDeviceState(TUsbcDeviceState aNextState);
	TInt ProcessSuspendEvent();
	TInt ProcessSuspendEventProceed();
	TInt ProcessResumeEvent();
	TInt ProcessResetEvent();
	TInt ProcessEp0ReceiveDone(TInt aCount, TInt aErrorStatus);
	TInt ProcessEp0TransmitDone(TInt aCount, TInt aErrorStatus);
	TInt ProcessEp0SetupReceived(TInt aCount, TInt aErrorStatus);
	TInt ProcessEp0DataReceived(TInt aCount, TInt aErrorStatus);
	TInt ProcessGetDeviceStatus(const TUsbcSetup& aPacket);
	TInt ProcessGetInterfaceStatus(const TUsbcSetup& aPacket);
	TInt ProcessGetEndpointStatus(const TUsbcSetup& aPacket);
	TInt ProcessSetClearDevFeature(const TUsbcSetup& aPacket);
	TInt ProcessSetClearIfcFeature(const TUsbcSetup& aPacket);
	TInt ProcessSetClearEpFeature(const TUsbcSetup& aPacket);
	TInt ProcessSetAddress(const TUsbcSetup& aPacket);
	TInt ProcessGetDescriptor(const TUsbcSetup& aPacket);
	TInt ProcessSetDescriptor(const TUsbcSetup& aPacket);
	TInt ProcessGetConfiguration(const TUsbcSetup& aPacket);
	TInt ProcessSetConfiguration(const TUsbcSetup& aPacket);
	TInt ProcessGetInterface(const TUsbcSetup& aPacket);
	TInt ProcessSetInterface(const TUsbcSetup& aPacket);
	TInt ProcessSynchFrame(const TUsbcSetup& aPacket);
	void ProceedSetDescriptor();
	void SetClearHaltFeature(TInt aRealEndpoint, TUint8 aRequest);
	TInt ClearHaltFeature(TInt aRealEndpoint);
	void ChangeConfiguration(TUint16 aValue);
	void InterfaceSetup(TUsbcInterface* aIfc);
	void InterfaceSetTeardown(TUsbcInterfaceSet* aIfc);
	void ChangeInterface(TUsbcInterface* aIfc);
	TInt DoForEveryEndpointInUse(TInt (DUsbClientController::*aFunction)(TInt), TInt& aCount);
	inline const TUsbcConfiguration* CurrentConfig() const;
	inline TUsbcConfiguration* CurrentConfig();
	inline TBool InterfaceExists(TInt aNumber) const;
	inline TBool EndpointExists(TUint aAddress) const;
	inline void Buffer2Setup(const TAny* aBuf, TUsbcSetup& aSetup) const;
	inline TUint EpIdx2Addr(TUint aRealEndpoint) const;
	inline TUint EpAddr2Idx(TUint aAddress) const;
	inline void SetEp0DataOutVars(const TUsbcSetup& aPacket, const CBase* aClientId = NULL);
	inline void ResetEp0DataOutVars();
	inline TBool IsInTheStatusList(const TUsbcStatusCallBack& aCallBack);
	inline TBool IsInTheEpStatusList(const TUsbcEndpointStatusCallBack& aCallBack);
	inline TBool IsInTheRequestList(const TUsbcRequestCallBack& aCallBack);
	static void ReconnectTimerCallBack(TAny *aPtr, TInt aDelay);
	static void CableStatusTimerCallBack(TAny *aPtr, TInt aDelay);
	static TInt CableStatusTimerSetDfc(TAny* aPtr);
private:
	// Private data members of controller
	TInt iDeviceTotalEndpoints;								// number of endpoints reported by PSL
	TInt iDeviceUsableEndpoints;							// number of endpoints reported to LDD
	TUsbcDeviceState iDeviceState;							// states as of USB spec chapter 9.1
	TUsbcDeviceState iDeviceStateB4Suspend;					// state before entering suspend state
	TBool iSelfPowered;										// true if device is capable of beeing self-powered
	TBool iRemoteWakeup;									// true if device is capable of signalling rmwakeup
	TBool iTrackDeviceState;								// true if we should track the device state in s/w
	TBool iHardwareActivated;								// true if controller silicon is in operating state
	TUsbcSetup iSetup;										// storage for a setup packet during its DATA_OUT
	TInt iEp0MaxPacketSize;									// currently configured max packet size for Ep0
	const CBase* iEp0ClientId;								// see comment at the begin of ps_usbc.cpp
	TUint16 iEp0DataReceived;								// indicates how many bytes have already been received
	TBool iEp0DataReceiving;								// true if ep0's in DATA_OUT stage
	TBool iEp0WritePending;									// true if a write on ep0 has been set up
	TBool iEp0ClientDataTransmitting;						// true if ep0's in DATA_IN on behalf of a client
	const CBase* iEp0DeviceControl;							// Device Ep0 requests are delivered to this LDD
	TUsbcDescriptorPool iDescriptors;						// the descriptors as of USB spec chapter 9.5
	TUint8 iCurrentConfig;									// bConfigurationValue of current Config (1-based!)
	RPointerArray<TUsbcConfiguration> iConfigs;				// the root of the modelled USB device
	TUsbcPhysicalEndpoint iRealEndpoints[KUsbcMaxEndpoints + 2]; // array will be filled once at startup
	TUint8 iEp0_RxBuf[KUsbcBufSzControl];					// ep0 incoming (rx) data (one packet) is placed here
	TUint8 iEp0_TxBuf[KUsbcBufSz_Ep0Tx];					// ep0 outgoing (tx) data is placed here
#ifdef USB_SUPPORTS_SET_DESCRIPTOR_REQUEST
	TUint8 iEp0_RxCollectionBuf[KUsbcBufSz_Ep0Rx];			//
#endif
	TInt iEp0_RxExtraCount;
	TInt iEp0_RxExtraError;
	TBool iEp0_RxExtraData;
	TSglQue<TUsbcStatusCallBack> iStatusCallbacks;			// list of device state notification requests
	TSglQue<TUsbcEndpointStatusCallBack> iEpStatusCallbacks; // list of endpoint state notification requests
	TSglQue<TUsbcRequestCallBack> iRequestCallbacks;		// list of data transfer requests
	TTickLink iReconnectTimer;								// implements USB re-enumeration delay
	TTickLink iCableStatusTimer;							// implements USB cable status detection delay
	TDfc iCableStatusTimerSetDfc;							// 
	};

/*********************Logical Driver********************************/

class DLddUsbcChannel;			// forward declaration
class DUsbcPowerHandler : public DPowerHandler
	{
public:
	DUsbcPowerHandler(DLddUsbcChannel *aLdd);
	virtual TInt DoPowerOn();
	virtual void DoPowerStandby();
	virtual void DoPowerEmergencyStandby();
public:
	DLddUsbcChannel *iLdd;
	};

class TUsbcDeviceStatusQueue;
class DLddUsbcChannel : public DLogicalChannel
      {
public:
      DLddUsbcChannel(DLogicalDevice* aLogicalDevice);
	  ~DLddUsbcChannel();

	  virtual void DoPowerUp();
	  virtual void DoPowerDown();
	  virtual void DoEmergencyPowerDown();
	  inline void SetCurrentConsumptionInMilliAmps(TInt aValue);
//protected:
//override pure virtual
      virtual void DoCancel(TInt aReqNo);
      virtual void DoRequest(TInt aReqNo,TAny* a1,TAny* a2);

      virtual void DoCreateL(TInt aUnit,CBase* aPdd,const TDesC* anInfo,const TVersion& aVer);
      virtual TInt DoControl(TInt aFunction,TAny* a1,TAny* a2);
	  TInt DoRxComplete(TUsbcEndpoint *aTUsbcEndpoint, TInt aEndpoint);
	  TInt DoTxComplete(TUsbcEndpoint *aTUsbcEndpoint,TInt aEndpoint, TInt anError);
	  DThread* Thread(){return iThread;};
private:
	  TInt SetInterface(TInt aInterfaceNumber,TUsbcInterfaceInfo *pInterfaceInfo);
	  void DestroyEndpoints(TUsbcAlternateSettingList* aAlternateSettingListRec);
	  void DestroyAllInterfaces();
	  void DestroyInterface(TUint aInterface);
	  void DestroyEp0();
	  inline void AddEmergencyDfc() { Kern::Add(iEmergencyCompleteDfc); }
	  inline TBool ValidEndpoint(TInt aEndpoint);
	  TInt DoEmergencyComplete();
	  void SetStatusChangeNotification();
	  void SetEndpointStatusChangeNotification();
	  void ReadDes8(const TAny *aPtr,TDes8 &aDes);
	  TInt SetupEp0();
	  TUint8* ReAllocate(TInt aBuffersize);
	  DPlatChunkHw* AllocateL(TInt aBuffersize);
	  void CancelNotifyEndpointStatus();
	  static TInt StatusChangeCallBack(TAny *aDLddUsbcChannel);
	  static TInt EndpointStatusChangeCallBack(TAny *aDLddUsbcChannel);
	  static TInt EmergencyCompleteDfc(TAny* aDLddUsbcChannel);
	  void DeConfigure();
	  TInt SelectAlternateSetting(TUint32 aAlternateSetting);
	  TInt ProcessAlternateSetting(TUint32 alternateSetting);
	  TInt ProcessDeviceState(TUint32 deviceState);
	  void ResetInterface();
	  void RebaseInterfaceMemory(TUsbcAlternateSettingList* aAlternateSettingListRec, TUint8* aBase);
	  void CheckEp0ConfigSize();
	  void StartEpReads();
	  TInt DoStatusChangeCallBack();
private:

//	  TUsbconfig iConfig;
	  DUsbClientController*  iController;
	  DUsbcPowerHandler* iPowerHandler;
	  TBool	iValidInterface;
	  TUsbcAlternateSettingList* iAlternateSettingList;
	  TUsbcEndpoint* iEndpoint[KMaxEndpointsPerClient+1]; // include ep0
	  TRequestStatus *iNotifyStatus;
	  TAny* iStatusChangePtr;
	  TBool	iStatusChangeNotification;
	  TUsbcStatusCallBack  iStatusCallBackInfo;
	  TRequestStatus *iRenumerateStatus;
	  TRequestStatus *iEndpointNotifyStatus;
	  TAny* iEndpointStatusChangePtr;
	  TUsbcEndpointStatusCallBack iEndpointStatusCallBackInfo;
	  TDfc  iEmergencyCompleteDfc;
	  TUint8* iBufferBase;
	  TInt iBufferSize;
	  TUint8* iBufferBaseEp0;
	  TInt iBufferSizeEp0;
	  TInt iNumberOfEndpoints;
	  DPlatChunkHw* iHwChunk;
	  DPlatChunkHw* iHwChunkEp0;
	  TInt iDeviceState;
	  TBool iOwnsDeviceControl;
	  TUint iAlternateSetting;
	  TUsbcDeviceStatusQueue* iStatusFifo;
	};

class TUsbcEndpoint
	{
public:
	TUsbcEndpoint();
	TUsbcEndpoint(DLddUsbcChannel* aLDD, DUsbClientController*  aController,
				  TUsbcEndpointInfo* pEndpointInfo,TInt aEndpointNumber);
//	TUsbcEndpoint(TUsbcEndpointInfo* pEndpointInfo);
	~TUsbcEndpoint();
	TInt Construct();
	TInt TryToStartRead();
	TInt ContinueWrite();
	TInt TryToStartWrite(TEndpointTransferInfo* pTfr);
	TInt CopyToClient(DThread* aThread);
	TInt CopyToClient(DThread* aThread, TBool& aCompleteNow);
//	TInt CopyMaxToClient(DThread* aThread);
	TInt SetMaxPacketSize(TInt aSize);
	void CancelTransfer(DThread *aThread);
	void AbortTransfer();
	inline TUsbcEndpointInfo* EndpointInfo();
	inline TInt RxBytesAvailable() const;
	inline TInt BufferSize() const;
	inline TUint8* SetBufferBase(TUint8* aBase);
	inline void SetTransferInfo(TEndpointTransferInfo* aTransferInfo);
	inline void ResetTransferInfo();
	inline void SetChannel(DLddUsbcChannel* aChannel);
	inline void SetEndpointNumber(TInt aEndpointNumber);
	inline void SetClientReadPending(TBool aVal);
	inline void SetClientWritePending(TBool aVal);
	inline TBool ClientWritePending();
	inline TBool ClientReadPending();

public:
	TDmaBuf *iDmaBuffers;

private:
  	inline void AddTxDfc() { Kern::Add(iTxCompleteDfc); }
  	inline void AddRxDfc() { Kern::Add(iRxCompleteDfc); }
	inline void AddContinueWriteDfc(){ Kern::Add(iContinueWriteDfc); }
	static TInt RequestCallBack(TAny* aTUsbcEndpoint);
  	static TInt TxCompleteDfc(TAny* aTUsbcEndpoint);
  	static TInt RxCompleteDfc(TAny* aTUsbcEndpoint);
  	static TInt ContinueWriteDfc(TAny* aTUsbcEndpoint);
	TInt EndpointComplete();
	TInt DoEndpointTxComplete();
	TInt DoEndpointRxComplete();
private:
    DUsbClientController*  iController;
	TDfc iTxCompleteDfc;
	TDfc iRxCompleteDfc;
	TDfc iContinueWriteDfc;
	TUsbcEndpointInfo iEndpointInfo;
	TEndpointTransferInfo iTransferInfo;
	TBool iClientReadPending;
	TBool iClientWritePending;
	TInt iEndpointNumber;
	DLddUsbcChannel* iLdd;
	TInt iError;
	TUsbcRequestCallBack* iRequestCallBackInfo;
	TUint32 iBytesTransferred;
	};

class TUsbcDeviceStatusQueue
	{
public:
	TUsbcDeviceStatusQueue();
	void AddStatusToQueue(TUint32 aDeviceStatus);
	TInt GetDeviceQueuedStatus(TUint32& aDeviceStatus);
private:
	TUint32 iDeviceStatusQueue[KUsbDeviceStatusQueueDepth];
	TInt iStatusQueueHead;
	};

#include <k32usbc.inl>

#endif	// __K32USBC_H__
