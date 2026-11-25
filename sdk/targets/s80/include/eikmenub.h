/*
* ==============================================================================
*  Name        : eikmenub.h
*  Part of     : CKON
*  Interface   : Menubar API
*  Description : Menu pane, Menu pane title and Menu bar title classes.
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


#ifndef EIKMENUB_H
#define EIKMENUB_H

// INCLUDES
#include <eikdef.h>
#include <eikbctrl.h>
#include <eikmenup.h>

// FORWARD DECLARATIONS
class CEikHotKeyTable;
class CCknSkinBase;

/**
* The <code>CEikMenuBarTitle</code> class defines a Menu bar title and 
* provides some of the functionality required to display it. The title is
* descriptive text for a Menu pane contained in the Menu bar.
*
* @lib eikcoctl.lib
* @since 6.0
*/
class CEikMenuBarTitle : public CBase
    {
    public:

    /** 
     * The anonymous enumeration defines attributes for the Menu bar title, 
     * that is, the Menu pane.
     */
    enum
        {
        /** dims the title */
        ETitleDimmed = 0x01,
        /** used when the icon is owned externally. This tells the Menu not to delete the icon */
        EIconOwnedExternally = 0x02
        };

    /** 
     * The structure <code>SData</code> defines attributes for the Menu bar 
     * title. 
     */
    struct SData
        {
        enum 
            { 
            /** specifies the maximum length of the text */
            ENominalTextLength=SLafMenuBar::ENominalTextLength 
            };
        /** stores the resource ID of the Menu pane */
        TInt iMenuPaneResourceId;
        /** the text description for the Menu pane */
        TBuf<ENominalTextLength> iText;
        };

    public:

        /**
        * The default object constructor.
        */
        IMPORT_C CEikMenuBarTitle();

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikMenuBarTitle();

        /**
        * Constructs a new icon for the title. The title is the descriptive text
        * for a Menu pane contained in the Menu bar. Takes ownership of the picture
        * bitmap and the mask bitmap, unless they are externally owned.
        * 
        * @param aBitmap The bitmap to use in the icon
        * @param aMask The mask to use in the icon
        * @remarks The bitmap appears to the left of the title text
        * @see SetBitmapsOwnedExternally()
        */
        IMPORT_C void CreateIconL(CFbsBitmap* aBitmap, CFbsBitmap* aMask);

        /**
        * Gets a pointer to the title icon's bitmap.
        * This does not imply transfer of ownership.
        * 
        * @return a pointer to the title icon's bitmap
        * @remarks
        * @see
        */
        IMPORT_C CFbsBitmap* IconBitmap() const;

        /**
        * Gets a pointer to the title icon's mask.
        * This does not imply transfer of ownership.
        * 
        * @return a pointer to the title icon's mask
        * @remarks
        * @see
        */
        IMPORT_C CFbsBitmap* IconMask() const;

        /**
        * Sets the Menu pane's bitmap and mask to be owned externally.
        * This method affects the state of owned CGulIcon member.
        *
        * @param aOwnedExternally If <code>ETrue</code> the icon is set as 
        *                         externally owned. If <code>EFalse</code> the
        *                         icon is set as not being externally owned
        * @remarks This method sets the flag for an icon of type 
        *          <code>CGulIcon</code> rather than for the Menu title
        * @see CGulIcon::SetIconOwnedExternally(TBool aOwnedExternally)
        */
        IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);

        /**
        * Sets the title icon. 
        * 
        * @param aIcon The title's icon
        * @remarks Ownership depends on the value set in 
        *          <code>SetBitmapsOwnedExternally</code> and 
        *          <code>SetIconOwnedExternally</code>. The bitmaps are owned 
        *          by the icon. The icon can be owned internally or externally, 
        *          <code>SetIconOwnedExternally</code>, by the 
        *          <code>CEikMenuBarTile</code>. The bitmaps can be owned 
        *          internally or externally by the icon 
        *          <code>SetBitmapsOwnedExternally</code>
        * @see
        */
        IMPORT_C void SetIcon(CGulIcon* aIcon);

        /**
        * Sets the bitmap for the icon. Transfers ownership unless the bitmaps
        * are owned externally.
        * 
        * @param aBitmap The bitmap to use
        * @remarks
        * @see
        */
        IMPORT_C void SetIconBitmapL(CFbsBitmap* aBitmap);

        /**
        * Sets the mask for the icon. Transfers ownership unless the bitmaps 
        * are owned externally.
        * 
        * @param aMask The mask to use
        * @remarks
        * @see
        */
        IMPORT_C void SetIconMaskL(CFbsBitmap* aMask);

        /**
        * Sets external ownership of the title icon.
        * 
        * @param aOwnedExternally If <code>ETrue</code> the icon is set as 
        *        externally owned. If <code>EFalse</code> the icon is set as 
        *        not being externally owned
        * @remarks Unlike <code>SetBitmapsOwnedExternally</code>, this method 
        *          sets the value for public variable <code>iTitleFlags</code>
        *          for a Menu title object of type <code>CEikMenuBarTitle</code>
        * @see SetBitmapsOwnedExternally()
        */
        IMPORT_C void SetIconOwnedExternally(TBool aOwnedExternally);

    public:

        /**
        * Internal to Symbian
        * @internal
        * @deprecated.
        */
        IMPORT_C void DrawIcon(CWindowGc& aGc, const TRect& aRect, TInt aLeftMargin) const;

    public:

        /**
        * Returns a pointer to the Menu bar title icon.
        * 
        * @return the icon
        * @remarks
        * @see
        */
        inline CGulIcon* Icon() const;

    public: // other functions
        /**
        * @internal
        */
        void CalculateBaseLine(TInt& aBaseLine, TInt& aTitleHeight);
        
        /**
        * @internal
        */
        TInt IconWidth() const;

    public:
        /** the resource data store */
        SData iData;
        /** the position of the title */
        TInt iPos;
        /** the flags store */
        TInt iTitleFlags;
        /** the height of the title, in pixels */
        TInt iHeight;
    private:
        CGulIcon* iIcon;
    };


