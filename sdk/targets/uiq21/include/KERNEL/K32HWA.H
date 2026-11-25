// K32HWA.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __K32HWA_H__
#define __K32HWA_H__

#include <k32std.h>
#include <d32hwa.h>
#include <e32ver.h>

const TInt KHwaMajorVersionNumber = 1;
const TInt KHwaMinorVersionNumber = 1;
const TInt KHwaBuildVersionNumber = KE32BuildVersionNumber;

const TInt KHwaMaxDataRequestPerTask = 4;

_LIT(KHwaPanicDeviceLit, "D32HWA");

enum THwaPanic
	{
	EHwaPanicTaskGeneral             =  0,
	EHwaPanicTaskReadInfoFail        =  1,
	EHwaPanicHandleWriteFail         =  2,
	EHwaPanicRequestFromWrongThread  =  3,
	EHwaPanicRequestAlreadyPending   =  4,
	EHwaPanicRequestNotPending       =  5,
	EHwaPanicRequestTooManyPending   =  6,
	EHwaPanicTaskCallUnsupported     =  7,
	EHwaPanicTaskNegativeAccessCount =  8,
	EHwaPanicHandleNotFound          =  9,
	EHwaPanicTaskDuplicateFail       = 10,
	EHwaPanicTaskOrphaned            = 11,
	};

class DHwaTask;
class DHwaDevice;
class DHwaDevicePdd;
class THwaTaskHwInterface;

enum THwaDataTfDir {EPutDataToTask, EGetDataFromTask};
enum THwaConnectionDir {EInputConnection, EOutputConnection};
class THwaDataTfReq
	{
public:
	THwaDataTfReq(DHwaTask* anOwningTask);
	inline DTransferBuffer* Buffer();
	inline TInt BytesToBeTransfered();
	inline THwaDataTfDir Direction();
	inline TInt TransferId();
	inline void Complete(TInt aReason, TInt aBytesTransfered=0);
	inline void DoComplete(TInt aReason, TInt aBytesTransfered=0);
private:
	void DoComplete();
	static TInt CompleteDfc(TAny* aDataReq);
private:
	DTransferBuffer* iBuf;
	TRequestStatus* iStatus;
	TInt iBytesToBeTransfered;
	TInt* iTransferLengthAddress;
	THwaDataTfDir iDir;
	TInt iTransferId;
	DHwaTask* iOwningTask;
	DThread* iOwningThread;
	TInt iCompletionReason;
	TInt iBytesTransfered;
	TSglQueLink iLink;
	TDfc iCompleteDfc;
	TBool iInUse;
friend class DHwaTask;
	};

class THwaTaskConnection
	{
public:
	THwaTaskConnection(DHwaTask* aConnectedTask, TInt anIndex, TInt aPeerIndex, TInt aConnectionId);
	inline DHwaTask* ConnectedTask() const;
	inline TInt ConnectionId() const;
	inline TInt Index() const;
	inline TInt PeerIndex() const;
private:
	DHwaTask* iConnectedTask;
	TInt iIndex;
	TInt iPeerIndex;
	TInt iConnectionId;
	TSglQueLink iLink;
friend class DHwaTask;
	};

