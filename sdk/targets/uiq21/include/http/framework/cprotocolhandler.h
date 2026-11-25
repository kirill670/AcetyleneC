// CProtocolHandler.h
//
// Copyright (C) 2001 Symbian Ltd

/** 
	@file CProtocolHandler.h
	@public
	@warning : This file contains Rose Model ID comments 
			   please do not delete
 */ 

#ifndef __CPROTOCOLHANDLER_H__
#define __CPROTOCOLHANDLER_H__

// System includes
#include <e32base.h>
#include <http/framework/httplogger.h>
#include <http/mhttpfilter.h>
#include <http/rhttpsession.h>

// Forward declarations
class CHeaderCodec;
class CProtTransaction;
class CSecurityPolicy;

// The ECom protocol handler plugin interface UID
const TUid KUidProtocolHandlerPluginInterface = {0x1000A449};

// Defined active object priorities
const TInt KProtocolHandlerActivePriority = CActive::EPriorityStandard;
const TInt KTransactionActivePriority = KProtocolHandlerActivePriority+1;

/** 
	@public
	@class			CProtocolHandler
	@since			7.0
	An abstract protocol handler.  Protocol handlers are required to
	act as the bridge between abstract representations of sessions, transactions and
	headers (the client side of the HTTP architecture) and specific comms transports
	(the network side of the architecture).

	Each instance of a concrete subclass of CProtocolHandler is associated
	with a specific	client session, and hence with a particular choice of proxy type,
	and by implication, transport type.  It is designed to appear like a filter in
	order to be placed at the end of a session's filter queue.  This allows it to 
	receive transaction-related events in the same way that any other filter
	(or indeed, the client) does.  An active object, it may implement a queuing
	system for submitted transactions, according to the chosen internal service
	model.

	In order to divide the abstract functionality associated with handling the HTTP
	protocol handler from the specifics needed for a particular choice of transport,
	this class defines a number of pure virtual methods which allow it to defer
	transport-specific choices or mechamisms.  These are mainly concerned with the
	service model (ie. allocation of transactions to objects that can handle them), the
	codec model (ie. on-demand encoding/decoding of	HTTP header data) and general
	housekeeping (eg. instantiation and cleanup of objects at particular points in
	a transaction lifecycle).
 */

//##ModelId=3C4C186A02A3
class CProtocolHandler : public CActive, public MHTTPFilter
	{
public:	// Methods

/** @fn				NewL(const TDesC8& aProtocol, RHTTPSession aSession)
	Intended Usage:	Standard factory constructor. This is the ECOM interface class from
					which concrete protocol handlers are derived. The method queries
					ECOM for the protocol handler plugin that matches the protocol
					description passed in.
	@since			7.0
	@param			aProtocol	(in) The name of the protocol required.
	@param			aSession	(in) The HTTP session on which this protocol handler
									 will be installed.
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
*/
	//##ModelId=3C4C186B007E
	static CProtocolHandler* NewL(const TDesC8& aProtocol, RHTTPSession aSession);

/** @fn				~CProtocolHandler()
	Intended Usage:	Class destructor.
	@since			7.0
*/
	//##ModelId=3C4C186B0075
	IMPORT_C virtual ~CProtocolHandler();

/** @fn				Codec() const
	Intended Usage:	Obtain the protocol handler's header codec.
	@since			7.0
	@return			The header codec owned by this protocol handler, or NULL if one
					has not yet been created.
	@see CHeaderCodec
*/
	//##ModelId=3C4C186B0074
	IMPORT_C CHeaderCodec* Codec() const;

public:	// Methods to be implemented in specific protocol handlers
	/** Get the Server Certificate for the current session.
	@param	aServerCert A TCertInfo which will be filled with the certificate information
	@return	An error code.  KErrNone if aServerCert has been completed, otherwise one of 
			the system wide error codes
	*/
	virtual TInt SessionServerCert(TCertInfo& aServerCert) = 0;

	/** Get the Server Certificate for the specified transaction.
	@param	aServerCert A TCertInfo which will be filled with the certificate information
	@param	aTransaction The transaction for which the certificate is requested
	@return	An error code.  KErrNone if aServerCert has been completed, otherwise one of 
			the system wide error codes
	*/
	virtual TInt TransactionServerCert(TCertInfo& aServerCert, RHTTPTransaction aTransaction) = 0;

public:	// Methods from MHTTPFilterBase
	
/**	@fn				MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent& aEvent)
	@since			7.0
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
	@see			MHTTPFilterBase
 */
	//##ModelId=3C4C186B0061
	IMPORT_C virtual void MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent& aEvent);

