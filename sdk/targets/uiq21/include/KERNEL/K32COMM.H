// K32COMM.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

//
// Texas Instruments : July 4, 2001. Added Comm PDD and LDD to support DMA
// 
#ifndef __K32COMM_H__
#define __K32COMM_H__
#include <k32std.h>
#include <d32comm.h>
#include <e32ver.h>
//
const TInt KCommsMajorVersionNumber=1;
const TInt KCommsMinorVersionNumber=1;
const TInt KCommsBuildVersionNumber=KE32BuildVersionNumber;
//
const TInt KDefaultRxBufferSize=0x400;
//
// Texas Instruments July 4, 2001 :  Receive DMA buffer constants
// those constants only apply to Helen platform so far 
//
const TInt KDefaultRxDmaBufferSize=0x400;
const TInt KUartMaxDmaTransferSize=0x400;

//
// Texas Instruments July 4, 2001 :  Special baud rate : 750 kbps
// this constant only applies to Helen platform so far 
//
const TInt KUartSpecialBaudRate = 750000;

const TInt KTxBufferSize=0x400;
const TInt KMaxHighWaterMark=0x080;
//
const TUint KReceiveIsrParityError=0x10000000;
const TUint KReceiveIsrFrameError=0x20000000;
const TUint KReceiveIsrOverrunError=0x40000000;
const TUint KReceiveIsrMaskError=0x70000000;
//
const TInt KTxNoChar=-1;
//
const TUint KReceiveIsrTermChar=0x80000000;
const TUint KReceiveIsrMaskComplete=0xf0000000;
const TUint KReceiveIsrShift=24;
const TUint KReceiveIsrShiftedMask=0x0f;
//
//
enum TStopMode {EStopNormal,EStopPwrDown,EStopEmergency};
//
//
class DChannelComm;
class DChannelCommDCE;
class DChannelCommDMA;

//
// Symbian's serial comms PDD object (only supports CPU mode)
//
class DComm : public CBase
	{
public:
	virtual TInt Start() =0;
	virtual void Stop(TStopMode aMode) =0;
	virtual void Break(TBool aState) =0;
	virtual void EnableTransmit() =0;
	virtual TUint Signals() const =0;
	virtual void SetSignals(TUint aSetMask,TUint aClearMask) =0;
	virtual TInt Validate(const TCommConfigV01 &aConfig) const =0;
	virtual void Configure(TCommConfigV01 &aConfig) =0;
	virtual void Caps(TDes8 &aCaps) const =0;
	virtual void CheckConfig(TCommConfigV01& aConfig)=0;
	virtual TInt DisableIrqs()=0;
	virtual void RestoreIrqs(TInt aIrq)=0;
	virtual TInt CompleteSlowOpen(DThread *aThread,TRequestStatus *aReqStat) =0;
	virtual TUint32 PowerRequirement()=0;
	inline TBool PowerGood();
	inline void SetCurrent(TInt aCurrent);
	inline void ReceiveIsr(TUint aChar);
	inline TInt TransmitIsr();
	inline void StateIsr(TUint aStatus);
	inline TBool Transmitting();
public:
	DChannelComm *iLdd;
	TBool iTransmitting;
	};

//
// Texas Instruments July 4, 2001: TI serial comms PDD object (supports DMA and CPU modes)
//
class DCommDMA : public CBase
{
public:
	virtual TInt    Start                 () =0;
	virtual void    Stop                  (TStopMode aMode) =0;
	virtual void    Break                 (TBool aState) =0;
	virtual void    EnableTransmit        () =0;
	virtual TUint   Signals               () const =0;
	virtual void    SetSignals            (TUint aSetMask,TUint aClearMask) =0;
	virtual TInt    Validate              (const TCommConfigV01 &aConfig) const =0;
	virtual void    Configure             (TCommConfigV01 &aConfig) =0;
	virtual void    Caps                  (TDes8 &aCaps) const =0;
	virtual void    CheckConfig           (TCommConfigV01& aConfig)=0;
	virtual TInt    DisableIrqs           ()=0;
	virtual void    RestoreIrqs           (TInt aIrq)=0;
	virtual TInt    CompleteSlowOpen      (DThread *aThread,TRequestStatus *aReqStat) =0;
	virtual TUint32 PowerRequirement      ()=0;
	inline  TBool   PowerGood             ();
	inline  void    SetCurrent            (TInt aCurrent);
	inline  void    ReceiveIsr            (TUint aChar);
	inline  TInt    TransmitIsr           ();
	inline  void    StateIsr              (TUint aStatus);
	inline  TBool   Transmitting          ();

