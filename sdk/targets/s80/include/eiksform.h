/**
* ==============================================================================
*  Name        : eiksform.h
*  Part of     : CKON / EIKDLG
*  Interface   : Form API
*  Description : Scrollable Form
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


#ifndef EIKSFORM_H
#define EIKSFORM_H

// INCLUDES
#include <coeccntx.h>
#include <eikform.h>
#include <eikscrlb.h>

/**
 * Scrollable form control.This is an extension of the <code>CEikForm</code>
 * class. The control that is displayed first can be varied so this control can
 * support a scrollbar. This widget does not come with a scrollbar - for that
 * use a <code>CEikScrollableFormContainer</code>.
 *  
 * @lib eikdlg.lib
 * @since Series90 1.0
 */
class CEikScrollableForm : public CEikForm
    {
    public:

        /**
        * C++ default constructor.
        */
        IMPORT_C CEikScrollableForm();

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CEikScrollableForm();

        /**
        * Completes construction of a scrollable form control.
        * 
        * @param aParent The <code>CCoeControl</code> parent of this form
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void ConstructL(const CCoeControl& aParent);

        /**
        * Calculates the line that <code>aYPos</code> is on and adjusts
        * <code>aYPos</code> to the top of that line. <code>YPos</code> is
        * relative to the <code>ViewWin</code> not the <code>DataWin</code>.
        *
        * @param aYPos A Y position within the form
        * @return the line that the (newly adjusted) <code>aYPos</code> is on
        * @remarks
        * @see
        */
        IMPORT_C TInt YPosToLine(TInt& aYPos) const;

        /**
        * Calculates the <code>YPos</code> of line relative to the 
        * <code>ViewWin</code> and adjusts <code>aLine</code> if it is out of
        * bounds.
        *
        * @param aLine The line to calculate the <code>YPos</code> of
        * @return the <code>YPos</code> of the line
        * @remarks
        * @see
        */
        IMPORT_C TInt LineToYPos(TInt& aLine) const;

        /**
        * Exposes the given line so that it is fully visible in the
        * <code>ViewWin</code>.
        *
        * @param aLine The line to be exposed
        * @remarks
        * @see
        */
        IMPORT_C void ExposeLine(TInt aLine);

        /**
        * Sets the y coordinate of the <code>DataWin</code> to the given
        * <code>aPosition</code>.
        *
        * @param aPosition The new y coordinate for the <code>DataWin</code>
        * @remarks
        * @see
        */
        IMPORT_C void SetDataPosition(TInt aPosition);
    public://simple getter functions

        /**
        * Returns the height of the control at the index specified by
        * <code>aLineIndex</code>.
        *
        * @param aLineIndex The control to determine the height of
        * @return the height of the control
        * @remarks
        * @see
        */
        IMPORT_C TInt ControlHeight(TInt aLineIndex) const;
    public: //from CCoeControl

        /**
        * Gets the minimum size for the scrollable form control.
        * 
        * @return the minimum size of the form
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual TSize MinimumSize();

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

        /**
        * Handles a change to the control's resources that are shared across
        * the environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u
    protected:

        /**
        * See CCoeControl
        */
        IMPORT_C virtual void ActivateL();

        /**
        * See CCoeControl
        */
        IMPORT_C virtual void SizeChanged();
    private: // from CCoeControl
        IMPORT_C void Reserved_1();
        IMPORT_C void Reserved_2();
    private: // from CEikForm
        IMPORT_C virtual void Reserved_3();
    private:
        RWindow* iViewWin;
    };

/**
 * Scrollable form control. This is a wrapper class containing a 
 * <code>CEikScrollableForm</code> and a scrollbar.
 *
 * @lib  eikdlg.lib
 * @since Series90 1.0
 */
class CEikScrollableFormContainer : public CEikBorderedControl, public MEikScrollBarObserver
    {
    public:

        /**
        * C++ default constructor.
        */
        IMPORT_C CEikScrollableFormContainer();

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CEikScrollableFormContainer();

        /**
        * Creates a scroll bar.
        *
        * @remarks
        * @see
        */
        IMPORT_C void CreateScrollBarL();

        /**
        * Refreshes/updates the scroll bar.
        *
        * @remarks
        * @see
        */
        IMPORT_C void UpdateScrollBarL();
    public://from CCoeControl

        /**
        * Gets the minimum size for the form.
        * 
        * @return the minimum size of the form
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual TSize MinimumSize();

        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

        /**
        * Handles a change to the control's resources that are shared across
        * the environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);         // not available before Release 005u
    protected:// from MEikScrollBarIObserver

        /**
        * Handles a scroll event - See MEikScrollBarIObserver
        * @param aScrollBar A pointer to the scroll bar object
        * @param aEventType The type of event
        * @return void
        */
        IMPORT_C virtual void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);
    protected://from CCoeControl

        /**
        * See CCoeControl
        */
        IMPORT_C virtual void SizeChanged();

        /**
        * Returns the number of component controls on the form - See CCoeControl
        * @return Number of component controls
        */
        IMPORT_C virtual TInt CountComponentControls() const;

        /**
        * Returns the component control with the specified index - See CCoeControl
        * @param aIndex The index of the required component control
        * @return A pointer to the component control
        */
        IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;
    private:
        IMPORT_C void Dummy1(); // To fill gap in .DEF file from removing reserved function
        IMPORT_C void Dummy2(); // To fill gap in .DEF file from removing reserved function
    protected:
        CEikScrollableForm* iScrollableForm;
        CEikScrollBar* iScrollBar;
    };


#endif  // EIKSFORM_H

// End of File
