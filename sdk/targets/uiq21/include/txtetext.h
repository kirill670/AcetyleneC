// TXTETEXT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTETEXT_H__
#define __TXTETEXT_H__

#include <e32std.h>
#include <e32base.h>
#include <fldset.h>
#include <s32std.h>


// Forward references
class CParaFormatLayer;
class CCharFormatLayer;
class MTextFieldFactory;
class CTextFieldSet;
class CTextField;
class TFindFieldInfo;
class CInlineEditData;
class MFepInlineTextFormatRetriever;
class TCharFormat;
class CEditableTextOptionalData;
class RFs;


// UIDs
const TUid KPlainTextFieldDataUid = {268435555};
const TUid KEditableTextUid = {268450334};
const TUid KPlainTextCharacterDataUid = {268450341};
const TUid KClipboardUidTypePlainText = {268450333};


const TInt KMaxFieldBufferSize=0x14;


/*
An abstract base class for editable text.
It contains some data, including optional FEP inline editing information.
*/

/**
 *
 * <code>A</code>n abstract base class which defines the behaviour that
 * all classes in the editable text class hierarchy
 * (<code>CPlainText</code>, <code>CGlobalText</code> and
 * <code>CRichText</code>) must provide.
 *
 * It provides no storage for text or text formatting, so it is not
 * directly usable. It defines protocols for editing the contents of a
 * text object and for extracting format data from a text object which
 * supports formatting.Note: when specifying a position in a text object
 * (the document position), zero is before the first character in the
 * document. If the document contains n characters, position n is after
 * the last character. Valid document positions are therefore between
 * zero and the length of the document, inclusive. Many editable text
 * functions raise a panic if a specified document position is
 * invalid.Note also that the functions which implement support for
 * front-end-processor inline editing are intended for internal use only
 * by Symbian.
 *
 * @since 5.0
 * @lib " etext.lib "
 */

class CEditableText : public CBase
	{
public:
	IMPORT_C ~CEditableText();
	IMPORT_C TStreamId StoreL(CStreamStore& aStore) const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId);

	// virtual persistence functions
	virtual void ExternalizeL(RWriteStream& aStream) const;
	virtual void InternalizeL(RReadStream& aStream);
	
/**
 *
 * Stores the text components, e.
 *
 * g. fields, pictures and formatting to the stream store specified. Does
 * not store the text content.
 *
 * @param     " CStreamStore& aStore "
 *            Stream store to which the text components are written.
 * @param     " CStoreMap& aMap "
 *            A store map. This binds the address of text components
 *            to the stream ID of <code>aStore</code>. This is
 *            needed to support deferred loading of pictures in rich
 *            text.
 */

	virtual void StoreComponentsL(CStreamStore& aStore,CStoreMap& aMap) const = 0;
	
/**
 *
 * Restores the text components, e.
 *
 * g. fields, pictures and formatting from the stream store. Does not
 * restore the text content.
 *
 * @param     " const CStreamStore& aStore "
 *            The stream store from which the text components are
 *            restored.
 */

	virtual void RestoreComponentsL(const CStreamStore& aStore) = 0;

	// modifier functions
	
/**
 *
 * Deletes the text content and components from the text object, leaving
 * the single end-of-text paragraph delimiter.
 *
 */

	virtual void Reset() = 0;
	
/**
 *
 * Inserts a single character or a descriptor into the text object at a
 * specified document position.
 *
 * @param     " TInt aInsertPos "
 *            A valid document position at which to insert the
 *            character or descriptor.
 * @param     " const TChar& aChar "
 *            The character to insert.
 * @param     " const TDesC& aBuf "
 *            The descriptor to insert.
 */

	virtual void InsertL(TInt aInsertPos,const TChar& aChar) = 0;
	virtual void InsertL(TInt aInsertPos,const TDesC& aBuf) = 0;
	
