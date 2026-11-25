// SS_STD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__SS_STD_H__)
#define __SS_STD_H__

#include <es_prot.h>

#ifdef __WINC__
#define ESOCK_MUTEX_NAME _L("SockSrvStartupMutex")
#endif

#define ESOCK_SEMAPHORE_NAME _L("SockSrvStartupSem")
#define ESOCK_LIB_NAME _L("ESOCK")

#if defined(_DEBUG)
#define __DEBUG_ONLY(c) c
#else
#define __DEBUG_ONLY(c)
#endif

const TUint KDefaultHeapSize=0x1000;
const TUint KMaxHeapSize=0x80000;
const TUint KMinQLength= 20 ;

enum TProtocolPanic
	{
	ENothingToComplete,
	EUnexpectedConnect,
	EUnexpectedClose,
	EUnexpectedConnectData,
	EUnexpectedDisconnectData,
	ERemoveRefused,
	EBadStateUpCall,
	EBadDataCount,
	EBadErrorCall,
	EBadDisconnect,
	EBadByteCount,
	EBadProtocolDescription,
	EErrorCallNotHandled,
	ECantProcessDescriptors,
	ECantProcessMbufs,
	ECantSendDescriptors,
	ECantSendMBufs,
	EDoesNotBindAbove,
	EDoesNotBindBelow,
	ENotListeningSocket,
	EAcceptQueFull,
	};

enum TESockPanic
	{
	ESockBadHandle,
	EBadCancel,
	EConnectingAlready,
	EReadingAlready,
	EWritingAlready,
	ECloseTwice,
	EShutDownTwice,
	EAcceptTwice,
	ETwoIoctls,
	ECantSendToOnConnection,
	EListenNeedsConnection,
	EAlreadyListening,
	ENotListening,
	EBadAccept,
	EBadDescriptor,
	ETwice,
	EBadQueyComplete,
	ENullSocket,
	EMbufManagerNotLoaded,
	ENoResolveFirst,
	ECannotConnect,
	};
//
enum TESockFault
	{
	EInitTwice,
	ECommServerNotRunning,
	ECreateTrapCleanup,
	EMainSchedulerError,
	ESvrCreateServer,
	ESvrStartServer,
	ESocketCreate,
	ENotImplementedYet,
	EOddSock,
	EBadHostResolver,
	EBadServiceResolver,
	EBadNetDBRequest,
	EBadBlocker,
	ESocketCloseNoProtocol,
	EProtocolCloseNoFamily,
	EBadState,
	ETwoReads,
	ETwoWrites,
	ETwoConnects,
	ETwoClose,
	ETwoIoctl,
	ENoSockManData,
	EBadAcceptQueue,
	EStateNull,
	EBadSocketRemove,
	EBadMbufCheck,
	ENegativeSessionCount,
	EMessageFifoNotDeleted,
	ELockManagerAlreadyActive,
	ELockManagerDeleteFault,
	EExclusiveModeBadServerPrio,
	ENormalModeBadServerPrio,
	ELockManagerBadActiveState,
	ESockServPauseWhenActive,
	ESockServCancelPauseWhenNotPaused,
	ESockServCancelPauseWhenActive,
#if defined(DONT_SEARCH_FOR_PROTOCOLS)
	ELoadDummyProtocol=1000,
#endif
	};
//
// Internal socket options bitmaps....
const TUint KOptBlocking=0x00000001;
const TUint KOptDontRoute=0x00000002;
const TUint KOptKeepAlive=0x00000004;
const TUint KOptDebug=0x00000008;
const TUint KOptOOBInLine=0x00000010;
const TUint KOptReUseAddr=0x00000020;
const TUint KOptBroadCast=0x00000040;
const TUint KOptSendBufSet=0x00000080;
const TUint KOptRecBufSet=0x00000100;
const TUint KESocketDefaultOptions=KOptBlocking;
//
class CSocket;
class CHostResolver;
class CServiceResolver;
class CNetDatabase;
class CSocketSchedulerLockManager ;

//
struct Sock
	{
	static TInt Read(const RMessage& aMessage,const TAny *aPtr,TDes8 &aDes,TInt anOffset=0);
	static void Write(const RMessage& aMessage,const TAny *aPtr,const TDesC8 &aDes,TInt anOffset=0);
	static TInt Read(const RMessage& aMessage,const TAny *aPtr,TDes16 &aDes,TInt anOffset=0);
	static void Write(const RMessage& aMessage,const TAny *aPtr,const TDesC16 &aDes,TInt anOffset=0);
	static void PanicClient(const RMessage& aMessage,TESockPanic aPanic);
	};
