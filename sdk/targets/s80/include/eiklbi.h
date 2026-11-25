/*
* ==============================================================================
*  Name        : eiklbi.h
*  Part of     : CKON
*  Interface   : Listbox API
*  Description : Listbox item drawer.
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
* ==============================================================================
*/

#ifndef EIKLBI_H
#define EIKLBI_H

// INCLUDES
#include <e32base.h>
#include <gdi.h>
#include <lafpublc.h>
#include <w32std.h>

// FORWARD DECLARATIONS
class CWindowGc;
class CListBoxData;
class TListItemProperties;
class TListFontBoundValues;
class CSpriteSet;
class MTextListBoxModel;

// CLASS DECLARATIONS

/**
 * The <code>CListItemDrawer</code> class draws individual Listbox items for a 
 * <code>CListBoxView</code>. The items may be marked with a tick symbol to 
 * enable multiple selection.
 * This class may be derived from to provide a different appearance for a 
 * Listbox.
 * 
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CListItemDrawer : public CBase
    {

public:
    /**
     * The <code>TFlags</code> enumeration provides Listbox attributes for 
     * handling multiple selections. These flags can be set using the 
     * <code>CListItemDrawer::SetFlags</code> method.
     */
    enum TFlags
        {
        /** 
        * if set, specifies the inclusion of a gap into which a tick mark 
        * can be drawn if the item is selected. This is used in the following 
        * <code>CListItemDrawer</code> class methods: <code>DrawItem()</code>, 
        * <code>DrawItemMark()</code>, and <code>SetDrawMark()</code> 
        */
        EDrawMarkSelection          = SLafListBox::EItemDrawMarkSelection,
        /** 
        * if set, draws a highlight over a selected list item. This is used 
        * in the <code>CTextListItemDrawer::DoDrawItemText()</code> method 
        */
        EPaintedSelection           = SLafListBox::EItemPaintedSelection,
        /** 
        * in this mode, a Listbox shows the selected item only when the Listbox 
        * is focused. When not focused, in this mode, a Listbox displays the 
        * selected item using a passive focus rectangle, that is, a rectangle 
        * that is not filled
        */
        EDrawOnlyActiveSelection    = SLafListBox::EItemDrawOnlyActiveSelection,
        /** this flag is not supported */
        EDataWidthClippedToViewRect = SLafListBox::EDataWidthClippedToViewRect,
        /** 
        * this flag is for internal use only. It is used to distinguish 
        * between the Series 80 and Series 90 behavior 
        */
        ESeries80Behaviour = 0x80000000
        };
