// U32STD.H
//
// Copyright (c) 1995-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __U32STD_H__
#define __U32STD_H__
#include <e32std.h>
#include <e32base.h>
#include <e32svr.h>

//#define __MINIMUM_MACHINE_CODE__
#define __ENABLE_NOTIFY_DEBUGGER__		// Enable the kernel debug support

#if defined(__WINS__)
#define __NAKED__ __declspec( naked )
#define __DUMMY__ TInt,
#ifndef __MINIMUM_MACHINE_CODE__
#define __MEM_MACHINE_CODED__
#endif
#define __CPU_X86
#endif

#if defined(__MX86__)
#define __NAKED__ __declspec( naked )
#define __DUMMY__
#ifndef __MINIMUM_MACHINE_CODE__
#define __MEM_MACHINE_CODED__
#endif
#define __CPU_X86
#endif


#if defined(__MARM__)
	#define __NAKED__ __declspec( naked )
	#define __DUMMY__
	#define __CPU_ARM

#ifndef __MINIMUM_MACHINE_CODE__
#if !defined(__BIG_ENDIAN__)
	#define __MEM_MACHINE_CODED__
	#define __DES_MACHINE_CODED__
	#define __REGIONS_MACHINE_CODED__
	#define __DES8_MACHINE_CODED__
	#define __DES16_MACHINE_CODED__
	#define __HEAP_MACHINE_CODED__
	#define __REALS_MACHINE_CODED__
	#define __COBJECT_MACHINE_CODED__
	#define __CACTIVESCHEDULER_MACHINE_CODED__
	#define __CSERVER_MACHINE_CODED__
	#define __FASTEXEC_MACHINE_CODED__
	#define __SCHEDULER_MACHINE_CODED__
	#define __MESSAGE_MACHINE_CODED__
	#define __ARRAY_MACHINE_CODED__
#if defined(__MARM_ARM4__) || defined(__MARM_ARMI__) || defined(__MARM_THUMB__)
	#define __DES16_MACHINE_CODED_HWORD__
#endif
#endif
	#define __PROCESS_MACHINE_CODED__
#endif

#if defined(__MEIG__)
#define __CPU_ARM720T__
#elif defined(__MISA__)
#define __CPU_SA1__
#elif defined(__MLNK__)
#define __CPU_ARM720T__
#elif defined(__MCOY__) || defined(__MCOT__)
#define __CPU_XSCALE__
#elif defined(__MINT__) || defined(__MINK__)
#define __CPU_ARM920T__
#elif defined(__MTEMPLATE__)
#define __CPU_ARM720T__
#elif defined(__MHELEN__)
#define __CPU_ARM925T__
#endif

#if defined(__CPU_ARM710T__) || defined(__CPU_ARM720T__)
	#define __CPU_ARMV4T
	#define __CPU_ARM_ABORT_MODEL_UPDATED
	#define __CPU_WRITE_BUFFER
#endif
#if defined(__CPU_ARM720T__)
	#define __CPU_HAS_JTAG_DEBUG_OUTPUT
#endif
#if defined(__CPU_ARM920T__)	// ARM920T in writeback mode
	#define __CPU_ARMV4T
	#define __CPU_ARM_ABORT_MODEL_RESTORED
	#define __CPU_SPLIT_CACHE
	#define __CPU_SPLIT_TLB
	#define __CPU_WRITE_BUFFER
	#define __CPU_WRITE_BACK_CACHE
	#define __CPU_CACHE_FLUSH_BY_WAY_SET_INDEX
	#define __CPU_CACHE_POLICY_IN_PTE
	#define __CPU_HAS_CACHE_TYPE_REGISTER
	#define __CPU_HAS_SINGLE_ENTRY_ITLB_FLUSH
	#define __CPU_HAS_SINGLE_ENTRY_ICACHE_FLUSH
	#define __CPU_EXC_VECTORS_MOVABLE
	#define __CPU_HAS_JTAG_DEBUG_OUTPUT
#endif
#if defined(__CPU_ARM926T__)	// ARM926T in writeback mode
	#define __CPU_ARMV5TJ
	#define __CPU_ARM_ABORT_MODEL_RESTORED
	#define __CPU_SPLIT_CACHE
	#define __CPU_SPLIT_TLB
	#define __CPU_WRITE_BUFFER
	#define __CPU_WRITE_BACK_CACHE
	#define __CPU_CACHE_FLUSH_BY_WAY_SET_INDEX
	#define __CPU_CACHE_POLICY_IN_PTE
	#define __CPU_HAS_CACHE_TYPE_REGISTER
	#define __CPU_HAS_SINGLE_ENTRY_ITLB_FLUSH
	#define __CPU_HAS_SINGLE_ENTRY_ICACHE_FLUSH
	#define __CPU_EXC_VECTORS_MOVABLE
	#define __CPU_HAS_JTAG_DEBUG_OUTPUT
	#define __CPU_HAS_ETM_PROCID_REG
#endif
#if defined(__CPU_XSCALE__)		// XScale in writethru mode
	#define __CPU_ARMV5TE
	#define __CPU_ARM_ABORT_MODEL_RESTORED
	#define __CPU_SPLIT_CACHE
	#define __CPU_SPLIT_TLB
	#define __CPU_WRITE_BUFFER
	#define __CPU_WRITE_BACK_CACHE
	#define __CPU_CACHE_WRITE_ALLOCATE
	#define __CPU_CACHE_FLUSH_BY_LINE_ALLOC
	#define __CPU_CACHE_POLICY_IN_PTE
	#define __CPU_HAS_CACHE_TYPE_REGISTER
	#define __CPU_HAS_SINGLE_ENTRY_ITLB_FLUSH
	#define __CPU_HAS_SINGLE_ENTRY_ICACHE_FLUSH
	#define	__CPU_HAS_BTB
	#define __CPU_USE_MMU_TEX_FIELD
	#define __CPU_EXC_VECTORS_MOVABLE
#endif
#if defined(__CPU_ARM925T__)	// ARM925T in write-through mode
	#define __CPU_ARMV4T
	#define __CPU_ARM_ABORT_MODEL_RESTORED
	#define __CPU_SPLIT_CACHE
	#define __CPU_SPLIT_TLB
	#define __CPU_WRITE_BUFFER
//	#define __CPU_WRITE_BACK_CACHE
	#define __CPU_CACHE_FLUSH_BY_WAY_SET_INDEX
	#define __CPU_CACHE_POLICY_IN_PTE
	#define __CPU_HAS_CACHE_TYPE_REGISTER
	#define __CPU_HAS_SINGLE_ENTRY_ITLB_FLUSH
	#define __CPU_HAS_SINGLE_ENTRY_ICACHE_FLUSH
	#define __SUPPORT_PARTNER_OS__
	#define __CPU_EXC_VECTORS_MOVABLE
