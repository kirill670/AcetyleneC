// Transition.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file Transition.h
	Comments : This file contains the definition of the class CTransition
				This file comment is for DOxygen only and is ignored by EDoc.
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_TRANSITION_3A23BFC30021_INCLUDED
#define _INC_TRANSITION_3A23BFC30021_INCLUDED

#include <e32base.h>

#include "TestUtilities.h"
#include "StateAccessor.h"
#include "TransitionObserver.h"

class CDataLogger;

/**
	@internal
	@class CUnitTestContext
	@Dependencies CBase 
	Comments : Provide the base class definition for a Unit Test's specific data.  This class
	is CBase derived so that test developers can derive from this class and add owned member 
	data if they wish.
 */
//##ModelId=3A9E205C014A
class CUnitTestContext : public CBase
	{
public:
/**
	@fn				CUnitTestContext(CDataLogger& aDataLogger, 
										MStateAccessor& aAccessor,
										MTransitionObserver& aObserver)
	Intended Usage	: Default constructor.
	@since			7.0
	@param			aDataLogger The output logging object.
	@param			aObserver The observer of this UnitTest's Transitions.
	@param			aAccessor WhiteBox state access to the class under test.
	@pre 			None.
	@post			CUnitTestContext is fully constructed, and initialized.
*/
	//##ModelId=3A9E205C0192
	CUnitTestContext(CDataLogger&			aDataLogger, 
					MStateAccessor&			aAccessor,
					MTransitionObserver&	aObserver);

/**
	@fn				CDataLogger& DataLogger() const
	Intended Usage	:	Provides access to the CDataLogger
	@since			7.0
	@return			A reference to a CDataLogger
	@pre 			Object is fully constructed
 */
	//##ModelId=3A9E205C0191
	CDataLogger& DataLogger() const;

/**
	@fn				MTransitionObserver& TransitionObserver() const
	Intended Usage	:	Provides access to the MTransitionObserver
	@since			7.0
	@return			A reference to an MTransitionObserver
	@pre 			Object is fully constructed
 */
	//##ModelId=3A9E205C0190
	MTransitionObserver& TransitionObserver() const;

/**
	@fn				MStateAccessor& StateAccessor() const
	Intended Usage	:	Provides access to the MStateAccessor
	@since			7.0
	@return			A reference to an MStateAccessor
	@pre 			Object is fully constructed
 */
	//##ModelId=3A9E205C0186
	MStateAccessor& StateAccessor() const;

protected:
	/** The output logging object. */
	//##ModelId=3AC9D0620222
	CDataLogger&			iDataLogger;
	/** The observer of this UnitTest's Transitions. */
	//##ModelId=3AC9D0620210
	MTransitionObserver&	iObserver;
	/** WhiteBox state access to the class under test. */
	//##ModelId=3AC9D0620206
	MStateAccessor&			iStateAccessor;
	};

/**
	@public
	@enum TTestBedAsyncState
	Dependencies : None
	Comments : Represents the possible states of an asynchronous transition when 
	ValidatePostConditions is called. EAsyncCalled means the async request has been made but
	not satisfied, EAsyncCompleted is when the request has been satisfied.
 */
enum TTestBedAsyncState {EAsyncCalled, EAsyncCompleted};

/**
	@public
	@class TTransitionValidator
	Dependencies : None
	Comments : Placeholder for the functions which validate the state of a transition
	before and after its execution.
 */
