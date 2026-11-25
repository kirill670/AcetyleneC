// D32HWA.INL
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//


// Class RHwaDevice

_LIT(KRHwaDeviceLit, "Hwa"); 

TInt RHwaDevice::Open(TInt aDeviceId)
	{
	return DoCreate(KRHwaDeviceLit, VersionRequired(), NULL, aDeviceId, NULL, NULL, EOwnerThread);
	}

TVersion RHwaDevice::VersionRequired() const
	{
	return TVersion(EMajorVersionNumber, EMinorVersionNumber, EBuildVersionNumber);
	}

void RHwaDevice::GetDeviceId(TInt& aDeviceId)
	{
	DoControl(EDeviceGetId, &aDeviceId);
	}

TInt RHwaDevice::GetCapabilities(THwaDeviceCapabilities& aDeviceCaps)
	{
	THwaDeviceCapsBuf buf;
	TInt r = DoControl(EDeviceGetCaps, &buf);
	if (r == KErrNone)
		aDeviceCaps = buf();
	return r;
	}

void RHwaDevice::GetStatus(THwaDeviceStatus& aStatus)
	{DoControl(EDeviceStatus, &aStatus);}

TInt RHwaDevice::GetCurrentResources(THwaDeviceResources& aDeviceResources, TUint aFlag)
	{
	THwaDeviceResourcesBuf buf;
	TInt r = DoControl(EDeviceCurrentResources, &buf, (TAny*) aFlag);
	if (r == KErrNone)
		aDeviceResources = buf();
	return r;
	}

TInt RHwaDevice::CreateTask(RHwaTask& aTask, TUid aTaskId, TDesC8* aCodeBuffer, TDesC8* aArgumentBuffer,
							TInt aFlagsWord, TInt aNumWindows)
	{ 
	// phase one: we create the host-side task
	TPckgBuf<TInt> h;
	TTaskCreateInfo inf = TTaskCreateInfo(aTaskId, aCodeBuffer, aArgumentBuffer, aFlagsWord, aNumWindows);
	TTaskCreateInfoBuf cb = TTaskCreateInfoBuf(inf);
	TInt r = DoSvControl(EDeviceSvCreateTask1, &cb, &h);
	if (r == KErrNone)
		{
		aTask.SetOwningDevice(*this);
		aTask.SetHandle(h());
		}
	else
		{
		return r;											// failure 1
		}
	// phase two: we create the dsp-side task (async call)
	TRequestStatus s;
	(void) DoSvControl(EDeviceCreateTask2, (TAny*) aTask.Handle(), &s);
	User::WaitForRequest(s);
	if (s.Int() == KErrNone)
		{
		return KErrNone;									// success
		}
	else
		{
		// phase three: clean up if something in p2 went wrong
		(void) DoSvControl(EDeviceSvCloseTask2, (TAny*) aTask.Handle());
		return s.Int();										// failure 2
		}
	}

TInt RHwaDevice::CloseTask(RHwaTask& aTask)
	{
	// phase one: we close the dsp-side task (async call)
	TRequestStatus s;
	(void) DoSvControl(EDeviceCloseTask1, (TAny*) aTask.Handle(), &s);
	User::WaitForRequest(s);
	if (s.Int() != KErrNone)
		{
		// what to do here?
		}
	// phase two: we close the host-side task
	TInt r = DoSvControl(EDeviceSvCloseTask2, (TAny*) aTask.Handle());
	aTask.SetHandle(KNullHandle);
	if (s.Int() != KErrNone)
		{
		return s.Int();
		}
	else
		{
		return r;
		}
	}

void RHwaDevice::NumberOfTasks(TInt& aNumTasks)
	{
	DoControl(EDeviceNumTasks, &aNumTasks);
	}

TInt RHwaDevice::Tasks(TTaskPropertyInfo& aTaskInfo)
	{
	TTaskPropertyInfoBuf buf;
	TInt r = DoControl(EDeviceGetNextTask, &buf);
	if (r != 0)
		aTaskInfo = buf();
	return r;
	}

TInt RHwaDevice::DuplicateTask(RHwaTask& aTask, TInt aFindHandle)
   {
   TPckgBuf<TInt> h;
   TInt r = DoSvControl(EDeviceSvDuplicateTask, (TAny*) aFindHandle, &h); 
   if (r == KErrNone)
	   {
	   aTask.SetHandle(h());
	   aTask.SetOwningDevice(*this); 
	   }
   return r;
   }

