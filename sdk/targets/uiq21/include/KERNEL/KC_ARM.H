// KC_ARM.H
//
// Copyright (c) 1998-2002 Symbian Ltd.  All rights reserved.
//


#ifndef __KCSTD_H__
#define __KCSTD_H__
#include <m32std.h>

#if defined (__CPU_CACHE_FLUSH_BY_DATA_READ)
const TLinAddr KCleanCacheDataAddr=0x430fe000u;
const TLinAddr KCleanAltCacheDataAddr=0x43100000u;
#elif defined (__CPU_CACHE_FLUSH_BY_LINE_ALLOC)
const TLinAddr KCleanCacheDataAddr=0x43000000u;
const TLinAddr KCleanAltCacheDataAddr=0x43100000u;
#endif

class Asic
	{
public:
//	static void Panic(TAsicPanic aPanic)=0;
	static TLinAddr MapFlash(TLinAddr aLinAddr, TPhyAddr aPhysAddr, TUint aSize);
	static void DebugOutput(TUint aLetter);
	static TBool DebugInit();
	static TBool LowBattery();
	static void HandleLowBattery();
	static void OutputToJTAG(TUint aLetter);
public:
	// Set by the PSU code
	static TMachineStartupType StartupReason;
	static TInt BatteryChanged;
	// Set by the Variant code
	static TBool Com1Initialised;
    static TBool BacklightPresent;
	};

const TInt KPageSize=0x1000;
const TLinAddr KCpuPage=KSuperPageLinAddr+KPageSize;

typedef TUint32 TArmReg;


typedef void (*TArmHandler)();
const TInt KMaxIntVector=7;

class TCpuPageRamBlock
    {
public:
    TPhysAddr iBlockStart;
    TUint32 iBlockSize;
    };

class TCpuPage
// WARNING: Keep in sync with bootstrap
	{
public:
	TArmHandler iVectors[KMaxIntVector];
	TMachineStartupType iStartupReason;
	
	TStackInfo iReEntrantStack;
	TStackInfo iExceptionStack;
	TStackInfo iIrqStack;
	TStackInfo iFiqStack;

	TUint32 iFastRamPageCountForExcCode;

	TUint32 iStartOfRam ;
	TUint32 iEndOfRam  ;
	TUint32 iRomPte ;

	//alloc data starts here
	TUint32 iAllocStartBytes ;
	TUint32 iAllocEndBytes  ;
	TCpuPageRamBlock iRamBlocks[264/8];
	TCpuPageRamBlock iVideoRam;
	};



#ifndef __SINGLE__
// default domain access is 0=manager, 1=client, 2,3=no access, 4-15=client
// 2=client now
#ifdef __LOCK_PAGE_TABLES__
const TArmReg KDefaultDomainAccess=0x55555507u;
#else
const TArmReg KDefaultDomainAccess=0x55555517u;
#endif
const TArmReg KSupervisorInitialDomainAccess=0x55555557u;
#else
// single process mode has unlimited access to everything
const TArmReg KDefaultDomainAccess=0xffffffffu;
const TArmReg KSupervisorInitialDomainAccess=0xffffffffu;
#endif

enum TArmVectors
	{
	EArmVectorUndef,EArmVectorSwi,
	EArmVectorAbortPrefetch,EArmVectorAbortData,
	EArmVectorReserved,
	EArmVectorIrq,EArmVectorFiq
	};

enum TArmFlags
	{
	ECpuThumb=0x00000020,
	ECpuNoFiq=0x00000040, ECpuNoIrq=0x00000080,
	ECpuVf=0x10000000, ECpuCf=0x20000000,
	ECpuZf=0x40000000, ECpuNf=0x80000000
	};

enum TArmModes
	{
	EUserMode=0x10,EFiqMode=0x11,EIrqMode=0x12,
	ESvcMode=0x13,EAbortMode=0x17,EUndefMode=0x1b,
	EMaskMode=0x1f
	};

class TArmBreakPoint
	{
public:
	// Possible values for aCpuInfo parameter of
	// RDebug::SetBreakPoint()
	enum
		{
		K16Bit = 2, // insert 16 bit breakpoint
		K32Bit = 4, // insert 32 bit breakpoint
		};

	static inline void HardcodedBreakPoint();

	enum 
		{
		KOpcode16 = 0xDE56,
		KOpcode32 = 0xE7F123F4,
		};
	};

__NAKED__ inline void TArmBreakPoint::HardcodedBreakPoint()
//
// Insert a hardcoded breakpoint
// 
	{
#if defined(__MARM_THUMB__)
	asm(".hword %a0" : : "i" (KOpcode16));
#else
	asm(".word %a0" : : "i" (KOpcode32));
#endif
	}


class TArmRegSet
	{
public:
	TArmReg iR0;
	TArmReg iR1;
	TArmReg iR2;
	TArmReg iR3;
	TArmReg iR4;
	TArmReg iR5;
	TArmReg iR6;
	TArmReg iR7;
	TArmReg iR8;
	TArmReg iR9;
	TArmReg iR10;
	TArmReg iR11;
	TArmReg iR12;
	TArmReg iR13;
	TArmReg iR14;
	TArmReg	iR15;
	TArmReg iFlags;
	TArmReg iDacr;
	};

