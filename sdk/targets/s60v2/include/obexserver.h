//
// obexserver.h
//
// Copyright (c) 2003-2004 Symbian Software Ltd.  All rights reserved.
//

#ifndef __OBEXSERVER_H
#define __OBEXSERVER_H

#include "obextypes.h"
#include "obexbase.h"

/** OBEX server.

CObexServer provides a framework for servicing OBEX requests from remote clients. 
It is designed to be able to act as either a "default" application (in IrDA 
terms, registering on the IrDA:OBEX IAS class), or as a application specific 
server (registering itself on a private IAS class). 

You implement service-specific behaviour by providing a MObexServerNotify 
interface implementation to the server object. The server calls the interface's 
functions to provide notification of server events, which specific implementations 
can process (or ignore) as appropriate.

This class is not designed for user derivation. 

@publishedAll
@released
*/
class CObexServer : public CObex
	{
	public:
	/**
	@publishedAll
	
	The target header checking to apply to incoming connection requests.  Defaults to
	EIfPresent.
	@see CObexServer::SetTargetChecking
	*/
	enum TTargetChecking
		{
		ENoChecking,	/** Allow all target headers to connect. */
		EIfPresent,		/** Only check target header in response to receiving one. Allows all clients
							specifying an Inbox service to connect. */
		EAlways,		/** Strict checking. Only allow connections if target header matches or no header
							received and none expected. */
		};

		IMPORT_C static CObexServer* NewL(TObexProtocolInfo& aObexProtocolInfoPtr);
		IMPORT_C static CObexServer* NewL(TObexProtocolInfo& aObexProtocolInfoPtr, TObexProtocolPolicy& aObexProtocolPolicy);
		IMPORT_C ~CObexServer();
		IMPORT_C TInt Start(MObexServerNotify* aOwner);
		IMPORT_C void Stop();
		IMPORT_C TBool IsStarted();
		IMPORT_C TOperation CurrentOperation() const;
		IMPORT_C void SetChallengeL(const TDesC& aPassword);
		IMPORT_C void ResetChallenge();
		IMPORT_C void UserPasswordL( const TDesC& aPassword); 
		IMPORT_C void SetTargetChecking(TTargetChecking aChecking);
		IMPORT_C TInt SetPutFinalResponseHeaders(CObexHeaderSet* aHeaderSet);
		
	private:
		CObexServer(TObexProtocolPolicy& aObexProtocolPolicy);
		void ConstructL(TObexProtocolInfo& aObexProtocolInfoPtr);
		TInt AcceptConnection();
		// Implementation of CObex Events
		virtual void OnPacketReceive(CObexPacket& aPacket);
		virtual void OnError(TInt aError);
		virtual void OnTransportUp();
		virtual void OnTransportDown();
		TInt PrepareConnectPacket(CObexPacket& aPacket);	
		TInt ParseConnectPacket(CObexPacket& aPacket);	
		TInt AddConnectionIDHeader(CObexPacket& aPacket);
		TInt PrepareFinalChallResponse(CObexPacket& aPacket, TConnectState& aNextState);
		TBool CheckForConnectionID(CObexBaseObject& aObject);
		void CheckTarget(TConnectState& aNextState, TInt& aRetVal);
		void ResetConnectionID();
		void SetConnectionID(TUint32 aConnectionID);
		TUint32 ConnectionID();

	private:
		MObexServerNotify* iOwner;
		TBool iEnabled;
		CObexBaseObject* iTransObject;
		CObexBaseObject* iSpecObject;
		TBool iSpecDone;
		TBool iTargetReceived;
		TTargetChecking iTargetChecking;
		TUint32 iConnectionID; 
		TBool iConnectionIdSet;
		CObexHeaderSet*	iPutFinalResponseHeaderSet;
		CObexHeader*	iHeader;
	};

