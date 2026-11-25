// EIKDLL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDLL_H__)
#define __EIKDLL_H__

#include <e32std.h>
#include <apacmdln.h>


class EikDll
/**
This API is deprecated to 3rd parties as there is a better API to use - RApaLsSession. 
But it is available for partners and licencees to use

@publishedPartner 
@released 
*/
//@publishedAll @deprecated 

	{
public: 
	IMPORT_C static void StartDocL(const TDesC& aDocName);
	IMPORT_C static TThreadId StartExeL(const TDesC& aName);
	IMPORT_C static TThreadId StartAppL(const CApaCommandLine& aCommandLine);
public:
	IMPORT_C static void RunAppInsideThread(CApaCommandLine* aCommandLine);
	};

#endif
