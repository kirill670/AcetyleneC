//	MsvSysAgentCondAction.H
//
//	Copyright (c) Symbian Software Ltd 2000-2004.  All rights reserved.  
//

#ifndef __MSVSYSAGENTCONDACTION_H__
#define	__MSVSYSAGENTCONDACTION_H__

#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__
 
#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__

#ifndef __MESSAGING_API_V2__
#include <sacls.h>
#include <saclient.h>
#endif // __MESSAGING_API_V2__

#include "MsvSendErrorAction.h"

/////////////////////////////////////////////////////////////////////////////
//
//	System Agent-related Class Declarations
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __HIDE_MESSAGING_API_V1__
const TUid KUidMsvSysAgentActions			= {0x10005E4A};

const TInt16 KMsvSysAgentConditionActionVersion	= 1;
#endif

#ifdef __MESSAGING_API_V2__

/** 
Defines a condition which a Publish and Subscribe Uid must satisfy.

@see RProperty

@publishedAll
@released
*/
class TMsvCondition
	{
public:
/** 
An enumeration defining the type of test to be made against a Publish 
and Subscribe property. 
*/
	enum TMsvSchSendConditionType
		{
		/** Tests that a value is equal to a state variable value. */
		EMsvSchSendEquals,		
		/** Tests that a value is unequal to a state variable value. */
		EMsvSchSendNotEquals,		
		/** Tests that a value is greater than a state variable value. */
		EMsvSchSendGreaterThan,	
		/** Tests that a value is less than a state variable value. */
		EMsvSchSendLessThan		
		};
		
public:
	/** second UID of the process which set the condition*/
	TUid iVariable;
	/** Integer state of corresponding P&S variable to be tested against*/
	TInt iState;
	/** type of test to be performed */
	TMsvSchSendConditionType iType;
	};
	
#endif // __MESSAGING_API_V2__

#ifdef __MESSAGING_API_V2__
/**
Schedule Send condition must be satisfied before a message sending attempt.

@publishedAll
@released
*/ 
#else
/**
A System Agent condition that must be satisfied before a message sending 
attempt. 

@publishedAll
@released
*/
#endif // __MESSAGING_API_V2__

class TMsvSysAgentConditionAction
	{
public:
	IMPORT_C TMsvSysAgentConditionAction();

#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C void ExternalizeL(RWriteStream& aWriteStream) const;
	IMPORT_C void InternalizeL(RReadStream& aReadStream);
#endif	// __HIDE_MESSAGING_API_V1__

#ifdef __MESSAGING_API_V2__
	/** Condition to meet. */
	TMsvCondition iCondition;
#else
	/** System agent condition to meet. */
	TSysAgentCondition iCondition;
#endif // __MESSAGING_API_V2__

	/** Error action to use. */
	TMsvSendErrorAction iErrorAction;

	/** Default error action. */
	TBool iUseDefaultSysAgentAction;

private:
#ifndef __REMOVE_MESSAGING_API_V1__		
	TInt16 iVersion;
#endif	//__REMOVE_MESSAGING_API_V1__
	};



#ifdef __MESSAGING_API_V2__
/**
Defines an array of  schedule send conditions that must be satisfied before a message sending attempt.

@see TMsvSysAgentConditionAction

@publishedAll
@released
*/ 
#else
/**
Defines an array of System Agent conditions  that must be satisfied before a message sending attempt.

@see TMsvSysAgentConditionAction

@publishedAll
@released
*/
#endif // __MESSAGING_API_V2__

class CMsvSysAgentActions : public CArrayFixFlat<TMsvSysAgentConditionAction>
	{
public:
	IMPORT_C CMsvSysAgentActions();
	IMPORT_C ~CMsvSysAgentActions();

#ifndef __HIDE_MESSAGING_API_V1__
	IMPORT_C void StoreL(CMsvStore& aStore) const;
	IMPORT_C void RestoreL(CMsvStore& aStore);
#endif	// __HIDE_MESSAGING_API_V1__

	IMPORT_C TBool ConditionsMetL(TMsvSendErrorAction& aErrorAction);

	/** Default send error action. */
	TMsvSendErrorAction iDefault;

private:

#ifndef __HIDE_MESSAGING_API_V1__		
	void ExternalizeL(RWriteStream&) const;
	void InternalizeL(RReadStream&);
#endif	// __HIDE_MESSAGING_API_V1__

	void GetConditionVariablesL(CArrayFix<TUid>& aUids) const;
	TBool CheckStates(const CArrayFix<TInt>& aStates, TMsvSendErrorAction& aErrorAction) const;
	TBool ConditionOK(const TMsvSysAgentConditionAction& aCondAction, const TInt aState) const;
	
#ifndef __MESSAGING_API_V2__
	RSystemAgent iAgent;
	TBool iAgentConnected;
#endif // __MESSAGING_API_V2__
	};

#endif	// __MSVSYSAGENTCONDACTION_H__
