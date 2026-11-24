/*
* ============================================================================
*  Name     : CalenInterimUtils.h
*  Part of  : Calendar / CalInterimUtils
*
*  Description:
*             This class contains utility methods related to usage of 
*             Calendar Interim API.
*       
*  Version:
*
*  Copyright (C) 2005 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing,  adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef __CALENINTERIMUTILS_H__
#define __CALENINTERIMUTILS_H__

//  INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS
class CCalEntry;
class CCalAttendee;
class CCalUser;

// CLASS DECLARATION

/**
* This class contains utility methods related to usage of
* Calendar Interim API
*/
class CalenInterimUtils
    {
    public: // New functions
        
        /**
        * Populates empty fields of a child entry with data from
        * the parent entry.
        * @param aChild child (modifying) entry to be populated
        * @param aParent parent (originating) entry
        */
        IMPORT_C static void PopulateChildFromParentL( CCalEntry& aChild,
                                                const CCalEntry& aParent );

        /**
        * Allocates and returns a new global UID.
        * @return UID, ownership is transferred to caller
        */
        IMPORT_C static HBufC8* GlobalUidL();
                                                
    private: // New functions
    
        /**
        * Helper method which populates child's attendee list if is empty.
        */
        static void PopulateAttendeeListL( CCalEntry& aChild,
                                           const CCalEntry& aParent );
        
        /*
        * Helper which creates a new copy of the given attendee. Item is
        * left in the cleanup stack.
        *
        * @param aSource attendee to copy
        * @return attendee, ownership is transferred to caller.
        */        
        static CCalAttendee* CopyAttendeeLC( const CCalAttendee& aSource );
        
        /*
        * Helper which creates a new copy of the given cal user. Item is
        * left in the cleanup stack.
        *
        * @param aSource user to copy
        * @return user, ownership is transferred to caller.
        */        
        static CCalUser* CopyUserLC( const CCalUser& aSource );
                                                        
        /**
        * Helper which reads handset's imei. Caller must pass long enough
        * descriptor (RMobilePhone::KPhoneSerialNumberSize).
        * @param aImei handset's imei
        */
        static void GetImeiL( TDes& aImei );
    
        /**
        * Helper which converts descriptor's content to 8 bit byte string.
        * @param aSource source content
        * @param aTarget modified byte string
        */
        static void ConvertToByteStringL( const TDesC& aSource,
                                   TDes8& aTarget );

        /**
        * Helper which converts each numerical character to a TInt8 and
        * writes them to the target byte string.
        * @param aSource descriptor containing numbers (e.g. "456")
        * @param aTarget modified byte string
        */        
        static void ConvertCharsToNumbersL( const TDesC& aSource,
                                     TDes8& aTarget );

    };

#endif // __CALENINTERIMUTILS_H__

// End of File
