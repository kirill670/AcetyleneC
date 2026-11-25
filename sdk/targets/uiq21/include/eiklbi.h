// EIKLBI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKLBI_H__)
#define __EIKLBI_H__  

#include <e32base.h>
#include <gdi.h>
#include <lafpublc.h>
#include <w32std.h>

class CWindowGc;
class CListBoxData;
class TListItemProperties;
class TListFontBoundValues;
class CSpriteSet;

/**
 *
 * Draws individual list box items for a <code>CListBoxView</code>.
 *
 * The items may optionally be markable.Writing derived classes:This
 * class may be derived from to provide a different appearance for a list
 * box.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CListItemDrawer : public CBase
	{
public:
	IMPORT_C ~CListItemDrawer();
	IMPORT_C virtual void DrawItem(TInt aItemIndex, TPoint aItemRectPos, TBool aItemIsSelected, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed) const;
	IMPORT_C virtual void ClearRect(const TRect& aRect) const;
	IMPORT_C virtual TInt ItemWidthInPixels(TInt aItemIndex) const;
	IMPORT_C virtual TSize MinimumCellSize() const;
	IMPORT_C virtual void SetGc(CWindowGc* aGc);
	IMPORT_C CWindowGc* Gc() const;
	IMPORT_C virtual void SetMarkColumnWidth(TInt aWidthInPixels);
	IMPORT_C virtual void SetMarkGutter(TInt aGapInPixels);
	IMPORT_C TInt MarkColumn() const;
	IMPORT_C TInt MarkGutter() const;
	IMPORT_C void SetItemCellSize(const TSize& aSizeInPixels);
	IMPORT_C virtual void SetViewRect(const TRect& aRect);
	IMPORT_C void SetDrawMark(TBool aDrawMark);
	IMPORT_C virtual TRect MatcherCursorRect(const TDesC& aMatchableText, TInt aCharPos, TInt aItemCellYPos, TInt aCurrentItemIndex ) const;
	IMPORT_C virtual TInt MatcherCursorAscent( TInt aCurrentItemIndex ) const;
	IMPORT_C virtual void DrawItemMark(TBool aItemIsSelected, TBool aViewIsDimmed, const TPoint& aMarkPos) const;
	IMPORT_C void SetSymbolFont(const CFont* aFont);
	IMPORT_C void SetVerticalInterItemGap(TInt aGapInPixels);
	IMPORT_C void SetData(CListBoxData* aData);
	IMPORT_C CFont* Font(TInt aItemIndex) const;
	IMPORT_C virtual TListItemProperties Properties(TInt aItemIndex) const;
	IMPORT_C void DrawFrame(CWindowGc& aGc,const TRect& aRect,TInt aFlags) const;
	IMPORT_C void TryCreateSpriteSetL(RWindowTreeNode& aWindowForSprite);
	IMPORT_C void TranslateSpritePosition(const TPoint& aPos, TBool aIsVisible);
public: // for test code only - DO NOT USE!
	IMPORT_C void SetSpriteSet(CSpriteSet* aSpriteSet);
public:
	/**
	 * Provides list box attributes for handling multiple selections.
	 *
	 * These flags can be set using the
	 * <code>CListItemDrawer::SetFlags</code> function.
	 */
	enum TFlags
		{
		/** If set, specifies the inclusion of a gap into which a tick mark can be
		drawn if the item is selected. This is used in the following
		<code>CListItemDrawer</code> class functions:<code>DrawItem()</code><-
		code>DrawItemMark()</code><code>SetDrawMark()</code> */
		EDrawMarkSelection			= SLafListBox::EItemDrawMarkSelection,

		/** If set, draws a highlight over a selected list item. This is used in
		the <code>CTextListItemDrawer::DoDrawItemText()</code> function. */
		EPaintedSelection			= SLafListBox::EItemPaintedSelection,
		EDrawOnlyActiveSelection	= SLafListBox::EItemDrawOnlyActiveSelection,	/** This flag is not supported. */
		EDataWidthClippedToViewRect = SLafListBox::EDataWidthClippedToViewRect
		};
