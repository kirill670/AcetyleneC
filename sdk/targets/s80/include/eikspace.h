/*
* ==============================================================================
*  Name        : eikspace.h
*  Part of     : ckon
*  Interface   : Spacer API
*  Description : Spacer control
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


#ifndef EIKSPACE_H
#define EIKSPACE_H

// INCLUDES
#include <coecntrl.h>
#include <gdi.h>

// FORWARD DECLARATIONS
class TResourceReader;

/**
*  The <code>CEikSpacer</code> class provides the spacer control.
*  A spacer can be used to create empty space between controls, for example,
*  in a Toolbar. The spacer can be either solid color or transparent.
* 
*  @lib eikctl.lib
*  @since
*/
class CEikSpacer : public CCoeControl
    {
public:
        
    /**
    * The default object constructor.
    */
    IMPORT_C CEikSpacer();
        
    /**
    * A object constructor that sets the width, height, and color (or 
    * transparency) of the spacer control.
    *
    * @param aWidth The width of the spacer control, in pixels
    * @param aHeight The height of the spacer control, in pixels
    * @param aColor The color of the spacer control, in pixels
    * @remarks
    * @see
    */
    IMPORT_C CEikSpacer(TInt aWidth,TInt aHeight,TRgb aColor);
        
    /**
    * The object destructor.
    */
    IMPORT_C ~CEikSpacer();
        
    /**
    * Sets the width of the spacer.
    *
    * @param aWidth The new width, in pixels
    * @remarks 
    * @see
    */
    IMPORT_C void SetWidth(TInt aWidth);
        
    /**
    * Sets the height of the spacer.
    *
    * @param aHeight The new height, in pixels
    * @remarks When a spacer control is used in a Toolbar, the height of each 
    *          spacer is automatically aligned to the height of the Toolbar
    * @see
    */
    IMPORT_C void SetHeight(TInt aHeight);
        
    /**
    * Sets the background color of the spacer.
    *
    * @param aColor The new color
    * @remarks
    * @see
    */
    IMPORT_C void SetColor(TRgb aColor);
       
    /**
    * Sets the brush to <code>NULL</code> to pick up the correct background 
    * colors.
    *
    * @param aClear <code>ETrue</code> to set to clear; <code>EFalse</code>
    *               to use a background color
    * @remarks
    * @see
    */
    IMPORT_C void SetClear(TBool aClear);
private: // from CCoeControl
    void ConstructFromResourceL(TResourceReader& aReader);
    void Draw(const TRect& aRect) const;
    TBool IsToolbandSpacer() const;
private:
    TRgb iColor;
    TBool iClear;
    };




#endif  // EIKSPACE_H

// End of File
