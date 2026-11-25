// COMMDB.H
//
// Copyright (c) 1997-1999,2001 Symbian Ltd.  All rights reserved.
//

/** Comms Database public interface
*/

#ifndef __COMMDB_H__
#define	__COMMDB_H__

#include <d32dbms.h>
#include <savarset.h>
#include <dial.h>
#include <cdbcols.h>
#include <cdblen.h>

//
// Protection of settings: when the entire table is protected, write operations
// fail with KErrWrite. However KErrAccessDenied should be returned to client 
//
#define TRAPD_CONVERT(_r,_s)	TRAPD(_r,_s); if(ret == KErrWrite) ret = KErrAccessDenied;
#define  TRAP_CONVERT(_r,_s)	TRAP(_r,_s);  if(ret == KErrWrite) ret = KErrAccessDenied;

/** Responsible for Transactions, Notifications, Write protection and Hidden
	records, Phone number resolution, Creating views. Stores the database, the
	session, transaction and notifier information. `CCommsDatabaseBase` is an
	abstract base class as the `CreateDatabaseL` and `Open` methods are pure
	virtual.
*/
class CCommsDatabaseBase : public CBase
	{
public:
	friend class CCommsDbTableView;
	friend class CCommsDbConnectionPrefTableView;
public:
	IMPORT_C virtual ~CCommsDatabaseBase();

	/** Return the version of the database server. */
	IMPORT_C TVersion Version() const;

	/** Begin a transaction. Call before `InsertRecord()` or `UpdateRecord()`. */
	IMPORT_C TInt BeginTransaction();
	/** End a transaction. Call after `InsertRecord()` or `UpdateRecord()`. */
	IMPORT_C TInt CommitTransaction();
	/** Cancel a transaction. */
	IMPORT_C void RollbackTransaction();
	/** True if BeginTransaction() has been called but not
		`CommitTransaction()` or `RollbackTransaction()`. */
	IMPORT_C TBool InTransaction();
	/** True if the database has been locked. */
	IMPORT_C TBool IsDatabaseWriteLockedL();

	/** Enable a notification event on any change to the database. */
	IMPORT_C void RequestNotification(TRequestStatus& aStatus);
	/** Cancels notifications. */
	IMPORT_C void CancelRequestNotification();

	/** Obtain a view of all records in a table. */
	IMPORT_C CCommsDbTableView* OpenTableLC(const TDesC& aTableName);
	CCommsDbTableView* OpenTableL(const TDesC& aTableName);
	/** Obtain a view of the records in a table that match the query. */
	IMPORT_C CCommsDbTableView* OpenViewLC(const TDesC& aTableName, const TDesC& aSqlQuery);
	/** Obtain a view of all the records in a table that the field
		`aColumnToMatch` matches `aValueToMatch`. */
	IMPORT_C CCommsDbTableView* OpenViewMatchingUintLC(const TDesC& aTableName, const TDesC& aColumnToMatch, TUint32 aValueToMatch);
	IMPORT_C CCommsDbTableView* OpenViewMatchingBoolLC(const TDesC& aTableName, const TDesC& aColumnToMatch, TBool aValueToMatch);
	IMPORT_C CCommsDbTableView* OpenViewMatchingTextLC(const TDesC& aTableName, const TDesC& aColumnToMatch, const TDesC8& aValueToMatch);
	IMPORT_C CCommsDbTableView* OpenViewMatchingTextLC(const TDesC& aTableName, const TDesC& aColumnToMatch, const TDesC16& aValueToMatch);

	/** Make hidden records visible */
	IMPORT_C void ShowHiddenRecords();

	/** Set `aDialString` to be the appropriate string based on the directory
		number, where the dial is being performed and the chargecard to use.
		`ResolvePhoneNumberL()` opens a comms database to perform the
		resolution */
	IMPORT_C static void ResolvePhoneNumberL(TDesC& aNumber, TDes& aDialString, TParseMode aDialParseMode, TUint32 aLocationId, TUint32 aChargecardId);
	/** Set `aDialString` to be the appropriate string based on the directory
		number, where the dial is being performed and the chargecard to use. */
	IMPORT_C void ResolvePhoneNumberFromDatabaseL(TDesC& aNumber, TDes& aDialString, TParseMode aDialParseMode, TUint32 aLocationId, TUint32 aChargecardId);

protected:
	class TCommDbSystemAgentNotification
		{
	public:
		TCommDbSystemAgentNotification();
		void Set(TUid aUid, TInt aVal);
	public:
		TUid iUid;
		TInt iValue;
		};

protected:
	/** @private */
	IMPORT_C CCommsDatabaseBase();
	virtual void CreateDatabaseL() =0;
	//
	void DoClose();
	CCommsDbTableView* DoOpenViewMatchingUintL(const TDesC& aTableName, const TDesC& aColumnToMatch, TUint32 aValueToMatch, TBool aIncludeHiddenRecords);
	CCommsDbTableView* DoOpenViewMatchingTextL(const TDesC& aTableName, const TDesC& aColumnToMatch, const TDesC8& aValueToMatch, TBool aIncludeHiddenRecords);
	CCommsDbTableView* DoOpenViewMatchingTextL(const TDesC& aTableName, const TDesC& aColumnToMatch, const TDesC16& aValueToMatch, TBool aIncludeHiddenRecords);
	CCommsDbTableView* DoOpenTableViewL(const TDesC& aTableName, const TDesC& aSqlQuery);
	CCommsDbTableView* DoOpenIAPTableViewL(const TDesC& aTableName,const TDesC& aSqlQuery);
	//
	void PopulateDialLocationL(TUint32 aId, TDialLocation& aLocation);
	void PopulateChargeCardL(TUint32 aId, TChargeCard& aChargeCard);
	void BeginInternalTransactionL();
	TInt CommitInternalTransaction();
	void RollbackInternalTransaction();
	void DatabaseUpdateHasOccurred();
	void NotifyChangeL(const TDesC& aSetting, TUint32 aVal);
	void ConvertToUid(const TDesC& aSetting, TUint32 aVal, TCommDbSystemAgentNotification& aNotification);
	TInt NotifyAllChanges();
	TUint32 GetRandomNumber(TUid aUid);
	inline RDbNamedDatabase* Database();
protected:
	RDbs iDbs;
	RDbNamedDatabase iDatabase;
	RDbNotifier iNotifier;
	RSAVarChangeNotify iSystemAgentNotifier;
	TInt iNotifierOpenError;
	TBool iShowHiddenRecords;
	TBool iUpdateHasOccurred;
	TBool iInInternalTransaction;
	RArray<TCommDbSystemAgentNotification> iNotifications;
	RSystemAgent iSystemAgent;
	};

