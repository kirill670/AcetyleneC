// CHARCONV.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__CHARCONV_H__)
#define __CHARCONV_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__E32BASE_H__)
#include <E32BASE.H>
#endif

const TInt KMaximumLengthOfReplacementForUnconvertibleUnicodeCharacters=50;

const TUint KCharacterSetIdentifierUtf7=0x1000582c;
const TUint KCharacterSetIdentifierUtf8=0x1000582d;
const TUint KCharacterSetIdentifierImapUtf7=0x1000582e;
const TUint KCharacterSetIdentifierJavaConformantUtf8=0x1000582f;
const TUint KCharacterSetIdentifierCodePage1252=0x100012b6;
const TUint KCharacterSetIdentifierIso88591=0x10003b10;
const TUint KCharacterSetIdentifierIso88592=0x1000507e;
const TUint KCharacterSetIdentifierIso88593=0x10008a28;
const TUint KCharacterSetIdentifierIso88594=0x1000507f;
const TUint KCharacterSetIdentifierIso88595=0x10005080;
const TUint KCharacterSetIdentifierIso88596=0x10008a29;
const TUint KCharacterSetIdentifierIso88597=0x10005081;
const TUint KCharacterSetIdentifierIso88598=0x10008a2a;
const TUint KCharacterSetIdentifierIso88599=0x10005082;
const TUint KCharacterSetIdentifierIso885910=0x10008a2b;
const TUint KCharacterSetIdentifierIso885913=0x10008a2c;
const TUint KCharacterSetIdentifierIso885914=0x10008a2d;
const TUint KCharacterSetIdentifierIso885915=0x10008a2e;
const TUint KCharacterSetIdentifierAscii=0x10004cc6;
const TUint KCharacterSetIdentifierSms7Bit=0x100053ab;
const TUint KCharacterSetIdentifierGb2312=0x10000fbe;
const TUint KCharacterSetIdentifierHz=0x10006065;
const TUint KCharacterSetIdentifierGb12345=0x1000401a;
const TUint KCharacterSetIdentifierGbk=0x10003ecb;
const TUint KCharacterSetIdentifierBig5=0x10000fbf;
const TUint KCharacterSetIdentifierShiftJis=0x10000fbd;
const TUint KCharacterSetIdentifierIso2022Jp=0x100066a0;
const TUint KCharacterSetIdentifierIso2022Jp1=0x100066a3;
const TUint KCharacterSetIdentifierJis=0x10006066;
const TUint KCharacterSetIdentifierEucJpPacked=0x10006067;
const TUint KCharacterSetIdentifierUnicodeLittle=0x101f3fae;  //Little Endian Unicode
const TUint KCharacterSetIdentifierUnicodeBig=0x101f4052; // Big Endian Unicode 
// note that other character sets than those listed above may be available at run-time, and also that none of the above are necessarily available at run-time

struct SCnvConversionData;
class CDeepDestructingArrayOfCharactersSets;
class CFileReader;
class CStandardNamesAndMibEnums;
class RFs;


/**
 *
 * Converts text between Unicode and other character sets.
 *
 * The first stage of the conversion is to specify the non-Unicode
 * character set being converted to or from. This is done by calling one
 * of the overloads of <code>PrepareToConvertToOrFromL()</code>.The
 * second stage is to convert the text using one of the overloads of
 * <code>ConvertFromUnicode()</code> or
 * <code>ConvertToUnicode()</code>.Where possible the first documented
 * overload of <code>PrepareToConvertToOrFromL()</code> should be used
 * because the second overload panics if the specified character set is
 * not available the first overload simply returns whether the character
 * set is available or not available. However if the conversions are to
 * be performed often, or if the user must select the character set for
 * the conversion from a list, the second overload may be more
 * appropriate.The first overload is less efficient than the second,
 * because it searches through the file system for the selected character
 * set every time it is invoked. The second overload searches through an
 * array of all available character sets. In this method, the file system
 * need only be searched once when
 * <code>CreateArrayOfCharacterSetsAvailableLC()</code> or
 * <code>CreateArrayOfCharacterSetsAvailableL()</code> is used to create
 * the array.The conversion functions allow users of this class to
 * perform partial conversions on an input descriptor handling the
 * situation where the input descriptor is truncated mid way through a
 * multi-byte character. This means that you do not have to guess how big
 * to make the output descriptor for a given input descriptor you can
 * simply do the conversion in a loop using a small output descriptor.
 * The ability to handle truncated descriptors also allows users of the
 * class to convert information received in chunks from an external
 * source.The class also provides a number of utility functions.
 *
 * @since 5.1
 * @lib "charconv.lib"
 */

