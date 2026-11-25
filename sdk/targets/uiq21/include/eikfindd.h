// EIKFINDD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKFINDD_H__)
#define __EIKFINDD_H__

#if !defined(__EIKDIALG_H__)
#include <eikdialg.h>
#endif

#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#if !defined(__EIKGTED_H__)
#include <eikgted.h>
#endif

class CEikEdwinFindDialog : public CEikDialog  
	{
public:
	IMPORT_C static TBool RunDlgLD(	SEdwinFindModel*	aModel,
									CDesCArray*			aFindList);
	IMPORT_C static TBool RunDlgLD(	SEdwinFindModel*	aModel);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	CEikEdwinFindDialog(SEdwinFindModel* aModel);
	void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikDialog
	IMPORT_C void CreateButtonGroupContainerL(TInt aResourceId);
	IMPORT_C void Reserved_4();
private:
	SEdwinFindModel* iModel;
	};


//
// Replace dialog class
//

class CEikEdwinReplaceDialog : public CEikDialog  
	{
public:
	IMPORT_C static TBool RunDlgLD(	SEdwinFindModel*	aFindModel,
									CDesCArray*			aFindList,
									CDesCArray*			aReplaceList);
	IMPORT_C static TBool RunDlgLD(	SEdwinFindModel*	aFindModel);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	CEikEdwinReplaceDialog(SEdwinFindModel* aModel);
	void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikDialog
	IMPORT_C void CreateButtonGroupContainerL(TInt aResourceId);
	IMPORT_C void Reserved_4();
private:
	SEdwinFindModel* iModel;
	};


//
// Replace option dialog class
//

class CEikEdwinReplaceOptionDialog : public CEikDialog  
	{
public:
	IMPORT_C static TBool RunDlgLD(	
									CEikGlobalTextEditor*	aEdwin,
									SEdwinFindModel*		aModel);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	CEikEdwinReplaceOptionDialog(CEikGlobalTextEditor* aEdwin,SEdwinFindModel* aModel);
    TBool OkToExitL(TInt aButtonId);
	void ReplacePressed();
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikDialog
	IMPORT_C void CreateButtonGroupContainerL(TInt aResourceId);
	IMPORT_C void Reserved_4();
private:
	CEikGlobalTextEditor* iEdwin;
	SEdwinFindModel* iModel;
	};


#endif
