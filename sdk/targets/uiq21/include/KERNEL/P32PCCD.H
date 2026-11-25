// P32PCCD.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//


#ifndef __P32PCCD_H__
#define __P32PCCD_H__
#include <p32std.h>

//
// PC Card Events
//
const TInt KMaxPccdEvents=7;
const TInt KMaxPccdEventsMask=0x0000007F;
const TInt KTotalPccdEventQueues=(KMaxPccdEvents-KMaxPEvents+1);
//
const TUint KPccdEvEmergencyPwrDown=KPEventPwrDownEmergency;
const TUint KPccdEvPwrDown=KPEventPwrDownNormal;
const TUint KPccdEvPwrUp=KPEventPwrUp;
const TUint KPccdEvMediaChange=KPEventMediaChange;
const TUint KPccdEvIReq=0x00000010;
const TUint KPccdEvIndChange=0x00000020;
const TUint KPccdEvRdyChange=0x00000040;
const TUint KPccdEvAll=0x0000007F;
//
enum TPccdEvent {
	EPccdEvEmergencyPwrDown=EPEventPwrDownEmergency,
	EPccdEvPwrDown=EPEventPwrDownNormal,
	EPccdEvPwrUp=EPEventPwrUp,
	EPccdEvMediaChange=EPEventMediaChange,
	EPccdEvIReq=4,
	EPccdEvIndChange=5,
	EPccdEvRdyChange=6};
//
const TUint KPccdEvFlagIReqLevelMode=0x00000001;
const TUint KPccdEvFlagReserved=0x80000000;
//
// PC Card maximum system settings
//
const TInt KMaxPccdSockets=KMaxPBusSockets;
const TInt KMaxPccdMediaChanges=2;
const TInt KMaxPccdVccSupplies=2;
const TUint KMaxFuncPerCard=8;
const TUint KDefaultAttribMemSize=0x10000;	  // 64K Bytes (32K CIS)

const TSocket KInvalidSocket=-1;
const TUint8 KInvalidFuncNum=(KMaxFuncPerCard+1);
//
// PC Card Enumerates
//
enum TPccdFuncType {EGlobalCard,EVendorMultiFuncCard,EMemoryCard,ESerialCard,
					EParallelCard,EFixedDiskCard,EVideoCard,ENetworkCard,EAimsCard,
					EScsiCard,EVendorSpecificCard,EUnknownCard}; // Order important
enum TPccdMemType {EPccdAttribMem,EPccdCommon8Mem,EPccdCommon16Mem,EPccdIo8Mem,EPccdIo16Mem};
enum TPccdCardStatus {ECardNotPresent,ECardNotReady,ECardBad,ECardReady};
enum TPccdAccessSpeed {EAcSpeed50nS,EAcSpeed100nS,EAcSpeed150nS,EAcSpeed200nS,
					   EAcSpeed250nS,EAcSpeed300nS,EAcSpeed450nS,EAcSpeed600nS,
					   EAcSpeed750nS,EAcSpeedExtended,EAcSpeedInValid};
enum TMemDeviceType {EDeviceNull,EDeviceRom,EDeviceOTP,EDeviceEPROM,
					 EDeviceEEPROM,EDeviceFlash,EDeviceSRam,EDeviceDRam,
					 EDeviceFunSpec,EDeviceInvalid}; // Order important

// Active signals (correspond to Config entry tuple - dont change)
const TUint KSigBvdActive=0x00000010;	
const TUint KSigWpActive=0x00000020;	
const TUint KSigReadyActive=0x00000040;
const TUint KSigWaitRequired=0x00000080;	
const TUint KSigWaitSupported=KSigWaitRequired;	
//
const TUint KPccdVcc_5V0=0x01;
const TUint KPccdVcc_3V3=0x02;
const TUint KPccdVcc_xVx=0x04;
const TUint KPccdVcc_yVy=0x08;
// Interrupt info 
const TUint KPccdIntShare=0x00000080;	
const TUint KPccdIntPulse=0x00000040;	
const TUint KPccdIntLevel=0x00000020;	

