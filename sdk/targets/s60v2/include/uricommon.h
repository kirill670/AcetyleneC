// UriCommon.h
//
// Copyright (c) Symbian Software Ltd 2001-2004. All rights reserved.
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

enum TFileUriFlags
/** 
	@enum TFileUriFlags
	Enum defining a flag used to indicate file storage type (fixed drive or removable media).
	@publishedAll
	@released
	@since 9.1	
 */
	 {
	 EExtMedia   = 1
	 };
 
 enum TUriFileName
/** 
	@enum TUriName
	Enum used by GetFileNameL to specify what data is returned. 
	@publishedAll
	@released
	@since 9.1	
 */
	 {
	/** Indicate a File URI is to be converted into a fully qualified file name. Will Leave if not used on a file URI */
	 EUriFileNameFull   = 0,
	 /** Indicate a the path component is to be converted into a file name with directories, but no drive. Behaviour is undefined for non-hierarchical  schemes */
	 EUriFileNamePath,
	 /** Indicate just the name is to be converted into a file name, with no directories. Behaviour is undefined for non-hierarchical  schemes */
	 EUriFileNameTail 
	 };

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
	EUriScheme,
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
