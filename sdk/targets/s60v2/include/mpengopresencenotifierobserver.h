/*
* ==============================================================================
*  Name        : MPEngOPresenceNotifierObserver.h
*  Part of     : Presence API
*  Interface   : CPEngOPresenceNotifierObserver
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


#ifndef _MPENGOPRESENCENOTIFIEROBSERVER_H
#define _MPENGOPRESENCENOTIFIEROBSERVER_H

// FORWARD DECLARATIONS
class CPEngOPresenceNotifier;

/**
* This is the observer interface of the CPEngOPresenceNotifier interface
* These functions must be implemented in order to handle the results
*
* @since Series 60 2.1
*/

class MPEngOPresenceNotifierObserver
    {
    public:
        /**
        * This method is called when the registering is complete.
        * @since Series 60 2.1
        * @param aErrorCode error codes 
        *        KErrNone if registering was succesfull
        *        KOPEngErrPENotLogged if Presence Engine is not logged. The 
        *        notifier will remain in unregistered state in this case
        */
        virtual void HandleNotifierRegisterL( 
                        const TInt aErrorCode ) = 0;

        /**
        * This method is called when the results from a call to 
        * SubscribePresence or UnSubscribePresence are ready.
        * @since Series 60 2.1
        * @param aNotifier Pointer to the CPEngOPresenceNotifier instance
        *       where the results can be retrieved.
        * @param aStatus is KErrNone if everything went ok.
        *         KOPEngErrNothingWasSubscribed if nothing couldn't be 
        *         subscribed
        *         KOPEngErrPartialSubscription if subscription or 
        *         removing was partially successfull
        */
        virtual void HandleSubscribeCompletedL( 
                        CPEngOPresenceNotifier* aNotifier,
                        TInt aStatus ) = 0;

        /**
        * This method is called when the subscribtion status of some
        * subscribed presence has changed.
        * @since Series 60 2.1
        * @param aNotifier Pointer to the CPEngOPresenceNotifier instance
        *       where the results can be retrieved.
        */
        virtual void HandleSubscribeChangedL( 
                        CPEngOPresenceNotifier* aNotifier ) = 0;

        /**
        * This method is called when the status of some observed
        * contact has changed.
        * @since Series 60 2.1
        * @param aNotifier Pointer to the CPEngOPresenceNotifier instance
        *       where the results can be retrieved.
        * @param aStatus is KErrNone if everything went ok.
        *         KOPEngErrNothingWasSubscribed if nothing couldn't be 
        *         subscribed
        *         KOPEngErrPartialSubscription if subscription or 
        *         removing was partially successfull
        */
        virtual void HandlePresenceChangedL(
                        CPEngOPresenceNotifier* aNotifier,
                        TInt aStatus ) = 0;

    };


#endif // _MPENGOPRESENCENOTIFIEROBSERVER_H
            
// End of File
