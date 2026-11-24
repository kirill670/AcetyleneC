// EIKMENUP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMENUP_H__)
#define __EIKMENUP_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

#if !defined(__EIKSBOBS_H__)
#include <eiksbobs.h> // for TEikScrollEvent
#endif

#include <bidi.h>

// FORWARD DECLARATIONS
class MEikMenuObserver;
class CEikHotKeyTable;
class CEikMenuPaneTitle;
class CEikButtonBase;
class CEikScrollBarFrame;
class CEikScrollBar;
class TEikScrollBarModel;
class CGulIcon;
class CEikMenuPaneExtension ;

// CONSTANTS
const TInt KScaleableTextSeparator = 0x0001;

/**
  * A helper class for extending CEikMenuPaneItem without breaking binary 
  * compability.
  */
class CExtendedItemData : public CBase
    {
public:
    ~CExtendedItemData();
public:
    CGulIcon* iIcon;
    HBufC* iScaleableText;    
    };


/**
 * The CEikMenuPaneItem class encapsulates the data needed to define a menu pane item and
 * provides some of the functionality required to display the item.
 *
 * @since ER5U
 */
class CEikMenuPaneItem : public CBase
    {
public:
    struct SData
        {
        enum { ENominalTextLength=40 };
        TInt iCommandId;
        TInt iCascadeId;
        TInt iFlags;
        TBuf<ENominalTextLength> iText; // less than this actually stored
        TBuf<1> iExtraText;
        };
public:
    /**
     * C++ default constructor.
     */
    IMPORT_C CEikMenuPaneItem();
    
    /**
     * Destructor.
     */
    IMPORT_C ~CEikMenuPaneItem();
    
    /**
     * Sets a menu item icon.
     * This replaces any icon already set for the menu item.
     * @param aIcon Menu item icon consisting of a picture bitmap and a mask bitmap.
     */
    IMPORT_C void SetIcon(CGulIcon* aIcon);
    
    /**
     * Draws the menu item icon.
     * @param aGc Graphics context to which the icon is drawn.
     * @param aRect Rectangle in which the icon is drawn. 
     * @param aDimmed If ETrue the icon is drawn dimmed. 
     * @param aBitmapSpaceRequired Length of one side of the square required to 
     * contain the bitmap.
     */
    IMPORT_C void DrawItemIcon(CWindowGc& aGc, 
                               TRect aRect, 
                               TBool aDimmed, 
                               TInt aBitmapSpaceRequired) const;
    
    /**
     * Construct an icon from bitmaps. 
     * Constructs a new icon for the menu item, taking ownership of 
     * the picture bitmap aBitmap and the mask bitmap aMask unless the 
     * bitmaps are externally owned.
     * @param aBitmap Picture bitmap.
     * @param aMask Mask bitmap.
     */
    IMPORT_C void CreateIconL(CFbsBitmap* aBitmap, 
                              CFbsBitmap* aMask);
    
    /**
     * Gets a pointer to the menu item's icon picture bitmap. 
     * This does not imply transfer of ownership.
     * @return Picture bitmap.
     */
    IMPORT_C CFbsBitmap* IconBitmap() const;
    
    /**
     * Gets a pointer to the menu item's icon mask bitmap. 
     * This does not imply transfer of ownership.
     * @return Mask bitmap.
     */
    IMPORT_C CFbsBitmap* IconMask() const;
    
    /**
     * Sets icon bitmap ownership.
     * Sets the menu item's icon bitmaps as externally owned if aOwnedExternally is ETrue.
     * @param aOwnedExternall If ETrue bitmaps are set as externally owned. 
     * If EFalse bitmaps are set as not being externally owned. 
     */
    IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);
    
    /**
     * Sets the picture bitmap. 
     * Transfers ownership unless the bitmaps are already owned externally.
     * @param aBitmap Picture bitmap.
     */
    IMPORT_C void SetIconBitmapL(CFbsBitmap* aBitmap);
    
    /**
     * Sets the mask bitmap. 
     * Transfers ownership unless the bitmaps are already owned externally.
     * @param aMask Mask bitmap.
     */
    IMPORT_C void SetIconMaskL(CFbsBitmap* aMask);
    
    /**
     *
     */
    IMPORT_C TPtrC ScaleableText() const;
    
    /**
     *
     */
    IMPORT_C void SetScaleableTextL(const TDesC& aText);

