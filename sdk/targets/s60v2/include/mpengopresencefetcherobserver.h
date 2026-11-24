/*
* ==============================================================================
*  Name        : MPEngOPresenceFetcherObserver.h
*  Part of     : Presence API
*  Interface   : MPEngOPresenceNotifierObserver
*  Description : Observer interface for PEngOpenPresence.dll ECOM plugin
*  Version     : 1.0
*
*  Copyright © 2003 Nokia Corporation.
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


#ifndef _MPENGOPRESENCEFETCHEROBSERVER_H
#define _MPENGOPRESENCEFETCHEROBSERVER_H

// FORWARD DECLARATIONS
class CPEngOPresenceFetcher;

/**
* This is the observer interface of the CPEngOPresenceFetcher interface
* These functions must be implemented in order to handle the results.
*  
* @since Series 60 2.1
*/

class MPEngOPresenceFetcherObserver
    {
    public:

        /**
        * This method is called when the registering is complete.
        * @since Series 60 2.1
        * @param aErrorCode error codes 
        *        KErrNone if registering was succesfull
        *        KOPEngErrPENotLogged if Presence Engine is not logged. The 
        *        fetcher will remain in unregistered state in this case
        */
        virtual void HandleFetcherRegisterL( 
                        const TInt aErrorCode ) = 0;

        /**
        * This method is called when the results from a call to GetByAttribute
        * function are ready.
        * Results are retrieved by using the FetchedPresenceIDsLC function.
        * @since Series 60 2.1
        * @param aFetcher Pointer to the CPEngOPresenceFetcher instance
        *       where the results can be retrieved.
        * @param aStatus is the value indicating the success of the fetch.
        *               KErrNone if succesfull.
        */
        virtual void HandleGetByAttributeL( 
                        CPEngOPresenceFetcher* aFetcher, TInt aStatus ) = 0;

        /**
        * This method is called when the results from a call to GetAttribute 
        * function are ready.
        * Results are retrieved by using the FetchedPresenceDataLC function.
        * @since Series 60 2.1
        * @param aFetcher Pointer to the CPEngOPresenceFetcher instance
        *       where the results can be retrieved.
        * @param aStatus is the value indicating the success of the fetch.
        *               KErrNone if succesfull.
        */
        virtual void HandleGetAttributeL( 
                        CPEngOPresenceFetcher* aFetcher, TInt aStatus ) = 0;
    };


#endif // _MPENGOPRESENCEFETCHEROBSERVER_H
            
// End of File
