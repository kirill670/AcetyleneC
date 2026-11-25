// COEFEPFF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COEFEPFF_H__)
#define __COEFEPFF_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

class CCoeFepParameters;
class CCoeFep;

/**
 *
 * FEP factory function must be exported by every FEP.
 *
 * The function is called by the UI Control Framework when it loads the
 * FEP. It returns a fully constructed object of a
 * <code>CCoeFep</code>-derived class, and passes ownership of that
 * object to the caller.
 *
 * @since     6.0
 * @param     "CCoeEnv& aConeEnvironment"
 *            A reference to the application's control environment.
 * @param     "const TDesC& aFullFileNameOfDll"
 *            The full file-name of the FEP's top-level DLL, i.e.
 *            something like "z:\system\fep\TFEP1.FEP". A FEP could
 *            use this parameter to work out the location of its
 *            resource file.
 * @param     "const CCoeFepParameters& aFepParameters"
 *            FEP parameters. These should simply bepassed to
 *            <code>CCoeFep::BaseConstructL()</code>.
 * @returns   "CCoeFep*"
 *            A pointer to the newly created object belonging to a
 *            <code>CCoeFep</code>-derived class.
 */
IMPORT_C CCoeFep* NewFepL(CCoeEnv& aConeEnvironment, const TDesC& aFullFileNameOfDll, const CCoeFepParameters& aFepParameters);

/**
 *
 * Run FEP settings dialog.
 *
 * The function is called by the FEP control-panel plug-in in order to
 * run the settings-dialog of that FEP. It must be exported by every
 * FEP.Note:The FEP may or may not be loaded when this function is
 * called.
 *
 * @since     6.0
 * @param     "CCoeEnv& aConeEnvironment"
 *            A reference to the application's control environment.
 * @param     "const TDesC& aFullFileNameOfDll"
 *            The full file-name of the FEP's top-level DLL, i.e.
 *            something like "z:\system\fep\TFEP1.FEP".
 */
IMPORT_C void SynchronouslyExecuteSettingsDialogL(CCoeEnv& aConeEnvironment, const TDesC& aFullFileNameOfDll);
IMPORT_C void Reserved_1();
IMPORT_C void Reserved_2();
IMPORT_C void Reserved_3();
IMPORT_C void Reserved_4();
IMPORT_C void Reserved_5();
IMPORT_C void Reserved_6();
IMPORT_C void Reserved_7();
IMPORT_C void Reserved_8();

#endif

