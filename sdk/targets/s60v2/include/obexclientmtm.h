// OBEXCLIENTMTM.H
//
// Copyright (c) 2001-2004 Symbian Sofwtare Ltd.  All rights reserved.
//

#ifndef __OBEXCLIENTMTM_H__
#define __OBEXCLIENTMTM_H__

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif     // __REMOVE_MESSAGING_API_V1__

#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif     // __SUPPORT_MESSAGING_API_V1__

#include <mtclbase.h> //CBaseMtm

// temporary forward declaration for now...
class CObexHeaderList;

class CMsvEntry;
class CMtmDllRegistry;
class CRichText;
class TMsvEntry;
class CRegisteredMtmDll;
class CMsvSession;
class CObexMtmHeader;
#ifndef __HIDE_MESSAGING_API_V1__
class CObexMtmFileNameExternaliser;
#endif // __HIDE_MESSAGING_API_V1__

extern const TInt KMaxObexPasswordLength;



class TObexMtmProgress
/**
Used to determine the progress for the current obex send operation.

@publishedPartner
@released
*/
	{
public:

	///The current state the send operation is in
	enum TSendState
		{
		ENullOp = 0, ///< Undefined state
		EInitialise, ///< Initialise Obex client object
		EConnect, ///< Trying to connect
		EConnectAttemptComplete, ///< Connection complete
		ESendObject, ///< Send Obex object
		ESendNextObject, ///< Send next Obex object
		ESendComplete, ///< Send complete
		EDisconnected, ///< Disconnected
		EUserCancelled,  ///< User has cancelled the send, the current operation is unimportant
		ESendError, ///< Problem with the send
		EInitialised, ///< Initialisation complete
		EMovedToSent ///< Move sent message to outbox (not supported from v7.0s)
		};
	TSendState iSendState; ///< Current state of send operation
	TInt iTotalEntryCount; ///< Total number of objects to send
	TInt iEntriesDone; 		///< Number of entries sent
	TInt iCurrentEntrySize; ///< Length attribute of the current object (bytes)
	TInt iCurrentBytesTrans;///< Number of bytes sent of the current object
	TInt iError;			///< Operation error code
	};



