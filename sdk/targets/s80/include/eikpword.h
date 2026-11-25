/*
* ==============================================================================
*  Name        : eikpword.h
*  Part of     : CKON
*  Interface   : Password API
*  Description : Password dialogs
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


#ifndef EIKPWORD_H
#define EIKPWORD_H

// INCLUDES
#include <eikdialg.h>
#include <cknsecreteditor.h>

// FORWARD DECLARATIONS
class CSecurityBase;

/**
* The <code>CEikSetPasswordDialog</code> class implements a Set 
* Password dialog. This class consists of two edit fields and 
* is used to change an existing password. The existing password must be 
* verified before the password can be changed, and the new password must be 
* entered correctly twice using the two edit fields on the dialog.
* Clients should call a variant of <code>RunDlgLD()</code> to 
* launch the dialog.
*
* @lib eikcdlg.lib
* @since Series90 1.0
*/
class CEikSetPasswordDialog : public CEikDialog
    {
public:
    /**
    * Launches the Set Password dialog. When this method
    * returns, the dialog has been dismissed (by tapping OK
    * or Cancel) and destroyed.
    *
    * @param aSecurity Security object
    * @param aOldPassword The existing password.
    *                     Must be valid (see <code>CSecurityBase</code>) 
    *                     otherwise the password cannot be changed
    * @return <code>ETrue</code> if the user taps OK; otherwise
    *         <code>EFalse</code>
    * @remarks To retrieve the changed password, implement the virtual methods
    *          of the object derived from <code>CSecurityBase</code> 
    *          appropriately and then acquire the new password from the 
    *          <code>CSecurityBase</code> object
    * @see <code>CSecurityBase</code>
    */
    IMPORT_C static TBool RunDlgLD(CSecurityBase& aSecurity,TPassword& aOldPassword);

    /**
    * Launches the Set Password dialog if no password is currently set. When 
    * this method returns, the dialog has been dismissed (by tapping OK or 
    * Cancel) and destroyed. This variant allows more settings to be 
    * supplied for the dialog launch.
    *
    * @param aSecurity Security object
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
    *          appropriately and then acquire the new password from the 
    *          <code>CSecurityBase</code> object
    * @see <code>CSecurityBase</code>
    */
    IMPORT_C static TBool RunDlgLD(
                                    CSecurityBase& aSecurity,
                                    TInt aMaxPasswordLength=KCknStandardPassword,
                                    TInt aMinPasswordLength=KCknMinPassword,
                                    TInt aMaxPasswordControlWidth=KCknStandardPasswordControlWidth);
    private: 
    CEikSetPasswordDialog(
                                    CSecurityBase& aSecurity,
                                    TPassword& aOldPassword,
                                    TInt aMaxPasswordLength,
                                    TInt aMinPasswordLength,
                                    TInt aMaxPasswordControlWidth);
    // from CEikDialog
        TBool OkToExitL(TInt aButtonId);
        void PreLayoutDynInitL();
    private:
        CSecurityBase& iSecurity;
        TPassword& iOldPassword;
        TInt iMaxPasswordLength;
        TInt iMinPasswordLength;
        TInt iMaxPasswordControlWidth;
    };


/**
 * The <code>CEikVerifyPasswordDialog</code> class implements dialogs 
 * that are used to verify a password. These dialogs consist of
 * a single edit field and OK and Cancel buttons.
 * The user enters a password that is verified against the 
 * password passed to the static method that launched the dialog.
 * Clients should call a variant of either <code>RunDlgLD()</code> or
 * <code>RunGetOldPasswordDlgLD()</code> to perform the dialog launch.
 * 
 * @lib eikcdlg.lib
 * @since Series90 1.0
 */