enum TPccdSocketVcc	{EPccdSocket_Invalid=0,EPccdSocket_5V0=KPccdVcc_5V0,EPccdSocket_3V3=KPccdVcc_3V3,
					 EPccdSocket_xVx=KPccdVcc_xVx,EPccdSocket_yVy=KPccdVcc_yVy};

enum TPccdSocketStatus {ESocketFullyOff,ESocketPoweredDown,ESocketNotReset,ESocketReady,
						ESocketCorruptCard,ESocketBatTooLow};
enum TPccdOpCritical {EPccdOpCritical,EPccdOpNonCritical};
//
// PC Card memory chunk speed/type/signal definitions
//
#define __IS_COMMON_MEM(aMemType) (aMemType==EPccdCommon8Mem||aMemType==EPccdCommon16Mem)
#define __IS_IO_MEM(aMemType) (aMemType==EPccdIo8Mem||aMemType==EPccdIo16Mem)
#define __IS_ATTRIB_MEM(aMemType) (aMemType==EPccdAttribMem)
#define DEF_IO_ACSPEED  EAcSpeed200nS
#define DEF_MEM_ACSPEED EAcSpeed250nS
#define DEF_ATTR_ACSPEED EAcSpeed600nS 
//
// PC Card Vcc definitions
//
const TInt KVcc_Level_5V=5000;
const TInt KVcc_Level_3V3=3300;
const TInt KVcc_Level_xVx=0;
const TInt KVcc_Level_yVy=0;
//
// General tuple parsing definitions
//
const TInt KSmallTplBufSize=16;
const TInt KLargeTplBufSize=257;
const TInt KMaxCfEntriesPerCis=20;
//
// Link Tuple definitions
//
const TUint KPccdLinkA=0x00000001;
const TUint KPccdLinkC=0x00000002;
const TUint KPccdLinkMFC=0x00000004;
const TUint KPccdNoLink=0x00000008;
//
// Tuple codes
//
const TUint8 KCisTplNull=0x00;
const TUint8 KCisTplDevice=0x01;
const TUint8 KCisTplLongLinkMfc=0x06;
const TUint8 KCisTplCheckSum=0x10;
const TUint8 KCisTplLongLinkA=0x11;
const TUint8 KCisTplLongLinkC=0x12;
const TUint8 KCisTplLinkTarget=0x13;
const TUint8 KCisTplNoLink=0x14;
const TUint8 KCisTplVers1=0x15;
const TUint8 KCisTplAltStr=0x16;
const TUint8 KCisTplDeviceA=0x17;
const TUint8 KCisTplJedecC=0x18;
const TUint8 KCisTplJedecA=0x19;
const TUint8 KCisTplConfig=0x1A;
const TUint8 KCisTplCfTableEntry=0x1B;
const TUint8 KCisTplDeviceOC=0x1C;
const TUint8 KCisTplDeviceOA=0x1D;
const TUint8 KCisTplDeviceGeo=0x1E;
const TUint8 KCisTplDeviceGeoA=0x1F;
const TUint8 KCisTplManfId=0x20;
const TUint8 KCisTplFuncId=0x21;
const TUint8 KCisTplFunce=0x22;
const TUint8 KCisTplSwIl=0x23;
const TUint8 KCisTplVers2=0x40;
const TUint8 KCisTplFormat=0x41;
const TUint8 KCisTplGeometry=0x42;
const TUint8 KCisTplByteOrder=0x43;
const TUint8 KCisTplDate=0x44;
const TUint8 KCisTplBattery=0x45;
const TUint8 KCisTplOrg=0x46;
const TUint8 KCisTplLongLinkCB=0x47;
const TUint8 KCisTplVendorSpecific1=0x80;
const TUint8 KCisTplVendorSpecific2=0x81;
const TUint8 KCisTplVendorSpecific3=0x82;
const TUint8 KCisTplEnd=0xFF;
//
const TUint8 KPccdNonSpecificTpl=0xff;
const TUint8 KInvalidConfOpt=0xFF;
const TUint KPccdRestartCis=0x8000;
//
// PC Card Configuration Register definitions
//
const TUint KConfigOptionReg=0;
const TUint KConfigOptionRegM=0x00000001;
const TUint KConfigAndStatusReg=1;
const TUint KConfigAndStatusRegM=0x00000002;
const TUint KPinReplacementReg=2;
const TUint KPinReplacementRegM=0x00000004;
const TUint KSocketAndCopyReg=3;
const TUint KSocketAndCopyRegM=0x00000008;

