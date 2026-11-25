// EIKMENUB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMENUB_H__)
#define __EIKMENUB_H__

#include <eikdef.h>
#include <eikbctrl.h>
#include <eikmenup.h>

class CEikHotKeyTable;

/**
 *
 * Defines a menu bar title and provides some of the functionality
 * required to display it.
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikMenuBarTitle : public CBase
	{
public:
	enum
		{
		ETitleDimmed = 0x01,
		EIconOwnedExternally = 0x02
		};
public:
	struct SData
		{
		enum { ENominalTextLength=SLafMenuBar::ENominalTextLength };
		TInt iMenuPaneResourceId;
		TBuf<ENominalTextLength> iText; // less than this actually stored
		};
public:
	IMPORT_C CEikMenuBarTitle();
	IMPORT_C ~CEikMenuBarTitle();
	IMPORT_C void CreateIconL(CFbsBitmap* aBitmap, CFbsBitmap* aMask);
	IMPORT_C CFbsBitmap* IconBitmap() const;
	IMPORT_C CFbsBitmap* IconMask() const;
	IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);
	IMPORT_C void SetIcon(CGulIcon* aIcon);
	IMPORT_C void SetIconBitmapL(CFbsBitmap* aBitmap);
	IMPORT_C void SetIconMaskL(CFbsBitmap* aMask);
	IMPORT_C void SetIconOwnedExternally(TBool aOwnedExternally);
public: // Internal to Symbian
	IMPORT_C void DrawIcon(CWindowGc& aGc, const TRect& aRect, TInt aLeftMargin) const;
public:
	inline CGulIcon* Icon() const;
public: // other functions
	void CalculateBaseLine(TInt& aBaseLine, TInt& aTitleHeight);
	TInt IconWidth() const;
public:
	SData iData;
	TInt iPos;
	TInt iTitleFlags;
	TInt iWidth;
private:
	CGulIcon* iIcon;
	};


/**
 *
 * This class enables you to construct and manipulate menu bars.
 *
 * Menu bars are constructed from completed <code>MENU_BAR</code>
 * resources, and issue application commands which should be handled by
 * overriding <code>CEikAppUi::HandleCommandL()</code>.
 *
 * @since 6.0
 * @lib " eikcoctl.lib "
 */
