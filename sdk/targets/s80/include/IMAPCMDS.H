// IMAPCMDS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined (__IMAPCMDS_H__)
#define __IMAPCMDS_H__

#if !defined (__MSVSTD_HRH__)
#include <msvstd.hrh>
#endif

class TImap4RenameFolder
/** Buffer for an IMAP folder name. 
@publishedAll
@released
*/
	{
public:
	/** IMAP folder name. */
	TBuf<128> iNewName;
	};

/** IMAP4-specific commands that can be issued through CImap4ClientMtm::InvokeAsyncFunctionL(). 
@publishedAll
@released
*/
enum TImap4Cmds {
	/** Tests if the service is connected.
	
	Completes with either KErrNone if connected or KErrDisconnected if not. */
	KIMAP4MTMIsConnected = KMtmFirstFreeMtmFunctionId,
	/** Connects to the internet, and then connects to the IMAP service whose TMsvId 
	is given in aSelection[0]. */
	KIMAP4MTMConnect,
	/** As KIMAP4MTMConnect, but, after connection to the IMAP service, starts a background 
	synchronisation.
	
	The call completes when the connection occurs and the synchronisation starts. */
	KIMAP4MTMConnectAndSynchronise,
	/** If there is a background synchronisation in progress, then stops it and completes 
	with KErrCancel; otherwise, completes with KErrNone. */
	KIMAP4MTMCancelBackgroundSynchronise,
	/** Ensures that the IMAP server will remain loaded ready for more commands. */
	KIMAP4MTMStartBatch,
	/** Ends the effect of KIMAP4MTMStartBatch. */
	KIMAP4MTMEndBatch,
	/** Tests if the server is busy.
	
	This completes with either KErrNone (neither session is busy) or KErrServerBusy 
	otherwise. */
	KIMAP4MTMBusy,
	/** Sets the server MTM context to the folder whose TMsvId is given by aSelection[0]. */
	KIMAP4MTMSelect,
	/** Synchronises the current folder that is selected on the remote server. */
	KIMAP4MTMSynchronise,
	/** Not supported. */
	KIMAP4MTMSyncTree,
	/** Not supported. */
	KIMAP4MTMReserved10,						// SyncSubscription
	/** Synchronises the service whose TMsvId is given by aSelection[0]. 
	
	If the service is already synchronising, then complete with KErrServerBusy. */
	KIMAP4MTMFullSync,
	/** Cancels any operations in progress and sends logout messages to server. 
	
	As long as the background synchronisation, this will also run any pending 
	delete operations queued while offline. */
	KIMAP4MTMDisconnect,
	/** Sets the local subscription flag on the folder specified by the TMsvId given 
	by aSelection[0]. */
    KIMAP4MTMLocalSubscribe,
	/** Clears the local subscription flag on the folder specified by the TMsvId given 
	by aSelection[0]. */
    KIMAP4MTMLocalUnsubscribe,
	/** Not supported. */
	KIMAP4MTMReserved15,						// MakeRemoteMailboxesInvisible
	/** Not supported. */
	KIMAP4MTMReserved16,						// MakeRemoteMailboxesVisible
	/** Selects the remote inbox and checks for new mails (but doesn't delete ones 
	that have gone). */
	KIMAP4MTMInboxNewSync,
	/** Selects and synchronises the folder specified by the TMsvId given by aSelection[0]. */
	KIMAP4MTMFolderFullSync,
	/** Completes (with KErrNone) only when the background synchronisation has finished. 
	
	
	It is used to ensure that no UI-initiated folder syncing is performed during 
	the background synchronisation. */
	KIMAP4MTMWaitForBackground,
	/** Renames the folder identified by aSelection[0]. 
	
	The new name of the folder is passed as the aParameter value. */
	KIMAP4MTMRenameFolder,
	/** Undeletes all of the items in aSelection (if they were deleted). */
	KIMAP4MTMUndeleteAll,
	/** Cancels any offline operations pending on each of the items in aSelection. 
	
	If any item is a folder, then it cancels all operations queued on any item 
	in that folder. If an IMAP4 service ID is given, then it cancels any Copy() 
	or MoveFromLocal() operations that are queued. A message can not have its 
	pending operations queued individually. */
	KIMAP4MTMCancelOffLineOperations,
	/** Populates all of the items in aSelection. */
	KIMAP4MTMPopulate,
	/** Synchronises local folder subscription flags with remote folder subscription 
	flags using defined subscription rules. */
	KIMAP4MTMSyncSubscription,
	/** Connect and synchronise mailbox after connection has occurred. */
	KIMAP4MTMConnectAndSyncCompleteAfterConnect,
	/** Connect and synchronise mailbox after a full synchronisation. */
	KIMAP4MTMConnectAndSyncCompleteAfterFullSync,
	/** Connect and synchronise mailbox after disconnection. */
	KIMAP4MTMConnectAndSyncCompleteAfterDisconnect,
	/** Not supported. */
	KIMAP4MTMCancelSendOnNextConnection,
	
