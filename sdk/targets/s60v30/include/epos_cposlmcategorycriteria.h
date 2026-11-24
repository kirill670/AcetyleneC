/*
* ==============================================================================
*  Name        : EPos_CPosLmCategoryCriteria.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks Search API
*  Description :
*     See class description below
*  Version     : 1.9    2005/03/14 12:20:52
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

#ifndef CPOSLMCATEGORYCRITERIA_H
#define CPOSLMCATEGORYCRITERIA_H

//  INCLUDES
#include <e32base.h>
#include <EPos_Landmarks.h>

#include "EPos_CPosLmSearchCriteria.h"

// CLASS DECLARATION

/**
*  Criterion used for searching for landmarks which belong to a certain
*  category.
*
*  A category has an ID in the database and it has also a unique name. There
*  are also some global categories which are known by all databases. It is
*  possible to specify either a local category in a specific landmark
*  database, a global category or the name of the category. If one is set,
*  the others are reset and not used.
*
*  It is also possible to search for uncategorized landmarks, i.e. landmarks
*  which do not contain any categories. If neither item ID, global ID nor name
*  are set, then @ref CPosLandmarkSearch::StartLandmarkSearchL will search for
*  uncategorized landmarks.
*
*  This criterion is only valid when searching for landmarks, i.e. if it
*  is passed to @p CPosLandmarkSearch::StartCategorySearchL, the function
*  will fail with error code @p KErrArgument.
*
*  @version $Revision: 1.9 $, $Date: 2005/03/14 12:20:52 $
*/
class CPosLmCategoryCriteria : public CPosLmSearchCriteria
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLmCategoryCriteria* NewLC();

        /**
        * Destructor.
        */
        virtual ~CPosLmCategoryCriteria();

    public: // New functions

        /**
        * Returns the item ID of the category which should be used as
        * landmark search criterion.
        *
        * @return The item ID of the category or @p KPosLmNullItemId
        *   if not set.
        */
        IMPORT_C TPosLmItemId CategoryItemId() const;

        /**
        * Returns the global category which should be used as landmark search
        * criterion.
        *
        * @return The global category or @p KPosLmNullGlobalCategory if not
        *   set.
        */
        IMPORT_C TPosLmGlobalCategory GlobalCategory() const;

        /**
        * Returns the name of the category which should be used as landmark
        * search criterion.
        *
        * @return The category name or empty descriptor if not
        *   set.
        */
        IMPORT_C TPtrC CategoryName() const;

        /**
        * Sets the item ID of the category which should be used as landmark
        * search criterion.
        *
        * Passing @p KPosLmNullItemId means uncategorized landmarks search.
        *
        * @param aItemId The item ID of the category.
        */
        IMPORT_C void SetCategoryItemId(
        /* IN  */       TPosLmItemId  aItemId
        );

        /**
        * Sets the global category which should be used as landmark search
        * criterion.
        *
        * Passing @p KPosLmNullGlobalCategory means uncategorized landmarks
        * search.
        *
        * @param aGlobalCategory The global category.
        */
        IMPORT_C void SetGlobalCategory(
        /* IN  */       TPosLmGlobalCategory  aGlobalCategory
        );

        /**
        * Sets the name of the category which should be used as landmark
        * search criterion.
        *
        * The exact category name must be specified. Wild-card characters are
        * not used as such, they will be considered as ordinary characters.
        * It is possible to use @ref CPosLmCatNameCriteria to
        * list categories which match a category name pattern containing
        * wild-card characters.
        *
        * The matching is case sensitive.
        *
        * An empty descriptor means uncategorized landmarks search.
        *
        * If the category name is longer than @p KPosLmMaxCategoryNameLength,
        * this function will leave with error code @p KErrArgument.
        *
        * @param aCategoryName The category name.
        */
        IMPORT_C void SetCategoryNameL(
        /* IN  */       const TDesC&  aCategoryName
        );

    private:

        CPosLmCategoryCriteria();

        void ConstructL();

        // By default, prohibit copy constructor
        CPosLmCategoryCriteria( const CPosLmCategoryCriteria& );
        // Prohibit assigment operator
        CPosLmCategoryCriteria& operator= ( const CPosLmCategoryCriteria& );

    private:    // Data

        TPosLmItemId            iItemId;
        TPosLmGlobalCategory    iGlobalCategory;
        HBufC*                  iCategoryName;

    };

#endif      // CPOSLMCATEGORYCRITERIA_H

// End of File
