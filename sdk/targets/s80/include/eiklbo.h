/*
* ==============================================================================
*  Name        : eiklbo.h
*  Part of     : CKON
*  Interface   : Listbox API
*  Description : Listbox observer mixin class.
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

#ifndef EIKLBO_H
#define EIKLBO_H


// FORWARD DECLARATIONS
class CEikListBox; 


// CLASS DECLARATIONS

/**
 * The <code>MEikListBoxObserver</code> class provides the Listbox observer 
 * interface. Each Listbox observer may be registered with a number of 
 * Listboxes. Each of these send events to the Listbox observer through its
 * <code>HandeListBoxEventL()</code> method. When writing derived classes, 
 * developers should implement a class that derives from this
 * interface to receive events from Listboxes.
 *
 * @lib eikcoctl.lib
 * @since 6.0
 */
class MEikListBoxObserver
    {
    public:  // Declarations
    /** 
     * The <code>TListBoxEvent</code> enumeration provides events that a 
     * Listbox can receive.
     */
    enum TListBoxEvent
        {
        /** key press event */
        EEventEnterKeyPressed,
        /** single tap event on an item */
        EEventItemClicked,
        /** two tap event on an item */
        EEventItemDoubleClicked,
        /** special event - reported by tree and contents Listboxes, for example, when expanding a directory tree */
        EEventItemActioned,
        /** editing started */
        EEventEditingStarted,       
        /** editing stopped */
        EEventEditingStopped,   
        /** selection changed */
        EEventSelectionChanged,     
        /** key press event */
        EEventDeleteKeyPressed, 
        /** key press event */
        EEventBackspaceKeyPressed,
        /** key press event */
        EEventEscapeKeyPressed      
        };

    public:

    // New methods
        
       /**
        * Handles Listbox events.
        * This pure virtual method is invoked by <code>CEikListBox</code> to
        * notify the observer of Listbox events.
        * 
        * @param aListBox The originating Listbox
        * @param aEventType A code for the event. Further information may be
        *                   obtained by accessing the Listbox itself
        * @remarks
        * @see
        */
        virtual void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType)=0;
        
    };


#endif      // EIKLBO_H   
            
// End of File
