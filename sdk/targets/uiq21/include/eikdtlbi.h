// EIKDTLBI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDTLBI_H__)
#define __EIKDTLBI_H__

#if !defined(__EIKHLBI_H__)
#include <eikhlbi.h>
#endif

class CDirectoryTreeListBoxModel;
class CFont;
class CGulIcon;

class CDirectoryTreeListItemDrawer : public CHierarchicalListItemDrawer
	{
public:
	IMPORT_C CDirectoryTreeListItemDrawer(CDirectoryTreeListBoxModel* aModel,const CFont* aFont,
											CArrayPtr<CGulIcon>* aIconArray);
private: // from CHierarchicalListItemDrawer
	CGulIcon* ItemIcon(TInt aItemIndex) const;
private: // from CListItemDrawer
	TAny* Reserved_1();
	};

#endif
