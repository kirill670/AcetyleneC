// P32PCCD.INL
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//


// Class DPcCardSocket
inline TPccdSocketStatus DPcCardSocket::SocketStatus()
	{return(iStatus);}

// Class DPcCardSocket
inline TInt DPcCardSocket::CardFuncCount()
	{return(iCardFuncArray.Count());}

// Class DPcCardSocket
inline TBool DPcCardSocket::IsValidCardFunc(TInt aCardFunc)
	{return(aCardFunc<CardFuncCount());}

// Class DPcCardSocket
inline TBool DPcCardSocket::IsVerified()
	{return(CardFuncCount()>0);}

// Class DPcCardSocket
inline TBool DPcCardSocket::IsMultiFuncCard()
	{return(CardFuncCount()>1);}

// Class DPcCardSocket
inline TInt DPcCardSocket::Number()
	{return(iSocketNum);}

// Class TPcCardFunction
inline void TPcCardFunction::SetConfigBaseAddr(TUint32 anAddr)
	{iConfigBaseAddr=anAddr;}

// Class TPcCardFunction
inline void TPcCardFunction::SetConfigRegMask(TInt aMask)
	{iConfigRegMask=aMask;}

// Class TPcCardFunction
inline void TPcCardFunction::SetFuncType(TPccdFuncType aType)
	{iFuncType=aType;}

// Class TPcCardFunction
inline TPccdFuncType TPcCardFunction::FuncType()
	{return(iFuncType);}

// Class TPcCardFunction
inline TInt TPcCardFunction::ConfigOption()
	{return(iConfigIndex);}

// Class TPcCardFunction
inline TBool TPcCardFunction::IsConfigured()
	{return(iConfigIndex!=KInvalidConfOpt);}

// Class TPcCardFunction
inline TBool TPcCardFunction::IsConfiguredByClient(CBase *aClientID)
	{return(IsConfigured()&&iClientID==aClientID);}

// Class TPcCardFunction
inline TBool TPcCardFunction::IsRestorableConfig()
	{return(iConfigFlags&KPccdConfigRestorable);}

// Class TPcCardFunction
inline TBool TPcCardFunction::ConfigOverridesNormalPwrEvents()
	{return(iConfigFlags&KPccdConfigOverrideNormalPwrEvents);}

// Class TPcCardFunction
inline TUint32 TPcCardFunction::InitCisOffset()
	{return(iInitCisOffset);}

// Class TPcCardFunction
inline TPccdMemType TPcCardFunction::InitCisMemType()
	{return(iInitCisMemType);}

// Class TPcCardVcc
inline void TPcCardVcc::SetVoltage(TPccdSocketVcc aVoltage)
	{iVoltageSetting=aVoltage;}

// Class TPcCardVcc
inline TPccdSocketVcc TPcCardVcc::VoltageSetting()
	{return(iVoltageSetting);}

// Class TPcCardVcc
inline TBool TPcCardVcc::IsOverrideNormalPwrEvents()
	{return(iFlags&KPccdConfigOverrideNormalPwrEvents);}

// Class RPccdChunkBase
inline TUint32 RPccdChunkBase::BaseAddr()
	{return(iChnk.iMemBaseAddr);}

// Class RPccdWindow
inline TInt RPccdWindow::Read(TInt aPos,TAny *aPtr,TInt aLength)
	{return(iChunk->Read(aPos+iOffset,aPtr,aLength));}

// Class RPccdWindow
inline TInt RPccdWindow::Write(TInt aPos,const TAny *aPtr,TInt aLength)
	{return(iChunk->Write(aPos+iOffset,aPtr,aLength));}

// Class RPccdWindow
inline TInt RPccdWindow::ReadByteMultiple(TInt aPos,TAny *aPtr,TInt aCount)
	{return(iChunk->ReadByteMultiple(aPos+iOffset,aPtr,aCount));}

// Class RPccdWindow
inline TInt RPccdWindow::WriteByteMultiple(TInt aPos,const TAny *aPtr,TInt aCount)
	{return(iChunk->WriteByteMultiple(aPos+iOffset,aPtr,aCount));}

// Class RPccdWindow
inline TInt RPccdWindow::ReadHWordMultiple(TInt aPos,TAny *aPtr,TInt aCount)
	{return(iChunk->ReadHWordMultiple(aPos+iOffset,aPtr,aCount));}

// Class RPccdWindow
inline TInt RPccdWindow::WriteHWordMultiple(TInt aPos,const TAny *aPtr,TInt aCount)
	{return(iChunk->WriteHWordMultiple(aPos+iOffset,aPtr,aCount));}

// Class RPccdWindow
inline void RPccdWindow::SetAccessSpeed(TPccdAccessSpeed aSpeed)
	{iAccessSpeed=aSpeed;}

// Class RPccdWindow
inline TBool RPccdWindow::IsPermanent()
	{return(iType&KPccdChunkPermanent);}

// Class RPccdWindow
inline TBool RPccdWindow::IsShareable()
	{return(iType&KPccdChunkShared);}

// Class RPccdWindow
inline TBool RPccdWindow::IsSystemOwned()
	{return(iType&KPccdChunkSystemOwned);}

