// D32HWA.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __D32HWA_H__
#define __D32HWA_H__

#include <e32std.h>
#include <e32ver.h>
// Transfer Buffers
#include <e32transbuf.h>


// The following #define affects RHwaTask's GetData and PutData functions.
//#define GETPUTDATA_ARE_KERNELSERVERCALLS

// ID and call number constants
const TInt KDeviceIdNull                 = 0xf0000000;
const TInt KTaskIdNull                   = 0xf0000000;
const TInt KConIdNull                    = 0xf0000000;
const TInt KDeviceCallBase               = 0x00000000;
const TInt KTaskCallBase                 = 0x80000000;
const TInt KDeviceSpecificDeviceCallBase = 0x40000000;
const TInt KDeviceSpecificTaskCallBase   = 0xC0000000;

// Task priority constants
const TInt KHwaTaskPriorityVeryLow  = 100;
const TInt KHwaTaskPriorityLow      = 200;
const TInt KHwaTaskPriorityNormal   = 300;
const TInt KHwaTaskPriorityHigh     = 400;
const TInt KHwaTaskPriorityVeryHigh = 500;

// Flags used by RHwaTask::Logon
const TUint KNoMessageNotification = 0x00000001;

const TInt KErrTaskMessageReceived = KErrCompletion;

enum THwaDeviceStatus 
	{EHwaDevUnknown, EHwaDevRunning, EHwaDevIdle, EHwaDevStalled};

enum THwaTaskStatus 
	{EHwaTaskUnknown, EHwaTaskReady, EHwaTaskRunning, EHwaTaskStalled, EHwaTaskSuspended, EHwaTaskKilled};

class TCapsDevHwaV01
	{
public:
	TVersion version;
	};

class TTaskCreateInfo
	{
public:
	inline TTaskCreateInfo();
	inline TTaskCreateInfo(TUid aTaskId, TDesC8* aCodeBuffer, TDesC8* anArgumentBuffer, TInt aFlagsWord,
						   TInt aNumWindows);
public:
	TUid iTaskId;
	TDesC8* iCodeBuffer; 
	TDesC8* iArgumentBuffer; 
	TInt iFlagsWord;
	TInt iNumWindows;
	};
typedef TPckgBuf<TTaskCreateInfo> TTaskCreateInfoBuf;

const TInt KTfBufIdNull = 0x0;
class TTaskDataTfInfo
	{
public:
	inline TTaskDataTfInfo();
	inline TTaskDataTfInfo(RTransferBuffer* aBuf, TRequestStatus* aStat, TInt aBytesToBeTransfered,
						   TInt* aBytesTransfered, TInt aTransferId);
public:
	RTransferBuffer* iBuf;
	TRequestStatus* iStat;
	TInt iBytesToBeTransfered;
	TInt* iBytesTransfered;
	TInt iTransferId;
	};
typedef TPckgBuf<TTaskDataTfInfo> TTaskDataTfInfoBuf;

class TTaskConnectInfo
	{
public:
	TInt iConnectTaskHandle;
	TInt iOutputIndex;
	TInt iInputIndex;
	TInt iConnectionId; 
	};
typedef TPckgBuf<TTaskConnectInfo> TTaskConnectInfoBuf;

class TTaskPropertyInfo
	{
public:
	TUid iTaskId;									// The UID for the task
	TBuf<32> iName;									// Human readable name for the task (up to 32 characters)
	TUint iOwningThreadId;							// Handle of owning thread? (the thread that created it)
	TInt iType;										// The type of task (device dependent if not useful to others)
	TUint iMessageDepth;							// Max # of simultaneous outstanding msgs allowed by the task
	TUint iNumInputs;								// Number of inputs
	TUint iNumOutputs;								// Number of outputs
	TInt iDeviceDependent[10];						// just that
	};
typedef TPckgBuf<TTaskPropertyInfo> TTaskPropertyInfoBuf;

