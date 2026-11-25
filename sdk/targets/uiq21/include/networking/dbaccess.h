// DBACCESS.H
//
// Copyright (c) 2000, 2001 Symbian Ltd.  All rights reserved.
//

// Generic Connection Agent Database Access Class Header

#ifndef __DBACCESS_H__
#define __DBACCESS_H__

#include <etel.h>
#include <etelmm.h>
#include <connectprog.h>
#include <cdbover.h>
#include <networking/connectionsettings.h>
#include "agentdialog.h"

_LIT(KGeneralServiceTable, "ISP");

class CCommDbOverrideSettings;

class CDefaultRecordAccess : public CBase
	{
public:
	CDefaultRecordAccess();
	CDefaultRecordAccess(const TDesC& aName);
	~CDefaultRecordAccess();
	void Close();
//
	TBool OpenRecordL(CCommsDatabase* aDb, TUint32 aId);
	TBool OpenRecordL(CCommsDatabase* aDb, TUint32 aId, const TDesC& aTableName);
//
	TBool SetOverridden(TBool aOverridden, TUint32 aId);
	inline CCommsDbTableView* Table() const { return iTable; }
	inline TPtrC Name() const { return iName; }
	inline TUint32 Id() const { return iId; }
private:
	void CloseTable();
private:
	CCommsDbTableView* iTable;
	TBuf<KCommsDbSvrMaxColumnNameLength> iName;
	TUint32 iId;
	TBool iOverridden;
	};

class MServiceChangeObserver
	{
public:
	virtual void ServiceChangeNotification(TUint32 aId, const TDesC& aType) = 0;
	};

//
// CCommsDbAccess
//
// One of these per CAgentController object.  Has a CCommsDatabase object and CCommsDbTableView's for 
// accessing data in CommDb.  Also uses a CCommDbOverrideSettings for accessing overridden 
// fields.  Also has a CDbChangeNotification for checking when the database is changed. 
// Exported methods in CCommsDbAccess object are also used by the CScriptBase class.
//
class CAgentCompanionSession;

