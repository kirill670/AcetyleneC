//
//	P32MMC.INL
//	(C) Copyright Symbian Ltd 1999
//

//		Global inline functions

inline TUint32 TMMC::BigEndian32(const TUint8* aPtr)
	{return( (aPtr[0]<<24) | (aPtr[1]<<16) | (aPtr[2]<<8) | (aPtr[3]) );}

inline void TMMC::BigEndian4Bytes(TUint8* aPtr, TUint32 aVal)
	{
	aPtr[0] = (TUint8)((aVal >> 24) & 0xFF);
	aPtr[1] = (TUint8)((aVal >> 16) & 0xFF);
	aPtr[2] = (TUint8)((aVal >> 8) & 0xFF);
	aPtr[3] = (TUint8)(aVal & 0xFF);
	}


//	--------  class TCID  --------

inline TCID::TCID(const TUint8* aPtr)
	{Mem::Copy(&iData[0], aPtr, KMMCCIDLength);}

inline TCID& TCID::operator=(const TCID& aCID)
	{Mem::Copy(&iData[0], &aCID.iData[0], KMMCCIDLength); return(*this);}

inline TCID& TCID::operator=(const TUint8* aPtr)
	{Mem::Copy(&iData[0], aPtr, KMMCCIDLength); return(*this);}

inline TBool TCID::operator==(const TCID& aCID) const
	{return(Mem::Compare(&iData[0],KMMCCIDLength,&aCID.iData[0],KMMCCIDLength)==0);}

inline TBool TCID::operator==(const TUint8* aPtr) const
	{return(Mem::Compare(&iData[0],KMMCCIDLength,aPtr,KMMCCIDLength)==0);}

inline void TCID::Copy(TUint8* aPtr) const
	{Mem::Copy(aPtr, &iData[0], KMMCCIDLength);}

inline TUint8 TCID::At(TUint anIndex) const
	{return(iData[KMMCCIDLength-1-anIndex]);}

//	--------  class TCSD  --------

inline TCSD::TCSD(const TUint8* aPtr)
	{Mem::Copy(&iData[0], aPtr, KMMCCSDLength);}

inline TCSD& TCSD::operator=(const TCSD& aCSD)
	{Mem::Copy(&iData[0], &aCSD.iData[0], KMMCCSDLength); return(*this);}

inline TCSD& TCSD::operator=(const TUint8* aPtr)
	{Mem::Copy(&iData[0], aPtr, KMMCCSDLength); return(*this);}

inline void TCSD::Copy(TUint8* aPtr) const
	{Mem::Copy(aPtr, &iData[0], KMMCCIDLength);}

inline TUint8 TCSD::At(TUint anIndex) const		// anIndex byte in little-endian format
	{return(iData[KMMCCSDLength-1-anIndex]);}

// Raw field accessors.  Encoded values such as memory capacity are calulated in
// non-inline functions defined in ps_mmc.cpp.

inline TUint TCSD::CSDStructure() const		{return( CSDField(127,126) );}
inline TUint TCSD::SpecVers() const			{return( CSDField(125,122) );}
inline TUint TCSD::Reserved120() const		{return( CSDField(121,120) );}
inline TUint TCSD::TAAC() const				{return( CSDField(119,112) );}
inline TUint TCSD::NSAC() const				{return( CSDField(111,104) );}
inline TUint TCSD::TranSpeed() const		{return( CSDField(103,96) );}
inline TUint TCSD::CCC() const				{return( CSDField(95,84) );}
inline TUint TCSD::ReadBlLen() const		{return( CSDField(83,80) );}
inline TBool TCSD::ReadBlPartial() const	{return( CSDField(79,79) );}
inline TBool TCSD::WriteBlkMisalign() const	{return( CSDField(78,78) );}
inline TBool TCSD::ReadBlkMisalign() const	{return( CSDField(77,77) );}
inline TBool TCSD::DSRImp() const			{return( CSDField(76,76) );}
inline TUint TCSD::Reserved74() const		{return( CSDField(75,74) );}
inline TUint TCSD::CSize() const			{return( CSDField(73,62) );}
inline TUint TCSD::VDDRCurrMin() const		{return( CSDField(61,59) );}
inline TUint TCSD::VDDRCurrMax() const		{return( CSDField(58,56) );}
inline TUint TCSD::VDDWCurrMin() const		{return( CSDField(55,53) );}
inline TUint TCSD::VDDWCurrMax() const		{return( CSDField(52,50) );}
inline TUint TCSD::CSizeMult() const		{return( CSDField(49,47) );}

