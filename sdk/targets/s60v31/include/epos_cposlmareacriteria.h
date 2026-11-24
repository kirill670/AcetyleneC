/*
* ==============================================================================
*  Name        : EPos_CPosLmAreaCriteria.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks Search API
*  Description :
*     See class description below
*  Version     : 1.7    2005/03/14 12:56:16
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

#ifndef CPOSLMAREACRITERIA_H
#define CPOSLMAREACRITERIA_H

//  INCLUDES
#include <e32base.h>
#include "EPos_CPosLmSearchCriteria.h"

// CLASS DECLARATION

/**
*  Criterion for searching for landmarks which reside in a certain area.
*
*  The search area is defined by providing two latitude and two longitude
*  values which specify the borders of the area. Note that this search
*  does not consider landmark coverage radius, see
*  @p CPosLandmark::GetCoverageRadius.
*
*  The search area is defined as a spherical rectangle, limited by two
*  longitude borders (WestLongitude and EastLongitude) and two latitude
*  borders (SouthLatitude and NorthLatitude).
*
*  It is required that -90 =< SouthLatitude =< NorthLatitude =< 90.
*  WestLongitude must be in the interval [-180, 180), i.e. not including +180.
*  EastLongitude must be in the interval [-180, 180], i.e. including +180.
*  It is allowed that EastLongitude < WestLongitude. This defines an area
*  which crosses the 180 meridian. The area definition is inclusive, i.e.
*  landmarks which lie on the border of the area will be considered as matches.
*  If WestLongitude = EastLongitude and NorthLatitude = SouthLatitude then
*  only landmarks which match the longitude and latitude respectively, are
*  considered to be matches. If WestLongitude = -180 and EastLongitude = +180,
*  all longitudes are included in the search.
*
*  This criterion is only valid when searching for landmarks, i.e. if it
*  is passed to @p CPosLandmarkSearch::StartCategorySearchL, the function
*  will fail with error code @p KErrArgument.
*
*  @version $Revision: 1.7 $, $Date: 2005/03/14 12:56:16 $
*/
class CPosLmAreaCriteria : public CPosLmSearchCriteria
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * The input parameters specify the area to search as described
        * in the class description.
        *
        * If one of the parameters is out of range, this function fails with
        * error code @p KErrArgument. The correct ranges are:
        *   -# -90 =< aSouthLatitude =< aNorthLatitude =< 90
        *   -# -180 <= aWestLongitude < 180
        *   -# -180 <= aEastLongitude <= 180
        *
        * @param aSouthLatitude The southern latitude border of the search area.
        * @param aNorthLatitude The northern latitude border of the search area.
        * @param aWestLongitude The western longitude border of the search area.
        * @param aEastLongitude The eastern longitude border of the search area.
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLmAreaCriteria* NewLC(
        /* IN  */       const TReal64&  aSouthLatitude,
        /* IN  */       const TReal64&  aNorthLatitude,
        /* IN  */       const TReal64&  aWestLongitude,
        /* IN  */       const TReal64&  aEastLongitude
        );

        /**
        * Destructor.
        */
        virtual ~CPosLmAreaCriteria();

    public: // New functions

        /**
        * Returns the search area.
        *
        * @param aSouthLatitude The southern latitude border of the search area.
        * @param aNorthLatitude The northern latitude border of the search area.
        * @param aWestLongitude The western longitude border of the search area.
        * @param aEastLongitude The eastern longitude border of the search area.
        */
        IMPORT_C void GetSearchArea(
        /* OUT */       TReal64&  aSouthLatitude,
        /* OUT */       TReal64&  aNorthLatitude,
        /* OUT */       TReal64&  aWestLongitude,
        /* OUT */       TReal64&  aEastLongitude
        ) const;

        /**
        * Define the search area.
        *
        * The input parameters specify the area to search as described in the
        * class description.
        *
        * If one of the parameters is out of range, this function fails with
        * error code @p KErrArgument. The correct ranges are:
        *   -# -90 =< aSouthLatitude =< aNorthLatitude =< 90
        *   -# -180 <= aWestLongitude < 180
        *   -# -180 <= aEastLongitude <= 180
        *
        * @param aSouthLatitude The southern latitude border of the search area.
        * @param aNorthLatitude The northern latitude border of the search area.
        * @param aWestLongitude The western longitude border of the search area.
        * @param aEastLongitude The eastern longitude border of the search area.
        * @returns @p KErrNone if successful, @p KErrArgument if the input
        *   parameters are invalid, otherwise a system wide error code.
        */
        IMPORT_C TInt SetSearchArea(
        /* IN  */       const TReal64&  aSouthLatitude,
        /* IN  */       const TReal64&  aNorthLatitude,
        /* IN  */       const TReal64&  aWestLongitude,
        /* IN  */       const TReal64&  aEastLongitude
        );

    private:

        CPosLmAreaCriteria();

        void ConstructL(
        /* IN  */       const TReal64&  aSouthLatitude,
        /* IN  */       const TReal64&  aNorthLatitude,
        /* IN  */       const TReal64&  aWestLongitude,
        /* IN  */       const TReal64&  aEastLongitude
        );

        // By default, prohibit copy constructor
        CPosLmAreaCriteria( const CPosLmAreaCriteria& );
        // Prohibit assigment operator
        CPosLmAreaCriteria& operator= ( const CPosLmAreaCriteria& );

    private:    // Data

        TReal64 iSouthLatitude;
        TReal64 iNorthLatitude;
        TReal64 iWestLongitude;
        TReal64 iEastLongitude;

    };

// CPOSLMAREACRITERIA_H
#endif

// End of File
