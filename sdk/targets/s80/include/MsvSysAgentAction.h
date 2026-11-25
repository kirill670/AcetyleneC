/////////////////////////////////////////////////////////////////////////////
//
//	MsvSysAgentCondAction.H
//
//	Copyright (c) 2000 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef SYS_AGENT_COND_ACTION_H_
#define	SYS_AGENT_COND_ACTION_H_

#include <sacls.h>
#include <saclient.h>
#include "MsvSendErrorAction.h"

/////////////////////////////////////////////////////////////////////////////
//
//	System Agent-related Class Declarations
//
/////////////////////////////////////////////////////////////////////////////

const TUid KUidMsvSysAgentActions			= {0x10005E4A};
const TInt16 KMsvSysAgentConditionActionVersion	= 1;

class TMsvSysAgentConditionAction
/** A System Agent condition that must be satisfied before a message sending attempt. 
@publishedAll
@released
*/
	{
public:
	IMPORT_C TMsvSysAgentConditionAction();

	IMPORT_C void ExternalizeL(RWriteStream& aWriteStream) const;
	IMPORT_C void InternalizeL(RReadStream& aReadStream);

	/** System agent condition to meet. */
	TSysAgentCondition iCondition;
	/** Error action to use. */
	TMsvSendErrorAction iErrorAction;
	/** Default error action. */
	TBool iUseDefaultSysAgentAction;

private:
	TInt16 iVersion;
	};

class CMsvSysAgentActions : public CArrayFixFlat<TMsvSysAgentConditionAction>
/** Defines an array of System Agent conditions that must be satisfied before a 
message sending attempt.

@see TMsvSysAgentConditionAction 
@publishedAll
@released
*/
	{
public:
	IMPORT_C CMsvSysAgentActions();
	IMPORT_C ~CMsvSysAgentActions();

	IMPORT_C void StoreL(CMsvStore& aStore) const;
	IMPORT_C void RestoreL(CMsvStore& aStore);

	IMPORT_C TBool ConditionsMetL(TMsvSendErrorAction& aErrorAction);

	/** Default send error action. */
	TMsvSendErrorAction iDefault;

private:

	void ExternalizeL(RWriteStream&) const;
	void InternalizeL(RReadStream&);

	void GetConditionVariablesL(CArrayFix<TUid>& aUids) const;
	TBool CheckStates(const CArrayFix<TInt>& aStates, TMsvSendErrorAction& aErrorAction) const;
	TBool ConditionOK(const TMsvSysAgentConditionAction& aCondAction, const TInt aState) const;


	RSystemAgent iAgent;
	TBool iAgentConnected;
	};

#endif
