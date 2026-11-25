// M32HAL.H
//
// Copyright (c) 1995-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __M32HAL_H__
#define __M32HAL_H__
#include <m32std.h>
#include <m32addr.h>

//
typedef TUint32 TPhysAddr;
typedef TUint32 TPhyAddr;
typedef TUint32 TPde;
typedef TUint32 TPte;
//
// Useful addresses

const TPhysAddr KRomPhysAddrInvalid=0xFFFFFFFFu;
const TPhysAddr KPhysAddrInvalid=0xFFFFFFFFu;
const TInt KMaxRamBanks=32;
const TInt KMaxRamAreas=64;

//
class DPlatThread;
class DPlatChunkHw;
class ImpMmu
	{
public:
	enum TMmuUnmapMode { EPageFree=0, EPageUnmapOnly };
	static TUint32 RoundToPageSize(TUint32 aSize);
	static TUint32 RoundToChunkSize(TUint32 aSize);
	IMPORT_C static TPhysAddr LinearToPhysical(TLinAddr aLinearAddress);
	static void FlushShadow();
	static void FlushReSchedule();
	static void FlushUnmap(TBool aCode);
	IMPORT_C static void IMB_Range(TLinAddr aBase, TUint aSize);
	IMPORT_C static void FlushDataBeforeDma(TLinAddr anAddr, TUint aBufferSize);
	IMPORT_C static void FlushDataAfterDma(TLinAddr anAddr, TUint aBufferSize);
	static void ApplyTopLevelPermissions(TLinAddr anAddr, TUint aChunkSize, TPde aPermissions);
	static void ApplyPagePermissions(TLinAddr anAddr, TUint aChunkSize, TPte aPermissions);
	static void ApplyAllPermissions(TLinAddr anAddr, TUint aChunkSize, TPde aTopLevelPerm, TPte aPagePerm);
	static void MoveChunk(TLinAddr anInitAddr, TUint aSize, TLinAddr aFinalAddr, TPde aPermissions);
	IMPORT_C static TInt RemoveRamPages(TInt aConsecutive,TPhysAddr& anAddr,TInt& aPageNo);
	static void UnlockPageTables();
	static void LockPageTables();
	IMPORT_C static TInt AllocatePageTable(TLinAddr aPageAddr, TPde aPdePerm, TBool aShadow);
	IMPORT_C static void FreePageTable(TInt aPdeIndex, TBool aShadow);
protected:
	static void Init1();
	static void Init2();
	static void InvalidateTLBForPage(TLinAddr anAddr);
	static TInt AllocShadowPage(TLinAddr aRomAddr);
	static TInt FreeShadowPage(TLinAddr aRomAddr);
	static TInt FreezeShadowPage(TLinAddr aRomAddr);
	static TInt MapRamPages(TLinAddr aBase, TInt anInitPageNum, TInt aNumPages, TPde aTopLevelPerm, TPte aPagePerm);
	static void UnmapPage(TLinAddr aPageAddr, TMmuUnmapMode aUnmapMode=EPageFree);
	static TInt MapPage(TLinAddr aLinAddr, TPhysAddr aPhysAddr, TPde aTopLevelPerm, TPte aPagePerm);
	static TInt RecoverRamDrive();
	static void ClearRamDrive();
	static TLinAddr GetPageTableLinearAddress(TPhysAddr aPageTable);
	static TInt PagesToEndOfPageTable(TLinAddr aLinAddr);
public:
	static TInt PageSizeInBytes;
	static TInt PageSizeMinus1;
	static TInt PageSizeShift;
	static TInt ChunkSizeInBytes;
	static TInt ChunkSizeMinus1;
	static TInt ChunkSizeShift;
	static TInt NumberOfRamPages;
	static TInt PageTableSizeInBytes;
	static TInt PageTableSizeMinus1;
	static TInt PageTableSizeShift;

	enum TFlushFlags	{
						EFlushDTLB=0x20000000,		// =DPlatProcess::EVariableAccess
						EFlushDCache=0x40000000,	// =DPlatProcess::EMoving
						EFlushITLB=0x04000000,		// =DPlatProcess::EVariableCode
						EFlushICache=0x10000000,	// =DPlatProcess::EMovingCode
						};
	static TInt FlushFlags;
protected:
	struct SPageTableInfoEntry
		{
		TUint16 iPagesPresent;
		TUint16 iPageTableId;
		};

	struct TBankData
		{
		TPhysAddr iBase;
		TInt iSize;
		TInt iBasePageNum;
		};

	static inline SPageTableInfoEntry* PageTableInfo()
		{return ((SPageTableInfoEntry*)KPageTableInfoLinearAddress);}
	static inline SPageTableInfoEntry& PageTableInfo(TInt aPdeIndex)
		{return ((SPageTableInfoEntry*)KPageTableInfoLinearAddress)[aPdeIndex];}
	static CBitMapAllocator* PageAllocator;
	static CBitMapAllocator* PageTableAllocator;
	static CBitMapAllocator* PageTableLinearAllocator;
	static TInt NumRamBanks;
	static TBankData* Bank;
	static TInt RamAreaSizeShift;
	static TInt RamAreaSizeInPagesMinus1;
	static TPhysAddr* RamAreaBase;
private:
	static void SetNewThreadContext(DPlatThread* aThread);
	friend TPte& PageTableEntry(TLinAddr aLinAddr);
	friend class TScheduler;
	};
