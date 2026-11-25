// QikMediaFolderChangeNotifier.h
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKMEDIAFOLDERCHANGENOTIFIER_H__
#define __QIKMEDIAFOLDERCHANGENOTIFIER_H__

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif
#include <badesca.h>

#include "QikMediaFileFolderUtils.h"

class CEikonEnv;

class MQikMediaFolderChangeNotifierObserver
	{
public:
	virtual TBool NewDiskStateL(const TDriveNumber& aDrive)=0;
	virtual TBool StructureChangedL(const TDriveNumber& aDrive, TDesC& aMimeType)=0;
	};

class CQikMediaFolderChangeNotifier : public CActive
	{
public:
	IMPORT_C static CQikMediaFolderChangeNotifier* NewL(MQikMediaFolderChangeNotifierObserver& aObserver,CEikonEnv& aEikEnv,const TDriveNumber& aDrive, const TDesC& aMimeType,const TNotifyType& aNotifyType);
	IMPORT_C ~CQikMediaFolderChangeNotifier();
	IMPORT_C TInt Start();
	
	TDriveNumber Drive() {return iDrive;};
private:
	CQikMediaFolderChangeNotifier(MQikMediaFolderChangeNotifierObserver& aObserver,CEikonEnv& aEikEnv);
	void ConstructL(const TDriveNumber& aDrive, const TDesC& aMimeType,const TNotifyType& aNotifyType);
	void DoCancel();
	void RunL();
private:
	MQikMediaFolderChangeNotifierObserver& iObserver;
	CEikonEnv& iEikEnv;
	TDriveNumber iDrive;
	TDesC* iMimeType;
	TNotifyType iNotifyType;

	TPath iPath;
	RFs iFs;
	TBool iDiskRemoved;
	TBool iDiskMissing;
	TBool iWatchingDrive;
	};

#endif  // __QIKMEDIAFOLDERCHANGENOTIFIER_H__