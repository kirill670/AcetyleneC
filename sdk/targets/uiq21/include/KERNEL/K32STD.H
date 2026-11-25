//
// K32STD.H
//
// Copyright (c) 1994-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __K32STD_H__
#define __K32STD_H__
#include <e32std.h>
#include <e32base.h>
#include <e32hal.h>
#include <e32rom.h>
#include <e32ver.h>
#include <e32svr.h>
#include <u32std.h>
#include <e32transbuf.h>
#if defined(__EPOC32__)
# include <m32addr.h>
#endif
#include <k32power.h>

//
// Useful constants
//
const TUint32 KBit0= 0x00000001;
const TUint32 KBit1= 0x00000002;
const TUint32 KBit2= 0x00000004;
const TUint32 KBit3= 0x00000008;
const TUint32 KBit4= 0x00000010;
const TUint32 KBit5= 0x00000020;
const TUint32 KBit6= 0x00000040;
const TUint32 KBit7= 0x00000080;
const TUint32 KBit8= 0x00000100;
const TUint32 KBit9= 0x00000200;
const TUint32 KBit10=0x00000400;
const TUint32 KBit11=0x00000800;
const TUint32 KBit12=0x00001000;
const TUint32 KBit13=0x00002000;
const TUint32 KBit14=0x00004000;
const TUint32 KBit15=0x00008000;
const TUint32 KBit16=0x00010000;
const TUint32 KBit17=0x00020000;
const TUint32 KBit18=0x00040000;
const TUint32 KBit19=0x00080000;
const TUint32 KBit20=0x00100000;
const TUint32 KBit21=0x00200000;
const TUint32 KBit22=0x00400000;
const TUint32 KBit23=0x00800000;
const TUint32 KBit24=0x01000000;
const TUint32 KBit25=0x02000000;
const TUint32 KBit26=0x04000000;
const TUint32 KBit27=0x08000000;
const TUint32 KBit28=0x10000000;
const TUint32 KBit29=0x20000000;
const TUint32 KBit30=0x40000000;
const TUint32 KBit31=0x80000000;

const TUint32 KSet32=0xffffffff;
const TUint32 KClear32=0x00000000;

const TInt KKilo=1024;
const TInt KMega=1024*1024;

//
// The only reason the kernel server should leave to shoot the client
//
const TInt KErrKernelServerLeave=0xcccccccc;
const TInt KErrExceptionLeave=0xcccccccd;
//
// The supervisor heap size
//
const TInt KKernelHeapSize=0x20000;
//
// Special server handles
//
const TInt KSvCurrentProcessHandle=0xffff0002;
const TInt KSvCurrentThreadHandle=0xffff0003;
//
// The CDevice::Create and CDevice::IsAvailable parse masks
//
const TUint KDeviceAllowUnit=0x01;
const TUint KDeviceAllowPhysicalDevice=0x02;
const TUint KDeviceAllowInfo=0x04;
const TUint KDeviceAllowAll=(KDeviceAllowUnit|KDeviceAllowPhysicalDevice|KDeviceAllowInfo);
//
// The number of requests supported per device driver
//
const TInt KMaxRequests=0x6;
//
const TInt KNoHeap=(-1);
//
// Chunk creation enumerates
//
enum TChunkType
	{
	// these never change or move or anything
	EDummy,			// Supervisor,Ro,Cacheable
	ECreating,		// User,Rw,Cacheable
	EKernelData,	// Supervisor,Rw,Cacheable
	EKernelStack,	// Supervisor,Rw,Cacheable
	EKernelCode,	// Supervisor,Rw,Cacheable
	EDll,			// User,Ro,Cacheable

	// This changes on a PDE basis when the file server runs
	ERamDrive,		// Supervisor,Rw,Cacheable

	// these change on PDE basis when run
	EUserCode,
	EUserData,
	EDllData,

	// the debugger changes on a page basis
	EDebugger,			// User,Rw,Cacheable
	EDebuggerUserRom,	// User,Ro,Cacheable (from above via PDE change)
	EDebuggerWatch,		// Supervisor, Ro

	// following are "vanilla" for use by HW chunks
	EHwUserRw,
	EHwUserRoNotBuff,
	EHwSupRw,
	EHwSupRoNotBuff,
	EHwUserRwNotBuffCache,
	EHwUserRoNotBuffCache,
	EHwSupRwNotBuffCache,
	EHwSupRoNotBuffCache,
	EHwUserRwNotCache,
	EHwSupRwNotCache,
	EHwUserRwNotBuff,
	EHwSupRwNotBuff,

	EUserSelfModCode,
	};
//
// Thread creation types
//
enum TThreadCreateType {EThreadSupervisor,EThreadNull,EThreadUser,EThreadRealTime};
//
// unsigned native 64-bit type for CpuTime calculations
//
#ifdef __GCC32__
typedef unsigned long long TCpuTime;
#else
typedef __int64 TCpuTime;
#endif
//
//
const TInt KMemoryNotifyGood=1;
const TInt KMemoryNotifyLow=2;
const TInt KMemoryNotifyFail=4;
//
// Kernel message
//
struct TFatUtilityFunctions;
class DThread;
class DSession;
class DSessionShare;
class TMessageSlot;
class TDisconnectMessage;
class TMessageBase
	{
protected:
	inline TMessageBase();
public:
	inline TBool IsFree() const;
	inline TBool IsDelivered() const;
	inline TBool IsAccepted() const;
	inline TBool IsSlot() const;
	inline TMessageSlot& MessageSlot();
	inline TDisconnectMessage& DisconnectMessage();
public:
	TDblQueLink iDelivery;
	TInt iFunction;
	};
class TMessagePool
	{
public:
	inline TMessagePool();
	TMessageSlot* Allocate(TInt aSize);
	inline TBool IsEmpty() const;
	inline void Put(TMessageSlot& aSlot);
	inline TMessageSlot& Get();
private:
	TMessageSlot* iFree;
	};
class TMessageSlot : public TMessageBase
	{
public:
	TMessageSlot(TMessagePool* aPool=0);
	TInt Complete(TInt aReason);
	void Release();
public:
	TInt iArgs[KMaxMessageArguments];
	DSessionShare* iShare;
	TRequestStatus *iStatus;
	TDblQueLink iOwner;
	TMessagePool* iPool;
	};
class TDisconnectMessage : public TMessageBase
	{
public:
	inline TDisconnectMessage();
public:
	DSession* iSession;
	};
//
// Delayed function call class
//
class TDfc
	{
public:
	IMPORT_C TDfc(const TCallBack &aCallBack);
	IMPORT_C void Cancel();
	inline void CallBack() const;
	inline void Deque();
	inline TBool Queued();
public:
	TDfc *iNext;
	TDfc *iPrev;
	TCallBack iCallBack;
	friend class TDfcQue;
	};
//
// The Dfc queue
//
class TDfcQue
	{
public:
	TDfc *iFirst;
	TDfc *iLast;
public:
	TDfcQue();
	inline TBool IsEmpty();
	};
//
// Timer classes
//
typedef void (*TTickCallBack)(TAny *aPtr,TInt aDelay);
class TTickQ;
class TTickLink : public TDeltaQueLink
	{
public:
	IMPORT_C TTickLink();
	IMPORT_C void PeriodicInMicroSeconds(TTimeIntervalMicroSeconds32 aPeriod,TTickCallBack aCallBack,TAny *aPtr,TBool aRegulated=EFalse);
	IMPORT_C void OneShotInMicroSeconds(TTimeIntervalMicroSeconds32 aTime,TTickCallBack aCallBack,TAny *aPtr);
	IMPORT_C void Lock(TInt aTicks,TTickCallBack aCallBack, TAny *aPtr);
	IMPORT_C void Cancel();
	IMPORT_C TInt GetNextLock(TTimerLockSpec aMark, TInt &aTickCount) const;
public:
	TUint iLastLock;
private:
    TBool iRegulated;
	enum {EOneShotTimer = 0, ELockTimer = -1}; // iPeriod for non-periodics
	TInt iPeriod;
	TAny *iPtr;
	TTickCallBack iCallBack;
	friend class TTickQ;
	};
//
class TSecondQ;
class TTickQ : public TDeltaQue<TTickLink>
	{
public:
    TTickQ();
    void Tick(TInt aBatch);
    void StartSecondQueue(TSecondQ* aQueue);
    void WakeUp();
	TBool CheckMidnightCrossover(TInt aSecs);
	TInt SecondsToMidnight() const;
	TBool UpdateSecondQAfterSleep();
    static void SystemTimeChanged();
	TInt GetIdleTime(TBool aIgnoreLocked);
public:
    TSecondQ* iSecondQueue;
    TInt iLastTimeInSecs;
	TInt iTomorrowStarts;
	TBool iForceInactivityTick;
	};
//
typedef void (*TSecondCallBack)(TAny *aPtr);
class TSecondQ;
class TSecondLink : public TDeltaQueLink
	{
public:
	IMPORT_C TSecondLink();
	IMPORT_C TInt At(const TTime &aHomeTime,TSecondCallBack aCallBack,TAny *aPtr);
	IMPORT_C void Cancel();
private:
	TTime iTime;
	TAny *iPtr;
	TSecondCallBack iCallBack;
	friend class TSecondQ;
	};
//
class TSecondQ : public TDeltaQue<TSecondLink>
	{
public:
	void Tick();
	static void SystemTimeChanged();
	static void SystemTimeChanged(TUint& aChanges);
	};
//
typedef void (*TInactivityCallBack)(TAny *aPtr);
class TInactivityQ;
class TInactivityLink : public TDblQueLink
	{
public:
	IMPORT_C TInactivityLink();
	IMPORT_C TInt Start(TInt aSeconds, TInactivityCallBack aCallBack, TAny* aPtr);
	IMPORT_C void Cancel();
private:
	TUint iTime;		// timeout period in ticks
	TAny *iPtr;
	TInactivityCallBack iCallBack;
	friend class TInactivityQ;
	};
//
class TInactivityQ : public TDblQue<TInactivityLink>
	{
public:
	TInactivityQ();
	void Tick();
	void Reset();
	TInt InactiveTime();
	TBool FirstDelta(TInt& aDelta);
public:
	TDblQue<TInactivityLink> iPending;	// timers waiting for next event before being requeued
	TUint iLastEventTime;	// tick counter at last user event
	};
//
// The Global Alloc Que
//
class TGlobalAlloc
	{
public:
	static TGlobalAlloc *NewL(TInt aHandle, TInt aSize);
	void ReAllocL(TInt aSize);
	TInt ReadGlobalData(TInt aPos, TInt aLength, TDes8& aTrg);
	TInt WriteGlobalData(TInt aPos, const TDesC8 &aSrc);
private:
	TGlobalAlloc() {}
public:
	TDblQueLink iLink;
	TInt iHandle;
	TPtrC8 iGlobalData;
	};

class TGlobalAllocQ : public TDblQue<TGlobalAlloc>
	{
public:
	TGlobalAllocQ();
	TGlobalAlloc *FindByHandle(TInt aHandle);
	void Delete(TGlobalAlloc *aPtr);
	};
//
// The kernel object definitions
//
class DProcess;
class DTimer : public CObject
	{
public:
	enum TTimerType {ERelative,EAbsolute,ELocked,EInactivity};
public:
	DTimer();
	~DTimer();
	void Create(DThread *aThread);
	IMPORT_C void Cancel();
	IMPORT_C void Abort();
	IMPORT_C void AbortAbsolute();
	IMPORT_C void AbortLocked();
	IMPORT_C void After(TRequestStatus &aStatus,TTimeIntervalMicroSeconds32 anInterval);
	IMPORT_C void At(TRequestStatus &aStatus,const TTime &aTime);
	IMPORT_C void Lock(TRequestStatus &aStatus, TTimerLockSpec aLock);
	IMPORT_C void Inactivity(TRequestStatus& aStatus, TInt aSeconds);
	static void TimerComplete(TAny *aPtr,TInt aDelay);
	static void SecondComplete(TAny *aPtr);
	static void LockComplete(TAny *aPtr, TInt aDelay);
	static void LockSynchronize(TAny *aPtr, TInt aDelay);
private:
	TRequestStatus *iStatus;
	TTimerType iType;
	TTickLink iTimer;
	TSecondLink iSecond;
	TInactivityLink iInactivity;
	DThread *iOwningThread;
	friend void TSecondQ::SystemTimeChanged();
	};
//
class DChangeNotifier : public CObject
	{
public:
	DChangeNotifier();
	~DChangeNotifier();
	IMPORT_C void Notify(TUint aChanges);
	IMPORT_C TInt Logon(TRequestStatus& aStatus,const DThread& aThread);
	IMPORT_C TInt LogonCancel(const DThread& aThread);
private:
	TUint iChanges;
	TRequestStatus* iStatus;
	const DThread* iThread;
	};
//
class DUndertaker : public CObject
	{
public:
	DUndertaker();
	~DUndertaker();
	IMPORT_C void Notify(DThread* aDeadThread);
	IMPORT_C TInt Logon(TRequestStatus *aStatus,TInt* aDeadThreadHandle);
	IMPORT_C TInt LogonCancel();
	void Complete(TInt aValue,DThread* aDeadThread);
	inline TRequestStatus* RequestStatus();
	inline DThread* OwningThread();
private:
	TRequestStatus *iStatus;
	DThread* iOwningThread;
	TInt* iDeadThreadHandle;
	};