//
class Mmu : public ImpMmu
	{
public:
	static void Init1();
	static void Init2();
	static TInt CommitRam(TLinAddr aBase, TInt aSize, TPde aTopLevelPerm, TPte aPagePerm);
	static void FreeRam(TLinAddr aBase, TInt aSize);
	static TInt MapPages(TLinAddr aLinAddr, TPhysAddr aPhysAddr, TInt aSize, TPde aTopLevelPerm, TPte aPagePerm);
	static void UnmapPages(TLinAddr aBase, TInt aSize, TMmuUnmapMode aUnmapMode=EPageFree);
	IMPORT_C static TInt AllocShadowPage(TLinAddr aRomAddr,TPhysAddr& aPage);
	IMPORT_C static TInt FreeShadowPage(TLinAddr aRomAddr,TPhysAddr aPage);
	IMPORT_C static TInt FreezeShadowPage(TLinAddr aRomAddr);
    IMPORT_C static void ReMap(TLinAddr anAddrL,TPhyAddr anAddrP);
    IMPORT_C static void MapRomL(TLinAddr anAddrL,TPhyAddr anAddrP,TInt aSize);
	static TPhysAddr GetRomPhysAddr(TLinAddr aRomAddr);
	static TInt PageNumber(TPhysAddr aPageAddr);
	static TPhysAddr PagePhysAddr(TInt aPageNumber);
	static TInt FreeRamInBytes();
private:
	static void DoFreeRam(TLinAddr aBase, TInt aSize);
	};
//
class ImpPsu
	{
public:
	static void Init1();
	static void Init3();
//
    static TBool ExternalPowerPresent();
    static TInt MainBatteryMaxMilliVolts();
    static TInt BackupBatteryMaxMilliVolts();
    static TSupplyStatus MainBatteryStatus();
    static TInt MainBatteryMilliVolts();
    static TSupplyStatus BackupBatteryStatus();
    static TInt BackupBatteryMilliVolts();
    static void CheckPowerSupplies();
	};
//
class Psu : public ImpPsu
	{
public:
	static void Init1();
	static void Init3();
	};
//
class ImpPic
	{
protected:
	static void Init1();
	static void Init3();
	static TInt GetID(const TDesC8& aName);
	static void Eoi(TInt anID);
	static void DoDisable(TInt anID);
	static void DoEnable(TInt anID);
	static void DoClear(TInt anID);
	};