private:
    inline void CreateExtendedDataBlock();
    inline TBool IsScaleableText(const TDesC& aText) const;
    TPtrC GetNominalText(const TDesC& aText);

public:
    TInt iPos;
    TInt iHotKeyCode;
    SData iData;
private:
    CExtendedItemData* iExtendedData;
    };


inline void CEikMenuPaneItem::CreateExtendedDataBlock()
    {
    if (!iExtendedData)
        {
        TRAPD(err, ( iExtendedData = new (ELeave) CExtendedItemData() ) );
        }
    }



inline TBool CEikMenuPaneItem::IsScaleableText(const TDesC& aText) const
    {
    return (aText.Locate(TChar(KScaleableTextSeparator)) == KErrNotFound ? EFalse : ETrue);
    }



class CEikMenuPane : public CEikBorderedControl
    {
private:
    enum {ENothingSelected=-1};
    class CMenuScroller;
    friend class CMenuScroller;
    friend class CEikMenuPaneExtension;
public:
    typedef TBuf<20> THotKeyDisplayText;
public:
    class CItemArray:public CArrayPtrFlat<CEikMenuPaneItem>
        {
    public:
        IMPORT_C CItemArray();
        IMPORT_C ~CItemArray();
        IMPORT_C void AddItemL(CEikMenuPaneItem* aMenuItem);
        };

public:
    /**
     * Destructor.
     */
    IMPORT_C ~CEikMenuPane();
    
    /**
     * Constructor. Constructs a menu pane object with the specified observer.
     * @param aMenuObserver Menu Observer.
     */
    IMPORT_C CEikMenuPane(MEikMenuObserver* aMenuObserver);

    /**
     * Completes construction of a menu pane object.
     * @param aOwner Menu pane owner ( for cascade menu )
     * @param aEditMenuObserver Observer for the edit menu.
     */
    IMPORT_C void ConstructL(CEikMenuPane* aOwner, 
                             MEikMenuObserver* aEditMenuObserver = NULL);
    
    /**
     * Destroys the menu pane's item array.
     */
    IMPORT_C void Reset();
    
public: // framework

    /**
     * Handles key events offered to the menu by the control environment and provides an 
     * appropriate implementation of CCoeControl::OfferKeyEventL(). 
     * @param aKeyEvent The key event. 
     * @param aType The type of key event: EEventKey, EEventKeyUp or EEventKeyDown.
     */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                         TEventCode aType);
    
    /**
     * Handles a pointer event on the menu.
     * @param aPointerEvent The pointer event to handle.
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
    /**
     * Gets the list of logical colours employed in the drawing of the control, 
     * paired with an explanation of how they are used. 
     * Appends the list into aColorUseList.
     * @param aColorUseList The list of colours paired with explanations.
     */
    IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
    
    /**
     * Handles a change to the menu's resources which are shared across the environment. 
     * For example, colours or fonts.
     * @param aType The type of resource that has changed.
     */
    IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u

private: // from base class
    /**
     * From CAknControl
     */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
public: // from MCoeInputObserver
    /**
     * Gets the input capabilities of the menu pane which accepts all text.
     */
    IMPORT_C TCoeInputCapabilities InputCapabilities() const;
    
protected: // from base class
    /**
     * Redraws an area of the menu pane. From CCoeControl.
     * @param aRect Optional, not used currently.
     */
    IMPORT_C void Draw(const TRect& aRect) const;
    
    /**
     * Takes any action required when the menu pane gains or loses focus, 
     * to change its appearance for example. From CCoeControl.
     * @param aDrawNow If EDrawNow the menu pane is redrawn. If 
     * ENoDrawNow the menu pane is not redrawn.
     */
    IMPORT_C void FocusChanged(TDrawNow aDrawNow);
    
    /**
     * Constructs the menu pane using the specified resource reader.
     * Fills the menu item array with the list of menu items provided by the resource file.
     * From CCoeControl.
     * @param aReader The resource reader to use.
     */
    IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    
