// MmfControllerFramework.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//


#ifndef __MMFCONTROLLERFRAMEWORK_H__
#define __MMFCONTROLLERFRAMEWORK_H__

#include <e32base.h>
#include <e32std.h>
#include <mmf/common/mmfutilities.h>
#include <mmf/common/mmfcontrollerframeworkbase.h>
#include <mmf/common/mmfipc.h>

_LIT(KMMFControllerProxyServerName, "MMFControllerProxyServer");
/**
 * @internalComponent
 */
#define KMMFControllerProxyVersion TVersion(7,1,1)
/**
 * @internalComponent
 */
const TInt KMMFControllerProxyMaxHeapSize = 0x1000000;//16MB
/**
 * @internalComponent
 */
const TInt KMMFControllerProxyMaxCachedMessages = 10;
/**
 * @internalComponent
 * Signals that the message is destined for the controller proxy
 */
const TInt KMMFObjectHandleControllerProxy = -1; 
/**
 * @publishedAll
 *
 * Signals that the message is destined for the controller
 */
const TInt KMMFObjectHandleController = -2;
/**
 * @publishedAll
 *
 * Null, or invalid, object handle
 */
const TInt KMMFObjectHandleNull = 0;
/**
 * @internalComponent
 *
 * The first valid object handle.  The MMF Object container will 
 * begin iterating from here when generating object handles.
 */
const TInt KMMFObjectHandleFirstValid = 1;
/**
 * @internalComponent
 */
const TInt KMmfControllerThreadShutdownTimeout = 20000000;	// 20 seconds

/**
 * @internalComponent
 *
 * The UID and messages associated with the controller proxy interface.
 */
const TUid KUidInterfaceMMFControllerProxy = {0x101F77E7};
/**
 * @internalComponent
 */
enum TMMFControllerProxyMessages
	{
	EMMFControllerProxyLoadControllerPluginByUid,
	EMMFControllerProxyReceiveEvents,
	EMMFControllerProxyCancelReceiveEvents
	};


/**
@publishedAll

Describes the destination of a message in the controller framework.

The destination is defined by a UID describing the interface and an integer object handle.
The controller framework uses this information when it receives a message to decide where 
to send the message.

The controller plugin and controller proxy use the special constant handles 
<code>KMMFObjectHandleControllerProxy<\code> and <code>KMMFObjectHandleController<\code> for
efficiency.
@since 7.0s
*/
class TMMFMessageDestination
	{
public:
/**
Default constructor.

Assigns a null uid to the interface, and a null handle to the handle.
@since 7.0s
*/
	IMPORT_C TMMFMessageDestination();

/**
Constructor for sending messages to the controller plugin.

Assigns <code>KMMFObjectHandleController<\code> to the destination handle.
@param	"aInterfaceId"	"The uid of the interface of this message destination."
@since 7.0s
*/
	IMPORT_C TMMFMessageDestination(TUid aInterfaceId);

/**
Full constructor.

@param	"aInterfaceId"			"The uid of the interface of this message destination."
@param	"aDestinationHandle"	"The handle of the destination object in the controller 
								framework."
@since 7.0s
*/
	IMPORT_C TMMFMessageDestination(TUid aInterfaceId, TInt aDestinationHandle);

/**
Copy constructor.

@param	"aOther"	"The TMMFMessageDestination object to be copied."
@since 7.0s
*/
	IMPORT_C TMMFMessageDestination(const TMMFMessageDestination& aOther);

/**
Returns the uid of the interface of the message destination.

@return	"The interface uid."
@since 7.0s
*/
	IMPORT_C TUid InterfaceId() const;

/**
Returns the handle of the destination object in the controller framework.

@return	"The destination handle."
@since 7.0s
*/
	IMPORT_C TInt DestinationHandle() const;

/**
Compares two destinations.

@param "aOther"	"The object to be compared with this object."
@return "ETrue if the objects are the same"
@return "EFalse if the objects are different."
@since 7.0s
*/
	IMPORT_C TBool operator==(const TMMFMessageDestination& aOther) const;

private:
	TUid iInterfaceId;
	TInt iDestinationHandle;
	};

/**
 * @publishedAll
 */
typedef TPckgBuf<TMMFMessageDestination> TMMFMessageDestinationPckg;


