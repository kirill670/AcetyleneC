// EIKFUTIL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKFUTIL_H__)
#define __EIKFUTIL_H__

#include <e32std.h>
#include <f32file.h>
#include <badesca.h>
#include <bautils.h>
#include <eikenv.h>

class CFont;
class CBaflFileSortTable;
class TResourceReader;

/**
 *
 * This class provides a set of drive, path and file utility functions.
 * @since 6.0
 * @lib " eikcore.lib "
 */
class EikFileUtils
	{ 
public:
	inline static TBool PathExists(const TDesC& aPath);
	inline static TInt IsFolder(const TDesC& aFullName, TBool& aIsFolder);
	inline static TBool FolderExists(const TDesC& aFolderName);
	inline static TFileName FolderNameFromFullName(const TDesC& aFullName);
	inline static TFileName DriveAndPathFromFullName(const TDesC& aFullName);
	inline static TFileName RootFolderPath(const TBuf<1> aDriveLetter);
	inline static void AbbreviateFileName(const TFileName& aOriginalFileName, TDes& aAbbreviatedFileName);
	IMPORT_C static TFileName AbbreviatePath(TDesC& aPathName, const CFont& aFont, TInt aMaxWidthInPixels);
	inline static TBool UidTypeMatches(const TUidType& aFileUid, const TUidType& aMatchUid);
	inline static TInt Parse(const TDesC& aName);
	IMPORT_C static TFileName ValidateFolderNameTypedByUserL(const TDesC& aFolderNameTypedByUser, const TDesC& aCurrentPath);
	inline static TInt CopyFile(const TDesC& aSourceFullName, const TDesC& aTargetFullName, TUint aSwitch = CFileMan::EOverWrite);
	inline static TInt RenameFile(const TDesC& aOldFullName, const TDesC& aNewFullName, TUint aSwitch = CFileMan::EOverWrite);
	inline static TInt DeleteFile(const TDesC& aSourceFullName, TUint aSwitch=0);
	inline static TInt CheckWhetherFullNameRefersToFolder(const TDesC& aFullName, TBool& aIsFolder);
	inline static TInt MostSignificantPartOfFullName(const TDesC& aFullName, TFileName& aMostSignificantPart);
	inline static TInt CheckFolder(const TDesC& aFolderName);
	inline static TInt DiskIsReadOnly(const TDesC& aFullName, TBool& aIsReadOnly);
	inline static void UpdateDiskListL(const RFs& aFs,CDesCArray& aArray,TBool aIncludeRom,TDriveNumber aDriveNumber);
	inline static void RemoveSystemDirectory(CDir& aDir);
	inline static TBool IsFirstDriveForSocket(TDriveUnit aDriveUnit);
	inline static TInt SortByTable(CDir& aDir,CBaflFileSortTable* aTable);
	};


/**
 *
 * Tests whether a path exists.
 *
 * @param     " const TDesC& aPath "
 *            The path to check.
 * @returns   " TBool "
 *            <code>ETrue</code> if the path exists,
 *            <code>EFalse</code> otherwise.
 */
inline TBool EikFileUtils::PathExists(const TDesC& aPath)
	{
	return BaflUtils::PathExists(CEikonEnv::Static()->FsSession(),aPath);
	}

/**
 *
 * Sets <code>aFullName</code> as a folder.
 *
 * @param     " const TDesC& aFullName "
 *            The drive and path to make into a folder.
 * @param     " TBool& aIsFolder "
 *            <code>ETrue</code> to set <code>aFullName</code> as a
 *            folder. <code>EFalse</code> otherwise.
 * @returns   " TInt "
 *            <code>KErrNone</code> if successful otherwise another
 *            of the system-wide error codes.
 */
inline TInt EikFileUtils::IsFolder(const TDesC& aFullName, TBool& aIsFolder)
	{
	return BaflUtils::IsFolder(CEikonEnv::Static()->FsSession(), aFullName,aIsFolder);
	}

/**
 *
 * Checks whether the specified folder exists.
 *
 * This returns boolean value if the folder does not exist: see also
 * <code>CheckFolder()</code> which returns an error.
 *
 * @param     " const TDesC& aFolderName "
 *            The folders name and path.
 * @returns   " TBool "
 *            <code>ETrue</code> if the folder exists,
 *            <code>EFalse</code> otherwise.
 */
inline TBool EikFileUtils::FolderExists(const TDesC& aFolderName)
	{
	return BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(), aFolderName);
	}

