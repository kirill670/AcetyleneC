// EIKCLBD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKCLBD_H__)
#define __EIKCLBD_H__

#include <e32base.h>
#include <gdi.h>

#include <eiklbd.h>
#include <avkon.hrh>

class CWindowGc;
class CGulIcon;
class CColumnListBoxDataExtension;
class MAknsControlContext;
class CCoeControl;
class TAknsItemID;
class CAknsListBoxBackgroundControlContext;
class CAknLayoutData;

/**
 * The CColumnListBoxData class handles the data required to draw a column list box.
 */
class CColumnListBoxData : public CListBoxData
    {
public:
    class TColors
        {
    public:
        IMPORT_C TColors();
    public:
        TRgb iText;
        TRgb iBack;
        TRgb iHighlightedText;
        TRgb iHighlightedBack;
        };
public:
    IMPORT_C static CColumnListBoxData* NewL();
    IMPORT_C ~CColumnListBoxData();
public:
    IMPORT_C TInt LastColumn() const;
    //
    IMPORT_C TInt ColumnWidthPixel(TInt aColumn) const;
    IMPORT_C void SetColumnWidthPixelL(TInt aColumn,TInt aWidth);
    //
    IMPORT_C TInt ColumnHorizontalGap(TInt aColumn) const;
    IMPORT_C void SetColumnHorizontalGapL(TInt aColumn,TInt aGap);
    //
    IMPORT_C TInt ColumnBaselinePos(TInt aColumn) const;
    IMPORT_C void SetColumnBaselinePosL(TInt aColumn,TInt aPos);
    //
    IMPORT_C TMargins ColumnMargins(TInt aColumn) const;
    IMPORT_C void SetColumnMarginsL(TInt aColumn,TMargins aMargins);
    //
    IMPORT_C const CFont* ColumnFont(TInt aColumn) const;
    IMPORT_C void SetColumnFontL(TInt aColumn,const CFont* aFont);
    //
    IMPORT_C CGraphicsContext::TTextAlign ColumnAlignment(TInt aColumn) const;
    IMPORT_C void SetColumnAlignmentL(TInt aColumn,CGraphicsContext::TTextAlign aAlign);
    //
    IMPORT_C CGraphicsContext::TPenStyle ColumnSeparatorStyle(TInt aColumn) const;
    IMPORT_C void SetColumnSeparatorStyleL(TInt aColumn, CGraphicsContext::TPenStyle aStyle);
    //
    IMPORT_C TBool ColumnIsOptional(TInt aColumn) const;
    IMPORT_C void SetOptionalColumnL(TInt aColumn,TBool aIsOptional);
    //
    IMPORT_C TBool ColumnIsGraphics(TInt aColumn) const;
    IMPORT_C void SetGraphicsColumnL(TInt aColumn,TBool aIsGraphics);
    //
    IMPORT_C TBool ColumnIsNumber(TInt aColumn) const;
    IMPORT_C void SetNumberColumnL(TInt aColumn,TBool aIsNumber);
    //
    IMPORT_C CArrayPtr<CGulIcon>* IconArray() const;
    IMPORT_C void SetIconArray(CArrayPtr<CGulIcon>* aArray);
    //
    IMPORT_C TInt ColumnTextClipGap(TInt aSubCellIndex) const;
    IMPORT_C void SetColumnTextClipGapL(TInt aSubCellIndex, TInt aSize);
    //
    IMPORT_C CFont* Font(const TListItemProperties& aItemProperties, TInt aColumn) const;
    IMPORT_C TBool MakeColumnRect( TInt aColumn, TRect& aRect );
    IMPORT_C virtual void Draw(const TListItemProperties& aItemProperties, CWindowGc& aGc,const TDesC* aText,const TRect& aRect,TBool aHighlight,const TColors& aColors) const;

   	/**
	* Sets position of listbox line
	*/
	IMPORT_C void SetSeparatorLinePosition(TAknSeparatorLinePosition aPosition);

	/**
	* Gives out separator line position
	*/
	IMPORT_C TAknSeparatorLinePosition SeparatorLinePosition() const;

	/**
	 * Gives out layout data for separator line drawing
	 */
	IMPORT_C CAknLayoutData *LayoutData() const;

private:
    struct SColumn
        {
        TInt iColumn; // Must be first entry
        TInt iWidth;
        TMargins iMargins;
        TInt iVerticalCap;
        const CFont* iBaseFont;
        TInt iActualFontIndex;
        TBool iGraphics;
    TBool iOptional;
    TInt iBaseline;
        CGraphicsContext::TTextAlign iAlign;
    CGraphicsContext::TPenStyle iSeparator;
    TInt iTextClipGap;
    TBool iNumberColumn;
    // the next are for storing x-coordinates of a column for the drawing algorithm.
    __MUTABLE TInt iX;
    __MUTABLE TInt iEndX;
        };
protected:
    IMPORT_C CColumnListBoxData();
    IMPORT_C void ConstructLD();
private:
    
    IMPORT_C TInt ColumnX(TInt aColumn) const;
    IMPORT_C void SetColumnXL(TInt aColumn,TInt aX) const; // note, const! (do not affect external state)
    //
    IMPORT_C TInt ColumnEndX(TInt aColumn) const;
    IMPORT_C void SetColumnEndXL(TInt aColumn,TInt aEndX) const; // note, Const!

    void AddColumnL(TInt aColumn);
    SColumn& At(TInt aArrayIndex);
    const SColumn& At(TInt aArrayIndex) const;
    TInt FindColumnIndex(TInt& aArrayIndex,TInt aColumn) const;
    void FindColumnIndexOrAddL(TInt& aArrayIndex,TInt aColumn);
    TInt AddActualFontL(const CFont* aBaseFont);
public:
    IMPORT_C CCoeControl *Control() const;
    IMPORT_C void SetControl(CCoeControl *aControl);
    IMPORT_C MAknsControlContext* SkinBackgroundContext() const;
    void SetSkinBackgroundContext(CAknsListBoxBackgroundControlContext *aContext); // takes ownership
    IMPORT_C void SetSkinStyle(const TAknsItemID *aId, const TRect &aTileRect);
    IMPORT_C void SetListEndSkinStyle(const TAknsItemID *aId, const TRect &aRect);
    IMPORT_C void SetSkinHighlightFrame(const TAknsItemID *aFrameId, const TAknsItemID *aFrameCenterId);
    IMPORT_C void SetSkinEnabledL(TBool aEnabled);
    void CreatePictographInterfaceL();
    void CreateMarqueeControlL();
    void ResetMarquee();
    TInt CurrentMarqueeItemIndex();
    void SetCurrentMarqueeItemIndex(TInt aIndex);
    // Enables or disables marquee.
    IMPORT_C void EnableMarqueeL(TBool aEnable); // ETrue = On, EFalse = Off
    /**
    * SetSubCellFontForRowL() sets the font attached to the cell for each row separately.
    * @since 2.6
    * @param aRow index number of the row
    * @param aColumn index number of the column
    * @param aFont font to be used
    * @return None
    */
    IMPORT_C void SetColumnFontForRowL(TInt aRow, TInt aColumn, const CFont* aFont);

    /**
    * RowAndSubCellFont queries font attached to the row and cell.
    * @since 2.6
    * @param aRow index number of the row
    * @param aColumn index number of the column
    * @return font handle
    */
    IMPORT_C const CFont* RowAndColumnFont(TInt aRow,TInt aColumn) const;

    /**
    * Sets the current list item index
    * @since 2.6
    * @param aIndex
    */
    void SetCurrentItemIndex(TInt aIndex);

    /**
    * Sets the subcell icon size
    * @since 2.8
    * @param aIndex
    * @param aSize
    */
    IMPORT_C void SetSubCellIconSize(TInt aIndex, TSize aSize);

    TSize GetSubCellIconSize(TInt aIndex);

protected:    
    /**
    * Wraps the text drawing functinality with & without marquee into one function,
    * so that inherited classes can modify their own drawing behaviour more easily.
    * @since 2.8
    * @param aText The whole text, not clipped
    * @param aClippedText Clipped / truncated text
    * @param aHighlight Does the current item have highlight
    * @param aIsTextClipped Is the current item clipped
    */
    IMPORT_C void DrawText(CWindowGc& aGc, const TRect& aTextRect, 
					    const TDesC& aText, const TDesC& aClippedText, const TInt aBaselineOffset,
					    const CGraphicsContext::TTextAlign aAlign, const CFont& aFont,
					    const TBool aHighlight, const TBool aIsTextClipped) const;


public:
    /**
    * Customizes marquee default behaviour. 
    * Use this before enabling marquee ( EnableMarqueeL() ), otherwise 
    * marquee behaviour will change during animation.
    * @since 2.8
    * @param aLoops Max number of loops to be executed (default 1)
    * @param aScrollAmount The amount of pixels scrolled per iteration (default 6)
    * @param aScrollDelay The interval between iterations (default 1000000)
    */
    IMPORT_C void SetMarqueeParams(const TInt aLoops, 
                        const TInt aScrollAmount, const TInt aScrollDelay);
    /**
    * Customizes marquee default behaviour. 
    * @since 2.8
    * @param aInterval The interval between frame updates
    */
    IMPORT_C void SetMarqueeParams(const TInt aLoops, const TInt aScrollAmount, 
                                    const TInt aScrollDelay, const TInt aInterval);                        

private:
    CArrayFix<SColumn>* iColumnArray;
    CColumnListBoxDataExtension *iExtension;
    };

#endif
