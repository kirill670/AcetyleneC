//
//Copyright (c) 2000, 2003 Symbian Software Ltd.  All rights reserved.
//

/**
@file 
Generic Connection Agent client interface
*/

#ifndef __AGENTCLIENT_H__
#define __AGENTCLIENT_H__

#include <nifman.h>
#include <cdbstore.h>

//
// RGenericAgent class
//
// Client interface class derived from RNif.  This can be used to start an
// agent for incoming or outgoing connections, with or without overrides.
// Also allows the client to ask what overrides are being used.
//

class RGenericAgent : public RNif
/**
* @publishedAll
* @deprecated 7.0s Replaced by new connection management RConnection API
* @see RConnection
* 
* The generic agent interfaces with NifMan.
* 
* Note that from v6.1 onwards, this replaces the NetDial API.
* 
* The Network Interface Manager (NifMan) provides a generic framework for controlling 
* network interfaces, and defines a plug-in architecture. The Generic Agent 
* is such a plug-in for handling dial-up networking. TCP/IP uses the Generic 
* Agent to establish a connection, before setting up the PPP connection.
* 
* The Generic Agent gets comms settings, such as modem and ISP configuration, 
* from the communications database (CommDb). It uses the Telephony subsystem 
* to make the dial-up connection. 
*/
	{
public:
	IMPORT_C RGenericAgent();
	IMPORT_C ~RGenericAgent();
	IMPORT_C TInt Open();
	IMPORT_C TInt StartOutgoing();
	IMPORT_C TInt StartOutgoing(CStoreableOverrideSettings& aOverrides);
	IMPORT_C void StartOutgoing(TRequestStatus& aStatus);
	IMPORT_C void StartOutgoing(CStoreableOverrideSettings& aOverrides, TRequestStatus& aStatus);
	IMPORT_C void CancelOutgoingErrorNotification();
	IMPORT_C TInt AcceptIncomingRequests(TRequestStatus& aStatus);
	IMPORT_C TInt AcceptIncomingRequests(CStoreableOverrideSettings& aOverrides, TRequestStatus& aStatus);
	IMPORT_C void AcceptIncomingRequestsCancel();
	IMPORT_C void ServiceChangeNotification(TRequestStatus& aStatus, TUint32& aNewISPId, TDes& aNewServiceType);
	IMPORT_C void CancelServiceChangeNotification();
	IMPORT_C TInt GetActiveIntSetting(const TDesC& aTableName, const TDesC& aColumnName, TUint32& aValue);
	IMPORT_C TInt GetActiveBoolSetting(const TDesC& aTableName, const TDesC& aColumnName, TBool& aValue);
	IMPORT_C TInt GetActiveDesSetting(const TDesC& aTableName, const TDesC& aColumnName, TDes8& aValue);
	IMPORT_C TInt GetActiveDesSetting(const TDesC& aTableName, const TDesC& aColumnName, TDes16& aValue);
	IMPORT_C TInt GetActiveLongDesSetting(const TDesC& aTableName, const TDesC& aColumnName, TDes& aValue);
	IMPORT_C static void ResolveError(TInt &aError);
	IMPORT_C void ConnectionError(TInt& aError);
	IMPORT_C void DebugMarkStart();
	IMPORT_C void DebugMarkEnd(TInt aCount = 0);
	IMPORT_C void DebugSetAllocFail(TInt aValue = 0);
private:
	void PackageOverridesArray(TAny* aPtr,  TInt aPtrNum, CStoreableOverrideSettings& aOverrides);
	void DoStartOutgoingL(CStoreableOverrideSettings& aOverrides);
	void DoAcceptIncomingRequestsL(CStoreableOverrideSettings& /*aOverrides*/, TRequestStatus& /*aStatus*/) {;};
	TInt StartNifForOutgoing();
	void DoStartOutgoingL(CStoreableOverrideSettings& aOverrides, TRequestStatus& aStatus);
	void StartNifForOutgoing(TRequestStatus& aStatus);
private:
	TPckg<TUint32> iNewISPId;
	};	

#endif

