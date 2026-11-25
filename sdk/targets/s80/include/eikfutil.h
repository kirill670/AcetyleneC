/*
* ==============================================================================
*  Name        : eikfutil.h
*  Part of     : UIKON
*  Interface   : File Utility API
*  Description : Utility functions for file/drive access.
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


#ifndef EIKFUTIL_H
#define EIKFUTIL_H

// INCLUDES
#include <e32std.h>
#include <f32file.h>
#include <badesca.h>
#include <bautils.h>
#include <eikenv.h>

// FORWARD DECLARATIONS
class CFont;
class CBaflFileSortTable;
class TResourceReader;

/** 
 * The <code>EikFileUtils</code> class provides a set of drive, path, and file 
 * utility functions. This class is essentially a thin layer over the 
 * <code>BaflUtils</code> class.  See bautils.h.
 * 
 * @publishedAll 
 * @released 
 * @lib eikcore.lib
 * @since
 */
class EikFileUtils

    { 
    public:
       /** 
        * Tests whether a path exists.
        * 
        * @param aPath The path to test for. The path must be complete: that is, 
		*              it must have a drive letter and full absolute directory. 
		*              If not, <code>EFalse</code> is returned
        * @remarks <code>EFalse</code> is returned in the following conditions:
		*          If the path does not contain a drive letter and a directory 
        *          If the path contains a filename or filename extension 
		*          If the path is badly formed, for example: 
		*                      if the path contains illegal characters, 
		*                      if a directory name consists of a single or double dot
		*                      if a directory name includes wildcard characters.
		*          For example "g:\\testfolder" and "z:\\te*" would return <code>EFalse</code>
        * @see
        */
        inline static TBool PathExists(const TDesC& aPath);

        /** 
        * Checks if the specified item is a folder.
        *
        * @param aFullName The name to check
        * @param aIsFolder <code>ETrue</code> if <code>aFullName</code> is a 
        *                  folder; <code>EFalse</code> otherwise
        * @return <code>KErrNone</code> if successful; otherwise another of 
        *         the system-wide error codes 
        * @remarks
        * @see
        */
        inline static TInt IsFolder(const TDesC& aFullName, TBool& aIsFolder);

        /** 
        * Tests whether a folder exists.
        *
        * @param aFolderName A path specifying the folder to test for.
        * @return <code>ETrue</code> if the folder specified in
        *         <code>aFolderName</code> exists; <code>EFalse</code> otherwise.
        *         <code>EFalse</code> is also returned if the specified path is 
        *         badly formed
        * @remarks The folder is specified in a path. The path can omit the 
        *          drive letter, in which case the drive letter is taken from 
        *          the session path. If the path contains illegal characters, 
        *          a folder name consists of a single or double dot, or a 
        *          folder name includes wildcard characters, the method 
        *          returns <code>EFalse</code>. A filename can be specified in 
        *          the path, and is ignored. However, if a filename is included 
        *          in the path, its name must not contain any illegal 
        *          characters. This is considered a badly formed path and 
        *          causes the method to return <code>EFalse</code>. If no 
        *          filename is specified, the path should end in a backslash
        * @see
        */
        inline static TBool FolderExists(const TDesC& aFolderName);

        /** 
        * Gets the folder name from a path.
        *
        * @param aFullName A path
        * @return The folder name
        * @remarks A valid full name should have a drive associated with it
		*          "\\" is an escape character used when "\" is required
        *          for example, "a:\\" to "z:\\", "a:" to "z:", or 
        *          "c:\\system\data\file.txt". If there is no drive, this is 
        *          an invalid entry and causes a panic 
        *          <code>EBafPanicBadOpenArg</code>. For example, if the path 
        *          is: "c:\documents\word\mydoc1", then "word" is returned; 
        *          "c:", then "c:" is returned; "c:\\", then "c:\" is returned;
        *          "c:\\mydoc1.txt", then "c:\" is returned
        * @see
        */
        inline static TFileName FolderNameFromFullName(const TDesC& aFullName);

        /** 
        * Gets the drive letter and path from a filename.
        *
        * @param aFullName The drive and path
        * @return the filename. This is in the form: <code>drive-letter:\path\</code>. 
        *         The drive letter is converted to lower case. 
		*         It is always a letter in the range a-z.
        * @remarks
        * @see
        */
        inline static TFileName DriveAndPathFromFullName(const TDesC& aFullName);
       
        /** 
        * Gets the root folder for the specified drive.
        *
        * @param aDriveLetter The drive letter
        * @return The root folder
        * @remarks If <code>aDriveLetter</code> is an alphabet character
        *          (lowercase or uppercase), the <code>TFileName</code> is 
        *          returned, which is the drive letter plus ":\" appended.
        *          If this is not the case, the method will panic with panic 
        *          code <code>EBafPanicBadOpenArg</code>
        * @see
        */
        inline static TFileName RootFolderPath(const TBuf<1> aDriveLetter);
       
        /** 
        * Abbreviates the filename to fit the maximum length of 
		* <code>aAbbreviatedFileName</code>, prefixing it with an ellipsis 
		* (three dots: Unicode character U+2026) if it is truncated.
        *
        * @param aOriginalFileName The original file name
        * @param aAbbreviatedFileName On return, the abbreviated filename
        * @remarks If <code>aOriginalFileName</code> is less than the maximum 
        *          length of <code>aAbbreviatedFileName</code>, the filename 
        *          is simply copied to <code>aAbbreviatedFileName</code>. If 
        *          not, the left-most characters of <code>aOriginalFileName</code>
        *          are copied to <code>aAbbreviatedFileName</code>, up to 
        *          the maximum length minus 1 of <code>aAbbreviatedFileName</code>. 
        *          The first character of <code>aAbbreviatedFileName</code> is 
        *          set to be an ellipsis
        * @see
        */
        inline static void AbbreviateFileName(const TFileName& aOriginalFileName, TDes& aAbbreviatedFileName);

       /**
        * Gets an abbreviated path. This method determines the space that is 
        * available to display <code>aPathName</code> according to the font 
        * size and available screen area. If there is sufficient space,
        * <code>aPathName</code> is returned as <code>TFileName</code>. If 
        * there is not sufficient space, <code>aPathName</code> is abbreviated 
        * to fit the available space, prefixed with an ellipsis. The 
        * abbreviation is returned as <code>TFileName</code>.
        *
        * @param aPathName The full path name
        * @param aFont The font used to display the path
        * @param aMaxWidthInPixels The available display space, in pixels
        * @return the path name. This is <code>aPathName</code> if there
        *         is sufficient space, or otherwise an abbreviation. 
        * @remarks
        * @see
        */
        IMPORT_C static TFileName AbbreviatePath(TDesC& aPathName, const CFont& aFont, TInt aMaxWidthInPixels);

        /** 
        * Tests whether two UID types match. A match is made if each UID in 
        * <code>aMatchUid</code> is either identical to the corresponding one 
        * in <code>aFileUid</code> or is <code>KNullUid</code>.
        *
        * @param aFileUid The UID type to match
        * @param aMatchUid The UID type to match against
        * @return <code>ETrue</code> if the UIDs match; <code>EFalse</code> 
        *         otherwise 
        * @remarks
        * @see
        */
        inline static TBool UidTypeMatches(const TUidType& aFileUid, const TUidType& aMatchUid);

        /** 
        * Checks if a specified filename can be parsed.
        *
        * @param aName The filename to parse
        * @return <code>KErrNone</code> if successful; otherwise another of 
        *         the system-wide error codes 
        * @remarks
        * @see
        */
        inline static TInt Parse(const TDesC& aName);

       /**
        * Checks if a folder name (without drive or path) is valid and returns the full 
		* name of the folder.
        *
        * @param aFolderNameTypedByUser The folder name entered by a user
        * @param aCurrentPath The current path
        * @return <code>aFolderNameTypedByUser</code> appended to <code>aCurrentPath</code>
        * @remarks
        * @see
        */
        IMPORT_C static TFileName ValidateFolderNameTypedByUserL(const TDesC& aFolderNameTypedByUser, const TDesC& aCurrentPath);

        /** 
        * Copies one or more files.
        *
        * @param aSourceFullName The path indicating the file(s) to be copied. 
        *                        Any path components that are not specified 
        *                        here will be taken from the session path
		*                        Wild cards (e.g. *) may be used.
        * @param aTargetFullName The path indicating the folder into which 
        *                        the file(s) are to be copied
		*                        Wildcards may not be used.
        * @param aSwitch Set this to: zero for no overwriting and no recursion; 
        *                <code>CFileMan::EOverWrite</code> (default) to 
        *                overwrite files with the same name; and/or 
        *                <code>CFileMan::ERecurse</code> for recursion. 
		*                Both flags can be used.
        * @return <code>KErrNone</code> if successful; otherwise another of 
        *         the system-wide error codes 
        * @remarks
        * @see <code>CFileMan::Copy()</code> in f32file.h
        */
        inline static TInt CopyFile(const TDesC& aSourceFullName, const TDesC& aTargetFullName, TUint aSwitch = CFileMan::EOverWrite);

        /** 
        * Renames or moves one or more files or directories.
        *
        * @param aOldFullName The path specifying the file(s) to be renamed
		*                     Wildcards (e.g. *) are permitted if target is a folder.
        * @param aNewFullName The path specifying the new name for the files 
        *                     and/or the new folder. Any directories 
        *                     specified in this path that do not exist will be 
        *                     created.  Wildcards are not permitted.
		* @param aSwitch Specify zero for no overwriting, or 
        *                <code>CFileMan::EOverWrite</code> (default) to 
        *                overwrite files with the same name. This method cannot 
        *                operate recursively
        * @return <code>KErrNone</code> if successful; otherwise another of the 
        *         system-wide error codes 
        * @remarks This method can be used to move one or more files by 
        *          specifying different destination and source directories
        * @see <code>CFileMan::Rename()</code>
        */
        inline static TInt RenameFile(const TDesC& aOldFullName, const TDesC& aNewFullName, TUint aSwitch = CFileMan::EOverWrite);

        /** 
        * Deletes one or more files.
        *
        * @param aSourceFullName The path indicating the file(s) to be deleted. 
        *                        This can either be a full path, or a path 
        *                        relative to the session path. Use wildcards 
        *                        to specify more than one file
        * @param aSwitch Specify <code>CFileMan::ERecurse</code> for recursion;
        *                zero (default) for no recursion
        * @return <code>KErrNone</code> if successful; otherwise another of 
        *         the system-wide error codes 
        * @remarks
        * @see <code>CFileMan::Delete()</code> 
        */
        inline static TInt DeleteFile(const TDesC& aSourceFullName, TUint aSwitch=0);

        /** 
        * Checks if a string is a valid folder name. 
        *
        * @param aFullName The string to check
        * @param aIsFolder <code>ETrue</code> if <code>aFullName</code> is a 
        *                  valid folder name; otherwise <code>EFalse</code>
        * @return <code>KErrNone</code> if successful; otherwise another of 
        *         the system-wide error codes (because <code>aFullName</code>
        *         cannot be parsed)
        * @remarks Only checks the syntax; it does not check if the folder exists.
        * @see
        */
        inline static TInt CheckWhetherFullNameRefersToFolder(const TDesC& aFullName, TBool& aIsFolder);

        /** 
        * Gets the folder name if the specified item is a valid folder name, 
        * otherwise gets the filename.
        *
        * @param aFullName The item to parse
        * @param aMostSignificantPart The folder or filename
        * @return <code>KErrNone</code> if successful; otherwise another of 
        *         the system-wide error codes 
        * @remarks
        * @see
        */
        inline static TInt MostSignificantPartOfFullName(const TDesC& aFullName, TFileName& aMostSignificantPart);

        /** 
        * Checks that the specified folder can be opened.
		*
        * @param aFolderName The folder to check
        * @return <code>KErrNone</code> if successful; otherwise another of 
        *         the system-wide error codes 
        * @remarks
        * @see <code>RDir::Open</code> in f32file.h
        */
        inline static TInt CheckFolder(const TDesC& aFolderName);

        /** 
        * Checks if the specified drive is read-only.
        *
        * @param aFullName The filename, including the drive
        * @param aIsReadOnly On return, <code>ETrue</code> if the drive is 
        *                    read-only; otherwise <code>EFalse</code>
        * @return <code>KErrNone</code> if successful; otherwise another of 
        *         the system-wide error codes 
        * @remarks
        * @see
        */
        inline static TInt DiskIsReadOnly(const TDesC& aFullName, TBool& aIsReadOnly);

        /** 
        * Retrieves a list of all drives present on the system. The file 
        * server is interrogated for a list of the drive letters for all 
        * available drives. The drive letter that corresponds to 
        * <code>aDriveNumber</code> is added to the list regardless of whether 
        * it is present or is corrupt. Also, the C: drive and the primary 
        * partitions on removable media slots are placed onto the list, even 
        * if corrupt or not present.
        *
        * @param aFs A connected session with the file server
        * @param aArray On return, contains the drive letters that correspond 
        *               to the available drives. The drive letters are 
        *               uppercase and are in alphabetical order
        * @param aIncludeRom Specify <code>ETrue</code> if the ROM drive 
        *                    should be included in the list; <code>EFalse</code>
        *                    if not
        * @param aDriveNumber The drive to force into the list, for example, 
        *                     the drive in the default path
        * @remarks
        * @see
        */
        inline static void UpdateDiskListL(const RFs& aFs,CDesCArray& aArray,TBool aIncludeRom,TDriveNumber aDriveNumber);

        /** 
        * Removes the system folder from a list of directory entries. 
        *
        * @param aDir The array of directory entries
        * @remarks
        * @see
        */
        inline static void RemoveSystemDirectory(CDir& aDir);

        /** 
        * Tests whether the specified drive corresponds to the primary 
        * partition in a removable media slot.
        *
        * @param aDriveUnit The drive to check
        * @return <code>ETrue</code> if the drive is the primary partition in 
        *         a removable media slot. <code>ETrue</code> is also returned 
        *         if the drive is C:. <code>EFalse</code> is returned otherwise
        * @remarks The method assumes that the D: drive corresponds to the
        *          primary partition on socket 0, and that the E: drive 
        *          corresponds to the primary partition on socket 1 (a socket 
        *          is a slot for removable media). This mapping may not always 
        *          be the case because it is set up in the variant layer of 
        *          the Symbian OS
        * @see
        */
        inline static TBool IsFirstDriveForSocket(TDriveUnit aDriveUnit);

        /** 
        * Sorts files by UID.  A UID comprises of 3 separate UIDs used in
		* combination.  The third UID is used for determining a project
		* identifier, similar to file extensions in DOS.
		* This method is used for customizing how 
        * lists of application files are sorted. The caller supplies a table, 
        * which specifies the order in which files are to be sorted. Files 
        * with a UID3 that is the first UID specified in the table, appear 
        * first. Files with a UID3 that is the second UID specified, appear 
        * next, and so on. Files with a UID3 that is not specified in the 
        * table, and directories, appear at the end of the list, with 
        * directories preceding the files, and with files sorted in 
        * ascending order of UID3. 
        *
        * @param aDir The array of files and directories to sort
        * @param aTable A sort order table containing the UIDs to use in the 
        *               sort
        * @return If successful, <code>KErrNone</code>; otherwise another of the 
        *         system-wide error codes
        * @remarks
        * @see <code>TUid</code> in e32std.h
        */
        inline static TInt SortByTable(CDir& aDir,CBaflFileSortTable* aTable);
    };