//
class DChunk : public CObject
	{
public:
	~DChunk();
	virtual void Close();
	inline TInt Size() const;
	inline TInt MaxSize() const;
	inline TUint8 *Base() const;
	inline TInt Bottom() const;
	inline TInt Top() const;
	inline void SetHeapInfo(TInt aHeapOffset,TInt aRunAddress);
	inline TInt HeapOffset();
	inline DProcess* OwningProcess() const;
	void Create(CObject* anOwner,DProcess* anOwningProcess,const TDesC *aName,TInt aMaxSize,TChunkType aChunkType=EUserData);
	IMPORT_C void Read(TInt aPos,TDes8 * aDes,TInt aMode) const;
	IMPORT_C void Write(TInt aPos,const TDesC8 * aDes,TInt aMode);
// Pure virtual
	virtual void DoCreate(TInt aMaxSize,TChunkType aChunkType)=0;
	virtual void AdjustUserL(TInt aNewSize)=0;
	virtual void AdjustL(TInt aNewSize)=0;
	virtual TInt Adjust(TInt aNewSize)=0;
	virtual TInt AdjustDoubleEnded(TInt aBottom, TInt aTop)=0;
	virtual void SetFinalPagePermissions()=0;
	virtual void Read(TInt aPos,TAny *aPtr,TInt aLength) const =0;
	virtual void Write(TInt aPos,const TAny *aPtr,TInt aLength)=0;
	virtual TInt ReserveAt(TLinAddr aAddr)=0;
protected:
	DChunk();
public:
	DProcess* iOwningProcess;	// NULL for global chunks
	TInt iSize;					// always the committed size
	TInt iMaxSize;
	TInt iHeapOffset;
	TInt iHeapRunAddress;
	TUint8 *iBase;
	CObjectIx *iDlls;			// references to all DLLs used by an EXE code chunk

	enum TChunkAttributes {EDoubleEnded=0x1};
	TInt iAttributes;
	TInt iStartPos;				// start of committed area for double-ended chunks
	friend class S;
	};
//
class DSemaphore : public CObject
	{
public:
	inline TInt Count() const;
	void Create(CObject*anOwner,const TDesC *aName,TInt aCount);
// Pure virtual
	virtual void DoCreate(TInt aCount)=0;
	virtual void Wait()=0;
	virtual void Signal()=0;
	virtual void Signal(TInt aCount)=0;
protected:
	DSemaphore();
protected:
	TInt iCount;
	};
//
class DMutex : public CObject
	{
public:
	inline TInt Count() const;
	void Create(CObject* anOwner,const TDesC *aName);
// Pure virtual
	virtual void DoCreate()=0;
	virtual void Wait()=0;
	virtual void Signal()=0;
protected:
	DMutex();
protected:
	TInt iCount;
	};
//
class DLibrary : public CObject
	{
public:
    ~DLibrary();
	virtual void Close();
	void LoadL(TLoaderInfo& anInfo);
	TName Name() const;
	void FileName(TDes& aFileName) const;
	static DLibrary *LibraryFromHandle(TInt aHandle);
	static void DataInfo(TInt aHandle, TModuleInfo &aInfo);
	static TInt InitialiseData(TInt aHandle, DProcess *aProcess);
	static void FreeData(TInt aHandle, DProcess *aProcess);
// Pure virtual
	virtual void DoLoadL(TLoaderInfo& anInfo) =0;
	virtual void LoadedL(TLoaderInfo& anInfo) =0;
	virtual TLibraryFunction Lookup(TInt anOrdinal) =0;
	virtual void Info(TLoaderInfo& anInfo) =0;
	virtual TLibraryEntry EntryPoint() =0;
	virtual TUint* DllRefTable() =0;
	virtual TInt GetRamSizes(TInt& aCodeSize,TInt& aConstDataSize) =0;
protected:
	DLibrary();
public:
	TLibraryEntry iEntryPoint;
	TDllRefTable* iDllRefTable;
	TUidType iType;
public:
	HBufC *iFileName;
	DLibrary **iDeps;	// libraries on which this one depends
	TInt iDepCount;		// number of dependencies
	TInt iNextDep;
	TBool iBeenHere;	// used during Close()
	RPointerArray<DLibrary> iClientDlls;	// libraries which depend on this one

	TInt AddDependency(DLibrary *aLib);
	void RemoveClient(DLibrary *aLib);
	void RemoveDependency(DLibrary *aLib);
	TBool IsInUse();
	};
//
class DCleanup : public CBase
	{
public:
	enum TCleanupType {EObject,ELogon,EShare};
public:
	DCleanup(TCleanupType aType);
	inline TCleanupType Type();
protected:
	TCleanupType iType;
	TDblQueLink iLink;
private:
	friend class DThread;
	friend class DProcess;
	};
//
class DCleanupObject : public DCleanup
	{
public:
	~DCleanupObject();
	static void NewL(DThread &aThread,CObject *anObject);
	TBool Remove(CObject *anObject);
private:
	DCleanupObject(CObject *anObject);
	CObject *iObject;
	};
//
class DLogon : public DCleanup
	{
public:
	~DLogon();
	DLogon(TRequestStatus *aStatus,DThread *aThread,DThread *aLoggedThread);
	TBool Cancel(TRequestStatus *aStatus,DThread *aThread);
protected:
	TRequestStatus *iStatus;
	DThread *iThread;
	DThread *iLoggedThread;
	};
//
class DLogonProcess : public DCleanup
	{
public:
	~DLogonProcess();
	DLogonProcess(TRequestStatus *aStatus,DThread *aThread,DProcess *aLoggedProcess);
	TBool Cancel(TRequestStatus *aStatus,DThread *aThread);
protected:
	TRequestStatus *iStatus;
	DThread *iThread;
	DProcess *iLoggedProcess;
	};
//
class TTls
	{
public:
	TInt iHandle;
	TAny *iPtr;
	};
//
struct LibQStruct
	{
	TDblQueLink iLibLink;
	DLibrary* iLibrary;
	};
//
class DThread : public CObject
	{
public:
	~DThread();
	void Create(CObject* anOwner,DProcess *anOwningProcess,TThreadCreateType aType,const TDesC &aName,TThreadFunction aFunction,TInt aStackSize,RHeap *aHeap,TInt aHeapMinSize,TInt aHeapMaxSize,TAny *aPtr,TOwnerType anOwnerType);
	IMPORT_C TInt Rename(const TDesC &aName);
	IMPORT_C TThreadPriority Priority() const;
	IMPORT_C void SetPriority(TThreadPriority aPriority);
	IMPORT_C TBool System() const;
	IMPORT_C void SetSystem(TBool aState);
	IMPORT_C TBool Protected() const;
	IMPORT_C void SetProtected(TBool aState);
	IMPORT_C TInt RequestCount() const;
	IMPORT_C void RequestComplete(TRequestStatus * &aStatus,TInt aReason) const;
	IMPORT_C TInt GetDesInfo(const TAny *aDes,TInt &aLength,TInt &aMaxLength,TUint8 * &aPtr,TBool aWriteable);
	IMPORT_C TInt GetDesLength(const TAny *aPtr);
	IMPORT_C TInt GetDesMaxLength(const TAny *aPtr);
	IMPORT_C TInt Read(const TAny * aPtr,TDes8 &aDes);
	IMPORT_C TInt Read(const TAny * aPtr,TDes16 &aDes);
	IMPORT_C TInt Read(const TAny * aPtr,TDes8 * aDes,TInt anOffset,TInt aMode);
	IMPORT_C TInt Write(const TAny * aPtr,const TDesC8 &aDes);
	IMPORT_C TInt Write(const TAny * aPtr,const TDesC16 &aDes);
	IMPORT_C TInt Write(const TAny * aPtr,const TDesC8 * aDes,TInt anOffset,TInt aMode);
	IMPORT_C TInt WriteNoCheck(const TAny * aPtr,const TDesC8 * aDes,TInt anOffset,TInt aMode);
	IMPORT_C void Logon(TRequestStatus *aStatus,DThread *anOwningThread);
	IMPORT_C TInt LogonCancel(TRequestStatus *aStatus,DThread *anOwningThread);
	IMPORT_C void After(TTimeIntervalMicroSeconds32 aTime,TRequestStatus &aStatus);
	IMPORT_C void At(const TTime &aTime,TRequestStatus &aStatus);
	IMPORT_C TInt SetTls(TInt aHandle,TAny *aPtr);
	IMPORT_C TAny *Tls(TInt aHandle);
	IMPORT_C void FreeTls(TInt aHandle);
	IMPORT_C TInt SetExceptionHandler(TExceptionHandler *aHandler,TUint aMask);
	IMPORT_C void ModifyExceptionMask(TUint aClearMask, TUint aSetMask);
	IMPORT_C TInt RaiseException(TExcType aType);
	IMPORT_C TExceptionHandler *ExceptionHandler();
	IMPORT_C TBool IsExceptionHandled(TExcType aType);
	void AddToCleanup(DCleanup &aCleanup);
	void RemoveFromCleanup(CObject *anObject);
	inline DProcess &OwningProcess();
	void DoClose();
	void CloseCreatedHeap();
	TInt StaticCallList(TInt& aCount,TUint*& aCallList);
	TInt DynamicCallList(DLibrary* aLibrary,TInt& aCount,TUint*& aCallList);
	TInt DisjointCallList(DLibrary* aLibrary,TInt& aCount,TUint*& aCallList);
	TBool ProtectThreadP();
	void ProtectThreadL();
	TInt GetRamSizes(TInt& aHeapSize,TInt& aStackSize);
	void AddThread(DThread &aThread);
	void DoDie();
	void MakeThisMainThread();
// Pure virtual
	virtual void DoCreate(TThreadCreateType aType,TInt aStackSize,TThreadFunction aFunction,TAny *aPtr,TOwnerType anOwnerType)=0;
	virtual void SupervisorSend(TInt aFunction,const TInt aPtr[],TRequestStatus *aStatus) =0;
	virtual void SupervisorComplete(TInt aReason) =0;
	virtual void Resume()=0;
	virtual void Suspend()=0;
	virtual void Kill(TInt aReason)=0;
	virtual void Die(TExitType aType,TInt aReason,const TDesC &aCategory)=0;
	virtual void Terminate(TInt aReason)=0;
	virtual void Panic(const TDesC &aCategory,TInt aReason)=0;
	virtual void DoSetPriority(TThreadPriority aPriority)=0;
	virtual TAny* HomeAddress(TAny* anAddress)=0;
	virtual TAny* CurrentAddress(const TAny* anAddress)=0;
	virtual TAny* CurrentAddress(const TAny* anAddress, TInt& aMaxSize)=0;
	virtual TInt Read(const TAny *aPtr,TUint8 *aTrg,TInt aLength)=0;
	virtual TInt Write(const TAny *aPtr,const TUint8 *aSrc,TInt aLength)=0;
	virtual TInt SetInitialParameter(TAny* aPtr)=0;
	virtual TInt CallFunction(TAny *aFunction, TAny *aArg1)=0;
	virtual TInt CallFunction(TAny *aFunction, TAny *aArg1, TAny *aArg2)=0;
	virtual void Context(TDes8 &aDes)=0;
	virtual TInt CpuTime(TTimeIntervalMicroSeconds& aMicroSeconds) const=0;
	inline CObjectIx &Handles();
protected:
	DThread();
	void Cleanup();
public:
	TThreadCreateType iType;
	DProcess* iOwningProcess;
	TThreadPriority iPriority;
	TUint iFlags;
	TExitType iExit;
	TInt iExitReason;
	DChunk *iStackHeapChunk;
	RHeap *iCreatedHeap;
	RHeap *iHeap;
	TTrap *iFrame;
	TTrapHandler *iTrapHandler;
	RArray<TTls> iTls;
	CActiveScheduler *iScheduler;
	DSemaphore *iRequestSemaphore;
	DTimer *iTimer;
	CObjectIx *iHandles;
	TDblQue<DCleanup> iCleanupQ;
	TBufC<KMaxExitCategoryName> iCategory;
    TUint iId;
	TExceptionHandler *iExceptionHandler;
	TUint iExceptionMask;
	TInt iExceptionErrorCode;
	TUint8* iRealTimeStackHeap;
	TInt iRealTimeHeapSize;
	TInt iRealTimeStackSize;
	TDblQueLink iThreadLink;
	TDblQue<DThread> iThreadQ;
	TMessageSlot iSyncMessage;
	};
//
class DProcess : public CObject
	{

public:
	~DProcess();
	void Create(TBool aFirstProcess,TLoaderInfo &anInfo,HBufC *aCommand);
	void DoClose();
	void Cleanup();
	TName Name() const;
	IMPORT_C TInt Rename(const TDesC &aName);
	IMPORT_C void FileName(TDes& aFileName) const;
	IMPORT_C void CommandLine(TDes &aCommand) const;
	IMPORT_C TProcessPriority Priority() const;
	IMPORT_C void SetPriority(TProcessPriority aPriority);
	IMPORT_C TBool System() const;
	IMPORT_C void SetSystem(TBool aState);
	IMPORT_C TBool Protected() const;
	IMPORT_C void SetProtected(TBool aState);
	IMPORT_C TInt MakeHandleToOwningProcess(TInt& aHandle,DProcess* anOwningProcess) const;
	IMPORT_C void SetOwningProcess(TInt aHandle);
	IMPORT_C void Logon(TRequestStatus* aStatus,DThread* anOwningThread);
	IMPORT_C TInt LogonCancel(TRequestStatus* aStatus,DThread* anOwningThread);
	inline CObjectIx &Handles();
	TBool ProtectProcessP();
	void ProtectProcessL();
// Pure virtual
	virtual void DoCreate(TBool aFirstProcess,TLoaderInfo& anInfo)=0;
	virtual void Loaded(TLoaderInfo& anInfo)=0;
	virtual void Resume()=0;
	virtual void Kill(TInt aReason)=0;
	virtual void Terminate(TInt aReason)=0;
	virtual void Panic(const TDesC& aCategory,TInt aReason)=0;
	virtual void DoSetPriority(TProcessPriority aPriority)=0;
	virtual TInt AddFindChunk(DChunk* aChunk)=0;
	virtual TInt AddChunk(DChunk* aChunk,TBool isReadOnly)=0;
	virtual void RemoveChunk(DChunk* aChunk)=0;
	virtual TInt GetRamSizes(TInt& aCodeSize,TInt& aConstDataSize,TInt& anInitialisedDataSize,TInt& anUninitialisedDataSize) =0;
	virtual void AddDllDependencyL(DLibrary *aDll)=0;
	virtual DThread* FirstThread()=0;
	virtual TInt GetMemoryInfo(TProcessMemoryInfo& aInfo) const = 0;
protected:
	DProcess();
public:
	TProcessPriority iPriority;
	TUidType iType;
	TInt iGeneration;
	TUint iFlags;
	TExitType iExit;
	TInt iExitReason;
	DProcess *iOwningProcess;
	CObjectIx *iHandles;
	HBufC *iFileName;
	HBufC *iCommand;
	TDblQue<DCleanup> iCleanupQ;
	TBufC<KMaxExitCategoryName> iCategory;
	TDllRefTable* iDllRefTable;
    TUint iId;

	enum TProcessAttributes {ENormal=0, EFixedAddress=1, EPrivate=2};
	TInt iAttributes;
	};

