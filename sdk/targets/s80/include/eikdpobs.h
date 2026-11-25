/*
* =============================================================================
*  Name        : eikdpobs.h
*  Part of     : CKON
*  Interface   : Dialog Base API
*  Description : Dialog page observer classes.
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

#ifndef EIKDPOBS_H
#define EIKDPOBS_H


// INCLUDES
#include <eikfctry.h>

// CLASS DECLARATIONS

/**
* The <code>MEikDialogPageObserver</code> class provides an interface through 
* which the behavior of the pages of a Dialog may be observed.
*
* @lib eikdlg.lib
* @since Series90 1.0
*/
class MEikDialogPageObserver
    {

    public:

    // New methods
        
        /**
        * Prepares for focus transition from the current line, for example, to validate 
        * the contents of the current control.
        *
        * @remarks
        * @see
        */
        IMPORT_C virtual void PrepareForFocusTransitionL()=0;

        /**
        * Called to take any action required before the active Dialog page is 
        * changed to <code>aPageId</code>.
        *
        * @param aPageId The ID of the new page
        * @remarks
        * @see
        */
        IMPORT_C virtual void PageChangedL(TInt aPageId)=0;

        /**
        * Takes any action required when the current line is changed to 
        * <code>aControlId</code>.
        *
        * @param aControlId The ID of the new line
        * @remarks
        * @see
        */
        IMPORT_C virtual void LineChangedL(TInt aControlId)=0;

        /**
        * Creates a custom control of type <code>aControlType</code> and
        * returns the control information for the custom control that is
        * created. Called if the Eikon control factory does not recognize the 
        * type, when creating a line on the Dialog page.
        *
        * @param aControlType The type of control
        * @return information about the created custom control
        * @remarks
        * @see
        */
        IMPORT_C virtual SEikControlInfo CreateCustomControlL(TInt aControlType)=0;

        /**
        * Gets the custom auto value for the custom control aControl of type
        * <code>aControlType</code> with return value aReturnValue.
        * This method is included in the interface to support deprecated
        * legacy code only.
        * @deprecated
        */
        IMPORT_C virtual void GetCustomAutoValue(TAny* aReturnValue,TInt aControlType,const CCoeControl* aControl)=0;

    };

/**
* The <code>MEikDialogValidatePageObserver</code> class provides an interface 
* through which the controls on Dialog pages can be validated.
*
* @lib eikdlg.lib
* @since Series90 1.0
*/
class MEikDialogValidatePageObserver
    {

    public:

    // New methods
        
        /**
        * Takes any action required before the active page is changed.
        *
        * @remarks
        * @see
        */
        IMPORT_C virtual void PrePageChangedL()=0;

    };

#endif      // EIKDPOBS_H   
            
// End of File