// COEUTILS.H
//
// Copyright (c) 1997-2005 Symbian Ltd.  All rights reserved.
//

#ifndef __COEUTILS_H__
#define __COEUTILS_H__

#include <e32std.h>

/** Provides file and path utility functions.

@publishedAll
@released */
class ConeUtils
	{
public:
	IMPORT_C static TBool FileExists(const TDesC& aFileName);
	IMPORT_C static void EnsurePathExistsL(const TPtrC& aFileName);
	};

// __COEUTILS_H__
#endif
