/*
 * =========================================================================
 *  Name     : SenMessagesConstants.h
 *  Part of  : SenUtils
 *  Created  : 2004/06/14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Utils/inc/SenMessagesConstants.h,v $
 *   $Date: 2004/10/26 07:41:24 $
 *   $Revision: 1.3 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */


#ifndef SEN_MESSAGES_CONSTANTS_H
#define SEN_MESSAGES_CONSTANTS_H

#include <e32base.h>

// Panics

_LIT(KPanic, "SenUtils");

enum TPanic
    {
    EInternalVariableNotInitialized = 1,
    EArgumentNull, // deprecated, not in use anymore(!)
    ETlsCouldNotBeInitialized,
    EResourceOfferingNull,
    EResourceOfferingNotNull,
    ELastResourceOfferingNull, // deprecated, not in use anymore(!)
    ELastResourceOfferingNotNull,  // deprecated, not in use anymore(!)
    ECredentialNull,
    };
#endif // SEN_MESSAGES_CONSTANTS_H
