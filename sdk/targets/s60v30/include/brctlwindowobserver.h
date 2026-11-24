/*
* ==============================================================================
*  Name        : BrCtlWindowObserver.h
*  Part of     : Browser Engine
*  Interface   : Browser Control API
*  Description : Handle multiple windows events such as open/close/etc
*  Version     : 3.0
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


#ifndef BRCTLWINDOWOBSERVER_H
#define BRCTLWINDOWOBSERVER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <BrCtlDefs.h>

// CONSTANTS

// MACROS

// DATA TYPES
enum TBrCtlWindowCommand
    {
    EFocusWindow,
    EUnfocusWindow,
    EShowWindow,
    ECloseWindow
    };

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CBrCtlInterface;

// CLASS DECLARATION

/**
*  This observer handles window events such open/close/etc
*
*  @lib BrowserEngine.lib
*  @since 3.0
*/
class MBrCtlWindowObserver
    {
    public: // New functions
        /**
        * Request the host applicaion to open the URL in a new window
        * @since 3.0
        * @param aUrl The Url of the request to be done in the new window
        * @param aTargetName The name of the new window
        * @param aUserInitiated ETrue if the new window is initiated by a user event (click)
        * @param aMethod The method to be used for fetching the supplied url
        * @param aContentType If the method is POST, this is the content type of the data to be posted 
        * @param aPostData If the method is POST, this is the data to be posted 
        * @param aBoundary The boundary used if the content is multipart/form-data
        * @param aReserved For future use
        * @return Return Value is the new browser control associated with the new window
        */
//        virtual CBrCtlInterface* OpenWindowL(TDesC& aUrl, TDesC* aTargetName, TBool aUserInitiated, 
//            TBrCtlDefs::TBrCtlMethod aMethod, const TDesC8* aContentType, 
//           const TDesC8* aPostData, const TDesC8* aBoundary, TAny* aReserved) = 0;

        virtual CBrCtlInterface* OpenWindowL(TDesC& aUrl, TDesC* aTargetName, TBool aUserInitiated,  
			TAny* aReserved) = 0;


        /**
        * Find a window by target name
        * @since 3.0
        * @param aTargetName name of the window to find
        * @return Return Value is the browser control associated with the window name
        */
        virtual CBrCtlInterface* FindWindowL( const TDesC& aTargetName ) const = 0;             

        /**
        * Handle window events such as close/focus etc
        * @since 3.0
        * @param aTargetName name of the window to send the event to
        * @param aCommand Command to pass to the window
        * @return void
        */
        virtual void HandleWindowCommandL( const TDesC& aTargetName, TBrCtlWindowCommand aCommand ) = 0;
    };

#endif      // BRCTLWINDOWOBSERVER_H
            
// End of File
