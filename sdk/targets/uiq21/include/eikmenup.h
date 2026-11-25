// EIKMENUP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMENUP_H__)
#define __EIKMENUP_H__

#include <eikbctrl.h>
#include <eikdef.h>
#include <eiksbobs.h> // for TEikScrollEvent
#include <lafpublc.h> // for THighlightType

class MEikMenuObserver;
class CEikHotKeyTable;
class CEikMenuPaneTitle;
class CEikButtonBase;
class CEikScrollBarFrame;
class CEikScrollBar;
class TEikScrollBarModel;
class CGulIcon;
class CEikMenuBar;
class TMargins8;
class CEikButtonGroupContainer;
class CEikMenuCbaContainer;

/**
 *
 * A menu item in a menu pane.  This encapsulates the data needed to define 
 * a menu pane item and provides some of the functionality required to 
 * display the item.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikMenuPaneItem : public CBase
	{
public:
	struct SData
		{
		enum { ENominalTextLength=80 };		/** Nominal text length (see <code>iText</code> below). */
		TInt iCommandId;
		TInt iCascadeId;
		TInt iFlags;
		TBuf<ENominalTextLength> iText; // less than this actually stored
		TBuf<ENominalTextLength> iExtraText;
		};
public:
	IMPORT_C static CEikMenuPaneItem* NewL(TInt aResourceId);
	IMPORT_C static CEikMenuPaneItem* NewLC(TInt aResourceId);
	IMPORT_C CEikMenuPaneItem();
	IMPORT_C ~CEikMenuPaneItem();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void SetIcon(CGulIcon* aIcon);
	IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);
public: // Internal to Symbian
	IMPORT_C void CreateIconL(CFbsBitmap* aBitmap, CFbsBitmap* aMask);
	IMPORT_C void DrawItemIcon(CWindowGc& aGc, TRect aRect, TBool aDimmed, TInt aBitmapSpaceRequired) const;
	IMPORT_C CFbsBitmap* IconBitmap() const;
	IMPORT_C CFbsBitmap* IconMask() const;
	IMPORT_C void SetIconBitmapL(CFbsBitmap* aBitmap);
	IMPORT_C void SetIconMaskL(CFbsBitmap* aMask);
public:
	inline CGulIcon* Icon() const;
public:
	TInt iPos;
	TInt iHotKeyCode;
	SData iData;
private:
	CGulIcon* iIcon;
	};

class CMenuPaneExtra;

/**
 *
 * A menu pane.
 *
 * Menu panes are opened by activating the menu title
 * (<code>CEikMenuPaneTitle</code> / <code>MENU_TITLE</code>) which is
 * displayed in the menu bar (<code>CEikMenuBar</code> /
 * <code>MENU_BAR</code>). They can also be cascaded from a menu item
 * (<code>CEikMenuPaneItem</code> / <code>MENU_ITEM</code>) or launched
 * by a menu button (<code>CEikMenuButton</code>).Menu panes may be
 * defined using a <code>MENU_PANE</code> resource.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikMenuPane : public CEikBorderedControl
	{	
private:
	class CMenuScroller;
	friend class CMenuScroller;
public:
	/**
	 * The text to be displayed for a hotkey.
	 */
	typedef TBuf<20> THotKeyDisplayText;
public:
	/**
	 *
	 * This class provides a constructor to create an array of menu pane
	 * items and a destructor to destroy an array of menu pane items.
	 * @lib "eikcoctl.lib"
	 */
	class CItemArray:public CArrayPtrFlat<CEikMenuPaneItem>
		{
	public:
		IMPORT_C CItemArray();
		IMPORT_C ~CItemArray();
		};
public:
	IMPORT_C ~CEikMenuPane();
	IMPORT_C CEikMenuPane(MEikMenuObserver* aMenuObserver);

	IMPORT_C void ConstructL(CEikMenuPane* aOwner);
	IMPORT_C void Reset();
public: // framework
	IMPORT_C void ActivateL();
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C TCoeInputCapabilities InputCapabilities() const; // not available before Release 006
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C TSize MinimumSize();
protected: // framework
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
public: // new functions
	IMPORT_C void AddMenuItemL(const CEikMenuPaneItem::SData& aMenuItem);
	IMPORT_C void AddMenuItemL(CEikMenuPaneItem* aMenuItem);
	IMPORT_C void InsertMenuItemAtL(const CEikMenuPaneItem::SData& aMenuItemData, TInt aIndex);
	IMPORT_C void InsertMenuItemAtL(CEikMenuPaneItem* aMenuItem, TInt aIndex);
	IMPORT_C void DeleteMenuItem(TInt aCommandId);
	IMPORT_C CEikMenuPaneItem::SData& ItemData(TInt aCommandId);
	IMPORT_C CEikMenuPaneItem* ItemAndPos(TInt aCommandId,TInt& aPos);
	IMPORT_C void StartDisplayingMenuPane(const CEikHotKeyTable* aHotKeyTable,const TPoint& aTargetPos, const CEikMenuPaneTitle* aMenuPaneTitle,TInt aMinWidth,  TPopupTargetPosType aTargetType = EPopupTargetTopLeft);
	IMPORT_C void SetItemTextL(TInt aCommandId,const TDesC& aDes);
	IMPORT_C void SetItemTextL(TInt aCommandId,TInt aRid);
	IMPORT_C void SetItemDimmed(TInt aCommandId,TBool aDimmed);
	IMPORT_C void SetItemButtonState(TInt aCommandId,TInt aButtonState);
	IMPORT_C void SetSelectedItem(TInt aSelectedItem);
	IMPORT_C TInt SelectedItem() const;
	IMPORT_C void CloseCascadeMenu();
	IMPORT_C void SetItemArray(CItemArray* aItemArray);
	IMPORT_C void SetItemArrayOwnedExternally(TBool aOwnedExternally);
	IMPORT_C void SetLaunchingButton(CEikButtonBase* aButton);
	IMPORT_C void MoveHighlightTo(TInt aNewSelectedItem);
	IMPORT_C TInt NumberOfItemsInPane() const;
	IMPORT_C void Close();
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType,TBool aConsumeAllKeys); // not available before Platform 004
	IMPORT_C void SetScrollBarOnLeft(TBool aOnLeft);
	IMPORT_C void SetArrowHeadScrollBar(TBool aArrowHead);
	IMPORT_C TInt MenuItemIndex(TInt aCommandId);
	IMPORT_C TInt MenuItemCommandId(TInt aIndex);
	IMPORT_C CEikButtonGroupContainer* MenuButtons() const;
