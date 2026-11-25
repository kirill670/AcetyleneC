/*
* ==============================================================================
*  Name        : ckntimepicker.h
*  Part of     : CKON
*  Interface   : Time API
*  Description : Time picker widget.
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
//
// Header file for the CCknTimePicker class.

#ifndef CKNTIMEPICKER_H
#define CKNTIMEPICKER_H


// INCLUDES
#include <cknbctrl.h>
#include <COECCNTX.H>
#include <eikbtgpc.h>
#include <eikcmobs.h>


// DATA TYPES


// FORWARD DECLARATIONS
class CCknDigitFlipper;
class CCknAmPmSelector;
class CCknDialogButton;
class CCknSkinBase;
class CEikTimeEditor;

// CLASS DECLARATIONS

/**
*  The <code>MCknTimePickerObserver</code> class is the interface for the Time 
*  Picker observer.
*
*  @lib cknctl.lib
*  @since Series 90 1.0
*/
class MCknTimePickerObserver
    {
    public:

    // New methods
        
       /**
        * Gets the minimum and maximum time for the Time Picker.
        *
        * @param aMinimumTime The minimum time
        * @param aMaximumTime The maximum time
        * @param aInitialTime The initial time
        * @remarks
        * @see
        */
        virtual void GetMinimumAndMaximumAndInitialTimeForTimePickerL(TTime& aMinimumTime, TTime& aMaximumTime, TTime& aInitialTime) const=0;

       /**
        * Sets the time using the Time Picker.
        *
        * @param aTime Returns the time from the Time Picker
        * @remarks This method is called by the Time Picker control after the 
        *          Close button is tapped
        * @see
        */
        virtual void SetTimeFromTimePickerAndDrawNow(const TTime& aTime)=0;
    };


/**
*  The <code>CCknTimePicker</code> class provides the Time Picker control. It 
*  provides controls to modify hour, minute, and am/pm settings (when in 
*  12-hour mode). This control is implemented like a dialog.
*
*  @lib cknctl.lib
*  @since Series 90 1.0
*/

