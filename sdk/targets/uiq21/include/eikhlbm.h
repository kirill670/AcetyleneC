// EIKHLBM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKHLBM_H__)
#define __EIKHLBM_H__

#include <bamdesca.h>
#include <eiklbm.h>


/**
 * The MHierarchicalListExpansionObserver class specifies an interface through which
 * the asynchronous expansion of a hierarchy can be observed.
 *
 * @since ER5U
 */
class MHierarchicalListExpansionObserver
	{
public:
	virtual void UpdateHierarchyL(TInt aItemIndex)=0;
	};

class CHierListItem : public CBase
	{
public:
	enum TFlags
		{
		EExpanded			=0x01,
		EHasFurtherSibling	=0x02
		};
public:
	IMPORT_C CHierListItem(TInt16 aFlags);
	IMPORT_C ~CHierListItem();
	IMPORT_C void SetTextL(const TDesC& aText);
	inline TDesC* Text() const;
	inline void SetLevel(TInt16 aLevel);
	inline TInt Level() const;
	inline void SetParent(CHierListItem* aParent);
	inline CHierListItem* Parent() const;
	inline void SetExpanded();
	inline void SetCollapsed();
	inline TBool IsExpanded() const;
	inline void SetHasFurtherSibling();
	inline void SetHasNoFurtherSibling();
	inline TBool HasFurtherSibling() const;
private:
	HBufC* iText;
	CHierListItem* iParent;
	TInt16 iLevel;
	TInt16 iFlags;
	TInt iSpare;
	};

const TInt KEikHierListInsertAsFirstSibling=-2;

class CHierarchicalListBoxModel : public CBase, public MListBoxModel, public MDesCArray
	{
public:
	IMPORT_C ~CHierarchicalListBoxModel();
	IMPORT_C void ConstructL();
	virtual void ExpandItemL(TInt aNodeToBeExpanded) = 0;
	IMPORT_C void CollapseItem(TInt aNodeToBeCollapsed);
	IMPORT_C void ExpandAllItemsL();
	IMPORT_C void CollapseAllItems();
	IMPORT_C CHierListItem* Item(TInt aIndex) const;
	IMPORT_C TPtrC ItemText(TInt aItemIndex) const;
	inline CArrayFix<CHierListItem*>* HierListArray() const;
	IMPORT_C void AddItemL(CHierListItem* aListItem,TInt aParentIndex,TInt aIndexOfSiblingToInsertAfter=-1);
	IMPORT_C void RemoveItem(TInt aItemIndex);
	IMPORT_C void RemoveAllItems();
	IMPORT_C TInt FirstChildIndex(TInt aItemIndex) const;
	IMPORT_C TInt NextSiblingIndex(TInt aItemIndex) const;
	IMPORT_C TInt PreviousSiblingIndex(TInt aItemIndex) const;
	IMPORT_C TInt ParentIndex(TInt aItemIndex) const;
	IMPORT_C void GetChildrenIndexesL(TInt aItemIndex,CArrayFix<TInt>* aChildren) const;
	IMPORT_C void Reset();
	IMPORT_C void AsynchronousExpandAllItemsL();
	IMPORT_C void SetExpansionObserver(MHierarchicalListExpansionObserver* aObserver);
private:
	TInt ExpanderL();
public:
	static TInt ExpanderCallBackL(TAny* aThis);
public: // from MListBoxModel
	IMPORT_C TInt NumberOfItems() const;
	IMPORT_C const MDesCArray* MatchableTextArray() const;
protected:
	IMPORT_C CHierarchicalListBoxModel();
private: // from MDesCArray
	IMPORT_C TInt MdcaCount() const;
	IMPORT_C TPtrC MdcaPoint(TInt aIndex) const;
private: // from MListBoxModel
	IMPORT_C TAny* Reserved_1();
protected:
	CArrayFix<CHierListItem*>* iHierListArray;
private:
	TInt iSpare;
private:
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

inline CArrayFix<CHierListItem*>* CHierarchicalListBoxModel::HierListArray() const
	{ return iHierListArray; }

#endif
