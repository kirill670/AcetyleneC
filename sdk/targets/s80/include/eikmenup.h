/*
* ==============================================================================
*  Name        : eikmenup.h
*  Part of     : CKON
*  Interface   : Menubar API
*  Description : Menu pane and Menu pane item classes
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef EIKMENUP_H
#define EIKMENUP_H

// INCLUDES
#include <eikbctrl.h>
#include <eiksbobs.h>   // for TEikScrollEvent
#include <eikdef.h>
#include <lafpublc.h>   // for THighlightType
#include <skin.h>

// CONSTANTS
/** <code>uSeconds</code> pause before scroll repeat */
const TInt KEikMenuPointerRepeatPause = 600000;

/** <code>uSeconds</code> pause between scroll repeats */
const TInt KEikMenuPointerRepeatInterval = 20000;

// FORWARD DECLARATIONS
class MEikMenuObserver;
class CEikHotKeyTable;
class CEikMenuPaneTitle;
class CEikButtonBase;
class CGulIcon;
class CEikMenuBar;
class TMargins8;
class CEikButtonGroupContainer;
class CEikMenuCbaContainer;
class CMenuPaneExtra;


/**
* The <code>CEikMenuPaneItem</code> class provides a Menu item in a Menu pane.
* This encapsulates the data needed to define a Menu pane item and provides 
* some of the functionality required to display the item.
*
* @lib eikcoctl.lib
* @since 6.0
*/
class CEikMenuPaneItem : public CBase
    {
    public:
        /** 
         * The struct <code>SData</code> is a storage structure for a Menu 
         * pane item.
         */
        struct SData
            {
            enum 
                { 
                /** the nominal text length (see <code>iText</code>) */
                ENominalTextLength=80 
                };
            /** the command ID associated with the Menu pane item */
            TInt iCommandId;
            /** the ID of a cascade Menu, if one exists */
            TInt iCascadeId;
            /** the flag settings for the Menu pane item */
            TInt iFlags;
            /** the text for the Menu pane item */
            TBuf<ENominalTextLength> iText;
            /** the extra Menu pane text such as the hotkey text */
            TBuf<ENominalTextLength> iExtraText;
            };
    public:

        /**
        * This method allocates and 
        * constructs a new Menu pane item from a resource of type 
        * <code>MENU_ITEM</code> with ID <code>aResourceId</code>.
        * It returns a pointer to the Menu pane item and transfers ownership.
        *
        * @param aResourceId The ID of the <code>MENU_ITEM</code> resource 
        *                    used to construct the Menu pane item
        * @return a pointer to the new Menu pane item
        * @remarks
        * @see
        */
        IMPORT_C static CEikMenuPaneItem* NewL(TInt aResourceId);

        /**
        * This method allocates and 
        * constructs a new Menu pane item from a resource of type 
        * <code>MENU_ITEM</code> with ID <code>aResourceId</code>.
        * It returns a pointer to the Menu pane item and transfers ownership, 
        * leaving the pointer on the cleanup stack.
        *
        * @param aResourceId The ID of the <code>MENU_ITEM</code> resource 
        *                    used to construct the Menu pane item
        * @return a pointer to the new Menu pane item
        * @remarks
        * @see
        */
        IMPORT_C static CEikMenuPaneItem* NewLC(TInt aResourceId);

        /**
        * The default object constructor.
        */
        IMPORT_C CEikMenuPaneItem();

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikMenuPaneItem();

        /**
        * Completes construction of the Menu pane item from a resource of type
        * <code>MENU_ITEM</code>. This method is called by <code>NewL()</code> 
        * and <code>NewLC()</code>.
        * 
        * @param aReader The resource reader
        * @remarks
        * @see
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Sets a Menu item icon, transferring ownership.
        * This replaces any icon already set for the Menu item.
        *
        * @param aIcon Menu item icon consisting of a picture bitmap and a 
        *              mask bitmap
        * @remarks
        * @see
        */
        IMPORT_C void SetIcon(CGulIcon* aIcon);

        /**
        * Sets icon bitmap ownership.
        *
        * Sets the Menu item's icon bitmaps as externally owned if
        * <code>aOwnedExternally</code> is <code>ETrue</code>.
        *
        * @deprecated
        * @internal
        * @param aOwnedExternally If <code>ETrue</code> bitmaps are set as externally owned. If <code>EFalse</code> bitmaps are set as not being externally owned.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);
    public:

        /**
        * Construct an icon from bitmaps.
        *
        * Constructs a new icon for the Menu item, taking ownership of the
        * picture bitmap <code>aBitmap</code> and the mask bitmap
        * <code>aMask</code> unless the bitmaps are externally owned.
        *
        * @deprecated
        * @internal
        * @param aBitmap Picture bitmap.
        * @param aMask Mask bitmap.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void CreateIconL(CFbsBitmap* aBitmap, CFbsBitmap* aMask);

        /**
        * Used to draw the Menu item icon. Now does nothing.
        * Draws the Menu item icon.
        *
        * @deprecated
        * @internal
        * @param aGc Not used
        * @param aRect Not used
        * @param aDimmed Not used
        * @param aBitmapSpaceRequired Not used
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void DrawItemIcon(CWindowGc& aGc, TRect aRect, TBool aDimmed, TInt aBitmapSpaceRequired) const;

        /**
        * Returns a pointer to the Menu item's icon picture bitmap. This does not imply transfer of ownership.
        * @deprecated
        * @internal
        * @return Picture bitmap.
        * <BR><B>Type of return value:</B> CFbsBitmap*
        * <BR><B>Range of return value:</B> Pointer to object.
        * <BR><B>Contents of return value:</B> See CFbsBitmap
        */
        IMPORT_C CFbsBitmap* IconBitmap() const;

        /**
        * Returns a pointer to the Menu item's icon mask bitmap. This does not imply transfer of ownership..
        * @deprecated
        * @internal
        * @return Mask bitmap.
        * <BR><B>Type of return value:</B> CFbsBitmap*
        * <BR><B>Range of return value:</B> Pointer to object.
        * <BR><B>Contents of return value:</B> See CFbsBitmap
        */
        IMPORT_C CFbsBitmap* IconMask() const;

        /**
        * Sets the picture bitmap. Transfers ownership unless the bitmaps are already owned externally..
        * @param aBitmap Picture bitmap.
        * @deprecated
        * @internal
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetIconBitmapL(CFbsBitmap* aBitmap);

        /**
        * Sets the mask bitmap. Transfers ownership unless the bitmaps are already owned externally..
        * @deprecated
        * @internal
        * @param aMask Mask bitmap.
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetIconMaskL(CFbsBitmap* aMask);
    public:

        /**
        * Returns the icon.
        *
        * @return a pointer to the icon
        * @remarks
        * @see
        */
        inline CGulIcon* Icon() const;
    public:
        /** the vertical position of the Menu pane item */
        TInt iPos;
        /** the hotkey code for the Menu pane item */
        TInt iHotKeyCode;
        /** the Menu pane item data */
        SData iData;
    private:
        CGulIcon* iIcon;
    };

