// DataLogger.h
//
// Copyright (c) 1997 - 2001 Symbian Ltd.  All rights reserved.
//

/** 
	@file DataLogger.h
	Comments : This file contains the definition of the class CDataLogger
				This file comment is for DOxygen only and is ignored by EDoc.
	
	@warning This code contains Rose2000 generated ModelId comments
			 used in round trip engineering. Please do not remove.
 */ 

#ifndef __DATALOGGER_H__
#define __DATALOGGER_H__

#include <e32base.h>
#include <Flogger.h>
#include "DataFormat.h"
#include "DefaultLogOutput.h"

/**
	@public
	@class CDataLogger
	Dependencies : CBase
	Comments : Handles the transformation of input data into text suitable 
		for output to a permanent store and the placing of that 
		data in the store.
 */

//##ModelId=3A23B76E01BE
class CDataLogger : public CBase
	{
public:
/**
	@fn				static CDataLogger* NewL(TLoggingInfo* aLogInfo)
	Intended Usage	: Standardized safe construction which leaves nothing on the cleanup stack.
	@exception		KErrNoMemory.	
	@since			7.0
	@param			aLogInfo The logging configuration information
	@return			CDataLogger* A pointer to the newly created class.
	@pre 			None
	@post			Nothing is left on the CleanupStack
 */
	//##ModelId=3A70658E0047
	static CDataLogger* NewL(TLoggingInfo* aLogInfo);

/**
	@fn				static CDataLogger* NewLC(TLoggingInfo* aLogInfo)
	Intended Usage	: Standardized safe construction which leaves CDataLogger* on the cleanup stack.
	@exception		KErrNoMemory.	
	@since			7.0
	@param			aLogInfo The logging configuration information
	@return			CDataLogger* A pointer to the newly created class.
	@pre 			None
	@post			CDataLogger is on the CleanupStack
 */
	//##ModelId=3A70658E000B
	static CDataLogger* NewLC(TLoggingInfo* aLogInfo);

/**
	@fn				 ~CDataLogger()
	Intended Usage	: Standardized virtual destruction method 
	@since			7.0
 */
	//##ModelId=3A70658D03DF
	~CDataLogger();

/**
	@fn				IMPORT_C void DumpMemoryBlock(const TUint8* aAddress, TInt aLength)
	Intended Usage	:	Logs a block of memory to file in hexadecimal and ASCII format.
					For example: 
	@code
	0000 : 40 fd 8f 01 38 fd 8f 01 21 5f 00 10 61 00 74 00 : @...8...!_..a.t.
	0010 : 40 55 ff 00 48 fd 8f 01 ac fd 8f 01 ac fd 8f 01 : @U..H...........
	0020 : 21 88 00 60 90 41 ff 00 01 00 00 00 24 1f 7b 00 : !..`.A......$.{.
	0030 : 61 00 74 00 72 00 65 00 34 fd 8f 01 23 00 f1 77 : a.t.r.e.4...#..w
	0040 : 23 00 00 00 38 00                               : #...8.          
	@endcode
	@since			7.0
	@param			aAddress The address of the start of the block to be logged
	@param			aLength The number of bytes to be logged
	@pre 			None
	@post			The specified block of memory is output to file in hex and ASCII format
 */
	//##ModelId=3A70658D0399
	IMPORT_C void DumpMemoryBlock(const TUint8* aAddress, TInt aLength);

/**
	@fn				IMPORT_C void LogInformation(const TDesC16& aComment)
	Intended Usage	:	Add the specified comment to the log file. Wide descriptor version
	Error Condition	:	
	@since			7.0
	@param			aComment The text to be logged
	@pre 			None
	@post			The specified text is added to the log file
 */
	//##ModelId=3A70658D0366
	IMPORT_C void LogInformation(const TDesC16& aComment);

/**
	@fn				IMPORT_C void LogInformation(const TDesC8& aComment)
	Intended Usage	:	Add the specified comment to the log file. Narrow descriptor 
	version
	Error Condition	:	
	@since			7.0
	@param			aComment The text to be logged
	@pre 			None
	@post			The specified text is added to the log file
 */
	//##ModelId=3AADFEED03E3
	IMPORT_C void LogInformation(const TDesC8& aComment);

/**
	@fn				IMPORT_C void LogInformationWithParameters(TRefByValue<const TDesC16> aFormat, ...)
	Intended Usage	:	Add the specified comment to the log file. Wide descriptor version
	Error Condition	:	
	@since			7.0
	@param			aFormat The text to be formatted and logged
	@param			...	An argument set
	@pre 			None
	@post			The specified text is formatted and added to the log file
 */
	//##ModelId=3A892F46000F
	IMPORT_C void LogInformationWithParameters(TRefByValue<const TDesC16> aFormat, ...);

/**
	@fn				IMPORT_C void LogInformationWithParameters(TRefByValue<const TDesC8> aFormat, ...)
	Intended Usage	:	Add the specified comment to the log file. Narrow 
					descriptor version
	Error Condition	:	
	@since			7.0
	@param			aFormat The text to be formatted and logged
	@param			...	An argument set
	@pre 			None
	@post			The specified text is formatted and added to the log file
 */
	//##ModelId=3AADFEED0393
	IMPORT_C void LogInformationWithParameters(TRefByValue<const TDesC8> aFormat, ...);

/**
	@fn				IMPORT_C void ReportInformation(const TDesC& aComment)
	Intended Usage	:	Add the specified comment to the report file
	Error Condition	:	
	@since			7.0
	@param			aComment The text to be logged
	@pre 			None
	@post			The specified text is added to the report file
 */
	//##ModelId=3A892F45034D
	IMPORT_C void ReportInformation(const TDesC& aComment);

/**
	@fn				IMPORT_C void ReportInformationWithParameters(TRefByValue<const TDesC> aFormat, ...)
	Intended Usage	:	Add the specified comment to the report file
	Error Condition	:	
	@since			7.0
	@param			aFormat The text to be formatted and logged
	@param			...	An argument set
	@pre 			None
	@post			The specified text is formatted and added to the log file
 */
	//##ModelId=3A892F450267
	IMPORT_C void ReportInformationWithParameters(TRefByValue<const TDesC> aFormat, ...);

private:
/**
	@fn				CDataLogger()
	Intended Usage	: Constructor
	@since			7.0
 */
	//##ModelId=3A70658D032A
	CDataLogger();

/**
	@fn				void ConstructL(TLoggingInfo* aLogInfo)
	Intended Usage	: Completes the safe construction of the CDataLogger object
	@exception		KErrNoMemory.
	@since			7.0
	@param			aLogInfo The logging configuration information
	@pre 			First phase of construction is complete
	@post			CDatalogger is fully constructed
 */
	//##ModelId=3A70658D0316
	void ConstructL(TLoggingInfo* aLogInfo);

/**
	@fn				void SetupRDebugL(TBool aRequest)
	Intended Usage	:	
	Error Condition	:	
	@since			7.0
	@param			TBool aRequest " "
	@pre 			Called only from ConstructL()
	@post			iDebug is set up for debug outputting or not.
 */
	//##ModelId=3A892F45014E
	void SetupRDebugL(TBool aRequest);

/**
	@fn				void Log(MLogOutput* aLogOutput, const TDesC16& aMessage)
	Intended Usage	:	Helper function which will log out a descriptor.  The destination for
	logging depends whether an alternative logger was supplied by the user at construction.
	Descriptors to be logged are broken up into maximum lengths of 150 as this is more 
	manageable and is the limit supported by RFileLogger.  Wide descriptor version.
	@since			7.0
	@param			aLogOutput The logging mechanism to use
	@param			aMessage The descriptor to log
	@pre 			This CDataLogger is constructed
	@post			The message is logged to the destination
 */
	//##ModelId=3A8AA4D001BF
	void Log(MLogOutput* aLogOutput, const TDesC16& aMessage);

/**
	@fn				void SetupLoggingL(TLoggingInfo* aLogInfo)
	Intended Usage	:
	Error Condition	:
	@since			7.0
	@param			aLogInfo The user supplied logging configuration information
	@pre 			Called from ConstructL()
	@post			Logging output objects are configured.
 */
	//##ModelId=3A9A54D10366
	void SetupLoggingL(TLoggingInfo* aLogInfo);

private:
/** A do nothing base class for debug logging */
	class TNullDebugPrint
		{
		public:
			virtual void Print(const TDesC&);
		};

/** An override class for debug logging to RDebug */
	class TDebugPrint : public TNullDebugPrint
		{
		public:
			/** Print the output to RDebug */
			void Print(const TDesC& aMessage);
		};
/** The class instance */
	//##ModelId=3A892F450144
	TNullDebugPrint* iDebug;

/** The logging style to be used (plain text, HTML or custom). */
	//##ModelId=3A9A54D1035C
	TLoggingStyle	iLogStyle;
/** The logging formats to be used if iLogStyle is HTML or custom. */
	//##ModelId=3A892F45013A
	TLogFormat		iLogFormat;
/** Provides the file logging facilities*/
	//##ModelId=3A70658D030C
	MLogOutput*		iLogOutput;
/** Provides the reporting facilities*/
	//##ModelId=3A9A54D10348
	MLogOutput*		iReportOutput;
/** Pointer to a default log output if the user doesn't supply one */
	//##ModelId=3A9A54D1033E
	CDefaultLogOutput*	iDefaultLogOutput;
/** Pointer to a default report output if the user doesn't supply one */
	//##ModelId=3A9A54D1032A
	CDefaultLogOutput*	iDefaultReportOutput;
/** Provides the file reporting facilities*/
	//##ModelId=3A892F450126
	RFileLogger		iReportFlogger;
/** Provides the area for formatting log and report data */
	//##ModelId=3A892F450112
	HBufC*			iFormatBuf;
/** Make the test State Accessor a friend */
	friend class TDataLogger_StateAccessor;
	};

inline void CDataLogger::TNullDebugPrint::Print(const TDesC&)
	{
	// Do nothing
	}

#endif
