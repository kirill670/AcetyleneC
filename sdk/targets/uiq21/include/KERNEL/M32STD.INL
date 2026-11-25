// M32STD.INL
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//


// class THardwareVariant
inline THardwareVariant::THardwareVariant()
	{iVariant=0x01000000;}
inline THardwareVariant::THardwareVariant(TUint aVariant)
	{iVariant=aVariant;}
inline THardwareVariant::operator TUint()
	{return iVariant;}
inline TUint THardwareVariant::Layer()
	{return iVariant>>24;}
inline TUint THardwareVariant::Parent()
	{return (iVariant>>16)&0xff;}
inline TUint THardwareVariant::VMask()
	{return iVariant&0xffff;}
inline TBool THardwareVariant::IsIndependent()
	{return (Layer()<=3);}
inline TBool THardwareVariant::IsCpu()
	{return (Parent()==3);}
inline TBool THardwareVariant::IsCompatibleWith(TUint aCpu, TUint aAsic, TUint aVMask)
	{ return(Layer()<=3 || (Parent()==3 && Layer()==aCpu) ||
		(Layer()==aAsic && (VMask() & aVMask)!=0) );}

// class TInterrupt
inline TBool TInterrupt::Enabled()
	{ return iEnabled; }

// class TDmaInterrupt
inline TDmaInterrupt::TDmaInterrupt(TDma *aDma)
	 : iDma(aDma) {}

// class TDma
inline TInt TDma::Channel()
	{ return iChannel; }
inline Dma::TDmaDevice TDma::DmaDevice()
	{ return iDevice; }

// Class DPlatThread
inline TThreadStatus DPlatThread::Status()
	{return((TThreadStatus)iStatus);}
inline void DPlatThread::SetStatus(TThreadStatus aStatus)
	{iStatus=(TInt8)aStatus;}
inline void DPlatThread::SetWaitingMutex(DPlatMutex *aMutex)
	{iWaitingSemMutx=(DPlatSemaphore *)aMutex;}
inline void DPlatThread::SetWaitingSemaphore(DPlatSemaphore *aSemaphore)
	{iWaitingSemMutx=aSemaphore;}

// Class DPlatProcess
inline TInt DPlatProcess::BeingCreated()
	{return(iAttributes&EBeingLoaded);}

// Class DPlatMutex
inline DPlatThread *DPlatMutex::HoldingThread()
    {return iHoldingThread;}
//
inline const TRomHeader &TheRomHeader()
	{return(*((const TRomHeader *)KRomHeaderLinAddr));}
inline const TRomEntry &RomEntry(TLinAddr anAddr)
	{return(*((const TRomEntry *)anAddr));}
inline const TRomImageHeader& RomImageHeader(TLinAddr anAddr)
	{return(*((const TRomImageHeader*)anAddr));}
inline void ReScheduleNeeded()
	{ReScheduleNeededFlag=ETrue;}
inline void ExecMutate()
	{ExecMutateFlag=ETrue;}
//
inline Custom* A::Variant()
    {return(A::TheVariant);}
//
