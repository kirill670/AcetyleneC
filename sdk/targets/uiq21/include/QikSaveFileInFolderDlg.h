// QikSaveFileInFolderDlg.h

// Copyright (c) 2000-2001 Symbian Ltd.  All rights reserved.

#ifndef _QIKSAVEFILEINFOLDERDLG_
#define _QIKSAVEFILEINFOLDERDLG_

#include <eikdialg.h>
#include <eiklbo.h>
#include <eiklabel.h>
#include <apmstd.h>
#include <badesca.h>

#include <eikchlst.h>
#include <QikMediaFileFolderUtils.h>

class CEikEdwin;
class CEikCheckBox;

/**
* CQikSaveFileInFolderDlg
*
* 
*/

class CQikSaveFileInFolderDlg : public CEikDialog, public MQikMediaFileFolderUtilsObserver 
	{
public:
	IMPORT_C static TBool RunDlgLD(const TFileName& aFullPath, const TFileName& aNewName);
	~CQikSaveFileInFolderDlg();
private:
	void GetHelpContext(TCoeHelpContext& aContext) const;
	void ConstructL();
	CQikSaveFileInFolderDlg(const TFileName& aFullPath, const TFileName& aNewName);
	void SetDialogTitleL();
	void PrepareSaveRecognizedFileDlgL();
	void PrepareSaveUnrecFileDlgL();
	//CEikDialog
	void PreLayoutDynInitL();
	void PostLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
	virtual void FileFolderEventCompleteL(TInt aStatus);
	void SortMediaFilesInternalDriveFirstL();
	void FindMimeTypeL();
	TInt PrepareForcedExitL();
	void UpdateDestinationPathL(TBool aWithFileName = ETrue);
	void TruncateFilenameL(TInt aLength);
	TBool ShowReplaceFileDialogL();
    void ShowCannotReplaceFileDlgL();
	void CreateUniqueFileNameL();
	void CalculateAndSetFileNameLimitL();
	TBool IsValidFileName(const TDesC* aFileName);
	static TInt WallpaperCompleteCallBack(TAny* aSelf);
private:
	TFileName iMimeType;
	const TFileName& iFullPath;
	CArrayPtrFlat<CQikMediaFile>* iFolderNames;
	CQikMediaFileFolderUtils* iMediaUtils;
	CEikChoiceList* iFolderChoiceList;
	CEikChoiceList* iLocationChoiceList;
	/** This variable is used as destination target when saving media to disk */
	CQikMediaFile* iStorageInfo;
	TInt iDriveIndex;
	TInt iDriveNameIndex;
	TBool iExiting;
	TBool iRecognized;
	TFileName iCurrentName;
	TFileName iExtension;
	TFileName iReplaceFileName;
	CEikEdwin* iNameEditField;
	CEikCheckBox* iCheckBox;
	};

#endif //_CQikSaveFileInFolderDlg_
