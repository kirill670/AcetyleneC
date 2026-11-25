/*
* ==============================================================================
*  Name        : eikchkbx.h
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

#ifndef EIKCHKBX_H
#define EIKCHKBX_H


//  INCLUDES
#include <eikbutb.h>

// CLASS DECLARATION

/**
*  The <code>CEikCheckBox</code> class implements a Checkbox control.
*
*  @lib eikctl.lib
*  @since Series 90 1.0
*/
class CEikCheckBox : public CEikButtonBase
    {
    public:  // Methods

    // Constructors and destructor

        /**
        * The C++ default object constructor.
        *
        * @return
        * @remarks
        * @see        
        */
        IMPORT_C CEikCheckBox();

        /**
        * A static two-phase object constructor.
        * Not exported so not accessible to the developer.
        *
        * @internal
        * @return
        * @remarks
        * @see
        */
        static CEikCheckBox* NewL();

        /**
        * The object destructor.
        * 
        * @remarks
        * @see
        */
        IMPORT_C ~CEikCheckBox();


    // New methods

        /**
        * The second-phase object constructor. This method currently has no 
        * implementation.
        *
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL();

        /**
        * Constructs a Checkbox from a resource file. 
        * 
        * @param aReader A resource reader
        * @remarks The resource control factory identifier is
        *          <code>EEikCtCheckBox</code>. It has no resource struct
        * @see <code>CCoeControl</code>
        */
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

    // Methods from base classes

        /**
        * Gets the minimum size of the Checkbox control. 
        *
        * @return the minimum size of the Checkbox control
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TSize MinimumSize();

        /**
        * Draws the border around the Checkbox control. This method also clears
        * the central area if the <code>CCoeControl::IsBlank()</code> method 
        * returns <code>ETrue</code>.
        *
        * @param aRect Not used
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void Draw(const TRect& /*aRect*/) const;

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
        * Handles a change to the control's resources that are shared across 
        * the environment.
        * 
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C virtual void HandleResourceChange(TInt aType);

    };

#endif      // EIKCHKBX_H

// End of File
