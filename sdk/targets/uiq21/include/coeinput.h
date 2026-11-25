// COEINPUT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEINPUT_H__)
#define __COEINPUT_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

// classes defined in FEPBASE, declared here
class MCoeFepAwareTextEditor;
class MCoeCaptionRetrieverForFep;

/**
 *
 * Describes which forms of text input are consumed by a control or view.
 * @since 6.0
 * @lib "cone.lib"
 */
class TCoeInputCapabilities
	{
public:
	/**
	 * Text input capability flags.
	 * These are used to define the text input capabilities of a control or
	 * view.
	 */
	enum
		{
		ENone							=0,				/** No text input capabilities supported. */
		EWesternNumericIntegerPositive	=0x00000001,	/** Supports positive western integers. */
		EWesternNumericIntegerNegative	=0x00000002,	/** Supports negative western integers. */
		EWesternNumericReal				=0x00000004,	/** Supports real numbers. */
		EWesternAlphabetic				=0x00000008,	/** Supports the western alphabets. */
		EJapaneseHiragana				=0x00000010,	/** Supports Hiragana. */
		EJapaneseKatakanaHalfWidth		=0x00000020,	/** Supports half width Katakana. */
		EJapaneseKatakanaFullWidth		=0x00000040,	/** Supports full width Katakana. */
		EDialableCharacters				=0x00000080,	/** Supports dialable characters */

		/** Supports secret text. This is text in which entered characters appear
		as asterisks.
		 */
		ESecretText						=0x00000100,
		EAllText						=0x01000000,	/** Supports all types of text. */

		/** Supports navigation keys. These keys include arrow keys, page-up,
		page-down, home, end, tab, etc.
		 */
		ENavigation						=0x02000000
		};
	class MCoeFepSpecificExtensions; // to be defined by concrete FEPs, declared here
public:
	// all these functions are exported (rather than inline) so that binary compatibility becomes easier to maintain
	IMPORT_C TCoeInputCapabilities(TUint aCapabilities);
	IMPORT_C TCoeInputCapabilities(TUint aCapabilities, MCoeFepAwareTextEditor* aFepAwareTextEditor, MCoeCaptionRetrieverForFep* aCaptionRetrieverForFep);
	IMPORT_C TCoeInputCapabilities(TUint aCapabilities, MCoeFepAwareTextEditor* aFepAwareTextEditor, MCoeCaptionRetrieverForFep* aCaptionRetrieverForFep, TUid aFepUid, MCoeFepSpecificExtensions* aFepSpecificExtensions);
	IMPORT_C TCoeInputCapabilities(const TCoeInputCapabilities& aAnother); // defined so that iSpareForFutureUse is not copied
	IMPORT_C TCoeInputCapabilities& operator=(const TCoeInputCapabilities& aAnother); // defined so that iSpareForFutureUse is not copied
	IMPORT_C TBool operator==(const TCoeInputCapabilities& aAnother) const; // defined so that iSpareForFutureUse is not tested
	IMPORT_C TBool operator!=(const TCoeInputCapabilities& aAnother) const; // defined so that iSpareForFutureUse is not tested
	IMPORT_C void MergeWith(const TCoeInputCapabilities& aAnother);
	IMPORT_C void SetCapabilities(TUint aCapabilities);
	IMPORT_C TUint Capabilities() const;
	IMPORT_C TBool IsNone() const;
	IMPORT_C TBool SupportsWesternNumericIntegerPositive() const;
	IMPORT_C TBool SupportsWesternNumericIntegerNegative() const;
	IMPORT_C TBool SupportsWesternNumericReal() const;
	IMPORT_C TBool SupportsWesternAlphabetic() const;
	IMPORT_C TBool SupportsJapaneseHiragana() const;
	IMPORT_C TBool SupportsJapaneseKatakanaHalfWidth() const;
	IMPORT_C TBool SupportsJapaneseKatakanaFullWidth() const;
	IMPORT_C TBool SupportsDialableCharacters() const;
	IMPORT_C TBool SupportsSecretText() const;
	IMPORT_C TBool SupportsAllText() const;
	IMPORT_C TBool SupportsNavigation() const;
	IMPORT_C MCoeFepAwareTextEditor* FepAwareTextEditor() const;
	IMPORT_C MCoeCaptionRetrieverForFep* CaptionRetrieverForFep() const;
	IMPORT_C MCoeFepSpecificExtensions* FepSpecificExtensions(TUid aFepUid) const;
private:
	TUint iCapabilities;
	MCoeFepAwareTextEditor* iFepAwareTextEditor;
	MCoeCaptionRetrieverForFep* iCaptionRetrieverForFep;
	TUint iFepUid;
	MCoeFepSpecificExtensions* iFepSpecificExtensions;
	TAny* iSpareForFutureUse[6];
	};

#endif
