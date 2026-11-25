/*
* =============================================================================
*  Name        : eikdtlbi.h
*  Part of     : CKON
*  Interface   : Tree Listbox API
*  Description : Directory tree listbox item drawer
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

#ifndef EIKDTLBI_H
#define EIKDTLBI_H

// INCLUDES
#include <eikhlbi.h>

// FORWARD DECLARATIONS
class CDirectoryTreeListBoxModel;
class CFont;
class CGulIcon;

// CLASS DECLARATIONS

/**
* Listbox item drawer class for the directory tree listbox.
* This class can be accessed through its corresponding 
* <code>CEikDirectoryTreeListBox</code>.
*
*  @lib eikfile.lib
*  @since Series90 1.0
*/
class CDirectoryTreeListItemDrawer : public CHierarchicalListItemDrawer
    {
public:
        /**
        * The default object constructor.
        *
        * @param aModel The model for this listbox
        * @param aFont The font that the text will be drawn in
        * @param aIconArray The icons to be displayed
        * @return
        * @remarks
        * @see
        */
    IMPORT_C CDirectoryTreeListItemDrawer(CDirectoryTreeListBoxModel* aModel,const CFont* aFont,
                                            CArrayPtr<CGulIcon>* aIconArray);

    protected:  // Methods
    // New Methods
        /**
        * Draws the text for the specified item, within a certain area.
        * @param aItemIndex The index of the item to be drawn.
        * @param aItemTextRect The area in which drawing is allowed.
        */
        void DrawItemText(TInt aItemIndex, const TRect& aItemTextRect) const;

    private: //Methods
        CGulIcon* ItemIcon(TInt aItemIndex) const;
        TAny* Reserved_1();
    };


#endif      // EIKDTLBI_H   
            
// End of File
