/*
* ==============================================================================
*  Name        : eikbutb.h
*  Part of     : CKON
*  Interface   : Button API
*  Description : CEikButtonBase is the base class from which concrete Button 
*                controls are derived. TEikButtonCoordinator is a Button 
*                coordinator class.
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


#ifndef EIKBUTB_H
#define EIKBUTB_H

// INCLUDES
#include <eikbctrl.h>
#include <uikon.hrh>
#include <lafpublc.h>

// FORWARD DECLARATIONS
class TEikButtonCoordinator;

/**
* The enumeration <code>TButtonBehavior</code> specifies Button behavior. These
* values may be bitwise ORed.
*/
enum TButtonBehavior
    {
    /** the Button is always clear */
    EEikButtonStaysClear=EEikButStaysClear,                     
    /** the Button is always set */
    EEikButtonStaysSet=EEikButStaysSet,
    /** the Button latches down */
    EEikButtonLatches=EEikButLatches,
    /** the Button reports a control event to its observer when a pen-down
	event occurs rather than when a pen-down-and-up event occurs */
    EEikButtonReportsOnPointerDown=EEikButReportOnPointerDown
    };

/**
*
* The <code>CEikButtonBase</code> class is the base class from which concrete 
* Button controls are derived. The concrete Button controls are command Buttons, 
* option Buttons, and checkboxes. The base class implements knowledge of the 
* Button's logical state, and can respond to user events. However, it cannot 
* draw itself. Derived classes should provide an appropriate implementation of
* <code>CCoeControl::Draw()</code>. It is usual to make the onscreen appearance 
* of the Button dependent on its current state. Derived classes may also 
* implement <code>StateChanged()</code> to respond appropriately to changes in 
* the draw state.
*
* @lib eikcoctl.lib
* @since 6.0
*/
class CEikButtonBase : public CEikBorderedControl
    {
    public:

        /**
        * The default object constructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C CEikButtonBase();

        /**
        * The object destructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C ~CEikButtonBase();
    public:
    /**
     * The enumeration <code>TState</code> provides the possible logical states 
     * for a Button. <code>TState</code> values represent the logical state of a
     * Button. Derived Button classes may draw themselves differently to 
     * indicate different states. See also the methods <code>State()</code> and
     * <code>SetState()</code>.
     */
    enum TState
        {
        /** the clear state; often drawn as button-up */
        EClear          =0, 
        /** the set state; often drawn as button-down */
        ESet            =1,     
        /** an indeterminate state. Often used for an animation stage between the two other Buttons. It may be used for derived tri-state Buttons */
        EIndeterminate  =2
        };
    public: // new functions

        /**
        * Gets the logical state of the Button.
        * 
        * @return the Button's logical state
        * @remarks A Button can have three logical states: 
        *          <code>EClear</code> - the Button is drawn as up 
        *          <code>ESet</code> - the Button is drawn as down 
        *          <code>EIndereminate</code> - the Button animates between up 
        *          and down states 
        * @see
        */
        IMPORT_C TState State() const;

        /**
        * Sets the state of the Button.
        * 
        * @param aState The logical state to which the Button is set
        * @remarks
        * @see
        */
        IMPORT_C void SetState(TState aState);

        /**
        * Animates a Button, showing the control as tapped momentarily.
        *
        * @remarks The method allows the drawing of the Button in up and down
        *          states. The method can be called when the logical
        *          state of the Button changes. The method is also called by
        *          method <code>OfferKeyEventL()</code>
        * @see State()
        */
        IMPORT_C virtual void Animate();

        /**
        * Sets the coordinator for the Button.
        * 
        * @param aButCoord The Button coordinator
        * @remarks A coordinator is used to coordinate groups of Buttons 
        *          on the screen
        * @see 
        */
        IMPORT_C void SetCoordinator(TEikButtonCoordinator* aButCoord);

        /**
        * Sets the behavior of the Button.
        * 
        * @param aBehavior Specifies the Button behavior
        * @remarks The Button can be set either up or down and no event is 
		* generated. The Button can be set to respond to pen-down events.
		* Typically, events are only sent by the button in response to an 
        * incoming pen-down event followed by a pen-up event
        * @see
        */
        IMPORT_C void SetBehavior(TButtonBehavior aBehavior);

        /**
        * Sets the Button flag so that the next pen-up event is ignored.
        * 
        * @remarks The Button's behavior determines whether it stays down 
        *          after it has been tapped. However, the behavior does not 
        *          affect the request to ignore the next 
        * @see
        */
        IMPORT_C void SetIgnoreNextPointerUp();

        /**
        * Sets the text to appear in a bubble help message for the Button.
        * 
        * @param aText The bubble help text
        * @remarks This method is not supported in Series 90
        * @see
        */
        IMPORT_C void SetBubbleHelpTextL(const TDesC& aText);
    protected:
    /**
     *
     * Possible states for the draw stateThe <code>TDrawState</code> values
     * affecting a Button are stored in <code>iButFlags</code>.
     *
     * All draw state flag bits must be maskable by <code>0x001f</code>; the
     * ones which describe a pressed Button must be maskable by
     * <code>0x0010</code>.
     */
    enum TDrawState
        {
        EDrawClear                  =SLafButtonBase::EDrawClear,                /** Button is clear. */
        EDrawSet                    =SLafButtonBase::EDrawSet,                  /** Button is set. */
        EDrawIndeterminate          =SLafButtonBase::EDrawIndeterminate,        /** Button is between set and clear. */
        EDrawClearPressed           =SLafButtonBase::EDrawClearPressed,         /** Button is clear, and the user is pressing it. */
        EDrawSetPressed             =SLafButtonBase::EDrawSetPressed,           /** Button is set, and the user is pressing it. */
        EDrawIndeterminatePressed   =SLafButtonBase::EDrawIndeterminatePressed  /** Button is between set and clear, and the user is pressing it. */
        };
    protected: // new functions

        /**
        * Sets event reporting on pointer down events.
        */
        IMPORT_C void SetReportOnPointerDown();

        /**
        * Gets the current draw state.
        * @return The current draw state.
        */
        IMPORT_C TDrawState DrawState() const;

        /**
        * Tests whether the Button is currently being pressed by the user.
        * @return <code>ETrue</code> if the Button is currently being pressed by the user.
        */
        IMPORT_C TBool IsPressed() const;

        /**
        * Specifies the Button can have an indeterminate state that is neither on, nor off.
        */
        IMPORT_C void SetAllowTristate();

        /**
        * Copies the current draw state to the specified Button.
        * @param aTargetButton The Button to which the draw state is copied.
        */
        IMPORT_C void CopyDrawStateTo(CEikButtonBase* aTargetButton) const;
    protected: // new functions
        TBool IsPointerEventDraggedOff();
    public: // from CCoeControl

        // not available before Release 005u
        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        * 
        * @param aType The <code>TInt</code> message UID value for the type of 
        *              resource that has changed
        * @remarks 
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);

        /**
        * Writes the internal state of the control and its components to 
        * <code>aStream</code>. In release mode, this method does nothing.
        * It is designed to be overridden and the base called by subclasses.
        *
        * @param aWriteStream Not used
        * @remarks 
        * @see
        */
        IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
    private: // from CCoeControl
        IMPORT_C void Reserved_2();
    private: // new function
        IMPORT_C virtual void StateChanged();
        IMPORT_C virtual void Reserved_3();
    public: // framework

        /**
        * Handles pointer events.
        * 
        * @param aPointerEvent The pointer event
        * @remarks
        * @see
        */
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);

        /**
        * Handles key events offered to the Button by the control environment.
        * 
        * @param aKeyEvent The key event to respond to
        * @param aType The type of key event, either: <code>EEventKey</code>,
        *              <code>EEventKeyUp</code> or <code>EEventKeyDown</code>
        * @return indicates whether or not the key event was used by this control.
        *         <code>EKeyWasConsumed</code> if the control takes action on 
        *         the key event; <code>EKeyWasNotConsumed</code> otherwise
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * Returns the input capabilities of the Button. Typically, called by 
        * the FEP-aware text editor. By default, the Button is capable of 
        * handling all text input. 
        * 
        * @return The input capabilities of the Button
        * @remarks Used, for example, when the Button is queried by the FEP 
        *          about the types of text inputs that are consumed by the 
        *          Button. Types that may be returned by the Button include:
        *          No text input capabilities supported
        *          Supports all types of text
        *          Supports real numbers
        *          The inputs may be logically ORed
        * @see CCoeControl
        */
        IMPORT_C TCoeInputCapabilities InputCapabilities() const;
    private: // internal use only
        TBool ClickCompleted();
    private:
    enum { EIgnoreNextPointerUp=0x1000 };
    protected:
        TInt iButFlags;
    private:
        TEikButtonCoordinator* iButCoord;
        HBufC* iBubbleHelpText;
    };

/**
*
*  The <code>TEikButtonCoordinator</code> class provides the Button coordinator. 
*  An instance of this class is used to coordinate groups of Buttons on
*  the screen in which only one may be set at one time. All Buttons that
*  should be coordinated in this way share the same Button coordinator.
*
*  @lib eikcoctl.lib
*  @since 6.0
*/
class TEikButtonCoordinator
    {
    public:

        /**
        * The default object constructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C TEikButtonCoordinator();


        /**
        * Sets the selected Button in the Button group.
        * 
        * @param aChosenButton Sets <code>aChosenButton</code> to be the current
        *        selected Button in the group
        * @remarks If <code>aChosenButton</code> is different from the currently
        *          selected Button, the selected Button is set to 
        *          <code>CEikButtonBase::EClear</code> and
		*          <code>aChosenButton</code> becomes the currently selected 
        *          Button
        * @see 
        */
        IMPORT_C void SetChosenButton(CEikButtonBase* aChosenButton);       
    private:
        CEikButtonBase* iChosenButton;
    };       


#endif  // EIKBUTB_H

// End of File
