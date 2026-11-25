// TextInputServerStartFunctions.h
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __TEXTINPUTSERVERSTARTFUNCTIONS_H__
#define __TEXTINPUTSERVERSTARTFUNCTIONS_H__
#include <e32def.h>

// classes referenced

/**
 * This is a utility class to keep all the functions, that are necessary to start the
 * TextInputServer. (These are the only exported functions from the Server)
 *
 * @internal
 * @since Quartz 6.0
 */
class TextInputServerStartFunctions
	{
public:
	IMPORT_C static const TDesC& TextInputServerSemaphoreName();
	IMPORT_C static const TDesC& TextInputServerThreadName();
	IMPORT_C static TInt StartupTextInputServer();
	};

#endif	// __TEXTINPUTSERVERSTARTFUNCTIONS_H__