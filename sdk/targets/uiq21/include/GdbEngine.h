// GdbEngine.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
// Interface of CGdbEngine
//

#ifndef __GDBENGINE_H__
#define __GDBENGINE_H__

#ifndef __E32BASE_H__
#include "e32base.h"
#endif

class CGdbCommPort;
class CGdbDriver;
class CGdbSubParserRepository;
class TGdbCommServParserFactory;

class CGdbEngine : public CBase
//
// Facade class simplifying access to the various engine features.
//
	{

public:
	// Ctor & Dtor
	IMPORT_C static CGdbEngine* NewLC();
	IMPORT_C ~CGdbEngine();

	// Getters/Setters
	IMPORT_C void SetPortL(CGdbCommPort* aOpenedCommPort);
	inline CGdbDriver& Driver();

	// Configuration File
	IMPORT_C CGdbCommPort* ReadConfigFileL(const TDesC& aConfigFilePath, TInt& aFaultyLine);
	
private:
	void ConstructL();

private:
	CGdbDriver* iDriver;
	CGdbSubParserRepository* iSubParserRepository; // has
	TGdbCommServParserFactory* iCommServParserFactory;	// has
	};


inline CGdbDriver& CGdbEngine::Driver()
	{

	return *iDriver;
	}

#endif // __GDBENGINE_H__
