/**
@file SS_STD.H


Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
*/

#if !defined(__SS_STD_H__)
#define __SS_STD_H__

#include <es_prot.h>
#include <es_enum.h>
#include <e32base.h> // for TTime
#include "connpref.h" // for TConnPref
#include <es_mbman.h>

#ifndef __WINC__
#include <cfmsgs.h>
#include <cfshared.h>
#include <cfutil.h>
#else
#define ESOCK_MUTEX_NAME _L("SockSrvStartupMutex")
#endif

/**
@internalComponent
*/
#define ESOCK_SEMAPHORE_NAME _L("SockSrvStartupSem")

/**
@internalComponent
*/
#define ESOCK_LIB_NAME _L("ESOCK")
#define ESOCK_SERVER_LIB_NAME _L("ESOCKSVR")

#if defined(_DEBUG)
/**
@internalComponent
*/
#define __DEBUG_ONLY(c) c
#else
#define __DEBUG_ONLY(c)
#endif

/**
@internalAll
*/
const TUint KDefaultHeapSize=0x1000;

/**
@internalAll
*/
const TUint KMaxHeapSize=0x80000;

/**
@internalComponent
*/
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
	EProviderIncomplete
	};

/** The panic numbers associated with the eSock panic category.
@publishedAll */
//This is internal.
enum TESockPanic
	{
	ESockBadHandle,     ///< panic numbers associated with Socket Bad Handle 
	EBadCancel,         ///< panic numbers associated with Bad Cancel
	EConnectingAlready, ///< panic numbers associated with Connecting Already
	EReadingAlready,    ///< panic numbers associated with Reading Already
	EWritingAlready,    ///< panic numbers associated with Writing Already
	ECloseTwice,        ///< panic numbers associated with ShutDownTwice
	EShutDownTwice,     ///< panic numbers associated with
	EAcceptTwice,       ///< panic numbers associated with Accept Twice
	ETwoIoctls,         ///< panic numbers associated with Two Ioctls
	ECantSendToOnConnection, ///< panic numbers associated with Can't Send To On Connection
	EListenNeedsConnection,  ///< panic numbers associated with Listen Needs Connection
	EAlreadyListening,  ///< panic numbers associated with Already Listening
	ENotListening,      ///< panic numbers associated with Not Listening
	EBadAccept,         ///< panic numbers associated with Bad Accept
	EBadDescriptor,     ///< panic numbers associated with Bad Descriptor
	ETwice,             ///<panic numbers associated with Twice
	EBadQueyComplete,   ///< panic numbers associated with Bad Quey Complete
	ENullSocket,        ///< panic numbers associated with Null Socket
	EMbufManagerNotLoaded, ///< panic numbers associated with Mbuf Manager Not Loaded
	ENoResolveFirst,    ///< panic numbers associated with No Resolve First
	ECannotConnect,     ///< panic numbers associated with Cannot Connect
	ENoQueryFirst       ///< panic numbers associated with No Query First
    };
/** The panic numbers associated with the eSock Fault panic category. 
@publishedAll */
// This is internal.
enum TESockFault
	{
	EInitTwice,             ///< Twice initialization eSock Fault
	ECommServerNotRunning,  ///< Communication server not running eSock Fault
	ECreateTrapCleanup,     ///< Create Trap Cleanup eSock Fault
	EMainSchedulerError,    ///< Main Scheduler Error eSock Fault
	ESvrCreateServer,       ///< Svr Create Server eSock Fault
	ESvrStartServer,        ///< Svr Start Server eSock Fault
	ESocketCreate,          ///< Socket Create eSock Fault
	ENotImplementedYet,     ///< Not Implemented Yet eSock Fault
	EOddSock,               ///< Odd Socket eSock Fault
	EBadHostResolver,       ///< Bad Host Resolver eSock Fault
	EBadServiceResolver,    ///< Bad Service Resolver eSock Fault
	EBadNetDBRequest,       ///< Bad NetDB Request eSock Fault
	EBadBlocker,            ///< Bad Blocker eSock Fault
	ESocketCloseNoProtocol, ///< Socket CloseNo Protocol eSock Fault
	EProtocolCloseNoFamily, ///< Protocol Close No Family eSock Fault
	EBadState,              ///< Bad State eSock Fault
	ETwoReads,              ///< Two Reads eSock Fault
	ETwoWrites,             ///< Two Writes eSock Fault
	ETwoConnects,           ///< Two Close eSock Fault
	ETwoClose,              ///< eSock Fault
	ETwoIoctl,              ///< Two Ioctl eSock Fault
	ENoSockManData,         ///< No Socket ManData eSock Fault
	EBadAcceptQueue,        ///< Bad Accept Queue eSock Fault
	EStateNull,             ///< State Null eSock Fault
	EBadSocketRemove,       ///< Bad Socket Remove eSock Fault
	EBadMbufCheck,          ///< Bad Mbuf Check eSock Fault
	ENegativeSessionCount,  ///< Negative Session Count eSock Fault
	EMessageFifoNotDeleted, ///< Message Fifo Not Deleted eSock Fault
	EBadConnection          ///< Bad Connection eSock Fault
#if defined(DONT_SEARCH_FOR_PROTOCOLS)
	ELoadDummyProtocol,     ///< Load Dummy Protocol eSock Fault
#endif
	};

/**
Internal socket options bitmap....
@internalComponent
*/
const TUint KOptBlocking=0x00000001;

/**
Internal socket options bitmap....
@internalComponent
*/
const TUint KOptDontRoute=0x00000002;

/**
Internal socket options bitmap....
@internalComponent
*/
const TUint KOptKeepAlive=0x00000004;

/**
Internal socket options bitmap....
@internalComponent
*/
const TUint KOptDebug=0x00000008;

/**
Internal socket options bitmap....
@internalComponent
*/
const TUint KOptOOBInLine=0x00000010;

/**
Internal socket options bitmap....
@internalComponent
*/
const TUint KOptReUseAddr=0x00000020;

/**
Internal socket options bitmap....
@internalComponent
*/
const TUint KOptBroadCast=0x00000040;

/**
Internal socket options bitmap....
@internalComponent
*/
const TUint KOptSendBufSet=0x00000080;

/**
Internal socket options bitmap....
@internalComponent
*/
const TUint KOptRecBufSet=0x00000100;

