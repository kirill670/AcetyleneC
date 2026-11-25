/*
* =============================================================================
*  Name        : eikvcurs.h
*  Part of     : UIKON
*  Interface   : Environment API
*  Description : Virtual cursor
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


#ifndef EIKVCURS_H
#define EIKVCURS_H

//** INCLUDES *
#include <e32std.h>


/** 
 * The <code>TEikVirtualCursor</code> provides support for the 
 * virtual cursor's state within an application. Support for the virtual cursor
 * is required for devices without a touch screen. 
 * There is one instance of this object per <code>CEikonEnv</code> object. 
 *
 * 
 * @lib
 * @since
 * @publishedAll
 * @released
 */
class TEikVirtualCursor
    {
public:
    /** 
     * The enumeration <code>TState</code> specifies the virtual cursor's state. 
     * The state may be on, off, or suspended. The suspended state is for  
     * applications to temporarily disable the cursor, but not 
     * to switch it off completely. For example, an editor control, which 
     * when focused needs to capture arrow keys, would disable the virtual 
     * cursor when it gains focus and enable it when unfocused. 
     */
    enum TState
        {
        /** sets the virtual cursor off */
        EOff=0,
        /** sets the virtual cursor on */
        EOn,
        /** sets the virtual cursor as suspended */
        ESuspended
        };

public:
    /**
     * The default object constructor.
     */
    TEikVirtualCursor();

private: //** Prevent passing by value *
    inline TEikVirtualCursor(const TEikVirtualCursor&);

public:
    /**
     * Sets the virtual cursor's state. The suspended state is for
     * use by clients that wish to temporarily disable the cursor
     * but not to switch it off completely.
     *
     * @param aState The virtual cursor's required state
     * @param aEnv The environment in which the virtual cursor exists
     * @remarks
     * @see
     */
    IMPORT_C void SetCursorStateL(TState aState, CCoeEnv& aEnv);

    /**
     * Gets the virtual cursor's state.
     *
     * @param aEnv The environment in which the virtual cursor exists
     * @return the virtual cursor's state
     * @remarks
     * @see 
     */
    IMPORT_C TState CursorState(CCoeEnv& aEnv);

public: //** But not exported *
    /**
     * Handles changes to the cursor visibility when an application 
     * switches to the foreground. 
     *
     * @internal
     * @param aEnv The environment in which the virtual cursor exists
     * @remarks
     * @see
     */
    void HandleAppToForeground(CCoeEnv& aEnv);

private:
    void SwitchOffEmulationAndBitmap(CCoeEnv& aEnv);
    void SwitchOnEmulationAndBitmap(CCoeEnv& aEnv);

private:
    TState iState;
    };


//** Inlines *

/** Constructor.
 *
 * Sets the cursor's state to ESuspended so that the call to switch off the virtual 
 * cursor will succeed when the application starts. Required due to the efficient 
 * implementation of SetCursorState().
 */
inline TEikVirtualCursor::TEikVirtualCursor(const TEikVirtualCursor&)
    {}


#endif //** EIKVCURS_H *

//** End of File *
