/*
* ==============================================================================
*  Name        : eikhlbm.h
*  Part of     : CKON
*  Interface   : Hierarchical Listbox API
*  Description : Hierarchical Listbox data model and list item classes.
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

#ifndef EIKHLBM_H
#define EIKHLBM_H

// INCLUDES
#include <bamdesca.h>
#include <eiklbm.h>


// DATA TYPES
/** when used as the item index parameter in 
 * <code>CHierarchicalListBoxModel::AddItemL</code>, this value causes the new
 * item to be inserted as the first of its parent's children
 */
const TInt KEikHierListInsertAsFirstSibling=-2;

// CLASS DECLARATIONS

/**
 * The <code>MHierarchicalListExpansionObserver</code> class specifies an 
 * interface through which the asynchronous expansion of a hierarchy can be 
 * observed.  
 *  
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class MHierarchicalListExpansionObserver
    {
public:
    // New methods
        /**
        * Updates the hierarchy for the specified list item.
        *
        * @param aItemIndex The list item for which the hierarchy is updated
        * @remarks This method is used to recalculate the position of the 
        * current item in the hierarchy after expansion so that, for example,
        * the scrollbar position can be adjusted
        * @see
        */
    virtual void UpdateHierarchyL(TInt aItemIndex)=0;
    };

/**
 * The <code>MHierarchicalListItemObserver</code> class specifies an interface 
 * through which the expansion or collapse of an item can be observed. This 
 * is not related to the <code>MHierarchicalListExpansionObserver</code> class.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class MHierarchicalListItemObserver
    {
public:
    /**
     * The enumeration <code>TEvent</code> defines the different kind of events 
     * that can happen. More events may be added in the future, so clients
     * must be able to deal with any values, for example, by putting a default 
     * case in their switch statements.
     */
    enum TEvent
        {
        /** the item has been collapsed */
        EItemCollapsed = 1,
        /** the item has been expanded */
        EItemExpanded = 2
        };

public:
    /**
     * This method is called when an item is updated. This method should not
     * attempt to modify the hierarchy. It should consider it as read-only.
     *
     * @param aItemIndex The index of the item that has been updated
     * @param aEvent The operation that has been performed on the item
     * @remarks
     * @see
     */
    virtual void ItemUpdated(TInt aItemIndex, TEvent aEvent) = 0;
    };

/**
 * The <code>CHierListItem</code> class provides an item in a hierarchical 
 * list model. 
 * <code>CHierListItem</code> objects are owned by an instance of 
 * <code>CHierarchicalListBoxModel</code> and are created and destroyed
 * throughout the lifetime of the <code>CHierarchicalListBoxModel</code>.
 *  
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class CHierListItem : public CBase
    {
public:
    /** 
     * The enumeration <code>TFlags</code> provides flags describing the item 
     * state and whether it has siblings or children. 
     */
    enum TFlags
        {
        /** the item is expanded and is displaying its children (if applicable) */
        EExpanded           =0x01,
        /** the item has other items following it at the same hierarchical level */
        EHasFurtherSibling  =0x02,
        /** the item has children */
        EHasChildren        =0x04,
        };