	// Returns true if PDD is in DMA mode, false otherwise
	virtual TBool   ReceiveDmaMode        () = 0;
	virtual TBool   TransmitDmaMode       () = 0;    

	// DMA specific functions
	virtual void    SetAutoHwFlowControl  (TBool aRTS, TBool aCTS) = 0;
	virtual void    SetAutoSwFlowControl  (TBool aRxState, TBool aTxState,
									       TUint8 aXon = 0, TUint8 aXoff = 0) = 0;
	virtual void    TxSwFlowControlSignal (TUint8 aFlowControlSignal) = 0;
	virtual void    DrainRxDmaBuffer      () = 0;
	virtual TInt    SetReceiveDmaBufferSize( TInt aSize) = 0;
		
public:
	DChannelCommDMA *iLdd;
	TBool  iTransmitting;
};


class DCommDCE : public CBase
	{
public:
	virtual TInt Start() =0;
	virtual void Stop(TStopMode aMode) =0;
	virtual void Break(TBool aState) =0;
	virtual void EnableTransmit() =0;
	virtual TUint Signals() const =0;
	virtual void SetSignals(TUint aSetMask,TUint aClearMask) =0;
	virtual TInt Validate(const TCommConfigV01 &aConfig) const =0;
	virtual void Configure(TCommConfigV01 &aConfig) =0;
	virtual void Caps(TDes8 &aCaps) const =0;
	virtual void CheckConfig(TCommConfigV01& aConfig)=0;
	virtual TInt DisableIrqs()=0;
	virtual void RestoreIrqs(TInt aIrq)=0;
	virtual TInt CompleteSlowOpen(DThread *aThread,TRequestStatus *aReqStat) =0;
	virtual TInt EnableConfigChangeDetection()=0;
	virtual void DisableConfigChangeDetection()=0;
	virtual void GetConfigChange(TDes8 &aConfig)=0;
	virtual TUint32 PowerRequirement()=0;
	inline TBool PowerGood();
	inline void SetCurrent(TInt aCurrent);
	inline void ReceiveIsr(TUint aChar);
	inline TInt TransmitIsr();
	inline void StateIsr(TUint aStatus);
	inline TBool Transmitting();
public:
	DChannelCommDCE *iLdd;
	TBool iTransmitting;
	};

class DDeviceComm : public DLogicalDevice
	{
public:
	DDeviceComm();
	virtual TInt Install();
	virtual void GetCaps(TDes8 &aDes) const;
	virtual DLogicalChannel *CreateL();
	};

class DCommPowerHandler : public DPowerHandler
	{
public:
	DCommPowerHandler(DChannelComm *aLdd);
	void RequestComplete();
	void RequestPending();
	static void Timeout(TAny *, TInt);

	virtual TInt DoPowerOn();
	virtual void DoPowerStandby();
	virtual void DoPowerEmergencyStandby();
public:
	DChannelComm *iLdd;
	TTickLink iTimer;
	};

class DCommDCEPowerHandler : public DPowerHandler
	{
public:
	DCommDCEPowerHandler(DChannelCommDCE *aLdd);
	void RequestComplete();
	void RequestPending();
	static void Timeout(TAny *, TInt);

	virtual TInt DoPowerOn();
	virtual void DoPowerStandby();
	virtual void DoPowerEmergencyStandby();
public:
	DChannelCommDCE *iLdd;
	TTickLink iTimer;
	};

//
// Texas Instruments July 4, 2001 : Added Comm LDD power handler for DMA transfer support
//
class DCommDMAPowerHandler : public DPowerHandler
{
public:
	DCommDMAPowerHandler(DChannelCommDMA *aLdd);
	void RequestComplete();
	void RequestPending();
	static void Timeout(TAny *, TInt);
	
	virtual TInt DoPowerOn();
	virtual void DoPowerStandby();
	virtual void DoPowerEmergencyStandby();
public:
	DChannelCommDMA *iLdd;
	TTickLink iTimer;
};

