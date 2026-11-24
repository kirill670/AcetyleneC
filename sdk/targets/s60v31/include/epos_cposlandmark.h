/*
* ==============================================================================
*  Name        : EPos_CPosLandmark.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks API
*  Description :
*     See class description below
*  Version     : 1.15    2005/07/07 13:40:48
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

#ifndef CPOSLANDMARK_H
#define CPOSLANDMARK_H

//  INCLUDES
#include <e32base.h>
#include <LbsFields.h>
#include <badesca.h>

#include "EPos_Landmarks.h"

// FORWARD DECLARATIONS
class TLocality;

// CLASS DECLARATION

/**
*  This is a container class for a landmark.
*
*  A landmark is principally a location with a name.
*
*  The landmark object can either be created by a client or retrieved from
*  @ref CPosLandmarkDatabase.
*
*  A landmark consists of a number of landmark attributes, e.g. landmark name,
*  landmark position, coverage area, etc.
*
*  A landmark may also contain generic position fields. These position fields
*  are defined in LbsFields.h. Only text fields are supported.
*
*  CPosLandmark contains functions for setting and getting landmark attributes
*  and position fields.
*
*  Note that CPosLandmark is only a local representation of the landmark. To
*  update the database, call @ref CPosLandmarkDatabase::UpdateLandmarkL (or
*  @ref CPosLandmarkDatabase::AddLandmarkL for a new landmark).
*
*  @lib eposlandmarks.lib
*  @since S60 3.0
*  @version $Revision: 1.15 $, $Date: 2005/07/07 13:40:48 $
*/
class CPosLandmark : public CBase
    {
    public:  // Data types

        typedef TUint32 TAttributes;
        /**
        *  Specifies a landmark attribute, e.g. landmark name or landmark
        *  position.
        *
        *  @since S60 3.0
        *  @version $Revision: 1.15 $, $Date: 2005/07/07 13:40:48 $
        */
        enum _TAttributes
            {
            ENoAttribute        = 0x0000  /**<
                No attribute specified. */,
            ELandmarkName       = 0x0001  /**<
                The name of the landmark. */,
            EPosition           = 0x0002  /**<
                The position of the landmark. */,
            ECoverageRadius     = 0x0004  /**<
                The landmark coverage radius. */,
            ECategoryInfo       = 0x0008  /**<
                The categories of the landmark. */,
            EIcon               = 0x0010  /**<
                The icon that represents the landmark in a UI. */,
            EDescription        = 0x0020  /**<
                A description of the landmark. */,
            EAllAttributes      = 0xFFFF  /**<
                All landmark attributes. */
            };

    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLandmark* NewLC();

        /**
        * Two-phased constructor.
        *
        * @returns A new instance of this class.
        */
        IMPORT_C static CPosLandmark* NewL();

        /**
        * Two-phased copy constructor.
        *
        * @param aLandmark The landmark to copy.
        * @returns A copy of the specified landmark object.
        */
        IMPORT_C static CPosLandmark* NewLC(
        /* IN  */       const CPosLandmark&  aLandmark
        );

        /**
        * Two-phased copy constructor.
        *
        * @param aLandmark The landmark to copy.
        * @returns A copy of the specified landmark object.
        */
        IMPORT_C static CPosLandmark* NewL(
        /* IN  */       const CPosLandmark&  aLandmark
        );

        /**
        * Destructor.
        */
        virtual ~CPosLandmark();

    public: // New functions

        /**
        * Reads the ID of the landmark entry in the database.
        *
        * @since S60 3.0
        * @returns The ID of the landmark entry in the database, or
        *   @p KPosLmNullItemId if the landmark has not been added to the
        *   database yet.
        */
        IMPORT_C TPosLmItemId LandmarkId() const;

        /**
        * Checks if the landmark is partial.
        *
        * A client can read partial information about a landmark from the
        * database. This function checks if only partial information is
        * included in the landmark object.
        *
        * For more about partial landmarks, see
        * @ref CPosLandmarkDatabase::ReadPartialLandmarkLC.
        *
        * @since S60 3.0
        * @returns @p EFalse if the landmark contains all the landmark
        *   information, otherwise @p ETrue.
        */
        IMPORT_C TBool IsPartial() const;

        /**
        * Reads the name of the landmark.
        *
        * This function will return error code @p KErrNotFound if the landmark
        * name is not set in this landmark object. This will be the case if
        * the landmark is read from the database using partial read and
        * landmark name is excluded. Note that if a landmark is fully read
        * from the database, the landmark name will always be included. If no
        * name has been set for the landmark in the database, it will
        * have an empty name string "".
        *
        * @since S60 3.0
        * @param aLandmarkName Will contain the landmark name.
        * @returns @p KErrNone if successful, @p KErrNotFound if the landmark
        *   name is not specified.
        */
        IMPORT_C TInt GetLandmarkName(
        /* OUT */       TPtrC&  aLandmarkName
        ) const;

        /**
        * Sets the name of the landmark.
        *
        * If the name of the landmark is longer than
        * @p KPosLmMaxTextFieldLength, this function will leave with error code
        * @p KErrArgument.
        *
        * If no name is set for the landmark when it is written to the database,
        * the landmark in the database will have an empty name string "".
        *
        * @since S60 3.0
        * @param aLandmarkName The landmark name.
        */
        IMPORT_C void SetLandmarkNameL(
        /* IN  */       const TDesC&  aLandmarkName
        );

        /**
        * Reads the landmark position.
        *
        * @since S60 3.0
        * @param aPosition Will contain the landmark position.
        * @returns @p KErrNone if successful, @p KErrNotFound if the landmark
        *   position is not set.
        */
        IMPORT_C TInt GetPosition(
        /* OUT */       TLocality&  aPosition
        ) const;

        /**
        * Sets the landmark position.
        *
        * Only WGS 84 coordinates are allowed. If another datum is used, this
        * function will leave with code @p KErrArgument.
        *
        * Latitude and longitude must be set in the position, otherwise this
        * function will leave with @p KErrArgument.
        *
        * @since S60 3.0
        * @param aPosition The landmark position.
        */
        IMPORT_C void SetPositionL(
        /* IN  */       const TLocality&  aPosition
        );

        /**
        * Reads the landmark coverage radius.
        *
        * Coverage radius is set if the landmark is big, e.g. a city. It
        * defines the size of the area which the landmark represents.
        *
        * @since S60 3.0
        * @param aCoverageRadius Will contain the coverage radius.
        * @returns @p KErrNone if successful, @p KErrNotFound if the landmark
        *   coverage radius is not set.
        */
        IMPORT_C TInt GetCoverageRadius(
        /* OUT */       TReal32&  aCoverageRadius
        ) const;

        /**
        * Sets the landmark coverage radius.
        *
        * Coverage radius is set if the landmark is big, e.g. a city. It
        * defines the size of the area which the landmark represents.
        *
        * If coverage radius is set to NaN, then the coverage radius will be
        * removed.
        *
        * @since S60 3.0
        * @param aCoverageRadius The coverage radius.
        */
        IMPORT_C void SetCoverageRadius(
        /* IN  */       TReal32  aCoverageRadius
        );

        /**
        * Adds a category to the landmark.
        *
        * If the specified category has already been added, nothing happens.
        *
        * @since S60 3.0
        * @param aCategoryId The category to add
        */
        IMPORT_C void AddCategoryL(
        /* IN  */       TPosLmItemId  aCategoryId
        );

        /**
        * Removes a category from the landmark.
        *
        * If the specified category is not in the landmark, nothing happens.
        *
        * @since S60 3.0
        * @param aCategoryId The category to remove
        */
        IMPORT_C void RemoveCategory(
        /* IN  */       TPosLmItemId  aCategoryId
        );

        /**
        * Retrieves the database item IDs for the categories contained in this
        * landmark.
        *
        * @since S60 3.0
        * @param aCategoryIdArray Will contain the categories.
        */
        IMPORT_C void GetCategoriesL(
        /* OUT */       RArray<TPosLmItemId>&  aCategoryIdArray
        ) const;

        /**
        * Checks if the landmark contains a specific position field.
        *
        * @since S60 3.0
        * @param aFieldId The position field.
        * @returns @p ETrue if the landmark contains the field, otherwise
        *   @p EFalse.
        */
        IMPORT_C TBool IsPositionFieldAvailable(
        /* IN  */       TPositionFieldId  aFieldId
        ) const;

        /**
        * Returns the number of position fields set in the landmark.
        *
        * @since S60 3.0
        * @returns The number of position fields set in the landmark.
        */
        IMPORT_C TUint NumOfAvailablePositionFields() const;

        /**
        * Returns the first position field contained in the landmark.
        *
        * This function is used to initiate iteration over the position fields.
        * @ref NextPositionFieldId is called to continue the iteration.
        *
        * @since S60 3.0
        * @returns The first position field contained by the landmark, or
        *   @p EPositionFieldNone if there are no position fields in the
        *   landmark.
        */
        IMPORT_C TPositionFieldId FirstPositionFieldId() const;

        /**
        * Returns the next position field contained in the landmark.
        *
        * This function is used to iterate the position fields in the landmark.
        * @ref FirstPositionFieldId is called to get the first ID. This ID is
        * passed to @ref NextPositionFieldId to obtain the second ID, etc.
        *
        * If the client specifies an ID which is not contained in the landmark,
        * this function will panic with code @p EPosInvalidPositionFieldId. It
        * is therefore important that the client does not remove the current
        * field while iterating. If the client still removes the current field,
        * the client must pass the previous field.
        *
        * @since S60 3.0
        * @param aFieldId The last position field which was read.
        * @returns The next position field contained by the landmark, or
        *   @p EPositionFieldNone if there are no more position fields in the
        *   landmark.
        */
        IMPORT_C TPositionFieldId NextPositionFieldId(
        /* IN  */       TPositionFieldId  aFieldId
        ) const;

        /**
        * Reads the value of a position field.
        *
        * @since S60 3.0
        * @param aFieldId The position field to read.
        * @param aFieldValue Will contain the value of the position field.
        * @returns @p KErrNone if successful, @p KErrNotFound if the landmark
        *   does not contain the specified position field.
        */
        IMPORT_C TInt GetPositionField(
        /* IN  */       TPositionFieldId  aFieldId,
        /* OUT */       TPtrC&  aFieldValue
        ) const;

        /**
        * Sets a position field in the landmark.
        *
        * If the position field text is longer than
        * @p KPosLmMaxTextFieldLength, this function will leave with error code
        * @p KErrArgument.
        *
        * @since S60 3.0
        * @param aFieldId The position field to set.
        * @param aFieldValue The new value for the position field.
        */
        IMPORT_C void SetPositionFieldL(
        /* IN  */       TPositionFieldId  aFieldId,
        /* IN  */       const TDesC&  aFieldValue
        );

        /**
        * Removes a position field from the landmark.
        *
        * If the specified position field is not contained in the landmark,
        * nothing will happen.
        *
        * @since S60 3.0
        * @param aFieldId The position field to remove.
        */
        IMPORT_C void RemovePositionField(
        /* IN  */       TPositionFieldId  aFieldId
        );

        /**
        * Associates the landmark with an icon.
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
        * Returns the a link to the icon associated with the landmark.
        *
        * Icons are found in icon files. It is referenced by the name of
        * the icon file and the index of the icon within the file.
        *
        * The landmark is not affected if the icon file is changed or
        * removed. It only contains a link to the icon. This means that the
        * link could be invalid.
        *
        * @since S60 3.0
        * @param aIconFileName The full icon file name.
        * @param aIconIndex The index of the icon within the icon file.
        * @param aIconMaskIndex The index of the icon mask within the
        *   icon file. If no icon mask index is defined @p KPosLmIconMaskNotUsed
        *   is returned.
         @returns @p KErrNone if successful, @p KErrNotFound if the icon is
        *   not set.
        */
        IMPORT_C TInt GetIcon(
        /* OUT */       TPtrC& aIconFileName,
        /* OUT */       TInt&  aIconIndex,
        /* OUT */       TInt&  aIconMaskIndex
        ) const;

        /**
        * Reads the description of the landmark.
        *
        * This function will return error code @p KErrNotFound if the landmark
        * description is not set in this landmark object. This will be the case
        * if the landmark is read from the database using partial read and
        * landmark description is excluded. Note that if a landmark is fully
        * read from the database, the landmark description will always be
        * included. If no description has been set for the landmark in
        * the database, it will have an empty description string "".
        *
        * @since S60 3.0
        * @param aLandmarkDescription Will contain the landmark description.
        * @returns @p KErrNone if successful, @p KErrNotFound if the landmark
        *   description is not specified.
        */
        IMPORT_C TInt GetLandmarkDescription(
        /* OUT */       TPtrC&  aLandmarkDescription
        ) const;

        /**
        * Sets a description for the landmark.
        *
        * If the name of the landmark is longer than
        * @p KPosLmMaxDescriptionLength, this function will leave with error
        * code @p KErrArgument.
        *
        * If no description is set for the landmark when it is written to the
        * database, the landmark in the database will have an empty description
        * string "".
        *
        * @since S60 3.0
        * @param aLandmarkDescription The landmark description.
        */
        IMPORT_C void SetLandmarkDescriptionL(
        /* IN  */       const TDesC&  aLandmarkDescription
        );

        /**
        * Removes landmark attributes from the landmark, e.g. landmark name.
        *
        * @since S60 3.0
        * @param aAttributes A bitmap specifying which landmark attributes to
        *   remove.
        */
        IMPORT_C void RemoveLandmarkAttributes(
        /* IN  */       TAttributes  aAttributes
        );

        /*
        * \internal
        *
        * Sets the partial update flag to the landmark.
        * This flag is used to indicate if only partial information is included
        * in the landmark object.
        *
        * This function is not supposed to be used by clients.
        *
        * @param aPartial @p EFalse if the landmark contains all the landmark
        *   information, otherwise @p ETrue.
        */
        void SetPartialL(
        /* IN  */       TBool aPartial
        );

        /*
        * \internal
        *
        * Sets the landmark ID to the landmark.
        *
        * This function is not supposed to be used by clients.
        *
        * @param aId The landmark ID to set.
        */
        void SetLandmarkIdL(
        /* IN  */       TPosLmItemId aId
        );

    private:

        /**
        * C++ default constructor.
        */
        CPosLandmark();

        // Prohibit copy constructor
        CPosLandmark(const CPosLandmark&);

        // Prohibit assigment operator
        CPosLandmark& operator= (const CPosLandmark&);

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();
        void ConstructL(const CPosLandmark& aLandmark);

    private:    // Data

        // Landmark ID
        TPosLmItemId iId;

        // Partial landmark flag
        TBool iIsPartial;

        // Landmark name
        HBufC* iLandmarkName;

        // Landmark position information
        TLocality* iPosition;

        // Landmark coverage radius
        TReal32 iCoverageRadius;

        // Landmark categories
        RArray<TPosLmItemId> iCategoryArray;

        // Landmark position field IDs
        RArray<TUint> iPositionFieldIds;

        // Landmark position field strings
        CDesCArray* iPositionFieldStrings;

        // Landmark icon filename
        HBufC* iIconFileName;

        // Landmark icon index
        TInt iIconIndex;

        // Landmark icon mask index
        TInt iIconMaskIndex;

        // Landmark description
        HBufC* iLandmarkDescription;
    };

// CPOSLANDMARK_H
#endif

// End of File
