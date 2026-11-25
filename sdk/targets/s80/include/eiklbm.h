/*
* ==============================================================================
*  Name        : eiklbm.h
*  Part of     : CKON
*  Interface   : Listbox API
*  Description : Listbox data model mixin class.
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

#ifndef EIKLBM_H
#define EIKLBM_H


// INCLUDES
#include <e32base.h>
#include <bamdesca.h>

// DATA TYPES

/**
 * The <code>TListBoxModelItemArrayOwnership</code> enumeration provides 
 * Listbox item array ownership flags. These values are used to describe 
 * whether or not a Listbox model owns an item array.
 */
enum TListBoxModelItemArrayOwnership
    {
    /** 
     * the Listbox model owns the item array and will delete it in its 
     * destructor 
     */
    ELbmOwnsItemArray,
    /** 
     * the model does not own the item array. The developer must maintain a 
     * pointer to it and free it explicitly before the application exits 
     */
    ELbmDoesNotOwnItemArray
    };

// FORWARD DECLARATIONS


// CLASS DECLARATIONS


/**
 * The <code>MListBoxModel</code> class provides the Listbox data model 
 * interface. This mixin protocol is implemented by all Listbox models. 
 * Listbox models provide information needed to display the required data in a
 * Listbox. When writing derived classes, this class should be implemented 
 * by anything providing data for display in a <code>CEikListBox</code>-derived
 * class. The very basic interface offered by <code>MListBoxModel</code> is 
 * usually expanded upon to provide more information for the specialized 
 * derived classes of <code>CEikListBox</code>. It is usual when deriving 
 * specialized Listboxes to subclass the Listbox class, its view classes, and 
 * its model together. 
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class MListBoxModel
    {

    public:
    // Constructors and destructor

       /**
        * The object destructor.
        */
        virtual ~MListBoxModel() {}


    // New methods
        
       /**
        * Gets the number of items in the Listbox.
        *
        * @return the number of items for the Listbox to display
        * @remarks
        * @see
        */
        virtual TInt NumberOfItems() const = 0;

       /**
        * Gets an array of strings used by the Listbox for matching user
        * key presses incrementally.
        *
        * @return an array of matchable strings
        * @remarks
        * @see
        */
        virtual const MDesCArray* MatchableTextArray() const = 0;

    private: //Methods
        virtual TAny* Reserved_1() = 0;
    };

/**
 * The <code>MTextListBoxModel</code> class provides the Text Listbox model 
 * interface. Text Listbox models provide the text of the items that are drawn 
 * by an associated <code>CTextListItemDrawer</code>. This interface is
 * implemented by <code>CTextListBoxModel</code>.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class MTextListBoxModel : public MListBoxModel
    {

    public:
    // Constructors and destructor

        /**
        * The empty virtual destructor.
        */
        virtual ~MTextListBoxModel() {}


    // New methods
        
       /**
        * Gets the item text for an item by its index.
        * This text, rather than the matcher string, is drawn by
        * <code>CTextListItemDrawer</code> objects.
        *
        * @param aItemIndex The index specifying an item
        * @return the text for that item
        * @remarks
        * @see
        */
        virtual TPtrC ItemText(TInt aItemIndex) const = 0;

    };


#endif      // EIKLBM_H   
            
// End of File
