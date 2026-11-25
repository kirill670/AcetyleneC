// M32MON.H
//
// Copyright (c) 1999-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __M32MON_H__
#define __M32MON_H__
#ifndef __M32STD_H__
#include <m32std.h>
#endif

class DMonObject
	{
public:
	TAny* iVptr;
	TInt iAccessCount;
	DMonObject* iOwner;
	CObjectCon* iContainer;
	HBufC* iName;
public:
	void AppendName(TDes& aDes);
	void FullName(TDes& aDes);
	void DumpData();
	DMonObject* Owner();
	TInt Type();
	};

/**
 * Debug Monitor class
 */
class Monitor
	{
public:
	enum TObjectType
		{
		EThread=0,
		EProcess=1,
		EChunk=2,
		ELibrary=3,
		ESemaphore=4,
		EMutex=5,
		ETimer=6,
		EServer=7,
		ESession=8,
		ELogicalDevice=9,
		EPhysicalDevice=10,
		ELogicalChannel=11,
		EChangeNotifier=12,
		EUndertaker=13,
		};
public:
	// KP
	void Print(const TDesC& aDes);
	void PrintLine(const TDesC& aDes);
	void NewLine();
	void Printf(TRefByValue<const TDesC> aFmt,...);
	void Input(TDes& aDes, const TDesC& aPrompt);
	void WaitForSensibleInput();
	void SkipSpaces(const TDesC& in, TInt& i);
	TInt ReadHex(const TDesC& in, TInt& i, TUint& r);
	void ProcessMemDumpCommand(const TDesC& aDes, TInt& i);
	void ProcessObjectDumpCommand(const TDesC& aDes, TInt& i);
	void ProcessObjectFullDumpCommand(const TDesC& aDes, TInt& i);
	void DisplayFaultInfo();
	void ProcessInfoCommand(const TDesC& aDes, TInt& i);
	TBool DoCommand();
	void DumpObjectContainer(const TDesC& aDes, TInt& i);
	void DumpObjectData(DMonObject* pO, TInt type);
	void DumpThreadData(DPlatThread* pT);
	void DumpProcessData(DPlatProcess* pP);
	void DumpChunkData(DPlatChunk* pC);
	CObjectCon* Container(TInt anIndex);
	void ProcessError(TInt anError);
	void Init(TAny* aCategory, TInt aReason);
public:
	// KC
	TInt Enter();
	void Leave(TInt aReason);
	static void HandleException();
	void QuadrupleBeepAndPowerDown();
	void CpuInit();
	void DumpCpuThreadData(DPlatThread* pT);
	void DumpCpuProcessData(DPlatProcess* pP);
	void DumpCpuChunkData(DPlatChunk* pC);
	void DumpCpuRegisters();
public:
	// KA
	void InitUart();
	void UartOut(TUint aChar);
	TUint8 UartIn();
	TBool CheckPower();
public:
	TUint32 iTrapState[16];
	TInt iTrapResult;
	TUint32 iExceptionInfo[4];
	TBuf<80> iFaultCategory;
	TInt iFaultReason;
	};

GLREF_D Monitor TheMonitor;
GLREF_D TLinAddr TheMonitorExceptionHandler;
GLREF_C void KFormat(TDes& aDes, const TDesC& aFmt, VA_LIST aList);
#endif
