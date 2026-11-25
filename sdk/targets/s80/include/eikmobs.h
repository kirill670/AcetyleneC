/*
* =============================================================================
*  Name        : eikmobs.h
*  Part of     : UIKON
*  Interface   : Menu Base API
*  Description : Menu observer classes.
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
* =============================================================================
*/


#ifndef EIKMOBS_H
#define EIKMOBS_H

// INCLUDES
#include <eikcmobs.h>
#include <w32std.h>
#include <coedef.h>

// FORWARD DECLARATIONS
class CCoeControl;
class CEikMenuPane;
class CEikMenuBar;
class CEikHotKeyTable;
class TPoint;

/** 
 * The <code>MEikMenuObserver</code> class provides the Menu observer interface.
 * Menu observers cooperate with Menu bars and Menu panes, initializing them 
 * before display and responding to Menu events appropriately. 
 * <code>CEikAppUi</code> implements <code>MEikMenuObserver</code>, so these 
 * methods may be implemented on an application's AppUI.
 *
 * @publishedAll
 * @released 
 * @lib
 * @since
 */
class MEikMenuObserver : public MEikCommandObserver

    {
    public:
    /** The <code>TMenuType</code> enumeration specifies the Menu types. */
    enum TMenuType
        {
        /** the Menu pane */
        EMenuPane,
        /** the Menu bar */
        EMenuBar
        };
    public:

        /**
        * Responds to a user's attempt to select a dimmed item by displaying a
        * message, <code>CEikonEnv::InfoMsg()</code>, to indicate that the item is
        * unavailable.
        *
        * @param aCommandId The command ID for the Menu item
        * @remarks
        * @see
        */
        IMPORT_C virtual void HandleAttemptDimmedSelectionL(TInt aCommandId);

       /**
        * This method is called when a hotkey event is offered to a Menu bar 
        * or a Menu pane to determine whether to send the corresponding command 
        * to the application when the associated Menu pane or item is dimmed.
        *
        * @param aCommandId The command corresponding to the selected hotkey
        * @return <code>ETrue</code> if the command should be passed to the 
        *         application (this is the default); <code>EFalse</code> if 
        *         the command should not be passed to the application
        * @remarks
        * @see
        */
        IMPORT_C virtual TBool CheckHotKeyNotDimmedL(TInt aCommandId);

       /**
        * Restores the Menu <code>aMenuControl</code>.
        *
        * @param aMenuControl The Menu to be restored
        * @param aResourceId The Menu's ID
        * @param aType The type of Menu being restored
        * @remarks The Menu is restored from the definition in the application's
        *          resource file for a Menu bar or pane
        * @see CCoeControl
        */
        IMPORT_C virtual void RestoreMenuL(CCoeControl* aMenuControl,
                                           TInt aResourceId,
                                           TMenuType aType);

       /**
        * Dynamically initializes a Menu pane. The Uikon framework calls this 
        * method immediately before 
        * the Menu pane is activated. Typically, this method should determine
        * the value of application data and initialize Menu items accordingly.
        * This includes dimming Menu items, changing their text, setting the 
        * state of checked items and option buttons (also known as radio 
        * buttons) and dynamically adding items to a Menu.
        *
        * @param aResourceId The resource ID identifying the Menu pane to 
        *                    initialize
        * @param aMenuPane The object representation of the Menu pane
        * @remarks The object type is <code>CEikMenuPane</code>
        * @see
        */
        IMPORT_C virtual void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);

       /**
        * Dynamically initializes a Menu bar. The Uikon framework calls this 
        * method, if it is implemented in a Menu observer, immediately before 
        * the Menu bar is activated. Typically, this method should determine
        * the value of application data and initialize Menu items accordingly.
        * This includes dimming Menu items, changing their text, setting the 
        * state of checked items and option buttons (also known as radio 
        * buttons) and dynamically adding items to a Menu.
        *
        * @param aResourceId The resource ID identifying the Menu bar to 
        *                    initialize
        * @param aMenuBar The in-memory representation of the Menu bar
        * @remarks
        * @see
        */
        IMPORT_C virtual void DynInitMenuBarL(TInt aResourceId,CEikMenuBar* aMenuBar);

       /**
        * This method is invoked by the input-handling methods of 
        * <code>CEikMenuBar</code>. It may be overridden to handle the display
        * of the Menus launched from the sidebar.
        *
        * @param aResourceId The resource ID identifying the Menu to launch
        * @param aPos The position of the Menu's reference point. For sidebar 
        *             Menus, this is the top-right corner
        * @param aModifiers The key modifiers held when the Menu was invoked
        * @param aTable The Menu bar's hotkey items
        * @remarks Sidebars are not supported in Series 90
        * @see
        */
        IMPORT_C virtual void HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,TInt aModifiers,const CEikHotKeyTable* aTable);

       /**
        * This method is called if a key that is not used by the Menu is 
        * pressed while the observer's Menu is displaying.
        *
        * @param aKeyEvent The key event the Menu is offering to the 
        *                  application
        * @param aType The event code type
        * @remarks
        * @see
        */
        IMPORT_C virtual void OfferKeyToAppL(const TKeyEvent& aKeyEvent,TEventCode aType);
    
       /** 
        * Called by the Uikon framework to handle the emphasizing or 
        * de-emphasizing of a Menu window. <code>CEikMenuBar</code> objects 
        * call this on their observer to emphasize themselves when they are 
        * displayed and de-emphasize themselves when they are not displayed.
        * 
        * @param aMenuControl The Menu control
        * @param aEmphasis <code>ETrue</code> to emphasize the Menu; 
        *        <code>EFalse</code> otherwise
        * @remarks When emphasized, all titles (that is, Menu panes in the Menu 
        *          bar) are displayed, unless dimmed. For a Menu pane, all 
        *          contained items are displayed, unless dimmed
        * @see
        */
        virtual void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis)=0;
    private:
        IMPORT_C virtual void Reserved_1_MenuObserver();
    };

