// $Workfile: MmsForwardOp.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 17 $
// $Date: 9/01/02 11:07 $
//


/** @file
    This file contains the interface to the MMS forward operation.
 */


#ifndef __MMSFORWARDOP_H__
#define __MMSFORWARDOP_H__


#include <msvapi.h>     // CMsvOperation

//forward declarations
class CMmsClientMessage;


/**
 * UID for TMmsForwardOperationProgress
 */
const TUid KUidForwardOpProgress = {0x1000AABF};


/**
 * This is a simple, struct-like class containing data required for reporting 
 * progress from a forward operation
 */
class TMmsForwardOpProgress
    {
    public:
    /**
     * An enumeration to describe the current state of the operation
     */
        enum TMmsForwardOpState
            {
            EInit,
            ECreateEntry,
            ECreateNewMessage,
            ECopyMediaObjects,
            EStoreNewMessage,
            EFinished
            };
    public:
        /**
         *  Default constructor
         */
        inline TMmsForwardOpProgress();

    private:
        TUid iProgressId;                ///< The UID of this progress structure

    public:
        TMmsForwardOpState iState;       ///< The current state of the operation
        TMsvId iMessageId;               ///< The id of the message created as a result of the forward operation, or KMsvNullIndexEntryId if the state of the operation isn't EFinished
        TInt iErrorCode;                 ///< The error code of the operation if it hasn't been completed successfully, or KErrNone

    };

/**
 * A package buffer typedef of a TMmsForwardOpProgress structure for convenience 
 */
typedef TPckgBuf<TMmsForwardOpProgress> TMmsFwdOpProgBuf;


/**
 * An operation which encapsulates the creation of a forwarded MMS message
 */
