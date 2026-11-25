// UnitTest.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file UnitTest.h
	Comments : This file contains the definition of the class CUnitTest
				This file comment is for DOxygen only and is ignored by EDoc.
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __UNITTEST_H__
#define __UNITTEST_H__

#include <e32base.h>
#include <f32file.h>

#include "TestUtilities.h"
#include "Transition.h"
#include "UnitTestInfo.h"
#include "UnitTestObserver.h"

class CTransition;
class CDataLogger;

/**
	@public
	@class CUnitTest
	Dependencies : CTimer, MTransitionObserver
	Comments : Abstract base class upon which a test developer can base his unit test class.
	Most functionality is implemented in this base class, to write a derived class just implement 
	a NewL() and a ConstructL() on the new object.  ConstructL() should first call 
	UnitTestConstructL() and then create the transitions which make up this unit test.
	Eg. 
	@code
		_LIT(KExampleUnitTest,"CExampleUnitTest");

		CExampleUnitTest* CExampleUnitTest::NewL(CDataLogger&		aDataLogger,
												 MUnitTestObserver& aObserver)
			{
			CExampleUnitTest* self = new(ELeave) CExampleUnitTest(aDataLogger,
																  aObserver);
			self->ConstructL();
			return self; 
			}

		TInt CExampleUnitTest::RunError(TInt aError)
			{
			// The RunL left so chain to the base first and then cleanup
			TInt error = CUnitTest::RunError(aError);	// Chain to base
			delete iTestClass;
			iTestClass = NULL;
			return error;
			}

		CExampleUnitTest::~CExampleUnitTest()
			{
			// delete the test context information
			delete iStateAccessor;
			delete iUTContext;
			delete iValidator;

			// Simply delete our test class instance
			delete iTestClass;
			}

		CExampleUnitTest::CExampleUnitTest(CDataLogger& aDataLogger,
											MUnitTestObserver& aObserver, 
											MStateAccessor& aStateAccessor)
		: CUnitTest(KExampleUnitTest, aDataLogger, aObserver, aStateAccessor)
			{
			//Do nothing
			}

		// Now the Individual transitions need to be added.
		void CExampleUnitTest::ConstructL()
			{
			// Perform base class initialization
			UnitTestConstructL();

			// Create the input variables to the transition creation
			iStateAccessor = new(ELeave) TExampleStateAccessor();
			iUTContext = new(ELeave) CUnitTestContext(iDataLogger, *iStateAccessor, *this);
			iValidator = new(ELeave) TTransitionValidator(*iUTContext);

			// Add the Transitions in the order they are to run
			// C'tor first, D'tor last...
			AddTransitionL(new(ELeave)CExampleNewLTransition(*iUTContext, *iValidator, iTestClass));
			AddTransitionL(new(ELeave)CExampleDtorTransition(*iUTContext, *iValidator, iTestClass));
			}
			
	@endcode
 */