public: // new functions

    /**
     * Adds a menu item dynamically by creating a new menu item, setting its data to aMenuItem
     * and appending it to the pane's menu item array. 
     * Updates the menu's scroll bar to take account of the new item.
     * @param aMenuItem The menu item to add.
     * NOTICE that SData is the structure and all fileds should be initialized.
     */
    IMPORT_C void AddMenuItemL(const CEikMenuPaneItem::SData& aMenuItem);
    
    /**
     * Adds a menu item dynamically by creating a new menu item, setting its data to aMenuItem
     * and inserting it into the pane's menu item array. 
     * Updates the menu's scroll bar to take account of the new item.
     * @param aMenuItem The menu item to add.
     * NOTICE that SData is the structure and all fileds should be initialized.
     * @param aPreviousId The id of the item after which the new item should be added.
     */
    IMPORT_C void AddMenuItemL(const CEikMenuPaneItem::SData& aMenuItem, 
                               TInt aPreviousId);
    
    /**
     * Adds a menu item dynamically by creating a new menu item from resource 
     * and inserting it into the pane's menu item array. 
     * @param aResourceId The ID of the resource for the menu item.
     * @param aPreviousId The ID of the previous menu item, after whcih this newly created 
     * item should be added.
     * @param aAddSeparator Shouldn't be used as separator is not not supported anymore.
     */
    IMPORT_C void AddMenuItemsL(TInt aResourceId, 
                                TInt aPreviousId = 0,
                                TBool aAddSeperator = EFalse);
    
    /**
     * Deletes the specified item in the menu pane.
     * @param aCommandId The ID for the item to be deleted.
     */
    IMPORT_C void DeleteMenuItem(TInt aCommandId);
    
    /**
     * Deletes the items between specified items.
     * @param aStartIndex The index of the item after which items should be deleted.
     * @param aEndIndex The index of the item up to which items should be deleted.
     */
    IMPORT_C void DeleteBetweenMenuItems(TInt aStartIndex, 
                                         TInt aEndIndex);
    
    /**
     * Gets a reference to the data in the specified menu item.
     * @param aCommandId The command ID of the menu item for which data is obtained.
     */
    IMPORT_C CEikMenuPaneItem::SData& ItemData(TInt aCommandId);
    
    /**
     * Gets a pointer to the specified menu item. Also gets the position of the item 
     * within the menu pane. Panics if there are no menu items in the menu pane. 
     * Panics if the menu pane id does not identify any menu pane item in the array.
     * @param aCommandId The ID of the menu item for which a pointer is returned. 
     * @param aPos On return, the position of the menu item with an ID of aCommandId.
     */
    IMPORT_C CEikMenuPaneItem* ItemAndPos(TInt aCommandId,TInt& aPos);
    
    /**
     * Displays a menu pane.
     * Displays the menu pane with the corner identified by aTargetType 
     * in the position specified by aTargetPos. This function uses aMinTitleWidth to 
     * calculate the area required to display the menu pane, taking into account 
     * whether the menu is a cascading menu or popup menu.
     * @param aHotKeyTable Optional hotkey table. 
     * @param aTargetPos Position of the corner of the menu pane identified by aTargetType. 
     * @param aMenuPaneTitle The menu pane's title.
     * @param aMinWidth Minimum width of the menu's title.
     * @param aTargetType The corner of the menu pane to which aTargetPos relates. 
     * The default is the top left corner. Possible: EPopupTargetTopLeft,
     * EPopupTargetTopRight, EPopupTargetBottomLeft, EPopupTargetBottomRight
     */
    IMPORT_C void StartDisplayingMenuPane(const CEikHotKeyTable* aHotKeyTable,
                                          const TPoint& aTargetPos, 
                                          const CEikMenuPaneTitle* aMenuPaneTitle,
                                          TInt aMinWidth,  
                                          TPopupTargetPosType aTargetType = EPopupTargetTopLeft);
    /**
     * Sets the text in a menu item.
     * @param aCommandId The command (as defined in an .hrh file) associated with this menu item. 
     *  This identifies the menu item whose text is to be set. 
     * @param aDes New item text.
     */                                      
    IMPORT_C void SetItemTextL(TInt aCommandId,
                               const TDesC& aDes);
    
    /**
     * Sets the text in a menu item from resource.
     * @param aCommandId The command (as defined in an .hrh file) associated with this menu item. 
     *  This identifies the menu item whose text is to be set. 
     * @param aRid The resource ID of the menu item text. 
     */
    IMPORT_C void SetItemTextL(TInt aCommandId,
                               TInt aRid);
                               
    /**
     * Dims (greys out) or undims a menu item. 
     * Dimming indicates that user input is not accepted.
     * @param aCommandId The command (as defined in an .hrh file) associated with this menu item. 
     * This identifies the menu item whose text is to be dimmed or un-dimmed. 
     * @param aDimmed ETrue to dim this menu item. EFalse to un-dim this menu item.
     */
    IMPORT_C void SetItemDimmed(TInt aCommandId,
                                TBool aDimmed);
                                
    /**
     * Sets the item to be indicated or not. It should be used to change the state of radio 
     * buttons or check box items.
     * It has real effect only starting from Series60 v3.0.
     * @param aButtonState should be EEikMenuItemSymbolOn or EEikMenuItemSymbolIndeterminate
     */                           
    IMPORT_C void SetItemButtonState(TInt aCommandId,
                                     TInt aButtonState);
    
    /**
     * Sets the selected menu item.
     * @param aSelectedItem The index of the item to get selected
     */                                
    IMPORT_C void SetSelectedItem(TInt aSelectedItem);
    
    /**
     * Gets the position of the selected menu item.
     * @return The position of the selected menu item.
     */
    IMPORT_C TInt SelectedItem() const;
    
    /**
     * Closes and destroys any current cascade menu and takes focus back. 
     * Does nothing if no cascade menu exists.
     */
    IMPORT_C void CloseCascadeMenu();
    
    /**
     * Sets the array containing the list of menu items for the current menu pane.
     * @param aItemArray The menu item array for the menu pane.
     */
    IMPORT_C void SetItemArray(CItemArray* aItemArray);
    
    /**
     * Set menu item array ownership.
     * @param aOwnedExternally If ETrue the menu pane's menu item array is set as externally owned. 
     * If EFalse the menu pane's menu item array is set as not externally owned.
     */
    IMPORT_C void SetItemArrayOwnedExternally(TBool aOwnedExternally);
    
    /**
     * Sets the specified button to launch the menu pane.
     * Doesn't have any effect in current implementation.
     * @param aButton The button to set as launching the menu.
     */
    IMPORT_C void SetLaunchingButton(CEikButtonBase* aButton);
    
    /**
     * Moves the menu pane highlight.
     * Moves the menu pane highlight to a newly selected menu item 
     * identified by aNewSelectedItem. Scrolls the menu to show the new 
     * selected item if necessary and redraws only the newly selected item 
     * and the currently selected item if possible.
     * @param aNewSelectedItem The newly selected menu item index.
     */
    IMPORT_C void MoveHighlightTo(TInt aNewSelectedItem);
    
    /**
     * Gets the number of menu items within the menu pane.
     */
    IMPORT_C TInt NumberOfItemsInPane() const;
    
    /**
     * Closes the menu pane.
     */
    IMPORT_C void Close();
    
    /**
     * Handles key events offered to the menu by the control environment.
     * @param aKeyEvent The key event.
     * @param aType The type of key event: EEventKey, EEventKeyUp or EEventKeyDown. 
     * @param aConsumeAllKeys If ETrue this function returns EKeyWasConsumed regardless 
     * of whether it was used. If EFalse the key event is consumed if possible and 
     * either EKeyWasConsumed or EKeyWasNotConsumed is returned as appropriate.
     */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                         TEventCode aType,
                                         TBool aConsumeAllKeys); // not available before Platform 004
    
    /**
     * Sets whether the scroll bar occupies the left side of the menu pane.
     * @param aOnLeft If ETrue the scroll bar will occupy the left side of the menu pane.
     */                                     
    IMPORT_C void SetScrollBarOnLeft(TBool aOnLeft);
    
    /**
     * Sets whether the menu pane uses an arrow head scroll bar.
     * @param aArrowHead If ETrue the menu pane uses an arrow head scroll bar.
     */
    IMPORT_C void SetArrowHeadScrollBar(TBool aArrowHead);
    