const TUint KConfOptConfM=0x0000003F;
const TUint KConfOptLevIReqM=0x00000040;
const TUint KConfOptSResetM=0x00000080;
const TUint KConfStatIntrAckM=0x00000001;
const TUint KConfStatIntrM=0x00000002;
const TUint KConfStatPwrDwnM=0x00000004;
const TUint KConfStatAudioEnableM=0x00000008;
const TUint KConfStatIoIs8M=0x00000020;
const TUint KConfStatSigChgM=0x00000040;
const TUint KConfStatChangedM=0x00000080;
const TUint KPinRepWProtM=0x00000001;
const TUint KPinRepReadyM=0x00000002;
const TUint KPinRepBvdM=0x0000000C;
//
// Pc Card Flag definitions - Mem request/setup and others
//
const TUint KPccdRequestWait=0x00000001;			// Memory request
const TUint KPccdChunkCacheable=0x00000010;			// Memory request
const TUint KPccdChunkShared=0x00000020;			// Memory request
const TUint KPccdChunkPermanent=0x00000040;			// Memory request
const TUint KPccdChunkSystemOwned=0x00000080;		// Memory request

const TUint KPccdDisableWaitStateCntrl=0x00000100; 	// Memory chunk setup
const TUint KPccdBusWidth32=0x00000200; 			// Memory chunk setup

const TUint KPccdReturnLinkTpl=0x00001000;			// Cis parsing
const TUint KPccdReportErrors=0x00002000;			// Cis parsing
const TUint KPccdFindOnly=0x00004000;				// Cis parsing

const TUint KPccdFastModeEnabled=0x00010000; 		// Access speed

const TUint KPccdCompatNoVccCheck=0x00000001;	    // Config compatibility checking
const TUint KPccdCompatNoVppCheck=0x00000002;	    // Config compatibility checking
const TUint KPccdCompatNoPwrCheck=0x00000004;	    // Config compatibility checking

const TUint KPccdConfigRestorable=0x00000001;	    // Configuration request
const TUint KPccdConfigOverrideNormalPwrEvents=0x00000002;	// Configuration request
//
// PC Card tick definitions
//
const TInt KPccdPowerUpReqInterval=20000;	// Units 1uS
const TInt KResetOnDefaultLen=5;			// Units 20ms
const TInt KResetOnMinLen=3;				// Units 20ms
const TInt KResetOffDefaultLen=5;			// Units 20ms
const TInt KPwrUpDefaultTimeOut=125;		// Units 20mS
const TInt KPwrUpMaxTimeOut=500;			// Units 20ms

class TPwrUpProfile
	{
public:					// Units: 20mS
	TInt iResetOnLen;	// Period that we hold Pc Card in reset.
	TInt iResetOffLen;	// Period that we pause following Pc Card in reset.
	TInt iPwrUpTimeout;	// Timeout waiting for ready (including reset on)
	};

class TPccdChnk
	{
public:
	IMPORT_C TPccdChnk();
	IMPORT_C TPccdChnk(TPccdMemType aType,TUint32 aBaseAddr,TUint32 aLen);
public:
	TPccdMemType iMemType;
	TUint32 iMemBaseAddr;
	TUint32 iMemLen;
	};