class DHwaTask : public CObject
	{
public:
	DHwaTask(DHwaDevice* anOwningDevice, DThread* anOwningThread);
	~DHwaTask();
	void CreateL(TUid aTaskId, TInt aNumWindows, THwaTaskHwInterface* aHwInterface);
	TInt Init(TDesC8* aCodeBuffer, TDesC8* anArgumentBuffer, TInt aFlagsWord, TInt aNumWindows);
	inline THwaTaskStatus Status();
	inline TUid TaskId();
	inline DHwaDevice* OwningDevice();
	inline DHwaDevicePdd* OwningDevicePdd();
	inline DThread* OwningThread();
	inline void ResourcesRequired(TDes8& aResourcesRequired);
	TInt SetPriority(TAny* aArg);
	TInt Start(TAny *aArg);
	TInt Resume(TAny* aArg);
	TInt Suspend(TAny* aArg);
	virtual void Close();
	// The following callbacks immediately signal a thread request complete,
	// so they mustn't be called, by the PDD, from within an ISR.
	inline void LogonComplete(TInt aReason);
	inline void CreateComplete(TInt aResult);
	inline void CloseComplete(TInt aResult);
	inline void SendMessageComplete(TInt aResult);
	inline void GetMessageComplete(TInt aResult);
	inline void SetPriorityComplete(TInt aResult);
	inline void StartComplete(TInt aResult);
	inline void SuspendComplete(TInt aResult);
	inline void ResumeComplete(TInt aResult);
	// This callback queues its own DFC, thus can be called from everywhere.
	inline void CompleteLogon(TInt aReason);
	virtual THwaDataTfReq* GetNextRequest(THwaDataTfDir aDir, TInt aTransferId=KTfBufIdNull);
	virtual void SetStatus(THwaTaskStatus aStatus);
	inline TBool TransferRequestPending(THwaDataTfDir aDir);
	inline DHwaTask* GetInputTask(TInt anIndex, TInt aConnectionId=KConIdNull);
	inline DHwaTask* GetOutputTask(TInt anIndex, TInt aConnectionId=KConIdNull);
	inline void Panic(const TDesC& aCategory, TInt aReason);
	inline DTransferWindow* Window(TInt anIndex=0);
	void GetProperties(TTaskPropertyInfo& aPropertyInfo);
	void GetStatus(TTaskStatusInfo& aStatusInfo);
private:
	inline void GetBufferInfo(TDes8& aBufferInfo);
	inline void ProcessComplete(TInt aResult);
	void LogonReq(TAny* aStatus);
	void DataTransferReq(DTransferBuffer* aBuf, TRequestStatus* aStatus, THwaDataTfDir aDir,
						 TInt aBytesToBeTransfered, TInt* aBytesTransfered, TInt aTransferId);
	TInt DataTransferCancel(THwaDataTfDir aDir, TInt aTransferId);
	THwaTaskConnection* GetConnection(TSglQue<THwaTaskConnection>& aQueue, TInt anIndex, TInt aConnectionId);
	TInt AddConnection(THwaConnectionDir aDir, DHwaTask* aConnectedTask, TInt anIndex,
					   TInt aPeerIndex, TInt aConnectionId);
	TInt RemoveConnection(THwaConnectionDir aDir, TInt anIndex, TInt aConnectionId);
	static TInt CompleteLogonDfc(TAny* aTask);
	TInt SendMessage(TAny* aArg);
	TInt GetMessage(TAny* aArg);
private:
	DHwaDevice* iOwningDevice;
	TUid iTaskId;
	THwaTaskStatus iStatus;
	TInt iHWifcCloseResult;
	DThread* iOwningThread;
	THwaTaskHwInterface* iHwInterface;
	TRequestStatus* iLogonRequestStatus;
	TUint iLogonRequestFlags;
	TInt iLogonCompletionReason;
	TDfc iLogonCompleteDfc;
	CArrayFixFlat<TInt> iWindowHandles;
	CArrayPtrFlat<DTransferWindow> iWindows;
	TInt iNumWindows;
	TRequestStatus* iCreateRequestStatus;
	TRequestStatus* iSendMsgRequestStatus;
	TRequestStatus* iGetMsgRequestStatus;
	TRequestStatus* iProcessRequestStatus;
	DThread* iClosingThread;
	DThread* iProcessThread;
	TRequestStatus* iCloseRequestStatus;
	TSglQue<THwaDataTfReq> iDataTfReqs;
	TSglQue<THwaDataTfReq> iFreeTfSlots;
	TSglQue<THwaTaskConnection> iInputConnections;
	TSglQue<THwaTaskConnection> iOutputConnections;
friend class DHwaDevice;
friend class THwaDataTfReq;
	};

class THwaTaskHwInterface
	{
public:
	inline THwaTaskHwInterface(DHwaTask* anOwningTask);
	virtual ~THwaTaskHwInterface() {};
	virtual TInt Init(TDesC8* aCodeBuffer, TDesC8* anArgumentBuffer, TInt aFlagsWord, TInt aNumWindows)=0;
	virtual void DoCreateTask() {iOwningTask->CreateComplete(KErrNone);}
	virtual void ResourcesRequired(TDes8& aResourcesRequired)=0;
	virtual void GetProperties(TTaskPropertyInfo& aPropertyInfo)=0;
	virtual void GetStatus(TTaskStatusInfo& aStatusInfo)=0;
	virtual void GetBufferInfo(TDes8& aBufferInfo)=0;
	virtual TInt Start()=0;
	virtual TInt Resume()=0;
	virtual TInt Suspend()=0;
	virtual void DoSetPriority(TInt aPriority)
		{iPriority = aPriority; iOwningTask->SetPriorityComplete(KErrNone);}
	virtual TInt DoInputFrom(const DHwaTask& /*aTask*/, TInt /*aOutputIndex*/, TInt /*aInputIndex*/,
							 TInt /*aConnectionId*/) {return KErrNone;}
	virtual void DoGetData(TInt /*aTransferId*/) {}
	virtual void DoGetDataCancel(TInt /*aTransferId*/) {}
	virtual void DoPutData(TInt /*aTransferId*/) {}
	virtual void DoPutDataCancel(TInt /*aTransferId*/) {}
	virtual TInt InputBufferSize() {return 0;}
	virtual TInt OutputBufferSize() {return 0;}
	virtual TInt SendMessage(TDesC8& /*aMessage*/) {return KErrNone;}
	virtual TInt GetMessage(TDes8& /*aMessage*/) {return KErrNone;}
	virtual TInt DoTaskCall(TInt /*aCallNumber*/, TAny* /*aParams*/)
		{iOwningTask->Panic(KHwaPanicDeviceLit, EHwaPanicTaskCallUnsupported); return KErrNone;}
	virtual TInt Close() {return KErrNone;}
	virtual void DoCloseTask(TBool aCallbackRequest=ETrue)
		{if (aCallbackRequest) iOwningTask->CloseComplete(KErrNone);}
	virtual void DoLogon(TUint /*aFlagsWord*/) {}
protected:
	DHwaTask* iOwningTask;
	TInt iPriority;
	};

