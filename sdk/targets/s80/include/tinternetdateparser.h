// tinternetdateparser.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

/**
	@file tinternetdateparser.h
	Comments :	This file contains the definition of internal classes used to parse TInternetDate data
*/ 


#ifndef		__TINTERNETDATEPARSER_H__
#define		__TINTERNETDATEPARSER_H__

#include <e32std.h>

/**
	@class TInternetDateParser
	Used as a support class of TInternetDate. This provides the implementation of parsing

	Supports parsing of the following date formats:
	Sun, 06 Nov 1994 08:49:37 GMT  ; RFC 822, updated by RFC 1123
    Sunday, 06-Nov-94 08:49:37 GMT ; RFC 850, obsoleted by RFC 1036
    Sun Nov  6 08:49:37 1994       ; ANSI C's asctime() format

	All dates are store relative to Universal Time and not local time. 

	@private
	@since 7.0
*/
class TInternetDateParser
	{
public:
	inline TInternetDateParser();
		
/**
	@fn				ConvertFromInternetFormL
	Intended Usage:	Used to parse internet text date/time into a TDateTime
	@since			7.0
	@param			aInternetTextDateTime The date/time in a text format
	@param			aTimeDate The result of parsing is placed here
	@leave			KErrNoMemory, KErrCorrupt If the format of the descriptor is not valid
*/	
	void ConvertFromInternetFormL(const TDesC8& aInternetTextDateTime, TDateTime& aDateTime);

/**
	@fn				ConvertToRfc1123FormL
	Intended Usage:	Converts from TDateTime to Internet RFC1123 Style date strings
	@since			7.0
	@param			aTimeDate The date/time to be parsed
	@leave			KErrNoMemory
	@return			HBufC8* aDescriptor containing a RFC1123 style date. 
*/
	HBufC8* ConvertToRfc1123FormL(const TDateTime& aDateTime);
private:

	void ConvertFromRfc1123And850FormL(const TDesC8& aRfc1123DateTime, TDateTime& aDateTime);
	void ConvertFromAscTimeFormL(const TDesC8& aAscTimeDateTime, TDateTime& aDateTime);
	TInt ParseRfcDateDayMonthYearL(const TDesC8& aDateTimeText, TDateTime& aDateTime);
	TMonth GetMonthL(const TDesC8& aMonthText);
	void ParseHHMMSSTimeL(const TDesC8& aDateTimeText, TDateTime& aDateTime);
	void ParseTimeOffsetL(const TDesC8& aTimeOffset, TTimeIntervalMinutes& aOffsetMinutes);
	void ParseHHMMTimeOffsetL(const TDesC8& aTimeOffset, TTimeIntervalMinutes& aOffsetMinutes);
	};


inline TInternetDateParser::TInternetDateParser()
	{}



#endif	//	__TINTERNETDATEPARSER_H__