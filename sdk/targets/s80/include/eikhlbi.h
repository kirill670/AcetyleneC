/*
* ==============================================================================
*  Name        : eikhlbi.h
*  Part of     : CKON
*  Interface   : Hierarchical Listbox API
*  Description : Hierarchical Listbox item drawer
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

#ifndef EIKHLBI_H
#define EIKHLBI_H

// INCLUDES
#include <eiklbi.h>

// DATA TYPES
// FORWARD DECLARATIONS
class CHierarchicalListBoxModel;
class CFont;
class CGulIcon;

// CLASS DECLARATIONS
/**
*  The <code>CHierarchicalListItemDrawer</code> class provides a listbox item 
*  drawer for the <code>CEikHierarchicalListBox</code>. This class is derived 
*  from the standard listbox item drawer and contains functionality specific 
*  to drawing Hierarchical Listbox items. This class must be sub-classed before 
*  use.
*
*  @lib eikctl.lib 
*  @since Series90 1.0
*/
class CHierarchicalListItemDrawer : public CListItemDrawer
    {
    
    public:
        // Constructors and destructor
        
        /**
        * The object destructor.
        */
        IMPORT_C ~CHierarchicalListItemDrawer();
        
        // New methods
        /**
        * Sets the icon array. The icons are used to contain the graphics that
        * are displayed in graphical columns. 
        *
        * @param aArray The new bitmap array
        * @remarks  This method passes ownership of the icon list
        *           <code>aArray</code> to the 
        *           <code>CHierarchicalListItemDrawer</code> object, which 
        *           destroys the array when it is itself deleted
        * @see
        */
        IMPORT_C void SetIconArray(CArrayPtr<CGulIcon>* aArray);
        /**
        * Gets the width of an item, in pixels.
        *
        * @param aItemIndex The index of the item
        * @return the width of the specified item, in pixels
        * @remarks
        * @see
        */
        IMPORT_C TInt ItemIconWidthInPixels(TInt aItemIndex) const;
        
        /**
        * Draws the whole item.
        *
        * @param aItemIndex The index of the item to draw
        * @param aActualItemRect The rectangle to draw in
        * @param aItemIsCurrent <code>ETrue</code> if the item is current
        * @param aViewIsEmphasized <code>ETrue</code> if the view is emphasized
        * @param aViewIsDimmed This parameter is not used
        * @param aItemIsSelected <code>ETrue</code> if the item is selected
        * @remarks The parameter <code>aItemIsSelected</code> is redundant, 
        *          since in a Hierarchical Listbox there can only be one
        *          selected item at any time, which is therefore the current
        *          item.
        *          If an item is emphasized, it is drawn with a border but not
        *          highlighted
        * @see CListItemDrawer
        */
        IMPORT_C void DrawActualItem(TInt aItemIndex,const TRect& aActualItemRect,TBool aItemIsCurrent,TBool aViewIsEmphasized,TBool /*aViewIsDimmed*/,TBool aItemIsSelected) const;
        
        /**
        * Gets the width of an item, in pixels.
        *
        * @param aItemIndex The index of an item
        * @return the width of the specified item, in pixels
        * @remarks
        * @see
        */
        IMPORT_C TInt ItemWidthInPixels(TInt aItemIndex) const;
    
    
    protected:  // Methods
        // Constructor
        /**
        * Protected default constructor. The constructor is used by derived classes.
        * @param aModel The model to use
        * @param aFont The font to use
        * @param aIconArray An array of icons to use
        */  
        
    IMPORT_C CHierarchicalListItemDrawer(CHierarchicalListBoxModel* aModel,const CFont* aFont,
                                            CArrayPtr<CGulIcon>* aIconArray);
    // New Methods
        /**
        * Draws an item's icon.
        * @param aItemIndex Index of the item being drawn
        * @param aActualItemRect Rectangle enclosing the entire item to be drawn
        * @param aItemIsEmphasizedAndCurrent <code>ETrue</code> causes the background and text 
        *        for the item to be drawn as highlighted colours
        * <BR><B>Type of return value:</B> void
        */
    IMPORT_C virtual void DrawItemIcon(TInt aItemIndex,TRect& aActualItemRect,TBool aItemIsEmphasizedAndCurrent) const;
        /**
        * Draws an item's text.
        * @param aItemIndex Index of the item being drawn
        * @param aItemTextRect Rectangle enclosing the item's text
        * <BR><B>Type of return value:</B> void
        */
    IMPORT_C virtual void DrawItemText(TInt aItemIndex, const TRect& aItemTextRect) const;
        /**
        * Gets the icon for a specified item. This is a pure virtual function which 
        * must be implemented in all derived classes.
        * If an item is to be drawn without a bitmap, this function should return NULL. 
        * Unless <code>ItemIconSize()</code> is also overridden, bitmaps should be 
        * drawn from <code>iIconArray</code> as that array is used to determine the 
        * icon's on-screen size
        * @param aItemIndex Index of an item
        * @return An appropriate icon for the item, or NULL
        */
    virtual CGulIcon* ItemIcon(TInt aItemIndex) const=0;
        /**
        * Gets the icon size. This size is used to determine the space in which all icons will be drawn. 
        * The function assumes that all icons have the same size, which is equal to the first icon
        * @return Area in which to draw all bitmaps
        */
    IMPORT_C virtual TSize ItemIconSize() const;
        /**
        * Gets the model. 
        * @return A pointer to this drawer's model
        */
    IMPORT_C CHierarchicalListBoxModel* HlModel() const;

    private: //Methods

    IMPORT_C TAny* Reserved_1();
    protected:     // Data
        /** A pointer to the model. */
        CHierarchicalListBoxModel* iModel;
        /** Font used to draw item texts. */
        const CFont* iFont;
        /** Array of bitmaps to use to draw the items. */
        CArrayPtr<CGulIcon>* iIconArray;
    private:     // Data
    TInt iSpare;
    };

#endif      // EIKHLBI_H   
// End of File
