/*
* ============================================================================
*  Name     : Eikfrlb.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/
// EIKFRLB.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
#if !defined(__EIKFRLB_H__)
#define __EIKFRLB_H__

#include <eiklbi.h>
#include <eiklbv.h>
#include <eiktxlbm.h>
#include <eiktxlbx.h>

class CFormattedCellListBoxData;

/**
*  CFormattedCellListBoxItemDrawer draws a single list item and manages
*  list item properties.
*
*  @lib avkon
*  @since 0.0
*/
class CFormattedCellListBoxItemDrawer : public CTextListItemDrawer
	{
public:
	IMPORT_C CFormattedCellListBoxItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont, CFormattedCellListBoxData* aFormattedCellData);
	IMPORT_C ~CFormattedCellListBoxItemDrawer();
	IMPORT_C CFormattedCellListBoxData* FormattedCellData() const;
	IMPORT_C CFormattedCellListBoxData* ColumnData() const; // for compability with columnlistbox itemdrawer
	IMPORT_C virtual void DrawEmptyItem(TInt aItemIndex, TPoint aItemRectPos, TBool aViewIsDimmed) const;
	IMPORT_C void SetTopItemIndex(TInt aTop);

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
	IMPORT_C void SetPropertiesL(TInt aItemIndex, TListItemProperties properties);
	IMPORT_C virtual TListItemProperties Properties(TInt aItemIndex) const;
	TSize LafItemSize() { return iItemCellSize; }

public: // from CTextListItemDrawer
	IMPORT_C void DrawItemText(TInt aItemIndex,const TRect& aItemTextRect,TBool aItemIsCurrent,TBool aViewIsEmphasized, TBool aItemIsSelected) const;
	IMPORT_C void DrawItemMark(TBool aItemIsSelected, TBool aViewIsDimmed, const TPoint& aMarkPos) const;
public: // from CListItemDrawer
	IMPORT_C TSize MinimumCellSize() const;
	IMPORT_C TInt ItemWidthInPixels(TInt aItemIndex) const; 
protected:
	void DrawCurrentItemRect(const TRect& aRect) const;
	void WordWrapListItem(TPtr& aTarget, const TDesC &aItemString, TInt aFirstIndex, TInt aSecondIndex) const;
private:
	IMPORT_C void CFormattedCellListBoxItemDrawer_Reserved();
protected:
	TInt iTopItemIndex;
	CArrayFix<SListProperties>* iPropertyArray;
	TInt iSpare;
	};

/** 
 * Avkon baseclass similar to uikon's column listbox.
 *
 *  ListBox <>--> View ---> ItemDrawer ---> Model
 *  ListBox <>--> ItemDrawer <>---> Data
 *  ListBox <>--> Model <>---> MDesCArray <--- Array <>---> Engine
 *
 * Content for list items are tab-separated strings.
 *
 * See concrete classes derived from CEikFormattedCellListBox for details.
 *
 * See methods
 *   CEikListBox::ConstructFromResourceL()
 *   CEikListBox::ConstructL()
 *   CEikTextListBox::SetItemTextArray()
 *   CEikFormattedCellListBoxData::SetIconArray()
 * 
 * Related flags for dialogs (avkon.hrh)
 *   EAknDialogSelectionList
 *   EAknDialogMenuList
 *   EAknDialogMultiselectionList
 *
 * Check also:
 *   CAknSelectionListDialog (aknselectionlist.h)
 *   CAknMarkableListDialog  (aknselectionlist.h)
 *   CAknPopupList           (aknpopup.h)
 *   CAknListQueryDialog     (aknquerydialog.h)
 *   CAknColumnListBox       (aknlists.h)
 *
 *  @lib avkon
 *  @since 0.0
 */
class CEikFormattedCellListBox : public CEikTextListBox 
	{
public:
	IMPORT_C CEikFormattedCellListBox();
	/** ConstructFromResource
	 *
	 * See LISTBOX resource definition
	 * 
	 * flags
	 *   EAknListBoxSelectionList
	 *   EAknListBoxMenuList
	 *   EAknListBoxMarkableList
	 *   EAknListBoxMultiselectionList
	 *   EAknListBoxViewerFlags
	 */
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	/** ConstructL() (eikfrlb.hrh)
	 * aFlags:
	 *   EAknListBoxSelectionList
	 *   EAknListBoxMenuList
	 *   EAknListBoxMarkableList
	 *   EAknListBoxMultiselectionList
	 *   EAknListBoxViewerFlags
	 */
	IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aFlags);
public:
	IMPORT_C CTextListBoxModel* Model() const;
	IMPORT_C CFormattedCellListBoxItemDrawer* ItemDrawer() const;

    // helper function
    void SetIconSizes();

public:
	/**
	 * Enable or disable logical to visual reordering in listbox data text drawing.
     * By default, it is enabled. This has any effect only when bidirectional text
     * is rendered.
     *
     * If you convert text to visual order prior to passing it to the listbox
     * (for example by wrapping text to lines with methods in AknBidiTextUtils),
     * then you should disable conversion in listbox by calling this method.
     *
	 * @since 2.0
	 * @param aUseConversion enable or disable conversion
	 */
	IMPORT_C void UseLogicalToVisualConversion( TBool aUseConversion );

public:
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
protected:
	IMPORT_C virtual void CreateItemDrawerL();
	IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect &aRect) const;
public: // from CEikListBox
	IMPORT_C CListBoxView* MakeViewClassInstanceL();
public: // from CCoeControl
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
protected: // from MObjectProvider
	IMPORT_C virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private: // listbox use only
	IMPORT_C virtual void CEikListBox_Reserved(); 
};

/**
*  CFormattedCellListBoxView draws all the list items and manages
*  the area of the screen allocated for list itself. In particular,
*  this class does not handle margins of the whole list.
*
*  @lib avkon
*  @since 0.0
*/
class CFormattedCellListBoxView : public CListBoxView
	{
public: // from CListBoxView
	IMPORT_C void Draw(const TRect* aClipRect = NULL) const;
	IMPORT_C virtual void DrawEmptyList(const TRect &aClientRect) const;
	IMPORT_C virtual void CalcBottomItemIndex();
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
	};


#endif
