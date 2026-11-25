/*
* ==============================================================================
*  Name        : eikfnlab.h
*  Part of     : CKON 
*  Interface   : Label API
*  Description : Label wrapper class for displaying a document filename.
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

#ifndef EIKFNLAB_H
#define EIKFNLAB_H

// INCLUDES
#include <eikbctrl.h>

// FORWARD DECLARATIONS
class CEikLabel;

/**
*  The <code>CEikFileNameLabel</code> class provides a Label that displays the 
*  current document's filename. This is a wrapper class around a 
*  <code>CEikLabel</code> designed for displaying the filename of the 
*  <code>CEikonEnv</code>'s current document. It automatically parses and 
*  positions the text.
*
*  Used internally and not intended to be used for application development.
*  Used by the TitleBand control
*
*  @internal
*  @lib eikcoctl.lib
*  @since Series90 1.0
*/
class CEikFileNameLabel : public CEikBorderedControl
    {
    public:

        /**
        * The C++ default object constructor.
        */
        IMPORT_C CEikFileNameLabel();

        /**
        * The object destructor.
        */
        IMPORT_C ~CEikFileNameLabel();

        /**
        * The second phase object constructor.
        * 
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void ConstructL();

        /**
        * Looks for the name of the <code>CEikonEnv</code>'s current document, 
        * gets its filename, and updates the text accordingly.
        * 
        * @return
        * @remarks
        * @see
        */
        IMPORT_C void UpdateL();
    public: // from CCoeControl 

        // not available before Release 005u
        /**
        * Gets the list of logical colors used for drawing the control. This 
        * method is no longer used. Skin functionality manages the colors for 
        * this control.
        * 
        * @param aColorUseList Not used
        * @return
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; 

        // not available before Release 005u
        /**
        * Handles a change to the control's resources that are shared across the 
        * environment.
        *
        * @param aType A <code>TInt</code> message UID value for the resource 
        *              that has changed
        * @return
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C void HandleResourceChange(TInt aType);         

        /**
        * Gets the minimum size for the Label.
        * 
        * @return the minimum size of the Label
        * @remarks
        * @see CCoeControl
        */
        IMPORT_C TSize MinimumSize();
    protected: // from CCoeControl

        /**
        * See CCoeControl.
        */
        IMPORT_C void Draw(const TRect& aRect) const;
    private: // from CCoeControl
        IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
        IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
        IMPORT_C TInt CountComponentControls() const;
        IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
        IMPORT_C void SizeChanged();
    private:
        CEikLabel* iLabel;
    };


#endif  // EIKFNLAB_H

// End of File
