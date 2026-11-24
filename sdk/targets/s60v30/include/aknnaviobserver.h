/*
* ============================================================================
*  Name     : AknNaviObserver.h
*  Part of  : Avkon
*
*  Description:
* 
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
// AKNNAVIOBSERVER.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNNAVIOBSERVER_H__)
#define __AKNNAVIOBSERVER_H__

class MAknNavigationObserver
    {
public:
    enum TAknNavigationEvent
        {
        ENaviEventHandleNavigation = 0x0010,
        ENaviEventLeftMostItemReached,
        ENaviEventRightMostItemReached,
        ENaviEventOneItemExists,
        ENaviEventRedrawNeeded
        };
    };

#endif // __AKNNAVIOBSERVER_H__
