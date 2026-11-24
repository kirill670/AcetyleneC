/*
* ==============================================================================
*  Name        : CPEngOPresenceNotifier.h
*  Part of     : Presence API
*  Interface   : CPEngOPresenceNotifier
*  Description : Header file for ECOM plugin PEngOpenPresence.dll
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


#ifndef _CPENGOPRESENCENOTIFIER_H
#define _CPENGOPRESENCENOTIFIER_H

// INCLUDES
#include <e32base.h>
#include <ECom.h>
#include <cntdef.h>
#include "MPEngOPresenceAttributes.h"

// FORWARD DECLARATIONS
class MPEngOPresenceNotifierObserver;
class CContactIdArray;
class MPresenceAttribute;
class MPresenceIDData;


// UID of this interface
const TUid KCPEngOPresenceNotifierInterfaceUid = { 0x101FB0C1 };

/**
* CPEngOPresenceNotifier is interface definition for ECOM plugin used for
* making local subscriptions and for receiving presence notifications from 
* the network.
* The following functionality is supported by this interface:
* 1. Registering for notification/subscription operations
* 2. Unregistering from the operations
* 3. Making local subscription of presence
* 4. Making local unsubscription of presence
* 5. Adding observer(s) for presence notifications
* 6. Removing observer(s) of presence notifications
*
* Preconditions:
* Presence Engine must be online. Otherwise registering is not succesfull.
* Active Scheduler must be installed.
*
* Limitations:
* Only local subscriptions can be made. Subscriptions to the network
* must be made using the Phonebook. Notifications can only be received for 
* Contacts, textual user id's are not supported.
*
* @since Series 60 2.1
*/

class CPEngOPresenceNotifier : public CBase
    {
    public:
        /**
        * Default 1st phase factory method.
        * Creates an instance of CPEngOPresenceNotifier object using ECOM
        * framework.
        * If the plugin is not found the eCom will leave with KErrNotFound.
        * @since Series 60 2.1
        * @return created instance of the CPresenceNotifier class
        */
        static CPEngOPresenceNotifier* NewL( );

        /**
        * Destructor
        * @since Series 60 2.1
        */
        virtual ~CPEngOPresenceNotifier( );

        /**
        * Method for registering the presence notifier to the 
        * Presence API.
        * This method is asynchronous method and it will signal its 
        * completition using the HandleNotifierRegisterL function.
        * If the Presence Engine is not connected to the network
        * then the HandleNotifierRegisterL will return KOPEngErrPENotLogged.
        * Also in this case the notifier will remain in unregistered state.
        *
        * @since Series 60 2.1
        * @param aObserver observer object used for notifying the client 
        *                   software. Cannot be NULL.
        * @return Status codes 
        *         KErrNone if function call was succesfull.
        *         KOPEngErrAllReadyRegistered is returned 
        *         if we are allready registered.
        *         KOPEngErrRegisteringInProgress if registering is in progress
        */
        virtual TInt RegisterL( 
                        MPEngOPresenceNotifierObserver& aObserver ) = 0;

        /**
        * Method for unregistering the presence notifier from the 
        * Presence API.
        * This will remove all subscritions as well presence observers.
        * This method is synchronous method.
        *
        * @since Series 60 2.1
        * @return Status codes 
        *        KErrNone Unregistering succesfull.
        *        KOPEngErrNotRegistered if we were not registered   
        */
        virtual TInt UnRegisterL( ) = 0;

        /**
        * Method for subscribing the presence of some Contacts Model ID's
        * This method is asynchronous method and it will signal its 
        * completion using the HandleSubscribeCompletedL function.
        *
        * @since Series 60 2.1
        * @param aPresenceIDs Array of Contacts Model ID's
        * @return Status codes KErrNone if everything went ok
        *                      KOPEngErrNotRegistered if we are not registered.
        */
        virtual TInt SubscribePresenceL( 
                        const CContactIdArray& aPresenceIDs ) = 0;

        /**
        * Method for unsubscribing the presence of some Contacts Model ID's
        * This method is asynchronous method and it will signal its 
        * completion using the HandleSubscribeCompletedL function.
        *
        * @since Series 60 2.1
        * @param aPresenceIDs Array of Contacts Model ID's
        * @return Status codes KErrNone if everything went ok
        *                      KOPEngErrNotRegistered if we are not registered.
        */
        virtual TInt UnSubscribePresenceL( 
                        const CContactIdArray& aPresenceIDs ) = 0;

        /**
        * Method for adding an observer for Contacts Model ID for listening 
        * changes of some given attribute.
        * HandlePresenceChangedL function is called when presence of
        * some observed ID has changed.
        *
        * @since Series 60 2.1
        * @param aPresenceID Contacts Model ID to listen.
        * @param aAttribute which attribute to listen.
        * @return Status codes KErrNone if everything went ok
        *                      KOPEngErrNotRegistered if we are not registered.
        */
        virtual TInt AddObserverL( 
                        const TContactItemId& aPresenceID, 
                        const TAttributeType& aAttribute ) = 0;

        /**
        * Method for removing an observer.
        *
        * @since Series 60 2.1
        * @param aPresenceID Contacts Model ID .
        * @param aAttribute which attribute to remove.
        * @return Status codes KErrNone if everything went ok
        *                      KOPEngErrNotRegistered if we are not registered.
        */
        virtual TInt RemoveObserverL( 
                        const TContactItemId& aPresenceID, 
                        const TAttributeType& aAttribute ) = 0;

        /**
        * Method for getting subscribed presencies.
        * Ownership is transferred to caller.
        * @since Series 60 2.1
        * @return MPresenceIDData
        */
        virtual MPresenceIDData* SubscribedPresenciesLC( ) const = 0;

        /**
        * Method for getting a list of subscriptions which have been removed.
        * Ownership is transferred to caller.
        *
        * @since Series 60 2.1
        * @return ContactIdArray
        */
        virtual CContactIdArray* RemovedSubscriptionsLC( ) const = 0;

        /**
        * Method for getting array of changed presencies.
        * Ownership is transferred to caller.
        *
        * @since Series 60 2.1
        * @return ContactIdArray
        */
        virtual CContactIdArray* FailedSubscriptionsLC( ) const = 0;

        /**
        * Method for getting array of changed presencies.
        * Ownership is transferred to caller.
        *
        * @since Series 60 2.1
        * @return ContactIdArray
        */
        virtual CContactIdArray* ChangedPresenciesLC( ) const = 0;

        /**
        * Method for getting the changed attributes of a contact.
        * Ownership is transferred to caller.
        *
        * @since Series 60 2.1
        * @param aPresenceID Whose attributes to fetch
        * @param aModified array of attributes
        */
        virtual void GetChangedAttributesL( 
                                const TContactItemId& aPresenceID,
                                RPointerArray<MPresenceAttribute>& aModified 
                                ) const = 0;

    protected:
        /**
        *   Default c'tor
        */
        inline CPEngOPresenceNotifier();

    private:
        /** A unique UID used in interface destruction 
        */
        TUid    iDtor_ID_Key;

    };

#include "CPEngOPresenceNotifier.inl"

#endif // _CPENGOPRESENCENOTIFIER_H
            
// End of File
