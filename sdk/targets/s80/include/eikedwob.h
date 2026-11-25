/*
* ==============================================================================
*  Name        : eikedwob.h
*  Part of     : CKON
*  Interface   : Edwin API
*  Description : Text editor observer classes.
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

#ifndef EIKEDWOB_H
#define EIKEDWOB_H

// FORWARD DECLARATIONS
class CEikEdwin;


// CLASS DECLARATIONS

/**
* The <code>MEikEdwinObserver</code> class is a mixin interface class
* describing the functionality expected of an observer for
* <code>CEikEdwin</code>. Edwin observers are informed by an Edwin control
* when its content changes, or when the user changes the cursor position.
* All Edwin observers should derive from this class.
*
* @lib eikcoctl.lib 
* @since 6.0
*/
class MEikEdwinObserver
    {
    public:  // Declarations
    /**
    * The <code>TEdwinEvent</code> enumeration indicates the type of event 
    * that occurs in an Edwin.
    */
    enum TEdwinEvent
        {
        /** indicates that the formatting of the content of the Edwin has
        * changed */
        EEventFormatChanged,
        /** indicates that the cursor position in an Edwin has changed */
        EEventNavigation,   
        /** indicates that a non-scrolling search operation has changed
        * the current selection */
        EEventFindNewSelection          
        };

    public:     
    /**
     * This pure virtual method is invoked by <code>CEikEdwin</code> to report
     * an event to its observer so that the observer can respond appropriately.
     *
     * @param aEdwin The originating Edwin
     * @param aEventType The event being reported
     * @return
     * @remarks
     * @see
     */
        virtual void HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType)=0;
    };

/**
* The <code>MEikEdwinSizeObserver</code> class is a mixin interface class for 
* observing size changes of Edwin controls.
*
* @lib eikcoctl.lib 
* @since 6.0
*/
class MEikEdwinSizeObserver
    {
    public:  // Declarations
    /**
     * The <code>TEdwinSizeEvent</code> enumeration specifies the type of event 
     * reported to the Edwin observer.
     */
    enum TEdwinSizeEvent
        {
        /** specifies a change in Edwin size. When the Edwin observer receives
        * an event of this type, it handles it by making its view larger or
        * smaller according to the new Edwin size */
        EEventSizeChanging
        };
    public:
        /**
        * Handles a change in the size of an Edwin control. When implementing
        * this method, if the Edwin needs to be redrawn, ensure that it returns 
        * <code>ETrue</code>.
        *
        * @param aEdwin The Edwin for which the size event is being handled
        * @param aEventType The event type
        * @param aDesirableEdwinSize The desired size for the Edwin identified by 
        *                            <code>aEdwin</code>
        * @return depends on the implementation. Returns <code>ETrue</code> to 
        *         redraw the Edwin, or <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        virtual TBool HandleEdwinSizeEventL(CEikEdwin* aEdwin, TEdwinSizeEvent aEventType, TSize aDesirableEdwinSize)=0;
    };

/**
* The <code>MEikEdwinClipboardObserver</code> class defines an interface for 
* classes to implement clipboard feedback functions.
*
* @lib eikcoctl.lib
* @since Series90 1.0
*/
class MEikEdwinClipboardObserver
    {
    public:  // Declarations
    /** 
    * This set of values defines clipboard functionality. The values are passed
    * to the method <code>ClipboardL()</code>, which implements a switch that 
    * calls the appropriate method, depending on <code>aClipboardFunc</code>.
    */
    enum TClipboardFunc
        {
        /** do not perform any clipboard functionality */
        ENoClipboard,
        /** cut */
        ECut,
        /** copy */
        ECopy,
        /** paste */
        EPaste
        };

    public:
        /**
        * Releases the clipboard.
        *
        * @remarks The default implementation deletes itself
        * @see
        */
        virtual void Release() = 0;

        /**
        * Handles the operation when nothing is selected.
        *
        * @param aClipboardFunc The clipboard action  
        * @remarks The default implementation informs the user, via an
        *          infoprint, that nothing is selected
        * @see
        */
        virtual void HandleNothingSelected(TClipboardFunc aClipboardFunc)=0;

        /**
        *  Handles the copy operation.
        *
        * @remarks The default implementation informs the user, via an
        *          infoprint, that nothing is selected
        * @see
        */
        virtual void HandleCopiedToClipboard()=0;

    private: //Methods
        virtual void MEikEdwinClipboardObserver_Reserved_1() = 0;
    };


#endif      // EIKEDWOB_H   
            
// End of File