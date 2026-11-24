/*
* ==============================================================================
*  Name        : SysUtil.h
*  Part of     : SysUtil / SysUtil
*  Interface   :
*  Description : This module offers API for applications to miscellaneous
*                   system utils:
*                   - Get SW version information
*                   - Get Language package version information
*  Version     :
*
*  Copyright (c) 2000 - 2004 Nokia Corporation.
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

#ifndef SYSUTIL_H
#define SYSUTIL_H

// INCLUDES
#include <e32base.h>

// CONSTANTS
// Helper constant to allocate buffers for
// GetSWVersion, GetLangSWVersion, GetLangVersion
// The value is  bigger than really needed for future use.
const TInt KSysUtilVersionTextLength = 64;

// FORWARD DECLARATIONS
class RFs;

// CLASS DECLARATION
/**
*  SysUtil Interface.
*  This class offers various utility methods for applications.
*/
class SysUtil
    {

    public: // New functions

        /**
        * Returns Software version string.
        * @param aVersion The returned version string. The size
        *       of the buffer should be KSysUtilVersionTextLength.
        * @return Symbian OS standard error code.
        */
        IMPORT_C static TInt GetSWVersion(TDes& aValue);

        /**
        * Returns SW version with which the currently installed
        * Language package is compatible with.
        * The returned version has the same syntax SW
        * version (see GetSWVersion).
        * @param aVersion The returned version string. The size
        *       of the buffer should be KSysUtilVersionTextLength.
        * @return Symbian OS standard error code.
        */
        IMPORT_C static TInt GetLangSWVersion(TDes& aValue);

        /**
        * Returns version of the currently installed Language package.
        * The returned version has the following syntax:
        *   xxx
        * @param aVersion The returned version string. The size
        *       of the buffer should be KSysUtilVersionTextLength.
        * @return Symbian OS standard error code.
        */
        IMPORT_C static TInt GetLangVersion(TDes& aValue);

        /**
        * Checks if the free FFS (internal Flash File System) storage
        * space is or will fall below Critical Level (CL).
        * The CL and FFS drive letter is defined by this module.
        * @param aFs File server session.
        *        Must be given if available in the caller,
        *        e.g. from EIKON environment.
        *        If NULL this method will create a temporary session for
        *        a check, but then the check is more expensive.
        * @param aBytesToWrite number of bytes the caller is about to add
        *        FFS, if known by the caller beforehand.
        *        The default value 0 checks if the current
        *        space is already below the CL.
        * @return ETrue if storage space would go below CL after adding
        *         aBytes more data, EFalse otherwise.
        *         Leaves on error.
        */
        IMPORT_C static TBool FFSSpaceBelowCriticalLevelL(
            RFs* aFs, TInt aBytesToWrite = 0);


        /**
        * Checks if the free MMC (Multi Media Card)
        * space is or will fall below Critical Level (CL).
        * The CL and MMC drive letter is defined by this module.
        * @param aFs File server session.
        *        Must be given if available in the caller,
        *        e.g. from EIKON environment.
        *        If NULL this method will create a temporary session for
        *        a check, but then the check is more expensive.
        * @param aBytesToWrite number of bytes the caller is about to add
        *        MMC, if known by the caller beforehand.
        *        The default value 0 checks if the current
        *        space is already below the CL.
        * @return Returns ETrue if storage space would go
        *         below CL after adding aBytesToWrite more data,
        *         EFalse otherwise.
        *         If system has no MMC drive support, return EFalse.
        *         Leaves on error (for example drive contains no media) with
        *         one of system-wide error codes.
        */
        IMPORT_C static TBool MMCSpaceBelowCriticalLevelL(
            RFs* aFs, TInt aBytesToWrite = 0);

        /**
        * Generic method to check if free drive storage
        * space is or will fall below Critical Level (CL).
        * The CL per drive is defined by this module.
        * @param aFs File server session.
        *        Must be given if available in the caller,
        *        e.g. from EIKON environment.
        *        If NULL this method will create a temporary session for
        *        a check, but then the check is more expensive.
        * @param aBytesToWrite number of bytes the caller is about to add
        *        FFS.The value 0 checks if the current
        *        space is already below the CL.
        * @param aDrive number of the drive to be checked.
        *        (see TDriveNumber of f32file.h)
        * @return ETrue if storage space would go below CL after adding
        *         aBytesToWrite more data, EFalse otherwise.
        *         Leaves on error with one of system-wide error code.
        *         e.g. KErrNotReady if drive contais no media.
        */
        IMPORT_C static TBool DiskSpaceBelowCriticalLevelL(
            RFs* aFs, TInt aBytesToWrite, TInt aDrive);

    };

#endif