/** @deprecated 7.0 "defined null so `NewL()` compiles for most clients" */
#define EDatabaseTypeIAP
#define EDatabaseTypeUnspecified

/** @public
	Implements the pure virtual functions `CreateDatabaseL()` and `DoOpen()`
	Responsible for Global settings and Connection Preferences. Utility
	functions for accessing Global and Agent tables. No additional (to 
	`CCommsDatabaseBase`) state is stored. Clients need an instance of
	`CCommsDatabase` in order to create views and access template records.
*/
class CCommsDatabase : public CCommsDatabaseBase
	{
public:
	/** Creates a `CCommsDatabase`. If the database filestore does not exist
		the default filestore is duplicated. If no default filestore exists an
		empty database is created. */
	IMPORT_C static CCommsDatabase* NewL();
	/** Creates a `CCommsDatabase`. If the database filestore exists and
		`aUseDefaultDb` is True the default filestore is duplicated. Otherwise
		an empty database is created. */
	IMPORT_C static CCommsDatabase* NewL(TBool aUseDefaultDb);
	/** Creates a `CCommsDatabase` as with `NewL()`. The method of opening:
		(Created, CopiedDefault or Opened) is returned in `aOpeningMethod`. */
	IMPORT_C static CCommsDatabase* NewL(TCommDbOpeningMethod &aOpeningMethod);
	IMPORT_C virtual ~CCommsDatabase();

	/** Access global settings. */
	IMPORT_C void GetGlobalSettingL(const TDesC& aSetting, TUint32& aValue);
	IMPORT_C void GetGlobalSettingL(const TDesC& aSetting, TDes& aValue);
	IMPORT_C void SetGlobalSettingL(const TDesC& aSetting, TUint32 aValue);
	IMPORT_C void SetGlobalSettingL(const TDesC& aSetting, const TDesC& aValue);
	IMPORT_C void ClearGlobalSettingL(const TDesC& aSetting);
	/** Retrieve settings (Modem, Chargecard, and Service) for the dial	out IAP. */
	IMPORT_C void GetCurrentDialOutSettingL(const TDesC& aSetting, TUint32& aValue);
	/** Retrieve settings for the dial in IAP. */
	IMPORT_C void GetCurrentDialInSettingL(const TDesC& aSetting, TUint32& aValue);

	/** Open a connection preference view. */
	IMPORT_C CCommsDbConnectionPrefTableView* OpenConnectionPrefTableLC();
	/** Open a connection preference view containing connections of the
		specified direction. */
	IMPORT_C CCommsDbConnectionPrefTableView* OpenConnectionPrefTableLC(TCommDbConnectionDirection aDirection);
	/** Open a connection preference view containing connections of the
		specified direction excluding connections of rank zero. */
	IMPORT_C CCommsDbConnectionPrefTableView* OpenConnectionPrefTableInRankOrderLC(TCommDbConnectionDirection aDirection);
	/** Open a connection preference view containing connections of the
		specified direction and rank. */
	IMPORT_C CCommsDbConnectionPrefTableView* OpenConnectionPrefTableViewOnRankLC(TCommDbConnectionDirection aDirection, TUint32 aRank);

	/** Access agent settings. `aService` is one of: (`DIAL_OUT_ISP`,
		`DIAL_IN_ISP`, `OUTGOING_WCDMA` or `CDMA2000_PACKET_SERVICE_TABLE`). */
	IMPORT_C void SetAgentL(const TDesC& aService, const TDesC& aAgent);
	IMPORT_C void SetAgentExtL(const TDesC& aService, const TDesC& aAgentExt);
	IMPORT_C void SetAgentClientTimeoutL(const TDesC& aService, TInt aClientTimeout);
	IMPORT_C void SetAgentRouteTimeoutL(const TDesC& aService, TInt aRouteTimeout);
	IMPORT_C void GetAgentL(const TDesC& aService, TDes& aAgent);
	IMPORT_C void GetAgentExtL(const TDesC& aService, TDes& aAgentExt);
	IMPORT_C TInt GetAgentClientTimeoutL(const TDesC& aService);
	IMPORT_C TInt GetAgentRouteTimeoutL(const TDesC& aService);
	IMPORT_C void ClearAgentAndExtL(const TDesC& aService);

	/** Open a view on the IAP table containing records that match the
		bearers and direction specified. `aBearerSet` is a bit mask of type
		`TCommDbBearer`. */
	IMPORT_C CCommsDbTableView* OpenIAPTableViewMatchingBearerSetLC(TUint32 aBearerSet, TCommDbConnectionDirection aDirection);

	/** Open a view on the proxy table containing records that match the
		service id and type specified. */
	IMPORT_C CCommsDbTableView* OpenViewOnProxyRecordLC(TUint32 aServiceId, const TDesC& aServiceType);

	/** @private */
private:
	enum TGlobalSettingType
		{
		ENotASetting,
		EGlobalSetting,
		ECompatibilitySetting
		};
private:
	CCommsDatabase();
	// CCommsDatabaseBase pure virtuals
	virtual void CreateDatabaseL();
	//
	void DoOpenL(TCommDbOpeningMethod& aOpeningMethod,TBool aUseDefaultDb);
	CCommsDbTableView* OpenGlobalSettingsTableLC(const TDesC& aSetting, TBool& aExists);
	TGlobalSettingType GlobalSettingTypeL(const TDesC& aSetting) const;
	void DoGetCurrentSettingL(const TDesC& aSetting, TUint32& aValue, TBool aDialOut);
	void DoSetGlobalSettingL(const TDesC& aSetting, TUint32 aVal);
	void DoSetGlobalSettingL(const TDesC& aSetting, const TDesC& aVal);
	void DoGetCompatibilitySettingL(const TDesC& aSetting, TUint32& aVal);
	void DoSetCompatibilitySettingL(const TDesC& aSetting, TUint32 aVal);
	void DoSetIAPCompatibilitySettingL(const TDesC& aSetting, TUint32 aVal, TCommDbConnectionDirection aDirection, CCommsDbConnectionPrefTableView* aView, TBool aExists);
	void DoClearCompatibilitySettingL(const TDesC& aSetting);
	CCommsDbConnectionPrefTableView* DoFindConnectionPrefLC(TCommDbConnectionDirection aDirection, TBool& aExists);
	CCommsDbConnectionPrefTableView* DoOpenConnectionPrefViewLC(TCommDbConnectionDirection aDirection, TBool aInRankOrder, TUint32 aRankingToMatch = KMaxTUint32);
	void ValidateRankL(TUint32 aRank);
	CCommsDbTableView* DoOpenAgentTableLC(const TDesC& aService, TBool& aExists);
	void SetAgentDesL(const TDesC& aService, const TDesC& aField, const TDesC& aValue);
	void SetAgentTimeoutL(const TDesC& aService, const TDesC& aTimeoutType, TInt aTimeout);
	void GetAgentDesL(const TDesC& aService, const TDesC& aField, TDes& aValue);
	TInt GetAgentTimeoutL(const TDesC& aService, const TDesC& aTimeoutType);
	void ValidateServiceL(const TDesC& aService);
	void OpenDefaultDbL(RFs& aFs);
	};


