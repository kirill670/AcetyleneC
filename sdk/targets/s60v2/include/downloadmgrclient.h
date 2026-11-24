/*
* ==============================================================================
*  Name        : DownloadMgrClient.h
*  Part of     : DownloadMgrClntSrv / DownloadMgr
*  Interface   : ?Interface_category, ?Interface_name
*  Description : This file contains the definition of the Client interface of Download Mgr Server.
*  Version     : ?Version
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

#ifndef __DOWNLOADMGR_CLIENT_H__
#define __DOWNLOADMGR_CLIENT_H__

//  INCLUDES
#include <e32base.h>
#include <f32file.h>
#include <HttpDownloadMgrCommon.h>

// DATA TYPES

// FORWARD DECLARATIONS
class CDownloadMgrHandler;
class RHttpDownload;
class MHttpDownloadMgrObserver;
class CDefaultAttrib;
class CRHttpDownloadExtension;
class CRHttpDownloadMgrExtension;

// TYPEDEFS
typedef CArrayPtrFlat< RHttpDownload > CDownloadArray;
typedef CArrayPtrFlat< MHttpDownloadMgrObserver >  CDownloadMgrObserver;

// CLASS DECLARATION

/**
*  Contains download states
*
*  @lib -
*  @since Series 60 2.8
*/
NONSHARABLE_CLASS( THttpDownloadEvent )
    {
    public: // Data
        // download state
        THttpDownloadState iDownloadState;
        // download progress state
        THttpProgressState iProgressState;
    };

/**
*  Provides the interface for notification of events from a Download Manager 
*  session and its subsessions.
*
*  @lib -
*  @since Series 60 2.8
*/
class MHttpDownloadMgrObserver
    {

    public:

        /**
        * Indicates an event.
        * @param aDownload The download with which the event occured.
        * @param aEvent Event type.
        * @return None.
        */
        virtual void HandleDMgrEventL( RHttpDownload& aDownload, THttpDownloadEvent aEvent ) = 0;
    };

