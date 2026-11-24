/*
* ==============================================================================
*  Name        : EPos_CPosLandmarkEncoder.h
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

#ifndef CPOSLANDMARKENCODER_H
#define CPOSLANDMARKENCODER_H

//  INCLUDES
#include <e32base.h>
#include "EPos_Landmarks.h"
#include "EPos_CPosLandmark.h"
#include "EPos_CPosLandmarkCategory.h"
#include "EPos_CPosLmOperation.h"

// FORWARD DECLARATIONS
class CPosLandmarkEncoderExtension;

// CLASS DECLARATION

/**
*  Class used for encoding landmark content.
*
*  When creating an instance of this class, the type (e.g. the mime type) of
*  the landmark content must be specified. The client will then receive an
*  encoder implementation which understands the requested landmark content.
*
*  Output is written either to a buffer or to a file.
*
*  The basic protocol for encoding is to 1) define where to write the
*  output to by calling @ref SetUseOutputBufferL or @ref SetOutputFileL, 2)
*  optionally add collection data using @ref AddCollectionDataL, 3) add
*  landmark data to encode by using functions in @ref CPosLandmarkEncoder
*  and/or @ref CPosLandmarkDatabase::ExportLandmarksL and 4) finalize the
*  encoding by calling @ref FinalizeEncodingL. If this protocol is not followed
*  the client is panicked with error code @p EPosLmProtocolBreak. Encoding can
*  be performed multiple times using the same encoder object.
*
*  If @ref CPosLandmarkEncoder is used, the client must call the global
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
class CPosLandmarkEncoder : public CBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        *
        * The client must specify the type (e.g. the mime type) of the content
        * format which should be used for encoding. If the type is not
        * supported, this function will leave with code @p KErrNotSupported.
        *
        * @since S60 3.0
        * @param The mime-type of the encode format.
        * @return A new instance of this class.
        */
        IMPORT_C static CPosLandmarkEncoder* NewL(
        /* IN  */       const TDesC8&  aContentMimeType
        );

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CPosLandmarkEncoder();

    public: // New functions

        /**
        * Encode to a buffer.
        *
        * This function returns a dynamic buffer which will be filled with
        * encoded landmark content. The client takes ownership of the buffer.
        *
        * The client must not delete the buffer until encoding is finalized.
        *
        * @since S60 3.0
        * @return The output buffer.
        */
        virtual CBufBase* SetUseOutputBufferL() = 0;

        /**
        * Encode to a file.
        *
        * The client specifies an output file for the encoder. The encoder
        * will then write all encoded data to this file.
        *
        * The file will be opened in exclusive mode which means that the file
        * cannot be accessed until the file is closed. The file is closed when
        * @ref FinalizeEncodingL has been executed. The file is also closed
        * if a new encoding is initialized by a call to
        * @ref SetUseOutputBufferL or @ref SetOutputFileL. After this, further
        * encoding to the old file is not possible.
        *
        * If there is already a file with the specified name, this function
        * will leave with error code @p KErrAlreadyExists.
        *
        * @since S60 3.0
        * @param aOutputFile The file name to write the encoded data to.
        */
        virtual void SetOutputFileL(
        /* IN */        const TDesC&  aOutputFile
        ) = 0;

        /**
        * Add landmark collection data to be encoded.
        *
        * Landmark collection data is generic information about the landmark
        * collection. It can for instance contain a name for the landmark
        * collection. Predefined collection attributes are defined by
        * @ref TPosLmCollectionDataId enumeration but also format specific
        * collection meta data can be defined.
        *
        * Collection data must be added before any landmarks are added. If
        * collection data is added later, this function will panic with
        * error code @p EPosLmProtocolBreak.
        *
        * Each collection ID can only be specified once. If a collection ID
        * is specified twice, this function will leave with error code
        * @p KErrAlreadyExists.
        *
        * If the collection data is not a part of the chosen landmark encoding
        * format, it will be silently ignored.
        *
        * It is not allowed to pass @p EPosLmCollDataNone to this function.
        * Doing so results in a panic with error code @p EPosLmInvalidArgument.
        *
        * @since S60 3.0
        * @param aDataId Identifies which collection data to add.
        * @param aCollectionData The collection data which should be added.
        */
        virtual void AddCollectionDataL(
        /* IN  */       TPosLmCollectionDataId  aDataId,
        /* IN  */       const TDesC&  aCollectionData
        ) = 0;

        /**
        * Add a landmark to be encoded.
        *
        * If the landmark contains any categories, those categories may be
        * added by calling @ref AddCategoryForLatestLandmarkL.
        *
        * The client can either call this function directly or pass this encoder
        * object to @ref CPosLandmarkDatabase::ExportLandmarksL.
        *
        * @since S60 3.0
        * @param aLandmark The landmark to add.
        */
        virtual void AddLandmarkL(
        /* IN  */       const CPosLandmark&  aLandmark
        ) = 0;

        /**
        * Add a landmark category for the most recently added landmark.
        *
        * The landmark category is added to the landmark which was most
        * recently added using @ref AddLandmarkL.
        *
        * If no landmarks have been added, this function panics with error code
        * @p EPosLmProtocolBreak.
        *
        * The client can either call this function directly or pass this
        * encoder object to @ref CPosLandmarkDatabase::ExportLandmarksL.
        *
        * @since S60 3.0
        * @param aCategory The landmark category to add.
        */
        virtual void AddCategoryForLatestLandmarkL(
        /* IN  */       const CPosLandmarkCategory&  aCategory
        ) = 0;

        /**
        * Finalize the encode process.
        *
        * Writes any buffered data to the output buffer/file. If an output
        * buffer is used it is compressed so that unused memory is freed. If an
        * output file is used, it is closed.
        *
        * After finalizing, further encoding to the specified output is not
        * possible. To start a new encoding, @ref SetUseOutputBufferL or
        * @ref SetOutputFileL must be called.
        *
        * The function returns an operation object which can be run in
        * incremental mode. If it is run incrementally the client can supervise
        * the progress of the operation.
        *
        * The client takes ownership of the returned operation object.
        *
        * If the @ref CPosLmOperation object is deleted before the operation
        * is complete, finalize is cancelled. Further encoding will not be
        * possible.
        *
        * @since S60 3.0
        * @return A handle to the operation.
        */
        virtual CPosLmOperation* FinalizeEncodingL() = 0;

    protected:

        /**
        * C++ default constructor.
        */
        IMPORT_C CPosLandmarkEncoder();

    private:

        // By default, prohibit copy constructor
        CPosLandmarkEncoder( const CPosLandmarkEncoder& );
        // Prohibit assigment operator
        CPosLandmarkEncoder& operator= ( const CPosLandmarkEncoder& );

    private:    // Data
        CPosLandmarkEncoderExtension* iExtension;

        // Implementation Uid
        TUid iDtorIdKey;
    };

// CPOSLANDMARKENCODER_H
#endif

// End of File
