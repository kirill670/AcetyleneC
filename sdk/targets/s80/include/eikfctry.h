/*
* ==============================================================================
*  Name        : eikfctry.h
*  Part of     : UIKON
*  Interface   : Control API
*  Description : Abstract control factory.
*  Version     : 1.0
*
*  Copyright (c) 2002 Nokia Corporation.
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

#ifndef EIKFCTRY_H
#define EIKFCTRY_H

// INCLUDES
#include <e32def.h>

// FORWARD DECLARATIONS
class CCoeControl;

// CONSTANTS
/**
 * [what]
 * @publishedPartner
 * @released
 */
enum
    {
    /** [what] */
    EEikControlHasEars=0x01,
    /** [what] */
    EEikControlIsNonFocusing=0x02,
    /** [what] */
    EEikControlHasExtraAscent=0x04
    };

/**
 * [what] 
 * @publishedAll
 * @released
 */
struct SEikControlInfo
    {
    /** [what] */
    CCoeControl* iControl;
    /** [what] */
    TInt iTrailerTextId;
    /** [what] */
    TInt iFlags;
    };

/** 
 * The <code>EikControlFactory</code> class is an abstract factory that creates 
 * controls by type. The class provides a unified way to create controls 
 * according to the specified control integer ID. 
 *
 * @publishedAll 
 * @released 
 * @lib [what]
 * @since
 */
class EikControlFactory

    {
    public:

   /**
    * Creates the specified type of control by going through the dynamically 
    * loaded DLLs Control Factories until one is found that successfully 
    * creates the desired control.
    *
    * @param aControlType The ID of the required type of control
    * @return the newly created control
    * @remarks
    * @see
    */
    IMPORT_C static SEikControlInfo CreateByTypeL(TInt aControlType);
    };

#endif  // EIKFCTRY_H

// End of File