//
class CSockSession : public CSharableSession
	{
public:
	CSockSession(TSocketServerSessionId aUniqueId);
	CSocket * CSocketFromHandle(TUint aHandle);
	CHostResolver * CHostResolverFromHandle(TUint aHandle);
	CServiceResolver * CServiceResolverFromHandle(TUint aHandle);
	CNetDatabase * CNetDatabaseFromHandle(TUint aHandle);
	void NewSocketL(TUint anAddrFamily,TUint aSocketType,TUint aProtocol);
	void NewSocketL();
	void TransferSocketL();
	void LoadProtocolL(TUint anAddrFamily,TUint aSocketType,TUint aProtocol);
	void UnLoadProtocolL(TUint anAddrFamily,TUint aSocketType,TUint aProtocol);
	void NewHostResolverL(TUint anAddrFamily,TUint aSocketType);
	void NewServiceResolverL(TUint anAddrFamily,TUint aSocketType,TUint aProtocol);
	void NewNetDatabaseL(TUint anAddrFamily,TUint aSocketType);
	virtual ~CSockSession();
	virtual void CreateL(const CServer &aServer);
	void AddProtocolL(CProtocolBase * const aProtocol);
	void RemoveProtocolL(CProtocolBase * const aProtocol);
	void NumProtocols(void);
	void ProtocolInfo(void);
	void ProtocolInfoByName(void);
	void PanicClient(TESockPanic aPanic);
	void WriteSubSessionHandle(TInt aHandle);
	virtual void ServiceL(const RMessage &aMessage);
	void DeleteSocket(TUint aHandle);
	void DeleteSocket(CSocket &aSocket);
	void DontCompleteCurrentRequest();
	void SetReturn(TInt aReturn,TInt anError=0,TUid anOwner=TUid::Null());
	void FreeSocketMemory();
	void InstallExtension();
	void DisableSockServSessInterfaceTracking(); // Do not hold interfaces open for this socket server session
	inline const RMessage& Message() const;
private:
	CObjectIx* iSockets;
	CObjectIx* iHostResolvers;
	CObjectIx* iServResolvers;
	CObjectIx* iNetDbs;
	CArrayFixFlat<CProtocolBase *> *iProtocols;
	TBool iComplete;
	TInt iReturn;
	TInt iLastError;
	TUid iLastErrorOwner;
	RMessage iOurMessage;
	TSocketServerSessionId iThisSockServSessId;	// Used to distinguish this socket server session from any other
	};
//
class CSocketServer : public CServer
	{
public:
	enum {EPriority=0};
public:
	static CSocketServer* New();
	virtual CSharableSession* NewSessionL(const TVersion &aVersion)const;
	inline TDblQueIter<CSession *>& SessionQ();
	static void FreeMemory(TAny*);
	void DoFreeMemory();
	void PauseSocketServ();
	void ResumeSocketServ();
	void ChangePriority(TInt aPriority);
private:
	void CancelPauseSocketServ();
	CSocketServer(TInt aPriority);
private:
	TBool iSocketServPaused;
	// Give each session on the socket server a unique id - can then track
	// which sessions use which interfaces via their id
	mutable TSocketServerSessionId iSockSessionUniqueId; // need to change this from within const method NewSessionL
	};
//

class TAcceptQEntry
	{
public:
	CServProviderBase *iSSP;
	HBufC8 *iConnectData;
	TInt iConnectDataError;
	};

class CSockSubSession : public CObject
	{
friend class CSockSession;
protected:
	CSockSubSession();
	void Read(const TAny *aPtr,TDes8 &aDes,TInt anOffset=0) const;
	void Write(const TAny *aPtr,const TDesC8 &aDes,TInt anOffset=0) const;

#ifdef _UNICODE
	void Read(const TAny *aPtr,TDes16 &aDes,TInt anOffset=0) const;
	void Write(const TAny *aPtr,const TDesC16 &aDes,TInt anOffset=0) const;
#endif

protected:
	CSockSession *iSession;
public:
	inline void DontCompleteCurrentRequest() const;
	inline void SetReturn(TInt aReturnValue,TInt anError=0,TUid anOwner=TUid::Null()) const;
#if defined(__GCC32__)
	const RMessage& Message() const;
#else
	inline const RMessage& Message() const;
#endif
	};

