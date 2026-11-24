/*
* ============================================================================
*  Name     : Eikfrlbd.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/
//
// EIKFRLBD.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKFRLBD_H__)
#define __EIKFRLBD_H__

#include <e32base.h>
#include <gdi.h>

#include <eiklbd.h>
#include <eikfrlb.h>
#include <avkon.hrh>

class CWindowGc;
class CGulIcon;
class CFormattedCellListBoxDataExtension;
class MAknsControlContext;
class TAknsItemID;
class CAknLayoutData;

/**
*  CFormattedCellListBoxData can draw list items
*  This is similar class than CColumnListBoxData from eikstd, but it can
*  more freely layout the list items; more parameters can be
*  used to position the elements. In particular, the position
*  of the elements is free, and not tied to fixed width columns.
*
*  This class is used to draw most of the Series60 list and grid layouts,
*
*  It also handles truncation of the text elements, centering
*  and cropping of images, z-order/overlapping cells, bi-directional
*  text drawing, backgrounds for lists, highlight drawing, various
*  text and image properties and finally the parts of the separator
*  lines that are inside list items.
*
* This is a very low level class. The less you use this class, the
* better. Applications should be using CAknSelectionListDialog
* or CAknMarkableListDialog or CAknListQueryDialog to use lists.
* There are enough predefined list layouts available; there should
* not be need for applications to use this class.
* See Style Guide for more information. Use of this class may
* cause your application to not look ok when properties of the
* device change.
*
*  @lib avkon
*  @since 0.0
*/
class CFormattedCellListBoxData : public CListBoxData
    {
public:
    class TColors
        {
    public:
        IMPORT_C TColors();
    public:
        // Text colour
        TRgb iText;
        // Background colour
        TRgb iBack;
        // Highlighted text colour
        TRgb iHighlightedText;
        // Highlighted background colour
        TRgb iHighlightedBack;
        // separator line colour
        TRgb iRightSeparatorColor;
        };
public:
    IMPORT_C static CFormattedCellListBoxData* NewL();
    IMPORT_C ~CFormattedCellListBoxData();
public:
    /**
    * SubCellColors queries colours attached to the cell.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return text and background colours in different situations
    */
    IMPORT_C const TColors& SubCellColors(TInt aSubCellIndex) const;
    /**
    * SetSubCellColorsL() sets colours attached to the cell.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetSubCellColorsL(TInt aSubCellIndex, const TColors &aColors);

    /**
    * SubCellBaselinePos queries baseline position from top of the cell
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return baseline y-position
    */
    IMPORT_C TInt SubCellBaselinePos(TInt aSubCellIndex) const;
    /**
    * SetSubCellBaselinePosL() sets baseline position from top of the cell
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetSubCellBaselinePosL(TInt aSubCellIndex, TInt aSize);

    /**
    * SubCellSize queries cell size in pixels.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return cell size
    */
    IMPORT_C TSize SubCellSize(TInt aSubCellIndex) const;
    /**
    * SetSubCellSizeL() sets cell size in pixels.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetSubCellSizeL(TInt aSubCellIndex, TSize aSize);

    /**
    * SubCellPosition queries cell position inside an item.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return cell position
    */
    IMPORT_C TPoint SubCellPosition(TInt aSubCellIndex) const;
    /**
    * SetSubCellPositionL() sets cell position inside an item.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetSubCellPositionL(TInt aSubCellIndex, TPoint aPosition);

    /**
    * SubCellIsTransparent determines whether this cell can overlap with 
    * one of the previous cells.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return ETrue = overlaps, EFalse = allocates area from other cells
    */
    IMPORT_C TBool SubCellIsTransparent(TInt aSubCellIndex) const;
    /**
    * SetTransparentSubCellL() modifies whether the cell can overlap with
    * one of the previous cells.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetTransparentSubCellL(TInt aSubCellIndex, TBool aIsTransparent);

    /**
    * SubCellIsNotAlwaysDrawn checks whether drawing algorithm always
    * draws the cell or whether empty string in list item string can
    * disable the drawing of the cell.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return ETrue = empty string disables cell, EFalse = always drawn
    */
    IMPORT_C TBool SubCellIsNotAlwaysDrawn(TInt aSubCellIndex) const;
    /**
    * SetNotAlwaysDrawnSubCellL() sets whether drawing algorithm always
    * draws the cell.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetNotAlwaysDrawnSubCellL(TInt aSubCellIndex, TBool aIsNotAlwaysDrawn);

    /**
    * SubCellMargins queries margins used for the content inside the cell.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return margins in pixels
    */
    IMPORT_C TMargins SubCellMargins(TInt aSubCellIndex) const;
    /**
    * SetSubCellMarginsL() sets margins for the content inside the cell.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetSubCellMarginsL(TInt aSubCellIndex, TMargins aMargins);

    /**
    * SubCellFont queries font attached to the cell.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return font handle
    */
    IMPORT_C const CFont* SubCellFont(TInt aSubCellIndex) const;
    /**
    * SetSubCellFontL() sets the font attached to the cell.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetSubCellFontL(TInt aSubCellIndex, const CFont* aFont);

    /**
    * SubCellAlignment queries the alignment attached to the cell.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return alignment. CGraphicsContext::ELeft, CGraphicsContext::ERight or CGraphicsContext::ECenter.
    */
    IMPORT_C CGraphicsContext::TTextAlign SubCellAlignment(TInt aSubCellIndex) const;
    /**
    * SetSubCellAlignmentL() sets the alignment attached to the cell.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetSubCellAlignmentL(TInt aSubCellIndex, CGraphicsContext::TTextAlign aAlign);

    /**
    * SubCellIsGraphics queries whether drawing algorithm considers the text
    * string in list item as unicode text string displayable on the screen, or as 
    * string representation of an index to icon array.
    *  
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return ETrue = graphics cell, EFalse = text cell
    */
    IMPORT_C TBool SubCellIsGraphics(TInt aSubCellIndex) const;
    /**
    * SetGraphicsSubCellL() sets whether drawing algorithm considers the text
    * string in list item as unicode text string displayable on the screen, or as 
    * string representation of an index to icon array.
    *
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetGraphicsSubCellL(TInt aSubCellIndex, TBool aIsGraphics);

    /**
    * SubCellRightSeparatorStyle queries whether vertical line is drawn to the
    * right side of the cell.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return style of pen used to draw line for right side of the cell
    */
    IMPORT_C CGraphicsContext::TPenStyle SubCellRightSeparatorStyle(TInt aColumn) const;
    /**
    * SetSubCellRightSeparatorStyleL() sets whether vertical line is drawn to the
    * right side of the cell.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetSubCellRightSeparatorStyleL(TInt aSubCell, CGraphicsContext::TPenStyle aStyle);

    /**
    * SubCellTextClipGap queries the amount of pixels text margins is grown if
    * it is truncated. This is usually very small number; used to make the layout
    * look more balanced when text is truncated. (the glyph used for truncation
    * is almost empty and on narrow text elements, it looks odd if the truncated
    * text element is exactly same size as non-truncated version.)
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return text and background colours in different situations
    */
    IMPORT_C TInt SubCellTextClipGap(TInt aSubCellIndex) const;
    /**
    * SetSubCellTextClipGapL() sets the amount of pixels truncation grows a text element.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetSubCellTextClipGapL(TInt aSubCellIndex, TInt aSize);

    /**
    * SkinEnabled queries whether skins are enabled on this list.
    * @since 2.0
    * @return ETrue = enabled, EFalse = disabled
    */
    IMPORT_C TBool SkinEnabled() const;
    /**
    * SetSkinEnabledL() sets whether skins are enabled on this list.
    * The default value is determined from global setting from CAknAppUi.
    * @since 2.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetSkinEnabledL(TBool aEnabled);

    /**
    * NumberCell queries whether the cell is used for numbers.
    * @since 2.0
    * @return ETrue = enabled, EFalse = disabled
    */
    IMPORT_C TBool SubCellIsNumberCell(TInt aSubCellIndex) const;
    /**
    * SetNumberCellL() sets whether the cell is used for numbers
    * @since 2.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aIsNumberCell new value for the flag
    * @return None
    */
    IMPORT_C void SetNumberCellL(TInt aSubCellIndex, TBool aIsNumberCell);

    /**
    * IconArray queries the icon array used when drawing bitmaps
    * for the listbox items. 
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return modifiable icon array
    */
    IMPORT_C CArrayPtr<CGulIcon>* IconArray() const;
    /**
    * SetIconArrayL() sets the icon array used when drawing bitmaps.
    * The array can be modified (no need to call this method when modifying),
    * even in MdcaPoint() or MdcaCount() methods of MDesCArray. See also
    * CTextListBoxModel::SetItemTextArray().
    * 
    * The most common way to crash a listbox is by forgetting to
    * call this method, or the list item string for graphics
    * cell is not an index of a bitmap.
    *
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aColors text and background colours
    * @return None
    */
    IMPORT_C void SetIconArrayL(CArrayPtr<CGulIcon>* aArray);
    IMPORT_C void SetIconArray(CArrayPtr<CGulIcon>* aArray);

    /**
    * Font access method based on the list item properties.
    * @since 0.0
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return font based on item properties
    */
    IMPORT_C CFont* Font(const TListItemProperties& aItemProperties,
                   TInt aSubCellIndex) const;
    
    /**
    * From CListBoxData Draw() is the most important method in CEikFormattedCellListBoxData.
    * This is the only method that needs to be implemented in this class and it draws the whole list
    * item.
    * @since 0.0
    * @param aProperties Properties attached to the list item
    * @param aGc Graphics context used for drawing the list item
    * @param aText a text string describing the list item cells
    * @param aRect the area of the screen for the whole list item
    * @param aHighlight whether the list item is selected
    * @param aColors the colours used for drawing the item
    * @return None.
    */
    IMPORT_C virtual void Draw(TListItemProperties aProperties, CWindowGc& aGc,const TDesC* aText,const TRect& aRect,TBool aHighlight, const TColors& aColors) const;

    IMPORT_C TBool UseSubCellColors(TInt aSubCell) const;

   /**
    * Ability for a skin subsystem to access Mop chain through current listbox control.
    * @since 2.0
    * @return current listbox instance or NULL.
    */
    IMPORT_C CCoeControl *Control() const;
   /**
    * Ability for a skin subsystem to access Mop chain through current listbox control.
    * @since 2.0
    * @param aControl current listbox instance or NULL.
    */
    IMPORT_C void SetControl(CCoeControl *aControlOrNull);
   /**
    * Access to the background context of the listbox.
    * @since 2.0
    * @return Skin background context
    */
    IMPORT_C MAknsControlContext* SkinBackgroundContext() const;
    /**
     * Modify properties of the skin context (background)
     * @since 2.0
     * @param aId skin background identifier
     * @param aRect skin background rectangle
     */
    IMPORT_C void SetBackgroundSkinStyle(const TAknsItemID *aId, const TRect &aRect);
    
    /**
    * Modify properties of the skin context (AB-column)
    * @since 2.0
    * @param aId skin background identifier
    * @param aTileRect skin background area from LAF
    */
    IMPORT_C void SetSkinStyle(const TAknsItemID *aId, const TRect &aTileRect);
    /**
    * Modify position of the parent for list default context
    * @since 2.0
    * @param aId skin background identifier
    * @param aTileRect skin background area from LAF
    */
    IMPORT_C void SetSkinParentPos(const TPoint &aPos);
   /**
    * Modify properties of the skin context (list ending)
    * @since 2.0
    * @param aId list ending skin background identifier
    * @param aRect list ending background area from LAF
    */
    IMPORT_C void SetListEndSkinStyle(const TAknsItemID *listEndId, const TRect &aRect);
    IMPORT_C TBool RespectFocus() const;
    IMPORT_C void SetRespectFocus(TBool aBool);

    /**
     * Set list higlight skin style
     * @since 2.0
     * @param aFrameId the id for the frame
     * @param aFrameCenterID the id for the frame center
     */
    IMPORT_C void SetSkinHighlightFrame(const TAknsItemID *aFrameId, const TAknsItemID *aFrameCenterId);
    /**
     * Set popup skin style
     * @since 2.0
     * @param aFrameId the id for the frame
     * @param aFrameCenterID the id for the frame center
     */
    IMPORT_C void SetSkinPopupFrame(const TAknsItemID *aFrameId, const TAknsItemID *aFrameCenterId);
    /**
     * Set popup skin frame position
     * @since 2.0
     * @param aOuterRect outer position of the frame
     * @param aInnerRect inner position of the frame
     */
    IMPORT_C void SetSkinPopupFramePosition(const TRect &aOuterRect, const TRect &aInnerRect);

    /**
     * Enable or disable logical to visual reordering in listbox data text drawing.
     * By default, it is enabled. This has any effect only when bidirectional text
     * is rendered.
     *
     * If you convert text to visual order prior to passing it to the listbox
     * (for example by wrapping text to lines with methods in AknBidiTextUtils),
     * then you should disable conversion in listbox by calling this method.
     *
     * @since 2.0
     * @param aUseConversion enable or disable conversion
     */
    IMPORT_C void UseLogicalToVisualConversion( TBool aUseConversion );

    /**
    * Enables or disables marquee.
    * @param aEnable ETrue = On, EFalse = Off
    */
    IMPORT_C void EnableMarqueeL(TBool aEnable);
    
    /**
    * Determines if marquee is on.
    * 
    */
    IMPORT_C const TBool IsMarqueeOn();

    /**
    * Creates pictograph interface.
    * Only effective in Japanese variant.
    * Called by the listbox.
    */
    void CreatePictographInterfaceL();

    /**
    * Creates marquee control.
    * Called by the listbox.
    */
    void CreateMarqueeControlL();

    /**
    * Resets the marquee animation data
    * 
    */
    void ResetMarquee();

    /**
    * Gets the current list item index that is/was drawn by marquee
    * 
    */
    TInt CurrentMarqueeItemIndex();
    
    /**
    * Sets the current list item index that was drawn by marquee
    * 
    */
    void SetCurrentMarqueeItemIndex(TInt aIndex);

    /**
    * Sets the current list item index (not for marquee)
    * @since 2.6
    * @param aIndex
    */
    void SetCurrentItemIndex(TInt aIndex);

    /**
    * SetSubCellFontForRowL() sets the font attached to the cell for each row separately.
    * @since 2.6
    * @param aRowIndex row, which subcells are to be changed
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @param aFont font to be used
    * @return None
    */
    IMPORT_C void SetSubCellFontForRowL(TInt aRowIndex, TInt aSubCellIndex, const CFont* aFont);

    /**
    * RowAndSubCellFont queries font attached to the row and cell.
    * @since 2.6
    * @param aRow index number of the row
    * @param aSubCellIndex index number (usually 0..6) of the subcell
    * @return font handle
    */
    IMPORT_C const CFont* RowAndSubCellFont(TInt aRow,TInt aSubCellIndex) const;

    /**
    * Enables / disables transparency effect, ie. does the listbox draw it's own background or not.
    * @param aDrawBackground  EFalse enables transparency
    */ 
    void SetDrawBackground(const TBool aDrawBackground);

    /**
    * Is the listbox drawing the background itself or not (= "transparency")
    */ 
    const TBool IsBackgroundDrawingEnabled() const;


	/**
	* Sets position of listbox line
	*/
	IMPORT_C void SetSeparatorLinePosition(TAknSeparatorLinePosition aPosition);

	/**
	* Gives out separator line position
	*/
	IMPORT_C TAknSeparatorLinePosition SeparatorLinePosition() const;

	/**
	 * Gives out layout data needed for separator lines drawing
	 */
	IMPORT_C CAknLayoutData *LayoutData() const;

private:
    // next methods are only used inside the drawing algorithm.
    // The set methods are also const because they do not change observable behavior of the system.
    TSize SubCellRealSize(TInt aSubCellIndex) const;
    void SetSubCellRealSize(TInt aSubCellIndex, TSize aRealSize) const;
    //
    TSize SubCellRealTextSize(TInt aSubCellIndex) const;
    void SetSubCellRealTextSize(TInt aSubCellIndex, TSize aRealSize) const;
    

    struct SSubCell
        {
        SSubCell() { }
        TInt iSubCell; // Must be first entry
        
        TInt iWidth;
        TMargins iMargin;
        const CFont* iBaseFont;
        TInt iActualFontIndex;
        TBool iGraphics;
        TBool iTransparent;
        TBool iNotAlwaysDrawn;
        CGraphicsContext::TTextAlign iAlign;
        CGraphicsContext::TPenStyle iRightSeparatorStyle;
        
        TPoint iPosition;
        TInt iBaseline;
        TSize iSize;

        TBool iUseSubCellColors; // this is set if someone calls SetSubCellColorsL()
        TColors iColors;
        TInt iTextClipGap;

        TBool iNumberCell;
        // the next ones change during drawing algorithm
        __MUTABLE TSize iRealSize;
        __MUTABLE TSize iRealTextSize;
        };
protected:
    IMPORT_C CFormattedCellListBoxData();
    IMPORT_C void ConstructLD();

        /**
        * DrawFormatted() is  the main drawing algorithm used for drawing
        * Series60 list item. Draw() method should call this method after
        * clearing the list item area and drawing the highlight.
        * @since 0.0
        * @param aProperties Properties attached to the list item
        * @param aGc Graphics context used for drawing the list item
        * @param aText a text string describing the list item cells
        * @param aRect the area of the screen for the whole list item
        * @param aHighlight whether the list item is selected
        * @param aColors the colours used for drawing the item
        * @return None.
        */
    IMPORT_C void DrawFormatted(TListItemProperties aProperties, CWindowGc& aGc,const TDesC* aText,const TRect& aRect,TBool aHighlight, const TColors& aColors) const;

public:
    /**
    * Customizes marquee default behaviour. 
    * Use this before enabling marquee ( EnableMarqueeL() ), otherwise 
    * marquee behaviour will change during animation.
    * @since 2.8
    * @param aLoops Max number of loops to be executed (default 1)
    * @param aScrollAmount The amount of pixels scrolled per frame (default 6)
    * @param aScrollDelay The delay between each loop (default 1000000ms)
    * @param aInterval The interval of frame updates
    */
    IMPORT_C void SetMarqueeParams(const TInt aLoops, const TInt aScrollAmount, 
                                    const TInt aScrollDelay, const TInt aInterval);


protected: // non-exported!
    CFormattedCellListBoxDataExtension *Extension();
    const CFormattedCellListBoxDataExtension *Extension() const;
public:
    void DrawDefaultHighlight(CWindowGc &aGc, const TRect &aItemRect, TBool aHighlight) const;
    void DrawSettingHighlight(CWindowGc &aGc, const TRect &aItemRect, TBool aHighlight) const;
    void DrawPopupHighlight(CWindowGc &aGc, const TRect &aItemRect, TBool aHighlight) const;
    void DrawPopupFrame(CWindowGc &aGc) const;
    // Informs drawing routine not to use logical-to-visual conversion
    // in these subcells.
    void SetWordWrappedSubcellIndices( TInt aFirstIndex, TInt aSecondIndex );
    IMPORT_C void SetSubCellIconSize(TInt aIndex, TSize aSize);
    TSize GetSubCellIconSize(TInt aIndex);


private:
    const TColors &Colors(TInt aItemIndex, TInt aSubCell) const;
    TInt LastSubCell() const;
    void AddSubCellL(TInt aSubCell);
    SSubCell& At(TInt aArrayIndex);
    const SSubCell& At(TInt aArrayIndex) const;
    TInt FindSubCellIndex(TInt& aArrayIndex,TInt aSubCell) const;
    void FindSubCellIndexOrAddL(TInt& aArrayIndex,TInt aSubCell);
    TInt AddActualFontL(const CFont* aBaseFont);

private:
    CArrayFix<SSubCell>* iSubCellArray;
    CArrayPtr<CGulIcon>* iIconArray;
    friend class CFormattedCellListBoxItemDrawer; // this is for "lastsubcell" -access.
    TColors defaultcolors;
    CFormattedCellListBoxDataExtension *iExtension; 
    };

