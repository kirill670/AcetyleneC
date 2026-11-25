/*
* ==============================================================================
*  Name        : eikubgcb.h
*  Part of     : CKON
*  Interface   : Button group API
*  Description : Mixin class for controls that can change the first button in a 
*  Description : Button Group containers when they get focus
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


#ifndef EIKUBGCB_H
#define EIKUBGCB_H

// INCLUDES
#include <EikCmObs.h>

// FORWARD DECLARATIONS
class CEikButtonGroupContainer;

/**
 * The <code>MEikUpdatingBgContainerBase</code> class is the base class for 
 * controls that change the first button of a Button Group container
 * when it gets focus. To ensure that the button is restored, the control 
 * should call <code>AddOrRemoveChangeButton(IsFocused())</code> in its 
 * <code>FocusChanged()</code> method and <code>AddOrRemoveChangeButton(EFalse)</code>
 * in its destructors. <code>HandleChangeButtonL()</code> will be called when 
 * the button is selected. If the control is displaying a pop-out, 
 * <code>PopupDisplayed()</code> should return <code>ETrue</code>. 
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class MEikUpdatingBgContainerBase : public MEikCommandObserver
    {
    public:

       /**
        * Adds or removes a button observer.
        *
        * @param aAdd <code>ETrue</code> to add a button observer. 
        *             <code>EFalse</code> to remove one
        * @param aRid The resource ID of the button observer to be added, if 
        *             relevant
        * @remarks
        * @see
        */
        IMPORT_C void AddOrRemoveChangeButton(TBool aAdd,TInt aRid=NULL);
    protected:

       /**
        * Called when the change button is activated.
        *
        * @remarks
        * @see
        */
        virtual void HandleChangeButtonL()=0;

       /**
        * @internal
        * @return ETrue to prevent a button observer from being removed while a popup is being shown.
        */
        virtual TBool PopupDisplayed()=0;
       /** @internal */
        CEikButtonGroupContainer* ButtonGroupContainer();
    private:
        IMPORT_C void RemoveCommandButtonObserver();
        IMPORT_C void AddCommandButtonObserverL(TInt aRid);
    private: // from MEikCommandObserver
        IMPORT_C void ProcessCommandL(TInt aCommandId);
    private:
        CEikButtonGroupContainer* iButtonGroupContainer;
        TBool iCommandObserverUpdated;
    };


#endif  // EIKUBGCB_H

// End of File
