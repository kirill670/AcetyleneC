// K32USBC.INL
// Kernel side header for USB device driver.
//
// Copyright (c) 1996-2003 Symbian Ltd.  All rights reserved.
//
#if !defined(__K32USBC_INL__)
#define __K32USBC_INL__


// --- DUsbClientController

void DUsbClientController::Buffer2Setup(const TAny* aBuf, TUsbcSetup& aSetup) const
	{
	aSetup.iRequestType = STATIC_CAST(TUint8*, aBuf)[0];	// TUint8 index
	aSetup.iRequest     = STATIC_CAST(TUint8*, aBuf)[1];
	aSetup.iValue  = SWAP_BYTES_16((STATIC_CAST(TUint16*, aBuf))[1]); // from here: TUint16 index!
	aSetup.iIndex  = SWAP_BYTES_16((STATIC_CAST(TUint16*, aBuf))[2]);
	aSetup.iLength = SWAP_BYTES_16((STATIC_CAST(TUint16*, aBuf))[3]);
	}

void DUsbClientController::SetEp0DataOutVars(const TUsbcSetup& aPacket, const CBase* aClientId)
	{
	iSetup = aPacket;
	iEp0DataReceiving = ETrue;
	iEp0DataReceived = 0;
	iEp0ClientId = aClientId;
	}

void DUsbClientController::ResetEp0DataOutVars()
	{
	iEp0DataReceiving = EFalse;
	iEp0DataReceived = 0;
	iEp0ClientId = NULL;
	}

TUint DUsbClientController::EpIdx2Addr(TUint aRealEndpoint) const
	{
	return ((aRealEndpoint << 7) & 0x80) | ((aRealEndpoint >> 1) & 0x0f);
	}
TUint DUsbClientController::EpAddr2Idx(TUint aAddress) const
	{
	return ((aAddress & 0x80) >> 7) | ((aAddress & 0x0f) << 1);
	}

TBool DUsbClientController::InterfaceExists(TInt aNumber) const
	{
	const TInt num_ifcsets = iConfigs[0]->iInterfaceSets.Count();
	for (TInt i = 0; i < num_ifcsets; ++i)
		{
		if ((iConfigs[0]->iInterfaceSets[i]->iInterfaceNumber) == aNumber)
			{
			return ETrue;
			}
		}
	return EFalse;
	}

TBool DUsbClientController::EndpointExists(TUint aAddress) const
	{
	// Ep0 doesn't have a "logical Ep" pointer (there's no virtual endpoint zero):
	// that's why this pointer being non-Null is not a sufficient criterion for endpoint-existence.
	// (Apart from that, Ep0 always exists.)
	const TInt idx = EpAddr2Idx(aAddress);
	return ((idx < iDeviceTotalEndpoints) &&
			((iRealEndpoints[idx].iLEndpoint != NULL) ||
			 ((aAddress & KUsbEpAddress_Portmask) == 0)));
	}

const TUsbcConfiguration* DUsbClientController::CurrentConfig() const
	{
	if (iCurrentConfig == 0)
		{
		return NULL;
		}
	return iConfigs[iCurrentConfig - 1];
	}

TUsbcConfiguration* DUsbClientController::CurrentConfig()
	{
	if (iCurrentConfig == 0)
		{
		return NULL;
		}
	return iConfigs[iCurrentConfig - 1];
	}

TBool DUsbClientController::IsInTheStatusList(const TUsbcStatusCallBack& aCallBack)
	{
	TSglQueIter<TUsbcStatusCallBack> iter(iStatusCallbacks);
	TUsbcStatusCallBack* p;
	while ((p = iter++) != NULL)
		{
		if (p == &aCallBack)
			return ETrue;
		}
	return EFalse;
	}

TBool DUsbClientController::IsInTheEpStatusList(const TUsbcEndpointStatusCallBack& aCallBack)
	{
	TSglQueIter<TUsbcEndpointStatusCallBack> iter(iEpStatusCallbacks);
	TUsbcEndpointStatusCallBack* p;
	while ((p = iter++) != NULL)
		{
		if (p == &aCallBack)
			return ETrue;
		}
	return EFalse;
	}

