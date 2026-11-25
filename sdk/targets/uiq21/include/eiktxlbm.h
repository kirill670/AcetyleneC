// EIKTXLBM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__EIKTXLBM_H__)
#define __EIKTXLBM_H__  

#include <eiklbm.h>


/**
 *
 * Text list box data.
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CTextListBoxModel : public CBase, public MTextListBoxModel
	{
public:
	IMPORT_C CTextListBoxModel();
	IMPORT_C virtual ~CTextListBoxModel();
	IMPORT_C virtual TInt NumberOfItems() const;
	IMPORT_C virtual const MDesCArray* MatchableTextArray() const;
	IMPORT_C virtual TPtrC ItemText(TInt aItemIndex) const;
	IMPORT_C virtual void ConstructL(MDesCArray* aItemTextArray = NULL, TListBoxModelItemArrayOwnership aOwnershipType = ELbmOwnsItemArray);
	IMPORT_C void SetItemTextArray(MDesCArray* aItemTextArray);
	IMPORT_C void SetOwnershipType(TListBoxModelItemArrayOwnership aOwnershipType); 
	IMPORT_C MDesCArray* ItemTextArray() const;
protected:
	IMPORT_C TListBoxModelItemArrayOwnership ItemArrayOwnershipType() const;
private: // from MListBoxModel
	IMPORT_C TAny* Reserved_1();
protected:
	MDesCArray* iItemTextArray;
private:
	TListBoxModelItemArrayOwnership iItemArrayOwnershipType;
	}; 


#endif
