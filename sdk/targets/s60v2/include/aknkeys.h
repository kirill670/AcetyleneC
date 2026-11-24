/*
* ============================================================================
*  Name     : AknKeys.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
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
// AKNKEYS.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNKEYS_H__)
#define __AKNKEYS_H__

#include <w32std.h>
#include <uikon.hrh>

/* Keyboard utilities
 */
class AknKeys 
    {
public:
    static TBool IsNumberKey(const TKeyEvent& aKeyEvent, TEventCode aType);
    };



#endif

