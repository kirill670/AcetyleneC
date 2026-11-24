// EIKDLL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDLL_H__)
#define __EIKDLL_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__APACMDLN_H__)
#include <apacmdln.h>
#endif

#if (defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)) && !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)
class EikDll
/**
This API is deprecated to 3rd parties as there is a better API to use - RApaLsSession. 
But it is available for partners and licencees to use

@publishedAll
@deprecated
*/
	{
public: 
	IMPORT_C static void StartDocL(const TDesC& aDocName);
	IMPORT_C static TThreadId StartExeL(const TDesC& aName);
	IMPORT_C static TThreadId StartAppL(const CApaCommandLine& aCommandLine);
public:
	IMPORT_C static void RunAppInsideThread(CApaCommandLine* aCommandLine);
	};
#endif

#endif
