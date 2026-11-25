/*
* ==============================================================================
*  Name        : eikhlbv.h
*  Part of     : CKON
*  Interface   : Hierarchical Listbox API
*  Description : Hierarchical Listbox view.
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

#ifndef EIKHLBV_H
#define EIKHLBV_H

// INCLUDES
#include <eiklbv.h>

// FORWARD DECLARATIONS
class CHierarchicalListBoxModel;
class CGulIcon;

// CLASS DECLARATIONS

/**
*  The <code>CHierarchicalListBoxView</code> class provides a Hierarchical 
*  Listbox view. This is a specialization of the basic Listbox view class for 
*  Hierarchical Listboxes.  It must be sub-classed before use.
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CHierarchicalListBoxView : public CListBoxView
    {
    public:  // Declarations

    /** The anonymous enumeration provides Hierarchical Listbox view flags. */
    enum
        {
        /** shows if the item is collapsed or expanded */
        EShowExpandCollapseIndicators=1,
        };

    public:
    // Constructors and destructor
        /**
        * The default object constructor.
        */
    IMPORT_C CHierarchicalListBoxView();
        /**
        * The object destructor.
        */
    IMPORT_C ~CHierarchicalListBoxView();
public: // from CListBoxView

    // New methods
        
        /**
        * Draws an item with links. The links are the elements (lines and
        * indentation) that indicate the item's position in the hierarchy.
        *
        * @param aItemIndex The index of the item to draw
        * @remarks No expansion is performed as part of this method, though
        *          it may be called as part of the process of expansion. The 
        *          specified item is rendered on the display as a result of a 
        *          call to this method
        * @see
        */
    IMPORT_C void DrawItem(TInt aItemIndex) const;

        /**
        * Returns the width required to display the items in the list.  
        *
        * @remarks The width is calculated as the space required to display
        *          the longest item in the array, including its text, icon,
        *          and any indentation due to its level in the hierarchy
        * @see CListBoxView::CalcDataWidth()
        */
    IMPORT_C void CalcDataWidth();

public:
        /**
        * Sets the view flags.
        *
        * @param aFlags The view flags, for example, 
        *               <code>EShowExpandCollapseIndicators</code>
        * @remarks <code>EShowExpandCollapseIndicators</code> is a member of 
        *          an anonymous enumeration owned by this class
        * @see
        */
        IMPORT_C void SetHierViewFlags(TUint aFlags);

        /**
        * Sets the expanded or collapsed indication icons. This method 
        * overrides the default +/- indicators with developer-supplied icons.
        *
        * @param aPlus The icon to replace the + default icon
        * @param aMinus The icon to replace the - default icon
        * @remarks
        * @see
        */
        IMPORT_C void SetPlusMinusIndicatorBitmaps(CGulIcon* aPlus,CGulIcon* aMinus);

        /**
        * Sets the horizontal scrollbar so that the specified item is 
        * positioned horizontally, to be visible. 
        *
        * @param aItemIndex The item to be positioned
        * @return <code>ETrue</code> if the scrolling offset has changed; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool SetHScrollForItem(TInt aItemIndex);

        /**
        * Adjusts the horizontal scroll. If the data for all the items can be
        * displayed without scrolling, then the horizontal scrolling offset is
        * set to zero.
        *
        * @return <code>ETrue</code> if the scrolling offset has changed; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool AdjustHScroll();
public:
        /**
        * Draws an item without links. Links are the lines that show the 
        * data's hierarchical structure.
        *
        * @param aItemIndex The index of the item to draw
        * @remarks
        * @see
        */
        IMPORT_C void DrawItemWithoutLinks(TInt aItemIndex) const;

        /**
        * Draws the specified item and all visible items below it. This is a 
        * common requirement for a Hierarchical Listbox.
        *
        * @param aIndexOfFirstItemToDraw The index of the first item to draw
        * @remarks
        * @see
        */
        IMPORT_C void DrawFromItem(TInt aIndexOfFirstItemToDraw);

        /**
        * Sets the item with the specified index to be the current item. 
        *
        * @param aIndex The index of the item to make current
        * @remarks This method does nothing beyond setting the current item 
        *          index for future use. It does not redraw the display. It 
        *          does not check that the index is within the range. If it is 
        *          outside the range, no item is highlighted or selected
        *          on the next redraw
        * @see
        */
        IMPORT_C void SetCurrentItemIndexOnly(TInt aIndex);

private: // from CListBoxView
        /**
        * Gets the onscreen size of an item, in pixels. As implemented in 
        * <code>CListBoxView</code>, all items report the same size. 
        * The size returned may be larger than the width of the Hierarchical 
        * Listbox view, but will not be smaller.
        *
        * @param aItemIndex The index of an item
        * @return the size of the item
        */
        IMPORT_C TSize ItemSize(TInt aItemIndex) const;

        /**
        * Gets the on-screen position of an item.
        * @param aItemIndex Index of an item
        * @return Position of the item
        */
        IMPORT_C TPoint ItemPos(TInt aItemIndex) const;

        /**
        * Moves to the specified item, sets it as the current item and scrolls 
        * the display to make the item visible.
        * @param aTargetItemIndex The index of the item to which to move
        * @param aSelectionMode The selection mode
        */
        IMPORT_C void VerticalMoveToItemL(TInt aTargetItemIndex, TSelectionMode aSelectionMode);

        IMPORT_C TAny* Reserved_1();
private:

        TInt IndentPerLevel() const;
        TInt ExpandCollapseIndicatorSize() const;
        void ClearPreceedingItemRect(TInt aItemIndex) const;
        void DrawItemLinks(TInt aItemIndex) const;
        CHierarchicalListBoxModel* HlModel() const;

    private:     // Data
        TUint iHierViewFlags;
        CGulIcon* iPlus;
        CGulIcon* iMinus;

    };

#endif      // EIKHLBV_H   
// End of File