/**
*  CSettingItemEditingListBoxData draws list items for setting page
* Special feature of this class is the rectangular style of highlight used in settings
*
*  @lib avkon
*  @since 0.0
*/
class CSettingItemEditingListBoxData : public CFormattedCellListBoxData
    {
public:
    IMPORT_C static CSettingItemEditingListBoxData* NewL();
    IMPORT_C virtual void Draw(TListItemProperties aProperties,
                   CWindowGc& aGc,
                   const TDesC* aText,
                   const TRect& aRect,
                   TBool aHighlight,
                   const TColors& aColors) const;
    };

/**
*  CSettingItemEditingListBoxData draws list items for form popup fields
* Special feature of this class is the rectangular style of highlight used in popup fields.
*
*  @lib avkon
*  @since 0.0
*/
class CFormGraphicListBoxData : public CFormattedCellListBoxData
    {
public:
    IMPORT_C static CFormGraphicListBoxData* NewL();
    IMPORT_C virtual void Draw(TListItemProperties aProperties,
                   CWindowGc& aGc,
                   const TDesC* aText,
                   const TRect& aRect,
                   TBool aHighlight,
                   const TColors& aColors) const;
    };


/**
*  CPopupFormattedListBoxData draws list items for popup windows
* Special feature of this class is the narrower style of highlight used in popups.
*
*  @lib avkon
*  @since 0.0
*/
class CPopupFormattedListBoxData : public CFormattedCellListBoxData
    {
public:
    IMPORT_C static CPopupFormattedListBoxData* NewL();
    IMPORT_C virtual void Draw(TListItemProperties aProperties,
                   CWindowGc& aGc,
                   const TDesC* aText,
                   const TRect& aRect,
                   TBool aHighlight,
                   const TColors& aColors) const;
    };

/**
*  CPopupFormattedListBoxData draws list items for grids
* Special feature of this class is the rectangular highlight used in grids.
*
*  @lib avkon
*  @since 0.0
*/
class CFormattedCellGridData : public CFormattedCellListBoxData
    {
public:
    IMPORT_C static CFormattedCellGridData* NewL();

    IMPORT_C virtual void Draw(TListItemProperties aProperties,
                   CWindowGc& aGc,
                   const TDesC* aText,
                   const TRect& aRect,
                   TBool aHighlight,
                   const TColors& aColors) const;
    };

#endif