/**
 *
 * Deletes one or more characters beginning at (and including) the
 * character at the specified document position.
 *
 * @param     " TInt aPos "
 *            The document position from which to delete.
 * @param     " TInt aLength "
 *            The number of characters to delete.
 * @returns   " TBool "
 *            Indicates whether or not two paragraphs have been
 *            merged as a result of the delete, so that the
 *            resulting paragraph needs to be reformatted. This
 *            value is only relevant to rich text, so for plain and
 *            global text implementations, the function always
 *            returns <code>EFalse</code>.
 */

	virtual TBool DeleteL(TInt aPos,TInt aLength) = 0;

	// interrogation functions
	
/**
 *
 * Gets a read-only pointer descriptor to a portion of the text.
 *
 * @param     " TInt aStartPos "
 *            A valid document position from which to read.
 * @param     " TInt aLength "
 *            If specified, the number of characters to read,
 *            inclusive of the character at position
 *            <code>aStartPos</code>. If not specified, the read
 *            continues to the end of the document, or the end of
 *            the segment if using segmented storage.
 * @returns   " TPtrC "
 *            Read-only pointer descriptor to a portion of the text.
 */

	virtual TPtrC Read(TInt aStartPos) const = 0;
	virtual TPtrC Read(TInt aStartPos,TInt aLength) const = 0;
	
/**
 *
 * Copies a portion of the text into a descriptor.
 *
 * Starts at the position specified and continues to the end of the
 * document. A length may optionally be specified.
 *
 * @param     " TDes& aBuf "
 *            Buffer which on return contains the extracted text.
 * @param     " TInt aPos=0 "
 *            The document position from which to copy. Must be a
 *            valid position, or a panic occurs.
 * @param     " TInt aLength "
 *            If specified, the number of characters to copy.
 */

	virtual void Extract(TDes& aBuf,TInt aPos=0) const = 0;
	virtual void Extract(TDes& aBuf,TInt aPos,TInt aLength) const = 0;

	// copy and paste
	
/**
 *
 * Copies a portion of the text to the clipboard.
 *
 * @param     " CStreamStore& aStore "
 *            The clipboard's store (see class
 *            <code>CClipboard</code>).
 * @param     " CStreamDictionary& aDictionary "
 *            The clipboard's stream dictionary (see class
 *            <code>CClipboard</code>).
 * @param     " TInt aPos "
 *            A valid document position from which to begin copying.
 * @param     " TInt aLength "
 *            The number of characters to copy.
 */

	virtual void CopyToStoreL(CStreamStore& aStore,CStreamDictionary& aDictionary,TInt aPos,TInt aLength) const = 0;
	
/**
 *
 * Pastes the contents of the clipboard into the text object at the
 * specified document position.
 *
 * @param     " const CStreamStore& aStore "
 *            The clipboard's store (see class
 *            <code>CClipboard</code>).
 * @param     " const CStreamDictionary& aDictionary "
 *            The clipboard's stream dictionary (see class
 *            <code>CClipboard</code>).
 * @param     " TInt aPos "
 *            A valid document position at which to paste the text.
 * @returns   " TInt "
 *            The number of characters pasted.
 */

	virtual TInt PasteFromStoreL(const CStreamStore& aStore,const CStreamDictionary& aDictionary,TInt aPos) = 0;

	// utility functions
	
/**
 *
 * Returns a count of the number of words in the document.
 *
 * @returns   " TInt "
 *            The number of words in the document
 */

	virtual TInt WordCount() const = 0;
	
/**
 *
 * Returns a count of the number of paragraphs in the document.
 *
 * @returns   " TInt "
 *            The number of paragraphs in the document. Notes: The
 *            end-of-text paragraph delimiter at the end of every
 *            document means this function always returns a count of
 *            at least one.
 */

	virtual TInt ParagraphCount() const = 0;
	
/**
 *
 * Returns a count of the number of characters in the document, excluding
 * the end-of-text paragraph delimiter.
 *
 * @returns   " TInt "
 *            The number of characters in the document.
 */

	virtual TInt DocumentLength() const = 0;
	
