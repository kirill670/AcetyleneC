/*
* ==============================================================================
*  Name        : cknseekbar.h
*  Part of     : CKON
*  Interface   : Seek Bar API
*  Description : Seek bar widget class
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

#ifndef CKNSEEKBAR_H
#define CKNSEEKBAR_H


// INCLUDES
#include <coecntrl.h>
#include <cknbctrl.h>


// DATA TYPES

/** the default length of the Seek Bar */
#define KCknSeekBarDefaultLength 150

// FORWARD DECLARATIONS

class MCknSliderCustomDrawBase;
class CCknSliderThumb;
class CCknTimeLabel;
class CFocusChangeCbaUpdater;

// CLASS DECLARATIONS

/**
* The <code>CCknSeekBar</code> class provides the Seek Bar control for 
* displaying and adjusting time using a slider bar. This control can be used, 
* for example, to show the current position in a multimedia file that is 
* being played and to allow the user to drag to a specific position in the
* file.
*
* @lib cknctl.lib
* @since Series90 1.0
*/
class CCknSeekBar : public CCknBorderedControl
    {

    public:  // Declarations


        /**
        * The enumeration <code>TCknSeekBarMode</code> is used to specify the 
        * mode that the Seek Bar is displayed in. In <code>EToolbar</code> 
        * mode, the toolbar displayed is slimmer and has no border.
        */
        enum TCknSeekBarMode
            {
            /** normal mode */
            ENormal,
            /** toolbar mode */
            EToolbar
            };

    private:  // Declarations
        /**
        * The enumeration <code>TButtonStatus</code> is used to [what]. 
        */
        enum TButtonStatus
            {
            EUnpressed,
            EPressed,
            EDisabled
            };

        /**
        * The enumeration <code>TSeekTimeIndicatorPosition</code> is used to 
        * specify the position of the time indicator box relative to the seek bar.
        */
        enum TSeekTimeIndicatorPosition
            {
            EAbove,
            EBelow,
            ELeft,
            ENotShown
            };

    public:

    // Constructors and destructor

        /**
        * Starts the two-phase object construction. Allocates and constructs a 
        * Seek Bar control. After construction, the application should usually 
        * perform the following operations before the Seek Bar is ready to use:
        *   Set a container window by calling 
        *       <code>SetContainerWindowL(CCoeControl*)</code>
        *   Set the size and position of the Seek Bar
        *   Set an observer to the Seek Bar control, if required, by calling 
        *       <code>SetObserver(MCoeObserver* )</code>
        *   Call <code>ActivateL()</code> to make the Seek Bar ready to use
        * 
        * @param aContainer The container that is used for custom draw. Must 
        *                   not be null
        * @param aSeekStart The lower limit for the seek time
        * @param aSeekEnd The upper limit for the seek time. Must be greater 
        *                 than the start time. If the start time exceeds the 
        *                 upper limit, the control panics with 
        *                 <code>ECknPanicSeekBarInvalidRange</code>
        * @param aLengthInPixels The length of the control in pixels. If it is 
        *                        too small, the length will be set to a 
        *                        minimum value
        * @param aGranularityInSeconds The size of the smallest time change. 
        *                              Must not be zero and must be less than 
        *                              the range, in seconds
        * @param aMode The mode that the Seek Bar is displayed in
        * @return a pointer to the newly constructed object.
        * @remarks
        * @see
        */
        IMPORT_C static CCknSeekBar* NewL(MCknSliderCustomDrawBase* aContainer,
                                          TTime aSeekStart,
                                          TTime aSeekEnd,
                                          TInt aGranularityInSeconds,
                                          TInt aLengthInPixels,
                                          TCknSeekBarMode aMode = ENormal);

        /**
        * Starts the two-phase object construction. Allocates and constructs a 
        * Seek Bar control using a default length set by the skin. After 
        * construction, the application should usually perform the following 
        * operations before the Seek Bar is ready to use:
        *   Set a container window by calling 
        *       <code>SetContainerWindowL(CCoeControl*)</code>
        *   Set the size and position of the Seek Bar
        *   Set an observer to the Seek Bar control, if required, by calling 
        *       <code>SetObserver(MCoeObserver* )</code>
        *   Call <code>ActivateL()</code> to make the Seek Bar ready to use
        *
        * @param aContainer The container that is used for custom draw. Must 
        *                   not be null
        * @param aSeekStart The lower limit for the seek time
        * @param aSeekEnd The upper limit for the seek time. Must be greater 
        *                 than the start time. If the start time exceeds the 
        *                 upper limit, the control panics with 
        *                 <code>ECknPanicSeekBarInvalidRange</code>
        * @param aGranularityInSeconds The size of the smallest time change. 
        *                              Must not be zero and must be less than 
        *                              the range, in seconds
        * @param aMode The mode that the Seek Bar is displayed in
        * @return a pointer to the newly constructed object
        * @remarks
        * @see
        */
        IMPORT_C static CCknSeekBar* NewL(MCknSliderCustomDrawBase* aContainer,
                                          TTime aSeekStart,
                                          TTime aSeekEnd,
                                          TInt aGranularityInSeconds,
                                          TCknSeekBarMode aMode = ENormal);
        /**
        * The default <code>NewL()</code> method used to construct a Seek Bar. 
        * Starts the two-phase object construction. 
        *
        * @return a pointer to the newly constructed object
        * @remarks
        * @see
        */
        IMPORT_C static CCknSeekBar* NewL();

        /**
        * The object destructor.
        */
        IMPORT_C ~CCknSeekBar();

        /**
        * Registers a <code>CCknTimeLabel</code> with this Seek 
        * Bar to show the time. This method has two effects. First, it makes
        * the time label and Seek Bar controls synchronized. Second, the 
        * <code>CCknSeekBar</code> object takes responsibility for deleting the 
        * <code>CCknTimeLabel</code> object. The containing control must not 
        * delete the time label control itself once this method has been 
        * called. If this method is called more than once, the pointer to the 
        * first time label is overwritten with the address of the second one. 
        * Therefore, the caller should ensure that the first time label can be 
        * deleted.
        *
        * @param aTimeLabel The time label to use
        * @remarks
        * @see
        */
        IMPORT_C void SetTimeLabel(CCknTimeLabel* aTimeLabel);

        /**
        * Sets the current seek time to an absolute value and redraws.
        *
        * @param aSeekTime The time to set. The time is rounded to the 
        *                  nearest value at the specified granularity. If 
        *                  the value is outside the time range, the seek time 
        *                  is set to the nearest limit
        * @remarks
        * @see
        */
        IMPORT_C void SetSeekTime(TTime aSeekTime);

        /**
        * Adjusts the current seek time relative to the current value and 
        * redraws.
        *
        * @param aSeconds The amount to adjust the current seek time by. 
        *                 Negative values decrease the seek time. The time is 
        *                 rounded to the nearest value. If the new time is 
        *                 outside the time range, it is set to the nearest 
        *                 limit
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
        * Set the control's container window. <code>CCknSeekBar</code> is not 
        * a window-owning control. Therefore, this method must be 
        * called by the containing application.
        *
        * @param aContainer The container
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);

        /**
        * Constructs a Seek Bar control from a resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource structure type is <code>SEEKBAR</code>
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

        /**
        * Activates this control. This method calculates the dimension of the 
        * components that make up the Seek Bar based on the parameters 
        * already provided. It sets the control as ready to be drawn.
        * 
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ActivateL();

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

    // New methods

        /**
        * Sets whether or not the Seek Bar is dimmed.
        *
        * @param aDimmed <code>ETrue</code> to set the Seek Bar as dimmed; 
        *                <code>EFalse</code> to set it as not dimmed
        * @remarks
        * @see
        */
        IMPORT_C void SetSeekBarDimmed(TBool aDimmed);

        /**
        * Sets whether or not the time label control is dimmed.
        * 
        * @param aDimmed <code>ETrue</code> to set the time label as dimmed;
        *                <code>EFalse</code> to set it as not dimmed
        * @remarks
        * @see
        */
        IMPORT_C void SetTimeLabelDimmed(TBool aDimmed);

        /**
        * Returns the rectangle for the time label control. If it does not
        * exist, returns an empty <code>TRect</code>.
        * 
        * @return [what]
        * @remarks
        * @see
        */
        IMPORT_C TRect TimeLabelRect(void);

    protected:  // Methods
        /**
        * From CCoeControl. How to react when focus is gained or lost
        */
        void FocusChanged(TDrawNow aDrawNow);

    // Methods from base classes

        /**
        * From CCoeControl Handles pointer events
        * @param aPointerEvent Pointer event to handle
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * From CCoeControl
        * @internal
        */
        IMPORT_C void Draw(const TRect& aRect) const;

        /**
        * From CCoeControl
        * @internal
        */
        IMPORT_C void SizeChanged();

        /**
        * From CCoeControl
        * @internal
        */
        IMPORT_C void PositionChanged();

        /**
        * From CCoeControl
        * @internal
        */
        IMPORT_C void HandleResourceChange(TInt aType);

        /**
         * From CCoeControl
         * Handles key events, allowed events: EKeyUpArrow, EKeyDownArrow if the volume bar is
         * displayed vertically; EKeyLeftArrow, EKeyRigthArrow if the volume bar is displayed
         * horizontally.
         *
         * @param aKeyEvent the occurred event
         * @param aType unused
         * @return A response
         **/
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

      // New Methods

        /**
        * C++ default constructor
        */
        IMPORT_C CCknSeekBar();

        /**
        * C++ constructor
        */
        IMPORT_C CCknSeekBar(MCknSliderCustomDrawBase* aContainer,TTime aSeekStart,TTime aSeekEnd,
                        TInt aGranularity,TInt aLengthInPixels);

public:
        /**
        * Sets the step time, that is, the speed at which to move through the 
        * file.
        *
        * @remarks Used to maintain BC
        * @param aGranularity The step size in seconds
        * @see
        */
        IMPORT_C void SetGranularity(TInt aGranularity);

protected:
        /**
        * @internal
        */
        void ConstructL();

        /**
        * @internal
        */
        void CalculateSize();

        /**
        * @internal
        */
        void CalculatePositions();

        /**
        * @internal
        */
        void SetCurrentTimeFromThumb();

        /**
        * @internal
        */
        void CalculateDimensions();

        /**
        * @internal
        */
        void DrawBackground(const TRect& aRect) const;

        /**
        * @internal
        */
        void DrawSliderFill(const TRect& aRect) const;

        /**
        * @internal
        */
        void DrawArrow(const TRect& aArrowRect) const;

        /**
        * @internal
        */
        void DrawArrowNow(const TRect& aArrowRect) const;

        /**
        * @internal
        */
        void DrawThumbAndBackgroundNow();

    private: //Methods

    // Methods from base classes

        TInt CountComponentControls() const;
        CCoeControl* ComponentControl(TInt aIndex) const;

    // New Methods

        void SetCurrentPositionFromThumb();

        /**
        * STATIC FUNCTION - send a command to a specified object
        *
        * @param aObject The object that will actually process the command
        * @param aCommandId the command Id
        */
        static void ProcessCommandL(TAny* aObject, TInt aCommandId);

        /**
        * Process a command.
        *
        * @param aCommandId the command Id.
        */
        void DoProcessCommandL(TInt aCommandId);

    private:     // Data

        TRect iLeftArrowRect;
        TRect iRightArrowRect;
        TRect iTimeIndicatorRect;
        TPoint iSeekBarOrigin; //top left of Seek Bar
        TButtonStatus iLeftArrowStatus;
        TButtonStatus iRightArrowStatus;
        enum
            {
            ENone,
            ELeftArrow,
            ERightArrow,
            EThumb
            } iPointerDownOn;
        TPoint iPenDownPos;
        MCknSliderCustomDrawBase* iContainer;
        TTime iStartTime;
        TTime iEndTime;
        TTime iCurrentTime;
        TInt iGranularity; //in seconds
        TInt iLength;
        TSeekTimeIndicatorPosition iTimeIndicatorPosition;
        CCknSliderThumb* iThumb;

        //dimensions
        TInt iThumbHeight;
        TInt iThumbThickness;
        TInt iBackgroundHeight;
        TInt iArrowWidth;
        TInt iArrowHeight;
        TInt iTimeBoxWidth;
        TInt iTimeBoxHeight;
        TInt iSpaceLeftBorder;
        TInt iSpaceRightBorder;
        TInt iTimeBoxDistanceFromSlider;
        TInt iTimeBoxBorderWidth;
        TInt iTimeBoxBorderHeight;
        TInt iSliderLimitFromLeft;
        TInt iSliderLimitFromRight;
        TBool iSmallBar;
        TUid iMbmUid;
        TBool iMbmDuplicated;
        CCknTimeLabel* iTimeLabel;
        void *iReserved;

        CFocusChangeCbaUpdater* iFocusChangeHandler;
    };

#endif      // CKNSEEKBAR_H

// End of File
