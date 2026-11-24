/*
* ==============================================================================
*  Name        : PathInfo.h
*  Part of     : PlatformConfig / PathInfo
*  Interface   : PathInfo API
*  Description : Holds information of system paths.
*                These utility methods should be used instead of hard coded
*                path names.
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


#ifndef PATH_INFO_H
#define PATH_INFO_H

//  INCLUDES
#include <e32std.h>

// CLASS DECLARATION
/**
*  Holds information of system paths.
*  All paths have the trailing backslash included.
*
*  @lib PlatformEnv.dll
*  @since 2.0
*
*  Code example:
*
*  -----------------------------------------------------------------------------
*  #include <PathInfo.h>
*
*  TFileName path = PathInfo::PhoneMemoryRootPath();
*  path.Append( PathInfo::GamesPath() );
*
*  // 'path' now contains games path in C: drive
*  -----------------------------------------------------------------------------
*/
class PathInfo
    {
    public: // New functions

        /**
        * Returns root path in ROM
        * @since 2.0
        */
        IMPORT_C static const TDesC& RomRootPath();
        /**
        * Returns root path in Phone Memory
        * @since 2.0
        */
        IMPORT_C static const TDesC& PhoneMemoryRootPath();
        /**
        * Returns root path in Memory Card
        * @since 2.0
        */
        IMPORT_C static const TDesC& MemoryCardRootPath();


        /**
        * Returns games path, to be appended in root path
        * @since 2.0
        */
        IMPORT_C static const TDesC& GamesPath();
        /**
        * Returns installs path, to be appended in root path
        * @since 2.0
        */
        IMPORT_C static const TDesC& InstallsPath();
        /**
        * Returns others path, to be appended in root path
        * @since 2.0
        */
        IMPORT_C static const TDesC& OthersPath();
        /**
        * Returns videos path, to be appended in root path
        * @since 2.0
        */
        IMPORT_C static const TDesC& VideosPath();
        /**
        * Returns images path, to be appended in root path
        * @since 2.0
        */
        IMPORT_C static const TDesC& ImagesPath();

        
        /**
        * Deprecated, to be removed! Use GmsPicturesPath() instead!
        */
        IMPORT_C static const TDesC& PicturesPath();        

        
        /**
        * Returns GMS pictures path, to be appended in root path
        * @since 2.0
        */
        IMPORT_C static const TDesC& GmsPicturesPath();
        /**
        * Returns MMS background images path, to be appended in root path
        * @since 2.0
        */
        IMPORT_C static const TDesC& MmsBackgroundImagesPath();
        /**
        * Returns presence logos path, to be appended in root path
        * @since 2.0
        */
        IMPORT_C static const TDesC& PresenceLogosPath();
        /**
        * Returns sounds path, to be appended in root path
        * @since 2.0
        */
        IMPORT_C static const TDesC& SoundsPath();
        /**
        * Returns digital sounds path, to be appended in root path
        * @since 2.0
        */
        IMPORT_C static const TDesC& DigitalSoundsPath();
        /**
        * Returns simple sounds path, to be appended in root path
        * @since 2.0
        */
        IMPORT_C static const TDesC& SimpleSoundsPath();

        // ---------------------------------------------------------------------
        // paths that are not necessarily under root directories
        // ---------------------------------------------------------------------

        /**
        * Returns thumbnail images path. It exists under the same directory
        * where the corresponding image is.
        * Do not try to append this to a root directory.
        */
        IMPORT_C static const TDesC& ImagesThumbnailPath();

        /**
        * Returns full path of the contacts folder in memory card.
        * It also contains the drive letter.
        * Do not try to append this to any root directory.
        * @since 2.5
        */
        IMPORT_C static const TDesC& MemoryCardContactsPath();

    private:

        /**
        * C++ default constructor.
        */
        PathInfo();
    };

// PATH_INFO_H   
#endif
            
// End of File