/**
 *
 * Gets a folder name from a path and file name.
 *
 * @param     " const TDesC& aFullName "
 *            The full path and file name from which the folder will
 *            be obtained.
 * @returns   " TFileName "
 *            Folder name
 */
inline TFileName EikFileUtils::FolderNameFromFullName(const TDesC& aFullName)
	{
	return BaflUtils::FolderNameFromFullName(aFullName);
	}

/**
 *
 * Parses the specified full path and file name to obtain the drive and
 * path.
 *
 * @param     " const TDesC& aFullName "
 *            The full path and file name from which the drive and
 *            path will be obtained.
 * @returns   " TFileName "
 *            The drive and path.
 */
inline TFileName EikFileUtils::DriveAndPathFromFullName(const TDesC& aFullName)
	{
	return BaflUtils::DriveAndPathFromFullName(aFullName);
	}

/**
 *
 * Gets the full path for a drive.
 *
 * @param     " const TBuf<1> aDriveLetter "
 *            The drives letter, <code>C</code> for example.
 * @returns   " TFileName "
 *            The full path for a drive, <code>C:\</code> for
 *            example.
 */
inline TFileName EikFileUtils::RootFolderPath(const TBuf<1> aDriveLetter)
	{
	return BaflUtils::RootFolderPath(aDriveLetter);
	}

/**
 *
 * Tests whether there is sufficient space to display the specified file
 * name.
 *
 * If there is sufficient space then <code>aOriginalFileName</code> is
 * the same as <code>aAbbreviatedFileName</code>. If there is not
 * sufficient space, <code>aOriginalFileName</code> is abbreviated to fit
 * the available space, prefixed with an ellipsis and the abbreviation is
 * returned as <code>aAbbreviatedFileName</code>.For example, if
 * <code>c:\home\letters\abcdef</code> is the original file name and the
 * destination buffer allows only 7 characters, the abbreviated file name
 * will be <code>...abcdef</code>. This can be used to display a file or
 * folder name in an error or progress dialog.
 *
 * @param     " const TFileName& aOriginalFileName "
 *            The file name to be displayed.
 * @param     " TDes& aAbbreviatedFileName "
 *            If there is insufficient space to display
 *            <code>aOriginalFileName</code>, this provides an
 *            abbreviation.
 */
inline void EikFileUtils::AbbreviateFileName(const TFileName& aOriginalFileName, TDes& aAbbreviatedFileName)
	{
	BaflUtils::AbbreviateFileName(aOriginalFileName,aAbbreviatedFileName);
	}

/**
 *
 * Tests whether two UID types match.
 *
 * @param     " const TUidType& aFileUid "
 *            The UID type to match.
 * @param     " const TUidType& aMatchUid "
 *            The UID type to match against.
 * @returns   " TBool "
 *            <code>ETrue</code> if the UIDs match,
 *            <code>EFalse</code> otherwise.
 */
inline TBool EikFileUtils::UidTypeMatches(const TUidType& aFileUid, const TUidType& aMatchUid)
	{
	return BaflUtils::UidTypeMatches(aFileUid,aMatchUid);
	}

/**
 *
 * Parse the specified file name specification.
 *
 * @param     " const TDesC& aName "
 *            The file name specification you wish to parse.
 * @returns   " TInt "
 *            <code>KErrNone</code> if successful otherwise another
 *            of the system-wide error codes.
 */
inline TInt EikFileUtils::Parse(const TDesC& aName)
	{
	return BaflUtils::Parse(aName);
	}

/**
 *
 * Copies the specified file to a specified destination file.
 *
 * Optionally, <code>aSwitch</code> can be set for either recursive
 * operation or to overwrite any files with the same name which exist in
 * the target directory. If recursive operation is set, any intermediate
 * directories are created. If no overwriting is set, any files with the
 * same name are not overwritten, and an error is returned for that
 * file.Notes:files can be copied across drivesopen files can be copied
 * only if they have been opened using the
 * <code>EFileShareReadersOnly</code> file share moderead-only, hidden
 * and system files can be copied and the source files attributes are
 * preserved in the target file
 *
 * @param     " const TDesC& aSourceFullName "
 *            Path indicating the file(s) to be copied. Any path
 *            components which are not specified here will be taken
 *            from the session path.
 * @param     " const TDesC& aTargetFullName "
 *            Path indicating the directory into which the file(s)
 *            are to be copied.
 * @param     " TUint aSwitch "
 *            Optional switch to specify overwriting or recursion.
 *            By default, this function operates with overwriting
 *            and non-recursively. Switch options are defined using
 *            the enum TSwitch. This is defined in f32file.h.
 * @returns   " TInt "
 *            <code>KErrNone</code> if the copy is successful,
 *            otherwise another of the system-wide error codes.
 */
