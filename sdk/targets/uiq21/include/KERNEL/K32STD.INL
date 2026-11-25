// K32STD.INL
//
// Copyright (c) 1994-1999 Symbian Ltd.  All rights reserved.
//


// CLass TSvrMessage
inline TInt TSvrMessage::Function() const
	{return iFunction;}
inline TInt TSvrMessage::Int0() const
	{return iArgs[0];}
inline TInt TSvrMessage::Int1() const
	{return iArgs[1];}
inline TInt TSvrMessage::Int2() const
	{return iArgs[2];}
inline TInt TSvrMessage::Int3() const
	{return iArgs[3];}
inline const TAny* TSvrMessage::Ptr0() const
	{return (const TAny*)iArgs[0];}
inline const TAny* TSvrMessage::Ptr1() const
	{return (const TAny*)iArgs[1];}
inline const TAny* TSvrMessage::Ptr2() const
	{return (const TAny*)iArgs[2];}
inline const TAny* TSvrMessage::Ptr3() const
	{return (const TAny*)iArgs[3];}
inline DThread* TSvrMessage::Client() const
	{return iClient;}
inline void TSvrMessage::Complete(TInt aReason) const
	{iClient->SupervisorComplete(aReason);}

// Class TDfc
inline void TDfc::Deque()
	{iNext->iPrev=iPrev; iPrev->iNext=iNext; iNext=NULL;}
inline TBool TDfc::Queued()
	{ return(iNext!=NULL); }
inline void TDfc::CallBack() const
	{iCallBack.CallBack();}

// class TDfcQue
inline TBool TDfcQue::IsEmpty()
	{ return(iFirst==(TDfc*)&iFirst); }

// Class DChunk
inline DProcess* DChunk::OwningProcess() const
	{return(iOwningProcess);}
inline TInt DChunk::Size() const
	{return(iSize);}
inline TInt DChunk::MaxSize() const
	{return(iMaxSize);}
inline TUint8 *DChunk::Base() const
	{return(iBase);}
inline void DChunk::SetHeapInfo(TInt aHeapOffset, TInt aRunAddress)
	{iHeapOffset=aHeapOffset;iHeapRunAddress=aRunAddress;}
inline TInt DChunk::HeapOffset()
	{return(iHeapOffset);}
inline TInt DChunk::Bottom() const
	{return(iStartPos);}
inline TInt DChunk::Top() const
	{return(iStartPos+iSize);}

// Class DSemaphore
inline TInt DSemaphore::Count() const
	{return(iCount);}

// Class DMutex
inline TInt DMutex::Count() const
	{return(iCount);}

// Class DThread
inline DProcess& DThread::OwningProcess()
	{return(*iOwningProcess);}
inline CObjectIx &DThread::Handles()
	{return(*iHandles);}

// Class DProcess
inline CObjectIx &DProcess::Handles()
	{return(*iHandles);}

// Class DCleanup
inline DCleanup::TCleanupType DCleanup::Type()
	{return(iType);}

// Class DLogicalChannel
inline DLogicalDevice *DLogicalChannel::Device()
	{return(iDevice);}
inline TBool DLogicalChannel::IsPending(TInt aReqNo) const
	{return(iRequestStatus[aReqNo]!=NULL);}

// Class DLogicalDevice
inline DLibrary *DLogicalDevice::Library()
	{return(iLibrary);}

// Class DPhysicalDevice
inline DLibrary *DPhysicalDevice::Library()
	{return(iLibrary);}

// Class DMedia
inline DMedia::TMediaStatus DMedia::Status()
	{return(iStatus);}
inline TInt64 DMedia::MediaLenInBytes()
	{return(iPartitionInfo.iMediaSizeInBytes);}
inline void DMedia::SetStatus(TMediaStatus aStatus)
	{iStatus=aStatus;}
inline TMediaDevice DMedia::DeviceType()
	{return(iDevice);}
inline TInt DMedia::PartitionCount() 
	{return(iPartitionInfo.iPartitionCount);}
inline TInt64 DMedia::PartitionBaseAddr(TInt aPartition)
	{return(iPartitionInfo.iEntry[aPartition].iPartitionBaseAddr);}
inline TInt64 DMedia::PartitionLen(TInt aPartition)
	{return(iPartitionInfo.iEntry[aPartition].iPartitionLen);}

// Class TDriveChangedFlags
inline TBool TDriveChangedFlags::IsMatchingEntry(DThread* aThread,TInt* aMountStatus)
    {return(iOwningThread==aThread && iMountStatus==aMountStatus);}
inline void TDriveChangedFlags::SetOpenRequestPending()
    {iOpenReqPending=ETrue;}
inline TBool TDriveChangedFlags::IsOpenRequestPending()
    {return(iOpenReqPending);}
inline TInt TDriveChangedFlags::DriveNumber()
    {return(iDriveNum);}

// Class DMediaDriver
inline TBool DMediaDriver::IsPending(TInt aReqNo) const
	{return(iReqStat[aReqNo]!=NULL);}
inline TBool DMediaDriver::AnyPending() const
	{return(iReqStat[0]||iReqStat[1]||iReqStat[2]);}

// Class DMediaChangeNotifierBase
inline void DMediaChangeNotifierBase::SignalMediaChange()
	{iThread->RequestComplete(iReqStat,KErrNone);}
inline TBool DMediaChangeNotifierBase::IsCallBackActive()
	{return(iReqStat!=NULL&&iThread!=NULL);}

// Class DTransferBuffer
inline TTransferBufferType DTransferBuffer::BufferType() const
	{return(iBufferType);}
inline TInt DTransferBuffer::BufferSize() const
	{return(iBufferSize);}

// Miscellaneous
#if defined __WINS__
inline TSuperPage &TheSuperPage()
	{return TheWinsSuperPage;}
inline TKernelPage &TheKernelPage()
	{return TheWinsKernelPage;}
inline TMachineConfiguration &TheMachineConfiguration()
	{return TheWinsMachineConfiguration;}
#else
inline TSuperPage &TheSuperPage()
	{return *(TSuperPage *)KSuperPageLinAddr;}
inline TKernelPage &TheKernelPage()
	{return *(TKernelPage *)(KSuperPageLinAddr+KKilo);}
inline TMachineConfiguration &TheMachineConfiguration()
	{return *(TMachineConfiguration *)(KSuperPageLinAddr+2*KKilo);}
#endif
