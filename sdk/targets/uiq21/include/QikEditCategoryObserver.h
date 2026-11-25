// QikEditCategoryObserver.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
// Created for Quartz 6.0


#ifndef __EDITCATEGORYOBSERVER_H__
#define __EDITCATEGORYOBSERVER_H__

/**
 * The MQikEditCategoryObserver class defines the interface used by the Edit Categories
 * dialogs. The application using categories should implement this interface and take
 * appropriate actions when called. It is up to the application to make sure that there
 * are no inconsistencies between the CategoryModel and the categorized items after these
 * methods have been called.
 * 
 * @short	Defines the interface required by the Edit Category dialogs.
 */
class MQikEditCategoryObserver
	{
public: // Pure virtual calback members
	/** Return ETrue if the user shall be allowed to add a category, otherwise EFalse. */
	virtual TBool	OkToAddCategory() const = 0;
	/** Do add the new category. Change the value of the parameter aHandle if necessary. 
	    Return ETrue if the operation was successful, otherwise EFalse. */
	virtual TBool	DoAddCategoryL( TInt& aHandle ) = 0;

	/** Return ETrue if the user shall be allowed to rename the category, otherwise EFalse. */
	virtual TBool	OkToRenameCategory( TInt aHandle, const TDesC& aNewName ) const = 0;
	/** Gives the application the option to do changes to its categorized items.
		If ETrue is returned, the category identified by aHandle will be given the aNewName name. */
	virtual TBool	DoRenameCategoryL( TInt aHandle, const TDesC& aNewName ) = 0;

	/** Return ETrue if the user shall be allowed to merge the categories, otherwise EFalse. */
	virtual TBool	OkToMergeCategories( TInt aSourceHandle, TInt aTargetHandle ) const = 0;
	/** When called, the application shall move all items in the aSourceHandle category
		to the aTargetHandle category and return ETrue.	If ETrue is returned, the category 
		identified by aSourceHandle will be deleted, after a call to DoDeleteCategoryL(). 
		If EFalse is returned, the merge is canceled. */
	virtual TBool	DoMergeCategoriesL( TInt aSourceHandle, TInt aTargetHandle ) = 0;

	/** Return ETrue if the user shall be allowed to delete the category, otherwise EFalse. */
	virtual TBool	OkToDeleteCategory( TInt aHandle ) const = 0;
	/** When called, the application should move all items in this category to the Unfiled category.
		If ETrue is returned, the category identified by aHandle will be deleted. */
	virtual TBool	DoDeleteCategoryL( TInt aHandle ) = 0;

	/** Return ETrue if the category is empty. Otherwise EFalse. */
	virtual TBool	IsCategoryEmpty( TInt aHandle ) const = 0;
	};



#endif //__EDITCATEGORYOBSERVER_H__
