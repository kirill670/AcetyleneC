/*
* =============================================================================
*  Name          : sipcrkeys.h
*  Part of       : SIP API
*  Description   :
*  Version       : SIP/4.0
*
*  Copyright (c) 2004 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* =============================================================================
*/
#ifndef SIPCRKEYS_H
#define SIPCRKEYS_H

// INCLUDES
#include <e32def.h>

const TUid KCRUidSIP = { 0x101FED88 };

// Transaction timer T1 defined in RFC 3261
const TUint32 KSIPTransactionTimerT1 = 0x01;

// Transaction timer T2 defined in RFC 3261
const TUint32 KSIPTransactionTimerT2 = 0x02;

// Transaction timer T4 defined in RFC 3261
const TUint32 KSIPTransactionTimerT4 = 0x03;	


#endif // SIPCRKEYS_H

// End of File
