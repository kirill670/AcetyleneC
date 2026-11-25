// QikEditCategoriesDlg.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
// Created for Quartz 6.0

#ifndef __QIKEDITCATEGORIESDLG_H__
#define __QIKEDITCATEGORIESDLG_H__

#include <eikdialg.h>
#include <badesca.h>

class CQikCategoryModel;
class MQikEditCategoryObserver;

/**
 * Dialog that lets the user add and edit categories.
 *
 * @since Quartz 6.0
 */
class CQikEditCategoriesDialog : public CEikDialog
	{
public:
	IMPORT_C static TBool RunDlgLD(	CQikCategoryModel* aCategoryModel, MQikEditCategoryObserver* aObserver );
protected:
	IMPORT_C CQikEditCategoriesDialog( CQikCategoryModel* aCategoryModel, MQikEditCategoryObserver* aObserver );
	IMPORT_C ~CQikEditCategoriesDialog();
protected:  //From CEikDialog
	IMPORT_C TBool OkToExitL( TInt aButtonId );
	IMPORT_C void PreLayoutDynInitL();
	void PopulateListBoxL();
protected:
	void AddCategoryL();
	void RenameCategoryL();
	TBool DeleteCategoryL();
	TInt Index(TInt aCategoryHandle) const;
protected:
	IMPORT_C virtual void RunAddDialogL() const;
	IMPORT_C virtual void RunRenameDialogL() const;
	IMPORT_C virtual TBool RunDeleteDialogL() const;
protected:
	CQikCategoryModel* iCategoryModel;	//allows access to category information
	MQikEditCategoryObserver* iCategoryObserver;
	CDesCArrayFlat* iCategoryNames;		//array of categories, shared with the choicelist in the dialog
	CArrayFixFlat<TInt>* iCategoryHandles;
	TInt iCurrentHandle;
	};


/**
 * Dialog that lets the user add a category.
 *
 * @since Quartz 6.0
 * @internal
 */
class CQikAddCategoryDialog : public CEikDialog
	{
public:	
	CQikAddCategoryDialog( CQikCategoryModel* aCategoryModel, MQikEditCategoryObserver*	aCategoryObserver );
	~CQikAddCategoryDialog();
protected:  //From CEikDialog
	TBool OkToExitL(TInt aButtonId);
protected:
	TBool CheckNameL( const TDesC& aName );
protected:
	CQikCategoryModel* iCategoryModel;	//allows access to category information
	MQikEditCategoryObserver* iObserver;
	};


/**
 * Dialog that lets the user delete and rename a selected category.
 *
 * @since Quartz 6.0
 * @internal
 */
class CQikRenameCategoryDialog : public CEikDialog
	{
public:
	CQikRenameCategoryDialog( CQikCategoryModel* aModel, MQikEditCategoryObserver* aObserver, TInt aCategoryHandle );
	~CQikRenameCategoryDialog();
protected:  //From CEikDialog
	TBool OkToExitL(TInt aButtonId);
	void PreLayoutDynInitL();
protected:
	TBool RenameCategoryL();
protected:
	CQikCategoryModel* iCategoryModel;	//allows access to category information
	MQikEditCategoryObserver* iCategoryObserver;
	TInt iCategoryHandle;	//the selected category
	};

#endif	// __QIKEDITCATEGORIESDLG_H__
