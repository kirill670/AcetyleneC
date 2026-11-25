// $Workfile: MmsRecipient.h $
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//
// $Author: Simonk $
// $Revision: 6 $
// $Date: 9/01/02 17:06 $
//

/** @file
 * This file contains the definition of the CMmsRecipient class.
 */


#ifndef __MMSRECIPIENT_H__
#define __MMSRECIPIENT_H__


#include <e32base.h>            // CBase
#include "MmsAddressParser.h"   // MmsAddressParser


// Forward declarations
class RWriteStream;
class RReadStream;


/**
 * A class to store information relating to a single MMS recipient.
 *
 * When a message is sent to multiple recipients, with delivery report requested,
 * a delivery report will be received from each recipient. This class provides a
 * Delivery Report Received flag per recipient to allow this information to be stored.
 */
class CMmsRecipient : public CBase
    {
    public:
        /**
         * 2-phase constructor.
         * Creates and returns a new recipient object.
         * @param aAddress The address of this recipient
         * @return A new CMmsRecipient object
         * @exception KErrXxx Standard EPOC error codes if allocation fails
         */
        IMPORT_C static CMmsRecipient* NewL(const TDesC& aAddress);

        /**
         * 2-phase constructor.
         * Creates a new recipient object from an open read stream and returns it.
         * @param aReadStream An open read stream
         * @return A new CMmsRecipient object
         * @exception KErrXxx Standard EPOC error codes if allocation fails, or standard EPOC stream error codes
         */
        IMPORT_C static CMmsRecipient* NewL(RReadStream& aReadStream);

        /**
         * C++ destructor.
         */
        IMPORT_C ~CMmsRecipient();

        /**
         * Set the Delivery Report Received flag for this recipient.
         */
        inline void SetDeliveryReportReceived();

        /**
         * Get the Delivery Report Received flag for this recipient.
         * @retval ETrue A delivery report has been received from this recipient.
         * @retval EFalse A delivery report has not been received from this recipient.
         */
        inline TBool DeliveryReportReceived() const;

        /**
         * Get the address of this recipient.
         * @return A descriptor identifying this recipient's address. Note: this will become invalid when this CMmsRecipient object is destroyed.
         */
        inline TPtrC Address() const;

        /**
         * Get the address type of this recipient.
         */
        inline MmsAddressParser::TMmsAddressType AddressType() const;

        /**
         * Internalizes the CMmsRecipient object from a stream.
         * @param aReadStream The stream to be read from
         * @exception KErrXXX Standard EPOC stream leave codes
         */
        IMPORT_C void InternalizeL(RReadStream& aReadStream);

        /**
         * Externalizes CMmsRecipient object to a stream.
         * @param aWriteStream The stream to be written to
         * @exception KErrXXX Standard EPOC stream leave codes
         */
        IMPORT_C void ExternalizeL(RWriteStream& aWriteStream) const;

    private:
        /**
         * C++ constructor.
         */
        CMmsRecipient();

        /**
         * 2nd-level constructor.
         * Constructs this recipient object.
         * @param aAddress The address of this recipient
         * @exception KErrXxx Standard EPOC error codes if allocation of member data fails
         */
        void ConstructL(const TDesC& aAddress);

    private:
        HBufC* iAddress;
        TBool iDeliveryReportReceived;
        MmsAddressParser::TMmsAddressType iAddressType;
    };


#include "MmsRecipient.inl"


#endif // __MMSRECIPIENT_H__