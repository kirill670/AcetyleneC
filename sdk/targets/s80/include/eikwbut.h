/*
* ==============================================================================
*  Name        : eikwbut.h
*  Part of     : CKON
*  Interface   : Button API
*  Description : The MEikWindowButtonGroupObserver class defines an interface to
*                be implemented by a client that wishes to observe events from 
*                window buttons. The CEikWindowButtonGroup class implements 
*                window buttons, which are controls in a horizontal group of 
*                buttons for use on the title bar of a window or frame.
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


#ifndef EIKWBUT_H
#define EIKWBUT_H

/** the default Button position */
#define KEikWButDefaultButtonPos -1
// INCLUDES
#include <coecntrl.h>
#include <eikwbut.hrh>

// FORWARD DECLARATIONS
class CEikCommandButton;
class CEikControlGroup;


/**
* The <code>MEikWindowButtonGroupObserver</code> class defines an interface to 
* be implemented by a client that wishes to observe events from window buttons.
*
* @lib eikmisc.lib
* @since ER5U
* @internal
*/
class MEikWindowButtonGroupObserver
    {
    public:

        /**
        * Handles a window button's control event.
        * 
        * @param aId The <code>TInt</code> ID of the window button 
        * @param aEventType The event type
        * @return
        * @remarks
        * @see
        */
        IMPORT_C virtual void HandleWindowButtonControlEventL(TInt aId, MCoeControlObserver::TCoeEvent aEventType)=0;
    };

/**
* The <code>CEikWindowButtonGroup</code> class implements a window button,
* which is a horizontal group of buttons for use on the title bar of a window 
* or frame. Various built-in styles of window button are available or custom 
* window buttons can be constructed. Each button must have a unique integer ID.
*
* @lib eikmisc.lib
* @since ER5U
* @internal
*/
class CEikWindowButtonGroup : public CCoeControl, public MCoeControlObserver
    {
    public:// Constructor, Destructor

        /**
        * The object destructor.
        * 
        * @return
        * @remarks
        * @see
        */
        IMPORT_C ~CEikWindowButtonGroup();

        /**
        * A two-phased object constructor.
        * 
        * @return
        * @remarks
        * @see
        */
        IMPORT_C static CEikWindowButtonGroup* NewL();
    private:
        CEikWindowButtonGroup();
        void ConstructL();
    public:// Framework from CCoeControl

        /**
        * Gets the minimum size that the current arrangement of window buttons 
        * can occupy.
        * 
        * @return the minimum size for the window buttons
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize() const;
    protected:

        /**
        * Used by the framework to tell the control that its size has been changed.
        */
        IMPORT_C void SizeChanged();

        /**
        * Returns the number of component controls.
        * @return The number of component controls.
        */
        IMPORT_C TInt CountComponentControls() const;

        /**
        * Returns a pointer, without transfering ownership, to the Component control at aIndex..
        * @param aIndex The index of the control.
        * @return The component control with an index of aIndex.
        */
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
    public://From MCoeControlObserver

        /**
        * This method is used by the framework to pass on button events to the 
        * button group. 
        * 
        * @param aControl The control that sent the event
        * @param aEventType The event type
        * @return
        * @remarks
        * @see MCoeControlObserver
        */
        IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
    public:// Accessors

        /**
        * Sets <code>aObserver</code> to be called back with control events
        * associated with the window buttons.
        *
        * @param aObserver The control observer
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void SetButtonObserver(MEikWindowButtonGroupObserver& aObserver);

        /**
        * Sets the container window of the window button with the ID 
        * <code>aId</code> to be the control <code>aWindowOwner</code>.
        * 
        * @param aId The ID of the window button 
        * @param aWindowOwner The container
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void SetContainerWindowL(TInt aId, CCoeControl& aWindowOwner);

        /**
        * Sets the window button with the ID <code>aId</code> to be dimmed or 
        * undimmed.
        * 
        * @param aDimmed If <code>ETrue</code>, the Button is dimmed; otherwise 
        *                <code>EFalse</code>
        * @param aId The Button ID
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void SetButtonDimmed(TBool aDimmed, TInt aId);

        /**
        * Determines if the Button with the ID <code>aId</code> is dimmed.
        * 
        * @param aId The Button ID
        * @return <code>ETrue</code> if the button at <code>aId</code> is dimmed;
        *         <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsDimmed(TInt aId);

        /**
        * Returns a pointer to the Button with ID <code>aId</code>, 
        * or <code>NULL</code> if there is no Button for this ID.
        * 
        * @param aId The Button ID
        * @return a pointer to the Button
        * @remarks
        * @see
        */
        IMPORT_C CCoeControl* Button(TInt aId) const;

        /**
        * Adds the control <code>aButton</code> with the ID <code>aId</code> 
        * to the group, at position <code>aPos</code>.
        * 
        * @param aId The Button ID
        * @param aButton The window button control
        * @param aPos The position of the window button
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void AddButtonL(TInt aId, CCoeControl* aButton, TInt aPos=KEikWButDefaultButtonPos);

        /**
        * Removes the button with the ID <code>aId</code> from the group and 
        * deletes it.
        * 
        * @param aId The Button ID
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void RemoveButton(TInt aId);

        /**
        * Adds a Close Button to the group at position <code>aPos</code>.
        * 
        * @param aPos The position at which to add the Close Button
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void AddCloseButtonL(TInt aPos=KEikWButDefaultButtonPos);

        /**
        * Adds a Minimize Button to the group at position <code>aPos</code>.
        * 
        * @param aPos The position at which to add the Minimize Button
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void AddMinimizeButtonL(TInt aPos=KEikWButDefaultButtonPos);

        /**
        * Adds a Maximize button to the group at position <code>aPos</code>.
        * 
        * @param aPos The position at which to add the Maximize Button
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void AddMaximizeButtonL(TInt aPos=KEikWButDefaultButtonPos);

        /**
        * Adds a 'Standard size' Button to the group at position 
        * <code>aPos</code>.
        * 
        * @param aPos The position at which to add the Standard Size Button
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void AddStandardSizeButtonL(TInt aPos=KEikWButDefaultButtonPos);

        /**
        * Adds a Resize button to the group at position <code>aPos</code>.
        * 
        * @param aPos The position at which to add the Resize Button
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void AddResizeButtonL(TInt aPos=KEikWButDefaultButtonPos);

        /**
        * Returns a reference to the <code>CEikControlGroup</code> that owns the 
        * Buttons.
        * 
        * @return the reference to the <code>CEikControlGroup</code>
        * @remarks
        * @see
        */
        IMPORT_C CEikControlGroup& ButtonGroup() const;
    private:
        void AddStandardButtonL(TInt aId, TInt aResourceId, TInt aPos);
    private:
        MEikWindowButtonGroupObserver*      iObserver;
        CEikControlGroup*                   iButtonGroup;
    };


#endif  // EIKWBUT_H

// End of File
