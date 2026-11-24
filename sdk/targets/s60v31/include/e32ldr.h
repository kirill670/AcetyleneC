// e32\include\e32ldr.h
//
// Copyright (c) 1995-2001 Symbian Ltd. All rights reserved.
//

/**
@file
@internalTechnology
*/

#ifndef __E32LDR_H__
#define __E32LDR_H__
#include <e32cmn.h>

const TInt KMaxLibraryEntryPoints=0x100;

//
// Loader version number.
//
const TInt KLoaderMajorVersionNumber=1;
const TInt KLoaderMinorVersionNumber=0;

//
// IPC messages to the loader
//
enum TLoaderMsg
	{
	ELoadProcess=1,
	ELoadLibrary=2,
	ELoadLogicalDevice=3,
	ELoadPhysicalDevice=4,
	ELoadLocale=5,
	ELoadFileSystem=6,
	EGetInfo=7,
	ELoaderDebugFunction=8,
	ELoadFSExtension=9,
	EGetInfoFromHeader=10,
	ELoadFSPlugin=11,
	ELoaderCancelLazyDllUnload=12,
	ELdrDelete=13,
	EMaxLoaderMsg
	};
//
// Loader message arguments:
//		0 = TLdrInfo
//		1 = Filename
//		2 = Command line (process) or path (library)
//
class TLdrInfo
	{
public:
	IMPORT_C TLdrInfo();		// for BC
public:
	TUidType iRequestedUids;
	TOwnerType iOwnerType;
	TInt iHandle;
	TUint32 iSecureId;
	TUint32 iRequestedVersion;
	};

#ifndef __KERNEL_MODE__
#include <e32std.h>
//
// Loader client class
//
class RLoader : public RSessionBase
	{
public:
	IMPORT_C TInt Connect();
	TVersion Version() const;
	TInt LoadProcess(TInt& aHandle, const TDesC& aFileName, const TDesC& aCommand, const TUidType& aUidType, TOwnerType aType);
	IMPORT_C TInt LoadLibrary(TInt& aHandle, const TDesC& aFileName, const TDesC& aPath, const TUidType& aType, TUint32 aModuleVersion);
	IMPORT_C TInt GetInfo(const TDesC& aFileName, TDes8& aInfoBuf);
	TInt LoadDeviceDriver(const TDesC& aFileName, TInt aDeviceType);
	IMPORT_C TInt DebugFunction(TInt aFunction, TInt a1, TInt a2, TInt a3);
	TInt LoadLocale(const TDesC& aLocaleDllName, TLibraryFunction* aExportList);
	TInt GetInfoFromHeader(const TDesC8& aHeader, TDes8& aInfoBuf);
	IMPORT_C TInt CancelLazyDllUnload();
	IMPORT_C TInt Delete(const TDesC& aFileName);
public:
#ifdef __ARMCC__
	// workaround for possible EDG bug (!!)
	inline TInt SendReceive(TInt aFunction,const TIpcArgs& aArgs) const
	  { return RSessionBase::SendReceive(aFunction, aArgs); }
#else
	using RSessionBase::SendReceive;
#endif
	};
#endif

//
// Information required to create a new code segment
//
enum TCodeSegAttributes
	{
	ECodeSegAttKernel	=0x00000001,
	ECodeSegAttGlobal	=0x00000002,
	ECodeSegAttFixed	=0x00000004,
	ECodeSegAttABIMask	=0x00000018,	  // same values as in image header
	ECodeSegAttHDll		=(TInt)0x80000000,// Emulator host file type: 1=DLL, 0=EXE
	ECodeSegAttExpVer	=0x40000000,	  // Filename is explicitly versioned
	};

class TCodeSegCreateInfo
	{
public:
	TBuf8<KMaxFileName> iFileName;		// not including {MMMMmmmm} version info
	TUidType iUids;				// uid1 indicates EXE or DLL
	TUint32 iAttr;
	TInt iCodeSize;
	TInt iTextSize;
	TInt iDataSize;
	TInt iBssSize;
	TInt iTotalDataSize;
	TUint32 iEntryPtVeneer;		// address of first instruction to be called
	TUint32 iFileEntryPoint;	// address of entry point within this code segment
	TInt iDepCount;
	TUint32 iExportDir;
	TInt iExportDirCount;
	TUint32 iCodeLoadAddress;	// 0 for RAM loaded code, else pointer to TRomImageHeader
	TUint32 iCodeRunAddress;
	TUint32 iDataLoadAddress;
	TUint32 iDataRunAddress;
	TUint32 iExceptionDescriptor;
	TInt iRootNameOffset;
	TInt iRootNameLength;
	TInt iExtOffset;
	TUint32 iModuleVersion;
	SSecurityInfo iS;
	TAny* iHandle;				// pointer to kernel-side DCodeSeg object
	TInt iClientProcessHandle;	// handle to client process for user DLL loads
public:
	IMPORT_C TPtrC8 RootName() const;
	IMPORT_C void FullFileName(TDes8& aName) const;
	};

