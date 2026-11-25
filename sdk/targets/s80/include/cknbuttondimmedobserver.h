/*
* ==============================================================================
*  Name        : cknbuttondimmedobserver.h
*  Part of     : CKON / CKNCTL
*  Interface   : Button API
*  Description : The observer for dimmed buttons.
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


#ifndef CKNBUTTONDIMMEDOBSERVER_H
#define CKNBUTTONDIMMEDOBSERVER_H

// INCLUDES
#include <e32def.h>

/**
* The <code>MCknButtonDimmedObserver</code> class provides the observer for 
* dimmed Buttons.
*
* @lib cknctl.lib
* @since Series90 1.0
*/
class MCknButtonDimmedObserver
    {
    public:

        /**
        * This method is called when a dimmed Button is selected.
        * 
        * @param aCommandId The command called, for example <code>EEikCmdExit</code>
        * @remarks An object of this type, <code>MCknButtonDimmedObserver</code>,
		*          will have been defined previously as an observer of the 
        *          Button
        * @see
        */
        virtual void HandleDimmedButtonSelectedL(TInt aCommandId)=0;
    private:
        IMPORT_C virtual void MCknButtonDimmedObserver_Reserved_1();
        IMPORT_C virtual void MCknButtonDimmedObserver_Reserved_2();
    };


#endif  // CKNBUTTONDIMMEDOBSERVER_H

// End of File