TInt RHwaDevice::TaskCall(TInt aCallNumber, TInt aTaskHandle, TAny* aParams)
	{
	return DoControl(aCallNumber, (TAny*) aTaskHandle, aParams);
	}

TInt RHwaDevice::SvTaskCall(TInt aCallNumber, TInt aTaskHandle, TAny* aParams)
	{
	return DoSvControl(aCallNumber, (TAny*) aTaskHandle, aParams);
	}

// Class RHwaTask

TInt RHwaTask::SetPriority(TInt aPriority)
	{
	TRequestStatus s; TTaskPriorityInfo info = {&s, aPriority};
	TInt r = iOwningDevice.TaskCall(ETaskSetPriority, iHandle, &info);
	if (r != KErrNone) return r;
	User::WaitForRequest(s);
	return s.Int();
	}

void RHwaTask::SetOwningDevice(const RHwaDevice& aDevice)
	{
	iOwningDevice = aDevice;
	}

void RHwaTask::OwningDevice(RHwaDevice& aDevice)
	{aDevice = iOwningDevice;}

TInt RHwaTask::GetTaskResources(THwaTaskResources& aTaskResources)
	{
	THwaTaskResourcesBuf buf;
	TInt r = iOwningDevice.TaskCall(ETaskResources, iHandle, &buf);
	if (r == KErrNone)
		aTaskResources = buf();
	return r;
	}

TInt RHwaTask::GetTaskProperties(TTaskPropertyInfo& aPropertyInfo)
	{
	TTaskPropertyInfoBuf buf;
	TInt r = iOwningDevice.TaskCall(ETaskProperties, iHandle, &buf);
	if (r == KErrNone)
		aPropertyInfo = buf();
	return r;
	}
	
TInt RHwaTask::GetTaskStatus(TTaskStatusInfo& aStatusInfo)
	{
	TTaskStatusInfoBuf buf;
	TInt r = iOwningDevice.TaskCall(ETaskStatus, iHandle, &buf);
	if (r == KErrNone)
		aStatusInfo = buf();
	return r;
	}
	
TInt RHwaTask::GetBufferInfo(TTransferBufferInfo& aBufferInfo)
	{
	TTransferBufferInfoBuf buf;
	TInt r = iOwningDevice.TaskCall(ETaskBufferInfo, iHandle, &buf);
	if (r == KErrNone)
		aBufferInfo = buf();
	return r;
	}

TInt RHwaTask::Close()
	{
	return iOwningDevice.CloseTask(*this);
	}

void RHwaTask::Logon(TRequestStatus& aStatus, TUint aFlagsWord)
	{
	TTaskLogonInfo info = {&aStatus, aFlagsWord};
	(void) iOwningDevice.TaskCall(ETaskLogon, iHandle, &info);
	}

void RHwaTask::LogonCancel()
	{
	(void) iOwningDevice.TaskCall(ETaskLogonCancel, iHandle);
	}

TInt RHwaTask::Start()
	{
	TRequestStatus s; 
  	TInt r = iOwningDevice.SvTaskCall(ETaskSvStart, iHandle, &s);
	if (r != KErrNone) return r;
	User::WaitForRequest(s);
	return s.Int();
	}

TInt RHwaTask::Suspend()
	{
	TRequestStatus s; 
  	TInt r = iOwningDevice.TaskCall(ETaskSuspend, iHandle, &s);
	if (r != KErrNone) return r;
	User::WaitForRequest(s);
	return s.Int();
	}

TInt RHwaTask::Resume()
	{
	TRequestStatus s; 
  	TInt r = iOwningDevice.TaskCall(ETaskResume, iHandle, &s);
	if (r != KErrNone) return r;
	User::WaitForRequest(s);
	return s.Int();
	}

TInt RHwaTask::InputFrom(const RHwaTask& anOutputTask, TInt anOutputIndex, TInt anInputIndex, TInt aConnectionId)
	{
	TTaskConnectInfoBuf buf; TTaskConnectInfo& info = buf();
	info.iConnectTaskHandle = anOutputTask.iHandle;
	info.iOutputIndex = anOutputIndex;
	info.iInputIndex = anInputIndex;
	info.iConnectionId = aConnectionId;
	return iOwningDevice.SvTaskCall(ETaskSvInputFrom, iHandle, &buf);
	}

