// COEINPUT.H
//
// Copyright (c) Symbian Software Ltd 1997 - 2004. All rights reserved.
//

#if !defined(__COEINPUT_H__)
#define __COEINPUT_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

// classes defined in FEPBASE, declared here
class MCoeFepAwareTextEditor;
class MCoeCaptionRetrieverForFep;

class MObjectProvider;

/** 
 * The <code>TCoeInputCapabilities</code> class describes which forms of text 
 * input are consumed by a control or view.
 *
 * @lib [what]
 * @publishedAll 
 * @released 
 */
class TCoeInputCapabilities

	{
public:
	/** 
     * The enumeration specifies the text input capability flags. These are 
     * used to define the text input capabilities of a control or view. 
     */
	enum
		{
		/** no text input capabilities are supported */
		ENone							=0,
		/** supports positive western integers */
		EWesternNumericIntegerPositive	=0x00000001,
		/** supports negative western integers */
		EWesternNumericIntegerNegative	=0x00000002,
		/** supports real numbers */
		EWesternNumericReal				=0x00000004,
		/** supports the western alphabets */
		EWesternAlphabetic				=0x00000008,
		/** supports Hiragana */
		EJapaneseHiragana				=0x00000010,
		/** supports half-width Katakana */
		EJapaneseKatakanaHalfWidth		=0x00000020,
		/** supports full-width Katakana */
		EJapaneseKatakanaFullWidth		=0x00000040,
		/** supports dialable characters */
		EDialableCharacters				=0x00000080,
		/** 
         * supports secret text. This is text in which characters appear 
		 * as asterisks 
         */
		ESecretText						=0x00000100,
		/** 
         * supports automatic sentence case. This is text in which the first 
         * word in a sentence begins with an uppercase letter, with all other 
         * letters and words in lowercase
         */
		EAutoSentenceCase				=0x00000200,
		/** supports all types of text */
		EAllText						=0x01000000,
		/** 
         * supports navigation keys, including arrow keys, page-up,
		 * page-down, home, end, and tab keys, etc. 
         */
		ENavigation						=0x02000000
		};
	class MCoeFepSpecificExtensions; // to be defined by concrete FEPs, declared here
public:
	// all these functions are exported (rather than inline) so that binary compatibility becomes easier to maintain
    /**
    * [what]
    * 
    * @param aCapabilities [what]
    * @remarks
    * @see
    */
    IMPORT_C TCoeInputCapabilities(TUint aCapabilities);
    /**
    * [what]
    * 
    * @param aCapabilities [what]
    * @param aFepAwareTextEditor [what]
    * @param aCaptionRetrieverForFep [what]
    * @remarks
    * @see
    */
	IMPORT_C TCoeInputCapabilities(TUint aCapabilities, MCoeFepAwareTextEditor* aFepAwareTextEditor, MCoeCaptionRetrieverForFep* aCaptionRetrieverForFep);
    /**
    * [what]
    * 
    * @param aCapabilities [what]
    * @param aFepAwareTextEditor [what]
    * @param aCaptionRetrieverForFep [what]
    * @param aFepUid [what]
    * @param aFepSpecificExtensions [what]
    * @remarks
    * @see
    */
	IMPORT_C TCoeInputCapabilities(TUint aCapabilities, MCoeFepAwareTextEditor* aFepAwareTextEditor, MCoeCaptionRetrieverForFep* aCaptionRetrieverForFep, TUid aFepUid, MCoeFepSpecificExtensions* aFepSpecificExtensions);
    /**
    * [what]
    * 
    * @param aAnother [what]
    * @remarks
    * @see
    */
	IMPORT_C TCoeInputCapabilities(const TCoeInputCapabilities& aAnother); // defined so that iSpareForFutureUse is not copied
    /**
    * [what]
    * 
    * @param aAnother [what]
    * @return
    * @remarks
    * @see
    */
	IMPORT_C TCoeInputCapabilities& operator=(const TCoeInputCapabilities& aAnother); // defined so that iSpareForFutureUse is not copied
    /**
    * [what]
    * 
    * @param aAnother [what]
    * @return
    * @remarks
    * @see
    */
	IMPORT_C TBool operator==(const TCoeInputCapabilities& aAnother) const; // defined so that iSpareForFutureUse is not tested
    /**
    * [what]
    * 
    * @param aAnother [what]
    * @return
    * @remarks
    * @see
    */
	IMPORT_C TBool operator!=(const TCoeInputCapabilities& aAnother) const; // defined so that iSpareForFutureUse is not tested
    /**
    * [what]
    * 
    * @param aAnother [what]
    * @remarks
    * @see
    */
	IMPORT_C void MergeWith(const TCoeInputCapabilities& aAnother);
    /**
    * [what]
    * 
    * @param aCapabilities [what]
    * @remarks
    * @see
    */
	IMPORT_C void SetCapabilities(TUint aCapabilities);
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TUint Capabilities() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool IsNone() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool SupportsWesternNumericIntegerPositive() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool SupportsWesternNumericIntegerNegative() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool SupportsWesternNumericReal() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool SupportsWesternAlphabetic() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool SupportsJapaneseHiragana() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool SupportsJapaneseKatakanaHalfWidth() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool SupportsJapaneseKatakanaFullWidth() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool SupportsDialableCharacters() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool SupportsSecretText() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool SupportsAutoSentenceCase() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool SupportsAllText() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C TBool SupportsNavigation() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C MCoeFepAwareTextEditor* FepAwareTextEditor() const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C MCoeCaptionRetrieverForFep* CaptionRetrieverForFep() const;
    /**
    * [what]
    * 
    * @param aFepUid [what]
    * @return [what]
    * @remarks
    * @see
    */
	IMPORT_C MCoeFepSpecificExtensions* FepSpecificExtensions(TUid aFepUid) const;
    /**
    * [what]
    * 
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C MObjectProvider* ObjectProvider() const;
    /**
    * [what]
    * 
    * @param aObjectProvider [what]
    * @return [what]
    * @remarks
    * @see
    */
    IMPORT_C void SetObjectProvider(MObjectProvider* aObjectProvider);

private:
	TUint iCapabilities;
	MCoeFepAwareTextEditor* iFepAwareTextEditor;
	MCoeCaptionRetrieverForFep* iCaptionRetrieverForFep;
	TUint iFepUid;
	MCoeFepSpecificExtensions* iFepSpecificExtensions;
    MObjectProvider* iObjectProvider;
    TAny* iSpareForFutureUse[5];
	};

#endif