class CCommsDbAccess : public CBase
	{
public:
	IMPORT_C static CCommsDbAccess* NewL();
	IMPORT_C ~CCommsDbAccess();

	// Close database access
	IMPORT_C void Close();

	// Set functions
	IMPORT_C void SetOverridesL(CCommDbOverrideSettings* aOverrides);

	// Default settings
	IMPORT_C void GetCurrentSettingsL(TConnectionSettings& aSettings, TCommDbConnectionDirection aDirection, TUint32 aRank);
	IMPORT_C void SetCurrentSettingsL(const TConnectionSettings& aSettings);
	IMPORT_C void SetModemAndLocationL(const TConnectionSettings& aSettings);
	void GetServiceSettingsL(TConnectionSettings& aSettings);
	TBool IsTelNumLengthZeroForRasConnectionL(TConnectionSettings& aSettings);
	TInt GetConnectionAttempts();

	// Modem related
	IMPORT_C void GetTsyNameL(TDes& aTsyName);
	IMPORT_C void SetCommPortL(const RCall::TCommPort& aCommPort);

	// Service Related
	IMPORT_C void GetServiceTypeL(TDes& aServiceType);
	void GetAuthParamsL(TBool& aPromptForAuth,TDes& aUsername,TDes& aPassword);

	// Agent Related
	void GetAgentExtL(const TDesC& aServiceType, TDes& aAgentExt);

	// MobileIP Related
	void SetNetworkMode(const RMobilePhone::TMobilePhoneNetworkMode aNetworkMode);

	// ISP
	void FillInConnectionNamesL(TIspConnectionNames& aNames);

	// Calls to database server for use by NifMan
	TInt ReadInt(const TDesC& aField, TUint32& aValue);
	TInt ReadBool(const TDesC& aField, TBool& aValue);
	TInt ReadDes(const TDesC& aField, TDes8& aValue);
	TInt ReadDes(const TDesC& aField, TDes16& aValue);
	HBufC* ReadLongDesLC(const TDesC& aField);
	TInt WriteInt(const TDesC& aField, TUint32 aValue);
	TInt WriteBool(const TDesC& aField, TBool aValuge);
	TInt WriteDes(const TDesC& aField, const TDesC8& aValue);
	TInt WriteDes(const TDesC& aField, const TDesC16& aValue);

	// Service change noification
	void RequestNotificationOfServiceChangeL(MServiceChangeObserver* aObserver);
	void CancelRequestNotificationOfServiceChange(MServiceChangeObserver* aObserver);

	// Reads from the agent extensions: read from the overrides, or if they don't exist 
	// straight from the database
	IMPORT_C void GetIntL(const TDesC& aTable, const TDesC& aField, TUint32& aValue);
	IMPORT_C void GetBoolL(const TDesC& aTable, const TDesC& aField, TBool& aValue);
	IMPORT_C void GetDesL(const TDesC& aTable, const TDesC& aField, TDes8& aValue);
	IMPORT_C void GetDesL(const TDesC& aTable, const TDesC& aField, TDes16& aValue);
	IMPORT_C HBufC* GetLongDesLC(const TDesC& aTable, const TDesC& aField);
	IMPORT_C TInt GetLengthOfLongDesL(const TDesC& aTable, const TDesC& aField);
	IMPORT_C TInt GetMaxLengthOfDesL(const TDesC& aTable, const TDesC& aField);
	IMPORT_C void GetGlobalL(const TDesC& aName,TUint32& aVal);

	// Some specific functions for agent exts
	IMPORT_C CCommsDbTableView* ModemTable();
	IMPORT_C TUint32 LocationId() const;
	IMPORT_C TCommDbConnectionDirection GetConnectionDirection() const;

private:
	CCommsDbAccess();
	void ConstructL();

	// Getting and setting connection preferences
	void GetIapConnectionPreferenceL(TConnectionSettings& aSettings);
	void SetIapConnectionPreferenceL(const TConnectionSettings& aSettings);
	TBool LocationRequiredL();

	// Convert name from NifMan
	CDefaultRecordAccess* ConvertFieldNameL(TDes& aName);
	CDefaultRecordAccess* ConvertTableNameToRecordAccessL(const TDesC& aTable);
	
	// Service change notification
	void CheckForServiceChange(TBool aChanged);

	// Reads from overrides and then if not there read from database
	void GetIntL(CDefaultRecordAccess* aSetting, const TDesC& aField, TUint32& aValue);
	void GetBoolL(CDefaultRecordAccess* aSetting, const TDesC& aField, TBool& aValue);
	void GetDesL(CDefaultRecordAccess* aSetting, const TDesC& aField, TDes8& aValue);
	void GetDesL(CDefaultRecordAccess* aSetting, const TDesC& aField, TDes16& aValue);
	HBufC* GetLongDesLC(CDefaultRecordAccess* aSetting, const TDesC& aField);
	TInt GetLengthOfLongDesL(CDefaultRecordAccess* aSetting, const TDesC& aField);
	TInt GetMaxLengthOfDesL(CDefaultRecordAccess* aSetting, const TDesC& aField);

private:
	CCommsDatabase* iDb;
	TCommDbConnectionDirection iDirection;
	CDefaultRecordAccess iIAPSetting;
	CDefaultRecordAccess iServiceSetting;
	CDefaultRecordAccess iChargecardSetting;
	CDefaultRecordAccess iModemSetting;
	CDefaultRecordAccess iLocationSetting;
	TBool iGotSettings;
	CCommDbOverrideSettings* iOverrides;
	RCall::TCommPort iCommPort;
	MServiceChangeObserver* iServiceChangeObserver;
	//MobileIP network mode
	RMobilePhone::TMobilePhoneNetworkMode iNetworkMode;
	};

#endif