//
// Texas Instruments July 4, 2001 : Symbian's serial comms LDD (CPU mode only)
//
class DChannelComm : public DLogicalChannel
	{
public:
	enum TState {ENotActive,EActive,EClosed};

	DChannelComm(DLogicalDevice *aDevice);
	~DChannelComm();
	virtual void ReceiveIsr(TUint aChar);
	virtual TInt TransmitIsr();
	virtual void StateIsr(TUint aStatus);
	inline void SetStatus(TState aStatus);
	inline void CompleteAllReqs(TInt aReason);
protected:
	virtual void DoCreateL(TInt aUnit,CBase *aDriver,const TDesC *anInfo,const TVersion &aVer);
	virtual void DoCancel(TInt aReqNo);
	virtual void DoRequest(TInt aReqNo,TAny *a1,TAny *a2);
	virtual TInt DoControl(TInt aFunction,TAny *a1,TAny *a2);
	void Start();
	void Stop(TStopMode aMode);
	void BreakOn();
	void BreakOff();
	void AssertFlowControl();
	void ReleaseFlowControl();
	TInt SetRxBufferSize(TInt aSize);
	void ResetBuffers(TBool aResetTx);
	TInt DoDrainRxBuffer(TInt aEndIndex);
	TInt DoFillTxBuffer();
	TInt DoCompleteRx();
	TInt DoCompleteTx();
	TInt DoCompleteEmergency();
	void ImmediateDrainRxBuffer(TInt aLength, TDes8* aDes, TBool aComplete);
	void ImmediateFillTxBuffer(const TDesC8* aDes, TInt aLength);
	inline void DrainRxBuffer()	{ Kern::Add(iRxDrainDfc); }
	inline void FillTxBuffer()	{ Kern::Add(iTxFillDfc); }
	inline void CompleteRead()	{ Kern::Add(iRxCompleteDfc); }
	inline void CompleteWrite() { Kern::Add(iTxCompleteDfc); }
	inline void CompleteSignalChange() { Kern::Add(iSignalChangeCompleteDfc); }
	inline void EmergencyComplete() { Kern::Add(iEmergencyDfc); }
	inline void EnableTransmit();
	inline TInt DisableIrqs();
	inline void RestoreIrqs(TInt aIrq);
	inline TInt IsLineFail(TUint aFailSignals);
private:
	static TInt DrainRxDfc(TAny* aDChannelComm);
	static TInt FillTxDfc(TAny* aDChannelComm);
	static TInt CompleteRxDfc(TAny* aDChannelComm);
	static TInt CompleteTxDfc(TAny* aDChannelComm);
	static TInt CompleteSignalChangeDfc(TAny* aDChannelComm);
	static TInt EmergencyDfc(TAny* aDChannelComm);
	inline TBool IsTerminator(TUint8 aChar);
	inline void SetTerminator(TUint8 aChar);
	inline TInt RxCount();
	inline TInt TxCount();
	inline TBool AreAnyPending() const;
	void InitiateRead(TAny* aRxDes, TInt aLength);
	void InitiateWrite(TAny* aTxDes, TInt aLength);
	TUint FailSignals(TUint aHandshake);
	TUint HoldSignals(TUint aHandshake);
	TUint FlowControlSignals(TUint aHandshake);
	TUint AutoSignals(TUint aHandshake);
	TInt SetConfig(TCommConfigV02& aConfig);
	void CheckOutputHeld();
	void UpdateSignals(TUint aNewStatus);
	void ResetDevice();
	void RestoreDtrRts();
public:
	inline TBool PowerGood();
	inline void SetCurrentConsumptionInMilliAmps(TInt aValue);
	virtual void DoPowerDown();
	virtual void DoEmergencyPowerDown();
public:
	// Port configuration
	TCommConfigV02 iConfig;
	DCommPowerHandler *iPowerHandler;
	friend class DCommPowerHandler;
private:
	// General items
	DComm *iPdd;
	TState iStatus;
	TDfc iRxDrainDfc;
	TDfc iRxCompleteDfc;
	TDfc iTxFillDfc;
	TDfc iTxCompleteDfc;
	TDfc iSignalChangeCompleteDfc;
	TDfc iEmergencyDfc;
	TUint iFlags;				//
	TUint iSignals;				// State of handshake lines
	TUint iFailSignals;			// 1 bit means line low causes line fail error
	TUint iHoldSignals;			// 1 bit means line low halts TX
	TUint iFlowControlSignals;	// 1 bit means signal is used for RX flow control
	TUint iAutoSignals;			// 1 bit means signal is high when channel is open
	TUint8 iTerminatorMask[32];	// 1 bit means character is a terminator
	TBool iSignalChangeNotification;
	TUint* iSignalChangePtr;
	TUint iSignalMask;
    TUint iSignalChangeInfo;
	TBool iDataAvailableNotification;

	// RX buffer related items
	TUint8 *iRxCharBuf;			// stores received characters
	TUint8 *iRxErrorBuf;		// stores received character error status
	volatile TInt iRxPutIndex;	// Index for next RX char to be stored
	TInt iRxGetIndex;			// Index for next RX char to be retrieved
	TInt iRxBufSize;
	TInt iFlowControlLowerThreshold;	// release flow control threshold
	TInt iFlowControlUpperThreshold;	// assert flow control threshold
	TInt iRxDrainThreshold;				// drain rx buffer before completion threshold
	TInt iRxBufCompleteIndex;	// One after last char to be forwarded due to completion
	TBool iInputHeld;			// TRUE if we have asserted flow control

	// RX client related items
	TAny *iRxDesPtr;			// client descriptor to accept received chars
	TInt iRxDesPos;				// pos of next char to be stored in client descriptor
	TInt iRxLength;				// number of rx chars to complete client request
	TBool iRxOutstanding;		// TRUE if a client read is outstanding
	TInt iRxError;

	// TX buffer related items
	TUint8 *iTxBuffer;			// stores characters awaiting transmission
	TInt iTxPutIndex;			// Index for next TX char to be stored
	volatile TInt iTxGetIndex;	// Index for next TX char to be output
	TInt iTxBufSize;
	TInt iTxFillThreshold;		// fill tx buffer threshold
	TInt iOutputHeld;			// bits set if peer has asserted flow control
	TInt iJamChar;				// character to jam into TX output stream

	// TX client related items
	TAny *iTxDesPtr;			// client descriptor being transmitted
	TInt iTxDesPos;				// pos of next char to be fetched from client descriptor
	TInt iTxDesLength;			// initial size of tx descriptor
	TBool iTxOutstanding;		// TRUE if a client write is outstanding
	TInt iTxError;
	};

