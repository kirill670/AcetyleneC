// K32COMM.INL
//
// Copyright (c) 1996-1999 Symbian Ltd.  All rights reserved.
//


inline TBool DComm::PowerGood()
	{ return(iLdd->PowerGood()); }

inline void DComm::SetCurrent(TInt aCurrent)
	{ iLdd->SetCurrentConsumptionInMilliAmps(aCurrent); }

inline void DComm::ReceiveIsr(TUint aChar)
	{ iLdd->ReceiveIsr(aChar); }

inline TInt DComm::TransmitIsr()
	{ return iLdd->TransmitIsr(); }

inline void DComm::StateIsr(TUint aStatus)
	{ iLdd->StateIsr(aStatus); }

inline TBool DComm::Transmitting()
	{ return iTransmitting; }

inline TBool DCommDCE::PowerGood()
	{ return(iLdd->PowerGood()); }

inline void DCommDCE::SetCurrent(TInt aCurrent)
	{ iLdd->SetCurrentConsumptionInMilliAmps(aCurrent); }

inline void DCommDCE::ReceiveIsr(TUint aChar)
	{ iLdd->ReceiveIsr(aChar); }

inline TInt DCommDCE::TransmitIsr()
	{ return iLdd->TransmitIsr(); }

inline void DCommDCE::StateIsr(TUint aStatus)
	{ iLdd->StateIsr(aStatus); }

inline TBool DCommDCE::Transmitting()
	{ return iTransmitting; }

//
// Texas Instruments 19/03/2001 : Adding Comm PDD for DMA transfer support
//

inline TBool DCommDMA::PowerGood()
	{ return(iLdd->PowerGood()); }

inline void DCommDMA::SetCurrent(TInt aCurrent)
	{ iLdd->SetCurrentConsumptionInMilliAmps(aCurrent); }

inline void DCommDMA::ReceiveIsr(TUint aChar)
	{ iLdd->ReceiveIsr(aChar); }

inline TInt DCommDMA::TransmitIsr()
	{ return iLdd->TransmitIsr(); }

inline void DCommDMA::StateIsr(TUint aStatus)
	{ iLdd->StateIsr(aStatus); }

inline TBool DCommDMA::Transmitting()
	{ return iTransmitting; }

inline TBool DChannelComm::AreAnyPending() const
// Return TRUE if any requests are pending.
	{ return(iRxDesPtr || iTxDesPtr); }

inline TBool DChannelComm::IsTerminator(TUint8 aChar)
	{ return (iTerminatorMask[aChar>>3]&(1<<(aChar&7))); }

inline void DChannelComm::SetTerminator(TUint8 aChar)
	{ iTerminatorMask[aChar>>3] |= (1<<(aChar&7)); }

inline TInt DChannelComm::RxCount()
	{ TInt r=iRxPutIndex-iRxGetIndex; return(r>=0 ? r : r+iRxBufSize); }

inline TInt DChannelComm::TxCount()
	{ TInt r=iTxPutIndex-iTxGetIndex; return(r>=0 ? r : r+iTxBufSize); }

inline void DChannelComm::EnableTransmit()
	{ iPdd->EnableTransmit(); }

inline TInt DChannelComm::DisableIrqs()
	{ return iPdd->DisableIrqs(); }

inline void DChannelComm::RestoreIrqs(TInt aIrq)
	{ iPdd->RestoreIrqs(aIrq); }

inline TInt DChannelComm::IsLineFail(TUint aFailSignals)
    { return(~iSignals & aFailSignals); }

inline void DChannelComm::SetStatus(TState aStatus)
	{ iStatus=aStatus; }

inline void DChannelComm::CompleteAllReqs(TInt aReason)
	{ DLogicalChannel::CompleteAll(aReason); }

inline void DChannelComm::SetCurrentConsumptionInMilliAmps(TInt aValue)
	{ iPowerHandler->SetCurrentConsumptionInMilliAmps(aValue); }

inline TBool DChannelComm::PowerGood()
	{ return iPowerHandler->PowerGood(); }

