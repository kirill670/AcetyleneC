// APFCTLF.H
//
// Copyright (c) 1997-2004 Symbian Software Ltd.  All rights reserved.
//

#ifndef __APFCTLF_H__
#define __APFCTLF_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__APAID_H__)
#include <apaid.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

// classes defined:
#if (defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)) && !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)
class CApaScanningControlFinder;
#endif
//
// classes referenced:
class CDir;
//
#if (defined(SYMBIAN_SUPPORT_UI_FRAMEWORKS_V1) || !defined(SYMBIAN_HIDE_UI_FRAMEWORKS_V1)) && !defined(SYMBIAN_REMOVE_UI_FRAMEWORKS_V1)
class CApaScanningControlFinder : public CApaAppFinder
/** Scans drives for control panel plugins (with .ctl extensions).

An object of this class is used by CApaSystemControlList, which 
is the list of plugins. 

@publishedPartner
@deprecated
*/
	{
public:
	IMPORT_C static CApaScanningControlFinder* NewLC(const RFs& aFs);
	IMPORT_C static CApaScanningControlFinder* NewL(const RFs& aFs);
	//
	IMPORT_C void FindAllAppsL();
	IMPORT_C TBool NextL(TApaAppEntry& aEntry);
	IMPORT_C TFileName FindAppL(const TDesC& aFileName,TUid aFileUid); 
	//
	IMPORT_C TFileName TempPath()const;
	IMPORT_C TFileName DefaultAppInfoFileName()const;
	//
	IMPORT_C ~CApaScanningControlFinder();
private:
	CApaScanningControlFinder(const RFs& aFs);
	TBool ScanDriveByNameL(TFileName& aFullPath,const TDesC& aDriveName,const TDesC& aTargetName);
	TBool ScanDriveByUidL(TFileName& aFullName,TUid aUid,const TDesC& aExtension,const TDesC& aDriveName);
	TInt GetAppEntryL(TApaAppEntry& aAppEntry,const TEntry& aDir);
	TInt GetFileListL(TInt aDriveNum);
	TInt NextDriveToScan(TInt aCurrentDrive)const;
	static void CheckErrorL(TInt aError);
private:
	CDir* iFileList;
	TDriveList* iDriveList;
	TInt iDriveNum;
	TInt iFileIndex;
	const RFs& iFs;
	};
#endif


#endif
