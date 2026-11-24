/*
* ==============================================================================
*  Name        : EPos_CPosLandmarkDatabase.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks API
*  Description :
*     See class description below
*  Version     : 1.22    2005/07/07 13:40:47
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

#ifndef CPOSLANDMARKDATABASE_H
#define CPOSLANDMARKDATABASE_H

//  INCLUDES
#include <e32base.h>
#include <s32strm.h>
#include "EPos_Landmarks.h"
#include "EPos_CPosLandmark.h"
#include "EPos_CPosLmPartialReadParameters.h"
#include "EPos_CPosLmItemIterator.h"
#include "EPos_TPosLmSortPref.h"
#include "EPos_CPosLmOperation.h"

// FORWARD DECLARATIONS
class CPosLandmarkParser;
class CPosLandmarkEncoder;

// CLASS DECLARATION

/**
*  Handle to a landmark database.
*
*  This class contains functions for creating, iterating, reading, modifying
*  and deleting landmarks.
*
*  Operations on the database may fail with error code @p KErrCorrupt if the
*  database is damaged. The client can try to recover the database by calling
*  @ref CPosLandmarkDatabase::InitializeL.
*
*  Operations on the database may fail with error code @p KErrLocked if another
*  client is writing to the database. Write operations can also fail with this
*  error code if another client is currently reading from the database.
*
*  If @ref CPosLandmarkDatabase is used, the client must call the global
*  function @ref ReleaseLandmarkResources before terminating in order to
*  release all used landmark resources, otherwise the client may receive
*  an ALLOC panic.
*
*  @p NetworkServices capability is required for remote databases.
*
*  To use this class, link against @p eposlandmarks.lib.
*
*  @version $Revision: 1.22 $, $Date: 2005/07/07 13:40:47 $
*/
class CPosLandmarkDatabase : public CBase
    {
    public:  // Data types

        typedef TUint TTransferOptions;

        /**
        *  Specifies options for importing and exporting landmarks.
        *
        *  @since S60 3.0
        *  @version $Revision: 1.22 $, $Date: 2005/07/07 13:40:47 $
        */
        enum _TTransferOptions
            {
            EDefaultOptions = 0                 /**<
                None of the transfer option flags are set. */,
            EIncludeCategories = 0x01           /**<
                Export/Import the categories of the landmarks. */,
            EIncludeGlobalCategoryNames = 0x02  /**<
                Only useful in combination with EIncludeCategories.
                If set, global category names will be used in export/import
                even if user has renamed them. For import it means that the
                names of the global categories in the database are overwritten
                by the imported names. For export it means that predefined
                names of global categories in the current language will be
                exported instead of user-defined names. */,
            ESupressCategoryCreation = 0x04     /**<
                Only useful in combination with EIncludeCategories.
                If set, no new categories are created in the database when
                importing landmarks. This means that connections from
                imported landmarks will be established only to already
                existing categories, according to the import information. */
            };

        /**
        *  Encapsulates size information for a landmark database.
        *
        *  @since S60 3.0
        *  @version $Revision: 1.22 $, $Date: 2005/07/07 13:40:47 $
        */
        struct TSize
            {
            TInt iFileSize;   /**<
                The size of the database in bytes. */
            TReal32 iUsage;   /**<
                How many percent of the database which is currently in use.
                This indicates how much space is available for compaction.
                This value lies in the interval [0.0, 1.0]. */
            };

    public:  // Constructors and destructor

        /**
        * Opens the default landmark database.
        *
        * The client takes ownership of the returned database handle.
        *
        * The database may have to be initialized before it can be used, see
        * @ref IsInitializingNeeded and @ref InitializeL.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @returns A handle to the open database.
        */
        IMPORT_C static CPosLandmarkDatabase* OpenL();

        /**
        * Opens a specific landmark database.
        *
        * The client refers to a database by URI. The URI consists of a
        * protocol specifier and the database location. "protocol://location".
        * If the client does not specify a protocol, "file://" will be assumed.
        *
        * For local landmark databases, the URI consists of the drive and the
        * database file name, e.g. "c:landmarks.ldb". The path cannot be
        * specified by the client. The extension of the database file name must
        * be "ldb" otherwise the client will get the error @p KErrArgument.
        *
        * If the client specifies a local database and does not specify the
        * drive letter, e.g. "landmarks.ldb", c: drive will be assumed.
        *
        * If the specified protocol is not supported, this function will
        * leave with code @p KErrNotSupported.
        *
        * The client takes ownership of the returned database handle.
        *
        * The database may have to be initialized before it can be used, see
        * @ref IsInitializingNeeded and @ref InitializeL.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aDatabaseUri The URI of the database to open.
        * @returns A handle to the open database.
        */
        IMPORT_C static CPosLandmarkDatabase* OpenL(
        /* IN  */       const TDesC&  aDatabaseUri
        );

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CPosLandmarkDatabase();

    public: // New functions

        /**
        * Checks if the database is in need of initialization.
        *
        * If the database needs to be initialized, the client must call
        * @ref InitializeL, otherwise the database may not be possible to
        * access. Access functions may leave with @p KErrPosLmNotInitialized.
        *
        * Initialization may be needed also if the database becomes damaged.
        * The client can then try to call @ref InitializeL to try to recover
        * the database.
        *
        * @since S60 3.0
        * @returns @p ETrue if the database is in need of initialization,
        *   otherwise @p EFalse.
        */
        virtual TBool IsInitializingNeeded() const = 0;

        /**
        * Initializes the database.
        *
        * This function may have to be called right after the database is
        * opened. @ref IsInitializingNeeded can be called to find out if
        * initialization is needed.
        *
        * If the database becomes damaged, the client can call
        * @ref InitializeL  to try to recover the database.
        *
        * It is ok to call @InitializeL even if initialization is not needed.
        * In this case, the operation will not do anything.
        *
        * If the database needs to be initialized, the client must call
        * @ref InitializeL, otherwise the database may not be possible to
        * access. Access functions may leave with @p KErrPosLmNotInitialized.
        *
        * The function returns an operation object which can be run in
        * incremental mode. If it is run incrementally the client can supervise
        * the progress of the operation.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, it is possible that the database is not yet initialized.
        *
        * The client takes ownership of the returned operation object.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* InitializeL() = 0;

        /**
        * Reads a landmark from the database.
        *
        * If the landmark does not exist in the database, this method leaves
        * with @p KErrNotFound.
        *
        * The client takes ownership of the returned database landmark object.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param The ID of the landmark to read.
        * @returns The requested landmark. The landmark object is put on the
        *   cleanup stack.
        */
        virtual CPosLandmark* ReadLandmarkLC(
        /* IN  */       TPosLmItemId  aLandmarkId
        ) = 0;

        /**
        * Returns an object for iterating the landmarks in the database.
        *
        * The iterator object is reset, so that the first
        * @ref CPosLmItemIterator::NextL call will return the first landmark
        * ID.
        *
        * The client takes ownership of the returned iterator object.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @return The landmark iterator.
        */
        virtual CPosLmItemIterator* LandmarkIteratorL() = 0;

        /**
        * Returns an object for iterating the landmarks in the database.
        *
        * The iterator object is reset, so that the first
        * @ref CPosLmItemIterator::NextL call will return the first landmark
        * ID.
        *
        * This overload of the iterator function takes a sort preference object
        * as input. The sort preference object specifies how the landmarks
        * should be sorted by the iterator.
        *
        * Only sorting by landmark name is supported. If the client tries to
        * sort by another attribute, this function will leave with error code
        * @p KErrNotSupported.
        *
        * The client takes ownership of the returned iterator object.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aSortPref A sort preference object.
        * @return The landmark iterator.
        */
        virtual CPosLmItemIterator* LandmarkIteratorL(
        /* IN  */       const TPosLmSortPref&  aSortPref
        ) = 0;

        /**
        * Adds a new landmark to the database and returns its ID.
        *
        * If the database is read-only, this method leaves with
        * @p KErrAccessDenied.
        *
        * A landmark can contain the IDs of the categories it belongs to. If
        * any of these categories does not exist in the database, the add
        * operation will still complete successfully but the category which
        * was not found will be ignored.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aLandmark The landmark to add.
        * @return The ID of the new landmark.
        */
        virtual TPosLmItemId AddLandmarkL(
        /* IN OUT */    CPosLandmark&  aLandmark
        ) = 0;

        /**
        * Updates a landmark in the database.
        *
        * If the database is read-only, this method leaves with
        * @p KErrAccessDenied.
        *
        * Only landmark objects containing full landmark information can be
        * used to update a landmark. If a partial landmark (see
        * @ref ReadPartialLandmarkLC and @ref CPosLandmark::IsPartial) is
        * passed to this function it will leave with @p KErrArgument.
        *
        * Note that any updates in the database made since the landmark
        * object was read from the database will be overwritten by this
        * operation.
        *
        * A landmark can contain the IDs of the categories it belongs to. If
        * any of these categories does not exist in the database, the update
        * operation will still complete successfully but the category which
        * was not found will be ignored.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aLandmark The new landmark data.
        */
        virtual void UpdateLandmarkL(
        /* IN  */       const CPosLandmark&  aLandmark
        ) = 0;

        /**
        * Removes a landmark from the database.
        *
        * If the landmark does not exist in the database, nothing happens.
        *
        * If the database is read-only, this method leaves with
        * @p KErrAccessDenied.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aLandmarkId The ID of the landmark to remove.
        */
        virtual void RemoveLandmarkL(
        /* IN  */       TPosLmItemId  aLandmarkId
        ) = 0;

        /**
        * Removes a set of landmarks from the database.
        *
        * If any of the specified landmarks don't exist in the database,
        * nothing happens for those landmarks.
        *
        * The function returns an operation object which can be run in
        * incremental mode. If it is run incrementally the client can supervise
        * the progress of the operation.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, it is possible that only a subset of the landmarks
        * have been deleted.
        *
        * If the database is read-only, this operation will fail with error
        * code @p KErrAccessDenied.
        *
        * The client takes ownership of the returned operation object.
        *
        * While removing landmarks, this operation will acquire a write-lock on
        * the database.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aLandmarkIdArray The IDs of the landmarks to remove.
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* RemoveLandmarksL(
        /* IN  */       const RArray<TPosLmItemId>&  aLandmarkIdArray
        ) = 0;

        /**
        * Removes all landmarks from the database.
        *
        * The function returns an operation object which can be run in
        * incremental mode. If it is run incrementally the client can supervise
        * the progress of the operation.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, it is possible that only a subset of the landmarks
        * have been deleted.
        *
        * If the database is read-only, this operation will fail with error
        * code @p KErrAccessDenied.
        *
        * The client takes ownership of the returned operation object.
        *
        * While removing landmarks, this operation will acquire a write-lock on
        * the database.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* RemoveAllLandmarksL() = 0;

        /**
        * Returns the partial read parameters for this database handle.
        *
        * Partial read parameters are used to define which landmark data should
        * be returned when @ref ReadPartialLandmarkLC is called.
        *
        * The client takes ownership of the returned parameter object.
        *
        * @since S60 3.0
        * @returns The current partial read parameters.
        */
        virtual CPosLmPartialReadParameters* PartialReadParametersLC() = 0;

        /**
        * Sets the partial read parameters for this database handle.
        *
        * Partial read parameters are used to define which landmark data should
        * be returned when @ref ReadPartialLandmarkLC is called.
        *
        * @since S60 3.0
        * @param aPartialSettings The new partial read parameters.
        */
        virtual void SetPartialReadParametersL(
        /* IN  */       const CPosLmPartialReadParameters&  aPartialSettings
        ) = 0;

        /**
        * Reads partial data from a landmark in the database.
        *
        * Partial settings define which landmark data should be returned in
        * this call. Partial read attributes are defined by calling
        * @ref SetPartialReadParametersL. If no partial read parameters have
        * been set, the landmarks will not contain any attributes.
        *
        * The caller takes ownership of the returned object.
        *
        * If the landmark does not exist in the database, this method leaves
        * with @p KErrNotFound.
        *
        * The client takes ownership of the returned landmark object.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param The ID of the landmark to read.
        * @returns The requested landmark. The landmark object will only
        *   contain the attributes defined in the partial read attributes. The
        *   landmark object is put on the cleanup stack.
        */
        virtual CPosLandmark* ReadPartialLandmarkLC(
        /* IN  */       TPosLmItemId  aLandmarkId
        ) = 0;

        /**
        * Reads partial data from a set of landmarks in the database.
        *
        * Partial settings define which landmark data should be read. Partial
        * read attributes are defined by calling @ref SetPartialReadParametersL.
        * If no partial read parameters have been set, the landmarks will not
        * contain any attributes.
        *
        * Note that the returned data may be very big if all attributes in
        * each landmark are requested. A typical use for this function is to
        * retrieve the names for a set of landmarks.
        *
        * When the request is completed, the result can be retrieved by calling
        * @ref TakePreparedPartialLandmarksL.
        *
        * The function returns an operation object which can be run in
        * incremental mode. If it is run incrementally the client can supervise
        * the progress of the operation.
        *
        * The client takes ownership of the returned operation object.
        *
        * While preparing landmark information, this operation will acquire a
        * read-lock on the database.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aLandmarkIdArray An array with IDs of the landmarks to read.
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* PreparePartialLandmarksL(
        /* IN  */       const RArray<TPosLmItemId>&  aLandmarkIdArray
        ) = 0;

        /**
        * Fetches the result from a call to @ref PreparePartialLandmarksL.
        *
        * The returned array will have the same length as the ID array passed
        * in the @ref PreparePartialLandmarksL call and it will have the same
        * order.
        *
        * The caller takes ownership of the returned array object including
        * the contained landmark objects.
        *
        * If reading a landmark failed during preparation, the corresponding
        * pointer value in the returned array will be NULL. For instance,
        * reading can fail if the specified ID does not exist in the database.
        *
        * This function can only be called once. If this function is called
        * a second time or if @ref PreparePartialLandmarksL has failed, this
        * function will leave with code @p KErrNotFound.
        *
        * @since S60 3.0
        * @param aPreparePartialLandmarkOperation The operation object returned
        *   by the @ref PreparePartialLandmarksL function.
        * @returns An array containing the prepared partial landmark objects.
        */
        virtual CArrayPtr<CPosLandmark>* TakePreparedPartialLandmarksL(
        /* IN  */       CPosLmOperation*  aPreparePartialLandmarkOperation
        ) = 0;

        /**
        * Returns a URI which points to the landmark database storage.
        *
        * The URI may point to a file in the terminal file system or on a
        * remote file.
        *
        * The client takes ownership of the returned descriptor.
        *
        * @since S60 3.0
        * @returns The database URI. The URI is put on the cleanup stack.
        */
        virtual HBufC* DatabaseUriLC() = 0;

        /**
        * Returns size information for the database.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @returns Size information for the database.
        */
        virtual TSize SizeL() = 0;

        /**
        * Compacts the landmark database.
        *
        * Compaction means that any unused space in the database is removed.
        *
        * The function returns an operation object which can be run in
        * incremental mode. If it is run incrementally the client can supervise
        * the progress of the operation.
        *
        * The client takes ownership of the returned operation object.
        *
        * If the database is read-only, this operation will fail with error
        * code @p KErrAccessDenied.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* CompactL() = 0;

        /**
        * Listens for database events.
        *
        * This function is asynchronous and it will complete the request
        * status when an event occurs. At this time, the client can read
        * event information from the retrieved event object.
        *
        * Event listening can be cancelled by calling
        * @ref CancelNotifyDatabaseEvent.
        *
        * If this function is called when the client already has an outstanding
        * @ref NotifyDatabaseEvent request, this function will panic with error
        * code @p EPosEventNotifierAlreadyHasOutstandingRequest.
        *
        * If events are not supported, status @p KErrNotSupported will be
        * returned.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aEvent Will contain the event information when an event
        *   occurs.
        * @param aStatus Will be completed with @p KErrNone if an event
        *   occurs and an error code if some error was encountered.
        */
        virtual void NotifyDatabaseEvent(
        /* OUT */   TPosLmEvent& aEvent,
        /* OUT */   TRequestStatus& aStatus
        ) = 0;

        /**
        * Cancels a call to @ref NotifyDatabaseEvent.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @return @p KErrNone if the request was successfully cancelled,
        *   otherwise a system wide error code.
        */
        virtual TInt CancelNotifyDatabaseEvent() = 0;

        /**
        * Exports a number of landmarks.
        *
        * To export a set of landmarks, the client must first create a
        * @ref CPosLandmarkEncoder object for the landmark content format in
        * which the landmarks should be encoded. The client can add some
        * information of the landmark collection in the encoder as well.
        *
        * The client must also provide a list of the landmarks which should be
        * exported. If one of the landmarks are not found in the database, this
        * operation fails with error code @p KErrNotFound.
        *
        * The client does not have to add any landmarks to the encoder object.
        * This function will add the ones specified in the ID array.
        *
        * The function returns an operation object which can be run in
        * incremental mode. If it is run incrementally the client can supervise
        * the progress of the operation.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, it is possible that only a subset of the landmarks have
        * been exported.
        *
        * The client takes ownership of the returned operation object.
        *
        * If the client specifies invalid transfer option values, this function
        * will panic.
        *
        * When all landmarks have been exported the client must finalize
        * encoding by calling @ref CPosLandmarkEncoder::FinalizeEncodingL.
        *
        * This function requires @p ReadUserData capability.
        *
        * @since S60 3.0
        * @param aLandmarkEncoder A landmark encoder object.
        * @param aLandmarkIdArray The landmarks which should be exported.
        * @param aTransferOptions A bitmap representing the options for the
        *   export operation. The bitmap values are defined by
        *   @ref _TTransferOptions.
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* ExportLandmarksL(
        /* IN  */       CPosLandmarkEncoder&  aLandmarkEncoder,
        /* IN  */       const RArray<TPosLmItemId>&  aLandmarkIdArray,
        /* IN  */       TTransferOptions  aTransferOptions
        ) = 0;

        /**
        * Import a set of landmarks.
        *
        * To import landmark content, the client must first create a parser
        * object which can parse the landmark content. The client does not have
        * to call @ref CPosLandmarkParser::ParseContentL first. If the content
        * is not already parsed, this will be handled by the import operation.
        *
        * The function returns an operation object which can be run in
        * incremental mode. If it is run incrementally the client can supervise
        * the progress of the operation.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, it is possible that only a subset of the landmarks have
        * been imported.
        *
        * The client takes ownership of the returned operation object.
        *
        * After completion @ref ImportedLandmarksIteratorL can be called to
        * retrieve the IDs of the added landmarks.
        *
        * If the database is read-only, this operation will fail with error
        * code @p KErrAccessDenied.
        *
        * If the client specifies invalid transfer option values, this function
        * will panic.
        *
        * The @p NextStep function in the operation object cannot be executed
        * synchronously using @p User::WaitForRequest. Doing so may cause the
        * operation to hang. @p NextStep must be run using an active object
        * for this operation.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aLandmarkParser An object which can parse landmark content.
        * @param aTransferOptions A bitmap representing the options for the
        *   import operation. The bitmap values are defined by
        *   @ref _TTransferOptions.
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* ImportLandmarksL(
        /* IN  */       CPosLandmarkParser&  aLandmarkParser,
        /* IN  */       TTransferOptions  aTransferOptions
        ) = 0;

        /**
        * Import a set of landmarks.
        *
        * To import landmark content, the client must first create a parser
        * object which can parse the landmark content. The client does not have
        * to call @ref CPosLandmarkParser::ParseContentL first. If the content
        * is not already parsed, this will be handled by the import operation.
        *
        * In this overload of the function, the client can pass an array
        * defining a subset of the landmarks in the parser object. This way
        * the client can select to import only a part of the landmark content.
        *
        * The function returns an operation object which can be run in
        * incremental mode. If it is run incrementally the client can supervise
        * the progress of the operation.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, it is possible that only a subset of the landmarks have
        * been imported.
        *
        * The client takes ownership of the returned operation object.
        *
        * After completion @ref ImportedLandmarksIteratorL can be called to
        * retrieve the IDs of the added landmarks.
        *
        * If the database is read-only, this operation will fail with error
        * code @p KErrAccessDenied.
        *
        * If the client specifies invalid transfer option values, this function
        * will panic.
        *
        * The @p NextStep function in the operation object cannot be executed
        * synchronously using @p User::WaitForRequest. Doing so may cause the
        * operation to hang. @p NextStep must be run using an active object
        * for this operation.
        *
        * This function requires @p ReadUserData and @p WriteUserData
        * capabilities.
        *
        * @since S60 3.0
        * @param aLandmarkParser An object which can parse landmark content.
        * @param aLandmarkSelection An array defining which of the parsed
        *   landmarks to import. The array items refer to the order in which
        *   @ref CPosLandmarkParser accesses the landmarks. 0 means the first
        *   parsed landmark, 1 means the second, etc. If the parser supports
        *   indexing, these numbers correspond to the index values used to
        *   access the landmarks in @ref CPosLandmarkParser::LandmarkLC. The
        *   index values must be less than the number of landmarks accessed by
        *   the parser, otherwise the operation object will panic with error
        *   code @p EPosInvalidIndex during execution. @p Note: The indexes
        *   can be used regardless of whether the parser supports indexing or
        *   not.
        * @param aTransferOptions A bitmap representing the options for the
        *   import operation. The bitmap values are defined by
        *   @ref _TTransferOptions.
        * @returns A handle to the operation.
        */
        virtual CPosLmOperation* ImportLandmarksL(
        /* IN  */       CPosLandmarkParser&  aLandmarkParser,
        /* IN */        const RArray<TUint>&  aLandmarkSelection,
        /* IN  */       TTransferOptions  aTransferOptions
        ) = 0;

        /**
        * Returns an object for iterating the landmarks added in an import
        * operation.
        *
        * To import landmarks @ref ImportLandmarksL is used.
        *
        * If @ref ImportedLandmarksIteratorL is called before the
        * @ref ImportLandmarksL operation has completed, the iterator will
        * iterate the landmarks imported so far. Landmarks imported after
        * the iterator is obtained will not affect the iterator. A new
        * iterator must be obtained to iterate these new landmarks.
        *
        * The client takes ownership of the returned iterator object.
        *
        * @since S60 3.0
        * @param aImportOperation This object is returned by
        *   @ref ImportLandmarksL methods.
        * @returns An object for iterating the landmarks added in the latest
        *   import operation.
        */
        virtual CPosLmItemIterator* ImportedLandmarksIteratorL(
        /* IN  */       CPosLmOperation*  aImportOperation
        ) = 0;

        /*
        * \internal
        *
        * Returns the database access implementation ID.
        *
        * This function is not supposed to be used by clients.
        *
        * @returns The @ref CPosLandmarkDatabase implementation ID.
        */
        TUid ImplementationId() const;

    protected:

        /**
        * C++ default constructor.
        */
        IMPORT_C CPosLandmarkDatabase();

    private:

        // By default, prohibit copy constructor
        CPosLandmarkDatabase( const CPosLandmarkDatabase& );
        // Prohibit assigment operator
        CPosLandmarkDatabase& operator= ( const CPosLandmarkDatabase& );

    private:    // Data

        // Implementation Uid
        TUid iDtorIdKey;
    };

// CPOSLANDMARKDATABASE_H
#endif

// End of File
