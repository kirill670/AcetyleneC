// CIniData.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__CINIDATA_H__)
#define __CINIDATA_H__

#include <e32base.h>

class CIniData : public CBase 
	{
public:
	// Constructor, pass in name of ini file to open
	// Default search path is 'c:\system\data' on target filesystem
	// ie. 'NewL(_L("c:\\system\\data\\ttools.ini"))' is equivalent 
	// to 'NewL(_L("ttools.ini"))' 
	IMPORT_C static CIniData* NewL(const TDesC& aName);
	IMPORT_C virtual ~CIniData();

	// Read text value reguardless of section
	// Returns: True(Success) or false(Failure)
	IMPORT_C TBool FindVar(const TDesC &aKeyName,	// Key to look for
						TPtrC &aResult);			// Buffer to store value

	// Read integer value reguardless of section
	// Returns: True(Success) or false(Failure)
	IMPORT_C TBool FindVar(const TDesC &aKeyName, 	// Key to look for
						TInt &aResult);				// Int ref to store result

	// Read text value under section
	// Returns: True(Success) or false(Failure)
	IMPORT_C TBool FindVar(const TDesC &aSection,	// Section to look under
						const TDesC &aKeyName,		// Key to look for
						TPtrC &aResult);			// Buffer to store result

	// Read integer value under section
	// Returns: True(Success) or false(Failure)
	IMPORT_C TBool FindVar(const TDesC &aSection,	// Section to look under
						const TDesC &aKeyName,		// Key to look for
						TInt &aResult);				// Int ref to store result

protected:
	IMPORT_C CIniData();
	IMPORT_C void ConstructL(const TDesC& aName);
private:
	HBufC* iName;
	HBufC* iToken;
	TPtr iPtr;
	};

#endif