inline TUint TCSD::EraseGrpSize() const		{return( CSDField(46,42) );}
inline TUint TCSD::EraseGrpMult() const		{return( CSDField(41,37) );}
inline TUint TCSD::WPGrpSize() const		{return( CSDField(36,32) );}

inline TBool TCSD::WPGrpEnable() const		{return( CSDField(31,31) );}
inline TUint TCSD::DefaultECC() const		{return( CSDField(30,29) );}
inline TUint TCSD::R2WFactor() const		{return( CSDField(28,26) );}
inline TUint TCSD::WriteBlLen() const		{return( CSDField(25,22) );}
inline TBool TCSD::WriteBlPartial() const	{return( CSDField(21,21) );}
inline TUint TCSD::Reserved16() const		{return( CSDField(20,16) );}
inline TBool TCSD::FileFormatGrp() const	{return( CSDField(15,15) );}
inline TBool TCSD::Copy() const				{return( CSDField(14,14) );}
inline TBool TCSD::PermWriteProtect() const	{return( CSDField(13,13) );}
inline TBool TCSD::TmpWriteProtect() const	{return( CSDField(12,12) );}
inline TUint TCSD::FileFormat() const		{return( CSDField(11,10) );}
inline TUint TCSD::ECC() const				{return( CSDField(9,8) );}
inline TUint TCSD::CRC() const				{return( CSDField(7,1) );}


//	--------  class TMMCStatus  --------

inline TMMCStatus::TMMCStatus(const TUint8* aPtr) : iData(TMMC::BigEndian32(aPtr)) {}
inline TMMCStatus::TMMCStatus(const TUint32& aData) : iData(aData) {}
inline TMMCStatus::operator TUint32() const {return(iData);}
inline TUint32 TMMCStatus::Error() const { return(iData & KMMCStatErrorMask); }
inline TMMCCardStateEnum TMMCStatus::State() const
	{ return((TMMCCardStateEnum)(iData & KMMCStatCurrentStateMask)); }


//	--------  class TMMCArgument  --------
//	--------  class TRCA  --------
//	--------  class TDSR  --------

inline TMMCArgument::TMMCArgument(const TUint32& aData) : iData(aData) {}
inline TMMCArgument::TMMCArgument(TRCA anRCA) : iData(TUint(anRCA)<<16) {}
inline TMMCArgument::TMMCArgument(TDSR aDSR) : iData(TUint(aDSR)<<16) {}
inline TMMCArgument::operator TUint32() const {return(iData);}
inline void TMMCArgument::SetRCA(TRCA anRCA)	{iData=(iData&0xFFFF)|(TUint(anRCA)<<16);}

inline TRCA::TRCA(TUint16 aData) : iData(aData) {}
inline TRCA::TRCA(TInt aData) : iData(static_cast<TUint16>(aData)) {}
inline TRCA::TRCA(TMMCArgument aData) {iData=(TUint16)((TUint32(aData)>>16)&0xFFFF);}
inline TRCA::operator TUint16() const {return(iData);}

inline TDSR::TDSR(TUint16 aData) : iData(aData) {}
inline TDSR::operator TUint16() const {return(iData);}


//	--------  class TMMCCard  --------

inline TBool TMMCCard::IsPresent() const
//
// If the card is present, its index shows the card number + 1
//
	{return( iIndex != 0 );}

inline TInt TMMCCard::Number() const					{return( iIndex - 1 );}
inline TMMCMediaTypeEnum TMMCCard::MediaType() const	{return(iCSD.MediaType());}
inline TUint TMMCCard::DeviceSize() const				{return(iCSD.DeviceSize());}
inline const TCID& TMMCCard::CID() const				{return(iCID);}
inline const TCSD& TMMCCard::CSD() const				{return(iCSD);}
inline TRCA TMMCCard::RCA() const						{return(iRCA);}
inline TBool TMMCCard::HasPassword() const				{return(iFlags&KMMCCardHasPassword);}
inline TBool TMMCCard::IsWriteProtected() const			{return(iFlags&KMMCCardIsWriteProtected);}

//	--------  class TMmcCardArray  --------

inline TUint TMmcCardArray::NewCardCount()
	{return(iNewCardsCount);}
inline TInt TMmcCardArray::CardsPresent()
	{return(iCardsPresent);}
inline TMMCCard* TMmcCardArray::NewCardP(TUint aNewCardNumber)
	{return(iNewCards[aNewCardNumber]);}
inline TMMCCard* TMmcCardArray::CardP(TUint aCardNumber)
	{return(iCards[aCardNumber]);}