/**
@publishedAll

Encapsulation of an RMessage or an RMessage2 to provide protection to controller plugins
from the changes occurring with secure APIs.

Adds required destination information to message so the controller framework
can determine which object the message is for.

Adds capability to check whether the message has been completed.

Allows two descriptors to be read from the client, and one descriptor to be copied to the client.
@see RMMFControllerProxy::SendSync
@see RMMFControllerProxy::SendAsync
@since 7.0s
*/
class TMMFMessage
	{
friend class CMMFControllerProxySession;
public:
/**
Copy constructor.

A controller plugin should use this to take a copy of the message when it must wait for some
other event before completing it.
@param "aMessage" "The message object to copy."
@since 7.0s
*/
	IMPORT_C TMMFMessage(const TMMFMessage& aMessage);

/**
Returns the destination of the message.

@return	"The destination of the message, consisting of a UID defining the interface and the
		handle of the destination object."
@since	7.0s
*/
	IMPORT_C const TMMFMessageDestination& Destination();

/**
Returns an integer describing the function being called. Equivalent to 
<code>RMessage::Function()<\code>.

@return	"The function being called over IPC."
@see	RMessage::Function()
@since	7.0s
*/
	IMPORT_C TInt Function();

/**
Returns the size of the first descriptor that can be copied over from the client.

Use this to create a descriptor of appropriate size before reading the data from the client.

@return	"The size of data 1."
@since	7.0s
*/
	IMPORT_C TInt SizeOfData1FromClient();

/**
Copy the first descriptor from the client.

@param	"aDes"	"A descriptor defining the area of memory into which the data from the client
				will be copied. Note, the descriptor must be of sufficient size."
@return	"One of the system-wide error codes. In particular, KErrBadDescriptor will be returned
		if the client did not provide a valid descriptor."
@since 7.0s
*/
	IMPORT_C TInt ReadData1FromClient(TDes8& aDes);

/**
Copy the first descriptor from the client.

@param	"aDes"	"A descriptor defining the area of memory into which the data from the client
				will be copied. Note, the descriptor must be of sufficient size."
@leave	""		"One of the system-wide error codes. In particular, the leave code 
				KErrBadDescriptor will be used if the client did not provide a valid descriptor."
@since 7.0s
*/
	IMPORT_C void ReadData1FromClientL(TDes8& aDes);
	

/**
Returns the size of the second descriptor that can be copied over from the client.

Use this to create a descriptor of appropriate size before reading the data from the client.

@return	"The size of data 2."
@since	7.0s
*/
	IMPORT_C TInt SizeOfData2FromClient();

/**
Copy the second descriptor from the client.

@param	"aDes"	"A descriptor defining the area of memory into which the data from the client
				will be copied. Note, the descriptor must be of sufficient size."
@return	"One of the system-wide error codes. In particular, KErrBadDescriptor will be returned
		if the client did not provide a valid descriptor."
@since 7.0s
*/
	IMPORT_C TInt ReadData2FromClient(TDes8& aDes);

/**
Copy the second descriptor from the client.

@param	"aDes"	"A descriptor defining the area of memory into which the data from the client
				will be copied. Note, the descriptor must be of sufficient size."
@leave	""		"One of the system-wide error codes. In particular, the leave code 
				KErrBadDescriptor will be used if the client did not provide a valid descriptor."
@since 7.0s
*/
	IMPORT_C void ReadData2FromClientL(TDes8& aDes);

/**
Copy data back to the client.

@param	"aDes"	"The data to be copied back to the client.  Note that the client must
				have already created a descriptor of sufficient size for the data to be
				copied into."
@return			"One of the system-wide error codes. In particular, the error code 
				KErrBadDescriptor will be returned if the client did not provide a valid 
				descriptor."
@since 7.0s
*/
	IMPORT_C TInt WriteDataToClient(const TDesC8& aDes);

/**
Copy data back to the client.

@param	"aDes"	"The data to be copied back to the client.  Note that the client must
				have already created a descriptor of sufficient size for the data to be
				copied into."
@leave	""		"One of the system-wide error codes. In particular, the leave code 
				KErrBadDescriptor will be used if the client did not provide a valid descriptor."
@since 7.0s
*/
	IMPORT_C void WriteDataToClientL(const TDesC8& aDes);
	

/**
Signal to the client that its request has been completed.

Equivalent to <code>RMessage::Complete<\code>.

@param	"aReason"	"The result code to be given back to the client."
@since 7.0s
*/
	IMPORT_C void Complete(TInt aReason);

/**
Checks whether this message has already been completed.

@return  "ETrue if the message has been completed, EFalse if not."
@since 7.0s
*/
	IMPORT_C TBool IsCompleted();
private:
/**
Constructs a TMMFMessage from an RMmfIpcMessage.
This is private since it only needs to be done by the class CMMFControllerProxySession.
@since 7.0s
*/
	TMMFMessage(const RMmfIpcMessage& aMessage);
/**
Gets the destination info from the client. 
This is private since it only needs to be done by the class CMMFControllerProxySession.
@since 7.0s
*/
	void FetchDestinationL();
private:
#ifdef __MMF_USE_IPC_V2__
/**The encapsulated message*/
	RMessagePtr2 iMessage;
/**The encapsulated function*/
	TInt iFunction;
/**Private padding to preserve BC with earlier versions*/
	TInt iDummyPadding[6];
#else
/**The RMessage encapsulated by this object.*/
	RMessage iMessage;
#endif // __MMF_USE_IPC_V2__

/**The destination of this message.*/
	TMMFMessageDestination iDestination;

/**Defines whether this object has yet to be completed.*/
	TBool iAmCompleted;
	};


