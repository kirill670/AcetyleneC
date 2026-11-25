// IMAPSET.H
//
// Copyright (c) 1998-2003 Symbian Ltd.  All rights reserved. 
//

#ifndef __IMAPSET_H__
#define __IMAPSET_H__

#include <msvuids.h>
#include "miutset.h"


/** Settings stream version. */
const TUint16 KImImapSettingsVersion = 5;

/** Default IMAP4 server port number. */
const TUint32 KIMAPDefaultPortNumber = 143;

/** Default inbox refresh rate in seconds. */
const TInt KImapDefaultInboxSyncRate = 300;

/** Default fetch size in bytes. */
const TUint KImapDefaultFetchSizeBytes = 20480;

/** @deprecated */
const TInt32 KImImapSynchroniseAll = -1;

/** @deprecated */
const TInt32 KImImapSynchroniseNone	= 0;


class CMsvStore;
class RMsvWriteStream;
class RMsvReadStream;


/** 
Specifies how the client synchronises its folders with the IMAP4 server. 

@see
CImImap4Settings

@publishedAll
@released
*/
enum TFolderSyncType
	{
	/** Merge local and remote folder information. */
	EUseCombination=0,
	/** Update the local copy of folder information when it is received from remote 
	IMAP4 server at the beginning of the mail session. */
	EUseLocal,
	/** Update the remote copy of folder information so that it matches the local folder 
	information. */
	EUseRemote
	};


/**
Specifies methods of synchronising IMAP4 subscription information with a server. 

@see
CImImap4Settings

@publishedAll
@released
*/
enum TFolderSubscribeType
	{
	/** Do not alter local or remote subscription information. */
	EUpdateNeither=0,
	/** Update local copy of subscription information when it is received from the 
	remote IMAP4 server at the beginning of the mail session. */
	EUpdateLocal,
	/** Update remote copy of subscription information so that it matches the local 
	subscription information. */
	EUpdateRemote,
	/** Merge local and remote subscription information, store updated information 
	on the remote server and store merged data on the local server. */
	EUpdateBoth
	};


/**
Defines which components of a message to fetch when copying or moving from
a server. 

@see
CImImap4Settings

@publishedAll
@released
*/
enum TImap4GetMailOptions
	{
	/** Get message headers. */
	EGetImap4EmailHeaders,
	/** Get message body. */
	EGetImap4EmailBodyText,
	/** Get message body and attachments. */
	EGetImap4EmailBodyTextAndAttachments,
	/** Get message attachments. */
	EGetImap4EmailAttachments
	};


/**
Flags to indicate what type of IMAP4 progress information is being returned. 

@publishedAll
@released
*/
enum TImap4ProgressType
	{
	/** Progress information is an TImap4GenericProgress object. */
	EImap4GenericProgressType,
	/** Progress information is an TImap4SyncProgress object. */
	EImap4SyncProgressType
	};