/** OBEX server notification interface.

Any service that provides OBEX server functionality must implement this interface 
to receive notifications of asynchronous events from the server.

The CObexServer object handles the protocol side of an OBEX server session, 
while this class provides the server policy for a particular session.

CObexServer is a friend of this class, hence member functions are private. 

@publishedAll
@released
*/
class MObexServerNotify
	{
	friend class CObexServer;

	private:
	/** Called if an OBEX protocol error occurs.
	
	It is only called for fatal errors that cause the OBEX connection to terminate. 
	An error that does not terminate the connection, for example the server issuing 
	a semantically valid, but unrecognised command, will not be indicated.
	
	@param aError Error code that describes the OBEX error. OBEX specific error 
	codes are listed from KErrIrObexClientNoDevicesFound. 
	
	@publishedAll
	@released
	*/
	virtual void ErrorIndication(TInt aError) =0;
	
	/** Called when the underlying socket transport connection is made from a remote 
	client to the server.
	
	Note that this does not, however, indicate an OBEX connection has been successfully 
	established.
	
	You can define any low-level connection policy here. It is also a good place 
	to set up the local connection information (CObex::LocalInfo()), if any non-defaults 
	are required. 

	@publishedAll
	@released
	*/
	virtual void TransportUpIndication() =0;
	
	/** Called when the transport connection is dropped (by either party).
	
	It is called whether the OBEX connection was gracefully disconnected or not. 
	The function is the definitive place for disconnection processing.
	
	@publishedAll
	@released
	*/
	virtual void TransportDownIndication() =0;
	
	/** Called when an OBEX connection is made from a remote client.
	
	Override this function to provide any extra OBEX connection processing.
	
	@param aRemoteInfo Connection information supplied by that remote machine
	@param aInfo Further information about the requested connection (reserved)
	@return System wide error code that indicates the success of the connection
	
	@publishedAll
	@released
	*/
	virtual TInt ObexConnectIndication(const TObexConnectInfo& aRemoteInfo, const TDesC8& aInfo) =0;

	/** Called on a (graceful) OBEX disconnection by the client.
	
	Override this to provide any extra processing OBEX disconnection processing.
	
	Note that this indication will not be raised if the remote machine simply 
	drops the transport connection. However, ErrorIndication() will be called 
	if the disconnection is unexpected/ invalid (i.e. another operation was in 
	progress at the time). In all cases, TransportDownIndication() will be called.
	
	@param aInfo Contains information about the disconnection (reserved) 
	
	@publishedAll
	@released
	*/
	virtual void ObexDisconnectIndication(const TDesC8& aInfo) =0;

	/** Called on receipt of the first packet of a (valid) put request. 
	
	It is called before any parsing of the packet is performed, simply to establish 
	whether this server is interested in receiving objects at all.
	
	Note if the returned object cannot be initialised for receiving (e.g. a temporary 
	file could not be created for a CObexFileObject), ERespInternalError is returned 
	to the client.
	
	@return CObexBaseObject-derived object, which the object being put will be 
	parsed into. If this is NULL,ERespForbidden is returned to the client. 
	
	@publishedAll
	@released
	*/
	virtual CObexBufObject* PutRequestIndication() =0;

	/** Called on receipt of every packet of an OBEX PUT operation.
	
	It will always be preceded by a PutRequestIndication(). The object returned 
	by the request indication will be updated to reflect all the information received 
	concerning the object which the client is sending, from packets up to and 
	including the current one. 
	
	You can use this function to provide periodic user notification on the progress 
	of the transfer (noting that the Length attribute may take an arbitrary number 
	of packets to become non-zero, and the constraints on its accuracy). Due to 
	the nature of OBEX operations, where any header attribute can be sent at any 
	point in the transfer, this is also a good place to marshal the details of 
	a received object, and possibly prompt for action on the received object (e.g. 
	renaming on filename clashes).
	
	Note that this function could be hit quite heavily, in proportion to the size 
	of the object transferred. Therefore more consideration should be given to 
	the speed of execution of this function than that of the other indications.
	
	@return KErrNoneinstructs the server to allow the client to continue the put 
	operation. Any other value cancels the operation with an appropriate OBEX 
	server response code. 
	
	@publishedAll
	@released
	*/
	virtual TInt PutPacketIndication() =0;

	/** Called after the final put packet has been successfully received and parsed. 
	
	Note that there will not necessarily be a call to this function corresponding 
	to each PutRequestIndication() as, if an error occurs while the put is being 
	carried out, ErrorIndication() will be called instead.
	
	Before version 6.1, the return type was void.
	
	@return KErrNoneinstructs the remote client that the put completed successfully. 
	Any other value cancels the operation with an appropriate OBEX server response 
	code.
	
	@publishedAll
	@released
	*/
	virtual TInt PutCompleteIndication() =0;

	/** Called when a full get request has been received from the client. 
	
	aRequestedObject holds all the details about the object the remote client 
	has requested. Use this function to analyse the client's request, and return 
	a pointer to the object to be returned to the client, or NULL to return no 
	object. 
	
	If NULL is returned, the server will send ERespForbidden to the client; if 
	an error occurs in returning the object, ERespInternalError is returned, otherwise 
	the returned object is sent back to the client.
	
	@param aRequiredObject Details about the object the remote client has requested
	@return Object to return to the client 
	
	@publishedAll
	@released
	*/
	virtual CObexBufObject* GetRequestIndication(CObexBaseObject *aRequiredObject) =0;

	/** Called for every packet of get reply sent by the server back to the client. 
	
	The function is only called while an object is being sent to the client, not 
	while the client is providing its initial specification for the object it 
	requires. 
	
	You can use this function to provide user notification on the object being 
	sent, and its progress. As with PutPacketIndication(), you should consider 
	that this function might get called often, especially for large objects and 
	small OBEX packet sizes, so the speed of execution here is important.
	
	@return KErrNone to continue sending the object, or any other error code to 
	cancel the operation 
	
	@publishedAll
	@released
	*/
	virtual TInt GetPacketIndication() =0;

	/** Called when the final packet of the object has been returned to the client.
	
	Note like PutCompleteIndication(), this function might not be called for each 
	GetRequestIndication(), if the operation is interrupted by an error.
	
	Before version 6.1, the return type was void.
	
	@return KErrNoneinstructs the remote client that the get completed successfully. 
	Any other value cancels the operation with an appropriate OBEX server response 
	code. 
	
	@publishedAll
	@released
	*/
	virtual TInt GetCompleteIndication() =0;

	/** Called when an OBEX SETPATH command is received by the server. 
	
	@param aPathInfo SETPATH command parameters
	@param aInfo Not currently used
	@return System wide error code indicating the success of the setpath command 
	
	@publishedAll
	@released
	*/
	virtual TInt SetPathIndication(const CObex::TSetPathInfo& aPathInfo, const TDesC8& aInfo) =0;

	/** Called when an abort packet is received from the client. 
	
	An OBEX abort command simply cancels the current operation, and does not necessarily 
	have to cause the connection to be dropped. On return, a ERespSuccess packet 
	is sent to the client. 
	
	@publishedAll
	@released
	*/
	virtual void AbortIndication() =0;
	};

#endif	// __OBEXSERVER_H