//
class TInterrupt;
class Pic : public ImpPic
	{
private:
	enum TIntIdType {ENotBound=0xFF};
public:
	static void Init1();
	static void Init3();
	static void Dispatch(TInt anID);
private:
	static TInt Bind(TInterrupt& anInterrupt, const TDesC8& aName);
	static void UnBind(TInterrupt &anInterrupt);
	static void CheckedDisable(TInt anID);
	static void CheckedEnable(TInt anID);
	static void Disable(TInt anID);
	static void Enable(TInt anID);
	static void Clear(TInt anID);
	friend class TInterrupt;
	};
//
class ImpExc
	{
protected:
	static void Init1();
	static void Init3();
protected:
	static TInt GetID(TExcType aType);
	enum TExcAction {EExcActionNonCritical, EExcActionCritical, EExcActionFatal };
	static TExcAction CheckCritical(TInt anID, const TExcInfo& anInfo, TAny* aContext, TInt aLock);
	static TInt AdjustRegisters(TAny* aContext);
	};
//
class TException;
class Exc : public ImpExc
	{
public:
	static void Init1();
	static void Init3();
	static void Dispatch(TInt anID, const TExcInfo &anInfo, TAny* aContext, TInt aLock);
	static void Fault(TInt anID, const TExcInfo &anInfo, TAny* aContext, TInt aLock);
	friend class TException;
	};
/**
 * Implementation of DMA
 */
class ImpDma
	{
public:
#if defined(__MHELEN__)
    /* Define the Helen Device supporting the DMA */
    enum TDmaDevice
	{
        EUartBT  ,  // Bluetooth UART
        EUartCom ,  // Com UART
        EUartGiga,  // Gigacell UART
        EComMcBsp,  // Com McBsp
        ECamera  ,  // Camera IF
        EUsbChannel0,  // USB channel 0 (TX/RX)
        EUsbChannel1,  // USB channel 0 (TX/RX)
        EMmc     ,  // Memory Card
        EuWire   ,  // MicroWire
	};
#else
	enum TDmaDevice
		{
		// Generic DMA devices
		ERam, EFlash, ESerialFlash,
		EIr1M, EIr4M, EUart, EUart2,
		EMultiMediaCard, ECodec, EUdc,
		// Platform specific DMA devices not in this generic list
		// are assigned identifiers in the ASSP layer and exported
		// to the variant
		};
#endif
	enum TDmaBufferMode { ESingleBuffer, EDoubleBuffer, EScatterGather };
	enum TDmaState { ERunning, EStall, EError, EBufferEmpty, ELastBuffer };
public:
	static void Init1();
	static void Init3();
	static TDmaBufferMode BufferMode();
	static TInt MaxBlockSize();
	// interrupt functions
	static TInt GetChannel(TDmaDevice aDevice);
	static TPtrC8 GetInterrupt(TInt aChannel);
	static void ClearInterrupt(TInt aChannel);
	static TDmaState GetState(TInt aChannel);
	// HW dma-block management
	static void InitialiseCopy(TInt aChannel, TDmaDevice aDevice, TPhysAddr aSrc, TPhysAddr aDest);
	static void InitialiseTransmit(TInt aChannel, TDmaDevice aDevice);
	static void InitialiseReceive(TInt aChannel, TDmaDevice aDevice);
	static void BlockCopy(TInt aChannel, TPhysAddr aSrc, TPhysAddr aDest, TInt aCount);
	static void BlockTransmit(TInt aChannel, TDmaDevice aDevice, TPhysAddr aBuffer, TInt aCount);
	static void BlockReceive(TInt aChannel, TDmaDevice aDevice, TPhysAddr aBuffer, TInt aCount);
	static void BlockFill(TInt aChannel, TDmaDevice aDevice, TPhysAddr aBuffer, TInt aCount);
	static void FinalBlock(TInt aChannel);
	};
class TDma;
class Dma : public ImpDma
	{
private:
	enum {ENotBound=KErrNotFound};
public:
	static TInt Bind(TDma &aDma, TDmaDevice aDevice);
	static void UnBind(TDma &aDma);
	friend class TDma;
	};
