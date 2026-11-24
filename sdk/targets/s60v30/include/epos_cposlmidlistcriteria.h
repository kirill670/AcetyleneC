/*
* ==============================================================================
*  Name        : EPos_CPosLmIdListCriteria.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks Search API
*  Description :
*
*  Version     : 1.10    2005/03/21 08:01:03
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

#ifndef CPOSLMIDLISTCRITERIA_H
#define CPOSLMIDLISTCRITERIA_H

//  INCLUDES
#include <e32base.h>
#include <EPos_Landmarks.h>
#include "EPos_CPosLmSearchCriteria.h"

// CLASS DECLARATION

/**
*  Landmark ID list search criterion.
*
*  This criterion is used if the client only wants to search a subset of the
*  landmarks in the database.
*
*  This criterion must be combined with other search criteria using a
*  @ref CPosLmCompositeCriteria. It is of no use on its own. If it is not
*  combined with another criterion,
*  @ref CPosLandmarkSearch::StartLandmarkSearchL will fail with error code
*  @p KErrArgument.
*
*  @p Example: If this criterion is combined with a @ref CPosLmTextCriteria,
*  the search operation searches the landmarks specified in the ID list
*  criterion and returns those which match the given text string.
*
*  Only one ID list criterion is allowed in each composite criterion, otherwise
*  @ref CPosLandmarkSearch::StartLandmarkSearchL will fail with error code
*  @p KErrArgument.
*
*  If the criterion does not contain any landmark IDs,
*  @ref CPosLandmarkSearch::StartLandmarkSearchL will fail with error code
*  @p KErrArgument.
*
*  @version $Revision: 1.10 $, $Date: 2005/03/21 08:01:03 $
*/
class CPosLmIdListCriteria : public CPosLmSearchCriteria
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLmIdListCriteria* NewLC();

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CPosLmIdListCriteria();

    public: // New functions

        /**
        * Sets the IDs of the landmarks which should be included in the search.
        *
        * @param aIdArray The IDs of the landmarks which should be included
        *   in the search.
        */
        IMPORT_C void SetLandmarkIdsL(
        /* IN  */       const RArray<TPosLmItemId>&  aIdArray
        );

        /**
        * Retrieves the list of IDs of the landmarks which should be included
        * in the search.
        *
        * @param aIdArray On return, contains the IDs of the landmarks which
        *   should be included in the search.
        */
        IMPORT_C void GetLandmarkIdsL(
        /* OUT */       RArray<TPosLmItemId>&  aIdArray
        ) const;

    private:

        /**
        * C++ default constructor.
        */
        CPosLmIdListCriteria();

        // By default, prohibit copy constructor
        CPosLmIdListCriteria( const CPosLmIdListCriteria& );
        // Prohibit assigment operator
        CPosLmIdListCriteria& operator= ( const CPosLmIdListCriteria& );

    private:  // Data

        RArray<TPosLmItemId> iIdArray;
    };

#endif      // CPOSLMIDLISTCRITERIA_H

// End of File
