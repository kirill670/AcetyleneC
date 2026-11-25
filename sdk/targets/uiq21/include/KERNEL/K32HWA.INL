// K32HWA.INL
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

// class THwaTaskHwInterface

THwaTaskHwInterface::THwaTaskHwInterface(DHwaTask* anOwningTask)
	: iOwningTask(anOwningTask), iPriority(KHwaTaskPriorityNormal)
	{}


// class THwaDataTfReq

DTransferBuffer* THwaDataTfReq::Buffer()
	{return iBuf;}

TInt THwaDataTfReq::BytesToBeTransfered()
	{return iBytesToBeTransfered;}

THwaDataTfDir THwaDataTfReq::Direction()
	{return iDir;}

TInt THwaDataTfReq::TransferId()
	{return iTransferId;}

void THwaDataTfReq::Complete(TInt aReason, TInt aBytesTransfered)
	{iCompletionReason = aReason; iBytesTransfered = aBytesTransfered; Kern::Add(iCompleteDfc);}

void THwaDataTfReq::DoComplete(TInt aReason, TInt aBytesTransfered)
	{
	if (iTransferLengthAddress)
		iOwningThread->Write(iTransferLengthAddress, (TUint8*) &aBytesTransfered, sizeof(TInt));
	iOwningThread->RequestComplete(iStatus, aReason);
	iOwningTask->iDataTfReqs.Remove(*this);
	iOwningTask->iFreeTfSlots.AddLast(*this);
	}


// class THwaTaskConnection

DHwaTask* THwaTaskConnection::ConnectedTask() const
	{return iConnectedTask;}

TInt THwaTaskConnection::ConnectionId() const
	{return iConnectionId;}

TInt THwaTaskConnection::Index() const
	{return iIndex;}

TInt THwaTaskConnection::PeerIndex() const
	{return iPeerIndex;}


// class DHwaTask

THwaTaskStatus DHwaTask::Status()
	{return iStatus;}

TUid DHwaTask::TaskId()
	{return iTaskId;}

DHwaDevice* DHwaTask::OwningDevice()
	{return iOwningDevice;}

DHwaDevicePdd* DHwaTask::OwningDevicePdd()
	{return iOwningDevice->DevicePdd();}

DThread* DHwaTask::OwningThread()
	{return iOwningThread;}

void DHwaTask::ResourcesRequired(TDes8& aResourcesRequired)
	{iHwInterface->ResourcesRequired(aResourcesRequired);}

void DHwaTask::CompleteLogon(TInt aReason)
	{
	if (aReason == KErrTaskMessageReceived &&
		iLogonRequestFlags & KNoMessageNotification)
		return;
	iLogonCompletionReason = aReason;
	Kern::Add(iLogonCompleteDfc);
	}

void DHwaTask::LogonComplete(TInt aReason)
	{
	if (iLogonRequestStatus)
		iOwningThread->RequestComplete(iLogonRequestStatus, aReason);
	}

void DHwaTask::CreateComplete(TInt aResult)
	{
	if (iCreateRequestStatus)
		iOwningThread->RequestComplete(iCreateRequestStatus, aResult);
	}

void DHwaTask::CloseComplete(TInt aResult)
	{
	if (iCloseRequestStatus)
		if (iClosingThread)
			iClosingThread->RequestComplete(iCloseRequestStatus, aResult);
	}

void DHwaTask::SendMessageComplete(TInt aResult)
	{
	if (iSendMsgRequestStatus)
		iOwningThread->RequestComplete(iSendMsgRequestStatus, aResult);
	}

void DHwaTask::GetMessageComplete(TInt aResult)
	{
	if (iGetMsgRequestStatus)
		iOwningThread->RequestComplete(iGetMsgRequestStatus, aResult);
	}

void DHwaTask::ProcessComplete(TInt aResult)
	{
	if (iProcessRequestStatus)
		if (iProcessThread)
			iProcessThread->RequestComplete(iProcessRequestStatus, aResult);
	}

void DHwaTask::SetPriorityComplete(TInt aResult)
	{ProcessComplete(aResult);}

void DHwaTask::StartComplete(TInt aResult)
	{ProcessComplete(aResult);}

void DHwaTask::SuspendComplete(TInt aResult)
	{ProcessComplete(aResult);}

void DHwaTask::ResumeComplete(TInt aResult)
	{ProcessComplete(aResult);}

TBool DHwaTask::TransferRequestPending(THwaDataTfDir /*aDir*/)
	{return !iDataTfReqs.IsEmpty();}

DHwaTask* DHwaTask::GetInputTask(TInt anIndex, TInt aConnectionId)
	{
	THwaTaskConnection* tc;
	return ((tc = GetConnection(iInputConnections, anIndex, aConnectionId)) != NULL) ?
		tc->iConnectedTask : NULL;
	}

DHwaTask* DHwaTask::GetOutputTask(TInt anIndex, TInt aConnectionId)
	{
	THwaTaskConnection* tc;
	return ((tc = GetConnection(iOutputConnections, anIndex, aConnectionId)) != NULL) ?
		tc->iConnectedTask : NULL;
	}

void DHwaTask::Panic(const TDesC& aCategory, TInt aReason)
	{iOwningThread->Panic(aCategory, aReason);}

DTransferWindow* DHwaTask::Window(TInt anIndex)
	{
	if (anIndex >= iNumWindows)
		return NULL;
	return iWindows[anIndex];
	}

void DHwaTask::GetBufferInfo(TDes8& aBufferInfo)
	{iHwInterface->GetBufferInfo(aBufferInfo);}


// class DHwaDevicePdd

DHwaDevicePdd::DHwaDevicePdd()
	: iLdd(NULL), iStatus(EHwaDevUnknown)
	{}


// class DHwaDevice

void DHwaDevice::SetStatus(THwaDeviceStatus aStatus)
	{iPdd->iStatus = aStatus;}

THwaDeviceStatus DHwaDevice::Status()
	{return iPdd->iStatus;}

TInt DHwaDevice::DeviceId()
	{return iDeviceId;}

DHwaDevicePdd* DHwaDevice::DevicePdd()
	{return iPdd;}

DThread* DHwaDevice::OwningThread()
	{return iThread;}

DHwaTask* DHwaDevice::Task(TInt aHandle)
	{return static_cast<DHwaTask*>(iTaskIx->At(aHandle));}