class TTaskStatusInfo
	{
public:
	THwaTaskStatus iStatus;							// Task's execution status
	TInt iPriority;									// Priority for the task
	TInt iNumStreams;								// Number of stream connections defined for the task
	TTaskConnectInfo iTaskConnections[16];			// Defined connections for this task.
	};
typedef TPckgBuf<TTaskStatusInfo> TTaskStatusInfoBuf;

class TTaskLogonInfo
	{
public:
	TRequestStatus* iStatus;
	TUint iFlags;
	};

class TTaskSendMsgInfo
	{
public:
	TRequestStatus* iStatus;
	TDesC8* iMessage;
	};

class TTaskGetMsgInfo
	{
public:
	TRequestStatus* iStatus;
	TDes8* iMessage;
	};

class TTaskPriorityInfo
	{
public:
	TRequestStatus* iStatus;
	TInt iPriority;
	};

class THwaDeviceCapabilities
	{
public:
	TUid iDeviceUid;
	TInt iMaxMessageSize;
	TBool iLittleEndian;
	TInt iWordSize;										
	TInt iNumberOfDevices;
	TInt iMips;
	TInt iTotalMemory;
	TInt iDeviceDependent[8];
	};
typedef TPckgBuf<THwaDeviceCapabilities> THwaDeviceCapsBuf;

class THwaDeviceResources
	{
public:
	TInt iSpareMips;		
	TInt iSpareMemory; 
	TInt iDeviceDependent[8];
	};
typedef TPckgBuf<THwaDeviceResources> THwaDeviceResourcesBuf;

class THwaTaskResources
	{
public:
	TInt iMipsRequired;
	TInt iMemoryRequired;
	TInt iDeviceDependent[12];
	};
typedef TPckgBuf<THwaTaskResources> THwaTaskResourcesBuf;

class TTransferBufferInfo
	{
public:
	TTransferBufferType iType;
	TUint iPhysicalAddressStart;
	TUint iPhysicalAddressEnd;
	TUint iSize;
	};
typedef TPckgBuf<TTransferBufferInfo> TTransferBufferInfoBuf;

class RHwaTask;
class RHwaDevice : public RBusLogicalChannel
	{
public:
	enum TVer
		{
		EMajorVersionNumber = 1, EMinorVersionNumber = 0, EBuildVersionNumber = KE32BuildVersionNumber
		};
	enum TControl
		{
		EDeviceGetId, EDeviceGetCaps, EDeviceStatus, EDeviceCurrentResources, EDeviceSvCreateTask1,
		EDeviceCreateTask2, EDeviceCloseTask1, EDeviceSvCloseTask2, EDeviceNumTasks, EDeviceGetNextTask,
		EDeviceSvDuplicateTask
		};
public:
	inline TInt Open(TInt aDeviceId);
	inline TVersion VersionRequired() const;
	inline void GetDeviceId(TInt& aDeviceId);
	inline TInt GetCapabilities(THwaDeviceCapabilities& aDeviceCaps);
	inline void GetStatus(THwaDeviceStatus& aStatus);
	inline TInt GetCurrentResources(THwaDeviceResources& aDeviceResources, TUint aFlag);
	inline TInt CreateTask(RHwaTask& aTask, TUid aTaskId, TDesC8* aCodeBuffer=NULL,
						   TDesC8* anArgumentBuffer=NULL, TInt aFlagsWord=0, TInt aNumWindows=1);
	inline TInt CloseTask(RHwaTask& aTask);
	inline void NumberOfTasks(TInt& aNumTasks);
	inline TInt Tasks(TTaskPropertyInfo& aTaskInfo);
	inline TInt DuplicateTask(RHwaTask& aTask, TInt aFindHandle);
	// Functions for fielding calls on behalf of the RHwaTask class
	inline TInt TaskCall(TInt aCallNumber, TInt aTaskHandle, TAny* aParams=0);
	inline TInt SvTaskCall(TInt aCallNumber, TInt aTaskHandle, TAny* aParams=0);
	};

