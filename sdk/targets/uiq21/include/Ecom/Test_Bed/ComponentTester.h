// ComponentTester.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file ComponentTester.h
	Comments : This file contains the definition of the class CComponentTester
				This file comment is for DOxygen only and is ignored by EDoc.
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __COMPONENTTESTER_H__
#define __COMPONENTTESTER_H__

#include <e32base.h>

#include "UnitTestInfo.h"
#include "UnitTest.h"
#include "DataLogger.h"
#include "ComponentTestObserver.h"

class CDataLogger;

/**
	@public
	@struct TTestInfo
	Dependencies : None
	Comments : Used by the UI component to pass in a list of the tests which are to run
	with information about each one.
 */
//##ModelId=3A9F862F0224
struct TTestInfo
	{
/** The zero-based component Id based on the list passed out from 
	CTestController::FindComponents */
	//##ModelId=3AC9D06401A5
	TInt	iComponentId;
/** The zero-based unit test Id within the above component */
	//##ModelId=3AC9D06401A0
	TInt	iUnitTestId;
/** The time at which this unit test should be scheduled to run */
	//##ModelId=3AC9D064019B
	TTimeIntervalMicroSeconds32 iRunTime;
/** Parameter block which is to be passed to the unit test */
	//##ModelId=3AC9D0640191
	TAny*	iParameters;
	};

/**
	@public
	@class CComponentTester
	Dependencies : CActive, MUnitTestObserver
	Comments : Abstract class from which developers can derive their own component testing
	classes.  To write a derived class just implement a NewLC() and a ConstructL() from 
	which ComponentTesterConstructL() should be the first thing called.
 */