//
// Information required to create a new process
//
class TProcessCreateInfo : public TCodeSegCreateInfo
	{
public:
	TInt iHeapSizeMin;
	TInt iHeapSizeMax;
	TInt iStackSize;
	TInt iClientHandle;			// handle to loader's client
	TInt iProcessHandle;		// handle to new DProcess
	TInt iFinalHandle;			// handle from loader client to new process
	TOwnerType iOwnerType;
	TProcessPriority iPriority;
	TUint iSecurityZone;
	};

const TUint KSecurityZoneUnique = 0u;
const TUint KSecurityZoneLegacyCode = ~0u;

//
// Information required to attach a code segment to a process
// in the form of a library.
//
class TLibraryCreateInfo
	{
public:
	TAny* iCodeSegHandle;		// pointer to kernel-side DCodeSeg object
	TInt iClientHandle;			// handle to loader's client
	TInt iLibraryHandle;		// handle to new DLibrary
	TOwnerType iOwnerType;
	};

//
// Information required to find an existing code segment
//
class TFindCodeSeg
	{
public:
	TUidType iUids;				// required UIDs
	const TAny* iRomImgHdr;		// ROM image header if ROM code required, NULL otherwise
	TUint32 iAttrMask;			// mask for attributes
	TUint32 iAttrVal;			// required value for masked attributes
	TInt iProcess;				// handle to process in which code is required to operate
								// not used if kernel only specified
	SSecurityInfo iS;			// required capabilities/SID
	TUint32 iModuleVersion;		// required version
	TBuf8<KMaxLibraryName> iName;	// name to look for - zero length means any
	};

//
// Loader magic executive functions
//
class E32Loader
	{
public:
	// used by loader only
	IMPORT_C static TInt CodeSegCreate(TCodeSegCreateInfo& aInfo);
	IMPORT_C static TInt CodeSegLoaded(TCodeSegCreateInfo& aInfo);
	IMPORT_C static TInt LibraryCreate(TLibraryCreateInfo& aInfo);
	IMPORT_C static TInt CodeSegOpen(TAny* aHandle, TInt aClientProcessHandle);
	IMPORT_C static void CodeSegClose(TAny* aHandle);
	IMPORT_C static void CodeSegNext(TAny*& aHandle, const TFindCodeSeg& aFind);
	IMPORT_C static void CodeSegInfo(TAny* aHandle, TCodeSegCreateInfo& aInfo);
	IMPORT_C static TInt CodeSegAddDependency(TAny* aImporter, TAny* aExporter);
	IMPORT_C static void CodeSegDeferDeletes();
	IMPORT_C static void CodeSegEndDeferDeletes();
	IMPORT_C static TInt ProcessCreate(TProcessCreateInfo& aInfo, const TDesC8* aCommandLine);
	IMPORT_C static TInt ProcessLoaded(TProcessCreateInfo& aInfo);
	IMPORT_C static TInt CheckClientState(TInt aClientHandle);
	IMPORT_C static TInt DeviceLoad(TAny* aHandle, TInt aType);
	IMPORT_C static TAny* ThreadProcessCodeSeg(TInt aHandle);
	IMPORT_C static void ReadExportDir(TAny* aHandle, TUint32* aDest);
	IMPORT_C static TInt LocaleExports(TAny* aHandle, TLibraryFunction* aExportsList);

	IMPORT_C static void GetV7StubAddresses(TLinAddr& aExe, TLinAddr& aDll);
	static TInt V7ExeEntryStub();
	static TInt V7DllEntryStub(TInt aReason);
public:
	// used by client side
	static TInt WaitDllLock();
	static TInt ReleaseDllLock();
	static TInt LibraryAttach(TInt aHandle, TInt& aNumEps, TLinAddr* aEpList);
	static TInt LibraryAttached(TInt aHandle);
	static TInt StaticCallList(TInt& aNumEps, TLinAddr* aEpList);
	static TInt LibraryDetach(TInt& aNumEps, TLinAddr* aEpList);
	static TInt LibraryDetached();
	};

typedef TInt (*TSupervisorFunction)(TAny*);

#endif

