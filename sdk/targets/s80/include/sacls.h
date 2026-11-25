// SACLS.H
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//

#ifndef __SACLS_H__
#define __SACLS_H__


/**
Constants
@internalComponent
*/
const TInt KNullState = 0;


/**
System agent maintained entries
@internalComponent
*/
const TInt KUidProfileValue		=0x100052D2;
const TUid KUidProfile			={KUidProfileValue};

/**
@internalComponent
*/
const TInt KUidPhonePwrValue=0x100052C5;
const TUid KUidPhonePwr={KUidPhonePwrValue};

/**
@internalComponent
*/
enum TSAPhoneStatus
	{
	ESAPhoneOff,
	ESAPhoneOn
	};

/**
@internalComponent
*/
const TInt KUidSIMStatusValue	=0x100052C6;
const TUid KUidSIMStatus		={KUidSIMStatusValue};

/**
@internalComponent
*/
enum TSASIMStatus
	{
	ESASimOk,
	ESASimNotPresent,
	ESASimRejected
	};

/**
@internalComponent
*/
const TInt KUidNetworkStatusValue=0x100052C7;
const TUid KUidNetworkStatus	={KUidNetworkStatusValue};

/**
@internalComponent
*/
enum TSANetworkStatus
	{
	ESANetworkAvailable,
	ESANetworkUnAvailable
	};

/**
@internalComponent
*/
const TInt KUidNetworkStrengthValue  =0x100052C8;
const TUid KUidNetworkStrength  ={KUidNetworkStrengthValue};

/**
@internalComponent
*/
enum TSANetworkStrength
	{
	ESANetworkStrengthNone,
	ESANetworkStrengthLow,
	ESANetworkStrengthMedium,
	ESANetworkStrengthHigh,
	ESANetworkStrengthUnknown
	};

/**
@internalComponent
*/
const TInt KUidChargerStatusValue	=0x100052C9;
const TUid KUidChargerStatus	={KUidChargerStatusValue};

/**
@internalComponent
*/
enum TSAChargerStatus
	{
	ESAChargerConnected,
	ESAChargerDisconnected,
	ESAChargerNotCharging
	};

/**
@internalComponent
*/
const TInt KUidBatteryStrengthValue  =0x100052CA;
const TUid KUidBatteryStrength  ={KUidBatteryStrengthValue};

/**
@internalComponent
*/
enum TSABatteryStrength
	{
	ESABatteryAlmostEmpty,
	ESABatteryLow,
	ESABatteryFull
	};

/**
@internalComponent
*/
const TInt KUidCurrentCallValue	=0x100052CB;
const TUid KUidCurrentCall		={KUidCurrentCallValue};

/**
@internalComponent
*/
enum TSACurrentCall
	{
	ESACallNone,
	ESACallVoice,
	ESACallFax,
	ESACallData,
	ESACallAlerting,
	ESACallRinging,
	ESACallAlternating,
	ESACallDialling,
	ESACallAnswering,
	ESACallDisconnecting
	};

/**
@internalComponent
*/
const TInt KUidDataPortValue	=0x100052CC;
const TUid KUidDataPort			={KUidDataPortValue};

/**
@internalComponent
*/
enum TSAPort
	{
	ESADataPortIdle,
	ESADataPortBusy	
	};

/**
@internalComponent
*/
const TInt KUidInboxStatusValue	=0x100052CD;
const TUid KUidInboxStatus		={KUidInboxStatusValue};

/**
@internalComponent
*/
enum TSAInboxStatus
	{
	ESAInboxEmpty,
	ESADocumentsInInbox
	};

/**
@internalComponent
*/
const TInt KUidOutboxStatusValue=0x100052CE;
const TUid KUidOutboxStatus		={KUidOutboxStatusValue};

/**
@internalComponent
*/
enum TSAOutboxStatus
	{
	ESAOutboxEmpty,
	ESADocumentsInOutbox
	};

