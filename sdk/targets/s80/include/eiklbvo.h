/*
* ==============================================================================
*  Name        : eiklbvo.h
*  Part of     : CKON
*  Interface   : Listbox API
*  Description : Listbox view observer.
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

#ifndef EIKLBVO_H
#define EIKLBVO_H

// FORWARD DECLARATIONS
class CListBoxView;

// CLASS DECLARATIONS

/**
 * The <code>MEikListBoxViewObserver</code> class provides an interface for 
 * objects wishing to observe a <code>CListBoxView</code>.
 *
 * @since 6.2
 * @internal
 */
class MEikListBoxViewObserver
    {
    public:  // Declarations
    enum TListBoxViewEvent
        {
        EEventSelectionChanged
        };

    public:
    // New methods
        
        /**
        * Function called when a view event occurs in the CListBoxView being observed. 
        * This function should be overridden in observer classes.
        * @param aListBoxView The CListBoxView that produced the view event. 
        * @param aEventType The type of view event.
        * <BR><B>Type of return value:</B> void
        */
        virtual void HandleListBoxViewEventL(CListBoxView* aListBoxView, TListBoxViewEvent aEventType)=0;

    };


#endif      // EIKLBVO_H   
            
// End of File
