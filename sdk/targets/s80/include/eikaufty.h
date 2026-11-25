/*
* ==============================================================================
*  Name        : eikaufty.h
*  Part of     : UIKON
*  Interface   : Application API
*  Description : AppUI factory interface class. 
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

#ifndef EIKAUFTY_H
#define EIKAUFTY_H

// INCLUDES
#include <f32file.h>
#include <e32base.h>
#include <eikdef.h>

// FORWARD DECLARATIONS
class CEikHotKeyTable;
class CEikMenuBar;
class CEikMenuPane;
class CEikCommandButton;
class CEikToolBar;
class CEikButtonGroupContainer;
class CEikAppUi;
class CEikonEnv;
class CEikStatusPane;


/**
 * The <code>MEikAppUiFactory</code> class defines a mixin interface to break
 * the dependency of the Uikon application user interface on controls.
 * 
 * @lib eikcore.lib
 * @since 6.0
*/
class MEikAppUiFactory
    {
    public:

        /**
        * Creates controls that are independent from the resource.
        *
        * @param aAppUi The AppUI
        * @remarks
        * @see
        */
        virtual void CreateResourceIndependentFurnitureL(CEikAppUi* aAppUi) =0;

        /**
        * Gets the client rectangle for this AppUI.
        *
        * @return the area of the screen available to the application for 
        *         drawing
        * @remarks
        * @see
        */
        virtual TRect ClientRect() = 0;

        /**
        * Reads the application information for this application from the 
        * specified resource offset. 
        *
        * @param aResourceFileOffset The offset of the application information
        * @param aAppUi The AppUI
        * @remarks
        * @see
        */
        virtual void ReadAppInfoResourceL(TInt aResourceFileOffset,
                     CEikAppUi* aAppUi) = 0;
    
        /**
        * Launches a pop-up menu.
        *
        * @param aResourceId The ID of the resource that defines the menu to 
        *                    be launched
        * @param aTargetPos Position of the corner of the menu identified by 
        *                   <code>aTargetType</code>
        * @param aTargetType The corner of the menu by which the menu will be 
        *                    positioned
        * @param aHotKeyTable Optional menu hotkey table
        * @param aAppUi The AppUI
        * @remarks
        * @see
        */
        virtual void LaunchPopupMenuL(TInt aResourceId,
                                      const TPoint& aTargetPos,
                                      TPopupTargetPosType aTargetType,
                                      const CEikHotKeyTable* aHotKeyTable,
                                      CEikAppUi* aAppUi) = 0;
        /**
        * Launches a pop-up menu.
        *
        * @param aResourceId The ID of the resource that defines the menu to be 
        *                    launched
        * @param aTargetPos Position of the corner of the menu identified by 
        *                   <code>aTargetType</code>
        * @param aHotKeyTable Optional menu hotkey table
        * @param aTargetType The corner of the menu by which the menu will be 
        *                    positioned
        * @param aAppUi The AppUI
        * @remarks
        * @see
        */
        virtual void DoLaunchPopupL(TInt aResourceId,
                                    const TPoint& aTargetPos, 
                                    const CEikHotKeyTable* aHotKeyTable, 
                                    TPopupTargetPosType aTargetType,
                                    CEikAppUi* aAppUi) = 0;

        /**
        * Closes the pop-up menu.
        *
        * @param aAppUi The AppUI
        * @remarks
        * @see
        */
        virtual void ClosePopup(CEikAppUi* aAppUi) = 0;

        /**
        * Stops displaying the application's menu bar. If the application has 
        * no menu bar or if the menu bar is not visible, this method has no 
        * effect.
        *
        * @remarks
        * @see
        */
        virtual void StopDisplayingMenuBar() = 0;
        
    
        /**
        * Handles sidebar menu commands.
        *
        * @param aResourceId The resource ID
        * @param aPos The position
        * @param aHotKeyTable The hot key table
        * @param aAppUi The AppUI
        * @remarks The sidebar is not supported in Series 90
        * @see
        */
        virtual void HandleSideBarMenuL(TInt aResourceId,const TPoint& aPos,
                                        const CEikHotKeyTable* aHotKeyTable,
                                        CEikAppUi* aAppUi) = 0;

        /**
        * Creates a hot key control.
        *
        * @param aResourceId The Resource ID
        * @param aAppUi The AppUI
        * @remarks
        * @see
        */
        virtual void CreateHotKeyControlL(TInt aResourceId, 
                                          CEikAppUi* aAppUi) = 0;

        /**
        * Gets a pointer to the menu bar.
        *
        * @return the pointer to the menu bar
        * @remarks
        * @see
        */
        virtual CEikMenuBar* MenuBar() const = 0;

        /**
        * Replaces or clears a menu bar, returning a pointer to the replaced
        * menu bar.
        *
        * @param aMenu The new menu bar. <code>NULL</code> to
        *              clear an existing menu bar
        * @return the pointer to the replaced menu bar
        * @remarks
        * @see
        */
        virtual CEikMenuBar* SwapMenuBar(CEikMenuBar* aMenu) = 0;

        /**
        * Gets pointer to a pop-up menu.
        *
        * @return the pointer to the pop-up menu
        * @remarks
        * @see
        */
        virtual CEikMenuPane* Popup() const = 0;

        /**
        * Gets a pointer to the toolbar.
        *
        * @return the pointer to the toolbar
        * @remarks
        * @see
        */
        virtual CEikButtonGroupContainer* ToolBar() const = 0;

        /**
        * Replaces or clears a button group, returning a pointer to the 
        * replaced button group.
        *
        * @param aNewGroup The new button group. <code>NULL</code> to
        *                  clear an existing button group
        * @return the pointer to the replaced button group
        * @remarks
        * @see
        */
        virtual CEikButtonGroupContainer* 
                    SwapButtonGroup(CEikButtonGroupContainer* aNewGroup) = 0;

        /**
        * Gets a pointer to the toolband.
        *
        * @return the pointer to the toolband
        * @remarks
        * @see
        */
        virtual CEikToolBar* ToolBand() const = 0;

        /**
        * Gets a pointer to the title band.
        *
        * @return the pointer to the title band
        * @remarks
        * @see
        */
        virtual CEikToolBar* TitleBand() const = 0;

        /**
        * Gets a pointer to the status pane.
        *
        * @return the pointer to the status pane
        * @remarks
        * @see
        */
        virtual CEikStatusPane* StatusPane() const = 0;

        /**
        * Replaces or clears a toolband, returning a pointer to the replaced
        * toolband.
        *
        * @param aToolBand The new toolband. <code>NULL</code> to
        *                  clear an existing toolband
        * @return the pointer to the replaced toolband.
        * @remarks
        * @see
        */
        inline CEikToolBar* SwapToolBand(CEikToolBar* aToolBand);

        /**
        * Replaces or clears a title band, returning a pointer to the replaced
        * title band.
        *
        * @param aTitleBand The new title band - <code>NULL</code> 
        *                   to clear an existing title band
        * @return the pointer to the replaced title band
        * @remarks
        * @see
        */
        inline CEikToolBar* SwapTitleBand(CEikToolBar* aTitleBand);

        /**
        * Creates a standard tab button.
        *
        * @return the pointer to the created tab button
        * @remarks
        * @see
        */
        virtual CEikCommandButton*  CreateStandardTabButtonL() const = 0;

        /**
        * Creates an embedded application.
        *
        * @param aEikonEnv The Eikon environment
        * @remarks
        * @see
        */
        virtual void CreateEmbeddedL(CEikonEnv& aEikonEnv) = 0;

        /**
        * Destroys the embedded application.
        *
        * @param aEikonEnv The Eikon environment
        * @remarks
        * @see
        */
        virtual void DestroyEmbedded(CEikonEnv& aEikonEnv) = 0;

        /**
        * Handles a change to the application's resources.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see <code>CCoeControl</code>
        */
        virtual void HandleResourceChangeL(TInt aType) = 0;

    protected:
    /** Defines the type of toolbar. */
    enum TToolBarType
        {
        /** Defines a band toolbar. */
        EBand,
        /** Defines a title toolbar. */
        ETitle
        };
    private:
        virtual CEikToolBar* SwapToolBar(CEikToolBar* aToolBar,TToolBarType aType) = 0;
    };

inline CEikToolBar* MEikAppUiFactory::SwapToolBand(CEikToolBar* aToolBand)
/** Replaces or clears a toolband, returning a pointer to the replaced toolband.

@param aToolBand The new toolband. This can be NULL to clear an existing 
toolband. 
@return Pointer to the replaced toolband. */
    {return SwapToolBar(aToolBand,EBand);}

inline CEikToolBar* MEikAppUiFactory::SwapTitleBand(CEikToolBar* aTitleBand)
/** Replaces or clears a title band, returning a pointer to the replaced title 
band.

@param aTitleBand The new title band. This can be NULL to clear an existing 
title band. 
@return Pointer to the replaced title band. */
    {return SwapToolBar(aTitleBand,ETitle);}


#endif  // EIKAUFTY_H

// End of File