public:
    /**
     * The enumeration <code>TListItemAttribute</code> provides attributes 
     * for list items.
     */
    enum TListItemAttribute
        {
        /** if set, the highlight for current text */
        ECurrent    = SLafListBox::ECurrent,
        /** if set, the highlight for text when the Listbox view is emphasized. This is used in the following <code>CListBoxView</code> class methods: <code>DrawItem()</code>, <code>DrawMatcherCursor()</code>, and <code>SetEmphasized()</code> */
        EEmphasized = SLafListBox::EEmphasized,
        /** if set, the highlight for selected text. This is used in the following methods: <code>CColumnListBoxItemDrawer</code>::<code>DrawItemText()</code>, <code>CHierarchicalListItemDrawer::DrawActualItem()</code>, and <code>CDirContentsListItemDrawer::DrawActualItem()</code> */
        ESelected   = SLafListBox::ESelected,
        // this last attribute is used to control that one can use only
        // valid attributes above. So do not use it at all.
        /** do not use */
        EMask       = SLafListBox::EMask
        };

    public:
    // Constructors and destructor


       /**
        * The object destructor.
        */
        IMPORT_C ~CListItemDrawer();


    // New methods
        
       /**
        * Draws an entire Listbox item.
        * This method is called by the Listbox view. As implemented in
        * <code>CListItemDrawer</code>, this method draws the item text using
        * <code>DrawActualItem()</code> and an item mark using
        * <code>DrawItemMark()</code>.
        *
        * @param aItemIndex The index of the item to draw
        * @param aItemRectPos The position of the rectangle to draw
        * @param aItemIsSelected  Whether the item is selected
        * @param aItemIsCurrent Whether the item is current
        * @param aViewIsEmphasized Whether the Listbox view has the emphasized 
        *                          flag set (see 
        *                          <code>CListBoxView::SetEmphasized()</code>)
        * @param aViewIsDimmed Whether the Listbox view has its dimmed flag set
        *                      (see <code>CListBoxView::SetDimmed()</code>)
        * @remarks 'Emphasized', in terms of a Listbox item, refers to whether 
        *          the currently selected item is drawn with focus or not
        * @see
        */
        IMPORT_C virtual void DrawItem(TInt aItemIndex, TPoint aItemRectPos, TBool aItemIsSelected, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed) const;

        /**
        * Clears the specified rectangle of this object's graphics context.
        * This method draws a blank rectangle using the current background 
        * color.
        *
        * @param aRect The rectangle to clear
        * @remarks
        * @see
        */
        IMPORT_C virtual void ClearRect(const TRect& aRect) const;

        /**
        * Gets the width of the specified item.
        *
        * @param aItemIndex The index of the item whose width is to be returned
        * @return the width of the item. This implementation always returns 
        *         <code>0</code>
        * @remarks This method should be overridden in derived classes
        * @see
        */
        IMPORT_C virtual TInt ItemWidthInPixels(TInt aItemIndex) const;

        /**
        * Gets the minimum size of a cell.
        *
        * @return the minimum size of a cell. This implementation always returns 
        *         <code>TSize(0, 0)</code>
        * @remarks This method should be overridden in derived classes
        * @see
        */
        IMPORT_C virtual TSize MinimumCellSize() const;

        /**
        * Sets the graphics context that this object uses for drawing.
        * This method should be called before drawing the Listbox item.
        *
        * @param aGc A pointer to the context to use
        * @remarks
        * @see
        */
        IMPORT_C virtual void SetGc(CWindowGc* aGc);

        /**
        * Gets the graphics context.
        *
        * @return this object's graphics context
        * @remarks
        * @see
        */
        IMPORT_C CWindowGc* Gc() const;

        /**
        * Sets the width of the tick mark column. This is the column 
        * before the item text that can contain a tick mark, for 
        * multiple selection.
        *
        * @param aWidthInPixels The new width for the tick mark column
        * @remarks
        * @see
        */
        IMPORT_C virtual void SetMarkColumnWidth(TInt aWidthInPixels);

        /**
        * Sets the width of the gap between the column containing the list's
        * item tick marks and the text column.
        *
        * @param aGapInPixels The new size of the gap between columns
        * @remarks
        * @see
        */
        IMPORT_C virtual void SetMarkGutter(TInt aGapInPixels);

        /**
        * Gets the width of the item tick mark column. This is the column 
        * before the item text that can contain a tick mark, for 
        * multiple selection.
        *
        * @return the width of the item tick mark column
        * @remarks
        * @see
        */
        IMPORT_C TInt MarkColumn() const;

        /**
        * Gets the width of the gap between the column containing the list's
        * item tick marks and the text column.
        *
        * @return the size of the gap between the columns
        * @remarks
        * @see
        */
        IMPORT_C TInt MarkGutter() const;

        /**
        * Sets the item cell size.
        * The cell size is the onscreen size of the entire item, including its
        * text and its item mark.
        *
        * @param aSizeInPixels The new size for the item cell
        * @remarks This method does not redraw the Listbox
        * @see
        */
        IMPORT_C void SetItemCellSize(const TSize& aSizeInPixels);

        /**
        * Sets the viewing rectangle for this item drawer.
        * This value is not used by <code>CListItemViewer</code>, but may be
        * used by its derived classes.
        *
        * @param aRect The new value for the viewing rectangle
        * @remarks This method does not redraw the Listbox
        * @see
        */
        IMPORT_C virtual void SetViewRect(const TRect& aRect);

        /**
        * Sets whether item tick marks are drawn.
        * Sets or clears the <code>EDrawMarkSelection</code> flag.
        *
        * @param aDrawMark If <code>ETrue</code>, leaves space for the tick 
        *                  mark column to the left of the text column and draws 
        *                  the item tick marks; if <code>EFalse</code>, does 
        *                  not set aside space or draw tick marks
        * @remarks
        * @see
        */
        IMPORT_C void SetDrawMark(TBool aDrawMark);

        /**
        * Gets a rectangle describing where the matcher cursor should be drawn.
        * The matcher cursor is the cursor that highlights matched text by
        * incremental matching.
        * The default behavior is to return an uninitialized <code>TRect</code>.
        * This method should be overridden to supply a <code>TRect</code>
        * containing where the matcher cursor should be drawn.
        *
        * @param aMatchableText The text of the currently matched string
        * @param aCharPos The position in the string of the character just
        *                 matched in the current incremental match
        * @param aItemCellYPos The Y position of the item cell
        * @param aCurrentItemIndex The index of the item cell
        * @return where the cursor should be drawn.
        *         The default behavior is to return an uninitialized <code>TRect</code>
        * @remarks This method should be overridden in derived classes
        * @see
        */
        IMPORT_C virtual TRect MatcherCursorRect(const TDesC& aMatchableText, TInt aCharPos, TInt aItemCellYPos, TInt aCurrentItemIndex ) const;

        /**
        * Gets the ascent of the matcher cursor.
        * The matcher cursor is the cursor that highlights matched text via
        * incremental matching.
        * This is obtained for the item at index <code>aCurrentItemIndex</code>
        * determined from the ascent of the font used for that item. This method
        * returns zero by default.
        *
        * @param aCurrentItemIndex The index of the item
        * @return the height of the matcher cursor (the height from the top
        *         of the cursor to its baseline, in pixels).
        *         This method returns zero by default
        * @remarks This method should be overridden in derived classes
        * @see
        */
        IMPORT_C virtual TInt MatcherCursorAscent( TInt aCurrentItemIndex ) const;

        /**
        * Draws an item tick mark.
        * A tick mark is used when selecting more than one item from a list.
        * A tick mark indicates that an item is selected. If <code>iDrawMark</code>
        * is set, this method is invoked by the framework to draw a tick mark. 
        * The tick mark should be drawn into
        * this list item drawer's graphics context. By default,
        * <code>DrawItemMark()</code> draws a tick using the standard symbol
        * font. This method does not need to be re-implemented for derived
        * classes that do not draw tick marks.
        *
        * @param aItemIsSelected Whether the item to draw for is a selected item
        * @param aViewIsDimmed Whether the item to draw for is set as dimmed
        * @param aMarkPos The position of the tick mark to be drawn
        * @remarks
        * @see
        */
        IMPORT_C virtual void DrawItemMark(TBool aItemIsSelected, TBool aViewIsDimmed, const TPoint& aMarkPos) const;

        /**
        * Sets the symbol font used by this item drawer.
        * The symbol font is used to draw the standard tick marks.
        *
        * @param aFont The font to use
        * @remarks
        * @see
        */
        IMPORT_C void SetSymbolFont(const CFont* aFont);

        /**
        * Sets the vertical gap between the item rows in the list.
        *
        * @param aGapInPixels The new value for the vertical gap between items, 
        *                     in pixels
        * @remarks
        * @see
        */
        IMPORT_C void SetVerticalInterItemGap(TInt aGapInPixels);

        /**
        * Sets the font storage data <code>CListBoxData</code> for the item drawer
        * and transfers ownership of that data. <code>CListBoxData</code> also
        * handles the <code>SetSearchStringL()</code> functionality, and how items 
        * containing the search string are drawn.
        *
        * @param aData Font storage data
        * @remarks
        * @see CListBoxData
        */
        IMPORT_C void SetData(CListBoxData* aData);

        /**
        * Gets the font for the specified item.
        * This method returns <code>NULL</code> if no font storage data has 
        * been set.
        *
        * @param aItemIndex The index of the item for which the font is 
        *                   returned
        * @return the item's font
        * @remarks
        * @see
        */
        IMPORT_C CFont* Font(TInt aItemIndex) const;

        /**
        * Gets the color and style properties of the specified item.
        *
        * @param aItemIndex The index of the item for which properties are
        *            obtained
        * @return the item's properties
        * @remarks
        * @see
        */
        IMPORT_C virtual TListItemProperties Properties(TInt aItemIndex) const;

        /**
        * Draws the frame.
        * This method uses the colors set with the fonts and color methods 
        * described above.
        *
        * @param aGc The graphics context to use to draw the frame
        * @param aRect The frame's rectangle
        * @param aFlags The item drawer flags
        * @remarks
        * @see TFlags
        * @see TListItemAttribute
        */
        IMPORT_C void DrawFrame(CWindowGc& aGc,const TRect& aRect,TInt aFlags) const;

        /**
        * This method attempts to create a sprite set. This will also delete
        * the old sprite set.
        *
        * @param aWindowForSprite The window for which a sprite set should be 
        *                         created
        * @remarks This method currently does not create a new sprite set, and
        *          should be implemented by the developer
        * @see CSpriteSet in gulsprite.h
        */
        IMPORT_C void TryCreateSpriteSetL(RWindowTreeNode& aWindowForSprite);

        /**
        * Translates the sprite position, if it is visible. Otherwise, it 
        * stops the display of the sprite.
        *
        * @param aPos The amount by which the sprite's position should be moved
        * @param aIsVisible If the sprite should be moved, pass in 
        *                   <code>ETrue</code>; <code>EFalse</code> to stop 
        *                   displaying it
        * @remarks
        * @see CSpriteSet in gulsprite.h
        */
        IMPORT_C void TranslateSpritePosition(const TPoint& aPos, TBool aIsVisible);

        /**
        * Sets a new sprite set and deletes the old one.
        * The <code>CSpriteSet</code> class allows a window server sprite to be 
        * drawn to a window. The class supports storage of any number of bitmap
        * /mask pairs, but only allows one of these bitmap/mask members to be 
        * displayed at any one time.
        *
        * @param aSpriteSet The pointer to the new sprite set
        * @remarks
        * @see CSpriteSet in gulsprite.h
        */
        IMPORT_C void SetSpriteSet(CSpriteSet* aSpriteSet);

        /**
        * Sets the color used to draw non-highlighted text.
        *
        * @param aColor The text color
        * @remarks
        * @see
        */
        inline void SetTextColor(TRgb aColor);

        /**
        * Sets the color used to draw the background for non-highlighted items.
        *
        * @param aColor The background color
        * @remarks
        * @see
        */
        inline void SetBackColor(TRgb aColor);

        /**
        * Sets the color used to draw highlighted text.
        *
        * @param aColor The highlighted text color
        * @remarks
        * @see
        */
        inline void SetHighlightedTextColor(TRgb aColor);

        /**
        * Sets the color used to draw the background for highlighted items.
        *
        * @param aColor The highlighted background color
        * @remarks
        * @see
        */
        inline void SetHighlightedBackColor(TRgb aColor);

        /**
        * Sets the color used to draw dimmed text.
        *
        * @param aColor The dimmed text color
        * @remarks
        * @see
        */
        inline void SetDimmedTextColor(TRgb aColor);

        /**
        * Sets the color used to draw the background for dimmed items.
        *
        * @param aColor The background color for dimmed items
        * @remarks
        * @see
        */
        inline void SetDimmedBackColor(TRgb aColor);

        /**
        * Gets the color used to draw non-highlighted text.
        *
        * @return the text color
        * @remarks
        * @see
        */
        inline TRgb TextColor() const;

        /**
        * Gets the color used to draw the background for non-highlighted items.
        *
        * @return the background color
        * @remarks
        * @see
        */
        inline TRgb BackColor() const;

        /**
        * Gets the color used to draw highlighted text.
        *
        * @return the highlighted text color
        * @remarks
        * @see
        */
        inline TRgb HighlightedTextColor() const;

        /**
        * Gets the color used to draw the background for highlighted items.
        *
        * @return the highlighted background color
        * @remarks
        * @see
        */
        inline TRgb HighlightedBackColor() const;

        /**
        * Gets the color used to draw dimmed text.
        *
        * @return the dimmed text color
        * @remarks
        * @see
        */
        inline TRgb DimmedTextColor() const;

        /**
        * Gets the color used to draw the background for dimmed items.
        *
        * @return the background color for dimmed items
        * @remarks
        * @see
        */
        inline TRgb DimmedBackColor() const;

        /**
        * Gets the item drawer flags.
        *
        * @return the item drawer flags
        * @remarks
        * @see TFlags
        * @see TListItemAttribute
        */
        inline TInt Flags() const;

        /**
        * Sets the item drawer flags.
        *
        * @param aFlags The new item drawer flags
        * @remarks
        * @see TFlags
        * @see TListItemAttribute
        */
        IMPORT_C void SetFlags(TInt aFlags);

        /**
        * Clears the specified item drawer flags.
        *
        * @param aFlags The item drawer flags
        * @remarks
        * @see
        */
        IMPORT_C void ClearFlags(TInt aFlags);

        /**
        * This method is the accessor method for the sprite set member.
        *
        * @return the pointer to the current sprite set
        * @remarks
        * @see CSpriteSet in gulsprite.h
        */
        IMPORT_C CSpriteSet* SpriteSet() const;

        /**
        * Gets the color used to draw tick marks. A tick mark indicates 
        * that an item is selected.
        *
        * @return the tick mark color
        * @remarks
        * @see 
        */
        inline TRgb MarkColor() const;

        /**
        * Sets the flag that allows the item drawer to handle the fact that 
        * it's text may have been truncated to fit within the bounds of the 
        * list's view rectangle.
        *
        * @since App-Framework_6.2
        * @param aIsClipped The new state of the 
        *                   <code>EDataWidthClippedToViewRect</code> flag
        * @remarks
        * @see
        */
        IMPORT_C void SetDataWidthClippedToViewRect(TBool aIsClipped);

        /**
        * Returns a boolean value informing the client whether or not the text 
        * has been truncated to fit within the bounds of the list's view 
        * rectangle, so that special handling can be performed, for example, the 
        * addition of an ellipsis.
        *
        * @since App-Framework_6.2
        * @return the state of the <code>EDataWidthClippedToViewRect</code> 
        *         flag
        * @remarks
        * @see
        */
        IMPORT_C TBool DataWidthClippedToViewRect() const;

        /**
        * Draws a specified string in standard label font into the top 
        * position of the list. Used to display an empty list text.
        *
        * @param aText The string to display
        * @param aDimmed <code>ETrue</code> if the list is to be dimmed; 
        *                <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void DrawEmptyListText(const TDesC& aText, TBool aDimmed) const;

    protected:  // Methods

    // New Methods
        
        /**
        * Constructs a list item drawer.
         *
         * Note that the graphics context is not yet set; initialisation may be
         * completed with <code>SetGc()</code>.
        */
        IMPORT_C CListItemDrawer();

        /**
         * Draws item text.
         *
         * This function is called by <code>CListItemDrawer::DrawItem()</code>
         * with appropriate arguments. Its purpose is to draw the actual item (
         * everything other than the item mark) into the graphics context.
         *
         * @param aItemIndex Which item to draw.
         * @param aActualItemRect Where the item should be drawn.
         * @param aItemIsCurrent Whether the item is current.
         * @param aViewIsEmphasized Whether the Listbox view is emphasised.
         * @param aViewIsDimmed Whether the Listbox view is dimmed.
         * @param aItemIsSelected Whether the Listbox item is selected.
         */
        virtual void DrawActualItem(TInt aItemIndex,const TRect& aActualItemRect,TBool aItemIsCurrent,
                                    TBool aViewIsEmphasized,TBool aViewIsDimmed,TBool aItemIsSelected) const =0;
    
        /*
         * Resets the pen style, brush style, brush colour etc.
         *
         * to suitable starting values for this class. This function is called
         * after every drawing operation.
         *
         */
        IMPORT_C virtual void ResetGc() const;

        /**
        * Gets the vertical gap between items in pixels.
        * @return the vertical gap between items in pixels
        */
        IMPORT_C TInt VerticalInterItemGap() const;
        

        /**
        * Sets up the graphics context for the specified item.
        * @param aItemIndex The item for which the graphics context will be set
        *            up
        */
        IMPORT_C void SetupGc(TInt aItemIndex) const;

        /**
        * Gets the offset of the text from the base line.
        * @param aFont The font to be used.
        * @return the offset
        */
        IMPORT_C TInt BaseLineOffset(const CFont& aFont) const;

    private: //Methods

        IMPORT_C virtual TAny* Reserved_1();
        inline TInt& VerticalInterItemGap();
        inline const CFont* SymbolFont() const;
        inline const CFont*& SymbolFont();
        void ExtendMarkColWidthIfNeededL();		//Only used in Series 80.
    
    protected:     // Data
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

    private:     // Data
        const CFont* iSymbolFont;
        TInt iVerticalInterItemGap;
        CSpriteSet* iSpriteSet;
        TUint iFlags;
    };

