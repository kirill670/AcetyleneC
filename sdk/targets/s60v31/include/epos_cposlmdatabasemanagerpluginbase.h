/*
* ==============================================================================
*  Name        : EPos_CPosLmDatabaseManagerPluginBase.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : SDK, Landmarks Database Management API
*  Description :
*
*  Version     : 1.5    2005/07/07 13:40:39
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

#ifndef CPOSLMDATABASEMANAGERPLUGINBASE_H
#define CPOSLMDATABASEMANAGERPLUGINBASE_H

//  INCLUDES
#include <e32base.h>
#include <badesca.h>
#include <EPos_TPosLmDatabaseEvent.h>
#include <EPos_TPosLmDatabaseSettings.h>
#include <EPos_HPosLmDatabaseInfo.h>

// FORWARD DECLARATIONS
class CPosLmDbManPluginBaseExtension;
class RPosLandmarkServer;

// CLASS DECLARATION

/**
*  This class is the base class which has to be subclassed in order to write a
*  plug-in for database management for a specific protocol.
*
*  This class is not used by client applications. Instead clients use @ref
*  CPosLmDatabaseManager which loads all @p CPosLmDatabaseManagerPluginBase
*  implementations.
*
*  @p CPosLmDatabaseManagerPluginBase contains functions for listing,
*  registering, unregistering, creating, deleting, copying landmark databases,
*  etc.
*
*  @lib eposlmdbmanlib.lib
*  @since S60 3.0
*  @version $Revision: 1.5 $, $Date: 2005/07/07 13:40:39 $
*/
class CPosLmDatabaseManagerPluginBase : public CBase
    {
    public:

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CPosLmDatabaseManagerPluginBase();

    public: // New functions

        /**
        * Retrieves the type of media where a landmark database resides.
        *
        * This function does not validate the URI. If the URI is invalid, this
        * function will just return @p EMediaUnknown.
        *
        * @since S60 3.0
        * @param aDatabaseUri The URI of the database to check media for.
        * @return Type of storage media.
        */
        virtual TMediaType DatabaseMedia(
        /* IN  */       const TDesC& aDatabaseUri
        ) = 0;

        /**
        * Retrieves the drive letter for the drive where a landmark database
        * resides.
        *
        * If the landmark database is remote or otherwise the drive letter is
        * not applicable, 0 is returned.
        *
        * This function does not validate the URI. If the URI is invalid, this
        * function will just return 0.
        *
        * @param aDatabaseUri The URI of the database to check drive letter
        *   for.
        * @return The drive letter, or 0 if drive letter is not applicable.
        */
        virtual TChar DatabaseDrive(
        /* IN  */       const TDesC& aDatabaseUri
        ) = 0;

        /**
        * Returns the protocol which the plug-in handles.
        *
        * The returned descriptor pointer is valid until the plug-in is
        * unloaded.
        *
        * @since S60 3.0
        * @return Pointer to the protocol descriptor, e.g. "file"
        */
        virtual TPtrC Protocol() = 0;

        /**
        * Lists the URIs to all landmark databases handled by this
        * plug-in.
        *
        * The client takes ownership of the returned array.
        *
        * If no databases are found, an empty array is returned.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @return The list of database URIs.
        */
        virtual CDesCArray* ListDatabasesLC() = 0;

        /**
        * Lists information about each landmark database handled by this
        * plug-in.
        *
        * The client specifies an array which is populated by this function.
        * The client takes ownership of all information objects in the array.
        *
        * If no databases are found, the input array is not modified.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aDatabaseInfoArray On return, contains information about
        *   the landmark databases.
        */
        virtual void ListDatabasesL(
        /* OUT */       RPointerArray<HPosLmDatabaseInfo>& aDatabaseInfoArray
        ) = 0;

        /**
        * Registers a landmark database.
        *
        * The landmark database is then returned when listing landmark
        * databases.
        *
        * Some protocols like "file" does not allow registering of databases
        * and will leave with error code @p KErrNotSupported. To add a
        * "file"-protocol database, the client must call @ref CreateDatabaseL.
        *
        * The client supplies an information object containing the URI of the
        * database to register. The information object can also contain
        * database settings, e.g. a display name for the database.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aDatabaseInfo Information about the landmark database to
        *   register.
        * @par Leave codes:
        * @p KErrNotSupported The protocol specified in the URI is not
        *   supported by this plug-in or the protocol does not allow
        *   registering landmark databases.\n
        * @p KErrArgument The URI is incorrect.\n
        * @p KErrAlreadyExists The database already exists in the registry.
        */
        virtual void RegisterDatabaseL(
        /* IN/OUT */       HPosLmDatabaseInfo& aDatabaseInfo
        ) = 0;

        /**
        * Unregisters a landmark database.
        *
        * After this, the landmark database will not be returned when listing
        * landmark databases.
        *
        * Some protocols like "file" does not allow unregistering of databases
        * and will leave with error code @p KErrNotSupported. To remove a
        * "file"-protocol database, the client must call @ref DeleteDatabaseL.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aDatabaseUri The URI of the database to register.
        * @par Leave codes:
        * @p KErrNotSupported The protocol specified in the URI is not
        *   supported by this plug-in or the protocol does not allow
        *   unregistering landmark databases.\n
        * @p KErrArgument The URI is incorrect.
        */
        virtual void UnregisterDatabaseL(
        /* IN  */       const TDesC& aDatabaseUri
        ) = 0;

        /**
        * Unregisters all landmark database which are accessed through this
        * plug-in
        *
        * After this, the landmark databases will not be returned when listing
        * landmark databases.
        *
        * Some protocols like "file" does not allow unregistering of databases
        * and will leave with error code @p KErrNotSupported. To remove a
        * "file"-protocol database, the client must call @ref DeleteDatabaseL.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @par Leave codes:
        * @p KErrNotSupported This plug-in does not allow unregistering
        *   landmark databases.
        */
        virtual void UnregisterAllDatabasesL() = 0;

        /**
        * Modifies the settings for a landmark database.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aDatabaseUri The URI of the database to modify settings for.
        * @param aDatabaseSettings The new settings for the database.
        * @par Leave codes:
        * @p KErrNotSupported The protocol specified in the URI is not
        *   supported by this plug-in.\n
        * @p KErrNotFound The specified database is not found.
        */
        virtual void ModifyDatabaseSettingsL(
        /* IN  */       const TDesC& aDatabaseUri,
        /* IN  */       const TPosLmDatabaseSettings& aDatabaseSettings
        ) = 0;

        /**
        * Retrieve information about a landmark database.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aDatabaseInfo An information object containing the URI of the
        *   landmark database. On return, the object contains information about
        *   the landmark database, including any database settings.
        * @par Leave codes:
        * @p KErrNotSupported The protocol specified in the URI is not
        *   supported by this plug-in.\n
        * @p KErrNotFound The specified database is not found.
        */
        virtual void GetDatabaseInfoL(
        /* IN/OUT */    HPosLmDatabaseInfo& aDatabaseInfo
        ) = 0;

        /**
        * Checks if the specified landmark database exists.
        *
        * The database to check is specified by passing a URI to this function.
        * URI construction is described in the class description for
        * @ref CPosLmDatabaseManager.
        *
        * This function requires @p ReadUserData capability. If the database is
        * remote, @p NetworkServices capability is also needed.
        *
        * @since S60 3.0
        * @param aDatabaseUri The URI of the database which should be checked
        *   for existence.
        * @return @p ETrue if the database exists, otherwise @p EFalse.
        * @par Leave codes:
        * @p KErrArgument The URI is incorrect or the protocol specified in the
        *   URI is not supported by this plug-in.\n
        */
        virtual TBool DatabaseExistsL(
        /* IN  */       const TDesC&  aDatabaseUri
        ) = 0;

        /**
        * Creates a landmark database.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities. If the database is remote, @p NetworkServices
        * capability is also needed.
        *
        * @since S60 3.0
        * @param aDatabaseInfo Information about the landmark database to
        *   create.
        * @par Leave codes:
        * @p KErrNotSupported The protocol is not supported or the create
        *   operation is not supported by the protocol plug-in.\n
        * @p KErrArgument The URI is incorrect or the protocol specified in the
        *   URI is not supported by this plug-in.\n
        * @p KErrAlreadyExists There is already a database at this URI.
        */
        virtual void CreateDatabaseL(
        /* IN/OUT */       HPosLmDatabaseInfo& aDatabaseInfo
        ) = 0;

        /**
        * Deletes a landmark database.
        *
        * The database to delete is specified by passing a URI to this
        * function. URI construction is described in the class description for
        * @ref CPosLmDatabaseManager. The URI must specify the protocol which
        * is handled by this database manager plug-in.
        *
        * If the specified database does not exist, the call is ignored.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities. If the database is remote, @p NetworkServices
        * capability is also needed.
        *
        * @since S60 3.0
        * @param aDatabaseUri The URI of the database to delete.
        * @par Leave codes:
        * @p KErrNotSupported The protocol is not supported or the delete
        *   operation is not supported by the plug-in.\n
        * @p KErrArgument The URI is incorrect or the protocol specified in the
        *   URI is not supported by this plug-in.\n
        * @p KErrInUse The database is in use by some client.\n
        * @p KErrAccessDenied The database is read-only.
        */
        virtual void DeleteDatabaseL(
        /* IN  */       const TDesC&  aDatabaseUri
        ) = 0;

        /**
        * Copies a landmark database to a new location.
        *
        * Database locations are specified as URIs. URI construction is
        * described in the class description for @ref CPosLmDatabaseManager.
        * The target and source URIs must specify the protocol which is handled
        * by this database manager plug-in.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities. If the database is remote, @p NetworkServices
        * capability is also needed.
        *
        * @since S60 3.0
        * @param aSourceUri The URI of the database to copy.
        * @param aTargetUri The URI of the new database location.
        * @par Leave codes:
        * @p KErrNotSupported The operation is not supported by the plug-in.\n
        * @p KErrArgument A URI is incorrect or the protocol specified in a
        *   URI is not supported by this plug-in.\n
        * @p KErrInUse There is a write-lock on the database, e.g. some client
        *   is currently modifying the database.\n
        * @p KErrNotFound There is no database at the source URI.\n
        */
        virtual void CopyDatabaseL(
        /* IN  */       const TDesC&  aSourceUri,
        /* IN  */       const TDesC&  aTargetUri
        ) = 0;

    protected:

        /**
        * C++ default constructor.
        */
        IMPORT_C CPosLmDatabaseManagerPluginBase();

        /**
        * Creates the internals of the manager.
        *
        * This function must be called first in the manager's @b ConstructL()
        * method.
        *
        * @param aConstructionParameters The construction parameters supplied
        *   in the factory call.
        */
        IMPORT_C void BaseConstructL(
        /* IN  */       TAny* aConstructionParameters
        );

    protected:

        /**
        * Returns a reference to an open landmark server session.
        *
        * @return The server session.
        */
        IMPORT_C RPosLandmarkServer& Session() const;

    private:

        // By default, prohibit copy constructor
        CPosLmDatabaseManagerPluginBase(
            const CPosLmDatabaseManagerPluginBase& );
        // Prohibit assigment operator
        CPosLmDatabaseManagerPluginBase& operator=(
            const CPosLmDatabaseManagerPluginBase& );

    private:    // Data

        CPosLmDbManPluginBaseExtension* iExtension;
    };

// CPOSLMDATABASEMANAGERPLUGINBASE_H
#endif

// End of File