/** 
 * The <code>MEikAutoMenuObserver</code> class provides additional 
 * functionality to an auto Menu title, in the form of an 
 * <code>OfferHotKeyL()</code> method, which is not required in the normal 
 * <code>MEikMenuObserver</code>. Auto Menu titles are used to ensure that 
 * some Menu panes appear in every Menu constructed for an application. 
 * 
 * @publishedAll 
 * @released 
 */
class MEikAutoMenuObserver : public MEikMenuObserver

    {
    public:
       /** 
        * Offers the specified hotkey to the auto Menu title. Implement this 
        * method to handle events from an auto Menu. 
        *
        * @param aKeyEvent The key event
        * @param aType The type of key event
        * @return The auto Menu title's response
        * @remarks Auto Menu titles are used to ensure that some Menu panes 
        *          appear in every Menu constructed for an application
        * @see
        */
        virtual TKeyResponse OfferHotKeyL(const TKeyEvent& aKeyEvent,TEventCode aType)=0;
    public: // from MEikMenuObserver

       /**
        * Sets the specified control's emphasis.
        *
        * @param aMenuControl The control for which emphasis is set
        * @param aEmphasis If <code>ETrue</code> the Menu is emphasized. If
        *            <code>EFalse</code> the Menu is not emphasized
        * @remarks When emphasized, all titles (that is, Menu panes in the Menu 
        *          bar) are displayed, unless dimmed. For a Menu pane, all 
        *          contained items are displayed, unless dimmed
        * @see CCoeControl
        */
        IMPORT_C void SetEmphasis(CCoeControl* aMenuControl,TBool aEmphasis);
    private:
        IMPORT_C virtual void Reserved_1_MenuObserver();
    };

#endif  // EIKMOBS_H

// End of File