const TInt KMaxChunksPerConfig=2;
class TPcCardConfig
	{
public:
	IMPORT_C TPcCardConfig();
	IMPORT_C TBool IsMachineCompatible(TSocket aSocket,TInt aFlag=0);
public:								 
	TPccdAccessSpeed iAccessSpeed;
	TUint iActiveSignals;
	TInt iVccMaxInMilliVolts;			
	TInt iVccMinInMilliVolts;						
	TPccdChnk iChnk[KMaxChunksPerConfig];
	TInt iValidChunks;
	TBool iIsIoAndMem;
	TBool iIsDefault;
	TBool iPwrDown;
	TInt iVppMaxInMilliVolts;						
	TInt iVppMinInMilliVolts;						
	TInt iOperCurrentInMicroAmps;				   
	TInt iPwrDwnCurrentInMicroAmps;				 
	TUint iInterruptInfo;
	TInt iConfigOption;
	TUint32 iConfigBaseAddr;
	TUint32 iRegPresent;	
	};

class TPcCardRegion 
	{
public:
	IMPORT_C TPcCardRegion();
	IMPORT_C TBool IsMachineCompatible(TSocket aSocket);
public:										
	TPccdAccessSpeed iAccessSpeed;
	TUint iActiveSignals;
	TPccdSocketVcc iVcc;
	TPccdChnk iChnk;
	TMemDeviceType iDeviceType;
	TInt iExtendedAccSpeedInNanoSecs;
	};

class TPccdType
	{
public:
	IMPORT_C TPccdType();
public:
	TPccdFuncType iFuncType[KMaxFuncPerCard];
	TInt iFuncCount;
	};

enum TPccdBatteryState {EPccBattZero,EPccBattVeryLow,EPccBattLow,EPccBattGood};
class TSocketIndicators
	{
public:
	TBool iCardDetected;
	TInt iVoltSense;
	TBool iWriteProtected;
	TPccdBatteryState iBatState;
	};

class TPcCardSocketInfo
	{
public:
	TInt iNomVppInMilliVolts;
	TInt iMaxVppCurrentInMicroAmps;
	TUint iSupportedSignals;
	TPccdAccessSpeed iMaxAttribAccSpeed;
	TPccdAccessSpeed iMaxCommonIoAccSpeed;
	};
//
class TPcCardMachineInfo
	{
public:
	TInt iTotalSockets;
	TInt iTotalMediaChanges;
	TInt iTotalPrimarySupplies;
	TInt iControllerHwVersion;
	TInt iDisableOnLowBattery;
    TInt iBaseBusNumber;
	};
typedef TPckg<TPcCardMachineInfo> TPcCardMachineInfoPckg;
//
class RPccdWindow;
class RPccdChunkBase
	{
public:
	RPccdChunkBase();
	virtual ~RPccdChunkBase();
	virtual void CreateL(TSocket aSocket,TPccdChnk aChunk,TUint aFlag)=0;
	virtual TInt SetupChunkHw(TPccdAccessSpeed aSpeed,TPccdMemType aMemType,TBool aWaitSig,TUint aFlag)=0;
	virtual TInt LinearAddress(TLinAddr &anAddr)=0;
	virtual TInt Read(TInt aPos,TAny *aPtr,TInt aLength)=0;
	virtual TInt Write(TInt aPos,const TAny *aPtr,TInt aLength)=0;
	virtual TInt ReadByteMultiple(TInt aPos,TAny *aPtr,TInt aCount)=0;
	virtual TInt WriteByteMultiple(TInt aPos,const TAny *aPtr,TInt aCount)=0;
	virtual TInt ReadHWordMultiple(TInt aPos,TAny *aPtr,TInt aCount)=0;
	virtual TInt WriteHWordMultiple(TInt aPos,const TAny *aPtr,TInt aCount)=0;
	virtual TBool IsTypeCompatible(TPccdMemType aMemType)=0;
	TInt AllocateWinCheck(TPccdChnk aWin,TUint aFlag);
	void AddWindowL(RPccdWindow *aWindow);
	void RemoveWindow(RPccdWindow *aWindow);
	TBool IsRemovable();
	TBool IsLocked();
	inline TUint32 BaseAddr();
protected:
	RPointerArray<RPccdWindow> iChunkWindows;
	TSocket iSocketNum;
	TPccdChnk iChnk;
	TBool iCacheable;
    friend class RPccdWindow;
	};

