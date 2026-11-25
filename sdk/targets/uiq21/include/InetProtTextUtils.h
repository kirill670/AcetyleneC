// TextUtils.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/**
	@file TextUtils.h
	Comments :	
 */

#ifndef __INETPROTTEXTUTILS_H__
#define __INETPROTTEXTUTILS_H__

// System includes
//
#include <e32base.h>

// Local includes
//
#include <uriutilscommon.h>

class InetProtTextUtils
	{
public:	// Enums

/**
	@enum TRemoveMode
	Enum defining whitespace removal modes.
	@since 6.0	
 */
	enum TRemoveMode
		{
		/** Specifies removal any contiguous whitespace characters at the beginning of some data */ 
		ERemoveLeft		= 0,
		/** Specifies removal any contiguous whitespace characters at the end of some data */ 
		ERemoveRight,
		/** Specifies removal any contiguous whitespace characters at the beginning and end of some data */ 
		ERemoveBoth
		};

public:	// Methods
	
/**
	@fn				RemoveWhiteSpace(TPtrC8& aData, TRemoveMode aMode)
	Intended Usage	:	Removes any contiguous whitespace at the extremes of the data,
	as specified by aMode. Whitespace is defined by the functions TChar::IsSpace() - 
	white space includes spaces, tabs, and separators (e.g. new line).
	@since			6.0
	@param			aData	A descriptor pointer with the data.
	@param			aMode	The specified removal mode.
	@return			The number of consumed whitespace characters. If the data is
	empty or the data is all whitespace the error code KUriUtilsErrEmptyData is
	returned.
 */
	IMPORT_C static TInt RemoveWhiteSpace(TPtrC8& aData, TRemoveMode aMode);

/**
	@fn				RemoveWhiteSpace(TPtrC16& aData, TRemoveMode aMode)
	Intended Usage	:	Removes any contiguous whitespace at the extremes of the data,
	as specified by aMode. Whitespace is defined by the functions TChar::IsSpace() - 
	white space includes spaces, tabs, and separators (e.g. new line).
	@since			6.0
	@param			aData	A descriptor pointer with the data.
	@param			aMode	The specified removal mode.
	@return			The number of consumed whitespace characters. If the data is
	empty or the data is all whitespace the error code KUriUtilsErrEmptyData is
	returned.
 */
	IMPORT_C static TInt RemoveWhiteSpace(TPtrC16& aData, TRemoveMode aMode);

/**
	@fn				ConvertIntToDescriptorL(TInt aInt, HBufC8*& aDes)
	Intended Usage	:	Converts an integer value into its character representation.
	@since			6.0
	@exception		KErrNoMemory, Math class exceptions.
	@param			aInt		An integer value.	
	@param			aBuffer		An output argument of a pointer to a data buffer
	that will contain the character representation of the integer value.
 */
	IMPORT_C static void ConvertIntToDescriptorL(TInt aInt, HBufC8*& aBuffer);

/**
	@fn				ConvertIntToDescriptorL(TInt aInt, HBufC16*& aDes)
	Intended Usage	:	Converts an integer value into its character representation.
	@since			6.0
	@exception		KErrNoMemory, Math class exceptions.
	@param			aInt		An integer value.	
	@param			aBuffer		An output argument of a pointer to a data buffer
	that will contain the character representation of the integer value.
 */
	IMPORT_C static void ConvertIntToDescriptorL(TInt aInt, HBufC16*& aBuffer);

/**
	@fn				ConvertDescriptorToInt(const TDesC8& aData, TInt& aInt)
	Intended Usage	:	Converts the character representation of an integer into its
	integer value. Preceeding whitespace is ignored and the integer is delimited by 
	either the end of the data, whitespace or any other character other than 0 to 9.
	@since			6.0
	@param			aData	A descriptor pointer with the data.
	@param			aInt	An output argument in which the integer value of the
	data is placed.
	@return			The number of consumed characters that contributed to the integer
	value, including any whitespace before the integer. If the data is empty the error
	code KUriUtilsErrEmptyData is returned. If there are no digits at the beginning 
	of the data the error code KUriUtilsErrNoIntergerInData is returned.
 */
	IMPORT_C static TInt ConvertDescriptorToInt(const TDesC8& aData, TInt& aInt);

/**
	@fn				ConvertDescriptorToInt(const TDesC16& aData, TInt& aInt)
	Intended Usage	:	Converts the character representation of an integer into its
	integer value. Preceeding whitespace is ignored and the integer is delimited by 
	either the end of the data, whitespace or any other character other than 0 to 9.
	@since			6.0
	@param			aData	A descriptor pointer with the data.
	@param			aInt	An output argument in which the integer value of the
	data is placed.
	@return			The number of consumed characters that contributed to the integer
	value, including any whitespace before the integer. If the data is empty the error
	code KUriUtilsErrEmptyData is returned. If there are no digits at the beginning 
	of the data the error code KUriUtilsErrNoIntergerInData is returned.
 */
	IMPORT_C static TInt ConvertDescriptorToInt(const TDesC16& aData, TInt& aInt);

	};

#endif	// __INETPROTTEXTUTILS_H__