/**
Internal socket options bitmap....
@internalComponent
*/
const TUint KESocketDefaultOptions=KOptBlocking;

//
class CSocket;
class CHostResolver;
class CServiceResolver;
class CNetDatabase;
class CConnection;
class TSockManData;

/**
@internalComponent
*/
struct Sock
	{
	static TInt Read(const RMessage2& aMessage,TInt aSrcParamIndex,TDes8 &aDes,TInt anOffset=0);
	static void Write(const RMessage2& aMessage,TInt aDstParamIndex,const TDesC8 &aDes,TInt anOffset=0);
	static TInt Read(const RMessage2& aMessage,TInt aSrcParamIndex,TDes16 &aDes,TInt anOffset=0);
	static void Write(const RMessage2& aMessage,TInt aDstParamIndex,const TDesC16 &aDes,TInt anOffset=0);
	static void Write(const RMessage2& aMessage,TInt aDstParamIndex,const TPckg<TUint32>& aDes,TInt anOffset = 0);
	static void PanicClient(const RMessage2& aMessage,TESockPanic aPanic);
	};

class CSockSession;
class MSockSessionObserver
/**
Notifier class used by observers of CSockSession events.
Internal socket options bitmaps....

@internalComponent
*/
	{
public:
	/** Event indicating session is about to close */
	virtual void SessionClosing(const CSockSession* aSession)=0;		
	};


class CSockSession : public CSession2
/**
Server side representation of RSocketServ.

@internalTechnology
*/
	{
public:
	CSockSession();
	CSocket * CSocketFromHandle(TUint aHandle);
	CHostResolver * CHostResolverFromHandle(TUint aHandle);
	CServiceResolver * CServiceResolverFromHandle(TUint aHandle);
	CNetDatabase * CNetDatabaseFromHandle(TUint aHandle);
	CConnection* CConnectionFromHandle(TUint aHandle);
	CSocket* NewSocketL(TUint anAddrFamily,TUint aSocketType,TUint aProtocol);
	void NewSocketL();
	void NewSocketWithConnectionL();
	void TransferSocketL();
	void LoadProtocolL(TUint anAddrFamily,TUint aSocketType,TUint aProtocol);
	void UnLoadProtocolL(TUint anAddrFamily,TUint aSocketType,TUint aProtocol);
	CHostResolver* NewHostResolverL(TUint anAddrFamily,TUint aSocketType);
	void NewHostResolverWithConnectionL(TUint anAddrFamily,TUint aSocketType, TInt aHandle);
	void NewServiceResolverL(TUint anAddrFamily,TUint aSocketType,TUint aProtocol);
	void NewNetDatabaseL(TUint anAddrFamily,TUint aSocketType);
	CConnection* NewConnectionL();
	CConnection* NewConnectionL(const TName& aName);

	virtual ~CSockSession();
	void AddProtocolL(CProtocolBase * const aProtocol);
	void RemoveProtocolL(CProtocolBase * const aProtocol);
	void NumProtocols(void);
	void ProtocolInfo(void);
	void ProtocolInfoByName(void);
	void PanicClient(TESockPanic aPanic);
	void WriteSubSessionHandle(TInt aHandle);
	virtual void ServiceL(const RMessage2 &aMessage);
	void DeleteSocket(TUint aHandle);
	void DeleteSocket(CSocket &aSocket);
	void DontCompleteCurrentRequest();
	void SetReturn(TInt aReturn,TInt anError=0,TUid anOwner=TUid::Null());
	void FreeSocketMemory();
	void InstallExtension();
	inline const RMessage2& Message() const;
	inline TSockManData* SockManGlobals() const;
	CInterface* FindDefaultInterface();
	void StoreOwnerInfo();
	TBool GetOwnerInfo(TProcessId& aProcId, TUidType& aUidType);

  	// Methods implementing observer functionality
	TInt RegisterObserver(MSockSessionObserver* aObserver);
	TInt DeRegisterObserver(MSockSessionObserver* aObserver);

protected:
	void ConnectSocketL(TInt aHandle);
	void SendToSocketL(TInt aHandle);
	void NotifyObservers();
	virtual void CreateL();

private:
	TBool UpdateDefaultInterface(CInterface* aIface, CInterface*& aIfaceDefault);

#ifdef _DEBUG_SOCKET_FUNCTIONS
	void LogServerState();
#endif

private:
	CObjectIx* iSockets;
	CObjectIx* iHostResolvers;
	CObjectIx* iServResolvers;
	CObjectIx* iNetDbs;
	CObjectIx* iConnections;

	CArrayFixFlat<CProtocolBase *>*       iProtocols;

	TBool iComplete;
	TInt  iReturn;
	TInt  iLastError;
	TUid  iLastErrorOwner;

	RMessage2 iOurMessage;

	TSockManData* iSockManGlobals;					// cache pointer to global variables to avoid TLS lookups

	TBool iOwnerInfoValid;
	TProcessId iProcessId;
	TUidType iUidType;

	RPointerArray<MSockSessionObserver> iObservers;	// Observers of this CSockSession
	};
#ifndef __WINC__
class CSocketServerChannelHandler;
#endif
class CSocketServer : public CServer2
/**
@internalComponent
*/
	{
public:
	enum {EPriority=0};
public:
#ifndef __WINC__
	static CSocketServer* NewL(CommsFW::RCFChannel::TMsgQueues aRxQueues, CommsFW::RCFChannel::TMsgQueues aTxQueues);
    void ConstructL(CommsFW::RCFChannel::TMsgQueues aRxQueues, CommsFW::RCFChannel::TMsgQueues aTxQueues);
#else
	static CSocketServer* NewL();
#endif
	~CSocketServer();
	virtual CSession2* NewSessionL(const TVersion& aVersion,const RMessage2& aMessage) const;
	inline TDblQueIter<CSession2 *>& SessionQ();
	static void FreeMemory(TAny*);
	void DoFreeMemory();
#ifndef __WINC__
	void CFShutdownMessageReceived(const CommsFW::TCFShutdownMsg& aMsg);
#endif
private:
	CSocketServer(TInt aPriority);
#ifndef __WINC__
	CSocketServerChannelHandler* iChannelHandler;
#endif
	};