class RPccdWindow
	{
public:
	IMPORT_C RPccdWindow();
	IMPORT_C RPccdWindow(TUint32 anOffset,TUint32 aLen,TPccdAccessSpeed aSpeed,TPccdMemType aMemType,TUint aFlag);
	IMPORT_C ~RPccdWindow();
	IMPORT_C TInt SetupChunkHw(TUint aFlag=0);
	inline TInt Read(TInt aPos,TAny *aPtr,TInt aLength);
	inline TInt Write(TInt aPos,const TAny *aPtr,TInt aLength);
	inline TInt ReadByteMultiple(TInt aPos,TAny *aPtr,TInt aCount);
	inline TInt WriteByteMultiple(TInt aPos,const TAny *aPtr,TInt aCount);
	inline TInt ReadHWordMultiple(TInt aPos,TAny *aPtr,TInt aCount);
	inline TInt WriteHWordMultiple(TInt aPos,const TAny *aPtr,TInt aCount);
	inline void SetAccessSpeed(TPccdAccessSpeed aSpeed);
	IMPORT_C TInt LinearAddress(TLinAddr &anAddr);
private:
	TBool Overlap(TUint32 anOffset,TUint aLen);
	void Connect(RPccdChunkBase *aChunk);
	void Disconnect();
	inline TBool IsPermanent();
	inline TBool IsShareable();
	inline TBool IsSystemOwned();
private:
	TPccdAccessSpeed iAccessSpeed;
	TPccdMemType iMemType;			// ???
	TUint32 iOffset;
	TUint32 iLen;
	RPccdChunkBase *iChunk;
	TBool iConnected;
	TUint iType;
	TBool iWaitSig;
	friend class RPccdChunkBase;
	};

class DPcCardSocket;
class TCisReader
	{
public:
   	IMPORT_C TCisReader();
	IMPORT_C TInt SelectCis(TSocket aSocket,TInt aCardFunc);
	IMPORT_C TInt Restart();
	IMPORT_C TInt FindReadTuple(TUint8 aDesiredTpl,TDes8 &aDes,TUint aFlag=0);
	IMPORT_C TInt ReadTuple(TDes8 &aDes);
	IMPORT_C TInt FindReadRegion(TPccdSocketVcc aSocketVcc,TPcCardRegion &anInfo,TUint8 aDesiredTpl=0);
	IMPORT_C TInt FindReadConfig(TPcCardConfig &anInfo);
private:
	TInt DoSelectCis(TSocket aSocket,TInt aCardFunc);
	void DoRestart();
	TInt DoFindReadTuple(TUint8 aDesiredTpl,TDes8 &aDes,TUint aFlag);
	TInt DoReadTuple(TDes8 &aDes);
	TInt FollowLink(TUint aFullErrorReport);
	TInt VerifyLinkTarget();
private:
	DPcCardSocket *iSocket;
	TInt iFunc;
	TUint32	iCisOffset;	
	TUint32	iLinkOffset;	
	TPccdMemType iMemType;
	TInt iLinkFlags;
	TBool iRestarted; 
	TInt iRegionCount; 	// For FindReadRegion() - Count of regions read so far.
	TInt iConfigCount;  // For FindReadConfig() - Configurations read so far.
	friend class DPcCardController;
	};

const TInt KMaxSimultaneousPwrUpsPerSocket=3;
class TPowerUpRequest
	{
public:
	TPowerUpRequest(TSocket aSocket);
	TInt Add(DThread *aThread,TRequestStatus *aReqStat);
	void TickService();
	static void Tick(TAny *aPtr,TInt);
private:
	TInt iState;
	TInt iElapsedTicks;	
	TSocket iSocketNum;
	DThread *iThread[KMaxSimultaneousPwrUpsPerSocket];
	TRequestStatus *iReqStat[KMaxSimultaneousPwrUpsPerSocket];
	TInt iResetOnLen;		
	TInt iResetOffLen;	
	TInt iPwrUpTimeout;	
	TTickLink iTickLink;
	};

