/*
* =============================================================================
*  Name        : cknmcanc.h
*  Part of     : CKON
*  Interface   : 
*  Description : MCknCancellableOperation class implements operation 
*                cancelling.
*                Class MCknCancelDialog to access cancel note from Dialog 
*                factory.
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


#ifndef CKNMCANC_H
#define CKNMCANC_H

// INCLUDES
#include <coecntrl.h>

/**
*  The <code>MCknCancellableOperation</code> class implements operation
*  canceling.
*
*  @lib 
*  @since Series90 1.0
*/
class MCknCancellableOperation
    {
    public:

        /**
        * This method is called when a running operation is to be canceled.
        * Typically, this method is called in response to a user tapping 
        * the Cancel button in a Cancel Note.
        *
        * @remarks 
        * @see
        */
        virtual void CancelOperation()=0;
    };


/**
*  The <code>MCknCancelDialog</code> class is used to access the Cancel Note 
*  from the dialog factory.
*
*  @lib 
*  @since Series90 1.0
*/
class MCknCancelDialog
    {
    public:

        /**
        * Launches a Cancel Note.
        *
        * @return <code>EFalse</code>
        * @remarks Always returns <code>EFalse</code>
        * @see
        */
        IMPORT_C virtual TBool RunDlgLD()=0;

        /**
        * This method is called when all resources allocated should be freed.
        *
        * @remarks
        * @see
        */
        IMPORT_C virtual void Release()=0;

        /**
        * Casts <code>this</code> to a <code>CCoeControl*</code>.
        *
        * @return a pointer to <code>CCoeControl</code>
        * @remarks
        * @see
        */
        IMPORT_C virtual CCoeControl* AsControl()=0;
    };


#endif  // CKNMCANC_H

// End of File