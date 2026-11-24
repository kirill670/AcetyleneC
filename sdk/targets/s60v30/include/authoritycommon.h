// AuthorityCommon.h
//
// Copyright (c) 2001-2005 Symbian Ltd.  All rights reserved.
//

/**
	@file AuthorityCommon.h
	Comments :	Internal header file with common information used by the authority
				classes TAuthorityC??, CAuthority?? and TAuthorityParser??.

	@see Authority8.h, Authority16.h
 */

#ifndef __AUTHORITYCOMMON_H__
#define __AUTHORITYCOMMON_H__

// System includes
//
#include <e32base.h>

/**
@enum TAuthorityComponent
Enum defining the authority components.
@publishedAll
@released
@warning		The enum value EAuthorityMaxComponents should not be used as it will 
cause a panic.
@since			6.0	
*/
enum TAuthorityComponent
	{
	/** The userinfo component specifier */
	EAuthorityUserinfo = 0,
	/** The host component specifier */	
	EAuthorityHost,
	/** The port component specifier */
	EAuthorityPort,
	/** Do not use as a field specifier - will cause panic */
	EAuthorityMaxComponents,
	/** The complete Authority. Only use with DisplayFormL, otherwise will cause panic */
	EAuthorityComplete = -1
	};
		
#endif	// __AUTHORITYCOMMON_H__