class TImap4GenericProgress
/**
Progress information for an IMAP4 get operation.

For the 'get mail when already connected' operations, the progress state can 
be obtained from TImap4GenericProgress::iState. In the case of the 'connect 
and get mail and disconnect' and 'connect and get mail and stay online', the 
actual progress defined in TImap4GenericProgress::iState will be of the form 
of 'Copy New Mail', 'Populating Message Selection' etc. The sub-operation 
state can then be obtained in the form of 'Connecting', 'Fetching', 'Disconnecting' 
etc. from TImap4GenericProgress::iImap4SubStateProgress.

@see
CImImap4GetMail 

@publishedAll
@released
*/
	{
public:
	IMPORT_C TInt ConnectionState() const;
	IMPORT_C TInt ConnectionIAP() const;

public:
	/** Operation type. */
	enum TImap4GenericProgressOp
		{
	/** Connect operation. */
		EConnect,
	/** Disconnect operation. */
		EDisconnect, 
	/** Sync operation. */
		ESync,
	/** Select operation. */
		ESelect,		
	/** Copy messages to local operation. */
		ECopyToLocal,
	/** Copy messages within remote server operation. */
		ECopyWithinService,
	/** Copy messages from local operation. */
		ECopyFromLocal,
	/** Move messages to local operation. */
		EMoveToLocal,
	/** Move messages within remote server operation. */
		EMoveWithinService,
	/** Move messages from local operation. */
		EMoveFromLocal,
	/** Message population operation. */
		EPopulate,		
	/** Delete operation. */
		EDelete,		
	/** Offline delete operation. */
		EOffLineDelete,
	/** Offline undelete operation. */
		EOffLineUndelete,
	/** Offline delete operation. */
		EOffLineCopyToLocal,
	/** Offline move messages to local operation. */
		EOffLineMoveToLocal,
	/** Offline copy messages from local operation. */
		EOffLineCopyFromLocal,
	/** Offline move messages from local operation. */
		EOffLineMoveFromLocal,
	/** Offline copy messages within remote server operation. */
		EOffLineCopyWithinService,
	/** Offline move messages within remote server operation. */
		EOffLineMoveWithinService,
	/** Offline message population operation. */
		EOffLinePopulate
		};

	/** Operation state information. */
	enum TImap4GenericProgressState
		{
	/** Disconnected. */
		EDisconnected,
	/** Connecting. */
		EConnecting,
	/** Idle. */
		EIdle,
	/** Selecting the folder to use. */
		ESelecting,
	/** Fetching messages to mirror server. */
		EFetching,
	/** Appending local messages to remote server. */
		EAppending,
	/** Copying local messages to local or within service. */
		ECopying,
	/** Deleting an item, including expunging a folder. */
		EDeleting,
	/** Synchronising folder after an operation. */
		ESyncing,
	/** Disconnecting. */
		EDisconnecting,
	/** Sync already in progress. */
		EBusy,
	/** CImImap4GetMail move operation in progress. */
		EMoving,
	/** CImImap4GetMail copy new mail operation in progress. */
		ECopyNewMail,
	/** CImImap4GetMail move new mail operation in progress. */
		EMoveNewMail,
	/** CImImap4GetMail copy selected messages operation in progress. */
		ECopyMailSelection,
	/** CImImap4GetMail move selected messages operation in progress. */
		EMoveMailSelection,
	/** CImImap4GetMail copy all messages operation in progress. */
		ECopyAllMail,
	/** CImImap4GetMail move all messages operation in progress. */
		EMoveAllMail,
	/** CImImap4GetMail populate new messages operation in progress. */
		EPopulateNewMail,
	/** CImImap4GetMail populate all messages operation in progress. */
		EPopulateAllMail,
	/** CImImap4GetMail populate selected messages operation in progress. */
		EPopulateMailSelection
		};

	/** Progress information type: always EImap4GenericProgressType. */
	TImap4ProgressType iType;
	/** Operation type. */
	TImap4GenericProgressOp iOperation;
	/** 
	The progress state.
	
	For 'connect and get mail and disconnect' and 'connect and get mail and stay 
	online' type operations, additional sub-operation state can be obtained from 
	iImap4SubStateProgress.
	*/
	TImap4GenericProgressState iState; 
	/** 
	The progress sub-state.
	
	This only applies to 'connect and get mail and disconnect' and 'connect and 
	get mail and stay online' type operations.
	*/
	TImap4GenericProgressState iImap4SubStateProgress;
	/** In the EConnecting state, this field holds the connection iap value, 
	otherwise it holds the number of messages still to be processed. */
	TInt		iMsgsToDo;
	/** In the EConnecting state, this field holds the connection stage value, 
	otherwise it holds the number of messages processed. */
	TInt		iMsgsDone;
	/** Number of message parts still to be processed. */
	TInt		iPartsToDo;
	/** Number of message parts processed. */
	TInt		iPartsDone;
	/** Number of bytes (for a multipart fetch) still to be processed. */
	TInt		iBytesToDo;
	/** Number of bytes (for a multipart fetch) processed. */
	TInt		iBytesDone;
	/** Error code. */
	TInt		iErrorCode;
	/** Message ID returned from the operation. */
	TMsvId		iReturnedMsvId;
	/** The total size of messages to be downloaded. */
	TInt		iTotalSize;
	};


