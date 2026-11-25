// SMTPSET.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined (__SMTPSET_H__)
#define __SMTPSET_H__

#if !defined (__MSVUIDS_H__)
#include <MSVUIDS.H>
#endif

#include "miutset.h"

class CMsvStore;
class RMsvWriteStream;
class RMsvReadStream;


const TUint16 KImSmtpClientSettingsVersion = 2;	// identify which version of this class has been stored
const TUint32 KSMTPDefaultPortNumber = 25;

enum TImSMTPSendCopyToSelf
	{
	ESendNoCopy,
	ESendCopyAsToRecipient,
	ESendCopyAsCcRecipient,
	ESendCopyAsBccRecipient
	};

enum TImSMTPSendMessageOption
	{
	ESendMessageImmediately,
	ESendMessageOnNextConnection,
	ESendMessageOnRequest
	};

//
//  TMsgImOutpoxSendState
//
enum TMsgImOutboxSendState
	{
	EMsgOutboxProgressWaiting,
	EMsgOutboxProgressConnecting,
	EMsgOutboxProgressSending,
	EMsgOutboxProgressDone
	};

//
//  TSmtpSessionState
//
enum TSmtpSessionState
	{
	EConnectingToSmtp,
	EWaitingForReply,
	EAuthorisingSmtp,
	ESendingStarttls,  //send 'STARTTLS'
	ESettingSecurity,  //set security in IMSK and send 'NOOP' ESendingImail,
	ESendingImail,
	ELogDataEvent,
	EClosingSmtp
	};

//
//  TImImailFileProgress
//
class TImImailFileProgress				
	{
public:
	TInt				iBytesSent;
	TInt				iBytesToSend;
	TSmtpSessionState	iSessionState;
	};

//
//  TImStmpProgress
//
class TImSmtpProgress
	{

public:
	IMPORT_C TMsgImOutboxSendState	Status() const;			    // Progress: current progress status of mail session
	IMPORT_C TInt						MsgNo() const;		    // Progress: No. of message currently being sent; zero=1st message

	IMPORT_C TInt						Error() const;			// Summary: completion code from end of last session
	IMPORT_C TInt						Sent() const;			// Summary: No. messages sent successfully
	IMPORT_C TInt						NotSent() const;		// Summary: No. messages I didn't attempt to send
	IMPORT_C TInt						FailedToSend() const;	// Summary: No. messages attempted to send but failed
	IMPORT_C TInt						SendTotal() const;		// Sent() + NotSent() + FailedToSend() = SendTotal()

	IMPORT_C void						SetError(TInt anError);
	IMPORT_C void						SetStatus(TMsgImOutboxSendState aStatus);
	IMPORT_C void						SetMsgNo(TInt aMsgNo);
	IMPORT_C void						InitialiseTotal(const TInt& aTotal);

	IMPORT_C void						UpdateSent();
	IMPORT_C void						UpdateFailedToSend();
	IMPORT_C void						DecrementSendTotal();
	IMPORT_C TMsvId						ServiceId() const;
	IMPORT_C void						SetServiceId(TMsvId aServiceId);


// data
public:
	TImImailFileProgress			iSendFileProgress;

private:
	TMsgImOutboxSendState	iStatus;
	TInt					iError;
	TInt					iMsgNo;
	TInt					iSent;
	TInt					iNotSent;
	TInt					iFailedToSend;
	TInt					iSendTotal;
	TMsvId					iServiceId;
	};

class CImSmtpSettings : public CImBaseEmailSettings
	{
public:
	IMPORT_C CImSmtpSettings();
	IMPORT_C ~CImSmtpSettings();
	IMPORT_C void Reset();

	// streaming operations
	IMPORT_C void InternalizeL(RMsvReadStream& aWriteStream);
	IMPORT_C void ExternalizeL(RMsvWriteStream& aReadStream) const;
	IMPORT_C void RestoreL(CMsvStore& aMessageStore);
	IMPORT_C void StoreL  (CMsvStore& aMessageStore) const;

	// EmailAlias - eg John Smith
	IMPORT_C const TPtrC EmailAlias() const;
	IMPORT_C void SetEmailAliasL(const TDesC& aEmailAlias);

	// EmailAddress eg name@address.com
	IMPORT_C const TPtrC EmailAddress() const;
	IMPORT_C void SetEmailAddressL(const TDesC& aEmailAddress);

	// ReplyToAddress eg replyname@address.com
	IMPORT_C const TPtrC ReplyToAddress() const;
	IMPORT_C void SetReplyToAddressL(const TDesC& aReplyToAddress);

	// Address for receipt eg name@address.com
	IMPORT_C const TPtrC ReceiptAddress() const;
	IMPORT_C void SetReceiptAddressL(const TDesC& aReceiptAddress);
	
	// BodyEncoding
	IMPORT_C const TMsgOutboxBodyEncoding BodyEncoding() const;
	IMPORT_C void SetBodyEncoding(TMsgOutboxBodyEncoding aBodyEncoding);
	IMPORT_C const TUid DefaultMsgCharSet() const;
	IMPORT_C void SetDefaultMsgCharSet(TUid aDefaultMsgCharSet);

	// Add VCard to Email or not
	IMPORT_C const TBool AddVCardToEmail() const;
	IMPORT_C void SetAddVCardToEmail(TBool aFlag);

	// Add Signature to Email or not
	IMPORT_C const TBool AddSignatureToEmail() const;
	IMPORT_C void SetAddSignatureToEmail(TBool aFlag);

	// Request Receipts or not
	IMPORT_C const TBool RequestReceipts() const;
	IMPORT_C void SetRequestReceipts(TBool aFlag);

	// Send a copy of the message to yourself
	IMPORT_C const TImSMTPSendCopyToSelf SendCopyToSelf() const;
	IMPORT_C void SetSendCopyToSelf(TImSMTPSendCopyToSelf aSendCopyToSelf);

	// Send message immediately, on request etc.
	IMPORT_C const TImSMTPSendMessageOption SendMessageOption() const;
	IMPORT_C void SetSendMessageOption(TImSMTPSendMessageOption aSendMessageOption);

	IMPORT_C CImSmtpSettings& CopyL(const CImSmtpSettings& aCImSmtpSettings);
	IMPORT_C TBool operator==(const CImSmtpSettings& aCImSmtpSettings) const;

private:
	enum TImSMTPEmailSettings
		{
		KSmtpSettingsClearFlag				= 0x00000000,
		KSmtpBaseEmailSettingsLastUsedFlag	= CImBaseEmailSettings::EBaseEmailSettingsLastUsedFlag,	//0x00000001
		KSmtpAddVCardToEmailFlag			= KSmtpBaseEmailSettingsLastUsedFlag << 1,	//0x00000002
		KSmtpAddSignatureToEmailFlag		= KSmtpAddVCardToEmailFlag << 1,			//0x00000004
		KSmtpRequestReceipts				= KSmtpAddSignatureToEmailFlag << 1,		//0x00000008
		KSmtpEmailSettingsLastUsedFlag		= KSmtpRequestReceipts						//0x00000008
		};

	HBufC*						iEmailAlias;
	HBufC*						iEmailAddress;
	HBufC*						iReplyToAddress;
	HBufC*						iReceiptAddress;
	TMsgOutboxBodyEncoding		iBodyEncoding;
	TUid						iDefaultMsgCharSet;
	TImSMTPSendCopyToSelf		iSendCopyToSelf;
	TImSMTPSendMessageOption	iSendMessageOption;
	};

#endif    // #define __SMTPSET_H__