class DHwaDevicePdd : public CBase
	{
public:
	virtual void GetDeviceCaps(TDes8& aDeviceCaps)=0;
	virtual void GetCurrentResources(TDes8& aDeviceResources, TInt aFlag)=0;
	virtual TUint32 PowerRequirement()=0;
	virtual THwaTaskHwInterface* CreateTaskHwInterfaceL(TUid aTaskId, DHwaTask* anOwningTask)=0;
	virtual TInt DoPowerOn()=0;
	virtual void DoPowerStandby()=0;
	virtual void DoPowerEmergencyStandby()=0;
protected:
	inline DHwaDevicePdd();
	virtual void DoCancel(TInt /*aReqNo*/) {}
	virtual void DoRequest(TInt /*aReqNo*/, TAny* /*a1*/, TAny* /*a2*/) {}
	virtual TInt DoControl(TInt /*aFunction*/, TAny* /*a1*/, TAny* /*a2*/) {return KErrNone;}
protected:
	DHwaDevice* iLdd;
	THwaDeviceStatus iStatus;
friend class DHwaDevice;
	};

class DLogicalDeviceHwa: public DLogicalDevice
	{
public:
	DLogicalDeviceHwa();
	virtual TInt Install();
	virtual void GetCaps(TDes8& aDes) const;
	virtual DLogicalChannel* CreateL();
	void TaskConAddL(DHwaTask* aTask);
	void TaskConRemove(DHwaTask* aTask);
	TInt TaskConFind(TInt& aFindHandle);
	DHwaTask* TaskConAt(TInt aFindHandle);
protected:
	~DLogicalDeviceHwa();
private:
	CObjectConIx* iTaskConIx;
	CObjectCon* iTaskCon;
	};

class DHwaPowerHandler : public DPowerHandler
	{
public:
	DHwaPowerHandler(DHwaDevice* aLdd);
	void RequestComplete();
	void RequestPending();
	static void Timeout(TAny* aHandler, TInt aDelay);
	virtual TInt DoPowerOn();
	virtual void DoPowerStandby();
	virtual void DoPowerEmergencyStandby();
public:
	DHwaDevice* iLdd;
	TTickLink iTimer;
	};

class DHwaDevice : public DLogicalChannel
	{
public:
	DHwaDevice(DLogicalDevice* aDevice);
	~DHwaDevice();
	virtual TInt PowerOn();
	virtual void PowerStandby();
	virtual void PowerEmergencyStandby();
	inline void SetStatus(THwaDeviceStatus aStatus);
	inline THwaDeviceStatus Status();
	inline TInt DeviceId();
	inline DHwaDevicePdd* DevicePdd();
	inline DThread* OwningThread();
protected:
	// the next functions all deal with task objects
	inline DHwaTask* Task(TInt aHandle);
	TBool TaskIsOursAndShared(DHwaTask* aTask);
	TInt TaskCall(TInt aCallNumber, TInt aTaskHandle, TAny* aParams);
	TInt TaskCallProperties(DHwaTask* aTask, TAny* aParams);
	TInt TaskCallStatus(DHwaTask* aTask, TAny* aParams);
	TInt TaskCallInputFrom(DHwaTask* aTask, const TAny* aArg);
	TInt TaskCallInputConnect(DHwaTask* aTask, TAny* aArg);
	TInt TaskCallOutputConnect(DHwaTask* aTask, TAny* aArg);
	TInt TaskCallDisConnectInput(DHwaTask* aTask, const TAny* aArg);
	TInt TaskCallTransferData(DHwaTask* aTask, const TAny* aArg, THwaDataTfDir aDir);
	TInt CreateTask1(const TAny* aArg1, TAny* aArg2);
	TInt CreateTask2(TInt aHandle, TRequestStatus* aStatus);
	TInt GetNextTask(TAny* aInfoBuf);
	TInt DuplicateTask(const TAny* aArg1, TAny* aArg2);
	TInt CloseTask1(TInt aHandle, TRequestStatus* aStatus);
	TInt CloseTask2(TInt aHandle);
	// here are the inherited virtual channel functions
	virtual void DoCreateL(TInt aDeviceId, CBase* aDriver, const TDesC* anInfo, const TVersion& aVer);
	virtual void DoCancel(TInt aReqNo);
	virtual void DoRequest(TInt aReqNo, TAny* a1, TAny* a2);
	virtual TInt DoControl(TInt aFunction, TAny* a1, TAny* a2);
	virtual void Close();
private:
	TInt iDeviceId;
	DHwaDevicePdd* iPdd;
	DHwaPowerHandler* iPowerHandler;
	CObjectIx* iTaskIx;
	TInt iFindHandle;
friend class DHwaPowerHandler;
	};

#include <k32hwa.inl>
#endif

