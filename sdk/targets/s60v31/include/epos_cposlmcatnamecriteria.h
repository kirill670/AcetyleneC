/*
* ==============================================================================
*  Name        : EPos_CPosLmCatNameCriteria.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks Search API
*  Description :
*     See class description below
*  Version     : 1.6    2005/03/14 12:27:16
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

#ifndef CPOSLMCATNAMECRITERIA_H
#define CPOSLMCATNAMECRITERIA_H

//  INCLUDES
#include <e32base.h>
#include "EPos_CPosLmSearchCriteria.h"

// CLASS DECLARATION

/**
*  Criterion for searching landmark categories with a certain name.
*
*  Wild-card characters are supported.
*
*  The client specifies the search pattern and starts the search using
*  @ref CPosLandmarkSearch. The search returns all categories which
*  match the search pattern.
*
*  This criterion is only valid when searching for landmark categories, i.e. if
*  it is passed to @p CPosLandmarkSearch::StartLandmarkSearchL, the function
*  will fail with error code @p KErrArgument.
*
*  @version $Revision: 1.6 $, $Date: 2005/03/14 12:27:16 $
*/
class CPosLmCatNameCriteria : public CPosLmSearchCriteria
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLmCatNameCriteria* NewLC();

        /**
        * Destructor.
        */
        virtual ~CPosLmCatNameCriteria();

    public: // New functions

        /**
        * Retrieves the search pattern.
        *
        * @return The category name search pattern.
        */
        IMPORT_C TPtrC SearchPattern() const;

        /**
        * Sets the search pattern.
        *
        * A non-empty search pattern must be set, otherwise
        * @ref CPosLandmarkSearch::StartCategorySearchL will leave with error
        * code @p KErrArgument.
        *
        * The search is case insensitive.
        *
        * Wild-card characters "?" and "*" are supported in the search string.
        * "?" matches a single occurrence of any character and "*" matches
        * zero or more consecutive occurrences of any characters.
        *
        * If the search pattern is longer than @p KPosLmMaxCategoryNameLength,
        * this function will leave with error code @p KErrArgument.
        *
        * @param aSearchPattern The pattern used to find categories.
        */
        IMPORT_C void SetSearchPatternL(
        /* IN  */       const TDesC&  aSearchPattern
        );


    private:

        CPosLmCatNameCriteria();

        void ConstructL();

        // By default, prohibit copy constructor
        CPosLmCatNameCriteria( const CPosLmCatNameCriteria& );
        // Prohibit assigment operator
        CPosLmCatNameCriteria& operator= ( const CPosLmCatNameCriteria& );

    private:    // Data

        HBufC* iSearchPattern;

    };

// CPOSLMCATNAMECRITERIA_H
#endif

// End of File