/**
 * The <code>CTextListItemDrawer</code> class provides an item drawer that can 
 * handle text. This class is used by <code>CListBoxView</code> to draw 
 * individual Listbox items for a <code>CEikTextListBox</code>.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CTextListItemDrawer : public CListItemDrawer
    {

    public:
    // Constructors and destructor
       /**
        * The object constructor.
        */
        IMPORT_C CTextListItemDrawer();

       /**
        * The object destructor.
        */
        IMPORT_C ~CTextListItemDrawer();

    // New methods
        
       /**
        * Constructs a new text item drawer that draws the data of the
        * specified model using the supplied font.
        *
        * @param aTextListBoxModel The model whose items will be drawn
        * @param aFont The font in which the items will be drawn
        * @remarks
        * @see <code>MTextListBoxModel</code> in eiklbm.h
        * @see <code>CFont</code> in gdi.h
        */
        IMPORT_C CTextListItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont);

       /**
        * Completes construction of the <code>CTextListItemDrawer</code> object.
        * 
        * @param aFont The font in which the Listbox items are drawn
        * @remarks
        * @see <code>CFont</code> in gdi.h
        */
        IMPORT_C void ConstructL(const CFont* aFont);

       /**
        * Draws the actual item contents for the specified item in the 
        * specified rectangle.
        *
        * @param aItemIndex The index of the item to draw
        * @param aActualItemRect The area to draw into
        * @param aItemIsCurrent <code>ETrue</code> if the item is current; 
        *                       <code>EFalse</code> otherwise 
        * @param aViewIsEmphasized <code>ETrue</code> if the view is emphasized;
        *                          <code>EFalse</code> otherwise 
        * @param aViewIsDimmed Ignored in this class's method
        * @param aItemIsSelected <code>ETrue</code> if the view is dimmed; 
                                 <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C virtual void DrawActualItem(TInt aItemIndex, const TRect& aActualItemRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed,TBool aItemIsSelected) const;

       /**
        * Gets the width of the specified item, in pixels, taking into account 
        * the current font and whether the tick mark column is being used (via 
        * the flag <code>EDrawMarkSelection</code>).
        *
        * @param aItemIndex The index of the item for which the width is 
        *                   obtained
        * @return the width of the specified item, in pixels
        * @remarks
        * @see
        */
        IMPORT_C virtual TInt ItemWidthInPixels(TInt aItemIndex) const;

       /**
        * Gets the minimum size of a cell.
        * A cell refers to a single Listbox item excluding any margins or
        * scrollbars.
        *
        * @return the minimum size for a cell, in pixels
        * @remarks
        * @see
        */
        IMPORT_C virtual TSize MinimumCellSize() const;

       /**
        * Sets the graphics context and sets it to use the font set
        * via the method <code>SetFont()</code>.
        *
        * @param aGc The graphics context to use
        * @remarks
        * @see
        */
        IMPORT_C virtual void SetGc(CWindowGc* aGc);

       /**
        * Sets the minimum number of characters to display in a cell.
        * A cell refers to a single Listbox item excluding any margins or
        * scrollbars.
        * 
        * @param aNumOfCharsToDisplayInCell The number of characters to display 
        *                                   in a cell
        * @remarks This value only affects the method <code>MinimumCellSize()</code>,
        *          which calculates the smallest size for a Listbox item
        * @see
        */
        IMPORT_C void SetCellWidthInChars(TInt aNumOfCharsToDisplayInCell);

       /**
        * Gets the position and size of the matcher cursor.
        * The matcher cursor is the cursor that highlights matched text via
        * incremental matching.
        *
        * @param aMatchableText The string currently being matched
        * @param aCharPos The position within the string
        * @param aItemCellYPos The Y position of the item cell, in pixels
        * @param aCurrentItemIndex The index of the current item
        * @return the rectangle covered by the matcher cursor, in pixels
        * @remarks
        * @see CListItemDrawer::MatcherCursorRect()
        * @see CListBoxView::EHasMatcherCursor
        */
        IMPORT_C virtual TRect MatcherCursorRect(const TDesC& aMatchableText, TInt aCharPos, TInt aItemCellYPos, TInt aCurrentItemIndex ) const;

        /**
        * Gets the ascent of the matcher cursor, in pixels.
        * The ascent is the number of pixels from the top of the cursor
        * to the baseline.
        *
        * @param aCurrentItemIndex The index of the current item
        * @return the ascent of the matcher cursor, in pixels
        * @remarks
        * @see
        */
        IMPORT_C virtual TInt MatcherCursorAscent( TInt aCurrentItemIndex ) const;

        /**
        * Sets the font to use when drawing items. This is set in the graphics
        * context.
        * 
        * @param aFont The font to use
        * @remarks
        * @see CFont in gdi.h
        */
        IMPORT_C void SetFont(const CFont* aFont);

        /**
        * Sets the search string.
        * This method allows text in the displayed list items,  
        * which contains the specified search string, to be highlighted.
        *
        * @param aSearchString  The new search string
        * @remarks This method requires that <code>SetData()</code> has been
        *          called to set the <code>CListBoxData</code> property.
        * @see <code>CListBoxData</code> in eiklbd.h
        */
        IMPORT_C void SetSearchStringL(const TDesC* aSearchString);

        /**
        * Gets the font for the specified item.
        *
        * @param aIndex The index of the item for which the font is obtained
        * @return the specified item's font
        * @remarks
        * @see
        */
        IMPORT_C const CFont* Font(TInt aIndex) const;

    protected:  // Methods

    // New Methods
        
        /**
        * Draws text.
         *
         * This function is invoked by <code>DrawItemText()</code> to draw a
         * string into a rectangular area of <code>iGc</code>.
        * @param aDes The string to draw.
        * @param aItemTextRect Area to draw into.
        * @param aItemIsCurrent <code>ETrue</code> if the item is current.
        * @param aViewIsEmphasized <code>ETrue</code> if the item is emphasised.
        * @param aItemIsSelected <code>ETrue</code> if the item is selected.
        * @param aItemIndex The item's index.
        */
        IMPORT_C virtual void DoDrawItemText(const TDesC& aDes, const TRect& aItemTextRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aItemIsSelected, TInt aItemIndex) const;

        /**
        * Draw item text.
         *
         * This function is invoked by <code>DrawActualItem()</code> to draw the
         * item text.
        * @param aItemIndex Index of the item to draw.
        * @param aItemTextRect Area to draw into.
        * @param aItemIsCurrent <code>ETrue</code> if the item is current.
        * @param aViewIsEmphasized <code>ETrue</code> if the view is emphasised.
        * @param aItemIsSelected <code>ETrue</code> if the view is selected.
        */
        IMPORT_C virtual void DrawItemText(TInt aItemIndex, const TRect& aItemTextRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aItemIsSelected) const;

        /**
        * Resets the graphics context.
         *
         * This function invokes <code>CListItemDrawer::ResetGc()</code> and
         * resets the pen colour to <code>iTextColor</code>.
        */
        IMPORT_C virtual void ResetGc() const;

        IMPORT_C TInt doMatcherCursorAscent(const CFont *aFont) const;
        IMPORT_C TRect doMatcherCursorRect(const TDesC& aMatchableText,TInt aCharPos,TInt aItemCellYPos, const CFont *aFont) const;
    private: //Methods
        IMPORT_C virtual TAny* Reserved_1();

    private:
        void DoSeries90DrawItemText(const TDesC& aDes, const TRect& aItemTextRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aItemIsSelected, TInt aItemIndex) const;
        void DoSeries80DrawItemText(const TDesC& aDes, const TRect& aItemTextRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aItemIsSelected, TInt aItemIndex) const;

    protected:     // Data
        MTextListBoxModel* iModel;
        const CFont* iFont;

    private:     // Data
        TInt iNumOfCharsInCell;
    };

