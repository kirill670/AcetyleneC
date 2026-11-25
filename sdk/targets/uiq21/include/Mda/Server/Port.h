// Mda\Server\Port.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_SERVER_PORT_H__
#define __MDA_SERVER_PORT_H__

/*
Notes:
A port is a synchronised startpoint or endpoint for data
All ports are derived from CMdaPort
*/

#include <Mda\Common\Port.h>

#include <Mda\Server\Base.h>
#include <Mda\Server\IoFactory.h>
#include <Mda\Server\Machine.h>
#include <Mda\Server\Controller.h>

class CMdaIO;
class CMdaConnection;
class CMdaBuffer;
class TMdaMessage;
class CMdaDispatchMessage;

class CMdaPort : public CMdaIOFactory, public MMdaMachineSlaveParent, public MMdaMachineMaster
// 
// Abstract base class for all ports
//
	{
public:
	IMPORT_C virtual void Close();
	// From CMdaObject (Message passing)
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	IMPORT_C virtual void OperationCancel(CMdaMessage* aMessage);
	// From CMdaIOFactory
	IMPORT_C virtual void NewIOL(CMdaMessage* aMessage);
	IMPORT_C virtual void CancelNewIO(CMdaMessage* aMessage);
	// New
	IMPORT_C virtual void PortConfigL(CMdaMessage* aMessage);
	IMPORT_C virtual void CancelPortConfig(CMdaMessage* aMessage);
	//
	IMPORT_C TMdaMachineState State() const;
	// Media Type Information
	IMPORT_C virtual TBool MediaTypePresent(TUid aMediaType) const =0; // Must supply
	// State change functions
	IMPORT_C virtual void ConnectDone();
	IMPORT_C TInt CountIO();
	IMPORT_C void IOClosed(CMdaIO* aIO);
protected:	
	// From MMdaMachineMaster
	IMPORT_C virtual void MachineStateChangeCompleted(CMdaMachine* aMachine);
	IMPORT_C virtual void MachineStateChangeFailed(CMdaMachine* aMachine,TInt aErr);
	// From MMdaMachineSlaveParent
	IMPORT_C virtual void MachineSetToFirstChild();
	IMPORT_C virtual CMdaMachine* MachineNextChild();
protected:
	IMPORT_C CMdaPort(TBool aSourcePort);
	IMPORT_C ~CMdaPort();
	IMPORT_C virtual CMdaIO* DoOpenIOL(TUid aMediaType);
	IMPORT_C virtual void AddIO(CMdaIO* aIO);
	IMPORT_C virtual void RemoveIO(CMdaIO* aIO);
	IMPORT_C virtual CMdaIO* OpenIOL(TUid aMediaType);
public: // Used by the controller
	TSglQueLink iControllerLink;
	CMdaController* iController;
protected:
    TSglQue<CMdaIO> iIOList;
    TSglQueIter<CMdaIO> iIOIter;
	TInt iOppReturn;
	TInt iIOCmndCount;
	TInt iIOCount;
	TBool iSource;
	friend class TMdaMachine;
	};

#endif
