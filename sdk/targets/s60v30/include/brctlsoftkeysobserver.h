/*
* ==============================================================================
*  Name        : BrCtlSoftkeysObserver.h
*  Part of     : Browser Engine
*  Interface   : Browser Control API
*  Description : Handle softkeys updates
*  Version     : %Version%
*
*  Copyright (c) 2004 Nokia Corporation.
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


#ifndef BRCTLSOFTKEYSOBSERVER_H
#define BRCTLSOFTKEYSOBSERVER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>

// DATA TYPES
enum TBrCtlKeySoftkey
    {
    EKeyRight,
    EKeyLeft
    };

enum TBrCtlSoftkeyChangeReason
    {
    EChangeReasonElementType,
    EChangeReasonLoad,
    EChangeReasonIdle
    };

/**
*  This observer is notified when the browser requests softkeys changes
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class MBrCtlSoftkeysObserver
    {
    public: // New functions
        
        /**
        * Browser Control requests to update a softkey
        * @since 2.8
        * @param aKeySoftkey Update the left softkey or the right softkey
        * @param aLabel The label associated with the softkey update
        * @param aCommandId The command to use if the softkey is selected by the user
        * @param aBrCtlSoftkeyChangeReason The reason for the softkey change
        * @return void
        */
        virtual void UpdateSoftkeyL(TBrCtlKeySoftkey aKeySoftkey,
                                    const TDesC& aLabel,
                                    TUint32 aCommandId,
                                    TBrCtlSoftkeyChangeReason aBrCtlSoftkeyChangeReason) = 0;
    };

#endif      // BRCTLSOFTKEYSOBSERVER_H   
            
// End of File
