/*
* ==============================================================================
*  Name        : EPos_CPosLandmarkParser.h
*  Part of     : Mobile Location Framework/Landmarks
*  Interface   : Landmarks API
*  Description :
*     See class description below
*  Version     : 1.10    2005/07/07 13:40:47
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

#ifndef CPOSLANDMARKPARSER_H
#define CPOSLANDMARKPARSER_H

//  INCLUDES
#include <e32base.h>
#include <f32file.h>
#include "EPos_Landmarks.h"
#include "EPos_CPosLandmark.h"
#include "EPos_CPosLandmarkCategory.h"
#include "EPos_CPosLmOperation.h"

// FORWARD DECLARATIONS
class CPosLandmarkParserExtension;

// CLASS DECLARATION

/**
*  Class used for parsing landmark content.
*
*  When creating an instance of this class, the type (e.g. the mime type) of
*  the landmark content must be specified. The client will then receive a
*  parser implementation which understands the requested landmark content.
*
*  The client specifies landmark content either in a buffer or in a file. The
*  buffer/file is needed until the client no longer uses the parser object for
*  accessing the parsed data. If the buffer/file is deleted or modified, it
*  may not be possible to access the parsed landmark data.
*
*  @ref ParseContentL returns a @ref CPosLmOperation which means parsing can
*  be run incrementally. Each call to @ref CPosLmOperation::NextStep parses
*  one landmark. The landmark can be retrieved by calling @ref LandmarkLC.
*
*  Optionally, the client can specify that the parser should build an index.
*  An index enables direct access to all landmarks when the content has been
*  fully parsed. The content is fully parsed when CPosLmOperation::NextStep
*  or CPosLmOperation::ExecuteL complete with KErrNone. The LandmarkLC method
*  then can be called with landmark index to directly access any of parsed
*  landmarks.
*
*  If @ref CPosLandmarkParser is used, the client must call the global
*  function @ref ReleaseLandmarkResources before terminating, in order to
*  release all used landmark resources, otherwise the client may receive
*  an ALLOC panic.
*
*  To use this class, link against @p eposlandmarks.lib.
*
*  @lib eposlandmarks.lib
*  @since S60 3.0
*  @version $Revision: 1.10 $, $Date: 2005/07/07 13:40:47 $
*/
class CPosLandmarkParser : public CBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * The client must specify the type (e.g. the mime type) of the landmark
        * content which should be parsed. If the type is not supported, this
        * function will leave with code @p KErrNotSupported.
        *
        * @since S60 3.0
        * @param The mime-type of the content to parse.
        * @return A new instance of this class.
        */
        IMPORT_C static CPosLandmarkParser* NewL(
        /* IN  */       const TDesC8&  aContentMimeType
        );

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CPosLandmarkParser();

    public: // New functions

        /**
        * Sets the buffer to be parsed.
        *
        * The parser does not copy the data which means the buffer must not
        * be deleted or modified until the client no longer uses the parser
        * to access the content.
        *
        * This call discards any previous parsing result.
        *
        * @since S60 3.0
        * @param aBuffer The buffer containing the landmark content.
        */
        virtual void SetInputBuffer(
        /* IN  */       const TDesC8&  aBuffer
        ) = 0;

        /**
        * Opens the file with the landmark content to be parsed.
        *
        * The file is opened in read-only sharing mode which means the file
        * cannot be deleted or modified until the file is released. The file is
        * released either by deleting the parser object or if
        * @ref SetInputBuffer, @ref SetInputFileL or @ref SetInputFileHandleL
        * is called for some new landmark content data.
        *
        * This call discards any previous parsing result.
        *
        * @since S60 3.0
        * @param aFile The file containing the landmark content.
        */
        virtual void SetInputFileL(
        /* IN  */       const TDesC&  aFile
        ) = 0;

        /**
        * Sets a handle to the file which should be parsed.
        *
        * The file needs to be open until the client no longer uses the parser
        * to access the content.
        *
        * This call discards any previous parsing result.
        *
        * @since S60 3.0
        * @param aFileHandle The handle to the file which should be parsed.
        */
        virtual void SetInputFileHandleL(
        /* IN  */       RFile&  aFileHandle
        ) = 0;

        /**
        * Parse landmark content.
        *
        * The landmark content to be parsed is specified in
        * @ref SetInputBuffer, @ref SetInputFileL or @ref SetInputFileHandleL.
        * If landmark content has not been specified, this function will panic
        * with error code @p EPosLmProtocolBreak.
        *
        * Any previously parsed data is discarded.
        *
        * The function returns an operation object which can be run in
        * incremental mode. If it is run incrementally the client can supervise
        * the progress of the operation.
        *
        * The client takes ownership of the returned operation object.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, it will not be possible to retrieve any parsed data.
        *
        * If the content is in unrecognized format, or if the content is
        * invalid, this operation will fail with error code
        * @p KErrPosLmUnknownFormat.
        *
        * If another content source is set by @ref SetInputBuffer,
        * @ref SetInputFileL or @ref SetInputFileHandleL, then this method
        * needs to be called again to get a new operation object. If the
        * previous operation object is still executed, it will panic with error
        * code @p EPosLmProtocolBreak.
        *
        * The client can specify that the parser should build an index while
        * parsing. Building an index uses more memory but it allows unlimited
        * direct access to all parsed data. If the parser does not support
        * indexing, this call will fail with error code @p KErrNotSupported.
        *
        * @since S60 3.0
        * @param aBuildIndex Specifies if the parser should build an
        *   index.
        * @return A handle to the operation.
        */
        virtual CPosLmOperation* ParseContentL(
        /* IN  */       TBool  aBuildIndex = EFalse
        ) = 0;

        /**
        * Retrieve the total number of parsed landmarks.
        *
        * This function can also be called while ParseContentL is
        * incrementally executed.
        *
        * @since S60 3.0
        * @return The total number of parsed landmarks.
        */
        virtual TUint32 NumOfParsedLandmarks() const = 0;

        /**
        * Retrieve the first landmark collection data identifier.
        *
        * Landmark collection data is generic information about the landmark
        * collection.
        *
        * If there is no landmark collection data, this function will return
        * @p EPosLmCollDataNone.
        *
        * To retrieve the next collection data, call @ref NextCollectionDataId.
        * To retrieve the content of the collection data, call
        * @ref CollectionData.
        *
        * @since S60 3.0
        * @return The first landmark collection data.
        */
        virtual TPosLmCollectionDataId FirstCollectionDataId() const = 0;

        /**
        * Retrieve the next landmark collection data identifier.
        *
        * Landmark collection data is generic information about the landmark
        * collection.
        *
        * If there is no more landmark collection data, this function will
        * return @p EPosLmCollDataNone.
        *
        * To retrieve the first collection data, call
        * @ref FirstCollectionDataId. To retrieve the content of the collection
        * data, call @ref CollectionData.
        *
        * @since S60 3.0
        * @return The next landmark collection data.
        */
        virtual TPosLmCollectionDataId NextCollectionDataId(
        /* IN  */       TPosLmCollectionDataId  aCollectionData
        ) const = 0;

        /**
        * Retrieve a specific collection data.
        *
        * If the requested collection data is not found, this function will
        * return an empty descriptor.
        *
        * The returned descriptor pointer can be used as long as the parser
        * object exists and is not reset by calling @ref SetInputBuffer,
        * @ref SetInputFileL or @ref SetInputFileHandleL.
        *
        * @since S60 3.0
        * @param aDataId The collection data to retrieve.
        * @return The requested collection data.
        */
        virtual TPtrC CollectionData(
        /* IN  */       TPosLmCollectionDataId  aDataId
        ) const = 0;

        /**
        * Retrieve a parsed landmark.
        *
        * The client can supply an index of the landmark to retrieve. Index
        * must be a positive number and less than the number of parsed
        * landmarks, otherwise this function will panic with error code
        * @p EPosInvalidIndex. If no index has been built, this function
        * will leave with error code @p KErrNotFound.
        *
        * A landmark index is built by supplying a parameter in
        * @ref ParseContentL.
        *
        * If @a aLandmarkIndex parameter is omitted, or
        * @p KPosLastParsedLandmark is supplied, then this function will
        * retrieve the last parsed landmark. This does not require that an
        * index has been built. Each @ref CPosLmOperation::NextStep call
        * will parse a new landmark.
        *
        * The client may retrieve the categories of the landmark by
        * calling @ref LandmarkCategoryLC and supplying the category ID
        * which can be obtained from the landmark object.
        *
        * @p Note that even if the returned landmark object is modified, the
        * changes will not be included when importing using
        * @ref CPosLandmarkDatabase::ImportLandmarksL.
        *
        * The client takes ownership of the returned landmark object.
        *
        * @since S60 3.0
        * @param aLandmarkIndex The index of the landmark to retrieve.
        * @return The requested landmark.
        */
        virtual CPosLandmark* LandmarkLC(
        /* IN  */       TUint  aLandmarkIndex = KPosLastParsedLandmark
        ) const = 0;

        /**
        * Retrieve a landmark category found in a parsed landmark.
        *
        * A landmark may include the IDs of some landmark categories. These
        * categories are retrieved by calling this function.
        *
        * If the client passes a category ID which is not part of the parsed
        * landmark content, this function will leave with code @p KErrNotFound.
        *
        * @p Note that a category ID in this case is not the ID of a category
        * stored in a database, but the category ID specified in
        * the parsed landmark.
        *
        * @p Note that even if the returned category object is modified, the
        * changes will not be included when importing using
        * @ref CPosLandmarkDatabase::ImportLandmarksL.
        *
        * The client takes ownership of the returned category object.
        *
        * @since S60 3.0
        * @param aCategoryId The ID of the landmark category.
        * @return The requested landmark category.
        */
        virtual CPosLandmarkCategory* LandmarkCategoryLC(
        /* IN  */       TPosLmItemId  aCategoryId
        ) const = 0;

    protected:

        /**
        * C++ default constructor.
        */
        IMPORT_C CPosLandmarkParser();

    private:

        // By default, prohibit copy constructor
        CPosLandmarkParser( const CPosLandmarkParser& );
        // Prohibit assigment operator
        CPosLandmarkParser& operator= ( const CPosLandmarkParser& );

    private:

        CPosLandmarkParserExtension* iExtension;

        // Implementation Uid
        TUid iDtorIdKey;

    };

// CPOSLANDMARKPARSER_H
#endif

// End of File
