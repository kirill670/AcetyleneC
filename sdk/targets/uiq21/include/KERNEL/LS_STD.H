// LS_STD.H
//
// Copyright (c) 1994-1999 Symbian Ltd.  All rights reserved.
//
// Interface for ELOCL, the low-level localisation DLL.
//

#ifndef __LS_STD_H__
#define __LS_STD_H__
#include <e32std.h>
#include <e32svr.h>
#include <e32ver.h>
#include <u32std.h>

struct TFatUtilityFunctions // functions to be implemented by locale-DLLs
	{
	enum TOverflowAction
		{
		EOverflowActionLeave,
		EOverflowActionTruncate
		};
	typedef void (*TConvertFromUnicodeL)(TDes8& aForeign, const TDesC16& aUnicode, const TDesC8& aReplacementForUnconvertibleUnicodeCharacters, TOverflowAction aOverflowAction);
	typedef void (*TConvertToUnicodeL)(TDes16& aUnicode, const TDesC8& aForeign, TOverflowAction aOverflowAction);
	typedef TBool (*TIsLegalShortNameCharacter)(TUint aCharacter);
	TConvertFromUnicodeL iConvertFromUnicodeL;
	TConvertToUnicodeL iConvertToUnicodeL;
	TIsLegalShortNameCharacter iIsLegalShortNameCharacter;
	};

// deprecated class... as of 6.1 
class LCountry
	{
public:
	static const TLanguage Language;
	static const TInt CountryCode;
	static const TInt UniversalTimeOffset;
	static const TDateFormat DateFormat;
	static const TTimeFormat TimeFormat;
	static const TText * const CurrencySymbol;
	static const TLocalePos CurrencySymbolPosition;
	static const TBool CurrencySpaceBetween;
	static const TInt CurrencyDecimalPlaces;
	static const TBool CurrencyNegativeInBrackets;
	static const TBool CurrencyTriadsAllowed;
	static const TText* const ShortDateFormatSpec;
	static const TText* const LongDateFormatSpec;
	static const TText* const TimeFormatSpec;
	static const TFatUtilityFunctions* const FatUtilityFunctions;
	static const TText * const ThousandsSeparator;
	static const TText * const DecimalSeparator;
	static const TText * const DateSeparator[KMaxDateSeparators];
	static const TText * const TimeSeparator[KMaxTimeSeparators];
	static const TLocalePos AmPmSymbolPosition;
	static const TBool AmPmSpaceBetween;
//	static const TUint DaylightSaving;
	static const TDaylightSavingZone HomeDaylightSavingZone;
	static const TUint WorkDays;
	static const TDay StartOfWeek;
	static const TClockFormat ClockFormat;
	static const TUnitsFormat UnitsGeneral;
	static const TUnitsFormat UnitsDistanceLong;
	static const TUnitsFormat UnitsDistanceShort;
	};

class LLanguage
	{
public:
	static const TText * const DateSuffixTable[KMaxSuffixes];
	static const TText * const DayTable[KMaxDays];
	static const TText * const DayAbbTable[KMaxDays];
	static const TText * const MonthTable[KMaxMonths];
	static const TText * const MonthAbbTable[KMaxMonths];
	static const TText * const AmPmTable[KMaxAmPms];
	};

class LMessages
	{
public:
	static const TText * const MsgTable[ELocaleMessages_LastMsg];
	};

#ifdef _UNICODE
/*
 * The LAlphabet class has been abolished in the Unicode build.
 * Locale-specific character set information is kept in a unique LCharSet
 * structure (defined in U32STD.H; used by the Exec, Locl, and K classes).
 * The reason for having an actual object (rather than a class with no
 * instances but with static members) is so that its address can be
 * returned by the new Exec function GetLocaleCharSet().
 */
extern const LCharSet TheCharSet;	// the one and only LCharSet object
#else
class LAlphabet
	{
public:
	static const TUint8 TypeTable[KMaxTranslateTable];
	static const TText UpperTable[KMaxTranslateTable];
	static const TText LowerTable[KMaxTranslateTable];
	static const TText FoldTable[KMaxTranslateTable];
	static const TText CollTable[KMaxTranslateTable];
	};
#endif //_UNICODE

#endif

