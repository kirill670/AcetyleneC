// Mda\Server\Controller.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_SERVER_CONTROLLER_H__
#define __MDA_SERVER_CONTROLLER_H__

// Public Media Server includes
#include <Mda\Common\Controller.h>

#include <Mda\Server\Environment.h>
#include <Mda\Server\IoFactory.h>
#include <Mda\Server\Machine.h>
#include <Mda\Server\Connection.h>
#include <Mda\Server\Dispatcher.h>

class CMdaPort;
class CMdaBroadcaster;
class CMdaDispatchMessage;
class CMdaSrcPort;
class CMdaDstPort;

class CMdaController;
class CMdaControllerSlave;

class TMdaElapsedTimePublic : public TMdaElapsedTime
	{
public:
	inline TMode& Mode() { return iMode; }
	inline TTimeIntervalMicroSeconds& Elapsed() { return iElapsed; }
	};

class TMdaConnecter : public MMdaMessage
	{
	enum TState
		{
		EIdle,
		ECreatingSrcIO,
		ECreatingDstIO
		};
public:
	inline TBool IsConnecting();
	void ConnectL(CMdaMessage* aMessage);
	void CancelConnect(CMdaMessage* aMessage);
	CMdaConnection* CreateConnectionL();
	void ErrorConnect(TInt aErr);
	void CleanupConnect();
	// From MMdaMessage
	virtual void MessageDoComplete(TInt aVal);
	virtual void MessageDoReturnObjectL(TInt aArg, CMdaObject* aObject);
private:
	CMdaController* iParent;
	TState iState;
	CMdaDispatchMessage* iMessage;
	CMdaMessage* iCommandMessage;
	CMdaIOFactory* iSrcIOFactory;
	CMdaIOFactory* iDstIOFactory;
	CMdaIO* iSrcIO;
	CMdaIO* iDstIO;
	TUid iMediaType;
	friend class CMdaController;
	};

inline TBool TMdaConnecter::IsConnecting()
	{ return (iState!=EIdle); }

// CMdaController

class CMdaController : public CMdaObject, MMdaMachineMaster
	{
public:
	IMPORT_C void Close();
	IMPORT_C virtual void AddEventListenerL(MMdaEventListener& aListener);
	IMPORT_C virtual void RemoveEventListener(MMdaEventListener& aListener);
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);		
	IMPORT_C virtual void OperationCancel(CMdaMessage* aMessage);
	// Setup and config functions
	IMPORT_C CMdaDispatcher& Dispatcher();
	// State functions
	IMPORT_C TInt Priority();
	IMPORT_C TMdaPriorityPreference PriorityPreferences();
	IMPORT_C virtual void ConnectionFinished(CMdaConnection* aConnection);
	IMPORT_C virtual void ConnectionError(CMdaConnection* aConnection);
protected:
	IMPORT_C CMdaController();
	IMPORT_C ~CMdaController();
	// From MMdaMachineMaster
	IMPORT_C virtual void MachineStateChangeCompleted(CMdaMachine* aMachine);
	IMPORT_C virtual void MachineStateChangeFailed(CMdaMachine* aMachine,TInt aErr);
	// New
	IMPORT_C void ConstructL();
	IMPORT_C TBool InConnList(CMdaConnection* aConnection);
	IMPORT_C TBool InPortList(CMdaPort* aPort);
	IMPORT_C void AddConnection(CMdaConnection* aConnection);
	IMPORT_C void RemoveConnection(CMdaConnection* aConnection);
	IMPORT_C void RemoveAllConnections();
	IMPORT_C void RemovePorts();
	IMPORT_C void DisconnectL(CMdaMessage* aMessage);
	IMPORT_C void GetStateL(CMdaMessage* aMessage) const;
	IMPORT_C void SetPriorityL(CMdaMessage* aMessage);
	IMPORT_C void StateChangeL(CMdaMessage* aMessage);
	IMPORT_C void CancelStateChange(CMdaMessage* aMessage);
	IMPORT_C void ProcessStateChange();
	IMPORT_C void PostStateChangeEvent();
	IMPORT_C void PostErrorEvent(TInt aError);
	IMPORT_C void PostEvent(const TMdaEvent& aEvent);
	IMPORT_C void CheckForCompletion();
	IMPORT_C void QueueBackwardsInternalStateChange(TMdaMachineState aTargetState);
	IMPORT_C void InternalStateChange();
protected:
	TInt iPriority;
	TMdaPriorityPreference iPriPrefs;

	TMdaConnecter iConnecter;

	CMdaDispatcher* iDispatcher;
	CMdaMachine* iMachine;
	CMdaControllerSlave* iSlave;

	CMdaMessage* iStateChangeMsg; // Received state change message
	TMdaMachineState iTargetState;
	TBool iStateChangeForwards;

	TSglQue<MMdaEventListener> iListList;

    TSglQue<CMdaConnection> iConnList;
    TSglQueIter<CMdaConnection> iConnIter;
	TInt iConnCount;

    TSglQue<CMdaPort> iPortList;
    TSglQueIter<CMdaPort> iPortIter;

	TBool iIsInternalStateChangeQueued;
	TMdaMachineState iInternalTargetState;

	TUint iMessageSequenceCount;

	friend class TMdaConnecter;
	friend class CMdaControllerSlave;
	friend class CMdaConnection;
	};

class CMdaControllerSlave : public CBase, public MMdaMachineMaster, MMdaMachineSlaveParent
	{
public:
	IMPORT_C CMdaControllerSlave(CMdaController& aController);

	// From MMdaMachineSlaveParent
	virtual void MachineSetToFirstChild();
	virtual CMdaMachine* MachineNextChild();
	// From MMdaMachineMaster
	virtual void MachineStateChangeCompleted(CMdaMachine* aMachine);
	virtual void MachineStateChangeFailed(CMdaMachine* aMachine,TInt aErr);

	/*
	IMPORT_C TBool Broadcasting();
	IMPORT_C void ToPorts(CMdaMessage* aMessage);
	IMPORT_C void ToPortsCancel();
	IMPORT_C void ToPortsRollback();
	IMPORT_C void DoComplete(TInt aVal);
	// From MMdaMachine
	*/
protected:
	CMdaController& iController;
	TInt iCount;
	TInt iReturn;
	friend class CMdaController;
	};

#endif
