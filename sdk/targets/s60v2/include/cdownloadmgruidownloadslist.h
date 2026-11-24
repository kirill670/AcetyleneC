/*
* ==============================================================================
*  Name        : CDownloadMgrUiDownloadsList.h
*  Part of     : Download Manager / UI Lib
*  Interface   : UI Lib, Downloads List
*  Description : Supports Download Menu and Downloads List
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


#ifndef CDOWNLOADMGRUIDOWNLOADSLIST_H
#define CDOWNLOADMGRUIDOWNLOADSLIST_H

//  INCLUDES
#include <CDownloadMgrUiBase.h>
#include <DownloadMgrClient.h>
#include <HttpDownloadMgrCommon.h>
#include <DownloadsListDlgObserver.h>

// FORWARD DECLARATIONS
class CDownloadMgrUiDownloadMenu;
class CDownloadMgrUiUserInteractions;
class CDownloadsListArray;
class CDownloadsListDlg;
class CUserInteractionsUtils;
class MDownloadMgrUiLibRegModel;
class CAsyncEventHandlerArray;
class CAsyncEventHandlerBase;
class CDownloadsListExtension;

// CLASS DECLARATION

/**
*  Display list of downloads.
*
*  @lib Download Manager UI Lib
*  @since Series 60 2.8
*/
NONSHARABLE_CLASS( CDownloadMgrUiDownloadsList ) : public CDownloadMgrUiBase, 
                                                   public MHttpDownloadMgrObserver,
                                                   public MDownloadsListDlgObserver
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        static CDownloadMgrUiDownloadsList* NewL
               ( MDownloadMgrUiLibRegModel& aRegistryModel );
        
        /**
        * Destructor.
        */
        virtual ~CDownloadMgrUiDownloadsList();

    public: // New functions

        // -------------------------------------------------------------
        // ************** Download Menu
        // -------------------------------------------------------------

        /**
        * Access the Download Menu utility.
        * @since Series 60 2.8
        * @return -
        */
        IMPORT_C CDownloadMgrUiDownloadMenu& DownloadMenu() const;

        // -------------------------------------------------------------
        // ************** Downloads List
        // -------------------------------------------------------------

        /**
        * Display the list of downloads.
        * @since Series 60 2.8
        * @return -
        */
        IMPORT_C void DisplayDownloadsListL();

        /**
        * Cancel displaying the list of downloads.
        * @since Series 60 2.8
        * @return -
        */
        IMPORT_C void CancelDisplayingDownloadsList();

        /**
        * Is the List of Downloads visible?
        * @since Series 60 2.8
        * @return ETrue/EFalse
        */
        IMPORT_C TBool IsVisible() const;

        /**
        * Number of downloads in the List of Downloads.
        * @since Series 60 2.8
        * @return TInt
        */
        IMPORT_C TInt Count() const;

        /**
        * Remove the given download from the list.
        */ 
        void DeleteDownloadL( RHttpDownload& aDownload );

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
        CDownloadMgrUiDownloadsList( MDownloadMgrUiLibRegModel& aRegistryModel );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    protected: // New functions

        // -------------------------------------------------------------
        // ************** List box utilities
        // -------------------------------------------------------------

        /**
        * Add downloads to the list residing in aDownloadMgr.
        * If a given download is already on the list, the list item is only updated.
        */ 
        void AddDownloadsToListModelL( CDownloadsListArray& aLBModel, 
                                       RHttpDownloadMgr& aDownloadMgr );

        /**
        * Add the download to the list.
        * If the download is already on the list, the list item is only updated.
        * This method should be used for adding new downloads - 
        * not for updating existing ones.
        * @return Returns the index relative to zero of the appended or updated item.
        */
        TInt AddDownloadToListModelL( CDownloadsListArray& aLBModel, 
                                      RHttpDownload& aDownload );

        // -------------------------------------------------------------
        // ************** Responses to download events
        // -------------------------------------------------------------

        void NewDownloadCreatedL( RHttpDownload& aDownload );
        void UpdateProgressInfoL( RHttpDownload& aDownload, THttpDownloadEvent aEvent );
        void DownloadPausedL( RHttpDownload& aDownload, THttpDownloadEvent aEvent );
        void DownloadCompletedL( RHttpDownload& aDownload, THttpDownloadEvent aEvent );
        void DownloadFailedL( RHttpDownload& aDownload, THttpDownloadEvent aEvent );
        void PauseableStateChangedL( RHttpDownload& aDownload, TBool aPausable );

        // -------------------------------------------------------------
        // ************** Other utility
        // -------------------------------------------------------------

        void HideMenu();
        TBool IsOnExternalMemory( const TDesC& aFileName ) const;

    protected: // Functions from MHttpDownloadMgrObserver

        virtual void HandleDMgrEventL( RHttpDownload& aDownload, THttpDownloadEvent aEvent );

    protected: // Functions from MDownloadsListDlgObserver

        virtual void PreLayoutDynInitL( CDownloadsListDlg& aDialog );
        virtual void ProcessCommandL( CDownloadsListDlg& aDialog, TInt aCommandId );
        virtual void DynInitMenuPaneL( CDownloadsListDlg& aDialog, TInt aResourceId, CEikMenuPane* aMenuPane );
        virtual TKeyResponse OfferKeyEventL( CDownloadsListDlg& aDialog, const TKeyEvent& aKeyEvent, TEventCode aType );

    private:  // Data
        
        CDownloadsListExtension*    iExtension; ///< Extension class. Owned.

        CUserInteractionsUtils*     iUiUtils; ///< Utility. Owned.
        CDownloadMgrUiDownloadMenu* iDownloadMenu; ///< Download Menu utility. Owned.
        CAsyncEventHandlerArray*    iEventHandlerArray; ///< Owned.
        CDownloadsListArray*        iListModel; ///< Association array: list item-download. Owned.
        CDownloadsListDlg*          iDialog; ///< Not owned - only reference.
        TBool                       iIsVisible; ///< Is the dialog visible?

    private: // Friend classes

        friend class CDownloadsListExtension;
    };

#endif /* CDOWNLOADMGRUIDOWNLOADSLIST_H */