class TImap4SyncProgress
/**
IMAP4 synchronisation progress information. 

The client may then use an object of this type created by the server MTM to 
track synchronisation progress.

@publishedAll
@released
*/
	{
public:
	/** Synchronisation state. */
	enum TImap4SyncProgressState
		{
	/** Idle. */
		EIdle,
	/** Busy. */
		EBusy,
	/** Connecting. */
		EConnecting,
	/** Disconnecting. */
		EDisconnecting,
	/** Synchronising inbox. */
		ESyncInbox,
	/** Synchronising folder tree. */
		ESyncFolderTree,
	/** Checking remote subscription. */
		ECheckRemoteSubscription,
	/** Updating remote subscription. */
		EUpdateRemoteSubscription,
	/** Synchronising other information. */
		ESyncOther,
	/** Deleting. */
		EDeleting,
	/** Processing pending operations. */
		EProcessingPendingOps
		};

	/** Progress information type: i.e. synchronisation information. */
	TImap4ProgressType iType;		//	will always be EImapSyncProgressType
	/** Synchronisation state. */
	TImap4SyncProgressState iState;	//	Where is the sync up to?
	/** 
	Folders to do count for synchronisation. 
	This is meaningful during ESyncOther and EDeleting.
	*/
	TInt		iFoldersToDo;
	/**
	Folders done count for synchronisation. 
	This is meaningful during ESyncOther and EDeleting.
	*/
	TInt		iFoldersDone;
	/** 
	Message to do count for synchronisation.
	This is meaningful during ESyncInbox, ESyncOther and EProcessingPendingOps.
	*/
	TInt		iMsgsToDo;
	/**
	Message done count for synchronisation.
	This is meaningful during ESyncInbox, ESyncOther and EProcessingPendingOps.
	*/
	TInt		iMsgsDone;
	/**
	Number of headers fetched during synchronisation.
	*/
	TInt		iHeadersFetched;
	/**
	Number of folders orphaned during synchronisation.
	*/
	TInt		iOrphanedFolders;
	/**
	Number of new folders during synchronisation.
	*/
	TInt		iNewFolders;
	/**
	Number of orphaned messages during synchronisation.
	*/
	TInt		iOrphanedMessages;
	/**
	Number of remote messages tagged for deletion.
	*/
	TInt		iRemoteMessagesDeleteTagged;
	/** Number of messages fetched during synchronisation. */
	TInt		iMessagesFetchedOK;
	/** Number of message parts fetched during synchronisation. */
	TInt		iMessagePartsFetchedOK;
	/** Number of message parts not found during synchronisation. */
	TInt		iMessagePartsNotFound;
	/** Number of folders not found during synchronisation. */
	TInt		iFoldersNotFound;
	/** Any error-code that the client needs to be informed of. */
	TInt		iErrorCode;
	};

class TImap4CompoundProgress
/**
IMAP operation progress information.

The class supplies both the two IMAP progress types, generic and synchronisation.

The IMAP4 server MTM owns two IMAP4 sessions that are used independently of 
each other to perform 'background' and 'foreground' operations. In a typical 
situation, the user may be downloading the body parts of a message (populating) 
in the foreground whilst in the background a full synchronisation may be underway. 
In this scenario, the generic progress will give an indication of the 'foreground' 
activity and the synchronisation progress will give an indication of the 'background' 
progress. The synchronisation progress component of the compound progress 
will always show the synchronisation progress irrespective of whether the 
synchronisation is running in the foreground or the background. 

@publishedAll
@released
*/
	{
public:
	/** Generic progress. */
	TImap4GenericProgress	iGenericProgress;
	/** Synchronisation progress. */
	TImap4SyncProgress		iSyncProgress;
	};