//##ModelId=3A24DC16022F
class CComponentTester : public CActive, public MUnitTestObserver
	{
public:
/**
	@fn				 ~CComponentTester()
	Intended Usage	: Standardized virtual destruction method 
	@since			7.0
 */
	//##ModelId=3A70658C0012
	IMPORT_C ~CComponentTester();

/**
	@fn				IMPORT_C virtual void TestComponent(RPointerArray<TTestInfo>* aTests)
	Intended Usage	:	Called to perform a full test of the component. Runs the listed 
					tests or all unit tests if aTests == 0
	Error Condition	:	
	@since			7.0
	@param			aTests The list of tests to run, 0 means run all tests
	@pre 			This CComponentTester is fully initialized
	@post			All unit tests will be set up to run
 */
	//##ModelId=3A34E609008C
	IMPORT_C virtual void TestComponent(RPointerArray<TTestInfo>* aTests);

/**
	@fn				IMPORT_C RPointerArray<CUnitTestInfo>* TransitionSetsL() const
	Intended Usage	:	Called to provide a list of the transition sets in this component test.
						Ownership of the array is passed to the calling object.
	Error Condition	:	
	@since			7.0
	@return			RPointerArray<CUnitTestInfo>* Information on the unit tests contained
	in this component.  Ownership of the array is passed to the calling object.
	@pre 			None
 */
	//##ModelId=3A70658B03E7
	IMPORT_C RPointerArray<CUnitTestInfo>* TransitionSetsL() const;

/**
	@fn				IMPORT_C void Complete(CUnitTest* aUnitTest)
	Intended Usage	:	Used, by the observed unit test, to indicate that the 
					test has completed
	Error Condition	:	
	@since			7.0
	@param			aUnitTest	The unit test which has completed.
	@pre 			None
	@post			If this was the last unit test then iObserver is informed that this 
	component is complete.
 */
	//##ModelId=3A7147060397
	IMPORT_C void Complete(CUnitTest* aUnitTest);

protected:
/**
	@fn				 IMPORT_C CComponentTester(CDataLogger&				aDataLogger, 
											   MComponentTestObserver&	aObserver)
	Intended Usage	: Default Constructor	
	@since			7.0
	@param 			aDataLogger Used for file logging capability
	@param 			aObserver To inform of completion of all tests
 */
	IMPORT_C CComponentTester(CDataLogger&			  aDataLogger, 
							  MComponentTestObserver& aObserver);

/**
	@fn				IMPORT_C void AddUnitTestL(const CUnitTest* aUnitTest)
	Intended Usage	:	Used by derived class to add UnitTests to the list
	Error Condition	:	
	@since			7.0
	@param			aUnitTest The UnitTest to be added
	@pre 			None
	@post			The specified unit test is added to the list of tests to be executed.
 */
	//##ModelId=3A76AEED020B
	IMPORT_C void AddUnitTestL(const CUnitTest* aUnitTest);

/**
	@fn				IMPORT_C void AddParamUnitTestL(const CUnitTest* aUnitTest)
	Intended Usage	:	Used by derived classes to add UnitTests which can only be run when
	they are supplied with parameters from the UI.
	Error Condition	:
	@since			7.0
	@param			aUnitTest The unit test to add to the list
	@pre 			None
	@post			The specified unit test is added to the list of test to be executed and 
	is flagged as requiring parameters
 */
	//##ModelId=3A9F862D03BC
	IMPORT_C void AddParamUnitTestL(const CUnitTest* aUnitTest);

/**
	@fn				IMPORT_C virtual void ConstructL() = 0
	Intended Usage	:	Standard two-phase construction method.  To be implemented 
	in derived class
	Error Condition	:	
	@since			7.0
	@pre 			First phase of construction is complete
	@post			Object is fully constructed
 */
	//##ModelId=3A76AEED01ED
	IMPORT_C virtual void ConstructL() = 0;

/**
	@fn				IMPORT_C void ComponentTesterConstructL()
	Intended Usage	:	Must be called by derived class ConstructL() to perform base class 
					initialisation.
	Error Condition	:	
	@since			7.0
	@pre 			None
	@post			Object is fully constructed
 */
	//##ModelId=3A76AEED01D9
	IMPORT_C void ComponentTesterConstructL();

/**
	@fn				IMPORT_C void RunL()
	Intended Usage	:	
	Error Condition	:	
	@since			7.0
	@pre 			This CComponentTester is fully constructed
	@post			One of the CUnitTest contained in this CComponentTester has been run
 */
	//##ModelId=3A9E205C00DC
	IMPORT_C void RunL();

/**
	@fn				IMPORT_C void DoCancel()
	Intended Usage	:	
	Error Condition	:	
	@since			7.0
	@pre 			This CComponentTester is fully constructed.
	@post			Any outstanding asynchronous requests are cancelled.
 */
	//##ModelId=3A9E205C00C8
	IMPORT_C void DoCancel();

protected:
/** List of all the unit tests which make up this component test*/
	//##ModelId=3A70658B03DE
	RPointerArray<CUnitTest>* iUnitTests;
/** The test logging mechanism*/
	//##ModelId=3A70658B03C8
	CDataLogger&			iDataLogger;
/** The observer to inform when we have completed the test */
	//##ModelId=3A70658B03B6
	MComponentTestObserver&		iObserver;
/** The index of the unittest which is to be run next */
	//##ModelId=3A714706038D
	TInt						iCurrentUnitTest;
/** The list of tests to run, NULL means run all tests. We take ownership of the list but 
	not the items on it.*/
	//##ModelId=3A9E205C00AA
	RPointerArray<TTestInfo>*	iUnitTestsToRun;
/** A list of the test which cannot run without a parameter set from the UI */
	//##ModelId=3A9F862D03B2
	RArray<TInt>				iParameterizedTests;
/** A placeholder which is only used to ensure correct object cleanup when 
	TransitionSetsL() leaves */
	//##ModelId=3AADFEEB03C2
	mutable RPointerArray<CUnitTestInfo>* iTransitionSets;

	friend class TComponentTester_StateAccessor;
	};

#endif
