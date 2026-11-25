// IRCOMM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__IRCOMM_H__)
#define __IRCOMM_H__


const TUint KCommLowUnit=0;
const TUint KCommHighUnit=0;

const TUint KIrCommLsapSel=KAutoBindLSAP;
const TUint KIrDialLsapSel=KAutoBindLSAP;
const TUint8 KDefaultPort=2;

const TInt KIrCommHitBitMask=0x02;

// ######  IrCOMM enums for cooked parameters  ######
enum TIrCOMMParamValue {EServiceType=0x00,EPortType=0x01,EPortName=0x02,
			EDataRate=0x10,EDataFormat=0x11,EFlowControl=0x12,EXonXoff=0x13,
			EEnqAck=0x14,ELineStatus=0x15,EBreak=0x16,EDTE=0x20,EDCE=0x021,
			EPoll=0x22};
enum TIrCOMMSupport {KCentronics=0x08,K9WireCooked=0x04,K3WireCooked=0x02,
		K3WireRaw=0x01,KLPT=0x00,KIrDIAL=0xff};

enum TIrCOMMDataFormat	{
	E5Bits=0x00,E6Bits=0x01,E7Bits=0x02,E8Bits=0x03,
	E1Stop=0x00,E2Stop=0x04,
	ENoParity=0x00,EEnableParity=0x08,
	EOddParity=0x00,EEvenParity=0x10,EMarkParity=0x20,ESpaceParity=0x30};

enum TIrCOMMFlowControl {EXonXoffInput=0x01,EXonXoffOutput=0x02,ERtsCtsInput=0x04,
		ERtsCtsOutput=0x08,EDsrDtrInput=0x10,EDsrDtrOutput=0x20,EEnqAckInput=0x40,
			EEnqAckOutput=0x80};
enum TIrCOMMLineStatus {EOverRun=0x02,EParity=0x04,EFraming=0x08};

enum TIrCOMMDteBits{EDeltaDTR=0x01, EDeltaRTS=0x02, EDTRState=0x04, ERTSState=0x08};
enum TIrCOMMDceBits{EDeltaCTS=0x01, EDeltaDSR=0x02, EDeltaRI=0x04, EDeltaCD=0x08,
					ECTSState=0x10, EDSRState=0x20, ERIState=0x40, ECDState=0x80};

#define SERIAL_DESCRIPTION _L("IrCOMM 3 wire raw")
#define SERIAL_NAME _S("IrCOMM")

#define IRDA_IAS_CLASSNAME _L8("IrDA:IrCOMM")
#define IRDA_LPT_CLASSNAME _L8("IrLPT")
#define IRDA_PARAMETERS_ATTRIBUTE _L8("Parameters")
#define IRDA_COOKED_LSAPSEL_ATTRIBUTE _L8("IrDA:TinyTP:LsapSel")
#define IRDA_RAW_LSAPSEL_ATTRIBUTE _L8("IrDA:IrLMP:LsapSel")
#define IRDA_MISCAPITALIZED_LSAPSEL_ATTRIBUTE _L8("IrDA:IrLMP:LSAPSel")
#define IRDA_IRDIAL_CLASSNAME _L8("IrModem")
#define IRDA_IRDIAL_LSAPSEL_ATTRIBUTE _L8("IrDA:TinyTP:LsapSel")
#define IRDA_IRMROUTER_CLASSNAME _L8("mRouter")
#define IRDA_IRMROUTER_LSAPSEL_ATTRIBUTE _L8("IrDA:TinyTP:LsapSel")
#define IRDA_TINYTP _L8("IrTinyTP")
#define IRDA_IRMUX _L8("IrMux")

const TUint KCentronicsParameterBit=0x08;
const TUint K9WireCookedParameterBit=0x04;
const TUint K3WireCookedParameterBit=0x02;
const TUint K3WireRawParameterBit=0x01;

