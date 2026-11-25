// EscapeUtils.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/**
	@file EscapeUtils.h
	Comments :	This file contains the API definition for escape enoding functionality
				and UNICODE/UTF8 conversion. Escape encoding is performed as specified
				by RFC2396.
*/

#ifndef __ESCAPEUTILS_H__
#define __ESCAPEUTILS_H__

// System includes
//
#include <e32base.h>

// Local includes
//
#include "UriUtilsCommon.h"

/**
	@class EscapeUtils
	Comments : Provides an API to allow data to be escape encoded and decoded. 
	Also provide an API for converting a UNICODE data (16-bit descriptor) into 
	UTF8 data (8-bit descriptor) and vice-verse.
	@public
	@since 6.0
	@libs euser.lib, charconv.lib
 */
class EscapeUtils
	{
public:	// Enums

/**
	@enum	TEscapeMode
	Enum defining escaping modes. Each mode has a different set of reserved characters.
	These are based on various uri components, as decribed in RFC2396.
 */
	enum TEscapeMode
		{
		/** Default mode, which has no reserved characters */
		EEscapeNormal	= 0,
		/** Mode specifying reserved characters in a uri query - ;/?:@&=+$,[] */
		EEscapeQuery,
		/** Mode specifying reserved characters in a uri path - /;=?[] */
		EEscapePath,
		/** Mode specifying reserved characters in a uri authority - /;:@?[] */
		EEscapeAuth,
		/** Mode specifying reserved characters in a URL ;/?:@&=+$[]!\'()~ */
		EEscapeUrlEncoded
		};

public:	// Methods

/**
	@fn				EscapeEncodeL(const TDesC8& aString, TEscapeMode aMode)
	Intended Usage	:	Escape encodes excluded and reserved characters in the 
	data as escape triples. The reserved characters are defined by the escape 
	mode. These characters and the set of excluded characters specified by RFC2396 
	form the entire set of excluded data.
	@since			6.0
	@exception		KErrNoMemory, KUriUtilsErr16BitChar
	@param			aData	A descriptor with the data to encode.
	@param			aMode	An enum specifying the escape mode.
	@return			A pointer to a descriptor buffer which contains the escape encoded data.
 */
	IMPORT_C static HBufC8* EscapeEncodeL(const TDesC8& aData, TEscapeMode aMode);

/**
	@fn				EscapeEncodeL(const TDesC16& aString, TEscapeMode aMode)
	Intended Usage	:	Escape encodes excluded and reserved characters in the 
	data as escape triples. The reserved characters are defined by the escape 
	mode. These characters and the set of excluded characters specified by RFC2396 
	form the entire set of excluded data.
	@since			6.0
	@exception		KErrNoMemory, KUriUtilsErr16BitChar
	@param			aData	A descriptor with the data to encode.
	@param			aMode	An enum specifying the escape mode.
	@return			A pointer to a descriptor buffer which contains the escape encoded data.
 */
	IMPORT_C static HBufC16* EscapeEncodeL(const TDesC16& aData, TEscapeMode aMode);

/**
	@fn				EscapeEncodeL(const TDesC8& aData, const TDesC8& aReservedChars)
	Intended Usage	:	Escape encodes excluded and reserved characters in the 
	data as escape triples. These characters and the set of excluded characters 
	specified by RFC2396 form the entire set of excluded data.
	@since			6.0
	@exception		KErrNoMemory, KUriUtilsErr16BitChar
	@param			aData			A descriptor with the data to encode.
	@param			aReservedChars	A descriptor with the reserved characters.
	@return			A pointer to a descriptor buffer which contains the escape encoded data.
 */
	IMPORT_C static HBufC8* EscapeEncodeL(const TDesC8& aData, const TDesC8& aReservedChars);

/**
	@fn				EscapeEncodeL(const TDesC16& aData, const TDesC16& aReservedChars)
	Intended Usage	:	Escape encodes excluded and reserved characters in the 
	data as escape triples. These characters and the set of excluded characters 
	specified by RFC2396 form the entire set of excluded data.
	@since			6.0
	@exception		KErrNoMemory, KUriUtilsErr16BitChar
	@param			aData			A descriptor with the data to encode.
	@param			aReservedChars	A descriptor with the reserved characters.
	@return			A pointer to a descriptor buffer which contains the escape encoded data.
 */
	IMPORT_C static HBufC16* EscapeEncodeL(const TDesC16& aData, const TDesC16& aReservedChars);

/**
	@fn				EscapeDecodeL(const TDesC8& aData)
	Intended Usage	:	Escape decodes the data.
	@since			6.0
	@exception		KErrNoMemory, KUriUtilsErrBadTriple
	@param			aData	A descriptor with the data to decode.
	@return			A pointer to a descriptor buffer which contains the escape decoded data.
 */
	IMPORT_C static HBufC8* EscapeDecodeL(const TDesC8& aData);

/**
	@fn				EscapeDecodeL(const TDesC16& aData)
	Intended Usage	:	Escape decodes the data.
	@since			6.0
	@exception		KErrNoMemory, KUriUtilsErrBadTriple
	@param			aData	A descriptor with the data to decode.
	@return			A pointer to a descriptor buffer which contains the escape decoded data.
 */
	IMPORT_C static HBufC16* EscapeDecodeL(const TDesC16& aData);

/**
	@fn				ConvertFromUnicodeToUtf8L(const TDesC& aData)
	Intended Usage	:	Converts UNICODE data into UTF8 format.
	@since			6.0
	@exception		KErrNoMemory, KUriUtilsCannotConvert
	@param			aData			A descriptor with the data to convert.
	@return			A pointer to an 8-bit descriptor buffer which contains UTF8 data.
 */
	IMPORT_C static HBufC8* ConvertFromUnicodeToUtf8L(const TDesC& aData);

/**
	@fn				ConvertToUnicodeFromUtf8L(const TDesC8& aData)
	Intended Usage	:	Converts UTF8 format into UNICODE data.
	@since			6.0
	@exception		KErrNoMemory, KUriUtilsCannotConvert
	@param			aData			A descriptor with the data to convert.
	@return			A pointer to a 16-bit descriptor buffer which contains UNICODE data.
 */
	IMPORT_C static HBufC* ConvertToUnicodeFromUtf8L(const TDesC8& aData);

/**
	@fn				TBool IsExcludedChar(TChar aChar)
	Intended Usage	:	Checks to see if the input argument is excluded.
	@since			6.0
	@param			aChar	The character to be checked.
	@return			A boolean value of ETrue if the character is an excluded one, or
	EFalse if it is not.
 */
	IMPORT_C static TBool IsExcludedChar(TChar aChar);

/**
	@fn				IsEscapeTriple(const TDesC8& aData, TInt& aHexValue)
	Intended Usage	:	Checks for an escape triple at the start of the input
	descriptor. If there is a triple its value is calculated and returned through
	the output argument aHexValue. If there is no escape triple then this argument
	is left unchanged.
	@since			6.0
	@param			aData		The descriptor to be checked for an escape triple.
	@param			aHexValue	The output argument with the value of the escape
	triple if it exists.
	@return			A boolean value of ETrue if there is an escape triple at the 
	start of the input descriptor, EFalse otherwise.
 */
	IMPORT_C static TBool IsEscapeTriple(const TDesC8& aData, TInt& aHexValue);

/**
	@fn				IsEscapeTriple(const TDesC16& aData, TInt& aHexValue)
	Intended Usage	:	Checks for an escape triple at the start of the input
	descriptor. If there is a triple its value is calculated and returned through
	the output argument aHexValue. If there is no escape triple then this argument
	is left unchanged.
	@since			6.0
	@param			aData		The descriptor to be checked for an escape triple.
	@param			aHexValue	The output argument with the value of the escape
	triple if it exists.
	@return			A boolean value of ETrue if there is an escape triple at the 
	start of the input descriptor, EFalse otherwise.
 */
	IMPORT_C static TBool IsEscapeTriple(const TDesC16& aData, TInt& aHexValue);

	};

#endif	// __ESCAPEUTILS_H__