/**
@internalComponent

RSessionBase-based client class to handle the creation of the controller thread and
message sending over IPC.

The controller proxy is responsible for sending and recieving messages over IPC; it does not
care exactly what those messages are.

@since 7.0s
@lib MMFControllerFramework.lib
*/
class RMMFControllerProxy : public RMmfSessionBase
	{
public:
/**
Constructor.
@since 7.0s
@lib MMFControllerframework.lib
*/
	IMPORT_C RMMFControllerProxy();

/**
Create a new thread and load a controller plugin into that thread.

@param	"aControllerUid"	"The UID of the controller plugin to be loaded."
@return	"One of the system-wide error codes."
@since	7.0s
@lib	MMFControllerFramework.lib
*/
	IMPORT_C TInt LoadController(TUid aControllerUid);

/**
Delete the controller plugin and close its thread.

Clients must call Close() on the controller proxy, otherwise leaks will occur.
@since	7.0s
@lib	MMFControllerFramework.lib
*/
	IMPORT_C void Close();
	
/**
Send a message synchronously to the controller thread.

The controller framework will analyze the message to determine its correct destination.

Note: This method will not return until the controller framework has serviced the command.

@param	"aDestination"	"The destination of the message, consisting of the uid of
						the interface of this message."
@param	"aFunction"		"The function number to indicate which function is to be called
						on the interface defined in the aDestination parameter."
@param	"aDataTo1"		"A reference to the first chunk of data to be copied to the controller 
						framework. The exact contents of the data are dependent on the 
						interface being called.  Can be NULL."
@param	"aDataTo2"		"A reference to the second chunk of data to be copied to the controller 
						framework. The exact contents of the data are dependent on the 
						interface being called.  Can be NULL."
@param	"aDataFrom"		"A reference to an area of memory to which the controller framework will 
						write any data to be passed back to the client.  Can't be NULL."
@return	"The result of the request.  Exact range of values is dependent on the interface."
@lib	MMFControllerFramework.lib
@since	7.0s
*/
	IMPORT_C TInt SendSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom) const;
/**
Send a message synchronously to the controller thread.

The controller framework will analyze the message to determine its correct destination.

Note: This method will not return until the controller framework has serviced the command.

@param	"aDestination"	"The destination of the message, consisting of the uid of
						the interface of this message."
@param	"aFunction"		"The function number to indicate which function is to be called
						on the interface defined in the aDestination parameter."
@param	"aDataTo1"		"A reference to the first chunk of data to be copied to the controller 
						framework. The exact contents of the data are dependent on the 
						interface being called.  Can be NULL."
@param	"aDataTo2"		"A reference to the second chunk of data to be copied to the controller 
						framework. The exact contents of the data are dependent on the 
						interface being called.  Can be NULL."
@return	"The result of the request.  Exact range of values is dependent on the interface."
@lib	MMFControllerFramework.lib
@since	7.0s
*/
	IMPORT_C TInt SendSync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction, const TDesC8& aDataTo1, const TDesC8& aDataTo2) const;

