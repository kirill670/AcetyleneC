/*
* ==============================================================================
*  Name        : SettingInfo.h
*  Part of     : PlatformEnv / SettingInfo
*  Interface   : SettingInfo API
*  Description : Offers information of some Series 60 software settings.
*  Version     : 1
*
*  Copyright (c) 2002 Nokia Corporation.
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


#ifndef SETTING_INFO_H
#define SETTING_INFO_H

//  INCLUDES
#include <e32base.h>
#include <SettingInfoIDs.h>

// FORWARD DECLARATIONS
class CSettingInfoImpl;

// CLASS DECLARATIONS

/**
*  Interface for handling setting change notifications.
*
*  @lib N/A
*  @since 2.0
*/
class MSettingInfoObserver
    {
    public:

        /**
        * Handles notifications. Implemented by user.
        * @since 2.0
        * @param aID ID of changed setting
        * @param aNewValue new value of the changed setting. This is always as text,
        * convert to an integer with e.g. TLex if required.
        */
        virtual void HandleNotificationL( 
            SettingInfo::TSettingID aID, const TDesC& aNewValue ) = 0;
    };

/**
*  Offers information of some Series 60 software settings.
*  API supports fetching current setting states and getting
*  notifications when settings are changed.
*
*  @lib PlatformEnv.dll
*  @since 2.0
*
*  Code examples:
*
*  -----------------------------------------------------------------------------
*  #include <SettingInfo.h>
*
*  iSettingInfo = CSettingInfo::NewL()
*  // ...
*  // Get index of the currently active profile
*  TInt profileIndex = KDefaultValue; // <-- used if error code returned
*  TInt err = iSettingInfo.Get( EActiveProfile, profileIndex );
*  -----------------------------------------------------------------------------
*
*  -----------------------------------------------------------------------------
*  #include <SettingInfo.h>
*
*  // Give observer instance as a parameter if using notifications
*  iSettingInfo = CSettingInfo::NewL( this )
*  // ...
*  // Get current bluetooth power mode
*  TInt btMode = KDefaultValue; // <-- used if error code returned
*  TInt err = iSettingInfo.Get( EBluetoothPowerMode, btMode );
*  // ...
*  // Order notifications when bluetooth power mode is changed
*  err = iSettingInfo.NotifyChanges( EBluetoothPowerMode );
*  -----------------------------------------------------------------------------
*/
class CSettingInfo : public CBase
    {
    public: // Panic codes

        enum TSettingInfoClientPanic
            {
            EObserverMissing = 0
            };

    public: // Constructors and destructor

        /**
        * Constructor
        * @since 2.0
        * @param aObserver Setting change observer. May be NULL if notification
        * methods are not used.
        */
        IMPORT_C static CSettingInfo* NewL( MSettingInfoObserver* aObserver );

        /**
        * Destructor
        * @since 2.0
        */
        IMPORT_C ~CSettingInfo();

    public: // New functions

        /**
        * Get current value of a setting. If error code is returned, the
        * original value in given variable remains unmodified.
        * @since 2.0
        * @param aID Setting ID
        * @param aValue Value is returned here
        *
        * @ret KErrNone if successful.
        *      KErrNotFound if not found.
        *      KErrNotSupported if not supported.
        *      KErrTooBig if given descriptor is too small.
        */
        IMPORT_C TInt Get( SettingInfo::TSettingID aID, TDes& aValue ) const;

        /**
        * Get current value of a setting. If error code is returned, the
        * original value in given variable remains unmodified.
        * @since 2.0
        * @param aID Setting ID
        * @param aValue Value is returned here
        *
        * @ret KErrNone if successful.
        *      KErrNotFound if not found.
        *      KErrNotSupported if setting is not supported.
        *      KErrGeneral if not convertable to integer.
        */        
        IMPORT_C TInt Get( SettingInfo::TSettingID aID, TInt& aValue ) const;

        /**
        * Orders notifications whenever the value of a setting has been changed.
        * Effective until canceled or CSettingInfo instance destroyed.
        * @since 2.0
        * @param aID Setting ID
        *
        * @ret KErrNone if successful.
        *      KErrNoMemory if no memory.
        *      KErrNotSupported if setting is not supported.
        */        
        IMPORT_C TInt NotifyChanges( SettingInfo::TSettingID aID );

        /**
        * Orders notifications whenever the value of any of the given settings
        * has been changed.
        * Effective until canceled or CSettingInfo instance destroyed.
        * If error code is returned, some of the notification requests may still
        * be successfully established.
        * @since 2.0
        * @param aIDs Setting IDs
        *
        * @ret KErrNone if successful.
        *      KErrNoMemory if no memory.
        *      KErrNotSupported if setting is not supported.
        */        
        IMPORT_C TInt NotifyChanges( 
            const CArrayFix<SettingInfo::TSettingID>& aIDs );

        /**
        * Cancels a notification request with the given setting ID.
        * @since 2.0
        * @param aID Setting ID
        */
        IMPORT_C void CancelNotifications( SettingInfo::TSettingID aID );

        /**
        * Cancels notification requests with the given setting IDs.
        * @since 2.0
        * @param aIDs Setting IDs
        */
        IMPORT_C void CancelNotifications( 
            const CArrayFix<SettingInfo::TSettingID>& aIDs );

    private: // Private constructors

        /**
        * C++ default constructor.
        */
        CSettingInfo();

        /**
        * Symbian OS second phase constructor.
        */
        void ConstructL( MSettingInfoObserver* aObserver );

    private: // Data

        CSettingInfoImpl* iImpl;
    };

#endif      // SETTING_INFO_H   
            
// End of File