// Error codes used in abort handler
const TInt KArmAbortErrorBaseEqIndexPre=1;
const TInt KArmAbortErrorBaseEqIndexPost=2;
const TInt KArmAbortErrorBaseR15=4;
const TInt KArmAbortErrorIndexR15=5;
const TInt KArmAbortErrorLoadWB=6;
const TInt KArmAbortErrorLdmStmEmpty=7;
const TInt KArmAbortErrorUserBankWB=8;
const TInt KArmAbortErrorBadInst=9;

class DArmPlatThread : public DPlatThread
	{
public:
	DArmPlatThread();
	virtual void SetupContext(TThreadCreateType aType,TAny *aStackTop,TThreadFunction aFunction,TAny *aPtr);
	virtual TInt SetInitialParameter(TAny* aPtr);
	virtual TInt CallFunction(TAny *aFunction, TAny *aArg1);
	virtual TInt CallFunction(TAny *aFunction, TAny *aArg1, TAny *aArg2);
	virtual void Context(TDes8 &aDes);
public:
	TArmRegSet iReg;
#ifdef __CPU_XSCALE__
	TUint32 iCp0Acc0[2];
#endif
	};

class DArmPlatProcess : public DPlatProcess
	{
public:
	DArmPlatProcess();
	~DArmPlatProcess();
	virtual void AddFixedAccessChunk(DPlatChunk *aChunk);
	virtual void RemoveFixedAccessChunk(DPlatChunk *aChunk);
private:
	void AdjustDomainAccess(TArmReg aClearMask, TArmReg aSetMask);
public:
	TInt iDomain;
	TArmReg iDacr;
	};

class DArmPlatChunk : public DPlatChunk
	{
public:
	DArmPlatChunk();
	~DArmPlatChunk();
	virtual void SetupPermissions(TChunkType aChunkType);
	virtual void SetPdeInfo();
public:
	TInt iDomain;
	};

inline TCpuPage &TheCpuPage()
	{return(*((TCpuPage *)KCpuPage));}
inline DArmPlatThread &CurrentThread()
	{return(*((DArmPlatThread *)TheCurrentThread));}

enum TArmPanic 
	{
	EThrdCreateInPlaceSize,
	EFastRamExcCodeSize,
	};

// TExtInterrupt and Arm::ExtInterruptID should be moved
// into the ASSP that uses it
typedef TUint8 TExtInterruptID;

class Arm
	{
public:
	static void Panic(TArmPanic aPanic);
	static void Init1Stacks();
	static void Init1Interrupts();
	static void SetHandler(TInt aVector,TArmHandler aHandler);
	static void IrqDispatch();
	static void FiqDispatch();
public:
	// Supervisor stacks
	static TUint32* FiqStackTop;
	static TUint32* IrqStackTop;
	static TUint32* ReEntrantStackTop;
	static TUint32* ExceptionStackTop;

	// The interrupt vectors
	static TInterrupt *IntVectors[];
	static TExtInterruptID ExtInterruptID[]; // Jane, not in MAD?
	static TInt PicVectorID[];
	static CBitMapAllocator* DomainAllocator;
	static TPartnerOS PartnerOS;
	};

#ifdef __CPU_WRITE_BACK_CACHE
#define __CLEAN_DCACHE_ENTRY(cc,r)	asm("mcr"#cc " p15, 0, "#r ", c7, c10, 1 ")
#else
#define __CLEAN_DCACHE_ENTRY(cc,r)
#endif

#ifdef __CPU_WRITE_BUFFER
#define __DRAIN_WRITE_BUFFER		asm("mcr p15, 0, r0, c7, c10, 4 ")
#else
#define __DRAIN_WRITE_BUFFER
#endif

// This is only used for backpatching BX instructions on CPUs which don't support BX
#if defined(__MISA__)		// MISA has no single-entry ICache flush
#define __FLUSH_ICACHE_ENTRY(cc,r)	asm("mcr"#cc " p15, 0, "#r ", c7, c5, 0 ")
#else						// ARM920 etc
#define __FLUSH_ICACHE_ENTRY(cc,r)	asm("mcr"#cc " p15, 0, "#r ", c7, c5, 1 ")
#endif

#ifdef __CPU_XSCALE__
#define	CPWAIT(cc,r)				asm("mrc"#cc" p15, 0, "#r", c2, c0, 0; mov"#cc" "#r","#r"; sub"#cc" pc, pc, #4 ");
#define XSCALE_STEP_A(x)			asm(x)		// workarounds for A-stepping XScale cores
#else
#define	CPWAIT(cc,r)
#define XSCALE_STEP_A(x)
#endif