	// need to pass in destination in aParameter
	/** Copy any new messages from the current service, assuming a new connection does 
	not need to be made. */
	KIMAP4MTMCopyNewMailWhenAlreadyConnected,
	/** Copy any new messages from the current service, and do not disconnect afterwards. */
	KIMAP4MTMConnectAndCopyNewMailAndStayOnline,
	/** Copy any new messages from the current service, and disconnect afterwards. */
	KIMAP4MTMConnectAndCopyNewMailAndDisconnect,
	/** Move any new messages from the current service, assuming a new connection does 
	not need to be made. */
	KIMAP4MTMMoveNewMailWhenAlreadyConnected,
	/** Move any new messages from the current service, and do not disconnect afterwards. */
	KIMAP4MTMConnectAndMoveNewMailAndStayOnline,
	/** Connect to current service, move any new messages, and disconnect afterwards. */
	KIMAP4MTMConnectAndMoveNewMailAndDisconnect,

	// need to pass in destination in aParameter
	/** Copy the specified messages from the current service, assuming a new connection 
	does not need to be made. */
	KIMAP4MTMCopyMailSelectionWhenAlreadyConnected,
	/** Connect to current service, copy the specified messages, and do not disconnect 
	afterwards. */
	KIMAP4MTMConnectAndCopyMailSelectionAndStayOnline,
	/** Connect to current service, copy the specified messages, and disconnect afterwards. */
	KIMAP4MTMConnectAndCopyMailSelectionAndDisconnect,
	/** Move the specified messages from the current service, assuming a new connection 
	does not need to be made. */
	KIMAP4MTMMoveMailSelectionWhenAlreadyConnected,
	/** Connect to current service, move the specified messages, and do not disconnect 
	afterwards. */
	KIMAP4MTMConnectAndMoveMailSelectionAndStayOnline,
	/** Connect to current service, move the specified messages, and disconnect afterwards. */
	KIMAP4MTMConnectAndMoveMailSelectionAndDisconnect,

	// need to pass in destination in aParameter
	/** Copy all messages from the current service, assuming a new connection does 
	not need to be made. */
	KIMAP4MTMCopyAllMailWhenAlreadyConnected,
	/** Connect to current service, copy all messages, and do not disconnect afterwards. */
	KIMAP4MTMConnectAndCopyAllMailAndStayOnline,
	/** Connect to current service, copy all messages, and disconnect afterwards. */
	KIMAP4MTMConnectAndCopyAllMailAndDisconnect,
	/** Move all messages from the current service, assuming a new connection does 
	not need to be made. */
	KIMAP4MTMMoveAllMailWhenAlreadyConnected,
	/** Connect to current service, move all messages, and do not disconnect afterwards. */
	KIMAP4MTMConnectAndMoveAllMailAndStayOnline,
	/** Connect to current service, move all messages, and disconnect afterwards. */
	KIMAP4MTMConnectAndMoveAllMailAndDisconnect,

	/** Populate the specified messages from the current service, assuming a new connection 
	does not need to be made. */
	KIMAP4MTMPopulateMailSelectionWhenAlreadyConnected,
	/** Connect and populate the specified messages. */
	KIMAP4MTMConnectAndPopulateMailSelectionAndStayOnline,
	/** Connect and populate the specified messages, then disconnect. */
	KIMAP4MTMConnectAndPopulateMailSelectionAndDisconnect,
	/** Populate new messages from the current service, assuming a new connection does 
	not need to be made. */
	KIMAP4MTMPopulateNewMailWhenAlreadyConnected,
	/** Populate all messages from the current service, assuming a new connection does 
	not need to be made. */
	KIMAP4MTMPopulateAllMailWhenAlreadyConnected,
	/** Connect and populate new messages from the current service. */
	KIMAP4MTMConnectAndPopulateNewMailAndStayOnline,
	/** Connect and populate new messages from the current service, then disconnect. */
	KIMAP4MTMConnectAndPopulateNewMailAndDisconnect,
	/** Connect and populate all messages from the current service. */
	KIMAP4MTMConnectAndPopulateAllMailAndStayOnline,
	/** Connect and populate all messages from the current service, then disconnect. */
	KIMAP4MTMConnectAndPopulateAllMailAndDisconnect,
	/** Creates a new message. */
	KIMAP4MTMCreateNewEmailMessage,
	/** Creates a new reply message. */
	KIMAP4MTMCreateReplyEmailMessage,
	/** Creates a new forwarded message. */
	KIMAP4MTMCreateForwardEmailMessage,
	/** Creates a new forwarded message. */
	KIMAP4MTMCreateForwardAsAttachmentEmailMessage,
	/** Creates a new message-receipt message. */
	KIMAP4MTMCreateReceiptEmailMessage
};

#endif