class CEikVerifyPasswordDialog : public CEikDialog
    {
    public:
    /** 
     * The enumeration <code>TVerifyPasswordDialogType</code> specifies the 
     * type of dialog to run. It determines the dialog title 
     * and infoprint text.
     */
    enum TVerifyPasswordDialogType
        {
        /** confirms the password before granting access */
        EVerifyPassword,
        /** confirms the password before the password is changed or removed */
        EGetOldPassword  // 
        };
    public:

    /**
    * Runs a dialog to verify a password. 
    *
    * @param aPasswordCorrect <code>ETrue</code> if the user enters the
    *                         password that matches <code>aSecurity</code>,
    *                         or else <code>EFalse</code>
    * @param aSecurity Security object
    * @param aPassword The existing password. Must be valid
    * @returns <code>ETrue</code> if the user taps OK; <code>EFalse</code>
    *          otherwise
    * @remarks Assumes that the <code>CSecurityBase</code> object 
    *          implements <code>PrepareL()</code> to verify the password
    * @see <code>CSecurityBase</code>
    */
    IMPORT_C static TBool RunDlgLD(
                                    TBool& aPasswordCorrect,
                                    const CSecurityBase& aSecurity,
                                    TPassword& aPassword);

    /**
    * Runs a dialog to verify a password. Like 
    * <code>RunDlgLD()</code> except with different text
    * for the dialog title.
    *
    * @param aPasswordCorrect <code>ETrue</code> if the user enters the
    *                         password that matches <code>aSecurity</code>;
    *                         <code>EFalse</code> otherwise
    * @param aSecurity Security object
    * @param aPassword The existing password. Must be valid
    * @returns <code>ETrue</code> if the user taps OK; <code>EFalse</code>
    *          otherwise
    * @remarks Assumes that the <code>CSecurityBase</code> object 
    *          implements <code>PrepareL()</code> to verify the password
    * @see <code>CSecurityBase</code>
    */
    IMPORT_C static TBool RunGetOldPasswordDlgLD(
                                    TBool& aPasswordCorrect,
                                    const CSecurityBase& aSecurity,
                                    TPassword& aPassword);

   /**
    * Runs a dialog to verify a password.
    *
    * @param aPasswordCorrect <code>ETrue</code> if the user enters the
    *                         password that matches <code>aSecurity</code>;
    *                         <code>EFalse</code> otherwise
    * @param aSecurity Security object
    * @param aPassword The existing password. Must be valid
    *                  The length must not be greater than 
    *                  <code>aMaxPasswordLength</code>
    * @param aMaxPasswordLength The maximum number of characters that the 
    *                           password can contain - must be between 1 and 
    *                           <code>KCknMaxPassword</code> (256)
    * @param aMaxPasswordControlWidth The maximum width in characters of the 
    *                                 secret editor control
    * @returns <code>ETrue</code> if the user taps OK; <code>EFalse</code>
    *          otherwise
    * @remarks Assumes that the <code>CSecurityBase</code> object 
    *          implements <code>PrepareL()</code> to verify the password
    * @see <code>CSecurityBase</code>
    */
    IMPORT_C static TBool RunDlgLD(
                                    TBool& aPasswordCorrect,
                                    const CSecurityBase& aSecurity,
                                    TCknPassword& aPassword,
                                    TInt aMaxPasswordLength=KCknStandardPassword,
                                    TInt aMaxPasswordControlWidth=KCknStandardPasswordControlWidth);

   /**
    * Runs a dialog to verify a password. Like <code>RunDlgLD()</code> 
    * except with different text for the dialog title.
    *
    * @param aPasswordCorrect <code>ETrue</code> if the user enters the
    *                         password that matches <code>aSecurity</code>;
    *                         <code>EFalse</code> otherwise
    * @param aSecurity Security object
    * @param aPassword The existing password. Must be valid
    *                  The length must not be greater than 
    *                  <code>aMaxPasswordLength</code>
    * @param aMaxPasswordLength The maximum number of characters that the 
    *                           password can contain - must be between 1 and 
    *                           <code>KCknMaxPassword</code> (256)
    * @param aMaxPasswordControlWidth The maximum width in characters of the 
    *                                 secret editor control
    * @returns <code>ETrue</code> if the user taps OK; <code>EFalse</code>
    *          otherwise
    * @remarks Assumes that the <code>CSecurityBase</code> object 
    *          implements <code>PrepareL()</code> to verify the password
    * @see <code>CSecurityBase</code>
    */
    IMPORT_C static TBool RunGetOldPasswordDlgLD(
                                    TBool& aPasswordCorrect,
                                    const CSecurityBase& aSecurity,
                                    TCknPassword& aPassword,
                                    TInt aMaxPasswordLength=KCknStandardPassword,
                                    TInt aMaxPasswordControlWidth=KCknStandardPasswordControlWidth);
    private: 
    CEikVerifyPasswordDialog(
                                    TBool& aPasswordCorrect,
                                    const CSecurityBase& aSecurity,
                                    TDes& aPassword,
                                    TVerifyPasswordDialogType aDialogType,
                                    TInt aMaxPasswordLength,
                                    TInt aMaxPasswordControlWidth);
    // from CEikDialog
        TBool OkToExitL(TInt aButtonId);
        void PreLayoutDynInitL();
    private:
        TBool& iPasswordCorrect;  // truth value is given back
        const CSecurityBase& iSecurity;
        TDes& iPassword;
        TVerifyPasswordDialogType iDialogType;
        TInt iMaxPasswordLength;
        TInt iMaxPasswordControlWidth;
    };



#endif  // EIKPWORD_H

// End of File