inline TMMCCard& TMmcCardArray::NewCard(TUint aCardNumber)
	{return *iNewCards[aCardNumber];}
inline TMMCCard& TMmcCardArray::Card(TUint aCardNumber)
	{return *iCards[aCardNumber];}

//	--------  class TMMCStackConfig  --------

inline TMMCStackConfig::TMMCStackConfig() : iUpdateMask(0), iClientMask(0) {}

inline void TMMCStackConfig::SetMode(TUint32 aMask)
	{iModes |= aMask; iUpdateMask |= aMask;}

inline void TMMCStackConfig::RemoveMode(TUint32 aMask)
	{iModes &= ~aMask; iUpdateMask |= aMask;}

inline void TMMCStackConfig::UseDefault(TUint32 aMask)
	{iUpdateMask &= ~aMask; iClientMask &= ~aMask;}

inline void TMMCStackConfig::SetPollAttempts(TUint aData)
	{iPollAttempts=aData; iClientMask |= KMMCModeClientPollAttempts; }
	
inline void TMMCStackConfig::SetOpCondBusyTimeout(TUint16 aData)
	{iOpCondBusyTimeout=aData; iClientMask |= KMMCModeClientiOpCondBusyTimeout; }
	
inline TInt TMMCStackConfig::OpCondBusyTimeout()
	{return((TInt)iOpCondBusyTimeout);}

inline void TMMCStackConfig::SetTimeOutRetries(TUint aData)
	{iTimeOutRetries=aData; iClientMask |= KMMCModeClientTimeOutRetries; }

inline void TMMCStackConfig::SetCRCRetries(TUint aData)
	{iCRCRetries=aData; iClientMask |= KMMCModeClientCRCRetries; }

inline void TMMCStackConfig::SetBusClockInKhz(TUint aData)
	{iBusConfig.iBusClock=aData; iClientMask |= KMMCModeClientBusClock; }

inline void TMMCStackConfig::SetTicksClockIn(TUint aData)
	{iBusConfig.iClockIn=aData; iClientMask |= KMMCModeClientClockIn; }

inline void TMMCStackConfig::SetTicksClockOut(TUint aData)
	{iBusConfig.iClockOut=aData; iClientMask |= KMMCModeClientClockOut; }

inline void TMMCStackConfig::SetResponseTimeOutInTicks(TUint aData)
	{iBusConfig.iResponseTimeOut=aData; iClientMask |= KMMCModeClientResponseTimeOut; }

inline void TMMCStackConfig::SetDataTimeOutInMcs(TUint aData)
	{iBusConfig.iDataTimeOut=aData; iClientMask |= KMMCModeClientDataTimeOut; }

inline void TMMCStackConfig::SetBusyTimeOutInMcs(TUint aData)
	{iBusConfig.iBusyTimeOut=aData; iClientMask |= KMMCModeClientBusyTimeOut; }


//	--------  class TMMCRCAPool  --------

inline TMMCRCAPool::TMMCRCAPool() : iLocked(0) {}
inline void TMMCRCAPool::LockRCA(TRCA anRCA)	{iLocked |= (1 << (((TUint(anRCA) / 257) - 1) & 31));}
inline void TMMCRCAPool::UnlockRCA(TRCA anRCA)	{iLocked &= ~(1 << (((TUint(anRCA) / 257) - 1) & 31));}
inline void TMMCRCAPool::ReleaseUnlocked()	{iPool = 0;}


//	--------  class TMMCSessRing  --------

inline TBool TMMCSessRing::IsEmpty() const	{return(iSize==0);}
inline void TMMCSessRing::SetMarker()		{iPMark=iPrevP;}
inline void TMMCSessRing::AdvanceMarker()	{if(iPMark != NULL) iPMark=iPMark->iLinkP;}
inline void TMMCSessRing::Point()			{iPoint=((iPrevP=iPMark)==NULL)? NULL : iPMark->iLinkP;}
inline TUint TMMCSessRing::Size() const				{return(iSize);}
inline TMMCSessRing::operator DMMCSession*() const	{return(iPoint);}


//	--------  class TMMCStateMachine  --------

