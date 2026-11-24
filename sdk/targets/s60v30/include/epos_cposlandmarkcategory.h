/*
* ==============================================================================
*  Name        : EPos_CPosLandmarkCategory.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks API
*  Description :
*     See class description below
*  Version     : 1.13    2005/07/07 13:40:48
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

#ifndef CPOSLANDMARKCATEGORY_H
#define CPOSLANDMARKCATEGORY_H

//  INCLUDES
#include <e32base.h>
#include "EPos_Landmarks.h"

// CLASS DECLARATION

/**
*  Landmark category.
*
*  A landmark database can contain a number of categories which can be
*  assigned to the landmarks in the database. A landmark can be associated
*  with multiple categories, e.g. a landmark can be a "Restaurant" and a "Pub".
*  Categories also enable filtered searches, e.g. a client could search for
*  nearby restaurants.
*
*  This class specifies the landmark category attributes, i.e. name, icon and
*  a global category identifier. Global categories enable a uniform
*  categorization across multiple databases.
*
*  A landmark category is created, updated or deleted by using functions in
*  @ref CPosLmCategoryManager.
*
*  @lib eposlandmarks.lib
*  @since S60 3.0
*  @version $Revision: 1.13 $, $Date: 2005/07/07 13:40:48 $
*/
class CPosLandmarkCategory : public CBase
    {
    public:  // Data types

        /**
        *  Bitmap for specifying a group of category attributes. Bit values are
        *  defined by _TAttributes.
        *
        *  @since S60 3.0
        *  @version $Revision: 1.13 $, $Date: 2005/07/07 13:40:48 $
        */
        typedef TUint32 TAttributes;

        /**
        *  Specifies a category attribute, e.g. category name or category icon.
        *
        *  @since S60 3.0
        *  @version $Revision: 1.13 $, $Date: 2005/07/07 13:40:48 $
        */
        enum _TAttributes
            {
            ENoAttribute        = 0x0000  /**<
                No attribute specified. */,
            ECategoryName       = 0x0001  /**<
                The name of the landmark category. */,
            EIcon               = 0x0010  /**<
                The icon that represents the category in a UI. */,
            EAllAttributes      = 0xFFFF  /**<
                All category attributes. */
            };

    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLandmarkCategory* NewLC();

        /**
        * Two-phased constructor.
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLandmarkCategory* NewL();

        /**
        * Two-phased copy constructor.
        *
        * @param aCategory The category to copy.
        * @returns A copy of the specified category object.
        */
        IMPORT_C static CPosLandmarkCategory* NewLC(
        /* IN  */       const CPosLandmarkCategory&  aCategory
        );

        /**
        * Two-phased copy constructor.
        *
        * @param aCategory The category to copy.
        * @returns A copy of the specified category object.
        */
        IMPORT_C static CPosLandmarkCategory* NewL(
        /* IN  */       const CPosLandmarkCategory&  aCategory
        );

        /**
        * Destructor.
        */
        virtual ~CPosLandmarkCategory();

    public: // New functions

        /**
        * Reads the ID of the category entry in the database.
        *
        * @since S60 3.0
        * @returns The ID of the category entry in the database, or
        *   @p KPosLmNullItemId if the category has not been added to the
        *   database yet.
        */
        IMPORT_C TPosLmItemId CategoryId() const;

        /**
        * Checks if the category is globally defined (i.e. not only in one
        * database)
        *
        * Global categories enable a uniform categorization across multiple
        * databases.
        *
        * @since S60 3.0
        * @returns The global category or @p KPosLmNullGlobalCategory if the
        *   category is not global.
        */
        IMPORT_C TPosLmGlobalCategory GlobalCategory() const;

        /**
        * \internal
        *
        * Sets the category to be global (i.e. not only defined in one
        * database).
        *
        * Global categories enable a uniform categorization across multiple
        * databases.
        *
        * @since S60 3.0
        * @param aGlobalCategory The global category ID or
        *   @p KPosLmNullGlobalCategory if the category should not be global.
        */
        void SetGlobalCategory(
        /* IN  */       TPosLmGlobalCategory  aGlobalCategory
        );

        /**
        * Reads the name of the landmark category.
        *
        * @since S60 3.0
        * @param aCategoryName Will contain the category name.
        * @returns @p KErrNone if successful, @p KErrNotFound if the category
        *   name is not set.
        */
        IMPORT_C TInt GetCategoryName(
        /* OUT */       TPtrC&  aCategoryName
        ) const;

        /**
        * Sets the name of the landmark category.
        *
        * If the client passes an empty descriptor, this function will leave
        * with error code @p KErrArgument.
        *
        * If the name of the landmark is longer than
        * @p KPosLmMaxCategoryNameLength, this function will leave with error
        * code @p KErrArgument.
        *
        * @since S60 3.0
        * @param aCategoryName The category name.
        */
        IMPORT_C void SetCategoryNameL(
        /* IN  */       const TDesC&  aCategoryName
        );

        /**
        * Associates the landmark category with an icon.
        *
        * Icons are found in icon files. To set an icon, the client
        * must specify the name of the icon file and the index of the
        * icon within the file.
        *
        * The landmark is not affected if the icon file is changed or
        * removed. It only contains a link to the icon.
        *
        * If the icon file name is longer than @p KMaxFileName,
        * this function will leave with error code @p KErrArgument.
        *
        * If the icon index is negative,
        * this function will panic with @p EPosLmInvalidArgument.
        *
        * If the icon mask index is negative and
        * not equal to @p KPosLmIconMaskNotUsed,
        * this function will panic with @p EPosLmInvalidArgument.
        *
        * @since S60 3.0
        * @param aIconFileName The full icon file name.
        * @param aIconIndex The index of the icon within the icon file.
        * @param aIconMaskIndex The index of the icon mask within the
        *   icon file.
        */
        IMPORT_C void SetIconL(
        /* IN  */       const TDesC&  aIconFileName,
        /* IN  */       TInt  aIconIndex,
        /* IN  */       TInt  aIconMaskIndex
        );

        /**
        * Returns the a link to the icon associated with the landmark category.
        *
        * Icons are found in icon files. It is referenced by the name of
        * the icon file and the index of the icon within the file.
        *
        * The landmark category is not affected if the icon file is
        * changed or removed. It only contains a link to the icon. This means
        * that the link could be invalid.
        *
        * @since S60 3.0
        * @param aIconFileName The full icon file name.
        * @param aIconIndex The index of the icon within the icon file.
        * @param aIconMaskIndex The index of the icon mask within the
        *   icon file. If no icon mask index is defined @p KPosLmIconMaskNotUsed
        *   is returned.
        * @returns @p KErrNone if successful, @p KErrNotFound if the icon is
        *   not set.
        */
        IMPORT_C TInt GetIcon(
        /* OUT */       TPtrC& aIconFileName,
        /* OUT */       TInt&  aIconIndex,
        /* OUT */       TInt&  aIconMaskIndex
        ) const;

        /**
        * Removes landmark attributes from the landmark category, e.g. category
        * name.
        *
        * @since S60 3.0
        * @param aAttributes A bitmap specifying which category attributes to
        *   remove.
        */
        IMPORT_C void RemoveCategoryAttributes(
        /* IN  */       TAttributes  aAttributes
        );

        /*
        * \internal
        *
        * Sets the category ID to the landmark category.
        *
        * This function is not supposed to be used by clients.
        *
        * @param aId The category ID to set.
        */
        void SetCategoryIdL(
        /* IN  */       TPosLmItemId aId
        );

    private:

        /**
        * C++ default constructor.
        */
        CPosLandmarkCategory();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();
        void ConstructL(const CPosLandmarkCategory& aCategory);

        // Prohibit copy constructor
        CPosLandmarkCategory(const CPosLandmarkCategory&);

        // Prohibit assigment operator
        CPosLandmarkCategory& operator= (const CPosLandmarkCategory&);

    private:    // Data

        // Category ID
        TPosLmItemId iId;

        // Global category
        TPosLmGlobalCategory iGlobalCategory;

        // Category label
        HBufC* iCategoryName;

        // Category icon filename
        HBufC* iIconFileName;

        // Category icon index
        TInt iIconIndex;

        // Category icon mask index
        TInt iIconMaskIndex;
    };

#endif      // CPOSLANDMARKCATEGORY_H

// End of File