// new for AVKON
    
    /**
     * Moves highlight to the next item or to the first one if last item is selected. 
     */
    IMPORT_C void NavigateToNextItem();
    
    /**
     * Inserts the menu item to the specified position.
     * @param aMenuItem The menu item to add.
     * NOTICE that SData is the structure and all fileds should be initialized.
     * @param aPosition The position of newly created item in the array.
     */
    IMPORT_C void InsertMenuItemL(const CEikMenuPaneItem::SData& aMenuItem, 
                                  TInt aPosition);
    
    /**
     * Checks whether menu pane contains the menu item and returns position of it if 
     * the item is found.
     * @param aCommandId The command ID of the item to be searched for.
     * @param aPosition On return contains position of the item.
     * @return ETrue if item was found. Otherwise EFalse.
     */
    IMPORT_C TBool MenuItemExists(TInt aCommandId, 
                                  TInt& aPosition);
    
    /**
     * Returns ETrue if the menu pane is cascade menu. EFalse if the menu pane
     * is the main menu.
     */
    IMPORT_C TBool IsCascadeMenuPane() const;
    
    /**
     * Enables or disables text scrolling functionality. It is disabled by default.
     * @param aEnable ETrue to enable text scrolling functionality.
     */
    IMPORT_C void EnableMarqueeL(const TBool aEnable); 

    /**
     * Report that selection was done for the currently highlighted item.
     */
    void ActivateCurrentItemL();
    
    /**
     * Closes cascade menu if there is one and it is active.
     */
    TBool CancelActiveMenuPane();
    
    /**
     * Deletes dimmed items from the menu item array.
     */
    void FilterDimmedItems();
    
    /**
     * Does nothing currently
     */
    void ClipMenuItems(TInt aWidth);
    
    /**
     * Returns the menu pane for the cascade menu or NULL if there is not any.
     */
    CEikMenuPane* CascadeMenuPane();
    
    /**
     * Gets a reference to the data in the specified menu item.
     * @param aItemIndex The index of the item in the items array.
     * @return The menu item's data.
     * @since 3.1
     */
    IMPORT_C CEikMenuPaneItem::SData& ItemDataByIndexL(TInt aItemIndex);
    
    /**
     * Returns ETrue in case when position of the menu was set from outside
     * @since 3.1
     */
    TBool IsPositionToBeForced() const;
    
    /**
     * Creates and enables a special characters row to be used in the edit menu
     * @param aSpecialChars Buffer that holds the selected characters after 
     * user has selected them.
     * @since 3.1
     */
    IMPORT_C void ConstructMenuSctRowL( TDes& aSpecialChars );
    