/**	@fn				MHFSessionRunL(const THTTPSessionEvent& aEvent)
	@since			7.0
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
	@see			MHTTPFilterBase
 */
	//##ModelId=3C4C186B0057
	IMPORT_C virtual void MHFSessionRunL(const THTTPSessionEvent& aEvent);

/**	@fn				MHFRunError(TInt aError, RHTTPTransaction aTransaction, const THTTPEvent& aEvent)
	@since			7.0
	@see			MHTTPFilterBase
 */
	//##ModelId=3C4C186B0043
	IMPORT_C virtual TInt MHFRunError(TInt aError, RHTTPTransaction aTransaction, const THTTPEvent& aEvent);

/**	@fn				MHFSessionRunError(TInt aError, const THTTPSessionEvent& aEvent)
	@since			7.0
	@see			MHTTPFilterBase
 */
	//##ModelId=3C4C186B0038
	IMPORT_C virtual TInt MHFSessionRunError(TInt aError, const THTTPSessionEvent& aEvent);

public:	// Methods from MHTTPFilter

/**	@fn				MHFUnload(RHTTPSession aSession, THTTPFilterHandle aHandle)
	@since			7.0
	@see			MHTTFilter
 */
	//##ModelId=3C4C186B0025
	IMPORT_C virtual void MHFUnload(RHTTPSession aSession, THTTPFilterHandle aHandle);

/**	@fn				MHFLoad(RHTTPSession aSession, THTTPFilterHandle aHandle)
	@since			7.0
	@see			MHTTFilter
 */
	//##ModelId=3C4C186B001A
	IMPORT_C virtual void MHFLoad(RHTTPSession aSession, THTTPFilterHandle aHandle);

protected: // callbacks/methods for sub-classes

/**	@fn				TransactionCompletedL(RHTTPTransaction aTrans, THTTPEvent aEventStatus)
	Intended usage:	Callback method for concrete protocol handler sub-classes to
					inform the base protocol handler that a transaction has completed.
					The concrete protocol handler must call this method in order to
					supply a completion event that will be sent to the client.
					In addition, the method allows the base protocol handler to do some
					queue management.
	@since			7.0
	@param			aTrans			(in) the completed transaction
	@param			aEventStatus	(in) an event to be sent back to the client along
										 the filter queue
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
 */
	//##ModelId=3C4C186B0010
	IMPORT_C void TransactionCompletedL(RHTTPTransaction aTrans, THTTPEvent aEventStatus);

/**	@fn				NumActiveTransactions() const
	Intended usage:	Obtain the number of currently active transactions
	@since			7.0
	@return			The number of currently active transactions
 */
	//##ModelId=3C4C186B0006
	IMPORT_C TInt NumActiveTransactions() const;

/**	@fn				TransactionFailed(RHTTPTransaction aTrans)
	Intended usage:	Callback method for concrete protocol handler sub-classes to
					inform the base protocol handler that a transaction has failed
					utterly. (i.e. the sub-class used aTrans.Fail().) The base protocol
					handler sets the transaction state to be cancelled.
	@since			7.0
	@param			aTrans			(in) the completed transaction
 */
	//##ModelId=3C4C186A03E5
	IMPORT_C void TransactionFailed(RHTTPTransaction aTrans);

/**	@fn				CompleteSelf()
	Intended usage:	Completes this active object - allows the protocol handler to
					reevaluate the queue of pending transactions and service new ones
					if possible.
	@since			7.0
 */
	//##ModelId=3C4C186A03E4
	IMPORT_C void CompleteSelf();

/**	@fn				FindTransaction(RHTTPTransaction aTransaction, CProtTransaction*& aProtTransaction) const
	Intended Usage:	Searches the array of CProtTransaction objects to if the
					aTransaction object is wrapped by one of them. If one is found aProtTransaction is set to it
	@since			7.0
	@param			aTransaction	The transaction to search for.
	@param			aProtTransaction	Reference to a CProtTransaction which will be set to the
					CProtTransaction which wraps the RHTTPTransaction.
	@return			If a CProtTransaction object is found, a positive value is
					returned that is the index to that object in the array. If 
					no object is found, KErrNotFound is returned.
 */
	IMPORT_C TInt FindTransaction(RHTTPTransaction aTransaction, const CProtTransaction*& aProtTransaction) const;

private: // methods to be implemented in specific protocol handlers

/**	@fn				CompleteSelf()
	Intended usage:	Creates the specific type of codec required for a specific type
					of protocol handler.
					
					This must be implemented by a concrete protocol handler sub-class.
	@since			7.0
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
 */
	//##ModelId=3C4C186A03DC
	virtual void CreateCodecL() = 0;