//
class ImpMilliSecondTimer
    {
public:
    static TInt CountFromMilliSeconds(TInt aMilliSeconds);
protected:
    static void Init3();
    static TInt Count();
    static void Start(TInt aCount);
    static void Next(TInt aCount);
    static void Stop();
    };
//
class TMilliSecondCallBack;
class MilliSecondTimer : public ImpMilliSecondTimer
    {
public:
    static void Init3();
    static void Enque(TMilliSecondCallBack* aCallBack);
	static void Deque(TMilliSecondCallBack* aCallBack);
    IMPORT_C static void CountExpired();
public:
	static TBool Active;
private:
	enum TRemoveResult	{ ENotPresent, EWasNotQueueHead, EWasQueueHead };

    static TBool AddToQueue(TMilliSecondCallBack* aCallBack);
	static TRemoveResult RemoveFromQueue( TMilliSecondCallBack *aCallBack );
    static TBool Expired;
    static TBool Locked;
	static TMilliSecondCallBack* Head;
    };
//
typedef void (*TPartnerOSFunction)(void);
typedef TInt (*TPartnerOSCheckFunction)(void);

class TPartnerOS
	{
public:
	TPartnerOSFunction		iBeforeSwiDispatch;
	TPartnerOSCheckFunction	iAfterSwiDispatch;
	TPartnerOSCheckFunction	iAfterSwiReschedule;
	TPartnerOSFunction		iBeforeIrqDispatch;
	TPartnerOSCheckFunction	iAfterIrqDispatch;
	TPartnerOSCheckFunction	iAfterIrqReschedule;
	TPartnerOSFunction		iBeforeFiqDispatch;
	TPartnerOSCheckFunction	iAfterFiqDispatch;
	TPartnerOSCheckFunction	iAfterFiqReschedule;
	};
//
class DPlatProcess;
class DPlatChunk;

/**
 * Hal Implementation class
 */
class ImpHal
	{
public:
	static void Init1();
	static void Init3();
	static void Init4();
	static void Init5();
	static void PrepareForRepro();
	static TInt InitSystemTime(const TTime& aTime);
	static DPlatProcess* NewProcessL(TInt aAttributes);
	static DPlatChunk* NewChunkL(TBool aGlobal, TChunkType aType, DProcess *aProcess);
	static TPde PdePermissions(TChunkType aChunkType, TInt aChunkState);
	static TPte PtePermissions(TChunkType aChunkType);
	static void InitialisationComplete();

	IMPORT_C static TUint ProfileTimer();
	IMPORT_C static TCpuTime ProfileTimeToMicroSeconds(TCpuTime aProfileTime);

// General

	IMPORT_C static void DisableIrqs();
	IMPORT_C static void EnableIrqs();
	IMPORT_C static TUint DebugMask();
	IMPORT_C static void SetDebugMask(TUint32 aVal);
	IMPORT_C static DPlatThread *NewThreadL(TAny *aPlace,TInt aSize);
    IMPORT_C static TInt PreemptionTicks();

	IMPORT_C static void SystemTime(TTime& aTime);
	IMPORT_C static TInt SetSystemTime(const TTime& aTime);
    IMPORT_C static void SystemTimeInSecondsFrom2000(TTimeIntervalSeconds& aSeconds);

	IMPORT_C static TInt IdleCurrentInMilliAmps();
	IMPORT_C static TInt RunningCurrentInMilliAmps();
	IMPORT_C static TBool TestBootSequence();
	IMPORT_C static TBool CaseClosed();

// MachineInfo V1

	IMPORT_C static TInt RamSize();
	IMPORT_C static TXYInputType XYInputType();

    IMPORT_C static TSize XYInputSizeInPixels();
    IMPORT_C static TPoint OffsetToDisplayInPixels();

    IMPORT_C static TInt ProcessorClockInKHz();
    IMPORT_C static TInt SpeedFactor();

// DriveInfo

    static TInt TotalSupportedDrives();
	static TInt DriveSettings();

// UserHal

    IMPORT_C static TInt StartupReason(TMachineStartupType& aReason);
    IMPORT_C static TInt PageSizeInBytes(TInt& aSize);
    IMPORT_C static TInt TickPeriod(TTimeIntervalMicroSeconds32 &aPeriod);

// Exports

	IMPORT_C static TInt DisableIrqsToLevel1();
	IMPORT_C static TInt DisableIrqsToLevel2();
    IMPORT_C static void RestoreIrqs(TInt aLevel);
	IMPORT_C static void Idle();
	IMPORT_C static void UnlockRamDrive();
	IMPORT_C static void LockRamDrive();

// POS butchery
	IMPORT_C static TInt GetPartnerOSVectors(TPartnerOS& aPartnerOS);
	IMPORT_C static TInt SetPartnerOSVectors(const TPartnerOS& aPartnerOS);
	};
