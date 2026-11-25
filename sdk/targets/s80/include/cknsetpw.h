/*
* ==============================================================================
*  Name        : cknsetpw.h
*  Part of     : CKON
*  Interface   : Password API
*  Description : Password dialog
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


#ifndef CKNSETPW_H
#define CKNSETPW_H

// INCLUDES
#include <eikdialg.h>

/**
 * The <code>CCknSetPasswordDialog</code> class implements a Set Password 
 * dialog for Ckon. This class consists of two instances of 
 * <code>CEikSecretEditor</code> (see cknsetpw.h) and is used to enter a 
 * new password. Clients should call <code>RunDlgLD</code> to launch the 
 * dialog.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknSetPasswordDialog : public CEikDialog
    {
    public:
        /**
        * Launches the Set Password dialog. When this method returns, the 
        * dialog has been dismissed (by pressing OK or Cancel) and destroyed.
        *
        * @param aPasswd If the two passwords in the edit fields match 
        *                and if OK is tapped, on return, contains the password 
        *                entered into the dialog 
        * @return <code>ETrue</code> if the user selects OK; otherwise 
        *         <code>EFalse</code>
        * @remarks The dialog is not seeded with the initial value of 
        *          <code>aPasswd</code>; both edit fields are empty
        * @see
        */
        IMPORT_C static TBool RunDlgLD(TPassword& aPasswd);

        /**
        * Method for retrieving help information. From CCoeControl.
        *
        * @param    aContext On return, contains help information
        * @internal
        * @remarks  Not accessible by clients
        * @see      CCoeControl
        */
        void GetHelpContext(TCoeHelpContext& aContext) const;
    private: 
        CCknSetPasswordDialog(TPassword& aPasswd);
        ~CCknSetPasswordDialog();
        TBool OkToExitL(TInt aButtonId);
    private:
        TPassword *iPasswd;
    };


#endif  // CKNSETPW_H

// End of File
