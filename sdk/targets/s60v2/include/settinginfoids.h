/*
* ==============================================================================
*  Name        : SettingInfoIDs.h
*  Part of     : PlatformEnv / SettingInfo
*  Interface   : SettingInfo API
*  Description : Setting IDs.
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


#ifndef SETTING_INFO_IDS_H
#define SETTING_INFO_IDS_H

// INCLUDES
#include <e32std.h>

// CONSTANTS

namespace SettingInfo
    {
    enum TSettingID
        {
        // Profile settings

        /**
        * @since 2.0
        *
        * Active profile index. Integer value.
        * Possible values in release 2.x:
        * 0 (general)
        * 1 (silent)
        * 2 (meeting)
        * 3 (outdoor)
        * 4 (pager)
        * 5 (offline)
        */
        EActiveProfile = 0,

        /**
        * @since 2.0
        *
        * Current ringing type. Integer value.
        * Possible values in release 2.x:
        * 0 (normal)
        * 1 (ascending)
        * 2 (ring once)
        * 3 (beep)
        * 4 (silent)
        */
        ERingingType = 1,

        /**
        * @since 2.0
        *
        * Current ringing volume. Integer value.
        * Possible values: 1-10.
        * Note! Audio components use scale 1-9, in which case both values
        * 1 and 2 in the scale 1-10 are usually mapped to value 1.
        */
        ERingingVolume = 2,

        /**
        * @since 2.0
        *
        * Current vibrating alert setting. Integer value.
        * Possible values in release 2.x:
        * 0 (off)
        * 1 (on)
        */        
        EVibratingAlert = 3,

        /**
        * @since 2.0
        *
        * Current keypad volume. Integer value.
        * Possible values in release 2.x:
        * 0 (off)
        * 1 (level 1)
        * 2 (level 2)
        * 3 (level 3)
        */        
        EKeypadVolume = 4,

        /**
        * @since 2.0
        *
        * Current warning tones setting. Integer value.
        * Possible values in release 2.x:
        * 0 (off)
        * 1 (on)
        */        
        EWarningTones = 5,

        /**
        * @since 2.0
        *
        * Current message alert setting. Integer value.
        * Possible values in release 2.x:
        * 0 (off)
        * 1 (on)
        */        
        EMessageAlert = 6,

        // Bluetooth settings

        /**
        * @since 2.0
        *
        * Current bluetooth power mode. Integer value.
        * Possible values in release 2.x:
        * 0 (unpowered/sleeping)
        * 1 (powered up and fully functional)
        */        
        EBluetoothPowerMode = 100,

        // Screen saver settings

        /**
        * @since 2.0
        *
        * Current screen saver plugin module name. String value.
        * If no plugin is in use, contains an emptry string.
        */        
        EScreenSaverPluginName = 200,

        // General settings

        /**
        * @since 2.6
        *
        * Indicates whether it is allowed to do network operations or not.
        * For example in offline/flight mode it is not allowed to do
        * network operations like sending MMS or starting IM sessions.
        * Possible values:
        * 0 (operations not allowed)
        * 1 (operations allowed)
        */        
        ENetworkConnectionAllowed = 300
        };
    }

#endif      // SETTING_INFO_IDS_H
            
// End of File
