/*
* ============================================================================
*  Name        : SendUi.h
*  Part of     : SendUI
*  Description : Can be used to show "Send" list query and to create and send
*                messages via available sending services. Created messages are
*                sent directly or message editor is opened for editing,
*                depending on the type of the selected service.
*  Version     : 3.0
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/


#ifndef CSENDUI_H
#define CSENDUI_H

#include <TSendingCapabilities.h>

// FORWARD DECLARATIONS
class CEikMenuPane;
class CSendUiImpl;
class CMessageData;
class CSendingServiceInfo;


// CLASS DECLARATION

/**
*  Offers "Send" pop-up list and message creation and sending services.
*  
*  Can be used to display "Send" list query and to create and send
*  messages via available services. Sending services can be based
*  on the MTM or ECom architecture. Created messages are sent
*  directly or message editor is opened for editing, depending on
*  the type of selected service.
*
*  @lib SendUi.lib
*  @since Series 60 3.0
*/
class CSendUi : public CBase
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        IMPORT_C static CSendUi* NewL();

        /**
        * Two-phased constructor.
        */
        IMPORT_C static CSendUi* NewLC();

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CSendUi();

    public: // New functions

        /**
        * Adds "Send" menu item to menupane.
        *
        * @since Series 60 3.0
        * @param aMenuPane Menupane where the "Send" menu item should be added.
        * @param aIndex The place of the "Send" menu item in menupane.
        * @param aCommandId Command id for the "Send" menu item.
        * @param aRequiredCapabilities Capabilities required by services to be
        *        shown in "Send" list query. If no capabilities are required
        *        (KCapabilitiesForAllServices), all available services are
        *        shown in "Send" list query.
        * @return None.
        */
        IMPORT_C void AddSendMenuItemL(
            CEikMenuPane& aMenuPane,
            TInt aIndex,
            TInt aCommandId,
            TSendingCapabilities aRequiredCapabilities = KCapabilitiesForAllServices );

        /**
        * First displays "Send" pop-up list query and then creates the message.
        * Editor is launched for editing the message or the message is sent
        * directly without opening the editor. Functionality depends on the
        * type of selected service.
        *
        * "Send" pop-up list query can be manipulated in three ways. All three
        *  methods can be used or just some of those.
        *
        * The first option is to set the required capabilities for services.
        * Eg. attachments supported. Sending services not matching to required
        * capabilities are filtered away. Capabilities are defined in
        * TSendingCapabilities.h.
        *
        * The second option is content based filtering. Filtering is based on
        * the files intended to send. Those files can be set as part of message
        * data. Filtering is done according the predefined rules.
        * Eg. If oversized file is intended to send, MMS is filtered away from
        * "Send" pop-up list.
        *
        * The third option is to set the array of service uids not wanted to
        * be shown in list query. These sending services are filtered away
        * even if those match to required capabilities.
        *
        * @since Series 60 3.0
        * @param aMessageData Data for the message.
        * @param aRequiredCapabilities Capabilities required by sending services
        *        to be shown in "Send" pop-up list query. If no capabilities are
        *        required (KCapabilitiesForAllServices), all available services
        *        are shown in "Send" pop-up list query.
        * @param aServicesToDim Array of service uids (MTM or ECom) NOT wanted
        *        to "Send" list query. 
        *        Predefined sending service uids are defined in: SendUiConsts.h
        * @param aBioTypeUid BIO message type uid.
        * @param aLaunchEditorEmbedded ETrue if the editor should be launched
        *        embedded. Otherwise the editor is launched stand-alone.
        *        Note: some services sends the messages without launching the
        *        editor at all.
        * @param aTitleText Title of the "Send" pop-up list query. If no title
        *		 is defined, then the localised default title "Send:" is used.
        * @return None.
        */
        IMPORT_C void ShowQueryAndSendL(
            const CMessageData* aMessageData,
            TSendingCapabilities aRequiredCapabilities = KCapabilitiesForAllServices,
            CArrayFix<TUid>* aServicesToDim = NULL,
            TUid aBioTypeUid = KNullUid,
            TBool aLaunchEditorEmbedded = ETrue,
            const TDesC& aTitleText = KNullDesC );

        /**
        * Displays "Send" pop-up list query and returns the user selection.
        *
        * "Send" pop-up list query can be manipulated in three ways. All three
        *  methods can be used or just some of those.
        *
        * The first option is to set the required capabilities for services.
        * Eg. attachments supported. Sending services not matching to required
        * capabilities are filtered away. Capabilities are defined in
        * TSendingCapabilities.h.
        *
        * The second option is content based filtering. Filtering is based on
        * the files intended to send. Those files can be set as part of message
        * data. Filtering is done according the predefined rules.
        * Eg. If oversized file is intended to send, MMS is filtered away from
        * "Send" pop-up list.
        *
        * The third option is to set the array of service uids not wanted to
        * be shown in list query. These sending services are filtered away
        * even if those match to required capabilities.
        * 
        * @since Series 60 3.0
        * @param aMessageData Data for the message. Attachments are used for
        *        content based filtering.
        * @param aRequiredCapabilities Capabilities required by sending services
        *        to be shown in "Send" pop-up list query. If no capabilities are
        *        required (KCapabilitiesForAllServices), all available services
        *        are shown in "Send" pop-up list query.
        * @param aServicesToDim Array of service uids (MTM or ECom) NOT wanted
        *        to "Send" list query. 
        *        Predefined sending service uids are defined in: SendUiConsts.h
        * @param aTitleText Title of the "Send" pop-up list query. If no title
        *		 is defined, then the localised default title "Send:" is used.        
        * @return Uid of the selected service (MTM or ECom). 
        *        KNullId is returned if user selects cancel.
        */
        IMPORT_C TUid ShowSendQueryL(
            const CMessageData* aMessageData = NULL,
            TSendingCapabilities aRequiredCapabilities = KCapabilitiesForAllServices,
            CArrayFix<TUid>* aServicesToDim = NULL,
            const TDesC& aTitleText = KNullDesC );

        /**
        * Creates the message and launches the editor for editing the message
        * or sends the message directly without opening the editor. 
        * Functionality depends on the type of selected service.
        *
        * If parameter aMtmUid is KsenduiMtmSmsUid and aBioTypeUid is
        * KmsgBioUidVCard and feature flag __SMARTMSG_SMS_VCARD_SENDING is not
        * supported then function leaves with error value KErrNotSupported.
        *
        * If parameter aMtmUid is KsenduiMtmSmsUid and aBioTypeUid is
        * KMsgBioUidVCalendar and feature flag __SMARTMSG_SMS_VCAL_SENDING is
        * not supported then function leaves with error value KErrNotSupported.
        *
        * @since Series 60 3.0
        * @param aServiceUid Uid of the sending service (MTM or ECom).
        * @param aMessageData Data for the message.
        * @param aBioTypeUid BIO message type uid.
        * @param aLaunchEditorEmbedded ETrue if the editor should be launched
        *        embedded. Otherwise the editor is launched stand-alone.
        *        Note: some sending services sends the messages without
        *        launching the editor at all.
        * @return None.
        */
        IMPORT_C void CreateAndSendMessageL(
            TUid aServiceUid,
            const CMessageData* aMessageData,
            TUid aBioTypeUid = KNullUid,
            TBool aLaunchEditorEmbedded = ETrue );

        /**
        * Validates that service is available and has required capabilities.
        * For ex. can be used when calling application creates its own "Send"
        * menu.
        * @since Series 60 3.0
        * @param aServiceUid Uid of the sending service (MTM or ECom).
        * @param aRequiredCapabilities Capabilities required for the sending
        *        service. 
        * @return ETrue if service is available and it has required 
        *         capabilities,otherwise EFalse.
        */
        IMPORT_C TBool ValidateServiceL(
            TUid aServiceUid,
            TSendingCapabilities aRequiredCapabilities );

        /**
        * Returns sending capabilities of the sending service.
        * @since Series 60 3.0
        * @param aServiceUid Uid of the sending service (MTM or ECom).
        * @param aServiceCapabilities TSendingCapabilities of the sending
        *        service as a return value.        
        * @return Return KErrNone if successful, or one of the system wide
        *         errors if unsuccessful.
        */
        IMPORT_C TInt ServiceCapabilitiesL(
            TUid aServiceUid,
            TSendingCapabilities& aServiceCapabilities );       
       
        /**
        * Can be used to check if sending of bio message is supported.
        * @since Series 60 3.0
        * @param aBioMessageUid Uid of the bio message.
        * @return: ETrue if sending of bio message is supported, otherwise
        *          EFalse.
        */
        IMPORT_C TBool CanSendBioMessage( TUid aBioMessageUid ) const;

        /**
        * Populates given list with the information about services
        * provided by specified ECom service provider.
        * Each service provider can provide 1..n services.
        * Ownership of the pointed objects are transfered to caller.
        *
        * Can be used for ex. when creating own "Send" menu, which needs to
        * include ECom based services.
        *
        * NOTE: Can be used only for ECom based services, NOT for MTMs
        *
        * @since Series 60 2.8
        * @param aServiceList Service list to be populated.
        * @param aServiceProvider Id of the specified service provider.
        *        KNullId means all service providers.
        *        Service providers are defined in SendUiConsts.h
        * @return none
        */
        IMPORT_C void AvailableServicesL(
            RPointerArray<CSendingServiceInfo>& aServiceList,
            TUid aServiceProvider = KNullUid);

        // Menu type enumeration
        enum TSendUiMenuType
            {
            ESendMenu,
            EWriteMenu
            };

        /**
        * Adds menu item of given type to menupane.
        *
        * @since Series 60 3.0
        * @param aMenuType Type of the menu, e.g. "ESendMenu" or "EWriteMenu"
        * @param aMenuPane Menupane where the menu item should be added.
        * @param aIndex The place of the menu item in menupane.
        * @param aCommandId Command id for the menu item.
        * @param aRequiredCapabilities Capabilities required from services to be
        *        shown in list query. If no capabilities are required
        *        (KCapabilitiesForAllServices), all available services are
        *        shown in list query.
        * @return None.
        */
        IMPORT_C void AddTypedMenuItemL(
            TSendUiMenuType aMenuType, 
            CEikMenuPane& aMenuPane,
            TInt aIndex,
            TInt aCommandId,
            TSendingCapabilities aRequiredCapabilities = KCapabilitiesForAllServices );

        /**
        * Displays list query and creates message.
        * See ShowQueryAndSendL.
        *
        * @since Series 60 3.0
        * @param aMenuType Type of the menu, e.g. "ESendMenu" or "EWriteMenu"
        * @param aMessageData Data for the message.
        * @param aRequiredCapabilities Capabilities required by sending services
        *        to be shown in "Send" pop-up list query. If no capabilities are
        *        required (KCapabilitiesForAllServices), all available services
        *        are shown in "Send" pop-up list query.
        * @param aServicesToDim Array of service uids (MTM or ECom) NOT wanted
        *        to "Send" list query. 
        *        Predefined sending service uids are defined in: SendUiConsts.h
        * @param aBioTypeUid BIO message type uid.
        * @param aLaunchEditorEmbedded ETrue if the editor should be launched
        *        embedded. Otherwise the editor is launched stand-alone.
        *        Note: some services sends the messages without launching the
        *        editor at all.
        * @param aTitleText Title of the list query. If no title is defined,
        *        then the localised default title is used, e.g. "Send" or 
        *        "Write".
        * @return None.
        */
        IMPORT_C void ShowTypedQueryAndSendL(
            TSendUiMenuType aMenuType, 
            const CMessageData* aMessageData,
            TSendingCapabilities aRequiredCapabilities = KCapabilitiesForAllServices,
            CArrayFix<TUid>* aServicesToDim = NULL,
            TUid aBioTypeUid = KNullUid,
            TBool aLaunchEditorEmbedded = ETrue,
            const TDesC& aTitleText = KNullDesC );

        /**
        * Displays list query and returns the user selection.
        * See ShowSendQueryL.
        * 
        * @since Series 60 3.0
        * @param aMenuType Type of the menu, e.g. "ESendMenu" or "EWriteMenu"
        * @param aMessageData Data for the message. Attachments are used for
        *        content based filtering.
        * @param aRequiredCapabilities Capabilities required by sending services
        *        to be shown in list query. If no capabilities are required
        *        (KCapabilitiesForAllServices), all available services are 
        *        shown in list query.
        * @param aServicesToDim Array of service uids (MTM or ECom) NOT wanted
        *        to list query. 
        *        Predefined sending service uids are defined in: SendUiConsts.h
        * @param aTitleText Title of the list query. If no title is defined,
        *        then the localised default title is used, e.g. "Send" or 
        *        "Write"
        * @return Uid of the selected service (MTM or ECom). 
        *        KNullId is returned if user selects cancel.
        */
        IMPORT_C TUid ShowTypedQueryL(
            TSendUiMenuType aMenuType, 
            const CMessageData* aMessageData = NULL,
            TSendingCapabilities aRequiredCapabilities = KCapabilitiesForAllServices,
            CArrayFix<TUid>* aServicesToDim = NULL,
            const TDesC& aTitleText = KNullDesC );

    private:

        /**
        * C++ default constructor.
        */
        CSendUi();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private:    // Data
        // SendUi API implmentation. Owned.
        CSendUiImpl*                        iSendUiImpl;
    };

#endif      // CSENDUI_H

// End of File
