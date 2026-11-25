// TestSuite.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// This contains CTestSuite which is the Abstract base class 
// for all the TestSuite DLLs

#if (!defined __TESTSUITE_H__)
#define __TESTSUITE_H__

#define MAX_LEN_TEST_SUITE_NAME 20

class CTestStep;

// Abstract base class for all test suites
class CTestSuite : public CBase
{
public:
	// second phase constructor
	IMPORT_C void ConstructL( CLog * pLogSystem );

	// destructor
	IMPORT_C virtual ~CTestSuite();

	// the name of this suite
	TBuf<MAX_LEN_TEST_SUITE_NAME> iSuiteName;

	// add a test step to the suite
	IMPORT_C void AddTestStepL( CTestStep * ptrTestStep );

	// public interface to run test steps
	IMPORT_C enum TVerdict DoTestStep( TPtrC step, TPtrC config );

	// test suite second phase initialisation 
	// pure-virtual all test suites must implement this
	// this is called from CTestSuite::ConstructL 
	virtual void InitialiseL( void ) = 0;

	// this should be a pure virtual so every test ddl
	// has to provide a version but for now defaults to ?.?
	IMPORT_C virtual TPtrC GetVersion( void );

	// control log display operation
	IMPORT_C void SetBufferDisplay( TBool aBufferDisplay );

	// logging to file and console
	IMPORT_C void Log( TRefByValue<const TDesC16> format, ... );

	// log data buffer
	TBuf<32384>		iLogData;

protected:
	
	// array of pointers to the test steps in this suite
	CArrayPtrFlat<CTestStep> *	iArrayTestSteps;

	// pointer to LogSystem for console display and file logging
	CLog * iLogSystem;

	// switch between buffered log display and real-time
	// ETrue = buffered display, EFalse = real-time
	TBool iBufferDisplay;

};

#endif /* __TESTSUITE_H__ */