TInt RHwaTask::InputConnection(RHwaTask& aTask, TInt anInputIndex, TInt aConnectionId)
	{
	TInt r; TTaskConnectInfo info = {aTask.iHandle, 0, anInputIndex, aConnectionId};
	if ((r = iOwningDevice.TaskCall(ETaskInputConnect, iHandle, &info)) == KErrNone)
		{aTask.iOwningDevice = iOwningDevice; aTask.iHandle = info.iConnectTaskHandle;}
	return r;
	}

TInt RHwaTask::OutputConnection(RHwaTask& aTask, TInt anOutputIndex, TInt aConnectionId)
	{
	TInt r; TTaskConnectInfo info = {aTask.iHandle, anOutputIndex, 0, aConnectionId};
	if ((r = iOwningDevice.TaskCall(ETaskOutputConnect, iHandle, &info)) == KErrNone)
		{aTask.iOwningDevice = iOwningDevice; aTask.iHandle = info.iConnectTaskHandle;}
	return r;
	}

TInt RHwaTask::DisConnectInput(TInt anInputIndex, TInt aConnectionId)
	{
	TTaskConnectInfoBuf buf; TTaskConnectInfo& info = buf();
	info.iConnectTaskHandle = KNullHandle;
	info.iOutputIndex = 0;
	info.iInputIndex = anInputIndex;
	info.iConnectionId = aConnectionId;
	return iOwningDevice.SvTaskCall(ETaskSvDisConnectInput, iHandle, &buf);
	}

TInt RHwaTask::PutData(RTransferBuffer& aBuf, TInt* aBytesTransfered, TInt aTransferId)
	{
	return PutData(aBuf, aBuf.GetBufferSize(), aBytesTransfered, aTransferId);
	}

TInt RHwaTask::PutData(RTransferBuffer& aBuf, TInt aBytesToBeTransfered, TInt* aBytesTransfered, TInt aTransferId)
	{
	TRequestStatus s;
	TTaskDataTfInfo info = TTaskDataTfInfo(&aBuf, &s, aBytesToBeTransfered, aBytesTransfered, aTransferId);
#ifdef GETPUTDATA_ARE_KERNELSERVERCALLS
	TTaskDataTfInfoBuf buf = TTaskDataTfInfoBuf(info); 
	TInt r = iOwningDevice.SvTaskCall(ETaskSvPutData, iHandle, &buf);
#else
	TInt r = iOwningDevice.TaskCall(ETaskSvPutData, iHandle, &info);
#endif
	if (r != KErrNone) return r;
	User::WaitForRequest(s);
	return s.Int();
	}

TInt RHwaTask::PutData(RTransferBuffer& aBuf, TRequestStatus& aStat, TInt* aBytesTransfered, TInt aTransferId)
	{
	return PutData(aBuf, aStat, aBuf.GetBufferSize(), aBytesTransfered, aTransferId);
	}

TInt RHwaTask::PutData(RTransferBuffer& aBuf, TRequestStatus& aStat, TInt aBytesToBeTransfered,
					   TInt* aBytesTransfered, TInt aTransferId)
	{
	TTaskDataTfInfo info = TTaskDataTfInfo(&aBuf, &aStat, aBytesToBeTransfered, aBytesTransfered, aTransferId);
#ifdef GETPUTDATA_ARE_KERNELSERVERCALLS
	TTaskDataTfInfoBuf buf = TTaskDataTfInfoBuf(info); 
	return iOwningDevice.SvTaskCall(ETaskSvPutData, iHandle, &buf);
#else
	return iOwningDevice.TaskCall(ETaskSvPutData, iHandle, &info);
#endif
	}

TInt RHwaTask::PutDataCancel(TInt aTransferId)
	{return iOwningDevice.TaskCall(ETaskPutDataCancel, iHandle, (TAny*) aTransferId);}

TInt RHwaTask::GetData(RTransferBuffer& aBuf, TInt* aBytesTransfered, TInt aTransferId)
	{
	TRequestStatus s; TTaskDataTfInfo info = TTaskDataTfInfo(&aBuf, &s, 0, aBytesTransfered, aTransferId);
#ifdef GETPUTDATA_ARE_KERNELSERVERCALLS
	TTaskDataTfInfoBuf buf = TTaskDataTfInfoBuf(info); 
	TInt r = iOwningDevice.SvTaskCall(ETaskSvGetData, iHandle, &buf);
#else
	TInt r = iOwningDevice.TaskCall(ETaskSvGetData, iHandle, &info);
#endif
	if (r != KErrNone) return r;
	User::WaitForRequest(s);
	return s.Int();
	}

