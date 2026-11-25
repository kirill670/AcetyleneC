// WapMessage.h
//
// Copyright (C) 2001 Symbian Ltd
// 

#ifndef __WAPMESSAGE_H__
#define __WAPMESSAGE_H__


#include <e32base.h>
#include <e32std.h>
#include <in_sock.h>
#include <nifman.h>
#include <in_iface.h>

/** The WAP Messaging API.  Four interfaces are defined that provide bound and fully-specified versions of WDP and Connectionless Push.
	An instantiation of each may be obtained using the CreateImplementationL() function, and must be released using Release() when no
	longer required.  Release() causes the instantiation to be deleted.

	For error codes returned by methods in this API, see <wapmsgerr.h>.  Most methods can return a set of general errors, with some
	returning additional specific errors.
*/

// TODO - These will move to a common WAPMSG/WSPTransport file at a later stage
namespace Wap
	{
	// Bearer type definition
	typedef enum
		{
		EAll,
		EIP,
		ESMS7,
		ESMS,
		EWAPSMS7,
		EWAPSMS
		} TBearer;

	// Port number definition
	typedef TUint16 TPort;
 
	class TAddressInfo
		{
	public:
		TName iName;			// Interface name
		TInetAddr iAddress;		// Interface IP Address (*)
		};
	}
									  
