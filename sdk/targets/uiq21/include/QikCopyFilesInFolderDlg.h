// QikCopyFilesInFolderDlg.h

// Copyright (c) 2000-2001 Symbian Ltd.  All rights reserved.

#ifndef _QIKCopyFilesInFolderDLG_
#define _QIKCopyFilesInFolderDLG_

#include <eikdialg.h>
#include <eiklbo.h>
#include <apmstd.h>
#include <badesca.h>

#include <eikchlst.h>
#include <QikMediaFileFolderUtils.h>
#include <QikMediaFolderChangeNotifier.h>

/**
* CQikCopyFilesInFolderDlg
*
* 
*/
class CQikCopyFilesInFolderDlg : public CEikDialog,public MQikMediaFileFolderUtilsObserver, public MQikMediaFolderChangeNotifierObserver
	{
public:
	IMPORT_C static TBool RunDlgLD(const CArrayFixFlat<TFileName>* aSourceFiles);
	IMPORT_C static TBool RunDlgLD(const CArrayFixFlat<TFileName>* aSourceFiles, CDesCArray* aMimeTypes);
	IMPORT_C static TBool RunDlgLD(const CArrayPtrFlat<CQikMediaFile>* aSourceFiles);
	~CQikCopyFilesInFolderDlg();

	void DoExitL();
private:
	CQikCopyFilesInFolderDlg(const CArrayFixFlat<TFileName>* aSourceFiles);
	CQikCopyFilesInFolderDlg(const CArrayFixFlat<TFileName>* aSourceFiles, CDesCArray* aMimeTypes);
	CQikCopyFilesInFolderDlg(const CArrayPtrFlat<CQikMediaFile>* aSourceFiles);
	void ConstructL();
	void CreateMimeTypeListL();
	void CreateChoiceListL();
	void CreateFoldersListL();
	TBool InsertDriveNameL(TDriveNumber aDrive, TInt aPos);
	
	//CEikDialog
	void PreLayoutDynInitL();
	void PostLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
	TInt PrepareForcedExitL();

	//From MQikMediaFileFolderUtilsObserver
	virtual void FileFolderEventCompleteL(TInt aStatus);

	//From MQikMediaFolderChangeNotifierObserver
	TBool NewDiskStateL(const TDriveNumber& aDrive);
	TBool StructureChangedL(const TDriveNumber& aDrive, TDesC& aMimeType);
private:
	const CArrayFixFlat<TFileName>* iSourceFiles; //the array list of source files to copy (files outside MMFH)
	const CArrayPtrFlat<CQikMediaFile>* iSourceMediaFiles;//the array list of source files to copy (files internal to MMFH)
	CDesCArray* iMimeTypes; // the list of mime types to get folder list from
	CDesCArray* iFolders; // the list of folders to display to the user.
	CArrayFixFlat<TDriveNumber>* iListDrives;// list of drives matching the iFolders list (to know on which drive is each folder).
	CQikMediaFileFolderUtils* iMediaUtils; // used to perfom listing, copying operations.
	TFileName iListFiles; //Contains the string to put in the label listing files.
	TBool iOwnMimeArray; //True if we create the mimeType array, false if it is passed as a parameter.

	CEikChoiceList* iFolderChoiceList; //The choice list displayed to the user.
	
	CQikMediaFolderChangeNotifier* iDiskNotifier; // The disk state change notifier

	CAsyncOneShot* iExitCallback; // A callback used to close the dialog
	};
#endif //_CQikCopyFilesInFolderDlg_