public:
	/**
	 * Provides attributes for list items.
	 */
    enum TListItemAttribute
        {
		ECurrent    = SLafListBox::ECurrent,		/** Highlight for current text. */

		/** Highlight for text when the listbox view is emphasized.This is used in
		the following <code>CListBoxView</code> class functions:
		<code>DrawItem()</code>, <code>DrawMatcherCursor()</code>,
		<code>SetEmphasized()</code>.	 */
		EEmphasized = SLafListBox::EEmphasized,

		/** Highlight for text that is selected. This is used in the following
		functions:
		<code>CColumnListBoxItemDrawer</code>::<code>DrawItemText()</code>,
		<code>CHierarchicalListItemDrawer::DrawActualItem()</code>,
		<code>CDirContentsListItemDrawer::DrawActualItem()</code>. */
		ESelected   = SLafListBox::ESelected,
		// This last attribute is used to control that one can use only
		// valid attributes above. So do not use it at all.
		EMask		= SLafListBox::EMask			/** Sum of all the above attributes. */
        };
public:
	inline void SetTextColor(TRgb aColor);
	inline void SetBackColor(TRgb aColor);
	inline void SetHighlightedTextColor(TRgb aColor);
	inline void SetHighlightedBackColor(TRgb aColor);
	inline void SetDimmedTextColor(TRgb aColor);
	inline void SetDimmedBackColor(TRgb aColor);
	inline TRgb TextColor() const;
	inline TRgb BackColor() const;
	inline TRgb HighlightedTextColor() const;
	inline TRgb HighlightedBackColor() const;
	inline TRgb DimmedTextColor() const;
	inline TRgb DimmedBackColor() const;
	inline TInt Flags() const;
	IMPORT_C void SetFlags(TInt aFlags);
	IMPORT_C void ClearFlags(TInt aFlags);
	IMPORT_C CSpriteSet* SpriteSet() const;
	inline TRgb MarkColor() const;
	// functions for limiting the width of items (using item truncation)
	IMPORT_C void SetDataWidthClippedToViewRect(TBool aIsClipped);
	IMPORT_C TBool DataWidthClippedToViewRect() const;
protected:
	IMPORT_C CListItemDrawer();
	/**
	 * Draws item text.
	 *
	 * This function is called by <code>CListItemDrawer::DrawItem()</code>
	 * with appropriate arguments. Its purpose is to draw the actual item (
	 * everything other than the item mark) into the graphics context.
	 *
	 * @param     "TInt aItemIndex"
	 *            Which item to draw.
	 * @param     "const TRect& aActualItemRect"
	 *            Where the item should be drawn.
	 * @param     "TBool aItemIsCurrent"
	 *            Whether the item is current.
	 * @param     "TBool aViewIsEmphasized"
	 *            Whether the list box view is emphasised.
	 * @param     "TBool aViewIsDimmed"
	 *            Whether the list box view is dimmed.
	 * @param     "TBool aItemIsSelected"
	 *            Whether the list box item is selected.
	 */
    virtual void DrawActualItem(TInt aItemIndex,const TRect& aActualItemRect,TBool aItemIsCurrent,
									TBool aViewIsEmphasized,TBool aViewIsDimmed,TBool aItemIsSelected) const =0;
	IMPORT_C virtual void ResetGc() const;
	IMPORT_C TInt VerticalInterItemGap() const;
    IMPORT_C void SetupGc(TInt aItemIndex) const;
	IMPORT_C TInt BaseLineOffset(const CFont& aFont) const;
private:
	IMPORT_C virtual TAny* Reserved_1();
    inline TInt& VerticalInterItemGap();
    inline const CFont* SymbolFont() const;
    inline const CFont*& SymbolFont();
protected:
	TSize iItemCellSize;
	TInt iMarkGutter;
	TInt iMarkColumnWidth;
	TRect iViewRect;
	TBool iDrawMark;
	CWindowGc* iGc;
	TRgb iTextColor;
	TRgb iBackColor;
	TRgb iHighlightedTextColor;
	TRgb iHighlightedBackColor;
	TRgb iDimmedTextColor;
	TRgb iDimmedBackColor;
	TRgb iMarkColor;
    CListBoxData* iData;
private:
	const CFont* iSymbolFont;
	TInt iVerticalInterItemGap;
	CSpriteSet* iSpriteSet;
	TUint iFlags;
	};


class MTextListBoxModel;