class ProtocolManager;
class Nif;
class CSocket : public CSockSubSession, public MSocketNotify
	{
	friend class ProtocolManager;
	friend class Nif;

private:
	enum TSocketState
		{
		ESStateNull=-1,
		ESStateCreated=0,
		ESStateOpeningActive,
		ESStateOpeningPassive,
		ESStateOpen,
		ESStateConnected,
		ESStateDisconnected,
		ESStateClosing,
		ESStateShuttingDown,
		ESStateDead,
		ESStateError,
		};
public:
//
	static CSocket * NewL(TServerProtocolDesc *aServiceInfo,CSockSession *aSession,CProtocolBase* aProt);
	virtual ~CSocket();
	void CreateL(TServerProtocolDesc *aServiceInfo,CSockSession *aSession,CProtocolBase* aProt);
   	CSocket();
	inline void SetSSP(CServProviderBase* anSSP);
// Request service routines.
	void ConnectL();
	void ShutdownL();
	void CloseSocket();
	void ListenL();
	void Accept();
//
	void AutoBind();
	void Bind();
	void RemoteName();
	void LocalName();
	void SetLocalName();
//
	void SetSockOptionL();
	void GetSockOptionL();
	void IoctlL();
	void GetDisconnectData( ) const;
	void InformSAPofSockServSessId(TSocketServerSessionId aSockServSessId);
//
	void SendL();
	void RecvL();
//
	inline void CancelSend();
	inline void CancelRecv();
	void CancelConnect();
	void CancelAccept();
	void CancelIoctl();
	void CancelAll();
//
	void GetInfo();
	void FreeMemory();
	void ReferenceL();
//
	TPtr8 IoctlBuffer();
//
// SSP Upcalls - from MSocketNotify
	void NewData(TUint aCount);
    void CanSend();
    void ConnectComplete();
	void ConnectComplete(const TDesC8 &aConnectData);
    void ConnectComplete(CServProviderBase &anSSP);
	void ConnectComplete(CServProviderBase &anSSP,const TDesC8 &aConnectData);
	void CanClose(TDelete aDelete=EDelete);
    void CanClose(const TDesC8 &aDisconnectData,TDelete aDelete=EDelete);
	void Error(TInt anError,TUint anOperationMask);
	void Disconnect( );
	void Disconnect(TDesC8 &aDisconnectData);
	void IoctlComplete(TDesC8 *aBuf);
//
// Utitlity functions for testing state and capabilities
//
	inline TUint IsConnectionOriented() const;
	inline TUint IsConnectionLess()const;
	inline TUint IsDataGram() const;
	inline TUint IsStream() const;
	inline TUint IsPseudoStream() const;
	inline TUint IsReliable() const;
	inline TUint DeliversInOrder() const;
	inline TUint IsMessageBased() const;
	inline TUint CanSendUrgentData() const;
	inline TUint CanSendConnectData() const;
	inline TUint CanSendDisconnectData() const;
	inline TUint CanBroadcast() const;
	inline TUint SupportsMultiPoint() const;
	inline TUint SupportsQOS() const;
	inline TUint IsWriteOnly() const;
	inline TUint IsReadOnly() const;
	inline TUint SupportsGracefulClose() const;
	inline TUint CanReconnect() const;
	inline TUint SupportsPeek() const;

//
private:
//
	TBool CheckRunningAndSetReturn() const;
//
// Utility functions for handling blocked messages.
//
	enum EBlockingFlags {EBlockedClose=0x01,EBlockedConnect=0x02,EBlockedIoctl=0x04,
						 EBlockedRead=0x08, EBlockedWrite=0x10,EWriteFlowedOff=0x20,
						 EReadStopped=0x40, EWriteStopped=0x80};

	inline void SetBlockedRead();
	inline void SetBlockedWrite();
	inline void SetBlockedConnect(const RMessage &aMessage);
	inline void SetBlockedClose(const RMessage &aMessage);
	inline void SetBlockedIoctl(const RMessage &aMessage);

	inline TBool IsBlockedRead();
	inline TBool IsBlockedWrite();
	inline TBool IsBlockedConnect();
	inline TBool IsBlockedClose();
	inline TBool IsBlockedIoctl();
	
	void CompleteRead(TInt anError);
	void CompleteWrite(TInt anError);
	void CompleteConnect(TInt anErr);
	void CompleteClose(TInt anErr);
	void CompleteIoctl(TInt anErr);
	void DoCompleteAccept();
//
	void DrainStreamProtocolL( );
	void FillStreamProtocolL( );
//
	void AcceptSetup(const CSocket& aSocket,CServProviderBase &anSSP);
    TUint SelectConditionsReady();
	TBool CheckReadStopped();
	void TryToCompleteSelectIoctl();

//
private:

	CServProviderBase *iSSP;
	CProtocolBase* iProtocol;
//
	TSocketState iState;
	TBool iIsBound;
	TInt iDataAvailable;
	TInt iSendOffset;
	TInt iRecOffset;
	TInt iSendByteCount;
	TInt iRecByteCount;
	TInt iSendFlags;
	TInt iRecvFlags;
	TBool iRecvOneOrMore;
	TSockXfrLength const *iSendLength;
	TSockXfrLength const *iRecvLength;
	TSockAddr *iRecvFromAddr;
	TSockAddr *iSendToAddr;
//
	RMessage iReadMsg;
	RMessage iWriteMsg;
	RMessage iBlockedClose;
	RMessage iBlockedConnect;
	RMessage iBlockedIoctl;
	TUint iBlockedOperations;
//
	TInt iError;
//
	TUint iOptions;
	TProtocolDesc *iProtocolInfo;
//
	HBufC8 *iRecBuf;
	TInt iRecBufSize;
	HBufC8 *iSendBuf;
	TInt iSendBufSize;
	HBufC8 *iDisconnectData;
	TInt iDisconnectDataError;
//
	CCirBuf<TAcceptQEntry> *iAcceptQ;
	TInt iSelectFlags;
	};