class TPcCardVcc : public TPBusPsuBase
	{
public:
	TPcCardVcc(TInt aPsuNum);
    virtual void Init();
    virtual TInt ResetEvent(TPBusPwrEvent anEvent, TInt anInfo, TResetMode aMode);
	virtual TBool IsLocked();
    TBool IsInCritical();
	inline void SetVoltage(TPccdSocketVcc aVoltage);
	inline TPccdSocketVcc VoltageSetting();
	inline TBool IsOverrideNormalPwrEvents();
 	TInt OverrideNormalPwrEvents(TBool anOverride);
	static TInt SocketVccToMilliVolts(TPccdSocketVcc aVcc);
protected:		  
	TPccdSocketVcc iVoltageSetting;
	TUint iFlags;
private:
	DPcCardSocket *iSocket[KMaxPccdSockets];
	friend class DPcCardController;
	};

class TPcCardMediaChange : public TMediaChangeBase
	{
public:
	TPcCardMediaChange(TInt aMediaChangeNum);
	virtual TInt Init();
private:
	virtual void MediaChangeEvent(TPBusPwrEvent anEvent);
private:
	TPcCardVcc *iVcc[KMaxPccdVccSupplies];
//	friend class DPcCardController;
	};

class TPcCardFunction
	{
public:
	TPcCardFunction(TUint32 anOffset,TPccdMemType aMemType);
	void SetConfigOption(TInt anIndex,CBase *aClientID,TUint aConfigFlags);
	inline void SetConfigBaseAddr(TUint32 anAddr);
	inline void SetConfigRegMask(TInt aMask);	
	inline void SetFuncType(TPccdFuncType aType);	
	TInt ConfigRegAddress(TInt aRegOffset,TInt &anAddr);
	void ClearConfiguration(TSocket aSocketNumForThisFunc);
	inline TPccdFuncType FuncType();
	inline TInt ConfigOption();
	inline TBool IsConfigured();
	inline TBool IsConfiguredByClient(CBase *aClientID);
	inline TBool IsRestorableConfig();
	inline TUint32 InitCisOffset();
	inline TPccdMemType InitCisMemType();
	inline TBool ConfigOverridesNormalPwrEvents();
//	void ReadCis(TUint32 aPos,TDes8 &aDes,TInt aLen);
protected:
	TPccdFuncType iFuncType;
	TUint32 iInitCisOffset;	
	TPccdMemType iInitCisMemType;
	TUint32 iConfigBaseAddr;
	TInt iConfigRegMask;
	TInt iConfigIndex;
	CBase *iClientID;
	TUint iConfigFlags;
	};

