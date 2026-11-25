/*
* ==============================================================================
*  Name        : sendui.h
*  Part of     : SENDUI
*  Interface   : Send as UI API
*  Description : 
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


#ifndef SENDUI_H
#define SENDUI_H

// INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS
class CEikMenuPane;
class CEikHotKeyTable;
class MDesC16Array;
class CRichText;
class CSendBaseUi;

/**
 * The <code>TSendingCapabilities</code> class is a container class that stores a 
 * set of capabilities that are required of the available MTMs by the calling 
 * application. These capabilities include maximum body and message sizes 
 * (<code>0</code> specifies no limit) and a <code>TSending</code> flag member 
 * used to request MTMs that support attachments, body text, or BIO-messaging.
 *
 * @lib sendui.lib
 * @since ?Series90 1.0
 */
class TSendingCapabilities
    {
    public:

    /** 
     * The enumeration <code>TSendingFlags</code> specifies features that an 
     * MTM is required to support. 
     */
    enum TSendingFlags
        {
        /** no features required, all MTMs are valid */
        EAllMTMs = 0,
        /** MTMs must support attachments */
        ESupportsAttachments = 1,
        /** MTMs must support text in the body of the message */
        ESupportsBodyText = 2,
        /** MTMs must support Bearer Independent Object (BIO) messaging */
        ESupportsBioSending = 4,
        /** 
        * MTMs must support attachments or body text - equivalent behavior to 
        * <code>ESupportsAttachments|ESupportsBodyText</code> 
        */
        ESupportsAttachmentsOrBodyText = 8
        };

    public:

        /**
        * The default object constructor.
        */
        IMPORT_C TSendingCapabilities();

        /**
        * The object constructor.
        *
        * @param aBodySize The maximum body size in bytes
        * @param aMessageSize The maximum total message size in bytes
        * @param aFlags The flags from <code>TSendingFlags</code>
        * @remarks
        * @see
        */
        IMPORT_C TSendingCapabilities(TInt aBodySize, TInt aMessageSize, TInt aFlags);

    public:
        /** the maximum body size in bytes */
        TInt    iBodySize;
        /** the maximum total message size in bytes */
        TInt    iMessageSize;
        /** the flags from <code>TSendingFlags</code> */
        TInt    iFlags;
    };