//
class Hal : public ImpHal
	{
public:
	static void Init1();
	static void Init3();

//  UserHal

	IMPORT_C static TInt MachineInfo(TMachineInfoV1& aMachineInfo);
	IMPORT_C static TInt MachineInfo(TMachineInfoV2& aMachineInfo);
	IMPORT_C static TInt SupplyInfo(TSupplyInfoV1& aSupplyInfo);
    IMPORT_C static TInt MemoryInfo(TMemoryInfoV1& aMemoryInfo);
	IMPORT_C static TInt DriveInfo(TDriveInfoV1& aDriveInfo);
    IMPORT_C static TInt SetXYInputCalibration(const TDigitizerCalibration& aCalibration);
    IMPORT_C static TInt CalibrationPoints(TDigitizerCalibration& aCalibration);
	IMPORT_C static TInt FaultReason(TInt &aReason);
	IMPORT_C static TInt ExceptionId(TInt &anId);
	IMPORT_C static TInt ExceptionInfo(TExcInfo &aReason);

 // TSupplyInfoV1

    IMPORT_C static TSupplyStatus MainBatteryStatus();
    IMPORT_C static TInt MainBatteryMilliVolts();
    IMPORT_C static TInt MainBatteryMaxMilliVolts();
    IMPORT_C static TSupplyStatus BackupBatteryStatus();
    IMPORT_C static TInt BackupBatteryMilliVolts();
    IMPORT_C static TInt BackupBatteryMaxMilliVolts();
    IMPORT_C static TBool ExternalPowerPresent();
    IMPORT_C static TUint Flags();

// TMachineInfoV2

    IMPORT_C static TVersion RomVersion();
    IMPORT_C static TXYInputType XYInputType();
    IMPORT_C static TSize XYInputSizeInPixels();
    IMPORT_C static TPoint OffsetToDisplayInPixels();

// TMemoryInfoV1

    IMPORT_C static TInt TotalRamInBytes();
    IMPORT_C static TInt TotalRomInBytes();
    IMPORT_C static TInt MaxFreeRamInBytes();
    IMPORT_C static TInt FreeRamInBytes();
    IMPORT_C static TInt InternalDiskRamInBytes();
    IMPORT_C static TBool RomIsReprogrammable();

// Exports

	IMPORT_C static TBool ColdStart();
	IMPORT_C static TInt AddProtected(TInt &aCounter,TInt aValue);
	IMPORT_C static void WaitMilliSeconds(TInt aMilliSeconds);
	IMPORT_C static TInt TickPeriod(TTimeIntervalMicroSeconds32 &aPeriod);
	IMPORT_C static void MapRom(TLinAddr anAddrL,TPhyAddr anAddrP,TInt aMapSize,TInt aRealSize);
	IMPORT_C static TCpuTime DfcRescheduleCpuTime();
	IMPORT_C static void SetVideoChunkHw(DPlatChunkHw* aChunk);
	IMPORT_C static void SetDisplaySizeInPixels(const TSize& aSize);
	IMPORT_C static void SetPhysicalScreenSize(const TSize& aSize);
	IMPORT_C static void SetMaximumDisplayColors(TInt aMaxColors);
	};
//

#endif