TBool DUsbClientController::IsInTheRequestList(const TUsbcRequestCallBack& aCallBack)
	{
	TSglQueIter<TUsbcRequestCallBack> iter(iRequestCallbacks);
	TUsbcRequestCallBack* p;
	while ((p = iter++) != NULL)
		{
		if (p == &aCallBack)
			return ETrue;
		}
	return EFalse;
	}

// --- Misc

void TUsbcEndpointStatusCallBack::SetState(TUint aState)
	{
	iState = aState;
	}

TUint TUsbcEndpointStatusCallBack::State() const
	{
	return iState;
	}

void TUsbcStatusCallBack::SetState(TUsbcDeviceState aState)
	{
	for (TInt i = 0; i < KUsbcDeviceRequests; ++i)
		{
		if (iState[i] == EUsbcNoState)
			{
			iState[i] = aState;
			return;
			}
		}
//	Kern::Printf(_L("Error: KUsbcDeviceRequests too small!"));
	}

TUsbcDeviceState TUsbcStatusCallBack::State(TInt aIndex) const
	{
	if (aIndex >= 0 && aIndex < KUsbcDeviceRequests)
		{
		return iState[aIndex];
		}
	else
		{
//		Kern::Printf(_L("Error: aIndex too large (%d)!"), aIndex);
		return EUsbcNoState;
		}
	}

void TUsbcStatusCallBack::ResetState()
	{
	for (TInt i = 0; i < KUsbcDeviceRequests; ++i)
		{
		iState[i] = EUsbcNoState;
		}
	}

void TUsbcRequestCallBack::SetCount(TInt aCount)
	{
	iCount = aCount;
	}

void TUsbcRequestCallBack::SetBufferInfo(TUint8* aBufferStart,TInt aLength )
	{
	iLength = aLength;
	iBufferStart = aBufferStart;
	}

const TUsbcInterface* TUsbcInterfaceSet::CurrentInterface() const
	{
	return iInterfaces[iCurrentInterface];
	}

TUsbcInterface* TUsbcInterfaceSet::CurrentInterface()
	{
	return iInterfaces[iCurrentInterface];
	}

// --- LDD

TInt TDmaBuf::RxBytesAvailable() const
	{return iRxBytesAvailable;}

TInt TDmaBuf::AdvanceIndex(TInt aIndex) const
	{
	return (aIndex+1)%iPacketArraySize;
	}

TUsbcEndpointInfo* TUsbcEndpoint::EndpointInfo()
	{return &iEndpointInfo;}

TInt TUsbcEndpoint::RxBytesAvailable() const
	{return iDmaBuffers->RxBytesAvailable();}

TInt TUsbcEndpoint::BufferSize() const
	{return iDmaBuffers->BufferSize();}

TUint8* TUsbcEndpoint::SetBufferBase(TUint8* aBase)
	{return iDmaBuffers->SetBufferBase(aBase);}

void TUsbcEndpoint::SetTransferInfo(TEndpointTransferInfo* aTransferInfo)
	{
	iTransferInfo=*aTransferInfo;
	iBytesTransferred=0;
	}

void TUsbcEndpoint::ResetTransferInfo()
	{
 	iTransferInfo.iDes=NULL;
	iTransferInfo.iTransferType=ETransferTypeNone;
	iTransferInfo.iTransferSize=0;
	iTransferInfo.iZlpReqd=EFalse;
	iBytesTransferred=0;
	}

void TUsbcEndpoint::SetClientReadPending(TBool aVal)
	{
	iClientReadPending=aVal;
	}

TBool TUsbcEndpoint::ClientReadPending()
	{
	return iClientReadPending;
	}

void TUsbcEndpoint::SetClientWritePending(TBool aVal)
	{
	iClientWritePending=aVal;
	}

TBool TUsbcEndpoint::ClientWritePending()
	{
	return iClientWritePending;
	}


#endif // __K32USBC_INL__
