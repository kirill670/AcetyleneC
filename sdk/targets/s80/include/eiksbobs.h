/*
* =============================================================================
*  Name        : eiksbobs.h
*  Part of     : CKON
*  Interface   : Scrollbar API
*  Description : Scrollbar observer mixin class
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
* =============================================================================
*/

#ifndef EIKSBOBS_H
#define EIKSBOBS_H

// DATA TYPES

/**
* The enumeration <code>TEikScrollEvent</code> communicates types of user 
* interaction with Scrollbars. To receive notification of Scrollbar events, 
* classes must implement the mixin <code>MEikScrollBarObserver</code>. Each 
* Scrollbar has a Scrollbar observer registered with it in its construction, 
* and will call the <code>HandleScrollEventL()</code> of its observer when the
* user moves the Scrollbar.
*/
enum TEikScrollEvent
    {
    /** the user scrolled leftwards */
    EEikScrollLeft=1,
    /** the user scrolled upwards */
    EEikScrollUp,
    /** the user scrolled rightwards */
    EEikScrollRight,
    /** the user scrolled downwards */
    EEikScrollDown, 
    /** the user scrolled leftwards by a page */
    EEikScrollPageLeft, 
    /** the user scrolled upwards by a page */
    EEikScrollPageUp, 
    /** the user scrolled rightwards by a page */
    EEikScrollPageRight,
    /** the user scrolled downwards by a page */
    EEikScrollPageDown,
    /** the user scrolled leftwards to the maximum extent */
    EEikScrollHome,
    /** the user scrolled upwards to the maximum extent */
    EEikScrollTop,
    /** the user scrolled rightwards to the maximum extent */
    EEikScrollEnd,
    /** the user scrolled downwards to the maximum extent */
    EEikScrollBottom,
    /** the user dragged the thumb horizontally */
    EEikScrollThumbDragHoriz,
    /** the user dragged the thumb vertically */
    EEikScrollThumbDragVert,
    /** the user released the thumb on a horizontal Scrollbar */
    EEikScrollThumbReleaseHoriz,
    /** the user released the thumb on a vertical Scrollbar */
    EEikScrollThumbReleaseVert 
    };


// FORWARD DECLARATIONS

class CEikScrollBar;

// CLASS DECLARATIONS

/**
* The <code>MEikScrollBarObserver</code> class provides an interface for 
* classes to receive notification of scroll events from a Scrollbar.
* Each Scrollbar has a Scrollbar observer registered with it in its
* construction, and calls the <code>HandleScrollEventL()</code> of
* its observer when the user moves the Scrollbar. Scrollbar observers
* are not owned by their Scrollbar and must be deleted explicitly. It
* is possible to register the same Scrollbar observer with many Scrollbars. 
* This class is intended for derivation by all classes interested
* in scroll events from <code>CEikScrollBar</code> objects.
*
* @lib eikcoctl.lib
* @since 6.0
*/
class MEikScrollBarObserver
    {
public:
        
    // New methods

    /**
    * Handles scroll events. This method is called by the 
    * <code>CEikScrollBar</code> object with which this Scrollbar observer 
    * object is registered. Implementations should handle scroll events 
    * appropriately.
    *
    * @param aScrollBar The Scrollbar object that has changed
    * @param aEventType The scroll event that occurred
    * @remarks
    * @see
    */
    virtual void HandleScrollEventL(CEikScrollBar* aScrollBar, 
                                    TEikScrollEvent aEventType)=0;

    };

#endif      // EIKSBOBS_H   

// End of File