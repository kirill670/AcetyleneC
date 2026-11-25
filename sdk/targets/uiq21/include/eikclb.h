// EIKCLB.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCLB_H__)
#define __EIKCLB_H__

#include <eiklbi.h>
#include <eiktxlbx.h>
#include <eiklbed.h>

class CColumnListBoxData;

class CColumnListBoxItemDrawer : public CTextListItemDrawer
	{
public:
    IMPORT_C CColumnListBoxItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CColumnListBoxData* aColumnData);
    IMPORT_C ~CColumnListBoxItemDrawer();
    IMPORT_C CColumnListBoxData* ColumnData() const;
public: // from CTextListItemDrawer
    IMPORT_C void DrawItemText(TInt aItemIndex,const TRect& aItemTextRect,TBool aItemIsCurrent,TBool aViewIsEmphasized, TBool aItemIsSelected) const;
	IMPORT_C void SetSearchStringL(const TDesC* aSearchString,const TInt aSearchStrColumn);
public: // from CListItemDrawer
	IMPORT_C TSize MinimumCellSize() const;
	IMPORT_C TInt ItemWidthInPixels(TInt aItemIndex) const;	
	IMPORT_C TListItemProperties Properties(TInt aItemIndex) const;
private: // from CListItemDrawer
	IMPORT_C TAny* Reserved_1();
protected:
	void DrawCurrentItemRect(const TRect& aRect) const;
private:
	TInt iSpare;
	};

class CEikColumnListBox : public CEikTextListBox
	{
public:
	IMPORT_C CEikColumnListBox();
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );
    IMPORT_C void ConstructL( CCoeControl* aParent,TInt aFlags=0,const CFont* aFont=NULL );
    IMPORT_C void EditItemL(TInt aColumn, TInt aMaxLength);
protected:
    IMPORT_C virtual void CreateItemDrawerL();
public:
    IMPORT_C CTextListBoxModel* Model() const;
    IMPORT_C CColumnListBoxItemDrawer* ItemDrawer() const;
public:	// from CCoeControl
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TInt iSpare;
	};

/**
 * The CEikColumnListBoxEditor class implements an item editor for column list boxes. 
 *
 * @since ER5U
 */
class CEikColumnListBoxEditor : public CEikListBoxTextEditor
    {
public:
    IMPORT_C CEikColumnListBoxEditor(MListBoxModel* aModel);
    IMPORT_C ~CEikColumnListBoxEditor();
    IMPORT_C void ConstructL(TInt aColumn);
public: // from MEikListBoxEditor
    IMPORT_C TPtrC ItemText();
    IMPORT_C TBool UpdateModelL();
protected:
    IMPORT_C TInt Column() const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
    TInt iColumnIndex; // refers to list box column
    };

#endif