inline TBool DChannelCommDCE::AreAnyPending() const
// Return TRUE if any requests are pending.
	{ return(iRxDesPtr || iTxDesPtr); }

inline TBool DChannelCommDCE::IsTerminator(TUint8 aChar)
	{ return (iTerminatorMask[aChar>>3]&(1<<(aChar&7))); }

inline void DChannelCommDCE::SetTerminator(TUint8 aChar)
	{ iTerminatorMask[aChar>>3] |= (1<<(aChar&7)); }

inline TBool DChannelCommDCE::ConfigDetection()
	{ return iConfigDetection; }

inline TInt DChannelCommDCE::RxCount()
	{ TInt r=iRxPutIndex-iRxGetIndex; return(r>=0 ? r : r+iRxBufSize); }

inline TInt DChannelCommDCE::TxCount()
	{ TInt r=iTxPutIndex-iTxGetIndex; return(r>=0 ? r : r+iTxBufSize); }

inline void DChannelCommDCE::EnableTransmit()
	{ iPdd->EnableTransmit(); }

inline TInt DChannelCommDCE::DisableIrqs()
	{ return iPdd->DisableIrqs(); }

inline void DChannelCommDCE::RestoreIrqs(TInt aIrq)
	{ iPdd->RestoreIrqs(aIrq); }

inline TInt DChannelCommDCE::IsLineFail(TUint aFailSignals)
    { return(~iSignals & aFailSignals); }

inline void DChannelCommDCE::SetStatus(TState aStatus)
	{ iStatus=aStatus; }

inline void DChannelCommDCE::CompleteAllReqs(TInt aReason)
	{ DLogicalChannel::CompleteAll(aReason); }

inline void DChannelCommDCE::SetCurrentConsumptionInMilliAmps(TInt aValue)
	{ iPowerHandler->SetCurrentConsumptionInMilliAmps(aValue); }

inline TBool DChannelCommDCE::PowerGood()
	{ return iPowerHandler->PowerGood(); }

//
// Texas Instruments 19/03/2001 : Adding Comm PDD for DMA transfer support
//
inline TBool DChannelCommDMA::AreAnyPending() const
// Return TRUE if any requests are pending.
	{ return(iRxDesPtr || iTxDesPtr); }

inline TBool DChannelCommDMA::IsTerminator(TUint8 aChar)
	{ return (iTerminatorMask[aChar>>3]&(1<<(aChar&7))); }

inline void DChannelCommDMA::SetTerminator(TUint8 aChar)
	{ iTerminatorMask[aChar>>3] |= (1<<(aChar&7)); }

inline TInt DChannelCommDMA::RxCount()
	{ TInt r=iRxPutIndex-iRxGetIndex; return(r>=0 ? r : r+iRxBufSize); }

inline TInt DChannelCommDMA::TxCount()
	{ TInt r=iTxPutIndex-iTxGetIndex; return(r>=0 ? r : r+iTxBufSize); }

inline void DChannelCommDMA::EnableTransmit()
	{ iPdd->EnableTransmit(); }

inline TInt DChannelCommDMA::DisableIrqs()
	{ return iPdd->DisableIrqs(); }

inline void DChannelCommDMA::RestoreIrqs(TInt aIrq)
	{ iPdd->RestoreIrqs(aIrq); }

inline TInt DChannelCommDMA::IsLineFail(TUint aFailSignals)
    { return(~iSignals & aFailSignals); }

inline void DChannelCommDMA::SetStatus(TState aStatus)
	{ iStatus=aStatus; }

inline void DChannelCommDMA::CompleteAllReqs(TInt aReason)
	{ DLogicalChannel::CompleteAll(aReason); }

inline void DChannelCommDMA::SetCurrentConsumptionInMilliAmps(TInt aValue)
	{ iPowerHandler->SetCurrentConsumptionInMilliAmps(aValue); }

inline TBool DChannelCommDMA::PowerGood()
	{ return iPowerHandler->PowerGood(); }