class CCommsDbTableAccessView;
class 	CCommDbTableExtension : public CBase
	{
public:
	CCommDbTableExtension();
	void SetAccessView(CCommsDbTableAccessView* aView);
	void SetQueryL(const TDbQuery& aQuery);
	void SetColSet(CDbColSet* aColSet);
	CCommsDbTableAccessView* GetAccessView();
	TDbQuery                 GetQuery();
	CDbColSet*               GetColSet();
	void                     DeleteColSet();
	void                     Close();

private:
	CDbColSet* iColSet;
	HBufC*   iQueryText;
	CCommsDbTableAccessView* iAccess;	
	};
	
	/** @public
	Implements actions on tables and records in the database. Uses a
	`CCommsDatabase` and has an `RDbView` to read from and write to database.
	Created via the `CCommsDatabase` object `OpenTableLC()` (to open a view of
	all the records in the table) or one of the `OpenViewLC...()` functions
	(to open a specific view of the table).
*/

class CCommsDbTableView : public CBase
	{
public:
	friend class CCommsDatabaseBase;
	friend class CCommsDbTemplateRecord;
public:
	/** Low level view creation. Use if `CCommsDatabase::OpenTableLC()` or
	`CCommsDatabase::OpenViewLC...()` are not sufficient. */
	static CCommsDbTableView* NewL(CCommsDatabaseBase& aDb, const TDesC& aTableName, const TDbQuery& aQuery, TBool aUseTemplate =ETrue);
	CCommsDbTableView(CCommsDatabaseBase& aDb, const TDesC& aTableName);
	IMPORT_C virtual ~CCommsDbTableView();

	/** Add a new record to this table. The record number is returned.
		`PutRecordChanges()` is called to complete the transaction */
	IMPORT_C TInt InsertRecord(TUint32& aId);
	/** Modify the current record of this view. `PutRecordChanges()` is called
		to complete the transaction */
	IMPORT_C TInt UpdateRecord();
	/** Remove the current record from the table. */
	IMPORT_C TInt DeleteRecord();
	/** Store an inserted or updated record back to the database. */
	IMPORT_C TInt PutRecordChanges(TBool aHidden = EFalse, TBool aReadOnly = EFalse);
	/** Cancel pending changes since an insert or update. */
	IMPORT_C void CancelRecordChanges();

	/** Navigate throught the records in the view */
	IMPORT_C TInt GotoFirstRecord();
	IMPORT_C TInt GotoNextRecord();
	IMPORT_C TInt GotoPreviousRecord();

	/** Access data from the current record */
	IMPORT_C void ReadTextL(const TDesC& aColumn, TDes8& aValue);
	IMPORT_C void ReadTextL(const TDesC& aColumn, TDes16& aValue);
	IMPORT_C HBufC* ReadLongTextLC(const TDesC& aColumn);
	IMPORT_C void ReadUintL(const TDesC& aColumn, TUint32& aValue);
	IMPORT_C void ReadBoolL(const TDesC& aColumn, TBool& aValue);
	/** Determine the type and attributes of a column. The type is one of:
		(EDbColBit, EDbColUint32, EDbColText8, EDbColText16, EDbColLongText16).
		The attribute is a bit mask of: (ENotNull and EAutoIncrement). */
	IMPORT_C void ReadTypeAttribL(const TDesC& aColumn, TDbColType& aColType, TUint32& aAttrib);
	/** Null columns return 0, integers and bools 1, strings return their length in characters. */
	IMPORT_C void ReadColumnLengthL(const TDesC& aColumn, TInt& aLength);

	/** Modify an inserted or modified record. Must call `PutRecordChanges()`
		to store the changes. */
	IMPORT_C void WriteTextL(const TDesC& aColumn, const TDesC8& aValue);
	IMPORT_C void WriteTextL(const TDesC& aColumn, const TDesC16& aValue);
	IMPORT_C void WriteLongTextL(const TDesC& aColumn, const TDesC& aValue);
	IMPORT_C void WriteUintL(const TDesC& aColumn, const TUint32& aValue);
	IMPORT_C void WriteBoolL(const TDesC& aColumn, const TBool& aValue);
	IMPORT_C void SetNullL(const TDesC& aColumn);
	IMPORT_C void ReadColumnMaxLengthL(const TDesC& aColumn, TInt& aLength);


	inline CCommsDatabaseBase* Database() const { return &iDb; }

	void  OpenL(const TDbQuery& aQuery);

	/** The name of the current table */
	inline void GetTableName(TDes& aTableName) const;

	/* @protected */
protected:
	TDbColNo ColNumL(const TDesC& aColumn) const;
	void Close();
	void ConstructL(const TDbQuery& aQuery, TBool aUseTemplate);
	RDbRowSet::TAccess GetL();
	
	/* @private */
private:
	TInt InsertRecordWithThisId(TUint32 aId);
	TBool TableWithTemplateRecord() const;
	TBool EncryptedColumn(const TDesC& aColumn) const;
	void DoCheckRecordExistsL();
	void DoReadIdAttribL(const TDesC& aTableName,TDbColType& aColType,TUint32& aAttrib);
	void DoReadIdColumnLengthL(const TDesC& aTableName,TInt& aLength);
	void CheckAndNotifyForDefaultModemsL();
	void DoGotoRecordL(RDbView::TPosition aPos);
	void DoInsertRecordL(TUint32& aId);
	void DoUpdateRecordL();
	void DoDeleteRecordL();
	void DoPutRecordChangesL(TBool aHidden, TBool aReadOnly);

private:
	enum TTableState {
		EClosed,
		EOpenIdle,
		EInsert,
		EUpdate
		};

private:
	CCommsDatabaseBase& iDb;

	TTableState iState;
	CCommsDbTemplateRecord* iTemplate;
	TBool iTsyNameChanged;
	TUint32 iCurrentWriteModeRecordId;
	TUint32 iCurrentId;

protected:
	CCommDbTableExtension* iThis;
	RDbView iTableView;
	TBuf<KCommsDbSvrMaxColumnNameLength> iTableName;

	};
class CCommsDbTableAccessView : public CBase
	{
public:
	static CCommsDbTableAccessView* NewL(CCommsDatabaseBase& aDb,const TDesC& aTableName);
	~CCommsDbTableAccessView();

	void SetAccessL(TUint aAccessType);
	RDbRowSet::TAccess GetAccessL();

	CCommsDbTableAccessView(const TDesC& aTableName);
	void ConstructL(CCommsDatabaseBase& aDb);
	
private:
	const TDesC&       iTableName;
	CCommsDbTableView* iView;
	TBool              iTableFound;
	};

#include <commdb.inl>

#endif
