// f32\inc\f32dbg.h
//
// Copyright (c) 1997-2004 Symbian Ltd. All rights reserved.
//
/**
@file
@internalTechnology

*/
#if !defined(__F32DBG_H__)
#define __F32DBG_H__
#include <e32std.h>


/**
@publishedPartner


A bit value indicating that tracing is to be active in
file system code, when set through a call to RFs::SetDebugRegister()
in _DEBUG or _DEBUG_RELEASE mode.
*/
#define KFSYS       0x0001


/**
@publishedPartner


A bit value indicating that tracing is to be active in
file server code, when set through a call to RFs::SetDebugRegister()
in _DEBUG or _DEBUG_RELEASE mode.
*/
#define KFSERV      0x0002


/**
@publishedPartner


A bit value indicating that tracing is to be active in
the loader code, when set through a call to RFs::SetDebugRegister()
in _DEBUG or _DEBUG_RELEASE mode.
*/
#define KFLDR       0x0004


/**
@publishedPartner


A bit value indicating that the number of (simulated) allocation
failures to complete a given function is to be printed, when set
through a call to RFs::SetDebugRegister() in _DEBUG or _DEBUG_RELEASE mode.
*/
#define KALLOC		0x0008


/**
@publishedPartner


A bit value indicating that tracing is to be active in
LFFS code, when set through a call to RFs::SetDebugRegister()
in _DEBUG or _DEBUG_RELEASE mode.
*/
#define KLFFS		0x0010


/**
@publishedPartner


A bit value indicating that tracing is to be active in
ISO9660 code, when set through a call to RFs::SetDebugRegister()
in _DEBUG or _DEBUG_RELEASE mode.
*/
#define	KISO9660	0x0020


/**
@publishedPartner


A bit value indicating that tracing is to be active in
NTFS code, when set through a call to RFs::SetDebugRegister()
in _DEBUG or _DEBUG_RELEASE mode.
*/
#define	KNTFS		0x0040


/**
@publishedPartner


A bit value indicating that tracing is to be active in
ROFS code, when set through a call to the function RFs::SetDebugRegister()
in _DEBUG or _DEBUG_RELEASE mode.
*/
#define	KROFS		0x0080


/**
@publishedPartner


A bit value indicating that tracing is to be active in
concurrent file system code, when set through a call to the function RFs::SetDebugRegister()
in _DEBUG or _DEBUG_RELEASE mode.
*/
#define KTHRD		0x0100

/**
@internalTechnology
*/
#define KCACHE		0x0200


/**
@internalTechnology
@prtototype

A bit value indicating that tracing is to be active in
COMPFS code, when set through a call to the function RFs::SetDebugRegister()
in _DEBUG or _DEBUG_RELEASE mode.
*/
#define	KCOMPFS		0x0400



// #define _DEBUG_RELEASE

const TInt KAllocFailureOn=0;
const TInt KAllocFailureOff=-1;

#if defined(_DEBUG) || defined(_DEBUG_RELEASE)
const TInt KControlIoCancelNCNotifier=KMaxTInt-1;
const TInt KControlIoNCDebugNotifierOn=KMaxTInt-2;
const TInt KControlIoNCDebugNotifierOff=KMaxTInt-3;
const TInt KControlIoGetCorruptLogRecord=KMaxTInt-4;
const TInt KControlIoGetNumberOfCorruptLogRecords=KMaxTInt-5;
const TInt KControlIoGetCorruptListFile=KMaxTInt-6;
const TInt KControlIoCorruptLogRecordReset=KMaxTInt-7;
const TInt KControlIoCacheCount=KMaxTInt-8;
const TInt KControlIoGetLocalDriveNumber=KMaxTInt-9;
const TInt KControlIoCancelDeferredDismount=KMaxTInt-10;

const TInt KNCDebugNotifierValue=-500000;	// between 0 and 1 second

GLREF_D TInt DebugNCNotifier;

class TIOCacheValues
	{ 
public:
	TInt iFreeCount;
	TInt iCloseCount;
	TInt iAllocated;
	};


struct TFsDebugCorruptLogRecord
	{
	TFileName iProcessName;
	TFileName iFileName;
	TInt iError;
	};

typedef TPckgBuf <TFsDebugCorruptLogRecord> TFsDebugCorruptLogRecordBuf;

#endif

enum TLoaderDebugFunction
	{
	ELoaderDebug_SetHeapFail,
	ELoaderDebug_SetRFsFail
	};


enum TFsDebugFunction
	{
	EFsSetAllocFailure,
	EFsSetErrorCondition,
	EFsSetDebugRegister,
	EFsDebugNotify
	};

#endif

