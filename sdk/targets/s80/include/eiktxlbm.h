/*
* =============================================================================
*  Name        : eiktxlbm.h
*  Part of     : CKON
*  Interface   : Text Listbox API
*  Description : Text Listbox data.
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

#ifndef EIKTXLBM_H
#define EIKTXLBM_H

//** INCLUDES */
#include <eiklbm.h>

//** CLASS DECLARATIONS */

/**
 * The <code>CTextListBoxModel</code> class provides Text Listbox data.
 * Text Listbox models provide the text of the items that are drawn by an 
 * associated <code>CTextListItemDrawer</code>. The Text Listbox model
 * is responsible for handling the list item array and whether it owns
 * the item array.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class CTextListBoxModel : public CBase, public MTextListBoxModel
    {
public:
    //** Constructors and destructor */

    /**
     * The default object constructor.
     */
    IMPORT_C CTextListBoxModel();


    /**
     * The object destructor.
     */
    IMPORT_C virtual ~CTextListBoxModel();


    //** New methods */

    /**
     * Gets the number of text items in this Text Listbox model.
     *
     * @return the number of text items
     * @remarks
     * @see
     */
    IMPORT_C virtual TInt NumberOfItems() const;

    /**
     * Gets a text array of strings. For the Text Listbox model, these
     * strings are those that are displayed.
     * This method is used for incremental matching of typed characters.
     *
     * @return the text array for matching
     * @remarks
     * @see ItemText()
     */
    IMPORT_C virtual const MDesCArray* MatchableTextArray() const;

    /**
     * Gets the text to be displayed in the Text Listbox control for the 
     * specified item.
     *
     * @param aItemIndex The index of an item
     * @return the text string to be displayed
     * @remarks
     * @see
     */
    IMPORT_C virtual TPtrC ItemText(TInt aItemIndex) const;

    /**
     * Completes construction of a Text Listbox model object.
     *
     * @param aItemTextArray The item array
     * @param aOwnershipType Whether the Text Listbox model takes
     *                       ownership of the item array.
     *                       If <code>ELbmOwnsItemArray</code>, the Listbox 
     *                       model owns the item array and deletes it in its 
     *                       destructor. If <code>ELbmDoesNotOwnItemArray</code>, 
     *                       the model does not own the item array. The developer 
     *                       must maintain a pointer to it and free it 
     *                       explicitly before the application exits
     * @remarks By default the Text Listbox takes ownership of the item array
     * @see TListBoxModelItemArrayOwnership in eiklbm.h
     */
    IMPORT_C virtual void ConstructL(MDesCArray* aItemTextArray = NULL, TListBoxModelItemArrayOwnership aOwnershipType = ELbmOwnsItemArray);

    /**
     * Sets a new text item array.
     *
     * @param aItemTextArray The new item text array
     * @remarks
     * @see
     */
    IMPORT_C void SetItemTextArray(MDesCArray* aItemTextArray);

    /**
     * Sets the item array ownership type.
     *
     * @param aOwnershipType Whether the Text Listbox model takes
     *                       ownership of the item array.
     *                       If <code>ELbmOwnsItemArray</code>, the Listbox 
     *                       model owns the item array and deletes it in its 
     *                       destructor. If <code>ELbmDoesNotOwnItemArray</code>, 
     *                       the model does not own the item array. The developer 
     *                       must maintain a pointer to it and free it 
     *                       explicitly before the application exits
     * @remarks
     * @see TListBoxModelItemArrayOwnership in eiklbm.h
     */
    IMPORT_C void SetOwnershipType(TListBoxModelItemArrayOwnership aOwnershipType); 

    /**
     * Gets the text item array.
     *
     * @return a pointer to the text item array
     * @remarks
     * @see
     */
    IMPORT_C MDesCArray* ItemTextArray() const;

protected: //** Methods */
    //** New Methods */

    /**
     * Gets the item array ownership type.
     *
     * @return Item array ownership.
     */
    IMPORT_C TListBoxModelItemArrayOwnership ItemArrayOwnershipType() const;

private: //** Methods */
    IMPORT_C TAny* Reserved_1();

protected: //** Data */
    /** The array of text items modelled by this Text Listbox model. */
    MDesCArray* iItemTextArray;

private: //** Data */
    TListBoxModelItemArrayOwnership iItemArrayOwnershipType;
    };


#endif //** EIKTXLBM_H */

//** End of File */
