// M32STD.H
//
// Copyright (c) 1995-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __M32STD_H__
#define __M32STD_H__
#include <e32std.h>
#include <e32base.h>
#include <e32svr.h>
#include <e32rom.h>
#include <e32ver.h>
#include <e32keys.h>
#include <u32std.h>
#include <k32std.h>
#include <p32std.h>
#include <m32hal.h>

#ifdef __SINGLE__
#define PageDirectory	((TPde*)TheSuperPage().iPageDir)
#endif

#if defined(__MEIG__) || defined(__MISA__) ||\
	defined(__MCOY__) || defined(__MINT__) || defined(__MCOT__)
// Only implemented on these ASSPs at the moment
#define __ENABLE_DEBUG_MONITOR__		// NOT TO BE ENABLED IN PRODUCT
#endif

#if defined(__MHELEN__) && defined(_DEBUG)
#define __ENABLE_DEBUG_MONITOR__
#endif

// Enable the per-thread CPU profiling in the rescheduler
//#define __PROFILE__

// The maximum size for the event queue
const TInt KMaxEventQueue=0x40;

// Hardware variant discriminator
class THardwareVariant
	{
public:
	inline THardwareVariant();
	inline THardwareVariant(TUint aVariant);
	inline operator TUint();
	inline TBool IsIndependent();
	inline TBool IsCpu();
	inline TBool IsCompatibleWith(TUint aCpu, TUint aAsic, TUint aVMask);
private:
	inline TUint Layer();
	inline TUint Parent();
	inline TUint VMask();
private:
	TUint iVariant;
	};

// Thread status
enum TThreadStatus {ECreated,ESuspended,EWaitSemaphore,EWaitMutex,EReady,ECurrent,EDead};
//
// The platform objects derived from the kernel abstract base classes.
//
//
class DPlatLibrary : public DLibrary
	{
public:
	DPlatLibrary();
	~DPlatLibrary();
	void DoLoadL(TLoaderInfo& anInfo);
	void LoadedL(TLoaderInfo& anInfo);
	TLibraryFunction Lookup(TInt anOrdinal);
	void Info(TLoaderInfo& anInfo);
	TLibraryEntry EntryPoint();
	TUint* DllRefTable();
	TInt GetRamSizes(TInt& aCodeSize,TInt& aConstDataSize);
private:
	void CreateGenericDataChunkL(TLoaderInfo& anInfo);
public:
	TUint iCodeAddress;
	TUint iCodeSize;
	DChunk* iCodeChunk;
	TUint32 iCheckSumCode;
	DChunk* iDataChunk;
	TLinAddr iDataRunAddress;
	TInt iDataSize;
	TInt iBssSize;
private:
	TBool iCreating;
	TUint iConstOffset;
	TUint *iExportDir;
	TInt iExportDirCount;
	};
