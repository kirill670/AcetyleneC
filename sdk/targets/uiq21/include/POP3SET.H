// POP3SET.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined (__POP3SET_H__)
#define __POP3SET_H__

#if !defined (__MSVUIDS_H__)
#include <MSVUIDS.H>
#endif
#if !defined(__MIUTSET_H__)
#include "miutset.h"
#endif
#if !defined(__MIUT_ERR_H__)
#include "miut_err.h"
#endif

const TUint16 KImPop3SettingsVersion = 3;	// identify which version of this class has been stored
const TUint32 KPOP3DefaultPortNumber = 110;

const TInt32 KImPop3SynchroniseAll	 = -1;	// negative values of sync limit mean "sync all"
const TInt32 KImPop3SynchroniseNone	 = 0;	// zero values of sync limit mean "do not sync"
											// positive vales of sync limit mean "sync N most recent messages"
enum TPop3GetMailOptions
	{
	EGetPop3EmailHeaders,
	EGetPop3EmailMessages
	};			   

class TPop3Progress
	{
public:
	enum TPop3ProgressType 
		{
		EPopRefreshing,
		EPopCopying,
		EPopDeleting,
		EPopConnecting,
		EPopTidying,
		EPopConnectedAndIdle,
		EPopDisconnecting,
		EPopDisconnected,
		EPopMoving,
		EPopCopyNewMail,
		EPopMoveNewMail,
		EPopCopyMailSelection,
		EPopMoveMailSelection,
		EPopCopyAllMail,
		EPopMoveAllMail,
		EPopPopulating,
		EPopCancellingOfflineOps,
		EPopMaxProgressValue=EPopCancellingOfflineOps
		};

	TPop3ProgressType	iPop3Progress;	// holds the progress for a 'super operation'
	TInt				iTotalMsgs;
	TInt				iMsgsToProcess;
	TInt				iBytesDone;
	TInt				iTotalBytes;
	TInt				iErrorCode; // client side needs to be informed of an error
	TPop3ProgressType	iPop3SubStateProgress; // holds the progress for the substate of the 'super operation'
	TMsvId				iServiceId;
	TInt				iTotalSize; // The total size of messages to be downloaded.
	};

class TImPop3GetMailInfo
	{
public:
	TInt32		iMaxEmailSize;			// only need to get mail if iMaxEmailSize < KMaxTUint
	TMsvId		iDestinationFolder;		// specifies the destination folder for get mail
	};

class CImPop3Settings : public CImBaseEmailSettings
	{
public:
	IMPORT_C CImPop3Settings();
	IMPORT_C ~CImPop3Settings();
	IMPORT_C void Reset();

	// streaming operations
	IMPORT_C void InternalizeL(RMsvReadStream&);
	IMPORT_C void ExternalizeL(RMsvWriteStream&) const;
	IMPORT_C void RestoreL(CMsvStore& aMessageStore);
	IMPORT_C void StoreL  (CMsvStore& aMessageStore) const;

	// User name
	IMPORT_C const TPtrC8 LoginName() const;
	IMPORT_C void SetLoginNameL(const TDesC8&);

	// Password
	IMPORT_C const TPtrC8 Password() const;
	IMPORT_C void SetPasswordL(const TDesC8&);

	// Autosend on connection or not
	IMPORT_C const TBool AutoSendOnConnect() const;
	IMPORT_C void SetAutoSendOnConnect(TBool aFlag);

	// APOP connection or not
	IMPORT_C const TBool Apop() const;
	IMPORT_C void SetApop(TBool aFlag);

	// In Disconnected Mode or not
	IMPORT_C const TBool DisconnectedUserMode() const;
	IMPORT_C void SetDisconnectedUserMode(TBool aFlag);

	// Delete emails when disconnecting or not
	IMPORT_C const TBool DeleteEmailsWhenDisconnecting() const;
	IMPORT_C void SetDeleteEmailsWhenDisconnecting(TBool aFlag);

	// Acknowledge Receipts or not
	IMPORT_C const TBool AcknowledgeReceipts() const;
	IMPORT_C void SetAcknowledgeReceipts(TBool aFlag);

	IMPORT_C const TInt MaxEmailSize() const;
	IMPORT_C void SetMaxEmailSize(const TInt aMaxEmailSize);

	// Get Mail options
	IMPORT_C const TPop3GetMailOptions GetMailOptions() const;
	IMPORT_C void SetGetMailOptions(TPop3GetMailOptions aGetMailOptions);

	// Inbox synchronisation limit
	IMPORT_C const TInt32 InboxSynchronisationLimit() const;
	IMPORT_C void SetInboxSynchronisationLimit(const TInt32 aInboxSyncLimit);

	// Copy and Equality constructors
	IMPORT_C CImPop3Settings& CopyL(const CImPop3Settings& aCImPop3Settings);
	IMPORT_C TBool operator==(const CImPop3Settings& aCImPop3Settings) const;

private:
	enum TImPop3EmailSettings
		{
		KPop3SettingsClearFlag					= 0x00000000,
		KPop3BaseEmailSettingsLastUsedFlag		= CImBaseEmailSettings::EBaseEmailSettingsLastUsedFlag,	//0x00000001
		KPop3ApopFlag							= KPop3BaseEmailSettingsLastUsedFlag << 1,		//0x00000002
		KPop3AutoSendFlag						= KPop3ApopFlag << 1,							//0x00000004
		KPop3DisconnectedModeFlag				= KPop3AutoSendFlag << 1,						//0x00000008
		KPop3DeleteEmailsWhenDisconnectingFlag	= KPop3DisconnectedModeFlag << 1,				//0x00000010
		KPop3AcknowledgeReceipts				= KPop3DeleteEmailsWhenDisconnectingFlag << 1,	//0x00000020
		KPop3EmailSettingsLastUsedFlag			= KPop3AcknowledgeReceipts						//0x00000020
		};

	HBufC8* iLoginName;
	HBufC8* iPassword;
	TInt32	iMaxEmailSize;
	TPop3GetMailOptions iGetMailOptions;
	TInt32  iInboxSyncLimit;
	};

#endif // #define __POP3SET_H__
