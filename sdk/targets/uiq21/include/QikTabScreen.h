// QIKTABSCREEN.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
// Created for Quartz 6.0


#ifndef __QIKTABSCREEN_H__
#define __QIKTABSCREEN_H__

#include <eikbctrl.h>	// class CEikBorderedControl
#include <coecobs.h>	// class MCoeControlObserver
#include <coeccntx.h>	// class MCoeControlContext

class CQikTab;
class CQikTabGroup;
class CQikTabScreen;
class CQikTabScreenPage;

typedef CArrayPtrFlat<CCoeControl>	CQikArrayOfTabPages;
typedef CArrayPtrFlat<CQikTab>		CQikArrayOfTabs;
typedef CArrayPtrFlat<CCoeControl>	CQikArrayOfTabPageControls;

const TInt KMaxTabTextLength = 32;


/** 
 * Use this class to get a tab control group with one or more tabs. If you want more
 * support, use the CQikTabScreen.
 * @see CQikTab, CQikTabScreen
 * @since Quartz 6.0
 */
class CQikTabGroup : public CCoeControl, public MCoeControlObserver, public MCoeControlContext
	{
public:
	enum TTabWidthType
		{
		EAllTabsTheSameWidth		= 0,
		EAllTabsAsWideAsTheWidest	= 1,
		EEachTabAsWideAsNeeded		= 2
		};

	enum THContentAlignment
		{
		ELeft	= 0,
		ECenter	= 1
		};

public:
	IMPORT_C CQikTabGroup();
	IMPORT_C ~CQikTabGroup();
	IMPORT_C void ConstructL(TTabWidthType aTabWidthType = EAllTabsTheSameWidth);
	IMPORT_C void AddTabL( CQikTab* aNewTab );
	IMPORT_C TInt NumberOfTabs() const;
	IMPORT_C CQikTab* Tab( TInt aIndex ) const;
	IMPORT_C virtual void SetCurrentTabL( TInt aNewCurrentTabIndex );
	IMPORT_C TInt CurrentTabIndex() const;
	IMPORT_C void ResetAndDestroy();
	IMPORT_C void SetExtraControlL( CCoeControl* aControl );
	IMPORT_C void SetTotalTabWidth( TInt aWidth );
	IMPORT_C void SetContentAlignment( THContentAlignment aAlignment );
	IMPORT_C THContentAlignment	ContentAlignment() const;
	IMPORT_C static TInt DefaultHeight();
public: 
	// from CCoeControl
	IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; 
	// from MCoeControlObserver
	IMPORT_C void HandleControlEventL( CCoeControl* aControl, MCoeControlObserver::TCoeEvent aEvent );
	// From MCoeControlContext
	IMPORT_C void PrepareContext(CWindowGc& aGc) const;
public:
	TBool IsFirst(const CQikTab* aTab) const;
	TBool IsLast(const CQikTab* aTab) const;
protected:
	IMPORT_C void RecalculateTabSizes();
	// from CCoeControl
	IMPORT_C void SizeChanged();
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Draw( const TRect& aRect ) const;
	IMPORT_C void Reserved_2();
private: // reserved virtual function space
	IMPORT_C virtual void QikReserved_1();
protected:	
	// *** Attributes
	CQikArrayOfTabs* iTabs;
	TTabWidthType iTabWidthType;
	THContentAlignment iHContentAlignment;
	TInt iIndexOfCurrentTab;
	CCoeControl* iExtraControl;
	TInt iWidthOfAllTabs;
private:
	TInt iQikSpare1;
	};


/**
 * The TabScreen lets the user of it create a multi-page screen area. The TabScreen has a TabGroup consisting of
 * one or more Tabs, and a TabPage connected to each tab. The TabScreen takes care of switching between the TabPages,
 * so that only the page connected to the currently selected tab is shown. User controls can be added to the general
 * TabPage object by calling the CQikTabScreenPage::AddControlL() method.
 *
 * The TabScreen can optionally host a extra control to be displayed at he right of the TabScreen's TabGroup. This can
 * for example be a button-bar control.
 *
 * NOTE: The TabScreen takes ownership of any control assigned to it by the SetExtraControlL() method, and the TabPages
 * takes ownership of all controls assigned to it by the CQikTabScreenPage::AddControlL() method.
 * <p>
 * To use the TabScreen you should:
 * <ol>
 * <li>Create it on the heap and call SetContainerWindow() and ConstructL() on it.
 * <li>Set the extent of it, using e.g. the SetExtentToAllAvailableSpaceL() method.
 * <li>Optionally modify the width of the TabGroup using the SetTabGroupWidth() method.
 * <li>Create a CQikTab object and a CQikTabScreenPage object.
 * <li>Create any number of controls to appear on the TabPage, adding them to the page using the CQikTabScreenPage::AddControlL() method.
 * <li>Add the Tab and its TabPage to the tab screen using the AddTabPageL() method.
 * <li>Repeat step 5 and 6 until all tabs are created and added.
 * </ol>
 *
 * @short The TabScreen is a compound control consisting of a TabGroup and a TabPage connected to each of the TabGroup's Tabs
 * @see CQikTabGroup, CQikTab, CQikTabScreenPage
 * @since Quartz 6.0
 */
