// LOGVIEW.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __LOGVIEW_H__
#define __LOGVIEW_H__

#include <logwrap.h>
#include <d32dbms.h>

//**********************************
// CLogView
//**********************************

class CLogClient;
class CLogGetEvent;
class CLogQuery;
class CLogFilterQuery;

class CLogView : public CLogActive
	{
public:
	IMPORT_C ~CLogView();
	//
public:
	inline const CLogEvent& Event() const;
	//
	IMPORT_C TBool FirstL(TRequestStatus& aStatus);
	IMPORT_C TBool LastL(TRequestStatus& aStatus);
	IMPORT_C TBool NextL(TRequestStatus& aStatus);
	IMPORT_C TBool PreviousL(TRequestStatus& aStatus);
	//
	IMPORT_C TInt CountL();
	void BackupL(TInt aStart);
	//
protected:
	CLogView(CLogClient& aClient, TInt aPriority = CActive::EPriorityStandard);
	void ConstructL();
	//
	TBool StartL(const TDesC& aSql);
	inline TBool IsValid() const;
	void ResetL();
	void DoCancel();
	void PerformPurge();
	void DoPurgeL();
	//
private:
	TBool DoQueryL(RDbRowSet::TPosition aPos);
	void DoRunL();
	void DoComplete(TInt&);
	//
private:
	CLogEvent* iEvent;
	CLogGetEvent* iGetEvent;
	//
protected:
	CLogClient& iClient;
	TDbBookmark iLastEvent;
	TBool iValid;
	//
	CLogQuery* iQuery;
	CLogFilterQuery* iFilterQuery;
	};

//**********************************
// CLogViewEvent
//**********************************

class CLogFilterList;
class CLogFilter;

class CLogViewEvent : public CLogView
	{
public:
	IMPORT_C static CLogViewEvent* NewL(CLogClient& aClient, TInt aPriority = CActive::EPriorityStandard);
	IMPORT_C ~CLogViewEvent();
	//
public:
	IMPORT_C TBool SetFilterL(const CLogFilterList& aFilterList, TRequestStatus& aStatus);
	IMPORT_C TBool SetFilterL(const CLogFilter& aFilter, TRequestStatus& aStatus);
	//
private:
	CLogViewEvent(CLogClient& aClient, TInt aPriority);
	};

//**********************************
// CLogViewRecent
//**********************************

class CLogViewDuplicate;
class CLogGetConfig;

class CLogViewRecent : public CLogView
	{
public:
	IMPORT_C static CLogViewRecent* NewL(CLogClient& aClient, TInt aPriority = CActive::EPriorityStandard);
	IMPORT_C ~CLogViewRecent();
	//
public:
	IMPORT_C TBool SetRecentListL(TLogRecentList aList, TRequestStatus& aStatus);
	IMPORT_C TBool SetRecentListL(TLogRecentList aList, const CLogFilter& aFilter, TRequestStatus& aStatus);
	IMPORT_C TBool SetRecentListL(TLogRecentList aList, const CLogFilterList& aFilterList, TRequestStatus& aStatus);
	//
	IMPORT_C TBool DuplicatesL(CLogViewDuplicate& aView, TRequestStatus& aStatus);
	IMPORT_C TBool DuplicatesL(CLogViewDuplicate& aView, const CLogFilter& aFilter, TRequestStatus& aStatus);
	IMPORT_C TBool DuplicatesL(CLogViewDuplicate& aView, const CLogFilterList& aFilterList, TRequestStatus& aStatus);
	//
	IMPORT_C void RemoveL(TLogId aId);
	IMPORT_C TBool RemoveL(TRequestStatus& aStatus);
	//
	inline TLogRecentList RecentList() const;
	//
private:
	CLogViewRecent(CLogClient& aClient, TInt aPriority);
	void DoRunL();
	//
	TBool DoRemoveL(TRequestStatus& aStatus);
	//
private:
	TLogRecentList iRecentList;
	TLogRecentList iCurrentList;
	};

//**********************************
// CLogViewDuplicate
//**********************************

class CLogViewDuplicate : public CLogView
	{
public:
	IMPORT_C static CLogViewDuplicate* NewL(CLogClient& aClient, TInt aPriority = CActive::EPriorityStandard);
	//
	IMPORT_C void RemoveL(TLogId aId);
	IMPORT_C TBool RemoveL(TRequestStatus& aStatus);
	//
	inline TLogId Source() const;
	//
public:
	// The following are not exported, use CLogViewRecent::DuplicatesL to initialise this view
	TBool SetEventL(TLogId aId, TRequestStatus& aStatus);
	TBool SetEventL(TLogId aId, const CLogFilter& aFilter, TRequestStatus& aStatus);
	TBool SetEventL(TLogId aId, const CLogFilterList& aFilterList, TRequestStatus& aStatus);
	//
private:
	CLogViewDuplicate(CLogClient& aClient, TInt aPriority);
	//
	TBool DoRemoveL(TRequestStatus& aStatus);
	//
private:
	TLogId iSourceId;
	};

#include "logview.inl"

#endif
