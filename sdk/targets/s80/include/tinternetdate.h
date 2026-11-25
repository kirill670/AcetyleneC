// tinternetdate.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

/**
	@file tinternetdate.h
	Comments :	This file contains the class TInternetDate
*/
  

#ifndef		__TINTERNETDATE_H__
#define		__TINTERNETDATE_H__

#include <e32std.h>

class TInternetDate
/**
@class TInternetDate
Stores dates in universal time and provides parsing of internet style dates 
into TDateTime and RFC 1123 (updates RFC 822) dates.

Supports parsing of the following date formats:
Sun, 06 Nov 1994 08:49:37 GMT  ; RFC 822, updated by RFC 1123
Sunday, 06-Nov-94 08:49:37 GMT ; RFC 850, obsoleted by RFC 1036
Sun Nov  6 08:49:37 1994       ; ANSI C's asctime() format

All dates are store relative to Universal Time and not local time. 

@publishedAll
@released
@since 7.0
*/
	{
public:	

	enum TInternetDateFormat
		{
		ERfc1123Format
		};

/**
	@fn				TInternetDate
	Intended Usage:	Default Constructor. Used when setting dates that are in a text format using SetDateL
	@since			7.0	.	
*/
	inline TInternetDate();

/**
	@fn				TInternetDate
	Intended Usage:	Constructor. Used when setting a date that you later want parsed into an internet text format
	@since			7.0
	@param		.	aUniversalTime, a time that should correspond to Universal Time
*/
	inline TInternetDate(TDateTime aUniversalTime);

/**
	@fn				SetDateL
	Intended Usage:	Used to set a date which is in a Internet form.
	@since			7.0
	@param			aDate, the text form of the date			.
	@leave			KErrCorrupt, if the date is not in the correct format
*/
	IMPORT_C void SetDateL(const TDesC8& aDate);

/**
	@fn				DateTime
	Intended Usage: Used to access the date/time
	@since			7.0
	@return			const TDateTime& The time stored in this object
*/
	IMPORT_C const TDateTime& DateTime();

/**
	@fn				InternetDateTimeL
	Intended Usage:	Used to access the date/time in a text formate
	@since			7.0
	@param			aInternetDateFormat The format of the date. Only RFC1123 dates are supported
	@return			HBufC8* A descriptor containing the date/time in the format 
					specifed by the parameter aInternetDateFormat
	@leave			KErrNoMemory
*/
	IMPORT_C HBufC8* InternetDateTimeL(TInternetDateFormat aInternetDateFormat);

private:
	TDateTime iDateTime;
	};


inline TInternetDate::TInternetDate()
	{}


inline TInternetDate::TInternetDate(TDateTime aUniversalTime) :
	iDateTime(aUniversalTime)
	{}


#endif	//	__TINTERNETDATE_H__