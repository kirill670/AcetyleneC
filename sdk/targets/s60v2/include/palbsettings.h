/*
* ============================================================================
*  Name     : PAlbSettings.h from PhotoAlbum Engine
*  Part of  : PhotoAlbum
*
*  Description: @deprecated
*
*  Version  :
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing,  adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

// INCLUDE FILES

#ifndef PALBSETTINGS_H
#define PALBSETTINGS_H

#include <e32std.h>

/**
 * @deprecated
 * This class encapsulates the usage of PathInfo for Photo Album folders.
 *
 * RestoreL() is provided to set up the default settings and to create all the
 * needed paths to the filesystem.
 */
class TPAlbSettings
    {

    public:  // Constructors and destructor
    enum TImageFormatSetting
        {
        EFormatJPEG = 0,    // default
        EFormatUPF
        };

    public:
    /**
     * @deprecated
     * Reset Photo Album settings to default
     * Imageformat defaults to JPEG
     */
    IMPORT_C static void RestoreL();

    /**
     * @deprecated
     * Get the current setting for image sending format.
     * NOTE: Only JPEG (EFormatJPEG) is supported
     * @return EFormatJPEG
     */
    IMPORT_C static TImageFormatSetting ImageSendingFormatL();

    /**
     * @deprecated
     * NOTE! This method has no functionality
     * Set the image sending format setting.
     * @param aFormat Either EFormatJPEG or EFormatUPF
     */
    IMPORT_C static void SetImageSendingFormatL( TImageFormatSetting& aFormat );

    /**
     * @deprecated
     * This method will return the image folder path as set in the Shared
     * Data module
     * @return heap descriptor pointer containing the full path.
     * NOTE! CleanupStack usage!!!
     */
    IMPORT_C static HBufC* RootImageFolderLC();

    /**
     * @deprecated
     * This method will return the image folder path as set in the Shared
     * Data module. Will result a full path name, ie: "c:\images\Cities\"
     *
     * @param aPathend a foldername (ie. "Cities") without the ending backslash
     * @return heap descriptor pointer containing the full path.
     * NOTE! CleanupStack usage!!!
     */
    IMPORT_C static HBufC* RootImageFolderWithSubFolderLC( const TDesC& aPathend );

    /**
     * @deprecated
     * This method will return the thumbnail folder path as set in the Shared
     * Data module
     * @return heap descriptor pointer containing the full path.
     * NOTE! CleanupStack usage!!!
     */
    IMPORT_C static HBufC* RootThumbnailFolderLC();

    /**
     * @deprecated
     * This method will return the picture folder path as set in the Shared
     * Data module
     * @return heap descriptor pointer containing the full path.
     * NOTE! CleanupStack usage!!!
     */
    IMPORT_C static HBufC* PictureFolderLC();
    /**
     * @deprecated
     * This method will return the picture folder name as set in the Shared
     * Data module
     * @return heap descriptor pointer containing the folder name, ie: "Pictures".
     * NOTE! CleanupStack usage!!!
     */
    IMPORT_C static HBufC* PictureFolderNameLC();

    /**
     * @deprecated
     * Ensures that the PhotoAlbum folders are created in the filesystem
     * also ensures that the Shared Data keynames for the folder settings
     * exist.
     * You don't have to call this directly. RestoreL() call this. Also
     * Photo Album engine will call this when the engine is constructed.
     */
    IMPORT_C static void RestoreFoldersL();

    /**
     * @deprecated
     * NOTE! This method has no functionality
     * Sets the default folder for image operations. If the path is on
     * drive c:, only folder c:\nokia\images\ and it's subfolders are
     * accepted. Otherwise the path must be absolute with a drive letter.
     * @param aPath name of the path
     * @return KErrNone if aPath is valid else KErrArgument.
     */
    IMPORT_C static TInt SetDefaultImageFolderL( TDesC& aPath );

    /**
     * @deprecated
     * This method will return the default image folder as set by
     * SetImageFolderL function.
     * NOTE! CleanupStack usage!!!
     */
    IMPORT_C static HBufC* DefaultImageFolderLC();

    /**
     * @deprecated
     * DO NOT USE! Use PictureFolderLC() instead
     * This method will return the default picture folder path that will be
     * written to the SharedData if the key dows not exist when PictureFolderLC
     * is called.
     * @return Reference to the full path.
     */
    IMPORT_C const static TDesC& PictureFolder();

    /**
     * @deprecated
     * This method will return the default picture folder name that will be
     * written to the SharedData if the key does not exist when
     * PictureFolderNameLC is called.
     * @return Reference to the default name "Pictures".
     */
    IMPORT_C const static TDesC& PictureFolderName();

    /**
     * @deprecated
     * This method will return the root image folder of the MMC
     * @return The folder name, ie: "E:\".
     */
    IMPORT_C static HBufC* MMCRootImageFolderLC();

    /**
     * @deprecated
     * DO NOT USE! Use MMCRootImageFolderLC() instead
     * This method will return the root image folder of the MMC
     * @return Reference to the folder name, ie: "E:\".
     */
    IMPORT_C const static TDesC& MMCRootImageFolder();

    };

#endif // PALBSETTINGS_H

// End of file.