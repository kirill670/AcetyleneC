/*
* ==============================================================================
*  Name        : eikwbtb.h
*  Part of     : CKON / CKNMISC
*  Interface   : Title bar API
*  Description : Title bar with mover and button group.
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


#ifndef EIKWBTB_H
#define EIKWBTB_H

// INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CEikWindowButtonGroup;
class CEikMover;
class MEikWindowButtonGroupObserver;



/**
 * The <code>CEikWindowButtonTitleBar</code> class provides a title bar that 
 * comprises a <code>CEikMover</code> and a <code>CEikWindowButtonGroup</code>, 
 * and is intended for use as a window/frame title bar.
 *
 * @lib eikmisc.lib
 * @since Series90 1.0
 * @internal
 */

class CEikWindowButtonTitleBar : public CCoeControl
    {
    public://Constructors and destructors

        /**
        * The two phase object constructor.
        * 
        * @return
        * @remarks
        * @see
        */
        IMPORT_C static CEikWindowButtonTitleBar* NewL();

        /**
        * The object destructor.
        * 
        * @return
        * @remarks
        * @see
        */
        IMPORT_C ~CEikWindowButtonTitleBar();
    public:

        /**
        * Gets the minimum size for the title bar.
        * 
        * @return
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Responds to size changes to set the size and position of the title bar.
        * 
        * @return
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SizeChanged();

        /**
        * Sets a component control's container window, if the container is a 
        * window-owning control. This method sets the control's associated window 
        * to be the same as the container's associated window. 
        *
        * @param aContainer The parent control
        * @return
        * @remarks
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void SetContainerWindowL(const CCoeControl& aContainer);
    public:// accessors

        /**
        * Sets the observer for the Button.
        * 
        * @param aObserver The observer to be used
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void SetButtonObserver(MEikWindowButtonGroupObserver& aObserver);

        /**
        * Returns the Buttons on the title bar.
        * 
        * @return a reference to the button group
        * @remarks
        * @see
        */
        IMPORT_C CEikWindowButtonGroup& Buttons() const;

        /**
        * Returns the mover.
        * 
        * @return a reference to the mover
        * @remarks
        * @see
        */
        IMPORT_C CEikMover& Mover() const;

        /**
        * Sets the text of the title bar.
        * 
        * @param aText A pointer to the text to be set
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void SetText(HBufC* aText);

        /**
        * Sets the text of the title bar and allocates memory for it.
        * 
        * @param aText The text to be set
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void SetTextL(const TDesC& aText);

        /**
        * Sets the text of the title bar from a resource.
        * 
        * @param aReader A reference to the resource reader
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void SetTextFromResourceL(TResourceReader& aReader);

        /**
        * Sets the active state of the title bar.
        * 
        * @param aActive <code>ETrue</code> if the title bar is to be active; 
        *                <code>EFalse</code> otherwise
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void SetActive(TBool aActive);

        /**
        * Queries the active state of the title bar.
        * 
        * @return the active state of the title bar. <code>ETrue</code> if the 
        *         title bar is active; <code>EFalse</code> otherwise
        * @remarks
        * @see
        */
        IMPORT_C TBool IsActive() const;
    protected: //framework from CCoeControl

        /**
        * See CCoeControl
        */
        IMPORT_C TInt CountComponentControls() const;

        /**
        * See CCoeControl
        */
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
    private:
        CEikWindowButtonTitleBar();
        void ConstructL();
    private:
        CEikWindowButtonGroup*  iWindowButtons;
        CEikMover*              iMover;
    };


#endif  // EIKWBTB_H

// End of File