inline TInt EikFileUtils::CopyFile(const TDesC& aSourceFullName, const TDesC& aTargetFullName, TUint aSwitch)
	{
	return BaflUtils::CopyFile(CEikonEnv::Static()->FsSession(),aSourceFullName,aTargetFullName,aSwitch);
	}

/**
 *
 * Renames or moves one or more files or directories.
 *
 * This can also be used to move one or more files by specifying
 * different destination and source directories. Note that the
 * destination and source directories must be on the same drive.If moving
 * files, you can set <code>aSwitch</code> so that any files with the
 * same name that exist in the target directory are overwritten. If
 * <code>aSwitch</code> is set for no overwriting, any files with the
 * same name are not overwritten, and an error
 * (<code>KErrAlreadyExists</code>) is returned for that file.This
 * function can only operate non-recursively, so that only the matching
 * files located in the single directory specified by
 * <code>aOldFullName</code> may be renamed.Read-only, system and hidden
 * files may be renamed or moved, and the source files attributes are
 * preserved in the target file, but open files cannot be renamed or
 * moved. Attempting to rename or move an open file will return an error
 * for that file.
 *
 * @param     " const TDesC& aOldFullName "
 *            Path specifying the file or directory to be renamed.
 * @param     " const TDesC& aNewFullName "
 *            Path specifying the new name for the file or
 *            directory. Any directories specified in this path
 *            which do not exist will be created.
 * @param     " TUint aSwitch "
 *            Optional, determines whether files are overwritten on
 *            the target.
 * @returns   " Tint "
 *            <code>KErrNone</code> if successful otherwise another
 *            of the system-wide error codes.
 */
inline TInt EikFileUtils::RenameFile(const TDesC& aOldFullName, const TDesC& aNewFullName, TUint aSwitch)
	{
	return BaflUtils::RenameFile(CEikonEnv::Static()->FsSession(),aOldFullName,aNewFullName,aSwitch);
	}

/**
 *
 * Deletes one or more files.
 *
 * This function may operate recursively or non-recursively. When
 * operating non-recursively, only the matching files located in the
 * directory specified in <code>aSourceFullName</code> are affected. When
 * operating recursively, all matching files in the directory hierarchy
 * below the directory specified in <code>aSourceFullName</code> are
 * deleted.Read-only and open files cannot be deleted. Attempting to do
 * so will return an error.
 *
 * @param     " const TDesC& aSourceFullName "
 *            Path indicating the file(s) to be deleted. This can
 *            either be a full path, or a path relative to the
 *            session path. Use wildcards to specify more than one
 *            file.
 * @param     " TUint aSwitch "
 *            Determines whether this function operates recursively.
 *            By default, this function operates non-recursively.
 * @returns   " TInt "
 *            <code>KErrNone</code> if <code>aSourceFullName</code>
 *            is successfully deleted, otherwise another of the
 *            system-wide error codes.
 */
inline TInt EikFileUtils::DeleteFile(const TDesC& aSourceFullName, TUint aSwitch)
	{
	return BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(), aSourceFullName,aSwitch);
	}

/**
 *
 * Tests whether a file specification refers to a folder.
 *
 * @param     " const TDesC& aFullName "
 *            The complete file specification to check.
 * @param     " TBool& aIsFolder "
 *            <code>ETrue</code> if <code>aFullName</code> is a
 *            folder, <code>EFalse</code> otherwise.
 * @returns   " TInt "
 *            <code>KErrNone</code> if <code>aFullName</code> is a
 *            folder, otherwise another of the system-wide error
 *            codes.
 */
inline TInt EikFileUtils::CheckWhetherFullNameRefersToFolder(const TDesC& aFullName, TBool& aIsFolder)
	{
	return BaflUtils::CheckWhetherFullNameRefersToFolder(aFullName,aIsFolder);
	}

/**
 *
 * Gets the most significant part of the specified drive, path and file
 * name.
 *
 * @param     " const TDesC& aFullName "
 *            The drive, path and file name.
 * @param     " TFileName& aMostSignificantPart "
 *            On return, the most significant part of
 *            <code>aFullName</code>.
 * @returns   " TInt "
 *            <code>KErrNone</code> if successful otherwise another
 *            of the system-wide error codes.
 */
inline TInt EikFileUtils::MostSignificantPartOfFullName(const TDesC& aFullName, TFileName& aMostSignificantPart)
	{
	return BaflUtils::MostSignificantPartOfFullName(aFullName,aMostSignificantPart);
	}