#ifndef __WINC__
class CSocketServerChannelHandler:public CommsFW::CCFModuleChannelHandler
/**
@internalComponent
*/
	{
	public:
		static CSocketServerChannelHandler* NewL(CommsFW::RCFChannel::TMsgQueues aRxQueues,
			CommsFW::RCFChannel::TMsgQueues aTxQueues, CSocketServer* aServer);
	private:
		CSocketServerChannelHandler(CSocketServer* aServer);
		virtual void CFMessageShutdown(const CommsFW::TCFShutdownMsg& aMessage);
	private:
		CSocketServer* iServer;
	};
#endif
//

class TAcceptQEntry
/**
@internalComponent
*/
	{
public:
	CServProviderBase *iSSP;
	HBufC8 *iConnectData;
	TInt iConnectDataError;
	};

class CSockSubSession : public CObject
/**
@internalComponent
*/
	{
friend class CSockSession;
friend class CInterface;					// for Session()
public:
	TBool GetOwnerInfo(TProcessId& aProcessId, TUidType& aUidType, TThreadId& aThreadId);
protected:
	CSockSubSession();
	void Read(const RMessage2& aMessage,TInt aSrcParamIndex,TDes8 &aDes,TInt anOffset=0) const;
	void Read(TInt aSrcParamIndex,TDes8 &aDes,TInt anOffset=0) const;
    void Write(const RMessage2& aMessage,TInt aDstParamIndex,const TDesC8 &aDes,TInt anOffset=0) const;
    void Write(TInt aDstParamIndex,const TDesC8 &aDes,TInt anOffset=0) const;
	void Write(const RMessage2& aMessage,TInt aDstParamIndex,const TPckg<TUint32>& aDes,TInt anOffset = 0) const;
	void Write(TInt aDstParamIndex,const TPckg<TUint32>& aDes,TInt anOffset = 0) const;

#ifdef _UNICODE
    void Read(const RMessage2& aMessage,TInt aSrcParamIndex,TDes16 &aDes,TInt anOffset=0) const;
    void Read(TInt aSrcParamIndex,TDes16 &aDes,TInt anOffset=0) const;
    void Write(const RMessage2& aMessage,TInt aDstParamIndex,const TDesC16 &aDes,TInt anOffset=0) const;
    void Write(TInt aDstParamIndex,const TDesC16 &aDes,TInt anOffset=0) const;
#endif // _UNICODE

	void StoreOwnerInfo();
	CSockSession* Session() { return iSession; }; // This could be a reference instead.

protected:
	CSockSession *iSession;
	TThreadId iThreadId;
public:
	inline void DontCompleteCurrentRequest() const;
	inline void SetReturn(TInt aReturnValue,TInt anError=0,TUid anOwner=TUid::Null()) const;
#if defined(__GCC32__)
	const RMessage2& Message() const;
#else
	inline const RMessage2& Message() const;
#endif
	};

class CInterfaceAsyncDtor : public CAsyncOneShot
/**
Class for asynchronously destroying CInterface instances.

@internalComponent
*/
	{
public:
	CInterfaceAsyncDtor();
	void AsyncDelete(CInterface& aInterface);
private:
	void RunL();
private:
	TDblQue<CInterface> iDeleteInterfaces;		// list of interfaces to destroy
	};

