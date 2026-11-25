/*
* ==============================================================================
*  Name        : eikmpan.h
*  Part of     : CKON / EIKMISC
*  Interface   : Panics
*  Description : Miscellaneous panic
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


#ifndef EIKMPAN_H
#define EIKMPAN_H

/** The enumeration <code>TEikMiscPanic</code> contains panics for Buttons */
enum TEikMiscPanic
    {
    /** the window Button ID is not unique */
    EEikPanicDuplicateWindowButtonId
    };


        /**
        * Generates a panic.
        * 
        * @param aPanic A panic of type <code>TEikMiscPanic</code>
        * @remarks
        * @see
        */
        GLREF_C void Panic(TEikMiscPanic aPanic);


#endif  // EIKMPAN_H

// End of File