public:
	TInt DefaultSelectedItemIndex(TInt aCurrentItemSelection) const;
	void SetMenuBar(CEikMenuBar& aBar);
	void SetMenuObserver(MEikMenuObserver* aMenuObserver);
	void HandleClose(TBool aCascadeMenu=EFalse);
private:
	enum { ECopyContextToScrollBar=0x01, EFadedBehind=0x02, ELeftAdornmentExist=0x04, ERightAdornmentExist=0x08};
	enum TUpadteItemValues
		{
		ENoUpdate			=0x00,
		EUpdateItemValues	=0x01,
		};
	enum TValidSize
		{
		EValidCurrentSize	=0x00,
		EInvalidCurrentSize	=0x01,
		};
private: // new functions
	TSize CalculateSize();
	TKeyResponse DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType,TBool aConsumeAllKeys);
	void DrawItem(CWindowGc& aGc,TInt aItem, SLafMenuPane::THighlightType aHighlight, TInt aMaxIconWidth) const;
	void DrawItem(CWindowGc& aGc,TInt aItem, SLafMenuPane::THighlightType aHighlight, TInt aMaxIconWidth, TBool aDrawVisualFeedBack) const;
	void FindHotKeyDisplayText(TDes& aDes,const CEikMenuPaneItem& aItem) const;
	void ReportSelectionMadeL();
	void ReportCanceled();
	void GiveVisualFeedback();
	void LaunchCascadeMenuL(TInt aCascadeMenuId);
	void DoLaunchCascadeMenuL(TInt aCascadeMenuId);
	void TryLaunchCascadeMenuL(const CEikMenuPaneItem& aItem);
	TBool ItemArrayOwnedExternally();
	TBool IsHotKeyL(TInt modifiers,TInt aCode);
	TBool MoveToItemL(TInt aCode, TInt aModifiers);
	void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);
	void CreateScrollBarFrame();
	void UpdateScrollBar();
	void DoUpdateScrollBarL();
	static TInt UpdateScrollBarCallBackL(TAny* aObj);
	TRect ViewRect() const;
	TInt NumberOfItemsThatFitInView(TValidSize aValidSize) const;
	TInt TotalItemHeight() const;
	void ScrollToMakeItemVisible(TInt aItemIndex);
	TBool IsItemVisible(TInt aItemIndex) const;
	void Scroll(TInt aAmount, TBool aDrawNow);
	TBool CheckCreateScroller();
	void CheckCreateScrollerL();
	void CreateItemArrayL();
	TInt MaxIconWidth() const;
	TMargins8 Margins() const;
	TMargins SumOfMarginsAndBorders() const;
	TRect InnerRect() const;
	void ProcessCommandToAllObserversL(TInt aCommandId);
	void SetVirtualCursorStateL(TBool aSetSuspended) const;
	void UpdateItemHeightForIcon(const CEikMenuPaneItem& aItem, TInt aItemTextTopSpace, TInt aItemTextBottomSpace);
	TSize CalculateSize(const CItemArray& aItemArray, TInt& aMenuPaneFlags, TInt& aHotkeyColWidth, TBool aUpdateItemValues) const;
	TInt NextItemThatCanBeSelected(TInt aCurrentMenuPaneItem, const TKeyEvent& aKeyEvent) const;
	TInt NumOfItemsThatRefuseHighlightAboveCurrent(TInt aCurrentItem) const;
private: // from CCoeControl
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C void Reserved_2();
private:
	friend class CEikMenuButton;
	friend class CEikMenuCbaContainer;
private:
	MEikMenuObserver* iMenuObserver;
	CEikMenuPane* iCascadeMenuPane;
	const CEikMenuPaneTitle* iMenuPaneTitle;
 	const CEikHotKeyTable* iHotKeyTable;
	CEikMenuPane* iOwner;
	CItemArray* iItemArray;
	TBool iArrayOwnedExternally;
	TBool iAllowPointerUpEvents;
	TInt iNumberOfDragEvents;
	TInt iSelectedItem;
	TInt iItemHeight;
	TInt iBaseLine;
	TInt iHotkeyColWidth;
	TInt iMenuPaneFlags;
	CEikScrollBarFrame* iSBFrame;
	CMenuScroller* iScroller;
	CEikButtonBase* iLaunchingButton; // for popouts only
	CEikMenuBar* iMenuBar;
	CEikMenuCbaContainer* iCbaContainer;
	CMenuPaneExtra* iMenuPaneExtra;
	};

// Inlines
inline CGulIcon* CEikMenuPaneItem::Icon() const
	{ return iIcon; }


#endif
