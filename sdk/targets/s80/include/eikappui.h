/*
* ==============================================================================
*  Name        : eikappui.h
*  Part of     : UIKON
*  Interface   : Application API
*  Description : Application UI
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


#ifndef EIKAPPUI_H
#define EIKAPPUI_H

// INCLUDES
#include <coeaui.h>
#include <coemain.h>
#include <eikmobs.h>
#include <apadef.h>
#include <vwsdef.h>
#include <eikdef.h>
#include <baerrhan.h>
#include <eikaufty.h>
#include <eikcmds.h>

// FORWARD DECLARATIONS
class CEikDocument;
class CEikApplication;
class MApaEmbeddedDocObserver;
class CEikAppUiExtra;


/** defined in basched.h */
struct SExtendedError;

/**
* the color scheme store 
* @publishedAll
* @released
*/
const TUid KUidEikColorSchemeStore={0x1};


/**
* the color scheme stream 
* @publishedAll
* @released
*/
const TUid KUidEikColorSchemeStream={0x1};

/**
 * The <code>CEikAppUi</code> class handles application-wide aspects of the 
 * application's user interface (AppUI) such as the toolbar, menus, the opening
 * and closing of files, and exiting the application cleanly.
 * AppUIs handle commands that are invoked using the menu bar,
 * toolbar, toolband, and hotkeys. The commands that an AppUI handles are
 * specified in its application resource file. An AppUI is
 * responsible for opening and closing the application document's files in
 * response to user commands. It also owns and manages the core controls
 * of the user interface, for example the toolbar and menu bar, and
 * handles commands from these. Every Uikon application should use its own
 * class derived from <code>CEikAppUi</code> to handle application-wide
 * user interface details. Responses to various kinds of events can be
 * handled at the level of the AppUI by providing suitable
 * implementations of the following virtual
 * methods:
 * <ul>
 * <li><code>CCoeAppUi::HandleKeyEventL()</code> - key events</li>
 * <li><code>CCoeAppUi::HandleForegroundEventL()</code> - application
 *     switched to foreground</li>
 * <li><code>CCoeAppUi::HandleSwitchOnEventL()</code> - not used in Series 90</li>
 * <li><code>CCoeAppUi::HandleSystemEventL()</code> - system events</li>
 * <li><code>CCoeAppUi::HandleMessageReadyL()</code> - message ready</li>
 * <li><code>CCoeAppUi::HandleApplicationSpecificEventL()</code> -
 *     application-specific events</li>
 * <li><code>CEikAppUi::HandleCommandL()</code> - handles commands defined in 
 *     resource files</li>
 * </ul>
 * 
 * @lib eikcore.lib
 * @since 6.0
*/
class CEikAppUi : public CCoeAppUi, public MEikMenuObserver, public MCoeMessageObserver
    {
    public:

        /**
        * The default object destructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C ~CEikAppUi();

        /**
        * The default object constructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C CEikAppUi();
    public: // new functions

        /**
        * Completes construction of a <code>CEikAppUi</code> object.
        * 
        * @remarks
        * @see
        */
        IMPORT_C virtual void ConstructL();

        /**
        * Handles changes to the model associated with this 
        * <code>CEikAppUi</code>'s application. This virtual method is empty 
        * in <code>CEikAppUi</code>.
        * 
        * @remarks
        * @see
        */
        IMPORT_C virtual void HandleModelChangeL();

        /**
        * This method is called by <code>CEikAppUi::HandleSideBarMenuL()</code>.
        * The framework calls <code>CEikAppUi::HandleSideBarMenuL()</code>
        * to handle user invocation of a sidebar menu.
        * 
        * @param aResourceId The ID of the resource that defines the menu to 
        *                    be launched
        * @param aTargetPos The position of the corner of the menu identified by 
        *        <code>aTargetType</code>
        * @param aTargetType The corner of the menu by which the menu will be 
        *        positioned
        * @param aHotKeyTable An optional menu hotkey table
        * @remarks The sidebar is not supported in Series 90
        * @see
        */
        IMPORT_C void LaunchPopupMenuL(TInt aResourceId,
                                       const TPoint& aTargetPos,
                                       TPopupTargetPosType aTargetType,
                                       const CEikHotKeyTable* aHotKeyTable=NULL);

        /**
        * Returns the AppUI inside which this AppUI is embedded.
        * Embedded AppUIs are used, for example, for editing embedded documents
        * and to stack a Help application onto the context of a current 
        * application.
        * 
        * @return a pointer to this <code>CEikAppUi</code>'s container AppUI. 
        *         <code>NULL</code> if this AppUI is not embedded
        * @remarks
        * @see
        */
        inline CEikAppUi* ContainerAppUi() const;

        /**
        * Sets this application UI's document pointer.
        * 
        * @param aDocument The AppUI's document
        * @remarks
        * @see
        */
        IMPORT_C void SetDocument(CEikDocument* aDocument);

        /**
        * Sets the embedded document's observer and read-only state.
        * The observer is informed when an action such as opening the 
        * embedded document is performed. The read-only flag applies to the
        * observer and its interactions with the document.
        *
        * @param aObserver The observer for the embedded document
        * @param aReadOnly <code>ETrue</code> to set the embedded document as 
        *                  read-only; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetEmbeddedDocInfo(MApaEmbeddedDocObserver* aObserver,
                                         TBool aReadOnly);

        /**
        * The default implementation of this method returns whether the
        * file <code>aDocumentName</code> exists. It does nothing else. The
        * Uikon application framework calls the three-argument form when an
        * application is started by selecting a file from the shell or by
        * issuing a 'Create new' file command. Most file-based
        * applications will override the virtual three-argument form to invoke
        * the two-argument form. If the passed value of
        * <code>aDocumentName</code> is not the name of a file of the right 
        * type for this application, a new file name is returned through
        * <code>aDocumentName</code>. Implementations of this method should
        * not attempt to open the document - that is handled separately by the
        * application framework after the command line has been processed. 
        * When called automatically, <code>aCommand</code> is either
        * <code>EApaCommandCreate</code> or <code>EApaCommandRun</code>.
        *
        * @param aCommand The shell command sent to the application
        * @param aDocumentName At call time, the name of the document as 
        *                      specified on the command line. On return, the 
        *                      name for the file that will be created by the 
        *                      calling framework
        * @param aTail The command line tail
        * @return <code>ETrue</code> if the final value of 
        *         <code>aDocumentName</code> represents an existing file;
        *         <code>EFalse</code> otherwise
        * @remarks The method verifies the existence of the document name.
        *          If the <code>aCommand</code> parameter is set to create, 
        *          the return value is <code>EFalse</code> as it is assumed 
        *          that 
        *          the document name is valid. Any other command results in 
        *          the last file opened being used as the document name 
        *          (of the file to be opened) and <code>ETrue</code> being 
        *          returned
        * @see
        */
        IMPORT_C virtual TBool ProcessCommandParametersL(TApaCommand aCommand,
                                                         TFileName& aDocumentName,
                                                         const TDesC8& aTail);

        /**
        * Gets this AppUI's document pointer.
        * 
        * @return the pointer to the AppUI's document
        * @remarks
        * @see
        */
        IMPORT_C CEikDocument* Document() const;

        /**
        * Gets a pointer to the application associated with this AppUI.
        * 
        * @return a pointer to the application associated with this AppUI
        * @remarks
        * @see
        */
        IMPORT_C CEikApplication* Application() const;

        /**
        * Gets the area of the screen available to the application for drawing.
        * This does not include the space that is available for a toolbar,
        * toolband or title band, if the application requires them.
        * 
        * @return the area of the screen available to the application for drawing
        * @remarks
        * @see
        */
        IMPORT_C TRect ClientRect() const;

        /**
        * Gets the total area of the screen available to the application.
        * This includes the space that is available for a toolbar, toolband, or
        * title band, if the application requires them.
        * 
        * @return the total area of the screen available to the application
        * @remarks
        * @see
        */
        IMPORT_C TRect ApplicationRect() const;

        /**
        * Stops displaying the application's menu bar.
        * If the application has no menu bar or if the menu bar is not visible,
        * this method has no effect.
        * 
        * @remarks
        * @see
        */
        IMPORT_C void StopDisplayingMenuBar();

        /**
        * Determines whether the application is set to fade when in the 
        * background.
        *
        * @return <code>ETrue</code> if the application is set to fade when in 
        *               the background; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool FadeWhenInBackground();

        /**
        * Sets the window as faded or unfaded.
        * 
        * @param aFaded <code>ETrue</code> to set the window as faded; 
        *               <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C void SetFaded(TBool aFaded);

        /**
        * Sets the position of the top dialog in the stack.
        * 
        * @param aPos The new position of the dialog
        * @remarks
        * @see
        */
        IMPORT_C void SetDialogPosition(const TPoint& aPos);
    public: // new function

        /**
        * Reports a resource change to the application.
        * 
        * @param aType The type of resource that has changed
        * @remarks
        * @see
        */
        IMPORT_C void ReportResourceChangedToAppL(TInt aType);

        /**
        * Handles user commands. This method is overridden by subclasses to handle
        * user commands passed on by the application framework. This method is 
        * called by <code>CEikAppUi::ProcessCommandL()</code> and has a blank 
        * implementation. It can be overridden to provide a custom 
        * response to user commands. A command instructs the application to 
        * perform a method and is invoked using a menu item, a 
        * hotkey, or a button in a toolbar, toolband, or dialog.
        * 
        * @param aCommand A command ID
        * @remarks
        * @see
        */
        IMPORT_C virtual void HandleCommandL(TInt aCommand);

        /**
        * Processes an application architecture message.
        * This method is overridden by subclasses to handle messages sent from the
        * application architecture framework. As defined in 
        * <code>CEikAppUi</code>, this method recognizes the message UIDs 
        * <code>KUidApaMessageSwitchOpenFileValue</code>
        * and <code>KUidApaMessageSwitchCreateFileValue</code>. It performs 
        * no action if the message contains neither of these values. 
        *  
        * @param aUid The message's unique identifier
        * @param aParams The message parameters
        * @remarks
        * @see CCoeAppUi::HandleMessageReplyL()
        * @see CApaTask::SendMessage()
        */
        IMPORT_C virtual void ProcessMessageL(TUid aUid,const TDesC8& aParams);

        /**
        * Opens the specified file in response to a corresponding message.
        * 
        * @param aFileName The file to open
        * @remarks
        * @see
        */
        IMPORT_C virtual void OpenFileL(const TDesC& aFileName);

        /**
        * Creates and opens a file with the given name in response to the 
        * corresponding message.
        * 
        * @param aFileName The name of the file to create and open
        * @remarks
        * @see
        */
        IMPORT_C virtual void CreateFileL(const TDesC& aFileName);

        /**
        * Handles errors.
        * 
        * @param aError The error code
        * @param aExtErr For extended error messages
        * @param aErrorText The text of the error
        * @param aContextText The text describing the context of the error
        * @return the value specifying the response to the error, for
        *         example, error not handled
        * @remarks
        * @see baerrhan.h
        */
        IMPORT_C virtual 
            TErrorHandlerResponse HandleError(TInt aError, 
                                              const SExtendedError& aExtErr,
                                              TDes& aErrorText,
                                              TDes& aContextText);

        /**
        * Handles a change to the resource of the application that is shared 
        * across the environment. The method is 
        * normally called by the CONE framework. It can also be called by 
        * the developer when used to change skins or other resource related 
        * items.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see
        */
        IMPORT_C virtual void HandleResourceChangeL(TInt aType);
    public: // from CCoeAppUiBase

        /**
        * Performs pre-exit processing to ensure that the application exits
        * cleanly.
        * 
        * @remarks
        * @see CCoeAppUiBase
        */
        IMPORT_C void PrepareToExit();
    protected: // new functions

        /**
        * Completes construction.
        * The implementation of ConstructL in CEikAppUi simply calls 
        * BaseConstructL().
        */
        IMPORT_C void BaseConstructL(TInt aAppUiFlags=0);

        /**
        * Reads the application information for this application from the 
        * specified resource offset.
        * This function is called automatically in BaseConstructL().
        * @param aResourceFileOffset Offset of application information.
        */
        IMPORT_C void ReadAppInfoResourceL(TInt aResourceFileOffset=0);

        /**
        * Creates a hotkey control.
        * Constructs a CEikHotKeyControl whose
        * CEikHotKeytable is specified by a resource ID, and adds
        * it to the control stack.
        * @param aResourceId A hot key table resource.
        */
        IMPORT_C void CreateHotKeyControlL(TInt aResourceId);

        /**
        * Marks this CEikAppUi's associated document as having changed.
        */
        IMPORT_C void SetDocChanged();

        /**
        * Saves changes made to the app UIs associated document if the document
        * is marked as having changed.
        */
        IMPORT_C void SaveAnyChangesL();

        /**
        * Closes the app UI.
        */
        IMPORT_C void Exit();

        /**
        * Saves the app UIs document, or sets the document as changed if the 
        * app UI is embedded.
        */
        IMPORT_C void SaveL();

        /**
        * Closes any currently visible sidebar popup menu.
        *
        * Calls to Popup immediately after a ClosePopup() return NULL.
        */
        IMPORT_C void ClosePopup();

        /**
         *
         * Processes shell commands.
         * The default implementation of this function returns whether or not 
         * the file <code>aDocumentName</code> exists, and does nothing else. 
         * The Uikon application framework calls the three-argument form when 
         * an application is started by selecting a file from the shell or by
         * issuing a <code>Create new file</code> command.Most file-based
         * applications will override the virtual three-argument form to invoke
         * the two-argument form. If the passed value of 
         * <code>aDocumentName</code> is not the name of a file of the right 
         * type for this application, a new filename is returned through
         * <code>aDocumentName</code>. Implementations of this function should
         * not attempt to open the document. That is handled separately by the
         * application framework after the command line has been processed.When
         * called automatically, <code>aCommand</code> is either
         * <code>EApaCommandCreate</code> or <code>EApaCommandRun</code>.
         *
         * @param     aCommand  The shell command sent to the application.
         * @param     aDocumentName  At call time, the name of the document as 
         *            specified on
         *            the command line. On return, the name for the file
         *            which will be created by the calling framework.
         * @returns   Whether the final value of <code>aDocumentName</code>
         *            represents an existing file.
         */
        IMPORT_C TBool ProcessCommandParametersL(TApaCommand aCommand,
                                                 TFileName& aDocumentName);
    protected: // from MEikMenuObserver

        /**
        * Handles sidebar menu commands.
        * This is called by the Uikon framework to handle user invocation of a
        * sidebar menu. See also MEikMenuObserver::HandleSideBarMenuL().
        * @param aResourceId ID of the resource that describes the menu.
        * @param aPos Position of the menus reference point. For sidebar 
        *             menus, this is the top-right corner.
        * @param aModifiers Bitwise OR of the modifiers held when the menu was
        *                   invoked by the user.
        * @param aTable Hotkey table for the menu.
        * @remarks The sidebar is not supported in Series 90
        * @see
        */
        IMPORT_C void HandleSideBarMenuL(TInt aResourceId,
                                         const TPoint& aPos,
                                         TInt aModifiers,
                                         const CEikHotKeyTable* aTable);
    protected: // from CCoeAppUi

        /**
        * Handles an application specific event.
        * This function takes action on notification of a change to the
        * environment colour scheme and informs everything on the control
        * stack of the change. See also CCoeAppUi.
        *
        * @param aType The type of the event that occured. This should be a 
        *              unique identifier constantt for the application specific
        *              event.
        * @param aEvent The window server event that occured.
        */
        IMPORT_C void HandleApplicationSpecificEventL(TInt aType,
                                                      const TWsEvent& aEvent); // not available before ER5u

        /**
        * Handles changes in keyboard focus when an application switches to,or
        * from the foreground
        *
        * @param aForeground ETrue to switch to the foreground.
        * EFalse to switch from the foreground.
        */
        IMPORT_C void HandleForegroundEventL(TBool aForeground);

        /**
        * Handles window server events.
        *
        * @param aEvent The window server event that occured.
        * @param aDestination The control associated with the event.
        */
        IMPORT_C void HandleWsEventL(const TWsEvent& aEvent, 
                                     CCoeControl* aDestination);

        /**
        * Handles the system event.
        * @param aEvent A system event.
        */
        IMPORT_C void HandleSystemEventL(const TWsEvent& aEvent);
    protected: // from MEikCommandObserver

        /**
        * Processes user command.
        * @param aCommand ID of the command to respond to.
        */
        IMPORT_C void ProcessCommandL(TInt aCommand);
    private: // from MEikMenuObserver
        IMPORT_C void SetEmphasis(CCoeControl* aMenuWindow,TBool aEmphasis);
		IMPORT_C void DeprecatedBaseConstructL(TInt aAppUiFlags=0);
    protected: // from MCoeMessageObserver
        /**
        * Handles window server message.
        * @param aClientHandleOfTargetWindowGroup The window group that the message was sent to
        * @param aMessageUid The message UID.
        * @param aMessageParameters The message parameters.
        */
    IMPORT_C MCoeMessageObserver::TMessageResponse 
        HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, 
                       TUid aMessageUid, 
                       const TDesC8& aMessageParameters);
    private: // from CCoeAppUiBase
        IMPORT_C void HandleScreenDeviceChangedL(); // used to be Reserved_1()
        IMPORT_C void Reserved_2();
    private: // new functions
        IMPORT_C virtual TBool ValidFileType(TUid aFileUid) const;
        IMPORT_C virtual void Reserved_3();
        IMPORT_C virtual void Reserved_4();
