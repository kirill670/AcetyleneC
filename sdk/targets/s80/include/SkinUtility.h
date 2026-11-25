/*
* ==============================================================================
*  Name        : skinutility.h
*  Part of     : SKINLOADER
*  Interface   : Skin API
*  Description : Skin Utility class.
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


#ifndef SKINUTILITY_H
#define SKINUTILITY_H

// INCLUDES
#include <e32std.h>
#include <gdi.h>

// FORWARD DECLARATIONS
class CFbsBitmap;

/**
*  
*  This class has methods for obtaining a mask from a bitmap with a specific 
*  background (masking) color, and for shifting the hue, saturation, and 
*  luminosity of a bitmap.
*
*  @lib skinloader.lib
*  @since Series90 1.0
*/
class SkinUtility
    {
    public:

        /**
        * Creates a black and white mask from the magenta areas or any color 
        * indicated by <code>aMaskColor</code> of <code>aSource</code>.
        *
        * @param aSource The source bitmap
        * @param aMaskColor The masking color (usually magenta)
        * @param aPositive Set to <code>EFalse</code> to create an inverted mask
        * @return the resulting mask
        * @remarks Using magenta as a bitmap mask removes the need to have 
        *          another bitmap file, that is, a bitmap mask file. Overlaying 
        *          the source bitmap with magenta produces a transparent 
        *          background. If <code>aPositive</code> is true, the pixels 
        *          representing the color specified by <code>aMaskColor</code>
        *          are represented using <code>1</code>. Otherwise the pixels 
        *          are represented using <code>0</code>
        * @see 

        */
        IMPORT_C static CFbsBitmap* ColorKeyMaskL(const CFbsBitmap& aSource, 
                                                  TRgb aMaskColor, 
                                                  bool aPositive);

        /**
        * Shifts the hue, saturation, and luminosity of the specified bitmap.
        *
        * @param aSource The source bitmap
        * @param aHue The amount to shift the hue by. This may be positive or 
        *        negative
        * @param aSaturation The amount to shift the saturation by. This may be
        *        positive or negative
        * @param aLuminosity The amount to shift the luminosity by. This may be
        *        positive or negative
        * @return the resulting bitmap
        * @remarks
        * @see
        */
        static CFbsBitmap* ShiftHslL(const CFbsBitmap& aSource,
									const TRgb& aMask,
									const TRgb& aRegion,
                                     TInt aHue, 
                                     TInt aSaturation, 
                                     TInt aLuminosity);
    };


#endif  // SKINUTILITY_H

// End of File
