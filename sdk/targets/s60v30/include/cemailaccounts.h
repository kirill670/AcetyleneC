//	CEMAILACCOUNTS.H
//
//	Copyright (c) 2004-2005 Symbian Software Ltd. All rights reserved.
//

#ifndef __CEMAILACCOUNTS_H__
#define __CEMAILACCOUNTS_H__


#include <e32std.h>
#include <e32base.h>
#include <msvapi.h>


class CImIAPPreferences;
class CImPop3Settings;
class CImImap4Settings;
class CImSmtpSettings;
class CRepository;

/**
Maximum size of email account name

@publishedAll
@released
*/
const TInt KEmailAccountNameSize = 256;

typedef TInt TPopAccountId;
typedef TInt TImapAccountId;
typedef TInt TSmtpAccountId;

/**
POP account ID

@publishedAll
@released
*/
class TPopAccount
	{
public:
	/** POP account Id */
	TPopAccountId iPopAccountId;

	/** POP account Name */
	TBuf<KEmailAccountNameSize> iPopAccountName;

	/** POP service */
	TMsvId iPopService;

	/** Related SMTP service */
	TMsvId iSmtpService;
	};

/**
IMAP account ID

@publishedAll
@released
*/
class TImapAccount
	{
public:
	/** IMAP account Id */
	TImapAccountId iImapAccountId;

	/** IMAP account Name */
	TBuf<KEmailAccountNameSize> iImapAccountName;

	/** IMAP service */
	TMsvId iImapService;

	/** Related SMTP service */
	TMsvId iSmtpService;
	};

/**
SMTP account ID

@publishedAll
@released
*/
class TSmtpAccount
	{
public:
	/** SMTP account Id */
	TSmtpAccountId iSmtpAccountId;

	/** SMTP account Name */
	TBuf<KEmailAccountNameSize> iSmtpAccountName;

	/** SMTP service */
	TMsvId iSmtpService;

	/** Related POP/IMAP service */
	TMsvId iRelatedService;
	};


