/*
* ==============================================================================
*  Name        : CDownloadMgrUiUserInteractions.h
*  Part of     : Download Manager / UI Lib
*  Interface   : UI Lib, User Interaction and Dialogs
*  Description : Supports user interaction dialogs for downloads
*  Version     : -
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


#ifndef CDOWNLOADMGRUIUSERINTERACTIONS_H
#define CDOWNLOADMGRUIUSERINTERACTIONS_H

//  INCLUDES
#include <CDownloadMgrUiBase.h>
#include <DownloadMgrClient.h>
#include <vwsdef.h>

// DATA TYPES
enum TClientAppExitType
    {
    ETerminatedByUser,
    ETerminatedBySystem
    };

/// User Interactions attributes
enum TUserInteractionsAttribute
    {
    /**
    * Type: TBool
    * Description: If EFalse, completed download is not handled
    */
    EUiLibAttrCompletedStateHandling = 1
    }; 

// FORWARD DECLARATIONS
class CUserInteractionsUtils;
class MDownloadMgrUiLibRegModel;
class CAsyncEventHandlerArray;
class CEikAppUi;
class CUserInteractionsExtension;

// CLASS DECLARATION

/**
*  The User Interactions supports the followings:
*  - User confirmation when content-type header arrives
*  - Handling completed downloads
*  - Querying HTTP authentication credentials
*  - Querying proxy authentication credentials
*  - Error notification
*  - Client App termination by the User
*
*  @lib Download Manager UI Lib
*  @since Series 60 2.8
*/
NONSHARABLE_CLASS( CDownloadMgrUiUserInteractions ) : public CDownloadMgrUiBase,
                                                      public MHttpDownloadMgrObserver
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        static CDownloadMgrUiUserInteractions* NewL
               ( MDownloadMgrUiLibRegModel& aRegistryModel );
        
        /**
        * Destructor.
        */
        virtual ~CDownloadMgrUiUserInteractions();

    public: // New functions

        /**
        * Client Apps can call this function before exiting the application. 
        * It should be called when the user terminates the application. 
        * It opens a confirmation query.
        * @return OK to exit? True/False. It is only a suggested value!
        */
        IMPORT_C TBool OkToExitL();

        /**
        * Client Apps can call this function in the App UI's destructor. 
        * It has been made non-leavable, so it can be called without TRAP.
        * It initializes Grouped Soft Notifications, if necessary.
        * @param aAppUi Reference to the actual App UI.
        * @param aExitType Exit type when this function is called.
        * @param aViewId View ID of the view where to switch in case user chooses
        *                accept softkey in the soft notification.
        * @param aCustomMessageId Custom message ID.
        * @param aViewActivationMsg Custom message sent to the view in 
        *                           the view activation process.
        * @return Error code or KErrNone.
        */
        IMPORT_C TInt PrepareToExit( CEikAppUi& aAppUi, 
                                     TClientAppExitType aExitType, 
                                     TVwsViewId aViewId, 
                                     TUid aCustomMessageId, 
                                     const TDesC8& aViewActivationMsg );

        /**
        * Currently it supports handling completed download.
        * @param aDownload The actual download
        * @return -
        */
        IMPORT_C void HandleDownloadL( RHttpDownload& aDownload );

        /**
        * The number of download confirmations being shown.
        * @return Non-negative integer value.
        */
        TInt DownloadConfirmationsShown() const;

    public: // Functions from CDownloadMgrUiBase

        IMPORT_C virtual void GetIntAttributeL( const TUint aAttribute, TInt32& aValue );
        IMPORT_C virtual void GetBoolAttributeL( const TUint aAttribute, TBool& aValue );
        IMPORT_C virtual void GetStringAttributeL( const TUint aAttribute, TDes16& aValue  );
        IMPORT_C virtual void GetStringAttributeL( const TUint aAttribute, TDes8& aValue  );
        IMPORT_C virtual void SetIntAttributeL( const TUint aAttribute, TInt32 aValue );
        IMPORT_C virtual void SetBoolAttributeL( const TUint aAttribute, TBool aValue );
        IMPORT_C virtual void SetStringAttributeL( const TUint aAttribute, const TDesC16& aValue );
        IMPORT_C virtual void SetStringAttributeL( const TUint aAttribute, const TDesC8& aValue );

    protected: // Constructors

        /**
        * C++ default constructor.
        */
        CDownloadMgrUiUserInteractions( MDownloadMgrUiLibRegModel& aRegistryModel );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    protected: // New functions

        // Event handler functions

        /**
        * Handle download completion with query (wait) dialog.
        * @param aDownload The actual download
        * @return -
        */
        void HandleCompletionWithQueryL( RHttpDownload& aDownload );

        /**
        * Leaving version of PrepareToExit().
        * @return None.
        */
        void PrepareToExitL( CEikAppUi& aAppUi, 
                             TClientAppExitType aExitType, 
                             TVwsViewId aViewId, 
                             TUid aCustomMessageId, 
                             const TDesC8& aViewActivationMsg );

        /**
        * Is a stand-alone instance running from the very same application?
        * @return True/False.
        */
        TBool IsStandAloneAppRunning( CEikAppUi& aAppUi );

    protected: // Functions from MHttpDownloadMgrObserver

        virtual void HandleDMgrEventL( RHttpDownload& aDownload, 
                                       THttpDownloadEvent aEvent );

    private:  // Data
        
        CUserInteractionsExtension* iExtension; ///< Extension class, Owned.

        CUserInteractionsUtils*     iUiUtils; ///< Owned.
        CAsyncEventHandlerArray*    iEventHandlerArray; ///< Owned.

    private: // Friend classes

        friend class CUserInteractionsExtension;
    };

#endif /* CDOWNLOADMGRUIUSERINTERACTIONS_H */
