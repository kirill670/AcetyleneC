// UriCommon.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/**
	@file UriCommon.h
	Comments :	Internal header file with common constants used by the implementations 
				of the uri classes TUriC??, CUri?? and TUriParser??.
 */

#ifndef __URICOMMON_H__
#define __URICOMMON_H__

// System includes
//
#include <e32base.h>

enum TUriComponent
/**
@enum TUriComponent
Enum defining the uri components.
@warning		The enum value EUriMaxComponents should not be used as it will 
cause a panic.
@publishedAll
@released
@since 6.0	
*/
	{
	/** The scheme component specifier */
	EUriScheme = 0,
	/** The userinfo component specifier */
	EUriUserinfo,
	/** The host component specifier */
	EUriHost,
	/** The port component specifier */
	EUriPort,
	/** The path component specifier */
	EUriPath,
	/** The query component specifier */
	EUriQuery,
	/** The fragment component specifier */
	EUriFragment,
	/** Do not use as a field specifier - will cause panic */
	EUriMaxComponents
	};
	
#endif	// __URICOMMON_H__