//
class DPlatProcess;
class DPlatChunk : public DChunk
	{
public:
	enum TChunkState {ENotRunning=0, ERunningRO=1, ERunningRW=2};

	DPlatChunk();
	~DPlatChunk();
	void Destruct();
	void DoCreate(TInt aMaxSize,TChunkType aType);
	IMPORT_C void SetContiguousRamL(TInt aSize);
	IMPORT_C void SetHardwareL(TPhysAddr aPhysAddr, TInt aSize);
	void SetFixedAddress(TLinAddr anAddr, TInt anInitialSize);
	void Reserve(TInt anInitialSize);
	TInt Adjust(TInt aNewSize);
	TInt AdjustDoubleEnded(TInt aBottom, TInt aTop);
	void AdjustL(TInt aNewSize);
	void AdjustUserL(TInt aNewSize);
	void Read(TInt aPos,TAny *aPtr,TInt aLength) const;
	void Write(TInt aPos,const TAny *aPtr,TInt aLength);
	TInt BaseOffset();
	void SetFinalPagePermissions();
	void ApplyTopLevelPermissions(TChunkState aChunkState);
	void MoveToRunAddress(TLinAddr aLinearAddr,TChunkState aChunkState);
	void MoveToHomeSection();
	TInt ReserveAt(TLinAddr aAddr);
private:
	TLinAddr AllocateHomeAddress(TInt aSize);
	void DeallocateHomeAddress();
	TLinAddr ReallocateHomeAddress(TInt aNewSize);
	virtual void SetupPermissions(TChunkType aChunkType)=0;
	virtual void SetPdeInfo()=0;
public:
	enum TPlatChunkAttributes	{
								EFixedAccess=0x80000000,
								EFixedAddress=0x40000000,
								EHomeAllocFromTop=0x20000000,
								EPrivate=0x10000000,
								ECode=0x08000000,
								EContiguous=0x04000000,
								EHardware=0x02000000,
								};

	TChunkType iChunkType;
	TChunkState iChunkState;
	TPte iPtePermissions;
	TPde iPdePermissions[3];	// indexed by iChunkState
	TInt iHomeRegionSize;
	TLinAddr iHomeBase;
	TPriQueLink iLink;
	TLinAddr iPreferedRunAddress;
	TInt iNumPdes;
	TPde* iPdes;
	TPde* iHomePdes;
#if defined(__SINGLE__)
	TUint8* iChunkBase;
#endif
private:
	friend class Mmu;
	friend class DPlatProcess;
	};
//

class TPhysAddrs 
   { 
   public:
   TPhysAddr iPhysAddr;
   TInt iSize;
   };

class DPlatChunkHw : public CObject
	{
public:
	IMPORT_C DPlatChunkHw();
	IMPORT_C ~DPlatChunkHw();
	IMPORT_C void DoCreateL(TPhyAddr anAddr,TInt aSize,TChunkType aChunkType);
	IMPORT_C void DoCreateL(class TPhysAddrs* aAddr,TInt aCount,TChunkType aChunkType);
	IMPORT_C void Read(TInt aPos,TAny *aPtr,TInt aLength) const;
	IMPORT_C void Write(TInt aPos,const TAny *aPtr,TInt aLength);
	IMPORT_C TLinAddr LinearAddress();
protected:
	TPhysAddr iPhysAddr;
	TLinAddr iLinAddr;
	TInt iSize;
public:
	TPriQueLink iLink;
	};
//
class DPlatTransferBuffer : public DTransferBuffer
	{
public:
	DPlatTransferBuffer();
	~DPlatTransferBuffer();
	IMPORT_C void SetNonContiguousL();
	IMPORT_C void SetContiguousL();
	IMPORT_C void SetFixedContiguousL(TPhysAddr aPhysAddr);
	void DoClose();
public:
	DPlatChunk* iChunk;
	};
//
class DPlatTransferWindow : public DTransferWindow
	{
public:
	DPlatTransferWindow();
	~DPlatTransferWindow();
	TInt DoMapInBuffer(DTransferBuffer& aBuffer);
	void DoMapOutBuffer();
	TUint8* DoBufferAddress();
	};
//
class DPlatThread;
class DPlatSemaphore : public DSemaphore
	{
public:
	DPlatSemaphore();
	~DPlatSemaphore();
	void DoCreate(TInt aCount);
	void Wait();
	void Signal();
	void Signal(TInt aCount);
	void WaitCancel(DPlatThread *aThread);
private:
	TDblQue<DPlatThread> iThreadQ;
	};
//
class DPlatMutex : public DMutex
	{
public:
	DPlatMutex();
	~DPlatMutex();
	void DoCreate();
	void Wait();
	void Signal();
	void WaitCancel(DPlatThread *aThread);
	inline DPlatThread *HoldingThread();
private:
	DPlatThread *iHoldingThread;
	TDblQue<DPlatThread> iThreadQ;
	};