/**
@internalComponent
*/
const TInt KUidClockValue		=0x100052CF;
const TUid KUidClock			={KUidClockValue};

/**
@internalComponent
*/
enum TSAClock
	{
	ESAAm,
	ESAPm
	};

/**
No longer used
@internalComponent
*/
const TInt KUidAlarmValue		=0x100052D0;
const TUid KUidAlarm			={KUidAlarmValue};

/**
@internalComponent
*/
enum TSAAlarm
	{
	ESAAlarmOff,
	ESAAlarmOn,
	};

/**
@internalComponent
*/
const TInt KUidIrdaStatusValue	=0x100052D1;
const TUid KUidIrdaStatus		={KUidIrdaStatusValue};

/**
@internalComponent
*/
enum TSAIrdaStatus
	{
	ESAIrLoaded,		//IRDA Irlap layer loaded
	ESAIrDiscoveredPeer,//Discovery begin
	ESAIrLostPeer,		//Discovery end
	ESAIrConnected,		//IRDA Irlap layer connected
	ESAIrBlocked,		//IRDA Irlap layer blocked
	ESAIrDisConnected,	//IRDA Irlap layer disconnected
	ESAIrUnloaded		//IRDA Irlap layer unloaded
	};



/** An enumeration whose enumerators define the type of test to be made against 
a state variable. The test type forms part of the condition specified by a 
TSysAgentCondition object.

Note: The enum is a part of SystemAgent services and it is deprecated now. Use 
P&S services.

@see TSysAgentCondition 
@see RProperty
@publishedAll
@deprecated
*/
enum TSysAgentConditionType
	{
	/** Tests that a value is equal to a state variable value. */
	ESysAgentEquals=32,		
	/** Tests that a value is unequal to a state variable value. */
	ESysAgentNotEquals,		
	/** Tests that a value is greater than a state variable value. */
	ESysAgentGreaterThan,	
	/** Tests that a value is less than a state variable value. */
	ESysAgentLessThan		
	};



/** Defines a condition which a state variable must satisfy.

A condition encapsulates three pieces of information:

the UID identifying the state variable against which a test is to be made.

the value against which that state variable is to be tested.

the type of test to be made.

A client of the System Agent, which needs to know when state variables have 
satisfied a set of conditions, must construct these conditions and pass them 
to the System Agent through the standard client handle, a RSystemAgent object, 
as a NotifyOnCondition() request.

Note: The class is a part of SystemAgent services and it is deprecated now. Use 
P&S services.

@see RSystemAgent::NotifyOnCondition()
@see TUid 
@see RProperty
@publishedAll
@deprecated
*/
class TSysAgentCondition
	{
public:
	inline TSysAgentCondition();
	inline TSysAgentCondition(TUid aVariable, TInt aState, TSysAgentConditionType aType);

public:
	TUid iVariable;
	TInt iState;
	TSysAgentConditionType iType;
	};


/** Constructs the object with default values.

The UID identifying the state variable against which a test is to be made 
is set to KNullUid.

The value against which that state variable is to be tested is set to KNullState.

The type of test to be made is set to ESysAgentEquals. 
@deprecated
*/
inline TSysAgentCondition::TSysAgentCondition()
:	iVariable(KNullUid), iState(KNullState), iType(ESysAgentEquals)
	{
	}

/** Constructs the object with the specified values.

@param aVariable The UID identifying the state variable against which a test 
is to be made.
@param aState The value against which the state variable identified by the 
specified UID is to be tested.
@param aType The type of test to be made. 
@deprecated
*/
inline TSysAgentCondition::TSysAgentCondition(TUid aVariable, TInt aState, TSysAgentConditionType aType)
:	iVariable(aVariable), iState(aState), iType(aType)
	{
	}

/**
@internalComponent
*/
IMPORT_C TInt StartSystemAgent(TAny* aAny);

#endif
