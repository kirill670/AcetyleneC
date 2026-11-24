// COLLATE.H
//
// Copyright (c) Symbian Software Ltd 1996-2005.  All rights reserved.
//
/**
@file
@publishedAll
@released
*/

/*
Definitions needed for Unicode collation.

Collation is the comparison of two Unicode strings to produce an ordering
that may be used in a dictionary or other list.

Collation is implemented using the Standard Unicode Collation algorithm. There
are four levels of comparison:

primary: basic character identity
secondary: accents and diacritics
tertiary: upper and lower case, and other minor attributes
quaternary: Unicode character value

Punctuation is normally ignored but can optionally be taken into account.
Strings are fully expanded using the standard Unicode canonical expansions before
they are compared. Thai and Lao vowels are swapped with the following character
if any.

EUSER contains the 'basic collation method'. This method assigns the standard Unicode collation key values
to the characters in the WGL4 repertoire, plus commonly used control characters and fixed-width spaces, plus
the CJK ideograms (for which the keys can be generated algorithmically). Other characters are collated after
all the characters for which keys are defined, and ordered by their Unicode values.

Locales can supply any number of other collation methods. They will usually supply a 'tailoring' of the standard
method. This is done by using the standard table as the main key table (signalled by placing NULL in
TCollationMethod::iMainTable) and specifying an override table (TCollationMethod::iOverrideTable).
Locale-specific collation data resides in ELOCL.
*/

#ifndef __COLLATE_H__
#define __COLLATE_H__

#include <e32std.h>

//This material is used in the Unicode build only.
#ifdef _UNICODE

/**
Collation key table structure.
@internalComponent
*/
struct TCollationKeyTable
	{
public:
	/**
    Masks for the various parts of the elements of the iKey array.
	*/
	enum
		{
		ELevel0Mask = 0xFFFF0000,	// primary key - basic character identity
		ELevel1Mask = 0x0000FF00,	// secondary key - accents and diacritics
		ELevel2Mask = 0x000000FC,	// tertiary key - case, etc.
		EIgnoreFlag = 0x2,			// if set, this key is normally ignored
		EStopFlag = 0x1				// if set, this key is the last in a sequence representing a Unicode value or values
		};

	/**
    An array containing all of the keys and strings of keys concatenated
    together. Each key has EStopFlag set only if it is the last key in its
    string. Eack key contains the keys for levels 0, 1 and 2, and a flag
    EIgnoreFlag if the key is usually ignored (for punctuation & spaces
    etc.).
    */
	const TUint32* iKey;
	/**
    An array of indices into the iKey array. Each element has its high 16
    bits indicating a Unicode value and its low 16 bits indicating an index
    into the iKey array at which its key starts. The elements are sorted by
    Unicode value.
    */
	const TUint32* iIndex;
	/**
    The size of the iIndex array.
    */
	TInt iIndices;
	/**
    Concatenated Unicode strings. Each is a strings that is to be converted
    to keys differently from how it would be if each letter were converted
    independently. An example is "ch" in Spanish, which sorts as though it
    were a single letter. Each Unicode string is preceeded by a 16-bit value
    indicating the string's length. The end of the string is not delimited.
    */
	const TUint16* iString;
	/**
    An array of elements mapping elements of iString to elements of iIndex.
    Each element has its high 16 bits indicating the index of the start of
    an element of iString, and its low 16 bits indicating the corresponding
    element in iIndex. This array is sorted on the string index.
    */
	const TUint32* iStringIndex;
	/**
    The size of the iStringIndex array.
    */
	TInt iStringIndices;
	};

/**
A collation method object specifies a table of collation keys, and optionally 
a tailoring table that contains those keys for which the values in the main table are overridden.
@internalComponent
*/
struct TCollationMethod
	{
	public:
	TUint iId;									// the UID of this collation method
	const TCollationKeyTable* iMainTable;		// the main collation key table; if null, use the standard table
	const TCollationKeyTable* iOverrideTable;	// if non-null, tailoring for collation keys
	
/**
 *
 * Miscellaneous constants.
 */

	enum
		{
		/** Don't ignore any keys(punctuation, etc. is normally ignored). */
		EIgnoreNone = 1,
		
		/** Reverse the normal order of upper and lower case for characters
		differing only in case.
		*/
		ESwapCase = 2,
		
		/** Compare secondary keys which represent accents in reverse order (from
		right to left); this is needed for French when comparing words that
		differ only in accents.
		*/
		EAccentsBackwards = 4,		
		
		/** Reverse the normal order for characters differing only in whether they
		are katakana or hiragana.
		 */
		ESwapKana = 8,
								
		/** Fold all characters to lower case before extracting keys; needed for
		comparison of filenames, for which case is ignored but other tertiary
		distinctions are not.
		*/
		EFoldCase = 16,
		
		/** Flag to indicate a collation method for matching purpose 
		This flag is only needed if we wish to specify a particular collation method
		to be used for matching purpose.
		*/
		EMatchingTable = 32
		};

	TUint iFlags;				// flags as defined above
	};

/**
A collation data set provides any collation methods needed by a locale.
@internalComponent
*/
struct TCollationDataSet
	{
	public:
	const TCollationMethod* iMethod;
	TInt iMethods;
	};

//Forward declarations
class TUTF32Iterator;
struct LCharSet;

/**
The TCollate object provides low-level collation functions.
@internalComponent
*/
class TCollate
	{
public:
	TCollate(const LCharSet* aCharSet,TUint aMask = 0,TUint aFlags = 0xFFFFFFFF);
	TCollate(const TCollationMethod& aMethod);
	enum TComparisonResult
		{
		ELeftComparesLessAndIsNotPrefix = -2,
		ELeftIsPrefixOfRight = -1,
		EStringsIdentical = 0,
		ERightIsPrefixOfLeft = 1,
		ERightComparesLessAndIsNotPrefix = 2
		};
	TComparisonResult Compare(const TUint16* aString1,TInt aLength1,
                              const TUint16* aString2,TInt aLength2,
                              TInt aMaxLevel = 3) const;
	TInt Find(const TUint16 *aString1,TInt aLength1,const TUint16 *aString2,TInt aLength2,
			  TInt aMaxLevel,TUint aString2WildChar = 0) const;
	TInt Match(const TUint16 *aCandidate, TInt aCandidateLength, const TUint16 *aSearchTerm,
               TInt aSearchTermLength, TInt aMaxLevel,
               TUint aWildChar = '?', TUint aWildSequenceChar = '*') const;

private:
	TComparisonResult CompareKeySequences(TUTF32Iterator& aLeft, TUTF32Iterator& aRight,
                                          TInt aMaxLevel, TInt aRightStringWildChar) const;
	TInt FindKeySequence(TUTF32Iterator& aCandidate, TUTF32Iterator& aSearchTerm,
                         TInt aMaxLevel, TInt aWildChar) const;

private:
	TCollationMethod iMethod;

	};

// Collation method IDs
const TUint KUidBasicCollationMethod = 0x10004F4E;
const TUint KUidStandardUnicodeCollationMethod = 0x10004E96;

#endif // _UNICODE

#endif // __COLLATE_H__