//
class DPlatThread : public DThread
	{
public:
	DPlatThread();
	~DPlatThread();
	void DoCreate(TThreadCreateType aType,TInt aStackSize,TThreadFunction aFunction,TAny *aPtr,TOwnerType anOwnerType);
	void SupervisorSend(TInt aFunction,const TInt aPtr[],TRequestStatus *aStatus);
	void SupervisorComplete(TInt aReason);
	void Resume();
	void Suspend();
	void Kill(TInt aReason);
	void Terminate(TInt aReason);
	void Panic(const TDesC &aCategory,TInt aReason);
	void DoSetPriority(TThreadPriority aPriority);
	TAny* HomeAddress(TAny* anAddress);
	TAny* CurrentAddress(const TAny* anAddress);
	TAny* CurrentAddress(const TAny* anAddress, TInt& aMaxSize);
	TInt Read(const TAny *aPtr,TUint8 *aTrg,TInt aLength);
	TInt Write(const TAny *aPtr,const TUint8 *aSrc,TInt aLength);
	TInt CpuTime(TTimeIntervalMicroSeconds& aMicroSeconds) const;
//
	virtual void SetupContext(TThreadCreateType aType,TAny *aStackTop,TThreadFunction aFunction,TAny *aPtr)=0;
//
	void Die(TExitType aType,TInt aReason,const TDesC &aCategory);
	void Exception(TExcType anException);
//
	void CheckSuspendThenReady();
	void SetAbsPriority();
	inline TThreadStatus Status();
	inline void SetStatus(TThreadStatus aStatus);
	inline void SetWaitingMutex(DPlatMutex *aMutex);
	inline void SetWaitingSemaphore(DPlatSemaphore *aSemaphore);
public:
	TRequestStatus* iSvStatus;
	TInt8 iStatus;
	TInt8 iSpare;
	TInt16 iSuspendCount;
	DPlatSemaphore *iWaitingSemMutx;
	TPriQueLink iLink;
	TDblQueLink iProcessLink;
	TUint iRescheduleTime;
	TCpuTime iTotalCpuTime;
private:
	friend class TScheduler;
	friend class DPlatSemaphore;
	friend class DPlatMutex;
	friend class DPlatProcess;
	};
//
class DPlatProcess : public DProcess
	{
public:
	DPlatProcess();
	~DPlatProcess();
	void Destruct();
	void DoCreate(TBool aFirstProcess,TLoaderInfo& anInfo);
	TInt GetRamSizes(TInt& aCodeSize,TInt& aConstDataSize,TInt& anInitialisedDataSize,TInt& anUninitialisedDataSize);
	TInt GetMemoryInfo(TProcessMemoryInfo& aInfo) const;
	void Loaded(TLoaderInfo& anInfo);
	void Resume();
	void Kill(TInt aReason);
	void Terminate(TInt aReason);
	void Panic(const TDesC& aCategory,TInt aReason);
	void DoSetPriority(TProcessPriority aPriority);
	void AddDllDependencyL(DLibrary *aDll);
//
	void CreateThreadL(TLoaderInfo& anInfo,DThread*& aThread);
	void Die(TExitType aType,TInt aReason,const TDesC &aCategory);
	void AddThread(DPlatThread &aThread);
	virtual DThread *FirstThread();
//
	TInt AddFindChunk(DChunk* aChunk);
	TInt AddChunk(DChunk* aChunk,TBool isReadOnly);
//	TInt AddChunk(DChunk *aChunk,TLinAddr& aDataSectionBase,TChunkType aChunkType,TBool isReadOnly);
	TInt AddChunk(DChunk *aChunk,TLinAddr& aDataSectionBase,TBool isReadOnly);
//	TInt AllocateDataSectionBase(DPlatChunk &aChunk,TChunkType aChunkType,TUint& aBase);
	TInt AllocateDataSectionBase(DPlatChunk &aChunk,TUint& aBase);
	IMPORT_C TUint8* DataSectionBase(DPlatChunk* aChunk) const;
	void RemoveChunk(DChunk *aChunk);
	DPlatChunk *LookupChunk(const TAny *aPtr,TInt &aPos);
	void MoveChunksToDataSection();
	void MoveChunksToHomeSection();
	void ProtectChunks();
	void UnprotectChunks();
//
	inline TInt BeingCreated();
//
	TUint ChunkAccess(DChunk* aChunk);
protected:
	TInt ChunkIndex(DChunk* aChunk,TInt& aPos) const;
	virtual void AddFixedAccessChunk(DPlatChunk *aChunk)=0;
	virtual void RemoveFixedAccessChunk(DPlatChunk *aChunk)=0;
public:
	TUint iEntryPoint;
	TUint iCodeAddress;
	TUint iCodeSize;
	TUint iTextSize;
	TInt  iBssSize;
	TUint iDataSize;
	TUint *iExportDir;
	TInt iExportDirCount;
	TBool iWindowServer;
	DChunk* iDataBssChunk;
	DChunk* iCodeChunk;
	TUint32 iCheckSumCode;

	enum TPlatProcessAttributes	{
								ESupervisor=0x80000000,
								EMoving=0x40000000,
								EVariableAccess=0x20000000,
								EMovingCode=0x10000000,
								EBeingLoaded=0x08000000,
								EVariableCode=0x04000000,
								};
	struct SChunkInfo
		{
		TLinAddr iDataSectionBase;
		DPlatChunk *iChunk;
		TInt16 iAccessCount;
		TInt16 isReadOnly;
		};

	TInt iNumChunks;
	TInt iAllocatedChunks;
	SChunkInfo *iChunks;
	TInt iNumMovingChunks;
	TInt iNumNonFixedAccessChunks;
	TInt iNumNonFixedAccessCodeChunks;
	TDblQue<DPlatThread> iThreadQ;
	friend class TScheduler;
	};
