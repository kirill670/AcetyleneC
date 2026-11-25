// EVENTLOGGER.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#ifndef __EVENTLOGGER_H__
#define __EVENTLOGGER_H__
#include <logcli.h>

// Event Logging facility
const TLogId KGenconnLogWaitingForLogId = KLogNullId -1;
const TInt KBytesInfoNotAvailable = -1;

class CEventLogger : public CActive
	{
public:
	enum { KConnectionStatusIdNotAvailable = -1,
		      KEventStateMaxCount = 10,
		      KDatabufferSize = 64};
	IMPORT_C static CEventLogger* NewL();
	IMPORT_C virtual ~CEventLogger();
	IMPORT_C void Cancel();
	IMPORT_C void LogCallStart(const TDesC& aRemote,TInt aLogDir, const TDesC& aTelNum, TUid aDataEventType, TRequestStatus& aStatus);
	IMPORT_C void LogCallEnd(TRequestStatus& aStatus);
	IMPORT_C void LogDataTransferred(TInt64 aBytesSent, TInt64 aBytesReceived, TUid aDataEventType, TRequestStatus& aStatus);
	IMPORT_C void LogDataAddEvent(TInt aRConnectionStatusId, const TDesC& aRemote, TInt aLogDir, const TDesC& aTelNum, TUid aDataEventType);
	TInt UpdateLogEventParam(CLogEvent & aLogEvent, TInt aRConnectionStatusId, const TUid& aDataEventType, const TInt64& aBytesSent, const TInt64& aBytesReceived);
	IMPORT_C TInt LogDataUpdateEvent(TInt aRConnectionStatusId, const TUid& aDataEventType, const TInt64& aBytesSent, const TInt64& aBytesReceived);
	IMPORT_C TInt LogDataUpdateEvent(TInt aRConnectionStatusId, const TUid& aDataEventType);
	IMPORT_C void LogDataNotifyLastEventUpdate(TRequestStatus* aStatus);

//from CActive
	void DoCancel();
	void RunL();

private:
	CEventLogger();
	void ConstructL();
private:
	CLogWrapper* iLogWrap;
	CLogEvent* iCurrentLogEvent;
	CArrayPtrFlat<CLogEvent>* iLogEventQueue;
	RFs iFsEventLog;
	TRequestStatus* iNotificationRequestStatus;
	};

#endif

