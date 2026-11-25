/**
@file SS_STD.INL

Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
*/

inline void CSocket::SetSSP(CServProviderBase* anSSP)
	{iSSP=anSSP;}

inline const RMessage2& CSockSession::Message() const
{ return (RMessage2&)iOurMessage; }

inline TSockManData* CSockSession::SockManGlobals() const
	{ return iSockManGlobals; };

#if !defined(__GCC32__)
inline const RMessage2& CSockSubSession::Message() const
	{
	return iSession->Message();
	}
#endif

inline void CSockSubSession::DontCompleteCurrentRequest() const
	{
	iSession->DontCompleteCurrentRequest();
	}

inline void CSockSubSession::SetReturn(TInt aComplete,TInt anError,TUid anOwner) const
	{
	iSession->SetReturn(aComplete,anError,anOwner);
	}

inline TUint CSocket::IsConnectionOriented()  const
	{
	return !(iProtocolInfo->iServiceInfo & KSIConnectionLess);
	}

inline TUint CSocket::IsConnectionLess() const
	{
	return (iProtocolInfo->iServiceInfo & KSIConnectionLess);
	}

inline TUint CSocket::IsDataGram() const
	{
	return (iProtocolInfo->iServiceInfo & KSIDatagram);
	}

inline TUint CSocket::IsStream() const
	{
	return (iProtocolInfo->iServiceInfo & KSIStreamBased);
	}

inline TUint CSocket::IsPseudoStream() const
	{
	return (iProtocolInfo->iServiceInfo & KSIPseudoStream);
	}

inline TUint CSocket::IsReliable() const
	{
	return (iProtocolInfo->iServiceInfo & KSIReliable);
	}

inline TUint CSocket::CanReconnect() const
	{
	return (iProtocolInfo->iServiceInfo & KSICanReconnect);
	}

inline TUint CSocket::SupportsPeek() const
	{
	return (iProtocolInfo->iServiceInfo & KSIPeekData);
	}

inline TUint CSocket::DeliversInOrder() const
	{
	return (iProtocolInfo->iServiceInfo & KSIInOrder);
	}

inline TUint CSocket::IsMessageBased() const
	{
	return (iProtocolInfo->iServiceInfo & KSIMessageBased);
	}

inline TUint CSocket::CanSendUrgentData() const
	{
	return (iProtocolInfo->iServiceInfo & KSIUrgentData);
	}

inline TUint CSocket::CanSendConnectData() const
	{
	return (iProtocolInfo->iServiceInfo & KSIConnectData);
	}

inline TUint CSocket::CanSendDisconnectData() const
	{
	return (iProtocolInfo->iServiceInfo & KSIDisconnectData);
	}

inline TUint CSocket::CanBroadcast() const
	{
	return (iProtocolInfo->iServiceInfo & KSIBroadcast);
	}

inline TUint CSocket::SupportsMultiPoint() const
	{
	return (iProtocolInfo->iServiceInfo & KSIMultiPoint);
	}

inline TUint CSocket::SupportsQOS() const
	{
	return (iProtocolInfo->iServiceInfo & KSIQOS);
	}

inline TUint CSocket::IsWriteOnly() const
	{
	return (iProtocolInfo->iServiceInfo & KSIWriteOnly);
	}

inline TUint CSocket::IsReadOnly() const
	{
	return (iProtocolInfo->iServiceInfo & KSIReadOnly);
	}

inline TUint CSocket::SupportsGracefulClose() const
	{
	return (iProtocolInfo->iServiceInfo & KSIGracefulClose);
	}

inline TUint CSocket::RequiresOwnerInfo() const
	{
	return (iProtocolInfo->iServiceInfo & KSIRequiresOwnerInfo);
	}

inline void CSocket::SetBlockedRead()
	{
	__ASSERT_DEBUG(!IsBlockedRead(),Fault(ETwoReads));
	iBlockedOperations|=EBlockedRead;
	}

inline void CSocket::SetBlockedWrite()
	{
	__ASSERT_DEBUG(!IsBlockedWrite(),Fault(ETwoWrites));
	iBlockedOperations|=EBlockedWrite;
	}

inline void CSocket::SetBlockedConnect(const RMessage2 &aMessage)
	{
	__ASSERT_DEBUG(!IsBlockedConnect(),Fault(ETwoConnects));
	iBlockedOperations|=EBlockedConnect;
	iBlockedConnect=aMessage;
	}

inline void CSocket::SetBlockedClose(const RMessage2 &aMessage)
	{
	__ASSERT_DEBUG(!IsBlockedClose(),Fault(ETwoClose));
	iBlockedOperations|=EBlockedClose;
	iBlockedClose=aMessage;
	}

inline void CSocket::SetBlockedIoctl(const RMessage2 &aMessage)
	{
	__ASSERT_DEBUG(!IsBlockedIoctl(),Fault(ETwoIoctl));
	iBlockedOperations|=EBlockedIoctl;
	iBlockedIoctl=aMessage;
	}

inline TBool CSocket::IsBlockedClose()
	{return iBlockedOperations&EBlockedClose;}

