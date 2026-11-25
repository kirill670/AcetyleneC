// UriUtilsCommon.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/**
	@file UriUtilsCommon.h
	Comments :	
 */

#ifndef __URIUTILSCOMMON_H__
#define __URIUTILSCOMMON_H__

// System includes
//
#include <e32base.h>

const TInt KUriUtilsErrorBase		= -5000;

/**
	@enum TUriError
	Enum defining the error and panic codes used in the UriUtils components.
	@since 6.0
 */
enum TUriUtilsError
	{
	/** Error specifying the use of an invalid component index */
	KUriUtilsErrBadComponentIndex		= KUriUtilsErrorBase,
	/** Error specifying the use of a base uri path is not absolute and not empty */
	KUriUtilsErrBadBasePath				= KUriUtilsErrorBase - 1,
	/** Error specifying that a buffer is not big enough to append a component and delimiters */
	KUriUtilsErrBufferOverflow			= KUriUtilsErrorBase - 2,
	/** Error specifying the use of an supported parsing mode */
	KUriUtilsErrBadDelimitedParserMode	= KUriUtilsErrorBase - 3,
	/** Error specifying that the delimiting character is not set */
	KUriUtilsErrNoDelimiter				= KUriUtilsErrorBase - 4,
	/** Error specifying that the data has not been parsed */
	KUriUtilsErrNotParsed				= KUriUtilsErrorBase - 5,
	/** Error specifying that a 16-bit character was found in data to be escape encode */
	KUriUtilsErr16BitChar				= KUriUtilsErrorBase - 6,
	/** Error specifying that a badly formed escape triple was found in data being escape decoded */
	KUriUtilsErrBadEscapeTriple			= KUriUtilsErrorBase - 7,
	/** Error specifying that charconv was unable to convert the input data */
	KUriUtilsCannotConvert				= KUriUtilsErrorBase - 8,
	/** Error specifying that there	was empty data */
	KUriUtilsErrEmptyData				= KUriUtilsErrorBase - 9,
	/** Error specifying that there is no character representation of an integer */
	KUriUtilsErrNoIntergerInData		= KUriUtilsErrorBase - 10,
	/** Error code specifying an invalid uri */
	KUriUtilsErrInvalidUri				= KUriUtilsErrorBase - 11,
	/** Error code for unsupported escaping mode */
	KUriUtilsErrBadEscapeMode			= KUriUtilsErrorBase - 12,
	/** Error code for unsupported text whitespace removal mode */
	KUriUtilsErrBadTextRemoveMode		= KUriUtilsErrorBase - 13
	};

// Constants
//
const TInt KSchemeDelimiter		= ':';
const TInt KUserinfoDelimiter	= '@';
const TInt KPortDelimiter		= ':';
const TInt KSlashDelimiter		= '/';
const TInt KQueryDelimiter		= '?';
const TInt KFragmentDelimiter	= '#';
const TInt KIPv6UriOpenBrace	= '[';
const TInt KIPv6UriCloseBrace	= ']';

#endif	// __URIUTILSCOMMON_H__