inline TMMCErr TMMCStateMachine::ExitCode()				{ return(iExitCode); }
inline TMMCErr TMMCStateMachine::SetExitCode(TMMCErr aCode) {TMMCErr r=iExitCode; iExitCode=aCode; return(r);}
inline TUint TMMCStateMachine::State()					{ return(iStack[iSP].iState); }
inline TMMCErr TMMCStateMachine::SetState(TUint aState)	{ iStack[iSP].iState=aState; return(0); }
inline void TMMCStateMachine::SuppressSuspension()		{ iSuspend = EFalse; }
inline void TMMCStateMachine::SetTraps(TMMCErr aMask)	{ iStack[iSP].iTrapMask=aMask; }
inline void TMMCStateMachine::ResetTraps()				{ iStack[iSP].iTrapMask=0; }
inline void TMMCStateMachine::Abort()					{ iAbort=ETrue; }
inline void TMMCStateMachine::Setup(TMMCErr (*anEntry)(TAny*), TAny* aContextP)
	{iContextP = aContextP; iStack[0].iFunction = anEntry; Reset();}
inline TMMCErr TMMCStateMachine::Pop(TBool aSuspend)
	{iSP--; if(!aSuspend) iSuspend = EFalse; return( 0 );}
inline TMMCErr TMMCStateMachine::PushMe()				{return(Push(iStack[iSP].iFunction,ETrue));}


//	--------  class DMMCSession  --------

inline void DMMCSession::SetStack(DMMCStack* aStackP)	{iStackP = aStackP;}
inline void DMMCSession::SetupCIMUpdateAcq()			{iSessionID = ECIMUpdateAcq;}
inline void DMMCSession::SetupCIMInitStack()			{iSessionID = ECIMInitStack;}
inline void DMMCSession::SetupCIMCheckStack()			{iSessionID = ECIMCheckStack;}
inline void DMMCSession::SetupCIMSetupCard()			{iSessionID = ECIMSetupCard;}
inline void DMMCSession::SetupCIMLockStack()			{iSessionID = ECIMLockStack;}
inline void DMMCSession::UnlockStack()	{if(iStackP != NULL) iStackP->UnlockStack(this);}
inline void DMMCSession::Stop()			{if(iStackP != NULL) iStackP->Stop(this);}
inline void DMMCSession::Abort()		{if(iStackP != NULL) iStackP->Abort(this);}
inline TMMCSessionTypeEnum DMMCSession::SessionID() const	{return(iSessionID);}
inline DMMCStack* DMMCSession::StackP() const	{return(iStackP);}
inline TMMCCard* DMMCSession::CardP() const		{return(iCardP);}
inline TBool DMMCSession::IsEngaged() const		{return((iState & KMMCSessStateEngaged) != 0);}
inline TMMCErr DMMCSession::MMCExitCode() const			{return(iMMCExitCode);}
inline TMMCStatus DMMCSession::LastStatus() const		{return(iLastStatus);}
inline TUint32 DMMCSession::BytesTransferred() const	{return(iBytesTransferred);}
inline TUint8* DMMCSession::ResponseP()			{return(&iCommand[iCmdSP].iResponse[0]);}

inline TUint32 DMMCSession::EffectiveModes() const
	{if(iStackP != NULL) return(iStackP->EffectiveModes(iConfig)); return(0);}

inline void DMMCSession::Block(TUint32 aFlag)
	{iStackP->Block(this, aFlag);}

inline void DMMCSession::UnBlock(TUint32 aFlag, TMMCErr anExitCode)
	{iStackP->UnBlock(this, aFlag, anExitCode);}

inline void DMMCSession::SwapMe()
	{iState |= KMMCSessStateDoReSchedule;}

inline void DMMCSession::ResetCommandStack()
	{iCmdSP = 0;}

inline void DMMCSession::PushCommandStack()
	{
	__ASSERT_ALWAYS(TUint(++iCmdSP)<KMaxMMCCommandStackDepth,
		DMMCController::Panic(DMMCController::EMMCCommandStack));
	}

inline void DMMCSession::PopCommandStack()
	{
	__ASSERT_ALWAYS(--iCmdSP>=0,
		DMMCController::Panic(DMMCController::EMMCCommandStack));
	}

inline TMMCCommandDesc& DMMCSession::Command()	{return(iCommand[iCmdSP]);}


//	--------  class DMMCStack  --------

inline void DMMCStack::ReportPowerUp()
	{iPoweredUp = ETrue;}

inline void DMMCStack::ReportPowerDown()
	{iPoweredUp = EFalse; iStackState |= KMMCStackStateInitPending;}

inline void DMMCStack::Reset()
	{iAbortAll = ETrue; Scheduler(iAbortReq);}

inline void DMMCStack::CompleteAll(TMMCErr aCode)
	{iCompleteAllExitCode = aCode; Scheduler(iCompReq);}

inline TUint DMMCStack::MaxCardsInStack() const
	{return( iMaxCardsInStack );}
												
