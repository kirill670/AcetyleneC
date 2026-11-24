/*
* ==============================================================================
*  Name        : HWRMVibraSDKCRKeys.h
*  Part of     : HW Resources and Enhancements / HWResourceManager
*  Interface   : SDK
*  Description : This file contains SDK central repository key definitions
*                for the vibra
*  Version     : 1
*
*  Copyright © 2002-2005 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/

#ifndef HWRMVIBRASDKCRKEYS_H
#define HWRMVIBRASDKCRKEYS_H

#include <e32std.h>

// CONSTANTS
const TUid KCRUidVibraCtrl = {0x10200C8B};

// Vibra Settings API

/**
* Vibra setting in active profile. 
* 
* Possible integer values:
*
* 0 Vibra is off in active profile (default value)
* 1 Vibra is on in active profile
*/
const TUint32 KVibraCtrlProfileVibraEnabled     = 0x00000001;

/**
* Maximum vibrating time supported by device. 
* 
* Value is milliseconds as an integer. 
* If value is zero, no maximum time is supported.
* Maximum supported time is TMaxTInt microseconds in milliseconds.
*
* Value is read-only.
*
* Default value: 10000.
*/
const TUint32 KVibraCtrlMaxTime                 = 0x00000002;

/**
* Minimum time vibra cannot be started after it was
* forcibly turned off when maximum time was reached.
* This can be used to enforce vibra cooling after long 
* use periods.
*
* Value is milliseconds as an integer.
*
* Value is read-only.
*
* Default value: 0
*/
const TUint32 KVibraMinOffTime                  = 0x00000003;

#endif  // HWRMVIBRASDKCRKEYS_H
            
// End of File
