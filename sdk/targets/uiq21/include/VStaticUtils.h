// VSTATICUTILS.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//
#ifndef __VSTATICUTILS_H__
#define __VSTATICUTILS_H__

// System includes
#include <e32base.h>

// User includes
#include "versit.h"


class VersitUtils
	{
public:
	/**
	 * Returns ETrue/EFalse indicating whether the specified charset
	 * results in an 8 bit value or not. E.g. ASCII is 7 bit, ISO-8859-1 is
	 * 8 bit.
	 */
	IMPORT_C static TBool EightBitEncoding(Versit::TVersitCharSet aCharSet);

	/**
	 * Returns ETrue/EFalse indicating whether the specified charset
	 * results in an 8 bit value or not.
	 */
	IMPORT_C static TBool EightBitEncoding(TUint aCharSetId);

	/**
	 * Returns a uid corresponding to the ConArc uid associated with a converter
	 */
	IMPORT_C static TUid ConArcEncodingUid(Versit::TVersitEncoding aEncoding);

	/**
	 * Returns an IANA text string corresponding to the specified charset
	 */
	IMPORT_C static const TDesC8& IANACharacterSetName(Versit::TVersitCharSet aCharSet);

	/**
	 * Returns a MIME encoding type corresponding to the specified encoding
	 */
	IMPORT_C static const TDesC8& IANAEncodingName(Versit::TVersitEncoding aEncoding);

	/**
	 * Returns a charconv uid associated with a versit character set
	 */
	IMPORT_C static TUid CharConvCharSetUid(Versit::TVersitCharSet aCharSet);

	static Versit::TVersitCharSet CharSet(TUint aCharConvCharSetUid);

	/**
	 * Returns ETrue if all of the characters in the specified text can
	 * be safely represented in 7 bit ASCII
	 */
	IMPORT_C static TBool DescriptorContainsOnlySevenBitCharacters(const TDesC& aText);

	/**
	 * Returns ETrue if the specified text needs encoding in some way
	 */
	IMPORT_C static TBool RequiresEncoding(const TDesC& aText);

	/**
	 * Convert the specified Unicode text to a narrow buffer, using the specified
	 * character set identifier.
	 */
	IMPORT_C static void UncodeToNarrowL(const TDesC& aUnicode, TDes8& aNarrow, const Versit::TEncodingAndCharset& aEncodingCharset);

	/**
	 * Add a escaping character before the simicolar for given string <code>aTextToEscape</code> 
	 */
	IMPORT_C static void AddEscapedString(TDes& aDestination,const TDesC& aTextToEscape,Versit::TVersitCharSet aCharSet);

	/**
	 * Add a escaping character before the simicolar for given string <code>aTextToEscape</code> 
	 */
	IMPORT_C static void AddEscapedString(TDes& aDestination,const TDesC& aTextToEscape,TUint aCharSetId);

	/**
	 * Encodes the specified buffer using the specified (utility) ConArc uid.
	 */
	IMPORT_C static void ConArcEncodeL(RReadStream& aSource, CBufBase& aTarget, TUid aConArcEncodingUid);

	/**
	 * Ensures that a the specified buffer doesn't contain any lines longer than
	 * the specified length. 
	 */
	IMPORT_C static void WrapLinesL(CBufBase& aBuffer, TInt aMaxLineLength);

	/** 
	 * Check error code for Versit custom error codes and leave if it is 
	 * a standard Epoc error code
	 */
	IMPORT_C static TBool CheckAndIgnoreCustomErrorL(TInt aError); 
	
	/** 
	 * Remove escaping char - backslash from the given narrow string <code>aText</code> 
	 */
	IMPORT_C static void RemoveEscapeChars(TPtr8& aText);

	/** 
	 * Remove escaping char - backslash from the given 16-bit string <code>aText</code>
	 */
	IMPORT_C static void RemoveEscapeChars(HBufC16& aText);

	/** 
	 * Remove escaping char - backslash (or Yen-symbol if Char Set is Shift-JIS) from the given 16-bit string <code>aText</code>
	 */
	IMPORT_C static void RemoveEscapeChars(HBufC16& aText,TUint aCharSetUid);

	/** 
	 * Return ETrue if the given string contains any white spaces, EFalse otherwise.
	 */
	IMPORT_C static TBool IsNoneWhiteSpaceChar(const TDesC8& aString);

	/** 
	 * Strip white spaces at begining and end from the given narrow string <code>aText</code>   
	 */
	IMPORT_C static void StripWhiteSpace(TPtr8& aString);

	/** 
	 * Strip white spaces at begining and end from the given 16-bit string <code>aText</code>   
	 */
	IMPORT_C static void StripWhiteSpace(TPtr16& aString);

	/** 
	 * Return ETrue if the given character is a white spaces, EFalse otherwise.
	 */
	static inline TBool IsWhiteSpace(TUint aChar);

	/** 
	 * Return ETrue if the given the given uid is the uid of Begin or End
	 */
	static inline TBool IsBeginOrEnd(TUid aUid);

	/** 
	 * Return ETrue if the given string contains any white spaces, EFalse otherwise.
	 */
	IMPORT_C static TBool IsNoneWhiteSpaceWideChar(const TDesC16& aString);

private:
	static void AddEscapedString(TBool aIsShiftJis,TDes& aDestination,const TDesC& aTextToEscape);
	static void DoRemoveEscapeChars(HBufC16& aText,TUint16 aEscapeChar);
	};

inline TBool VersitUtils::IsWhiteSpace(TUint aChar)
	{return (aChar==CVersitParser::ESpace || aChar==CVersitParser::EHTab);}
inline TBool VersitUtils::IsBeginOrEnd(TUid aUid)
	{return (aUid.iUid==KVersitTokenBeginUid || aUid.iUid==KVersitTokenEndUid);}
#endif