class DTransferWindow;

/**
	Kernel memory object for use in conjunction with Transfer Windows.

	@lib ekern.lib
	@since 6.2
 */
class DTransferBuffer : public CObject
	{
public:
	~DTransferBuffer();
	void Create(CObject* aOwner, DProcess* aOwningProcess, TInt aBufferSize);
	void Close();
	void AsyncClose();
	inline TTransferBufferType BufferType() const;
	inline TInt BufferSize() const;
// Pure virtual
	virtual void SetNonContiguousL()=0;
	virtual void DoClose()=0;
protected:
	DTransferBuffer();
public:
	TDblQueLink iLink;
	TInt iBufferSize;
	TTransferBufferType iBufferType;
	DTransferWindow* iMappingWindow;
	DProcess* iOwningProcess;
	};

/**
	Class for delaying deletion of transfer buffer objects.
	Use of this class avoids deletion of transfer buffers at
	inopportune moments, deleting them instead at the next
	kernel supervisor call.
 */
class TTransferBufferGarbageQ : public TDblQue<DTransferBuffer>
	{
public:
	TTransferBufferGarbageQ();
	void Empty();
	};

/**
	Kernel object for viewing and editing memory in other processes.
	The advantage of this object is that data can be shared between
	processes while avoiding having to copy data between processes,
	which enables operations to be completed more quickly.
	The downside is that one process can have access to memory in another
	process, albeit in a controlled way.
	These objects are intended for use where speed is essential, such as for
	streaming media data.
	Transfer Buffers are the memory objects which can be mapped in and
	out of transfer windows, such that transfer windows offer a view on the 
	buffer.  The buffer can be accessed via a pointer provided by the window.

  	@lib euser.lib
	@since 6.2
 */
class DTransferWindow : public CObject
	{
public:
	~DTransferWindow();
	void CreateL(CObject* aOwner, DProcess* aOwningProcess, TInt aBufferSize);
	void Close();
	IMPORT_C TInt MapInBuffer(DTransferBuffer& aBuffer);
	IMPORT_C void WaitForBuffer(TCallBack aCallBack);
	static TInt WaitForBufferComplete(TAny* aDTransferWindowPtr);
	void WaitForBuffer(TRequestStatus& aStatus);
	IMPORT_C void CancelWaitForBuffer();
	IMPORT_C void MapOutBuffer();
	IMPORT_C void WaitForBufferFree(TCallBack aCallBack);
	static TInt WaitForBufferFreeComplete(TAny* aDTransferWindowPtr);
	void WaitForBufferFree(TRequestStatus& aStatus);
	IMPORT_C void CancelWaitForBufferFree();
	IMPORT_C TUint8* BufferAddress();
	IMPORT_C TInt BufferSize() const;
	IMPORT_C TTransferBufferType BufferType() const;
// Pure virtual
	virtual TInt DoMapInBuffer(DTransferBuffer& aBuffer)=0;
	virtual void DoMapOutBuffer()=0;
	virtual TUint8* DoBufferAddress()=0;
protected:
	DTransferWindow();
	TCallBack iWaitForBufferCallBack;
	TCallBack iWaitForBufferFreeCallBack;
	TRequestStatus* iWaitForBufferStatus;
	DThread* iWaitForBufferThread;
	TRequestStatus* iWaitForBufferFreeStatus;
	DThread* iWaitForBufferFreeThread;
public:
	DTransferBuffer* iBuffer;
	TInt iMaxBufferSize;
	DProcess* iOwningProcess;
	};

//
// Kernel heap class.
// Used by platforms to work magic effects while bootstrapping.
//
class RHeapK : public RHeap
	{
#if defined(__SINGLE__)
public:
	TInt Available(TInt &aBiggestBlock) const;
#endif
protected:
	RHeapK(TInt aMaxLength);
	RHeapK(const RChunk& aChunk,TInt anOffset,TInt aMinLength,TInt aMaxLength,TInt aGrowBy);
	virtual TInt ChunkAdjust(TInt aSize);
	virtual TInt CompressAll();
	};
//
const TInt KChannelControlLateOpen=0x00ffffff;
const TUint KChanRequestNoReservedMask=0xf0000000;
//
class S;
class Kern;
class DLogicalDevice;
class DLogicalChannel : public CObject
	{
protected:
	IMPORT_C DLogicalChannel(DLogicalDevice *aDevice);
	IMPORT_C ~DLogicalChannel();
	IMPORT_C void SetBehaviour(TUint aValidRequests);
	IMPORT_C void Complete(TInt aReqNo);
	IMPORT_C void Complete(TInt aReqNo,TInt aReason);
	IMPORT_C void CompleteAll(TInt aReason);
	inline DLogicalDevice *Device();
	inline TBool IsPending(TInt aReqNo) const;
// Pure virtual
	virtual void DoCancel(TInt aReqNo) =0;
	virtual void DoRequest(TInt aReqNo,TAny *a1,TAny *a2) =0;
	IMPORT_C virtual void Close();
	IMPORT_C virtual void DoCreateL(TInt aUnit,CBase *aDriver,const TDesC *anInfo,const TVersion &aVer);
	IMPORT_C virtual TInt DoControl(TInt aFunction,TAny *a1,TAny *a2);
public:
	void Request(TInt aReqNo,TRequestStatus &aStatus,TAny *a1,TAny *a2);
	void Cancel(TUint aReqMask);
	TInt Control(TInt aFunction,TAny *a1,TAny *a2);
protected:
	DThread *iThread;
private:
	TRequestStatus *iRequestStatus[KMaxRequests];
	TUint iValidRequests;
	DLogicalDevice *iDevice;
	friend class S;
	friend class Kern;
	friend class RBusLogicalChannel;
	friend class DThread;
	friend class DLogicalDevice;
	};
//
class DLogicalDevice : public CObject
	{
public:
	IMPORT_C virtual TInt Remove();
	IMPORT_C virtual TBool QueryVersionSupported(const TVersion &aVer) const;
	IMPORT_C virtual TBool IsAvailable(TInt aUnit,const TDesC *aDriver,const TDesC *anInfo) const;
	inline DLibrary *Library();
// Pure virtual
	virtual TInt Install() =0;
	virtual void GetCaps(TDes8 &aDes) const =0;
	virtual DLogicalChannel *CreateL() =0;
protected:
	IMPORT_C DLogicalDevice();
	IMPORT_C ~DLogicalDevice();
protected:
	TVersion iVersion;
	TUint iParseMask;
	TUint iUnitsMask;
private:
	DLibrary *iLibrary;
	TInt iOpenChannels;
	friend class S;
	friend class DLogicalChannel;
	};
typedef DLogicalDevice *(*TLogicalDeviceNew)();
//
class DPhysicalDevice : public CObject
	{
public:
	IMPORT_C virtual TInt Remove();
	IMPORT_C virtual TBool QueryVersionSupported(const TVersion &aVer) const;
	IMPORT_C virtual TBool IsAvailable(TInt aUnit,const TDesC *anInfo) const;
    IMPORT_C virtual TUint CheckForSlowOpening(TInt aUnit);
	inline DLibrary *Library();
// Pure virtual
	virtual TInt Install() =0;
	virtual void GetCaps(TDes8 &aDes) const =0;
	virtual CBase *CreateL(TInt aUnit,const TDesC *anInfo,const TVersion &aVer) =0;
protected:
	IMPORT_C DPhysicalDevice();
	IMPORT_C ~DPhysicalDevice();
protected:
	TVersion iVersion;
	TUint iUnitsMask;
private:
	DLibrary *iLibrary;
	friend class S;
	};
typedef DPhysicalDevice *(*TPhysicalDeviceNew)();
//
class DServer : public CObject
	{
public:
	DServer();
	~DServer();
	void Create(const TDesC &aName);
	IMPORT_C void Receive(RMessage &aMessage,TRequestStatus &aStatus);
	void Cancel();
	void Deliver(TMessageBase &aMessage);
private:
	void Accept(TMessageBase &aMessage);
public:
	DThread *iOwningThread;
	RMessage *iPtr;
	TRequestStatus *iStatus;
	TDblQue<DSession> iSessionQ;
	TDblQue<TMessageBase> iDeliveredQ;
	};
//
class DSessionShare
	{
	class DThreadExit : public DCleanup
		{
	public:
		DThreadExit(DSessionShare& aShare);
		void Discard();
	private:
		~DThreadExit();
	private:
		DSessionShare* iShare;
		};
public:
	static DSessionShare* NewL(DSession& aSession,DThread& aClient,DServer& aServer);
	~DSessionShare();
	TInt Deliver(TMessageSlot& aMessage,TInt aFunction,const TInt *aPtr,TRequestStatus *aStatus);
//
	inline TBool IsAlive() const;
	void ServerTerminated();
	inline void ThreadExit();
	void Discard();
	void Close();
private:
	DSessionShare(DSession& aSession);
public:
	DSession* iSession;
	DThread* iClient;
	TInt iClientHandle;
	DThreadExit* iExitHandler;
	TDblQue<TMessageSlot> iOutstandingQ;
	};
//
class DSession : public CObject
	{
	friend class DServer;
	friend class DThread;
	friend class Kern;
private:
	enum {EShareGranularity=5};
	enum {EMaxMessages=255};
	enum {EMaxShares=255};
	enum {ELocalPool=0x1,ESharable=0x2,EShared=0x4,EAutoAttach=0x8};
public:
	DSession();
	~DSession();
	void Create(DServer *aServer,DThread *aClient,TInt aMessageSlots);
	void SetSessionPtr(const TAny *aUserSession,TBool aSharable);
	IMPORT_C TInt SendAsync(TInt aFunction,const TInt *aPtr,TRequestStatus *aStatus);
	TInt SendSync(TInt aFunction,const TInt *aPtr,TRequestStatus *aStatus);
	virtual void Close();
//
	void DiscardShare(DSessionShare& aShare);
	void AttachL(DThread& aClient);
	void ShareL(RSessionBase::TAttachMode aAttachMode);
	inline TBool Sharable() const;
	inline TBool Shared() const;
private:
	void CloseFromServer();
	DSessionShare** FindEntry(DThread& aClient) const;
	DSessionShare* FindShare() const;
public:
	const TAny* iUserSession;
	union
		{
		DSessionShare* iPrimary;
		DSessionShare** iShares;
		};
	TUint8 iClients;
	TUint8 iAlloc;
	TUint8 iAttributes;
	TUint8 iAvailable;
	TMessagePool iLocalPool;
	TMessageSlot* iMessages;
	TDisconnectMessage iDisconnect;
	DServer* iServer;
	TDblQueLink iServerLink;
	};


class TSvrMessage
	{
public:
	inline TInt Function() const;
	inline TInt Int0() const;
	inline TInt Int1() const;
	inline TInt Int2() const;
	inline TInt Int3() const;
	inline const TAny* Ptr0() const;
	inline const TAny* Ptr1() const;
	inline const TAny* Ptr2() const;
	inline const TAny* Ptr3() const;
	inline DThread* Client() const;
	inline void Complete(TInt aReason) const;
public:
	TInt iFunction;
	TInt iArgs[KMaxMessageArguments];
	DThread* iClient;
	};

//
// Peripheral Bus definitions
//
typedef signed int TPBusNum;
class DPeriphBusController;
class TPBusInfo
	{
public:
	DPeriphBusController* iPtr;
	TPBusNum iBusNum;
	};

//
// Local Drive Subsystem definitions
//
enum TMediaState {EDoorOpen,EDoorClosed};

class TDriveChangedFlags
	{
public:
	TDriveChangedFlags(DThread* aThread,TInt* aMountStatus,TBool* aChangedFlag,TInt aDriveNum);
	TInt UpdateMountStatus();
	TInt UpdateMediaChange();
    TInt CompleteOpenRequest(TInt aReason);
	TBool ThreadIsValid();
    inline TBool IsMatchingEntry(DThread* aThread,TInt* aMountStatus);
    inline void SetOpenRequestPending();
    inline TBool IsOpenRequestPending();
	inline TInt DriveNumber();
private:
    TBool iOpenReqPending;
	DThread *iOwningThread;
	TInt *iMountStatus;
	TBool *iChangedFlag;
	TInt iDriveNum;
	};
//
class TPartitionEntry
	{
public:
	TInt64 iPartitionBaseAddr;
	TInt64 iPartitionLen;
	};
//
const TInt KMaxPartitionEntries=0x4;
class TPartitionInfo
	{
public:
	TPartitionInfo();
public:
	TInt64 iMediaSizeInBytes;
	TInt iPartitionCount;
	TPartitionEntry iEntry[KMaxPartitionEntries];
	};
//
//
class TMediaDrvDescData
	{
public:
	IMPORT_C TMediaDrvDescData();
	IMPORT_C TMediaDrvDescData(TLocalDriveMessageData aData);
	TMediaDrvDescData &operator=(TLocalDriveMessageData aData);
	IMPORT_C TBool IsCurrentThread();
	IMPORT_C TInt CurrentThreadDescCheck(TInt aLen);
public:
	const TAny* iPtr;
	TInt iHandle;
	TInt iOffset;
	DThread *iThread;
	};