#endif
#if defined(__CPU_SA1__)
	#define __CPU_ARMV4
	#define __CPU_ARM_ABORT_MODEL_RESTORED
	#define __CPU_SPLIT_CACHE
	#define __CPU_SPLIT_TLB
	#define __CPU_WRITE_BUFFER
	#define __CPU_WRITE_BACK_CACHE
	#define __CPU_CACHE_FLUSH_BY_DATA_READ
    #define __CPU_EXC_VECTORS_MOVABLE
#endif
#if defined(__MHELEN__)
    #define __CPU_ARMV4T // Support Thumb
	#define __CPU_ARM_ABORT_MODEL_UPDATED
	#define __CPU_SPLIT_CACHE
	#define __CPU_SPLIT_TLB
    #define __CPU_WRITE_BUFFER
	//#define __CPU_WRITE_BACK_CACHE  // COPY BACK
    #define __CPU_CACHE_POLICY_IN_PTE // WRITE_THROUGH
#endif
#endif

#ifdef __CPU_ARMV4
	#define __CPU_64BIT_MULTIPLY
#endif
#ifdef __CPU_ARMV4T
	#define __CPU_THUMB
	#define __CPU_ARM_SUPPORTS_BX
	#define __CPU_64BIT_MULTIPLY
#endif
#if defined(__CPU_ARMV5TE) || defined(__CPU_ARMV5TJ)
	#define __CPU_THUMB
	#define __CPU_ARM_SUPPORTS_BX
	#define __CPU_64BIT_MULTIPLY
	#define __CPU_ARM_LDR_PC_SETS_TBIT
	#define __CPU_ARM_HAS_CLZ
	#define __CPU_ARM_HAS_MCRR
#endif
#if defined(__CPU_THUMB) || defined(__MARM_ARMI__) || defined(__MARM_THUMB__)
#if defined(__ARM_ARCH_4T__) || defined(__thumb__)	// i.e. are we using -march=armv4t or thumb
	#define __SUPPORT_THUMB_INTERWORKING
#endif
#endif

// ARM CPU macros to allow Thumb/Non-thumb builds
#ifdef __CPU_ARM

#ifdef __SUPPORT_THUMB_INTERWORKING
#define __JUMP(cc,r) asm("bx"#cc " "#r )
#ifdef __CPU_ARM_LDR_PC_SETS_TBIT
#define __POPRET(rlist) asm("ldmfd sp!, {"##rlist##"pc} ")
#define __CPOPRET(cc,rlist) asm("ldm"#cc "fd sp!, {"##rlist##"pc} ")
#else
#define __POPRET(rlist) asm("ldmfd sp!, {"##rlist##"lr} ");\
						asm("bx lr ")