class CQikTabScreen : public CCoeControl, public MCoeControlObserver
	{
public:
	IMPORT_C CQikTabScreen();
	IMPORT_C virtual ~CQikTabScreen();
	IMPORT_C void ConstructL( CQikTabGroup::TTabWidthType aTabWidthType );
	IMPORT_C void SetExtentToAllAvailableSpaceL();
	IMPORT_C void SetTotalTabWidth( TInt aWidth );
	IMPORT_C void AddTabPageL( CQikTab* aNewTab, CCoeControl* aNewTabPage );
	IMPORT_C CCoeControl* PageControl( TInt aIndex ) const;
	IMPORT_C CQikTab* Tab( TInt aIndex ) const;
	IMPORT_C void ResetAndDestroy();
	IMPORT_C void SetExtraControlL( CCoeControl* aControl );

	// Exported interface from the CQikTabGroup
	IMPORT_C void SetCurrentTabL( TInt aNewCurrentTabIndex );
	IMPORT_C TInt CurrentTabIndex() const;
	IMPORT_C void SetContentAlignment( CQikTabGroup::THContentAlignment aAlignment );
	IMPORT_C CQikTabGroup::THContentAlignment ContentAlignment() const;
public:	// from CCoeControl
	IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );
	IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
	IMPORT_C void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );
	IMPORT_C void ActivateL();
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
protected:	// from CCoeControl
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl( TInt aIndex ) const;
	IMPORT_C void SizeChanged();
	IMPORT_C void PositionChanged();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // reserved virtual function space
	IMPORT_C virtual void QikReserved_1();
protected:
	CQikTabGroup* iTabGroup;
	TInt iIndexOfCurrentTab;
	CQikArrayOfTabPages* iTabPages;
private:
	TInt iQikSpare1;
	};


/**
 *
 *
 * NOTE: The TabPage takes ownership of all controls added to it by the CQikTabScreenPage::AddControlL() method.
 *
 * NOTE: The controls to be added to the page must be added to the page before there extent is set.
 * <p>
 * To use the TabPage you should:
 * <ol>
 * <li>Create it on the heap and call ConstructL() on it. Don't call SetContainerWindowL() as the control is WindowOwning.
 * <li>Create a control to be added to the page.
 * <li>Add the control to the page using the CQikTabScreenPage::AddControlL() method.
 * <li>Set the extent and other properties of the added control.
 * <li>Repeat step 3 through 5 until all controls are created and added.
 * <li>Add the page and its tab (CQikTab) to the TabScreen using the CQikTabScreen::AddTabPageL() method.
 * </ol>
 *
 * @short This is the page connected to a tab, holding the user controls to be shown when the connected tab is the selected one.
 * @see CQikTabScreen, CQikTabGroup, CQikTab
 * @since Quartz 6.0
 */
class CQikTabScreenPage : public CEikBorderedControl
	{
public:
	IMPORT_C CQikTabScreenPage();
	IMPORT_C virtual ~CQikTabScreenPage();
	IMPORT_C void ConstructL( const CQikTabScreen& aParent );
	IMPORT_C void AddControlL( CCoeControl* aControl );
	IMPORT_C TInt DeleteControl( const CCoeControl* aControl );
	IMPORT_C void ResetAndDestroy();
public:	// from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
protected:
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Draw( const TRect& aRect ) const;
	IMPORT_C void Reserved_2();
private: // reserved virtual function space
	IMPORT_C virtual void QikReserved_1();
protected:
	// *** Attributes
	CQikArrayOfTabPageControls* iControlsOnTabPage;
private:
	TInt iQikSpare1;
	};



/** 
 * 
 * @short Objects of this class represents one single tab in a group of tabs (CQikTabGroup)
 * @see CQikTabGroup, CQikTabScreen 
 * @since Quartz 6.0
 */
class CQikTab : public CCoeControl
	{
public:
	IMPORT_C CQikTab();
	IMPORT_C ~CQikTab();
	IMPORT_C const TDesC& Text() const;
	IMPORT_C void SetText( const TDesC& aText );
	IMPORT_C void SetPicture( const CFbsBitmap* aMain, const CFbsBitmap* aMask = NULL );
	IMPORT_C void SetPictureFromFileL( const TDesC& aFileName, TInt aMain, TInt aMask = -1 );
public:	
	// Should only be used by CQikTabGroup and derived classes
	IMPORT_C const CQikTabGroup* Container() const;
	IMPORT_C void SetContainer( const CQikTabGroup* aContainer );
	IMPORT_C void SetSelected( TBool aSelected );
public:	// from CCoeControl
	IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );
	IMPORT_C TSize MinimumSize();
	IMPORT_C void HandleResourceChange(TInt aType);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
protected: // from CCoeControl
	IMPORT_C void HandlePointerEventL( const TPointerEvent& aPointerEvent );
	IMPORT_C void SizeChanged();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Draw( const TRect& aRect ) const;
	IMPORT_C void Reserved_2();
private: // reserved virtual function space
	IMPORT_C virtual void QikReserved_1();
protected:	
	const CQikTabGroup*	iContainer;
	TBool iIsSelected; 	
private:
	TBuf<KMaxTabTextLength>	iText;
	const CFbsBitmap* iBitmap;
	const CFbsBitmap* iBitmapMask;
private:
	TInt iQikSpare1;
	};


#endif // __QIKTABSCREEN_H__






