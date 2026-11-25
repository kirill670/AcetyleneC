// QikSelectMediaFileDlg.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
// Created for Quartz 6.0

#ifndef __QIKSELECTMEDIAFILEDLG_H__
#define __QIKSELECTMEDIAFILEDLG_H__

#include <eikdialg.h>
#include <badesca.h>
#include <e32base.h>
#include <eiklbx.h>
#include <eiktxlbx.h>
#include <eikclb.h>
#include <eikhopbt.h> 
#include <eikchlst.h>	// CEikChoiceList
#include <fbs.h>
#include <apparc.h>
#include <apgcli.h>
#include <qiksoundplayer.h> // MQikSoundPlayerObserver


#include <QikMediaFileFolderUtils.h>

class CQikSelectImageListBox;
class TMediaFileInfo;

/**
 * Dialog that lets the user add and edit file folders.
 *
 */
class CQikSelectMediaFileDlg : public CEikDialog, public MQikSoundPlayerObserver
	{
public:
	IMPORT_C static TBool RunDlgLD(const MDesCArray& aMimeTypes, TFileName& aFileName, const TDesC* aTitle=NULL);
	IMPORT_C static TBool RunDlgLD(const MDesCArray& aMimeTypes, TFileName& aFileName, CQikMediaFileFolderUtils& aUtils, const TDesC* aTitle=NULL);
	~CQikSelectMediaFileDlg();
	//From CEikDialog
	SEikControlInfo CreateCustomControlL(TInt aControlType);
private:
	void ConstructL();
	CQikSelectMediaFileDlg(const MDesCArray& aMimeTypes, TFileName& aFileName, CQikMediaFileFolderUtils& aMediaUtils, const TDesC* aTitle);
	void CreateInitialArraysL();
	void CreateCurrentArraysL(TDesC16* aFolder, TInt aIndex);
	void SetDialogTitleL();
	void CreateListBoxL();
	void SortMediaFilesInternalDriveFirstL();
	void GetUnrecognizedFilesL(CArrayPtrFlat<CQikMediaFile>& aFilesArray, TInt aIndex);
	void CreateChoiceListL();
	void CreateChoiceListRecognizedMimeTypeL();
	void CreateChoiceListUnrecMimeTypeL();
	void AddVoiceNotesToMediaFilesL();
	TBool CheckIfVoiceNoteFile(const CQikMediaFile* aFileInfo) const;
	TBool IsSnakingListBoxActive();
	TInt AddNewBitmapsL(const TUid aAppUid);
	void GetFullName(const TDesC& aFileName, TFileName& aFullFileName);
	CGulIcon* GetFileIconL(const CQikMediaFile* aFile);
	void ClearBitmapsL();
	void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEvent);
	TBool OkToExitL( TInt aButtonId );
	void PreLayoutDynInitL();
	void PostLayoutDynInitL();
	void PopulateListBoxL();
	void PlaySoundL();
	void SelectionL();
	// From MQikSoundPlayerObserver
	virtual void PlayComplete();
private:
	const MDesCArray& iMimeTypes;
	CQikMediaFileFolderUtils& iMediaUtils;
	CDesCArray* iChoiceListArray;						//Contains the folders represented in the choicelist.
	CArrayPtrFlat<CQikMediaFile>* iSelectedFileArray;      //Temporary array containing files from selected folder.
	CArrayPtrFlat<CQikMediaFile>* iMediaFileArray;			//Temporary array containing all files. Sorted by drive, folder and filename.
	CArrayPtrFlat<CQikMediaFile>* iDriveAndFolderArray;		//Contains drive and folder info to set iCurrentFolderInfo.
	CArrayPtrFlat<CQikMediaFile>* iVoiceFiles;			//Contains all the voicenotes from directory C:\VoiceNote
	CDesCArray* iSpecificMimeTypes;						// Specific MIME-types used for icon-caching.
	CArrayPtrFlat<CGulIcon>* iIconArray;	// Icon cache. One icon per MIME-type.
	
	TFileName&				iFileName;
	const TDesC*			iTitle;
	CQikSelectImageListBox* iSelectImageListBox;
	CEikColumnListBox*		iListBox;
	CEikChoiceList*			iChoiceList;
	CEikLabeledOptionButton* iThumbnailOptionButton;
	CEikLabeledOptionButton* iListOptionButton;
	TInt					iDriveNameIndex;
	TBuf<32>				iAllFolder;
	TBool					iUnrecMode;

	RApaLsSession           iAppList; // List of apps runnin
	CArrayFix<TUid>*        iAppUids; //  Array of uids associated with the bitmaps
	CArrayPtr<CGulIcon>*  iQuestionMarkIcons; //Array of ? icons for files without known application or without bitmap
	CArrayPtr<CApaMaskedBitmap>* iAppBitmaps;
	CQikSoundPlayer* iPlayer;

	enum TSelectMediaFileIconSizes
		{
		EIconSizeSmall=0,
		EIconSizeMedium,
		EIconSizeLarge
		};
	TSelectMediaFileIconSizes iIconSize; // Current wanted size for icon

	enum TDialogType
		{
		EDialogTypeAudio=0,
		EDialogTypeImage,
		EDialogTypeOther
		};
	TDialogType iDialogType;
	};

class TKeyArrayPtr : public TKeyArrayFix
	{
public:
	inline TKeyArrayPtr( TInt aOffset, TKeyCmpText aType, const CArrayPtrFlat<CQikMediaFile>* aArray) : TKeyArrayFix(aOffset, aType) , iArray(aArray) {}
	TAny* At(TInt aIndex) const;

private:
	const CArrayPtrFlat<CQikMediaFile>* iArray;
	};


#endif	// __QIKSELECTMEDIAFILEDLG_H__

