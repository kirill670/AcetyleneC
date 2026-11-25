/*
* =============================================================================
*  Name        : cknitlbx.h
*  Part of     : CKON
*  Interface   : Text Listbox API
*  Description : Listboxes for displaying text and icons.
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

#ifndef CKNITLBX_H
#define CKNITLBX_H


//** INCLUDES */
#include <eiklbi.h>
#include <eiktxlbm.h>
#include <eiklbx.h>
#include <gulicon.h>

/**
 * The <code>CTextAndIconListBoxModel</code> class implements a model for a 
 * Text and Icon Listbox. This is based on the <code>CTextListBoxModel</code>,
 * but as well as storing text data, it also stores icons.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CTextAndIconListBoxModel : public CTextListBoxModel
    {
public: //** Declarations */
    /**
     * The <code>TIconArrayOwnership</code> enumeration provides 
     * icon array ownership flags. These values are used to describe 
     * whether or not a Text and Icon Listbox model owns an icon array.
     */
    enum TIconArrayOwnership
        {
        /** the model owns the icon array and deletes it in its destructor */
        ELbmOwnsIconArray=0x01,
        /** the model does not own the icon array. The developer must maintain a pointer to it and free it explicitly before the application exits */
        ELbmDoesNotOwnIconArray=0x02
        };

public:
    // Constructors and destructor

    /**
     * The object destructor.
     */
    IMPORT_C ~CTextAndIconListBoxModel();

    //** New methods */

    /**
     * The second-phase object constructor.
     *
     * @param aItemTextArray A pointer to an array of item text
     * @param aOwnershipType The ownership of the item text array. The array
     *                       may be owned the model, or owned externally
     * @param aIconArray A pointer to an array of icons
     * @param aIconArrayOwnershipType The ownership of the icon array. The 
     *                                array may be owned by the model, or 
     *                                owned externally
     * @remarks
     * @see
     */
    IMPORT_C void ConstructL(MDesCArray* aItemTextArray,TListBoxModelItemArrayOwnership aOwnershipType,CArrayPtr<CGulIcon>* aIconArray,TIconArrayOwnership aIconArrayOwnershipType);

    /**
     * Return a pointer to the model's icon array
     *
     * @return a pointer to the model's icon array
     * @remarks
     * @see
     */
    IMPORT_C CArrayPtr<CGulIcon>* IconArray();

private: //** Data */
    TInt iFlags;
    CArrayPtr<CGulIcon>* iIconArray;
    };

