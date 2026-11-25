// $Workfile: MmsReplyOp.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 14 $
// $Date: 31/01/02 12:16 $
//


/** @file
    This file contains the interfaces for the MMS reply operation.
 */


#ifndef __MMSREPLYOP_H__
#define __MMSREPLYOP_H__


#include <msvapi.h>     // CMsvOperation

//forward declarations
class TMmsClientProgress;
class CMmsClientMessage;
class CMmsSettings;


/**
 * UID for TMmsReplyOperationProgress
 */
const TUid KUidReplyOpProgress = {0x1000AAC0};


/**
 * This is a simple, struct-like class containing data required for reporting 
 * progress from a reply operation
 */
class TMmsReplyOpProgress
    {
    public:
        /// An enumeration to describe the current state of the operation
        enum TMmsReplyOpState
            {
            EInit,                  ///< Initial state
            ECreateNewEntry,        ///< Creating new entry for the reply message
            EInitialiseNewMessage,  ///< Initialising and storing the new MMS message
            EFinished               ///< Finished
            };
    public:
        inline TMmsReplyOpProgress();

    private:
        TUid iProgressId;           ///< The UID of this progress structure

    public:
        TMmsReplyOpState iState;    ///< The current state of the operation
        TMsvId iMessageId;          ///< The id of the message created as a result of the reply operation, or KMsvNullIndexEntryId if the state of the operation isn't EFinished
        TInt iErrorCode;                 ///< The error code of the operation if it hasn't been completed successfully, or KErrNone

    };

/**
 * A package buffer typedef of a TMmsReplyOpProgress structure for convenience 
 */
typedef TPckgBuf<TMmsReplyOpProgress> TMmsReplyOpProgBuf;

/**
 * An operation which encapsulates the creation of a reply to a received MMS message
 */
