/*
* ==============================================================================
*  Name        : BrCtlDownloadObserver.h
*  Part of     : Browser Engine
*  Interface   : Browser Control API
*  Description : Handle download events
*  Version     : 3.0
*
*  Copyright (c) 2005 Nokia Corporation.
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


#ifndef BRCTLDOWNLOADOBSERVER_H
#define BRCTLDOWNLOADOBSERVER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <BrCtlDefs.h>

// CONSTANTS

// MACROS

// DATA TYPES
enum TBrCtlDownloadEvent
    {
    EDownloadEventStarted,      // aValue is the total size
    EDownloadEventCompleted,    // aValue is the total size
    EDownloadEventProgress,     // aValue is the size that was downloaded
    EDownloadEventCanceled,     // N/A
    EDownloadEventError,		// N/A
	EDownloadEventPaused,		// aValue is the size downloaded so far
	EDownloadEventResumed,		// aValue is the size downloaded
	EDownloadEventPausable		// aValue = true when it is pausable
    };

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CBrCtlInterface;

// CLASS DECLARATION

/**
*  This observer handles download events
*
*  @lib BrowserEngine.lib
*  @since 3.0
*/
class MBrCtlDownloadObserver
    {
    public: // New functions
        /**
        * Inform the host application that a new download has started using the Download Manager
        * @since 3.0
        * @param aTransactionID The ID of the transaction, it is unique as long as the transaction is on-going
        * @param aFileName The name of file in which the content is stored/
        * @param aContentType The content type of the downloaded content
        * @param aUrl The Url of the request to be done in the new window
        * @return Return ETrue if the file is handled progressively, EFalse otherwise
        */
        virtual TBool NewDownloadL(TUint aTransactionID,
                                   const TDesC& aFileName,
                                   const TDesC& aContentType,
                                   const TDesC& aUrl) = 0;


        /**
        * Inform the host application that a new download has started using the Download Manager
        * @since 3.0
        * @param aTransactionID The ID of the transaction, it is unique as long as the transaction is on-going
        * @param aFileName The name of file in which the content is stored/
        * @param aContentType The content type of the downloaded content
        * @param aUrl The Url of the request to be done in the new window
        * @return Return ETrue if the file is handled progressively, EFalse otherwise
        */
        virtual void ResumeDownloadL(TUint aTransactionID,
                                   TUint aLength,
                                   const TDesC& aFileName,
                                   const TDesC& aContentType,
                                   const TDesC& aUrl) = 0;

        /**
        * Inform the host application of a progress event related to a download
        * @since 3.0
        * @param aTransactionID The ID of the transaction, it is unique as long as the transaction is on-going
        * @param aDownloadEvent The event to be reported
        * @param aValue The value depends on the event
        * @return void
        */
        virtual void HandleDownloadEventL(TUint aTransactionID, 
                                          TBrCtlDownloadEvent aDownloadEvent,
                                          TUint aValue) = 0;             

    };

#endif      // BRCTLDOWNLOADOBSERVER_H
            
// End of File