const TUint8 KIrCOMMServiceTypeIAS_PI_Parameter=0x00;
const TUint8 KIrCOMMIASServiceType=0x04;   // Set to 9-wire cooked here = 0x04
// V.IMP:  0x01=3-wire Raw, 0x02=3-wire cooked, 0x04=9-wire cooked
const TUint8 KIrCOMMPortTypeIAS_PI_Parameter=0x01;
const TUint8 KIrCOMMIASPortType=0x01; // 0x01=Serial, 0x02=Parallel.
const TInt KIrCOMMDefaultPortNumber=2;
//
const TInt KConnectorPriority=0;
const TInt KReaderPriority=100;
const TInt KWriterPriority=50;
const TInt KStarterPriotity=-10;
const TInt KImmediatePriority=1000;
//
// Intuwave - added value to those possible to put in bitfield of iSIRSettings
// in TCommConfigV01
const TUint KConfigmRouterTinyTP=0x04;

//
class CIrCommPort;
class CIrCommReader2;
class CIrCommCirBuf : public CCirBufBase
    {
friend class CIrCommReader2;

public:
    CIrCommCirBuf();
    TInt WriteToClient(TAny* aPtr, TInt& aOffset, TInt aClientLength, CIrCommPort& aPort);
    TInt Consume(const TDesC8& aDes, CIrCommPort& aPort);
    inline TBool TerminatorReceived() const;
    inline void Reset();
    inline void SetLengthL(TInt aLength);
    void Rescan(CIrCommPort& aPort);
private:
    TInt iTerminatorOffset;
    };

class CIrCommReader2 : public CActive
    {
public:
    static CIrCommReader2* NewL(CIrCommPort& aParent);
    void ConstructL(CIrCommPort& aParent);
    CIrCommReader2();
    ~CIrCommReader2();

    void ClientCompleteRequest(TInt aResult);
    void ClientFlushBuffers();
    TInt ClientSetBufferLength(TInt aLength);
    void ClientRead(const TAny* aPtr, TInt aLength);
	void CheckStarted();
    inline TInt ClientQueryReceiveBuffers() const;
    inline TInt ClientBufferLength() const;

    inline TBool IsClientRequestPending() const;
    inline TBool IsStarted() const;

    TInt Start(RSocket& aSocket, TInt aReadBufLen);
    void Stop();
    inline void RescanTerminators();

private:
    void TryToComplete();
    void FillRxBuffer();
    virtual void RunL();
    virtual void DoCancel();

    CIrCommPort* iParent;
    RSocket *iSocket;

    TAny* iClientPtr;
    TInt iClientLength;
    TInt iClientDone;
    TBool iClientOneOrMore;

    CIrCommCirBuf* iCircBuf;
    TPtr8 iReadPtr;
    TInt iReadRemaining;
    };
//
class CIrCommWriter2 : public CActive
    {
public:
    CIrCommWriter2(CIrCommPort& aParent);
    ~CIrCommWriter2();

    virtual void RunL();
    virtual void DoCancel();

    void ClientCompleteRequest(TInt aResult);
    void ClientWrite(const TAny* aPtr, TInt aLength);
    TInt Start(RSocket& aSocket, TInt aWriteBufLen);
    void Stop(TInt aClearSocket=EFalse);
    void RemoteLinesChanged();
    void LocalLinesChanged();
    inline TBool IsWriteZero() const;
    inline TBool IsClientRequestPending() const;
    inline void ClearLocalLineChangePending();

private:
    void TryToComplete();
    void CheckStarted();

    CIrCommPort* iParent;
    RSocket *iSocket;

    TAny* iClientPtr;
    TInt iClientLength;
    TInt iClientDone;

    TPtr8 iWritePtr;
    TBool iLocalLineChangePending;
    };

class CIrCommCommonBase : public CActive
	{
protected:
	CIrCommCommonBase(CIrCommPort& aParent);
    ~CIrCommCommonBase();
	TInt OpenSocket(TIrCOMMSupport aLevel);
    void ClearSocket();

	CIrCommPort* iPort;
	RSocket iCommonSocket;
	TBuf8<60> iConnectDataIn;  // Max IrCOMM conn data = 60 bytes
	TBuf8<60> iConnectDataOut; // Win95 sends 24 bytes....
	};

