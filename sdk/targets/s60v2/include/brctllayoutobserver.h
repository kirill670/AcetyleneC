/*
* ==============================================================================
*  Name        : BrCtlLayoutObserver.h
*  Part of     : Browser Engine
*  Interface   : Browser Control API
*  Description : Handle scrollbar and tab events
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


#ifndef BRCTLLAYOUTOBSERVER_H
#define BRCTLLAYOUTOBSERVER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>


// DATA TYPES
enum TBrCtlLayout
	{
	EOriginTopLeft,
	EOriginTopRight
	};

enum TBrCtlTabDirection
    {
    ETabLeft,
    ETabRight,
    ETabUp,
    ETabDown
    };

/**
*  This observer is notified of scrolling and tabbing events
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class MBrCtlLayoutObserver
    {
    public: // New functions
        
        /**
        * Update the position of vertical scrollbar.
        * @since 2.8
        * @param aDocumentHeight The total height of the markup page
        * @param aDisplayHeight The height of the display
        * @param aDisplayPosY The current Y position
        * @return void
        */
        virtual void UpdateBrowserVScrollBarL(TInt aDocumentHeight, 
                                              TInt aDisplayHeight,
                                              TInt aDisplayPosY ) = 0;

        /**
        * Update the position of horizontal scrollbar.
        * @since 2.8
        * @param aDocumentWidth The total width of the markup page
        * @param aDisplayWidth The width of the display
        * @param aDisplayPosX The current X position
        * @return void
        */
        virtual void UpdateBrowserHScrollBarL(TInt aDocumentWidth, 
                                              TInt aDisplayWidth,
                                              TInt aDisplayPosX ) = 0;

        /**
        * Inform the layout of the page: right to left or left to right. Useful when the application draws the scrollbar itself.
        * @since 2.8
        * @param aNewLayout RTL or LTR
        * @return void
        */
        virtual void NotifyLayoutChange( TBrCtlLayout aNewLayout ) = 0;
    };

#endif      // BRCTLLAYOUTOBSERVER_H
            
// End of File
