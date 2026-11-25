/*
* ==============================================================================
*  Name        : CknCheckBox.h
*  Part of     : CKON
*  Interface   : Checkbox API
*  Description : Checkbox control
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

#ifndef CKNCHECKBOX_H
#define CKNCHECKBOX_H


//  INCLUDES
#include <eikbutb.h>
#include <eikchkbx.h>
#include <CknLabelObserver.h>

class CCknSkinBase;

// CLASS DECLARATION

/**
*  This <code>CCknCheckBox</code> class implements a Checkbox control.
*
*  @lib cknctl.lib
*  @since Series90 1.0
*/
class CCknCheckBox : public CEikCheckBox, public MCknLabelObserver
    {
    public:
    /**
     * The enumeration <code>TMode</code> identifies the mode of the Checkbox.
     */
    enum TMode
        {
        /** normal mode */
        EModeNormal,
        /** multi-field numeric editor mode */
        EModeMfne
        };

    public:  // Methods

    // Constructors and destructor

        /**
        * Starts the two-phase object construction.
        * 
        * @return the Checkbox control
        * @remarks
        * @see
        */
        IMPORT_C static CCknCheckBox* NewL();

        /**
        * The object destructor.
        * 
        * @return None
        * @remarks 
        * @see
        */
        IMPORT_C ~CCknCheckBox();

        /**
        * Sets the Checkbox mode. The Checkbox can either be in normal or 
        * multifield numeric editor (MFNE) mode.
        *
        * @param aMode The mode of the Checkbox 
        * @remarks The MFNE Checkbox is bigger to allow the system to draw
        *          a focus rectangle around it
        */
        IMPORT_C void SetMode(TMode aMode);

    // Methods from base classes

        /**
        * Gets the minimum size of the Checkbox control.
        *
        * @return the minimum size of the control
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Draws the Checkbox control.
        *
        * @param aRect Not used
        * @return
        * @remarks The appropriate bitmap is used depending upon the 
        *          <code>TState</code> and the dimmed state of the control
        * @see CCoeControl
        */
        IMPORT_C void Draw(const TRect& /*aRect*/) const;

        /**
        * Handles pointer events when a caption in a dialog is tapped.
        *
        * @param aPointerEvent The pointer event from the label
        * @return
        * @remarks This behavior is unique to Checkbox
        * @see MCknLabelObserver
        */
        IMPORT_C void HandleLabelPointerL(const TPointerEvent& aPointerEvent);

    protected:
        /**
        * C++ default constructor.
        */
        IMPORT_C CCknCheckBox();

        /**
        * Symbian 2 phase constructor
        */
        IMPORT_C void ConstructL();

    private:
        CCknSkinBase& iSkin;
        TMode iMode;
        void* iReserved;
    };

#endif      // CKNCHECKBOX_H

// End of File