/**
Send a message asynchronously to the controller thread.

The controller framework will analyze the message to determine its correct destination.

Note: This method will return immediately.  The RunL of the active object owning the 
<code>aStatus<\code> parameter will be called when the command is completed by the 
controller framework.

@param	"aDestination"	"The destination of the message, consisting of the uid of
						the interface of this message."
@param	"aFunction"		"The function number to indicate which function is to be called
						on the interface defined in the aDestination parameter."
@param	"aDataTo1"		"A reference to the first chunk of data to be copied to the controller 
						framework. The exact contents of the data are dependent on the 
						interface being called.  Can be NULL."
@param	"aDataTo2"		"A reference to the second chunk of data to be copied to the controller 
						framework. The exact contents of the data are dependent on the 
						interface being called.  Can be NULL."
@param	"aDataFrom"		"A reference to an area of memory to which the controller framework will 
						write any data to be passed back to the client.  Can't be NULL."
@param "aStatus"		"The TRequestStatus of an active object.  This will contain the 
						result of the request on completion.  The exact range of 
						result values is dependent on the interface."
@lib	MMFControllerFramework.lib
@since	7.0s
*/
	IMPORT_C void SendAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction,  const TDesC8& aDataTo1, const TDesC8& aDataTo2, TDes8& aDataFrom, TRequestStatus& aStatus) const;
/**
Send a message asynchronously to the controller thread.

The controller framework will analyze the message to determine its correct destination.

Note: This method will return immediately.  The RunL of the active object owning the 
<code>aStatus<\code> parameter will be called when the command is completed by the 
controller framework.

@param	"aDestination"	"The destination of the message, consisting of the uid of
						the interface of this message."
@param	"aFunction"		"The function number to indicate which function is to be called
						on the interface defined in the aDestination parameter."
@param	"aDataTo1"		"A reference to the first chunk of data to be copied to the controller 
						framework. The exact contents of the data are dependent on the 
						interface being called.  Can be NULL."
@param	"aDataTo2"		"A reference to the second chunk of data to be copied to the controller 
						framework. The exact contents of the data are dependent on the 
						interface being called.  Can be NULL."
@param "aStatus"		"The TRequestStatus of an active object.  This will contain the 
						result of the request on completion.  The exact range of 
						result values is dependent on the interface."
@lib	MMFControllerFramework.lib
@since	7.0s
*/
	IMPORT_C void SendAsync(const TMMFMessageDestinationPckg& aDestination, TInt aFunction,  const TDesC8& aDataTo1, const TDesC8& aDataTo2, TRequestStatus& aStatus) const;

/**
Register to receive events from the controller framework.

Events can be generated at any time, and are generally associated with things that occur
due to something happening internally within the controller. For example, an event will
be generated if the controller stops playing due to reaching the end of a file.
	
@param	"aEventPckg"	"A reference to a TMMFEventPckg object that must be member data
						of the active object calling this method.  The details of the event
						will be copied into this object when an event occurs."
@param "aStatus"		"The TRequestStatus of the active object calling this method."
@lib	MMFControllerFramework.lib
@see	TMMFEvent
@see	CMMFControllerEventMonitor
@since	7.0s
*/
	IMPORT_C void ReceiveEvents(TMMFEventPckg& aEvent, TRequestStatus& aStatus);

/**
Cancel a previous registration to receive events from the controller framework.

This must be called from the <code>DoCancel()<\code> method of the active object using the
ReceiveEvents() API.

@return "One of the standard system-wide error codes."
@lib	MMFControllerFramework.lib
@see	TMMFEvent
@since	7.0s
*/
	IMPORT_C TInt CancelReceiveEvents();
private:
	/**Creates the new thread*/
	TInt DoCreateSubThread(const TDesC& aName, TUint aMaxHeapSize);

/**
Determines the maximum heap size required by the selected controller
*/
	TUint ControllersMaxHeapSizeL(TUid aControllerUid);

private:
	/**The thread in which the controller plugin will run.*/
	RThread iSubThread;
	/**Used to hold destination for messages from the controller proxy 
	(not from clients calling SendSync/SendAsync!!)*/
	TMMFMessageDestinationPckg iDestinationPckg;
	};

