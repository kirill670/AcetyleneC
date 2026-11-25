// $Workfile: MmsClientMtm.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 24 $
// $Date: 25/03/02 17:00 $
//


/** @file
    This file contains the interface for the MMS client MTM.
 */


#ifndef __MMSCLIENTMTM_H__
#define __MMSCLIENTMTM_H__


#include <mtclbase.h>       // CBaseMtm


// Forward declarations
class CMmsClientMessage;
class CMmsClientMtmSmilGenerator;
class CMmsSettings;



/**
 * The MMS client MTM.
 *
 * Implements the standard client MTM interface from CBaseMtm, including several functions which manipulate
 * an MMS message referenced by the MTM (e.g. AddAddresseeL, SetSubjectL, etc.). The MTM maintains an MMS message
 * object: changes made by these APIs are cached in this object then written to the message store when
 * SaveMessageL is called.
 *
 * Note that before these message manipulation methods are called, the MTM's MMS message must be initialised.
 * This is done in one of the following ways:
 * @li <b>Load an existing message.</b> Call <code>SetCurrentEntryL</code> or <code>SwitchCurrentEntryL</code> to
 *     set the MTM's context to an existing entry, then call <code>LoadMessageL</code>.
 * @li <b>Create a new message.</b> Call <code>SetCurrentEntryL</code> or <code>SwitchCurrentEntryL</code> to
 *     set the MTM's context to a folder entry, then call <code>CreateMessageL</code> to create a new message in that folder.
 *
 */
