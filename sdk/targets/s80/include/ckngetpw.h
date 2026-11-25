/*
* ==============================================================================
*  Name        : ckngetpw.h
*  Part of     : CKON
*  Interface   : Password API
*  Description : Password dialog.
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


#ifndef CKNGETPW_H
#define CKNGETPW_H

// INCLUDES
#include <eikdialg.h>

// FORWARD DECLARATIONS
class CEikCaptionedControl;
class CCknInputFrame;

/**
 * The <code>CCknGetPasswordDialog</code> class implements the Get Password 
 * dialog. This class consists of one instance of <code>CEikSecretEditor</code>
 * (see ckngetpw.h) and it is used to ask the user for a password. Clients 
 * should call <code>RunDlgLD()</code> to launch the dialog.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknGetPasswordDialog : public CEikDialog
    {
    public:
        /**
        * Launches the Get Password dialog. When this method returns, the 
        * dialog has been dismissed (by pressing OK or Cancel) and destroyed.
        *
        * @param aPasswd On return, contains the password entered 
        *                into the dialog, if OK is tapped
        * @return <code>ETrue</code> if OK is tapped; <code>EFalse</code> if 
        *         Cancel is tapped
        * @remarks The dialog is not seeded with the initial value of 
        *          <code>aPasswd</code>; it is empty
        * @see
        */
        IMPORT_C static TBool RunDlgLD(TPassword& aPasswd);

        /**
        * Method for retrieving help information. From CCoeControl.
        * @internal
        * @param    aContext On return, contains help information
        * @return
        * @remarks  Not accessible by clients
        * @see      CCoeControl
        */
        void GetHelpContext(TCoeHelpContext& aContext) const;
    private: 
        CCknGetPasswordDialog(TPassword& aPasswd);
        ~CCknGetPasswordDialog();
        void PostLayoutDynInitL();
        TBool OkToExitL(TInt aButtonId);
    private:
        TPassword *iPasswd;
    };


#endif  // CKNGETPW_H

// End of File
