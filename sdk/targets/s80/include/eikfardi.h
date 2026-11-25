/*
* ==============================================================================
*  Name        : eikfardi.h
*  Part of     : CKON
*  Interface   : Find and Replace API
*  Description : Find and Replace dialog observers
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

#ifndef EIKFARDI_H
#define EIKFARDI_H

// INCLUDES
#include <eikedwin.h>

// CLASS DECLARATIONS

/**
 * The <code>MEikFindAndReplaceDlgObserver</code> class is a mixin used by 
 * the <code>CEikFindAndReplaceDialog</code> to call back to an observer with 
 * Find and Replace instructions.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class MEikFindAndReplaceDlgObserver
    {
    public:
    // New methods
        
        /**
        * Calls back with find instructions.
        *
        * @param aModel The find model to use
        * @param aResetStart Where to start the find from. If <code>ETrue</code>,
        *                    start from the beginning; if <code>EFalse</code>,
        *                    continue from the current position
        * @return <code>ETrue</code> if the find text specified in 
		*         <code>aModel</code> was found, otherwise return 
		*         <code>EFalse</code>         
        * @remarks
        * @see
        */
        virtual TBool CallBackFindL(SEdwinFindModel& aModel, TBool aResetStart)=0;
        /**
        * Calls back with replace instructions.
        *
        * @param aModel The find model to use
        * @param aResetStart Where to start the find from. If <code>ETrue</code>,
        *                    start from the beginning; if <code>EFalse</code>,
        *                    continue from the current position
        * @return <code>ETrue</code> if the find text specified in 
		*         <code>aModel</code> was found, otherwise return 
		*         <code>EFalse</code>
        * @remarks
        * @see
        */
        virtual TBool CallBackReplaceL(SEdwinFindModel& aModel, TBool aResetStart)=0;
    };

/**
 * The <code>MEikFindAndReplaceDlgOptionsDialogObserver</code> class is an 
 * mixin used by <code>CEikFindAndReplaceDialog</code> to allow an Options 
 * sub-dialog to be displayed.
 *
 * @lib eikctl.lib
 * @since Series90 1.0
 */
class MEikFindAndReplaceDlgOptionsDialogObserver
    {
    public:
    // New methods
        
        /**
        * Runs the Options sub-dialog.
        *
        * @param aModel The find model to use
        * @param aFindOnly Whether it is a find only.
        * @return <code>ETrue</code> if dialog has been closed with the OK 
		*               button, otherwise <code>EFalse</code>
        * @remarks
        * @see
        */
        virtual TBool RunOptionsDialogLD(SEdwinFindModel& aModel, TBool aFindOnly)=0;
    };


#endif      // EIKFARDI_H   
            
// End of File
