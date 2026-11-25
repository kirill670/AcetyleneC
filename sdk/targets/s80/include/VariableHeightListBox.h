// VariableHeightListBox.h
// Copyright (c) Nokia Corporation 2002. All rights reserved.
//
#ifndef __VARIABLEHEIGHTLISTBOX_H__
#define __VARIABLEHEIGHTLISTBOX_H__

#include <eikscrlb.h>
#include <eiksbobs.h>
#include <apgcli.h>
#include <gulicon.h>
#include <skin.h>

#include <VariableHeightListBoxItem.h>

class CVarHeightLbxIconCache;

/**
 * class CVariableItemHeightListBox
 *
 * displays a list of variable height items in the format:
 *
 * [icon][left set text]            [right set text]
 *
 * and each result can have any number of lines, optionally indented. An item
 * can also have a separator before it, allow the list box to be divided into
 * groups or categories
 *
 * This is used by globalfinder for displaying results
 *
 * Each item in the listbox must derive from MVariableItemHeightListBoxEntry
 */
class CVariableItemHeightListBox : public CEikBorderedControl, public MEikScrollBarObserver
	{
public:
	// destructor
	IMPORT_C ~CVariableItemHeightListBox();
	IMPORT_C TBool UpdateScrollBars();
	IMPORT_C void SetFont(TCknLogicalFont::TFontCategory aFont);
	IMPORT_C TInt CurrentItemIndex() const;
// from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C TSize MinimumSize();
/*! \brief return given item */
	virtual const MVariableItemHeightListBoxEntry& Entry(TInt aIndex) const=0;
/*! \brief return ETrue if item has a separator before it */
	virtual TBool ItemHasSeparatorBefore(TInt aItem) const=0;
/*! \brief return ETrue if separators are to be displayed */
	virtual TBool DisplaySeparators() const=0;
/*! \brief the selected item has been activated by clicking or Enter */
	virtual void HandleItemActivatedL()=0;
/*! \brief the selected item has been deleted using Ctrl-D or Delete/Backspace */
	virtual void HandleItemDeletedL()=0;
/*! \brief Esc key has been pressed */
	virtual void HandleEscapeL()=0;
/*! \brief allows construction by derived classes */
	virtual void DoConstructL()=0;
/*! \brief return line indent in pixels for the given line in the items */
	virtual TInt LineIndent(TInt aLine) const=0;
/*! \brief return number of items */
	virtual TInt NumberItems() const=0;
/*! \brief return separator text before given item */
	virtual TPtrC SeparatorText(const MVariableItemHeightListBoxEntry& aEntry) const=0;
	virtual TVarHeightListBoxColumnInfo::TDisplayPriority DisplayPriority() const=0;
// virtual
	IMPORT_C virtual void DoOverlayIcon(CBitmapContext& aGc,const MVariableItemHeightListBoxEntry& aEntry,TInt aLine,TInt aCol,const TPoint& aBltPos,const TRect& aBitmapRect) const;
	IMPORT_C virtual void DrawSeparator(CBitmapContext& aGc,TRect& aRect,const MVariableItemHeightListBoxEntry& aEntry) const;
	IMPORT_C virtual TInt SeparatorHeight() const;
	IMPORT_C virtual TInt InterItemGap() const;
protected:
	IMPORT_C CVariableItemHeightListBox();
	IMPORT_C void BringItemIntoView(TInt aItem,TBool aForceTopItem,TBool aRedrawIfInView);
	IMPORT_C void ConstructL(CCoeControl* aParent);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void SetCurrentItem(TInt aIndex);
	IMPORT_C void DrawItemNow(TInt aItem,TBool aBringIntoView,TBool aDrawSeparator);
	IMPORT_C void HandleItemAddedL();
	IMPORT_C void CacheItemsIconsL(const MVariableItemHeightListBoxEntry& aEntry);
	IMPORT_C void DoSetFont();
	IMPORT_C void ResetIconsL();
private:
	TRect ItemRect(TInt aItem) const;
	void BringItemIntoView(TInt aItem,TBool aForceTopItem,TBool aRedrawIfInView,TBool aUpdateScrollBar);
	void DrawItem(CBitmapContext& aGc,TInt aItem,const TRect& aRect,const MVariableItemHeightListBoxEntry& aEntry) const;
	void DoUpdateScrollBarsL();
	void UpdateScrollBarThumb();
	void DoScrollWhileDragging();
	TBool AnchorLastItemToBottom();
	TBool HasSeparatorBefore(TInt aItem) const;
	TBool ItemInView(TInt aItem) const;
	TBool AreScrollbarsRequired();
	TInt ItemsFullyInView() const;
	TInt ItemHeight(TInt aItem) const;
	TInt TotalHeightRequired() const;
	TInt Item(const TPoint& aPos) const;
// from MEikScrollBarObserver
	IMPORT_C void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType);
	void HandleScrollEvent(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType);

// from CCoeControl
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void SizeChanged();
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C TInt CountComponentControls() const;
//
	static TInt UpdateScrollBarsCallBack(TAny* aObj);
	static TInt ScrollWhileDragging(TAny* aObj);
protected:
	RApaLsSession iAppArcSession;
	TRect iViewRect;
	TInt iCurrentItemIndex;
	TInt iTopItemIndex;
	TInt iTopItemOffset;
	TEikScrollBarModel iScrollModel;
	TEikScrollEvent iScrollEvent;
	CEikScrollBar* iScrollBar;
	CPeriodic* iIdleScroller;
	CIdle* iIdle;
//
	TInt iGrabbedItem;
//
	TCknLogicalFont::TFontCategory iFontCat;
	const CFont* iFont;
//
	CVarHeightLbxIconCache* iIconCache;
//
	CGulIcon* iDefaultIconSmall;
	TInt iItemRightMargin;
	TInt iZoomHeight;
	TInt iZoomBaseline;
	mutable TBuf<256> iDrawBuffer;
	};

#endif // __VARIABLEHEIGHTLISTBOX_H__