class CMmsClientMtm : public CBaseMtm
    {
    public:
        /**
         * 2-phase constructor.
         * Creates, constructs and returns a new CMmsClientMtm object.
         * @param aRegisteredMtmDll Registration data for the MTM DLL
         * @param aSession An open session to the messaging server
         * @return A new CMmsClientMtm object
         * @exception KErrXxx Standard EPOC error codes if allocation or construction of the object fails
         */
        IMPORT_C static CMmsClientMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);

        /**
         * C++ destructor
         */
        IMPORT_C ~CMmsClientMtm();

    public: // from CBaseMtm

        /**
         * Loads the MTM's cached message details from the messaging store.
         * @exception KErrXxx Standard EPOC error codes
         */
        IMPORT_C virtual void LoadMessageL();

        /**
         * Commits the MTM's cached message details to the messaging store.
         *
         * If SendAs (or the Client MTM API) has been used to add body text or attachments,
         * these are converted to MMS media objects here and an appropriate SMIL presentation is generated.
         * @exception KErrXxx Standard EPOC error codes
         */
        IMPORT_C virtual void SaveMessageL();

        /**
         * Validate the current message.
         * @note This function will raise a panic by calling <code>User::Invariant()</code> if the MTM's MMS message object has not been initialised: see notes at the top of this document on how to initialise it.
         * @param aPartList A bitset identifying the parts to be validated. Note that <code>KMsvMessagePartRecipient</code> is the only part supported in this version.
         * @return If valid, <code>KErrNone</code>. If invalid, identifies the invalid part(s). The error value is the logical OR of the TMsvPartList bits for each invalid part.
         *         Note that in the current version the only bit used in this return value will be <code>KMsvMessagePartRecipient</code>.
         */
        IMPORT_C virtual TMsvPartList ValidateMessage(TMsvPartList aPartList);
        
        /**
         * Finds text in the current message.
         *
         * For the current release, support is only provided for searching within recipients, sender and subject.
         * Attempts to search in other message parts will be ignored.
         * @note This function will raise a panic by calling <code>User::Invariant()</code> if the MTM's MMS message object has not been initialised: see notes at the top of this document on how to initialise it.
         * @param aTextToFind The text to find
         * @param aPartList The message parts to search in
         * @return The message parts where the text was found, or <code>KMsvMessagePartNone</code> if not found.
         */
        IMPORT_C virtual TMsvPartList Find(const TDesC& aTextToFind, TMsvPartList aPartList);

        /**
         * Create a reply to the current message.
         *
         * Returns a CMmsReplyOperation. When this completes, its FinalProgress() method can be 
         * used to get the TMsvId of the newly-created message. (See CMmsReplyOperation.)
         * @note This function will panic with <code>EMmsMtmPanicInvalidContext</code> if the MTM's context is not set to an MMS message.
         * @param aDestination      The ID of a folder where the reply message should be created
         * @param aPartlist         Identifies the parts to be included in the reply message.
         *                          Set the KMsvMessagePartRecipient bit to specify Reply To All,
         *                          and clear it to specify a reply to original sender only.
         *                          All other bits are ignored.
         * @param aCompletionStatus Request status of the requesting active object
         * @exception KErrXxx Standard EPOC error codes
         * @return A CMmsReplyOperation object
         */
        IMPORT_C virtual CMsvOperation* ReplyL(TMsvId aDestination, TMsvPartList aPartlist, TRequestStatus& aCompletionStatus);

        /**
         * Create a forward of the current message.
         *
         * Returns a CMmsForwardOperation. When this completes, its FinalProgress() method can be 
         * used to get the TMsvId of the newly-created message. (See CMmsForwardOperation.)
         * @note This function will panic with <code>EMmsMtmPanicInvalidContext</code> if the MTM's context is not set to an MMS message.
         * @param aDestination      The ID of a folder where the forward message should be created
         * @param aPartlist         Ignored
         * @param aCompletionStatus Request status of the requesting active object
         * @exception KErrXxx Standard EPOC error codes
         * @return A CMmsForwardOperation object
         */
        IMPORT_C virtual CMsvOperation* ForwardL(TMsvId aDestination, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);

        /**
         * Add a To recipient to the MTM's message, and also to the MTM's cached addressee list.
         * This is a generic interface for use mainly by the CSendAs API.
         * For more flexible manipulation (such as adding Cc and Bcc recipients) you should use the CMmsClientMessage API in the MMSUTILS library.
         * @note This function will raise a panic by calling <code>User::Invariant()</code> if the MTM's MMS message object has not been initialised: see notes at the top of this document on how to initialise it.
         * @param aRealAddress The address to add. This should be one of the following: IPv4 address, IPv6 address, global phone number, RFC822 e-mail address.
         * @exception KErrXxx Standard EPOC error codes if memory cannot be allocated to store the new addressee
         */
        IMPORT_C virtual void AddAddresseeL(const TDesC& aRealAddress);

        /**
         * Add a To recipient to the MTM's message, and also to the MTM's cached addressee list.
         * This is a generic interface for use mainly by the CSendAs API.
         * For more flexible manipulation (such as adding Cc and Bcc recipients) you should use the CMmsClientMessage API in the MMSUTILS library.
         * @note This function will raise a panic by calling <code>User::Invariant()</code> if the MTM's MMS message object has not been initialised: see notes at the top of this document on how to initialise it.
         * @param aRealAddress The address to add. This should be one of the following: IPv4 address, IPv6 address, global phone number, RFC822 e-mail address.
         * @param aAlias This parameter is ignored.
         * @exception KErrXxx Standard EPOC error codes if memory cannot be allocated to store the new addressee
         */
        IMPORT_C virtual void AddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias);

        /**
         * Remove a To recipient from the MTM's message.
         * @note This function will raise a panic by calling <code>User::Invariant()</code> if the MTM's MMS message object has not been initialised: see notes at the top of this document on how to initialise it.
         * @param aIndex The index of the recipient to be deleted. The function will panic with <code>EMmsMtmPanicBadAddresseeIndex</code> if this is out of bounds.
         */
        IMPORT_C virtual void RemoveAddressee(TInt aIndex);

        /**
         * Set the subject of the MTM's currtent message.
         * @note This function will raise a panic by calling <code>User::Invariant()</code> if the MTM's MMS message object has not been initialised: see notes at the top of this document on how to initialise it.
         * @param aSubject The new subject for the MTM's message
         * @exception KErrXxx Standard EPOC error codes if allocation of the new subject fails
         */
        IMPORT_C virtual void SetSubjectL(const TDesC& aSubject);

        /**
         * Get the subject of the MTM's current message.
         * @note This function will raise a panic by calling <code>User::Invariant()</code> if the MTM's MMS message object has not been initialised: see notes at the top of this document on how to initialise it.
         * @return The subject of the MTM's message. This will be a zero-length descriptor if no subject has been set.
         * exception None This function does not leave
         */
        IMPORT_C virtual const TPtrC SubjectL() const;

        /**
         * Creates a child attachment entry under the current message.
         * @note
         * Only one file should be stored in the directory returned.
         * Any other files in the directory will be ignored.
         * To add more than one attachment, call this function repeatedly.
         * @note
         * This function will raise a panic by calling <code>User::Invariant()</code> if the MTM's MMS message object has not been initialised: see notes at the top of this document on how to initialise it.
         * @param aAttachmentId On return, contains the ID of the new attachment entry
         * @param aDirectory On return, contains the file directory owned by the attachment. The attachment payload should be stored as a file in this directory.
         * @exception KErrXxx Standard EPOC error codes if a directory cannot be created to store this attachment.
         */
        IMPORT_C virtual void CreateAttachmentL(TMsvId& aAttachmentId, TFileName& aDirectory);

        /**
         * Deletes an attachment identified by aAttachmentId under the entry identified by aMessageId
         * @param aMessageId A MMS message ID. This must identify a valid MMS message or the function will panic with <code>EMmsMtmPanicInvalidContext</code>.
         *                   If this ID is the same as the ID of the MTM's current context, no context switch will occur.
         *                   Otherwise the MTMN's context is switched and all changed made to the current context since the last call to
         *                   <code>SaveMessageL()</code> will be lost. In this case, <code>LoadMessageL()</code> should be called before any further
         *                   data is set on the context (e.g. adding addressees, attachments, subject, etc.)
         * @param aAttachmentId The ID if the attachment to be deleted.
         * @exception KErrNotFound An attachment with ID </code>aAttachmentId</code> was not found under the message with ID <code>aMessageId</code>
         */
        IMPORT_C virtual void DeleteAttachmentL(TMsvId aMessageId, TMsvId aAttachmentId);

        /**
         * Create a new message for this MTM. This creates a new messaging entry, then
         * re-initialises the MTM's CMmsClientMessage object with this new entry's context.
         * @param aServiceId The ID of the service for which the message is to be created
         * @exception KErrXxx Standard EPOC error codes if construction of new objects fails
         */
        IMPORT_C virtual void CreateMessageL(TMsvId aServiceId);

        /**
         * Query the capabilities of this MTM.
         * @param aCapability A capability UID from MTMUIDS.H
         * @param aResponse For some capabilities, this will contain a value indicating the kind of support provided.
         * @retval KErrNone This capability is supported by the MTM
         * @retval KErrNotSupported This capability is not supported by the MTM
         */
        IMPORT_C virtual TInt QueryCapability(TUid aCapability, TInt& aResponse);

        /**
         * Not supported in this MTM.
         * @exception KErrNotSupported Always leaves with this code
         */
        IMPORT_C virtual void InvokeSyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter);

        /**
         * Invoke an asynchronous MMS-specific function on the MTM.
         * All functions are currently delegated directly to the server MTM.
         * @note The calling code takes ownership of the returned CMsvOperation and is responsible for deleting it.
         * @param aFunctionId An MMS function ID from the TMmsMtmCmds enum in MmsMtmCmds.h
         * @param aSelection A CMsvEntrySelection appropriate to the function being called. For send/fetch operations, this lists the IDs of the messages to be sent or fetched.
         * @param aParameter A descriptor/package buffer parameter appropriate to the function being called
         * @param aCompletionStatus The iStatus of the requesting active object
         * @exception KErrDiskFull If <code>aFunctionId</code> is <code>KMmsMtmFetchMessage</code> or <code>KMmsMtmBackgroundFetchMessage</code>, leaves with this code if there is not enough disk space available to fetch the message(s).
         * @exception KErrXxx Standard EPOC error codes if an error occurs transferring the command to the server MTM
         * @return A running CMsvOperation object which can be used to track the progress of the asynchronous object.
         */
        IMPORT_C virtual CMsvOperation* InvokeAsyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus);

    private: // from CBaseMtm

        /**
         * This function is called after the context of this instance has been changed to another entry, and
         * is responsible for cleaning up the MTM's current context.
         * @note
         * This function deletes the MTM's MMS message object: note that this must be re-initialised before the MTM's
         * message manipulation APIs can be used.
         */
        virtual void ContextEntrySwitched(); // called after the context of this instance has been changed to another entry

    private:

        /**
         * C++ constructor.
         */
        CMmsClientMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aMsvSession);

        /**
         * 2nd-phase constructor. Initialises this object's member data.
         * @exception KErrXxx Standard EPOC error codes if allocation or construction of the object's members fails
         */
        void ConstructL();
        
        /**
         * Constructs the MTM's CMmsClientMessage with the current context.
         * @exception KErrXxx Standard EPOC error codes if construction of the CMmsClientMessage object fails.
         */
        void InitialiseMmsMessageL();
        
        /**
         * If SendAs (or the CBaseMtm::Body() API) has been used to specify body text, this function converts it into
         * a plain text MMS media object. This plain text object will be referenced by the message's SMIL presentation.
         * @exception KErrXxx Standard EPOC error codes, e.g. if the new media objects' binary files cannot be opened for writing
         */
        void ConvertSendAsBodyL();
        
        /**
         * If SendAs (or the CBaseMtm API) has been used to specify attachments, this function converts them into media objects.
         * @exception KErrXxx Standard EPOC error codes, e.g. if the new media objects' binary files cannot be opened for writing
         */
        void ConvertSendAsAttachmentsL();
        
        /**
         * Check if there is sufficient disk space available to fetch the listed MMS message(s).
         * @retval EFalse There is not sufficient disk space available
         * @retval ETrue There is sufficient disk space available
         * @param aSelection One or more MMS messages for which available disk space should be checked
         */
        TBool EnoughDiskSpaceToFetchMessagesL(const CMsvEntrySelection& aSelection);

        /**
         * Do basic file type recognition based on filename extension.
         * Note this does not use the file recognizers provided by APPARC because of the associated efficiency overhead,
         * and also because recognizers do not yet exist for some of the types we need to process (e.g. AMR, WBMP).
         * @param aFileName The filename to recognize
         * @return A MIME type string (e.g. "image/gif").
         */
        TPtrC RecognizeFileL(const TDesC& aFileName);

    private:
        CMmsClientMessage* iMmsMessage;
        CMmsClientMtmSmilGenerator* iSmilGenerator;

    private:
        enum TPanicCodes
            {
            EMmsMtmPanicUnknownFunctionID,  ///< Panic code used if an unknown function ID is passed to InvokeAsyncFunctionL
            EMmsMtmPanicInvalidContext,     ///< Panic code used if the MTM's context is set to an entry which is not an MMS message
            EMmsMtmPanicNullAddresseeList,  ///< Panic code used if a function such as AddAddresseeL is called while the MTM's addressee list is NULL
            EMmsMtmPanicBadAddresseeIndex,  ///< Panic code used if the index passed to RemoveAddressee is out of bounds
            EMmsMtmPanicNullEntry           ///< Panic code used if iMsvEntry is accessed whilst NULL
            };

        /**
         * Panic function for the CMmsClientMtm class
         */
        void Panic(TPanicCodes aReason) const;

        // Declare standard invariant test functions
        __DECLARE_TEST;
    };


#endif // __MMSCLIENTMTM_H__
