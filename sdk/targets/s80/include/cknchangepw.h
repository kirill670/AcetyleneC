// CKNCHANGEPW.H
//
// Copyright (c) Nokia Corporation 2002. All rights reserved.
//

#if !defined(__CKNCHANGEPW_H__)
#define __CKNCHANGEPW_H__

#include <eikdialg.h>
#include <cknsecreteditor.h>

class CSecurityBase;

/**
 * The <code>CCknChangePasswordDialog</code> class implements a Change Password
 * dialog for Ckon. It consists of two instances of <code>CCknSecretEditor</code> 
 * (see cknchangepw.h) and can be used to change an existing password. The 
 * existing password must be verified before the password can be changed, and 
 * the new password must be entered correctly twice using the two edit fields 
 * on the dialog. Password protection can be disabled using the checkbox on 
 * the dialog. Clients should call a variant of <code>RunDlgLD()</code> to 
 * launch the dialog.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknChangePasswordDialog : public CEikDialog
    {
public:
    /**
    * Launches the Change Password dialog. When this method 
    * returns, the dialog has been dismissed (by pressing OK
    * or Cancel) and destroyed.
    *
    * @param aSecurity Security object
    * @param aPasswd The existing password.
    *                Must be valid (see <code>CSecurityBase</code>) 
    *                otherwise the password cannot be changed
    * @return <code>ETrue</code> if the user taps OK; otherwise
    *         <code>EFalse</code>
    * @remarks To retrieve the changed password, the virtual methods of 
    *          the object derived from <code>CSecurityBase</code> must be 
    *          implemented appropriately and the new password from this object
    *          must be acquired
    * @see <code>CSecurityBase</code>
    */
    IMPORT_C static TBool RunDlgLD(CSecurityBase& aSecurity,
                                    TPassword& aPasswd);
    
    /**
    * Launches the Change Password dialog. When this method
    * returns, the dialog has been dismissed (by pressing OK
    * or Cancel) and destroyed. This variant allows more 
    * settings to be supplied for the dialog launch.
    *
    * @param aSecurity Security object
    * @param aPassword The existing password. Must be valid
    *                  otherwise the password cannot be changed
    * @param aMaxPasswordLength The maximum number of characters that the new 
    *                           password can contain - must be between 
    *                           <code>aMinPasswordLength</code> and 
    *                           <code>KCknMaxPassword</code> (256)
    * @param aMinPasswordLength The minimum number of characters that the new 
    *                           password can contain - must be between 1 
    *                           and <code>aMaxPasswordLength</code>
    * @param aMaxPasswordControlWidth The maximum width in characters of the 
    *                                 secret edit fields
    * @return <code>ETrue</code> if the user taps OK; otherwise 
    *          <code>EFalse</code>
    * @remarks To retrieve the changed password, implement the virtual methods
    *          of the object derived from <code>CSecurityBase</code> 
    *          appropriately and then acquire the new password from this object
    * @see <code>CSecurityBase</code>
    */
    IMPORT_C static TBool RunDlgLD(
                                    CSecurityBase& aSecurity, 
                                    const TCknPassword& aPassword, 
                                    TInt aMaxPasswordLength=KCknStandardPassword,
                                    TInt aMinPasswordLength=KCknMinPassword,
                                    TInt aMaxPasswordControlWidth=KCknStandardPasswordControlWidth);
private: 
    CCknChangePasswordDialog(
                                    CSecurityBase& aSecurity,
                                    TInt aMaxPasswordLength,
                                    TInt aMinPasswordLength,
                                    TInt aMaxPasswordControlWidth);
    ~CCknChangePasswordDialog();
    void PreLayoutDynInitL();
    void HandleControlStateChangeL(TInt aControlId);
    TBool OkToExitL(TInt aButtonId);
    
private:
    CSecurityBase& iSecurity;
    HBufC* iOldPassword;
    TInt iMaxPasswordLength;
    TInt iMinPasswordLength;
    TInt iMaxPasswordControlWidth;
    };

#endif