/**
Creates, loads, saves and deletes email accounts. 

@publishedAll
@released
*/
class CEmailAccounts : public CBase, public MMsvSessionObserver
	{
public:

	IMPORT_C static CEmailAccounts* NewL();
	IMPORT_C static CEmailAccounts* NewLC();
	IMPORT_C virtual ~CEmailAccounts();

	IMPORT_C TPopAccount CreatePopAccountL(const TDesC& aAccountName, const CImPop3Settings& aPopSettings,
		const CImIAPPreferences& aPopIAP, TBool aReadOnly);

	IMPORT_C TImapAccount CreateImapAccountL(const TDesC& aAccountName, const CImImap4Settings& aImapSettings,
		const CImIAPPreferences& aImapIAP, TBool aReadOnly);

	IMPORT_C TSmtpAccount CreateSmtpAccountL(TPopAccount& aPopAccount, const CImSmtpSettings& aSmtpSettings,
		const CImIAPPreferences& aSmtpIAP, TBool aReadOnly);

	IMPORT_C TSmtpAccount CreateSmtpAccountL(TImapAccount& aImapAccount, const CImSmtpSettings& aSmtpSettings,
		const CImIAPPreferences& aSmtpIAP, TBool aReadOnly);

	IMPORT_C TSmtpAccount CreateSmtpAccountL(const TDesC& aAccountName, const CImSmtpSettings& aSmtpSettings, 
		const CImIAPPreferences& aSmtpIAP, TBool aReadOnly);

	IMPORT_C void GetPopAccountsL(RArray<TPopAccount>& aAccounts);
	IMPORT_C void GetPopAccountL(TMsvId aServiceId, TPopAccount& aAccount); 
	IMPORT_C void DeletePopAccountL(const TPopAccount& aAccount);

	IMPORT_C void GetImapAccountsL(RArray<TImapAccount>& aAccounts);
	IMPORT_C void GetImapAccountL(TMsvId aServiceId, TImapAccount& aAccount); 
	IMPORT_C void DeleteImapAccountL(const TImapAccount& aAccount);

	IMPORT_C void GetSmtpAccountsL(RArray<TSmtpAccount>& aAccounts);
	IMPORT_C void GetSmtpAccountL(TMsvId aServiceId, TSmtpAccount& aAccount); 
	IMPORT_C void DeleteSmtpAccountL(const TSmtpAccount& aAccount);
	IMPORT_C void DeleteDefaultSmtpAccountL();

	IMPORT_C void PopulateDefaultPopSettingsL(CImPop3Settings& aPopSettings,
	CImIAPPreferences& aPopIap);

	IMPORT_C void PopulateDefaultImapSettingsL(CImImap4Settings& aImapSettings,
	CImIAPPreferences& aImapIap);

	IMPORT_C void PopulateDefaultSmtpSettingsL(CImSmtpSettings& aSmtpSettings,
	CImIAPPreferences& aSmtpIap);

	IMPORT_C TInt DefaultSmtpAccountL(TSmtpAccount& aAccount);
	IMPORT_C void SetDefaultSmtpAccountL(const TSmtpAccount& aAccount);

	IMPORT_C void LoadPopSettingsL(const TPopAccount& aAccount, CImPop3Settings& aPopSettings);
	IMPORT_C void LoadPopIapSettingsL(const TPopAccount& aAccount, CImIAPPreferences& aIAP);

	IMPORT_C void LoadImapSettingsL(const TImapAccount& aAccount, CImImap4Settings& aImapSettings);
	IMPORT_C void LoadImapIapSettingsL(const TImapAccount& aAccount, CImIAPPreferences& aIAP);

	IMPORT_C void LoadSmtpSettingsL(const TSmtpAccount& aAccount, CImSmtpSettings& aSmtpSettings);
	IMPORT_C void LoadSmtpIapSettingsL(const TSmtpAccount& aAccount, CImIAPPreferences& aIAP);

	IMPORT_C void SavePopSettingsL(const TPopAccount& aAccount, const CImPop3Settings& aPopSettings);
	IMPORT_C void SavePopIapSettingsL(const TPopAccount& aAccount, const CImIAPPreferences& aIAP);

	IMPORT_C void SaveImapSettingsL(const TImapAccount& aAccount, const CImImap4Settings& aImapSettings);
	IMPORT_C void SaveImapIapSettingsL(const TImapAccount& aAccount, const CImIAPPreferences& aIAP);

	IMPORT_C void SaveSmtpSettingsL(const TSmtpAccount& aAccount, const CImSmtpSettings& aSmtpSettings);
	IMPORT_C void SaveSmtpIapSettingsL(const TSmtpAccount& aAccount, const CImIAPPreferences& aIAP);
										
private:
	CEmailAccounts();
	void HandleSessionEventL(TMsvSessionEvent , TAny* , TAny* , TAny* );
	CMsvSession& SessionL();
	CRepository& PopRepositoryL();
	CRepository& ImapRepositoryL();
	CRepository& SmtpRepositoryL();

	TMsvId CreateEmailServiceL(CMsvEntry& aMsvEntry, const TDesC& aAccountName, TUid aMTMType, TBool aVisible);
	void SetRelatedIdL(CMsvEntry& aMsvEntry, TMsvId aId, TMsvId aRelatedId);
	void SetEntryDetailsL(TMsvId aId, const TDesC& aAccountName);
	void UnSetInPreparationFlagsL(CMsvEntry& aMsvEntry, TMsvId aId);
	void DeleteServiceEntryL(CMsvEntry& aMsvEntry, TMsvId aId);

	TUint GetNextEmptyAccountSlotL(CRepository& aRepository);
	TUint32 FindEmailAccountL(TMsvId aService, CRepository& aRepository);

	void LoadIAPPrefSettingsL(TUint32 aAccountId, CImIAPPreferences& aIAP, CRepository& aRepository);
	void DoLoadPopSettingsL(TUint32 aAccountId, CImPop3Settings& aPopSettings);
	void DoLoadImapSettingsL(TUint32 aAccountId, CImImap4Settings& aImapSettings);
	void DoLoadSmtpSettingsL(TUint32 aAccountId, CImSmtpSettings& aSmtpSettings);

	void SaveIAPPrefSettingsL(TUint32 aAccountId, const CImIAPPreferences& aIAP, CRepository& aRepository);
	void DoSavePopSettings(TUint32 aAccountId, const CImPop3Settings& aPopSettings);
	void DoSaveSmtpSettings(TUint32 aAccountId, const CImSmtpSettings& aSmtpSettings);
	void DoSaveImapSettings(TUint32 aAccountId, const CImImap4Settings& aImapSettings);	

	TUint32 DoCreatePopAccountL(const TDesC& aAccountName, const CImPop3Settings& aPopSettings, 
		const CImIAPPreferences& aPopIAP, TMsvId aPopService, TMsvId aRelatedService);
	TUint32 DoCreateImapAccountL(const TDesC& aAccountName, const CImImap4Settings& aImapSettings,
		const CImIAPPreferences& aImapIAP, TMsvId aImapService, TMsvId aRelatedService);
	TUint32 DoCreateSmtpAccountL(TPopAccount& aPopAccount, const CImSmtpSettings& aSmtpSettings, 
		const CImIAPPreferences& aSmtpIAP, TMsvId aSmtpService, CMsvEntry& aMsvEntry, TUint32& aPopAccountId);
	TUint32 DoCreateSmtpAccountL(TImapAccount& aImapAccount, const CImSmtpSettings& aSmtpSettings, 
		const CImIAPPreferences& aSmtpIAP, TMsvId aSmtpService, CMsvEntry& aMsvEntry, TUint32& aImapAccountId);
	TUint32 DoCreateSmtpAccountL(const TDesC& aAccountName, const CImSmtpSettings& aSmtpSettings, 
		const CImIAPPreferences& aSmtpIAP, TMsvId aSmtpService, TMsvId aRelatedService);	

	void DeleteIAPPrefSettingsL(TUint32 aAccountId, CRepository& aRepository);
	void DeletePopSettings(TUint32 aAccountId);
	void DeleteSmtpSettings(TUint32 aAccountId);
	void DeleteImapSettings(TUint32 aAccountId);	

private:
	enum TEmailSettingTypes
		{
		// Partial CenRep Id for service settings
		EServiceSettingType 			= 0x00000000,
		// Partial CenRep Id for IAP Prefs
		EIAPPrefSettingType				= 0x00010000,
		// CenRep mask for email accounts
		EAccountMask 					= 0x800FFFFF			
		};
	
	enum TPOPServiceSettingsCenRepId
		{
		EPOPServiceId					= 0x00000000,
		EPOPAccountNameId				= 0x00000001,
		EPOPRelatedSMTPServiceId		= 0x00000002,
		EPOPSettingsVersionId			= 0x00000003, 
		EPOPServerAddressId				= 0x00000004,
		EPOPPortNumberId			   	= 0x00000005,     	
		EPOPFlagsId						= 0x00000006,
		EPOPLoginNameId					= 0x00000007,
		EPOPPasswordId					= 0x00000008,
		EPOPMaxEmailSizeId				= 0x00000009,
		EPOPGetEmailOptionsId			= 0x0000000A,
		EPOPInboxSynchronisationLimitId	= 0x0000000B,
		EPOPPopulationLimitId			= 0x0000000C		
		};

	enum TIAPPreferencesCenRepId
		{
		// single settings		
		EIAPPrefVersion 				= 0x00010000,
		EIAPChoicesCount 				= 0x00010001,
		
		// List of settings
		EIAPListIDs						= 0x00011000,
		EIAPListDialogPrefs				= 0x00012000,
		};

	enum TIMAPServiceSettingsCenRepId
		{
		EIMAPServiceId					= 0x00000000,
		EIMAPAccountNameId				= 0x00000001,
		EIMAPRelatedSMTPServiceId		= 0x00000002,
		EIMAPSettingsVersionId			= 0x00000003, 
		EIMAPServerAddressId			= 0x00000004,
		EIMAPPortNumberId			   	= 0x00000005,     	
		EIMAPFlagsId					= 0x00000006,
		EIMAPLoginNameId				= 0x00000007,
		EIMAPPasswordId					= 0x00000008,
		EIMAPFolderPathId				= 0x00000009,
		EIMAPPathSeparatorId			= 0x0000000A,
		EIMAPSynchronisationStrategyId	= 0x0000000B,
		EIMAPSubscriptionStrategyId		= 0x0000000C,
		EIMAPMaxEmailSizeId				= 0x0000000D,
		EIMAPGetMailOptionsId			= 0x0000000E,
		EIMAPInboxSynchronisationLimitId= 0x0000000F,
		EIMAPMailboxSynchronisationLimitId= 0x00000010,		
		EIMAPSyncRateId					= 0x00000020,
		EIMAPFetchSizeId				= 0x00000030,
		EIMAPIdleTimeoutId				= 0x00000040,
		EPartialMailOptionsId			= 0x00000050,
		EBodyTextSizeLimitId			= 0x00000060,		
		EAttachmentSizeLimitId			= 0x00000070,
		EIMAPSearchStringId				= 0x00000080
		};

	enum TSMTPServiceSettingsCenRepId
		{
		ESMTPServiceId					= 0x00000000,
		ESMTPAccountNameId				= 0x00000001,		
		ESMTPSettingsVersionId			= 0x00000002,
		ESMTPServerAddressId			= 0x00000003, 
		ESMTPPortNumberId				= 0x00000004, 
		ESMTPFlagsId				   	= 0x00000005,     	
		ESMTPEmailAliasId				= 0x00000006, 
		ESMTPEmailAddressId				= 0x00000007,
		ESMTPReplyToAddressId			= 0x00000008,
		ESMTPReceiptAddressId			= 0x00000009,
		ESMTPBodyEncodingId				= 0x0000000A,
		ESMTPDefaultMsgCharSetId		= 0x0000000B,
		ESMTPSendCopyToSelfId			= 0x0000000C,
		ESMTPSendMessageOptionId		= 0x0000000D,
		ESMTPLoginNameId				= 0x0000000E,
		ESMTPPasswordId					= 0x0000000F,
		ESMTPRelatedServiceId			= 0x00000010,
		ESMTPIncludeToCcId				= 0x00000011
		};
				
private:
	CMsvSession* iMsvSession;
	CRepository* iPOPRepository;
	CRepository* iSMTPRepository;
	CRepository* iIMAPRepository;	
	};

#endif // __CEMAILACCOUNTS_H__
