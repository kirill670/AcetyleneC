//
// obexclient.h
//
// Copyright (c) 2003-2004 Symbian Software Ltd.  All rights reserved.
//

#ifndef __OBEXCLIENT_H
#define __OBEXCLIENT_H

#include "obextypes.h"
#include "obexbase.h"

/**
@publishedAll
@released

Client side functionality. Connection based.
Supports ...
	@li Opening IrDA TTP sockets for the OBEX session.
	@li Opening an OBEX session over a connected socket
	@li Standard OBEX (spec. version 1.2) operations.
 
@par  Deriving Classes from CObexClient
This class is not designed for user derivation.
*/
NONSHARABLE_CLASS(CObexClient) : public CObex
	{
public:
		IMPORT_C ~CObexClient();
		IMPORT_C static CObexClient* NewL(TObexProtocolInfo& aObexProtocolInfoPtr);
		IMPORT_C static CObexClient* NewL(TObexProtocolInfo& aObexProtocolInfoPtr, TObexProtocolPolicy& aObexProtocolPolicy);
		IMPORT_C void Connect(TRequestStatus& aStatus);
		IMPORT_C void Connect(CObexBaseObject& aObject, TRequestStatus& aStatus);	
		IMPORT_C void ConnectL(CObexBaseObject& aObject, const TDesC& aPassword, 
														TRequestStatus& aStatus);
		IMPORT_C void ConnectL(const TDesC& aPassword, TRequestStatus& aStatus);
		IMPORT_C void Disconnect(TRequestStatus& aStatus);						
		IMPORT_C void Put(CObexBaseObject& aObject, TRequestStatus& aStatus);
		IMPORT_C void Get(CObexBaseObject& aObject, TRequestStatus& aStatus);		
		IMPORT_C void SetPath(TSetPathInfo& aPathInfo, TRequestStatus& aStatus);
		IMPORT_C void Abort();					
		IMPORT_C void UserPasswordL( const TDesC& aPassword);
		IMPORT_C const CObexHeaderSet& GetPutFinalResponseHeaders();
		
	private:
		CObexClient(TObexProtocolPolicy& aObexProtocolPolicy);
		void ConstructL(TObexProtocolInfo& aObexProtocolInfoPtr);
		TBool AlreadyActive(TRequestStatus& aStatus);
		void ClientCommandL(TOperation aOp, TAny* aParam, TRequestStatus& aStatus);
		// Implementation of CObex Events
		virtual void OnPacketReceive(CObexPacket& aPacket);
		virtual void OnError(TInt aError);
		virtual void OnTransportUp();
		virtual void OnTransportDown();
		void SetRequest(TRequestStatus& aStatus, TOperation aOperation);
		void CompleteRequest(const TInt aCompletion);
		TInt PrepareConnectPacket(CObexPacket& aPacket);	// Should be members of TConnectInfo
		TInt ParseConnectPacket(CObexPacket& aPacket);	
		void ResetConnectionID();
		void SetConnectionID(TUint32 aConnectionID);
		void EmptyHeaderSet();

	private: 
		TRequestStatus* iPendingRequest;
		CObexBaseObject* iCurrentObject;
		TUint32 iConnectionID; 
		TBool iConnectionIdSet;
		CObexHeaderSet* iHeaderSet;
		CObexHeader* iHeader;
	};

#endif	// __OBEXCLIENT_H
