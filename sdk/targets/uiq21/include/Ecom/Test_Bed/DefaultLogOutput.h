// DefaultLogOutput.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file DefaultLogOutput.h
	Comments : This file contains the definition of the class CDefaultLogOutput
				This file comment is for DOxygen only and is ignored by EDoc.
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __DEFAULTLOGOUTPUT_H__
#define __DEFAULTLOGOUTPUT_H__

#include <e32base.h>
#include <flogger.h>

#include "DataFormat.h"

/**
	@public
	@class CDefaultLogOutput
	Dependencies : CBase, MLogOutput, TDesC, RFileLogger
	Comments : Default implementation of the MLogOutput interface.  This will be used
	if an alternative is not supplied at construction of the CTestController.
 */
//##ModelId=3A9A54CF018D
class CDefaultLogOutput : public CBase, public MLogOutput
	{
public:
/**
	@fn				CDefaultLogOutput(const TDesC& aTitle)
	Intended Usage	:	Standard constructor
	@exception		KErrNoMemory
	@since			7.0
	@param			aTitle The title to be used in the log
 */
	//##ModelId=3A9A54CF01B5
	explicit CDefaultLogOutput(const TDesC& aTitle);

/**
	@fn				~CDefaultLogOutput()
	Intended Usage	:	Standard destructor
	@since			7.0
 */
	//##ModelId=3A9A54CF01AF
	~CDefaultLogOutput();

/**
	@fn				TInt OpenL()
	Intended Usage	:	Opens the RFileLogger ready for logging
	Error Condition	:	Fails to connect to RFileLogger
	@exception		@see RFileLogger::Connect()
	@since			7.0
	@pre 			This object is fully constructed
	@post			RFileLogger is opened and ready for logging
 */
	//##ModelId=3A9A54CF01AE
	void OpenL();

/**
	@fn				void Write(const TDesC& aOutput)
	Intended Usage	:	Outputs the specified message to RFileLogger
	@since			7.0
	@param			aOutput The descriptor to be logged
	@pre 			OpenL has previously been called
	@post			The descriptor has been written to RFileLogger
 */
	//##ModelId=3A9A54CF01AC
	void Write(const TDesC& aOutput);

/**
	@fn				void Close()
	Intended Usage	:	Closes RFileLogger when logging has completed
	@since			7.0
	@pre 			OpenL has previously been called
	@post			RFileLogger has been closed and this object can be deleted
 */
	//##ModelId=3A9A54CF01AB
	void Close();

protected:
/** The title which is output to the log file */
	//##ModelId=3AC9D0610146
	const TDesC&	iTitle;
/** Handle to the file logging mechanism for outputting messages */
	//##ModelId=3AC9D061013C
	RFileLogger		iFLogger;
	};

#endif	// __DEFAULTLOGOUTPUT_H__