/**	@fn				CreateProtTransactionL(RHTTPTransaction aTransaction) = 0
	Intended Usage:	Creates a representation of a client transaction to be used in the
					protocol handler.  Since the protocol handler deals with the low-
					level data for a transaction as sent over a particular transport,
					an appropriate CProtTransaction-derived class is used that owns a
					CRxData and a CTxData to handle the low-level data.
					
					This must be implemented by a concrete protocol handler sub-class.
	@since			7.0
	@leave			Leave code KErrNoMemory if there was not enough memory to 
					create the object.
	@param			aTransaction	The RHTTPTransaction object associated with
									this CProtTransaction object.
	@return			A pointer to a created CProtTransaction-derived class.
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
	@see			CRxData
	@see			CTxData
 */
	//##ModelId=3C4C186A03DA
	virtual CProtTransaction* CreateProtTransactionL(RHTTPTransaction aTransaction) = 0;

/**	@fn				ServiceL(CProtTransaction& aTrans) = 0
	Intended Usage:	Attempt to service the transaction.  This implies that the concrete
					protocol handler will allocate some transport resources to the
					transaction - which could fail if the protocol handler has hit an
					internal limit of resources or bandwidth.
					
					This must be implemented by a concrete protocol handler sub-class.
	@since			7.0
	@param			aTrans	The pending protocol transaction object which is to be
							serviced.
	@return			A flag that indicates if the transaction can be serviced immediately.
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
 */
	//##ModelId=3C4C186A03D0
	virtual TBool ServiceL(CProtTransaction& aTrans) = 0;

/**	@fn				ClosedTransactionHook(CProtTransaction* aTrans) = 0
	Intended Usage:	Called when the RHTTPTransaction object corresponding to aTrans has
					been closed by the client. This allows the concrete protocol handler
					to do any cleanup required for this particular transaction.

					Ownership of the CProtTransaction object is transferred back to the
					concrete protocol handler, which then has deletion responsibility
					for it.  By the time this function has been called, the base
					protocol handler will have dequeued the transaction.
					
					The client's RHTTPTransaction will be closed when this function
					returns,  so it is not possible to send events to the client during
					the function's execution.
					
					This must be implemented by a concrete protocol handler sub-class.
	@since			7.0
	@param			aTrans		(in) A pointer to the transaction about to be closed.
 */
	//##ModelId=3C4C186A03C6
	virtual void ClosedTransactionHook(CProtTransaction* aTrans) = 0;

/**	@fn				CancelTransactionHook(CProtTransaction& aTrans) = 0
	Intended Usage:	Called when the RHTTPTransaction object corresponding to aTrans has
					been cancelled by the client or an intermediate filter. This allows
					the concrete protocol handler to do any cleanup and to perform the
					necessary actions for cancellation on its transport layer.
					
					This must be implemented by a concrete protocol handler sub-class.
	@since			7.0
	@param			aTrans		(in) A reference to the transaction being cancelled.
 */
	//##ModelId=3C4C186A03B3
	virtual void CancelTransactionHook(CProtTransaction& aTransaction) = 0;

/**	@fn				NotifyNewRequestBodyPart(CProtTransaction& aTransaction) = 0
	Intended Usage:	Called to notify the concrete protocol handler that new request
					body data is available for transmission.
					
					This must be implemented by a concrete protocol handler sub-class.
	@since			7.0
	@param			aTrans		(in) A reference to the transaction whose request body
									 has new data available.
 */
	//##ModelId=3C4C186A03A8
	virtual void NotifyNewRequestBodyPart(CProtTransaction& aTransaction) = 0;

protected: // Methods inherited from CActive

/**	@fn				RunL()
	Intended Usage:	Do some processing when a previous asynchronous request made by
					this object has completed.
	@since			7.0
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
 */
	//##ModelId=3C4C186A0377
	IMPORT_C virtual void RunL();

/**	@fn				RunError(TInt aError)
	Intended Usage:	Do any cleanup required should RunL leave
	@since			7.0
	@param			aError		(in) The error code that RunL left with
	@return			A final error code - KErrNone if the error was handled by this
					method.
 */
	//##ModelId=3C4C186A036E
	IMPORT_C virtual TInt RunError(TInt aError);

/**	@fn				DoCancel()
	Intended Usage:	Cancel outstanding asynchronous requests that this object has made
	@since			7.0
 */
	//##ModelId=3C4C186A036D
	IMPORT_C virtual void DoCancel();

protected:	// Methods

/**	@fn				CProtocolHandler(RHTTPSession aSession)
	Intended Usage:	Constructs a protocol handler associated with the supplied HTTP
					client session.
	@since			7.0
	@param			aSession	(in) The session on which the new protocol handler will
									 be installed.
 */
	IMPORT_C CProtocolHandler(RHTTPSession aSession);

