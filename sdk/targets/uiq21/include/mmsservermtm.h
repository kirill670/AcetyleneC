// MmsServerMtm.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
// 

#ifndef	__MMSSERVERMTM_H__
#define	__MMSSERVERMTM_H__


#include <e32base.h>
#include <msvstd.h>
#include <msventry.h>
#include <mtsr.h>
#include <mmsutils.h>
#include <agentclient.h>

class CMmsOperation;
class CMmsBackgroundOperationList;
class CMmsConnectionManager;

class CMmsServerMtm : public CBaseServerMtm
/**
 * This class forms the entry point to all of the server MTM
 * functionality. It is capable of initiating the following
 * functionality:
 *
 *   * Sending a MMS message
 *
 *   * Fetching the MMS body for an incomplete MMS message (message
 *     notification)
 *
 * CMmsServerMtm does not implement any of the above functionality
 * directly but it will own objects that do. It does interpret the
 * incoming commands and initiate the required operations to handle
 * them.
 */
	{
public:
	/**
	 * 2 phase constructor.
	 *
	 * Creates a CMmsServerMtm.
	 *
	 * Note that this function should not be called directly. It should
	 * only be invoked indirectly by the message server.
	 *
	 * @exception Can leave if there is no available memory.
	 * @aReturn A fully constructed CMmsServerMtm object.
	 * @param aMmsServerMtmDll The MMS server MTM DLL.
	 * @param aEntry The CMsvServerEntry used for selecting messages.
	 */
	IMPORT_C static CMmsServerMtm* NewL(CRegisteredMtmDll& aMmsServerMtmDll,
												  CMsvServerEntry* aEntry);

	/**
	 * Destructor
	 */
	~CMmsServerMtm();


	/**
	 * CBaseServerMtm function.
	 * Not supported for MMS.
	 */
	void CopyFromLocalL(const CMsvEntrySelection& aSelection, TMsvId aDestination, TRequestStatus& aStatus);


	
	/**
	 * CBaseServerMtm function.
	 * Not supported for MMS.
	 */
	void CopyToLocalL(const CMsvEntrySelection& aSelection, TMsvId aDestination, TRequestStatus& aStatus);
	
	
	
	/**
	 * CBaseServerMtm function.
	 * Not supported for MMS.
	 */
	void DeleteAllL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);


	
	/**
	 * CBaseServerMtm function.
	 * Not supported for MMS.
	 */
	void MoveToLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	

	
	/**
	 * CBaseServerMtm function.
	 * Not supported for MMS.
	 */
	void MoveFromLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	
	
	
	/**
	 * CBaseServerMtm function.
	 * Not supported for MMS.
	 */
	void MoveWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);

	

	/**
	 * CBaseServerMtm function.
	 * Not supported for MMS.
	 */
	void CopyWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus);
	
	
	/**
	 * States whether a command is expected.
	 *
	 * @return EFalse
	 */
	TBool CommandExpected();



	/**
	 * CBaseServerMtm derived function.
	 *
	 * This function is used to intitiate fetch and send operations.
	 *
	 * @exception The operations can leave with a variety of error codes.
	 *
	 * @param aSelection The selection of messages that should be sent
	 * by the user fetch operation.
	 *
	 * @param aStatus The status of the owning active object in the
	 * message server.
	 *
	 * @param aCommand The command to perform. Currently supported
	 * commands are:
	 *
	 * KMmsMtmSendMessage
	 * KMmsMtmBackgroundSendMessage
	 * KMmsMtmFetchMessage
	 * KMmsMtmBackgroundFetchMessage
	 * KMmsMtmAutoFetchMessage
	 * KMmsMtmBackgroundAutoFetchMessage
	 * KMmsMtmAcknowledgeNotification
	 *
	 * @param aParameter Reserved
	 */
	void StartCommandL(CMsvEntrySelection& aSelection, TInt aCommand, const TDesC8& aParameter, TRequestStatus& aStatus);

	/**
	 * MTM CreateL function.
	 * Not supported for MMS.
	 */
	void CreateL(TMsvEntry aNewEntry, TRequestStatus& aStatus);


	/**
	 * MTM ChangeL function.
	 * Not supported for MMS.
	 */
	void ChangeL(TMsvEntry aNewEntry, TRequestStatus& aStatus);

	/**
	 * MTM ProgressL function.
	 *
	 * @return A package buffer containing a TMmsTransferProgress structure.
	 */
	const TDesC8& Progress();

	/**
	 * Decides if the MTM can safely be unloaded.
	 *
	 * This function is called by the owned background operation list when
	 * there are no active background operations.
	 * If there are no active user operations either then the DLL can
	 * safely be unloaded.
	 */
	void BackgroundOperationsComplete();

	/**
	 * Allows clients to add a background operation
	 *
	 * @exception Leaves if no memory is available
	 * @param aOperation The operation to be added to the list
	 */
	 void AddBackgroundOperationL(CMmsOperation* aOperation);
