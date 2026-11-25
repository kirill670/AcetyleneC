// Log.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.

#include <f32file.h>

#if (!defined __LOG_H__)
#define __LOG_H__

// max length of log file line
#define	MAX_LOG_LINE_LENGTH		200

// max length of source file name
#define	MAX_LOG_FILENAME_LENGTH	200

// test verdict
enum TVerdict
{
	EPass =0,
	EFail,
	EInconclusive,
	ETestSuiteError,
	EAbort
};

class TIntegrationTestLog16Overflow :public TDes16Overflow
	{
public:
	// TDes16Overflow pure virtual
	virtual void Overflow(TDes16& aDes);
	};

class CFileLogger 
{
public:
	IMPORT_C void CreateLog(const TDesC& aDir, const TDesC& aName);
	IMPORT_C TInt Connect( void );
	IMPORT_C void CloseLog( void );
	IMPORT_C void WriteFormat( TRefByValue<const TDesC16> format, ...  );

private:
	// handle
	RFile iLogfile;
	RFs	  iFs;
	TBool iEnabled;
};

// Class CLog used for all file and console log data
class CLog  : public CBase
{
public:
	IMPORT_C static CLog * NewL(CConsoleBase * console);
	IMPORT_C void Construct( CConsoleBase * console );
	IMPORT_C ~CLog();

	// open close log file
	IMPORT_C void OpenLogFileL(TFileName scriptFileName);
	IMPORT_C void CloseLogFile();

	// write to log output in Printf style
	IMPORT_C void Log( TRefByValue<const TDesC16> format, ... );
	IMPORT_C void Log( TRefByValue<const TDesC16> format, VA_LIST aList );
	IMPORT_C void LogResult( TVerdict ver, TRefByValue<const TDesC16> format, ... );

	// add some blank lins to log output
	IMPORT_C void LogBlankLine( TInt number =1 );
	
	// convert a EPOC error to text
	IMPORT_C static TPtrC EpocErrorToText(TInt aError);

	// convert a test verdict to text 
	IMPORT_C const TText* TestResultText( enum TVerdict TestVerdict );

protected:
	// log systems pointer to the current console
	CConsoleBase * iConsole;

	// File logging system
	CFileLogger iFileLogger;

};




#endif /* __LOG_H__ */
