// EIKTXLBX.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
   
#if !defined(__EIKTXLBX_H__)
#define __EIKTXLBX_H__

#include <coecntrl.h>
#include <eiklbx.h>
#include <eiklbm.h>

class CTextListBoxModel;

/**
 *
 * List box for displaying text.
 *
 * Text list boxes use the standard list box view,
 * <code>CListBoxView</code>, and a customised item drawer and list box
 * model. Writing derived classes:This class can be either used as-is, or
 * derived from to provide further functionality. There are three classes
 * supplied in Uikon which are derived from this class:<code>CEikChoiceL-
 * istPopoutListBox</code><code>CEikColumnListBox</code><code>CEikFileSe-
 * lectorListBox</code>
 *
 * @since 6.0
 * @lib " eikcoctl.lib "
 */
class CEikTextListBox : public CEikListBox
	{
public:
	IMPORT_C ~CEikTextListBox();
	IMPORT_C CEikTextListBox();
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aFlags = 0);
	IMPORT_C CTextListBoxModel* Model() const;
public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
protected:
	IMPORT_C virtual void CreateItemDrawerL();
	IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
private:
	IMPORT_C virtual void Reserved_3(); // listbox use only
protected:
	TInt iRequiredCellCharWidth;
	};

/**
 * The CListBoxView-derived class used alongside the CEikListBox-derived class CEikTextListBox.
 * @since App-Framework_6.2
 * @public
 */
class CTextListBoxView : public CListBoxView
	{
public:
	IMPORT_C CTextListBoxView();
	IMPORT_C ~CTextListBoxView();
	IMPORT_C void AllowVariableHeightItems();
	IMPORT_C void AllowPartiallyVisibleItems();
protected:
	IMPORT_C CTextListBoxView(TUint aInitialFlags); // one or more of CListBoxView::TInitialFlags
	IMPORT_C virtual void ConstructL(MListBoxModel* aListBoxModel, CListItemDrawer* aItemDrawer, CWsScreenDevice* aScreen, RWindowGroup* aGroupWin, RWindow* aWsWindow, const TRect& aDisplayArea, TInt aItemHeight);
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex);
	IMPORT_C virtual void CalcBottomItemIndex();
	IMPORT_C virtual void SetItemHeight(TInt aItemHeight);
	IMPORT_C virtual void UpdateSelectionL(TSelectionMode aSelectionMode);
	IMPORT_C virtual TBool ScrollToMakeItemVisible(TInt aItemIndex);
	IMPORT_C virtual void VScrollTo(TInt aNewTopItemIndex);
	IMPORT_C virtual void VScrollTo(TInt aNewTopItemIndex, TRect& aMinRedrawRect);
	IMPORT_C virtual void HScroll(TInt aHScrollAmount);
	IMPORT_C virtual void CalcDataWidth();
	IMPORT_C virtual TInt VisibleWidth(const TRect& aRect) const;
	IMPORT_C virtual TInt CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const;
	IMPORT_C virtual void Draw(const TRect* aClipRect = NULL) const;
	IMPORT_C virtual void DrawItem(TInt aItemIndex) const;
	IMPORT_C virtual TPoint ItemPos(TInt aItemIndex) const;
	IMPORT_C virtual TSize ItemSize(TInt aItemIndex=0) const;
	IMPORT_C virtual void MoveCursorL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode);
	IMPORT_C virtual void VerticalMoveToItemL(TInt aTargetItemIndex, TSelectionMode aSelectionMode);
	IMPORT_C virtual TBool XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const;
	IMPORT_C virtual TInt NumberOfItemsThatFitInRect(const TRect& aRect) const;
private:
	IMPORT_C virtual TAny* Reserved_1();
private:
	TAny* iSpareForFutureUse;
	};

/**
 *
 * Horizontal snaking text list box.
 *
 * This snaking list box is intended for displaying text. The list box
 * lays its items out using the <code>CEikSnakingListBox</code>
 * algorithms, and uses a <code>CTextListItemDrawer</code> to draw its
 * items.This class is not intended for user derivation.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikSnakingTextListBox : public CEikSnakingListBox
	{
public:
	IMPORT_C ~CEikSnakingTextListBox();
	IMPORT_C CEikSnakingTextListBox();
	IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aFlags = 0);
	IMPORT_C CTextListBoxModel* Model() const;
public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	};


#endif