class CImImap4Settings : public CImBaseEmailSettings
/**
Run-time configuration settings for IMAP4.

Messaging clients should use an instance of this class to specify
and retrieve configuration settings that are used by the IMAP4 service when
executing email operations.

Service settings such as the user name and password, synchronisation strategy,
and the maximum number of messages to synchronise are all specified in this object.
Storing and restoring from the message store is also supported.

To use this class to change a setting:
1) Set the current context to the IMAP4 service entry using CMsvStore.
2) Create an instance of CImImap4Settings and put it on the cleanup stack.
3) Retrieve the existing settings by calling CImImap4Settings::RestoreL().
4) Change the login user name by calling CImImap4Settings::SetLoginNameL().
5) Save the new settings by calling CImImap4Settings::StoreL().
6) Pop and destroy the CImImap4Settings instance.

@see CMsvStore

@publishedAll
@released
*/
	{
public:
	IMPORT_C CImImap4Settings();
	IMPORT_C virtual ~CImImap4Settings();
	IMPORT_C void Reset();
	IMPORT_C void InternalizeL(RMsvReadStream& aWriteStream);
	IMPORT_C void ExternalizeL(RMsvWriteStream& aReadStream) const;
	IMPORT_C void RestoreL(CMsvStore& aMessageStore);
	IMPORT_C void StoreL(CMsvStore& aMessageStore) const;
	IMPORT_C const TPtrC8 LoginName() const;
	IMPORT_C void SetLoginNameL(const TDesC8& aLoginName);
	IMPORT_C const TPtrC8 Password() const;
	IMPORT_C void SetPasswordL(const TDesC8& aPassword);
	IMPORT_C const TPtrC8 FolderPath() const;
	IMPORT_C void SetFolderPathL(const TDesC8& aFolderPath);
	IMPORT_C const TText8 PathSeparator() const;
	IMPORT_C void SetPathSeparator(const TText8 aPathSeparator);
	IMPORT_C const TBool DisconnectedUserMode() const;
	IMPORT_C void SetDisconnectedUserMode(TBool aFlag);
	IMPORT_C void SetSynchronise(const TFolderSyncType aType);
	IMPORT_C const TFolderSyncType Synchronise() const;
	IMPORT_C void SetSubscribe(const TFolderSubscribeType aType);
	IMPORT_C const TFolderSubscribeType Subscribe() const;
	IMPORT_C const TBool AutoSendOnConnect() const;
	IMPORT_C void SetAutoSendOnConnect(TBool aFlag);
	IMPORT_C const TUint MaxEmailSize() const;
	IMPORT_C void SetMaxEmailSize(const TUint aMaxEmailSize);
	IMPORT_C const TBool DeleteEmailsWhenDisconnecting() const;
	IMPORT_C void SetDeleteEmailsWhenDisconnecting(TBool aFlag);
	IMPORT_C const TBool AcknowledgeReceipts() const;
	IMPORT_C void SetAcknowledgeReceipts(TBool aFlag);
	IMPORT_C const TImap4GetMailOptions GetMailOptions() const;
	IMPORT_C void SetGetMailOptions(TImap4GetMailOptions aGetMailOptions);
	IMPORT_C CImImap4Settings& CopyL(const CImImap4Settings& aCImImap4Settings);
	IMPORT_C TBool operator==(const CImImap4Settings& aCImImap4Settings) const;
	IMPORT_C const TInt32 InboxSynchronisationLimit() const;
	IMPORT_C void SetInboxSynchronisationLimit(const TInt32 aInboxSyncLimit);
	IMPORT_C const TInt32 MailboxSynchronisationLimit() const;
	IMPORT_C void SetMailboxSynchronisationLimit(const TInt32 aMailboxSyncLimit);
	IMPORT_C const TBool UpdatingSeenFlags() const;
	IMPORT_C void SetUpdatingSeenFlags(TBool aFlag);
	IMPORT_C const TInt SyncRate() const;
	IMPORT_C void SetSyncRateL(TInt aSyncRate);
	IMPORT_C TUint FetchSize() const;
	IMPORT_C void SetFetchSizeL(TUint aFetchSizeBytes);

private:
	class TImImap4SettingsExtension
		{
	public:
		inline TImImap4SettingsExtension();
	public:
		HBufC8* iLoginName;
		HBufC8* iPassword;
		HBufC8* iFolderPath;
		TInt	iSyncRate;
		TUint	iFetchSizeBytes;
		};
	
	inline TImImap4SettingsExtension* Extension() const;
	inline void CheckExtensionExistsL();

	enum TImImap4EmailSettings
		{
		KImap4EmailSettingsClearFlag				= 0x00000000,
		KImap4BaseEmailSettingsLastUsedFlag			= CImBaseEmailSettings::EBaseEmailSettingsLastUsedFlag,
		KImap4EmailDisconnectedModeFlag				= KImap4BaseEmailSettingsLastUsedFlag << 1,
		KImap4EmailAutoSendFlag						= KImap4EmailDisconnectedModeFlag << 1,
		KImap4EmailDeleteEmailsWhenDisconnecting	= KImap4EmailAutoSendFlag << 1,
		KImap4EmailAcknowledgeReceipts				= KImap4EmailDeleteEmailsWhenDisconnecting << 1,
		KImap4EmailUpdatingSeenFlags				= KImap4EmailAcknowledgeReceipts << 1,
		KImap4EmailSettingsLastUsedFlag				= KImap4EmailUpdatingSeenFlags
		};

	TImImap4SettingsExtension*	iExtension; // renamed iReceiptAddress

	TInt32  iInboxSyncLimit;
	TInt32  iMailboxSyncLimit;

	TText8  iPathSeparator;
	TFolderSyncType iSynchroniseStrategy;
	TFolderSubscribeType iSubscriptionStrategy;
	TUint32	iMaxEmailSize;
	TImap4GetMailOptions iGetMailOptions;
	};


class TImImap4GetMailInfo
/**
Specifies message criteria that are used as a filter when retrieving messages.

Options include the maximum message size, the destination folder ID, and what 
message parts are required. 

@see
CImImap4GetMail

@publishedAll
@released
*/
	{
public:
	/** The maximum message size. */
	TInt32					iMaxEmailSize;
	/** The required message parts. */
	TImap4GetMailOptions	iGetMailBodyParts;
	/** The destination folder ID. */
	TMsvId					iDestinationFolder;
	};

inline CImImap4Settings::TImImap4SettingsExtension* CImImap4Settings::Extension() const
	{
	return iExtension;
	}

inline void CImImap4Settings::CheckExtensionExistsL()
	{
	if (!iExtension)
		iExtension=new (ELeave) CImImap4Settings::TImImap4SettingsExtension;
	}

inline CImImap4Settings::TImImap4SettingsExtension::TImImap4SettingsExtension() 
: iLoginName(NULL) ,iPassword(NULL) ,iFolderPath(NULL), iSyncRate(KImapDefaultInboxSyncRate), iFetchSizeBytes(KImapDefaultFetchSizeBytes)
	{
	}


#endif // __IMAPSET_H__