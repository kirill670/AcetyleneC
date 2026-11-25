// DAMIMPOR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#if !defined(__DAMIMPOR_H__)
#define __DAMIMPOR_H__

#include <s32file.h>
#include <s32mem.h>
#include <damainc.h>
class CDaRow;
class CDaModel;

class TDaFileImportParams
	{
public:
	IMPORT_C TDaFileImportParams();
public:
	CDaModel* iModel;
	TFileName iFileName;
	TChar iDelimiter;
	TChar iColumnSeparator;
	TChar iRecordSeparator;
	TInt iRecNo;
	};

class CDaFileImporter : public CDaIncremental
	{
public:
	IMPORT_C CDaFileImporter(TDaFileImportParams const& aParams); 
	IMPORT_C ~CDaFileImporter();
	IMPORT_C void OpenL();
	IMPORT_C void CloseL();
	IMPORT_C virtual TInt ImportL();
	IMPORT_C virtual TInt Next(TInt& aRemainingSteps);
	IMPORT_C virtual TInt DoNext(TInt& /*aRemainingSteps*/);
	IMPORT_C virtual void HandleLeave(TInt aError);
	IMPORT_C virtual void HandleCancel();
	
protected:
	enum TState {EBeforeStartOfToken, EReadingToken, EEndOfFile, EStartOfFile};
	TDaFileImportParams iParams;
	RFs iFs;
	RFileBuf iFile;
	TState iState;
	CDaRow* iRow;
	CBufFlat* iLineBuffer;
	CBufFlat* iColumnBuffer;
	TInt iRecNo;
	TInt iTotalBytesRead;
	TInt iFileSize;
private:
	void DoCancel();
	};

class CDaFileSeparatedImporter : public CDaFileImporter
	{
public:
	static CDaFileSeparatedImporter* NewL(TDaFileImportParams const& aParams);
	IMPORT_C ~CDaFileSeparatedImporter();
	TInt DoNext(TInt& aRemainingSteps);
private:
	CDaFileSeparatedImporter(TDaFileImportParams const& aParams) : CDaFileImporter(aParams) {}
	void ConstructL();
private:
	};

class CDaFileDelimitedImporter : public CDaFileImporter
	{
public:
	static CDaFileDelimitedImporter* NewL(TDaFileImportParams const& aParams);
	IMPORT_C ~CDaFileDelimitedImporter();
	TInt DoNext(TInt& aRemainingSteps);
private:
	CDaFileDelimitedImporter(TDaFileImportParams const& aParams) : CDaFileImporter(aParams) {}
	void ConstructL();
	TInt ProcessLine(TPtrC const& aLineBuffer);
	TPtrC GetToken();
private:
	TLex iLex;
	TLexMark iMark;
	};

class TDaFileImporterFactory
	{
public:
	IMPORT_C static CDaFileImporter* CreateL(TDaFileImportParams const& aParams);
	};

class CDaExporter : public CDaIncremental
	{
public:
	IMPORT_C static CDaExporter* NewL(CDaModel& aModel, const TDaFileImportParams& aParams);
	IMPORT_C ~CDaExporter();
	IMPORT_C virtual void CloseL();
	IMPORT_C virtual TInt Next(TInt& aRemainingSteps);
private:
	void ConstructL();
	CDaExporter(CDaModel& aModel, const TDaFileImportParams& aParams);
private:
	CDaModel& iModel;
	const TDaFileImportParams& iParams;
	RFile iOutFile;
	RFs iFs;
	CDaRow* iRow;
	CBufFlat* iColumnBuffer;
	CBufFlat* iOutBuffer;
	TInt iColCount;
	TInt iCurrentRow;
	};




#endif