//  void DoLaunchPopupL(TInt aResourceId,const TPoint& aTargetPos, const CEikHotKeyTable* aHotKeyTable, TPopupTargetPosType aTargetType = EPopupTargetTopLeft);
    public:
    /**
     * This enumeration relates to the use of an application resource file
     * and screen furniture.
     */
    enum
        {
        /** the application uses its standard application resource file */
        EStandardApp            = 0x00,
        /** the application has no application resource file */
        ENoAppResourceFile      = 0x01,
        /** 
         * the application uses a different application resource file from 
         * its standard 
         */
        ENonStandardResourceFile= 0x02,     
        /** 
         * the application uses no screen furniture, for example, application 
         * title area, status pane, and menu 
         */
        ENoScreenFurniture      = 0x04,     
        /** the last reserved AppUI flag used during a base construction call */
        ELastReservedEikAppUiFlag = 0x08
        };
    private: // new functions
        void CreateResourceIndependentFurnitureL();
        TBool ValidFileExistsL(const TDesC& aFileName);
    protected:
        CEikDocument* iDocument;
        CEikAppUi* iContainerAppUi;
        MApaEmbeddedDocObserver* iDoorObserver;
        TBool iEmbeddedAndReadOnly;
        TInt iFlags;
    private:
    enum
        {
        EEmbedded = 0x01
        };
    private:
        CEikAppUiExtra* iEikAppUiExtra;
    };

inline CEikAppUi* CEikAppUi::ContainerAppUi() const
/** Returns the app UI inside which this app UI is embedded.

Embedded app UIs are used for editing embedded documents.

@return A pointer to this object's container app UI. NULL if this app 
UI is not embedded */
    { return iContainerAppUi; }


#endif  // EIKAPPUI_H

// End of File
