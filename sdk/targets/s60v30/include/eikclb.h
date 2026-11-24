// EIKCLB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
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
public:
	/** The SetProperties is convinience method for normal cases.
	 * NOTE that it does NOT work correctly if you can insert/delete
	 * items from the list -- You need to update all properties if
	 * any changes to the item text array happen! Often it is convinient
	 * to override the Properties() method. Further, use this only
	 * for small lists as it causes O(n) time if you need to set
	 * all properties.
	 *
	 * It has been implemented as sorted list of (index,Property) pairs.
	 */
	struct SListProperties 
	    {
	    TInt iItem; // must be first
	    TListItemProperties iProperties;
	    };
    IMPORT_C void ClearAllPropertiesL();
	/** 
	 * If you're using find, aItemIndex for this method is the same as you give in
	 * MdcaPoint() --> the default Properties() does conversion between
	 * indexes.
	 */
    IMPORT_C void SetPropertiesL(TInt aItemIndex, TListItemProperties aProperty);
    IMPORT_C virtual TListItemProperties Properties(TInt aItemIndex) const;
public: // from CTextListItemDrawer
    IMPORT_C void DrawItemText(TInt aItemIndex,const TRect& aItemTextRect,TBool aItemIsCurrent,TBool aViewIsEmphasized, TBool aItemIsSelected) const;
	// the next one is for avkon
	IMPORT_C void DrawItemMark(TBool aItemIsSelected, TBool aViewIsDimmed, const TPoint& aMarkPos) const;
public: // from CListItemDrawer
	IMPORT_C TSize MinimumCellSize() const;
	IMPORT_C TInt ItemWidthInPixels(TInt aItemIndex) const;	
    IMPORT_C void SetItemCellSize(const TSize& aSizeInPixels);
	TSize LafItemSize() { return iItemCellSize; }
private: // from CListItemDrawer
	IMPORT_C TAny* Reserved_1();
private: // defining reserved method.
	IMPORT_C void CColumnListBoxItemDrawer_Reserved();
protected:
	void DrawCurrentItemRect(const TRect& aRect) const;
	CArrayFix<SListProperties>* iPropertyArray;
	TInt iSpare;
	};

/**
 * Starting from 3.0 listbox uses highlight animations. Starting and stopping
 * animation is connected to focus events. To support highlight animations
 * properly you have to make sure that the list has focus when it has 'visual
 * focus'. Common issues:
 * - In many cases list is in a container which sits on top of the control
 *   stack. The container receives all focus events and should hand them to the
 *   list too. E.g.
 *             void CContainer::FocusChanged( TDrawNow aDrawNow )
 *                 {
 *                 ... some code ...
 *                 if( iListBox )
 *                     iListBox->SetFocus( IsFocused(), aDrawNow );
 *                 }
 * - When switching components programmatically, e.g. from one list to another
 *   in the same view, make sure that you remove focus from the other
 *   component.
 * - In more complex cases you may have to add a dummy interceptor control to
 *   the top of control stack to hand focus events to list.
 * - Make sure you handle resource changes correctly. If resource handle chain
 *   is solid it should reach CCoeControl::HandleResourceChange, which informs
 *   child components about resource change.
 */
class CEikColumnListBox : public CEikTextListBox
	{
public:
	IMPORT_C CEikColumnListBox();
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );
    IMPORT_C void ConstructL( const CCoeControl* aParent,TInt aFlags=0);
    IMPORT_C void EditItemL(TInt aColumn, TInt aMaxLength);
protected:
    IMPORT_C virtual void CreateItemDrawerL();
    IMPORT_C virtual void CreateModelL();
public:
    IMPORT_C CTextListBoxModel* Model() const;
    IMPORT_C CColumnListBoxItemDrawer* ItemDrawer() const;

    /**
    * This method needs to be called to enable extended drawing features such as
    * skinning, pictograph drawing and marquee text in the listbox draw routine.
    *
    * Methods CEikFormattedCellListBox::ConstructL and
    * CEikFormattedCellListBox::ConstructFromResourceL call this method. So, you
    * only need to call this if your listbox implementation does not call either
    * of those.
    * 
    * This method can be safely called more than once.
    * Item drawer must be created before calling this method, or a panic is raised.
    *
    * @since 2.6
    */
    IMPORT_C void EnableExtendedDrawingL();

    // helper function
    void SetIconSizes();
public: // from CEikListBox
	IMPORT_C CListBoxView* MakeViewClassInstanceL();
    IMPORT_C void FocusChanged(TDrawNow aDrawNow);
public:	// from CCoeControl
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aUid);
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
	IMPORT_C virtual void CEikListBox_Reserved(); // listbox use only
private: // data
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
    IMPORT_C void ConstructL(TInt aColumn);   // just set column index
public: // from MEikListBoxEditor
    IMPORT_C TPtrC ItemText();
    IMPORT_C TBool UpdateModelL();
public: // From CCoeControl
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);    
protected:
    IMPORT_C TInt Column() const;
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private:
    TInt iColumnIndex; // refers to list box column
    };

class CColumnListBoxView : public CListBoxView
	{
public: // from CListBoxView
	IMPORT_C void Draw(const TRect* aClipRect = NULL) const;
	IMPORT_C virtual void CalcBottomItemIndex();
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();

private: // data
    TInt iSpare;
	};

#endif