class CMmsReplyOperation : public CMsvOperation
    {
    public:
        /**
         * 2-phase constructor
         *
         * Creates, constructs and starts a CMmsReplyOperation object then returns it.
         *
         * @param aMsvSession               An open session on the messaging server
         * @param aPriority                 A priority for this operation
         * @param aObserverRequestStatus    iStatus member of the requesting active object
         * @param aOriginalId               ID of the message we wish to reply to
         * @param aDestinationId            ID of the folder in which the reply message is to be created
         * @param aReplyToAll               If EFalse, reply is addressed on to the sender of the original message. If ETrue, reply is addressed to sender, To recipients and Cc recipients of original message.
         * @exception KErrXxx Standard EPOC error codes
         * @return A new, started CMmsReplyOperation object
         */
        IMPORT_C static CMmsReplyOperation* CreateReplyL(CMsvSession& aMsvSession, TInt aPriority, TRequestStatus& aObserverRequestStatus, TMsvId aOriginalId, TMsvId aDestinationId, TBool aReplyToAll);

        /**
         * C++ destructor
         */
        IMPORT_C ~CMmsReplyOperation();

    public: // from CMsvOperation
        /**
         * Returns a package buffer containing the current state of the operation.
         *
         * Example use:
         * @code
         * // Assuming an operation iReplyOp...
         * TMmsReplyOpProgress::TMmsReplyOpState state;
         * TMmsReplyOpProgBuf package;
         * package.Copy(iReplyOp->ProgressL());
         * state = package().iState;
         * @endcode
         *
         * Note that in practice this will rarely be called as this operation is expected to be quick to complete.
         *
         * @exception None Does not leave: trailing L defined in base class
         * @return A TMmsReplyOpProgBuf encapsulating the current state of the operation. Note that if the operation has completed this will be <code>EFinished</code>.
         */
	    IMPORT_C virtual const TDesC8& ProgressL();

        /**
         * Returns a package buffer containing the TMsvId of the newly-created reply message.
         *
         * Example use:
         * @code
         * // Assuming a Client MTM object iMmsClientMtm and a TMsvPartList object partList
         * CMsvOperationWait* wait = CMsvOperationWait::NewLC();
         * wait->Start();
         * CMsvOperation* op = iMmsClientMtm->ReplyL(KMsvDraftEntryId, partList, wait->iStatus); // returns a CMmsReplyOperation
         * CleanupStack::PushL(op);
         * CActiveScheduler::Start();
         * // Check op for successful completion, then...
         * TMsvId replyEntryId;
         * TMmsReplyOpProgBuf package;
         * package.Copy(op->FinalProgress());
         * replyEntryId = package().iMessageId; // Now you have the new message's ID
         * CleanupStack::PopAndDestroy(2); // op, wait
         * @endcode
         *
         * @return A TMmsReplyOpProgBuf encapsulating the ID of the newly-created reply message.
         */
	    IMPORT_C virtual const TDesC8& FinalProgress();

        /**
         * Get the UID of the MTM associated with this operation.
         * @retval KUidMsgTypeMMS
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
         * Creates a new entry to store the new (reply) MMS message in.
         * Also restores the original message from the messaging store.
         *
         * This is called from the RunL and forms the first step of the operation.
         *
         * @exception KErrXxx Standard EPOC error codes
         */
        void CreateNewEntryL();

        /**
         * Initialises necessary data in the new reply message as follows:
         * @li Subject is set to the original message subject, preceded by a token loaded from resource file (e.g. "Re: ")
         * @li First To recipient is set as sender of original message
         * @li Other To and Cc recipients are copied from the original message if Reply To All is requested. (Note that the user's From address, as specified in the settings object in the MMS service entry, is filtered out if found.)
         *
         * This is called from the RunL and forms the second step of the operation.
         *
         * @exception KErrXxx Standard EPOC error codes
         */
        void InitialiseNewMessageL();

    private:
        /**
         * C++ constructor
         *
         * @param aMsvSession               An open session on the messaging server
         * @param aPriority                 A priority for this operation
         * @param aObserverRequestStatus    iStatus member of the requesting active object
         * @param aOriginalId               ID of the message we wish to reply to
         * @param aDestinationId            ID of the folder in which the reply message is to be created
         * @param aReplyToAll               If <code>EFalse</code>, reply is addressed on to the sender of the original message. If <code>ETrue</code>, reply is addressed to sender, To recipients and Cc recipients of original message.
         */
        CMmsReplyOperation(CMsvSession& aMsvSession, TInt aPriority, TRequestStatus& aObserverRequestStatus, TMsvId aOriginalId, TMsvId aDestinationId, TBool aReplyToAll);
        
        /**
         * 2nd phase constructor. Constructs the objects member data.
         * 
         * @exception KErrXxx Standard EPOC error codes
         */
        void ConstructL();

        /**
         * Completes the requesting active object with <code>KErrNone</code>.
         * Any error code passed in can be retrieved from the operation progress by calling ProgressL.
         *
         * @param aErrorCode The error code to copy into the operation's progress structure
         */
        void CompleteRequestingObject(TInt aErrorCode);

    private:
        TMsvId iOriginalId;                     ///< ID of the message this operation is replying to
        TMsvId iDestinationId;                  ///< ID of the directory the new message should be created in

        CMmsClientMessage* iOriginalMessage;    ///< The original message used to seed the new message
        CMmsClientMessage* iNewMessage;         ///< The new reply message
        TMmsReplyOpProgress iProgress;          ///< The current state of the operation
        CMsvOperation* iOp;                     ///< The operation to create the new entry
        CMsvEntry* iEntry;                      ///< For creating the new entry that results from this operation
        TBool iReplyToAll;                      ///< Flag indicating whether a Reply To All is required
        TMsvEntry iIndexEntry;

        HBufC* iSubjectPrefix;                  ///< The subject prefix for new reply messages, read from resource file

        TMmsReplyOpProgBuf iProgressBuf;        ///< Package buffer returned by ProgressL() and FinalProgressL()
    };


#include "MmsReplyOp.inl"

#endif // __MMSREPLYOP_H__