/**
 *
 * Updates a document position to the start of the paragraph.
 *
 * @param     " TInt& aPos "
 *            Initially specifies a valid document position. On
 *            return, set to the document position of the first
 *            character in the paragraph.
 * @returns   " TInt "
 *            The number of characters skipped in scanning to the
 *            start of the paragraph.
 */

	virtual TInt ToParagraphStart(TInt& aPos) const = 0;
	inline TBool HasChanged() const;
	
/**
 *
 * Returns the start position and length of the word that contains the
 * specified document position.
 *
 * @param     " TInt aCurrentPos "
 *            A valid document position.
 * @param     " TInt& aStartPos "
 *            On return, the document position of the first
 *            character in the word containing document position
 *            <code>aCurrentPos</code>.
 * @param     " TInt& aLength "
 *            On return, the length of the word containing document
 *            position <code>aCurrentPos</code>. Does not include
 *            the trailing word delimiter character.
 * @param     " TBool aPictureIsDelimiter "
 *            Specifies whether picture characters should be
 *            considered to be word delimiters. For example, this
 *            value might be <code>EFalse</code> when navigating a
 *            document, but <code>ETrue</code> when carrying out
 *            spell checking.
 * @param     " TBool aPunctuationIsDelimiter "
 *            Specifies whether puncutation characters should be
 *            considered to be word delimiters.
 */

	virtual void GetWordInfo(TInt aCurrentPos,TInt& aStartPos,TInt& aLength,
							 TBool aPictureIsDelimiter,TBool aPunctuationIsDelimiter) const = 0;
	IMPORT_C virtual TInt ScanWords(TInt& aPos,TUint& aScanMask) const;
	IMPORT_C virtual TInt ScanParas(TInt& aPos,TUint& aScanMask) const;
	IMPORT_C virtual void SetHasChanged(TBool aHasChanged);

	// Internal to Symbian - support for front-end-processor inline editing
	IMPORT_C void StartFepInlineEditL(TBool& aParagraphContainingStartPositionOfInlineTextHasChangedFormat,TInt& aNumberOfCharactersSuccessfullyDeleted,TInt& aNumberOfCharactersSuccessfullyInserted,TInt& aPositionOfInsertionPointInDocument,TInt aNewPositionOfInsertionPointInDocument,const TDesC& aInitialInlineText,TInt aPositionOfInlineTextInDocument,TInt aNumberOfCharactersToHide,MFepInlineTextFormatRetriever& aInlineTextFormatRetriever);
	IMPORT_C void UpdateFepInlineTextL(TBool& aParagraphContainingStartPositionOfInlineTextHasChangedFormat,TInt& aNumberOfCharactersSuccessfullyDeleted,TInt& aNumberOfCharactersSuccessfullyInserted,TInt& aPositionOfInsertionPointInDocument,TInt aNewPositionOfInsertionPointInDocument,const TDesC& aNewInlineText);
	IMPORT_C void CommitFepInlineEditL(TBool& aParagraphContainingStartPositionOfInlineTextHasChangedFormat,TInt& aNumberOfCharactersSuccessfullyDeleted,TInt& aNumberOfCharactersSuccessfullyInserted,TInt& aPositionOfInsertionPointInDocument,TInt aNewPositionOfInsertionPointInDocument);
	IMPORT_C void CancelFepInlineEdit(TBool& aParagraphContainingStartPositionOfInlineTextHasChangedFormat,TInt& aNumberOfCharactersSuccessfullyDeleted,TInt& aNumberOfCharactersSuccessfullyInserted,TInt& aPositionOfInsertionPointInDocument,TInt aNewPositionOfInsertionPointInDocument);

	IMPORT_C virtual void Reserved_1();

	
/**
 *
 * Storage type.
 * @since 
 */

	enum TDocumentStorage
		{
		/** Storage uses a flat buffer (<code>CBufFlat</code>). */
		EFlatStorage, 
		/** Storage uses a segmented buffer (<code>CBufSeg</code>). */
		ESegmentedStorage
		};