public:
    // Constructors and destructor

        /**
        * The object constructor. 
        *
        * @param aFlags Flags for the new object. These are from the 
        *               <code>TFlags</code> enumeration
        * @remarks The caller of this method must also set the level of the 
        *          newly created item using <code>SetLevel()</code>. It is 
        *          recommended that items be created and added to the list 
        *          using <code>CHierarchicalListBoxModel::AddItemL()</code> as
        *          this also handles insertion into the list
        * @see <code>CHierListItem::SetLevel()</code>
        * @see <code>CHierarchicalListBoxModel::AddItemL()</code>
        */
    IMPORT_C CHierListItem(TInt16 aFlags);

        /**
        * The object destructor.
        */

    IMPORT_C ~CHierListItem();

    // New methods
        /**
        * Sets this item's text by copying the descriptor that is passed in.
        *
        * @param aText The new value for the text of the item
        * @return 
        * @remarks 
        * @see SetLevel()
        */
        IMPORT_C void SetTextL(const TDesC& aText);
    
        /**
        * Gets this item's text.
        *
        * @return the item's text
        * @remarks
        * @see
        */
        inline TDesC* Text() const;
    
        /**
        * Sets the item's level. An item's level represents its depth within 
        * the hierarchy.
        * The highest (root) level is level 0, which means that the item has no 
        * parent. The level of an item's children is one higher than that 
        * of the parent.
        *
        * @param aLevel The new level for this item
        * @remarks If this method is used to change an item's level rather than
        *          to set it for the first time, it is also necessary to change 
        *          the level of any child items. In addition, it may be 
        *          necessary to change the setting of the 
        *          <code>EHasFurtherSibling</code> field of 
        *          <code>CHierListItem::TFlags</code> for any other items at 
        *          both the old and new levels and the <code>EHasChildren</code>
        *          fields for the previous and new parents.
        *          If the list's hierarchy is made inconsistent due to errors 
        *          in any of these, the results are unpredictable but can cause
        *          panics or the disappearance of items from the display
        * @see CHierListItem::TFlags
        */
        inline void SetLevel(TInt16 aLevel);
    
        /**
        * Gets the item's level. An item's level represents its depth within 
        * the hierarchy.
        * The highest (root) level is level 0, which means that the item has no 
        * parent. The level of an item's children is one higher than that 
        * of the parent.
        *
        * @return this item's level
        * @remarks
        * @see
        */
        inline TInt Level() const;
        
        /**
        * Sets this item's parent.
        *
        * @param aParent The item to record as this item's parent
        * @remarks If this method is used to set a parent of a different level
        *          to the original one, <code>SetLevel()</code> must also be 
        *          called to make the hierarchy consistent. Otherwise, the 
        *          results are unpredictable
        * @see
        */
        inline void SetParent(CHierListItem* aParent);
        
        /**
        * Gets this item's parent.
        * 
        * @return the item that is this item's parent
        * @remarks
        * @see
        */
        inline CHierListItem* Parent() const;
        
        /**
        * Sets the <code>EExpanded</code> field of <code>TFlags</code>. 
        * This method should be called on a <code>CHierListItem</code> by 
        * <code>CHierarchicalListBoxModel::ExpandItemL()</code> 
        * when the item has been expanded.
        *
        * @remarks This method only sets a flag - the display is not redrawn
        *          as a result of a call to this method
        * @see
        */
        inline void SetExpanded();
        
        /**
        * Sets the item as collapsed by clearing the <code>EExpanded</code> 
        * field of <code>TFlags</code>.
        *
        * @remarks This method only sets a flag - the display is not redrawn
        *          as a result of a call to this method
        * @see
        */
        inline void SetCollapsed();
        
        /**
        * Reports whether the item is expanded.
        *
        * @return <code>ETrue</code> if this item is expanded; 
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        inline TBool IsExpanded() const;
        
        /**
        * Sets that this item has further siblings.
        *
        * @remarks This method sets the field <code>TFlags::EHasFurtherSibling</code>.
        *          The flag field is used to calculate the number of items in 
        *          a level. All but the last item has this field set; the last 
        *          item has it cleared, which indicates that it is the last item
        * @see CHierListItem::TFlags
        */
        inline void SetHasFurtherSibling();
        
        /**
        * Sets that this item has no further siblings.
        *
        * @remarks This method clears the field <code>TFlags::EHasFurtherSibling</code>
        * @see CHierListItem::TFlags
        * @see SetHasFurtherSibling()
        */
        inline void SetHasNoFurtherSibling();
        
        /**
        * Reports whether this item has further siblings.
        *
        * @return <code>ETrue</code> if this item has further siblings; 
        *         <code>EFalse</code> if this is the last item in a level
        * @remarks
        * @see
        */
        inline TBool HasFurtherSibling() const;
        
        /**
        * Sets that this item has children.
        *
        * @remarks This method sets the field <code>TFlags::EHasChildren</code>.
        *          This flag field is used by an owning class, for example,
        *          <code>CDirectoryTreeListBoxModel</code>, to determine 
        *          whether an item should be indicated as expandable, for 
        *          example, by drawing a + before the icon
        * @see
        */
        inline void SetHasChildren();
        
        /**
        * Sets that this item has no children.
        *
        * @remarks This method clears the field <code>TFlags::EHasChildren</code>
        * @see
        */
        inline void SetHasNoChildren();
        
        /**
        * Reports whether this item has children.
        *
        * @return <code>ETrue</code> if this item has children; 
        *         <code>EFalse</code> if this item has no children
        * @remarks
        * @see
        */
        inline TBool HasChildren() const;
        

        private:     // Data
        HBufC* iText;
        CHierListItem* iParent;
        TInt16 iLevel;
        TInt16 iFlags;
    };

