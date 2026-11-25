/*
* ==============================================================================
*  Name        : eikrutil.h
*  Part of     : UIKON
*  Interface   : Resource Utility API
*  Description : Resource utility functions.
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


#ifndef EIKRUTIL_H
#define EIKRUTIL_H

// INCLUDES
#include <e32std.h>
#include <gulutil.h>

// FORWARD DECLARATIONS
class CFbsFont;
class CEikonEnv;
class CWsScreenDevice;
class TResourceReader;

/**
 * This class provides utilities for reading standard resources, for example to 
 * create screen fonts and read 8-bit, 16-bit, and 32-bit signed integers from 
 * resources.
 * 
 * @lib eikcore.lib
 * @since 6.0
 */
class EikResourceUtils
    {
    public:

        /**
         * Creates a screen font for the specified environment by reading a font 
         * UID and font flags from the specified resource. This method returns a 
         * pointer to the font and transfers ownership.
         *
         * @param aResourceReader The resource reader for the font resources
         * @param aScreenDevice The target device for the screen font
         * @return the pointer to the created screen font. This is now owned by 
         *         the calling class
         * @remarks
         * @see
         */
        inline static CFbsFont* CreateScreenFontL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice);

        /**
         * Creates a screen font for the specified environment by reading a font
         * UID and font flags from the specified resource. This method returns a 
         * pointer to the font and transfers ownership.
         *
         * @param aResourceId The <code>TInt</code> ID of the resource for the 
         *                    font
         * @param aEnv The target Eikon environment for which the screen font 
         *             will be created
         * @return the pointer to the created screen font. This is now owned by 
         *         the calling class
         * @remarks
         * @see
         */
        IMPORT_C static CFbsFont* CreateScreenFontL(TInt aResourceId,CEikonEnv* aEnv=NULL);

        /**
         * Gets the 8-bit signed integer that is held in a specified resource 
         * location.
         *
         * @param aResourceId The ID that indicates the 
         *                    location in the resource to be read 
         * @param aEnv The Eikon environment
         * @return the 8-bit integer that has been read from the resource file
         * @remarks
         * @see
         */
        inline static TInt8 ReadTInt8L(TInt aResourceId,CEikonEnv* aEnv=NULL);

        /**
         * Gets the 16-bit signed integer held in a specified resource location.
         *
         * @param aResourceId The ID that indicates the 
         *                    location in the resource to be read
         * @param aEnv The Eikon environment
         * @return the 16-bit integer that has been read from the resource file
         * @remarks
         * @see
         */
        inline static TInt16 ReadTInt16L(TInt aResourceId,CEikonEnv* aEnv=NULL);

        /**
         * Gets the 32-bit signed integer held in a specified resource location.
         *
         * @param aResourceId The <code>TInt</code> ID that indicates the 
         *                    location in the resource to be read
         * @param aEnv The Eikon environment
         * @return the 32-bit integer that has been read from the resource file
         * @remarks
         * @see
         */
        inline static TInt32 ReadTInt32L(TInt aResourceId,CEikonEnv* aEnv=NULL);

        /**
         * Creates an array of colors from a resource.
         *
         * @param aResourceId The ID of the resource from 
         *                    which to read the colors
         * @param aEnv The Eikon environment in which the control colors are
         *             to be created. This is optional. If it is not defined 
         *             then <code>CEikonEnv::Static()</code> is used
         * @return the pointer to the array of control colors.  This is now 
         *         owned by the calling class
         * @remarks
         * @see
         */
        IMPORT_C static CColorArray* CreateColorArrayL(TInt aResourceId,CEikonEnv* aEnv=NULL);

        /**
         * Creates an array of control colors from a resource definition, 
         * returns it, and places it on the cleanup stack.
         *
         * @param aResourceId The ID of the resource from 
         *                    which to create the array of control colors
         * @param aEnv The Eikon environment in which the control colors are to 
         *             be created
         * @return a pointer to the array of control colors. This is now owned 
         *         by the calling class and must be deleted when finished with
         * @remarks
         * @see
         */
        IMPORT_C static CColorArray* CreateColorArrayLC(TInt aResourceId,CEikonEnv* aEnv=NULL);
    //
    private:
        enum TResourceTypeInt { EResourceInt8,EResourceInt16,EResourceInt32 };
    private:
        IMPORT_C static TInt32 ReadResourceIntL(TInt aResourceId,CEikonEnv* aEnv,TResourceTypeInt aSize);
    };

inline CFbsFont* EikResourceUtils::CreateScreenFontL(TResourceReader& aResourceReader,CWsScreenDevice& aScreenDevice)
/** Create a screen font from resource.

Creates a font for the specified screen device by reading a font UID and font 
flags from the given position in a resource. Returns a pointer to the font 
and transfers ownership.

@param aResourceReader The resource reader to use to read the font. 
@param aScreenDevice The screen device for which the font will be created. 
@return Screen font object. */
    {
        return(ResourceUtils::CreateScreenFontL(aResourceReader,aScreenDevice));
    }

inline TInt8 EikResourceUtils::ReadTInt8L(TInt aResourceId,CEikonEnv* aEnv)
/** Gets the 8-bit signed integer held in a specified resource location.

@param aResourceId The location in the resource to be read. 
@param aEnv The UI environment. 
@return The eight bits that follow the specified location in the resource. */
    {
        return((TInt8)ReadResourceIntL(aResourceId,aEnv,EResourceInt8));
    }

inline TInt16 EikResourceUtils::ReadTInt16L(TInt aResourceId,CEikonEnv* aEnv)
/** Gets the 16-bit signed integer held in a specified resource location.

@param aResourceId The location in the resource to be read. 
@param aEnv The UI environment. 
@return The 16 bits that follow the specified location in the resource. */
    {
        return((TInt16)ReadResourceIntL(aResourceId,aEnv,EResourceInt16));
    }

inline TInt32 EikResourceUtils::ReadTInt32L(TInt aResourceId,CEikonEnv* aEnv)
/** Gets the 32-bit signed integer held in a specified resource location.

@param aResourceId The location in the resource to be read. 
@param aEnv The UI environment. 
@return The 32 bits that follow the specified location in the resource. */
    {
        return((TInt32)ReadResourceIntL(aResourceId,aEnv,EResourceInt32));
    }


#endif  // EIKRUTIL_H

// End of File
