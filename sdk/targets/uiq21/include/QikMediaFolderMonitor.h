// QikMediaFolderMonitor.h
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __QikMediaFolderMonitor_H__
#define __QikMediaFolderMonitor_H__

#include <badesca.h>
#include <eikmenup.h>
#include <e32std.h>

#include "QikMediaFolderChangeNotifier.h"

class CEikonEnv;

class MQikMediaFolderMonitorObserver
	{
public:
	virtual void FolderChangeL(const TDriveNumber& aDrive, const TDesC& aFolder, const TBool aUpdateNeeded)=0;
	virtual void FolderChangeToAllL(const TBool aUpdateNeeded)=0;
	};

class CQikMediaFolderMonitor :public CBase, public MQikMediaFolderChangeNotifierObserver
	{
public:
	IMPORT_C static CQikMediaFolderMonitor* NewL(MQikMediaFolderMonitorObserver& aObserver, RFs& aFs,MDesCArray& aMimeTypes,CEikonEnv& aEikEnv);
	IMPORT_C ~CQikMediaFolderMonitor();
	IMPORT_C void DynInitMenuPaneL(CEikMenuPane* aMenuPane, TBool aAllFolder = ETrue);

	IMPORT_C virtual TBool NewDiskStateL(const TDriveNumber& aDrive);
	IMPORT_C virtual TBool StructureChangedL(const TDriveNumber& aDrive, TDesC& aMimeType);
	IMPORT_C TInt ProcessCommandL(TInt aCommand);
private:
	CQikMediaFolderMonitor(MQikMediaFolderMonitorObserver& aObserver,RFs& aFs,CEikonEnv& aEikEnv);
	void ConstructL(MDesCArray& aMimeTypes);
	void BuildNotifiersListL();
	void BuildCategoriesListL();
	void UpdateCurrentFolderIndex();

private:
	MQikMediaFolderMonitorObserver& iObserver;
	RFs& iFs;
	CDesCArray* iMimeTypes;
	CEikonEnv& iEikEnv;

	TDriveNumber iCurrentDrive;
	TDriveList iDriveList;
	CQikMediaFileFolderUtils* iFoldersUtils;
	CQikMediaFolderChangeNotifier* iDiskNotifier;
	CArrayPtrFlat<CQikMediaFile>* iFoldersList;
	CArrayPtrFlat<CQikMediaFolderChangeNotifier>* iNotifiersList;
	CArrayPtrFlat<HBufC>* iCategoriesList;
	TInt iSelectedCategory;
	TInt iNotUsed;
	HBufC* iCurrentFolderName;
	};
#endif  // __QikMediaFolderMonitor_H__