class CSubInterface;
class CInterface : public CBase, public MConnectionNotify, public MSockSessionObserver
/**
Class representing an underlying interface.  CSocket, CHostResolver and CConnection objects
are each associated with one of these objects which, in turn, communicates with Nifman on
their behalf.

MConnectionNotify is used to observe events from CNifSession in Nifman (primarily Progress
Notification).  MSockSessionObserver is used to observe events on CSockSession's (session
closing for the idle timer implementation).

@internalComponent
*/
	{
	friend class CSocket;						// for ConnectionInfo() (CSocket::NoBearer())
	friend class CSubInterface;					// for iConnections
	friend class SocketServer;					// for iLink
	friend class CInterfaceAsyncDtor;			// for iLink
public:
	// methods for creating and looking up CInterface instances
	static CInterface* NewL(CSocket&);
	static CInterface* NewL(CHostResolver&);
	static CInterface* NewL(CConnection&);
	static CInterface* FindByConnectionInfo(const TDesC8& aConnectionInfo, TSockManData* aGlobal);

	static TBool IsLocalBearer(const TDesC8& aConnectionInfo);	// does connection info refer to local interface ?

	inline TBool IsSelectionComplete() const;
	inline TBool SubSessionsPresent() const;
	inline TBool IsNewBearer(const TDesC8& aConnectionInfo) const;
	inline void AddMonitor();

	// Methods for associating and disassociating subsessions
	void Join(CSocket&);
	void Join(CHostResolver&);
	void Join(CConnection&);

	void Leave(CSocket&, TBool aDeleteInterface = ETrue);
	void Leave(CHostResolver&);
	void Leave(CConnection&, TBool aDeleteInterfaceIfLast = ETrue);
	
	void JoinAndSetConnection(CSocket&);
	void JoinAndSetConnection(CHostResolver&);

	//	methods that subsessions are intended to use (especially CConnection)
	void StartL(TConnStartType aType);
	void StartL(TConnStartType aType, const TConnPref& aPrefs);
	void AttachToConnectionL(const TDesC8& aConnectionInfo, TBool aMonitorAttach);
	void Stop(TInt aError);
	void Stop(TSubConnectionUniqueId aSubConnectionUniqueId, TInt aError);
	void ProgressL(TNifProgressBuf& aBuffer) const;
	// no progress for subconnections, handled by CSubConnection
	void LastProgressError(TNifProgressBuf& aBuffer);
	void RequestServiceChangeNotificationL();
	void CancelServiceChangeNotification();
	void GetIntSettingL(const TDesC& aSettingName, TUint32& aValue);			// CommDb parameter access
	void GetBoolSettingL(const TDesC& aSettingName, TBool& aValue);
	void GetDes8SettingL(const TDesC& aSettingName, TDes8& aValue);
	void GetDes16SettingL(const TDesC& aSettingName, TDes16& aValue);
	HBufC* GetLongDesSettingLC(const TDesC& aSettingName);
	void EnumerateConnectionsL(RPointerArray<TConnectionInfo>& aConnectionInfoPtrArray);	// information enumeration
	void EnumerateClientsL(TUint& aCount, HBufC8*& aClientInfoBuffer);
	void EnumerateSocketsL(TUint& aCount, HBufC8*& aSocketInfoBuffer);
	TInt EnumerateSubConnectionsL(TUint& aCount);
	TBool AllInterfaceNotificationL();
	TBool AllSubConnectionNotificationEnableL();
	void ControlL(TUint aOptionLevel, TUint aOptionName, TDes8& aOption);
	void SetUsageProfile(TUint aProfile);
	TInt GetSubConnectionInfo(TUint aIndex, TDes8& aSubConnectionInfo);
	TInt GetSubConnectionInfo(TDes8& aSubConnectionInfo);
	TInt CancelAllSubConnectionNotification();
	TInt DataTransferred(TSubConnectionUniqueId aSubConnectionUniqueId, TUint& aUplinkVolume, TUint& aDownlinkVolume);
	TInt DataTransferredCancel(TSubConnectionUniqueId aSubConnectionUniqueId);

	// MConnectionNotify callback interface from Nifman
	virtual void SelectionComplete(TInt aError, const TDesC8& aSelectionInfo);
	virtual void ConnectionError(TInt aError);
	virtual void LinkLayerOpen(TInt aError);
	virtual void LinkLayerClosed(TInt aError);
	virtual void ProgressNotification(TInt aStage, TInt aError);
	virtual void ProgressNotification(TSubConnectionUniqueId aSubConnectionUniqueId, TInt aStage, TInt aError);
	virtual void ServiceChangeNotification(TUint32 aId, const TDesC& aType);
	virtual void InterfaceStateChangeNotification(TDesC8& aInfo);
	virtual void NotifyDataSent(TSubConnectionUniqueId aSubConnectionUniqueId, TUint aUplinkVolume);
	virtual void NotifyDataReceived(TSubConnectionUniqueId aSubConnectionUniqueId, TUint aDownlinkVolume);
	virtual void SubConnectionEvent(const TSubConnectionEvent& aSubConnectionEvent);

protected:
	CInterface();
	~CInterface();
	void DeleteThisInstance();

private:
	inline CConnectionProvdBase* Provider() const;	// return underlying provider
	inline const TDesC8& ConnectionInfo() const;	// return the connection information
	inline void DeleteConnectionInfo();				// free up memory taken up by connection information
	inline TBool OnGlobalList() const;				// check if instance in on global interface list

	// Methods concerned with sub-session/interface associations
	void CreateL(CSocket&);
	void CreateL(CHostResolver&);
	void CreateL(CConnection&);
	void AddToGlobal();								// add to global list of CInterface instances
	void RemoveFromGlobal();						// remove from global list
	TInt StoreSelection(const TDesC8& aInfo);		// store connection information
	void RelocateTo(CInterface& aDestination);		// methods for moving subsessions between CInterface instances
	void Receive(CSocket& aCSocket);
	void Receive(CHostResolver& aHostResolver);
	void Receive(CConnection& aConnection);

	void AsyncDelete();								// asynchronous destructor
	void UpdateUsageProfile();
	void ErrorSocketsAndHostResolvers(TInt aError);	// Post an error to all sockets and host resolvers associated with interface
	void ProcessSocketsAndHostResolvers(const TDesC8& aConnectionInfo);
	void SignalLinkUpToHostResolvers();

	// methods used to (de)register as an observer of a CSockSession
	TInt RegisterSessionObserver(CSockSubSession& aSubSession);
	void DeRegisterSessionObservers();

	// used internally to implement the MConnectionNotify SelectionComplete() and
	// ProgressNotification() callbacks
	void ProviderNotification(TInt aStage, TInt aError, const TDesC8& aInfo);

	// MSockSessionNotify method used to observe CSockSession events
	void SessionClosing(const CSockSession* aSession);

	// Used to find correct subinterface to which to route events
	TInt FindSubInterface(TSubConnectionUniqueId aSubConnectionUniqueId);
	TInt FindPositionForInsertInOrder(TSubConnectionUniqueId aSubConnectionUniqueId);

	//Used to check if a client information is in the client information list.
	TBool DoesConnectionInfoExist(TDesC8& aInfoBuf, TInt aCount, TConnectionClientInfo& aInfo);

private:
	CConnectionProvdBase* iProvider;		// Pointer to Nifman connection provider

	// Linked lists storing all subsession objects associated with the instance.
	TDblQue<CSocket> iSockets;				
	TDblQue<CHostResolver> iHostResolvers;
	TDblQue<CConnection> iConnections;		
	TInt iSocketCount;
	TInt iHostResolverCount;
	TInt iConnectionCount;
	TInt iConnectionMonitorCount;			// CConnection instances in iConnectionCount that are in monitor mode

	RPointerArray<CSockSession> iSessions;	// Sessions associated with this interface
	RPointerArray<CSubInterface> iSubInterfaces; // Sub interfaces associated with this interface
	HBufC8* iConnectionInfo;				// Connection information received from Nifman on selection completion
	TDblQueLink iLink;						// for TSockManData::iInterfaces linked list.
	TBool iSelectionComplete:1;				// whether interface has passed KFinishedSelection stage
	TBool iOnGlobalList:1;					// whether this instance is on the global list or not
	TBool iOnDtorList:1;					// whether this instance is on the async d'tor list or not
	TBool iNotificationsEnabled:1;			// whether subconnection notifications have been enabled
	TUint iUsageProfile;					// what usage profile has been communicated to Nifman
	};