/**
 * The <code>TListItemProperties</code> class provides color and style 
 * properties that can be applied when drawing the contents of Listbox items.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class TListItemProperties
    {
    private:  // Declarations
    enum
        {
        ELbxItemBold        = 0x0001,
        ELbxItemItalics     = 0x0002,
        ELbxItemUnderlined  = 0x0004,
        ELbxItemDimmed      = 0x0008    
        };

    public:
    // Constructors and destructor
        /**
        * The default object constructor.
        */
        IMPORT_C TListItemProperties();


    // New methods
        
        /**
        * Sets whether the list item is drawn bold or not bold.
        *
        * @param aBold <code>ETrue</code> to draw the list item bold: 
        *              <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        inline void SetBold(TBool aBold);

        /**
        * Determines whether the list item is drawn bold.
        *
        * @return <code>ETrue</code> if the list item is drawn bold;
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        inline TBool IsBold() const;

        /**
        * Sets whether or not the list item is drawn in italics.
        *
        * @param aItalics <code>ETrue</code> to draw the list item in italics; 
        *                 <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        inline void SetItalics(TBool aItalics);

        /**
        * Determines whether the list item is drawn in italics.
        *
        * @return <code>ETrue</code> if the list item is drawn in
        *         italics; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        inline TBool IsItalics() const;

        /**
        * Sets whether or not the list item is drawn with an underline.
        *
        * @param aUnderlined <code>ETrue</code> to draw the list item with an
        *        underline; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        inline void SetUnderlined(TBool aUnderlined);

       /**
        * Determines whether the list item is underlined.
        *
        * @return <code>ETrue</code> if the list item is drawn underlined; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        inline TBool IsUnderlined() const;

       /**
        * An item is usually drawn dimmed to indicate that it cannot accept 
        * user input.
        *
        * @param aDimmed <code>ETrue</code> to draw the list item dimmed;
        *                <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        inline void SetDimmed(TBool aDimmed);

        /**
        * Determines the list item's dim state.
        * An item is usually drawn dimmed to indicate that it cannot accept 
        * user input.
        *
        * @return <code>ETrue</code> if the list item is dimmed; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        inline TBool IsDimmed() const;

        /**
        * Sets the list item's color.
        *
        * @param aColor The list item's color
        * @remarks
        * @see
        */
        inline void SetColor(TRgb aColor);

        /**
        * Gets the list item's color.
        *
        * @return the list item's color
        * @remarks
        * @see
        */
        inline TRgb Color() const;

    private:     // Data
        TUint iFlags;
        TRgb iColor;
    };