class TIrCommQuery  : public TIASQuery
    {
public:
	void FormulateIrMRouterQuery(const TIrdaSockAddr& anAddr);
	void FormulateIrdialQuery(const TIrdaSockAddr& anAddr);
    void FormulateParametersQuery(const TIrdaSockAddr& anAddr);
    void FormulateLsapQuery(TIrCOMMSupport aLevel, const TIrdaSockAddr& anAddr);
    TIrCOMMSupport FormulateLsapQueryFromResult(const TIASResponse& aResult, const TIrdaSockAddr& anAddr);
    void FormulateLptQuery(const TIrdaSockAddr& anAddr);
    void FormulateMiscapitalizedQuery(const TIrdaSockAddr& anAddr);
    static TIrCOMMSupport MaxBitFrom(TUint8 aUnion);
    };

class CIrCommConnectInitiator : public CIrCommCommonBase
	{
public:
    inline RSocket& Socket() const;
	virtual void DoCancel();
    virtual void RunL();
	CIrCommConnectInitiator(CIrCommPort& aParent);
    ~CIrCommConnectInitiator();
	void Start();
    void Stop(TRequestStatus*& aStatus);
	inline void Stop();

    static TInt TimerExpired(TAny* aThis);
    void KillTimer();
    void StartTimer(TTimeIntervalMicroSeconds32);

    void Clear();
    void GoToDiscovering();
    void LockedAction();
    void GoToStopped();

private:
    enum TState { EStopped, EDiscovering, EQueryingIAS, EConnecting, EConnected, EShuttingDown };

    TState iState;
    TInt iAttemptCount;

    // For Connecting
	TIrdaSockAddr iConnectAddr;

    // For discovering
    RHostResolver iRes;
	TNameEntry iName;
    TBuf<5> iAsterix;

    // For querying IAS
    RNetDatabase iNetDB;
    TIrCommQuery iQuery;
	TIASResponse iResult;
    TBool iIASTimedOut;

    // For timing
    TDeltaTimerEntry iTimerEntry;
    TBool iTimerActive;

    // for locking
    TBool iAwaitingLockAction;
	};

//
// CActive derived call to handle passively connecting to the remote host
//
class CIrCommConnectResponder : public CIrCommCommonBase
	{
public:
    inline RSocket& Socket() const;
	CIrCommConnectResponder(CIrCommPort& aParent);
	~CIrCommConnectResponder();
    void Start();
    void Stop(TRequestStatus*& aStatus, TBool aClear=EFalse);
	inline void Stop(TBool aClear=EFalse);
    void GoToAccepting();
	void DoCancel();
	void RunL();
    void LockedAction();
    void Clear();
private:
    enum TState { EStopped, EAccepting, EAccepted };
	RSocket iDataSocket;
    TBool iAwaitingLockAction;
    TBool iIASIsRegistered;
    TState iState;
    TInt iAcceptError;
	};

//
// CActive derived call to handle passively connecting to the remote host
//
class CIrDialConnectResponder : public CIrCommCommonBase
	{
public:
    inline RSocket& Socket() const;
	CIrDialConnectResponder(CIrCommPort& aParent);
	~CIrDialConnectResponder();
    void Start();
    void Stop(TRequestStatus*& aStatus, TBool aClear=EFalse);
	inline void Stop(TBool aClear=EFalse);
    void GoToAccepting();
	void DoCancel();
	void RunL();
    void LockedAction();
    void Clear();
private:
    enum TState { EStopped, EAccepting, EAccepted };
	RSocket iDataSocket;
    TBool iAwaitingLockAction;
    TBool iIASIsRegistered;
    TState iState;
    TInt iAcceptError;
	};

