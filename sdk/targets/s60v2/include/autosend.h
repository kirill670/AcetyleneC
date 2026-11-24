//	AutoSend.h
//
//	Copyright (c) 2001-2004 Symbian Software Ltd. All rights reserved.
//

#ifndef __AUTOSEND_H__
#define __AUTOSEND_H__

#if !defined(_MSG_NO_LOGGING) || defined(_DEBUG)
#define AUTOSEND_LOGGING
#endif
const TInt KDefaultPriority = CActive::EPriorityStandard;

_LIT(KMsvWinsAutoSendThreadName, "AutoSend");

class CClientMtmRegistry;

#ifdef __MESSAGING_API_V2__
TInt Execute(const TMsvId aDestinationId);
#else
void Execute(const TMsvId aDestinationId);
#endif	// __MESSAGING_API_V2__
void DoExecuteL(const TMsvId aDestinationId);

#ifdef __MESSAGING_API_V2__
class TDummyMsvSessionObserver : public MMsvSessionObserver
	{
public:
	void HandleSessionEventL(TMsvSessionEvent aEvent, TAny *aArg1, TAny *aArg2, TAny *aArg3);
	};
#endif	// __MESSAGING_API_V2__

/**
@internalComponent
@released
*/
class CAutoSendProgressTimer : public CTimer
	{
public:
	static CAutoSendProgressTimer* NewL(CMsvOperation& aOperation, const TTimeIntervalMicroSeconds32& aPollInterval);
	void Start();
	~CAutoSendProgressTimer();
	
private:
	CAutoSendProgressTimer(CMsvOperation& aOperation, const TTimeIntervalMicroSeconds32& aPollInterval);
	void RunL();
	CMsvOperation& iOperation;
	TTimeIntervalMicroSeconds32 iPollInterval;
	};

/**
@internalComponent
@released
*/
class CImAutoSend : public MMsvSessionObserver, CActive
	{
public:	
	static CImAutoSend* StartLC(const TMsvId aDestinationId);
	~CImAutoSend();

	void HandleSessionEventL(MMsvSessionObserver::TMsvSessionEvent /*aEvent*/, TAny* /*aArg1*/, TAny* /*aArg2*/, TAny* /*aArg3*/) {};
	TBool IsSendActive() {return IsActive();}

private:

	CImAutoSend(const TMsvId aDestinationId);
	void ConstructL();

	void DoCancel();
	void RunL();

	void CallMtmL();

#ifdef AUTOSEND_LOGGING
	void FLog(const TDesC& buf);
	void FLog(TRefByValue<const TDesC> aFormat, ...);
#endif

private:
	CMsvSession*			iSession;
	CMsvOperation*			iOperation;
	CAutoSendProgressTimer*	iTimer;
	TMsvId					iDestinationId;
	CActiveSchedulerWait	iActiveSchedulerWait;
	};

#endif