class CSubConnection;
class CSubInterface : public CBase
/**
Mux/demux for subconnections between the connection provider and each clients CSubConnection objects

@internalComponent
*/
	{
public:
	static CSubInterface* NewL(TSubConnectionUniqueId aThisSubConnectionsUniqueId, CInterface* aOwningInterface);
	~CSubInterface();

	// Downcalls from CSubConnection
	// need some way of tracking which client issued which granularity request
	// perhaps rather than passing granularities, we could scan all CSubConnections for them?
	TInt DataSentNotificationRequest(TUint aRequestedGranularity, TUint aRequestedNotificationVolume);
	TInt DataSentNotificationCancel();
	TInt DataReceivedNotificationRequest(TUint aRequestedGranularity, TUint aRequestedNotificationVolume);
	TInt DataReceivedNotificationCancel();

	// Upcalls from connection provider via CInterface
	TInt ProgressNotification(TInt aStage, TInt aError, const TDesC8& aInfo);
	TInt NotifyDataTransferred(TUint aUplinkVolume, TUint aDownlinkVolume);
	TInt NotifyDataSent(TUint aUplinkVolume);
	TInt NotifyDataReceived(TUint aDownlinkVolume);

	//	Calls from CInterface
	TInt Join(CConnection& aConnection);
	void Leave(CConnection& aConnection);

	//	Access this subconnections unique id for search purposes
	inline TSubConnectionUniqueId SubConnectionUniqueId();

private:
	CSubInterface(TSubConnectionUniqueId aThisSubConnectionsUniqueId, CInterface* aOwningInterface);
	void ConstructL();

	TInt CalculateNewUplinkGranularity(TUint aRequestedGranularity);
	TInt CalculateNewDownlinkGranularity(TUint aRequestedGranularity);

	TInt SetNextUplinkGranularity();
	TInt SetNextDownlinkGranularity();

private:
	TSubConnectionUniqueId iThisSubConnectionsUniqueId;

	CInterface* iInterface;
	/** @note We *do not* own these, so don't delete them (they are owned by CConnections) */
	RPointerArray<CSubConnection> iSubConnections;	

	RArray<TUint> iUplinkGranularities;		// ordered lists of deltas for the granularities
	RArray<TUint> iDownlinkGranularities;

	TUint iCurrentUplinkGranularity;		// the aggregate notification granularity calculated from all the CConnection requests
	TUint iCurrentDownlinkGranularity;
	};


class CConnPref : public CObject
/**
@internalComponent
*/
	{
private:
	CConnPref();
	CConnPref(const TConnPref& aConnPrefs);

public:
	static CConnPref* NewL();
	static CConnPref* NewL(const TConnPref& aConnPrefs);
	virtual ~CConnPref();
	inline operator const TConnPref&() const;
	inline void Set(TConnPref& aPrefs);
private:
	TConnPref iConnPrefs;
	};

class ProtocolManager;
class Nif;
class CWaitForMBufs;
class CSocket : public CSockSubSession, public MSocketNotify
/**
@internalTechnology
*/
	{
	friend class ProtocolManager;
	friend class Nif;
	friend class CInterface;									// for iInterfaceLink, SetInterface(), ConnectionClientInfoL() and ConnectionSocketInfoL()
	friend CInterface* CSockSession::FindDefaultInterface();	// for SetInterface()

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

	void AutoBind();
	void Bind();
	void RemoteName();
	void LocalName();
	void SetLocalName();

	void SetSockOptionL();
	void GetSockOptionL();
	void IoctlL();
	void GetDisconnectData( ) const;
//
	void SendL(TBool useLength);
	void RecvL(TBool useLength);
//
	inline void CancelSend();
	inline void CancelRecv();
	void CancelConnect();
	void CancelAccept();
	void CancelIoctl();
	void CancelAll();

	void GetInfo();
	void FreeMemory();
	void ReferenceL();

	void CommunicateOwner();
	CProtocolBase* Protocol() { return iProtocol; };
	void SetConnection(const TDesC8& aConnectionInfo);
	void SetConnPrefs(CConnPref* aPrefs);


	TPtr8 IoctlBuffer();

	//	SSP Upcalls - from MSocketNotify
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
	void NoBearer(const TDesC8& aConnectionParams);
	void Bearer(const TDesC8& aConnectionInfo);
	// Utitlity functions for testing state and capabilities
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
	inline TUint RequiresOwnerInfo() const;
	inline TUint StateCanProcessData() const;

private:

	TBool CheckRunningAndSetReturn() const;
	// Utility functions for handling blocked messages.
	enum EBlockingFlags {EBlockedClose=0x01,EBlockedConnect=0x02,EBlockedIoctl=0x04,
						 EBlockedRead=0x08, EBlockedWrite=0x10,EWriteFlowedOff=0x20,
						 EReadStopped=0x40, EWriteStopped=0x80};

	inline CInterface* Interface() const;
	inline void SetInterface(CInterface* aInterface);

	TInt GetConnectionSocketInfo(TConnectionSocketInfo& aInfo);

	inline void SetBlockedRead();
	inline void SetBlockedWrite();
	inline void SetBlockedConnect(const RMessage2 &aMessage);
	inline void SetBlockedClose(const RMessage2 &aMessage);
	inline void SetBlockedIoctl(const RMessage2 &aMessage);

	inline TBool IsBlockedRead();
	inline TBool IsBlockedWrite();
	inline TBool IsBlockedConnect();
	inline TBool IsBlockedClose();
	inline TBool IsBlockedIoctl();
	inline TBool IsImplicitStartup() const;
	
	void CompleteRead(TInt anError);
	void CompleteWrite(TInt anError);
	void CompleteConnect(TInt anErr);
	void CompleteClose(TInt anErr);
	void CompleteIoctl(TInt anErr);
	void DoCompleteAccept();
//
	TInt DrainStreamProtocolL( );
	TInt FillStreamProtocolL( );
//
	void AcceptSetup(const CSocket& aSocket,CServProviderBase &anSSP);
    TUint SelectConditionsReady();
	TBool CheckReadStopped();
	void TryToCompleteSelectIoctl();
	void CreateAndStartExplicitConnectionL();
	void CreateAndStartConnectionL(const TDesC8& aConnectionInfo=TPtrC8());
	void DoError(TInt aError, TUint aOperationMask, TBool aDeleteInterface=ETrue);
//
	TInt RequestAsyncMBufAllocation(TInt aSignalType, TUint aSize);	

	inline TSocketState State() const;
	IMPORT_C void SetState(TSocketState aState);
private:

	CServProviderBase *iSSP;		//lint -esym(613, CSocket::iSSP)	// NULL-ness well controlled
	CProtocolBase* iProtocol;
	CInterface* iInterface;
	TDblQueLink iInterfaceLink;				// for CInterface::iSockets

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
	TSockXfrLength iSendTransferLength;
	TSockXfrLength iRecvTransferLength;

//	TSockAddr *iRecvFromAddr;
	TBool iRecvFromAddr;
	TSockAddr *iSendToAddr;
	TSockAddr iRecvFromTransferAddr;
	TSockAddr iSendToTransferAddr;
//
	RMessage2 iReadMsg;
	RMessage2 iWriteMsg;
	RMessage2 iBlockedClose;
	RMessage2 iBlockedConnect;
	RMessage2 iBlockedIoctl;
	TUint iBlockedOperations;

	TInt iError;

	TUint iOptions;
	TProtocolDesc *iProtocolInfo;
//
	HBufC8 *iRecBuf;	//lint -esym(613, CSocket::iRecBuf)	// NULL-ness well controlled
	TInt iRecBufSize;
	HBufC8 *iSendBuf;
	TInt iSendBufSize;
	HBufC8 *iDisconnectData;
	TInt iDisconnectDataError;
	RMBufChain iDatagramTail;
//
	CWaitForMBufs* iAllocAsync;
//
	CCirBuf<TAcceptQEntry> *iAcceptQ;	//lint -esym(613, CSocket::iAcceptQ)	// NULL-ness well controlled
	TInt iSelectFlags;
	CConnPref* iConnPrefs;
	TBool iImplicitStartup:1;
	};