//##ModelId=3A9E205E01ED
class TTransitionValidator
	{
public:
/**
	@fn				TTransitionValidator(CUnitTestContext& aUTContext)
	Intended Usage	:	Standard constructor
	@since			7.0
	@param			aUTContext The context within which this transition is executing
 */
	//##ModelId=3A9E205E020D
	TTransitionValidator(CUnitTestContext& aUTContext);

/**
	@fn				~TTransitionValidator()
	Intended Usage	: Standard Destructor.
	Error Condition	: None.	
	@since			7.0
*/
	//##ModelId=3AADFEEE0254
	virtual ~TTransitionValidator();

/**
	@fn				virtual TBool ValidatePreConditions()
	Intended Usage	:	Overridden in the derived transition to check the transition pre
	conditions.
	@since			7.0
	@return			TBool ETrue if the Preconditions were valid, EFalse if not.
	@pre 			This CTransition is fully constructed
	@post			Returns the validity of the preconditions
 */
	//##ModelId=3A9E205E020C
	virtual TBool ValidatePreConditions();

/**
	@fn				virtual TBool ValidatePostConditions(TTestBedAsyncState aAsyncState)
	Intended Usage	:	Overridden in the derived transition to check the transition post
	conditions.
	When overriding, if the transition calls an asynchronous function ValidatePostConditions
	will be called twice. Firstly, after the asynchronous function has been called and, 
	secondly, after the asynchronous request has completed.  The parameter aAsyncState can
	be used to distinguish between these two cases.
	@since			7.0
	@param			aAsyncState EAsyncCalled if the async function has been just been called,
	EAsyncCompleted if the function has completed.
	@return			TBool ETrue if the Postconditions were valid, EFalse if not.
	@pre 			This CTransition is fully constructed
	@post			Unspecified
 */
	//##ModelId=3A9E205E0201
	virtual TBool ValidatePostConditions(TTestBedAsyncState aAsyncState);

protected:
/** The context that this transition will be executing in */
	//##ModelId=3AC9D06403D3
	CUnitTestContext& iUTContext;
	};

/**
	@public
	@struct TTransitionInfo
	Dependencies : None
	Comments : Structure for storing the current transition id and iteration number
 */
//##ModelId=3A8276D1009C
struct TTransitionInfo
	{
	//##ModelId=3A8276D100BF
	TTransitionInfo(const TDesC& aTransitionId, 
					CDataLogger& aDataLogger);
/** Descriptor containing the transition identifier */
	//##ModelId=3AC9D064017A
	const TDesC&		iTransitionId;
/** The iteration that this transition is currently on */
	//##ModelId=3AC9D0640170
	TInt				iIteration;
/** The Data Logger that this transition is currently using */
	//##ModelId=3AC9D0640166
	const CDataLogger&	iDataLogger;
	};

const TInt KFirstTransitionIteration = 1;

/**
	@public
	@class CTransition
	Dependencies : CActive
	Comments : Base class from which test developers 
				can derive their own transitions for both
				synchronous and asynchronous methods on
				the test class.
				
				The default behaviour is to log its activity,
				and claim that the pre and post conditions are true.
				The TransitMethodL implementation does nothing.
				To	write a complete test class method transition
				override:
				
				1. The c'tor, (To obtain the test class reference, 
				(or pointer reference for a NewL transit), 
				and any parameters for the TransitMethodL).

				2. SetStartStateL() to set the test class state,
				Using the TStateAccessor provided in the c'tor.

				3. ValidatePreConditions() to test the test class state 
				is valid.

				4. TransitMethodL() to define the transition behaviour,
				calling the method to test with the appropriate parameters.

				5. ValidatePostConditions(), to check the end state is valid.
				
				The simplest case of implementation is to derive an empty 
				class, that relies entirely upon the default behaviour,
				and implement the remaining methods as appropriate.
				(See the the EXAMPLE implementation.)
 */