// Couple of utility classes so that we never have to go synchronous
class CProtocolStarter : public CTimer
//
// Active object to start up the Irda protocol asynchronously
//
	{
public:
	static CProtocolStarter* NewL(CIrCommPort& aPort);
    ~CProtocolStarter();
    void CheckStarted();
    void DeferredDelete();
    inline RSocketServ& SocketServ() const;
    void LockedAction();

private:
	CProtocolStarter(CIrCommPort& aPort);
	virtual void RunL();
    virtual void DoCancel();
	TInt TimerExpired(TAny* aThis);

    enum TStarterState {ENotStarted, EStarted, EStarting, EClosing, EStatusIoctl};

	CIrCommPort *iPort;
    RSocketServ iSockServ;
    TStarterState iState;
    TBool iLoaded;
	TInt iShutdownTicks;
	TPckgBuf<TInt> iIoctlBuf;
	};

class CLocker : public CActive
    {

public:
    CLocker(CIrCommPort& aPort);
    ~CLocker();
    void Lock();
    virtual void RunL();
    virtual void DoCancel();
private:
    CIrCommPort* iPort;
    };

//
// "Entry point object" makes the objects which do the work
//
class CIrCommPortFactory : public CSerial
	{
	enum {KMajorVersion=1,KMinorVersion=0,KBuild=204};
public:
	static CIrCommPortFactory* NewL();
	virtual CPort * NewPortL(const TUint aUnit);
	virtual void Info(TSerialInfo &aSerialInfo);
private:
	void ConstructL();
	CIrCommPortFactory();
	};

class TIrCOMMParameters
	{
public:
	TIrCOMMParameters(TDes8& anIrCOMMFrame);
    TIrCOMMParameters(const TDesC8& anIrCOMMFrame);

	TInt PeekNextParameter(TIrCOMMParamValue &aType,TInt &aLength);
	TInt GetNextParameterAsInteger(TIrCOMMParamValue aType,TInt &aValue);
	void AddIntegerParameter(TIrCOMMParamValue aType, TInt aValue);
    inline TInt Length() const;
private:
	TPtr8 iDataFrame;
	};

//#define _DEBUG_CONSOLE_
#if defined(_DEBUG_CONSOLE_)
//
#include <E32TWIN.H>
class RDebugConsole : public RConsole
	{
public:
	RDebugConsole();
public:
	void Printf(TRefByValue<const TDesC> aFmt,...);
	};

#define DEBUG_TRACE(m) m

#else   // (_DEBUG)

#define DEBUG_TRACE(m)
//
#endif