class CObexClientMtm : public CBaseMtm
/**
CObexClientMtm 

Abstract base class for Client Mtms that send obex objects

The functionality missing is an implementation of InvokeAsyncFunctionL()
which should return a messaging operation for a specific transport, InitialiseHeaderL() which is used
to create a CObexMtmHeader derived object of the appropriate type, and TestInvariant() which is used to
perform invariant testing of the derived types (in debug only).
These pure-virtual functions are the transport specific aspects of the MTM.

@internalTechnology
@released
*/
	{
public:
#ifndef __HIDE_MESSAGING_API_V1__
	enum TSyncCmds
		{
		/**
		 * Used by InvokeSyncFunction() for filename externalisation (if filenames are being stored in
		 * the message store, as opposed to storing as attachments). Rollback will be performed if
		 * ESendasCmdCommitExternalise is *not* called prior to a subsequent call with ESendasCmdStartExternalise
		 */
		ESendasCmdStartExternalise,			//<Begin externalising filenames to the message store
		ESendasCmdExternaliseFileName,		//<Add a name to the message store
		ESendasCmdCommitExternalise,		//<Commit all names to the message store
		};
#endif // __HIDE_MESSAGING_API_V1__

	/// Contains the connect the timeout values for connect and put operations
	struct STimeouts
		{
		TInt iConnectTimeout;
		TInt iPutTimeout;
		};

	//CBaseMtm Implementation
	
	/**
	 * Commits cached changes to the message store, by calling CommitChangesL. 
	 *
	 * @leave KErrXxx System-wide error codes if message cannot be saved.
	 */
	
	IMPORT_C virtual void SaveMessageL();
	
	/**
	 * This function loads the header from the message store
	 *
	 * @leave KErrXXX system-wide error codes
	 */
	
	IMPORT_C virtual void LoadMessageL();

	/**
	 * Ensure that the current message context part indicated is valid. Currently only works on KMsvMessagePartRecipient--all other parts
	 * are assumed to be valid
	 *
	 * @param aPartList Bitmask indicating parts of message to be validated
	 * @return Bitmask of any invalid parts--KErrNone otherwise
	 */
	
	IMPORT_C virtual TUint ValidateMessage(TMsvPartList aPartList);
	
	/**
  	 * Finds the given text within the specified parts of the current message context. NOT IMPLEMENTED!
	 * 
	 * @param aTextToFind Reference to the text to search for in the specified message parts
	 * @param aPartList Bitmask indicating parts of message to be searched for the text
	 * @return Bitmask of any parts containing the message text
	 */
	
	IMPORT_C virtual TMsvPartList Find(const TDesC& aTextToFind, TMsvPartList aPartList);
	
	/**
	 * Unsupported
	 *
	 * @leave Leaves always with KErrNotSupported
	 */
	
	IMPORT_C virtual CMsvOperation* ReplyL  (TMsvId aReplyEntryId, TMsvPartList aPartlist, TRequestStatus& aCompletionStatus);
	
	/**
	 * Unsupported
	 *
	 *  @leave Leaves always with KErrNotSupported
	 */
		
	IMPORT_C virtual CMsvOperation* ForwardL(TMsvId aForwardEntryId, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);
	// addresssee list (used by objects with no MTM knowledge)
	
	/**
	 * Adds addressee to the addressee "list". Note that this MUST be a TDesC containing binary data representing
	 * the TSockAddress of the addressee, usually as a TDesC16. This function will then package the data directly into 
	 * 8 bit data.
 	 * NB: Only ONE addressee is supported
	 *
	 * @param aRealAddress Reference to the address of the recipient
 	 * @leave KErrXXX if address cannot be appended
	 * @leave KErrAlreadyExists if the Addressee "list" already contains an entry
	 */

	IMPORT_C virtual void AddAddresseeL(const TDesC& aRealAddress);
	
	/**
	 * Adds addressee to the addressee "list". Note that this MUST be a TDesC containing binary data representing
	 * the TSockAddress of the addressee, usually as a TDesC16. This function will then package the data directly into 
	 * 8 bit data.
	 * NB: Only ONE addressee is supported
	 *
	 * @param aRealAddress Reference to the address of the recipient
	 * @param aAlias Reference to the alias of the recipient--ignored in this implementation
	 * @leave KErrXXX if address cannot be appended
	 * @leave KErrAlreadyExists if the Addressee "list" already contains an entry
	 */

	IMPORT_C virtual void AddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias);
	
	/**
	 * Removes addressee at index aIndex from the addressee "list".
	 *
	 * @param aIndex zero-based index of the addressee (ignored since "there can be only one").
	 */

	IMPORT_C virtual void RemoveAddressee(TInt aIndex);
	
	/**
	 * Sets the subject of the current message context
	 *
	 * @param aSubject Reference to the new message subject text
	 * @leave Leaves if creation of new HBufC fails
	 */	
	
	IMPORT_C void SetSubjectL(const TDesC& aSubject);

	/**
	 * Returns the subject of the current message context. Will not leave.
	 *
	 * @return const TPtrC representation of the Subject, or an empty TPtrC if the subject hasn't been set
	 * @leave Never
	 */
	
	IMPORT_C const TPtrC SubjectL() const;
	
#ifdef __MESSAGING_API_V2__
	IMPORT_C void CreateMessageAttachmentL(TMsvId aAttachmentId); 
#endif // __MESSAGING_API_V2__

#ifndef __HIDE_MESSAGING_API_V1__
	/**
	 * Begins externalising filenames to the message store.
	 * Used to implement the ESendasCmdStartExternalise command.
	 * Can now be called directly so that client code using the new CObexHeaderList
	 * has a consistent API for interacting with the MTM.
	 *
	 * @param aSelection Selection of message entries for the requested function to operate on.
	 * @leave Leaves if no memory is available.
	 */

	IMPORT_C void StartFileNameExternaliseL(const CMsvEntrySelection& aSelection);

	/**
	 * Add a name to the message store.
	 * Used to implement the ESendasCmdExternaliseFileName command.
	 * Can now be called directly so that client code using the new CObexHeaderList
	 * has a consistent API for interacting with the MTM.  Note that the filename can be
	 * presented in it's native Unicode form - it no longer needs to be encapsulated in an
	 * 8-bit descriptor to get it past the synchronous MTM API.
	 *
	 * @param aFilename filename to place in the message store. The file is not opened until it is sent.
	 * @leave Leaves if no memory is available.
	 */
	
	IMPORT_C void ExternaliseFileNameL(const TDesC& aFilename);
	
	/**
	 * Add a name and a set of headers to the message store.
	 * This allows the Obex MTM client to add additional application specific headers to the
	 * individual parts of an outgoing message.  This can be used to implement some of the additional
	 * services which use obex as an underlying transport.
 	 * 
	 * @param aFilename filename to place in the message store. The file is not opened until it is sent.
	 * @param aHeaderList list of headers to place in the message store.
	 * @leave Leaves if no memory is available.
	 */

	IMPORT_C void ExternaliseFileNameAndHeadersL(const TDesC& aFilename, const CObexHeaderList& aHeaderList);
	
	/**
	 * Commit all names (and header lists, if present) to the message store.
	 * Used to implement the ESendasCmdCommitExternalise command.
	 * Can now be called directly so that client code using the new CObexHeaderList
	 * has a consistent API for interacting with the MTM.
	 *
	 * @leave Leaves if no memory is available.
	 */

	IMPORT_C void CommitFileNameExternaliseL();
