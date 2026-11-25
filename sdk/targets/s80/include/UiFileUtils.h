/*
* ==============================================================================
*  Name        : uifileutils.h
*  Part of     : Utilities
*  Interface   : Utilities API
*  Description : File utilities
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

#ifndef __UIFILEUTILS_H__
#define __UIFILEUTILS_H__

// INCLUDES
#include <e32std.H>
#include <f32file.H>

/**
*  A static utility class to help File access
*  ?other_description_lines
*
*  @lib uiutils.lib
*  @since ?Series90_version
*/
class UiFileUtils
	{
public:
	enum TDriveType
		{
		EROMDrive,
		ERAMDrive,
		EPrimaryExternalDrive
		};


		/**
		* Gets the drive name
		* @since ?Series90_version
		* @param aDrive The drive letter
		* @param aName Upon return, the name of the drive
		* @return void
		* <BR><B>Type of return value:</B> void
		*/
	IMPORT_C static void GetDriveName(TDriveType aDrive, TDes& aName);

		/**
		* Gets the drive name
		* @since ?Series90_version
		* @param aDrive The drive letter
		* @param aName Upon return, the name of the drive
		* @param aShowFullName If ETrue, add drive volume name at the end of aDrive
		* descriptor.
		* @return ETrue if given aDrive name is a root directory (i.e. like 'C:\')
		* and stores device specific drive name into aDriveName parameter. Otherwise
		* returns EFalse.
		* <BR><B>Type of return value:</B> TBool
		*/
	IMPORT_C static TBool DriveName(const TDesC& aDrive, TDes& aDriveName, 
									TBool aShowFullName=EFalse);

		/**
		* Gets the localised name for a default folder
		* @since ?Series90_version
		* @param aPath
		* @param aName Upon return, the name of the folder, or no change.
		* @return ETrue if aName contains a localised version of the path, EFalse
		* otherwise.
		* <BR><B>Type of return value:</B> TBool
		*/
	IMPORT_C static void GetFolderNameL(const TDesC& aPath, TDes& aName);

	};


#endif // __UIFILEUTILS_H__
