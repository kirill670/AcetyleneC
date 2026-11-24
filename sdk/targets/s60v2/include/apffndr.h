// APFFNDR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APFFNDR_H__
#define __APFFNDR_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__APAID_H__)
#include <apaid.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if (defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)) && !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)

// classes defined:
class CApaScanningAppFinder;
//
// classes referenced:
class CDir;
//

/**
KAppDllSearchPath

@internalComponent
*/
_LIT(KAppDllSearchPath,"\\System\\Apps\\");

/**
KAppDllSearchAnyFile

@internalComponent
*/
_LIT(KAppDllSearchAnyFile,"*");

/**
KAppDllSearchString

@internalComponent
*/
_LIT(KAppDllSearchString,"?:\\System\\Apps\\");

class CApaScanningAppFinder : public CApaAppFinder
/** Scans drives for applications (with a .app extension).

@publishedAll
@deprecated
*/
	{
public:
	IMPORT_C static CApaScanningAppFinder* NewLC(const RFs& aFs);
	IMPORT_C static CApaScanningAppFinder* NewL(const RFs& aFs);
	//
	IMPORT_C void FindAllAppsL();
	IMPORT_C TBool NextL(TApaAppEntry& aEntry);
	IMPORT_C TFileName FindAppL(const TDesC& aFileName,TUid aFileUid); 
	//
	IMPORT_C TFileName TempPath()const;
	IMPORT_C TFileName DefaultAppInfoFileName()const;
	//
	IMPORT_C ~CApaScanningAppFinder();
private:
	CApaScanningAppFinder(const RFs& aFs);
	TBool ScanDriveByNameL(TFileName& aFullPath,const TDesC& aDriveName,const TDesC& aTargetName,TBool aUseExeExtension);
	TBool ScanDriveByUidL(TFileName& aFullName,TUid aUid,const TDesC& aExtension,const TDesC& aDriveName);
	TBool ScanDirListByUidL(CDir& aDirList, TFileName& aFullName,TUid aUid,const TDesC& aExtension,const TDesC& aDriveName,TBool aUseExeExtension);
	void SetSearchPathL(TFileName& aSearchPath,const TDesC& aFileName,TBool aUseExeExtension)const;
	TInt GetAppEntryL(TApaAppEntry& aAppEntry,const TEntry& aDir,TBool aUseExeExtension);
	TInt GetFileListL(TInt aDriveNum);
	TInt NextDriveToScan(TInt aCurrentDrive)const;
	static void CheckErrorL(TInt aError);
private:
	CDir* iFileList;
	TDriveList* iDriveList;
	TInt iDriveNum;
	TInt iDirIndex;
	const RFs& iFs;
	};
#endif // #if (defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)) && !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)

#endif