class CHostResolver : public CSockSubSession, public MResolverNotify
/**
@internalComponent
*/
	{
	friend class ProtocolManager;
	friend class CInterface;									// for iInterfaceLink and SetInterface()
	friend CInterface* CSockSession::FindDefaultInterface();	// for Interface()
public:
	static CHostResolver * NewL(TServerProtocolDesc* aServiceInfo, CSockSession *aSession);

	inline void SetResolver(CHostResolvProvdBase* aResolver);
	
    void GetByName();
	void Next();
	void GetByAddress();
	void GetHostName();
	void SetHostName();

    void Query(void);
    void QueryGetNext(void);


    virtual ~CHostResolver();
	void Cancel();
	void QueryComplete(TInt anError);
	void SetConnection(const TDesC8& aConnectionInfo);
	void SetConnPrefs(CConnPref* aPrefs);
	void LinkUp();
	inline TUint RequiresOwnerInfo() const;
private:
	CHostResolver();
	void CreateL(TServerProtocolDesc* aServiceInfo, CSockSession *aSession);
	void CreateAndStartImplicitConnectionL();
	void CreateAndStartExplicitConnectionL();
	void SetInterface(CInterface* aInterface);
	inline CInterface* Interface() const { return iInterface; };
	inline TUint RequiresConnectionStartup();
	inline TBool IsImplicitStartup() const;
	void HandleConnectionSetup();
	void HandleImplicitConnectionSetup();
	void HandleExplicitConnectionSetup();
private:
	CInterface *iInterface;
	CHostResolvProvdBase* iRSP;
	TBool iBusy;
	RMessage2 iBlockedReq;
	TNameRecord iNameRec;
	TInt iCount;
	TInt iCurrentOp;
	TBool iAwaitingConnection;
	TDblQueLink iInterfaceLink;			// for CInterface::iHostResolvers
	TProtocolDesc *iProtocolInfo;
	CConnPref* iConnPrefs;
	TBool iImplicitStartup:1;
	
    HBufC8 *ipQryBuf;       ///< pointer to the query data buffer heap descriptor
    HBufC8 *ipQryRespBuf;   ///< pointer to the query response buffer heap descriptor

    TPtr8   iPtrQryBuf;     ///< Pointer descriptor, associated with ipQryBuf 
    TPtr8   iPtrQryResBuf;  ///< Pointer descriptor, associated with ipQryRespBuf 
    

    HBufC8* CHostResolver::GetBuffer(HBufC8* apBuf, TInt aBufLenRequired);
    TBool   GetQueryRespBuffer(void);
    TBool   GetQueryBuffer(void);

    };

class CServiceResolver : public CSockSubSession, public MResolverNotify
/**
@internalComponent
*/
	{
	friend class ProtocolManager;
private:
	CServiceResolver();
	void CreateL(CSockSession *aSession);
public:

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
	RMessage2 iBlockedReq;
	TBool iBusy;
	TServiceName iNameBuf;
	TInt32 iPortNum;
	};

class CNetDatabase : public CSockSubSession, public MResolverNotify
/**
@internalComponent
*/
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
	RMessage2 iBlockedReq;
	TBool iBusy;
	HBufC8* iBuf;
	TPtr8* iBufPtr;
	};

template<class TInfo, TInt QueueSize>
class TNotificationQueue
/**
Class used to maintain a notification queue for CConnection.

@internalComponent
*/
	{
public:
	inline TNotificationQueue();
	inline TBool IsEmpty() const { return iQueueLength == 0; };
	void Enque(const TInfo& aInfo);
	TBool Deque(TInfo& aInfo);
	void Reset();
private:
	TInfo iQueue[QueueSize];
	TUint iQueueLength;
	TUint iQueueStart;
	};

#include <es_notq.inl>

/**
@internalComponent
*/
const TUint KMaxProgressQueueLength = 4;

/**
@internalComponent
*/
typedef TNotificationQueue<TNifProgress, KMaxProgressQueueLength>	TProgressQueue;

/**
@internalComponent
*/
const TUint KMaxInterfaceNotificationQueueLength = 4;

/**
@internalComponent
*/
typedef TNotificationQueue<TInterfaceNotification, KMaxInterfaceNotificationQueueLength>	TInterfaceChangeQueue;

/**
@internalComponent
*/
const TUint KMaxSubConnectionEventQueueLength = 8;

/**
@internalComponent
*/
typedef TNotificationQueue<TSubConnectionEvent*, KMaxSubConnectionEventQueueLength> TSubConnectionEventQueue;

/**
@internalComponent
*/
const TUint KActivityTimerPriority = EPriorityLow;	// Checking for connection activity is only a low priority task

