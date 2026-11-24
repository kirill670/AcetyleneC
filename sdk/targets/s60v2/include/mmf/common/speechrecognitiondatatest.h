//
// SpeechRecognitionDataTest.h
//
// Copyright (c) 2002-2003 Nokia Corporation. All rights reserved
//

#ifndef __SPEECHRECOGNITIONDATATEST_H__
#define __SPEECHRECOGNITIONDATATEST_H__

//  INCLUDES
#include <e32base.h>

/**
@publishedAll
@released

Class to encapsulate diagnostic parameter values.

@since  2.0
*/

class TDiagnostic
{
public:// Constructors and destructor
	/**
    Two-phased constructor.
	*/
	IMPORT_C TDiagnostic();

	/**
	Destructor.
	*/
	IMPORT_C ~TDiagnostic();

public:
	/** Signal to noise ratio.
	*/
	TInt32 iSNR;
	/** Whether the recognition result was accepted.
	*/
	TBool iAccepted;
	/** Controller specific diagnostic data related to the recognition result.
	*/
	TPtr iData;
};

#endif // __SPEECHRECOGNITIONDATATEST_H__
