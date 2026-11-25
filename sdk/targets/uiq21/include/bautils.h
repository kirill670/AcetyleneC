// BAUTILS.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__BAUTILS_H__)
#define __BAUTILS_H__

#include <e32std.h>
#include <f32file.h>
#include <barsread.h>
#include <badesca.h>

const TUint KBaflCharTruncation=0x2026; // Unicode's "horizontal ellipsis"

// There are at most 8 languages in the language downgrade path.
// The end of the language path is marked by an ELangNone.
const TInt KMaxDowngradeLanguages = 8;
typedef TLanguage TLanguagePath[KMaxDowngradeLanguages + 1];

class RFs;
class CBaflFileSortTable;

/**
 *
 * Provide simple-to-use file system utilities.
 *
 * The functions listed in "Copying, renaming, and deleting files" create
 * a <code>CFileMan</code> object, call its appropriate function, and
 * then delete the object. They're useful for one-off calls, but for
 * repeated use it's more efficient to use <code>CFileMan</code>
 * directly.Note that there is a very similiar group of functions
 * available in <code>EikFileUtils</code>, which may be easier to use in
 * GUI applications, as they do not require a file server session to be
 * passed.
 *
 * @since 5.0
 * @lib "bafl.lib"
 */
class BaflUtils
	{
public:
	IMPORT_C static void CopyWithTruncation(TDes& aDest,const TDesC& aSrc,TChar aTruncationSymbol=KBaflCharTruncation);
	IMPORT_C static TBool FileExists(const RFs& aFs,const TDesC& aFileName);
	IMPORT_C static void EnsurePathExistsL(RFs& aFs,const TDesC& aFileName);
	IMPORT_C static TPtrC ExtractAppNameFromFullName(const TFullName &aName);
	IMPORT_C static void NearestLanguageFile(const RFs& aFs,TFileName& aName);
	IMPORT_C static TInt GetSystemDrive(TDriveNumber& aDriveNumber);
	IMPORT_C static TBool PathExists(RFs& aFs,const TDesC& aFileName);
	IMPORT_C static TInt IsFolder(const RFs& aFs, const TDesC& aFullName, TBool& aIsFolder);
	IMPORT_C static TBool FolderExists(RFs& aFs, const TDesC& aFolderName);
	IMPORT_C static TFileName FolderNameFromFullName(const TDesC& aFullName);
	IMPORT_C static TFileName DriveAndPathFromFullName(const TDesC& aFullName);
	IMPORT_C static TFileName RootFolderPath(const TBuf<1> aDriveLetter);
	IMPORT_C static void AbbreviateFileName(const TFileName& aOriginalFileName, TDes& aAbbreviatedFileName);
	IMPORT_C static TBool UidTypeMatches(const TUidType& aFileUid, const TUidType& aMatchUid);
	IMPORT_C static TInt Parse(const TDesC& aName);
	IMPORT_C static TInt ValidateFolderNameTypedByUserL(const RFs& aFs, const TDesC& aFolderNameTypedByUser, const TDesC& aCurrentPath, TFileName& aNewFolderFullName);
	IMPORT_C static TInt CopyFile(RFs& aFs, const TDesC& aSourceFullName, const TDesC& aTargetFullName, TUint aSwitch = CFileMan::EOverWrite);
	IMPORT_C static TInt RenameFile(RFs& aFs, const TDesC& aOldFullName, const TDesC& aNewFullName, TUint aSwitch = CFileMan::EOverWrite);
	IMPORT_C static TInt DeleteFile(RFs& aFs, const TDesC& aSourceFullName, TUint aSwitch = 0);
	IMPORT_C static TInt CheckWhetherFullNameRefersToFolder(const TDesC& aFullName, TBool& aIsFolder);
	IMPORT_C static TInt MostSignificantPartOfFullName(const TDesC& aFullName, TFileName& aMostSignificantPart);
	IMPORT_C static TInt CheckFolder(RFs& aFs, const TDesC& aFolderName);
	IMPORT_C static TInt DiskIsReadOnly(RFs& aFs, const TDesC& aFullName, TBool& aIsReadOnly);
	IMPORT_C static void UpdateDiskListL(const RFs& aFs,CDesCArray& aArray,TBool aIncludeRom,TDriveNumber aDriveNumber);
	IMPORT_C static void RemoveSystemDirectory(CDir& aDir);
	IMPORT_C static TBool IsFirstDriveForSocket(TDriveUnit aDriveUnit);
	IMPORT_C static TInt SortByTable(CDir& aDir,CBaflFileSortTable* aTable);
	IMPORT_C static void GetDowngradePathL(const RFs& aFs, const TLanguage aCurrentLanguage, RArray<TLanguage>& aLanguageArray);
	IMPORT_C static void PersistLocale();
	IMPORT_C static void PersistHAL();
	IMPORT_C static void PersistScreenCalibration(const TDigitizerCalibration& aScreenCalibration);
	IMPORT_C static void InitialiseScreenCalibration(RFs& aFs);
	IMPORT_C static void InitialiseHAL(RFs& aFs);
	IMPORT_C static void InitialiseLocale(RFs& aFs);
private:
	static void DoCopyFileL(RFs& aFs, const TDesC& aSourceFullName, const TDesC& aTargetFullName, TUint aSwitch);
	static void DoRenameFileL(RFs& aFs, const TDesC& aOldFullName, const TDesC& aNewFullName, TUint aSwitch);
	static void DoDeleteFileL(RFs& aFs, const TDesC& aSourceFullName, TUint aSwitch);
	};

/**
 * @internal
 * Internal to Symbian
 */
class CBaflFileSortTable : public CArrayFixFlat<TUid>
	{
public:
	IMPORT_C CBaflFileSortTable();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
private:
	enum {EArrayGranularity=4};
	};

#endif
