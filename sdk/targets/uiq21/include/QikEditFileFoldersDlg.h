// QikEditFileFoldersDlg.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKEDITFILEFOLDERSDLG_H__
#define __QIKEDITFILEFOLDERSDLG_H__

#include <eikdialg.h>
#include <badesca.h>
#include <QikMediaFileFolderUtils.h>

#include <eikchlst.h>
#include <qikutils.hrh>
/**
 * Dialog that lets the user add and edit folders.
 *
 */
class CQikEditFileFoldersDlg : public CEikDialog, public MQikMediaFileFolderUtilsObserver
	{
public:
	IMPORT_C static TBool RunDlgLD( const MDesCArray& aMimeTypes, CArrayPtrFlat<HBufC>* aCategoriesList, TInt aSelectedItem, CQikMediaFile*& aFolderInfo, TBool& aUpdateNeeded);
	~CQikEditFileFoldersDlg();
private:
	void GetHelpContext(TCoeHelpContext& aContext) const;
	void ConstructL(CArrayPtrFlat<HBufC>* aCategoriesList);
	CQikEditFileFoldersDlg( const MDesCArray& aMimeTypes,TInt aSelectedItem, CQikMediaFile*& aFolderInfo, TBool& aUpdateNeeded);
	virtual void RunAddDialogL();
	virtual void RunRenameDialogL();
	void AddFileFolderL();
	void RenameFileFolderL();
	void DeleteFileFolderL();
	void AddItemToListL(TDesC& aFolder, TDriveNumber& aDrive);
	void CreateListsL();
	void RefreshFolderListL();
	//From CEikDialog
	TBool OkToExitL( TInt aButtonId );
	void PreLayoutDynInitL();
	//MQikMediaFileFolderUtilsObserver
	virtual void FileFolderEventCompleteL(TInt aStatus);

private:
	const MDesCArray& iMimeTypes;
	CArrayPtrFlat<HBufC>* iCategoriesList;
	TInt iSelectedItem;
	CArrayPtrFlat<CQikMediaFile>* iInfoArray;
	CQikMediaFileFolderUtils* iMediaUtils;
	CEikTextListBox* iFolderListBox;
	CArrayFixFlat<TDriveNumber>* iListDrives;
	CDesCArrayFlat* iFoldersList;
	CArrayFixFlat<TDriveNumber>* iDrivesMatchingFolders;
	TQikMediaOperation iOperation; 

	TBuf<32> iUnfiled;
	TName iCurrentCategory;
	CQikMediaFile*& iFolderInfo;
	TBool& iUpdateNeeded;
	TInt iInternalSeparatorIndex;
	TInt iExternalSeparatorIndex;

	};


/**
 * Dialog that lets the user add a folder.
 *
 */
class CQikAddFileFolderDlg : public CEikDialog, public MQikMediaFileFolderUtilsObserver
	{
public:
	static TBool RunDlgLD(const MDesCArray& aMimeTypes, CArrayFixFlat<TDriveNumber>* aListDrives,TDes& aFolderName, TDriveNumber& aDrive);
	~CQikAddFileFolderDlg();
private:
	void ConstructL();
	CQikAddFileFolderDlg( const MDesCArray& aMimeTypes,CArrayFixFlat<TDriveNumber>* aListDrives,TDes& aFolderName,TDriveNumber& iDrive);
	TBool CheckNameL( const TDesC& aName );
	void CreateLocationChoiceListL();
	TBool AddFolderL();
	//CEikDialog
	void PreLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
	// MQikMediaFileFolderUtilsObserver
	void FileFolderEventCompleteL(TInt aStatus);
	TInt PrepareForcedExitL();
private:
	CArrayPtrFlat<CQikMediaFile>* iInfoArray;
	const MDesCArray& iMimeTypes;
	CQikMediaFileFolderUtils* iMediaUtils;
	TInt iDriveIndex;
	CArrayFixFlat<TDriveNumber>* iListDrives;
	CEikChoiceList* iLocationChoiceList;
	TDes& iFolderName;
	TDriveNumber& iDrive;
	};


/**
 * Dialog that lets the user delete and rename a selected folder.
 *
 */
class CQikRenameFileFolderDlg : public CEikDialog, public MQikMediaFileFolderUtilsObserver
	{
public:
	static TBool RunDlgLD(const MDesCArray& aMimeTypes, TDes& aFolderName, TDriveNumber& aDrive, CArrayFixFlat<TDriveNumber>* aListDrives);
	~CQikRenameFileFolderDlg();
private:
	void ConstructL();
	CQikRenameFileFolderDlg(const MDesCArray& aMimeTypes, TDes& aFolderName, TDriveNumber& aDrive,CArrayFixFlat<TDriveNumber>* aListDrives);
	TBool CheckNameL( const TDesC& aName );
	void CreateLocationChoiceListL();
	void RenameFolderL();
	TBool RunRenameFolderL();
	//CEikDialog
	void PreLayoutDynInitL();
	TBool OkToExitL(TInt aButtonId);
	TInt PrepareForcedExitL();
	//MQikMediaFileFolderUtilsObserver
	void FileFolderEventCompleteL(TInt aStatus);

private:
	const MDesCArray& iMimeTypes;
	TDes& iFolder;
	TDriveNumber& iDrive;
	CArrayFixFlat<TDriveNumber>* iListDrives;
	CArrayPtrFlat<CQikMediaFile>* iSourceArray;
	CQikMediaFile* iDestinationInfo;
	CQikMediaFileFolderUtils* iMediaUtils;
	CEikChoiceList* iLocationChoiceList;
	TBuf<32> iFolderName;
	TInt iDriveIndex;	//External drive.
	TInt iNumOp;
	};
#endif	// __QIKEDITFILEFOLDERSDLG_H__


