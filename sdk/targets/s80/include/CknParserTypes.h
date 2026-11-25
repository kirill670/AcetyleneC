/*
* =============================================================================
*  Name        : cknparsertypes.h
*  Part of     : TEXTPARSERS
*  Interface   : Parser Banner API
*  Description : Different literals and an enum.
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
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


#ifndef CKNPARSERTYPES_H
#define CKNPARSERTYPES_H

// CONSTANTS
// MACROS
// DATA TYPES
// FUNCTION PROTOTYPES


_LIT(KCknParserBannerPhone,"PHONE"); 
_LIT(KCknParserBannerUrl,"URL"); 
_LIT(KCknParserBannerEmail,"EMAIL"); 

/** @internal */
enum TParserTypes
    {
    EParserPhone,
    EParserUrl,
    EParserEmail
    };


#endif  // CKNPARSERTYPES_H

// End of File
