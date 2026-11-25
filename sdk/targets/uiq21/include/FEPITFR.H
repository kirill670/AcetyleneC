// FEPITFR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// the class for inline-text format retrieval - in its own header file to prevent low-level components dependent on this class from gaining unnecessary (and undesirable) dependencies on high-level components

#if !defined(__FEPITFR_H__)
#define __FEPITFR_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

class TCharFormat;

/**
 *
 * Specifies the mixin protocol for finding out the formatting to apply
 * to inline text.
 *
 * This class should be overridden by front end processors which support
 * inline editing.An instance of a class which implements this protocol
 * should be passed to
 * <code>MCoeFepAwareTextEditor::StartFepInlineEditL()</code>.
 *
 * @since 6.0
 * @lib ""
 */
class MFepInlineTextFormatRetriever // to be overridden by inline-editing front-end processors
	{
public:
	/**
	 *
	 * Gets the character formatting to apply to the inline text.
	 *
	 * This function may be used to differentiate the formatting of the
	 * inline text from the surrounding text. The first parameter should be
	 * set to contain the character formatting values to
	 * use.<code>MCoeFepAwareTextEditor</code> provides a member function for
	 * finding out the character formatting of the surrounding text
	 * <code>GetFormatForFep()</code>. This can be called inside the
	 * implementation of this function to make any necessary adjustments to
	 * the format of the inline text to ensure that it is different from the
	 * surrounding text.The second and third parameters enable different
	 * parts of the inline text to have different formatting. All
	 * implementations of this function need to set the
	 * <code>aNumberOfCharactersWithSameFormat</code> parameter. If all of
	 * the inline text uses the same formatting then
	 * <code>aNumberOfCharactersWithSameFormat</code> should be set to the
	 * length of the inline text and the <code>aPositionOfCharacter</code>
	 * parameter can be ignored.When the inline text does not all use the
	 * same formatting, the second parameter should be set to the number of
	 * characters starting at <code>aPositionOfCharacter</code> which have
	 * the same formatting see the following example.ExampleIf the inline
	 * text is 7 characters long, the first 4 characters are in format A, the
	 * next 2 characters are in format B, and the remaining character is in
	 * format C.When the FEP framework (which knows that the inline text is 7
	 * characters long) needs to find out the format of the inline text, it
	 * calls <code>GetFormatOfFepInlineText()</code> passing zero into
	 * <code>aPositionOfCharacter</code> (to signify the start of the inline
	 * text). As the first 4 characters are all in format A, the function
	 * should set <code>aFormat</code> to A and it should set
	 * <code>aNumberOfCharactersWithSameFormat</code> to 4. As the FEP
	 * framework has only been told the format of the first 4 characters, it
	 * calls <code>GetFormatOfFepInlineText()</code> again passing 4 into
	 * <code>aPositionOfCharacter</code>. As the 2 characters starting at
	 * position 4 are all in format B, the function should set
	 * <code>aFormat</code> to B and it should set
	 * <code>aNumberOfCharactersWithSameFormat</code> to 2. The FEP framework
	 * still does not know the format of the 7th character so it calls
	 * <code>GetFormatOfFepInlineText()</code> a third time passing 6 into
	 * <code>aPositionOfCharacter</code>. As the character at position 6 is
	 * in format C, the function should set <code>aFormat</code> to C and it
	 * should set <code>aNumberOfCharactersWithSameFormat</code> to 1. The
	 * FEP framework now knows the format of all of the inline text.
	 *
	 * @param     "TCharFormat& aFormat"
	 *            On return, contains the formatting to apply to the
	 *            inline text (or to a portion of it).
	 * @param     "TInt& aNumberOfCharactersWithSameFormat"
	 *            On return, contains the number of characters in the
	 *            inline text (starting at
	 *            <code>aPositionOfCharacter</code>) which have the same
	 *            formatting.
	 * @param     "TInt aPositionOfCharacter"
	 *            Start position within the inline text.
	 */
	virtual void GetFormatOfFepInlineText(TCharFormat& aFormat, TInt& aNumberOfCharactersWithSameFormat, TInt aPositionOfCharacter) const=0;
private:
	IMPORT_C virtual void MFepInlineTextFormatRetriever_Reserved_1();
	IMPORT_C virtual void MFepInlineTextFormatRetriever_Reserved_2();
	};

#endif