class CEikMenuBar : public CEikBorderedControl
	{
public:
	struct SCursor
		{
		TInt iMenuPaneIndex;
		TInt iMenuItemIndex;
		};

	struct SPosition
		{
		TInt iMenuId;
		SCursor iMenuCursorPos;
		};

	friend class CEikMenuPaneTitle;
private:
	enum {ENothingSelected=-1};
public:
	IMPORT_C ~CEikMenuBar();
	IMPORT_C CEikMenuBar();
private: // framework
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C TCoeInputCapabilities InputCapabilities() const; // not available before Release 006
public:
	/**
	 * This class enables construction, and destruction of an array of
	 * information about menu bar titles.
	 * @lib " eikcoctl.lib "
	 */
	class CTitleArray : public CArrayPtrFlat<CEikMenuBarTitle>
		{
	public:
		IMPORT_C ~CTitleArray();
		IMPORT_C CTitleArray();
		};
public: // new functions
	IMPORT_C void ConstructL(MEikMenuObserver* aMenuObserver,TInt aHotKeyResourceId=0,TInt aMenuTitleResourceId=0);
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void ChangeMenuBarL(TInt aHotKeyResourceId=0,TInt aMenuTitleResourceId=0,TInt aDisplayNow=ETrue);
	IMPORT_C void SetHotKeyTable(CEikHotKeyTable* aHotKeyTable);
	IMPORT_C void SetMenuTitleResourceId(TInt aMenuTitleResourceId);
	IMPORT_C void SetMenuTitleArray(CTitleArray* aTitleArray);
	IMPORT_C void SetTitleArrayOwnedExternally(TBool aOwnedExternally);
	IMPORT_C SCursor SetMenuCursor(const SCursor& aCursor);
	IMPORT_C void StopDisplayingMenuBar();
	IMPORT_C void TryDisplayMenuBarL();
	IMPORT_C void MoveHighlightToL(TInt aNewSelectedTitle,TInt aNewSelectedItem=0);
	IMPORT_C void DrawItem(TInt aItem) const;
	CEikHotKeyTable* HotKeyTable() const;
	IMPORT_C TInt SelectedTitle();
	IMPORT_C TInt SelectedItem();
	IMPORT_C virtual void FindCommandIdInResourceL(TInt aCommandId,TInt& aPaneIndex,TInt& aItemIndex);
	IMPORT_C void ReduceRect(TRect& aRect) const;
	IMPORT_C void SetTitleL(const TDesC& aText, TInt aResourceId, CGulIcon* aIcon = NULL);
	IMPORT_C void SetTitleDimmed(TInt aTitleIndex, TBool aTitleDimmed);
	IMPORT_C CTitleArray* MenuTitleArray() const;
	IMPORT_C TInt FindIndexFromResourceId(TInt aResourceId) const;
public:
	void SetTitleTextL(const TDesC& aText);
	void CalculateSizeAndPositionL();
	MEikMenuObserver* MenuBarObserver() const;
	void UpdateInvalidatedWindowRegion();
	inline TBool UseSmallAdornments() const;
public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	IMPORT_C void Reserved_2();
private:
	TKeyResponse DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void DisplayL(TBool aDisplayWithMenuPaneOpen, TBool aGainFocus=ETrue);
	void MoveHighlightToCurrentMenuPaneFirstItem();
	inline void StartDisplayingMenuBarL();
	void StartDisplayingMenuBarL(TBool aDisplayWithMenuPaneOpen);
	void StopDisplayingMenuBar(TBool aSwapping);
	void HideMenuPane();
	void HideMenuPaneTitle();
	TKeyResponse TryNavigateAlongMenuBarL(TInt aKeyCode);
	void SaveCurrentMenuPositionL();
	void SetCursorPositionFromArray();
	TBool MenuHasItems();
	void SetMenuHasItems();
	TBool MenuHasPane();
	void SetMenuHasPane();
	TBool TitleArrayOwnedExternally();
	void ResetTitleArray();
	void CreateTitleArrayL();
	void SetMenuPaneFlag(TInt aFlag);
	void CreateIconFromResourceL(TResourceReader& aReader, CEikMenuBarTitle& aTitle, TInt aTitleFontHeight);
	inline MEikMenuObserver* MenuObserver() const;
	MEikMenuObserver* MenuObserver(TInt aTitleIndex) const;
	void DrawTitle(const CEikMenuBarTitle& aTitle) const;
	TBool IsTitleDimmed(TInt aTitleIndex);
	void SetVirtualCursorStateL(TBool aSetSuspended) const;
	void UpdateTitleTextBaseline();
private:
	struct STitleOverload
		{
		TInt iIndex;
		TBuf<CEikMenuBarTitle::SData::ENominalTextLength> iText;
		};
private:
	enum TEikMenuFlags {ETitleArrayOwnedExternally=0x01,EMenuHasItems=0x02,EMenuHasPane=0x04,EUseSmallAdornments=0x08,EMenuPaneWillBeRestored=0x10};
	CEikMenuPaneTitle* iMenuPaneTitle;
	MEikMenuObserver* iMenuObserver;
	CEikMenuPane* iMenuPane;
 	CEikHotKeyTable* iHotKeyTable;
	SCursor iCursor;
	TInt iMenuTitleResourceId;
	TInt iMenuHotKeyResourceId;
	TInt iSelectedTitle;
	TInt iBaseLine;
	TInt iMenuFlags;
	CTitleArray* iTitleArray;
	CArrayFixFlat<SPosition>* iPastMenuPosArray;
	CArrayFix<STitleOverload>* iTitleOverloads;
	TInt iDummy;
	};


/**
 *
 * This class is not intended to be used by application programmers.
 *
 * It is documented only for completeness.
 *
 * @since 6.0
 * @lib "eikcoctl.lib"
 */
class CEikMenuPaneTitle : public CEikBorderedControl
	{
public:
	IMPORT_C CEikMenuPaneTitle(CEikMenuBar* aMenuBar);
	IMPORT_C void ConstructL();
	IMPORT_C void SetSelectedTitle(TInt aSelectedTitle);
	IMPORT_C TMargins Margins() const;
	IMPORT_C void Close();
public:
	TInt SelectedTitle() const;
public: // framework
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	enum { EClearTitle=0x01 };
private:
	CEikMenuBar* iMenuBar;
	TInt iSelectedTitle;
	TInt iMenuTitleFlags;
	};


// Inlines

/**
 * Returns a pointer to the menu bar title icon. 
 */
inline CGulIcon* CEikMenuBarTitle::Icon() const
	{ return iIcon; }

/**
 * Gets a pointer to the menus hot key table.
 *
 * @returns   " CEikHotKeyTable* "
 *            Pointer to the menus hot key table.
 */
inline CEikHotKeyTable* CEikMenuBar::HotKeyTable() const
	{ return(iHotKeyTable); }

/**
 *
 * Tests whether the smallest possible spacing is being used by the menu
 * bar.
 *
 * @returns   " TBool "
 *            <code>ETrue</code> if the menu bar is using the
 *            smallest spacing values defined in the Laf.
 */
inline TBool CEikMenuBar::UseSmallAdornments() const
	{
	return iMenuFlags&EUseSmallAdornments;
	}

#endif
