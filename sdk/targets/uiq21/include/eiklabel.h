// EIKLABEL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKLABEL_H__)
#define __EIKLABEL_H__

#include <eikalign.h>
#include <coeccntx.h>

class CEikLabelExtra;

/**
 *
 * The CEikLabel class is able to display one or more lines of text and it provides functions to set
 * the text and font, which wil be used when displaying the label control.
 * This control is usually used as compound control by buttons or by specific type of labels
 * such as CEikFileNameLabel, etc.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikLabel : public CEikAlignedControl, public MCoeControlContext
	{
public:  // new functions
	IMPORT_C ~CEikLabel();
	IMPORT_C CEikLabel();
public:  // from CCoeControl
	IMPORT_C TSize MinimumSize();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C void HandleResourceChange(TInt aType);			// not available before Release 005u
protected: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
protected: // from MCoeControlContext
	IMPORT_C void PrepareContext(CWindowGc& aGc) const; // Do not use
public:  
	/**
	 * Determines text emphasis.
	 */
	enum TTextEmphasis
		{
		ENoEmphasis		 =0x00,		/** Text is drawn with no emphasis. */
		EPartialEmphasis =0x10,		/** Text is drawn partially emphasised. */
		EFullEmphasis	 =0x20		/** Text is drawn with full emphasis. */
		};
public:  // new functions
	IMPORT_C void SetTextL(const TDesC& aText);
	inline const TDesC* Text() const;
	IMPORT_C void SetBufferReserveLengthL(TInt aLength);
	IMPORT_C void SetFont(const CFont* aFont);
	inline const CFont* Font() const;
	IMPORT_C void SetEmphasis(TTextEmphasis aEmphasis);
	IMPORT_C void SetPixelGapBetweenLines(TInt aGap);
	IMPORT_C TInt PixelGapBetweenLines() const;
	inline TBool IsUnderlined() const;
	IMPORT_C void SetUnderlining(TBool aUnderLining);
	inline TBool IsStrikethrough() const;
	IMPORT_C void SetStrikethrough(TBool aStrikethrough);
	IMPORT_C TSize CalcMinimumSize(TPtrC& aText) const;
	inline TUint8 NumberOfLines();
	IMPORT_C void SetAutoWrapping(TBool aAutoWrapping);
	inline TBool IsAutoWrapping() const;
	IMPORT_C void SetWrappingWidthL(TInt aWidth);
	IMPORT_C void SetNumberOfVisibleLines(TInt aMaxNumberOfLines);
public:
	TInt BufferReserveLength() const;
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	IMPORT_C void SizeChanged();
private:
	IMPORT_C void Reserved_2();
private: // new functions
	TInt HeightInPixels() const;
	TInt WidthInPixels(TPtrC& aText) const;
	void SetupGcForEmphasis(CGraphicsContext& aGc) const;
	void CheckCreateExtensionL();
	TInt WrapText(TInt aMaximumWidth);
	void RevertAnyWrappingChanges();
	void TryWrappingText();
protected:
	/**
	 * Determines whether text is drawn with underlining and strike-through.
	 */
	enum TLabelFlags
		{
		EUnderlining				= 0x02,		/** Text is drawn with underlining. */
		EStrikethrough				= 0x04,		/** Text is drawn with strike-through. */
		ETextBufferReserveLength	= 0x08,
		// cannot use 10 and 20 since they are used by TTextEmphasis
		EAutoWrapping				= 0x40
		};
	HBufC* iText;
	const CFont* iFont;
	TUint8 iNumberOfLines;
	TUint8 iLabFlags;
	TInt iGapBetweenLines;
private:
	CEikLabelExtra* iExtra;
	};


/**
 *
 * Gets the labels text.
 *
 * @returns   "TDesC*"
 *            The labels text.
 */
inline const TDesC* CEikLabel::Text() const
	{ return(iText); }

/**
 *
 * Gets the labels font.
 *
 * @returns   "CFont*"
 *            The labels font.
 */
inline const CFont* CEikLabel::Font() const
	{ return(iFont); }

/**
 *
 * Tests whether the label is underlined.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the label is set as underlined,
 *            <code>EFalse</code> if the label is not set as
 *            underlined.
 */
inline TBool CEikLabel::IsUnderlined() const
    {return iLabFlags&EUnderlining;}

/**
 *
 * Tests label strike-through.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the label is set to be drawn
 *            with a line through it, <code>EFalse</code> if the
 *            label is not set to be drawn with a line through it.
 */
inline TBool CEikLabel::IsStrikethrough() const
    {return iLabFlags&EStrikethrough;}

/**
 *
 * Gets the number of lines of text in the label.
 *
 * @returns   "TUint8"
 *            The number of lines of text.
 */
inline TUint8 CEikLabel::NumberOfLines()
	{return iNumberOfLines;}	
/**
 * Returns ETrue if the label has the auto wrapping flag set.
 *
 * @since App-Framework_6.2
 */
inline TBool CEikLabel::IsAutoWrapping() const
    {return iLabFlags&EAutoWrapping;}

#endif