//
// Inlines
//
inline void CListItemDrawer::SetTextColor(TRgb aColor)
    {iTextColor=aColor;}

inline void CListItemDrawer::SetBackColor(TRgb aColor)
    {iBackColor=aColor;}

inline void CListItemDrawer::SetHighlightedTextColor(TRgb aColor)
    {iHighlightedTextColor=aColor;}

inline void CListItemDrawer::SetHighlightedBackColor(TRgb aColor)
    {iHighlightedBackColor=aColor;}

inline void CListItemDrawer::SetDimmedTextColor(TRgb aColor)
    {iDimmedTextColor=aColor;}

inline void CListItemDrawer::SetDimmedBackColor(TRgb aColor)
    {iDimmedBackColor=aColor;}

inline TRgb CListItemDrawer::TextColor() const
    {return iTextColor;}

inline TRgb CListItemDrawer::BackColor() const
    {return iBackColor;}

inline TRgb CListItemDrawer::HighlightedTextColor() const
    {return iHighlightedTextColor;}

inline TRgb CListItemDrawer::HighlightedBackColor() const
    {return iHighlightedBackColor;}

inline TRgb CListItemDrawer::DimmedTextColor() const
    {return iDimmedTextColor;}

inline TRgb CListItemDrawer::DimmedBackColor() const
    {return iDimmedBackColor;}