//
// CPort is the object which interfaces to the commserver
//
class CIrCommPort : public CPort
	{
public:
	static CIrCommPort * NewL(TUint aUint);
public:
	virtual void StartRead(const TAny *aClientBuffer,TInt aLength);
	virtual void ReadCancel();
	virtual TInt QueryReceiveBuffer(TInt& aLength) const;
	virtual void ResetBuffers(TUint aFlags);
	virtual void StartWrite(const TAny *aClientBuffer,TInt aLength);
	virtual void WriteCancel();
	virtual void Break(TInt aTime);
	virtual void BreakCancel();
	virtual TInt GetConfig(TDes8& aPackage) const;
	virtual TInt SetConfig(const TDesC8& aPackage);
	virtual TInt SetServerConfig(const TDesC8& aPackage);
	virtual TInt GetServerConfig(TDes8& aPackage);
	virtual TInt GetCaps(TDes8& aPackage);
	virtual TInt GetSignals(TUint& aSignals);
	virtual TInt SetSignalsToMark(TUint aSignals);
	virtual TInt SetSignalsToSpace(TUint aSignals);
	virtual TInt GetReceiveBufferLength(TInt& aLength) const;
	virtual TInt SetReceiveBufferLength(TInt aLength);
	virtual ~CIrCommPort();

	void ProtocolStarted();
    void ProtocolStopped(TRequestStatus*&);
	void CancelReaderWriter();
	void Destruct();
	void IrDAErrorCompletion(TInt anError);

	inline TIrCOMMSupport IrCOMMSupport() const;
    inline TBool AreAnyPending() const;
	void HandleIrCommControlFrame(const TDesC8 &aControl);
    void AppendIrCommControlFrame(TDes8& aFrame);
    void AppendIrCommConnectData(TDes8& aData);

    TBool IsLineFail(TUint iHandShake) const;
    inline TBool IsLineFail() const;
    inline TBool IsLineObeyed() const;
    inline RSocketServ& SocketServ() const;
    void InitiateSuccess(TDes8& aConnectInData);
    void AcceptSuccess(TDes8& aConnectInData);
    inline void SetIrCOMMSupport(TIrCOMMSupport aLevel);
    static TInt BreakTimerExpired(TAny* aPort);
    TInt StartReaderWriter(RSocket& aSocket);
    void CheckLinesAsserted(TBool aChange=EFalse);
    void LockSocketServer();
    void DoLockedActions();
    void SetOutputHeld();
	inline RSocket* Socket() const;

    inline TBool UsingTerminators() const;
    TBool IsTerminatorChar(TText8 aChar);

	// Version 02 additions to IrCOMM starts from here
	virtual void NotifySignalChange(TUint aSignalMask);
	virtual void NotifySignalChangeCancel();
	virtual void NotifyConfigChange();
	virtual void NotifyConfigChangeCancel();
	virtual void NotifyFlowControlChange();
	virtual void NotifyFlowControlChangeCancel();
	virtual void NotifyBreak();
	virtual void NotifyBreakCancel();
	virtual void NotifyDataAvailable();
	virtual void NotifyDataAvailableCancel();
	virtual void NotifyOutputEmpty();
	virtual void NotifyOutputEmptyCancel();
	virtual TInt GetFlowControlStatus(TFlowControl& aFlowControl);
	virtual TInt GetRole(TCommRole& aRole);
	virtual TInt SetRole(TCommRole aRole);

	void StartSignals();
	void SoftwareFlowChanged(TText8 aChar);
	void HardwareFlowChanged();
	void OutPutBufferIsEmpty();
	void InPutBufferHasNewData();
	// Version 02 additions to IrCOMM ends to here

	// Intuwave additions
	TBool CheckmRouterTinyTP() const;

private:
    CIrCommPort();
	void ConstructL(TUint aUint);

private:

	CIrCommReader2 *iReader;
	CIrCommWriter2 *iWriter;
    CProtocolStarter* iStarter;
	CIrCommConnectInitiator* iInitiator;
    CIrCommConnectResponder* iIrcommAcceptor;
	CIrDialConnectResponder* iIrdialAcceptor;
    CLocker* iLocker;
	RSocket* iSocket;
private:
	TIrCOMMSupport iIrCOMMSupport;
	TUint iLastRemoteSignals;
    TUint iSignals;
    TCommConfigV01 iConfig;
    TDeltaTimerEntry iBreakTimer;
    TUint iFlags;
    TUint iOutputHeld;
public:
	TBool iDontCheckStarted;
private:
	// Version 02 extensions starts from here
	TCommRole iRole;
	TInt  iRemoteBaud;
	TUint iNotifySignalMask;
	TBool iSignalNotify;
	TBool iFlowControlNotify;
	TBool iConfigNotify;
	TCommNotificationV01 iPeerConfig;
	TBool iBreakNotify;
	TBool iInBufHasDataNotify;
	TBool iOutBufIsEmptyNotify;
	TFlowControl iFlowControl;
	//Version 02 extensions ends to here

	// Intuwave Extension
	TBool imRouterTinyTP;   // flag indicates whether CSY should search for mRouter TinyTP service
							// instead of just using IRCOMM

#if defined (_DEBUG_CONSOLE_)
public:
	RDebugConsole iConsole;
#endif

	};

const TUint KDTEDeltaInput = (KCTSChanged|KDSRChanged|KDCDChanged|KRNGChanged);
const TUint KDTESignalAll = (KSignalDTEOutputs|KSignalDTEInputs);

const TUint KDCEDeltaInput = (KRTSChanged|KDTRChanged);
const TUint KDCESignalAll = (KSignalDCEOutputs|KSignalDCEInputs);

const TUint KXoffSignal = 0x80000000;


const TUint KFlagBreakOn            = 0x01;
const TUint KFlagBreakTimerPending  = 0x02;
const TUint KFlagAppendServiceLevel = 0x04;
const TUint KFlagAppendExtraParam   = 0x08;