#endif // __HIDE_MESSAGING_API_V1__
	
	// --- RTTI functions ---

	/**
	 * Gives the capability of the MTM. 
	 *
	 * @param aCapability capability to be queried
	 * @retval aResponse capability dependent return value.
	 * @return KErrNone if the capability is supported, or KErrNotSupported if not.
	 */

	IMPORT_C virtual TInt QueryCapability(TUid aCapability, TInt& aResponse);

#ifndef __HIDE_MESSAGING_API_V1__	
	/**
	 * Starts a synchronous function, and returns once it's complete
	 *
	 * @param aFunctionId Identifier of the function to be invoked.
	 * @param aSelection Selection of message entries for the requested function to operate on.
	 * @param aParameter Buffer containing input and output parameters.
	 * @leave Leaves if no memory is available, or if the specified aFunctionId is unsupported.
	 */
#endif // __HIDE_MESSAGING_API_V1__
	IMPORT_C virtual void InvokeSyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter);
	
	/**
	 * Create a new message for this MTM. This creates a new messaging entry, then
	 * re-initialises the MTM's CObexMtmHeader object.
	 *
	 * @param aServiceId The ID of the service for which the message is to be created
	 * @leave KErrXxx Standard EPOC error codes if construction of new objects fails
	 */

	IMPORT_C virtual void CreateMessageL(TMsvId /*aServiceId*/);
	
	/**
	 * Destructor deletes FileNameExternaliser and Header
	 */

	IMPORT_C ~CObexClientMtm();

	/**
	 * Commits cached changes to the message store. 
	 *
	 * @leave KErrXxx System-wide error codes if changes cannot be committed.
	 */

	IMPORT_C void CommitChangesL();
	
	/**
	 * This function calculates the size of all attachments to the message by either:
	 *
	 *  @li summing the sizes of each of the children or;
	 *  @li reading in all of the filenames from the store, and summing their sizes.*
	 *
	 *  @return total size of the attachments.
	 *  @leave KErrXXX system-wide error codes
	 */
	
	IMPORT_C TInt32 GetAttachmentSizeL();

#ifndef __HIDE_MESSAGING_API_V1__
	//Password accessor functions

	/**
	 * Sets the password associated with the current entry's service entry.
	 *
	 * @param aPassword password to be set
	 * @leave KErrXXX system-wide error codes
	 */

	IMPORT_C void SetPasswordL(const TDesC& aPassword);

	/**
	 * Gets the password associated with the current entry's service entry.
	 *
	 * @leave KErrXXX system wide error codes
	 */
	
	IMPORT_C HBufC* GetPasswordLC();
#endif //__HIDE_MESSAGING_API_V1__

protected:
	
	/**
	 * Constructor. Initialises iMsgTypeUid with Uid provided by the derived class.
	 *
	 * @param aRegisteredMtmDll Registration data for MTM DLL.
	 * @param aMsvSession CMsvSession of the client requesting the object.
	 * @param aMsgTypeUid Uid of the message
	 */

	IMPORT_C CObexClientMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession, TUid aMsgTypeUid);
	
	/**
	 * Empty implementation provided for future-proofing.
	 */
	
	IMPORT_C void ConstructL();
	
	
	/// Initialises header information (must be overidden in derived class)
	virtual void InitialiseHeaderL() = 0;
	
	/**
	 * Resets the MTM when the context is switched.
	 * Must be called by the derived class's ContextEntrySwitched prior to constructing a new header.
	 */

	IMPORT_C void ContextEntrySwitched(); // called after the context of this instance has been changed to another entry

protected:
	CObexMtmHeader* iHeader;	///<Header information that must be initialised by InitialiseHeaderL in the derived classes!

private:
#ifndef __REMOVE_MESSAGING_API_V1__
#ifndef __HIDE_MESSAGING_API_V1__
	CObexMtmFileNameExternaliser* iObexMtmFileNameExternaliser;	///<Filename externaliser used for reading and writing filenames to and from the message store
#else
	TUint8   iFiller[sizeof(CBase*)];
#endif	// __HIDE_MESSAGING_API_V1__
#endif	// __REMOVE_MESSAGING_API_V1__
	const TUid iMsgTypeUid;	///<Message type UID, set by the derived class's constructor as appropriate for each derived MTM
	};

//Custom invariant test macro--allows TestInvariant() function to be virtual

#ifdef _DEBUG
#define __TEST_INVARIANT_VIRTUAL TestInvariant();
#else
#define __TEST_INVARIANT_VIRTUAL
#endif //__DEBUG__

#endif // __OBEXCLIENTMTM_H__
