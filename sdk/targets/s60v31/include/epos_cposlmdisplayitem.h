/*
* ==============================================================================
*  Name        : EPos_CPosLmDisplayItem.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks Search API
*  Description :
*     See class description below
*  Version     : 1.9    2005/03/14 14:32:33
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

#ifndef CPOSLMDISPLAYITEM_H
#define CPOSLMDISPLAYITEM_H

//  INCLUDES
#include <e32base.h>

// FORWARD DECLARATIONS
class CPosLandmark;
class CPosLandmarkCategory;

// CLASS DECLARATION

/**
* Displayable item.
*
* A displayable item consists of a landmark or category and its database
* index. Database index is 0 if running single database search, and it is
* in the range [0, @ref CPosLmMultiDbSearch::NumOfDatabasesInSearch - 1] in
* case of multiple database search. Thus, this class is a link between a
* landmark or a category and its database.
*
* The class is usually not instantiated by client applications.
*
* @version $Revision: 1.9 $, $Date: 2005/03/14 14:32:33 $
*/
class CPosLmDisplayItem : public CBase
    {

    public:  // Data types

    /**
    * Display item type.
    */
    enum TDisplayItemType
        {
        ELandmarkItem = 0       /**< Landmark display item. This indicates
                                * that the item contains a landmark and the
                                * @ref Landmark function can be called to
                                * access it.
                                */,
        ECategoryItem           /**< Category display item. This indicates
                                * that the item contains a category and the
                                * @ref Category function can be called to
                                * access it.
                                */
        };

    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * @param aLandmark A landmark.
        * @param aDatabaseIndex A database index.
        *
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLmDisplayItem* NewL(
        /* IN */        CPosLandmark* aLandmark,
        /* IN */        TUint aDatabaseIndex = 0
        );

        /**
        * Two-phased constructor.
        *
        * @param aCategory A category.
        * @param aDatabaseIndex A database index.
        *
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLmDisplayItem* NewL(
        /* IN */        CPosLandmarkCategory* aCategory,
        /* IN */        TUint aDatabaseIndex = 0
        );

        /**
        * Destructor.
        */
        virtual ~CPosLmDisplayItem();

    public:  // New functions

        /**
        * Returns the type of the display item.
        *
        * @return The display item type.
        */
        IMPORT_C TDisplayItemType DisplayItemType() const;

        /**
        * Returns the index of the database, which contained item belongs to.
        *
        * The database index is associated with a database URI from the list
        * of databases specified in @ref CPosLmMultiDbSearch.
        *
        * If display data is used in @ref CPosLandmarkSearch, this
        * function always returns 0.
        *
        * @return The database index of this displayable item.
        */
        IMPORT_C TUint DatabaseIndex() const;

        /**
        * Returns the category contained in the displayable item.
        *
        * This function panics with @p EPosInvalidItemType if the item type
        * is not a category displayable item. See @ref DisplayItemType.
        *
        * @return The category.
        */
        IMPORT_C const CPosLandmarkCategory& Category() const;

        /**
        * Returns the landmark contained in the displayable item.
        *
        * This function panics with @p EPosInvalidItemType if the item type
        * is not a landmark displayable item. See @ref DisplayItemType.
        *
        * @return The landmark.
        */
        IMPORT_C const CPosLandmark& Landmark() const;

        /**
        * Returns the distance to a position specified in the
        * @ref CPosLmNearestCriteria. The distance data is only used when
        * searching with this criteria.
        *
        * @param aDistance Distance to the position specified in a
        *   @ref CPosLmNearestCriteria.
        * @return KErrNone if distance is available. KErrNotFound otherwise.
        */
        IMPORT_C TInt GetDistance(
        /* OUT */       TReal32& aDistance
        ) const;

        /*
        * Sets the database index of this displayable item.
        *
        * @param aDatabaseIndex The database index.
        */
        void SetDatabaseIndex(
        /* IN */        TUint aDatabaseIndex
        );

        /*
        * Sets the distance to the position specified in the nearest criterion.
        *
        * @param aDistance Distance to the position.
        */
        void SetDistance(
        /* IN */        TReal32 aDistance
        );

    private:

        /**
        * C++ default constructor.
        *
        * @param aLandmark A landmark.
        * @param aDatabaseIndex Database index.
        */
        CPosLmDisplayItem(
        /* IN */        CPosLandmark* aLandmark,
        /* IN */        TUint aDatabaseIndex
        );

        /**
        * C++ default constructor.
        *
        * @param aCategory A category.
        * @param aDatabaseIndex Database index.
        */
        CPosLmDisplayItem(
        /* IN */        CPosLandmarkCategory* aCategory,
        /* IN */        TUint aDatabaseIndex
        );

    private:    // Data

        TDisplayItemType iDisplayItemType;

        CPosLandmark* iLandmark;

        CPosLandmarkCategory* iCategory;

        TUint iDatabaseIndex;

        TReal32 iDistance;

        TBool iHasDistance;

    };

// CPOSLMDISPLAYITEM_H
#endif

// End of File