/**
 * The <code>CTextAndIconListBoxItemDrawerBase</code> class implements a base 
 * class for an item drawer for a Text and Icon Listbox.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CTextAndIconListBoxItemDrawerBase : public CListItemDrawer
    {
public:
    //** Constructors and destructor */

    /**
     * The object destructor.
     */
    IMPORT_C ~CTextAndIconListBoxItemDrawerBase();

    //** New methods */

    /**
     * The  constructor of the object with its model and text display font.
     *
     * @param aTextListBoxModel The Text and Icon Listbox model
     * @param aFont The font used for item caption text
     * @remarks
     * @see
     */
    IMPORT_C CTextAndIconListBoxItemDrawerBase(MTextListBoxModel* aTextListBoxModel, const CFont* aFont);

    /**
     * Sets the maximum number of lines in the Text and Icon Listbox. The 
     * method guarantees that text of size <code>aMaxIconSize</code> is drawn 
     * correctly if the item size is at least the size returned by 
     * <code>MinimumCellSize()</code>.
     *
     * @param aMaxNumberOfLines The maximum number of lines in the Text and 
     *                          Icon Listbox
     * @remarks
     * @see
     */
    IMPORT_C void SetMaxNumberOfLines(TInt aMaxNumberOfLines);

    /**
     * Returns the maximum number of lines in a Text and Icon Listbox.
     *
     * @return the maximum number of lines in a Text and Icon Listbox
     * @remarks
     * @see
     */
    IMPORT_C TInt MaxNumberOfLines() const;

    /**
     * Returns the maximum icon size.
     *
     * @return the maximum icon size
     * @remarks
     * @see
     */
    IMPORT_C TSize MaximumIconSize() const;

    /**
     * Gets the maximum text width. <b>Note</b>: The maximum width is 
     * calculated based on the item cell size. The column width must be 
     * defined before calling the method.
     *
     * @return the maximum text width
     * @remarks
     * @see
     */
    IMPORT_C virtual TInt MaximumTextWidth() const=0;

    /**
     * Sets the brush pattern for the Text and Icon Listbox. This does 
     * not take ownership of the brush bitmap.
     *
     * @param aBitmap The brush pattern for the item drawer
     * @remarks
     * @see
     */
    IMPORT_C void UseBrushPattern(const CFbsBitmap* aBitmap);

    /**
     * Gets the Text and Icon Listbox's brush pattern.
     *
     * @return the brush pattern bitmap
     * @remarks
     * @see
     */
    IMPORT_C const CFbsBitmap* BrushPattern() const;

    /**
     * Sets the font.
     *
     * @param aFont The font used for drawing item text
     * @remarks
     * @see
     */
    IMPORT_C void SetFont(const CFont* aFont);

    /**
     * Gets the minimum cell size.
     *
     * @return the minimum cell size, in pixels
     * @remarks
     * @see
     */
    IMPORT_C virtual TSize MinimumCellSize() const=0;

    /**
     * Draws an item. This method is called by the view class to draw 
     * each item.
     *
     * @param aItemIndex The index of the item to draw
     * @param aItemRectPos The position at which to draw the item
     * @param aItemIsSelected <code>ETrue</code> to set that the item is selected;
     *                        <code>EFalse</code> otherwise
     * @param aItemIsCurrent <code>ETrue</code> to set that the item is current;
     *                       <code>EFalse</code> otherwise
     * @param aViewIsEmphasized <code>ETrue</code> to set that the item is 
     *                          emphasized; <code>EFalse</code> otherwise
     * @param aViewIsDimmed <code>ETrue</code> to set that the item is dimmed;
     *                      <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C virtual void DrawItem(TInt aItemIndex, TPoint aItemRectPos, TBool aItemIsSelected, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed) const;

    /**
     * Draws the Listbox item. This method is called by 
     * <code>DrawItem()</code> with the appropriate arguments. Its purpose 
     * is to draw an item into the graphics context at the specified 
     * rectangle.
     *
     * @param aItemIndex The index of the item to draw
     * @param aActualItemRect The rectangle in which to draw the item
     * @param aItemIsSelected <code>ETrue</code> to set that the item is selected;
     *                        <code>EFalse</code> otherwise
     * @param aItemIsCurrent <code>ETrue</code> to set that the item is current;
     *                       <code>EFalse</code> otherwise
     * @param aViewIsEmphasized <code>ETrue</code> to set that the item is 
     *                          emphasized; <code>EFalse</code> otherwise
     * @param aViewIsDimmed <code>ETrue</code> to set that the item is dimmed;
     *                      <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C virtual void DrawActualItem(TInt aItemIndex, const TRect& aActualItemRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed,TBool aItemIsSelected) const=0;

    /**
     * Clears a rectangle. The brush pattern is used if it has been defined.
     *
     * @param aRect The rectangle to be cleared
     * @remarks
     * @see
     */
    IMPORT_C void ClearRect(const TRect& aRect) const;

protected: //** Methods */
    //** New Methods */

    /**
     * Draws the item's text and text background into the given rectangle. This is called by DrawActualIem().
     * 
     * @param aItemIndex The index of the item.
     * @param aRect The rectangle in which the text is to be drawn.
     * @param aAlign The text alignment within the rectangle. This can be either CGraphicsContext::ECenter
     *               or CGraphicsContext::ELeft. ERight can be used but it's not tested and not guaranteed to work.
     * @return
     * @remarks
     * @see
     */
    IMPORT_C void DrawText(TInt aItemIndex, TRect& aRect,CGraphicsContext::TTextAlign aAlign) const;

    /**
     * Gets text box height in pixels.
     * 
     * @return text box height in pixels
     * @remarks
     * @see
     */
    IMPORT_C TInt TextBoxHeightInPixels() const;

    /**
     * Sets maximum icon size. Guarantees that icon of size aMaxIconSize is drawn 
     * properly if item size is at least the size returned by MinimumCellSize().
     * 
     * @param aMaxIconSize The maximum icon size.
     * @remarks
     * @see
     */
    IMPORT_C void SetMaximumIconSize(TSize aMaxIconSize);

