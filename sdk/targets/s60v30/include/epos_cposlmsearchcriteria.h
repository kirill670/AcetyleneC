/*
* ==============================================================================
*  Name        : EPos_CPosLmSearchCriteria.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks Search API
*  Description :
*     See class description below
*  Version     : 1.7    2005/03/14 10:27:30
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

#ifndef CPOSLMSEARCHCRITERIA_H
#define CPOSLMSEARCHCRITERIA_H

//  INCLUDES
#include <e32base.h>

// CLASS DECLARATION

/**
*  Abstract base class for landmark search criterion classes.
*
*  Criterion classes are used in @ref CPosLandmarkSearch to specify what to
*  search for. It specifies what criteria the landmark must fulfill to be
*  considered a search match.
*
*  @version $Revision: 1.7 $, $Date: 2005/03/14 10:27:30 $
*/
class CPosLmSearchCriteria : public CBase
    {
    public:  // Data types

        /**
        *  Specifies the subclass of the criterion object.
        *
        *  @version $Revision: 1.7 $, $Date: 2005/03/14 10:27:30 $
        */
        enum TCriteriaType
            {
            ECriteriaArea = 0     /**< subclass CPosLmAreaCriteria */,
            ECriteriaText         /**< subclass CPosLmTextCriteria */,
            ECriteriaComposite    /**< subclass CPosLmCompositeCriteria */,
            ECriteriaCategory     /**< subclass CPosLmCategoryCriteria */,
            ECriteriaFindNearest  /**< subclass CPosLmNearestCriteria */,
            ECriteriaIdList       /**< subclass CPosLmIdListCriteria */,

            ECriteriaCategoryByName = 100 /**< subclass CPosLmCatNameCriteria */
            };

    public:  // Constructors and destructor

        /**
        * Destructor.
        */
        virtual ~CPosLmSearchCriteria();

    public:  // New functions

        /**
        * Returns the criterion type.
        *
        * @returns The criterion type.
        */
        IMPORT_C TCriteriaType CriteriaType() const;

    protected:

        /**
        * C++ default constructor.
        */
        CPosLmSearchCriteria(
        /* IN  */       TCriteriaType  aCriteriaType
        );

    private:

        // By default, prohibit copy constructor
        CPosLmSearchCriteria( const CPosLmSearchCriteria& );
        // Prohibit assigment operator
        CPosLmSearchCriteria& operator= ( const CPosLmSearchCriteria& );

    private:    // Data

        TCriteriaType iCriteriaType;

    };

#endif      // CPOSLMSEARCHCRITERIA_H

// End of File