enum TCommFault
	{
	EBadUnit,
	EServiceNotSupported,
	ECancelNotOutstanding,
	EGivenABadSocket,
	ENoMemory,
	ELostProtocol,
    ESessionNotClosed,
    EStrayTimer,
    EBadState,
    EInvalidStateChange
	};

enum TCommPanic
	{
	EBadDescriptor,ENotImplemented,
	};

class IrCOMMUtil
	{
public:
	static void Fault(TCommFault aFault);
	static void Panic(TCommPanic aPanic);
	};

// Inlines

inline TBool CIrCommCirBuf::TerminatorReceived() const
	{ return iTerminatorOffset>=0 ? 1 : 0; }

inline void CIrCommCirBuf::Reset()
	{ iTerminatorOffset=-1; CCirBufBase::Reset(); }

inline void CIrCommCirBuf::SetLengthL(TInt aLength)
    { iTerminatorOffset=-1; CCirBufBase::SetLengthL(aLength); }

inline RSocketServ& CProtocolStarter::SocketServ() const
    { return (RSocketServ&)iSockServ; }

inline TBool CIrCommWriter2::IsWriteZero() const
    { return iClientPtr&&!iClientLength; }

inline TBool CIrCommWriter2::IsClientRequestPending() const
    { return iClientPtr ? 1 : 0; }

inline void CIrCommWriter2::ClearLocalLineChangePending()
    { iLocalLineChangePending=EFalse; }

inline TBool CIrCommReader2::IsClientRequestPending() const
    { return iClientPtr ? 1 : 0; }

inline TBool CIrCommReader2::IsStarted() const
    { return iSocket ? 1 : 0; }

inline void CIrCommReader2::RescanTerminators()
    { iCircBuf->Rescan(*iParent); }

inline TInt CIrCommReader2::ClientQueryReceiveBuffers() const
    { return iCircBuf->Count(); }

inline TInt CIrCommReader2::ClientBufferLength() const
    { return iCircBuf->Length(); }

inline  RSocketServ& CIrCommPort::SocketServ() const
    { return iStarter->SocketServ(); }

inline TIrCOMMSupport CIrCommPort::IrCOMMSupport() const
    { return iIrCOMMSupport;}

inline TBool CIrCommPort::UsingTerminators() const
    { return iConfig.iTerminatorCount>0; }

inline TBool CIrCommPort::AreAnyPending() const
    { return iReader->IsClientRequestPending() || iWriter->IsClientRequestPending() || (iFlags&KFlagBreakTimerPending) ||iInBufHasDataNotify==TRUE; }

inline void CIrCommPort::LockSocketServer()
    { iLocker->Lock(); }

inline void CIrCommPort::SetIrCOMMSupport(TIrCOMMSupport aLevel)
    { iIrCOMMSupport=aLevel; }

inline RSocket* CIrCommPort::Socket() const
    { return iSocket; }

inline TBool CIrCommPort::IsLineFail() const
    { return IsLineFail(iConfig.iHandshake); }

inline TBool CIrCommPort::IsLineObeyed() const
    { return iOutputHeld ? 0 : 1; }

inline TBool CIrCommPort::CheckmRouterTinyTP() const
    { return imRouterTinyTP; }

inline RSocket& CIrCommConnectInitiator::Socket() const
    { return (RSocket&)iCommonSocket; }

inline void CIrCommConnectInitiator::Stop()
    { TRequestStatus* p=0; Stop(p); }

inline void CIrCommConnectResponder::Stop(TBool aBool)
    { TRequestStatus* p=0; Stop(p, aBool); }

inline RSocket& CIrCommConnectResponder::Socket() const
    { return (RSocket&)iDataSocket; }

inline void CIrDialConnectResponder::Stop(TBool aBool)
    { TRequestStatus* p=0; Stop(p, aBool); }

inline RSocket& CIrDialConnectResponder::Socket() const
    { return (RSocket&)iDataSocket; }

inline TInt TIrCOMMParameters::Length() const
    { return iDataFrame.Length(); }

#endif
