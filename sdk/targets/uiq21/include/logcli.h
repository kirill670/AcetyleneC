// LOGCLI.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __LOGCLI_H__
#define __LOGCLI_H__

#include <f32file.h>
#include <d32dbms.h>
#include <logwrap.h>
#include <logcli.rsg>

//**********************************
// CLogEventType
//**********************************

class CLogEventType : public CBase
	{
public:
	IMPORT_C static CLogEventType* NewL();
	IMPORT_C ~CLogEventType();
	//
public:
	inline TUid Uid() const;
	inline void SetUid(TUid aUid);
	//
	inline const TDesC& Description() const;
	inline void SetDescription(const TDesC& aDescription);
	//
	inline TBool LoggingEnabled() const;
	inline void SetLoggingEnabled(TBool aEnable);
	//
	IMPORT_C void Copy(const CLogEventType& aType);
	//
private:
	CLogEventType();
	void ConstructL();
	//
private:
	TUid iUid;
	HBufC* iDescription;
	TBool iLoggingEnabled;
	};

//**********************************
// TLogConfig
//**********************************

class TLogConfig
	{
public:
	IMPORT_C TLogConfig();
	//
public:
	TLogSize iMaxLogSize;
	TLogRecentSize iMaxRecentLogSize;
	TLogAge iMaxEventAge;
	};

//**********************************
// CLogFilter
//**********************************

class CLogFilter : public CBase
	{
public:
	IMPORT_C static CLogFilter* NewL();
	IMPORT_C ~CLogFilter();
	//
public:
	inline TUid EventType() const;
	inline void SetEventType(TUid aType);
	//
	inline const TDesC& RemoteParty() const;
	inline void SetRemoteParty(const TDesC& aRemote);
	//
	inline const TDesC& Direction() const;
	inline void SetDirection(const TDesC& aDirection);
	//
	inline TLogDurationType DurationType() const;
	inline void SetDurationType(TLogDurationType aType);
	//
	inline const TDesC& Status() const;
	inline void SetStatus(const TDesC& aStatus);
	//
	inline TContactItemId Contact() const;
	inline void SetContact(TContactItemId aContact);
	//
	inline const TDesC& Number() const;
	inline void SetNumber(const TDesC& aNumber);
	//
	inline TLogFlags Flags() const;
	inline void SetFlags(TLogFlags aFlags);
	inline void ClearFlags(TLogFlags aFlags);
	//
	inline TUint32 NullFields() const;
	inline void SetNullFields(TUint32 aFields);
	//
	IMPORT_C void Copy(const CLogFilter& aFilter);
	//
private:
	CLogFilter();
	void ConstructL();
	//
private:
	TUid iEventType;
	HBufC* iRemoteParty;
	HBufC* iDirection;
	TLogDurationType iDurationType;
	HBufC* iStatus;
	TContactItemId iContact;
	HBufC* iNumber;
	TLogFlags iFlags;
	TUint32 iNullFields;
	};

class CLogFilterList : public CArrayPtrFlat<const CLogFilter>
	{
public:
	IMPORT_C CLogFilterList();
	IMPORT_C CLogFilterList* CopyL() const;
	IMPORT_C CLogFilterList* CopyLC() const;
	};

//**********************************
// CLogClient
//**********************************

class CLogMaintenance;
class CLogRecentSetup;
class CLogNotify;
class CLogAddEvent;
class CLogGetEvent;
class CLogChangeEvent;
class CLogDeleteEvent;
class CLogAddType;
class CLogGetType;
class CLogUpdate;
class CLogGetConfig;
class CLogGetString;
class CLogChangeConfig;
class CLogBackup;
class CLogView;
class CLogClientTimer;