/**
* The <code>CSendAppUi</code> class is the base class for Send As operations.
* Several of the methods deal with <code>CEikMenuPane</code>, which can be
* found in eikmenup.h. For more on BIO-messaging see biodb.h.
*
* @lib sendui.lib
* @since ?Series90 1.0
*/
class CSendAppUi : public CBase
    {
    public:

        /**
        * Starts the two-phase object construction.
        *
        * @param aCommandId The command ID to start numbering MTM IDs from
        * @param aHotKeyTable The hotkeys to be associated with menu items 
        *                     (optional)
        * @remarks MTM IDs are numbered from <code>aCommandId</code> up. 
        *          So <code>aCommandId</code> must be chosen to be 
        *          greater than existing command IDs
        * @return a pointer to the new <code>CSendAppUi</code> object
        * @see
        */
        IMPORT_C static CSendAppUi* NewL(const TInt aCommandId, 
                                         CEikHotKeyTable* aHotKeyTable = NULL);

        /**
        * Starts the two-phase object construction. This method leaves a 
        * pointer to the new <code>CSendAppUi</code> object on the cleanup 
        * stack.
        *
        * @param aCommandId The command ID to start numbering MTM IDs from
        * @param aHotKeyTable The hotkeys to be associated with menu items 
        *                     (optional)
        * @remarks MTM menu command IDs are numbered from <code>aCommandId</code>
        *          up. So <code>aCommandId</code> must be chosen to be 
        *          greater than existing command IDs
        * @return a pointer to the new <code>CSendAppUi</code> object
        */
        IMPORT_C static CSendAppUi* NewLC(const TInt aCommandId,
                                          CEikHotKeyTable* aHotKeyTable = NULL);

        /**
        * The object destructor.
        */
        IMPORT_C virtual ~CSendAppUi();

        /**
        * Adds a Send menu item at the specified position in the specified 
        * menu pane. The Send menu item has command ID <code>R_SENDUI_MENU</code>
        * (defined in sendnorm.rsg). This is usually called by an AppUI's
        * <code>DynInitMenuPaneL()</code> method to initialize a menu pane.
        * A <code>TSendingCapabilities</code> object is passed in with the 
        * properties required for MTMs to be displayed in the Send cascade.
        * These properties are used to filter the MTMs to produce a list that
        * is displayed on the Send menu. A second set of capabilities can 
        * also be specified. Any MTMs returned using the first set of 
        * capabilities but not those in the second set are displayed as dimmed 
        * in the Send menu. Thus, for example, send methods that do not support 
        * attachments still appear in the menu.
        *
        * @param aMenuPane The menu pane to contain the Send menu item
        * @param aIndex The position in the menu pane to insert the Send menu 
        *               item
        * @param aRequiredCapabilities The set of properties for MTMs to be 
        *               displayed in the Send menu
        * @param aCapabilitiesToDisplay The set of properties for MTMs to be 
        *                               displayed undimmed in the Send menu 
        * @remarks
        * @see
        */
        IMPORT_C virtual void DisplaySendMenuItemL(CEikMenuPane& aMenuPane, 
                                                   const TInt aIndex, 
                                                   TSendingCapabilities aRequiredCapabilities, 
                                                   TSendingCapabilities aCapabilitiesToDisplay);

        /**
        * Adds a Send menu item at the specified position in the specified 
        * menu pane.
        *
        * @param aMenuPane The menu pane to contain the Send menu item
        * @param aIndex The position in the menu pane to insert the Send menu 
        *               item
        * @param aRequiredCapabilities The set of properties for MTMs to be 
        *                              displayed in the Send menu
        * @remarks For 6.0 compatibility
        * @see DisplaySendMenuItemL()
        */
        IMPORT_C virtual void DisplaySendMenuItemL(CEikMenuPane& aMenuPane, 
                                                   const TInt aIndex, 
                                                   TSendingCapabilities aRequiredCapabilities);

        /**
        * Displays the Send menu pane. This lists the MTMs available that 
        * match the set(s) of <code>TSendingCapabilties</code> passed into 
        * <code>DisplaySendMenuItemL</code>. This is usually called by an 
        * AppUI's <code>DynInitMenuPaneL()</code> method when the 
        * <code>R_SENDUI_MENU</code> menu ID is received, that is, when the 
        * Send menu item is tapped.
        *
        * @param aMenuPane The menu pane containing the Send menu item
        * @param aMtmsToDim An array of <code>TUid</code>s for any MTMs that 
        *                   should be set to dimmed in the Send menu pane
        * @param aMtmsToDrop An array of <code>TUid</code>s for any MTMs that 
        *                    should be removed from the Send menu pane 
        * @remarks UIDs required by <code>aMtmsToDim</code> and
        *          <code>aMtmsToDrop</code> are MTM-specific and are not 
        *          published in a single place. To find MTM UIDs, search the 
        *          available documentation for identifiers beginning with 
        *          <code>KUidMsgType</code>
        * @see
        */
        IMPORT_C virtual void DisplaySendCascadeMenuL(CEikMenuPane& aMenuPane, 
                                                      CArrayFix<TUid>* aMtmsToDim, 
                                                      CArrayFix<TUid>* aMtmsToDrop);

        /**
        * Displays the Send menu pane.
        *
        * @param aMenuPane The menu pane containing the Send menu item
        * @param aMtmsToDim An array of <code>TUid</code>s for any MTMs that 
        *                   should be set to dimmed in the Send menu pane
        * @remarks For 6.0 compatibility
        * @see DisplaySendCascadeMenuL()
        */
        IMPORT_C virtual void DisplaySendCascadeMenuL(CEikMenuPane& aMenuPane, 
                                                      CArrayFix<TUid>* aMtmsToDim);

        /**
        * Displays the Send menu pane.
        *
        * @param aMenuPane The menu pane containing the Send menu item
        * @remarks
        * @see DisplaySendCascadeMenuL()
        */
        IMPORT_C virtual void DisplaySendCascadeMenuL(CEikMenuPane& aMenuPane);

        /**
        * Checks if the MTM associated with a command ID can support the given
        * capabilities. This command will be 
        * specific to the MTM item selected from the Send menu pane.
        * 
        * @param aCommandId An ID representing a specific MTM item selected
        *        from the Send cascade
        * @param aRequiredCapabilities The sending capabilities required for 
        *                              this operation
        * @param aMtmsToDim An array of <code>TUid</code>s for any MTMs that 
        *                   should be set to dimmed in the Send menu pane. If 
        *                   <code>aCommandId</code> matches one of these, it is 
        *                   invalid (optional)
        * @return <code>ETrue</code> if the Send operation is supported for 
        *         the MTM and capabilities are passed in; <code>EFalse</code>
        *         otherwise
        * @remarks There is no need to perform this check when the capabilities
        *          are the same as those used in <code>DisplaySendMenuItemL()</code>
        *          because the menu only displays valid MTMs
        * @see
        */
        IMPORT_C virtual TBool CommandIsValidL(const TInt aCommandId, 
                                               TSendingCapabilities aRequiredCapabilities,
                                               CArrayFix<TUid>* aMtmsToDim = NULL);

        /**
        * Gets the MTM UID for a particular command ID.
        * The command ID is a value associated with an item in the Send menu.
        * The application-specific value for <code>aCommandId</code> that was
        * passed into <code>NewL()</code> is subtracted from the command ID to
        * give an array index. This index is used to look up the MTM UID in an
        * internal array.
        *
        * @param aCommandId The command ID
        * @return the UID of the MTM
        * @remarks
        * @see
        */
        IMPORT_C virtual TUid MtmForCommand(const TInt aCommandId);

        /**
        * Gets the sending capabilities for a particular MTM.
        *
        * @param aUid The UID of the MTM
        * @return the sending capabilities of the MTM
        * @remarks The capabilities for an MTM selected from the Send menu or
        *          dialog can be checked by first calling <code>MtmForCommand()</code> 
        *          to convert the command ID to a UID
        * @see
        */
        IMPORT_C virtual TSendingCapabilities MtmCapabilitiesL(const TUid aUid);

        /**
        * Creates and sends a new message. The required MTM is obtained via 
        * the command ID passed in. The actual MTM required is obtained via 
        * an offset to the base command ID. This command ID is passed in via 
        * the Send menu pane listing the set of available sending methods, 
        * for example, SMS, email etc. A rich text object containing the 
        * message body and/or an array of attachment filenames can be passed 
        * in, as can arrays of addresses and real names for recipients of this 
        * message.
        *
        * @param aCommandId A command ID from the Send menu. See 
        *                   <code>MtmForCommand</code> for the relationship 
        *                   between command ID and MTM UID
        * @param aBodyText A pointer to a <code>CRichText</code> containing the 
        *                  message body (optional)
        * @param aAttachments An array of filenames for files to add as 
        *                     attachments to the message (optional)
        * @param aBioTypeUid An optional UID to specify the BIO message type 
        *                    for the message (if it is to be a BIO message)
        * @param aRealAddresses An array of addresses to add as recipients to 
        *                       the message (optional)
        * @param aAliases An array of real names to add as recipients to the 
        *                 message (optional)
        * @remarks
        * @see
        */
        IMPORT_C virtual void CreateAndSendMessageL(const TInt aCommandId, 
                                                    const CRichText* aBodyText = NULL,
                                                    MDesC16Array* aAttachments = NULL,
                                                    const TUid aBioTypeUid = KNullUid,
                                                    MDesC16Array* aRealAddresses = NULL, 
                                                    MDesC16Array* aAliases = NULL);

        /**
        * Creates and sends a new message.
        *
        * @param aMtmUid The UID of the MTM required to create this message
        * @param aBodyText A pointer to a <code>CRichText</code> containing 
        *                  the message body (optional)
        * @param aAttachments An array of filenames for files to add as 
        *                     attachments to the message (optional)
        * @param aBioTypeUid An optional UID to specify the BIO message type 
        *                    for the message (if it is to be a BIO message)
        * @param aRealAddresses An array of addresses to add as recipients to 
        *                       the message (optional)
        * @param aAliases An array of real names to add as recipients to the 
        *                 message (optional)
        * @remarks
        * @see CreateAndSendMessageL()
        */
        IMPORT_C virtual void CreateAndSendMessageL(const TUid aMtmUid, 
                                                    const CRichText* aBodyText = NULL, 
                                                    MDesC16Array* aAttachments = NULL, 
                                                    const TUid aBioTypeUid = KNullUid, 
                                                    MDesC16Array* aRealAddresses = NULL, 
                                                    MDesC16Array* aAliases = NULL);

        /**
        * Creates a new message. A rich text object containing the message body 
        * and/or an array of attachment filenames can be passed in, as can 
        * arrays of addresses (for example, to, cc, and bcc) and a subject.
        *
        * @param aMtmUid The UID of the MTM required to create this message
        * @param aToAddresses An array of addresses to add as recipients to 
        *                     the message
        * @param aCcAddresses An array of addresses to add as cc to the 
        *                     message
        * @param aBccAddresses An array of addresses to add as bcc to the 
        *                     message
        * @param aSubject The subject for the message
        * @param aBodyText A pointer to a <code>CRichText</code> containing 
        *                  the message body
        * @param aAttachments An array of filenames for files to add as 
        *                     attachments to message
        * @see
        */
        IMPORT_C virtual void ExtendedCreateAndSendMessageL(const TUid aMtmUid,
                                                            MDesC16Array* aToAddresses, 
                                                            MDesC16Array* aCcAddresses, 
                                                            MDesC16Array* aBccAddresses, 
                                                            const TDesC* aSubject, 
                                                            const CRichText* aBodyText, 
                                                            MDesC16Array* aAttachments);


        /** 
        * Launches the Send As dialog. This allows the user to select from a 
        * list of MTMs. The selected MTM UID is returned in the 
        * <code>aMtmUid</code> reference.
        *
        * @param aMtmUid A reference to the UID of the MTM selected from the 
        *                dialog
        * @param aRequiredCapabilities The sending capabilities required for 
        *                              the MTMs to be displayed in the dialog
        * @param aCapabilitiesToDisplay An optional parameter containing a 
        *                               subset of the sending capabilities 
        *                               specified in <code>aRequiredCapabilities</code>. 
        *                               If this parameter is defined, only the 
        *                               MTMs with these capabilities will be 
        *                               active, the others being dimmed
        * @param aDimmedItemInfoResId The resource ID for the info message text 
        *                             that is displayed if a dimmed item is 
        *                             selected in the dialog (optional)
        * @param aMtmsToDrop An array containing <code>TUid</code> for any 
        *                    MTMs that should be removed from the dialog 
        *                    list (optional)
        * @return <code>ETrue</code> if a valid MTM has been selected and OK is
        *         tapped in the dialog; <code>EFalse</code> if the dialog is 
        *         cancelled
        * @remarks
        * @see CSendAsDialog
        */
        IMPORT_C TBool SendDialogL(TUid& aMtmUid, 
                                   TSendingCapabilities aRequiredCapabilities,
                                   TSendingCapabilities aCapabilitiesToDisplay = TSendingCapabilities(),
                                   TInt aDimmedItemInfoResId=-1,
                                   CArrayFix<TUid>* aMtmsToDrop = NULL);

        /** 
        * Launches the Send As dialog. This allows the user to select from a 
        * list of MTMs. The selected MTM UID is returned in the 
        * <code>aMtmUid</code> reference.
        *
        * @param aMtmUid A reference to the UID of the MTM selected from the 
        *                dialog
        * @param aMtmsToDim An array containing <code>TUid</code> for any MTMs 
        *                   that should be set to dimmed in the dialog list
        * @param aMtmsToDrop An array containing <code>TUid</code> for any 
        *                    MTMs that should be removed from the dialog list
        * @param aRequiredCapabilities The sending capabilities required for 
        *                              the MTMs to be displayed in the dialog
        * @param aCapabilitiesToDisplay An optional parameter containing a 
        *                               subset of the sending capabilities 
        *                               specified in <code>aRequiredCapabilities</code>. 
        *                               If this parameter is defined, only the 
        *                               MTMs with these capabilities will be 
        *                               active, the others being dimmed
        * @param aDimmedItemInfoResId The resource ID for the info message text 
        *                             that is displayed if a dimmed item is 
        *                             selected in the dialog (optional)
        * @return <code>ETrue</code> if a valid MTM has been selected and OK 
        *         is tapped in the dialog, <code>EFalse</code> if the dialog 
        *         is cancelled
        * @remarks
        * @see SendDialogL()
        * @see CSendAsDialog
        */
        IMPORT_C TBool SendDialogL(TUid& aMtmUid, 
                                   CArrayFix<TUid>* aMtmsToDim, 
                                   CArrayFix<TUid>* aMtmsToDrop, 
                                   TSendingCapabilities aRequiredCapabilities, 
                                   TSendingCapabilities aCapabilitiesToDisplay = TSendingCapabilities(), 
                                   TInt aDimmedItemInfoResId=-1);


        /** 
        * Called if the user tries to execute a dimmed menu command.
        * An info message is displayed to inform the user why the command is 
        * not possible.
        *
        * @param aCommandId The selected command ID
        * @remarks
        * @see
        */
        IMPORT_C void HandleAttemptDimmedSelectionL(const TInt aCommandId);
        
        /** @internal */
        RLibrary* UiDll() {return iUiDll;};
        /** @internal */
        void SetUiDll(RLibrary* aLibrary) {iUiDll = aLibrary;};
        /** @internal */
        CSendBaseUi* SendUi() {return iSendUi;};
        /** @internal */
        void SetSendUi(CSendBaseUi* aSendUi) {iSendUi = aSendUi;};

    private:
        RLibrary* iUiDll;
        CSendBaseUi* iSendUi;
    };



#endif  // SENDUI_H

// End of File