/**
 *
 * Miscellaneous constants.
 * @since 
 */
	enum 
		{
		/** Granularity of the buffer, default 256 characters. */
		EDefaultTextGranularity = 256
		};

	/*
	Useful Unicode character definitions.
	ETEXT uses standard Unicode to store its text. In particular 0x2029 and 0x2028 are used
	as paragraph separator and forced line break respectively.
	*/

	enum
		{								// Unicode name, etc.
		/** Tab stop. */
		ETabCharacter = 0x0009,			// horizontal tabulation
		/** New page. */
		EPageBreak = 0x000C,			// form feed
		/** Visible space character. */
		ESpace = 0x0020,				// space
		EApostrophe = 0x0027,			// apostrophe
		EHyphenMinus = 0x002D,			// hyphen-minus; generally used for hyphen, but see 0x2010
		/** A hard (non-breaking) space. */
		ENonBreakingSpace = 0x00A0,		// no-break space
		/** A soft hyphen (ensures that a hyphen followed by a new line will be
		inserted at that point should a line break be required anywhere within
		the word).
		 */
		EPotentialHyphen = 0x00AD,		// soft hyphen
		EHyphen = 0x2010,				// hyphen; intended as an unambiguous hyphen codepoint
		/** A hard (non-breaking) hyphen. */
		ENonBreakingHyphen = 0x2011,	// non-breaking hyphen
		ELeftSingleQuote = 0x2018,		// left single quotation mark
		ERightSingleQuote = 0x2019,		// right single quotation mark
		ELeftDoubleQuote = 0x201C,		// left double quotation mark
		ERightDoubleQuote = 0x201D,		// right double quotation mark
		EBullet = 0x2022,				// bullet
		EEllipsis = 0x2026,				// horizontal ellipsis
		/** Forced line break. */
		ELineBreak = 0x2028,			// line separator
		/** Paragraph delimiter. */
		EParagraphDelimiter = 0x2029,	// paragraph separator
		/** Represents a picture inserted into the text object. */
		EPictureCharacter = 0xFFFC,		// object replacement character
		EZeroWidthNoBreakSpace = 0xFEFF,// zero-width no-break space
		EByteOrderMark = 0xFEFF,		// byte order mark; SAME AS zero-width no-break space
		EReversedByteOrderMark = 0xFFFE	// not a character; evidence of endianness opposite to that of platform
		};

protected:
	// support for front-end-processor inline-editing
	IMPORT_C void OverrideFormatOfInlineTextIfApplicable(TPtrC& aView,TCharFormat& aFormat,TInt aStartPos) const;

	TBool iHasChanged;

private:
	void SetAndTransferOwnershipOfInlineEditDataL(CInlineEditData* aInlineEditData);
	CInlineEditData* InlineEditData() const;
	void DeleteInlineEditDataAndSetToNull();

	CEditableTextOptionalData* iOptionalData;
	};


// Information relating to the number of components owned by an editable text instance.

/**
 *
 * Provides information about the number of components owned by an
 * editable text object.
 *
 * Components are fields and (rich text only), pictures and styles.An
 * instance of this class is returned by
 * <code>CPlainText::ComponentInfo()</code> and by
 * <code>CRichText::ComponentInfo()</code>.
 *
 * @since 5.0
 * @lib " etext.lib "
 */

class TEtextComponentInfo
	{
public:
	IMPORT_C TEtextComponentInfo();
	IMPORT_C TEtextComponentInfo(TInt aFieldCount,TInt aPictureCount,TInt aStyleCount);
public:
	TInt iFieldCount;
	TInt iPictureCount;
	TInt iStyleCount;
	};

/**
 *
 * Page table.
 *
 * The page table is an array of integers; each integer represents the
 * number or characters on a page.
 *
 * @since 5.0
 * @lib ""
 */

typedef CArrayFix<TInt> TPageTable;
	
/**
CPlainText stores unformatted Unicode text, and provides the following services among others:
externalization and internalization; import from, and export to, arbitrary streams, optionally
translating between Unicode and other encodings; reading and writing of field data; extraction
of Unicode text; finding word and paragraph boundaries.
*/