class CHostResolver : public CSockSubSession, public MResolverNotify
	{
	friend class ProtocolManager;
private:
	CHostResolver();
	void CreateL(CSockSession *aSession);
public:
	static CHostResolver * NewL(CSockSession *aSession);
//
	inline void SetResolver(CHostResolvProvdBase* aResolver);
	void GetByName();
	void Next();
	void GetByAddress();
	void GetHostName();
	void SetHostName();
	virtual ~CHostResolver();
	void Cancel();
	void QueryComplete(TInt anError);
private:
	CHostResolvProvdBase* iRSP;
	TBool iBusy;
	RMessage iBlockedReq;
	TNameRecord iNameRec;
	TInt iCount;
	TInt iCurrentOp;
	};

class CServiceResolver : public CSockSubSession, public MResolverNotify
	{
	friend class ProtocolManager;
private:
	CServiceResolver();
	void CreateL(CSockSession *aSession);
public:
//
	static CServiceResolver* NewL(CSockSession* aSession);
	inline void SetResolver(CServiceResolvProvdBase* aResolver);
	void GetByName();
	void GetByNumber();
	void RegisterService();
	void RemoveService();
	virtual ~CServiceResolver();
	void Cancel();
	void QueryComplete(TInt anError);
private:
	CServiceResolvProvdBase* iRSP;
	RMessage iBlockedReq;
	TBool iBusy;
	TServiceName iNameBuf;
	TInt32 iPortNum;
	};

class CNetDatabase : public CSockSubSession, public MResolverNotify
	{
	friend class ProtocolManager;
private:
	CNetDatabase();
public:
	static CNetDatabase * NewL(CSockSession *aSession);
	void RequestL();
	inline void SetProvd(CNetDBProvdBase* aResolver);
	virtual ~CNetDatabase();
	void QueryComplete(TInt anError);
	void Cancel();
private:
	CNetDBProvdBase* iRSP;
	RMessage iBlockedReq;
	TBool iBusy;
	HBufC8* iBuf;
	TPtr8* iBufPtr;
	};

GLREF_C void Fault(TESockFault aFault);
GLREF_C void Panic(TProtocolPanic aPanic);
GLREF_C TInt SocketServerThread(TAny *);

class TSockManData;
class CSockSession;
class CSocketScheduler : public CActiveScheduler
	{
public:
	static void New();
    virtual void Error(TInt anError) const;
    static TBool CheckLockedL(CSockSession* aSession);
    static void SetLockedL(CSockSession* aSession);
    static TInt Unlock(CSockSession* aSession);
	static void UnlockForClose(CSockSession* aSession);
    virtual void WaitForAnyRequest();
	inline static void SetGlobals(TSockManData* aGlobals);
	inline static void SetWaitHook(TCallBack* aCall);
	inline static TSockManData* Globals();
private:
	~CSocketScheduler();
    TSockManData* iGlobals;
	CSockSession* iCurrentSession;
	TCallBack* iWaitHook;
//    CSockSession* iLockedSession;
	CSocketSchedulerLockManager* iLockManager ;
	};

class CSocketSchedulerLockManager : public CActive 
{

public :
	~CSocketSchedulerLockManager() ;
	static CSocketSchedulerLockManager* NewL() ;
	TInt PerformUnlockActions(CSockSession* aSession) ;
	void PerformLockActionsL(CSockSession* aLockedSession) ;
	void PerformCloseActions(CSockSession* aLockedSession) ;
    TBool CheckLockedL(CSockSession* aSession);
    CSockSession* GetLockedSession();

private :
	void ResumeSocketServ();

	void ConstructL () ;
	CSocketSchedulerLockManager();
	void RunL() ;
	void DoCancel() ;
    CSockSession* iLockedSession;
    RArray<RMessage> iLockedMessageFifo;
} ;
#include "ss_std.inl"	

#endif