class DPcCardSocket : public CBase
	{
public:
	DPcCardSocket(TSocket aSocketNum);
	virtual void CreateL();
	virtual void SetSocketStatus(TPccdSocketStatus aStatus);
	void SafeSetSocketStatus(TPccdSocketStatus aStatus);
	virtual void Reset1()=0;
	virtual void Reset2();
	void CreateMemWindowL(TPccdChnk aChnk,TPccdAccessSpeed aSpeed,RPccdWindow **aWin,TUint aFlag);
	void DestroyMemWindow(RPccdWindow *aWin);
	TInt RequestConfig(TInt aCardFunc,CBase *aClientID,TPcCardConfig &anInfo,TUint aFlag);
	void ReleaseConfig(TInt aCardFunc,CBase *aClientID);
	TInt ReadConfigReg(TInt aCardFunc,TInt aRegOffset,TUint8 &aVal);
	TInt WriteConfigReg(TInt aCardFunc,TInt aRegOffset,const TUint8 aVal);
	TInt AddCallBack(TPBusCallBack& aCallBack,TUint aFlag);
	TInt AddCallBack(TPBusCallBack& aCallBack,TPccdEvent anEvent);
	void RemoveCallBack(CBase* aClientID,TPBusCallBack* aCallBack=NULL);
	TInt EnableEvent(TPccdEvent anEvent);
	TInt DisableEvent(CBase *aClientID,TPccdEvent anEvent);
	TInt ClearEvent(TPccdEvent anEvent);
	void SetEvent(TPccdEvent anEvent,TInt anInfo=0);
	TInt ReadCis(TPccdMemType aMemType,TInt aPos,TDes8 &aDes,TInt aLen);
	inline TPccdSocketStatus SocketStatus();
	inline TInt Number();
	TPcCardFunction *CardFunc(TInt aCardFunc);
	void AddNewFuncL(TUint32 anOffset,TPccdMemType aMemType);
	inline TInt CardFuncCount();
	inline TBool IsValidCardFunc(TInt aCardFunc);
	inline TBool IsMultiFuncCard();
	TBool IsConfigLocked();
	TBool IsMemoryLocked();
	TBool IsVerified();
	TBool ConfigOverridesNormalPwrEvents();
	virtual void HwReset(TBool anAssert)=0;
	virtual TInt Indicators(TSocketIndicators &anInd)=0;
	virtual TBool Ready(TInt aCardFunc=KInvalidFuncNum)=0;
	TPccdSocketVcc VccSetting();
	void Restore();
protected:
	virtual RPccdChunkBase *NewPccdChunkL(TPccdMemType aType)=0;
	virtual TInt EventCallBackEnable(TPccdEvent anEvent,TUint aFlag=0)=0;
	virtual void EventCallBackDisable(TPccdEvent anEvent)=0;
	virtual void EventCallBackClear(TPccdEvent anEvent)=0;
	TBool EventCallBacksRequested(TPccdEvent anEvent);
	void RemoveChunk(RPccdChunkBase *aChunk);
    TInt VerifyEventMask(TUint anEventMask);
protected:
	TSocket iSocketNum;
	TPccdSocketStatus iStatus;
	RPointerArray<TPcCardFunction> iCardFuncArray;
	RPointerArray<RPccdChunkBase> iMemChunks;
	TPBusEventArrayBase iEventArray[KTotalPccdEventQueues];
	TPowerUpRequest iPwrUpReq;
	RPccdWindow *iAttribWin;
	friend class RPccdChunkBase;
	friend class DPcCardController;
	};

