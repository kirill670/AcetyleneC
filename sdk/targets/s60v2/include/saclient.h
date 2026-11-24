// SACLIENT.H
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//

#ifndef __SACLIENT_H__
#define __SACLIENT_H__

#include <e32base.h>
#include "sacls.h"

/**
Constants
@internalComponent
*/
const TInt KSysAgentDefaultBufferExpireTimeInSeconds = 10; // 10 seconds




/** Encapsulates a request for notification of a change to a state variable.

The request is constructed and passed to the System Agent through the standard 
client handle, a RSystemAgent object.

The class is used in an active object environment. Typically, a TSysAgentEvent 
object is owned by an active object and takes that active object's request 
status.

Note: The class is a part of SystemAgent services and it is deprecated now. Use 
P&S services.

@see RSystemAgent
@see RSystemAgent::NotifyOnEvent()
@see RSystemAgent::NotifyOnAnyEvent()
@see CActive 
@see RProperty
@publishedAll
@deprecated
*/
class TSysAgentEvent
	{
public:
	IMPORT_C TSysAgentEvent();
	IMPORT_C TSysAgentEvent(TRequestStatus& aStatus);
public:
	IMPORT_C void SetRequestStatus(TRequestStatus& aStatus);
	IMPORT_C void SetUid(TUid aUid);
	IMPORT_C TInt State();
	IMPORT_C TUid Uid();
public:
	TRequestStatus& RequestStatus();
	void SetState(const TInt aState);
	TPckgBuf<TInt>& StatePckgBuf();
	TPckgBuf<TUid>& UidPckgBuf();
private:
	TPckgBuf<TInt> iRetStatePckg;
	TPckgBuf<TUid> iRetUidPckg;
	TRequestStatus* iStatus;
	};



/** Base class for client handles to the System Agent.

The class encapsulates a connection to the System Agent server.

Note: The class is a part of SystemAgent services and it is deprecated now. Use 
P&S services.

@see RSystemAgent
@see RSAVarChangeNotify 
@see RProperty
@publishedAll
@deprecated
*/
class RSystemAgentBase : public RSessionBase
	{
public:
	IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;
	RSystemAgentBase();
protected:
	IMPORT_C TInt StartSystemAgentServer();
	};


// Note: using any TSysAgentEvent asynchronous method will panic if
// a valid TRequestStatus has not been initialised.

/** The standard client handle to the System Agent.

This is the standard interface between clients and the System Agent.

Those who need to access information and to be notified of changes to state 
variables maintained by the System Agent, use this class.

Note that after construction, RSystemAgentBase::Connect() must be called before 
using any of the services provided by this class.

Note: The class is a part of SystemAgent services and it is deprecated now. Use 
P&S services.

@see RSystemAgentBase::Connect()
@see CArrayFixFlat 
@see RProperty
@publishedAll
@deprecated
*/
class RSystemAgent : public RSystemAgentBase
 	{
public:
	IMPORT_C RSystemAgent();
	IMPORT_C TInt GetState(TUid aUid);

	// aUids must contain at least one uid
	IMPORT_C TInt GetStates(const CArrayFixFlat<TUid>& aUids, CArrayFixFlat<TInt>& aStates);

	IMPORT_C void NotifyOnEvent(TSysAgentEvent& aEvent);
	IMPORT_C void NotifyOnAnyEvent(TSysAgentEvent& aEvent);

	// Returns an error code if aConditions does not contain at least one item, otherwise error code is returned through TRequestStatus
	IMPORT_C TInt NotifyOnCondition(CArrayFixFlat<TSysAgentCondition>& aConditions, TRequestStatus& aStatus);
	IMPORT_C void NotifyEventCancel();

	IMPORT_C void SetEventBufferEnabled(TBool aEnabled);
	IMPORT_C void SetEventBufferEnabled(TBool aEnabled, TTimeIntervalSeconds aExpireTime);

public: // do nothing in release builds
	IMPORT_C void __DbgShutDownServer();
	IMPORT_C void __DbgFailAlloc(TInt aCount);
	IMPORT_C void __DbgMarkHeap();
	IMPORT_C void __DbgMarkEnd();
	IMPORT_C void __DbgEventGenerator(TBool aEnableDisable);
	};



#endif