class CHierarchicalListBoxModelExtension;

/**
* This class must be sub-classed before use, as the base of any Listbox that 
* needs to display hierarchical data.
* The <code>CHierarchicalListBoxModel</code> class provides the data model for 
* a Hierarchical Listbox. <code>CHierarchicalListBoxModel</code> represents 
* all of the data displayed in the Hierarchical Listbox at one time. 
* The data that is modeled changes as items are collapsed or expanded. If an 
* item is expanded, more data is added to the model. 
* For a derived class, the modeled data is owned by this class as the parent.
* <b>Note</b>: The pure 
* virtual method <code>ExpandItemL()</code> must be implemented in each derived 
* class. 
*
* @lib eikctl.lib 
* @since Series90 1.0
*/
class CHierarchicalListBoxModel : public CBase, public MListBoxModel, public MDesCArray
    {
public:
    // Constructors and destructor
        /**
        * The object destructor.
        */
        IMPORT_C ~CHierarchicalListBoxModel();
    
    // New methods
        
        /**
        * Completes construction of a <code>CHierarchicalListBoxModel</code> 
        * object. 
        * 
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL();

        /**
        * This method expands an item in 
        * the list, adding items at the lower level to the model data.
        * Implementations should also set the status of the expanded item using
        * <code>CHierListItem::SetExpanded()</code>.
        *
        * @param aNodeToBeExpanded The index of the node to be expanded
        * @remarks
        * @see
        */
        virtual void ExpandItemL(TInt aNodeToBeExpanded) = 0;

        /**
        * Collapses an item in the list, deleting items at the lower level 
        * from the model data. Implementations should also set the status of 
        * the collapsed item using <code>CHierListItem::SetCollapsed()</code>.
        * The item itself is left in the list.
        *
        * @param aNodeToBeCollapsed The index of the item to be collapsed
        * @remarks
        * @see
        */
        IMPORT_C void CollapseItem(TInt aNodeToBeCollapsed);

        /**
        * Expands every item in the list. This uses <code>ExpandItemL()</code>.
        * The method is synchronous and some delay may be seen by the user when
        * processing a large list.
        *
        * @remarks <code>AsynchronousExpandAllItemsL()</code> performs the same
        *          task more slowly, but without the visible delay seen when 
        *          using this method
        * @see AsynchronousExpandAllItemsL()
        */
        IMPORT_C void ExpandAllItemsL();

        /**
        * Collapses all items. This collapses every item in the model, so that 
        * only top-level items remain.
        *
        * @remarks
        * @see
        */
        IMPORT_C void CollapseAllItems();

        /**
        * Gets a specified item.
        *
        * @param aIndex The index of the item to obtain
        * @return the item at that point in the list; or, if the index 
        *         specified was invalid, <code>NULL</code>
        * @remarks <code>aIndex</code> refers only to the position of the 
        *          item in the data model; it is not related to the level of 
        *          the item in the hierarchy. As items are expanded and 
        *          collapsed, their children are inserted into the array so 
        *          that an item's index may change independently of any of its 
        *          data
        * @see
        */
        IMPORT_C CHierListItem* Item(TInt aIndex) const;

        /**
        * Gets an item's text.
        *
        * @param aItemIndex The index of an item in the list. This value must 
        *                   be valid
        * @return the text of the specified item
        * @remarks
        * @see
        */
    IMPORT_C TPtrC ItemText(TInt aItemIndex) const;

        /**
        * Gets a pointer to this model's item array.
        *
        * @return a pointer to this model's item array
        * @remarks
        * @see
        */
        inline CArrayFix<CHierListItem*>* HierListArray() const;

        /**
        * Adds an item into the hierarchy list. The position and parent of the 
        * item are also specified.
        *
        * @param aListItem The item to be added
        * @param aParentIndex The index of the new item's parent; <code>-1</code>
        *                     indicates that the item has no parent
        * @param aIndexOfSiblingToInsertAfter The index of the item after which 
        *        the new item is to be inserted. If not negative, this item 
        *        must be a sibling of (that is, at the same level as) the item 
        *        to be added. An index of 
        *        <code>KEikHierListInsertAsFirstSibling</code> causes the item 
        *        to be inserted immediately after the parent as its first child. 
        *        If <code>aParentIndex</code> is <code>-1</code>, the default 
        *        value of <code>-1</code> causes the item to be added at the 
        *        end of the list, otherwise it is inserted as the first sibling
        *        immediately following the parent 
        * @remarks Items are inserted into the array, so that the indexes of 
        *          all of the following entries are changed. Indexes are 
        *          continuous throughout the array and do not reflect levels 
        *          so that a parent is followed by all of its children
        * @see
        */

        IMPORT_C void AddItemL(CHierListItem* aListItem,TInt aParentIndex,TInt aIndexOfSiblingToInsertAfter=-1);

        /**
        * Removes an item from the model. This deletes both the item and all of
        * its children.
        *
        * @param aItemIndex The index of the <code>CHierListItem</code> to 
        *                   remove
        * @remarks This method differs from <code>CollapseItem()</code> in that
        *          the indexed item is also removed from the list
        * @see
        */
        IMPORT_C void RemoveItem(TInt aItemIndex);

        /**
        * Removes all of the items in this model.
        *
        * @remarks
        * @see
        */
        IMPORT_C void RemoveAllItems();

        /**
        * Gets the index of the first child of the specified item.
        *
        * @param aItemIndex The index of the item
        * @return the index of the item's first child
        * @remarks
        * @see
        */
        IMPORT_C TInt FirstChildIndex(TInt aItemIndex) const;

        /**
        * Gets the index of the next sibling. An error is returned if there 
        * are no further items at the current level in the hierarchy (siblings).
        *
        * @param aItemIndex The index of the item for which the next sibling 
        *                   is required
        * @return the index of the next sibling, or, if it does not exist,
        *         <code>KErrNotFound</code>
        * @remarks
        * @see
        */
        IMPORT_C TInt NextSiblingIndex(TInt aItemIndex) const;

        /**
        * Gets the index of the previous sibling. An error is returned if 
        * there are no previous items at the current level in the hierarchy 
        * (siblings).
        *
        * @param aItemIndex The index of the item for which the previous 
        *                   sibling is required
        * @return the index of the previous sibling, or, if it does not exist,
        *         <code>KErrNotFound</code>
        * @remarks
        * @see
        */
        IMPORT_C TInt PreviousSiblingIndex(TInt aItemIndex) const;

        /** 
        * Gets the index of this item's parent. An error is returned if the 
        * specified item is at level 0, that is, if it has no 
        * parent.
        *
        * @param aItemIndex The index of the item for which the parent item is
        *                   required
        * @return the index of the parent item, or <code>KErrNotFound</code>
        *         if this item has no parent
        * @remarks
        * @see
        */
        IMPORT_C TInt ParentIndex(TInt aItemIndex) const;

        /**
        * Gets all of the children of the specified item. The children are stored
        * as an array of indices.
        *
        * @param aItemIndex The index of the item for which the children are 
        *                   required
        * @param aChildren An array containing all of the index values for the 
        *                  specified item's children
        * @remarks
        * @see
        */
        IMPORT_C void GetChildrenIndexesL(TInt aItemIndex,CArrayFix<TInt>* aChildren) const;

        /**
        * Removes all of the items in this model. This is the same as 
        * <code>RemoveAllItems()</code>.
        *
        * @remarks This method deletes all items from the array and frees
        *          the memory allocated to the array buffer
        * @see
        */
        IMPORT_C void Reset();

        /**
        * Expands a large hierarchy asynchronously. If an expansion observer 
        * has been set, it is notified after each node in the hierarchy has 
        * been expanded. The method uses a low priority active object to 
        * perform the expansion.
        *
        * @remarks <code>ExpandAllItemsL()</code> performs the same task more 
        *          quickly, but may result in a visible delay when processing
        *          a large list
        * @see
        */
        IMPORT_C void AsynchronousExpandAllItemsL();    // not available before release 5u

        /**
        * Sets the expansion observer. The assigned observer is notified after 
        * each node in the hierarchy has been expanded using 
        * <code>AsynchronousExpandAllItemsL()</code>.
        *
        * @param aObserver The expansion observer
        * @remarks
        * @see
        */
        IMPORT_C void SetExpansionObserver(MHierarchicalListExpansionObserver* aObserver);  // not available before release 5u
        /**
        * Sets the list item observer. The assigned observer is notified 
        * whenever an item is updated, that is, when it is expanded or 
        * collapsed.
        *
        * @param aObserver The list item observer
        * @remarks
        * @see MHierarchicalListExpansionObserver
        */
        IMPORT_C void SetListItemObserverL(MHierarchicalListItemObserver* aObserver);
        /**
        * Returns the list item observer. 
        *
        * @return the list item observer
        * @remarks
        * @see SetExpansionObserver()
        * @see MHierarchicalListExpansionObserver
        */
        IMPORT_C MHierarchicalListItemObserver* GetListItemObserver() const;

    private: // new in ER5U


        TInt ExpanderL();

    public: // new in ER5U
        /**
        * A callback method for an idle active object that does asynchronous 
        * hierarchy expansion.
        *
        * @param aThis The object to call back
        * @return <code>O</code> if the hierarchy is updated; otherwise 
        *         <code>1</code>
        * @remarks
        * @see
        */
    static TInt ExpanderCallBackL(TAny* aThis);
    
    public: // from MListBoxModel
        /**
        * Gets the number of items in the model.
        *
        * @return the number of items in the model
        * @remarks The number of items in the model changes as items are 
        *          expanded and collapsed
        * @see
        */
    IMPORT_C TInt NumberOfItems() const;
        /**
        * Gets an array of descriptors for all the items in the list.
        *
        * @return the array of descriptors
        * @remarks This method is a one-step way to access the descriptors for
        *          list items rather than using <code>HierListArray()</code> 
        *          and <code>ItemText()</code>
        * @see
        */
    IMPORT_C const MDesCArray* MatchableTextArray() const;

    protected:  // Methods
    // New Methods
        
        /**
        * Protected empty default constructor. Construction is completed by calling ConstructL().
        */
    IMPORT_C CHierarchicalListBoxModel();

private: // from MDesCArray
        /**
        * From MDesCArray Returns the number of descriptor elements in a descriptor array.
        * @return The number of descriptor elements in a descriptor array
        */
    IMPORT_C TInt MdcaCount() const;
    
        /**
        * From MDesCArray Indexes into a descriptor array.
        * @param aIndex The position of the descriptor element within a descriptor array. 
        *               The position is relative to zero; i.e. zero implies the first 
        *               descriptor element in a descriptor array
        * @return A 16 bit non-modifiable pointer descriptor representing the descriptor 
        *         element located at position aIndex within a descriptor array
        */
    IMPORT_C TPtrC MdcaPoint(TInt aIndex) const;

private: // from MListBoxModel

    IMPORT_C TAny* Reserved_1();

private:
    void CheckCreateExtensionL();

protected:     // Data
        /** The list of items maintained by this model. The number of items in this array 
          * will vary during the lifetime of a CEikHierarchicalListBox; see especially ExpandItemL() */
    CArrayFix<CHierListItem*>* iHierListArray;
private:     // Data
        CHierarchicalListBoxModelExtension* iExtension;
        CIdle* iExpander;
        TInt iAsyncExpandItemIndex;
        MHierarchicalListExpansionObserver* iExpansionObserver;
    };

