// QikCategoryModel.h
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
// Created for Quartz 6.0

#ifndef __QIKCATEGORYMODEL_H__
#define __QIKCATEGORYMODEL_H__

#include <e32base.h>	// CArrayPtrFlat
#include <s32strm.h>	// RReadStream, RWriteStream
#include <qikon.hrh>	// EQikCategoryNameMaxLength

class TResourceReader;
class CQikCategory;
class CEikonEnv;

typedef TBufC<EQikCategoryNameMaxLength> TQikCategoryName;

/**
 * This class holds data about the categories a user can choose between when categorizing
 * application specific items. To categorize an application item, the application should
 * associate that item with the category handle taken from this model. When changes is made
 * to the data in this model using e.g. the Edit Categories dialogs, the application is
 * notified about the changes through the MQikEditCategoryObserver. When a user change
 * category using the category menu pane, the application is notified through the
 * interface specified by the MQikCategoryMenuObserver implemented by the CQikAppUi class.
 *
 * @see MQikEditCategoryObserver, CQikAppUi, MQikCategoryMenuObserver
 */
class CQikCategoryModel : public CBase
	{
public:
	enum TValidateNameResult
		{
		ENameIsOK,
		ENameNotAllowed,
		ENameAlreadyExist,
		ENameNoChange
		};

public:
	IMPORT_C static CQikCategoryModel* NewL();
	IMPORT_C static CQikCategoryModel* NewLC();
	IMPORT_C ~CQikCategoryModel();
	IMPORT_C void SetSorted(TBool aSort);
	IMPORT_C TBool Sorted() const;
	IMPORT_C void SetDeleteOnlyEmpty(TBool aDelete);
	IMPORT_C TBool DeleteOnlyEmpty() const;

	// Methods to iterate over all categories
	IMPORT_C TInt CountCategories() const;
	IMPORT_C const TQikCategoryName& CategoryNameByIndex(TInt aIndex) const;
	IMPORT_C TInt CategoryHandle(TInt aIndex) const;

	// Methods for getting category related data
	IMPORT_C TInt CategoryHandle(const TDesC& aCategoryName) const;
	IMPORT_C const TQikCategoryName& CategoryNameByHandle( TInt aHandle ) const;
	IMPORT_C TInt HandleOfAllCategory() const;
	IMPORT_C TInt HandleOfUnfiledCategory() const;
	IMPORT_C TInt CategoryIndex(TInt aHandle) const;

	IMPORT_C TBool IsCategoryHiddenInList(TInt aIndex) const;			// Hidden in list of categories to edit, typically e.g. the All category
	IMPORT_C void SetCategoryHiddenInList(TInt aHandle, TBool aHidden);
	IMPORT_C TBool CanCategoryBeRenamed(TInt aHandle) const;
	IMPORT_C void SetCategoryRenameable(TInt aHandle, TBool aRenameable);
	IMPORT_C TBool CanCategoryBeDeleted(TInt aHandle) const;
	IMPORT_C void SetCategoryDeleteable(TInt aHandle, TBool aDeleteable);
	IMPORT_C TBool IsCategoryDimmedInMenu(TInt aHandle) const;
	IMPORT_C void SetCategoryDimmedInMenu(TInt aHandle, TBool aDimmed);
	IMPORT_C TInt16 CategorySortedAs(TInt aHandle);
	IMPORT_C void SetCategorySortedAs(TInt aHandle, TInt16 aSortedAs);
	IMPORT_C TInt32& AppDefinedFlags(TInt aHandle);
	IMPORT_C TValidateNameResult ValidCategoryName(const TDesC& aName, const TDesC* aOldName = NULL) const;

	// Methods to read categories from resource and ini files
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

	// Methods to handle adding, removing, and deleting categories. These are normally only used by the category dialogs.
	IMPORT_C TInt& AddCategoryL(const TDesC& aName, TInt16 aFlags = 0);
	IMPORT_C TInt& AddCategoryL(TInt aHandle, const TDesC& aName, TInt16 aFlags = 0);
	IMPORT_C void DeleteCategoryL(TInt aHandle);
	IMPORT_C void RenameCategoryL(TInt aHandle, const TDesC& aNewName);
	IMPORT_C TBool CheckModelIntegrity() const;

private:
	CQikCategoryModel();
	void ConstructL();
	TInt NewCategoryHandle() const;
	void DoSort();

private:
	enum TCategoryFlags
		{
		ECategoryFlagSort = 0x01,
		ECategoryFlagDeleteOnlyEmpty = 0x02
		};

	CArrayPtrFlat<CQikCategory>* iCategories;
	TInt iFlags;
	mutable TInt iCachedIndex;
	CEikonEnv* iEikEnv; 
	};


class CDictionaryStore;
class TResourceReader;


const TInt KNoCategoryResource = -1;
const TInt KCategoryNullStream = 0;


class QikCategoryUtils
	{
public:
	IMPORT_C static CQikCategoryModel* ConstructCategoriesLC( TInt aCategoryResourceId = KNoCategoryResource, TUid aCategoryStreamId = TUid::Uid(KCategoryNullStream) );
	IMPORT_C static void LoadCategoriesFromResourceL( CQikCategoryModel& aCategoryModel, TInt aCategoryResourceId, TResourceReader* aResourceReader = NULL );
	IMPORT_C static TBool LoadCategoriesFromIniFileL( CQikCategoryModel& aCategoryModel, TUid aCategoryStreamId, const CDictionaryStore* aStore = NULL );
	IMPORT_C static void SaveCategoriesToIniFileL( const CQikCategoryModel& aCategoryModel, TUid aCategoryStreamId, CDictionaryStore* aStore = NULL );
private:
	QikCategoryUtils();
	~QikCategoryUtils();
	};



#endif // __QIKCATEGORYMODEL_H__
