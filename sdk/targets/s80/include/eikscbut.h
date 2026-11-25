/*
* =============================================================================
*  Name        : eikscbut.h
*  Part of     : CKON
*  Interface   : Scrollbar API
*  Description : Scrollbar buttons.
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

#ifndef EIKSCBUT_H
#define EIKSCBUT_H


// INCLUDES
#include <eikbutb.h>
#include <lafpublc.h>


// FORWARD DECLARATIONS
class MEikScrollBarCustomDrawBase;


// CLASS DECLARATIONS

/**
* The <code>CEikScrollButton</code> class provides a nudge button.
*
* @lib eikcoctl.lib
* @since 6.0
*/
class CEikScrollButton : public CEikButtonBase
    {
public:  // Declarations

    /**
    * The enumeration <code>TType</code> determines a nudge button's type.
    */
    enum TType
        {
        /** nudge button to move the display to the left */
        ENudgeLeft=SLafScrollButton::ENudgeLeft,
        /** nudge button to move the display up */
        ENudgeUp=SLafScrollButton::ENudgeUp,
        /** nudge button to move the display to the right */
        ENudgeRight=SLafScrollButton::ENudgeRight, 
        /** nudge button to move the display down */
        ENudgeDown=SLafScrollButton::ENudgeDown, 
        /** nudge button to move the display one page to the left */
        EPageLeft=SLafScrollButton::EPageLeft, 
        /** nudge button to move the display one page up */
        EPageUp=SLafScrollButton::EPageUp, 
        /** nudge button to move the display one page to the right */
        EPageRight=SLafScrollButton::EPageRight, 
        /** nudge button to move the display one page down */
        EPageDown=SLafScrollButton::EPageDown, 
        // nudge button to move the display to the home position.
        /** not supported by Series 90 */
        EHome=SLafScrollButton::EHome, 
        // nudge button to move the display to the top.
        /** not supported by Series 90 */
        ETop=SLafScrollButton::ETop,
        // nudge button to move the display to the end position.
        /** not supported by Series 90 */
        EEnd=SLafScrollButton::EEnd, 
        // nudge button to move the display to the bottom.
        /** not supported by Series 90 */
        EBottom=SLafScrollButton::EBottom
        };

    /** 
    * The enumeration <code>TTypeOfScrollBar</code> determines the type of 
    * Scrollbar that the button is used in. 
    */
    enum TTypeOfScrollBar
         {
         /** the Scrollbar complete with shaft */
         ENormal     =0x00,
         /** the floating nudge button, without shaft or thumb */
         EArrowHead  =0x01
         };

public:

    // Constructors and destructor

    /**
    * The object destructor.
    */
    IMPORT_C ~CEikScrollButton();

    /**
    * The object constructor
    *
    * @param aType The type of nudge button
    * @remarks
    * @see
    */
    IMPORT_C CEikScrollButton(TType aType);

    // New methods

    /**
    * Gets the nudge button type.
    *
    * @return the type of nudge button
    * @remarks
    * @see
    */
    IMPORT_C TType Type() const;

    /**
    * Sets the nudge button's background custom drawer.
    *
    * @param aCustomDrawer The nudge button's background custom drawer
    * @remarks
    * @see 
    */
    IMPORT_C void SetCustomDrawer(MEikScrollBarCustomDrawBase* aCustomDrawer);

    // Methods from base classes

    /**
    * Sets whether or not the control is dimmed.
    *
    * @param aDimmed <code>ETrue</code> to dim the control, <code>EFalse</code>
    * to set the control as not dimmed
    * @remarks
    * @see CCoeControl
    */
    IMPORT_C virtual void SetDimmed(TBool aDimmed);

    /**
    * Gets the list of logical colors used for drawing the control. This 
    * method is no longer used. Skin functionality manages the colors for 
    * this control.
    * 
    * @param aColorUseList Not used
    * @remarks
    * @see CCoeControl
    */
    IMPORT_C virtual void GetColorUseListL(
                             CArrayFix<TCoeColorUse>& aColorUseList) const;

    /**
    * Handles a change to the control's resources that are shared across the 
    * environment.
    * 
    * @param aType A <code>TInt</code> message UID value for the resource 
    *              that has changed
    * @remarks
    * @see CCoeControl
    */
    IMPORT_C virtual void HandleResourceChange(TInt aType);

protected:  // Methods

    // Methods from base classes
        
    /**
    * @internal
    */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

private: //Methods

    virtual void Draw(const TRect& aRect) const;
    virtual void StateChanged();

private:     // Data

    friend class CEikScrollBar;
    TType iType;
    TInt iFlag;
    MEikScrollBarCustomDrawBase* iCustomDrawer;

    };

/**
* Provides methods to create a nudge button and to handle pointer events.
*
* @lib eikcoctl.lib
* @since 6.0
*/
class CEikArrowHeadScrollButton : public CEikScrollButton
    {

public: //Methods

    // Constructors and destructor

    /**
    * Static constructor.
    *
    * @param aParent The nudge button's parent control
    * @param aType The type of nudge button to create
    * @return the new nudge button object
    * @remarks <code>aType</code> is an inherited member variable
    * @see 
    */
    IMPORT_C static CEikArrowHeadScrollButton* NewL(const CCoeControl* aParent,
                                                    TType aType);

    // New methods
        
    /**
    * @internal
    */
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);

    /**
    * @internal
    */
    void HandleResourceChange(TInt aType);

private: //Methods

    CEikArrowHeadScrollButton(TType aType);
    void BaseConstructL(const CCoeControl* aParent);

protected: // Methods

    // Methods from base classes
        
    /**
    * From CCoeControl
    */
    IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;

private: //Methods

    virtual void Draw(const TRect& aRect) const;

private:     // Data

    TInt iFlag;
    TInt iDummy;
    TRgb iBrush;

    };


#endif      // EIKSCBUT_H   

// End of File