private:
    enum { EInvalidCurrentSize=0x01, EBackgroundFaded=0x02 };
    
private: // new functions
    TRect CalculateSizeAndPosition() ;
    enum THighlightType {ENoHighlight,EDrawHighlight,ERemoveHighlight};
    void DrawItem(CWindowGc& aGc,TInt aItem,THighlightType aHighlight) const;
    void FindHotKeyDisplayText(TDes& aDes,const CEikMenuPaneItem& aItem) const;
    void ReportSelectionMadeL();
    void ReportCanceled();
    void GiveVisualFeedback();
    void LaunchCascadeMenuL(TInt aCascadeMenuId);
    void DoLaunchCascadeMenuL(TInt aCascadeMenuId);
    void TryLaunchCascadeMenuL(const CEikMenuPaneItem& aItem);
    void PrepareGcForDrawingItems(CGraphicsContext& aGc) const;
    TBool ItemArrayOwnedExternally() const;
    TBool IsHotKeyL(const TInt modifiers,const TInt aCode);
    TBool MoveToItemL(TInt aCode, TInt aModifiers);
    void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);
    void CreateScrollBarFrame();
    void UpdateScrollBar();
    void DoUpdateScrollBarL();
    void UpdateScrollBarThumbs();
    static TInt UpdateScrollBarCallBackL(TAny* aObj);
    TRect ViewRect() const;
