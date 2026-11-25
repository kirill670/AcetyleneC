/*
* ==============================================================================
*  Name        : ckntimelabel.h
*  Part of     : CKON
*  Interface   : Seek Bar API
*  Description : Time label widget class
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

#ifndef CKNTIMELABEL_H
#define CKNTIMELABEL_H


// INCLUDES
#include <coecntrl.h>
#include <cknbctrl.h>
#include "CknSeekBar.h"

// CLASS DECLARATIONS

/**
* The <code>CCknTimeLabel</code> class specifies a control for displaying 
* time for use with a Seek Bar. The time label can be used, for example, in a 
* multimedia file to show the current time in the file that is being played.
*
* @lib cknctl.lib
* @since Series90 1.0
*/
class CCknTimeLabel : public CCknBorderedControl
    {

    public:  // Declarations

    // Constructors and destructor

        /**
        * Starts the two-phase object construction. Allocates and constructs a 
        * time label control. After construction, the application should 
        * usually perform the following operations before the time label is 
        * ready to use:
        *   Set a container window by calling 
        *       <code>SetContainerWindowL(CCoeControl*)</code>
        *   Set the size and position of the time label
        *   Call <code>ActivateL()</code> to make the time label ready to use
        *
        * @param aSeekStart The lower limit for the seek time
        * @param aSeekEnd The upper limit for the seek time. Must be greater 
        *                 than the start time. If the start time exceeds the 
        *                 upper limit, the control panics with 
        *                 <code>ECknPanicSeekBarInvalidRange</code>
        * @param aGranularityInSeconds The size of the smallest time change. 
        *                              Must not be zero and must be less than 
        *                              the range, in seconds
        * @param aMode The mode that the time label is displayed in; either 
        *              <code>ENormal</code> or <code>EToolbar</code>. 
        *              <code>EToolbar</code> produces a smaller time label
        *              that is compatible with the <code>EToolbar</code> Seek 
        *              Bar 
        * @return a pointer to the newly constructed object
        * @remarks
        * @see
        */
        IMPORT_C static CCknTimeLabel* NewL(TTime aSeekStart,
                                            TTime aSeekEnd,
                                            TInt aGranularityInSeconds, 
                    CCknSeekBar::TCknSeekBarMode aMode = CCknSeekBar::ENormal);

        /**
        * The default <code>NewL()</code> method used to construct a time label.
        *
        * @return a pointer to the newly constructed object
        * @remarks
        * @see
        */
        IMPORT_C static CCknTimeLabel* NewL();

        /**
        * The object destructor.
        */
        IMPORT_C ~CCknTimeLabel();

        /**
        * Sets the current time to an absolute value and redraws.
        *
        * @param aTime The time to set. The time is rounded to the nearest
        *                  granular value. If outside the time range, the seek 
        *                  time is set to the nearest limit
        * @remarks
        * @see
        */
        IMPORT_C void SetTime(TTime aTime);

        /**
        * Adjusts the current seek time relative to the current value and 
        * redraws.
        *
        * @param aSeconds The amount to adjust the current seek time by. 
        *                 Negative values decrease the seek time. The time is 
        *                 rounded to the nearest granular value. If the new
        *                 time is outside the time range, it is set to the 
        *                 nearest limit
        * @remarks
        * @see
        */
        IMPORT_C void IncreaseSeekTime(TInt aSeconds);

        /**
        * Gets the current seek time.
        *
        * @return the current seek time
        * @remarks
        * @see
        */
        IMPORT_C TTime SeekTime();

        /**
        * Sets the start time.
        *
        * @param aStartTime The new start time. If the current seek time is 
        *                   before the new start time, it is set to the new 
        *                   start time
        * @remarks
        * @see
        */
        IMPORT_C void SetStartTime(TTime aStartTime);

        /**
        * Gets the start time.
        *
        * @return the start time
        * @remarks
        * @see
        */
        IMPORT_C TTime StartTime();

        /**
        * Sets the end time.
        *
        * @param aEndTime The new end time. If the current seek time is after 
        *                 the new end time, it is set to the new end time
        * @remarks
        * @see
        */
        IMPORT_C void SetEndTime(TTime aEndTime);

        /**
        * Gets the end time.
        *
        * @return the end time
        * @remarks
        * @see
        */
        IMPORT_C TTime EndTime();

    // Methods from base classes

        /**
        * Sets whether or not the control is dimmed.
        *
        * @param aDimmed <code>ETrue</code> to set the control as dimmed; 
        *                <code>EFalse</code> to set it as not dimmed
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SetDimmed(TBool aDimmed);

        /**
        * Gets the control's minimum required size.
        *
        * @return the minimum size of the control
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize();

    protected:  // Methods

    // Methods from base classes

        /**
        * From CCoeControl
        * @internal
        */
        IMPORT_C void Draw(const TRect& aRect) const;

        /**
        * From CCoeControl
        * @internal
        */
        IMPORT_C void HandleResourceChange(TInt aType);

    // New Methods

        /**
        * C++ default constructor
        */
        IMPORT_C CCknTimeLabel();

        /**
        * C++ constructor
        */
        IMPORT_C CCknTimeLabel(TTime aSeekStart,TTime aSeekEnd,
            TInt aGranularity,TInt aLengthInPixels);

        /**
        * @internal
        */
        void ConstructL();

    private: //Methods

    // Methods from base classes

        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt aIndex) const;

    private:     // Data

        /** the parent of this control, used to draw the background when the container is not a MCknSliderCustomDrawBase */
        const CCoeControl* iParent;
        TTime iStartTime;
        TTime iEndTime;
        TTime iCurrentTime;
        TInt iGranularity; //in seconds
        TInt iLength;
        TSize iSize;

        //dimensions
        TInt iTimeBoxBorderWidth;
        TInt iTimeBoxBorderHeight;
        TBool iSmallBar;
        TUid iMbmUid;
        TBool iMbmDuplicated;
        void *iReserved;
    };

#endif      // CKNTIMELABEL_H

// End of File
