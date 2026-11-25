// EIKHLBV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKHLBV_H__)
#define __EIKHLBV_H__

#if !defined(__EIKLBV_H__)
#include <eiklbv.h>
#endif

class CHierarchicalListBoxModel;

class CHierarchicalListBoxView : public CListBoxView
	{
public:
	IMPORT_C CHierarchicalListBoxView();
public: // from CListBoxView
	IMPORT_C void DrawItem(TInt aItemIndex) const;
	IMPORT_C void CalcDataWidth();
public:
	IMPORT_C void DrawItemWithoutLinks(TInt aItemIndex) const;
	IMPORT_C void DrawFromItem(TInt aIndexOfFirstItemToDraw);
	IMPORT_C void SetCurrentItemIndexOnly(TInt aIndex);
private: // from CListBoxView
	IMPORT_C TSize ItemSize(TInt aItemIndex) const;
	IMPORT_C TPoint ItemPos(TInt aItemIndex) const;
	IMPORT_C void VerticalMoveToItemL(TInt aTargetItemIndex, TSelectionMode aSelectionMode);
	IMPORT_C TAny* Reserved_1();
private:
	void ClearPreceedingItemRect(TInt aItemIndex) const;
	void DrawItemLinks(TInt aItemIndex) const;
	CHierarchicalListBoxModel* HlModel() const;
private:
	TInt iSpare;
	};

#endif
