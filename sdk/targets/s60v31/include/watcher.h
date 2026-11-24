// watcher.h
//
// Copyright (c) Symbian Software Ltd 2000-2005.  All rights reserved.
//

#ifndef __WATCHER_H__
#define __WATCHER_H__

#include <e32base.h>
#include <f32file.h>



//**********************************
// Constants
//**********************************

const TInt KWatcherDelay = 10000000; // 10 seconds

/** 
ECom interface UID for Active Watcher. 
@internalTechnology
@deprecated
*/
const TUid KUidEComWatcher = { 0x10006554 };

/** 
ECom interface UID for non-SMS related critical watchers. 
@publishedPartner
@released
*/
const TUid KUidMsgCriticalWatchers = { 0x1027433D };

/** 
ECom interface UID for non-SMS related non-critical watchers. 
@publishedPartner
@released
*/
const TUid KUidMsgNonCriticalWatchers = { 0x1027433E };

class CWatcherLog;
class RFs;

struct TWatcherParams
	{
	TWatcherParams(RFs& aFs, CWatcherLog& aLog) : iFs(aFs), iLog(aLog) {}
	//
	RFs&			iFs;
	CWatcherLog&	iLog;			
	};


//**********************************
// CWatcher
//**********************************

class CWatcher : public CActive
/**
@internalComponent
@released
*/
	{
public:
	IMPORT_C static CWatcher* NewL(TInt aPriority);
	IMPORT_C ~CWatcher();
	//
	IMPORT_C void Start(TRequestStatus& aStatus);
	//
private:
	CWatcher(TInt aPriority);
	void DoCancel();
	void RunL();
	//
private:
	TRequestStatus* iObserver;
	RThread iThread;
	};

//**********************************
// CWatcherLog
//**********************************

const TInt KWatcherLogBuffer = 256;
_LIT(KWatcherStringFormat, "%S");

class CWatcherLog : public CBase
/**
@publishedPartner
@released
*/
	{
public:
	static CWatcherLog* NewL(RFs& aFs);
	~CWatcherLog();
	//
	IMPORT_C void Printf(TRefByValue<const TDesC> aFmt,...);
	IMPORT_C void Printf(TRefByValue<const TDesC8> aFmt,...);
	IMPORT_C TBool IsLogging() const;
	//
private:
	CWatcherLog(RFs& aFs);
	void ConstructL();
	TBool IsConsole() const;

	//
private:
	CConsoleBase* iConsole;
	RFs& iFs;
	};

//**********************************
// CWatcherWait
//**********************************

class CWatcherWait: public CActive
/**
@internalComponent
@released
*/
	{
public:
	IMPORT_C static CWatcherWait* NewLC(TInt aPriority=EPriorityStandard);
	IMPORT_C ~CWatcherWait();
	IMPORT_C void Start();
	//
protected:
	CWatcherWait(TInt aPriority);
	void RunL();
	void DoCancel();
	};


// __WATCHER_H__
#endif