class CLogClient : public CLogBase
	{
public:
	IMPORT_C static CLogClient* NewL(RFs& aFs, TInt aPriority = CActive::EPriorityStandard);
	IMPORT_C ~CLogClient();
	//
public:
	IMPORT_C void AddEvent(CLogEvent& aEvent, TRequestStatus& aStatus);
	IMPORT_C void GetEvent(CLogEvent& aEvent, TRequestStatus& aStatus);
	IMPORT_C void ChangeEvent(const CLogEvent& aEvent, TRequestStatus& aStatus);
	IMPORT_C void DeleteEvent(TLogId aId, TRequestStatus& aStatus);
	IMPORT_C void AddEventType(const CLogEventType& aType, TRequestStatus& aStatus);
	IMPORT_C void GetEventType(CLogEventType& aType, TRequestStatus& aStatus);
	IMPORT_C void ChangeEventType(const CLogEventType& aType, TRequestStatus& aStatus);
	IMPORT_C void DeleteEventType(TUid aId, TRequestStatus& aStatus);
	IMPORT_C void GetConfig(TLogConfig& aConfig, TRequestStatus& aStatus);
	IMPORT_C void ChangeConfig(const TLogConfig& aConfig, TRequestStatus& aStatus);
	IMPORT_C void ClearLog(const TTime& aDate, TRequestStatus& aStatus);
	IMPORT_C void ClearLog(TInt aRecentList, TRequestStatus& aStatus);
	//
	IMPORT_C void NotifyChange(TTimeIntervalMicroSeconds32 aDelay, TRequestStatus& aStatus);
	IMPORT_C void NotifyChangeCancel();
	//
	IMPORT_C TInt GetString(TDes& aString, TInt aId) const;
	IMPORT_C void BackupL(TBool aStart);
	//
public:
	void LoadStringL(TDes& aDes, TInt aId, ...) const;
	void LoadStringListL(TDes& aDes, TInt aId, VA_LIST list) const;
	void AppendStringL(TDes& aDes, TInt aId, ...) const;
	void AppendStringListL(TDes& aDes, TInt aId, VA_LIST list) const;
	const TDesC& LoadDbStringL(TInt aId, ...) const;
	const TDesC& LoadDbStringListL(TInt aId, VA_LIST list) const;
	//
	static void CancelRowSet(TAny *aRowSet);
	static void CloseRowSet(TAny *aRowSet);
	RDbNamedDatabase& Database();
	TInt BackupError() const;
	//
	CLogAddEvent* DoAddEventL(CLogEvent& aEvent, TRequestStatus& aObserver);
	CLogGetEvent* DoGetEventL(CLogEvent& aEvent, TRequestStatus& aObserver);
	CLogChangeEvent* DoChangeEventL(const CLogEvent& aEvent, TRequestStatus& aObserver);
	CLogDeleteEvent* DoDeleteEventL(TLogId aId, TRequestStatus& aObserver);
	CLogAddType* DoAddEventTypeL(const CLogEventType& aType, TRequestStatus& aObserver);
	CLogGetType* DoGetEventTypeL(TUid aId, TRequestStatus* aObserver = NULL);
	CLogGetType* DoGetEventTypeL(TLogTypeId aId, TRequestStatus* aObserver = NULL);
	CLogUpdate* DoChangeEventTypeL(const CLogEventType& aType, TRequestStatus& aObserver);
	CLogUpdate* DoDeleteEventTypeL(TUid aId, TRequestStatus& aObserver);
	CLogGetConfig* DoGetConfigL(TLogConfig& aConfig, TRequestStatus& aObserver);
	CLogChangeConfig* DoChangeConfigL(const TLogConfig& aConfig, TRequestStatus& aObserver);
	CLogUpdate* DoClearLogL(const TTime& aDate, TRequestStatus& aObserver);
	CLogUpdate* DoClearLogL(TInt aRecentList, TRequestStatus& aObserver);
	CLogUpdate* DoUpdateL(const TDesC& aSql, TBool aUseTransaction, TDbTextComparison aComparison, TRequestStatus& aObserver);
	CLogGetString* DoGetStringL(const TDesC& aString, TBool aAddString, TRequestStatus* aObserver = NULL);
	CLogGetString* DoGetStringL(TLogStringId aId, TRequestStatus* aObserver = NULL);
	//
	void AddViewL(CLogView& aView);
	void RemoveView(CLogView& aView);
	//
private:
	CLogClient(RFs& aFs, TInt aPriority);
	void ConstructL();
	//
	void DoRunL();
	void DoComplete(TInt&);
	void DoCancel();
	//
	void OpenDatabaseL();
	void LoadResourcesL();
	void DoGetStringL(TDes& aString, TInt aId) const;
	void SetAutoColumnL(TUint aTable, TUint aColumn);
	//
	void CreateDatabaseL(const TDesC& aName, TBool aReplace);
	void CreateTablesL();
	void CreateIndexesL();
	void CreateTypesL();
	void CreateConfigL();
	//
	void BeginL();
	void CommitL();
	static void Rollback(TAny *aClient);
	//
	enum TLogState {	ELogNone, ELogMaintain,
						ELogAddEvent, ELogGetEvent, ELogChangeEvent, ELogDeleteEvent,
						ELogClearLog, ELogClearRecent, 
						ELogGetConfig, ELogChangeConfig,
						ELogAddType, ELogGetType, ELogChangeType, ELogDeleteType };
	//
	void DoTask(TLogState aTask, TRequestStatus& aStatus);
	CLogActive* DoTaskL();
	void DoTask();
	//
private:
	RDbs iDbsSession;
	RDbNamedDatabase iDatabase;
	RResourceFile iResFile;
	//
	HBufC* iSql;
	TLogState iState;
	CLogRecentSetup* iRecentSetup;
	TInt iBackupError;
	TRequestStatus* iChangeObserver;
	RFs& iFs;
	CArrayPtrFlat<CLogView>* iViewList;
	TBuf<8> iParameter;
	TInt iRetryCount;
	//
	CLogAddEvent* iAddEvent;
	CLogGetEvent* iGetEvent;
	CLogChangeEvent* iChangeEvent;
	CLogDeleteEvent* iDeleteEvent;
	CLogAddType* iAddType;
	CLogGetType* iGetType;
	CLogUpdate* iUpdate;
	CLogGetConfig* iGetConfig;
	CLogMaintenance* iMaintain;
	CLogGetString* iGetString;
	CLogChangeConfig* iChangeConfig;
	//
	CLogActive* iCurrent;
	CLogNotify* iNotify;
	CLogBackup* iBackup;
	CLogClientTimer* iRetryTimer;
	//
private:
	IMPORT_C void CLogBase_Reserved1();
	};

#include "logcli.inl"

#endif