#ifdef _DEBUG
#define ASM_DEBUG4(fn,a0,a1,a2,a3)	asm("stmfd sp!, {r0-r4,ip,lr} ");	\
									asm("mov r0,"  # a0 );				\
									asm("mov r1,"  # a1 );				\
									asm("mov r2,"  # a2 );				\
									asm("mov r3,"  # a3 );				\
									asm("mrs r4, cpsr ");				\
									asm("bl " #fn "__Fiiii" );			\
									asm("msr cpsr, r4 ");				\
									asm("ldmfd sp!, {r0-r4,ip,lr} ");

#define ASM_DEBUG3(fn,a0,a1,a2)		asm("stmfd sp!, {r0-r4,ip,lr} ");	\
									asm("mov r0,"  # a0 );				\
									asm("mov r1,"  # a1 );				\
									asm("mov r2,"  # a2 );				\
									asm("mrs r4, cpsr ");				\
									asm("bl " #fn "__Fiii" );			\
									asm("msr cpsr, r4 ");				\
									asm("ldmfd sp!, {r0-r4,ip,lr} ");

#define ASM_DEBUG2(fn,a0,a1)		asm("stmfd sp!, {r0-r4,ip,lr} ");	\
									asm("mov r0,"  # a0 );				\
									asm("mov r1,"  # a1 );				\
									asm("mrs r4, cpsr ");				\
									asm("bl " #fn "__Fii" );			\
									asm("msr cpsr, r4 ");				\
									asm("ldmfd sp!, {r0-r4,ip,lr} ");

#define ASM_DEBUG1(fn,a0)			asm("stmfd sp!, {r0-r4,ip,lr} ");	\
									asm("mov r0,"  # a0 );				\
									asm("mrs r4, cpsr ");				\
									asm("bl " #fn "__Fi" );				\
									asm("msr cpsr, r4 ");				\
									asm("ldmfd sp!, {r0-r4,ip,lr} ");

#define ASM_DEBUG0(fn)				asm("stmfd sp!, {r0-r4,ip,lr} ");	\
									asm("mrs r4, cpsr ");				\
									asm("bl " #fn "__Fv" );				\
									asm("msr cpsr, r4 ");				\
									asm("ldmfd sp!, {r0-r4,ip,lr} ");

#define ASM_CDEBUG4(cc,fn,a0,a1,a2,a3)	asm("b" #cc " .+40 ");			\
									asm("stmfd sp!, {r0-r4,ip,lr} ");	\
									asm("mov r0,"  # a0 );				\
									asm("mov r1,"  # a1 );				\
									asm("mov r2,"  # a2 );				\
									asm("mov r3,"  # a3 );				\
									asm("mrs r4, cpsr ");				\
									asm("bl " #fn "__Fiiii" );			\
									asm("msr cpsr, r4 ");				\
									asm("ldmfd sp!, {r0-r4,ip,lr} ");

#define ASM_CDEBUG3(cc,fn,a0,a1,a2)	asm("b" #cc " .+36 ");				\
									asm("stmfd sp!, {r0-r4,ip,lr} ");	\
									asm("mov r0,"  # a0 );				\
									asm("mov r1,"  # a1 );				\
									asm("mov r2,"  # a2 );				\
									asm("mrs r4, cpsr ");				\
									asm("bl " #fn "__Fiii" );			\
									asm("msr cpsr, r4 ");				\
									asm("ldmfd sp!, {r0-r4,ip,lr} ");

#define ASM_CDEBUG2(cc,fn,a0,a1)	asm("b" #cc " .+32 ");				\
									asm("stmfd sp!, {r0-r4,ip,lr} ");	\
									asm("mov r0,"  # a0 );				\
									asm("mov r1,"  # a1 );				\
									asm("mrs r4, cpsr ");				\
									asm("bl " #fn "__Fii" );			\
									asm("msr cpsr, r4 ");				\
									asm("ldmfd sp!, {r0-r4,ip,lr} ");

#define ASM_CDEBUG1(cc,fn,a0)		asm("b" #cc " .+28 ");				\
									asm("stmfd sp!, {r0-r4,ip,lr} ");	\
									asm("mov r0,"  # a0 );				\
									asm("mrs r4, cpsr ");				\
									asm("bl " #fn "__Fi" );				\
									asm("msr cpsr, r4 ");				\
									asm("ldmfd sp!, {r0-r4,ip,lr} ");

#define ASM_CDEBUG0(cc,fn)			asm("b" #cc " .+24 ");				\
									asm("stmfd sp!, {r0-r4,ip,lr} ");	\
									asm("mrs r4, cpsr ");				\
									asm("bl " #fn "__Fv" );				\
									asm("msr cpsr, r4 ");				\
									asm("ldmfd sp!, {r0-r4,ip,lr} ");
#else
#define ASM_DEBUG4(fn,a0,a1,a2,a3)
#define ASM_DEBUG3(fn,a0,a1,a2)
#define ASM_DEBUG2(fn,a0,a1)
#define ASM_DEBUG1(fn,a0)
#define ASM_DEBUG0(fn)
#define ASM_CDEBUG4(cc,fn,a0,a1,a2,a3)
#define ASM_CDEBUG3(cc,fn,a0,a1,a2)
#define ASM_CDEBUG2(cc,fn,a0,a1)
#define ASM_CDEBUG1(cc,fn,a0)
#define ASM_CDEBUG0(cc,fn)
#endif

#endif
