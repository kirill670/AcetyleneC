/*
* ============================================================================
*  Name         : btnotif.h
*  Part of      : BTNotif
*  Description  : Declares Bluetooth notifiers API (partly).
*  Version      :
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/


#ifndef BTNOTIF_H
#define BTNOTIF_H

#include <eiknotapi.h>

// CONSTANTS
const TUid KPowerModeSettingNotifierUid = {0x100059E2}; // Notifier id for power mode setting
const TUid KSapModeNotifierUid          = {0x101F8736}; // Notifier id for sap mode

// FUNCTIONS
IMPORT_C CArrayPtr<MEikSrvNotifierBase2>* NotifierArray();   // Notifier array (entry point)

#endif // BTNOTIF_H

// End of File
