// QikMediaFileFolderUtils.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKMEDIAFILEFOLDERUTILS_H__
#define __QIKMEDIAFILEFOLDERUTILS_H__

#include <f32file.h> // class MFileManObserver
#include <apgcli.h>	// class RApaLsSession
#include <qikutils.hrh> // enum definitions
#include <eikdialg.h> //progress dialog
#include <eikprogi.h>

class CEikonEnv;
class CQikMediaFile;
class TDataType;
class CQikUtilsProgressDialog;
class CQikExtensionMimeType;


/**
 * This class is an observer for the dialogs, applications to use for getting notified when
 * the asynchronous file or folder operations are done in CQikMediaFileFolderUtils.
 */
class MQikMediaFileFolderUtilsObserver
	{
public:	
	virtual void FileFolderEventCompleteL(TInt aStatus) = 0;
	};

/**
 * This class provides functionality for saving, renaming, moving, copying and deleting media files, 
 * and also for creating, renaming, moving and deleting media folders. Using this functionality ojects
 * run asynchronously. The class also provides functionality for listing mediafiles and folders synchronously. 
 */
class CQikMediaFileFolderUtils : public CActive, public MFileManObserver
	{
public:
	IMPORT_C static CQikMediaFileFolderUtils* NewL(CEikonEnv& aEikenv);
	IMPORT_C ~CQikMediaFileFolderUtils();
	IMPORT_C void Start();
	IMPORT_C void RecognizedMediaFilesL(const MDesCArray& aMimeTypes, CArrayPtrFlat<CQikMediaFile>& aRecognizedFilesList);
	IMPORT_C void FilesInFolderL(const MDesCArray& aMimeTypes, const TDesC& aFolderName,const TDriveNumber& aDrive, CArrayPtrFlat<CQikMediaFile>& aSelectedFilesList);
	IMPORT_C void FoldersL(const MDesCArray& aMimeTypes, CArrayPtrFlat<CQikMediaFile>& aFoldersList);
	IMPORT_C void SetOperationL(TQikMediaOperation aOperation, const CArrayPtrFlat<CQikMediaFile>& aSourceList, const CQikMediaFile& aDestination);
	IMPORT_C void SetOperationL(TQikMediaOperation aOperation, const CArrayPtrFlat<CQikMediaFile>& aSourceList);
	IMPORT_C void SetOperationL(TQikMediaOperation aOperation, const TFileName& aFullPath, const CQikMediaFile& aDestination);
	IMPORT_C void RecognizedMediaTypesL(CDesCArray& aMimeTypes);
	IMPORT_C void FilesInFolderL(const TDesC& aFolderName, const TDriveNumber& aDrive, const CArrayPtrFlat<CQikMediaFile>& aAllFilesList, CArrayPtrFlat<CQikMediaFile>& aSelectedFilesList);
	IMPORT_C TFileName CreateFileNameL(const CQikMediaFile& aMediaFile);
	IMPORT_C void SetObserver(MQikMediaFileFolderUtilsObserver* aObserver);
	IMPORT_C void FolderFromMimetypeL(const TDesC& aMimetype, TDes& aFolder);
	IMPORT_C void SetOperationL(TQikMediaOperation aOperation, const CArrayFixFlat<TFileName>& aSourceFiles, const TDriveNumber& aDrive, const TDesC& aFolder);
	IMPORT_C TAny* ExtensionL(TUid aExtensionUid);
	IMPORT_C void FoldersOnDriveL(const MDesCArray& aMimeTypes, CArrayPtrFlat<CQikMediaFile>& aFoldersList,const TDriveNumber& aDrive);
	void CancelOperation();
	void UpdateProgressBarL();
	void StopSaving();	
protected: // from CActive
	virtual void DoCancel();
	virtual void RunL();

	// From MFileManObserver
	MFileManObserver::TControl NotifyFileManStarted();
	MFileManObserver::TControl NotifyFileManOperation();
	MFileManObserver::TControl NotifyFileManEnded();

private:
	CQikMediaFileFolderUtils(CEikonEnv& aEikEnv);
	void ConstructL();
	void ReadFoldersAndMimeTypesFromResourceL();
	void CreateDefaultFoldersL();
	TBool CheckIfMimeTypeExists(const TDesC& aMimeType);
	void FilesInOtherL(const TPath& aMediaPath, const TInt& aDrive, CArrayPtrFlat<CQikMediaFile>& aRecognizedFilesList, const MDesCArray& aMimeTypes, const TBool aUnrecognized, CArrayPtrFlat<CQikExtensionMimeType>* aExtensionMimeType);
	void PhysicalFolderFromMimetype(const TDesC& aMimeType, const TInt& aDrive, TDes& aFolder);
	TInt MemoryAvailable(const TFileName& aSourceName, const TFileName& aDestinationName);
	TInt PerformFileOperationL(TFileName& aSource, const TFileName& aDestination);
	TInt PerformOperationL();
	TInt FileOperationL();
	TInt RenameMoveFolderL();
	TInt AddDeleteFolderL();
	TQikMediaFileType FileTypeFromMediaType(const TDesC& aMediaType, const TDriveNumber aDrive);
	void PhysicalPathFromMediaFileL(const CQikMediaFile& aMediaFile, TDes& aFolder);
	TBool CheckMimeType(const TDesC& aMimeType, const MDesCArray& aMimeTypes);
	TPtrC MimeTypeL(const TPtrC aFileName, CArrayPtrFlat<CQikExtensionMimeType>* aExtensionMimeType) const;
	TDataRecognitionResult MimeType(const TPtrC aFileName) const;
	void NextOperationL();
	void ShowProgressDialogL(TInt aFinalValue = 0);
	void UpdateProgressL();
	TInt CheckDriveForOperationL(const TDriveNumber aDriveNumber, TBool& aIsReadOnly);
	void ShowInfoWinL(TInt aResId) const;
	static TInt CallUpdateProgressbarFunctionL(TAny* aObject);
	void StartProgressTimerL(TInt aTimerIntervall);
private:
	CEikonEnv& iEikEnv;
	CFileMan* iFileMan;
	RApaLsSession iLsSession;
	CDataTypeArray* iSystemMediaTypes;
	CDesCArrayFlat* iInternalFolders;
	CDesCArrayFlat* iExternalFolders;
	CDesCArrayFlat* iRecognizedMimeTypes;
	CArrayPtrFlat<CQikExtensionMimeType>* iExtensionMimeTypeDefault;
	CArrayFixFlat<TInt>* iFolderIds;
	TQikMediaOperation iOperation;
	CArrayPtrFlat<CQikMediaFile>* iSourceArray;

public:
	MQikMediaFileFolderUtilsObserver* iFileFolderUtilsObserver;

private:
	TFileName iSource;
	CQikMediaFile* iDestinationFile;
	HBufC* iInternalMediaPath;
	HBufC* iExternalMediaPath;
	HBufC* iDefaultFolder;
	TInt iNumberOfElements;
	TInt iIndex;
	TInt iNotUsed;
	TInt iResourceFileOffsetQikDlg;
	TInt iResourceFileOffsetQEikStd;
	CArrayFixFlat<TFileName>* iSourceExternalArray;
	CQikUtilsProgressDialog* iProgressDlg;
	TBool iDeleteSourceDir;
	TInt iMsgId;
	TBool iCancelled;
	TBool iOkToStart;
	CPeriodic* iProgressTimer;
	TInt iBytesTransfered;
	TInt iSaveFileSize;
	TBool iStopSaving;
	RArray<TAny*> iExtensions;
	};

