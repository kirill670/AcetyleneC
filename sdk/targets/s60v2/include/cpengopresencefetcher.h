/*
* ==============================================================================
*  Name        : CPEngOPresenceFetcher.h
*  Part of     : Presence API
*  Interface   : CPEngOPresenceFetcher
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


#ifndef _CPENGOPRESENCEFETCHER_H
#define _CPENGOPRESENCEFETCHER_H

// INCLUDES
#include <e32base.h>
#include <badesca.h>
#include <ECom.h>
#include <MPEngOPresenceAttributes.h>

// FORWARD DECLARATIONS
class MPEngOPresenceFetcherObserver;
class CContactIdArray;
class MDesCArray;
class MPresenceIDData;
class MPresenceData;

// UID of this interface
const TUid KCPEngOPresenceFetcherInterfaceUid = { 0x101FB0BE };


/**
* CPEngOPresenceFetcher is interface definition for ECOM plugin used for
* fething presence attributes from the Presence Engine.
* The following functionality is supported by this interface:
* 1. Registering for fetching operations
* 2. Unregistering from the fetching operations
* 3. Get presence information of contacts based on given attributes
* 4. Get attribute values of desired contacts or textual user id's
*
* Supported attributes are: 
* UserAvailability, StatusContent and StatusText
*
* Preconditions:
* Presence Engine must be online otherwise registering is not succesfull.
* Active Scheduler must be installed.
*
* Limitations:
* This plugin only supports one fetch at a time. If multiple simultanous fetches 
* are required, multiple instances of this plugin must be used.
*
* @since Series 60 2.1
*/

class CPEngOPresenceFetcher : public CBase
    {
    public:
        /**
        * Default 1st phase factory method.
        * Creates an instance of CPEngOPresenceFetcher object using ECOM
        * framework.
        * If the plugin is not found the eCom will leave with KErrNotFound.
        * @since Series 60 2.1
        * @return created instance of the CPresenceFetcher class
        */
        static CPEngOPresenceFetcher* NewL( );

        /**
        * Destructor
        * @since Series 60 2.1
        */
        virtual ~CPEngOPresenceFetcher( );

        /**
        *  Method for registering the presence fetcher to the 
        *  Presence Engine.
        *  This method is asynchronous method and it will signal its 
        *  completion using the HandleFetcherRegisterL function.
        *  If the Presence Engine is not connected to the network
        *  then the HandleNotifierRegisterL will return KOPEngErrPENotLogged.
        *  Also in this case the fetcher will remain in unregistered state.
        *  There must be only one call the registering. Other calls will 
        *  fail with error code.
        *  After registering is succesfully done, client can issue other fetcher 
        *  function calls. 
        *
        *  @since Series 60 2.1
        *  @param aObserver observer object used for notifying the client 
        *                                    software.
        *  @return Status codes 
        *                     KErrNone if function call was succesfull.
        *                     This doesn't mean that the registering 
        *                     is complete.
        *                     KOPEngErrAllReadyRegistered is returned 
        *                     if we are allready registered.
        *                     KOPEngErrRegisteringInProgress if 
        *                     registering is ongoing.
        */
        virtual TInt RegisterL( 
                        MPEngOPresenceFetcherObserver& aObserver ) = 0;

        /**
        *  Method for unregistering the presence fetcher from the 
        *  Presence Engine.
        *  This method is synchronous method.
        *  If this is called during registering the registering will
        *  be canceled.
        *  When this is called all outstanding fetches are canceled.
        *  @since Series 60 2.1
        *  @return Status codes 
        *        KErrNone Unregistering succesfull.
        *        KOPEngErrNotRegistered if we were not registered   
        */
        virtual TInt UnRegisterL( ) = 0;

        /**
        *  This is a factory method for creating different kind of attributes.
        *  The ownership is transfered to the client. 
        *  It is clients responsiblity
        *  to delete this object after it is no longer needed. Client can 
        *  modify/access the object trough the M-interface.
        *  This function will leave with KErrNoMemory if allocation fails.
        *  @since Series 60 2.1
        *  @param aType   Type of the attribute to be created. Defined in
        *                               TAttributeType
        *  @return handle to MPresenceAttribute object.
        */
        virtual MPresenceAttribute* CreateAttributeLC( 
                                    TAttributeType aType ) = 0;

        /**
        * Method for fetching the Contacts Model ID's using some combination
        * of the presence attributes and their values.
        * Those contacts are returned which match the given attributes.
        * E.g. If the aAttributes contain one attributes e.g. UserAvailability
        * and the value of that attribute is ON_LINE then all ID's which have 
        * those values are returned from the Contacts Model.
        * This function is asynchronous and it will signal its
        * completion using the HandleGetByAttributeL function.
        * @since Series 60 2.1
        * @param aAttributes 1 or many attributes defining what kind of
        *                                  contact IDs are fetched.
        * @return Status codes KErrNone if no errors
        *                    KOPEngErrNotRegistered if we are not registered
        *                    KOPEngErrGetByAttributesAllReadyActive if there is 
        *                    allready a call to GetByAttributes 
        *                    which has not been handled.
        */
        virtual TInt GetByAttributesL( 
                        const RPointerArray<MPresenceAttribute>& aAttributes ) = 0;

        /**
        * Method for fetching the attribute value of Contacts Model ID's 
        * and/or Textual User ID's with given attribute(s).
        * This function is asynchronous and it will signal its
        * completion using the HandleGetAttributeL function.
        *
        * @since Series 60 2.1
        * @param aPresenceIDs Array of Contacts Model IDs.
        * @param aTUIDs            Array of Textual User IDs.
        * @param aAttributes       Array of attribute types.
        * @return Status codes
        *                    KErrNone if function call went ok.
        *                    KOPEngErrNotRegistered if we are not registered
        *                    KOPEngErrGetAttributesAllReadyActive if there is 
        *                    allready a call to GetAttributes which has not been 
        *                    handled.
        *                    KErrArgument if aAttributes length is 0 or both
        *                    aPresenceIDs and aTUIDs have zero length
        */
        virtual TInt GetAttributeL( 
                        const CContactIdArray& aPresenceIDs,
                        const MDesCArray& aTUIDs, 
                        const TArray<TAttributeType>& aAttributes ) = 0;

        /**
        * Method for getting the presence ID results
        * Ownership is transferred to caller.
        *
        * @since Series 60 2.1
        * @return MPresenceIDData
        */
        virtual MPresenceIDData* FetchedPresenceIDsLC( ) const = 0;

        /**
        * Method for getting the PresenceData results.
        * Ownership is transferred to caller.
        * @since Series 60 2.1
        * @return MPresenceData contains the results
        */
        virtual MPresenceData* FetchedPresenceDataLC( ) const = 0;

    protected:
        /**
        *   Default c'tor
        */
        inline CPEngOPresenceFetcher();

    private:
        /** A unique UID used in interface destruction 
        */
        TUid    iDtor_ID_Key;

    };

#include "CPEngOPresenceFetcher.inl"


#endif // _CPENGOPRESENCEFETCHER_H
            
// End of File
