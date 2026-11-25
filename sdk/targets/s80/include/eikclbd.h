/*
* =============================================================================
*  Name        : eikclbd.h
*  Part of     : CKON
*  Interface   : Column Listbox API
*  Description : Column Listbox data
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* =============================================================================
*/

#ifndef EIKCLBD_H
#define EIKCLBD_H


// INCLUDES
#include <e32base.h>
#include <gdi.h>
#include <eiklbd.h>

// CONSTANTS
/** used if there is to be no icon in an otherwise graphic column */
const TInt KNoIcon=-1;

// FORWARD DECLARATIONS
class CWindowGc;
class CGulIcon;


// CLASS DECLARATIONS

/**
*  The <code>CColumnListBoxData</code> class handles the data required to draw 
*  a Column Listbox.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CColumnListBoxData : public CListBoxData
    {
    public:  // Declarations

    /**
     *  The <code>TColors</code> data structure is used to store the text and 
     *  background colors for the Column Listbox, for both normal and 
     *  highlighted items.
     *
     *  @lib eikctl.lib
     *  @since Series90 1.0
     */
    class TColors
        {
    public:
        /**
        * Constructs and initializes the data colors to blacks and whites.
        */
        IMPORT_C TColors();
    public:
        /** the color of the text in the Column Listbox */
        TRgb iText;
        /** the color of the background */
        TRgb iBack;
        /** the color of highlighted text */
        TRgb iHighlightedText;
        /** the color of highlighted background */
        TRgb iHighlightedBack;
        };

    public:
    // Constructors and destructor

        /**
        * Starts the two-phase object construction.
        * 
        * @return a pointer to the Column Listbox data item
        * @remarks
        * @see
        */
        IMPORT_C static CColumnListBoxData* NewL();

        /**
        * The object destructor.
        */
        IMPORT_C ~CColumnListBoxData();


    // New methods
        
        /**
        * Gets the last column defined.
        * 
        * @return the column with the largest index, or 
        *         <code>KErrNotFound</code> if there are no columns
        * @remarks
        * @see
        */
        IMPORT_C TInt LastColumn() const;

        /**
        * Gets the width of a specified column.
        *
        * @param aColumn The index of the column for which the width is 
        *                required
        * @return the width of the column, in pixels. Zero is returned if no 
        *         column exists at the specified index
        * @remarks
        * @see
        */
        IMPORT_C TInt ColumnWidthPixel(TInt aColumn) const;

        /**
        * Sets a column's width. If no column data is found at the specified 
        * index, a new column is created.
        *
        * @param aColumn The index of the column for which the width is to be 
        *                set
        * @param aWidth The new width for the column, in pixels
        * @remarks
        * @see
        */
        IMPORT_C void SetColumnWidthPixelL(TInt aColumn,TInt aWidth);

        /**
        * Returns the horizontal gap of a column. The gap is shown to the 
        * right of the column and is the space between the right-hand edge of 
        * <code>aColumn</code> and the left-hand edge of the next column 
        * to the right.  
        *
        * @param aColumn The index of the column for which the gap is to be 
        *                returned
        * @return the horizontal gap of the column
        * @remarks
        * @see
        */
        IMPORT_C TInt ColumnHorizontalGap(TInt aColumn) const;

        /**
        * Sets a column's horizontal gap, in pixels. The gap is shown to the 
        * right of the column and is the space between the right-hand edge of
        * <code>aColumn</code> and the right-hand edge of the next column 
        * to the right. If no column data is found at the specified index, 
        * a new column is created.
        *
        * @param aColumn The specified column
        * @param aGap The gap width
        * @remarks
        * @see
        */
        IMPORT_C void SetColumnHorizontalGapL(TInt aColumn,TInt aGap);

        /**
        * Gets a column's font.
        *
        * @param aColumn The index of the column for which the font is to be 
        *                obtained
        * @return the column's font, or <code>NULL</code> if no data exists at 
        *         the specified column index
        * @remarks
        * @see
        */
        IMPORT_C const CFont* ColumnFont(TInt aColumn) const;

        /**
        * Sets a column's font.  Ownership is passed to the column.
        * If no column data is found at the specified index, a new column is created.
        * 
        * @param aColumn The index of the column for which the 
        *                font is to be set
        * @param aFont The new font for the column
        * @remarks
        * @see
        */
        IMPORT_C void SetColumnFontL(TInt aColumn,const CFont* aFont);

        /**
        * Gets a column's text alignment.
        *
        * @param aColumn The index of the column for which the
        *        alignment is to be obtained
        * @return the text alignment for the column. The default is 
        *         <code>ELeft</code>. <code>TAlign</code> can be found in 
        *         e32std.h and suitable values are <code>ELeft</code>, 
        *         <code>ECenter</code>, and <code>ERight</code>
        * @remarks
        * @see
        */
        IMPORT_C CGraphicsContext::TTextAlign ColumnAlignment(TInt aColumn) const;
        
        /**
        * Sets a column's text alignment.
        * If no column data is found at the specified index, a new column is created.
        *
        * @param aColumn The index of the column for which the 
        *        alignment is to be set
        * @param aAlign The new text alignment for the column
        * @remarks
        * @see
        */
        IMPORT_C void SetColumnAlignmentL(TInt aColumn,CGraphicsContext::TTextAlign aAlign);

        /**
        * Tests whether a column contains graphics.  
        *
        * @param aColumn The index of the column to be tested
        * @return <code>ETrue</code> if the specified column is a graphical 
        *         column; <code>EFalse</code> if not. The default is 
        *         <code>EFalse</code>
        * @remarks This method returns <code>ETrue</code> if the column is set 
        *          to graphical even if no icons are currently present
        * @see
        */
        IMPORT_C TBool ColumnIsGraphics(TInt aColumn) const;

        /**
        * Sets whether a column will contain graphics.
        * If no column data is found at the specified index, a new column is created.
        * 
        * @param aColumn The index of the column
        * @param aIsGraphics <code>ETrue</code> if the specified
        *         column contains graphics; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetGraphicsColumnL(TInt aColumn,TBool aIsGraphics);

        /**
        * Gets a list of icons. These icons are used to contain the graphics 
        * that are displayed in graphical columns.
        *
        * @return a pointer to the array of icons
        * @remarks
        * @see
        */
        IMPORT_C CArrayPtr<CGulIcon>* IconArray() const;

        /**
        * Sets the icon array. These icons are used to contain the graphics
        * that are displayed in graphical columns. This method passes ownership 
        * of the icon list <code>aArray</code> to the Column Listbox. It is 
        * assumed that the caller has cleared any previous array.
        *
        * @param aArray The new bitmap array
        * @remarks
        * @see
        */
        IMPORT_C void SetIconArray(CArrayPtr<CGulIcon>* aArray);

        /**
        * Gets the font, color, and style properties for the specified column.
        *
        * @param aItemProperties The color and style properties, for example,
        *                        <code>ELbxItemBold</code> to be applied to 
        *                        the specified column. See eiklbi.h
        * @param aColumn The column to which the color and style
        *                properties are to be applied
        * @return the column's item font
        * @remarks
        * @see
        */
        IMPORT_C CFont* Font(const TListItemProperties& aItemProperties, TInt aColumn) const;

        /**
        * Returns the given column's rectangle.
        *
        * @param aColumn The index of the column for which the rectangle is to 
        *                be obtained
        * @param aRect On return, contains the column's rectangle
        * @return <code>EFalse</code> if the specified column does not exist; 
        *          <code>ETrue</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool MakeColumnRect( TInt aColumn, TRect& aRect );

        /**
        * Draws a single row. The text <code>aText</code> is parsed into 
        * columns. <code>aText</code> is split on 
        * <code>KColumnListSeparator</code>. Text or bitmaps are drawn 
        * according to whether the column has been set as a graphic (see 
        * <code>SetGraphicsColumnL()</code>) or text column. If a cell is in a 
        * text column, its text is drawn into the rectangle specified by its 
        * column width (see <code>SetColumnWidthPixelL()</code>). If a cell is 
        * in a graphic column, the text for that column is parsed into a 
        * single <code>TInt</code> as a decimal string, which is used to index 
        * the icon array (see <code>SetIconArray()</code>). The appropriate 
        * icon from the array is drawn into the cell's rectangle.
        * This method is called from 
        * <code>CColumnListBoxItemDrawer::DrawItemText</code>. The row to be 
        * drawn is identified by the <code>aRect</code> parameter.
        * 
        * @param aItemProperties The properties of each column in the row (eiklbi.h)
        * @param aGc The graphics context to draw into (w32std.h)
        * @param aText The text to parse and draw
        * @param aRect The bounding rectangle for the entire row
        * @param aHighlight <code>ETrue</code> to draw the item highlighted; 
        *                   <code>EFalse</code> otherwise
        * @param aColors The colors to use if the item is highlighted (gulbordr.h)
        * @remarks Column cells within the row are drawn from left to right
        * @see
        */
        IMPORT_C virtual void Draw(const TListItemProperties& aItemProperties, CWindowGc& aGc,const TDesC* aText,const TRect& aRect,TBool aHighlight,const TColors& aColors) const;

        /**
        * As the previous <code>Draw()</code> method, but with an additional 
        * baseline offset property, <code>aBaseLineOffset</code>,
        * that specifies the offset from which the item will be drawn.
        *
        * @param aItemProperties The properties of each column in the row
        * @param aGc The graphics context to draw into
        * @param aText The text to parse and draw
        * @param aRect The bounding rectangle for the entire row
        * @param aHighlight <code>ETrue</code> to draw the item highlighted;
        *                   <code>EFalse</code> otherwise
        * @param aColors The colors to use if the item is highlighted
        * @param aBaseLineOffset The offset to be specified
        * @remarks See previous <code>Draw()</code> method for more details
        * @see
        */
        IMPORT_C virtual void Draw(const TListItemProperties& aItemProperties, CWindowGc& aGc,const TDesC* aText,const TRect& aRect,TBool aHighlight,const TColors& aColors,TInt aBaseLineOffset) const;

        /**
        * Sets the search string and column for the Column Listbox.
        * For more information, see <code>CListBoxData</code>.
        *
        * @param aSearchString The search string
        * @param aColumnIndex The column to which the search string is to be 
        *                     applied
        * @remarks
        * @see
        */
        IMPORT_C void SetSearchStringL(const TDesC* aSearchString,const TInt aColumnIndex=0);

        /**
        * Sets that fonts passed in <code>SetColumnFontL()</code> are used 
        * directly. Otherwise these fonts are used as a base font for 
        * generating fonts. Sets the flag <code>EUseColumnFontsDirectly</code>.
        *
        * @remarks
        * @see
        */
        IMPORT_C void SetUsesColumnFontsDirectly();

        /** @internal */
        const CFont* FontHandleNull(const TListItemProperties& aItemProperties, TInt aColumn) const;

    private:
        /** Private structures */
        /** @internal */
        struct SColumn
            {
            TInt iColumn; // Must be first entry
            TInt iWidth;
            TInt iVerticalCap;
            const CFont* iBaseFont;
            TInt iActualFontIndex;
            TBool iGraphics;
            CGraphicsContext::TTextAlign iAlign;
            };
        /** Private flags */
        /** @internal */
        enum TFlags
            {
            /** If set, uses column fonts directly */
            EUseColumnFontsDirectly=0x0001
            };
    protected:  // Methods
        
        /**
        * Protected default constructor. This constructor is protected to ensure that users call the static NewL() 
        * constructor to create and fully construct this object.
        */
        IMPORT_C CColumnListBoxData();

        /**
        * Deferred constructor. This is called by NewL() to complete construction of this class.
        */
        IMPORT_C void ConstructLD();

    private: //Methods
        void AddColumnL(TInt aColumn);
        SColumn& At(TInt aArrayIndex);
        const SColumn& At(TInt aArrayIndex) const;
        TInt FindColumnIndex(TInt& aArrayIndex,TInt aColumn) const;
        void FindColumnIndexOrAddL(TInt& aArrayIndex,TInt aColumn);
        TInt AddActualFontL(const CFont* aBaseFont);

    private:     // Data
        CArrayFix<SColumn>* iColumnArray;
        CArrayPtr<CGulIcon>* iIconArray;
        TInt iSearchStrColumn;
        TInt iFlags;
    };


#endif      // EIKCLBD_H   
            
// End of File
