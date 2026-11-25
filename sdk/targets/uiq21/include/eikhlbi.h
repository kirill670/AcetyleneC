// EIKHLBI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKHLBI_H__)
#define __EIKHLBI_H__

#include <eiklbi.h>

class CHierarchicalListBoxModel;
class CFont;
class CGulIcon;

class CHierarchicalListItemDrawer : public CListItemDrawer
	{
public:
	IMPORT_C ~CHierarchicalListItemDrawer();
	IMPORT_C void SetIconArray(CArrayPtr<CGulIcon>* aArray);
	IMPORT_C TInt ItemIconWidthInPixels(TInt aItemIndex) const;
public: // from CListItemDrawer
	IMPORT_C void DrawActualItem(TInt aItemIndex,const TRect& aActualItemRect,TBool aItemIsCurrent,TBool aViewIsEmphasized,TBool aViewIsDimmed,TBool aItemIsSelected) const;
	IMPORT_C TInt ItemWidthInPixels(TInt aItemIndex) const;
protected:
	IMPORT_C CHierarchicalListItemDrawer(CHierarchicalListBoxModel* aModel,const CFont* aFont,
											CArrayPtr<CGulIcon>* aIconArray);
	IMPORT_C virtual void DrawItemIcon(TInt aItemIndex,TRect& aActualItemRect,TBool aItemIsEmphasizedAndCurrent) const;
	IMPORT_C virtual void DrawItemText(TInt aItemIndex, const TRect& aItemTextRect) const;
	virtual CGulIcon* ItemIcon(TInt aItemIndex) const=0;
	IMPORT_C virtual TSize ItemIconSize() const;
	IMPORT_C CHierarchicalListBoxModel* HlModel() const;
private:
	IMPORT_C TAny* Reserved_1();
protected:
	CHierarchicalListBoxModel* iModel;
	const CFont* iFont;
	CArrayPtr<CGulIcon>* iIconArray;
private:
	TInt iSpare;
	};

#endif