inline TDesC* CHierListItem::Text() const
    { return (iText); }
inline TInt CHierListItem::Level() const
    { return (iLevel); }
inline CHierListItem* CHierListItem::Parent() const
    { return (iParent); }
inline void CHierListItem::SetLevel(TInt16 aLevel)
    { iLevel=aLevel; }
inline void CHierListItem::SetParent(CHierListItem* aParent)
    { iParent=aParent; }
inline void CHierListItem::SetExpanded()
    { iFlags|=EExpanded; }
inline void CHierListItem::SetCollapsed()
    { iFlags&=~EExpanded; }
inline TBool CHierListItem::IsExpanded() const
    { return iFlags&EExpanded; }
inline void CHierListItem::SetHasFurtherSibling()
    { iFlags|=EHasFurtherSibling; }
inline void CHierListItem::SetHasNoFurtherSibling()
    { iFlags&=~EHasFurtherSibling; }
inline TBool CHierListItem::HasFurtherSibling() const
    { return iFlags&EHasFurtherSibling; }
inline void CHierListItem::SetHasChildren()
    { iFlags|=EHasChildren; }
inline void CHierListItem::SetHasNoChildren()
    { iFlags&=~EHasChildren; }
inline TBool CHierListItem::HasChildren() const
    { return iFlags&EHasChildren; }

inline CArrayFix<CHierListItem*>* CHierarchicalListBoxModel::HierListArray() const
    { return iHierListArray; }

#endif      // EIKHLBM_H   
// End of File