/**	@fn				ConstructL(RHTTPSession aSession)
	Intended Usage:	Second phase construction in which any necessary allocation is done
	@since			7.0
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
	@param			RHTTPSession aSession.
 */
	//##ModelId=3C4C186A036C
	IMPORT_C void ConstructL(RHTTPSession aSession);

protected: // Attributes

	/** The session to which this protocol handler is dedicated
	*/
	//##ModelId=3C4C186A033C
	RHTTPSession iSession;

	/** The codec used for this protocol handler (to be specialised in subclasses)
	*/
	//##ModelId=3C4C186A032F
	CHeaderCodec* iCodec;

	/** HTTP logger handle (debug only)
	*/
	__DECLARE_LOG

	/** An interface providing the security policy. This may be NULL if there is no security policy plugin */
	//##ModelId=3C4C186A031D
	CSecurityPolicy* iSecurityPolicy;	

private: // Methods

/**	@fn				SubmitTransactionL(RHTTPTransaction aTransaction)
	Intended Usage:	Called after a client RHTTPTransaction::SubmitL(), this method
					enqueues the supplied client transaction.  It checks to see if there
					already exists a CProtTransaction for this transaction. If there is
					and its state is ECancelled, then the associated request data is
					reset and the state changed to EPending. A CompleteSelf() is issued.
					In the case of an existing CProtTransaction that has not been
					cancelled, the submit event is ignored. If no CProtTransaction
					object existed, then one is created for the transaction and a
					CompleteSelf() is issued.
	@since			7.0	
	@leave			KErrHttpCantResetRequestBody if the request body data cannot
					be reset. KErrNoMemory if a new CProtTransaction cannot be
					created or added to the transaction queue.
	@param			aTransaction	The submitted transaction.
	@pre 			None
	@post			If there is a new pending CProtTransaction object the protocol
					handler will have been self-completed (i.e. the RunL will be 
					called).
 */
	//##ModelId=3C4C186A0362
	void SubmitTransactionL(RHTTPTransaction aTransaction);

/**	@fn				HandleCancelTransaction(RHTTPTransaction aTrans)
	Intended Usage:	Sets the state of the CProtTransaction object for this 
					transaction to ECancelled, and resets the object. This
					object can be reused if the transaction is resubmitted.
	@since			7.0
	@param			RHTTPTransaction aTrans
	@pre 			A CProtTransaction object exists for this transaction.
	@post			The state of the CProtTransaction object is set to ECancelled 
					and it has been reset.
 */
	//##ModelId=3C4C186A0359
	void HandleCancelTransaction(RHTTPTransaction aTrans);

/**	@fn				HandleClosedTransaction(RHTTPTransaction aTrans)
	Intended Usage:	Removes the CProtTransaction object for the transaction
					from the queue of CProtTransaction objects.
	@since			7.0
	@param			RHTTPTransaction aTrans
	@pre 			A CProtTransaction object exists for this transaction.
	@post			The CProtTransaction object has been removed from the queue.
 */
	//##ModelId=3C4C186A034F
	void HandleClosedTransaction(RHTTPTransaction aTrans);

/**	@fn				FindTransaction(RHTTPTransaction aTransaction) const
	Intended Usage:	Searches the array of CProtTransaction objects to if the
					aTransaction object is wrapped by one of them.
	@since			7.0
	@param			aTransaction	The transaction to search for.
	@return			If a CProtTransaction object is found, a positive value is
					returned that is the index to that object in the array. If 
					no object is found, KErrNotFound is returned.
 */
	//##ModelId=3C4C186A0346
	TInt FindTransaction(RHTTPTransaction aTransaction) const;

/**	@fn				Reserved1()
	Intended Usage:	Reserve a slot in the v-table to preserve future BC
	@since			7.0
 */
	//##ModelId=3C4C186A0345
	inline virtual void Reserved1();

/**	@fn				Reserved2()
	Intended Usage:	Reserve a slot in the v-table to preserve future BC
	@since			7.0
 */
	//##ModelId=3C4C186A0344
	inline virtual void Reserved2();

private: // Attributes

	/** A list of transactions. Each transaction has a list state, e.g. pending,
		active, etc.
	*/
	//##ModelId=3C4C186A0313
	RPointerArray<CProtTransaction>		iTransactions;

	/**	The transaction which is currently being serviced - used in RunError so 
		we know which transaction caused RunL to leave.
	*/
	//##ModelId=3C4C186A02FF
	RHTTPTransaction					iCurrentTransaction;

	/** The destructor key UID indentification required by ECom
	*/
	//##ModelId=3C4C186A02F5
	TUid iDtor_ID_Key;
	};



inline void CProtocolHandler::Reserved1()
	{}
inline void CProtocolHandler::Reserved2()
	{}

#endif // __CPROTOCOLHANDLER_H__

