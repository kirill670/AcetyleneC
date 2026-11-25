/**
* ==============================================================================
*  Name        : uiresourceutils.h
*  Part of     : Utilities
*  Interface   : Utilities API
*  Description : Resource utilities
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


#ifndef UIRESOURCEUTILS_H
#define UIRESOURCEUTILS_H

// INCLUDES
#include <E32STD.H>

// FORWARD DECLARATIONS
class CCoeEnv;
class RResourceFile;

/**
 * The <code>UiResourceUtils</code> class is a static utility class to help
 * loading of resource files. To simplify and centralise the usual searches and
 * loading of resource files performed by many components.
 *
 * @lib uiutils.lib
 * @since [what]
 */
class UiResourceUtils
    {
    public:

       /**
        * Loads the most relevant language resource file. Note that the drive
        * is determined by the caller's Dll filename and the path is the system
        * data directory.
        *
        * @param aCoeEnv Cone environment
        * @param aResourceLeafName Leaf name of the original resource file (may
        *                          have drive and folders in it, but these are
        *                          ignored and it must be a parseable path)
        * @return the success of the loading
        * @remarks
        * @see
        */
        inline TInt LoadSystemResourceFileL(CCoeEnv& aCoeEnv, const TDesC& aResourceLeafName);
        
       /**
        * Loads the most relevant language resource file. Note that the drive
        * is determined by the caller's Dll filename.
        *
        * @param aCoeEnv Cone environment
        * @param aOriginalResourceLeafName Leaf name of the original resource
        *                                  file (may have drive and folders in
        *                                  it, but these are ignored and it
        *                                  must be a parseable path)
        * @param aOriginalResourcePath Path of the resource file (may have
        *                              drive and leaf name in it, but these are
        *                              ignored and it must be a parseable path)
        * @return the success of the loading
        * @remarks
        * @see
        */
        inline TInt LoadResourceFileL(CCoeEnv& aCoeEnv, const TDesC& aOriginalResourceLeafName, const TDesC& aOriginalResourcePath);    

       /**
        * Loads the most relevant language resource file.
        *
        * @param aCoeEnv Cone environment
        * @param aDrive Drive path (may have folders in it, but must be a
        *               parseable path)
        * @param aOriginalResourceLeafName Leaf name of the original resource
        *                                  file (may have drive and folders in
        *                                  it, but these are ignored and it
        *                                  must be a parseable path)
        * @param aOriginalResourcePath Path of the resource file (may have
        *                              drive and leaf name in it, but these are
        *                              ignored and it must be a parseable path)
        * @return the success of the loading
        * @remarks
        * @see
        */
        IMPORT_C static TInt LoadResourceFileL(CCoeEnv& aCoeEnv, const TDesC& aDrive, const TDesC& aOriginalResourceLeafName, const TDesC& aOriginalResourcePath);

       /**
        * Gets the name of the resource file.
        *
        * @param aFs File system
        * @param aDrive Drive letter
        * @param aOriginalResourceLeafName Leaf name of the original resource
        *                                  file (may have drive and folders in
        *                                  it, but these are ignored and it
        *                                  must be a parseable path)
        * @param aOriginalResourcePath Path of the resource file (may have
        *                              drive and leaf name in it, but these are
        *                              ignored and it must be a parseable path)
        * @param aResourceFileNameAndPath Will be filled with the resource
        *                                 filename and path
        * @remarks
        * @see
        */
        IMPORT_C static void GetResourceFileName(RFs& aFs, const TDesC& aDrive, const TDesC& aOriginalResourceLeafName, const TDesC& aOriginalResourcePath, TFileName& aResourceFileNameAndPath);

       /**
        * Read in a resource from a file without using the
        * <code>CCoeEnv</code>.
        *
        * @param aFile A Resource File which must have already been opened
        * @param aResourceId The ID of the required resource
        * @param aResString The resource string is placed in this descriptor
        * @return result of resource read
        * @remarks
        * @see
        */
        IMPORT_C static TInt GetDesCResourceWithoutCoeEnv(RResourceFile& aFile, const TUint32 aResourceId, TDes& aResString);
    };

#include <UiResourceUtils.inl>

#endif  // UIRESOURCEUTILS_H

// End of File