inline TBool EikFileUtils::PathExists(const TDesC& aPath)
    {
    return BaflUtils::PathExists(CEikonEnv::Static()->FsSession(),aPath);
    }

inline TInt EikFileUtils::IsFolder(const TDesC& aFullName, TBool& aIsFolder)
    {
    return BaflUtils::IsFolder(CEikonEnv::Static()->FsSession(), aFullName,aIsFolder);
    }

inline TBool EikFileUtils::FolderExists(const TDesC& aFolderName)
    {
    return BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(), aFolderName);
    }

inline TFileName EikFileUtils::FolderNameFromFullName(const TDesC& aFullName)
    {
    return BaflUtils::FolderNameFromFullName(aFullName);
    }

inline TFileName EikFileUtils::DriveAndPathFromFullName(const TDesC& aFullName)
    {
    return BaflUtils::DriveAndPathFromFullName(aFullName);
    }

inline TFileName EikFileUtils::RootFolderPath(const TBuf<1> aDriveLetter)
    {
    return BaflUtils::RootFolderPath(aDriveLetter);
    }

inline void EikFileUtils::AbbreviateFileName(const TFileName& aOriginalFileName, TDes& aAbbreviatedFileName)
    {
    BaflUtils::AbbreviateFileName(aOriginalFileName,aAbbreviatedFileName);
    }