//##ModelId=3A23BA9F037C
class CUnitTest : public CTimer, public MTransitionObserver
	{
public:
/**
	@fn				~CUnitTest()
	Intended Usage	:	Standard Destructor
	@since			7.0
 */
	//##ModelId=3A70658A0236
	IMPORT_C ~CUnitTest();

/**
	@fn				void RunTest(TTimeIntervalMicroSeconds32 aTimeAfter = 0)
	Intended Usage	:	Sets up the Timer Object request to cause the test to run.
	Error Condition	:	
	@since			7.0
	@param			aTimeAfter The time after which the unit test should be run
	@pre 			None
	@post			RunL() will be set up to run after the specified time.
 */
	//##ModelId=3A70658A0204
	IMPORT_C void RunTest(TTimeIntervalMicroSeconds32 aTimeAfter = 0);

/**
	@fn				inline const TDesC& UnitTestName() const
	Intended Usage	:	Return the name identifier of this Unit Test
	Error Condition	:	
	@since			7.0
	@return			TDesC& The identifier of this unit test
	@pre 			None
 */
	//##ModelId=3A70658A01E6
	inline const TDesC& UnitTestName() const;

/**
	@fn				TransitionSetL() const
	Intended Usage	:	Creates and returns a CUnitTestInfo containing information on this 
					UnitTest.  Passes ownership of the CUnitTestInfo to the calling object.
	Error Condition	:	
	@since			7.0
	@return			CUnitTestInfo* Information on this unit test
	@pre 			None
 */
	//##ModelId=3A70658A01DC
	CUnitTestInfo* TransitionSetL() const;

/**
	@fn				GetCurrentTransition() const
	Intended Usage	: Retrieve a reference to the transition whose RunL() method 
					is currently executing.
					This allows transition information can be retrieved and 
					RepeatOnce() can be called on the transition.
	@since			7.0
	@return			CTransition& a reference to the currently executing transition. 
	@pre 			None
	@post			No change.
 */
	//##ModelId=3AC9D0610040
	IMPORT_C CTransition& GetCurrentTransition() const;

/**
	@fn				SetCurrentTransition(CTransition& aTransition)
	Intended Usage	: MTransitionObserver override that recieves a reference to
					the transition whose RnunL() method is executing.
					This allows transition information can be retrieved and 
					RepeatOnce() can be called on the transition.
	@since			7.0
	@param			aTransition A reference to the transition to set as current
	@return			void 
	@pre 			None
	@post			aTransition will be recorded as the currently 
					executing transition.
 */
	//##ModelId=3AC9D061000E
	IMPORT_C void SetCurrentTransition(CTransition& aTransition);

/**
	@fn				Complete(CTransition& aTransition, TInt aAsyncPostCheckError)
	Intended Usage	: MTransitionObserver override that is called to indicate 
					that an asynchronous function on the specified
					transition has completed.	
	@since			7.0
	@param			aTransition The transition which has completed an async function.
	@param			aAsyncPostCheckError An error code from the second phase of post-condition
					validation done after the transition's asynchronous request had completed.
					Used for asynchronous transitions only - for synchronous transitions, 2-phase
					post-condition checking does not apply, and a value of KErrNone is supplied.
	@pre 			The specified transition has launched an asynchronous function
	@post			The transition has fully completed, if all transitions are complete
					then the unittest is complete.
 */
	//##ModelId=3A9277480236
	IMPORT_C void Complete(CTransition& aTransition, TInt aAsyncPostCheckError);

/**
	@fn				SetParametersL(TAny* aParams)
	Intended Usage	:	Should be overridden in the derived unit test to accept parameters
	to be used in the unit test.  The default implementation is to do nothing.
	Error Condition	:	
	@since			7.0
	@param			aParams The parameter block which the unit test will use
	@pre 			This CUnitTest is constructed
	@post			The parameters are stored and ready for use in the test
 */
	//##ModelId=3A9F862C0248
	IMPORT_C virtual void SetParametersL(TAny* aParams);

/**
	@fn				PrepareUnitTestL()
	Intended Usage	:	May be overidden in the derived unit test to perform any unit test
					specific environment setup (eg copying data files into place).  The 
					default implementation is to do nothing.
	Error Condition	:	Depends on implementation.
	@since			7.0
	@pre 			This CUnitTest is constructed
	@post			Depends on implementation
 */
	//##ModelId=3B449E930041
	virtual void PrepareUnitTestL();

protected:
/**
	@fn				inline CUnitTest(const TDesC&		  aName, 
									 CDataLogger&		  aDataLogger, 
									 MUnitTestObserver&   aUnitTestObserver)
	Intended Usage	:	Standard Constructor
	Error Condition	:	
	@param			aName The identifier of this unit test
	@param			aDataLogger Provides the logging capability
	@param			aUnitTestObserver Is informed when this unit test completes
	@since			7.0
 */
	//##ModelId=3A70658A01AA
	inline CUnitTest(const TDesC&		  aName, 
					 CDataLogger&		  aDataLogger, 
					 MUnitTestObserver&   aUnitTestObserver);

/**
	@fn				virtual void RunL()
	Intended Usage	:	Implementation of CActive method.  Each iteration of RunL() causes one transition
	to be run.
	Error Condition	:	
	@since			7.0
	@pre 			Preconditions are ensured by RunTest()
	@post			Transition has been activated
 */
	//##ModelId=3A76AEEC019B
	IMPORT_C virtual void RunL();

/**
	@fn				IMPORT_C virtual void ConstructL() = 0
	Intended Usage	:	Must be overridden in derived class to complete construction
	Error Condition	:	
	@since			7.0
 */
	//##ModelId=3A76AEEC0173
	IMPORT_C virtual void ConstructL() = 0;

/**
	@fn				IMPORT_C void UnitTestConstructL()
	Intended Usage	:	Called from derived class construction to perform all base
						class initialisation.
	Error Condition	:	
	@since			7.0
	@pre 			Should be called during construction of the derived class to perform base class
					initialisation.
	@post			Unspecified
 */
	//##ModelId=3A76AEEC015F
	IMPORT_C void UnitTestConstructL();

/**
	@fn				IMPORT_C void AddTransitionL(CTransition* aTransition)
	Intended Usage	:	Adds the transition to the list to be run during this unit test
	@exception		KErrNoMemory
	@since			7.0
	@param			aTransition The transition to be added to the list
	@pre 			Should be used in developer implemented ConstructL() to add transitions to the
					Unit Test
	@post			The specified transition is added to the list to be run for this unit test
 */
	//##ModelId=3A93A42B020E
	IMPORT_C void AddTransitionL(CTransition* aTransition);

/**
	@fn				IMPORT_C void AddBlockingTransitionL(CTransition* aTransition)
	Intended Usage	:	Adds a transition to the unit test which will block until all
					previous asynchronous transitions have completed before running.
	@exception		KErrNoMemory
	@since			7.0
	@param			aTransition The transition to be added to the list
	@pre 			Should be used in developer implemented ConstructL() to add transitions to the
					Unit Test
	@post			The specified transition is added to the list to be run for this unit test
 */
	//##ModelId=3A76AEEC010F
	IMPORT_C void AddBlockingTransitionL(CTransition* aTransition);

/**
	@fn				virtual void DoCancel()
	Intended Usage	:	Standard Active Object method for cancelling the current request
	@since			7.0
	@pre 			None
	@post			Any outstanding requests are cancelled
 */
	IMPORT_C virtual void DoCancel();

	//##ModelId=3B449E920393
	IMPORT_C void AddLeaveErrorCodeL(TInt aLeaveErrorCode);
	

protected:
/** The identifier of this Unit Test*/
	//##ModelId=3A70658A0183
	const TDesC&	iUnitTestName;
/** List of the transitions which make up this Unit Test*/
	//##ModelId=3A70658A016F
	RPointerArray<CTransition>* iTransitions;
/** The test logging mechanism*/
	//##ModelId=3A41E4CD0328
	CDataLogger&	iDataLogger;
/** Used to call back to the test controller that the test has finished*/
	//##ModelId=3A71470502BA
	MUnitTestObserver&	iUnitTestObserver;
/** The index in iTransitions of the next transition to be run */
	//##ModelId=3A7FF34D00D9
	TInt					iNextTransitionIndex;
/** List of the asyncronous transitions which have requests outstanding */
	//##ModelId=3A92774801F0
	RPointerArray<CTransition>* iOutstandingTransitions;
/** Indicates that the next transition is waiting for the completion of async requests 
	before it will be run*/
	//##ModelId=3A93A42B01D1
	TBool iWaitingForCompletion;
/** The currently executing transition : NOT OWNED */
	//##ModelId=3AC9D06003BA
	CTransition* iCurrentlyExecutingTransition;
/** List of all the acceptable error codes */	
	//##ModelId=3B449E92037F
	RArray<TInt> iLeaveErrorArray;
/** Connection to the file server - required by iFileMan */	
	//##ModelId=3B449E920361
	RFs iFs;
/** File manager - useful in PrepareUnitTestL if copying files is required */
	//##ModelId=3B449E920343
	CFileMan* iFileMan;

	friend class TUnitTest_StateAccessor;
	};

#include "UnitTest.inl"

#endif
