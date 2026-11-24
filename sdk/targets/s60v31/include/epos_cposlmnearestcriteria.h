/*
* ==============================================================================
*  Name        : EPos_CPosLmNearestCriteria.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks Search API
*  Description :
*     See class description below
*  Version     : 1.14    2005/03/14 13:12:09
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

#ifndef CPOSLMNEARESTCRITERIA_H
#define CPOSLMNEARESTCRITERIA_H

//  INCLUDES
#include <e32base.h>
#include <LbsPosition.h>
#include "EPos_CPosLmSearchCriteria.h"

// CLASS DECLARATION

/**
*  Criterion for finding the landmarks which are closest to a certain
*  coordinate, called "center coordinate".
*
*  When using @ref CPosLmNearestCriteria, the matches returned in the search
*  are sorted in ascending distance order if the client does not specify
*  other sort preferences.
*
*  By default, this search returns all landmarks in the database, except
*  those which have no coordinates. It is recommended to specify a maximum
*  distance to narrow down the search. This is done by @ref SetMaxDistance.
*
*  The client can specify if the coverage radius should be used.
*  If coverage radius is used, the distance to the landmark coverage area
*  border is used instead of the distance to the landmark coverage area
*  center. If the source coordinate is inside the landmark coverage area,
*  the distance is considered zero. By default, the coverage radius is not
*  used.
*
*  This criterion is only valid when searching for landmarks, i.e. if it
*  is passed to @p CPosLandmarkSearch::StartCategorySearchL, the function
*  will fail with error code @p KErrArgument.
*
*  @version $Revision: 1.14 $, $Date: 2005/03/14 13:12:09 $
*/
class CPosLmNearestCriteria : public CPosLmSearchCriteria
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * Latitude and longitude must be set in the coordinate (not NaN),
        * otherwise this function will panic with code @p EPosNaNCoordinate.
        * Altitude is ignored.
        *
        * @param aCoordinate The center coordinate of the landmark search.
        * @param aUseCoverageRadius @p ETrue if coverage radius should be
        *   considered in the search.
        */
        IMPORT_C static CPosLmNearestCriteria* NewLC(
        /* IN  */       const TCoordinate&  aCoordinate,
        /* IN  */       TBool  aUseCoverageRadius = EFalse
        );

        /**
        * Destructor.
        */
        virtual ~CPosLmNearestCriteria();

    public: // New functions

        /**
        * Returns the center coordinate of the search.
        *
        * @param aCoordinate On return, contains the center coordinate.
        */
        IMPORT_C void GetCoordinate(
        /* OUT */       TCoordinate&  aCoordinate
        ) const;

        /**
        * Set the center coordinate of the search.
        *
        * Latitude and longitude must be set in the coordinate (not NaN),
        * otherwise this function will panic with code @p EPosNaNCoordinate.
        * Altitude is ignored.
        *
        * @param aCoordinate The center coordinate of the landmarks search.
        */
        IMPORT_C void SetCoordinate(
        /* IN  */       const TCoordinate&  aCoordinate
        );

        /**
        * Returns if coverage radius is considered in the search.
        *
        * @return @p ETrue if coverage radius is considered in the search.
        *   @p EFalse otherwise.
        */
        IMPORT_C TBool UseCoverageRadius() const;

        /**
        * Set if coverage radius should be considered in the search.
        *
        * @param aUseCoverageRadius @p ETrue if coverage radius should be
        *   considered in the search. @p EFalse otherwise.
        */
        IMPORT_C void SetUseCoverageRadius(
        /* IN  */       TBool  aUseCoverageRadius
        );

        /**
        * Returns whether the search should be limited to landmarks which are
        * closer than a maximum distance.
        *
        * By default the maximum distance is set to NaN which means that the
        * distance is unlimited.
        *
        * @return The maximum distance or NaN if the distance is unlimited.
        */
        IMPORT_C TReal32 MaxDistance() const;

        /**
        * Set a maximum distance for the search.
        *
        * Only landmarks, which are closer to the center coordinate than the
        * maximum distance are considered matches.
        *
        * @param aMaxDistance The maximum distance or NaN if the distance
        *   should be unlimited.
        */
        IMPORT_C void SetMaxDistance(
        /* IN  */       TReal32  aMaxDistance
        );

    private:

        CPosLmNearestCriteria(TBool aUseCoverageRadius);

        void ConstructL(const TCoordinate& aCoordinate);

        // By default, prohibit copy constructor
        CPosLmNearestCriteria( const CPosLmNearestCriteria& );
        // Prohibit assigment operator
        CPosLmNearestCriteria& operator= ( const CPosLmNearestCriteria& );

    private:    // Data

        TCoordinate iCenterCoordinate;
        TBool       iUseCoverageRadius;
        TReal32     iMaxDistance;

    };

// CPOSLMNEARESTCRITERIA_H
#endif

// End of File
