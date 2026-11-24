/*
* ============================================================================
*  Name     : CMmsClientMtm from mmsclient.h
*  Part of  : mmsengine\clientmtm
*
*  Description: 
*     Client Mtm for multimedia messaging.
*     This is the API for accessing multimedia messaging engine.
*  Version:
*
*  Copyright (C) 2002-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef MMSCLIENT_H
#define MMSCLIENT_H

//  INCLUDES
#include  <mtclbase.h> // base client mtm
#include  <e32std.h>   // TTimeInterval & TTime
#include  "mmsconst.h" // common constants

// CONSTANTS

// MACROS

// DATA TYPES
typedef struct
    {
    const TUint SymbianCharsetUID;
    const TUint IANAMIBEnum;
    }TMmsCharacterSetLookup;

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CMmsSettings;
class CMmsHeaders;
class CMsvMimeHeaders;
class CMsvFindText;
class CMmsAttachmentWaiter;

// CLASS DECLARATION

/**
*  Client Mtm for multimedia messaging subsystem.
*  This class will be the interface to the UI component
*  and other messaging component that might want to handle multimedia messages
*  (For example SendAs interface).
*
*   Note: new functions has to be added as last virtual functions in order
*   not to to break the vtable 
*/
class CMmsClientMtm :public CBaseMtm
    {
    public:  // Constructors and destructor
        // constructor is private!

        /**
        * Factory function.
        * The only function exported by this polymorphic interface dll.<br>
        * This function is not directly called by the application that needs
        * access, it is called by an instance of CClientMtmRegistry class.
        * @param  aRegisteredMtmDll Reference to Mtm Dll registry class
        * @param  aSession Reference to a Message Server session.
        * @return Pointer to CMmsClientMtm class.
        *
        * <PRE>
        * Example of getting access to this class:
        *
        * // Called by a Uikon application that implements
        * // MMsvSessionObserver interface
        *
        * iSession = CMsvSession::OpenSyncL(*this);
        * CleanupStack::PushL(iSession);
        * iClientMtmRegistry = CClientMtmRegistry::NewL(*iSession);
        * CleanupStack::PushL(iClientMtmRegistry);
        * iMmsClient = (CMmsClientMtm *) iClientMtmRegistry->
        *               NewMtmL(KUidMsgTypeMultimedia);
        * CleanupStack::PushL(iMmsClient);
        *
        * // - do other initialization -
        *
        * CleanupStack::Pop(3);    //iSession, iClientMtmRegistry, iMmsClient
        *
        * // - call any public functions in CMmsClientMtm
        *
        * // When the application finishes,
        * // it must delete the objects in reverse order:
        * delete iMmsClient;
        * delete iClientMtmRegistry;
        * delete iSession;
        * </PRE>
        */
        IMPORT_C static CMmsClientMtm* NewL(
            CRegisteredMtmDll& aRegisteredMtmDll,
            CMsvSession& aSession );
        
        /**
        * Destructor.
        */
        virtual ~CMmsClientMtm();

    public:  // New functions

        // ----------------------------------------------------------
        // Functions to create and modify message entries

        /**
        * Create a new message entry
        * @param aDestination target folder
        * @param aCompletionStatus Reference to the status of
        *     an active object.<br>
        *     This status will be set as completed when the operation
        *     completes.
        * @return Pointer to a message server operation (active object). <br>
        *     The progress information provides the id of the created message 
        *     when the message has been created in a 8-bit descriptor. 
        *     While the operation is in progress the package will contain a
        *     null id (KMsvNullIndexEntryId). If there was an error while
        *     creating the message, then the message will be deleted and the
        *     package will contain null id.
        */
        virtual CMsvOperation* CreateNewEntryL(
            TMsvId aDestination, 
            TRequestStatus& aCompletionStatus);
    
        
        // -------------------------------------------------------------------
        // FUNCTIONS TO HANDLE MMSC SETTINGS
        // 
        // Only one MMS service entry may be created!
        // 
        // The Client MTM maintains cached MMS service settings, referred to
        // as current service below. Some of those cached settings are used
        // as template values when a new multimedia message is created.

        /**
        * Create new service entry.
        * Context is set to the new service entry.
        * Currently maximum one service is created, and further requests
        * do not create a new service entry! 
        */
        virtual void CreateServiceL();
        
        // Use Base MTM functions to get default service id.
        
        // Functions to load, save, and access MMS Settings
        // There is no need to set context to service when
        // these functions are used.
        //
        // Usage:
        // 
        // CMmsSettings* settings = CMmsSettings::NewL();
        // CleanupStack::PushL( settings );
        // iMmsClient->RestoreSettingsL();
        // settings->CopyL( iMmsClient->MmsSettings() );
        //
        // // change settings here...
        // // The settings are changed using CMmsSettings API
        //
        // iMmsClient->SetSettingsL( *settings );
        // iMmsClient->StoreSettingsL();
        // CleanupStack::PopAndDestroy(); // settings

        /**
        * Get a reference to CMmsSettings class.
        * The contents of the class are those used by MMS Client MTM
        * when constructing a message. If the settings must be changed,
        * a copy must be made, and SetSettingsL function used to deliver
        * the settings to MMS Client MTM
        * @return constant reference to iMmsSettings member of CMmsClientMtm
        */
        virtual const CMmsSettings& MmsSettings();
        
        /**
        * Copy the values from aSettings to CMmsClientMtm.
        * Used to provide new settings to MMS Client MTM when settings have
        * been changed. Will affect only messages created after the settings
        * have been changed. 
        * Use function StoreSettingsL to save the settings on disk.
        * @param aSettings new values for CMmsSettings
        */
        virtual void SetSettingsL( const CMmsSettings& aSettings );
        
        /**
        * Save settings to disk
        */
        virtual void StoreSettingsL();
        
        /**
        * Load settings from disk
        */
        virtual void RestoreSettingsL();

        /**
        * Restore factory settings to the default service entry and select it
        * as the current service entry.
        * @param aLevel defines the operations to be done
        */
        virtual void RestoreFactorySettingsL( 
            TMmsFactorySettingsLevel aLevel = EMmsFactorySettingsLevelNormal );

        /**
        * Validate service.<br>
        * Checks that access points point to valid entries
        *     in comms database.
        * @return error code (defined in mmserrors.h or e32std.h)
        * KErrNone = service ok. Other error codes in mmserrors.h or e32err.h
        */
        virtual TInt ValidateService( TMsvId aServiceId );

        // -------------------------------------------------------------------
        // FUNCTIONS TO HANDLE MMS HEADERS

        // Accessors and mutators for header fields.
        // Some of these header fields have default values that are assigned
        // from cached service settings when a new header is allocated.
        // Some header fields are needed by protocol only.
        // Those headers don't have accessors and mutators here,
        // as they are used by Server MTM who accesses them directly
        // through functions offered by CMmsHeaders.

        /**
        * Sender mutator
        * @param aAlias
        */
        virtual void SetSenderL( const TDesC& aAlias );

        /**
        * Sender accessor
        * @return Real address of sender (for example phone number). <br>
        *     Alias can be searched from contacts database.
        */
        virtual const TPtrC Sender() const;

        /**
        * Message class mutator.
        * @param aMessageClass message class code
        */
        virtual void SetMessageClass( TMmsMessageClass aMessageClass );

        /**
        * Message class accessor
        * @return Message class: Personal/Advertisement/Informational. <br>
        *     values defined in MMSCONST.H
        */
        virtual TInt MessageClass() const;

        /**
        * Expiration interval mutator.
        * Both for message and service entries.
        * @param aInterval The length of time after which the message
        *     is discarded by MMSC. Expressed in seconds.
        */
        virtual void SetExpiryInterval( TTimeIntervalSeconds aInterval );

        /**
        * Expiration interval accessor.
        * Both for message and service entries.
        * @return Storage time of the message in MMSC (in seconds).
        */
        virtual TTimeIntervalSeconds ExpiryInterval() const;

        /**
        * Expiration date mutator.
        * @param aDate The date and time the message will expire (In UTC time)
        *     The date must be greater than 1970-01-01, 00:00:00 GMT (UTC time)
        */
        virtual void SetExpiryDate( TTime aDate );

        /**
        * Expiration date accessor.
        * @return The date and time the message will expire. (in UTC time)
        */
        virtual TTime ExpiryDate() const;

        /**
        * Delivery time interval mutator.
        * @param aInterval The length of time after which the message will<br>
        *     be delivered to the recipient by the MMSC.<br>
        *     Expressed in seconds.
        */
        virtual void SetDeliveryTimeInterval( TTimeIntervalSeconds aInterval );

        /**
        * Delivery time interval accessor.
        * @return delivery time interval of the message (in seconds).
        */
        virtual TTimeIntervalSeconds DeliveryTimeInterval() const;

        /**
        * Delivery date mutator.
        * @param aDate The date and time the message will be delivered <br>
        *     to the recipient by the MMSC. (in UTC time)
        *     The date must be greater than 1970-01-01, 00:00:00 GMT (UTC time)
        */
        virtual void SetDeliveryDate( TTime aDate );

        /**
        * Delivery date accessor.
        * @return The date and time the message will be delivered to the
        *     recipient by the MMSC. (in UTC time)
        */
        virtual TTime DeliveryDate() const;

        /**
        * Message priority mutator (Low/Normal/High). Default: Normal.
        * @param aPriority Message priority, values defined in MMSCONST.H
        */
        virtual void SetMessagePriority( TMmsMessagePriority aPriority );

        /**
        * Message priority accessor.
        * @return Message priority, values defined in MMSCONST.H
        */
        virtual TInt MessagePriority() const;

        /**
        * Sender visibility mutator.
        * @param aVisibility Hide or Show (values defined in MMSCONST.H)
        */
        virtual void SetSenderVisibility( 
            TMmsMessageSenderVisibility aVisibility );

        /**
        * Sender visibility accessor.
        * @return Hide or Show (values defined in MMSCONST.H)
        */
        virtual TInt SenderVisibility() const;

        /**
        * Delivery Report Request mutator.
        * @param aRequest Yes or No (values defined in MMSCONST.H)
        */
        virtual void SetDeliveryReport( 
            TMmsYesNo aRequest );

        /**
        * Delivery Report Request accessor.
        * @return Yes or No (values defined in MMSCONST.H)
        */
        virtual TInt DeliveryReport() const;

        /**
        * Read Reply Request mutator.
        * @param aRequest Yes or No (values defined in MMSCONST.H)
        */
        virtual void SetReadReply( TMmsYesNo aRequest );

        /**
        * Read Reply Request accessor.
        * @return Yes or No (values defined in MMSCONST.H)
        */
        virtual TInt ReadReply() const;

        /**
        * Sending date and time accessor.
        * Valid only for mobile terminated messages
        * @return the time when MMSC has received the message from sender.
        *     (in UTC time)
        */
        virtual TTime SendingDate() const;

        /**
        * Response text accessor.
        * Valid only in cases a response text has been obtained from MMSC:
        *     Mobile terninated messages and messages whose senging has failed.
        * @return Response text string.
        * @since 2.0
        */
        virtual TPtrC ResponseText() const;
        
        /**
        * Response status accessor.
        * This function returns the status MMS server has sent with a
        *     retrieved message.
        * This is used in case of permanent failures to indicate the
        *     reason of failure.
        * @return Status code sent by MMS server.
        * @since 3.0
        */
        virtual TInt ResponseStatus() const;
        
        /**
        * Number of previous senders in case on message forwarded
        *     without retrieval.
        * @return number of times the message has been forwarded.
        * @since 3.0
        */
        virtual TInt NumberOfPreviousSenders() const;
        
        /**
        * Address of previous sender
        * @param aSequence number indicates the number in sequence.
        *     1 is the first sender, a higher number indicates a later sender
        *     If the sequence number exceeds the number of senders, TPtrC() is
        *     returned
        * @return address of the previous senders
        * @since 3.0
        */
        virtual TPtrC PreviousSender( TInt aSequenceNumber ) const;
        
        /**
        * Time when the message was previously sent (in UTC time)
        * @param aSequence number indicates the number in sequence.
        *     1 is the time of the first sending, a higher number indicates
        *         a later sending
        *     If the sequence number exceeds the number of senders,
        *         TTime = 0 is returned
        * @return time of the previous sending (in UTC time)
        * @since 3.0
        */
        virtual TTime PreviousSendingDate( TInt aSequenceNumber ) const;
        
        /**
        * Time when the message was received in the terminal (UTC time).
        * @return time of the arrival of the message (in UTC time)
        * @since 3.0
        */
        virtual TTime MessageReceiveTime() const;
        
        /**
        * Actual message size in encoded format.
        * This is valid only for a nofification. X-Mms-Message-Size.
        * @return message size in octets.
        */
        virtual TInt MessageTransferSize() const;

        /**
        * Location of the message.
        * This is valid only for a nofification. X-Mms-Content-Location.
        * @return location of the actual message.
        */
        virtual TPtrC8 MessageContentLocation() const;

        /**
        * Message root part mutator.
        * Leaves with KErrNotFound if attachment not found.
        * @param aId Attachment Id of the message part which should be 
        * displayed first.<br>
        * Should point to the SMIL part that starts the message display.
        */
        virtual void SetMessageRootL( const TMsvAttachmentId aId );

        /**
        * Message root part accessor.
        * @return the attachment part that starts the message display.
        * KMsvNullIndexEntryId if not set.
        */
        virtual TMsvAttachmentId MessageRootAttachment() const;

        /**
        * Maximum image size mutator.
        * @param aHeight image height
        * @param aWidth image width
        */
        virtual void SetMaximumImage( TInt aWidth, TInt aHeight );

        /**
        * Maximum image size accessor.
        * @param aHeight image height (OUT)
        * @param aWidth image width (OUT)
        */
        virtual void GetMaximumImage( TInt& aWidth, TInt& aHeight ) const;

        // -------------------------------------------------------------------
        // GENERAL MESSAGE INFORMATION METHODS 

        /**
        * Message size accessor. SaveMessageL and LoadMessageL updates the 
        * value.
        * @return size of all message parts in bytes including both
        * attachments and internal header structures. The actual message
        * size in transmission is smaller due to the header
        * binary encoding.
        */
        virtual TInt32 MessageSize();

        /**
        * Message description mutator. 
        * This provides a method to override the default message description.
        * The next SaveMessageL saves the description text in the 
        * TMsvEntry::iDescription.
        * Note that this method does not check the text length, so avoid long 
        * descriptions to minimize memory usage. Zero length description is
        *     ignored.
        * @param aText message description
        */
        virtual void SetMessageDescriptionL( const TDesC& aText );
        
        // ---------------------------------------------------------------------
        // FUNCTIONS TO HANDLE EXTRA MESSAGE ATTRIBUTES (FOR UI USE ONLY)

        /** 
        * Add attribute to an attribute array. No duplicates allowed
        * If attribute exists, its value is changed
        * @param aName Name of the attribute (case sensitive)
        * @param aValue Value of the attribute
        * Leaves if memory runs out or if aValue or aName is empty
        */
        virtual void AddAttributeL( const TDesC& aName, const TDesC& aValue );
            
        /**
        * Get value for an attribute.
        * @param aName Name of the attribute (case sensitive)
        * @return Pointer to the value of the attribute
        * Leaves with KErrNotFound if attribute not found or aName is empty
        */
        virtual TPtrC GetAttributeL( const TDesC& aName );
            
        /**
        * Check if attribute is present
        * @param aName Name of the attribute (case sensitive)
        * @return ETrue if the attribute is found, EFalse otherwise
        */
        virtual TBool FindAttribute( const TDesC& aName );
            
        /**
        * Delete named attribute from list
        * @param aName Name of the attribute (case sensitive)
        */
        virtual void DeleteAttribute( const TDesC& aName );
        
        /**
        * Reset all attributes
        */
        virtual void ResetAttributes();

        // -------------------------------------------------------------------
        // FUNCTIONS TO HANDLE MESSAGE ATTACHMENTS

        /**
        * Create attachment entry and copy specified file to message store.
        * User should call SaveMessageL afterwards to update TMsvEntry of the
        *     message entry.
        * @param aStore an open EditStore. Caller must commit store
        *     (several attachments can be added before committing store)
        * @param aFile opened file handle, source of the attachment.
        *     File must be in public location to be accessible.
        *     Caller must close the file afterwards.
        * @param aMimeType mime type of the attachmet.
        * @param aMimeHeaders mime headers for the attachment. If content type
        *     is not defined, function adds the mime type and subtype from
        *     aMimeType.
        *     Suggested filename in aMimeHeaders is used as attachment name
        * @param aAttachmentInfo must be initialized to
        *     CMsvAttachment::EMsvFile.
        *     On return contains data about the attachment.
        *     Ownership of attachmentinfo is transferred to attachment manager,
        *     it must not be deleted by caller.
        * @param aAttaId attachment id of the newly created attachment
        */
        virtual void CreateAttachment2L(
            CMsvStore& aStore,
            RFile& aFile,
            TDesC8& aMimeType,
            CMsvMimeHeaders& aMimeHeaders,
            CMsvAttachment* aAttachmentInfo,
            TMsvAttachmentId& aAttaId);

        /**
        * Create text/plain attachment. <br>
        * Creates a text attachment from descriptor.
        * Has option to convert all unicode paragraph separator marks to
        *     line feeds.
        * Converts text from unicode (ucs-2) to utf-8 before storing it.
        * @param aStore an open EditStore. Caller must commit store
        *     (several attachments can be added before committing store)
        * @param aAttachmentId returned ID of the new attachment entry
        * @param aText UNICODE text to be added as a text/plain attachment.
        * @param aFile suggested filename for the attachment
        * @param aConvertParagraphSeparator flag to tell if the function 
        *     will search for all 0x2029 characters (Unicode paragraph
        *     separator) and replace them with 0x000a (line feed).
        *     aConvertParagraphSeparator == ETrue: convert
        *     aConvertParagraphSeparator == EFalse: do not convert
        */
        virtual void CreateTextAttachmentL(
            CMsvStore& aStore,
            TMsvAttachmentId& aAttachmentId,
            const TDesC& aText,
            const TDesC& aFile,
            TBool aConvertParagraphSeparator = ETrue );

        // -------------------------------------------------------------------
        // MESSAGE HANDLING FUNCTIONS 

        // NOTE: these are asynchronous functions

        /**
        * Send current message using default service settings.
        *     If no default service, aCompletionStatus will reflect the error.
        *     The message is moved to OUTBOX folder before starting to send it.
        * @param aCompletionStatus iStatus member of an active object.
        *     It will be set as completed when the request has finished.
        * @param aSendingTime time at which the message selection is to be sent
        *     given as local time. If aSending time is zero or in the past, the
        *     message is scheduled to be sent as soon as possible.
        * @return pointer to an operation active object.
        *     If successful, this is an asynchronously completing operation.
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        virtual CMsvOperation* SendL( TRequestStatus& aCompletionStatus,
            const TTime aSendingTime = TTime( 0 )  );

        /**
        * Send selection of message using default service settings.
        *     If no default service, aCompletionStatus will reflect the error.
        *     The messages are moved to OUTBOX folder before starting to send
        *     them. All messages must be in the same place originally
        *     (all in drafts, or all in outbox).
        * @param aSelection list of messages to be sent. If list is empty,
        *      nothing is sent.
        * @param aCompletionStatus iStatus member of an active object.
        *     It will be set as completed when the request has finished.
        * @param aSendingTime time at which the message selection is to be sent
        *     given as local time. If aSending time is zero or in the past, the
        *     message is scheduled to be sent as soon as possible.
        * @return pointer to an operation active object.<br>
        *     If successful, this is an asynchronously completing operation.
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        virtual CMsvOperation* SendL(
            CMsvEntrySelection& aSelection,
            TRequestStatus& aCompletionStatus,
            TTime aSendingTime = TTime( 0 ) );
        
        /**
        * Fetch all available MMS messages from current MMSC to inbox.
        * This can be used if the phone has been off, and the user wants
        * to fetch pending messages.
        * If there are postponed notifications, they are all fetched.
        * We have hoped that MMS specs would support telling MMSC that 
        * it should send new notifications for all pending messages. 
        * However, for the time being this is not possible.
        * @param aCompletionStatus iStatus member of an active object.
        *     It will be set as completed when the request has finished.
        * @aparam aForced indicates if the messages should be fetched
        *     regardless of current mode settings.
        *     ETrue = user initiated fetch, use override
        *     EFalse = event triggered fetch, fetch only if settings allow.
        * @return pointer to an operation active object.
        *     If successful, this is an asynchronously completing operation.
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        virtual CMsvOperation* FetchAllL( TRequestStatus& aCompletionStatus,
            TBool aForced = ETrue );

    public:  // FUNCTIONS FROM BASE CLASSES

        /**
        * From CBaseMtm: Return type of this Mtm
        * @return Registered Mtm type
        */
        inline TUid Type() const;


        // Context specific functions

        /**
        * From CBaseMtm: Set current context
        * @param aEntry Pointer to entry instance
        */
        inline void SetCurrentEntryL( CMsvEntry* aEntry );        

        /**
        * From CBaseMtm: Switch context to entry defined by aId.
        * @param aId Entry id in message store.
        */
        inline void SwitchCurrentEntryL( TMsvId aId );
        
        /**
        * From CBaseMtm: return reference to current entry
        * @return reference to entry instance
        */
        inline CMsvEntry& Entry() const;
        
        /**
        * From CBaseMtm: Query if entry context has been set
        * @return ETrue, if context has been set, EFalse, if not
        */
        inline TBool HasContext() const;

        // Message specific functions

        /**
        * From CBaseMtm: Store current entry data.
        */
        void SaveMessageL(); 

        /**
        * From CBaseMtm: Restore current entry data.
        */
        void LoadMessageL();

        /**
        * From CBaseMtm: Validates that selected parts of current message are
        *     legal.
        * @param aPartList Flags specifying which parts to validate.
        *     (defined in MTMDEF.H).
        *     KMsvMessagePartPartBody is ignored.
        *     KMsvMessagePartRecipient is supported.
        *     KMsvMessagePartOriginator is supported.
        *     KMsvMessagePartDescription is ignored.
        *     KMsvMessagePartDate is ignored.
        *     KMsvMessagePartAttachments is supported.
        * @return KErrNone if message is valid.
        *     If invalid, identifies the invalid part(s). The error value is
        *     the bitmask of the TMsvPartList IDs for each invalid part 
        */
        TMsvPartList ValidateMessage( TMsvPartList aPartList );
        
        /**
        * From CBaseMtm: Searches for specified text in selected parts of
        * current message.
        * @param aPartList Flags specifying which parts to search.
        *     (defined in MTMDEF.H).
        *     KMsvMessagePartPartBody is ignored.
        *     KMsvMessagePartRecipient is supported.
        *     KMsvMessagePartOriginator is supported.
        *     KMsvMessagePartDescription is supported.
        *     KMsvMessagePartDate is ignored.
        *     KMsvMessagePartAttachments is ignored.
        * Following find attributes are supported:
        *     KMsvFindCaseSensitive
        *     KMsvFindWholeWord
        * @return Flags that specify in which of the specified parts the text
        *     was found.
        */
        TMsvPartList Find( const TDesC& aTextToFind, TMsvPartList aPartList );

        /**
        * From CBaseMtm: Send a reply to current message 
        * @param aDestination Id for the new message entry.
        * @param aPartlist Flags specifying which standard message parts
        *     are to be included in the response.
        * @param aPartlist Flags specifying which standard message parts
        *     are to be included in the response.
        *     (defined in MTMDEF.H)
        *     KMsvMessagePartPartBody is ignored
        *     KMsvMessagePartRecipient causes reply-to-all. 
        *        Otherwise reply-to-sender only.
        *     KMsvMessagePartOriginator is ignored.
        *     KMsvMessagePartDescription copies Subject field.
        *     KMsvMessagePartDate is ignored.
        *     KMsvMessagePartAttachments is ignored.
        * @param aCompletionStatus Reference to the status of
        *     an active object.
        *     This status will be set as completed when the operation completes
        * @return Pointer to a message server operation (active object).
        *     The progress information provides the id of the created message
        *     when the message has been created in a 8-bit descriptor.
        *     While the operation is in progress the package will contain a
        *     null id (KMsvNullIndexEntryId). If there was an error while
        *     creating the message, then the message will be deleted and the
        *     package will contain null id.
        */
        CMsvOperation* ReplyL(
            TMsvId aDestination,
            TMsvPartList aPartlist,
            TRequestStatus& aCompletionStatus );
        
        /**
        * From CBaseMtm: Forward current message to new recipient
        * @param aDestination Id for the new message entry.
        *     to be included in the response. (defined in MTMDEF.H)
        * @param aPartlist Flags specifying which standard message parts
        *     are to be included in the response.
        *     KMsvMessagePartPartBody is ignored.
        *     KMsvMessagePartRecipient is ignored.
        *     KMsvMessagePartOriginator is ignored.
        *     KMsvMessagePartDescription copies Subject field.
        *     KMsvMessagePartDate is ignored.
        *     KMsvMessagePartAttachments is ignored.
        * @param aCompletionStatus Reference to the status of
        *     an active object.
        *     This status will be set as completed when the operation completes
        * @return Pointer to message server operation (active object).
        *     The progress information provides the id of the created message 
        *     when the message has been created in a 8-bit descriptor. 
        *     While the operation is in progress the package will contain a
        *     null id (KMsvNullIndexEntryId). If there was an error while
        *     creating the message, then the message will be deleted and the
        *     package will contain null id.
        */
        CMsvOperation* ForwardL(
            TMsvId aDestination,
            TMsvPartList aPartList,
            TRequestStatus& aCompletionStatus );
        
        /**
        * New recipient list function is not virtual, and the base MTM
        * implementation must always be used.
        * The function is shown here for reference only
        */
//        const CMsvRecipientList& AddresseeList() const;

        /**
        * From CBaseMtm: Adds an addressee. Cannot distiguish To, Cc, and Bcc.
        * New addresses are handled as To type of addresses.
        * @param aRealAddress Reference to an address string
        */
        void AddAddresseeL( const TDesC& aRealAddress );
        
        /**
        * From CBaseMtm: Adds an addressee. Cannot distiguish To, Cc, and Bcc.
        * New addresses are handled as To type of addresses. 
        * @param aRealAddress Reference to an address string
        * @param aAlias Reference to a descriptive name (not a real address)
        */
        void AddAddresseeL( const TDesC& aRealAddress, const TDesC& aAlias );
        
        /**
        * From CBaseMtm: Adds a typed addressee (To, Cc or Bcc )
        * @param aType recipient type (EMsvRecipientTo, EMsvRecipientCc,
        *     or EMsvRecipientBcc)
        * @param aRealAddress Reference to an address string
        */
        virtual void AddAddresseeL(
            TMsvRecipientType aType,
            const TDesC& aRealAddress);
        
        /**
        * From CBaseMtm: Adds a typed addressee (To, Cc or Bcc )
        * @param aType recipient type (EMsvRecipientTo, EMsvRecipientCc,
        *     or EMsvRecipientBcc)
        * @param aRealAddress Reference to an address string
        * @param aAlias Reference to a descriptive name (not a real address)
        */
        virtual void AddAddresseeL(
            TMsvRecipientType aType,
            const TDesC& aRealAddress,
            const TDesC& aAlias);
        
        /**
        * From CBaseMtm: Removes an entry from addressee list.
        *     Cannot distinguish To, Cc and Bcc.
        * @param aIndex Index to the array of addresses.
        */
        void RemoveAddressee( TInt aIndex );

        // Note: rich text body not supported in MMS Message encapsulation.
        
        /**
        * From CBaseMtm Rich text body accessor
        * @return reference to the rich text body
        */
        inline CRichText& Body();

        /**
        * From CBaseMtm Rich text body accessor
        * @return reference to the rich text body
        */
        inline const CRichText& Body() const;

        /**
        * From CBaseMtm: Sets the message subject
        * @param aSubject Subject as text string.
        */
        void SetSubjectL( const TDesC& aSubject );
        
        /**
        * From CBaseMtm: Subject accessor
        * @return Constant pointer descriptor pointing to subject
        */
        const TPtrC SubjectL() const;

        // General MTM-specific functionality

        /**
        * From CBaseMtm:
        * @param aCapability Uid specifying which capablity is queried
        * @param aResponse reference to an integer that will contain the value
        *     describing the capability at return.
        * @return error code, KErrNone, if specified capability is known
        *     to Mtm,
        *     KErrNotSupported, if capability Uid is unknown
        */
        TInt QueryCapability( TUid aCapability, TInt& aResponse );

        /**
        * From CBaseMtm: Pass a function code to Server MTM, wait until the
        *     function returns. This function should be used to
        *     invoke synchronous protocol-specific operations.
        * @param aFunctionId An enumeration constant defining the operation
        *     to be performed.<br>
        *     (available function codes defined in MMSCONST.H)
        * @param aSelection Array of message entry ids to be operated on.<br>
        *     First must be a service id unless a default service for this
        *     MTM type has been defined.
        * @param aParameter Reference to a descriptor that contains any
        *     parameter required by function specified by aFunctionId.
        */
        void InvokeSyncFunctionL(
            TInt aFunctionId,
            const CMsvEntrySelection& aSelection,
            TDes8& aParameter );
        
        /**
        * From CBaseMtm: Pass a function code to Server MTM to invoke an
        *     asychronous function. This function should be used to
        *     invoke asynchronous protocol-specific operations.
        * @param aFunctionId An enumeration constant defining the operation
        *     to be performed (available function codes defined in MMSCONST.H)
        * @param aSelection Array of message entry id's to be uperated on.
        *     First must be a service id unless a default service for this
        *     MTM type has been defined.
        * @param aParameter Reference to a descriptor that contains any
        *     parameter required by function specified by aFunctionId.
        * @param aCompletionStatus Reference to the status
        *     of an active object.
        *     This status will be set as completed when the operation completes
        * @return Pointer to a message server operation (active object).
        *     If successful, this is an asynchronously completing
        *     operation.
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        CMsvOperation*  InvokeAsyncFunctionL(
            TInt aFunctionId,
            const CMsvEntrySelection& aSelection,
            TDes8& aParameter,
            TRequestStatus& aCompletionStatus );
        
        /**
        * From CBaseMtm: Return session that was set at initialization
        * @return Reference to session object
        */
        inline CMsvSession& Session();

        // Functions for SendAs support
        // These functions get the edit store from the current entry.
        // The caller should not hold the store open.
        // The store is committed and closed after each operation
        
        /**
        * From CBaseMtm Adds a file attachment to the current message entry.
        * The attachment is referenced by its file path and is copied into the
        *     message store. 
        * Only one asynchronous operation can be run at any one time.
        * @param aFilePath The full path specification of the attachment file.
        * @param aMimeType The mime type of the attachment file.
        * @param aCharset The character set in case the attachment is of text type
        *        if not relevant for current attachment type, set aCharset to 0
        * @param aStatus The request status to complete.
        * @leave System-wide error codes.
        */
        void AddAttachmentL( const TDesC& aFilePath,
            const TDesC8& aMimeType,
            TUint aCharset,
            TRequestStatus& aStatus );

        /**
        * From CBaseMtm Adds a file attachment to the current message entry.
        * The attachment is referenced by an open file handle and is copied
        *     into the message store. 
        * Only one asynchronous operation can be run at any one time.
        * @param aFile An open file handle for the file attachment.
        *        The function closes the file handle when done.
        *        The caller should not attempt to close the handle afterwards
        *        Use as follows:
        *        CleanupStack::CleanupClosePush( aFile );
        *        AddAttachmentL( aFile, ... );
        *        CleanupStack::Pop(); // get handle off cleanup stack
        * @param aMimeType The mime type of the attachment file.
        * @param aCharset The character set in case the attachment is of text type
        *        if not relevant for current attachment type, set aCharset to 0
        * @param aStatus The request status to complete.
        * @leave System-wide error codes.
        */
        void AddAttachmentL( RFile& aFile,
            const TDesC8& aMimeType,
            TUint aCharset,
            TRequestStatus& aStatus );
        
        /**
        * From CBaseMtm Adds a file attachment to the current message entry
        *     as a linked file.
        * The attachment is referenced by its file path and is not copied
        *     into the message store. The attachment file is always used from
        *     its original location on disk indicated by the aFilePath
        *     parameter. Only one asynchronous operation can be run at any
        *     one time.
        * @param aFilePath The full path specification of the attachment file.
        * @param aMimeType The mime type of the attachment file.
        * @param aCharset The character set in case the attachment is of text type
        *        if not relevant for current attachment type, set aCharset to 0
        * @param aStatus The request status to complete.
        * @leave System-wide error codes.
        */
        void AddLinkedAttachmentL( const TDesC& aFilePath,
            const TDesC8& aMimeType,
            TUint aCharset,
            TRequestStatus& aStatus );
        
        /**
        * From CBaseMtm Adds a message entry as an attachment to the current
        *     message entry.
        * Not supported. No Message attachments allowed in MMS.
        * @leave KErrNotSupported
        */
        void AddEntryAsAttachmentL( TMsvId aAttachmentId,
            TRequestStatus& aStatus );
        
        /**
        * From CBaseMtm
        * @param aFileName suggested filename
        * @param aAttachmentFile An open file handle for the file attachment.
        * @param aMimeType The mime type of the attachment file.
        * @param aCharset The character set in case the attachment is of text type
        *        if not relevant for current attachment type, set aCharset to 0
        * @param aStatus The request status to complete.
        * @leave System-wide error codes.
        */
        void CreateAttachmentL( const TDesC& aFileName,
            RFile& aAttachmentFile,
            const TDesC8& aMimeType,
            TUint aCharset,
            TRequestStatus& aStatus);

        /**
        * From CBaseMtm Cancels the current attachment operation.
        */
        void CancelAttachmentOperation();
        
        // End of attachment funtions to support SendAs

        /**
        * From CBaseMtm: Create an empty entry in the outbox<br>
        * and set it as current context.<br>
        * The entry will be invisible and under construction.
        * @param aServiceId Service id for the new entry.
        */
        void CreateMessageL( TMsvId aServiceId );
        
        /**
        * From CBaseMtm:BIO functions to support the SendAs API.
        * Entry().Entry().iBioType will be set by SendAs if this function does
        *    not leave.
        * The default implementation in CBaseMtm is to do nothing.
        */
        void BioTypeChangedL( TUid aBioTypeUid );
    
        /**
        * From CBaseMtm: Return id of default service.
        * Only one MMS service is supported.
        * @return default service
        */
        TMsvId DefaultServiceL() const;
        
        /**
        * From CBaseMtm: Remove default service
        * Does nothing. Deletion of service not supported
        */
        void RemoveDefaultServiceL();
        
        /**
        * From CBaseMtm: Change default service
        * Does nothing. Changing of default service not supported
        */
        void ChangeDefaultServiceL(const TMsvId& aService);

    protected:  // New functions

        /**
        * Lists all visible and free MMS Notifications from inbox. 
        * @return selection of Notifications in inbox.
        * @since 2.8
        */
        CMsvEntrySelection* ListNotificationsInInboxL();

    protected:  // Functions from base classes
        
        /**
        * From CBaseMtm: Called after the context of this instance
        * has been changed to another entry.
        */
        void ContextEntrySwitched();

        /**
        * From CBaseMtm: React to changes 
        * @param aEvent Code that tells which event has occurred.
        *     Event codes defined in MSVAPI.H
        * @param arg1 Depends on Event
        * @param arg2 Depends on Event
        * @param arg3 Depends on Event
        */
        void HandleEntryEventL(
            TMsvEntryEvent aEvent,
            TAny* arg1,
            TAny* arg2,
            TAny* arg3 );

        /**
        * By default Symbian OS constructor is private.
        * @param aRegisteredMtmDll Reference to Mtm Dll registry class
        * @param aSession Reference to a Message Server session.
        */
        CMmsClientMtm(
            CRegisteredMtmDll& aRegisteredMtmDll,
            CMsvSession& aSession );

        void ConstructL();
        
    private:

        /**
        * This method builds the iAddresseeList from the iMmsHeaders data.
        */
        void BuildAddresseeListL();

        /**
        * This methods adds entries from the the specified array to
        *     iAddresseeList.
        * @param aArray recipient array.
        */
        void BuildAddresseeListL(
            const CDesCArray& aArray, TMsvRecipientType aValue); 

        /**
        * Attachments size
        * @return size of all attachments, binary data + mime headers.
        */
        TInt32 AttachmentsSizeL();

        /**
        * List notifications in MMS folder.
        * @return selection of notifications
        */
        CMsvEntrySelection* ListMmsFolderNotificationsL();

        /**
        * List notifications in MMS folder - only for mode switch fetch.
        * @return selection of notifications
        */
        CMsvEntrySelection* ListInboxNotificationsL();

        /**
        * Fetch messages corresponding to unhandled notifications in ibox
        * This function is needed only when the fetching mode is changed        
        * @param aCompletionStatus iStatus member of an active object.
        *     It will be set as completed when the request has finished.
        * @aparam aForced indicates if the messages should be fetched
        *     regardless of current mode settings.
        *     ETrue = user initiated fetch, use override
        *     EFalse = event triggered fetch, fetch only if settings allow.
        * @return pointer to an operation active object.
        *     If successful, this is an asynchronously completing operation.
        *     If failed, this is a completed operation, with status set to
        *     the relevant error code.
        */
        CMsvOperation* FetchAllFromInboxL( TRequestStatus& aCompletionStatus,
            TBool aForced = ETrue );

        /**
        * Convert date time from UTC to local time.
        * @param aDate UTC date time
        * @return local time
        */
        // all times expressed in global time zone - no conversions
        /*
        TInt64 ConvertUTCDateToLocal( TInt64 aDate ) const;
        */

        /**
        * Find text from the given recipient list.
        * @param aTextToFind a text to be searched
        * @param aPartList message part list
        * @param aRecipients the recipient list
        * @param aFindText CMsvFindText object to help in the find
        * @return ETrue if match found.
        */
        TBool FindInRecipientL( 
            const TDesC& aTextToFind,
            TMsvPartList aPartlist,
            const CDesCArray& aRecipients,
            CMsvFindText& aFindText );
            
        /**
        * Add an attachment from public location either as copied file or
        *     linked file.
        * @param aFilePath The full path specification of the attachment file.
        * @param aMimeType The mime type of the attachment file.
        * @param aType CMsvAttachment::EMsvFile or
        *     CMsvAttachment::EMsvLinkedFile
        * @param aStatus The request status to complete when request has
        *     completed.
        * @param aCharacter set IANA MIBEnum of the character set for the
        *     attachment if needed.
        */
        void AddFilePathAttachmentL(const TDesC& aFilePath,
            const TDesC8& aMimeType,
            CMsvAttachment::TMsvAttachmentType aType,
            TRequestStatus& aStatus,
            const TUint aCharacterSet = 0 );
        
        /**
        * Store attribures to attribute stream in message entry
        * @param aStore message store
        */
        void StoreAttributesL( CMsvStore& aStore );
        
        /**
        * Restore attribures from attribute stream in message entry
        * @param aStore message store
        */
        void RestoreAttributesL( CMsvStore& aStore );
        
        /**
        * Checks whether given sample is UTF16 text.
        * @since    3.0
        * @param    aSample IN text sample
        * @return   1015 if the sample starts with unicode BOM
        *           (unicode with explicit byte mark) 
        *           0 otherwise
        */
        TUint GetUnicodeCharacterSet( TDesC8& aSample );
        
        /**
        * Reads bytes from so that sample is full or if file is shorter than
        *     sample then read whole file.
        * @since    3.0
        * @param    aFile       IN open file handle to read bytes from
        * @param    aSample     OUT sample buffer
        */
        void ReadBytesFromFileL( const RFile aFile, TDes8& aSample );
        
        /**
        * Tries to recognize character set from given sample. 
        * @since    3.0
        * @param    aFile       IN File to be recognized
        * @return   CharConv id of the character set
        */
        TUint RecognizeCharSetL( RFile& aFile );
        
        /**
        * Convert Symbian charset UID to IANA MIBEnum
        * @since    3.0
        * @param    aCharconvCharsetId  IN charconv id
        * @return   MIB enumeration
        */
        TUint CharconvIdToMibIdL( TUint aCharconvCharsetId );


    public:     // Data
    
    protected:  // Data
        CMmsSettings* iMmsSettings;  // MMSC settings (access point etc.)
        
        CMmsHeaders*  iMmsHeaders;   // MMS message headers        
        TMsvId        iServiceId;    // last selected service
        HBufC*        iAddressOpen;  // address separator begin characters
        HBufC*        iAddressClose; // address separator close characters 
        TBool         iFetchAll;     // All the messages are fetched when
                                     // settings are saved after certain fetch
                                     // mode change.
        TBool         iFetchOverride; // force fetching all messages.
        TInt          iMessageDrive; // messages are on C: drive by default,
                                     // may be moved to other drive
        TInt32        iHomeMode;     // receiving mode in the home network
        TInt32        iRoamingMode;  // receiving mode when roaming
        TInt          iAccessPointCount; // number of access points
        CDesCArrayFlat* iAttributes;     // zero or more attributes for UI.
                                         // Name, value pairs
    	CMsvSession& iOwnSession;    // copy of session because base class session is private

        
    private:    // Data
        // active object that commits the store when attachment operation
        // is complete
        CMmsAttachmentWaiter* iAttaWaiter;

    public:     // Friend classes

    protected:  // Friend classes

    private:    // Friend classes

    };

// panic function 
GLREF_C void gPanic( TMmsPanic aPanic );

#include "mmsclient.inl"

// MMSCLIENT_H   
#endif
            
// End of File

