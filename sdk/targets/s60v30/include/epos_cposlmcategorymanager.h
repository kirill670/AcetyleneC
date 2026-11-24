/*
* ==============================================================================
*  Name        : EPos_CPosLmCategoryManager.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks API
*  Description :
*     See class description below
*  Version     : 1.15    2005/07/07 13:40:47
*
*  Copyright (c) 2002-2005 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
*
* ==============================================================================
*/

#ifndef CPOSLMCATEGORYMANAGER_H
#define CPOSLMCATEGORYMANAGER_H

//  INCLUDES
#include <e32base.h>
#include "EPos_CPosLandmarkDatabase.h"
#include "EPos_CPosLandmarkCategory.h"
#include "EPos_CPosLmItemIterator.h"
#include "EPos_CPosLmOperation.h"

// CLASS DECLARATION

/**
*  Category management for a landmark database.
*
*  A landmark database can contain a number of categories which can be
*  assigned to the landmarks in the database. A landmark can be associated
*  with multiple categories, e.g. a landmark can be a "Restaurant" and a "Pub".
*  Categories also enable filtered searches, e.g. a client could search for
*  nearby restaurants.
*
*  This class contains functions for managing landmark categories. This includes
*  reading, listing, creating and updating landmark categories.
*
*  To use this class, link against @p eposlandmarks.lib.
*
*  @p NetworkServices capability is required for remote databases.
*
*  @lib eposlandmarks.lib
*  @since S60 3.0
*  @version $Revision: 1.15 $, $Date: 2005/07/07 13:40:47 $
*/
class CPosLmCategoryManager : public CBase
    {
    public:  // Data types

        /**
        *  Specifies the sort preference for landmark categories.
        *
        *  @since S60 3.0
        *  @version $Revision: 1.15 $, $Date: 2005/07/07 13:40:47 $
        */
        enum TCategorySortPref
            {
            ECategorySortOrderNone = 0        /**<
                Categories not sorted */,
            ECategorySortOrderNameAscending   /**<
                Sorted ascending by category name. */,
            ECategorySortOrderNameDescending  /**<
                Sorted descending by category name. */
            };

    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * The client takes ownership of the category manager.
        *
        * @since S60 3.0
        * @param aLandmarkDatabase The landmark database to manage categories
        *   in.
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLmCategoryManager* NewL(
        /* IN  */       CPosLandmarkDatabase&  aLandmarkDatabase
        );

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CPosLmCategoryManager();

    public: // New functions

        /**
        * Reads a landmark category from the database.
        *
        * If the landmark category does not exist in the database, this method
        * leaves with @p KErrNotFound.
        *
        * The client takes ownership of the returned category object.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aCategoryId The ID of the landmark category to read.
        * @returns The requested landmark category. The category object is put
        *   on the cleanup stack.
        */
        virtual CPosLandmarkCategory* ReadCategoryLC(
        /* IN  */       TPosLmItemId  aCategoryId
        ) = 0;

        /**
        * Returns an object for iterating the landmark categories in the
        * database.
        *
        * The iterator object is reset, so that the first
        * @ref CPosLmItemIterator::NextL call will return the first landmark
        * category.
        *
        * The client takes ownership of the returned iterator object.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aSortPref How to sort the categories. Default is no sorting.
        * @return The landmark iterator.
        */
        virtual CPosLmItemIterator* CategoryIteratorL(
        /* IN  */       TCategorySortPref  aSortPref = ECategorySortOrderNone
        ) = 0;

        /**
        * Returns an object for iterating referenced landmark categories in
        * the database.
        *
        * A category is referenced if there are landmarks in the database which
        * contains this category.
        *
        * The iterator object is reset, so that the first
        * @ref CPosLmItemIterator::NextL call will return the first landmark
        * category.
        *
        * The client takes ownership of the returned iterator object.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aSortPref How to sort the categories. Default is no sorting.
        * @return The landmark iterator.
        */
        virtual CPosLmItemIterator* ReferencedCategoryIteratorL(
        /* IN  */       TCategorySortPref  aSortPref = ECategorySortOrderNone
        ) = 0;

        /**
        * Adds a landmark category to the database and returns its ID.
        *
        * The input category object must have a name set, otherwise this
        * function will leave with error code @p KErrArgument.
        *
        * This function will leave with code @p KErrAlreadyExists if a category
        * with the same name already exists in the database.
        *
        * The client is not allowed to create global categories, so if a global
        * category is set in the category object, this function will leave with
        * @p KErrArgument.
        *
        * If the database is read only, this method leaves with
        * @p KErrAccessDenied.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aCategory The landmark category to add.
        * @return The ID of the new category.
        */
        virtual TPosLmItemId AddCategoryL(
        /* IN OUT */    CPosLandmarkCategory&  aCategory
        ) = 0;

        /**
        * Updates a landmark category in the database.
        *
        * The input category object must have a name set, otherwise this
        * function will leave with error code @p KErrArgument.
        *
        * This function will leave with code @p KErrAlreadyExists if another
        * category with the same name exists in the database.
        *
        * The client is not allowed to change the global category identifier in
        * the category object. If this value has been changed, this function
        * will leave with @p KErrArgument.
        *
        * If the database is read only, this method leaves with
        * @p KErrAccessDenied.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aCategory The new landmark category data.
        */
        virtual void UpdateCategoryL(
        /* IN  */       const CPosLandmarkCategory&  aCategory
        ) = 0;

        /**
        * Removes a landmark category from the database.
        *
        * If the landmark category does not exist in the database, nothing
        * happens.
        *
        * If the database is read only, this operation will fail with error
        * code @p KErrAccessDenied.
        *
        * This call will also remove the category from all landmarks which
        * contained it.
        *
        * The function returns an operation object which can be run in either
        * synchronous or asynchronous mode. If it is run in asynchronous mode
        * the client can supervise the progress of the operation.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, it is possible that the category has not been removed,
        * but some landmarks may no longer contain this category
        *
        * The client takes ownership of the returned operation object.
        *
        * While removing the category, this operation will acquire a
        * write-lock on the database.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aCategoryId The ID of the landmark category to delete.
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* RemoveCategoryL(
        /* IN  */       TPosLmItemId  aCategoryId
        ) = 0;

        /**
        * Remove a set of landmark categories from the database.
        *
        * If any of the landmark categories does not exist in the database, it
        * is ignored.
        *
        * This call will also remove the categories from all landmarks which
        * contained them.
        *
        * The function returns an operation object which can be run in either
        * synchronous or asynchronous mode. If it is run in asynchronous mode
        * the client can supervise the progress of the operation.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, it is possible that only a subset of the landmark
        * categories have been deleted.
        *
        * The client takes ownership of the returned operation object.
        *
        * If the database is read only, this operation will fail with error
        * code @p KErrAccessDenied.
        *
        * This call will also remove the categories from all landmarks which
        * contained them.
        *
        * While removing the category, this operation will acquire a
        * write-lock on the database.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aCategoryIdArray The IDs of the landmark categories to delete.
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* RemoveCategoriesL(
        /* IN  */       const RArray<TPosLmItemId>&  aCategoryIdArray
        ) = 0;

        /**
        * Adds a category to a set of landmarks.
        *
        * If the specified category does not exist, this operation will fail
        * with error code @p KErrNotFound.
        *
        * If any of the specified landmarks does not exist, the category will
        * be added to the other landmarks. No error will be reported though.
        *
        * If the category is already contained in one of the landmarks, nothing
        * will be further added to that landmark.
        *
        * The function returns an operation object which can be run in either
        * synchronous or asynchronous mode. If it is run in asynchronous mode
        * the client can supervise the progress of the operation.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, it is possible that the category has only been added
        * to a subset of the landmarks.
        *
        * The client takes ownership of the returned operation object.
        *
        * Note: There is no need to call
        * @p CPosLandmarkDatabase::UpdateLandmark for this change to take
        * place.
        *
        * If the database is read only, this operation will fail with error
        * code @p KErrAccessDenied.
        *
        * While adding the category to the landmarks, this operation will
        * acquire a write-lock on the database.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aCategoryId The category to add to the set of landmarks.
        * @param aLandmarkIdArray The landmarks to add the category to.
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* AddCategoryToLandmarksL(
        /* IN  */       TPosLmItemId  aCategoryId,
        /* IN  */       RArray<TPosLmItemId>&  aLandmarkIdArray
        ) = 0;

        /**
        * Removes a category from a set of landmarks.
        *
        * If the specified category does not exist, this operation will fail
        * with error code @p KErrNotFound.
        *
        * If any of the specified landmarks does not exist, the category will
        * be removed from the other landmarks. No error will be reported though.
        *
        * If the category is not found in one of the landmarks, nothing will
        * happen for that landmark.
        *
        * The function returns an operation object which can be run in either
        * synchronous or asynchronous mode. If it is run in asynchronous mode
        * the client can supervise the progress of the operation.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, it is possible that the category has only been removed
        * from a subset of the landmarks.
        *
        * The client takes ownership of the returned operation object.
        *
        * If the database is read only, this operation will fail with error
        * code @p KErrAccessDenied.
        *
        * While removing the category from the landmarks, this operation will
        * acquire a write-lock on the database.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aCategoryId The category to remove from the set of landmarks.
        * @param aLandmarkIdArray The landmarks to remove the category from.
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* RemoveCategoryFromLandmarksL(
        /* IN  */       TPosLmItemId  aCategoryId,
        /* IN  */       RArray<TPosLmItemId>&  aLandmarkIdArray
        ) = 0;

        /**
        * Gets a category by name.
        *
        * The category name must be unique in the database, so there cannot be
        * multiple matches.
        *
        * This get function only looks for an exact match.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aCategoryName The name of the category to get.
        * @return @p KPosLmNullItemId if the category was not found, otherwise
        *   the ID of the category item in the database.
        */
        virtual TPosLmItemId GetCategoryL(
        /* IN  */       const TDesC&  aCategoryName
        ) = 0;

        /**
        * Gets the ID of a global category.
        *
        * This function requires @p ReadUserData capability.
        *
        * @param aGlobalCategory The global category to look for.
        * @return @p KPosLmNullItemId if the category was not found, otherwise
        *   the ID of the category item in the database.
        *
        * @since S60 3.0
        */
        virtual TPosLmItemId GetGlobalCategoryL(
        /* IN  */       TPosLmGlobalCategory  aGlobalCategory
        ) = 0;

        /**
        * Gets the predefined name of a global category.
        *
        * If the global category is not recognized, this function will return
        * @p NULL.
        *
        * @since S60 3.0
        * @param aGlobalCategory The global category to get a name for.
        * @return The name of the global category or @p NULL if the category
        *   is not recognized.
        */
        virtual HBufC* GlobalCategoryNameL(
        /* IN  */       TPosLmGlobalCategory  aGlobalCategory
        ) = 0;

        /**
        * Resets the information for all global categories.
        *
        * Global categories usually has a default name and icon. The client
        * can change the name and icon. This function resets the name and
        * icon to the default ones.
        *
        * The function returns an operation object which can be run in either
        * synchronous or asynchronous mode. If it is run in asynchronous mode
        * the client can supervise the progress of the operation.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, it is possible that that only a subset of the global
        * categories have been resetted.
        *
        * The client takes ownership of the returned operation object.
        *
        * If the database is read only, this operation will fail with error
        * code @p KErrAccessDenied.
        *
        * While resetting, this operation will acquire a write-lock on the
        * database.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* ResetGlobalCategoriesL() = 0;

    protected:

        /**
        * C++ default constructor.
        */
        IMPORT_C CPosLmCategoryManager();

    private:

        // By default, prohibit copy constructor
        CPosLmCategoryManager( const CPosLmCategoryManager& );
        // Prohibit assigment operator
        CPosLmCategoryManager& operator= ( const CPosLmCategoryManager& );

    private:    // Data

        // Implementation UID
        TUid iDtorIdKey;

    };

#endif      // CPOSLMCATEGORYMANAGER_H

// End of File
