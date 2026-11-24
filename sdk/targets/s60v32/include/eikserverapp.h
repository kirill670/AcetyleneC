// EikServerApp.h
//
// Copyright (c) Symbian Software Ltd 2004-2005.  All rights reserved.
//

#ifndef EIKSERVERAPP_H 
#define EIKSERVERAPP_H

#include <apaserverapp.h>
#include <apadef.h>

class RWindowGroup;

class REikAppServiceBase : public RApaAppServiceBase

/** Launches and connects to new instances of server apps.

This adds the ability to launch new server applications to
RApaAppServiceBase.
All UI level client side service support should derive from this
class.

@publishedPartner

@see RApaAppServiceBase */
	{
public:
	IMPORT_C void ConnectNewAppL(TUid aAppUid);
	IMPORT_C void ConnectNewAppL(TUid aAppUid, const TSecurityPolicy& aSecurityPolicy);
	IMPORT_C void ConnectNewChildAppL(TUid aAppUid, RWindowGroup& aParentWindowGroup);
	IMPORT_C void ConnectNewChildAppL(TUid aAppUid, RWindowGroup& aParentWindowGroup, const TSecurityPolicy& aSecurityPolicy);
	IMPORT_C void Close();
	
private:
	void LaunchAppL(TUid aAppUid, TUint aServerDifferentiator, RWindowGroup* aParentWindowGroup, TRequestStatus& aRequestStatusForRendezvous, 
		TApaCommand& aLaunchCommand);
	TUint StartServerL(TUid aAppUid, RWindowGroup* aParentWindowGroup);

private:
	IMPORT_C virtual void ExtensionInterface(TUid aInterfaceId, TAny*& aImplementaion);

private:
	TInt iEikReserved1;
	};
	
class CEikAppServer : public CApaAppServer
/** Base class for all server application's servers.
Server applications must derive from this class to implement their
servers. These must be instantiated in an override of
CEikApplication::NewAppServerL().
This class adds support for uniquely named servers over CApaAppServers.

@publishedPartner

@see CApaAppServer */
	{
public: // internal
	void ConstructUniqueL(TUint aServerDifferentiator, TUid aAppUid);

public:	// from CApaAppServer
	IMPORT_C void ConstructL(const TDesC& aFixedServerName);
	IMPORT_C CApaAppServiceBase* CreateServiceL(TUid aServiceType) const;
	IMPORT_C TCustomResult CreateServiceSecurityCheckL(TUid aServiceType, const RMessage2& aMsg, TInt& aAction, TSecurityInfo& aMissing);

private:
	IMPORT_C virtual void ExtensionInterface(TUid aInterfaceId, TAny*& aImplementaion);

private:
	TInt iEikReserved1;
	};

#endif
