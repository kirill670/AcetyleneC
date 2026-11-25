/**
@file NIFMAN.H

Interface Manager API

Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
*/


#if !defined(__NIFMAN_H__)
#define __NIFMAN_H__

#include <es_prot.h>
#include <nifvar.h>
#include <cdbover.h>

class CNifMan;
class CNifFactory : public CObject
/**
Manager classes

@publishedPartner
@released
*/
	{
friend class CNifMan;
public:
	IMPORT_C CNifFactory();
	IMPORT_C virtual TInt Open();
	IMPORT_C virtual void Close();
	IMPORT_C static void Cleanup(TAny* aObject);
    IMPORT_C static TInt ControlledDelete(TAny* aFactory);
	IMPORT_C void InitL(RLibrary& aLib, CObjectCon& aCon);

protected:
	IMPORT_C ~CNifFactory();
	virtual void InstallL()=0;
	RLibrary iLib;
	CAsyncCallBack* iAsyncDtor;
	};

/**
Static internal API class
@internalComponent
*/
enum TNifSocketState { ENifBuffers2048=-4, ENifBuffers1024, ENifBuffers512, 
					   ENifSocketNull=-1,
                       ENifSocketCreated=0, ENifSocketOpen=3, ENifSocketConnected=4,
					   ENifSocketError=9 };

class MNifIfUser;
class MNifIfNotify;
class CNifIfBase;
class CNifAgentBase;
class CSockSession;
class CConnectionProvdBase;
class Nif
/**
@internalTechnology
*/
	{
public:
	/** Network protocol support */
	IMPORT_C static void BindL(MNifIfUser& aUser, TAny* aId, TDes& aResult, const TDesC& aName=TPtrC(0,0));
	IMPORT_C static void NetworkLayerClosed(MNifIfUser& aUser);
	IMPORT_C static void StartL(TDes& aResult, const TDesC& aName=TPtrC());
	IMPORT_C static void Stop(const TDesC& aName=TPtrC());
	IMPORT_C static CNifIfBase* CreateInterfaceL(const TDesC& aName, MNifIfNotify* aNotify);
	IMPORT_C static CNifAgentBase* CreateAgentL(const TDesC& aAgentName, const TBool aNewInstance = EFalse);
	IMPORT_C static void CheckInstalledMBufManagerL();
	IMPORT_C static CProtocolBase* IsProtocolLoaded(const TDesC& aName);
	IMPORT_C static void CheckInstalledL();
	IMPORT_C static TInt SetSocketState(TNifSocketState aState, CServProviderBase* aProvd);
	IMPORT_C static void ProgressL(TNifProgress& aProgress, const TDesC& aName=TPtrC());
	IMPORT_C static void Stop(TAny* aId, CNifIfBase* aIf=0);
	IMPORT_C static void ProgressL(TNifProgress& aProgress, TAny* aId, CNifIfBase* aIf=0);
	IMPORT_C static CConnectionProvdBase* NewConnectionL(MConnectionNotify* aConnection);

	/** deprecated function */
	IMPORT_C static CNifIfBase* CreateInterfaceL(const TDesC& aName);
	};


/**
Client side classes
async message for progress notifier

@publishedAll
@deprecated 7.0s - replaced with RConnection API
*/
const TInt KDefaultNifSlots = 1;	

class RNif : public RSessionBase
/**
Provides a Network Interface Manager (NifMan) API for the client application so that it may manage
a connection.  

Provided for backwards compatibility only - from v7.0s onwards is superseded by RConnection API.
@publishedAll
@deprecated 7.0s - replaced with RConnection API
*/
	{
public:
	IMPORT_C TInt AgentInfo(TNifAgentInfo& aInfo);
	IMPORT_C TInt DisableTimers(TBool aDisable=ETrue);
	IMPORT_C TInt Stop();
	IMPORT_C void ProgressNotification(TNifProgressBuf& aProgress, TRequestStatus& aStatus);
	IMPORT_C void CancelProgressNotification();
	IMPORT_C TInt Progress(TNifProgress& aProgress);
	IMPORT_C TInt LastProgressError(TNifProgress& aProgress);
	IMPORT_C static TVersion Version();
	IMPORT_C TInt Open(const TDesC& aName=TPtrC(), TInt aSlots=KDefaultNifSlots);
	IMPORT_C TInt NetworkActive(TBool& aIsActive);
protected:
	IMPORT_C TInt Start(TAny *aPtr);
	IMPORT_C void Start(TAny *aPtr, TRequestStatus& aStatus);
	};

class Nifman
/**
@internalTechnology
*/
	{
public:
	IMPORT_C static TInt CheckIniConfig();
	};

class RNifMonitor : public RNif
/**
@publishedPartner
@deprecated 7.0s - replaced with RConnection API
*/
	{
public:
	IMPORT_C TInt Open(const TDesC& aName=TPtrC(), TInt aSlots=KDefaultNifSlots);
	};

/**
RConnection::Control() levels for NIFMAN

@publishedPartner
@released
*/
const TUint KCOLInterface = 100;
const TUint KCOLAgent     = 200;

/**
RConnection::Control() option

@publishedPartner
@released
*/
const TUint KConnDisableTimers = KConnReadUserDataBit | 1;
const TUint KConnGetInterfaceName = KConnReadUserDataBit | KConnWriteUserDataBit | 2;

#ifdef _DEBUG
/**
@internalTechnology
*/
const TUint KConnStartWithAgentName = KConnReadUserDataBit | 9999;
#endif

/**
@publishedPartner
@released
*/
const TUint KConnMaxInterfaceName = 32;

class TConnInterfaceName
/**
@publishedPartner
@released
*/
	{
public:
	TUint iIndex;
	TBuf<KConnMaxInterfaceName> iName;
	};
/**
@internalTechnology
*/
enum TAgentConnectType 
	{
	EAgentStartDialOut,
	EAgentReconnect,
	EAgentStartCallBack,
	EAgentNone,
	EAgentStartDialIn
	};

#endif // __NIFMAN_H__