/**
 *
 * Item drawer which can handle text.
 *
 * Used by <code>CListBoxView</code> to draw individual list box items
 * for a <code>CEikTextListBox</code>.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CTextListItemDrawer : public CListItemDrawer
	{
public:
	IMPORT_C CTextListItemDrawer();
	IMPORT_C ~CTextListItemDrawer();
	IMPORT_C CTextListItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont);
	IMPORT_C void ConstructL(const CFont* aFont);
	IMPORT_C virtual void DrawActualItem(TInt aItemIndex, const TRect& aActualItemRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed,TBool aItemIsSelected) const;
	IMPORT_C virtual TInt ItemWidthInPixels(TInt aItemIndex) const;
	IMPORT_C virtual TSize MinimumCellSize() const;
	IMPORT_C virtual void SetGc(CWindowGc* aGc);
	IMPORT_C void SetCellWidthInChars(TInt aNumOfCharsToDisplayInCell);
    IMPORT_C virtual TRect MatcherCursorRect(const TDesC& aMatchableText, TInt aCharPos, TInt aItemCellYPos, TInt aCurrentItemIndex ) const;
    IMPORT_C virtual TInt MatcherCursorAscent( TInt aCurrentItemIndex ) const;
	IMPORT_C void SetFont(const CFont* aFont);
	IMPORT_C void SetSearchStringL(const TDesC* aSearchString);
	IMPORT_C const CFont* Font(TInt aIndex) const;
protected:
    IMPORT_C virtual void DoDrawItemText(const TDesC& aDes, const TRect& aItemTextRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aItemIsSelected, TInt aItemIndex) const;
    IMPORT_C virtual void DrawItemText(TInt aItemIndex, const TRect& aItemTextRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aItemIsSelected) const;
	IMPORT_C virtual void ResetGc() const;
private:
	IMPORT_C virtual TAny* Reserved_1();
protected:
	MTextListBoxModel* iModel;
	const CFont* iFont;
private:
	TInt iNumOfCharsInCell;
	};

/**
 *
 * Colour and style properties which can be applied when drawing the
 * contents of list box items.
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class TListItemProperties
    {
public:
	IMPORT_C TListItemProperties();
public:
    inline void SetBold(TBool aBold);
    inline TBool IsBold() const;
    inline void SetItalics(TBool aItalics);
    inline TBool IsItalics() const;
    inline void SetUnderlined(TBool aUnderlined);
    inline TBool IsUnderlined() const;
    inline void SetDimmed(TBool aDimmed);
    inline TBool IsDimmed() const;
    inline void SetColor(TRgb aColor);
    inline TRgb Color() const;
private:
    TUint iFlags;
    TRgb iColor;
private:
    enum
        {
        ELbxItemBold		= 0x0001,
        ELbxItemItalics		= 0x0002,
        ELbxItemUnderlined	= 0x0004,
		ELbxItemDimmed		= 0x0008	
        };
    };

//
// Inlines
//

/**
 * Sets the colour used to draw non-highlighted text.
 *
 * @param     "TRgb aColor"
 *            The text colour.
 */
inline void CListItemDrawer::SetTextColor(TRgb aColor)
	{iTextColor=aColor;}

/**
 * Sets the colour used to draw the background for non-highlighted items.
 *
 * @param     "TRgb aColor"
 *            The background colour.
 */
inline void CListItemDrawer::SetBackColor(TRgb aColor)
	{iBackColor=aColor;}

/**
 * Sets the colour used to draw highlighted text.
 *
 * @param     "TRgb aColor"
 *            The highlighted text colour.
 */
inline void CListItemDrawer::SetHighlightedTextColor(TRgb aColor)
	{iHighlightedTextColor=aColor;}

/**
 * Sets the colour used to draw the background for highlighted items.
 *
 * @param     "TRgb aColor"
 *            The highlighted background colour.
 */
inline void CListItemDrawer::SetHighlightedBackColor(TRgb aColor)
	{iHighlightedBackColor=aColor;}

/**
 * Sets the colour used to draw dimmed text.
 *
 * @param     "TRgb aColor"
 *            The dimmed text colour.
 */
inline void CListItemDrawer::SetDimmedTextColor(TRgb aColor)
	{iDimmedTextColor=aColor;}

/**
 * Sets the colour used to draw the background for dimmed items.
 *
 * @param     "TRgb aColor"
 *            The background colour for dimmed items.
 */
inline void CListItemDrawer::SetDimmedBackColor(TRgb aColor)
	{iDimmedBackColor=aColor;}

/**
 * Gets the colour used to draw non-highlighted text.
 *
 * @returns   "TRgb"
 *            The text colour.
 */
inline TRgb CListItemDrawer::TextColor() const
	{return iTextColor;}

/**
 * Gets the colour used to draw the background for non-highlighted items.
 *
 * @returns   "TRgb"
 *            The background colour.
 */
inline TRgb CListItemDrawer::BackColor() const
	{return iBackColor;}

/**
 * Gets the colour used to draw highlighted text.
 *
 * @returns   "TRgb"
 *            The highlighted text colour.
 */