/**
* The <code>CEikMenuBar</code> class enables the construction and manipulation 
* of Menu bars. Menu bars are defined using the resource file <code>MENU_BAR</code>
* keyword. 
*
* @lib eikcoctl.lib
* @since 6.0
*/
class CEikMenuBar : public CEikBorderedControl
    {
    public:

    /** 
     * The <code>SCursor</code> struct holds a location of a Menu item within 
     * a Menu pane. 
     */
    struct SCursor
        {
        /** the relevant Menu pane */
        TInt iMenuPaneIndex;
        /** the relevant Menu item */
        TInt iMenuItemIndex;
        };
    
    /** 
     * The <code>SPosition</code> structure holds the Menu title resource ID 
     * together with an <code>SCursor</code> structure.
     */
    struct SPosition
        {
        /** the Menu resource ID */
        TInt iMenuId;
        /** see <code>SCursor</code> */
        SCursor iMenuCursorPos;
        };

    friend class CEikMenuPaneTitle;
    private:
    enum {ENothingSelected=-1};
    public:

        /**
        * The object destructor. If the array is externally owned, this method 
        * removes everything associated with the Menu bar, except the array 
        * that holds the Menu titles (that is, the Menu panes).
        */
        IMPORT_C ~CEikMenuBar();

        /**
        * The object constructor.
        */
        IMPORT_C CEikMenuBar();

    private: // framework
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
        IMPORT_C void Draw(const TRect& aRect) const;
        IMPORT_C TCoeInputCapabilities InputCapabilities() const; // not available before Release 006
    public:

        /**
        * The <code>CTitleArray</code> class enables construction and 
        * destruction of an array of information about Menu bar titles.
        * This class is embedded in <code>CEikMenuBar</code>.
        *
        * @lib eikcoctl.lib 
        * @since
        */
        class CTitleArray : public CArrayPtrFlat<CEikMenuBarTitle>
            {
        public:

            /**
            * The object destructor. This method also destroys all Menu bar 
            * titles.
            */
            IMPORT_C ~CTitleArray();

            /**
            * The default object constructor.
            */
            IMPORT_C CTitleArray();
            };

    public: // new functions

        /**
        * Allocates and constructs a Menu bar. This constructor sets an 
        * observer for the Menu, creates a hotkey table (optional), and creates a 
        * Menu title array and an array to hold Menu positions.
        *
        * @param aMenuObserver The Menu's observer
        * @param aHotKeyResourceId The ID of the resource, of type 
        *        <code>HOTKEY</code> from which the hotkey table is created. 
        *        This is optional
        * @param aMenuTitleResourceId The ID of the resource, of type 
        *        <code>MENU_BAR</code> from which the Menu title array is 
        *        created. This is optional
        * @remarks The <code>CEikAppUi</code> class inherits from mixin class 
        *          <code>MEikMenuObserver</code> and implements 
        *          <code>DynInitMenuPaneL</code>
        * @see
        */
        IMPORT_C void ConstructL(MEikMenuObserver* aMenuObserver,TInt aHotKeyResourceId=0,TInt aMenuTitleResourceId=0);

        /**
        * Constructs a Menu bar using the specified resource reader.
        * 
        * @param aReader The resource reader to use
        * @remarks This method is called by the framework
        * @see
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Allows a Menu bar to be replaced with another during run-time.
        * For the replacement Menu bar's resource ID to be used as one of the 
        * method's parameters, it must be defined in the application's resource 
        * file using the <code>MENU_BAR</code> keyword. The replacement Menu 
        * bar may have an associated hotkey also defined in the resource file.
        * If <code>EDisplayNow</code> is <code>ETrue</code>, the Menu bar and 
        * its related Menu pane are automatically displayed.
        *
        * @param aHotKeyResourceId The resource, of type 
        *        <code>HOTKEY</code>, that defines the hotkeys associated with
        *        this Menu. Specifying a new set of hotkeys for the new Menu 
        *        means that hotkeys are context-dependent and the same hotkey 
        *        can be used to perform different commands
        * @param aMenuTitleResourceId The resource, of type 
        *        <code>MENU_BAR</code>, that defines the Menu to use
        * @param aDisplayNow If <code>ETrue</code>, displays the new Menu bar 
        *        immediately. If <code>EFalse</code>, displays the new Menu bar 
        *        when invoked by the user
        * @remarks
        * @see
        */
        IMPORT_C void ChangeMenuBarL(TInt aHotKeyResourceId=0,TInt aMenuTitleResourceId=0,TInt aDisplayNow=ETrue);

        /**
        * Sets the hotkey table.
        * 
        * @param aHotKeyTable The hotkey table
        * @remarks A hotkey table is an array for hotkey commands and their 
        *          associated key codes and modifiers. This method is used 
        *          whether modifications to the key table are required
        * @see eikhkeyt.h
        */
        IMPORT_C void SetHotKeyTable(CEikHotKeyTable* aHotKeyTable);

        /**
        * Sets the Menu's resource ID to the one defined in the resource file.
        * 
        * @param aMenuTitleResourceId The resource ID
        * @remarks The title resource ID being referred is that of a Menu pane
        * @see
        */
        IMPORT_C void SetMenuTitleResourceId(TInt aMenuTitleResourceId);

        /**
        * Sets the Menu title array. If it is not externally owned, this 
        * method removes the current array.
        * 
        * @param aTitleArray The title array
        * @remarks The title array contains the titles (that is, the text 
        *          description) of each Menu pane contained in the Menu bar
        * @see
        */
        IMPORT_C void SetMenuTitleArray(CTitleArray* aTitleArray);

        /**
        * Sets the title array as externally owned.
        *
        * @param aOwnedExternally If <code>ETrue</code>, sets the Menu bar 
        *                         title array as externally owned. If 
        *                         <code>EFalse</code>, sets the Menu bar title 
        *                         array as not being externally owned
        * @remarks If the title array is owned externally, the Menu bar 
        *          object does not need to delete the object and its contents.
        *          Otherwise ownership and responsibility for the destruction
        *          of the title array rests with the Menu bar object
        * @see
        */
        IMPORT_C void SetTitleArrayOwnedExternally(TBool aOwnedExternally);

        /**
        * Sets the cursor to the specified Menu pane and Menu item.
        *
        * @param aCursor The Menu pane and Menu item to which the cursor is set
        * @return a structure holding two index values. The first is the Menu 
        *         pane in the Menu bar and the second is the index position of 
        *         a Menu item in the Menu pane
        * @remarks The Menu bar is not expanded to show the 
        *          change
        * @see SCursor
        */
        IMPORT_C SCursor SetMenuCursor(const SCursor& aCursor);

        /**
        * Stops displaying the Menu bar. This method causes the Menu bar to 
        * disappear from the screen until the user invokes it again. In 
        * most circumstances, this is performed by the Uikon framework, so an 
        * application program does not normally need to use this method.
        *
        * @remarks An example of when this method is called by the application 
        *          is when an embedded object is opened and then closed. The 
        *          existing Menu bar may still reflect items related to the 
        *          embedded object that are no longer valid. This method allows 
        *          the Menu bar not to be displayed. Then changes are made to 
        *          the Menu bar, before calling <code>TryDisplayMenuBarL()</code> 
        *          to display it
        * @see
        */
        IMPORT_C void StopDisplayingMenuBar();

        /**
        * Displays the Menu bar. If the Menu is not already displayed, this 
        * method displays the Menu bar and allows the user to make a selection.
        * In most circumstances, this is performed by the framework, so 
        * an application program does not normally need to use this method.
        * 
        * @remarks
        * @see StopDisplayingMenuBar()
        */
        IMPORT_C void TryDisplayMenuBarL();

        /**
        * Highlights the specified item. The <code>aNewSelectedTitle</code> 
        * value identifies the new Menu title to highlight. While 
        * <code>aNewSelectedItem</code>, if specified, is used to identify a 
        * Menu pane item to highlight. This method also redraws any previously 
        * highlighted item so that it is no longer highlighted. If the 
        * specified item is dimmed, and so cannot accept input, this method 
        * calls <code>HandleAttemptDimmedSelectionL()</code> on the Menu's 
        * observer.
        *
        * @param aNewSelectedTitle The ID of the Menu bar title to highlight
        * @param aNewSelectedItem Optional. If supplied, this identifies the 
        *                         Menu item to highlight
        * @remarks If the value of the selected title does not exist, that is, 
        *          if it has not been created or its value is less than zero, 
        *          the method leaves with <code>KErrNoMemory</code> 
        * @see
        */
        IMPORT_C void MoveHighlightToL(TInt aNewSelectedTitle,TInt aNewSelectedItem=0);

        /**
        * Draws the specified Menu bar title.
        * 
        * @param aItem The index of the item to draw
        * @remarks A Menu pane can hold one or more Menu items. Each item in 
        *          the pane is stored in an array container. The first item is 
        *          stored in index <code>0</code>, the second in index 
        *          <code>1</code>, and so on
        * @see
        */
        IMPORT_C void DrawItem(TInt aItem) const;

        /** @internal */
        CEikHotKeyTable* HotKeyTable() const;

        /**
        * Returns the index of the selected title.
        * 
        * @return the selected title
        * @remarks
        * @see
        */
        IMPORT_C TInt SelectedTitle();

        /**
        * Gets the index of the Menu item selected by the cursor.
        *
        * @return the index of the selected Menu item
        * @remarks
        * @see
        */
        IMPORT_C TInt SelectedItem();

        /**
        * Searches for the Menu item that corresponds to the specified command.
        *
        * @param aCommandId The ID to search for. Defined in the application's 
        *                   resource file for field <code>command</code> in 
        *                   <code>MENU_ITEM</code>
        * @param aPaneIndex The index of the Menu pane. If the command ID is 
        *                   found, this variable is modified to the Menu pane 
        *                   containing the item that matches the command ID. 
        *                   If the item is not found, the value is 
        *                   <code>-1</code>
        * @param aItemIndex The index of the Menu item. If the command ID is 
        *                   found, the value of this variable is modified to 
        *                   the index of the match item. If the item is not 
        *                   found, the value is <code>-1</code> 
        * @remarks 
        * @see
        */
        IMPORT_C virtual void FindCommandIdInResourceL(TInt aCommandId,TInt& aPaneIndex,TInt& aItemIndex);

        /**
        * Changes the Menu's display area. This has no effect if the Menu is 
        * not currently visible. This method subtracts the size of the Menu 
        * bar from the <code>aRect</code> that is passed in as an argument and 
        * returns the new rectangle in a new value of <code>aRect</code>.
        *
        * @param aRect The rectangle used by the Menu and, on return, the new 
        *              rectangle to be used by the Menu
        * @remarks
        * @see
        */
        IMPORT_C void ReduceRect(TRect& aRect) const;

        /**
        * Sets the text and, optionally, the icon for the specified title.
        *
        * @param aText The title's text
        * @param aResourceId The resource ID of the title for which the text 
        *                    and icon are set
        * @param aIcon The icon. If <code>NULL</code>, no icon is set
        * @remarks If an icon is set, it is displayed to the left of
        *          the Menu pane title (that is, the descriptive text)
        * @see
        */
        IMPORT_C void SetTitleL(const TDesC& aText, TInt aResourceId, CGulIcon* aIcon = NULL);

        /**
        * Sets the specified title's dim state.
        * Dimming indicates that user input cannot be accepted.
        *
        * @param aTitleIndex The title for which the dim state is being set
        * @param aTitleDimmed If <code>ETrue</code> the title is dimmed; 
        *                     <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetTitleDimmed(TInt aTitleIndex, TBool aTitleDimmed);

        /**
        * Gets the Menu title array.
        *
        * @internal
        * @return Pointer to the Menu title array.
        * <BR><B>Type of return value:</B> CTitleArray*
        * <BR><B>Range of return value:</B> Object Reference
        * <BR><B>Contents of return value:</B> An array of titles
        */
        IMPORT_C CTitleArray* MenuTitleArray() const;

        /**
        * Finds the index of the Menu bar title that corresponds to the 
        * specific resource ID. This method returns a negative index if the 
        * title is not found.
        *
        * @param aResourceId The resource ID to search for
        * @return the index of the title with a resource ID of 
        *         <code>aResourceId</code>
        * @remarks
        * @see
        */
        IMPORT_C TInt FindIndexFromResourceId(TInt aResourceId) const;
    public:
        /**
        * @internal
        */
        void SetTitleTextL(const TDesC& aText);

        /**
        * @internal
        */
        void CalculateSizeAndPositionL();

        /**
        * @internal
        */
        MEikMenuObserver* MenuBarObserver() const;

        /**
        * @internal
        */
        void UpdateInvalidatedWindowRegion();

        /**
        * @internal
        */
        void GivePaneFocus();

        /**
        * @internal
        */
        void HasValidDragEvent();

        /**
        * Tests whether the Menu bar is using the smallest possible spacing.
        *
        * @return <code>ETrue</code> if the Menu bar is using the smallest 
        *         spacing values defined in the LAF; <code>EFalse</code> 
        *         otherwise
        * @remarks
        * @see
        */
        inline TBool UseSmallAdornments() const;
/**
* Checks whether the Menu bar is 'hidden' i.e. only the Menu pane should be 
* shown.
* Note: Using <code>MakeVisible(EFalse)</code> stops the Menu bar from getting
* key events :. bad.
* @internal
* @return ETrue if the Menu bar should be hidden, else EFalse;
* @remarks
* @see
*/
        TBool HiddenMenuBar() const;
    public: // from CCoeControl

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
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);

        /**
        * Writes the internal state of the control and its components to 
        * <code>aStream</code>.
        * Does nothing in release mode.
        * Designed to be overidden and base called by subclasses.
        *
        * @internal
        * 
        * @param aWriteStream The stream to use
        * <BR><B>Type of return value:</B> void
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    private:
        IMPORT_C void Reserved_2();
    private:
        TKeyResponse DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        TKeyResponse CheckForTaskSwitchingL(const TKeyEvent& aKeyEvent,TEventCode aType);
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
        CEikMenuBarTitle* TitleAndPos(TInt aResourceId, TInt& aPos);
        void DrawTitle(const CEikMenuBarTitle& aTitle) const;
        TBool IsTitleDimmed(TInt aTitleIndex);
        void SetVirtualCursorStateL(TBool aSetSuspended) const;
        void UpdateTitleTextBaseline();
        void OpenMenuPaneL(TInt aNewSelectedTitle, TInt aNewSelectedItem=0, TBool aIsFocused=ETrue);
        TRect InnerRect(const TRect& aOuterRect) const;
        TMargins BorderMargins() const;
        static TInt LongMenuKeyCallBack(TAny* aPtr);
        void RemovePaneFocus();
        void DrawBorder(CWindowGc& aGc, const TRect& aRect, const TRect& aDrawRect) const;
        void SetPointerOutsideMenu(TBool aState);
    private:
        struct STitleOverload
            {
            TInt iIndex;
            TBuf<CEikMenuBarTitle::SData::ENominalTextLength> iText;
            };
    private:
        class CExtraData : public CBase
            {
            public:
                CExtraData();
                ~CExtraData();
                TInt iMenuPaneTitleState;
                CPeriodic* iTimer;
                CCknSkinBase& iSkin;
                TBool iPointerOutsideMenu;
                TBool iTaskSwitching;
            };
    private:
        enum TEikMenuFlags {ETitleArrayOwnedExternally=0x01,EMenuHasItems=0x02,EMenuHasPane=0x04,EUseSmallAdornments=0x08, EAllowUpDragEventsOutsideMenu=0x10};
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
        CExtraData *iExtra;
    };


/**
* This class is not intended to be used by application programmers.
* It is documented only for completeness.
*
* @internal
* @lib eikcoctl.lib
* @since 6.0
*/
class CEikMenuPaneTitle : public CEikBorderedControl
    {
    public:

        /**
        * default constructor.
        *
        * @param aMenuBar the parent Menu ber
        * @remarks
        * @see
        */
        IMPORT_C CEikMenuPaneTitle(CEikMenuBar* aMenuBar);

        /**
        * Symbian 2nd phase constructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL();

        /**
        * Sets the selected title.
        * 
        * @param aSelectedTitle Index of the title to select
        * @remarks
        * @see
        */
        IMPORT_C void SetSelectedTitle(TInt aSelectedTitle);

        /**
        * Returns the margins.
        * 
        * @return The margins of this control
        * @remarks
        * @see
        */
        IMPORT_C TMargins Margins() const;

        /**
        * Close the Menu pane title window
        * 
        * @remarks
        * @see
        */
        IMPORT_C void Close();
    public:
        /**
        * @internal
        */ 
        TInt SelectedTitle() const;
    public: // framework

        /**
        * Draws the control.
        * 
        * @param aRect The rect in which to draw
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void Draw(const TRect& aRect) const;

        /**
        * Handle a pointer event.
        * 
        * @param aPointerEvent The pointer event
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * Get the colors used by this control.
        * 
        * @param aColorUseList The color use list. Parameter will be used for 
        *        return value
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;

        /**
        * Handle a resource change.
        * 
        * @param aType The type of resource change
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType); 

        /**
        * Write the state of the control.
        * 
        * @param aWriteStream The stream to use
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    private:
    enum { EClearTitle=0x01 };
    private:
        CEikMenuBar* iMenuBar;
        TInt iSelectedTitle;
        TInt iMenuTitleFlags;
    };


// Inlines

inline CGulIcon* CEikMenuBarTitle::Icon() const
    { return iIcon; }

inline CEikHotKeyTable* CEikMenuBar::HotKeyTable() const
    { return(iHotKeyTable); }

inline TBool CEikMenuBar::UseSmallAdornments() const
    {
        return iMenuFlags&EUseSmallAdornments;
    }


inline TBool CEikMenuBar::HiddenMenuBar() const
    {
    return iTitleArray->Count() == 1;
    }

#endif  // EIKMENUB_H

// End of File