/**
 *
 * Stores and manipulates plain text.
 *
 * Plain text cannot be displayed, so this class provides no support for
 * formatting. It is purely an in-memory buffer for text, and provides
 * services that act upon it. These services include the following:
 * import from and export to streams, optionally translating between
 * Unicode and other encodings; reading and writing of field data;
 * extraction of text; finding word and paragraph boundaries.The type and
 * size of in-memory buffer can be specified upon object construction.
 * However, if no specification is provided a buffer is provided with
 * default settings. There are two types of storage buffer: segmented
 * buffers and flat buffers. The default buffer for plain text is
 * segmented (<code>CBufSeg</code>). This is most efficient when a large
 * quantity of text is to be stored, or will have a large dynamic range.
 * A flat buffer (<code>CBufFlat</code>) is most appropriate for storing
 * small quantities of text of bounded length. For most uses, however, a
 * segmented buffer is sufficient.
 *
 * @since 5.0
 * @lib " etext.lib "
 */

class CPlainText: public CEditableText
	{
public:
	
/**
 *
 * Line delimiter translation.
 * @since 
 */

	enum TTextOrganisation
		{
		/** When importing text from a text file, all line feeds are converted
		into paragraph delimiters.When exporting text to a text file, lines do
		not wrap and paragraph delimiters are converted into CR/LF pairs.
		 */
		EOrganiseByParagraph,
		/** When importing text from a text file, a single line feed or a line
		feed followed by a carriage return is converted into a space
		character. A line feed which is followed by another line feed is
		converted into a <code>CEditableText::EParagraphDelimiter</code>.When
		exporting text to a text file, lines wrap at the specified wrap width
		and paragraph delimiters are converted into CR/LFs pairs.
		 */
		EOrganiseByLine
		};

	/**
	 *
	 * Scan mask values.
	 * @since 
	 */

	enum
		{
		/** Scan direction is backwards. The default is forwards. */
		EScanBackwards = 0x01,
		/** If the current document position is a word or paragraph boundary, no
		scan occurs.*/
		EScanStayIfBoundary = 0x02,
		/** Scan to the first character in the word or paragraph. */
		EScanToUnitStart = 0x04,
		/** Scan to the last character in the word or paragraph. */
		EScanToUnitEnd = 0x08,
		/** Treat adjacent word or paragraph delimiters as a single delimiter.
		Required when performing a word count, for example.
		 */
		EScanJoinDelimiters = 0x10,
		/** Picture characters are considered to be word delimiters. */
		EScanPictureIsDelimiter = 0x20,
		/** Punctuation characters, except hyphens and apostrophes, are considered
		to be word delimiters. */
		EScanPunctuationIsDelimiter = 0x40
		};

	/**
	 *
	 * Used in text scanning functions to indicate the end of the document
	 * has been passed.
	 * @since 
	 */

	enum TScanDataEnd
		{
		/** Indicates that a scan has passed the end of text paragraph delimiter. */
		EScanEndOfData = -1
		};

/**
 *
 * Parameters for importing or exporting text using
 * <code>CPlainText::ImportTextL()</code> or
 * <code>CPlainText::ExportTextL()</code>.
 * @since 6.1
 * @lib " etext.lib "
 */

	class TImportExportParam
		{
		public:
		
/**
 *
 * Default constructor.
 *
 * All member data is assigned default values. For details, see the
 * member data.
 *
 */

		TImportExportParam():
			iOrganisation(EOrganiseByParagraph),
			iMaxOutputChars(KMaxTInt),
			iMaxInputChars(KMaxTInt),
			iMaxLineLength(KMaxTInt),
			iOutputInternal(FALSE),
			iInputInternal(FALSE),
			iForeignEncoding(0),
			iGuessForeignEncoding(FALSE),
			iFileSession(NULL),
			iReserved(0)
			{
			}

		TTextOrganisation iOrganisation;
		TInt iMaxOutputChars;
		TInt iMaxInputChars;
		TInt iMaxLineLength;				// maximum line length when exporting text
		TBool iOutputInternal;				// output is in internal format, so write according to native endianness
		TBool iInputInternal;				// input is in internal format, so read according to native endianness
		TUint iForeignEncoding;				// if non-zero, UID of non-Unicode encoding to convert to or from
		TBool iGuessForeignEncoding;		// if true, guess the foreign encoding when importing; use
											// the guessed encoding if the confidence level is 50% or above
											// otherwise leave with KErrNotSupported
		RFs* iFileSession;					// if non-null, file session used by CHARCONV to load conversion data
		TUint iReserved;
		};

/**
 *
 * Results of importing or exporting text using
 * <code>CPlainText::ImportTextL()</code> or
 * <code>CPlainText::ExportTextL()</code>.
 * @since 6.1
 * @lib " etext.lib "
 */

	class TImportExportResult
		{
		public:
		
/**
 *
 * Default constructor.
 *
 * All member data is initialised to zero.
 *
 */

		TImportExportResult():
			iOutputChars(0),
			iInputChars(0),
			iForeignEncoding(0),
			iReserved(0)
			{
			}

		TInt iOutputChars;
		TInt iInputChars;
		TUint iForeignEncoding;				// foreign encoding actually used; useful if the encoding was guessed
		TUint iReserved;		
		};
			   
	IMPORT_C static CPlainText* NewL(TDocumentStorage aStorage = ESegmentedStorage,
									 TInt aDefaultTextGranularity = EDefaultTextGranularity);
	IMPORT_C static CPlainText* NewL(const CStreamStore& aStore,TStreamId aStreamId,
									 MTextFieldFactory* aFieldFactory = NULL,
									 TDocumentStorage aStorage = ESegmentedStorage);
	IMPORT_C virtual ~CPlainText();

	// primary persistence functions
	IMPORT_C virtual void StoreComponentsL(CStreamStore& aStore,CStoreMap& aMap) const;
	IMPORT_C virtual void RestoreComponentsL(const CStreamStore& aStore);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);

	// secondary persistence functions
	IMPORT_C void ExternalizePlainTextL(RWriteStream& aStream) const;
	IMPORT_C void InternalizePlainTextL(RReadStream& aStream);
	IMPORT_C void ExternalizePlainTextNoLengthCountL(RWriteStream& aStream) const; // Deprecated
	IMPORT_C void InternalizePlainTextL(RReadStream& aStream,TInt aLength); // Deprecated

	// import and export text
	IMPORT_C void ImportTextL(TInt aPos,RReadStream& aInput,TTextOrganisation aTextOrganisation,
							  TInt aMaxOutputChars = KMaxTInt,TInt aMaxInputChars = KMaxTInt,
							  TInt* aOutputChars = NULL,TInt* aInputChars = NULL);
	IMPORT_C void ExportTextL(TInt aPos,RWriteStream& aOutput,TTextOrganisation aTextOrganisation,
							  TInt aMaxOutputChars = KMaxTInt,TInt aMaxInputChars = KMaxTInt,
							  TInt aMaxLineLength = KMaxTInt,
							  TInt* aOutputChars = NULL,TInt* aInputChars = NULL) const;
	IMPORT_C virtual TInt ImportTextFileL(TInt aPos,const TDes& aFileName,TTextOrganisation aTextOrganisation);
	IMPORT_C virtual void ExportAsTextL(const TDes& aFileName,TTextOrganisation aTextOrganisation,
										TInt aMaxLineLength) const;

	// import and export text AND optionally translate from or to a non-Unicode encoding
	IMPORT_C void ImportTextL(TInt aPos,RReadStream& aInput,
							  const TImportExportParam& aParam,TImportExportResult& aResult);
	IMPORT_C void ExportTextL(TInt aPos,RWriteStream& aOutput,
							  const TImportExportParam& aParam,TImportExportResult& aResult) const;

	// read and write field data
	IMPORT_C void StoreFieldComponentsL(CStreamStore& aStore,CStoreMap& aMap) const;
	IMPORT_C void RestoreFieldComponentsL(const CStreamStore& aStore);
	IMPORT_C void ExternalizeFieldDataL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeFieldDataL(RReadStream& aStream);

	// modifier functions
	IMPORT_C virtual void Reset();
	IMPORT_C virtual void InsertL(TInt aPos,const TChar& aChar);
	IMPORT_C virtual void InsertL(TInt aPos,const TDesC& aBuf);
	IMPORT_C virtual TBool DeleteL(TInt aPos,TInt aLength);

	// interrogation functions
	IMPORT_C virtual TPtrC Read(TInt aStartPos) const;
	IMPORT_C virtual TPtrC Read(TInt aStartPos,TInt aLength) const;
	IMPORT_C virtual void Extract(TDes& aBuf,TInt aPos=0) const;
	IMPORT_C virtual void Extract(TDes& aBuf,TInt aPos,TInt aLength) const;

	// Flags for ExtractSelectively
	enum
		{
		EExtractAll = 0,	// extract all characters
		EExtractVisible = 1	// discard control characters and soft hyphens; change par and line separators to spaces
		};
	IMPORT_C void ExtractSelectively(TDes& aBuf,TInt aPos,TInt aLength,TUint aFlags);

	// copy and paste
	IMPORT_C virtual void CopyToStoreL(CStreamStore& aStore,CStreamDictionary& aDictionary,TInt aPos,TInt aLength) const;
	IMPORT_C virtual TInt PasteFromStoreL(const CStreamStore& aStore,const CStreamDictionary& aDictionary,TInt aPos);

	// utility functions
	IMPORT_C void SetPageTable(TPageTable* aPageTable);
	IMPORT_C TInt PageContainingPos(TInt aPos) const;
	IMPORT_C virtual TInt DocumentLength() const;
 	IMPORT_C virtual TInt WordCount() const;
	IMPORT_C virtual TInt ParagraphCount() const;
	IMPORT_C virtual TInt ToParagraphStart(TInt& aPos) const;
	IMPORT_C virtual TInt CharPosOfParagraph(TInt& aLength,TInt aParaOffset) const;
	IMPORT_C virtual TInt ParagraphNumberForPos(TInt& aPos) const;
	IMPORT_C virtual void GetWordInfo(TInt aCurrentPos,TInt& aStartPos,TInt& aLength,
						TBool aPictureIsDelimiter,TBool aPunctuationIsDelimiter) const;
	IMPORT_C virtual TInt ScanWords(TInt& aPos,TUint& aScanMask) const;
	IMPORT_C virtual TInt ScanParas(TInt& aPos,TUint& aScanMask) const;
	IMPORT_C virtual TEtextComponentInfo ComponentInfo() const;
	//
	// Field functions
	IMPORT_C void SetFieldFactory(MTextFieldFactory* aFactory);
	inline const MTextFieldFactory* FieldFactory() const;
	IMPORT_C CTextField* NewTextFieldL(TUid aFieldType) const;
	IMPORT_C void InsertFieldL(TInt aPos,CTextField* aField,TUid aFieldType); 
	IMPORT_C virtual void UpdateFieldL(TInt aPos); 
	IMPORT_C void UpdateAllFieldsL(); 
	IMPORT_C TInt FieldCount() const;
	IMPORT_C const CTextField* TextField(TInt aPos) const;
	IMPORT_C TBool FindFields(TInt aPos) const; 
	IMPORT_C TBool FindFields(TFindFieldInfo& aInfo,TInt aPos,TInt aRange=0) const;
	IMPORT_C TBool RemoveField(TInt aPos);  
	IMPORT_C TBool ConvertFieldToText(TInt aPos); 
	IMPORT_C void ConvertAllFieldsToText();

