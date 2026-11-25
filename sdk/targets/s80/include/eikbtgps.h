/*
* ==============================================================================
*  Name        : eikbtgps.h
*  Part of     : CKON
*  Interface   : Button Group API
*  Description : Stack for button group containers.
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

#ifndef EIKBTGPS_H
#define EIKBTGPS_H

// INCLUDES
#include <coemain.h>
#include <eikbtgpc.h>

/**
 * The <code>CEikButtonGroupStack</code> class provides a list of all Button 
 * Groups currently available within a thread. Only Button Groups that are 
 * expected to be available to other controls will register here.
 *
 * @lib eikcoctl.lib
 * @since 1.2
 */
class CEikButtonGroupStack : public CCoeStatic
    {
    public:

       /**
        * Gets the minimum size required to display all the visible button
        * groups on the Button Group stack.
        *
        * @since     6.1
        * @return the minimum size required to display the biggest of the 
        *         visible Button Groups currently on the stack
        * @remarks
        * @see
        */
        IMPORT_C static TSize MinimumSize();
    public:
        /** @internal */
        static CEikButtonGroupContainer* Current();
        /** @internal */
        static void AddL(CEikButtonGroupContainer& aGroup);
        /** @internal */
        static void Remove(CEikButtonGroupContainer& aGroup);
        /** @internal */
        static TBool ButtonGroupInStack(const CEikButtonGroupContainer* aBgc);
    private:
        inline CEikButtonGroupStack();
        inline static CEikButtonGroupStack* Self();
    private:
        TDblQue<CEikButtonGroupContainer> iBtStack;
    };

#endif  // EIKBTGPS_H

// End of File