inline TBool CSocket::IsBlockedConnect()
	{return iBlockedOperations&EBlockedConnect;}

inline TBool CSocket::IsBlockedIoctl()
	{return iBlockedOperations&EBlockedIoctl;}

inline TBool CSocket::IsBlockedRead()
	{return iBlockedOperations&EBlockedRead;}

inline TBool CSocket::IsBlockedWrite()
	{return iBlockedOperations&EBlockedWrite;}

inline TBool CSocket::IsImplicitStartup() const
	{return iImplicitStartup;}

void CSocket::CancelSend()
	{ CompleteWrite(KErrCancel); }

void CSocket::CancelRecv()
	{ CompleteRead(KErrCancel); }

inline void CSocket::SetInterface(CInterface* aInterface)
	{ iInterface = aInterface; };

inline CSocket::TSocketState CSocket::State() const
	{
	return iState;
	}

inline void CHostResolver::SetResolver(CHostResolvProvdBase* aResolver)
	{iRSP=aResolver;}

inline TUint CHostResolver::RequiresConnectionStartup()
	{ return iProtocolInfo->iNamingServices & KNSRequiresConnectionStartup; };

inline TUint CHostResolver::RequiresOwnerInfo() const
	{
	return (iProtocolInfo->iServiceInfo & KSIRequiresOwnerInfo);
	}

inline TBool CHostResolver::IsImplicitStartup() const
	{return iImplicitStartup;}

inline void CServiceResolver::SetResolver(CServiceResolvProvdBase* aResolver)
	{iRSP=aResolver;}

inline void CNetDatabase::SetProvd(CNetDBProvdBase* aResolver)
	{iRSP=aResolver;}

inline void CSocketScheduler::SetGlobals(TSockManData* aGlobals)
    { ((CSocketScheduler*)CActiveScheduler::Current())->iGlobals=aGlobals; }

inline void CSocketScheduler::SetWaitHook(TCallBack* aCall)
	{ ((CSocketScheduler*)CActiveScheduler::Current())->iWaitHook=aCall; }

inline TSockManData* CSocketScheduler::Globals()
	{ return ((CSocketScheduler*)CActiveScheduler::Current())->iGlobals; }

// CConnection

inline TBool CConnection::IsConnectionActive() const
	{ return Interface() && Interface()->IsSelectionComplete(); }

inline TBool CConnection::IsMonitorMode() const
	{ return iMonitorMode; }

// CSubConnection

inline TSubConnectionUniqueId CSubConnection::SubConnectionUniqueId()
/**
Access this subconnections unique id for search purposes

@internalComponent
@return The unique id of the subconnection to which this CSubConnection refers
*/
	{ return(iThisSubConnectionsUniqueId); }

inline CSubConnection::CActivityTimer::CActivityTimer(CSubConnection* aOwner, TInt aPriority) 
: CTimer(aPriority), iOwner(aOwner)
/**
Set up the activity timer for subconnection activity

@param aOwner, The owing subconnection
@param aPriority, The priority of the active object
*/
	{ CActiveScheduler::Add(this); };

// CInterface

inline CInterface* CConnection::Interface() const
	{ return iInterface; };

inline void CConnection::SetInterface(CInterface* aInterface)
	{ iInterface = aInterface; };

inline void CConnection::ResetLastProgressError()
	{ iLastProgressError.iError = KErrNone; iLastProgressError.iStage = KConnectionUninitialised; };

inline CInterface* CSocket::Interface() const
	{ return iInterface; };

void CInterface::AddMonitor()
	{ iConnectionMonitorCount++; }

inline CConnectionProvdBase* CInterface::Provider() const
	{ return iProvider; };

inline const TDesC8& CInterface::ConnectionInfo() const
	{ return *iConnectionInfo; };

inline TBool CInterface::IsNewBearer(const TDesC8& aConnectionInfo) const
	{ 	
 	if(iConnectionInfo == NULL)
 		return ETrue;
 	else 
 		return (ConnectionInfo() != aConnectionInfo); }

inline TBool CInterface::IsSelectionComplete() const
	{ return iSelectionComplete; };

inline void CInterface::DeleteConnectionInfo()
	{ delete iConnectionInfo; iConnectionInfo = NULL;	iSelectionComplete = EFalse; };

inline TBool CInterface::OnGlobalList() const
	{ return iOnGlobalList; };

inline TBool CInterface::SubSessionsPresent() const
	{ return (iSocketCount || iHostResolverCount || iConnectionCount); };

// CSubInterface

inline TSubConnectionUniqueId CSubInterface::SubConnectionUniqueId()
/**
Access this subconnections unique id for search purposes

@return The unique id of the subconnection to which this CSubInterface refers
*/
	{ return(iThisSubConnectionsUniqueId); }

inline CConnPref::operator const TConnPref&() const
	{ 
	return iConnPrefs; 
	}
inline void CConnPref::Set(TConnPref& aPrefs)
	{
	iConnPrefs = aPrefs;
	}

inline const CConnPref* const CConnection::GetConnPrefs() const
	{
	return iPrefs;
	}


