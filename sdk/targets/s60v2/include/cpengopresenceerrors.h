/*
* ==============================================================================
*  Name        : CPEngOPresenceErrors.h
*  Part of     : Presence API
*  Interface   : 
*  Description : Header file for errors
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
#ifndef _OPENGERRORS_H
#define _OPENGERRORS_H

const TInt KOPEngErrorBase = -20000;
const TInt KOPEngStatusBase = -30000;

// These enum values define different error statuses 
enum TOPEngErrors   // Open API errors
    {
    // General error
    KOPEngGeneralError = KOPEngErrorBase,
    // Returned if the RegisterL call has not been called succesfully.
    KOPEngErrNotRegistered = KOPEngErrorBase - 1,
    // We are allready registered, no need to register second time
    KOPEngErrAllReadyRegistered = KOPEngErrorBase - 2,
    // We are not logged to the any service provider
    KOPEngErrPENotLogged = KOPEngErrorBase - 3,
    // Registering is currently ongoing
    KOPEngErrRegisteringInProgress = KOPEngErrorBase - 4,
    // Active object is active
    KOPEngErrGetByAttributesAllReadyActive = KOPEngErrorBase - 5,
    // Active object is active
    KOPEngErrGetAttributesAllReadyActive = KOPEngErrorBase - 6,
    // Incorrect attribute
    KOPEngErrUnSupportedAttribute = KOPEngErrorBase - 7,
    // Contact id was not subscribed
    KOPEngErrNotSubscribed = KOPEngErrorBase - 8,
    // No subscriptions were made. 
    KOPEngErrNothingWasSubscribed = KOPEngErrorBase - 9,
    // Only some of the requested subscriptions were done
    KOPEngErrPartialSubscription = KOPEngErrorBase - 10,
    // Active object is active
    KOPEngErrSubscribeAllReadyActive = KOPEngErrorBase - 11,
    // Active object is active
    KOPEngErrRemoveSubscriberAllReadyActive = KOPEngErrorBase - 12,
    };

// These enum values define different status codes releated to the connection
// to the outside world.
enum TOPEngStatus   // Open API errors
    {
    // General status code
    KOPEngGeneralStatus = KOPEngStatusBase,
    // The service is now offline. e.g GPRS suspend
    KOPEngServiceOffLine = KOPEngStatusBase - 1,
    // The service is now online
    KOPEngServiceOnLine = KOPEngStatusBase - 2,
    // The network is down. No connection
    KOPEngServiceNetworkDown = KOPEngStatusBase - 3,
    // The Service provider has been changed
    KOPEngServiceSAPChanged = KOPEngStatusBase - 4,
    };


#endif // _OPENGERRORS_H

//  End of File