TInt RHwaTask::GetData(RTransferBuffer& aBuf, TRequestStatus& aStat, TInt* aBytesTransfered, TInt aTransferId)
	{
	TTaskDataTfInfo info = TTaskDataTfInfo(&aBuf, &aStat, 0, aBytesTransfered, aTransferId);
#ifdef GETPUTDATA_ARE_KERNELSERVERCALLS
	TTaskDataTfInfoBuf buf = TTaskDataTfInfoBuf(info);
	return iOwningDevice.SvTaskCall(ETaskSvGetData, iHandle, &buf);
#else
	return iOwningDevice.TaskCall(ETaskSvGetData, iHandle, &info);
#endif
	}

TInt RHwaTask::GetDataCancel(TInt aTransferId)
	{
	return iOwningDevice.TaskCall(ETaskGetDataCancel, iHandle, (TAny*) aTransferId);
	}

TInt RHwaTask::InputBufferSize(TInt& aSize)
	{
	return iOwningDevice.TaskCall(ETaskInputBufferSize, iHandle, &aSize);
	}

TInt RHwaTask::OutputBufferSize(TInt& aSize)
	{
	return iOwningDevice.TaskCall(ETaskOutputBufferSize, iHandle, &aSize);
	}

TInt RHwaTask::SendMessage(TDesC8& aMessage)
	{
	TRequestStatus s; TTaskSendMsgInfo info = {&s, &aMessage};
	TInt r = iOwningDevice.TaskCall(ETaskSendMessage, iHandle, &info);
	if (r != KErrNone) return r;
	User::WaitForRequest(s);
	return s.Int();
	}

TInt RHwaTask::SendMessage(TRequestStatus& aStatus, TDesC8& aMessage)
	{
	TTaskSendMsgInfo info = {&aStatus, &aMessage};
	return iOwningDevice.TaskCall(ETaskSendMessage, iHandle, &info);
	}

TInt RHwaTask::GetMessage(TDes8& aMessage)
	{
	TRequestStatus s; TTaskGetMsgInfo info = {&s, &aMessage};
	TInt r = iOwningDevice.TaskCall(ETaskGetMessage, iHandle, &info);
	if (r != KErrNone) return r;
	User::WaitForRequest(s);
	return s.Int();
	}

TInt RHwaTask::GetMessage(TRequestStatus& aStatus, TDes8& aMessage)
	{
	TTaskGetMsgInfo info = {&aStatus, &aMessage};
	return iOwningDevice.TaskCall(ETaskGetMessage, iHandle, &info);
	}

// class TTaskCreateInfo

TTaskCreateInfo::TTaskCreateInfo()
	: iTaskId(TUid::Null()), iCodeBuffer(NULL), iArgumentBuffer(NULL), iFlagsWord(0), iNumWindows(0)
	{}

TTaskCreateInfo::TTaskCreateInfo(TUid aTaskId, TDesC8* aCodeBuffer, TDesC8* anArgumentBuffer, TInt aFlagsWord,
								 TInt aNumWindows)
	: iTaskId(aTaskId), iCodeBuffer(aCodeBuffer), iArgumentBuffer(anArgumentBuffer), iFlagsWord(aFlagsWord),
	  iNumWindows(aNumWindows)
	{}

// class TTaskDataTfInfo

TTaskDataTfInfo::TTaskDataTfInfo()
	: iBuf(NULL), iStat(0), iBytesToBeTransfered(0), iBytesTransfered(0), iTransferId(KTfBufIdNull)
	{}

TTaskDataTfInfo::TTaskDataTfInfo(RTransferBuffer* aBuf, TRequestStatus* aStat, TInt aBytesToBeTransfered,
								 TInt* aBytesTransfered, TInt aTransferId)
	: iBuf(aBuf), iStat(aStat), iBytesToBeTransfered(aBytesToBeTransfered), iBytesTransfered(aBytesTransfered),
	  iTransferId(aTransferId)
	{}