inline TMMCCard* DMMCStack::CardP(TUint aCardNumber)
	{return( (aCardNumber<iMaxCardsInStack) ? (iCardArray->CardP(aCardNumber)) : NULL );}

inline DMMCController* DMMCStack::MMCControllerP() const
	{return( iMMCControllerP );}

inline TBool DMMCStack::InitStackInProgress() const
	{return( (iStackState & KMMCStackStateInitInProgress) != 0 );}

inline TBool DMMCStack::HasSessionsQueued() const
	{return((iWorkSet.Size()!=0) || (iReadyQueue.Size()!=0) || (iEntryQueue.Size()!=0));}

inline TBool DMMCStack::HasCardsPresent()
	{
	for (TUint i=0 ; i<iMaxCardsInStack ; i++)
		if (CardDetect(i)) return(ETrue);
	return(EFalse);
	}

inline TMMCStateMachine& DMMCStack::Machine()
	{return( iSessionP->iMachine );}

inline TMMCBusConfig& DMMCStack::BusConfig()
	{return( iConfig.iBusConfig );}

inline TMMCCommandDesc& DMMCStack::Command()
	{return( iSessionP->Command() );}

inline DMMCSession& DMMCStack::Session()
	{return(*iSessionP);}

inline void DMMCStack::BlockCurrentSession(TUint32 aFlag)
	{Block(iSessionP,aFlag);}

inline void DMMCStack::UnBlockCurrentSession(TUint32 aFlag, TMMCErr anExitCode)
	{UnBlock(iSessionP,aFlag,anExitCode);}

inline void DMMCStack::ReportInconsistentBusState()
	{iStackState |= KMMCStackStateBusInconsistent;}

inline void DMMCStack::ReportASSPEngaged()
	{iSessionP->iState |= KMMCSessStateASSPEngaged;}

inline void DMMCStack::ReportASSPDisengaged()
	{iSessionP->iState &= ~KMMCSessStateASSPEngaged;}

inline void DMMCStack::SetDoorOpened()
	{iDoorOpened=ETrue;}

inline TRCA DMMCStack::CurrentSessCardRCA()
	{return(iSessionP->CardRCA());}

inline void DMMCStack::CurrentSessPushCmdStack()
	{iSessionP->PushCommandStack();}

inline void DMMCStack::CurrentSessPopCmdStack()
	{iSessionP->PopCommandStack();}

inline void DMMCStack::CurrentSessFillCmdDesc(TMMCCommandEnum aCommand)
	{iSessionP->FillCommandDesc(aCommand);}

inline void DMMCStack::CurrentSessFillCmdDesc(TMMCCommandEnum aCommand,TMMCArgument anArgument)
	{iSessionP->FillCommandDesc(aCommand,anArgument);}

inline void DMMCStack::CurrentSessFillCmdArgs(TMMCArgument anArgument,TUint32 aLength,TUint8* aMemoryP,TUint32 aBlkLen)
	{iSessionP->FillCommandArgs(anArgument,aLength,aMemoryP,aBlkLen);}

inline void DMMCStack::StackSessionNotifier(DThread* aNotifierThread, TRequestStatus* aNotifierReqStat)
	{iNotifierThread = aNotifierThread; iNotifierReqStat = aNotifierReqStat;}

inline void DMMCStack::DeselectsToIssue(TUint aNumber)
	{iDeselectsToIssue = aNumber; iStackState |= KMMCStackStateDoDeselect;}

inline TInt DMMCStack::AddPowerEvent(TPBusCallBack& aCallBack,TPBusNum aBus,TInt anEventNum)
		{return(iPwrEventArray.Add(aCallBack,(DPeriphBusController*)MMCControllerP(),aBus,anEventNum));}

inline void DMMCStack::RemovePowerEvent(CBase *aClientID)
		{iPwrEventArray.Remove(aClientID);}

//	--------  class DMMCController  --------

// Return a pointer to the DMMCStack object corresponding to the specified MMC card.
inline DMMCStack* DMMCController::Stack(TPBusNum aBus)
	{return( ((TInt)aBus < iMachineInfo.iTotalSockets) ? iStacks[0] : NULL );}

inline void DMMCController::ResetInactivity(TPBusNum /*aBus*/)
	{iPsu->ResetInactivityTimer();}

inline TPBusPsuBase* DMMCController::AccessPrimaryPsu(TPBusNum aBus)
	{ return PrimaryPsu(aBus); }

//	--------  class TMMCPsu  --------

inline void TMMCPsu::SetVoltage(TUint32 aVoltage)
	{iVoltageSetting=aVoltage;}