class DChannelCommDCE : public DLogicalChannel
	{
public:
	enum TState {ENotActive,EActive,EClosed};

	DChannelCommDCE(DLogicalDevice *aDevice);
	~DChannelCommDCE();
	virtual void ReceiveIsr(TUint aChar);
	virtual TInt TransmitIsr();
	virtual void StateIsr(TUint aStatus);
	virtual void ConfigChangeIsr();
	inline void SetStatus(TState aStatus);
	inline void CompleteAllReqs(TInt aReason);
protected:
	virtual void DoCreateL(TInt aUnit,CBase *aDriver,const TDesC *anInfo,const TVersion &aVer);
	virtual void DoCancel(TInt aReqNo);
	virtual void DoRequest(TInt aReqNo,TAny *a1,TAny *a2);
	virtual TInt DoControl(TInt aFunction,TAny *a1,TAny *a2);
	void Start();
	void Stop(TStopMode aMode);
	void BreakOn();
	void BreakOff();
	void AssertFlowControl();
	void ReleaseFlowControl();
	TInt SetRxBufferSize(TInt aSize);
	void ResetBuffers(TBool aResetTx);
	TInt DoDrainRxBuffer(TInt aEndIndex);
	TInt DoFillTxBuffer();
	TInt DoCompleteRx();
	TInt DoCompleteTx();
	TInt DoCompleteConfigChange();
	TInt DoCompleteEmergency();
	void ImmediateDrainRxBuffer(TInt aLength, TDes8* aDes, TBool aComplete);
	void ImmediateFillTxBuffer(const TDesC8* aDes, TInt aLength);
	inline void DrainRxBuffer()	{ Kern::Add(iRxDrainDfc); }
	inline void FillTxBuffer()	{ Kern::Add(iTxFillDfc); }
	inline void CompleteRead()	{ Kern::Add(iRxCompleteDfc); }
	inline void CompleteWrite() { Kern::Add(iTxCompleteDfc); }
	inline void CompleteSignalChange() { Kern::Add(iSignalChangeCompleteDfc); }
	inline void CompleteFlowControlChange() { Kern::Add(iFlowControlChangeCompleteDfc); }
	inline void CompleteConfigChange() { Kern::Add(iConfigChangeCompleteDfc); }
	inline void EmergencyComplete() { Kern::Add(iEmergencyDfc); }
	inline void EnableTransmit();
	inline TInt DisableIrqs();
	inline void RestoreIrqs(TInt aIrq);
	inline TInt IsLineFail(TUint aFailSignals);
private:
	static TInt DrainRxDfc(TAny* aDChannelCommDCE);
	static TInt FillTxDfc(TAny* aDChannelCommDCE);
	static TInt CompleteRxDfc(TAny* aDChannelCommDCE);
	static TInt CompleteTxDfc(TAny* aDChannelCommDCE);
	static TInt CompleteSignalChangeDfc(TAny* aDChannelCommDCE);
	static TInt CompleteFlowControlChangeDfc(TAny* aDChannelCommDCE);
	static TInt CompleteConfigChangeDfc(TAny* aDChannelCommDCE);
	static TInt EmergencyDfc(TAny* aDChannelCommDCE);
	inline TBool IsTerminator(TUint8 aChar);
	inline void SetTerminator(TUint8 aChar);
	inline TInt RxCount();
	inline TInt TxCount();
	inline TBool AreAnyPending() const;
	void InitiateRead(TAny* aRxDes, TInt aLength);
	void InitiateWrite(TAny* aTxDes, TInt aLength);
	TUint FailSignals(TUint aHandshake);
	TUint HoldSignals(TUint aHandshake);
	TUint FlowControlSignals(TUint aHandshake);
	TUint AutoSignals(TUint aHandshake);
	TInt SetConfig(TCommConfigV01& aConfig);
	void CheckOutputHeld();
	void UpdateSignals(TUint aNewStatus);
	void ResetDevice();
	void RestoreDsrCts();
public:
	inline TBool PowerGood();
	inline void SetCurrentConsumptionInMilliAmps(TInt aValue);
    inline TBool ConfigDetection();
	virtual void DoPowerDown();
	virtual void DoEmergencyPowerDown();
public:
	// Port configuration
	TCommConfigV01 iConfig;
	DCommDCEPowerHandler *iPowerHandler;
	friend class DCommDCEPowerHandler;
private:
	// General items
	DCommDCE *iPdd;
	TState iStatus;
	TDfc iRxDrainDfc;
	TDfc iRxCompleteDfc;
	TDfc iTxFillDfc;
	TDfc iTxCompleteDfc;
	TDfc iSignalChangeCompleteDfc;
	TDfc iFlowControlChangeCompleteDfc;
	TDfc iConfigChangeCompleteDfc;
	TDfc iEmergencyDfc;
	TUint iFlags;				//
	TUint iSignals;				// State of handshake lines
	TUint iFailSignals;			// 1 bit means line low causes line fail error
	TUint iHoldSignals;			// 1 bit means line low halts TX
	TUint iFlowControlSignals;	// 1 bit means signal is used for RX flow control
	TUint iAutoSignals;			// 1 bit means signal is high when channel is open
	TUint8 iTerminatorMask[32];	// 1 bit means character is a terminator
	TBool iSignalChangeNotification;
	TUint* iSignalChangePtr;
	TUint iSignalMask;
    TUint iSignalChangeInfo;
	TBool iDataAvailableNotification;
	TBool iFlowControlChangeNotification;
	TBool iConfigChangeNotification;
	TAny* iNotifyConfigChangePtr;
	TBool iConfigDetection;
	// RX buffer related items
	TUint8 *iRxCharBuf;			// stores received characters
	TUint8 *iRxErrorBuf;		// stores received character error status
	volatile TInt iRxPutIndex;	// Index for next RX char to be stored
	TInt iRxGetIndex;			// Index for next RX char to be retrieved
	TInt iRxBufSize;
	TInt iFlowControlLowerThreshold;	// release flow control threshold
	TInt iFlowControlUpperThreshold;	// assert flow control threshold
	TInt iRxDrainThreshold;				// drain rx buffer before completion threshold
	TInt iRxBufCompleteIndex;	// One after last char to be forwarded due to completion
	TBool iInputHeld;			// TRUE if we have asserted flow control

	// RX client related items
	TAny *iRxDesPtr;			// client descriptor to accept received chars
	TInt iRxDesPos;				// pos of next char to be stored in client descriptor
	TInt iRxLength;				// number of rx chars to complete client request
	TBool iRxOutstanding;		// TRUE if a client read is outstanding
	TInt iRxError;

	// TX buffer related items
	TUint8 *iTxBuffer;			// stores characters awaiting transmission
	TInt iTxPutIndex;			// Index for next TX char to be stored
	volatile TInt iTxGetIndex;	// Index for next TX char to be output
	TInt iTxBufSize;
	TInt iTxFillThreshold;		// fill tx buffer threshold
	TInt iOutputHeld;			// bits set if peer has asserted flow control
	TInt iJamChar;				// character to jam into TX output stream

	// TX client related items
	TAny *iTxDesPtr;			// client descriptor being transmitted
	TInt iTxDesPos;				// pos of next char to be fetched from client descriptor
	TInt iTxDesLength;			// initial size of tx descriptor
	TBool iTxOutstanding;		// TRUE if a client write is outstanding
	TInt iTxError;
	};

