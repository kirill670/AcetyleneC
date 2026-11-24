/*
* ==============================================================================
*  Name        : EPos_CPosLmPartialReadParameters.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks API
*  Description :
*     See class description below
*  Version     : 1.8    2005/07/07 13:40:47
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

#ifndef CPOSLMPARTIALREADPARAMETERS_H
#define CPOSLMPARTIALREADPARAMETERS_H

//  INCLUDES
#include <e32base.h>
#include <LbsFields.h>
#include "EPos_CPosLandmark.h"

// CLASS DECLARATION

/**
*  Container class for partial landmark settings.
*  Partial settings are used to define which landmark data should be returned
*  when @ref CPosLandmarkDatabase::ReadPartialLandmarkLC is called.
*
*  @lib eposlandmarks.lib
*  @since S60 3.0
*  @version $Revision: 1.8 $, $Date: 2005/07/07 13:40:47 $
*/
class CPosLmPartialReadParameters : public CBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLmPartialReadParameters* NewLC();

        /**
        * Destructor.
        */
        virtual ~CPosLmPartialReadParameters();

    public: // New functions

        /**
        * Returns a bitmap of the landmark attributes which should be included
        * in a partial landmark.
        *
        * The bitmap is a combination of the values in
        * CPosLandmark::TAttribute.
        *
        * @since S60 3.0
        * @return The partial landmark attributes bitmap.
        */
        IMPORT_C CPosLandmark::TAttributes RequestedAttributes() const;

        /**
        * Sets a bitmap of the landmark attributes which should be included in
        * a partial landmark.
        *
        * The bitmap is constructed from the values in
        * CPosLandmark::TAttribute.
        *
        * @since S60 3.0
        * @param aAttributes A partial landmark attributes bitmap.
        */
        IMPORT_C void SetRequestedAttributes(
        /* IN  */       CPosLandmark::TAttributes  aAttributes
        );

        /**
        * Returns the position fields which should be included in a partial
        * landmark.
        *
        * @since S60 3.0
        * @param aRequestedFields Will contain the requested position fields,
        *   i.e. @p TPositionFieldId.
        * @returns @p KErrNone if successful, otherwise one of the system wide
        *   error codes.
        */
        IMPORT_C TInt GetRequestedPositionFields(
        /* OUT */       RArray<TUint>&  aRequestedFields
        ) const;

        /**
        * Sets the position fields which should be included in a partial
        * landmark.
        *
        * @since S60 3.0
        * @param aRequestedFields The requested position fields, i.e.
        *   @p TPositionFieldId.
        * @returns @p KErrNone if successful, otherwise one of the system wide
        *   error codes.
        */
        IMPORT_C TInt SetRequestedPositionFields(
        /* IN */       const RArray<TUint>&  aRequestedFields
        );

    private:

        /**
        * C++ default constructor.
        */
        CPosLmPartialReadParameters();

        /**
        * By default EPOC constructor is private.
        */
        void ConstructL();

        // By default, prohibit copy constructor
        CPosLmPartialReadParameters(
            const CPosLmPartialReadParameters& );
        // Prohibit assigment operator
        CPosLmPartialReadParameters& operator= (
            const CPosLmPartialReadParameters& );

    private:    // Data

        // Requested position fields
        RArray<TUint> iRequestedFields;

        // Requested attributes
        TUint32 iAttributes;
    };

#endif      // CPOSLMPARTIALREADPARAMETERS_H

// End of File