protected:
	IMPORT_C CPlainText();
	IMPORT_C void ConstructL(TDocumentStorage aStorage = ESegmentedStorage,
							 TInt aDefaultTextGranularity = EDefaultTextGranularity);
	IMPORT_C void ConstructL(const CStreamStore& aStore,TStreamId aStreamId,MTextFieldFactory* aFieldFactory,
							 TDocumentStorage aStorage = ESegmentedStorage);
	IMPORT_C void DoConstructL(TDocumentStorage aStorage,TInt aDefaultTextGranularity,
							   MTextFieldFactory* aFieldFactory = NULL);
	void DoExtract(TDes& aBuf,TInt aPos,TInt aLength,TUint aFlags = 0) const;
	IMPORT_C void PtInsertL(TInt aInsertPos,const TDesC& aBuf);
	IMPORT_C void DoPtInsertL(TInt aPos,const TDesC& aBuf);
	IMPORT_C TBool DoPtDelete(TInt aPos,TInt aLength);
	void InsertL(TInt aPos,const CPlainText* aText);
	TBool Delete(TInt aPos,TInt aLength);

	// streaming
	IMPORT_C void DoExternalizeFieldDataL(RWriteStream& aStream) const;
	IMPORT_C void DoInternalizeFieldDataL(RReadStream& aStream);
	IMPORT_C void DoExternalizePlainTextL(RWriteStream& aStream) const;
	IMPORT_C void DoInternalizePlainTextL(RReadStream& aStream);
	TStreamId DoCopyToStoreL(CStreamStore& aStore,CStreamDictionary& aDictionary,TInt aPos,TInt aLength) const;
	TInt DoPasteFromStoreL(const CStreamStore& aStore,TStreamId aStreamId,TInt aPos);
	void CopyComponentsL(CStreamStore& aStore,CStoreMap& aMap,TInt aPos,TInt aLength) const;
	void PasteComponentsL(const CStreamStore& aStore,TInt aPos);
	void CopyToStreamL(RWriteStream& aStream,TInt aPos,TInt aLength) const;

	// utility functions
	inline static void ConsumeAdornmentL(RReadStream& aStream);
	inline static TUid UidFromStreamL(RReadStream& aStream);
