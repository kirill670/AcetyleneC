// EIKLBM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__EIKLBM_H__)
#define __EIKLBM_H__  


#include <e32base.h>
#include <bamdesca.h>


/**
 * List box item array ownership flags.
 *
 * These values are used to describe whether or not a list box model owns
 * an item array.
 */
enum TListBoxModelItemArrayOwnership
	{
	/** The list box model owns the item array, and will delete it in its
	destructor. */
	ELbmOwnsItemArray,

	/** The model does not own the item array you must maintain a pointer to
	it and free it explicitly before your program exits. */
	ELbmDoesNotOwnItemArray
	};

/**
 *
 * List box data model interface.
 *
 * This mixin protocol is implemented by all list box models. List box
 * models provide information needed to display the required data in a
 * list box.Writing derived classes:This class should be implemented by
 * anything providing data for display in a
 * <code>CEikListBox</code>-derived class. The very basic interface
 * offered by <code>MListBoxModel</code> is usually expanded upon to
 * provide more information for the specialised subclasses of
 * <code>CEikListBox</code>. It is usual when deriving specialised list
 * boxes to subclass the list box class, its view classes and its model
 * together. See also:
 *
 * @since 6.0
 * @lib ""
 */
class MListBoxModel 
	{
public:
	/**
	 * Virtual destructor with an empty implementation.
	 */
	virtual ~MListBoxModel() {}

	/**
	 * Gets the number of items in the list box.
	 *
	 * @returns   "TInt"
	 *            Number of items for the list box to display.
	 */
	virtual TInt NumberOfItems() const = 0;

	/**
	 * Gets an array of strings used by the list box for matching user
	 * keypresses incrementally.
	 *
	 * @returns   "MDesCArray*"
	 *            An array of matchable strings.
	 */
	virtual const MDesCArray* MatchableTextArray() const = 0;
private:
	virtual TAny* Reserved_1() = 0;
	};

/**
 *
 * Text list box model interface.
 *
 * Text list box models provide the text of the items which are drawn by
 * an associated <code>CTextListItemDrawer</code>. This interface is
 * implemented by <code>CTextListBoxModel</code>.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class MTextListBoxModel : public MListBoxModel
	{
public:
	/**
	 * Empty virtual destructor.
	 */
	virtual ~MTextListBoxModel() {}

	/**
	 * Gets the item text for an item by its index.
	 *
	 * This text, rather than the matcher string, is drawn by
	 * <code>CTextListItemDrawer</code>s.
	 *
	 * @param     "TInt aItemIndex"
	 *            Index specifying an item.
	 * @returns   "TPtrC"
	 *            The text for that item.
	 */
	virtual TPtrC ItemText(TInt aItemIndex) const = 0;
	};


#endif