//
// Texas Instruments July 4,2001 : TI serial comms LDD (DMA and CPU modes)
//
class DChannelCommDMA : public DLogicalChannel
{
public:
	enum TState {EOpen,EActive,EClosed};
	
	DChannelCommDMA(DLogicalDevice *aDevice);
	~DChannelCommDMA();

	// ******************************************
	// Specific DMA functions
	virtual void ReceiveFrame(const TDes8 &aFrame);
	virtual void TransmitFrame(TDes8 &aFrame);
	virtual void SwFlowControlIsr(TUint aStatus);
	// ******************************************

	virtual void ReceiveIsr(TUint aChar);
	virtual TInt TransmitIsr();
	virtual void StateIsr(TUint aStatus);
	inline void SetStatus(TState aStatus);
	inline void CompleteAllReqs(TInt aReason);
protected:
	virtual void DoCreateL(TInt aUnit,CBase *aDriver,const TDesC *anInfo,const TVersion &aVer);
	virtual void DoCancel(TInt aReqNo);
	virtual void DoRequest(TInt aReqNo,TAny *a1,TAny *a2);
	virtual TInt DoControl(TInt aFunction,TAny *a1,TAny *a2);
	void Start();
	void Stop(TStopMode aMode);
	void BreakOn();
	void BreakOff();
	void AssertFlowControl();
	void ReleaseFlowControl();
	TInt SetRxBufferSize(TInt aSize);
	void SetReceiveDmaMode(); // Set Rx DMA mode on UART
	void SetTransmitDmaMode(); // Set Tx DMA mode on UART
	void ResetBuffers(TBool aResetTx);
	TInt DoDrainRxBuffer(TInt aEndIndex);
	TInt DoFillTxBuffer();
	TInt DoCompleteRx();
	TInt DoCompleteTx();
	TInt DoCompleteEmergency();
	void ImmediateDrainRxBuffer(TInt aLength, TDes8* aDes, TBool aComplete);
	void ImmediateFillTxBuffer(const TDesC8* aDes, TInt aLength);
	inline void DrainRxBuffer()	{ Kern::Add(iRxDrainDfc); }
	inline void FillTxBuffer()	{ Kern::Add(iTxFillDfc); }
	inline void CompleteRead()	{ Kern::Add(iRxCompleteDfc); }
	inline void CompleteWrite() { Kern::Add(iTxCompleteDfc); }
	inline void CompleteSignalChange() { Kern::Add(iSignalChangeCompleteDfc); }
	inline void EmergencyComplete() { Kern::Add(iEmergencyDfc); }
	inline void EnableTransmit();
	inline TInt DisableIrqs();
	inline void RestoreIrqs(TInt aIrq);
	inline TInt IsLineFail(TUint aFailSignals);
private:
	static TInt DrainRxDfc(TAny* aDChannelCommDMA);
	static TInt FillTxDfc(TAny* aDChannelCommDMA);
	static TInt CompleteRxDfc(TAny* aDChannelCommDMA);
	static TInt CompleteTxDfc(TAny* aDChannelCommDMA);
	static TInt CompleteSignalChangeDfc(TAny* aDChannelCommDMA);
	static TInt EmergencyDfc(TAny* aDChannelCommDMA);
	inline TBool IsTerminator(TUint8 aChar);
	inline void SetTerminator(TUint8 aChar);
	inline TInt RxCount();
	inline TInt TxCount();
	inline TBool AreAnyPending() const;
	void InitiateRead(TAny* aRxDes, TInt aLength);
	void InitiateWrite(TAny* aTxDes, TInt aLength);
	TUint FailSignals(TUint aHandshake);
	TUint HoldSignals(TUint aHandshake);
	TUint FlowControlSignals(TUint aHandshake);
	TUint AutoSignals(TUint aHandshake);
	TInt SetConfig(TCommConfigV01& aConfig);
	void CheckOutputHeld();
	void UpdateSignals(TUint aNewStatus);
public:
	inline TBool PowerGood();
	inline void SetCurrentConsumptionInMilliAmps(TInt aValue);
	virtual void DoPowerUp();
	virtual void DoPowerDown();
	virtual void DoEmergencyPowerDown();
public:
	// Port configuration
	TCommConfigV01 iConfig;
	DCommDMAPowerHandler *iPowerHandler;
	friend class DCommDMAPowerHandler;
private:
	// General items
	DCommDMA *iPdd;
	TState iStatus;
	TBool  iRxDmaMode;
	TBool  iTxDmaMode;
	TDfc iRxDrainDfc;
	TDfc iRxCompleteDfc;
	TDfc iTxFillDfc;
	TDfc iTxCompleteDfc;
	TDfc iSignalChangeCompleteDfc;
	TDfc iEmergencyDfc;
	TUint iFlags;				//
	TUint iSignals;				// State of handshake lines
	TUint iFailSignals;			// 1 bit means line low causes line fail error
	TUint iHoldSignals;			// 1 bit means line low halts TX
	TUint iFlowControlSignals;	// 1 bit means signal is used for RX flow control
	TUint iAutoSignals;			// 1 bit means signal is high when channel is open
	TUint8 iTerminatorMask[32];	// 1 bit means character is a terminator
	TBool iSignalChangeNotification;
	TUint* iSignalChangePtr;
	TUint iSignalMask;
	TUint iSignalChangeInfo;
	TBool iDataAvailableNotification;