inline TBool EikFileUtils::UidTypeMatches(const TUidType& aFileUid, const TUidType& aMatchUid)
    {
    return BaflUtils::UidTypeMatches(aFileUid,aMatchUid);
    }

inline TInt EikFileUtils::Parse(const TDesC& aName)
    {
    return BaflUtils::Parse(aName);
    }

inline TInt EikFileUtils::CopyFile(const TDesC& aSourceFullName, const TDesC& aTargetFullName, TUint aSwitch)
    {
    return BaflUtils::CopyFile(CEikonEnv::Static()->FsSession(),aSourceFullName,aTargetFullName,aSwitch);
    }

inline TInt EikFileUtils::RenameFile(const TDesC& aOldFullName, const TDesC& aNewFullName, TUint aSwitch)
    {
    return BaflUtils::RenameFile(CEikonEnv::Static()->FsSession(),aOldFullName,aNewFullName,aSwitch);
    }

inline TInt EikFileUtils::DeleteFile(const TDesC& aSourceFullName, TUint aSwitch)
    {
    return BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(), aSourceFullName,aSwitch);
    }

inline TInt EikFileUtils::CheckWhetherFullNameRefersToFolder(const TDesC& aFullName, TBool& aIsFolder)
    {
    return BaflUtils::CheckWhetherFullNameRefersToFolder(aFullName,aIsFolder);
    }