class TSockOpt;
class CSubConnection;
class CConnection : public CSockSubSession
/**
Server side class representing an RConnection

@internalComponent
*/
	{
	friend class CSubConnection;	// for iInterface
	friend class CInterface;		// for iInterfaceLink
	friend CInterface* CSockSession::FindDefaultInterface();		// for SetInterface()
public:
	
	// methods for creating CConnection instances
	static CConnection* NewL(CSockSession *aSession);
	static CConnection* NewL(CSockSession *aSession, const CConnection& aExistingConnection);
	virtual ~CConnection();

	inline TBool IsConnectionActive() const;				// associated with interface which is active ?
	inline TBool IsMonitorMode() const;						// attached to interface in monitor mode ?

	TBool ServiceL(const RMessage2& aMessage);
	void JoinInterfaceL(CSocket& aSocket);					// join a socket to the same interface as this CConnection
	void JoinInterfaceL(CHostResolver& aHostResolver);		// join a Host Resolver to the same interface as this CConnection

	
	// Upcalls from CInterface
	void ProgressNotification(TInt aStage, TInt aError, const TDesC8& aInfo);
	void ProgressNotification(TSubConnectionUniqueId aSubConnectionUniqueId, TInt aStage, TInt aError, const TDesC8& aInfo);
	void ServiceChangeNotification(TUint32 aId, const TDesC& aType);
	void InterfaceStateChangeNotification(TDesC8& aInfo);
	void SubConnectionEvent(const TSubConnectionEvent& aSubConnectionEvent);

	
	// methods for a CSubInterface to create corresponding CSubConnections
	CSubConnection* CreateSubConnectionL(TSubConnectionUniqueId aSubConnectionUniqueId, CSubInterface* aOwningSubInterface);
	CSubConnection* DeleteSubConnection(TSubConnectionUniqueId aSubConnectionUniqueId);

	inline const CConnPref* const GetConnPrefs() const;

protected:
	CConnection();
	void CreateL(CSockSession *aSession);
	void CreateL(CSockSession *aSession, const CConnection& aExistingConnection);

private:
	// Underlying implementations of individual RConnection methods
	TBool StartL(const RMessage2& aMessage);
	TBool StartWithPrefsL(const RMessage2& aMessage);
	TBool StopL(const RMessage2& aMessage);
	TBool ProgressL(const RMessage2& aMessage);
	TBool LastProgressErrorL(const RMessage2& aMessage);
	TBool RequestProgressNotificationL(const RMessage2& aMessage);
	TBool CancelProgressNotification(const RMessage2& aMessage);
	TBool RequestServiceChangeNotificationL(const RMessage2& aMessage);
	TBool CancelServiceChangeNotification(const RMessage2& aMessage);
	TBool GetIntSettingL(const RMessage2& aMessage);
	TBool GetBoolSettingL(const RMessage2& aMessage);
	TBool GetDes8SettingL(const RMessage2& aMessage);
	TBool GetDes16SettingL(const RMessage2& aMessage);
	TBool GetLongDesSettingL(const RMessage2& aMessage);
	TBool EnumerateConnectionsL(const RMessage2& aMessage);
	TBool GetConnectionInfoL(const RMessage2& aMessage);
	void ExtractEnumInfoL(HBufC8* aBuffer, TUint aCount, TInt aSize, TUint aIndex, TDes8& aPckg);
	TBool EnumerateConnectionClientsL(const TSockOpt& aArgs);
	TBool GetConnectionClientInfoL(const TSockOpt& aArgs);
	TBool EnumerateConnectionSocketsL(const TSockOpt& aArgs);
	TBool GetConnectionSocketInfoL(const TSockOpt& aArgs);
	TBool ControlL(const RMessage2& aMessage);
	TBool AttachL(const RMessage2& aMessage);
	TBool AllInterfaceNotificationL(const RMessage2& aMessage);
	TBool CancelAllInterfaceNotificationL(const RMessage2& aMessage);

	// Underlying implementations of individual RConnection methods relating to subconnections
 	TBool StopSubConnectionL(const RMessage2& aMessage);
	TBool StopSubConnection(const RMessage2& aMessage);
	TBool SubConnectionProgressL(const RMessage2& aMessage);
	TBool RequestSubConnectionProgressNotificationL(const RMessage2& aMessage);
	TBool CancelSubConnectionProgressNotification(const RMessage2& aMessage);
	TBool EnumerateSubConnectionsL(const RMessage2& aMessage);
	TBool GetSubConnectionInfoL(const RMessage2& aMessage);
	TBool AllSubConnectionNotificationL(const RMessage2& aMessage);
	TBool CancelAllSubConnectionNotification(const RMessage2& aMessage);
	TBool DataTransferredL(const RMessage2& aMessage);
	TBool DataTransferredCancel(const RMessage2& aMessage);
	TBool DataSentNotificationRequestL(const RMessage2& aMessage);
	TBool DataSentNotificationCancel(const RMessage2& aMessage);
	TBool DataReceivedNotificationRequestL(const RMessage2& aMessage);
	TBool DataReceivedNotificationCancel(const RMessage2& aMessage);
	TBool IsSubConnectionActiveRequestL(const RMessage2& aMessage);
	TBool IsSubConnectionActiveCancel(const RMessage2& aMessage);

	TInt FindSubConnection(TSubConnectionUniqueId aSubConnectionUniqueId);
	TInt FindPositionForInsertInOrder(TSubConnectionUniqueId aSubConnectionUniqueId);

	TBool SelectedProgressMatch(const TNifProgress& aProgress) const;

	void LeaveInterface(TBool aDeleteInterfaceIfLast = ETrue);			// disassociation from the underlying interface
	inline CInterface* Interface() const;
	inline void SetInterface(CInterface* aInterface);
	inline void ResetLastProgressError();

private:
	CInterface*	iInterface;							// associated interface (if any)
		//lint -esym(613, CConnection::iInterface)	// carefully controlled states													

	RPointerArray<CSubConnection> iSubConnections;

	RMessage2 iStartAttachMessage;					// RConnection::Start()/Attach() message (mutually exclusive use)
	RMessage2 iProgressNotificationMessage;			// RConnection::ProgressNotification() message
	RMessage2 iServiceChangeNotificationMessage;		// RConnection::ServiceChangeNotification() message
	RMessage2 iAllInterfaceNotificationMessage;
	RMessage2 iStopMessage;							// RConnection::Stop() message
	RMessage2 iAllSubConnectionNotificationMessage;


	TBool iStartOutstanding:1;						// Start() outstanding
	TBool iProgressOutstanding:1;					// ProgressNotification() outstanding
	TBool iServiceChangeNotificationOutstanding:1;	// ServiceChangeNotification() outstanding
	TBool iAttachOutstanding:1;						// Attach() outstanding
	TBool iAllInterfaceNotificationOutstanding:1;
	TBool iMonitorMode:1;							// Attach(EAttachTypeMonitor) has been successfully performed
	TBool iStopOutstanding:1;						// Stop() outstanding
	TBool iAllSubConnectionNotificationOutstanding:1; // AllSubConnectionNotification() outstanding

	TUint iSelectedProgressStage;					// the particular stage required for selected progress requests.

	TProgressQueue iProgressQueue;					// queue of progress notifications received
	TInterfaceChangeQueue iInterfaceChangeQueue;	// queue of interface notifications received
	TNifProgress iLastProgress;                     // last progress notified, so we can filter duplicates
	TNifProgress iLastProgressError;				// last progress received which had an error

	TSubConnectionEventQueue iSubConnectionEventQueue; // queue of subconnection events received

	TInt  iCount;
	TInt  iCurrentOp;

	TUint iConnectionInfoCount;
	TUint iConnectionClientCount;
	TUint iConnectionSocketCount;
	RPointerArray<TConnectionInfo> iConnectionInfoPtrArray;
	HBufC8* iConnectionClientBuf;
	HBufC8* iConnectionSocketBuf;

	TDblQueLink iInterfaceLink;						// for CInterface::iConnections
	CConnPref* iPrefs;
	TBool iNotificationsEnabled;
	TBool iDeferredSubConnectionNotificationEnable;
	};

