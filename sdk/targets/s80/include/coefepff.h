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
 * This FEP factory method must be exported by every FEP. The method is called 
 * by the UI Control Framework when it loads the FEP. It returns a fully 
 * constructed object of a <code>CCoeFep</code>-derived class, and passes 
 * ownership of that object to the caller. The method can leave with any of 
 * the system-wide error codes, for instance KErrNoMemory.
 * 
 * @publishedAll
 * @released
 * @param aConeEnvironment A reference to the application's control environment
 * @param aFullFileNameOfDll The full filename of the FEP's top-level DLL, 
 *                           that is, something like "z:\system\fep\TFEP1.FEP". 
 *                           A FEP could use this parameter to work out the 
 *                           location of its resource file
 * @param aFepParameters The FEP parameters. These should simply be passed to 
 *                       <code>CCoeFep::BaseConstructL()</code>
 * @return a pointer to the newly created object belonging to a 
 *         <code>CCoeFep</code>-derived class
 * @remarks
 * @see
 */
IMPORT_C CCoeFep* NewFepL(CCoeEnv& aConeEnvironment, const TDesC& aFullFileNameOfDll, const CCoeFepParameters& aFepParameters);

/** 
 * Runs the FEP settings dialog. The method is called by the FEPs control panel 
 * plug-in in order to run the settings dialog for the FEP. It must be exported 
 * by every FEP. The method can leave with any of the system-wide error codes,
 * for instance <code>KErrNoMemory</code>. <b>Note</b>: the FEP may or may not 
 * be loaded when this method is called.
 *
 * @publishedAll
 * @released
 * @param aConeEnvironment A reference to the application's control environment
 * @param aFullFileNameOfDll The full filename of the FEP's top-level DLL, 
 *                           that is, something like "z:\system\fep\TFEP1.FEP". 
 *                           A FEP could use this parameter to work out the 
 *                           location of its resource file
 * @remarks
 * @see
 */
IMPORT_C void SynchronouslyExecuteSettingsDialogL(CCoeEnv& aConeEnvironment, const TDesC& aFullFileNameOfDll);
/** [what] */
IMPORT_C void Reserved_1();
/** [what] */
IMPORT_C void Reserved_2();
/** [what] */
IMPORT_C void Reserved_3();
/** [what] */
IMPORT_C void Reserved_4();
/** [what] */
IMPORT_C void Reserved_5();
/** [what] */
IMPORT_C void Reserved_6();
/** [what] */
IMPORT_C void Reserved_7();
/** [what] */
IMPORT_C void Reserved_8();

#endif

