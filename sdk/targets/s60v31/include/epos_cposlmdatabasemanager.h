/*
* ==============================================================================
*  Name        : EPos_CPosLmDatabaseManager.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : SDK, Landmarks Database Management API
*  Description :
*
*  Version     : 1.13    2005/07/07 13:40:40
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

#ifndef CPOSLMDATABASEMANAGER_H
#define CPOSLMDATABASEMANAGER_H

//  INCLUDES
#include <e32base.h>
#include <badesca.h>
#include "EPos_TPosLmDatabaseEvent.h"
#include "EPos_TPosLmDatabaseSettings.h"
#include "EPos_HPosLmDatabaseInfo.h"

// CLASS DECLARATION

/**
*  This class is used to manage landmark databases.
*
*  @p CPosLmDatabaseManager contains functions for listing registering,
*  unregistering, creating, deleting, copying landmark databases, etc.
*  It also has functions for managing the default landmark database. The
*  client can listen to events related to database management.
*
*  A database is local if it resides in the phone or in some device which
*  is mapped to the phones file system. If a database is not local, it is
*  remote.
*
*  The client refers to a database by URI. The URI consists of a protocol
*  specifier and the database location: "protocol://location". If the
*  client does not specify a protocol, "file://" is assumed.
*
*  For local landmark databases, the URI consists of the drive and the
*  database file name, e.g. "c:landmarks.ldb". The path cannot be specified
*  by the client. The extension of the database file name must be "ldb".
*  If the a path is included or if the file name extension is not .ldb",
*  the client receives the error code @p KErrArgument. For local landmark
*  databases, the client receives the error code @p KErrBadName if the
*  file name is invalid and @p KErrNotReady if the drive specified in the URI
*  does not exist.
*
*  If the client specifies a local database URI and does not specify the drive
*  letter, e.g. "landmarks.ldb", c: drive is assumed.
*
*  Local databases are created by calling @ref CreateDatabaseL. "Bookmarks"
*  to remote databases are created by calling @ref RegisterDatabaseL. After
*  this they are listed by the database manager.
*
*  If @ref CPosLmDatabaseManager is used, the client must call the global
*  function @ref ReleaseLandmarkResources before terminating, in order to
*  release all used landmark resources, otherwise the client may receive
*  an ALLOC panic.
*
*  @lib eposlmdbmanlib.lib
*  @since S60 3.0
*  @version $Revision: 1.13 $, $Date: 2005/07/07 13:40:40 $
*/
class CPosLmDatabaseManager : public CBase
    {
    public:

        /**
        * Two-phased constructor.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        */
        IMPORT_C static CPosLmDatabaseManager* NewL();

        /**
        * Destructor.
        *
        * @since S60 3.0
        */
        IMPORT_C virtual ~CPosLmDatabaseManager();

    public: // New functions

        /**
        * Retrieves the URI of the default landmark database.
        *
        * The default landmark database is the one which is opened when calling
        * @p CPosLandmarkDatabase::OpenL without any parameters.
        *
        * Only "file"-protocol databases can be set as default.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @return The URI of the default landmark database. The client takes
        *   ownership of the descriptor object.
        */
        virtual HBufC* DefaultDatabaseUriLC() = 0;

        /**
        * Sets a landmark database as default.
        *
        * This database is opened the next time
        * @p CPosLandmarkDatabase::OpenL() called without parameters.
        *
        * To move the current default database to another drive, first use
        * @ref CopyDatabaseL to copy the database to the new drive, then use
        * @ref SetDefaultDatabaseUriL to set the new database as default and
        * finally, use @ref DeleteDatabaseL if the old default database should
        * be deleted.
        *
        * Only "file"-protocol databases can be set as default.
        *
        * This function requires @p WriteDeviceData capability.
        *
        * @since S60 3.0
        * @param aDatabaseUri The URI of the database which should be set as
        *   default.
        * @par Leave codes:
        * @p KErrNotSupported The protocol specified something else
        *   than "file://" as protocol in the URI.\n
        * @p KErrArgument The URI is incorrect.\n
        * @p KErrNotFound The landmark database which should be set as default
        * does not exist.
        */

        virtual void SetDefaultDatabaseUriL(
        /* IN  */       const TDesC& aDatabaseUri
        ) = 0;

        /**
        * Listens for database management events.
        *
        * This function is asynchronous and it completes the request
        * status when an event occurs. At this time, the client can read
        * event information from the retrieved event object.
        *
        * Event listening can be canceled by calling
        * @ref CancelNotifyDatabaseEvent.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aEvent Contains the event information when an event
        *   occurs.
        * @param aStatus Is completed with @p KErrNone if an event
        *   occurs or an error code if some error is encountered.
        */

        virtual void NotifyDatabaseEvent(
        /* OUT */   TPosLmDatabaseEvent& aEvent,
        /* OUT */   TRequestStatus& aStatus
        ) = 0;

        /**
        * Cancels a call to @ref NotifyDatabaseEvent.
        *
        * @since S60 3.0
        * @return @p KErrNone if the request was successfully cancelled,
        *   otherwise a system wide error code.
        */
        virtual TInt CancelNotifyDatabaseEvent() = 0;

        /**
        * Retrieves the database URI associated with the last event.
        *
        * Some events, e.g. @p EPosLmDbDatabaseRegistered and
        * @p EPosLmDbDatabaseUnregistered, refer to a specific database. The
        * URI of the database can be retrieved through this function.
        *
        * If the URI should be retrieved, this function must be called before
        * @ref NotifyDatabaseEvent is called again to listen for the next
        * event.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @return The database URI associated with the event. The client takes
        *   ownership of the descriptor object.
        * @par Leave codes:
        * @p KErrNotFound There is no database URI associated with the event
        * or, the database URI has been discarded because the client has called
        * @ref NotifyDatabaseEvent again.
        */
        virtual HBufC* DatabaseUriFromLastEventLC() = 0;

        /**
        * Lists the URIs to all landmark databases known by the Landmarks
        * system.
        *
        * The client can specify a protocol string as input to this function.
        * The function then only returns a list of the databases which
        * are accessed through this protocol.
        *
        * The client takes ownership of the returned array.
        *
        * If no databases are found, an empty array is returned.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aProtocol The protocol for which database URIs should be
        *   listed. If no protocol is specified, i.e. if an empty string is
        *   specified, all known database URIs are listed.
        * @return The list of database URIs.
        * @par Leave codes:
        * @p KErrNotSupported The protocol is not supported in the platform.
        */
        virtual CDesCArray* ListDatabasesLC(
        /* IN  */       const TDesC& aProtocol = KNullDesC
        ) = 0;

        /**
        * Lists information about each landmark database known by the Landmarks
        * system.
        *
        * The client can specify a protocol string as input to this function.
        * The function then only returns information about the databases
        * which are accessed through this protocol.
        *
        * The client specifies an array which is populated by this function.
        * The client takes ownership of all information objects in the array.
        *
        * If no databases are found, an empty array is returned.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aDatabaseInfoArray On return, contains information about
        *   the landmark databases. Any objects which are in the array when
        *   it is passed to this function are not removed.
        * @param aProtocol The protocol for which database URIs should be
        *   listed. If no protocol is specified, i.e. if an empty string is
        *   specified, all known database URIs are listed.
        * @par Leave codes:
        * @p KErrNotSupported The protocol is not supported in the platform.
        */
        virtual void ListDatabasesL(
        /* OUT */       RPointerArray<HPosLmDatabaseInfo>& aDatabaseInfoArray,
        /* IN  */       const TDesC& aProtocol = KNullDesC
        ) = 0;

        /**
        * Registers a landmark database.
        *
        * The landmark database is then returned when listing landmark
        * databases.
        *
        * For local landmark databases, this function leaves with error code
        * @p KErrNotSupported. To add a local database, the client must call
        * @ref CreateDatabaseL.
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
        *   register. The information object will be updated with
        *   media type and drive information.
        * @par Leave codes:
        * @p KErrNotSupported The protocol specified in the URI is not
        *   supported in the platform or the protocol does not allow
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
        * After this, the landmark database are not returned when listing
        * landmark databases.
        *
        * For local landmark databases, this function leaves with error code
        * @p KErrNotSupported. To remove a local database, the client must call
        * @ref DeleteDatabaseL.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aDatabaseUri The URI of the database to register.
        * @par Leave codes:
        * @p KErrNotSupported The protocol specified in the URI is not
        *   supported in the platform or the protocol does not allow
        *   unregistering landmark databases.\n
        * @p KErrArgument The URI is incorrect.
        */
        virtual void UnregisterDatabaseL(
        /* IN  */       const TDesC& aDatabaseUri
        ) = 0;

        /**
        * Unregisters all landmark database which are accessed through a
        * certain protocol.
        *
        * After this, the landmark databases are not be returned when listing
        * landmark databases.
        *
        * For local landmark databases, this function leaves with error code
        * @p KErrNotSupported. To remove a local database, the client must call
        * @ref DeleteDatabaseL.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aProtocol The protocol to unregister all databases for.
        * @par Leave codes:
        * @p KErrNotSupported The protocol is not supported in the platform
        *   or the protocol does not allow unregistering landmark databases.
        * @p KErrArgument The protocol is an empty string.
        */
        virtual void UnregisterAllDatabasesL(
        /* IN  */       const TDesC& aProtocol
        ) = 0;

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
        *   supported in the platform.\n
        * @p KErrNotFound The specified database is not found.\n
        * @p KErrArgument The URI is incorrect.
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
        *   supported in the platform.\n
        * @p KErrNotFound The specified database is not found.\n
        * @p KErrArgument The URI is incorrect.
        */
        virtual void GetDatabaseInfoL(
        /* IN/OUT */    HPosLmDatabaseInfo& aDatabaseInfo
        ) = 0;

        /**
        * Checks if the specified landmark database exists.
        *
        * The database to check is specified by passing a URI to this function.
        * URI construction is described in the class description for
        * @ref CPosLmDatabaseManager. The URI must point to a database which is
        * handled by this database manager, i.e. not a remote location.
        *
        * This function requires @p ReadUserData capability. If the database is
        * remote, @p NetworkServices capability is also needed.
        *
        * @since S60 3.0
        * @param aDatabaseUri The URI of the database which should be checked
        *   for existence.
        * @return @p ETrue if the database exists, otherwise @p EFalse.
        * @par Leave codes:
        * @p KErrNotSupported The protocol specified in the URI is not
        *   supported.\n
        * @p KErrArgument The URI is incorrect.
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
        *   create. The information object will be updated with
        *   media type and drive information.
        * @par Leave codes:
        * @p KErrNotSupported The protocol specified in the URI is not
        *   supported.\n
        * @p KErrArgument The URI is incorrect.\n
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
        * @ref CPosLmDatabaseManager.
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
        * @p KErrNotSupported The protocol specified in the URI is not
        *   supported.\n
        * @p KErrArgument The URI is incorrect.\n
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
        * Target URI protocol must be the same as source URI protocol.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities. If the databases are remote, @p NetworkServices
        * capability is also needed.
        *
        * @since S60 3.0
        * @param aSourceUri The URI of the database to copy.
        * @param aTargetUri The URI of the new database location.
        * @par Leave codes:
        * @p KErrNotSupported The protocol specified in the a URI is not
        *   supported.\n
        * @p KErrArgument A URI is incorrect.\n
        * @p KErrAlreadyExists There is already a database at the target URI.\n
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
        IMPORT_C CPosLmDatabaseManager();

    private:

        // By default, prohibit copy constructor
        CPosLmDatabaseManager( const CPosLmDatabaseManager& );
        // Prohibit assigment operator
        CPosLmDatabaseManager& operator= ( const CPosLmDatabaseManager& );

    private:    // Data

        // Implementation Uid
        TUid iDtorIdKey;
    };

// CPOSLMDATABASEMANAGER_H
#endif

// End of File
