// DelimitedParserCommon.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/**
	@file DelimitedParserCommon.h
	Comments :	
 */

#ifndef __DELIMITEDPARSERCOMMON_H__
#define __DELIMITEDPARSERCOMMON_H__

// System includes
//
#include <e32base.h>

/**
@enum TDelimitedDataParseMode
Enum defining the modes for the delimited data parser.
@publishedAll
@released
@since			6.0	
*/
enum TDelimitedDataParseMode
	{
	/** Unparsed soecifier */
	EDelimitedDataNotParsed = 0,
	/** Specifier for parsing from left to right */
	EDelimitedDataForward,
	/** Specifier for parsing from right to left */
	EDelimitedDataReverse
	};

#endif	// __DELIMITEDPARSERCOMMON_H__