class CMmsForwardOperation : public CMsvOperation
    {
    public:
        /**
         * C++ constructor
         *
         * @param aMsvSession An open session on the messaging server
         * @param aPriority A priority for this operation
         * @param aObserverRequestStatus iStatus member of the requesting active object
         * @param aOriginalId ID of the message we wish to forward
         * @param aDestinationId ID of the folder in which the forward message is to be created
         * @exception KErrXxx Standard EPOC error codes
         * @return A newly created and commenced CMmsForwardOperation object
         */
        IMPORT_C static CMmsForwardOperation* CreateForwardL(CMsvSession& aMsvSession, TInt aPriority, TRequestStatus& aObserverRequestStatus, TMsvId aOriginalId, TMsvId aDestinationId);
        /**
         * C++ destructor
         */
        IMPORT_C ~CMmsForwardOperation();

    public: // from CMsvOperation
        /**
         * Returns a package buffer containing the current state of the operation.
         *
         * Example use:
         * @code
         * // Assuming an operation iFwdOp...
         * TMmsForwardOpProgress::TMmsForwardOpState state;
         * TMmsFwdOpProgBuf package;
         * package.Copy(iFwdOp->ProgressL());
         * state = package().iState;
         * @endcode
         *
         *
         * @exception None Does not leave: trailing L defined in base class
         * @return A TMmsFwdOpProgBuf packaging progress information, including the current state of the operation. Note that
         * if the operation has completed this will be <code>EFinished</code>.
         */
	    IMPORT_C virtual const TDesC8& ProgressL();

        /**
         * Returns a package buffer containing the TMsvId of the newly-created forward message.
         *
         * Example use:
         * @code
         * // Assuming a Client MTM object iMmsClientMtm and a TMsvPartList object partList
         * CMsvOperationWait* wait = CMsvOperationWait::NewLC();
         * wait->Start();
         * CMsvOperation* op = iMmsClientMtm->ForwardL(KMsvDraftEntryId, partList, wait->iStatus); // returns a CMmsForwardOperation
         * CleanupStack::PushL(op);
         * CActiveScheduler::Start();
         * // Check op for successful completion, then...
         * TMsvId forwardEntryId;
         * TMmsFwdOpProgBuf package;
         * package.Copy(op->FinalProgress());
         * forwardEntryId = package().iMessageId; // Now you have the new message's ID
         * CleanupStack::PopAndDestroy(2); // op, wait
         * @endcode
         *
         * @return A TMmsFwdOpProgBuf packaging progress information, including the ID of the  newly-created forward message 
         * if the operation was successful, and the appropriate error code if the operation failed.
         */
	    IMPORT_C virtual const TDesC8& FinalProgress();
        
        /**
         * Get the UID of the MTM associated with this operation.
         * @retval KUidMsgTypeMMS The MTM UID for MMS
         */
	    IMPORT_C virtual TUid Mtm() const;

    private: // from CActive
        /**
         * Cancels any asynchronous calls outstanding on this operation.
         */
        virtual void DoCancel();
        /**
         * Implements this operation's state machine to break up a potentially long-running task into a number of steps.
         * The operation is re-scheduled between steps and signals the requesting active object at the end of the last step.
         *
         * @exception KErrXxx Standard EPOC error codes
         */
        virtual void RunL();
        /**
         * Called by the Active Scheduler if the AO's RunL leaves.
         * This should handle the leave code (passed in as aError) and return KErrNone to prevent the AS from panicking.
         *
         * @param aError Leave code from the RunL method
         */
        virtual TInt RunError(TInt aError);

    private:
        /**
         * Updates the state machine of this operation
         */
        void SelectNextState();
        /**
         * Restores the original MMS message from the message store and creates a new entry, required for the
         * new MMS message that'll be created as a result of this operation
         * 
         * @exception KErrXxx Standard EPOC error codes
         */
        void CreateNewEntryL();
        /**
         * Initialises a new MMS message, formatting its subject field
         *
         * @exception KErrXxx Standard EPOC error codes
         */
        void CreateNewMessageL();
        /**
         * Copies the next media object from the original message to the new message.  SelectNextState is responsible 
         * for the correct iteration through the media objects of the original message
         *
         * @exception KErrXxx Standard EPOC error codes
         */
        void CopyMediaObjectL();
        /**
         * Commits the new message to the messaging store after deleting the temporary directory into which
         * the media objects of the original message were copied.
         *
         * @exception KErrXxx Standard EPOC error codes
         */
        void StoreNewMessageL();
        /**
         * Completes the requesting active object with <code>KErrNone</code>.
         * Any error code passed in can be retrieved from the operation progress by calling ProgressL.
         *
         * @param aErrorCode The error code to copy into the operation's progress structure
         */
        void CompleteRequestingObject(TInt aErrorCode);
        
    private:
        /**
         * C++ constructor
         *
         * @param aMsvSession An open session on the messaging server
         * @param aPriority A priority for this operation
         * @param aObserverRequestStatus iStatus member of the requesting active object
         * @param aOriginalId ID of the message we wish to forward
         * @param aDestinationId ID of the folder in which the forward message is to be created
         */
        CMmsForwardOperation(CMsvSession& aMsvSession, TInt aPriority, TRequestStatus& aObserverRequestStatus, TMsvId aOriginalId, TMsvId aDestinationId);
        /**
         * 2nd phase constructor. Constructs the objects member data.
         * 
         * @exception KErrXxx Standard EPOC error codes
         */
        void ConstructL();

    private:
        TMsvId iOriginalId;         ///<The id of the message being forwarded
        TMsvId iDestinationId;      ///<The id of the directory in the message store that will hold the new message
        CMmsClientMessage* iOriginalMessage;    ///<The original message that will seed the new message
        CMmsClientMessage* iNewMessage;     ///<The new message created as a result of this operation
        TMmsForwardOpProgress iProgress;   ///<The current state of the operation
        CMsvOperation* iOperation;  ///<The operation to create the new entry
        CMsvEntry* iEntry;          ///<For creating the new entry that results from this operation
        TMsvEntry iIndexEntry;      ///<The index entry of the newly created message
        HBufC* iSubjectPrefix;      ///< The subject prefix for new forward messages, read from resource
        TMmsFwdOpProgBuf iProgressBuf;   ///< Package buffer returned by ProgressL() and FinalProgressL()
        CFileMan* iFileMan;         ///< File management class
        
    };

#include "MmsForwardOp.inl"

#endif //__MMSFORWARDOP_H__
