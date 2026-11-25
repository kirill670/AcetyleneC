/*
* ==============================================================================
*  Name        : eikcmobs.h
*  Part of     : UIKON
*  Interface   : Application API
*  Description : Command observer interface.
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


#ifndef EIKCMOBS_H
#define EIKCMOBS_H

// INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class CCoeControl;


/**
 * Command observers respond to user commands and have the secondary
 * function of creating custom controls on request for classes such as
 * <code>CEikToolbar</code> or developer-defined classes.
 * An implementation of the pure virtual method
 * <code>ProcessCommandL()</code> must be provided for each concrete
 * class derived from <code>MEikCommandObserver</code>.
 * <code>CreateCustomCommandControlL()</code> may also be overridden.
 *
 * @lib eikcore.lib
 * @since 6.0
 */
class MEikCommandObserver
    {
    public:
        /**
        * Processes user commands. Derived classes must provide an 
        * implementation of this method that responds to user commands 
        * appropriately based on a developer-defined ID for the command.
        *
        * @param  aCommandId The ID of the command to respond to
        * @remarks
        * @see
        */
        virtual void ProcessCommandL(TInt aCommandId)=0;

        /**
        * This method can be called to create custom controls on request from
        * their control ID. Custom controls are user-supplied control classes.

        * @param aControlType A custom control ID
        * @return a pointer to <code>CCoeControl</code>
        * @remarks
        * @see
        */
        IMPORT_C virtual 
            CCoeControl* CreateCustomCommandControlL(TInt aControlType);
    };


#endif  // EIKCMOBS_H

// End of File