/**
@internalComponent

Startup parameters passed into the threadfunction of the controller proxy subthread.

Used to signal back to the main thread when the subthread is fully started.
@since 7.0s
*/
class TMMFControllerProxyStartParams
	{
public:
/**
Constructor.

@param	"aStatus"	"The TRequestStatus to be signalled when the ControllerProxyServer is up and running."
@since 7.0s
*/
	TMMFControllerProxyStartParams(TRequestStatus& aStatus) : iStatus(&aStatus), iThreadId(RThread().Id())
		{aStatus=KRequestPending;};

/**
Signal the client thread that the server is up and running.
@leave	""	"This method can leave if it fails to open a handle to the client thread."
@since 7.0s
*/
	void SignalL()
		{
		RThread starter;
		User::LeaveIfError(starter.Open(iThreadId));
		starter.RequestComplete(iStatus,KErrNone);
		starter.Close();
		};
public:
	TRequestStatus* iStatus;
	TThreadId iThreadId;
	};

/**
@internalComponent

Used to Kill the controller thread either immediately or after a timeout.
Used by the controller thread on startup to prevent orphaning if no sessions are created to it.
*/
class CMMFControllerProxyShutdown : public CTimer
	{
	enum {EMMFControllerProxyShutdownDelay=1000000};	// 1s
public:
/**
Create a new shutdown timer.
@leave	""	"This method can leave with one of the system-wide error codes."
@since 7.0s
*/
	static CMMFControllerProxyShutdown* NewL();

/**
Start the shutdown timer.  The RunL of this active object will be called after
<code>EMMFControllerProxyShutdownDelay<\code> microseconds.
@since 7.0s
*/
	void Start();

/**
Shut down the controller thread immediately.

Calls <code>CActiveScheduler::Stop()<\code>.
@since 7.0s
*/
	void ShutdownNow();
private:
	CMMFControllerProxyShutdown();
	void ConstructL();

/**
Calls <code>ShutdownNow()<\code>.
@since 7.0s
*/
	void RunL();
	};


/**
@publishedAll

Mixin class to define an object capable of handling an event within the controller framework.
*/
class MAsyncEventHandler
	{
public:
/**
Send an event to the client.
@param "aEvent" "The event."
@since 7.0s
*/
	virtual TInt SendEventToClient(const TMMFEvent& aEvent) = 0;
	};

/**
@publishedAll

Used to hold on to an TMMFMessage so we can complete it asynchronously to 
send an event to the client.

@since 7.0s
*/
class CMMFEventReceiver : public CBase
	{
public:
/**
Construct a new event receiver.
@param "aMessage"	"The message to be completed when an event occurs."
@leave ""			"This method may leave with one of the system-wide error codes."
@return				"The newly created event receiver."
@since				7.0s
*/
	static CMMFEventReceiver* NewL(const TMMFMessage& aMessage);

/**
Destructor.
Completes the message with KErrCancel if the message hasn't already been completed.
@since 7.0s
*/
	~CMMFEventReceiver();

/**
Send an event to the client.
@param "aEvent" "The event."
@since  7.0s
*/
	void SendEvent(const TMMFEvent& aEvent);
private:
/**
Constructor.
@param "aMessage"	"The message to be completed when an event occurs."
@since				7.0s
*/
	CMMFEventReceiver(const TMMFMessage& aMessage);
private:
/** The message to be completed when an event occurs.*/
	TMMFMessage iMessage;
	};