class CCnvCharacterSetConverter : public CBase
	{
public:
	
/**
 *
 * Indicates whether a character set is available or unavailablefor
 * conversion.
 
 *
 * Used by the second overload of
 * <code>PrepareToConvertToOrFromL()</code>.
 * * @since 
 */

	enum TAvailability
		{
		/** The requested character set can be converted. */
		EAvailable,
		/** The requested character set cannot be converted. */
		ENotAvailable
		};
	
/**
 *
 * Flags conversion errors.
 
 *
 * At this stage there is only one error flag others may be added in the
 * future.
 * * @since 
 */

	enum TError
		{
/** The input descriptor contains a single corrupt character. This error
might be returned if the input descriptor only contains some of the
bytes of a single multi-byte character.
 */
		EErrorIllFormedInput=KErrCorrupt
		};
	
/**
 *
 * Specifies the default endian-ness of the current character set.
 
 *
 * Used by <code>SetDefaultEndiannessOfForeignCharacters()</code>.
 * * @since 
 */

	enum TEndianness
		{
		/** The character set is big-endian. */
		ELittleEndian,
		/** The character set is little-endian. */
		EBigEndian
		};
	
/**
 *
 * Downgrade for line and paragraph separators.
 * @since 6.0
 */

	enum TDowngradeForExoticLineTerminatingCharacters
		{
/** Paragraph/line separators should be downgraded (if necessary) into
carriage return and line feed pairs.
 */
		EDowngradeExoticLineTerminatingCharactersToCarriageReturnLineFeed,
/** Paragraph/line separators should be downgraded (if necessary) into a
line feed only.
 */
		EDowngradeExoticLineTerminatingCharactersToJustLineFeed
		};

/**
*
* Output flag used to indicate whether or not a character in the source
* descriptor is the first half of a surrogate pair, but is the last
* character in the descriptor to convert.
 
*
* NoteThis enumeration can be used in the
* <code>DoConvertToUnicode()</code> and
* <code>DoConvertFromUnicode()</code> functions. These are part of the
* Character Conversion Plug-in Provider API and are for use by plug-in
* conversion libraries only.
* * @since 6.0
*/

	enum
		{
		/** Appends the converted text to the output descriptor.*/
		EInputConversionFlagAppend										=0x00010000,
/** By default, when the input descriptor passed to
<code>DoConvertFromUnicode()</code> or
<code>DoConvertToUnicode()</code> consists of nothing but a truncated
sequence, the error-code <code>EErrorIllFormedInput</code> is
returned. If this behaviour is undesirable, the input flag <code>EInp-
utConversionFlagAllowTruncatedInputNotEvenPartlyConsumable</code>
should be set.
 */
		EInputConversionFlagAllowTruncatedInputNotEvenPartlyConsumable	=0x00020000,
		/** Stops converting when the first unconvertible character is reached. */
		EInputConversionFlagStopAtFirstUnconvertibleCharacter			=0x00040000,
		/** Appends the default character set Escape sequence at end of converted text */
		EInputConversionFlagMustEndInDefaultCharacterSet				=0x00080000
		};
	enum
		{
/** Indicates whether or not the source descriptor ends in a truncated
sequence, e.g. the first half only of a surrogate pair.
 */
		EOutputConversionFlagInputIsTruncated							=0x01000000
		};

/** Initial value for the state argument in a set of related calls to
<code>ConvertToUnicode()</code>.
 */
	enum {KStateDefault=0};
	enum 
		{
		/** The lowest confidence value for a character set accepted by Autodetect*/
		ELowestThreshold = 25
		};
	struct SCharacterSet
		{
		
/**
 *
 * Gets the character sets UID.
 *
 * @returns   "TUint"
 *            The UID of the character set.
 */

		inline TUint Identifier() const {return iIdentifier;}

/**
 *
 * Tests whether a filename given by the function
 * <code>SCharacterSet::Name()</code> is a real file name (i.
 *
 * e. conversion is provided by a plug in DLL), or just the character set
 * name (i.e. conversion is built into EPOC).Note:If the function returns
 * <code>ETrue</code> then the path and filename can be parsed using
 * <code>TParse</code> or <code>TParsePtrC</code> functions to obtain
 * just the filename.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the name is a real filename.
 *            <code>EFalse</code> if it is just the character set
 *            name.
 */

		inline TBool NameIsFileName() const {return iFlags&EFlagNameIsFileName;}

/**
 *
 * Gets the full path and filename of the DLL which implements conversion
 * for the character set.
 *
 * If the character set is one for which conversion is built into EPOC
 * rather than implemented by a plug in DLL, the function just returns
 * the name of the character set. The <code>NameIsFileName()</code>
 * function can be used to determine whether or not it is legal to create
 * a <code>TParsePtrC</code> object over the descriptor returned by
 * <code>Name()</code>.Notes:The name returned cannot be treated as an
 * Internet-standard name, it is locale-independent and should be mapped
 * to the locale-dependent name by software at a higher level before
 * being shown to the user. Conversion from Internet-standard names of
 * character sets to the UID identifiers is provided by the member
 * function <code>ConvertStandardNameOfCharacterSetToIdentifierL()</code-
 * >.Typically, to find the user-displayable name (as opposed to the
 * internet-standard name) of a character set, you would do something
 * like this:
 *
 * @returns   "TPtrC"
 *            Full path and filename of the character set converter
 *            plug in DLL, or just the name of the character set.
 */

		inline TPtrC Name() const {return *iName;}
	private:
		enum
			{
			EFlagNameIsFileName					=0x00000001,
			EFlagFileIsConversionPlugInLibrary	=0x00000002
			};
	private:
		inline TBool FileIsConversionPlugInLibrary() const {return iFlags&EFlagFileIsConversionPlugInLibrary;}
	private:
		TUint iIdentifier;
		TUint iFlags;
		HBufC* iName;
	private:
		friend class CCnvCharacterSetConverter;
		friend class CDeepDestructingArrayOfCharactersSets;
		};
	
/**
 *
 * Holds an ascending array of the indices of the characters in the
 * source Unicode text which could not be converted by
 * <code>CCnvCharacterSetConverter::ConvertFromUnicode()</code> into the
 * foreign character set.
 * @since 6.0
 * @lib "charconv.lib"
 */

	class TArrayOfAscendingIndices
		{
	public:
		
/**
 *
 * The return value of
 * <code>CCnvCharacterSetConverter::AppendIndex()</code>.
 * @since 
 */
		enum TAppendResult
			{
			/** The append failed. */
			EAppendFailed,
			/** The append succeeded. */
			EAppendSuccessful
			};
	public:
		
/**
 *
 * C++ constructor.
 *
 * The array is initialised to be of length zero.
 *
 */

		inline TArrayOfAscendingIndices() :iArrayOfIndices(0) {}
		IMPORT_C TAppendResult AppendIndex(TInt aIndex);
		
/**
 *
 * Deletes a single index from the array.
 *
 * @param     "TInt aIndexOfIndex"
 *            The index of the index to delete. Must not be negative
 *            and must not be greater than the length of the array,
 *            or a panic occurs.
 */

		inline void Remove(TInt aIndexOfIndex) {iArrayOfIndices.Delete(aIndexOfIndex, 1);}
		
/**
 *
 * Deletes all indices from the array.
 *
 * @since     6.1
 */

		inline void RemoveAll() {iArrayOfIndices.SetLength(0);}

/**
 *
 * Returns the number of indices in the array.
 *
 * @returns   "TInt"
 *            The number of indices in the array.
 */

		inline TInt NumberOfIndices() const {return iArrayOfIndices.Length();}

/**
 *
 * Gets the value of the specified index.
 *
 * @param     "TInt aIndexOfIndex"
 *            Index into the array.
 * @returns   "TInt"
 *            The value of the index.
 */

		inline TInt operator[](TInt aIndexOfIndex) const {return iArrayOfIndices[aIndexOfIndex];}
	private:
		enum {KMaximumNumberOfIndices=25};
	private:
		TBuf16<KMaximumNumberOfIndices> iArrayOfIndices;
		};
public:
	IMPORT_C static CCnvCharacterSetConverter* NewL();
	IMPORT_C static CCnvCharacterSetConverter* NewLC();
	IMPORT_C virtual ~CCnvCharacterSetConverter();
	IMPORT_C static CArrayFix<SCharacterSet>* CreateArrayOfCharacterSetsAvailableL(RFs& aFileServerSession);
	IMPORT_C static CArrayFix<SCharacterSet>* CreateArrayOfCharacterSetsAvailableLC(RFs& aFileServerSession);
	IMPORT_C TUint ConvertStandardNameOfCharacterSetToIdentifierL(const TDesC8& aStandardNameOfCharacterSet, RFs& aFileServerSession);
	IMPORT_C HBufC8* ConvertCharacterSetIdentifierToStandardNameL(TUint aCharacterSetIdentifier, RFs& aFileServerSession);
	IMPORT_C TUint ConvertMibEnumOfCharacterSetToIdentifierL(TInt aMibEnumOfCharacterSet, RFs& aFileServerSession);
	IMPORT_C TInt ConvertCharacterSetIdentifierToMibEnumL(TUint aCharacterSetIdentifier, RFs& aFileServerSession);
	IMPORT_C void PrepareToConvertToOrFromL(TUint aCharacterSetIdentifier, const CArrayFix<SCharacterSet>& aArrayOfCharacterSetsAvailable, RFs& aFileServerSession);
	IMPORT_C TAvailability PrepareToConvertToOrFromL(TUint aCharacterSetIdentifier, RFs& aFileServerSession);
	// the following attribute-setting functions should be called (if at all) after calling PrepareToConvertToOrFromL and before calling ConvertFromUnicode and/or ConvertToUnicode
	IMPORT_C void SetDefaultEndiannessOfForeignCharacters(TEndianness aEndianness);
	IMPORT_C void SetDowngradeForExoticLineTerminatingCharacters(TDowngradeForExoticLineTerminatingCharacters aDowngradeForExoticLineTerminatingCharacters); // by default this attribute is set to EDowngradeExoticLineTerminatingCharactersToCarriageReturnLineFeed
	IMPORT_C void SetReplacementForUnconvertibleUnicodeCharactersL(const TDesC8& aReplacementForUnconvertibleUnicodeCharacters); // must be a single character preceded by its escape sequence (if any), and must be little-endian if the endianness of the character-set is unspecified, otherwise in the same endianness as the character-set
	// the conversion functions return either one of the TError values above, or the number of unconverted elements left at the end of the input descriptor
	IMPORT_C TInt ConvertFromUnicode(TDes8& aForeign, const TDesC16& aUnicode) const;
	IMPORT_C TInt ConvertFromUnicode(TDes8& aForeign, const TDesC16& aUnicode, TInt& aNumberOfUnconvertibleCharacters) const;
	IMPORT_C TInt ConvertFromUnicode(TDes8& aForeign, const TDesC16& aUnicode, TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstUnconvertibleCharacter) const;
	IMPORT_C TInt ConvertFromUnicode(TDes8& aForeign, const TDesC16& aUnicode, TArrayOfAscendingIndices& aIndicesOfUnconvertibleCharacters) const;
	IMPORT_C TInt ConvertToUnicode(TDes16& aUnicode, const TDesC8& aForeign, TInt& aState) const;
	IMPORT_C TInt ConvertToUnicode(TDes16& aUnicode, const TDesC8& aForeign, TInt& aState, TInt& aNumberOfUnconvertibleCharacters) const;
	IMPORT_C TInt ConvertToUnicode(TDes16& aUnicode, const TDesC8& aForeign, TInt& aState, TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter) const;
	IMPORT_C static void AutoDetectCharacterSetL(TInt& aConfidenceLevel, TUint& aCharacterSetIdentifier, const CArrayFix<SCharacterSet>& aArrayOfCharacterSetsAvailable, const TDesC8& aSample);
	IMPORT_C static void ConvertibleToCharacterSetL(TInt& aConfidenceLevel, const TUint aCharacterSetIdentifier,const CArrayFix<SCharacterSet>& aArrayOfCharacterSetsAvailable, const TDesC8& aSample);
	// the following functions are only to be called by conversion plug-in libraries
	IMPORT_C static TInt DoConvertFromUnicode(const SCnvConversionData& aConversionData, TEndianness aDefaultEndiannessOfForeignCharacters, const TDesC8& aReplacementForUnconvertibleUnicodeCharacters, TDes8& aForeign, const TDesC16& aUnicode, TArrayOfAscendingIndices& aIndicesOfUnconvertibleCharacters);
	IMPORT_C static TInt DoConvertFromUnicode(const SCnvConversionData& aConversionData, TEndianness aDefaultEndiannessOfForeignCharacters, const TDesC8& aReplacementForUnconvertibleUnicodeCharacters, TDes8& aForeign, const TDesC16& aUnicode, TArrayOfAscendingIndices& aIndicesOfUnconvertibleCharacters, TUint& aOutputConversionFlags, TUint aInputConversionFlags);
	IMPORT_C static TInt DoConvertToUnicode(const SCnvConversionData& aConversionData, TEndianness aDefaultEndiannessOfForeignCharacters, TDes16& aUnicode, const TDesC8& aForeign, TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter);
	IMPORT_C static TInt DoConvertToUnicode(const SCnvConversionData& aConversionData, TEndianness aDefaultEndiannessOfForeignCharacters, TDes16& aUnicode, const TDesC8& aForeign, TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter, TUint& aOutputConversionFlags, TUint aInputConversionFlags);
	IMPORT_C static const SCnvConversionData& AsciiConversionData();
private:
	enum
		{
		EStoredFlagOwnsConversionData				=0x00000001,
		EStoredFlagConversionPlugInLibraryIsLoaded	=0x00000002
		};
	enum TCharacterSetSearch
		{
		EStopCharacterSetSearch,
		EContinueCharacterSetSearch
		};
	enum TConversionPlugInFunctionOrdinals
		{
		EReplacementForUnconvertibleUnicodeCharacters=1,
		EConvertFromUnicode=2,
		EConvertToUnicode=3,
		EIsInThisCharacterSet=4
		};
	typedef const TDesC8& (*FReplacementForUnconvertibleUnicodeCharacters)();
	typedef TInt (*FConvertFromUnicode)(TEndianness aDefaultEndiannessOfForeignCharacters, const TDesC8& aReplacementForUnconvertibleUnicodeCharacters, TDes8& aForeign, const TDesC16& aUnicode, TArrayOfAscendingIndices& aIndicesOfUnconvertibleCharacters);
	typedef TInt (*FConvertToUnicode)(TEndianness aDefaultEndiannessOfForeignCharacters, TDes16& aUnicode, const TDesC8& aForeign, TInt& aState, TInt& aNumberOfUnconvertibleCharacters, TInt& aIndexOfFirstByteOfFirstUnconvertibleCharacter);
	typedef TBool (*FIsInThisCharacterSetL)(TBool& aSetToTrue, TInt& aConfidenceLevel, const TDesC8& aSample); // added in 6.1 as the 4th-ordinal exported function in the CONVPLUG interface
private:
	CCnvCharacterSetConverter();
	void ConstructL();
	static CArrayFix<SCharacterSet>* DoCreateArrayOfCharacterSetsAvailableLC(RFs& aFileServerSession, TUint aIdentifierOfOnlyCharacterSetOfInterest);
	static TCharacterSetSearch AppendHardCodedCharacterSetIfRequiredL(CArrayFix<SCharacterSet>& aArrayOfCharacterSets, TUint aIdentifierOfOnlyCharacterSetOfInterest, TUint aIdentifierOfHardCodedCharacterSet, const TDesC& aNameOfHardCodedCharacterSet);
	void ScanForStandardNamesAndMibEnumsL(RFs& aFileServerSession);
	void ScanForStandardNamesAndMibEnumsROMOnlyL(RFs& aFileServerSession);
	TAvailability DoPrepareToConvertToOrFromL(TUint aCharacterSetIdentifier, const CArrayFix<SCharacterSet>* aArrayOfCharacterSetsAvailable, RFs& aFileServerSession);
	static void DeleteConversionData(const SCnvConversionData* aConversionData);
	static void DeleteConversionData(TAny* aConversionData);
	static TEndianness EndiannessOfForeignCharacters(const SCnvConversionData& aConversionData, TEndianness aDefaultEndiannessOfForeignCharacters);
private:
	TUint iStoredFlags;
	TUint iCharacterSetIdentifierOfLoadedConversionData; // 0 or a UID
	TInt iIndexOfConversionPlugInLibrary;
	RLibrary iConversionPlugInLibrary[2];
	const SCnvConversionData* iConversionData;
	TEndianness iDefaultEndiannessOfForeignCharacters;
	TDowngradeForExoticLineTerminatingCharacters iDowngradeForExoticLineTerminatingCharacters;
	TBuf8<KMaximumLengthOfReplacementForUnconvertibleUnicodeCharacters> iReplacementForUnconvertibleUnicodeCharacters;
	CStandardNamesAndMibEnums* iStandardNamesAndMibEnums;
	};

#endif