class CSubConnection : public CBase
/**
Handle subconnection-related asynchronous client requests that may not complete immediately
@internalComponent
*/
	{
public:
	CSubConnection(TSubConnectionUniqueId aSubConnectionUniqueId, CConnection* aOwningConnection, CSubInterface* aOwningSubInterface);
	~CSubConnection();

	// Downcalls from client via CConnection
	TBool RequestSubConnectionProgressNotificationL(const RMessage2& aMessage);
	TBool CancelSubConnectionProgressNotification(const RMessage2& aMessage);
	TBool DataSentNotificationRequestL(const RMessage2& aMessage);
	TBool DataSentNotificationCancel(const RMessage2& aMessage);
	TBool DataReceivedNotificationRequestL(const RMessage2& aMessage);
	TBool DataReceivedNotificationCancel(const RMessage2& aMessage);
	TBool IsSubConnectionActiveRequestL(const RMessage2& aMessage);
	TBool IsSubConnectionActiveCancel(const RMessage2& aMessage);

	//	Calls from CConnection
	TInt GetCurrentProgress(TNifProgress& aProgress);

	// Upcalls from CSubInterface
	void NotifyDataTransferred(const TUint aUplinkVolume, const TUint aDownlinkVolume);
	void NotifyDataSent(TUint aUplinkVolume, TUint aCurrentGranularity);
	void NotifyDataReceived(TUint aDownlinkVolume, TUint aCurrentGranularity);
	void ProgressNotification(TInt aStage, TInt aError, const TDesC8& aInfo);

	/**
	Callback from activity timer
	*/
	void CheckSubConnectionActivity();

	/**
	Access this subconnections unique id for search purposes
	*/
	inline TSubConnectionUniqueId SubConnectionUniqueId();

	class CActivityTimer : public CTimer
	/**
	@internalComponent
	*/
		{
	public:
		static CActivityTimer* NewL(CSubConnection* aOwner, TInt aPriority);
		virtual inline ~CActivityTimer() {};
		void RunL();
	private:
		inline CActivityTimer(CSubConnection* aOwner, TInt aPriority);
	private:
		CSubConnection* iOwner;
		};

private:
	TSubConnectionUniqueId iThisSubConnectionsUniqueId;
	CConnection* iConnection;
	CSubInterface* iSubInterface;

	TUint iUplinkDataVolume;
	TUint iDownlinkDataVolume;
	TUint iUplinkDataNotificationVolume;
	TUint iDownlinkDataNotificationVolume;
	TInt iRemainingUplinkGranularity;
	TInt iRemainingDownlinkGranularity;

	TBool iDataSentNotificationsInAbsoluteMode;
	TBool iDataReceivedNotificationsInAbsoluteMode;

	TNifProgress iCurrentProgress;
	TInt iLastProgressToClient;
	TInt iClientRequestedProgress;
	CActivityTimer* iActivityTimer;
	TInt iRequestedClientTimerPeriod;
	TBool iClientBelievesSubConnectionActive;
	TUint iPreviousUplinkDataVolume;
	TUint iPreviousDownlinkDataVolume;

	TBool iOutstandingProgressNotification:1;
	TBool iOutstandingDataSentNotification:1;
	TBool iOutstandingDataReceivedNotification:1;
	TBool iOutstandingSubConnectionActivity:1;

	RMessage2 iOutstandingProgressNotificationMessage;
	RMessage2 iOutstandingDataSentNotificationMessage;
	RMessage2 iOutstandingDataReceivedNotificationMessage;
	RMessage2 iOutstandingSubConnectionActivityMessage;
	};

/**
@internalComponent
*/
GLREF_C void Fault(TESockFault aFault);

/**
@internalComponent
*/
GLREF_C void Panic(TProtocolPanic aPanic);
EXPORT_C TInt SocketServerThread(TAny *);

class TSockManData;
class CSockSession;
class CSocketScheduler : public CActiveScheduler
/**
@internalTechnology
*/
	{

public:
	static CSocketScheduler* New();
	~CSocketScheduler();
    virtual void Error(TInt anError) const;
    static TBool CheckLockedL(CSockSession* aSession);
    static void SetLockedL(CSockSession* aSession);
    static TInt Unlock(CSockSession* aSession);
    static void SessionRequestFinished(CSockSession* aSession);
    virtual void WaitForAnyRequest();
	inline static void SetGlobals(TSockManData* aGlobals);
	inline static void SetWaitHook(TCallBack* aCall);
	inline static TSockManData* Globals();
private:
    TSockManData* iGlobals;
	CSockSession* iCurrentSession;
	TCallBack* iWaitHook;
    CSockSession* iLockedSession;
    CArrayFixFlat<RMessage2>* iLockedMessageFifo;
	};

#include "ss_std.inl"

#endif
