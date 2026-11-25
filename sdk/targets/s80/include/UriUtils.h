// UriUtils.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/**
	@file UriUtils.h
	Comments :	
 */

#ifndef __URIUTILS_H__
#define __URIUTILS_H__

// System includes
//
#include <e32base.h>

// Local includes
//
#include "uri8.h"
#include "uri16.h"

class UriUtils
/**
@publishedAll
@released
*/
	{
public:

	enum TUriHostType 
		{
		EIPv6Host,
		EIPv4Host,
		ETextHost,
		};

/**
	@fn				ConvertToInternetFormL(const TUriC16& aUri)
	Intended Usage	:	Converts a 16-bit format uri into its internet form. Any 
	Unicode characters are converted into Utf8 representation and then any excluded
	characters are escape encoded.
	@since			6.0
	@exception		KErrNoMemory, KUriUtilsCannotConvert, KUriUtilsErr16BitChar
	@param			aUri	The 16-bit format uri.
	@return			A pointer to a newly created 8-bit uri.
 */
	IMPORT_C static CUri8* ConvertToInternetFormL(const TUriC16& aUri);

/**
	@fn				ConvertToDisplayFormL(const TUriC8& aUri)
	Intended Usage	:	Converts an 8-bit format uri its into display form. Any escape
	tripes are decoded and sets of Utf8 format characters are converted into Unicode.
	@since			6.0
	@exception		KErrNoMemory, KUriUtilsCannotConvert, KUriUtilsErrBadTriple
	@param			aUri	The 8-bit format uri.
	@return			A pointer to a newly created 16-bit uri.
 */
	IMPORT_C static CUri16* ConvertToDisplayFormL(const TUriC8& aUri);

/**
	@fn				HasInvalidChars(const TDesC8& aData)
	Intended Usage	:	Checks a descriptor for excluded (invalid) characters.
	Excluded characters include all control characters (values 0x00 to 0x1F and
	greater than 0x7F), space (0x20), delimiter characters ('<', '>', '#', '%',
	'"') and unwise characters ('{', '}', '|', '\', '^', '[', ']', '`').
	@since			6.0
	@param			aData	The descriptor to be checked.
	@return			A boolean value of ETrue if the descriptor contains invalid 
	characters, otherwise EFalse.
 */
	IMPORT_C static TBool HasInvalidChars(const TDesC8& aData);

/**
	@fn				HasInvalidChars(const TDesC16& aData)
	Intended Usage	:	Checks a descriptor for excluded (invalid) characters.
	Excluded characters include all control characters (values 0x00 to 0x1F and
	greater than 0x7F), space (0x20), delimiter characters ('<', '>', '#', '%',
	'"') and unwise characters ('{', '}', '|', '\', '^', '[', ']', '`').
	@since			6.0
	@param			aData	The descriptor to be checked.
	@return			A boolean value of ETrue if the descriptor contains invalid 
	characters, otherwise EFalse.
 */
	IMPORT_C static TBool HasInvalidChars(const TDesC16& aData);

/**
	@fn				HostType(const TDesC8& aHost)
	Intended Usage	: Checks the supplied host for an IPv4, IPv6 or text format host
	@since			7.0
	@param			aHost	The descriptor containing the host to check
	@return			A TUriHostType enum of either EIPv6, EIPv4, EText or EUnknown
 */
	IMPORT_C static UriUtils::TUriHostType HostType(const TDesC8& aHost);

/**
	@fn				HostType(const TDesC16& aHost)
	Intended Usage	: Checks the supplied host for an IPv4, IPv6 or text format host
	@since			7.0
	@param			aHost	The descriptor containing the host to check
	@return			A TUriHostType enum of either EIPv6, EIPv4, EText or EUnknown
 */
	IMPORT_C static UriUtils::TUriHostType HostType(const TDesC16& aHost);	
	};

#endif	// __URIUTILS_H__