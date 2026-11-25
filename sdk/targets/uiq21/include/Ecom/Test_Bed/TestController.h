//
// TestController.h
// Copyright © 1997-2001 Symbian Ltd. All rights reserved.
//

/** 
	@file TestController.h
	Comments : This file contains the definition of the class CTestController
				This file comment is for DOxygen only and is ignored by EDoc.
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __TESTCONTROLLER_H__
#define __TESTCONTROLLER_H__

#include <e32base.h>

#include "ComponentInfo.h"
#include "TestManager.h"
#include "TransitionObserver.h"
#include "Transition.h"
#include "ManagerObserver.h"

class CComponentTester;
class CDataLogger;

/**
	@public
	@class CTestController
	Dependencies : CBase
	Comments : Manages the whole test procedure.
 */
//##ModelId=3A34E468034A
class CTestController : public CBase, private MManagerObserver
	{
public:
/**
	@fn				static IMPORT_C CTestController* NewL(CActiveScheduler* aScheduler,
														  TLoggingInfo*		aLogInfo = NULL)
	Intended Usage	: Standardized safe construction which leaves nothing on the cleanup stack.
	@exception		KErrNoMemory.
	@since			7.0
	@param 			aScheduler The active scheduler to use,  pass NULL if no scheduler exists
	@param			aLogInfo The logging info to use, defaults to NULL
	@return			CTestController* A pointer to the newly created class.
	@pre 			None
	@post			Nothing is on the CleanupStack
 */
	//##ModelId=3A70658B01BF
	static IMPORT_C CTestController* NewL(CActiveScheduler* aScheduler,
										  TLoggingInfo*		aLogInfo = NULL);

/**
	@fn				static IMPORT_C CTestController* NewLC(CActiveScheduler* aScheduler,
														   TLoggingInfo*	 aLogInfo = NULL)
	Intended Usage	: Standardized safe construction which leaves CTestController* on the cleanup stack.
	@exception		KErrNoMemory.
	@since			7.0
	@param 			aScheduler The active scheduler, if one exists, otherwise NULL
	@param			aLogInfo The logging configuration information
	@return			CTestController* A pointer to the newly created class.
	@pre 			None
	@post			CTestController is on the CleanupStack
 */
	//##ModelId=3A70658B0197
	static IMPORT_C CTestController* NewLC(CActiveScheduler* aScheduler,
										   TLoggingInfo*	 aLogInfo = NULL);

/**
	@fn				 ~CTestController()
	Intended Usage	: Standardized virtual destruction method
	@since			7.0
 */
	//##ModelId=3A70658B0183
	virtual IMPORT_C ~CTestController();

/**
	@fn				Start()
	Intended Usage	:	Starts the testbed and runs all tests on all components.  This 
					function runs synchronously and does not return until all tests 
					are complete.
	@since			7.0
	@pre 			This object is constructed
	@post			Starts the active scheduler and therefore doesn't complete until the 
					active scheduler is stopped.
 */
	IMPORT_C void Start();

/**
	@fn				Start(RPointerArray<TTestInfo>* aTests)
	Intended Usage	:	Starts the specified tests.This function runs 
					synchronously and does not return until all tests are complete.
	@since			7.0
	@param			aTests The list of tests to be run.
	@pre 			This object is constructed
	@post			Starts the active scheduler and therefore doesn't complete until the 
					active scheduler is stopped.
 */
	//##ModelId=3A70658B015B
	IMPORT_C void Start(RPointerArray<TTestInfo>* aTests);

/**
	@fn				Start(TRequestStatus* aStatus)
	Intended Usage	:	Starts the testbed and runs all tests on all components.  This 
					function runs asynchronously and completes aStatus when all tests 
					are complete.
	@since			7.0
	@param			aStatus Status word for the calling function.  Is completed when all 
					tests are complete.
	@pre 			This object is constructed
	@post			An asynchronous request is issued to run all tests.
 */
	IMPORT_C void Start(TRequestStatus* aStatus);

/**
	@fn				Start(TRequestStatus* aStatus, RPointerArray<TTestInfo>* aTests)
	Intended Usage	:	Starts the specified tests.  If the default for aTest is used
					then all tests are run on all components.  This function runs 
					asynchronously and completes aStatus when all tests are complete.
	@since			7.0
	@param			aStatus Status word for the calling function.  Is completed when all 
					tests are complete.
	@param			aTests The list of tests to be run.
	@pre 			This object is constructed.
	@post			An asynchronous request is issued to run the specified tests.
 */
	IMPORT_C void Start(TRequestStatus* aStatus, RPointerArray<TTestInfo>* aTests);

/**
	@fn				RPointerArray<CComponentInfo>& FindComponents() const
	Intended Usage	:	Returns an array of the components available for testing
	Error Condition	:	
	@since			7.0
	@return			RPointerArray<CComponentInfo>& Information on the components which 
					are available for testing.
	@pre 			The object is fully constructed
	@post			Returns an array of the available components which can be used to select
					which test to run.
 */
	//##ModelId=3A34F53D0165
	IMPORT_C const RPointerArray<CComponentInfo>& FindComponents() const;

/**
	@fn				IMPORT_C CDataLogger& DataLogger()
	Intended Usage	:	Returns a reference to the file logging functionality for use 
					by the user interface component.
	@since			7.0
	@return			CDataLogger& The current data logger to allow external logging
	@pre 			The CTestController has been created so that the data logger exists
	@post			Unspecified
 */
	//##ModelId=3A8D59C8022A
	static IMPORT_C CDataLogger& DataLogger();

/**
	@fn				Cancel()
	Intended Usage	:	Cancels any outstanding tests.
	@since			7.0
	@pre 			This object has been created and the asynchronous version of 
					Start has been called.
	@post			Any outstanding tests have been cancelled.
 */
	IMPORT_C void Cancel();

	friend class TTestController_StateAccessor;

private:
/**
	@fn				 CTestController(CActiveScheduler* aScheduler)
	Intended Usage	: Default Constructor
	@since			7.0
	@param 			aScheduler The existing active scheduler or NULL
 */
	//##ModelId=3A70658B0133
	CTestController(CActiveScheduler* aScheduler);

/**
	@fn				void ConstructL(TLoggingInfo* aLogInfo)
	Intended Usage	: Completes the safe construction of the CTestController object
	@exception		KErrNoMemory.
	@since			7.0
	@param			aLogInfo The logging configuration information
	@pre 			First phase of construction is complete
	@post			Object is fully constructed
 */
	//##ModelId=3A70658B011F
	void ConstructL(TLoggingInfo* aLogInfo);

/**
	@fn				void DiscoverTestsL()
	@exception		KErrNoMemory.
	Intended Usage	:	Called during construction to find all test modules
	Error Condition	:	
	@since			7.0
	@pre 			None
	@post			A list of all tests is available
 */
	//##ModelId=3A70658B010B
	void DiscoverTestsL();

/**
	@fn				RPointerArray<CUnitTestInfo>* GetUnitTestsL(TEntry& aEntry)
	Intended Usage	:	Queries a test module to find a list of the unit tests which
						are available for testing.
	Error Condition	:	
	@since			7.0
	@param			aEntry The test module to be queried
	@return			RPointerArray<CUnitTestInfo>* List of the available unit tests
	@pre 			The library which aEntry corresponds to exists and is a test dll
	@post			A list of the unit tests in that dll is returned
 */
	//##ModelId=3A70658B00ED
	RPointerArray<CUnitTestInfo>* GetUnitTestsL(TEntry& aEntry);

/**
	@fn				void ScanDriveL(TDriveUnit aDrive, RFs& aFs)
	Intended Usage	:	Scan a drive for the test dll directory and identify any test DLLs 
						within that directory for addition to the test list.
	Error Condition	:	
	@exception		KErrNoMemory
	@since			7.0
	@param			aDrive The drive to search for tests
	@param			aFs File server reference
	@pre 			None
	@post			Any tests on this drive are added to the list of all tests
 */
	//##ModelId=3A70658B00BB
	void ScanDriveL(TDriveUnit aDrive, RFs& aFs);

/**
	@fn				TestsComplete()
	Intended Usage	:	Called by the CTestManager to indicate that all tests
					are complete.  Either stops the active scheduler if in 
					synchronous mode or completes the client if in async mode.
	@since			7.0
	@pre 			This object is constructed
	@post			Appropriate action is taken to complete the tests.
 */
	void TestsComplete();

private:
/** Starts the tests and stops the active scheduler when finished*/
	//##ModelId=3A70658B00A7
	CTestManager*			iTestManager;
/** A list of the available tests*/
	//##ModelId=3A70658B0093
	RPointerArray<CComponentInfo>	iTestList;
/** Placeholder for an active scheduler if one is passed in on creation */
	//##ModelId=3A76AEEC03AE
	CActiveScheduler*	iScheduler;
/** Flag indicating if we own the active scheduler in iScheduler */
	//##ModelId=3A76AEEC039C
	TBool				iOwnScheduler;
/** Provides the file logging capability */
	//##ModelId=3A8D59C801E4
	CDataLogger*		iDataLogger;
/** The status word of the client (if tests were run asynchronously). To be completed
	when all tests have finished running. */
	TRequestStatus* iClientStatus;
	};  // End of CTestController definition


#endif // _INC_TESTCONTROLLER_3A34E468034A_INCLUDED
