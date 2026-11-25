// EIKCFDLG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCFDLG_H__)
#define __EIKCFDLG_H__

#if !defined(__EIKDIALG_H__)
#include <eikdialg.h>
#endif

class CEikFileOpenDialog : public CEikDialog
	{
public:
	IMPORT_C CEikFileOpenDialog(TDes* aFileName, TInt aTitleId=0);
	IMPORT_C void SetShowSystem(TBool aShowSystem);
	IMPORT_C void SetRequiredUid(const TUidType& aUidType);
	IMPORT_C void SetRequiredExtension(const TDesC* aExtension);
	IMPORT_C void RestrictToNativeDocumentFiles();
protected: // from CEikDialog
	IMPORT_C void PreLayoutDynInitL();
	IMPORT_C TBool OkToExitL(TInt aButtonId);
protected: // new function
	IMPORT_C void HandleBrowseButtonL();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TDes* iFileName;
	TUidType iUidType;
	TDesC* iExtension;
	TBool iShowSystem;
	TInt iTitleId;
	RFs iFs;
	};


class CEikFileSaveAsDialog : public CEikDialog
	{
public:
	IMPORT_C CEikFileSaveAsDialog(TDes* aFileName,TBool* aUseNewFile=NULL,TInt aTitleId=0,TBool aAppendExtension=EFalse);
	IMPORT_C CEikFileSaveAsDialog(TDes* aFileName,const TDesC* aTitle,TBool* aUseNewFile=NULL,TBool aAppendExtension=EFalse);
	IMPORT_C static TBool RunDlgLD(	TDes* aFileName,
									TBool* aUseNewFile=NULL,
									TInt aTitleId=0,
									TBool aAppendExtension=EFalse);
protected: // from CEikDialog
	IMPORT_C TBool OkToExitL(TInt aButtonId);
	IMPORT_C void PreLayoutDynInitL();
protected: // new
	IMPORT_C void HandleBrowseButtonL();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TDes* iFileName;
	TBool* iUseNewFile;
	TInt iTitleId;
	const TDesC* iTitle;
	TBool iAppendExtension;
	RFs iFs;
	};

// 
// CEikScreenCaptureDialog
//

class CEikScreenCaptureDialog : public CEikFileSaveAsDialog
	{
public:
	IMPORT_C static TBool RunDlgLD(
									TDes*	aFileName, 
									TBool&	aSaveAsMonochromeImage, 
									TInt	aTitleId=0);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: 
	CEikScreenCaptureDialog(
							TDes* aFileName, 
							TBool& aSaveAsMonochromeImage, 
							TInt aTitleId=0);
	// inherited
	TBool OkToExitL(TInt aButtonId);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TBool& iSaveAsMonochrome;
	TInt iSpare;
	};

#endif
