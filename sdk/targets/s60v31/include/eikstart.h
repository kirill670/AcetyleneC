// EIKSTART.H
//
// Copyright (c) Symbian Software Ltd 1997-2004.  All rights reserved.
//

#if !defined(__EIKSTART_H__)
#define __EIKSTART_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__APPARC_H__)
#include <apparc.h>
#endif


class CApaCommandLine;

class EikStart
/**
This is the API to initialise and run the application architecture for applications built as exes.
It is not intended to be used for generally running applications from other code. Use RApaLsSession for that.

@publishedAll
@released
*/
	{
public:
	IMPORT_C static TInt RunApplication(TApaApplicationFactory aApplicationFactory);
private:
	static void RunApplication(const TApaApplicationFactory& aApplicationFactory,CApaCommandLine* aCommandLine);
	};

#endif
