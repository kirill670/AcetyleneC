/*
* ==============================================================================
*  Name        : imconnection.h
*  Part of     : IM SDK API
*  Description : IM Connection interface
*  Version     : 1.0
*
*  Copyright (c) 2004, 2005 Nokia Corporation.
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

#ifndef IMCONNECTION_H
#define IMCONNECTION_H

// INCLUDES
#include <e32base.h>
#include <ecom.h>

// DATA TYPES
enum TImConnectionStatus
    {
    ELoggedIn = 0,
    ENotLoggedIn
    };

// FORWARD DECLARATIONS
class MImClient;
class MImConnectionObserver;

// CLASS DECLARATION

/**
*  Instant Messaging API class
*  By creating this class the user automatically connects to the Symbian server
*  but to do something reasonable the IM interface has to be created using 
*  this class. The following order of calling the methods is one possibility to 
*  use this class:
*  1. NewL() - instantiate the object
*  2. RegisterObserverL() - register the observer methods
*  3. LoginL() - connect to the protocol stack and login to remote IM server
*  4. CreateImClientL() - get the IM interface
*
*  All the error codes are returned using the leave mechanism.
*
*  @lib imclient.dll
*  @since Series 60 3.0
*/
class CImConnection : public CBase
    {
    public:

        /**
        * Factory method for creating the class instance.
        * @since Series 60 3.0
        * @param aClientId the ClientId of the application
        * @return CImConnection
        */
        static CImConnection* NewL( 
            const TDesC& aApplicationId );
        
        // Destructor
	    virtual ~CImConnection( );


    public: // New functions
        
        /**
        * Creates the IM interface to sending and receiving IMs
        * @since Series 60 3.0
        * @return MImClient
        */
        virtual MImClient* CreateImClientL( ) = 0;

        /**
        * Method for registering the IM Connection observer to the API.
        * This method is synchronous.
        * The method can leave with the following reasons:
        * 	KImApiErrAlreadyRegistered - if it was registered already
        * 	or other system wide error code
        * @since Series 60 3.0
        * @param aObserver observer object which receives the notification
        */
        virtual void RegisterObserverL(
            MImConnectionObserver* aObserver ) = 0;

        /**
        * Method for unregistering the IM Connection observer.
        * This method is synchronous.
        * @since Series 60 2.6
        */
        virtual void UnregisterObserver( ) = 0;

        /**
        * Method for getting the connection status.
        * This method is synchronous.
        * @since Series 60 3.0
        * @return connection status enum
        */
        virtual TImConnectionStatus ImConnectionStatus( ) = 0;

        /**
        * Connects the application to the protocol stack and logs in to the 
        * remote SAP server using the given login info.
        * This method is asynchronous and the completion is signaled by
        * HandleLoginL() observer method.
        * Possible leave reasons:
        * 	KErrNotSupported - protocol mismatch
        *	KImApiErrLoginInProgress - already logging in
        *	KImApiErrLogoutInProgress - logout is ongoing
        *	KImApiErrCancelLoginInProgress - cancel login is ongoing
        *	KImApiErrAlreadyLoggedIn - already logged in
        * @since Series 60 3.0
        * @return connection status enum
        */
        virtual void LoginL( 
            const TDesC&  aServer,
            const TDesC&  aUserID,
            const TDesC&  aPassword,
            const TUint32 aAP ) = 0;

        /**
        * Cancels the ongoing login operation.
        * This method is asynchronous and the completion is signaled by
        * HandleCancelLoginL() observer method.
        * Possible leave reasons:
        * 	KErrNotSupported - protocol mismatch
        *	KImApiErrNotLogged - not logging in
        *	KImApiErrLogoutInProgress - logout is ongoing
        *	KImApiErrCancelLoginInProgress - cancel login is ongoing
        *	KImApiErrAlreadyLoggedIn - already logged in
        * @since Series 60 3.0
        */
        virtual void CancelLoginL( ) = 0;

        /**
        * Logs out from current session.
        * This method is asynchronous and the completion is signaled by
        * HandleLogoutL() observer method.
        * Possible leave reasons:
        * 	KErrNotSupported - protocol mismatch
        *	KImApiErrNotLogged - not logging in
        *	KImApiErrLogoutInProgress - logout is ongoing
        *	KImApiErrCancelLoginInProgress - cancel login is ongoing
        * @since Series 60 3.0
        */
        virtual void LogoutL( ) = 0;

    protected:
        // C++ constructor
        inline CImConnection( );

    private:
        // Unique instance identifier key (needed for ECom)
        TUid iDtor_ID_Key;
        
    };

/**
*  Connection Observer interface
*
*  @lib imclient.dll
*  @since Series 60 3.0
*/
class MImConnectionObserver
    {
    public:

        /**
        * Method is called when the LoginL() is completed.
        * @since Series 60 3.0
        * @param aErrorCode status code        
        */
        virtual void HandleLoginL( 
            const TInt aErrorCode ) = 0;

        /**
        * Method is called when the CancelLoginL() is completed.
        * @since Series 60 3.0
        * @param aErrorCode status code
        */
        virtual void HandleCancelLoginL( 
            const TInt aErrorCode ) = 0;

        /**
        * Method is called when the LogoutL() is completed.
        * Also called in situations when the Logout was initiated by the server
        * or another client which was using the same connection
        * @since Series 60 3.0
        * @param aErrorCode status code
        */
        virtual void HandleLogoutL(
            const TInt aErrorCode ) = 0;

    };

#include "imconnection.inl"

#endif