/**
* The <code>CEikMenuPane</code> class provides a Menu pane.
* A Menu pane is opened by selecting a Menu title (that is, the text label
* for the Menu pane) contained in a Menu bar. In a resource file, a Menu 
* pane is declared within a Menu bar using the keyword <code>MENU_TITLE</code>
* and its corresponding class definition is <code>CEikMenuPaneTitle</code>. 
* The Menu pane is defined in the resource file using <code>MENU_PANE</code> and
* its corresponding class definition is <code>CEikMenuPane</code>.
*
* @lib eikcoctl.lib
* @since 6.0
*/
class CEikMenuPane : public CEikBorderedControl
    {   
    private:
        class CMenuScroller : public CBase
            {
        public:
            static CMenuScroller* NewL(CEikMenuPane& aMenu);
            ~CMenuScroller();

            inline TInt TopItemIndex() const;
            inline void SetTopItemIndex(TInt aIndex);
            inline CIdle* Idle() const;
            void HandleScrollEventL(TEikScrollEvent aEventType);
        private:
            CMenuScroller(CEikMenuPane& aMenu);
            void ConstructL();
        private:
            CEikMenuPane& iMenuPane;
            TInt iTopItemIndex;
            CIdle* iIdle;
            };

        friend class CMenuScroller;
        friend class CMenuPaneExtra;
    public:
        /** the text to be displayed for a hotkey */
        typedef TBuf<20> THotKeyDisplayText;
    public:
        /**
        * The <code>CEikMenuPane::CItemArray</code> class provides a 
        * constructor to create an array of Menu pane items and a destructor 
        * to destroy an array of Menu pane items. Each item in the Menu pane
        * occupies an index in the array. For example, the first item occupies
        * index <code>0</code>, the second occupies index <code>1</code>, and 
        * so on.
        *
        * @lib eikcoctl.lib
        * @since
        */
        class CItemArray:public CArrayPtrFlat<CEikMenuPaneItem>
            {
            public:
                /**
                * The object constructor.
                */
                IMPORT_C CItemArray();
                /**
                * The object destructor.
                */
                IMPORT_C ~CItemArray();
            };
    public:
        /** 
         * The enumeration <code>TMenuPaneLevel</code> specifies the level of 
         * the Menu pane. 
         */
        enum TMenuPaneLevel
            {
            /** a Menu pane can be the first level; in this case, there is no Menu bar */
            EMenuPaneLevelFirst,
            /** the second level Menu pane */
            EMenuPaneLevelSecond,
            /** the third level Menu pane */
            EMenuPaneLevelThird
            };
    public:

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikMenuPane();

        /**
        * Constructs a Menu pane object with the specified observer.
        *
        * @param aMenuObserver The Menu observer
        * @remarks
        * @see
        */
        IMPORT_C CEikMenuPane(MEikMenuObserver* aMenuObserver);


        /**
        * Completes construction of a Menu pane object, where a 
        * Menu is the owner of a cascade Menu. 
        *
        * @see ConstructFromResourceL()
        * @param aOwner The Menu pane owner. If this is <code>NULL</code>, it 
        *               implies that this is the first Menu pane on the Menu 
        *               bar; otherwise, it is a cascaded Menu pane
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(CEikMenuPane* aOwner);

        /**
        * Completes construction of a Menu pane object, where a Menu is the 
        * owner of a cascade Menu.
        *
        * @see ConstructFromResourceL()
        * @param aOwner The Menu pane owner. If this is <code>NULL</code>, it
        *               implies that this is the first Menu pane on the Menu 
        *               bar; otherwise, it is a cascaded Menu pane
        * @param aDisableFading Set to <code>ETrue</code> to disable fading 
        *                       behind the Menu pane. <code>EFalse</code> 
        *                       enables fading behind the Menu pane
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL(CEikMenuPane* aOwner, TBool aDisableFading);

        /**
        * Destroys the Menu pane's item array.
        *
        * @remarks
        * @see
        */
        IMPORT_C void Reset();
    public:

        /**
        * Activates the Menu pane control and makes sure that the selected item is visible.
        * It may also activate and draw its relative Menu pane title.
        * This function won't leave since the Menu pane and Menu pane title don't use the
        * backup window.
        * @internal
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void ActivateL();

        /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this control. 
        *         <code>EKeyWasConsumed</code> if the control takes action on the 
        *         key event; <code>EKeyWasNotConsumed</code> otherwise
        * @remarks
        * @see CCoeControl::OfferKeyEventL()
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Handles a pointer event on the Menu.
        *
        * @see CCoeControl::HandlePointerEventL()
        * @param aPointerEvent The pointer event to handle
        * @remarks
        * @see
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        *
        * @see CCoeControl::HandleResourceChange()
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);

        /**
        * Returns the input capabilities of the Menu pane. Typically, called by
        * the FEP-aware text editor. By default, the Menu pane supports 
        * navigation keys. 
        *
        * @return the input capabilities
        * @remarks 
        * @see CCoeControl
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;

        /**
        * Serialise internal state to a stream.
        * @internal.
        * @param aWriteStream The stream
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

        /**
        * Redraws the Menu pane.
        *
        * @param aRect If supplied, the coordinates must be relative 
        *              to the Menu pane's top left-hand corner
        * @remarks
        * @see
        */
        IMPORT_C void Draw(const TRect& aRect) const;

        /**
        * Gets the minimum size of this Menu pane.
        *
        * @return the minimum size for the control
        * @remarks
        * @see
        */
        IMPORT_C TSize MinimumSize();
    protected:

        /**
        * Takes any action required when the Menu pane gains or loses focus, to change its appearance for example..
        * @param aDrawNow If <code>EDrawNow</code> the Menu pane is redrawn. If <code>ENoDrawNow</code> the Menu pane is not redrawn
        */
        IMPORT_C void FocusChanged(TDrawNow aDrawNow);

        /**
        * Completes construction of the Menu pane item from a resource. This function is called by <code>NewL()</code> and <code>NewLC()</code>..
        * @param aReader The resource reader
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
    public:

        /**
        * Adds a Menu item dynamically. This method adds a new Menu item to 
        * the Menu pane by creating a new Menu item, setting its data to 
        * <code>aMenuItem</code> and appending it to the pane's Menu item 
        * array. It updates the Menu's scrollbar to take account of the new 
        * item.
        *
        * @param aMenuItem The Menu item to add
        * @remarks This method allows the Menu item data to be added to the 
        *          Menu pane. Use this method when public variable 
        *          <code>iData</code> of object type
        *          <code>CEikMenuPaneItem</code> has been accessed directly. 
        *          Method <code>AddMenuItemL(CEikMenuPaneItem* aMenuItem)</code> 
        *          is called by this method 
        * @see
        */
        IMPORT_C void AddMenuItemL(const CEikMenuPaneItem::SData& aMenuItem);

        /**
        * Adds a new Menu item to the Menu pane. This method updates the 
        * Menu's scrollbar to take account of the new item. <b>Note</b>:
        * The item is appended after the existing items.
        *
        * @see InsertMenuItemAtL()
        * @param aMenuItem The Menu item to add
        * @remarks This method is also called by 
        *          <code>AddMenuItemL(const CEikMenuPaneItem::SData& aMenuItem)</code>.
        *          This method is called when methods in <code>CEikMenuPaneItem</code>
        *          have been used to complete the object's construction
        * @see
        */
        IMPORT_C void AddMenuItemL(CEikMenuPaneItem* aMenuItem);

        /**
        * Inserts a new Menu item. The item is inserted into the Menu pane's 
        * list of Menu items at the position identified by <code>aIndex</code>. 
        * This is done by creating a new Menu item, setting its data to 
        * <code>aMenuItemData</code> and inserting it into the pane's Menu. 
        * This method also updates the Menu's scrollbar to take 
        * account of the new item. If the index is beyond the end of the array,
        * the item is appended to it.
        *
        * @param aMenuItemData The data for the new Menu item
        * @param aIndex The index into the Menu pane's array of Menu items at 
        *               which to insert the new Menu item
        * @remarks If a Menu pane has three Menu items, the index position for 
        *          the first item is <code>0</code> and the index position for 
        *          the third (last) item is <code>2</code>. A new item can be 
        *          inserted in any of the existing index positions or at the 
        *          end of the Menu pane in index position <code>3</code>. 
        *          Adding the item to index position <code>0</code> or <code>1</code> 
        *          results in all of the items following the inserted item  
        *          being shifted by one index position. Use this method when 
        *          public variable <code>iData</code> of object type
        *          <code>CEikMenuPaneItem</code> has been accessed directly
        * @see
        */
        IMPORT_C void InsertMenuItemAtL(const CEikMenuPaneItem::SData& aMenuItemData, TInt aIndex);

        /**
        * Inserts a new Menu item at index <code>aIndex</code> in the Menu
        * pane. Updates the Menu's scrollbar to take account of the new item. 
        * If the index is beyond the end of the Menu pane's array of Menu items,
        * the item is appended to the array.
        *
        * @param aMenuItem The new Menu item
        * @param aIndex The index into the Menu pane's array of Menu items at 
        *               which to insert the new Menu item
        * @remarks If a Menu pane has three Menu items, the index position for 
        *          the first item is <code>0</code> and the index position for 
        *          the third (last) item is <code>2</code>. A new item can be 
        *          inserted in any of the existing index positions or at the 
        *          end of the Menu pane in index position <code>3</code>. 
        *          Adding the item to index position <code>0</code> or <code>1</code> 
        *          results in all of the items following the inserted item 
        *          being shifted by one index position
        * @see
        */
        IMPORT_C void InsertMenuItemAtL(CEikMenuPaneItem* aMenuItem, TInt aIndex);

        /**
        * Deletes the specified item in the Menu pane.
        *
        * @param aCommandId The Menu item to delete
        * @remarks The memory assigned to the item object is deleted
        * @see
        */
        IMPORT_C void DeleteMenuItem(TInt aCommandId);

        /**
        * Gets a reference to the data in the specified Menu item.
        *
        * @param aCommandId The Menu item for which data is obtained
        * @return the Menu item's data
        * @remarks
        * @see
        */

        IMPORT_C CEikMenuPaneItem::SData& ItemData(TInt aCommandId);

        /**
        * Gets a pointer to the specified Menu item. This method also gets the 
        * position of the item in the Menu pane. It panics if there are no 
        * Menu items in the Menu pane. 
        *
        * @param aCommandId The ID of the Menu item for which a pointer is 
        *                   returned
        * @param aPos On return, the position of the Menu item with an ID of 
        *             <code>aCommandId</code>
        * @return a pointer to the Menu item with an ID of 
        *         <code>aCommandId</code>
        * @remarks
        * @see
        */
        IMPORT_C CEikMenuPaneItem* ItemAndPos(TInt aCommandId,TInt& aPos);

        /**
        * Displays the Menu pane with the corner identified by
        * <code>aTargetType</code> in the position specified by
        * <code>aTargetPos</code>. This method uses <code>aMinWidth</code> to 
        * calculate the area required to display the Menu pane, taking into 
        * account whether the Menu is a cascading Menu or popup Menu.
        *
        * @param aHotKeyTable Optional hotkey table
        * @param aTargetPos The position of the corner of the Menu pane 
        *                   identified by <code>aTargetType</code>
        * @param aMenuPaneTitle The Menu pane's title
        * @param aMinWidth The minimum width of the Menu's title
        * @param aTargetType The corner of the Menu pane to which 
        *                    <code>aTargetPos</code> relates. The default 
        *                    position is the top left corner
        * @remarks This method is called by the framework
        * @see See eikdef.h for the definition on TPopupTargetPosType 
        */
        IMPORT_C void StartDisplayingMenuPane(const CEikHotKeyTable* aHotKeyTable,
                                              const TPoint& aTargetPos, 
                                              const CEikMenuPaneTitle* aMenuPaneTitle,
                                              TInt aMinWidth,  
                                              TPopupTargetPosType aTargetType = EPopupTargetTopLeft);

        /**
        * Sets the text in a Menu item.
        *
        * @param aCommandId The command (as defined in an .hrh file) associated 
        *                   with this Menu item. This identifies the Menu item 
        *                   whose text is to be set
        * @param aDes The new text
        * @remarks
        * @see
        */
        IMPORT_C void SetItemTextL(TInt aCommandId,const TDesC& aDes);

        /**
        * Sets the text in a Menu item from resource.
        * 
        * @param aCommandId The command (as defined in an .hrh file) associated 
        *                   with this Menu item. This identifies the Menu item 
        *                   whose text is to be set
        * @param aRid The resource ID of the Menu item text
        * @remarks
        * @see
        */
        IMPORT_C void SetItemTextL(TInt aCommandId,TInt aRid);

        /**
        * Dims or undims a Menu item. Dimming indicates that user input cannot 
        * be accepted.
        *
        * @param aCommandId The command associated with this Menu item 
        *                   (defined in an .hrh file) 
        * @param aDimmed <code>ETrue</code> to dim this Menu item; 
        *                <code>EFalse</code> to undim it
        * @remarks This identifies the Menu item 
        *          whose text is to be dimmed or undimmed
        * @see
        */
        IMPORT_C void SetItemDimmed(TInt aCommandId,TBool aDimmed);

        /**
        * Sets the state of the specified Menu item.
        *
        * @param aCommandId The command (as defined in an .hrh file) associated 
        *                   with this Menu item. This identifies the Menu item 
        *                   for which the state is set or unset
        * @param aButtonState <code>EEikMenuItemSymbolOn</code> or 
        *                     <code>EEikMenuItemSymbolIndeterminate</code>
        * @remarks
        * @see
        */
        IMPORT_C void SetItemButtonState(TInt aCommandId,TInt aButtonState);

        /**
        * Sets the selected Menu item.
        *
        * @param aSelectedItem The Menu item to set as selected
        * @remarks
        * @see
        */
        IMPORT_C void SetSelectedItem(TInt aSelectedItem);

        /**
        * Gets the position of the selected Menu item.
        *
        * @return The position of the selected Menu item contained on the Menu pane
        * @remarks Each item is associated with an index position on the Menu 
        *          pane. For example, item one occupies index position 
        *          <code>0</code>, item two occupies index 
        *          position <code>1</code>, and so on
        * @see
        */
        IMPORT_C TInt SelectedItem() const;

        /**
        * Closes and destroys any current cascade Menu and takes focus back. 
        * If no cascade Menu exists, this method does nothing.
        *
        * @remarks
        * @see
        */
        IMPORT_C void CloseCascadeMenu();

        /**
        * Sets the array containing the list of Menu items for the current 
        * Menu pane.
        *
        * @param aItemArray The Menu item array for the Menu pane
        * @remarks
        * @see
        */
        IMPORT_C void SetItemArray(CItemArray* aItemArray);

        /**
        * Set Menu item array ownership.
        *
        * @param aOwnedExternally If <code>ETrue</code>, the Menu pane's 
        *                         Menu item array is set as externally owned; 
        *                         if <code>EFalse</code>, the Menu pane's Menu 
        *                         item array is set as not externally owned
        * @remarks If the item array is marked as owned externally, the 
        *          <code>CEikMenuPane</code> object does not delete the item array
        *          and its resources. It is up to the external owner to do so. An 
        *          item array contains the items positioned on the Menu pane
        * @see
        */
        IMPORT_C void SetItemArrayOwnedExternally(TBool aOwnedExternally);

        /**
        * Sets the specified button to launch the Menu pane.
        *
        * @param aButton  The button to set as launching the Menu
        * @remarks
        * @see
        */
        IMPORT_C void SetLaunchingButton(CEikButtonBase* aButton);

        /**
        * Moves the Menu pane highlight to a newly selected Menu item 
        * identified by <code>aNewSelectedItem</code>. Scrolls the Menu to 
        * show the new selected item, if necessary, and redraws only the newly 
        * selected item and the currently selected item.
        *
        * @param aNewSelectedItem the newly selected Menu item
        * @remarks
        * @see
        */
        IMPORT_C void MoveHighlightTo(TInt aNewSelectedItem);

        /**
        * Returns the number of Menu items in a displayed Menu pane.
        * 
        * @return The number of Menu items in the Menu pane
        * @remarks If no items exist, the value <code>0</code> is returned
        * @see
        */
        IMPORT_C TInt NumberOfItemsInPane() const;

        /**
        * Closes the Menu pane. Destroys the command button array container, if 
        * one exists, and closes the window, if the Menu pane owns one.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void Close();

        /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType The type of key event, either: <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @param aConsumeAllKeys If <code>ETrue</code>, this method returns
        *                        <code>EKeyWasConsumed</code> regardless of 
        *                        whether it was used. If <code>EFalse</code>,
        *                        the key event is consumed, if possible, and 
        *                        either <code>EKeyWasConsumed</code> or
        *                        <code>EKeyWasNotConsumed</code> is returned,
        *                        as appropriate
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType,TBool aConsumeAllKeys); // not available before Platform 004

        /**
        * Used to set whether the scrollbar occupies the left side of the Menu pane. Now does nothing.
        * 
        * @deprecated
        * @param aOnLeft Not used
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetScrollBarOnLeft(TBool aOnLeft);

        /**
        * Does nothing.
        * 
        * @deprecated
        * @param aArrowHead Not used
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void SetArrowHeadScrollBar(TBool aArrowHead);

        /**
        * Returns the index of the Menu item with a command ID of 
        * <code>aCommandId</code>. This method panics if <code>aCommandId</code>
        * does not exist. Each item in a Menu pane occupies an index position in a 
        * container array. The first item is placed in index <code>0</code>, 
        * the second in index <code>1</code> and so on.
        * 
        * @param aCommandId The command ID of the Menu item for which the index
        *                   is returned
        * @return the index of the Menu item with a command ID of 
        *         <code>aCommandId</code>
        * @remarks
        * @see
        */
        IMPORT_C TInt MenuItemIndex(TInt aCommandId);

        /**
        * Returns the <code>CommandId</code> of the specified Menu item. This 
        * method panics if <code>aIndex</code> does not exist. It also panics 
        * if the index is out of range. Each item in a Menu pane occupies an 
        * index position in a container array. The first item is placed in 
        * index <code>0</code>, the second in index <code>1</code>, and so on.
        * 
        * @param aIndex The index of the Menu item for which the command ID is 
        *               returned
        * @return the command ID of the Menu item at <code>aIndex</code>
        * @remarks
        * @see
        */
        IMPORT_C TInt MenuItemCommandId(TInt aIndex);

        /**
        * Returns a pointer to the associated button group. Ownership is not 
        * transferred.
        * 
        * @return a pointer to the associated button group. If there is no such
        *         group, this is <code>NULL</code>
        * @remarks The button group is the container holding the CBA buttons
        * @see
        */
        IMPORT_C CEikButtonGroupContainer* MenuButtons() const;

        /**
        * Specifies that the Menu pane should act like a Menu bar and
        * use the Menu bar's border - for pop-out Menu panes that should
        * look like a Menu bar.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void UseMenuBarBorder();

        /**
        * Set the level of the Menu pane.
        * 
        * @param aValue The new level
        * @remarks
        * @see
        */
        IMPORT_C void SetLevel(TMenuPaneLevel aValue);
    public:
     
        /** @internal */
        TInt DefaultSelectedItemIndex(TInt aCurrentItemSelection) const;
        /** @internal */
        void SetMenuBar(CEikMenuBar& aBar);
        /** @internal */
        void SetMenuObserver(MEikMenuObserver* aMenuObserver);
        /** @internal */
        void HandleClose(TBool aCascadeMenu=EFalse);
        /** @internal */
        void AttemptLaunchCascadeMenuL(TInt aIndex);
        /** @internal */
        TBool PaneOrCascadeIsFocused() const;
        /** @internal */
        void CancelCascadeFocus();
    private:
        enum 
            { 
            ECopyContextToScrollBar =0x01, 
            EFadedBehind            =0x02, 
            ELeftAdornmentExist     =0x04, 
            ERightAdornmentExist    =0x08,
            EDisableFadingBehind    =0x10
            };
        enum TUpadteItemValues
            {
            ENoUpdate           =0x00,
            EUpdateItemValues   =0x01,
            };
        enum TValidSize
            {
            EValidCurrentSize   =0x00,
            EInvalidCurrentSize =0x01,
            };
        enum TScrlButtonState
            {
            EUnpressed = 0,
            EPressed,
            EDisabled
            };
    private:
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
        void HandleScrollEventL(TEikScrollEvent aEventType);
        TRect ViewRect() const;
        TInt NumberOfItemsThatFitInView(TValidSize aValidSize) const;
        TInt TotalItemHeight() const;
        void ScrollToMakeItemVisible(TInt aItemIndex);
        TBool IsItemVisible(TInt aItemIndex) const;
        void Scroll(TInt aAmount, TBool aDrawNow);
        TBool CheckCreateScroller();
        void CheckCreateScrollerL();
        void ResetItemArray();
        void CreateItemArrayL();
        TInt MaxIconWidth() const;
        TMargins8 Margins() const;
        TMargins SumOfMarginsAndBorders() const;
        TRect InnerRect() const;
        void ProcessCommandToAllObserversL(TInt aCommandId);
        void SetVirtualCursorStateL(TBool aSetSuspended) const;
        void UpdateItemHeightForIcon(const CEikMenuPaneItem& aItem, TInt aItemTextTopSpace, TInt aItemTextBottomSpace);
        TSize CalculateSize(const CItemArray& aItemArray, TInt& aMenuPaneFlags, TInt& aHotkeyColWidth, TBool aUpdateItemValues);
        TInt NextItemThatCanBeSelected(TInt aCurrentMenuPaneItem, const TKeyEvent& aKeyEvent) const;
        TInt NumOfItemsThatRefuseHighlightAboveCurrent(TInt aCurrentItem) const;
        void DrawScrollButtons(CWindowGc& aGc) const;
        void DrawScrollButtonsNow() const;
        TBool IsScrolledToTop() const;
        TBool IsScrolledToBottom() const;
        void UpdateScrolling();
        void HandleSkinResourceLoadL();
        void DrawBorder(CWindowGc& aGc, const TRect& aRect) const;
        TMargins BorderMargins() const;
        TRect InnerRect(const TRect& aOuterRect) const;
        void LoadBorderBitmapsL();
        TBool UsingMenuBarBorder() const;
        const CFont* Font() const;
        void PrepareGcForDrawingItems(CWindowGc& aGc) const;
        void FadeBehindMenu(TBool aFade);
        void MoveHighlightToAndOpenIfSubmenuL(TInt aNewSelectedItem);
        void GiveCascadeFocus();
        TBool HiddenMenuBar() const;
        void SetPointerOutsideMenu(TBool aState);
        void DrawSelectedItem();
    private:
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
        TAny* iDummy;
        CMenuScroller* iScroller;
        CEikButtonBase* iLaunchingButton;
        CEikMenuBar* iMenuBar;
        CEikMenuCbaContainer* iCbaContainer;
        CMenuPaneExtra* iExt;
    };

inline CGulIcon* CEikMenuPaneItem::Icon() const
    { 
    return iIcon; 
    }

inline TBool CEikMenuPane::IsScrolledToTop() const
    {
    return IsItemVisible(0);
    }

inline TBool CEikMenuPane::IsScrolledToBottom() const
    {
    if (iItemArray->Count() > 0)
        return IsItemVisible(iItemArray->Count()-1);
    else
        return ETrue;
    }

#endif  // EIKMENUP_H

// End of File