private: //** Methods */
    CTextAndIconListBoxItemDrawerBase();

protected: //** Data */
    /** This text listbox's model. */
    MTextListBoxModel* iModel;
    /** The font used for drawing item text. */
    const CFont* iFont;

private: //** Data */
    TInt iMaxNumberOfLines;
    TSize iMaxIconSize;
    const CFbsBitmap* iBrushPattern;
    };

/**
 * The <code>CVerticalTextAndIconListBoxItemDrawer</code> class implements an 
 * item drawer to be used with the <code>CCknVerticalTextAndIconListBox</code>
 * class.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CVerticalTextAndIconListBoxItemDrawer : public CTextAndIconListBoxItemDrawerBase
    {
public:
    //** New methods */

    /**
     * The object constructor. The constructor uses the passed parameters to 
     * initialize the base class.
     *
     * @param aTextListBoxModel The Listbox model
     * @param aFont The font in which to draw the list item text
     * @remarks
     * @see
     */
    IMPORT_C CVerticalTextAndIconListBoxItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont);

    /**
     * Returns the minimum cell size required for the maximum icon size, and 
     * the maximum number of text lines. The maximum text width is 0 pixels 
     * with minimum cell size.
     *
     * @return the minimum cell size, in pixels
     * @remarks
     * @see
     */
    IMPORT_C virtual TSize MinimumCellSize() const;

    /**
     * Draws the actual item. This method is called by 
     * <code>CTextAndIconListBoxItemDrawerBase::DrawItem()</code> with 
     * appropriate arguments. Its purpose is to draw an item into the graphics 
     * context.
     *
     * @param aItemIndex The index of the item to draw
     * @param aActualItemRect The rectangle in which to draw the item
     * @param aItemIsSelected <code>ETrue</code> to set that the item is selected;
     *                        <code>EFalse</code> otherwise
     * @param aItemIsCurrent <code>ETrue</code> to set that the item is current;
     *                       <code>EFalse</code> otherwise
     * @param aViewIsEmphasized <code>ETrue</code> to set that the item is 
     *                          emphasized; <code>EFalse</code> otherwise
     * @param aViewIsDimmed <code>ETrue</code> to set that the item is dimmed;
     *                      <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C virtual void DrawActualItem(TInt aItemIndex, const TRect& aActualItemRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed,TBool aItemIsSelected) const;

    /**
     * Gets the maximum text width. <b>Note</b>: The maximum width is calculated 
     * based on the item cell size. The column width must be defined before 
     * calling the method.
     *
     * @return the maximum text width
     * @remarks
     * @see
     */
    IMPORT_C virtual TInt MaximumTextWidth() const;
    };

