// TXTLAYDC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTLAYDC_H__
#define __TXTLAYDC_H__

#include <e32std.h>

class CParaFormat;
class TCharFormat;
class CPicture;

/**
 *
 * This class specifies the mixin protocol for providing the information
 * needed by the text layout engine to lay out a text object.
 *
 * It is inherited by classes which implement this protocol. Examples of
 * such classes are <code>CRichText</code> and
 * <code>CGlobalText</code>.At the heart of the interface are two
 * interrogation functions; one gives the paragraph formatting for a
 * document position, and the other gives a pointer descriptor to a
 * series of contiguous characters with identical character formatting,
 * and their character formatting. This information is sufficient for the
 * layout engine to find the formatting and content of an entire
 * document.The constructor for the layout engine
 * (<code>CTextLayout</code>) is prototyped as:By viewing the text object
 * purely in terms of the <code>MLayDoc</code> interface, the layout
 * engine is insulated from any editable text implementation issues.
 *
 * @since 5.0
 * @lib ""
 */

class MLayDoc
	{
	// Defines interface for extracting content & format information from text source.
	// Designed to be 'mixed-in' with other classes.
	//
public:
	
	/**
	 *
	 * Used as a parameter to the <code>PictureHandleL()</code> function to
	 * control whether picture data should be loaded into memory or not.
	 * @since 
	 */

	enum TForcePictureLoad 
		{
		/** Do not load the picture data into memory. */
		EForceLoadFalse,
		/** Load the picture data into memory. */
		EForceLoadTrue
		};
public:
	
	/**
	 *
	 * Gets the the number of characters in the document.
	 *
	 * @returns   " TInt "
	 *            The number of characters contained in the document.
	 */

	virtual TInt LdDocumentLength()const=0;  // Does not include final document terminator

	/**
	 *
	 * Gets the document position of the start of the paragraph containing a
	 * specified position.
	 *
	 * @param     " TInt& aCurrentPos "
	 *            A valid document position. On return contains the
	 *            document position of the first character in the
	 *            paragraph.
	 * @returns   " TInt "
	 *            The number of characters skipped in scanning to the
	 *            start of the paragraph.
	 */

	virtual TInt LdToParagraphStart(TInt& aCurrentPos)const=0;
	
	/**
	 *
	 * Gets the effective paragraph formatting which applies to the paragraph
	 * which contains a specified document position.
	 *
	 * On return, <code>aFormat</code> is filled with values for all
	 * paragraph format attributes.
	 *
	 * @param     " CParaFormat* aFormat "
	 *            On return, filled with the paragraph's effective
	 *            paragraph formatting.
	 * @param     " TInt aPos "
	 *            Any document position within the paragraph of
	 *            interest.
	 */

	virtual void GetParagraphFormatL(CParaFormat* aFormat,TInt aPos)const=0;
	
	/**
	 *
	 * Gets a constant pointer descriptor to a portion of the text object
	 * with constant character formatting.
	 *
	 * The view starts at the document position specified, and ends at: the
	 * last character which shares the same character formatting (rich text
	 * only), orthe end of the document, orthe end of the segment, if
	 * segmented storage is being usedwhichever occurs first. Also fills a
	 * character format object with the character formatting of the range of
	 * characters.
	 *
	 * @param     " TPtrC& aView "
	 *            On return, a constant pointer to a portion of the
	 *            text.
	 * @param     " TCharFormat& aFormat "
	 *            On return, contains the character formatting of the
	 *            text.
	 * @param     " TInt aStartPos "
	 *            The start position for the view. Must be a valid
	 *            document position, or a panic occurs.
	 */

	virtual void GetChars(TPtrC& aView,TCharFormat& aFormat,TInt aStartPos)const=0;	
	// Return a block of (>=1) characters from aStartPos and the attributes that they have.
	//
	
	/**
	 *
	 * Gets the size of a picture located at a specified document position.
	 *
	 * NoteThe global text implementation of this function always
	 * returns<code>KErrNotFound</code> because global text does not support
	 * pictures.
	 *
	 * @param     " TSize& aSize "
	 *            On return, contains the size of the picture located
	 *            at<code>aPos</code>.
	 * @param     " TInt aPos "
	 *            Document position of the picture.
	 * @returns   " TInt "
	 *            <code>KErrNotFound</code> if there is no picture at
	 *            the specified document position, <code>KErrNone</code>
	 *            if there is.
	 */

	virtual TInt GetPictureSizeInTwips(TSize& aSize, TInt aPos)const=0;
	
	/**
	 *
	 * Gets a pointer to the picture located at a specified document
	 * position, if one exists.
	 *
	 * If the picture is not in memory, the function loads it (if the second
	 * argument has a value of <code>EForceLoadTrue</code>).NoteThe global
	 * text implementation of this function always returns NULL because
	 * global text does not support pictures.
	 *
	 * @param     " TInt aPos "
	 *            Document position of the picture character.
	 * @param     " TForcePictureLoad aForceLoad "
	 *            If the picture is not loaded into memory,
	 *            <code>EForceLoadTrue</code> loads it using the picture
	 *            factory; <code>EForceLoadFalse</code> does not, and in
	 *            this case, the function returns NULL.
	 * @returns   " CPicture* "
	 *            A pointer to the picture located at <code>aPos</code>.
	 *            NULL if <code>aPos</code> does not specify a picture
	 *            character, or if there is a picture at
	 *            <code>aPos</code> which is not in memory, and the
	 *            second argument is <code>EForceLoadFalse</code>.
	 */

	virtual CPicture* PictureHandleL(TInt aPos,TForcePictureLoad aForceLoad=EForceLoadTrue)const=0;
	// returns the handle of the picture at aPos, or NULL if there is none.
	// By default, (EForceLoadTrue), if the picture is not in memory it is loaded.  This can be overriden.
	//
	
	/**
	 *
	 * Tests whether a page break occurs within a range of characters.
	 *
	 * A page table should have been set up first:
	 * see<code>CPlainText::SetPageTable()</code>.
	 *
	 * @param     " TInt aPos "
	 *            The document position from which to begin searching
	 *            for a page break.
	 * @param     " TInt aLength "
	 *            The number of characters to search for a page break,
	 *            beginning at<code>aPos</code>. The default is zero.
	 * @returns   " TBool "
	 *            True if a page break occurs within the specified
	 *            range, otherwise false.
	 */

	virtual TBool EnquirePageBreak(TInt aPos,TInt aLength=0)const=0;

	
	/**
	 *
	 * This function should be implemented by text objects which support
	 * paragraph labels.
	 *
	 * Each paragraph may have at most one label. By default, the functions
	 * provided by <code>MLayDoc</code> apply to the main body of text. This
	 * function is provided to change this so that the <code>MLayDoc</code>
	 * object is an individual paragraph label, (each of which is treated as
	 * a separate document). Paragraph labelling has not been implemented by
	 * global or rich text.This function should select the paragraph label
	 * associated with the paragraph containing document position
	 * <code>aPos</code> (<code>aPos</code> is a document position in the
	 * main document).
	 *
	 * @param     " TInt aPos "
	 *            A document position within a paragraph. This
	 *            paragraph's label should be set as the main
	 *            <code>MLayDoc</code> document.
	 * @returns   " TBool "
	 *            Should return <code>EFalse</code> if the paragraph has
	 *            no label, in which case the function has no effect,
	 *            <code>ETrue</code> otherwise.
	 */

	virtual TBool SelectParagraphLabel(TInt aPos)=0;

	/**
	 *
	 * Cancels a paragraph label selection made by a call
	 * to<code>SelectParagraphLabel()</code> so that the main document
	 * reverts back to the main body of text.
	 *
	 */
	virtual void CancelSelectLabel()=0;
	// Cancels any paragraph label select. Harmless if not in label mode.
	//

	IMPORT_C virtual void MLayDoc_Reserved_1();
	};

#endif