//
enum TPBusPasswordFunc {EPbPswdUnlock,EPbPswdLock,EPbPswdClear};
class DMedia;
class DMediaDriver;
class TLocDrv
	{
public:
	TLocDrv();
	void Create(TInt aDriveNumber);
	void ConnectL(TDriveChangedFlags aChangedFlags);
	void Disconnect(DThread *anOwningThread,TInt *aMountStatus);
    void Open(DThread *aLocDrvOwningThread,TRequestStatus *aStatus,TInt aStartResult);
	TInt Enlarge(TInt aLength);
	TInt ReduceSize(TInt64 aPos,TInt aLength);
	TInt Caps(TDes8& aCapsBuf);
	void Read(TInt64 aPos,TInt *aLength,TLocalDriveMessageData &aTrg,DThread *aThread,TRequestStatus *aStatus);
	void Write(TInt64 aPos,TInt *aLength,TLocalDriveMessageData &aSrc,DThread *aThread,TRequestStatus *aStatus);
	void Format(TInt64 aPos,TInt *aLength,DThread *aThread,TRequestStatus *aStatus);
	void PasswordControl(TPBusPasswordFunc aFunc,TPBusPasswordData& aPasswordData,DThread *aThread,TRequestStatus* aStat);
	TInt SetMountInfo(TLocalDriveMessageData &aMountInfo);
	inline TInt Number() {return(iDriveNumber);}
	inline TBool IsDisMounted() {return(iMedia==NULL);}
protected:
	DMediaDriver *MediaDriver();
	TInt CheckDeviceAndParamters(TInt64 aPos,TInt aLength);
    void SetPartitionInfo();
protected:
	TInt iDriveNumber;
	DMedia *iMedia;
	TInt64 iPartitionBaseAddr;
	TInt64 iPartitionLen;
	TInt iPartitionNumber;
	friend class DPrimaryMediaBase;
	};
/**
 * DMedia Class
 */
class DMedia : public CBase
	{
public:
	enum TMediaStatus {EStatClosed,EStatHasDriver,EStatFullyMounted};
public:
	DMedia(TInt aMediaNum);
	virtual void CreateL(TMediaDevice aDevice);
	virtual void Destroy();
	IMPORT_C static void Start(TMediaDevice aDevice,DThread *anOwningThread,TRequestStatus *aStatus);
    IMPORT_C static TInt Open(TMediaDevice aDevice);
	IMPORT_C static void CleanUp(TMediaDevice aDevice);
	void Close();
	TInt Enlarge(TInt aPartition,TInt aLength);
	TInt ReduceSize(TInt aPartition,TInt64 &aPos,TInt aLength);
	inline TInt64 MediaLenInBytes();
    inline TMediaStatus Status(); 
	inline void SetStatus(TMediaStatus aStatus);
	inline TMediaDevice DeviceType();
	inline TInt PartitionCount();
	inline TInt64 PartitionBaseAddr(TInt aPartition);
	inline TInt64 PartitionLen(TInt aPartition);
	DMediaDriver *Driver();
protected:
	friend class S;
	static TInt MediaCallBack(TAny *aPtr);
public:
	TPartitionInfo iPartitionInfo;
protected:
	TInt iMediaNum;
	TMediaDevice iDevice;
	TMediaStatus iStatus;
	DMediaDriver *iDriver;
	};
/**
 * Primary Media Base Class
 */
class DPrimaryMediaBase : public DMedia
	{
public:
	static DPrimaryMediaBase *NewL(TInt aMediaNum);
	DPrimaryMediaBase(TInt aMediaNum);
	virtual void CreateL(TMediaDevice aDevice);
	void Destroy();
	void AddChangeFlagsL(TDriveChangedFlags aChangedFlags);
	void RemoveChangeFlags(DThread* anOwningThread,TInt* aMountStatus);
    void UpdateFlagsForOpenRequest(DThread* anOwningThread,TInt* aMountStatus);
    void ReadPartitionInfo();
	TInt SetMountInfo(TLocalDriveMessageData &aMountInfo,TInt aMediaNum);
	TMediaDrvDescData* MountInfo(TInt aMediaNum);
protected:
    void QueueNotifyDfc(TBool aMediaChangeEvent);
    virtual void ResetMediaDriverCurrent(DMediaDriver* aDriver);
private:
	static TInt MediaChangeDfc(TAny *aPrimaryMedia);
	static TInt PowerDownDfc(TAny *aPrimaryMedia);
	void NotifyMediaStatusChange(TBool aMediaChangeFlags);
    static TInt PartitionInfoCallBack(TAny *aPrimaryMedia);
    static TInt PartitionInfoDfc(TAny *aPrimaryMedia);
private:
	TDfc iMediaChangeDfc;
	TDfc iPowerDownDfc;
	RArray<TDriveChangedFlags> iChangedArray;
    TInt iPartitionInfoError;
    TInt iPartitionInfoDrvNum;
    TCallBack iPartitionInfoCallBack;
	TDfc iPartitionInfoDfc;
	TMediaDrvDescData* iMountInfo;		// Mount info array
	TInt iMediaCount; 					// Total number if DMedia objects managed by this 
	friend class Kern;
	friend class S;						// Required to initialise iMediaCount
	};
//
const TInt KMediaDriverPriorityHigh=2;
const TInt KMediaDriverPriorityNormal=1;
const TInt KMediaDriverPriorityLow=0;
class DPhysicalDeviceMedia : public DPhysicalDevice
	{
public:
	virtual TInt Priority()=0;
	};
//
// The number of asynchronous requests supported by a media driver
//
const TInt KMediaDrvMaxReqs=0x3;
//
const TInt KMediaDrvReadReq=0x0;
const TInt KMediaDrvWriteReq=0x1;
const TInt KMediaDrvFormatReq=0x2;
//
const TInt KMediaDrvMultipleReqs=0x00000001;
//
class DMediaDriver : public CBase
	{
public:
	IMPORT_C DMediaDriver();
	IMPORT_C ~DMediaDriver();
	IMPORT_C virtual TInt DoCreate(TMediaDevice aMediaDevice,const TDesC* anInfo);
	void Read(TInt64 &aPos,TInt *aLength,TLocalDriveMessageData &aTrg,DThread *aThread,TRequestStatus *aStatus);
	void Write(TInt64 &aPos,TInt *aLength,TLocalDriveMessageData &aSrc,DThread *aThread,TRequestStatus *aStatus);
	void Format(TInt64 &aPos,TInt *aLength,DThread *aThread,TRequestStatus *aStatus);
	void PartitionInfo(TPartitionInfo &anInfo);
// Pure virtual
	virtual TInt Enlarge(TInt aLength)=0;
	virtual TInt ReduceSize(TInt64 &aPos,TInt aLength)=0;
	virtual void Close()=0;
	virtual void Caps(TDes8& aCapsBuf)=0;
	virtual void ReadPartitionInfo(TInt &aResult,const TCallBack& aCallBack)=0;
	IMPORT_C virtual void PasswordControl(TPBusPasswordFunc aFunc,TPBusPasswordData& aPasswordData,DThread *aThread,TRequestStatus* aStat);
	IMPORT_C virtual void SetCurrentConsumptionInMilliAmps(TInt aValue);
protected:
	virtual TInt Open(TMediaDevice aMediaDevice)=0;
	IMPORT_C void Complete(TInt aReqNo,TInt aReason);
    IMPORT_C void Complete(TInt aReqNo,TInt aReason,TInt aLenWriteBack);
    IMPORT_C void CompleteAll(TInt aReason);
	inline TBool IsPending(TInt aReqNo) const;
	inline TBool AnyPending() const;
	IMPORT_C void SetTotalSizeInBytes(TInt64 aTotalSizeInBytes);
	IMPORT_C TInt64 TotalSizeInBytes();
// Asynchronous 
	virtual void DoRead(TInt64 &aPos,TInt aLength,TMediaDrvDescData &aTrg)=0;
	virtual void DoWrite(TInt64 &aPos,TInt aLength,TMediaDrvDescData &aSrc)=0;
	virtual void DoFormat(TInt64 &aPos,TInt aLength)=0;
// Synchronous
	IMPORT_C virtual TInt DoSyncRead(TInt64 &aPos,TInt &aLength,TMediaDrvDescData &aTrg);
	IMPORT_C virtual TInt DoSyncWrite(TInt64 &aPos,TInt &aLength,TMediaDrvDescData &aSrc);
	IMPORT_C virtual TInt DoSyncFormat(TInt64 &aPos,TInt &aLength);
private:
    TInt RequestSetup(TInt aReqNo,TInt64 &aPos,TInt *aLength,DThread *aThread,TRequestStatus *aStatus);
protected:
	TUint iFlags;
	TPartitionInfo iPartitionInfo;
	const TMediaDrvDescData* iMountInfo;
private:
	DThread *iReqThread[KMediaDrvMaxReqs];
	TRequestStatus *iReqStat[KMediaDrvMaxReqs];
	TInt *iReqLenAddr[KMediaDrvMaxReqs];
	TInt64 iTotalSizeInBytes;
    TInt iCurrentConsumption;
	friend class Kern;
//	friend class DMedia;						
	};
/**
 * DMediaChangeNotifierBase class
 */
class DMediaChangeNotifierBase : public CBase
	{
public:
	static DMediaChangeNotifierBase* NewL(TPBusNum aBus);
	DMediaChangeNotifierBase(TPBusNum aBus);
	TInt RegisterNotification(TRequestStatus *aReqStat,DThread *aThread,TBool aFirstRegistration);
protected:
    virtual TInt DoRegisterNotification(TBool aFirstRegistration);
	static TInt EventCallBack(TAny *aPtr);
	static TInt CallBackDfc(TAny *aPtr);
	inline void SignalMediaChange();
	inline TBool IsCallBackActive();
protected:
    TPBusNum iPBusNum;
private:
	TRequestStatus *iReqStat;
	DThread *iThread;
	TDfc iDfc;
	};
//
struct SLocaleData
//
// Data must be identical to that in TLocale
//
	{
	TInt iCountryCode;
	TTimeIntervalSeconds iUniversalTimeOffset;
	TDateFormat iDateFormat;
	TTimeFormat iTimeFormat;
	TLocalePos iCurrencySymbolPosition;
	TBool iCurrencySpaceBetween;
	TInt iCurrencyDecimalPlaces;
	TLocale::TNegativeCurrencyFormat iNegativeCurrencyFormat; // replaced TBool iCurrencyNegativeInBrackets to match TLocale
	TBool iCurrencyTriadsAllowed;
	TChar iThousandsSeparator;
	TChar iDecimalSeparator;
	TChar iDateSeparator[KMaxDateSeparators];
	TChar iTimeSeparator[KMaxTimeSeparators];
	TLocalePos iAmPmSymbolPosition;
	TBool iAmPmSpaceBetween;
	TUint iDaylightSaving;
	TDaylightSavingZone iHomeDaylightSavingZone;
	TUint iWorkDays;
	TDay iStartOfWeek;
	TClockFormat iClockFormat;
	TUnitsFormat iUnitsGeneral;
	TUnitsFormat iUnitsDistanceShort;
	TUnitsFormat iUnitsDistanceLong;
	TUint iExtraNegativeCurrencyFormatFlags;
	TUint16 iLanguageDowngrade[3];
	TUint16 iSpare16;
	TInt iSpare[0x20];
	};