/**
*  Creates a download manager session and performs operations on it 
*
*  @lib -
*  @since Series 60 2.8
*/
NONSHARABLE_CLASS( RHttpDownloadMgr ) : public RSessionBase,
                                        public MHttpDownloadMgrObserver
	{
    public:
        /**
        * C++ default constructor.
        */
        IMPORT_C RHttpDownloadMgr();

    public:  // New functions

        /**
        * Creates a download manager session.
        * @param aAppUid Client application's UID.
        * @param aObserver Observer
        * @param aMaster Indicates whether (if ETrue) this instance 
        * inherints all downloads of other instances. (stand-alone app flag).
        * @return None.
        */
        IMPORT_C void ConnectL( TUid aAppUid,
                                MHttpDownloadMgrObserver& aObserver,
                                TBool aMaster );

        /**
        * Gives version information.
        * @param -
        * @return TVersion Contains version information.
        */
        IMPORT_C TVersion Version() const;

        /**
        * Closes download manager session.
        * @param -
        * @return None.
        */
        IMPORT_C void Close();

        /**
        * Returns a list of the current downloads.
        * @param -
        * @return CDownloadArray
        */
        IMPORT_C const CDownloadArray& CurrentDownloads() const;

        /**
        * Creates a new download subsession.
        * @param aUrl The url to be downloaded.
        * @param aResult The result is true if the download is created.
        * If the URL is already being downloaded the seult is false.
        * @return RHttpDownload&
        */
        IMPORT_C RHttpDownload& CreateDownloadL( const TDesC8& aUrl, TBool& aResult );

        /**
        * Pauses all downloads.
        * @param -
        * @return None.
        */
        IMPORT_C TInt PauseAll();

        /**
        * Resumes all downloads.
        * @param -
        * @return None.
        */
        IMPORT_C TInt StartAll();

        /**
        * Resets all downloads.
        * @param -
        * @return None.
        */
        IMPORT_C TInt ResetAll();

        /**
        * Deletes all downloads.
        * @param -
        * @return None.
        */
        IMPORT_C TInt DeleteAll();

        /**
        * Disconnect the http connection and pauses all downloads.
        * @param -
        * @return None.
        */
        IMPORT_C TInt Disconnect();

		/**
		* Gets the value for a TInt attribute.
		* @param aAttribute Identifies the attribute to be retrived.
		* @param aValue On completion, contains the requested TInt attribute.
        * @return None.
		*/
		IMPORT_C TInt GetIntAttribute( const TUint aAttribute, TInt32& aValue );

		/**
		* Gets the value for a TBool attribute.
		* @param aAttribute Identifies the attribute to be retrived.
		* @param aValue On completion, contains the requested TBool attribute.
        * @return None.
		*/
		IMPORT_C TInt GetBoolAttribute( const TUint aAttribute, TBool& aValue );

		/**
		* Gets the value for a TDes16 attribute.
		* @param aAttribute Identifies the attribute to be retrived.
		* @param aValue On completion, contains the requested TDes16 attribute.
        * @return None.
		*/
		IMPORT_C TInt GetStringAttribute( const TUint aAttribute, TDes16& aValue  );

		/**
		* Gets the value for a TDes8 attribute.
		* @param aAttribute Identifies the attribute to be retrived.
		* @param aValue On completion, contains the requested TDes8 attribute.
        * @return None.
		*/
        IMPORT_C TInt GetStringAttribute( const TUint aAttribute, TDes8& aValue  );

		/**
		* Sets the value for a TInt attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
		IMPORT_C TInt SetIntAttribute( const TUint aAttribute, TInt32 aValue );

		/**
		* Sets the value for a TBool attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
		IMPORT_C TInt SetBoolAttribute( const TUint aAttribute, TBool aValue );

		/**
		* Sets the value for a TDesC attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
		IMPORT_C TInt SetStringAttribute( const TUint aAttribute, const TDesC16& aValue );

		/**
		* Sets the value for a TDesC8 attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
        IMPORT_C TInt SetStringAttribute( const TUint aAttribute, const TDesC8& aValue );

		/**
		* Sets the value for the default TInt attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
		IMPORT_C TInt SetDefaultIntAttribute( const TUint aAttribute, TInt32 aValue );

		/**
		* Sets the value for the default TBool attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
		IMPORT_C TInt SetDefaultBoolAttribute( const TUint aAttribute, TBool aValue );

		/**
		* Sets the value for the default TDesC attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
		IMPORT_C TInt SetDefaultStringAttribute( const TUint aAttribute, const TDesC16& aValue );

		/**
		* Sets the value for the default TDesC8 attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
        IMPORT_C TInt SetDefaultStringAttribute( const TUint aAttribute, const TDesC8& aValue );

		/**
		* Adds client to the observer list.
		* @param aObserver Observer.
        * @return None.
		*/
        IMPORT_C void AddObserverL( MHttpDownloadMgrObserver& aObserver );

		/**
		* Removes client from the observer list.
		* @param aObserver Observer.
        * @return None.
		*/
        IMPORT_C void RemoveObserver( MHttpDownloadMgrObserver& aObserver );

    protected: // from MHttpDownloadMgrObserver

        /**
        * Indicates an event.
        * @param aDownload The download with which the event occured.
        * @param aEvent Event type.
        * @return None.
        */
        void HandleDMgrEventL( RHttpDownload& aDownload, THttpDownloadEvent aEvent );

    private:

        /**
        * Indicates the session's event.
        * @param aHandle Unique identifier of server side subsession.
        * @param aEvent Event type.
        * @return None.
        */
        void HandleSessionEventL( TInt aHandle, THttpDownloadEvent aEvent );

    private:  // New functions

        /**
        * Initializes the download manager session.
        * @param aAppUid Client app's UID.
        * @param aObserver Observer to add to the observer list.
        * @param aMaster Indicates whether (if ETrue) this instance 
        * inherints all downloads of other instances. (stand-alone app flag).
        * @return None.
        */
        void InitializeL( TUid aAppUid,
                          MHttpDownloadMgrObserver& aObserver,
                          TBool aMaster );

        /**
        * Adds the created download to the list. If it is already added, 
        * then it will do nothing.
        * @param aElement Download subsession.
        * @return RHttpDownload& reference to the added item in the list.
        */
        RHttpDownload& AddToArrayL( RHttpDownload* aElement );

        /**
        * Removes the download from the list.
        * @param aElement Download subsession.
        * @return None.
        */
        void RemoveFromArray( RHttpDownload* aElement );

        /**
        * Finds the download in the list.
        * @param aElement Download subsession.
        * @param aIndex Index of the element found.
        * @return KErrNone if found, KErrNotFound otherwise..
        */
        TInt FindInArray( RHttpDownload* aElement, TInt& aIndex ) const;

        /**
        * Returns a reference to the download identified by a handle.
        * @param aHandle Handle identifier.
        * @return RHttpDownload&
        */
        RHttpDownload& DownloadFromHandleL( TUint aHandle );

        /**
        * Finds observer based on index.
        * @param aObserver Observer found.
        * @param aIndex Index.
        * @return TInt
        */
        TInt FindObserver( MHttpDownloadMgrObserver& aObserver, TInt& aIndex ) const;

        /**
        * Attach client to the session.
        * @param aBuf Buffer to the subsession IDs.
        * @return None.
        */
        void AttachL( const TDesC8& aBuf );

        /**
        * Close a download subsession.
        * @param aElement Download subsession.
        * @return None.
        */
        void CloseDownload( RHttpDownload* aElement );

		/**
		* Creates buffer for the default attributes.
		* @param -
        * @return None.
		*/
        HBufC8* AllocDefAttribBufLC();

		/**
		* Packes the default values of the attributes.
		* @param -
        * @return bbuffer of the packed attribs.
		*/
        HBufC8* PackedDefaultAttributesLC();

		/**
		* Sets the default value for the TInt32 attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
        void DoSetDefaultAttributeL( const TUint aAttribute, TInt32 aValue );

		/**
		* Sets the default value for the TBool attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
        void DoSetDefaultAttributeL( const TUint aAttribute, TBool aValue );

		/**
		* Sets the default value for the TDesC8 attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
        void DoSetDefaultAttributeL( const TUint aAttribute, const TDesC8& aValue );

		/**
		* Sets the default value for the TDesC16 attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
        void DoSetDefaultAttributeL( const TUint aAttribute, const TDesC16& aValue );

        /**
        * Start session's event notification.
        * @param aStatus Handler's request status.
        * @return None.
        */
        void StartSessionEventNotification( const TDesC8& aDownloadState,
                                            const TDesC8& aProgressState,
                                            const TDesC8& aHandle,
                                            TRequestStatus& aStatus );

        /**
        * Cancels session's event notification.
        * @param -
        * @return None.
        */
        void CancelSessionEventNotification();

    private:     // Data
        // The client application UID.
        TUid                             iAppUid;
        // List of downloads.
        CDownloadArray*                  iDownloadArray;  ///< Owned.
        // List of observers.
        CDownloadMgrObserver*            iObservers;      ///< Owned.
        // Default attributes.
        CArrayPtrFlat< CDefaultAttrib >* iDefaultAttribs; ///< Owned.
        // Moved event handler
        CDownloadMgrHandler*             iManagerHandler; ///< Owned.
        // Extension class
        CRHttpDownloadMgrExtension*      iExtension;      ///< Owned.

    public:     // Friend classes

        friend class RHttpDownload;
        friend class CDownloadMgrHandler;
	};