inline TRgb CListItemDrawer::HighlightedTextColor() const
	{return iHighlightedTextColor;}

/**
 * Gets the colour used to draw the background for highlighted items.
 *
 * @returns   "TRgb"
 *            The highlighted background colour.
 */
inline TRgb CListItemDrawer::HighlightedBackColor() const
	{return iHighlightedBackColor;}

/**
 * Gets the colour used to draw dimmed text.
 *
 * @returns   "TRgb"
 *            The dimmed text colour.
 */
inline TRgb CListItemDrawer::DimmedTextColor() const
	{return iDimmedTextColor;}

/**
 * Gets the colour used to draw the background for dimmed items.
 *
 * @returns   "TRgb"
 *            The background colour for dimmed items.
 */
inline TRgb CListItemDrawer::DimmedBackColor() const
	{return iDimmedBackColor;}

/**
 * Gets the colour used to draw tick marks.
 * A tick mark usually indicates that an item is selected.
 *
 * @returns   "TRgb"
 *            The tick mark colour.
 */
inline TRgb CListItemDrawer::MarkColor() const
	{return iMarkColor;}

/**
 * Gets the item drawer flags.
 *
 * @returns   "TInt"
 *            The item drawer flags.
 */
inline TInt CListItemDrawer::Flags() const
	{return iFlags;}

/**
 * Tests whether the list item is italicised.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the list item is drawn in
 *            italics. <code>EFalse</code> otherwise.
 */
inline TBool TListItemProperties::IsItalics() const
	{return iFlags&ELbxItemItalics;}

/**
 * Tests whether the list item is drawn bold.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the list item is drawn bold.
 *            <code>EFalse</code> otherwise.
 */
inline TBool TListItemProperties::IsBold() const
	{return iFlags&ELbxItemBold;}

/**
 * Test whether the list item is drawn with an underline.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the list item is drawn with an
 *            underline. <code>EFalse</code> otherwise.
 */
inline TBool TListItemProperties::IsUnderlined() const
	{return iFlags&ELbxItemUnderlined;}

/**
 * Tests list item dim state.
 *
 * An item is usually drawn dimmed to indicate that it cannot accept user
 * input.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the list item is dimmed.
 *            <code>EFalse</code> otherwise.
 */
inline TBool TListItemProperties::IsDimmed() const
	{return iFlags&ELbxItemDimmed;}

/**
 * Sets the list items colour.
 *
 * @param     "TRgb aColor"
 *            The list items colour.
 */
inline void TListItemProperties::SetColor(TRgb aColor)
	{iColor=aColor;}

/**
 * Gets the list items colour.
 *
 * @returns   "TRgb"
 *            The list items colour.
 */
inline TRgb TListItemProperties::Color() const
    {return iColor;}

/**
 * Sets whether the list item is drawn bold or not bold.
 *
 * @param     "TBool aBold"
 *            <code>ETrue</code> to draw the list item bold.
 *            <code>EFalse</code> otherwise.
 */
inline void TListItemProperties::SetBold(TBool aBold)
    {
    if (aBold) 
		iFlags|=ELbxItemBold;
	else
		iFlags&=(~ELbxItemBold);
    }

/**
 * Sets whether or not the list item is drawn in italics.
 *
 * @param     "TBool aItalics"
 *            <code>ETrue</code> to draw the list item in italics.
 *            <code>EFalse</code> otherwise.
 */
inline void TListItemProperties::SetItalics(TBool aItalics)
    {
    if (aItalics)
		iFlags|=ELbxItemItalics;
	else
		iFlags&=(~ELbxItemItalics);
    }

/**
 * Sets whether or not the list item is drawn with an underline.
 *
 * @param     "TBool aUnderlined"
 *            <code>ETrue</code> to draw the list item with an
 *            underline. <code>EFalse</code> otherwise.
 */
inline void TListItemProperties::SetUnderlined(TBool aUnderlined)
    {
	if (aUnderlined)
		iFlags|=ELbxItemUnderlined;
	else
		iFlags&=(~ELbxItemUnderlined);
    }

/**
 * Sets list item dim state.
 *
 * An item is usually drawn dimmed to indicate that it cannot accept user
 * input.
 *
 * @param     "TBool aDimmed"
 *            <code>ETrue</code> to draw the list item dimmed.
 *            <code>EFalse</code> otherwise.
 */
inline void TListItemProperties::SetDimmed(TBool aDimmed)
    {
    if (aDimmed)
		iFlags|=ELbxItemDimmed;
	else
		iFlags&=(~ELbxItemDimmed);
    }

#endif
