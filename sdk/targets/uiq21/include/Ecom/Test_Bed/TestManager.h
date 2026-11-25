// TestManager.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file TestManager.h
	Comments : This file contains the definition of the class CTestManager
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __TESTMANAGER_H__
#define __TESTMANAGER_H__

#include <e32base.h>

#include "ComponentInfo.h"
#include "Datalogger.h"
#include "ComponentTester.h"
#include "ComponentTestObserver.h"
#include "ManagerObserver.h"

/**
	@public
	@class CTestManager
	Dependencies : CActive, MComponentTestObserver
	Comments : Active object which launches all the tests which the TestController has 
	discovered.  Also, acts as an observer on each CComponentTester waiting for a Complete
	message to indicate the test has finished.
 */
//##ModelId=3A70658C0166
class CTestManager : public CActive, public MComponentTestObserver
	{
public:
/**
	@fn				static CTestManager* NewL(RPointerArray<CComponentInfo>* aTestList,
											  CDataLogger& aDataLogger,
											  MManagerObserver& aObserver)
	Intended Usage	:	Standard two-phase construction which leaves nothing on the 
	CleanupStack
	@since			7.0
	@param			aTestList List of tests available to be performed
	@param			aDataLogger Provides the file logging functionality
	@param			aObserver The object to inform when all the tests are complete
	@return			CTestManager* A pointer to the newly created class
	@pre 			None
	@post			Nothing is left on the CleanupStack
 */
	//##ModelId=3A70658C01E8
	static CTestManager* NewL(RPointerArray<CComponentInfo>* aTestList,
							  CDataLogger& aDataLogger,
							  MManagerObserver& aObserver);

/**
	@fn				~CTestManager()
	Intended Usage	:	Standard destructor
	@since			7.0
 */
	//##ModelId=3A70658C01DF
	~CTestManager();

/**
	@fn				void RunTests(RPointerArray<TTestInfo>* aTests)
	Intended Usage	:	Prepare for the test run.
	Error Condition	:	
	@since			7.0
	@param			aTests The list of tests to run, 0 means all tests
	@pre 			None
	@post			This is active and awaiting call to RunL() by the active scheduler
 */
	//##ModelId=3A70658C01DE
	void RunTests(RPointerArray<TTestInfo>* aTests);

/**
	@fn				void Complete(CComponentTester* aTester, TInt aUnitTestId)
	Intended Usage	:	Callback from the CComponentTester being observed to indicate 
	that it has completed a unit test
	@since			7.0
	@param			aTester The CComponentTester which is signalling
	@param			aUnitTestId The Id of the completed unit test
	@pre 			The specified unit test has been launched
	@post			If all unit tests are complete then the specified CComponentTester has been 
	added to the Garbage list ready for deletion at the next opportunity, this will also 
	unload the appropriate library. Otherwise launch the next unit test.
 */
	//##ModelId=3A70658C01D5
	void Complete(CComponentTester* aTester, TInt aUnitTestId);

/**
	@fn				StartedTests() const
	Intended Usage	:	Returns a flag indicating whether any tests have been started yet
	@since			7.0
	@return			ETrue if any tests have been launched, EFalse otherwise
	@pre 			This object is fully constructed
 */
	TBool StartedTests() const;

protected:
/**
	@fn				CTestManager(RPointerArray<CComponentInfo>* aTestList, 
								 CDataLogger& aDataLogger,
								 MManagerObserver& aObserver)
	Intended Usage	:	Constructor
	@since			7.0
	@param			aTestList The list of tests to be launched by this CTestManager
	@param			aDataLogger The file logging capability
	@param			aObserver The class to inform when all the tests are complete
 */
	//##ModelId=3A70658C01CC
	CTestManager(RPointerArray<CComponentInfo>* aTestList, 
				 CDataLogger& aDataLogger,
				 MManagerObserver& aObserver);

/**
	@fn				void ConstructL()
	Intended Usage	:	Second phase of safe two-phase construction method
	@since			7.0
	@pre 			First phase of construction is complete
	@post			Object is fully constructed and initialized
 */
	//##ModelId=3A70658C01CB
	void ConstructL();

/**
	@fn				void RunL()
	Intended Usage	:	Used to launch each test, in turn, and then to stop the active 
	scheduler when all tests have completed
	@since			7.0
	@pre 			None
	@post			Initially each run of RunL() will result in a ComponentTester being created and
					launched.  Once all the tests have launched RunL() will only be called at completion
					to stop the active scheduler.
 */
	//##ModelId=3A70658C01CA
	void RunL();

/**
	@fn				void DoCancel()
	Intended Usage	:	Standard Active Object method used to cancel any outstanding requests
	Error Condition	:	
	@since			7.0
	@pre 			Object is fully constructed and initialised
	@post			Any outstanding requests have been cancelled.
 */
	//##ModelId=3A70658C01C2
	void DoCancel();

/**
	@fn				void TestComponentL(TInt aComponentIndex)
	Intended Usage	:	Loads the appropriate library and test the specified component
	@since			7.0
	@param			aComponentIndex The zero base index of the component to test
	@pre 			Object is fully constructed and initialised
	@post			Specified component test has been activated to run
 */
	//##ModelId=3A8BBFE70360
	void TestComponentL(TInt aComponentIndex);

/**
	@fn				RunError(TInt aErrorCode)
	Intended Usage	:	Handles the situation where the RunL leaves.  RunL will only leave 
	through a leave from TestComponentL, this will occur if the test to be run fails to 
	construct.
	Error Condition	:	None
	@since			7.0
	@param			aErrorCode The error code which RunL left with.
	@return			KErrNone because we handle the error.
	@pre 			This object is fully constructed and initialized
	@post			The test which failed to construct is cleaned up.
 */
	//##ModelId=3B16364003C4
	TInt RunError(TInt aErrorCode);

protected:
/** The observer to inform when all tests are complete */
	MManagerObserver&	iObserver;
/** List of all the test to be run*/
	//##ModelId=3A71AF8303C5
	RPointerArray<CComponentInfo>*	iTestList;
/** The index (in iTestList) of the test which is to be loaded next*/
	//##ModelId=3A71AF8303BE
	TInt iCurrentTestLoad;
/** The test logging mechanism*/
	//##ModelId=3A71AF8303B9
	CDataLogger&	iDataLogger;
/** Flag indicating that all tests have completed*/
	//##ModelId=3A71AF8303B1
	TBool			iAmStopping;
/** List of the tests to be run, NULL means run all tests */
	//##ModelId=3A9F862E0196
	RPointerArray<TTestInfo>* iTestsToRun;
/** The library containing the test which is currently being run */
	//##ModelId=3B16364003B0
	RLibrary iCurrentLibrary;
/** The test which is currently being run */
	//##ModelId=3B1636400356
	CComponentTester* iCurrentTester;

	friend class TTestManager_StateAccessor;
	};

#endif