private:
	/**
	 * Private helper function to initiate a user fetch operation.
	 *
	 * @param aSelection The selection of messages that should be fetched
	 * by the user fetch operation.
	 *
	 * @param aStatus The status of the owning active object in the
	 * message server.
	 *
	 * @exception The operations can leave with a variety of error codes.
	 */
	void StartUserFetchL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus, TBool aAutoFetch);


	/**
	 * Private helper function to initiate a user send operation.
	 *
	 * @param aSelection The selection of messages that should be sent
	 * by the user fetch operation.
	 *
	 * @param aStatus The status of the owning active object in the
	 * message server.
	 *
	 * @exception The operations can leave with a variety of error codes.
	 */
	void StartUserSendL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);

	
	/**
	 * Private helper function to initiate a background fetch operation.
	 *
	 * @param aSelection The selection of messages that should be fetched
	 * by the background fetch operation.
	 *
	 * @param aStatus The status of the owning active object in the
	 * message server.
	 *
	 * @exception The operations can leave with a variety of error codes.
	 */	
	void StartBackgroundFetchL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus, TBool aAutoFetch);


	/**
	 * Private helper function to initiate a background send operation.
	 *
	 * @param aSelection The selection of messages that should be sent
	 * by the background send operation.
	 *
	 * @param aStatus The status of the owning active object in the
	 * message server.
	 *
	 * @exception The operations can leave with a variety of error codes.
	 */
	void StartBackgroundSendL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);

	
	/**
	 * Private helper function to initiate an acknowledgement.
	 *
	 * This operation is used to acknowledge a notification without
	 * auto-fetching the message. It will only ever be initiated by the
	 * watcher, never by the UI.
	 *
	 * @param aSelection The selection of messages that should be acknowledged
	 *
	 * @param aStatus The status of the owning active object in the
	 * message server.
	 *
	 * @exception The operations can leave with a variety of error codes.
	 */
	void StartAcknowledgementL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);

	
	/**
	 * Private helper function to initiate a rejection.
	 *
	 * This operation is used to reject an MMS message.
	 *
	 * @param aSelection The selection of messages that should be rejected
	 *
	 * @param aStatus The status of the owning active object in the
	 * message server.
	 *
	 * @exception The operations can leave with a variety of error codes.
	 */
    void StartRejectionL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);

	/**
	 * Constructor.
	 * @param aMmsServerMtmDll The MMS server MTM DLL.
	 * @param aEntry The CMsvServerEntry used for selecting messages.
	 */
	CMmsServerMtm(CRegisteredMtmDll& aMmsServerMtmDll, CMsvServerEntry* aEntry);

	
	
	/**
	 * Part of the 2 phase construction.
	 *
	 * @exception Can leave if there is no available memory.
	 */
	void ConstructL();



	/**
	 * CBaseServerMtm derived function.
	 *
	 * Cancels the current user operation but will NOT cancel any
	 * background operations.
	 */
	void DoCancel();

	
	/**
	 * CBaseServerMtm derived function.
	 *
	 * Handles the completion of a user operation, completes the owning
	 * active object in the message server.
	 */
	void DoRunL();


	/**
	 * CBaseServerMtm derived function.
	 *
	 * Handles the completion of the server MTM.
	 */
	void DoComplete(TInt aError);

	/**
	 * Set the server MTM to active, then complete its own status.
	 *
	 * Simply completing the report status directly doesn't work and can lead
	 * to the server MTM being deleted.
	 */
	void ForceComplete();


private:
	TBool iActiveBackgroundOperations;						///< a flag stating whether or not there are any background operations running
	CMmsBackgroundOperationList* iBackgroundOperationList;	///< a list of any running background operations
	CMmsOperation* iCurrentUserOperation;					///< the current user operation
	TRequestStatus* iReportStatus;							///< the status of the owning active object in the message server
	TPckgBuf<TMmsTransferProgress> iProgressBuf;			///< the progress buffer
	TBool iCanBeUnloaded;									///< can the DLL be unloaded, ETrue if there are no running background operations
    CMmsConnectionManager* iConnMan;                        ///< the connection manager
    };



#endif