//
// The executive handlers
//
class ExecHandler
	{
public:
	static TInt ChunkNext(__DUMMY__ TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static TUint8 *ChunkBase(__DUMMY__ TInt aHandle);
	static TInt ChunkSize(__DUMMY__ TInt aHandle);
	static TInt ChunkMaxSize(__DUMMY__ TInt aHandle);
	static void ChunkSetHeapInfo(__DUMMY__ TInt aHandle,TInt anOffset,TInt aRunAddress);
	static void ChunkRead(__DUMMY__ TInt aPos,TDes8 *aDes,TInt aMode,TInt aHandle);
	static void ChunkWrite(__DUMMY__ TInt aPos,const TDesC8 *aDes,TInt aMode,TInt aHandle);
	static TInt ChunkBottom(__DUMMY__ TInt aHandle);
	static TInt ChunkTop(__DUMMY__ TInt aHandle);
	static TInt ChunkReserveAt(__DUMMY__ TInt aHandle, TUint8 *aAddr);
//
	static TInt LogicalDeviceNext(__DUMMY__ TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static void LogicalDeviceGetCaps(__DUMMY__ TDes8 &aDes,TInt aHandle);
	static TBool LogicalDeviceQueryVersionSupported(__DUMMY__ const TVersion &aVer,TInt aHandle);
	static TBool LogicalDeviceIsAvailable(__DUMMY__ TInt aUnit,const TDesC *aPhysicalDevice,const TDesC *anInfo,TInt aHandle);
//
	static TInt PhysicalDeviceNext(__DUMMY__ TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
//
	static TInt ChannelNext(__DUMMY__ TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static void ChannelRequest(__DUMMY__ TInt aReqNo,TRequestStatus &aStatus,TAny **aArg,TInt aHandle);
	static void ChannelCancel(__DUMMY__ TUint aRequestMask,TInt aHandle);
	static TInt ChannelControl(__DUMMY__ TInt aFunction,TAny *a1,TAny *a2,TInt aHandle);
	static TUint BusDevCheckOpenMode(__DUMMY__ TBusDevOpenModeData* anOpenData);
	static TInt BusChannelCheckStatus(__DUMMY__ TInt aSocket);
//
	static void LibraryType(__DUMMY__ TUidType &aUids, TInt aHandle);
	static TInt LibraryNext(__DUMMY__ TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static TLibraryFunction LibraryLookup(__DUMMY__ TInt anOrdinal,TInt aHandle);
	static TLibraryEntry LibraryEntryPoint(__DUMMY__ TInt aHandle);
	static TUint* LibraryDllRefTable(__DUMMY__ TInt aHandle);
	static TInt StaticCallList(__DUMMY__ TInt aHandle,TInt& aCount, TUint*& aList);
	static TInt DynamicCallList(__DUMMY__ TInt aHandle,TInt& aCount, TUint*& aList);
	static TInt LibraryCallList(__DUMMY__ TInt aHandle,TInt& aCount, TUint*& aList);
	static void LibraryFileName(__DUMMY__ TDes &aFileName,TInt aHandle);
//
	static TInt MutexNext(__DUMMY__ TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static TInt MutexCount(__DUMMY__ TInt aHandle);
	static void MutexWait(__DUMMY__ TInt aHandle);
	static void MutexSignal(__DUMMY__ TInt aHandle);
//
	static void ProcessType(__DUMMY__ TUidType &aUids, TInt aHandle);
	static void ProcessSetType(__DUMMY__ const TUidType &aType, TInt aHandle);
	static TInt ProcessId(__DUMMY__ TInt aHandle);
	static TInt ProcessNext(__DUMMY__ TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static void ProcessResume(__DUMMY__ TInt aHandle);
	static void ProcessFileName(__DUMMY__ TDes &aName,TInt aHandle);
	static void ProcessCommandLine(__DUMMY__ TDes &aName,TInt aHandle);
	static TInt ProcessCommandLineLength(__DUMMY__ TInt aHandle);
	static TExitType ProcessExitType(__DUMMY__ TInt aHandle);
	static TInt ProcessExitReason(__DUMMY__ TInt aHandle);
	static void ProcessExitCategory(__DUMMY__ TDes &aName,TInt aHandle);
	static TProcessPriority ProcessPriority(__DUMMY__ TInt aHandle);
	static void ProcessSetPriority(__DUMMY__ TProcessPriority aPriority,TInt aHandle);
	static TUint ProcessFlags(__DUMMY__ TInt aHandle);
	static void ProcessSetFlags(__DUMMY__ TUint aClearMask,TUint aSetMask,TInt aHandle);
	static void ProcessSetOwner(__DUMMY__ TInt anOwningHandle,TInt aHandle);
//
	static TInt SemaphoreNext(__DUMMY__ TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static TInt SemaphoreCount(__DUMMY__ TInt aHandle);
	static void SemaphoreWait(__DUMMY__ TInt aHandle);
	static void SemaphoreSignal1(__DUMMY__ TInt aHandle);
	static void SemaphoreSignalN(__DUMMY__ TInt aCount,TInt aHandle);
//
	static TInt ServerNext(__DUMMY__ TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static void ServerReceive(__DUMMY__ TInt aHandle,TRequestStatus &aStatus,RMessage &aMessage);
	static void ServerCancel(__DUMMY__ TInt aHandle);
//
	static void SetSessionPtr(__DUMMY__ TInt aMsgHandle,const TAny *aSession,TBool aSharable);
	static TInt SessionSendAsync(__DUMMY__ TInt aHandle,TInt aFunction,TAny *aPtr,TRequestStatus *aStatus);
//
    static TInt ThreadId(__DUMMY__ TInt aHandle);
	static TInt ThreadNext(__DUMMY__ TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static void ThreadResume(__DUMMY__ TInt aHandle);
	static void ThreadSuspend(__DUMMY__ TInt aHandle);
	static TThreadPriority ThreadPriority(__DUMMY__ TInt aHandle);
	static void ThreadSetPriority(__DUMMY__ TThreadPriority aPriority,TInt aHandle);
	static TProcessPriority ThreadProcessPriority(__DUMMY__ TInt aHandle);
	static void ThreadSetProcessPriority(__DUMMY__ TProcessPriority aPriority,TInt aHandle);
	static TUint ThreadFlags(__DUMMY__ TInt aHandle);
	static void ThreadSetFlags(__DUMMY__ TUint aClearMask,TUint aSetMask,TInt aHandle);
	static TInt ThreadRequestCount(__DUMMY__ TInt aHandle);
	static TExitType ThreadExitType(__DUMMY__ TInt aHandle);
	static TInt ThreadExitReason(__DUMMY__ TInt aHandle);
	static void ThreadExitCategory(__DUMMY__ TDes &aName,TInt aHandle);
	static TInt ThreadGetDesLength(__DUMMY__ const TAny *aPtr,TInt aHandle);
	static TInt ThreadGetDesMaxLength(__DUMMY__ const TAny *aPtr,TInt aHandle);
	static TInt ThreadRead8(__DUMMY__ const TAny *aPtr,TDes8 *aDes,TInt anOffset,TInt aHandle);
	static TInt ThreadRead16(__DUMMY__ const TAny *aPtr,TDes16 *aDes,TInt anOffset,TInt aHandle);
	static TInt ThreadWrite8(__DUMMY__ const TAny *aPtr,const TDesC8 *aDes,TInt anOffset,TInt aHandle);
	static TInt ThreadWrite16(__DUMMY__ const TAny *aPtr,const TDesC16 *aDes,TInt anOffset,TInt aHandle);
	static void ThreadRequestComplete(__DUMMY__ TRequestStatus * &aStatus,TInt aReason,TInt aHandle);
//
	static void TimerCancel(__DUMMY__ TInt aHandle);
	static void TimerAfter(__DUMMY__ TRequestStatus &aStatus,TTimeIntervalMicroSeconds32 aTime,TInt aHandle);
	static void TimerAt(__DUMMY__ TRequestStatus &aStatus,const TTime &aTime,TInt aHandle);
	static void TimerLock(__DUMMY__ TRequestStatus &aStatus,TTimerLockSpec aLock,TInt aHandle);
	static void TimerInactivity(__DUMMY__ TRequestStatus& aStatus, TInt aSeconds, TInt aHandle);
	static TInt UserInactivityTime();
	static void ResetInactivityTime();
//
	static TInt ChangeNotifierLogon(__DUMMY__ TRequestStatus& aStatus,TInt aHandle);
	static TInt ChangeNotifierLogoff(__DUMMY__ TInt aHandle);
//
	static void WaitForAnyRequest();
	static void RequestSignal(__DUMMY__ TInt aCount);
//
	static TUint Fold(__DUMMY__ TUint aChar);
	static TUint Collate(__DUMMY__ TUint aChar);
	static TUint LowerCase(__DUMMY__ TUint aChar);
	static TUint UpperCase(__DUMMY__ TUint aChar);
	static TUint Type(__DUMMY__ TUint aChar);
	static TInt Match8(__DUMMY__ const TDesC8 &aLeft,const TDesC8 &aRight,TMatchType aType);
	static TInt Match16(__DUMMY__ const TDesC16 &aLeft,const TDesC16 &aRight,TMatchType aType);
	static TInt Find8(__DUMMY__ const TDesC8 &aDes,const TUint8* pS,TInt aLen,TMatchType aType);		//*
	static TInt Find16(__DUMMY__ const TDesC16 &aDes,const TUint16* pS,TInt aLen,TMatchType aType);	//*
	static TInt LocateF8(__DUMMY__ const TDesC8 &aDes,TUint aChar);
	static TInt LocateF16(__DUMMY__ const TDesC16 &aDes,TUint aChar);
//
	static void HandleName(__DUMMY__ TDes &aName,TInt aHandle);
	static void HandleFullName(__DUMMY__ TDes &aFullName,TInt aHandle);
	static void HandleInfo(__DUMMY__ THandleInfo* anInfo,TInt aHandle);
	static void HandleCount(__DUMMY__ TInt aHandle, TInt& aProcessHandleCount, TInt& aThreadHandleCount);
	static TUint HandleAttributes(__DUMMY__ TInt aHandle);
//
	static void After(__DUMMY__ TTimeIntervalMicroSeconds32 anInterval,TRequestStatus &aStatus);
	static void At(__DUMMY__ const TTime &aTime,TRequestStatus &aStatus);
//
	static TInt MessageComplete(__DUMMY__ TInt aHandle,TInt aReason);
//
	static TLanguage Language();
	static void DayName(__DUMMY__ TDay aDay,TDes &aName);
	static void DayNameAbb(__DUMMY__ TDay aDay,TDes &aName);
	static void MonthName(__DUMMY__ TMonth aMonth,TDes &aName);
	static void MonthNameAbb(__DUMMY__ TMonth aMonth,TDes &aName);
	static void Suffix(__DUMMY__ TInt aSuffix,TDes &aName);
	static void AmPmName(__DUMMY__ TAmPm aSelector,TDes &aName);
	static void CurrencySymbol(__DUMMY__ TDes &aName);
	static void SetCurrencySymbol(__DUMMY__ const TDesC& aName);
	static void ShortDateFormatSpec(__DUMMY__ TDes& aName);
	static void LongDateFormatSpec(__DUMMY__ TDes& aName);
	static void TimeFormatSpec(__DUMMY__ TDes& aName);
	static const TFatUtilityFunctions* FatUtilityFunctions();
	static void LocaleRefresh(__DUMMY__ SLocaleData &aLocale);
	static void LocaleSet(__DUMMY__ const SLocaleData &aLocale);
	static void LocaleMessageText(__DUMMY__ TLocaleMessage aMsgNo,TDes& aMsg);
//
	static RHeap *Heap();
	static RHeap *HeapSwitch(__DUMMY__ RHeap *aHeap);
//
	static void TimeNow(__DUMMY__ TTime& aUniversalTime,TTimeIntervalSeconds& aUniversalTimeOffset);
	static TInt SetHomeTime(__DUMMY__ const TTime &aHomeTime);
	static TUint TickCount();
	static TTimerLockSpec LockPeriod();
//
	static void PushTrapFrame(__DUMMY__ TTrap *aFrame);
	static TTrap *PopTrapFrame();
	static CActiveScheduler *ActiveScheduler();
	static void SetActiveScheduler(__DUMMY__ CActiveScheduler *aScheduler);
//
	static void SvSendReceive(__DUMMY__ TInt aFunction,TAny *aPtr,TRequestStatus &aStatus);
//
	static void CaptureEventHook();
	static void ReleaseEventHook();
	static void RequestEvent(__DUMMY__ TRawEventBuf &anEvent,TRequestStatus &aStatus);
	static void RequestEventCancel();
	static TInt AddEvent(__DUMMY__ const TRawEvent& anEvent);
	static void ScreenInfo(__DUMMY__ TDes8 &anInfo);
//
	static TInt DllAllocateModuleHandle(__DUMMY__ const TInt *anID);
	static TInt DllGlobalAlloc(__DUMMY__ TInt aHandle,TInt aSize);
	static TBool DllGlobalAllocated(__DUMMY__ TInt aHandle);
	static TInt DllGlobalRead(__DUMMY__ TInt aHandle,TInt aPos,TInt aLength,TDes8 &aDes);
	static TInt DllGlobalWrite(__DUMMY__ TInt aHandle,TInt aPos,const TDesC8 &aDes);
	static TAny *DllTls(__DUMMY__ TInt aHandle);
	static void DllDataInfo(__DUMMY__ TInt aHandle, TModuleInfo &aInfo);
	static void DllFileName(__DUMMY__ TInt aHandle, TDes &aFileName);
//
	static TTrapHandler *TrapHandler();
	static TTrapHandler *SetTrapHandler(__DUMMY__ TTrapHandler *aHandler);
//
	static TInt HalGet(__DUMMY__ THalFunction Function,TAny* aData);
	static TInt HalSet(__DUMMY__ THalFunction Function,TAny* aData);
//
	static void KernelStartup(__DUMMY__ TThreadFunction aFunction);
	static void BlockThreads(__DUMMY__ TBlockType aType);
	static void WsRegisterThread(__DUMMY__ TThreadFunction aFunction);
	static void FsRegisterThread(__DUMMY__ TThreadFunction aFunction);
//
	static TInt Beep(__DUMMY__ TInt aFrequency,TTimeIntervalMicroSeconds32 aDuration);
//
	static TBool JustInTime();
	static void SetJustInTime(__DUMMY__ const TBool aBoolean);
//
	static TInt LockedInc(__DUMMY__ TInt &aValue);
	static TInt LockedDec(__DUMMY__ TInt &aValue);
//
	static TInt DriveCaps(__DUMMY__ TDes8& anInfo,TAny *aDrive);
	static void DriveReadRequest(__DUMMY__ TLocalDriveData &aDriveData,TLocalDriveMessageData &aTrg,TRequestStatus &aStatus,TAny *aDrive);
	static void DriveWriteRequest(__DUMMY__ TLocalDriveData &aDriveData,TLocalDriveMessageData &aSrc,TRequestStatus &aStatus,TAny *aDrive);
	static void DriveFormatRequest(__DUMMY__ TInt64 &aPos,TInt *aLength,TRequestStatus &aStatus,TAny *aDrive);
	static TInt DriveSetMountInfoRequest(__DUMMY__ TLocalDriveMessageData &aMountInfo,TAny *aDrive);
	static TInt DriveForceRemountRequest(__DUMMY__ TUint aFlags,TAny *aDrive);
//
	static void SetDebugMask(__DUMMY__ TUint32 aVal);
	static TUint32 DebugMask();

//
	static TInt DebugFunction(__DUMMY__ TDebugFunction* aFunction,TAny* aPar1,TAny* aPar2,TAny* aPar3);
	static TInt BreakPoint();
	static TInt ProfileStart(__DUMMY__ TInt aProfile);
	static TInt ProfileEnd(__DUMMY__ TInt aProfile);
//
	static TBool PasswordIsEnabled();
	static TBool PasswordIsValid(__DUMMY__ const TPassword& aPassword);
//
	static TUint32 FastCounter();
	static TUint32 MathRandom();
//
	static TExceptionHandler* ExceptionHandler(__DUMMY__ TInt aHandle);
	static TInt SetExceptionHandler(__DUMMY__ TExceptionHandler* aHandler, TUint32 aMask, TInt aHandle);
	static void ModifyExceptionMask(__DUMMY__ TUint32 aClearMask, TUint32 aSetMask, TInt aHandle);
	static TInt RaiseException(__DUMMY__ TExcType aType,TInt aHandle);
	static TBool IsExceptionHandled(__DUMMY__ TExcType aType,TInt aHandle);
	static void ThreadContext(__DUMMY__ TDes8 &aDes, TInt aHandle);
//
	static TInt ThreadGetRamSizes(__DUMMY__ TInt& aHeapSize, TInt& aStackSize, TInt aHandle);
	static TInt ProcessGetRamSizes(__DUMMY__ TInt& aCodeSize, TInt& aConstDataSize, TInt& anInitialisedDataSize, TInt& anUninitialisedDataSize, TInt aHandle);
	static TInt ProcessGetMemoryInfo(__DUMMY__ TProcessMemoryInfo& aInfo, TInt aHandle);
	static TInt LibraryGetRamSizes(__DUMMY__ TInt& aCodeSize, TInt& aConstDataSize, TInt aHandle);
//
	static TInt MachineConfiguration(__DUMMY__ TDes8& aConfig,TInt& aSize);
//
    static TInt TestBootSequence();
//
	static const LCharSet *GetLocaleCharSet();
//
	static void WsSwitchOnScreen();
	static void WsRegisterSwitchOnScreenHandling(__DUMMY__ TBool aState);
//
	static TInt DllAddDependency(__DUMMY__ TAny *anImportingDll, TAny *anExportingDll);
//
	static void UnlockRamDrive();
	static void LockRamDrive();
	static TLinAddr RomRootDirectoryAddress();
	static TLinAddr RomHeaderAddress();
//
	static TInt SessionSendSync(__DUMMY__ TInt aHandle,TInt aFunction,TAny *aPtr,TRequestStatus *aStatus);
//
	static TInt DriveReadPasswordData(__DUMMY__ TDes8& aBuf);
	static TInt DrivePasswordStoreLengthInBytes();
//
	static TInt ThreadGetCpuTime(__DUMMY__ TInt aHandle, TTimeIntervalMicroSeconds& aCpuTime);
//
	static TInt SetMemoryThresholds(__DUMMY__ TInt aLowThreshold, TInt aGoodThreshold);
//
	static void IMB_Range(__DUMMY__ TLinAddr aBase, TUint aSize);
//
	static TInt TransferBufferSize(__DUMMY__ TInt aHandle);
	static void TransferWindowWaitForBuffer(__DUMMY__ TInt aHandle, TRequestStatus& aStatus);
	static void TransferWindowCancelWaitForBuffer(__DUMMY__ TInt aHandle);
	static void TransferWindowWaitForBufferFree(__DUMMY__ TInt aHandle, TRequestStatus& aStatus);
	static void TransferWindowCancelWaitForBufferFree(__DUMMY__ TInt aHandle);
	static TUint8* TransferWindowBufferAddress(__DUMMY__ TInt aHandle);
	static TInt TransferWindowBufferSize(__DUMMY__ TInt  aHandle);
	static TInt TransferWindowMapInBuffer(__DUMMY__ TInt aWinHandle, TInt aBufHandle);
	static TInt TransferWindowMapOutBuffer(__DUMMY__ TInt aHandle);
//
	static TInt NotSupported32();
	static TInt NotSupported31();
	static TInt NotSupported30();
	static TInt NotSupported29();
	static TInt NotSupported28();
	static TInt NotSupported27();
	static TInt NotSupported26();
	static TInt NotSupported25();
	static TInt NotSupported24();
	static TInt NotSupported23();
	static TInt NotSupported22();
	static TInt NotSupported21();
	static TInt NotSupported20();
	static TInt NotSupported19();
	static TInt NotSupported18();
	static TInt NotSupported17();
	static TInt NotSupported16();
	static TInt NotSupported15();
	static TInt NotSupported14();
	static TInt NotSupported13();
	static TInt NotSupported12();
	static TInt NotSupported11();
	static TInt NotSupported10();
	static TInt NotSupported9();
	static TInt NotSupported8();
	static TInt NotSupported7();
	static TInt NotSupported6();
	static TInt NotSupported5();
	static TInt NotSupported4();
	static TInt NotSupported3();
	static TInt NotSupported2();
	static TInt NotSupported1();
	};
//
// Exported from E32LOCL.DLL
//
class Locl
	{
public:
	IMPORT_C static TLanguage Language();
	IMPORT_C static TBool UniCode();
	IMPORT_C static void LocaleData(SLocaleData *aLocale);
	IMPORT_C static const TText *CurrencySymbol();
	IMPORT_C static const TText* ShortDateFormatSpec();
	IMPORT_C static const TText* LongDateFormatSpec();
	IMPORT_C static const TText* TimeFormatSpec();
	IMPORT_C static const TFatUtilityFunctions* FatUtilityFunctions();
	IMPORT_C static const TText * const *DateSuffixTable();
	IMPORT_C static const TText * const *DayTable();
	IMPORT_C static const TText * const *DayAbbTable();
	IMPORT_C static const TText * const *MonthTable();
	IMPORT_C static const TText * const *MonthAbbTable();
	IMPORT_C static const TText * const *AmPmTable();
	IMPORT_C static const TText * const *MsgTable();
	IMPORT_C static const LCharSet *CharSet();
	IMPORT_C static const TUint8 *TypeTable();
	IMPORT_C static const TText *UpperTable();
	IMPORT_C static const TText *LowerTable();
	IMPORT_C static const TText *FoldTable();
	IMPORT_C static const TText *CollTable();

	};
//
// Platform independent function exported from E32KERN.DLL
//
typedef TInt (*TIdleCallBack)(TInt);
class Kern
	{
public:
//
	IMPORT_C static void SupervisorInitialise(TThreadFunction aFunction);
	IMPORT_C static RHeap &Heap();
	IMPORT_C static RHeap &HeapSwitch(RHeap &aHeap);
	IMPORT_C static TInt AddEvent(const TRawEvent& anEvent);
//
	IMPORT_C static void Add(TDfc &aDfc);
//
	IMPORT_C static DTimer* TimerFromHandle(TInt aHandle);
//
	IMPORT_C static TInt ChunkFind(TInt &aFindHandle,const TDesC &aMatch,TFullName &aName);
	IMPORT_C static DChunk* ChunkFromHandle(TInt aHandle);
	IMPORT_C static CObjectCon* Chunks();
//
	IMPORT_C static TInt SemaphoreFind(TInt &aFindHandle,const TDesC &aMatch,TFullName &aName);
	IMPORT_C static DSemaphore* SemaphoreFromHandle(TInt aHandle);
//
	IMPORT_C static TInt MutexFind(TInt &aFindHandle,const TDesC &aMatch,TFullName &aName);
	IMPORT_C static DMutex* MutexFromHandle(TInt aHandle);
//
	IMPORT_C static TInt ThreadFind(TInt &aFindHandle,const TDesC &aMatch,TFullName &aName);
	IMPORT_C static DThread* ThreadFromHandle(TInt aHandle);
	IMPORT_C static DThread* ThreadFromId(TThreadId aId);
	IMPORT_C static CObjectCon* Threads();
	IMPORT_C static DThread* SvThread();
//
	IMPORT_C static TInt ProcessFind(TInt &aFindHandle,const TDesC &aMatch,TFullName &aName);
	IMPORT_C static DProcess* ProcessFromHandle(TInt aHandle);
	IMPORT_C static CObjectCon* Processes();
	IMPORT_C static DProcess* SvProcess();
//
	IMPORT_C static TInt LogicalDeviceFind(TInt &aFindHandle,const TDesC &aMatch,TFullName &aName);
	IMPORT_C static DLogicalDevice* LogicalDeviceFromHandle(TInt aHandle);
	IMPORT_C static CObjectCon* LogicalDevices();
//
	IMPORT_C static TInt PhysicalDeviceFind(TInt &aFindHandle,const TDesC &aMatch,TFullName &aName);
	IMPORT_C static DPhysicalDevice* PhysicalDeviceFromHandle(TInt aHandle);
	IMPORT_C static CObjectCon* PhysicalDevices();
//
	IMPORT_C static TInt ChannelFind(TInt &aFindHandle,const TDesC &aMatch,TFullName &aName);
	IMPORT_C static DLogicalChannel* ChannelFromHandle(TInt aHandle);
	IMPORT_C static CObjectCon* Channels();
//
	IMPORT_C static TInt LibraryFind(TInt &aFindHandle,const TDesC &aMatch,TFullName &aName);
	IMPORT_C static DLibrary* LibraryFromHandle(TInt aHandle);
	IMPORT_C static CObjectCon* Libraries();
//
	IMPORT_C static TInt ServerFind(TInt &aFindHandle,const TDesC &aMatch,TFullName &aName);
	IMPORT_C static DServer* ServerFromHandle(TInt aHandle);
//
	IMPORT_C static DSession* SessionFromHandle(TInt aHandle);
	IMPORT_C static void SetSessionPtr(TInt aHandle,const TAny *aSession,TBool aSharable);
	IMPORT_C static TInt MessageComplete(TInt aHandle,TInt aReason);
//
	IMPORT_C static DTransferBuffer* TransferBufferFromHandle(TInt aHandle);
	IMPORT_C static DTransferBuffer* TransferBufferFromHandle(TInt aHandle, DThread *aThread);
	IMPORT_C static CObjectCon* TransferBuffers();
//
	IMPORT_C static DTransferWindow* TransferWindowFromHandle(TInt aHandle);
	IMPORT_C static DTransferWindow* TransferWindowFromHandle(TInt aHandle, DThread* aThread);
	IMPORT_C static CObjectCon* TransferWindows();
//
	IMPORT_C static void NotifyChanges(TUint aChangesMask);
	IMPORT_C static void NotifyThreadDeath(DThread* aThread);
//
	IMPORT_C static void WaitForAnyRequest();
	IMPORT_C static void WaitForRequest(TRequestStatus &aStatus);
	IMPORT_C static void WaitForRequest(TRequestStatus &aStatus1,TRequestStatus &aStatus2);
//
	IMPORT_C static void NameFromHandle(TInt aHandle,DThread *aThread,TDes &aName);
	IMPORT_C static void FullNameFromHandle(TInt aHandle,DThread *aThread,TDes &aFullName);
//
	IMPORT_C static void SvSendReceive(TInt aFunction,TAny *aPtr,TRequestStatus &aStatus);
//
	IMPORT_C static void EventCaptureHook();
	IMPORT_C static void EventReleaseHook();
	IMPORT_C static void EventRequest(TRawEventBuf &anEvent,TRequestStatus &aStatus);
	IMPORT_C static void EventRequestCancel();
//
	IMPORT_C static void SetIdleCallBack(TIdleCallBack aCallback);
	IMPORT_C static void ClearIdleCallBack();
//
	IMPORT_C static void Printf(TRefByValue<const TDesC> aFmt,...);
//
    IMPORT_C static TBool PowerGood();
    IMPORT_C static void NewBattery();
//
    IMPORT_C static TTime HomeTime();
    IMPORT_C static TTimeIntervalSeconds HomeTimeOffset();
//
    IMPORT_C static TInt SwitchOnCount();
//
    IMPORT_C static void LocaleMessageText(TLocaleMessage aMsgNo,TDes& aMsg);
//
	IMPORT_C static TUint32 Random();
	IMPORT_C static void RandomSalt(TUint32 aBitOfSalt);
//
	IMPORT_C static void PanicCurrentThread(const TDesC& aCategory, TInt aReason);
//
	IMPORT_C static void RegisterPBusController(TPBusNum aMachineBusNum,DPeriphBusController* aController,TPBusNum aControllerBusNum);
	IMPORT_C static DPeriphBusController* PBusController(TPBusNum aMachineBusNum=0);
	IMPORT_C static TPBusNum PBusControllerBusNum(TPBusNum aMachineBusNum);
    IMPORT_C static TMediaDevice DeviceFromMediaNumber(TInt aMediaNumber);
	IMPORT_C static TInt ForceMediaRemount(TMediaDevice aDevice,TBool aFullMediaChange);
    IMPORT_C static TPBusNum PeriphBusFromMediaDevice(TMediaDevice aDevice);
	IMPORT_C static TBool LocalMediaIsOpen(TInt aMediaNumber);
	IMPORT_C static TInt64 LocalMediaLenInBytes(TInt aMediaNumber);
	IMPORT_C static void LocalMediaCaps(TInt aMediaNumber,TLocalDriveCaps &anInfo);
	IMPORT_C static void LocalMediaRead(TInt aMediaNumber,TInt64 &aPos,TInt *aLength,TLocalDriveMessageData &aTrg,DThread *aThread,TRequestStatus *aStatus);
	IMPORT_C static void LocalMediaWrite(TInt aMediaNumber,TInt64 &aPos,TInt *aLength,TLocalDriveMessageData &aSrc,DThread *aThread,TRequestStatus *aStatus);
	IMPORT_C static void LocalMediaFormat(TInt aMediaNumber,TInt64 &aPos,TInt *aLength,DThread *aThread,TRequestStatus *aStatus);
	IMPORT_C static TInt LocalMediaSyncRead(TInt aMediaNumber,TInt64 &aPos,TInt *aLength,TLocalDriveMessageData &aTrg);
	IMPORT_C static TInt LocalMediaSyncWrite(TInt aMediaNumber,TInt64 &aPos,TInt *aLength,TLocalDriveMessageData &aSrc);
	IMPORT_C static TInt LocalMediaSyncFormat(TInt aMediaNumber,TInt64 &aPos,TInt *aLength);
#ifdef __WINS__
	IMPORT_C static TInt LocalDriveFromBusNum(TInt aBusNum,DPeriphBusController* aController);
#endif	
	};

class TChunkCreate
	{
public:
	enum {EData,ECode};
public:
	TInt iSize;
	TInt iMaxSize;
	TInt iType;
	};

class TDoubleEndedChunkCreate
	{
public:
	TInt iInitialBottom;
	TInt iInitialTop;
	TInt iMaxSize;
	TInt iType;
	};
//
// Supervisor server functions. Must be called in the server context.
//
class S
	{
public:
	static TBool Initialise();
	static void InitialiseLocalDrivesL();
	static void CreateObjectContainersL();
	static void CreateEventQueueL(TInt aSize);
//
	static TInt OpenObject(TInt &aHandle,DProcess *anOwningProcess,CObjectCon *aCon,const TDesC &aName);
	static TInt OpenObject(TInt &aHandle,CObject *&anObject,DProcess *anOwningProcess,CObjectCon *aCon,const TDesC &aName);
	static TInt OpenObject(TInt &aHandle,DThread *anOwningThread,CObjectCon *aCon,const TDesC &aName);
	static TInt OpenObject(TInt &aHandle,CObject *&anObject,DThread *anOwningThread,CObjectCon *aCon,const TDesC &aName);
	static TInt OpenFindHandle(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,TInt aFindHandle,TOwnerType aType);
	static TInt MakeHandle(CObject *anObj,DProcess *anOwningProcess);
	static TInt MakeHandle(CObject *anObj,DThread *anOwningThread);
	static TInt MakeHandleAndOpen(CObject *anObj,DProcess *anOwningProcess);
	static TInt MakeHandleAndOpen(CObject *anObj,DThread *anOwningThread);
	static TInt DuplicateHandle(DThread *aSrc,TInt aHandle,DThread *aTrg,TInt &aNewHandle,TOwnerType aType);
//
	static void Close(TInt aHandle,DProcess *anOwningProcess,DThread* anOwningThread);
	static void CheckedClose(CObject *anObj);
	static void CheckedClose(CObject *anObj,CObject *anOwner);
	static void OrphanAndDeleteHandles(CObjectIx*& anIndex,CObject* anOwner);
//
	static CObject* ObjectFromHandleL(TInt aHandle);
	static CObject* ObjectFromHandleL(TInt aHandle,DThread *aThread);
	static CObject* ObjectFromHandleL(TInt aHandle,DThread *aThread,CObjectCon *aCon);
	static DChunk& ChunkFromHandleL(TInt aHandle);
 	static DChunk* ChunkFromHandle(TInt aHandle);
 	static DThread& ThreadFromHandleL(TInt aHandle);
 	static DThread* ThreadFromHandle(TInt aHandle);
 	static DProcess& ProcessFromHandleL(TInt aHandle,DThread *aThread);
	static DProcess* ProcessFromHandle(TInt aHandle,DThread *aThread);
	static DLogicalChannel& ChannelFromHandleL(TInt aHandle);
 	static DLogicalChannel* ChannelFromHandle(TInt aHandle);
	static DSession& SessionFromHandleL(TInt aHandle);
	static DSession* SessionFromHandle(TInt aHandle);
	static DLibrary& LibraryFromHandleL(TInt aHandle,DThread *aThread);
	static DLibrary* LibraryFromHandle(TInt aHandle,DThread *aThread);
//
	IMPORT_C static TInt ChunkCreate(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TDesC *aName,TPckgBuf<TChunkCreate> &aChunkCreateInfo,TOwnerType aType);
	static void ChunkCreateL(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TDesC *aName,TInt aMaxSize,DChunk * &aChunk,TOwnerType aType,TChunkType aChunkType);
	IMPORT_C static TInt ChunkCreateDoubleEnded(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TDesC *aName,TPckgBuf<TDoubleEndedChunkCreate> &aChunkCreateInfo,TOwnerType aType);
	static void ChunkCreateDoubleEndedL(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TDesC *aName,TInt aMaxSize,DChunk * &aChunk,TOwnerType aType,TChunkType aChunkType);
	static TInt ChunkOpen(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TDesC &aName,TBool aIsReadOnly,TOwnerType aType);
	static TInt ChunkCompressAll();
//
	static TInt ChannelCreate(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TDesC &aDevice,const TVersion &aVer,const TDesC *aChan,TInt aUnit,const TDesC *aDriver,const TDesC *anInfo,TOwnerType aType);
	static void ChannelCreateL(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TVersion &aVer,const TDesC *aChan,TInt aUnit,CBase *aDriver,const TDesC *anInfo,DLogicalDevice *aDevice,DLogicalChannel * &aChannel,TOwnerType aType);
//
	static TInt LogicalDeviceOpen(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TDesC &aDevice,TOwnerType aType);
	static TInt LogicalDeviceLoad(TInt aHandle,DThread *aThread);
	static TInt LogicalDeviceFree(const TDesC &aDeviceName);
//
	IMPORT_C static TInt PhysicalDeviceLoad(TInt aHandle,DThread *aThread);
	IMPORT_C static TInt PhysicalDeviceFree(const TDesC &aDeviceName);
//
	IMPORT_C static TInt LibraryLoadExact(DProcess* anOwningProcess,DThread* anOwningThread,TLoaderInfo& anInfo);
    static void LibraryLoadExactL(DProcess* anOwningProcess,DThread* anOwningThread,TLoaderInfo& anInfo,DLibrary*& aLib);
//
	static TInt ServerCreate(TInt &aHandle,DThread *anOwningThread,const TDesC &aName);
	static void ServerCreateL(TInt &aHandle,DThread *anOwningThread,const TDesC &aName,DServer * &aServer);
//
	static TInt SessionCreate(TInt &aHandle,DProcess *anOwningProcess,DThread *anOwningThread,const TDesC &aServer,TInt aMessageSlots);
	static void SessionCreateL(TInt &aHandle,DProcess *anOwningProcess,DThread *anOwningThread,TInt aMessageSlots,DServer *aServer,DSession * &aSession);
	static TInt ShareSession(TInt& aHandle,TInt aMode,DThread* aClient,DProcess* aProcess);
	static TInt AttachSession(TInt aHandle,DThread *aClient);
	static TInt AllocateMessages();
	static void MessageComplete(TInt aHandle);
//
	IMPORT_C static TInt MutexCreate(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TDesC *aName,TOwnerType aType);
	static void MutexCreateL(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TDesC *aName,DMutex * &aMutex,TOwnerType aType);
	static TInt MutexOpen(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TDesC &aName,TOwnerType aType);
//
	static TInt ProcessCreate(DProcess* anOwningProcess,DThread* anOwningThread,TLoaderInfo& anInfo,HBufC *aCommand,TOwnerType aType);
	static void ProcessCreateL(DProcess* anOwningProcess,DThread* anOwningThread,TLoaderInfo& anInfo,HBufC *aCommand,DProcess*& aProcess,TOwnerType aType);
	static TInt ProcessOpen(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TDesC &aName,TOwnerType aType);
	static TInt ProcessOpen(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,TProcessId aId,TOwnerType aType);
//
	IMPORT_C static TInt SemaphoreCreate(TInt &aHandle,DProcess *anOwningProcess,DThread *anOwningThread,const TDesC *aName,TInt aCount,TOwnerType aType);
	static void SemaphoreCreateL(TInt &aHandle,DProcess *anOwningProcess,DThread *anOwningThread,const TDesC *aName,TInt aCount,DSemaphore * &aSemaphore,TOwnerType aType);
	static TInt SemaphoreOpen(TInt &aHandle,DProcess *anOwningProcess,DThread *anOwningThread,const TDesC &aName,TOwnerType aType);
//
	static TInt RealTimeThreadCreate(TInt &aHandle,const TDesC &aName,TThreadFunction aFunction,TInt aStackSize,TInt aHeapSize,TAny *aPtr);
	static void RealTimeThreadCreateL(TInt &aHandle,const TDesC &aName,TThreadFunction aFunction,TInt aStackSize,TInt aHeapSize,TAny *aPtr,DThread* &aThread);
	static TInt ThreadCreate(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,TInt aLibraryHandle,const TDesC &aName,TThreadFunction aFunction,TInt aStackSize,RHeap *aHeap,TInt aHeapMinSize,TInt aHeapMaxSize,TAny *aPtr,TOwnerType aType);
	static void ThreadCreateL(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,TInt aLibraryHandle,const TDesC &aName,TThreadFunction aFunction,TInt aStackSize,RHeap *aHeap,TInt aHeapMinSize,TInt aHeapMaxSize,TAny *aPtr,DThread* &aThread,TOwnerType aType);
	static TInt ThreadOpen(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,const TDesC &aFullName,TOwnerType aType);
	static TInt ThreadOpen(TInt &aHandle,DProcess *anOwningProcess,DThread* anOwningThread,TThreadId aId,TOwnerType aType);
//
	static TInt TimerCreate(TInt &aHandle,DThread *anOwningThread);
	static void TimerCreateL(TInt &aHandle,DThread *anOwningThread,DTimer* &aTimer);
//
	static TInt ChangeNotifierCreate(TInt &aHandle,DProcess *anOwningProcess);
	static void ChangeNotifierCreateL(TInt &aHandle,DProcess *anOwningProcess,DChangeNotifier*& aNotifier);
//
	static TInt UndertakerCreate(TInt &aHandle,DProcess *anOwningProcess);
	static void UndertakerCreateL(TInt &aHandle,DProcess *anOwningProcess,DUndertaker*& aNotifier);
//
	static void UnmarkAllLibraries();
//
	static void TransferBufferCreateL(TInt& aHandle, DProcess* aOwningProcess, DThread* aOwningThread, TInt aBufferSize, DTransferBuffer*& aTransferBuffer, TOwnerType aType);
	static TInt TransferBufferCreate(TInt &aHandle, DProcess *anOwningProcess, DThread* aOwningThread, TInt aBufferSize, TOwnerType aType);
	IMPORT_C static TInt TransferBufferCreateNoType(TInt &aHandle, DProcess *anOwningProcess, DThread* aOwningThread, TInt aBufferSize, TOwnerType aType);
	static DTransferBuffer& TransferBufferFromHandleL(TInt aHandle);
	static DTransferBuffer* TransferBufferFromHandle(TInt aHandle);
	static void TransferWindowCreateL(TInt& aHandle, DProcess* aOwningProcess, DThread* aOwningThread, TInt aBufferSize, DTransferWindow*& aTransferWindow, TOwnerType aType);
	IMPORT_C static TInt TransferWindowCreate(TInt &aHandle, DProcess *aOwningProcess, DThread* aOwningThread, TInt aBufferSize, TOwnerType aType);
	IMPORT_C static TInt TransferWindowClose(TInt &aHandle, DProcess *aOwningProcess, DThread* aOwningThread);
	static void TransferWindowOpenL(TInt& aHandle, DProcess* aOwningProcess, DThread* aOwningThread, TOwnerType aType, DTransferWindow*& aTransferWindow);
	static TInt TransferWindowOpen(TInt& aHandle, DProcess* aOwningProcess, DThread* aOwningThread, TOwnerType aType, DTransferWindow*& aTransferWindow);
	static DTransferWindow& TransferWindowFromHandleL(TInt aHandle);
	static DTransferWindow* TransferWindowFromHandle(TInt aHandle);
	};
//
// Exported supervisor server functions. Must be called in the server context.
//
class Sup
	{
public:
	IMPORT_C static TInt RealTimeThreadCreate(TInt &aHandle,const TDesC &aName,TThreadFunction aFunction,TInt aStackSize,TInt aHeapSize,TAny *aPtr);
	};
//
// Functions and data in the platform independent kernel.
//
class DDebugger;
class K
	{
public:
	static CObject *ObjectFromHandle(TInt aHandle,DThread *aThread);
	static CObject *ObjectFromHandle(TInt aHandle,DThread *aThread,CObjectCon *aCon);
	static CObject *ObjectFromHandleNull(TInt aHandle,DThread *aThread);
	static CObject *ObjectFromHandleNull(TInt aHandle,DThread *aThread,CObjectCon *aCon);
//
	static void TryDeliverEvent();
//
	static void	PowerTick();
	static void	PowerSecondTick();
//
    static TUint SlowOpenCheckAllPhysicalDevices(const TDesC &aName,TInt aUnit);
//
	static TInt AddEvent(const TRawEvent& anEvent);
//
	static void PanicCurrentThread(TInt aPanic);
	static TInt TotalCurrentConsumptionInMilliAmps();
//
	static void Randomize();
//
	static TUint AdjustTickCount(TUint aCount);
	static TUint AdjustedTickCounter();
public:
	static RHeapK *Heap;
	static DChunk *DataBssChunk;
	static DChunk *StackHeapChunk;
//
    static TUint NextId;
//
	static CObjectConIx *Container;
//
	static CObjectCon *LogicalDevices;
	static CObjectCon *PhysicalDevices;
	static CObjectCon *Mutexes;
	static CObjectCon *Processes;
	static CObjectCon *Chunks;
	static CObjectCon *Semaphores;
	static CObjectCon *Servers;
	static CObjectCon *Threads;
	static CObjectCon *Timers;
	static CObjectCon *Channels;
	static CObjectCon *Sessions;
	static CObjectCon *Libraries;
	static CObjectCon *ChangeNotifiers;
	static CObjectCon *Undertakers;
	static CObjectCon *TransferBuffers;
	static CObjectCon *TransferWindows;
//
	static TTransferBufferGarbageQ* TransferBufferGarbageQ;
	static TTickQ* TickQ;
	static TSecondQ* SecondQ;
	static TInactivityQ* InactivityQ;
	static TGlobalAllocQ *GlobalAllocQ;
	static DThread *NullThread;
	static TDfcQue DfcQ;
//
	static DProcess* TheKernelProcess;
	static DProcess *SvProcess;
	static DThread *SvThread;
	static TSvrMessage SvMessage;
//
	static TLanguage Language;
	static TBool UniCode;
	static TBuf<KMaxCurrencySymbol> CurrencySymbol;
	static TBuf<KMaxShortDateFormatSpec> ShortDateFormatSpec;
	static TBuf<KMaxLongDateFormatSpec> LongDateFormatSpec;
	static TBuf<KMaxTimeFormatSpec> TimeFormatSpec;
	static const TFatUtilityFunctions* FatUtilityFunctions;
	static const TText * const *DateSuffixTable;
	static const TText * const *DayTable;
	static const TText * const *DayAbbTable;
	static const TText * const *MonthTable;
	static const TText * const *MonthAbbTable;
	static const TText * const *AmPmTable;
	static const TText * const *MsgTable;
	static const LCharSet *CharSet;
	static const TUint8 *TypeTable;
	static const TText *UpperTable;
	static const TText *LowerTable;
	static const TText *FoldTable;
	static const TText *CollTable;
//
// for default LOCALE setup when changed to new locale.
  
    static DLibrary * LocaleLib;
    static TBool DefaultLocale;
	static TLanguage DefLanguage;
	static TBuf<KMaxCurrencySymbol> DefCurrencySymbol;
	static TBuf<KMaxShortDateFormatSpec> DefShortDateFormatSpec;
	static TBuf<KMaxLongDateFormatSpec> DefLongDateFormatSpec;
	static TBuf<KMaxTimeFormatSpec> DefTimeFormatSpec;
	static const TFatUtilityFunctions* DefFatUtilityFunctions;
	static const TText * const *DefDateSuffixTable;
	static const TText * const *DefDayTable;
	static const TText * const *DefDayAbbTable;
	static const TText * const *DefMonthTable;
	static const TText * const *DefMonthAbbTable;
	static const TText * const *DefAmPmTable;
	static const TText * const *DefMsgTable;
	static const LCharSet *DefCharSet;
	static const TUint8 *DefTypeTable;
	static const TText *DefUpperTable;
	static const TText *DefLowerTable;
	static const TText *DefFoldTable;
	static const TText *DefCollTable;
//
	static TRawEvent *EventHeadPtr;
	static TRawEvent *EventTailPtr;
	static TRawEvent *EventBufferStart;
	static TRawEvent *EventBufferEnd;
	static TAny *EventRequestPtr;
	static TRequestStatus *EventStatusPtr;
	static DThread *EventThread;
//
	static TUint TickCounter;
	static TUint RtcTickRef;
	static TUint TickCountRef;
    static TTimeIntervalSeconds AutoSwitchOffTimeout;
    static TBool ExternalPowerPresent;

	static TBool JustInTime;
//
	static TLocDrv TheDrives[KMaxLocalDrives];
	static DMedia *TheMedia[KMaxLocalDrives];
	static DMediaChangeNotifierBase* TheMediaChangeNotifier[KMaxPBusSockets];
    static TPBusInfo PBusController[KMaxPBusSockets];
	static TInt RegisteredBusControllerCount;
//
	static TInt ClientErrorCode;
//
    static TBool PowerGood;
	static TIdleCallBack IdleCallBack;
	static DPowerModel *PowerModel;
//
    static TInt DriverCurrentMilliAmps;
//
	static TTimeIntervalMicroSeconds32 TickPeriod;
	static TInt TickFrequency;		// approximate tick frequency
    static TTime Year2000;
	static TInt XtalError;			// crystal error in parts per 2^24
//
    static TInt SwitchOnCount;
    static TBool LastCaseClosed;
//
    static TInt SupplyInfoFlags;
//
	static TInt MemoryLowThreshold;
	static TInt MemoryGoodThreshold;
	static TInt MemoryNotifierFlags;
	};

/**
 * Platform dependent functions exported from E32KERN.DLL
 */
class Plat
	{
public:
	IMPORT_C static void Panic(const TDesC &aName,TInt aPanicNumber);
	IMPORT_C static void Fault(const TDesC &aName,TInt aFaultNumber);
	IMPORT_C static TTime SystemTime();
	IMPORT_C static TInt SetSystemTime(const TTime& aTime);
    IMPORT_C static TTimeIntervalSeconds SystemTimeInSecondsFrom2000();
	IMPORT_C static TUint TickCount();
	IMPORT_C static TTimerLockSpec LockPeriod();
	IMPORT_C static void ScreenInfo(TDes8 &anInfo);
	IMPORT_C static TInt NullThread(TAny *aPtr);
	IMPORT_C static void EnterCS();
	IMPORT_C static void LeaveCS();
	IMPORT_C static DThread &CurrentThread();
	IMPORT_C static DProcess &CurrentProcess();
	IMPORT_C static TInt BindExtInterrupt(TInt anExtIntID,const TDesC8& aName);
	IMPORT_C static TUint DebugMask();
	IMPORT_C static void DebugInit();
	IMPORT_C static DDebugger *Debugger();
	IMPORT_C static void SetDebugger(DDebugger *aDebugger);
	IMPORT_C static void SetSoundRecordState(TBool aState);
	IMPORT_C static void Reset(TMachineStartupType aType);
	IMPORT_C static void WaitAtLeastAMicroSecond();
	IMPORT_C static void OsSwitchOnScreen();
#ifdef __WINS__
	IMPORT_C static TBool* MediaDoorOpenPtr();
	IMPORT_C static TInt* CurrentPBusDevicePtr();
	IMPORT_C static void SetMediaChangeCallBackPtr(TCallBack* aPtr);
#endif
	IMPORT_C static TBool CheckInWservThread();
	};

/**
 * Functions and data in the platform dependent kernel.
 */
class P
	{
public:
	static TBool Initialise();
	static void Init4();
	static void CreateVariant();
	static void FindRomRootDirectory();
	static DChunk *NewChunkL(TBool aGlobal, TChunkType aType, DProcess* aProcess);
	static DSemaphore *NewSemaphore();
	static DMutex *NewMutex();													  
	static DThread *NewThread(TThreadCreateType aType);
	static DProcess *NewProcess(TInt aAttributes);
	static DLibrary *NewLibrary(TInt aNumDeps);
	static DTransferBuffer *NewTransferBufferL();
	static DTransferWindow *NewTransferWindowL();
	static void SetDebugMask(TUint32 aVal);
	static TInt MicroSecondsToTicks(TInt aMicroSeconds);
	static TUint RoundTicksToSecond(TUint aTicks);
	static TUint TimerLockSpecToTicks(TTimerLockSpec aLock);
	static TPtrC8 StartupBeep(TMachineStartupType aReason);
	static void EnterTimeCS();
	static void LeaveTimeCS();
	static void EnterEventCS();
	static void LeaveEventCS();
	static void WsRegisterThread(TThreadFunction aFunction);
	static void FsRegisterThread(TThreadFunction aFunction);
	static void OutputToCom1(TUint aLetter);
	static void Print(const TDesC* aBuf);
	static void Break();
	static void HalInfo(TDes8 &anInfo);
	static TInt HalPageSize();
	static TInt HalFunction(THalFunction aFunction,TAny* aData);
    static TInt ExternalPowerPresent();
    static TInt DisableIrqsToLevel2();
    static void RestoreIrqs(TInt aLevel);
	static TInt IdleCurrentInMilliAmps();
	static TInt RunningCurrentInMilliAmps();
//
	static void PowerOn();
	static void PowerStandby();
	static void PowerStandby(TTimeIntervalSeconds& aWakeUp);
	static void Restart();
//
	static void Wait(TInt aDelay);
	static void BlockThreads(TBlockType aType);
	static TBool PasswordIsEnabled();
	static TInt PasswordSetEnabled(const TPassword& aPassword,TBool aIsEnabled);
	static TBool PasswordIsValid(const TPassword& aPassword);
	static TInt PasswordSet(const TPassword& anOldPassword,const TPassword& aNewPassword);
	static TLDriveAssignInfo DeviceInfoFromDrive(TInt aDriveNumber);
	static TMediaDevice DeviceFromMedia(TInt aMediaNumber);
	static TMediaDeviceAssignInfo MediaInfoFromDevice(TMediaDevice aDevice);
	static TPBusNum PeriphBusFromMediaDevice(TMediaDevice aDevice);
	static void PowerUpPeriphBus(TPBusNum aBus,DThread *aThread,TRequestStatus *aReqStat);
	static TInt BusDevPowerStatus(TInt aSocket);
    static TInt ForceMediaChange(TMediaDevice aDevice);
	static TInt ReadPeriphBusPasswordData(TDes8 &aBuf);
	static TInt WritePeriphBusPasswordData(TDesC8 &aBuf);
	static TInt PeriphBusPasswordStoreLengthInBytes();
	static SLocaleData &Locale();
    static TPtrC8 MachineConfiguration();
    static void SetMachineConfiguration(const TDesC8& aConfig);
    static TBool TestBootSequence();
	static void WsSwitchOnScreen();
	static void WsRegisterSwitchOnScreenHandling(TBool aState);
    static void CheckPowerSupplies();
	static void InvalidateTickCounter();
	static void SynchroniseTickCounter();
#if defined(__WINC__)
	static void SignalKernelStarted();
	static void SignalFileServerStarted();
#endif
	static TInt MachineCurrentInMilliAmps();
	static void CreateSupervisor();
	static void SupervisorReceive(TRequestStatus &aStatus);
	static TUint FastCounter();

private:
	static void DebugPortChanged();
	};

/********************************************
 * Kernel-side trap harness
 * Doesn't call user-side trap handlers
 ********************************************/
class TTrapK : public TTrap
	{
public:
	IMPORT_C TInt Trap(TInt& aResult);
	IMPORT_C static void UnTrap();
	};

#define KTRAP(_r,_s)	{							\
						TTrapK __t;					\
						if (__t.Trap(_r)==0)		\
							{						\
							_s;						\
							TTrapK::UnTrap();		\
							}						\
						}

#define KTRAPD(_r,_s)	TInt _r;					\
						{							\
						TTrapK __t;					\
						if (__t.Trap(_r)==0)		\
							{						\
							_s;						\
							TTrapK::UnTrap();		\
							}						\
						}

//
typedef TBufC8<KMaxPassword<<3> TPasswordToken;
//
// ROM configuration
//
enum TRomType
	{
	// These match values used in the Bootstrap
	ERomTypeFlash = 1,		// Or ROM
	ERomTypeRamAsRom = 4,
	};
//
class TSuperPageRomConfig
	{
public:
	TUint32	iSize;		// size of ROM in bytes, 0=no ROM present
	TUint32	iWidth;		// bus width in bits
	TUint32	iSpeed;		// number of wait states
	TUint32	iType;		// enum TRomType
	};
//
// Digitizer calibration
//
class TDigitizerCalibrateValues
    {
public:
    TInt iR11;
    TInt iR12;
    TInt iR21;
    TInt iR22;
    TInt iTx;
    TInt iTy;
    };


class TStackInfo
	{
public:
	TUint Size() const {return (iTop-iBottom)*sizeof(TUint32);}
public:
	TUint32* iBottom;
	TUint32* iTop;
	};

//
// The super page
// This structure holds values discovered by the bootstrap that
// are required by the generic kernel.
//
class TSuperPage
	{
public:
	// Start of data owned by the bootstrap
	// It must match the definition there
	TInt iRamDriveOffset;
	TInt iRamDriveSize;
	TInt iMaxFreeRam;
	TInt iTotalRomSize;
	TInt iTotalRamSize;
	TLinAddr iPageDir;
	TLinAddr iRamBootData;
	TLinAddr iBootTable;				// used temporarily by bootstrap
	TInt iMmuState;						// used temporarily by bootstrap
	TSuperPageRomConfig iRomConfig[8];	// index = chip select number
	TUint iRomBasePhys[8];
	TUint iActiveCpu;
	TUint iActiveAsic;
	TUint iActiveVariant;
	TLinAddr iPrimaryEntry;
	TInt iDebugMask;
	TLinAddr iRomRootDirectoryList;
	TUint32 iLowestStackBottom;
	TUint32 iHighestStackTop;
	TStackInfo iNullStack;
	TUint32 iDebugPort;
	// End of bootstrap data
	};

//
// The kernel's page
// This structure contains generic kernel data that needs
// to be preserved over a warm reset.
//
class TKernelPage
	{
public:
	// Start of data owned by the generic kernel
	TUint32 iSignature;		// 'EPOC'
	TVersion iCurrentOSVersion;

	DDebugger *iDebugger;		// Needs a constant address for external debugger sw
	TMachineStartupType iStartupReason;
	TInt iKernelFault;
	TInt iKernelExcId;
	TExcInfo iKernelExcInfo;

	TTime LastSetTime;		// The last time set by the user
	TInt TheRTCCorrection;		// The accumulated RTC correction due to crystal errors

	TTime iMainBatteryInsertionTime;
	TTimeIntervalMicroSeconds iMainBatteryInUseMicroSeconds;
	TTimeIntervalMicroSeconds iExternalPowerInUseMicroSeconds;
	TInt64 iMainBatteryMilliAmpTicks;
	// End of kernel data
	};

//
// The machine configuration
// This struture contains system wide settings that should be
// persisted over a warm reset and machine state saves.
//
class TMachineConfiguration
	{
public:
	// system wide settings
	SLocaleData iLocale;

	TBool iPasswordEnabled;
	TPasswordToken iPasswordToken;

	// platform specific data
	TInt iXtalError;
	TInt64 iMachineUniqueId;
	TDigitizerCalibrateValues iCalibration;
	TDigitizerCalibrateValues iCalibrationSaved;
	TDigitizerCalibrateValues iCalibrationFactory;
	};

inline TSuperPage &TheSuperPage();
inline TKernelPage &TheKernelPage();
inline TMachineConfiguration &TheMachineConfiguration();
#ifdef __WINS__
GLREF_D TSuperPage TheWinsSuperPage;
GLREF_D	TKernelPage TheWinsKernelPage;
GLREF_D TMachineConfiguration TheWinsMachineConfiguration;
#endif
//
#ifdef _DEBUG
#define __KTRACE_OPT(a,p) {if((Plat::DebugMask()&(a))==(a))p;}
#define __KTRACE_ANY(a,p) {if(Plat::DebugMask()&(a))p;}
#define KHARDWARE		0x00000001
#define KBOOT			0x00000002
#define KSERVER			0x00000004
#define KMMU			0x00000008
#define KSEMAPHORE		0x00000010
#define KSCHED			0x00000020
#define KPROC			0x00000040
#define KEXEC			0x00000080
#define KEXECFAST		0x00000100
#define KTHREAD			0x00000200
#define KDLL			0x00000400
#define KLOGON			0x00000800
#define KPBUS1			0x00001000
#define KPBUS2			0x00002000
#define KPBUSDRV		0x00004000
#define KPOWER			0x00008000
#define KTIMING			0x00010000
#define KEVENT			0x00020000
#define KSCRATCH		0x00040000	// reserved for temporary debugging
#define KMEMTRACE		0x00080000  // Trace memory and heap allocs
#define KIPC			0x00100000	// Trace IPC system and messages
#define KDEBUGGER		0x00200000  // Trace App Debugging API (RDebug)
#define	KTLB			0x00400000	// software TLB loading if any
#define	KVIDEO			0x00800000	// Trace video calls
#define KUSB            0x01000000  // Trace USB calls
#define KPANIC			0x80000000
#define KALWAYS			0xbfffffff
#else
#define __KTRACE_OPT(a, p)
#define __KTRACE_ANY(a, p)
#endif 
//
#ifdef __ENABLE_NOTIFY_DEBUGGER__
#define __KNOTIFY_DEBUGGER(a) {if(Plat::Debugger())Plat::Debugger()->a;}
#else
#define __KNOTIFY_DEBUGGER(a)
#endif
//
#include <k32std.inl>
#endif

#if defined(__WINS__)
// these functions are only actually called under WINC
IMPORT_C void E32Initialize();
IMPORT_C void E32DeInitialize();
IMPORT_C void E32ExitProcess();
#endif
