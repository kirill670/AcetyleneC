/*
* ==============================================================================
*  Name        : EPos_TPosLmDatabaseSettings.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks API, SDK
*  Description :
*
*  Version     : 1.5    2005/08/24 08:03:29
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

#ifndef TPOSLMDATABASESETTINGS_H
#define TPOSLMDATABASESETTINGS_H

//  INCLUDES
#include <e32std.h>

// CONSTANT DECLARATIONS
const TInt KPosLmDatabaseName = 64;
#define KPOSLMDATABASESETTINGSRESERVEDSIZE 31

// DATA TYPES
typedef TBuf<KPosLmDatabaseName> TPosLmDatabaseName;

// CLASS DECLARATION

/**
*  @ref TPosLmDatabaseSettings encapsulates the attributes that can be set for
*  a landmark database.
*
*  The only available attribute is the displayable name.
*
*  To set a new display name, create a @ref HPosLmDatabaseInfo object
*  containing the URI of the database. Call @ref SetDatabaseName on the
*  @ref TPosLmDatabaseSettings member in @ref HPosLmDatabaseInfo and then
*  pass the @ref HPosLmDatabaseInfo to
*  @ref CPosLmDatabaseManager::ModifyDatabaseSettingsL.
*
*  When retrieving settings for a database, @ref IsAttributeSet can be used to
*  find out whether display name is set for the database or not.
*
*  @lib eposlmdbmanlib.lib
*  @since S60 3.0
*  @version $Revision: 1.5 $, $Date: 2005/08/24 08:03:29 $
*/
class TPosLmDatabaseSettings
    {
    public: // Data types

        /**
        *  Enumeration of the attributes that can be set for a landmark
        *  database.
        *
        *  @since S60 3.0
        *  @version $Revision: 1.5 $, $Date: 2005/08/24 08:03:29 $
        */
        enum TAttribute
            {
            EName = 0x01                 /**<
                Displayable name for the landmark database */
            };

    public:  // Constructors and destructor

        /**
        * Default constructor.
        * @return A new instance of this class.
        */
        IMPORT_C TPosLmDatabaseSettings();


    public: // New functions

        /**
        * Checks whether a database attribute is set in this instance.
        *
        * @since S60 3.0
        * @param aDbAttribute The database attribute to check.
        * @return @p ETrue if the attribute is set, otherwise @p EFalse.
        */
        IMPORT_C TBool IsAttributeSet(
        /* IN  */       TAttribute aDbAttribute
        ) const;

        /**
        * Unset a database attribute.
        *
        * If an attribute is not set in this instance and the instance is
        * passed as input to a function for modifying the settings for a
        * database, e.g.  @ref CPosLmDatabaseManager::ModifyDatabaseSettingsL,
        * the attribute will be removed from the database.
        *
        * @since S60 3.0
        * @param aDbAttribute The database attribute to unset.
        */
        IMPORT_C void UnsetAttribute(
        /* IN  */       TAttribute aDbAttribute
        );

        /**
        * Retrieves the displayable name for the database.
        *
        * If the @p EName attribute is not set, an empty descriptor is returned.
        *
        * @since S60 3.0
        * @return A pointer to the name descriptor. This pointer is valid until
        *   the @ref TPosLmDatabaseSettings instance is destroyed.
        */
        IMPORT_C TPtrC DatabaseName() const;

        /**
        * Set a displayable name for the database.
        *
        * If an empty descriptor is set, the database display name will be
        * set to an empty string.
        *
        * @since S60 3.0
        * @param aDatabaseName The new name for the database.
        */
        IMPORT_C void SetDatabaseName(
        /* IN  */       const TPosLmDatabaseName& aDatabaseName
        );

    private:    // Data

        TUint8 iAttributes;
        TPosLmDatabaseName iName;
        TUint8 iReserved[KPOSLMDATABASESETTINGSRESERVEDSIZE];

    };

#endif      // TPOSLMDATABASESETTINGS_H

// End of File