//
class TSupervisor
	{
public:
	void Receive(TRequestStatus &aStatus);
	void Deliver(TInt aFunction,const TInt aPtr[],DThread& aClient);
public:
	TRequestStatus *iStatus;
	};
//
class RPlatHeapK : public RHeapK
	{
public:
	static RHeapK* FixedHeap(TAny* aBase,TInt aMaxLength);
	RHeap* Relocate(DPlatProcess* aProcess,DPlatChunk* aChunk);
	void Mutate(DPlatChunk* aChunk,TInt anOffset,TInt aMinLength,TInt aMaxLength,TInt aGrowBy=KMinHeapGrowBy);
protected:
	RPlatHeapK(TInt aMaxLength);
	};

//
// The Scheduler
//
class TScheduler : private TPriQue<DPlatThread>
	{
public:
	TScheduler();
	void StartPreemptionTimer();
	void TickPreemptionTimer();
	TInt ReSchedule();
	void Ready(DPlatThread &aThread);
private:
	static void TimerComplete(TAny *aPtr,TInt aDelay);
private:
	TInt iTimer;
	TInt iTimeslice;
	};
//
// The millisecond timer abstraction
//
class TMilliSecondCallBack
    {
public:
    IMPORT_C TMilliSecondCallBack(TInt aMilliseconds,TCallBack aCallback);
    IMPORT_C void Start();
	IMPORT_C void Cancel();
private:
	TMilliSecondCallBack *iNext;
    TInt iDelta;
    TInt iCount;
    TCallBack iCallBack;
    friend class MilliSecondTimer;
    };

/**
 * The interrupt abstraction
 */
class TInterrupt
	{
public:
	enum TBindBehaviour { EBindOnce, EBindChain, EBindFinal };
public:
	IMPORT_C TInterrupt();
	IMPORT_C void Enable();
	IMPORT_C void Disable();
	IMPORT_C void Clear();
	IMPORT_C TInt Bind(const TDesC8 &aName);
	IMPORT_C TInt Bind(const TDesC8 &aName, TBindBehaviour aBehaviour);
    IMPORT_C void UnBind();
	inline TBool Enabled();
protected:
	IMPORT_C virtual void Service()=0;
private:
	TInterrupt *Prev();
	friend class Pic;
private:
	TInt iID;
	TBool iEnabled;
	TBindBehaviour iBindBehaviour;
	TInterrupt *iNext;
	};