/** 
* This class is used to get an abstract description of a file location. It gives the drive, 
* the mimeType, the folder, and the name of the file, CQikMediaFileFolderUtils uses the class to 
* recreate the real physical path to the external media the drive is mounted on.
*/
class CQikMediaFile : public CBase
	{
public:
	IMPORT_C static CQikMediaFile* NewL(TDriveNumber aDrive, const TDesC& aMimeType, const TDesC& aFolder, const TDesC& aName, TInt aSize);
	IMPORT_C static CQikMediaFile* NewL(TDriveNumber aDrive, const TDesC& aMimeType, const TDesC& aFolder, const TDesC& aName, TInt aSize, TQikMediaFileType aType);
	IMPORT_C ~CQikMediaFile();
	IMPORT_C TDriveNumber Drive() const;
	IMPORT_C const TDesC& MimeType() const;
	IMPORT_C const TDesC& Folder() const;
	IMPORT_C const TDesC& Name() const;
	IMPORT_C TInt Size() const;
	IMPORT_C TQikMediaFileType FileType() const;
	void SetMimeTypeL(const TDesC& aMimeType);
	void SetFileTypeL(TQikMediaFileType aType);

private:
	CQikMediaFile();
	CQikMediaFile(TDriveNumber aDrive, TInt aSize);
	void ConstructL(const TDesC& aMimeType, const TDesC& aFolder, const TDesC& aName, TQikMediaFileType aType);
	
private:
	TDriveNumber iDrive;
	HBufC* iMimeType;
	HBufC* iFolder;
	HBufC* iName;
	TInt iSize;
	TQikMediaFileType iFileType;
	TInt iSpare;			// Not used.
	};


/**
* CQikUtilsProgressDialog
* 
* Presents a progress dialog to the user, when doing an operation.
* The cancel button is removed when uninstalling.
*/
class CQikUtilsProgressDialog : public CEikDialog
	{
public:
	CQikUtilsProgressDialog(TQikMediaOperation aOperation, CQikMediaFileFolderUtils* aMediaUtils);
	virtual ~CQikUtilsProgressDialog();
public:
	void PreLayoutDynInitL();
	void EndDialogL();
	void SetProgressFinalValue(TInt aValue);
	void UpdateProgress(TInt aValue);
	void SetTextL(const TDesC& aText);
private:
	//TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	TBool OkToExitL(TInt aButtonId);
	TBool ShutL();
private:
	TQikMediaOperation iOperation;
	CQikMediaFileFolderUtils* iMediaUtils;
	};

#endif //__QIKMEDIAFILEFOLDERUTILS_H__
