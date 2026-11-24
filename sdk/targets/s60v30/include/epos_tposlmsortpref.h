/*
* ==============================================================================
*  Name        : EPos_TPosLmSortPref.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks API
*  Description :
*     See class description below
*  Version     : 1.11    2005/07/07 13:40:47
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

#ifndef TPOSLMSORTPREF_H
#define TPOSLMSORTPREF_H

//  INCLUDES
#include <e32base.h>
#include "EPos_CPosLandmark.h"

// CLASS DECLARATION

/**
*  Class for specifying sort preference.
*
*  A sort pref object can be passed to some listing and searching functions in
*  the API, to specify a sorting order for the returned landmark list.
*
*  Landmark sorting is not case sensitive.
*
*  @lib eposlandmarks.lib
*  @since S60 3.0
*  @version $Revision: 1.11 $, $Date: 2005/07/07 13:40:47 $
*/
class TPosLmSortPref
    {
    public:  // Data types

        /**
        *  Specifies the sort order.
        *
        *  @since S60 3.0
        *  @version $Revision: 1.11 $, $Date: 2005/07/07 13:40:47 $
        */
        enum TSortOrder
            {
            EAscending = 0  /**< Ascending sort order */,
            EDescending     /**< Descending sort order */
            };

    public:  // Constructors

        /**
        * C++ default constructor.
        *
        * Only one landmark attribute can be specified here, not a bitmap
        * of landmark attributes. If more than one attribute is specified,
        * or if no attributes are specified, this function will panic with
        * error code @p EPosNoneOrMultipleLandmarkAttributeSet.
        *
        * Landmark sorting is not case sensitive.
        *
        * @since S60 3.0
        * @param aLandmarkAttribute The landmark attribute to sort by.
        * @param aSortOrder Ascending or descending sort order.
        */
        IMPORT_C TPosLmSortPref(
        /* IN  */       CPosLandmark::TAttributes  aLandmarkAttribute,
        /* IN  */       TSortOrder  aSortOrder = EAscending
        );

    public: // New functions

        /**
        * Gets the preferred sort order.
        *
        * @since S60 3.0
        * @return The preferred sort order.
        */
        IMPORT_C TSortOrder SortOrder() const;

        /**
        * Gets the landmark attribute to sort by.
        *
        * @since S60 3.0
        * @return The landmark attribute to sort by, or
        *   @p CPosLandmark::ENoAttribute, if sort is not done by landmark
        *   attribute.
        */
        IMPORT_C CPosLandmark::TAttributes LandmarkAttributeToSortBy() const;

        /**
        * Sets the landmark attribute to sort by.
        *
        * Only one landmark attribute can be specified here, not a bitmap
        * of landmark attributes. If more than one attribute is specified,
        * or if no attributes are specified, this function will panic with
        * error code @p EPosNoneOrMultipleLandmarkAttributeSet.
        *
        * Landmark sorting is not case sensitive.
        *
        * @since S60 3.0
        * @param aLandmarkAttribute The landmark attribute to sort by.
        * @param aSortOrder The preferred sort order.
        */
        IMPORT_C void SetSortByLandmarkAttribute(
        /* IN  */       CPosLandmark::TAttributes  aLandmarkAttribute,
        /* IN  */       TSortOrder  aSortOrder = EAscending
        );

    private:

        TSortOrder iSortOrder;
        CPosLandmark::TAttributes iLandmarkAttribute;
        TUint8 iUnusedData[16];

    };

#endif      // TPOSLMSORTPREF_H

// End of File