/**
 *
 * Checks whether the specified folder exists.
 *
 * This returns an error if the folder does not exist: see also
 * <code>FolderExists()</code> which returns a boolean value.
 *
 * @param     " const TDesC& aFolderName "
 *            The folders name and path.
 * @returns   " TInt "
 *            <code>KErrNone</code> if <code>aFolderName</code>
 *            exists, otherwise another of the system-wide error
 *            codes.
 */
inline TInt EikFileUtils::CheckFolder(const TDesC& aFolderName)
	{
	return BaflUtils::CheckFolder(CEikonEnv::Static()->FsSession(),aFolderName);
	}

/**
 *
 * Gets drive read only state.
 *
 * @param     " const TDesC& aFullName "
 *            The disks full name.
 * @param     " TBool& aIsReadOnly "
 *            <code>ETrue</code> to set the specified disk as being
 *            read-only. <code>EFalse</code> to set the specified
 *            disk as not being read-only.
 * @returns   " TInt "
 *            <code>KErrNone</code> if successful otherwise another
 *            of the system-wide error codes.
 */
inline TInt EikFileUtils::DiskIsReadOnly(const TDesC& aFullName, TBool& aIsReadOnly)
	{
	return BaflUtils::DiskIsReadOnly(CEikonEnv::Static()->FsSession(),aFullName,aIsReadOnly);
	}

/**
 *
 * Updates the list of available drives.
 *
 * Inserts a list of all available drives in <code>aArray</code>. The
 * drive list consists of an array of 26 bytes. Array index zero
 * corresponds to drive A, one equals B and so on. Each byte with a non
 * zero value signifies that the corresponding drive contains recognised
 * media.Note that the local file system always reserves drive letters A
 * through I. The internal RAM always uses drive letter C. Drive letter Z
 * is always used for the ROM.
 *
 * @param     " const RFs& aFs "
 *            File server session.
 * @param     " CDesCArray& aArray "
 *            The array in which to insert the list of available
 *            drives.
 * @param     " TBool aIncludeRom "
 *            <code>ETrue</code> if the ROM is included as a drive,
 *            <code>EFalse</code> otherwise.
 * @param     " TDriveNumber aDriveNumber "
 *            Drive with which to begin the list.
 */
inline void EikFileUtils::UpdateDiskListL(const RFs& aFs,CDesCArray& aArray,TBool aIncludeRom,TDriveNumber aDriveNumber)
	{
	BaflUtils::UpdateDiskListL(aFs,aArray,aIncludeRom,aDriveNumber);
	}

/**
 *
 * Deletes a directory and all files and directories contained in the
 * directory structure below it.
 *
 * @param     " CDir& aDir "
 *            The directory to be deleted.
 */
inline void EikFileUtils::RemoveSystemDirectory(CDir& aDir)
	{
	BaflUtils::RemoveSystemDirectory(aDir);
	}

/**
 *
 * Tests whether the specified drive is the first drive for the socket.
 *
 * Sockets provide a generic interface to communication protocols through
 * communication end points known as sockets. EPOC sockets are similar in
 * concept to Berkeley Software Distribution (BSD) sockets from the
 * University of California at Berkeley. They provide a generic interface
 * to network level communications protocols for common operations
 * involved in network computing.
 *
 * @param     " TDriveUnit aDriveUnit "
 *            The drive to check.
 * @returns   " TBool "
 *            <code>ETrue</code> if <code>aDriveUnit</code> is the
 *            first drive for the socket, <code>EFalse</code>
 *            otherwise.
 */
inline TBool EikFileUtils::IsFirstDriveForSocket(TDriveUnit aDriveUnit)
	{
	return BaflUtils::IsFirstDriveForSocket(aDriveUnit);
	}

/**
 *
 * Sorts the files in the given table into order.
 *
 * Any file with UID[2] matching an entry in the table will be sorted
 * relative to others in the table and before any files with no matching
 * UID.
 *
 * @param     " CDir& aDir "
 *            Array of directory entries that have been read into
 *            memory from the file system.
 * @param     " CBaflFileSortTable* aTable "
 *            The table in which the sorted directory entries are
 *            stored.
 * @returns   " TInt "
 *            <code>KErrNone</code> if successful otherwise another
 *            of the system-wide error codes.
 */
inline TInt EikFileUtils::SortByTable(CDir& aDir,CBaflFileSortTable* aTable)
	{
	return BaflUtils::SortByTable(aDir,aTable);
	}


#endif
