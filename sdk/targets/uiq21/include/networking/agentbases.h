// AGENTBASES.H
//
// Copyright (c) 2000, 2001 Symbian Ltd.  All rights reserved.
//

// Header for Base classes in States and State Machines

#ifndef __AGENTBASES_H__
#define __AGENTBASES_H__

#include <comms-infras/nifprvar.h>
#include <e32base.h>

const TUid KUidAgxType = { 0x10008B6A };

//
// Propagation towards the Agent Controller
//

class MAgentObserver
	{
public:
	virtual void PreventConnectionRetries() = 0;
	virtual void ServiceStarted() = 0;
	virtual void ConnectionComplete(TInt aProgress, TInt aError) = 0;
	virtual void ConnectionComplete(TInt aError) = 0;
	virtual void DisconnectComplete() = 0;
	virtual void UpdateProgress(TInt aProgress, TInt aError) = 0;
	virtual TInt Notification(TAgentToNifEventType aEvent, TAny* aInfo) = 0;
	virtual TInt IncomingConnectionReceived() = 0;
	};

class CCommsDbAccess;
class CDialogProcessor;

//
// Agent State Machine Base
//

class MAgentStateMachineEnv
	{
public:
	virtual CDialogProcessor* DlgPrc() = 0;
	virtual CCommsDbAccess* Db() =0;
	virtual void CompleteState(TInt aError) = 0;
	virtual TBool IsReconnect() const =0;
	virtual TBool CallBack() const =0;
	};

//
// CAgentStateBase
//

class CAgentStateBase : public CActive
	{
public:
	IMPORT_C CAgentStateBase(MAgentObserver& aSMObserver);
	IMPORT_C virtual ~CAgentStateBase();
	virtual void StartState() = 0;
	virtual CAgentStateBase* NextStateL(TBool aContinue) = 0;
protected:
	IMPORT_C void JumpToRunl(TInt aError);
protected:
	MAgentObserver* iSMObserver;
	};

//
// CAgentSMBase
//

class CAgentSMBase : public CActive, public MAgentObserver, public MAgentStateMachineEnv
	{
public:
	enum TSMContinueConnectType
		{
		ECallBack,
		EReconnect,
		EDisconnect
		};
	enum TSMPhase
		{
		EConnecting,
		EConnected,
		EDisconnecting,
		EDisconnected
		};
public:
	IMPORT_C CAgentSMBase(MAgentObserver& aControllerObserver, CDialogProcessor* aDlgPrc, CCommsDbAccess& aDbAccess);
	IMPORT_C virtual ~CAgentSMBase();
//
// Downward calls from NifMan/Agent Controller to state machine/states
//
	void StartConnect();
	void CancelConnect();
	IMPORT_C virtual void ConnectionContinuation(TSMContinueConnectType aConnectionAction);
	virtual TInt GetExcessData(TDes8& aBuffer) = 0;
	virtual TInt Notification(TNifToAgentEventType aEvent, TAny* aInfo) = 0;
	IMPORT_C virtual void GetLastError(TInt& aError);
//
// Upward calls from states/state machine to NifMan/Agent Controller. Inherited from MAgentObserver.
//
	IMPORT_C virtual void PreventConnectionRetries();
	IMPORT_C virtual void ServiceStarted();
	IMPORT_C virtual void ConnectionComplete(TInt aProgress,TInt aError);
	IMPORT_C virtual void ConnectionComplete(TInt aError);
	IMPORT_C virtual void DisconnectComplete();
	IMPORT_C virtual void UpdateProgress(TInt aProgress,TInt aError);
	IMPORT_C virtual TInt Notification(TAgentToNifEventType aEvent, TAny* aInfo);
	IMPORT_C virtual TInt IncomingConnectionReceived();
//
// MAgentStateMachineEnv derivision
//
	IMPORT_C virtual CDialogProcessor* DlgPrc();
	IMPORT_C virtual CCommsDbAccess* Db();
	IMPORT_C virtual void CompleteState(TInt aError);
	virtual inline TBool IsReconnect() const;
	virtual inline TBool CallBack() const;
//
private:
	IMPORT_C virtual void RunL();
	IMPORT_C virtual void DoCancel();
	void ProcessState();
	void ConnectCompleteReset();
protected:
	CAgentStateBase* iState;
	MAgentObserver* iControllerObserver;
	CDialogProcessor* iDlgPrc;
	CCommsDbAccess* iDb;
	TBool iContinueConnection;
	TBool iIsReconnect;
	TBool iCallBack;
	TSMPhase iSMPhase;
	};

#include <networking/agentbases.inl>

#endif

