// $Workfile: MmsSettings.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Markw $
// $Revision: 12 $
// $Date: 13/12/01 12:16 $
//


/** @file
 * This file contains the interface for the CMmsSettings class.
 */


#ifndef __MMSSETTINGS_H__
#define __MMSSETTINGS_H__


// System includes
#include <e32base.h>
#include <badesca.h>    // CDesCArraySeg (can't forward declare as it's a typedef)
#include <msvstd.h>     // TMsvPriority
// User includes
#include "MmsUtils.h"   // TMmsPriority etc.


// Forward declarations
class CMsvStore;
class RReadStream;
class RWriteStream;


/**
 * The MMS settings class.
 * This class contains two types of information: basic service-wide settings (such as
 * server address and the user's From address), and filter values to support filtering
 * of incoming messages.
 * 
 * Note that filtering is not supported in the current release. The APIs are provided
 * for future compatibility only.
 */
class CMmsSettings : public CBase
    {
    public:
        /**
         * 2 Phase constructor
         *
         * This function creates a CMmsSettings object.
         *
         * @exception KErrXxx Leaves if no memory is available
         * @return A newly created CMmsSettings object
         */
        IMPORT_C static CMmsSettings* NewL();
        /**
         * 2 Phase constructor
         *
         * This function creates a CMmsSettings object and leaves it on the cleanup stack.
         *
         * @exception KErrXxx Leaves if no memory is available
         * @return A newly created CMmsSettings object
         */
        IMPORT_C static CMmsSettings* NewLC();
        /**
         * C++ destructor.
         */
        IMPORT_C ~CMmsSettings();

        /**
         * Store this object to a message entry store. The object creates its own stream with a known UID and externalizes its data to it.
         *
         * @param aStore The message entry store
         * @exception KErrXxx Standard store leave codes
         */
        IMPORT_C void StoreL(CMsvStore& aStore) const;
        /**
         * Restore this object from a message entry store. The object opens a stream with a known UID and internalizes its data from it.
         *
         * @param aStore The message entry store
         * @exception KErrXxx Standard store leave codes
         */
        IMPORT_C void RestoreL(const CMsvStore& aStore);

        /**
         * Get the MMS server address for this service.
         *
         * @return A descriptor referring to MMS server address. Note this may be empty if none has been set.
         */
        IMPORT_C TPtrC ServerAddress() const;
        /**
         * Set the MMS server address for this service.
         *
         * @param aAddress The MMS server address
         * @exception Leaves if a heap buffer cannot be allocated to store aAddress
         */
        IMPORT_C void SetServerAddressL(const TDesC& aAddress);

        /**
         * Get the user's MMS address, to appear in the From field of outgoing messages.
         *
         * @return A descriptor referring to the user's From address. Note this may be empty if none has been set.
         */
        IMPORT_C TPtrC FromAddress() const;
        /**
         * Set the user's MMS address, to appear in the From field of outgoing messages.
         *
         * @param aAddress User's MMS address
         * @exception KErrXxx Standard EPOC leave codes if a heap buffer cannot be allocated to store aAddress
         */
        IMPORT_C void SetFromAddressL(const TDesC& aAddress);

        /**
         * Get the array of allowed senders of incoming MMS messages.
         * Note that sender filtering is not implemented in this version, although the API is provided for future source compatibility.
         *
         * @return A modifiable reference to an array of allowed incoming senders. If this is empty, all senders will be accepted.
         */
        IMPORT_C CDesCArray& AllowedIncomingSenders();
        /**
         * Get the array of allowed senders of incoming MMS messages.
         * Note that sender filtering is not implemented in this version, although the API is provided for future source compatibility.
         *
         * @return A const reference to an array of allowed incoming senders. If this is empty, all senders will be accepted.
         */
        IMPORT_C const CDesCArray& AllowedIncomingSenders() const;

        /**
         * Get the maximum allowed size of an incoming MMS message.
         * Note that maximum size filtering is not implemented in this version, although the API is provided for future source compatibility.
         * @return The maximum allowed size in bytes of an incoming MMS message. If this is 0, no size limit will be imposed.
         */
        inline TInt MaxIncomingMessageSize() const;
        /**
         * Set the maximum allowed size of an incoming MMS message.
         * Note that maximum size filtering is not implemented in this version, although the API is provided for future source compatibility.
         * @param aMaxSizeBytes The maximum allowed size in bytes of an incoming MMS message. Set to 0 to allow all incoming messages.
         */
        inline void SetMaxIncomingMessageSize(TInt aMaxSizeBytes);

        /**
         * Get the current status of automatic fetch.
         * @retval ETrue Automatic Fetch is enabled
         * @retval EFalse Automatic Fetch is disabled
         */
        inline TBool AutomaticFetch() const;
        /**
         * Set the current status of automatic fetch.
         *
         * @param aEnable ETrue to enable Automatic Fetch, EFalse to disable it
         */
        inline void SetAutomaticFetch(TBool aEnable);

        //
        // Default header value APIs for outgoing messages
        //

        /**
         * Get the default priority for outgoing MMS messages.
         * @return The default priority, or <code>EMmsPriorityUnset</code> if unset
         */
        inline TMmsPriority DefaultPriority();
        /**
         * Set the default priority for outgoing MMS messages.
         * @param aPriority The default priority. Use <code>EMmsPriorityUnset</code> to clear any previously set value and leave the default unset.
         */
        inline void SetDefaultPriority(TMmsPriority aPriority);

        /**
         * Get the default expiry interval for outgoing MMS messages, in seconds.
         * Note that the default expiry time cannot be expressed as an absolute time value.
         * @return The default expiry interval, or 0 if unset
         */
        inline TInt DefaultExpiryInterval();
        /**
         * Set the default expiry interval for outgoing MMS messages, in seconds.
         * Note that the default expiry time cannot be set as an absolute time value.
         * @param aSeconds The default expiry interval in seconds. Use 0 to clear any previously set value and leave the default unset.
         */
        inline void SetDefaultExpiryInterval(TInt aSeconds);

        /**
         * Get the default delivery time interval for outgoing MMS messages, in seconds.
         * Note that the default delivery time cannot be expressed as an absolute time value.
         * @return The default expiry interval, or 0 if unset
         */
        inline TInt DefaultDeliveryTimeInterval();
        /**
         * Set the default delivery time interval for outgoing MMS messages, in seconds.
         * Note that the default delivery time cannot be set as an absolute time value.
         * @param aSeconds The default delivery time interval in seconds. Use 0 to clear any previously set value and leave the default unset.
         */
        inline void SetDefaultDeliveryTimeInterval(TInt aSeconds);

        /**
         * Get the default sender visibility for outgoing MMS messages
         * @return The default sender visibility, or <code>EMmsSenderVisibilityUnset</code> if unset
         */
        inline TMmsSenderVisibility DefaultSenderVisibility();
        /**
         * Set the default sender visibility for outgoing MMS messages.
         * @param aVisibility The default sender visibility. Use <code>EMmsSenderVisibilityUnset</code> to clear any previously set value and leave the default unset.
         */
        inline void SetDefaultSenderVisibility(TMmsSenderVisibility aVisibility);

        /**
         * Get the default read reply flag for outgoing MMS messages
         * @return The default read reply flag, or <code>EMmsYesNoUnset</code> if unset
         */
        inline TMmsYesNo DefaultReadReply();
        /**
         * Set the default read reply flag for outgoing MMS messages.
         * @param aReadReply The default read reply flag. Use <code>EMmsYesNoUnset</code> to clear any previously set value and leave the default unset.
         */
        inline void SetDefaultReadReply(TMmsYesNo aReadReply);

        /**
         * Get the default delivery report flag for outgoing MMS messages
         * @return The default delivery report flag, or <code>EMmsYesNoUnset</code> if unset
         */
        inline TMmsYesNo DefaultDeliveryReport();
        /**
         * Set the default delivery report flag for outgoing MMS messages.
         * @param aDeliveryReport The default delivery report flag. Use <code>EMmsYesNoUnset</code> to clear any previously set value and leave the default unset.
         */
        inline void SetDefaultDeliveryReport(TMmsYesNo aDeliveryReport);

    private:
        /**
         * C++ constructor.
         */
        CMmsSettings();
        /**
         * Called from NewL to perform construction of a new CMmsSettings object.
         *
         * @exception KErrXxx Leaves there is not enough memory to allocate member data.
         */
        void ConstructL();

        /**
         * Externalize this object to a stream in a message entry store.
         *
         * @param aWriteStream The message entry store stream
         * @exception KErrXxx Standard stream leave codes
         */
        void ExternalizeL(RWriteStream& aWriteStream) const;
        /**
         * Internalize this object from a stream in a message entry store.
         *
         * @param aReadStream The message entry store stream
         * @exception KErrNotSupported The stream was written by a previous version and its format is no longer supported
         * @exception KErrXxx Standard stream leave codes
         */
        void InternalizeL(RReadStream& aReadStream);

    private:
        HBufC* iServerAddress;                  ///< The MMS server address for this service
        HBufC* iFromAddress;                    ///< The user's default From address for this service
        TInt iMaxIncomingMessageSize;           ///< Maximum allowed incoming message size, in bytes.
        CDesCArraySeg* iAllowedIncomingSenders; ///< Array of allowed incoming sender addresses
        TBool iAutomaticFetch;                  ///< Flag stating whether automatic fetch is enabled

        TMmsPriority iDefaultPriority;          ///< Default priority for outgoing MMS messages
        TInt iDefaultExpiryInterval;            ///< Default relative expiry time for outgoing MMS messages, expressed an an interval in seconds
        TInt iDefaultDeliveryTimeInterval;      ///< Default relative delivery time for outgoing MMS messages, expressed an an interval in seconds
        TMmsSenderVisibility iDefaultSenderVisibility; ///< Default sender visibility for outgoing MMS messages
        TMmsYesNo iDefaultReadReply;            ///< Default Read Reply flag for outgoing MMS messages
        TMmsYesNo iDefaultDeliveryReport;       ///< Default Delivery Report flag for outgoing MMS messages
    };


#include "MmsSettings.inl"


#endif // __MMSSETTINGS_H__