#define __CPOPRET(cc,rlist)	asm("ldm"#cc "fd sp!, {"##rlist##"lr} ");\
							asm("bx"#cc " lr ")
#endif
#else
#define __JUMP(cc,r) asm("mov"#cc " pc, "#r )
#define __POPRET(rlist) asm("ldmfd sp!, {"##rlist##"pc} ")
#define __CPOPRET(cc,rlist) asm("ldm"#cc "fd sp!, {"##rlist##"pc} ")
#endif

#ifdef __MARM_THUMB__
#define __SWITCH_TO_ARM		asm("push {r0} ");\
							asm("add r0, pc, #4 ");\
							asm("bx r0 ");\
							asm("nop ");\
							asm(".align 2 ");\
							asm(".code 32 ");\
							asm("ldr r0, [sp], #4 ")
#define __END_ARM			asm(".code 16 ")
#else
#define __SWITCH_TO_ARM
#define __END_ARM
#endif

#define CC_EQ	0
#define	CC_NE	1
#define CC_CS	2
#define CC_CC	3
#define CC_MI	4
#define CC_PL	5
#define CC_VS	6
#define CC_VC	7
#define CC_HI	8
#define CC_LS	9
#define CC_GE	10
#define CC_LT	11
#define CC_GT	12
#define CC_LE	13
#define	CC_AL	14

#ifdef __CPU_ARM_HAS_CLZ
#define CLZ(Rd,Rm)		asm(".word %a0" : : "i" ((TInt)0xe1600010|((Rd)<<12)|(Rm)));
#define CLZcc(cc,Rd,Rm)	asm(".word %a0" : : "i" ((TInt)0x01600010|((cc)<<28)|((Rd)<<12)|(Rm)));
#endif
#ifdef __CPU_ARM_HAS_MCRR
#define MCRR(cop,opc,Rd,Rn,CRm)			asm(".word %a0" : : "i" ((TInt)0xec400000|((Rn)<<16)|((Rd)<<12)|((cop)<<8)|((opc)<<4)|(CRm)));
#define MCRRcc(cc,cop,opc,Rd,Rn,CRm)	asm(".word %a0" : : "i" ((TInt)0x0c400000|((cc)<<28)|((Rn)<<16)|((Rd)<<12)|((cop)<<8)|((opc)<<4)|(CRm)));
#define MRRC(cop,opc,Rd,Rn,CRm)			asm(".word %a0" : : "i" ((TInt)0xec500000|((Rn)<<16)|((Rd)<<12)|((cop)<<8)|((opc)<<4)|(CRm)));
#define MRRCcc(cc,cop,opc,Rd,Rn,CRm)	asm(".word %a0" : : "i" ((TInt)0x0c500000|((cc)<<28)|((Rn)<<16)|((Rd)<<12)|((cop)<<8)|((opc)<<4)|(CRm)));
#endif

#ifdef __CPU_XSCALE__
#define MAR(acc,RdLo,RdHi)			MCRR(0,0,RdLo,RdHi,acc)
#define MARcc(cc,acc,RdLo,RdHi)		MCRR(cc,0,0,RdLo,RdHi,acc)
#define MRA(acc,RdLo,RdHi)			MRRC(0,0,RdLo,RdHi,acc)
#define MRAcc(cc,acc,RdLo,RdHi)		MRRC(cc,0,0,RdLo,RdHi,acc)
#define MIAgen(cc,acc,Rm,Rs,opc3)	asm(".word %a0" : : "i" ((TInt)0x0e200010|((cc)<<28)|((opc3)<<16)|((Rs)<<12)|((acc)<<5)|(Rm)));
#define MIA(acc,Rm,Rs)				MIAgen(CC_AL,acc,Rm,Rs,0)
#define MIAPH(acc,Rm,Rs)			MIAgen(CC_AL,acc,Rm,Rs,8)
#define MIABB(acc,Rm,Rs)			MIAgen(CC_AL,acc,Rm,Rs,12)
#define MIATB(acc,Rm,Rs)			MIAgen(CC_AL,acc,Rm,Rs,13)
#define MIABT(acc,Rm,Rs)			MIAgen(CC_AL,acc,Rm,Rs,14)
#define MIATT(acc,Rm,Rs)			MIAgen(CC_AL,acc,Rm,Rs,15)
#define MIAcc(cc,acc,Rm,Rs)			MIAgen(cc,acc,Rm,Rs,0)
#define MIAPHcc(cc,acc,Rm,Rs)		MIAgen(cc,acc,Rm,Rs,8)
#define MIABBcc(cc,acc,Rm,Rs)		MIAgen(cc,acc,Rm,Rs,12)
#define MIATBcc(cc,acc,Rm,Rs)		MIAgen(cc,acc,Rm,Rs,13)
#define MIABTcc(cc,acc,Rm,Rs)		MIAgen(cc,acc,Rm,Rs,14)
#define MIATTcc(cc,acc,Rm,Rs)		MIAgen(cc,acc,Rm,Rs,15)
#endif

#endif // __CPU_ARM

// Trace macros for User-side code, controlled by the debug mask
// They should really work under WINS/WINC too, but at the moment they
// cause the kernel to go re-entrant.
#if defined(_DEBUG) && !defined(__WINS__)
#define __UTRACE_OPT(a,p) {if((UserSvr::DebugMask()&(a))==(a))p;}
#define __UTRACE_ANY(a,p) {if(UserSvr::DebugMask()&(a))p;}
#else
#define __UTRACE_OPT(a,p)
#define __UTRACE_ANY(a,p)
#endif

// Entry point reasons - private between user library and stub
#if defined(__WINS__)
enum TWin32DllReason {EWin32DllProcessAttach=60,EWin32DllThreadAttach,EWin32DllThreadDetach,EWin32DllProcessDetach};
#endif

struct TUnicodeDataSet;                 // forward declaration
struct TCollationDataSet;               // forward declaration

/*
The LCharSet structure is used in Unicode builds to supply locale-specific
character attribute and collation data.

The structure is defined in both builds to avoid having to have a dummy ExecHandler::GetLocaleCharSet function
with a different signature in the 8-bit build.
*/
struct LCharSet
	{
	const TUnicodeDataSet* iCharDataSet;			// if non-null, character data overriding standard Unicode data
	const TCollationDataSet* iCollationDataSet;		// if non-null, locale-specific collation data
	};

//
// The bits in the type table (non-Unicode build only)
//
#ifndef _UNICODE
const TUint __U=0x01; // Uppercase letter
const TUint __L=0x02; // Lowercase letter
const TUint __D=0x04; // Decimal digit
const TUint __S=0x08; // Space
const TUint __P=0x10; // Punctuation
const TUint __C=0x20; // Control character
const TUint __X=0x40; // Hex digit
const TUint __B=0x80; // A blank character
#endif

//
enum TMatchType {EMatchNormal,EMatchFolded,EMatchCollated};
enum TDesType {EBufC,EPtrC,EPtr,EBuf,EBufCPtr};
//
const TUint KMaskDesLength=0xfffffff;
const TInt KShiftDesType=28;
//
// Contants for iFlags in DProcess and DThread
//
const TUint KThreadFlagMark=0x01;
const TUint KThreadFlagNotifyIfDie=0x02;
const TUint KThreadFlagSystem=0x04;
const TUint KThreadFlagProtected=0x08;
const TUint KThreadFlagBusy=0x10;
const TUint KThreadFlagLastChance=0x10000;
const TUint KThreadFlagMain=0x80000000;
const TUint KProcessLoadedFromRam=0x20000;
//
struct SPtrC8 {TInt length;const TUint8 *ptr;};
struct SBufC8 {TInt length;TUint8 buf[1];};
struct SPtr8 {TInt length;TInt maxLength;TUint8 *ptr;};
struct SBuf8 {TInt length;TInt maxLength;TUint8 buf[1];};
struct SBufCPtr8 {TInt length;TInt maxLength;SBufC8 *ptr;};

struct SPtrC16 {TInt length;const TUint16 *ptr;};
struct SBufC16 {TInt length;TUint16 buf[1];};
struct SPtr16 {TInt length;TInt maxLength;TUint16 *ptr;};
struct SBuf16 {TInt length;TInt maxLength;TUint16 buf[1];};
struct SBufCPtr16 {TInt length;TInt maxLength;SBufC16 *ptr;};

const TInt KChunkShiftBy0=0;
const TInt KChunkShiftBy1=KMinTInt;

#if defined(_DEBUG)
const TInt KHeadSize=(sizeof(RHeap::SDebugCell)); // Size of allocated cell header with space for heaven info
const TInt KAlignMask=(sizeof(TInt)-1); // Alignment mask
const TInt KMinCellSize=(TInt)sizeof(RHeap::SDebugCell);
#else
const TInt KHeadSize=(sizeof(RHeap::TAllocSize)); // Size of allocated cell header
const TInt KAlignMask=(KHeadSize-1); // Alignment mask
const TInt KMinCellSize=(TInt)sizeof(RHeap::SCell);
#endif

const TInt KCellSize=(sizeof(RHeap::SCell)); // Size of free cell header
const TInt KAlignMaskNot=(~KAlignMask); // Inverted alignment mask

class TCheckedHeapWalk : public THeapWalk
	{
public:
	TCheckedHeapWalk(const RHeap &aHeap);
	virtual void Info(THeapWalk::TCellType aType,TAny *aBase,TInt aLength);
	inline TInt FreeCount();
	inline TInt TotalAllocSize();
private:
	TInt iFreeCount;
	TInt iTotalAllocSize;
    };
inline TInt TCheckedHeapWalk::FreeCount()
	{return(iFreeCount);}
inline TInt TCheckedHeapWalk::TotalAllocSize()
	{return(iTotalAllocSize);}
//
inline TInt align(TInt aSize)
//
// Align a size to the round up boundary.
//
	{

	return((aSize+KAlignMask)&KAlignMaskNot);
	}
//
// Supervisor server messages
//
const TUint KThreadHandle=0x40000000;
enum TSvMessage
	{
	ESvChunkCreateLocal,ESvChunkCreateGlobal,ESvChunkOpen,ESvChunkAdjust,
	ESvChunkCompressAll,
	ESvLogicalDeviceLoad,ESvLogicalDeviceFree,ESvLogicalDeviceOpen,
	ESvPhysicalDeviceLoad,ESvPhysicalDeviceFree,
	ESvChannelCreate,ESvChannelControl,
	ESvLibraryLoadExact,ESvLibraryLoaded,
	ESvFindHandleOpen,ESvHandleDuplicate,ESvHandleClose,
	ESvHeapMarkStart,ESvHeapMarkCheck,ESvHeapMarkEnd,
	ESvHeapSetAllocFail,
	ESvServerCreate,ESvSessionCreate,
	ESvMutexCreate,ESvMutexOpen,
	ESvSemaphoreCreate,ESvSemaphoreOpen,
	ESvTimerCreate,
	ESvProcessCreate,ESvProcessLoaded,ESvProcessOpen,ESvProcessOpenById,ESvProcessRename,
	ESvProcessKill,ESvProcessTerminate,ESvProcessPanic,
	ESvProcessOwner,ESvProcessLogon,ESvProcessLogonCancel,
	ESvThreadCreate,ESvThreadSetParameter,ESvThreadOpen,ESvThreadOpenById,
	ESvThreadProcess,ESvThreadRename,
	ESvThreadKill,ESvThreadTerminate,ESvThreadPanic,
	ESvThreadLogon,ESvThreadLogonCancel,
	ESvThreadGetHeap,
	ESvMessageComplete,
	ESvDllSetTls,ESvDllFreeTls,
	ESvNotifierCreate,
	ESvDllGlobalAlloc,
	ESvDriveConnect,ESvDriveDisconnect,ESvBusDevAsyncStart,ESvDriveOpen,
	ESvDriveEnlarge,ESvDriveReduce,ESvUserMediaFunction,
	ESvDebugOpen,ESvDebugClose,ESvDebugKillThread,
	ESvPasswordSetEnabled,ESvPasswordSet,
	ESvUndertakerCreate,ESvUndertakerLogon,ESvUndertakerLogonCancel,
	ESvMmu,ESvMmuInfo,
    ESvSetMachineConfiguration,
    ESvChangeLocale,
	ESvDllAddDependency,
	ESvChunkCreateDoubleEndedLocal, ESvChunkCreateDoubleEndedGlobal,
	ESvChunkAdjustDoubleEnded,
	ESvResetMachine,
	ESvDllInitialiseData,
	ESvDllFreeData,
	ESvAllocateMessages,ESvSessionAttach,ESvSessionShare,
	ESvDriveUnlock, ESvDriveLock, ESvDriveClear, ESvDriveWritePasswordData,
	ESvTransferBufferCreate, ESvTransferBufferOpen, ESvTransferWindowCreate,
	ESvTransferWindowOpen
	};
//
// Executive dispatch numbers
//

enum TExecDispatch
	{
	EExecChunkNext=0x00,
	EExecChunkBase=0x01,
	EExecChunkSize=0x02,
	EExecChunkMaxSize=0x03,
	EExecChunkRead=0x04,
	EExecChunkWrite=0x05,
	EExecLogicalDeviceNext=0x06,
	EExecLogicalDeviceGetCaps=0x07,
	EExecLogicalDeviceQueryVersionSupported=0x08,
	EExecLogicalDeviceIsAvailable=0x09,
	EExecPhysicalDeviceNext=0x0a,
	EExecChannelNext=0x0b,
	EExecChannelRequest=0x0c,
	EExecChannelCancel=0x0d,
	EExecChannelControl=0x0e,
	EExecLibraryNext=0x0f,
	EExecLibraryLookup=0x10,
	EExecLibraryEntryPoint=0x11,
	EExecLibraryDllRefTable=0x12,
	EExecStaticCallList=0x13,
	EExecDynamicCallList=0x14,
	EExecLibraryCallList=0x15,
	EExecLibraryFileName=0x16,
	EExecMutexNext=0x17,
	EExecMutexCount=0x18,
	EExecMutexWait=0x19,
	EExecMutexSignal=0x1a,
	EExecProcessId=0x1b,
	EExecProcessNext=0x1c,
	EExecProcessResume=0x1d,
	EExecProcessFileName=0x1e,
	EExecProcessCommandLine=0x1f,
	EExecProcessExitType=0x20,
	EExecProcessExitReason=0x21,
	EExecProcessExitCategory=0x22,
	EExecProcessPriority=0x23,
	EExecProcessSetPriority=0x24,
	EExecProcessFlags=0x25,
	EExecProcessSetFlags=0x26,
	EExecProcessSetOwner=0x27,
	EExecSemaphoreNext=0x28,
	EExecSemaphoreCount=0x29,
	EExecSemaphoreWait=0x2a,
	EExecSemaphoreSignal1=0x2b,
	EExecSemaphoreSignalN=0x2c,
	EExecServerNext=0x2d,
	EExecServerReceive=0x2e,
	EExecServerCancel=0x2f,
	EExecSetSessionPtr=0x30,
	EExecSessionSendAsync=0x31,
	EExecThreadId=0x32,
	EExecThreadNext=0x33,
	EExecThreadResume=0x34,
	EExecThreadSuspend=0x35,
	EExecThreadPriority=0x36,
	EExecThreadSetPriority=0x37,
	EExecThreadProcessPriority=0x38,
	EExecThreadSetProcessPriority=0x39,
	EExecThreadFlags=0x3a,
	EExecThreadSetFlags=0x3b,
	EExecThreadRequestCount=0x3c,
	EExecThreadExitType=0x3d,
	EExecThreadExitReason=0x3e,
	EExecThreadExitCategory=0x3f,
	EExecThreadGetDesLength=0x40,
	EExecThreadGetDesMaxLength=0x41,
	EExecThreadRead8=0x42,
	EExecThreadRead16=0x43,
	EExecThreadWrite8=0x44,
	EExecThreadWrite16=0x45,
	EExecThreadRequestComplete=0x46,
	EExecTimerCancel=0x47,
	EExecTimerAfter=0x48,
	EExecTimerAt=0x49,
	EExecTimerLock=0x4a,
	EExecChangeNotifierLogon=0x4b,
	EExecChangeNotifierLogoff=0x4c,
	EExecWaitForAnyRequest=0x4d,
	EExecRequestSignal=0x4e,
	EExecFold=0x4f,
	EExecCollate=0x50,
	EExecLowerCase=0x51,
	EExecUpperCase=0x52,
	EExecType=0x53,
	EExecMatch8=0x54,
	EExecMatch16=0x55,
	EExecFind8=0x56,
	EExecFind16=0x57,
	EExecLocateF8=0x58,
	EExecLocateF16=0x59,
	EExecHandleName=0x5a,
	EExecHandleFullName=0x5b,
	EExecHandleInfo=0x5c,
	EExecHandleCount=0x5d,
	EExecAfter=0x5e,
	EExecAt=0x5f,
	EExecLanguage=0x60,
	EExecDayName=0x61,
	EExecDayNameAbb=0x62,
	EExecMonthName=0x63,
	EExecMonthNameAbb=0x64,
	EExecSuffix=0x65,
	EExecAmPmName=0x66,
	EExecCurrencySymbol=0x67,
	EExecLocale=0x68,
	EExecLocaleSet=0x69,
	EExecLocaleMessageText=0x6a,
	EExecMessageComplete=0x6b,
	EExecHeap=0x6c,
	EExecHeapSwitch=0x6d,
	EExecTimeNow=0x6e,
	EExecSetHomeTime=0x6f,
	EExecTickCount=0x70,
	EExecLockPeriod=0x71,
	EExecPushTrapFrame=0x72,
	EExecPopTrapFrame=0x73,
	EExecActiveScheduler=0x74,
	EExecSetActiveScheduler=0x75,
	EExecSvSendReceive=0x76,
	EExecCaptureEventHook=0x77,
	EExecReleaseEventHook=0x78,
	EExecRequestEvent=0x79,
	EExecRequestEventCancel=0x7a,
	EExecAddEvent=0x7b,
	EExecScreenInfo=0x7c,
	EExecDllGlobalAllocated=0x7d,
	EExecDllGlobalRead=0x7e,
	EExecDllGlobalWrite=0x7f,
	EExecDllTls=0x80,
	EExecTrapHandler=0x81,
	EExecSetTrapHandler=0x82,
	EExecHalGet=0x83,
	EExecHalSet=0x84,
	EExecKernelStartup=0x85,
	EExecBlockThreads=0x86,
	EExecWsRegisterThread=0x87,
	EExecFsRegisterThread=0x88,
	EExecBeep=0x89,
	EExecDebugger=0x8a,
	EExecJustInTime=0x8b,
	EExecSetJustInTime=0x8c,
	EExecLockedInc=0x8d,
	EExecLockedDec=0x8e,
	EExecDriveReadRequest=0x8f,
	EExecDriveWriteRequest=0x90,
	EExecDriveCaps=0x91,
	EExecDriveFormatRequest=0x92,
	EExecSetDebugMask=0x93,
	EExecUnused1=0x94,
	EExecUnused2=0x95,
	EExecUnused3=0x96,
	EExecDebugFunction=0x97,
	EExecBreakPoint=0x98,
	EExecProfileStart=0x99,
	EExecProfileEnd=0x9a,
	EExecPasswordIsEnabled=0x9b,
	EExecPasswordIsValid=0x9c,
	EExecFastCounter=0x9d,
	EExecExceptionHandler=0x9e,
	EExecSetExceptionHandler=0x9f,
	EExecModifyExceptionMask=0xa0,
	EExecRaiseException=0xa1,
	EExecIsExceptionHandled=0xa2,
	EExecThreadGetRamSizes=0xa3,
	EExecProcessGetRamSizes=0xa4,
	EExecLibraryGetRamSizes=0xa5,
	EExecMachineConfiguration=0xa6,
	EExecTestBootSequence=0xa7,
	EExecChunkSetHeapInfo=0xa8,
	EExecLibraryType=0xa9,
	EExecProcessType=0xaa,
	EExecGetLocaleCharSet=0xab,
	EExecWsSwitchOnScreen=0xac,
	EExecWsRegisterSwitchOnScreenHandling=0xad,
	EExecSetCurrencySymbol=0xae,
	EExecProcessSetType=0xaf,
	EExecChunkBottom=0xb0,
	EExecChunkTop=0xb1,
	EExecUnlockRamDrive=0xb2,
	EExecLockRamDrive=0xb3,
	EExecChunkReserveAt=0xb4,
	EExecThreadContext=0xb5,
	EExecDllDataInfo=0xb6,
	EExecBusDevCheckOpenMode=0xb7,
	EExecRomRootDirAddress=0xb8,
	EExecHandleAttributes=0xb9,
	EExecBusChannelCheckStatus=0xba,
	EExecDllFileName=0xbb,
	EExecRomHeaderAddress=0xbc,
	EExecDebugMask=0xbd,
	EExecMathRandom=0xbe,
	EExecSessionSendSync=0xbf,
	EExecProcessCommandLineLength=0xc0,
	EExecTimerInactivity=0xc1,
	EExecUserInactivityTime=0xc2,
	EExecDriveReadPasswordData=0xc3,
	EExecDrivePasswordStoreLengthInBytes=0xc4,
	EExecShortDateFormatSpec=0xc5,
	EExecLongDateFormatSpec=0xc6,
	EExecTimeFormatSpec=0xc7,
	EExecFatUtilityFunctions=0xc8,
	EExecResetInactivityTime=0xc9,
	EExecThreadGetCpuTime=0xca,
	EExecSetMemoryThresholds=0xcb,
	EExecIMBRange=0xcc,
	EExecTransferBufferSize=0xcd,
	EExecTransferWindowWaitForBuffer=0xce,
	EExecTransferWindowCancelWaitForBuffer=0xcf,
	EExecTransferWindowWaitForBufferFree=0xd0,
	EExecTransferWindowCancelWaitForBufferFree=0xd1,
	EExecTransferWindowBufferAddress=0xd2,
	EExecTransferWindowBufferSize=0xd3,
	EExecProcessGetMemoryInfo=0xd4,
	EExecDriveForceRemountRequest=0xd5,
	EExecDriveSetMountInfo=0xd6,
	EExecTransferWindowMapInBuffer=0xd7,
	EExecTransferWindowMapOutBuffer=0xd8,
	// Rotate the ExecNotSupported so that we keep 32 slots - saves having to renumber them
	EExecNotSupported18=0xd9,
	EExecNotSupported17=0xda,
	EExecNotSupported16=0xdb,
	EExecNotSupported15=0xdc,
	EExecNotSupported14=0xdd,
	EExecNotSupported13=0xde,
	EExecNotSupported12=0xdf,
	EExecNotSupported11=0xe0,
	EExecNotSupported10=0xe1,
	EExecNotSupported9=0xe2,
	EExecNotSupported8=0xe3,
	EExecNotSupported7=0xe4,
	EExecNotSupported6=0xe5,
	EExecNotSupported5=0xe6,
	EExecNotSupported4=0xe7,
	EExecNotSupported3=0xe8,
	EExecNotSupported2=0xe9,
	EExecNotSupported1=0xea,
	EExecNotSupported32=0xeb,
	EExecNotSupported31=0xec,
	EExecNotSupported30=0xed,
	EExecNotSupported29=0xee,
	EExecNotSupported28=0xef,
	EExecNotSupported27=0xf0,
	EExecNotSupported26=0xf1,
	EExecNotSupported25=0xf2,
	EExecNotSupported24=0xf3,
	EExecNotSupported23=0xf4,
	EExecNotSupported22=0xf5,
	EExecNotSupported21=0xf6,
	EExecNotSupported20=0xf7,
	EExecNotSupported19=0xf8,
	EExecMaxDispatch=0xf9
	};

// UserHal stuff
const TUint KLedMaskRed1=0x00000001;
const TUint KLedMaskGreen1=0x00000002;
const TUint KLedMaskYellow1=0x00000004;

const TUint KSupplyFlagSoundWarning=0x00000001;
const TUint KSupplyFlagBacklightWarning=0x00000002;
const TUint KSupplyFlagTimeChanged=0x80000000;
//
class TClearSetMask
	{
public:
	TUint iClearMask;
	TUint iSetMask;
	};
//
enum TSupplyStatus
    {
    EZero,EVeryLow,ELow,EGood
    };

class TSupplyInfoV1
    {
public:
    TTime iMainBatteryInsertionTime;
    TSupplyStatus iMainBatteryStatus;
    TTimeIntervalMicroSeconds iMainBatteryInUseMicroSeconds;
    TInt iCurrentConsumptionMilliAmps;
    TInt iMainBatteryConsumedMilliAmpSeconds;
    TInt iMainBatteryMilliVolts;
    TInt iMainBatteryMaxMilliVolts;
    TSupplyStatus iBackupBatteryStatus;
    TInt iBackupBatteryMilliVolts;
    TInt iBackupBatteryMaxMilliVolts;
    TBool iExternalPowerPresent;
    TTimeIntervalMicroSeconds iExternalPowerInUseMicroSeconds;
    TUint iFlags;
	};
typedef TPckgBuf<TSupplyInfoV1> TSupplyInfoV1Buf;

class TMouseProperties
	{
public:
	TUint8 iSpeed;
	TUint8 iAcceleration;
	};

enum THalFunction
    {
	// Still available in UserHal
	EMachineInfo,
	EMemoryInfo,
	EDriveInfo,
	ERomInfo,
	EStartupReason,
	EFaultReason,
	EExceptionId,
	EExceptionInfo,
	EPageSizeInBytes,
	ESwitchOff,
	ETickPeriod,
	ESetXYInputCalibration,
	ECalibrationPoints,
    ESaveXYInputCalibration,
    ERestoreXYInputCalibration,

	// Used by HAL
	ESupplyInfo,

	// Used by HAL for emulator
	EDisplayState,
	EModifyLedMask,
    ESetPointerSwitchesOn,
    EPointerSwitchesOn,
    ESetCaseOpenSwitchesOn,
    ECaseOpenSwitchesOn,
    ESetCaseCloseSwitchesOff,
    ECaseCloseSwitchesOff,
	EDisplayMemoryAddress,

	// Used by HAL
	EDebugPort,
	ESetDebugPort,
    };
//
enum TUserMediaFunction {EUserMediaRemount,EUserMediaNotifyChange};
//
struct TFatUtilityFunctions;
class Exec
	{
public:
	static TInt ChunkNext(TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static TUint8 *ChunkBase(TInt aHandle);
	static TInt ChunkSize(TInt aHandle);
	static TInt ChunkMaxSize(TInt aHandle);
	static void ChunkSetHeapInfo(TInt aHandle, TInt anOffset, TInt aRunAddress);
	static TInt ChunkBottom(TInt aHandle);
	static TInt ChunkTop(TInt aHandle);
//
	static TInt LogicalDeviceNext(TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static void LogicalDeviceGetCaps(TDes8 &aDes,TInt aHandle);
	static TBool LogicalDeviceQueryVersionSupported(const TVersion &aVer,TInt aHandle);
	static TBool LogicalDeviceIsAvailable(TInt aUnit,const TDesC *aPhysicalDevice,const TDesC *anInfo,TInt aHandle);
//
	static TInt PhysicalDeviceNext(TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
//
	static TInt ChannelNext(TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static void ChannelRequest(TInt aReqNo,TRequestStatus &aStatus,TAny **aArg,TInt aHandle);
	static void ChannelCancel(TUint aRequestMask,TInt aHandle);
	static TInt ChannelControl(TInt aFunction,TAny *a1,TAny *a2,TInt aHandle);
	static TUint BusDevCheckOpenMode(TBusDevOpenModeData *anOpenData);
	static TInt BusChannelCheckStatus(TInt aSocket);
//
	static void LibraryType(TUidType &aUids, TInt aHandle);
	static TInt LibraryNext(TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static TLibraryFunction LibraryLookup(TInt anOrdinal,TInt aHandle);
	static TLibraryEntry LibraryEntryPoint(TInt aHandle);
	static TUint* LibraryDllRefTable(TInt aHandle);
	static TInt StaticCallList(TInt aHandle, TInt& aCount, TUint*& aList);
	static TInt DynamicCallList(TInt aHandle, TInt& aCount, TUint*& aList);
	static TInt LibraryCallList(TInt aHandle, TInt& aCount, TUint*& aList);
	static void LibraryFileName(TDes &aFileName, TInt aHandle);
//
	static TInt MutexNext(TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static TInt MutexCount(TInt aHandle);
	static void MutexWait(TInt aHandle);
	static void MutexSignal(TInt aHandle);
//
	static void ProcessType(TUidType &aUids, TInt aHandle);
	static void ProcessSetType(const TUidType &aType, TInt aHandle);
	static TInt ProcessId(TInt aHandle);
	static TInt ProcessNext(TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static void ProcessResume(TInt aHandle);
	static void ProcessFileName(TDes &aName,TInt aHandle);
	static void ProcessCommandLine(TDes &aName,TInt aHandle);
	static TInt ProcessCommandLineLength(TInt aHandle);
	static TExitType ProcessExitType(TInt aHandle);
	static TInt ProcessExitReason(TInt aHandle);
	static void ProcessExitCategory(TDes &aName,TInt aHandle);
	static TProcessPriority ProcessPriority(TInt aHandle);
	static void ProcessSetPriority(TProcessPriority aPriority,TInt aHandle);
	static TUint ProcessFlags(TInt aHandle);
	static void ProcessSetFlags(TUint aClearFlags,TUint aSetFlags,TInt aHandle);
	static void ProcessSetOwner(TInt anOwningHandle,TInt aHandle);
//
	static TInt SemaphoreNext(TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static TInt SemaphoreCount(TInt aHandle);
	static void SemaphoreWait(TInt aHandle);
	static void SemaphoreSignal1(TInt aHandle);
	static void SemaphoreSignalN(TInt aCount,TInt aHandle);
//
	static TInt ServerNext(TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static void ServerReceive(TInt aHandle,TRequestStatus &aStatus,RMessage &aMessage);
	static void ServerCancel(TInt aHandle);
	static void SetSessionPtr(TInt aMsgHandle,const TAny *aUserSession,TBool aSharable);
//
	static TInt SessionSendAsync(TInt aHandle,TInt aFunction,TAny *aPtr,TRequestStatus *aStatus);
//
    static TInt ThreadId(TInt aHandle);
	static TInt ThreadNext(TFullName &aName,TInt &aFindHandle,const TDesC &aMatch);
	static void ThreadResume(TInt aHandle);
	static void ThreadSuspend(TInt aHandle);
	static TThreadPriority ThreadPriority(TInt aHandle);
	static void ThreadSetPriority(TThreadPriority aPriority,TInt aHandle);
	static TProcessPriority ThreadProcessPriority(TInt aHandle);
	static void ThreadSetProcessPriority(TProcessPriority aPriority,TInt aHandle);
	static TUint ThreadFlags(TInt aHandle);
	static void ThreadSetFlags(TUint aClearMask,TUint aSetMask,TInt aHandle);
	static TInt ThreadRequestCount(TInt aHandle);
	static TExitType ThreadExitType(TInt aHandle);
	static TInt ThreadExitReason(TInt aHandle);
	static void ThreadExitCategory(TDes &aName,TInt aHandle);
	static TInt ThreadGetDesLength(const TAny *aPtr,TInt aHandle);
	static TInt ThreadGetDesMaxLength(const TAny *aPtr,TInt aHandle);
	static TInt ThreadRead8(const TAny *aPtr,TDes8 *aDes,TInt anOffset,TInt aHandle);
	static TInt ThreadRead16(const TAny *aPtr,TDes16 *aDes,TInt anOffset,TInt aHandle);
	static TInt ThreadWrite8(const TAny *aPtr,const TDesC8 *aDes,TInt anOffset,TInt aHandle);
	static TInt ThreadWrite16(const TAny *aPtr,const TDesC16 *aDes,TInt anOffset,TInt aHandle);
	static void ThreadRequestComplete(TRequestStatus * &aStatus,TInt aReason,TInt aHandle);
//
	static void TimerCancel(TInt aHandle);
	static void TimerAfter(TRequestStatus &aStatus,TTimeIntervalMicroSeconds32 anInterval,TInt aHandle);
	static void TimerAt(TRequestStatus &aStatus,const TTime &aTime,TInt aHandle);
	static void TimerLock(TRequestStatus &aStatus,TTimerLockSpec aLock, TInt aHandle);
	static void TimerInactivity(TRequestStatus& aStatus, TInt aSeconds, TInt aHandle);
	static TInt UserInactivityTime();
	static void ResetInactivityTime();
//
	static TInt ChangeNotifierLogon(TRequestStatus& aStatus,TInt aHandle);
	static TInt ChangeNotifierLogoff(TInt aHandle);
//
	static void WaitForAnyRequest();
	static void RequestSignal(TInt aCount);
//
	static TUint Fold(TUint aChar);
	/** @deprecated in 6.2 */
	static TUint Collate(TUint aChar);
	static TUint LowerCase(TUint aChar);
	static TUint UpperCase(TUint aChar);
	static TUint Type(TUint aChar);
	static TInt Match8(const TDesC8 &aLeftD,const TDesC8 &aRightD,TMatchType aType);
	static TInt Match16(const TDesC16 &aLeftD,const TDesC16 &aRightD,TMatchType aType);
	static TInt Find8(const TDesC8 &aDes,const TUint8* pS,TInt aLen,TMatchType aType);
	static TInt Find16(const TDesC16 &aDes,const TUint16* pS,TInt aLen,TMatchType aType);
	static TInt LocateF8(const TDesC8 &aDes,TUint aChar);
	static TInt LocateF16(const TDesC16 &aDes,TUint aChar);
//
	static void HandleName(TDes &aName,TInt aHandle);
	static void HandleFullName(TDes &aFullName,TInt aHandle);
	static void HandleInfo(THandleInfo* anInfo,TInt aHandle);
	static void HandleCount(TInt aHandle, TInt& aProcessHandleCount, TInt& aThreadHandleCount);
	static TUint HandleAttributes(TInt aHandle);
//
	static void After(TTimeIntervalMicroSeconds32 anInterval,TRequestStatus &aStatus);
	static void At(const TTime &aTime,TRequestStatus &aStatus);
//
	static TInt MessageComplete(TInt aHandle,TInt aReason);
//
	static TLanguage Language();
	static void DayName(TDay aDay,TDes &aName);
	static void DayNameAbb(TDay aDay,TDes &aName);
	static void MonthName(TMonth aMonth,TDes &aName);
	static void MonthNameAbb(TMonth aMonth,TDes &aName);
	static void Suffix(TInt aSuffix,TDes &aName);
	static void AmPmName(TAmPm aSelector,TDes &aName);
	static void CurrencySymbol(TDes &aName);
	static void SetCurrencySymbol(const TDesC&aName);
	static void ShortDateFormatSpec(TDes& aName);
	static void LongDateFormatSpec(TDes& aName);
	static void TimeFormatSpec(TDes& aName);
	static const TFatUtilityFunctions* FatUtilityFunctions();
	static void LocaleRefresh(TLocale &aLocale);
	static void LocaleSet(const TLocale &aLocale);
	static void LocaleMessageText(TLocaleMessage aMsgNo,TDes& aMsg);
//
	static RHeap *Heap();
	static RHeap *HeapSwitch(RHeap *aHeap);
//
	static void TimeNow(TTime& aUniversalTimeTime,TTimeIntervalSeconds& aUniversalTimeOffsetOffset);
	static TInt SetHomeTime(const TTime& aHomeTime);
	static TUint TickCount();
	static TTimerLockSpec LockPeriod();
//
	static void PushTrapFrame(TTrap *aFrame);
	static TTrap *PopTrapFrame();
	static CActiveScheduler *ActiveScheduler();
	static void SetActiveScheduler(CActiveScheduler *aScheduler);
//
	static void SvSendReceive(TInt aFunction,TAny *aPtr,TRequestStatus &aStatus);
//
	static void CaptureEventHook();
	static void ReleaseEventHook();
	static void RequestEvent(TRawEventBuf &anEvent,TRequestStatus &aStatus);
	static void RequestEventCancel();
	static TInt AddEvent(const TRawEvent& anEvent);
	static void ScreenInfo(TDes8 &anInfo);
//
	static TBool DllGlobalAllocated(TInt aHandle);
	static TInt DllGlobalRead(TInt aHandle,TInt aPos,TInt aLength,TDes8 &aDes);
	static TInt DllGlobalWrite(TInt aHandle,TInt aPos,const TDesC8 &aDes);
	static TAny *DllTls(TInt aHandle);
	static void DllDataInfo(TInt aHandle, TModuleInfo &aInfo);
	static void DllFileName(TInt aHandle, TDes &aFileName);
//
	static TTrapHandler *TrapHandler();
	static TTrapHandler *SetTrapHandler(TTrapHandler *aHandler);
//
	static TInt HalGet(THalFunction aFunction,TAny* aData);
	static TInt HalSet(THalFunction aFunction,TAny* aData);
//
	static void KernelStartup(TThreadFunction aFunction);
	static void BlockThreads(TBlockType aType);
	static void WsRegisterThread(TThreadFunction aFunction);
	static void FsRegisterThread(TThreadFunction aFunction);
//
	static TInt Beep(TInt aFrequency,TTimeIntervalMicroSeconds32 aDuration);
//
	static TBool JustInTime();
	static void SetJustInTime(const TBool aBoolean);
//
	static TInt LockedInc(TInt &aValue);
	static TInt LockedDec(TInt &aValue);
//
	static TInt DriveCaps(TDes8& anInfo,TAny *aDrive);
	static void DriveRead(TLocalDriveData &aDriveData,TLocalDriveMessageData &aTrg,TRequestStatus &aStatus,TAny *aDrive);
	static void DriveWrite(TLocalDriveData &aDriveData,TLocalDriveMessageData &aSrc,TRequestStatus &aStatus,TAny *aDrive);
	static void DriveFormat(TInt64 &aPos,TInt *aLength,TRequestStatus &aStatus,TAny *aDrive);
	static TInt DriveForceRemount(TUint aFlags,TAny *aDrive);
	static TInt DriveSetMountInfo(TLocalDriveMessageData &aMountInfo,TAny *aDrive);
//
	static void SetDebugMask(TUint32 aVal);
//
	static TInt DebugFunction(TDebugFunction* aFunction,TAny* aPar1,TAny* aPar2,TAny* aPar3);
	static TInt BreakPoint();
	static TInt ProfileStart(TInt aProfile);
	static TInt ProfileEnd(TInt aProfile);
//
	static TBool PasswordIsEnabled();
	static TBool PasswordIsValid(const TPassword& aPassword);
//
	static TUint32 FastCounter();
	static TUint32 MathRandom();
//
	static TExceptionHandler* ExceptionHandler(TInt aHandle);
	static TInt SetExceptionHandler(TExceptionHandler* aHandler, TUint32 aMask, TInt aHandle);
	static void ModifyExceptionMask(TUint32 aClearMask, TUint32 aSetMask, TInt aHandle);
	static TInt RaiseException(TExcType aType,TInt aHandle);
	static TBool IsExceptionHandled(TExcType aType,TInt aHandle);
	static void ThreadContext(TDes8 &aDes, TInt aHandle);
//
	static TInt ThreadGetRamSizes(TInt& aHeapSize, TInt& aStackSize, TInt aHandle);
	static TInt ProcessGetRamSizes(TInt& aCodeSize, TInt& aConstDataSize, TInt& anInitialisedDataSize, TInt& anUninitialisedDataSize, TInt aHandle);
	static TInt LibraryGetRamSizes(TInt& aCodeSize, TInt& aConstDataSize, TInt aHandle);
//
    static TInt MachineConfiguration(TDes8& aConfig,TInt& aSize);
//
    static TInt TestBootSequence();
//
	static const LCharSet *GetLocaleCharSet();
//
    static void WsSwitchOnScreen();
    static void WsRegisterSwitchOnScreenHandling(TBool aState);
//
	static TInt SessionSendSync(TInt aHandle,TInt aFunction,TAny *aPtr,TRequestStatus *aStatus);
//
	static TInt DriveReadPasswordData(TDes8& aBuf);
	static TInt DrivePasswordStoreLengthInBytes();
//
	static TInt ThreadGetCpuTime(TInt aHandle, TTimeIntervalMicroSeconds& aCpuTime);
//
	static TInt SetMemoryThresholds(TInt aLowThreshold, TInt aGoodThreshold);
//
	static void IMB_Range(TAny* aBase, TUint aSize);
//
	static TInt TransferBufferSize(TInt aHandle);
	static void TransferWindowWaitForBuffer(TInt aHandle, TRequestStatus& aStatus);
	static void TransferWindowCancelWaitForBuffer(TInt aHandle);
	static void TransferWindowWaitForBufferFree(TInt aHandle, TRequestStatus& aStatus);
	static void TransferWindowCancelWaitForBufferFree(TInt aHandle);
	static TUint8* TransferWindowBufferAddress(TInt aHandle);
	static TInt TransferWindowBufferSize(TInt aHandle);
	static TInt TransferWindowMapInBuffer(TInt aWinHandle,TInt aBufHandle);
	static TInt TransferWindowMapOutBuffer(TInt aHandle);
//
	static TInt ProcessGetMemoryInfo(TProcessMemoryInfo& aInfo, TInt aHandle);


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
class TChannelDoCreate
	{
public:
	TVersion iVer;
	const TDesC *iName;
	const TDesC *iPhysicalDevice;
	const TDesC8 *iInfo;
	};
//
class TCreateSession
	{
public:
	TVersion iVer;
	TInt iMessageSlots;
	};
//
class TThreadCreate
	{
public:
	TThreadFunction iFunction;
	TInt iStackSize;
	RHeap *iHeap;
	TInt iHeapMinSize;
	TInt iHeapMaxSize;
	TAny *iPtr;
	TInt iLibraryHandle;
	};
//
// Handler below is used by test prints to trucate rather than panic the caller.
//
#if defined(_UNICODE)
class TestOverflowTruncate : public TDes16Overflow
	{
public:
	virtual void Overflow(TDes16 &aDes);
	};
#else
class TestOverflowTruncate : public TDes8Overflow
	{
public:
	virtual void Overflow(TDes8 &aDes);
	};
#endif
//
GLREF_C TInt SvSendReceive(TInt aFunction,TAny *aPtr);
GLREF_C void SvSendReceiveCheck(TInt aFunction,TAny *aPtr);


#endif