/**
 * The <code>CHorizontalTextAndIconListBoxItemDrawer</code> class implements 
 * an item drawer to be used with the <code>CCknHorizontalTextAndIconListBox</code>
 * class.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CHorizontalTextAndIconListBoxItemDrawer : public CTextAndIconListBoxItemDrawerBase
    {
public:
    //** New methods */

    /**
     * The object constructor. The constructor uses the passed parameters to 
     * initialize the base class, and sets the maximum icon size to be 
     * appropriate for small icons.
     *
     * @param aTextListBoxModel The Listbox model
     * @param aFont The font in which to draw the list item text
     * @remarks
     * @see
     */
    IMPORT_C CHorizontalTextAndIconListBoxItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont);

    /**
     * Gets the minimum cell size.
     *
     * @return the minimum cell size, in pixels
     * @remarks
     * @see
     */
    IMPORT_C virtual TSize MinimumCellSize() const;

    /**
     * Draws the Listbox item. This method is called by 
     * <code>DrawItem()</code> with the appropriate arguments. Its purpose 
     * is to draw an item into the graphics context at the specified 
     * rectangle.
     *
     * @param aItemIndex The index of the item to draw
     * @param aActualItemRect The rectangle in which to draw the item
     * @param aItemIsSelected <code>ETrue</code> to set that the item is selected;
     *                        <code>EFalse</code> otherwise
     * @param aItemIsCurrent <code>ETrue</code> to set that the item is current;
     *                       <code>EFalse</code> otherwise
     * @param aViewIsEmphasized <code>ETrue</code> to set that the item is 
     *                          emphasized; <code>EFalse</code> otherwise
     * @param aViewIsDimmed <code>ETrue</code> to set that the item is dimmed;
     *                      <code>EFalse</code> otherwise
     * @remarks
     * @see
     */
    IMPORT_C virtual void DrawActualItem(TInt aItemIndex, const TRect& aActualItemRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aViewIsDimmed,TBool aItemIsSelected) const;

    /**
     * Gets the maximum text width. <b>Note</b>: The maximum width is 
     * calculated based on the item cell size. The column width must be defined 
     * before calling the method.
     *
     * @return the maximum text width
     * @remarks
     * @see
     */
    IMPORT_C virtual TInt MaximumTextWidth() const;
    };

/**
 * The <code>CCknVerticalTextAndIconListBox</code> is based on the Snaking 
 * Listbox, but is capable of displaying icons next to the text.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknVerticalTextAndIconListBox : public CEikSnakingListBox
    {
public:
    //** Constructors and destructor */

    /**
     * The default object constructor.
     */
    IMPORT_C CCknVerticalTextAndIconListBox();

    //** New methods */

    /**
     * The second-phase constructor. Parameters.
     *
     * @param aParent A pointer to container control. The ownership of the parent
     *                control is not transferred
     * @param aFlags The Listbox flags
     * @param aModel A pointer to the Listbox model. If the pointer is 
     *               <code>NULL</code>, the model is created. The ownership of 
     *               the model depends on the <code>aFlags</code> parameter. 
     *               By default, the model is owned by the Listbox
     * @param aItemDrawer A pointer to the Listbox item drawer. If the pointer 
     *                    is <code>NULL</code>, the item drawer is created. 
     *                    The item drawer is owned by the Listbox
     * @remarks
     * @see
     */
    IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aFlags, CTextAndIconListBoxModel* aModel, CTextAndIconListBoxItemDrawerBase* aItemDrawer);

    /**
     * Sets the brush pattern for the Listbox. This does not take ownership of 
     * the brush bitmap.
     *
     * @param aBitmap The brush pattern bitmap
     * @remarks
     * @see
     */
    IMPORT_C void UseBrushPattern(const CFbsBitmap* aBitmap);

    /**
     * Draws the control. The control is redrawn because of the patterned brush.
     *
     * @param aRect The rectangle in which the control is to be drawn
     * @remarks
     * @see CCoeControl
     */
    IMPORT_C virtual void Draw(const TRect& aRect) const;

protected: //** Methods */

    //** New Methods */

    /**
     * Creates an item drawer instance.
     */
    IMPORT_C virtual void CreateItemDrawerL();

    /**
     * Creates view class instance.
     *
     * @return a pointer to the newly created view class instance
     * @remarks
     * @see
     */
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();

private: //** Data */
    const CFbsBitmap* iBrushPattern;
    };

/**
 * The <code>CCknHorizontalTextAndIconListBox</code> class provides the 
 * horizontal Text and Icon Listbox. This class creates a Listbox with items 
 * arranged horizontally. Each item consists of an icon and some text.
 *
 * @lib cknctl.lib
 * @since Series90 1.0
 */
class CCknHorizontalTextAndIconListBox : public CCknVerticalTextAndIconListBox
    {
public:
    //** Constructors and destructor */

    /**
     * The default object constructor.
     */
    IMPORT_C CCknHorizontalTextAndIconListBox();

    //** New methods */

    /**
     * Creates the item drawer instance. This is the object used to draw 
     * this class.
     *
     * @remarks
     * @see
     */
    IMPORT_C virtual void CreateItemDrawerL();
    };


#endif //** CKNITLBX_H */

//** End of File */