/**
*  Creates a download manager subsession and performs operations on it 
*
*  @lib -
*  @since Series 60 2.8
*/
NONSHARABLE_CLASS( RHttpDownload ): public RSubSessionBase
	{
    private:

        /**
        * C++ default constructor.
        */
        RHttpDownload( RHttpDownloadMgr* aServer );

    public:  // New functions

        /**
        * Starts downloading.
        * @param -
        * @return None.
        */
        IMPORT_C TInt Start();

        /**
        * Pauses downloading.
        * @param -
        * @return None.
        */
        IMPORT_C TInt Pause();

        /**
        * Resets downloading.
        * @param -
        * @return None.
        */
        IMPORT_C TInt Reset();

        /**
        * Deletes downloading.
        * @param -
        * @return None.
        */
        IMPORT_C TInt Delete();

        /**
        * Moves downloaded content to the previously specified location
        * @param -
        * @return None.
        */
        IMPORT_C TInt Move();

		/**
		* Gets the value for a TInt attribute.
		* @param aAttribute Identifies the attribute to be retrived.
		* @param aValue On completion, contains the requested TInt attribute.
        * @return None.
		*/
		IMPORT_C TInt GetIntAttribute( const TUint aAttribute, TInt32& aValue );

		/**
		* Gets the value for a TBool attribute.
		* @param aAttribute Identifies the attribute to be retrived.
		* @param aValue On completion, contains the requested TBool attribute.
        * @return None.
		*/
		IMPORT_C TInt GetBoolAttribute( const TUint aAttribute, TBool& aValue );

		/**
		* Gets the value for a TDes16 attribute.
		* @param aAttribute Identifies the attribute to be retrived.
		* @param aValue On completion, contains the requested TDes16 attribute.
        * @return None.
		*/
		IMPORT_C TInt GetStringAttribute( const TUint aAttribute, TDes16& aValue  );

		/**
		* Gets the value for a TDes8 attribute.
		* @param aAttribute Identifies the attribute to be retrived.
		* @param aValue On completion, contains the requested TDes8 attribute.
        * @return None.
		*/
        IMPORT_C TInt GetStringAttribute( const TUint aAttribute, TDes8& aValue  );

        /**
        * Gets the download's destination file's handle.
        * @param aFile RFile that adopts file handle from download.
        */
        IMPORT_C TInt GetFileHandleAttribute( RFile& aFile );
        
		/**
		* Sets the value for a TInt attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
		IMPORT_C TInt SetIntAttribute( const TUint aAttribute, TInt32 aValue );

		/**
		* Sets the value for a TDesC attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
		IMPORT_C TInt SetBoolAttribute( const TUint aAttribute, TBool aValue );

		/**
		* Sets the value for a TDesC attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
		IMPORT_C TInt SetStringAttribute( const TUint aAttribute, const TDesC16& aValue );

		/**
		* Sets the value for a TDesC8 attribute.
		* @param aAttribute Identifies the attribute to be set.
		* @param aValue The value to be set.
        * @return None.
		*/
        IMPORT_C TInt SetStringAttribute( const TUint aAttribute, const TDesC8& aValue );

        /**
        * Sets the download's destination file handle.
        * @param aFile RFile to be transfered to server.
        * @return KErrNotSupported on non-EKA2 platform.
        * @return KErrBadHandle is file is not opened.
        */
        IMPORT_C TInt SetFileHandleAttribute( RFile& aFile );

    public: // New functions

        /**
        * Closes download subsession.
        * @param -
        * @return None.
        */
        void Close();

    private: // New functions

        /**
        * Creates download subsession.
        * @param aUrl The url to be downloaded.
        * @return None.
        */
        void CreateL( const TDesC8& aUrl, const TPtr8 aPackedAttribs );

        /**
        * Attaches subsession to the server subsession by handle.
        * @param aHandle A handle which identifies the server subsession.
        * @return None.
        */
        void AttachL( TInt aHandle );

        /**
        * Start event notification.
        * @param aStatus Handler's request status.
        * @return None.
        */
        void StartEventNotification( const TDesC8& aDownloadState,
                                     const TDesC8& aProgressState,
                                     TRequestStatus& aStatus );

        /**
        * Cancels event notification.
        * @param -
        * @return None.
        */
        void CancelEventNotification();

        /**
        * Returns true if the handle is equals with the stored one.
        * @param aHandle Handle.
        * @return TBool.
        */
        TBool IsDownload( TInt aHandle );

		/**
		* Sets the default value for the attributes.
		* @param aDownload The download which default attributes to be set.
        * @return None.
		*/
        void SetDefaultAttributesL( const TDesC8& aPackedAttribs );

		/**
		* Buffers attributes which need when a client deletes download.
		* @param None.
        * @return None.
		*/
        void BufferAttributesL();

		/**
		* Sets event type.
		* @param aEventType.
        * @return None.
		*/
        void SetEventType( THttpDownloadState aEventType );

    private:    // Data
        // Event notification handler.
        CDownloadMgrHandler*     iDownloadHandler;  ///< Owned.
        // Download manager session.
        RHttpDownloadMgr*        iDownloadMgr;      ///< NOT Owned.
        // Unique identifier of server side subsession.
        TInt                     iHandle;
        // Extension class
        CRHttpDownloadExtension* iExtension;        ///< Owned.

    public:     // Friend classes
 
        friend class CDownloadMgrHandler;
        friend class RHttpDownloadMgr;

	};

#endif /* __DOWNLOADMGR_CLIENT_H__ */