//##ModelId=3A23BFC30021
class CTransition : public CActive
	{
public:
/**
	@fn				 IMPORT_C ~CTransition()
	Intended Usage	: Standardized virtual destruction method
	@since			7.0
	@pre 			The CTransition exists
	@post			The object has been destroyed
 */
	//##ModelId=3A70658D0031
	IMPORT_C ~CTransition();

/**
	@fn				virtual void SetStartStateL()
	Intended Usage	:	Sets the state of the test object to that specified
	Error Condition	:	
	@since			7.0
	@pre 			The CTransition is instantiated
	@post			The CTransition is in the state specified
 */
	//##ModelId=3A70658D001D
	IMPORT_C virtual void SetStartStateL();

/**
	@fn				IMPORT_C const TDesC& TransitionId() const
	Intended Usage	:	Returns the transition identifier
	Error Condition	:	
	@since			7.0
	@return			const TDesC& The identifier of this transition
	@pre 			The CTransition has been instantiated
 */
	//##ModelId=3A70658C03DD
	IMPORT_C const TDesC& TransitionId() const;

/**
	@fn				IMPORT_C const TTransitionInfo& TransitionInfo() const
	Intended Usage	:	Get information on this transition.  Return struct contains the 
	transition ID, the current iteration and the logging mechanism used by this transition
	Error Condition	:	
	@since			7.0
	@return			const TTransitionInfo Information on the current transition
	@pre 			This CTransition is initialized
 */
	//##ModelId=3A7A7FB001CA
	IMPORT_C const TTransitionInfo& TransitionInfo() const;

/**
	@fn				virtual void RunTransition(TRequestStatus* aUnitTestStatus)
	Intended Usage	:	Indicates that this transition should be run as soon as possible.
	This function calls ValidatePreConditions to ensure the object is in the appropriate start state 
	and then sets the transition active causing its RunL function to be called.
	Error Condition	:	
	@since			7.0
	@param			aUnitTestStatus Status word of the calling CUnitTest
	@pre 			The test object is in an appropriate state for this transition
	@post			The test object is in the end state of this transition
 */
	//##ModelId=3A70658C03C9
	IMPORT_C virtual void RunTransition(TRequestStatus* aUnitTestStatus);

/**
	@fn				IMPORT_C void RepeatOnce()
	Intended Usage	:	Flag this transition to be repeated
	@since			7.0
	@pre 			None
	@post			The iRepeatThis flag is set to true.
 */
	//##ModelId=3A7A7FB001AC
	IMPORT_C void RepeatOnce();

/**
	@fn				IMPORT_C TBool IsBlockingTransition() const
	Intended Usage	:	A blocking transition is one which does not run until all 
					outstanding asynchronous transitions have completed.  This function returns
					whether this is a blocking transition.
					This function does not need to be used by test developers as it is taken 
					care of in the transition and unittest base classes.  Blocking transitions
					can be added using AddBlockingTransitionL() in CUnitTest::ConstructL().
	@since			7.0
	@return			TBool Flag indicating whether this is a blocking transition or not.
	@pre 			None
 */
	//##ModelId=3A93A42D01CA
	IMPORT_C TBool IsBlockingTransition() const;

/**
	@fn				IMPORT_C void SetBlockingTransition(TBool aBlocking)
	Intended Usage	:	A blocking transition is one which does not run until all 
					outstanding asynchronous transitions have completed.
					This function does not need to be used by test developers as it is taken 
					care of in the transition and unittest base classes.  Blocking transitions
					can be added using AddBlockingTransitionL() in CUnitTest::ConstructL().
	@since			7.0
	@param			aBlocking Pass ETrue to set this as a blocking transition
	@pre 			This object is fully constructed
	@post			The blocking status of this CTransition is set
 */
	//##ModelId=3A93A42D0198
	IMPORT_C void SetBlockingTransition(TBool aBlocking);

/**
	@fn				GetErrorCode() const
	Intended Usage	:	Returns the error code last recorded by the transition.
	@since			7.0
	@return			The error code that was last recorded during the transition execution.
	@pre 			This object is fully constructed.
 */
	//##ModelId=3B449E96032A
	IMPORT_C TInt GetErrorCode() const;

protected:
/**
	@fn				 CTransition(const TDesC&			aTransactionId, 
								CUnitTestContext&		aUTContext,
								TTransitionValidator&	aValidator)
	Intended Usage	: Default Constructor
	@param			aTransitionId The identifier of this transition
	@param			aUTContext The context within which this transition should run
	@param			aValidator Provides Pre & Post condition validation
	@since			7.0
	@pre 			None
	@post			First phase of two phase construction is complete
 */
	IMPORT_C CTransition(const TDesC&					aTransitionId, 
							   CUnitTestContext&		aUTContext,
							   TTransitionValidator&	aValidator);

/**
	@fn				virtual void DoCancel()
	Intended Usage	:	Standard Active Object method for cancelling the current request
	Error Condition	:	
	@since			7.0
	@pre 			None
	@post			Any outstanding requests are cancelled
 */
	//##ModelId=3A70658C0383
	IMPORT_C virtual void DoCancel();

/**
	@fn				RunL()
	Intended Usage	:	Implementation of CActive pure virtual method.  For each transition execution 
	RunL is performed twice.
	The first time it calls TransitMethodL() which is the developer defined function which executes the 
	test method.  It then immediately sets itself active and attempts to complete.  If TransitMethodL() 
	called a synchronous function then iStatus will not be KRequestPending and the RunL will be called as
	soon as it is scheduled.  If TransitMethodL() calls an asyncronous function then it will pass iStatus to the function and RunL
	will be called when the asynchronous function completes.
	Whichever method is used the second call of RunL() will complete the request of the CUnitTest which 
	called this transition by setting its status word.  If it has been requested that this transition is
	repeated then the status word will be set to KTestBedRepeatTest.
	Error Condition	:	
	@since			7.0
	@pre 			RunTransition() ensures the preconditions for this function
	@post			After 1st run - test method has been called
					After 2nd run - Unittest has been completed.
 */
	//##ModelId=3A75626E015B
	IMPORT_C virtual void RunL();
	
/**
	@fn				TransitMethodL()
	Intended Usage	:	Calls the method on the class being tested.  If the call is to 
	an asynchronous service provider you must set iStatus to KRequestPending as usual
	Error Condition	:	
	@since			7.0
	@pre 			Preconditions for this transition have been validated
	@post			The test method has been executed
 */
	//##ModelId=3A75626E0133
	IMPORT_C virtual void TransitMethodL() = 0;
	
/**
	@fn				RunError(TInt anErrorCode)
	Intended Usage	:	Called by the active scheduler if RunL leaves
	@since			7.0
	@param			anErrorCode The error code which RunL left with
	@return			KErrNone because if a CTransition::RunL leaves then we simply log
					the event and inform the CUnitTest.
	@pre 			This function is only called by the active scheduler if RunL leaves.
	@post			The owning CUnitTest has been informed that this CTransition left
 */
	//##ModelId=3A892F440175
	IMPORT_C virtual TInt RunError(TInt aErrorCode);

/**
	@fn				PostTransitionCleanup()
	Intended Usage	:	Called from the RunL immediately after TransitMethodL() executes
	@since			7.0
	@pre 			Must be called from RunL only after TransitMethodL() has completed.
	@post			Default behaviour is to do nothing. 
					See the derived classes for additional functionality.
 */
	//##ModelId=3B449E9602B2
	IMPORT_C virtual void PostTransitionCleanup();

protected:
/** The transition identifier*/
	//##ModelId=3A70658C0353
	const TDesC&		iTransitionId;
/** The context in which this transition is running (logging, state accessor & observer) */
	//##ModelId=3A9E205D01D8
	CUnitTestContext&	iUTContext;
/** Used for checking the state of the test object - provides pre and post condition 
	validation functions */
	//##ModelId=3A9E205D01BA
	TTransitionValidator& iValidator;
/** Indicates that this transition should be re-run after the current run */
	//##ModelId=3A7A7FB0016F
	TBool					iRepeatThis;
/** The iStatus of the UnitTest which owns me so that I can complete it */
	//##ModelId=3A7FF34E03DD
	TRequestStatus*			iUnitTestStatus;
/** Indicates that the transition has executed and can be completed */
	//##ModelId=3A7FF34E03C9
	TBool					iTransitionFinished;
/** indicates the code that the RunL left with when completing with a KErrTestBedLeft */
	//##ModelId=3A892F44016B
	TInt iLeaveError;
/** Indicates that this transition should not execute until all previous async transitions
	have finished */
	//##ModelId=3A93A42D0184
	TBool					iBlockingTransition;
/** Indicates that this transition is an asynchronous transition*/
	TBool					iAsyncTransition;
/** Information on this transition including its ID, its iteration number and the data logger
	it is currently using */
	//##ModelId=3AADFEEC03D8
	TTransitionInfo			iTransitionInfo;

/** A friend for self-test operation */
	friend class TTransition_StateAccessor;
	};

#include "Transition.inl"

#endif
