// EIKHLBX.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKHLBX_H__)
#define __EIKHLBX_H__

#include <eiklbx.h>
#include <eiklbed.h>

class CHierarchicalListBoxModel;
class CHierarchicalListBoxView;
class CHierarchicalListItemDrawer;

class CEikHierarchicalListBox : public CEikListBox
	{
public:
	IMPORT_C CEikHierarchicalListBox();
	IMPORT_C ~CEikHierarchicalListBox();
	IMPORT_C CHierarchicalListBoxModel* HlModel() const;
	IMPORT_C CHierarchicalListBoxView* HlView() const;
	IMPORT_C CHierarchicalListItemDrawer* HlDrawer() const;
public: // from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
public: // from CEikListBox
    IMPORT_C void EditItemL(TInt aMaxLength);
protected: // from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CEikListBox
	IMPORT_C CListBoxView* MakeViewClassInstanceL();
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikListBox
	IMPORT_C void Reserved_3(); // listbox use only
private:
	void HandleItemSelectionL();
private:
	TBool* iHlbxDestroyed;
	TInt iPressedIndex;
	};

/**
 * The CEikHierarchicalListBoxEditor class implements an item editor for hierarchical list boxes.
 *
 * @since ER5U
 */
class CEikHierarchicalListBoxEditor : public CEikListBoxTextEditor
	{
public:
	IMPORT_C CEikHierarchicalListBoxEditor( MListBoxModel* aModel );
	IMPORT_C ~CEikHierarchicalListBoxEditor();
public: // from MEikListBoxEditor
	IMPORT_C TPtrC ItemText();
	IMPORT_C TBool UpdateModelL();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TInt iSpare;
	};

#endif