/**
@internalComponent

The controller proxy server.  

The main server inside the controller thread, responsible for creating and destroying the single
session used to transmit messages from the client to the server.

Every controller plugin runs in its own thread, and has its own controller proxy server.

@since 7.0s
*/
class CMMFControllerProxyServer : public CMmfIpcServer
	{
public:
/**
Construct the server.
@leave ""			"This method may leave with one of the system-wide error codes."
@return				"The newly created server."
@since				7.0s
*/
	static CMMFControllerProxyServer* NewL();
/**
Destructor.
@since 7.0s
*/
	~CMMFControllerProxyServer();
/**
Static thread function.

The address of this function is passed into RThread::Create.
Unpackages the startup parameters and calls DoStartThreadL().
@param "aAny"	"A pointer to the packaged startup parameters."
@return "One of the system-wide error codes."
@since 7.0s
*/
	static TInt StartThread(TAny* aAny);

/**
Called by the active scheduler when the ServiceL of the session leaves.
Completes the message with the error and restarts the server.
@param "aError"	"The error that the session ServiceL left with."
@return "KErrNone"
@since 7.0s
*/
	TInt RunError(TInt aError);

/**
Signals that the session has been created.
Stops the shutdown timer.
@since 7.0s
*/
	void SessionCreated();

/**
Signals that the session has been destroyed.
Causes the server to shut down immediately.
@since 7.0s
*/
	void SessionDestroyed();
private:
/**
Thread startup code.
Creates the cleanup stack, installs the active scheduler and creates the server.
Once all this is completed successfully, it signals the success back to the client.
@param	"aParams"	"Used to signal startup success back to the client."
@leave	""			"This function may leave with one of the system-wide error codes."
@since 7.0s
*/
	static void DoStartThreadL(TMMFControllerProxyStartParams* aParams);

/**
Creates a new session.  Only one session may be created with the ControllerProxyServer.
@param	"aVersion"	"The version number of the session."
@return "A pointer to the new session."
@leave	""			"This function may leave with one of the system-wide error codes."
@since 7.0s
*/
	CMmfIpcSession* NewSessionL(const TVersion& aVersion) const;

/** 
Constructor 
@since 7.0s
*/
	CMMFControllerProxyServer();

/**
Second phase constructor.
@since 7.0s
*/
	void ConstructL();
private:
/** The timer used to shut down the server in case the client fails to connect a session.*/
	CMMFControllerProxyShutdown* iShutdownTimer;
/** Indicates whether we have a session connected.  Only one session is allowed to connect to the server.*/
	TBool iHaveSession;
	};

class CMMFController;

/**
@internalComponent

The controller proxy session.

Only one session can be connected to a controller proxy server.
@since 7.0s
*/
class CMMFControllerProxySession : public CMmfIpcSession, public MAsyncEventHandler
	{
public:
/**
Construct the session.
@leave ""			"This method may leave with one of the system-wide error codes."
@return				"The newly created server."
@since				7.0s
*/
	static CMMFControllerProxySession* NewL();

/**
Second phase constructor called by the CServer base class.
@param "aServer"	"A reference to the server to which this session is attached."
@leave ""			"This function may leave with one of the system-wide error codes."
@since				7.0s
*/
	void CreateL(const CMmfIpcServer& aServer);

/**
Destructor.
*/
	~CMMFControllerProxySession();

/**
Called by the CServer baseclass when a request has been made by the client.
@param	"aMessage"	"The request to be handled.  The controller proxy session will create
					a TMMFMessage from this, and pass on the request to the controller
					base class to handle."
@leave	""			"This function may leave with on of the system-wide error codes. If
					a leave occurs, the message will be automatically completed by the 
					<code>RunError()<\code> of the Controller Proxy Server."
@since	7.0s
*/
	void ServiceL(const RMmfIpcMessage& aMessage);

/**
Derived from MAsyncEventHandler.
@see MAsyncEventHandler
@since	7.0s
*/
	TInt SendEventToClient(const TMMFEvent& aEvent);
private:
/**
Constructor
*/
	CMMFControllerProxySession();

/**
Handle a request from the client to register to receive events from the controller framework.
@param	"aMessage"	"The request to be handled."
@leave	"This function may leave with one of the system-wide error codes."
@return "ETrue if the message is to be completed now, EFalse if the message will be completed later."
*/
	TBool ReceiveEventsL(TMMFMessage& aMessage);

/**
Handle a request from the client to stop receiving events from the controller framework.
@param	"aMessage"	"The request to be handled."
@leave	"This function may leave with one of the system-wide error codes."
@return "ETrue if the message is to be completed now, EFalse if the message will be completed later."
*/
	TBool CancelReceiveEvents(TMMFMessage& aMessage);

/**
Handle a request from the client to load a controller plugin.
@param	"aMessage"	"The request to be handled."
@leave	"This function may leave with one of the system-wide error codes."
@return "ETrue if the message is to be completed now, EFalse if the message will be completed later."
*/
	TBool LoadControllerL(TMMFMessage& aMessage);
private:
	/** The controller plugin. */
	CMMFController* iController;
	/** A pointer to the server. */
	CMMFControllerProxyServer* iServer;
	/** The event receiver.  Used to send events to the client.*/
	CMMFEventReceiver* iEventReceiver;
	/** The events waiting to be sent to the client.*/
	RArray<TMMFEvent> iEvents;
	};


#endif