class RHwaTask : public RHandleBase
	{
public:	
	enum TControl
		{
		ETaskSetPriority = KTaskCallBase, ETaskResources, ETaskProperties, ETaskStatus, ETaskBufferInfo,
		ETaskLogon, ETaskLogonCancel, ETaskSvStart, ETaskSuspend, ETaskResume, ETaskSvInputFrom,
		ETaskInputConnect, ETaskOutputConnect, ETaskSvDisConnectInput, ETaskSvPutData, ETaskPutDataCancel,
		ETaskSvGetData, ETaskGetDataCancel, ETaskInputBufferSize, ETaskOutputBufferSize, ETaskSendMessage,
		ETaskGetMessage
		};
public:
	inline TInt SetPriority(TInt aPriority);
	inline void OwningDevice(RHwaDevice& aDevice);
	inline TInt GetTaskResources(THwaTaskResources& aTaskResources);
	inline TInt GetTaskProperties(TTaskPropertyInfo& aPropertyInfo);
	inline TInt GetTaskStatus(TTaskStatusInfo& aStatusInfo);
	inline TInt GetBufferInfo(TTransferBufferInfo& aBufferInfo);
	inline TInt Close();

	// Task control
	inline void Logon(TRequestStatus& aStatus, TUint aFlagsWord=0);
	inline void LogonCancel(); 
	inline TInt Start();
	inline TInt Suspend();
	inline TInt Resume();

	// Data transfer between tasks
	inline TInt InputFrom(const RHwaTask& anOutputTask, TInt anOutputIndex=0, TInt anInputIndex=0,
						  TInt aConnectionId=KConIdNull);
	inline TInt InputConnection(RHwaTask& aTask, TInt anInputIndex=0, TInt aConnectionId=KConIdNull);
	inline TInt OutputConnection(RHwaTask& aTask, TInt anOutputIndex=0, TInt aConnectionId=KConIdNull);
	inline TInt DisConnectInput(TInt anInputIndex=0, TInt aConnectionId=KConIdNull);

	// Data transfer between task and Epoc
	inline TInt PutData(RTransferBuffer& aBuf, TInt* aBytesTransfered=NULL, TInt aTransferId=KTfBufIdNull);
	inline TInt PutData(RTransferBuffer& aBuf, TInt aBytesToBeTransfered, TInt* aBytesTransfered=NULL,
						TInt aTransferId=KTfBufIdNull);
	inline TInt PutData(RTransferBuffer& aBuf, TRequestStatus& aStat, TInt* aBytesTransfered=NULL,
						TInt aTransferId=KTfBufIdNull);
	inline TInt PutData(RTransferBuffer& aBuf, TRequestStatus& aStat, TInt aBytesToBeTransfered,
						TInt* aBytesTransfered=NULL, TInt aTransferId=KTfBufIdNull);
	inline TInt PutDataCancel(TInt aTransferId=KTfBufIdNull);
	inline TInt GetData(RTransferBuffer& aBuf, TInt* aBytesTransfered=NULL, TInt aTransferId=KTfBufIdNull);
	inline TInt GetData(RTransferBuffer& aBuf, TRequestStatus& aStat, TInt* aBytesTransfered=NULL,
						TInt aTransferId=KTfBufIdNull);
	inline TInt GetDataCancel(TInt aTransferId=KTfBufIdNull);
	inline TInt InputBufferSize(TInt& aSize);
	inline TInt OutputBufferSize(TInt& aSize);

	// Messaging
	inline TInt SendMessage(TDesC8& aMessage);
	inline TInt SendMessage(TRequestStatus& aStatus, TDesC8& aMessage);
	inline TInt GetMessage(TDes8& aMessage);
	inline TInt GetMessage(TRequestStatus& aStatus, TDes8& aMessage);

protected:
	inline void SetOwningDevice(const RHwaDevice& aDevice);
	RHwaDevice iOwningDevice;

friend class RHwaDevice;
	};

#include <d32hwa.inl>
#endif
