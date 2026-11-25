// TestStep.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// This contains CTestCase which is the base class for all the Testcases

#if (!defined __TESTSTEP_H__)
#define __TESTSTEP_H__

#include "CIniData.h"

class CTestSuite;

#define MAX_LEN_TEST_STEP_NAME	20

class CTestStep : public CBase
{
public:

	// construct destruct
	IMPORT_C CTestStep(const TDesC aName); 
	IMPORT_C CTestStep();
	IMPORT_C virtual ~CTestStep();

	// every test step must implement one of these
	virtual enum TVerdict doTestStepL( void ) = 0;
	
	// tests may optionaly implement pre and post ambles
	IMPORT_C virtual enum TVerdict doTestStepPreambleL( void );
	IMPORT_C virtual enum TVerdict doTestStepPostambleL( void );

	// the name of the test step
	TBuf<MAX_LEN_TEST_STEP_NAME> iTestStepName;

	// pointer to suite which owns this test 
	CTestSuite * iSuite;

	// the current test step verdict
	TVerdict iTestStepResult;

	// initialise the config parameter system
	IMPORT_C void LoadConfig( TPtrC config );
	IMPORT_C void UnLoadConfig( void );


protected:

	// read values from the Config file functions
	IMPORT_C TBool GetBoolFromConfig(const TDesC &aSectName,const TDesC &aKeyName,TBool &aResult);
	IMPORT_C TBool GetIntFromConfig(const TDesC &aSectName,const TDesC &aKeyName,TInt &aResult);
	IMPORT_C TBool GetStringFromConfig(const TDesC &aSectName,const TDesC &aKeyName,TPtrC &aResult);

	// test functions
	IMPORT_C void testBooleanTrue( TBool aCondition, char* aFile, TInt aLine );
	IMPORT_C void testBooleanTrueL( TBool aCondition, char* aFile, TInt aLine );
	IMPORT_C void testBooleanTrueWithErrorCode( TBool aCondition, TInt errorCode  , char* aFile, TInt aLine );
	IMPORT_C void testBooleanTrueWithErrorCodeL( TBool aCondition, TInt errorCode  , char* aFile, TInt aLine );
	IMPORT_C void teste( TBool aCondition, TInt value2 );

	// printf format log
	IMPORT_C void Log( TRefByValue<const TDesC16> format, ... );

	IMPORT_C TPtrC EpocErrorToText(TInt aError);

	// config file data
	CIniData *	iConfigData;

	// print buffer used by ErrorToText
	TBuf <20> iPrnBuf;

private:
	// true if ConfigData has been loaded
	TBool   iConfigDataAvailable;
};

// autotest macros mapped to CTestStep functions

// check a boolean is true
#define TESTL(a) testBooleanTrueL(a, __FILE__, __LINE__)
#define TEST(a)  testBooleanTrue(a, __FILE__, __LINE__)

// check a boolean is true if not return error code b
#define TESTE(a, b) testBooleanTrueWithErrorCode(a, b, __FILE__, __LINE__)
#define TESTEL(a, b) testBooleanTrueWithErrorCodeL(a, b, __FILE__, __LINE__)

// leave error code
#define TEST_ERROR_CODE 84	


#endif /* __TESTSTEP_H__ */
