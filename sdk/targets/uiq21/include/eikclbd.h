// EIKCLBD.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//
#ifndef __EIKCLBD_H__
#define __EIKCLBD_H__

#include <e32base.h>
#include <gdi.h>
#include <eiklbd.h>

class CWindowGc;
class CGulIcon;

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
	IMPORT_C const CFont* ColumnFont(TInt aColumn) const;
	IMPORT_C void SetColumnFontL(TInt aColumn,const CFont* aFont);
	//
	IMPORT_C const TBool ColumnUsesItemSpecificFont(TInt aColumn) const;
	IMPORT_C void SetColumnUsesItemSpecificFontL(TInt aColumn, TBool aUseFontPropertiesSpecificToItem);
	//
	IMPORT_C CGraphicsContext::TTextAlign ColumnAlignment(TInt aColumn) const;
	IMPORT_C void SetColumnAlignmentL(TInt aColumn,CGraphicsContext::TTextAlign aAlign);
	//
	IMPORT_C TBool ColumnIsGraphics(TInt aColumn) const;
	IMPORT_C void SetGraphicsColumnL(TInt aColumn,TBool aIsGraphics);
	//
	IMPORT_C TBool ColumnIsLefthandInterlacing(TInt aColumn) const;
	IMPORT_C void SetLefthandInterlacingColumnL(TInt aColumn);
	//
	IMPORT_C CArrayPtr<CGulIcon>* IconArray() const;
	IMPORT_C void SetIconArray(CArrayPtr<CGulIcon>* aArray);
    //
    IMPORT_C CFont* Font(const TListItemProperties& aItemProperties, TInt aColumn) const;
    IMPORT_C TBool MakeColumnRect(TInt aColumn, TRect& aRect);
	IMPORT_C virtual void Draw(const TListItemProperties& aItemProperties, CWindowGc& aGc, const TDesC* aText, const CFont& aDefaultFont, const TRect& aRect, TBool aHighlight, const TColors& aColors) const;

	IMPORT_C void SetSearchStringL(const TDesC* aSearchString,const TInt aColumnIndex=0);

	IMPORT_C void SetInnerGutter(TInt aInnerGutter);
	IMPORT_C TInt GetInnerGutter() const;
private:
    struct SColumn
        {
        TInt iColumn; // Must be first entry
        TInt iWidth;
        TInt iHorizontalGap;
        const CFont* iBaseFont;
        TInt iActualFontIndex;
        TBool iGraphics;
		TBool iIsLefthandInterlacing;
        CGraphicsContext::TTextAlign iAlign;
		TBool iUseItemFontProperties;
        };
protected:
    IMPORT_C CColumnListBoxData();
	IMPORT_C void ConstructL();	
protected: 
	IMPORT_C void ConstructLD();	// deprecated
private:
	void AddColumnL(TInt aColumn);
	SColumn& At(TInt aArrayIndex);
	const SColumn& At(TInt aArrayIndex) const;
	TInt FindColumnIndex(TInt& aArrayIndex,TInt aColumn) const;
	void FindColumnIndexOrAddL(TInt& aArrayIndex,TInt aColumn);
    TInt AddActualFontL(const CFont* aBaseFont);
private:
	CArrayFix<SColumn>* iColumnArray;
	CArrayPtr<CGulIcon>* iIconArray;
	TInt iSearchStrColumn;
	TInt iInnerGutter;
private:
	TInt iSpare2;
	};

#endif	// __EIKCLBD_H__