/** Bound WDP
*/
class CWapBoundDatagramService : public CBase
	{
public: // creation/deletion
	IMPORT_C static CWapBoundDatagramService* NewL();
	IMPORT_C virtual ~CWapBoundDatagramService();

public: // API methods

	/** 
	 * Connect to the wapstack, opening an endpoint that can be used to listen for subsequent incoming datagrams.
	 * All WapBoundDatagramService implementaions must automatically close this endpoint upon destruction.
	 * This overload of the Connect method allows an IP address associated with a network interface to be specified. 
	 * In multihomed systems this can be used to specify which network interface the endpoint should be bound to.
	 * @param aBearer (in) the bearer to listen on (use EAll for all bearers)
	 * @param aPort	(in) the port to listen on. If set to 0, a local port will be chosen for the client's first SendTo
	 * @param aInetAddr (in) the ip address of the network interface that should be used in a multihomed system.
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt Connect(Wap::TBearer aBearer, Wap::TPort aPort,TInetAddr aInetAddr)=0;	

	/** 
	 * Connect to the wapstack, opening an endpoint that can be used to listen for subsequent incoming datagrams.
	 * All WapBoundDatagramService implementaions must automatically close this endpoint upon destruction.
	 * @param aBearer (in) the bearer to listen on (use EAll for all bearers)
	 * @param aPort	(in) the port to listen on. If set to 0, a local port will be chosen for the client's first SendTo
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt Connect(Wap::TBearer aBearer,Wap::TPort aPort)=0;

	/**
	 * Send data to a remote endpoint.
	 * @param aRemoteHost (in) the bearer-dependent address of the remote host to which the data will be sent
	 * @param aRemotePort (in) the port on the remote host to which the data will be sent
	 * @param aBuffer (in) the data buffer to be written over the connection
	 * @param aBearer (in) the bearer to be used, if the bound connection was opened with 'all'
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */ 
	virtual TInt SendTo(const TDesC8& aRemoteHost, Wap::TPort aRemotePort, const TDesC8& aBuffer, Wap::TBearer aBearer)=0;

	/**
	 * Wait for a datagram to be received, and discover how large a buffer is required to retrieve it.
	 * This asyncronous method waits for a datagram to be received and will then complete allowing the client to discover how large a buffer
	 * is needed to retrieve the entire datagram that has been received.
	 * A subsiquent call to RecvFrom with a buffer of sufficent size will then allow the client to retrieve the datagram fully.
	 * @param aDataSizePckg (out) the size of data subsequently received, in bytes
	 * @param aReqStatus (inout) used to signal when a data size is known
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt AwaitRecvDataSize(TPckg<TUint16>& aDataSizePckg, TRequestStatus& aReqStatus)=0;

	/**
	 * receive data on a bound port.
	 * An asynchronous notification is sent to the client when data arrives.
	 * @param aRemoteHost (out) the bearer-dependent address of the remote host from which the data was received
	 * @param aRemotePort (out) the port on the remote host from which the data was received
	 * @param aBuffer (out) a client-allocated data buffer to be filled with data received. Data that overflows the buffer is discarded.
	 * @param aTruncated (out) indicates whether the received datagram was truncated to fit in the client's supplied buffer
	 * @param aReqStatus (inout) used to notify the client that a datagram was received
	 * @param aTimeout (in) an optional millisecond time-out which allows a timed read to be made.  If no data is received 
	 * within the timeout period the request completes with KErrTimedOut. If a value of 0 is supplied the timeout is infinite.
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt RecvFrom(TDes8& aRemoteHost, Wap::TPort& aRemotePort, TDes8& aBuffer, TBool& aTruncated, 
							TRequestStatus& aReqStatus, TUint32 aTimeout)=0;
 
	/**
	 * Cancel a previously requested asynchronous RecvFrom or AwaitRecvDataSize notification. 
	 * If a datagram arrives at the local host, it will be discarded.
	 * @since 7.0
	 * @public
	 */
	virtual void CancelRecv()=0;

	/** 
	 * Get the local port of this endpoint.Useful if one was chosen automatically.
 	 * @param aPort (out) the port number
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt GetLocalPort(Wap::TPort& aPort)=0;

	/**
	 * Get the local address of this endpoint.
	 * @param aLocalHost (inout) the address of the local host. A reference to a HBufC8 pointer should 
	 * be passed in. This pointer MUST be null! A HBufC8 will be allocated to hold the address, ownership 
	 * of this buffer will be passed over to the client.
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt GetLocalAddress(HBufC8*& aLocalHost)=0;

	/**
	 * Get the bearer on which a received datagram arrived.
	 * Useful when EAll was specified in Connect()
	 * @param aBearer (out) the bearer
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt GetBearer(Wap::TBearer& aBearer)=0;	

	/**
	 * Query the WDP bearer for its maximum datagram size and its nominal datagram size.
	 * @param aMaxSize (out) the maximum datagram size
	 * @param aNorminalSize (out) the nominal datagram size (nominal = size within which a datagram won't 
	 * have to be split into smaller individual messages and then re-assembled at the other end).  
	 * This will fail for a stream connection
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt GetDatagramSizes(TUint16& aMaxSize, TUint16& aNominalSize)=0;	

protected: // methods
	IMPORT_C CWapBoundDatagramService();
	IMPORT_C void ConstructL();

private: // attributes
	/// D'tor Key identification required for ECOM
	TUid iDtor_ID_Key;
	};

/** Fully-Specified WDP
*/
class CWapFullySpecDatagramService : public CBase
	{
public: // creation/deletion
	IMPORT_C static CWapFullySpecDatagramService* NewL();
	IMPORT_C virtual ~CWapFullySpecDatagramService();

public: // API methods

	/** 
	 * Connect to the wapstack, opening an endpoint which is to be used only with a single, named remote host.
	 * All WapBoundDatagramService implementaions must automatically close this endpoint upon destruction.
	 * This overload of the Connect method allows an IP address associated with a network interface to be specified. 
	 * In multihomed systems this can be used to specify which network interface the endpoint should be bound to.
	 * @param aRemoteHost (in) the bearer-dependent address of the remote host with which the data will be exchanged
	 * @param aRemotePort (in) the port on the remote host to which data will be sent
	 * @param aBearer (in) the bearer to use (not EAll)	
	 * @param aInetAddr (in) the ip address of the network interface that should be used in a multihomed system.
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt Connect(const TDesC8& aRemoteHost, Wap::TPort aRemotePort, Wap::TBearer aBearer, TInetAddr aInetAddr)=0;

	/** 
	 * Connect to the wapstack, opening an endpoint which is to be used only with a single, named remote host.
	 * All WapBoundDatagramService implementaions must automatically close this endpoint upon destruction.
	 * This overload of the Connect method allows an IP address associated with a network interface to be specified. 
	 * In multihomed systems this can be used to specify which network interface the endpoint should be bound to.
	 * @param aRemoteHost (in) the bearer-dependent address of the remote host with which the data will be exchanged
	 * @param aRemotePort (in) the port on the remote host to which data will be sent
	 * @param aBearer (in) the bearer to use (not EAll)	
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt Connect(const TDesC8& aRemoteHost, Wap::TPort aRemotePort, Wap::TBearer aBearer)=0;

	/**
	 * Send data on a fully-specified connection.
	 * @param aBuffer (in) the data buffer to be written over the connection
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt Send(const TDesC8& aBuffer)=0;

	/**
	 * Wait for a datagram to be received, and discover how large a buffer is required to retrieve it.
	 * This asyncronous method waits for a datagram to be received and will then complete allowing the client to discover how large a buffer
	 * is needed to retrieve the entire datagram that has been received.
	 * A subsiquent call to RecvFrom with a buffer of sufficent size will then allow the client to retrieve the datagram fully.
	 * @param aDataSizePckg (out) the size of data subsequent ly received, in bytes
	 * @param aReqStatus (inout) used to signal when a data size is known
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt AwaitRecvDataSize(TPckg<TUint16>& aDataSizePckg, TRequestStatus& aReqStatus)=0; 

	/**
	 * receive data on a bound port.
	 * An asynchronous notification is sent to the client when data arrives.
	 * @param aBuffer (out) a client-allocated data buffer to be filled with data received. Data that overflows the buffer is discarded.
	 * @param aTruncated (out) indicates whether the received datagram was truncated to fit in the client's supplied buffer
	 * @param aReqStatus (inout) used to notify the client that a datagram was received
	 * @param aTimeout (in) an optional millisecond time-out which allows a timed read to be made.  If no data is received 
	 * within the timeout period the request completes with KErrTimedOut. If a value of 0 is supplied the timeout is infinite.
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt Recv(TDes8& aBuffer, TBool& aTruncated, TRequestStatus& aReqStatus, TUint32 aTimeout)=0;			

	/**
	 * Cancel a previously requested asynchronous Recv or AwaitRecvDataSize notification.
	 * If a datagram arrives at the local host, it will be discarded.
	 * @since 7.0
	 * @public
	 */
	virtual void CancelRecv()=0;

	/** 
	 * Get the local port of this endpoint.Useful if one was chosen automatically.
 	 * @param aPort (out) the port number
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt GetLocalPort(Wap::TPort& aPort)=0;	

	/**
	 * Get the local address of this endpoint.
	 * @param aLocalHost (inout) the address of the local host. A reference to a HBufC8 pointer should 
	 * be passed in. This pointer MUST be null! A HBufC8 will be allocated to hold the address, ownership 
	 * of this buffer will be passed over to the client.
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt GetLocalAddress(HBufC8*& aLocalHost)=0;	

	/**
	 * Query the WDP bearer for its maximum datagram size and its nominal datagram size.
	 * @param aMaxSize (out) the maximum datagram size
	 * @param aNorminalSize (out) the nominal datagram size (nominal = size within which a datagram won't 
	 * have to be split into smaller individual messages and then re-assembled at the other end).  
	 * This will fail for a stream connection
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt GetDatagramSizes(TUint16& aMaxSize, TUint16& aNominalSize)=0;	

protected: // methods
	IMPORT_C CWapFullySpecDatagramService();
	IMPORT_C void ConstructL();

private: // ECOM
	// D'tor Key identification required for ECOM
	TUid iDtor_ID_Key;
	};

/** Bound Connectionless Push
*/
class CWapBoundCLPushService : public CBase
{
public: // creation/deletion
	IMPORT_C static CWapBoundCLPushService* NewL();
	IMPORT_C virtual ~CWapBoundCLPushService();

public: // API methods

	/**
	 * Opens a socket which is to be used to listen for subsequent incoming Push messages from any sender;
	 * i.e. it has only been 'bound' to the local address
	 * This overload of the Connect method allows an IP address associated with a network interface to be specified. 
	 * In multihomed systems this can be used to specify which network interface the endpoint should be bound to.
	 * @param aBearer (in) the bearer to listen on (use EAll for all bearers)
	 * @param aPort (in) the port to listen on. If set to 0, a local port will be chosen for the client's first SendTo
	 * @param aSecure (in) security flag indicates whether WTLS will be used or not
	 * @param aInetAddr (in) the address of the adapter to use
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt Connect(Wap::TBearer aBearer, Wap::TPort aPort, TBool aSecure, TInetAddr aInetAddr)=0;

	/**
	 * Opens a socket which is to be used to listen for subsequent incoming Push messages from any sender;
	 * i.e. it has only been 'bound' to the local address
	 * @param aBearer (in) the bearer to listen on (use EAll for all bearers)
	 * @param aPort (in) the port to listen on. If set to 0, a local port will be chosen for the client's first SendTo
	 * @param aSecure (in) security flag indicates whether WTLS will be used or not
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt Connect(Wap::TBearer aBearer, Wap::TPort aPort, TBool aSecure)=0;

	/**
	 * Request an asynchronous notification upon arrival of the next push messages on the listening connection.
	 * The request completes upon receipt of the message, filling the buffers with as much received data as possible.  
	 * A return code will indicate whether further data remains.  The call must be re-issued for subsequent messages 
	 * or to receive remaining data from a previous push message.
	 * @param aPushHeaders (out) (client-allocated) - when a push message arrives the header data is written here
	 * @param aPushBody (out) (client-allocated) - when a push message arrives the body data is written here
	 * @param aPushIdPckg (out) when a push message arrives an integer ID that uniquely specifies the message is written here
	 * @param aReqStatus (inout) used by the service provider to notify the client when a push has arrived. 
	 * EMoreData is returned if more pushed data is available
	 * @retval TInt	KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt AwaitPush(TDes8& aPushHeaders, TDes8& aPushBody, TPckgBuf<TUint8>& aPushIdPckg, TRequestStatus& aReqStatus)=0;
 
	/**
	 * Cancel a previously-requested push message notification. If a push message arrives the client will not be notified.
	 * @since 7.0
	 * @public
	 */
	virtual void CancelAwaitPush()=0;

	/** 
	 * Get the local port of this endpoint.Useful if one was chosen automatically.
 	 * @param aPort (out) the port number
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt GetLocalPort(Wap::TPort& aPort)=0;	

	/**
	 * Get the local address of this endpoint.
	 * @param aLocalHost (inout) the address of the local host. A reference to a HBufC8 pointer should 
	 * be passed in. This pointer MUST be null! A HBufC8 will be allocated to hold the address, ownership 
	 * of this buffer will be passed over to the client.
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt GetLocalAddress(HBufC8*& aLocalHost)=0;

	/**
	 * Get the bearer on which the push message arrived.
	 * Useful when EAll was specified in Connect()
	 * @param aBearer (out) the bearer
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt GetBearer(Wap::TBearer& aBearer)=0;

protected: // methods
	IMPORT_C CWapBoundCLPushService();
	IMPORT_C void ConstructL();

private: // ECOM
	// D'tor Key identification required for ECOM
	TUid iDtor_ID_Key;
};

/** Fully-Specified Connectionless Push
*/
class CWapFullySpecCLPushService : public CBase
{
public: // creation/deletion
	IMPORT_C static CWapFullySpecCLPushService* NewL();
	IMPORT_C virtual ~CWapFullySpecCLPushService();

public: // API methods

	/**
	 * Opens a socket which is to be used only with a single, named remote host.
	 * This overload of the Connect method allows an IP address associated with a network interface to be specified. 
	 * In multihomed systems this can be used to specify which network interface the endpoint should be bound to.
	 * @param aRemoteHost (in) the bearer-dependent address of the remote host with which the data will be exchanged
	 * @param aRemotePort (in) the port on the remote host to which data will be sent
	 * @param aBearer (in) the bearer to use (not EAll)
	 * @param aSecure (in) security flag indicates whether WTLS will be used or not
	 * @param aInetAddr (in) the address of the adapter to use
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.			  
	 * @since 7.0
	 * @public
	 */
	virtual TInt Connect(const TDesC8& aRemoteHost, Wap::TPort aRemotePort, Wap::TBearer aBearer, TBool aSecure, TInetAddr aInetAddr)=0;

	/**
	 * Opens a socket which is to be used only with a single, named remote host.
	 * @param aRemoteHost (in) the bearer-dependent address of the remote host with which the data will be exchanged
	 * @param aRemotePort (in) the port on the remote host to which data will be sent
	 * @param aBearer (in) the bearer to use (not EAll)
	 * @param aSecure (in) security flag indicates whether WTLS will be used or not
	 * @param aInetAddr (in) the address of the adapter to use
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.			  
	 * @since 7.0
	 * @public
	 */
	virtual TInt Connect(const TDesC8& aRemoteHost, Wap::TPort aRemotePort, Wap::TBearer aBearer, TBool aSecure)=0;

	///  

	/**
	 * Request an asynchronous notification upon arrival of the next push messages on the listening connection.
	 * The request completes upon receipt of the message, filling the buffers with as much received data as possible.  
	 * A return code will indicate whether further data remains.  The call must be re-issued for subsequent messages 
	 * or to receive remaining data from a previous push message.
	 * @param aPushHeaders (out) (client-allocated) - when a push message arrives the header data is written here
	 * @param aPushBody (out) (client-allocated) - when a push message arrives the body data is written here
	 * @param aPushIdPckg (out) when a push message arrives an integer ID that uniquely specifies the message is written here
	 * @param aReqStatus (inout) used by the service provider to notify the client when a push has arrived
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt AwaitPush(TDes8& aPushHeaders, TDes8& aPushBody, TPckgBuf<TUint8>& aPushIdPckg, TRequestStatus& aReqStatus)=0;

	/**
	 * Cancel a previously-requested push message notification.  If a push message arrives the client will not be notified.
	 * @since 7.0
	 * @public
	 */ 
	virtual void CancelAwaitPush()=0;

	/** 
	 * Get the local port of this endpoint.Useful if one was chosen automatically.
 	 * @param aPort (out) the port number
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt GetLocalPort(Wap::TPort& aPort)=0;	/// (out) the port number

	/**
	 * Get the local address of this endpoint.
	 * @param aLocalHost (inout) the address of the local host. A reference to a HBufC8 pointer should 
	 * be passed in. This pointer MUST be null! A HBufC8 will be allocated to hold the address, ownership 
	 * of this buffer will be passed over to the client.
	 * @retval TInt KErrNone on successful completion, or one of the system error codes on failure.
	 * @since 7.0
	 * @public
	 */
	virtual TInt GetLocalAddress(HBufC8*& aLocalHost)=0;	/// (out) the address of the local host

protected: // methods
	IMPORT_C CWapFullySpecCLPushService();
	IMPORT_C void ConstructL();

private: // ECOM
	// D'tor Key identification required for ECOM
	TUid iDtor_ID_Key;
};


// Utility class for client/implementation use.
class CWapMessageUtils : public CBase
	{
public:
	/// Return a list of all the addresses that are available
	IMPORT_C static TInt GetLocalAddressesL(RArray<Wap::TAddressInfo>& aAddressInfo); 
	};

#endif // __WAPMESSAGE_H__