inline TRgb CListItemDrawer::MarkColor() const
    {return iMarkColor;}

inline TInt CListItemDrawer::Flags() const
    {return iFlags;}

inline TBool TListItemProperties::IsItalics() const
    {return iFlags&ELbxItemItalics;}

inline TBool TListItemProperties::IsBold() const
    {return iFlags&ELbxItemBold;}

inline TBool TListItemProperties::IsUnderlined() const
    {return iFlags&ELbxItemUnderlined;}

inline TBool TListItemProperties::IsDimmed() const
    {return iFlags&ELbxItemDimmed;}

inline void TListItemProperties::SetColor(TRgb aColor)
    {iColor=aColor;}

inline TRgb TListItemProperties::Color() const
    {return iColor;}

inline void TListItemProperties::SetBold(TBool aBold)
    {
    if (aBold) 
        iFlags|=ELbxItemBold;
    else
        iFlags&=(~ELbxItemBold);
    }

inline void TListItemProperties::SetItalics(TBool aItalics)
    {
    if (aItalics)
        iFlags|=ELbxItemItalics;
    else
        iFlags&=(~ELbxItemItalics);
    }

inline void TListItemProperties::SetUnderlined(TBool aUnderlined)
    {
    if (aUnderlined)
        iFlags|=ELbxItemUnderlined;
    else
        iFlags&=(~ELbxItemUnderlined);
    }

inline void TListItemProperties::SetDimmed(TBool aDimmed)
    {
    if (aDimmed)
        iFlags|=ELbxItemDimmed;
    else
        iFlags&=(~ELbxItemDimmed);
    }
    
#endif      // EIKLBI_H   
            
// End of File