//    TInt NumberOfItemsThatFitInView() const;
    TInt TotalItemHeight() const;
    void ScrollToMakeItemVisible(TInt aItemIndex);
    void Scroll(TInt aAmount);
    TBool CheckCreateScroller();
    void CheckCreateScrollerL();
    void ResetItemArray();
    void CreateItemArrayL();
    void SetVScrollBarFlag();
    TInt TopHighlightGap() const;
    TInt BottomHighlightGap() const;
    TInt EvaluateMaxIconWidth() const;
    void CreateIconFromResourceL(TResourceReader& aReader, CEikMenuPaneItem& aItem) const;
    // new for AVKON
    void AnimateMenuPane(const TPoint& aNewPos);

    // To make layout correct
    TRect ListMenuPane() const;
    TRect PopupMenuWindow() const;
    TRect PopupSubmenuWindow() const;

    // Skin support for menu
    void UpdateBackgroundContext(const TRect& aWindowRect);

    // Support method for highlight animation
    void RepaintHighlight() const;

private: // from CCoeControl
    IMPORT_C void Reserved_1();
    IMPORT_C void Reserved_2();

private : // new functions
    void LoadCascadeBitmapL() ;

    // Support for check mark, from v3.0
    void LoadCheckMarkBitmapL();
    TBool MenuHasCheckBoxOn() const;
    // Support for radio button, from v3.0
    void LoadRadioButtonBitmapL();
    TBool IsItemMemberOfRadioButtonGroup(TInt aItem) const ;
    // for drawing,from v3.0
    TBool MenuHasIcon() const;

    TRect CalculateSizeAndPositionScalable( const TRect& aWindowRect, TInt aNumItemsInPane ) ;
    TRect HighlightRect() const;
    void PrepareHighlightFrame() const;
    void SetCascadedIconSize() const;

    // fixes marquee flickering
    friend class CAknMarqueeControl;
    static TInt RedrawMarqueeEvent( TAny* aControl );
    
    CEikMenuPaneExtension* Extension() const;

protected: // from CoeControl
    IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

public: // From CoeControl.
    IMPORT_C TInt CountComponentControls() const;
    IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
    
protected: // new functions
    /**
     * Disables sliding effect
     * By default is enabled if there is enough memory.
     *
     * @since 3.1
     */
    void DisableAnimation();
    
    /**
     * The position of the menu will be changed according to the one 
     * which is specified by arguments in StartDisplayingMenuPane()
     * By default those arguments are not used.
     *
     * @since 3.1
     */
    void SetPositionToBeForced(TBool aForced);
    
    /**
     * Returns the maximum number of items which can be seen simultaneously.
     *
     */
    TInt NumberOfItemsThatFitInView() const;
    
    
private: // data
    friend class CEikMenuButton;
    MEikMenuObserver* iMenuObserver;
    MEikMenuObserver* iEditMenuObserver;
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
    TInt iFlags;
    CEikScrollBarFrame* iSBFrame;
    CMenuScroller* iScroller;
    CEikButtonBase* iLaunchingButton; // for popouts only
    TInt iSubPopupWidth; // 0..2
    TBool iEnableAnimation;
    CEikMenuPaneExtension* iExtension ;  // iSpare used for extension class pointer.

    };





#endif

