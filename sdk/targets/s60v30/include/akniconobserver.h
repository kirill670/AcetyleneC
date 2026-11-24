/*
* ==============================================================================
*  Name        : AknIconObserver.h
*  Part of     : AknIcon
*  Interface   : AknIcon
*  Description : CFbsBitmap change observer
*
*  Version     : 1
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
#ifndef AKN_ICON_OBSERVER_H
#define AKN_ICON_OBSERVER_H

// INCLUDES

// CONSTANTS

// FORWARD DECLARATIONS
class CFbsBitmap;

// FUNCTION PROTOTYPES


// CLASS DECLARATION

/**
* MAknIconObserver.
*/
class MAknIconObserver
    {
public:
    virtual void BitmapChanged(CFbsBitmap *aBitmap)=0;
    };

class MAknIconChangeObserver
    {
public:
    virtual void BitmapChanged()=0;
    };
    
#endif // AKN_ICON_OBSERVER_H

// End of File