inline TInt EikFileUtils::MostSignificantPartOfFullName(const TDesC& aFullName, TFileName& aMostSignificantPart)
    {
    return BaflUtils::MostSignificantPartOfFullName(aFullName,aMostSignificantPart);
    }

inline TInt EikFileUtils::CheckFolder(const TDesC& aFolderName)
    {
    return BaflUtils::CheckFolder(CEikonEnv::Static()->FsSession(),aFolderName);
    }

inline TInt EikFileUtils::DiskIsReadOnly(const TDesC& aFullName, TBool& aIsReadOnly)
    {
    return BaflUtils::DiskIsReadOnly(CEikonEnv::Static()->FsSession(),aFullName,aIsReadOnly);
    }

inline void EikFileUtils::UpdateDiskListL(const RFs& aFs,CDesCArray& aArray,TBool aIncludeRom,TDriveNumber aDriveNumber)
    {
    BaflUtils::UpdateDiskListL(aFs,aArray,aIncludeRom,aDriveNumber);
    }

inline void EikFileUtils::RemoveSystemDirectory(CDir& aDir)
    {
    BaflUtils::RemoveSystemDirectory(aDir);
    }

inline TBool EikFileUtils::IsFirstDriveForSocket(TDriveUnit aDriveUnit)
    {
    return BaflUtils::IsFirstDriveForSocket(aDriveUnit);
    }

inline TInt EikFileUtils::SortByTable(CDir& aDir,CBaflFileSortTable* aTable)
/** Sorts files by UID.

The caller supplies a table which specifies the order in which files are to be sorted. 
The files whose UID3 is the first UID in the table appear first. The files whose UID3 
is the UID specified second appear next, and so on. Files whose UID3 is not specified 
in the table, and directories, appear at the end of the list, with directories preceding 
the files, and with files sorted in ascending order of UID3.

This function is used for customising how lists of application files are sorted.

@param aDir The array of files and directories to sort. 
@param aTable A sort order table containing the UIDs to use in the sort. 
@return KErrNone if successful otherwise another of the system-wide error codes. */
    {
    return BaflUtils::SortByTable(aDir,aTable);
    }

#endif  // EIKFUTIL_H

// End of File