	// DMA auto-signalling (Auto HW/SW flow control)
	TBool iAutoRTS;             
	TBool iAutoCTS;
	TBool iAutoObeyXoff;        // defines if rx software flow control is set up
	TBool iAutoSendXoff;        // defines if tx software flow control is set up

	// RX buffer related items
	TUint8 *iRxCharBuf;			// stores received characters
	TUint8 *iRxErrorBuf;		// stores received character error status
	volatile TInt iRxPutIndex;	// Index for next RX char to be stored
	TInt iRxGetIndex;			// Index for next RX char to be retrieved
	TInt iRxBufSize;
	TInt iFlowControlLowerThreshold;	// release flow control threshold
	TInt iFlowControlUpperThreshold;	// assert flow control threshold
	TInt iRxDrainThreshold;				// drain rx buffer before completion threshold
	TInt iRxBufCompleteIndex;	// One after last char to be forwarded due to completion
	TBool iInputHeld;			// TRUE if we have asserted flow control
	
	// RX client related items
	TAny *iRxDesPtr;			// client descriptor to accept received chars
	TInt iRxDesPos;				// pos of next char to be stored in client descriptor
	TInt iRxLength;				// number of rx chars to complete client request
	TBool iRxOutstanding;		// TRUE if a client read is outstanding
	TInt iRxError;
	
	// TX buffer related items
	TUint8 *iTxBuffer;			// stores characters awaiting transmission
	TInt iTxPutIndex;			// Index for next TX char to be stored
	volatile TInt iTxGetIndex;	// Index for next TX char to be output
	TInt iTxBufSize;
	TInt iTxFillThreshold;		// fill tx buffer threshold
	TInt iOutputHeld;			// bits set if peer has asserted flow control
	TInt iJamChar;				// character to jam into TX output stream
	
	// TX client related items
	TAny *iTxDesPtr;			// client descriptor being transmitted
	TInt iTxDesPos;				// pos of next char to be fetched from client descriptor
	TInt iTxDesLength;			// initial size of tx descriptor
	TBool iTxOutstanding;		// TRUE if a client write is outstanding
	TInt iTxError;

	// Read request timer
	TTickLink iReadRequestTimer;
	virtual void StartReadTimer();
	static  void ReadTimeout(TAny *, TInt);
};

#include "k32comm.inl"

#endif