//
// The Dma abstraction
//
class TDmaInterrupt : public TInterrupt
	{
private:
	inline TDmaInterrupt(TDma *aDma);
	virtual void Service();
	friend class TDma;
private:
	TDma *iDma;
	};

class TDma
	{
public:
	IMPORT_C TDma();
	IMPORT_C TInt Bind(Dma::TDmaDevice aDevice);
	IMPORT_C void UnBind();
	IMPORT_C void Cancel();
	IMPORT_C TInt Count();
	inline TInt Channel();
	inline Dma::TDmaDevice DmaDevice();
protected:
	IMPORT_C TInt Copy(const TUint8* aLogicalSource, TUint8* aLogicalDest, TInt aCount);
	IMPORT_C TInt Transmit(const TUint8* aLogicalSource, TInt aCount);
	IMPORT_C TInt Receive(TUint8* aLogicalDest, TInt aCount);
	IMPORT_C TInt Fill(const TUint8* aBuffer, TInt aCount);
	IMPORT_C virtual void Service()=0;
private:
	TInt GetLargestXfer(TLinAddr startAddr,TPhysAddr& src);
	void NextBlock();
	friend class Dma;
	friend class TDmaInterrupt;
private:
	enum TDmaMode { EDmaCopy, EDmaPipeReceive, EDmaPipeTransmit, EDmaFill };
	TInt iChannel;
	Dma::TDmaDevice iDevice;
	TDmaInterrupt iInterrupt;
//
	TDmaMode iMode;
	TLinAddr iSrc;
	TLinAddr iDest;
	TInt iCount;
	};
//
// The exception abstraction
//
class TException
	{
public:
	IMPORT_C TException();
	IMPORT_C TInt Bind(TUint32 aMask);
	IMPORT_C void UnBind();
public:
	// Handler returns ETrue if the exception was handled
	virtual TBool Service(TInt anId, const TExcInfo& anInfo, TAny* aContext, TInt anError)=0;
public:
	TUint32 iMask;
    TDblQueLink iLink;
	friend class Exc;
	};
//
class TInternalRamDrive
	{
public:
	static TInt Create();
	IMPORT_C static DPlatChunk *TheInternalRamChunk(); 
	IMPORT_C static TInt Adjust(TInt aNewSize);
private:
	};
