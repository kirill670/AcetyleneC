/*
* ==============================================================================
*  Name        : cknmarginsobserver.h
*  Part of     : CKON
*  Interface   : Margins API
*  Description : Margin observer mixin class.
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
* ==============================================================================
*/

#ifndef CKNMARGINSOBSERVER_H
#define CKNMARGINSOBSERVER_H


/**
 * The <code>MCknMarginsObserver</code> class is a mixin observer class for 
 * watching margins.
 * The <code>CEikListBox</code> class uses this class, so if a Listbox has its 
 * margin observer set, the <code>MarginsChanged</code> callback method will be 
 * called whenever the Listbox's margins are modified.
 *
 * @lib eikcoctl.lib
 * @since Series90 1.0
 */
class MCknMarginsObserver
    {
    public:
        /**
        * When a margin is modified, this callback method is called.
        *
        * @remarks
        * @see
        */
        virtual void MarginsChanged() = 0;
    };
    

#endif  // CKNMARGINSOBSERVER_H

// End of File