protected:
	enum
		{
		EImportBufSize = 512,
		EBiggestCharacterPaste=0x100000
		};

	enum TUnitOfText
		{
		EUnitIsWord,
		EUnitIsParagraph
		};

	struct SScanData
		{
		TInt pos;			// current character position
		TInt oldPos;		// old character position
		TText* buf;			// address of data (Unicode-aware)
		TInt currentSegLen; // number of characters left in segment
		TInt totalBufLen;	// number of unread characters
		TInt delta;			// specifies current scan direction
		TUint32 scanMask;	// bitmask containing the scan settings
		enum
			{
			EInsideUnit = 0x10000000,
			EStopEnd = 0x20000000,
			EStopBegin = 0x40000000,
			EIsDelimiter = 0x80000000
			};
		};

private:
	CPlainText(const CPlainText& aPlainTextDoc);
	CPlainText& operator=(const CPlainText& aPlainTextDoc);
	TInt PasteFromStreamL(RReadStream& aStream,TInt aPos);
	void InsertEodL();
	void InitScanControl(TInt& aPos,TUint& aScanMask,TUnitOfText aContext,SScanData& aScanData) const;
	void InitScanData(TInt aPos,SScanData& aScanData) const;
	void KillFieldSet();
	TInt CountUnits(TUnitOfText aContext) const;
	TInt ScanUnit(TInt& aPos,TUnitOfText aContext,SScanData& aScanData) const;
	TBool TestForDelimiter(TUnitOfText aContext,SScanData& aScanData) const;
	TBool GetChar(SScanData& aScanData,TChar& aChar) const;
	void UpdatePageTable(TInt aPos,TInt aLength);
	inline TBool FieldSetPresent() const;
	void CreateFieldSetL(TInt aDocumentLength);

	IMPORT_C void Reserved_1();			// from CEditableText
	IMPORT_C virtual void Reserved_2();	// new

	void* iReserved_1;

protected:
	CBufBase* iByteStore;				// handle to document storage class.
	TSwizzle<CTextFieldSet> iFieldSet;  // handle to field storage class
	TPageTable* iPageTable;				// may be NULL
	MTextFieldFactory* iFieldFactory;  // temporary handle to field factory during restoration

	__DECLARE_TEST;
	};


#include <txtetext.inl>

#endif // __TXTETEXT_H__
