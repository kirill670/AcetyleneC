/*
* ==============================================================================
*  Name        : AknDef.h
*  Part of     : Avkon
*  Interface   : 
*  Description : 
*  Version     : 
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
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

#ifndef AKNDEF_H
#define AKNDEF_H

#include <akndef.hrh>
#include <e32std.h>

class TVwsViewId;

// Not sure this should be here...
const TInt KEikMessageWindowsFadeChange			=0x10006890;

// added by LMB [20/6/00] for CEikCaptionedControl 
const TInt KEikMessageCaptionedControlEditableStateChange			=0x10008E99;
const TInt KEikMessageCaptionedControlNotEditableStateChange		=0x10008E9A;
const TInt KEikMessageCaptionedControlEditableStateChangeWideWithGraphic			=0x101F5FBA;
const TInt KEikMessageCaptionedControlEditableStateChangeWideWithoutGraphic			=0x101F5FBB;
const TInt KEikMessageCaptionedControlNotEditableStateChangeWideWithGraphic			=0x101F5FBC;
const TInt KEikMessageCaptionedControlNotEditableStateChangeWideWithoutGraphic		=0x101F5FBD;

const TInt KEikClearPartialForegroundState		=0x101f54f4;
const TInt KEikPartialForeground				=0x101f6aab;

//UID Name: KUidDynamicLayoutVariantSwitch
//Number Allocation (Hexadecimal): 101F8121 To 101F8184 Inclusive.
const TInt KEikDynamicLayoutVariantSwitch	= 0x101F8121;

const TInt KEikDynamicLayoutVariantSwitch_APAC	= 0x101F8124;  // deprecated

const TInt KEikInputLanguageChange = 0x101F8519;

#define KAknApplicationShellViewId TVwsViewId(TUid::Uid(0x101F4CD2), TUid::Uid(0x00000001))

const TInt KAknHardwareLayoutSwitch = 0x10202672;
const TInt KAknDelayedLayoutSwitch = 0x102797FD;

namespace AknDef
    {
    /**
    * Returns the view uid of currently active idle state application. Alternatives 
    * include Phone application and Idle application.
    *
    * @since Series 60 2.8
    * @return The view uid of currently active idle state application.
    */
    IMPORT_C TInt GetPhoneIdleViewId(TVwsViewId& aViewId);
    }

#endif