class CCknTimePicker : public CCknBorderedControl, public MCoeControlObserver, public MCoeControlContext
    {
public: 
    // Constructors and destructor

       /**
        * Allocates and constructs a <code>CCknTimePicker</code> object, 
        * cleaning the cleanup stack.
        *
        * @param aTimeFormat An enumeration whose enumerators represent the 
        *                    12/24 hour time format
        * @param aDuration Not used
        * @param aMinTime The minimum time allowed for this control
        * @param aMaxTime The maximum time allowed for this control
        * @param aTheTime The time stored by this control
        * @param aIncrement The absolute amount to increment or decrement by 
		*                   when the arrowheads are tapped. Defaults to 1 if 
		*                   not defined
        * @return a pointer to the built <code>CCknTimePicker</code>
        * @remarks
        * @see
        */
        IMPORT_C static CCknTimePicker* NewL(TTimeFormat aTimeFormat, TBool aDuration, TTime aMinTime, TTime aMaxTime, TTime aTheTime, TInt aIncrement=1);
        
       /**
        * Allocates and constructs a <code>CCknTimePicker</code> object, 
        * leaving the pointer to it on the cleanup stack.
        *
        * @param aTimeFormat An enumeration whose enumerators represent the 
        *                    12/24 hour time format
        * @param aDuration Not used
        * @param aMinTime The minimum time allowed for this control
        * @param aMaxTime The maximum time allowed for this control
        * @param aTheTime The time stored by this control
        * @param aIncrement The absolute amount to increment or decrement by 
		*                   when the arrowheads are tapped. Defaults to 1 if 
		*                   not defined
        * @return a pointer to the built <code>CCknTimePicker</code>
        * @remarks
        * @see
        */
        IMPORT_C static CCknTimePicker* NewLC(TTimeFormat aTimeFormat, TBool aDuration, TTime aMinTime, TTime aMaxTime, TTime aTheTime, TInt aIncrement=1);

       /**
        * The object destructor.
        */
        ~CCknTimePicker();

    // New methods
        
       /**
        * Returns the time value stored in the control.
        *
        * @return the time
        * @remarks
        * @see
        */
        IMPORT_C TTime Time() const;

       /**
        * Sets the Time Picker observer.
        *
        * @param aObserver The observer
        * @remarks
        * @see
        */
        IMPORT_C void SetTimePickerObserver(MCknTimePickerObserver* aObserver);

       /**
        * Displays the Time Picker control.
        *
        * @remarks This is implemented like a dialog
        * @see
        */
        IMPORT_C void ExecuteLD();
    
    // Methods from base classes
        
       /**
        * Handles key events offered to the control by the control environment. 
        * 
        * @param aKeyEvent The key event offered
        * @param aType  The type of key event, either <code>EEventKey</code>, 
        *               <code>EEventKeyUp</code> or <code>EEventKeyDown</code> 
        * @return indicates whether or not the key event was used by this 
        *         control. <code>EKeyWasConsumed</code> if the control takes 
        *         action on the key event; <code>EKeyWasNotConsumed</code> 
        *         otherwise
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

       /**
        * Handles pointer events.
        *
        * @param aPointerEvent The pointer event
        * @remarks
        * @see <code>CCoeControl</code>
        */
        void HandlePointerEventL(const TPointerEvent& aPointerEvent);

       /**
        * Gets the minimum size for the Time Picker. Calculates all contained 
        * controls' sizes.
        * 
        * @return a <code>Tsize</code> object that is the object's minimum size
        * @remarks
        * @see <code>CCoeControl</code>
        */  
        TSize MinimumSize();

       /**
        * Draws the object.
        *
        * @param aRect The drawing area
        * @remarks
        * @see <code>CCoeControl</code>
        */
        void Draw(const TRect& aRect) const;

       /**
        * Called when the Time Picker size changes. 
        *
        * @remarks
        * @see <code>CCoeControl</code>
        */
        void SizeChanged();

        // from MCoeControlObserver
        /**
        * Handles an <code>EEventStateChanged</code> event from an observed 
        * control.
        *
        * @param aControl The control that sent the event
        * @param aEventType The event type
        * @remarks
        * @see <code>MCoeControlObserver</code>
        */
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

        
    protected:  // Methods

    // Methods from base classes
        /**
        * From CCoeControl Gets the number of controls contained in a compound control
        * @return Returns 4 if there is an am/pm selector, otherwise 3
        * <BR><B>Name of return value:</B> (Write name here)
        * <BR><B>Type of return value:</B> void
        * <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
        * <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl Get the specified component of a control.
        * @param aIndex The index of the control to be returned
        * @return @param A pointer to one of the control's sub-controls
        * <BR><B>Name of return value:</B> (Write name here)
        * <BR><B>Type of return value:</B> void
        * <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
        * <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
        */
        CCoeControl* ComponentControl(TInt aIndex) const;

    // New Methods
        
        CCknTimePicker(TTimeFormat aTimeFormat, TBool aDuration, TTime aMinTime, TTime aMaxTime, TTime aTheTime, TInt aIncrement);
        /**
        * Second phase constuctor
        */
        void ConstructL();

        /**
        * constructs the components inside CCknTimePicker. 
        */
        void ConstructComponentsL();

        /**
        * creates the layout of the components
        */
        void LayoutComponents();

        /**
        * Determines the index of the control from the co-ordinates provided
        * @param aPoint The position of the control
        * @return the index of the control at aPoint, if no control occupies that area then the return is ETimePickerNoControl
        */
        TInt ControlIndexFromPosition(const TPoint aPoint);

        /**
        * Determines the index of the control that is currently focused.
        * @return he index of the control with focus, if not control has focus then the return is ETimePickerNoControl
        */
        TInt IndexOfFocusedControl();



    private: //Methods

    //from MCoeControlContext
        void PrepareContext(CWindowGc& aGc) const;

       void SetTime(TTime aTime);
        void BaseConstructL();
        void MoveFocusBy(TInt aDelta);

    protected:     // Data
        TTimeFormat iTimeFormat;
        TTime iMinTime;
        TTime iMaxTime;
        TTime iTime;
        MCknTimePickerObserver* iTimePickerObserver;
        TBool iTimePickerWaiting;
        TUint iInternalFlags;

        /** The hour field */
        CCknDigitFlipper* iHourField;
        /** The minute field */
        CCknDigitFlipper* iMinuteField;
        /** The am or pm field */
        CCknAmPmSelector* iAmPmField;
        /** The increment or decrement value */
        TInt iIncrement;
        /** The close button. */
        CCknDialogButton* iButton;
    };

class CCknTimePickerS80 : public CCknTimePicker, public MEikCommandObserver
    {
public:
    static CCknTimePickerS80* NewL(TTimeFormat aTimeFormat, TBool aDuration,
        TTime aMinTime, TTime aMaxTime, TTime aTheTime, TInt aIncrement);
    static CCknTimePickerS80* NewLC(TTimeFormat aTimeFormat, TBool aDuration,
        TTime aMinTime, TTime aMaxTime, TTime aTheTime, TInt aIncrement);
    ~CCknTimePickerS80();

private:
    CCknTimePickerS80(TTimeFormat aTimeFormat, TBool aDuration,
        TTime aMinTime, TTime aMaxTime, TTime aTheTime, TInt aIncrement);
    void ConstructL();
    void ConstructComponentsL();
    void LayoutComponents();
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
    TSize MinimumSize();
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
    void Draw(const TRect& aRect) const;
    void CreateButtonGroupContainerL(TInt aResourceId);

private: // from MEikCommandObserver
    virtual void ProcessCommandL(TInt aCommandId);
    
private:
    CEikTimeEditor* iTimeEditor;
    CEikButtonGroupContainer* iButtonGroupContainer;
    };

#endif      // CKNTIMEPICKER_H   
            
// End of File