class DPcCardController : public DPeriphBusController
	{
public:
	DPcCardController();
	virtual TPBusControllerType ControllerType();
	virtual void PowerUpBus(TPBusNum aBus,DThread *aThread,TRequestStatus *aReqStat);
	virtual TInt RegisterPowerNotification(TPBusNum aBus,TPBusCallBack& aCallBack,TUint aFlag);
	virtual void DeregisterPowerNotification(TPBusNum aBus,CBase* aClientID,TPBusCallBack* aCallBack=NULL);
	virtual TInt SetPowerEvent(TPBusNum aBus,TPBusPwrEvent anEvent,TInt anInfo=0);
	virtual TInt DeregisterClient(CBase *aClientID);
	virtual TInt DeviceIsReady(TPBusNum aBus);
	virtual TInt TotalSupportedBuses();
	virtual TPBusNum BaseBusNumber();
	virtual TPccdCardStatus CardStatus(TSocket aSocket);
	virtual void PowerUpCard(TSocket aSocket,DThread *aThread,TRequestStatus *aReqStat);
	virtual TInt RestoreCardPower(TSocket aSocket);
	virtual TInt PowerDownCard(TSocket aSocket);
	virtual TInt VerifyCard(TSocket aSocket,TPccdType &aType);
	virtual void SoftResetCard(TSocket aSocket,TInt aCardFunc);
	virtual TInt RequestConfig(TSocket aSocket,TInt aCardFunc,CBase *aClientID,TPcCardConfig &anInfo);
	virtual TInt RequestConfig(TSocket aSocket,TInt aCardFunc,CBase *aClientID,TPcCardConfig &anInfo,TUint aFlag);
	virtual void ReleaseConfig(TSocket aSocket,TInt aCardFunc,CBase *aClientID);
	virtual TInt RequestMemory(TSocket aSocket,TPccdChnk aChnk,TPccdAccessSpeed aSpeed,RPccdWindow **aWin,TUint aFlag=0);
	virtual void ReleaseMemory(TSocket aSocket,RPccdWindow *aWin);
	virtual TInt ReadConfigReg(TSocket aSocket,TInt aCardFunc,TInt aRegOffset,TUint8 &aVal);
	virtual TInt WriteConfigReg(TSocket aSocket,TInt aCardFunc,TInt aRegOffset,TUint8 aVal);
	virtual TBool CardIsReadyAndVerified(TSocket aSocket);
	virtual TBool CardIsReady(TSocket aSocket);
	virtual TBool CardIsPresent(TSocket aSocket);
	virtual TBool CardIsPowered(TSocket aSocket);
	virtual TInt RegisterEvent(TSocket aSocket,TPccdEvent anEvent,TPBusCallBack& aCallBack);
	virtual TInt RegisterEvent(TSocket aSocket,TPBusCallBack& aCallBack,TUint aFlag);
	virtual void DeregisterEvent(TSocket aSocket,CBase *aClientID,TPBusCallBack* aCallBack=NULL);
	virtual TInt SetEvent(TSocket aSocket,TPccdEvent anEvent,TInt anInfo=0);
	virtual TInt InCritical(TSocket aSocket,CBase *aClientID=NULL);
	virtual void EndInCritical(TSocket aSocket,CBase *aClientID=NULL);
	virtual TBool IsInCritical(TSocket aSocket,CBase *aClientID);
	virtual TPccdSocketVcc SocketVcc(TSocket aSocket);
	virtual TInt SocketIndicators(TSocket aSocket,TSocketIndicators &anInd);
	virtual void PwrUpProfile(TPwrUpProfile& aProfile);
	virtual void SetPwrUpProfile(TPwrUpProfile& aProfile);
	static void PcCardMachineInfo(TPcCardMachineInfo &anInfo);
    static void SocketInfo(TSocket aSocket,TPcCardSocketInfo& anInfo);
    static TInt VccSupplyFromSocket(TSocket aSocket);
	static TInt MediaChangeNumFromSocket(TSocket aSocket);
	static TInt MediaChangeNumFromVcc(TInt aVccNum);
    void ResetInactivity(TSocket aSocket);
protected:
	virtual void DoCreateL();
    virtual TInt PowerOn();
    virtual void PowerStandby();
    virtual void PowerEmergencyStandby();
	virtual TInt ConfigHw()=0;
	virtual TInt EnableEvent(TPBusNum aBus,TInt anEvent);
	virtual TInt DisableEvent(TPBusNum aBus,CBase *aClientID,TInt anEvent);
	virtual TInt ClearEvent(TPBusNum aBus,TInt anEvent);
	virtual TMediaChangeBase *MediaChange(TPBusNum aBus);
	virtual TPBusPsuBase *PrimaryPsu(TPBusNum aBus);
	static DPcCardSocket &Socket(TSocket aSocket);
	static TPcCardVcc &Vcc(TSocket aSocket);
	void GetCisFormatL(TSocket aSocket);
	TInt ValidateCis(TSocket aSocket,TInt aCardFunc);
	TInt DoPowerUpCard(TSocket aSocket,DThread *aThread,TRequestStatus *aReqStat);
protected:
	DPcCardSocket *iSocket[KMaxPccdSockets];
	TPcCardMediaChange *iMediaChange[KMaxPccdMediaChanges];
	TPcCardVcc *iVcc[KMaxPccdVccSupplies];
    TPcCardMachineInfo iMachineInfo;
	TPwrUpProfile iPwrUpProfile;
private:
	friend class TCisReader;
	friend class DPcCardSocket;
	friend class TPowerUpRequest;
	friend class TPcCardVcc;
	friend class TPcCardMediaChange;
	friend class RPccdChunkBase;
	friend class TPcCardConfig;
	friend class TPcCardRegion;
	friend class TPcCardFunction;
public:
	enum TPcCardPanic
		{
		EPcCardBadSocketNumber=0,
		EPcCardCisReaderUnInit=1,
		EPcCardBadFunctionNumber=2,
		EPcCardPowerUpReqFault=3,
		EPcCardMediaDriverCurrentConsumption=4
		};
    static void Panic(TPcCardPanic aPanic);
	};

#if defined(__WINS__)
class TPcCardControllerInterface
	{
public:
	IMPORT_C static TInt Create(); 
	};
#endif

#include <p32pccd.inl>

#endif