//
// Platform private functions and data.
//
class PP
	{
public:
	enum TPlatPanic
    	{
		EIniCreateSecondary=0,
		EIniProtectSecondary=1,
		ESemInitialCountNegative=2,
		ESemSignalCountNegative=3,
		ESegMaxSizeExceeded=4,
		EThrdTypeUnknown=5,
		EThrdAddressInvalid=6,
		EThrdSuicideIllegal=7,
		EThrdDeadIllegal=8,
		EThrdStatusUnknown=9,
		EThrdProtected=10,
		EProcRemoveChunk=11,
		EProcResumeNotLoaded=12,
		EProcBadChunkType=13,
		EProcProtected=14,
		EDevOrdinalZero=15,
		EHalInvalidStartupReason=16,
		EPanicForNoReasonAtAll=17,
		EHalCreateXYInputFailed=18,
		EPicIdNumberInvalid=19,
		EPicIntNotBound=20,
		EIntAlreadyBound=21,
		EExcIdNumberInvalid=22,
		EExcExcNotBound=23,
		EExcAlreadyBound=24,
		EMmuOutOfMemory=25,
		EMmuNotPDEAligned=26,
		EMmuRegionAlreadyExists=27,
		EMmuHWSizeNotPageMultiple=28,
		EMmuHWBaseNotPageMultiple=29,
		EMmuTooManyPagesPreAllocated=30,
		EMmuReservePagesInvalid=31,
		EMmuInvalidPhysicalAddress=32,
		EMmuInvalidPagePoolAddress=33,
		EMmuMappingInvalidLinearAddress=34,
		EMmuMappingInvalidPhysicalAddress=35,
		EMmuMarkPageInvalidLinearAddress=36,
		EMmuFreeInvalidPDEAddress=37,
		EMmuDebugMappingInvalidLinearAddress=38,
		EMmuDebugMappingInvalidPhysicalAddress=39,
		EMmuPageTableNotPresentInDebug=40,
		EMmuInvalidLargerCommittedSize=41,
		EMmuShrinkingRegionUnexpectedly=42,
		EMmuLargerCommittedTooLarge=43,
		EMmuInvalidSmallerCommittedSize=44,
		EMmuGrowingRegionUnexpectedly=45,
		EMmuInvalidHWLinAddrToMap=46,
		EMmuInvalidHWPhysAddrToMap=47,
		EMmuGettingInvalidRegion=48,
		EMmuInvalidNewSize=49,
		EMmuInvalidNewBaseAddress=50,
		EMmuInvalidOldBaseAddress=51,
		EMmuInvalidLowAddress=52,
		EMmuInvalidHomeAddress=53,
		EMmuInvalidNewLowAddress=54,
		EMmuInvalidHomeAddress2=55,
		EMmuIsFreeBaseNotPageMultiple=56,
		EMmuIsFreeSizeNotPageMultiple=57,
		EMmuInvalidHWLinAddrToUnMap=58,
		EMmuGrowRegionInPlace=59,
		EMmuInvalidRomAddress=60,
		EMmuResizeToZero=61,
		EMmuKernelGrowingMoreThanOneChunk=62,
		EMmuPageTableInLockedArea=63,
		EHwChunkExists=64,
		EMmuInvalidPageTableAddress=65,
 		EKemmuInvalidPDE=66,
		EKemmuInvalidPDE2=67,
		EKemmuInvalidPDE3=68,
		EKemmuInvalidPDE4=69,
		EKemmuInvalidPhysAddr=70,
 		EKemmuInvalidPhysAddr2=71,
		EKemmuAddrOutOfRange=72,
		EKemmuAddrOutOfRange2=73,
		EKemmuAddrOutOfRange3=74,
		EKemmuAddrOutOfRange4=75,
		EKemmuAddrOutOfRange5=76,
		EKemmuAddrOutOfRange6=77,
		EMmuInvalidAlloc=78,
		ETHeapCreateSizeTooSmall=79,
		ETHeapMaxLengthNegative=80,
		ETHeapMutateNotSame=81,
		EDllMoving=82,
		EMilliSecondCallBackAlreadyQueued=83,
		EMilliSecondCountExpiredUnexpectedly=84,
		EMmuRegionNotNull=85,
		EMmuSizeIsZero=86,
		EBadWriteAddress=87,
		EInvalidThreadType=88,
        EIllegalWsProcess=89,
        EIllegalWsSwitchOnScreen=90,
		ESystemThreadPanic=91,
		EFixedChunkMoving=92,
		EBadRamAreaSize=93,
		EMaxRamAreasExceeded=94,
		EPageAllocatorCreateFailed=95,
		EPageTableAllocatorCreateFailed=96,
		EPageTableLinearAllocatorCreateFailed=97,
		EInvalidPageTableAfterBoot=98,
		EDomainAllocatorCreateFailed=99,
        EVariantInitialisation=100,
		EPicPrevIntNotBound=101,
		EDmaSrcCrossesPhysicalPageBoundary=102,
		EDmaDestCrossesPhysicalPageBoundary=103,
		EDmaCountTooBig=104,
		EDmaInvalidChannel=105,
		EDmaUnBindWhileInUse=106,
		EDmaChannelBusy=107,
		EUnTrapKWithoutTrap=108,
		EDmaTransferZeroBytes=109,
		EMmuMmuUsedInSingleBuild=110,
		EDmaCountNotAligned=111,
		EDmaSrcNotAligned=112,
		EDmaDestNotAligned=113,
		EDmaBufferNotAligned=114,
		ESvrReceiveNotPending=115,
		ESvrReceiveAlreadyPending=116,
		ESvrMessageAlreadyWaiting=117,
		ESvrMessageCompletion=118,
		EStartExtensionsFailed=119,
		EIdleSleepTooLong=120,
		ECodeMoving=121,
		ETransferBufferTypeAlreadyDecided=122,
		};
	enum TPlatFault
    	{
		ESystemException=0x10000000,
		ESoftwareWarmReset=0x10000001
    	};
public:
	static void Panic(TPlatPanic aPanic);
	static void Fault(TPlatFault aFault);
	static TBool SuperPageSignatureValid();
	static void SetSuperPageSignature();
public:
	static TScheduler TheScheduler;
	static TSupervisor Supervisor;
//
	static TPriQue<DPlatChunk> ChunkQueue;
	static TPriQue<DPlatChunkHw> HwChunkQueue;
	static DPlatChunkHw* VideoChunkHw;
//
	static TInt KernCSLocked;
	static TInt TimeCSLocked;
	static TInt TimeTickPending;
//
	static TBool ColdStart;
//
	static TInt PicMaxVectors;
	static TInterrupt **PicVectorTable;
//
	static TDblQue<TException> ExceptionHandlers;
//
	static TInt DmaMaxChannels;
	static TDma **DmaChannelTable;
//
	static TUint32 *NullStackTop;
//
	static DPlatChunk *TheRamDriveChunk;
//
	static CSecurityBase *ThePassword;
//
	static TBool PasswordEnabled;
//
	static DPlatThread* TheKernelThread;
	static DPlatThread* TheFileServerThread;
	static DPlatThread* TheWindowServerThread;
	static DPlatProcess* TheFileServerProcess;
	static DPlatProcess* TheWindowServerProcess;
//
	static TInt XtalErrorAcc;
//
    static TBool WsSwitchOnScreenHandling;
//
	static TInt MachineCurrent[2];	// [0]=idle current, [1]=running current
	static TInt SvStackMinSize;
	static TLinAddr HomeSectionBase;
	static TLinAddr HomeSectionEnd;
	static TLinAddr HomeSectionSize;
	static TLinAddr RomRootDirectoryAddress;
	static TLinAddr HardwareSectionBase;
	static TLinAddr HardwareSectionEnd;
//
	static TBool MouseOn;
	static TBool MouseButtonDown;
	static TUint8 MouseSpeed;
	static TUint8 MouseAcceleration;
//
	static TSize DisplaySizeInPixels;
	static TSize PhysicalScreenSize;
	static TInt MaximumDisplayColors;
	};
//
inline const TRomHeader &TheRomHeader();
inline const TRomImageHeader &RomImageHeader(TLinAddr anAddr);
inline void ReScheduleNeeded();
//
GLREF_D DPlatThread *TheCurrentThread;
GLREF_D DPlatThread *TheOldThread;
GLREF_D DPlatProcess *TheCurrentProcess;
GLREF_D DPlatProcess *TheCurrentVMProcess;
GLREF_D DPlatProcess *TheCurrentDataSectionProcess;
GLREF_D DPlatProcess *TheICachedUserVMProcess;
GLREF_D TBool ReScheduleNeededFlag;
GLREF_D TBool RealTimeReScheduleFlag;
GLREF_D TBool InSlowExec;
GLREF_D TBool CacheFlushNeededFlag;
GLREF_D	TBool ExecMutateFlag;
GLREF_D TCpuTime DfcRescheduleTime;

class Arch
    {
public:
    IMPORT_C static TAny* Variant();
    };

class Custom;
typedef Custom* (*TVariantInitialise)();
class A
    {
public:
    static void SetVariant(Custom* aVariant);
    inline static Custom* Variant();
private:
    static Custom* TheVariant;
    };

#include <m32std.inl>
#endif

